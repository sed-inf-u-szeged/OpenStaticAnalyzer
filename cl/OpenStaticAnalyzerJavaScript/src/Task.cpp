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
#include <string>
#include <sstream>
#include <cstdlib>
#include <cstdarg>

#include <Exception.h>
#include <common/inc/WriteMessage.h>
#include <common/inc/StringSup.h>
#include <common/inc/FileSup.h>
#include <common/inc/PlatformDependentDefines.h>
#include <graph/inc/graph.h>
#include <graphsupport/inc/GraphConstants.h>
#include <controller/inc/ProfileCommon.h>

#include <boost/filesystem/path.hpp>
#include <boost/filesystem.hpp>
#include <boost/filesystem/operations.hpp>
#include <boost/regex.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/make_shared.hpp>

#include "../inc/Task.h"
#include "../inc/messages.h"
#include "../inc/Properties.h"

#define TASK_NAME_DEF(_NAME) const string _NAME::name(#_NAME)
#define TOOL_RUL_CONFIG(_TOOL_NAME) _TOOL_NAME##_rulconfig
#define TOOL_RUL_CONFIG_DEF(_TOOL_NAME, _CONFIG) const string TOOL_RUL_CONFIG(_TOOL_NAME)(#_CONFIG)

using namespace std;
using namespace columbus;
using namespace columbus::controller;
using namespace common;
using namespace boost::filesystem;
using namespace boost;

TASK_NAME_DEF(CleanResultsTask);

Task::ExecutionResult CleanResultsTask::execute()
{
  ExecutionResult result;
  ExecutionLogger logger(this, result);
  try {
    set<path> directoryList;
    directory_iterator end;
    directory_iterator begin(props.projectResultDir);
    for (directory_iterator iter = begin; iter != end; ++iter) {
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
  }
  HANDLE_TASK_EXCEPTIONS

  return result;
}

CleanResultsTask::CleanResultsTask(const Properties& properties)
  : Task(properties)
{
  // there is no dependency
}

TASK_NAME_DEF(CleanProjectTask);

Task::ExecutionResult CleanProjectTask::execute()
{
  ExecutionResult result;
  ExecutionLogger logger(this, result);

  try {

    if (exists(props.projectBaseDir) && is_directory(props.projectBaseDir)) {

      recursive_directory_iterator it(props.projectBaseDir);
      recursive_directory_iterator endit;

      list<path> folderList;

      while (it != endit) {
        if (is_directory(*it) && it->path().filename() == props.analysisOutputDir) {
          folderList.push_back(it->path());
        }
        if (is_directory(*it) && it->path().filename() == "OpenStaticAnalyzer" && it->path().parent_path().filename() == "target") {
          folderList.push_back(it->path());
        }
        ++it;
      }
      for (list<path>::iterator folder = folderList.begin(); folder != folderList.end(); ++folder) {
        logstream << "Removing directory: " << folder->string() << endl;
        remove_all(*folder);
      }
    }
  }
  HANDLE_TASK_EXCEPTIONS
  return result;
}

CleanProjectTask::CleanProjectTask(const Properties& properties)
  : Task(properties)
{
  addDependsOn(JSAN2LimTask::name);
  addDependsOn(GraphDumpTask::name);
}

TASK_NAME_DEF(JSANTask);

Task::ExecutionResult JSANTask::execute()
{
  ExecutionResult result;
  ExecutionLogger logger(this, result);

  try {
    vector<string> sv;

    // -------------------------------------------------------------------------------------------------------------
    // ---------------------------------------------- Run JSAN ------------------------------------------------------
    // -------------------------------------------------------------------------------------------------------------

    sv.clear();

    if (!props.nodeOptions.empty()) {
      sv.push_back(props.nodeOptions);
    }

    const string JSANPath = (props.toolsDir / "node_modules" / "jsan" / "JSAN.js").string();
    sv.push_back(JSANPath);

    vector<string> JSANOptionsV;
    split(props.JSANOptions, JSANOptionsV, ' ');
    sv.insert(sv.end(), JSANOptionsV.begin(), JSANOptionsV.end());
    const string out = (props.asgDir / (props.projectName + ".jssi")).string();

    sv.push_back("-o");
    sv.push_back(out);

    if (!props.externalHardFilter.empty()) {
      if (!exists(props.externalHardFilter.string())) {
        WriteMsg::write(WriteMsg::mlDebug, "Hardfilter file: %s does not exist. Filtering step is left out.", props.externalHardFilter.string().c_str() );
      }
      else {
        sv.push_back("-e");
        sv.push_back(props.externalHardFilter.string());
      }
    }


    const string baseDir = (props.projectBaseDir).string();
    sv.push_back(baseDir);
    checkedExec("node", sv, logger);
  }
  HANDLE_TASK_EXCEPTIONS
  return result;
}

JSANTask::JSANTask(const Properties& properties)
  : Task(properties)
{
  addDependsOn(CleanResultsTask::name);
}


TASK_NAME_DEF(JSAN2ChangePathTask);

Task::ExecutionResult JSAN2ChangePathTask::execute()
{
  ExecutionResult result;
  ExecutionLogger logger(this, result);

  try {
    vector<string> sv;
    addMessageLevel(sv);
    sv.push_back((props.asgDir / (props.projectName + ".jssi")).string());
    sv.push_back("-from:" + props.projectBaseDir.string() + DIRDIVCHAR);

    checkedExec(props.toolsDir / "JSAN2ChangePath", sv, logger);

  } HANDLE_TASK_EXCEPTIONS

    return result;
}

JSAN2ChangePathTask::JSAN2ChangePathTask(const Properties& properties) : Task(properties)
{
  addDependsOn(JSANTask::name);
}


TASK_NAME_DEF(RunESLintTask);
Task::ExecutionResult RunESLintTask::execute()
{
  ExecutionResult result;

  ExecutionLogger logger(this, result);
  try {
    vector<string> sv;

    sv.clear();

    if (!props.nodeOptions.empty()) {
      sv.push_back(props.nodeOptions);
    }

    const string ESLintRunnerPath = (props.toolsDir / "node_modules" / "eslintrunner" / "ESLintRunner.js").string();
    sv.push_back(ESLintRunnerPath);


    if (!props.profileXML.empty()) {
      sv.push_back("--rul");
      const string rul = (props.tempDir / "ESLint.rul").string();
      sv.push_back(rul);
    }

    sv.push_back("--out");
    const string out = (props.tempDir / (props.projectName + "-ESLint-result.xml")).string();
    sv.push_back(out);

    const string baseDir = (props.projectBaseDir).string();
    sv.push_back(baseDir);


    checkedExec("node", sv, logger);
  }
  HANDLE_TASK_EXCEPTIONS

  return result;
}
RunESLintTask::RunESLintTask(const Properties& properties)
  : Task(properties)
{
  addDependsOn(JSANTask::name);
  addDependsOn(ProfileTask::name);
}

TASK_NAME_DEF(JSAN2LimTask);

Task::ExecutionResult JSAN2LimTask::execute()
{
  ExecutionResult result;
  ExecutionLogger logger(this, result);

  try {

    vector<string> sv;
    addMessageLevel(sv);

    sv.push_back((props.asgDir / (props.projectName + ".jssi")).string());
    sv.push_back("-out:" + (props.asgDir / (props.projectName + ".lim")).string());

    checkedExec(props.toolsDir / "JSAN2Lim", sv, logger);
  }
  HANDLE_TASK_EXCEPTIONS

  return result;
}

JSAN2LimTask::JSAN2LimTask(const Properties& properties)
  : Task(properties)
{
  addDependsOn(JSANTask::name);
  addDependsOn(JSAN2ChangePathTask::name);
}

TASK_NAME_DEF(ESLint2GraphTask);

Task::ExecutionResult ESLint2GraphTask::execute()
{
  ExecutionResult result;
  ExecutionLogger logger(this, result);
  if (props.runESLint) {
    try {
      vector<string> sv;

      sv.clear();

      sv.push_back("-graph:" + (props.graphDir / (props.projectName + "-ESLint.graph")).string());
      sv.push_back("-out:" + (props.projectTimedResultDir / (props.projectName + "-ESLint.txt")).string());
      sv.push_back("-lim:" + (props.asgDir / (props.projectName + ".lim")).string());
      sv.push_back("-exportrul");
      sv.push_back("-rul:" + (props.tempDir / "ESLint.rul").string());
      sv.push_back((props.tempDir / (props.projectName + "-ESLint-result.xml")).string());

      checkedExec(props.toolsDir / "ESLint2Graph", sv, logger);
    }
    HANDLE_TASK_EXCEPTIONS
  }
  return result;
}

ESLint2GraphTask::ESLint2GraphTask(const Properties& properties)
  : Task(properties)
{
  addDependsOn(RunESLintTask::name);
  addDependsOn(JSAN2LimTask::name);
  addDependsOn(ProfileTask::name);
}

TASK_NAME_DEF(LIM2MetricsTask);

Task::ExecutionResult LIM2MetricsTask::execute()
{
  ExecutionResult result;
  ////////////////////////////////////////////////////////////////////////////////////////////////////
  ExecutionLogger logger(this, result);

  try {
    vector<string> sv;
    addMessageLevel(sv);

    sv.push_back("-graph:" + (props.graphDir / (props.projectName + "-metrics.graph")).string());
    sv.push_back("-rul:" + (props.toolsDir / "MET.rul").string());
    sv.push_back("-rulconfig:javascript");
    sv.push_back("-exportrul");

    sv.push_back((props.asgDir / (props.projectName + ".lim")).string());

    checkedExec(props.toolsDir / "LIM2Metrics", sv, logger);
  }
  HANDLE_TASK_EXCEPTIONS
  ////////////////////////////////////////////////////////////////////////////////////////////////////

  return result;
}

LIM2MetricsTask::LIM2MetricsTask(const Properties& properties)
  : Task(properties)
{
  addDependsOn(JSANTask::name);
  addDependsOn(JSAN2LimTask::name);
}

TASK_NAME_DEF(DcfTask);
TOOL_RUL_CONFIG_DEF(Dcf, javascript);

Task::ExecutionResult DcfTask::execute()
{
  ExecutionResult result;
  ExecutionLogger logger(this, result);

  try {

    vector<string> sv;
    addMessageLevel(sv);

    sv.push_back("-lim:" + (props.asgDir / (props.projectName + ".lim")).string());
    sv.push_back("-graph:" + (props.graphDir / (props.projectName + "-DCF.graph")).string());
    sv.push_back("-metrics");

    sv.push_back("-out:" + (props.projectTimedResultDir / (props.projectName + "-clones.txt")).string());

    sv.push_back("-multipleasgroot");
    sv.push_back("-onlyfunctionclone");
    sv.push_back("-patternfilterlog:" + (props.logDir / "clone-filter.log").string());
    sv.push_back("-patternfilter");
    sv.push_back("10");
    sv.push_back("100");
    if (props.cloneMinLines != -1)
      sv.push_back("-minlines:" + common::toString(props.cloneMinLines));
    if (props.cloneGenealogy) {
      sv.push_back("-genealogy:" + (props.projectResultDir / (props.projectName + ".gsi")).string());
    }
    sv.push_back("-rul:" + (props.toolsDir / "DCF.rul").string());
    sv.push_back("-rulconfig:" + TOOL_RUL_CONFIG(Dcf));
    sv.push_back("-exportrul");

    sv.push_back((props.asgDir / (props.projectName + ".jssi")).string());

    checkedExec(props.toolsDir / "DuplicatedCodeFinder", sv, logger);

    if (props.cloneGenealogy)
      copy_file(props.projectResultDir / (props.projectName + ".gsi"), props.asgDir / (props.projectName + ".gsi"), copy_option::overwrite_if_exists);
  }
  HANDLE_TASK_EXCEPTIONS

  return result;
}

DcfTask::DcfTask(const Properties& properties)
  : Task(properties)
{
  addDependsOn(JSAN2LimTask::name);
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
      if (fileIterator->path().extension() == ".graph")
        sv.push_back(fileIterator->path().string());
    }
    sort(sv.begin(), sv.end());
    sv.push_back("-out:" + (props.projectTimedResultDir / (props.projectName + ".graph")).string());
    sv.push_back("-summary");


    checkedExec(props.toolsDir / "GraphMerge", sv, logger);
  }
  HANDLE_TASK_EXCEPTIONS

  return result;
}

GraphMergeTask::GraphMergeTask(const Properties& properties)
  : Task(properties)
{
  addDependsOn(JSANTask::name);
  addDependsOn(ESLint2GraphTask::name);
  addDependsOn(LIM2MetricsTask::name);
  addDependsOn(DcfTask::name);
  addDependsOn(Sonar2GraphTask::name);
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

      sv.push_back((props.projectTimedResultDir / (props.projectName + ".graph")).string());
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

  }
  HANDLE_TASK_EXCEPTIONS

  return result;
}

GraphDumpTask::GraphDumpTask(const Properties& properties)
  : Task(properties)
{
  addDependsOn(GraphMergeTask::name);
  addDependsOn(MetricHunterTask::name);
  addDependsOn(LIM2PatternsTask::name);
}

TASK_NAME_DEF(MetricHunterTask);

Task::ExecutionResult MetricHunterTask::execute()
{
  ExecutionResult result;
  ExecutionLogger logger(this, result);
  try {

    string graphFile = (props.projectTimedResultDir / (props.projectName + ".graph")).string();

    vector<string> sv;
    addMessageLevel(sv);

    sv.push_back("-graph:" + graphFile);
    sv.push_back("-out:" + (props.projectTimedResultDir / (props.projectName + "-MetricHunter.txt")).string());

    sv.push_back("-thresholds:" + (props.tempDir / "MetricHunter.threshold").string());

    sv.push_back("-exportrul");
    sv.push_back(graphFile);

    checkedExec(props.toolsDir / "MetricHunter", sv, logger);
  }
  HANDLE_TASK_EXCEPTIONS

  return result;
}

MetricHunterTask::MetricHunterTask(const Properties& properties)
  : Task(properties)
{
  addDependsOn(GraphMergeTask::name);
}

TASK_NAME_DEF(ProfileTask);

Task::ExecutionResult ProfileTask::execute()
{
  ExecutionResult result;
  ExecutionLogger logger(this, result);
  try {

    // original rul files
    path ESLintRulFileOrig = props.toolsDir / "ESLint.rul";

    // temp rul files
    path ESLintRulFile = props.tempDir / "ESLint.rul";

    // data
    ProfileHandler profile;
    map<string, rul::RulHandler*> rulHandlers; // for rul files
    map<string, bool> runTool; // running tools

    // load profile
    if (!props.profileXML.empty())
      profile.parseXML(props.profileXML.string());

    boost::shared_ptr<rul::RulHandler> eslintrh;

    // copy original rul files into temp
    if (exists(ESLintRulFileOrig)) {
      copy_file(ESLintRulFileOrig, ESLintRulFile);
    }

    //load rul file
    eslintrh = boost::make_shared<rul::RulHandler>(ESLintRulFile.string(), "Default", "eng");
    rulHandlers.insert(make_pair("ESLINT", eslintrh.get()));

    //set running tools
    runTool.insert(make_pair("ESLINT", props.runESLint));

    //process rules csv
    profileProcessRulesCSV(profile, rulHandlers, runTool, props.rulesCSV.string());

    //metrichunter thresholds
    path MetricHunterThresholdsFileOrig = props.toolsDir / "MetricHunter.threshold";
    path MetricHunterThresholdsFile = props.tempDir / "MetricHunter.threshold";

    //process thresholds
    profileProcessToolThresholds(profile, "MetricHunter", MetricHunterThresholdsFileOrig.string(), MetricHunterThresholdsFile.string());

    //process udm metrics
    bool UDM_result = profileProcessUDM(profile, (props.tempDir / "UDM.rul").string(), "javascript");
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
  }
  HANDLE_TASK_EXCEPTIONS
  return result;
}

ProfileTask::ProfileTask(const Properties& properties)
  : Task(properties)
{
  addDependsOn(JSAN2LimTask::name);
}

TASK_NAME_DEF(UserDefinedMetricsTask);
TOOL_RUL_CONFIG_DEF(UserDefinedMetrics, javascript);

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
    sv.push_back("-rul:" + (props.tempDir / "UDM.rul").string());
    sv.push_back("-rulconfig:" + TOOL_RUL_CONFIG(UserDefinedMetrics));
    sv.push_back("-graph:" + (props.projectTimedResultDir / (props.projectName + ".graph")).string());

    checkedExec(props.toolsDir / "UserDefinedMetrics", sv, logger);
  }
  HANDLE_TASK_EXCEPTIONS

  return result;
}

UserDefinedMetricsTask::UserDefinedMetricsTask(list<string>& inactives, const Properties& properties)
  : Task(properties)
  , inactives(inactives)
{
  addDependsOn(GraphMergeTask::name);
  addDependsOn(MetricHunterTask::name);
}

SONAR2GRAPH_TASK(js)

Sonar2GraphTask::Sonar2GraphTask(const Properties& properties) : Task(properties)
{
  addDependsOn(JSAN2LimTask::name);
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
    sv.push_back("-pattern:" + props.patternFile + (!props.patternFile.empty() ? "," : "") + (props.toolsDir / "Patterns" / "AntiPatterns").string());
    sv.push_back("-metrics:" + (props.toolsDir / "MET.rul").string());
    sv.push_back("-out:" + (props.projectTimedResultDir / (props.projectName + ".txt")).string());

    if (!props.whitelist.empty()) {
        sv.push_back("-whitelist:" + props.whitelist);
    }
    if (!props.blacklist.empty()) {
        sv.push_back("-blacklist:" + props.blacklist);
    }

    checkedExec(props.toolsDir / "LIM2Patterns", sv, logger);

  } HANDLE_TASK_EXCEPTIONS

    return result;
}

LIM2PatternsTask::LIM2PatternsTask(const Properties& properties) : Task(properties) {
  addDependsOn(GraphMergeTask::name);
  addDependsOn(MetricHunterTask::name);
  addDependsOn(UserDefinedMetricsTask::name);
}
