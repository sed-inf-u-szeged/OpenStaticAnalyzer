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
  RangeExpressionSyntax::RangeExpressionSyntax(NodeId _id, Factory *_factory) :
    ExpressionSyntax(_id, _factory),
    m_LeftOperand(0),
    m_RightOperand(0)
  {
  }

  RangeExpressionSyntax::~RangeExpressionSyntax() {
  }

  void RangeExpressionSyntax::prepareDelete(bool tryOnVirtualParent){
    removeLeftOperand();
    removeRightOperand();
    expression::ExpressionSyntax::prepareDelete(false);
  }

  NodeKind RangeExpressionSyntax::getNodeKind() const {
    return ndkRangeExpressionSyntax;
  }

  expression::ExpressionSyntax* RangeExpressionSyntax::getLeftOperand() const {
    expression::ExpressionSyntax *_node = NULL;
    if (m_LeftOperand != 0)
      _node = dynamic_cast<expression::ExpressionSyntax*>(factory->getPointer(m_LeftOperand));
    if ( (_node == NULL) || factory->getIsFiltered(_node))
      return NULL;

    return _node;
  }

  expression::ExpressionSyntax* RangeExpressionSyntax::getRightOperand() const {
    expression::ExpressionSyntax *_node = NULL;
    if (m_RightOperand != 0)
      _node = dynamic_cast<expression::ExpressionSyntax*>(factory->getPointer(m_RightOperand));
    if ( (_node == NULL) || factory->getIsFiltered(_node))
      return NULL;

    return _node;
  }

  bool RangeExpressionSyntax::setEdge(EdgeKind edgeKind, NodeId edgeEnd, bool tryOnVirtualParent) {
    switch (edgeKind) {
      case edkRangeExpressionSyntax_LeftOperand:
        setLeftOperand(edgeEnd);
        return true;
      case edkRangeExpressionSyntax_RightOperand:
        setRightOperand(edgeEnd);
        return true;
      default:
        break;
    }
    if (expression::ExpressionSyntax::setEdge(edgeKind, edgeEnd, false)) {
      return true;
    }
    return false;
  }

  bool RangeExpressionSyntax::removeEdge(EdgeKind edgeKind, NodeId edgeEnd, bool tryOnVirtualParent) {
    switch (edgeKind) {
      case edkRangeExpressionSyntax_LeftOperand:
        removeLeftOperand();
        return true;
      case edkRangeExpressionSyntax_RightOperand:
        removeRightOperand();
        return true;
      default:
        break;
    }
    if (expression::ExpressionSyntax::removeEdge(edgeKind, edgeEnd, false)) {
      return true;
    }
    return false;
  }

  void RangeExpressionSyntax::setLeftOperand(NodeId _id) {
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

      if (m_LeftOperand) {
        removeParentEdge(m_LeftOperand);
        if (factory->getExistsReverseEdges())
          factory->reverseEdges->removeEdge(m_LeftOperand, m_id, edkRangeExpressionSyntax_LeftOperand);
      }
      m_LeftOperand = _node->getId();
      if (m_LeftOperand != 0)
        setParentEdge(factory->getPointer(m_LeftOperand), edkRangeExpressionSyntax_LeftOperand);
      if (factory->getExistsReverseEdges())
        factory->reverseEdges->insertEdge(m_LeftOperand, this->getId(), edkRangeExpressionSyntax_LeftOperand);
    } else {
      if (m_LeftOperand) {
        throw CsharpException(COLUMBUS_LOCATION, CMSG_EX_CAN_T_SET_EDGE_TO_NULL);
      }
    }
  }

  void RangeExpressionSyntax::setLeftOperand(expression::ExpressionSyntax *_node) {
    if (_node == NULL)
      throw CsharpException(COLUMBUS_LOCATION, CMSG_EX_CAN_T_SET_EDGE_TO_NULL);

    setLeftOperand(_node->getId());
  }

  void RangeExpressionSyntax::removeLeftOperand() {
      if (m_LeftOperand) {
        removeParentEdge(m_LeftOperand);
        if (factory->getExistsReverseEdges())
          factory->reverseEdges->removeEdge(m_LeftOperand, m_id, edkRangeExpressionSyntax_LeftOperand);
      }
      m_LeftOperand = 0;
  }

  void RangeExpressionSyntax::setRightOperand(NodeId _id) {
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

      if (m_RightOperand) {
        removeParentEdge(m_RightOperand);
        if (factory->getExistsReverseEdges())
          factory->reverseEdges->removeEdge(m_RightOperand, m_id, edkRangeExpressionSyntax_RightOperand);
      }
      m_RightOperand = _node->getId();
      if (m_RightOperand != 0)
        setParentEdge(factory->getPointer(m_RightOperand), edkRangeExpressionSyntax_RightOperand);
      if (factory->getExistsReverseEdges())
        factory->reverseEdges->insertEdge(m_RightOperand, this->getId(), edkRangeExpressionSyntax_RightOperand);
    } else {
      if (m_RightOperand) {
        throw CsharpException(COLUMBUS_LOCATION, CMSG_EX_CAN_T_SET_EDGE_TO_NULL);
      }
    }
  }

  void RangeExpressionSyntax::setRightOperand(expression::ExpressionSyntax *_node) {
    if (_node == NULL)
      throw CsharpException(COLUMBUS_LOCATION, CMSG_EX_CAN_T_SET_EDGE_TO_NULL);

    setRightOperand(_node->getId());
  }

  void RangeExpressionSyntax::removeRightOperand() {
      if (m_RightOperand) {
        removeParentEdge(m_RightOperand);
        if (factory->getExistsReverseEdges())
          factory->reverseEdges->removeEdge(m_RightOperand, m_id, edkRangeExpressionSyntax_RightOperand);
      }
      m_RightOperand = 0;
  }

  void RangeExpressionSyntax::accept(Visitor &visitor) const {
    visitor.visit(*this);
  }

  void RangeExpressionSyntax::acceptEnd(Visitor &visitor) const {
    visitor.visitEnd(*this);
  }

  double RangeExpressionSyntax::getSimilarity(const base::Base& base){
    if(base.getNodeKind() == getNodeKind()) {
      return 1.0;
    } else {
      return 0.0;
    }
  }

  void RangeExpressionSyntax::swapStringTable(RefDistributorStrTable& newStrTable, std::map<Key,Key>& oldAndNewStrKeyMap ){
    std::map<Key,Key>::iterator foundKeyId;

      m_position.swapStringTable(newStrTable,oldAndNewStrKeyMap);

  }

  NodeHashType RangeExpressionSyntax::getHash(std::set<NodeId>& travNodes) const {
    if (hashOk) return nodeHashCache;
    common::WriteMsg::write(CMSG_GET_THE_NODE_HASH_OF_NODE_BEGIN,this->getId()); 
    if (travNodes.count(getId())>0) {
      common::WriteMsg::write(CMSG_GET_THE_NODE_HASH_OF_NODE_SKIP);
      return 0;
    }
    travNodes.insert(getId());
    Crc_type resultHash;
    resultHash.process_bytes( "expression::RangeExpressionSyntax", strlen("expression::RangeExpressionSyntax"));
    common::WriteMsg::write(CMSG_GET_THE_NODE_HASH_OF_NODE_END,resultHash.checksum()); 
    nodeHashCache = resultHash.checksum();
    hashOk = true;
    return nodeHashCache;
  }

  void RangeExpressionSyntax::save(io::BinaryIO &binIo,bool withVirtualBase  /*= true*/) const {
    ExpressionSyntax::save(binIo,false);

    binIo.writeUInt4(m_LeftOperand);
    binIo.writeUInt4(m_RightOperand);

  }

  void RangeExpressionSyntax::load(io::BinaryIO &binIo, bool withVirtualBase /*= true*/) {
    ExpressionSyntax::load(binIo,false);

    m_LeftOperand =  binIo.readUInt4();
    if (m_LeftOperand != 0)
      setParentEdge(factory->getPointer(m_LeftOperand),edkRangeExpressionSyntax_LeftOperand);

    m_RightOperand =  binIo.readUInt4();
    if (m_RightOperand != 0)
      setParentEdge(factory->getPointer(m_RightOperand),edkRangeExpressionSyntax_RightOperand);

  }


}


}}}
