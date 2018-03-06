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

namespace expression { 
  IfExpression::IfExpression(NodeId _id, Factory *_factory) :
    Expression(_id, _factory),
    m_hasBody(0),
    m_hasElseBody(0),
    m_hasTest(0)
  {
  }

  IfExpression::~IfExpression() {
  }

  void IfExpression::prepareDelete(bool tryOnVirtualParent){
    removeBody();
    removeElseBody();
    removeTest();
    expression::Expression::prepareDelete(false);
  }

  NodeKind IfExpression::getNodeKind() const {
    return ndkIfExpression;
  }

  expression::Expression* IfExpression::getBody() const {
    expression::Expression *_node = NULL;
    if (m_hasBody != 0)
      _node = dynamic_cast<expression::Expression*>(factory->getPointer(m_hasBody));
    if ( (_node == NULL) || factory->getIsFiltered(_node))
      return NULL;

    return _node;
  }

  expression::Expression* IfExpression::getElseBody() const {
    expression::Expression *_node = NULL;
    if (m_hasElseBody != 0)
      _node = dynamic_cast<expression::Expression*>(factory->getPointer(m_hasElseBody));
    if ( (_node == NULL) || factory->getIsFiltered(_node))
      return NULL;

    return _node;
  }

  expression::Expression* IfExpression::getTest() const {
    expression::Expression *_node = NULL;
    if (m_hasTest != 0)
      _node = dynamic_cast<expression::Expression*>(factory->getPointer(m_hasTest));
    if ( (_node == NULL) || factory->getIsFiltered(_node))
      return NULL;

    return _node;
  }

  bool IfExpression::setEdge(EdgeKind edgeKind, NodeId edgeEnd, bool tryOnVirtualParent) {
    switch (edgeKind) {
      case edkIfExpression_HasBody:
        setBody(edgeEnd);
        return true;
      case edkIfExpression_HasElseBody:
        setElseBody(edgeEnd);
        return true;
      case edkIfExpression_HasTest:
        setTest(edgeEnd);
        return true;
      default:
        break;
    }
    if (expression::Expression::setEdge(edgeKind, edgeEnd, false)) {
      return true;
    }
    return false;
  }

  bool IfExpression::removeEdge(EdgeKind edgeKind, NodeId edgeEnd, bool tryOnVirtualParent) {
    switch (edgeKind) {
      case edkIfExpression_HasBody:
        removeBody();
        return true;
      case edkIfExpression_HasElseBody:
        removeElseBody();
        return true;
      case edkIfExpression_HasTest:
        removeTest();
        return true;
      default:
        break;
    }
    if (expression::Expression::removeEdge(edgeKind, edgeEnd, false)) {
      return true;
    }
    return false;
  }

  void IfExpression::setBody(NodeId _id) {
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

      if (m_hasBody) {
        removeParentEdge(m_hasBody);
        if (factory->getExistsReverseEdges())
          factory->reverseEdges->removeEdge(m_hasBody, m_id, edkIfExpression_HasBody);
      }
      m_hasBody = _node->getId();
      if (m_hasBody != 0)
        setParentEdge(factory->getPointer(m_hasBody), edkIfExpression_HasBody);
      if (factory->getExistsReverseEdges())
        factory->reverseEdges->insertEdge(m_hasBody, this->getId(), edkIfExpression_HasBody);
    } else {
      if (m_hasBody) {
        throw PythonException(COLUMBUS_LOCATION, CMSG_EX_CAN_T_SET_EDGE_TO_NULL);
      }
    }
  }

  void IfExpression::setBody(expression::Expression *_node) {
    if (_node == NULL)
      throw PythonException(COLUMBUS_LOCATION, CMSG_EX_CAN_T_SET_EDGE_TO_NULL);

    setBody(_node->getId());
  }

  void IfExpression::removeBody() {
      if (m_hasBody) {
        removeParentEdge(m_hasBody);
        if (factory->getExistsReverseEdges())
          factory->reverseEdges->removeEdge(m_hasBody, m_id, edkIfExpression_HasBody);
      }
      m_hasBody = 0;
  }

  void IfExpression::setElseBody(NodeId _id) {
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

      if (m_hasElseBody) {
        removeParentEdge(m_hasElseBody);
        if (factory->getExistsReverseEdges())
          factory->reverseEdges->removeEdge(m_hasElseBody, m_id, edkIfExpression_HasElseBody);
      }
      m_hasElseBody = _node->getId();
      if (m_hasElseBody != 0)
        setParentEdge(factory->getPointer(m_hasElseBody), edkIfExpression_HasElseBody);
      if (factory->getExistsReverseEdges())
        factory->reverseEdges->insertEdge(m_hasElseBody, this->getId(), edkIfExpression_HasElseBody);
    } else {
      if (m_hasElseBody) {
        throw PythonException(COLUMBUS_LOCATION, CMSG_EX_CAN_T_SET_EDGE_TO_NULL);
      }
    }
  }

  void IfExpression::setElseBody(expression::Expression *_node) {
    if (_node == NULL)
      throw PythonException(COLUMBUS_LOCATION, CMSG_EX_CAN_T_SET_EDGE_TO_NULL);

    setElseBody(_node->getId());
  }

  void IfExpression::removeElseBody() {
      if (m_hasElseBody) {
        removeParentEdge(m_hasElseBody);
        if (factory->getExistsReverseEdges())
          factory->reverseEdges->removeEdge(m_hasElseBody, m_id, edkIfExpression_HasElseBody);
      }
      m_hasElseBody = 0;
  }

  void IfExpression::setTest(NodeId _id) {
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

      if (m_hasTest) {
        removeParentEdge(m_hasTest);
        if (factory->getExistsReverseEdges())
          factory->reverseEdges->removeEdge(m_hasTest, m_id, edkIfExpression_HasTest);
      }
      m_hasTest = _node->getId();
      if (m_hasTest != 0)
        setParentEdge(factory->getPointer(m_hasTest), edkIfExpression_HasTest);
      if (factory->getExistsReverseEdges())
        factory->reverseEdges->insertEdge(m_hasTest, this->getId(), edkIfExpression_HasTest);
    } else {
      if (m_hasTest) {
        throw PythonException(COLUMBUS_LOCATION, CMSG_EX_CAN_T_SET_EDGE_TO_NULL);
      }
    }
  }

  void IfExpression::setTest(expression::Expression *_node) {
    if (_node == NULL)
      throw PythonException(COLUMBUS_LOCATION, CMSG_EX_CAN_T_SET_EDGE_TO_NULL);

    setTest(_node->getId());
  }

  void IfExpression::removeTest() {
      if (m_hasTest) {
        removeParentEdge(m_hasTest);
        if (factory->getExistsReverseEdges())
          factory->reverseEdges->removeEdge(m_hasTest, m_id, edkIfExpression_HasTest);
      }
      m_hasTest = 0;
  }

  void IfExpression::accept(Visitor &visitor) const {
    visitor.visit(*this);
  }

  void IfExpression::acceptEnd(Visitor &visitor) const {
    visitor.visitEnd(*this);
  }

  double IfExpression::getSimilarity(const base::Base& base){
    if(base.getNodeKind() == getNodeKind()) {
      return 1.0;
    } else {
      return 0.0;
    }
  }

  void IfExpression::swapStringTable(RefDistributorStrTable& newStrTable, std::map<Key,Key>& oldAndNewStrKeyMap ){
    std::map<Key,Key>::iterator foundKeyId;

  }

  NodeHashType IfExpression::getHash(std::set<NodeId>& travNodes) const {
    if (hashOk) return nodeHashCache;
    common::WriteMsg::write(CMSG_GET_THE_NODE_HASH_OF_NODE_BEGIN,this->getId()); 
    if (travNodes.count(getId())>0) {
      common::WriteMsg::write(CMSG_GET_THE_NODE_HASH_OF_NODE_SKIP);
      return 0;
    }
    travNodes.insert(getId());
    Crc_type resultHash;
    resultHash.process_bytes( "expression::IfExpression", strlen("expression::IfExpression"));
    common::WriteMsg::write(CMSG_GET_THE_NODE_HASH_OF_NODE_END,resultHash.checksum()); 
    nodeHashCache = resultHash.checksum();
    hashOk = true;
    return nodeHashCache;
  }

  void IfExpression::save(io::BinaryIO &binIo,bool withVirtualBase  /*= true*/) const {
    Expression::save(binIo,false);

    binIo.writeUInt4(m_hasBody);
    binIo.writeUInt4(m_hasElseBody);
    binIo.writeUInt4(m_hasTest);

  }

  void IfExpression::load(io::BinaryIO &binIo, bool withVirtualBase /*= true*/) {
    Expression::load(binIo,false);

    m_hasBody =  binIo.readUInt4();
    if (m_hasBody != 0)
      setParentEdge(factory->getPointer(m_hasBody),edkIfExpression_HasBody);

    m_hasElseBody =  binIo.readUInt4();
    if (m_hasElseBody != 0)
      setParentEdge(factory->getPointer(m_hasElseBody),edkIfExpression_HasElseBody);

    m_hasTest =  binIo.readUInt4();
    if (m_hasTest != 0)
      setParentEdge(factory->getPointer(m_hasTest),edkIfExpression_HasTest);

  }


}


}}}
