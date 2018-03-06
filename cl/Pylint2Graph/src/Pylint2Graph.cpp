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

#include "../inc/Pylint2Graph.h"
#include "../inc/PylintRulMaker.h"
#include "../inc/messages.h"

#include <common/inc/StringSup.h>
#include <common/inc/WriteMessage.h>
#include <rul/inc/RulHandler.h>
#include <graph/inc/graph.h>
#include <strtable/inc/RefDistributorStrTable.h>
#include <lim/inc/Factory.h>
#include <lim2graph/inc/Lim2GraphConverter.h>
#include <graphsupport/inc/GraphConstants.h>
#include <graphsupport/inc/GraphRangeIndexer.h>
#include <graphsupport/inc/Metric.h>
#include <graphsupport/inc/MetricSum.h>
#include <graphsupport/inc/RulBuilder.h>

#include <fstream>
#include <boost/regex.hpp>

using namespace std;
using namespace common;
using namespace columbus;
using namespace columbus::graph;


struct PylintWarning {
  PylintWarning()
    : path(), lineNum(0), colNum(0), ruleId(), text() {}
  PylintWarning(string path, int lineNum, int colNum, string ruleId, string text)
    : path(path), lineNum(lineNum), colNum(colNum), ruleId(ruleId), text(text) {}
  ~PylintWarning() {}

  string path;
  int lineNum;
  int colNum;
  string ruleId;
  string text;

  bool operator<(const PylintWarning& other) const {
    if (path != other.path)
      return path < other.path;
    else if (lineNum != other.lineNum)
      return lineNum < other.lineNum;
    else if (colNum != other.colNum)
      return colNum < other.colNum;
    else if (ruleId != other.ruleId)
      return ruleId < other.ruleId;
    else if (text != other.text)
      return text < other.text;
    return false;
  }
};


Pylint2Graph::Pylint2Graph(const string& rulFile, const string& rulConfig, ostream& out, const string& changePathFrom /* = "" */, const string& changePathTo /* = "" */) :
  out(out),
  changePathFrom(changePathFrom),
  changePathTo(changePathTo),
  limFact(strTable, "", columbus::lim::asg::limLangOther),
  rulHandler(new columbus::rul::RulHandler(rulFile, rulConfig, "eng", "ISO-8859-1")),
  graphIndexer(graphsupport::GraphRangeIndexer::getGraphRangeIndexerInstance())
{
}

Pylint2Graph::~Pylint2Graph() {
  if (rulHandler)
    delete rulHandler;
}

void Pylint2Graph::buildGraph(const string& limFileName) {
  list<HeaderData*> header;
  WriteMsg::write(CMSG_PYLINT2GRAPH_LOADING_LIM, limFileName.c_str());
  //load lim
  try {
    limFact.load(limFileName, header);
  } catch (const lim::asg::LimException& ex) {
    WriteMsg::write(CMSG_PYLINT2GRAPH_LOAD_LIM_EXCEPTION, limFileName.c_str(), ex.getLocation().c_str(), ex.getMessage().c_str());
    exit(EXIT_FAILURE);
  }
  //load filter
  string filterFileName = common::replaceExtension(limFileName, ".flim");
  if (common::pathFileExists(filterFileName, false)) {
    WriteMsg::write(CMSG_PYLINT2GRAPH_LOADING_LIM_FILTER, filterFileName.c_str());
    if (fileTimeCmp(filterFileName, limFileName) == -1) {
      WriteMsg::write(CMSG_PYLINT2GRAPH_FILTER_FILE_IS_DEPRECATED, filterFileName.c_str());
    } else {
      try {
        limFact.loadFilter(filterFileName);
      } catch (const lim::asg::LimException& ex) {
        WriteMsg::write(CMSG_PYLINT2GRAPH_LOAD_FILTER_EXCEPTION, filterFileName.c_str(), ex.getLocation().c_str(), ex.getMessage().c_str());
        exit(EXIT_FAILURE);
      }
    }
  }

  WriteMsg::write(CMSG_PYLINT2GRAPH_USING_CONFIG, rulHandler->getConfig().c_str());

  lim2graph::convertBaseGraph(limFact, graph, /*edges=*/ true, /*attributes=*/ true, /*components=*/ true, /*variants=*/ false, /*instances=*/ false);
  graphIndexer.turnOn(graph);
}


void Pylint2Graph::convertResults(const string& pylintResultsFile) {
  const boost::regex regexpWarn(":(.*):(\\d+):(\\d+): \\[(\\w+)\\((\\w+[-\\w]*)\\)\\] (.*)");

  set<PylintWarning> warnings;

  ifstream input(pylintResultsFile.c_str());
  if (input.is_open()) {
    string line;

    while (input.good()) {

      getline(input, line);

      if (!line.empty()) {

        if (line.find("*****") == 0) {
          // nothing to do

        } else if (line[0] == ':') {
          boost::smatch match;

          if (boost::regex_search(line, match, regexpWarn)) { // TODO multi line warnings are not handled
            string path = match[1];
            string lineNum = match[2];
            string colNum = match[3];
            string id = match[4];
            string name = match[5];
            string text = match[6];

            common::trim(text);

            int iline = atoi(lineNum.c_str());
            int icol = atoi(colNum.c_str()) + 1;

            string ruleId;

            try {
              ruleId = rulHandler->getRuleIdByOriginalId(name);
            } catch (const rul::RulHandlerException&) {
              WriteMsg::write(CMSG_PYLINT2GRAPH_MISSING_RULE, name.c_str(), path.c_str(), iline, text.c_str());
              continue;
            }

            common::changePath(path, changePathFrom, changePathTo);

            warnings.insert(PylintWarning(path, iline, icol, ruleId, text));

          } else {
            WriteMsg::write(CMSG_PYLINT2GRAPH_REGEXP_ERROR, line.c_str());
          }
        }
      }
    }

    input.close();
  }

  // add sorted warnings
  for (set<PylintWarning>::const_iterator it = warnings.begin(), itEnd = warnings.end(); it != itEnd; ++it) {
    const PylintWarning& warning = *it;
    addWarningToNode(warning.path, warning.lineNum, warning.colNum, warning.lineNum, warning.colNum, warning.ruleId, warning.text);
  }
}

void Pylint2Graph::saveResultGraph(const string& outGraphFile, bool exportRul) {
  if (exportRul) {
    graphsupport::buildRulToGraph(graph, *rulHandler);
  }

  // summarize warnings
  graphsupport::cumSum(graph, graph::Edge::EdgeType(graphsupport::graphconstants::ETYPE_LIM_COMPONENT, graph::Edge::edtDirectional), true);
  graphsupport::cumSum(graph, graph::Edge::EdgeType(graphsupport::graphconstants::ETYPE_LIM_COMPONENTTREE, graph::Edge::edtReverse), false);
  graphsupport::cumSum(graph, graph::Edge::EdgeType(graphsupport::graphconstants::ETYPE_LIM_LOGICALTREE, graph::Edge::edtReverse), false);

  // create group metrics
  columbus::graphsupport::createGroupMetrics(graph, *rulHandler);

  graph.saveBinary(outGraphFile);
}

void Pylint2Graph::addWarningToNode(const string& path, int line, int col, int endline, int endcol, const string& warningID, const string& warningText) {
  if (!rulHandler->getIsEnabled(warningID)) {
    return; // rule is not enabled
  }

  list<Node> nodes;

  graphIndexer.findNodesByRange(graph, path, line, INT_MIN, endline, INT_MAX, nodes);

  int minDist = INT_MAX;
  Node node;
  for (list<Node>::iterator it = nodes.begin(); it != nodes.end(); ++it) {
    vector<graphsupport::Position> positions;
    graphsupport::getPositionAttributes(*it, positions);
    for (vector<graphsupport::Position>::iterator pos = positions.begin(); pos != positions.end(); ++pos) {
      int dist = abs(line - pos->line) + abs(endline - pos->endline);
      if(dist < minDist) {
        node = *it;
        minDist = dist;
      }
    }
  }

  if (node == Graph::invalidNode) { // could not find the node by path, skip this warning
    WriteMsg::write(CMSG_PYLINT2GRAPH_NO_NODE_FOUND_AT_PATH, warningID.c_str(), path.c_str(), line, col, endline, endcol);

  } else {
    // if the found node is attribute, we use that parent
    if (node.getType().getType() == graphsupport::graphconstants::NTYPE_LIM_ATTRIBUTE) {
      Edge::EdgeIterator edgeIt = node.findOutEdges(Edge::EdgeType(graphsupport::graphconstants::ETYPE_LIM_LOGICALTREE, Edge::edtReverse));
      if (edgeIt.hasNext()) {
        node = edgeIt.next().getToNode();
      }
    }

    if (node != Graph::invalidNode) {
      if (graphsupport::addWarningOnce(graph, node, warningID, path, line, col, endline, endcol, warningText)) {
        out << path << "(" << line << "): " << warningID << ": " << warningText << endl;
      } else {
        WriteMsg::write(CMSG_PYLINT2GRAPH_WARNING_ALREADY_ADDED, warningID.c_str(), node.getUID().c_str(), path.c_str(), line, col, endline, endcol, warningText.c_str());
      }
    }
  }
}
