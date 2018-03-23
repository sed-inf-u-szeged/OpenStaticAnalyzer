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

namespace structure { 
  JoinClauseSyntax::JoinClauseSyntax(NodeId _id, Factory *_factory) :
    QueryClauseSyntax(_id, _factory),
    m_identifier(0),
    m_InExpression(0),
    m_Into(0),
    m_LeftExpression(0),
    m_RightExpression(0),
    m_Type(0)
  {
  }

  JoinClauseSyntax::~JoinClauseSyntax() {
  }

  void JoinClauseSyntax::prepareDelete(bool tryOnVirtualParent){
    removeInExpression();
    removeInto();
    removeLeftExpression();
    removeRightExpression();
    removeType();
    structure::QueryClauseSyntax::prepareDelete(false);
  }

  NodeKind JoinClauseSyntax::getNodeKind() const {
    return ndkJoinClauseSyntax;
  }

  Key JoinClauseSyntax::getIdentifierKey() const {
    return m_identifier;
  }

  const std::string& JoinClauseSyntax::getIdentifier() const {
    return factory->getStringTable().get(m_identifier);
  }

  void JoinClauseSyntax::setIdentifierKey(Key _identifier) {
    m_identifier = _identifier;
  }

  void JoinClauseSyntax::setIdentifier(const std::string& _identifier) {
    m_identifier = factory->getStringTable().set(_identifier);
  }

  expression::ExpressionSyntax* JoinClauseSyntax::getInExpression() const {
    expression::ExpressionSyntax *_node = NULL;
    if (m_InExpression != 0)
      _node = dynamic_cast<expression::ExpressionSyntax*>(factory->getPointer(m_InExpression));
    if ( (_node == NULL) || factory->getIsFiltered(_node))
      return NULL;

    return _node;
  }

  structure::JoinIntoClauseSyntax* JoinClauseSyntax::getInto() const {
    structure::JoinIntoClauseSyntax *_node = NULL;
    if (m_Into != 0)
      _node = dynamic_cast<structure::JoinIntoClauseSyntax*>(factory->getPointer(m_Into));
    if ( (_node == NULL) || factory->getIsFiltered(_node))
      return NULL;

    return _node;
  }

  expression::ExpressionSyntax* JoinClauseSyntax::getLeftExpression() const {
    expression::ExpressionSyntax *_node = NULL;
    if (m_LeftExpression != 0)
      _node = dynamic_cast<expression::ExpressionSyntax*>(factory->getPointer(m_LeftExpression));
    if ( (_node == NULL) || factory->getIsFiltered(_node))
      return NULL;

    return _node;
  }

  expression::ExpressionSyntax* JoinClauseSyntax::getRightExpression() const {
    expression::ExpressionSyntax *_node = NULL;
    if (m_RightExpression != 0)
      _node = dynamic_cast<expression::ExpressionSyntax*>(factory->getPointer(m_RightExpression));
    if ( (_node == NULL) || factory->getIsFiltered(_node))
      return NULL;

    return _node;
  }

  expression::TypeSyntax* JoinClauseSyntax::getType() const {
    expression::TypeSyntax *_node = NULL;
    if (m_Type != 0)
      _node = dynamic_cast<expression::TypeSyntax*>(factory->getPointer(m_Type));
    if ( (_node == NULL) || factory->getIsFiltered(_node))
      return NULL;

    return _node;
  }

  bool JoinClauseSyntax::setEdge(EdgeKind edgeKind, NodeId edgeEnd, bool tryOnVirtualParent) {
    switch (edgeKind) {
      case edkJoinClauseSyntax_InExpression:
        setInExpression(edgeEnd);
        return true;
      case edkJoinClauseSyntax_Into:
        setInto(edgeEnd);
        return true;
      case edkJoinClauseSyntax_LeftExpression:
        setLeftExpression(edgeEnd);
        return true;
      case edkJoinClauseSyntax_RightExpression:
        setRightExpression(edgeEnd);
        return true;
      case edkJoinClauseSyntax_Type:
        setType(edgeEnd);
        return true;
      default:
        break;
    }
    if (structure::QueryClauseSyntax::setEdge(edgeKind, edgeEnd, false)) {
      return true;
    }
    return false;
  }

  bool JoinClauseSyntax::removeEdge(EdgeKind edgeKind, NodeId edgeEnd, bool tryOnVirtualParent) {
    switch (edgeKind) {
      case edkJoinClauseSyntax_InExpression:
        removeInExpression();
        return true;
      case edkJoinClauseSyntax_Into:
        removeInto();
        return true;
      case edkJoinClauseSyntax_LeftExpression:
        removeLeftExpression();
        return true;
      case edkJoinClauseSyntax_RightExpression:
        removeRightExpression();
        return true;
      case edkJoinClauseSyntax_Type:
        removeType();
        return true;
      default:
        break;
    }
    if (structure::QueryClauseSyntax::removeEdge(edgeKind, edgeEnd, false)) {
      return true;
    }
    return false;
  }

  void JoinClauseSyntax::setInExpression(NodeId _id) {
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

      if (m_InExpression) {
        removeParentEdge(m_InExpression);
        if (factory->getExistsReverseEdges())
          factory->reverseEdges->removeEdge(m_InExpression, m_id, edkJoinClauseSyntax_InExpression);
      }
      m_InExpression = _node->getId();
      if (m_InExpression != 0)
        setParentEdge(factory->getPointer(m_InExpression), edkJoinClauseSyntax_InExpression);
      if (factory->getExistsReverseEdges())
        factory->reverseEdges->insertEdge(m_InExpression, this->getId(), edkJoinClauseSyntax_InExpression);
    } else {
      if (m_InExpression) {
        throw CsharpException(COLUMBUS_LOCATION, CMSG_EX_CAN_T_SET_EDGE_TO_NULL);
      }
    }
  }

  void JoinClauseSyntax::setInExpression(expression::ExpressionSyntax *_node) {
    if (_node == NULL)
      throw CsharpException(COLUMBUS_LOCATION, CMSG_EX_CAN_T_SET_EDGE_TO_NULL);

    setInExpression(_node->getId());
  }

  void JoinClauseSyntax::removeInExpression() {
      if (m_InExpression) {
        removeParentEdge(m_InExpression);
        if (factory->getExistsReverseEdges())
          factory->reverseEdges->removeEdge(m_InExpression, m_id, edkJoinClauseSyntax_InExpression);
      }
      m_InExpression = 0;
  }

  void JoinClauseSyntax::setInto(NodeId _id) {
    structure::JoinIntoClauseSyntax *_node = NULL;
    if (_id) {
      if (!factory->getExist(_id))
        throw CsharpException(COLUMBUS_LOCATION, CMSG_EX_THE_END_POINT_OF_THE_EDGE_DOES_NOT_EXIST);

      _node = dynamic_cast<structure::JoinIntoClauseSyntax*> (factory->getPointer(_id));
      if ( _node == NULL) {
        throw CsharpException(COLUMBUS_LOCATION, CMSG_EX_INVALID_NODE_KIND);
      }
      if (&(_node->getFactory()) != this->factory)
        throw CsharpException(COLUMBUS_LOCATION, CMSG_EX_THE_FACTORY_OF_NODES_DOES_NOT_MATCH );

      if (m_Into) {
        removeParentEdge(m_Into);
        if (factory->getExistsReverseEdges())
          factory->reverseEdges->removeEdge(m_Into, m_id, edkJoinClauseSyntax_Into);
      }
      m_Into = _node->getId();
      if (m_Into != 0)
        setParentEdge(factory->getPointer(m_Into), edkJoinClauseSyntax_Into);
      if (factory->getExistsReverseEdges())
        factory->reverseEdges->insertEdge(m_Into, this->getId(), edkJoinClauseSyntax_Into);
    } else {
      if (m_Into) {
        throw CsharpException(COLUMBUS_LOCATION, CMSG_EX_CAN_T_SET_EDGE_TO_NULL);
      }
    }
  }

  void JoinClauseSyntax::setInto(structure::JoinIntoClauseSyntax *_node) {
    if (_node == NULL)
      throw CsharpException(COLUMBUS_LOCATION, CMSG_EX_CAN_T_SET_EDGE_TO_NULL);

    setInto(_node->getId());
  }

  void JoinClauseSyntax::removeInto() {
      if (m_Into) {
        removeParentEdge(m_Into);
        if (factory->getExistsReverseEdges())
          factory->reverseEdges->removeEdge(m_Into, m_id, edkJoinClauseSyntax_Into);
      }
      m_Into = 0;
  }

  void JoinClauseSyntax::setLeftExpression(NodeId _id) {
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

      if (m_LeftExpression) {
        removeParentEdge(m_LeftExpression);
        if (factory->getExistsReverseEdges())
          factory->reverseEdges->removeEdge(m_LeftExpression, m_id, edkJoinClauseSyntax_LeftExpression);
      }
      m_LeftExpression = _node->getId();
      if (m_LeftExpression != 0)
        setParentEdge(factory->getPointer(m_LeftExpression), edkJoinClauseSyntax_LeftExpression);
      if (factory->getExistsReverseEdges())
        factory->reverseEdges->insertEdge(m_LeftExpression, this->getId(), edkJoinClauseSyntax_LeftExpression);
    } else {
      if (m_LeftExpression) {
        throw CsharpException(COLUMBUS_LOCATION, CMSG_EX_CAN_T_SET_EDGE_TO_NULL);
      }
    }
  }

  void JoinClauseSyntax::setLeftExpression(expression::ExpressionSyntax *_node) {
    if (_node == NULL)
      throw CsharpException(COLUMBUS_LOCATION, CMSG_EX_CAN_T_SET_EDGE_TO_NULL);

    setLeftExpression(_node->getId());
  }

  void JoinClauseSyntax::removeLeftExpression() {
      if (m_LeftExpression) {
        removeParentEdge(m_LeftExpression);
        if (factory->getExistsReverseEdges())
          factory->reverseEdges->removeEdge(m_LeftExpression, m_id, edkJoinClauseSyntax_LeftExpression);
      }
      m_LeftExpression = 0;
  }

  void JoinClauseSyntax::setRightExpression(NodeId _id) {
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

      if (m_RightExpression) {
        removeParentEdge(m_RightExpression);
        if (factory->getExistsReverseEdges())
          factory->reverseEdges->removeEdge(m_RightExpression, m_id, edkJoinClauseSyntax_RightExpression);
      }
      m_RightExpression = _node->getId();
      if (m_RightExpression != 0)
        setParentEdge(factory->getPointer(m_RightExpression), edkJoinClauseSyntax_RightExpression);
      if (factory->getExistsReverseEdges())
        factory->reverseEdges->insertEdge(m_RightExpression, this->getId(), edkJoinClauseSyntax_RightExpression);
    } else {
      if (m_RightExpression) {
        throw CsharpException(COLUMBUS_LOCATION, CMSG_EX_CAN_T_SET_EDGE_TO_NULL);
      }
    }
  }

  void JoinClauseSyntax::setRightExpression(expression::ExpressionSyntax *_node) {
    if (_node == NULL)
      throw CsharpException(COLUMBUS_LOCATION, CMSG_EX_CAN_T_SET_EDGE_TO_NULL);

    setRightExpression(_node->getId());
  }

  void JoinClauseSyntax::removeRightExpression() {
      if (m_RightExpression) {
        removeParentEdge(m_RightExpression);
        if (factory->getExistsReverseEdges())
          factory->reverseEdges->removeEdge(m_RightExpression, m_id, edkJoinClauseSyntax_RightExpression);
      }
      m_RightExpression = 0;
  }

  void JoinClauseSyntax::setType(NodeId _id) {
    expression::TypeSyntax *_node = NULL;
    if (_id) {
      if (!factory->getExist(_id))
        throw CsharpException(COLUMBUS_LOCATION, CMSG_EX_THE_END_POINT_OF_THE_EDGE_DOES_NOT_EXIST);

      _node = dynamic_cast<expression::TypeSyntax*> (factory->getPointer(_id));
      if ( _node == NULL) {
        throw CsharpException(COLUMBUS_LOCATION, CMSG_EX_INVALID_NODE_KIND);
      }
      if (&(_node->getFactory()) != this->factory)
        throw CsharpException(COLUMBUS_LOCATION, CMSG_EX_THE_FACTORY_OF_NODES_DOES_NOT_MATCH );

      if (m_Type) {
        removeParentEdge(m_Type);
        if (factory->getExistsReverseEdges())
          factory->reverseEdges->removeEdge(m_Type, m_id, edkJoinClauseSyntax_Type);
      }
      m_Type = _node->getId();
      if (m_Type != 0)
        setParentEdge(factory->getPointer(m_Type), edkJoinClauseSyntax_Type);
      if (factory->getExistsReverseEdges())
        factory->reverseEdges->insertEdge(m_Type, this->getId(), edkJoinClauseSyntax_Type);
    } else {
      if (m_Type) {
        throw CsharpException(COLUMBUS_LOCATION, CMSG_EX_CAN_T_SET_EDGE_TO_NULL);
      }
    }
  }

  void JoinClauseSyntax::setType(expression::TypeSyntax *_node) {
    if (_node == NULL)
      throw CsharpException(COLUMBUS_LOCATION, CMSG_EX_CAN_T_SET_EDGE_TO_NULL);

    setType(_node->getId());
  }

  void JoinClauseSyntax::removeType() {
      if (m_Type) {
        removeParentEdge(m_Type);
        if (factory->getExistsReverseEdges())
          factory->reverseEdges->removeEdge(m_Type, m_id, edkJoinClauseSyntax_Type);
      }
      m_Type = 0;
  }

  void JoinClauseSyntax::accept(Visitor &visitor) const {
    visitor.visit(*this);
  }

  void JoinClauseSyntax::acceptEnd(Visitor &visitor) const {
    visitor.visitEnd(*this);
  }

  double JoinClauseSyntax::getSimilarity(const base::Base& base){
    if(base.getNodeKind() == getNodeKind()) {
      const JoinClauseSyntax& node = dynamic_cast<const JoinClauseSyntax&>(base);
      double matchAttrs = 0;
      std::string str1, str2;
      size_t strMax;
      double strSim;
      str1 = getIdentifier();
      str2 = node.getIdentifier();
      strMax = std::max(str1.size(), str2.size());
      strSim = 1 - ((double)common::math::editDistance(str1, str2) / (strMax > 0 ? strMax : 1));
      if (strSim < Common::SimilarityMinForStrings)
        return 0.0;
      matchAttrs += strSim;
      return matchAttrs / (1 / (1 - Common::SimilarityMinimum)) + Common::SimilarityMinimum;
    } else {
      return 0.0;
    }
  }

  void JoinClauseSyntax::swapStringTable(RefDistributorStrTable& newStrTable, std::map<Key,Key>& oldAndNewStrKeyMap ){
    std::map<Key,Key>::iterator foundKeyId;

    foundKeyId = oldAndNewStrKeyMap.find(m_identifier);
    if (foundKeyId != oldAndNewStrKeyMap.end()) {
      m_identifier = foundKeyId->second;
    } else {
      Key oldkey = m_identifier;
      m_identifier = newStrTable.set(factory->getStringTable().get(m_identifier));
      oldAndNewStrKeyMap.insert(std::pair<Key,Key>(oldkey,m_identifier));    }

      m_position.swapStringTable(newStrTable,oldAndNewStrKeyMap);

  }

  NodeHashType JoinClauseSyntax::getHash(std::set<NodeId>& travNodes) const {
    if (hashOk) return nodeHashCache;
    common::WriteMsg::write(CMSG_GET_THE_NODE_HASH_OF_NODE_BEGIN,this->getId()); 
    if (travNodes.count(getId())>0) {
      common::WriteMsg::write(CMSG_GET_THE_NODE_HASH_OF_NODE_SKIP);
      return 0;
    }
    travNodes.insert(getId());
    Crc_type resultHash;
    resultHash.process_bytes( "structure::JoinClauseSyntax", strlen("structure::JoinClauseSyntax"));
    common::WriteMsg::write(CMSG_GET_THE_NODE_HASH_OF_NODE_END,resultHash.checksum()); 
    nodeHashCache = resultHash.checksum();
    hashOk = true;
    return nodeHashCache;
  }

  void JoinClauseSyntax::save(io::BinaryIO &binIo,bool withVirtualBase  /*= true*/) const {
    QueryClauseSyntax::save(binIo,false);

    factory->getStringTable().setType(m_identifier, StrTable::strToSave);
    binIo.writeUInt4(m_identifier);

    binIo.writeUInt4(m_InExpression);
    binIo.writeUInt4(m_Into);
    binIo.writeUInt4(m_LeftExpression);
    binIo.writeUInt4(m_RightExpression);
    binIo.writeUInt4(m_Type);

  }

  void JoinClauseSyntax::load(io::BinaryIO &binIo, bool withVirtualBase /*= true*/) {
    QueryClauseSyntax::load(binIo,false);

    m_identifier = binIo.readUInt4();

    m_InExpression =  binIo.readUInt4();
    if (m_InExpression != 0)
      setParentEdge(factory->getPointer(m_InExpression),edkJoinClauseSyntax_InExpression);

    m_Into =  binIo.readUInt4();
    if (m_Into != 0)
      setParentEdge(factory->getPointer(m_Into),edkJoinClauseSyntax_Into);

    m_LeftExpression =  binIo.readUInt4();
    if (m_LeftExpression != 0)
      setParentEdge(factory->getPointer(m_LeftExpression),edkJoinClauseSyntax_LeftExpression);

    m_RightExpression =  binIo.readUInt4();
    if (m_RightExpression != 0)
      setParentEdge(factory->getPointer(m_RightExpression),edkJoinClauseSyntax_RightExpression);

    m_Type =  binIo.readUInt4();
    if (m_Type != 0)
      setParentEdge(factory->getPointer(m_Type),edkJoinClauseSyntax_Type);

  }


}


}}}
