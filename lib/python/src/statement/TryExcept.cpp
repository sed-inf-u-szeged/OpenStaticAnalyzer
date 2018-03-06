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

#include "python/inc/python.h"
#include "python/inc/Common.h"
#include "common/inc/WriteMessage.h"

#include "python/inc/messages.h"
#include <algorithm>
#include <string.h>
#include "common/inc/math/common.h"


namespace columbus { namespace python { namespace asg {

typedef boost::crc_32_type  Crc_type;

namespace statement { 
  TryExcept::TryExcept(NodeId _id, Factory *_factory) :
    Try(_id, _factory),
    m_hasElseBody(0),
    hasHandlerContainer(),
    m_hasFinallyBody(0)
  {
  }

  TryExcept::~TryExcept() {
  }

  void TryExcept::prepareDelete(bool tryOnVirtualParent){
    removeElseBody();
    while (!hasHandlerContainer.empty()) {
      const NodeId id = *hasHandlerContainer.begin();
      removeParentEdge(id);
      if (factory->getExistsReverseEdges())
        factory->reverseEdges->removeEdge(id, this->getId(), edkTryExcept_HasHandler);
      hasHandlerContainer.pop_front();
    }
    removeFinallyBody();
    statement::Try::prepareDelete(false);
  }

  NodeKind TryExcept::getNodeKind() const {
    return ndkTryExcept;
  }

  statement::Suite* TryExcept::getElseBody() const {
    statement::Suite *_node = NULL;
    if (m_hasElseBody != 0)
      _node = dynamic_cast<statement::Suite*>(factory->getPointer(m_hasElseBody));
    if ( (_node == NULL) || factory->getIsFiltered(_node))
      return NULL;

    return _node;
  }

  ListIterator<statement::Handler> TryExcept::getHandlerListIteratorBegin() const {
    return ListIterator<statement::Handler>(&hasHandlerContainer, factory, true);
  }

  ListIterator<statement::Handler> TryExcept::getHandlerListIteratorEnd() const {
    return ListIterator<statement::Handler>(&hasHandlerContainer, factory, false);
  }

  bool TryExcept::getHandlerIsEmpty() const {
    return getHandlerListIteratorBegin() == getHandlerListIteratorEnd();
  }

  unsigned int TryExcept::getHandlerSize() const {
    unsigned int size = 0;
    ListIterator<statement::Handler> endIt = getHandlerListIteratorEnd();
    for (ListIterator<statement::Handler> it = getHandlerListIteratorBegin(); it != endIt; ++it) {
      ++size;
    }
    return size;
  }

  statement::Suite* TryExcept::getFinallyBody() const {
    statement::Suite *_node = NULL;
    if (m_hasFinallyBody != 0)
      _node = dynamic_cast<statement::Suite*>(factory->getPointer(m_hasFinallyBody));
    if ( (_node == NULL) || factory->getIsFiltered(_node))
      return NULL;

    return _node;
  }

  bool TryExcept::setEdge(EdgeKind edgeKind, NodeId edgeEnd, bool tryOnVirtualParent) {
    switch (edgeKind) {
      case edkTryExcept_HasElseBody:
        setElseBody(edgeEnd);
        return true;
      case edkTryExcept_HasHandler:
        addHandler(edgeEnd);
        return true;
      case edkTryExcept_HasFinallyBody:
        setFinallyBody(edgeEnd);
        return true;
      default:
        break;
    }
    if (statement::Try::setEdge(edgeKind, edgeEnd, false)) {
      return true;
    }
    return false;
  }

  bool TryExcept::removeEdge(EdgeKind edgeKind, NodeId edgeEnd, bool tryOnVirtualParent) {
    switch (edgeKind) {
      case edkTryExcept_HasElseBody:
        removeElseBody();
        return true;
      case edkTryExcept_HasHandler:
        removeHandler(edgeEnd);
        return true;
      case edkTryExcept_HasFinallyBody:
        removeFinallyBody();
        return true;
      default:
        break;
    }
    if (statement::Try::removeEdge(edgeKind, edgeEnd, false)) {
      return true;
    }
    return false;
  }

  void TryExcept::setElseBody(NodeId _id) {
    statement::Suite *_node = NULL;
    if (_id) {
      if (!factory->getExist(_id))
        throw PythonException(COLUMBUS_LOCATION, CMSG_EX_THE_END_POINT_OF_THE_EDGE_DOES_NOT_EXIST);

      _node = dynamic_cast<statement::Suite*> (factory->getPointer(_id));
      if ( _node == NULL) {
        throw PythonException(COLUMBUS_LOCATION, CMSG_EX_INVALID_NODE_KIND);
      }
      if (&(_node->getFactory()) != this->factory)
        throw PythonException(COLUMBUS_LOCATION, CMSG_EX_THE_FACTORY_OF_NODES_DOES_NOT_MATCH );

      if (m_hasElseBody) {
        removeParentEdge(m_hasElseBody);
        if (factory->getExistsReverseEdges())
          factory->reverseEdges->removeEdge(m_hasElseBody, m_id, edkTryExcept_HasElseBody);
      }
      m_hasElseBody = _node->getId();
      if (m_hasElseBody != 0)
        setParentEdge(factory->getPointer(m_hasElseBody), edkTryExcept_HasElseBody);
      if (factory->getExistsReverseEdges())
        factory->reverseEdges->insertEdge(m_hasElseBody, this->getId(), edkTryExcept_HasElseBody);
    } else {
      if (m_hasElseBody) {
        throw PythonException(COLUMBUS_LOCATION, CMSG_EX_CAN_T_SET_EDGE_TO_NULL);
      }
    }
  }

  void TryExcept::setElseBody(statement::Suite *_node) {
    if (_node == NULL)
      throw PythonException(COLUMBUS_LOCATION, CMSG_EX_CAN_T_SET_EDGE_TO_NULL);

    setElseBody(_node->getId());
  }

  void TryExcept::removeElseBody() {
      if (m_hasElseBody) {
        removeParentEdge(m_hasElseBody);
        if (factory->getExistsReverseEdges())
          factory->reverseEdges->removeEdge(m_hasElseBody, m_id, edkTryExcept_HasElseBody);
      }
      m_hasElseBody = 0;
  }

  void TryExcept::addHandler(const statement::Handler *_node) {
    if (_node == NULL)
      throw PythonException(COLUMBUS_LOCATION, CMSG_EX_THE_NODE_IS_NULL);

    if (&(_node->getFactory()) != this->factory)
      throw PythonException(COLUMBUS_LOCATION, CMSG_EX_THE_FACTORY_OF_NODES_DOES_NOT_MATCH);

    if (!((_node->getNodeKind() == ndkHandler) ))
      throw PythonException(COLUMBUS_LOCATION, CMSG_EX_INVALID_NODE_KIND);

    hasHandlerContainer.push_back(_node->getId());
    setParentEdge(_node,edkTryExcept_HasHandler);

    if (factory->reverseEdges)
      factory->reverseEdges->insertEdge(_node, this, edkTryExcept_HasHandler);
  }

  void TryExcept::addHandler(NodeId _id) {
    const statement::Handler *node = dynamic_cast<statement::Handler*>(factory->getPointer(_id));
    if (node == NULL)
      throw PythonException(COLUMBUS_LOCATION, CMSG_EX_INVALID_NODE_KIND);
    addHandler( node );
  }

  void TryExcept::removeHandler(NodeId id) {
    if (!factory->getExist(id))
      throw PythonException(COLUMBUS_LOCATION, CMSG_EX_THE_END_POINT_OF_THE_EDGE_DOES_NOT_EXIST);

    ListIterator<statement::Handler>::Container::iterator it = find(hasHandlerContainer.begin(), hasHandlerContainer.end(), id);

    if (it == hasHandlerContainer.end())
      throw PythonException(COLUMBUS_LOCATION, CMSG_EX_THE_END_POINT_OF_THE_EDGE_DOES_NOT_EXIST);

    hasHandlerContainer.erase(it);

    removeParentEdge(id);

    if (factory->getExistsReverseEdges())
      factory->reverseEdges->removeEdge(id, this->getId(), edkTryExcept_HasHandler);
  }

  void TryExcept::removeHandler(statement::Handler *_node) {
    if (_node == NULL)
      throw PythonException(COLUMBUS_LOCATION, CMSG_EX_THE_EDGE_IS_NULL);

    removeHandler(_node->getId());
  }

  void TryExcept::setFinallyBody(NodeId _id) {
    statement::Suite *_node = NULL;
    if (_id) {
      if (!factory->getExist(_id))
        throw PythonException(COLUMBUS_LOCATION, CMSG_EX_THE_END_POINT_OF_THE_EDGE_DOES_NOT_EXIST);

      _node = dynamic_cast<statement::Suite*> (factory->getPointer(_id));
      if ( _node == NULL) {
        throw PythonException(COLUMBUS_LOCATION, CMSG_EX_INVALID_NODE_KIND);
      }
      if (&(_node->getFactory()) != this->factory)
        throw PythonException(COLUMBUS_LOCATION, CMSG_EX_THE_FACTORY_OF_NODES_DOES_NOT_MATCH );

      if (m_hasFinallyBody) {
        removeParentEdge(m_hasFinallyBody);
        if (factory->getExistsReverseEdges())
          factory->reverseEdges->removeEdge(m_hasFinallyBody, m_id, edkTryExcept_HasFinallyBody);
      }
      m_hasFinallyBody = _node->getId();
      if (m_hasFinallyBody != 0)
        setParentEdge(factory->getPointer(m_hasFinallyBody), edkTryExcept_HasFinallyBody);
      if (factory->getExistsReverseEdges())
        factory->reverseEdges->insertEdge(m_hasFinallyBody, this->getId(), edkTryExcept_HasFinallyBody);
    } else {
      if (m_hasFinallyBody) {
        throw PythonException(COLUMBUS_LOCATION, CMSG_EX_CAN_T_SET_EDGE_TO_NULL);
      }
    }
  }

  void TryExcept::setFinallyBody(statement::Suite *_node) {
    if (_node == NULL)
      throw PythonException(COLUMBUS_LOCATION, CMSG_EX_CAN_T_SET_EDGE_TO_NULL);

    setFinallyBody(_node->getId());
  }

  void TryExcept::removeFinallyBody() {
      if (m_hasFinallyBody) {
        removeParentEdge(m_hasFinallyBody);
        if (factory->getExistsReverseEdges())
          factory->reverseEdges->removeEdge(m_hasFinallyBody, m_id, edkTryExcept_HasFinallyBody);
      }
      m_hasFinallyBody = 0;
  }

  void TryExcept::accept(Visitor &visitor) const {
    visitor.visit(*this);
  }

  void TryExcept::acceptEnd(Visitor &visitor) const {
    visitor.visitEnd(*this);
  }

  double TryExcept::getSimilarity(const base::Base& base){
    if(base.getNodeKind() == getNodeKind()) {
      return 1.0;
    } else {
      return 0.0;
    }
  }

  void TryExcept::swapStringTable(RefDistributorStrTable& newStrTable, std::map<Key,Key>& oldAndNewStrKeyMap ){
    std::map<Key,Key>::iterator foundKeyId;

  }

  NodeHashType TryExcept::getHash(std::set<NodeId>& travNodes) const {
    if (hashOk) return nodeHashCache;
    common::WriteMsg::write(CMSG_GET_THE_NODE_HASH_OF_NODE_BEGIN,this->getId()); 
    if (travNodes.count(getId())>0) {
      common::WriteMsg::write(CMSG_GET_THE_NODE_HASH_OF_NODE_SKIP);
      return 0;
    }
    travNodes.insert(getId());
    Crc_type resultHash;
    resultHash.process_bytes( "statement::TryExcept", strlen("statement::TryExcept"));
    common::WriteMsg::write(CMSG_GET_THE_NODE_HASH_OF_NODE_END,resultHash.checksum()); 
    nodeHashCache = resultHash.checksum();
    hashOk = true;
    return nodeHashCache;
  }

  void TryExcept::save(io::BinaryIO &binIo,bool withVirtualBase  /*= true*/) const {
    Try::save(binIo,false);

    binIo.writeUInt4(m_hasElseBody);
    binIo.writeUInt4(m_hasFinallyBody);


    for (ListIterator<statement::Handler>::Container::const_iterator it = hasHandlerContainer.begin(); it != hasHandlerContainer.end(); ++it) {
      binIo.writeUInt4(*it);
    }
    binIo.writeUInt4(0); // This is the end sign
  }

  void TryExcept::load(io::BinaryIO &binIo, bool withVirtualBase /*= true*/) {
    Try::load(binIo,false);

    m_hasElseBody =  binIo.readUInt4();
    if (m_hasElseBody != 0)
      setParentEdge(factory->getPointer(m_hasElseBody),edkTryExcept_HasElseBody);

    m_hasFinallyBody =  binIo.readUInt4();
    if (m_hasFinallyBody != 0)
      setParentEdge(factory->getPointer(m_hasFinallyBody),edkTryExcept_HasFinallyBody);

    NodeId _id;

    _id = binIo.readUInt4();
    while (_id) {
      hasHandlerContainer.push_back(_id);
      setParentEdge(factory->getPointer(_id),edkTryExcept_HasHandler);
      _id = binIo.readUInt4();
    }
  }


}


}}}
