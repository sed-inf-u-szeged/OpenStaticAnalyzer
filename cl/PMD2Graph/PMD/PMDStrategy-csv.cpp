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

#include <xercesc/util/PlatformUtils.hpp>
#include <xercesc/util/TransService.hpp>
#include <xercesc/parsers/AbstractDOMParser.hpp>
#include <xercesc/dom/DOM.hpp>

#include <xercesc/dom/DOMDocument.hpp>
#if defined(XERCES_NEW_IOSTREAMS)
#include <iostream>
#else
#include <iostream.h>
#endif
#include "PMDStrategy.h"
#include <rul/inc/RulHandler.h>
#include <common/inc/StringSup.h>
#include <graphsupport/inc/CsvExporter.h>
#include <graphsupport/inc/MetricSum.h>
#include <graphsupport/inc/GraphConstants.h>
#include "../messages.h"

#if defined(XERCES_NEW_IOSTREAMS)
#include <iostream>
#else
#include <iostream.h>
#endif

using namespace columbus;
using namespace common;
using namespace std;
XERCES_CPP_NAMESPACE_USE

static std::string toUTF8String(const XMLCh* ch) {
  return (char*)TranscodeToStr(ch, "UTF-8").str();
}

void PMDStrategy::makeCsv(std::string& lim, std::string& rul, std::string& rulConfig, File_Names& file_names, std::string& metrics, std::string& groupedmetrics, std::string& monitor, std::string& checkerbasedir, std::string& pathfrom, std::string& pathto, FILE *f) {
  std::map<string, string> levelMap;
  levelMap.insert(make_pair("Namespace", "Package"));
  levelMap.insert(make_pair("Class", "Class"));
  levelMap.insert(make_pair("Method", "Method"));

  CheckerStrategy::makeCsv(lim, rul, rulConfig, file_names, metrics, groupedmetrics, monitor, checkerbasedir, levelMap);

  std::string iniFileName = ((common::pathFindFileName(rul) == rul) ? "." + string(DIRDIVSTRING) : "") + rul;
  rul::RulHandler rulHandler(iniFileName, "Default", "eng", "ISO-8859-1");

  graph.setHeaderInfo("asg", "java");

  for(File_Names::iterator it = file_names.begin(); it != file_names.end(); it++)
    collectdata(*it, rulHandler, checkerbasedir, pathfrom, pathto, f);

  // summarize warnings
  graphsupport::cumSum(graph, graph::Edge::EdgeType(graphsupport::graphconstants::ETYPE_LIM_COMPONENT, graph::Edge::edtDirectional), true);
  graphsupport::cumSum(graph, graph::Edge::EdgeType(graphsupport::graphconstants::ETYPE_LIM_COMPONENTTREE, graph::Edge::edtReverse), false);
  graphsupport::cumSum(graph, graph::Edge::EdgeType(graphsupport::graphconstants::ETYPE_LIM_LOGICALTREE, graph::Edge::edtReverse), false);
  // create group metrics
  columbus::graphsupport::createGroupMetrics(graph, rulHandler);

}

void PMDStrategy::collectdata(std::string& fileName,rul::RulHandler& rul, std::string& checkerbasedir, std::string& pathfrom, std::string& pathto, FILE *f) {
  map<string, string> mapping;
  vector<string> ruleIds;
  rul.getRuleIdList(ruleIds);
  for (vector<string>::const_iterator it = ruleIds.begin(); it != ruleIds.end(); ++it) {
    mapping[rul.getDisplayName(*it)] = *it;
  }

  const string chkbasedir = common::stringLower((const string&)checkerbasedir);
  size_t chkbasedir_lenght = chkbasedir.length();

  const string lowerpathfrom = common::stringLower((const string&)pathfrom);
  size_t lowerpathfrom_lenght = lowerpathfrom.length();

  WriteMsg::write(CMSG_PMD2GRAPH_LOADING_XML, fileName.c_str());
  loaddom(fileName.c_str());
  if (doc && doc->getDocumentElement()) {
    DOMElement* root = doc->getDocumentElement();
    DOMNodeList* childs = root->getChildNodes();
    XMLSize_t length = childs->getLength();
    for(unsigned int i = 0; i < length; i++){
      DOMNode * node = childs->item(i);
      const char* node_type = XMLString::transcode(node->getNodeName());
      if( strcmp(node_type,"file") == 0 && 
          node->getAttributes()->getNamedItem(XMLString::transcode("name"))) {

            DOMNamedNodeMap * mymap = node->getAttributes();

            XMLCh* nameAttr = XMLString::transcode("name");
            string path = toUTF8String(mymap->getNamedItem(nameAttr)->getNodeValue());
            XMLString::release(&nameAttr);

            string path_lower = common::stringLower((const string&)path);

            if (lowerpathfrom_lenght) {
              string::size_type found = 0;
              while ((found = path_lower.find(lowerpathfrom, found)) != string::npos) {
                path.replace(found, lowerpathfrom_lenght, pathto);
                path_lower = common::stringLower((const string&)path);
                found += pathto.length();
              }
            }

            if (chkbasedir_lenght && path_lower.compare(0, chkbasedir_lenght, chkbasedir)==0)
              path = path.substr(chkbasedir_lenght);

            DOMNodeList* childs2 = node->getChildNodes();
            XMLSize_t length2 = childs2->getLength();
            for(unsigned int j = 0; j < length2; j++){
              DOMNode * node2 = childs2->item(j);
              if( strcmp(XMLString::transcode(node2->getNodeName()),"violation") == 0) {
                    DOMNamedNodeMap * mymap = node2->getAttributes();
                    int we_line = 0, we_col = 0, we_endline = 0, we_endcol = 0;
                    string we_uniquename = "", we_path = "", we_groupID = "", we_warningID = "", we_warningtext = "";
                    if(mymap->getNamedItem(XMLString::transcode("beginline")))
                      str2int(XMLString::transcode(mymap->getNamedItem(XMLString::transcode("beginline"))->getNodeValue()), we_line);
                    if(mymap->getNamedItem(XMLString::transcode("begincolumn")))
                      str2int(XMLString::transcode(mymap->getNamedItem(XMLString::transcode("begincolumn"))->getNodeValue()), we_col);
                    if(mymap->getNamedItem(XMLString::transcode("endline")))
                      str2int(XMLString::transcode(mymap->getNamedItem(XMLString::transcode("endline"))->getNodeValue()), we_endline);
                    if(mymap->getNamedItem(XMLString::transcode("endcolumn")))
                      str2int(XMLString::transcode(mymap->getNamedItem(XMLString::transcode("endcolumn"))->getNodeValue()), we_endcol);
                    we_path = path;
                    if(mymap->getNamedItem(XMLString::transcode("package")))
                      we_uniquename = X(mymap->getNamedItem(XMLString::transcode("package"))->getNodeValue());

                    if(mymap->getNamedItem(XMLString::transcode("rule"))) {
                      string ruleName = separateName(X(mymap->getNamedItem(XMLString::transcode("rule"))->getNodeValue()));
                      we_warningID = mapping[ruleName];
                    }
                    const XMLCh * wtext = node2->getTextContent();
                    XMLString::collapseWS((XMLCh*)wtext);
                    we_warningtext = toUTF8String(wtext);
                    try {
                      mt->addWarningToNode(chkbasedir + we_path, we_line, we_col, we_endline, we_endcol, we_groupID, we_warningID, we_warningtext, false, f);
                    } catch(Exception &e) {
                      WriteMsg::write(CMSG_PMD2GRAPH_EXCEPTION_INFO, e.getLocation().c_str(), e.getMessage().c_str());
                    }
              }
            }
      } else if(strcmp(node_type,"error") == 0) {
        stats.error_files.push_back(XMLString::transcode(node->getAttributes()->getNamedItem(XMLString::transcode("filename"))->getNodeValue()));
      }
    }
  }
}


