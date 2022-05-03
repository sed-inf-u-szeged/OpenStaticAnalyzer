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
using namespace columbus::cppcheck2graph;


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
  warningMsgXMLCh = XMLString::transcode(_WARNING_MSG);
  locationFileXMLCh = XMLString::transcode(_WARNING_LOCATION_FILE);
  locationFile0XMLCh = XMLString::transcode(_WARNING_LOCATION_FILE0);
  locationLineXMLCh = XMLString::transcode(_WARNING_LOCATION_LINE);

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
  XMLString::release(&locationFile0XMLCh);
  XMLString::release(&locationLineXMLCh);
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

void ResultConverter::addWarning(){
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
  // The last location is the place of the warning
  Location location = locations.back();
  locations.pop_back();
  // Find nodes at location
  common::pathCanonicalize(location.file, location.file);
  location.file = common::replace(location.file.c_str(), changePathFrom.c_str(), changePathTo.c_str());
  if (graphIndexer.findNodesByRange(graph, location.file, location.line, 0, location.line, INT_MAX, nodes)) {
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
      bool warningAdded = false;
      // If there is more location, then we creating extraInfo attribute
      if (locations.size() != 0) {
        AttributeComposite extraInfo = graph.createAttributeComposite(graphsupport::graphconstants::ATTR_EXTRAINFO, graphsupport::graphconstants::CONTEXT_TRACE);
        for(list<Location>::iterator it = locations.begin(); it != locations.end(); ++it)
        {
          common::pathCanonicalize(it->file, it->file);
          it->file = common::replace(it->file.c_str(), changePathFrom.c_str(), changePathTo.c_str());
          extraInfo.addAttribute(graphsupport::createSourceLinkAttribute(graph, it->file, it->line));
        }

        warningAdded = graphsupport::addWarningOnce(graph, node, ruleId, location.file, location.line, 0, location.line, 10000, warningText, extraInfo, &warningCache);
      } else{
        warningAdded = graphsupport::addWarningOnce(graph, node, ruleId, location.file, location.line, 0, location.line, 10000, warningText, &warningCache);
      }
      
      if (warningAdded){
        if(!txtOutFile.empty()) {
          std::ofstream out(txtOutFile.c_str(), std::ofstream::out | std::ofstream::app);
          if(!out) {
            WriteMsg::write(CMSG_FAILED_TO_OPEN_FILE, txtOutFile.c_str());
          }else{
            out << location.file << "(" << location.line << "): " << ruleId << ": " << warningText << std::endl;
          }
        }
      }
    }
    else
    {
      WriteMsg::write(CMSG_UNABLE_TO_ADD_WARNING_AT_LOCATION, location.file.c_str(), location.line);
    }
  }
  else
  {
    WriteMsg::write(CMSG_UNABLE_TO_ADD_WARNING_AT_LOCATION, location.file.c_str(), location.line);
  }
}

void ResultConverter::aggregateWarnings() {
  graphsupport::cumSum(graph, graph::Edge::EdgeType(graphsupport::graphconstants::ETYPE_LIM_COMPONENT, graph::Edge::edtDirectional), true, std::set<std::string>(), true);
  graphsupport::cumSum(graph, graph::Edge::EdgeType(graphsupport::graphconstants::ETYPE_LIM_LOGICALTREE, graph::Edge::edtReverse), false);

  graphsupport::createGroupMetrics(graph, rulHandler);
}

void ResultConverter::startElement (const XMLCh *const uri, const XMLCh *const localname, const XMLCh *const qname, const Attributes &attrs){
  char* localnameChar = XMLString::transcode(localname);
  if(strcmp(localnameChar, _WARNING) == 0) {
    const XMLCh* ruleId = attrs.getValue(ruleIdXMLCh);
    const XMLCh* warningMsg = attrs.getValue(warningMsgXMLCh);
    
    char* ruleIdChar = XMLString::transcode(ruleId);
    char* warningMsgChar = XMLString::transcode(warningMsg);
        
    // Set the current warning's data
    id = ruleIdChar;
    warningText = warningMsgChar;
    
    XMLString::release(&ruleIdChar);
    XMLString::release(&warningMsgChar);
  } 
  else if(strcmp(localnameChar, _WARNING_LOCATION) == 0) {
    const XMLCh* locationFile = attrs.getValue(locationFileXMLCh);
    const XMLCh* locationFile0 = attrs.getValue(locationFile0XMLCh);
    const XMLCh* locationLine = attrs.getValue(locationLineXMLCh);
    
    char* locationFileChar = XMLString::transcode(locationFile);
    char* locationFile0Char = locationFile0 ? XMLString::transcode(locationFile0) : nullptr;
    char* locationLineChar = XMLString::transcode(locationLine);

    // Creating and adding the location to the current warning's locations
    Location location;
    
    if (locationFile0Char == nullptr)
      location.file = locationFileChar;
    else
    {
      if (!common::pathIsRelative(locationFileChar))
        location.file = locationFileChar;
      else
        location.file = common::pathRemoveFileSpec(locationFile0Char) + DIRDIVSTRING + locationFileChar;
    }

    
    location.line = atoi(locationLineChar);
    locations.push_back(location);
    
    XMLString::release(&locationFileChar);
    XMLString::release(&locationLineChar);
  }
  XMLString::release(&localnameChar);
}

void ResultConverter::endElement(const XMLCh *const uri, const XMLCh *const localname, const XMLCh *const qname){
  char* localnameChar = XMLString::transcode(localname);
  if(strcmp(localnameChar, _WARNING) == 0) {
    // If the warning has location, then add it to the graph
    if(locations.size()>0){
      addWarning();
      locations.clear();
      id.clear();
    }
  }
  XMLString::release(&localnameChar);
}
