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
  Handler::Handler(NodeId _id, Factory *_factory) :
    Statement(_id, _factory),
    m_hasName(0),
    m_hasExceptBody(0),
    m_hasType(0)
  {
  }

  Handler::~Handler() {
  }

  void Handler::prepareDelete(bool tryOnVirtualParent){
    removeName();
    removeExceptBody();
    removeType();
    statement::Statement::prepareDelete(false);
  }

  NodeKind Handler::getNodeKind() const {
    return ndkHandler;
  }

  expression::Expression* Handler::getName() const {
    expression::Expression *_node = NULL;
    if (m_hasName != 0)
      _node = dynamic_cast<expression::Expression*>(factory->getPointer(m_hasName));
    if ( (_node == NULL) || factory->getIsFiltered(_node))
      return NULL;

    return _node;
  }

  statement::Suite* Handler::getExceptBody() const {
    statement::Suite *_node = NULL;
    if (m_hasExceptBody != 0)
      _node = dynamic_cast<statement::Suite*>(factory->getPointer(m_hasExceptBody));
    if ( (_node == NULL) || factory->getIsFiltered(_node))
      return NULL;

    return _node;
  }

  expression::Expression* Handler::getType() const {
    expression::Expression *_node = NULL;
    if (m_hasType != 0)
      _node = dynamic_cast<expression::Expression*>(factory->getPointer(m_hasType));
    if ( (_node == NULL) || factory->getIsFiltered(_node))
      return NULL;

    return _node;
  }

  bool Handler::setEdge(EdgeKind edgeKind, NodeId edgeEnd, bool tryOnVirtualParent) {
    switch (edgeKind) {
      case edkHandler_HasName:
        setName(edgeEnd);
        return true;
      case edkHandler_HasExceptBody:
        setExceptBody(edgeEnd);
        return true;
      case edkHandler_HasType:
        setType(edgeEnd);
        return true;
      default:
        break;
    }
    if (statement::Statement::setEdge(edgeKind, edgeEnd, false)) {
      return true;
    }
    return false;
  }

  bool Handler::removeEdge(EdgeKind edgeKind, NodeId edgeEnd, bool tryOnVirtualParent) {
    switch (edgeKind) {
      case edkHandler_HasName:
        removeName();
        return true;
      case edkHandler_HasExceptBody:
        removeExceptBody();
        return true;
      case edkHandler_HasType:
        removeType();
        return true;
      default:
        break;
    }
    if (statement::Statement::removeEdge(edgeKind, edgeEnd, false)) {
      return true;
    }
    return false;
  }

  void Handler::setName(NodeId _id) {
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

      if (m_hasName) {
        removeParentEdge(m_hasName);
        if (factory->getExistsReverseEdges())
          factory->reverseEdges->removeEdge(m_hasName, m_id, edkHandler_HasName);
      }
      m_hasName = _node->getId();
      if (m_hasName != 0)
        setParentEdge(factory->getPointer(m_hasName), edkHandler_HasName);
      if (factory->getExistsReverseEdges())
        factory->reverseEdges->insertEdge(m_hasName, this->getId(), edkHandler_HasName);
    } else {
      if (m_hasName) {
        throw PythonException(COLUMBUS_LOCATION, CMSG_EX_CAN_T_SET_EDGE_TO_NULL);
      }
    }
  }

  void Handler::setName(expression::Expression *_node) {
    if (_node == NULL)
      throw PythonException(COLUMBUS_LOCATION, CMSG_EX_CAN_T_SET_EDGE_TO_NULL);

    setName(_node->getId());
  }

  void Handler::removeName() {
      if (m_hasName) {
        removeParentEdge(m_hasName);
        if (factory->getExistsReverseEdges())
          factory->reverseEdges->removeEdge(m_hasName, m_id, edkHandler_HasName);
      }
      m_hasName = 0;
  }

  void Handler::setExceptBody(NodeId _id) {
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

      if (m_hasExceptBody) {
        removeParentEdge(m_hasExceptBody);
        if (factory->getExistsReverseEdges())
          factory->reverseEdges->removeEdge(m_hasExceptBody, m_id, edkHandler_HasExceptBody);
      }
      m_hasExceptBody = _node->getId();
      if (m_hasExceptBody != 0)
        setParentEdge(factory->getPointer(m_hasExceptBody), edkHandler_HasExceptBody);
      if (factory->getExistsReverseEdges())
        factory->reverseEdges->insertEdge(m_hasExceptBody, this->getId(), edkHandler_HasExceptBody);
    } else {
      if (m_hasExceptBody) {
        throw PythonException(COLUMBUS_LOCATION, CMSG_EX_CAN_T_SET_EDGE_TO_NULL);
      }
    }
  }

  void Handler::setExceptBody(statement::Suite *_node) {
    if (_node == NULL)
      throw PythonException(COLUMBUS_LOCATION, CMSG_EX_CAN_T_SET_EDGE_TO_NULL);

    setExceptBody(_node->getId());
  }

  void Handler::removeExceptBody() {
      if (m_hasExceptBody) {
        removeParentEdge(m_hasExceptBody);
        if (factory->getExistsReverseEdges())
          factory->reverseEdges->removeEdge(m_hasExceptBody, m_id, edkHandler_HasExceptBody);
      }
      m_hasExceptBody = 0;
  }

  void Handler::setType(NodeId _id) {
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

      if (m_hasType) {
        removeParentEdge(m_hasType);
        if (factory->getExistsReverseEdges())
          factory->reverseEdges->removeEdge(m_hasType, m_id, edkHandler_HasType);
      }
      m_hasType = _node->getId();
      if (m_hasType != 0)
        setParentEdge(factory->getPointer(m_hasType), edkHandler_HasType);
      if (factory->getExistsReverseEdges())
        factory->reverseEdges->insertEdge(m_hasType, this->getId(), edkHandler_HasType);
    } else {
      if (m_hasType) {
        throw PythonException(COLUMBUS_LOCATION, CMSG_EX_CAN_T_SET_EDGE_TO_NULL);
      }
    }
  }

  void Handler::setType(expression::Expression *_node) {
    if (_node == NULL)
      throw PythonException(COLUMBUS_LOCATION, CMSG_EX_CAN_T_SET_EDGE_TO_NULL);

    setType(_node->getId());
  }

  void Handler::removeType() {
      if (m_hasType) {
        removeParentEdge(m_hasType);
        if (factory->getExistsReverseEdges())
          factory->reverseEdges->removeEdge(m_hasType, m_id, edkHandler_HasType);
      }
      m_hasType = 0;
  }

  void Handler::accept(Visitor &visitor) const {
    visitor.visit(*this);
  }

  void Handler::acceptEnd(Visitor &visitor) const {
    visitor.visitEnd(*this);
  }

  double Handler::getSimilarity(const base::Base& base){
    if(base.getNodeKind() == getNodeKind()) {
      return 1.0;
    } else {
      return 0.0;
    }
  }

  void Handler::swapStringTable(RefDistributorStrTable& newStrTable, std::map<Key,Key>& oldAndNewStrKeyMap ){
    std::map<Key,Key>::iterator foundKeyId;

  }

  NodeHashType Handler::getHash(std::set<NodeId>& travNodes) const {
    if (hashOk) return nodeHashCache;
    common::WriteMsg::write(CMSG_GET_THE_NODE_HASH_OF_NODE_BEGIN,this->getId()); 
    if (travNodes.count(getId())>0) {
      common::WriteMsg::write(CMSG_GET_THE_NODE_HASH_OF_NODE_SKIP);
      return 0;
    }
    travNodes.insert(getId());
    Crc_type resultHash;
    resultHash.process_bytes( "statement::Handler", strlen("statement::Handler"));
    common::WriteMsg::write(CMSG_GET_THE_NODE_HASH_OF_NODE_END,resultHash.checksum()); 
    nodeHashCache = resultHash.checksum();
    hashOk = true;
    return nodeHashCache;
  }

  void Handler::save(io::BinaryIO &binIo,bool withVirtualBase  /*= true*/) const {
    Statement::save(binIo,false);

    binIo.writeUInt4(m_hasName);
    binIo.writeUInt4(m_hasExceptBody);
    binIo.writeUInt4(m_hasType);

  }

  void Handler::load(io::BinaryIO &binIo, bool withVirtualBase /*= true*/) {
    Statement::load(binIo,false);

    m_hasName =  binIo.readUInt4();
    if (m_hasName != 0)
      setParentEdge(factory->getPointer(m_hasName),edkHandler_HasName);

    m_hasExceptBody =  binIo.readUInt4();
    if (m_hasExceptBody != 0)
      setParentEdge(factory->getPointer(m_hasExceptBody),edkHandler_HasExceptBody);

    m_hasType =  binIo.readUInt4();
    if (m_hasType != 0)
      setParentEdge(factory->getPointer(m_hasType),edkHandler_HasType);

  }


}


}}}
