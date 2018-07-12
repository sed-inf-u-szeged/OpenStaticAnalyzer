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

namespace statement { 
  TryStatement::TryStatement(NodeId _id, Factory *_factory) :
         Positioned(_id, _factory),
    Statement(_id, _factory),
    m_hasBlock(0),
    m_hasFinalizer(0),
    m_hasHandler(0)
  {
  }

  TryStatement::~TryStatement() {
  }

  void TryStatement::prepareDelete(bool tryOnVirtualParent){
    removeBlock();
    removeFinalizer();
    removeHandler();
    if (tryOnVirtualParent) {
      base::Positioned::prepareDelete(false);
    }
    statement::Statement::prepareDelete(false);
  }

  NodeKind TryStatement::getNodeKind() const {
    return ndkTryStatement;
  }

  statement::BlockStatement* TryStatement::getBlock() const {
    statement::BlockStatement *_node = NULL;
    if (m_hasBlock != 0)
      _node = dynamic_cast<statement::BlockStatement*>(factory->getPointer(m_hasBlock));
    if ( (_node == NULL) || factory->getIsFiltered(_node))
      return NULL;

    return _node;
  }

  statement::BlockStatement* TryStatement::getFinalizer() const {
    statement::BlockStatement *_node = NULL;
    if (m_hasFinalizer != 0)
      _node = dynamic_cast<statement::BlockStatement*>(factory->getPointer(m_hasFinalizer));
    if ( (_node == NULL) || factory->getIsFiltered(_node))
      return NULL;

    return _node;
  }

  statement::CatchClause* TryStatement::getHandler() const {
    statement::CatchClause *_node = NULL;
    if (m_hasHandler != 0)
      _node = dynamic_cast<statement::CatchClause*>(factory->getPointer(m_hasHandler));
    if ( (_node == NULL) || factory->getIsFiltered(_node))
      return NULL;

    return _node;
  }

  bool TryStatement::setEdge(EdgeKind edgeKind, NodeId edgeEnd, bool tryOnVirtualParent) {
    switch (edgeKind) {
      case edkTryStatement_HasBlock:
        setBlock(edgeEnd);
        return true;
      case edkTryStatement_HasFinalizer:
        setFinalizer(edgeEnd);
        return true;
      case edkTryStatement_HasHandler:
        setHandler(edgeEnd);
        return true;
      default:
        break;
    }
    if (tryOnVirtualParent) {
      if (base::Positioned::setEdge(edgeKind, edgeEnd, false)) {
        return true;
      }
    }
    if (statement::Statement::setEdge(edgeKind, edgeEnd, false)) {
      return true;
    }
    return false;
  }

  bool TryStatement::removeEdge(EdgeKind edgeKind, NodeId edgeEnd, bool tryOnVirtualParent) {
    switch (edgeKind) {
      case edkTryStatement_HasBlock:
        removeBlock();
        return true;
      case edkTryStatement_HasFinalizer:
        removeFinalizer();
        return true;
      case edkTryStatement_HasHandler:
        removeHandler();
        return true;
      default:
        break;
    }
    if (tryOnVirtualParent) {
      if (base::Positioned::removeEdge(edgeKind, edgeEnd, false)) {
        return true;
      }
    }
    if (statement::Statement::removeEdge(edgeKind, edgeEnd, false)) {
      return true;
    }
    return false;
  }

  void TryStatement::setBlock(NodeId _id) {
    statement::BlockStatement *_node = NULL;
    if (_id) {
      if (!factory->getExist(_id))
        throw JavaScriptException(COLUMBUS_LOCATION, CMSG_EX_THE_END_POINT_OF_THE_EDGE_DOES_NOT_EXIST);

      _node = dynamic_cast<statement::BlockStatement*> (factory->getPointer(_id));
      if ( _node == NULL) {
        throw JavaScriptException(COLUMBUS_LOCATION, CMSG_EX_INVALID_NODE_KIND);
      }
      if (&(_node->getFactory()) != this->factory)
        throw JavaScriptException(COLUMBUS_LOCATION, CMSG_EX_THE_FACTORY_OF_NODES_DOES_NOT_MATCH );

      if (m_hasBlock) {
        removeParentEdge(m_hasBlock);
        if (factory->getExistsReverseEdges())
          factory->reverseEdges->removeEdge(m_hasBlock, m_id, edkTryStatement_HasBlock);
      }
      m_hasBlock = _node->getId();
      if (m_hasBlock != 0)
        setParentEdge(factory->getPointer(m_hasBlock), edkTryStatement_HasBlock);
      if (factory->getExistsReverseEdges())
        factory->reverseEdges->insertEdge(m_hasBlock, this->getId(), edkTryStatement_HasBlock);
    } else {
      if (m_hasBlock) {
        throw JavaScriptException(COLUMBUS_LOCATION, CMSG_EX_CAN_T_SET_EDGE_TO_NULL);
      }
    }
  }

  void TryStatement::setBlock(statement::BlockStatement *_node) {
    if (_node == NULL)
      throw JavaScriptException(COLUMBUS_LOCATION, CMSG_EX_CAN_T_SET_EDGE_TO_NULL);

    setBlock(_node->getId());
  }

  void TryStatement::removeBlock() {
      if (m_hasBlock) {
        removeParentEdge(m_hasBlock);
        if (factory->getExistsReverseEdges())
          factory->reverseEdges->removeEdge(m_hasBlock, m_id, edkTryStatement_HasBlock);
      }
      m_hasBlock = 0;
  }

  void TryStatement::setFinalizer(NodeId _id) {
    statement::BlockStatement *_node = NULL;
    if (_id) {
      if (!factory->getExist(_id))
        throw JavaScriptException(COLUMBUS_LOCATION, CMSG_EX_THE_END_POINT_OF_THE_EDGE_DOES_NOT_EXIST);

      _node = dynamic_cast<statement::BlockStatement*> (factory->getPointer(_id));
      if ( _node == NULL) {
        throw JavaScriptException(COLUMBUS_LOCATION, CMSG_EX_INVALID_NODE_KIND);
      }
      if (&(_node->getFactory()) != this->factory)
        throw JavaScriptException(COLUMBUS_LOCATION, CMSG_EX_THE_FACTORY_OF_NODES_DOES_NOT_MATCH );

      if (m_hasFinalizer) {
        removeParentEdge(m_hasFinalizer);
        if (factory->getExistsReverseEdges())
          factory->reverseEdges->removeEdge(m_hasFinalizer, m_id, edkTryStatement_HasFinalizer);
      }
      m_hasFinalizer = _node->getId();
      if (m_hasFinalizer != 0)
        setParentEdge(factory->getPointer(m_hasFinalizer), edkTryStatement_HasFinalizer);
      if (factory->getExistsReverseEdges())
        factory->reverseEdges->insertEdge(m_hasFinalizer, this->getId(), edkTryStatement_HasFinalizer);
    } else {
      if (m_hasFinalizer) {
        throw JavaScriptException(COLUMBUS_LOCATION, CMSG_EX_CAN_T_SET_EDGE_TO_NULL);
      }
    }
  }

  void TryStatement::setFinalizer(statement::BlockStatement *_node) {
    if (_node == NULL)
      throw JavaScriptException(COLUMBUS_LOCATION, CMSG_EX_CAN_T_SET_EDGE_TO_NULL);

    setFinalizer(_node->getId());
  }

  void TryStatement::removeFinalizer() {
      if (m_hasFinalizer) {
        removeParentEdge(m_hasFinalizer);
        if (factory->getExistsReverseEdges())
          factory->reverseEdges->removeEdge(m_hasFinalizer, m_id, edkTryStatement_HasFinalizer);
      }
      m_hasFinalizer = 0;
  }

  void TryStatement::setHandler(NodeId _id) {
    statement::CatchClause *_node = NULL;
    if (_id) {
      if (!factory->getExist(_id))
        throw JavaScriptException(COLUMBUS_LOCATION, CMSG_EX_THE_END_POINT_OF_THE_EDGE_DOES_NOT_EXIST);

      _node = dynamic_cast<statement::CatchClause*> (factory->getPointer(_id));
      if ( _node == NULL) {
        throw JavaScriptException(COLUMBUS_LOCATION, CMSG_EX_INVALID_NODE_KIND);
      }
      if (&(_node->getFactory()) != this->factory)
        throw JavaScriptException(COLUMBUS_LOCATION, CMSG_EX_THE_FACTORY_OF_NODES_DOES_NOT_MATCH );

      if (m_hasHandler) {
        removeParentEdge(m_hasHandler);
        if (factory->getExistsReverseEdges())
          factory->reverseEdges->removeEdge(m_hasHandler, m_id, edkTryStatement_HasHandler);
      }
      m_hasHandler = _node->getId();
      if (m_hasHandler != 0)
        setParentEdge(factory->getPointer(m_hasHandler), edkTryStatement_HasHandler);
      if (factory->getExistsReverseEdges())
        factory->reverseEdges->insertEdge(m_hasHandler, this->getId(), edkTryStatement_HasHandler);
    } else {
      if (m_hasHandler) {
        throw JavaScriptException(COLUMBUS_LOCATION, CMSG_EX_CAN_T_SET_EDGE_TO_NULL);
      }
    }
  }

  void TryStatement::setHandler(statement::CatchClause *_node) {
    if (_node == NULL)
      throw JavaScriptException(COLUMBUS_LOCATION, CMSG_EX_CAN_T_SET_EDGE_TO_NULL);

    setHandler(_node->getId());
  }

  void TryStatement::removeHandler() {
      if (m_hasHandler) {
        removeParentEdge(m_hasHandler);
        if (factory->getExistsReverseEdges())
          factory->reverseEdges->removeEdge(m_hasHandler, m_id, edkTryStatement_HasHandler);
      }
      m_hasHandler = 0;
  }

  void TryStatement::accept(Visitor &visitor) const {
    visitor.visit(*this);
  }

  void TryStatement::acceptEnd(Visitor &visitor) const {
    visitor.visitEnd(*this);
  }

  double TryStatement::getSimilarity(const base::Base& base){
    if(base.getNodeKind() == getNodeKind()) {
      return 1.0;
    } else {
      return 0.0;
    }
  }

  void TryStatement::swapStringTable(RefDistributorStrTable& newStrTable, std::map<Key,Key>& oldAndNewStrKeyMap ){
    std::map<Key,Key>::iterator foundKeyId;

  }

  NodeHashType TryStatement::getHash(std::set<NodeId>& travNodes) const {
    if (hashOk) return nodeHashCache;
    common::WriteMsg::write(CMSG_GET_THE_NODE_HASH_OF_NODE_BEGIN,this->getId()); 
    if (travNodes.count(getId())>0) {
      common::WriteMsg::write(CMSG_GET_THE_NODE_HASH_OF_NODE_SKIP);
      return 0;
    }
    travNodes.insert(getId());
    Crc_type resultHash;
    resultHash.process_bytes( "statement::TryStatement", strlen("statement::TryStatement"));
    common::WriteMsg::write(CMSG_GET_THE_NODE_HASH_OF_NODE_END,resultHash.checksum()); 
    nodeHashCache = resultHash.checksum();
    hashOk = true;
    return nodeHashCache;
  }

  void TryStatement::save(io::BinaryIO &binIo,bool withVirtualBase  /*= true*/) const {
    if (withVirtualBase)
      Positioned::save(binIo,false);

    Statement::save(binIo,false);

    binIo.writeUInt4(m_hasBlock);
    binIo.writeUInt4(m_hasFinalizer);
    binIo.writeUInt4(m_hasHandler);

  }

  void TryStatement::load(io::BinaryIO &binIo, bool withVirtualBase /*= true*/) {
    if (withVirtualBase)
      Positioned::load(binIo, false);

    Statement::load(binIo,false);

    m_hasBlock =  binIo.readUInt4();
    if (m_hasBlock != 0)
      setParentEdge(factory->getPointer(m_hasBlock),edkTryStatement_HasBlock);

    m_hasFinalizer =  binIo.readUInt4();
    if (m_hasFinalizer != 0)
      setParentEdge(factory->getPointer(m_hasFinalizer),edkTryStatement_HasFinalizer);

    m_hasHandler =  binIo.readUInt4();
    if (m_hasHandler != 0)
      setParentEdge(factory->getPointer(m_hasHandler),edkTryStatement_HasHandler);

  }


}


}}}
