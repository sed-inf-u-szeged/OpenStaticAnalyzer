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

namespace expression { 
  LogicalExpression::LogicalExpression(NodeId _id, Factory *_factory) :
         Positioned(_id, _factory),
    Expression(_id, _factory),
    m_operator(looAnd),
    m_hasLeft(0),
    m_hasRight(0)
  {
  }

  LogicalExpression::~LogicalExpression() {
  }

  void LogicalExpression::prepareDelete(bool tryOnVirtualParent){
    removeLeft();
    removeRight();
    if (tryOnVirtualParent) {
      base::Positioned::prepareDelete(false);
    }
    expression::Expression::prepareDelete(false);
  }

  NodeKind LogicalExpression::getNodeKind() const {
    return ndkLogicalExpression;
  }

  LogicalOperator LogicalExpression::getOperator() const {
    return m_operator;
  }

  void LogicalExpression::setOperator(LogicalOperator _operator) {
    m_operator = _operator;
  }

  expression::Expression* LogicalExpression::getLeft() const {
    expression::Expression *_node = NULL;
    if (m_hasLeft != 0)
      _node = dynamic_cast<expression::Expression*>(factory->getPointer(m_hasLeft));
    if ( (_node == NULL) || factory->getIsFiltered(_node))
      return NULL;

    return _node;
  }

  expression::Expression* LogicalExpression::getRight() const {
    expression::Expression *_node = NULL;
    if (m_hasRight != 0)
      _node = dynamic_cast<expression::Expression*>(factory->getPointer(m_hasRight));
    if ( (_node == NULL) || factory->getIsFiltered(_node))
      return NULL;

    return _node;
  }

  bool LogicalExpression::setEdge(EdgeKind edgeKind, NodeId edgeEnd, bool tryOnVirtualParent) {
    switch (edgeKind) {
      case edkLogicalExpression_HasLeft:
        setLeft(edgeEnd);
        return true;
      case edkLogicalExpression_HasRight:
        setRight(edgeEnd);
        return true;
      default:
        break;
    }
    if (tryOnVirtualParent) {
      if (base::Positioned::setEdge(edgeKind, edgeEnd, false)) {
        return true;
      }
    }
    if (expression::Expression::setEdge(edgeKind, edgeEnd, false)) {
      return true;
    }
    return false;
  }

  bool LogicalExpression::removeEdge(EdgeKind edgeKind, NodeId edgeEnd, bool tryOnVirtualParent) {
    switch (edgeKind) {
      case edkLogicalExpression_HasLeft:
        removeLeft();
        return true;
      case edkLogicalExpression_HasRight:
        removeRight();
        return true;
      default:
        break;
    }
    if (tryOnVirtualParent) {
      if (base::Positioned::removeEdge(edgeKind, edgeEnd, false)) {
        return true;
      }
    }
    if (expression::Expression::removeEdge(edgeKind, edgeEnd, false)) {
      return true;
    }
    return false;
  }

  void LogicalExpression::setLeft(NodeId _id) {
    expression::Expression *_node = NULL;
    if (_id) {
      if (!factory->getExist(_id))
        throw JavascriptException(COLUMBUS_LOCATION, CMSG_EX_THE_END_POINT_OF_THE_EDGE_DOES_NOT_EXIST);

      _node = dynamic_cast<expression::Expression*> (factory->getPointer(_id));
      if ( _node == NULL) {
        throw JavascriptException(COLUMBUS_LOCATION, CMSG_EX_INVALID_NODE_KIND);
      }
      if (&(_node->getFactory()) != this->factory)
        throw JavascriptException(COLUMBUS_LOCATION, CMSG_EX_THE_FACTORY_OF_NODES_DOES_NOT_MATCH );

      if (m_hasLeft) {
        removeParentEdge(m_hasLeft);
        if (factory->getExistsReverseEdges())
          factory->reverseEdges->removeEdge(m_hasLeft, m_id, edkLogicalExpression_HasLeft);
      }
      m_hasLeft = _node->getId();
      if (m_hasLeft != 0)
        setParentEdge(factory->getPointer(m_hasLeft), edkLogicalExpression_HasLeft);
      if (factory->getExistsReverseEdges())
        factory->reverseEdges->insertEdge(m_hasLeft, this->getId(), edkLogicalExpression_HasLeft);
    } else {
      if (m_hasLeft) {
        throw JavascriptException(COLUMBUS_LOCATION, CMSG_EX_CAN_T_SET_EDGE_TO_NULL);
      }
    }
  }

  void LogicalExpression::setLeft(expression::Expression *_node) {
    if (_node == NULL)
      throw JavascriptException(COLUMBUS_LOCATION, CMSG_EX_CAN_T_SET_EDGE_TO_NULL);

    setLeft(_node->getId());
  }

  void LogicalExpression::removeLeft() {
      if (m_hasLeft) {
        removeParentEdge(m_hasLeft);
        if (factory->getExistsReverseEdges())
          factory->reverseEdges->removeEdge(m_hasLeft, m_id, edkLogicalExpression_HasLeft);
      }
      m_hasLeft = 0;
  }

  void LogicalExpression::setRight(NodeId _id) {
    expression::Expression *_node = NULL;
    if (_id) {
      if (!factory->getExist(_id))
        throw JavascriptException(COLUMBUS_LOCATION, CMSG_EX_THE_END_POINT_OF_THE_EDGE_DOES_NOT_EXIST);

      _node = dynamic_cast<expression::Expression*> (factory->getPointer(_id));
      if ( _node == NULL) {
        throw JavascriptException(COLUMBUS_LOCATION, CMSG_EX_INVALID_NODE_KIND);
      }
      if (&(_node->getFactory()) != this->factory)
        throw JavascriptException(COLUMBUS_LOCATION, CMSG_EX_THE_FACTORY_OF_NODES_DOES_NOT_MATCH );

      if (m_hasRight) {
        removeParentEdge(m_hasRight);
        if (factory->getExistsReverseEdges())
          factory->reverseEdges->removeEdge(m_hasRight, m_id, edkLogicalExpression_HasRight);
      }
      m_hasRight = _node->getId();
      if (m_hasRight != 0)
        setParentEdge(factory->getPointer(m_hasRight), edkLogicalExpression_HasRight);
      if (factory->getExistsReverseEdges())
        factory->reverseEdges->insertEdge(m_hasRight, this->getId(), edkLogicalExpression_HasRight);
    } else {
      if (m_hasRight) {
        throw JavascriptException(COLUMBUS_LOCATION, CMSG_EX_CAN_T_SET_EDGE_TO_NULL);
      }
    }
  }

  void LogicalExpression::setRight(expression::Expression *_node) {
    if (_node == NULL)
      throw JavascriptException(COLUMBUS_LOCATION, CMSG_EX_CAN_T_SET_EDGE_TO_NULL);

    setRight(_node->getId());
  }

  void LogicalExpression::removeRight() {
      if (m_hasRight) {
        removeParentEdge(m_hasRight);
        if (factory->getExistsReverseEdges())
          factory->reverseEdges->removeEdge(m_hasRight, m_id, edkLogicalExpression_HasRight);
      }
      m_hasRight = 0;
  }

  void LogicalExpression::accept(Visitor &visitor) const {
    visitor.visit(*this);
  }

  void LogicalExpression::acceptEnd(Visitor &visitor) const {
    visitor.visitEnd(*this);
  }

  double LogicalExpression::getSimilarity(const base::Base& base){
    if(base.getNodeKind() == getNodeKind()) {
      const LogicalExpression& node = dynamic_cast<const LogicalExpression&>(base);
      double matchAttrs = 0;
      if(node.getOperator() == getOperator()) ++matchAttrs;
      return matchAttrs / (1 / (1 - Common::SimilarityMinimum)) + Common::SimilarityMinimum;
    } else {
      return 0.0;
    }
  }

  void LogicalExpression::swapStringTable(RefDistributorStrTable& newStrTable, std::map<Key,Key>& oldAndNewStrKeyMap ){
    std::map<Key,Key>::iterator foundKeyId;

  }

  NodeHashType LogicalExpression::getHash(std::set<NodeId>& travNodes) const {
    if (hashOk) return nodeHashCache;
    common::WriteMsg::write(CMSG_GET_THE_NODE_HASH_OF_NODE_BEGIN,this->getId()); 
    if (travNodes.count(getId())>0) {
      common::WriteMsg::write(CMSG_GET_THE_NODE_HASH_OF_NODE_SKIP);
      return 0;
    }
    travNodes.insert(getId());
    Crc_type resultHash;
    resultHash.process_bytes( "expression::LogicalExpression", strlen("expression::LogicalExpression"));
    common::WriteMsg::write(CMSG_GET_THE_NODE_HASH_OF_NODE_END,resultHash.checksum()); 
    nodeHashCache = resultHash.checksum();
    hashOk = true;
    return nodeHashCache;
  }

  void LogicalExpression::save(io::BinaryIO &binIo,bool withVirtualBase  /*= true*/) const {
    if (withVirtualBase)
      Positioned::save(binIo,false);

    Expression::save(binIo,false);

    binIo.writeUByte1(m_operator);

    binIo.writeUInt4(m_hasLeft);
    binIo.writeUInt4(m_hasRight);

  }

  void LogicalExpression::load(io::BinaryIO &binIo, bool withVirtualBase /*= true*/) {
    if (withVirtualBase)
      Positioned::load(binIo, false);

    Expression::load(binIo,false);

    m_operator = (LogicalOperator)binIo.readUByte1();

    m_hasLeft =  binIo.readUInt4();
    if (m_hasLeft != 0)
      setParentEdge(factory->getPointer(m_hasLeft),edkLogicalExpression_HasLeft);

    m_hasRight =  binIo.readUInt4();
    if (m_hasRight != 0)
      setParentEdge(factory->getPointer(m_hasRight),edkLogicalExpression_HasRight);

  }


}


}}}
