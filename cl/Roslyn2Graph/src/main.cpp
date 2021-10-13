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

#define PROGRAM_NAME "Roslyn2Graph"
#define EXECUTABLE_NAME "Roslyn2Graph"

#include <cstdlib>
#include <xercesc/sax2/SAX2XMLReader.hpp>
#include <xercesc/sax2/XMLReaderFactory.hpp>
#include <xercesc/sax2/DefaultHandler.hpp>
#include <xercesc/sax2/Attributes.hpp>
#include <xercesc/util/XMLString.hpp>
#include <MainCommon.h>
#include <common/inc/Stat.h>
#include <io/inc/CsvIO.h>
#include <boost/filesystem.hpp>

#include "../inc/ResultConverter.h"
#include "../inc/messages.h"

XERCES_CPP_NAMESPACE_USE

using namespace std;
using namespace common;
using namespace columbus;
using namespace columbus::roslyn2graph;

static string graphFileName;
static string outputFileName;
static string limFileName;
static string inputDirectory;
static string fList;
static list<string> listOfFiles;

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

static void ppFile(char *filename) {
  inputDirectory = filename;
}

const common::Option OPTIONS_OBJ [] = {
  { false,  "-graph",           1, "filename",          0,  OT_WC,  ppGraph,      NULL,   "Save binary graph output."},
  { false,  "-out",             1, "filename",          0,  OT_WC,  ppOut,        NULL,   "Specify the name of the output file. The list of rule violations will be dumped in it.\n"},
  CL_LIM
  COMMON_CL_ARGS
};

static void getFileNames() {
  namespace fs = boost::filesystem;
  fs::path someDir(inputDirectory);
  fs::directory_iterator end_iter;

  if (fs::exists(someDir) && fs::is_directory(someDir))
  {
    for (fs::directory_iterator dir_iter(someDir); dir_iter != end_iter; ++dir_iter)
    {
      if (dir_iter->path().extension().generic_string() == ".xml" &&  fs::is_regular_file(dir_iter->status()))
      {
        listOfFiles.push_back(dir_iter->path().generic_string());
        updateMemoryStat();
      }
    }
  }
}

int main(int argc, char* argv[]) {
  int ret = EXIT_SUCCESS;
  MAIN_BEGIN

  MainInit(argc, argv, "-");

  // init xerces
  try {
    XMLPlatformUtils::Initialize();
  }
  catch (const XMLException& toCatch)
  {
    char* message = XMLString::transcode(toCatch.getMessage());
    string exceptionMessage = "Error during XERCES initialization! ";
    exceptionMessage += message;
    XMLString::release(&message);
    throw Exception("Initialize()", exceptionMessage);
  }


  if (inputDirectory.empty()) {
    WriteMsg::write(CMSG_NO_INPUT_DIR);
    clError();
  }

  getFileNames();

  if (limFileName.empty()) {
    WriteMsg::write(CMSG_NO_LIM_FILE);
    clError();
  }
  if (graphFileName.empty()) {
    WriteMsg::write(CMSG_NO_OUTPUT_FILE);
    clError();
  }

  // Converting roslyn output
  {
    ResultConverter converter(limFileName, outputFileName, "", "");
    for(auto & file : listOfFiles){
      if(pathFileExists(file, false)) {
        converter.process(file);
      }
      else {
        WriteMsg::write(CMSG_FILE_NOT_EXISTS, file.c_str());
        ret = EXIT_FAILURE;
      }
    }
    converter.aggregateWarnings();
    converter.saveResultGraph(graphFileName, false);
  }

  WriteMsg::write(CMSG_FINISHED);


  try {
    XMLPlatformUtils::Terminate();
  }
  catch (const XMLException& toCatch)
  {
    char* message = XMLString::transcode(toCatch.getMessage());
    string exceptionMessage = message;
    XMLString::release(&message);
    throw Exception("Terminate()", exceptionMessage);
  }


  MAIN_END

  return ret;
}
