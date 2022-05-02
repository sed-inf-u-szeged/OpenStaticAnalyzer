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
#include <boost/filesystem.hpp>
#include <rul/inc/RulTags.h>
#include "../inc/ResultConverter.h"
#include "../inc/messages.h"
#include "../inc/defines.h"

using namespace std;
using namespace common;
using namespace columbus;
using namespace columbus::graph;
using namespace columbus::roslyn2graph;

XERCES_CPP_NAMESPACE_USE


ResultConverter::ResultConverter(const std::string& limFileName, const std::string& txtOutFile, const std::string& changePathFrom, const std::string& changePathTo):
    DefaultHandler(),
    parser(),
    rulHandler("Default", "eng"),
    limStrTable(),
    limFactory(limStrTable, "", columbus::lim::asg::limLangOther),
    graphIndexer(graphsupport::GraphRangeIndexer::getGraphRangeIndexerInstance()),
    changePathFrom(changePathFrom),
    changePathTo(changePathTo)
{
  rulHandler.setToolDescription("ID", "Roslyn2Graph");
  // Loading lim
  list<HeaderData*> headerDataList;
  limFactory.load(limFileName, headerDataList);
  loadFilter(limFactory, limFileName, ".flim");
  lim2graph::convertBaseGraph(limFactory, graph, true, true, true, true, false);
  graphIndexer.turnOn(graph);

  // Xml attribute names
  xmlDiagnosticCh = XMLString::transcode(_DIAGNOSTIC);
  xmlIdCh = XMLString::transcode(_DIAGNOSTIC_ID);
  xmlSeverityCh = XMLString::transcode(_DIAGNOSTIC_SEVERITY);
  xmlIsSuppressedCh = XMLString::transcode(_DIAGNOSTIC_IS_SUPPRESSED);
  xmlMessageCh = XMLString::transcode(_DIAGNOSTIC_MESSAGE);

  xmlLocationCh = XMLString::transcode(_DIAGNOSTIC_LOCATION);
  xmlFilePathCh = XMLString::transcode(_DIAGNOSTIC_FILE_PATH);
  xmlStartLineCh = XMLString::transcode(_DIAGNOSTIC_START_LINE);
  xmlStartCharacterCh = XMLString::transcode(_DIAGNOSTIC_START_CHARACTER);
  xmlEndLineCh = XMLString::transcode(_DIAGNOSTIC_END_LINE);
  xmlEndCharacterCh = XMLString::transcode(_DIAGNOSTIC_END_CHARACTER);

  xmlDescriptorCh = XMLString::transcode(_DIAGNOSTIC_DESCRIPTOR);
  xmlTitleCh = XMLString::transcode(_DIAGNOSTIC_TITLE);
  xmlCategoryCh = XMLString::transcode(_DIAGNOSTIC_CATEGORY);
  xmlDescriptionCh = XMLString::transcode(_DIAGNOSTIC_DESCRIPTION);
  xmlHelpLinkUriCh = XMLString::transcode(_DIAGNOSTIC_HELP_LINK_URI);

  // Creating empty text output file
  if(!txtOutFile.empty()) {
    this->txtOutFile = ofstream(txtOutFile.c_str());
    if(!this->txtOutFile) {
      WriteMsg::write(CMSG_FAILED_TO_OPEN_FILE, txtOutFile.c_str());
    } else {
      this->txtOutFile << "";
    }
  }

  priorityMap["Hidden"] = "Info";
  priorityMap["Info"] = "Minor";
  priorityMap["Warning"] = "Major";
  priorityMap["Error"] = "Critical";
}

ResultConverter::~ResultConverter() {
  XMLString::release(&xmlDiagnosticCh);
  XMLString::release(&xmlIdCh);
  XMLString::release(&xmlSeverityCh);
  XMLString::release(&xmlIsSuppressedCh);
  XMLString::release(&xmlMessageCh);

  XMLString::release(&xmlLocationCh);
  XMLString::release(&xmlFilePathCh);
  XMLString::release(&xmlStartLineCh);
  XMLString::release(&xmlStartCharacterCh);
  XMLString::release(&xmlEndLineCh);
  XMLString::release(&xmlEndCharacterCh);

  XMLString::release(&xmlDescriptorCh);
  XMLString::release(&xmlTitleCh);
  XMLString::release(&xmlCategoryCh);
  XMLString::release(&xmlDescriptionCh);
  XMLString::release(&xmlHelpLinkUriCh);
}

void ResultConverter::process(const std::string& resultFileName){
  WriteMsg::write(CMSG_PROCESSING_FILE, resultFileName.c_str());
  updateComponent(resultFileName);
  parser.parseXML(resultFileName, this);
}

void ResultConverter::saveResultGraph(const std::string& graphOutputFilename, bool createXMLdump) {
  graph.saveBinary(graphOutputFilename);
  if (createXMLdump) {
    graph.saveXML(common::pathRemoveExtension(graphOutputFilename) + ".xml");
  }
}

void ResultConverter::addWarning() {
  if (isSuppressed || severity == "Hidden") {
    return; // rule is not enabled
  }
  if (dynamicRules.find(id) == dynamicRules.end()) {
    defineMetric();
  }

  string ruleId = _RULE_PREFIX + id;
  Node node;

  if (location.file.empty()) {
    node = component;
  } else {
    // Find nodes at location
    common::pathCanonicalize(location.file, location.file);
    common::changePath(location.file, changePathFrom, changePathTo);
    list<Node> nodes;

    if (!graphIndexer.findNodesByRange(graph, location.file, location.startLine, location.startChar, location.endLine,
                                       location.endChar, nodes)) {
      return;
    }

    int minDist = INT_MAX;
    // Find the closest one
    for (auto &it : nodes) {
      vector<graphsupport::Position> positions;
      graphsupport::getPositionAttributes(it, positions);
      for (auto &position : positions) {
        int distance = abs(location.startLine - position.line) + abs(location.endLine - position.endline);
        if (distance < minDist) {
          node = it;
          minDist = distance;
        }
      }
    }

    // If the found node is an attribute, we use its parent
    if (node != Graph::invalidNode) {
      if (node.getType().getType() == graphsupport::graphconstants::NTYPE_LIM_ATTRIBUTE) {
        Edge::EdgeIterator edgeIt = node.findOutEdges(
            Edge::EdgeType(graphsupport::graphconstants::ETYPE_LIM_LOGICALTREE, Edge::edtReverse));
        if (edgeIt.hasNext()) {
          node = edgeIt.next().getToNode();
        }
      }
    }
  }

  if (node == Graph::invalidNode)
    return;

  bool warningAdded = graphsupport::addWarningOnce(graph, node, ruleId, location.file, location.startLine, location.startChar, location.endLine, location.endChar, message, &warningCache);

  if (txtOutFile){
    if (warningAdded) {
      txtOutFile << location.file
          << "(" << location.startLine << ":" << location.startChar
          << " - " << location.endLine <<":"<< location.endChar <<"): "
          << ruleId << ": " << message << std::endl;

    } else {
      WriteMsg::write(CMSG_SKIPPING_DUPLICATE_WARNING, id.c_str());
    }
  }
}

void ResultConverter::aggregateWarnings() {
  WriteMsg::write(CMSG_WRITING_RULES_TO_GRAPH);
  columbus::graphsupport::buildRulToGraph(graph, rulHandler);

  WriteMsg::write(CMSG_AGGREGATING_WARNINGS);
  graphsupport::cumSum(graph, graph::Edge::EdgeType(graphsupport::graphconstants::ETYPE_LIM_COMPONENT, graph::Edge::edtDirectional), true, std::set<std::string>(), true);
  graphsupport::cumSum(graph, graph::Edge::EdgeType(graphsupport::graphconstants::ETYPE_LIM_LOGICALTREE, graph::Edge::edtReverse), false);

  WriteMsg::write(CMSG_CREATING_GROUP_METRICS);
  graphsupport::createGroupMetrics(graph, rulHandler);
}

void ResultConverter::startElement (const XMLCh *const uri, const XMLCh *const localname, const XMLCh *const qname, const Attributes &attrs){
  if (XMLString::compareIString(localname, xmlDiagnosticCh) == 0) {
    char* idValue = XMLString::transcode(attrs.getValue(xmlIdCh));
    char* severityValue = XMLString::transcode(attrs.getValue(xmlSeverityCh));
    char* isSuppressedValue = XMLString::transcode(attrs.getValue(xmlIsSuppressedCh));
    char* messageValue = XMLString::transcode(attrs.getValue(xmlMessageCh));

    id = idValue;
    severity = severityValue;
    isSuppressed = strcmp("true", isSuppressedValue) == 0;
    message = messageValue;

    XMLString::release(&idValue);
    XMLString::release(&severityValue);
    XMLString::release(&isSuppressedValue);
    XMLString::release(&messageValue);

  } else if (XMLString::compareIString(localname, xmlLocationCh) == 0) {
    char* filePathValue = XMLString::transcode(attrs.getValue(xmlFilePathCh));
    char* startLineValue = XMLString::transcode(attrs.getValue(xmlStartLineCh));
    char* startCharacterValue = XMLString::transcode(attrs.getValue(xmlStartCharacterCh));
    char* endLineValue = XMLString::transcode(attrs.getValue(xmlEndLineCh));
    char* endCharacterValue = XMLString::transcode(attrs.getValue(xmlEndCharacterCh));

    location.file = filePathValue;
    location.startLine = atoi(startLineValue);
    location.startChar = atoi(startCharacterValue);
    location.endLine = atoi(endLineValue);
    location.endChar = atoi(endCharacterValue);

    XMLString::release(&filePathValue);
    XMLString::release(&startLineValue);
    XMLString::release(&startCharacterValue);
    XMLString::release(&endLineValue);
    XMLString::release(&endCharacterValue);

  } else if (XMLString::compareIString(localname, xmlDescriptorCh) == 0) {
    char* titleValue = XMLString::transcode(attrs.getValue(xmlTitleCh));
    char* categoryValue = XMLString::transcode(attrs.getValue(xmlCategoryCh));
    char* descriptionValue = XMLString::transcode(attrs.getValue(xmlDescriptionCh));
    char* helpLinkUriValue = XMLString::transcode(attrs.getValue(xmlHelpLinkUriCh));

    title = titleValue;
    category = categoryValue;
    description = descriptionValue;
    helpLinkUri = helpLinkUriValue;

    XMLString::release(&titleValue);
    XMLString::release(&categoryValue);
    XMLString::release(&descriptionValue);
    XMLString::release(&helpLinkUriValue);
  }
}

void ResultConverter::endElement(const XMLCh *const uri, const XMLCh *const localname, const XMLCh *const qname){
  if (XMLString::compareIString(localname, xmlDiagnosticCh) == 0) {
    addWarning();
    id.clear();
    location.file.clear();
  }
}

void ResultConverter::defineMetric() {
  string fullGroupId = _RULE_GROUP_PREFIX + category;
  string fullId = _RULE_PREFIX + id;
  string fullDescription = description + '\n' + helpLinkUri;
  rulHandler.defineMetric(fullId);
  rulHandler.createConfiguration(fullId, "Default");
  rulHandler.setIsEnabled(fullId, true);
  rulHandler.setIsVisible(fullId, true);
  rulHandler.setGroupType(fullId, "false");
  {
    auto &tag_metadata =
        rulHandler.getTagMetadataStore().try_add_kind("general").try_add_value(fullGroupId).value_metadata_ref();
    tag_metadata.summarized = true;
    rulHandler.addTag(fullId, rul::SplitTagStringView{"tool", "Roslyn"});
    rulHandler.addTag(fullId, rul::SplitTagStringView{"general", fullGroupId});
  }
  rulHandler.createLanguage(fullId, "eng");
  rulHandler.setHasWarningText(fullId, true);
  rulHandler.setSettingValue(fullId, "Priority", priorityMap[severity], true);
  rulHandler.setDisplayName(fullId, title);
  rulHandler.setHelpText(fullId, fullDescription);
  rulHandler.setDescription(fullId, fullDescription);
  rulHandler.setOriginalId(fullId, id);
  dynamicRules.insert(id);
}

void ResultConverter::updateComponent(const string& inputFileName) {
  string projectName = boost::filesystem::path(inputFileName).stem().string();
  for (auto it = graph.findNodes(Node::NodeType("Component")); it.hasNext();) {
    string name;
    component = it.next();
    graphsupport::getNodeNameAttribute(component, name);
    if (name == projectName) {
      return;
    }
  }

  throw Exception(COLUMBUS_LOCATION, CMSG_EX_UNKNOWN_COMPONENT + projectName);
}
