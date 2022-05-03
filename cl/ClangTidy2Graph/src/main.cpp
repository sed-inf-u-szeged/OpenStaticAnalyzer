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

#define PROGRAM_NAME "ClangTidy2Graph"
#define EXECUTABLE_NAME "ClangTidy2Graph"

#include <cstdlib>
#include <MainCommon.h>
#include <common/inc/Stat.h>
#include <common/inc/FileSup.h>
#include <io/inc/CsvIO.h>
#include <rul/inc/RulHandler.h>

#include "../inc/ResultConverter.h"
#include "../inc/messages.h"

using namespace std;
using namespace common;
using namespace columbus;
using namespace columbus::clangtidy2graph;

static string rulesListFileName;
static string outputFileName;
static string limFileName;
static string graphFileName;
static string rul_s = "ClangTidy.rul";
static string rulConfig = "Default";
static bool exportRul = false;
static string fList;
static list<string> listOfFile;
static size_t peakMemory = 0;

static bool ppMakeRul(const Option *o, char *argv[]) {
  rulesListFileName = argv[0];
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
  { false,  "-makerul",         1, "rules.csv",         0,  OT_WS,  ppMakeRul,    NULL,   "Making rul file from the rules.csv file."},
  { false,  "-graph",           1, "filename",          0,  OT_WC,  ppGraph,      NULL,   "Save binary graph output."},
  { false,  "-out",             1, "filename",          0,  OT_WC,  ppOut,        NULL,   "Specify the name of the output file. The list of rule violations will be dumped in it.\n"},
  CL_INPUT_LIST
  CL_LIM
  CL_RUL_AND_RULCONFIG("ClangTidy.rul")
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

  if( !rulesListFileName.empty() ){
    // Process the rules.csv and generate the rul.
    io::CsvIO csv(rulesListFileName, io::IOBase::omRead); //Open CSV
    csv.setSeparator(';');
    
    rul::RulHandler rulHandler(rulConfig, "eng");
    rulHandler.setToolDescription("ID", "ClangTidy");
    
    list<string> line;
    int num_of_lines = 0;

    while(csv.readLine(line)){
      num_of_lines++;
      if(num_of_lines > 1){
        //Reading csv
        string priority = line.back();
        line.pop_back(); //Priority
        string check_id = line.back();
        line.pop_back(); //ID
        string display_name = line.back();
        line.pop_back(); //New name
        line.pop_back(); //Old name
        string group = line.back();
        line.pop_back(); //Group
        string full_name = line.back();
      
      
      // Check does group exist
      if(!rulHandler.getIsDefined(group)){
        // insert new group metric
        rulHandler.defineMetric(group);
        rulHandler.createConfiguration(group, rulHandler.getConfig());
        rulHandler.createLanguage(group, "eng");
        rulHandler.setGroupType(group, "summarized");
        rulHandler.setDisplayName(group, group);        
        rulHandler.setHasWarningText(group, true);
        rulHandler.setIsEnabled(group, true);
        rulHandler.setIsVisible(group, true);
        rulHandler.setHelpText(group,"");
        
      }
      
      //insert new check metric
      rulHandler.defineMetric(check_id);
      rulHandler.createConfiguration(check_id, rulHandler.getConfig());
      rulHandler.setIsEnabled(check_id, true);
      rulHandler.createLanguage(check_id, "eng");
      rulHandler.setHasWarningText(check_id, true);
      rulHandler.setGroupType(check_id, "false");
      rulHandler.addMetricGroupMembers(check_id, group);
      rulHandler.setSettingValue(check_id, "Priority", priority, true);
      rulHandler.setDisplayName(check_id, display_name);
      rulHandler.setOriginalId(check_id, full_name);
        
      }
      line.erase(line.begin(), line.end());
      
    }
    
    csv.close();
    rulHandler.saveRul(rul_s);
    
  }else {

    // TODO Process the xml outputs of the ClangTidy
    
    // ...
    
    loadStringListFromFile(fList, listOfFile);
    // Missing input file.
    if (listOfFile.empty()) {
      WriteMsg::write(CMSG_NO_INPUT_FILE);
      clError();
    }
    // Missing output filename.
    if (graphFileName.empty()) {
      WriteMsg::write(CMSG_NO_OUTPUT_FILE);
      clError();
    }
    ResultConverter converter(limFileName, outputFileName, rul_s, rulConfig, exportRul, "", "");
    updateMemStat(&peakMemory);
    for(list<string>::iterator file = listOfFile.begin(); file != listOfFile.end(); ++file){
      string ctFilePath = *file + ".ct.err";
      if(pathFileExists(ctFilePath, false)){
        WriteMsg::write(WriteMsg::mlNormal, "Loading warnings from file: %s\n", ctFilePath.c_str());
        converter.process(ctFilePath);
      }else{
        // If a compilation unit does not contain a warning, the ct.err file will NOT be generated either
        WriteMsg::write(WriteMsg::mlNormal, "No warnings for file: %s\n", (*file).c_str());
      }
    }
    
    updateMemStat(&peakMemory);
    converter.aggregateWarnings();
    converter.saveResultGraph(graphFileName, /*xml_dump=*/false);

    // ...

    updateMemStat(&peakMemory);
  }

  MAIN_END
  
  return ret;
}
