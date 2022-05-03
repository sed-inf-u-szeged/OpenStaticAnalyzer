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

#include <cstdio>
#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <algorithm>
#include "messages.h"

#define PROGRAM_NAME "CANConfig"
#define EXECUTABLE_NAME "CANConfig"

#define PREDEFINED_MACROS_FILENAME "predefined_macros.txt"
#define PREDEFINED_MACROS_FULL_FILENAME "predefined_macros_full.txt"
#define CAN_CONFIG_FILENAME        "can.ini"

#include <MainCommon.h>
#include <common/inc/FileSup.h>
#include <common/inc/StringSup.h>
#include <common/inc/PlatformDependentDefines.h>

using namespace common;
using namespace std;

static string directoryOfTheBinary;
static string outputDirectoryName = ".";
static string inputCompiler;
static string outputFilenname = CAN_CONFIG_FILENAME;
static bool   gccMode = false;

static string clangInternalMacros[] = {
  "----"
};

static string clInternalMacros[] = {
  "----"
};

bool loadFileByLine(const string& filename, vector<string>& lines) {
  string line;
  ifstream input(filename.c_str());
  if (input.is_open()) {
    while (input.good()) {
      getline(input, line);
      if (!line.empty())
        lines.push_back(line); 
    }
    input.close();
  } else 
    return false;
    
  return true;
}

#ifdef GENERATE_MACROS

static string createPredefinedMacroCheckClangCommandLine(bool cpp ) {
  return "echo \" \" | \"" + inputCompiler + "\" -x " + 
          (cpp ? " c++" : " c") +
         " - -E -dM";
}

static void reformatLine(string& line) {
  if (line.size() > 8)
    line = line.substr(8);  // "#define "
}


static void createClangMacros(bool cpp, vector<string>& macros) {
  string const tmpFile = "tmpfile";
  string command = createPredefinedMacroCheckClangCommandLine(cpp);
  
  if (common::run(command, false, tmpFile)) {
    WriteMsg::write( CMSG_COMMAND_EXECUTION_FAILED, command.c_str());
    exit(EXIT_FAILURE);
  }

  if (!loadFileByLine(tmpFile, macros)) {
    WriteMsg::write( CMSG_LOAD_PREDEFINED_MACROS_FAILED, tmpFile.c_str());
    exit(EXIT_FAILURE);
  }
  
  for_each(macros.begin(), macros.end(), reformatLine);
  sort(macros.begin(), macros.end());
 
  pathDeleteFile(tmpFile);
}

static void writeMacroIfNeeded(ofstream& out, const string& line, bool clang) {
  
  if (clang) {
    for (size_t i = 0; i < sizeof(clangInternalMacros) / sizeof(string); ++i)
      if (line.find(clangInternalMacros[i]) == 0)
        return;
  } else {

    for (size_t i = 0; i < sizeof(clInternalMacros) / sizeof(string); ++i)
      if (line.find(clInternalMacros[i]) == 0)
        return;
  }
  out << line << endl;
}

static void generateMacroFile(const vector<string>& cMacros, const vector<string>& cppMacros, bool clang) {
  vector<string>::const_iterator cit = cMacros.begin();
  vector<string>::const_iterator cppit = cppMacros.begin();

  const string predefinedMacroFileName = outputDirectoryName + DIRDIVSTRING PREDEFINED_MACROS_FILENAME;
  ofstream pdefMacroFile(predefinedMacroFileName.c_str());
  const string predefinedMacroFullFileName = outputDirectoryName + DIRDIVSTRING PREDEFINED_MACROS_FULL_FILENAME;
  ofstream pdefMacroFullFile(predefinedMacroFullFileName.c_str());

  if (!pdefMacroFile.is_open()) {
    WriteMsg::write( CMSG_ERROR_OPEN_FILE, predefinedMacroFileName.c_str());
    exit(EXIT_FAILURE);
  }

  if(!pdefMacroFullFile.is_open()) {
    if(pdefMacroFile.is_open())
      pdefMacroFile.close();
    WriteMsg::write( CMSG_ERROR_OPEN_FILE, predefinedMacroFullFileName.c_str());
    exit(EXIT_FAILURE);
  }

  while (cit != cMacros.end() && cppit != cppMacros.end()) {
    if (*cit == *cppit) {
      writeMacroIfNeeded(pdefMacroFile, *cit, clang);
      pdefMacroFullFile << *cit << endl;
      ++cit;
      ++cppit;
    } else if (*cit < *cppit) {
      writeMacroIfNeeded(pdefMacroFile, *cit, clang);
      pdefMacroFullFile << *cit << endl;
      ++cit;
    } else {
      writeMacroIfNeeded(pdefMacroFile,  *cppit, clang);
      pdefMacroFullFile << *cppit << endl;
      ++cppit;
    }
  }
    
  while (cit != cMacros.end()) {
    writeMacroIfNeeded(pdefMacroFile, *cit, clang);
    pdefMacroFullFile << *cit << endl;
    ++cit;
  }
    
  while (cppit != cppMacros.end()) {
    writeMacroIfNeeded(pdefMacroFile,  *cppit, clang);
    pdefMacroFullFile << *cppit << endl;
    ++cppit;
  }
    
  pdefMacroFile.close();
  pdefMacroFullFile.close();
}
#endif

#ifdef __linux

enum class LanguageConfiguration
{
  c,
  cpp
};

enum class LibCppConfiguration
{
  none,
  libstdcpp,
  libcpp
};

static string createIncludeSearchCheckCommandLine(LanguageConfiguration languageConfiguration, LibCppConfiguration libcppConfiguration)
{
  string langConfig;
  switch (languageConfiguration)
  {
    case LanguageConfiguration::c     : langConfig = "c"; break;
    case LanguageConfiguration::cpp   : langConfig = "c++"; break;
  }

  string libcppConfig;
  switch (libcppConfiguration)
  {
    case LibCppConfiguration::none        : break;
    case LibCppConfiguration::libstdcpp   : libcppConfig = "-stdlib=libstdc++"; break;
    case LibCppConfiguration::libcpp      : libcppConfig = "-stdlib=libc++"; break;
  }

  return "echo \" \" | \"" + inputCompiler + "\" -x " + langConfig + " " + libcppConfig + " -v -E -";
}




static void getIncludes(LanguageConfiguration languageConfiguration, LibCppConfiguration libcppConfiguration, list<string>& includes)
{
  string const tmpFile = "tmpfile";
  string command = createIncludeSearchCheckCommandLine(languageConfiguration, libcppConfiguration);

  if (common::run(command, false, tmpFile, tmpFile)) {
    WriteMsg::write( CMSG_COMMAND_EXECUTION_FAILED, command.c_str());
    exit(EXIT_FAILURE);
  }

  vector<string> lines;
  if (!loadFileByLine(tmpFile, lines)) {
    WriteMsg::write( CMSG_LOAD_COMPILER_OUTPUT_FAILED, tmpFile.c_str());
    exit(EXIT_FAILURE);
  }

  bool inside = false;
  for(vector<string>::const_iterator lineIt = lines.begin(); lineIt != lines.end(); ++lineIt) {
    if (lineIt->find("#include <...> search starts here:") == 0)
      inside = true;
    else if (lineIt->find("End of search list.") == 0)
      inside = false;
    else if (inside)
      includes.push_back(trim(*lineIt));
  }

  pathDeleteFile(tmpFile);
}

static void createIncludes(LanguageConfiguration languageConfiguration, LibCppConfiguration libcppConfiguration, const string& iniFileName, const string& section) {
  list<string> includes;
  getIncludes(languageConfiguration, libcppConfiguration, includes);

  int counter = 1;
  for (const auto& path : includes)
    common::writePrivateProfileString(section.c_str(), ("path" + toString(counter++)).c_str(), path.c_str(), iniFileName.c_str());
}

static void generateClangIncludeSearchConfig() {
  string iniFileName = outputDirectoryName + DIRDIVSTRING + outputFilenname;
  createIncludes(LanguageConfiguration::c, LibCppConfiguration::none, iniFileName, "IncludePath_c");
  createIncludes(LanguageConfiguration::cpp, LibCppConfiguration::libcpp, iniFileName, "IncludePath_cpp");
}

static void generateGccIncludeSearchConfig() {
  string iniFileName = outputDirectoryName + DIRDIVSTRING + outputFilenname;
  createIncludes(LanguageConfiguration::c, LibCppConfiguration::none, iniFileName, "IncludePath_c");
  createIncludes(LanguageConfiguration::cpp, LibCppConfiguration::none, iniFileName, "IncludePath_cpp");
}


#elif defined _WIN32

static void generateClIncludeSearchConfig(const vector<string>& cIncludes, const vector<string>& cppIncludes) {
  string iniFileName = outputDirectoryName + DIRDIVSTRING + outputFilenname;

  int counter = 0;
  for (vector<string>::const_iterator incIt = cIncludes.begin(); incIt != cIncludes.end(); ++incIt)
    common::writePrivateProfileString("IncludePath_c", ("path" + toString(counter++)).c_str(), incIt->c_str(), iniFileName.c_str());

  counter = 0;
  for (vector<string>::const_iterator incIt = cppIncludes.begin(); incIt != cppIncludes.end(); ++incIt)
    common::writePrivateProfileString("IncludePath_cpp", ("path" + toString(counter++)).c_str(), incIt->c_str(), iniFileName.c_str());
  
}


static string createPredefinedMacroCheckClCommandLine(bool cpp, const string& filename) {
  return CL_PAR_PLUS + inputCompiler + CL_PAR_PLUS + " /EP " +
         (cpp ? " /TP /Bx" : " /TC /B1") +
         "\"" + directoryOfTheBinary + "Paramcheck.exe\" " +
         filename;
}

static void createClMacrosAndIncludes(bool cpp, vector<string>& macros, vector<string>& includes) {

  string const tmpInputFile = "tmpfile_empty";
  ofstream emptyFile(tmpInputFile.c_str());
  if (emptyFile.is_open())
    emptyFile.close();
  else {
    WriteMsg::write( CMSG_ERROR_CREATE_FILE, tmpInputFile.c_str());
    exit(EXIT_FAILURE);
  }

  string const tmpFileOut = "tmpfile1";
  string const tmpFileError = "tmpfile2";
  
  string command = createPredefinedMacroCheckClCommandLine(cpp, tmpInputFile);
  if (common::run(command, false, tmpFileOut, tmpFileError)) {
    WriteMsg::write( CMSG_COMMAND_EXECUTION_FAILED, command.c_str());
    pathDeleteFile(tmpInputFile);
    pathDeleteFile(tmpFileOut);
    pathDeleteFile(tmpFileError);
    exit(EXIT_FAILURE);
  }

  vector<string> macrosAndIncludes;
  if (!loadFileByLine(tmpFileOut, macrosAndIncludes)) {
    WriteMsg::write( CMSG_LOAD_PREDEFINED_MACROS_FAILED, tmpFileOut.c_str());
    pathDeleteFile(tmpInputFile);
    pathDeleteFile(tmpFileOut);
    pathDeleteFile(tmpFileError);
    exit(EXIT_FAILURE);
  }
  
  for (vector<string>::const_iterator it = macrosAndIncludes.begin(); it != macrosAndIncludes.end(); ++it) {
    if (it->find("#define") == 0) 
      macros.push_back(*it);
    else if (!it->empty())
      includes.push_back(removeQuotes(*it));
  }

#ifdef GENERATE_MACROS
  for_each(macros.begin(), macros.end(), reformatLine);
  sort(macros.begin(), macros.end());
#endif

  pathDeleteFile(tmpInputFile);
  pathDeleteFile(tmpFileOut);
  pathDeleteFile(tmpFileError);

}

#endif 

static bool ppOutDir(const Option *o, char *argv[]) {
  static bool alreadySet = false;
  if (alreadySet) 
    WriteMsg::write( CMSG_OUTPUT_DIRECTORY_PARAMETER_IS_SETED, outputDirectoryName.c_str());
  outputDirectoryName = argv[0];
  alreadySet = true;
  return true;
}

static bool ppConfigfileName(const Option *o, char *argv[])
{
  outputFilenname = argv[0];
  return true;
}

static bool ppGcc(const Option *o, char *argv[])
{
  gccMode = true;
  return true;
}

static void ppFile(char *filename) {
  if (!inputCompiler.empty()) 
    WriteMsg::write( CMSG_COMPILER_IS_SETED, inputCompiler.c_str());

  inputCompiler = filename;
}

const Option OPTIONS_OBJ[] = {
  { false, "-out",          1, "outputdirectory", 0, OT_WS | OT_WC,     ppOutDir,             NULL,    "Place the output files into the given directory"},
  { false, "-filename",     1, "filename",        0, OT_WS | OT_WC,     ppConfigfileName,     NULL,    "Set the name of the generated config file"},
  { false, "-gcc",          0, "",                0, OT_NONE,           ppGcc,                NULL,    "Generate configuration for GCC"},

  COMMON_CL_ARGS
};

  
int main(int argc, char *argv[])
{
  MAIN_BEGIN

    MainInit(argc, argv, "-");

    directoryOfTheBinary = common::getExecutableProgramDir();

    vector<string> cMacros;
    vector<string> cppMacros;

#ifdef __linux
    if (inputCompiler.empty())
      inputCompiler = "clang";

    if (gccMode)
      generateGccIncludeSearchConfig();
    else
      generateClangIncludeSearchConfig();

#elif defined _WIN32
    if (inputCompiler.empty())
      inputCompiler = "cl";

    vector<string> cIncludes;
    vector<string> cppIncludes;

    createClMacrosAndIncludes(false, cMacros, cIncludes);
    createClMacrosAndIncludes(true, cppMacros, cppIncludes);

    generateClIncludeSearchConfig(cIncludes, cppIncludes);
#endif

  MAIN_END
  
  return 0;
}

