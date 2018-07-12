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

#include "../inc/RulBuilder.h"
#include "../inc/Metric.h"
#include "../inc/GraphConstants.h"
#include <rul/inc/RulHandler.h>

using namespace std;
using namespace columbus::graph;

namespace columbus { namespace graphsupport {

void buildRulToGraph(Graph& graph, rul::RulHandler& rulHandler) {
  Node root = graph.findNode(graphconstants::UID_RUL_ROOT);
  if(root == Graph::invalidNode) {
    root = graph.createNode(graphconstants::UID_RUL_ROOT, graphconstants::NTYPE_ROOT);
  }
  
  Node tool = graph.findNode(rulHandler.getToolDescription("ID"));
  if (tool == Graph::invalidNode) {
    tool = graph.createNode(rulHandler.getToolDescription("ID"), graphconstants::NTYPE_RUL_TOOL);
    graph.createDirectedEdge(root, tool, graphconstants::ETYPE_RUL_TREE, true);
  }
  
  Node groups = graph.findNode(graphconstants::UID_RUL_GROUPS); 
  if (groups == Graph::invalidNode) {
    groups = graph.createNode(graphconstants::UID_RUL_GROUPS, graphconstants::NTYPE_RUL_TREE_NODE);
    graph.createDirectedEdge(root, groups, graphconstants::ETYPE_RUL_TREE, true);
  }
  
  
  
  set<string> rulIdList;
  rulHandler.getRuleIdList(rulIdList);
  for(set<string>::const_iterator rulIdIt = rulIdList.begin(); rulIdIt != rulIdList.end(); ++rulIdIt) {
  
    Node metric = graph.findNode(*rulIdIt);
    if (metric == Graph::invalidNode) {
      metric = graph.createNode(*rulIdIt, graphconstants::NTYPE_RUL_METRIC);
      
      if (rulHandler.getGroupType(*rulIdIt) == "false")
        graph.createDirectedEdge(tool, metric, graphconstants::ETYPE_RUL_TREE, true);
      else
        graph.createDirectedEdge(groups, metric, graphconstants::ETYPE_RUL_TREE, true);

      metric.addAttribute(graph.createAttributeString(graphconstants::ATTR_RUL_DESCRIPTION, graphconstants::CONTEXT_RUL, rulHandler.getDescription(*rulIdIt)));
      metric.addAttribute(graph.createAttributeString(graphconstants::ATTR_RUL_DISPLAYNAME, graphconstants::CONTEXT_RUL, rulHandler.getDisplayName(*rulIdIt)));
      metric.addAttribute(graph.createAttributeString(graphconstants::ATTR_RUL_ENABLED, graphconstants::CONTEXT_RUL, rulHandler.getIsEnabled(*rulIdIt)?"true":"false"));
      metric.addAttribute(graph.createAttributeString(graphconstants::ATTR_RUL_GROUPTYPE, graphconstants::CONTEXT_RUL, rulHandler.getGroupType(*rulIdIt)));
      metric.addAttribute(graph.createAttributeString(graphconstants::ATTR_RUL_HELPTEXT, graphconstants::CONTEXT_RUL, rulHandler.getHelpText(*rulIdIt)));
      metric.addAttribute(graph.createAttributeString(graphconstants::ATTR_RUL_WARNING, graphconstants::CONTEXT_RUL, rulHandler.getHasWarningText(*rulIdIt)?"true":"false"));

      AttributeComposite& settingsAttr = dynamic_cast<AttributeComposite&>(metric.addAttribute(graph.createAttributeComposite(graphconstants::ATTR_RUL_SETTINGS, graphconstants::CONTEXT_RUL)));
      set<string> settingsSet;
      rulHandler.getMetricSettingsName(*rulIdIt, settingsSet);
      for(set<string>::const_iterator settingsIt = settingsSet.begin(); settingsIt != settingsSet.end(); ++settingsIt) {
        settingsAttr.addAttribute(graph.createAttributeString(*settingsIt, graphconstants::CONTEXT_RUL, rulHandler.getSettingValue(*rulIdIt, *settingsIt)));
      }

      const set<string>& calculated = rulHandler.getCalculatedForSet(*rulIdIt);
      AttributeComposite& calculatedAttr = dynamic_cast<AttributeComposite&>(metric.addAttribute(graph.createAttributeComposite(graphconstants::ATTR_RUL_CALCULATED, graphconstants::CONTEXT_RUL)));
      for (set<string>::const_iterator calcForIt = calculated.begin(); calcForIt != calculated.end(); ++calcForIt) {
        calculatedAttr.addAttribute(graph.createAttributeString(graphconstants::ATTR_RUL_CALCULATEDFOR, graphconstants::CONTEXT_RUL, *calcForIt));
      }
    }
  }
  rulIdList.clear();

  rulHandler.getGroupIdList(rulIdList);
  for(set<string>::const_iterator rulIdIt = rulIdList.begin(); rulIdIt != rulIdList.end(); ++rulIdIt) {
    set<string> members;
    rulHandler.getGroupMembers(*rulIdIt, members);
    for(set<string>::const_iterator memberIt = members.begin(); memberIt != members.end(); ++memberIt) {
      addEdgeOnce(graph, graph.findNode(*rulIdIt), graph.findNode(*memberIt), Edge::EdgeType(graphconstants::ETYPE_RUL_GROUPCONTAINS, Edge::edtDirectional), true);
    }
  }
}


void buildRuleItemToGraph(Graph& graph, const string& metricID, const string& toolID, const string& description, const string& displayName, bool isEnabled, const string& groupType, const string& helpText, bool isWarning, const map<string, string>& settings, const set<string>& calculated) {

  Node root = graph.findNode(graphconstants::UID_RUL_ROOT);
  if(root == Graph::invalidNode) {
    root = graph.createNode(graphconstants::UID_RUL_ROOT, graphconstants::NTYPE_ROOT);
  }  
  
  Node tool = graph.findNode(toolID);
  if (tool == Graph::invalidNode) {
    tool = graph.createNode(toolID, graphconstants::NTYPE_RUL_TOOL);
    graph.createDirectedEdge(root, tool, graphconstants::ETYPE_RUL_TREE, true);
  }

  Node metric = graph.findNode(metricID);
  if (metric == Graph::invalidNode) {
    metric = graph.createNode(metricID, graphconstants::NTYPE_RUL_METRIC);
  } else {
    return;
  }

  graph.createDirectedEdge(tool, metric, graphconstants::ETYPE_RUL_TREE, true);

  metric.addAttribute(graph.createAttributeString(graphconstants::ATTR_RUL_DESCRIPTION, graphconstants::CONTEXT_RUL, description));
  metric.addAttribute(graph.createAttributeString(graphconstants::ATTR_RUL_DISPLAYNAME, graphconstants::CONTEXT_RUL, displayName));
  metric.addAttribute(graph.createAttributeString(graphconstants::ATTR_RUL_ENABLED, graphconstants::CONTEXT_RUL, isEnabled?"true":"false"));
  metric.addAttribute(graph.createAttributeString(graphconstants::ATTR_RUL_GROUPTYPE, graphconstants::CONTEXT_RUL, groupType));
  metric.addAttribute(graph.createAttributeString(graphconstants::ATTR_RUL_HELPTEXT, graphconstants::CONTEXT_RUL, helpText));
  metric.addAttribute(graph.createAttributeString(graphconstants::ATTR_RUL_WARNING, graphconstants::CONTEXT_RUL, isWarning?"true":"false"));

  AttributeComposite& settingsAttr = dynamic_cast<AttributeComposite&>(metric.addAttribute(graph.createAttributeComposite(graphconstants::ATTR_RUL_SETTINGS, graphconstants::CONTEXT_RUL)));
  for(map<string, string>::const_iterator settingsIt = settings.begin(); settingsIt != settings.end(); ++settingsIt) {
    settingsAttr.addAttribute(graph.createAttributeString(settingsIt->first, graphconstants::CONTEXT_RUL, settingsIt->second));
  }

  AttributeComposite& calculatedAttr = dynamic_cast<AttributeComposite&>(metric.addAttribute(graph.createAttributeComposite(graphconstants::ATTR_RUL_CALCULATED, graphconstants::CONTEXT_RUL)));
  for (set<string>::const_iterator calcForIt = calculated.begin(); calcForIt != calculated.end(); ++calcForIt) {
    calculatedAttr.addAttribute(graph.createAttributeString(graphconstants::ATTR_RUL_CALCULATEDFOR, graphconstants::CONTEXT_RUL, *calcForIt));
  }
}


bool readRuleItemFromGraph(Graph& graph, const string& metricID, string& description, string& displayName, bool& isEnabled, string& groupType, string& helpText, bool& isWarning, map<string, string>& settings, set<string>& calculated) {
  Node metric = graph.findNode(metricID);
  if (metric == Graph::invalidNode)
    return false;
    
  Attribute::AttributeIterator attributeIt = metric.getAttributes();
  while (attributeIt.hasNext()) {
    Attribute& attr = attributeIt.next();
    const string& name = attr.getName();
    if (name == graphconstants::ATTR_RUL_DESCRIPTION)
      description = attr.getStringValue();
    else if (name == graphconstants::ATTR_RUL_DISPLAYNAME)
      displayName = attr.getStringValue();
    else if (name == graphconstants::ATTR_RUL_ENABLED)
      isEnabled = (attr.getStringValue() != "false");
    else if (name == graphconstants::ATTR_RUL_GROUPTYPE)
      groupType = attr.getStringValue();
    else if (name == graphconstants::ATTR_RUL_HELPTEXT)
      helpText = attr.getStringValue();
    else if (name == graphconstants::ATTR_RUL_WARNING)
      isWarning = (attr.getStringValue() != "false");
    else if (name == graphconstants::ATTR_RUL_SETTINGS) {
      if (attr.getType() != Attribute::atComposite)
        continue;
      Attribute::AttributeIterator settingsIt = dynamic_cast<AttributeComposite&>(attr).getAttributes();
      while (settingsIt.hasNext()) {
        Attribute& settingAttribute = settingsIt.next();
        settings[settingAttribute.getName()] = settingAttribute.getStringValue();
      }
    } else if (name == graphconstants::ATTR_RUL_CALCULATED) {
      if (attr.getType() != Attribute::atComposite)
        continue;

      Attribute::AttributeIterator calculatedIt = dynamic_cast<AttributeComposite&>(attr).getAttributes();
      while (calculatedIt.hasNext())
        calculated.insert(calculatedIt.next().getStringValue());
      
    }
  }
  return true;
}


} }
