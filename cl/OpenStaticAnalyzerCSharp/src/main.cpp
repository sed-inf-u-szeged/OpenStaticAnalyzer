/*
 *  This file is part of OpenStaticAnalyzer.
 *
 *  Copyright (c) 2004-2017 Department of Software Engineering - University of Szeged
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

#include <time.h>
#include <fstream>
#include <common/inc/FileSup.h>
#include <common/inc/StringSup.h>
#include <common/inc/WriteMessage.h>
#include <common/inc/PlatformDependentDefines.h>
#include <threadpool/inc/ThreadPool.h>
#include <boost/filesystem.hpp>

#include "../inc/messages.h"
#include "../inc/Properties.h"
#include "../inc/Task.h"
#include <controller/inc/Controller.h>

#define PROGRAM_NAME "OpenStaticAnalyzer for C#"
#define EXECUTABLE_NAME "OpenStaticAnalyzerCSharp"

#include "MainCommon.h"

using namespace std;
using namespace common;
using namespace boost::filesystem;
using namespace columbus::controller;

Properties props;

static void ppFile(char *str) {
}

bool ppResultsDir(const common::Option *o, char *argv[]) {
  props.resultsDir = argv[0];
  return true;
}

bool ppProjectName(const common::Option *o, char *argv[]) {
  props.projectName = argv[0];
  return true;
}

bool ppInputFile(const common::Option *o, char *argv[]) {
  props.inputFile = argv[0];
  return true;
}

bool ppExternalHardFilter(const common::Option *o, char *argv[]) {
  props.externalHardFilter = argv[0];
  return true;
}

bool ppExternalSoftFilter(const common::Option *o, char *argv[]) {
  props.externalSoftFilter = argv[0];
  return true;
}

bool ppMaxThreads(const common::Option *o, char *argv[]) {
  props.maxThreads = common::str2int(argv[0]);
  return true;
}

bool ppCurrentDate(const common::Option *o, char *argv[]) {
  props.currentDate = argv[0];
  return true;
}

bool ppCleanResults(const common::Option *o, char *argv[]) {
  props.cleanResults = common::str2int(argv[0]);
  return true;
}

bool ppCloneGenealogy (const common::Option *o, char *argv[]) {
  if(strcmp(argv[0], "true") == 0)
    props.cloneGenealogy = true;
  else
    props.cloneGenealogy = false;
  return true;
}

bool ppCsvDecimalMark (const common::Option *o, char *argv[]) {
  if (argv[0][0] != 0)
    props.csvDecimalmark = argv[0][0];
  return true;
}

bool ppCsvSeparator (const common::Option *o, char *argv[]) {
  if (strcmp(argv[0], "\\t") == 0)
    props.csvSeparator = '\t';
  else if (argv[0] != 0)
    props.csvSeparator = argv[0][0];

  return true;
}

bool ppFxCopPath(const common::Option *o, char *argv[]) {
  props.fxcopBinaryPath = argv[0];
  return true;
}

bool ppCloneMinLines(const common::Option *o, char *argv[]) {
  props.cloneMinLines = common::str2int(argv[0]);
  return true;
}

bool ppRunMetricHunter(const common::Option *o, char *argv[]) {
  if(strcmp(argv[0], "true") == 0)
    props.runMetricHunter = true;
  else
    props.runMetricHunter = false;
  return true;
}

bool ppRunDCF(const common::Option *o, char *argv[]) {
  if(strcmp(argv[0], "true") == 0)
    props.runDCF = true;
  else
    props.runDCF = false;
  return true;
}

bool ppRunFxCop(const common::Option *o, char *argv[]) {
  if(strcmp(argv[0], "true") == 0)
    props.runFxCop = true;
  else
    props.runFxCop = false;
  return true;
}

bool ppRunMET(const common::Option *o, char *argv[]) {
  if(strcmp(argv[0], "true") == 0)
    props.runLimMetrics = true;
  else
    props.runLimMetrics = false;
  return true;
}

bool ppProfileXML(const common::Option *o, char *argv[]) {
  props.profileXML = argv[0];
  return true;
}

bool ppRulesCSV(const common::Option *o, char *argv[]) {
  props.rulesCSV = argv[0];
  return true;
}

bool ppVerbose(const common::Option *o, char *argv[]) {
  WriteMsg::setMessageLevel(WriteMsg::mlDebug);
  props.verbose = true;
  return true;
}

bool ppConfiguration(const common::Option *o, char *argv[]) {
  props.config = argv[0];
  return true;
}

bool ppPlatform(const common::Option *o, char *argv[]) {
  props.platform = argv[0];
  return true;
}

const Option OPTIONS_OBJ [] = {
  { false,  "-resultsDir",           1, CL_KIND_DIR,      0, OT_WE | OT_WC,     ppResultsDir,            NULL, "Under this directory a new directory with the name of the project will be created (if it doesn't exist yet)."},
  { false,  "-projectName",          1, CL_KIND_STRING,   0, OT_WE | OT_WC,     ppProjectName,           NULL, "This is the name of the project you analyze."},
  { false,  "-input",                1, CL_KIND_FILE,     0, OT_WE | OT_WC,     ppInputFile,             NULL, "The input to analyze. A solution (.sln), project (.csproj), or source (.cs) file."},
  { false,  "-configuration",        1, CL_KIND_STRING,   0, OT_WE | OT_WC,     ppConfiguration,         NULL, "The name of the project configuration." },
  { false,  "-platform",             1, CL_KIND_STRING,   0, OT_WE | OT_WC,     ppPlatform,              NULL, "The name of the target platform." },
  { false,  "-externalHardFilter",   1, CL_KIND_FILE,     0, OT_WE | OT_WC,     ppExternalHardFilter,    NULL, "A filter file containing regular expression lines. See documentation."},
  { false,  "-externalSoftFilter",   1, CL_KIND_FILE,     0, OT_WE | OT_WC,     ppExternalSoftFilter,    NULL, "A filter file containing regular expression lines. See documentation."},
  { false,  "-maximumThreads",       1, CL_KIND_NUMBER,   0, OT_WE | OT_WC,     ppMaxThreads,            NULL, "Sets the maximum number of threads the controller can start if possible. The default value is the number of available CPU cores on the current system."},
  { false,  "-currentDate",          1, CL_KIND_STRING,   0, OT_WE | OT_WC,     ppCurrentDate,           NULL, "The name of the dated directory inside the result directory of the project. If it is not set, then the current date is used."},
  { false,  "-cleanResults",         1, CL_KIND_NUMBER,   0, OT_WE | OT_WC,     ppCleanResults,          NULL, "Cleans all but the last n number of timestamped result directory of the current project."},
  { false,  "-cloneMinLines",        1, CL_KIND_NUMBER,   0, OT_WE | OT_WC,     ppCloneMinLines,         NULL, "This parameter sets the minimum required size of each duplication in lines of code. The default value is 10."},
  { false,  "-cloneGenealogy",       1, CL_KIND_BOOL,     0, OT_WE | OT_WC,     ppCloneGenealogy,        NULL, "This parameter turns on or off the tracking of code clones (copy-pasted source code fragments) through the consecutive revisions of the software system. It is required that during the analysis of the different revisions, the values set to projectName and resultsDir remain the same, so OpenStaticAnalyzer will handle them as different revisions of the same system. Its value can be \"true\" (turn this feature on) or \"false\" (turn this feature off). The default value is \"false\"."},
  { false,  "-csvSeparator",         1, CL_KIND_CHAR,     0, OT_WE | OT_WC,     ppCsvSeparator,          NULL, "This parameter sets the separator character in the CSV outputs."},
  { false,  "-csvDecimalMark",       1, CL_KIND_CHAR,     0, OT_WE | OT_WC,     ppCsvDecimalMark,        NULL, "This parameter sets the decimal mark character in the CSV outputs."},
  { false,  "-FxCopPath",            1, CL_KIND_DIR,      0, OT_WE | OT_WC,     ppFxCopPath,             NULL, "Specify the the directory which contains the FxCop binaries. If not provided, the program will search through the installed Visual Studio directories and use the latest one if found."},
  { false,  "-runMetricHunter",      1, CL_KIND_BOOL,     0, OT_WE | OT_WC,     ppRunMetricHunter,       NULL, "This parameter turns on or off the MetricHunter module. With this feature, OpenStaticAnalyzer lists metric threshold violations. Its value can be \"true\" (turn this feature on) or \"false\" (turn this feature off). The default value is \"true\""},
  { false,  "-runDCF",               1, CL_KIND_BOOL,     0, OT_WE | OT_WC,     ppRunDCF,                NULL, "This parameter turns on or off the DuplicatedCodeFinder module. With this feature, OpenStaticAnalyzer identifies copy-pasted code fragments. Its value can be \"true\" (turn this feature on) or \"false\" (turn this feature off). The default value is \"true\""},
  { false,  "-runMET",               1, CL_KIND_BOOL,     0, OT_WE | OT_WC,     ppRunMET,                NULL, "This parameter turns on or off the Metric module. With this feature, OpenStaticAnalyzer computes source code metrics. Its value can be \"true\" (turn this feature on) or \"false\" (turn this feature off). The default value is \"true\""},
  { false,  "-runFxCop",             1, CL_KIND_BOOL,     0, OT_WE | OT_WC,     ppRunFxCop,              NULL, "This parameter turns on or off the FxCop analysis. FxCop is a tool developed by Microsoft, and it provides several coding rule violation checks. Find out more in the User's Guide. The default value is \"true\""},
  { false,  "-profileXML",           1, CL_KIND_FILE,     0, OT_WE | OT_WC,     ppProfileXML,            NULL, "Global configuration file for OpenStaticAnalyzer. Its 'tool-options' tag can be used to override the default metric thresholds for the MetricHunter tool. Furthermore, its 'rule-options' tag can enable/disable or modify the priorities of multiple rules."},
  { false,  "-rulesCSV",             1, CL_KIND_FILE,     0, OT_WE | OT_WC,     ppRulesCSV,              NULL, "There are certain rule violations that are computed by more than one tool. E.g. ADLIBDC (Avoid Decimal Literals In BigDecimal Constructor) is checked by both FindBugs and PMD. In these cases, in order to avoid duplications, there is a priority order among the tools. This parameter can be used to override these default priorizations by specifying a .csv file."},
  CL_VERBOSE
  CL_MESSAGELEVEL
  CL_HELP
  CL_VERSION
  CL_LAST
};

#define DUMP_PROPERTY_PATH(name) WriteMsg::write(WriteMsg::mlDebug, "  " #name "=[%s]\n", props.name.string().c_str())
#define DUMP_PROPERTY_STRING(name) WriteMsg::write(WriteMsg::mlDebug, "  " #name "=[%s]\n", props.name.c_str())
#define DUMP_PROPERTY_INT(name) WriteMsg::write(WriteMsg::mlDebug, "  " #name "=%d\n", props.name)
#define DUMP_PROPERTY_CHAR(name) WriteMsg::write(WriteMsg::mlDebug, "  " #name "=%c\n", props.name)

void dumpProperties() {
  DUMP_PROPERTY_PATH(startCurrentDir);
  DUMP_PROPERTY_PATH(toolchainDir);
  DUMP_PROPERTY_PATH(toolsDir);
  DUMP_PROPERTY_PATH(resultsDir);
  DUMP_PROPERTY_PATH(currentDate);
  DUMP_PROPERTY_PATH(projectResultDir);
  DUMP_PROPERTY_PATH(projectTimedResultDir);
  DUMP_PROPERTY_PATH(logDir);
  DUMP_PROPERTY_PATH(tempDir);
  DUMP_PROPERTY_PATH(asgDir);
  DUMP_PROPERTY_PATH(externalHardFilter);
  DUMP_PROPERTY_PATH(externalSoftFilter);
  DUMP_PROPERTY_STRING(projectName);
  DUMP_PROPERTY_INT(cloneGenealogy);
  DUMP_PROPERTY_INT(maxThreads);
  DUMP_PROPERTY_CHAR(csvSeparator);
  DUMP_PROPERTY_CHAR(csvDecimalmark);
  DUMP_PROPERTY_PATH(profileXML);
  DUMP_PROPERTY_PATH(rulesCSV);
  DUMP_PROPERTY_INT(runLimMetrics);
  DUMP_PROPERTY_INT(runDCF);
  DUMP_PROPERTY_INT(runFxCop);
  DUMP_PROPERTY_INT(runMetricHunter);
  DUMP_PROPERTY_INT(cloneMinLines);
  DUMP_PROPERTY_STRING(config);
  DUMP_PROPERTY_STRING(platform);
}

bool checkIfBinaryInPackage(const string& toolName) {
  return exists(props.toolsDir / (toolName + BINARYEXT));
}


void checkUserProperties()
{
  if(props.resultsDir.empty())
  {
    WriteMsg::write(WriteMsg::mlError, "Please set the resultsDir parameter. Under this directory a new directory with the name of the analyzed project will be created, if it does not exist yet. All results will be stored there under separate directories with their names containing the date and time.\n");
    clError();
  }

  if(props.projectName.empty())
  {
    WriteMsg::write(WriteMsg::mlError, "Please set the projectName parameter to the name of the analyzed software system.\n");
    clError();
  }

  if(props.inputFile.empty())
  {
    WriteMsg::write(WriteMsg::mlError, "Please set the input parameter. A solution (.sln), project (.csproj) or single source file (.cs) must be given.\n");
    clError();
  }

  if (props.config.empty() || props.platform.empty())
  {
    WriteMsg::write(WriteMsg::mlError, "Please set the platform and configuration parameters.\n");
    clError();
  }

  props.resultsDir = system_complete(props.resultsDir);
  props.inputFile = canonical(props.inputFile).make_preferred();

  if (props.currentDate.empty())
    props.currentDate = common::getCurrentTimeAndDate("%Y-%m-%d-%H-%M-%S"); // pattern="yyyy-MM-dd_HH-mm-ss"

  props.projectResultDir = props.resultsDir / props.projectName / "csharp";
  props.projectTimedResultDir =  props.projectResultDir / props.currentDate;

  const path smDir = "openstaticanalyzer";

  props.logDir =  props.projectTimedResultDir / smDir / "log";
  props.tempDir = props.projectTimedResultDir / smDir / "temp";
  props.asgDir = props.projectTimedResultDir / smDir / "asg";
  props.graphDir = props.projectTimedResultDir / smDir / "graph";

  if ( !props.externalHardFilter.empty() )
    props.externalHardFilter = system_complete(props.externalHardFilter);
  if ( !props.externalSoftFilter.empty() )
    props.externalSoftFilter = system_complete(props.externalSoftFilter);

  if (props.maxThreads == 0)
    props.maxThreads = columbus::thread::ThreadPool::getNumberOfCores();

  if (props.cleanResults < -1)
    props.cleanResults = -1;


  if (props.rulesCSV.empty())
    props.rulesCSV = props.toolsDir / "rules_csharp.csv";


  props.lcssiList = props.tempDir / "lcssi.list";

  props.fxcopOutPath = props.tempDir / "FxCopOut";

  props.runFxCop = props.runFxCop && checkIfBinaryInPackage("FxCop2Graph");
  props.runLimMetrics = props.runLimMetrics && checkIfBinaryInPackage("LIM2Metrics");
  props.runDCF = props.runDCF && checkIfBinaryInPackage("DuplicatedCodeFinder");
  props.runMetricHunter = props.runMetricHunter && checkIfBinaryInPackage("MetricHunter");
}


void initializeProperties() {
  props.startCurrentDir = current_path();

  char* baseDir = std::getenv("CODE_ANALIZER_BASE_DIR");
  if ( baseDir ) {
    props.toolchainDir = path(baseDir);
  } else {
    props.toolchainDir = path(common::getExecutableProgramDir());
  }

#ifdef _WIN32
  string platform = "Windows";
#else
  string platform = "Linux";
#endif

  props.toolsDir = props.toolchainDir / (platform + "Tools");
}

void makedirs()
{
  boost::system::error_code errorcode;
  remove_all(props.projectTimedResultDir, errorcode);
  if(errorcode.value() != boost::system::errc::success){
    WriteMsg::write(WriteMsg::mlError, CMSG_ERROR_DELETE_DIR, props.projectTimedResultDir.string().c_str(), errorcode.message().c_str());
    exit(EXIT_FAILURE);
  }
  if(!create_directories(props.projectTimedResultDir)){
    WriteMsg::write(WriteMsg::mlError, CMSG_ERROR_CREATE_DIR, props.projectTimedResultDir.string().c_str());
    exit(EXIT_FAILURE);
  }
  if(!create_directories(props.logDir)){
    WriteMsg::write(WriteMsg::mlError, CMSG_ERROR_CREATE_DIR, props.logDir.string().c_str());
    exit(EXIT_FAILURE);
  }
  if(!create_directories(props.tempDir)){
    WriteMsg::write(WriteMsg::mlError, CMSG_ERROR_CREATE_DIR, props.tempDir.string().c_str());
    exit(EXIT_FAILURE);
  }
  if(!create_directories(props.asgDir)){
    WriteMsg::write(WriteMsg::mlError, CMSG_ERROR_CREATE_DIR, props.asgDir.string().c_str());
    exit(EXIT_FAILURE);
  }
  if(!create_directories(props.graphDir)){
    WriteMsg::write(WriteMsg::mlError, CMSG_ERROR_CREATE_DIR, props.graphDir.string().c_str());
    exit(EXIT_FAILURE);
  }
}

void logEnvironment()
{
  ofstream envlog;
  envlog.open((props.logDir / "environment.txt").string().c_str());
  vector<string> variables;

  common::getEnvironmentVariables(variables);

  for(vector<string>::iterator it = variables.begin(); it != variables.end(); ++it){
    envlog << *it <<endl;
  }
  envlog.close();
}

int runAnalyzeMode()
{
  Controller ctrl(props);

  ctrl.addTask(new SolutionAnalysisTask(props));


  ctrl.addTask(new ProfileTask(props));

  list<string> inactives;

  if (props.runFxCop)
    ctrl.addTask(new FxCop2GraphTask(props));
  else
    inactives.push_back("FxCop2Graph");

  if (props.runLimMetrics)
    ctrl.addTask(new Lim2metricsTask(props));
  else
    inactives.push_back("LIM2Metrics");

  if (props.runDCF)
    ctrl.addTask(new DcfTask(props));
  else
    inactives.push_back("DuplicatedCodeFinder");

  ctrl.addTask(new GraphMergeTask(props));

  if (props.runMetricHunter)
    ctrl.addTask(new MetricHunterTask(props));
  else
    inactives.push_back("MetricHunter");

  ctrl.addTask(new GraphDumpTask(props));

  if (props.cleanResults != -1)
    ctrl.addTask(new CleanResultsTask(props));

  return ctrl.executeTasks(Controller::EM_FAIL_ON_ANY_ERROR);
}


int main(int argc, char* argv[])
{
  int ret = 0;
  MAIN_BEGIN

    WriteMsg::setAutomaticFlush(true);

    MainInit(argc, argv, "-");

    initializeProperties();

    checkUserProperties();
    dumpProperties();

    makedirs();
    logEnvironment();

    ret = runAnalyzeMode();

  MAIN_END

  return ret;
}

