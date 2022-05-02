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

#include <iostream>
#include <fstream>
#include <string>       // std::string
#include <sstream>      // std::stringstream
#include <cstdlib>
#include <cstdarg>
#include <algorithm>
#include <regex>

#include <Exception.h>
#include <Environment.h>
#include <common/inc/WriteMessage.h>
#include <common/inc/StringSup.h>
#include <common/inc/FileSup.h>
#include <common/inc/PlatformDependentDefines.h>
#include <graph/inc/graph.h>
#include <graphsupport/inc/GraphConstants.h>
#include <controller/inc/ProfileCommon.h>
#include <controller/inc/messages.h>
#include <archivecpp/inc/ArchiveHandler.h>

#include <boost/filesystem/path.hpp>
#include <boost/filesystem.hpp>
#include <boost/filesystem/operations.hpp>
#include <boost/regex.hpp>

#include "../inc/Task.h"
#include "../inc/messages.h"
#include "../inc/Properties.h"

using namespace std;
using namespace columbus;
using namespace columbus::controller;
using namespace common;
using namespace boost::filesystem;

namespace
{
  void generateClangTidyConfigFile(columbus::rul::RulHandler& rulHandler, const std::string& outputFileName);
  list<TemporalArhiveExtractor> archives;
}


TASK_NAME_DEF (CleanupTask);

Task::ExecutionResult CleanupTask::execute()
{
  ExecutionResult result;
  ExecutionLogger logger(this, result);

  try {
    // Although the desctructor will be called during the program termination we
    // invoke it here just to remove them as soon as possible
    logstream << "Removing the contents of the temporarily extracted archives.\n";
    archives.clear();

    path wrapperbin(LONGDIRPREFIXSTRING + (props.columbusWrapperTmpDir / "bin").wstring());
    logstream << "Removing directory: " << wrapperbin.string() << "\n";

    boost::system::error_code errorcode;
    for(int i=0; i<3; i++){
      remove_all(wrapperbin, errorcode);
      if(errorcode.value() == boost::system::errc::success)
        break;
    }

    logger.warningIfFail( errorcode.value() == boost::system::errc::success, "Failed to remove wrapper bin directory. %s.\n", errorcode.message().c_str());

  } HANDLE_TASK_EXCEPTIONS
  return result;
}

CleanupTask::CleanupTask(const Properties& properties) : Task(properties)
{
  addDependsOn(GraphMergeTask::name);
}

TASK_NAME_DEF( CleanProjectTask);

Task::ExecutionResult CleanProjectTask::execute()
{
  ExecutionResult result;
  ExecutionLogger logger(this, result);

  try {

    if(exists(props.projectBaseDir) && is_directory(props.projectBaseDir)){

      recursive_directory_iterator it(props.projectBaseDir);
      recursive_directory_iterator endit;

      list<path> folderList;

      while(it != endit)
      {
        if(is_directory(*it) && it->path().filename() == props.analysisOutputDir) {
          folderList.push_back(it->path());
        }
        ++it;
      }
      for(list<path>::iterator folder = folderList.begin(); folder != folderList.end(); ++folder){
        logstream << "Removing directory: " << folder->string() << endl;
        remove_all(*folder);
      }
    }

  } HANDLE_TASK_EXCEPTIONS
  return result;
}

CleanProjectTask::CleanProjectTask(const Properties& properties) : Task(properties)
{
  addDependsOn(Can2limTask::name);
  addDependsOn(GraphDumpTask::name);
}



TASK_NAME_DEF(WrapperTask);

Task::ExecutionResult WrapperTask::execute()
{
  ExecutionResult result;
  ExecutionLogger logger(this, result);

  try {
    path wrapperWorkDir = props.columbusWrapperTmpDir;
    path wrapperWorkDirBin = wrapperWorkDir / "bin";    // These directories are used in the LinkStaticLibsTask as well
    path wrapperWorkDirLog = wrapperWorkDir / "log";
    path wrapperWorkDirTmp = wrapperWorkDir / "tmp";
    path wrapperWorkDirLib = wrapperWorkDir / "lib";

    createDirectories(wrapperWorkDirBin, logger);
    createDirectories(wrapperWorkDirLog, logger);
    createDirectories(wrapperWorkDirTmp, logger);
    createDirectories(wrapperWorkDirLib, logger);

    copyBinaryExecutable(props.wrapperToolsDir, wrapperWorkDirBin, "CAN");
    copyBinaryExecutable(props.wrapperToolsDir, wrapperWorkDirBin, "CANConfig");
    copyBinaryExecutable(props.wrapperToolsDir, wrapperWorkDirBin, "CANLink");
    copyBinaryExecutable(props.wrapperToolsDir, wrapperWorkDirBin, "CANLib");
    copyBinaryExecutable(props.wrapperToolsDir, wrapperWorkDirBin, "AnalyzerWrapperConfig");

    copyDirectory(props.wrapperToolsDir, wrapperWorkDirBin, "cppcheck");
    copyDirectory(props.wrapperToolsDir, wrapperWorkDirLib, "clang");

    SafeEnvironmentModifier wwd_env("WRAPPER_WORK_DIR", wrapperWorkDir, logger);
    SafeEnvironmentModifier wbd_env("WRAPPER_BIN_DIR", wrapperWorkDirBin, logger);
    SafeEnvironmentModifier wld_env("WRAPPER_LOG_DIR", wrapperWorkDirLog, logger);
    SafeEnvironmentModifier wtd_env("WRAPPER_TEMP_DIR", wrapperWorkDirTmp, logger);
    SafeEnvironmentModifier we_env("WRAPPER_ENVIRONMENT", props.tempDir, logger);
    SafeEnvironmentModifier wwdn_env("WRAPPER_WORK_DIR_NAME", props.columbusWrapperTmpDirName, logger);

    // -------------------------------------------------------------------------------------------------------------
    // --------------------------------------- WrapperEnvironmentConfig --------------------------------------------
    // -------------------------------------------------------------------------------------------------------------

    path wrapperEnvironmentConfigPath = wrapperWorkDir / "wrapper_environment_config.ini";

    vector<string> sv;

    if (props.wrapperMode == WM_CL) 
	{
      wrapTool("cl.exe", "CLWrapper.exe", sv);
      wrapTool("link.exe", "LinkWrapper.exe", sv);
      wrapTool("lib.exe", "LibWrapper.exe", sv);
      wrapTool("clang-cl.exe","CLWrapper.exe",sv);
      wrapTool("lld-link.exe","LinkWrapper.exe",sv);
      wrapTool("llvm-lib.exe","LibWrapper.exe",sv);

      copy_file(props.wrapperBinDir/"VsbuildWrapper.exe", wrapperWorkDirBin / "msbuild.exe");
      copy_file(props.wrapperBinDir/"VsbuildWrapper.exe", wrapperWorkDirBin / "devenv.exe");
    } 
    else if (props.wrapperMode == WM_CLANG) 
    {
      string clangTool = props.prefix + "clang" + props.postfix;
      string clangppTool = props.prefix + "clang++" + props.postfix;
      string arTool  = props.prefix + "ar";
      string ldTool  = props.prefix + "ld";
      string lnTool  = props.prefix + "ln";
      string llvmarTool  = "llvm-ar";
      string llvmldTool  = "ld.lld";


      wrapTool(clangTool,"ClangWrapper",sv);
      wrapTool(clangppTool,"ClangWrapper",sv);
      wrapTool(arTool,"ArWrapper",sv);
      wrapTool(ldTool,"LdWrapper",sv);
      wrapTool(lnTool,"LnWrapper",sv);
      wrapTool(llvmarTool,"ArWrapper",sv);
      wrapTool(llvmldTool,"LdWrapper",sv);
      wrapTool("cp","CopyMoveWrapper",sv);
      wrapTool("mv","CopyMoveWrapper",sv);

      // creating rm wrapper script
      std::ofstream rm_wrapper((wrapperWorkDirBin / "rm").string().c_str());
      if (rm_wrapper) {
        rm_wrapper << "#!/bin/sh\n/bin/rm -rf \"$@\"" << endl;
        rm_wrapper.close();
        boost::filesystem::permissions(wrapperWorkDirBin / "rm", boost::filesystem::add_perms | boost::filesystem::owner_exe | boost::filesystem::group_exe | boost::filesystem::others_exe );
      } else {
        logstream << CMSG_CAN_NOT_CREATE_RM_WRAPPER_ERROR << endl;
        result.setError();
      }

      sv.push_back("-setWrapperRunFirst");
      sv.push_back("cp");
      sv.push_back("1");

      sv.push_back("-setWrapperRunFirst");
      sv.push_back("mv");
      sv.push_back("1");

      sv.push_back("-setWrappedExtraParamToBegin");
      sv.push_back("cp");
      sv.push_back("-R");

      if (!props.externalHardFilter.empty()) {
        sv.push_back("-setWrappedParamlistFilter");
        sv.push_back(clangTool);
        sv.push_back(props.externalHardFilter.string());

        sv.push_back("-setWrappedParamlistFilter");
        sv.push_back(clangppTool);
        sv.push_back(props.externalHardFilter.string());

        sv.push_back("-setWrappedParamlistFilter");
        sv.push_back(arTool);
        sv.push_back(props.externalHardFilter.string());

        sv.push_back("-setWrappedParamlistFilter");
        sv.push_back(ldTool);
        sv.push_back(props.externalHardFilter.string());

        sv.push_back("-setWrappedParamlistFilter");
        sv.push_back(llvmarTool);
        sv.push_back(props.externalHardFilter.string());

        sv.push_back("-setWrappedParamlistFilter");
        sv.push_back(llvmldTool);
        sv.push_back(props.externalHardFilter.string());

      }
    }
    else
    {
      throw Exception(COLUMBUS_LOCATION, "FAIL no wrapper config for this target.");
    }

    sv.push_back("-workingdir");
    sv.push_back(wrapperWorkDir.string());
    sv.push_back(wrapperEnvironmentConfigPath.string());

    checkedExec(props.wrapperBinDir / "WrapperEnvironmentConfig", sv, logger);

    SafeEnvironmentModifier config_env(ANALYZER_WRAPPER_CONFIG_FILE_ENV_VAR, wrapperEnvironmentConfigPath, logger);

    // ----------------------------------------------------------------------------------------------------------------------
    // --------------------------------------------------- AnalyzerWrapperConfig --------------------------------------------
    // ----------------------------------------------------------------------------------------------------------------------

    sv.clear() ;
    sv.push_back("-needToRun");
    sv.push_back("compiler");
    sv.push_back("1");

    sv.push_back("-toolMessageLevel");
    sv.push_back("compiler");
    addMessageLevelNumber(sv, 4, 3);

    sv.push_back("-messageLevel");
    addMessageLevelNumber(sv, 4, 3);

    sv.push_back("-needToRun");
    sv.push_back("linker");
    sv.push_back("1");

    sv.push_back("-toolMessageLevel");
    sv.push_back("linker");
    addMessageLevelNumber(sv, 4, 3);

    sv.push_back("-needToRun");
    sv.push_back("archive");
    sv.push_back("1");

    sv.push_back("-toolMessageLevel");
    sv.push_back("archive");
    addMessageLevelNumber(sv, 4, 3);

    if (!props.externalSoftFilter.empty()) {
      sv.push_back("-linkerFilterFile");
      sv.push_back(props.externalSoftFilter.string());
    }

    if (props.runCppcheck) {
      sv.push_back("-runCppcheck");
      sv.push_back("1");
    }

    if (props.wrapperMode == WM_CL)
    {
      if (props.noDelayedTemplateParsing) {
        sv.push_back("-noDelayedTemplateParsing");
        sv.push_back("1");
      }
    }

    sv.push_back("-outputDir");
    sv.push_back(props.analysisOutputDir);

    checkedExec(wrapperWorkDirBin / "AnalyzerWrapperConfig", sv, logger);

    // ----------------------------------------------------------------------------------------------------------------------

    string oldPath;
    const char* pathValue = getenv("PATH");
    if (pathValue != NULL)
      oldPath = pathValue;

    SafeEnvironmentModifier path_env("PATH", ((wrapperWorkDir / "bin").string() + PATH_SEPARATOR + oldPath).c_str(), logger, false);

    sv.clear();
    checkedExec(props.buildScript, sv, logger);

    if (exists(wrapperWorkDirLog / "Error.log")) {
      logstream << CMSG_WRAPPER_ERROR << endl;
      result.setError(CMSG_WRAPPER_ERROR);
    }
    boost::system::error_code ec;
    auto componentListSize = file_size(wrapperWorkDirLog / "component.list", ec);
    if (ec)
      componentListSize = 0;

    auto aastListSize = file_size(wrapperWorkDirLog / "aast.list", ec);
    if (ec)
      aastListSize = 0;

    if ((componentListSize == 0) && (aastListSize == 0))
    {
      logstream << CMSG_NO_OUTPUT_ERROR << endl;
      result.setCriticalError(CMSG_NO_OUTPUT_ERROR);
    }
  } HANDLE_TASK_EXCEPTIONS

  return result;
}

WrapperTask::WrapperTask(const Properties& properties) : Task(properties)
{
  addDependsOn(CleanResultsTask::name);
}

void WrapperTask::wrapTool(const string& wrappedTool, const string& wrapperTool, vector<string>& sv ) const
{
  sv.push_back("-wraptools");
  sv.push_back(wrappedTool);
  sv.push_back(wrapperTool);
  copy_file(props.wrapperBinDir/wrapperTool, props.columbusWrapperTmpDir/"bin"/wrapperTool, copy_option::overwrite_if_exists);
  copy_file(props.wrapperBinDir/("exewrapper" BINARYEXT), props.columbusWrapperTmpDir/"bin"/wrappedTool);
}



TASK_NAME_DEF(Can2limTask);

Task::ExecutionResult Can2limTask::execute()
{
  ExecutionResult result;
  ExecutionLogger logger(this, result);

  try {

    vector<string> sv;
    addMessageLevel(sv);

    sv.push_back("-ilist:" + (props.columbusWrapperTmpDir / "log" / "component.list").string());
    sv.push_back("-out:" + (props.asgDir / (props.projectName + ".lim")).string());

    if (props.maxCan2LimThreads > 0)
      sv.push_back("-maxThreads:" + to_string(props.maxCan2LimThreads));

    if (!props.externalSoftFilter.empty())
      sv.push_back("-fltp:" + props.externalSoftFilter.string());

    checkedExec(props.toolsDir / "CAN2Lim", sv, logger);

  } HANDLE_TASK_EXCEPTIONS

  return result;
}

Can2limTask::Can2limTask(const Properties& properties) : Task(properties)
{
  addDependsOn(LinkStaticLibsTask::name);
  addDependsOn(StaticLibHandlerTask::name);
  addDependsOn(WrapperTask::name);
}

TASK_NAME_DEF(ProfileTask);

Task::ExecutionResult ProfileTask::execute()
{
  ExecutionResult result;
  ExecutionLogger logger(this, result);
  try {

    // original rul files
    path CppcheckRulFileOrig = props.toolsDir / "Cppcheck.rul.md";
    path CppcheckRulMetadataFileOrig = props.toolsDir / "Cppcheck.rul_metadata.md";
    path ClangTidyRulFileOrig = props.toolsDir / "ClangTidy.rul.md";
    path ClangTidyRulMetadataFileOrig = props.toolsDir / "ClangTidy.rul_metadata.md";

    // temp rul files
    path CppcheckRulFile = props.tempDir / "Cppcheck.rul.md";
    path CppcheckRulMetadataFile = props.tempDir / "Cppcheck.rul_metadata.md";
    path ClangTidyRulFile = props.tempDir / "ClangTidy.rul.md";
    path ClangTidyRulMetadataFile = props.tempDir / "ClangTidy.rul_metadata.md";
    
    path ClangTidyConfigFile = props.tempDir / "ClangTidy.conf";

    // copy original rul files into temp
    if (exists(CppcheckRulFileOrig))
      copy_file(CppcheckRulFileOrig, CppcheckRulFile);
    if (exists(CppcheckRulMetadataFileOrig))
      copy_file(CppcheckRulMetadataFileOrig, CppcheckRulMetadataFile);
    if (exists(ClangTidyRulFileOrig))
      copy_file(ClangTidyRulFileOrig, ClangTidyRulFile);
    if (exists(ClangTidyRulMetadataFileOrig))
      copy_file(ClangTidyRulMetadataFileOrig, ClangTidyRulMetadataFile);

    // data
    ProfileHandler profile;
    map<string, rul::RulHandler*> rulHandlers; // for rul files
    map<string, bool> runTool; // running tools

    // load profile
    if(!props.profileXML.empty())
      profile.parseXML(props.profileXML.string());


    // load rul files
    rul::RulHandler cppcheckrh(CppcheckRulFile.string(), "Default", "eng");
    rul::RulHandler ctrh(ClangTidyRulFile.string(), "Default", "eng");

    rulHandlers.insert(make_pair("CPPCHECK", &cppcheckrh));
    rulHandlers.insert(make_pair("CT", &ctrh));

    // set running tools
    runTool.insert(make_pair("CPPCHECK", props.runCppcheck));
    runTool.insert(make_pair("CT", props.runClangTidy));

    //process rules csv
    profileProcessRulesCSV(profile, rulHandlers, runTool, props.rulesCSV.string());


    path MetricHunterThresholdsFileOrig = props.toolsDir / "MetricHunter.threshold";
    path MetricHunterThresholdsFile = props.tempDir / "MetricHunter.threshold";

    //process thresholds
    profileProcessToolThresholds(profile, "MetricHunter", MetricHunterThresholdsFileOrig.string(), MetricHunterThresholdsFile.string());

    //generate clang-tidy config file
    generateClangTidyConfigFile(ctrh,ClangTidyConfigFile.string());
    
    

    //process udm metrics
    bool UDM_result = profileProcessUDM(profile, (props.tempDir / "UDM.rul.md").string(), "cpp");
    if (!props.runUDMExplicit) {
      // if runUDM wasn't explicitly set, we decide by the presence of UDM metrics in the profile
      props.runUDM = UDM_result;
    }
    else if (props.runUDMExplicit && props.runUDM && !UDM_result) {
      // if, however, runUDM was explicitly set to true, but there are no valid UDM metrics, we abort
      throw Exception(COLUMBUS_LOCATION, "UDM explicitly set to run without corresponding setup in the profile XML");
    }

    //process lim2patterns parameters
    if (props.runLIM2Patterns) {
      map<string, string> parameters;
      if (profileProcessLIM2Patterns(profile, "LIM2Patterns", parameters)) {
        if (parameters.find("whitelist") != parameters.end()) {
          props.whitelist = parameters["whitelist"];
        }
        if (parameters.find("blacklist") != parameters.end()) {
          props.blacklist = parameters["blacklist"];
        }
        if (parameters.find("pattern_directories") != parameters.end()) {
          props.patternFile = parameters["pattern_directories"];
        }
      }
    }

  } HANDLE_TASK_EXCEPTIONS
  return result;
}

ProfileTask::ProfileTask(const Properties& properties) : Task(properties)
{
  addDependsOn(Can2limTask::name);
}

TASK_NAME_DEF(Cppcheck2GraphTask);

Task::ExecutionResult Cppcheck2GraphTask::execute()
{
  ExecutionResult result;
  ExecutionLogger logger(this, result);

  try {
    vector<string> sv;
    addMessageLevel(sv);

    sv.push_back("-graph:" + (props.graphDir / (props.projectName + "-cppcheck.graph")).string());
    sv.push_back("-rul:" + (props.tempDir / "Cppcheck.rul.md").string());
    sv.push_back("-exportrul");
    sv.push_back("-lim:" + (props.asgDir / (props.projectName + ".lim")).string());
    sv.push_back("-inputlist:" + (props.columbusWrapperTmpDir / "log" / "ast.list").string());
    sv.push_back("-out:" + (props.projectTimedResultDir  / (props.projectName + "-Cppcheck.txt")).string());

    checkedExec(props.toolsDir / "Cppcheck2Graph", sv, logger, false);

  } HANDLE_TASK_EXCEPTIONS

  return result;
}

Cppcheck2GraphTask::Cppcheck2GraphTask(const Properties& properties) : Task(properties)
{
  addDependsOn(LinkStaticLibsTask::name);
  addDependsOn(WrapperTask::name);
  addDependsOn(Can2limTask::name);
  addDependsOn(ProfileTask::name);
}

TASK_NAME_DEF(Lim2metricsTask);

Task::ExecutionResult Lim2metricsTask::execute()
{
  ExecutionResult result;
  ExecutionLogger logger(this, result);

  try {
    vector<string> sv;
    addMessageLevel(sv);

    sv.push_back("-graph:" + (props.graphDir / (props.projectName + "-metrics.graph")).string());
    sv.push_back("-rul:" + (props.toolsDir / "MET.rul.md").string());
    sv.push_back("-rulconfig:cpp");
    sv.push_back("-exportrul");
    sv.push_back((props.asgDir /  (props.projectName + ".lim")).string());

    checkedExec(props.toolsDir / "LIM2Metrics", sv, logger, false);

  } HANDLE_TASK_EXCEPTIONS

  return result;
}

Lim2metricsTask::Lim2metricsTask(const Properties& properties) : Task(properties)
{
  addDependsOn(LinkStaticLibsTask::name);
  addDependsOn(WrapperTask::name);
  addDependsOn(Can2limTask::name);
}

TASK_NAME_DEF(DcfTask);

Task::ExecutionResult DcfTask::execute()
{
  ExecutionResult result;
  ExecutionLogger logger(this, result);

  try {

    vector<string> sv;
    addMessageLevel(sv);

    sv.push_back("-inputlist:" + (props.columbusWrapperTmpDir / "log" / "component.list").string());
    sv.push_back("-lim:" + (props.asgDir / (props.projectName + ".lim")).string());
    sv.push_back("-graph:" + (props.graphDir  / (props.projectName + "-DCF.graph")).string());
    sv.push_back("-metrics");
    sv.push_back("-multipleasgroot");
    sv.push_back("-onlyfunctionclone");
    sv.push_back("-out:" + (props.projectTimedResultDir  / (props.projectName + "-clones.txt")).string());
    sv.push_back("-patternfilterlog:" + (props.logDir / "clone-filter.log").string());
    sv.push_back("-patternfilter");
    sv.push_back("30");
    sv.push_back("100");
    sv.push_back("-rul:" + (props.toolsDir / "DCF.rul.md").string());
    sv.push_back("-rulconfig:cpp");
    sv.push_back("-exportrul");

    if (props.cloneMinLines != -1)
      sv.push_back("-minlines:" + common::toString(props.cloneMinLines));
    if (props.cloneGenealogy){
      sv.push_back("-genealogy:" + (props.projectResultDir / (props.projectName + ".gsi")).string());
    }

    if (!props.externalSoftFilter.empty())
      sv.push_back("-fltp:" + props.externalSoftFilter.string());

    checkedExec(props.toolsDir / "DuplicatedCodeFinder", sv, logger, false);

  } HANDLE_TASK_EXCEPTIONS

  return result;
}

DcfTask::DcfTask(const Properties& properties) : Task(properties)
{
  addDependsOn(LinkStaticLibsTask::name);
  addDependsOn(StaticLibHandlerTask::name);
  addDependsOn(WrapperTask::name);
  addDependsOn(Can2limTask::name);
}

TASK_NAME_DEF(ClangTidyTask);

void ClangTidyTask::Worker::operator()()
{
  std::fstream logstream(logDir, ios_base::binary | ios_base::app);
  while (true)
  {
    bool result = false;
    vector<string> args;
    {
      // Take the next set of arguments to invoke clang-tidy with
      boost::lock_guard<boost::mutex> lock(m);
      if (clangtidy_args.empty())
        break;
      args = clangtidy_args.front();
      clangtidy_args.pop();
    }
    // Invoke clang-tidy with the arguments
    result = exec(program, args, logstream);

    {
      boost::lock_guard<boost::mutex> lock(m);

      if (result)
        *failure = true;
    }

    if(threadsLeft.load() > 0)
      threadsLeft--;
  }
  cv.notify_all();
}

Task::ExecutionResult ClangTidyTask::execute()
{
  ExecutionResult result;
  ExecutionLogger logger(this, result);
  
  try {
    path wrapperWorkDir = props.columbusWrapperTmpDir;
    path wrapperWorkDirLog = wrapperWorkDir / "log";
    const string ClangTidyConfigFile = (props.tempDir / "ClangTidy.conf").string();
    const boost::filesystem::path& clangTidyPath = props.wrapperToolsDir / "clang-tidy";

    list<string> astList;

    if (loadStringListFromFile((wrapperWorkDirLog / "ast.list").string(), astList))
    {
      astList.sort();
      astList.unique();

      // Start running clang-tidy on multiple threads
      queue<vector<string>> clangtidy_args; // Holds the arguements for each seperate run of the clang-metrics
      boost::condition_variable cv; // Used to notify the main thread when a thread has finished
      boost::mutex m;
      std::atomic<int> threadsLeft(astList.size()); // Used my the main thread to check if all other threads have finished
      vector<int> results(props.maxThreads, 0); // For each thread holds if any of it's clang-tidy executions failed

      // Setup the arguements
      for (const auto& fileName : astList)
      {
        string clangTidyOutputFile = fileName + ".ct.err";
        pathDeleteFile(clangTidyOutputFile);

        vector<string> args;
        args.push_back(fileName);
        args.push_back("-config-file=" + ClangTidyConfigFile);
        args.push_back("-xml=" + clangTidyOutputFile);
        args.push_back("--");
        clangtidy_args.push(args);
      }

     
      
      // Start the threads which will run clang-tidy with the given arguements, the current thread is already running on the threadPool so (maxThreads - 1) threads can be started 
      for (int i = 1; i < props.maxThreads; i++)
      {
        if(!clangtidy_args.empty())
        {
          string logDir = (properties.logDir / (getName() + "-T" + to_string(i) + ".log")).string();
          int* taskResult = &results[i];
          threadPool.add(columbus::thread::ThreadPool::PtrTask(new Worker(clangTidyPath, clangtidy_args, logDir, m, cv, threadsLeft, taskResult)));
        }
      }
      
      {
        // Start a worker on this thread too
        string logDir = (properties.logDir / (getName() + "-T0.log")).string();
        int* taskResult = &results[0];
        Worker worker(clangTidyPath, clangtidy_args, logDir, m, cv, threadsLeft, taskResult);
        worker();
      }

      // Wait for all the threads to finish
      boost::unique_lock<boost::mutex> lock(m);
      cv.wait(lock, [&threadsLeft]() { return  threadsLeft.load() == 0; });
      
      // Delete any empty log files
      for (int i = 0; i < props.maxThreads; i++)
      {
        string logDir = (properties.logDir / (getName() + "-T" + to_string(i) + ".log")).string();
        if (std::ifstream(logDir))
          if (file_size(logDir) == 0)
            std::remove(logDir.c_str());
      }

      bool failure = false;
      string errorMsg = "ERROR: Execution failure! \nCheck logs:\n";
      for (int i = 0; i < props.maxThreads; i++)
      {
        if (results.at(i) == 1)
        {
          failure = true;
          errorMsg += (properties.logDir / (getName() + "-T" + to_string(i) + ".log")).string() + "\n";
        }
      }
      
      logger.errorIfFail(!failure, errorMsg.c_str());

      vector<string> tidy2graphArgs;

      tidy2graphArgs.push_back("-graph:" + (props.graphDir / (props.projectName + "-clangtidy.graph")).string());
      tidy2graphArgs.push_back("-rul:" + (props.tempDir / "ClangTidy.rul.md").string());
      tidy2graphArgs.push_back("-exportrul");
      tidy2graphArgs.push_back("-lim:" + (props.asgDir / (props.projectName + ".lim")).string());
      tidy2graphArgs.push_back("-inputlist:" + (props.columbusWrapperTmpDir / "log" / "ast.list").string());
      tidy2graphArgs.push_back("-out:" + (props.projectTimedResultDir  / (props.projectName + "-ClangTidy.txt")).string());

      checkedExec(props.toolsDir / "ClangTidy2Graph", tidy2graphArgs, logger, false);
    }
  } HANDLE_TASK_EXCEPTIONS

  return result;
}

ClangTidyTask::ClangTidyTask(const Properties& properties, columbus::thread::ThreadPool& threadPool) : Task(properties), threadPool(threadPool)
{
  addDependsOn(Can2limTask::name);
  addDependsOn(ProfileTask::name);
}

TASK_NAME_DEF(Lim2umlTask);

Task::ExecutionResult Lim2umlTask::execute()
{
  ExecutionResult result;
  ExecutionLogger logger(this, result);

  try {

  } HANDLE_TASK_EXCEPTIONS
  return result;
}

Lim2umlTask::Lim2umlTask(const Properties& properties) : Task(properties)
{
  addDependsOn(LinkStaticLibsTask::name);
  addDependsOn(WrapperTask::name);
  addDependsOn(Can2limTask::name);
}

TASK_NAME_DEF(GraphMergeTask);

Task::ExecutionResult GraphMergeTask::execute()
{
  ExecutionResult result;
  ExecutionLogger logger(this, result);
  try {
    vector<string> sv;
    addMessageLevel(sv);

    directory_iterator end;

    for (directory_iterator fileIterator(props.graphDir); fileIterator != end; ++fileIterator) {
      sv.push_back(fileIterator->path().string());
    }
    sort(sv.begin(), sv.end());
    sv.push_back("-out:" + (props.projectTimedResultDir /  (props.projectName + ".graph")).string());
    sv.push_back("-summary");

    checkedExec(props.toolsDir / "GraphMerge", sv, logger);

  } HANDLE_TASK_EXCEPTIONS

  return result;
}

GraphMergeTask::GraphMergeTask(const Properties& properties) : Task(properties)
{
  addDependsOn(LinkStaticLibsTask::name);
  addDependsOn(WrapperTask::name);
  addDependsOn(Cppcheck2GraphTask::name);
  addDependsOn(Lim2metricsTask::name);
  addDependsOn(DcfTask::name);
  addDependsOn(Sonar2GraphTask::name);
  addDependsOn(ClangTidyTask::name);
}


TASK_NAME_DEF(GraphDumpTask);

Task::ExecutionResult GraphDumpTask::execute()
{
  ExecutionResult result;
  ExecutionLogger logger(this, result);
  try
  {
    {
      vector<string> sv;
      addMessageLevel(sv);

      sv.push_back((props.projectTimedResultDir /  (props.projectName + ".graph")).string());
      sv.push_back("-csv");
      sv.push_back("-xml");
      sv.push_back("-csvseparator:" + string(1, props.csvSeparator));
      sv.push_back("-csvdecimalmark:" + string(1, props.csvDecimalmark));
      sv.push_back("-sarif");
      sv.push_back("-sarifseverity:" + props.sarifSeverityLevel);

      checkedExec(props.toolsDir / "GraphDump", sv, logger);
    }

    {
      vector<string> sv;
      addMessageLevel(sv);

      sv.push_back((props.projectTimedResultDir / (props.projectName + "-summary.graph")).string());
      sv.push_back("-xml");
      sv.push_back("-json");

      checkedExec(props.toolsDir / "GraphDump", sv, logger);
    }

  } HANDLE_TASK_EXCEPTIONS

  return result;
}

GraphDumpTask::GraphDumpTask(const Properties& properties) : Task(properties)
{
  addDependsOn(GraphMergeTask::name);
  addDependsOn(MetricHunterTask::name);
  addDependsOn(UserDefinedMetricsTask::name);
  addDependsOn(LIM2PatternsTask::name);
}


TASK_NAME_DEF(CleanResultsTask);

Task::ExecutionResult CleanResultsTask::execute()
{
  ExecutionResult result;
  ExecutionLogger logger(this, result);
  try {
    set<path> directoryList;
    directory_iterator end;
    directory_iterator begin(props.projectResultDir);
    for( directory_iterator iter = begin; iter != end ; ++iter ) {
      if (is_directory(iter->path())) {
        static const regex dateFormatRegexpr("\\d{4}(-\\d{2}){5}");
        if (regex_match(iter->path().filename().string(), dateFormatRegexpr))
          directoryList.insert(*iter);
      }
    }

    set<path>::const_iterator dirIt = directoryList.begin();
    int toBeDeletedCounter = (int)directoryList.size() - props.cleanResults - 1;
    for (int dirCounter = 0; dirCounter < toBeDeletedCounter; ++dirCounter) {
      logstream << "Removing directory:" << dirIt->string() << "\n";
      remove_all(*dirIt);
      ++dirIt;
    }

    if (props.cleanResults == 0) {
      path genealogyFile = props.projectResultDir / (props.projectName + ".gsi");
      logstream << "Removing genealogy file:" << genealogyFile.string() << "\n";
      logger.warningIfFail(remove(genealogyFile), "Failed to remove the genealogy file:%s\n", genealogyFile.string().c_str());

      path lastMergedGraph = props.projectResultDir / (props.projectName + ".graph");
      logstream << "Removing the graph file:" << lastMergedGraph.string() << "\n";
      logger.warningIfFail(remove(lastMergedGraph), "Failed to remove the graph file:%s\n", lastMergedGraph.string().c_str());
    }

  } HANDLE_TASK_EXCEPTIONS

  return result;

}

CleanResultsTask::CleanResultsTask(const Properties& properties) : Task(properties)
{
  // there is no dependency
}

TASK_NAME_DEF(MetricHunterTask);

Task::ExecutionResult MetricHunterTask::execute()
{
  ExecutionResult result;
  ExecutionLogger logger(this, result);

  try {

    string graphFile = (props.projectTimedResultDir  / (props.projectName + ".graph")).string();

    vector<string> sv;
    addMessageLevel(sv);

    sv.push_back("-graph:" + graphFile);
    sv.push_back("-out:" + (props.projectTimedResultDir  / (props.projectName + "-MetricHunter.txt")).string());
    sv.push_back("-thresholds:" + (props.tempDir / "MetricHunter.threshold").string());

    sv.push_back("-exportrul");
    sv.push_back(graphFile);


    checkedExec(props.toolsDir / "MetricHunter", sv, logger, false);

  } HANDLE_TASK_EXCEPTIONS

  return result;
}

MetricHunterTask::MetricHunterTask(const Properties& properties) : Task(properties)
{
  addDependsOn(GraphMergeTask::name);
}

TASK_NAME_DEF(LinkStaticLibsTask);

Task::ExecutionResult LinkStaticLibsTask::execute() {
  ExecutionResult result;
  ExecutionLogger logger(this, result);

  try {

    path wrapperWorkDir = props.columbusWrapperTmpDir;
    path wrapperWorkDirBin = wrapperWorkDir / "bin";
    path wrapperWorkDirLog = wrapperWorkDir / "log";

    list<string> aastList;
    if (loadStringListFromFile((wrapperWorkDirLog / "aast.list").string(), aastList)) {
      aastList.sort();
      aastList.unique();
      for (const auto& filename : aastList)
      {
        if (filename.length() > 5) {
          string outputname = filename.substr(0, filename.length() - 4) + "component";
          std::ofstream componentFile(outputname.c_str(), ios::trunc);
          if (componentFile)
          {
            const string componentDirectoryName = filename + ".content";
            TemporalArhiveExtractor tae(filename, componentDirectoryName, true);
            for (const auto& astFilename : tae.getFileList())
              componentFile << astFilename << endl;
            archives.push_back(std::move(tae));
            componentFile.close();
          }

          std::ofstream componentlist((wrapperWorkDirLog / "component.list").string().c_str(), ios::app);
          if (componentlist) {
            componentlist << outputname << endl;
            componentlist.close();
          } else {
            logstream << CMSG_CANNOT_OPEN_LCSI_FOR_WRITING << endl;
          }

        } else {
          logstream << CMSG_TOO_SHORT_ACSI_NAME << "('" << filename << "')" << endl;
        }
      }
    }
  } HANDLE_TASK_EXCEPTIONS

  return result;
}

LinkStaticLibsTask::LinkStaticLibsTask(const Properties& properties) : Task(properties)
{
  addDependsOn(WrapperTask::name);
}

namespace {

  void generateClangTidyConfigFile(rul::RulHandler& rulHandler, const string& outputFileName)
  { 
    vector<string> disabledRules;

    std::vector<std::string> ruleIds;
    rulHandler.getRuleIdList(ruleIds);

    for (const auto &ruleId : ruleIds) {
      if (!rulHandler.getIsEnabled(ruleId)) {
        disabledRules.push_back(rulHandler.getOriginalIdByRuleId(ruleId));
      }
    }

    //All checks are enabled by default
    string checks = "*";

    if (disabledRules.size() > 0)
    {      
      //Concatenate disabled checks
      std::ostringstream buf;
      copy(disabledRules.begin(), disabledRules.end(), ostream_iterator<string>(buf, ",-"));

      string strDisabledRules("-" + buf.str());
      strDisabledRules = strDisabledRules.substr(0, strDisabledRules.size() - 2);
      checks = checks + ',' + strDisabledRules;
    }

    std::ofstream out(outputFileName, std::ofstream::out | std::ofstream::app);
    if (!out)
    {
      const char *cstr = outputFileName.c_str();
      WriteMsg::write(CMSG_FAILED_TO_OPEN_FILE, cstr);
    }
    else
    {
      out << "Checks: '" << checks << "'" << endl;
      out << "WarningsAsErrors: ''" << endl;
      out << "HeaderFilterRegex: ''" << endl;
      out << "AnalyzeTemporaryDtors: false" << endl;
      out.close();
    }
  }
}

TASK_NAME_DEF(UserDefinedMetricsTask);

Task::ExecutionResult UserDefinedMetricsTask::execute()
{
  ExecutionResult result;
  if (!props.runUDM) {
    inactives.push_back("UserDefinedMetrics");
    return result;
  }

  ExecutionLogger logger(this, result);

  try {
    vector<string> sv;
    sv.push_back((props.projectTimedResultDir / (props.projectName + ".graph")).string());
    sv.push_back("-rul:" + (props.tempDir / "UDM.rul.md").string());
    sv.push_back("-rulconfig:cpp");
    sv.push_back("-graph:" + (props.projectTimedResultDir / (props.projectName + ".graph")).string());

    checkedExec(props.toolsDir / "UserDefinedMetrics", sv, logger);

  } HANDLE_TASK_EXCEPTIONS

  return result;
}

UserDefinedMetricsTask::UserDefinedMetricsTask(list<string>& inactives, const Properties& properties) : Task(properties), inactives(inactives)
{
  addDependsOn(GraphMergeTask::name);
  addDependsOn(MetricHunterTask::name);
}

TASK_NAME_DEF(StaticLibHandlerTask);

Task::ExecutionResult StaticLibHandlerTask::execute()
{
  ExecutionResult result;
  ExecutionLogger logger(this, result);

  try
  {
    path wrapperWorkDir = props.columbusWrapperTmpDir;
    path wrapperWorkDirBin = wrapperWorkDir / "bin";
    path wrapperWorkDirLog = wrapperWorkDir / "log";

    list<string> aastList;
    if (loadStringListFromFile((wrapperWorkDirLog / "aast.list").string(), aastList))
    {
      aastList.sort();
      aastList.unique();
      for (const auto& filename : aastList)
      {
        if (filename.length() > 5) {
          string outputname = filename.substr(0, filename.length() - 4) + "component";
          std::ofstream componentFile(outputname.c_str(), ios::trunc);
          if (componentFile)
          {
            const string componentDirectoryName = filename + ".content";
            TemporalArhiveExtractor tae(filename, componentDirectoryName, true);
            for (const auto& astFilename : tae.getFileList())
              componentFile << astFilename << "\n";
            archives.push_back(std::move(tae));
            componentFile.close();
          }
        } else {
          logstream << CMSG_TOO_SHORT_ACSI_NAME << "('" << filename << "')" << endl;
        }
      }
    }

    list<string> componentList;
    if (loadStringListFromFile((wrapperWorkDirLog / "component.list").string(), componentList))
    {
      for (const auto& componentFilename : componentList)
      {
        list<string> astFilesOfTheComponent;
        loadStringListFromFile(componentFilename, astFilesOfTheComponent);
        // this looks weird
        for (auto astFilenameIerator = astFilesOfTheComponent.begin(); astFilenameIerator != astFilesOfTheComponent.end(); ++astFilenameIerator)
        {
          if (pathFindExtension(*astFilenameIerator) == "aast")
          {
            list<string> astFilesOfTheStaticLib;
            const string componentFilenameOfTheStaticLib = pathRemoveExtension(*astFilenameIerator) + ".component";
            loadStringListFromFile(componentFilenameOfTheStaticLib, astFilesOfTheStaticLib);
            for (const auto& extractedAstFilename : astFilesOfTheStaticLib)
              astFilesOfTheComponent.insert(astFilenameIerator, extractedAstFilename);

            astFilenameIerator = astFilesOfTheComponent.erase(astFilenameIerator);
            if (astFilenameIerator == astFilesOfTheComponent.end())
              break;
          }
        }

        std::ofstream componentFile(componentFilename.c_str(), ios::trunc);
        if (componentFile)
        {
            for (const auto& astFilename : astFilesOfTheComponent)
              componentFile << astFilename << "\n";
            componentFile.close();
        }
      }
    }

  } HANDLE_TASK_EXCEPTIONS

  return result;
}

StaticLibHandlerTask::StaticLibHandlerTask(const Properties& properties) : Task(properties)
{
  addDependsOn(WrapperTask::name);
}

SONAR2GRAPH_TASK(cpp)

Sonar2GraphTask::Sonar2GraphTask(const Properties& properties) : Task(properties)
{
  addDependsOn(Can2limTask::name);
}

TASK_NAME_DEF(LIM2PatternsTask);

Task::ExecutionResult LIM2PatternsTask::execute()
{
  ExecutionResult result;
  ExecutionLogger logger(this, result);
  try {
    vector<string> sv;

    sv.push_back("-graph:" + (props.projectTimedResultDir / (props.projectName + ".graph")).string());
    sv.push_back("-lim:" + (props.asgDir / (props.projectName + ".lim")).string());
    sv.push_back("-pattern:" + props.patternFile + (!props.patternFile.empty() ? "," : "") + (props.commonDir / "Patterns" / "AntiPatterns").string());
    sv.push_back("-metrics:" + (props.toolsDir / "MET.rul.md").string());
    sv.push_back("-out:" + (props.projectTimedResultDir / (props.projectName + ".txt")).string());

    if (!props.whitelist.empty()) {
        sv.push_back("-whitelist:" + props.whitelist);
    }
    if (!props.blacklist.empty()) {
        sv.push_back("-blacklist:" + props.blacklist);
    }

    checkedExec(props.commonDir / "LIM2Patterns", sv, logger);


  } HANDLE_TASK_EXCEPTIONS

    return result;
}

LIM2PatternsTask::LIM2PatternsTask(const Properties& properties) : Task(properties) {
  addDependsOn(GraphMergeTask::name);
  addDependsOn(MetricHunterTask::name);
  addDependsOn(UserDefinedMetricsTask::name);
}
