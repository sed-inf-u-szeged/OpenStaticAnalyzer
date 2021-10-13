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

#include <map>
#include <set>
#include <fstream>
#include <iostream>
#include <algorithm>
#include <limits.h>
#include "MetricTree.h"
#include <common/inc/StringSup.h>
#include <common/inc/WriteMessage.h>
#include <graphsupport/inc/Metric.h>
#include <graphsupport/inc/GraphConstants.h>
#include <common/inc/FileSup.h>
#include <lim2graph/inc/Lim2GraphConverter.h>
#include <strtable/inc/RefDistributorStrTable.h>
#include <lim/inc/Factory.h>
#include <graphsupport/inc/Metric.h>
#include "messages.h"

using namespace common;
using namespace std;
using namespace columbus;
using namespace columbus::graph;

extern bool print_debug;


MetricTree::MetricTree(std::string& fileName, std::string& rul, std::string& rulConfig, const std::map<string, string>& levelMap, columbus::graph::Graph& graph, columbus::graphsupport::GraphRangeIndexer& graphIndexer)
  : fileName(fileName), 
    xRulhandler(NULL),
    levelMap(levelMap), 
    graph(graph), 
    graphIndexer(graphIndexer)
{
  std::string iniFileName = ((common::pathFindFileName(rul) == rul) ? "." + std::string(DIRDIVSTRING) : "") + rul;
  xRulhandler = new columbus::rul::RulHandler(iniFileName, rulConfig, "eng");
  this->graphIndexer.turnOn(this->graph);
}


MetricTree::~MetricTree() {
}

void MetricTree::buildtree() {
  columbus::RefDistributorStrTable strTable;
  columbus::lim::asg::Factory limFact(strTable, "", columbus::lim::asg::limLangOther);
  std::list<HeaderData*> header;
  WriteMsg::write(CMSG_PMD2GRAPH_LOADING_LIM, fileName.c_str());
  try {
    limFact.load(fileName, header);
  } catch (const lim::asg::LimException& ex) {
    WriteMsg::write(CMSG_PMD2GRAPH_LOAD_LIM_EXCEPTION, fileName.c_str(), ex.getLocation().c_str(), ex.getMessage().c_str());
    exit(EXIT_FAILURE);
  }
  string filter = common::replaceExtension(fileName, ".flim");
  if (common::pathFileExists(filter, false)) {
    WriteMsg::write(CMSG_PMD2GRAPH_LOADING_LIM_FILTER, filter.c_str());

    if (fileTimeCmp(filter, fileName) == -1) {
      WriteMsg::write(CMSG_PMD2GRAPH_FILTER_FILE_IS_DEPRECATED, filter.c_str());
    } else {
      try {
        limFact.loadFilter(filter);
      } catch (const lim::asg::LimException& ex) {
        WriteMsg::write(CMSG_PMD2GRAPH_LOAD_FILTER_EXCEPTION, filter.c_str(), ex.getLocation().c_str(), ex.getMessage().c_str());
        exit(EXIT_FAILURE);
      }
    }
  }
  lim2graph::convertBaseGraph(limFact, graph, /*edges=*/ true, /*attributes=*/ true, /*components=*/ true, /*variants=*/ false, /*instances=*/ false);
}


void MetricTree::addWarningToNode(const string& path, int line, int col, int endline, int endcol, const string& groupID, const string& warningID, const string& warningText, FILE *f) {
  if (!xRulhandler->getIsEnabled(warningID)) {
    return; // rule is not enabled
  }

  string lower_path = path;
  LowerDriveLetterOnWindows(lower_path);
  Node node;
  list<Node> nodes;
  graphIndexer.findNodesByRange(graph, path, line, INT_MIN, endline, INT_MAX, nodes);
  int max_line = INT_MIN, min_endline = INT_MAX;
  // cut wrong nodes and find deeper node
  for(list<Node>::iterator it = nodes.begin(); it != nodes.end(); it++) {
    vector<graphsupport::Position> positions;
    graphsupport::getPositionAttributes(*it, positions);
    for(vector<graphsupport::Position>::iterator pit = positions.begin(); pit != positions.end(); ++pit) {
      string act_lower_path = pit->path;
      LowerDriveLetterOnWindows(act_lower_path);
      if( lower_path == act_lower_path && (line >= pit->line) && (endline <= pit->endline) 
        && !( ((line == pit->line) && (col < pit->col)) || ((endline == pit->endline) && (endcol > pit->endcol))))
      {
        if( (max_line < pit->line) && (min_endline > pit->endline))
        {
          max_line = pit->line;
          min_endline = pit->endline;
          node = *it;
          break;
        }
      }
    }
  }

  if (node == Graph::invalidNode) {// could not find the node by path, skip this warning
    WriteMsg::write(CMSG_PMD2GRAPH_NO_NODE_FOUND_AT_PATH, warningID.c_str(), path.c_str(), line, col, endline, endcol);
    return;
  }

  // if the found node is attribute, we use that parent
  if(!(node == Graph::invalidNode)) {
    if(node.getType().getType() == graphsupport::graphconstants::NTYPE_LIM_ATTRIBUTE) {
      Edge::EdgeIterator edgeIt = node.findOutEdges(Edge::EdgeType(graphsupport::graphconstants::ETYPE_LIM_LOGICALTREE, Edge::edtReverse));
      if(edgeIt.hasNext()) {
        node = edgeIt.next().getToNode();
      }
    }
  }
  
  if(node != Graph::invalidNode) {
    if (graphsupport::addWarningOnce(graph, node, warningID, path, line, col, endline, endcol, warningText, &warningCache)) {
      WriteMsg::writeWarningMessage(f, CMSG_PMD2GRAPH_ADDED_WARNING, path.c_str(), line, warningID.c_str(), warningText.c_str());
    } else {
      WriteMsg::write(CMSG_PMD2GRAPH_WARNING_ALREADY_ADDED, warningID.c_str(), node.getUID().c_str(), path.c_str(), line, col, endline, endcol, warningText.c_str());
    }
  }
}
