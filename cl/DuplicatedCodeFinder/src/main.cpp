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

#include "../inc/common.h"
#include "../inc/dcm.h"

#include "common/inc/WriteMessage.h"
#include "../inc/messages.h"

#include "ReleaseVersion.h"
#include "rul/inc/RulHandler.h"
#include "common/inc/Arguments.h"

#include "MainCommon.h"

columbus::rul::RulHandler* rulHandler = NULL;
using namespace std;
using namespace common;
using namespace columbus;
using namespace columbus::dcf;

Config config;


//-------------------------------------------------------
// Callback methods for argument processing

static bool ppList (const Option *o, char *argv[]) {
  config.fList = argv[0];
  return true;
}

static bool ppRul (const Option *o, char *argv[]) {
  config.rul_str = argv[0];
  return true;
}

static bool ppRulConfig (const Option *o, char *argv[]) {
  config.rulConfig = argv[0];
  return true;
}

static bool ppMetrics (const Option *o, char *argv[]) {
  config.metrics = true;
  return true;
}

static bool ppOut (const Option *o, char *argv[]) {
  config.dcout = argv[0];
  return true;
}

static bool ppPathLower (const Option *o, char *argv[]) {
  config.lp = true;
  return true;
}

static bool ppLines (const Option *o, char *argv[]) {
  config.minLines = boost::lexical_cast<unsigned int>(argv[0]);
  return true;
}

static bool ppNodes (const Option *o, char *argv[]) {
  config.minAsgNodes = boost::lexical_cast<unsigned int>(argv[0]);
  return true;
}

static bool ppOccur (const Option *o, char *argv[]) {
  config.minOccur = boost::lexical_cast<unsigned int>(argv[0]);
  return true;
}


#ifdef GENEALOGY
static bool ppGenealogy (const Option *o, char *argv[]) {
  config.genealogyFilename = argv[0];
  return true;
}
#endif

static void ppFile(char *filename) {
  
  config.files.push_back(filename);
}

static bool ppLimFile(const Option *o, char *argv[]) {
  config.limFileName = argv[0];
  return true;
}

static bool ppGraph (const Option *o, char *argv[]) {
  config.graphFilename = argv[0];
  return true;
}

static bool ppPatternFilter (const Option *o, char *argv[]) {
  config.patternMaxSingleLength = boost::lexical_cast<unsigned int>(argv[0]);
  config.patternMinFullLength   = boost::lexical_cast<unsigned int>(argv[1]);
  return true;
}

static bool ppFOut (const Option *o, char *argv[]) {
  config.dcFout = argv[0];
  return true;
}

static bool ppMultipleAsgRoot(const Option *o, char *argv[]) {
  config.singleAsgRoot = false;
  return true;
}

static bool ppExportRul(const Option *o, char *argv[]) {
  config.exportRul = true;
  return true;
}
/*Only function clone*/
static bool ppFc(const Option *o, char *argv[]) {
  config.ofc = true;
  return true;
}


static bool  ppFst (const Option *o, char *argv[]) {
  config.statementFilter = false;
  return true;
}

const common::Option OPTIONS_OBJ [] = {
  CL_LIM
  { false,  "-metrics",       0, "",                      0, OT_WC,    ppMetrics,      NULL,   "Calculate clone metrics."},
  { false,  "-out",           1, "filename",              0, OT_WC,    ppOut,          NULL,   "File into which the list of the clones is written. If it is not specified then the list will be written to the standard output."},
  { false,  "-lowerpath",     0, "",                      0, OT_NONE,  ppPathLower,    NULL,   "Convert all the paths to lower case."},
  { false,  "-minlines",      1, "number",                0, OT_WC,    ppLines,        NULL,   "The minimum number of lines of each duplication. Default value is 10."},
  { false,  "-minnodes",      1, "number",                0, OT_WC,    ppNodes,        NULL,   "The minimum number of ASG nodes of each duplication. Default value is 20."},
  { false,  "-minoccur",      1, "number",                0, OT_WC,    ppOccur,        NULL,   "The minimum number of occurences of each kind of duplication. Default value is 2."},

#ifdef GENEALOGY
  { false,  "-genealogy",      1, "filename",             0, OT_WC,    ppGenealogy,    NULL,    "The geneology while, which contains historical information about the clones."},
#endif

  { false, "-graph",           1, "filename",             0, OT_WC,    ppGraph,        NULL,   "Save structured result of the clones and metrics in binary graph format."},
  { false, "-patternfilterlog",1, "filename",             0, OT_WC,    ppFOut,         NULL,   "Save the source code positions of the filtered source elements to the given file. If it is not set then the list will be written to the standard out."},
  { false, "-patternfilter",   2, "number number",        0, OT_WS,    ppPatternFilter,NULL,   "Enable pattern filter with the given parameters. The first number is the maximum length (default value is 10) of a single pattern "
                                                                                               "and the second number is the minimum length (default value is 100) of the whole repeating patter series to be detected."},
  { false,  "-multipleasgroot",      0, "",               0, OT_WC,    ppMultipleAsgRoot, NULL,"Clone instances can have multiple ASG root."},
  { false,  "-onlyfunctionclone",    0, "",               0, OT_WC,    ppFc,              NULL,"Clones are detected only inside the functions."},
  { false,  "-statementNotReq",      0, "",               0, OT_WC,    ppFst,             NULL,"Not filter clone instance which has not contained statement."},
  CL_RUL_AND_RULCONFIG("DCF.rul")
  CL_EXPORTRUL
  CL_INPUT_LIST
  COMMON_CL_ARGS
};

void initValues() {
  //------------------------ Loading files ---------------------------
  if (config.rul_str.empty()) {
    std::string rulFile;
    rulFile = "DCF.rul";
    config.rul_str = getExecutableProgramDir()+rulFile;
    common::WriteMsg::write(CMSG_RUL_FILE_NOT_SET, config.rul_str.c_str());
  }
  //trying to touch the .rul file
  try {
    if(!common::pathIsAbsolute(config.rul_str.c_str())) {
      config.rul_str = getExecutableProgramDir() + config.rul_str;
    }
    // create rule handler
    if(config.rulConfig.empty()) {
#ifdef SCHEMA_JAVA
      config.rulConfig = "java";
#elif defined(SCHEMA_PYTHON)
	  config.rulConfig = "python";
#endif
    }

    rulHandler=new rul::RulHandler(config.rul_str, config.rulConfig, "eng");
  } catch(columbus::Exception& e) {
    common::WriteMsg::write(CMSG_SIMPLE_STRING_TRANSMIT_ERR,e.toString().c_str());
    
    exit(-1);
  }
  common::WriteMsg::write(CMSG_RUL_FILE_FOUND, config.rul_str.c_str());

  loadStringListFromFile(config.fList, config.files);
  
  if (!config.blockPaths.empty()) {
    std::ifstream ifs(config.blockPaths.c_str());
    string line;
    do {
      getline(ifs, line);
      if (!line.empty()) {
        if (config.lp)
          config.bpaths.push_back(boost::to_lower_copy(line));
        else
          config.bpaths.push_back(line);
      }
      if (ifs.eof()) break;
    } while (true);
  }

  if (config.files.size() == 0) {
    common::WriteMsg::write(CMSG_NO_INPUT_FILES);
    Help();
    exit(common::retBadArgError);
  }

  if (config.limFileName.empty()) {
    common::WriteMsg::write(CMSG_NO_INPUT_LIM_FILE);
    Help();
    exit(common::retBadArgError);
  }
 
  common::WriteMsg::write(CMSG_THE_LIM_INPUT_FILE,config.limFileName.c_str());
  common::WriteMsg::write(CMSG_LINE_INFO_CASE , (config.lp ? CMSG_LINE_INFO_CASE_LOWERED : CMSG_LINE_INFO_CASE_DEFAULT));
  common::WriteMsg::write(CMSG_MINIMUM_NUMBER_OF_LINES,config.minLines);
  common::WriteMsg::write(CMSG_MAXIMUM_PATTERN_SIZE,config.patternMaxSingleLength);
  common::WriteMsg::write(CMSG_MINIMUM_PATTERN_FULL_LENGTH, config.patternMinFullLength);
}


static inline void setStartTime(uint64_t *time) {
  timestat usedtime= getProcessUsedTime();
  *time= usedtime.user + usedtime.system;
}

static inline void setElapsedTime(uint64_t *time) {
  timestat usedtime= getProcessUsedTime();
  *time= usedtime.user + usedtime.system - *time;
}

int main(int argc, char* argv[]){
  int exit_code = EXIT_SUCCESS;
  uint64_t time = 0;
  WriteMsg::setAutomaticFlush(true);
  MAIN_BEGIN

  MainInit(argc, argv,"-");
  
  if (config.files.empty() && config.fList.empty()) {
    Help();
    exit(common::retBadArgError);
  }
   
  setStartTime(&time);
  initValues();
  
  /**
  * Checking whether config file exists
  * Just in order to emit a warning
  **/
  common::WriteMsg::write(CMSG_DETECTING_CODE_DUPLICATIONS );

  int maxCCSize = 0;
  if (!config.safemode.empty()) {
    maxCCSize = atoi(config.safemode.c_str()); 
  }

  DuplicatedCodeMiner dcm(config, rulHandler);
  dcm.setStatementFilter(config.statementFilter);
  ofstream* fout = NULL;

#ifdef GENEALOGY
  dcm.setDumpgraphml( config.graphml);
#endif

  if(config.dcFout.empty()) {
    common::WriteMsg::write(CMSG_FILTER_RESULT_REDIRECTED_TO_STANDARD_OUT);
    dcm.setFilterOut(cout);

  } else {
    fout = new ofstream(config.dcFout.c_str());
    if(!fout->fail()) {
      common::WriteMsg::write(CMSG_FILTER_RESULT_REDIRECTED_INTO_FILE, config.dcFout.c_str());
      dcm.setFilterOut(*fout);
    } else {
      common::WriteMsg::write(CMSG_FAILED_OPEN_FILE, config.dcFout.c_str());
    }
  }

  //the main detecting clones
  exit_code = dcm.dcminer(maxCCSize,config.backup);


  if (exit_code == EXIT_SUCCESS) {

    if(!config.dcout.empty()) {
      common::WriteMsg::write(CMSG_DUMPING_OUTPUT_TO_FILE, config.dcout.c_str());
      ofstream out(config.dcout.c_str());
      dcm.dumpLastSystem(out);
    }
    /**
    * Eventually to the standard output as well
    */
    if(config.dcout.empty()) {
      common::WriteMsg::write(CMSG_DUMPING_OUTPUT_TO_STANDARD_OUTPUT);
      dcm.dumpLastSystem(cout);
    }


    if(!config.graphFilename.empty()) {
      dcm.exportGraph(config.graphFilename);
    }
    common::WriteMsg::write(CMSG_DONE_N);
   
    dcm.saveGenealogy();

  }

  delete rulHandler;

  if(fout != NULL) {
    fout->flush();
    fout->close();
    delete fout;
  }
  
  setElapsedTime(&time);

  WriteMsg::write(CMSG_STATISTICS);
  WriteMsg::write(CMSG_DETECTING_TIME, time);
  WriteMsg::write(CMSG_PEAK_MEMORY_USAGE, config.stat.memory_peak / (1024 * 1024));


  MAIN_END
  return exit_code; 
}
