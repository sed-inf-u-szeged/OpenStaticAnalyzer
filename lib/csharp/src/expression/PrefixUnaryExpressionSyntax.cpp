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
  PrefixUnaryExpressionSyntax::PrefixUnaryExpressionSyntax(NodeId _id, Factory *_factory) :
    ExpressionSyntax(_id, _factory),
    m_Operand(0),
    m_OverloadedOperatorCall(0)
  {
  }

  PrefixUnaryExpressionSyntax::~PrefixUnaryExpressionSyntax() {
  }

  void PrefixUnaryExpressionSyntax::prepareDelete(bool tryOnVirtualParent){
    removeOperand();
    removeOverloadedOperatorCall();
    expression::ExpressionSyntax::prepareDelete(false);
  }

  NodeKind PrefixUnaryExpressionSyntax::getNodeKind() const {
    return ndkPrefixUnaryExpressionSyntax;
  }

  expression::ExpressionSyntax* PrefixUnaryExpressionSyntax::getOperand() const {
    expression::ExpressionSyntax *_node = NULL;
    if (m_Operand != 0)
      _node = dynamic_cast<expression::ExpressionSyntax*>(factory->getPointer(m_Operand));
    if ( (_node == NULL) || factory->getIsFiltered(_node))
      return NULL;

    return _node;
  }

  structure::OperatorDeclarationSyntax* PrefixUnaryExpressionSyntax::getOverloadedOperatorCall() const {
    structure::OperatorDeclarationSyntax *_node = NULL;
    if (m_OverloadedOperatorCall != 0)
      _node = dynamic_cast<structure::OperatorDeclarationSyntax*>(factory->getPointer(m_OverloadedOperatorCall));
    if ( (_node == NULL) || factory->getIsFiltered(_node))
      return NULL;

    return _node;
  }

  bool PrefixUnaryExpressionSyntax::setEdge(EdgeKind edgeKind, NodeId edgeEnd, bool tryOnVirtualParent) {
    switch (edgeKind) {
      case edkPrefixUnaryExpressionSyntax_Operand:
        setOperand(edgeEnd);
        return true;
      case edkPrefixUnaryExpressionSyntax_OverloadedOperatorCall:
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

  bool PrefixUnaryExpressionSyntax::removeEdge(EdgeKind edgeKind, NodeId edgeEnd, bool tryOnVirtualParent) {
    switch (edgeKind) {
      case edkPrefixUnaryExpressionSyntax_Operand:
        removeOperand();
        return true;
      case edkPrefixUnaryExpressionSyntax_OverloadedOperatorCall:
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

  void PrefixUnaryExpressionSyntax::setOperand(NodeId _id) {
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
          factory->reverseEdges->removeEdge(m_Operand, m_id, edkPrefixUnaryExpressionSyntax_Operand);
      }
      m_Operand = _node->getId();
      if (m_Operand != 0)
        setParentEdge(factory->getPointer(m_Operand), edkPrefixUnaryExpressionSyntax_Operand);
      if (factory->getExistsReverseEdges())
        factory->reverseEdges->insertEdge(m_Operand, this->getId(), edkPrefixUnaryExpressionSyntax_Operand);
    } else {
      if (m_Operand) {
        throw CsharpException(COLUMBUS_LOCATION, CMSG_EX_CAN_T_SET_EDGE_TO_NULL);
      }
    }
  }

  void PrefixUnaryExpressionSyntax::setOperand(expression::ExpressionSyntax *_node) {
    if (_node == NULL)
      throw CsharpException(COLUMBUS_LOCATION, CMSG_EX_CAN_T_SET_EDGE_TO_NULL);

    setOperand(_node->getId());
  }

  void PrefixUnaryExpressionSyntax::removeOperand() {
      if (m_Operand) {
        removeParentEdge(m_Operand);
        if (factory->getExistsReverseEdges())
          factory->reverseEdges->removeEdge(m_Operand, m_id, edkPrefixUnaryExpressionSyntax_Operand);
      }
      m_Operand = 0;
  }

  void PrefixUnaryExpressionSyntax::setOverloadedOperatorCall(NodeId _id) {
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
          factory->reverseEdges->removeEdge(m_OverloadedOperatorCall, m_id, edkPrefixUnaryExpressionSyntax_OverloadedOperatorCall);
      }
      m_OverloadedOperatorCall = _node->getId();
      if (factory->getExistsReverseEdges())
        factory->reverseEdges->insertEdge(m_OverloadedOperatorCall, this->getId(), edkPrefixUnaryExpressionSyntax_OverloadedOperatorCall);
    } else {
      if (m_OverloadedOperatorCall) {
        throw CsharpException(COLUMBUS_LOCATION, CMSG_EX_CAN_T_SET_EDGE_TO_NULL);
      }
    }
  }

  void PrefixUnaryExpressionSyntax::setOverloadedOperatorCall(structure::OperatorDeclarationSyntax *_node) {
    if (_node == NULL)
      throw CsharpException(COLUMBUS_LOCATION, CMSG_EX_CAN_T_SET_EDGE_TO_NULL);

    setOverloadedOperatorCall(_node->getId());
  }

  void PrefixUnaryExpressionSyntax::removeOverloadedOperatorCall() {
      if (m_OverloadedOperatorCall) {
        if (factory->getExistsReverseEdges())
          factory->reverseEdges->removeEdge(m_OverloadedOperatorCall, m_id, edkPrefixUnaryExpressionSyntax_OverloadedOperatorCall);
      }
      m_OverloadedOperatorCall = 0;
  }

  void PrefixUnaryExpressionSyntax::accept(Visitor &visitor) const {
    visitor.visit(*this);
  }

  void PrefixUnaryExpressionSyntax::acceptEnd(Visitor &visitor) const {
    visitor.visitEnd(*this);
  }

  double PrefixUnaryExpressionSyntax::getSimilarity(const base::Base& base){
    if(base.getNodeKind() == getNodeKind()) {
      return 1.0;
    } else {
      return 0.0;
    }
  }

  void PrefixUnaryExpressionSyntax::swapStringTable(RefDistributorStrTable& newStrTable, std::map<Key,Key>& oldAndNewStrKeyMap ){
    std::map<Key,Key>::iterator foundKeyId;

      m_position.swapStringTable(newStrTable,oldAndNewStrKeyMap);

  }

  NodeHashType PrefixUnaryExpressionSyntax::getHash(std::set<NodeId>& travNodes) const {
    if (hashOk) return nodeHashCache;
    common::WriteMsg::write(CMSG_GET_THE_NODE_HASH_OF_NODE_BEGIN,this->getId()); 
    if (travNodes.count(getId())>0) {
      common::WriteMsg::write(CMSG_GET_THE_NODE_HASH_OF_NODE_SKIP);
      return 0;
    }
    travNodes.insert(getId());
    Crc_type resultHash;
    resultHash.process_bytes( "expression::PrefixUnaryExpressionSyntax", strlen("expression::PrefixUnaryExpressionSyntax"));
    common::WriteMsg::write(CMSG_GET_THE_NODE_HASH_OF_NODE_END,resultHash.checksum()); 
    nodeHashCache = resultHash.checksum();
    hashOk = true;
    return nodeHashCache;
  }

  void PrefixUnaryExpressionSyntax::save(io::BinaryIO &binIo,bool withVirtualBase  /*= true*/) const {
    ExpressionSyntax::save(binIo,false);

    binIo.writeUInt4(m_Operand);
    binIo.writeUInt4(m_OverloadedOperatorCall);

  }

  void PrefixUnaryExpressionSyntax::load(io::BinaryIO &binIo, bool withVirtualBase /*= true*/) {
    ExpressionSyntax::load(binIo,false);

    m_Operand =  binIo.readUInt4();
    if (m_Operand != 0)
      setParentEdge(factory->getPointer(m_Operand),edkPrefixUnaryExpressionSyntax_Operand);

    m_OverloadedOperatorCall =  binIo.readUInt4();

  }


}


}}}
