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
  AttributeArgumentSyntax::AttributeArgumentSyntax(NodeId _id, Factory *_factory) :
    Positioned(_id, _factory),
    m_Expression(0),
    m_NameColon(0),
    m_NameEquals(0)
  {
  }

  AttributeArgumentSyntax::~AttributeArgumentSyntax() {
  }

  void AttributeArgumentSyntax::prepareDelete(bool tryOnVirtualParent){
    removeExpression();
    removeNameColon();
    removeNameEquals();
    base::Positioned::prepareDelete(false);
  }

  NodeKind AttributeArgumentSyntax::getNodeKind() const {
    return ndkAttributeArgumentSyntax;
  }

  expression::ExpressionSyntax* AttributeArgumentSyntax::getExpression() const {
    expression::ExpressionSyntax *_node = NULL;
    if (m_Expression != 0)
      _node = dynamic_cast<expression::ExpressionSyntax*>(factory->getPointer(m_Expression));
    if ( (_node == NULL) || factory->getIsFiltered(_node))
      return NULL;

    return _node;
  }

  structure::NameColonSyntax* AttributeArgumentSyntax::getNameColon() const {
    structure::NameColonSyntax *_node = NULL;
    if (m_NameColon != 0)
      _node = dynamic_cast<structure::NameColonSyntax*>(factory->getPointer(m_NameColon));
    if ( (_node == NULL) || factory->getIsFiltered(_node))
      return NULL;

    return _node;
  }

  structure::NameEqualsSyntax* AttributeArgumentSyntax::getNameEquals() const {
    structure::NameEqualsSyntax *_node = NULL;
    if (m_NameEquals != 0)
      _node = dynamic_cast<structure::NameEqualsSyntax*>(factory->getPointer(m_NameEquals));
    if ( (_node == NULL) || factory->getIsFiltered(_node))
      return NULL;

    return _node;
  }

  bool AttributeArgumentSyntax::setEdge(EdgeKind edgeKind, NodeId edgeEnd, bool tryOnVirtualParent) {
    switch (edgeKind) {
      case edkAttributeArgumentSyntax_Expression:
        setExpression(edgeEnd);
        return true;
      case edkAttributeArgumentSyntax_NameColon:
        setNameColon(edgeEnd);
        return true;
      case edkAttributeArgumentSyntax_NameEquals:
        setNameEquals(edgeEnd);
        return true;
      default:
        break;
    }
    if (base::Positioned::setEdge(edgeKind, edgeEnd, false)) {
      return true;
    }
    return false;
  }

  bool AttributeArgumentSyntax::removeEdge(EdgeKind edgeKind, NodeId edgeEnd, bool tryOnVirtualParent) {
    switch (edgeKind) {
      case edkAttributeArgumentSyntax_Expression:
        removeExpression();
        return true;
      case edkAttributeArgumentSyntax_NameColon:
        removeNameColon();
        return true;
      case edkAttributeArgumentSyntax_NameEquals:
        removeNameEquals();
        return true;
      default:
        break;
    }
    if (base::Positioned::removeEdge(edgeKind, edgeEnd, false)) {
      return true;
    }
    return false;
  }

  void AttributeArgumentSyntax::setExpression(NodeId _id) {
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
          factory->reverseEdges->removeEdge(m_Expression, m_id, edkAttributeArgumentSyntax_Expression);
      }
      m_Expression = _node->getId();
      if (m_Expression != 0)
        setParentEdge(factory->getPointer(m_Expression), edkAttributeArgumentSyntax_Expression);
      if (factory->getExistsReverseEdges())
        factory->reverseEdges->insertEdge(m_Expression, this->getId(), edkAttributeArgumentSyntax_Expression);
    } else {
      if (m_Expression) {
        throw CsharpException(COLUMBUS_LOCATION, CMSG_EX_CAN_T_SET_EDGE_TO_NULL);
      }
    }
  }

  void AttributeArgumentSyntax::setExpression(expression::ExpressionSyntax *_node) {
    if (_node == NULL)
      throw CsharpException(COLUMBUS_LOCATION, CMSG_EX_CAN_T_SET_EDGE_TO_NULL);

    setExpression(_node->getId());
  }

  void AttributeArgumentSyntax::removeExpression() {
      if (m_Expression) {
        removeParentEdge(m_Expression);
        if (factory->getExistsReverseEdges())
          factory->reverseEdges->removeEdge(m_Expression, m_id, edkAttributeArgumentSyntax_Expression);
      }
      m_Expression = 0;
  }

  void AttributeArgumentSyntax::setNameColon(NodeId _id) {
    structure::NameColonSyntax *_node = NULL;
    if (_id) {
      if (!factory->getExist(_id))
        throw CsharpException(COLUMBUS_LOCATION, CMSG_EX_THE_END_POINT_OF_THE_EDGE_DOES_NOT_EXIST);

      _node = dynamic_cast<structure::NameColonSyntax*> (factory->getPointer(_id));
      if ( _node == NULL) {
        throw CsharpException(COLUMBUS_LOCATION, CMSG_EX_INVALID_NODE_KIND);
      }
      if (&(_node->getFactory()) != this->factory)
        throw CsharpException(COLUMBUS_LOCATION, CMSG_EX_THE_FACTORY_OF_NODES_DOES_NOT_MATCH );

      if (m_NameColon) {
        removeParentEdge(m_NameColon);
        if (factory->getExistsReverseEdges())
          factory->reverseEdges->removeEdge(m_NameColon, m_id, edkAttributeArgumentSyntax_NameColon);
      }
      m_NameColon = _node->getId();
      if (m_NameColon != 0)
        setParentEdge(factory->getPointer(m_NameColon), edkAttributeArgumentSyntax_NameColon);
      if (factory->getExistsReverseEdges())
        factory->reverseEdges->insertEdge(m_NameColon, this->getId(), edkAttributeArgumentSyntax_NameColon);
    } else {
      if (m_NameColon) {
        throw CsharpException(COLUMBUS_LOCATION, CMSG_EX_CAN_T_SET_EDGE_TO_NULL);
      }
    }
  }

  void AttributeArgumentSyntax::setNameColon(structure::NameColonSyntax *_node) {
    if (_node == NULL)
      throw CsharpException(COLUMBUS_LOCATION, CMSG_EX_CAN_T_SET_EDGE_TO_NULL);

    setNameColon(_node->getId());
  }

  void AttributeArgumentSyntax::removeNameColon() {
      if (m_NameColon) {
        removeParentEdge(m_NameColon);
        if (factory->getExistsReverseEdges())
          factory->reverseEdges->removeEdge(m_NameColon, m_id, edkAttributeArgumentSyntax_NameColon);
      }
      m_NameColon = 0;
  }

  void AttributeArgumentSyntax::setNameEquals(NodeId _id) {
    structure::NameEqualsSyntax *_node = NULL;
    if (_id) {
      if (!factory->getExist(_id))
        throw CsharpException(COLUMBUS_LOCATION, CMSG_EX_THE_END_POINT_OF_THE_EDGE_DOES_NOT_EXIST);

      _node = dynamic_cast<structure::NameEqualsSyntax*> (factory->getPointer(_id));
      if ( _node == NULL) {
        throw CsharpException(COLUMBUS_LOCATION, CMSG_EX_INVALID_NODE_KIND);
      }
      if (&(_node->getFactory()) != this->factory)
        throw CsharpException(COLUMBUS_LOCATION, CMSG_EX_THE_FACTORY_OF_NODES_DOES_NOT_MATCH );

      if (m_NameEquals) {
        removeParentEdge(m_NameEquals);
        if (factory->getExistsReverseEdges())
          factory->reverseEdges->removeEdge(m_NameEquals, m_id, edkAttributeArgumentSyntax_NameEquals);
      }
      m_NameEquals = _node->getId();
      if (m_NameEquals != 0)
        setParentEdge(factory->getPointer(m_NameEquals), edkAttributeArgumentSyntax_NameEquals);
      if (factory->getExistsReverseEdges())
        factory->reverseEdges->insertEdge(m_NameEquals, this->getId(), edkAttributeArgumentSyntax_NameEquals);
    } else {
      if (m_NameEquals) {
        throw CsharpException(COLUMBUS_LOCATION, CMSG_EX_CAN_T_SET_EDGE_TO_NULL);
      }
    }
  }

  void AttributeArgumentSyntax::setNameEquals(structure::NameEqualsSyntax *_node) {
    if (_node == NULL)
      throw CsharpException(COLUMBUS_LOCATION, CMSG_EX_CAN_T_SET_EDGE_TO_NULL);

    setNameEquals(_node->getId());
  }

  void AttributeArgumentSyntax::removeNameEquals() {
      if (m_NameEquals) {
        removeParentEdge(m_NameEquals);
        if (factory->getExistsReverseEdges())
          factory->reverseEdges->removeEdge(m_NameEquals, m_id, edkAttributeArgumentSyntax_NameEquals);
      }
      m_NameEquals = 0;
  }

  void AttributeArgumentSyntax::accept(Visitor &visitor) const {
    visitor.visit(*this);
  }

  void AttributeArgumentSyntax::acceptEnd(Visitor &visitor) const {
    visitor.visitEnd(*this);
  }

  double AttributeArgumentSyntax::getSimilarity(const base::Base& base){
    if(base.getNodeKind() == getNodeKind()) {
      return 1.0;
    } else {
      return 0.0;
    }
  }

  void AttributeArgumentSyntax::swapStringTable(RefDistributorStrTable& newStrTable, std::map<Key,Key>& oldAndNewStrKeyMap ){
    std::map<Key,Key>::iterator foundKeyId;

      m_position.swapStringTable(newStrTable,oldAndNewStrKeyMap);

  }

  NodeHashType AttributeArgumentSyntax::getHash(std::set<NodeId>& travNodes) const {
    if (hashOk) return nodeHashCache;
    common::WriteMsg::write(CMSG_GET_THE_NODE_HASH_OF_NODE_BEGIN,this->getId()); 
    if (travNodes.count(getId())>0) {
      common::WriteMsg::write(CMSG_GET_THE_NODE_HASH_OF_NODE_SKIP);
      return 0;
    }
    travNodes.insert(getId());
    Crc_type resultHash;
    resultHash.process_bytes( "structure::AttributeArgumentSyntax", strlen("structure::AttributeArgumentSyntax"));
    common::WriteMsg::write(CMSG_GET_THE_NODE_HASH_OF_NODE_END,resultHash.checksum()); 
    nodeHashCache = resultHash.checksum();
    hashOk = true;
    return nodeHashCache;
  }

  void AttributeArgumentSyntax::save(io::BinaryIO &binIo,bool withVirtualBase  /*= true*/) const {
    Positioned::save(binIo,false);

    binIo.writeUInt4(m_Expression);
    binIo.writeUInt4(m_NameColon);
    binIo.writeUInt4(m_NameEquals);

  }

  void AttributeArgumentSyntax::load(io::BinaryIO &binIo, bool withVirtualBase /*= true*/) {
    Positioned::load(binIo,false);

    m_Expression =  binIo.readUInt4();
    if (m_Expression != 0)
      setParentEdge(factory->getPointer(m_Expression),edkAttributeArgumentSyntax_Expression);

    m_NameColon =  binIo.readUInt4();
    if (m_NameColon != 0)
      setParentEdge(factory->getPointer(m_NameColon),edkAttributeArgumentSyntax_NameColon);

    m_NameEquals =  binIo.readUInt4();
    if (m_NameEquals != 0)
      setParentEdge(factory->getPointer(m_NameEquals),edkAttributeArgumentSyntax_NameEquals);

  }


}


}}}
