/*
 *  This file is part of OpenStaticAnalyzer.
 *
 *  Copyright (c) 2004-2018 Department of Software Engineering - University of Szeged
 *
 *  Licensed under Version 1.2 of the EUPL (the "Licence");
 *
 *  You may not use this work except in compliance with the Licence.
 *
 *  You may obtain a copy of the Licence in the LICENSE file or at:
 *
 *  https://joinup.ec.europa.eu/software/page/eupl
 *
 *  Unless required by applicable law or agreed to in writing, software
 *  distributed under the Licence is distributed on an "AS IS" basis,
 *  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *  See the Licence for the specific language governing permissions and
 *  limitations under the Licence.
 */

#include <lim/inc/lim.h>
#include "../inc/messages.h"
#include "../inc/ASTVisitor.h"
#include "../inc/MergeUID.h"

#include <csi/inc/csi.h>
#include <common/inc/PlatformDependentDefines.h>
#include <clang/AST/ASTContext.h>
#include <clang/Tooling/Tooling.h>
#include <clang/Tooling/CompilationDatabase.h>
#include <clang/Metrics/Output.h>
#include <clang/Metrics/invoke.h>

#include <ErrorCodes.h>
#include <common/inc/FileSup.h>
#include <common/inc/WriteMessage.h>
#include <common/inc/Arguments.h>
#include <common/inc/Stat.h>
#include <common/inc/DirectoryFilter.h>
#include <lim/inc/lim.h>
#include <threadpool/inc/ThreadPool.h>

#include <clangsupport/ASTFilter.h>
#include "../inc/clangHelpers.h"

#include <string>
#include <list>
#include <limits>
#include <set>
#include <iomanip>

#define PROGRAM_NAME "CAN2Lim"
#define EXECUTABLE_NAME PROGRAM_NAME

#include "MainCommon.h"

using namespace std;
using namespace columbus;
using namespace common;
using namespace clang;

#define BUFFERSIZE 8192
#define STATMEMSIZE size

static string listFile;
static string out;
static bool dLIMML = false;
static bool dGraphml= false;
bool pathLower = false;
string changePathFrom;
string changePathTo;
string g_filterfile;
int maxThreads = 0;

static list<string> inputFiles;

static bool ppList (const common::Option *o, char *argv[]) {
  listFile = argv[0];
  return true;
}

static bool ppOut (const common::Option *o, char *argv[]) {
  out = argv[0];
  return true;
}

static bool ppPathLower (const common::Option *o, char *argv[]) {
  pathLower = true;
  return true;
}

static bool ppLimDump (const common::Option *o, char *argv[]) {
  dLIMML = true;
  return true;
}

static bool dumpGRAPHML(const Option *o, char *argv[]) {
  dGraphml= true;
  return true;
}

static void ppFile(char *filename) {
  inputFiles.push_back(filename);
}

static bool ppFilterPath (const Option *o, char *argv[]) {
  g_filterfile = argv[0];
  return true;
}

static bool ppMaxThreads(const Option* o, char* argv[]) {
  maxThreads = common::str2int(argv[0]);
  return true;
}

const common::Option OPTIONS_OBJ [] = {
  { false,  "-ilist",        1, "listfile",        0, common::OT_WC,             ppList,           NULL,       "List file containing input filenames" },
  { false,  "-out",          1, "outputfile",      0, common::OT_WC,             ppOut,            NULL,       "Output file" },
  { false,  "-pathlower",    0, "",                0, common::OT_NONE,           ppPathLower,      NULL,       "Paths are converted to lower case for writting out" },
  { false,  "-dLIMML",       0, "",                0, common::OT_NONE,           ppLimDump,        NULL,       "Create LIMML dump" },
  { false,  "-dGRAPHML",     0, "",                0, common::OT_WC,             dumpGRAPHML,      NULL,       "Dump graphml to lim" },
  { false,  "-maxThreads",   1, CL_KIND_NUMBER,    0, OT_WE | OT_WC,             ppMaxThreads,     NULL,       "This parameter sets the maximum number of threads the Can2Lim can start. The default value is the number of available CPU cores on the current system."},
  CL_FLTP
  COMMON_CL_ARGS
};


void checkInputFiles() {

  if (!listFile.empty())
    loadStringListFromFile(listFile, inputFiles);

  if (inputFiles.empty())
  {
    WriteMsg::write(CMSG_CAN2LIM_NO_INPUT_FILE);
    clError();
  }

  if (inputFiles.size() == 1)
  {
    if (out.empty())
      out = pathRemoveExtension(*inputFiles.begin()) + ".lim";
  }
  else
  {
    if (out.empty())
      out = "noname.lim";
  }
}

static inline void setStartTime(uint64_t *time) {
  timestat usedtime= getProcessUsedTime();
  *time= usedtime.user + usedtime.system;
}

static inline void setElapsedTime(uint64_t *time) {
  timestat usedtime= getProcessUsedTime();
  *time= usedtime.user + usedtime.system - *time;
}

static inline void updateMemStat(uint64_t *max_mem) {
  memstat ms = getProcessUsedMemSize();
  if (*max_mem < ms.STATMEMSIZE) {
    *max_mem = ms.STATMEMSIZE;
  }
}

// The threadPool calls the () operator of this class
class MetricsWorker : public columbus::thread::Task
{
public:
  MetricsWorker(clang::metrics::Invocation& metricsInvocation, const tooling::FixedCompilationDatabase& compilationDatabase
    , queue<string>& compilationUnitNames, boost::shared_mutex& taskLockSharedMutex)
    : metricsInvocation(metricsInvocation)
    , compilationDatabase(compilationDatabase)
    , compilationUnitNames(compilationUnitNames)
    , taskLockSharedMutex(taskLockSharedMutex)
  {
  }

  void operator()()
  {
    // Breaks when there is no more work to do (When compilationUnitNames is empty)
    while (true)
    {
      vector<string> compilationsUnitsForCurrentThread;
      {
        // Take the name of the next compilation unit to process
        columbus::thread::ThreadPool::TaskLock lock(taskLockSharedMutex);
        if (compilationUnitNames.empty())
          break;
        compilationsUnitsForCurrentThread.push_back(compilationUnitNames.front());
        compilationUnitNames.pop();
      }
      // Invoke clang-metrics with the given compilation unit name
      metricsInvocation.invoke(compilationDatabase, compilationsUnitsForCurrentThread);
    }

  }

private:
  clang::metrics::Invocation& metricsInvocation;
  const tooling::FixedCompilationDatabase& compilationDatabase;
  queue<string>& compilationUnitNames;
  boost::shared_mutex& taskLockSharedMutex;
};

// The threadPool calls the () operator of this class
class CAN2LimWorker : public columbus::thread::Task
{
public:
  CAN2LimWorker(queue<string>& compilationUnitNames, const tooling::FixedCompilationDatabase& compilationDatabase, GlobalASTConversionInfo_ThreadSafe& globalConversionInfo, MergeUIDFactory& uidFactory, uint64_t& mem, boost::shared_mutex& taskLockSharedMutex)
    : uidFactory(uidFactory)
    , compilationUnitNames(compilationUnitNames)
    , compilationDatabase(compilationDatabase)
    , globalConversionInfo(globalConversionInfo)
    , mem(mem)
    , taskLockSharedMutex(taskLockSharedMutex)
  {
  }
  void operator()()
  {
    // Breaks when there is no more work to do (When compilationUnitNames is empty)
    while (true)
    {
      string compilationUnitName;
      {
        // Take the name of the next compilation unit to process
        columbus::thread::ThreadPool::TaskLock lock(taskLockSharedMutex);
        if (compilationUnitNames.empty())
          break;
        compilationUnitName = compilationUnitNames.front();
        compilationUnitNames.pop();
      }
      // Setup clang tool
      ASTConversionInfo conversionInfo(compilationUnitName.c_str(), compilationUnitName, globalConversionInfo, uidFactory);
      tooling::ClangTool tool(compilationDatabase, { compilationUnitName });
      unique_ptr<clang::tooling::FrontendActionFactory> factory = newConvert2LimActionFactory(conversionInfo);
      tool.clearArgumentsAdjusters();
      tool.appendArgumentsAdjuster(tooling::getClangStripOutputAdjuster());
      tool.appendArgumentsAdjuster(tooling::getInsertArgumentAdjuster("-fsyntax-only", tooling::ArgumentInsertPosition::BEGIN));

      WriteMsg::write(CMSG_CAN2LIM_CONVERTING, compilationUnitName.c_str());
      // Run clang tool
      tool.run(factory.get());
      {
        columbus::thread::ThreadPool::TaskLock lock(taskLockSharedMutex);
        updateMemStat(&mem);
      }
    }
  }

private:
  MergeUIDFactory& uidFactory;
  queue<string>& compilationUnitNames;
  const tooling::FixedCompilationDatabase& compilationDatabase;
  GlobalASTConversionInfo_ThreadSafe& globalConversionInfo;
  uint64_t& mem;
  boost::shared_mutex& taskLockSharedMutex;
};

CANFilePathRenamer cANFilePathRenamer(changePathFrom, changePathTo);

int main(int argc, char *argv[]) {
  uint64_t conversiontime = 0;
  uint64_t totaltime = 0;
  uint64_t mem = 0;
  int notExistedFiles = 0;
  int existedFiles = 0;

  WriteMsg::setAutomaticFlush(true);

  MAIN_BEGIN

    MainInit(argc, argv, "-");

    WriteMsg::setTimestampPrefixes(true);

    setStartTime(&totaltime);
    checkInputFiles();

    // Initialize LIM
    columbus::RefDistributorStrTable limStrTable;
    columbus::RefDistributorStrTable cppStrTable;

    const string rootName = "global namespace";
    lim::asg::Factory limFact(limStrTable, rootName, columbus::lim::asg::limLangCpp);

    auto rootNode = limFact.getRoot();
    //set the root package attributes which is not defined
    rootNode->setAccessibility(lim::asg::ackNone);
    rootNode->setIsStatic(false);
    rootNode->setDemangledName(rootName);

    updateMemStat(&mem);
    setStartTime(&conversiontime);
    
    MergeUIDFactory uidFactory;
    unique_ptr<metrics::Output> metricsOutput = make_unique<metrics::Output>(uidFactory);
    LimOrigin limOrigin;
    GlobalASTConversionInfo globalConversionInfo(limFact, *metricsOutput, limOrigin);

    vector<vector<string>> compilationUnitsByComponent;
    unordered_set<string> astFilesAlreadySeen;

    WriteMsg::write(WriteMsg::mlNormal, "\nBased on the input list, the following components will be analyzed:\n");
    // Read the component and ast filenames
    for (const string& componentFileName : inputFiles)
    {
      WriteMsg::write(WriteMsg::mlNormal,"%s", componentFileName.c_str());
      WriteMsg::write(WriteMsg::mlDebug, "; it's .ast files:");
      WriteMsg::write(WriteMsg::mlNormal, "\n");

      lim::asg::base::Component& component = limFact.createComponent(componentFileName.c_str());
      limFact.getComponentRootRef().addContains(&component);
      limFact.getRoot()->addBelongsTo(component.getId());

      list<string> temp;
      compilationUnitsByComponent.push_back(vector<string>());
      vector<string>& compilationUnits = compilationUnitsByComponent.back();

      if (!loadStringListFromFile(componentFileName, temp))
      {
        WriteMsg::write(CMSG_CAN2LIM_CANT_LOAD_COMPONENT_FILE, componentFileName.c_str()); //Error!
        return EXIT_FAILURE;
      }

      for (auto it = temp.begin(); it != temp.end(); ++it)
      {
        const string& astFileName = *it;
        if (common::pathFindExtension(astFileName) != "ast")
        { // Just skip...
        }
        else if(!common::pathFileExists(astFileName))
          WriteMsg::write(CMSG_FILE_DOES_NOT_EXIST, it->c_str()); //Error!
        else
        {
          GlobalASTConversionInfo::ASTIdentifier astID(astFileName);
          if (globalConversionInfo.componentsOfTU.count(astID) == 0)
          {
            // If this this is the first time we see this .ast file, we add it to a list, and we will analyze these
            compilationUnits.push_back(astFileName);
            astFilesAlreadySeen.insert(astFileName);
            WriteMsg::write(WriteMsg::mlDebug, "\t%s\n",it->c_str());
          }
          else
          {
            WriteMsg::write(WriteMsg::mlDebug, "\t%s (duplicate .ast file, thrown away)\n", it->c_str());
          }

          if (astFilesAlreadySeen.count(astFileName) == 0)
          {
            // If this .ast file is a copy of another one that we already encountered, we still have to add it as a file (for the DCF to work properly)
            string modifiedASTFilename = astFileName.c_str();
            columbus::lim::asg::physical::File *astFileNode = &globalConversionInfo.limFactory.createFile(modifiedASTFilename);

            if(!contains(component.getCompilationUnitListIteratorBegin(), component.getCompilationUnitListIteratorEnd(),astFileNode))
              component.addCompilationUnit(astFileNode);

            globalConversionInfo.limFactory.setFiltered(astFileNode->getId());

            astFilesAlreadySeen.insert(astFileName);
          }

          globalConversionInfo.componentsOfTU[astID].insert(&component);
        }
      }

      existedFiles++;
    }
    WriteMsg::write(WriteMsg::mlNormal, "\n");

    // Check maxThreads
    if (maxThreads == 0)
      maxThreads = columbus::thread::ThreadPool::getNumberOfCores();

    // Call clang-metrics

    const tooling::FixedCompilationDatabase compilationDatabase(".", { "-fno-delayed-template-parsing" }); // Fishy?

    updateMemStat(&mem);
    uint64_t metrics_calc_total_time = 0;
    setStartTime(&metrics_calc_total_time);

    WriteMsg::write(WriteMsg::mlNormal, "Clang-metrics has started processing all .ast files, calculating common code metrics (Multithread:%d) ... \n", maxThreads);
    bool clangMetricsHalsteadDebug = false;
    bool clangMetricsRangeDebug = false;

    bool clangMetricsProcessingTraceDebug = false;
    //cout << "Message level is " << WriteMsg::getMessageLevel() << endl;
    if (WriteMsg::getMessageLevel() >= WriteMsg::mlDebug) {
      clangMetricsProcessingTraceDebug = true;
    }

    // Create Invocation object that stores data across multiple invocation calls
    clang::metrics::Invocation metricsInvocation(std::move(metricsOutput), clang::metrics::InvokeOptions{ clangMetricsHalsteadDebug,clangMetricsRangeDebug,clangMetricsProcessingTraceDebug });
    // Analyze only one component at a time
    for (auto it = compilationUnitsByComponent.begin(); it != compilationUnitsByComponent.end(); it++)
    {
      columbus::thread::ThreadPool threadPool(maxThreads);
      queue<string> compilationUnitNames;

      // Setup a queue that will be accessed by all threads, holding the names of all the compilationUnits they must process between them
      for (const auto& compilationUnitName : *it)
        compilationUnitNames.push(compilationUnitName);

      // Create all the threads, the threadPool calls their () operator and they start analyzing the compilationsUnits in compilationUnitNames
      for (int i = 0; i < maxThreads; i++)
        threadPool.add(columbus::thread::ThreadPool::PtrTask(new MetricsWorker(metricsInvocation, compilationDatabase, compilationUnitNames, threadPool.getTaskLockMutex())));

      threadPool.wait();
    }

    // Call the metricsInvocation aggregate method and take ownership of the output object holding the results
    metricsOutput = metricsInvocation.aggregate();
    WriteMsg::write(WriteMsg::mlNormal, "Clang-metrics has finished!\n\n");

    setElapsedTime(&metrics_calc_total_time);

    // Call the conversions from the ASTs to LIM

    WriteMsg::write(WriteMsg::mlNormal, "Conversion of each .ast file to LIM nodes has started (Multithread:%d) ... \n", maxThreads);
    updateMemStat(&mem);
    uint64_t ast_conversion_total_time = 0;
    setStartTime(&ast_conversion_total_time);

    // Create threadsafe wrapper of the globalConversionInfo object
    GlobalASTConversionInfo_ThreadSafe globalInfoThreadSafe(globalConversionInfo);
    // Analyze only one component at a time
    for (auto it = compilationUnitsByComponent.begin(); it != compilationUnitsByComponent.end(); it++)
    {
      columbus::thread::ThreadPool threadPool(maxThreads);
      queue<string> compilationUnitNames;

      // Setup a queue that will be accessed by all threads, holding the names of all the compilationUnits they must process between them
      for (const auto& compilationUnitName : *it)
        compilationUnitNames.push(compilationUnitName);

      // Create all the threads, the threadPool calls their () operator and they start analyzing the compilationsUnits in compilationUnitNames
      for (int i = 0; i < maxThreads; i++)
        threadPool.add(columbus::thread::ThreadPool::PtrTask(new CAN2LimWorker(compilationUnitNames, compilationDatabase, globalInfoThreadSafe, uidFactory, mem, threadPool.getTaskLockMutex())));

      threadPool.wait();
    }

    WriteMsg::write(WriteMsg::mlNormal, "Conversion is finished!\n\n");

    // Post process of the whole conversion
    WriteMsg::write(WriteMsg::mlNormal, "Post processing the LIM (linking, comments, calculating global metrics, etc.) ...\n");
    globalConversionInfo.finalizeConversion();
    WriteMsg::write(WriteMsg::mlNormal, "Post processing is finished.\n");

    setElapsedTime(&ast_conversion_total_time);
    setElapsedTime(&conversiontime);

    updateMemStat(&mem);

    if (existedFiles == 0) {
      WriteMsg::write(CMSG_CAN2LIM_NO_LCSI_LOADED);
      return common::retASGLoadError;
    }

    uint64_t savingtime = 0;
    setStartTime(&savingtime);
    std::list<HeaderData*> headerList;
    headerList.push_back(&limOrigin);

    try {
      limFact.save(out,  headerList, false);
    } catch (const IOException& e) {
      common::WriteMsg::write(CMSG_CAN2LIM_FACTORY_SAVE_ERROR, e.getMessage().c_str());
    }

    setElapsedTime(&savingtime);

    string filterfile = out.substr(0, out.find_last_of('.')) + ".flim";
    try {
      limFact.saveFilter(filterfile);
    } catch  (const IOException&) {
      common::WriteMsg::write(CMSG_CAN2LIM_FILTER_SAVE_PROBLEM, filterfile.c_str());
    }

    // Save the LIM as .limml file (if flag is set)
    uint64_t limmltime = 0;
    setStartTime(&limmltime);

    if (dLIMML) {
      string limmlFile = common::pathRemoveExtension(out) + ".limml";
      ofstream ofLimml(limmlFile.c_str());
      if (!ofLimml.is_open()) {
        common::WriteMsg::write(CMSG_CAN2LIM_LIMML_DUMP_PROBLEM, limmlFile.c_str());
      } else {
        lim::asg::VisitorLIMML *visitorLimml = new lim::asg::VisitorLIMML(ofLimml, "");
        lim::asg::AlgorithmPreorder ap;
        ap.setVisitSpecialNodes(true, true);
        ap.run(limFact, *visitorLimml);
        delete visitorLimml;
        ofLimml.close();
      }
    }

    // Save the lim as .graphml file (if flag is set)
    if (dGraphml) {
      io::GraphmlIO ioToDumpGraphml((out + ".graphml").c_str(), "Lim");
      std::set<std::string> edgeFilter;
      lim::asg::VisitorGraphml visitorToDumpGraphml(ioToDumpGraphml, edgeFilter);
      lim::asg::AlgorithmPreorder ap;
      ap.run(limFact, visitorToDumpGraphml);
    }

    setElapsedTime(&limmltime);
    setElapsedTime(&totaltime);

    WriteMsg::write(CMSG_CAN2LIM_STATISTICS);
    WriteMsg::write(CMSG_CAN2LIM_CONVERSION_PHASE_TIME, ((float)conversiontime)/100);
    WriteMsg::write(CMSG_CAN2LIM_METRICS_CALC_TIME, ((float)metrics_calc_total_time)/100);
    WriteMsg::write(CMSG_CAN2LIM_CONVERSION_TIME, ((float)ast_conversion_total_time)/100);
    WriteMsg::write(CMSG_CAN2LIM_SAVE_TIME, ((float)savingtime)/100);
    WriteMsg::write(CMSG_CAN2LIM_DUMP_TIME, ((float)limmltime)/100);
    WriteMsg::write(CMSG_CAN2LIM_TOTAL_TIME, ((float)totaltime)/100);
    WriteMsg::write(CMSG_CAN2LIM_PEAK_MEMORY, ((float)mem)/1048576);
    WriteMsg::write(CMSG_CAN2LIM_NOT_EXISTED_FILES, notExistedFiles);

  MAIN_END

  //throw 20;

  return EXIT_SUCCESS;
}
