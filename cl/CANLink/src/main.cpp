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
#include "ReleaseVersion.h"
#include "ErrorCodes.h"
#include "common/inc/Arguments.h"
#include "common/inc/Stat.h"
#include <io/inc/CsvIO.h>
#include <common/inc/FileSup.h>
#include <common/inc/DirectoryFilter.h>
#include <Environment.h>

#define PROGRAM_NAME "CANLink"
#define EXECUTABLE_NAME "CANLink"

#include "MainCommon.h"

#include "common/inc/WriteMessage.h"
#include "../inc/messages.h"

using namespace std;
using namespace common;
using namespace columbus;

//-- data for CmdLine -->
static string out;
static string statFile;
static string fList; //list of the input files
static string fltpFile;
static list<string> listOfAst;

#define STATMEMSIZE size

// Callback methods for argument processing
static bool ppOut(const Option *o, char *argv[]) {
  out= argv[0];
  return true;
}

static void ppFile(char *filename) {
  listOfAst.push_back(filename);
}

static bool ppFilter (const common::Option *o, char *argv[]) {
  fltpFile = argv[0];
  return true;
}

static bool ppStat(const Option *o, char *argv[]) {
  statFile = argv[0];
  return true;
}

static bool ppList (const Option *o, char *argv[]) {
  fList = argv[0];
  return true;
}

const Option OPTIONS_OBJ[]= {
  {false, "-out",           1, "filename",          1, OT_WS | OT_WC,      ppOut,                  NULL,    "Output file name"},
  {false, "-stat",          1, "filename",          0, OT_WS | OT_WC,      ppStat,                 NULL,    "Create statistic file for wrapper environment"},
  {false, "-ilist",         1, "filename",          0, OT_WC,              ppList,                 NULL,    "Name of the file, which contains the list of the input files"},
  {false, "-filter",        1, "filterfile",        0, OT_WC,              ppFilter,               NULL,    "Filter file (files are taken account only from these paths)"},

  COMMON_CL_ARGS};

int main(int argc, char *argv[])
{
  int ret = EXIT_SUCCESS;
  WriteMsg::setAutomaticFlush(true);
  MAIN_BEGIN

  MainInit(argc, argv, "-");

  loadStringListFromFile(fList, listOfAst);
  if (listOfAst.empty()) {
    common::WriteMsg::write(CMSG_NO_INPUT_FILE);
    clError();
  }

  if (out.empty()) {
    WriteMsg::write(CMSG_NO_OUTPUT_FILE);
    clError();
  }

  size_t numberOfAstFiles = 0;
  ofstream outputListFile(out.c_str());
  if (outputListFile)
  {
    for (auto& inputFileName : listOfAst)
    {
      if (pathFindExtension(inputFileName) == ".ast")
        ++numberOfAstFiles;
      outputListFile << indep_fullpath(inputFileName) << "\n";
    }
  }
  else
  {
    WriteMsg::write(CMSG_CAN_NOT_OPEN_OUTPUT_FILE, out.c_str());
    ret = EXIT_FAILURE;
  }

  timestat totaltime = getProcessUsedTime();
  memstat memory = getProcessUsedMemSize();

  WriteMsg::write(CMSG_STATISTICS);
  WriteMsg::write(CMSG_STAT_USER_TIME, totaltime.user);
  WriteMsg::write(CMSG_STAT_SYSTEM_TIME, totaltime.system);
  WriteMsg::write(CMSG_STAT_PEAK_MEMORY_USAGE, memory.size /  (1024 * 1024));

  if (!statFile.empty()) {
    bool writeHeader = false;

    if (!pathFileExists(statFile, false))
      writeHeader = true;

    io::CsvIO csv(statFile, io::IOBase::omAppend);

    if (writeHeader) {
      csv.writeColumn(CMSG_STAT_HEADER_CPU_TIME);
      csv.writeColumn(CMSG_STAT_HEADER_PEAK_MEMORY_USAGE);
      csv.writeColumn(CMSG_STAT_HEADER_OUTPUT_FILE);
      csv.writeColumn(CMSG_STAT_HEADER_NUMBER_OF_INPUT_FILES);
      csv.writeColumn(CMSG_STAT_HEADER_NUMBER_OF_CSI_FILES);
      csv.writeColumn(CMSG_STAT_HEADER_NUMBER_OF_WARNINGS);
      csv.writeNewLine();
    }

    string path;
    common::pathCanonicalize(path, out);
    csv.writeColumn((totaltime.user + totaltime.system) / 100.0f);
    csv.writeColumn((unsigned long)(memory.size / (1024 * 1024)));
    csv.writeColumn(path);
    csv.writeColumn((unsigned int)listOfAst.size());
    csv.writeColumn((unsigned int)numberOfAstFiles);
    csv.writeColumn(WriteMsg::getWasWarning());
    csv.writeNewLine();
  }

  MAIN_END

  return ret;
}
