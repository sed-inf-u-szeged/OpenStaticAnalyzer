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

#include "AntWrapper.h"
#include "common/inc/FileSup.h"
#include "common/inc/StringSup.h"
#include "common/inc/PlatformDependentDefines.h"
#include "AbstractWrapperLib/inc/paramsup/ParamsupCommon.h"
#include "AbstractWrapperLib/inc/messages.h"

#include <stdio.h>
#include <stdlib.h>
#include <list>
#include <string>
#include <set>
#include <sstream>
#include <iostream>
#include <fstream>
#include <string.h>
#include "Exception.h"

using namespace std;
using namespace common;

#define BUFFERSIZE 4096

#define PROG_NAME                           "AntWrapper"
#define ORIG_PROG                           "ant"
#define EXEWRAPPERSECTION                   "EXEWRAPPER"
#if defined(__unix__)
#define ANT_NAME "ant"
#else
#define ANT_NAME "ant.bat"
#endif

namespace ColumbusWrappers {

  AntWrapper::AntWrapper(std::string fname) : AbstractWrapper(fname)
  {
  }

  string logfile;

  bool AntWrapper::loadLogFile(){
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

  bool AntWrapper::printTempBuildXml(std::string file, std::string basedir, std::string defaultTarget, std::string projectName){
    stringstream stream;

    char* workingdir = getenv("WRAPPER_WORK_DIR");
    if (workingdir == NULL){
      writeMsgToFile(logfile.c_str(), PROG_NAME, WriteMsg::mlError, CMSG_JAVA_DONT_USE_WITHOUT_WRAPPER_ENVIRONMENT);
      return false;
    }

    stream << workingdir << DIRDIVCHAR <<"jcolumbus_build.xml";
    ofstream myBuild;
    myBuild.open (stream.str().c_str());
    if (!myBuild.is_open()){
      writeMsgToFile(logfile.c_str(), PROG_NAME, WriteMsg::mlError, CMSG_JAVA_IO_OPEN_ERROR, stream.str().c_str());
      return false;
    }

    myBuild << "<project basedir=\"" << basedir << "\"";
    if (projectName != "")
      myBuild << " name=\"" << projectName << "\"";
    if (defaultTarget != "")
      myBuild << " default=\"" << defaultTarget << "\"";
    myBuild << ">" << endl;
    myBuild << "<import file=\"" << workingdir << "/wrapper.xml\"" <<"/>" << endl;
    /*
    small hack because Ant creates 2 names for each imported target
    - target_name
    - prefix_name + separator + target_name
    by default prefix is the project's name (if defined) and the separator is "."
    and they can be overridden by the import task's "as" and "prefixSeparator" attributes (since Ant 1.8.0)
    the problem is that the second one can collide with an other existing target
    */
    // we use a fictive name to avoid conflicts of target names
    myBuild << "<import file=\"" << file << "\" as=\"\" prefixSeparator=\"___java_wrapper_separator___\"/>" << endl;
    // there is a bug (or bugfix?) between versions 1.8.2 and 1.8.3, so the previous "as" attribute can't be used
    // we hack the "prefixSeparator" attribute instead
    myBuild << "</project>" << endl;
    myBuild.close();
    return true;
  }

  int AntWrapper::buildOriginal(const std::string& antParameters){
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

      // Find the directory in which the exewrapper is. 
      string path = common::getExecutableProgramDir();
      if(path.length() && (path[path.length()-1] == DIRDIVCHAR))
        path = path.substr(0, path.length()-1);
      if(!path.length())  { // in worst case the wrapper directory is used
        writeMsgToFile(logfile.c_str(), PROG_NAME, WriteMsg::mlError, CMSG_JAVA_EXEWRAPPER_DIRECTORY_SEARCH_FAIL);
        path = bin_dir;
      }
      string skip_directory = path;

      // create tool_name for can be used in the config.
      string wrapped_filename = common::pathFindFileName(ANT_NAME);
      string tool_name = common::stringLower(wrapped_filename);
      tool_name = common::pathRemoveExtension(tool_name);

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
        // EXIT;
        return -1;
      }

      command_orig = CL_PAR_PLUS + command_orig + CL_PAR_PLUS;

      string params="";

      string execAnt = command_orig + " -f " CL_PAR_PLUS + string(workingdir) + "/jcolumbus_build.xml" CL_PAR_PLUS + antParameters;
      writeMsgToFile(logfile.c_str(), PROG_NAME, WriteMsg::mlNormal, execAnt.c_str());
      int ret = common::run(execAnt, false);

      return ret;
    } catch (...) {
      writeMsgToFile(logfile.c_str(), PROG_NAME, WriteMsg::mlError, CMSG_JAVA_UNKNOWN_EXCEPTION);
      return -1;
    }
  }

  string AntWrapper::getAttributeValue(const string& tag, const string attr) {
    string value = "";
    size_t pos = 0;

    if ((pos=tag.find(attr)) != string::npos){
      size_t nextqm=0;
      if ((nextqm=tag.substr(pos).find("\"")) != string::npos){
        size_t endqm=0;
        if ((endqm=tag.substr(pos+nextqm+1).find("\"")) != string::npos){
          value = tag.substr(pos+nextqm+1, endqm);
        }
      }
    }

    return value;
  }

  bool AntWrapper::parsingParameters(int argc, char** argv, std::string& antParameters, std::string& filename, std::string& basedir, std::string& defaultTarget, std::string& projectName){

    for (int i=1; i<argc; ++i){
      string tmp=argv[i];
      if (tmp.compare("-f")==0 || tmp.compare("-file")==0 || tmp.compare("-buildfile")==0){
        if (++i == argc){
          writeMsgToFile(logfile.c_str(), PROG_NAME, WriteMsg::mlError, CMSG_ANT_WRAPPER_MISSING_ANT_PARAMETER);
          return false;
        }
        filename = argv[i];
      } else {
        string param = string(argv[i]);
        replaceQuoteForQuoteWithBackslash(param);
        antParameters += " " CL_PAR_PLUS + param + CL_PAR_PLUS;
      }
    }

    if (!common::pathIsAbsolute(filename.c_str()))
      filename = common::getCwd() + "/" + filename;
    filename = correctDirDivs(filename);

    string buildfileDir = common::pathRemoveFileSpec(filename);
    ifstream in(filename.c_str());
    if (in.fail()) {
        writeMsgToFile(logfile.c_str(), PROG_NAME, WriteMsg::mlError, CMSG_JAVA_IO_OPEN_ERROR, filename.c_str());
      return false;
    }

    size_t beginPos = string::npos;
    size_t endPos = string::npos;
    string line;

    while (!in.eof()) {
      getline(in,line);
      line += '\n';

      if ((beginPos = line.find("<project")) != string::npos) {
        unsigned quotes = 0;
        size_t len = line.length();
        size_t i = beginPos;

        while (endPos == string::npos) {
          while (i < len) {
            if (line[i] == '"')
              quotes++;
            else if (line[i] == '>' && quotes%2 == 0) {
              endPos = i;
              break;
            }
            i++;
          }
          if (endPos == string::npos && !in.eof()) {
            string tmp;
            getline(in,tmp);
            line += tmp + '\n';
            len = line.length();
          } else
            break;
        }
        break;
      }
    }

    if (beginPos != string::npos && endPos != string::npos) {
      string project = line.substr(beginPos, endPos);

      defaultTarget = getAttributeValue(project, "default");

      string tmpBasedir = getAttributeValue(project, "basedir");
      if (common::pathIsAbsolute(tmpBasedir.c_str()))
        basedir = tmpBasedir;
      else {
        basedir = buildfileDir;
        if (tmpBasedir[0] && tmpBasedir.compare(".") != 0)
          basedir += "/" + tmpBasedir;
      }

      projectName = getAttributeValue(project, "name");

    } else {
      writeMsgToFile(logfile.c_str(), PROG_NAME, WriteMsg::mlError, CMSG_JAR_WRAPPER_XML_PARSING_ERROR, filename.c_str());
      return false;
    }

    return true;
  }

  bool AntWrapper::process(int argc, char** argv){

    char* env = getenv("WRAPPER_ENVIRONMENT");
    if (env == NULL){
      writeErrorMsg(PROG_NAME, CMSG_JAVA_DONT_USE_WITHOUT_WRAPPER_ENVIRONMENT);
      return false;
    }

    if (!loadLogFile())
      return false;

    string file = "build.xml";
    string baseDir=".";
    string defaultTarget="";
    string projectName="";
    string antParameters="";

    if (!parsingParameters(argc, argv, antParameters, file, baseDir, defaultTarget, projectName))
      return false;
    if (!printTempBuildXml(file, baseDir, defaultTarget, projectName))
      return false;
    buildOriginal (antParameters);
    return true;
  }
} // namespace ColumbusWrappers
