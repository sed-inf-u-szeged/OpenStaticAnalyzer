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


#define TASK_NAME_DEF(_NAME)   const string  _NAME::name(#_NAME)
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
        if(is_directory(*it) && it->path().filename() == "OpenStaticAnalyzer" && it->path().parent_path().filename() == "target") {
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
  addDependsOn(JAN2limTask::name);
  addDependsOn(GraphDumpTask::name);
}



TASK_NAME_DEF( DirectoryBasedAnalysisTask);

Task::ExecutionResult DirectoryBasedAnalysisTask::execute()
{
  ExecutionResult result;
  ExecutionLogger logger(this, result);

  try {
    vector<string> sv;
    
    // -------------------------------------------------------------------------------------------------------------
    // ---------------------------------------------- GenericConfig ------------------------------------------------
    // -------------------------------------------------------------------------------------------------------------

    path tmpConfig = props.tempDir / "toolchain.ini";

    copy_file(props.wrapperToolsDir / "toolchain.ini", tmpConfig);

    sv.push_back("-config:" + tmpConfig.string());

    if (!props.externalHardFilter.empty()) {
      sv.push_back("-option:JAN/hardFilter=" + props.externalHardFilter.string());
    }
    sv.push_back("-option:JAN/needCheck=0");
    
    
    checkedExec(props.wrapperToolsDir / "GenericConfig", sv, logger);


    // -------------------------------------------------------------------------------------------------------------
    // ---------------------------------------------- Run JAN ------------------------------------------------------
    // -------------------------------------------------------------------------------------------------------------
    
    sv.clear();

    string JANPath = (props.wrapperToolsDir / "JAN.jar").string();

    string source_file_list = (props.tempDir / "source_file_list.lst").string();
    string cp_list = (props.tempDir / "cp_list.lst").string();

    string ljsi_file = (props.projectBaseDir / props.analysisOutputDir / (props.projectName + ".ljsi")).string();
    string fjsi_file = (props.projectBaseDir / props.analysisOutputDir / (props.projectName + ".fjsi")).string();
    
    vector<string> JANJvmOptionsV;
    split(props.JANJvmOptions, JANJvmOptionsV, ' ');
    sv.insert(sv.end(), JANJvmOptionsV.begin(), JANJvmOptionsV.end());

    sv.push_back("--patch-module");
    sv.push_back("jdk.compiler=" + (props.wrapperToolsDir / "jdk.compiler.jar").string());

    sv.push_back("-jar");
    sv.push_back(JANPath);

    sv.push_back("-i");
    sv.push_back(props.projectBaseDir.string());

    sv.push_back("-r");

    vector<string> JANOptionsV;
    split(props.JANOptions, JANOptionsV, ' ');
    sv.insert(sv.end(), JANOptionsV.begin(), JANOptionsV.end());

    if (props.runPMD){
      sv.push_back("-s");
      sv.push_back(source_file_list);

      sv.push_back("-u");
      sv.push_back(cp_list);
    }

    if (!props.javacOptions.empty()){
      sv.push_back("-j:|" + props.javacOptions);
    }

    sv.push_back("-c");
    sv.push_back(tmpConfig.string());

    sv.push_back("-o");
    sv.push_back(ljsi_file);


    checkedExec("java", sv, logger);
    
    copy_file(ljsi_file, (props.asgDir / (props.projectName + ".ljsi")).string());
    copy_file(fjsi_file, (props.asgDir / (props.projectName + ".fjsi")).string());

    std::ofstream outfile;

    outfile.open(props.superLinkList.string().c_str());
    outfile << ljsi_file;
    outfile.close();
    outfile.clear();

    // -------------------------------------------------------------------------------------------------------------
    // ---------------------------------------------- Run PMD ------------------------------------------------------
    // -------------------------------------------------------------------------------------------------------------

    if(props.runPMD){
      sv.clear();

      string pmd_config_file = (props.wrapperToolsDir / "PMD" / "PMD-config.xml").string();
      string pmd_res_xml = (props.tempDir / (props.projectName + "-PMD.xml")).string();

      vector<string> JvmOptionsV;
      split(props.JVMOptions, JvmOptionsV, ' ');
      sv.insert(sv.end(), JvmOptionsV.begin(), JvmOptionsV.end());

      sv.push_back("-cp");
      sv.push_back((props.wrapperToolsDir / "PMD" / "lib" / "*").string());

      sv.push_back("net.sourceforge.pmd.PMD");

      sv.push_back("-V");

      sv.push_back("-d");
      sv.push_back(source_file_list);
      

      vector<string> PMDOptionsV;
      split(props.PMDOptions, PMDOptionsV, ' ');
      sv.insert(sv.end(), PMDOptionsV.begin(), PMDOptionsV.end());

      sv.push_back("-auxclasspath");
      sv.push_back("file:///" + cp_list);
      
      sv.push_back("-f");
      sv.push_back("xml");
      
      sv.push_back("-R");
      sv.push_back(pmd_config_file);

      sv.push_back("-r");
      sv.push_back(pmd_res_xml);

      sv.push_back("-failOnViolation");
      sv.push_back("false"); // By default PMD exits with status 4 if violations are found, disable this

      try {
        checkedExec("java", sv, logger);
      } catch (const columbus::Exception&) {
        logstream << CMSG_PMD_ERROR << endl;
        throw;
      }

      outfile.open(props.pmdXmlList.string().c_str());
      outfile << pmd_res_xml;
      outfile.close();
    }
    
    

  } HANDLE_TASK_EXCEPTIONS
  return result;
}

DirectoryBasedAnalysisTask::DirectoryBasedAnalysisTask(const Properties& properties) : Task(properties)
{
  addDependsOn(CleanResultsTask::name);
}

TASK_NAME_DEF(JANFilterTask);

Task::ExecutionResult JANFilterTask::execute()
{
  ExecutionResult result;
  ExecutionLogger logger(this, result);

  try {

    vector<string> sv;
    addMessageLevel(sv);

    sv.push_back("-filterrefl");
    sv.push_back("-fltp:" + props.externalSoftFilter.string());
    sv.push_back("-inputlist:" + props.superLinkList.string());
    
    checkedExec(props.toolsDir / "JANFilter", sv, logger);


  } HANDLE_TASK_EXCEPTIONS
  return result;
}

JANFilterTask::JANFilterTask(const Properties& properties) : Task(properties)
{
  addDependsOn(DirectoryBasedAnalysisTask::name);
}

TASK_NAME_DEF(JAN2limTask);

Task::ExecutionResult JAN2limTask::execute()
{
  ExecutionResult result;
  ExecutionLogger logger(this, result);

  try {  

    vector<string> sv;
    addMessageLevel(sv);

    sv.push_back("-inputlist:" + props.superLinkList.string());
    sv.push_back("-out:" + (props.asgDir / (props.projectName + ".lim")).string());
    sv.push_back("-struct:"  + props.superLinkList.string() + ".info");

    checkedExec(props.toolsDir / "JAN2Lim", sv, logger);
    
  } HANDLE_TASK_EXCEPTIONS

  return result;
}

JAN2limTask::JAN2limTask(const Properties& properties) : Task(properties)
{
  addDependsOn(JANFilterTask::name);
}

TASK_NAME_DEF(PMD2GraphTask);

Task::ExecutionResult PMD2GraphTask::execute()
{
  ExecutionResult result;
  ExecutionLogger logger(this, result);

  try {
    vector<string> sv;
    addMessageLevel(sv);

    sv.push_back("-makecsv");
    sv.push_back("-lst:" + props.pmdXmlList.string());
    sv.push_back("-lim:" + (props.asgDir / (props.projectName + ".lim")).string());
    sv.push_back("-rul:" + (props.tempDir / "PMD.rul").string());
    sv.push_back("-exportrul");
    sv.push_back("-graph:" + (props.graphDir / (props.projectName + "-PMD.graph")).string());
    
    sv.push_back("-out:" + (props.projectTimedResultDir  / (props.projectName + "-PMD.txt")).string());

    checkedExec(props.toolsDir / "PMD2Graph", sv, logger);
    
  } HANDLE_TASK_EXCEPTIONS

  return result;
}

PMD2GraphTask::PMD2GraphTask(const Properties& properties) : Task(properties)
{
  addDependsOn(JAN2limTask::name);
  addDependsOn(ProfileTask::name);
}



TASK_NAME_DEF(FindBugsTask);

Task::ExecutionResult FindBugsTask::execute()
{
  ExecutionResult result;
  ExecutionLogger logger(this, result);

  try {

    path FBoutput = props.tempDir / (props.projectName + "-FindBugs.xml");

    vector<string> sv;

    sv.push_back("-textui");
    sv.push_back("-analyzeFromFile");
    sv.push_back(props.FBFileList);
    sv.push_back("-xml:withMessages");
    sv.push_back("-output");
    sv.push_back(FBoutput.string());

    vector<string> FBOptionsV;
    split(props.FBOptions, FBOptionsV, ' ');
    sv.insert(sv.end(), FBOptionsV.begin(), FBOptionsV.end());

    try {
#ifdef _WIN32
      string fbExt = ".bat";
#else
      string fbExt;
#endif
      checkedExec(props.wrapperToolsDir / "spotbugs" / "bin" / ("spotbugs" + fbExt), sv, logger);
    } catch (const columbus::Exception&) {
      logstream << CMSG_FINDBUGS_ERROR << endl;
      throw;
    }


    sv.clear();

    addMessageLevel(sv);

    sv.push_back("-lim:" + (props.asgDir / (props.projectName + ".lim")).string());
    sv.push_back("-rul:" + (props.tempDir / "FindBugs.rul").string());
    sv.push_back("-exportrul");
    sv.push_back("-graph:" + (props.graphDir / (props.projectName + "-FindBugs.graph")).string());
    sv.push_back("-out:" + (props.projectTimedResultDir  / (props.projectName + "-FindBugs.txt")).string());

    sv.push_back(FBoutput.string());

    checkedExec(props.toolsDir / "FindBugs2Graph", sv, logger);

  } HANDLE_TASK_EXCEPTIONS

  return result;
}

FindBugsTask::FindBugsTask(const Properties& properties) : Task(properties)
{
  addDependsOn(JAN2limTask::name);
  addDependsOn(ProfileTask::name);
}

TASK_NAME_DEF(Lim2metricsTask);
TOOL_RUL_CONFIG_DEF(Lim2metrics, java);

Task::ExecutionResult Lim2metricsTask::execute()
{
  ExecutionResult result;
  ExecutionLogger logger(this, result);

  try {
    vector<string> sv;
    addMessageLevel(sv);

    sv.push_back("-graph:" + (props.graphDir / (props.projectName + "-metrics.graph")).string());
    sv.push_back("-rul:" + (props.toolsDir / "MET.rul").string());
    sv.push_back("-rulconfig:" + TOOL_RUL_CONFIG(Lim2metrics));
    sv.push_back("-exportrul");
    sv.push_back((props.asgDir /  (props.projectName + ".lim")).string());

    checkedExec(props.toolsDir / "LIM2Metrics", sv, logger);
    
  } HANDLE_TASK_EXCEPTIONS

  return result;
}

Lim2metricsTask::Lim2metricsTask(const Properties& properties) : Task(properties)
{
  addDependsOn(JAN2limTask::name);
}



TASK_NAME_DEF(DcfTask);
TOOL_RUL_CONFIG_DEF(Dcf, java);

Task::ExecutionResult DcfTask::execute()
{
  ExecutionResult result;
  ExecutionLogger logger(this, result);

  try {

    vector<string> sv;
    addMessageLevel(sv);

    sv.push_back("-inputlist:" + props.superLinkList.string());
    sv.push_back("-lim:" + (props.asgDir / (props.projectName + ".lim")).string());
    sv.push_back("-graph:" + (props.graphDir  / (props.projectName + "-DCF.graph")).string());
    sv.push_back("-metrics");

    sv.push_back("-out:" + (props.projectTimedResultDir  / (props.projectName + "-clones.txt")).string());

    sv.push_back("-multipleasgroot");
    sv.push_back("-onlyfunctionclone");
    sv.push_back("-patternfilterlog:" + (props.logDir / "clone-filter.log").string());
    sv.push_back("-patternfilter");
    sv.push_back("10");
    sv.push_back("100");
    if (props.cloneMinLines != -1) 
      sv.push_back("-minlines:" + common::toString(props.cloneMinLines));
    if (props.cloneGenealogy){
      sv.push_back("-genealogy:" + (props.projectResultDir / (props.projectName + ".gsi")).string());
    }
    sv.push_back("-rul:" + (props.toolsDir / "DCF.rul").string());
    sv.push_back("-rulconfig:" + TOOL_RUL_CONFIG(Dcf));
    sv.push_back("-exportrul");

    checkedExec(props.toolsDir / "DuplicatedCodeFinder", sv, logger);
    
    if (props.cloneGenealogy)
      copy_file(props.projectResultDir / (props.projectName + ".gsi"), props.asgDir / (props.projectName + ".gsi"), copy_option::overwrite_if_exists);

  } HANDLE_TASK_EXCEPTIONS

  return result;
}

DcfTask::DcfTask(const Properties& properties) : Task(properties)
{
  addDependsOn(JAN2limTask::name);
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
      if(fileIterator->path().extension() == ".graph")
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
  addDependsOn(PMD2GraphTask::name);
  addDependsOn(FindBugsTask::name);
  addDependsOn(Lim2metricsTask::name);
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
    
    checkedExec(props.toolsDir / "MetricHunter", sv, logger);

  } HANDLE_TASK_EXCEPTIONS

  return result;
}
    
MetricHunterTask::MetricHunterTask(const Properties& properties) : Task(properties)
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
    path FindBugsRulFileOrig = props.toolsDir / "FindBugs.rul";
    path PMDRulFileOrig = props.toolsDir / "PMD.rul";

    // temp rul files
    path FindBugsRulFile = props.tempDir / "FindBugs.rul";
    path PMDRulFile = props.tempDir / "PMD.rul";
    
    
    // data
    ProfileHandler profile;
    map<string, rul::RulHandler*> rulHandlers; // for rul files
    map<string, bool> runTool; // running tools
    
    // load profile
    if(!props.profileXML.empty())
      profile.parseXML(props.profileXML.string());
    
    boost::shared_ptr<rul::RulHandler> fbrh;
    boost::shared_ptr<rul::RulHandler> pmdrh;

    // copy original rul files into temp
    if (exists(FindBugsRulFileOrig))
    {
      copy_file(FindBugsRulFileOrig, FindBugsRulFile);
      fbrh = boost::make_shared<rul::RulHandler>(FindBugsRulFile.string(), "Default", "eng");
      rulHandlers.insert(make_pair("FB", fbrh.get()));
    }
    if (exists(PMDRulFileOrig))
    {
      copy_file(PMDRulFileOrig, PMDRulFile);
      pmdrh = boost::make_shared<rul::RulHandler>(PMDRulFile.string(), "Default", "eng");
      rulHandlers.insert(make_pair("PMD", pmdrh.get()));
    }

    // set running tools
    runTool.insert(make_pair("FB", props.runFindBugs));
    runTool.insert(make_pair("PMD", props.runPMD));
        
    //process rules csv
    profileProcessRulesCSV(profile, rulHandlers, runTool, props.rulesCSV.string());


    path MetricHunterThresholdsFileOrig = props.toolsDir / "MetricHunter.threshold";
    path MetricHunterThresholdsFile = props.tempDir / "MetricHunter.threshold";

    //process thresholds
    profileProcessToolThresholds(profile, "MetricHunter", MetricHunterThresholdsFileOrig.string(), MetricHunterThresholdsFile.string());

    //process udm metrics
    bool UDM_result = profileProcessUDM(profile, (props.tempDir / "UDM.rul").string(), "java");
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
  addDependsOn(JAN2limTask::name);
}

TASK_NAME_DEF(UserDefinedMetricsTask);
TOOL_RUL_CONFIG_DEF(UserDefinedMetrics, java);

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

  } HANDLE_TASK_EXCEPTIONS

  return result;
}

UserDefinedMetricsTask::UserDefinedMetricsTask(list<string>& inactives, const Properties& properties) : Task(properties), inactives(inactives)
{
  addDependsOn(GraphMergeTask::name);
  addDependsOn(MetricHunterTask::name);
}

SONAR2GRAPH_TASK(java)

Sonar2GraphTask::Sonar2GraphTask(const Properties& properties) : Task(properties)
{
  addDependsOn(JAN2limTask::name);
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
