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

#define PROGRAM_NAME "GraphDumpTool"
#define EXECUTABLE_NAME "GraphDump"

#include <graph/inc/graph.h>
#include <iostream>
#include <vector>

#include <MainCommon.h>
#include <common/inc/FileSup.h>
#include <common/inc/WriteMessage.h>
#include <common/inc/Stat.h>
#include <graphsupport/inc/CsvExporter.h>
#include <graphsupport/inc/SarifExporter.h>
#include "../inc/messages.h"

using namespace std;
using namespace common;
using namespace columbus;
using namespace columbus::graph;

static vector<string> files;
static string csvFile;
static string xmlFile;
static string jsonFile;
static string sarifFile;
static char csvSeparator = ',';
static char csvDmark = '.';
static string sarifSeverityLevel = "2345c";

static void ppFile(char *filename) {
  files.push_back(filename);
}

static bool ppCsvOutput(const Option *o, char *argv[]) {
  csvFile = argv[0];
  return true;
}

static bool ppCsvOutputDefault(const Option *o) {
  if (!files.empty()) {
    csvFile = replaceExtension(files[0], ".csv");
  }
  return true;
}

static bool ppSaveXML (const common::Option *o, char *argv[]) {
  xmlFile = argv[0];
  return true;
}

static bool ppSaveXMLDefault (const common::Option *o) {
  if (!files.empty()) {
    xmlFile = replaceExtension(files[0], ".xml");
  }
  return true;
}

static bool ppSaveJSON (const common::Option *o, char *argv[]) {
  jsonFile = argv[0];
  return true;
}

static bool ppSaveJSONDefault (const common::Option *o) {
  if (!files.empty()) {
    jsonFile = replaceExtension(files[0], ".json");
  }
  return true;
}


static bool ppSarifOutput (const common::Option *o, char *argv[]) {
  sarifFile = argv[0];
  return true;
}

static bool ppSarifOutputDefault (const common::Option *o) {
  if (!files.empty()) {
    sarifFile = replaceExtension(files[0], ".sarif");
  }
  return true;
}

static bool ppSarifSeverity(const common::Option *o, char *argv[]) {
	if (argv[0][0]) {
		sarifSeverityLevel = "";
	}
  for (char *c = argv[0]; *c; c++) {
      if ((*c >= '1' && *c <= '5') || (*c == 'c' || *c == 'C')) {
          sarifSeverityLevel += *c;
      }
      else {
          sarifSeverityLevel = "2345c";
          break;
      }
  }
  return true;
}

static bool ppCsvSeparator (const common::Option *o, char *argv[]) {
  if (strcmp(argv[0], "\\t") == 0)
    csvSeparator = '\t';
  else if (argv[0] != 0) 
    csvSeparator = argv[0][0];
  
  return true;
}

static bool ppCsvDecimalMark (const common::Option *o, char *argv[]) {
  if (argv[0][0] != 0)
    csvDmark = argv[0][0];
  return true;
}

const Option OPTIONS_OBJ [] = {
  { false,  "-csv",     1, "filename",      1, OT_WC | OT_DEFAULT,  ppCsvOutput,  ppCsvOutputDefault, "Generate csv dump files with the given file name template."},
  CL_CSVSEPARATOR
  CL_CSVDECIMALMARK
  { false,  "-xml",     1, "filename",      1, OT_WC | OT_DEFAULT,  ppSaveXML,    ppSaveXMLDefault,   "Generate XML dump file."},
  { false,  "-json",    1, "filename",      1, OT_WC | OT_DEFAULT,  ppSaveJSON,    ppSaveJSONDefault,   "Generate JSON dump file."},
  { false,  "-sarif",   1, "filename",      1, OT_WC | OT_DEFAULT,  ppSarifOutput,  ppSarifOutputDefault, "Generate SARIF dump files with the given file name template."},
  CL_SARIFSEVERITY
  COMMON_CL_ARGS
};


int main(int argc, char** argv) {
  MAIN_BEGIN

  // The message writer functions must be initialized before anything else.
  MainInit(argc, argv, "-");

  if(files.empty()) {
    WriteMsg::write(CMSG_NO_INPUT_FILE);
    clError();
  }

  if(files.size() > 1) {
    WriteMsg::write(CMSG_TOO_MANY_INPUT_FILES);
    clError();
  }

  common::WriteMsg::write(CMSG_LOAD_FILE, files[0].c_str());
  Graph g;
  g.loadBinary(files[0]);
  
  if (!csvFile.empty()) {
    common::WriteMsg::write(CMSG_CSV_DUMP);
    graphsupport::exportReadableMetricsCSV(g, csvFile, csvSeparator, csvDmark);
  }
  
  if (!xmlFile.empty()) {
    common::WriteMsg::write(CMSG_XML_DUMP);
    g.saveXML(xmlFile);
  }

  if (!jsonFile.empty())
  {
    common::WriteMsg::write(CMSG_JSON_DUMP);
    g.saveJSON(jsonFile);
  }

  if (!sarifFile.empty()) {
    common::WriteMsg::write(CMSG_SARIF_DUMP);
    graphsupport::exportToSarif(g, sarifFile, sarifSeverityLevel);
  }

  MAIN_END

  return 0;
}
