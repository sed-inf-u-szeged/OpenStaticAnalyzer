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

#define PROGRAM_NAME "GenericConfig"
#define EXECUTABLE_NAME "GenericConfig"

#include <fstream>

#include <MainCommon.h>
#include <common/inc/FileSup.h>
#include <common/inc/PlatformDependentDefines.h>
#include "common/inc/WriteMessage.h"
#include "messages.h"

using namespace common;
using namespace columbus;
using namespace std;

static string config;
static string source;
static string prefix;
static int skip = 0;
static std::list<std::string> opts;

// Callback methods for argument processing
static bool ppConfig (const Option *o, char *argv[]) {
  config = argv[0];
  return true;
}

static bool ppSource (const Option *o, char *argv[]) {
  source = argv[0];
  return true;
}

static bool ppSkipL (const Option *o, char *argv[]) {
  skip = atoi(argv[0]);
  return true;
}

static bool ppSkipP (const Option *o, char *argv[]) {
  prefix = argv[0];
  return true;
}

static bool ppOpts (const Option *o, char *argv[]) {
  opts.push_back(argv[0]);
  return true;
}

static void ppFile(char *opt) {
}

const Option OPTIONS_OBJ [] = {
  { false,  "-config",      1,   "file",          0, OT_WC,      ppConfig,        NULL,   "The path of the config file."},
  { false,  "-source",      1,   "file",          0, OT_WC,      ppSource,        NULL,   "The file we want to read the configs from."},
  { false,  "-skiplines",   1,   "num",           0, OT_WC,      ppSkipL,         NULL,   "The number of lines to skip in the source file."},
  { false,  "-skipprefix",  1,   "string",        0, OT_WC,      ppSkipP,         NULL,   "A prefix string to skip it at the begin of options."},
  { false,  "-option",      1,   "string",        0, OT_WC,      ppOpts,          NULL,   "Ini options in the form 'section/key=value'."},
  COMMON_CL_ARGS
};

void clError(const char* message = "Bad command line!") {
  WriteMsg::write(CMSG_GENCFG_CL_ERROR,message);
  Help();
  exit(common::retBadArgError);
}

bool processOptions(int argc, char** argv)
{
  if ( config.empty()) {
    WriteMsg::write(CMSG_GENCFG_FILTER_CANNOT_BE_LOADED);
    Help();
    return 1;
  }

  if ( source.empty() && opts.size() == 0) {
    WriteMsg::write(CMSG_GENCFG_ERROR_OPEN_FILE);
    Help();
    return 1;
  }
  
  if ( !source.empty()){
    ifstream ifs(source.c_str());
    if (!ifs.is_open()) {
      WriteMsg::write(CMSG_GENCFG_IO_ERROR, source.c_str());
      return 1;
    } else {
      string tmp;
      while (getline(ifs, tmp)) {
        if (skip >0 ){
          skip--;
        } else {
          int from = 0;
          if ( !prefix.empty()) {
            from = prefix.size();
          }
          opts.push_back(tmp.substr(from));
        }
      }
    }
  } else {
      if (skip > 0 || !prefix.empty()){
            WriteMsg::write(CMSG_GENCFG_SKIPPREFIX_OR_SKIPLINE_CANT_BE_USED);
      }
  }

  return 0;
}

int main(int argc, char *argv[]) {
  MAIN_BEGIN

  MainInit(argc, argv, "-");

  if (processOptions(argc, argv)){
    return 1;
  }
  for ( list<string>::iterator it = opts.begin(); it != opts.end(); ++it){
    string full_opt = *it;
    int slashPos = full_opt.find_first_of("/");
    int equPos = full_opt.find_first_of("=");
    if (slashPos == 0 || equPos == 0 || equPos < slashPos ){
      WriteMsg::write(CMSG_GENCFG_WRONG_ARG_FORMAT);
      continue;
    }

    string section = full_opt.substr(0, slashPos);
    string opt = full_opt.substr(slashPos+1, equPos-slashPos-1);
    string value = full_opt.substr(equPos+1);

    int ret = writePrivateProfileString(section.c_str(),opt.c_str(),value.c_str(),config.c_str());
    if (ret == 0) {
      WriteMsg::write(CMSG_GENCFG_ERR_REWRITE_OPTION, opt.c_str());
    }
  }

  MAIN_END

  return 0;
}
