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

#ifndef _METRICGRAPSUPPORT
#define _METRICGRAPSUPPORT

#include <graph/inc/graph.h>
#include "GraphRangeIndexer.h"
#include <string>
#include <map>

/**
  \file Metric.h
  \brief Contains graph support for metrics and warnings
*/

namespace columbus { namespace graphsupport { 

  /**
   * \brief position of a node
   */
  struct Position {
    Position(const std::string& path, int line, int col, int endline, int endcol ) : 
      path(path), line(line), col(col), endline(endline), endcol(endcol) {}
    std::string path;
    int line;
    int col;
    int endline;
    int endcol;
  };

   /**
  * \brief  remove metric
  * \param graph [in] the graph
  * \param node [in] the node
  * \param name [in] the name of Metric
  */

  void removeMetric(graph::Graph& graph, graph::Node& node, const std::string& name) ;

  /**
  * \brief Adds a composite warning attribute to a node.
  * \param graph [in] the graph
  * \param node [in] the node
  * \param name [in] the warning type ('GEN1001')
  * \param path [in] the file path, witch contains the warning
  * \param line [in] warning place in the file (start line)
  * \param col [in] warning place in the file (start column)
  * \param endLine [in] warning place in the file (end line)
  * \param endCol [in] warning place in the file (end column)
  * \param warningText [in] the warning description
  */
  void addWarning(graph::Graph& graph, graph::Node& node, const std::string& name, const std::string& path, int line, int col, int endLine, int endCol, const std::string& text);

  /**
  * \brief Adds a composite attribute to a node.
  * \param graph [in] the graph
  * \param UID [in] the UID of node
  * \param name [in] the warning type ('GEN1001')
  * \param path [in] the file path, witch contains the warning
  * \param line [in] warning place in the file (start line)
  * \param col [in] warning place in the file (start column)
  * \param endLine [in] warning place in the file (end line)
  * \param endCol [in] warning place in the file (end column)
  * \param warningText [in] the warning description
  */
  void addWarning(graph::Graph& graph, const std::string& UID, const std::string& name, const std::string& path, int line, int col, int endLine, int endCol, const std::string& text);

  /**
  * \brief Adds a composite warning attribute to a node if it not exist.
  * \param graph [in] the graph
  * \param node [in] the node
  * \param name [in] the warning type ('GEN1001')
  * \param path [in] the file path, witch contains the warning
  * \param line [in] warning place in the file (start line)
  * \param col [in] warning place in the file (start column)
  * \param endLine [in] warning place in the file (end line)
  * \param endCol [in] warning place in the file (end column)
  * \param warningText [in] the warning description
  * \return return true, if the warning didn't exist
  */
  bool addWarningOnce(graph::Graph& graph, graph::Node& node, const std::string& name, const std::string& path, int line, int col, int endLine, int endCol, const std::string& text);

  /**
  * \brief Adds a composite attribute to a node if it not exist.
  * \param graph [in] the graph
  * \param UID [in] the UID of node
  * \param name [in] the warning type ('GEN1001')
  * \param path [in] the file path, witch contains the warning
  * \param line [in] warning place in the file (start line)
  * \param col [in] warning place in the file (start column)
  * \param endLine [in] warning place in the file (end line)
  * \param endCol [in] warning place in the file (end column)
  * \param warningText [in] the warning description
  * \return return true, if the warning didn't exist
  */
  bool addWarningOnce(graph::Graph& graph, const std::string& UID, const std::string& name, const std::string& path, int line, int col, int endLine, int endCol, const std::string& text);

  /**
  * \brief Adds a composite warning attribute to a node if it not exist.
  * \param graph [in] the graph
  * \param node [in] the node
  * \param name [in] the warning type ('GEN1001')
  * \param path [in] the file path, witch contains the warning
  * \param line [in] warning place in the file (start line)
  * \param col [in] warning place in the file (start column)
  * \param endLine [in] warning place in the file (end line)
  * \param endCol [in] warning place in the file (end column)
  * \param warningText [in] the warning description
  * \param extraInfo [in] the extraInfo composite attribute 
  * \return return true, if the warning didn't exist
  */
  bool addWarningOnce(graph::Graph& graph, graph::Node& node, const std::string& name, const std::string& path, int line, int col, int endLine, int endCol, const std::string& text, const graph::AttributeComposite& extraInfo);

  /**
  * \brief Adds a 'position' composite attribute to a node.
  * \param graph [in] the graph
  * \param node [in] the node
  * \param path [in] the file path
  * \param line [in] start line
  * \param col [in] start column
  * \param endLine [in] end line
  * \param endCol [in] end column
  * \param realizationLevel [in] save realization level beside the position info or no
  * \param definition [in] if it is true then the given position is a definition, otherwise it is a declaration.
  */
  void addPositionAttribute(graph::Graph& graph, graph::Node& node, const std::string& path, int line, int col, int endLine, int endCol, bool realizationLevel = false, bool definition = true);

  /**
  * \brief Adds a 'position' composite attribute to a node.
  * \param graph [in] the graph
  * \param UID [in] the UID of node
  * \param path [in] the file path
  * \param line [in] start line
  * \param col [in] start column
  * \param endLine [in] end line
  * \param endCol [in] end column
  * \param realizationLevel [in] save realization level beside the position info or no
  * \param definition [in] if it is true then the given position is a definition, otherwise it is a declaration.
  */
  void addPositionAttribute(graph::Graph& graph, const std::string& UID, const std::string& path, int line, int col, int endLine, int endCol, bool realizationLevel = false, bool definition = true);

  /**
  * \brief get a 'position' composite attribute from a node.
  * \param node [in] the node
  * \param path [out] the file path
  * \param line [out] start line
  * \param col [out] start column
  * \param endLine [out] end line
  * \param endCol [out] end column
  * \param realizationLevel [out] true if realization level exists
  * \param definition [out] true if realization level exists and it is a definition, otherwise it is false
  * \return return true, if all attribute is found
  */
  bool getPositionAttribute(const graph::Node& node, std::string& path, int& line, int& col, int& endLine, int& endCol, bool& realizationLevel, bool& definition);


  /**
  * \brief get a 'position' composite attribute from a node.
  * \param node [in] the node
  * \param path [out] the file path
  * \param line [out] start line
  * \param col [out] start column
  * \param endLine [out] end line
  * \param endCol [out] end column
  * \return return true, if all attribute is found
  */
  bool getPositionAttribute(const graph::Node& node, std::string& path, int& line, int& col, int& endLine, int& endCol);

  /**
  * \brief get a 'position' composite attribute from a node.
  * \param UID [in] the UID of node
  * \param path [out] the file path
  * \param line [out] start line
  * \param col [out] start column
  * \param endLine [out] end line
  * \param endCol [out] end column
  * \return return true, if all attribute is found
  */
  bool getPositionAttribute(graph::Graph& graph, const std::string& UID, std::string& path, int& line, int& col, int& endLine, int& endCol);

  /**
  * \brief get a 'position' composite attribute from a node.
  * \param node [in] the node
  * \param positionAttributes [out] the attributes
  * \return return true, if all attribute is founded  */
  bool getPositionAttributes(graph::Node& node, std::vector<Position>& positionAttributes);

  /**
   * \brief Adds a name attribute to the node. It changes its value if the name attribute already exists.
   * \param graph [in] the graph
   * \param node [in] the node
   * \param name [in] the value of the name attribute
   */
  void addNodeNameAttribute(graph::Graph& graph, graph::Node& node, const std::string& name);

  /**
   * \brief Adds a long name attribute to the node.It changes its value if the long name attribute already exists.
   * \param graph [in] the graph
   * \param node [in] the node
   * \param name [in] the value of the long name attribute
   */
  void addNodeLongNameAttribute(graph::Graph& graph, graph::Node& node, const std::string& longName);

  /**
   * \brief gives back node name by first name attribute
   * \param node [in] the node
   * \param name [out] the node name
   * \return true, if node has name attribute, otherwise return false
   */
  bool getNodeNameAttribute(const graph::Node& node, std::string& name);

  /**
   * \brief gives back node long name by first LongName attribute
   * \param node [in] the node
   * \param name [out] the qualified name name
   * \return true, if node has LongName attribute, otherwise return false
   */
  bool getNodeLongNameAttribute(const graph::Node& node, std::string& longName);

  /**
   * \brief gives back the value of the first TUID attribute of the node
   * \param node [in] the node
   * \param name [out] the value of its first TUID attribute
   * \return true, if node has TUID attribute, otherwise return false
   */
  bool getNodeTUIDAttribute(const graph::Node& node, std::string& tuid);

  /**
  * \brief set a string attribute of the node
  * \param graph [in] graph
  * \param node [in] node
  * \param value [in]  value
  */
  void setStringAttribute(graph::Graph& graph, graph::Node& node, const std::string& name, const std::string& value);
  
  /**
  * \brief set a string attribute of the node
  * \param graph [in] graph
  * \param UID [in] unique name of node
  * \param value [in] value
  */
  void setStringAttribute(graph::Graph& graph, const std::string& UID, const std::string& name, const std::string& value);
  
  /**
  * \brief increase metric value by 'value' on 'node'. If metric doesn't exist, the function create one, and set value to 'value'
  * \param graph [in] graph
  * \param node [in] node, witch has metric
  * \param value [in] incrase metric with value
  */
  void incMetricInt(graph::Graph& graph, graph::Node& node, const std::string& name, int value);
  
  /**
  * \brief increase metric value by 'value' on 'node'. If metric doesn't exist, the function create one, and set value to 'value'
  * \param graph [in] graph
  * \param UID [in] unique name of node
  * \param value [in] incrase metric with value
  */
  void incMetricInt(graph::Graph& graph, const std::string& UID, const std::string& name, int value);

  /**
  * \brief increase metric value by 'value' on 'node'. If metric doesn't exist, the function create one, and set value to 'value'
  * \param graph [in] graph
  * \param node [in] node, witch has metric
  * \param value [in] incrase metric with value
  */
  void incMetricFloat(graph::Graph& graph, graph::Node& node, const std::string& name, float value);

  /**
  * \brief increase metric value by 'value' on 'node'. If metric doesn't exist, the function create one, and set value to 'value'
  * \param graph [in] graph
  * \param UID [in] unique name of node
  * \param value [in] incrase metric with value
  */
  void incMetricFloat(graph::Graph& graph, const std::string& UID, const std::string& name, float value);

  /**
  * \brief set metric value to 'value' on 'node'. If metric doesn't exist, the function create one, and set value to 'value'
  * \param graph [in] graph
  * \param node [in] node, witch has metric
  * \param value [in] incrase metric with value
  */
  void setMetricInt(graph::Graph& graph, graph::Node& node, const std::string& name, int value);
  
  /**
  * \brief set metric value to 'value' on 'node'. If metric doesn't exist, the function create one, and set value to 'value'
  * \param graph [in] graph
  * \param UID [in] unique name of node
  * \param value [in] incrase metric with value
  */
  void setMetricInt(graph::Graph& graph, const std::string& UID, const std::string& name, int value);

  /**
  * \brief set metric value to 'value' on 'node'. If metric doesn't exist, the function create one, and set value to 'value'
  * \param graph [in] graph
  * \param node [in] node, witch has metric
  * \param value [in] incrase metric with value
  */
  void setMetricFloat(graph::Graph& graph, graph::Node& node, const std::string& name, float value);

  /**
  * \brief set metric value to 'value' on 'node(UID)'. If metric doesn't exist, the function create one, and set value to 'value'
  * \param graph [in] graph
  * \param UID [in] unique name of node
  * \param value [in] incrase metric with value
  */
  void setMetricFloat(graph::Graph& graph, const std::string& UID, const std::string& name, float value);

  /**
  * \brief set metric value to INVALID on 'node'. If metric doesn't exist, the function create one, and set value to INVALID
  * \param graph [in] graph
  * \param node [in] node, witch has metric
  */
  void setMetricINVALID(graph::Graph& graph, graph::Node& node, const std::string& name);

  /**
  * \brief set metric value to INVALID on 'node(UID)'. If metric doesn't exist, the function create one, and set value to INVALID
  * \param graph [in] graph
  * \param UID [in] unique name of node
  */
  void setMetricINVALID(graph::Graph& graph, const std::string& UID, const std::string& name);

  /**
  * \brief checks whether the given attribute is INVALID or no. It returns true if the given attribute is a string attribute and its value is the columbus::graphsupport::INVALID.
  * \param attr [in] the attribute to be checked
  * \return true if it is invalid. false otherwise.
  */
  bool isINVALID(const graph::Attribute& attr);

  /**
  * \brief gives back node int metrics with values 
  * \param graph [in] graph
  * \param node [in] node, witch has metric
  * \param metrics [out] the metrics names and values
  */
  void getIntMetrics(graph::Graph& graph, graph::Node& node, std::map<std::string, int>& metrics );

  /**
  * \brief gives back node int metrics with values 
  * \param graph [in] graph
  * \param UID [in] unique name of node
  * \param metrics [out] the metrics names and values
  */
  void getIntMetrics(graph::Graph& graph, const std::string& UID, std::map<std::string, int>& metrics );

  /**
  * \brief gives back node float metrics with values 
  * \param graph [in] graph
  * \param node [in] node, witch has metric
  * \param metrics [out] the metrics names and values
  */
  void getFloatMetrics(graph::Graph& graph, graph::Node& node, std::map<std::string, float>& metrics );

  /**
  * \brief gives back node float metrics with values 
  * \param graph [in] graph
  * \param UID [in] unique name of node
  * \param metrics [out] the metrics names and values
  */
  void getFloatMetrics(graph::Graph& graph, const std::string& UID, std::map<std::string, float>& metrics );

  /**
  * \brief gives back node Warnings attributes
  * \param node [in] the node
  */
  graph::Attribute::AttributeIterator getWarningAttributes(graph::Node& node);

  /**
  * \brief gives back node Metrics attributes
  * \param node [in] the node
  */
  graph::Attribute::AttributeIterator getMetricAttributes(graph::Node& node);

  /**
   * \brief add edge once to graph
   * \param graph [in] the input graph
   * \param from [in] the source node
   * \param to [in] the target node
   * \param edgeType [in] the new edge type
   * \param reverse [in] create reverse edge to directional edge
   * \return the new edge, or the same exist edge
   */
  graph::Edge addEdgeOnce(graph::Graph& graph, graph::Node from, graph::Node to, graph::Edge::EdgeType type, bool reverse = false);

  /**
   * \brief lift 'edgeType' type edge one level by 'along' type edge
   * \param graph [in] graph
   * \param from [in] the source node type
   * \param to [in] the target node type
   * \param along [in] lift edges along this edge
   * \param edgeType [in] lift edges witch has 'edgeType' type
   */
  void liftEdge(graph::Graph& graph, graph::Node::NodeType from, graph::Node::NodeType to, graph::Edge::EdgeType along, graph::Edge::EdgeType edgeType );

  /**
   * \brief lift 'edgeType' type edge one level by 'along' type edge and rename lifted edges to newEdgeType
   * \param graph [in] graph
   * \param from [in] the source node type
   * \param to [in] the target node type
   * \param along [in] lift edges along this edge
   * \param edgeType [in] lift edges witch has 'edgeType' type
   * \param newEdgeType [in] the lifted edge name
   */
  void liftEdge(graph::Graph& graph, graph::Node::NodeType from, graph::Node::NodeType to, graph::Edge::EdgeType along, graph::Edge::EdgeType edgeType, const std::string& newEdgeType );

  /**
   * \brief lift 'edgeType' type edge one level by 'along' type edge and rename lifted edges to newEdgeType
   * \param graph [in] graph
   * \param from [in] the source node type
   * \param to [in] the target node type
   * \param along [in] lift edges along this edge
   * \param edgeType [in] lift edges witch has 'edgeType' type
   * \param newEdgeType [in] the lifted edge name
   * \param recursive [in] it it true, lift edges recursively
   */
  void liftEdge(graph::Graph& graph, graph::Node::NodeType from, graph::Node::NodeType to, graph::Edge::EdgeType along, graph::Edge::EdgeType edgeType, const std::string& newEdgeType, bool recursive );

  /**
   * \brief lift edge source and target differently (first lift only source, after lift only target)
   * \param graph [in] graph
   * \param from [in] the source node type
   * \param along [in] lift edges along this edge
   * \param edgeType [in] lift edges witch has 'edgeType' type
   * \param newEdgeType [in] the lifted edge name
   */
  void multiLiftEdge(graph::Graph& graph, graph::Node::NodeType from, graph::Edge::EdgeType along, graph::Edge::EdgeType edgeType, const std::string& newEdgeType);

  /**
   * \brief add attribute once to node
   * \param node [in] node from graph
   * \param attr [in] the attribute
   * \param refresh [in] if it true, existing attribute will be replaced, otherwise not
   */
  void addAttributeOnce(graph::Node node, const graph::Attribute& attr, bool refresh);

  /**
   * \brief add attribute once to edge
   * \param edge [in] edge from graph
   * \param attr [in] the attribute
   * \param refresh [in] if it true, existing attribute will be replaced, otherwise not
   */
  void addAttributeOnce(graph::Edge edge, const graph::Attribute& attr, bool refresh);
  
  /**
   * \brief find first attribute by context, type and name
   * \param type [in] the attribute type
   * \param node [in] node from graph
   * \param name [in] the attribute name
   * \param context [in] the attribute context
   * \return the founded attribute, otherwise invalidAttribute
   */
  const graph::Attribute& getNodeAttribute(graph::Node node, const graph::Attribute::aType type, const std::string& name, const std::string& context);

  /**
   * \brief Creates a composite SourceLink attribute with the corresponding line info attribtues.
   * \param graph [in] the graph in which the attribute is created
   * \param path [in] the file path
   * \param line [in] warning place in the file (start line)
   * \param column [in] warning place in the file (start column)
   * \param endLine [in] warning place in the file (end line)
   * \param endColumn [in] warning place in the file (end column)
   * \return return the created SourceLink attribute
   */
  graph::AttributeComposite createSourceLinkAttribute(graph::Graph& graph, const std::string& path, int line, int column, int endLine, int endColumn);

  /**
   * \brief Creates a composite SourceLink attribute with the corresponding line info attribtues.
   * \param graph [in] the graph in which the attribute is created
   * \param path [in] the file path
   * \param line [in] warning place in the file (start line)
   * \return return the created SourceLink attribute
   */
  graph::AttributeComposite createSourceLinkAttribute(graph::Graph& graph, const std::string& path, int line);
  
  /**
   * \brief Sets the Anonymous attribute of the given node.
   * \param graph        [in] the graph in which the attribute is created if it does not exists
   * \param node         [in] the node which attribute is set
   * \param isAnonymous  [in] the new value of the Anonymous attribute
   */
  void setAnonymousAttribute(graph::Graph& graph, graph::Node& node, const bool isAnonymous);

  /**
   * \brief Gets the Anonymous attribute of the given node.
   * \param node         [in] the node which attribute is checked
   * \return the value of the Anonymous attribute of the given node. If it does not have Anonymous attribute, then the function will return false.
   */
  bool getAnonymousAttribute(const graph::Node& node);
  
}}

#endif
