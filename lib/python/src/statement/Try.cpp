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

namespace statement { 
  Try::Try(NodeId _id, Factory *_factory) :
    CompoundStatement(_id, _factory),
    hasHandlerContainer(),
    m_hasElseBody(0),
    m_hasFinallyBody(0)
  {
  }

  Try::~Try() {
  }

  void Try::prepareDelete(bool tryOnVirtualParent){
    while (!hasHandlerContainer.empty()) {
      const NodeId id = *hasHandlerContainer.begin();
      removeParentEdge(id);
      if (factory->getExistsReverseEdges())
        factory->reverseEdges->removeEdge(id, this->getId(), edkTry_HasHandler);
      hasHandlerContainer.pop_front();
    }
    removeElseBody();
    removeFinallyBody();
    statement::CompoundStatement::prepareDelete(false);
  }

  NodeKind Try::getNodeKind() const {
    return ndkTry;
  }

  ListIterator<statement::Handler> Try::getHandlerListIteratorBegin() const {
    return ListIterator<statement::Handler>(&hasHandlerContainer, factory, true);
  }

  ListIterator<statement::Handler> Try::getHandlerListIteratorEnd() const {
    return ListIterator<statement::Handler>(&hasHandlerContainer, factory, false);
  }

  bool Try::getHandlerIsEmpty() const {
    return getHandlerListIteratorBegin() == getHandlerListIteratorEnd();
  }

  unsigned int Try::getHandlerSize() const {
    unsigned int size = 0;
    ListIterator<statement::Handler> endIt = getHandlerListIteratorEnd();
    for (ListIterator<statement::Handler> it = getHandlerListIteratorBegin(); it != endIt; ++it) {
      ++size;
    }
    return size;
  }

  statement::Suite* Try::getElseBody() const {
    statement::Suite *_node = NULL;
    if (m_hasElseBody != 0)
      _node = dynamic_cast<statement::Suite*>(factory->getPointer(m_hasElseBody));
    if ( (_node == NULL) || factory->getIsFiltered(_node))
      return NULL;

    return _node;
  }

  statement::Suite* Try::getFinallyBody() const {
    statement::Suite *_node = NULL;
    if (m_hasFinallyBody != 0)
      _node = dynamic_cast<statement::Suite*>(factory->getPointer(m_hasFinallyBody));
    if ( (_node == NULL) || factory->getIsFiltered(_node))
      return NULL;

    return _node;
  }

  bool Try::setEdge(EdgeKind edgeKind, NodeId edgeEnd, bool tryOnVirtualParent) {
    switch (edgeKind) {
      case edkTry_HasHandler:
        addHandler(edgeEnd);
        return true;
      case edkTry_HasElseBody:
        setElseBody(edgeEnd);
        return true;
      case edkTry_HasFinallyBody:
        setFinallyBody(edgeEnd);
        return true;
      default:
        break;
    }
    if (statement::CompoundStatement::setEdge(edgeKind, edgeEnd, false)) {
      return true;
    }
    return false;
  }

  bool Try::removeEdge(EdgeKind edgeKind, NodeId edgeEnd, bool tryOnVirtualParent) {
    switch (edgeKind) {
      case edkTry_HasHandler:
        removeHandler(edgeEnd);
        return true;
      case edkTry_HasElseBody:
        removeElseBody();
        return true;
      case edkTry_HasFinallyBody:
        removeFinallyBody();
        return true;
      default:
        break;
    }
    if (statement::CompoundStatement::removeEdge(edgeKind, edgeEnd, false)) {
      return true;
    }
    return false;
  }

  void Try::addHandler(const statement::Handler *_node) {
    if (_node == NULL)
      throw PythonException(COLUMBUS_LOCATION, CMSG_EX_THE_NODE_IS_NULL);

    if (&(_node->getFactory()) != this->factory)
      throw PythonException(COLUMBUS_LOCATION, CMSG_EX_THE_FACTORY_OF_NODES_DOES_NOT_MATCH);

    if (!((_node->getNodeKind() == ndkHandler) ))
      throw PythonException(COLUMBUS_LOCATION, CMSG_EX_INVALID_NODE_KIND);

    hasHandlerContainer.push_back(_node->getId());
    setParentEdge(_node,edkTry_HasHandler);

    if (factory->reverseEdges)
      factory->reverseEdges->insertEdge(_node, this, edkTry_HasHandler);
  }

  void Try::addHandler(NodeId _id) {
    const statement::Handler *node = dynamic_cast<statement::Handler*>(factory->getPointer(_id));
    if (node == NULL)
      throw PythonException(COLUMBUS_LOCATION, CMSG_EX_INVALID_NODE_KIND);
    addHandler( node );
  }

  void Try::removeHandler(NodeId id) {
    if (!factory->getExist(id))
      throw PythonException(COLUMBUS_LOCATION, CMSG_EX_THE_END_POINT_OF_THE_EDGE_DOES_NOT_EXIST);

    ListIterator<statement::Handler>::Container::iterator it = find(hasHandlerContainer.begin(), hasHandlerContainer.end(), id);

    if (it == hasHandlerContainer.end())
      throw PythonException(COLUMBUS_LOCATION, CMSG_EX_THE_END_POINT_OF_THE_EDGE_DOES_NOT_EXIST);

    hasHandlerContainer.erase(it);

    removeParentEdge(id);

    if (factory->getExistsReverseEdges())
      factory->reverseEdges->removeEdge(id, this->getId(), edkTry_HasHandler);
  }

  void Try::removeHandler(statement::Handler *_node) {
    if (_node == NULL)
      throw PythonException(COLUMBUS_LOCATION, CMSG_EX_THE_EDGE_IS_NULL);

    removeHandler(_node->getId());
  }

  void Try::setElseBody(NodeId _id) {
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
          factory->reverseEdges->removeEdge(m_hasElseBody, m_id, edkTry_HasElseBody);
      }
      m_hasElseBody = _node->getId();
      if (m_hasElseBody != 0)
        setParentEdge(factory->getPointer(m_hasElseBody), edkTry_HasElseBody);
      if (factory->getExistsReverseEdges())
        factory->reverseEdges->insertEdge(m_hasElseBody, this->getId(), edkTry_HasElseBody);
    } else {
      if (m_hasElseBody) {
        throw PythonException(COLUMBUS_LOCATION, CMSG_EX_CAN_T_SET_EDGE_TO_NULL);
      }
    }
  }

  void Try::setElseBody(statement::Suite *_node) {
    if (_node == NULL)
      throw PythonException(COLUMBUS_LOCATION, CMSG_EX_CAN_T_SET_EDGE_TO_NULL);

    setElseBody(_node->getId());
  }

  void Try::removeElseBody() {
      if (m_hasElseBody) {
        removeParentEdge(m_hasElseBody);
        if (factory->getExistsReverseEdges())
          factory->reverseEdges->removeEdge(m_hasElseBody, m_id, edkTry_HasElseBody);
      }
      m_hasElseBody = 0;
  }

  void Try::setFinallyBody(NodeId _id) {
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
          factory->reverseEdges->removeEdge(m_hasFinallyBody, m_id, edkTry_HasFinallyBody);
      }
      m_hasFinallyBody = _node->getId();
      if (m_hasFinallyBody != 0)
        setParentEdge(factory->getPointer(m_hasFinallyBody), edkTry_HasFinallyBody);
      if (factory->getExistsReverseEdges())
        factory->reverseEdges->insertEdge(m_hasFinallyBody, this->getId(), edkTry_HasFinallyBody);
    } else {
      if (m_hasFinallyBody) {
        throw PythonException(COLUMBUS_LOCATION, CMSG_EX_CAN_T_SET_EDGE_TO_NULL);
      }
    }
  }

  void Try::setFinallyBody(statement::Suite *_node) {
    if (_node == NULL)
      throw PythonException(COLUMBUS_LOCATION, CMSG_EX_CAN_T_SET_EDGE_TO_NULL);

    setFinallyBody(_node->getId());
  }

  void Try::removeFinallyBody() {
      if (m_hasFinallyBody) {
        removeParentEdge(m_hasFinallyBody);
        if (factory->getExistsReverseEdges())
          factory->reverseEdges->removeEdge(m_hasFinallyBody, m_id, edkTry_HasFinallyBody);
      }
      m_hasFinallyBody = 0;
  }

  void Try::accept(Visitor &visitor) const {
    visitor.visit(*this);
  }

  void Try::acceptEnd(Visitor &visitor) const {
    visitor.visitEnd(*this);
  }

  double Try::getSimilarity(const base::Base& base){
    if(base.getNodeKind() == getNodeKind()) {
      return 1.0;
    } else {
      return 0.0;
    }
  }

  void Try::swapStringTable(RefDistributorStrTable& newStrTable, std::map<Key,Key>& oldAndNewStrKeyMap ){
    std::map<Key,Key>::iterator foundKeyId;

  }

  NodeHashType Try::getHash(std::set<NodeId>& travNodes) const {
    if (hashOk) return nodeHashCache;
    common::WriteMsg::write(CMSG_GET_THE_NODE_HASH_OF_NODE_BEGIN,this->getId()); 
    if (travNodes.count(getId())>0) {
      common::WriteMsg::write(CMSG_GET_THE_NODE_HASH_OF_NODE_SKIP);
      return 0;
    }
    travNodes.insert(getId());
    Crc_type resultHash;
    resultHash.process_bytes( "statement::Try", strlen("statement::Try"));
    common::WriteMsg::write(CMSG_GET_THE_NODE_HASH_OF_NODE_END,resultHash.checksum()); 
    nodeHashCache = resultHash.checksum();
    hashOk = true;
    return nodeHashCache;
  }

  void Try::save(io::BinaryIO &binIo,bool withVirtualBase  /*= true*/) const {
    CompoundStatement::save(binIo,false);

    binIo.writeUInt4(m_hasElseBody);
    binIo.writeUInt4(m_hasFinallyBody);


    for (ListIterator<statement::Handler>::Container::const_iterator it = hasHandlerContainer.begin(); it != hasHandlerContainer.end(); ++it) {
      binIo.writeUInt4(*it);
    }
    binIo.writeUInt4(0); // This is the end sign
  }

  void Try::load(io::BinaryIO &binIo, bool withVirtualBase /*= true*/) {
    CompoundStatement::load(binIo,false);

    m_hasElseBody =  binIo.readUInt4();
    if (m_hasElseBody != 0)
      setParentEdge(factory->getPointer(m_hasElseBody),edkTry_HasElseBody);

    m_hasFinallyBody =  binIo.readUInt4();
    if (m_hasFinallyBody != 0)
      setParentEdge(factory->getPointer(m_hasFinallyBody),edkTry_HasFinallyBody);

    NodeId _id;

    _id = binIo.readUInt4();
    while (_id) {
      hasHandlerContainer.push_back(_id);
      setParentEdge(factory->getPointer(_id),edkTry_HasHandler);
      _id = binIo.readUInt4();
    }
  }


}


}}}
