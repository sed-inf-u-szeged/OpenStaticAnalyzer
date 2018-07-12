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
#include <map>
#include <set>

#include "AnalyzerWrapperConfig.h"
#include <common/inc/FileSup.h>
#include <common/inc/StringSup.h>
#include <common/inc/WriteMessage.h>
#include <common/inc/PlatformDependentDefines.h>
#include <Exception.h>

#define BUFFERSIZE 8192

#define PROGRAM_NAME "AnalyzerWrapperConfig"
#define EXECUTABLE_NAME "AnalyzerWrapperConfig"

#include <MainCommon.h>

using namespace std;
using namespace common;

static list<string> files;

string configfile = ANALYZER_WRAPPER_CONFIG;

bool casesensitive = false;

string outputdir = ".columbus";
map<string, string> needtorun;
string linkfilterfile;
map<string, string> needstat;
string configdir;
map<string, set<pair<string, string> > > paramtoskip;
string messagelevel;
map<string, string> toolmessagelevel;
map<string, set<string> > extraparam;
string instrumenting;
string prepForInstrument;
string runCppcheck;
int linkingMode = 3;

//Callback functions for argument processing.
static bool ppOutputDir(const Option *o, char *argv[]) {
  outputdir = argv[0];
  return true;
}

static bool ppNeedToRun(const Option *o, char *argv[]) {
  LowerStringOnWindows(argv[0]);
  needtorun.insert(make_pair(argv[0], argv[1]));
  return true;
}

static bool ppFilterFile(const Option *o, char *argv[]) {
  LowerStringOnWindows(argv[0]);
  linkfilterfile = common::indep_fullpath(argv[0]);
  return true;
}

static bool ppNeedStat(const Option *o, char *argv[]) {
  stringLower(argv[0]);
  needstat.insert(make_pair(argv[0],argv[1]));
  return true;
}

static bool ppConfigDir(const Option *o, char *argv[]) {
  LowerStringOnWindows(argv[0]);
  configdir = common::indep_fullpath(argv[0]);
  return true;
}

static bool ppParamToSkip(const Option *o, char *argv[]) {
  stringLower(argv[0]);
  paramtoskip[argv[0]].insert(make_pair(argv[1], argv[2]));
  return true;
}

static bool ppExtraParam(const Option *o, char *argv[]) {
  stringLower(argv[0]);
  extraparam[argv[0]].insert(argv[1]);
  return true;
}

static bool ppMessageLevel(const Option *o, char *argv[]) {
  messagelevel = argv[0];
  return true;
}

static bool ppToolMessageLevel(const Option *o, char *argv[]) {
  stringLower(argv[0]);
  toolmessagelevel.insert(make_pair(argv[0], argv[1]));
  return true;
}

static bool ppEnableCompInst(const Option *o, char *argv[]) {
  instrumenting = argv[0];
  return true;
}

static bool ppPrepCompInst(const Option *o, char *argv[]) {
  prepForInstrument = argv[0];
  return true;
}

static bool ppCppcheck(const Option *o, char *argv[]) {
  runCppcheck = argv[0];
  return true;
}

static bool ppLinkingMode(const Option *o, char *argv[]) {
  linkingMode = common::str2int(argv[0]);
  return true;
}

static void ppFile(char *filename) {
  files.push_back(filename);
}

const Option OPTIONS_OBJ[] = {
  { false,  "-outputDir",                 1, "directory",                           0, OT_WS,    ppOutputDir,            NULL, "Set the name of the directory where the outputs of compiler, linker and archive will be created. e.g.: -outputDir dirname"},
  { false,  "-needToRun",                 2, "name needednumber{0,1}",              0, OT_WS,    ppNeedToRun,            NULL, "Set whether the compiler, linker or archive needs to run or not. e.g.: -needToRun compiler|linker|archive 0|1"},
  { false,  "-linkerFilterFile",          1, "path",                                0, OT_WS,    ppFilterFile,           NULL, "Set the path of the linker filter file. e.g.: -linkerFilterFile path"},
  { false,  "-needStat",                  2, "name needednumber{0,1}",              0, OT_WS,    ppNeedStat,             NULL, "Set whether the compiler, linker or archive creates stat file or not. e.g.: -needStat compiler|linker|archive 0|1"},
  { false,  "-configDir",                 1, "directorypath",                       0, OT_WS,    ppConfigDir,            NULL, "Set the path of the directory where compiler and linker find their config files. e.g.: -configDir path"},
  { false,  "-paramToSkip",               3, "swichname num",                       0, OT_WS,    ppParamToSkip,          NULL, "Set switch and its number of parameters of wrapped tool which will be skipped. e.g.: -paramToSkip switchname num  |  -paramToSkip regexp num"},
  { false,  "-setExtraParam",             2, "name param",                          0, OT_WS,    ppExtraParam,           NULL, "Set extra param for compiler, linker or archive. e.g.: -setExtraParam compiler|linker|archive param"},
  { false,  "-messageLevel",              1, "levelnumber",                         0, OT_WS,    ppMessageLevel,         NULL, "Set message level for wrapper tools (default: 3). e.g.: -messageLevel level"},
  { false,  "-toolMessageLevel",          2, "name levelnumber",                    0, OT_WS,    ppToolMessageLevel,     NULL, "Set message level for compiler, linker and archive tools (default: 2). e.g.: -toolMessageLevel compiler|linker|archive level"},
  { false,  "-enableCompilerInstrument",  1, "enablenumber{0,1}",                   0, OT_WS,    ppEnableCompInst,       NULL, "Set whether run instrumenter instead of analyzer tools (CAN, CANLink, CANLib) or not. e.g.: -enableCompilerInstrument 0|1"},
  { false,  "-prepareCompilerInstrument", 1, "needednumber{0,1}",                   0, OT_WS,    ppPrepCompInst,         NULL, "Set prepare for instrument: it means that the CAN analyzes preprocessed files, so we have to preprocess these files before CAN calling. e.g.: -prepareCompilerInstrument 0|1"},
  { false,  "-runCppcheck",               1, "enablenumber{0,1}",                   0, OT_WS,    ppCppcheck,             NULL, "Set whether run cppcheck or not. e.g.: -runCppcheck 0|1"},
  { false,  "-linkingMode",               1, "number",                              0, OT_WS,    ppLinkingMode,          NULL, "Set the linking mode.\nMode 1: Invoke CANLink instead of CANLib for the static libraries. Do not link the the lcsi of the static library into the lcsi of the exe.\nMode 2: Invoke CANLink instead of CANLib for the static libraries. Link the the lcsi of the static library into the lcsi of the exe. Mode 3: Use CANLib and link the csi files of the acsi into the lcsi of the exe."},
  COMMON_CL_ARGS
};

/**
 * @brief The main function which creates and modifies the analyzer_wrapper_config.ini file.
 */
int main(int argc, char **argv) {

  MAIN_BEGIN

#ifdef _WIN32
  casesensitive = false;
#elif __unix__
  casesensitive = true;
#endif

  MainInit(argc, argv, "-");

  configfile = common::getExecutableProgramDir() + DIRDIVSTRING + configfile;

  if (!files.empty()) {
    clError();
  }

  if(!outputdir.empty()) {
    writePrivateProfileString(ALLSECTION, OUTPUT_DIR, outputdir.c_str(), configfile.c_str(), casesensitive);
  }

  if(!needtorun.empty()) {
    map<string, string>::const_iterator it;
    for(it = needtorun.begin(); it != needtorun.end(); it++) {
      writePrivateProfileString(it->first.c_str(), NEED_TO_RUN, it->second.c_str(), configfile.c_str(), casesensitive);
    }
  }

  if(!linkfilterfile.empty()) {
    writePrivateProfileString(LINKERSECTION, LINK_FILTER_FILE, linkfilterfile.c_str(), configfile.c_str(), casesensitive);
  }

  if(!needstat.empty()) {
    map<string, string>::const_iterator it;
    for(it = needstat.begin(); it != needstat.end(); it++) {
      writePrivateProfileString(common::stringLower(it->first).c_str(), NEED_STAT, it->second.c_str(), configfile.c_str(), casesensitive);
    }
  }

  if(!toolmessagelevel.empty()) {
    map<string, string>::const_iterator it;
    for(it = toolmessagelevel.begin(); it != toolmessagelevel.end(); it++) {
      writePrivateProfileString(common::stringLower(it->first).c_str(), TOOL_MESSAGE_LEVEL, it->second.c_str(), configfile.c_str(), casesensitive);
    }
  }

  if(!configdir.empty()) {
    writePrivateProfileString(ALLSECTION, CONFIG_DIR, configdir.c_str(), configfile.c_str(), casesensitive);
  }

  if(!paramtoskip.empty()) {
    map<string, set<pair<string, string> > >::const_iterator it1;
    for(it1 = paramtoskip.begin(); it1 != paramtoskip.end(); it1++) {
      int count = getPrivateProfileInt(common::stringLower(it1->first).c_str(), NUM_OF_PARAM_TO_SKIP, 0, configfile.c_str(), casesensitive);

      set<pair<string, string> >::const_iterator it2;
      for(it2 = it1->second.begin(); it2 != it1->second.end(); it2++) {
        count++;
        string tmp(PARAM_TO_SKIP);
        tmp = tmp + "_" + toString(count);
        writePrivateProfileString(common::stringLower(it1->first).c_str(), tmp.c_str(), (it2->first + ";" + it2->second).c_str(), configfile.c_str(), casesensitive);
      }
      writePrivateProfileString(common::stringLower(it1->first).c_str(), NUM_OF_PARAM_TO_SKIP, toString(count).c_str(), configfile.c_str(), casesensitive);
    }
  }

  if(!extraparam.empty()) {
    map<string, set<string> >::const_iterator it1;
    for(it1 = extraparam.begin(); it1 != extraparam.end(); it1++) {
      int count = getPrivateProfileInt(common::stringLower(it1->first).c_str(), NUM_OF_EXTRA_PARAM, 0, configfile.c_str(), casesensitive);

      set<string>::const_iterator it2;
      for(it2 = it1->second.begin(); it2 != it1->second.end(); it2++) {
        count++;
        string tmp(EXTRA_PARAM);
        tmp = tmp + "_" + toString(count);
        writePrivateProfileString(common::stringLower(it1->first).c_str(), tmp.c_str(), it2->c_str(), configfile.c_str(), casesensitive);
      }
      writePrivateProfileString(common::stringLower(it1->first).c_str(), NUM_OF_EXTRA_PARAM, toString(count).c_str(), configfile.c_str(), casesensitive);
    }
  }

  if(!messagelevel.empty()) {
    writePrivateProfileString(ALLSECTION, MESSAGE_LEVEL, messagelevel.c_str(), configfile.c_str(), casesensitive);
  }

  if(!instrumenting.empty()) {
    writePrivateProfileString(ALLSECTION, ENABLE_COMPILER_INSTRUMENT, instrumenting.c_str(), configfile.c_str(), casesensitive);
  }

  if(!prepForInstrument.empty()) {
    writePrivateProfileString(ALLSECTION, PREPARE_FOR_INSTRUMENT, prepForInstrument.c_str(), configfile.c_str(), casesensitive);
  }
  
  if(!runCppcheck.empty()) {
    writePrivateProfileString(COMPILERSECTION, RUN_CPPCHECK, runCppcheck.c_str(), configfile.c_str(), casesensitive);
  }
  
  writePrivateProfileString(ALLSECTION, LINKING_MODE, toString(linkingMode).c_str(), configfile.c_str(), casesensitive);

  MAIN_END

  return 0;
}
