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

#include <fstream>
#include <iostream>
#include <list>
#include <string>
#include <vector>
#include "messages.h"
#include <common/inc/Stat.h>

#include "PMD/PMDStrategy.h"

#define PROGRAM_NAME "PMD2Graph"
#define EXECUTABLE_NAME "PMD2Graph"

#include "MainCommon.h"

using namespace std;
using namespace columbus;
using namespace common;

// parameters
static string listFile;

//static string checker;
static bool makerul      = false;
static bool makeconfig   = false;
static bool makecsv      = false;

static string metrics;
static string groupedmetrics;
static string warnings;
static string rul_str;
static string rul_options;
static string rulConfig  = "Default";
static string config;
static string lst;
static string checkerbasedir;
static string changepathfrom;
static string changepathto;
static string lim;
static string separator = ";";
static string faulthunter_rul;
static bool exportRul = false;
static bool printstdout = false;
static std::string out; //name of the output file
PMD2GraphStat stats;

bool print_debug = false;

static string graph_filename;
static list<string> inputFiles;

//--------------------------------------------------------------

static bool ppMakeRul (const Option *o, char *argv[]) {
  makerul = true;
  return true;
}

static bool ppMakeCfg (const Option *o, char *argv[]) {
  makeconfig = true;
  return true;
}

static bool ppMakeCsv (const Option *o, char *argv[]) {
  makecsv = true;
  return true;
}

static bool ppMetrics (const Option *o, char *argv[]) {
  metrics = argv[0];
  return true;
}

static bool ppGroupedMetrics (const Option *o, char *argv[]) {
  groupedmetrics = argv[0];
  return true;
}

static bool ppWarnings (const Option *o, char *argv[]) {
  warnings = argv[0];
  return true;
}

static bool ppChkrBaseDir (const Option *o, char *argv[]) {
  checkerbasedir = argv[0];
  return true;
}

static bool ppLimFile (const Option *o, char *argv[]) {
  lim = argv[0];
  return true;
}

static bool ppRul (const Option *o, char *argv[]) {
  rul_str = argv[0];
  return true;
}

static bool ppRulOptions (const Option *o, char *argv[]) {
  rul_options = argv[0];
  return true;
}

static bool ppRulConfig (const Option *o, char *argv[]) {
  rulConfig = argv[0];
  return true;
}

static bool ppConfig (const Option *o, char *argv[]) {
  config = argv[0];
  return true;
}

static bool ppList (const Option *o, char *argv[]) {
  lst = argv[0];
  return true;
}

static bool ppGraph (const Option *o, char *argv[]) {
  graph_filename = argv[0];
  return true;
}

static bool ppExportRul(const Option *o, char *argv[]) {
  exportRul = true;
  return true;
}

static void ppFile(char *filename) {
  inputFiles.push_back(filename);
}

static bool ppOut (const Option *o, char *argv[]) {
  out = argv[0];
  return true;
}

static bool ppPrintStdOut (const Option *o, char *argv[]) {
  printstdout = true;
  return true;
}

static bool ppFaultHunterRul(const Option *o, char *argv[]) {
  faulthunter_rul = argv[0];
  return true;
}

const Option OPTIONS_OBJ [] = {
  { false,  "-makerul",         0, "",                  1,  OT_NONE,  ppMakeRul,        NULL,   "Making rul file based on input list file."},
  { false,  "-makeconfig",      0, "",                  1,  OT_NONE,  ppMakeCfg,        NULL,   "Making config file based on input rul file."},
  { false,  "-makecsv",         0, "",                  1,  OT_NONE,  ppMakeCsv,        NULL,   "Making csv and/or graph files based on input list file."},
  { false,  "-metrics",         1, "outputname",        0,  OT_WC,    ppMetrics,        NULL,   "Name of the metrics output."},
  { false,  "-groupedmetrics",  1, "outputname",        0,  OT_WC,    ppGroupedMetrics, NULL,   "Name of the grouped metrics output."},
  { false,  "-warnings",        1, "outputname",        0,  OT_WC,    ppWarnings,       NULL,   "Name of the warnings output."},
  { false,  "-checkerbasedir",  1, "path",              0,  OT_WC,    ppChkrBaseDir,    NULL,   "Path prefix in the checker's input files."},
  CL_LIM
  { false,  "-rul",             1, "rulfile",           0,  OT_WC,    ppRul,            NULL,   "Name of the rule file(in/out)."},
  { false,  "-ruloptions",      1, "listfile",          0,  OT_WC,    ppRulOptions,     NULL,   "Name of the rule option file(in)."},
  { false,  "-rulconfig",       1, "rulconfig",         0,  OT_WC,    ppRulConfig,      NULL,   "Name of the rule configuration file."},
  { false,  "-config",          1, "file",              0,  OT_WC,    ppConfig,         NULL,   "Name of the config file(out)."},
  { false,  "-lst",             1, "listfile",          0,  OT_WC,    ppList,           NULL,   "Name of the list file.(used by makerul and makecsv)"},
  { false,  "-graph",           1, "file",              0,  OT_WC,    ppGraph,          NULL,   "Save binary graph output."},
  { false,  "-out",             1, "file",              0,  OT_WC,    ppOut,            NULL,   "Specify the name of the output file. The list of rule violations will be dumped in it.\n"
                                                                                                "Either this or the -printstdout switch has to be provided."},
  { false,  "-printstdout",     0, "",                  0,  OT_NONE,  ppPrintStdOut,    NULL,   "Dump the detected rule violations to the standard output."},
  { false,  "-faulthunterrul",  1, "rulfile",           0,  OT_WC,    ppFaultHunterRul, NULL,   "Name of the FaultHunter rul file."},
  CL_EXPORTRUL
  COMMON_CL_ARGS
};

void checkInputFiles() {

  if ( !listFile.empty()) {
    ifstream ifs(listFile.c_str());
    if (ifs.is_open()) {
      string tmp;
      while (getline(ifs, tmp)) {
        if (!tmp.length())
          continue;
        if (tmp[tmp.length()-1]==0xD) { // handle DOS line-ends in unix
          inputFiles.push_back(tmp.substr(0,tmp.length()-1));
        } else {
          inputFiles.push_back(tmp);
        }
      }
      ifs.close();
    }
  }
}

void checkSeparator() {
  if (separator.length() == 3 && separator[0] == separator[2] && separator[0] == '"')
    separator = separator[1];
}

void checkCheckerSettings(){
  if( (makerul && makeconfig) ||
      (makerul && makecsv) ||
      (makecsv && makeconfig)){
        WriteMsg::write(CMSG_PMD2GRAPH_ARGS_MORE_THAN_ONE_PHASE);
        Help();
        exit(1);
  }
  if( !makerul && !makeconfig && !makecsv){
    WriteMsg::write(CMSG_PMD2GRAPH_ARGS_NO_PHASE_GIVEN);
    Help();
    exit(1);
  }

  if( makerul && (lst.empty() || rul_str.empty())){
    WriteMsg::write(CMSG_PMD2GRAPH_ARGS_MAKERUL_ERROR);
    Help();
    exit(1);
  }

  if( makeconfig && (lst.empty() || rul_str.empty())){
    WriteMsg::write(CMSG_PMD2GRAPH_ARGS_MAKECONFIG_ERROR);
    Help();
    exit(1);
  }
  
  if(makecsv && ((!printstdout && out.empty()) || (printstdout && !out.empty()))) {
    WriteMsg::write(CMSG_PMD2GRAPH_ARGS_OUT_PARAM_ERROR);
    Help();
    exit(1);
  }

  if( makecsv && (lim.empty() || lst.empty() || rul_str.empty() || (metrics.empty() && groupedmetrics.empty() && warnings.empty() && graph_filename.empty()))){

    WriteMsg::write(CMSG_PMD2GRAPH_ARGS_MAKECSV_ERROR);
    Help();
    exit(1);
  }

}

int main(int argc, char *argv[]) {
  MAIN_BEGIN
    MainInit(argc, argv, "-");

    checkInputFiles();
    checkSeparator();
    checkCheckerSettings();

    File_Names file_names;
    if(!lst.empty()) {
      if (!common::loadStringListFromFile(lst, file_names)) {
        WriteMsg::write(CMSG_PMD2GRAPH_CANT_LOAD_LIST_FILE, lst.c_str());
        return EXIT_FAILURE;
      }
    }

    if(!common::pathIsAbsolute(rul_str.c_str()))
      rul_str = getExecutableProgramDir() + rul_str;
    PMDStrategy pmd_strategy;
    if(makerul){
      pmd_strategy.makeRul(file_names, rul_str, rulConfig, rul_options, faulthunter_rul);
    }else if(makeconfig){
      pmd_strategy.makeConfig(file_names, rul_str, rulConfig, config);
    } else if(makecsv){
      graph::Graph graph;
      FILE *f;
      if( !out.empty()) {
        WriteMsg::write(CMSG_PMD2GRAPH_DUMPING_OUTPUT_TO_FILE, out.c_str());
        f = fopen(out.c_str(), "wt");
        if(!f) {
          WriteMsg::write(CMSG_PMD2GRAPH_ERROR_OPENING_DUMP_FILE, out.c_str());
          f = stdout;
        }
      } else {
        WriteMsg::write(CMSG_PMD2GRAPH_DUMPING_OUTPUT_TO_STANDARD_OUTPUT);
        f = stdout;
      }
      pmd_strategy.makeCsv(lim, rul_str, rulConfig, file_names, metrics, groupedmetrics, warnings, checkerbasedir, changepathfrom, changepathto, f);
      if(f != stdout) {
        fclose(f);
      }
      
      pmd_strategy.addLicenseTypeToTheGraphHeader(EXECUTABLE_NAME);

      if (!graph_filename.empty())
        pmd_strategy.saveGraph(graph_filename, exportRul);
      
    }
    if(print_debug) {
      PMD2GraphStat::ErrorFileList::iterator it = stats.error_files.begin();
      while(it != stats.error_files.end()) {
        WriteMsg::write(CMSG_PMD2GRAPH_ERROR_ANALYZE_FILE, *it);
        ++it;
      }
    }

  MAIN_END

  return 0;
}
