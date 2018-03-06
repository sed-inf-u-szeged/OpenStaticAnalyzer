/*
 *  This file is part of OpenStaticAnalyzer.
 *
 *  Copyright (c) 2004-2017 Department of Software Engineering - University of Szeged
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
  Raise::Raise(NodeId _id, Factory *_factory) :
    SimpleStatement(_id, _factory),
    m_hasTracebackExpression(0),
    m_hasTypeExpression(0),
    m_hasValueExpression(0)
  {
  }

  Raise::~Raise() {
  }

  void Raise::prepareDelete(bool tryOnVirtualParent){
    removeTracebackExpression();
    removeTypeExpression();
    removeValueExpression();
    statement::SimpleStatement::prepareDelete(false);
  }

  NodeKind Raise::getNodeKind() const {
    return ndkRaise;
  }

  expression::Expression* Raise::getTracebackExpression() const {
    expression::Expression *_node = NULL;
    if (m_hasTracebackExpression != 0)
      _node = dynamic_cast<expression::Expression*>(factory->getPointer(m_hasTracebackExpression));
    if ( (_node == NULL) || factory->getIsFiltered(_node))
      return NULL;

    return _node;
  }

  expression::Expression* Raise::getTypeExpression() const {
    expression::Expression *_node = NULL;
    if (m_hasTypeExpression != 0)
      _node = dynamic_cast<expression::Expression*>(factory->getPointer(m_hasTypeExpression));
    if ( (_node == NULL) || factory->getIsFiltered(_node))
      return NULL;

    return _node;
  }

  expression::Expression* Raise::getValueExpression() const {
    expression::Expression *_node = NULL;
    if (m_hasValueExpression != 0)
      _node = dynamic_cast<expression::Expression*>(factory->getPointer(m_hasValueExpression));
    if ( (_node == NULL) || factory->getIsFiltered(_node))
      return NULL;

    return _node;
  }

  bool Raise::setEdge(EdgeKind edgeKind, NodeId edgeEnd, bool tryOnVirtualParent) {
    switch (edgeKind) {
      case edkRaise_HasTracebackExpression:
        setTracebackExpression(edgeEnd);
        return true;
      case edkRaise_HasTypeExpression:
        setTypeExpression(edgeEnd);
        return true;
      case edkRaise_HasValueExpression:
        setValueExpression(edgeEnd);
        return true;
      default:
        break;
    }
    if (statement::SimpleStatement::setEdge(edgeKind, edgeEnd, false)) {
      return true;
    }
    return false;
  }

  bool Raise::removeEdge(EdgeKind edgeKind, NodeId edgeEnd, bool tryOnVirtualParent) {
    switch (edgeKind) {
      case edkRaise_HasTracebackExpression:
        removeTracebackExpression();
        return true;
      case edkRaise_HasTypeExpression:
        removeTypeExpression();
        return true;
      case edkRaise_HasValueExpression:
        removeValueExpression();
        return true;
      default:
        break;
    }
    if (statement::SimpleStatement::removeEdge(edgeKind, edgeEnd, false)) {
      return true;
    }
    return false;
  }

  void Raise::setTracebackExpression(NodeId _id) {
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

      if (m_hasTracebackExpression) {
        removeParentEdge(m_hasTracebackExpression);
        if (factory->getExistsReverseEdges())
          factory->reverseEdges->removeEdge(m_hasTracebackExpression, m_id, edkRaise_HasTracebackExpression);
      }
      m_hasTracebackExpression = _node->getId();
      if (m_hasTracebackExpression != 0)
        setParentEdge(factory->getPointer(m_hasTracebackExpression), edkRaise_HasTracebackExpression);
      if (factory->getExistsReverseEdges())
        factory->reverseEdges->insertEdge(m_hasTracebackExpression, this->getId(), edkRaise_HasTracebackExpression);
    } else {
      if (m_hasTracebackExpression) {
        throw PythonException(COLUMBUS_LOCATION, CMSG_EX_CAN_T_SET_EDGE_TO_NULL);
      }
    }
  }

  void Raise::setTracebackExpression(expression::Expression *_node) {
    if (_node == NULL)
      throw PythonException(COLUMBUS_LOCATION, CMSG_EX_CAN_T_SET_EDGE_TO_NULL);

    setTracebackExpression(_node->getId());
  }

  void Raise::removeTracebackExpression() {
      if (m_hasTracebackExpression) {
        removeParentEdge(m_hasTracebackExpression);
        if (factory->getExistsReverseEdges())
          factory->reverseEdges->removeEdge(m_hasTracebackExpression, m_id, edkRaise_HasTracebackExpression);
      }
      m_hasTracebackExpression = 0;
  }

  void Raise::setTypeExpression(NodeId _id) {
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

      if (m_hasTypeExpression) {
        removeParentEdge(m_hasTypeExpression);
        if (factory->getExistsReverseEdges())
          factory->reverseEdges->removeEdge(m_hasTypeExpression, m_id, edkRaise_HasTypeExpression);
      }
      m_hasTypeExpression = _node->getId();
      if (m_hasTypeExpression != 0)
        setParentEdge(factory->getPointer(m_hasTypeExpression), edkRaise_HasTypeExpression);
      if (factory->getExistsReverseEdges())
        factory->reverseEdges->insertEdge(m_hasTypeExpression, this->getId(), edkRaise_HasTypeExpression);
    } else {
      if (m_hasTypeExpression) {
        throw PythonException(COLUMBUS_LOCATION, CMSG_EX_CAN_T_SET_EDGE_TO_NULL);
      }
    }
  }

  void Raise::setTypeExpression(expression::Expression *_node) {
    if (_node == NULL)
      throw PythonException(COLUMBUS_LOCATION, CMSG_EX_CAN_T_SET_EDGE_TO_NULL);

    setTypeExpression(_node->getId());
  }

  void Raise::removeTypeExpression() {
      if (m_hasTypeExpression) {
        removeParentEdge(m_hasTypeExpression);
        if (factory->getExistsReverseEdges())
          factory->reverseEdges->removeEdge(m_hasTypeExpression, m_id, edkRaise_HasTypeExpression);
      }
      m_hasTypeExpression = 0;
  }

  void Raise::setValueExpression(NodeId _id) {
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

      if (m_hasValueExpression) {
        removeParentEdge(m_hasValueExpression);
        if (factory->getExistsReverseEdges())
          factory->reverseEdges->removeEdge(m_hasValueExpression, m_id, edkRaise_HasValueExpression);
      }
      m_hasValueExpression = _node->getId();
      if (m_hasValueExpression != 0)
        setParentEdge(factory->getPointer(m_hasValueExpression), edkRaise_HasValueExpression);
      if (factory->getExistsReverseEdges())
        factory->reverseEdges->insertEdge(m_hasValueExpression, this->getId(), edkRaise_HasValueExpression);
    } else {
      if (m_hasValueExpression) {
        throw PythonException(COLUMBUS_LOCATION, CMSG_EX_CAN_T_SET_EDGE_TO_NULL);
      }
    }
  }

  void Raise::setValueExpression(expression::Expression *_node) {
    if (_node == NULL)
      throw PythonException(COLUMBUS_LOCATION, CMSG_EX_CAN_T_SET_EDGE_TO_NULL);

    setValueExpression(_node->getId());
  }

  void Raise::removeValueExpression() {
      if (m_hasValueExpression) {
        removeParentEdge(m_hasValueExpression);
        if (factory->getExistsReverseEdges())
          factory->reverseEdges->removeEdge(m_hasValueExpression, m_id, edkRaise_HasValueExpression);
      }
      m_hasValueExpression = 0;
  }

  void Raise::accept(Visitor &visitor) const {
    visitor.visit(*this);
  }

  void Raise::acceptEnd(Visitor &visitor) const {
    visitor.visitEnd(*this);
  }

  double Raise::getSimilarity(const base::Base& base){
    if(base.getNodeKind() == getNodeKind()) {
      return 1.0;
    } else {
      return 0.0;
    }
  }

  void Raise::swapStringTable(RefDistributorStrTable& newStrTable, std::map<Key,Key>& oldAndNewStrKeyMap ){
    std::map<Key,Key>::iterator foundKeyId;

  }

  NodeHashType Raise::getHash(std::set<NodeId>& travNodes) const {
    if (hashOk) return nodeHashCache;
    common::WriteMsg::write(CMSG_GET_THE_NODE_HASH_OF_NODE_BEGIN,this->getId()); 
    if (travNodes.count(getId())>0) {
      common::WriteMsg::write(CMSG_GET_THE_NODE_HASH_OF_NODE_SKIP);
      return 0;
    }
    travNodes.insert(getId());
    Crc_type resultHash;
    resultHash.process_bytes( "statement::Raise", strlen("statement::Raise"));
    common::WriteMsg::write(CMSG_GET_THE_NODE_HASH_OF_NODE_END,resultHash.checksum()); 
    nodeHashCache = resultHash.checksum();
    hashOk = true;
    return nodeHashCache;
  }

  void Raise::save(io::BinaryIO &binIo,bool withVirtualBase  /*= true*/) const {
    SimpleStatement::save(binIo,false);

    binIo.writeUInt4(m_hasTracebackExpression);
    binIo.writeUInt4(m_hasTypeExpression);
    binIo.writeUInt4(m_hasValueExpression);

  }

  void Raise::load(io::BinaryIO &binIo, bool withVirtualBase /*= true*/) {
    SimpleStatement::load(binIo,false);

    m_hasTracebackExpression =  binIo.readUInt4();
    if (m_hasTracebackExpression != 0)
      setParentEdge(factory->getPointer(m_hasTracebackExpression),edkRaise_HasTracebackExpression);

    m_hasTypeExpression =  binIo.readUInt4();
    if (m_hasTypeExpression != 0)
      setParentEdge(factory->getPointer(m_hasTypeExpression),edkRaise_HasTypeExpression);

    m_hasValueExpression =  binIo.readUInt4();
    if (m_hasValueExpression != 0)
      setParentEdge(factory->getPointer(m_hasValueExpression),edkRaise_HasValueExpression);

  }


}


}}}
