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
  ForInStatement::ForInStatement(NodeId _id, Factory *_factory) :
         Positioned(_id, _factory),
    Statement(_id, _factory),
    m_hasRight(0),
    m_hasBody(0),
    m_hasLeft(0)
  {
  }

  ForInStatement::~ForInStatement() {
  }

  void ForInStatement::prepareDelete(bool tryOnVirtualParent){
    removeRight();
    removeBody();
    removeLeft();
    if (tryOnVirtualParent) {
      base::Positioned::prepareDelete(false);
    }
    statement::Statement::prepareDelete(false);
  }

  NodeKind ForInStatement::getNodeKind() const {
    return ndkForInStatement;
  }

  expression::Expression* ForInStatement::getRight() const {
    expression::Expression *_node = NULL;
    if (m_hasRight != 0)
      _node = dynamic_cast<expression::Expression*>(factory->getPointer(m_hasRight));
    if ( (_node == NULL) || factory->getIsFiltered(_node))
      return NULL;

    return _node;
  }

  statement::Statement* ForInStatement::getBody() const {
    statement::Statement *_node = NULL;
    if (m_hasBody != 0)
      _node = dynamic_cast<statement::Statement*>(factory->getPointer(m_hasBody));
    if ( (_node == NULL) || factory->getIsFiltered(_node))
      return NULL;

    return _node;
  }

  base::Positioned* ForInStatement::getLeft() const {
    base::Positioned *_node = NULL;
    if (m_hasLeft != 0)
      _node = dynamic_cast<base::Positioned*>(factory->getPointer(m_hasLeft));
    if ( (_node == NULL) || factory->getIsFiltered(_node))
      return NULL;

    return _node;
  }

  bool ForInStatement::setEdge(EdgeKind edgeKind, NodeId edgeEnd, bool tryOnVirtualParent) {
    switch (edgeKind) {
      case edkForInStatement_HasRight:
        setRight(edgeEnd);
        return true;
      case edkForInStatement_HasBody:
        setBody(edgeEnd);
        return true;
      case edkForInStatement_HasLeft:
        setLeft(edgeEnd);
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

  bool ForInStatement::removeEdge(EdgeKind edgeKind, NodeId edgeEnd, bool tryOnVirtualParent) {
    switch (edgeKind) {
      case edkForInStatement_HasRight:
        removeRight();
        return true;
      case edkForInStatement_HasBody:
        removeBody();
        return true;
      case edkForInStatement_HasLeft:
        removeLeft();
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

  void ForInStatement::setRight(NodeId _id) {
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
          factory->reverseEdges->removeEdge(m_hasRight, m_id, edkForInStatement_HasRight);
      }
      m_hasRight = _node->getId();
      if (m_hasRight != 0)
        setParentEdge(factory->getPointer(m_hasRight), edkForInStatement_HasRight);
      if (factory->getExistsReverseEdges())
        factory->reverseEdges->insertEdge(m_hasRight, this->getId(), edkForInStatement_HasRight);
    } else {
      if (m_hasRight) {
        throw JavascriptException(COLUMBUS_LOCATION, CMSG_EX_CAN_T_SET_EDGE_TO_NULL);
      }
    }
  }

  void ForInStatement::setRight(expression::Expression *_node) {
    if (_node == NULL)
      throw JavascriptException(COLUMBUS_LOCATION, CMSG_EX_CAN_T_SET_EDGE_TO_NULL);

    setRight(_node->getId());
  }

  void ForInStatement::removeRight() {
      if (m_hasRight) {
        removeParentEdge(m_hasRight);
        if (factory->getExistsReverseEdges())
          factory->reverseEdges->removeEdge(m_hasRight, m_id, edkForInStatement_HasRight);
      }
      m_hasRight = 0;
  }

  void ForInStatement::setBody(NodeId _id) {
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
          factory->reverseEdges->removeEdge(m_hasBody, m_id, edkForInStatement_HasBody);
      }
      m_hasBody = _node->getId();
      if (m_hasBody != 0)
        setParentEdge(factory->getPointer(m_hasBody), edkForInStatement_HasBody);
      if (factory->getExistsReverseEdges())
        factory->reverseEdges->insertEdge(m_hasBody, this->getId(), edkForInStatement_HasBody);
    } else {
      if (m_hasBody) {
        throw JavascriptException(COLUMBUS_LOCATION, CMSG_EX_CAN_T_SET_EDGE_TO_NULL);
      }
    }
  }

  void ForInStatement::setBody(statement::Statement *_node) {
    if (_node == NULL)
      throw JavascriptException(COLUMBUS_LOCATION, CMSG_EX_CAN_T_SET_EDGE_TO_NULL);

    setBody(_node->getId());
  }

  void ForInStatement::removeBody() {
      if (m_hasBody) {
        removeParentEdge(m_hasBody);
        if (factory->getExistsReverseEdges())
          factory->reverseEdges->removeEdge(m_hasBody, m_id, edkForInStatement_HasBody);
      }
      m_hasBody = 0;
  }

  void ForInStatement::setLeft(NodeId _id) {
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

      if (Common::getIsBaseClassKind(_node->getNodeKind(), ndkPattern) || _node->getNodeKind() == ndkVariableDeclaration) {
        if (m_hasLeft) {
          removeParentEdge(m_hasLeft);
          if (factory->getExistsReverseEdges())
            factory->reverseEdges->removeEdge(m_hasLeft, m_id, edkForInStatement_HasLeft);
        }
        m_hasLeft = _node->getId();
        if (m_hasLeft != 0)
          setParentEdge(factory->getPointer(m_hasLeft), edkForInStatement_HasLeft);
        if (factory->getExistsReverseEdges())
          factory->reverseEdges->insertEdge(m_hasLeft, this->getId(), edkForInStatement_HasLeft);
      } else {
        throw JavascriptException(COLUMBUS_LOCATION, CMSG_EX_INVALID_NODE_KIND);
      }
    } else {
      if (m_hasLeft) {
        throw JavascriptException(COLUMBUS_LOCATION, CMSG_EX_CAN_T_SET_EDGE_TO_NULL);
      }
    }
  }

  void ForInStatement::setLeft(base::Positioned *_node) {
    if (_node == NULL)
      throw JavascriptException(COLUMBUS_LOCATION, CMSG_EX_CAN_T_SET_EDGE_TO_NULL);

    setLeft(_node->getId());
  }

  void ForInStatement::removeLeft() {
      if (m_hasLeft) {
        removeParentEdge(m_hasLeft);
        if (factory->getExistsReverseEdges())
          factory->reverseEdges->removeEdge(m_hasLeft, m_id, edkForInStatement_HasLeft);
      }
      m_hasLeft = 0;
  }

  void ForInStatement::accept(Visitor &visitor) const {
    visitor.visit(*this);
  }

  void ForInStatement::acceptEnd(Visitor &visitor) const {
    visitor.visitEnd(*this);
  }

  double ForInStatement::getSimilarity(const base::Base& base){
    if(base.getNodeKind() == getNodeKind()) {
      return 1.0;
    } else {
      return 0.0;
    }
  }

  void ForInStatement::swapStringTable(RefDistributorStrTable& newStrTable, std::map<Key,Key>& oldAndNewStrKeyMap ){
    std::map<Key,Key>::iterator foundKeyId;

  }

  NodeHashType ForInStatement::getHash(std::set<NodeId>& travNodes) const {
    if (hashOk) return nodeHashCache;
    common::WriteMsg::write(CMSG_GET_THE_NODE_HASH_OF_NODE_BEGIN,this->getId()); 
    if (travNodes.count(getId())>0) {
      common::WriteMsg::write(CMSG_GET_THE_NODE_HASH_OF_NODE_SKIP);
      return 0;
    }
    travNodes.insert(getId());
    Crc_type resultHash;
    resultHash.process_bytes( "statement::ForInStatement", strlen("statement::ForInStatement"));
    common::WriteMsg::write(CMSG_GET_THE_NODE_HASH_OF_NODE_END,resultHash.checksum()); 
    nodeHashCache = resultHash.checksum();
    hashOk = true;
    return nodeHashCache;
  }

  void ForInStatement::save(io::BinaryIO &binIo,bool withVirtualBase  /*= true*/) const {
    if (withVirtualBase)
      Positioned::save(binIo,false);

    Statement::save(binIo,false);

    binIo.writeUInt4(m_hasRight);
    binIo.writeUInt4(m_hasBody);
    binIo.writeUInt4(m_hasLeft);

  }

  void ForInStatement::load(io::BinaryIO &binIo, bool withVirtualBase /*= true*/) {
    if (withVirtualBase)
      Positioned::load(binIo, false);

    Statement::load(binIo,false);

    m_hasRight =  binIo.readUInt4();
    if (m_hasRight != 0)
      setParentEdge(factory->getPointer(m_hasRight),edkForInStatement_HasRight);

    m_hasBody =  binIo.readUInt4();
    if (m_hasBody != 0)
      setParentEdge(factory->getPointer(m_hasBody),edkForInStatement_HasBody);

    m_hasLeft =  binIo.readUInt4();
    if (m_hasLeft != 0)
      setParentEdge(factory->getPointer(m_hasLeft),edkForInStatement_HasLeft);

  }


}


}}}
