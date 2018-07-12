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
  BinaryExpressionSyntax::BinaryExpressionSyntax(NodeId _id, Factory *_factory) :
    ExpressionSyntax(_id, _factory),
    m_Left(0),
    m_OverloadedOperatorCall(0),
    m_Right(0)
  {
  }

  BinaryExpressionSyntax::~BinaryExpressionSyntax() {
  }

  void BinaryExpressionSyntax::prepareDelete(bool tryOnVirtualParent){
    removeLeft();
    removeOverloadedOperatorCall();
    removeRight();
    expression::ExpressionSyntax::prepareDelete(false);
  }

  NodeKind BinaryExpressionSyntax::getNodeKind() const {
    return ndkBinaryExpressionSyntax;
  }

  expression::ExpressionSyntax* BinaryExpressionSyntax::getLeft() const {
    expression::ExpressionSyntax *_node = NULL;
    if (m_Left != 0)
      _node = dynamic_cast<expression::ExpressionSyntax*>(factory->getPointer(m_Left));
    if ( (_node == NULL) || factory->getIsFiltered(_node))
      return NULL;

    return _node;
  }

  structure::OperatorDeclarationSyntax* BinaryExpressionSyntax::getOverloadedOperatorCall() const {
    structure::OperatorDeclarationSyntax *_node = NULL;
    if (m_OverloadedOperatorCall != 0)
      _node = dynamic_cast<structure::OperatorDeclarationSyntax*>(factory->getPointer(m_OverloadedOperatorCall));
    if ( (_node == NULL) || factory->getIsFiltered(_node))
      return NULL;

    return _node;
  }

  expression::ExpressionSyntax* BinaryExpressionSyntax::getRight() const {
    expression::ExpressionSyntax *_node = NULL;
    if (m_Right != 0)
      _node = dynamic_cast<expression::ExpressionSyntax*>(factory->getPointer(m_Right));
    if ( (_node == NULL) || factory->getIsFiltered(_node))
      return NULL;

    return _node;
  }

  bool BinaryExpressionSyntax::setEdge(EdgeKind edgeKind, NodeId edgeEnd, bool tryOnVirtualParent) {
    switch (edgeKind) {
      case edkBinaryExpressionSyntax_Left:
        setLeft(edgeEnd);
        return true;
      case edkBinaryExpressionSyntax_OverloadedOperatorCall:
        setOverloadedOperatorCall(edgeEnd);
        return true;
      case edkBinaryExpressionSyntax_Right:
        setRight(edgeEnd);
        return true;
      default:
        break;
    }
    if (expression::ExpressionSyntax::setEdge(edgeKind, edgeEnd, false)) {
      return true;
    }
    return false;
  }

  bool BinaryExpressionSyntax::removeEdge(EdgeKind edgeKind, NodeId edgeEnd, bool tryOnVirtualParent) {
    switch (edgeKind) {
      case edkBinaryExpressionSyntax_Left:
        removeLeft();
        return true;
      case edkBinaryExpressionSyntax_OverloadedOperatorCall:
        removeOverloadedOperatorCall();
        return true;
      case edkBinaryExpressionSyntax_Right:
        removeRight();
        return true;
      default:
        break;
    }
    if (expression::ExpressionSyntax::removeEdge(edgeKind, edgeEnd, false)) {
      return true;
    }
    return false;
  }

  void BinaryExpressionSyntax::setLeft(NodeId _id) {
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

      if (m_Left) {
        removeParentEdge(m_Left);
        if (factory->getExistsReverseEdges())
          factory->reverseEdges->removeEdge(m_Left, m_id, edkBinaryExpressionSyntax_Left);
      }
      m_Left = _node->getId();
      if (m_Left != 0)
        setParentEdge(factory->getPointer(m_Left), edkBinaryExpressionSyntax_Left);
      if (factory->getExistsReverseEdges())
        factory->reverseEdges->insertEdge(m_Left, this->getId(), edkBinaryExpressionSyntax_Left);
    } else {
      if (m_Left) {
        throw CsharpException(COLUMBUS_LOCATION, CMSG_EX_CAN_T_SET_EDGE_TO_NULL);
      }
    }
  }

  void BinaryExpressionSyntax::setLeft(expression::ExpressionSyntax *_node) {
    if (_node == NULL)
      throw CsharpException(COLUMBUS_LOCATION, CMSG_EX_CAN_T_SET_EDGE_TO_NULL);

    setLeft(_node->getId());
  }

  void BinaryExpressionSyntax::removeLeft() {
      if (m_Left) {
        removeParentEdge(m_Left);
        if (factory->getExistsReverseEdges())
          factory->reverseEdges->removeEdge(m_Left, m_id, edkBinaryExpressionSyntax_Left);
      }
      m_Left = 0;
  }

  void BinaryExpressionSyntax::setOverloadedOperatorCall(NodeId _id) {
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
          factory->reverseEdges->removeEdge(m_OverloadedOperatorCall, m_id, edkBinaryExpressionSyntax_OverloadedOperatorCall);
      }
      m_OverloadedOperatorCall = _node->getId();
      if (factory->getExistsReverseEdges())
        factory->reverseEdges->insertEdge(m_OverloadedOperatorCall, this->getId(), edkBinaryExpressionSyntax_OverloadedOperatorCall);
    } else {
      if (m_OverloadedOperatorCall) {
        throw CsharpException(COLUMBUS_LOCATION, CMSG_EX_CAN_T_SET_EDGE_TO_NULL);
      }
    }
  }

  void BinaryExpressionSyntax::setOverloadedOperatorCall(structure::OperatorDeclarationSyntax *_node) {
    if (_node == NULL)
      throw CsharpException(COLUMBUS_LOCATION, CMSG_EX_CAN_T_SET_EDGE_TO_NULL);

    setOverloadedOperatorCall(_node->getId());
  }

  void BinaryExpressionSyntax::removeOverloadedOperatorCall() {
      if (m_OverloadedOperatorCall) {
        if (factory->getExistsReverseEdges())
          factory->reverseEdges->removeEdge(m_OverloadedOperatorCall, m_id, edkBinaryExpressionSyntax_OverloadedOperatorCall);
      }
      m_OverloadedOperatorCall = 0;
  }

  void BinaryExpressionSyntax::setRight(NodeId _id) {
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

      if (m_Right) {
        removeParentEdge(m_Right);
        if (factory->getExistsReverseEdges())
          factory->reverseEdges->removeEdge(m_Right, m_id, edkBinaryExpressionSyntax_Right);
      }
      m_Right = _node->getId();
      if (m_Right != 0)
        setParentEdge(factory->getPointer(m_Right), edkBinaryExpressionSyntax_Right);
      if (factory->getExistsReverseEdges())
        factory->reverseEdges->insertEdge(m_Right, this->getId(), edkBinaryExpressionSyntax_Right);
    } else {
      if (m_Right) {
        throw CsharpException(COLUMBUS_LOCATION, CMSG_EX_CAN_T_SET_EDGE_TO_NULL);
      }
    }
  }

  void BinaryExpressionSyntax::setRight(expression::ExpressionSyntax *_node) {
    if (_node == NULL)
      throw CsharpException(COLUMBUS_LOCATION, CMSG_EX_CAN_T_SET_EDGE_TO_NULL);

    setRight(_node->getId());
  }

  void BinaryExpressionSyntax::removeRight() {
      if (m_Right) {
        removeParentEdge(m_Right);
        if (factory->getExistsReverseEdges())
          factory->reverseEdges->removeEdge(m_Right, m_id, edkBinaryExpressionSyntax_Right);
      }
      m_Right = 0;
  }

  void BinaryExpressionSyntax::accept(Visitor &visitor) const {
    visitor.visit(*this);
  }

  void BinaryExpressionSyntax::acceptEnd(Visitor &visitor) const {
    visitor.visitEnd(*this);
  }

  double BinaryExpressionSyntax::getSimilarity(const base::Base& base){
    if(base.getNodeKind() == getNodeKind()) {
      return 1.0;
    } else {
      return 0.0;
    }
  }

  void BinaryExpressionSyntax::swapStringTable(RefDistributorStrTable& newStrTable, std::map<Key,Key>& oldAndNewStrKeyMap ){
    std::map<Key,Key>::iterator foundKeyId;

      m_position.swapStringTable(newStrTable,oldAndNewStrKeyMap);

  }

  NodeHashType BinaryExpressionSyntax::getHash(std::set<NodeId>& travNodes) const {
    if (hashOk) return nodeHashCache;
    common::WriteMsg::write(CMSG_GET_THE_NODE_HASH_OF_NODE_BEGIN,this->getId()); 
    if (travNodes.count(getId())>0) {
      common::WriteMsg::write(CMSG_GET_THE_NODE_HASH_OF_NODE_SKIP);
      return 0;
    }
    travNodes.insert(getId());
    Crc_type resultHash;
    resultHash.process_bytes( "expression::BinaryExpressionSyntax", strlen("expression::BinaryExpressionSyntax"));
    common::WriteMsg::write(CMSG_GET_THE_NODE_HASH_OF_NODE_END,resultHash.checksum()); 
    nodeHashCache = resultHash.checksum();
    hashOk = true;
    return nodeHashCache;
  }

  void BinaryExpressionSyntax::save(io::BinaryIO &binIo,bool withVirtualBase  /*= true*/) const {
    ExpressionSyntax::save(binIo,false);

    binIo.writeUInt4(m_Left);
    binIo.writeUInt4(m_OverloadedOperatorCall);
    binIo.writeUInt4(m_Right);

  }

  void BinaryExpressionSyntax::load(io::BinaryIO &binIo, bool withVirtualBase /*= true*/) {
    ExpressionSyntax::load(binIo,false);

    m_Left =  binIo.readUInt4();
    if (m_Left != 0)
      setParentEdge(factory->getPointer(m_Left),edkBinaryExpressionSyntax_Left);

    m_OverloadedOperatorCall =  binIo.readUInt4();

    m_Right =  binIo.readUInt4();
    if (m_Right != 0)
      setParentEdge(factory->getPointer(m_Right),edkBinaryExpressionSyntax_Right);

  }


}


}}}
