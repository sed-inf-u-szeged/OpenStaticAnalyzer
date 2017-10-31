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
#include <common/inc/StringSup.h>
#include <iostream>
#include <algorithm>
#include "../privinc/messages.h"

using namespace std;

namespace columbus {  namespace graph {

  Attribute::~Attribute(){
  }

  Attribute::Attribute(const string& name, const string& context, Graph *g) :
    graph(g),
    name( graph->getStrTable()->set(name)),
    context( graph->getStrTable()->set(context))
  {
  }

  Attribute::Attribute(Key nameKey, Key contextKey, Graph *g) :
    graph(g),
    name(nameKey),
    context(contextKey)
  {
  }

  Attribute::Attribute() :
    graph(NULL),
    name(0),
    context()
  {
  }

  Attribute::Attribute( const Attribute& copy ):
    graph(copy.graph),
    name( copy.name),
    context( copy.context)
  {

  }

  const string& Attribute::getName() const {
    if(graph == NULL)
      throw InvalidGetter( COLUMBUS_LOCATION, CMSG_EX_INVALID_ATTRIBUTE_NO_NAME);
    return graph->getStrTable()->get(name);
  }

  Attribute::aType Attribute::getType() const{
    // default attribute type
    return atInvalid;
  }

  const string& Attribute::getContext() const {
    if(graph == NULL)
      throw InvalidGetter( COLUMBUS_LOCATION, CMSG_EX_INVALID_ATTRIBUTE_NO_CONTEXT);
    return graph->getStrTable()->get(context);
  }

  Attribute* Attribute::copy() const{
    return new Attribute(*this);
  }


  

  void Attribute::copyStrings(StrTable *from,StrTable *to) {
    name = to->set(from->get(name));
    context = to->set(from->get(context));
  }

  void Attribute::setGraph(Graph* graph) {
    this->graph = graph;
  }

  bool Attribute::equals(const Attribute &attribute) const{
    if( (graph == NULL) && (attribute.graph == NULL) ) return true;
    if( (graph == NULL) || (attribute.graph == NULL) ) return false;
    
    if (graph == attribute.graph) {
      return ( ( getType() == attribute.getType() ) && (name == attribute.name) && (context == attribute.context) );
    } else {
      return ( ( getType() == attribute.getType() ) && (getName() == attribute.getName()) && (getContext() == attribute.getContext()) );
    }
    
  }

  int Attribute::hashCode() const {
    size_t hash = (size_t)name;
    hash ^= size_t(context);
    hash ^= (size_t)getType();
    //hash ^= (size_t)graph;
    HASHLONGTOINT(hash)
    return (int)hash;
  }

  string Attribute::getStringValue() const {
    return "";
  }
  
  bool Attribute::operator==(const Attribute& attribute) const{
    return equals(attribute);
  }

  bool Attribute::operator!=(const Attribute& attribute) const{
    return !equals(attribute);
  }

  bool Attribute::operator<(const Attribute& attribute) const{
    if (attribute.graph == graph) {
      if(name < attribute.name) {
        return true;
      } else {
        if( name == attribute.name) {
          return getType() < attribute.getType();
        } else {
          return false;
        }
      }
    } else {
      string nameStr = getName();
      string attrNameStr = attribute.getName();
      if(nameStr < attrNameStr) {
        return true;
      } else {
        if(nameStr == attrNameStr) {
          return getType() < attribute.getType();
        } else {
          return false;
        }
      }
    }
  }


  Attribute& Attribute::add(const Attribute &attribute){
    return *this;
  }

  Attribute& Attribute::operator=( const columbus::graph::Attribute& copy) {
    graph  =copy.graph;
    name   = copy.name;
    context= copy.context;

    return *this;
  }

  AttributeInt::AttributeInt(const string &name, const string& context, int value,Graph *g) :
    Attribute(name, context, g),
    value(value)
  {
  }

  AttributeInt::AttributeInt(Key nameKey, Key contextKey, int value, Graph *g) : 
    Attribute(nameKey, contextKey, g),
    value(value)
  {
  }

  AttributeInt::AttributeInt() : 
    Attribute() ,
    value(0)
  {
  }

  int AttributeInt::getValue() const {
    if(graph == NULL)
      throw InvalidGetter( COLUMBUS_LOCATION, CMSG_EX_INVALID_ATTRIBUTE_NO_VALUE);
    return value;
  }

  string AttributeInt::getStringValue() const {
    if(graph == NULL)
      throw InvalidGetter( COLUMBUS_LOCATION, CMSG_EX_INVALID_ATTRIBUTE_NO_VALUE);
    return common::toString(value);
  }

  void AttributeInt::setValue(int value) {
    if(graph == NULL)
      throw InvalidSetter( COLUMBUS_LOCATION, CMSG_EX_INVALID_ATTRIBUTE_NO_VALUE);
    this->value = value;
  }
  
  void AttributeInt::incValue(int value) {
    if(graph == NULL)
      throw InvalidSetter( COLUMBUS_LOCATION, CMSG_EX_INVALID_ATTRIBUTE_NO_VALUE);
    this->value += value;
  }

  Attribute::aType AttributeInt::getType() const {
    return atInt;
  }

  bool AttributeInt::equals(const Attribute& attribute) const {
    if(attribute.getType() != Attribute::atInt)
      return false;
    const AttributeInt& attributeInt = static_cast<const AttributeInt&>(attribute);
    return (  Attribute::equals(attribute) && (getValue() == attributeInt.getValue()) );
  }

  int AttributeInt::hashCode() const {
    size_t hash = Attribute::hashCode();
    hash ^= (size_t)value;
    HASHLONGTOINT(hash)
    return (int)hash;
  }

  Attribute* AttributeInt::copy() const {
    return new AttributeInt(*this);
  }



  AttributeFloat::AttributeFloat(const string &name, const string& context, float _value,Graph *g) :
    Attribute(name, context, g),
    value(_value) 
  {
  }

  AttributeFloat::AttributeFloat(Key nameKey, Key contextKey, float _value, Graph *g) :
    Attribute(nameKey, contextKey, g),
    value(_value) 
  {
  }

  AttributeFloat::AttributeFloat() :
    Attribute(),
    value(0.0)
  {
  }

  float AttributeFloat::getValue() const {
    if(graph == NULL)
      throw InvalidGetter( COLUMBUS_LOCATION, CMSG_EX_INVALID_ATTRIBUTE_NO_VALUE);
    return value;
  }

  string AttributeFloat::getStringValue() const {
    if(graph == NULL)
      throw InvalidGetter( COLUMBUS_LOCATION, CMSG_EX_INVALID_ATTRIBUTE_NO_VALUE);
    return common::toString(value);
  }

  void AttributeFloat::setValue(float value) {
    if(graph == NULL)
      throw InvalidSetter( COLUMBUS_LOCATION, CMSG_EX_INVALID_ATTRIBUTE_NO_VALUE);
    this->value = value;
  }

  void AttributeFloat::incValue(float value) {
    if(graph == NULL)
      throw InvalidSetter( COLUMBUS_LOCATION, CMSG_EX_INVALID_ATTRIBUTE_NO_VALUE);
    this->value += value;
  }

  Attribute* AttributeFloat::copy() const{
    return new AttributeFloat(*this);
  }


  Attribute::aType AttributeFloat::getType() const {
    return atFloat;
  }

  bool AttributeFloat::equals(const Attribute& attribute) const {
    if(attribute.getType() != Attribute::atFloat)
      return false;
    const AttributeFloat& attributeFloat = static_cast<const AttributeFloat&>(attribute);

    return (  Attribute::equals(attribute) && (getValue() == attributeFloat.getValue()) );
  }

  int AttributeFloat::hashCode() const {
    size_t hash = Attribute::hashCode();
    hash ^= (size_t)value;
    HASHLONGTOINT(hash)
    return (int)hash;
  }




  AttributeString::AttributeString(const string &name, const string& context, const string &value,Graph *g) :
    Attribute(name, context, g),
    value(graph->getStrTable()->set(value)) 
  { 
  }

  AttributeString::AttributeString(Key nameKey, Key contextKey, Key valueKey, Graph *g) :
    Attribute(nameKey, contextKey, g),
    value(valueKey) 
  { 
  }

  AttributeString::AttributeString() :
    Attribute(),
    value()
  {
  }

  void AttributeString::copyStrings(StrTable *from,StrTable *to) {
    Attribute::copyStrings(from,to);
    value = to->set(from->get(value));
  }

  const string& AttributeString::getValue() const {
    if(graph == NULL)
      throw InvalidGetter( COLUMBUS_LOCATION, CMSG_EX_INVALID_ATTRIBUTE_NO_VALUE);
    return graph->getStrTable()->get(value);
  }

  string AttributeString::getStringValue() const {
    if(graph == NULL)
      throw InvalidGetter( COLUMBUS_LOCATION, CMSG_EX_INVALID_ATTRIBUTE_NO_VALUE);
    return graph->getStrTable()->get(value);
  }

  bool AttributeString::equals(const Attribute& attribute) const {
    if(attribute.getType() != Attribute::atString)
      return false;
    const AttributeString& attributeString = static_cast<const AttributeString&>(attribute);

    return (  Attribute::equals(attribute) && (getValue() == attributeString.getValue()) );
  }

  int AttributeString::hashCode() const {
    size_t hash = Attribute::hashCode();
    hash ^= (size_t)value;
    HASHLONGTOINT(hash)
    return (int)hash;
  }

  void AttributeString::setValue(const string& value) {
    if(graph == NULL)
      throw InvalidSetter( COLUMBUS_LOCATION, CMSG_EX_INVALID_ATTRIBUTE_NO_VALUE);
    this->value = graph->getStrTable()->set(value);
  }

  Attribute::aType AttributeString::getType() const {
    return atString;
  }

  Attribute* AttributeString::copy() const {
    return new AttributeString(*this);
  }


// filer flags

  bool Attribute::AttributeIterator::FilterFlags::operator==(const FilterFlags& fflag) const{
    return (type == fflag.type) && (name == fflag.name) && (context == fflag.context);
  }

  Attribute::AttributeIterator::FilterFlags::FilterFlags(bool typeV, bool nameV, bool contextV) : type(typeV), name(nameV), context(contextV) {}


//----- begin Attribute iterator

  bool Attribute::AttributeIterator::isOutFilteredItem(Attribute* attribute) {
    if(fFlags.context) {
      if (graph && graph->strTable && graph->strTable == attribute->graph->strTable) {
        if (!contextKey)
          contextKey = graph->strTable->get(context);
        if (contextKey != attribute->context)
          return true;
      } else if (attribute->graph->strTable->get(context) != attribute->context)
        return true;
    }
    if(fFlags.name) {
      if (graph && graph->strTable && graph->strTable == attribute->graph->strTable) {
        if (!nameKey)
          nameKey = graph->strTable->get(name);
        if (nameKey != attribute->name)
          return true;
      } else if (attribute->graph->strTable->get(name) != attribute->name)
        return true;
    }
    if(fFlags.type) {
      if (type != attribute->getType())
        return true;
    }
    return false;
  }

  Attribute::AttributeIterator::AttributeIterator(Container *container, IteratorContainer *itContainer, Graph *graph, GraphVertex graphVertex, FilterFlags filter, Attribute::aType type , const string& name, const string& context) :
    graph(graph),
    container(container),
    it(),
    iterators(itContainer),
    lastOp(op_None),
    type(type),
    name(name),
    context(context),
    nameKey(0),
    contextKey(0),
    fFlags(filter),
    graphVertex(graphVertex),
    graphEdge(),
    attributeComposite(NULL),
    iteratorType(iteratorOnVertex)
  {
    iterators->push_back(this);
  }

  Attribute::AttributeIterator::AttributeIterator(Container *container, IteratorContainer *itContainer, Graph *graph, GraphEdge graphEdge, FilterFlags filter, Attribute::aType type , const string& name, const string& context) :
    graph(graph),
    container(container),
    it(),
    iterators(itContainer),
    lastOp(op_None),
    type(type),
    name(name),
    context(context),
    nameKey(0),
    contextKey(0),
    fFlags(filter),
    graphVertex(),
    graphEdge(graphEdge),
    attributeComposite(NULL),
    iteratorType(iteratorOnEdge)
  {
    iterators->push_back(this);
  }

  Attribute::AttributeIterator::AttributeIterator(Container *container, IteratorContainer *itContainer, Graph *graph, AttributeComposite* attrComposite, FilterFlags filter, Attribute::aType type , const string& name, const string& context) :
    graph(graph),
    container(container),
    it(),
    iterators(itContainer),
    lastOp(op_None),
    type(type),
    name(name),
    context(context),
    nameKey(0),
    contextKey(0),
    fFlags(filter),
    graphVertex(),
    graphEdge(),
    attributeComposite(attrComposite),
    iteratorType(iteratorOnComposite)
  {
    iterators->push_back(this);
  }


  Attribute::AttributeIterator::AttributeIterator(Container *container, IteratorContainer *itContainer, Graph *graph, GraphVertex graphVertex) :
    graph(graph),
    container(container),
    it(),
    iterators(itContainer),
    lastOp(op_None),
    type(Attribute::atInt),
    name(""),
    context(""),
    nameKey(0),
    contextKey(0),
    fFlags(FilterFlags(false, false, false)),
    graphVertex(graphVertex),
    graphEdge(),
    attributeComposite(NULL),
    iteratorType(iteratorOnVertex)
  {
    iterators->push_back(this);
  }

  Attribute::AttributeIterator::AttributeIterator(Container *container, IteratorContainer *itContainer, Graph *graph, GraphEdge graphEdge) :
    graph(graph),
    container(container),
    it(),
    iterators(itContainer),
    lastOp(op_None),
    type(Attribute::atInt),
    name(""),
    context(""),
    nameKey(0),
    contextKey(0),
    fFlags(FilterFlags(false, false, false)),
    graphVertex(),
    graphEdge(graphEdge),
    attributeComposite(NULL),
    iteratorType(iteratorOnEdge)
  {
    iterators->push_back(this);
  }

  Attribute::AttributeIterator::AttributeIterator(Container *container, IteratorContainer *itContainer, Graph *graph, AttributeComposite* attrComposite) :
    graph(graph),
    container(container),
    it(),
    iterators(itContainer),
    lastOp(op_None),
    type(Attribute::atInt),
    name(""),
    context(""),
    nameKey(0),
    contextKey(0),
    fFlags(FilterFlags(false, false, false)),
    graphVertex(),
    graphEdge(),
    attributeComposite(attrComposite),
    iteratorType(iteratorOnComposite)
  {
    iterators->push_back(this);
  }

  void Attribute::AttributeIterator::add(const Attribute& attribute) {

    for(AttributeList::iterator itc = container->begin(); itc != container->end(); itc++){
      if(attribute.equals(**itc)) throw AlreadyExist( COLUMBUS_LOCATION, CMSG_EX_ATTRIBUTE_ALREADY_EXIST);
    }

    switch (lastOp) {
      case op_None:
       it = container->begin();
        break;
      case op_Next:
      case op_Add:
        ++it;
        break;
      case op_Invalidated:
        throw GraphInvalidIteratorException( COLUMBUS_LOCATION, CMSG_EX_INVALID_ITERATOR);
      case op_Previous:
      case op_Remove:
        break;
    }

    it = container->insert(it, attribute.copy() );

    lastOp = op_Add;
  }

  void Attribute::AttributeIterator::remove() {
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

  Attribute::AttributeIterator::AttributeIterator() :
    graph(NULL),
    container(NULL),
    it(),
    iterators(NULL),
    lastOp(op_Invalidated),
    type(atInt),
    name(),
    context(),
    nameKey(0),
    contextKey(0),
    fFlags(false, false, false),
    graphVertex(),
    graphEdge(),
    attributeComposite(NULL),
    iteratorType(iteratorOnEdge)
  {
  }


  Attribute::AttributeIterator::AttributeIterator(const Attribute::AttributeIterator &iterator) :
    graph(iterator.graph),
    container(iterator.container),
    it(iterator.it),
    iterators(iterator.iterators),
    lastOp(iterator.lastOp),
    type(iterator.type),
    name(iterator.name),
    context(iterator.context),
    nameKey(iterator.nameKey),
    contextKey(iterator.contextKey),
    fFlags(iterator.fFlags),
    graphVertex(iterator.graphVertex),
    graphEdge(iterator.graphEdge),
    attributeComposite(iterator.attributeComposite),
    iteratorType(iterator.iteratorType)
  {
    if (lastOp != op_Invalidated && iterators)
      iterators->push_back(this);
  }

  Attribute::AttributeIterator::~AttributeIterator() {
    removeIterator();
  }

  Attribute::AttributeIterator& Attribute::AttributeIterator::operator=(const AttributeIterator &otherIt) {
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

    graph = otherIt.graph;
    iteratorType = otherIt.iteratorType;
    graphVertex = otherIt.graphVertex;
    graphEdge = otherIt.graphEdge;
    attributeComposite = otherIt.attributeComposite;

    container = otherIt.container;
    if (otherIt.lastOp != op_None )
      it = otherIt.it;

    iterators = otherIt.iterators;
    lastOp = otherIt.lastOp;
    fFlags = otherIt.fFlags;
    type = otherIt.type;
    name = otherIt.name;
    context = otherIt.context;
    nameKey = otherIt.nameKey;
    contextKey = otherIt.contextKey;

    if (lastOp != op_Invalidated && iterators && insertIntoIterators)
      iterators->push_back(this);

    return *this;
  }

  bool Attribute::AttributeIterator::hasNext() {
    return nextItem() != container->end();
  }

  Attribute& Attribute::AttributeIterator::next() {
    it = nextItem();
    lastOp = op_Next;

    if (it == container->end())
        throw GraphNoSuchElementException( COLUMBUS_LOCATION, CMSG_EX_ITERATOR_NOT_PREVIUS_ELEMENT);

    return **it;
  }

  bool Attribute::AttributeIterator::hasPrevious() {
    return previousItem() != container->end();
  }

  Attribute& Attribute::AttributeIterator::previous() {
    it = previousItem();
    lastOp = op_Previous;

    if (it == container->end())
        throw GraphNoSuchElementException( COLUMBUS_LOCATION, CMSG_EX_ITERATOR_NOT_PREVIUS_ELEMENT);

    return **it;
  }

  bool Attribute::AttributeIterator::equals(const AttributeIterator& otherIt) const {
    if (lastOp == op_Invalidated)
      throw GraphInvalidIteratorException( COLUMBUS_LOCATION, CMSG_EX_INVALID_ITERATOR);
    bool itEqual = false;
    if ((lastOp != op_None || otherIt.lastOp != op_None ))
      itEqual = it == otherIt.it;
    else
      itEqual = true;
    return itEqual && (lastOp == otherIt.lastOp) && (fFlags == otherIt.fFlags) && (container == otherIt.container)
      && (graph == otherIt.graph) 
      && ((iteratorType == iteratorOnVertex)?(graphVertex == otherIt.graphVertex):1)
      && ((iteratorType == iteratorOnEdge)?(graphEdge == otherIt.graphEdge):1)
      && (type == otherIt.type) && (name == otherIt.name) && (context == otherIt.context) && (nameKey == otherIt.nameKey) && (contextKey == otherIt.contextKey);
  }

  int Attribute::AttributeIterator::hashCode() const {
    size_t hashLong = (size_t)(graph) ^ (size_t)(container) ^ (((size_t)iteratorType)<<8) ^ (size_t)lastOp;
    HASHLONGTOINT(hashLong);
    return static_cast<int>(hashLong);
  }

  Attribute::AttributeIterator::Container::iterator Attribute::AttributeIterator::findNextNotFiltered(bool inc, const Attribute::AttributeIterator::Container::iterator& _it) {
    Container::iterator j = _it;

    if(j != container->end() && !inc && isOutFilteredItem(*j) ) 
      inc = true;
    

    if (j == container->end() && inc)
      return container->end();

    if (inc) {
      j++;
      while( j != container->end() ) {
        if(!isOutFilteredItem(*j))
          return j;
        ++j;
      }
    }

/*    while (j != container->end())
      j = safeRemove(j);*/

    return j;
  }



  Attribute::AttributeIterator::Container::iterator Attribute::AttributeIterator::nextItem() {
    switch (lastOp) {
      case op_None:       return findNextNotFiltered(false, container->begin());
      case op_Add:        return findNextNotFiltered(true, it);
      case op_Remove:     return findNextNotFiltered(false, it);
      case op_Next:       return findNextNotFiltered(true, it);
      case op_Previous:   return it;
      case op_Invalidated:
        throw GraphInvalidIteratorException( COLUMBUS_LOCATION, CMSG_EX_INVALID_ITERATOR);
    }
    return container->end();
  }

  Attribute::AttributeIterator::Container::iterator Attribute::AttributeIterator::findPrevious(bool dec, const Attribute::AttributeIterator::Container::iterator& _it) {
    Container::iterator j = _it;

    if (j == container->begin() && dec)
      return container->end();

    if (dec)
      --j;

/*    while (!fact->getExist(*j)) {
      j = safeRemove(j);
      if (j == container->begin())
        return j;
      --j;
    }*/

    return j;
  }

  Attribute::AttributeIterator::Container::iterator Attribute::AttributeIterator::previousItem() {
    switch (lastOp) {
      case op_None:       return container->end();
      case op_Add:        return it;
      case op_Remove:     return findPrevious(true, it);
      case op_Next:       return it;
      case op_Previous:   return findPrevious(true, it);
      case op_Invalidated:
        throw GraphInvalidIteratorException( COLUMBUS_LOCATION, CMSG_EX_INVALID_ITERATOR);
    }
    return container->end();
  }

  Attribute::AttributeIterator::Container::iterator Attribute::AttributeIterator::safeRemove(const Attribute::AttributeIterator::Container::iterator &_it) {
    Container::iterator nextElement = _it;
    ++nextElement;

    for (IteratorContainer::iterator icIt = iterators->begin(); icIt != iterators->end(); ++icIt) {
      if (((*icIt)->it == _it) && (*icIt != this)) {
        (*icIt)->it = nextElement;
        (*icIt)->lastOp = op_Remove;
      }
    }

    return container->erase(_it);
  }

  void Attribute::AttributeIterator::invalidate() {
    lastOp = op_Invalidated;
  }

  inline void Attribute::AttributeIterator::removeIterator() {
    if (lastOp != op_Invalidated && iterators) {
      for (IteratorContainer::iterator _it = iterators->begin(); _it != iterators->end(); ++_it) {
        if (*_it == this) {
          iterators->erase(_it);
          if (iterators->empty()) {
            switch (iteratorType) {
              case iteratorOnEdge:
                graph->removeAttributeIteratorOnEdgeContainer(graphEdge);
                break;
              case iteratorOnVertex:
                graph->removeAttributeIteratorOnVertexContainer(graphVertex);
                break;
              case iteratorOnComposite:
                delete attributeComposite->iterators;
                attributeComposite->iterators = NULL;
                break;
            }
          }
          return;
        }
      }
    }
  }

//----- end Attribute iterator

  AttributeComposite::AttributeComposite(const string& name, const string& context, Graph* g) :
    Attribute(name, context, g),
    values(NULL),
    iterators(NULL)
  {
    values = new AttributeList();
  }

  AttributeComposite::AttributeComposite(Key nameKey, Key contextKey, Graph* g) :
    Attribute(nameKey, contextKey, g),
    values(NULL),
    iterators(NULL)
  {
    values = new AttributeList();
  }

  AttributeComposite::AttributeComposite() :
    Attribute(),
    values(NULL),
    iterators(NULL)
  {
  }

  AttributeComposite::AttributeComposite(const AttributeComposite& attribute) :
    Attribute(attribute.name, attribute.context, attribute.graph) ,
    values(NULL),
    iterators(NULL)
  {
    if (this == &attribute)
      return;
      
    if (attribute.values == NULL) {
      values = NULL;
    } else {
      values = new AttributeList();
      for(AttributeList::iterator it = attribute.values->begin(); it != attribute.values->end(); it++) {
        values->push_back( (*it)->copy() );
      }
    }
  }

  string AttributeComposite::getStringValue() const {
    if(graph == NULL)
      throw InvalidGetter( COLUMBUS_LOCATION, CMSG_EX_INVALID_ATTRIBUTE_NO_VALUE);
    return "Not implemented yet!";
  }

  AttributeComposite& AttributeComposite::operator=( const columbus::graph::AttributeComposite& copy)
  {
    if (this == &copy)
      return *this;
      
    Attribute::operator=(copy);
    iterators = copy.iterators;
    if (copy.values == NULL) {
      values = NULL;
    } else {
      values = new AttributeList();
      for(AttributeList::iterator it = copy.values->begin(); it != copy.values->end(); it++) {
        values->push_back( (*it)->copy() );
      }
    }

    return *this;
  }

  AttributeComposite::~AttributeComposite() {
    if (values != NULL) {
      for(AttributeList::iterator it = values->begin(); it != values->end(); it++) {
        delete *it;
      }
      delete values;
    }
    if(iterators != NULL) {
      for(list<AttributeIterator*>::iterator it = iterators->begin(); it != iterators->end(); ++it) {
        (*it)->invalidate();
      }
      delete iterators;
    }
  }

  bool AttributeComposite::deleteAttribute(const Attribute& attribute){
    if(graph == NULL)
      throw InvalidSetter( COLUMBUS_LOCATION, CMSG_EX_NO_DEL_ATTRIBUTE_TO_INVALID_NODE);
    for(AttributeList::iterator it = values->begin(); it != values->end(); it++){
      if(attribute == **it) {
        delete *it;
        values->erase(it);
        return true;
      }
    }
    return false;
/*    return deleteAttribute(attribute.getType(),attribute.getName());*/
  }

  bool AttributeComposite::deleteAttribute(Attribute::aType type, const string& name){
    if(graph == NULL)
      throw InvalidSetter( COLUMBUS_LOCATION, CMSG_EX_NO_DEL_ATTRIBUTE_TO_INVALID_NODE);
    bool deleted = false;;
    for(AttributeList::iterator it = values->begin(); it != values->end();){
      if( ((**it).getName() == name) && ((**it).getType() == type) ) {
        delete *it;
        values->erase(it++);
        deleted = true;
      } else {
        ++it;
      }

    }
    return deleted;
  }

  bool AttributeComposite::deleteAttribute(Attribute::aType type){
    if(graph == NULL)
      throw InvalidSetter( COLUMBUS_LOCATION, CMSG_EX_NO_DEL_ATTRIBUTE_TO_INVALID_NODE);
    bool deleted = false;
    for(AttributeList::iterator it = values->begin(); it != values->end();){
      if( ((**it).getType() == type) ) {
        delete *it;
        values->erase(it++);
        deleted = true;
      } else {
        ++it;
      }
    }
    return deleted;
  }

  Attribute::aType AttributeComposite::getType() const {
    return atComposite;
  }

  bool AttributeComposite::equals(const Attribute& attribute) const {
    if(attribute.getType() != Attribute::atComposite)
      return false;
    const AttributeComposite& attributeComposite = static_cast<const AttributeComposite&>(attribute);
    bool eq = Attribute::equals(attribute);

    AttributeList::iterator it = values->begin();
    AttributeList::iterator it2 = attributeComposite.values->begin() ;
    for( ; eq && ( (it != values->end()) && (it2 != attributeComposite.values->end()) ); it++, it2++) {
      eq = eq && (*it)->equals(**it2);
    }
    if( eq && ( (it != values->end()) || (it2 != attributeComposite.values->end())) )
      eq = false;
    return ( eq );
  }

  int AttributeComposite::hashCode() const {
    size_t hash = Attribute::hashCode();
    for(AttributeList::iterator it = values->begin() ; it != values->end() ; it++) {
      hash ^= (size_t)((*it)->hashCode());
    }
    HASHLONGTOINT(hash)
    return (int)hash;
  }


  Attribute& AttributeComposite::addAttribute(const Attribute& value) {
    if(graph == NULL)
      throw InvalidSetter( COLUMBUS_LOCATION, CMSG_EX_NO_ADD_ATTRIBUTE_TO_INVALID_ATTRIBUTE);
    if(value.graph == NULL) {
      throw InvalidSetter( COLUMBUS_LOCATION, CMSG_EX_NO_ADD_INVALID_ATTRIBUTE_TO_ATTRIBUTE);
    }
    
/*    for(AttributeList::iterator it = values->begin(); it != values->end(); it++) {
      if(value.equals(**it)) throw AlreadyExist("Attribute::add(const Attribute& value)","Attribute is already exist");
    }*/
    Attribute *attr = value.copy();

    if(value.graph != graph) {
      attr->setGraph(graph);
      attr->copyStrings(value.graph->getStrTable(),graph->getStrTable());
    }

    values->push_back(attr);
    
    return *attr;

  }

  Attribute::AttributeIterator AttributeComposite::findAttribute(const aType type, const string& name, const string& context) {

    Attribute::AttributeIterator::FilterFlags filter(true, true, true);
    if(iterators == NULL)
      iterators = new AttributeIterator::IteratorContainer();
    return Attribute::AttributeIterator(values, iterators, graph, this, filter, type, name, context);

  }

  Attribute::AttributeIterator AttributeComposite::findAttributeByType(Attribute::aType type)  {

    Attribute::AttributeIterator::FilterFlags filter(true, false, false);
    if(iterators == NULL)
      iterators = new AttributeIterator::IteratorContainer();
    return Attribute::AttributeIterator(values, iterators, graph, this, filter, type, "", "");

  }

  Attribute::AttributeIterator AttributeComposite::findAttributeByName(const string& name) {

    Attribute::AttributeIterator::FilterFlags filter(false, true, false);
    if(iterators == NULL)
      iterators = new AttributeIterator::IteratorContainer();
    return Attribute::AttributeIterator(values, iterators, graph, this, filter, Attribute::atInt, name, "");

  }

  Attribute::AttributeIterator AttributeComposite::findAttributeByContext(const string& context) {

    Attribute::AttributeIterator::FilterFlags filter(false, false, true);
    if(iterators == NULL)
      iterators = new AttributeIterator::IteratorContainer();
    return Attribute::AttributeIterator(values, iterators, graph, this, filter, Attribute::atInt, "", context);

  }


  void AttributeComposite::copyStrings(StrTable *from,StrTable *to) {
    Attribute::copyStrings(from, to);
    for(AttributeList::iterator it = values->begin(); it != values->end(); it++) {
      (*it)->copyStrings(from, to);
    }
  }

  void AttributeComposite::setGraph(Graph* graph) {
    this->graph = graph;
    for(AttributeList::iterator it = values->begin(); it != values->end(); it++) {
      (*it)->setGraph(graph);
    }
  }

  Attribute* AttributeComposite::copy() const{
    return new AttributeComposite(*this);
  }



  Attribute::AttributeIterator AttributeComposite::getAttributes() {
    if(iterators == NULL) {
      iterators = new AttributeIterator::IteratorContainer();
    }
    return Attribute::AttributeIterator(values, iterators, graph, this);
  }

 

}}
