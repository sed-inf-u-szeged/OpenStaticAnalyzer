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

#include <boost/interprocess/sync/scoped_lock.hpp>
#include "JarWrapper.h"
#include "common/inc/FileSup.h"
#include "common/inc/PlatformDependentDefines.h"
#include "AbstractWrapperLib/inc/paramsup/ParamsupCommon.h"
#include "AbstractWrapperLib/inc/messages.h"
#include "Environment.h"
#include <boost/filesystem/path.hpp>
#include <boost/interprocess/sync/file_lock.hpp>
#include <boost/interprocess/sync/sharable_lock.hpp>

#include <stdio.h>
#include <stdlib.h>
#include <list>
#include <string>
#include <sstream>
#include <iostream>
#include <fstream>
#include <set>
#include <string.h>

using namespace std;
using namespace common;
using namespace boost::interprocess;

#define BUFFERSIZE 4096

#define PROG_NAME                           "JarWrapper"
#define ORIG_PROG                           "jar"
#define EXEWRAPPERSECTION                   "EXEWRAPPER"

namespace ColumbusWrappers {

  JarWrapper::JarWrapper(std::string fname) : AbstractWrapper(fname)
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

  bool JarWrapper::loadLogFile(){
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

  bool JarWrapper::process(int argc, char** argv){
    try {
      // Check the wrapper environment 
      char* env = getenv("WRAPPER_ENVIRONMENT");
      if (env == NULL){
        writeErrorMsg(PROG_NAME, CMSG_JAVA_DONT_USE_WITHOUT_WRAPPER_ENVIRONMENT);
        return false;
      }

      if (!loadLogFile())
        return false;

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

      char buffer[BUFFERSIZE];
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
      string tool_name = ORIG_PROG;

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

      string cwd = common::getCwd();

      string params="";
      string output="";
      std::list<string> inputDirs;
      bool updateArchive = false;
      for (int i=1; i<argc; i++){
        if (strncmp(argv[i],"-C",2) == 0) {
          string path;
          common::pathCanonicalize(path, argv[i+1]);
          inputDirs.push_back(path);
        }

      if ( string(argv[i]).find("*") != string::npos) {
        size_t lastSlashPos = common::correctDirDivs(argv[i]).find_last_of(DIRDIVCHAR);
        if (lastSlashPos == string::npos){
            params += " " + string(argv[i]);
        } else {
            params += " " CL_PAR_PLUS + string(argv[i]).substr(0,lastSlashPos) + CL_PAR_PLUS + string(argv[i]).substr(lastSlashPos, string(argv[i]).length());
        }
        continue;
      }

        if (common::pathFileExists(common::pathRemoveFileSpec(argv[i]), true)) {
          params+= " " CL_PAR_PLUS+ string(argv[i]) + CL_PAR_PLUS;
        } else {
          params+= " " + string(argv[i]);
        }

        if (i==1) {
          if (strchr(argv[i],'u')) {
            updateArchive = true;
          }
          params += "v";//verbose
        }
        else if (i==2)
          output = argv[2];
      }
      inputDirs.push_back(cwd);

      string jar_log = getRollingFileName(temp_dir, "jar_log", "txt");
      string janlink_input = getRollingFileName(temp_dir, "JANLINK_input", "txt");

      //Execution of jar command
      string execJar = command_orig + params;
      writeMsgToFile(logfile.c_str(), PROG_NAME, WriteMsg::mlNormal, execJar.c_str());

#ifdef __unix__
      common::run(execJar, false, CL_PAR_PLUS + jar_log + CL_PAR_PLUS);
#else
      common::run(execJar, false, jar_log);
#endif

      bool needToLink = false;
      ifstream ifs(jar_log.c_str());
      ofstream ofs(janlink_input.c_str());

      char columbus_dir[BUFFERSIZE];
      common::getPrivateProfileString("JAN", "columbusResultDir", "", columbus_dir, BUFFERSIZE, configfile.c_str());

      boost::filesystem::path outputJarPath(output);
      string outputLjsi = (outputJarPath.parent_path() / string(columbus_dir) / (outputJarPath.filename().string() + ".ljsi")).string();

      if (!ifs.is_open()) {
        writeMsgToFile(logfile.c_str(), PROG_NAME, WriteMsg::mlError, CMSG_JAVA_IO_OPEN_ERROR, jar_log.c_str());
        return false;
      } else if (!ofs.is_open()) {
        writeMsgToFile(logfile.c_str(), PROG_NAME, WriteMsg::mlError, CMSG_JAVA_IO_OPEN_ERROR, janlink_input.c_str());
        return false;
      } else {
        if (updateArchive) {
          string arch = outputLjsi;
          if (!common::pathIsAbsolute(arch.c_str())) {
            if (cwd[strlen(cwd.c_str())-1] != DIRDIVCHAR)
              arch = DIRDIVCHAR + arch;
            arch = cwd + arch;
          }
          if (common::pathFileExists(arch, false))
            ofs << arch.c_str() << endl;
        }
        //Determining the list file of the JANLink
        string tmp;
        while (getline(ifs, tmp)) {
          if (tmp.empty())
            continue;
          if (tmp.compare(0,8,"adding: ")==0) {
            size_t pos = tmp.find(".class(");
            if (pos!=string::npos) {
              tmp = tmp.substr(8, pos-8) + ".jsi";
              size_t last_slash_pos = tmp.find_last_of("/\\",tmp.length());
              if (last_slash_pos == string::npos){
                last_slash_pos = 0;
              }
              tmp = tmp.substr(0,last_slash_pos) + DIRDIVSTRING + string(columbus_dir) + DIRDIVSTRING + tmp.substr(last_slash_pos);
              for (std::list<string>::iterator it = inputDirs.begin(); it != inputDirs.end(); ++it) {
                if (common::pathFileExists(*it + DIRDIVSTRING + tmp, false)) {
                  ofs << it->c_str() << DIRDIVSTRING <<  tmp << std::endl;
                  needToLink = true;
                  break;
                }
              }
            }
          }
        }
        ifs.close();
        ofs.close();
      }

      int ret = 0;
      if (needToLink) {
        string outputLjsiDir = boost::filesystem::path(outputLjsi).parent_path().string();
        if (!common::pathFileExists(outputLjsiDir, true)) {
          common::makeDirectory(outputLjsiDir);
        }
        //Execution of JANLink
        string execJANLink = 
          CL_PAR_PLUS "JANLink" CL_PAR_PLUS
          " -out:" CL_PAR_PLUS + outputLjsi + CL_PAR_PLUS
          + " -inputlist:" CL_PAR_PLUS + janlink_input + CL_PAR_PLUS;

        char statfile[BUFFERSIZE];
        getPrivateProfileString("STATISTICS", "janlinkStatisticFile", NULL, statfile, BUFFERSIZE, configfile.c_str(), true);
        string stat(statfile);

        if (!stat.empty()){
          execJANLink += " -stat:" CL_PAR_PLUS + string(log_dir) + DIRDIVSTRING + stat + CL_PAR_PLUS;
        }

        writeMsgToFile(logfile.c_str(), PROG_NAME, WriteMsg::mlNormal, execJANLink.c_str());

#ifdef __unix__
        ret = common::run(execJANLink, false, CL_PAR_PLUS + logfile + CL_PAR_PLUS, CL_PAR_PLUS + logfile + CL_PAR_PLUS);
#else
        ret = common::run(execJANLink, false, logfile, logfile);
#endif

        //Writing out the name of the output into the superlink file
        string superlink = string(log_dir) + DIRDIVSTRING "superlinklist.txt";
        string lockFile = getLockFileName(superlink);
        ofstream ofs2;
        ofstream lock(lockFile.c_str());
        
        file_lock f_lock(lockFile.c_str());

        ofs2.open(superlink.c_str(), ios::app);
        if (ofs2.is_open()) {
          //sets an exclusive lock on the file (no other processes can read or write it)
          scoped_lock<file_lock> e_lock(f_lock);


          string canonPath;
          common::pathCanonicalize(canonPath, outputLjsi);
          ofs2 << canonPath << endl;
          ofs2.close();
        }
        lock.close();
      }

      return ret ? false : true;

    } catch (...) {
      writeMsgToFile(logfile.c_str(), PROG_NAME, WriteMsg::mlError, CMSG_JAVA_UNKNOWN_EXCEPTION);
      return false;
    }
  }

} // namespace ColumbusWrappers
