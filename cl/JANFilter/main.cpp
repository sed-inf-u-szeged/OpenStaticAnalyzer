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

#include <java/inc/java.h>
#include <common/inc/FileSup.h>
#include <cstring>
#include <common/inc/Stat.h>
#include <io/inc/CsvIO.h>

#define PROGRAM_NAME "JANFilter"
#define EXECUTABLE_NAME "JANFilter"

#include <MainCommon.h>
#include "messages.h"

using namespace std;
using namespace common;
using namespace columbus;
using namespace columbus::java::asg;

// command line
static string fltp;
static bool filterRefl = false;
static bool safemode = false;
static string lst;
list<string> files;

// Callback methods for argument processing
static bool ppFilterPath (const Option *o, char *argv[]) {
  fltp = argv[0];
  return true;
}

static bool ppFilterRefl (const Option *o, char *argv[]) {
  filterRefl = true;
  return true;
}

static bool ppList (const Option *o, char *argv[]) {
  lst = argv[0];
  return true;
}

static bool ppSafemode (const Option *o, char *argv[]) {
  safemode = true;
  return true;
}

static void ppFile(char *filename) {
  files.push_back(filename);
}

const Option OPTIONS_OBJ [] = {
  CL_REFLECTION_FILTER
  CL_SAFEMODE
  CL_FLTP
  CL_INPUT_LIST
  COMMON_CL_ARGS
};

void clErrorStr(const char* message) {
  WriteMsg::write(CMSG_ERROR_MSG);
  Help();
  exit(common::retBadArgError);
}

void checkInputFile() {
  if (files.size() == 0) clError();
}

int main(int argc, char *argv[]) {

  MAIN_BEGIN

    MainInit(argc, argv, "-");

    if (!lst.empty()) {
      common::loadStringListFromFile(lst,files);
    }

    checkInputFile();
    // processing filter path(s)

    DirectoryFilter filter;

    if (!fltp.empty()) {
      if (common::pathFileExists(fltp, false)) {
        filter.openFilterFile(fltp);
      } else {
        WriteMsg::write(CMSG_CANNOT_OPEN_FILE, fltp.c_str());
        return EXIT_FAILURE;
      }
    }

    for (list<std::string>::iterator iter=files.begin(); iter!=files.end(); iter++) {
      string inputFile=(*iter);

      // loading the ASG
      RefDistributorStrTable strTable;
      Factory fact(strTable);

      CsiHeader csiHeader;

  #ifndef _DEBUG
      try {
  #endif
        fact.load(inputFile, csiHeader);
  #ifndef _DEBUG
      } catch (IOException e) {
        WriteMsg::write(CMSG_CANNOT_READ_FILE, inputFile.c_str());
        exit(EXIT_FAILURE);
      }
  #endif

      // loading filter
      fact.initializeFilter();
      size_t inLen = inputFile.length();
      string filterFile;

      if ((strlen(".jsi") <= inLen) && (inputFile.substr(inLen - strlen(".jsi")) == string(".jsi"))) {
        filterFile = inputFile.substr(0, inLen - strlen(".jsi"));
        filterFile += ".fjsi";
      } else if ((strlen(".ljsi") <= inLen) && (inputFile.substr(inLen - strlen(".ljsi")) == string(".ljsi"))) {
        filterFile = inputFile.substr(0, inLen - strlen(".ljsi"));
        filterFile += ".fjsi";
      } else {
        filterFile += ".fjsi";
        common::WriteMsg::write(CMSG_WRONG_FILE_FORMAT);
      }

      if (!common::pathFileExists(filterFile, false)) {
        common::WriteMsg::write(CMSG_FILTER_DOES_NOT_EXIST);
      } else if (common::fileTimeCmp(filterFile, inputFile) == -1) {
        common::WriteMsg::write(CMSG_FILTER_FILE_DEPRECATED);
      } else {
        try {
          common::WriteMsg::write(CMSG_LOAD_FILTER_FILE, filterFile.c_str());
          fact.loadFilter(filterFile);
        } catch (IOException e) {
          common::WriteMsg::write(CMSG_FILTER_CANNOT_LOAD, filterFile.c_str());
        }
        fact.turnFilterOn();
      }

      JANFilter janFilter(fact, filter, filterRefl);
      AlgorithmPreorder ap;
      ap.setVisitSpecialNodes(true, true);
      if (safemode)
        ap.setSafeMode();
      ap.run(fact, janFilter, *fact.getRoot());

      // saving the filter
      common::WriteMsg::write(CMSG_SAVE_FILTER_FILE, filterFile.c_str());
      fact.saveFilter(filterFile);
    }
  MAIN_END

  return 0;
}
