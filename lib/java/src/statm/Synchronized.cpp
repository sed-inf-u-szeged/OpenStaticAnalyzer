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

#include "java/inc/java.h"
#include "java/inc/Common.h"
#include "common/inc/WriteMessage.h"

#include "java/inc/messages.h"
#include <algorithm>
#include <string.h>
#include "common/inc/math/common.h"
#include <sstream>


namespace columbus { namespace java { namespace asg {

typedef boost::crc_32_type  Crc_type;

namespace statm { 
  Synchronized::Synchronized(NodeId _id, Factory *_factory) :
         Base(_id, _factory),
         Commentable(_id, _factory),
    Statement(_id, _factory),
    m_hasLock(0),
    m_hasBlock(0)
  {
  }

  Synchronized::~Synchronized() {
  }

  void Synchronized::clone(const Synchronized& other, bool tryOnVirtualParent) {
    if (tryOnVirtualParent) {
      base::Base::clone(other, false);
    }
    if (tryOnVirtualParent) {
      base::Commentable::clone(other, false);
    }
    statm::Statement::clone(other, false);

    m_hasLock = other.m_hasLock;
    m_hasBlock = other.m_hasBlock;
  }

  void Synchronized::prepareDelete(bool tryOnVirtualParent){
    removeLock();
    removeBlock();
    if (tryOnVirtualParent) {
      base::Base::prepareDelete(false);
    }
    if (tryOnVirtualParent) {
      base::Commentable::prepareDelete(false);
    }
    statm::Statement::prepareDelete(false);
  }

  NodeKind Synchronized::getNodeKind() const {
    return ndkSynchronized;
  }

  expr::Expression* Synchronized::getLock() const {
    expr::Expression *_node = NULL;
    if (m_hasLock != 0)
      _node = dynamic_cast<expr::Expression*>(factory->getPointer(m_hasLock));
    if ( (_node == NULL) || factory->getIsFiltered(_node))
      return NULL;

    return _node;
  }

  statm::Block* Synchronized::getBlock() const {
    statm::Block *_node = NULL;
    if (m_hasBlock != 0)
      _node = dynamic_cast<statm::Block*>(factory->getPointer(m_hasBlock));
    if ( (_node == NULL) || factory->getIsFiltered(_node))
      return NULL;

    return _node;
  }

  bool Synchronized::setEdge(EdgeKind edgeKind, NodeId edgeEnd, bool tryOnVirtualParent) {
    switch (edgeKind) {
      case edkSynchronized_HasLock:
        setLock(edgeEnd);
        return true;
      case edkSynchronized_HasBlock:
        setBlock(edgeEnd);
        return true;
      default:
        break;
    }
    if (tryOnVirtualParent) {
      if (base::Base::setEdge(edgeKind, edgeEnd, false)) {
        return true;
      }
    }
    if (tryOnVirtualParent) {
      if (base::Commentable::setEdge(edgeKind, edgeEnd, false)) {
        return true;
      }
    }
    if (statm::Statement::setEdge(edgeKind, edgeEnd, false)) {
      return true;
    }
    return false;
  }

  bool Synchronized::removeEdge(EdgeKind edgeKind, NodeId edgeEnd, bool tryOnVirtualParent) {
    switch (edgeKind) {
      case edkSynchronized_HasLock:
        removeLock();
        return true;
      case edkSynchronized_HasBlock:
        removeBlock();
        return true;
      default:
        break;
    }
    if (tryOnVirtualParent) {
      if (base::Base::removeEdge(edgeKind, edgeEnd, false)) {
        return true;
      }
    }
    if (tryOnVirtualParent) {
      if (base::Commentable::removeEdge(edgeKind, edgeEnd, false)) {
        return true;
      }
    }
    if (statm::Statement::removeEdge(edgeKind, edgeEnd, false)) {
      return true;
    }
    return false;
  }

  void Synchronized::setLock(NodeId _id) {
    expr::Expression *_node = NULL;
    if (_id) {
      if (!factory->getExist(_id))
        throw JavaException(COLUMBUS_LOCATION, CMSG_EX_THE_END_POINT_OF_THE_EDGE_DOES_NOT_EXIST);

      _node = dynamic_cast<expr::Expression*> (factory->getPointer(_id));
      if ( _node == NULL) {
        throw JavaException(COLUMBUS_LOCATION, CMSG_EX_INVALID_NODE_KIND);
      }
      if (&(_node->getFactory()) != this->factory)
        throw JavaException(COLUMBUS_LOCATION, CMSG_EX_THE_FACTORY_OF_NODES_DOES_NOT_MATCH );

      if (m_hasLock) {
        removeParentEdge(m_hasLock);
        if (factory->getExistsReverseEdges())
          factory->reverseEdges->removeEdge(m_hasLock, m_id, edkSynchronized_HasLock);
      }
      m_hasLock = _node->getId();
      if (m_hasLock != 0)
        setParentEdge(factory->getPointer(m_hasLock), edkSynchronized_HasLock);
      if (factory->getExistsReverseEdges())
        factory->reverseEdges->insertEdge(m_hasLock, this->getId(), edkSynchronized_HasLock);
    } else {
      if (m_hasLock) {
        throw JavaException(COLUMBUS_LOCATION, CMSG_EX_CAN_T_SET_EDGE_TO_NULL);
      }
    }
  }

  void Synchronized::setLock(expr::Expression *_node) {
    if (_node == NULL)
      throw JavaException(COLUMBUS_LOCATION, CMSG_EX_CAN_T_SET_EDGE_TO_NULL);

    setLock(_node->getId());
  }

  void Synchronized::removeLock() {
      if (m_hasLock) {
        removeParentEdge(m_hasLock);
        if (factory->getExistsReverseEdges())
          factory->reverseEdges->removeEdge(m_hasLock, m_id, edkSynchronized_HasLock);
      }
      m_hasLock = 0;
  }

  void Synchronized::setBlock(NodeId _id) {
    statm::Block *_node = NULL;
    if (_id) {
      if (!factory->getExist(_id))
        throw JavaException(COLUMBUS_LOCATION, CMSG_EX_THE_END_POINT_OF_THE_EDGE_DOES_NOT_EXIST);

      _node = dynamic_cast<statm::Block*> (factory->getPointer(_id));
      if ( _node == NULL) {
        throw JavaException(COLUMBUS_LOCATION, CMSG_EX_INVALID_NODE_KIND);
      }
      if (&(_node->getFactory()) != this->factory)
        throw JavaException(COLUMBUS_LOCATION, CMSG_EX_THE_FACTORY_OF_NODES_DOES_NOT_MATCH );

      if (m_hasBlock) {
        removeParentEdge(m_hasBlock);
        if (factory->getExistsReverseEdges())
          factory->reverseEdges->removeEdge(m_hasBlock, m_id, edkSynchronized_HasBlock);
      }
      m_hasBlock = _node->getId();
      if (m_hasBlock != 0)
        setParentEdge(factory->getPointer(m_hasBlock), edkSynchronized_HasBlock);
      if (factory->getExistsReverseEdges())
        factory->reverseEdges->insertEdge(m_hasBlock, this->getId(), edkSynchronized_HasBlock);
    } else {
      if (m_hasBlock) {
        throw JavaException(COLUMBUS_LOCATION, CMSG_EX_CAN_T_SET_EDGE_TO_NULL);
      }
    }
  }

  void Synchronized::setBlock(statm::Block *_node) {
    if (_node == NULL)
      throw JavaException(COLUMBUS_LOCATION, CMSG_EX_CAN_T_SET_EDGE_TO_NULL);

    setBlock(_node->getId());
  }

  void Synchronized::removeBlock() {
      if (m_hasBlock) {
        removeParentEdge(m_hasBlock);
        if (factory->getExistsReverseEdges())
          factory->reverseEdges->removeEdge(m_hasBlock, m_id, edkSynchronized_HasBlock);
      }
      m_hasBlock = 0;
  }

  void Synchronized::accept(Visitor &visitor) const {
    visitor.visit(*this);
  }

  void Synchronized::acceptEnd(Visitor &visitor) const {
    visitor.visitEnd(*this);
  }

  double Synchronized::getSimilarity(const base::Base& base){
    if(base.getNodeKind() == getNodeKind()) {
      const Synchronized& node = dynamic_cast<const Synchronized&>(base);
      double matchAttrs = 0;
      if(node.getIsCompilerGenerated() == getIsCompilerGenerated()) ++matchAttrs;
      if(node.getIsToolGenerated() == getIsToolGenerated()) ++matchAttrs;
      return matchAttrs / (2 / (1 - Common::SimilarityMinimum)) + Common::SimilarityMinimum;
    } else {
      return 0.0;
    }
  }

  void Synchronized::swapStringTable(RefDistributorStrTable& newStrTable, std::map<Key,Key>& oldAndNewStrKeyMap ){
    std::map<Key,Key>::iterator foundKeyId;

  }

  NodeHashType Synchronized::getHash(std::set<NodeId>& travNodes) const {
    if (hashOk) return nodeHashCache;
    common::WriteMsg::write(CMSG_GET_THE_NODE_HASH_OF_NODE_BEGIN,this->getId()); 
    if (travNodes.count(getId())>0) {
      common::WriteMsg::write(CMSG_GET_THE_NODE_HASH_OF_NODE_SKIP);
      return 0;
    }
    travNodes.insert(getId());
    Crc_type resultHash;
    resultHash.process_bytes( "statm::Synchronized", strlen("statm::Synchronized"));
    common::WriteMsg::write(CMSG_GET_THE_NODE_HASH_OF_NODE_END,resultHash.checksum()); 
    nodeHashCache = resultHash.checksum();
    hashOk = true;
    return nodeHashCache;
  }

  void Synchronized::sort(bool withVirtualBase /* = true */) {
    if (withVirtualBase)
      Base::sort(false);
    if (withVirtualBase)
      Commentable::sort(false);
    Statement::sort(false);
  }

  void Synchronized::save(io::BinaryIO &binIo,bool withVirtualBase  /*= true*/) const {
    if (withVirtualBase)
      Base::save(binIo,false);

    if (withVirtualBase)
      Commentable::save(binIo,false);

    Statement::save(binIo,false);

    binIo.writeUInt4(m_hasLock);
    binIo.writeUInt4(m_hasBlock);

  }

  void Synchronized::load(io::BinaryIO &binIo, bool withVirtualBase /*= true*/) {
    if (withVirtualBase)
      Base::load(binIo, false);

    if (withVirtualBase)
      Commentable::load(binIo, false);

    Statement::load(binIo,false);

    m_hasLock =  binIo.readUInt4();
    if (m_hasLock != 0)
      setParentEdge(factory->getPointer(m_hasLock),edkSynchronized_HasLock);

    m_hasBlock =  binIo.readUInt4();
    if (m_hasBlock != 0)
      setParentEdge(factory->getPointer(m_hasBlock),edkSynchronized_HasBlock);

  }


}


}}}
