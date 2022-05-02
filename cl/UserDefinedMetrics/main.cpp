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

//
// DEFINES
//

#define PROGRAM_NAME "UserDefinedMetrics"
#define EXECUTABLE_NAME PROGRAM_NAME

//
// INCLUDES
//

#include "MainCommon.h"
#include "common/inc/FileSup.h"
#include "common/inc/Arguments.h"
#include "common/inc/Stat.h"
#include "graphsupport/inc/RulBuilder.h"
#include "inc/UdmHelpers.h"

//
// USINGS
//

using namespace std;
using namespace columbus;
using namespace common;

//
// PARAMETERS AND DEFAULTS
//

static string graphFile;
static string rulFile = "UDM.rul";
static string rulConfig = "Default";
static list<string> inputFiles;
bool warning = false;


static bool ppGraph( const Option *o, char *argv[] ) {
  graphFile = argv[0];
  return true;
}

static bool ppRul( const Option *o, char *argv[] ) {
  rulFile = argv[0];
  return true;
}

static bool ppRulConfig( const Option *o, char *argv[] ) {
  rulConfig = argv[0];
  return true;
}

static void ppFile( char *filename ) {
  inputFiles.push_back( filename );
}

const Option OPTIONS_OBJ [] = {
  { false,  "-out",                 1, "filename" ,       0, common::OT_WC,             ppGraph,              NULL,       "Save binary graph output to the given file" },
  { false,  "-graph",               1, "filename" ,       0, common::OT_WC,             ppGraph,              NULL,       "Save binary graph output to the given file" },
  CL_RUL_AND_RULCONFIG("UDM.rul")
  COMMON_CL_ARGS
};

static inline void setStartTime(unsigned long long *time) {
    timestat usedtime = getProcessUsedTime();
    *time = usedtime.user + usedtime.system;
}

static inline void setElapsedTime(unsigned long long *time) {
    timestat usedtime = getProcessUsedTime();
    *time = usedtime.user + usedtime.system - *time;
}

static inline void updateMemStat(size_t *max_mem) {
    memstat ms = getProcessUsedMemSize();
    if (*max_mem < ms.size) {
        *max_mem = ms.size;
    }
}

int main(int argc, char *argv[]) {

  int exit_code = 0;
  unsigned long long totaltime = 0;
  unsigned long long calculatingtime = 0;
  unsigned long long exporttime = 0;
  unsigned long long buildingtime = 0;
  unsigned long long checkingtime = 0;
  unsigned long long readingtime = 0;
  size_t mem = 0;

  MAIN_BEGIN

  std::cout << "----\n";
  for (int i = 0; i < argc; ++i) {
    std::cout << argv[i] << '\n';
  }
  std::cout << "----\n";

    //
    //  INIT
    //

    MainInit(argc, argv, "-");
    if (inputFiles.size() != 1) {
      clError();
    }

    setStartTime(&totaltime);
    updateMemStat(&mem);

    //
    //  LOADING THE "CalculatedFor" ATTRIBUTES FROM GRAPH'S "RulMetric" TYPE NODES
    //

    setStartTime(&readingtime);

    graph::Graph graph;
    graph.loadBinary(*(inputFiles.begin()));
    map<string, set<string>> graph_calculatedFors;
    loadGraphcCalcFor(graph, graph_calculatedFors);

    updateMemStat(&mem);

    //
    //  LOADING THE USER'S METRIC DEFINITIONS
    //

    map<string, UdmNode> udm_nodes;
    rul::RulHandler rulHand(indep_fullpath(rulFile), rulConfig, "eng");
    loadUdmMetrics(udm_nodes, rulHand, graph_calculatedFors);

    setElapsedTime(&readingtime);
    updateMemStat(&mem);

    //
    //  CHECKING THE FORMULAS AND THE DEPENDENCIES BETWEEN THEM
    //

    setStartTime(&checkingtime);

    checkCalcFors(udm_nodes, graph_calculatedFors);

    setElapsedTime(&checkingtime);
    updateMemStat(&mem);

    //
    //  BUILDING THE DEPENDENCY VECTOR
    //

    setStartTime(&buildingtime);

    vector<vector<string>> dependencyOrder;
    buildDependency(dependencyOrder, udm_nodes);

    setElapsedTime(&buildingtime);
    updateMemStat(&mem);

    //
    //  CALCULATING THE FORMULAS BY THE DEPENDENCY VECTOR
    //

    setStartTime(&calculatingtime);

    evaluateGraph(udm_nodes, dependencyOrder, graph);
    

    setElapsedTime(&calculatingtime);
    updateMemStat(&mem);

    //
    //  ADDING THE UDM.rul CONTENT TO THE GRAPH
    //

    setStartTime(&exporttime);

    graphsupport::buildRulToGraph(graph, rulHand);

    updateMemStat(&mem);

    //
    //  CREATING HEADER INFO AND
    //  EXPORTING AND SAVING THE NEW GRAPH
    //

    graph.saveBinary(graphFile);

    setElapsedTime(&exporttime); 

    //
    //  STATS
    //

    setElapsedTime( &totaltime );
    updateMemStat(&mem);

    WriteMsg::write(CMSG_UDM_STATISTICS);
    WriteMsg::write(CMSG_UDM_READING_TIME, ((float)readingtime)/100);
    WriteMsg::write(CMSG_UDM_BUILDING_TIME, ((float)buildingtime) / 100);
    WriteMsg::write(CMSG_UDM_CALCULATION_TIME, ((float)calculatingtime)/100);
    WriteMsg::write(CMSG_UDM_EXPORT_TIME, ((float)exporttime)/100);
    WriteMsg::write(CMSG_UDM_TOTAL_TIME, ((float)totaltime)/100);
    WriteMsg::write(CMSG_UDM_PEAK_MEMORY, ((float)mem)/1048576);
    
  MAIN_END
  return exit_code;
}
