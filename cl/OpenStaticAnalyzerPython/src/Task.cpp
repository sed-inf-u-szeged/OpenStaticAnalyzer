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
#include <Environment.h>
#include <common/inc/WriteMessage.h>
#include <common/inc/StringSup.h>
#include <common/inc/FileSup.h>
#include <graph/inc/graph.h>
#include <graphsupport/inc/GraphConstants.h>
#include <common/inc/PlatformDependentDefines.h>
#include <controller/inc/ProfileCommon.h>

#include <boost/filesystem/path.hpp>
#include <boost/filesystem.hpp>
#include <boost/filesystem/operations.hpp>
#include <boost/regex.hpp>

#include "../inc/Task.h"
#include "../inc/messages.h"
#include "../inc/Properties.h"


#define TASK_NAME_DEF(_NAME)  const string  _NAME::name(#_NAME)
#define TOOL_RUL_CONFIG(_TOOL_NAME) _TOOL_NAME##_rulconfig
#define TOOL_RUL_CONFIG_DEF(_TOOL_NAME, _CONFIG) const string TOOL_RUL_CONFIG(_TOOL_NAME)(#_CONFIG)

using namespace std;
using namespace columbus;
using namespace columbus::controller;
using namespace common;
using namespace boost::filesystem;
using namespace boost;

TASK_NAME_DEF(PANTask);

Task::ExecutionResult PANTask::execute()
{
  ExecutionResult result;
  ExecutionLogger logger(this, result);

  try {
    vector<string> sv;
    addMessageLevel(sv);

    sv.push_back("-out:" + (props.asgDir / (props.projectName + ".psi")).string());
    sv.push_back((props.projectBaseDir).string());

    sv.push_back("-analyzepackages");

    if (!props.externalHardFilter.empty())
      sv.push_back("-fltp:" + props.externalHardFilter.string());

    sv.push_back("-pythonBinary:" + props.pythonBinary.string());

    if (props.pythonVersion == "2")
      checkedExec(props.toolsDir / "PAN2", sv, logger);
    else
      checkedExec(props.toolsDir / "PAN3", sv, logger);

  } HANDLE_TASK_EXCEPTIONS

  return result;
}

PANTask::PANTask(const Properties& properties) : Task(properties)
{
  // there is no dependency 
}

TASK_NAME_DEF(PAN2LimTask);

Task::ExecutionResult PAN2LimTask::execute()
{
  ExecutionResult result;
  ExecutionLogger logger(this, result);

  try {
    vector<string> sv;
    addMessageLevel(sv);

    sv.push_back((props.asgDir / (props.projectName + ".psi")).string());
    sv.push_back("-out:" + (props.asgDir / (props.projectName + ".lim")).string());

    checkedExec(props.toolsDir / "PAN2Lim", sv, logger);
    
  } HANDLE_TASK_EXCEPTIONS

  return result;
}

PAN2LimTask::PAN2LimTask(const Properties& properties) : Task(properties)
{
  addDependsOn(PANTask::name);
}


TASK_NAME_DEF(LIM2MetricsTask);
TOOL_RUL_CONFIG_DEF(LIM2Metrics, python);

Task::ExecutionResult LIM2MetricsTask::execute()
{
  ExecutionResult result;
  ExecutionLogger logger(this, result);

  try {
    vector<string> sv;
    addMessageLevel(sv);

    sv.push_back("-graph:" + (props.graphDir / (props.projectName + "-metrics.graph")).string());
    sv.push_back("-rul:" + (props.toolsDir / "MET.rul").string());
    sv.push_back("-rulconfig:" + TOOL_RUL_CONFIG(LIM2Metrics));
    sv.push_back("-exportrul");
    sv.push_back((props.asgDir /  (props.projectName + ".lim")).string());

    checkedExec(props.toolsDir / "LIM2Metrics", sv, logger);

  } HANDLE_TASK_EXCEPTIONS

  return result;
}

LIM2MetricsTask::LIM2MetricsTask(const Properties& properties) : Task(properties)
{
  addDependsOn(PANTask::name);
  addDependsOn(PAN2LimTask::name);
}

TASK_NAME_DEF(DcfTask);
TOOL_RUL_CONFIG_DEF(Dcf, python);

Task::ExecutionResult DcfTask::execute()
{
  ExecutionResult result;
  ExecutionLogger logger(this, result);

  try {

    vector<string> sv;
    addMessageLevel(sv);

    sv.push_back((props.asgDir / (props.projectName + ".psi")).string());
    sv.push_back("-lim:" + (props.asgDir / (props.projectName + ".lim")).string());
    sv.push_back("-graph:" + (props.graphDir  / (props.projectName + "-DCF.graph")).string());
    sv.push_back("-metrics");
    sv.push_back("-multipleasgroot");
    sv.push_back("-onlyfunctionclone");
    sv.push_back("-out:" + (props.projectTimedResultDir  / (props.projectName + "-clones.txt")).string());
    sv.push_back("-patternfilter");
    sv.push_back("10");
    sv.push_back("100");
    sv.push_back("-rul:" + (props.toolsDir / "DCF.rul").string());
    sv.push_back("-rulconfig:" + TOOL_RUL_CONFIG(Dcf));
    sv.push_back("-exportrul");

    if (props.cloneGenealogy){
      sv.push_back("-genealogy:" + (props.projectResultDir / (props.projectName + ".gsi")).string());
    }

    if (props.cloneMinLines != -1) 
      sv.push_back("-minlines:" + common::toString(props.cloneMinLines));

    checkedExec(props.toolsDir / "DuplicatedCodeFinder", sv, logger);
  
  } HANDLE_TASK_EXCEPTIONS

  return result;
}

DcfTask::DcfTask(const Properties& properties) : Task(properties)
{
  addDependsOn(PANTask::name);
  addDependsOn(PAN2LimTask::name);
}


TASK_NAME_DEF(PylintTask);

Task::ExecutionResult PylintTask::execute()
{
  ExecutionResult result;
  ExecutionLogger logger(this, result);

  try {
    vector<string> sv;
    addMessageLevel(sv);

    sv.push_back("-runpylint");
    sv.push_back("-pythonBinary:" + props.pythonBinary.string());
    sv.push_back("-pylintdir:" + (props.toolsDir / "python").string());
    sv.push_back("-pylintrc:" + (props.toolsDir / "Pylint.conf").string());
    sv.push_back("-projectbasedir:" + props.projectBaseDir.string());
    sv.push_back("-pylintout:" + (props.tempDir / (props.projectName + "-Pylint-result.txt")).string());
    for (const string& s : props.pylintOptions)
      sv.push_back("-pylintOptions:" + s);

    checkedExec(props.toolsDir / "Pylint2Graph", sv, logger);

  } HANDLE_TASK_EXCEPTIONS

  return result;
}

PylintTask::PylintTask(const Properties& properties) : Task(properties)
{
  // there is no dependency 
}


TASK_NAME_DEF(Pylint2GraphTask);
TOOL_RUL_CONFIG_DEF(Pylint2Graph, Default);

Task::ExecutionResult Pylint2GraphTask::execute()
{
  ExecutionResult result;
  ExecutionLogger logger(this, result);

  try {
    vector<string> sv;
    addMessageLevel(sv);

    sv.push_back((props.tempDir / (props.projectName + "-Pylint-result.txt")).string());
    sv.push_back("-lim:" + (props.asgDir / (props.projectName + ".lim")).string());
    sv.push_back("-graph:" + (props.graphDir / (props.projectName + "-Pylint.graph")).string());
    sv.push_back("-out:" + (props.projectTimedResultDir / (props.projectName + "-Pylint.txt")).string());
    sv.push_back("-rul:" + (props.tempDir / "Pylint.rul").string());
    sv.push_back("-rulconfig:" + TOOL_RUL_CONFIG(Pylint2Graph));
    sv.push_back("-exportrul");

    checkedExec(props.toolsDir / "Pylint2Graph", sv, logger);

  } HANDLE_TASK_EXCEPTIONS

  return result;
}

Pylint2GraphTask::Pylint2GraphTask(const Properties& properties) : Task(properties)
{
  addDependsOn(PAN2LimTask::name);
  addDependsOn(PylintTask::name);
  addDependsOn(ProfileTask::name);
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
    sv.push_back("-out:" + (props.projectTimedResultDir / (props.projectName + ".graph")).string());

    checkedExec(props.toolsDir / "GraphMerge", sv, logger);
  
  } HANDLE_TASK_EXCEPTIONS
  
  return result;
}

GraphMergeTask::GraphMergeTask(const Properties& properties) : Task(properties)
{
  addDependsOn(PANTask::name);
  addDependsOn(LIM2MetricsTask::name);
  addDependsOn(DcfTask::name);
  addDependsOn(Pylint2GraphTask::name);
}


TASK_NAME_DEF(MetricHunterTask);

Task::ExecutionResult MetricHunterTask::execute()
{
  ExecutionResult result;
  ExecutionLogger logger(this, result);

  try {
    vector<string> sv;
    addMessageLevel(sv);
    sv.push_back((props.projectTimedResultDir / (props.projectName + ".graph")).string());
    sv.push_back("-thresholds:" + (props.tempDir / "MetricHunter.threshold").string());

    sv.push_back("-graph:" + (props.projectTimedResultDir / (props.projectName + ".graph")).string());
    sv.push_back("-out:" + (props.projectTimedResultDir / (props.projectName + "-MetricHunter.txt")).string());
    sv.push_back("-exportrul");

    checkedExec(props.toolsDir / "MetricHunter", sv, logger);

  } HANDLE_TASK_EXCEPTIONS

  return result;
}

MetricHunterTask::MetricHunterTask(const Properties& properties) : Task(properties)
{
  addDependsOn(GraphMergeTask::name);
}


TASK_NAME_DEF(GraphDumpTask);

Task::ExecutionResult GraphDumpTask::execute()
{
  ExecutionResult result;
  ExecutionLogger logger(this, result);

  try {
    vector<string> sv;
    addMessageLevel(sv);

    sv.push_back((props.projectTimedResultDir / (props.projectName + ".graph")).string());
    sv.push_back("-csv");
    sv.push_back("-xml");
    sv.push_back("-csvseparator:" + string(1, props.csvSeparator));
    sv.push_back("-csvdecimalmark:" + string(1, props.csvDecimalmark));

    checkedExec(props.toolsDir / "GraphDump", sv, logger);

  } HANDLE_TASK_EXCEPTIONS

  return result;
}

GraphDumpTask::GraphDumpTask(const Properties& properties) : Task(properties)
{
  addDependsOn(GraphMergeTask::name);
  addDependsOn(MetricHunterTask::name);
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
    for( directory_iterator iter = begin; iter != end; ++iter ) {
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
    }
    
  } HANDLE_TASK_EXCEPTIONS
  
  return result;

}

CleanResultsTask::CleanResultsTask(const Properties& properties) : Task(properties)
{
  // there is no dependency 
}


TASK_NAME_DEF(ProfileTask);

Task::ExecutionResult ProfileTask::execute()
{
  ExecutionResult result;
  ExecutionLogger logger(this, result);
  try {

    // original rul files
    path PylintRulFileOrig = props.toolsDir / "Pylint.rul";

    // temp rul files
    path PylintRulFile = props.tempDir / "Pylint.rul";
    
    // copy original rul files into temp
    if (exists(PylintRulFileOrig))
      copy_file(PylintRulFileOrig, PylintRulFile);
    
    // data
    ProfileHandler profile;
    map<string, rul::RulHandler*> rulHandlers; // for rul files
    map<string, bool> runTool; // running tools
    
    // load profile
    if(!props.profileXML.empty())
      profile.parseXML(props.profileXML.string());

    // load rul files
    rul::RulHandler pylintrh(PylintRulFile.string(), "Default", "eng");
    
    rulHandlers.insert(make_pair("PYLINT", &pylintrh));
    
    // set running tools
    runTool.insert(make_pair("PYLINT", props.runPylint));

    //process rules csv
    profileProcessRulesCSV(profile, rulHandlers, runTool, props.rulesCSV.string());

    path MetricHunterThresholdsFileOrig = props.toolsDir / "MetricHunter.threshold";
    path MetricHunterThresholdsFile = props.tempDir / "MetricHunter.threshold";

    //process thresholds
    profileProcessToolThresholds(profile, "MetricHunter", MetricHunterThresholdsFileOrig.string(), MetricHunterThresholdsFile.string());

  } HANDLE_TASK_EXCEPTIONS
  return result;
}

ProfileTask::ProfileTask(const Properties& properties) : Task(properties)
{
  addDependsOn(PAN2LimTask::name);
}
