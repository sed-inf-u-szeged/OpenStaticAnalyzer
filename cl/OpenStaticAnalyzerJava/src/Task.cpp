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
    string vulerabilityPath = (props.wrapperToolsDir / "vulnerability.jar").string();
    string androidPath = (props.wrapperToolsDir / "android.jar").string();

    string source_file_list = (props.tempDir / "source_file_list.lst").string();
    string cp_list = (props.tempDir / "cp_list.lst").string();

    string ljsi_file = (props.projectBaseDir / props.analysisOutputDir / (props.projectName + ".ljsi")).string();
    string fjsi_file = (props.projectBaseDir / props.analysisOutputDir / (props.projectName + ".fjsi")).string();
    
    vector<string> JANJvmOptionsV;
    split(props.JANJvmOptions, JANJvmOptionsV, ' ');
    sv.insert(sv.end(), JANJvmOptionsV.begin(), JANJvmOptionsV.end());

    sv.push_back("-jar");
    sv.push_back(JANPath);

    sv.push_back("-i");
    sv.push_back(props.projectBaseDir.string());

    sv.push_back("-r");

    if (props.runPMD){
      sv.push_back("-s");
      sv.push_back(source_file_list);

      sv.push_back("-u");
      sv.push_back(cp_list);
    }

    if (!props.javacOptions.empty()){
      sv.push_back("-j:|" + props.javacOptions);
    }
    
    sv.push_back("-j:-cp");
    sv.push_back("-j:" + vulerabilityPath);

    sv.push_back("-j:-cp");
    sv.push_back("-j:" + androidPath);

    sv.push_back("-c");
    sv.push_back(tmpConfig.string());

    sv.push_back("-o");
    sv.push_back(ljsi_file);


    checkedExec("java", sv, logger);
    
    copy_file(ljsi_file, (props.asgDir / (props.projectName + ".ljsi")).string());
    copy_file(fjsi_file, (props.asgDir / (props.projectName + ".fjsi")).string());

    ofstream outfile;

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

      sv.push_back("-Djava.ext.dirs=" + (props.wrapperToolsDir / "PMD" / "lib").string());

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



TASK_NAME_DEF( WrapperBasedAnalysisTask);

Task::ExecutionResult WrapperBasedAnalysisTask::execute()
{
  ExecutionResult result;
  ExecutionLogger logger(this, result);

  try {

    path wrapperWorkDir = props.columbusWrapperTmpDir;
    path wrapperWorkDirBin = wrapperWorkDir / "bin";
    path wrapperWorkDirLog = wrapperWorkDir / "log";
    path wrapperWorkDirTmp = wrapperWorkDir / "tmp";

    createDirectories(wrapperWorkDirBin, logger);
    createDirectories(wrapperWorkDirLog, logger);
    createDirectories(wrapperWorkDirTmp, logger);


    copyBinaryExecutable(props.wrapperToolsDir, wrapperWorkDirBin, "GenericConfig");
    copyBinaryExecutable(props.wrapperToolsDir, wrapperWorkDirBin, "JANLink");
    
    string files[13] = {
      "JAN.jar",
      "JColumbusAntWrapper.jar",
      "OpenStaticAnalyzerAgent-4.0.jar",
      "OpenStaticAnalyzer-maven-plugin-4.0.jar",
      "OpenStaticAnalyzer-maven-plugin-4.0-V2.pom",
      "OpenStaticAnalyzer-maven-plugin-4.0-V3.pom",
      "OpenStaticAnalyzer-maven-plugin-4.0-V31.pom",
      "OpenStaticAnalyzer-Maven-plugin-mojo-executer-2.2.1.jar",
      "OpenStaticAnalyzer-Maven-plugin-mojo-executer-2.2.1.pom",
      "OpenStaticAnalyzer-Maven-plugin-mojo-executer-3.0.jar",
      "OpenStaticAnalyzer-Maven-plugin-mojo-executer-3.0.pom",
      "OpenStaticAnalyzer-Maven-plugin-mojo-executer-3.1.jar",
      "OpenStaticAnalyzer-Maven-plugin-mojo-executer-3.1.pom"
    };

    for(int i=0; i < 13; ++i ){
      copy_file(props.wrapperToolsDir / files[i], wrapperWorkDirBin / files[i]);
    }

    copyDirectory(props.wrapperToolsDir, wrapperWorkDirBin, "findbugs-3.0.0");
    copyDirectory(props.wrapperToolsDir, wrapperWorkDirBin, "PMD");


    SafeEnvironmentModifier wwd_env("WRAPPER_WORK_DIR", wrapperWorkDir, logger);
    SafeEnvironmentModifier wbd_env("WRAPPER_BIN_DIR", wrapperWorkDirBin, logger);
    SafeEnvironmentModifier wld_env("WRAPPER_LOG_DIR", wrapperWorkDirLog, logger);
    SafeEnvironmentModifier wtd_env("WRAPPER_TEMP_DIR", wrapperWorkDirTmp, logger);
    SafeEnvironmentModifier we_env("WRAPPER_ENVIRONMENT", props.tempDir, logger);
    SafeEnvironmentModifier wwdn_env("WRAPPER_WORK_DIR_NAME", props.columbusWrapperTmpDirName, logger);
    
    SafeEnvironmentModifier mo_env("MAVEN_OPTS", "-javaagent:" + (props.wrapperToolsDir / "OpenStaticAnalyzerAgent-4.0.jar").string(), logger);
    SafeEnvironmentModifier ssll_env("OSA_SUPERLINKLIST", props.superLinkList.string(), logger);
    SafeEnvironmentModifier sspmdll_env("OSA_SUPERPMDLIST", props.pmdXmlList.string(), logger);

    if(!props.mavenFilter.empty())
      SafeEnvironmentModifier swmf_env("OSA_WRAPPER_MAVEN_FILTER", props.mavenFilter, logger);
        
    SafeEnvironmentModifier smd_env("OSA_DIR", props.toolchainDir, logger);
    SafeEnvironmentModifier smld_env("OSA_LOG_DIR", wrapperWorkDirLog, logger);
    SafeEnvironmentModifier smwb_env("OSA_WRAPPER_BATCH", "", logger);
    SafeEnvironmentModifier pbd_env("PROJECT_BASE_DIR", props.projectBaseDir, logger);
    
    
    // -------------------------------------------------------------------------------------------------------------
    // ---------------------------------------------- GenericConfig ------------------------------------------------
    // -------------------------------------------------------------------------------------------------------------
    
    vector<string> sv;

    path configFile = wrapperWorkDirBin / "toolchain.ini";

    copy_file(props.wrapperToolsDir / "toolchain.ini", configFile);

    sv.push_back("-config:" + configFile.string());

    if (props.runPMD){
      sv.push_back("-option:OTHER_TOOLS/CALL_PMD=1");
    }else{
      sv.push_back("-option:OTHER_TOOLS/CALL_PMD=0");
    }

    if (!props.externalHardFilter.empty()) {
      sv.push_back("-option:JAN/hardFilter=" + props.externalHardFilter.string());
    }
    
    if (!props.JANJvmOptions.empty()){
      sv.push_back("-option:JAN_CALL/JAN_JVM_OPTS=" + props.JANJvmOptions);
    }
    
    checkedExec(wrapperWorkDirBin / "GenericConfig", sv, logger);

    // -------------------------------------------------------------------------------------------------------------
    // --------------------------------------- WrapperEnvironmentConfig --------------------------------------------
    // -------------------------------------------------------------------------------------------------------------
    
    path wrapperEnvironmentConfigPath = wrapperWorkDir / "wrapper_environment_config.ini";
    
    sv.clear();
    
#ifdef _WIN32
    string ext = ".exe";
#else
    string ext;
#endif

    wrapTool("ant" + ext, "AntWrapper" + ext,sv);
    wrapTool("javac" + ext, "JavacWrapper" + ext,sv);
    wrapTool("jar" + ext, "JarWrapper" + ext,sv);
      
    sv.push_back("-setWrappedRun");
    sv.push_back("ant" + ext);
    sv.push_back("0");

    sv.push_back("-setWrappedRun");
    sv.push_back("javac" + ext);
    sv.push_back("0");

    sv.push_back("-setWrappedRun");
    sv.push_back("jar" + ext);
    sv.push_back("0");
      
    sv.push_back("-setLogging");
    sv.push_back("ant" + ext);
    sv.push_back("1");
    sv.push_back("1");
      
    sv.push_back("-setLogging");
    sv.push_back("javac" + ext);
    sv.push_back("1");
    sv.push_back("1");
      
    sv.push_back("-setLogging");
    sv.push_back("jar" + ext);
    sv.push_back("1");
    sv.push_back("1");

    ofstream outfile;

#ifdef _WIN32
    outfile.open((wrapperWorkDirBin / "ant.bat").string().c_str());
    outfile << "ant.exe %%*";
    outfile.close();
    outfile.clear();
#endif

    string jColumbusAntWrapperJar = (wrapperWorkDirBin / "JColumbusAntWrapper.jar").string();

    outfile.open((wrapperWorkDir / "wrapper.xml").string().c_str());
    outfile 
      << "<project>" << endl
      << "  <taskdef name=\"javac\"    classname=\"org.jcolumbus.antwrapper.taskdefs.Javac\"    classpath=\"" + jColumbusAntWrapperJar + "\"/>" << endl
      << "  <taskdef name=\"zip\"      classname=\"org.jcolumbus.antwrapper.taskdefs.Zip\"      classpath=\"" + jColumbusAntWrapperJar + "\"/>" << endl
      << "  <taskdef name=\"jar\"      classname=\"org.jcolumbus.antwrapper.taskdefs.Jar\"      classpath=\"" + jColumbusAntWrapperJar + "\"/>" << endl
      << "  <taskdef name=\"war\"      classname=\"org.jcolumbus.antwrapper.taskdefs.War\"      classpath=\"" + jColumbusAntWrapperJar + "\"/>" << endl
      << "  <taskdef name=\"ear\"      classname=\"org.jcolumbus.antwrapper.taskdefs.Ear\"      classpath=\"" + jColumbusAntWrapperJar + "\"/>" << endl
      << "  <taskdef name=\"copy\"     classname=\"org.jcolumbus.antwrapper.taskdefs.Copy\"     classpath=\"" + jColumbusAntWrapperJar + "\"/>" << endl
      << "  <taskdef name=\"move\"     classname=\"org.jcolumbus.antwrapper.taskdefs.Move\"     classpath=\"" + jColumbusAntWrapperJar + "\"/>" << endl
      << "  <taskdef name=\"delete\"   classname=\"org.jcolumbus.antwrapper.taskdefs.Delete\"   classpath=\"" + jColumbusAntWrapperJar + "\"/>" << endl
      << "</project>" << endl;
    outfile.close();
    outfile.clear();


    sv.push_back("-workingdir");
    sv.push_back(wrapperWorkDir.string());
    sv.push_back(wrapperEnvironmentConfigPath.string());
    
    checkedExec(props.wrapperBinDir / "WrapperEnvironmentConfig", sv, logger);

    SafeEnvironmentModifier config_env(OSA_WRAPPER_CONFIG_FILE_ENV_VAR, wrapperEnvironmentConfigPath, logger);

    // ----------------------------------------------------------------------------------------------------------------------
    
    string oldPath;
    const char* pathValue = getenv("PATH");
    if (pathValue != NULL)
      oldPath = pathValue;
      
    SafeEnvironmentModifier path_env("PATH", (wrapperWorkDirBin.string() + PATH_SEPARATOR + oldPath).c_str(), logger, false);

    sv.clear();
    checkedExec(props.buildScript, sv, logger);
    
    if (exists(wrapperWorkDirLog / "Error.log")) {
      logstream << CMSG_WRAPPER_ERROR << "\n";
      result.setCriticalError();
    }

    if (exists(wrapperWorkDirLog / props.superLinkList.filename()))
      copy_file(wrapperWorkDirLog / props.superLinkList.filename(), props.superLinkList);
    if (exists(wrapperWorkDirLog / props.pmdXmlList.filename()))
      copy_file(wrapperWorkDirLog / props.pmdXmlList.filename(), props.pmdXmlList);
    

  } HANDLE_TASK_EXCEPTIONS
  return result;
}

void WrapperBasedAnalysisTask::wrapTool(const string& wrappedTool, const string& wrapperTool, vector<string>& sv ) const
{
  sv.push_back("-wraptools");
  sv.push_back(wrappedTool);
  sv.push_back(wrapperTool);
  copy_file(props.wrapperBinDir/wrapperTool, props.columbusWrapperTmpDir/"bin"/wrapperTool, copy_option::overwrite_if_exists);
  copy_file(props.wrapperBinDir/("exewrapper" BINARYEXT), props.columbusWrapperTmpDir/"bin"/wrappedTool);
}

WrapperBasedAnalysisTask::WrapperBasedAnalysisTask(const Properties& properties) : Task(properties)
{
  addDependsOn(CleanResultsTask::name);
}



TASK_NAME_DEF( RemoveWrapperBinsTask);

Task::ExecutionResult RemoveWrapperBinsTask::execute()
{
  ExecutionResult result;
  ExecutionLogger logger(this, result);

  try {
    
    path wrapperbin(LONGDIRPREFIXSTRING + (props.columbusWrapperTmpDir / "bin").wstring());
    logstream << "Removing directory: " << wrapperbin.string() << "\n";

    system::error_code errorcode;
    for(int i=0; i<3; i++){
      remove_all(wrapperbin, errorcode);
      if(errorcode.value() == system::errc::success)
        break;
    }

    logger.warningIfFail( errorcode.value() == system::errc::success, "Failed to remove wrapper bin directory. %s.\n", errorcode.message().c_str());

  } HANDLE_TASK_EXCEPTIONS
  return result;
}

RemoveWrapperBinsTask::RemoveWrapperBinsTask(const Properties& properties) : Task(properties)
{
  addDependsOn(WrapperBasedAnalysisTask::name);
}

TASK_NAME_DEF(CheckASGListTask);

Task::ExecutionResult CheckASGListTask::execute()
{
  ExecutionResult result;
  ExecutionLogger logger(this, result);

  try {

    if (!exists(props.superLinkList)){
      logstream << "ASG list file does not exist: " << props.superLinkList.string() << "!" << endl;
      result.setCriticalError();
    }

    ifstream filestr;
    filestr.open(props.superLinkList.string().c_str(), ios::ate | ios::binary);
    streamoff length = filestr.tellg();
    if ( 0 == length ){
      logstream << "ASG list file is empty: " << props.superLinkList.string() << "!" << endl;
      result.setCriticalError();
    }

    if(result.hasCriticalError()){
      return result;
    }
    
    path superLinkListOrig = props.superLinkList.string() + ".orig";

    copy_file(props.superLinkList, superLinkListOrig);
    
    vector<string> sv;
    addMessageLevel(sv);

    sv.push_back("-inputlist:" + superLinkListOrig.string());
    sv.push_back("-checklist:" + props.superLinkList.string());


    checkedExec(props.wrapperToolsDir / "JANLink", sv, logger);
    
  } HANDLE_TASK_EXCEPTIONS
  return result;
}

CheckASGListTask::CheckASGListTask(const Properties& properties) : Task(properties)
{
  addDependsOn(WrapperBasedAnalysisTask::name);
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
  addDependsOn(CheckASGListTask::name);
  addDependsOn(DirectoryBasedAnalysisTask::name);
}

TASK_NAME_DEF(SuperlinkTask);

Task::ExecutionResult SuperlinkTask::execute()
{
  ExecutionResult result;
  ExecutionLogger logger(this, result);

  try {

    vector<string> sv;
    addMessageLevel(sv);

    sv.push_back("-filterrefl");
    sv.push_back("-fltp:" + props.externalSoftFilter.string());
    sv.push_back("-inputlist:" + props.superLinkList.string());
    sv.push_back("-out:" + (props.asgDir / (props.projectName + ".ljsi")).string());
        
    checkedExec(props.wrapperToolsDir / "JANLink", sv, logger);
  } HANDLE_TASK_EXCEPTIONS
  return result;
}

SuperlinkTask::SuperlinkTask(const Properties& properties) : Task(properties)
{
  addDependsOn(JANFilterTask::name);
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
  addDependsOn(SuperlinkTask::name);
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
      checkedExec(props.wrapperToolsDir / "findbugs-3.0.0" / "bin" / ("findbugs" + fbExt), sv, logger);
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
}

TASK_NAME_DEF(GraphDumpTask);

Task::ExecutionResult GraphDumpTask::execute()
{
  ExecutionResult result;
  ExecutionLogger logger(this, result);
  try {
    
    vector<string> sv;
    addMessageLevel(sv);

    sv.push_back((props.projectTimedResultDir /  (props.projectName + ".graph")).string());
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

  } HANDLE_TASK_EXCEPTIONS
  return result;
}

ProfileTask::ProfileTask(const Properties& properties) : Task(properties)
{
  addDependsOn(JAN2limTask::name);
}
