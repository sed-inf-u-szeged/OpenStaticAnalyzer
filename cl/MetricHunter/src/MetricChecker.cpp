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

#include "../inc/MetricChecker.h"
#include "../inc/defines.h"
#include "../inc/messages.h"
#include <iostream>
#include <fstream>
#include <common/inc/Stat.h>
#include <common/inc/StringSup.h>
#include <common/inc/WriteMessage.h>
#include <rul/inc/RulHandler.h>
#include <graph/inc/graph.h>
#include <graphsupport/inc/Metric.h>
#include <graphsupport/inc/GraphConstants.h>

#include <xercesc/sax2/SAX2XMLReader.hpp>
#include <xercesc/sax2/XMLReaderFactory.hpp>
#include <xercesc/sax2/DefaultHandler.hpp>
#include <xercesc/sax2/Attributes.hpp>
#include <xercesc/util/XMLString.hpp>

using namespace std;
using namespace common;
using namespace columbus;
using namespace columbus::rul;

namespace columbus { namespace rul {

  MetricChecker::MetricChecker(graph::Graph& graph, rul::RulHandler& handler, const string& txtOutputFileName) : theGraph(graph), rul(&handler), txtOutputFileName(txtOutputFileName) {    
    count=0;
  };

  const bool MetricChecker::checkRuleProperties(string& rulid, const string& nodetype) {
    set<string> sset = rul->getCalculatedForSet(rulid);
    if (rul->getIsDefined(rulid) && rul->getIsEnabled(rulid)) {
      for(set<string>::const_iterator it = sset.begin(); it != sset.end(); it++) {
        if(*it == nodetype){ return true; }
      }

    }
    return false;
  }

  void MetricChecker::addNodeType(string& nodeType){
    nodeTypes.insert(nodeType);
  }

  void MetricChecker::runChecker(){
    set<string> allRules;
    rul->getRuleIdList(allRules);

    set<string> notGroupRules;
    
    for (set<string>::iterator RulesIt = allRules.begin(); RulesIt != allRules.end(); ++ RulesIt) {
      if (rul->getGroupType(*RulesIt) == "false" && rul->getIsEnabled(*RulesIt)) 
        notGroupRules.insert(*RulesIt);
    }

    for(set<string>::const_iterator iter = nodeTypes.begin(); iter != nodeTypes.end(); iter++) {
      const string& nodetype = *iter;
      graph::Node::NodeIterator methodNodes = theGraph.findNodes(graph::Node::NodeType( nodetype ));
      while(methodNodes.hasNext()){
        graph::Node mn = methodNodes.next();
        for(set<string>::const_iterator it = notGroupRules.begin(); it != notGroupRules.end(); it++) {
          
          string rulid = *it;
          string whichMetric = rul->getSettingValue(rulid, "metricName");
          string whichRelation = rul->getSettingValue(rulid, "relation");
          string whichBaseline = rul->getSettingValue(rulid, "threshold"); 

          if(checkRuleProperties( rulid, nodetype)){
            executeCheck(mn, whichMetric, rulid, whichRelation, whichBaseline);
          }
        }
      }
    }
  }

  void MetricChecker::addWarning(columbus::graph::Node& node, const string& warningName, const string& warningText){
    int line = extractIntCompAttr(node, "Position", "Line");
    int col = extractIntCompAttr(node, "Position", "Column");
    int endline = extractIntCompAttr(node, "Position", "EndLine");
    int endcol = extractIntCompAttr(node, "Position", "EndColumn");
    string path = extractStringCompAttr(node,"Position", "Path");

    string name;
    graphsupport::getNodeNameAttribute(node, name);

    string filledWarningText = common::replace(warningText.c_str(), "%", name.c_str());

    if(graphsupport::addWarningOnce(theGraph, node, warningName, path, line, col, endline, endcol, filledWarningText)) {
      ofstream txtOutputStream(txtOutputFileName.c_str(), ios::app);
      ostream* output = NULL;

      if (txtOutputStream)
        output = &txtOutputStream;
      else
        output = &cout;

      if (!path.empty())
        (*output) << path << "(" << line << "):" << warningName << ": " << filledWarningText << "\n";
      else
        (*output) << warningName << ": " << filledWarningText << "\n";
        
      WriteMsg::write(CMSG_WARNING_ADDED, node.getUID().c_str(), warningName.c_str());
      count++;
    }
    else {
      WriteMsg::write(CMSG_WARNING_NOT_ADDED, node.getUID().c_str());
    }
  };

  void MetricChecker::save(const std::string& savingPath, bool saveXML, const std::string& xmlPath) {
    theGraph.saveBinary(savingPath);
    WriteMsg::write(CMSG_GRAPH_SAVED, savingPath.c_str());
    if(saveXML) {
      theGraph.saveXML(xmlPath + ".xml");
      WriteMsg::write(CMSG_XML_SAVED);
    }
  };

  void MetricChecker::executeCheck(columbus::graph::Node& node, const std::string& metricName, const std::string& rulename, const std::string& relation, const std::string& baselineStr) {
    double metricValue = 0;
    string metricValueStr;
   
    graph::Attribute::AttributeIterator aIt = node.findAttributeByName( metricName );
    if ( aIt.hasNext() ) {
      graph::Attribute& attr = aIt.next();
      metricValueStr = attr.getStringValue();
      if(attr.getType() == graph::Attribute::atInt) {
         metricValue = ((graph::AttributeInt&)attr).getValue();
      } else if(attr.getType() == graph::Attribute::atFloat) {
        metricValue = ((graph::AttributeFloat&)attr).getValue();
      } else {
        return;
      }
    } else {
      return;
    }

    double baseline;
    common::str2double(baselineStr, baseline);

    string warningText = getWarningString(metricName, node.getType().getType(), relation,  metricValueStr, baselineStr);
    if(relation == LESS_THAN) {
      if((float)metricValue < baseline) { addWarning(node, rulename, warningText); }
    } else if(relation == GREATER_THAN) {
      if((float)metricValue > baseline) { addWarning(node, rulename, warningText); }
    } else if(relation == LESS_EQUAL) {
      if((float)metricValue <= baseline) { addWarning(node, rulename, warningText); }
    } else if(relation == GREATER_EQUAL) {
      if((float)metricValue >= baseline) { addWarning(node, rulename, warningText); }
    } else { WriteMsg::write(CMSG_UNKNOWN_REL_ERROR); }

  };
  
} }
