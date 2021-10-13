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

#include "csharp/inc/csharp.h"
#include "csharp/inc/Common.h"
#include "common/inc/WriteMessage.h"

#include "csharp/inc/messages.h"
#include <algorithm>
#include <string.h>
#include "common/inc/math/common.h"


namespace columbus { namespace csharp { namespace asg {

typedef boost::crc_32_type  Crc_type;

namespace expression { 
  InvocationExpressionSyntax::InvocationExpressionSyntax(NodeId _id, Factory *_factory) :
    ExpressionSyntax(_id, _factory),
    m_ArgumentList(0),
    m_Expression(0),
    m_LocalFunctionCall(0),
    m_MethodCall(0)
  {
  }

  InvocationExpressionSyntax::~InvocationExpressionSyntax() {
  }

  void InvocationExpressionSyntax::prepareDelete(bool tryOnVirtualParent){
    removeArgumentList();
    removeExpression();
    removeLocalFunctionCall();
    removeMethodCall();
    expression::ExpressionSyntax::prepareDelete(false);
  }

  NodeKind InvocationExpressionSyntax::getNodeKind() const {
    return ndkInvocationExpressionSyntax;
  }

  structure::ArgumentListSyntax* InvocationExpressionSyntax::getArgumentList() const {
    structure::ArgumentListSyntax *_node = NULL;
    if (m_ArgumentList != 0)
      _node = dynamic_cast<structure::ArgumentListSyntax*>(factory->getPointer(m_ArgumentList));
    if ( (_node == NULL) || factory->getIsFiltered(_node))
      return NULL;

    return _node;
  }

  expression::ExpressionSyntax* InvocationExpressionSyntax::getExpression() const {
    expression::ExpressionSyntax *_node = NULL;
    if (m_Expression != 0)
      _node = dynamic_cast<expression::ExpressionSyntax*>(factory->getPointer(m_Expression));
    if ( (_node == NULL) || factory->getIsFiltered(_node))
      return NULL;

    return _node;
  }

  statement::LocalFunctionStatementSyntax* InvocationExpressionSyntax::getLocalFunctionCall() const {
    statement::LocalFunctionStatementSyntax *_node = NULL;
    if (m_LocalFunctionCall != 0)
      _node = dynamic_cast<statement::LocalFunctionStatementSyntax*>(factory->getPointer(m_LocalFunctionCall));
    if ( (_node == NULL) || factory->getIsFiltered(_node))
      return NULL;

    return _node;
  }

  structure::MethodDeclarationSyntax* InvocationExpressionSyntax::getMethodCall() const {
    structure::MethodDeclarationSyntax *_node = NULL;
    if (m_MethodCall != 0)
      _node = dynamic_cast<structure::MethodDeclarationSyntax*>(factory->getPointer(m_MethodCall));
    if ( (_node == NULL) || factory->getIsFiltered(_node))
      return NULL;

    return _node;
  }

  bool InvocationExpressionSyntax::setEdge(EdgeKind edgeKind, NodeId edgeEnd, bool tryOnVirtualParent) {
    switch (edgeKind) {
      case edkInvocationExpressionSyntax_ArgumentList:
        setArgumentList(edgeEnd);
        return true;
      case edkInvocationExpressionSyntax_Expression:
        setExpression(edgeEnd);
        return true;
      case edkInvocationExpressionSyntax_LocalFunctionCall:
        setLocalFunctionCall(edgeEnd);
        return true;
      case edkInvocationExpressionSyntax_MethodCall:
        setMethodCall(edgeEnd);
        return true;
      default:
        break;
    }
    if (expression::ExpressionSyntax::setEdge(edgeKind, edgeEnd, false)) {
      return true;
    }
    return false;
  }

  bool InvocationExpressionSyntax::removeEdge(EdgeKind edgeKind, NodeId edgeEnd, bool tryOnVirtualParent) {
    switch (edgeKind) {
      case edkInvocationExpressionSyntax_ArgumentList:
        removeArgumentList();
        return true;
      case edkInvocationExpressionSyntax_Expression:
        removeExpression();
        return true;
      case edkInvocationExpressionSyntax_LocalFunctionCall:
        removeLocalFunctionCall();
        return true;
      case edkInvocationExpressionSyntax_MethodCall:
        removeMethodCall();
        return true;
      default:
        break;
    }
    if (expression::ExpressionSyntax::removeEdge(edgeKind, edgeEnd, false)) {
      return true;
    }
    return false;
  }

  void InvocationExpressionSyntax::setArgumentList(NodeId _id) {
    structure::ArgumentListSyntax *_node = NULL;
    if (_id) {
      if (!factory->getExist(_id))
        throw CsharpException(COLUMBUS_LOCATION, CMSG_EX_THE_END_POINT_OF_THE_EDGE_DOES_NOT_EXIST);

      _node = dynamic_cast<structure::ArgumentListSyntax*> (factory->getPointer(_id));
      if ( _node == NULL) {
        throw CsharpException(COLUMBUS_LOCATION, CMSG_EX_INVALID_NODE_KIND);
      }
      if (&(_node->getFactory()) != this->factory)
        throw CsharpException(COLUMBUS_LOCATION, CMSG_EX_THE_FACTORY_OF_NODES_DOES_NOT_MATCH );

      if (m_ArgumentList) {
        removeParentEdge(m_ArgumentList);
        if (factory->getExistsReverseEdges())
          factory->reverseEdges->removeEdge(m_ArgumentList, m_id, edkInvocationExpressionSyntax_ArgumentList);
      }
      m_ArgumentList = _node->getId();
      if (m_ArgumentList != 0)
        setParentEdge(factory->getPointer(m_ArgumentList), edkInvocationExpressionSyntax_ArgumentList);
      if (factory->getExistsReverseEdges())
        factory->reverseEdges->insertEdge(m_ArgumentList, this->getId(), edkInvocationExpressionSyntax_ArgumentList);
    } else {
      if (m_ArgumentList) {
        throw CsharpException(COLUMBUS_LOCATION, CMSG_EX_CAN_T_SET_EDGE_TO_NULL);
      }
    }
  }

  void InvocationExpressionSyntax::setArgumentList(structure::ArgumentListSyntax *_node) {
    if (_node == NULL)
      throw CsharpException(COLUMBUS_LOCATION, CMSG_EX_CAN_T_SET_EDGE_TO_NULL);

    setArgumentList(_node->getId());
  }

  void InvocationExpressionSyntax::removeArgumentList() {
      if (m_ArgumentList) {
        removeParentEdge(m_ArgumentList);
        if (factory->getExistsReverseEdges())
          factory->reverseEdges->removeEdge(m_ArgumentList, m_id, edkInvocationExpressionSyntax_ArgumentList);
      }
      m_ArgumentList = 0;
  }

  void InvocationExpressionSyntax::setExpression(NodeId _id) {
    expression::ExpressionSyntax *_node = NULL;
    if (_id) {
      if (!factory->getExist(_id))
        throw CsharpException(COLUMBUS_LOCATION, CMSG_EX_THE_END_POINT_OF_THE_EDGE_DOES_NOT_EXIST);

      _node = dynamic_cast<expression::ExpressionSyntax*> (factory->getPointer(_id));
      if ( _node == NULL) {
        throw CsharpException(COLUMBUS_LOCATION, CMSG_EX_INVALID_NODE_KIND);
      }
      if (&(_node->getFactory()) != this->factory)
        throw CsharpException(COLUMBUS_LOCATION, CMSG_EX_THE_FACTORY_OF_NODES_DOES_NOT_MATCH );

      if (m_Expression) {
        removeParentEdge(m_Expression);
        if (factory->getExistsReverseEdges())
          factory->reverseEdges->removeEdge(m_Expression, m_id, edkInvocationExpressionSyntax_Expression);
      }
      m_Expression = _node->getId();
      if (m_Expression != 0)
        setParentEdge(factory->getPointer(m_Expression), edkInvocationExpressionSyntax_Expression);
      if (factory->getExistsReverseEdges())
        factory->reverseEdges->insertEdge(m_Expression, this->getId(), edkInvocationExpressionSyntax_Expression);
    } else {
      if (m_Expression) {
        throw CsharpException(COLUMBUS_LOCATION, CMSG_EX_CAN_T_SET_EDGE_TO_NULL);
      }
    }
  }

  void InvocationExpressionSyntax::setExpression(expression::ExpressionSyntax *_node) {
    if (_node == NULL)
      throw CsharpException(COLUMBUS_LOCATION, CMSG_EX_CAN_T_SET_EDGE_TO_NULL);

    setExpression(_node->getId());
  }

  void InvocationExpressionSyntax::removeExpression() {
      if (m_Expression) {
        removeParentEdge(m_Expression);
        if (factory->getExistsReverseEdges())
          factory->reverseEdges->removeEdge(m_Expression, m_id, edkInvocationExpressionSyntax_Expression);
      }
      m_Expression = 0;
  }

  void InvocationExpressionSyntax::setLocalFunctionCall(NodeId _id) {
    statement::LocalFunctionStatementSyntax *_node = NULL;
    if (_id) {
      if (!factory->getExist(_id))
        throw CsharpException(COLUMBUS_LOCATION, CMSG_EX_THE_END_POINT_OF_THE_EDGE_DOES_NOT_EXIST);

      _node = dynamic_cast<statement::LocalFunctionStatementSyntax*> (factory->getPointer(_id));
      if ( _node == NULL) {
        throw CsharpException(COLUMBUS_LOCATION, CMSG_EX_INVALID_NODE_KIND);
      }
      if (&(_node->getFactory()) != this->factory)
        throw CsharpException(COLUMBUS_LOCATION, CMSG_EX_THE_FACTORY_OF_NODES_DOES_NOT_MATCH );

      if (m_LocalFunctionCall) {
        if (factory->getExistsReverseEdges())
          factory->reverseEdges->removeEdge(m_LocalFunctionCall, m_id, edkInvocationExpressionSyntax_LocalFunctionCall);
      }
      m_LocalFunctionCall = _node->getId();
      if (factory->getExistsReverseEdges())
        factory->reverseEdges->insertEdge(m_LocalFunctionCall, this->getId(), edkInvocationExpressionSyntax_LocalFunctionCall);
    } else {
      if (m_LocalFunctionCall) {
        throw CsharpException(COLUMBUS_LOCATION, CMSG_EX_CAN_T_SET_EDGE_TO_NULL);
      }
    }
  }

  void InvocationExpressionSyntax::setLocalFunctionCall(statement::LocalFunctionStatementSyntax *_node) {
    if (_node == NULL)
      throw CsharpException(COLUMBUS_LOCATION, CMSG_EX_CAN_T_SET_EDGE_TO_NULL);

    setLocalFunctionCall(_node->getId());
  }

  void InvocationExpressionSyntax::removeLocalFunctionCall() {
      if (m_LocalFunctionCall) {
        if (factory->getExistsReverseEdges())
          factory->reverseEdges->removeEdge(m_LocalFunctionCall, m_id, edkInvocationExpressionSyntax_LocalFunctionCall);
      }
      m_LocalFunctionCall = 0;
  }

  void InvocationExpressionSyntax::setMethodCall(NodeId _id) {
    structure::MethodDeclarationSyntax *_node = NULL;
    if (_id) {
      if (!factory->getExist(_id))
        throw CsharpException(COLUMBUS_LOCATION, CMSG_EX_THE_END_POINT_OF_THE_EDGE_DOES_NOT_EXIST);

      _node = dynamic_cast<structure::MethodDeclarationSyntax*> (factory->getPointer(_id));
      if ( _node == NULL) {
        throw CsharpException(COLUMBUS_LOCATION, CMSG_EX_INVALID_NODE_KIND);
      }
      if (&(_node->getFactory()) != this->factory)
        throw CsharpException(COLUMBUS_LOCATION, CMSG_EX_THE_FACTORY_OF_NODES_DOES_NOT_MATCH );

      if (m_MethodCall) {
        if (factory->getExistsReverseEdges())
          factory->reverseEdges->removeEdge(m_MethodCall, m_id, edkInvocationExpressionSyntax_MethodCall);
      }
      m_MethodCall = _node->getId();
      if (factory->getExistsReverseEdges())
        factory->reverseEdges->insertEdge(m_MethodCall, this->getId(), edkInvocationExpressionSyntax_MethodCall);
    } else {
      if (m_MethodCall) {
        throw CsharpException(COLUMBUS_LOCATION, CMSG_EX_CAN_T_SET_EDGE_TO_NULL);
      }
    }
  }

  void InvocationExpressionSyntax::setMethodCall(structure::MethodDeclarationSyntax *_node) {
    if (_node == NULL)
      throw CsharpException(COLUMBUS_LOCATION, CMSG_EX_CAN_T_SET_EDGE_TO_NULL);

    setMethodCall(_node->getId());
  }

  void InvocationExpressionSyntax::removeMethodCall() {
      if (m_MethodCall) {
        if (factory->getExistsReverseEdges())
          factory->reverseEdges->removeEdge(m_MethodCall, m_id, edkInvocationExpressionSyntax_MethodCall);
      }
      m_MethodCall = 0;
  }

  void InvocationExpressionSyntax::accept(Visitor &visitor) const {
    visitor.visit(*this);
  }

  void InvocationExpressionSyntax::acceptEnd(Visitor &visitor) const {
    visitor.visitEnd(*this);
  }

  double InvocationExpressionSyntax::getSimilarity(const base::Base& base){
    if(base.getNodeKind() == getNodeKind()) {
      return 1.0;
    } else {
      return 0.0;
    }
  }

  void InvocationExpressionSyntax::swapStringTable(RefDistributorStrTable& newStrTable, std::map<Key,Key>& oldAndNewStrKeyMap ){
    std::map<Key,Key>::iterator foundKeyId;

      m_position.swapStringTable(newStrTable,oldAndNewStrKeyMap);

  }

  NodeHashType InvocationExpressionSyntax::getHash(std::set<NodeId>& travNodes) const {
    if (hashOk) return nodeHashCache;
    common::WriteMsg::write(CMSG_GET_THE_NODE_HASH_OF_NODE_BEGIN,this->getId()); 
    if (travNodes.count(getId())>0) {
      common::WriteMsg::write(CMSG_GET_THE_NODE_HASH_OF_NODE_SKIP);
      return 0;
    }
    travNodes.insert(getId());
    Crc_type resultHash;
    resultHash.process_bytes( "expression::InvocationExpressionSyntax", strlen("expression::InvocationExpressionSyntax"));
    common::WriteMsg::write(CMSG_GET_THE_NODE_HASH_OF_NODE_END,resultHash.checksum()); 
    nodeHashCache = resultHash.checksum();
    hashOk = true;
    return nodeHashCache;
  }

  void InvocationExpressionSyntax::save(io::BinaryIO &binIo,bool withVirtualBase  /*= true*/) const {
    ExpressionSyntax::save(binIo,false);

    binIo.writeUInt4(m_ArgumentList);
    binIo.writeUInt4(m_Expression);
    binIo.writeUInt4(m_LocalFunctionCall);
    binIo.writeUInt4(m_MethodCall);

  }

  void InvocationExpressionSyntax::load(io::BinaryIO &binIo, bool withVirtualBase /*= true*/) {
    ExpressionSyntax::load(binIo,false);

    m_ArgumentList =  binIo.readUInt4();
    if (m_ArgumentList != 0)
      setParentEdge(factory->getPointer(m_ArgumentList),edkInvocationExpressionSyntax_ArgumentList);

    m_Expression =  binIo.readUInt4();
    if (m_Expression != 0)
      setParentEdge(factory->getPointer(m_Expression),edkInvocationExpressionSyntax_Expression);

    m_LocalFunctionCall =  binIo.readUInt4();

    m_MethodCall =  binIo.readUInt4();

  }


}


}}}
