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

#include <lim2graph/inc/Lim2GraphConverter.h>
#include <graphsupport/inc/RulBuilder.h>
#include <graphsupport/inc/GraphConstants.h>
#include <graphsupport/inc/MetricSum.h>
#include <common/inc/StringSup.h>
#include "../inc/ResultConverter.h"
#include "../inc/messages.h"
#include "../inc/defines.h"

using namespace std;
using namespace common;
using namespace columbus;
using namespace columbus::graph;
using namespace columbus::eslint2graph;


ResultConverter::ResultConverter(const std::string& limFileName, const std::string& txtOutFile, const std::string& rulFileName, const std::string& rulConfig, const bool exportRul, const std::string& changePathFrom, const std::string& changePathTo):
    DefaultHandler(),
    parser(),
    rulHandler(rulFileName, rulConfig, "eng"),
    limStrTable(),
    limFactory(limStrTable, "", columbus::lim::asg::limLangOther),
    graphIndexer(graphsupport::GraphRangeIndexer::getGraphRangeIndexerInstance()),
    changePathFrom(changePathFrom),
    changePathTo(changePathTo),
    txtOutFile(txtOutFile)
{
  // Loading lim
  list<HeaderData*> headerDataList;
  limFactory.load(limFileName, headerDataList);
  loadFilter(limFactory, limFileName, ".flim");
  lim2graph::convertBaseGraph(limFactory, graph, true, true, true, true, false);
  graphIndexer.turnOn(graph);
  if(exportRul) {
    graphsupport::buildRulToGraph(graph, rulHandler);
  }

  // Xml attribute names
  ruleIdXMLCh = XMLString::transcode(_RULE_ID);  
  locationFileXMLCh = XMLString::transcode(_FILE_NAME);
  locationLineXMLCh = XMLString::transcode(_WARNING_LINE);
  locationColumnXMLCh = XMLString::transcode(_WARNING_COLUMN);
  warningMsgXMLCh = XMLString::transcode(_WARNING_MSG);
  nodeTypeXMLCh = XMLString::transcode(_WARNING_NODETYPE);

  // Creating empty text output file
  if(!txtOutFile.empty()) {
    std::ofstream out(txtOutFile.c_str());
    if(!out) {
      WriteMsg::write(CMSG_FAILED_TO_OPEN_FILE, txtOutFile.c_str());
    } else {
      out << "";
    }
  }
}

ResultConverter::~ResultConverter(){
  XMLString::release(&ruleIdXMLCh);
  XMLString::release(&warningMsgXMLCh);
  XMLString::release(&locationFileXMLCh);
  XMLString::release(&locationLineXMLCh);
  XMLString::release(&nodeTypeXMLCh);
}

void ResultConverter::process(const std::string& resultFileName){
  parser.parseXML(resultFileName, this);
}

void ResultConverter::saveResultGraph(const std::string& graphOutputFilename, bool createXMLdump) {
  graph.saveBinary(graphOutputFilename);
  if (createXMLdump) {
    graph.saveXML(common::pathRemoveExtension(graphOutputFilename) + ".xml");
  }
}

void ResultConverter::addWarning(Location location){
  string ruleId;
  try{
    ruleId = rulHandler.getRuleIdByOriginalId(id);
  }catch(rul::RulHandlerException &){
    WriteMsg::write(CMSG_ORIGINAL_RULE_NOT_EXIST, id.c_str());
    return;
  }
  if (!rulHandler.getIsDefined(ruleId)) {
    WriteMsg::write(CMSG_RULE_NOT_DEFINED, ruleId.c_str());
    return;
  }
  if (!rulHandler.getIsEnabled(ruleId)) {
    return; // rule is not enabled
  }

  list<Node> nodes;
  // Find nodes at location
  common::changePath(location.file, changePathFrom, changePathTo);
  if (graphIndexer.findNodesByRange(graph, location.file, location.line, location.column, location.line, INT_MAX, nodes)) {
    int minDist = INT_MAX;
    Node node;
    // Find the closest one
    for(list<Node>::iterator it = nodes.begin(); it != nodes.end(); ++it) {
      vector<graphsupport::Position> positions;
      graphsupport::getPositionAttributes(*it, positions);
      for(vector<graphsupport::Position>::iterator pos = positions.begin(); pos != positions.end(); ++pos) {
        if((abs(location.line-pos->line) + abs(location.line-pos->endline)) < minDist) {
          node = *it;
          minDist = abs(location.line-pos->line) + abs(location.line-pos->endline);
        }
      }
    }
    
    // If the found node is an attribute, we use its parent
    if(node != Graph::invalidNode) {
      if(node.getType().getType() == graphsupport::graphconstants::NTYPE_LIM_ATTRIBUTE) {
        Edge::EdgeIterator edgeIt = node.findOutEdges(Edge::EdgeType(graphsupport::graphconstants::ETYPE_LIM_LOGICALTREE, Edge::edtReverse));
        if(edgeIt.hasNext()) {
          node = edgeIt.next().getToNode();
        }
      }
    }

    if (node != Graph::invalidNode) {
      bool warningAdded = graphsupport::addWarningOnce(graph, node, ruleId, location.file, location.line, location.column, location.line, 10000, warningText);
      
      if (warningAdded){
        if(!txtOutFile.empty()) {
          std::ofstream out(txtOutFile.c_str(), std::ofstream::out | std::ofstream::app);
          if(!out) {
            WriteMsg::write(CMSG_FAILED_TO_OPEN_FILE, txtOutFile.c_str());
          }else{
            out << location.file << "(" << location.line << "): " << ruleId << ": " << warningText << std::endl;
          }
        }
      }else{
        WriteMsg::write(CMSG_UNABLE_TO_ADD_WARNING_AT_LOCATION, location.file.c_str(), location.line);
      }
    }
  }
}

void ResultConverter::aggregateWarnings() {
  graphsupport::cumSum(graph, graph::Edge::EdgeType(graphsupport::graphconstants::ETYPE_LIM_COMPONENT, graph::Edge::edtDirectional), true);
  graphsupport::cumSum(graph, graph::Edge::EdgeType(graphsupport::graphconstants::ETYPE_LIM_COMPONENTTREE, graph::Edge::edtReverse), false);
  graphsupport::cumSum(graph, graph::Edge::EdgeType(graphsupport::graphconstants::ETYPE_LIM_LOGICALTREE, graph::Edge::edtReverse), false);

  graphsupport::createGroupMetrics(graph, rulHandler);
}

void ResultConverter::startElement (const XMLCh *const uri, const XMLCh *const localname, const XMLCh *const qname, const Attributes &attrs){
  char* localnameChar = XMLString::transcode(localname);
  if(strcmp(localnameChar, _WARNING) == 0) {
    const XMLCh* ruleId = attrs.getValue(ruleIdXMLCh);
    const XMLCh* warningMsg = attrs.getValue(warningMsgXMLCh);
    const XMLCh* locationLine = attrs.getValue(locationLineXMLCh);
    const XMLCh* locationColumn = attrs.getValue(locationColumnXMLCh);
    const XMLCh* nodeType = attrs.getValue(nodeTypeXMLCh);

    char* ruleIdChar = XMLString::transcode(ruleId);
    char* warningMsgChar = XMLString::transcode(warningMsg);
    char* locationLineChar = XMLString::transcode(locationLine);
    char* locationColumnChar = XMLString::transcode(locationColumn);
    char* nodeTypeChar = XMLString::transcode(nodeType);

    // Set the current warning's data
    id = ruleIdChar;
    warningText = warningMsgChar;
    
    Location location;
    location.file = currentFileName;
    location.line = atoi(locationLineChar);
    location.column = atoi(locationColumnChar);
    addWarning(location);

    XMLString::release(&ruleIdChar);
    XMLString::release(&warningMsgChar);
    XMLString::release(&locationLineChar);
    XMLString::release(&nodeTypeChar);
  }else if(strcmp(localnameChar, _FILE) == 0) {
    const XMLCh* locationFile = attrs.getValue(locationFileXMLCh);
    char* currentFileChar = XMLString::transcode(locationFile);
    currentFileName = currentFileChar;
    XMLString::release(&currentFileChar);
  }
  XMLString::release(&localnameChar);
}

void ResultConverter::addLicenseTypeToTheGraphHeader(const string& toolName) {
  graph.setHeaderInfo(toolName + graphsupport::graphconstants::HEADER_MODE_KEY_SUFFIX, graphsupport::graphconstants::HEADER_MODE_VALUE_FULL );
}
