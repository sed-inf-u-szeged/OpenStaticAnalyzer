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
  WithItem::WithItem(NodeId _id, Factory *_factory) :
    Positioned(_id, _factory),
    m_hasContext(0),
    m_hasTarget(0)
  {
  }

  WithItem::~WithItem() {
  }

  void WithItem::prepareDelete(bool tryOnVirtualParent){
    removeContext();
    removeTarget();
    base::Positioned::prepareDelete(false);
  }

  NodeKind WithItem::getNodeKind() const {
    return ndkWithItem;
  }

  expression::Expression* WithItem::getContext() const {
    expression::Expression *_node = NULL;
    if (m_hasContext != 0)
      _node = dynamic_cast<expression::Expression*>(factory->getPointer(m_hasContext));
    if ( (_node == NULL) || factory->getIsFiltered(_node))
      return NULL;

    return _node;
  }

  expression::Expression* WithItem::getTarget() const {
    expression::Expression *_node = NULL;
    if (m_hasTarget != 0)
      _node = dynamic_cast<expression::Expression*>(factory->getPointer(m_hasTarget));
    if ( (_node == NULL) || factory->getIsFiltered(_node))
      return NULL;

    return _node;
  }

  bool WithItem::setEdge(EdgeKind edgeKind, NodeId edgeEnd, bool tryOnVirtualParent) {
    switch (edgeKind) {
      case edkWithItem_HasContext:
        setContext(edgeEnd);
        return true;
      case edkWithItem_HasTarget:
        setTarget(edgeEnd);
        return true;
      default:
        break;
    }
    if (base::Positioned::setEdge(edgeKind, edgeEnd, false)) {
      return true;
    }
    return false;
  }

  bool WithItem::removeEdge(EdgeKind edgeKind, NodeId edgeEnd, bool tryOnVirtualParent) {
    switch (edgeKind) {
      case edkWithItem_HasContext:
        removeContext();
        return true;
      case edkWithItem_HasTarget:
        removeTarget();
        return true;
      default:
        break;
    }
    if (base::Positioned::removeEdge(edgeKind, edgeEnd, false)) {
      return true;
    }
    return false;
  }

  void WithItem::setContext(NodeId _id) {
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

      if (m_hasContext) {
        removeParentEdge(m_hasContext);
        if (factory->getExistsReverseEdges())
          factory->reverseEdges->removeEdge(m_hasContext, m_id, edkWithItem_HasContext);
      }
      m_hasContext = _node->getId();
      if (m_hasContext != 0)
        setParentEdge(factory->getPointer(m_hasContext), edkWithItem_HasContext);
      if (factory->getExistsReverseEdges())
        factory->reverseEdges->insertEdge(m_hasContext, this->getId(), edkWithItem_HasContext);
    } else {
      if (m_hasContext) {
        throw PythonException(COLUMBUS_LOCATION, CMSG_EX_CAN_T_SET_EDGE_TO_NULL);
      }
    }
  }

  void WithItem::setContext(expression::Expression *_node) {
    if (_node == NULL)
      throw PythonException(COLUMBUS_LOCATION, CMSG_EX_CAN_T_SET_EDGE_TO_NULL);

    setContext(_node->getId());
  }

  void WithItem::removeContext() {
      if (m_hasContext) {
        removeParentEdge(m_hasContext);
        if (factory->getExistsReverseEdges())
          factory->reverseEdges->removeEdge(m_hasContext, m_id, edkWithItem_HasContext);
      }
      m_hasContext = 0;
  }

  void WithItem::setTarget(NodeId _id) {
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

      if (m_hasTarget) {
        removeParentEdge(m_hasTarget);
        if (factory->getExistsReverseEdges())
          factory->reverseEdges->removeEdge(m_hasTarget, m_id, edkWithItem_HasTarget);
      }
      m_hasTarget = _node->getId();
      if (m_hasTarget != 0)
        setParentEdge(factory->getPointer(m_hasTarget), edkWithItem_HasTarget);
      if (factory->getExistsReverseEdges())
        factory->reverseEdges->insertEdge(m_hasTarget, this->getId(), edkWithItem_HasTarget);
    } else {
      if (m_hasTarget) {
        throw PythonException(COLUMBUS_LOCATION, CMSG_EX_CAN_T_SET_EDGE_TO_NULL);
      }
    }
  }

  void WithItem::setTarget(expression::Expression *_node) {
    if (_node == NULL)
      throw PythonException(COLUMBUS_LOCATION, CMSG_EX_CAN_T_SET_EDGE_TO_NULL);

    setTarget(_node->getId());
  }

  void WithItem::removeTarget() {
      if (m_hasTarget) {
        removeParentEdge(m_hasTarget);
        if (factory->getExistsReverseEdges())
          factory->reverseEdges->removeEdge(m_hasTarget, m_id, edkWithItem_HasTarget);
      }
      m_hasTarget = 0;
  }

  void WithItem::accept(Visitor &visitor) const {
    visitor.visit(*this);
  }

  void WithItem::acceptEnd(Visitor &visitor) const {
    visitor.visitEnd(*this);
  }

  double WithItem::getSimilarity(const base::Base& base){
    if(base.getNodeKind() == getNodeKind()) {
      return 1.0;
    } else {
      return 0.0;
    }
  }

  void WithItem::swapStringTable(RefDistributorStrTable& newStrTable, std::map<Key,Key>& oldAndNewStrKeyMap ){
    std::map<Key,Key>::iterator foundKeyId;

  }

  NodeHashType WithItem::getHash(std::set<NodeId>& travNodes) const {
    if (hashOk) return nodeHashCache;
    common::WriteMsg::write(CMSG_GET_THE_NODE_HASH_OF_NODE_BEGIN,this->getId()); 
    if (travNodes.count(getId())>0) {
      common::WriteMsg::write(CMSG_GET_THE_NODE_HASH_OF_NODE_SKIP);
      return 0;
    }
    travNodes.insert(getId());
    Crc_type resultHash;
    resultHash.process_bytes( "statement::WithItem", strlen("statement::WithItem"));
    common::WriteMsg::write(CMSG_GET_THE_NODE_HASH_OF_NODE_END,resultHash.checksum()); 
    nodeHashCache = resultHash.checksum();
    hashOk = true;
    return nodeHashCache;
  }

  void WithItem::save(io::BinaryIO &binIo,bool withVirtualBase  /*= true*/) const {
    Positioned::save(binIo,false);

    binIo.writeUInt4(m_hasContext);
    binIo.writeUInt4(m_hasTarget);

  }

  void WithItem::load(io::BinaryIO &binIo, bool withVirtualBase /*= true*/) {
    Positioned::load(binIo,false);

    m_hasContext =  binIo.readUInt4();
    if (m_hasContext != 0)
      setParentEdge(factory->getPointer(m_hasContext),edkWithItem_HasContext);

    m_hasTarget =  binIo.readUInt4();
    if (m_hasTarget != 0)
      setParentEdge(factory->getPointer(m_hasTarget),edkWithItem_HasTarget);

  }


}


}}}
