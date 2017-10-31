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
#include "../privinc/GraphSchemaReader.h"
#include "../privinc/messages.h"
#include <algorithm>

using namespace std;
using namespace boost;

namespace columbus {  namespace graph {

  Node::Node(Graph* g, GraphVertex vertex) :
    g(g),
    vertex(vertex)
  {
  }

  Node::Node() 
    : g(NULL) 
    , vertex()
  {
  }

  Node::Node(const Node& node) :
    g(node.g),
    vertex(node.vertex)
  {
  }

  Attribute& Node::addAttribute(const Attribute& attribute){

    if(g == NULL)
      throw InvalidSetter( COLUMBUS_LOCATION, CMSG_EX_NO_ADD_ATTRIBUTE_TO_INVALID_NODE);

    if(attribute.graph == NULL) 
      throw InvalidSetter( COLUMBUS_LOCATION, CMSG_EX_NO_ADD_INVALID_ATTRIBUTE_TO_NODE);

    AttributeList *attributes = get(vertex_attributes,*g->getBGraph(),vertex);

  /*  for(AttributeList::iterator it = attributes->begin(); it != attributes->end(); it++){
      if(attribute.equals(**it)) throw AlreadyExist("Node::addAttribute(const Attribute& attribute)","Attribute is already exist in " + getUID());
    }*/
    
    if(!g->gsReader->canAddAttributeToNode(getType().getType(), attribute) )
      throw GraphSchemaException( COLUMBUS_LOCATION, CMSG_EX_CANT_ADD_ATTRIBUTE_TO_NODE( attribute.getName(), getType().getType()));

    Attribute *attr = attribute.copy();
    if(attribute.graph != g) {
      attr->setGraph(g);
      attr->copyStrings(attribute.graph->getStrTable(),g->getStrTable());
    }

    attributes->push_back(attr);
    
    return *attr;
  }

  void Node::deleteAttributes() {
    if(g == NULL)
      throw InvalidSetter( COLUMBUS_LOCATION, CMSG_EX_NO_DEL_ATTRIBUTE_TO_INVALID_NODE);
    AttributeList *attributes = get(vertex_attributes,*g->getBGraph(),vertex);
    for(AttributeList::iterator it = attributes->begin(); it != attributes->end(); it++){
      delete *it;
    }
    attributes->clear();
  }

  bool Node::deleteAttribute(const Attribute& attribute){
    if(g == NULL)
      throw InvalidSetter( COLUMBUS_LOCATION, CMSG_EX_NO_DEL_ATTRIBUTE_TO_INVALID_NODE);
    AttributeList *attributes = get(vertex_attributes,*g->getBGraph(),vertex);
    for(AttributeList::iterator it = attributes->begin(); it != attributes->end(); it++){
      if( attribute == **it ) {
        delete *it;
        attributes->erase(it);
        return true;
      }
    }
    return false;
  }

  bool Node::deleteAttribute(Attribute::aType type, const string& name){
    bool deleted = false;
    if(g == NULL)
      throw InvalidSetter( COLUMBUS_LOCATION, CMSG_EX_NO_DEL_ATTRIBUTE_TO_INVALID_NODE);
    AttributeList *attributes = get(vertex_attributes,*g->getBGraph(),vertex);
    for(AttributeList::iterator it = attributes->begin(); it != attributes->end(); ){
      if( ((**it).getName() == name) && ((**it).getType() == type) ) {
        delete *it;
        attributes->erase(it++);
        deleted = true;
      } else 
        ++it;
    }
    return deleted;
  }

  bool Node::deleteAttribute(Attribute::aType type, const string& name, const string& context){
    bool deleted = false;
    if(g == NULL)
      throw InvalidSetter( COLUMBUS_LOCATION, CMSG_EX_NO_DEL_ATTRIBUTE_TO_INVALID_NODE);
    AttributeList *attributes = get(vertex_attributes,*g->getBGraph(),vertex);
    for(AttributeList::iterator it = attributes->begin(); it != attributes->end(); ){
      if( ((**it).getName() == name) && ((**it).getType() == type) && ((**it).getContext() == context )) {
        delete *it;
        attributes->erase(it++);
        deleted = true;
      } else 
        ++it;
    }
    return deleted;
  }

  bool Node::deleteAttribute(Attribute::aType type){
    if(g == NULL)
      throw InvalidSetter( COLUMBUS_LOCATION, CMSG_EX_NO_DEL_ATTRIBUTE_TO_INVALID_NODE);
    bool deleted = false;
    AttributeList *attributes = get(vertex_attributes,*g->getBGraph(),vertex);
    for(AttributeList::iterator it = attributes->begin(); it != attributes->end(); ){
      if( ((**it).getType() == type) ) {
        delete *it;
        attributes->erase(it++);
        deleted = true;
      } else
        ++it;
    }
    return deleted;
  }

  bool Node::deleteAttribute(const string& context){
    bool deleted = false;
    if(g == NULL)
      throw InvalidSetter( COLUMBUS_LOCATION, CMSG_EX_NO_DEL_ATTRIBUTE_TO_INVALID_NODE);
    AttributeList *attributes = get(vertex_attributes,*g->getBGraph(),vertex);
    for(AttributeList::iterator it = attributes->begin(); it != attributes->end(); ){
      if( ((**it).getContext() == context) ) {
        delete *it;
        attributes->erase(it++);
        deleted = true;
      } else 
        ++it;
    }
    return deleted;
  }

  Attribute::AttributeIterator Node::getAttributes() const{
    if(g == NULL)
      throw InvalidGetter( COLUMBUS_LOCATION, CMSG_EX_INVALID_NODE_NO_ATTRIBUTE);
    return Attribute::AttributeIterator( g->getAttributeList(vertex), g->getAttributeIteratorOnVertex(vertex), g, vertex);
  }

  Attribute::AttributeIterator Node::findAttributeByType(Attribute::aType type) const {
    if(g == NULL)
      throw InvalidGetter( COLUMBUS_LOCATION, CMSG_EX_INVALID_NODE_NO_ATTRIBUTE);
    Attribute::AttributeIterator::FilterFlags filter(true, false, false);
    return Attribute::AttributeIterator(g->getAttributeList(vertex), g->getAttributeIteratorOnVertex(vertex), g, vertex, filter, type, "", "");
  }

  Attribute::AttributeIterator Node::findAttributeByName(const string& name) const {
    if(g == NULL)
      throw InvalidGetter( COLUMBUS_LOCATION, CMSG_EX_INVALID_NODE_NO_ATTRIBUTE);
    Attribute::AttributeIterator::FilterFlags filter(false, true, false);
    return Attribute::AttributeIterator(g->getAttributeList(vertex), g->getAttributeIteratorOnVertex(vertex), g, vertex, filter, Attribute::atInt, name, "");
  }

  Attribute::AttributeIterator Node::findAttributeByContext(const string& context) const {
    if(g == NULL)
      throw InvalidGetter( COLUMBUS_LOCATION, CMSG_EX_INVALID_NODE_NO_ATTRIBUTE);
    Attribute::AttributeIterator::FilterFlags filter(false, false, true);
    return Attribute::AttributeIterator(g->getAttributeList(vertex), g->getAttributeIteratorOnVertex(vertex), g, vertex, filter, Attribute::atInt, "", context);
  }


  Attribute::AttributeIterator Node::findAttribute(Attribute::aType type, const string& name, const string& context) const{
  /*  if(g == NULL)
      throw InvalidGetter("Node::findAttribute(Attribute::aType type, const String& name)","Invalid node doesn't has attribute");
    AttributeList *attributes = get(vertex_attributes,*g->getBGraph(),vertex);
    for(AttributeList::iterator it = attributes->begin(); it != attributes->end(); it++){
      if( ((**it).getName() == name) && ((**it).getType() == type) && ((**it).getContext() == context) ) {
        return **it;
      }
    }
    return (Attribute&)Graph::invalidAttribute;*/

    if(g == NULL)
      throw InvalidGetter( COLUMBUS_LOCATION, CMSG_EX_INVALID_NODE_NO_ATTRIBUTE);
    Attribute::AttributeIterator::FilterFlags filter(true, true, true);
    return Attribute::AttributeIterator(g->getAttributeList(vertex), g->getAttributeIteratorOnVertex(vertex), g, vertex, filter, type, name, context);

  }

  Edge::EdgeIterator Node::getOutEdges() const{
    if(g == NULL)
      throw InvalidGetter("Node::getOutEdges()","Invalid node don't has out edges");
    out_edge_iter e_begin, e_end;
    boost::tie(e_begin, e_end) = out_edges(vertex, *g->getBGraph());

    return Edge::EdgeIterator(e_begin,e_end,g->getEdgeIteratorOnNode(vertex),g, vertex,Edge::EdgeTypeSet());
  }

  Edge::EdgeIterator Node::findOutEdges(const Edge::EdgeType& type) const {
    if(g == NULL)
      throw InvalidGetter( COLUMBUS_LOCATION, CMSG_EX_INVALID_NODE_NO_OUT_EDGES);
    out_edge_iter e_begin, e_end;
    boost::tie(e_begin, e_end) = out_edges(vertex, *g->getBGraph());
    Edge::EdgeTypeSet typeSet;
    typeSet.insert(type);
    return Edge::EdgeIterator(e_begin,e_end,g->getEdgeIteratorOnNode(vertex), g, vertex,typeSet);
  }

  Edge::EdgeIterator Node::findOutEdges(const Edge::EdgeTypeSet& types) const {
    if(g == NULL)
      throw InvalidGetter( COLUMBUS_LOCATION, CMSG_EX_INVALID_NODE_NO_OUT_EDGES);
    out_edge_iter e_begin, e_end;
    boost::tie(e_begin, e_end) = out_edges(vertex, *g->getBGraph());

    return Edge::EdgeIterator(e_begin,e_end,g->getEdgeIteratorOnNode(vertex),g, vertex,types);
  }


  Node::NodeType Node::getType() const {
    if(g == NULL)
      throw InvalidGetter( COLUMBUS_LOCATION, CMSG_EX_INVALID_NODE_NO_TYPE);
    return g->getVertexType(vertex);
  }

  void Node::setType(const NodeType& type) {
    if(g == NULL)
      throw InvalidSetter( COLUMBUS_LOCATION, CMSG_EX_INVALID_NODE_NO_TYPE);
    Key typeKey = g->strTable->set(type.getType());
    IndexMapVertexTypes types = get(vertex_type,*(g->getBGraph()));
    put(types,vertex,typeKey);
  }

  const string& Node::getUID() const{
    if(g == NULL)
      throw InvalidGetter( COLUMBUS_LOCATION, CMSG_EX_INVALID_NODE_NO_UID);
    return g->getVertexUID(vertex);
  }

  void Node::setUID(const string& UID) {
    if(g == NULL)
      throw InvalidGetter( COLUMBUS_LOCATION, CMSG_EX_INVALID_NODE_NO_UID);
    g->setVertexUID(vertex, UID);
  }

  bool Node::equals(const Node& node) const{
    if( (g == NULL) && (node.g == NULL) )
      return true;
    
    if( (g == NULL) || (node.g == NULL) )
      return false;
    
    if(g != node.g)
      return false;
    
    return (get(vertex_UID, *g->getBGraph(), vertex) == get(vertex_UID, *node.g->getBGraph(), node.vertex));
  }

  int Node::hashCode() const {
    if(g == NULL)
      return 0;
    size_t hash = get(vertex_UID, *g->getBGraph(), vertex);
    hash ^= (size_t)g;
    HASHLONGTOINT(hash);
    return (int)hash;
  }

  bool Node::operator==(const Node& node) const {
    return equals(node);
  }

  bool Node::operator!=(const Node& node) const {
    return !equals(node);
  }

  bool Node::operator<(const Node& node) const {
    if( (g == NULL) && (node.g == NULL) )
      return false;
    
    if( (g == NULL) )
      return true;
    
    if( (node.g == NULL) )
      return false;

    if (g == node.g) {
      return (get(vertex_UID, *g->getBGraph(), vertex) < get(vertex_UID, *node.g->getBGraph(), node.vertex));
    } else  {
      return (getUID() < node.getUID());
      
    }
  }


  Node& Node::operator=(const Node& node) {
    g = node.g;
    vertex = node.vertex;
    return (*this);
  }

  Node::~Node(){
  }

  Node::NodeIterator::NodeIterator(vertex_iter container_begin,vertex_iter container_end, IteratorContainer *itContainer, Graph* graph, const NodeTypeSet &filteredNodes) :
    graph(graph),
    container_begin(container_begin),
    container_end(container_end),
    iterators(itContainer),
    filteredNodes(filteredNodes),
    it(),
    lastOp(op_None)
  {
    iterators->push_back(this);
  }

  void Node::NodeIterator::add(const Node &node) {
  }

  void Node::NodeIterator::remove() {
    switch (lastOp) {
      case op_None:
      case op_Add:
      case op_Remove:
        throw GraphInvalidIteratorException( COLUMBUS_LOCATION, CMSG_EX_ERROR_CALL_ORDER);
      case op_Next:
      case op_Previous:
        it = safeRemove(it);
        it = findNextNotFiltered(false, it);
        break;
      case op_Invalidated:
        throw GraphInvalidIteratorException( COLUMBUS_LOCATION, CMSG_EX_INVALID_ITERATOR);
    }

    lastOp = op_Remove;
  }

  Node::NodeIterator::NodeIterator() :
    graph(NULL),
    container_begin(),
    container_end(),
    iterators(NULL),
    filteredNodes(NodeTypeSet()),
    it(),
    lastOp(op_Invalidated)
  {
  }

  Node::NodeIterator::NodeIterator(const NodeIterator &iterator) :
    graph(iterator.graph),
    container_begin(iterator.container_begin),
    container_end(iterator.container_end),
    iterators(iterator.iterators),
    filteredNodes(iterator.filteredNodes),
    it(),
    lastOp(iterator.lastOp)
  {
    if (lastOp != op_Invalidated && iterators)
      iterators->push_back(this);
  }

  Node::NodeIterator::~NodeIterator() {
    if (lastOp != op_Invalidated) {
      for (IteratorContainer::iterator _it = iterators->begin(); _it != iterators->end(); ++_it) {
        if (*_it == this) {
          iterators->erase(_it);
          return;
        }
      }
    }
  }

  Node::NodeIterator& Node::NodeIterator::operator=(const NodeIterator &otherIt) {
    if (this == &otherIt)
      return *this;

    if (otherIt.lastOp == op_Invalidated)
      throw GraphInvalidIteratorException( COLUMBUS_LOCATION, CMSG_EX_INVALID_ITERATOR);

    bool insertIntoIterators = true;
    if (lastOp != op_Invalidated && iterators) {
      if (iterators == otherIt.iterators) {
        insertIntoIterators = false;
      } else {
        for (NodeIterator::IteratorContainer::iterator _it = iterators->begin(); _it != iterators->end(); ++_it) {
          if (*_it == this) {
            iterators->erase(_it);
            break;
          }
        }
      }
    }

    if (otherIt.lastOp != op_None)
      it = otherIt.it;
    
    container_begin = otherIt.container_begin;
    container_end = otherIt.container_end;
    iterators = otherIt.iterators;
    lastOp = otherIt.lastOp;
    graph = otherIt.graph;
    filteredNodes = otherIt.filteredNodes;

    if (lastOp != op_Invalidated && iterators && insertIntoIterators)
      iterators->push_back(this);

    return *this;
  }

  bool Node::NodeIterator::hasNext() {
    return nextItem() != container_end;
  }

  Node Node::NodeIterator::next() {
    it = nextItem();
    lastOp = op_Next;

    if (it == container_end)
        throw GraphNoSuchElementException( COLUMBUS_LOCATION, CMSG_EX_ITERATOR_NOT_NEXT_ELEMENT);

    return Node(graph,*it);
  }

  bool Node::NodeIterator::hasPrevious() {
    return previousItem() != container_end;
  }

  Node Node::NodeIterator::previous() {
    it = previousItem();
    lastOp = op_Previous;

    if (it == container_end)
        throw GraphNoSuchElementException( COLUMBUS_LOCATION, CMSG_EX_ITERATOR_NOT_PREVIUS_ELEMENT);

    return Node(graph,*it);
  }

  bool Node::NodeIterator::equals(const NodeIterator& otherIt) const {
    if (lastOp == op_Invalidated)
      throw GraphInvalidIteratorException( COLUMBUS_LOCATION, CMSG_EX_INVALID_ITERATOR);

    return this == &otherIt;
  }

  int Node::NodeIterator::hashCode() const {
    size_t hash = (size_t)this;
    HASHLONGTOINT(hash);
    return (int)hash;
  }

  vertex_iter Node::NodeIterator::findNextNotFiltered(bool inc, const vertex_iter& _it) {

    vertex_iter j = _it;

    if(!filteredNodes.empty()) {

      if( (j != container_end) && !inc && (filteredNodes.find(NodeType(graph->getVertexType(*j))) == filteredNodes.end()))
        inc = true;
      if(inc) {
        ++j;
        while( j != container_end ) {
          if(filteredNodes.find(NodeType(graph->getVertexType(*j))) != filteredNodes.end()) {
            return j;
          }
          ++j;
        }      
        return container_end;
      } else {
        return j;
      }
    } else {

      if (j == container_end && inc)
        return container_end;

      if (inc) 
        ++j;

      return j;
    }

  }

  vertex_iter Node::NodeIterator::nextItem() {
    switch (lastOp) {
      case op_None:       return findNextNotFiltered(false, container_begin);
      case op_Add:        return findNextNotFiltered(true, it);
      case op_Remove:     return findNextNotFiltered(false, it);
      case op_Next:       return findNextNotFiltered(true, it);
      case op_Previous:   return it;
      case op_Invalidated:
        throw GraphInvalidIteratorException( COLUMBUS_LOCATION, CMSG_EX_INVALID_ITERATOR);
    }
    return container_end;
  }

  vertex_iter Node::NodeIterator::findPreviousNotDeletedFiltered(bool dec, const vertex_iter& _it) {
    vertex_iter j = _it;

    if(!filteredNodes.empty()) {

      if((j != container_end) && !dec && (filteredNodes.find(NodeType(graph->getVertexType(*j))) == filteredNodes.end()) )
        dec = true;
      if(dec) {
        --j;
        while( j != container_begin ) {
          if(filteredNodes.find(NodeType(graph->getVertexType(*j))) != filteredNodes.end()) {
            return j;
          }
          --j;
        }      
        return container_end;
      } else {
        return j;
      }
    } else {

      if (j == container_begin && dec)
        return container_end;

      if (dec) 
        --j;

      return j;
    }

  }

  vertex_iter Node::NodeIterator::previousItem() {
    switch (lastOp) {
      case op_None:       return findPreviousNotDeletedFiltered(false,container_end);
      case op_Add:        return it;
      case op_Remove:     return findPreviousNotDeletedFiltered(true, it);
      case op_Next:       return it;
      case op_Previous:   return findPreviousNotDeletedFiltered(true, it);
      case op_Invalidated:
        throw GraphInvalidIteratorException( COLUMBUS_LOCATION, CMSG_EX_INVALID_ITERATOR);
    }
    return container_end;
  }

 vertex_iter Node::NodeIterator::safeRemove(const vertex_iter &_it) {
    vertex_iter nextElement = _it;
    ++nextElement;

    for (IteratorContainer::iterator icIt = iterators->begin(); icIt != iterators->end(); ++icIt) {
      if (((*icIt)->it == _it) && (*icIt != this)) {
        (*icIt)->it = nextElement;
        (*icIt)->lastOp = op_Remove;
      }
    }

    clear_vertex(*_it,*graph->getBGraph());
    remove_vertex(*_it,*graph->getBGraph());
    return nextElement;
 }

  void Node::NodeIterator::invalidate() {
    lastOp = op_Invalidated;
  }

  // end Node iterator

  // NodeType

  Node::NodeType::NodeType(const string &type) :
    _type(type)
  {
  }

  const string& Node::NodeType::getType() const {
    return _type;
  }

  Node::NodeType::NodeType(const NodeType &NTYPE) : 
    _type(NTYPE._type)
  {
  }

  Node::NodeType& Node::NodeType::operator =(const Node::NodeType& NTYPE) {
    this->_type = NTYPE._type;
    return *this;
  }

  bool Node::NodeType::operator ==(const NodeType& nodeType) const {
    return (getType() == nodeType.getType());
  }

  bool Node::NodeType::operator !=(const NodeType& nodeType) const {
    return (getType() != nodeType.getType());
  }

  bool Node::NodeType::operator<(const NodeType& nodeType) const {
    return this->getType() < nodeType.getType();
  }

  //end NodeType

}}
