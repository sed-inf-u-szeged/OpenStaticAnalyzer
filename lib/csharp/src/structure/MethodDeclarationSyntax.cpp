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
  MethodDeclarationSyntax::MethodDeclarationSyntax(NodeId _id, Factory *_factory) :
    BaseMethodDeclarationSyntax(_id, _factory),
    m_identifier(0),
    ConstraintClausesContainer(),
    m_ExplicitInterfaceSpecifier(0),
    m_ExpressionBody(0),
    m_ReturnType(0)
  {
  }

  MethodDeclarationSyntax::~MethodDeclarationSyntax() {
  }

  void MethodDeclarationSyntax::prepareDelete(bool tryOnVirtualParent){
    while (!ConstraintClausesContainer.empty()) {
      const NodeId id = *ConstraintClausesContainer.begin();
      removeParentEdge(id);
      if (factory->getExistsReverseEdges())
        factory->reverseEdges->removeEdge(id, this->getId(), edkMethodDeclarationSyntax_ConstraintClauses);
      ConstraintClausesContainer.pop_front();
    }
    removeExplicitInterfaceSpecifier();
    removeExpressionBody();
    removeReturnType();
    structure::BaseMethodDeclarationSyntax::prepareDelete(false);
  }

  NodeKind MethodDeclarationSyntax::getNodeKind() const {
    return ndkMethodDeclarationSyntax;
  }

  Key MethodDeclarationSyntax::getIdentifierKey() const {
    return m_identifier;
  }

  const std::string& MethodDeclarationSyntax::getIdentifier() const {
    return factory->getStringTable().get(m_identifier);
  }

  void MethodDeclarationSyntax::setIdentifierKey(Key _identifier) {
    m_identifier = _identifier;
  }

  void MethodDeclarationSyntax::setIdentifier(const std::string& _identifier) {
    m_identifier = factory->getStringTable().set(_identifier);
  }

  ListIterator<structure::TypeParameterConstraintClauseSyntax> MethodDeclarationSyntax::getConstraintClausesListIteratorBegin() const {
    return ListIterator<structure::TypeParameterConstraintClauseSyntax>(&ConstraintClausesContainer, factory, true);
  }

  ListIterator<structure::TypeParameterConstraintClauseSyntax> MethodDeclarationSyntax::getConstraintClausesListIteratorEnd() const {
    return ListIterator<structure::TypeParameterConstraintClauseSyntax>(&ConstraintClausesContainer, factory, false);
  }

  bool MethodDeclarationSyntax::getConstraintClausesIsEmpty() const {
    return getConstraintClausesListIteratorBegin() == getConstraintClausesListIteratorEnd();
  }

  unsigned int MethodDeclarationSyntax::getConstraintClausesSize() const {
    unsigned int size = 0;
    ListIterator<structure::TypeParameterConstraintClauseSyntax> endIt = getConstraintClausesListIteratorEnd();
    for (ListIterator<structure::TypeParameterConstraintClauseSyntax> it = getConstraintClausesListIteratorBegin(); it != endIt; ++it) {
      ++size;
    }
    return size;
  }

  structure::ExplicitInterfaceSpecifierSyntax* MethodDeclarationSyntax::getExplicitInterfaceSpecifier() const {
    structure::ExplicitInterfaceSpecifierSyntax *_node = NULL;
    if (m_ExplicitInterfaceSpecifier != 0)
      _node = dynamic_cast<structure::ExplicitInterfaceSpecifierSyntax*>(factory->getPointer(m_ExplicitInterfaceSpecifier));
    if ( (_node == NULL) || factory->getIsFiltered(_node))
      return NULL;

    return _node;
  }

  structure::ArrowExpressionClauseSyntax* MethodDeclarationSyntax::getExpressionBody() const {
    structure::ArrowExpressionClauseSyntax *_node = NULL;
    if (m_ExpressionBody != 0)
      _node = dynamic_cast<structure::ArrowExpressionClauseSyntax*>(factory->getPointer(m_ExpressionBody));
    if ( (_node == NULL) || factory->getIsFiltered(_node))
      return NULL;

    return _node;
  }

  expression::TypeSyntax* MethodDeclarationSyntax::getReturnType() const {
    expression::TypeSyntax *_node = NULL;
    if (m_ReturnType != 0)
      _node = dynamic_cast<expression::TypeSyntax*>(factory->getPointer(m_ReturnType));
    if ( (_node == NULL) || factory->getIsFiltered(_node))
      return NULL;

    return _node;
  }

  bool MethodDeclarationSyntax::setEdge(EdgeKind edgeKind, NodeId edgeEnd, bool tryOnVirtualParent) {
    switch (edgeKind) {
      case edkMethodDeclarationSyntax_ConstraintClauses:
        addConstraintClauses(edgeEnd);
        return true;
      case edkMethodDeclarationSyntax_ExplicitInterfaceSpecifier:
        setExplicitInterfaceSpecifier(edgeEnd);
        return true;
      case edkMethodDeclarationSyntax_ExpressionBody:
        setExpressionBody(edgeEnd);
        return true;
      case edkMethodDeclarationSyntax_ReturnType:
        setReturnType(edgeEnd);
        return true;
      default:
        break;
    }
    if (structure::BaseMethodDeclarationSyntax::setEdge(edgeKind, edgeEnd, false)) {
      return true;
    }
    return false;
  }

  bool MethodDeclarationSyntax::removeEdge(EdgeKind edgeKind, NodeId edgeEnd, bool tryOnVirtualParent) {
    switch (edgeKind) {
      case edkMethodDeclarationSyntax_ConstraintClauses:
        removeConstraintClauses(edgeEnd);
        return true;
      case edkMethodDeclarationSyntax_ExplicitInterfaceSpecifier:
        removeExplicitInterfaceSpecifier();
        return true;
      case edkMethodDeclarationSyntax_ExpressionBody:
        removeExpressionBody();
        return true;
      case edkMethodDeclarationSyntax_ReturnType:
        removeReturnType();
        return true;
      default:
        break;
    }
    if (structure::BaseMethodDeclarationSyntax::removeEdge(edgeKind, edgeEnd, false)) {
      return true;
    }
    return false;
  }

  void MethodDeclarationSyntax::addConstraintClauses(const structure::TypeParameterConstraintClauseSyntax *_node) {
    if (_node == NULL)
      throw CsharpException(COLUMBUS_LOCATION, CMSG_EX_THE_NODE_IS_NULL);

    if (&(_node->getFactory()) != this->factory)
      throw CsharpException(COLUMBUS_LOCATION, CMSG_EX_THE_FACTORY_OF_NODES_DOES_NOT_MATCH);

    if (!((_node->getNodeKind() == ndkTypeParameterConstraintClauseSyntax) ))
      throw CsharpException(COLUMBUS_LOCATION, CMSG_EX_INVALID_NODE_KIND);

    ConstraintClausesContainer.push_back(_node->getId());
    setParentEdge(_node,edkMethodDeclarationSyntax_ConstraintClauses);

    if (factory->reverseEdges)
      factory->reverseEdges->insertEdge(_node, this, edkMethodDeclarationSyntax_ConstraintClauses);
  }

  void MethodDeclarationSyntax::addConstraintClauses(NodeId _id) {
    const structure::TypeParameterConstraintClauseSyntax *node = dynamic_cast<structure::TypeParameterConstraintClauseSyntax*>(factory->getPointer(_id));
    if (node == NULL)
      throw CsharpException(COLUMBUS_LOCATION, CMSG_EX_INVALID_NODE_KIND);
    addConstraintClauses( node );
  }

  void MethodDeclarationSyntax::removeConstraintClauses(NodeId id) {
    if (!factory->getExist(id))
      throw CsharpException(COLUMBUS_LOCATION, CMSG_EX_THE_END_POINT_OF_THE_EDGE_DOES_NOT_EXIST);

    ListIterator<structure::TypeParameterConstraintClauseSyntax>::Container::iterator it = find(ConstraintClausesContainer.begin(), ConstraintClausesContainer.end(), id);

    if (it == ConstraintClausesContainer.end())
      throw CsharpException(COLUMBUS_LOCATION, CMSG_EX_THE_END_POINT_OF_THE_EDGE_DOES_NOT_EXIST);

    ConstraintClausesContainer.erase(it);

    removeParentEdge(id);

    if (factory->getExistsReverseEdges())
      factory->reverseEdges->removeEdge(id, this->getId(), edkMethodDeclarationSyntax_ConstraintClauses);
  }

  void MethodDeclarationSyntax::removeConstraintClauses(structure::TypeParameterConstraintClauseSyntax *_node) {
    if (_node == NULL)
      throw CsharpException(COLUMBUS_LOCATION, CMSG_EX_THE_EDGE_IS_NULL);

    removeConstraintClauses(_node->getId());
  }

  void MethodDeclarationSyntax::setExplicitInterfaceSpecifier(NodeId _id) {
    structure::ExplicitInterfaceSpecifierSyntax *_node = NULL;
    if (_id) {
      if (!factory->getExist(_id))
        throw CsharpException(COLUMBUS_LOCATION, CMSG_EX_THE_END_POINT_OF_THE_EDGE_DOES_NOT_EXIST);

      _node = dynamic_cast<structure::ExplicitInterfaceSpecifierSyntax*> (factory->getPointer(_id));
      if ( _node == NULL) {
        throw CsharpException(COLUMBUS_LOCATION, CMSG_EX_INVALID_NODE_KIND);
      }
      if (&(_node->getFactory()) != this->factory)
        throw CsharpException(COLUMBUS_LOCATION, CMSG_EX_THE_FACTORY_OF_NODES_DOES_NOT_MATCH );

      if (m_ExplicitInterfaceSpecifier) {
        removeParentEdge(m_ExplicitInterfaceSpecifier);
        if (factory->getExistsReverseEdges())
          factory->reverseEdges->removeEdge(m_ExplicitInterfaceSpecifier, m_id, edkMethodDeclarationSyntax_ExplicitInterfaceSpecifier);
      }
      m_ExplicitInterfaceSpecifier = _node->getId();
      if (m_ExplicitInterfaceSpecifier != 0)
        setParentEdge(factory->getPointer(m_ExplicitInterfaceSpecifier), edkMethodDeclarationSyntax_ExplicitInterfaceSpecifier);
      if (factory->getExistsReverseEdges())
        factory->reverseEdges->insertEdge(m_ExplicitInterfaceSpecifier, this->getId(), edkMethodDeclarationSyntax_ExplicitInterfaceSpecifier);
    } else {
      if (m_ExplicitInterfaceSpecifier) {
        throw CsharpException(COLUMBUS_LOCATION, CMSG_EX_CAN_T_SET_EDGE_TO_NULL);
      }
    }
  }

  void MethodDeclarationSyntax::setExplicitInterfaceSpecifier(structure::ExplicitInterfaceSpecifierSyntax *_node) {
    if (_node == NULL)
      throw CsharpException(COLUMBUS_LOCATION, CMSG_EX_CAN_T_SET_EDGE_TO_NULL);

    setExplicitInterfaceSpecifier(_node->getId());
  }

  void MethodDeclarationSyntax::removeExplicitInterfaceSpecifier() {
      if (m_ExplicitInterfaceSpecifier) {
        removeParentEdge(m_ExplicitInterfaceSpecifier);
        if (factory->getExistsReverseEdges())
          factory->reverseEdges->removeEdge(m_ExplicitInterfaceSpecifier, m_id, edkMethodDeclarationSyntax_ExplicitInterfaceSpecifier);
      }
      m_ExplicitInterfaceSpecifier = 0;
  }

  void MethodDeclarationSyntax::setExpressionBody(NodeId _id) {
    structure::ArrowExpressionClauseSyntax *_node = NULL;
    if (_id) {
      if (!factory->getExist(_id))
        throw CsharpException(COLUMBUS_LOCATION, CMSG_EX_THE_END_POINT_OF_THE_EDGE_DOES_NOT_EXIST);

      _node = dynamic_cast<structure::ArrowExpressionClauseSyntax*> (factory->getPointer(_id));
      if ( _node == NULL) {
        throw CsharpException(COLUMBUS_LOCATION, CMSG_EX_INVALID_NODE_KIND);
      }
      if (&(_node->getFactory()) != this->factory)
        throw CsharpException(COLUMBUS_LOCATION, CMSG_EX_THE_FACTORY_OF_NODES_DOES_NOT_MATCH );

      if (m_ExpressionBody) {
        removeParentEdge(m_ExpressionBody);
        if (factory->getExistsReverseEdges())
          factory->reverseEdges->removeEdge(m_ExpressionBody, m_id, edkMethodDeclarationSyntax_ExpressionBody);
      }
      m_ExpressionBody = _node->getId();
      if (m_ExpressionBody != 0)
        setParentEdge(factory->getPointer(m_ExpressionBody), edkMethodDeclarationSyntax_ExpressionBody);
      if (factory->getExistsReverseEdges())
        factory->reverseEdges->insertEdge(m_ExpressionBody, this->getId(), edkMethodDeclarationSyntax_ExpressionBody);
    } else {
      if (m_ExpressionBody) {
        throw CsharpException(COLUMBUS_LOCATION, CMSG_EX_CAN_T_SET_EDGE_TO_NULL);
      }
    }
  }

  void MethodDeclarationSyntax::setExpressionBody(structure::ArrowExpressionClauseSyntax *_node) {
    if (_node == NULL)
      throw CsharpException(COLUMBUS_LOCATION, CMSG_EX_CAN_T_SET_EDGE_TO_NULL);

    setExpressionBody(_node->getId());
  }

  void MethodDeclarationSyntax::removeExpressionBody() {
      if (m_ExpressionBody) {
        removeParentEdge(m_ExpressionBody);
        if (factory->getExistsReverseEdges())
          factory->reverseEdges->removeEdge(m_ExpressionBody, m_id, edkMethodDeclarationSyntax_ExpressionBody);
      }
      m_ExpressionBody = 0;
  }

  void MethodDeclarationSyntax::setReturnType(NodeId _id) {
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

      if (m_ReturnType) {
        removeParentEdge(m_ReturnType);
        if (factory->getExistsReverseEdges())
          factory->reverseEdges->removeEdge(m_ReturnType, m_id, edkMethodDeclarationSyntax_ReturnType);
      }
      m_ReturnType = _node->getId();
      if (m_ReturnType != 0)
        setParentEdge(factory->getPointer(m_ReturnType), edkMethodDeclarationSyntax_ReturnType);
      if (factory->getExistsReverseEdges())
        factory->reverseEdges->insertEdge(m_ReturnType, this->getId(), edkMethodDeclarationSyntax_ReturnType);
    } else {
      if (m_ReturnType) {
        throw CsharpException(COLUMBUS_LOCATION, CMSG_EX_CAN_T_SET_EDGE_TO_NULL);
      }
    }
  }

  void MethodDeclarationSyntax::setReturnType(expression::TypeSyntax *_node) {
    if (_node == NULL)
      throw CsharpException(COLUMBUS_LOCATION, CMSG_EX_CAN_T_SET_EDGE_TO_NULL);

    setReturnType(_node->getId());
  }

  void MethodDeclarationSyntax::removeReturnType() {
      if (m_ReturnType) {
        removeParentEdge(m_ReturnType);
        if (factory->getExistsReverseEdges())
          factory->reverseEdges->removeEdge(m_ReturnType, m_id, edkMethodDeclarationSyntax_ReturnType);
      }
      m_ReturnType = 0;
  }

  void MethodDeclarationSyntax::accept(Visitor &visitor) const {
    visitor.visit(*this);
  }

  void MethodDeclarationSyntax::acceptEnd(Visitor &visitor) const {
    visitor.visitEnd(*this);
  }

  double MethodDeclarationSyntax::getSimilarity(const base::Base& base){
    if(base.getNodeKind() == getNodeKind()) {
      const MethodDeclarationSyntax& node = dynamic_cast<const MethodDeclarationSyntax&>(base);
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

  void MethodDeclarationSyntax::swapStringTable(RefDistributorStrTable& newStrTable, std::map<Key,Key>& oldAndNewStrKeyMap ){
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

  NodeHashType MethodDeclarationSyntax::getHash(std::set<NodeId>& travNodes) const {
    if (hashOk) return nodeHashCache;
    common::WriteMsg::write(CMSG_GET_THE_NODE_HASH_OF_NODE_BEGIN,this->getId()); 
    if (travNodes.count(getId())>0) {
      common::WriteMsg::write(CMSG_GET_THE_NODE_HASH_OF_NODE_SKIP);
      return 0;
    }
    travNodes.insert(getId());
    Crc_type resultHash;
    resultHash.process_bytes( "structure::MethodDeclarationSyntax", strlen("structure::MethodDeclarationSyntax"));
    common::WriteMsg::write(CMSG_GET_THE_NODE_HASH_OF_NODE_END,resultHash.checksum()); 
    nodeHashCache = resultHash.checksum();
    hashOk = true;
    return nodeHashCache;
  }

  void MethodDeclarationSyntax::save(io::BinaryIO &binIo,bool withVirtualBase  /*= true*/) const {
    BaseMethodDeclarationSyntax::save(binIo,false);

    factory->getStringTable().setType(m_identifier, StrTable::strToSave);
    binIo.writeUInt4(m_identifier);

    binIo.writeUInt4(m_ExplicitInterfaceSpecifier);
    binIo.writeUInt4(m_ExpressionBody);
    binIo.writeUInt4(m_ReturnType);


    for (ListIterator<structure::TypeParameterConstraintClauseSyntax>::Container::const_iterator it = ConstraintClausesContainer.begin(); it != ConstraintClausesContainer.end(); ++it) {
      binIo.writeUInt4(*it);
    }
    binIo.writeUInt4(0); // This is the end sign
  }

  void MethodDeclarationSyntax::load(io::BinaryIO &binIo, bool withVirtualBase /*= true*/) {
    BaseMethodDeclarationSyntax::load(binIo,false);

    m_identifier = binIo.readUInt4();

    m_ExplicitInterfaceSpecifier =  binIo.readUInt4();
    if (m_ExplicitInterfaceSpecifier != 0)
      setParentEdge(factory->getPointer(m_ExplicitInterfaceSpecifier),edkMethodDeclarationSyntax_ExplicitInterfaceSpecifier);

    m_ExpressionBody =  binIo.readUInt4();
    if (m_ExpressionBody != 0)
      setParentEdge(factory->getPointer(m_ExpressionBody),edkMethodDeclarationSyntax_ExpressionBody);

    m_ReturnType =  binIo.readUInt4();
    if (m_ReturnType != 0)
      setParentEdge(factory->getPointer(m_ReturnType),edkMethodDeclarationSyntax_ReturnType);

    NodeId _id;

    _id = binIo.readUInt4();
    while (_id) {
      ConstraintClausesContainer.push_back(_id);
      setParentEdge(factory->getPointer(_id),edkMethodDeclarationSyntax_ConstraintClauses);
      _id = binIo.readUInt4();
    }
  }


}


}}}
