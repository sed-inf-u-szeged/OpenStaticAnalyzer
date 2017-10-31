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

#include "../inc/graph.h"

#include "../privinc/GraphXmlHandler.h"
#include "../privinc/GraphSchemaReader.h"
#include "boost/tuple/tuple_comparison.hpp"
#include "boost/lexical_cast.hpp"
#include "boost/algorithm/string/split.hpp"
#include "boost/algorithm/string/classification.hpp"
#include "../privinc/messages.h"

using namespace boost;
using namespace std;
using namespace columbus::io;

#define _UNIQUENAME         "UniqueName"
#define _STARTUNIQUENAME    "StartUniqueName"
#define _ENDUNIQUENAME      "EndUniqueName"
#define _EDGE_DIRECTION     "Edge Direction"
#define _BIDIRECTIONAL      "Bidirectional"
#define _DIRECTIONAL        "Directional"
#define _REVERSE            "Reverse"
#define _EMPTY_FIELD        "N/A"
#define _NAME_SEPARATOR     "_"
#define _TYPE_CONTEXT_BEGIN "["
#define _TYPE_CONTEXT_SEP   ":"
#define _TYPE_NAME_ID       "Type"
#define _TYPE_NAME_BEGIN    "[Type:"
#define _CONTEXT_NAME_ID    "Context"
#define _CONTEXT_NAME_BEGIN "[Context:"
#define _TYPE_NAME_END      "]"
#define _CONTEXT_NAME_END   "]"

namespace columbus {  namespace graph {

  Graph::Graph()
    : attributeIteratorsOnVertex()
    , attributeIteratorsOnEdge()
    , edgeIteratorOnNode()
    , nodeIterators()
    , headerInformations()
    , g( new BGraph())
    , strTable( new StrTable())
    , nodeUIDs()
    , edgePairMap()
    , gsReader( new GraphSchemaReader())
  {

  }

  Graph::~Graph() {
    
    clearAttributes();
    clearHelperContaioners();
    clearHeaderInfo();
    delete g;
    delete strTable;
    delete gsReader;

  }

  void Graph::clearAttributes() {
    //g beli node-k attributumait es azok taroloi torlese
    vertex_iter vertex_begin, vertex_end, vertex_it;
    boost::tie(vertex_begin, vertex_end) = vertices(*g);
    for(vertex_it = vertex_begin; vertex_it != vertex_end; vertex_it++ ) {
      AttributeList* attrList = get(vertex_attributes, *g, *vertex_it);
      for(AttributeList::iterator it = attrList->begin(); it != attrList->end(); it++) {
        delete *it;
      }
      delete attrList;
    }

    //g beli elek attributumait es azok taroloi torlese
    edge_iter edge_begin, edge_end, edge_it;
    boost::tie(edge_begin, edge_end) = edges(*g);
    for(edge_it = edge_begin; edge_it != edge_end; edge_it++ ) {
      AttributeList* attrList = get(edge_attributes, *g, *edge_it);
      for(AttributeList::iterator it = attrList->begin(); it != attrList->end(); it++) {
        delete *it;
      }
      delete attrList;
    }
  }
  
  void Graph::clearHelperContaioners() {
    nodeUIDs.clear();
    edgePairMap.clear();
    for(Attribute::AttributeIteratorOnVertexMap::iterator it = attributeIteratorsOnVertex.begin(); it != attributeIteratorsOnVertex.end(); ++it) {
      for(Attribute::AttributeIteratorList::iterator it2 = it->second->begin(); it2 != it->second->end(); ++it2) {
        (*it2)->invalidate();
      }
      delete it->second;
    }
    attributeIteratorsOnVertex.clear();

    for(Attribute::AttributeIteratorOnEdgeMap::iterator it = attributeIteratorsOnEdge.begin(); it != attributeIteratorsOnEdge.end(); ++it) {
      for(Attribute::AttributeIteratorList::iterator it2 = it->second->begin(); it2 != it->second->end(); ++it2) {
        (*it2)->invalidate();
      }
      delete it->second;
    }
    attributeIteratorsOnEdge.clear();
    
    for(EdgeIteratorOnNodeMap::iterator it = edgeIteratorOnNode.begin(); it != edgeIteratorOnNode.end(); ++it) {
      for(EdgeIteratorList::iterator it2 = it->second->begin(); it2 != it->second->end(); ++it2) {
        (*it2)->invalidate();
      }
      delete it->second;
    }
    edgeIteratorOnNode.clear();
    for(NodeIteratorList::iterator it = nodeIterators.begin(); it != nodeIterators.end(); ++it) {
      (*it)->invalidate();
    }
    nodeIterators.clear();

  }

  void addAttributeFromEdgeToEdge(Edge& from, Edge& to) {
    Attribute::AttributeIterator attrIt = from.getAttributes();
    while(attrIt.hasNext()) {
      Attribute& attr = attrIt.next();
      to.addAttribute(attr);
    }
  }


  void Graph::copyGraph(const Graph& graph) {
    // node-k atepitese az uj grafba
    Node::NodeIterator nodes = const_cast<Graph&>(graph).getNodes();
    while(nodes.hasNext()) {
      Node node = nodes.next();
      addNode(node);
    }
    // elek atepitese az uj grafba
  
    set<GraphEdge> addedEdges;
    
    nodes = const_cast<Graph&>(graph).getNodes();
    while(nodes.hasNext()) {
      Node node = nodes.next();
      Edge::EdgeIterator outEdges = node.getOutEdges();
      while(outEdges.hasNext()) {
        Edge edge = outEdges.next();

        if(addedEdges.find(edge.edge) != addedEdges.end())
          continue;
        // get edge inform
        Edge::EdgeType edgeType = edge.getType();
        if(edgeType.getDirectionType() == Edge::edtReverse)
          continue;
        string fromNodeUID = edge.getFromNode().getUID();
        string toNodeUID = edge.getToNode().getUID();
        Edge reversePair = edge.getReversePair();

        

        switch(edgeType.getDirectionType()) {
          case Edge::edtBidirectional:
            {
              // add edge
              Edge addedEdge = createBidirectedEdge(fromNodeUID, toNodeUID, edgeType.getType());
              addAttributeFromEdgeToEdge(edge, addedEdge);
              // add edge pair attributes ....
              Edge addedEdgeReversePair = addedEdge.getReversePair();
              addAttributeFromEdgeToEdge(reversePair, addedEdgeReversePair);
              addedEdges.insert(reversePair.edge);
              break;
            }
          case Edge::edtDirectional:
            {
              // add edge
              
              if(reversePair == invalidEdge) {
                Edge addedEdge = createDirectedEdge(fromNodeUID, toNodeUID, edgeType.getType(), false );
                addAttributeFromEdgeToEdge(edge, addedEdge);
              }
              else {
                Edge addedEdge = createDirectedEdge(fromNodeUID, toNodeUID, edgeType.getType(), true );
                addAttributeFromEdgeToEdge(edge, addedEdge);
                Edge addedEdgeReversePair = addedEdge.getReversePair();
                addAttributeFromEdgeToEdge(reversePair, addedEdgeReversePair);
                addedEdges.insert(reversePair.edge);
              }
              break;
            }
          default:
            break;
        }
        addedEdges.insert(edge.edge);
        
      }
    }
  }

  Graph::Graph(const Graph& graph) 
    : attributeIteratorsOnVertex()
    , attributeIteratorsOnEdge()
    , edgeIteratorOnNode()
    , nodeIterators()
    , headerInformations (graph.headerInformations)
    , g(new BGraph())
    , strTable(new StrTable(*graph.strTable))
    , nodeUIDs()
    , edgePairMap()
    , gsReader(new GraphSchemaReader(*graph.gsReader))
  {
    copyGraph(graph);
  }

  Graph& Graph::operator=(const Graph& graph) {
    delete g;
    delete gsReader;
    delete strTable;
    g = new BGraph();
    strTable = new StrTable(*graph.strTable);
    gsReader = new GraphSchemaReader(*graph.gsReader);
    headerInformations = graph.headerInformations;

    clearHelperContaioners();
    copyGraph(graph);
    return *this;
  }

  Attribute::AttributeIteratorList* Graph::getAttributeIteratorOnVertex(GraphVertex vertex) {
    Attribute::AttributeIteratorOnVertexMap::iterator it = attributeIteratorsOnVertex.find(vertex);
    if(it == attributeIteratorsOnVertex.end()) {
      Attribute::AttributeIteratorList* attributeList = new Attribute::AttributeIteratorList();
      attributeIteratorsOnVertex.insert(make_pair(vertex, attributeList));
      return attributeList;
    } else {
      return it->second;
    }
  }

  void Graph::removeAttributeIteratorOnVertexContainer(GraphVertex vertex) {
    Attribute::AttributeIteratorOnVertexMap::iterator it = attributeIteratorsOnVertex.find(vertex);
    if (it != attributeIteratorsOnVertex.end()) {
      for(Attribute::AttributeIteratorList::iterator listIt = it->second->begin(); listIt != it->second->end(); ++listIt) {
        (*listIt)->invalidate();
      }
      delete it->second;
      attributeIteratorsOnVertex.erase(it);
    }
  }

  Attribute::AttributeIteratorList* Graph::getAttributeIteratorOnEdge(GraphEdge edge) {
    Attribute::AttributeIteratorOnEdgeMap::iterator it = attributeIteratorsOnEdge.find(edge);
    if(it == attributeIteratorsOnEdge.end()) {
      Attribute::AttributeIteratorList* attributeList = new Attribute::AttributeIteratorList();
      attributeIteratorsOnEdge.insert(make_pair(edge,attributeList));
      return attributeList;
    } else {
      return it->second;
    }
  }

  void Graph::removeAttributeIteratorOnEdgeContainer(GraphEdge edge) {
    Attribute::AttributeIteratorOnEdgeMap::iterator it = attributeIteratorsOnEdge.find(edge);
    if (it != attributeIteratorsOnEdge.end()) {
      for(Attribute::AttributeIteratorList::iterator listIt = it->second->begin(); listIt != it->second->end(); ++listIt) {
        (*listIt)->invalidate();
      }
      delete it->second;
      attributeIteratorsOnEdge.erase(it);
    }
  }

  Graph::EdgeIteratorList* Graph::getEdgeIteratorOnNode(GraphVertex vertex) {
    EdgeIteratorOnNodeMap::iterator it = edgeIteratorOnNode.find(vertex);
    if(it == edgeIteratorOnNode.end()) {
      EdgeIteratorList* edgeList = new EdgeIteratorList();
      edgeIteratorOnNode.insert(make_pair(vertex,edgeList));
      return edgeList;
    } else {
      return it->second;
    }
  }

  void Graph::removeEdgeIteratorContainer(GraphVertex vertex) {
    EdgeIteratorOnNodeMap::iterator it = edgeIteratorOnNode.find(vertex);
    if (it != edgeIteratorOnNode.end()) {
      for(EdgeIteratorList::iterator listIt = it->second->begin(); listIt != it->second->end(); ++listIt) {
        (*listIt)->invalidate();
      }
      delete it->second;
      edgeIteratorOnNode.erase(it);
    }
  }


  Graph::NodeIteratorList* Graph::getNodeIterators() {
    return &nodeIterators;
  }

  Node Graph::createNode(const string& UID, const Node::NodeType& NTYPE){

    if(!gsReader->canAddNode(NTYPE.getType())) 
      throw GraphSchemaException( COLUMBUS_LOCATION, CMSG_EX_CANT_ADD_TYPE( NTYPE.getType()));


    Key UIDKey = strTable->set(UID);
    KeyMap::iterator it = nodeUIDs.find(UIDKey);
    if(it != nodeUIDs.end() ) {
      throw AlreadyExist( COLUMBUS_LOCATION, CMSG_EX_NODE_ALREADY_EXIST_WITH_ID(UID));
    } 

    AttributeList *elementAttr = new AttributeList();
    VertexAttributes vertexAttr(elementAttr);
    VertexType vertexType( strTable->set(NTYPE.getType()) ,vertexAttr);
    VertexProperty vertexProperty(UIDKey, vertexType);    
    GraphVertex vertex = add_vertex(vertexProperty,*g);

    nodeUIDs.insert(make_pair(UIDKey,vertex));

    return Node(this,vertex);

  }

  Node Graph::createNode(Key UIDKey, Key NTYPEKey){

    KeyMap::iterator it = nodeUIDs.find(UIDKey);
    if(it != nodeUIDs.end() ) {
      throw AlreadyExist( COLUMBUS_LOCATION, CMSG_EX_NODE_ALREADY_EXIST_WITH_ID(strTable->get(UIDKey)));
    } 

    AttributeList *elementAttr = new AttributeList();
    VertexAttributes vertexAttr(elementAttr);
    VertexType vertexType(NTYPEKey, vertexAttr);
    VertexProperty vertexProperty(UIDKey, vertexType);    
    GraphVertex vertex = add_vertex(vertexProperty, *g);

    nodeUIDs.insert(make_pair(UIDKey,vertex));

    return Node(this,vertex);
  }


  Node Graph::createNode(const char* UID, const char* NTYPE) {
    return createNode(string(UID), string(NTYPE));
  }

  Node Graph::addNode(const Node& node) {
    if(!gsReader->canAddNode(node.getType().getType()))
      throw GraphSchemaException( COLUMBUS_LOCATION, CMSG_EX_CANT_ADD_TYPE( node.getType().getType()));

    const string& UID = node.getUID();
    Key UIDKey = strTable->set(UID);
    KeyMap::iterator it = nodeUIDs.find(UIDKey);
    if(it != nodeUIDs.end() ) {
      throw AlreadyExist( COLUMBUS_LOCATION, CMSG_EX_NODE_ALREADY_EXIST_WITH_ID(UID));
    }

    AttributeList *elementAttr = new AttributeList();

    // copy node attributes to this node
    Attribute::AttributeIterator attrIt = node.getAttributes();
    while(attrIt.hasNext()) {
      Attribute& attribute = attrIt.next();
      Attribute *attr = attribute.copy();
      if(attribute.graph != this) {
        attr->setGraph(this);
        attr->copyStrings(attribute.graph->getStrTable(),getStrTable());
      }
      elementAttr->push_back(attr);
    }

    VertexAttributes vertexAttr(elementAttr);
    VertexType vertexType( strTable->set(node.getType().getType()) ,vertexAttr);
    VertexProperty vertexProperty(UIDKey,vertexType);
    GraphVertex vertex = add_vertex(vertexProperty,*g);

    nodeUIDs.insert(make_pair(UIDKey,vertex));

    return Node(this,vertex);

  }


  void Graph::clear_node(const GraphVertex& node) {
    edge_iter edge_end, edge_it;
    boost::tie(edge_it, edge_end) = edges(*g);
    while(edge_it != edge_end) {
      edge_iter edge_it_del = edge_it;
      ++edge_it;
      if(source(*edge_it_del, *g) == node || target(*edge_it_del, *g) == node) {
        edgePairMap.erase(*edge_it_del);
        delete_edge(*edge_it_del);
      }
    }
  }

  bool Graph::deleteNode(const string& UID) {
    Key UIDKey = strTable->set(UID);
    KeyMap::iterator it = nodeUIDs.find(UIDKey);
    if(it == nodeUIDs.end() ) {
      return false;
    }
    deleteIteratorContainerFromNode(it->second);
    // delete node attributes

    AttributeList *node_attr = getAttributeList(it->second);
    for(AttributeList::iterator it = node_attr->begin(); it != node_attr->end(); it++) {
      delete *it;
    }
    delete node_attr;
    clear_node(it->second);
    remove_vertex(it->second, *g);
    nodeUIDs.erase(it);
    // What happens with the edges?????? (PEPE)
    return true;
  }

  bool Graph::deleteNode(const Node& node) {
    return deleteNode(node.getUID());
  }

  bool Graph::deleteNode(const Node::NodeType& NTYPE) {
    bool deleted = false;

    IndexMapVertexTypes types = get(vertex_type,*g);
    IndexMapVertexUIDs uids = get(vertex_UID,*g);

    vertex_iter vi, vi_end, next;
    boost::tie(vi, vi_end) = vertices(*g);

    for (next = vi; vi != vi_end; vi = next) {
      
      next++;

      if( types[*vi] == strTable->set(NTYPE.getType()) ) {
        AttributeList *attributes = getAttributeList(*vi);
        deleteIteratorContainerFromNode(*vi);
        for(AttributeList::iterator it = attributes->begin(); it != attributes->end(); it++) {
          Attribute *attr = *it;
          delete attr;
        }
        delete attributes;

        nodeUIDs.erase(uids[*vi]);

        clear_node(*vi);
        remove_vertex(*vi, *g);
        deleted = true;
      }
    }
    return deleted;

  }

  BGraph* Graph::getBGraph() const{
    return g;
  }

  StrTable* Graph::getStrTable() const {
    return strTable;
  }

  const string& Graph::getVertexUID(const GraphVertex& vertex) const {
    return getStrTable()->get( get(vertex_UID,*getBGraph(),vertex) );
  }

  void Graph::setVertexUID(const GraphVertex& vertex, const string& uid) {
    KeyMap::iterator it = nodeUIDs.find(getStrTable()->get(uid));
    if(it != nodeUIDs.end()) {
      throw AlreadyExist( COLUMBUS_LOCATION, CMSG_EX_NODE_ALREADY_EXIST_WITH_ID( uid));
    }
    Key& uidKey = get(vertex_UID,*getBGraph(),vertex);
    it = nodeUIDs.find(uidKey);
    if(it != nodeUIDs.end()) {
      nodeUIDs.erase(it);
    }
    uidKey = getStrTable()->set(uid);
    nodeUIDs.insert(make_pair(uidKey, vertex));
  }


  const Node::NodeType Graph::getVertexType(const GraphVertex& vertex) const {
    return Node::NodeType(getStrTable()->get( get(vertex_type,*getBGraph(),vertex) ));
  }

  AttributeList* Graph::getAttributeList(const GraphVertex& vertex) const {
    return get(vertex_attributes,*getBGraph(),vertex);
  }

  const Edge::EdgeType Graph::getEdgeType(const GraphEdge& edge) const {
    return Edge::EdgeType(getStrTable()->get( get(edge_type,*getBGraph(),edge) ),(Edge::eDirectionType)get(edge_direction,*getBGraph(),edge) );
  }

  AttributeList* Graph::getAttributeList(const GraphEdge& edge) const {
    return get(edge_attributes,*getBGraph(),edge);
  }

  GraphEdge Graph::createEdge(GraphVertex fromVertex, GraphVertex toVertex, const string& type, Edge::eDirectionType directionType) {
    return createEdge(fromVertex, toVertex, strTable->set(type), directionType);
  }

  GraphEdge Graph::createEdge(GraphVertex fromVertex, GraphVertex toVertex, Key typeKey, Edge::eDirectionType directionType) {
    
    AttributeList *elementAttr = new AttributeList();
    EdgeAttributes edgeAttr(elementAttr);
    EdgeDirection edgeDirection(directionType,elementAttr);
    EdgeProperty edgeProperty(typeKey ,edgeDirection);
    GraphEdge edge;
    bool isAdded;
    boost::tie(edge,isAdded) = add_edge(fromVertex, toVertex, edgeProperty, *g);
    return edge;
  }

  Edge Graph::createReservePair(const Edge& edge) {
    GraphVertex fromVertex = edge.getToNode().vertex;
    GraphVertex toVertex = edge.getFromNode().vertex;
    string type = edge.getType().getType();
    GraphEdge g_edge,revEdge;
    g_edge = edge.edge;
    revEdge = createEdge(fromVertex,toVertex,type,Edge::edtReverse);
    edgePairMap.insert(make_pair(g_edge,revEdge));
    edgePairMap.insert(make_pair(revEdge,g_edge));
    return Edge(this,revEdge);
  }

  void Graph::convertEdgeToBidirectional(Edge& edge) {
    Edge newEdge = createBidirectedEdge(edge.getFromNode(), edge.getToNode(), edge.getType().getType());
    Edge oldEdgePair = edge.getReversePair();
    Attribute::AttributeIterator attrIt = edge.getAttributes();
    while(attrIt.hasNext()) {
      Attribute& attr = attrIt.next();
      newEdge.addAttribute(attr);
    }
    if(!(oldEdgePair == invalidEdge)) {
      attrIt = oldEdgePair.getAttributes();
      Edge newEdgePair = newEdge.getReversePair();
      while(attrIt.hasNext()) {
        Attribute& attr = attrIt.next();
        newEdgePair.addAttribute(attr);
      }
    }
    deleteEdge(edge);
    edge = newEdge;
  }

  void Graph::convertEdgeToDirectionalWithReverse(Edge& edge) {
    Edge newEdge = createDirectedEdge(edge.getFromNode(), edge.getToNode(), edge.getType().getType(), true);
    Edge oldEdgePair = edge.getReversePair();
    Attribute::AttributeIterator attrIt = edge.getAttributes();
    while(attrIt.hasNext()) {
      Attribute& attr = attrIt.next();
      newEdge.addAttribute(attr);
    }
    if(!(oldEdgePair == invalidEdge)) {
      attrIt = oldEdgePair.getAttributes();
      Edge newEdgePair = newEdge.getReversePair();
      while(attrIt.hasNext()) {
        Attribute& attr = attrIt.next();
        newEdgePair.addAttribute(attr);
      }
    }
    deleteEdge(edge);
    edge = newEdge;
  }


  Edge Graph::createDirectedEdge(const Node& from, const Node& to, const string& type, bool createReverse) {

    if(!gsReader->canAddEdge(type, Edge::edtDirectional, from.getType().getType(), to.getType().getType() ))
      throw GraphSchemaException( COLUMBUS_LOCATION, CMSG_EX_CANT_ADD_DIRECTIONAL( type, from.getType().getType(), to.getType().getType()));

    GraphVertex fromVertex = from.vertex;
    GraphVertex toVertex = to.vertex;
    
    GraphEdge edge,revEdge;
    edge = createEdge(fromVertex,toVertex,type,Edge::edtDirectional);
    
    if(createReverse) {
      if(!gsReader->canAddEdge(type, Edge::edtReverse, to.getType().getType(), from.getType().getType()) )
        throw GraphSchemaException( COLUMBUS_LOCATION, CMSG_EX_CANT_ADD_REVERSE( type, to.getType().getType(), from.getType().getType()));
      revEdge = createEdge(toVertex,fromVertex,type,Edge::edtReverse);
      edgePairMap.insert(make_pair(edge,revEdge));
      edgePairMap.insert(make_pair(revEdge,edge));

    }
    return Edge(this,edge);
  }

  Edge Graph::createDirectedEdge(const Node& from, const Node& to, Key typeKey, bool createReverse) {


    GraphVertex fromVertex = from.vertex;
    GraphVertex toVertex = to.vertex;
    
    GraphEdge edge,revEdge;
    edge = createEdge(fromVertex, toVertex, typeKey, Edge::edtDirectional);
    
    if(createReverse) {
      revEdge = createEdge(toVertex, fromVertex, typeKey, Edge::edtReverse);
      edgePairMap.insert(make_pair(edge,revEdge));
      edgePairMap.insert(make_pair(revEdge,edge));

    }
    return Edge(this,edge);
  }


  Edge Graph::createDirectedEdge(const string& fromUID, const string& toUID, const string& type, bool createReverse) {

    GraphVertex fromVertex, toVertex;
    KeyMap::iterator fromIt,toIt;

    fromIt = nodeUIDs.find(strTable->get(fromUID));
    toIt = nodeUIDs.find(strTable->get(toUID));

    if( (fromIt != nodeUIDs.end()) && (toIt != nodeUIDs.end()) ) {
      GraphEdge edge,revEdge;
      fromVertex = fromIt->second;
      toVertex = toIt->second;
      if(!gsReader->canAddEdge(type, Edge::edtDirectional, strTable->get(get(vertex_type,*getBGraph(),fromVertex)), strTable->get(get(vertex_type,*getBGraph(),toVertex))))
        throw GraphSchemaException( COLUMBUS_LOCATION, CMSG_EX_CANT_ADD_DIRECTIONAL( type, strTable->get(get(vertex_type,*getBGraph(),fromVertex)),strTable->get(get(vertex_type,*getBGraph(),toVertex))));
      edge = createEdge(fromVertex,toVertex,type,Edge::edtDirectional);
    
      if(createReverse) {
        if(!gsReader->canAddEdge(type, Edge::edtDirectional, strTable->get(get(vertex_type,*getBGraph(),fromVertex)), strTable->get(get(vertex_type,*getBGraph(),toVertex))))
          throw GraphSchemaException( COLUMBUS_LOCATION, CMSG_EX_CANT_ADD_REVERSE( type, strTable->get(get(vertex_type,*getBGraph(),toVertex)),strTable->get(get(vertex_type,*getBGraph(),fromVertex))));
        revEdge = createEdge(toVertex,fromVertex,type,Edge::edtReverse);
        edgePairMap.insert(make_pair(edge,revEdge));
        edgePairMap.insert(make_pair(revEdge,edge));
      }
      return Edge(this,edge);
    }
    return invalidEdge;

  }

  Edge Graph::createBidirectedEdge(const Node& from, const Node& to, const string& type) {
    if(!gsReader->canAddEdge(type, Edge::edtBidirectional, from.getType().getType(), to.getType().getType() ))
      throw GraphSchemaException( COLUMBUS_LOCATION, CMSG_EX_CANT_ADD_BIDIRECTIONAL( type, from.getType().getType(), to.getType().getType()));

    GraphVertex fromVertex = from.vertex, toVertex = to.vertex;
    GraphEdge edge = createEdge(fromVertex,toVertex,type,Edge::edtBidirectional);
    GraphEdge revEdge = createEdge(toVertex,fromVertex,type,Edge::edtBidirectional);
    edgePairMap.insert(make_pair(edge,revEdge));
    edgePairMap.insert(make_pair(revEdge,edge));
    return Edge(this,edge);
  }


  Edge Graph::createBidirectedEdge(const Node& from, const Node& to, Key typeKey) {

    GraphVertex fromVertex = from.vertex, toVertex = to.vertex;
    GraphEdge edge = createEdge(fromVertex,toVertex, typeKey, Edge::edtBidirectional);
    GraphEdge revEdge = createEdge(toVertex,fromVertex, typeKey, Edge::edtBidirectional);
    edgePairMap.insert(make_pair(edge,revEdge));
    edgePairMap.insert(make_pair(revEdge,edge));
    return Edge(this,edge);
  }


  Edge Graph::createBidirectedEdge(const string& fromUID, const string& toUID, const string& type) {

    GraphVertex fromVertex, toVertex;
    KeyMap::iterator fromIt,toIt;

    fromIt = nodeUIDs.find(strTable->get(fromUID));
    toIt = nodeUIDs.find(strTable->get(toUID));
    if( (fromIt != nodeUIDs.end()) && (toIt != nodeUIDs.end()) ) {
      GraphEdge edge,revEdge;
      fromVertex = fromIt->second;
      toVertex = toIt->second;
      if(!gsReader->canAddEdge(type, Edge::edtBidirectional, strTable->get(get(vertex_type,*getBGraph(),fromVertex)), strTable->get(get(vertex_type,*getBGraph(),toVertex))))
        throw GraphSchemaException( COLUMBUS_LOCATION, CMSG_EX_CANT_ADD_DIRECTIONAL( type, strTable->get(get(vertex_type,*getBGraph(),fromVertex)),strTable->get(get(vertex_type,*getBGraph(),toVertex))));

      edge = createEdge(fromVertex,toVertex,type,Edge::edtBidirectional);
      revEdge = createEdge(toVertex,fromVertex,type,Edge::edtBidirectional);
      edgePairMap.insert(make_pair(edge,revEdge));
      edgePairMap.insert(make_pair(revEdge,edge));
      return Edge(this,edge);
    }
    return invalidEdge;
  }

  Node Graph::findNode(const string& UID) {
    Key UIDKey = strTable->get(UID);
    if(UIDKey == 0) return invalidNode;

    KeyMap::iterator it = nodeUIDs.find(UIDKey);
    if(it == nodeUIDs.end() ) {
      return invalidNode;
    }
    return Node(this,it->second);
  }

  Node::NodeIterator Graph::findNodes(const Node::NodeType& NTYPE) {
    vertex_iter n_begin,n_end;
    boost::tie(n_begin,n_end) = vertices(*g);
    Node::NodeTypeSet nts;
    nts.insert(NTYPE);
    return Node::NodeIterator(n_begin,n_end,getNodeIterators(),this,nts);
  }

  Node::NodeIterator Graph::findNodes(const Node::NodeTypeSet& NTS) {
    vertex_iter n_begin,n_end;
    boost::tie(n_begin,n_end) = vertices(*g);
    return Node::NodeIterator(n_begin,n_end,getNodeIterators(),this,NTS);
  }

  bool Graph::nodeIsExist(const string& UID) {
    Key UIDKey = strTable->set(UID);
    KeyMap::iterator it = nodeUIDs.find(UIDKey);
    if(it == nodeUIDs.end() ) {
      return false;
    }
    return true;
  }


  void Graph::deleteIteratorContainerFromEdge(const GraphEdge& edge) {
    removeAttributeIteratorOnEdgeContainer(edge);
  }

  void Graph::deleteIteratorContainerFromNode(const GraphVertex& node) {
    removeAttributeIteratorOnVertexContainer(node);
    removeEdgeIteratorContainer(node);
  }


  void Graph::delete_edge(const GraphEdge& edge) {
    AttributeList *edge_attr = getAttributeList(edge);
    deleteIteratorContainerFromEdge(edge);
    for(AttributeList::iterator it = edge_attr->begin(); it != edge_attr->end(); it++) {
      delete *it;
    }
    delete edge_attr;
    remove_edge(edge, *g);
  }

  void Graph::deleteEdge(const Edge& edge) {
    delete_edge(edge.edge);
    // remove edge pair
    if(hasEdgePair(edge.edge)) {
      GraphEdge edgePair = getEdgePair(edge.edge);
      delete_edge(edgePair);
      edgePairMap.erase(edge.edge);
      edgePairMap.erase(edgePair);
    }
  }

  void Graph::deleteEdge(const Edge::EdgeType& type) {
    IndexMapEdgeTypes edgeTypes = get(edge_type,*g);
    IndexMapEdgeDirection edgeDirections = get(edge_direction,*g);
    Key typeKey = strTable->get(type.getType());
    edge_iter it,edge_begin,edge_end;
    boost::tie(edge_begin, edge_end) = edges(*g);
    for(it = edge_begin; it != edge_end;) {
      edge_iter del_it = it;
      ++it;
      if( (typeKey == edgeTypes[*del_it]) && (static_cast<int>(type.getDirectionType()) == edgeDirections[*del_it]) ) {

        // get edge pair
        if( hasEdgePair(*del_it) && ( (edgeDirections[*del_it] == static_cast<int>(Edge::edtBidirectional)) || 
           (edgeDirections[*del_it] == static_cast<int>(Edge::edtDirectional)) ) ) {
          // remove edge pair
          GraphEdge edgePair = getEdgePair(*del_it);
          if(*it == edgePair) {
            ++it;
          }
          delete_edge(edgePair);
          edgePairMap.erase(*del_it);
          edgePairMap.erase(edgePair);
        }
        delete_edge(*del_it);
      }
    }
  }

  void Graph::deleteEdge(const Node& from, const Node& to) {
    IndexMapEdgeDirection edgeDirections = get(edge_direction,*g);
    out_edge_iter it,e_begin, e_end;
    boost::tie(e_begin, e_end) = out_edges(from.vertex, *getBGraph());
    for(it = e_begin; it != e_end;) {
      GraphVertex toNode = target(*it, *getBGraph());
      if(toNode == to.vertex) {

        out_edge_iter deletable_it = it;

        if( hasEdgePair(*it) && ( (edgeDirections[*it] == static_cast<int>(Edge::edtBidirectional)) ||
           (edgeDirections[*it] == static_cast<int>(Edge::edtDirectional)) ) ) {
          GraphEdge edgePair = getEdgePair(*it);
          delete_edge(edgePair);
          edgePairMap.erase(*it);
          edgePairMap.erase(edgePair);
        }
        ++it;
        delete_edge(*deletable_it);
        
      } else {
        ++it;
      }
    }
  }

  GraphEdge Graph::getEdgePair(GraphEdge edge) const {
    EdgePairMap::const_iterator it = edgePairMap.find(edge);
    if(it != edgePairMap.end() ) {
      return it->second;
    } else {
      throw EdgeNotFound("Graph::getEdgePair(GraphEdge edge)","Edge pair not found!");
    }
  }

  bool Graph::hasEdgePair(GraphEdge edge) const {
    EdgePairMap::const_iterator it = edgePairMap.find(edge);
    if(it != edgePairMap.end() ) {
      return true;
    } else {
      return false;
    }
  }

  void Graph::traverseBreadthFirst(const Node& startNode, const Edge::EdgeTypeSet& edges, 
      nodeVisitorCallback nodeVisitorFunc, edgeVisitorCallback edgeVisitorFunc, void* data) {

    set<GraphVertex> visitedVertexes;
    queue<GraphVertex> next;
    next.push(startNode.vertex);

    while(!next.empty()) {
      GraphVertex vertex = next.front();
      next.pop();
      if(visitedVertexes.find(vertex) != visitedVertexes.end())
        continue;
      visitedVertexes.insert(vertex);
      Node node(this,vertex);
      
      if (nodeVisitorFunc != NULL)
        nodeVisitorFunc(node, data);
      
      Edge::EdgeIterator edgeIt = node.findOutEdges(edges);
      while(edgeIt.hasNext()) {
        Edge edge = edgeIt.next();
        if (edgeVisitorFunc != NULL)
          edgeVisitorFunc(edge, data);
        next.push(edge.getToNode().vertex);
      }
    }

  }

  void Graph::traverseDepthFirstPostorder(const Node& startNode, const Edge::EdgeTypeSet& edges, 
    nodeVisitorCallback nodeVisitorFunc, edgeVisitorCallback edgeVisitorFunc, void* data) {

    set<GraphVertex> visitedVertexes;

    traverseDepthFirstPostorder(startNode,edges,nodeVisitorFunc,edgeVisitorFunc,visitedVertexes, data);
  }

  void Graph::traverseDepthFirstPostorder(const Node& node, const Edge::EdgeTypeSet& edges, 
    nodeVisitorCallback nodeVisitorFunc, edgeVisitorCallback edgeVisitorFunc,set<GraphVertex>& visitedVertexes, void* data) 
  {
    if(visitedVertexes.find(node.vertex) != visitedVertexes.end() ) {
      return;
    }
    visitedVertexes.insert(node.vertex);
    Edge::EdgeIterator edgeIt = node.findOutEdges(edges);
    // warning elkerulese miatt
    GraphVertex tempVertex = node.vertex;
    bool setNode = false;
    while(edgeIt.hasNext()) {
      Edge edge = edgeIt.next();
      if(!setNode) {
        tempVertex = edge.getToNode().vertex;
        setNode = true;
      }
      if(!edgeIt.hasNext()) {
        if( (edge.getToNode().vertex != tempVertex) ) {
          traverseDepthFirstPostorder(Node(this,tempVertex),edges,nodeVisitorFunc,edgeVisitorFunc,visitedVertexes, data);
        }
        if (edgeVisitorFunc != NULL)
          edgeVisitorFunc(edge, data);
        traverseDepthFirstPostorder(edge.getToNode(),edges,nodeVisitorFunc,edgeVisitorFunc,visitedVertexes, data);
      } else {
        if( (edge.getToNode().vertex == tempVertex)) {
          if (edgeVisitorFunc != NULL)
            edgeVisitorFunc(edge, data);
        } else {
          traverseDepthFirstPostorder(Node(this,tempVertex),edges,nodeVisitorFunc,edgeVisitorFunc,visitedVertexes, data);
          if (edgeVisitorFunc != NULL)
            edgeVisitorFunc(edge, data);
          tempVertex = edge.getToNode().vertex;
        }
      }
    }

    if (nodeVisitorFunc != NULL)
      nodeVisitorFunc(node, data);

  }


  void Graph::traverseDepthFirstPreorder(const Node& startNode, const Edge::EdgeTypeSet& edges, 
    nodeVisitorCallback nodeVisitorFunc, edgeVisitorCallback edgeVisitorFunc, void* data) {

    set<GraphVertex> visitedVertexes;

    traverseDepthFirstPreorder(startNode,edges,nodeVisitorFunc,edgeVisitorFunc,visitedVertexes, data);
  }

  void Graph::traverseDepthFirstPreorder(const Node& node, const Edge::EdgeTypeSet& edges, 
    nodeVisitorCallback nodeVisitorFunc, edgeVisitorCallback edgeVisitorFunc,set<GraphVertex>& visitedVertexes, void* data) 
  {
    if(visitedVertexes.find(node.vertex) != visitedVertexes.end() ) {
      return;
    }
    if (nodeVisitorFunc != NULL)
      nodeVisitorFunc(node, data);
    visitedVertexes.insert(node.vertex);
    Edge::EdgeIterator edgeIt = node.findOutEdges(edges);
    // warning elkerulese miatt
    GraphVertex tempVertex = node.vertex;
    bool setNode = false;
    while(edgeIt.hasNext()) {
      Edge edge = edgeIt.next();
      if(!setNode) {
        tempVertex = edge.getToNode().vertex;
        setNode = true;
      }
      if(!edgeIt.hasNext()) {
        if( (edge.getToNode().vertex != tempVertex) ) {
          traverseDepthFirstPreorder(Node(this,tempVertex),edges,nodeVisitorFunc,edgeVisitorFunc,visitedVertexes, data);
        }
        if (edgeVisitorFunc != NULL)
          edgeVisitorFunc(edge, data);
        traverseDepthFirstPreorder(edge.getToNode(),edges,nodeVisitorFunc,edgeVisitorFunc,visitedVertexes, data);
      } else {
        if( (edge.getToNode().vertex == tempVertex)) {
          if (edgeVisitorFunc != NULL)
            edgeVisitorFunc(edge, data);
        } else {
          traverseDepthFirstPreorder(Node(this,tempVertex),edges,nodeVisitorFunc,edgeVisitorFunc,visitedVertexes, data);
          if (edgeVisitorFunc != NULL)
            edgeVisitorFunc(edge, data);
          tempVertex = edge.getToNode().vertex;
        }
      }
    }

  }


  void Graph::traverseDepthFirst(const Node& startNode, const Edge::EdgeTypeSet& edges, 
    nodeVisitorCallback nodeVisitorFuncPre, nodeVisitorCallback nodeVisitorFuncPost, edgeVisitorCallback edgeVisitorFunc, void* data) {

    set<GraphVertex> visitedVertexes;

    traverseDepthFirst(startNode,edges,nodeVisitorFuncPre,nodeVisitorFuncPost,edgeVisitorFunc,visitedVertexes, data);
  }

  void Graph::traverseDepthFirst(const Node& node, const Edge::EdgeTypeSet& edges, 
    nodeVisitorCallback nodeVisitorFuncPre, nodeVisitorCallback nodeVisitorFuncPost, edgeVisitorCallback edgeVisitorFunc,set<GraphVertex>& visitedVertexes, void *data) {
    
    if(visitedVertexes.find(node.vertex) != visitedVertexes.end() ) {
      return;
    }

    if (nodeVisitorFuncPre != NULL)
      nodeVisitorFuncPre(node, data);

    visitedVertexes.insert(node.vertex);
    Edge::EdgeIterator edgeIt = node.findOutEdges(edges);
    // warning elkerulese miatt
    GraphVertex tempVertex = node.vertex;
    bool setNode = false;
    while(edgeIt.hasNext()) {
      Edge edge = edgeIt.next();
      if(!setNode) {
        tempVertex = edge.getToNode().vertex;
        setNode = true;
      }
      if(!edgeIt.hasNext()) {
        if( (edge.getToNode().vertex != tempVertex) ) {
          traverseDepthFirst(Node(this,tempVertex),edges,nodeVisitorFuncPre,nodeVisitorFuncPost,edgeVisitorFunc,visitedVertexes, data);
        }
        if (edgeVisitorFunc != NULL)
          edgeVisitorFunc(edge, data);
        traverseDepthFirst(edge.getToNode(),edges,nodeVisitorFuncPre,nodeVisitorFuncPost,edgeVisitorFunc,visitedVertexes, data);
      } else {
        if( (edge.getToNode().vertex == tempVertex)) {
          if (edgeVisitorFunc != NULL)
            edgeVisitorFunc(edge, data);
        } else {
          traverseDepthFirst(Node(this,tempVertex),edges, nodeVisitorFuncPre,nodeVisitorFuncPost,edgeVisitorFunc,visitedVertexes, data);
          if (edgeVisitorFunc != NULL)
            edgeVisitorFunc(edge, data);
          tempVertex = edge.getToNode().vertex;
        }
      }
    }
    if (nodeVisitorFuncPost != NULL)
      nodeVisitorFuncPost(node, data);
  }


  void Graph::writeAttributeToXml(Attribute& attribute,SimpleXmlIO& sio) const {
    switch(attribute.getType()) {
      case Attribute::atInt:
        {
          sio.writeBeginElement(XML_GRAPH_ATTR);
          sio.writeAttribute(XML_GRAPH_TYPE,"int");
          sio.writeAttribute(XML_GRAPH_NAME,((AttributeInt&)attribute).getName());
          sio.writeAttribute(XML_GRAPH_CONTEXT,((AttributeInt&)attribute).getContext());
          sio.writeAttribute(XML_GRAPH_VALUE, ((AttributeInt&)attribute).getValue());
          sio.writeEndElement();
          break;
        }
      case Attribute::atFloat:
        {
          sio.writeBeginElement(XML_GRAPH_ATTR);
          sio.writeAttribute(XML_GRAPH_TYPE,"float");
          sio.writeAttribute(XML_GRAPH_NAME,((AttributeFloat&)attribute).getName());
          sio.writeAttribute(XML_GRAPH_CONTEXT,((AttributeFloat&)attribute).getContext());
          sio.writeAttribute(XML_GRAPH_VALUE, ((AttributeFloat&)attribute).getValue());
          sio.writeEndElement();
          break;
        }
      case Attribute::atString:
        {
          sio.writeBeginElement(XML_GRAPH_ATTR);
          sio.writeAttribute(XML_GRAPH_TYPE,"string");
          sio.writeAttribute(XML_GRAPH_NAME,((AttributeString&)attribute).getName());
          sio.writeAttribute(XML_GRAPH_CONTEXT,((AttributeString&)attribute).getContext());
          sio.writeAttribute(XML_GRAPH_VALUE, ((AttributeString&)attribute).getValue());
          sio.writeEndElement();
          break;
        }
      case Attribute::atComposite:
        {
          sio.writeBeginElement(XML_GRAPH_ATTR);
          sio.writeAttribute(XML_GRAPH_TYPE,"composite");
          AttributeComposite& attrComp = (AttributeComposite&)attribute;
          sio.writeAttribute(XML_GRAPH_NAME, attrComp.getName());
          sio.writeAttribute(XML_GRAPH_CONTEXT, attrComp.getContext());
          // write out composite elements
          for(AttributeList::iterator it = attrComp.values->begin(); it != attrComp.values->end(); it++) {
            writeAttributeToXml(**it, sio);
          }
          sio.writeEndElement();
        }
      default:
        break;
    }
  }

  bool compareNodeByUID(Node n1, Node n2) {
    return (n1.getUID() <  n2.getUID());
  }

  void Graph::saveXML(const string& filename) const {
    set<GraphEdge> savedEdgePairs;
    SimpleXmlIO sio(filename,io::IOBase::omWrite);
    sio.writeXMLDeclaration("1.0","utf-8");
    sio.writeBeginElement(XML_GRAPH_ROOT);
    sio.writeBeginElement(XML_GRAPH_HEAD);
    for(StringMap::const_iterator it = headerInformations.begin(); it != headerInformations.end(); it++) {
      sio.writeBeginElement(XML_GRAPH_INFO);
      sio.writeAttribute(XML_GRAPH_NAME, strTable->get(it->first) );
      sio.writeAttribute(XML_GRAPH_VALUE, strTable->get(it->second) );
      sio.writeEndElement();
    }
    sio.writeEndElement();
    sio.writeBeginElement(XML_GRAPH_DATA);
    vertex_iter vertex_begin, vertex_end,vertex_it;
    boost::tie(vertex_begin,vertex_end) = vertices(*g);

    list<Node> nodeList;

    for(vertex_it = vertex_begin; vertex_it != vertex_end; vertex_it++) {
      nodeList.push_back( Node( const_cast<Graph*>(this),*vertex_it) );
    }

    nodeList.sort(compareNodeByUID);

    for(list<Node>::iterator it = nodeList.begin(); it != nodeList.end(); it++ ) {

      GraphVertex vertex = it->vertex;
      // write node
      sio.writeBeginElement(XML_GRAPH_NODE);
      sio.writeAttribute(XML_GRAPH_NAME, strTable->get(get(vertex_UID,*g,vertex) ) );
      sio.writeAttribute(XML_GRAPH_TYPE,strTable->get(get(vertex_type,*g,vertex) ) );
      AttributeList *vertex_attr = get(vertex_attributes,*g,vertex);
      // write attributes
      for(AttributeList::iterator it = vertex_attr->begin(); it != vertex_attr->end(); it++) {
        writeAttributeToXml(**it,sio);
      }
      // write out edges
      out_edge_iter edge_begin, edge_end, edge_it;
      boost::tie(edge_begin,edge_end) = out_edges(vertex,*g);
      for(edge_it = edge_begin; edge_it != edge_end; edge_it++) {
        if(get(edge_direction,*g,*edge_it) != Edge::edtReverse && savedEdgePairs.find(*edge_it) == savedEdgePairs.end() ) {
          sio.writeBeginElement(XML_GRAPh_EDGE);
          sio.writeAttribute(XML_GRAPH_TYPE, strTable->get(get(edge_type,*g,*edge_it) ) );
          switch(get(edge_direction,*g,*edge_it)) {
            case Edge::edtBidirectional:
              sio.writeAttribute(XML_GRAPH_DIRECTION,"bidirectional");
              break;
            case Edge::edtDirectional:
              sio.writeAttribute(XML_GRAPH_DIRECTION,"directional");
              break;
            default:
              break;
          }
          sio.writeAttribute(XML_GRAPH_EDGE_TO, strTable->get(get(vertex_UID,*g,target(*edge_it,*g) ) ) );
          // write reserve pair edge
          if(hasEdgePair(*edge_it)) {
            GraphEdge reservePair = getEdgePair(*edge_it);
            savedEdgePairs.insert(reservePair);
            sio.writeBeginElement(XML_GRAPH_EDGE_PAIR);
            AttributeList *edge_attr = get(edge_attributes,*g,reservePair);
            for(AttributeList::iterator it = edge_attr->begin(); it != edge_attr->end(); it++) {
              writeAttributeToXml(**it,sio);
            }
            sio.writeEndElement();
          }
          AttributeList *edge_attr = get(edge_attributes,*g,*edge_it);
          for(AttributeList::iterator it = edge_attr->begin(); it != edge_attr->end(); it++) {
            writeAttributeToXml(**it,sio);
          }
          sio.writeEndElement();
        }
      }
      // write node end
      sio.writeEndElement();
    }
    sio.writeEndElement();
    sio.writeEndElement();
    sio.close();
  }

  void Graph::loadXML(const string& filename) {
    GraphSchemaReader::TurnOffFilterSafety turnOffFilterSafety(*gsReader);
    // delete graph

    clear();

    GraphXmlHandler Handler(this);
    io::loadXml(filename,Handler);
  }

  void Graph::createGMLNode(SimpleXmlIO& sio, void* id, const string& name) const {
    sio.writeBeginElement("node");
    sio.writeAttribute("id", id);
      
      sio.writeBeginElement("data");
      sio.writeAttribute("key", "d0");
      
        sio.writeBeginElement("y:ShapeNode");
          
          sio.writeBeginElement("y:Shape");
          sio.writeAttribute(XML_GRAPH_TYPE, "rectangle");
          sio.writeEndElement();
          
          sio.writeBeginElement("y:NodeLabel");
          sio.writeAttribute("alignment", "center");
          sio.writeAttribute("autoSizePolicy", "content");
          sio.writeElementContent(name);
          sio.writeEndElement();
          
        sio.writeEndElement();
      sio.writeEndElement();
    sio.writeEndElement();
  }
  
  void Graph::createGMLEdge(SimpleXmlIO& sio, unsigned id , void* from, void* to, Edge::eDirectionType et, const string& name) const {
    sio.writeBeginElement("edge");
    sio.writeAttribute("id", (int)id);
    sio.writeAttribute("source", from);
    sio.writeAttribute("target", to);

      sio.writeBeginElement("data");
      sio.writeAttribute("key", "d2");

        sio.writeBeginElement("y:PolyLineEdge");

          switch (et) {
            case Edge::edtBidirectional:
              sio.writeBeginElement("y:LineStyle");
              sio.writeAttribute("color", "#000000");
              sio.writeAttribute("type", "line");
              sio.writeAttribute("width", "1.0");
              sio.writeEndElement();
              
              sio.writeBeginElement("y:Arrows");
              sio.writeAttribute("source", "standard");
              sio.writeAttribute("target", "standard");
              sio.writeEndElement();
              break;
            case Edge::edtDirectional:
              sio.writeBeginElement("y:LineStyle");
              sio.writeAttribute("color", "#000000");
              sio.writeAttribute("type", "line");
              sio.writeAttribute("width", "1.0");
              sio.writeEndElement();
              
              sio.writeBeginElement("y:Arrows");
              sio.writeAttribute("source", "none");
              sio.writeAttribute("target", "standard");
              sio.writeEndElement();
              break;
            
            case Edge::edtReverse:
              sio.writeBeginElement("y:LineStyle");
              sio.writeAttribute("color", "#D0D0D0");
              sio.writeAttribute("type", "dashed");
              sio.writeAttribute("width", "1.0");
              sio.writeEndElement();
              
              sio.writeBeginElement("y:Arrows");
              sio.writeAttribute("source", "none");
              sio.writeAttribute("target", "standard");
              sio.writeEndElement();
              break;
            default:
              break;
          }

          sio.writeBeginElement("y:EdgeLabel");
          sio.writeAttribute("textColor", et == Edge::edtReverse ? "#D0D0D0" : "#000000");
          sio.writeAttribute("visible", "true");
          sio.writeElementContent(name);
          sio.writeEndElement();

        sio.writeEndElement();      
      sio.writeEndElement();      
    
      sio.writeBeginElement("data");
      sio.writeAttribute("key", "d3");
      sio.writeEndElement();      
      
    sio.writeEndElement();      
  }

  void Graph::saveGML(const string& filename) const {
    SimpleXmlIO sio(filename, io::IOBase::omWrite);

    sio.writeXMLDeclaration("1.0", "utf-8");
    sio.writeBeginElement("graphml");
    sio.writeAttribute("xmlns", "http://graphml.graphdrawing.org/xmlns/graphml");
    sio.writeAttribute("xmlns:xsi", "http://www.w3.org/2001/XMLSchema-instance");
    sio.writeAttribute("xmlns:y", "http://www.yworks.com/xml/graphml");
    sio.writeAttribute("xsi:schemaLocation", "http://graphml.graphdrawing.org/xmlns/graphml http://www.yworks.com/xml/schema/graphml/1.0/ygraphml.xsd");
    
      sio.writeBeginElement("key");
      sio.writeAttribute("for", "node");
      sio.writeAttribute("id", "d0");
      sio.writeAttribute("yfiles.type", "nodegraphics");
      sio.writeEndElement();

      sio.writeBeginElement("key");
      sio.writeAttribute("attr.name", "description");
      sio.writeAttribute("attr.type", "string");
      sio.writeAttribute("for", "node");
      sio.writeAttribute("id", "d1");
      sio.writeEndElement();

      sio.writeBeginElement("key");
      sio.writeAttribute("for", "edge");
      sio.writeAttribute("id", "d2");
      sio.writeAttribute("yfiles.type", "edgegraphics");
      sio.writeEndElement();

      sio.writeBeginElement("key");
      sio.writeAttribute("attr.name", "description");
      sio.writeAttribute("attr.type", "string");
      sio.writeAttribute("for", "edge");
      sio.writeAttribute("id", "d3");
      sio.writeEndElement();

      sio.writeBeginElement("key");
      sio.writeAttribute("for", "graphml");
      sio.writeAttribute("id", "d4");
      sio.writeAttribute("yfiles.type", "resources");
      sio.writeEndElement();

      sio.writeBeginElement("graph");
      sio.writeAttribute("edgedefault", "directed");
      sio.writeAttribute("id", "G");

      vertex_iter vertex_begin;
      vertex_iter vertex_end;
      vertex_iter vertex_it;

      out_edge_iter edge_begin;
      out_edge_iter edge_end;
      out_edge_iter edge_it;

      boost::tie(vertex_begin, vertex_end) = vertices(*g);

      unsigned edge_counter = 0;
      set<GraphEdge> visitedEdges;


      // For every vertex
      for(vertex_it = vertex_begin; vertex_it != vertex_end; vertex_it++) {
        createGMLNode(sio, *vertex_it, strTable->get(get(vertex_type, *g, *vertex_it)));
        
        boost::tie(edge_begin, edge_end) = out_edges(*vertex_it, *g);
        
        // For every outgoing edges 
        for(edge_it = edge_begin; edge_it != edge_end; edge_it++, edge_counter++) {
          Edge::eDirectionType et = (Edge::eDirectionType)get(edge_direction, *g, *edge_it);
          
          if (et == Edge::edtBidirectional) {
            // Only one edge of the bidirectional edges are exported. 
            if (visitedEdges.find(edgePairMap.find(*edge_it)->second) == visitedEdges.end()) {
              createGMLEdge(sio, edge_counter, source(*edge_it, *g), target(*edge_it, *g), et, strTable->get(get(edge_type, *g, *edge_it)));
              visitedEdges.insert(*edge_it);
            }
          } else
            createGMLEdge(sio, edge_counter, source(*edge_it, *g), target(*edge_it, *g), et, strTable->get(get(edge_type, *g, *edge_it)));
        }
      }      
      
      sio.writeEndElement();

      sio.writeBeginElement("data");
      sio.writeAttribute("key", "d4");
        sio.writeBeginElement("y:Resources");
        sio.writeEndElement();
      sio.writeEndElement();
      
    sio.writeEndElement();

    sio.close();
  }

  static string getAttributeValue(Attribute *attr) {
    string value;

    value = "(";
    value += attr->getName();
    if (!attr->getContext().empty()) {
      value += "[";
      value += attr->getContext();
      value += "]";
    }
    value += ":";

    switch (attr->getType()) {
      case Attribute::atInt:
        value += lexical_cast<string>(((AttributeInt*)attr)->getValue());
        break;
      case Attribute::atFloat:
        value += lexical_cast<string>(((AttributeFloat*)attr)->getValue());
        break;
      case Attribute::atString:
        value += ((AttributeString*)attr)->getValue();
        break;
      case Attribute::atComposite:
        break;
      case Attribute::atInvalid:
        value += "__INVALID__";
        break;
      default:
        break;
    }

    value += ")";

    return value;
  }

  // The CSV dump can be extremely slow!!!!!!
  void Graph::saveCSV(const string& filename, const string& edge) const {
    CsvIO cio(filename, io::IOBase::omWrite);

    typedef set<boost::tuple<Key, Key, enum Attribute::aType> > TripletSet;
    typedef map<Key, TripletSet> NodeTypesMapType;
    
    NodeTypesMapType nodeTypes;

    vertex_iter vertex_begin;
    vertex_iter vertex_end;
    vertex_iter vertex_it;

    boost::tie(vertex_begin, vertex_end) = vertices(*g);

    // Collecting the vertex types and attributes
    for(vertex_it = vertex_begin; vertex_it != vertex_end; vertex_it++) {

      TripletSet& attributeSet = nodeTypes.insert(make_pair(get(vertex_type, *g, *vertex_it), TripletSet())).first->second;

      AttributeList *vertex_attr = get(vertex_attributes, *g, *vertex_it);

      // Collceting the attributes of the vertex
      for(AttributeList::iterator it = vertex_attr->begin(); it != vertex_attr->end(); it++)
        attributeSet.insert(boost::make_tuple((*it)->name, (*it)->context, (*it)->getType()));

    }

    // Iterate through the vertices of each type
    for (NodeTypesMapType::const_iterator tit = nodeTypes.begin(); tit != nodeTypes.end(); ++tit) {
      cio.writeColumn(strTable->get(tit->first));

      for (TripletSet::const_iterator sit = tit->second.begin(); sit != tit->second.end(); ++sit)
        if (!strTable->get(sit->get<1>()).empty())
          cio.writeColumn(strTable->get(sit->get<0>()) + "|" + strTable->get(sit->get<1>()));
        else
          cio.writeColumn(strTable->get(sit->get<0>()));

      cio.writeNewLine();

      // Looking for an exact type of vertices
      for(vertex_it = vertex_begin; vertex_it != vertex_end; vertex_it++)
        if (tit->first == get(vertex_type, *g, *vertex_it)) {
          // Write out the UID of the vertex
          cio.writeColumn(strTable->get(get(vertex_UID, *g, *vertex_it)));

          // Write out the attributes of the vertex
          for (TripletSet::const_iterator sit = tit->second.begin(); sit != tit->second.end(); ++sit) {
            bool found = false;

            AttributeList *vertex_attr = get(vertex_attributes, *g, *vertex_it);
            for(AttributeList::iterator it = vertex_attr->begin(); it != vertex_attr->end(); it++)
              if (boost::make_tuple((*it)->name, (*it)->context, (*it)->getType()) == *sit) {
                cio.writeColumn(getAttributeValue(*it));
                found = true;
                break;
              }
            
            if (!found)
              cio.writeColumn(_EMPTY_FIELD);
          }
          cio.writeNewLine();
        }

      cio.writeNewLine();
    }

    cio.close();
  }

  struct HeaderElement;

  bool isEqual(const vector<HeaderElement>& left, const vector<HeaderElement>& right) ;

  struct HeaderElement {

    HeaderElement() :
      element(""),
      contexts(),
      type(Attribute::atInt),
      children(),
      parent(NULL),
      maxNumber(0)
    {}

    HeaderElement(const columbus::graph::HeaderElement& copy):
      element(copy.element),
      contexts(copy.contexts),
      type(copy.type),
      children(copy.children),
      parent(copy.parent),
      maxNumber(copy.maxNumber)
    {}

    HeaderElement& operator=(const columbus::graph::HeaderElement& copy){
      element = copy.element;
      contexts = copy.contexts;
      type = copy.type;
      children = copy.children;
      parent = copy.parent;
      maxNumber = copy.maxNumber;
      return *this;
    }

    string element;
    set<string> contexts;
    Attribute::aType type;
    vector<HeaderElement> children;
    HeaderElement* parent;
    int maxNumber;

    void refreshChildrenParent() {
      for(vector<HeaderElement>::iterator it = children.begin(); it != children.end(); it++) {
        it->parent = this;
        it->refreshChildrenParent();
      }
    }

    bool operator ==(const HeaderElement& hElement ) const {
      // if parents is null, we check only parents addresses
      return (element == hElement.element) && (type == hElement.type) && (isEqual(children, hElement.children));
    }

  };

  template<class T>
  struct csvSection {
    csvSection<T> ():header(),elements() {}

    vector<HeaderElement> header;
    list<T> elements;
  };

  bool isEqual(const vector<HeaderElement>& left, const vector<HeaderElement>& right) {
    bool result = true;
    if(left.size() != right.size())
      result = false;
    else {
      for(vector<HeaderElement>::const_iterator leftIt = left.begin(), rightIt = right.begin(); (leftIt != left.end()) && (rightIt != right.end()); leftIt++, rightIt++ ) {
        if(!(*leftIt == *rightIt))
          result = false;
      }
    }
    return result;
  }

  string convertHeaderElementToString(const HeaderElement& header) ;

  string getHeaderElementLongName(const HeaderElement& header, bool withContext = false) ;

  bool contain(const vector<HeaderElement>& list,const HeaderElement& element) {

    for(vector<HeaderElement>::const_iterator it = list.begin(); it != list.end(); it++) {
      if(*it == element)
        return true;
    }
    return false;
  }

  string aTypeToString(Attribute::aType type) {
    string sType;
    switch(type) {
      case Attribute::atInt:
        sType = "atInt";
        break;
      case Attribute::atFloat:
        sType = "atFloat";
        break;
      case Attribute::atString:
        sType = "atString";
        break;
      case Attribute::atComposite:
        sType = "atComposite";
        break;
      case Attribute::atInvalid:
        sType = "atInvalid";
        break;
    }
    return sType;
  }

  Attribute::aType stringToAType(string type) {
    Attribute::aType aType = Attribute::atString;
    if(type == "atInt")
      aType = Attribute::atInt;
    else if(type == "atFloat")
      aType = Attribute::atFloat;
    else if(type == "atString")
      aType = Attribute::atString;
    else if (type == "atComposite")
      aType = Attribute::atComposite;
    else if (type == "atInvalid")
      aType = Attribute::atInvalid;
    return aType;
  }


  HeaderElement* addAttributeToHeader(vector<HeaderElement>& names, HeaderElement& nameList, map<pair<string, Attribute::aType>, int>& attributeNumbers) {
    HeaderElement* result = NULL;
    if(!contain(names, nameList)) {
      names.push_back(nameList);
      result = &(names.back());
    } else {
      int maxNum = attributeNumbers[make_pair(getHeaderElementLongName(nameList), nameList.type)];
      for(vector<HeaderElement>::iterator it = names.begin(); it != names.end(); it++) {
        if(*it == nameList) {
          if(maxNum > it->maxNumber) {
            it->maxNumber = maxNum;
          }
          result = &(*it);
          break;
        }
      }
    }
    return result;
  }

  // T can be Node or Edge
  void getAttributeName(AttributeComposite& attribute, vector<HeaderElement>& names, map<pair<string, Attribute::aType>, int>& attributeNumbers, HeaderElement* parent) {
    Attribute::AttributeIterator it = attribute.getAttributes();
    while(it.hasNext()) {
      Attribute& attr = it.next();
      if(attr.getType() == Attribute::atComposite) {
        // add composite attribute to attributelist
        HeaderElement compositeName;
        compositeName.element = attr.getName();
        compositeName.type = Attribute::atComposite;
        compositeName.contexts.insert(attr.getContext());
        compositeName.parent = parent;
        compositeName.maxNumber = ++attributeNumbers[make_pair(getHeaderElementLongName(compositeName), compositeName.type)];
        HeaderElement* addedCompositeName = addAttributeToHeader(names, compositeName, attributeNumbers);
        vector<HeaderElement> childNames;
        getAttributeName(static_cast<AttributeComposite&>(attr), childNames, attributeNumbers, addedCompositeName);
        for(vector<HeaderElement>::iterator listIt = childNames.begin(); listIt != childNames.end(); listIt++) {
          HeaderElement& nameList = *listIt;
          nameList.maxNumber = ++attributeNumbers[make_pair(getHeaderElementLongName(nameList), nameList.type)];
          addAttributeToHeader(addedCompositeName->children, nameList, attributeNumbers);
        }
      } else {
        HeaderElement nameList;
        nameList.element = attr.getName();
        nameList.type = attr.getType();
        nameList.contexts.insert(attr.getContext());
        nameList.parent = parent;
        nameList.maxNumber = ++attributeNumbers[make_pair(getHeaderElementLongName(nameList), nameList.type)];
        addAttributeToHeader(names, nameList, attributeNumbers);
      }
    }
  }

  template<class OutputIterator>
  void addAttributesToSection(Attribute::AttributeIterator& attrIt, OutputIterator& currentSection) {
    map<pair<string, Attribute::aType>, int> attributeNumbers;
    while(attrIt.hasNext()) {
      Attribute& attr = attrIt.next();
      if(attr.getType() == Attribute::atComposite) {
        // add composite attribute to attributelist
        HeaderElement compositeName;
        compositeName.element = attr.getName();
        compositeName.type = Attribute::atComposite;
        compositeName.contexts.insert(attr.getContext());
        compositeName.parent = NULL;
        compositeName.maxNumber = ++attributeNumbers[make_pair(getHeaderElementLongName(compositeName), compositeName.type)];
        getAttributeName(static_cast<AttributeComposite&>(attr), compositeName.children, attributeNumbers, &compositeName);
        HeaderElement* addedCompositeName = addAttributeToHeader(currentSection->second.header, compositeName, attributeNumbers);
        addedCompositeName->refreshChildrenParent();
      } else {
        HeaderElement nameList;
        nameList.element = attr.getName();
        nameList.type = attr.getType();
        nameList.contexts.insert(attr.getContext());
        nameList.parent = NULL;
        nameList.maxNumber = ++attributeNumbers[make_pair(getHeaderElementLongName(nameList), nameList.type)];
        addAttributeToHeader(currentSection->second.header, nameList, attributeNumbers);
      }
    }
  }

  inline bool canWriteContext(const HeaderElement& header) {
    return header.children.empty() && (header.parent == NULL) && (header.contexts.size() < 2);
  }

  string getHeaderElementLongName(const HeaderElement& header, bool withContext) {
    string name = header.element + _TYPE_NAME_BEGIN + aTypeToString(header.type) + _TYPE_NAME_END;
    if(withContext && canWriteContext(header))
      name += _CONTEXT_NAME_BEGIN + *(header.contexts.begin()) + _CONTEXT_NAME_END;
    HeaderElement* parent = header.parent;
    while(parent != NULL) {
      name = parent->element + _NAME_SEPARATOR + name;
      parent = parent->parent;
    }
    return name;
  }

  string convertHeaderElementToString(const HeaderElement& header) {
    string out = getHeaderElementLongName(header, true);
    for(vector<HeaderElement>::const_iterator it = header.children.begin(); it != header.children.end(); it++) {
      out += ";" + convertHeaderElementToString(*it);
    }
    return out;
  }

  template<class AttributeContainer>
  void getAttributesByHeaderInfo(const HeaderElement& headerInfo, AttributeContainer& element, list<Attribute*>& attributes) {
    // find element
    Attribute::AttributeIterator attrIt = element.findAttributeByName(headerInfo.element);
    while(attrIt.hasNext()) {
      Attribute& attr = attrIt.next();
      if(attr.getType() != headerInfo.type)
        continue;
      if((attr.getType() != Attribute::atComposite) && !headerInfo.children.empty() )
        continue;
      list<Attribute*> tmpAttributes;
      for(vector<HeaderElement>::const_iterator it = headerInfo.children.begin(); it != headerInfo.children.end(); it++) {
        getAttributesByHeaderInfo(*it, static_cast<AttributeComposite&>(attr), tmpAttributes);
      }
      if(tmpAttributes.size() != headerInfo.children.size())
        continue;
      attributes.push_back(&attr);
    }
  }

  void writeAttributeToCsv(Attribute& attr, io::CsvIO& csvOut, bool writeContext, const HeaderElement& headerInfo) {
    if(attr == Graph::invalidAttribute)
      csvOut.writeColumn(_EMPTY_FIELD);
    else {
      if(attr.getType() != headerInfo.type)
        throw GraphException( COLUMBUS_LOCATION, CMSG_EX_WRONG_ATTRIBUTE_FOUND);
      else {
        switch(attr.getType()) {
          case Attribute::atInt:
            {
              string value = lexical_cast<string>(static_cast<const AttributeInt&>(attr).getValue());
              if(writeContext && !attr.getContext().empty())
                value += _CONTEXT_NAME_BEGIN + attr.getContext() + _CONTEXT_NAME_END;
              csvOut.writeColumn(value);
              break;
            }
          case Attribute::atFloat:
            {
              string value = lexical_cast<string>(static_cast<const AttributeFloat&>(attr).getValue());
              if(writeContext && !attr.getContext().empty())
                value += _CONTEXT_NAME_BEGIN + attr.getContext() + _CONTEXT_NAME_END;
              csvOut.writeColumn(value);
              break;
            }
          case Attribute::atString:
            {
              string value = (static_cast<const AttributeString&>(attr).getValue());
              if(writeContext && !attr.getContext().empty())
                value += _CONTEXT_NAME_BEGIN + attr.getContext() + _CONTEXT_NAME_END;
              csvOut.writeColumn(value);
              break;
            }
          case Attribute::atComposite:
            {
              // write out composite attrubute
              if(writeContext && !attr.getContext().empty())
                csvOut.writeColumn(_CONTEXT_NAME_BEGIN + attr.getContext() + _CONTEXT_NAME_END);
              else
                csvOut.writeColumn("");
              // write out child attributes
              for(vector<HeaderElement>::const_iterator headerElementIt = headerInfo.children.begin(); headerElementIt != headerInfo.children.end(); headerElementIt++) {
                Attribute::AttributeIterator attributeIt = static_cast<AttributeComposite&>(attr).findAttributeByName(headerElementIt->element);
                bool childIsWritedOut = false;
                while(attributeIt.hasNext()) {
                  Attribute& attr2 = attributeIt.next();
                  if(attr2.getType() == headerElementIt->type) {
                    writeAttributeToCsv(attr2, csvOut, writeContext, *headerElementIt);
                    childIsWritedOut = true;
                    break;
                  }
                }
                if(!childIsWritedOut)
                  throw GraphException( COLUMBUS_LOCATION, CMSG_EX_WRONG_ATTRIBUTE_NOT_FOUND + headerElementIt->element);
              }
              break;
            }
          default:
            break;
        }
      }
    }
  }

  string getEmptAttribute(const HeaderElement& headerElement) {
    string out = _EMPTY_FIELD;
    for(vector<HeaderElement>::const_iterator it = headerElement.children.begin(); it != headerElement.children.end(); it++) {
      out += ";" + getEmptAttribute(*it);
    }
    return out;
  }

  void Graph::saveCSV(const string& filename) {
  
    typedef map< string, csvSection<Node> > nodeSectionContainer;
    typedef map< string, csvSection<Edge> > edgeSectionContainer;

    nodeSectionContainer nodeSC;
    edgeSectionContainer edgeSC;

    Node::NodeIterator allNodes = getNodes();

    while(allNodes.hasNext()) {
      Node node = allNodes.next();
      // get node type
      string nodeType = node.getType().getType();
      nodeSectionContainer::iterator currentSection = nodeSC.find(nodeType);
      if(currentSection == nodeSC.end() ) {
        // create new section
        csvSection<Node> section;
        currentSection = (nodeSC.insert(make_pair( nodeType, section) ).first);
      }
      currentSection->second.elements.push_back(node);
      // add attributes name
      Attribute::AttributeIterator attrIt = node.getAttributes();
      addAttributesToSection(attrIt, currentSection);
      // get edges
      Edge::EdgeIterator edgeIt = node.getOutEdges();
      while(edgeIt.hasNext()) {
        Edge edge = edgeIt.next();
        string edgeType = edge.getType().getType();
        edgeSectionContainer::iterator currentEdgeSection = edgeSC.find(edgeType);
        if(currentEdgeSection == edgeSC.end() ) {
          // create new section
          csvSection<Edge> section;
          currentEdgeSection = (edgeSC.insert(make_pair( edgeType, section) ).first);
        }
        currentEdgeSection->second.elements.push_back(edge);
        // add attributes
        Attribute::AttributeIterator edgeAttrIt = edge.getAttributes();
        addAttributesToSection(edgeAttrIt, currentEdgeSection);

      }

    }

    io::CsvIO csvOut(filename, io::IOBase::omWrite);
    // write output
    // write out nodes
    for(nodeSectionContainer::iterator sectionIt = nodeSC.begin(); sectionIt != nodeSC.end(); sectionIt++) {

      // write out section name
      csvOut.writeColumn(sectionIt->first);
      csvOut.writeNewLine();
      // write out section header
      csvOut.writeColumn(_UNIQUENAME);
      for(vector<HeaderElement>::iterator headerIt = sectionIt->second.header.begin(); headerIt != sectionIt->second.header.end(); headerIt++) {
        headerIt->refreshChildrenParent();
        string headerCol = convertHeaderElementToString(*headerIt);
        for(int i = 0; i < headerIt->maxNumber; i++)
          csvOut.writeColumn(headerCol);
      }
      csvOut.writeNewLine();
      // write out nodes
      for(list<Node>::iterator nodeValureIt = sectionIt->second.elements.begin(); nodeValureIt != sectionIt->second.elements.end(); nodeValureIt++) {
        csvOut.writeColumn(nodeValureIt->getUID());
        // write attributes
        for(vector<HeaderElement>::iterator attributeNameIt = sectionIt->second.header.begin(); attributeNameIt != sectionIt->second.header.end(); attributeNameIt++) {
          bool writeContext = !canWriteContext(*attributeNameIt);
          list<Attribute*> attributes;
          getAttributesByHeaderInfo(*attributeNameIt, *nodeValureIt, attributes);
          int countWritedAttributes = 0;
          for(list<Attribute*>::iterator attributeIt = attributes.begin(); attributeIt != attributes.end(); attributeIt++, countWritedAttributes++) {
            writeAttributeToCsv(**attributeIt, csvOut, writeContext, *attributeNameIt);
          }
          string emptyAttribute = getEmptAttribute(*attributeNameIt);
          for(; countWritedAttributes < attributeNameIt->maxNumber; countWritedAttributes++) {
            csvOut.writeColumn(emptyAttribute);
          }
//          writeAttributeToCsv(*attributes.front(), csvOut, (attributeNameIt->contexts.size() > 1) );
        }
        csvOut.writeNewLine();
      }
      csvOut.writeNewLine();
    }
    csvOut.writeNewLine();

    // write out edges

    for(edgeSectionContainer::iterator edgeSectionIt = edgeSC.begin(); edgeSectionIt != edgeSC.end(); edgeSectionIt++) {
      // write section name
      csvOut.writeColumn(edgeSectionIt->first);
      csvOut.writeNewLine();
      // write out section header
      csvOut.writeColumn(_UNIQUENAME);
      csvOut.writeColumn(_STARTUNIQUENAME);
      csvOut.writeColumn(_ENDUNIQUENAME);
      csvOut.writeColumn(_EDGE_DIRECTION);
      for(vector<HeaderElement>::iterator headerIt = edgeSectionIt->second.header.begin(); headerIt != edgeSectionIt->second.header.end(); headerIt++) {
        string headerCol = convertHeaderElementToString(*headerIt);
        for(int i = 0; i < headerIt->maxNumber; i++)
          csvOut.writeColumn(headerCol);

      }
      csvOut.writeNewLine();
      // write out edges
      for(list<Edge>::iterator edgeValureIt = edgeSectionIt->second.elements.begin(); edgeValureIt != edgeSectionIt->second.elements.end(); edgeValureIt++) {
        csvOut.writeColumn(edgeValureIt->getName());
        csvOut.writeColumn(edgeValureIt->getFromNode().getUID());
        csvOut.writeColumn(edgeValureIt->getToNode().getUID());
        switch(edgeValureIt->getType().getDirectionType()) {
          case Edge::edtBidirectional:
            csvOut.writeColumn(_BIDIRECTIONAL);
            break;
          case Edge::edtDirectional:
            csvOut.writeColumn(_DIRECTIONAL);
            break;
          case Edge::edtReverse:
            csvOut.writeColumn(_REVERSE);
            break;
        }
        // write attributes
        for(vector<HeaderElement>::iterator attributeNameIt = edgeSectionIt->second.header.begin(); attributeNameIt != edgeSectionIt->second.header.end(); attributeNameIt++) {
          list<Attribute*> attributes;
          bool writeContext = !canWriteContext(*attributeNameIt);
          getAttributesByHeaderInfo(*attributeNameIt, *edgeValureIt, attributes);
          int countWritedAttributes = 0;
          for(list<Attribute*>::iterator attributeIt = attributes.begin(); attributeIt != attributes.end(); attributeIt++, countWritedAttributes++) {
            writeAttributeToCsv(**attributeIt, csvOut, writeContext, *attributeNameIt);
          }
          string emptyAttribute = getEmptAttribute(*attributeNameIt);
          for(; countWritedAttributes < attributeNameIt->maxNumber; countWritedAttributes++) {
            csvOut.writeColumn(emptyAttribute);
          }

//          getAttributesByHeaderInfo(*attributeNameIt, *edgeValureIt, attributes);
//          writeAttributeToCsv(*attributes.front(), csvOut,  (attributeNameIt->contexts.size() > 1));
        }
        csvOut.writeNewLine();
      }
      csvOut.writeNewLine();
    }
    csvOut.writeNewLine();


    csvOut.flush();
    csvOut.close();
  }

  void Graph::loadCSV(const string& filename) {
    GraphSchemaReader::TurnOffFilterSafety turnOffFilterSafety(*gsReader);
    enum { rsNone, rsHeader, rsNodeData, rsEdgeData } readerState = rsNone;
    // open the csv file
    io::CsvIO csvIn(filename, io::IOBase::omRead);
    string head;
    list<string> header;
    while(true) {
      list<string> line;
      if(!csvIn.readLine(line)) break;
      // read empty line -> section break
      if(line.empty()) {
        readerState = rsNone;
        continue;
      }
      switch(readerState) {
        // read head name
        case rsNone:
          head = line.front();
          readerState = rsHeader;
          break;
          // read header information
        case rsHeader:
          header = line;
          if(header.front() != _UNIQUENAME)
            throw GraphException( COLUMBUS_LOCATION, CMSG_EX_WRONG_HEADER_INFORMATION);
          // if header start with: _UNIQUENAME _STARTUNIQUENAME _ENDUNIQUENAME _EDGE_DIRECTION then it is edge section
          if( isEdgeHeader(header) ) {
            readerState = rsEdgeData;
          } else {
          // else it is node section
            readerState = rsNodeData;
          }
          break;
        case rsNodeData:
          processCSVNodeLine(line, head, header);
          break;
        case rsEdgeData:
          processCSVEdgeLine(line, head, header);
          break;
      }
    }
  }


  bool Graph::isEdgeHeader(const list<string>& header) {
    const char* columns[5] = {_UNIQUENAME, _STARTUNIQUENAME, _ENDUNIQUENAME, _EDGE_DIRECTION};
    if(header.size() < 4)
      return false;
    list<string>::const_iterator it = header.begin();
    for(int i = 0; i < 4; i++) {
      if(strcmp(it->c_str(), columns[i]) !=0 )
        return false;
      it++;
    }
    return true;
  }

  void Graph::processCSVNodeLine(const list<string>& line, const string& head, const list<string>& header) {
    // firs element is must be unique name
    Node node = findNode(line.front());
    if(node == invalidNode)
      node = createNode(line.front(), Node::NodeType(head));
    else
      node.setType(Node::NodeType(head));
    // load node attributes
    loadAttributes(node, line, header, 1);
  }

  void Graph::processCSVEdgeLine(const list<string>& line, const string& head, const list<string>& header) {
    list<string>::const_iterator lineIt = line.begin();
    // skip edge unique name
    lineIt++;
    // read from node name
    Node fromNode = findNode(*lineIt);
    if(fromNode == invalidNode)
      fromNode = createNode(*lineIt, Node::NodeType("__INVALID__"));
    lineIt++;
    // read to node
    Node toNode = findNode(*lineIt);
    if(toNode == invalidNode)
      toNode = createNode(*lineIt, Node::NodeType("__INVALID__"));
    lineIt++;
    // read edge type
    if(*lineIt == _BIDIRECTIONAL) {
      Edge edge = createBidirectedEdge(fromNode, toNode, head);
      loadAttributes(edge, line, header, 4);
    } else if(*lineIt == _DIRECTIONAL) {
      Edge edge = createDirectedEdge(fromNode, toNode, head, false);
      loadAttributes(edge, line, header, 4);
    }
// else if(*lineIt == _REVERSE) {
//
//    }

  }

  template<class T>
  void Graph::loadAttributes(T& element, const list<string>& line, const list<string>& header, int offset) {
    if(line.size() != header.size())
      throw GraphException( COLUMBUS_LOCATION, CMSG_EX_WRONG_LINE_LENGTH);
    list<string>::const_iterator headerIt = header.begin(), lineIt = line.begin();
    for(int i = 0; i < offset; i++) {
      headerIt++;
      lineIt++;
    }
    for(; (headerIt != header.end()) && (lineIt != line.end()); headerIt++, lineIt++) {
      if(*lineIt == _EMPTY_FIELD)
        continue;
      processAttribute(element, *headerIt, *lineIt);
    }
  }
  

  template<class T>
  void Graph::processAttribute(T& element, const string& sign, const string& value) {
    string nCsign = sign;
    Attribute::aType attrType = getTypeFromString(nCsign);
    string context;
    getContextFromString(nCsign, context);
    list< string > splitSign;
    // remove type name and context form header

    split( splitSign, nCsign, is_any_of(_NAME_SEPARATOR) );
    processAtrtibutePart(element, splitSign, value, attrType, context);
  }

  bool findDataInString(string& text, const char* beginChar, const char* sepChar, const char* endChar, const char* name, string& value) ;

  template<class T>
  void Graph::processAtrtibutePart(T& element, list<string>& splitSign, const string& val, Attribute::aType attrType, const string& defCotnext) {
    string value = val;
    string context;
    bool hasContext = getContextFromString(value, context);
    if(!hasContext)
      context = defCotnext;
    AttributeComposite* attrComp = NULL;
    // find first attribute, it is not exist, we create one
    string attributeName = splitSign.front();
    splitSign.pop_front();
    if(splitSign.empty()) {
      switch(attrType) {
        case Attribute::atInt:
          element.addAttribute(createAttributeInt(attributeName, context, lexical_cast<int>(value)));
          break;
        case Attribute::atFloat:
          element.addAttribute(createAttributeFloat(attributeName, context, lexical_cast<float>(value)));
          break;
        case Attribute::atString:
          element.addAttribute(createAttributeString(attributeName, context, value));
          break;
        case Attribute::atComposite:
          element.addAttribute(createAttributeComposite(attributeName, context));
          break;
        default:
          break;
      }
      return;
    }
    Attribute::AttributeIterator attrIt = element.findAttributeByName(attributeName);
    while(attrIt.hasNext()) {
      // we found the attribute, and set last to active
      Attribute& attr = attrIt.next();
      if( attr.getType() == Attribute::atComposite)
        attrComp = dynamic_cast<AttributeComposite*>(&attr);
    } 
    // if attrComp doesn't have value
    if(attrComp == NULL)
      attrComp = dynamic_cast<AttributeComposite*>(&element.addAttribute(createAttributeComposite(attributeName, "")));
    processAtrtibutePart(*attrComp, splitSign, value, attrType, context);
  }

  bool findDataInString(string& text, const char* beginChar, const char* sepChar, const char* endChar, const char* name, string& value) {
    value = "";
    bool founded = false;
    size_t startState = 0;
    size_t begin = 0;
    size_t end = 0;
    size_t valEnd = 0;
    while(true) {
      begin = text.find_first_of(beginChar, startState);
      if(begin != string::npos) {
        end = text.find_first_of(sepChar, begin);
        if(end != string::npos) {
          string id = text.substr(begin, end - begin + 1);
          if(id == name) {
            valEnd = text.find_first_of(endChar, end);
            if(valEnd != string::npos) {
              value = text.substr(end + 1, valEnd - end - 1);
            }
            break;
          } else {
            startState = end + 1;
            continue;
          }
        } else {
          break;
        }
      } else {
        break;
      }
    }
    if(begin < valEnd) {
      text = text.substr(0, begin) + text.substr(valEnd + 1);
      founded = true;
    }
    return founded;
  }

  Attribute::aType Graph::getTypeFromString(string& text) {
    string value;
    findDataInString(text, _TYPE_CONTEXT_BEGIN, _TYPE_CONTEXT_SEP, _TYPE_NAME_END, _TYPE_NAME_BEGIN, value);
    return stringToAType(value);
  }

  bool Graph::getContextFromString(string& text, string& value) {
    value = "";
    return findDataInString(text, _TYPE_CONTEXT_BEGIN, _TYPE_CONTEXT_SEP, _CONTEXT_NAME_END, _CONTEXT_NAME_BEGIN, value);
  }


  //--- Create attributes

  AttributeInt Graph::createAttributeInt(const string& name, const string& context, int value) {
    return AttributeInt(name, context, value,this);
  }

  AttributeFloat Graph::createAttributeFloat(const string& name, const string& context, float value) {
    return AttributeFloat(name, context, value,this);
  }

  AttributeString Graph::createAttributeString(const string& name, const string& context, const string& value) {
    return AttributeString(name, context, value,this);
  }

  AttributeComposite Graph::createAttributeComposite(const string& name, const string& context) {
    return AttributeComposite(name, context, this);
  }




  //--- Create attributes end

  void Graph::initAttribute(const Node::NodeTypeSet& nodeTypeSet,const Attribute& attr) {
    vertex_iter vertex_begin, vertex_end, vertex_it;
    boost::tie(vertex_begin,vertex_end) = vertices(*g);

    for(vertex_it = vertex_begin; vertex_it != vertex_end; vertex_it++) {
      Node node(this,*vertex_it);
      if(nodeTypeSet.find(node.getType()) !=  nodeTypeSet.end() ) {
        node.addAttribute(attr);
      }
    }

  }

  Node::NodeSet Graph::getRootByEdgeType(const Edge::EdgeType& edgeType) {
    Node::NodeSet root;

    vertex_iter vertex_begin, vertex_end, vertex_it;
    boost::tie(vertex_begin,vertex_end) = vertices(*g);

    for(vertex_it = vertex_begin; vertex_it != vertex_end; vertex_it++) {
      Node node(this,*vertex_it);
      Edge::EdgeIterator edgeIt = node.findOutEdges(edgeType);
      if(!edgeIt.hasNext()) {
        root.insert(node);
      }
    }
    return root;
  }


  Node::NodeSet Graph::getLeafByEdgeType(const Edge::EdgeType& edgeType) {
    Node::NodeSet leaf;
    Node::NodeSet notLeaf;
    vertex_iter vertex_begin, vertex_end, vertex_it;
    boost::tie(vertex_begin,vertex_end) = vertices(*g);

    for(vertex_it = vertex_begin; vertex_it != vertex_end; vertex_it++) {
      Node node(this,*vertex_it);


      // ide mar mutatott el
      if(notLeaf.find(node) != notLeaf.end() )
        continue;
      // innen mutat az el, es ide meg nem mutatott
      leaf.insert(node);
      // az innen elerheto csucsok nem levelek
      Edge::EdgeIterator edgeIt = node.findOutEdges(edgeType);
      while(edgeIt.hasNext()) {
        Edge edge = edgeIt.next();
        Node toNode = edge.getToNode();
        Node fromNode = edge.getFromNode();
//        switch (edge.getType().getDirectionType()) {
//          case Edge::edtBidirectional:
//            notLeaf.insert(toNode);
//            notLeaf.insert(fromNode);
//            leaf.erase(toNode);
//            leaf.erase(fromNode);
//            break;
//          case Edge::edtDirectional:
//            notLeaf.insert(toNode);
//            leaf.erase(toNode);
//            break;
//          case Edge::edtReverse:
//            notLeaf.insert(fromNode);
//            leaf.erase(fromNode);
//            break;
//        }
        notLeaf.insert(toNode);
        leaf.erase(toNode);
      }
    }
    return leaf;
  }

  const Node Graph::invalidNode;

  const Edge Graph::invalidEdge;

  const Attribute Graph::invalidAttribute;

  void Graph::writeAttributeToBinary(Attribute& attribute, io::BinaryIO& out) const {
    switch(attribute.getType()) {
      case Attribute::atInt:
        out.writeUInt4(Attribute::atInt);
        out.writeUInt4( ((AttributeInt&)attribute).name );
        out.writeUInt4( ((AttributeInt&)attribute).context );
        out.writeInt4( ((AttributeInt&)attribute).value );
        break;
        
      case Attribute::atFloat:
        out.writeUInt4(Attribute::atFloat);
        out.writeUInt4( ((AttributeFloat&)attribute).name );
        out.writeUInt4( ((AttributeFloat&)attribute).context );
        out.writeFloat4( ((AttributeFloat&)attribute).value );
        break;
      case Attribute::atString:
        out.writeUInt4(Attribute::atString);
        out.writeUInt4( ((AttributeString&)attribute).name );
        out.writeUInt4( ((AttributeString&)attribute).context );
        out.writeUInt4( ((AttributeString&)attribute).value );
        break;
      case Attribute::atComposite:
        out.writeUInt4(Attribute::atComposite);
        out.writeUInt4( ((AttributeComposite&)attribute).name );
        out.writeUInt4( ((AttributeComposite&)attribute).context );
        out.writeUInt4(static_cast<unsigned int>( ((AttributeComposite&)attribute).values->size()));
        for(AttributeList::iterator it = ((AttributeComposite&)attribute).values->begin(); it != ((AttributeComposite&)attribute).values->end(); it++) {
          writeAttributeToBinary(**it, out);
        }
        break;
      default:
        break;
    }
  }


  void Graph::saveBinary(const string& filename) const {
    io::BinaryIO out(filename, io::BinaryIO::omWrite);
    set<GraphEdge> savedEdgePairs;

    // write out strTable
    strTable->save(out);

    // write out header information
    out.writeUInt4(static_cast<unsigned int>(headerInformations.size()));
    for(StringMap::const_iterator it = headerInformations.begin(); it != headerInformations.end(); it++) {
      out.writeUInt4(it->first);
      out.writeUInt4(it->second);
    }

    // write out Nodes
    vertex_iter vertex_begin, vertex_end,vertex_it;
    boost::tie(vertex_begin,vertex_end) = vertices(*g);
    for(vertex_it = vertex_begin; vertex_it != vertex_end; vertex_it++) {

      // node uid, type key

      out.writeUInt4(get(vertex_UID,*g,*vertex_it));
      out.writeUInt4(get(vertex_type,*g,*vertex_it));
      
      // write out attributes size

      AttributeList *vertex_attr = get(vertex_attributes,*g,*vertex_it);

      // write out attributes
      out.writeUInt4(static_cast<unsigned int>(vertex_attr->size()));
      for(AttributeList::iterator it = vertex_attr->begin(); it != vertex_attr->end(); it++) {
        writeAttributeToBinary(**it,out);
      }

      // write out edges

      out_edge_iter edge_begin, edge_end, edge_it;
      boost::tie(edge_begin,edge_end) = out_edges(*vertex_it,*g);
      for(edge_it = edge_begin; edge_it != edge_end; edge_it++) {
        if(get(edge_direction,*g,*edge_it) != Edge::edtReverse  && savedEdgePairs.find(*edge_it) == savedEdgePairs.end() ) {

          // edge type
          out.writeUInt4(get(edge_type,*g,*edge_it));

          // edge direction

          out.writeUInt4(get(edge_direction,*g,*edge_it));

          // to node
          out.writeUInt4(get(vertex_UID,*g,target(*edge_it,*g)));

          // has pair

          if(hasEdgePair(*edge_it)) {
            out.writeBool1(true);
            savedEdgePairs.insert(getEdgePair(*edge_it));
          } else {
            out.writeBool1(false);
          }


          // write attributes

          AttributeList *edge_attr = get(edge_attributes,*g,*edge_it);

          out.writeUInt4(static_cast<unsigned int>(edge_attr->size()));

          for(AttributeList::iterator it = edge_attr->begin(); it != edge_attr->end(); it++) {
            writeAttributeToBinary(**it,out);
          }

          // write reserve pair edge
          if(hasEdgePair(*edge_it)) {
            // write attributes

            AttributeList *edge_attr = get(edge_attributes,*g, getEdgePair(*edge_it));

            out.writeUInt4(static_cast<unsigned int>(edge_attr->size()));

            for(AttributeList::iterator it = edge_attr->begin(); it != edge_attr->end(); it++) {
              writeAttributeToBinary(**it,out);
            }
          }
        }

      }
      // write empty edge

      // edge type
      out.writeUInt4(0);

      // edge direction
      out.writeUInt4(0);

      // to node
      out.writeUInt4(0);
    }

    //write empty node
    
    // node uid, type key
    out.writeUInt4(0);
    out.writeUInt4(0);

    out.close();
  }


  template<class T>
  void Graph::readAttributeToBinary(io::BinaryIO& in, T& container) {
    Attribute::aType type = static_cast<Attribute::aType>(in.readUInt4());
    switch(type) {
      case Attribute::atInt:
        {
          Key name = in.readUInt4();
          Key context = in.readUInt4();
          int value = in.readInt4();
          container.addAttribute(AttributeInt(name, context, value, this));
          break;
        }
      case Attribute::atFloat:
        {
          Key name = in.readUInt4();
          Key context = in.readUInt4();
          float value = in.readFloat4();
          container.addAttribute(AttributeFloat(name, context, value, this));
          break;
        }
      case Attribute::atString:
        {
          Key name = in.readUInt4();
          Key context = in.readUInt4();
          Key value = in.readUInt4();
          container.addAttribute(AttributeString(name, context, value, this));
          break;
        }
      case Attribute::atComposite:
        {
          Key name = in.readUInt4();
          Key context = in.readUInt4();
          unsigned int attributes_length = in.readUInt4();
          AttributeComposite& attrComposite = (AttributeComposite&)container.addAttribute(AttributeComposite(name, context, this));
          for(unsigned int i = 0; i < attributes_length; i++) {
            readAttributeToBinary(in, attrComposite);
          }
          break;
        }
      default:
        break;
    }
  }

  void Graph::loadBinary(const string& filename) {
    GraphSchemaReader::TurnOffFilterSafety turnOffFilterSafety(*gsReader);
    // delete old graph

    clear();

    io::BinaryIO in(filename, io::BinaryIO::omRead);
    strTable->load(in);

    // reade header information
    unsigned int headerCount = in.readUInt4();
    for(unsigned int i = 0; i < headerCount; i++) {
      unsigned int infoName = in.readUInt4();
      unsigned int infoValue = in.readUInt4();
      setHeaderInfo(strTable->get(infoName), strTable->get(infoValue));
    }

    Key invalidNodeType = strTable->set("__INVALID__");
    
    while(true) {
      if(in.eof())
        throw GraphException( COLUMBUS_LOCATION, CMSG_EX_UNEXCPECTED_END_OF_LINE);

      // read a node

      unsigned int UID = in.readUInt4();
      unsigned int type = in.readUInt4();

      // last node

      if( (UID == 0) && (type == 0) )
        break;

      //create node or find it

      Node node;

      KeyMap::const_iterator nodeMapIt = nodeUIDs.find(UID);
      if(nodeMapIt != nodeUIDs.end()) {
        IndexMapVertexTypes types = get(vertex_type, *g);
        put(types, nodeMapIt->second, type);
        node = Node(this, nodeMapIt->second);
      } else {
        node = createNode(UID, type);
      }


      // read attribute length
      unsigned int nodeAttrSize = in.readUInt4();

      // read attributes
      for(unsigned int i=0; i < nodeAttrSize; i++) {
        readAttributeToBinary(in, node);
      }

      // read edges

      while(true) {
        if(in.eof())
          throw GraphException( COLUMBUS_LOCATION, CMSG_EX_UNEXCPECTED_END_OF_LINE);

        // edge type
        unsigned int edgeTypeKey = in.readUInt4();

        // edge direction
        unsigned int edgeDirectionKey = in.readUInt4();

        // to node
        unsigned int toNodeKey = in.readUInt4();

        if( (edgeTypeKey == 0) && (edgeDirectionKey == 0) && (toNodeKey == 0) )
          break;

        bool hasPair = in.readBool1();

        // create to node or get to node
        Node toNode;
        
        nodeMapIt = nodeUIDs.find(toNodeKey);
        if(nodeMapIt != nodeUIDs.end()) {
          toNode = Node(this, nodeMapIt->second);
        } else {
          toNode = createNode(toNodeKey, invalidNodeType);
        }

        // create edge

        Edge::eDirectionType edgeDirection = static_cast<Edge::eDirectionType> (edgeDirectionKey);

        Edge edge;

        switch(edgeDirection) {
          case Edge::edtBidirectional:
            edge = createBidirectedEdge(node, toNode, edgeTypeKey);
            break;
          case Edge::edtDirectional:
            edge = createDirectedEdge(node, toNode, edgeTypeKey, false);
            break;
          default:
            // other direction can't be
            break;
        }

        // read attributes

        unsigned int edgeAttributeSize = in.readUInt4();

        for(unsigned int i = 0; i < edgeAttributeSize; i++) {
          readAttributeToBinary(in, edge);
        }

        // add reverse pair attribute

        if(hasPair) {
          Edge revPair = createReservePair(edge);
          unsigned int revEdgeAttributeSize = in.readUInt4();
          for(unsigned int i = 0; i < revEdgeAttributeSize; i++) {
            readAttributeToBinary(in, revPair);
          }
        }

      }

      // debug
      //cout << "++++" << node.getUID();
      //cout << endl;
      //Edge::EdgeIterator edgeIt = node.getOutEdges();
      //while(edgeIt.hasNext()) {
      //  Edge edge = edgeIt.next();
        //cout << "     " << edge.getToNode().getUID() << " " << edge.getType().getType() << " " << edge.getType().getDirectionType() << endl;
      //}
      
    }
    in.close();
  }

  void Graph::clear() {

    clearAttributes();
    clearHelperContaioners();
    clearHeaderInfo();

    if (g != NULL)
      delete g;
    g = new BGraph();
    
    if(strTable != NULL)
      delete strTable;
    strTable = new StrTable();

  }

  void Graph::loadSchema(const string& filename) {
    gsReader->read(filename);
  }

  Node::NodeIterator Graph::getNodes() {
    vertex_iter begin, end;
    boost::tie(begin, end) = vertices(*g);
    return Node::NodeIterator(begin, end, getNodeIterators(), this, Node::NodeTypeSet());
  }

  void Graph::setHeaderInfo(const string& key, const string& value) {
    pair<StringMap::iterator, bool> result = headerInformations.insert(make_pair(strTable->set(key), strTable->set(value)));
    if (!result.second)
      result.first->second = strTable->set(value);
  }

  string Graph::getHeaderInfo(const string& key) {
    StringMap::iterator it = headerInformations.find(strTable->get(key));
    if(it == headerInformations.end())
      throw GraphException("Graph::getHeaderInfo(const string& key)", "Header information not exist!");
    return strTable->get(it->second);
  }

  bool Graph::deleteHeaderInfo(const string& key) {
    size_t deletedElementsCount = headerInformations.erase(strTable->get(key));
    if(deletedElementsCount == 0)
      return false;
    return true;
  }

  void Graph::clearHeaderInfo() {
    headerInformations.clear();
  }

  template<class NodeEdge>
  void Graph::convertOnlyNewAttribute(NodeEdge& oldNode, NodeEdge& newNode) {
    // delete all old attribute
    oldNode.deleteAttributes();
    Attribute::AttributeIterator attributeIt = newNode.getAttributes();
    while(attributeIt.hasNext()) {
      Attribute& attr = attributeIt.next();
      oldNode.addAttribute(attr);
    }
  }

  template<class NodeEdge>
  void Graph::convertSummarizeAttribute(NodeEdge& oldNode, NodeEdge& newNode, Graph::CompsiteAndStringMergeMode attributeStringAndCompositeMode, Graph::NumericMergeMode attributeNumericMode) {
    Attribute::AttributeIterator attributeIt = newNode.getAttributes();
    while(attributeIt.hasNext()) {
      Attribute& attr = attributeIt.next();
      switch(attr.getType()) {
        case Attribute::atComposite:
        case Attribute::atString:
          if (attributeStringAndCompositeMode == Graph::csmmAddNewAttributes) {
            oldNode.addAttribute(attr);
          } else {
            Attribute::AttributeIterator attrItForAttr = oldNode.findAttribute(attr.getType(), attr.getName(), attr.getContext());
            bool foundEqualAttribute = false;
            while(attrItForAttr.hasNext()) {
              Attribute& eqAttr = attrItForAttr.next();
              if(eqAttr == attr) {
                if(attributeStringAndCompositeMode == Graph::csmmDropOldAttributes)
                  oldNode.deleteAttribute(eqAttr); // found old attribuute and drop it
                foundEqualAttribute = true;
                break;
              }
            }
            if( (foundEqualAttribute && attributeStringAndCompositeMode == Graph::csmmDropOldAttributes ) || // if we found attribute and drop mode is on
              (!foundEqualAttribute && attributeStringAndCompositeMode == Graph::csmmUnionNewAttributes)     // id we not found attribute and unio mode is on
              ) {
              oldNode.addAttribute(attr);
            }
          }
          break;
        case Attribute::atInt:
        case Attribute::atFloat:
          {
            if (attributeNumericMode == Graph::nmmAddNewAttributes) {
              // if add new mode is on
              oldNode.addAttribute(attr);
            } else {
              Attribute::AttributeIterator attrItForAttr = oldNode.findAttribute(attr.getType(), attr.getName(), attr.getContext());
              bool foundEqualAttribute = false;
              if(attrItForAttr.hasNext()) {
                Attribute& eqAttr = attrItForAttr.next();
                if(attributeNumericMode == Graph::nmmDropOldAttributes)
                  oldNode.deleteAttribute(eqAttr); // found old attribuute and drop it
                else if(attributeNumericMode == Graph::nmmSummarizeAttributes) {
                  // summarize attributes
                  if(attr.getType() == Attribute::atInt) {
                    static_cast<AttributeInt&>(eqAttr).incValue(static_cast<AttributeInt&>(attr).getValue());
                  } else if (attr.getType() == Attribute::atFloat) {
                    static_cast<AttributeFloat&>(eqAttr).incValue(static_cast<AttributeFloat&>(attr).getValue());
                  }
                  foundEqualAttribute = true;
                  break;
                }
              }
              
              if( (foundEqualAttribute && attributeNumericMode == Graph::nmmDropOldAttributes ) || // if we found attribute and drop mode is on
                (!foundEqualAttribute && attributeNumericMode == Graph::nmmSummarizeAttributes)     // id we not found attribute and sum mode is on
                ) {
                oldNode.addAttribute(attr);
              } 
            }
          }
          break;
        default:
          break;
      }
    }
  }

  void Graph::convertNodeMerge(Node& newNode, Graph& oldGraph, Graph::MergeMode mode, Graph::CompsiteAndStringMergeMode attributeStringAndCompositeMode, Graph::NumericMergeMode attributeNumericMode) {
    Node oldNode = oldGraph.findNode(newNode.getUID());
    if(oldNode == Graph::invalidNode) {
      // we can add node to graph
      oldGraph.addNode(newNode);
    } else {
      // we have to merge nodes
      switch(mode) {
        case Graph::mmDropNewAttributes:
          // throw all new attribute, we not convert anything
          break;
        case Graph::mmDropOldAttributes:
          // throw all old attribute
          convertOnlyNewAttribute(oldNode, newNode);
          break;
        case Graph::mmUnionAttribute:
          // union attributes
          convertSummarizeAttribute(oldNode, newNode, attributeStringAndCompositeMode, attributeNumericMode);
          break;
        default:
          break;
      }
    }

  }

  void Graph::convertEdgeAttribute(Edge& oldEdge, Edge& newEdge, Graph& oldGraph, Graph::MergeMode mode, Graph::CompsiteAndStringMergeMode attributeStringAndCompositeMode, Graph::NumericMergeMode attributeNumericMode) {
    // we have to merge nodes
    switch(mode) {
      case Graph::mmDropNewAttributes:
        // throw all new attribute, we not convert anything
        break;
      case Graph::mmDropOldAttributes:
        // throw all old attribute
        convertOnlyNewAttribute(oldEdge, newEdge);
        break;
      case Graph::mmUnionAttribute:
        // union attributes
        convertSummarizeAttribute(oldEdge, newEdge, attributeStringAndCompositeMode, attributeNumericMode);
        break;
      default:
        break;
    }
  }

  void Graph::convertEdgeMerge(multimap<string, Edge>& oldNodeTargets, Edge& newEdge, Graph& oldGraph, Graph::MergeMode mode,
      Graph::CompsiteAndStringMergeMode attributeStringAndCompositeMode, Graph::NumericMergeMode attributeNumericMode) {
    Node fromNode = newEdge.getFromNode();
    Node toNode = newEdge.getToNode();
    const string& fromNodeUID = fromNode.getUID();
    const string& toNodeUID = toNode.getUID();
    Edge::EdgeType newEdgeType = newEdge.getType();
    Edge oldEdge;

    if (oldNodeTargets.size()) {
      pair<multimap<string, Edge>::iterator, multimap<string, Edge>::iterator> eqr = oldNodeTargets.equal_range(toNodeUID);
      for (multimap<string, Edge>::iterator eit = eqr.first; eit != eqr.second; ++eit) {
        Edge edge = eit->second;
        if (edge.getType() == newEdgeType) {
          oldEdge = edge;
          break;
        }
      }
    }

#if 0
    Node oldNode = oldGraph.findNode(fromNodeUID);
    const string& newEdgeName = newEdgeType.getType();
    out_edge_iter it,e_begin, e_end;
    boost::tie(e_begin, e_end) = out_edges( oldNode.vertex , *oldNode.g->getBGraph());
    for(it = e_begin; it != e_end; ++it ) {
      if(  ( get(edge_direction,*oldNode.g->getBGraph(),*it) != get(edge_direction,*newEdge.g->getBGraph(),newEdge.edge) )
        || ( newEdgeName != oldNode.g->strTable->get(get(edge_type,*oldNode.g->getBGraph(),*it)) )
      ) {
        continue;
      }
      Edge edge(oldNode.g, *it);
      if(edge.getToNode().getUID() == toNodeUID) {
        oldEdge = edge;
        break;
      }
    }

//    replaced with boost specific code
//    Edge::EdgeIterator edgeIt = oldNode.findOutEdges(newEdgeType);
//    while(edgeIt.hasNext()) {
//      Edge edge = edgeIt.next();
//      if(edge.getToNode().getUID() == toNodeUID) {
//        oldEdge = edge;
//        break;
//      }
//    }
#endif

    Edge pairEdge = newEdge.getReversePair();
    if(oldEdge == Graph::invalidEdge) {
      // edge not exist in old graph, we create it
      Edge oldEdgePair;
      if(pairEdge == Graph::invalidEdge) {
        // edge doesn't have pair
        oldEdge = oldGraph.createDirectedEdge(fromNodeUID, toNodeUID, newEdgeType.getType(), false );
      } else {
        // edge has pair
        if(newEdgeType.getDirectionType() == Edge::edtDirectional) {
          oldEdge = oldGraph.createDirectedEdge(fromNodeUID, toNodeUID, newEdgeType.getType(), true );
          oldEdgePair = oldEdge.getReversePair();
        } else if(newEdgeType.getDirectionType() == Edge::edtBidirectional) {
          oldEdge = oldGraph.createBidirectedEdge(fromNodeUID, toNodeUID, newEdgeType.getType());
          oldEdgePair = oldEdge.getReversePair();
        }
      }
      // add attributes to old edge
      Attribute::AttributeIterator attrIt = newEdge.getAttributes();
      while(attrIt.hasNext()) {
        Attribute& attr = attrIt.next();
        oldEdge.addAttribute(attr);
      }
      // add attributes to old edgePair
      if( !(oldEdgePair == Graph::invalidEdge) && !(pairEdge == Graph::invalidEdge) ) {
        attrIt = pairEdge.getAttributes();
        while(attrIt.hasNext()) {
          Attribute& attr = attrIt.next();
          oldEdgePair.addAttribute(attr);
        }
      }
    } else {
      Edge::EdgeType oldEdgeType = oldEdge.getType();
      Edge oldEdgePair = oldEdge.getReversePair();
      // add attributes to old edge
      if( (newEdgeType.getDirectionType() == Edge::edtDirectional) && (pairEdge == Graph::invalidEdge)) { // new edge is directed
        if(oldEdgeType.getDirectionType() == Edge::edtDirectional && (oldEdgePair == Graph::invalidEdge) ) { // old edge is directed
          convertEdgeAttribute(newEdge, oldEdge, oldGraph, mode, attributeStringAndCompositeMode, attributeNumericMode);
        } else if(oldEdgeType.getDirectionType() == Edge::edtBidirectional) { // old edge is bidirectiona
          convertEdgeAttribute(newEdge, oldEdge, oldGraph, mode, attributeStringAndCompositeMode, attributeNumericMode);
        } else if(oldEdgeType.getDirectionType() == Edge::edtDirectional){  // old edge is directional with reverse
          convertEdgeAttribute(newEdge, oldEdge, oldGraph, mode, attributeStringAndCompositeMode, attributeNumericMode);
        }
      } else if(newEdgeType.getDirectionType() == Edge::edtBidirectional) { // new edge is bidirectional

        if(oldEdgeType.getDirectionType() == Edge::edtDirectional && (oldEdgePair == Graph::invalidEdge) ) { // old edge is directed
          oldGraph.convertEdgeToBidirectional(oldEdge);
          oldEdgePair = oldEdge.getReversePair();
          convertEdgeAttribute(oldEdge, newEdge, oldGraph, mode, attributeStringAndCompositeMode, attributeNumericMode);
          convertEdgeAttribute(oldEdgePair, pairEdge,  oldGraph, mode, attributeStringAndCompositeMode, attributeNumericMode);
        } else if(oldEdgeType.getDirectionType() == Edge::edtBidirectional) { // old edge is bidirectiona
          convertEdgeAttribute(oldEdge, newEdge, oldGraph, mode, attributeStringAndCompositeMode, attributeNumericMode);
          convertEdgeAttribute(oldEdgePair, pairEdge, oldGraph, mode, attributeStringAndCompositeMode, attributeNumericMode);
        } else if(oldEdgeType.getDirectionType() == Edge::edtDirectional){  // old edge is directional with reverse
          convertEdgeAttribute(oldEdge, newEdge, oldGraph, mode, attributeStringAndCompositeMode, attributeNumericMode);
          convertEdgeAttribute(oldEdgePair, pairEdge, oldGraph, mode, attributeStringAndCompositeMode, attributeNumericMode);
        }
      } else if(newEdgeType.getDirectionType() == Edge::edtDirectional) { // new edge is directional with reverse
        if(oldEdgeType.getDirectionType() == Edge::edtDirectional && (oldEdgePair == Graph::invalidEdge) ) { // old edge is directed
          oldEdgePair = oldGraph.createReservePair(oldEdge);
          convertEdgeAttribute(oldEdge, newEdge, oldGraph, mode, attributeStringAndCompositeMode, attributeNumericMode);
          convertEdgeAttribute(oldEdge, pairEdge, oldGraph, mode, attributeStringAndCompositeMode, attributeNumericMode);
        } else if(oldEdgeType.getDirectionType() == Edge::edtBidirectional) { // old edge is bidirectional
          oldGraph.convertEdgeToDirectionalWithReverse(oldEdge);
          oldEdgePair = oldEdge.getReversePair();
          convertEdgeAttribute(oldEdge, newEdge, oldGraph, mode, attributeStringAndCompositeMode, attributeNumericMode);
          convertEdgeAttribute(oldEdge, pairEdge, oldGraph, mode, attributeStringAndCompositeMode, attributeNumericMode);
        } else if(oldEdgeType.getDirectionType() == Edge::edtDirectional){  // old edge is directional with reverse
          convertEdgeAttribute(oldEdge, newEdge, oldGraph, mode, attributeStringAndCompositeMode, attributeNumericMode);
          convertEdgeAttribute(oldEdge, pairEdge, oldGraph, mode, attributeStringAndCompositeMode, attributeNumericMode);
        }
      }
    }
  }


  void Graph::merge(Graph& graph, Graph::MergeMode nodeMode, Graph::CompsiteAndStringMergeMode nodeAttributeStringAndCompositeMode, Graph::NumericMergeMode nodeAttributeNumericMode,
    Graph::MergeMode edgeMode, Graph::CompsiteAndStringMergeMode edgeAttributeStringAndCompositeMode, Graph::NumericMergeMode edgeAttributeNumericMode) {
    // convert all nodes from 'graph' to this graph
    set<Node> visitedNodes;
    set<Edge> visitedEdges;
    Node::NodeIterator nodeIt = graph.getNodes();
    while(nodeIt.hasNext()) {
      Node newNode = nodeIt.next();
      // convert node
      if(visitedNodes.find(newNode) == visitedNodes.end() ) {
        visitedNodes.insert(newNode);
        convertNodeMerge(newNode, *this, nodeMode, nodeAttributeStringAndCompositeMode, nodeAttributeNumericMode);
      }
      multimap<string, Edge> oldNodeTargets;
      Node oldNode = this->findNode(newNode.getUID());
      if (!(oldNode == Graph::invalidNode)) {
        Edge::EdgeIterator eit = oldNode.getOutEdges();
        while (eit.hasNext()) {
          Edge edge = eit.next();
          oldNodeTargets.insert(make_pair(edge.getToNode().getUID(), edge));
        }
      }

      // convert edges
      Edge::EdgeIterator edgeIt = newNode.getOutEdges();
      while(edgeIt.hasNext()) {
        Edge newEdge = edgeIt.next();
        Node toNode = newEdge.getToNode();
        if(visitedNodes.find(toNode) == visitedNodes.end() ) {
          visitedNodes.insert(toNode);
          convertNodeMerge(toNode, *this, nodeMode, nodeAttributeStringAndCompositeMode, nodeAttributeNumericMode);
        }
        // convert edge
        if( (newEdge.getType().getDirectionType() != Edge::edtReverse) && (visitedEdges.find(newEdge) == visitedEdges.end()) ) {
          visitedEdges.insert(newEdge);
          Edge edgePair = newEdge.getReversePair();
          if(!(edgePair == invalidEdge))
            visitedEdges.insert(edgePair);
          convertEdgeMerge(oldNodeTargets, newEdge, *this, edgeMode, edgeAttributeStringAndCompositeMode, edgeAttributeNumericMode);
        }
      }
    }
    
    // merge the headerinfo
    for (StringMap::const_iterator pairIt = graph.headerInformations.begin(); pairIt != graph.headerInformations.end(); ++pairIt) {
      setHeaderInfo(graph.strTable->get(pairIt->first), graph.strTable->get(pairIt->second));
    }
    
  }

  void Graph::mergeWithBinary(const string& filename, Graph::MergeMode nodeMode, Graph::CompsiteAndStringMergeMode nodeAttributeStringAndCompositeMode, Graph::NumericMergeMode nodeAttributeNumericMode,
    Graph::MergeMode edgeMode, Graph::CompsiteAndStringMergeMode edgeAttributeStringAndCompositeMode, Graph::NumericMergeMode edgeAttributeNumericMode) {
    Graph mergeGraph;
    mergeGraph.loadBinary(filename);
    merge(mergeGraph, nodeMode, nodeAttributeStringAndCompositeMode, nodeAttributeNumericMode, edgeMode, edgeAttributeStringAndCompositeMode, edgeAttributeNumericMode);
  }

  void Graph::mergeWithXML(const string& filename, Graph::MergeMode nodeMode, Graph::CompsiteAndStringMergeMode nodeAttributeStringAndCompositeMode, Graph::NumericMergeMode nodeAttributeNumericMode,
    Graph::MergeMode edgeMode, Graph::CompsiteAndStringMergeMode edgeAttributeStringAndCompositeMode, Graph::NumericMergeMode edgeAttributeNumericMode) {
    Graph mergeGraph;
    mergeGraph.loadXML(filename);
    merge(mergeGraph, nodeMode, nodeAttributeStringAndCompositeMode, nodeAttributeNumericMode, edgeMode, edgeAttributeStringAndCompositeMode, edgeAttributeNumericMode);
  }

}}
