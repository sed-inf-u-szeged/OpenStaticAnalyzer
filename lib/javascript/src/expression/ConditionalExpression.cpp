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
  ConditionalExpression::ConditionalExpression(NodeId _id, Factory *_factory) :
         Positioned(_id, _factory),
    Expression(_id, _factory),
    m_hasAlternate(0),
    m_hasConsequent(0),
    m_hasTest(0)
  {
  }

  ConditionalExpression::~ConditionalExpression() {
  }

  void ConditionalExpression::prepareDelete(bool tryOnVirtualParent){
    removeAlternate();
    removeConsequent();
    removeTest();
    if (tryOnVirtualParent) {
      base::Positioned::prepareDelete(false);
    }
    expression::Expression::prepareDelete(false);
  }

  NodeKind ConditionalExpression::getNodeKind() const {
    return ndkConditionalExpression;
  }

  expression::Expression* ConditionalExpression::getAlternate() const {
    expression::Expression *_node = NULL;
    if (m_hasAlternate != 0)
      _node = dynamic_cast<expression::Expression*>(factory->getPointer(m_hasAlternate));
    if ( (_node == NULL) || factory->getIsFiltered(_node))
      return NULL;

    return _node;
  }

  expression::Expression* ConditionalExpression::getConsequent() const {
    expression::Expression *_node = NULL;
    if (m_hasConsequent != 0)
      _node = dynamic_cast<expression::Expression*>(factory->getPointer(m_hasConsequent));
    if ( (_node == NULL) || factory->getIsFiltered(_node))
      return NULL;

    return _node;
  }

  expression::Expression* ConditionalExpression::getTest() const {
    expression::Expression *_node = NULL;
    if (m_hasTest != 0)
      _node = dynamic_cast<expression::Expression*>(factory->getPointer(m_hasTest));
    if ( (_node == NULL) || factory->getIsFiltered(_node))
      return NULL;

    return _node;
  }

  bool ConditionalExpression::setEdge(EdgeKind edgeKind, NodeId edgeEnd, bool tryOnVirtualParent) {
    switch (edgeKind) {
      case edkConditionalExpression_HasAlternate:
        setAlternate(edgeEnd);
        return true;
      case edkConditionalExpression_HasConsequent:
        setConsequent(edgeEnd);
        return true;
      case edkConditionalExpression_HasTest:
        setTest(edgeEnd);
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

  bool ConditionalExpression::removeEdge(EdgeKind edgeKind, NodeId edgeEnd, bool tryOnVirtualParent) {
    switch (edgeKind) {
      case edkConditionalExpression_HasAlternate:
        removeAlternate();
        return true;
      case edkConditionalExpression_HasConsequent:
        removeConsequent();
        return true;
      case edkConditionalExpression_HasTest:
        removeTest();
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

  void ConditionalExpression::setAlternate(NodeId _id) {
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

      if (m_hasAlternate) {
        removeParentEdge(m_hasAlternate);
        if (factory->getExistsReverseEdges())
          factory->reverseEdges->removeEdge(m_hasAlternate, m_id, edkConditionalExpression_HasAlternate);
      }
      m_hasAlternate = _node->getId();
      if (m_hasAlternate != 0)
        setParentEdge(factory->getPointer(m_hasAlternate), edkConditionalExpression_HasAlternate);
      if (factory->getExistsReverseEdges())
        factory->reverseEdges->insertEdge(m_hasAlternate, this->getId(), edkConditionalExpression_HasAlternate);
    } else {
      if (m_hasAlternate) {
        throw JavaScriptException(COLUMBUS_LOCATION, CMSG_EX_CAN_T_SET_EDGE_TO_NULL);
      }
    }
  }

  void ConditionalExpression::setAlternate(expression::Expression *_node) {
    if (_node == NULL)
      throw JavaScriptException(COLUMBUS_LOCATION, CMSG_EX_CAN_T_SET_EDGE_TO_NULL);

    setAlternate(_node->getId());
  }

  void ConditionalExpression::removeAlternate() {
      if (m_hasAlternate) {
        removeParentEdge(m_hasAlternate);
        if (factory->getExistsReverseEdges())
          factory->reverseEdges->removeEdge(m_hasAlternate, m_id, edkConditionalExpression_HasAlternate);
      }
      m_hasAlternate = 0;
  }

  void ConditionalExpression::setConsequent(NodeId _id) {
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

      if (m_hasConsequent) {
        removeParentEdge(m_hasConsequent);
        if (factory->getExistsReverseEdges())
          factory->reverseEdges->removeEdge(m_hasConsequent, m_id, edkConditionalExpression_HasConsequent);
      }
      m_hasConsequent = _node->getId();
      if (m_hasConsequent != 0)
        setParentEdge(factory->getPointer(m_hasConsequent), edkConditionalExpression_HasConsequent);
      if (factory->getExistsReverseEdges())
        factory->reverseEdges->insertEdge(m_hasConsequent, this->getId(), edkConditionalExpression_HasConsequent);
    } else {
      if (m_hasConsequent) {
        throw JavaScriptException(COLUMBUS_LOCATION, CMSG_EX_CAN_T_SET_EDGE_TO_NULL);
      }
    }
  }

  void ConditionalExpression::setConsequent(expression::Expression *_node) {
    if (_node == NULL)
      throw JavaScriptException(COLUMBUS_LOCATION, CMSG_EX_CAN_T_SET_EDGE_TO_NULL);

    setConsequent(_node->getId());
  }

  void ConditionalExpression::removeConsequent() {
      if (m_hasConsequent) {
        removeParentEdge(m_hasConsequent);
        if (factory->getExistsReverseEdges())
          factory->reverseEdges->removeEdge(m_hasConsequent, m_id, edkConditionalExpression_HasConsequent);
      }
      m_hasConsequent = 0;
  }

  void ConditionalExpression::setTest(NodeId _id) {
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

      if (m_hasTest) {
        removeParentEdge(m_hasTest);
        if (factory->getExistsReverseEdges())
          factory->reverseEdges->removeEdge(m_hasTest, m_id, edkConditionalExpression_HasTest);
      }
      m_hasTest = _node->getId();
      if (m_hasTest != 0)
        setParentEdge(factory->getPointer(m_hasTest), edkConditionalExpression_HasTest);
      if (factory->getExistsReverseEdges())
        factory->reverseEdges->insertEdge(m_hasTest, this->getId(), edkConditionalExpression_HasTest);
    } else {
      if (m_hasTest) {
        throw JavaScriptException(COLUMBUS_LOCATION, CMSG_EX_CAN_T_SET_EDGE_TO_NULL);
      }
    }
  }

  void ConditionalExpression::setTest(expression::Expression *_node) {
    if (_node == NULL)
      throw JavaScriptException(COLUMBUS_LOCATION, CMSG_EX_CAN_T_SET_EDGE_TO_NULL);

    setTest(_node->getId());
  }

  void ConditionalExpression::removeTest() {
      if (m_hasTest) {
        removeParentEdge(m_hasTest);
        if (factory->getExistsReverseEdges())
          factory->reverseEdges->removeEdge(m_hasTest, m_id, edkConditionalExpression_HasTest);
      }
      m_hasTest = 0;
  }

  void ConditionalExpression::accept(Visitor &visitor) const {
    visitor.visit(*this);
  }

  void ConditionalExpression::acceptEnd(Visitor &visitor) const {
    visitor.visitEnd(*this);
  }

  double ConditionalExpression::getSimilarity(const base::Base& base){
    if(base.getNodeKind() == getNodeKind()) {
      return 1.0;
    } else {
      return 0.0;
    }
  }

  void ConditionalExpression::swapStringTable(RefDistributorStrTable& newStrTable, std::map<Key,Key>& oldAndNewStrKeyMap ){
    std::map<Key,Key>::iterator foundKeyId;

  }

  NodeHashType ConditionalExpression::getHash(std::set<NodeId>& travNodes) const {
    if (hashOk) return nodeHashCache;
    common::WriteMsg::write(CMSG_GET_THE_NODE_HASH_OF_NODE_BEGIN,this->getId()); 
    if (travNodes.count(getId())>0) {
      common::WriteMsg::write(CMSG_GET_THE_NODE_HASH_OF_NODE_SKIP);
      return 0;
    }
    travNodes.insert(getId());
    Crc_type resultHash;
    resultHash.process_bytes( "expression::ConditionalExpression", strlen("expression::ConditionalExpression"));
    common::WriteMsg::write(CMSG_GET_THE_NODE_HASH_OF_NODE_END,resultHash.checksum()); 
    nodeHashCache = resultHash.checksum();
    hashOk = true;
    return nodeHashCache;
  }

  void ConditionalExpression::save(io::BinaryIO &binIo,bool withVirtualBase  /*= true*/) const {
    if (withVirtualBase)
      Positioned::save(binIo,false);

    Expression::save(binIo,false);

    binIo.writeUInt4(m_hasAlternate);
    binIo.writeUInt4(m_hasConsequent);
    binIo.writeUInt4(m_hasTest);

  }

  void ConditionalExpression::load(io::BinaryIO &binIo, bool withVirtualBase /*= true*/) {
    if (withVirtualBase)
      Positioned::load(binIo, false);

    Expression::load(binIo,false);

    m_hasAlternate =  binIo.readUInt4();
    if (m_hasAlternate != 0)
      setParentEdge(factory->getPointer(m_hasAlternate),edkConditionalExpression_HasAlternate);

    m_hasConsequent =  binIo.readUInt4();
    if (m_hasConsequent != 0)
      setParentEdge(factory->getPointer(m_hasConsequent),edkConditionalExpression_HasConsequent);

    m_hasTest =  binIo.readUInt4();
    if (m_hasTest != 0)
      setParentEdge(factory->getPointer(m_hasTest),edkConditionalExpression_HasTest);

  }


}


}}}
