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
  NamedExpr::NamedExpr(NodeId _id, Factory *_factory) :
    Expression(_id, _factory),
    m_hasTarget(0),
    m_hasValue(0)
  {
  }

  NamedExpr::~NamedExpr() {
  }

  void NamedExpr::prepareDelete(bool tryOnVirtualParent){
    removeTarget();
    removeValue();
    expression::Expression::prepareDelete(false);
  }

  NodeKind NamedExpr::getNodeKind() const {
    return ndkNamedExpr;
  }

  expression::Expression* NamedExpr::getTarget() const {
    expression::Expression *_node = NULL;
    if (m_hasTarget != 0)
      _node = dynamic_cast<expression::Expression*>(factory->getPointer(m_hasTarget));
    if ( (_node == NULL) || factory->getIsFiltered(_node))
      return NULL;

    return _node;
  }

  expression::Expression* NamedExpr::getValue() const {
    expression::Expression *_node = NULL;
    if (m_hasValue != 0)
      _node = dynamic_cast<expression::Expression*>(factory->getPointer(m_hasValue));
    if ( (_node == NULL) || factory->getIsFiltered(_node))
      return NULL;

    return _node;
  }

  bool NamedExpr::setEdge(EdgeKind edgeKind, NodeId edgeEnd, bool tryOnVirtualParent) {
    switch (edgeKind) {
      case edkNamedExpr_HasTarget:
        setTarget(edgeEnd);
        return true;
      case edkNamedExpr_HasValue:
        setValue(edgeEnd);
        return true;
      default:
        break;
    }
    if (expression::Expression::setEdge(edgeKind, edgeEnd, false)) {
      return true;
    }
    return false;
  }

  bool NamedExpr::removeEdge(EdgeKind edgeKind, NodeId edgeEnd, bool tryOnVirtualParent) {
    switch (edgeKind) {
      case edkNamedExpr_HasTarget:
        removeTarget();
        return true;
      case edkNamedExpr_HasValue:
        removeValue();
        return true;
      default:
        break;
    }
    if (expression::Expression::removeEdge(edgeKind, edgeEnd, false)) {
      return true;
    }
    return false;
  }

  void NamedExpr::setTarget(NodeId _id) {
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
          factory->reverseEdges->removeEdge(m_hasTarget, m_id, edkNamedExpr_HasTarget);
      }
      m_hasTarget = _node->getId();
      if (m_hasTarget != 0)
        setParentEdge(factory->getPointer(m_hasTarget), edkNamedExpr_HasTarget);
      if (factory->getExistsReverseEdges())
        factory->reverseEdges->insertEdge(m_hasTarget, this->getId(), edkNamedExpr_HasTarget);
    } else {
      if (m_hasTarget) {
        throw PythonException(COLUMBUS_LOCATION, CMSG_EX_CAN_T_SET_EDGE_TO_NULL);
      }
    }
  }

  void NamedExpr::setTarget(expression::Expression *_node) {
    if (_node == NULL)
      throw PythonException(COLUMBUS_LOCATION, CMSG_EX_CAN_T_SET_EDGE_TO_NULL);

    setTarget(_node->getId());
  }

  void NamedExpr::removeTarget() {
      if (m_hasTarget) {
        removeParentEdge(m_hasTarget);
        if (factory->getExistsReverseEdges())
          factory->reverseEdges->removeEdge(m_hasTarget, m_id, edkNamedExpr_HasTarget);
      }
      m_hasTarget = 0;
  }

  void NamedExpr::setValue(NodeId _id) {
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

      if (m_hasValue) {
        removeParentEdge(m_hasValue);
        if (factory->getExistsReverseEdges())
          factory->reverseEdges->removeEdge(m_hasValue, m_id, edkNamedExpr_HasValue);
      }
      m_hasValue = _node->getId();
      if (m_hasValue != 0)
        setParentEdge(factory->getPointer(m_hasValue), edkNamedExpr_HasValue);
      if (factory->getExistsReverseEdges())
        factory->reverseEdges->insertEdge(m_hasValue, this->getId(), edkNamedExpr_HasValue);
    } else {
      if (m_hasValue) {
        throw PythonException(COLUMBUS_LOCATION, CMSG_EX_CAN_T_SET_EDGE_TO_NULL);
      }
    }
  }

  void NamedExpr::setValue(expression::Expression *_node) {
    if (_node == NULL)
      throw PythonException(COLUMBUS_LOCATION, CMSG_EX_CAN_T_SET_EDGE_TO_NULL);

    setValue(_node->getId());
  }

  void NamedExpr::removeValue() {
      if (m_hasValue) {
        removeParentEdge(m_hasValue);
        if (factory->getExistsReverseEdges())
          factory->reverseEdges->removeEdge(m_hasValue, m_id, edkNamedExpr_HasValue);
      }
      m_hasValue = 0;
  }

  void NamedExpr::accept(Visitor &visitor) const {
    visitor.visit(*this);
  }

  void NamedExpr::acceptEnd(Visitor &visitor) const {
    visitor.visitEnd(*this);
  }

  double NamedExpr::getSimilarity(const base::Base& base){
    if(base.getNodeKind() == getNodeKind()) {
      return 1.0;
    } else {
      return 0.0;
    }
  }

  void NamedExpr::swapStringTable(RefDistributorStrTable& newStrTable, std::map<Key,Key>& oldAndNewStrKeyMap ){
    std::map<Key,Key>::iterator foundKeyId;

  }

  NodeHashType NamedExpr::getHash(std::set<NodeId>& travNodes) const {
    if (hashOk) return nodeHashCache;
    common::WriteMsg::write(CMSG_GET_THE_NODE_HASH_OF_NODE_BEGIN,this->getId()); 
    if (travNodes.count(getId())>0) {
      common::WriteMsg::write(CMSG_GET_THE_NODE_HASH_OF_NODE_SKIP);
      return 0;
    }
    travNodes.insert(getId());
    Crc_type resultHash;
    resultHash.process_bytes( "expression::NamedExpr", strlen("expression::NamedExpr"));
    common::WriteMsg::write(CMSG_GET_THE_NODE_HASH_OF_NODE_END,resultHash.checksum()); 
    nodeHashCache = resultHash.checksum();
    hashOk = true;
    return nodeHashCache;
  }

  void NamedExpr::save(io::BinaryIO &binIo,bool withVirtualBase  /*= true*/) const {
    Expression::save(binIo,false);

    binIo.writeUInt4(m_hasTarget);
    binIo.writeUInt4(m_hasValue);

  }

  void NamedExpr::load(io::BinaryIO &binIo, bool withVirtualBase /*= true*/) {
    Expression::load(binIo,false);

    m_hasTarget =  binIo.readUInt4();
    if (m_hasTarget != 0)
      setParentEdge(factory->getPointer(m_hasTarget),edkNamedExpr_HasTarget);

    m_hasValue =  binIo.readUInt4();
    if (m_hasValue != 0)
      setParentEdge(factory->getPointer(m_hasValue),edkNamedExpr_HasValue);

  }


}


}}}
