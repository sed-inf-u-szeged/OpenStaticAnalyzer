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

#define PROGRAM_NAME "LIM2Metrics"
#define EXECUTABLE_NAME PROGRAM_NAME


//
// INCLUDES
//

#include <iostream>
#include "messages.h"
#include "MainCommon.h"
#include "common/inc/FileSup.h"
#include "common/inc/WriteMessage.h"
#include "common/inc/Arguments.h"
#include "common/inc/Stat.h"
#include "csi/inc/csi.h"
#include "lim2graph/inc/Lim2GraphConverter.h"
#include "limmetrics/inc/LimMetrics.h"
#include "graphsupport/inc/CsvExporter.h"
#include "graphsupport/inc/RulBuilder.h"


//
// USINGS
//

using namespace std;
using namespace columbus;
using namespace common;


//
// PARAMETERS AND DEFAULTS
//

static string csvFile;
static string graphFile;
static string rulFile = "MET.rul";
static string rulConfig;
static bool pathLower = false;
static bool exportRul = false;
static char csvSeparator = ',';
static list<string> inputFiles;

static bool ppGraph( const common::Option *o, char *argv[] ) {
  graphFile = argv[0];
  return true;
}

static bool ppCsv( const common::Option *o, char *argv[] ) {
  csvFile = argv[0];
  return true;
}

static bool ppPathLower( const common::Option *o, char *argv[] ) {
  pathLower = true;
  return true;
}

static bool ppExportRul( const Option *o, char *argv[] ) {
  exportRul = true;
  return true;
}

static bool ppRul( const common::Option *o, char *argv[] ) {
  rulFile = argv[0];
  return true;
}

static bool ppRulConfig( const common::Option *o, char *argv[] ) {
  rulConfig = argv[0];
  return true;
}

static void ppFile( char *filename ) {
  inputFiles.push_back( filename );
}

static bool ppCsvSeparator( const common::Option *o, char *argv[] ) {
  if ( strcmp( argv[0], "\\t" ) == 0 ) {
    csvSeparator = '\t';
  } else if ( argv[0] != 0 ) {
    csvSeparator = argv[0][0];
  }
  return true;
}


const common::Option OPTIONS_OBJ [] = {
  { false,  "-out",                 1, "filename" ,       0, common::OT_WC,             ppGraph,              NULL,       "Save binary graph output to the given file"},
  { false,  "-graph",               1, "filename" ,       0, common::OT_WC,             ppGraph,              NULL,       "Save binary graph output to the given file"},
  { false,  "-csv",                 1, "filename",        0, common::OT_WC,             ppCsv,                NULL,       "Create csv output file"},
  CL_CSVSEPARATOR
  { false,  "-pathlower",           0, "",                0, common::OT_NONE,           ppPathLower,          NULL,       "Paths are converted to lower case for writting out"},
  CL_RUL_AND_RULCONFIG("MET.rul")
  CL_EXPORTRUL
  COMMON_CL_ARGS
};


void loadFilter(lim::asg::Factory& fact, const string& file) {
  string flt = common::pathRemoveExtension(file) + ".flim";
  if (common::fileTimeCmp(flt, file) == -1) {
    common::WriteMsg::write(CMSG_LIM2METRICS_FLIM_OLDER_THAN_LIM, flt.c_str());
    return;
  }

  try {
    fact.loadFilter(flt);
  } catch (IOException e) {
    common::WriteMsg::write(CMSG_LIM2METRICS_FILTER_NOT_LOADED, flt.c_str());
    return;
  }
}

int main(int argc, char *argv[]) {

  int exit_code = 0;

  MAIN_BEGIN

    //
    // INIT
    //

    MainInit( argc, argv, "-" );

    if ( inputFiles.size() != 1 ) {
      clError();
    }

    //
    // LOAD LIM
    //

    common::WriteMsg::write( CMSG_LIM2METRICS_DEBUG_LIM_LOAD );

    RefDistributorStrTable limStrTable;
    lim::asg::Factory limFact( limStrTable, "", lim::asg::limLangOther );
    lim::asg::OverrideRelations overrides( limFact );

    std::list<HeaderData*> header;
    PropertyData prop;
    header.push_back( &prop );
    header.push_back( &overrides );
    limFact.load( inputFiles.begin()->c_str(), header );

    //
    // LOAD FILTER
    //

    common::WriteMsg::write( CMSG_LIM2METRICS_DEBUG_FILTER_LOAD );

    limFact.initializeFilter();
    loadFilter(limFact, inputFiles.begin()->c_str());

    //
    // CONVERT LIM TO GRAPH
    //

    common::WriteMsg::write( CMSG_LIM2METRICS_DEBUG_GRAPH_CONVERT );

    graph::Graph limGraph;
    lim2graph::convertBaseGraph( limFact, limGraph, true, true, true, true, false );

    //
    // LOAD RUL
    //

    common::WriteMsg::write( CMSG_LIM2METRICS_DEBUG_RUL_LOAD );

    if ( rulConfig == "" ) {
      switch( limFact.getLanguage() ) {
        case lim::asg::limLangC :          rulConfig = "c"; break;
        case lim::asg::limLangCpp :        rulConfig = "cpp"; break;
        case lim::asg::limLangJava :       rulConfig = "java"; break;
        case lim::asg::limLangPython :     rulConfig = "python"; break;
        case lim::asg::limLangCsharp:      rulConfig = "csharp"; break;
        case lim::asg::limLangJavaScript:  rulConfig = "javascript"; break;
        default :                       rulConfig = "Default"; break;
      }
    }

    rul::RulHandler rul( common::indep_fullpath( rulFile ), rulConfig, "eng" );

    //
    // COMPILE SHARED CONTAINERS
    //
    // NEWSHARED
    // If the computation of a metric

    lim::metrics::SharedContainers shared;
    lim::metrics::InheritanceHelper inheritance( limFact.getReverseEdges() );
    shared.overrides = &overrides;
    shared.factory = &limFact;
    shared.inheritance = &inheritance;

    lim::metrics::LCOMMapType LCOMMap;
    shared.LCOMMap = nullptr;

    //
    // RUN VISITOR
    //

    common::WriteMsg::write( CMSG_LIM2METRICS_DEBUG_VISITOR_RUN );
    lim::metrics::LimMetricsVisitor visitor( limFact, limGraph, rul, shared);
    visitor.run();
    
    //
    // EXPORT RESULTS
    //

    common::WriteMsg::write( CMSG_LIM2METRICS_DEBUG_EXPORT_RESULTS );
    if ( ! csvFile.empty() ) {
      cout << "CSV export to " << csvFile << endl;
      graphsupport::exportReadableMetricsCSV( limGraph, csvFile, csvSeparator );
    }
    
    if ( ! graphFile.empty() ) {
      cout << "Saving graph to " << graphFile << endl;
      if ( exportRul ) {
        cout << "Exporting rul" << endl;
        graphsupport::buildRulToGraph( limGraph, rul );
      }
      limGraph.saveBinary( graphFile );
    }

  MAIN_END

  return exit_code;
}
