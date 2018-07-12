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


#define PROGRAM_NAME "GraphMerge"
#define EXECUTABLE_NAME "GraphMerge"

#include <MainCommon.h>
#include <vector>

#include "messages.h"
#include <graph/inc/graph.h>
#include <graphsupport/inc/MetricSum.h>
#include <graphsupport/inc/Metric.h>
#include <io/inc/CsvIO.h>
#include <common/inc/Stat.h>
#include "common/inc/Arguments.h"
#include "common/inc/FileSup.h"

using namespace std;
using namespace common;
using namespace columbus;
using namespace columbus::graph;
using namespace columbus::graphsupport;

static vector<string> files;
static string out;
static bool saveXml;

static void ppFile(char *filename) {
  files.push_back(filename);
}

static bool ppOut(const Option *o, char *argv[]) {
  out = argv[0];
  return true;
}

static bool ppSaveXML (const common::Option *o, char *argv[]) {
  saveXml = true;
  return true;
}

const Option OPTIONS_OBJ [] = {
  { false,  "-out",         1, "filename",      1, OT_WC,    ppOut,             NULL, "The merged output graph."},
  { false,  "-dumpxml",     0, "",              0, OT_NONE,  ppSaveXML,         NULL, "Dump the graph in xml format."},
  COMMON_CL_ARGS
};

int main(int argc, char** argv) {
  MAIN_BEGIN

    MainInit(argc, argv, "-");

    if (files.empty()) {
      WriteMsg::write(CMSG_NO_INPUT_FILE);
      clError();
    }
    if (out.empty()) {
      WriteMsg::write(CMSG_NO_OUTPUT_FILE);
      clError();
    }

    Graph g;
    WriteMsg::write(CMSG_LOAD_FILE, files[0].c_str());
    g.loadBinary(files[0]);
    for (size_t i = 1; i < files.size(); ++i) {
      WriteMsg::write(CMSG_MERGE_FILE, files[i].c_str());
      g.mergeWithBinary(files[i], Graph::mmUnionAttribute, Graph::csmmUnionNewAttributes, Graph::nmmSummarizeAttributes, Graph::mmUnionAttribute, Graph::csmmUnionNewAttributes, Graph::nmmSummarizeAttributes);
    }
    summarizeWarningMetricsByPriority(g, true); 

    WriteMsg::write(CMSG_SAVE_FILE, out.c_str());
    g.saveBinary(out);
    if (saveXml) {
      g.saveXML(common::pathRemoveExtension(out) + ".xml");
    }
    
  MAIN_END
  
  return 0;
}
