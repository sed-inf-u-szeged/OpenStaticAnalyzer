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


#define PROGRAM_NAME "Pylint2Graph"
#define EXECUTABLE_NAME "Pylint2Graph"

#include <iostream>
#include <MainCommon.h>
#include <common/inc/Stat.h>

#include "../inc/messages.h"
#include "../inc/PylintRulMaker.h"
#include "../inc/PylintRunner.h"
#include "../inc/Pylint2Graph.h"

using namespace std;
using namespace common;
using namespace columbus;


static bool makeRul = false;
static string pylintMessagesTxt;
static string pylintIdsTxt;
static string outGraph;
static string outTxt;
static string changepathfrom;
static string changepathto;
static string limFile;
static string rulFile = "Pylint.rul.md";
static string rulConfig = "Default";
static bool exportRul;
static bool runPylint = false;
static string pythonBinary;
static string pylintDir;
static string pylintrc;
static string projectBaseDir;
static string pylintOut;
static list<string> pylintOptions;
static list<string> inputFiles;

static bool ppMakeRul(const Option *o, char *argv[]) {
  makeRul = true;
  pylintMessagesTxt = argv[0];
  return true;
}

static bool ppIds(const Option *o, char *argv[]) {
  pylintIdsTxt = argv[0];
  return true;
}

static bool ppGraph(const Option *o, char *argv[]) {
  outGraph = argv[0];
  return true;
}

static bool ppOut(const common::Option *o, char *argv[]) {
  outTxt = argv[0];
  return true;
}

static bool ppLimFile(const Option *o, char *argv[]) {
  limFile = argv[0];
  return true;
}

static bool ppRul(const Option *o, char *argv[]) {
  rulFile = argv[0];
  return true;
}

static bool ppRulConfig(const Option *o, char *argv[]) {
  rulConfig = argv[0];
  return true;
}

static bool ppExportRul(const Option *o, char *argv[]) {
  exportRul = true;
  return true;
}

static bool ppRunPylint(const Option *o, char *argv[]) {
  runPylint = true;
  return true;
}

static bool ppPythonBinary(const Option *o, char *argv[]) {
  pythonBinary = argv[0];
  return true;
}

static bool ppPylintDir(const Option *o, char *argv[]) {
  pylintDir = argv[0];
  return true;
}

static bool ppPylintrc(const Option *o, char *argv[]) {
  pylintrc = argv[0];
  return true;
}

static bool ppProjectBaseDir(const Option *o, char *argv[]) {
  projectBaseDir = argv[0];
  return true;
}

static bool ppPylintOut(const Option *o, char *argv[]) {
  pylintOut = argv[0];
  return true;
}

bool ppPylintOptions(const common::Option *o, char *argv[]) {
  pylintOptions.push_back(argv[0]);
  return true;
}

static void ppFile(char *filename) {
  inputFiles.push_back(filename);
}

const common::Option OPTIONS_OBJ [] = {
  // options for making rul file
  { false,  "-makerul",         1, "pylint_messages.txt",   0,  OT_WS,      ppMakeRul,            NULL,     "Makes rul file from the pylint messages file."},
  { false,  "-ids",             1, "pylint_ids.txt",        0,  OT_WS,      ppIds,                NULL,     "File which contains previous rule ids." },
  // options for running pylint
  { false,  "-runpylint",       0, "",                      0,  OT_NONE,    ppRunPylint,          NULL,     "Runs Pylint checker."},
  { false,  "-pythonBinary",    1, "file",                  0,  OT_WC,      ppPythonBinary,       NULL,     "Path of the Python 2.7/3.x binary."},
  { false,  "-pylintdir",       1, "directory",             0,  OT_WC,      ppPylintDir,          NULL,     "Directory of the Pylint checker. It will be added to the PYTHONPATH environment variable."},
  { false,  "-pylintrc",        1, "file",                  0,  OT_WC,      ppPylintrc,           NULL,     "Configuration file for Pylint."},
  { false,  "-projectbasedir",  1, "directory",             0,  OT_WC,      ppProjectBaseDir,     NULL,     "Base directory of the input project."},
  { false,  "-pylintout",       1, "file",                  0,  OT_WC,      ppPylintOut,          NULL,     "Output file for the Pylint results."},
  { false,  "-pylintOptions",   1, "string",                0,  OT_WC,      ppPylintOptions,      NULL,     "Passes command line options to Pylint. Options with arguments can be passed with successive -pylintOptions options."},
  // options for collecting pylint results
  { false,  "-graph",           1, "filename",              0,  OT_WC,      ppGraph,              NULL,     "Save binary graph output to the given file."},
  { false,  "-out",             1, "filename",              0,  OT_WC,      ppOut,                NULL,     "If it is specified then the list of rule violations will be written into this file."
                                                                                                            " Otherwise they will be dumped to the standard output."},
  CL_LIM
  CL_RUL_AND_RULCONFIG("Pylint.rul.md")
  CL_EXPORTRUL
  COMMON_CL_ARGS
};


int main(int argc, char* argv[]) {
  MAIN_BEGIN

    MainInit(argc, argv, "-");

    if (!common::pathIsAbsolute(rulFile.c_str())) {
      rulFile = getExecutableProgramDir() + rulFile;
    }

    if (!makeRul && !runPylint) {
      if (inputFiles.size() != 1) {
        WriteMsg::write(CMSG_WRONG_INPUT);
        clError();
      }
    }

    updateMemoryStat(true);

    if (runPylint) {
      if (pythonBinary.empty() || pylintDir.empty() || pylintrc.empty() || projectBaseDir.empty() || pylintOut.empty()) {
        WriteMsg::write(CMSG_RUNPYLINT_OPTION_ERROR);
        exit(EXIT_FAILURE);
      }
    }

    if (makeRul) {
      PylintRulMaker pylintRulMaker;
      pylintRulMaker.makeRul(pylintMessagesTxt, pylintIdsTxt, rulFile);

    } else if (runPylint) {
      PylintRunner runner;
      runner.run(projectBaseDir, pythonBinary, pylintDir, pylintrc, pylintOut, pylintOptions);
      updateMemoryStat();

    } else {
      std::ostream* out = &cout;
      std::ofstream ofs;

      if (!outTxt.empty()) {
        ofs.open(outTxt.c_str());
        if (!ofs.is_open()) {
          WriteMsg::write(CMSG_CANNOT_OPEN_FILE, outTxt.c_str());
        } else {
          out = &ofs;
        }
      }

      updateMemoryStat();

      Pylint2Graph pylint2Graph(rulFile, rulConfig, *out, changepathfrom, changepathto);
      pylint2Graph.buildGraph(limFile);
      pylint2Graph.convertResults(inputFiles.front());
      
      updateMemoryStat();

      if (!outGraph.empty())
        pylint2Graph.saveResultGraph(outGraph, exportRul);
    }

  MAIN_END

  return 0;
}
