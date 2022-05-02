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
#include <Environment.h>

#include "../inc/messages.h"
#include "../inc/Properties.h"
#include "../inc/Task.h"
#include <controller/inc/Controller.h>

#define PROGRAM_NAME "Analyzer for Python"
#define EXECUTABLE_NAME "AnalyzerPython"

#include "MainCommon.h"

using namespace std;
using namespace common;
using namespace boost::filesystem;
using namespace columbus::controller;

Properties props;

static void ppFile(char *str) {

}

bool ppProjectBaseDir(const common::Option *o, char *argv[]) {
  props.projectBaseDir = argv[0];
  return true;
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

bool ppCloneMinLines(const common::Option *o, char *argv[]) {
  props.cloneMinLines = common::str2int(argv[0]);
  return true;
}

bool ppCsvSeparator(const common::Option *o, char *argv[]) {
  if (strcmp(argv[0], "\\t") == 0)
    props.csvSeparator = '\t';
  else if (argv[0] != 0)
    props.csvSeparator = argv[0][0];
  return true;
}

bool ppCsvDecimalMark(const common::Option *o, char *argv[]) {
  if (argv[0][0] != 0)
    props.csvDecimalmark = argv[0][0];
  return true;
}

bool ppPythonBinary(const common::Option *o, char *argv[]) {
  props.pythonBinary = argv[0];
  return true;
}

bool ppPythonVersion(const common::Option *o, char *argv[]) {
  props.pythonVersion = argv[0];
  return true;
}

bool ppPylintOptions(const common::Option *o, char *argv[]) {
  props.pylintOptions.push_back(argv[0]);
  return true;
}

bool ppCloneGenealogy (const common::Option *o, char *argv[]) {
  if(strcmp(argv[0], "true") == 0)
    props.cloneGenealogy = true;
  else
    props.cloneGenealogy = false;
  return true;
}

bool ppRunMetricHunter (const common::Option *o, char *argv[]) {
  if(strcmp(argv[0], "true") == 0)
    props.runMetricHunter = true;
  else
    props.runMetricHunter = false;
   return true;
}

bool  ppPylint(const common::Option *o, char *argv[]) {
  if(strcmp(argv[0], "true") == 0)
    props.runPylint = true;
  else
    props.runPylint = false;
   return true;
}

bool  ppRunDCF(const common::Option *o, char *argv[]) {
  if(strcmp(argv[0], "true") == 0)
    props.runDCF = true;
  else
    props.runDCF = false;
   return true;
}

bool  ppRunMET(const common::Option *o, char *argv[]) {
  if(strcmp(argv[0], "true") == 0)
    props.runLim2Metric = true;
  else
    props.runLim2Metric = false;
  return true;
}

bool ppRunUDM(const common::Option *o, char *argv[]) {
  props.runUDMExplicit = true;
  if (strcmp(argv[0], "true") == 0)
    props.runUDM = true;
  else
    props.runUDM = false;
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

CL_PPSARIFSEVERITY

bool ppRunSonar2Graph(const common::Option *o, char *argv[]) {
  props.runSonar2Graph = argv[0];
  return true;
}

bool ppHost(const common::Option *o, char *argv[]) {
  props.host = argv[0];
  return true;
}

bool ppPort(const common::Option *o, char *argv[]) {
  props.port = argv[0];
  return true;
}

bool ppProjectKey(const common::Option *o, char *argv[]) {
  props.projectKey = argv[0];
  return true;
}

bool ppProjectPrefix(const common::Option *o, char *argv[]) {
  props.projectPrefix = argv[0];
  return true;
}

bool ppJsonPath(const common::Option *o, char *argv[]) {
  props.jsonPath = argv[0];
  return true;
}

bool ppSqUsername(const common::Option *o, char *argv[]) {
  props.sqUsername = argv[0];
  return true;
}

bool ppSqPassword(const common::Option *o, char *argv[]) {
  props.sqPassword = argv[0];
  return true;
}

bool ppLanguageKey(const common::Option *o, char *argv[]) {
  props.languageKey = argv[0];
  return true;
}

bool ppStrict(const common::Option *o, char *argv[]) {
  if(strcmp(argv[0], "true") == 0)
    props.strict = true;
  else
    props.strict = false;
  return true;
}

// LIM2Patterns start::
bool ppRunLIM2Patterns(const common::Option *o, char *argv[]) {
  if (strcmp(argv[0], "true") == 0)
    props.runLIM2Patterns = true;
  else
    props.runLIM2Patterns = false;
  return true;
}

static bool ppGetPattern(const Option *o, char *argv[]) {
  props.patternFile = argv[0];
  return true;
}
// LIM2Patterns end::


const Option OPTIONS_OBJ [] = {
  { false,  "-projectBaseDir",       1, CL_KIND_DIR,      1, OT_WE | OT_WC,     ppProjectBaseDir,        NULL, "Directory of the source code to be analyzed specified with relative or absolute path."},
  { false,  "-resultsDir",           1, CL_KIND_DIR,      2, OT_WE | OT_WC,     ppResultsDir,            NULL, "Relative or absolute path name of the directory where the results of the analysis will be stored. The directory will be created automatically if it does not exist."},
  { false,  "-projectName",          1, CL_KIND_STRING,   3, OT_WE | OT_WC,     ppProjectName,           NULL, "The name of the analyzed software system. The name specified here will be used for storing the results."},
  { false,  "-externalHardFilter",   1, CL_KIND_FILE,     0, OT_WE | OT_WC,     ppExternalHardFilter,    NULL, "Filter file specified with relative or absolute path, to filter out certain files from the analysis based on their path names. Filtered files will not appear in the results. The filter file is a simple text file containing lines starting with '+' or '-' characters followed by a regular expression. During the analysis, each input file will be checked for these expressions. If the first character of the last matching expression is '-', then the given file will be excluded from the analysis. If the first character of the last matching expression is '+', or there is no matching expression, then the file will be analyzed. A line starting with a different character than '-' or '+' will be ignored."},
  { false,  "-cloneGenealogy",       1, CL_KIND_BOOL,     0, OT_WE | OT_WC,     ppCloneGenealogy,        NULL, "This parameter turns on or off the tracking of code clones (copy-pasted source code fragments) through the consecutive revisions of the software system. It is required that during the analysis of the different revisions, the values set to projectName and resultsDir remain the same, so OpenStaticAnalyzer will handle them as different revisions of the same system. Its value can be \"true\" (turn this feature on) or \"false\" (turn this feature off). The default value is \"false\"."},
  { false,  "-cloneMinLines",        1, CL_KIND_NUMBER,   0, OT_WE | OT_WC,     ppCloneMinLines,         NULL, "This parameter sets the minimum required size of each duplication in lines of code. The default value is 10."},
  { false,  "-csvSeparator",         1, CL_KIND_CHAR,     0, OT_WE | OT_WC,     ppCsvSeparator,          NULL, "This parameter sets the separator character in the CSV outputs. The default value is the comma (\",\"). The character set here must be placed in quotation marks (e.g. -csvSeparator=\";\"). Tabulator character can be set by the special \"\\t\" value."},
  { false,  "-csvDecimalMark",       1, CL_KIND_CHAR,     0, OT_WE | OT_WC,     ppCsvDecimalMark,        NULL, "This parameter sets the decimal mark character in the CSV outputs. The default is value is the dot (\".\"). The character set here must be placed in quotation marks (e.g. -csvDecimalMark=\",\")."},
  { false,  "-currentDate",          1, CL_KIND_STRING,   0, OT_WE | OT_WC,     ppCurrentDate,           NULL, "The name of the directory with date inside the result directory of the project. If it is not set, then the current date is used."},
  { false,  "-maximumThreads",       1, CL_KIND_NUMBER,   0, OT_WE | OT_WC,     ppMaxThreads,            NULL, "This parameter sets the maximum number of parallel tasks the controller can start. The default value is the number of available CPU cores on the current system."},
  { false,  "-pythonBinary",         1, CL_KIND_FILE,     5, OT_WE | OT_WC,     ppPythonBinary,          NULL, "Sets Python 2.7/3.x binary executable name (full path is required if its directory is not in PATH)."},
  { false,  "-pythonVersion",        1, CL_KIND_STRING,   4, OT_WE | OT_WC,     ppPythonVersion,         NULL, "This parameter sets the Python version (2 or 3)." },
  { false,  "-pylintOptions",        1, CL_KIND_STRING,   0, OT_WE | OT_WC,     ppPylintOptions,         NULL, "Passes command line options to Pylint. Options with arguments can be passed with successive -pylintOptions options."},
  { false,  "-cleanResults",         1, CL_KIND_NUMBER,   0, OT_WE | OT_WC,     ppCleanResults,          NULL, "Cleans all but the last n number of timestamped result directory of the current project."},
  { false,  "-runMetricHunter",      1, CL_KIND_BOOL,     0, OT_WE | OT_WC,     ppRunMetricHunter,       NULL, "This parameter turns on or off the MetricHunter module. With this feature, OpenStaticAnalyzer lists metric threshold violations. Its value can be \"true\" (turn this feature on) or \"false\" (turn this feature off). The default value is \"true\""},
  { false,  "-runPylint",            1, CL_KIND_BOOL,     0, OT_WE | OT_WC,     ppPylint,                NULL, "This parameter turns on or off the Pylint coding rule violation checking. With this feature, OpenStaticAnalyzer lists coding rule violations detected by Pylint. Its value can be \"true\" (turn this feature on) or \"false\" (turn this feature off). The default value is \"true\"."},
  { false,  "-runDCF",               1, CL_KIND_BOOL,     0, OT_WE | OT_WC,     ppRunDCF,                NULL, "This parameter turns on or off the DuplicatedCodeFinder module. With this feature, OpenStaticAnalyzer identifies copy-pasted code fragments. Its value can be \"true\" (turn this feature on) or \"false\" (turn this feature off). The default value is \"true\""},
  { false,  "-runMET",               1, CL_KIND_BOOL,     0, OT_WE | OT_WC,     ppRunMET,                NULL, "This parameter turns on or off the Metric module. With this feature, OpenStaticAnalyzer computes source code metrics. Its value can be \"true\" (turn this feature on) or \"false\" (turn this feature off). The default value is \"true\""},
  { false,  "-profileXML",           1, CL_KIND_FILE,     0, OT_WE | OT_WC,     ppProfileXML,            NULL, "Global configuration file for OpenStaticAnalyzer. Its 'tool-options' tag can be used to override the default metric thresholds for the MetricHunter tool. Furthermore, its 'rule-options' tag can enable/disable or modify the priorities of multiple rules."},
  { false,  "-rulesCSV",             1, CL_KIND_FILE,     0, OT_WE | OT_WC,     ppRulesCSV,              NULL, "There are certain rule violations that are computed by more than one tool. E.g. OSC (Old Style Class) is checked by both Pylint and FaultHunter. In these cases, in order to avoid duplications, there is a priority order among the tools. This parameter can be used to override these default priorizations by specifying a .csv file."},
  { false,  "-runLIM2Patterns",      1, CL_KIND_BOOL,     0, OT_WE | OT_WC,     ppRunLIM2Patterns,       NULL, "Run LIM2Patterns." },
  CL_SONAR2GRAPH_RUN
  CL_SONAR2GRAPH_ARGS
  CL_UDM_OPTIONS
  CL_SARIFSEVERITY
  CL_LIM2PATTERNS
  CL_MESSAGELEVEL
  CL_HELP
  CL_VERSION
  CL_LAST
};

#define DUMP_PROPERTY_PATH(name) WriteMsg::write(WriteMsg::mlDebug, "  " #name "=[%s]\n", props.name.string().c_str())
#define DUMP_PROPERTY_STRING(name) WriteMsg::write(WriteMsg::mlDebug, "  " #name "=[%s]\n", props.name.c_str())
#define DUMP_PROPERTY_INT(name) WriteMsg::write(WriteMsg::mlDebug, "  " #name "=%d\n", props.name)
#define DUMP_PROPERTY_CHAR(name) WriteMsg::write(WriteMsg::mlDebug, "  " #name "=%c\n", props.name)
#define DUMP_PROPERTY_STRING_LIST(name) { string val; for (const string& s : props.name) val += "[" + s + "]"; WriteMsg::write(WriteMsg::mlDebug, "  " #name "=[%s]\n", val.c_str()); }

void dumpProperties() {
  DUMP_PROPERTY_PATH(startCurrentDir);
  DUMP_PROPERTY_PATH(toolchainDir);
  DUMP_PROPERTY_PATH(toolsDir);
  DUMP_PROPERTY_PATH(resultsDir);
  DUMP_PROPERTY_PATH(projectBaseDir);
  DUMP_PROPERTY_PATH(currentDate);
  DUMP_PROPERTY_PATH(projectResultDir);
  DUMP_PROPERTY_PATH(projectTimedResultDir);
  DUMP_PROPERTY_PATH(logDir);
  DUMP_PROPERTY_PATH(tempDir);
  DUMP_PROPERTY_PATH(asgDir);
  DUMP_PROPERTY_PATH(externalHardFilter);
  DUMP_PROPERTY_STRING(projectName);
  DUMP_PROPERTY_INT(cloneGenealogy);
  DUMP_PROPERTY_INT(maxThreads);
  DUMP_PROPERTY_CHAR(csvSeparator);
  DUMP_PROPERTY_CHAR(csvDecimalmark);
  DUMP_PROPERTY_INT(cloneMinLines);
  DUMP_PROPERTY_INT(cleanResults);
  DUMP_PROPERTY_PATH(pythonBinary);
  DUMP_PROPERTY_STRING(pythonVersion);
  DUMP_PROPERTY_STRING_LIST(pylintOptions);
  DUMP_PROPERTY_PATH(profileXML);
  DUMP_PROPERTY_PATH(rulesCSV);
  DUMP_PROPERTY_INT(runDCF);
  DUMP_PROPERTY_INT(runPylint);
  DUMP_PROPERTY_INT(runMetricHunter);
  DUMP_PROPERTY_INT(runLim2Metric);
  DUMP_PROPERTY_INT(runUDM);
  DUMP_PROPERTY_INT(runUDMExplicit);
  DUMP_PROPERTY_INT(runLIM2Patterns);
}

bool checkIfBinaryInPackage(const string& toolName) {
  return exists(props.toolsDir / (toolName + BINARYEXT));
}

void checkPython() {
  if (props.pythonVersion.empty()) {
    WriteMsg::write(WriteMsg::mlError, "Please set the python version of the analyzed software. Allowed values are: 2 and 3.\n");
    clError();
  } else if (props.pythonVersion != "2" && props.pythonVersion != "3") {
    WriteMsg::write(WriteMsg::mlError, "Invalid Python version: %s. Allowed values are: 2 and 3. Please set it with the '-pythonVersion' option.\n", props.pythonVersion.c_str());
    clError();
  }

  if (props.pythonBinary.empty()) {
    WriteMsg::write(WriteMsg::mlError, "Please set the python 2.7/3.x binary with '-pythonBinary' option.\n");
    clError();
  }

  string pyBin = props.pythonBinary.string();
  vector<string> sv;
  sv.push_back("--version");
  stringstream ss;
  int ret = common::run(pyBin, sv, ss);
  string outStr = ss.str();

  if (ret != 0) {
    WriteMsg::write(CMSG_PYTHON_BIN_ERROR);
    exit(EXIT_FAILURE);
  }

  {
    static const boost::regex versionRegex("Python (\\d+)\\.(\\d+)");
    boost::smatch match;

    if (boost::regex_search(outStr, match, versionRegex)) {
      string pythonReleaseVersion = match[1].str() + "." + match[2].str();

      if (match[1].str() != props.pythonVersion) {
        WriteMsg::write(WriteMsg::mlError, "The specified python version (%s) is not compatible with the python executable (%s).\n", props.pythonVersion.c_str(), pythonReleaseVersion.c_str());
        exit(EXIT_FAILURE);
      }

      int pyMajor = common::str2int(match[1].str());
      int pyMinor = common::str2int(match[2].str());

      if (!((pyMajor == 2 && pyMinor == 7) || pyMajor == 3)) {
        WriteMsg::write(WriteMsg::mlError, "Required minimum python versions are 2.7 and 3.x.\n");
        exit(EXIT_FAILURE);
      }
    }
  }
}

void checkPylint() {
  static const string OSA_PYLINT_1_VERSION = "1.9.4";
  static const string OSA_PYLINT_2_VERSION = "2.3.1";

  char* pythonPathEnv = NULL;

  char* columbusPythonLibPath = props.pythonVersion == "2" ? getenv("COLUMBUS_PYTHON2_LIB_PATH") : getenv("COLUMBUS_PYTHON3_LIB_PATH");
  if (columbusPythonLibPath != NULL) {
    string pythonPath = string(columbusPythonLibPath);

    pythonPathEnv = getenv("PYTHONPATH");
    if (pythonPathEnv != NULL) {
      pythonPath += PATH_SEPARATOR + string(pythonPathEnv);
    }

    if (common::setEnvironmentVariable("PYTHONPATH", pythonPath.c_str()) != 0) {
      WriteMsg::write(WriteMsg::mlError, CMSG_ERROR_ENVSET_FAILURE, "PYTHONPATH");
      exit(EXIT_FAILURE);
    }
  }

  vector<string> sv;
  sv.push_back("-c");
  sv.push_back("import pylint; print(pylint.__version__);");
  stringstream ss;

  int ret = common::run(props.pythonBinary.string(), sv, ss);
  if (ret != 0) {
    WriteMsg::write(WriteMsg::mlWarning, "Warning: Failed to retrieve version of Pylint. The Pylint checker will not be executed.\n");
    props.runPylint = false;
  }

  if (!pythonPathEnv) {
    if (common::unsetEnvironmentVariable("PYTHONPATH") != 0) {
      WriteMsg::write(WriteMsg::mlError, CMSG_ERROR_ENVSET_FAILURE, "PYTHONPATH");
      exit(EXIT_FAILURE);
    }
  }

  if (!props.runPylint)
    return;

  string ver = ss.str();
  common::trim(ver);

  if (props.pythonVersion == "2") {
    if (ver.compare(0, 3, "1.8") != 0 && ver.compare(0, 3, "1.9") != 0) {
      WriteMsg::write(WriteMsg::mlWarning, "Warning: Required Pylint version for analyzing Python 2.7 projects is Pylint 1.8.x or 1.9.x, found %s. The Pylint checker will not be executed.\n", ver.c_str());
      props.runPylint = false;
    } else {
      if (ver != OSA_PYLINT_1_VERSION)
        WriteMsg::write(WriteMsg::mlWarning, "Warning: Expected version of Pylint is %s, found %s. Pylint results may be incomplete or incorrect.\n", OSA_PYLINT_1_VERSION.c_str(), ver.c_str());
    }
  } else {
    if (ver.compare(0, 1, "2") != 0) {
      WriteMsg::write(WriteMsg::mlWarning, "Warning: Required Pylint version for analyzing Python 3.x projects is Pylint 2.x, found %s. The Pylint checker will not be executed.\n", ver.c_str());
      props.runPylint = false;
    } else {
      if (ver != OSA_PYLINT_2_VERSION)
        WriteMsg::write(WriteMsg::mlWarning, "Warning: Expected version of Pylint is %s, found %s. Pylint results may be incomplete or incorrect.\n", OSA_PYLINT_2_VERSION.c_str(), ver.c_str());
    }
  }
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

  if(props.projectBaseDir.empty())
  {
    WriteMsg::write(WriteMsg::mlError, "Please set the projectBaseDir parameter. This is the directory that contains the source files you analyze.\n");
    clError();
  }

  if (!boost::filesystem::exists(props.projectBaseDir))
  {
    WriteMsg::write(WriteMsg::mlError, "The directory given in the projectBaseDir parameter does not exist.\n");
    clError();
  }

  if (!is_directory(props.projectBaseDir))
  {
    WriteMsg::write(WriteMsg::mlError, "The projectBaseDir parameter must be a directory.\n");
    clError();
  }

  checkPython();

  if (props.runPylint)
    checkPylint();

  props.resultsDir = system_complete(props.resultsDir);
  props.projectBaseDir = canonical(props.projectBaseDir).make_preferred();

  if (props.currentDate.empty())
    props.currentDate = common::getCurrentTimeAndDate("%Y-%m-%d-%H-%M-%S"); // pattern="yyyy-MM-dd-HH-mm-ss"

  props.projectResultDir = props.resultsDir / props.projectName / "python";
  props.projectTimedResultDir =  props.projectResultDir / props.currentDate;

  const path osaDir = "analyzer";

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
    props.rulesCSV = props.toolsDir / "rules_python.csv";

  props.runPylint = props.runPylint && checkIfBinaryInPackage("Pylint2Graph");
  props.runLim2Metric = props.runLim2Metric && checkIfBinaryInPackage("LIM2Metrics");
  props.runDCF = props.runDCF && checkIfBinaryInPackage("DuplicatedCodeFinder");
  props.runMetricHunter = props.runMetricHunter && checkIfBinaryInPackage("MetricHunter");
  props.runLIM2Patterns = props.runLIM2Patterns && exists(props.commonDir / ("LIM2Patterns" BINARYEXT));
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


  props.cloneGenealogy = false;

  props.toolsDir = props.toolchainDir / "Tools";
  props.commonDir = props.toolchainDir / ".." / "Common";

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

int runAnalyzeMode()
{
  columbus::thread::ThreadPool threadPool(props.maxThreads);
  Controller ctrl(props, threadPool);
  list<string> inactives;

  ctrl.addTask(new PANTask(props));
  ctrl.addTask(new PAN2LimTask(props));
  ctrl.addTask(new ProfileTask(props));

  // skipping UDM can only be decided here if it's explicit on the command line
  // otherwise, we run it, and it exits, if there was nothing to do according to the profile
  if (!props.runUDMExplicit || props.runUDM)
    ctrl.addTask(new UserDefinedMetricsTask(inactives, props));
  else
    inactives.push_back("UserDefinedMetrics");

  if (props.runLim2Metric)
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

  if (props.runPylint) {
    ctrl.addTask(new PylintTask(props));
    ctrl.addTask(new Pylint2GraphTask(props));
  } else
    inactives.push_back("Pylint2Graph");

  ctrl.addTask(new GraphMergeTask(props));

  ctrl.addTask(new GraphDumpTask(props));

  if (props.runLIM2Patterns)
      ctrl.addTask(new LIM2PatternsTask(props));
  else
      inactives.push_back("LIM2Patterns");

  if (props.cleanResults != -1)
    ctrl.addTask(new CleanResultsTask(props));

  if (props.runSonar2Graph) {
    ctrl.addTask(new Sonar2GraphTask(props));
  }

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
    logEnvironment(props);
    logCommandLineArguments(props, argc, argv);


    ret = runAnalyzeMode();

  MAIN_END

  return ret;
}

