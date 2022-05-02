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

#define PROGRAM_NAME "Cppcheck2Graph"
#define EXECUTABLE_NAME "Cppcheck2Graph"

#include <cstdlib>
#include <xercesc/sax2/SAX2XMLReader.hpp>
#include <xercesc/sax2/XMLReaderFactory.hpp>
#include <xercesc/sax2/DefaultHandler.hpp>
#include <xercesc/sax2/Attributes.hpp>
#include <xercesc/util/XMLString.hpp>
#include <MainCommon.h>
#include <common/inc/Stat.h>
#include <io/inc/CsvIO.h>

#include "../inc/RuleConverter.h"
#include "../inc/ResultConverter.h"
#include "../inc/messages.h"

using namespace std;
using namespace common;
using namespace columbus;
using namespace columbus::cppcheck2graph;

static string configFileName;
static string errorListFileName;
static string groupsFileName;
static string graphFileName;
static string outputFileName;
static string limFileName;
static string rul_s = "Cppcheck.rul.md";
static string rulConfig = "Default";
static bool exportRul = false;
static string fList;
static list<string> listOfFile;
static size_t peakMemory = 0;

static bool ppMakeRul(const Option *o, char *argv[]) {
  errorListFileName = argv[0];
  groupsFileName = argv[1];
  configFileName = argv[2];
  return true;
}

static bool ppGraph(const Option *o, char *argv[]) {
  graphFileName = argv[0];
  return true;
}

static bool ppOut(const Option *o, char *argv[]) {
  outputFileName = argv[0];
  return true;
}

static bool ppLimFile(const Option *o, char *argv[]) {
  limFileName = argv[0];
  return true;
}

static bool ppRul (const Option *o, char *argv[]) {
  rul_s = argv[0];
  return true;
}

static bool ppRulConfig (const Option *o, char *argv[]) {
  rulConfig = argv[0];
  return true;
}

static bool ppExportRul(const Option *o, char *argv[]) {
  exportRul = true;
  return true;
}

static bool ppList(const Option *o, char *argv[]) {
  fList = argv[0];
  return true;
}

static void ppFile(char *filename) {
  listOfFile.push_back(filename);
}


const common::Option OPTIONS_OBJ [] = {
  { false,  "-makerul",         3, "errorlist.xml errorgroups.xml options.csv",  0,  OT_WS,  ppMakeRul,    NULL,   "Making rul file from the error list of the cppcheck (2. version of the XML file is required)."},
  { false,  "-graph",           1, "filename",          0,  OT_WC,  ppGraph,      NULL,   "Save binary graph output."},
  { false,  "-out",             1, "filename",          0,  OT_WC,  ppOut,        NULL,   "Specify the name of the output file. The list of rule violations will be dumped in it.\n"},
  CL_INPUT_LIST
  CL_LIM
  CL_RUL_AND_RULCONFIG("Cppcheck.rul.md")
  CL_EXPORTRUL
  COMMON_CL_ARGS
};

static inline void updateMemStat(size_t *max_mem) {
  memstat ms = getProcessUsedMemSize();
  if (*max_mem < ms.size) {
    *max_mem = ms.size;
  }
}

int main(int argc, char* argv[]) {
  int ret = EXIT_SUCCESS;
  MAIN_BEGIN

  MainInit(argc, argv, "-");

  if( !errorListFileName.empty() ){
    // Generating rul file from cppcheck error list
    RuleConverter converter(rulConfig);
    converter.process(configFileName, errorListFileName, groupsFileName);
    converter.saveRulFile(rul_s);
  } else {
    loadStringListFromFile(fList, listOfFile);
    if (listOfFile.empty()) {
      WriteMsg::write(CMSG_NO_INPUT_FILE);
    }
    if (graphFileName.empty()) {
      WriteMsg::write(CMSG_NO_OUTPUT_FILE);
      clError();
    }

    // Converting cppcheck output
    ResultConverter converter(limFileName, outputFileName, rul_s, rulConfig, exportRul, "", "");
    updateMemStat(&peakMemory);
    for(list<string>::iterator file = listOfFile.begin(); file != listOfFile.end(); ++file){
      if(pathFileExists(*file + ".err", false))
        converter.process(*file + ".err");
      else {
        WriteMsg::write(CMSG_FILE_NOT_EXISTS, (*file + ".err").c_str());
        ret = EXIT_FAILURE;
      }
    }
    updateMemStat(&peakMemory);
    converter.aggregateWarnings();
    converter.saveResultGraph(graphFileName, false);

    updateMemStat(&peakMemory);

  }

  MAIN_END
  
  return ret;
}
