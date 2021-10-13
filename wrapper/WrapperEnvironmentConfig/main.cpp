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

#include <string>
#include <vector>
#include <map>
#include <set>
#include <iostream>
#include <fstream>

#include "WrapperEnvironmentCommon.h"
#include <common/inc/FileSup.h>
#include <common/inc/StringSup.h>
#include <common/inc/WriteMessage.h>
#include <common/inc/PlatformDependentDefines.h>
#include <Exception.h>

#define BUFFERSIZE 8192

#define PROGRAM_NAME "WrapperEnvironmentConfig"
#define EXECUTABLE_NAME "WrapperEnvironmentConfig"

#include <MainCommon.h>

using namespace std;
using namespace common;

static list<string> files;

string configfile = WRAPPER_ENVIRONMENT_CONFIG;

string workingdir;

map<string, string> wraptools;
map<string, pair<string, string> > loggings;
map<string, string> wrappedrun;
map<string, string> alwaysrun;
map<string, string> wrapperfirst;
map<string, string> wrapperDirectoryFilter;
map<string, vector<string> > wrapperparams;
map<string, set<pair<string,string> > > wrappedparamsafter;
map<string, vector<string> > wrappedparamsbegin;
map<string, vector<string> > wrappedparamsend;
map<string, set<string> > wrappedparamsremove;
map<string, string> wrappedParamFilter;
map<string, string> wrappedreturn;
map<string, string> originaltools;

set<string> starttools;
set<string> stoptools;
string wraplog = "wraplog.log";
string wrapperml = "1";
bool wrapper_can_cause_error = false;

bool casesensitive = false;

//Callback functions for argument processing
static bool ppWorkingDir(const Option *o, char *argv[]) {
  workingdir = common::indep_fullpath(argv[0]);
  return true;
}

static bool ppWrapTools(const Option *o, char *argv[]) {
  LowerStringOnWindows(argv[0]);
  LowerStringOnWindows(argv[1]);
  wraptools.insert(make_pair(argv[0],argv[1]));
  return true;
}

static bool ppSetLogging(const Option *o, char *argv[]) {
  pair<string,string> tmppair = make_pair(argv[1],argv[2]);
  loggings.insert(make_pair(argv[0],tmppair));
  return true;
}

static bool ppSetWrappedRun(const Option *o, char *argv[]) {
  wrappedrun.insert(make_pair(argv[0], argv[1]));
  return true;
}

static bool ppSetAlwaysRun(const Option *o, char *argv[]) {
  alwaysrun.insert(make_pair(argv[0],argv[1]));
  return true;
}

static bool ppSetWrapperRunFirst(const Option *o, char *argv[]) {
  wrapperfirst.insert(make_pair(argv[0],argv[1]));
  return true;
}

static bool ppSetWrapperExtraParams(const Option *o, char *argv[]) {
  wrapperparams[argv[0]].push_back(argv[1]);
  return true;
}

static bool ppSetWrappedExtraParamAfterParam(const Option *o, char *argv[]) {
  wrappedparamsafter[argv[0]].insert(make_pair(argv[1],argv[2]));
  return true;
}

static bool ppSetWrappedExtraParamToBegin(const Option *o, char *argv[]) {
  wrappedparamsbegin[argv[0]].push_back(argv[1]);
  return true;
}

static bool ppSetWrappedExtraParamToEnd(const Option *o, char *argv[]) {
  wrappedparamsend[argv[0]].push_back(argv[1]);
  return true;
}

static bool ppSetWrappedRemoveParam(const Option *o, char *argv[]) {
  wrappedparamsremove[argv[0]].insert(argv[1]);
  return true;
}

static bool ppSetWrapperDirectoryFilter(const Option *o, char *argv[]) {
  string fltp = common::indep_fullpath(argv[1]);
  LowerStringOnWindows(fltp);
  wrapperDirectoryFilter.insert(make_pair(argv[0],fltp));
  return true;
}

static bool ppSetWrappedParamFilter(const Option *o, char *argv[]) {
  string fltp = common::indep_fullpath(argv[1]);
  LowerStringOnWindows(fltp);
  wrappedParamFilter.insert(make_pair(argv[0],fltp));
  return true;
}

static bool ppSetWrappedReturn(const Option *o, char *argv[]) {
  wrappedreturn.insert(make_pair(argv[0],argv[1]));
  return true;
}

static bool ppSetOriginal(const Option *o, char *argv[]) {
  string orig = common::indep_fullpath(argv[1]);
  originaltools.insert(make_pair(argv[0],orig));
  return true;
}

static bool ppStartTool(const Option *o, char *argv[]) {
  string start = common::indep_fullpath(argv[0]);
  starttools.insert(start);
  return true;
}

static bool ppStopTool(const Option *o, char *argv[]) {
  string stop = common::indep_fullpath(argv[0]);
  stoptools.insert(stop);
  return true;
}

static bool ppWrapperML(const Option *o, char *argv[]) {
  if(argv[0]) {
    wrapperml = argv[0];
  }
  return true;
}

static bool ppWrapLog(const Option *o, char *argv[]) {
  if(argv[0]) {
    wraplog = argv[0];
  }
  return true;
}
static bool ppWraperCanCauseError(const Option *o, char *argv[]) {
  wrapper_can_cause_error = true;
  return true;
}


static void ppFile(char *filename) {
  files.push_back(filename);
}

const Option OPTIONS_OBJ[] = {
  { false,  "-workingdir",                       1, "directory",                             0, OT_WS,    ppWorkingDir,                      NULL, "The path where the wrapper working dir will be created. e.g.: -workingdir dir"},
  { false,  "-wraptools",                        2, "wrappedtool wrappertool",               0, OT_WS,    ppWrapTools,                       NULL, "The pair of wrapped tool and wrapper tool. If no wrapper tool is needed, write \"[none]\". e.g.: -wraptools wrapped wrapper. If no wrapper tool type: [none]" },
  { false,  "-setLogging",                       3, "wrappedtool number{0,1} number{0,1}",   0, OT_WS,    ppSetLogging,                      NULL, "Set the logging of wrapped tool and wrapper tool. It is belonging to wrapped tool. e.g.: -setLogging wrapped 0|1 0|1"},
  { false,  "-setWrappedRun",                    2, "wrappedtool number{0,1}",               0, OT_WS,    ppSetWrappedRun,                   NULL, "Set whether the wrapped tool needs to run or not. It is belonging to wrapped tool. e.g.: -setWrappedRun wrapped 0|1"},
  { false,  "-setWrapperAlwaysRun",              2, "wrappedtool number{0,1}",               0, OT_WS,    ppSetAlwaysRun,                    NULL, "Set whether the running of wrapper tool depends on wrapped tool return or not. It is belonging to wrapped tool. e.g.: -setWrapperAlwaysRun wrapped 0|1"},
  { false,  "-setWrapperRunFirst",               2, "wrappedtool number{0,1}",               0, OT_WS,    ppSetWrapperRunFirst,              NULL, "Set whether the wrapper tool runs first or the wrapped tool. It is belonging to wrapped tool. e.g.: -setWrapperRunFirst wrapped 0|1"},
  { false,  "-setWrapperExtraParam",             2, "wrappedtool extraparam",                0, OT_WS,    ppSetWrapperExtraParams,           NULL, "Set what extra parameter want to insert before the wrapped tool parameters for the wrapper tool. It is belonging to wrapped tool. e.g.: -setWrapperExtraParam wrapped param"},
  { false,  "-setWrappedExtraParamAfterParam",   3, "wrappedtool param extraparam",          0, OT_WS,    ppSetWrappedExtraParamAfterParam,  NULL, "Set what extra parameter want to insert after a given parameter (it can be given by regular expression) for wrapped tool. It is belonging to wrapped tool. e.g.: -setWrappedExtraParamAfterParam wrapped extra param"},
  { false,  "-setWrappedExtraParamToBegin",      2, "wrappedtool extraparam",                0, OT_WS,    ppSetWrappedExtraParamToBegin,     NULL, "Set what extra parameter want to insert before the wrapped tool parameters for wrapped tool. It is belonging to wrapped tool. e.g.: -setWrappedExtraParamToBegin wrapped extra"},
  { false,  "-setWrappedExtraParamToEnd",        2, "wrappedtool extraparam",                0, OT_WS,    ppSetWrappedExtraParamToEnd,       NULL, "Set what extra parameter want to insert after the wrapped tool parameters for wrapped tool. It is belonging to wrapped tool. e.g.: -setWrappedExtraParamToEnd wrapped extra"},
  { false,  "-setWrappedRemoveParam",            2, "wrappedtool remove",                    0, OT_WS,    ppSetWrappedRemoveParam,           NULL, "Set what parameter wanted to remove from wrapped tool parameters. It can be given by regular expression. It is belonging to wrapped tool. e.g.: -setWrappedRemoveParam wrapped remove"},
  { false,  "-setWrapperDirectoryFilter",        2, "wrappedtool filepath",                  0, OT_WS,    ppSetWrapperDirectoryFilter,       NULL, "Set the filter file which can be used by wrapper tool. It is belonging to wrapped tool. e.g.: -setWrapperUseFilterFile wrapped filepath"},
  { false,  "-setWrappedParamlistFilter",        2, "wrappedtool filepath",                  0, OT_WS,    ppSetWrappedParamFilter,           NULL, "Set regular expressions in a file. If any of them is matched with the parameter list of the wrapped tool, the wrapper tool runs. It is belonging to wrapped tool. e.g.: -setWrappedFilterRegex wrapped filepath"},
  { false,  "-setWrappedReturn",                 2, "wrappedtool return",                    0, OT_WS,    ppSetWrappedReturn,                NULL, "Set return value for wrapped tool which differs from original return value. It is belonging to wrapped tool. e.g.: -setWrappedReturn wrapped return"},
  { false,  "-setOriginal",                      2, "wrappedtool fullpath",                  0, OT_WS,    ppSetOriginal,                     NULL, "Set the path of the original tool which will be wrapped. It is belonging to wrapped tool. e.g.: -setOriginal wrapped fullpath"},
  { false,  "-starttool",                        1, "tool",                                  0, OT_WS,    ppStartTool,                       NULL, "The name of the tool or script which will be called by the StartWrapper script. e.g.: -starttool tool"},
  { false,  "-stoptool",                         1, "tool",                                  0, OT_WS,    ppStopTool,                        NULL, "The name of the tool or script which will be called by the StopWrapper script. e.g.: -stoptool tool"},
  { false,  "-wrapperml",                        1, "levelnumber",                           0, OT_WS,    ppWrapperML,                       NULL, "The message level of the wrapper environment. (Default: 1) e.g.: -wrapperml ml"},
  { false,  "-wraplog",                          1, "filename",                              0, OT_WS,    ppWrapLog,                         NULL, "The name of the wrapper log file. (Default: wraplog.log) e.g.: -wraplog logfilename"},
  { false,  "-setWrapperCanCauseError",          0, "",                                      0, OT_WS,    ppWraperCanCauseError,             NULL, "If it is set then a wrapper program error overrides the return value of the original command."},
  COMMON_CL_ARGS
};

/**
 * @brief Collects the (wrapped tool - wrapper tool) pairs.
 * @param wrappedtools       [out] The map of the collected pairs.
 */

void getWrappedTools(map<string, string>& wrappedtools) {
  char tmp[BUFFERSIZE];
  getPrivateProfileString(STARTWRAPPERSECTION, WRAPPED_TO_WRAPPER, NULL, tmp, BUFFERSIZE, configfile.c_str(), casesensitive);
  string tmpstr(tmp);
  vector<string> tmpvec;

  split(tmpstr, tmpvec, ';');
  vector<string>::const_iterator it;
  for(it = tmpvec.begin(); it != tmpvec.end(); it++) {
    if (it->empty()) {
      continue;
    }

    size_t found = it->find_first_of(',');
    string wd = it->substr(0, found);
    string wr = "";
    if (found != string::npos) {
      wr = it->substr(found+1, it->length()-found-1);
    }

    LowerStringOnWindows(wd);
    LowerStringOnWindows(wr);
    wrappedtools.insert(make_pair(wd, wr));

  }
}


/**
 * @brief Returns the correct section name about a section string.
 * @param wrmap      [in] The map of the (wrapped tool - wrapper tool) pairs.
 * @param section    [in] The input section string.
 * @return           The correct section name.
 */
string getSectionName(map<string,string> wrmap, string section) {
  map<string,string>::const_iterator it;
  LowerStringOnWindows(section);
  bool eqSection = false;
  bool inSection = false;
  string full = "";
  for(it = wrmap.begin(); it != wrmap.end(); it++) {
    string tmp = it->first;
    LowerStringOnWindows(tmp);
    if(tmp == section) {
      eqSection = true;
    } else {
      vector<string> tmpvec;
      split(tmp, tmpvec, DIRDIVCHAR);
      if(!tmpvec.empty() && tmpvec[tmpvec.size()-1] == section) {
        inSection = true;
        full = tmp;
      }
    }
  }
  if (eqSection) {
    return "prog_" + section;
  } else if (!eqSection && inSection) {
    return "prog_" + full;
  } else {
    return "prog_" + section;
  }
}

/**
 * @brief The main function which creates and modifies the wrapper_environment_config.ini file.
 */
int main(int argc, char **argv) {

  MAIN_BEGIN

#ifdef _WIN32
  casesensitive = false;
#endif

#ifdef __linux__
  casesensitive = true;
#endif

  MainInit(argc, argv, "-");

  configfile = common::getCwd() + DIRDIVSTRING + configfile;

  if (!files.empty()) {
    if (files.size() != 1) {
      clError();
    } else {
      configfile = *files.begin();
    }
  }

//Put "/" or "\" to the end of working dir string and sets WRAPPER_WORKING_DIR value
  if(!workingdir.empty()) {
    if(workingdir[workingdir.length()-1] != DIRDIVCHAR) {
      workingdir = workingdir + DIRDIVSTRING;
    }
    writePrivateProfileString(STARTWRAPPERSECTION, WRAPPER_WORKING_DIR, workingdir.c_str(), configfile.c_str(), casesensitive);
  }else{
    char wdir[8196];
    getPrivateProfileString(STARTWRAPPERSECTION, WRAPPER_WORKING_DIR, NULL, wdir, 8196, configfile.c_str(), casesensitive);
    if (wdir[0] == '\0') {
      workingdir = common::indep_fullpath("." DIRDIVSTRING);
      writePrivateProfileString(STARTWRAPPERSECTION, WRAPPER_WORKING_DIR, workingdir.c_str(), configfile.c_str(), casesensitive);
    }
  }

//Sets WRAPPED_TO_WRAPPER value
  map<string, string> wrappedtools;
  getWrappedTools(wrappedtools);
  if(!wraptools.empty()) {
    string tmpstr = "";
    map<string,string>::iterator it1;
    for(it1 = wraptools.begin(); it1 != wraptools.end(); it1++) {
      LowerStringOnWindows(it1->first);
      LowerStringOnWindows(it1->second);
      wrappedtools[it1->first] = it1->second;
    }
    map<string,string>::const_iterator it2;
    for(it2 = wrappedtools.begin(); it2 != wrappedtools.end(); it2++) {
      tmpstr = tmpstr + it2->first + "," + it2->second + ";";
    }
    writePrivateProfileString(STARTWRAPPERSECTION, WRAPPED_TO_WRAPPER, tmpstr.c_str(), configfile.c_str(), casesensitive);
  }

//Sets OTHER_START_TOOLS value
  if(!starttools.empty()) {
    char tmp[BUFFERSIZE];
    getPrivateProfileString(STARTWRAPPERSECTION, OTHER_START_TOOLS, NULL, tmp, BUFFERSIZE, configfile.c_str(), casesensitive);
    string tmpstr(tmp);
    if(!tmpstr.empty() && tmpstr[tmpstr.length()-1] != ';') {
      tmpstr = tmpstr + ";";
    }
    set<string>::const_iterator it;
    for(it = starttools.begin(); it != starttools.end(); it++) {
      tmpstr = tmpstr + *it + ";";
    }
    writePrivateProfileString(STARTWRAPPERSECTION, OTHER_START_TOOLS, tmpstr.c_str(), configfile.c_str(), casesensitive);
  }

//Sets OTHER_STOP_TOOLS value
  if(!stoptools.empty()) {
    char tmp[BUFFERSIZE];
    getPrivateProfileString(STOPWRAPPERSECTION, OTHER_STOP_TOOLS, NULL, tmp, BUFFERSIZE, configfile.c_str(), casesensitive);
    string tmpstr(tmp);
    if(!tmpstr.empty() && tmpstr[tmpstr.length()-1] != ';') {
      tmpstr = tmpstr + ";";
    }
    set<string>::const_iterator it;
    for(it = stoptools.begin(); it != stoptools.end(); it++) {
      tmpstr = tmpstr + *it + ";";
    }
    writePrivateProfileString(STOPWRAPPERSECTION, OTHER_STOP_TOOLS, tmpstr.c_str(), configfile.c_str(), casesensitive);
  }

//Sets WRAPPER_ML value
  writePrivateProfileString(WRAPPERSECTION, WRAPPER_ML, wrapperml.c_str(), configfile.c_str(), casesensitive);

//Sets WRAPPER_LOG_FILE value
  writePrivateProfileString(WRAPPERSECTION, WRAPPER_LOG_FILE, wraplog.c_str(), configfile.c_str(), casesensitive);

//Sets WRAPPEDTOOL_LOGGING and WRAPPERTOOL_LOGGING values
  if(!loggings.empty()) {
    map<string, pair<string, string> >::const_iterator it;
    for(it = loggings.begin(); it != loggings.end(); it++) {
      writePrivateProfileString(getSectionName(wrappedtools, it->first).c_str(), WRAPPEDTOOL_LOGGING, it->second.first.c_str(), configfile.c_str(), casesensitive);
      writePrivateProfileString(getSectionName(wrappedtools, it->first).c_str(), WRAPPERTOOL_LOGGING, it->second.second.c_str(), configfile.c_str(), casesensitive);
    }
  }

//Sets WRAPPEDTOOL_RUN value
  if(!wrappedrun.empty()) {
    map<string, string>::const_iterator it;
    for(it = wrappedrun.begin(); it != wrappedrun.end(); it++) {
      writePrivateProfileString(getSectionName(wrappedtools, it->first).c_str(), WRAPPEDTOOL_RUN, it->second.c_str(), configfile.c_str(), casesensitive);
    }
  }

//Sets WRAPPERTOOL_ALWAYS_RUN value
  if(!alwaysrun.empty()) {
    map<string, string>::const_iterator it;
    for(it = alwaysrun.begin(); it != alwaysrun.end(); it++) {
      writePrivateProfileString(getSectionName(wrappedtools, it->first).c_str(), WRAPPERTOOL_ALWAYS_RUN, it->second.c_str(), configfile.c_str(), casesensitive);
    }
  }

//Sets WRAPPERTOOL_RUN_FIRST value
  if(!wrapperfirst.empty()) {
    map<string, string>::const_iterator it;
    for(it = wrapperfirst.begin(); it != wrapperfirst.end(); it++) {
      writePrivateProfileString(getSectionName(wrappedtools, it->first).c_str(), WRAPPERTOOL_RUN_FIRST, it->second.c_str(), configfile.c_str(), casesensitive);
    }
  }

//Sets WRAPPERTOOL_USE_FILTER_FILE value
  if(!wrapperDirectoryFilter.empty()) {
    map<string, string>::const_iterator it;
    for(it = wrapperDirectoryFilter.begin(); it != wrapperDirectoryFilter.end(); it++) {
      writePrivateProfileString(getSectionName(wrappedtools, it->first).c_str(), WRAPPERTOOL_DIRECTORY_FILTER, it->second.c_str(), configfile.c_str(), casesensitive);
    }
  }

//Sets WRAPPEDTOOL_FILTER_REGEX value
  if(!wrappedParamFilter.empty()) {
    map<string, string>::const_iterator it;
    for(it = wrappedParamFilter.begin(); it != wrappedParamFilter.end(); it++) {
      writePrivateProfileString(getSectionName(wrappedtools, it->first).c_str(), WRAPPEDTOOL_PARAM_FILTER, it->second.c_str(), configfile.c_str(), casesensitive);
    }
  }

//Sets WRAPPEDTOOL_RETURN_SUCCESSFUL value
  if(!wrappedreturn.empty()) {
    map<string, string>::const_iterator it;
    for(it = wrappedreturn.begin(); it != wrappedreturn.end(); it++) {
      writePrivateProfileString(getSectionName(wrappedtools, it->first).c_str(), WRAPPEDTOOL_RETURN_SUCCESSFUL, it->second.c_str(), configfile.c_str(), casesensitive);
    }
  }

//Sets NUMBER_OF_WRAPPER_EXTRA_PARAMS and WRAPPERTOOL_EXTRA_PARAM_* values
  if(!wrapperparams.empty()) {
    map<string, vector<string> >::const_iterator itm;
    for(itm = wrapperparams.begin(); itm != wrapperparams.end(); itm++) {
      int count = getPrivateProfileInt(getSectionName(wrappedtools, itm->first).c_str(), NUMBER_OF_WRAPPER_EXTRA_PARAMS, 0, configfile.c_str(), casesensitive);

      vector<string>::const_iterator itv;
      for(itv = itm->second.begin(); itv != itm->second.end(); itv++) {
        count++;
        string tmp(WRAPPERTOOL_EXTRA_PARAM);
        tmp = tmp + "_" + toString(count);
        writePrivateProfileString(getSectionName(wrappedtools, itm->first).c_str(), tmp.c_str(), itv->c_str(), configfile.c_str(), casesensitive);
      }
      writePrivateProfileString(getSectionName(wrappedtools, itm->first).c_str(), NUMBER_OF_WRAPPER_EXTRA_PARAMS, toString(count).c_str(), configfile.c_str(), casesensitive);

    }
  }

//Sets NUMBER_OF_WRAPPED_PARAMS_AFTER_PARAMS and WRAPPEDTOOL_EXTRA_PARAM_AFTER_PARAM_* values
  if(!wrappedparamsafter.empty()) {
    map<string, set<pair<string,string> > >::const_iterator itm;
    for(itm = wrappedparamsafter.begin(); itm != wrappedparamsafter.end(); itm++) {
      int count = getPrivateProfileInt(getSectionName(wrappedtools, itm->first).c_str(), NUMBER_OF_WRAPPED_PARAMS_AFTER_PARAMS, 0, configfile.c_str(), casesensitive);

      set<pair<string,string> >::const_iterator its;
      for(its = itm->second.begin(); its != itm->second.end(); its++) {
        count++;
        string tmp(WRAPPEDTOOL_EXTRA_PARAM_AFTER_PARAM);
        tmp = tmp + "_" + toString(count);
        string val = its->first + "," + its->second;
        writePrivateProfileString(getSectionName(wrappedtools, itm->first).c_str(), tmp.c_str(), val.c_str(), configfile.c_str(), casesensitive);
      }
      writePrivateProfileString(getSectionName(wrappedtools, itm->first).c_str(), NUMBER_OF_WRAPPED_PARAMS_AFTER_PARAMS, toString(count).c_str(), configfile.c_str(), casesensitive);

    }
  }

//Sets NUMBER_OF_WRAPPED_PARAMS_BEGIN and WRAPPEDTOOL_EXTRA_PARAM_TO_BEGIN_* values
  if(!wrappedparamsbegin.empty()) {
    map<string, vector<string> >::const_iterator itm;
    for(itm = wrappedparamsbegin.begin(); itm != wrappedparamsbegin.end(); itm++) {
      int count = getPrivateProfileInt(getSectionName(wrappedtools, itm->first).c_str(), NUMBER_OF_WRAPPED_PARAMS_BEGIN, 0, configfile.c_str(), casesensitive);

      vector<string>::const_iterator itv;
      for(itv = itm->second.begin(); itv != itm->second.end(); itv++) {
        count++;
        string tmp(WRAPPEDTOOL_EXTRA_PARAM_TO_BEGIN);
        tmp = tmp + "_" + toString(count);
        writePrivateProfileString(getSectionName(wrappedtools, itm->first).c_str(), tmp.c_str(), itv->c_str(), configfile.c_str(), casesensitive);
      }
      writePrivateProfileString(getSectionName(wrappedtools, itm->first).c_str(), NUMBER_OF_WRAPPED_PARAMS_BEGIN, toString(count).c_str(), configfile.c_str(), casesensitive);

    }
  }

//Sets NUMBER_OF_WRAPPED_PARAMS_END and WRAPPEDTOOL_EXTRA_PARAM_TO_END_* values
  if(!wrappedparamsend.empty()) {
    map<string, vector<string> >::const_iterator itm;
    for(itm = wrappedparamsend.begin(); itm != wrappedparamsend.end(); itm++) {
      int count = getPrivateProfileInt(getSectionName(wrappedtools, itm->first).c_str(), NUMBER_OF_WRAPPED_PARAMS_END, 0, configfile.c_str(), casesensitive);

      vector<string>::const_iterator itv;
      for(itv = itm->second.begin(); itv != itm->second.end(); itv++) {
        count++;
        string tmp(WRAPPEDTOOL_EXTRA_PARAM_TO_END);
        tmp = tmp + "_" + toString(count);
        writePrivateProfileString(getSectionName(wrappedtools, itm->first).c_str(), tmp.c_str(), itv->c_str(), configfile.c_str(), casesensitive);
      }
      writePrivateProfileString(getSectionName(wrappedtools, itm->first).c_str(), NUMBER_OF_WRAPPED_PARAMS_END, toString(count).c_str(), configfile.c_str(), casesensitive);

    }
  }

//Sets NUMBER_OF_REMOVE_PARAMS and WRAPPEDTOOL_REMOVE_PARAM_* values
  if(!wrappedparamsremove.empty()) {
    map<string, set<string> >::const_iterator itm;
    for(itm = wrappedparamsremove.begin(); itm != wrappedparamsremove.end(); itm++) {
      int count = getPrivateProfileInt(getSectionName(wrappedtools, itm->first).c_str(), NUMBER_OF_REMOVE_PARAMS, 0, configfile.c_str(), casesensitive);

      set<string>::const_iterator its;
      for(its = itm->second.begin(); its != itm->second.end(); its++) {
        count++;
        string tmp(WRAPPEDTOOL_REMOVE_PARAM);
        tmp = tmp + "_" + toString(count);
        writePrivateProfileString(getSectionName(wrappedtools, itm->first).c_str(), tmp.c_str(), its->c_str(), configfile.c_str(), casesensitive);
      }
      writePrivateProfileString(getSectionName(wrappedtools, itm->first).c_str(), NUMBER_OF_REMOVE_PARAMS, toString(count).c_str(), configfile.c_str(), casesensitive);

    }
  }

//Sets CHANGE_ORIGINAL value
//It is needed if the wrapped tool is given by full path
  if(!wraptools.empty()) {
    map<string, string>::const_iterator it;
    for(it = wraptools.begin(); it != wraptools.end(); it++) {
      if(pathIsAbsolute(it->first)) {
        writePrivateProfileString(getSectionName(wrappedtools, it->first).c_str(), CHANGE_ORIGINAL, "1", configfile.c_str(), casesensitive);
      } else {
        if(pathFindFileName(it->first) == it->first) {
          writePrivateProfileString(getSectionName(wrappedtools, it->first).c_str(), CHANGE_ORIGINAL, "0", configfile.c_str(), casesensitive);
        } else {
          writePrivateProfileString(getSectionName(wrappedtools, it->first).c_str(), CHANGE_ORIGINAL, "1", configfile.c_str(), casesensitive);
        }
      }
    }
  }

//Sets ORIGINAL_TOOL value
  if(!originaltools.empty()) {
    map<string,string>::const_iterator it;
    for(it = originaltools.begin(); it != originaltools.end(); it++) {
      writePrivateProfileString(getSectionName(wrappedtools, it->first).c_str(), ORIGINAL_TOOL, it->second.c_str(), configfile.c_str(), casesensitive);
    }
  }


  if (wrapper_can_cause_error) {
    writePrivateProfileString(WRAPPERSECTION, WRAPPER_CAN_CAUSE_ERROR, "1", configfile.c_str(), casesensitive);
  }

  MAIN_END

  return 0;
}
