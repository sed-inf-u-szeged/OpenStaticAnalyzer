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
  WithStatement::WithStatement(NodeId _id, Factory *_factory) :
         Positioned(_id, _factory),
    Statement(_id, _factory),
    m_hasObject(0),
    m_hasBody(0)
  {
  }

  WithStatement::~WithStatement() {
  }

  void WithStatement::prepareDelete(bool tryOnVirtualParent){
    removeObject();
    removeBody();
    if (tryOnVirtualParent) {
      base::Positioned::prepareDelete(false);
    }
    statement::Statement::prepareDelete(false);
  }

  NodeKind WithStatement::getNodeKind() const {
    return ndkWithStatement;
  }

  expression::Expression* WithStatement::getObject() const {
    expression::Expression *_node = NULL;
    if (m_hasObject != 0)
      _node = dynamic_cast<expression::Expression*>(factory->getPointer(m_hasObject));
    if ( (_node == NULL) || factory->getIsFiltered(_node))
      return NULL;

    return _node;
  }

  statement::Statement* WithStatement::getBody() const {
    statement::Statement *_node = NULL;
    if (m_hasBody != 0)
      _node = dynamic_cast<statement::Statement*>(factory->getPointer(m_hasBody));
    if ( (_node == NULL) || factory->getIsFiltered(_node))
      return NULL;

    return _node;
  }

  bool WithStatement::setEdge(EdgeKind edgeKind, NodeId edgeEnd, bool tryOnVirtualParent) {
    switch (edgeKind) {
      case edkWithStatement_HasObject:
        setObject(edgeEnd);
        return true;
      case edkWithStatement_HasBody:
        setBody(edgeEnd);
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

  bool WithStatement::removeEdge(EdgeKind edgeKind, NodeId edgeEnd, bool tryOnVirtualParent) {
    switch (edgeKind) {
      case edkWithStatement_HasObject:
        removeObject();
        return true;
      case edkWithStatement_HasBody:
        removeBody();
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

  void WithStatement::setObject(NodeId _id) {
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

      if (m_hasObject) {
        removeParentEdge(m_hasObject);
        if (factory->getExistsReverseEdges())
          factory->reverseEdges->removeEdge(m_hasObject, m_id, edkWithStatement_HasObject);
      }
      m_hasObject = _node->getId();
      if (m_hasObject != 0)
        setParentEdge(factory->getPointer(m_hasObject), edkWithStatement_HasObject);
      if (factory->getExistsReverseEdges())
        factory->reverseEdges->insertEdge(m_hasObject, this->getId(), edkWithStatement_HasObject);
    } else {
      if (m_hasObject) {
        throw JavascriptException(COLUMBUS_LOCATION, CMSG_EX_CAN_T_SET_EDGE_TO_NULL);
      }
    }
  }

  void WithStatement::setObject(expression::Expression *_node) {
    if (_node == NULL)
      throw JavascriptException(COLUMBUS_LOCATION, CMSG_EX_CAN_T_SET_EDGE_TO_NULL);

    setObject(_node->getId());
  }

  void WithStatement::removeObject() {
      if (m_hasObject) {
        removeParentEdge(m_hasObject);
        if (factory->getExistsReverseEdges())
          factory->reverseEdges->removeEdge(m_hasObject, m_id, edkWithStatement_HasObject);
      }
      m_hasObject = 0;
  }

  void WithStatement::setBody(NodeId _id) {
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
          factory->reverseEdges->removeEdge(m_hasBody, m_id, edkWithStatement_HasBody);
      }
      m_hasBody = _node->getId();
      if (m_hasBody != 0)
        setParentEdge(factory->getPointer(m_hasBody), edkWithStatement_HasBody);
      if (factory->getExistsReverseEdges())
        factory->reverseEdges->insertEdge(m_hasBody, this->getId(), edkWithStatement_HasBody);
    } else {
      if (m_hasBody) {
        throw JavascriptException(COLUMBUS_LOCATION, CMSG_EX_CAN_T_SET_EDGE_TO_NULL);
      }
    }
  }

  void WithStatement::setBody(statement::Statement *_node) {
    if (_node == NULL)
      throw JavascriptException(COLUMBUS_LOCATION, CMSG_EX_CAN_T_SET_EDGE_TO_NULL);

    setBody(_node->getId());
  }

  void WithStatement::removeBody() {
      if (m_hasBody) {
        removeParentEdge(m_hasBody);
        if (factory->getExistsReverseEdges())
          factory->reverseEdges->removeEdge(m_hasBody, m_id, edkWithStatement_HasBody);
      }
      m_hasBody = 0;
  }

  void WithStatement::accept(Visitor &visitor) const {
    visitor.visit(*this);
  }

  void WithStatement::acceptEnd(Visitor &visitor) const {
    visitor.visitEnd(*this);
  }

  double WithStatement::getSimilarity(const base::Base& base){
    if(base.getNodeKind() == getNodeKind()) {
      return 1.0;
    } else {
      return 0.0;
    }
  }

  void WithStatement::swapStringTable(RefDistributorStrTable& newStrTable, std::map<Key,Key>& oldAndNewStrKeyMap ){
    std::map<Key,Key>::iterator foundKeyId;

  }

  NodeHashType WithStatement::getHash(std::set<NodeId>& travNodes) const {
    if (hashOk) return nodeHashCache;
    common::WriteMsg::write(CMSG_GET_THE_NODE_HASH_OF_NODE_BEGIN,this->getId()); 
    if (travNodes.count(getId())>0) {
      common::WriteMsg::write(CMSG_GET_THE_NODE_HASH_OF_NODE_SKIP);
      return 0;
    }
    travNodes.insert(getId());
    Crc_type resultHash;
    resultHash.process_bytes( "statement::WithStatement", strlen("statement::WithStatement"));
    common::WriteMsg::write(CMSG_GET_THE_NODE_HASH_OF_NODE_END,resultHash.checksum()); 
    nodeHashCache = resultHash.checksum();
    hashOk = true;
    return nodeHashCache;
  }

  void WithStatement::save(io::BinaryIO &binIo,bool withVirtualBase  /*= true*/) const {
    if (withVirtualBase)
      Positioned::save(binIo,false);

    Statement::save(binIo,false);

    binIo.writeUInt4(m_hasObject);
    binIo.writeUInt4(m_hasBody);

  }

  void WithStatement::load(io::BinaryIO &binIo, bool withVirtualBase /*= true*/) {
    if (withVirtualBase)
      Positioned::load(binIo, false);

    Statement::load(binIo,false);

    m_hasObject =  binIo.readUInt4();
    if (m_hasObject != 0)
      setParentEdge(factory->getPointer(m_hasObject),edkWithStatement_HasObject);

    m_hasBody =  binIo.readUInt4();
    if (m_hasBody != 0)
      setParentEdge(factory->getPointer(m_hasBody),edkWithStatement_HasBody);

  }


}


}}}
