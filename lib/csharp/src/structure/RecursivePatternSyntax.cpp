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
  RecursivePatternSyntax::RecursivePatternSyntax(NodeId _id, Factory *_factory) :
    PatternSyntax(_id, _factory),
    m_Designation(0),
    m_PositionalPatternClause(0),
    m_PropertyPatternClause(0),
    m_Type(0)
  {
  }

  RecursivePatternSyntax::~RecursivePatternSyntax() {
  }

  void RecursivePatternSyntax::prepareDelete(bool tryOnVirtualParent){
    removeDesignation();
    removePositionalPatternClause();
    removePropertyPatternClause();
    removeType();
    structure::PatternSyntax::prepareDelete(false);
  }

  NodeKind RecursivePatternSyntax::getNodeKind() const {
    return ndkRecursivePatternSyntax;
  }

  structure::VariableDesignationSyntax* RecursivePatternSyntax::getDesignation() const {
    structure::VariableDesignationSyntax *_node = NULL;
    if (m_Designation != 0)
      _node = dynamic_cast<structure::VariableDesignationSyntax*>(factory->getPointer(m_Designation));
    if ( (_node == NULL) || factory->getIsFiltered(_node))
      return NULL;

    return _node;
  }

  structure::PositionalPatternClauseSyntax* RecursivePatternSyntax::getPositionalPatternClause() const {
    structure::PositionalPatternClauseSyntax *_node = NULL;
    if (m_PositionalPatternClause != 0)
      _node = dynamic_cast<structure::PositionalPatternClauseSyntax*>(factory->getPointer(m_PositionalPatternClause));
    if ( (_node == NULL) || factory->getIsFiltered(_node))
      return NULL;

    return _node;
  }

  structure::PropertyPatternClauseSyntax* RecursivePatternSyntax::getPropertyPatternClause() const {
    structure::PropertyPatternClauseSyntax *_node = NULL;
    if (m_PropertyPatternClause != 0)
      _node = dynamic_cast<structure::PropertyPatternClauseSyntax*>(factory->getPointer(m_PropertyPatternClause));
    if ( (_node == NULL) || factory->getIsFiltered(_node))
      return NULL;

    return _node;
  }

  expression::TypeSyntax* RecursivePatternSyntax::getType() const {
    expression::TypeSyntax *_node = NULL;
    if (m_Type != 0)
      _node = dynamic_cast<expression::TypeSyntax*>(factory->getPointer(m_Type));
    if ( (_node == NULL) || factory->getIsFiltered(_node))
      return NULL;

    return _node;
  }

  bool RecursivePatternSyntax::setEdge(EdgeKind edgeKind, NodeId edgeEnd, bool tryOnVirtualParent) {
    switch (edgeKind) {
      case edkRecursivePatternSyntax_Designation:
        setDesignation(edgeEnd);
        return true;
      case edkRecursivePatternSyntax_PositionalPatternClause:
        setPositionalPatternClause(edgeEnd);
        return true;
      case edkRecursivePatternSyntax_PropertyPatternClause:
        setPropertyPatternClause(edgeEnd);
        return true;
      case edkRecursivePatternSyntax_Type:
        setType(edgeEnd);
        return true;
      default:
        break;
    }
    if (structure::PatternSyntax::setEdge(edgeKind, edgeEnd, false)) {
      return true;
    }
    return false;
  }

  bool RecursivePatternSyntax::removeEdge(EdgeKind edgeKind, NodeId edgeEnd, bool tryOnVirtualParent) {
    switch (edgeKind) {
      case edkRecursivePatternSyntax_Designation:
        removeDesignation();
        return true;
      case edkRecursivePatternSyntax_PositionalPatternClause:
        removePositionalPatternClause();
        return true;
      case edkRecursivePatternSyntax_PropertyPatternClause:
        removePropertyPatternClause();
        return true;
      case edkRecursivePatternSyntax_Type:
        removeType();
        return true;
      default:
        break;
    }
    if (structure::PatternSyntax::removeEdge(edgeKind, edgeEnd, false)) {
      return true;
    }
    return false;
  }

  void RecursivePatternSyntax::setDesignation(NodeId _id) {
    structure::VariableDesignationSyntax *_node = NULL;
    if (_id) {
      if (!factory->getExist(_id))
        throw CsharpException(COLUMBUS_LOCATION, CMSG_EX_THE_END_POINT_OF_THE_EDGE_DOES_NOT_EXIST);

      _node = dynamic_cast<structure::VariableDesignationSyntax*> (factory->getPointer(_id));
      if ( _node == NULL) {
        throw CsharpException(COLUMBUS_LOCATION, CMSG_EX_INVALID_NODE_KIND);
      }
      if (&(_node->getFactory()) != this->factory)
        throw CsharpException(COLUMBUS_LOCATION, CMSG_EX_THE_FACTORY_OF_NODES_DOES_NOT_MATCH );

      if (m_Designation) {
        removeParentEdge(m_Designation);
        if (factory->getExistsReverseEdges())
          factory->reverseEdges->removeEdge(m_Designation, m_id, edkRecursivePatternSyntax_Designation);
      }
      m_Designation = _node->getId();
      if (m_Designation != 0)
        setParentEdge(factory->getPointer(m_Designation), edkRecursivePatternSyntax_Designation);
      if (factory->getExistsReverseEdges())
        factory->reverseEdges->insertEdge(m_Designation, this->getId(), edkRecursivePatternSyntax_Designation);
    } else {
      if (m_Designation) {
        throw CsharpException(COLUMBUS_LOCATION, CMSG_EX_CAN_T_SET_EDGE_TO_NULL);
      }
    }
  }

  void RecursivePatternSyntax::setDesignation(structure::VariableDesignationSyntax *_node) {
    if (_node == NULL)
      throw CsharpException(COLUMBUS_LOCATION, CMSG_EX_CAN_T_SET_EDGE_TO_NULL);

    setDesignation(_node->getId());
  }

  void RecursivePatternSyntax::removeDesignation() {
      if (m_Designation) {
        removeParentEdge(m_Designation);
        if (factory->getExistsReverseEdges())
          factory->reverseEdges->removeEdge(m_Designation, m_id, edkRecursivePatternSyntax_Designation);
      }
      m_Designation = 0;
  }

  void RecursivePatternSyntax::setPositionalPatternClause(NodeId _id) {
    structure::PositionalPatternClauseSyntax *_node = NULL;
    if (_id) {
      if (!factory->getExist(_id))
        throw CsharpException(COLUMBUS_LOCATION, CMSG_EX_THE_END_POINT_OF_THE_EDGE_DOES_NOT_EXIST);

      _node = dynamic_cast<structure::PositionalPatternClauseSyntax*> (factory->getPointer(_id));
      if ( _node == NULL) {
        throw CsharpException(COLUMBUS_LOCATION, CMSG_EX_INVALID_NODE_KIND);
      }
      if (&(_node->getFactory()) != this->factory)
        throw CsharpException(COLUMBUS_LOCATION, CMSG_EX_THE_FACTORY_OF_NODES_DOES_NOT_MATCH );

      if (m_PositionalPatternClause) {
        removeParentEdge(m_PositionalPatternClause);
        if (factory->getExistsReverseEdges())
          factory->reverseEdges->removeEdge(m_PositionalPatternClause, m_id, edkRecursivePatternSyntax_PositionalPatternClause);
      }
      m_PositionalPatternClause = _node->getId();
      if (m_PositionalPatternClause != 0)
        setParentEdge(factory->getPointer(m_PositionalPatternClause), edkRecursivePatternSyntax_PositionalPatternClause);
      if (factory->getExistsReverseEdges())
        factory->reverseEdges->insertEdge(m_PositionalPatternClause, this->getId(), edkRecursivePatternSyntax_PositionalPatternClause);
    } else {
      if (m_PositionalPatternClause) {
        throw CsharpException(COLUMBUS_LOCATION, CMSG_EX_CAN_T_SET_EDGE_TO_NULL);
      }
    }
  }

  void RecursivePatternSyntax::setPositionalPatternClause(structure::PositionalPatternClauseSyntax *_node) {
    if (_node == NULL)
      throw CsharpException(COLUMBUS_LOCATION, CMSG_EX_CAN_T_SET_EDGE_TO_NULL);

    setPositionalPatternClause(_node->getId());
  }

  void RecursivePatternSyntax::removePositionalPatternClause() {
      if (m_PositionalPatternClause) {
        removeParentEdge(m_PositionalPatternClause);
        if (factory->getExistsReverseEdges())
          factory->reverseEdges->removeEdge(m_PositionalPatternClause, m_id, edkRecursivePatternSyntax_PositionalPatternClause);
      }
      m_PositionalPatternClause = 0;
  }

  void RecursivePatternSyntax::setPropertyPatternClause(NodeId _id) {
    structure::PropertyPatternClauseSyntax *_node = NULL;
    if (_id) {
      if (!factory->getExist(_id))
        throw CsharpException(COLUMBUS_LOCATION, CMSG_EX_THE_END_POINT_OF_THE_EDGE_DOES_NOT_EXIST);

      _node = dynamic_cast<structure::PropertyPatternClauseSyntax*> (factory->getPointer(_id));
      if ( _node == NULL) {
        throw CsharpException(COLUMBUS_LOCATION, CMSG_EX_INVALID_NODE_KIND);
      }
      if (&(_node->getFactory()) != this->factory)
        throw CsharpException(COLUMBUS_LOCATION, CMSG_EX_THE_FACTORY_OF_NODES_DOES_NOT_MATCH );

      if (m_PropertyPatternClause) {
        removeParentEdge(m_PropertyPatternClause);
        if (factory->getExistsReverseEdges())
          factory->reverseEdges->removeEdge(m_PropertyPatternClause, m_id, edkRecursivePatternSyntax_PropertyPatternClause);
      }
      m_PropertyPatternClause = _node->getId();
      if (m_PropertyPatternClause != 0)
        setParentEdge(factory->getPointer(m_PropertyPatternClause), edkRecursivePatternSyntax_PropertyPatternClause);
      if (factory->getExistsReverseEdges())
        factory->reverseEdges->insertEdge(m_PropertyPatternClause, this->getId(), edkRecursivePatternSyntax_PropertyPatternClause);
    } else {
      if (m_PropertyPatternClause) {
        throw CsharpException(COLUMBUS_LOCATION, CMSG_EX_CAN_T_SET_EDGE_TO_NULL);
      }
    }
  }

  void RecursivePatternSyntax::setPropertyPatternClause(structure::PropertyPatternClauseSyntax *_node) {
    if (_node == NULL)
      throw CsharpException(COLUMBUS_LOCATION, CMSG_EX_CAN_T_SET_EDGE_TO_NULL);

    setPropertyPatternClause(_node->getId());
  }

  void RecursivePatternSyntax::removePropertyPatternClause() {
      if (m_PropertyPatternClause) {
        removeParentEdge(m_PropertyPatternClause);
        if (factory->getExistsReverseEdges())
          factory->reverseEdges->removeEdge(m_PropertyPatternClause, m_id, edkRecursivePatternSyntax_PropertyPatternClause);
      }
      m_PropertyPatternClause = 0;
  }

  void RecursivePatternSyntax::setType(NodeId _id) {
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
          factory->reverseEdges->removeEdge(m_Type, m_id, edkRecursivePatternSyntax_Type);
      }
      m_Type = _node->getId();
      if (m_Type != 0)
        setParentEdge(factory->getPointer(m_Type), edkRecursivePatternSyntax_Type);
      if (factory->getExistsReverseEdges())
        factory->reverseEdges->insertEdge(m_Type, this->getId(), edkRecursivePatternSyntax_Type);
    } else {
      if (m_Type) {
        throw CsharpException(COLUMBUS_LOCATION, CMSG_EX_CAN_T_SET_EDGE_TO_NULL);
      }
    }
  }

  void RecursivePatternSyntax::setType(expression::TypeSyntax *_node) {
    if (_node == NULL)
      throw CsharpException(COLUMBUS_LOCATION, CMSG_EX_CAN_T_SET_EDGE_TO_NULL);

    setType(_node->getId());
  }

  void RecursivePatternSyntax::removeType() {
      if (m_Type) {
        removeParentEdge(m_Type);
        if (factory->getExistsReverseEdges())
          factory->reverseEdges->removeEdge(m_Type, m_id, edkRecursivePatternSyntax_Type);
      }
      m_Type = 0;
  }

  void RecursivePatternSyntax::accept(Visitor &visitor) const {
    visitor.visit(*this);
  }

  void RecursivePatternSyntax::acceptEnd(Visitor &visitor) const {
    visitor.visitEnd(*this);
  }

  double RecursivePatternSyntax::getSimilarity(const base::Base& base){
    if(base.getNodeKind() == getNodeKind()) {
      return 1.0;
    } else {
      return 0.0;
    }
  }

  void RecursivePatternSyntax::swapStringTable(RefDistributorStrTable& newStrTable, std::map<Key,Key>& oldAndNewStrKeyMap ){
    std::map<Key,Key>::iterator foundKeyId;

      m_position.swapStringTable(newStrTable,oldAndNewStrKeyMap);

  }

  NodeHashType RecursivePatternSyntax::getHash(std::set<NodeId>& travNodes) const {
    if (hashOk) return nodeHashCache;
    common::WriteMsg::write(CMSG_GET_THE_NODE_HASH_OF_NODE_BEGIN,this->getId()); 
    if (travNodes.count(getId())>0) {
      common::WriteMsg::write(CMSG_GET_THE_NODE_HASH_OF_NODE_SKIP);
      return 0;
    }
    travNodes.insert(getId());
    Crc_type resultHash;
    resultHash.process_bytes( "structure::RecursivePatternSyntax", strlen("structure::RecursivePatternSyntax"));
    common::WriteMsg::write(CMSG_GET_THE_NODE_HASH_OF_NODE_END,resultHash.checksum()); 
    nodeHashCache = resultHash.checksum();
    hashOk = true;
    return nodeHashCache;
  }

  void RecursivePatternSyntax::save(io::BinaryIO &binIo,bool withVirtualBase  /*= true*/) const {
    PatternSyntax::save(binIo,false);

    binIo.writeUInt4(m_Designation);
    binIo.writeUInt4(m_PositionalPatternClause);
    binIo.writeUInt4(m_PropertyPatternClause);
    binIo.writeUInt4(m_Type);

  }

  void RecursivePatternSyntax::load(io::BinaryIO &binIo, bool withVirtualBase /*= true*/) {
    PatternSyntax::load(binIo,false);

    m_Designation =  binIo.readUInt4();
    if (m_Designation != 0)
      setParentEdge(factory->getPointer(m_Designation),edkRecursivePatternSyntax_Designation);

    m_PositionalPatternClause =  binIo.readUInt4();
    if (m_PositionalPatternClause != 0)
      setParentEdge(factory->getPointer(m_PositionalPatternClause),edkRecursivePatternSyntax_PositionalPatternClause);

    m_PropertyPatternClause =  binIo.readUInt4();
    if (m_PropertyPatternClause != 0)
      setParentEdge(factory->getPointer(m_PropertyPatternClause),edkRecursivePatternSyntax_PropertyPatternClause);

    m_Type =  binIo.readUInt4();
    if (m_Type != 0)
      setParentEdge(factory->getPointer(m_Type),edkRecursivePatternSyntax_Type);

  }


}


}}}
