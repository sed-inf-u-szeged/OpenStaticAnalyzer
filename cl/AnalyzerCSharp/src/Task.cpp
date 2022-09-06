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

#include "../inc/Task.h"
#include "../inc/messages.h"
#include "../inc/Properties.h"

using namespace std;
using namespace columbus;
using namespace columbus::controller;
using namespace common;
using namespace boost::filesystem;
using namespace boost;


TASK_NAME_DEF(SolutionAnalysisTask);

Task::ExecutionResult SolutionAnalysisTask::execute()
{
  ExecutionResult result;
  ExecutionLogger logger(this, result);


  try {
    vector<string> sv ;

    createDirectories(props.fxcopOutPath, logger);

    sv.push_back("-input:" + props.inputFile.string());
    sv.push_back("-output:" + props.asgDir.string());
    if(!props.lcssiList.empty())
        sv.push_back("-outList:" + props.lcssiList.string());
    if(!props.projectName.empty())
        sv.push_back("-limName:" + props.projectName);

#ifndef __unix__
    if (props.runFxCop) {
        sv.push_back("-runFxCop:true");
        sv.push_back("-fxCopPath:" + props.fxcopBinaryPath.string());
        sv.push_back("-fxCopOut:" + props.fxcopOutPath.string());
    }
    else
#endif
        sv.push_back("-runFxCop:false");

    if(!props.config.empty())
        sv.push_back("-configuration:" + props.config);
    if (!props.platform.empty())
        sv.push_back("-platform:" + props.platform);
    if(!props.externalHardFilter.empty())
        sv.push_back("-externalHardFilter:" + props.externalHardFilter.string());
    if(!props.externalSoftFilter.empty())
        sv.push_back("-externalSoftFilter:" + props.externalSoftFilter.string());
    if(props.csvSeparator)
        sv.push_back("-csvseparator:" + string(1, props.csvSeparator));
    if(props.csvDecimalmark)
        sv.push_back("-csvdecimalmark:" + string(1, props.csvDecimalmark));

    sv.push_back(string("-runAnalyzers:") + (props.runRoslynAnalyzers ? "true" : "false"));
    sv.push_back("-analyzersOut:" + props.roslynAnalyzersOutPath.string());

    checkedExec(props.toolsDir / "CSAN", sv, logger);

  } HANDLE_TASK_EXCEPTIONS

  return result;
}

SolutionAnalysisTask::SolutionAnalysisTask(const Properties& properties) : Task(properties)
{
  // there is no dependency
}

TASK_NAME_DEF(ProfileTask);

Task::ExecutionResult ProfileTask::execute()
{
  ExecutionResult result;
  ExecutionLogger logger(this, result);
  try {

#ifndef __unix__
    // original rul files
    path FxCopRulFileOrig = props.toolsDir / "FxCop.rul.md";
    path FxCopRulMetadataFileOrig = props.toolsDir / "FxCop.rul_metadata.md";

    // temp rul files
    path FxCopRulFile = props.tempDir / "FxCop.rul.md";
    path FxCopRulMetadataFile = props.tempDir / "FxCop.rul_metadata.md";

    // copy original rul files into temp
    if (exists(FxCopRulFileOrig))
      copy_file(FxCopRulFileOrig, FxCopRulFile);
    if (exists(FxCopRulMetadataFileOrig))
      copy_file(FxCopRulMetadataFileOrig, FxCopRulMetadataFile);
#endif

    // data
    ProfileHandler profile;
    map<string, rul::RulHandler*> rulHandlers; // for rul files
    map<string, bool> runTool; // running tools

#ifndef __unix__
    // load profile
    if(!props.profileXML.empty())
      profile.parseXML(props.profileXML.string());

    // load rul files
    rul::RulHandler fxcoprh(FxCopRulFile.string(), "Default", "eng");

    rulHandlers.insert(make_pair("FXCOP", &fxcoprh));

    // set running tools
    runTool.insert(make_pair("FxCop", props.runFxCop));

    //process rules csv
    profileProcessRulesCSV(profile, rulHandlers, runTool, props.rulesCSV.string());
#endif

    path MetricHunterThresholdsFileOrig = props.toolsDir / "MetricHunter.threshold";
    path MetricHunterThresholdsFile = props.tempDir / "MetricHunter.threshold";

    //process thresholds
    profileProcessToolThresholds(profile, "MetricHunter", MetricHunterThresholdsFileOrig.string(), MetricHunterThresholdsFile.string());

    //process udm metrics
    bool UDM_result = profileProcessUDM(profile, (props.tempDir / "UDM.rul.md").string(), "csharp");
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
  //addDependsOn(SolutionAnalysisTask::name);
}


#ifndef __unix__
TASK_NAME_DEF(FxCop2GraphTask);

Task::ExecutionResult FxCop2GraphTask::execute()
{
  ExecutionResult result;
  ExecutionLogger logger(this, result);

  try {
    vector<string> sv ;

    sv.push_back("-graph:" + (props.graphDir / (props.projectName + "-FxCop.graph")).string());
    sv.push_back("-rul:" + (props.tempDir / "FxCop.rul.md").string());
    sv.push_back("-exportrul");
    sv.push_back("-lim:" + (props.asgDir / (props.projectName + ".lim")).string());
    sv.push_back(props.fxcopOutPath.string());

    if (props.txtoutput)
      sv.push_back("-out:" + (props.projectTimedResultDir  / (props.projectName + "-FxCop.txt")).string());

    checkedExec(props.toolsDir / "FxCop2Graph", sv, logger);

  } HANDLE_TASK_EXCEPTIONS

  return result;
}

FxCop2GraphTask::FxCop2GraphTask(const Properties& properties) : Task(properties)
{
  addDependsOn(SolutionAnalysisTask::name);
  addDependsOn(ProfileTask::name);
}

#endif

TASK_NAME_DEF(Lim2metricsTask);

Task::ExecutionResult Lim2metricsTask::execute()
{
  ExecutionResult result;
  ExecutionLogger logger(this, result);

  try {
    vector<string> sv ;

    sv.push_back("-graph:" + (props.graphDir / (props.projectName + "-metrics.graph")).string());
    sv.push_back("-rul:" + (props.toolsDir / "MET.rul.md").string());
    sv.push_back("-rulconfig:csharp");
    sv.push_back("-exportrul");
    sv.push_back((props.asgDir /  (props.projectName + ".lim")).string());

    checkedExec(props.toolsDir / "LIM2Metrics", sv, logger);

  } HANDLE_TASK_EXCEPTIONS

  return result;
}

Lim2metricsTask::Lim2metricsTask(const Properties& properties) : Task(properties)
{
  addDependsOn(SolutionAnalysisTask::name);
}

TASK_NAME_DEF(DcfTask);

Task::ExecutionResult DcfTask::execute()
{
  ExecutionResult result;
  ExecutionLogger logger(this, result);

  try {

    vector<string> sv ;

    sv.push_back("-inputlist:" + props.lcssiList.string());
    sv.push_back("-lim:" + (props.asgDir / (props.projectName + ".lim")).string());
    sv.push_back("-graph:" + (props.graphDir  / (props.projectName + "-DCF.graph")).string());
    sv.push_back("-metrics");
    sv.push_back("-multipleasgroot");
    sv.push_back("-onlyfunctionclone");
    if (props.txtoutput)
      sv.push_back("-out:" + (props.projectTimedResultDir  / (props.projectName + "-clones.txt")).string());
    sv.push_back("-patternfilterlog:" + (props.logDir / "clone-filter.log").string());
    sv.push_back("-patternfilter");
    sv.push_back("10");
    sv.push_back("100");
    sv.push_back("-rul:" + (props.toolsDir / "DCF.rul.md").string());
    sv.push_back("-rulconfig:csharp");
    sv.push_back("-exportrul");
    if (props.cloneMinLines != -1)
      sv.push_back("-minlines:" + common::toString(props.cloneMinLines));
    if (props.cloneGenealogy){
      sv.push_back("-genealogy:" + (props.projectResultDir / (props.projectName + ".gsi")).string());
    }

    checkedExec(props.toolsDir / "DuplicatedCodeFinder", sv, logger);

  } HANDLE_TASK_EXCEPTIONS

  return result;
}

DcfTask::DcfTask(const Properties& properties) : Task(properties)
{
  addDependsOn(SolutionAnalysisTask::name);
}

TASK_NAME_DEF(GraphMergeTask);

Task::ExecutionResult GraphMergeTask::execute()
{
  ExecutionResult result;
  ExecutionLogger logger(this, result);
  try {
    vector<string> sv ;

    directory_iterator end;

    for (directory_iterator fileIterator(props.graphDir); fileIterator != end; ++fileIterator) {
      sv.push_back(fileIterator->path().string());
    }
    sort(sv.begin(), sv.end());
    sv.push_back("-out:" + (props.projectTimedResultDir /  (props.projectName + ".graph")).string());
    sv.push_back("-summary");

    if (props.createStats)
      sv.push_back("-stat:" + (props.logDir / "statGraphMerge.csv").string());


    checkedExec(props.toolsDir / "GraphMerge", sv, logger);

  } HANDLE_TASK_EXCEPTIONS

  return result;
}

GraphMergeTask::GraphMergeTask(const Properties& properties) : Task(properties)
{
#ifndef __unix__
  addDependsOn(FxCop2GraphTask::name);
#endif
  addDependsOn(Lim2metricsTask::name);
  addDependsOn(DcfTask::name);
  addDependsOn(Sonar2GraphTask::name);
  addDependsOn(Roslyn2GraphTask::name);
}


TASK_NAME_DEF(GraphDumpTask);

Task::ExecutionResult GraphDumpTask::execute()
{
  ExecutionResult result;
  ExecutionLogger logger(this, result);
  try
  {
    {
      vector<string> sv ;

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
  addDependsOn(Roslyn2GraphTask::name);
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

    vector<string> sv ;
    sv.push_back("-graph:" + graphFile);
    if (props.txtoutput)
      sv.push_back("-out:" + (props.projectTimedResultDir  / (props.projectName + "-MetricHunter.txt")).string());
    sv.push_back("-thresholds:" + (props.tempDir / "MetricHunter.threshold").string());

    sv.push_back("-exportrul");
    sv.push_back(graphFile);

    checkedExec(props.toolsDir / "MetricHunter", sv, logger);

  } HANDLE_TASK_EXCEPTIONS

  return result;
}

MetricHunterTask::MetricHunterTask(const Properties& properties) : Task(properties)
{
  addDependsOn(GraphMergeTask::name);
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
    if (props.createStats)
      sv.push_back("-stat:" + (props.logDir / "statUDM.csv").string());
    sv.push_back("-rul:" + (props.tempDir / "UDM.rul.md").string());
    sv.push_back("-rulconfig:csharp");
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

SONAR2GRAPH_TASK(cs)

Sonar2GraphTask::Sonar2GraphTask(const Properties& properties) : Task(properties)
{
  addDependsOn(SolutionAnalysisTask::name);
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

TASK_NAME_DEF(Roslyn2GraphTask);

Roslyn2GraphTask::Roslyn2GraphTask(const Properties& properties) : Task(properties) {
  addDependsOn(SolutionAnalysisTask::name);
}

Task::ExecutionResult Roslyn2GraphTask::execute() {
  ExecutionResult result;
  ExecutionLogger logger(this, result);

  try {
    vector<string> sv ;

    sv.push_back("-graph:" + (props.graphDir / (props.projectName + "-Roslyn.graph")).string());
    sv.push_back("-lim:" + (props.asgDir / (props.projectName + ".lim")).string());

    if (props.txtoutput)
      sv.push_back("-out:" + (props.projectTimedResultDir  / (props.projectName + "-Roslyn.txt")).string());

    sv.push_back(props.roslynAnalyzersOutPath.string());

    checkedExec(props.toolsDir / "Roslyn2Graph", sv, logger);

  } HANDLE_TASK_EXCEPTIONS

  return result;
}
