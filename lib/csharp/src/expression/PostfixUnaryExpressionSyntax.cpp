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
  PostfixUnaryExpressionSyntax::PostfixUnaryExpressionSyntax(NodeId _id, Factory *_factory) :
    ExpressionSyntax(_id, _factory),
    m_Operand(0),
    m_OverloadedOperatorCall(0)
  {
  }

  PostfixUnaryExpressionSyntax::~PostfixUnaryExpressionSyntax() {
  }

  void PostfixUnaryExpressionSyntax::prepareDelete(bool tryOnVirtualParent){
    removeOperand();
    removeOverloadedOperatorCall();
    expression::ExpressionSyntax::prepareDelete(false);
  }

  NodeKind PostfixUnaryExpressionSyntax::getNodeKind() const {
    return ndkPostfixUnaryExpressionSyntax;
  }

  expression::ExpressionSyntax* PostfixUnaryExpressionSyntax::getOperand() const {
    expression::ExpressionSyntax *_node = NULL;
    if (m_Operand != 0)
      _node = dynamic_cast<expression::ExpressionSyntax*>(factory->getPointer(m_Operand));
    if ( (_node == NULL) || factory->getIsFiltered(_node))
      return NULL;

    return _node;
  }

  structure::OperatorDeclarationSyntax* PostfixUnaryExpressionSyntax::getOverloadedOperatorCall() const {
    structure::OperatorDeclarationSyntax *_node = NULL;
    if (m_OverloadedOperatorCall != 0)
      _node = dynamic_cast<structure::OperatorDeclarationSyntax*>(factory->getPointer(m_OverloadedOperatorCall));
    if ( (_node == NULL) || factory->getIsFiltered(_node))
      return NULL;

    return _node;
  }

  bool PostfixUnaryExpressionSyntax::setEdge(EdgeKind edgeKind, NodeId edgeEnd, bool tryOnVirtualParent) {
    switch (edgeKind) {
      case edkPostfixUnaryExpressionSyntax_Operand:
        setOperand(edgeEnd);
        return true;
      case edkPostfixUnaryExpressionSyntax_OverloadedOperatorCall:
        setOverloadedOperatorCall(edgeEnd);
        return true;
      default:
        break;
    }
    if (expression::ExpressionSyntax::setEdge(edgeKind, edgeEnd, false)) {
      return true;
    }
    return false;
  }

  bool PostfixUnaryExpressionSyntax::removeEdge(EdgeKind edgeKind, NodeId edgeEnd, bool tryOnVirtualParent) {
    switch (edgeKind) {
      case edkPostfixUnaryExpressionSyntax_Operand:
        removeOperand();
        return true;
      case edkPostfixUnaryExpressionSyntax_OverloadedOperatorCall:
        removeOverloadedOperatorCall();
        return true;
      default:
        break;
    }
    if (expression::ExpressionSyntax::removeEdge(edgeKind, edgeEnd, false)) {
      return true;
    }
    return false;
  }

  void PostfixUnaryExpressionSyntax::setOperand(NodeId _id) {
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

      if (m_Operand) {
        removeParentEdge(m_Operand);
        if (factory->getExistsReverseEdges())
          factory->reverseEdges->removeEdge(m_Operand, m_id, edkPostfixUnaryExpressionSyntax_Operand);
      }
      m_Operand = _node->getId();
      if (m_Operand != 0)
        setParentEdge(factory->getPointer(m_Operand), edkPostfixUnaryExpressionSyntax_Operand);
      if (factory->getExistsReverseEdges())
        factory->reverseEdges->insertEdge(m_Operand, this->getId(), edkPostfixUnaryExpressionSyntax_Operand);
    } else {
      if (m_Operand) {
        throw CsharpException(COLUMBUS_LOCATION, CMSG_EX_CAN_T_SET_EDGE_TO_NULL);
      }
    }
  }

  void PostfixUnaryExpressionSyntax::setOperand(expression::ExpressionSyntax *_node) {
    if (_node == NULL)
      throw CsharpException(COLUMBUS_LOCATION, CMSG_EX_CAN_T_SET_EDGE_TO_NULL);

    setOperand(_node->getId());
  }

  void PostfixUnaryExpressionSyntax::removeOperand() {
      if (m_Operand) {
        removeParentEdge(m_Operand);
        if (factory->getExistsReverseEdges())
          factory->reverseEdges->removeEdge(m_Operand, m_id, edkPostfixUnaryExpressionSyntax_Operand);
      }
      m_Operand = 0;
  }

  void PostfixUnaryExpressionSyntax::setOverloadedOperatorCall(NodeId _id) {
    structure::OperatorDeclarationSyntax *_node = NULL;
    if (_id) {
      if (!factory->getExist(_id))
        throw CsharpException(COLUMBUS_LOCATION, CMSG_EX_THE_END_POINT_OF_THE_EDGE_DOES_NOT_EXIST);

      _node = dynamic_cast<structure::OperatorDeclarationSyntax*> (factory->getPointer(_id));
      if ( _node == NULL) {
        throw CsharpException(COLUMBUS_LOCATION, CMSG_EX_INVALID_NODE_KIND);
      }
      if (&(_node->getFactory()) != this->factory)
        throw CsharpException(COLUMBUS_LOCATION, CMSG_EX_THE_FACTORY_OF_NODES_DOES_NOT_MATCH );

      if (m_OverloadedOperatorCall) {
        if (factory->getExistsReverseEdges())
          factory->reverseEdges->removeEdge(m_OverloadedOperatorCall, m_id, edkPostfixUnaryExpressionSyntax_OverloadedOperatorCall);
      }
      m_OverloadedOperatorCall = _node->getId();
      if (factory->getExistsReverseEdges())
        factory->reverseEdges->insertEdge(m_OverloadedOperatorCall, this->getId(), edkPostfixUnaryExpressionSyntax_OverloadedOperatorCall);
    } else {
      if (m_OverloadedOperatorCall) {
        throw CsharpException(COLUMBUS_LOCATION, CMSG_EX_CAN_T_SET_EDGE_TO_NULL);
      }
    }
  }

  void PostfixUnaryExpressionSyntax::setOverloadedOperatorCall(structure::OperatorDeclarationSyntax *_node) {
    if (_node == NULL)
      throw CsharpException(COLUMBUS_LOCATION, CMSG_EX_CAN_T_SET_EDGE_TO_NULL);

    setOverloadedOperatorCall(_node->getId());
  }

  void PostfixUnaryExpressionSyntax::removeOverloadedOperatorCall() {
      if (m_OverloadedOperatorCall) {
        if (factory->getExistsReverseEdges())
          factory->reverseEdges->removeEdge(m_OverloadedOperatorCall, m_id, edkPostfixUnaryExpressionSyntax_OverloadedOperatorCall);
      }
      m_OverloadedOperatorCall = 0;
  }

  void PostfixUnaryExpressionSyntax::accept(Visitor &visitor) const {
    visitor.visit(*this);
  }

  void PostfixUnaryExpressionSyntax::acceptEnd(Visitor &visitor) const {
    visitor.visitEnd(*this);
  }

  double PostfixUnaryExpressionSyntax::getSimilarity(const base::Base& base){
    if(base.getNodeKind() == getNodeKind()) {
      return 1.0;
    } else {
      return 0.0;
    }
  }

  void PostfixUnaryExpressionSyntax::swapStringTable(RefDistributorStrTable& newStrTable, std::map<Key,Key>& oldAndNewStrKeyMap ){
    std::map<Key,Key>::iterator foundKeyId;

      m_position.swapStringTable(newStrTable,oldAndNewStrKeyMap);

  }

  NodeHashType PostfixUnaryExpressionSyntax::getHash(std::set<NodeId>& travNodes) const {
    if (hashOk) return nodeHashCache;
    common::WriteMsg::write(CMSG_GET_THE_NODE_HASH_OF_NODE_BEGIN,this->getId()); 
    if (travNodes.count(getId())>0) {
      common::WriteMsg::write(CMSG_GET_THE_NODE_HASH_OF_NODE_SKIP);
      return 0;
    }
    travNodes.insert(getId());
    Crc_type resultHash;
    resultHash.process_bytes( "expression::PostfixUnaryExpressionSyntax", strlen("expression::PostfixUnaryExpressionSyntax"));
    common::WriteMsg::write(CMSG_GET_THE_NODE_HASH_OF_NODE_END,resultHash.checksum()); 
    nodeHashCache = resultHash.checksum();
    hashOk = true;
    return nodeHashCache;
  }

  void PostfixUnaryExpressionSyntax::save(io::BinaryIO &binIo,bool withVirtualBase  /*= true*/) const {
    ExpressionSyntax::save(binIo,false);

    binIo.writeUInt4(m_Operand);
    binIo.writeUInt4(m_OverloadedOperatorCall);

  }

  void PostfixUnaryExpressionSyntax::load(io::BinaryIO &binIo, bool withVirtualBase /*= true*/) {
    ExpressionSyntax::load(binIo,false);

    m_Operand =  binIo.readUInt4();
    if (m_Operand != 0)
      setParentEdge(factory->getPointer(m_Operand),edkPostfixUnaryExpressionSyntax_Operand);

    m_OverloadedOperatorCall =  binIo.readUInt4();

  }


}


}}}
