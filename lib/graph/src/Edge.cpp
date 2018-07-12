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

#include "../inc/graph.h"
#include "../privinc/GraphSchemaReader.h"
#include "../privinc/messages.h"

using namespace std;

namespace columbus {  namespace graph {

  Edge::Edge(Graph* g, GraphEdge edge) :
    g(g),
    edge(edge)
  {
  }

  Edge::Edge() :
    g(NULL),
    edge()
  {
  }

  Edge::Edge(const Edge& cedge) :
    g(cedge.g),
    edge(cedge.edge)
  {
  }

  Attribute& Edge::addAttribute(const Attribute& attribute) {
    if(g == NULL)
      throw InvalidSetter( COLUMBUS_LOCATION, CMSG_EX_NO_ADD_ATTRIBUTE_TO_INVALID_EDGE);
    if(attribute.graph == NULL) 
      throw InvalidSetter( COLUMBUS_LOCATION, CMSG_EX_NO_ADD_INVALID_ATTRIBUTE_TO_EDGE);
    AttributeList *attributes = get(edge_attributes,*g->getBGraph(),edge);

/*    for(AttributeList::iterator it = attributes->begin(); it != attributes->end(); it++){
      if(attribute.equals(**it)) throw AlreadyExist("Edge::addAttribute(const Attribute& attribute)","Attribute is already exist");
    }*/

    if(!g->gsReader->canAddAttributeToEdge(getType().getType(), getType().getDirectionType(), getToNode().getType().getType(), getFromNode().getType().getType(), attribute))
      throw GraphSchemaException( COLUMBUS_LOCATION, CMSG_EX_CANT_ADD_ATTRIBUTE_TO_EDGE( attribute.getName(), getType().getType()));

    Attribute *attr;
    attr = attribute.copy();
    if(attribute.graph != g) {
      attr->setGraph(g);
      attr->copyStrings(attribute.graph->getStrTable(),g->getStrTable());
    }

    attributes->push_back(attr);
    return *attr;

  }

  void Edge::deleteAttributes() {
    if(g == NULL)
      throw InvalidSetter("Edge::deleteAttributes()","Can't del attribute to invalidEdge");
    AttributeList *attributes = get(edge_attributes,*g->getBGraph(),edge);
    for(AttributeList::iterator it = attributes->begin(); it != attributes->end(); it++){
      delete *it;
    }
    attributes->clear();
  }

  bool Edge::deleteAttribute(Attribute::aType type, const string& name, const string& context){
    bool deleted = false;
    if(g == NULL)
      throw InvalidSetter( COLUMBUS_LOCATION, CMSG_EX_NO_DEL_ATTRIBUTE_TO_INVALID_EDGE);
    AttributeList *attributes = get(edge_attributes,*g->getBGraph(),edge);
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


  bool Edge::deleteAttribute(const Attribute& attribute) {
    if(g == NULL)
      throw InvalidSetter( COLUMBUS_LOCATION, CMSG_EX_NO_DEL_ATTRIBUTE_TO_INVALID_EDGE);
    AttributeList *attributes = get(edge_attributes,*g->getBGraph(),edge);
    for(AttributeList::iterator it = attributes->begin(); it != attributes->end(); it++){
      if( attribute == **it ) {
        delete *it;
        attributes->erase(it);
        return true;
      } 
    }
    return false;
  }

  bool Edge::deleteAttribute(Attribute::aType type, const string& name){
    bool deleted = false;
    if(g == NULL)
      throw InvalidSetter( COLUMBUS_LOCATION, CMSG_EX_NO_DEL_ATTRIBUTE_TO_INVALID_EDGE);
    AttributeList *attributes = get(edge_attributes,*g->getBGraph(),edge);
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

  bool Edge::deleteAttribute(Attribute::aType type) {
    if(g == NULL)
      throw InvalidSetter( COLUMBUS_LOCATION, CMSG_EX_NO_DEL_ATTRIBUTE_TO_INVALID_EDGE);
    bool deleted = false;
    AttributeList *attributes = get(edge_attributes,*g->getBGraph(),edge);
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

  Attribute::AttributeIterator Edge::getAttributes() const {
    if(g == NULL)
      throw InvalidGetter( COLUMBUS_LOCATION, CMSG_EX_INVALID_EDGE_HASNOT_ATTRIBUTE);
    return Attribute::AttributeIterator( g->getAttributeList(edge),g->getAttributeIteratorOnEdge(edge), g, edge);
  }

  Attribute::AttributeIterator Edge::findAttribute(Attribute::aType type, const string& name, const string& context) const {
    if(g == NULL)
      throw InvalidGetter( COLUMBUS_LOCATION, CMSG_EX_INVALID_EDGE_HASNOT_ATTRIBUTE);
    Attribute::AttributeIterator::FilterFlags filter(true, true, true);
    return Attribute::AttributeIterator(g->getAttributeList(edge), g->getAttributeIteratorOnEdge(edge), g, edge, filter, type, name, context);

  }

  Attribute::AttributeIterator Edge::findAttributeByType(Attribute::aType type) const {
    if(g == NULL)
      throw InvalidGetter( COLUMBUS_LOCATION, CMSG_EX_INVALID_EDGE_HASNOT_ATTRIBUTE);
    Attribute::AttributeIterator::FilterFlags filter(true, false, false);
    return Attribute::AttributeIterator(g->getAttributeList(edge), g->getAttributeIteratorOnEdge(edge), g, edge, filter, type, "", "");
  }

  Attribute::AttributeIterator Edge::findAttributeByName(const string& name) const {
    if(g == NULL)
      throw InvalidGetter( COLUMBUS_LOCATION, CMSG_EX_INVALID_EDGE_HASNOT_ATTRIBUTE);
    Attribute::AttributeIterator::FilterFlags filter(false, true, false);
    return Attribute::AttributeIterator(g->getAttributeList(edge), g->getAttributeIteratorOnEdge(edge), g, edge, filter, Attribute::atInt, name, "");
  }

  Attribute::AttributeIterator Edge::findAttributeByContext(const string& context) const {
    if(g == NULL)
      throw InvalidGetter( COLUMBUS_LOCATION, CMSG_EX_INVALID_EDGE_HASNOT_ATTRIBUTE);
    Attribute::AttributeIterator::FilterFlags filter(false, false, true);
    return Attribute::AttributeIterator(g->getAttributeList(edge), g->getAttributeIteratorOnEdge(edge), g, edge, filter, Attribute::atInt, "", context);
  }


  Edge Edge::getReversePair() const {
    if(g == NULL)
      throw InvalidGetter( COLUMBUS_LOCATION, CMSG_EX_INVALID_EDGE_HASNOT_PAIR);
    if(g->hasEdgePair(edge)) {
      return Edge(g,g->getEdgePair(edge));
    }
    else
      return Graph::invalidEdge;
  }

  Node Edge::getFromNode() const {
    if(g == NULL)
      throw InvalidGetter( COLUMBUS_LOCATION, CMSG_EX_INVALID_EDGE_HASNOT_FROMNODE);
    GraphVertex from = source(edge, *g->getBGraph());
    return Node(g,from);
  }

  Node Edge::getToNode() const {
    if(g == NULL)
      throw InvalidGetter( CMSG_EX_INVALID_EDGE_HASNOT_FROMNODE, CMSG_EX_INVALID_EDGE_HASNOT_TONODE);
    GraphVertex to = target(edge, *g->getBGraph());
    return Node(g,to);
  }

  Edge::EdgeType Edge::getType() const {
    if(g == NULL)
      return EdgeType("",edtBidirectional);
    return g->getEdgeType(edge);
  }

  bool Edge::equals(const Edge& edge) const {
    if( (g == NULL) && (edge.g == NULL) )
      return true;
    if( (g == NULL) || (edge.g == NULL) )
      return false;
    return ( (this->edge == edge.edge) && (g == edge.g ) );
  }

  int Edge::hashCode() const {
    if(g == NULL) {
      return 0;
    }
    size_t hash = (size_t)g ^ (size_t)edge.m_source ^ (size_t)edge.m_target ^ (size_t)edge.m_eproperty;
    HASHLONGTOINT(hash);
    return (int)hash;
  }

  bool Edge::operator==(const Edge& edge) const{
    return equals(edge);
  }

  bool Edge::operator!=(const Edge& edge) const{
    return !equals(edge);
  }

  bool Edge::operator<(const Edge& edge) const{
    if( (g == NULL) && (edge.g == NULL) )
      return false;
    if( (g == NULL) )
      return true;
    if((edge.g == NULL) )
      return false;
    return this->edge < edge.edge;
    /*if(getFromNode() <  edge.getFromNode())
      return true;
    else if ( ! (getFromNode() == edge.getFromNode()) )
      return false;
    else return getType() < edge.getType();*/
  }

  string Edge::getName() const {

    const string& A = getFromNode().getUID();
    const string& B = getToNode().getUID();
    switch(getType().getDirectionType()) {
      case edtBidirectional:
        {
          if(A < B) {
            return A + getType().getType() + B;
          } else {
            return B + getType().getType() + A;
          }
          break;
        }
      case edtDirectional:
        {
          return A + getType().getType() + B;
          break;
        }
      case edtReverse:
        {
          return B + getType().getType() + A;
          break;
        }
      default:
        return "";
    }
  }

  // edge iteratior

  Edge::EdgeIterator::EdgeIterator(out_edge_iter container_begin,out_edge_iter container_end, IteratorContainer *itContainer,Graph* graph,  GraphVertex vertex, const EdgeTypeSet &filteredEdges) :
    graph(graph),
    vertex(vertex),
    container_begin(container_begin),
    container_end(container_end),
    it(),
    iterators(itContainer),
    lastOp(op_None)
  {
    for (EdgeTypeSet::const_iterator etsIt = filteredEdges.begin(); etsIt != filteredEdges.end(); ++etsIt) {
      this->filteredEdges.insert(make_pair(graph->getStrTable()->get(etsIt->getType()), etsIt->getDirectionType()));
    }
    
    iterators->push_back(this);
  }

  void Edge::EdgeIterator::add(const Edge &edge) {
/*    switch (lastOp) {
      case op_None:
       it = container_begin;
        break;
      case op_Next:
      case op_Add:
        ++it;
        break;
      case op_Invalidated:
        throw GraphInvalidIteratorException("Edge::EdgeIterator::add(const Edge &edge)", "The iterator is invalid.");
      case op_Previous:
      case op_Remove:
        break;
    }

    //it = container->insert(it, edge);

    lastOp = op_Add;*/
  }

  void Edge::EdgeIterator::remove() {
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

  Edge::EdgeIterator::EdgeIterator() :
    graph(NULL),
    vertex(),
    container_begin(),
    container_end(),
    it (),
    iterators(NULL),
    filteredEdges(),
    lastOp(op_Invalidated)
  {
  }

  Edge::EdgeIterator::EdgeIterator(const EdgeIterator &iterator) :
    graph(iterator.graph),
    vertex(iterator.vertex),
    container_begin(iterator.container_begin),
    container_end(iterator.container_end),
    it (iterator.it),
    iterators(iterator.iterators),
    filteredEdges(iterator.filteredEdges),
    lastOp(iterator.lastOp)
  {
    if (lastOp != op_Invalidated && iterators)
      iterators->push_back(this);
  }

  void Edge::EdgeIterator::removeIterator() {
    for (IteratorContainer::iterator _it = iterators->begin(); _it != iterators->end(); ++_it) {
      if (*_it == this) {
        iterators->erase(_it);
        break;
      }
    }
    if(iterators->empty()) {
      graph->removeEdgeIteratorContainer(vertex);
    }
  }

  Edge::EdgeIterator::~EdgeIterator() {
    if (lastOp != op_Invalidated) {
      removeIterator();
    }
  }

  Edge::EdgeIterator& Edge::EdgeIterator::operator=(const EdgeIterator &otherIt) {
    if (this == &otherIt)
      return *this;

    if (otherIt.lastOp == op_Invalidated)
      throw GraphInvalidIteratorException( COLUMBUS_LOCATION, CMSG_EX_INVALID_ITERATOR);

    bool insertIntoIterators = true;
    if (lastOp != op_Invalidated && iterators) {
      if (iterators == otherIt.iterators) {
        insertIntoIterators = false;
      } else {
        removeIterator();
      }
    }

    it = otherIt.it;
    container_begin = otherIt.container_begin;
    container_end = otherIt.container_end;
    iterators = otherIt.iterators;
    lastOp = otherIt.lastOp;
    graph = otherIt.graph;
    filteredEdges = otherIt.filteredEdges;

    if (lastOp != op_Invalidated && iterators && insertIntoIterators)
      iterators->push_back(this);

    return *this;
  }

  bool Edge::EdgeIterator::hasNext() {
    return nextItem() != container_end;
  }

  Edge Edge::EdgeIterator::next() {
    it = nextItem();
    lastOp = op_Next;

    if (it == container_end)
        throw GraphNoSuchElementException( COLUMBUS_LOCATION, CMSG_EX_ITERATOR_NOT_NEXT_ELEMENT);

    return Edge(graph,*it);
  }

  bool Edge::EdgeIterator::hasPrevious() {
    return previousItem() != container_end;
  }

  Edge Edge::EdgeIterator::previous() {
    it = previousItem();
    lastOp = op_Previous;

    if (it == container_end)
        throw GraphNoSuchElementException( COLUMBUS_LOCATION, CMSG_EX_ITERATOR_NOT_PREVIUS_ELEMENT);

    return Edge(graph,*it);
  }

  bool Edge::EdgeIterator::equals(const EdgeIterator& otherIt) const {
    if (lastOp == op_Invalidated)
      throw GraphInvalidIteratorException( COLUMBUS_LOCATION, CMSG_EX_INVALID_ITERATOR);
    return this == &otherIt;
  }

  int Edge::EdgeIterator::hashCode() const {
    size_t hash = (size_t)this;
    HASHLONGTOINT(hash);
    return (int)hash;
  }

  out_edge_iter Edge::EdgeIterator::findNextNotFiltered(bool inc, const out_edge_iter& _it) {

    out_edge_iter j = _it;

    if(!filteredEdges.empty()) {
      if( !inc && (j != container_end) && (filteredEdges.find(make_pair(get(edge_type,*graph->getBGraph(),*j), (Edge::eDirectionType)get(edge_direction,*graph->getBGraph(),*j))) == filteredEdges.end()))
        inc = true;
      if(inc) {
        ++j;
        while( j != container_end ) {
          if(filteredEdges.find(make_pair(get(edge_type,*graph->getBGraph(),*j), (Edge::eDirectionType)get(edge_direction,*graph->getBGraph(),*j))) != filteredEdges.end()) {
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

  out_edge_iter Edge::EdgeIterator::nextItem() {
    switch (lastOp) {
      case op_None:       return findNextNotFiltered(false, container_begin);
      case op_Add:        return findNextNotFiltered(true, it);
      case op_Remove:     return findNextNotFiltered(false, it);
      case op_Next:       return findNextNotFiltered(true, it);
      case op_Previous:   return it;
      case op_Invalidated:
        throw GraphInvalidIteratorException("Edge::EdgeIterator::nextItem()", "The iterator is invalid.");
    }
    return container_end;
  }


  out_edge_iter Edge::EdgeIterator::findPreviousNotDeletedFiltered(bool dec, const out_edge_iter& _it) {

    out_edge_iter j = _it;

    if(!filteredEdges.empty()) {

      if( (j != container_end) && !dec && (filteredEdges.find(make_pair(get(edge_type,*graph->getBGraph(),*j), (Edge::eDirectionType)get(edge_direction,*graph->getBGraph(),*j))) == filteredEdges.end()))
        dec = true;
      if(dec) {
        --j;
        while( j != container_begin ) {
          if(filteredEdges.find(make_pair(get(edge_type,*graph->getBGraph(),*j), (Edge::eDirectionType)get(edge_direction,*graph->getBGraph(),*j))) != filteredEdges.end()) {
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

  out_edge_iter Edge::EdgeIterator::previousItem() {
    switch (lastOp) {
      case op_None:       return container_end;
      case op_Add:        return it;
      case op_Remove:     return findPreviousNotDeletedFiltered(true, it);
      case op_Next:       return it;
      case op_Previous:   return findPreviousNotDeletedFiltered(true, it);
      case op_Invalidated:
        throw GraphInvalidIteratorException( COLUMBUS_LOCATION, CMSG_EX_INVALID_ITERATOR);
    }
    return container_end;
  }

  out_edge_iter Edge::EdgeIterator::safeRemove(const out_edge_iter &_it) {
    out_edge_iter nextElement = _it;
    ++nextElement;

    for (IteratorContainer::iterator icIt = iterators->begin(); icIt != iterators->end(); ++icIt) {
      if (((*icIt)->it == _it) && (*icIt != this)) {
        (*icIt)->it = nextElement;
        (*icIt)->lastOp = op_Remove;
      }
    }

    remove_edge(*_it,*graph->getBGraph());
    return nextElement;
  }

  void Edge::EdgeIterator::invalidate() {
    lastOp = op_Invalidated;
  }

  // edge iterator end

  // edge type

  Edge::EdgeType::EdgeType(const string &type, Edge::eDirectionType dtype) :
    _type(type),
    _dtype(dtype)
  {
  }

  Edge::eDirectionType Edge::EdgeType::getDirectionType() const {
    return _dtype;
  }


  const string& Edge::EdgeType::getType() const {
    return _type;
  }

  bool Edge::EdgeType::operator <(const EdgeType& edgeType) const {
    if(getDirectionType() < edgeType.getDirectionType()) {
      return true;
    } else {
      if(getDirectionType() == edgeType.getDirectionType()) {
        return getType() < edgeType.getType();
      } else {
        return false;
      }
    }
  }


  bool Edge::EdgeType::operator ==(const EdgeType &edgeType) const {
    return ((getDirectionType() == edgeType.getDirectionType() && getType() == edgeType.getType()));
  }

  bool Edge::EdgeType::operator !=(const EdgeType &edgeType) const {
    return !(*this == edgeType);
  }

  // edge type end


}}

