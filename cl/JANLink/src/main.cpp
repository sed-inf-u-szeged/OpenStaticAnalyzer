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

#define PROGRAM_NAME "JANLink (Java Linker)"
#define EXECUTABLE_NAME "JANLink"

#include <MainCommon.h>
#include <fstream>
#include <time.h>
#include "../inc/Linker.h"
#include "../inc/messages.h"
#include <common/inc/FileSup.h>
#include <common/inc/Stat.h>
#include <common/inc/PlatformDependentDefines.h>
#include <common/inc/DirectoryFilter.h>
#include <io/inc/CsvIO.h>
#include <iostream>

using namespace common;
using namespace columbus;

//-- data for CmdLine -->
static std::string out, outflt, lst, mem, fltp, check;
static bool filterRefl = false;
static bool safemode = false;

static std::list<std::string> files;
// <---------------------

const std::string oext = ".ljsi";
const std::string ofltext = ".fjsi";
const std::string jmlext = ".jml";

// Callback methods for argument processing
static bool ppOut (const Option *o, char *argv[]) {
  out = argv[0];
  return true;
}

static bool ppList (const Option *o, char *argv[]) {
  lst = argv[0];
  return true;
}

static bool ppFilterPath (const Option *o, char *argv[]) {
  fltp = argv[0];
  return true;
}

static bool ppFilterRefl (const Option *o, char *argv[]) {
  filterRefl = true;
  return true;
}

static bool ppSafemode (const Option *o, char *argv[]) {
  safemode = true;
  return true;
}

static bool ppMem (const Option *o, char *argv[]) {
  mem = argv[0];
  return true;
}

static bool ppCheck (const Option *o, char *argv[]) {
  check = argv[0];
  return true;
}

static void ppFile(char *filename) {
  files.push_back(filename);
}

const Option OPTIONS_OBJ [] = {
  { false,  "-out",           1,   "filename",              0, OT_WC,      ppOut,            NULL,   "The linked ASG file."},
  { false,  "-maxmem",        1,   "number",                0, OT_WC,      ppMem,            NULL,   "Sets the maximum memory usage in MB."},
  { false,  "-checklist",     1,   "filename",              0, OT_WC,      ppCheck,          NULL,   "Output list file. Delete the same ASG's from the original list (uses timestamps of the graph headers)."},
  CL_REFLECTION_FILTER
  CL_SAFEMODE
  CL_FLTP
  CL_INPUT_LIST
  COMMON_CL_ARGS
};


void clError(WriteMsg::MsgLevel msgLevel = WriteMsg::mlError, const char* message = "Bad command line!") {
  WriteMsg::write(msgLevel, message);
  Help();
  exit(common::retBadArgError);
}

void checkOutputFile() {
  if (!check.empty()) {
    return;
  }

  if (out.empty()) {
    clError(CMSG_NO_OUTPUT_FILE);
  }

  outflt = pathRemoveExtension(out) + ofltext;
}

void checkListFile() {
  if (lst == "") return;

#ifdef __unix__
  if (lst[0] == '~') {  // under linux '~' is resolved before examining if it is absolute path or not
    char* home = getenv("HOME");
    if (home != NULL)
      lst = std::string(home) + lst.substr(1);
    else
      lst = lst.substr(1);
  }
#endif

  std::ifstream ifs(lst.c_str());
  if (!ifs.is_open()) return;

  files.clear();
  std::set<std::string> fset;

  std::string line;
  while (getline(ifs , line)) {
    if (!line.empty() && (*line.rbegin() == 0xD))  // handle DOS line-ends in unix
      line.resize(line.size() - 1);

    if (line.empty())
      continue;
    line = common::correctDirDivs(line);
    if (fset.insert(line).second)
      files.push_back(line);
  }

  ifs.close();}

void checkInputFiles() {
  for (std::list<std::string>::iterator it = files.begin(); it != files.end(); it++)
    *it = common::correctDirDivs(*it);
}

ErrorCode rewriteFileList() {
  ErrorCode ec = retOk;

  std::map<std::string, std::string> ljsiFileMap;
  for (std::list<std::string>::iterator it = files.begin(); it != files.end(); ++it) {

    columbus::RefDistributorStrTable tmpStt;
    columbus::java::asg::Factory tmpFact(tmpStt);

    WriteMsg::write(CMSG_LOAD_HEADER, it->c_str());
    CsiHeader tmpHeader;
#ifndef _DEBUG
    try {
#endif
      tmpFact.loadHeader(*it, tmpHeader);
#ifndef _DEBUG
    } catch (IOException e) {
      WriteMsg::write(CMSG_CANNOT_OPEN_FILE, it->c_str());
      ec = retASGLoadWarning;
      continue;
    }
#endif

    std::string timestamp;
    if (!tmpHeader.get(Linker::TIME_STAMP, timestamp)) {
      WriteMsg::write(CMSG_MISSING_TIMESTAMP, it->c_str());
      return retOtherError;
    }

    std::string filename(*it);
    std::pair<std::map<std::string, std::string>::iterator, bool> ret = ljsiFileMap.insert(make_pair(timestamp, filename));
    if (!ret.second) {
      WriteMsg::write(CMSG_SKIP_DUPLICATE, filename.c_str(), timestamp.c_str(), ret.first->second.c_str());
    }
  }

  if (ljsiFileMap.empty()) {
    WriteMsg::write(CMSG_NO_INPUT_LOADED);
    return retFileError;
  }

  WriteMsg::write(CMSG_SAVING_NEW_LIST, check.c_str());
  std::ofstream ofs(check.c_str());
  if (ofs.is_open()) {
    for (std::map<std::string, std::string>::iterator it = ljsiFileMap.begin(); it != ljsiFileMap.end(); ++it) {
      ofs << it->second << std::endl;
    }
    ofs.close();
  } else {
    WriteMsg::write(CMSG_CANNOT_OPEN_FILE, check.c_str());
    return retFileError;
  }

  return ec;
}

int main(int argc, char *argv[]) {
  common::ErrorCode ec = common::retOk;

  MAIN_BEGIN

    MainInit(argc, argv, "-");

    checkOutputFile();
    checkListFile();
    checkInputFiles();

    if (files.empty()) {
      clError(CMSG_NO_INPUT_FILES);
    }

    if (!check.empty()) {
      return rewriteFileList();
    }

    DirectoryFilter filter;
    if (!fltp.empty()) {
      if (common::pathFileExists(fltp, false)) {
        filter.openFilterFile(fltp);
      } else {
        WriteMsg::write(CMSG_CANNOT_OPEN_FLTP, fltp.c_str());
        return EXIT_FAILURE;
      }
    }

    Linker::JANLinkStat janlinkStat;
    Linker linker(out, outflt, false, mem, filter, filterRefl, safemode, janlinkStat, "");
    ec = linker.link(files);
    if (ec == common::retLinkingOK)
      ec = retOk;

  MAIN_END

  return ec;
}
