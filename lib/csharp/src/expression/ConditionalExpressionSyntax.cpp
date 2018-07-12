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
  ConditionalExpressionSyntax::ConditionalExpressionSyntax(NodeId _id, Factory *_factory) :
    ExpressionSyntax(_id, _factory),
    m_Condition(0),
    m_WhenFalse(0),
    m_WhenTrue(0)
  {
  }

  ConditionalExpressionSyntax::~ConditionalExpressionSyntax() {
  }

  void ConditionalExpressionSyntax::prepareDelete(bool tryOnVirtualParent){
    removeCondition();
    removeWhenFalse();
    removeWhenTrue();
    expression::ExpressionSyntax::prepareDelete(false);
  }

  NodeKind ConditionalExpressionSyntax::getNodeKind() const {
    return ndkConditionalExpressionSyntax;
  }

  expression::ExpressionSyntax* ConditionalExpressionSyntax::getCondition() const {
    expression::ExpressionSyntax *_node = NULL;
    if (m_Condition != 0)
      _node = dynamic_cast<expression::ExpressionSyntax*>(factory->getPointer(m_Condition));
    if ( (_node == NULL) || factory->getIsFiltered(_node))
      return NULL;

    return _node;
  }

  expression::ExpressionSyntax* ConditionalExpressionSyntax::getWhenFalse() const {
    expression::ExpressionSyntax *_node = NULL;
    if (m_WhenFalse != 0)
      _node = dynamic_cast<expression::ExpressionSyntax*>(factory->getPointer(m_WhenFalse));
    if ( (_node == NULL) || factory->getIsFiltered(_node))
      return NULL;

    return _node;
  }

  expression::ExpressionSyntax* ConditionalExpressionSyntax::getWhenTrue() const {
    expression::ExpressionSyntax *_node = NULL;
    if (m_WhenTrue != 0)
      _node = dynamic_cast<expression::ExpressionSyntax*>(factory->getPointer(m_WhenTrue));
    if ( (_node == NULL) || factory->getIsFiltered(_node))
      return NULL;

    return _node;
  }

  bool ConditionalExpressionSyntax::setEdge(EdgeKind edgeKind, NodeId edgeEnd, bool tryOnVirtualParent) {
    switch (edgeKind) {
      case edkConditionalExpressionSyntax_Condition:
        setCondition(edgeEnd);
        return true;
      case edkConditionalExpressionSyntax_WhenFalse:
        setWhenFalse(edgeEnd);
        return true;
      case edkConditionalExpressionSyntax_WhenTrue:
        setWhenTrue(edgeEnd);
        return true;
      default:
        break;
    }
    if (expression::ExpressionSyntax::setEdge(edgeKind, edgeEnd, false)) {
      return true;
    }
    return false;
  }

  bool ConditionalExpressionSyntax::removeEdge(EdgeKind edgeKind, NodeId edgeEnd, bool tryOnVirtualParent) {
    switch (edgeKind) {
      case edkConditionalExpressionSyntax_Condition:
        removeCondition();
        return true;
      case edkConditionalExpressionSyntax_WhenFalse:
        removeWhenFalse();
        return true;
      case edkConditionalExpressionSyntax_WhenTrue:
        removeWhenTrue();
        return true;
      default:
        break;
    }
    if (expression::ExpressionSyntax::removeEdge(edgeKind, edgeEnd, false)) {
      return true;
    }
    return false;
  }

  void ConditionalExpressionSyntax::setCondition(NodeId _id) {
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

      if (m_Condition) {
        removeParentEdge(m_Condition);
        if (factory->getExistsReverseEdges())
          factory->reverseEdges->removeEdge(m_Condition, m_id, edkConditionalExpressionSyntax_Condition);
      }
      m_Condition = _node->getId();
      if (m_Condition != 0)
        setParentEdge(factory->getPointer(m_Condition), edkConditionalExpressionSyntax_Condition);
      if (factory->getExistsReverseEdges())
        factory->reverseEdges->insertEdge(m_Condition, this->getId(), edkConditionalExpressionSyntax_Condition);
    } else {
      if (m_Condition) {
        throw CsharpException(COLUMBUS_LOCATION, CMSG_EX_CAN_T_SET_EDGE_TO_NULL);
      }
    }
  }

  void ConditionalExpressionSyntax::setCondition(expression::ExpressionSyntax *_node) {
    if (_node == NULL)
      throw CsharpException(COLUMBUS_LOCATION, CMSG_EX_CAN_T_SET_EDGE_TO_NULL);

    setCondition(_node->getId());
  }

  void ConditionalExpressionSyntax::removeCondition() {
      if (m_Condition) {
        removeParentEdge(m_Condition);
        if (factory->getExistsReverseEdges())
          factory->reverseEdges->removeEdge(m_Condition, m_id, edkConditionalExpressionSyntax_Condition);
      }
      m_Condition = 0;
  }

  void ConditionalExpressionSyntax::setWhenFalse(NodeId _id) {
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

      if (m_WhenFalse) {
        removeParentEdge(m_WhenFalse);
        if (factory->getExistsReverseEdges())
          factory->reverseEdges->removeEdge(m_WhenFalse, m_id, edkConditionalExpressionSyntax_WhenFalse);
      }
      m_WhenFalse = _node->getId();
      if (m_WhenFalse != 0)
        setParentEdge(factory->getPointer(m_WhenFalse), edkConditionalExpressionSyntax_WhenFalse);
      if (factory->getExistsReverseEdges())
        factory->reverseEdges->insertEdge(m_WhenFalse, this->getId(), edkConditionalExpressionSyntax_WhenFalse);
    } else {
      if (m_WhenFalse) {
        throw CsharpException(COLUMBUS_LOCATION, CMSG_EX_CAN_T_SET_EDGE_TO_NULL);
      }
    }
  }

  void ConditionalExpressionSyntax::setWhenFalse(expression::ExpressionSyntax *_node) {
    if (_node == NULL)
      throw CsharpException(COLUMBUS_LOCATION, CMSG_EX_CAN_T_SET_EDGE_TO_NULL);

    setWhenFalse(_node->getId());
  }

  void ConditionalExpressionSyntax::removeWhenFalse() {
      if (m_WhenFalse) {
        removeParentEdge(m_WhenFalse);
        if (factory->getExistsReverseEdges())
          factory->reverseEdges->removeEdge(m_WhenFalse, m_id, edkConditionalExpressionSyntax_WhenFalse);
      }
      m_WhenFalse = 0;
  }

  void ConditionalExpressionSyntax::setWhenTrue(NodeId _id) {
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

      if (m_WhenTrue) {
        removeParentEdge(m_WhenTrue);
        if (factory->getExistsReverseEdges())
          factory->reverseEdges->removeEdge(m_WhenTrue, m_id, edkConditionalExpressionSyntax_WhenTrue);
      }
      m_WhenTrue = _node->getId();
      if (m_WhenTrue != 0)
        setParentEdge(factory->getPointer(m_WhenTrue), edkConditionalExpressionSyntax_WhenTrue);
      if (factory->getExistsReverseEdges())
        factory->reverseEdges->insertEdge(m_WhenTrue, this->getId(), edkConditionalExpressionSyntax_WhenTrue);
    } else {
      if (m_WhenTrue) {
        throw CsharpException(COLUMBUS_LOCATION, CMSG_EX_CAN_T_SET_EDGE_TO_NULL);
      }
    }
  }

  void ConditionalExpressionSyntax::setWhenTrue(expression::ExpressionSyntax *_node) {
    if (_node == NULL)
      throw CsharpException(COLUMBUS_LOCATION, CMSG_EX_CAN_T_SET_EDGE_TO_NULL);

    setWhenTrue(_node->getId());
  }

  void ConditionalExpressionSyntax::removeWhenTrue() {
      if (m_WhenTrue) {
        removeParentEdge(m_WhenTrue);
        if (factory->getExistsReverseEdges())
          factory->reverseEdges->removeEdge(m_WhenTrue, m_id, edkConditionalExpressionSyntax_WhenTrue);
      }
      m_WhenTrue = 0;
  }

  void ConditionalExpressionSyntax::accept(Visitor &visitor) const {
    visitor.visit(*this);
  }

  void ConditionalExpressionSyntax::acceptEnd(Visitor &visitor) const {
    visitor.visitEnd(*this);
  }

  double ConditionalExpressionSyntax::getSimilarity(const base::Base& base){
    if(base.getNodeKind() == getNodeKind()) {
      return 1.0;
    } else {
      return 0.0;
    }
  }

  void ConditionalExpressionSyntax::swapStringTable(RefDistributorStrTable& newStrTable, std::map<Key,Key>& oldAndNewStrKeyMap ){
    std::map<Key,Key>::iterator foundKeyId;

      m_position.swapStringTable(newStrTable,oldAndNewStrKeyMap);

  }

  NodeHashType ConditionalExpressionSyntax::getHash(std::set<NodeId>& travNodes) const {
    if (hashOk) return nodeHashCache;
    common::WriteMsg::write(CMSG_GET_THE_NODE_HASH_OF_NODE_BEGIN,this->getId()); 
    if (travNodes.count(getId())>0) {
      common::WriteMsg::write(CMSG_GET_THE_NODE_HASH_OF_NODE_SKIP);
      return 0;
    }
    travNodes.insert(getId());
    Crc_type resultHash;
    resultHash.process_bytes( "expression::ConditionalExpressionSyntax", strlen("expression::ConditionalExpressionSyntax"));
    common::WriteMsg::write(CMSG_GET_THE_NODE_HASH_OF_NODE_END,resultHash.checksum()); 
    nodeHashCache = resultHash.checksum();
    hashOk = true;
    return nodeHashCache;
  }

  void ConditionalExpressionSyntax::save(io::BinaryIO &binIo,bool withVirtualBase  /*= true*/) const {
    ExpressionSyntax::save(binIo,false);

    binIo.writeUInt4(m_Condition);
    binIo.writeUInt4(m_WhenFalse);
    binIo.writeUInt4(m_WhenTrue);

  }

  void ConditionalExpressionSyntax::load(io::BinaryIO &binIo, bool withVirtualBase /*= true*/) {
    ExpressionSyntax::load(binIo,false);

    m_Condition =  binIo.readUInt4();
    if (m_Condition != 0)
      setParentEdge(factory->getPointer(m_Condition),edkConditionalExpressionSyntax_Condition);

    m_WhenFalse =  binIo.readUInt4();
    if (m_WhenFalse != 0)
      setParentEdge(factory->getPointer(m_WhenFalse),edkConditionalExpressionSyntax_WhenFalse);

    m_WhenTrue =  binIo.readUInt4();
    if (m_WhenTrue != 0)
      setParentEdge(factory->getPointer(m_WhenTrue),edkConditionalExpressionSyntax_WhenTrue);

  }


}


}}}
