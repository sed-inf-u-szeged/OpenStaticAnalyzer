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

#ifndef _CONFIG_H
#define _CONFIG_H

#define PROGRAM_NAME           "DuplicatedCodeFinder"
#define EXECUTABLE_NAME        "DuplicatedCodeFinder"


#define TOOL_NAME              "Columbus Clone Extractor (v1.1)"

#define DCM_RELAXATIONS        "dcmRelaxations"
#define DCM_MATCH              "dcmMatch"
#define DCM_LOWMEMORY          "dcmLowMemoryMode"
#define DCM_OUT                "dcmOutput"
#define DCM_STDOUT             "dcmStdout"
#define DCM_FUNCTION_BLOCK_ONLY "dcmFunctionBlocksOnly"
#define DCM_MAP_FILE_NAME      "dcmMapFileName"
#define DCM_MAP_SIZE           "dcmMapSize"
#define DCM_ALGORITHM          "dcmAlgorithm"
#define DCM_LINES              "dcmLines"


#define LIM_FILTER_FILE_EXTENSION ".flim"
#define FILTER_FILE_EXTENSION_W L".fcsi"

#include <string>
#include <list>
#include <cstring>

struct Config {

  Config() 
    : minLines    (20)
    , minStatements (8)
    , minAsgNodes (35)
    , minOccur    (2)
    , metrics     (false)
    , lp          (false)
    , inputFile   (false)
    , singleAsgRoot (true)
    , ofc           (false)
    , patternMaxSingleLength(10)
    , patternMinFullLength(100)
    , exportRul(false)
    , statementFilter(true)
    , smallGenealogy(true)
    , maxCCSize(0)
  {
    memset(&stat,0,sizeof(stat));
  }

  unsigned int           minLines;              ///< minimum lines in clone
  unsigned int           minStatements;         ///< minimum number of statements in the clone instance
  unsigned int           minAsgNodes;           ///< minimum asg nodes at clone
  unsigned int           minOccur;              ///< minimum clone occurrence
  std::string            genealogyFilename;     ///< name of the genealogy instance file
  bool                   metrics;               ///< calculate metrics 
  bool                   lp;                    ///< lower path
  bool                   inputFile;
  bool                   singleAsgRoot;
  bool                   ofc;                    ///< only function clones
  unsigned int           patternMaxSingleLength;///< maximal length of a single pattern
  unsigned int           patternMinFullLength;  ///< minimal length of the full repeating pattern series
  std::string            dcFout;
  std::string            fList;                 ///< list of the input files
  std::string            blockPaths;            ///< list of the paths which should be blocked
  std::string            rul_str;               ///< location of the .rul file
  std::string            rulConfig;             ///< rule configuration
  std::string            dcout;                 ///< name of the output file
  std::list<std::string> files;                 ///< list of the input files
  std::list<std::string> bpaths;
  std::string            graphFilename;
  std::string            limFileName;
  bool                   exportRul;
  std::string            systemName;
  std::string            systemVersion;
  std::string            filterfile;

  struct {
    uint64_t      memory_peak;
    uint64_t      asgSerializationTime;
    uint64_t      filterTime;
    uint64_t      cloneFindTime;
    uint64_t      cloneClassFilterTime;
    uint64_t      calculateMetricsTime;
    uint64_t      finalizeTime;
    uint64_t      buildCloneTreeTime;
    uint64_t      evolutionMappingTime;
    
    unsigned int serializedASGLength;
    unsigned int serializedASGLengthFiltered;
    unsigned int numOfFoundsuffixInstances;
    unsigned int numOfpotInstances;
    unsigned int numOfFoundsuffixClass;
    unsigned int numberOfInstancesInTheLastSystem;
    unsigned int numberOfTrivialPairs;
    unsigned int totalASTNodeNumber;
  } stat;

  bool statementFilter;
  bool smallGenealogy;                           ///< keep the string attributes of the last system only in the genealogy output
  std::string            xmlDumpFile;
  int                    maxCCSize;              ///< muber of maximum allowed clone instance in one clone class
};

extern Config config;

#endif
