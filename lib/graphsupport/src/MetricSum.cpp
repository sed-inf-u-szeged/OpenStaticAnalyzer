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

#include "../inc/MetricSum.h"
#include "../inc/Metric.h"
#include "../inc/RulBuilder.h"
#include "../inc/messages.h"
#include "../inc/GraphConstants.h"

#include <rul/inc/RulHandler.h>
#include <common/inc/StringSup.h>
#include <common/inc/WriteMessage.h>
#include <iostream>
#include <map>
#include <set>

using namespace columbus::graph;
using namespace common;
using namespace std;

namespace columbus { namespace graphsupport {
  
  list<Node> postOrderedNodes;
  set<Node> addedNodes;

  void nodeVisit(const Node& node, void* data) {
    // cout << node.getUID() << endl;
    set<Node>::iterator foundednode = addedNodes.find(node);
    if(foundednode == addedNodes.end()) {
      postOrderedNodes.push_back(node);
      addedNodes.insert(node);
    }
  }

  void edgeVisit(const Edge& edge, void* data) {
  }



  void topologicalShort(Graph& graph,Edge::EdgeType edgeType) {
  //  find start node
 
    Node::NodeSet root = graph.getRootByEdgeType(edgeType);

    Edge::EdgeTypeSet edgeTypeSet;


    switch(edgeType.getDirectionType()) {
      case Edge::edtBidirectional:
        edgeTypeSet.insert(edgeType);
        break;
      case Edge::edtDirectional:
        edgeTypeSet.insert(Edge::EdgeType(edgeType.getType(),Edge::edtReverse));
        break;
      case Edge::edtReverse:
        edgeTypeSet.insert(Edge::EdgeType(edgeType.getType(),Edge::edtDirectional));
        break;
    }

    for(Node::NodeSet::iterator it = root.begin(); it != root.end(); it++) {
      //cout << (*it).getUID();
      graph.traverseDepthFirstPostorder(*it,edgeTypeSet,nodeVisit,edgeVisit, NULL);
    }
   
  }
  
  void sumAttributes(Node& node, Graph& graph, const set<string>& metrics) {
    // sum warning attributes
    Attribute::AttributeIterator attributeIt = node.getAttributes();
    unordered_map<string, Attribute&> warningToMetricMap;
    list<string> warnings;

    while (attributeIt.hasNext()) {
      Attribute& attr = attributeIt.next();

      const string& attrName = attr.getName();
      if (!metrics.empty() && metrics.find(attrName) == metrics.end())
        continue;
        
      if ((attr.getType() == Attribute::atComposite) && (attr.getContext() == graphconstants::CONTEXT_WARNING))
        warnings.push_back(attrName);
      else if ((attr.getType() == Attribute::atInt) && (attr.getContext() == graphconstants::CONTEXT_METRIC)) {
        auto insertionResult = warningToMetricMap.insert(std::pair<string, Attribute&>(attrName, attr));

        // There should only be one Metric attribute so one cannot already exist for the warning
        if (!insertionResult.second)
          throw graph::GraphException(COLUMBUS_LOCATION, CMSG_EX_FOUND_MORE_METRIC_ATTRIBUTE(attrName, node.getUID()));
      }

    }

    for (string warning : warnings)
    {
      auto it = warningToMetricMap.find(warning);
      if (it == warningToMetricMap.end())
        warningToMetricMap.insert(std::pair<string, Attribute&>(warning, node.addAttribute(graph.createAttributeInt(warning, graphconstants::CONTEXT_METRIC, 1))));
      else
        ((AttributeInt&)(it->second)).incValue(1);
    }
  }

  void cumAttributes(Node& fromNode, Node& toNode, Graph& graph, const set<string>& metrics) {
    // cum warnings
    Attribute::AttributeIterator attributeIt = fromNode.getAttributes();

    while(attributeIt.hasNext()) {
      Attribute& attr = attributeIt.next();
      if( (attr.getType() != Attribute::atInt) && (attr.getType() != Attribute::atFloat) )
        continue;
      
      if(attr.getContext() != graphconstants::CONTEXT_METRIC)
        continue;

      const string& attrName = attr.getName();
      if (!metrics.empty() && metrics.find(attrName) == metrics.end())
        continue;
      
      Attribute::AttributeIterator cumAttrIt = toNode.findAttribute(attr.getType(),attrName, attr.getContext());

      if(!cumAttrIt.hasNext()) {
        toNode.addAttribute(attr);
      } else {
        Attribute& cumAttr =  cumAttrIt.next();
        if(cumAttrIt.hasNext())
          throw graph::GraphException( COLUMBUS_LOCATION, CMSG_EX_FOUND_MORE_METRIC_ATTRIBUTE( attrName, toNode.getUID()));
        if(cumAttr.getType() == Attribute::atInt && attr.getType() == Attribute::atInt) {
          (dynamic_cast<AttributeInt&>(cumAttr)).incValue( dynamic_cast<AttributeInt&>(attr).getValue());
        } else if(cumAttr.getType() == Attribute::atFloat && attr.getType() == Attribute::atFloat) {
          (dynamic_cast<AttributeFloat&>(cumAttr)).incValue( dynamic_cast<AttributeFloat&>(attr).getValue());
        } else {
          throw Exception( COLUMBUS_LOCATION, CMSG_EX_WRONG_ATTRIBUTE_TYPE);
        }
      }
    }
  }

  void cumSum(Graph& graph, const Edge::EdgeType& edgeType, bool sumWarnings, const set<string>& metrics, bool cumulateToSystemComponent) {
    postOrderedNodes.clear();
    addedNodes.clear();
    topologicalShort(graph,edgeType);

    Node systemComponentNode;

    if (cumulateToSystemComponent)
    {
      auto componentNodeIt = graph.findNodes(Node::NodeType(graphconstants::NTYPE_LIM_COMPONENT));
      while (componentNodeIt.hasNext())
      {
        string longName;
        Node nextNode = componentNodeIt.next();
        if (getNodeLongNameAttribute(nextNode, longName) && longName == "<System>")
        {
          systemComponentNode = nextNode;
          break;
        }
      }
    }




    for(list<Node>::iterator it = postOrderedNodes.begin(); it != postOrderedNodes.end(); it++) {
      Node node = (*it);
      
      // cout << node.getUID() << endl;
      Edge::EdgeIterator edgeIt = node.findOutEdges(edgeType);
      if(sumWarnings)
        sumAttributes(node, graph, metrics) ;

      if (edgeIt.hasNext() && (systemComponentNode != Graph::invalidNode))
      {
        cumAttributes(node, systemComponentNode, graph, metrics);
      }


      while(edgeIt.hasNext()) {
        Edge edge = edgeIt.next();
        Node toNode = edge.getToNode();
        cumAttributes(node,toNode, graph, metrics);
      }

    }
 
  }

  void createGroupMetrics(graph::Graph& graph, rul::RulHandler& rulHandler, const std::set<std::string>& metrics) {
    std::unordered_map<std::string, std::set<std::shared_ptr<rul::Tag>>> enabled_metrics_with_tags;
    const auto enabled_metrics_with_tags_emplacer = [&](const auto &rule_list) {
      for (const auto &rule_name : rule_list) {
        if (!rulHandler.getIsEnabled(rule_name)) { continue; }
        const auto &tags = rulHandler.getTags(rule_name);
        if (tags.empty()) { continue; }
        enabled_metrics_with_tags.try_emplace(rule_name, tags);
      }
    };

    if (metrics.empty()) {
      std::set<std::string> rule_list;
      rulHandler.getRuleIdList(rule_list);
      enabled_metrics_with_tags_emplacer(rule_list);
    } else {
      enabled_metrics_with_tags_emplacer(metrics);
    }

    auto node_it = graph.getNodes();
    while (node_it.hasNext()) {
      auto node = node_it.next();
      auto attr_it = node.getAttributes();

      while (attr_it.hasNext()) {
        const auto &attr = attr_it.next();
        if ((attr.getType() != Attribute::atInt && attr.getType() != Attribute::atFloat) ||
            attr.getContext() != graphconstants::CONTEXT_METRIC) {
          continue;
        }

        const auto &metric_tag_it = enabled_metrics_with_tags.find(attr.getName());
        if (metric_tag_it == enabled_metrics_with_tags.end()) { continue; }

        for (const auto &tag : metric_tag_it->second) {
          const auto summarize_tag = [&](const auto &tag_name) {
            const auto metric_value = [&]() -> float {
              if (attr.getType() == Attribute::atInt) {
                return static_cast<float>(dynamic_cast<const AttributeInt &>(attr).getValue());
              }
              return dynamic_cast<const AttributeFloat &>(attr).getValue();
            }();

            if (auto tag_metric_group_attr_it =
                    node.findAttribute(Attribute::atFloat, tag_name, graphconstants::CONTEXT_METRICGROUP);
                tag_metric_group_attr_it.hasNext()) {
              auto &metric_group_attr = dynamic_cast<AttributeFloat &>(tag_metric_group_attr_it.next());
              metric_group_attr.incValue(metric_value);
            } else {
              node.addAttribute(
                  graph.createAttributeFloat(tag_name, graphconstants::CONTEXT_METRICGROUP, metric_value));
            }
          };

          if (const auto &value = tag->get_value(); !value.empty()) {
            std::string tag_name = '/' + tag->get_kind();
            (tag_name += '/') += value;
            if (tag->get_value_summarized()) { summarize_tag(tag_name); }
            if (const auto &detail = tag->get_detail(); !detail.empty()) {
              (tag_name += '/') += detail;
              if (tag->get_detail_summarized()) { summarize_tag(tag_name); }
            }
          }
        }
      }
    }
  }

  static const int getPriorityNumberByName(const string& priority) {
    if(priority == "Blocker")
      return 0;
    else if(priority == "Critical")
      return 1;
    else if(priority == "Major")
      return 2;
    else if(priority == "Minor")
      return 3;
    else if (priority == "Info")
      return 4;

    throw columbus::Exception(COLUMBUS_LOCATION, CMSG_EX_INVALID_PRIORITY_VALUE(priority));
  }

  static const string getPriorityNameByNumber(int priority) {
    if(priority == 0)
      return "Blocker";
    else if(priority == 1)
      return "Critical";
    else if(priority == 2)
      return "Major";
    else if(priority == 3)
      return "Minor";
    else if (priority == 4)
      return "Info";

    throw columbus::Exception(COLUMBUS_LOCATION, CMSG_EX_INVALID_PRIORITY_VALUE(common::toString(priority)));
  }
  
  static const string getPriorityWarningName(int priority) {
    return "Warning" + getPriorityNameByNumber(priority);
  }

  
  void summarizeWarningMetricsByPriority(graph::Graph& graph, const bool buildRul, const set<string>& metrics) {

    map<string, int> priorities;
    
    // collecting the priorities of the warnings
    Node::NodeIterator nodeIt = graph.findNodes(Node::NodeType(graphconstants::NTYPE_RUL_METRIC)); 
    while (nodeIt.hasNext()) {
      Node rule = nodeIt.next();
      Attribute::AttributeIterator enabledId = rule.findAttributeByName(graphconstants::ATTR_RUL_ENABLED);
      if (enabledId.hasNext()) {
        Attribute& enabled = enabledId.next();
        
        if (enabled.getStringValue() == "false")
          continue;   // Only enabled warnings are taken into account
        
        Attribute::AttributeIterator settingsIt = rule.findAttributeByName(graphconstants::ATTR_RUL_SETTINGS);
        if (settingsIt.hasNext()) {
          Attribute& settings = settingsIt.next();
          if (settings.getType() == Attribute::atComposite) {
            Attribute::AttributeIterator priorityIt = ((AttributeComposite&)settings).findAttributeByName(graphconstants::ATTR_RUL_PRIORITY);
            if (priorityIt.hasNext()) {
              Attribute& priority = priorityIt.next();
              if (priority.getType() == Attribute::atString) {
                int pr = getPriorityNumberByName(((AttributeString&)priority).getValue());
                priorities.insert(make_pair(rule.getUID(), pr));
              } else {
                WriteMsg::write(WriteMsg::mlDDDebug, "Type of the priority attribute is not string so it is not used!\n");
              }
            }
          } else {
            WriteMsg::write(WriteMsg::mlDDDebug, "Type of the '%s' attribute is not composit so it is not used!\n", graphconstants::ATTR_RUL_SETTINGS.c_str());
          }
        }
      }
    }
    
    nodeIt = graph.getNodes();
    while (nodeIt.hasNext()) {
      Node node = nodeIt.next();

      // Check wheter it is a member of a logical or component tree
      bool found = false;
      Edge::EdgeIterator edgeIt = node.getOutEdges();
      while (edgeIt.hasNext()) {
        Edge edge = edgeIt.next(); 
        string edgeType = edge.getType().getType();
        if (edgeType == graphconstants::ETYPE_LIM_LOGICALTREE ||
            edgeType == graphconstants::ETYPE_LIM_COMPONENTTREE) 
        {
          found = true;
          break;
        }
      }

      if (found) {
        vector<int> prioritySum(5, 0);
        Attribute::AttributeIterator attributeIt = node.findAttributeByContext(graphconstants::CONTEXT_METRIC);
        while (attributeIt.hasNext()) {
          Attribute& metricAttribute = attributeIt.next();
          const string& name = metricAttribute.getName();
          map<string, int>::const_iterator priIt = priorities.find(name);
          if (priIt != priorities.end() && metricAttribute.getType() == Attribute::atInt) {
            if (metrics.empty() || metrics.find(name) != metrics.end())
              prioritySum[priIt->second] += ((AttributeInt&)metricAttribute).getValue();
          } else {
            WriteMsg::write(WriteMsg::mlDDDebug, "Priority for metric '%s' is not found or it is not an integer type metric!\n", name.c_str());
          }
        }

        for(int i=0; i<=4; ++i)
          incMetricInt(graph, node, getPriorityWarningName(i),  prioritySum[i]);
      }
    }

    if (buildRul) {
      static const auto tags = [](){
        std::set<rul::Tag> tags_;
        tags_.insert(rul::Tag("internal", "csv_column"));
        return tags_;
      }();

      for(int i=0; i<=4; ++i) {
          string priorityName = getPriorityNameByNumber(i);
          buildRuleItemToGraph(graph, getPriorityWarningName(i), "__AUTOMATIC__",
                               "Number of warnings with " + priorityName + " priority", 
                              priorityName + " Warnings",
                              true,
                              "false",
                              "Number of warnings with " + priorityName + " priority", 
                              true,
                              map<string, string>(),
                              set<string>(),
                              tags);
      }
    }
  }

   
  
}}
