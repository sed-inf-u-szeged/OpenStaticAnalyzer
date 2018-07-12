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

namespace structure { 
  GroupClauseSyntax::GroupClauseSyntax(NodeId _id, Factory *_factory) :
    SelectOrGroupClauseSyntax(_id, _factory),
    m_ByExpression(0),
    m_GroupExpression(0)
  {
  }

  GroupClauseSyntax::~GroupClauseSyntax() {
  }

  void GroupClauseSyntax::prepareDelete(bool tryOnVirtualParent){
    removeByExpression();
    removeGroupExpression();
    structure::SelectOrGroupClauseSyntax::prepareDelete(false);
  }

  NodeKind GroupClauseSyntax::getNodeKind() const {
    return ndkGroupClauseSyntax;
  }

  expression::ExpressionSyntax* GroupClauseSyntax::getByExpression() const {
    expression::ExpressionSyntax *_node = NULL;
    if (m_ByExpression != 0)
      _node = dynamic_cast<expression::ExpressionSyntax*>(factory->getPointer(m_ByExpression));
    if ( (_node == NULL) || factory->getIsFiltered(_node))
      return NULL;

    return _node;
  }

  expression::ExpressionSyntax* GroupClauseSyntax::getGroupExpression() const {
    expression::ExpressionSyntax *_node = NULL;
    if (m_GroupExpression != 0)
      _node = dynamic_cast<expression::ExpressionSyntax*>(factory->getPointer(m_GroupExpression));
    if ( (_node == NULL) || factory->getIsFiltered(_node))
      return NULL;

    return _node;
  }

  bool GroupClauseSyntax::setEdge(EdgeKind edgeKind, NodeId edgeEnd, bool tryOnVirtualParent) {
    switch (edgeKind) {
      case edkGroupClauseSyntax_ByExpression:
        setByExpression(edgeEnd);
        return true;
      case edkGroupClauseSyntax_GroupExpression:
        setGroupExpression(edgeEnd);
        return true;
      default:
        break;
    }
    if (structure::SelectOrGroupClauseSyntax::setEdge(edgeKind, edgeEnd, false)) {
      return true;
    }
    return false;
  }

  bool GroupClauseSyntax::removeEdge(EdgeKind edgeKind, NodeId edgeEnd, bool tryOnVirtualParent) {
    switch (edgeKind) {
      case edkGroupClauseSyntax_ByExpression:
        removeByExpression();
        return true;
      case edkGroupClauseSyntax_GroupExpression:
        removeGroupExpression();
        return true;
      default:
        break;
    }
    if (structure::SelectOrGroupClauseSyntax::removeEdge(edgeKind, edgeEnd, false)) {
      return true;
    }
    return false;
  }

  void GroupClauseSyntax::setByExpression(NodeId _id) {
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

      if (m_ByExpression) {
        removeParentEdge(m_ByExpression);
        if (factory->getExistsReverseEdges())
          factory->reverseEdges->removeEdge(m_ByExpression, m_id, edkGroupClauseSyntax_ByExpression);
      }
      m_ByExpression = _node->getId();
      if (m_ByExpression != 0)
        setParentEdge(factory->getPointer(m_ByExpression), edkGroupClauseSyntax_ByExpression);
      if (factory->getExistsReverseEdges())
        factory->reverseEdges->insertEdge(m_ByExpression, this->getId(), edkGroupClauseSyntax_ByExpression);
    } else {
      if (m_ByExpression) {
        throw CsharpException(COLUMBUS_LOCATION, CMSG_EX_CAN_T_SET_EDGE_TO_NULL);
      }
    }
  }

  void GroupClauseSyntax::setByExpression(expression::ExpressionSyntax *_node) {
    if (_node == NULL)
      throw CsharpException(COLUMBUS_LOCATION, CMSG_EX_CAN_T_SET_EDGE_TO_NULL);

    setByExpression(_node->getId());
  }

  void GroupClauseSyntax::removeByExpression() {
      if (m_ByExpression) {
        removeParentEdge(m_ByExpression);
        if (factory->getExistsReverseEdges())
          factory->reverseEdges->removeEdge(m_ByExpression, m_id, edkGroupClauseSyntax_ByExpression);
      }
      m_ByExpression = 0;
  }

  void GroupClauseSyntax::setGroupExpression(NodeId _id) {
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

      if (m_GroupExpression) {
        removeParentEdge(m_GroupExpression);
        if (factory->getExistsReverseEdges())
          factory->reverseEdges->removeEdge(m_GroupExpression, m_id, edkGroupClauseSyntax_GroupExpression);
      }
      m_GroupExpression = _node->getId();
      if (m_GroupExpression != 0)
        setParentEdge(factory->getPointer(m_GroupExpression), edkGroupClauseSyntax_GroupExpression);
      if (factory->getExistsReverseEdges())
        factory->reverseEdges->insertEdge(m_GroupExpression, this->getId(), edkGroupClauseSyntax_GroupExpression);
    } else {
      if (m_GroupExpression) {
        throw CsharpException(COLUMBUS_LOCATION, CMSG_EX_CAN_T_SET_EDGE_TO_NULL);
      }
    }
  }

  void GroupClauseSyntax::setGroupExpression(expression::ExpressionSyntax *_node) {
    if (_node == NULL)
      throw CsharpException(COLUMBUS_LOCATION, CMSG_EX_CAN_T_SET_EDGE_TO_NULL);

    setGroupExpression(_node->getId());
  }

  void GroupClauseSyntax::removeGroupExpression() {
      if (m_GroupExpression) {
        removeParentEdge(m_GroupExpression);
        if (factory->getExistsReverseEdges())
          factory->reverseEdges->removeEdge(m_GroupExpression, m_id, edkGroupClauseSyntax_GroupExpression);
      }
      m_GroupExpression = 0;
  }

  void GroupClauseSyntax::accept(Visitor &visitor) const {
    visitor.visit(*this);
  }

  void GroupClauseSyntax::acceptEnd(Visitor &visitor) const {
    visitor.visitEnd(*this);
  }

  double GroupClauseSyntax::getSimilarity(const base::Base& base){
    if(base.getNodeKind() == getNodeKind()) {
      return 1.0;
    } else {
      return 0.0;
    }
  }

  void GroupClauseSyntax::swapStringTable(RefDistributorStrTable& newStrTable, std::map<Key,Key>& oldAndNewStrKeyMap ){
    std::map<Key,Key>::iterator foundKeyId;

      m_position.swapStringTable(newStrTable,oldAndNewStrKeyMap);

  }

  NodeHashType GroupClauseSyntax::getHash(std::set<NodeId>& travNodes) const {
    if (hashOk) return nodeHashCache;
    common::WriteMsg::write(CMSG_GET_THE_NODE_HASH_OF_NODE_BEGIN,this->getId()); 
    if (travNodes.count(getId())>0) {
      common::WriteMsg::write(CMSG_GET_THE_NODE_HASH_OF_NODE_SKIP);
      return 0;
    }
    travNodes.insert(getId());
    Crc_type resultHash;
    resultHash.process_bytes( "structure::GroupClauseSyntax", strlen("structure::GroupClauseSyntax"));
    common::WriteMsg::write(CMSG_GET_THE_NODE_HASH_OF_NODE_END,resultHash.checksum()); 
    nodeHashCache = resultHash.checksum();
    hashOk = true;
    return nodeHashCache;
  }

  void GroupClauseSyntax::save(io::BinaryIO &binIo,bool withVirtualBase  /*= true*/) const {
    SelectOrGroupClauseSyntax::save(binIo,false);

    binIo.writeUInt4(m_ByExpression);
    binIo.writeUInt4(m_GroupExpression);

  }

  void GroupClauseSyntax::load(io::BinaryIO &binIo, bool withVirtualBase /*= true*/) {
    SelectOrGroupClauseSyntax::load(binIo,false);

    m_ByExpression =  binIo.readUInt4();
    if (m_ByExpression != 0)
      setParentEdge(factory->getPointer(m_ByExpression),edkGroupClauseSyntax_ByExpression);

    m_GroupExpression =  binIo.readUInt4();
    if (m_GroupExpression != 0)
      setParentEdge(factory->getPointer(m_GroupExpression),edkGroupClauseSyntax_GroupExpression);

  }


}


}}}
