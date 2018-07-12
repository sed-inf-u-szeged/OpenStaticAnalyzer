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

#include "JavacWrapper.h"
#include "common/inc/FileSup.h"
#include "common/inc/PlatformDependentDefines.h"
#include "common/inc/StringSup.h"
#include "AbstractWrapperLib/inc/paramsup/ParamsupCommon.h"
#include "AbstractWrapperLib/inc/messages.h"

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <sstream>
#include <fstream>
#include <list>
#include <string>
#include <set>
#include <string.h>

using namespace std;
using namespace common;

#define BUFFERSIZE 4096

#define PROG_NAME                           "JavacWrapper"
#define ORIG_PROG                           "javac"
#define EXEWRAPPERSECTION                   "EXEWRAPPER"

namespace ColumbusWrappers {

  JavacWrapper::JavacWrapper(std::string fname) : AbstractWrapper(fname)
  {
  }
  string logfile;

  string getRollingFileName(string dir, string file, string ext){
    int i = 1;
    std::stringstream path;
    path << dir << DIRDIVSTRING << file << i << "." << ext;
    while ( common::pathFileExists(path.str(), false)){
      i++;
      path.str(std::string());
      path << dir << DIRDIVSTRING << file << i << "." << ext;
    }
    return path.str();
  }

  int runPMD(char* bin_dir, char* temp_dir, char* log_dir, string sourcelist, string cplist, char* jvm_opts){
    std::stringstream pmd;
    string pmd_dir = string(bin_dir) + DIRDIVSTRING + "PMD";

    pmd << "java " << jvm_opts;
    pmd << " " << CL_PAR_PLUS << "-Djava.ext.dirs=" << pmd_dir << DIRDIVSTRING << "lib" << CL_PAR_PLUS;
    pmd << " net.sourceforge.pmd.PMD";

    pmd << " -V";
    pmd << " -d " << CL_PAR_PLUS << sourcelist << CL_PAR_PLUS;
    pmd << " -f " << "xml";
    pmd << " -R " << CL_PAR_PLUS << pmd_dir << DIRDIVSTRING << "PMD-config.xml" << CL_PAR_PLUS;
    string pmd_out = getRollingFileName(temp_dir, "PMD-out", "xml");
    pmd << " -r " << CL_PAR_PLUS << pmd_out << CL_PAR_PLUS;
    pmd << " -auxclasspath " << CL_PAR_PLUS << "file:///" << cplist << CL_PAR_PLUS;
    //TODO encoding, version

    string pmd_list = string(log_dir) + DIRDIVSTRING + "pmd-output-list.txt";
    ofstream ofs(pmd_list.c_str(), fstream::app);

    if (!ofs.is_open()) {
      writeMsgToFile(logfile.c_str(), PROG_NAME, WriteMsg::mlError, CMSG_JAVA_IO_OPEN_ERROR, pmd_list.c_str());
    } else {
      ofs << pmd_out << endl;
      ofs.close();
    }

    string execPMD = pmd.str();

    writeMsgToFile(logfile.c_str(), PROG_NAME, WriteMsg::mlNormal, execPMD.c_str());

#ifdef __unix__
    int retPMD = common::run(execPMD, false, CL_PAR_PLUS + logfile + CL_PAR_PLUS, CL_PAR_PLUS + logfile + CL_PAR_PLUS);
#else
    int retPMD = common::run(execPMD, false, logfile, logfile);
#endif

    return retPMD;
  }

  int runOriginalJavac(char** argv, int argc, string command_orig){
    std::stringstream ss;
    ss << command_orig;
    for (int i = 1; i<argc; i++){
      string argvi = argv[i];
      if (argvi.find("*") != string::npos ) {
        size_t lastSlashPos = common::correctDirDivs(argvi).find_last_of(DIRDIVCHAR);
        if (lastSlashPos == string::npos){
          ss << " " << argvi;
        } else {
          ss << " " << CL_PAR_PLUS << argvi.substr(0,lastSlashPos) << CL_PAR_PLUS << argvi.substr(lastSlashPos,argvi.length());
        }
      } else {
        ss << " " << CL_PAR_PLUS << argv[i] << CL_PAR_PLUS;
      }
    }

    writeMsgToFile(logfile.c_str(), PROG_NAME, WriteMsg::mlNormal, ss.str().c_str());
    return common::run(ss.str(), false);
  }

  bool JavacWrapper::loadLogFile(){
    char* logdir = getenv("WRAPPER_LOG_DIR");
    if (logdir == NULL){
      writeErrorMsg(PROG_NAME, CMSG_JAVA_DONT_USE_WITHOUT_WRAPPER_ENVIRONMENT);
      return false;
    }
    logfile = string(logdir) + DIRDIVCHAR;

    if (common::pathFileExists(configfile, false)){
      char logfileName[BUFFERSIZE];
      getPrivateProfileString("ENVIRONMENT", "JWRAPPER_LOG", "default_wrapper.log", logfileName, BUFFERSIZE, configfile.c_str(), true);
      logfile += logfileName;
    } else {
      logfile += "default_wrapper.log";
    }
    return true;
  }

  bool JavacWrapper::process(int argc, char** argv){

    char* env = getenv("WRAPPER_ENVIRONMENT");
    if (env == NULL){
      writeErrorMsg(PROG_NAME, CMSG_JAVA_DONT_USE_WITHOUT_WRAPPER_ENVIRONMENT);
      return false;
    }

    if (!loadLogFile())
      return false;

    buildOriginal(argc, argv);
    return true;
  }

  int JavacWrapper::buildOriginal(int argc, char** argv){

    try {
      char buffer[BUFFERSIZE];
      // Check the wrapper environment 
      char* bin_dir = getenv("WRAPPER_BIN_DIR");
      if (bin_dir == NULL){
        writeMsgToFile(logfile.c_str(), PROG_NAME, WriteMsg::mlError, CMSG_JAVA_DONT_USE_WITHOUT_WRAPPER_ENVIRONMENT);
        return false;
      }
      char* workingdir = getenv("WRAPPER_WORK_DIR");
      if (workingdir == NULL){
        writeMsgToFile(logfile.c_str(), PROG_NAME, WriteMsg::mlError, CMSG_JAVA_DONT_USE_WITHOUT_WRAPPER_ENVIRONMENT);
        return false;
      }
      char* temp_dir = getenv("WRAPPER_TEMP_DIR");
      if (temp_dir == NULL){
        writeMsgToFile(logfile.c_str(), PROG_NAME, WriteMsg::mlError, CMSG_JAVA_DONT_USE_WITHOUT_WRAPPER_ENVIRONMENT);
        return false;
      }
      char* log_dir = getenv("WRAPPER_LOG_DIR");
      if (log_dir == NULL){
        writeMsgToFile(logfile.c_str(), PROG_NAME, WriteMsg::mlError, CMSG_JAVA_DONT_USE_WITHOUT_WRAPPER_ENVIRONMENT);
        return false;
      }

      // Find the directory in which the exewrapper is. 
      string path = common::getExecutableProgramDir();
      if(path.length() && (path[path.length()-1] == DIRDIVCHAR))
        path = path.substr(0, path.length()-1);
      if (!path.length()) { // in worst case the wrapper directory is used
        writeMsgToFile(logfile.c_str(), PROG_NAME, WriteMsg::mlError, CMSG_JAVA_EXEWRAPPER_DIRECTORY_SEARCH_FAIL);
        path = bin_dir;
      }
      string skip_directory = path;

      // create tool_name for can be used in the config.
      string wrapped_filename = ORIG_PROG;
      string tool_name = common::pathFindFileName(ORIG_PROG);

      // Searching for the original program
      string command_orig; 

      // Check wether the original program is set in the config or not.         
      char* orig_prog = buffer;
      common::getPrivateProfileString(EXEWRAPPERSECTION, tool_name.c_str(), "", orig_prog, BUFFERSIZE, configfile.c_str());
      if (!orig_prog[0])   // If it is not set in the config we try to find it in the path. 
        command_orig = common::findFile(wrapped_filename.c_str(), skip_directory.c_str());
      else                 // use the program which was set in the config
        command_orig = orig_prog;

      // In case we did not find the original exe we quit. 
      if (command_orig.empty()) {
        writeMsgToFile(logfile.c_str(), PROG_NAME, WriteMsg::mlError, CMSG_JAVA_ORIGINAL_PROGRAM_CANNOT_FIND, ORIG_PROG);
        return false;
      }

      command_orig = CL_PAR_PLUS + command_orig + CL_PAR_PLUS;

      string params_for_jan="";
      string destDir="";
      string inputs="";
      string argFiles = "";
      string cp = "";

      for (int i = 1; i<argc; i++){
        string argvi = argv[i];

        // if the actual argument is -d do the same as below, plus set the destDir
        if (argvi == "-d"){
          params_for_jan += "|" + argvi;
          destDir = argv[++i];
          params_for_jan +="|" + destDir;
          continue;
        }

        // get the last 5 character of the argument
        string java_end = "";
        if (argvi.length()>5 ){
          java_end=argvi.substr(argvi.length()-5,5);
        }

        // if the arg ends with .java and its an existing file concat it to the inputs
        if ( !java_end.compare(".java" ) && common::pathFileExists(argvi,false)){
          inputs +=" " CL_PAR_PLUS + argvi + CL_PAR_PLUS;

        // if the arg starts with @ and its an exesting file concat it to the arg files
        } else if ( !argvi.substr(0,1).compare("@") && common::pathFileExists(argvi.substr(1,argvi.size()),false))  {
          argFiles += " " CL_PAR_PLUS "@" + common::indep_fullpath(argvi.substr(1,argvi.size())) + CL_PAR_PLUS;

        // if the arg file contains * its an input with wildcard
        } else if (argvi.find("*") != string::npos) {
           inputs +=" " CL_PAR_PLUS + argvi + CL_PAR_PLUS;

        // else its an other parameter
        } else {
           params_for_jan +="|" + argvi;
        }
      }

      char jan_jvm_opts[BUFFERSIZE];
      getPrivateProfileString("JAN_CALL", "JAN_JVM_OPTS", NULL, jan_jvm_opts, BUFFERSIZE, configfile.c_str(), true);

      char jan_opts[BUFFERSIZE];
      getPrivateProfileString("JAN_CALL", "JAN_OPTIONS", NULL, jan_opts, BUFFERSIZE, configfile.c_str(), true);

      std::stringstream janalyzer;
      janalyzer << "java " << jan_jvm_opts << " -jar " CL_PAR_PLUS << bin_dir << DIRDIVCHAR << "JAN.jar" << CL_PAR_PLUS;


      janalyzer << " " << jan_opts;

      if ( inputs != ""){
        janalyzer << " -i " << inputs;
      }
      janalyzer << " -e " << CL_PAR_PLUS << workingdir << DIRDIVCHAR << "temp" << CL_PAR_PLUS;
      if (destDir != ""){
        janalyzer << " -d " << CL_PAR_PLUS << destDir << CL_PAR_PLUS;
      }
      char statfile[BUFFERSIZE];
      getPrivateProfileString("STATISTICS", "janStatisticFile", "", statfile, BUFFERSIZE, configfile.c_str(), false);
      string stat(statfile);

      if (!stat.empty()){
        janalyzer << " -t " << CL_PAR_PLUS << log_dir << DIRDIVCHAR << stat << CL_PAR_PLUS;
      }

      janalyzer << " -p ";

      if (params_for_jan != ""){
        janalyzer << " -j " << CL_PAR_PLUS << params_for_jan << CL_PAR_PLUS;
      }
      if (argFiles != ""){
        janalyzer << " -f " << argFiles;
      }

      int callPMD = getPrivateProfileInt("OTHER_TOOLS", "CALL_PMD", 0, configfile.c_str(), true);
      string sourcelist = getRollingFileName(temp_dir, "source_file_list", "lst");
      string cplist = getRollingFileName(temp_dir, "classpath_list", "lst");
      if (callPMD){
        janalyzer << " -s " << CL_PAR_PLUS << sourcelist << CL_PAR_PLUS;
        janalyzer << " -u " << CL_PAR_PLUS << cplist << CL_PAR_PLUS;
      }

      string execJAN = janalyzer.str();
      writeMsgToFile(logfile.c_str(), PROG_NAME, WriteMsg::mlNormal, execJAN.c_str());

      int JANret;
#ifdef __unix__
      JANret = common::run(execJAN, false, CL_PAR_PLUS + logfile + CL_PAR_PLUS, CL_PAR_PLUS + logfile + CL_PAR_PLUS);
#else
      JANret = common::run(execJAN, false, logfile, logfile);
#endif

      if (callPMD){
        if (runPMD(bin_dir,temp_dir, log_dir, sourcelist, cplist, jan_jvm_opts) != 0){
          writeMsgToFile(logfile.c_str(), PROG_NAME, WriteMsg::mlError, CMSG_JAVAC_WRAPPER_PMD_EXEC_ERROR);
        }
      }

      if ( runOriginalJavac(argv,argc,command_orig) != 0){
        writeMsgToFile(logfile.c_str(), PROG_NAME, WriteMsg::mlError, CMSG_JAVAC_WRAPPER_JAVAC_EXEC_ERROR);
      }

      return JANret;

    } catch (...) {
      writeMsgToFile(logfile.c_str(), PROG_NAME, WriteMsg::mlError, CMSG_JAVA_UNKNOWN_EXCEPTION);
      return false;
    }
  } 
} // namespace ColumbusWrappers
