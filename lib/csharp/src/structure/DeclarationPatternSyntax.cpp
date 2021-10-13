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
  DeclarationPatternSyntax::DeclarationPatternSyntax(NodeId _id, Factory *_factory) :
    PatternSyntax(_id, _factory),
    m_Designation(0),
    m_Type(0)
  {
  }

  DeclarationPatternSyntax::~DeclarationPatternSyntax() {
  }

  void DeclarationPatternSyntax::prepareDelete(bool tryOnVirtualParent){
    removeDesignation();
    removeType();
    structure::PatternSyntax::prepareDelete(false);
  }

  NodeKind DeclarationPatternSyntax::getNodeKind() const {
    return ndkDeclarationPatternSyntax;
  }

  structure::VariableDesignationSyntax* DeclarationPatternSyntax::getDesignation() const {
    structure::VariableDesignationSyntax *_node = NULL;
    if (m_Designation != 0)
      _node = dynamic_cast<structure::VariableDesignationSyntax*>(factory->getPointer(m_Designation));
    if ( (_node == NULL) || factory->getIsFiltered(_node))
      return NULL;

    return _node;
  }

  expression::TypeSyntax* DeclarationPatternSyntax::getType() const {
    expression::TypeSyntax *_node = NULL;
    if (m_Type != 0)
      _node = dynamic_cast<expression::TypeSyntax*>(factory->getPointer(m_Type));
    if ( (_node == NULL) || factory->getIsFiltered(_node))
      return NULL;

    return _node;
  }

  bool DeclarationPatternSyntax::setEdge(EdgeKind edgeKind, NodeId edgeEnd, bool tryOnVirtualParent) {
    switch (edgeKind) {
      case edkDeclarationPatternSyntax_Designation:
        setDesignation(edgeEnd);
        return true;
      case edkDeclarationPatternSyntax_Type:
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

  bool DeclarationPatternSyntax::removeEdge(EdgeKind edgeKind, NodeId edgeEnd, bool tryOnVirtualParent) {
    switch (edgeKind) {
      case edkDeclarationPatternSyntax_Designation:
        removeDesignation();
        return true;
      case edkDeclarationPatternSyntax_Type:
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

  void DeclarationPatternSyntax::setDesignation(NodeId _id) {
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
          factory->reverseEdges->removeEdge(m_Designation, m_id, edkDeclarationPatternSyntax_Designation);
      }
      m_Designation = _node->getId();
      if (m_Designation != 0)
        setParentEdge(factory->getPointer(m_Designation), edkDeclarationPatternSyntax_Designation);
      if (factory->getExistsReverseEdges())
        factory->reverseEdges->insertEdge(m_Designation, this->getId(), edkDeclarationPatternSyntax_Designation);
    } else {
      if (m_Designation) {
        throw CsharpException(COLUMBUS_LOCATION, CMSG_EX_CAN_T_SET_EDGE_TO_NULL);
      }
    }
  }

  void DeclarationPatternSyntax::setDesignation(structure::VariableDesignationSyntax *_node) {
    if (_node == NULL)
      throw CsharpException(COLUMBUS_LOCATION, CMSG_EX_CAN_T_SET_EDGE_TO_NULL);

    setDesignation(_node->getId());
  }

  void DeclarationPatternSyntax::removeDesignation() {
      if (m_Designation) {
        removeParentEdge(m_Designation);
        if (factory->getExistsReverseEdges())
          factory->reverseEdges->removeEdge(m_Designation, m_id, edkDeclarationPatternSyntax_Designation);
      }
      m_Designation = 0;
  }

  void DeclarationPatternSyntax::setType(NodeId _id) {
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
          factory->reverseEdges->removeEdge(m_Type, m_id, edkDeclarationPatternSyntax_Type);
      }
      m_Type = _node->getId();
      if (m_Type != 0)
        setParentEdge(factory->getPointer(m_Type), edkDeclarationPatternSyntax_Type);
      if (factory->getExistsReverseEdges())
        factory->reverseEdges->insertEdge(m_Type, this->getId(), edkDeclarationPatternSyntax_Type);
    } else {
      if (m_Type) {
        throw CsharpException(COLUMBUS_LOCATION, CMSG_EX_CAN_T_SET_EDGE_TO_NULL);
      }
    }
  }

  void DeclarationPatternSyntax::setType(expression::TypeSyntax *_node) {
    if (_node == NULL)
      throw CsharpException(COLUMBUS_LOCATION, CMSG_EX_CAN_T_SET_EDGE_TO_NULL);

    setType(_node->getId());
  }

  void DeclarationPatternSyntax::removeType() {
      if (m_Type) {
        removeParentEdge(m_Type);
        if (factory->getExistsReverseEdges())
          factory->reverseEdges->removeEdge(m_Type, m_id, edkDeclarationPatternSyntax_Type);
      }
      m_Type = 0;
  }

  void DeclarationPatternSyntax::accept(Visitor &visitor) const {
    visitor.visit(*this);
  }

  void DeclarationPatternSyntax::acceptEnd(Visitor &visitor) const {
    visitor.visitEnd(*this);
  }

  double DeclarationPatternSyntax::getSimilarity(const base::Base& base){
    if(base.getNodeKind() == getNodeKind()) {
      return 1.0;
    } else {
      return 0.0;
    }
  }

  void DeclarationPatternSyntax::swapStringTable(RefDistributorStrTable& newStrTable, std::map<Key,Key>& oldAndNewStrKeyMap ){
    std::map<Key,Key>::iterator foundKeyId;

      m_position.swapStringTable(newStrTable,oldAndNewStrKeyMap);

  }

  NodeHashType DeclarationPatternSyntax::getHash(std::set<NodeId>& travNodes) const {
    if (hashOk) return nodeHashCache;
    common::WriteMsg::write(CMSG_GET_THE_NODE_HASH_OF_NODE_BEGIN,this->getId()); 
    if (travNodes.count(getId())>0) {
      common::WriteMsg::write(CMSG_GET_THE_NODE_HASH_OF_NODE_SKIP);
      return 0;
    }
    travNodes.insert(getId());
    Crc_type resultHash;
    resultHash.process_bytes( "structure::DeclarationPatternSyntax", strlen("structure::DeclarationPatternSyntax"));
    common::WriteMsg::write(CMSG_GET_THE_NODE_HASH_OF_NODE_END,resultHash.checksum()); 
    nodeHashCache = resultHash.checksum();
    hashOk = true;
    return nodeHashCache;
  }

  void DeclarationPatternSyntax::save(io::BinaryIO &binIo,bool withVirtualBase  /*= true*/) const {
    PatternSyntax::save(binIo,false);

    binIo.writeUInt4(m_Designation);
    binIo.writeUInt4(m_Type);

  }

  void DeclarationPatternSyntax::load(io::BinaryIO &binIo, bool withVirtualBase /*= true*/) {
    PatternSyntax::load(binIo,false);

    m_Designation =  binIo.readUInt4();
    if (m_Designation != 0)
      setParentEdge(factory->getPointer(m_Designation),edkDeclarationPatternSyntax_Designation);

    m_Type =  binIo.readUInt4();
    if (m_Type != 0)
      setParentEdge(factory->getPointer(m_Type),edkDeclarationPatternSyntax_Type);

  }


}


}}}
