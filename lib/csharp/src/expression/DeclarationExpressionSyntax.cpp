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
  DeclarationExpressionSyntax::DeclarationExpressionSyntax(NodeId _id, Factory *_factory) :
    ExpressionSyntax(_id, _factory),
    m_Designation(0),
    m_Type(0)
  {
  }

  DeclarationExpressionSyntax::~DeclarationExpressionSyntax() {
  }

  void DeclarationExpressionSyntax::prepareDelete(bool tryOnVirtualParent){
    removeDesignation();
    removeType();
    expression::ExpressionSyntax::prepareDelete(false);
  }

  NodeKind DeclarationExpressionSyntax::getNodeKind() const {
    return ndkDeclarationExpressionSyntax;
  }

  structure::VariableDesignationSyntax* DeclarationExpressionSyntax::getDesignation() const {
    structure::VariableDesignationSyntax *_node = NULL;
    if (m_Designation != 0)
      _node = dynamic_cast<structure::VariableDesignationSyntax*>(factory->getPointer(m_Designation));
    if ( (_node == NULL) || factory->getIsFiltered(_node))
      return NULL;

    return _node;
  }

  expression::TypeSyntax* DeclarationExpressionSyntax::getType() const {
    expression::TypeSyntax *_node = NULL;
    if (m_Type != 0)
      _node = dynamic_cast<expression::TypeSyntax*>(factory->getPointer(m_Type));
    if ( (_node == NULL) || factory->getIsFiltered(_node))
      return NULL;

    return _node;
  }

  bool DeclarationExpressionSyntax::setEdge(EdgeKind edgeKind, NodeId edgeEnd, bool tryOnVirtualParent) {
    switch (edgeKind) {
      case edkDeclarationExpressionSyntax_Designation:
        setDesignation(edgeEnd);
        return true;
      case edkDeclarationExpressionSyntax_Type:
        setType(edgeEnd);
        return true;
      default:
        break;
    }
    if (expression::ExpressionSyntax::setEdge(edgeKind, edgeEnd, false)) {
      return true;
    }
    return false;
  }

  bool DeclarationExpressionSyntax::removeEdge(EdgeKind edgeKind, NodeId edgeEnd, bool tryOnVirtualParent) {
    switch (edgeKind) {
      case edkDeclarationExpressionSyntax_Designation:
        removeDesignation();
        return true;
      case edkDeclarationExpressionSyntax_Type:
        removeType();
        return true;
      default:
        break;
    }
    if (expression::ExpressionSyntax::removeEdge(edgeKind, edgeEnd, false)) {
      return true;
    }
    return false;
  }

  void DeclarationExpressionSyntax::setDesignation(NodeId _id) {
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
          factory->reverseEdges->removeEdge(m_Designation, m_id, edkDeclarationExpressionSyntax_Designation);
      }
      m_Designation = _node->getId();
      if (m_Designation != 0)
        setParentEdge(factory->getPointer(m_Designation), edkDeclarationExpressionSyntax_Designation);
      if (factory->getExistsReverseEdges())
        factory->reverseEdges->insertEdge(m_Designation, this->getId(), edkDeclarationExpressionSyntax_Designation);
    } else {
      if (m_Designation) {
        throw CsharpException(COLUMBUS_LOCATION, CMSG_EX_CAN_T_SET_EDGE_TO_NULL);
      }
    }
  }

  void DeclarationExpressionSyntax::setDesignation(structure::VariableDesignationSyntax *_node) {
    if (_node == NULL)
      throw CsharpException(COLUMBUS_LOCATION, CMSG_EX_CAN_T_SET_EDGE_TO_NULL);

    setDesignation(_node->getId());
  }

  void DeclarationExpressionSyntax::removeDesignation() {
      if (m_Designation) {
        removeParentEdge(m_Designation);
        if (factory->getExistsReverseEdges())
          factory->reverseEdges->removeEdge(m_Designation, m_id, edkDeclarationExpressionSyntax_Designation);
      }
      m_Designation = 0;
  }

  void DeclarationExpressionSyntax::setType(NodeId _id) {
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
          factory->reverseEdges->removeEdge(m_Type, m_id, edkDeclarationExpressionSyntax_Type);
      }
      m_Type = _node->getId();
      if (m_Type != 0)
        setParentEdge(factory->getPointer(m_Type), edkDeclarationExpressionSyntax_Type);
      if (factory->getExistsReverseEdges())
        factory->reverseEdges->insertEdge(m_Type, this->getId(), edkDeclarationExpressionSyntax_Type);
    } else {
      if (m_Type) {
        throw CsharpException(COLUMBUS_LOCATION, CMSG_EX_CAN_T_SET_EDGE_TO_NULL);
      }
    }
  }

  void DeclarationExpressionSyntax::setType(expression::TypeSyntax *_node) {
    if (_node == NULL)
      throw CsharpException(COLUMBUS_LOCATION, CMSG_EX_CAN_T_SET_EDGE_TO_NULL);

    setType(_node->getId());
  }

  void DeclarationExpressionSyntax::removeType() {
      if (m_Type) {
        removeParentEdge(m_Type);
        if (factory->getExistsReverseEdges())
          factory->reverseEdges->removeEdge(m_Type, m_id, edkDeclarationExpressionSyntax_Type);
      }
      m_Type = 0;
  }

  void DeclarationExpressionSyntax::accept(Visitor &visitor) const {
    visitor.visit(*this);
  }

  void DeclarationExpressionSyntax::acceptEnd(Visitor &visitor) const {
    visitor.visitEnd(*this);
  }

  double DeclarationExpressionSyntax::getSimilarity(const base::Base& base){
    if(base.getNodeKind() == getNodeKind()) {
      return 1.0;
    } else {
      return 0.0;
    }
  }

  void DeclarationExpressionSyntax::swapStringTable(RefDistributorStrTable& newStrTable, std::map<Key,Key>& oldAndNewStrKeyMap ){
    std::map<Key,Key>::iterator foundKeyId;

      m_position.swapStringTable(newStrTable,oldAndNewStrKeyMap);

  }

  NodeHashType DeclarationExpressionSyntax::getHash(std::set<NodeId>& travNodes) const {
    if (hashOk) return nodeHashCache;
    common::WriteMsg::write(CMSG_GET_THE_NODE_HASH_OF_NODE_BEGIN,this->getId()); 
    if (travNodes.count(getId())>0) {
      common::WriteMsg::write(CMSG_GET_THE_NODE_HASH_OF_NODE_SKIP);
      return 0;
    }
    travNodes.insert(getId());
    Crc_type resultHash;
    resultHash.process_bytes( "expression::DeclarationExpressionSyntax", strlen("expression::DeclarationExpressionSyntax"));
    common::WriteMsg::write(CMSG_GET_THE_NODE_HASH_OF_NODE_END,resultHash.checksum()); 
    nodeHashCache = resultHash.checksum();
    hashOk = true;
    return nodeHashCache;
  }

  void DeclarationExpressionSyntax::save(io::BinaryIO &binIo,bool withVirtualBase  /*= true*/) const {
    ExpressionSyntax::save(binIo,false);

    binIo.writeUInt4(m_Designation);
    binIo.writeUInt4(m_Type);

  }

  void DeclarationExpressionSyntax::load(io::BinaryIO &binIo, bool withVirtualBase /*= true*/) {
    ExpressionSyntax::load(binIo,false);

    m_Designation =  binIo.readUInt4();
    if (m_Designation != 0)
      setParentEdge(factory->getPointer(m_Designation),edkDeclarationExpressionSyntax_Designation);

    m_Type =  binIo.readUInt4();
    if (m_Type != 0)
      setParentEdge(factory->getPointer(m_Type),edkDeclarationExpressionSyntax_Type);

  }


}


}}}
