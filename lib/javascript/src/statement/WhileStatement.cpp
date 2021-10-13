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
  WhileStatement::WhileStatement(NodeId _id, Factory *_factory) :
         Positioned(_id, _factory),
    Statement(_id, _factory),
    m_hasBody(0),
    m_hasTest(0)
  {
  }

  WhileStatement::~WhileStatement() {
  }

  void WhileStatement::prepareDelete(bool tryOnVirtualParent){
    removeBody();
    removeTest();
    if (tryOnVirtualParent) {
      base::Positioned::prepareDelete(false);
    }
    statement::Statement::prepareDelete(false);
  }

  NodeKind WhileStatement::getNodeKind() const {
    return ndkWhileStatement;
  }

  statement::Statement* WhileStatement::getBody() const {
    statement::Statement *_node = NULL;
    if (m_hasBody != 0)
      _node = dynamic_cast<statement::Statement*>(factory->getPointer(m_hasBody));
    if ( (_node == NULL) || factory->getIsFiltered(_node))
      return NULL;

    return _node;
  }

  expression::Expression* WhileStatement::getTest() const {
    expression::Expression *_node = NULL;
    if (m_hasTest != 0)
      _node = dynamic_cast<expression::Expression*>(factory->getPointer(m_hasTest));
    if ( (_node == NULL) || factory->getIsFiltered(_node))
      return NULL;

    return _node;
  }

  bool WhileStatement::setEdge(EdgeKind edgeKind, NodeId edgeEnd, bool tryOnVirtualParent) {
    switch (edgeKind) {
      case edkWhileStatement_HasBody:
        setBody(edgeEnd);
        return true;
      case edkWhileStatement_HasTest:
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
    if (statement::Statement::setEdge(edgeKind, edgeEnd, false)) {
      return true;
    }
    return false;
  }

  bool WhileStatement::removeEdge(EdgeKind edgeKind, NodeId edgeEnd, bool tryOnVirtualParent) {
    switch (edgeKind) {
      case edkWhileStatement_HasBody:
        removeBody();
        return true;
      case edkWhileStatement_HasTest:
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
    if (statement::Statement::removeEdge(edgeKind, edgeEnd, false)) {
      return true;
    }
    return false;
  }

  void WhileStatement::setBody(NodeId _id) {
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

      if (m_hasBody) {
        removeParentEdge(m_hasBody);
        if (factory->getExistsReverseEdges())
          factory->reverseEdges->removeEdge(m_hasBody, m_id, edkWhileStatement_HasBody);
      }
      m_hasBody = _node->getId();
      if (m_hasBody != 0)
        setParentEdge(factory->getPointer(m_hasBody), edkWhileStatement_HasBody);
      if (factory->getExistsReverseEdges())
        factory->reverseEdges->insertEdge(m_hasBody, this->getId(), edkWhileStatement_HasBody);
    } else {
      if (m_hasBody) {
        throw JavascriptException(COLUMBUS_LOCATION, CMSG_EX_CAN_T_SET_EDGE_TO_NULL);
      }
    }
  }

  void WhileStatement::setBody(statement::Statement *_node) {
    if (_node == NULL)
      throw JavascriptException(COLUMBUS_LOCATION, CMSG_EX_CAN_T_SET_EDGE_TO_NULL);

    setBody(_node->getId());
  }

  void WhileStatement::removeBody() {
      if (m_hasBody) {
        removeParentEdge(m_hasBody);
        if (factory->getExistsReverseEdges())
          factory->reverseEdges->removeEdge(m_hasBody, m_id, edkWhileStatement_HasBody);
      }
      m_hasBody = 0;
  }

  void WhileStatement::setTest(NodeId _id) {
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
          factory->reverseEdges->removeEdge(m_hasTest, m_id, edkWhileStatement_HasTest);
      }
      m_hasTest = _node->getId();
      if (m_hasTest != 0)
        setParentEdge(factory->getPointer(m_hasTest), edkWhileStatement_HasTest);
      if (factory->getExistsReverseEdges())
        factory->reverseEdges->insertEdge(m_hasTest, this->getId(), edkWhileStatement_HasTest);
    } else {
      if (m_hasTest) {
        throw JavascriptException(COLUMBUS_LOCATION, CMSG_EX_CAN_T_SET_EDGE_TO_NULL);
      }
    }
  }

  void WhileStatement::setTest(expression::Expression *_node) {
    if (_node == NULL)
      throw JavascriptException(COLUMBUS_LOCATION, CMSG_EX_CAN_T_SET_EDGE_TO_NULL);

    setTest(_node->getId());
  }

  void WhileStatement::removeTest() {
      if (m_hasTest) {
        removeParentEdge(m_hasTest);
        if (factory->getExistsReverseEdges())
          factory->reverseEdges->removeEdge(m_hasTest, m_id, edkWhileStatement_HasTest);
      }
      m_hasTest = 0;
  }

  void WhileStatement::accept(Visitor &visitor) const {
    visitor.visit(*this);
  }

  void WhileStatement::acceptEnd(Visitor &visitor) const {
    visitor.visitEnd(*this);
  }

  double WhileStatement::getSimilarity(const base::Base& base){
    if(base.getNodeKind() == getNodeKind()) {
      return 1.0;
    } else {
      return 0.0;
    }
  }

  void WhileStatement::swapStringTable(RefDistributorStrTable& newStrTable, std::map<Key,Key>& oldAndNewStrKeyMap ){
    std::map<Key,Key>::iterator foundKeyId;

  }

  NodeHashType WhileStatement::getHash(std::set<NodeId>& travNodes) const {
    if (hashOk) return nodeHashCache;
    common::WriteMsg::write(CMSG_GET_THE_NODE_HASH_OF_NODE_BEGIN,this->getId()); 
    if (travNodes.count(getId())>0) {
      common::WriteMsg::write(CMSG_GET_THE_NODE_HASH_OF_NODE_SKIP);
      return 0;
    }
    travNodes.insert(getId());
    Crc_type resultHash;
    resultHash.process_bytes( "statement::WhileStatement", strlen("statement::WhileStatement"));
    common::WriteMsg::write(CMSG_GET_THE_NODE_HASH_OF_NODE_END,resultHash.checksum()); 
    nodeHashCache = resultHash.checksum();
    hashOk = true;
    return nodeHashCache;
  }

  void WhileStatement::save(io::BinaryIO &binIo,bool withVirtualBase  /*= true*/) const {
    if (withVirtualBase)
      Positioned::save(binIo,false);

    Statement::save(binIo,false);

    binIo.writeUInt4(m_hasBody);
    binIo.writeUInt4(m_hasTest);

  }

  void WhileStatement::load(io::BinaryIO &binIo, bool withVirtualBase /*= true*/) {
    if (withVirtualBase)
      Positioned::load(binIo, false);

    Statement::load(binIo,false);

    m_hasBody =  binIo.readUInt4();
    if (m_hasBody != 0)
      setParentEdge(factory->getPointer(m_hasBody),edkWhileStatement_HasBody);

    m_hasTest =  binIo.readUInt4();
    if (m_hasTest != 0)
      setParentEdge(factory->getPointer(m_hasTest),edkWhileStatement_HasTest);

  }


}


}}}
