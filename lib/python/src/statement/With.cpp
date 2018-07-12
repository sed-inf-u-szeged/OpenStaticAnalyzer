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
  With::With(NodeId _id, Factory *_factory) :
    CompoundStatement(_id, _factory),
    m_hasExpression(0),
    m_hasTargetList(0)
  {
  }

  With::~With() {
  }

  void With::prepareDelete(bool tryOnVirtualParent){
    removeExpression();
    removeTargetList();
    statement::CompoundStatement::prepareDelete(false);
  }

  NodeKind With::getNodeKind() const {
    return ndkWith;
  }

  expression::Expression* With::getExpression() const {
    expression::Expression *_node = NULL;
    if (m_hasExpression != 0)
      _node = dynamic_cast<expression::Expression*>(factory->getPointer(m_hasExpression));
    if ( (_node == NULL) || factory->getIsFiltered(_node))
      return NULL;

    return _node;
  }

  statement::TargetList* With::getTargetList() const {
    statement::TargetList *_node = NULL;
    if (m_hasTargetList != 0)
      _node = dynamic_cast<statement::TargetList*>(factory->getPointer(m_hasTargetList));
    if ( (_node == NULL) || factory->getIsFiltered(_node))
      return NULL;

    return _node;
  }

  bool With::setEdge(EdgeKind edgeKind, NodeId edgeEnd, bool tryOnVirtualParent) {
    switch (edgeKind) {
      case edkWith_HasExpression:
        setExpression(edgeEnd);
        return true;
      case edkWith_HasTargetList:
        setTargetList(edgeEnd);
        return true;
      default:
        break;
    }
    if (statement::CompoundStatement::setEdge(edgeKind, edgeEnd, false)) {
      return true;
    }
    return false;
  }

  bool With::removeEdge(EdgeKind edgeKind, NodeId edgeEnd, bool tryOnVirtualParent) {
    switch (edgeKind) {
      case edkWith_HasExpression:
        removeExpression();
        return true;
      case edkWith_HasTargetList:
        removeTargetList();
        return true;
      default:
        break;
    }
    if (statement::CompoundStatement::removeEdge(edgeKind, edgeEnd, false)) {
      return true;
    }
    return false;
  }

  void With::setExpression(NodeId _id) {
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

      if (m_hasExpression) {
        removeParentEdge(m_hasExpression);
        if (factory->getExistsReverseEdges())
          factory->reverseEdges->removeEdge(m_hasExpression, m_id, edkWith_HasExpression);
      }
      m_hasExpression = _node->getId();
      if (m_hasExpression != 0)
        setParentEdge(factory->getPointer(m_hasExpression), edkWith_HasExpression);
      if (factory->getExistsReverseEdges())
        factory->reverseEdges->insertEdge(m_hasExpression, this->getId(), edkWith_HasExpression);
    } else {
      if (m_hasExpression) {
        throw PythonException(COLUMBUS_LOCATION, CMSG_EX_CAN_T_SET_EDGE_TO_NULL);
      }
    }
  }

  void With::setExpression(expression::Expression *_node) {
    if (_node == NULL)
      throw PythonException(COLUMBUS_LOCATION, CMSG_EX_CAN_T_SET_EDGE_TO_NULL);

    setExpression(_node->getId());
  }

  void With::removeExpression() {
      if (m_hasExpression) {
        removeParentEdge(m_hasExpression);
        if (factory->getExistsReverseEdges())
          factory->reverseEdges->removeEdge(m_hasExpression, m_id, edkWith_HasExpression);
      }
      m_hasExpression = 0;
  }

  void With::setTargetList(NodeId _id) {
    statement::TargetList *_node = NULL;
    if (_id) {
      if (!factory->getExist(_id))
        throw PythonException(COLUMBUS_LOCATION, CMSG_EX_THE_END_POINT_OF_THE_EDGE_DOES_NOT_EXIST);

      _node = dynamic_cast<statement::TargetList*> (factory->getPointer(_id));
      if ( _node == NULL) {
        throw PythonException(COLUMBUS_LOCATION, CMSG_EX_INVALID_NODE_KIND);
      }
      if (&(_node->getFactory()) != this->factory)
        throw PythonException(COLUMBUS_LOCATION, CMSG_EX_THE_FACTORY_OF_NODES_DOES_NOT_MATCH );

      if (m_hasTargetList) {
        removeParentEdge(m_hasTargetList);
        if (factory->getExistsReverseEdges())
          factory->reverseEdges->removeEdge(m_hasTargetList, m_id, edkWith_HasTargetList);
      }
      m_hasTargetList = _node->getId();
      if (m_hasTargetList != 0)
        setParentEdge(factory->getPointer(m_hasTargetList), edkWith_HasTargetList);
      if (factory->getExistsReverseEdges())
        factory->reverseEdges->insertEdge(m_hasTargetList, this->getId(), edkWith_HasTargetList);
    } else {
      if (m_hasTargetList) {
        throw PythonException(COLUMBUS_LOCATION, CMSG_EX_CAN_T_SET_EDGE_TO_NULL);
      }
    }
  }

  void With::setTargetList(statement::TargetList *_node) {
    if (_node == NULL)
      throw PythonException(COLUMBUS_LOCATION, CMSG_EX_CAN_T_SET_EDGE_TO_NULL);

    setTargetList(_node->getId());
  }

  void With::removeTargetList() {
      if (m_hasTargetList) {
        removeParentEdge(m_hasTargetList);
        if (factory->getExistsReverseEdges())
          factory->reverseEdges->removeEdge(m_hasTargetList, m_id, edkWith_HasTargetList);
      }
      m_hasTargetList = 0;
  }

  void With::accept(Visitor &visitor) const {
    visitor.visit(*this);
  }

  void With::acceptEnd(Visitor &visitor) const {
    visitor.visitEnd(*this);
  }

  double With::getSimilarity(const base::Base& base){
    if(base.getNodeKind() == getNodeKind()) {
      return 1.0;
    } else {
      return 0.0;
    }
  }

  void With::swapStringTable(RefDistributorStrTable& newStrTable, std::map<Key,Key>& oldAndNewStrKeyMap ){
    std::map<Key,Key>::iterator foundKeyId;

  }

  NodeHashType With::getHash(std::set<NodeId>& travNodes) const {
    if (hashOk) return nodeHashCache;
    common::WriteMsg::write(CMSG_GET_THE_NODE_HASH_OF_NODE_BEGIN,this->getId()); 
    if (travNodes.count(getId())>0) {
      common::WriteMsg::write(CMSG_GET_THE_NODE_HASH_OF_NODE_SKIP);
      return 0;
    }
    travNodes.insert(getId());
    Crc_type resultHash;
    resultHash.process_bytes( "statement::With", strlen("statement::With"));
    common::WriteMsg::write(CMSG_GET_THE_NODE_HASH_OF_NODE_END,resultHash.checksum()); 
    nodeHashCache = resultHash.checksum();
    hashOk = true;
    return nodeHashCache;
  }

  void With::save(io::BinaryIO &binIo,bool withVirtualBase  /*= true*/) const {
    CompoundStatement::save(binIo,false);

    binIo.writeUInt4(m_hasExpression);
    binIo.writeUInt4(m_hasTargetList);

  }

  void With::load(io::BinaryIO &binIo, bool withVirtualBase /*= true*/) {
    CompoundStatement::load(binIo,false);

    m_hasExpression =  binIo.readUInt4();
    if (m_hasExpression != 0)
      setParentEdge(factory->getPointer(m_hasExpression),edkWith_HasExpression);

    m_hasTargetList =  binIo.readUInt4();
    if (m_hasTargetList != 0)
      setParentEdge(factory->getPointer(m_hasTargetList),edkWith_HasTargetList);

  }


}


}}}
