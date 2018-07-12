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

#include "python/inc/python.h"
#include "python/inc/Common.h"
#include "common/inc/WriteMessage.h"

#include "python/inc/messages.h"
#include <algorithm>
#include <string.h>
#include "common/inc/math/common.h"


namespace columbus { namespace python { namespace asg {

typedef boost::crc_32_type  Crc_type;

namespace expression { 
  ArgumentList::ArgumentList(NodeId _id, Factory *_factory) :
    Positioned(_id, _factory),
    m_hasPositionalArguments(0),
    m_hasDictionary(0),
    hasKeywordContainer(),
    m_hasTuple(0)
  {
  }

  ArgumentList::~ArgumentList() {
  }

  void ArgumentList::prepareDelete(bool tryOnVirtualParent){
    removePositionalArguments();
    removeDictionary();
    while (!hasKeywordContainer.empty()) {
      const NodeId id = *hasKeywordContainer.begin();
      removeParentEdge(id);
      if (factory->getExistsReverseEdges())
        factory->reverseEdges->removeEdge(id, this->getId(), edkArgumentList_HasKeyword);
      hasKeywordContainer.pop_front();
    }
    removeTuple();
    base::Positioned::prepareDelete(false);
  }

  NodeKind ArgumentList::getNodeKind() const {
    return ndkArgumentList;
  }

  expression::ExpressionList* ArgumentList::getPositionalArguments() const {
    expression::ExpressionList *_node = NULL;
    if (m_hasPositionalArguments != 0)
      _node = dynamic_cast<expression::ExpressionList*>(factory->getPointer(m_hasPositionalArguments));
    if ( (_node == NULL) || factory->getIsFiltered(_node))
      return NULL;

    return _node;
  }

  expression::Expression* ArgumentList::getDictionary() const {
    expression::Expression *_node = NULL;
    if (m_hasDictionary != 0)
      _node = dynamic_cast<expression::Expression*>(factory->getPointer(m_hasDictionary));
    if ( (_node == NULL) || factory->getIsFiltered(_node))
      return NULL;

    return _node;
  }

  ListIterator<expression::Keyword> ArgumentList::getKeywordListIteratorBegin() const {
    return ListIterator<expression::Keyword>(&hasKeywordContainer, factory, true);
  }

  ListIterator<expression::Keyword> ArgumentList::getKeywordListIteratorEnd() const {
    return ListIterator<expression::Keyword>(&hasKeywordContainer, factory, false);
  }

  bool ArgumentList::getKeywordIsEmpty() const {
    return getKeywordListIteratorBegin() == getKeywordListIteratorEnd();
  }

  unsigned int ArgumentList::getKeywordSize() const {
    unsigned int size = 0;
    ListIterator<expression::Keyword> endIt = getKeywordListIteratorEnd();
    for (ListIterator<expression::Keyword> it = getKeywordListIteratorBegin(); it != endIt; ++it) {
      ++size;
    }
    return size;
  }

  expression::Expression* ArgumentList::getTuple() const {
    expression::Expression *_node = NULL;
    if (m_hasTuple != 0)
      _node = dynamic_cast<expression::Expression*>(factory->getPointer(m_hasTuple));
    if ( (_node == NULL) || factory->getIsFiltered(_node))
      return NULL;

    return _node;
  }

  bool ArgumentList::setEdge(EdgeKind edgeKind, NodeId edgeEnd, bool tryOnVirtualParent) {
    switch (edgeKind) {
      case edkArgumentList_HasPositionalArguments:
        setPositionalArguments(edgeEnd);
        return true;
      case edkArgumentList_HasDictionary:
        setDictionary(edgeEnd);
        return true;
      case edkArgumentList_HasKeyword:
        addKeyword(edgeEnd);
        return true;
      case edkArgumentList_HasTuple:
        setTuple(edgeEnd);
        return true;
      default:
        break;
    }
    if (base::Positioned::setEdge(edgeKind, edgeEnd, false)) {
      return true;
    }
    return false;
  }

  bool ArgumentList::removeEdge(EdgeKind edgeKind, NodeId edgeEnd, bool tryOnVirtualParent) {
    switch (edgeKind) {
      case edkArgumentList_HasPositionalArguments:
        removePositionalArguments();
        return true;
      case edkArgumentList_HasDictionary:
        removeDictionary();
        return true;
      case edkArgumentList_HasKeyword:
        removeKeyword(edgeEnd);
        return true;
      case edkArgumentList_HasTuple:
        removeTuple();
        return true;
      default:
        break;
    }
    if (base::Positioned::removeEdge(edgeKind, edgeEnd, false)) {
      return true;
    }
    return false;
  }

  void ArgumentList::setPositionalArguments(NodeId _id) {
    expression::ExpressionList *_node = NULL;
    if (_id) {
      if (!factory->getExist(_id))
        throw PythonException(COLUMBUS_LOCATION, CMSG_EX_THE_END_POINT_OF_THE_EDGE_DOES_NOT_EXIST);

      _node = dynamic_cast<expression::ExpressionList*> (factory->getPointer(_id));
      if ( _node == NULL) {
        throw PythonException(COLUMBUS_LOCATION, CMSG_EX_INVALID_NODE_KIND);
      }
      if (&(_node->getFactory()) != this->factory)
        throw PythonException(COLUMBUS_LOCATION, CMSG_EX_THE_FACTORY_OF_NODES_DOES_NOT_MATCH );

      if (m_hasPositionalArguments) {
        removeParentEdge(m_hasPositionalArguments);
        if (factory->getExistsReverseEdges())
          factory->reverseEdges->removeEdge(m_hasPositionalArguments, m_id, edkArgumentList_HasPositionalArguments);
      }
      m_hasPositionalArguments = _node->getId();
      if (m_hasPositionalArguments != 0)
        setParentEdge(factory->getPointer(m_hasPositionalArguments), edkArgumentList_HasPositionalArguments);
      if (factory->getExistsReverseEdges())
        factory->reverseEdges->insertEdge(m_hasPositionalArguments, this->getId(), edkArgumentList_HasPositionalArguments);
    } else {
      if (m_hasPositionalArguments) {
        throw PythonException(COLUMBUS_LOCATION, CMSG_EX_CAN_T_SET_EDGE_TO_NULL);
      }
    }
  }

  void ArgumentList::setPositionalArguments(expression::ExpressionList *_node) {
    if (_node == NULL)
      throw PythonException(COLUMBUS_LOCATION, CMSG_EX_CAN_T_SET_EDGE_TO_NULL);

    setPositionalArguments(_node->getId());
  }

  void ArgumentList::removePositionalArguments() {
      if (m_hasPositionalArguments) {
        removeParentEdge(m_hasPositionalArguments);
        if (factory->getExistsReverseEdges())
          factory->reverseEdges->removeEdge(m_hasPositionalArguments, m_id, edkArgumentList_HasPositionalArguments);
      }
      m_hasPositionalArguments = 0;
  }

  void ArgumentList::setDictionary(NodeId _id) {
    expression::Expression *_node = NULL;
    if (_id) {
      if (!factory->getExist(_id))
        throw PythonException(COLUMBUS_LOCATION, CMSG_EX_THE_END_POINT_OF_THE_EDGE_DOES_NOT_EXIST);

      _node = dynamic_cast<expression::Expression*> (factory->getPointer(_id));
      if ( _node == NULL) {
        throw PythonException(COLUMBUS_LOCATION, CMSG_EX_INVALID_NODE_KIND);
      }
      if (&(_node->getFactory()) != this->factory)
        throw PythonException(COLUMBUS_LOCATION, CMSG_EX_THE_FACTORY_OF_NODES_DOES_NOT_MATCH );

      if (m_hasDictionary) {
        removeParentEdge(m_hasDictionary);
        if (factory->getExistsReverseEdges())
          factory->reverseEdges->removeEdge(m_hasDictionary, m_id, edkArgumentList_HasDictionary);
      }
      m_hasDictionary = _node->getId();
      if (m_hasDictionary != 0)
        setParentEdge(factory->getPointer(m_hasDictionary), edkArgumentList_HasDictionary);
      if (factory->getExistsReverseEdges())
        factory->reverseEdges->insertEdge(m_hasDictionary, this->getId(), edkArgumentList_HasDictionary);
    } else {
      if (m_hasDictionary) {
        throw PythonException(COLUMBUS_LOCATION, CMSG_EX_CAN_T_SET_EDGE_TO_NULL);
      }
    }
  }

  void ArgumentList::setDictionary(expression::Expression *_node) {
    if (_node == NULL)
      throw PythonException(COLUMBUS_LOCATION, CMSG_EX_CAN_T_SET_EDGE_TO_NULL);

    setDictionary(_node->getId());
  }

  void ArgumentList::removeDictionary() {
      if (m_hasDictionary) {
        removeParentEdge(m_hasDictionary);
        if (factory->getExistsReverseEdges())
          factory->reverseEdges->removeEdge(m_hasDictionary, m_id, edkArgumentList_HasDictionary);
      }
      m_hasDictionary = 0;
  }

  void ArgumentList::addKeyword(const expression::Keyword *_node) {
    if (_node == NULL)
      throw PythonException(COLUMBUS_LOCATION, CMSG_EX_THE_NODE_IS_NULL);

    if (&(_node->getFactory()) != this->factory)
      throw PythonException(COLUMBUS_LOCATION, CMSG_EX_THE_FACTORY_OF_NODES_DOES_NOT_MATCH);

    if (!((_node->getNodeKind() == ndkKeyword) ))
      throw PythonException(COLUMBUS_LOCATION, CMSG_EX_INVALID_NODE_KIND);

    hasKeywordContainer.push_back(_node->getId());
    setParentEdge(_node,edkArgumentList_HasKeyword);

    if (factory->reverseEdges)
      factory->reverseEdges->insertEdge(_node, this, edkArgumentList_HasKeyword);
  }

  void ArgumentList::addKeyword(NodeId _id) {
    const expression::Keyword *node = dynamic_cast<expression::Keyword*>(factory->getPointer(_id));
    if (node == NULL)
      throw PythonException(COLUMBUS_LOCATION, CMSG_EX_INVALID_NODE_KIND);
    addKeyword( node );
  }

  void ArgumentList::removeKeyword(NodeId id) {
    if (!factory->getExist(id))
      throw PythonException(COLUMBUS_LOCATION, CMSG_EX_THE_END_POINT_OF_THE_EDGE_DOES_NOT_EXIST);

    ListIterator<expression::Keyword>::Container::iterator it = find(hasKeywordContainer.begin(), hasKeywordContainer.end(), id);

    if (it == hasKeywordContainer.end())
      throw PythonException(COLUMBUS_LOCATION, CMSG_EX_THE_END_POINT_OF_THE_EDGE_DOES_NOT_EXIST);

    hasKeywordContainer.erase(it);

    removeParentEdge(id);

    if (factory->getExistsReverseEdges())
      factory->reverseEdges->removeEdge(id, this->getId(), edkArgumentList_HasKeyword);
  }

  void ArgumentList::removeKeyword(expression::Keyword *_node) {
    if (_node == NULL)
      throw PythonException(COLUMBUS_LOCATION, CMSG_EX_THE_EDGE_IS_NULL);

    removeKeyword(_node->getId());
  }

  void ArgumentList::setTuple(NodeId _id) {
    expression::Expression *_node = NULL;
    if (_id) {
      if (!factory->getExist(_id))
        throw PythonException(COLUMBUS_LOCATION, CMSG_EX_THE_END_POINT_OF_THE_EDGE_DOES_NOT_EXIST);

      _node = dynamic_cast<expression::Expression*> (factory->getPointer(_id));
      if ( _node == NULL) {
        throw PythonException(COLUMBUS_LOCATION, CMSG_EX_INVALID_NODE_KIND);
      }
      if (&(_node->getFactory()) != this->factory)
        throw PythonException(COLUMBUS_LOCATION, CMSG_EX_THE_FACTORY_OF_NODES_DOES_NOT_MATCH );

      if (m_hasTuple) {
        removeParentEdge(m_hasTuple);
        if (factory->getExistsReverseEdges())
          factory->reverseEdges->removeEdge(m_hasTuple, m_id, edkArgumentList_HasTuple);
      }
      m_hasTuple = _node->getId();
      if (m_hasTuple != 0)
        setParentEdge(factory->getPointer(m_hasTuple), edkArgumentList_HasTuple);
      if (factory->getExistsReverseEdges())
        factory->reverseEdges->insertEdge(m_hasTuple, this->getId(), edkArgumentList_HasTuple);
    } else {
      if (m_hasTuple) {
        throw PythonException(COLUMBUS_LOCATION, CMSG_EX_CAN_T_SET_EDGE_TO_NULL);
      }
    }
  }

  void ArgumentList::setTuple(expression::Expression *_node) {
    if (_node == NULL)
      throw PythonException(COLUMBUS_LOCATION, CMSG_EX_CAN_T_SET_EDGE_TO_NULL);

    setTuple(_node->getId());
  }

  void ArgumentList::removeTuple() {
      if (m_hasTuple) {
        removeParentEdge(m_hasTuple);
        if (factory->getExistsReverseEdges())
          factory->reverseEdges->removeEdge(m_hasTuple, m_id, edkArgumentList_HasTuple);
      }
      m_hasTuple = 0;
  }

  void ArgumentList::accept(Visitor &visitor) const {
    visitor.visit(*this);
  }

  void ArgumentList::acceptEnd(Visitor &visitor) const {
    visitor.visitEnd(*this);
  }

  double ArgumentList::getSimilarity(const base::Base& base){
    if(base.getNodeKind() == getNodeKind()) {
      return 1.0;
    } else {
      return 0.0;
    }
  }

  void ArgumentList::swapStringTable(RefDistributorStrTable& newStrTable, std::map<Key,Key>& oldAndNewStrKeyMap ){
    std::map<Key,Key>::iterator foundKeyId;

  }

  NodeHashType ArgumentList::getHash(std::set<NodeId>& travNodes) const {
    if (hashOk) return nodeHashCache;
    common::WriteMsg::write(CMSG_GET_THE_NODE_HASH_OF_NODE_BEGIN,this->getId()); 
    if (travNodes.count(getId())>0) {
      common::WriteMsg::write(CMSG_GET_THE_NODE_HASH_OF_NODE_SKIP);
      return 0;
    }
    travNodes.insert(getId());
    Crc_type resultHash;
    resultHash.process_bytes( "expression::ArgumentList", strlen("expression::ArgumentList"));
    common::WriteMsg::write(CMSG_GET_THE_NODE_HASH_OF_NODE_END,resultHash.checksum()); 
    nodeHashCache = resultHash.checksum();
    hashOk = true;
    return nodeHashCache;
  }

  void ArgumentList::save(io::BinaryIO &binIo,bool withVirtualBase  /*= true*/) const {
    Positioned::save(binIo,false);

    binIo.writeUInt4(m_hasPositionalArguments);
    binIo.writeUInt4(m_hasDictionary);
    binIo.writeUInt4(m_hasTuple);


    for (ListIterator<expression::Keyword>::Container::const_iterator it = hasKeywordContainer.begin(); it != hasKeywordContainer.end(); ++it) {
      binIo.writeUInt4(*it);
    }
    binIo.writeUInt4(0); // This is the end sign
  }

  void ArgumentList::load(io::BinaryIO &binIo, bool withVirtualBase /*= true*/) {
    Positioned::load(binIo,false);

    m_hasPositionalArguments =  binIo.readUInt4();
    if (m_hasPositionalArguments != 0)
      setParentEdge(factory->getPointer(m_hasPositionalArguments),edkArgumentList_HasPositionalArguments);

    m_hasDictionary =  binIo.readUInt4();
    if (m_hasDictionary != 0)
      setParentEdge(factory->getPointer(m_hasDictionary),edkArgumentList_HasDictionary);

    m_hasTuple =  binIo.readUInt4();
    if (m_hasTuple != 0)
      setParentEdge(factory->getPointer(m_hasTuple),edkArgumentList_HasTuple);

    NodeId _id;

    _id = binIo.readUInt4();
    while (_id) {
      hasKeywordContainer.push_back(_id);
      setParentEdge(factory->getPointer(_id),edkArgumentList_HasKeyword);
      _id = binIo.readUInt4();
    }
  }


}


}}}
