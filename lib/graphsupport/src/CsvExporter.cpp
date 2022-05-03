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

#include "../inc/CsvExporter.h"
#include "../inc/Metric.h"
#include "../inc/RulBuilder.h"
#include "../inc/GraphConstants.h"
#include <common/inc/FileSup.h>
#include <io/inc/IO.h>
#include "../inc/messages.h"
#include <iostream>

using namespace columbus::io;
using namespace columbus::graph;
using namespace std;

namespace columbus { namespace graphsupport {

  static void exportImpactSetAll(graph::Graph& graph, const string& filename, graph::Edge::EdgeTypeSet& edgeTypes, const std::set<graph::Node>* const parentNodes) {
    CsvIO csvOut(filename, IOBase::omWrite);
    // write header information
    csvOut.writeColumn( CMSG_STAT_HEADER_NAME);
    csvOut.writeColumn( CMSG_STAT_HEADER_PATH);
    csvOut.writeColumn( CMSG_STAT_HEADER_LINE);
    csvOut.writeColumn( CMSG_STAT_HEADER_DESCRIPTION);
    csvOut.writeNewLine();
    Node::NodeIterator nodes = graph.getNodes();
    set<Node> impactedNodes;
    while(nodes.hasNext()) {
      Node node = nodes.next();
      Edge::EdgeIterator edges = node.findOutEdges(edgeTypes);
      while(edges.hasNext()) {
        Edge edge = edges.next();
        if( (parentNodes != NULL) && (parentNodes->find(edge.getFromNode()) == parentNodes->end()) ) {
          continue;
        }
        impactedNodes.insert(edge.getToNode());
      }
    }
    for(set<Node>::iterator it = impactedNodes.begin(); it != impactedNodes.end(); ++it) {
      string name = "", path = "";
      int line =0, col = 0, endLine = 0, endCol = 0;
      getNodeNameAttribute(*it, name);
      getPositionAttribute(*it, path, line, col, endLine, endCol);
      if(!name.empty()) {
        csvOut.writeColumn(name);
        csvOut.writeColumn(path);
        csvOut.writeColumn(line);
        csvOut.writeColumn( CMSG_STAT_HEADER_IMPACTED);
      }
      csvOut.writeNewLine();
    }
    csvOut.flush();
    csvOut.close();
  }

  void exportImpactSet(graph::Graph& graph, const string& filename, graph::Edge::EdgeTypeSet& edgeTypes, const std::set<graph::Node>& parentNodes) {
    exportImpactSetAll(graph, filename, edgeTypes, &parentNodes);
  }

  void exportImpactSet(graph::Graph& graph, const string& filename, graph::Edge::EdgeTypeSet& edgeTypes) {
    exportImpactSetAll(graph, filename, edgeTypes, NULL);
  }


  typedef set<string> StringSet;
  typedef map<string, string> StringMap;
  typedef vector<string> StringVector;
  typedef map<string, StringSet> StringStringSetMap;
  typedef map<string, StringVector> StringStringVectorMap;
  typedef map<string, StringStringSetMap> StringStringStringSetMap;

  static string csvName(const string& fname, const string& fext, const string& nodeType) {
    return fname + "-" + nodeType + fext;
  }


  static void writeMetricsHeader(const StringVector& metrics, const StringMap& idMap, io::CsvIO& csvHeader) {
    for (StringVector::const_iterator metricsIterator = metrics.begin(); metricsIterator != metrics.end(); ++metricsIterator)
    {
      const auto displayNameIt = idMap.find(*metricsIterator);
      if (displayNameIt != idMap.end())
        csvHeader.writeColumn(displayNameIt->second);
      else
        csvHeader.writeColumn(*metricsIterator);
    }
  }

  static void writeMetrics(const StringVector& nodeTypeMetricsVector, const Node& node, io::CsvIO& csvOut) {
    for (StringVector::const_iterator metricsIterator = nodeTypeMetricsVector.begin(); metricsIterator != nodeTypeMetricsVector.end(); ++metricsIterator) {
      Attribute::AttributeIterator attributesIt = node.findAttributeByName(*metricsIterator);
      if (!attributesIt.hasNext()) {
        csvOut.writeColumn("0");
        continue;
      }

      bool found = false;
      while (attributesIt.hasNext() && !found) {
        const Attribute& at = attributesIt.next();
        if (at.getContext() == graphconstants::CONTEXT_METRIC || at.getContext() == graphconstants::CONTEXT_METRICGROUP) {
          if (isINVALID(at)) 
            csvOut.writeColumn("");
          else {
            if (at.getType() == Attribute::atFloat) 
              csvOut.writeColumn(((AttributeFloat&)at).getValue());
            else
              csvOut.writeColumn(at.getStringValue());
          }
          found = true;
        }
      }

      if (!found)
        csvOut.writeColumn("0");
    }
  }

  static void writePositionColumns(const Node& node, io::CsvIO& csvOut, bool writeRealizationLevel = false) {
    string path;
    int line = 0, col = 0, endLine = 0, endCol = 0;
    bool realizationLevel = false, definition = false;
    getPositionAttribute(node, path, line, col, endLine, endCol, realizationLevel, definition);
    if (writeRealizationLevel) {
      if (realizationLevel) {
        if (definition)
          csvOut.writeColumn(graphconstants::ATTRVALUE_LIM_RELDEFINES);
        else
          csvOut.writeColumn(graphconstants::ATTRVALUE_LIM_RELDECLARES);
      } else
        csvOut.writeColumn("-");
    }
    csvOut.writeColumn(path);
    csvOut.writeColumn(line);
    csvOut.writeColumn(col);
    csvOut.writeColumn(endLine);
    csvOut.writeColumn(endCol);
  }


  static void writeComponents(const Node& node, io::CsvIO& csvOut) {
    string components;
    Edge::EdgeIterator componentIt = node.findOutEdges(Edge::EdgeType(graphconstants::ETYPE_LIM_COMPONENT, Edge::edtDirectional));
    while (componentIt.hasNext()) {
      Edge componentEdge = componentIt.next();
      components.append(componentEdge.getToNode().getUID());
      if (componentIt.hasNext())
        components.append(", ");
    }
    csvOut.writeColumn(components);
  }


  static const Node getParent(const Node& node, const Edge::EdgeType& edgeType) {
    Edge::EdgeIterator componentIt = node.findOutEdges(edgeType);
    if (componentIt.hasNext()) {
      return componentIt.next().getToNode();
    }
    return Graph::invalidNode;
  }

  static void writeParent(const Node& node, io::CsvIO& csvOut, const Edge::EdgeType& edgeType) {
    Node parentNode = getParent(node, edgeType);
    if (parentNode != Graph::invalidNode)
      csvOut.writeColumn(parentNode.getUID());
    else
      csvOut.writeColumn("");
  }

  static void setCsvStyle(io::CsvIO& csv, char separator, char dmark) {
    csv.setSeparator(separator);
    csv.setDecimalMark(dmark);
    csv.setQuotationMode(true);
  }

  static const string IDColumn = "ID";
  static const string ParentColumn = "Parent";

  void exportReadableMetricsCSV(graph::Graph& graph, const string& filename, char separator, char dmark) {
    string fname, fext;
    common::splitExt(filename, fname, fext);

    // In the first round we collect all the metric attributes for all kind of nodes.
    StringStringSetMap nodeTypeMetricsMap;
    StringSet grouppedMetrics;
    StringSet warningMetricsWithoutCalculatedFor;
    StringStringStringSetMap orderMap; // tool = > group => metrics set    
    StringSet warningMetricGroupsWithCollectedCalculatedFor;  // These are those warning groups which calculatedFor properties are collected from their group members
    StringMap groupIDDisplayNameMap; // group ID => display name
    
    Node::NodeIterator allNodes = graph.findNodes(graphconstants::NTYPE_RUL_METRIC);
    while (allNodes.hasNext()) {
      Node node = allNodes.next();

      // Collect all the group member metrics
      const Attribute& groupTypeAttr = getNodeAttribute(node, Attribute::atString, graphconstants::ATTR_RUL_GROUPTYPE, graphconstants::CONTEXT_RUL);
      if (groupTypeAttr != Graph::invalidAttribute) {
        if (groupTypeAttr.getStringValue().compare("summarized") == 0) {
          Edge::EdgeIterator groupMembersIt = node.findOutEdges(Edge::EdgeType(graphconstants::ETYPE_RUL_GROUPCONTAINS, Edge::edtDirectional));
          while (groupMembersIt.hasNext()) {
            Edge edge = groupMembersIt.next();
            grouppedMetrics.insert(edge.getToNode().getUID());
          }

          auto displayNameIt = node.findAttributeByName(graphconstants::ATTR_RUL_DISPLAYNAME);
          if (displayNameIt.hasNext())
            groupIDDisplayNameMap[node.getUID()] = displayNameIt.next().getStringValue();
        } 

        // store the group state and the tool for reordering
        Edge::EdgeIterator toolIt = node.findOutEdges(Edge::EdgeType(graphconstants::ETYPE_RUL_TREE, Edge::edtReverse));
        if (toolIt.hasNext()) {
          const string& toolID = toolIt.next().getToNode().getUID();
          Edge::EdgeIterator groupIt = node.findOutEdges(Edge::EdgeType(graphconstants::ETYPE_RUL_GROUPCONTAINS, Edge::edtReverse));
          if (groupIt.hasNext()) {
            orderMap[toolID][groupIt.next().getToNode().getUID()].insert(node.getUID());
          } else {   // Not group member. Add to the "Nongroupped" group.
            orderMap[toolID]["-"].insert(node.getUID());
          }
        } else {
          // The metric does not belong to any tool!!!! RUL error.
          // TODO Write warning
        }

      }

      // Check if it is enabled
      const AttributeString& enabledAttr = (const AttributeString&)getNodeAttribute(node, Attribute::atString, graphconstants::ATTR_RUL_ENABLED, graphconstants::CONTEXT_RUL);
      if (enabledAttr != Graph::invalidAttribute && enabledAttr.getStringValue() == "true") {

        
        // collect the calculatedFor entries for the groups from the warning items
        Edge::EdgeIterator groupIt = node.findOutEdges(Edge::EdgeType(graphconstants::ETYPE_RUL_GROUPCONTAINS, Edge::edtReverse));
        while (groupIt.hasNext()) {
          Node groupNode = groupIt.next().getToNode();
          const string& groupID = groupNode.getUID();
          const Attribute& groupTypeAttr = getNodeAttribute(groupNode, Attribute::atString, graphconstants::ATTR_RUL_GROUPTYPE, graphconstants::CONTEXT_RUL);
          if (groupTypeAttr.getStringValue() != "summarized")
            continue;

          AttributeComposite& calculatedAttr = (AttributeComposite&)getNodeAttribute(node, Attribute::atComposite, graphconstants::ATTR_RUL_CALCULATED, graphconstants::CONTEXT_RUL);
          if (calculatedAttr!= Graph::invalidAttribute) {
            Attribute::AttributeIterator calculatedForAttrIt = calculatedAttr.findAttributeByName(graphconstants::ATTR_RUL_CALCULATEDFOR);
            while (calculatedForAttrIt.hasNext()) {
              nodeTypeMetricsMap[calculatedForAttrIt.next().getStringValue()].insert(groupID);
              warningMetricGroupsWithCollectedCalculatedFor.insert(groupID);
            }
          }
        }
        
        bool hasCalculatedFor = false;
        // Collect the node types for which it is calculated
        AttributeComposite& calculatedAttr = (AttributeComposite&)getNodeAttribute(node, Attribute::atComposite, graphconstants::ATTR_RUL_CALCULATED, graphconstants::CONTEXT_RUL);
        if (calculatedAttr!= Graph::invalidAttribute) {
          Attribute::AttributeIterator calculatedForAttrIt = calculatedAttr.findAttributeByName(graphconstants::ATTR_RUL_CALCULATEDFOR);
          while (calculatedForAttrIt.hasNext()) {
            nodeTypeMetricsMap[calculatedForAttrIt.next().getStringValue()].insert(node.getUID());
            hasCalculatedFor = true;
          }
        }
        
        // Collect all the warning metrics without calculatedFor 
        const AttributeString& warningAttr = (const AttributeString&)getNodeAttribute(node, Attribute::atString, graphconstants::ATTR_RUL_WARNING, graphconstants::CONTEXT_RUL);
        if (warningAttr != Graph::invalidAttribute && warningAttr.getStringValue() == "true") {
          if (!hasCalculatedFor)
            warningMetricsWithoutCalculatedFor.insert(node.getUID());
        }
      }
    }

    // Remove those metrics from the warningMetricsWithoutCalculatedFor container which has collected calculatedFor entries
    for (StringSet::const_iterator groupIt = warningMetricGroupsWithCollectedCalculatedFor.begin(); groupIt != warningMetricGroupsWithCollectedCalculatedFor.end(); ++groupIt) {
      warningMetricsWithoutCalculatedFor.erase(*groupIt);
    }

    // Create node types for the missing ones and add all the warning metrics to all but the clone class and clone instance types
    string asg = graph.getHeaderInfo(graphconstants::HEADER_ASG_KEY);
    if (asg == graphconstants::HEADER_ASG_VALUE_JAVA) {
      // inserting empty sets if these types are not exists
      nodeTypeMetricsMap[graphconstants::NTYPE_LIM_CLASS].insert(warningMetricsWithoutCalculatedFor.begin(), warningMetricsWithoutCalculatedFor.end());
      nodeTypeMetricsMap[graphconstants::NTYPE_LIM_ENUM].insert(warningMetricsWithoutCalculatedFor.begin(), warningMetricsWithoutCalculatedFor.end());
      nodeTypeMetricsMap[graphconstants::NTYPE_LIM_INTERFACE].insert(warningMetricsWithoutCalculatedFor.begin(), warningMetricsWithoutCalculatedFor.end());
      nodeTypeMetricsMap[graphconstants::NTYPE_LIM_ANNOTATION].insert(warningMetricsWithoutCalculatedFor.begin(), warningMetricsWithoutCalculatedFor.end());
      nodeTypeMetricsMap[graphconstants::NTYPE_LIM_METHOD].insert(warningMetricsWithoutCalculatedFor.begin(), warningMetricsWithoutCalculatedFor.end());
      nodeTypeMetricsMap[graphconstants::NTYPE_LIM_ATTRIBUTE].insert(warningMetricsWithoutCalculatedFor.begin(), warningMetricsWithoutCalculatedFor.end());
      nodeTypeMetricsMap[graphconstants::NTYPE_LIM_COMPONENT].insert(warningMetricsWithoutCalculatedFor.begin(), warningMetricsWithoutCalculatedFor.end());
      nodeTypeMetricsMap[graphconstants::NTYPE_LIM_PACKAGE].insert(warningMetricsWithoutCalculatedFor.begin(), warningMetricsWithoutCalculatedFor.end());
      nodeTypeMetricsMap[graphconstants::NTYPE_LIM_FILE];
      nodeTypeMetricsMap[graphconstants::NTYPE_LIM_FOLDER];
      nodeTypeMetricsMap[graphconstants::NTYPE_DCF_CLONECLASS];
      nodeTypeMetricsMap[graphconstants::NTYPE_DCF_CLONEINSTANCE];

    } else if (asg == graphconstants::HEADER_ASG_VALUE_CPP) {
      nodeTypeMetricsMap[graphconstants::NTYPE_LIM_CLASS].insert(warningMetricsWithoutCalculatedFor.begin(), warningMetricsWithoutCalculatedFor.end());
      nodeTypeMetricsMap[graphconstants::NTYPE_LIM_ENUM].insert(warningMetricsWithoutCalculatedFor.begin(), warningMetricsWithoutCalculatedFor.end());
      nodeTypeMetricsMap[graphconstants::NTYPE_LIM_INTERFACE].insert(warningMetricsWithoutCalculatedFor.begin(), warningMetricsWithoutCalculatedFor.end());
      nodeTypeMetricsMap[graphconstants::NTYPE_LIM_UNION].insert(warningMetricsWithoutCalculatedFor.begin(), warningMetricsWithoutCalculatedFor.end());
      nodeTypeMetricsMap[graphconstants::NTYPE_LIM_STRUCTURE].insert(warningMetricsWithoutCalculatedFor.begin(), warningMetricsWithoutCalculatedFor.end());
      nodeTypeMetricsMap[graphconstants::NTYPE_LIM_METHOD].insert(warningMetricsWithoutCalculatedFor.begin(), warningMetricsWithoutCalculatedFor.end());
      nodeTypeMetricsMap[graphconstants::NTYPE_LIM_FUNCTION].insert(warningMetricsWithoutCalculatedFor.begin(), warningMetricsWithoutCalculatedFor.end());
      nodeTypeMetricsMap[graphconstants::NTYPE_LIM_ATTRIBUTE].insert(warningMetricsWithoutCalculatedFor.begin(), warningMetricsWithoutCalculatedFor.end());
      nodeTypeMetricsMap[graphconstants::NTYPE_LIM_COMPONENT].insert(warningMetricsWithoutCalculatedFor.begin(), warningMetricsWithoutCalculatedFor.end());
      nodeTypeMetricsMap[graphconstants::NTYPE_LIM_NAMESPACE].insert(warningMetricsWithoutCalculatedFor.begin(), warningMetricsWithoutCalculatedFor.end());
      nodeTypeMetricsMap[graphconstants::NTYPE_LIM_FILE];
      nodeTypeMetricsMap[graphconstants::NTYPE_LIM_FOLDER];
      nodeTypeMetricsMap[graphconstants::NTYPE_DCF_CLONECLASS];
      nodeTypeMetricsMap[graphconstants::NTYPE_DCF_CLONEINSTANCE];

    } else if (asg == graphconstants::HEADER_ASG_VALUE_C) { 
      nodeTypeMetricsMap[graphconstants::NTYPE_LIM_ENUM].insert(warningMetricsWithoutCalculatedFor.begin(), warningMetricsWithoutCalculatedFor.end());
      nodeTypeMetricsMap[graphconstants::NTYPE_LIM_STRUCTURE].insert(warningMetricsWithoutCalculatedFor.begin(), warningMetricsWithoutCalculatedFor.end());
      nodeTypeMetricsMap[graphconstants::NTYPE_LIM_UNION].insert(warningMetricsWithoutCalculatedFor.begin(), warningMetricsWithoutCalculatedFor.end());
      nodeTypeMetricsMap[graphconstants::NTYPE_LIM_FUNCTION].insert(warningMetricsWithoutCalculatedFor.begin(), warningMetricsWithoutCalculatedFor.end());
      nodeTypeMetricsMap[graphconstants::NTYPE_LIM_ATTRIBUTE].insert(warningMetricsWithoutCalculatedFor.begin(), warningMetricsWithoutCalculatedFor.end());
      nodeTypeMetricsMap[graphconstants::NTYPE_LIM_COMPONENT].insert(warningMetricsWithoutCalculatedFor.begin(), warningMetricsWithoutCalculatedFor.end());
      nodeTypeMetricsMap[graphconstants::NTYPE_LIM_NAMESPACE].insert(warningMetricsWithoutCalculatedFor.begin(), warningMetricsWithoutCalculatedFor.end());
      nodeTypeMetricsMap[graphconstants::NTYPE_LIM_FILE];
      nodeTypeMetricsMap[graphconstants::NTYPE_LIM_FOLDER];
      nodeTypeMetricsMap[graphconstants::NTYPE_DCF_CLONECLASS];
      nodeTypeMetricsMap[graphconstants::NTYPE_DCF_CLONEINSTANCE];

    } else if (asg == graphconstants::HEADER_ASG_VALUE_RPG) {
      nodeTypeMetricsMap[graphconstants::NTYPE_RPG_SYSTEM].insert(warningMetricsWithoutCalculatedFor.begin(), warningMetricsWithoutCalculatedFor.end());
      nodeTypeMetricsMap[graphconstants::NTYPE_RPG_PROGRAM].insert(warningMetricsWithoutCalculatedFor.begin(), warningMetricsWithoutCalculatedFor.end());
      nodeTypeMetricsMap[graphconstants::NTYPE_RPG_PROCEDURE].insert(warningMetricsWithoutCalculatedFor.begin(), warningMetricsWithoutCalculatedFor.end());
      nodeTypeMetricsMap[graphconstants::NTYPE_RPG_SUBROUTINE].insert(warningMetricsWithoutCalculatedFor.begin(), warningMetricsWithoutCalculatedFor.end());
      nodeTypeMetricsMap[graphconstants::NTYPE_LIM_COMPONENT].insert(warningMetricsWithoutCalculatedFor.begin(), warningMetricsWithoutCalculatedFor.end());
      nodeTypeMetricsMap[graphconstants::NTYPE_DCF_CLONECLASS];
      nodeTypeMetricsMap[graphconstants::NTYPE_DCF_CLONEINSTANCE];

    } else if (asg == graphconstants::HEADER_ASG_VALUE_PYTHON) {
      nodeTypeMetricsMap[graphconstants::NTYPE_LIM_CLASS].insert(warningMetricsWithoutCalculatedFor.begin(), warningMetricsWithoutCalculatedFor.end());
      nodeTypeMetricsMap[graphconstants::NTYPE_LIM_METHOD].insert(warningMetricsWithoutCalculatedFor.begin(), warningMetricsWithoutCalculatedFor.end());
      nodeTypeMetricsMap[graphconstants::NTYPE_LIM_FUNCTION].insert(warningMetricsWithoutCalculatedFor.begin(), warningMetricsWithoutCalculatedFor.end());
      nodeTypeMetricsMap[graphconstants::NTYPE_LIM_ATTRIBUTE].insert(warningMetricsWithoutCalculatedFor.begin(), warningMetricsWithoutCalculatedFor.end());
      nodeTypeMetricsMap[graphconstants::NTYPE_LIM_COMPONENT].insert(warningMetricsWithoutCalculatedFor.begin(), warningMetricsWithoutCalculatedFor.end());
      nodeTypeMetricsMap[graphconstants::NTYPE_LIM_PACKAGE].insert(warningMetricsWithoutCalculatedFor.begin(), warningMetricsWithoutCalculatedFor.end());
      nodeTypeMetricsMap[graphconstants::NTYPE_LIM_MODULE].insert(warningMetricsWithoutCalculatedFor.begin(), warningMetricsWithoutCalculatedFor.end());
      nodeTypeMetricsMap[graphconstants::NTYPE_LIM_FILE];
      nodeTypeMetricsMap[graphconstants::NTYPE_LIM_FOLDER];
      nodeTypeMetricsMap[graphconstants::NTYPE_DCF_CLONECLASS];
      nodeTypeMetricsMap[graphconstants::NTYPE_DCF_CLONEINSTANCE];
    
    } else if (asg == graphconstants::HEADER_ASG_VALUE_CSHARP) {
      nodeTypeMetricsMap[graphconstants::NTYPE_LIM_CLASS].insert(warningMetricsWithoutCalculatedFor.begin(), warningMetricsWithoutCalculatedFor.end());
      nodeTypeMetricsMap[graphconstants::NTYPE_LIM_ENUM].insert(warningMetricsWithoutCalculatedFor.begin(), warningMetricsWithoutCalculatedFor.end());
      nodeTypeMetricsMap[graphconstants::NTYPE_LIM_INTERFACE].insert(warningMetricsWithoutCalculatedFor.begin(), warningMetricsWithoutCalculatedFor.end());
      nodeTypeMetricsMap[graphconstants::NTYPE_LIM_STRUCTURE].insert(warningMetricsWithoutCalculatedFor.begin(), warningMetricsWithoutCalculatedFor.end());
      nodeTypeMetricsMap[graphconstants::NTYPE_LIM_DELEGATE].insert(warningMetricsWithoutCalculatedFor.begin(), warningMetricsWithoutCalculatedFor.end());
      nodeTypeMetricsMap[graphconstants::NTYPE_LIM_METHOD].insert(warningMetricsWithoutCalculatedFor.begin(), warningMetricsWithoutCalculatedFor.end());
      nodeTypeMetricsMap[graphconstants::NTYPE_LIM_ATTRIBUTE].insert(warningMetricsWithoutCalculatedFor.begin(), warningMetricsWithoutCalculatedFor.end());
      nodeTypeMetricsMap[graphconstants::NTYPE_LIM_COMPONENT].insert(warningMetricsWithoutCalculatedFor.begin(), warningMetricsWithoutCalculatedFor.end());
      nodeTypeMetricsMap[graphconstants::NTYPE_LIM_NAMESPACE].insert(warningMetricsWithoutCalculatedFor.begin(), warningMetricsWithoutCalculatedFor.end());
      nodeTypeMetricsMap[graphconstants::NTYPE_LIM_FILE];
      nodeTypeMetricsMap[graphconstants::NTYPE_LIM_FOLDER];
      nodeTypeMetricsMap[graphconstants::NTYPE_DCF_CLONECLASS];
      nodeTypeMetricsMap[graphconstants::NTYPE_DCF_CLONEINSTANCE];

    } else if (asg == graphconstants::HEADER_ASG_VALUE_JAVASCRIPT){
      nodeTypeMetricsMap[graphconstants::NTYPE_LIM_CLASS].insert(warningMetricsWithoutCalculatedFor.begin(), warningMetricsWithoutCalculatedFor.end());
      nodeTypeMetricsMap[graphconstants::NTYPE_LIM_METHOD].insert(warningMetricsWithoutCalculatedFor.begin(), warningMetricsWithoutCalculatedFor.end());
      nodeTypeMetricsMap[graphconstants::NTYPE_LIM_FUNCTION].insert(warningMetricsWithoutCalculatedFor.begin(), warningMetricsWithoutCalculatedFor.end());
      nodeTypeMetricsMap[graphconstants::NTYPE_LIM_ATTRIBUTE].insert(warningMetricsWithoutCalculatedFor.begin(), warningMetricsWithoutCalculatedFor.end());
      nodeTypeMetricsMap[graphconstants::NTYPE_LIM_COMPONENT].insert(warningMetricsWithoutCalculatedFor.begin(), warningMetricsWithoutCalculatedFor.end());
      nodeTypeMetricsMap[graphconstants::NTYPE_LIM_PACKAGE].insert(warningMetricsWithoutCalculatedFor.begin(), warningMetricsWithoutCalculatedFor.end());

      nodeTypeMetricsMap[graphconstants::NTYPE_LIM_FILE];
      nodeTypeMetricsMap[graphconstants::NTYPE_LIM_FOLDER];
      nodeTypeMetricsMap[graphconstants::NTYPE_DCF_CLONECLASS];
      nodeTypeMetricsMap[graphconstants::NTYPE_DCF_CLONEINSTANCE];
    }
    else {
      throw Exception(COLUMBUS_LOCATION, CMSG_EX_UNHANDLED_ASG_TYPE(asg));
    }
    
    // Remove all warning metrics, which belongs to a group.
    for (StringStringSetMap::iterator nodeTypeIterator = nodeTypeMetricsMap.begin(); nodeTypeIterator != nodeTypeMetricsMap.end(); ++nodeTypeIterator) {
      StringSet notGrouppedMetrics;
      // Calculate the difference between the collected and groupped metrics.
      set_difference(nodeTypeIterator->second.begin(), nodeTypeIterator->second.end(), 
        grouppedMetrics.begin(), grouppedMetrics.end(), 
        inserter(notGrouppedMetrics, notGrouppedMetrics.end()));

      nodeTypeIterator->second = notGrouppedMetrics;  // replace the collected with the difference
    }


    StringStringVectorMap reorderedMetricsMap;

    // Reorder the metrics by the tools and groups.  Not the most effective but due to the small number of elements the simplier code is better.
    for (StringStringSetMap::iterator nodeTypeIterator = nodeTypeMetricsMap.begin(); nodeTypeIterator != nodeTypeMetricsMap.end(); ++nodeTypeIterator) {
      reorderedMetricsMap[nodeTypeIterator->first];
      for (StringStringStringSetMap::const_iterator toolIt = orderMap.begin(); toolIt != orderMap.end(); ++toolIt) {
        for (StringStringSetMap::const_iterator groupIt = toolIt->second.begin(); groupIt != toolIt->second.end(); ++groupIt) {
          for (StringSet::const_iterator metricIt = groupIt->second.begin(); metricIt != groupIt->second.end(); ++metricIt) {
            if (nodeTypeIterator->second.find(*metricIt) != nodeTypeIterator->second.end())
              reorderedMetricsMap[nodeTypeIterator->first].push_back(*metricIt);
          }
        }
      }
    } 

    // Create the csv file headers
    for (StringStringVectorMap::iterator nodeTypeIterator = reorderedMetricsMap.begin(); nodeTypeIterator != reorderedMetricsMap.end(); ++nodeTypeIterator) {
      if (nodeTypeIterator->first == graphconstants::NTYPE_LIM_CLASS ||
        nodeTypeIterator->first == graphconstants::NTYPE_LIM_STRUCTURE ||
        nodeTypeIterator->first == graphconstants::NTYPE_LIM_DELEGATE ||
        nodeTypeIterator->first == graphconstants::NTYPE_LIM_UNION ||
        nodeTypeIterator->first == graphconstants::NTYPE_LIM_ENUM ||
        nodeTypeIterator->first == graphconstants::NTYPE_LIM_INTERFACE ||
        nodeTypeIterator->first == graphconstants::NTYPE_LIM_ANNOTATION ||
        nodeTypeIterator->first == graphconstants::NTYPE_LIM_METHOD ||
        nodeTypeIterator->first == graphconstants::NTYPE_LIM_FUNCTION ||
        nodeTypeIterator->first == graphconstants::NTYPE_LIM_ATTRIBUTE ||
        nodeTypeIterator->first == graphconstants::NTYPE_RPG_PROGRAM ||
        nodeTypeIterator->first == graphconstants::NTYPE_RPG_MODULE ||
        nodeTypeIterator->first == graphconstants::NTYPE_RPG_PROCEDURE ||
        nodeTypeIterator->first == graphconstants::NTYPE_RPG_SUBROUTINE ||
        nodeTypeIterator->first == graphconstants::NTYPE_LIM_MODULE)
      {
        io::CsvIO csvHeader(csvName(fname, fext, nodeTypeIterator->first), io::IOBase::omWrite);
        setCsvStyle(csvHeader, separator, dmark);
        csvHeader.writeColumn(IDColumn);
        csvHeader.writeColumn(graphconstants::ATTR_NAME);
        csvHeader.writeColumn(graphconstants::ATTR_LONGNAME);
        csvHeader.writeColumn(ParentColumn);
        csvHeader.writeColumn(graphconstants::NTYPE_LIM_COMPONENT);

        if (asg == graphconstants::HEADER_ASG_VALUE_CPP) {
          csvHeader.writeColumn(graphconstants::ATTR_REALIZATIONLEVEL);
        }
       
        csvHeader.writeColumn(graphconstants::ATTR_PATH);
        csvHeader.writeColumn(graphconstants::ATTR_LINE);
        csvHeader.writeColumn(graphconstants::ATTR_COLUMN);
        csvHeader.writeColumn(graphconstants::ATTR_ENDLINE);
        csvHeader.writeColumn(graphconstants::ATTR_ENDCOLUMN);
       
        writeMetricsHeader(nodeTypeIterator->second, groupIDDisplayNameMap, csvHeader);
        csvHeader.writeNewLine();
        csvHeader.close();

      } else if (nodeTypeIterator->first == graphconstants::NTYPE_DCF_CLONECLASS) {
        io::CsvIO csvHeader(csvName(fname, fext, nodeTypeIterator->first), io::IOBase::omWrite);
        setCsvStyle(csvHeader, separator, dmark);
        csvHeader.writeColumn(IDColumn);
        csvHeader.writeColumn(graphconstants::ATTR_NAME);
        csvHeader.writeColumn(graphconstants::NTYPE_LIM_COMPONENT);
        writeMetricsHeader(nodeTypeIterator->second, groupIDDisplayNameMap, csvHeader);
        csvHeader.writeNewLine();
        csvHeader.close();

      } else if (nodeTypeIterator->first == graphconstants::NTYPE_DCF_CLONEINSTANCE) {
        io::CsvIO csvHeader(csvName(fname, fext, nodeTypeIterator->first), io::IOBase::omWrite);
        setCsvStyle(csvHeader, separator, dmark);
        csvHeader.writeColumn(IDColumn);
        csvHeader.writeColumn(graphconstants::ATTR_NAME);
        csvHeader.writeColumn(ParentColumn);
        csvHeader.writeColumn(graphconstants::NTYPE_LIM_COMPONENT);

        csvHeader.writeColumn(graphconstants::ATTR_PATH);
        csvHeader.writeColumn(graphconstants::ATTR_LINE);
        csvHeader.writeColumn(graphconstants::ATTR_COLUMN);
        csvHeader.writeColumn(graphconstants::ATTR_ENDLINE);
        csvHeader.writeColumn(graphconstants::ATTR_ENDCOLUMN);

        writeMetricsHeader(nodeTypeIterator->second, groupIDDisplayNameMap, csvHeader);
        csvHeader.writeNewLine();
        csvHeader.close();

      } else if (nodeTypeIterator->first == graphconstants::NTYPE_LIM_COMPONENT) {
        io::CsvIO csvHeader(csvName(fname, fext, nodeTypeIterator->first), io::IOBase::omWrite);
        setCsvStyle(csvHeader, separator, dmark);
        csvHeader.writeColumn(IDColumn);
        csvHeader.writeColumn(graphconstants::ATTR_NAME);
        csvHeader.writeColumn(graphconstants::ATTR_LONGNAME);
        writeMetricsHeader(nodeTypeIterator->second, groupIDDisplayNameMap, csvHeader);
        csvHeader.writeNewLine();
        csvHeader.close();

      } else if (nodeTypeIterator->first == graphconstants::NTYPE_LIM_PACKAGE ||
        nodeTypeIterator->first == graphconstants::NTYPE_RPG_SYSTEM ||
        nodeTypeIterator->first == graphconstants::NTYPE_LIM_NAMESPACE)
      {
        io::CsvIO csvHeader(csvName(fname, fext, nodeTypeIterator->first), io::IOBase::omWrite);
        setCsvStyle(csvHeader, separator, dmark);
        csvHeader.writeColumn(IDColumn);
        csvHeader.writeColumn(graphconstants::ATTR_NAME);
        csvHeader.writeColumn(graphconstants::ATTR_LONGNAME);
        csvHeader.writeColumn(ParentColumn);
        csvHeader.writeColumn(graphconstants::NTYPE_LIM_COMPONENT);
        writeMetricsHeader(nodeTypeIterator->second, groupIDDisplayNameMap, csvHeader);
        csvHeader.writeNewLine();
        csvHeader.close();
      } else if (nodeTypeIterator->first == graphconstants::NTYPE_LIM_FILE ||
        nodeTypeIterator->first == graphconstants::NTYPE_LIM_FOLDER)
      {
        io::CsvIO csvHeader(csvName(fname, fext, nodeTypeIterator->first), io::IOBase::omWrite);
        setCsvStyle(csvHeader, separator, dmark);
        csvHeader.writeColumn(IDColumn);
        csvHeader.writeColumn(graphconstants::ATTR_NAME);
        csvHeader.writeColumn(graphconstants::ATTR_LONGNAME);
        csvHeader.writeColumn(ParentColumn);
        writeMetricsHeader(nodeTypeIterator->second, groupIDDisplayNameMap, csvHeader);
        csvHeader.writeNewLine();
        csvHeader.close();
      }
    }

    // Write out the metric values
    allNodes = graph.getNodes();
    while (allNodes.hasNext()) {
      Node node = allNodes.next();
      string nodeType = node.getType().getType();
      if (nodeType == graphconstants::NTYPE_LIM_CLASS ||
        nodeType == graphconstants::NTYPE_LIM_STRUCTURE ||
        nodeType == graphconstants::NTYPE_LIM_DELEGATE ||
        nodeType == graphconstants::NTYPE_LIM_UNION ||
        nodeType == graphconstants::NTYPE_LIM_ENUM ||
        nodeType == graphconstants::NTYPE_LIM_INTERFACE ||
        nodeType == graphconstants::NTYPE_LIM_ANNOTATION ||
        nodeType == graphconstants::NTYPE_LIM_METHOD ||
        nodeType == graphconstants::NTYPE_LIM_FUNCTION ||
        nodeType == graphconstants::NTYPE_LIM_ATTRIBUTE ||
        nodeType == graphconstants::NTYPE_RPG_PROGRAM ||
        nodeType == graphconstants::NTYPE_RPG_MODULE ||
        nodeType == graphconstants::NTYPE_RPG_PROCEDURE ||
        nodeType == graphconstants::NTYPE_RPG_SUBROUTINE ||
        nodeType == graphconstants::NTYPE_LIM_MODULE)
      {
        io::CsvIO csvOut(csvName(fname, fext, nodeType), io::IOBase::omAppend);
        setCsvStyle(csvOut, separator, dmark);
        csvOut.writeColumn(node.getUID());
        string name;
        getNodeNameAttribute(node, name);
        csvOut.writeColumn(name);

        getNodeLongNameAttribute(node, name);
        csvOut.writeColumn(name);

        writeParent(node, csvOut, Edge::EdgeType(graphconstants::ETYPE_LIM_LOGICALTREE, Edge::edtReverse));

        string asg = graph.getHeaderInfo(graphconstants::HEADER_ASG_KEY);
        
        writeComponents(node, csvOut);

        writePositionColumns(node, csvOut, asg == graphconstants::HEADER_ASG_VALUE_CPP);
        writeMetrics(reorderedMetricsMap[nodeType], node, csvOut);
        csvOut.writeNewLine();
        csvOut.close();

      } else if (nodeType == graphconstants::NTYPE_DCF_CLONECLASS) {
        const Attribute& cloneSmellAttr = getNodeAttribute(node, Attribute::atString, graphconstants::ATTR_DCF_CLONESMELLTYPE, graphconstants::CONTEXT_ATTRIBUTE);
        if (cloneSmellAttr.getStringValue() != "cstDisappearing") {
          io::CsvIO csvOut(csvName(fname, fext, nodeType), io::IOBase::omAppend);
          setCsvStyle(csvOut, separator, dmark);
          csvOut.writeColumn(node.getUID());
          string name;
          getNodeNameAttribute(node, name);
          csvOut.writeColumn(name);
          writeComponents(node, csvOut);
          writeMetrics(reorderedMetricsMap[nodeType], node, csvOut);
          csvOut.writeNewLine();
          csvOut.close();
        }
      } else if (nodeType == graphconstants::NTYPE_DCF_CLONEINSTANCE) {
        const Attribute& cloneSmellAttr = getNodeAttribute(node, Attribute::atString, graphconstants::ATTR_DCF_CLONESMELLTYPE, graphconstants::CONTEXT_ATTRIBUTE);
        bool fakeInstance = cloneSmellAttr.getStringValue() == "cstDisappearing";
        if (!fakeInstance) {
          Node parentNode = getParent(node,  Edge::EdgeType(graphconstants::ETYPE_DCF_CLONETREE, Edge::edtReverse));
          const Attribute& cloneSmellAttr = getNodeAttribute(parentNode, Attribute::atString, graphconstants::ATTR_DCF_CLONESMELLTYPE, graphconstants::CONTEXT_ATTRIBUTE);
          fakeInstance = cloneSmellAttr.getStringValue() == "cstDisappearing";
        }
        if (!fakeInstance) {
          io::CsvIO csvOut(csvName(fname, fext, nodeType), io::IOBase::omAppend);
          setCsvStyle(csvOut, separator, dmark);
          csvOut.writeColumn(node.getUID());
          string name;
          getNodeNameAttribute(node, name);
          csvOut.writeColumn(name);        
          writeParent(node, csvOut, Edge::EdgeType(graphconstants::ETYPE_DCF_CLONETREE, Edge::edtReverse));
          writeComponents(node, csvOut);
          writePositionColumns(node, csvOut);
          writeMetrics(reorderedMetricsMap[nodeType], node, csvOut);
          csvOut.writeNewLine();
          csvOut.close();
        }
      } else if (nodeType == graphconstants::NTYPE_LIM_COMPONENT) {
        io::CsvIO csvOut(csvName(fname, fext, nodeType), io::IOBase::omAppend);
        setCsvStyle(csvOut, separator, dmark);
        csvOut.writeColumn(node.getUID());
        string name;
        getNodeNameAttribute(node, name);
        csvOut.writeColumn(name);

        getNodeLongNameAttribute(node, name);
        csvOut.writeColumn(name);

        writeMetrics(reorderedMetricsMap[nodeType], node, csvOut);
        csvOut.writeNewLine();
        csvOut.close();

      } else if (nodeType == graphconstants::NTYPE_LIM_PACKAGE ||
        nodeType == graphconstants::NTYPE_RPG_SYSTEM ||
        nodeType == graphconstants::NTYPE_LIM_NAMESPACE)
      {
        io::CsvIO csvOut(csvName(fname, fext, nodeType), io::IOBase::omAppend);
        setCsvStyle(csvOut, separator, dmark);
        csvOut.writeColumn(node.getUID());
        string name;
        getNodeNameAttribute(node, name);
        csvOut.writeColumn(name);

        getNodeLongNameAttribute(node, name);
        csvOut.writeColumn(name);

        writeParent(node, csvOut, Edge::EdgeType(graphconstants::ETYPE_LIM_LOGICALTREE, Edge::edtReverse));
        writeComponents(node, csvOut);
        writeMetrics(reorderedMetricsMap[nodeType], node, csvOut);
        csvOut.writeNewLine();
        csvOut.close();

      } else if (nodeType == graphconstants::NTYPE_LIM_FILE ||
        nodeType == graphconstants::NTYPE_LIM_FOLDER)
      {
        io::CsvIO csvOut(csvName(fname, fext, nodeType), io::IOBase::omAppend);
        setCsvStyle(csvOut, separator, dmark);
        csvOut.writeColumn(node.getUID());
        string name;
        getNodeNameAttribute(node, name);
        csvOut.writeColumn(name);

        getNodeLongNameAttribute(node, name);
        csvOut.writeColumn(name);

        writeParent(node, csvOut, Edge::EdgeType(graphconstants::ETYPE_LIM_PHYSICALTREE, Edge::edtReverse));
        writeMetrics(reorderedMetricsMap[nodeType], node, csvOut);
        csvOut.writeNewLine();
        csvOut.close();

      }
    }
  }
}}
