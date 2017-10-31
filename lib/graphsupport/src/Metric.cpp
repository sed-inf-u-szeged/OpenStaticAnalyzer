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

#include "../inc/Metric.h"
#include "../inc/GraphConstants.h"

#include <iostream>
#include <map>
#include <set>
#include <algorithm>
#include <iterator>

using namespace columbus::graph;
using namespace std;

namespace columbus { namespace graphsupport {
  
  void removeINVALIDMetric(graph::Graph& graph, graph::Node& node, const string& name) {
    Attribute::AttributeIterator metricIt = node.findAttribute(Attribute::atString, name, graphconstants::ATTRVALUE_INVALID);
    AttributeString* invalidAttribute = NULL;
    if(metricIt.hasNext()) {
      // we found the INVALID attribute
      invalidAttribute = dynamic_cast<AttributeString*>(&metricIt.next());
    }
    if(invalidAttribute != NULL) {
      node.deleteAttribute(*invalidAttribute);
    }
  }


  void removeMetric(graph::Graph& graph, graph::Node& node, const string& name) {
    Attribute::AttributeIterator metricIt = node.findAttributeByName( name);
    AttributeString* invalidAttribute = NULL;
    if(metricIt.hasNext()) {
      // we found the INVALID attribute
      invalidAttribute = dynamic_cast<AttributeString*>(&metricIt.next());
    }
    if(invalidAttribute != NULL) {
      node.deleteAttribute(*invalidAttribute);
    }
  }
 
  static void addWarning(Graph& graph,Node& node, const string& name, const string& path, int line, int col, int endLine, int endCol, const string& text, const AttributeComposite* extraInfo) {
    AttributeComposite attrComposite = graph.createAttributeComposite(name, graphconstants::CONTEXT_WARNING);
    attrComposite.addAttribute(graph.createAttributeString(graphconstants::ATTR_PATH, "", path));
    attrComposite.addAttribute(graph.createAttributeInt(graphconstants::ATTR_LINE, "", line));
    attrComposite.addAttribute(graph.createAttributeInt(graphconstants::ATTR_COLUMN, "", col));
    attrComposite.addAttribute(graph.createAttributeInt(graphconstants::ATTR_ENDLINE, "", endLine));
    attrComposite.addAttribute(graph.createAttributeInt(graphconstants::ATTR_ENDCOLUMN, "", endCol));
    attrComposite.addAttribute(graph.createAttributeString(graphconstants::ATTR_WARNINGTEXT, "", text));
    
    if (extraInfo != NULL)
      attrComposite.addAttribute(*extraInfo);
      
    node.addAttribute(attrComposite);
  }

  void addWarning(Graph& graph,Node& node, const string& name, const string& path, int line, int col, int endLine, int endCol, const string& text) {
    addWarning(graph, node, name, path, line, col, endLine, endCol, text, NULL);
  }

  void addWarning(Graph& graph, const string& UID, const string& name, const string& path, int line, int col, int endLine, int endCol, const string& text ) {
    Node node = graph.findNode(UID);
    addWarning(graph, node, name, path, line, col, endLine, endCol, text);
  }

  static bool addWarningOnce(Graph& graph,Node& node, const string& name, const string& path, int line, int col, int endLine, int endCol, const string& text, const AttributeComposite* extraInfo) {
    Attribute::AttributeIterator it = node.findAttribute(Attribute::atComposite, name, graphconstants::CONTEXT_WARNING);
    while(it.hasNext()) {
      int sameValues = 0;
      AttributeComposite& compAttr = static_cast<AttributeComposite&>(it.next());
      Attribute::AttributeIterator compIt = compAttr.getAttributes();
      while(compIt.hasNext()) {
        Attribute& attr = compIt.next();
        const string& attrName = attr.getName();
        if(attrName == graphconstants::ATTR_PATH) {
          if(path == static_cast<AttributeString&>(attr).getValue()) sameValues++;
          else break;
        } else if(attrName == graphconstants::ATTR_WARNINGTEXT) {
          if(text == static_cast<AttributeString&>(attr).getValue()) sameValues++;
          else break;
        } else if(attrName == graphconstants::ATTR_LINE) {
          if(line == static_cast<AttributeInt&>(attr).getValue()) sameValues++;
          else break;
        } else if(attrName == graphconstants::ATTR_COLUMN) {
          if(col == static_cast<AttributeInt&>(attr).getValue()) sameValues++;
          else break;
        } else if(attrName == graphconstants::ATTR_ENDLINE) {
          if(endLine == static_cast<AttributeInt&>(attr).getValue()) sameValues++;
          else break;
        } else if(attrName == graphconstants::ATTR_ENDCOLUMN) {
          if(endCol == static_cast<AttributeInt&>(attr).getValue()) sameValues++;
          else break;
        }
      }
      if(sameValues == 6)
        return false;
    }
    addWarning(graph, node, name, path, line, col, endLine, endCol, text, extraInfo);
    return true;
  }
  
  bool addWarningOnce(Graph& graph,Node& node, const string& name, const string& path, int line, int col, int endLine, int endCol, const string& text ) {
    return addWarningOnce(graph, node, name, path, line, col, endLine, endCol, text, NULL);
  }

  bool addWarningOnce(Graph& graph, const string& UID, const string& name, const string& path, int line, int col, int endLine, int endCol, const string& text ) {
    Node node = graph.findNode(UID);
    return addWarningOnce(graph, node, name, path, line, col, endLine, endCol, text);
  }

  bool addWarningOnce(Graph& graph,Node& node, const string& name, const string& path, int line, int col, int endLine, int endCol, const string& text, const AttributeComposite& extraInfo) {
    return addWarningOnce(graph, node, name, path, line, col, endLine, endCol, text, &extraInfo);
  }


  void addPositionAttribute(graph::Graph& graph, graph::Node& node, const string& path, int line, int col, int endLine, int endCol, bool realizationLevel, bool definition) {
    GraphRangeIndexer& indexer = GraphRangeIndexer::getGraphRangeIndexerInstance();
    indexer.addNode(graph, node, path, line, col, endLine, endCol);
    AttributeComposite attrComposite = graph.createAttributeComposite(graphconstants::ATTR_POSITION, graphconstants::CONTEXT_ATTRIBUTE);
    attrComposite.addAttribute(graph.createAttributeString(graphconstants::ATTR_PATH, "", path));
    attrComposite.addAttribute(graph.createAttributeInt(graphconstants::ATTR_LINE, "", line));
    attrComposite.addAttribute(graph.createAttributeInt(graphconstants::ATTR_COLUMN, "", col));
    attrComposite.addAttribute(graph.createAttributeInt(graphconstants::ATTR_ENDLINE, "", endLine));
    attrComposite.addAttribute(graph.createAttributeInt(graphconstants::ATTR_ENDCOLUMN, "", endCol));
    if (realizationLevel) {
      if (definition)
        attrComposite.addAttribute(graph.createAttributeString(graphconstants::ATTR_REALIZATIONLEVEL, "", graphconstants::ATTRVALUE_LIM_RELDEFINES));
      else
        attrComposite.addAttribute(graph.createAttributeString(graphconstants::ATTR_REALIZATIONLEVEL, "", graphconstants::ATTRVALUE_LIM_RELDECLARES));
    }
    node.addAttribute(attrComposite);
  }

  void addPositionAttribute(graph::Graph& graph, const string& UID, const string& path, int line, int col, int endLine, int endCol, bool realizationLevel, bool definition) {
    Node node = graph.findNode(UID);
    addPositionAttribute(graph, node, path, line, col, endLine, endCol, realizationLevel, definition);
  }



  void addNodeNameAttribute(graph::Graph& graph, graph::Node& node, const string& name) {
    setStringAttribute(graph, node, graphconstants::ATTR_NAME, name);
  }

  void addNodeLongNameAttribute(graph::Graph& graph, graph::Node& node, const string& longName) {
    setStringAttribute(graph, node, graphconstants::ATTR_LONGNAME, longName);
  }

  void incMetricInt(graph::Graph& graph, graph::Node& node, const string& name, int value) {
    removeINVALIDMetric(graph, node, name);
    // find node metric attribute
    Attribute::AttributeIterator metricIt = node.findAttribute(Attribute::atInt, name, graphconstants::CONTEXT_METRIC);
    if(metricIt.hasNext()) {
      // we found a metric, now incrase it
      AttributeInt& attrInt = static_cast<AttributeInt&>(metricIt.next());
      attrInt.incValue(value);
    } else {
      // add new metric and set value to 'value'
      node.addAttribute(graph.createAttributeInt(name, graphconstants::CONTEXT_METRIC, value) );
    }
  }

  void incMetricInt(graph::Graph& graph, const string& UID, const string& name, int value) {
    Node gNode = graph.findNode(UID);
    if(gNode == Graph::invalidNode) 
      return;
    incMetricInt(graph, gNode, name, value);
  }

  void incMetricFloat(graph::Graph& graph, graph::Node& node, const string& name, float value) {
    removeINVALIDMetric(graph, node, name);
    // find node metric attribute
    Attribute::AttributeIterator metricIt = node.findAttribute(Attribute::atFloat, name, graphconstants::CONTEXT_METRIC);
    if(metricIt.hasNext()) {
      // we found a metric, now incrase it
      AttributeFloat& attrfloat = static_cast<AttributeFloat&>(metricIt.next());
      attrfloat.incValue(value);
    } else {
      // add new metric and set value to 'value'
      node.addAttribute(graph.createAttributeFloat(name, graphconstants::CONTEXT_METRIC, value) );
    }
  }

  void incMetricFloat(graph::Graph& graph, const string& UID, const string& name, float value) {
    Node gNode = graph.findNode(UID);
    if(gNode == Graph::invalidNode) 
      return;
    incMetricFloat(graph, gNode, name, value);
  }


  void setMetricInt(graph::Graph& graph, graph::Node& node, const string& name, int value) {
    removeINVALIDMetric(graph, node, name);
    // find node metric attribute
    Attribute::AttributeIterator metricIt = node.findAttribute(Attribute::atInt, name, graphconstants::CONTEXT_METRIC);
    if(metricIt.hasNext()) {
      // we found a metric, now set it
      AttributeInt& attrInt = static_cast<AttributeInt&>(metricIt.next());
      attrInt.setValue(value);
    } else {
      // add new metric and set value to 'value'
      node.addAttribute(graph.createAttributeInt(name, graphconstants::CONTEXT_METRIC, value) );
    }
  }

  void setMetricInt(graph::Graph& graph, const string& UID, const string& name, int value) {
    Node gNode = graph.findNode(UID);
    if(gNode == Graph::invalidNode) 
      return;
    setMetricInt(graph, gNode, name, value);
  }

  void setMetricFloat(graph::Graph& graph, graph::Node& node, const string& name, float value) {
    removeINVALIDMetric(graph, node, name);
    if(value > numeric_limits<float>::max() || value < -numeric_limits<float>::max() || value != value) {
      setMetricINVALID(graph, node, name);
    } else {
      // find node metric attribute
      Attribute::AttributeIterator metricIt = node.findAttribute(Attribute::atFloat, name, graphconstants::CONTEXT_METRIC);
      if(metricIt.hasNext()) {
        // we found a metric, now set it
        AttributeFloat& attrfloat = static_cast<AttributeFloat&>(metricIt.next());
        attrfloat.setValue(value);
      } else {
        // add new metric and set value to 'value'
        node.addAttribute(graph.createAttributeFloat(name, graphconstants::CONTEXT_METRIC, value) );
      }
    }
  }

  void setMetricFloat(graph::Graph& graph, const string& UID, const string& name, float value) {
    Node gNode = graph.findNode(UID);
    if(gNode == Graph::invalidNode) 
      return;
    setMetricFloat(graph, gNode, name, value);
  }

  void setMetricINVALID(graph::Graph& graph, graph::Node& node, const string& name) {
    // remove attribute old values
    std::list<Attribute*> removableAttributes;
    Attribute::AttributeIterator metricIt = node.findAttributeByContext(graphconstants::CONTEXT_METRIC);
    while(metricIt.hasNext()) {
      Attribute& attr = metricIt.next();
      if( (attr.getName() == name) && (attr.getType() != Attribute::atString) )
        removableAttributes.push_back(&attr);
    }
    for(std::list<Attribute*>::iterator it = removableAttributes.begin(); it != removableAttributes.end(); it++) {
      node.deleteAttribute(**it);
    }
    // find node metric attribute
    metricIt = node.findAttribute(Attribute::atString, name, graphconstants::CONTEXT_METRIC);
    if(metricIt.hasNext()) {
      // we found a metric, now set it
      AttributeString& attrstring = static_cast<AttributeString&>(metricIt.next());
      attrstring.setValue(graphconstants::ATTRVALUE_INVALID);
    } else {
      // add new metric and set value to 'value'
      node.addAttribute(graph.createAttributeString(name, graphconstants::CONTEXT_METRIC, graphconstants::ATTRVALUE_INVALID) );
    }
  }

  void setMetricINVALID(graph::Graph& graph, const string& UID, const string& name) {
    Node gNode = graph.findNode(UID);
    if(gNode == Graph::invalidNode) 
      return;
    setMetricINVALID(graph, gNode, name);
  }

  bool isINVALID(const graph::Attribute& attr) {
    if (attr.getType() != Attribute::atString)
      return false;
    
    if (((const graph::AttributeString&)attr).getValue().compare(graphconstants::ATTRVALUE_INVALID) != 0)
      return false;
      
    return true;
  }
  
  void getIntMetrics(graph::Graph& graph, graph::Node& node, std::map<string, int>& metrics ) {
    Attribute::AttributeIterator metricIt = node.findAttributeByType(Attribute::atInt);
    while(metricIt.hasNext()) {
      AttributeInt& attrInt = static_cast<AttributeInt&>(metricIt.next());
      if(attrInt.getContext() == graphconstants::CONTEXT_METRIC) {
        metrics.insert(make_pair(attrInt.getName(), attrInt.getValue() ) );
      }
    }
  }

  void getIntMetrics(graph::Graph& graph, const string& UID, std::map<string, int>& metrics ) {
    Node gNode = graph.findNode(UID);
    if(gNode == Graph::invalidNode) 
      return;
    getIntMetrics(graph, gNode, metrics);
  }

  void getFloatMetrics(graph::Graph& graph, graph::Node& node, std::map<string, float>& metrics ) {
    Attribute::AttributeIterator metricIt = node.findAttributeByType(Attribute::atFloat);
    while(metricIt.hasNext()) {
      AttributeFloat& attrfloat = static_cast<AttributeFloat&>(metricIt.next());
      if(attrfloat.getContext() == graphconstants::CONTEXT_METRIC) {
        metrics.insert(make_pair(attrfloat.getName(), attrfloat.getValue() ) );
      }
    }
  }

  void getFloatMetrics(graph::Graph& graph, const string& UID, std::map<string, float>& metrics ) {
    Node gNode = graph.findNode(UID);
    if(gNode == Graph::invalidNode) 
      return;
    getFloatMetrics(graph, gNode, metrics);
  }

  bool cutAttribute(AttributeComposite& nodePositionAttribute, string& path, int& line, int& col, int& endline, int& endcol, bool& realizationLevel, bool& definition) {
    bool fLine = false, fCol = false, fEndLine = false, fEndCol = false, fPath = false;
    realizationLevel = false;
    Attribute::AttributeIterator nodePositions = nodePositionAttribute.getAttributes();
    while(nodePositions.hasNext()) {
      Attribute& attr = nodePositions.next();
      if(attr.getType() == Attribute::atInt) {
        AttributeInt& attrInt = static_cast<AttributeInt&>(attr);
        const string& attrName = attrInt.getName();
        if(attrName == graphconstants::ATTR_LINE) {
          fLine = true;
          line = attrInt.getValue();
        } else if (attrName == graphconstants::ATTR_COLUMN) {
          fCol = true;
          col = attrInt.getValue();
        } else if (attrName == graphconstants::ATTR_ENDLINE) {
          fEndLine = true;
          endline = attrInt.getValue();
        } else if (attrName == graphconstants::ATTR_ENDCOLUMN) {
          fEndCol = true;
          endcol = attrInt.getValue();
        }
      } else if (attr.getType() == Attribute::atString) {
        AttributeString& attrString = static_cast<AttributeString&>(attr);
        if(attrString.getName() == graphconstants::ATTR_PATH) {
          fPath = true;
          path = attrString.getValue();
        } else if(attrString.getName() == graphconstants::ATTR_REALIZATIONLEVEL) { 
          realizationLevel = true;
          definition = attrString.getValue() == graphconstants::ATTRVALUE_LIM_RELDEFINES;
        }
      }
    }
    return (fLine && fCol && fEndLine && fEndCol && fPath);
  }

  bool getPositionAttributes(graph::Node& node, std::vector<Position>& positionAttributes) {
    int line, col, endline, endcol;
    std::string path;
    positionAttributes.clear();
    Attribute::AttributeIterator nodePositionAttributes = node.findAttribute(Attribute::atComposite, graphconstants::ATTR_POSITION, graphconstants::CONTEXT_ATTRIBUTE);
    while(nodePositionAttributes.hasNext()) {
      AttributeComposite& nodePositionAttribute = static_cast<AttributeComposite&>(nodePositionAttributes.next());
      bool realizationLevel, definition;
      if (cutAttribute(nodePositionAttribute, path, line, col, endline, endcol, realizationLevel, definition))
        positionAttributes.push_back(Position(path, line, col, endline, endcol));
    }
    return !positionAttributes.empty();
  }

  bool getPositionAttribute(const graph::Node& node, string& path, int& line, int& col, int& endLine, int& endCol, bool& realizationLevel, bool& definition) {
    line = 0;
    col = 0;
    endLine = 0;
    endCol = 0;
    path.clear();
    realizationLevel = false;
    definition = false;
    
    bool ret = false;
    Attribute::AttributeIterator nodePositionAttributes = node.findAttribute(Attribute::atComposite, graphconstants::ATTR_POSITION, graphconstants::CONTEXT_ATTRIBUTE);
    while (nodePositionAttributes.hasNext()) {
      AttributeComposite& nodePositionAttribute = static_cast<AttributeComposite&>(nodePositionAttributes.next());
      ret = cutAttribute(nodePositionAttribute, path, line, col, endLine, endCol, realizationLevel, definition);
      if (definition)
        break;
    }
    return ret;
  }

  bool getPositionAttribute(const graph::Node& node, string& path, int& line, int& col, int& endLine, int& endCol) {
    line = 0;
    col = 0;
    endLine = 0;
    endCol = 0;
    path.clear();
    bool realizationLevel;
    bool definition;
    
    bool ret = false;
    Attribute::AttributeIterator nodePositionAttributes = node.findAttribute(Attribute::atComposite, graphconstants::ATTR_POSITION, graphconstants::CONTEXT_ATTRIBUTE);
    if(nodePositionAttributes.hasNext()) {
      AttributeComposite& nodePositionAttribute = static_cast<AttributeComposite&>(nodePositionAttributes.next());
      ret = cutAttribute(nodePositionAttribute, path, line, col, endLine, endCol, realizationLevel, definition);
    }
    return ret;
  }


  bool getPositionAttribute(graph::Graph& graph, const string& UID, string& path, int& line, int& col, int& endLine, int& endCol) {
    Node gNode = graph.findNode(UID);
    if(gNode == Graph::invalidNode) 
      return false;
    bool realizationLevel, definition;
    return getPositionAttribute(gNode, path, line, col, endLine, endCol, realizationLevel, definition);
  }

  Attribute::AttributeIterator getWarningAttributes(graph::Node& node) {
    return node.findAttributeByContext(graphconstants::CONTEXT_WARNING);
  }

  Attribute::AttributeIterator getMetricAttributes(graph::Node& node) {
    return node.findAttributeByContext(graphconstants::CONTEXT_METRIC);
  }

  bool getNodeNameAttribute(const graph::Node& node, string& name) {
    bool ret = false;
    Attribute::AttributeIterator nodeNameAttributes = node.findAttribute(Attribute::atString, graphconstants::ATTR_NAME, graphconstants::CONTEXT_ATTRIBUTE);
    if(nodeNameAttributes.hasNext()) {
      AttributeString& nodeName = dynamic_cast<AttributeString&>(nodeNameAttributes.next());
      ret = true;
      name = nodeName.getValue();
    }
    return ret;
  }

  bool getNodeLongNameAttribute(const graph::Node& node, string& longName) {
    bool ret = false;
    Attribute::AttributeIterator nodeNameAttributes = node.findAttribute(Attribute::atString, graphconstants::ATTR_LONGNAME, graphconstants::CONTEXT_ATTRIBUTE);
    if(nodeNameAttributes.hasNext()) {
      AttributeString& nodeName = dynamic_cast<AttributeString&>(nodeNameAttributes.next());
      ret = true;
      longName = nodeName.getValue();
    }
    return ret;
  }

  bool getNodeTUIDAttribute(const graph::Node& node, string& tuid) {
    bool ret = false;
    Attribute::AttributeIterator nodeNameAttributes = node.findAttribute(Attribute::atString, graphconstants::ATTR_TUID, graphconstants::CONTEXT_ATTRIBUTE);
    if(nodeNameAttributes.hasNext()) {
      AttributeString& nodeName = dynamic_cast<AttributeString&>(nodeNameAttributes.next());
      ret = true;
      tuid = nodeName.getValue();
    }
    return ret;
  }

  static inline void getToNodes(Node& node, graph::Edge::EdgeType& along, graph::Node::NodeType toType, set<Node>& toNodes) {
    Edge::EdgeIterator alongEdges = node.findOutEdges(along);
    while(alongEdges.hasNext()) {
      Edge edge = alongEdges.next();
      Node toNode = edge.getToNode();
      if(toNode.getType() == toType) {
        toNodes.insert(toNode);
      }
    }
  }

  static inline void getToNodesRecursive(Node& node, graph::Edge::EdgeType& along, set<Node>& toNodes, map<Node, set<Node> >& adjacencyMap) {
    map<Node, set<Node> >::iterator adj = adjacencyMap.find(node);
    if(adjacencyMap.find(node) == adjacencyMap.end()) {
      toNodes.clear();
      stack<Node> nodesByalongEdges;
      nodesByalongEdges.push(node);
      while(!nodesByalongEdges.empty()) {
        Edge::EdgeIterator alongEdges = nodesByalongEdges.top().findOutEdges(along);
        nodesByalongEdges.pop();
        while(alongEdges.hasNext()) {
          Edge edge = alongEdges.next();
          Node toNode = edge.getToNode();
          toNodes.insert(toNode);
          nodesByalongEdges.push(toNode);
        }
      }
      adjacencyMap[node] = toNodes;
    } else {
      toNodes = adj->second;
    }
  }

  void liftEdge(graph::Graph& graph, graph::Node::NodeType fromType, graph::Node::NodeType toType, graph::Edge::EdgeType along, graph::Edge::EdgeType edgeType ) {
    liftEdge(graph, fromType, toType, along, edgeType, edgeType.getType(), false);
  }

  void liftEdge(graph::Graph& graph, graph::Node::NodeType fromType, graph::Node::NodeType toType, graph::Edge::EdgeType along, graph::Edge::EdgeType edgeType, const string& newEdgeType  ) {
    liftEdge(graph, fromType, toType, along, edgeType, newEdgeType, false);
  }


  void liftEdge(graph::Graph& graph, graph::Node::NodeType fromType, graph::Node::NodeType toType, graph::Edge::EdgeType along, graph::Edge::EdgeType edgeType, const string& newEdgeType, bool recursive ) {
    // get nodes
    Node::NodeIterator nodeIt = graph.findNodes(fromType);
    while(nodeIt.hasNext()) {
      stack<Node> nodeStack;
      nodeStack.push(nodeIt.next());
      while(!nodeStack.empty()) {
        Node node = nodeStack.top();
        cout << node.getUID() << endl;
        nodeStack.pop();
        // get edges of node, collect nodes along edge
        set<Node> fromNodes;
        getToNodes(node, along, toType, fromNodes);

        // get edges witch will be lifted
        set<Edge> liftedEdges;
        Edge::EdgeIterator liftedEdgeIt = node.findOutEdges(edgeType);
        while(liftedEdgeIt.hasNext()) {
          Edge edge = liftedEdgeIt.next();
          Node toNode = edge.getToNode();
          // liftedEdge
          set<Node> toNodes;
          getToNodes(toNode, along, toType, toNodes);
          for(set<Node>::const_iterator fromNodesIt = fromNodes.begin(); fromNodesIt != fromNodes.end(); ++fromNodesIt) {
            for(set<Node>::const_iterator toNodesIt = toNodes.begin(); toNodesIt != toNodes.end(); ++toNodesIt) {
              Edge::EdgeType edt(newEdgeType ,edge.getType().getDirectionType());

              addEdgeOnce(graph, *fromNodesIt, *toNodesIt, edt);
              cout << fromNodesIt->getUID() << " " << toNodesIt->getUID() << endl;
            }
          }
        }
        if(recursive) {
          for(set<Node>::const_iterator it = fromNodes.begin(); it != fromNodes.end(); ++it) {
            nodeStack.push(*it);
          }
        }
      }
    }
  }

  void multiLiftEdge(graph::Graph& graph, graph::Node::NodeType fromType, graph::Edge::EdgeType along, graph::Edge::EdgeType edgeType, const std::string& newEdgeType) {
    map<Node, set<Node> > edgeCreationMap;
    map<Node, set<Node> > adjacencyMap;
//    int i = 0;
    Node::NodeIterator nodeIt = graph.findNodes(fromType);
    while(nodeIt.hasNext()) {
      Node node = nodeIt.next();
//      cout << ++i << " S: " << node.getUID() << " " << edgeType.getType() << " " << newEdgeType << endl;
      Edge::EdgeIterator outEdges = node.findOutEdges(edgeType);
      set<Node> nodeParents;
      getToNodesRecursive(node, along, nodeParents, adjacencyMap);
      int y = 0;
      while(outEdges.hasNext()) {
        y++;
        Edge edge = outEdges.next();
        Node toNode = edge.getToNode();
//        cout << "\tT: " << toNode.getUID() << endl;
        if(node == toNode) {
          for(set<Node>::iterator it = nodeParents.begin(); it != nodeParents.end(); ++it) {
            edgeCreationMap[*it].insert(*it);
          }
        } else {
          set<Node> toNodeParents;
          getToNodesRecursive(toNode, along, toNodeParents, adjacencyMap);

          set<Node> diffNodes;
          set<Node> diffNodesFrom;
          std::insert_iterator<std::set<Node> > ii(diffNodes, diffNodes.begin());
          std::insert_iterator<std::set<Node> > iiFrom(diffNodesFrom, diffNodesFrom.begin());
          set_difference(toNodeParents.begin(), toNodeParents.end(), nodeParents.begin(), nodeParents.end(), ii);
          set_difference(nodeParents.begin(), nodeParents.end(),toNodeParents.begin(), toNodeParents.end(), iiFrom);
          diffNodes.insert(toNode);
          diffNodesFrom.insert(node);


          for(set<Node>::const_iterator itFrom = diffNodesFrom.begin(); itFrom != diffNodesFrom.end(); ++itFrom) {
            for(set<Node>::const_iterator it = diffNodes.begin(); it != diffNodes.end(); ++it) {
              if(*it == toNode && *itFrom == node )
                continue;
              edgeCreationMap[*itFrom].insert(*it);
//              cout << "\t\t" << itFrom->getUID() << " " << it->getUID() << endl;
            }
          }

        }
      }
//      cout << " " << y << endl;
    }
    for(map<Node, set<Node> >::iterator ecmIt = edgeCreationMap.begin(); ecmIt != edgeCreationMap.end(); ++ecmIt) {
      for(set<Node>::iterator ecmsIt = ecmIt->second.begin(); ecmsIt != ecmIt->second.end(); ++ecmsIt) {
        graph.createDirectedEdge(ecmIt->first, *ecmsIt, newEdgeType, false);
      }
    }
  }

  Edge addEdgeOnce(graph::Graph& graph, graph::Node from, graph::Node to, graph::Edge::EdgeType type, bool reverse) {
    Edge retEdge;
    Edge::EdgeIterator edgeIt = from.findOutEdges(type);
    bool toNodeFound = false;
    while(edgeIt.hasNext()) {
      Edge edge = edgeIt.next();
      if(edge.getToNode() == to) {
        toNodeFound = true;
        retEdge = edge;
        break;
      }
    }
    if(!toNodeFound) {
      switch(type.getDirectionType()) {
      case Edge::edtBidirectional:
      {
        retEdge = graph.createBidirectedEdge(from, to, type.getType());
        break;
      }
      case Edge::edtDirectional:
      {
        retEdge = graph.createDirectedEdge(from, to, type.getType(), reverse);
        break;
      }
      case Edge::edtReverse:
      {
        retEdge = graph.createDirectedEdge(to, from, type.getType(), true);
        break;
      }
      }
    }
    return retEdge;

  }

  template<class nodeEdge>
  inline static void addAttributeOnceT(nodeEdge ne, const graph::Attribute& attr, bool refresh) {
    Attribute::AttributeIterator attrIt = ne.findAttribute(attr.getType(), attr.getName(), attr.getContext());
    if(attrIt.hasNext()) {
      Attribute& nextAttr = attrIt.next();
      if(refresh) {
        ne.deleteAttribute(nextAttr);
        ne.addAttribute(attr);
      }
    } else {
      ne.addAttribute(attr);
    }
  }

  void addAttributeOnce(graph::Node node, const graph::Attribute& attr, bool refresh) {
    addAttributeOnceT(node, attr, refresh);
  }

  void addAttributeOnce(graph::Edge edge, const graph::Attribute& attr, bool refresh) {
    addAttributeOnceT(edge, attr, refresh);
  }


  const Attribute& getNodeAttribute(graph::Node node, const Attribute::aType type, const std::string& name, const std::string& context) {
    Attribute::AttributeIterator nodeNameAttributes = node.findAttribute(type, name, context);
    if(nodeNameAttributes.hasNext()) {
      return nodeNameAttributes.next();
    }
    return Graph::invalidAttribute;
  }
  

  void setStringAttribute( graph::Graph& graph, graph::Node& node, const string& name, const string& value )
  {
        // find node metric attribute
    Attribute::AttributeIterator metricIt = node.findAttribute(Attribute::atString, name, graphconstants::CONTEXT_ATTRIBUTE);
    if(metricIt.hasNext()) {
      // we found a metric, now set it
      AttributeString& attrstring = static_cast<AttributeString&>(metricIt.next());
      attrstring.setValue(value);
    } else {
      // add new metric and set value to 'value'
      node.addAttribute(graph.createAttributeString(name, graphconstants::CONTEXT_ATTRIBUTE, value ));
    }
  }

  void setStringAttribute(graph::Graph& graph, const string& UID, const string& name, const string& value )
  {
    Node gNode = graph.findNode(UID);
    if(gNode == Graph::invalidNode) 
      return;
    setStringAttribute(graph, gNode, name, value);
  }

  graph::AttributeComposite createSourceLinkAttribute(graph::Graph& graph, const std::string& path, int line, int column, int endLine, int endColumn) {
    AttributeComposite sl = graph.createAttributeComposite(graphconstants::ATTR_SOURCELINK, "");
    sl.addAttribute(graph.createAttributeString(graphconstants::ATTR_PATH, "", path));
    sl.addAttribute(graph.createAttributeInt(graphconstants::ATTR_LINE, "", line));
    sl.addAttribute(graph.createAttributeInt(graphconstants::ATTR_COLUMN, "", column));
    sl.addAttribute(graph.createAttributeInt(graphconstants::ATTR_ENDLINE, "", endLine));
    sl.addAttribute(graph.createAttributeInt(graphconstants::ATTR_ENDCOLUMN, "", endColumn));
    return sl;
  }

  graph::AttributeComposite createSourceLinkAttribute(graph::Graph& graph, const std::string& path, int line) {
    AttributeComposite sl = graph.createAttributeComposite(graphconstants::ATTR_SOURCELINK, "");
    sl.addAttribute(graph.createAttributeString(graphconstants::ATTR_PATH, "", path));
    sl.addAttribute(graph.createAttributeInt(graphconstants::ATTR_LINE, "", line));
    sl.addAttribute(graph.createAttributeInt(graphconstants::ATTR_COLUMN, "", 0));
    sl.addAttribute(graph.createAttributeInt(graphconstants::ATTR_ENDLINE, "", line));
    sl.addAttribute(graph.createAttributeInt(graphconstants::ATTR_ENDCOLUMN, "", 10000));
    return sl;
  }


  void setAnonymousAttribute(graph::Graph& graph, graph::Node& node, const bool isAnonymous) {
    Attribute::AttributeIterator anonymousIt = node.findAttribute(Attribute::atInt, graphconstants::ATTR_ANONYMOUS, graphconstants::CONTEXT_ATTRIBUTE);
    if(anonymousIt.hasNext()) {
      AttributeInt& attrInt = static_cast<AttributeInt&>(anonymousIt.next());
      attrInt.setValue(isAnonymous ? 1 : 0);
    } else {
      node.addAttribute(graph.createAttributeInt(graphconstants::ATTR_ANONYMOUS, graphconstants::CONTEXT_ATTRIBUTE, isAnonymous ? 1 : 0));
    }
  }


  bool getAnonymousAttribute(const graph::Node& node) {
    Attribute::AttributeIterator anonymousIt = node.findAttribute(Attribute::atInt, graphconstants::ATTR_ANONYMOUS, graphconstants::CONTEXT_ATTRIBUTE);
    if(anonymousIt.hasNext()) {
      AttributeInt& attrInt = static_cast<AttributeInt&>(anonymousIt.next());
      return attrInt.getValue() != 0;
    }
    return false;
  }

}}
