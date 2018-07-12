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

namespace expression { 
  Binary::Binary(NodeId _id, Factory *_factory) :
    Expression(_id, _factory),
    m_hasLeftExpression(0),
    m_hasRightExpression(0)
  {
  }

  Binary::~Binary() {
  }

  void Binary::prepareDelete(bool tryOnVirtualParent){
    removeLeftExpression();
    removeRightExpression();
    expression::Expression::prepareDelete(false);
  }

  expression::Expression* Binary::getLeftExpression() const {
    expression::Expression *_node = NULL;
    if (m_hasLeftExpression != 0)
      _node = dynamic_cast<expression::Expression*>(factory->getPointer(m_hasLeftExpression));
    if ( (_node == NULL) || factory->getIsFiltered(_node))
      return NULL;

    return _node;
  }

  expression::Expression* Binary::getRightExpression() const {
    expression::Expression *_node = NULL;
    if (m_hasRightExpression != 0)
      _node = dynamic_cast<expression::Expression*>(factory->getPointer(m_hasRightExpression));
    if ( (_node == NULL) || factory->getIsFiltered(_node))
      return NULL;

    return _node;
  }

  bool Binary::setEdge(EdgeKind edgeKind, NodeId edgeEnd, bool tryOnVirtualParent) {
    switch (edgeKind) {
      case edkBinary_HasLeftExpression:
        setLeftExpression(edgeEnd);
        return true;
      case edkBinary_HasRightExpression:
        setRightExpression(edgeEnd);
        return true;
      default:
        break;
    }
    if (expression::Expression::setEdge(edgeKind, edgeEnd, false)) {
      return true;
    }
    return false;
  }

  bool Binary::removeEdge(EdgeKind edgeKind, NodeId edgeEnd, bool tryOnVirtualParent) {
    switch (edgeKind) {
      case edkBinary_HasLeftExpression:
        removeLeftExpression();
        return true;
      case edkBinary_HasRightExpression:
        removeRightExpression();
        return true;
      default:
        break;
    }
    if (expression::Expression::removeEdge(edgeKind, edgeEnd, false)) {
      return true;
    }
    return false;
  }

  void Binary::setLeftExpression(NodeId _id) {
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

      if (m_hasLeftExpression) {
        removeParentEdge(m_hasLeftExpression);
        if (factory->getExistsReverseEdges())
          factory->reverseEdges->removeEdge(m_hasLeftExpression, m_id, edkBinary_HasLeftExpression);
      }
      m_hasLeftExpression = _node->getId();
      if (m_hasLeftExpression != 0)
        setParentEdge(factory->getPointer(m_hasLeftExpression), edkBinary_HasLeftExpression);
      if (factory->getExistsReverseEdges())
        factory->reverseEdges->insertEdge(m_hasLeftExpression, this->getId(), edkBinary_HasLeftExpression);
    } else {
      if (m_hasLeftExpression) {
        throw PythonException(COLUMBUS_LOCATION, CMSG_EX_CAN_T_SET_EDGE_TO_NULL);
      }
    }
  }

  void Binary::setLeftExpression(expression::Expression *_node) {
    if (_node == NULL)
      throw PythonException(COLUMBUS_LOCATION, CMSG_EX_CAN_T_SET_EDGE_TO_NULL);

    setLeftExpression(_node->getId());
  }

  void Binary::removeLeftExpression() {
      if (m_hasLeftExpression) {
        removeParentEdge(m_hasLeftExpression);
        if (factory->getExistsReverseEdges())
          factory->reverseEdges->removeEdge(m_hasLeftExpression, m_id, edkBinary_HasLeftExpression);
      }
      m_hasLeftExpression = 0;
  }

  void Binary::setRightExpression(NodeId _id) {
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

      if (m_hasRightExpression) {
        removeParentEdge(m_hasRightExpression);
        if (factory->getExistsReverseEdges())
          factory->reverseEdges->removeEdge(m_hasRightExpression, m_id, edkBinary_HasRightExpression);
      }
      m_hasRightExpression = _node->getId();
      if (m_hasRightExpression != 0)
        setParentEdge(factory->getPointer(m_hasRightExpression), edkBinary_HasRightExpression);
      if (factory->getExistsReverseEdges())
        factory->reverseEdges->insertEdge(m_hasRightExpression, this->getId(), edkBinary_HasRightExpression);
    } else {
      if (m_hasRightExpression) {
        throw PythonException(COLUMBUS_LOCATION, CMSG_EX_CAN_T_SET_EDGE_TO_NULL);
      }
    }
  }

  void Binary::setRightExpression(expression::Expression *_node) {
    if (_node == NULL)
      throw PythonException(COLUMBUS_LOCATION, CMSG_EX_CAN_T_SET_EDGE_TO_NULL);

    setRightExpression(_node->getId());
  }

  void Binary::removeRightExpression() {
      if (m_hasRightExpression) {
        removeParentEdge(m_hasRightExpression);
        if (factory->getExistsReverseEdges())
          factory->reverseEdges->removeEdge(m_hasRightExpression, m_id, edkBinary_HasRightExpression);
      }
      m_hasRightExpression = 0;
  }

  double Binary::getSimilarity(const base::Base& base){
    if(base.getNodeKind() == getNodeKind()) {
      return 1.0;
    } else {
      return 0.0;
    }
  }

  void Binary::swapStringTable(RefDistributorStrTable& newStrTable, std::map<Key,Key>& oldAndNewStrKeyMap ){
    std::map<Key,Key>::iterator foundKeyId;

  }

  NodeHashType Binary::getHash(std::set<NodeId>& travNodes) const {
    if (hashOk) return nodeHashCache;
    common::WriteMsg::write(CMSG_GET_THE_NODE_HASH_OF_NODE_BEGIN,this->getId()); 
    if (travNodes.count(getId())>0) {
      common::WriteMsg::write(CMSG_GET_THE_NODE_HASH_OF_NODE_SKIP);
      return 0;
    }
    travNodes.insert(getId());
    Crc_type resultHash;
    resultHash.process_bytes( "expression::Binary", strlen("expression::Binary"));
    common::WriteMsg::write(CMSG_GET_THE_NODE_HASH_OF_NODE_END,resultHash.checksum()); 
    nodeHashCache = resultHash.checksum();
    hashOk = true;
    return nodeHashCache;
  }

  void Binary::save(io::BinaryIO &binIo,bool withVirtualBase  /*= true*/) const {
    Expression::save(binIo,false);

    binIo.writeUInt4(m_hasLeftExpression);
    binIo.writeUInt4(m_hasRightExpression);

  }

  void Binary::load(io::BinaryIO &binIo, bool withVirtualBase /*= true*/) {
    Expression::load(binIo,false);

    m_hasLeftExpression =  binIo.readUInt4();
    if (m_hasLeftExpression != 0)
      setParentEdge(factory->getPointer(m_hasLeftExpression),edkBinary_HasLeftExpression);

    m_hasRightExpression =  binIo.readUInt4();
    if (m_hasRightExpression != 0)
      setParentEdge(factory->getPointer(m_hasRightExpression),edkBinary_HasRightExpression);

  }


}


}}}
