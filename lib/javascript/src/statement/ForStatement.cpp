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
  ForStatement::ForStatement(NodeId _id, Factory *_factory) :
         Positioned(_id, _factory),
    Statement(_id, _factory),
    m_hasBody(0),
    m_hasTest(0),
    m_hasUpdate(0),
    m_hasInit(0)
  {
  }

  ForStatement::~ForStatement() {
  }

  void ForStatement::prepareDelete(bool tryOnVirtualParent){
    removeBody();
    removeTest();
    removeUpdate();
    removeInit();
    if (tryOnVirtualParent) {
      base::Positioned::prepareDelete(false);
    }
    statement::Statement::prepareDelete(false);
  }

  NodeKind ForStatement::getNodeKind() const {
    return ndkForStatement;
  }

  statement::Statement* ForStatement::getBody() const {
    statement::Statement *_node = NULL;
    if (m_hasBody != 0)
      _node = dynamic_cast<statement::Statement*>(factory->getPointer(m_hasBody));
    if ( (_node == NULL) || factory->getIsFiltered(_node))
      return NULL;

    return _node;
  }

  expression::Expression* ForStatement::getTest() const {
    expression::Expression *_node = NULL;
    if (m_hasTest != 0)
      _node = dynamic_cast<expression::Expression*>(factory->getPointer(m_hasTest));
    if ( (_node == NULL) || factory->getIsFiltered(_node))
      return NULL;

    return _node;
  }

  expression::Expression* ForStatement::getUpdate() const {
    expression::Expression *_node = NULL;
    if (m_hasUpdate != 0)
      _node = dynamic_cast<expression::Expression*>(factory->getPointer(m_hasUpdate));
    if ( (_node == NULL) || factory->getIsFiltered(_node))
      return NULL;

    return _node;
  }

  base::Positioned* ForStatement::getInit() const {
    base::Positioned *_node = NULL;
    if (m_hasInit != 0)
      _node = dynamic_cast<base::Positioned*>(factory->getPointer(m_hasInit));
    if ( (_node == NULL) || factory->getIsFiltered(_node))
      return NULL;

    return _node;
  }

  bool ForStatement::setEdge(EdgeKind edgeKind, NodeId edgeEnd, bool tryOnVirtualParent) {
    switch (edgeKind) {
      case edkForStatement_HasBody:
        setBody(edgeEnd);
        return true;
      case edkForStatement_HasTest:
        setTest(edgeEnd);
        return true;
      case edkForStatement_HasUpdate:
        setUpdate(edgeEnd);
        return true;
      case edkForStatement_HasInit:
        setInit(edgeEnd);
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

  bool ForStatement::removeEdge(EdgeKind edgeKind, NodeId edgeEnd, bool tryOnVirtualParent) {
    switch (edgeKind) {
      case edkForStatement_HasBody:
        removeBody();
        return true;
      case edkForStatement_HasTest:
        removeTest();
        return true;
      case edkForStatement_HasUpdate:
        removeUpdate();
        return true;
      case edkForStatement_HasInit:
        removeInit();
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

  void ForStatement::setBody(NodeId _id) {
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
          factory->reverseEdges->removeEdge(m_hasBody, m_id, edkForStatement_HasBody);
      }
      m_hasBody = _node->getId();
      if (m_hasBody != 0)
        setParentEdge(factory->getPointer(m_hasBody), edkForStatement_HasBody);
      if (factory->getExistsReverseEdges())
        factory->reverseEdges->insertEdge(m_hasBody, this->getId(), edkForStatement_HasBody);
    } else {
      if (m_hasBody) {
        throw JavascriptException(COLUMBUS_LOCATION, CMSG_EX_CAN_T_SET_EDGE_TO_NULL);
      }
    }
  }

  void ForStatement::setBody(statement::Statement *_node) {
    if (_node == NULL)
      throw JavascriptException(COLUMBUS_LOCATION, CMSG_EX_CAN_T_SET_EDGE_TO_NULL);

    setBody(_node->getId());
  }

  void ForStatement::removeBody() {
      if (m_hasBody) {
        removeParentEdge(m_hasBody);
        if (factory->getExistsReverseEdges())
          factory->reverseEdges->removeEdge(m_hasBody, m_id, edkForStatement_HasBody);
      }
      m_hasBody = 0;
  }

  void ForStatement::setTest(NodeId _id) {
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
          factory->reverseEdges->removeEdge(m_hasTest, m_id, edkForStatement_HasTest);
      }
      m_hasTest = _node->getId();
      if (m_hasTest != 0)
        setParentEdge(factory->getPointer(m_hasTest), edkForStatement_HasTest);
      if (factory->getExistsReverseEdges())
        factory->reverseEdges->insertEdge(m_hasTest, this->getId(), edkForStatement_HasTest);
    } else {
      if (m_hasTest) {
        throw JavascriptException(COLUMBUS_LOCATION, CMSG_EX_CAN_T_SET_EDGE_TO_NULL);
      }
    }
  }

  void ForStatement::setTest(expression::Expression *_node) {
    if (_node == NULL)
      throw JavascriptException(COLUMBUS_LOCATION, CMSG_EX_CAN_T_SET_EDGE_TO_NULL);

    setTest(_node->getId());
  }

  void ForStatement::removeTest() {
      if (m_hasTest) {
        removeParentEdge(m_hasTest);
        if (factory->getExistsReverseEdges())
          factory->reverseEdges->removeEdge(m_hasTest, m_id, edkForStatement_HasTest);
      }
      m_hasTest = 0;
  }

  void ForStatement::setUpdate(NodeId _id) {
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

      if (m_hasUpdate) {
        removeParentEdge(m_hasUpdate);
        if (factory->getExistsReverseEdges())
          factory->reverseEdges->removeEdge(m_hasUpdate, m_id, edkForStatement_HasUpdate);
      }
      m_hasUpdate = _node->getId();
      if (m_hasUpdate != 0)
        setParentEdge(factory->getPointer(m_hasUpdate), edkForStatement_HasUpdate);
      if (factory->getExistsReverseEdges())
        factory->reverseEdges->insertEdge(m_hasUpdate, this->getId(), edkForStatement_HasUpdate);
    } else {
      if (m_hasUpdate) {
        throw JavascriptException(COLUMBUS_LOCATION, CMSG_EX_CAN_T_SET_EDGE_TO_NULL);
      }
    }
  }

  void ForStatement::setUpdate(expression::Expression *_node) {
    if (_node == NULL)
      throw JavascriptException(COLUMBUS_LOCATION, CMSG_EX_CAN_T_SET_EDGE_TO_NULL);

    setUpdate(_node->getId());
  }

  void ForStatement::removeUpdate() {
      if (m_hasUpdate) {
        removeParentEdge(m_hasUpdate);
        if (factory->getExistsReverseEdges())
          factory->reverseEdges->removeEdge(m_hasUpdate, m_id, edkForStatement_HasUpdate);
      }
      m_hasUpdate = 0;
  }

  void ForStatement::setInit(NodeId _id) {
    base::Positioned *_node = NULL;
    if (_id) {
      if (!factory->getExist(_id))
        throw JavascriptException(COLUMBUS_LOCATION, CMSG_EX_THE_END_POINT_OF_THE_EDGE_DOES_NOT_EXIST);

      _node = dynamic_cast<base::Positioned*> (factory->getPointer(_id));
      if ( _node == NULL) {
        throw JavascriptException(COLUMBUS_LOCATION, CMSG_EX_INVALID_NODE_KIND);
      }
      if (&(_node->getFactory()) != this->factory)
        throw JavascriptException(COLUMBUS_LOCATION, CMSG_EX_THE_FACTORY_OF_NODES_DOES_NOT_MATCH );

      if (Common::getIsBaseClassKind(_node->getNodeKind(), ndkExpression) || _node->getNodeKind() == ndkVariableDeclaration) {
        if (m_hasInit) {
          removeParentEdge(m_hasInit);
          if (factory->getExistsReverseEdges())
            factory->reverseEdges->removeEdge(m_hasInit, m_id, edkForStatement_HasInit);
        }
        m_hasInit = _node->getId();
        if (m_hasInit != 0)
          setParentEdge(factory->getPointer(m_hasInit), edkForStatement_HasInit);
        if (factory->getExistsReverseEdges())
          factory->reverseEdges->insertEdge(m_hasInit, this->getId(), edkForStatement_HasInit);
      } else {
        throw JavascriptException(COLUMBUS_LOCATION, CMSG_EX_INVALID_NODE_KIND);
      }
    } else {
      if (m_hasInit) {
        throw JavascriptException(COLUMBUS_LOCATION, CMSG_EX_CAN_T_SET_EDGE_TO_NULL);
      }
    }
  }

  void ForStatement::setInit(base::Positioned *_node) {
    if (_node == NULL)
      throw JavascriptException(COLUMBUS_LOCATION, CMSG_EX_CAN_T_SET_EDGE_TO_NULL);

    setInit(_node->getId());
  }

  void ForStatement::removeInit() {
      if (m_hasInit) {
        removeParentEdge(m_hasInit);
        if (factory->getExistsReverseEdges())
          factory->reverseEdges->removeEdge(m_hasInit, m_id, edkForStatement_HasInit);
      }
      m_hasInit = 0;
  }

  void ForStatement::accept(Visitor &visitor) const {
    visitor.visit(*this);
  }

  void ForStatement::acceptEnd(Visitor &visitor) const {
    visitor.visitEnd(*this);
  }

  double ForStatement::getSimilarity(const base::Base& base){
    if(base.getNodeKind() == getNodeKind()) {
      return 1.0;
    } else {
      return 0.0;
    }
  }

  void ForStatement::swapStringTable(RefDistributorStrTable& newStrTable, std::map<Key,Key>& oldAndNewStrKeyMap ){
    std::map<Key,Key>::iterator foundKeyId;

  }

  NodeHashType ForStatement::getHash(std::set<NodeId>& travNodes) const {
    if (hashOk) return nodeHashCache;
    common::WriteMsg::write(CMSG_GET_THE_NODE_HASH_OF_NODE_BEGIN,this->getId()); 
    if (travNodes.count(getId())>0) {
      common::WriteMsg::write(CMSG_GET_THE_NODE_HASH_OF_NODE_SKIP);
      return 0;
    }
    travNodes.insert(getId());
    Crc_type resultHash;
    resultHash.process_bytes( "statement::ForStatement", strlen("statement::ForStatement"));
    common::WriteMsg::write(CMSG_GET_THE_NODE_HASH_OF_NODE_END,resultHash.checksum()); 
    nodeHashCache = resultHash.checksum();
    hashOk = true;
    return nodeHashCache;
  }

  void ForStatement::save(io::BinaryIO &binIo,bool withVirtualBase  /*= true*/) const {
    if (withVirtualBase)
      Positioned::save(binIo,false);

    Statement::save(binIo,false);

    binIo.writeUInt4(m_hasBody);
    binIo.writeUInt4(m_hasTest);
    binIo.writeUInt4(m_hasUpdate);
    binIo.writeUInt4(m_hasInit);

  }

  void ForStatement::load(io::BinaryIO &binIo, bool withVirtualBase /*= true*/) {
    if (withVirtualBase)
      Positioned::load(binIo, false);

    Statement::load(binIo,false);

    m_hasBody =  binIo.readUInt4();
    if (m_hasBody != 0)
      setParentEdge(factory->getPointer(m_hasBody),edkForStatement_HasBody);

    m_hasTest =  binIo.readUInt4();
    if (m_hasTest != 0)
      setParentEdge(factory->getPointer(m_hasTest),edkForStatement_HasTest);

    m_hasUpdate =  binIo.readUInt4();
    if (m_hasUpdate != 0)
      setParentEdge(factory->getPointer(m_hasUpdate),edkForStatement_HasUpdate);

    m_hasInit =  binIo.readUInt4();
    if (m_hasInit != 0)
      setParentEdge(factory->getPointer(m_hasInit),edkForStatement_HasInit);

  }


}


}}}
