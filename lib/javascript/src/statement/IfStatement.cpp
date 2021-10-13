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
  IfStatement::IfStatement(NodeId _id, Factory *_factory) :
         Positioned(_id, _factory),
    Statement(_id, _factory),
    m_hasTest(0),
    m_hasConsequent(0),
    m_hasAlternate(0)
  {
  }

  IfStatement::~IfStatement() {
  }

  void IfStatement::prepareDelete(bool tryOnVirtualParent){
    removeTest();
    removeConsequent();
    removeAlternate();
    if (tryOnVirtualParent) {
      base::Positioned::prepareDelete(false);
    }
    statement::Statement::prepareDelete(false);
  }

  NodeKind IfStatement::getNodeKind() const {
    return ndkIfStatement;
  }

  expression::Expression* IfStatement::getTest() const {
    expression::Expression *_node = NULL;
    if (m_hasTest != 0)
      _node = dynamic_cast<expression::Expression*>(factory->getPointer(m_hasTest));
    if ( (_node == NULL) || factory->getIsFiltered(_node))
      return NULL;

    return _node;
  }

  statement::Statement* IfStatement::getConsequent() const {
    statement::Statement *_node = NULL;
    if (m_hasConsequent != 0)
      _node = dynamic_cast<statement::Statement*>(factory->getPointer(m_hasConsequent));
    if ( (_node == NULL) || factory->getIsFiltered(_node))
      return NULL;

    return _node;
  }

  statement::Statement* IfStatement::getAlternate() const {
    statement::Statement *_node = NULL;
    if (m_hasAlternate != 0)
      _node = dynamic_cast<statement::Statement*>(factory->getPointer(m_hasAlternate));
    if ( (_node == NULL) || factory->getIsFiltered(_node))
      return NULL;

    return _node;
  }

  bool IfStatement::setEdge(EdgeKind edgeKind, NodeId edgeEnd, bool tryOnVirtualParent) {
    switch (edgeKind) {
      case edkIfStatement_HasTest:
        setTest(edgeEnd);
        return true;
      case edkIfStatement_HasConsequent:
        setConsequent(edgeEnd);
        return true;
      case edkIfStatement_HasAlternate:
        setAlternate(edgeEnd);
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

  bool IfStatement::removeEdge(EdgeKind edgeKind, NodeId edgeEnd, bool tryOnVirtualParent) {
    switch (edgeKind) {
      case edkIfStatement_HasTest:
        removeTest();
        return true;
      case edkIfStatement_HasConsequent:
        removeConsequent();
        return true;
      case edkIfStatement_HasAlternate:
        removeAlternate();
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

  void IfStatement::setTest(NodeId _id) {
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

      if (m_hasTest) {
        removeParentEdge(m_hasTest);
        if (factory->getExistsReverseEdges())
          factory->reverseEdges->removeEdge(m_hasTest, m_id, edkIfStatement_HasTest);
      }
      m_hasTest = _node->getId();
      if (m_hasTest != 0)
        setParentEdge(factory->getPointer(m_hasTest), edkIfStatement_HasTest);
      if (factory->getExistsReverseEdges())
        factory->reverseEdges->insertEdge(m_hasTest, this->getId(), edkIfStatement_HasTest);
    } else {
      if (m_hasTest) {
        throw JavascriptException(COLUMBUS_LOCATION, CMSG_EX_CAN_T_SET_EDGE_TO_NULL);
      }
    }
  }

  void IfStatement::setTest(expression::Expression *_node) {
    if (_node == NULL)
      throw JavascriptException(COLUMBUS_LOCATION, CMSG_EX_CAN_T_SET_EDGE_TO_NULL);

    setTest(_node->getId());
  }

  void IfStatement::removeTest() {
      if (m_hasTest) {
        removeParentEdge(m_hasTest);
        if (factory->getExistsReverseEdges())
          factory->reverseEdges->removeEdge(m_hasTest, m_id, edkIfStatement_HasTest);
      }
      m_hasTest = 0;
  }

  void IfStatement::setConsequent(NodeId _id) {
    statement::Statement *_node = NULL;
    if (_id) {
      if (!factory->getExist(_id))
        throw JavascriptException(COLUMBUS_LOCATION, CMSG_EX_THE_END_POINT_OF_THE_EDGE_DOES_NOT_EXIST);

      _node = dynamic_cast<statement::Statement*> (factory->getPointer(_id));
      if ( _node == NULL) {
        throw JavascriptException(COLUMBUS_LOCATION, CMSG_EX_INVALID_NODE_KIND);
      }
      if (&(_node->getFactory()) != this->factory)
        throw JavascriptException(COLUMBUS_LOCATION, CMSG_EX_THE_FACTORY_OF_NODES_DOES_NOT_MATCH );

      if (m_hasConsequent) {
        removeParentEdge(m_hasConsequent);
        if (factory->getExistsReverseEdges())
          factory->reverseEdges->removeEdge(m_hasConsequent, m_id, edkIfStatement_HasConsequent);
      }
      m_hasConsequent = _node->getId();
      if (m_hasConsequent != 0)
        setParentEdge(factory->getPointer(m_hasConsequent), edkIfStatement_HasConsequent);
      if (factory->getExistsReverseEdges())
        factory->reverseEdges->insertEdge(m_hasConsequent, this->getId(), edkIfStatement_HasConsequent);
    } else {
      if (m_hasConsequent) {
        throw JavascriptException(COLUMBUS_LOCATION, CMSG_EX_CAN_T_SET_EDGE_TO_NULL);
      }
    }
  }

  void IfStatement::setConsequent(statement::Statement *_node) {
    if (_node == NULL)
      throw JavascriptException(COLUMBUS_LOCATION, CMSG_EX_CAN_T_SET_EDGE_TO_NULL);

    setConsequent(_node->getId());
  }

  void IfStatement::removeConsequent() {
      if (m_hasConsequent) {
        removeParentEdge(m_hasConsequent);
        if (factory->getExistsReverseEdges())
          factory->reverseEdges->removeEdge(m_hasConsequent, m_id, edkIfStatement_HasConsequent);
      }
      m_hasConsequent = 0;
  }

  void IfStatement::setAlternate(NodeId _id) {
    statement::Statement *_node = NULL;
    if (_id) {
      if (!factory->getExist(_id))
        throw JavascriptException(COLUMBUS_LOCATION, CMSG_EX_THE_END_POINT_OF_THE_EDGE_DOES_NOT_EXIST);

      _node = dynamic_cast<statement::Statement*> (factory->getPointer(_id));
      if ( _node == NULL) {
        throw JavascriptException(COLUMBUS_LOCATION, CMSG_EX_INVALID_NODE_KIND);
      }
      if (&(_node->getFactory()) != this->factory)
        throw JavascriptException(COLUMBUS_LOCATION, CMSG_EX_THE_FACTORY_OF_NODES_DOES_NOT_MATCH );

      if (m_hasAlternate) {
        removeParentEdge(m_hasAlternate);
        if (factory->getExistsReverseEdges())
          factory->reverseEdges->removeEdge(m_hasAlternate, m_id, edkIfStatement_HasAlternate);
      }
      m_hasAlternate = _node->getId();
      if (m_hasAlternate != 0)
        setParentEdge(factory->getPointer(m_hasAlternate), edkIfStatement_HasAlternate);
      if (factory->getExistsReverseEdges())
        factory->reverseEdges->insertEdge(m_hasAlternate, this->getId(), edkIfStatement_HasAlternate);
    } else {
      if (m_hasAlternate) {
        throw JavascriptException(COLUMBUS_LOCATION, CMSG_EX_CAN_T_SET_EDGE_TO_NULL);
      }
    }
  }

  void IfStatement::setAlternate(statement::Statement *_node) {
    if (_node == NULL)
      throw JavascriptException(COLUMBUS_LOCATION, CMSG_EX_CAN_T_SET_EDGE_TO_NULL);

    setAlternate(_node->getId());
  }

  void IfStatement::removeAlternate() {
      if (m_hasAlternate) {
        removeParentEdge(m_hasAlternate);
        if (factory->getExistsReverseEdges())
          factory->reverseEdges->removeEdge(m_hasAlternate, m_id, edkIfStatement_HasAlternate);
      }
      m_hasAlternate = 0;
  }

  void IfStatement::accept(Visitor &visitor) const {
    visitor.visit(*this);
  }

  void IfStatement::acceptEnd(Visitor &visitor) const {
    visitor.visitEnd(*this);
  }

  double IfStatement::getSimilarity(const base::Base& base){
    if(base.getNodeKind() == getNodeKind()) {
      return 1.0;
    } else {
      return 0.0;
    }
  }

  void IfStatement::swapStringTable(RefDistributorStrTable& newStrTable, std::map<Key,Key>& oldAndNewStrKeyMap ){
    std::map<Key,Key>::iterator foundKeyId;

  }

  NodeHashType IfStatement::getHash(std::set<NodeId>& travNodes) const {
    if (hashOk) return nodeHashCache;
    common::WriteMsg::write(CMSG_GET_THE_NODE_HASH_OF_NODE_BEGIN,this->getId()); 
    if (travNodes.count(getId())>0) {
      common::WriteMsg::write(CMSG_GET_THE_NODE_HASH_OF_NODE_SKIP);
      return 0;
    }
    travNodes.insert(getId());
    Crc_type resultHash;
    resultHash.process_bytes( "statement::IfStatement", strlen("statement::IfStatement"));
    common::WriteMsg::write(CMSG_GET_THE_NODE_HASH_OF_NODE_END,resultHash.checksum()); 
    nodeHashCache = resultHash.checksum();
    hashOk = true;
    return nodeHashCache;
  }

  void IfStatement::save(io::BinaryIO &binIo,bool withVirtualBase  /*= true*/) const {
    if (withVirtualBase)
      Positioned::save(binIo,false);

    Statement::save(binIo,false);

    binIo.writeUInt4(m_hasTest);
    binIo.writeUInt4(m_hasConsequent);
    binIo.writeUInt4(m_hasAlternate);

  }

  void IfStatement::load(io::BinaryIO &binIo, bool withVirtualBase /*= true*/) {
    if (withVirtualBase)
      Positioned::load(binIo, false);

    Statement::load(binIo,false);

    m_hasTest =  binIo.readUInt4();
    if (m_hasTest != 0)
      setParentEdge(factory->getPointer(m_hasTest),edkIfStatement_HasTest);

    m_hasConsequent =  binIo.readUInt4();
    if (m_hasConsequent != 0)
      setParentEdge(factory->getPointer(m_hasConsequent),edkIfStatement_HasConsequent);

    m_hasAlternate =  binIo.readUInt4();
    if (m_hasAlternate != 0)
      setParentEdge(factory->getPointer(m_hasAlternate),edkIfStatement_HasAlternate);

  }


}


}}}
