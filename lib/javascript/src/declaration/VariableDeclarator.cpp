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

#include "javascript/inc/javascript.h"
#include "javascript/inc/Common.h"
#include "common/inc/WriteMessage.h"

#include "javascript/inc/messages.h"
#include <algorithm>
#include <string.h>
#include "common/inc/math/common.h"


namespace columbus { namespace javascript { namespace asg {

typedef boost::crc_32_type  Crc_type;

namespace declaration { 
  VariableDeclarator::VariableDeclarator(NodeId _id, Factory *_factory) :
    Positioned(_id, _factory),
    m_hasIdentifier(0),
    m_hasInit(0)
  {
  }

  VariableDeclarator::~VariableDeclarator() {
  }

  void VariableDeclarator::prepareDelete(bool tryOnVirtualParent){
    removeIdentifier();
    removeInit();
    base::Positioned::prepareDelete(false);
  }

  NodeKind VariableDeclarator::getNodeKind() const {
    return ndkVariableDeclarator;
  }

  statement::Pattern* VariableDeclarator::getIdentifier() const {
    statement::Pattern *_node = NULL;
    if (m_hasIdentifier != 0)
      _node = dynamic_cast<statement::Pattern*>(factory->getPointer(m_hasIdentifier));
    if ( (_node == NULL) || factory->getIsFiltered(_node))
      return NULL;

    return _node;
  }

  expression::Expression* VariableDeclarator::getInit() const {
    expression::Expression *_node = NULL;
    if (m_hasInit != 0)
      _node = dynamic_cast<expression::Expression*>(factory->getPointer(m_hasInit));
    if ( (_node == NULL) || factory->getIsFiltered(_node))
      return NULL;

    return _node;
  }

  bool VariableDeclarator::setEdge(EdgeKind edgeKind, NodeId edgeEnd, bool tryOnVirtualParent) {
    switch (edgeKind) {
      case edkVariableDeclarator_HasIdentifier:
        setIdentifier(edgeEnd);
        return true;
      case edkVariableDeclarator_HasInit:
        setInit(edgeEnd);
        return true;
      default:
        break;
    }
    if (base::Positioned::setEdge(edgeKind, edgeEnd, false)) {
      return true;
    }
    return false;
  }

  bool VariableDeclarator::removeEdge(EdgeKind edgeKind, NodeId edgeEnd, bool tryOnVirtualParent) {
    switch (edgeKind) {
      case edkVariableDeclarator_HasIdentifier:
        removeIdentifier();
        return true;
      case edkVariableDeclarator_HasInit:
        removeInit();
        return true;
      default:
        break;
    }
    if (base::Positioned::removeEdge(edgeKind, edgeEnd, false)) {
      return true;
    }
    return false;
  }

  void VariableDeclarator::setIdentifier(NodeId _id) {
    statement::Pattern *_node = NULL;
    if (_id) {
      if (!factory->getExist(_id))
        throw JavaScriptException(COLUMBUS_LOCATION, CMSG_EX_THE_END_POINT_OF_THE_EDGE_DOES_NOT_EXIST);

      _node = dynamic_cast<statement::Pattern*> (factory->getPointer(_id));
      if ( _node == NULL) {
        throw JavaScriptException(COLUMBUS_LOCATION, CMSG_EX_INVALID_NODE_KIND);
      }
      if (&(_node->getFactory()) != this->factory)
        throw JavaScriptException(COLUMBUS_LOCATION, CMSG_EX_THE_FACTORY_OF_NODES_DOES_NOT_MATCH );

      if (m_hasIdentifier) {
        removeParentEdge(m_hasIdentifier);
        if (factory->getExistsReverseEdges())
          factory->reverseEdges->removeEdge(m_hasIdentifier, m_id, edkVariableDeclarator_HasIdentifier);
      }
      m_hasIdentifier = _node->getId();
      if (m_hasIdentifier != 0)
        setParentEdge(factory->getPointer(m_hasIdentifier), edkVariableDeclarator_HasIdentifier);
      if (factory->getExistsReverseEdges())
        factory->reverseEdges->insertEdge(m_hasIdentifier, this->getId(), edkVariableDeclarator_HasIdentifier);
    } else {
      if (m_hasIdentifier) {
        throw JavaScriptException(COLUMBUS_LOCATION, CMSG_EX_CAN_T_SET_EDGE_TO_NULL);
      }
    }
  }

  void VariableDeclarator::setIdentifier(statement::Pattern *_node) {
    if (_node == NULL)
      throw JavaScriptException(COLUMBUS_LOCATION, CMSG_EX_CAN_T_SET_EDGE_TO_NULL);

    setIdentifier(_node->getId());
  }

  void VariableDeclarator::removeIdentifier() {
      if (m_hasIdentifier) {
        removeParentEdge(m_hasIdentifier);
        if (factory->getExistsReverseEdges())
          factory->reverseEdges->removeEdge(m_hasIdentifier, m_id, edkVariableDeclarator_HasIdentifier);
      }
      m_hasIdentifier = 0;
  }

  void VariableDeclarator::setInit(NodeId _id) {
    expression::Expression *_node = NULL;
    if (_id) {
      if (!factory->getExist(_id))
        throw JavaScriptException(COLUMBUS_LOCATION, CMSG_EX_THE_END_POINT_OF_THE_EDGE_DOES_NOT_EXIST);

      _node = dynamic_cast<expression::Expression*> (factory->getPointer(_id));
      if ( _node == NULL) {
        throw JavaScriptException(COLUMBUS_LOCATION, CMSG_EX_INVALID_NODE_KIND);
      }
      if (&(_node->getFactory()) != this->factory)
        throw JavaScriptException(COLUMBUS_LOCATION, CMSG_EX_THE_FACTORY_OF_NODES_DOES_NOT_MATCH );

      if (m_hasInit) {
        removeParentEdge(m_hasInit);
        if (factory->getExistsReverseEdges())
          factory->reverseEdges->removeEdge(m_hasInit, m_id, edkVariableDeclarator_HasInit);
      }
      m_hasInit = _node->getId();
      if (m_hasInit != 0)
        setParentEdge(factory->getPointer(m_hasInit), edkVariableDeclarator_HasInit);
      if (factory->getExistsReverseEdges())
        factory->reverseEdges->insertEdge(m_hasInit, this->getId(), edkVariableDeclarator_HasInit);
    } else {
      if (m_hasInit) {
        throw JavaScriptException(COLUMBUS_LOCATION, CMSG_EX_CAN_T_SET_EDGE_TO_NULL);
      }
    }
  }

  void VariableDeclarator::setInit(expression::Expression *_node) {
    if (_node == NULL)
      throw JavaScriptException(COLUMBUS_LOCATION, CMSG_EX_CAN_T_SET_EDGE_TO_NULL);

    setInit(_node->getId());
  }

  void VariableDeclarator::removeInit() {
      if (m_hasInit) {
        removeParentEdge(m_hasInit);
        if (factory->getExistsReverseEdges())
          factory->reverseEdges->removeEdge(m_hasInit, m_id, edkVariableDeclarator_HasInit);
      }
      m_hasInit = 0;
  }

  void VariableDeclarator::accept(Visitor &visitor) const {
    visitor.visit(*this);
  }

  void VariableDeclarator::acceptEnd(Visitor &visitor) const {
    visitor.visitEnd(*this);
  }

  double VariableDeclarator::getSimilarity(const base::Base& base){
    if(base.getNodeKind() == getNodeKind()) {
      return 1.0;
    } else {
      return 0.0;
    }
  }

  void VariableDeclarator::swapStringTable(RefDistributorStrTable& newStrTable, std::map<Key,Key>& oldAndNewStrKeyMap ){
    std::map<Key,Key>::iterator foundKeyId;

  }

  NodeHashType VariableDeclarator::getHash(std::set<NodeId>& travNodes) const {
    if (hashOk) return nodeHashCache;
    common::WriteMsg::write(CMSG_GET_THE_NODE_HASH_OF_NODE_BEGIN,this->getId()); 
    if (travNodes.count(getId())>0) {
      common::WriteMsg::write(CMSG_GET_THE_NODE_HASH_OF_NODE_SKIP);
      return 0;
    }
    travNodes.insert(getId());
    Crc_type resultHash;
    resultHash.process_bytes( "declaration::VariableDeclarator", strlen("declaration::VariableDeclarator"));
    common::WriteMsg::write(CMSG_GET_THE_NODE_HASH_OF_NODE_END,resultHash.checksum()); 
    nodeHashCache = resultHash.checksum();
    hashOk = true;
    return nodeHashCache;
  }

  void VariableDeclarator::save(io::BinaryIO &binIo,bool withVirtualBase  /*= true*/) const {
    Positioned::save(binIo,false);

    binIo.writeUInt4(m_hasIdentifier);
    binIo.writeUInt4(m_hasInit);

  }

  void VariableDeclarator::load(io::BinaryIO &binIo, bool withVirtualBase /*= true*/) {
    Positioned::load(binIo,false);

    m_hasIdentifier =  binIo.readUInt4();
    if (m_hasIdentifier != 0)
      setParentEdge(factory->getPointer(m_hasIdentifier),edkVariableDeclarator_HasIdentifier);

    m_hasInit =  binIo.readUInt4();
    if (m_hasInit != 0)
      setParentEdge(factory->getPointer(m_hasInit),edkVariableDeclarator_HasInit);

  }


}


}}}
