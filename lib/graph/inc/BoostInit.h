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

#ifndef _GRAPHBOOSTINIT_H
#define _GRAPHBOOSTINIT_H

#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/properties.hpp>

#include "strtable/inc/StrTable.h"
#include "graph/inc/graph.h"

/**
* \internal
* \file BoostInit.h
* \brief initialize boost for the graph lib
*/

// define macros for XML reader and writer

#define XML_GRAPH_ROOT      "graph"
#define XML_GRAPH_HEAD      "header"
#define XML_GRAPH_DATA      "data"
#define XML_GRAPH_INFO      "info"
#define XML_GRAPH_DIRECTION "direction"
#define XML_GRAPH_NODE      "node"
#define XML_GRAPH_NAME      "name"
#define XML_GRAPH_TYPE      "type"
#define XML_GRAPH_CONTEXT   "context"
#define XML_GRAPH_VALUE     "value"
#define XML_GRAPh_EDGE      "edge"
#define XML_GRAPH_ATTR      "attribute"
#define XML_GRAPH_EDGE_TO   "to"
#define XML_GRAPH_EDGE_PAIR "edgePair"

#ifdef __LP64__
#define HASHLONGTOINT(hash) hash = hash ^ (hash>>sizeof(int));
#else
#define HASHLONGTOINT(hash)
#endif


//--Boost init

// add edge type to boost
enum edge_type_t { edge_type };

namespace boost {
  BOOST_INSTALL_PROPERTY(edge, type);
}

// add edge pair to boost
enum edge_pair_t { edge_pair };

namespace boost {
  BOOST_INSTALL_PROPERTY(edge, pair);
}

// add edge direction to boost
enum edge_direction_t { edge_direction };

namespace boost {
  BOOST_INSTALL_PROPERTY(edge, direction);
}

// add edge attributes to boost

enum edge_attributes_t { edge_attributes };

namespace boost {
  BOOST_INSTALL_PROPERTY(edge, attributes);
}

// add vertex UID to boost (node_id)

enum vertex_UID_t { vertex_UID };

namespace boost {
  BOOST_INSTALL_PROPERTY(vertex, UID);
}

// add vertex type to boost (node_type)

enum vertex_type_t { vertex_type };

namespace boost {
  BOOST_INSTALL_PROPERTY(vertex, type);
}

// add vertex attributes to boost (node_attributes)

enum vertex_attributes_t { vertex_attributes };

namespace boost {
  BOOST_INSTALL_PROPERTY(vertex, attributes);
}

//--End boost init

namespace columbus {  namespace graph {

  class Attribute;

  typedef std::list<Attribute*> AttributeList;

  typedef std::vector<Attribute*> AttributeVector;

  typedef columbus::Key Key;

  // create edge proportyes


  typedef boost::property<edge_attributes_t,AttributeList* > EdgeAttributes;
  typedef boost::property<edge_direction_t,int/*eDirectionType*/,EdgeAttributes> EdgeDirection;
  typedef boost::property<edge_type_t,Key,EdgeDirection> EdgeProperty;

  // create vertex proportyes

  typedef boost::property<vertex_attributes_t,AttributeList* > VertexAttributes;
  typedef boost::property<vertex_type_t,Key,VertexAttributes> VertexType;
  typedef boost::property<vertex_UID_t,Key,VertexType> VertexProperty;

  // create new Graph
  typedef boost::adjacency_list<boost::vecS, boost::listS, boost::directedS, VertexProperty, EdgeProperty> BGraph;

  // vertexes
  typedef boost::graph_traits<BGraph>::vertex_descriptor GraphVertex;

  //edges
  typedef boost::graph_traits<BGraph>::edge_descriptor GraphEdge;

  //iterators

  typedef boost::graph_traits<BGraph>::vertex_iterator vertex_iter;
  typedef boost::graph_traits<BGraph>::out_edge_iterator out_edge_iter;
  typedef boost::graph_traits<BGraph>::edge_iterator edge_iter;

  // property maps

  // vertex attributes
  typedef boost::property_map<BGraph, vertex_attributes_t>::type IndexMapVertexAttributes;
  // vertex UID
  typedef boost::property_map<BGraph, vertex_UID_t>::type IndexMapVertexUIDs;
  // vertex type
  typedef boost::property_map<BGraph, vertex_type_t>::type IndexMapVertexTypes;
  // edge type
  typedef boost::property_map<BGraph, edge_type_t>::type IndexMapEdgeTypes;
  // edge direction
  typedef boost::property_map<BGraph, edge_direction_t>::type IndexMapEdgeDirection;
  
}}

#endif
