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

    if (props.runFxCop) {
        sv.push_back("-runFxCop:true");
        sv.push_back("-fxCopPath:" + props.fxcopBinaryPath.string());
        sv.push_back("-fxCopOut:" + props.fxcopOutPath.string());
    }
    else
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

    // original rul files
    path FxCopRulFileOrig = props.toolsDir / "FxCop.rul";

    // temp rul files
    path FxCopRulFile = props.tempDir / "FxCop.rul";

    // copy original rul files into temp
    if (exists(FxCopRulFileOrig))
      copy_file(FxCopRulFileOrig, FxCopRulFile);

    // data
    ProfileHandler profile;
    map<string, rul::RulHandler*> rulHandlers; // for rul files
    map<string, bool> runTool; // running tools

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

    path MetricHunterThresholdsFileOrig = props.toolsDir / "MetricHunter.threshold";
    path MetricHunterThresholdsFile = props.tempDir / "MetricHunter.threshold";

    //process thresholds
    profileProcessToolThresholds(profile, "MetricHunter", MetricHunterThresholdsFileOrig.string(), MetricHunterThresholdsFile.string());


  } HANDLE_TASK_EXCEPTIONS
  return result;
}

ProfileTask::ProfileTask(const Properties& properties) : Task(properties)
{
  //addDependsOn(SolutionAnalysisTask::name);
}


TASK_NAME_DEF(FxCop2GraphTask);

Task::ExecutionResult FxCop2GraphTask::execute()
{
  ExecutionResult result;
  ExecutionLogger logger(this, result);

  try {
    vector<string> sv ;

    sv.push_back("-graph:" + (props.graphDir / (props.projectName + "-FxCop.graph")).string());
    sv.push_back("-rul:" + (props.tempDir / "FxCop.rul").string());
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

TASK_NAME_DEF(Lim2metricsTask);

Task::ExecutionResult Lim2metricsTask::execute()
{
  ExecutionResult result;
  ExecutionLogger logger(this, result);

  try {
    vector<string> sv ;

    sv.push_back("-graph:" + (props.graphDir / (props.projectName + "-metrics.graph")).string());
    sv.push_back("-rul:" + (props.toolsDir / "MET.rul").string());
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
    sv.push_back("-rul:" + (props.toolsDir / "DCF.rul").string());
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

    if (props.createStats)
      sv.push_back("-stat:" + (props.logDir / "statGraphMerge.csv").string());


    checkedExec(props.toolsDir / "GraphMerge", sv, logger);

  } HANDLE_TASK_EXCEPTIONS

  return result;
}

GraphMergeTask::GraphMergeTask(const Properties& properties) : Task(properties)
{
  addDependsOn(FxCop2GraphTask::name);
  addDependsOn(Lim2metricsTask::name);
  addDependsOn(DcfTask::name);
}


TASK_NAME_DEF(GraphDumpTask);

Task::ExecutionResult GraphDumpTask::execute()
{
  ExecutionResult result;
  ExecutionLogger logger(this, result);
  try {

    vector<string> sv ;

    sv.push_back((props.projectTimedResultDir /  (props.projectName + ".graph")).string());
    sv.push_back("-csv");
    sv.push_back("-xml");
    sv.push_back("-csvseparator:" + string(1, props.csvSeparator));
    sv.push_back("-csvdecimalmark:" + string(1, props.csvDecimalmark));

    if (props.createStats)
      sv.push_back("-stat:" + (props.logDir / "statGraphDump.csv").string());

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

