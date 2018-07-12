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
  BaseSpecifier::BaseSpecifier(NodeId _id, Factory *_factory) :
    Positioned(_id, _factory),
    m_hasName(0),
    m_derivesFrom(0)
  {
  }

  BaseSpecifier::~BaseSpecifier() {
  }

  void BaseSpecifier::prepareDelete(bool tryOnVirtualParent){
    removeName();
    removeDerivesFrom();
    base::Positioned::prepareDelete(false);
  }

  NodeKind BaseSpecifier::getNodeKind() const {
    return ndkBaseSpecifier;
  }

  expression::Expression* BaseSpecifier::getName() const {
    expression::Expression *_node = NULL;
    if (m_hasName != 0)
      _node = dynamic_cast<expression::Expression*>(factory->getPointer(m_hasName));
    if ( (_node == NULL) || factory->getIsFiltered(_node))
      return NULL;

    return _node;
  }

  statement::ClassDef* BaseSpecifier::getDerivesFrom() const {
    statement::ClassDef *_node = NULL;
    if (m_derivesFrom != 0)
      _node = dynamic_cast<statement::ClassDef*>(factory->getPointer(m_derivesFrom));
    if ( (_node == NULL) || factory->getIsFiltered(_node))
      return NULL;

    return _node;
  }

  bool BaseSpecifier::setEdge(EdgeKind edgeKind, NodeId edgeEnd, bool tryOnVirtualParent) {
    switch (edgeKind) {
      case edkBaseSpecifier_HasName:
        setName(edgeEnd);
        return true;
      case edkBaseSpecifier_DerivesFrom:
        setDerivesFrom(edgeEnd);
        return true;
      default:
        break;
    }
    if (base::Positioned::setEdge(edgeKind, edgeEnd, false)) {
      return true;
    }
    return false;
  }

  bool BaseSpecifier::removeEdge(EdgeKind edgeKind, NodeId edgeEnd, bool tryOnVirtualParent) {
    switch (edgeKind) {
      case edkBaseSpecifier_HasName:
        removeName();
        return true;
      case edkBaseSpecifier_DerivesFrom:
        removeDerivesFrom();
        return true;
      default:
        break;
    }
    if (base::Positioned::removeEdge(edgeKind, edgeEnd, false)) {
      return true;
    }
    return false;
  }

  void BaseSpecifier::setName(NodeId _id) {
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
          factory->reverseEdges->removeEdge(m_hasName, m_id, edkBaseSpecifier_HasName);
      }
      m_hasName = _node->getId();
      if (m_hasName != 0)
        setParentEdge(factory->getPointer(m_hasName), edkBaseSpecifier_HasName);
      if (factory->getExistsReverseEdges())
        factory->reverseEdges->insertEdge(m_hasName, this->getId(), edkBaseSpecifier_HasName);
    } else {
      if (m_hasName) {
        throw PythonException(COLUMBUS_LOCATION, CMSG_EX_CAN_T_SET_EDGE_TO_NULL);
      }
    }
  }

  void BaseSpecifier::setName(expression::Expression *_node) {
    if (_node == NULL)
      throw PythonException(COLUMBUS_LOCATION, CMSG_EX_CAN_T_SET_EDGE_TO_NULL);

    setName(_node->getId());
  }

  void BaseSpecifier::removeName() {
      if (m_hasName) {
        removeParentEdge(m_hasName);
        if (factory->getExistsReverseEdges())
          factory->reverseEdges->removeEdge(m_hasName, m_id, edkBaseSpecifier_HasName);
      }
      m_hasName = 0;
  }

  void BaseSpecifier::setDerivesFrom(NodeId _id) {
    statement::ClassDef *_node = NULL;
    if (_id) {
      if (!factory->getExist(_id))
        throw PythonException(COLUMBUS_LOCATION, CMSG_EX_THE_END_POINT_OF_THE_EDGE_DOES_NOT_EXIST);

      _node = dynamic_cast<statement::ClassDef*> (factory->getPointer(_id));
      if ( _node == NULL) {
        throw PythonException(COLUMBUS_LOCATION, CMSG_EX_INVALID_NODE_KIND);
      }
      if (&(_node->getFactory()) != this->factory)
        throw PythonException(COLUMBUS_LOCATION, CMSG_EX_THE_FACTORY_OF_NODES_DOES_NOT_MATCH );

      if (m_derivesFrom) {
        if (factory->getExistsReverseEdges())
          factory->reverseEdges->removeEdge(m_derivesFrom, m_id, edkBaseSpecifier_DerivesFrom);
      }
      m_derivesFrom = _node->getId();
      if (factory->getExistsReverseEdges())
        factory->reverseEdges->insertEdge(m_derivesFrom, this->getId(), edkBaseSpecifier_DerivesFrom);
    } else {
      if (m_derivesFrom) {
        throw PythonException(COLUMBUS_LOCATION, CMSG_EX_CAN_T_SET_EDGE_TO_NULL);
      }
    }
  }

  void BaseSpecifier::setDerivesFrom(statement::ClassDef *_node) {
    if (_node == NULL)
      throw PythonException(COLUMBUS_LOCATION, CMSG_EX_CAN_T_SET_EDGE_TO_NULL);

    setDerivesFrom(_node->getId());
  }

  void BaseSpecifier::removeDerivesFrom() {
      if (m_derivesFrom) {
        if (factory->getExistsReverseEdges())
          factory->reverseEdges->removeEdge(m_derivesFrom, m_id, edkBaseSpecifier_DerivesFrom);
      }
      m_derivesFrom = 0;
  }

  void BaseSpecifier::accept(Visitor &visitor) const {
    visitor.visit(*this);
  }

  void BaseSpecifier::acceptEnd(Visitor &visitor) const {
    visitor.visitEnd(*this);
  }

  double BaseSpecifier::getSimilarity(const base::Base& base){
    if(base.getNodeKind() == getNodeKind()) {
      return 1.0;
    } else {
      return 0.0;
    }
  }

  void BaseSpecifier::swapStringTable(RefDistributorStrTable& newStrTable, std::map<Key,Key>& oldAndNewStrKeyMap ){
    std::map<Key,Key>::iterator foundKeyId;

  }

  NodeHashType BaseSpecifier::getHash(std::set<NodeId>& travNodes) const {
    if (hashOk) return nodeHashCache;
    common::WriteMsg::write(CMSG_GET_THE_NODE_HASH_OF_NODE_BEGIN,this->getId()); 
    if (travNodes.count(getId())>0) {
      common::WriteMsg::write(CMSG_GET_THE_NODE_HASH_OF_NODE_SKIP);
      return 0;
    }
    travNodes.insert(getId());
    Crc_type resultHash;
    resultHash.process_bytes( "statement::BaseSpecifier", strlen("statement::BaseSpecifier"));
    common::WriteMsg::write(CMSG_GET_THE_NODE_HASH_OF_NODE_END,resultHash.checksum()); 
    nodeHashCache = resultHash.checksum();
    hashOk = true;
    return nodeHashCache;
  }

  void BaseSpecifier::save(io::BinaryIO &binIo,bool withVirtualBase  /*= true*/) const {
    Positioned::save(binIo,false);

    binIo.writeUInt4(m_hasName);
    binIo.writeUInt4(m_derivesFrom);

  }

  void BaseSpecifier::load(io::BinaryIO &binIo, bool withVirtualBase /*= true*/) {
    Positioned::load(binIo,false);

    m_hasName =  binIo.readUInt4();
    if (m_hasName != 0)
      setParentEdge(factory->getPointer(m_hasName),edkBaseSpecifier_HasName);

    m_derivesFrom =  binIo.readUInt4();

  }


}


}}}
