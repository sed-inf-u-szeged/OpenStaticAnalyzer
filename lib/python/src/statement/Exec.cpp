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
  Exec::Exec(NodeId _id, Factory *_factory) :
    SimpleStatement(_id, _factory),
    m_hasExpression(0),
    m_hasGlobals(0),
    m_hasLocals(0)
  {
  }

  Exec::~Exec() {
  }

  void Exec::prepareDelete(bool tryOnVirtualParent){
    removeExpression();
    removeGlobals();
    removeLocals();
    statement::SimpleStatement::prepareDelete(false);
  }

  NodeKind Exec::getNodeKind() const {
    return ndkExec;
  }

  expression::Expression* Exec::getExpression() const {
    expression::Expression *_node = NULL;
    if (m_hasExpression != 0)
      _node = dynamic_cast<expression::Expression*>(factory->getPointer(m_hasExpression));
    if ( (_node == NULL) || factory->getIsFiltered(_node))
      return NULL;

    return _node;
  }

  expression::Expression* Exec::getGlobals() const {
    expression::Expression *_node = NULL;
    if (m_hasGlobals != 0)
      _node = dynamic_cast<expression::Expression*>(factory->getPointer(m_hasGlobals));
    if ( (_node == NULL) || factory->getIsFiltered(_node))
      return NULL;

    return _node;
  }

  expression::Expression* Exec::getLocals() const {
    expression::Expression *_node = NULL;
    if (m_hasLocals != 0)
      _node = dynamic_cast<expression::Expression*>(factory->getPointer(m_hasLocals));
    if ( (_node == NULL) || factory->getIsFiltered(_node))
      return NULL;

    return _node;
  }

  bool Exec::setEdge(EdgeKind edgeKind, NodeId edgeEnd, bool tryOnVirtualParent) {
    switch (edgeKind) {
      case edkExec_HasExpression:
        setExpression(edgeEnd);
        return true;
      case edkExec_HasGlobals:
        setGlobals(edgeEnd);
        return true;
      case edkExec_HasLocals:
        setLocals(edgeEnd);
        return true;
      default:
        break;
    }
    if (statement::SimpleStatement::setEdge(edgeKind, edgeEnd, false)) {
      return true;
    }
    return false;
  }

  bool Exec::removeEdge(EdgeKind edgeKind, NodeId edgeEnd, bool tryOnVirtualParent) {
    switch (edgeKind) {
      case edkExec_HasExpression:
        removeExpression();
        return true;
      case edkExec_HasGlobals:
        removeGlobals();
        return true;
      case edkExec_HasLocals:
        removeLocals();
        return true;
      default:
        break;
    }
    if (statement::SimpleStatement::removeEdge(edgeKind, edgeEnd, false)) {
      return true;
    }
    return false;
  }

  void Exec::setExpression(NodeId _id) {
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
          factory->reverseEdges->removeEdge(m_hasExpression, m_id, edkExec_HasExpression);
      }
      m_hasExpression = _node->getId();
      if (m_hasExpression != 0)
        setParentEdge(factory->getPointer(m_hasExpression), edkExec_HasExpression);
      if (factory->getExistsReverseEdges())
        factory->reverseEdges->insertEdge(m_hasExpression, this->getId(), edkExec_HasExpression);
    } else {
      if (m_hasExpression) {
        throw PythonException(COLUMBUS_LOCATION, CMSG_EX_CAN_T_SET_EDGE_TO_NULL);
      }
    }
  }

  void Exec::setExpression(expression::Expression *_node) {
    if (_node == NULL)
      throw PythonException(COLUMBUS_LOCATION, CMSG_EX_CAN_T_SET_EDGE_TO_NULL);

    setExpression(_node->getId());
  }

  void Exec::removeExpression() {
      if (m_hasExpression) {
        removeParentEdge(m_hasExpression);
        if (factory->getExistsReverseEdges())
          factory->reverseEdges->removeEdge(m_hasExpression, m_id, edkExec_HasExpression);
      }
      m_hasExpression = 0;
  }

  void Exec::setGlobals(NodeId _id) {
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

      if (m_hasGlobals) {
        removeParentEdge(m_hasGlobals);
        if (factory->getExistsReverseEdges())
          factory->reverseEdges->removeEdge(m_hasGlobals, m_id, edkExec_HasGlobals);
      }
      m_hasGlobals = _node->getId();
      if (m_hasGlobals != 0)
        setParentEdge(factory->getPointer(m_hasGlobals), edkExec_HasGlobals);
      if (factory->getExistsReverseEdges())
        factory->reverseEdges->insertEdge(m_hasGlobals, this->getId(), edkExec_HasGlobals);
    } else {
      if (m_hasGlobals) {
        throw PythonException(COLUMBUS_LOCATION, CMSG_EX_CAN_T_SET_EDGE_TO_NULL);
      }
    }
  }

  void Exec::setGlobals(expression::Expression *_node) {
    if (_node == NULL)
      throw PythonException(COLUMBUS_LOCATION, CMSG_EX_CAN_T_SET_EDGE_TO_NULL);

    setGlobals(_node->getId());
  }

  void Exec::removeGlobals() {
      if (m_hasGlobals) {
        removeParentEdge(m_hasGlobals);
        if (factory->getExistsReverseEdges())
          factory->reverseEdges->removeEdge(m_hasGlobals, m_id, edkExec_HasGlobals);
      }
      m_hasGlobals = 0;
  }

  void Exec::setLocals(NodeId _id) {
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

      if (m_hasLocals) {
        removeParentEdge(m_hasLocals);
        if (factory->getExistsReverseEdges())
          factory->reverseEdges->removeEdge(m_hasLocals, m_id, edkExec_HasLocals);
      }
      m_hasLocals = _node->getId();
      if (m_hasLocals != 0)
        setParentEdge(factory->getPointer(m_hasLocals), edkExec_HasLocals);
      if (factory->getExistsReverseEdges())
        factory->reverseEdges->insertEdge(m_hasLocals, this->getId(), edkExec_HasLocals);
    } else {
      if (m_hasLocals) {
        throw PythonException(COLUMBUS_LOCATION, CMSG_EX_CAN_T_SET_EDGE_TO_NULL);
      }
    }
  }

  void Exec::setLocals(expression::Expression *_node) {
    if (_node == NULL)
      throw PythonException(COLUMBUS_LOCATION, CMSG_EX_CAN_T_SET_EDGE_TO_NULL);

    setLocals(_node->getId());
  }

  void Exec::removeLocals() {
      if (m_hasLocals) {
        removeParentEdge(m_hasLocals);
        if (factory->getExistsReverseEdges())
          factory->reverseEdges->removeEdge(m_hasLocals, m_id, edkExec_HasLocals);
      }
      m_hasLocals = 0;
  }

  void Exec::accept(Visitor &visitor) const {
    visitor.visit(*this);
  }

  void Exec::acceptEnd(Visitor &visitor) const {
    visitor.visitEnd(*this);
  }

  double Exec::getSimilarity(const base::Base& base){
    if(base.getNodeKind() == getNodeKind()) {
      return 1.0;
    } else {
      return 0.0;
    }
  }

  void Exec::swapStringTable(RefDistributorStrTable& newStrTable, std::map<Key,Key>& oldAndNewStrKeyMap ){
    std::map<Key,Key>::iterator foundKeyId;

  }

  NodeHashType Exec::getHash(std::set<NodeId>& travNodes) const {
    if (hashOk) return nodeHashCache;
    common::WriteMsg::write(CMSG_GET_THE_NODE_HASH_OF_NODE_BEGIN,this->getId()); 
    if (travNodes.count(getId())>0) {
      common::WriteMsg::write(CMSG_GET_THE_NODE_HASH_OF_NODE_SKIP);
      return 0;
    }
    travNodes.insert(getId());
    Crc_type resultHash;
    resultHash.process_bytes( "statement::Exec", strlen("statement::Exec"));
    common::WriteMsg::write(CMSG_GET_THE_NODE_HASH_OF_NODE_END,resultHash.checksum()); 
    nodeHashCache = resultHash.checksum();
    hashOk = true;
    return nodeHashCache;
  }

  void Exec::save(io::BinaryIO &binIo,bool withVirtualBase  /*= true*/) const {
    SimpleStatement::save(binIo,false);

    binIo.writeUInt4(m_hasExpression);
    binIo.writeUInt4(m_hasGlobals);
    binIo.writeUInt4(m_hasLocals);

  }

  void Exec::load(io::BinaryIO &binIo, bool withVirtualBase /*= true*/) {
    SimpleStatement::load(binIo,false);

    m_hasExpression =  binIo.readUInt4();
    if (m_hasExpression != 0)
      setParentEdge(factory->getPointer(m_hasExpression),edkExec_HasExpression);

    m_hasGlobals =  binIo.readUInt4();
    if (m_hasGlobals != 0)
      setParentEdge(factory->getPointer(m_hasGlobals),edkExec_HasGlobals);

    m_hasLocals =  binIo.readUInt4();
    if (m_hasLocals != 0)
      setParentEdge(factory->getPointer(m_hasLocals),edkExec_HasLocals);

  }


}


}}}
