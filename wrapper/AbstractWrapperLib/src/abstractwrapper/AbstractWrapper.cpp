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

#include <cstdlib>
#include <stdio.h>
#include <fstream>

#include <iostream>

#include "AbstractWrapperLib/inc/abstractwrapper/AbstractWrapper.h"
#include "AbstractWrapperLib/inc/paramsup/ParamsupCommon.h"
#include "AbstractWrapperLib/inc/messages.h"
#include <AnalyzerWrapperConfig/AnalyzerWrapperConfig.h>
#include <common/inc/FileSup.h>
#include <common/inc/PlatformDependentDefines.h>
#include <common/inc/WriteMessage.h>
#include <boost/filesystem.hpp>
#include <boost/regex.hpp>

#ifdef _WIN32
#include <Windows.h>
#endif

#if defined(__linux__) || defined(__APPLE__)
#include <unistd.h>
#endif

using namespace std;
using namespace common;

#define ABSTRACT_WRAPPER      "AbstractWrapper"

namespace ColumbusWrappers {

  AbstractWrapper::AbstractWrapper(string configfile) : mode(wrapper_unknown),
                                                        configfile(configfile),
                                                        input_paramvector(),
                                                        wrapper_work_dir(),
                                                        wrapper_bin_dir(),
                                                        wrapper_log_dir(),
                                                        wrapper_temp_dir(),
                                                        outputdir(),
                                                        configdir(),
                                                        messagelevel(3),
                                                        wrappedExe(),
                                                        instrument_enable(0),
                                                        prep_instrument(0)
  {
    readConfig();
    getEnvVars();
    WriteMsg::setMessageLevel(WriteMsg::MsgLevel(messagelevel));
    WriteMsg::setAutomaticFlush(true);
  }


  AbstractWrapper::~AbstractWrapper() {
  }


  void AbstractWrapper::readConfig() {
    outputdir = getConfigString(ALLSECTION, OUTPUT_DIR, ".columbus");
    configdir = getConfigString(ALLSECTION, CONFIG_DIR, NULL);
    messagelevel = getConfigInt(ALLSECTION, MESSAGE_LEVEL, 3);
    instrument_enable = getConfigInt(ALLSECTION, ENABLE_COMPILER_INSTRUMENT, 0);
    prep_instrument = getConfigInt(ALLSECTION, PREPARE_FOR_INSTRUMENT, 0);
  }


  void AbstractWrapper::getEnvVars() {
    char* wwd = getenv("WRAPPER_WORK_DIR");
    if (wwd != NULL) {
      wrapper_work_dir = wwd;
      wrapper_work_dir = common::removeQuotes(wrapper_work_dir);
    }

    char* wbd = getenv("WRAPPER_BIN_DIR");
    if (wbd != NULL) {
      wrapper_bin_dir = wbd;
      wrapper_bin_dir = common::removeQuotes(wrapper_bin_dir);
    }

    char* wld = getenv("WRAPPER_LOG_DIR");
    if (wld != NULL) {
      wrapper_log_dir = wld;
      wrapper_log_dir = common::removeQuotes(wrapper_log_dir);
    }

    char* wtd = getenv("WRAPPER_TEMP_DIR");
    if (wtd != NULL) {
      wrapper_temp_dir = wtd;
      wrapper_temp_dir = common::removeQuotes(wrapper_temp_dir);
    }
  }


  int AbstractWrapper::getConfigInt(const char* section, const char* key, int def) {
    bool casesensitive = false;
#if defined(__linux__) || defined(__APPLE__)
    casesensitive = true;
#endif
    return getPrivateProfileInt(section, key, def, configfile.c_str(), casesensitive);
  }


  string AbstractWrapper::getConfigString(const char* section, const char* key, const char* def) {
    bool casesensitive = false;
#if defined(__linux__) || defined(__APPLE__)
    casesensitive = true;
#endif
    char buffer[8192];
    getPrivateProfileString(section, key, const_cast<char*>(def), buffer, 8192, configfile.c_str(), casesensitive);
    return string(buffer);
  }


  void AbstractWrapper::getParamToSkip(const char* section, int numofparamtoskip, set<pair<string, int> >& paramSet) {
    if (numofparamtoskip > 0) {
      for (int i = 1; i <= numofparamtoskip; i++) {
        string key(PARAM_TO_SKIP);
        key = key + "_" + toString(i);
        string tmp = getConfigString(section, key.c_str(), NULL);
        if (!tmp.empty()) {
          size_t found = tmp.find_last_of(';');
          string regex = tmp.substr(0, found);
          int num = 0;
          if(found != string::npos) {
            num = str2int(tmp.substr(found+1, tmp.length()-found-1));
          }
          paramSet.insert(make_pair(regex, num));
        }
      }
    }
  }


  void AbstractWrapper::getExtraParam(const char* section, int numofextraparam, vector<string>& paramVector) {
    if (numofextraparam > 0) {
      for (int i = 1; i <= numofextraparam; i++) {
        string key(EXTRA_PARAM);
        key = key + "_" + toString(i);
        string val = getConfigString(section, key.c_str(), NULL);
        if (!val.empty()) {
          paramVector.push_back(val);
        }
      }
    }
  }


  bool AbstractWrapper::isObjectFile(string& name) const {
    string file;
    string ext;

    if (!common::splitExt(name, file, ext)) {
      return false;
    }

    if (mode == wrapper_gcc || mode == wrapper_ar || mode == wrapper_clang) {
      if (ext == ".o" || ext == ".ao" || ext == ".lo") {
        return true;
      }
    } else if (mode == wrapper_cl || mode == wrapper_lib) {
      if (common::stringLower(ext) == ".obj") {
        return true;
      }
    }

    return false;
  }


  bool AbstractWrapper::isArchiveFile(string& name) const {
    string file;
    string ext;

    if (!common::splitExt(name, file, ext)) {
      return false;
    }

    if (mode == wrapper_gcc || mode == wrapper_ar || mode == wrapper_clang) {
      if (ext == ".a") {
        return true;
      }
    } else if (mode == wrapper_cl || mode == wrapper_lib) {
      if (common::stringLower(ext) == ".lib") {
        return true;
      }
    }

    return false;
  }


  std::string AbstractWrapper::getObjectFileExtension() const {
    return ((mode == wrapper_gcc || mode == wrapper_clang) ? ".o" : ".obj");
  }


  static const std::string FixDirdivSign(const std::string& path) {
#ifdef _WIN32
    return replace(path.c_str(), "/", "\\");
#endif
    return path;
  }

  void AbstractWrapper::insertDir(std::string& file, bool createDir) const {
    insertDir(file, outputdir, createDir);
  }


  void AbstractWrapper::insertDir(std::string& file, const std::string& dirname, bool createDir) const {
    file = FixDirdivSign(file);

    if (pathIsDirectory(file)) {

      if (file[file.size()-1] == DIRDIVCHAR) {
        if (createDir)
          makeDirectory(file + dirname);
        file = file + dirname + DIRDIVSTRING;

      } else {
        file = file + DIRDIVSTRING + dirname;
        if (createDir)
          makeDirectory(file);
      }
    } else {
      size_t div_pos = file.find_last_of(DIRDIVCHAR);

      if (div_pos != std::string::npos) {
        if (createDir)
          makeDirectory(file.substr(0,div_pos) + DIRDIVSTRING + dirname);
        file.insert(div_pos, DIRDIVSTRING + dirname);

      } else {
        if (createDir)
          makeDirectory(dirname);
        file = dirname + DIRDIVSTRING + file;
      }
    }
  }


  void AbstractWrapper::replaceQuoteForQuoteWithBackslash(string& param) const
  {
    if (param.empty())
      return;
#if defined(__linux__) || defined(__APPLE__)
    param = replace(param.c_str(), "'", "'\\''");
#endif

#ifdef _WIN32
    param = replace(param.c_str(), "\"", "\\\"");
    if (param[param.length()-1] == '\\') {
      param += "\\";
    }
#endif
  }


  void AbstractWrapper::corrigateParamList(list<string>& paramlist) const {
#if defined(__linux__) || defined(__APPLE__)
    for (list<string>::iterator it = paramlist.begin(); it != paramlist.end(); it++) {
      replaceQuoteForQuoteWithBackslash(*it);
    }
#endif

#ifdef _WIN32
    for (list<string>::iterator it = paramlist.begin(); it != paramlist.end(); it++) {
      replaceQuoteForQuoteWithBackslash(*it);
    }
#endif
  }


  void AbstractWrapper::setParams(int argc, char **argv, list<string>& paramlist, set<pair<string, int> > paramtoskip)
  {
    if (argc == 0)
      return;

    wrappedExe = argv[0];
    writeDebugMsg(ABSTRACT_WRAPPER, CMSG_ABSTRACT_WRAPPER_ORIGINAL_WRAPPED_TOOL, argv[0]);

    for (int i = 1; i < argc; i++) {
      writeDebugMsg(ABSTRACT_WRAPPER,CMSG_ABSTRACT_WRAPPER_ORIGINAL_ARGUMENT_CL, i, argv[i]);
      string tmp = checkedRemoveQuotes(argv[i]);
      if (isCommandFile(tmp)) {
        processCommandFile(tmp);
        continue;
      }
      writeDebugMsg(ABSTRACT_WRAPPER, CMSG_ABSTRACT_WRAPPER_ARGUMENT_QUOTES_REMOVED, i, tmp.c_str());
      input_paramvector.push_back(tmp);
    }

    for (size_t i = 0; i < input_paramvector.size(); i++) {
      int step;
      if (checkSkipParam(input_paramvector[i], paramtoskip, step) && i + step < input_paramvector.size()) {
        writeDebugMsg(ABSTRACT_WRAPPER, CMSG_ABSTRACT_WRAPPER_SKIP_ARGUMENT, input_paramvector[i].c_str(), step);
        i = i + step;
        continue;
      }
      paramlist.push_back(input_paramvector[i]);
    }
  }


  string AbstractWrapper::checkedRemoveQuotes(const string& s) {
    string tmp = s;
    size_t size = tmp.length();

    if (size > 1) {
      if ((tmp[size-1] == '"' && tmp[0] == '"') || (tmp[size-1] == '\'' && tmp[0] == '\'')) {
        tmp = tmp.substr(1, size-2);
      }
    }

    return tmp;
  }


  bool AbstractWrapper::isCommandFile(string& param) {
    return (param.find_first_of("@") != string::npos&& common::stringLower(param.substr(0,6)) != "/base:" && common::stringLower(param.substr(0,7)) != "/entry:");
  }

  static void splitCommandfileArgs(const char* str1, std::vector<std::string>& out) {
    unsigned int first=0;
    unsigned int last=0;
    unsigned int length=strlen(str1);
    std::string inp(str1);
    bool inSingleQuotes=false;            // '
    bool inDoubleQuotes=false;            // "
    bool inBackSlashDoubleQuotes=false;   // \"
    bool inBackSlashSingleQuotes=false;   // \'
    int backslashes = 0;
    std::string output;
    while (last<length) {
      if (str1[last] == '\\') {
        if ((last+1 < length && (str1[last+1] == '\\' || str1[last+1] == '\"' || str1[last+1] == '\'')) || (last>0 && str1[last-1] == '\\')) {
          backslashes++;
        }
        if (backslashes % 2 == 0) {
          output += str1[last];
        }
        last++;
        continue;
      } else if (str1[last] == '\'') {
        if (last > 0 && str1[last-1] == '\\' && backslashes % 2 == 1) {
          inBackSlashSingleQuotes = !inBackSlashSingleQuotes;
          backslashes--;
          output += str1[last];
        } else if (!inDoubleQuotes) {
          inSingleQuotes = !inSingleQuotes;
        } else {
          output += str1[last];
        }
        last++;
        continue;
      } else if (str1[last] == '\"') {
        if (last > 0 && str1[last-1] == '\\' && backslashes % 2 == 1) {
          inBackSlashDoubleQuotes = !inBackSlashDoubleQuotes;
          backslashes--;
          output += str1[last];
        } else if (!inSingleQuotes) {
          inDoubleQuotes = !inDoubleQuotes;
        } else {
          output += str1[last];
        }
        last++;
        continue;
      } else if (inDoubleQuotes && str1[last] != '\"') {
        output += str1[last];
        last++;
        continue;
      } else if (inSingleQuotes && str1[last] != '\'') {
        output += str1[last];
        last++;
        continue;
      } else if (str1[last]== ' ') {
        if ((!inBackSlashDoubleQuotes && !inBackSlashSingleQuotes) || (!inDoubleQuotes && !inSingleQuotes)) {
          out.push_back(output);
          output.clear();
          do {
            last++;
          } while (str1[last] == ' ' && last<length);
          first=last;
          backslashes = 0;
          inSingleQuotes=false;            // '
          inDoubleQuotes=false;            // "
          inBackSlashDoubleQuotes=false;   // \"
          inBackSlashSingleQuotes=false;   // \'
          continue;
        }
      }
      output += str1[last];
      last++;
    } //while
    if (first<last) {
      out.push_back(output);
      output.clear();
      backslashes = 0;
    }
  }


  string checkUTF16LE(string filename) {
    string fname_new = filename + ".save";
    FILE* f=fopen(filename.c_str(), "r");
    bool unicode=false;
    if (f) {
      fseek(f,0, SEEK_END);
      if (ftell(f)>1) {
        fseek(f,0, SEEK_SET);
        char a,b;
        int read = fscanf(f, "%c%c", &a, &b);
        if (read != EOF && read == 2 && ((unsigned char)a)==255 && ((unsigned char)b)==254) {
          unicode=true;
        } else {
          //back to the beginning
          fseek(f,0, SEEK_SET);
        }
      }
    }
    if (unicode) {
      FILE * f2=fopen((filename+".tmp").c_str(), "w");
      char ch;
      while (fread(&ch, 1, 1, f)) {
        if (ch!=0 && ch!=13) 
          fprintf(f2, "%c", ch);
        fflush(f2);
      };
      fclose(f);
      fclose(f2);
      fname_new = filename+".tmp";
    } else {
      fname_new = filename;
    }
    return fname_new;
  }


  void AbstractWrapper::processCommandFile(string& param) {
    string filename = param.substr(param.find_first_of("@")+1);
    if (mode == wrapper_cl || mode == wrapper_lib) {
      filename = checkUTF16LE(filename);
    }
    ifstream is(filename.c_str());
    std::string line;
    while (is.good()) {
      string tmp="";
      getline(is, tmp);
      if((mode == wrapper_cl || mode == wrapper_lib) && tmp[0] == '#') {
        continue;
      }
      line+=" "+tmp;
    }
    is.close();

    writeDebugMsg(ABSTRACT_WRAPPER, CMSG_ABSTRACT_WRAPPER_INPUT_COMMAND_FILE, param.c_str(), line.c_str());

    vector<string> tmp;
    splitCommandfileArgs(line.c_str(), tmp);
    for (vector<string>::iterator it = tmp.begin(); it != tmp.end(); it++) {
      if (it->empty()) {
        continue;
      }
      writeDebugMsg(ABSTRACT_WRAPPER, CMSG_ABSTRACT_WRAPPER_SPLIT_COMMAND_FILE_ARGS, it->c_str());
      string tmps = *it;
      tmps = checkedRemoveQuotes(tmps);
      writeDebugMsg(ABSTRACT_WRAPPER, CMSG_ABSTRACT_WRAPPER_COMMAND_FILE_ARGS_QOUTES_REMOVED, tmps.c_str());
      if (isCommandFile(tmps)) {
        processCommandFile(tmps);
        continue;
      }
      input_paramvector.push_back(tmps);
    }
  }


  bool AbstractWrapper::checkSkipParam(string& param, set<pair<string, int> > paramtoskip, int& skip) {
    for (set<pair<string, int> >::const_iterator it = paramtoskip.begin(); it != paramtoskip.end(); it++) {
      boost::regex re(it->first);
      if(boost::regex_search(param, re)) {
        skip = it->second;
        return true;
      }
    }
    return false;
  }


  int AbstractWrapper::systemCall(const string& cmd, const string& filename) const {
    if (filename != "") {
      std::ofstream f(filename.c_str(), ios::out);
      f << cmd;
      f.close();
      return common::run(cmd, false, filename);
    } else {
      return common::run(cmd, false);
    }
  }

  int AbstractWrapper::systemCall(const string& executable, const vector<string>& arguments, const string& filename) const {
    if (filename != "") {
      std::ofstream f(filename.c_str(), ios::out);
      f << executable << "\n";
      for (const auto& arg : arguments)
        f << arg << "\n";
      f.close();
      return common::run(executable, arguments, filename);
    } else {
      return common::run(executable, arguments);
    }
  }


  int AbstractWrapper::silentSystemCall(const string& cmd) const {
    return common::run(cmd, true);
  }


  int AbstractWrapper::getCurrentProcessId() const {
    unsigned long procId = 0;

#ifdef _WIN32
    procId = GetCurrentProcessId();
#endif
#if defined(__linux__) || defined(__APPLE__)
    procId = (unsigned long)getpid();
#endif
    return procId;
  }
}
