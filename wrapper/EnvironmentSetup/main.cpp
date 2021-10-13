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
#include <fstream>
#include <iostream>
#include <set>

#include <WrapperEnvironmentConfig/WrapperEnvironmentCommon.h>
#include <common/inc/WriteMessage.h>
#include <common/inc/FileSup.h>
#include <common/inc/StringSup.h>
#include <common/inc/PlatformDependentDefines.h>
#include <Exception.h>

#define PROGRAM_NAME "EnvironmentSetup"
#define EXECUTABLE_NAME "EnvironmentSetup"
#define BUFFERSIZE 8192

#include <MainCommon.h>

using namespace std;
using namespace common;

string configfile = WRAPPER_ENVIRONMENT_CONFIG;
static list<string> files;

char buffer[BUFFERSIZE];
bool casesensitive = false;

static void ppFile(char *filename) {
  files.push_back(filename);
}

const Option OPTIONS_OBJ[] = {
  COMMON_CL_ARGS
};

/**
 * @brief Processes the config.ini file for wrapper environment creates a script which sets the environmental variables.
 * @param ofs        [out] The output script.
 */
void processConfig(ofstream& ofs) {

  string tmpstr = "";

//Processes the WRAPPER_WORKING_DIR value and sets WRAPPER_ENVIRONMENT environmental variable
  char* workingdir = buffer;
  string workingstring = "";
  getPrivateProfileString(STARTWRAPPERSECTION, WRAPPER_WORKING_DIR, NULL, workingdir, BUFFERSIZE, configfile.c_str(), casesensitive);
  workingstring = workingdir;

  LowerStringOnWindows(workingstring);

  if(!workingstring.empty()) {
    ofs << SETENVVAR << " WRAPPER_ENVIRONMENT=" << ENV_VAL_PLUS << workingstring << ENV_VAL_PLUS << endl;
  } else {
    ofs << SETENVVAR << " WRAPPER_ENVIRONMENT=" << ENV_VAL_PLUS << common::indep_fullpath("." DIRDIVSTRING) << ENV_VAL_PLUS << endl;
  }


  char* starttools = buffer;
  getPrivateProfileString(STARTWRAPPERSECTION, OTHER_START_TOOLS, NULL, starttools, BUFFERSIZE, configfile.c_str(), casesensitive);
  string startstring(starttools);

  char* wrappedtools = buffer;
  getPrivateProfileString(STARTWRAPPERSECTION, WRAPPED_TO_WRAPPER, NULL, wrappedtools, BUFFERSIZE, configfile.c_str(), casesensitive);
  string wrapstring(wrappedtools);

  char* stoptools = buffer;
  getPrivateProfileString(STOPWRAPPERSECTION, OTHER_STOP_TOOLS, NULL, stoptools, BUFFERSIZE, configfile.c_str(), casesensitive);
  string stopstring(stoptools);

//Processes the OTHER_START_TOOLS value and sets START_TOOLS environmental variable
  vector<string> starts;
  vector<string>::const_iterator it1;
  split(startstring, starts, ';');
  tmpstr = "";
  for(it1 = starts.begin(); it1 != starts.end(); it1++) {
    if(it1->empty()) {
      continue;
    }
    tmpstr = tmpstr + "\"" + *it1 + "\"" + " ";
  }
  if(!tmpstr.empty()) {
    ofs << SETENVVAR << " START_TOOLS=" << ENV_VAL_PLUS << tmpstr << ENV_VAL_PLUS << endl;
  }

//Processes the OTHER_STOP_TOOLS value and sets STOP_TOOLS environmental variable
  vector<string> stops;
  vector<string>::const_iterator it2;
  split(stopstring, stops, ';');
  tmpstr = "";
  for(it2 = stops.begin(); it2 != stops.end(); it2++) {
    if(it2->empty()) {
      continue;
    }
    tmpstr = tmpstr + "\"" + *it2 + "\"" + " ";
  }
  if(!tmpstr.empty()) {
    ofs << SETENVVAR << " STOP_TOOLS=" << ENV_VAL_PLUS << tmpstr << ENV_VAL_PLUS << endl;
  }

//Processes the WRAPPED_TO_WRAPPER and CHANGE_ORIGINAL values and sets WRAPPED_TOOLS, WRAPPER_TOOLS and ORIG_TOOLS environmental variable
  vector<string> wraps;
  vector<string>::const_iterator it3;
  split(wrapstring, wraps, ';');
  string wrappers = "";
  string wrappeds = "";
  string origs = "";
  set<string> wrtools;
  for(it3 = wraps.begin(); it3 != wraps.end(); it3++) {

    if(it3->empty()) {
      continue;
    }

    size_t found = it3->find_first_of(',');
    string wd = it3->substr(0, found);
    string wr = "";
    if(found != string::npos) {
      wr = it3->substr(found+1, it3->length()-found-1);
    }
    int change;
    string wd_sec = "prog_" + wd;
    change = getPrivateProfileInt(wd_sec.c_str(), CHANGE_ORIGINAL, 0, configfile.c_str(), casesensitive);
    if(change == 0) {
      wrappeds = wrappeds + "\"" + wd + "\"" + " ";
    } else if(change == 1) {
      origs = origs + "\"" + wd + "\"" + " ";
    }
    if(wr != "[none]") {
      wrtools.insert(wr);
    }
  }
  set<string>::const_iterator setit;
  for(setit = wrtools.begin(); setit != wrtools.end(); setit++) {
    wrappers = wrappers + "\"" + *setit + "\"" + " ";
  }
  if(!wrappeds.empty()) {
    ofs << SETENVVAR << " WRAPPED_TOOLS=" << ENV_VAL_PLUS << wrappeds << ENV_VAL_PLUS << endl;
  }
  if(!wrappers.empty()) {
    ofs << SETENVVAR << " WRAPPER_TOOLS=" << ENV_VAL_PLUS << wrappers << ENV_VAL_PLUS << endl;
  }
  if(!origs.empty()) {
    ofs << SETENVVAR << " ORIG_TOOLS=" << ENV_VAL_PLUS << origs << ENV_VAL_PLUS << endl;
  }
}

/**
 * @brief The main function of the EnvironmentSetup.
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

  string configdir = common::getCwd();
  configfile = configdir + DIRDIVSTRING + configfile;

  if (!files.empty()) {
    if (files.size() != 1) {
      clError();
    } else {
      configfile = *files.begin();
    }
  }

  string output;
  output = configdir + DIRDIVSTRING + "setter" SCRIPTEXT;
  ofstream outbat(output.c_str());
  if(outbat.is_open()) {
    outbat << SCRIPTSTART << endl;
    processConfig(outbat);
    outbat.flush();
    outbat.close();
  }

  MAIN_END

  return 0;
}
