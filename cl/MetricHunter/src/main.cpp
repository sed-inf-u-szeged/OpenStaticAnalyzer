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

#define PROGRAM_NAME "MetricHunter"
#define EXECUTABLE_NAME "MetricHunter"

#include <fstream>
#include <string>
#include <time.h>

#include <MainCommon.h>
#include <LanguageCommon.h>
#include <common/inc/FileSup.h>
#include <common/inc/WriteMessage.h>

#include <common/inc/Stat.h>
#include <common/inc/messages.h>
#include <rul/inc/RulHandler.h>
#include <graph/inc/graph.h>
#include <graphsupport/inc/Metric.h>
#include <graphsupport/inc/MetricSum.h>
#include "../inc/messages.h"
#include "../inc/defines.h"
#include "../inc/ThresholdReader.h"
#include "../inc/MetricChecker.h"
#include <graphsupport/inc/RulBuilder.h>
#include <graphsupport/inc/GraphConstants.h>

using namespace std;
using namespace common;
using namespace columbus;
using namespace columbus::rul;
using namespace graph;
using namespace graphsupport;


string thresholdFile = "MetricHunter.threshold";
string graphOutputFileName;
string txtOutputFileName;
bool exportRul = false;
string newRulPath;
string inputFileName;
string rulFileConfig;

static bool ppGraph(const Option *o, char *argv[]) {
  graphOutputFileName = argv[0];
  return true;
}

static bool ppOut(const Option *o, char *argv[]) {
  txtOutputFileName = argv[0];
  return true;
}

bool ppRulConfig (const common::Option *o, char *argv[]) {
  rulFileConfig = argv[0];
  return true;
}

bool ppThresholdFile(const Option *o, char *argv[]) {
  thresholdFile = argv[0];
  return true;
}

static void ppFile(char *filename) {
  inputFileName = filename;
}

bool ppExportRul(const Option *o, char *argv[]) {
  exportRul = true;
  return true;
}

const common::Option OPTIONS_OBJ [] = {
  { false,  "-graph",       1, "filename",      1, OT_WC,    ppGraph,           NULL, "The output graph with the warnings."},
  { false,  "-out",         1, "filename",      0, OT_WC,    ppOut,             NULL, "The output text with the warnings."},
  { false,  "-thresholds",  1, "filename",      1, OT_WC,    ppThresholdFile,   NULL, "The thresholds file."},
  CL_EXPORTRUL
  COMMON_CL_ARGS
};

bool checkRuleFromGraph(Graph& graph, const Threshold& threshold) {
  
  string description;
  string displayName; 
  bool isEnabled;
  string groupType;
  string helpText;
  bool isWarning;
  map<string, string> settings;
  set<string> calculated;
  
  if (!graphsupport::readRuleItemFromGraph(graph, threshold.getMid(), description, displayName, isEnabled, groupType, helpText, isWarning, settings, calculated)) {
    WriteMsg::write(CMSG_NO_RULE_FOUND, threshold.getMid().c_str());
    return false;
  }
  if (!isEnabled) {
    WriteMsg::write(CMSG_RULE_IS_NOT_ENABLED, threshold.getMid().c_str());
    return false;
  }
  for (vector<string>::const_iterator entitiesIt = threshold.getEntities().begin();  entitiesIt != threshold.getEntities().end(); ++entitiesIt) {
    if (calculated.find(*entitiesIt) == calculated.end()) {
      WriteMsg::write(CMSG_INVALID_ENTITY, threshold.getMid().c_str(), entitiesIt->c_str());
      return false;
    }
  }
  
  return true;
}

string getWarningGroupName(const string& metricGroupName) {
  return metricGroupName + " Metric Rules";
}

void buildWarningMetricRules(Graph& graph, RulHandler& rlh) {
   
  Node::NodeIterator rulNodesIt = graph.findNodes(graphconstants::NTYPE_RUL_METRIC);
  while (rulNodesIt.hasNext()) {
    Node node = rulNodesIt.next();
    const Attribute& groupTypeAttr = getNodeAttribute(node, Attribute::atString, graphconstants::ATTR_RUL_GROUPTYPE, graphconstants::CONTEXT_RUL);
    if (groupTypeAttr != Graph::invalidAttribute) {
      if (groupTypeAttr.getStringValue() == "visual") {
        string gMid = getWarningGroupName(node.getUID());
        const string& displayName = node.findAttributeByName(graphsupport::graphconstants::ATTR_RUL_DISPLAYNAME).next().getStringValue();
        rlh.defineMetric(gMid);
        rlh.createConfiguration(gMid, "Default");
        rlh.createLanguage(gMid, "en");
        rlh.setDescription(gMid, "");
        rlh.setDisplayName(gMid, gMid);
        rlh.setHelpText(gMid, "These rules deal with '" + displayName + "' threshod violations.");
        rlh.setGroupType(gMid, "summarized");
        rlh.setIsEnabled(gMid, true);
        rlh.setHasWarningText(gMid, true);
        
        Edge::EdgeIterator metricIt = node.findOutEdges(Edge::EdgeType(graphconstants::ETYPE_RUL_GROUPCONTAINS, Edge::edtDirectional));
        while (metricIt.hasNext()) {
          Node metricNode = metricIt.next().getToNode();
          AttributeComposite& calculatedAttr = (AttributeComposite&)getNodeAttribute(metricNode, Attribute::atComposite, graphconstants::ATTR_RUL_CALCULATED, graphconstants::CONTEXT_RUL);
          if (calculatedAttr!= Graph::invalidAttribute) {
            Attribute::AttributeIterator calculatedForAttrIt = calculatedAttr.findAttributeByName(graphconstants::ATTR_RUL_CALCULATEDFOR);
            while (calculatedForAttrIt.hasNext()) {
              const string& entity = calculatedForAttrIt.next().getStringValue();
              
              string newMid = getWarningName(metricNode.getUID(), entity);
              rlh.defineMetric(newMid);
              rlh.createConfiguration(newMid, "Default");
              rlh.createLanguage(newMid, "en");
              rlh.setIsEnabled(newMid, false);
              rlh.setDisplayName(newMid, metricNode.getUID() + " warning");
              rlh.setDescription(newMid, "");
              rlh.setGroupType(newMid, "false");
              rlh.setHasWarningText(newMid, true);              
              rlh.setHelpText(newMid, "Threshold warning for '" + metricNode.getUID() + "' metrics of the '" + entity + "' entities.");
              rlh.setSettingValue(newMid, graphsupport::graphconstants::ATTR_RUL_PRIORITY, "Info", false);

              set<string> calculatedForSet;
              calculatedForSet.insert(entity);
              rlh.setCalculatedForSet(newMid, calculatedForSet);
              
              rlh.addMetricGroupMembers(newMid, gMid);

            }
          }
        }
      }
    }
  }
}


void buildNewRule(Graph& graph, RulHandler& rlh, vector<Threshold>& thresholds) {
  rlh.setToolDescription("ID", "MetricHunter");
  for (vector<Threshold>::const_iterator thresholdIt = thresholds.begin(); thresholdIt != thresholds.end(); ++thresholdIt) {
    if (checkRuleFromGraph(graph, *thresholdIt))
      for (vector<string>::const_iterator entitiesIt = thresholdIt->getEntities().begin(); entitiesIt != thresholdIt->getEntities().end(); ++entitiesIt) {
        string newMid = getWarningName(thresholdIt->getMid(),  *entitiesIt);
        rlh.setIsEnabled(newMid, true);
        rlh.setWarningText(newMid, getWarningString(thresholdIt->getMid(), *entitiesIt, thresholdIt->getRelation(), "", thresholdIt->getValue()));
        rlh.setSettingValue(newMid, "threshold", thresholdIt->getValue(), false);
        rlh.setSettingValue(newMid, "relation", thresholdIt->getRelation(), false);
        rlh.setSettingValue(newMid, "metricName", thresholdIt->getMid(), false);
      }
    else if (WriteMsg::getMessageLevel() >= WriteMsg::mlWarning)
      WriteMsg::write(CMSG_RULE_SKIPPED, thresholdIt->info().c_str());
  }
}

int main(int argc, char* argv[]) {

  MAIN_BEGIN

  MainInit(argc, argv, "-"); 

  if (inputFileName.empty()) {
    WriteMsg::write(CMSG_NO_INPUT_FILE);
    clError();
  }

  if (graphOutputFileName.empty()) {
    WriteMsg::write(CMSG_NO_OUTPUT_FILE);
    clError();
  }

  if (thresholdFile.empty()) {
    WriteMsg::write(CMSG_NO_THRESHOLD_FILE);
    clError();
  }

  WriteMsg::write(CMSG_DEBUG_INPUT, inputFileName.c_str(), thresholdFile.c_str());

  Graph graph;
  ThresholdReader th(thresholdFile);
  vector<Threshold> vec = th.getThresholdVector();
  set<string> defined_nodes = th.getDefinedEntites();
  RulHandler rlh("Default", "en");

  graph.loadBinary(inputFileName);

  buildWarningMetricRules(graph, rlh);
  buildNewRule(graph, rlh, vec);

  if (!txtOutputFileName.empty()) 
     ofstream(txtOutputFileName.c_str(), ofstream::trunc);

  columbus::graphsupport::buildRulToGraph(graph, rlh);
  MetricChecker mc(graph, rlh, txtOutputFileName);
  
  for (set<string>::const_iterator i = defined_nodes.begin(); i != defined_nodes.end(); i++) {
    string element = *i;
    mc.addNodeType(element);
  }
  
  mc.runChecker();
  
  set<string> metrics;
  rlh.getRuleIdList(metrics);

  graphsupport::cumSum(graph, Edge::EdgeType(graphsupport::graphconstants::ETYPE_LIM_COMPONENT, Edge::edtDirectional), true, metrics);
  graphsupport::cumSum(graph, Edge::EdgeType(graphsupport::graphconstants::ETYPE_LIM_COMPONENTTREE, Edge::edtReverse), false, metrics);
  graphsupport::cumSum(graph, Edge::EdgeType(graphsupport::graphconstants::ETYPE_LIM_LOGICALTREE, Edge::edtReverse), false, metrics);
  

  graphsupport::summarizeWarningMetricsByPriority(graph, true, metrics);
  graphsupport::createGroupMetrics(graph, rlh, metrics);

  WriteMsg::write(CMSG_ADDED_WARNINGS, mc.count);
    
  mc.save(graphOutputFileName, false, "");

  MAIN_END

  return 0;
}
