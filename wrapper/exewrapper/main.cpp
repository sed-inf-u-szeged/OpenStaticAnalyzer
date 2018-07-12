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

#include "messages.h"

#include <cstdlib>
#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <vector>
#include <set>
#include <list>
#include <ctime>

#include <common/inc/FileSup.h>
#include <common/inc/StringSup.h>
#include <common/inc/WriteMessage.h>
#include <WrapperEnvironmentConfig/WrapperEnvironmentCommon.h>
#include <common/inc/PlatformDependentDefines.h>
#include <common/inc/DirectoryFilter.h>
#include <Environment.h>

#include <boost/regex.hpp>

using namespace std;
using namespace common;

#define EXIT if (doWrapp) \
              common::unsetEnvironmentVariable(OSA_INEXEWRAPPER_ENV_VAR); \
             return -1

#define BUFFERSIZE 8192

char buffer[BUFFERSIZE];
string config_file;
bool casesensitive = false;
string bin_dir;
bool isFromBinDir = false;
string binFromBinDir;
string orig_ant_executable="ant.bat";

DirectoryFilter dirFilter;
DirectoryFilter paramFilter;


/**
 * @brief Collects the wrapper tool which is belonging to the given wrapped tool.
 * @param wrappertool        [out] The name of the wrapper tool.
 * @param progname           [in] The given wrapped tool.
 */
void getWrapperTool(string& wrappertool, string progname, const string& wrapperworkdirname) {
  char wrappedtools[BUFFERSIZE];
  getPrivateProfileString(STARTWRAPPERSECTION, WRAPPED_TO_WRAPPER, NULL, wrappedtools, BUFFERSIZE, config_file.c_str(), casesensitive);
  string wrapstring(wrappedtools);
  vector<string> wraps;
  vector<string>::const_iterator it3;
  split(wrapstring, wraps, ';');
  for (it3 = wraps.begin(); it3 != wraps.end(); it3++) {

    if (it3->empty()) {
      continue;
    }

    size_t found = it3->find_first_of(',');
    string wd = it3->substr(0, found);
    string wr = "";
    if (found != string::npos) {
      wr = it3->substr(found+1, it3->length()-found-1);
    }
    
    LowerStringOnWindows(wd);
    LowerStringOnWindows(progname);

    if (wd == progname) {
      wrappertool = wr;
    } else {
      string dir, file;
      common::splitPath(progname, dir, file);
      size_t dirfound = dir.rfind(wrapperworkdirname);
      size_t binfound = dir.rfind("bin");
      if (dirfound != string::npos && binfound != string::npos && binfound > dirfound && wd == file) {
        isFromBinDir = true;
        binFromBinDir = file;
        wrappertool = wr;
      }
    }
  }
}

/**
 * @brief Collects what extra parameter wanted to insert and after which parameter.
 * @param paramVector        [out] Vector for (extra parameter - parameter) pairs.
 * @param section            [in] The name of the wrapped tool.
 */
void getExtraParamsAfterParams(vector<pair<string,string> >& paramVector, string section) {
  int numofextraparamsafterparams = getPrivateProfileInt(section.c_str(), NUMBER_OF_WRAPPED_PARAMS_AFTER_PARAMS, 0, config_file.c_str(), casesensitive);

  if (numofextraparamsafterparams == 0) {
    return;
  }

  for (int i = 1; i <= numofextraparamsafterparams; i++) {
    char tmp[BUFFERSIZE];
    string key(WRAPPEDTOOL_EXTRA_PARAM_AFTER_PARAM);
    key = key + "_" + toString(i);
    getPrivateProfileString(section.c_str(), key.c_str(), NULL, tmp, BUFFERSIZE, config_file.c_str(), casesensitive);
    string val(tmp);
    vector<string> tmpVec;
    split(val, tmpVec, ',');
    paramVector.push_back(make_pair(tmpVec[0],tmpVec[1]));
  }
}

/**
 * @brief Collects values from WRAPPERTOOL_EXTRA_PARAM_*, WRAPPEDTOOL_EXTRA_PARAM_TO_BEGIN_*, WRAPPEDTOOL_EXTRA_PARAM_TO_END_* or WRAPPEDTOOL_REMOVE_PARAM_*.
 * @param outVector        [out] The values of the given key.
 * @param section          [in] The name of the given section (wrapped tool name).
 * @param opt              [in] The name of the given key.
 * @param count            [in] The value of NUMBER_OF_WRAPPER_EXTRA_PARAMS, NUMBER_OF_WRAPPED_PARAMS_BEGIN, NUMBER_OF_WRAPPED_PARAMS_END or NUMBER_OF_REMOVE_PARAMS.
 */
void getValues(vector<string>& outVector, string section, const char* opt, int count) {
  if (count == 0) {
    return;
  }

  for (int i = 1; i <= count; i++) {
    char tmp[BUFFERSIZE];
    string key(opt);
    key = key + "_" + toString(i);
    getPrivateProfileString(section.c_str(), key.c_str(), NULL, tmp, BUFFERSIZE, config_file.c_str(), casesensitive);
    string val(tmp);
    if (!val.empty()) {
      outVector.push_back(val);
    }
  }
}

/**
 * @brief Writes timestamp and the given command to the given file.
 * @param file         [in out] The given file name.
 * @param position     [in] The place where the message is written out.
 * @param tool         [in] The given tool name.
 * @param command      [in] The given command.
 * @param prefix       [in] The given prefix of the message.
 */
void writeTimeStampAndCommand(string file, string position, string tool, vector<string> command, string prefix = "") {
  if(file.empty()) {
    return;
  }
  
  ofstream out(file.c_str(), ios::app);
  if(out.is_open()) {
    time_t rawtime;
    struct tm *timeinfo;

    time (&rawtime);
    timeinfo = localtime(&rawtime);
    string act_time = asctime(timeinfo);
    act_time.erase(std::remove(act_time.begin(), act_time.end(), '\n'), act_time.end());

    out << prefix;
    out << "[" << act_time << "]";
    out << position;

    if (!tool.empty()) {
      out << tool;
    }

    if(!command.empty()) {
      for (vector<string>::const_iterator it = command.begin(); it != command.end(); ++it) {
        out << " " + *it;
      }
    }
    out << endl;

    out.flush();
    out.close();
  }
}

/**
 * @brief The main function which is simulate and manipulate the running of a given program.
 */
int main(int argc, char **argv) {

#ifdef _WIN32
  casesensitive = false;
#endif

#ifdef __unix__
  casesensitive = true;
#endif

  string first_param=argv[0];
  string called_prog = first_param;

  called_prog = common::pathFindFileName(called_prog);
  std::string programExtension = pathFindExtension(first_param);

  char* debugfilename = getenv(COLUMBUS_EXEWRAPPER_DEBUG_ENV_VAR);
  if (debugfilename != NULL) {
    FILE* f = fopen(debugfilename, "at");
    if (f != NULL) {
      for (int i = 0; i < argc; ++i)
        fprintf(f, "ARG(%d):[%s]\n", i, argv[i]);

      fprintf(f, "Called prog:[%s]\n", called_prog.c_str());
      fclose(f);
    }
  }

  if (!casesensitive) {
    programExtension = common::stringLower(programExtension);
  }

  if (programExtension != "exe" ) {
    called_prog = first_param + ".exe";
  }

#ifdef _WIN32
  bool ant_bat_wrapping = false;
  if ( called_prog == "ant.exe" ){
    ant_bat_wrapping = true;
  }
#endif

  int ret = 0;
  bool runWrapper = false;
  bool needWrapper = true;

  char* bindir = getenv("WRAPPER_BIN_DIR");
  if (!bindir) {
    WriteMsg::write(CMSG_EXEWRAPPER_WRAPPER_BIN_DIR_NOT_SET);
    return -1;
  } else {
    bin_dir = common::removeQuotes(bindir);
  }

  char *configfile = getenv(OSA_WRAPPER_CONFIG_FILE_ENV_VAR);
  if (!configfile) {
    config_file = "";
  } else {
    config_file += configfile;
    config_file = common::removeQuotes(config_file);
  }

  bool doWrapp = true;
  if (getenv(OSA_INEXEWRAPPER_ENV_VAR)) {
    doWrapp = false;
  } else {
    common::setEnvironmentVariable(OSA_INEXEWRAPPER_ENV_VAR,"1");
  }


  if (getenv("OSA_DISABLE_ANALYSIS")) {
    doWrapp = false;
  }

//Gets the path from where the wrapped tool has been called.
  string act_dir = common::getCwd();

//Gets the wrapper tool name
  string wrtool = "";

  const char* wrapperworkdirname = getenv("WRAPPER_WORK_DIR_NAME");
  if (wrapperworkdirname == NULL) {
      WriteMsg::write(CMSG_EXEWRAPPER_WRAPPER_WORK_DIR_NAME_NOT_SET);
      return EXIT_FAILURE;
  }
        
#ifdef _WIN32
  getWrapperTool(wrtool, called_prog, wrapperworkdirname);
#endif

#ifdef __unix__
  getWrapperTool(wrtool, argv[0], wrapperworkdirname);
#endif

  string command_wr = "";

  if(!wrtool.empty() && wrtool != "[none]") {
    command_wr = bin_dir + DIRDIVSTRING + wrtool;
    command_wr = common::indep_fullpath(command_wr);
  } else {
    needWrapper = false;
  }

  string prog_name = argv[0];

#ifdef _WIN32
  prog_name = called_prog;
  if (ant_bat_wrapping){
    prog_name= orig_ant_executable;
  }
#endif

  if (isFromBinDir) {
    prog_name = binFromBinDir;
  }

  string section = "prog_" + prog_name;
#ifdef _WIN32
  section = "prog_" + called_prog;
#endif

  LowerStringOnWindows(section);

//Collect informations from config.ini file
  int wrap_log = getPrivateProfileInt(section.c_str(), WRAPPERTOOL_LOGGING, 1, config_file.c_str(), casesensitive);
  int run_orig = getPrivateProfileInt(section.c_str(), WRAPPEDTOOL_RUN, 1, config_file.c_str(), casesensitive);
  int wrap_alwaysrun = getPrivateProfileInt(section.c_str(), WRAPPERTOOL_ALWAYS_RUN, 0, config_file.c_str(), casesensitive);
  int wrap_first = getPrivateProfileInt(section.c_str(), WRAPPERTOOL_RUN_FIRST, 0, config_file.c_str(), casesensitive);
  int wrapper_can_cause_error = getPrivateProfileInt(WRAPPERSECTION, WRAPPER_CAN_CAUSE_ERROR, 0, config_file.c_str(), casesensitive);
  
  
  char tmpfltp[BUFFERSIZE];
  getPrivateProfileString(section.c_str(), WRAPPERTOOL_DIRECTORY_FILTER, NULL, tmpfltp, BUFFERSIZE, config_file.c_str(), casesensitive);
  string wrap_dirfilter(tmpfltp);

  char tmpret[BUFFERSIZE];
  getPrivateProfileString(section.c_str(), WRAPPEDTOOL_RETURN_SUCCESSFUL, NULL, tmpret, BUFFERSIZE, config_file.c_str(), casesensitive); 
  string wrapped_return(tmpret);

  int changed = getPrivateProfileInt(section.c_str(), CHANGE_ORIGINAL, 0, config_file.c_str(), casesensitive);

  char tmpparam[BUFFERSIZE];
  getPrivateProfileString(section.c_str(), WRAPPEDTOOL_PARAM_FILTER, NULL, tmpparam, BUFFERSIZE, config_file.c_str(), casesensitive);
  string paramfilter(tmpparam);

  int tmpcount = 0;
  vector<string> wrapperextraparams;
  tmpcount = getPrivateProfileInt(section.c_str(), NUMBER_OF_WRAPPER_EXTRA_PARAMS, 0, config_file.c_str(), casesensitive);
  getValues(wrapperextraparams, section, WRAPPERTOOL_EXTRA_PARAM, tmpcount);
  tmpcount = 0;

  vector<string> extraparamstobegin;
  tmpcount = getPrivateProfileInt(section.c_str(), NUMBER_OF_WRAPPED_PARAMS_BEGIN, 0, config_file.c_str(), casesensitive);
  getValues(extraparamstobegin, section, WRAPPEDTOOL_EXTRA_PARAM_TO_BEGIN, tmpcount);
  tmpcount = 0;

  vector<string> extraparamstoend;
  tmpcount = getPrivateProfileInt(section.c_str(), NUMBER_OF_WRAPPED_PARAMS_END, 0, config_file.c_str(), casesensitive);
  getValues(extraparamstoend, section, WRAPPEDTOOL_EXTRA_PARAM_TO_END, tmpcount);
  tmpcount = 0;

  vector<string> removeparams;
  tmpcount = getPrivateProfileInt(section.c_str(), NUMBER_OF_REMOVE_PARAMS, 0, config_file.c_str(), casesensitive);
  getValues(removeparams, section, WRAPPEDTOOL_REMOVE_PARAM, tmpcount);
  tmpcount = 0;

  vector<pair<string,string> > extraparamsafterparams;
  getExtraParamsAfterParams(extraparamsafterparams, section);

//Gets the wrapped tool name
  string wrapped_filename = common::pathFindFileName(argv[0]);

#ifdef _WIN32
   wrapped_filename = common::pathFindFileName(called_prog);
   if ( ant_bat_wrapping ) {
     wrapped_filename = common::pathFindFileName(orig_ant_executable);
   }
#endif

// temporary hack BEGIN
#ifdef _WIN32
  bool isLib = false;
  string tool_name = common::stringLower(called_prog);
  if (ant_bat_wrapping){
    tool_name = common::stringLower(orig_ant_executable);
  }
  common::correctDirDivs(tool_name);
  string dir, prg;
  size_t found = tool_name.find_last_of(DIRDIVCHAR);
  if (found == string::npos) {
    prg = tool_name;
    dir = "";
  } else {
    prg = tool_name.substr(found+1, tool_name.length()-found-1);
    dir = tool_name.substr(0, found);
  }
  if (prg == "lib" || prg == "lib.exe") {
    if (!dir.empty()) {
      prog_name = dir + DIRDIVSTRING + "link.exe";
    } else {
      prog_name = "link.exe";
    }
    isLib = true;
  }
#endif
// temporary hack END

  string orig_command;

//Finds the original tool
  if (changed) {
    orig_command = prog_name + "_orig";
  } else {
    char orig_tool[BUFFERSIZE];
    getPrivateProfileString(section.c_str(), ORIGINAL_TOOL, NULL, orig_tool, BUFFERSIZE, config_file.c_str(), casesensitive);
    if (orig_tool[0] == '\0') {
      orig_command = findFile(wrapped_filename.c_str(), bin_dir.c_str());
    } else {
      orig_command = orig_tool;
    }
  }

  if (orig_command.empty()) {
    WriteMsg::write(CMSG_EXEWRAPPER_ORIG_TOOL_NOT_FOUND, argv[0]);
    EXIT;
  }

  if (debugfilename != NULL) {
    FILE* f = fopen(debugfilename, "at");
    if (f != NULL) {
      fprintf(f, "Original tool:[%s]\n", orig_command.c_str());
      fclose(f);
    }
  }


  string wrappedExe = orig_command;

  string origparams = "";
  std::vector<std::string> origParamVector;
  std::vector<std::string> wrapperParamVector;
  list<string> paramlist;

  wrapperParamVector.push_back(wrappedExe);

  for (int i = 1; i < argc; i++) {
    origparams += string(argv[i]) + " ";
    origParamVector.push_back(argv[i]);
    paramlist.push_back(argv[i]);
  }


//Manipulate the parameter lists of the wrapped tool and the wrapper tool
  if (!extraparamstobegin.empty()) {
    vector<string>::const_iterator it;
    for (it = extraparamstobegin.begin(); it != extraparamstobegin.end(); it++) {
      paramlist.push_front(*it);
    }
  }


  if (!extraparamstoend.empty()) {
    vector<string>::const_iterator it;
    for (it = extraparamstoend.begin(); it != extraparamstoend.end(); it++) {
      paramlist.push_back(*it);
    }
  }


  if (!extraparamsafterparams.empty()) {
    vector<pair<string,string> >::const_iterator it;
    for (it = extraparamsafterparams.begin(); it != extraparamsafterparams.end(); it++) {
      list<string>::iterator itp;
      for(itp = paramlist.begin(); itp != paramlist.end(); itp++) {
        string actp = *itp;
        list<string>::iterator actit = itp;
        boost::regex re(it->second.c_str());
        if(boost::regex_search(actp, re)) {
          ++actit;
          if(actit != paramlist.end()) {
            paramlist.insert(actit, it->first);
          } else {
            paramlist.push_back(it->first);
          }
          
        }
      }
    }
  }


  if (!removeparams.empty()) {
    vector<string>::const_iterator it;
    std::set<std::string> paramset;
    for (it = removeparams.begin(); it != removeparams.end(); it++) {
      list<string>::iterator itp;
      for(itp = paramlist.begin(); itp != paramlist.end(); itp++) {
        string actp = *itp;
        boost::regex re(it->c_str());
        if(boost::regex_search(actp, re)) {
          paramset.insert(actp);
        }
      }
    }
    set<string>::iterator setit;
    for(setit = paramset.begin(); setit != paramset.end(); setit++) {
      paramlist.remove(*setit);
    }
  }


  if (needWrapper && !wrapperextraparams.empty()) {
    vector<string>::const_iterator it;
    for (it = wrapperextraparams.begin(); it != wrapperextraparams.end(); it++) {
      wrapperParamVector.push_back(*it);
    }
  }

//Sets the parameter list
  list<string>::iterator paramit;
  for (paramit = paramlist.begin(); paramit != paramlist.end(); ++paramit) {
    wrapperParamVector.push_back(*paramit);
  }

//Sets the wrapper command and the wrapped (original) command
  string wrapperCommand = command_wr;

// temporary hack BEGIN
#ifdef _WIN32
  if(isLib) {
    origParamVector.push_back("/LIB");
  }
#endif
// temporary hack END


//Sets filter for wrapper tool
  if (needWrapper && !wrap_dirfilter.empty()) {
    dirFilter.openFilterFile(wrap_dirfilter);
    if (!dirFilter.isFilteredOut(act_dir)) {
      runWrapper = true;
    }
  } else if (needWrapper && !paramfilter.empty()) {
    paramFilter.openFilterFile(paramfilter);
    if (!paramFilter.isFilteredOut(origparams)) {
      runWrapper = true;
    }
  } else if (needWrapper) {
    runWrapper = true;
  } else {
    runWrapper = false;
  }

//Sets logging
  char* logdir_env = getenv("WRAPPER_LOG_DIR");
  string logfile;
  string logdir;
  if (logdir_env != NULL) {
    logdir = logdir_env;
    logfile = logdir;
  }
  
  char tmplog[BUFFERSIZE];
  getPrivateProfileString(WRAPPERSECTION, WRAPPER_LOG_FILE, NULL, tmplog, BUFFERSIZE, config_file.c_str(), casesensitive);
  logfile = common::removeQuotes(logfile) + DIRDIVSTRING + tmplog;
  logfile = common::indep_fullpath(logfile);

  string wrapperlog;
  string wpd_log;
  string wrapperlogForRun;
  if(wrap_log) {
    wrapperlog = logfile;
    wrapperlogForRun = logfile;
  }

  if(run_orig) {
    if (doWrapp) {
      writeTimeStampAndCommand(logfile, "[exewrapper][ORIG] ", prog_name, origParamVector, "[INFO]");
    } else {
      writeTimeStampAndCommand(logfile, "[exewrapper][ORIG*] ", prog_name, origParamVector, "[INFO]");
    }
  }

  int wr_ret = 0;

  if (!runWrapper) {
      vector<string> retvector;
      retvector.push_back(CMSG_EXEWRAPPER_NO_NEED_TO_RUN_WRAPPER);
      writeTimeStampAndCommand(wrapperlog, "[exewrapper][WRAPPER]", "", retvector, "[WARNING]");
  }

//Runs wrapper tool and wrapped tool
  if (!run_orig) {
    if (doWrapp && runWrapper) {
      writeTimeStampAndCommand(wrapperlog, "[exewrapper][WRAPPER] ", wrapperCommand, wrapperParamVector, "[INFO]");
      ret = wr_ret = run(wrapperCommand, wrapperParamVector, wrapperlogForRun, wrapperlogForRun);
    }
  } else {
    if (wrap_first) {
      if (doWrapp && runWrapper) {
        writeTimeStampAndCommand(wrapperlog, "[exewrapper][WRAPPER] ", wrapperCommand, wrapperParamVector, "[INFO]");
        wr_ret = run(wrapperCommand, wrapperParamVector, wrapperlogForRun, wrapperlogForRun);
      }
      ret = run(orig_command, origParamVector);

      if(!wrapped_return.empty()) {
        ret = str2int(wrapped_return);
      }
    } else {
      ret = run(orig_command, origParamVector);
      if (ret == 0) {
        if (doWrapp && runWrapper) {
          writeTimeStampAndCommand(wrapperlog, "[exewrapper][WRAPPER] ", wrapperCommand, wrapperParamVector, "[INFO]");
          wr_ret = run(wrapperCommand, wrapperParamVector, wrapperlogForRun, wrapperlogForRun);
        }
      } else {
        if (wrap_alwaysrun) {
          if (doWrapp && runWrapper) {
            writeTimeStampAndCommand(wrapperlog, "[exewrapper][WRAPPER] ", wrapperCommand, wrapperParamVector, "[INFO]");
            wr_ret = run(wrapperCommand, wrapperParamVector, wrapperlogForRun, wrapperlogForRun);
          }
        }
        vector<string> retvector;
        retvector.push_back(CMSG_EXEWRAPPER_ORIG_TOOL_FAILED);
        writeTimeStampAndCommand(wrapperlog, "[exewrapper][WRAPPER]", "", retvector, "[WARNING]");
      }

      if(!wrapped_return.empty()) {
        ret = str2int(wrapped_return);
      }
    }
  }

  if (doWrapp) {
    common::unsetEnvironmentVariable(OSA_INEXEWRAPPER_ENV_VAR);
  }

  if (wr_ret != 0) {
    vector<string> ret;
    ret.push_back(CMSG_EXEWRAPPER_TOOL_RETURNED);
    ret.push_back(toString(wr_ret));
    writeTimeStampAndCommand(wrapperlog, "[exewrapper][WRAPPER]", "", ret, "[ERROR]");
    if (!logdir.empty()) {
      FILE *error_file = fopen((logdir + DIRDIVSTRING "Error.log").c_str(), "at");
      if (error_file != NULL) {
        fprintf(error_file, "%s :%d\n", wrtool.c_str(), wr_ret);
        fclose(error_file);
      }
    }
  }

  if (wrapper_can_cause_error && wr_ret != 0) {
    ret = wr_ret;
  }
  
  writeTimeStampAndCommand(wrapperlog, "[exewrapper][WRAPPER RETURN VALUE] " + common::toString(ret), "", std::vector<std::string>(), "[INFO]");
  return ret;
}
