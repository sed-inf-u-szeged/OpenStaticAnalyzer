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


#include <time.h>
#include <fstream>
#include <common/inc/FileSup.h>
#include <common/inc/StringSup.h>
#include <common/inc/WriteMessage.h>
#include <common/inc/PlatformDependentDefines.h>
#include <threadpool/inc/ThreadPool.h>
#include <boost/filesystem.hpp>
#include <boost/regex.hpp>

#include "../inc/messages.h"
#include "../inc/Properties.h"
#include "../inc/Task.h"
#include <controller/inc/Controller.h>

#define PROGRAM_NAME "OpenStaticAnalyzer for JavaScript"
#define EXECUTABLE_NAME "OpenStaticAnalyzerJavaScript"

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

bool ppExternalHardFilter(const common::Option *o, char *argv[]) {
  props.externalHardFilter = argv[0];
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

bool ppCleanProject(const common::Option *o, char *argv[]) {
  if(strcmp(argv[0], "true") == 0)
    props.cleanProject = true;
  else
    props.cleanProject = false;
  return true;
}

bool ppBaseDir(const common::Option *o, char *argv[]) {
  props.projectBaseDir = argv[0];
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

bool ppCloneMinLines(const common::Option *o, char *argv[]) {
  props.cloneMinLines = common::str2int(argv[0]);
  return true;
}


bool ppRunDCF(const common::Option *o, char *argv[]) {
  if(strcmp(argv[0], "true") == 0)
    props.runDCF = true;
  else
    props.runDCF = false;
  return true;
}

bool ppRunMET(const common::Option *o, char *argv[]) {
  if(strcmp(argv[0], "true") == 0)
    props.runLimMetrics = true;
  else
    props.runLimMetrics = false;
  return true;
}

bool ppRunMetricHunter(const common::Option *o, char *argv[]) {
  if (strcmp(argv[0], "true") == 0)
    props.runMetricHunter = true;
  else
    props.runMetricHunter = false;
  return true;
}

bool ppNodeOptions(const common::Option *o, char *argv[]) {
  props.nodeOptions = argv[0];
  return true;
}

bool ppVerbose(const common::Option *o, char *argv[]) {
  WriteMsg::setMessageLevel(WriteMsg::mlDebug);
  props.verbose = true;
  return true;
}


bool ppRunESLint(const common::Option *o, char *argv[]) {
  if(strcmp(argv[0], "true") == 0)
    props.runESLint = true;
  else
    props.runESLint = false;
  return true;
}

bool ppJSANOptions(const common::Option *o, char *argv[]) {
  props.JSANOptions = argv[0];
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

const Option OPTIONS_OBJ [] = {  
  { false,  "-resultsDir",            1, CL_KIND_DIR,     0, OT_WE | OT_WC,     ppResultsDir,             NULL, "Relative or absolute path name of the directory where the results of the analysis will be stored. The directory will be created automatically if it does not exist."},
  { false,  "-projectName",           1, CL_KIND_STRING,  0, OT_WE | OT_WC,     ppProjectName,            NULL, "The name of the analyzed software system. The name specified here will be used for storing the results."},
  { false,  "-externalHardFilter",    1, CL_KIND_FILE,    0, OT_WE | OT_WC,     ppExternalHardFilter,     NULL, "Filter file specified with relative or absolute path, to filter out certain files from the analysis based on their path names. Filtered files will not appear in the results. The filter file is a simple text file containing lines starting with '+' or '-' characters followed by a regular expression. During the analysis, each input file will be checked for these expressions. If the first character of the last matching expression is '-', then the given file will be excluded from the analysis. If the first character of the last matching expression is '+', or there is no matching expression, then the file will be analyzed. A line starting with a different character than '-' or '+' will be ignored."},
  { false,  "-nodeOptions",           1, CL_KIND_STRING,  0, OT_WE | OT_WC,     ppNodeOptions,            NULL, "Extra parameters can be added for the NodeJS used by OpenStaticAnalyzer. For instance the maximum heap memory of the v8 (used by Node) can be set manually if the default value is not enough." },

  { false,  "-maximumThreads",        1, CL_KIND_NUMBER,  0, OT_WE | OT_WC,     ppMaxThreads,             NULL, "This parameter sets the maximum number of parallel tasks the controller can start. The default value is the number of available CPU cores on the current system."},
  { false,  "-currentDate",           1, CL_KIND_STRING,  0, OT_WE | OT_WC,     ppCurrentDate,            NULL, "The name of the directory with date inside the result directory of the project. If it is not set, then the current date is used."},
  { false,  "-cleanResults",          1, CL_KIND_NUMBER,  0, OT_WE | OT_WC,     ppCleanResults,           NULL, "Cleans all but the last n number of timestamped result directory of the current project."},
  { false,  "-cleanProject",          1, CL_KIND_BOOL,    0, OT_WE | OT_WC,     ppCleanProject,           NULL, "Removes all files (from the directory set by the projectBaseDir parameter) created during the analysis, but does not remove anything from the results directory (resultsDir). Its value can be \"true\" (turn this feature on, setting projectBaseDir is mandatory in this case) or \"false\" (turn this feature off). The default value is \"false\"."},
  { false,  "-projectBaseDir",        1, CL_KIND_DIR,     0, OT_WE | OT_WC,     ppBaseDir,                NULL, "Directory of the source code to be analyzed specified with relative or absolute path. Using this option the directory analysis mode will be activated. Setting projectBaseDir is mandatory."},
 
  { false,  "-JSANOptions",           1, CL_KIND_STRING,  0, OT_WE | OT_WC,     ppJSANOptions,            NULL, ""}, 

  { false,  "-cloneGenealogy",        1, CL_KIND_BOOL,    0, OT_WE | OT_WC,     ppCloneGenealogy,         NULL, "This parameter turns on or off the tracking of code clones (copy-pasted source code fragments) through the consecutive revisions of the software system. It is required that during the analysis of the different revisions, the values set to projectName and resultsDir remain the same, so OpenStaticAnalyzer will handle them as different revisions of the same system. Its value can be \"true\" (turn this feature on) or \"false\" (turn this feature off). The default value is \"false\"."},
  { false,  "-csvSeparator",          1, CL_KIND_CHAR,    0, OT_WE | OT_WC,     ppCsvSeparator,           NULL, "This parameter sets the separator character in the CSV outputs. The default value is the comma (\",\"). The character set here must be placed in quotation marks (e.g. -csvSeparator=\";\"). Tabulator character can be set by the special \"\\t\" value."},
  { false,  "-csvDecimalMark",        1, CL_KIND_CHAR,    0, OT_WE | OT_WC,     ppCsvDecimalMark,         NULL, "This parameter sets the decimal mark character in the CSV outputs. The default is value is the dot (\".\"). The character set here must be placed in quotation marks (e.g. -csvDecimalMark=\",\")."},
  { false,  "-cloneMinLines",         1, CL_KIND_NUMBER,  0, OT_WE | OT_WC,     ppCloneMinLines,          NULL, "This parameter sets the minimum required size of each duplication in lines of code. The default value is 10."},
  { false,  "-runESLint",             1, CL_KIND_BOOL,    0, OT_WE | OT_WC,     ppRunESLint,              NULL, "This parameter turns on or off the ESLint coding rule violation checking. With this feature, OpenStaticAnalyzer lists coding rule violations detected by ESLint, such as unused variables, empty catch blocks, etc. Its value can be \"true\" (turn this feature on) or \"false\" (turn this feature off). The default value is \"true\"."},
  
  { false,  "-runDCF",                1, CL_KIND_BOOL,    0, OT_WE | OT_WC,     ppRunDCF,                 NULL, "This parameter turns on or off the DulpicatedCodeFinder module. With this feature, OpenStaticAnalyzer lists metric threshold violations. Its value can be \"true\" (turn this feature on) or \"false\" (turn this feature off). The default value is \"true\""},
  { false,  "-runMET",                1, CL_KIND_BOOL,    0, OT_WE | OT_WC,     ppRunMET,                 NULL, "This parameter turns on or off the MetricsCalculator module. With this feature, OpenStaticAnalyzer lists metric threshold violations. Its value can be \"true\" (turn this feature on) or \"false\" (turn this feature off). The default value is \"true\""},
  { false,  "-runMetricHunter",       1, CL_KIND_BOOL,    0, OT_WE | OT_WC,     ppRunMetricHunter,        NULL, "This parameter turns on or off the MetricHunter module. With this feature, OpenStaticAnalyzer lists metric threshold violations. Its value can be \"true\" (turn this feature on) or \"false\" (turn this feature off). The default value is \"true\"" },

  { false,  "-profileXML",            1, CL_KIND_FILE,    0, OT_WE | OT_WC,     ppProfileXML,             NULL, "Global configuration file for OpenStaticAnalyzer. Its tool-options tag can be used to override the default metric thresholds for the MetricHunter tool or define custom metric formulas for the UserDefinedMetrics tool. Furthermore, its rule-options tag can enable/disable or modify the priorities of multiple rules." },
  { true,   "-rulesCSV",              1, CL_KIND_FILE,    0, OT_WE | OT_WC,     ppRulesCSV,               NULL, "Set the rules csv." },
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
  DUMP_PROPERTY_PATH(profileXML);
  DUMP_PROPERTY_STRING(projectName);
  DUMP_PROPERTY_INT(cloneGenealogy);
  DUMP_PROPERTY_INT(maxThreads);
  DUMP_PROPERTY_CHAR(csvSeparator);
  DUMP_PROPERTY_CHAR(csvDecimalmark);
  DUMP_PROPERTY_PATH(projectBaseDir);
  DUMP_PROPERTY_STRING(analysisOutputDir);
  DUMP_PROPERTY_INT(runDCF);
  DUMP_PROPERTY_INT(runLimMetrics);
  DUMP_PROPERTY_INT(runMetricHunter);
  DUMP_PROPERTY_INT(runESLint);
  DUMP_PROPERTY_PATH(rulesCSV);
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

  if(props.cleanProject && props.projectBaseDir.empty())
  {
    WriteMsg::write(WriteMsg::mlError, "Please set the baseDir parameter. This is necessary when the cleanProject is set.\n");
    clError();
  }

  props.resultsDir = system_complete(props.resultsDir);


  if ( !props.projectBaseDir.empty() )
    props.projectBaseDir = canonical(props.projectBaseDir).make_preferred();

  if (props.currentDate.empty())
    props.currentDate = common::getCurrentTimeAndDate("%Y-%m-%d-%H-%M-%S"); // pattern="yyyy-MM-dd-HH-mm-ss"
  
  props.projectResultDir = props.resultsDir / props.projectName / "javascript";
  props.projectTimedResultDir =  props.projectResultDir / props.currentDate;

  const path osaDir = "openstaticanalyzer";
  
  props.logDir =  props.projectTimedResultDir / osaDir / "log";
  props.tempDir = props.projectTimedResultDir / osaDir / "temp";
  props.asgDir = props.projectTimedResultDir / osaDir / "asg";
  props.graphDir = props.projectTimedResultDir / osaDir / "graph";

  if ( !props.externalHardFilter.empty() )
    props.externalHardFilter = system_complete(props.externalHardFilter);
  
  if (props.maxThreads == 0)
    props.maxThreads = columbus::thread::ThreadPool::getNumberOfCores();
  
  if (props.cleanResults < -1)
    props.cleanResults = -1;
  
  if (props.rulesCSV.empty())
      props.rulesCSV = props.toolsDir / "rules_javascript.csv";


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
  
  props.toolsDir = props.toolchainDir / "Tools";

  stringstream outStream;
  string tmpStr;
  boost::smatch result;
  
  outStream.str(string());
  outStream.clear();
  tmpStr.clear();

  tmpStr = outStream.str();
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
  
  if (props.cleanResults != -1)
    ctrl.addTask(new CleanResultsTask(props));

  ctrl.addTask(new JSANTask(props));
  ctrl.addTask(new JSAN2LimTask(props));

  list<string> inactives;

  ctrl.addTask(new ProfileTask(props));

  if (props.runESLint){
    ctrl.addTask(new RunESLintTask(props));
    ctrl.addTask(new ESLint2GraphTask(props));
  }
  else {
    inactives.push_back("ESLint");
  }

  if (props.runLimMetrics)
    ctrl.addTask(new LIM2MetricsTask(props));
  else
    inactives.push_back("LIM2Metrics");

  if (props.runDCF)
    ctrl.addTask(new DcfTask(props));
  else
    inactives.push_back("DuplicatedCodeFinder");

  if (props.runMetricHunter)
    ctrl.addTask(new MetricHunterTask(props));
  else
    inactives.push_back("MetricHunter");

  ctrl.addTask(new AddLicenceTask(inactives, props));
  ctrl.addTask(new GraphMergeTask(props));
  ctrl.addTask(new GraphDumpTask(props));



  if (props.cleanProject)
    ctrl.addTask(new CleanProjectTask(props));

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

