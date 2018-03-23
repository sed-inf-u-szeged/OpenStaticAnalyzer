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
  DelegateDeclarationSyntax::DelegateDeclarationSyntax(NodeId _id, Factory *_factory) :
    MemberDeclarationSyntax(_id, _factory),
    m_identifier(0),
    AttributeListsContainer(),
    ConstraintClausesContainer(),
    m_ParameterList(0),
    m_ReturnType(0)
  {
  }

  DelegateDeclarationSyntax::~DelegateDeclarationSyntax() {
  }

  void DelegateDeclarationSyntax::prepareDelete(bool tryOnVirtualParent){
    while (!AttributeListsContainer.empty()) {
      const NodeId id = *AttributeListsContainer.begin();
      removeParentEdge(id);
      if (factory->getExistsReverseEdges())
        factory->reverseEdges->removeEdge(id, this->getId(), edkDelegateDeclarationSyntax_AttributeLists);
      AttributeListsContainer.pop_front();
    }
    while (!ConstraintClausesContainer.empty()) {
      const NodeId id = *ConstraintClausesContainer.begin();
      removeParentEdge(id);
      if (factory->getExistsReverseEdges())
        factory->reverseEdges->removeEdge(id, this->getId(), edkDelegateDeclarationSyntax_ConstraintClauses);
      ConstraintClausesContainer.pop_front();
    }
    removeParameterList();
    removeReturnType();
    structure::MemberDeclarationSyntax::prepareDelete(false);
  }

  NodeKind DelegateDeclarationSyntax::getNodeKind() const {
    return ndkDelegateDeclarationSyntax;
  }

  Key DelegateDeclarationSyntax::getIdentifierKey() const {
    return m_identifier;
  }

  const std::string& DelegateDeclarationSyntax::getIdentifier() const {
    return factory->getStringTable().get(m_identifier);
  }

  void DelegateDeclarationSyntax::setIdentifierKey(Key _identifier) {
    m_identifier = _identifier;
  }

  void DelegateDeclarationSyntax::setIdentifier(const std::string& _identifier) {
    m_identifier = factory->getStringTable().set(_identifier);
  }

  ListIterator<structure::AttributeListSyntax> DelegateDeclarationSyntax::getAttributeListsListIteratorBegin() const {
    return ListIterator<structure::AttributeListSyntax>(&AttributeListsContainer, factory, true);
  }

  ListIterator<structure::AttributeListSyntax> DelegateDeclarationSyntax::getAttributeListsListIteratorEnd() const {
    return ListIterator<structure::AttributeListSyntax>(&AttributeListsContainer, factory, false);
  }

  bool DelegateDeclarationSyntax::getAttributeListsIsEmpty() const {
    return getAttributeListsListIteratorBegin() == getAttributeListsListIteratorEnd();
  }

  unsigned int DelegateDeclarationSyntax::getAttributeListsSize() const {
    unsigned int size = 0;
    ListIterator<structure::AttributeListSyntax> endIt = getAttributeListsListIteratorEnd();
    for (ListIterator<structure::AttributeListSyntax> it = getAttributeListsListIteratorBegin(); it != endIt; ++it) {
      ++size;
    }
    return size;
  }

  ListIterator<structure::TypeParameterConstraintClauseSyntax> DelegateDeclarationSyntax::getConstraintClausesListIteratorBegin() const {
    return ListIterator<structure::TypeParameterConstraintClauseSyntax>(&ConstraintClausesContainer, factory, true);
  }

  ListIterator<structure::TypeParameterConstraintClauseSyntax> DelegateDeclarationSyntax::getConstraintClausesListIteratorEnd() const {
    return ListIterator<structure::TypeParameterConstraintClauseSyntax>(&ConstraintClausesContainer, factory, false);
  }

  bool DelegateDeclarationSyntax::getConstraintClausesIsEmpty() const {
    return getConstraintClausesListIteratorBegin() == getConstraintClausesListIteratorEnd();
  }

  unsigned int DelegateDeclarationSyntax::getConstraintClausesSize() const {
    unsigned int size = 0;
    ListIterator<structure::TypeParameterConstraintClauseSyntax> endIt = getConstraintClausesListIteratorEnd();
    for (ListIterator<structure::TypeParameterConstraintClauseSyntax> it = getConstraintClausesListIteratorBegin(); it != endIt; ++it) {
      ++size;
    }
    return size;
  }

  structure::ParameterListSyntax* DelegateDeclarationSyntax::getParameterList() const {
    structure::ParameterListSyntax *_node = NULL;
    if (m_ParameterList != 0)
      _node = dynamic_cast<structure::ParameterListSyntax*>(factory->getPointer(m_ParameterList));
    if ( (_node == NULL) || factory->getIsFiltered(_node))
      return NULL;

    return _node;
  }

  expression::TypeSyntax* DelegateDeclarationSyntax::getReturnType() const {
    expression::TypeSyntax *_node = NULL;
    if (m_ReturnType != 0)
      _node = dynamic_cast<expression::TypeSyntax*>(factory->getPointer(m_ReturnType));
    if ( (_node == NULL) || factory->getIsFiltered(_node))
      return NULL;

    return _node;
  }

  bool DelegateDeclarationSyntax::setEdge(EdgeKind edgeKind, NodeId edgeEnd, bool tryOnVirtualParent) {
    switch (edgeKind) {
      case edkDelegateDeclarationSyntax_AttributeLists:
        addAttributeLists(edgeEnd);
        return true;
      case edkDelegateDeclarationSyntax_ConstraintClauses:
        addConstraintClauses(edgeEnd);
        return true;
      case edkDelegateDeclarationSyntax_ParameterList:
        setParameterList(edgeEnd);
        return true;
      case edkDelegateDeclarationSyntax_ReturnType:
        setReturnType(edgeEnd);
        return true;
      default:
        break;
    }
    if (structure::MemberDeclarationSyntax::setEdge(edgeKind, edgeEnd, false)) {
      return true;
    }
    return false;
  }

  bool DelegateDeclarationSyntax::removeEdge(EdgeKind edgeKind, NodeId edgeEnd, bool tryOnVirtualParent) {
    switch (edgeKind) {
      case edkDelegateDeclarationSyntax_AttributeLists:
        removeAttributeLists(edgeEnd);
        return true;
      case edkDelegateDeclarationSyntax_ConstraintClauses:
        removeConstraintClauses(edgeEnd);
        return true;
      case edkDelegateDeclarationSyntax_ParameterList:
        removeParameterList();
        return true;
      case edkDelegateDeclarationSyntax_ReturnType:
        removeReturnType();
        return true;
      default:
        break;
    }
    if (structure::MemberDeclarationSyntax::removeEdge(edgeKind, edgeEnd, false)) {
      return true;
    }
    return false;
  }

  void DelegateDeclarationSyntax::addAttributeLists(const structure::AttributeListSyntax *_node) {
    if (_node == NULL)
      throw CsharpException(COLUMBUS_LOCATION, CMSG_EX_THE_NODE_IS_NULL);

    if (&(_node->getFactory()) != this->factory)
      throw CsharpException(COLUMBUS_LOCATION, CMSG_EX_THE_FACTORY_OF_NODES_DOES_NOT_MATCH);

    if (!((_node->getNodeKind() == ndkAttributeListSyntax) ))
      throw CsharpException(COLUMBUS_LOCATION, CMSG_EX_INVALID_NODE_KIND);

    AttributeListsContainer.push_back(_node->getId());
    setParentEdge(_node,edkDelegateDeclarationSyntax_AttributeLists);

    if (factory->reverseEdges)
      factory->reverseEdges->insertEdge(_node, this, edkDelegateDeclarationSyntax_AttributeLists);
  }

  void DelegateDeclarationSyntax::addAttributeLists(NodeId _id) {
    const structure::AttributeListSyntax *node = dynamic_cast<structure::AttributeListSyntax*>(factory->getPointer(_id));
    if (node == NULL)
      throw CsharpException(COLUMBUS_LOCATION, CMSG_EX_INVALID_NODE_KIND);
    addAttributeLists( node );
  }

  void DelegateDeclarationSyntax::removeAttributeLists(NodeId id) {
    if (!factory->getExist(id))
      throw CsharpException(COLUMBUS_LOCATION, CMSG_EX_THE_END_POINT_OF_THE_EDGE_DOES_NOT_EXIST);

    ListIterator<structure::AttributeListSyntax>::Container::iterator it = find(AttributeListsContainer.begin(), AttributeListsContainer.end(), id);

    if (it == AttributeListsContainer.end())
      throw CsharpException(COLUMBUS_LOCATION, CMSG_EX_THE_END_POINT_OF_THE_EDGE_DOES_NOT_EXIST);

    AttributeListsContainer.erase(it);

    removeParentEdge(id);

    if (factory->getExistsReverseEdges())
      factory->reverseEdges->removeEdge(id, this->getId(), edkDelegateDeclarationSyntax_AttributeLists);
  }

  void DelegateDeclarationSyntax::removeAttributeLists(structure::AttributeListSyntax *_node) {
    if (_node == NULL)
      throw CsharpException(COLUMBUS_LOCATION, CMSG_EX_THE_EDGE_IS_NULL);

    removeAttributeLists(_node->getId());
  }

  void DelegateDeclarationSyntax::addConstraintClauses(const structure::TypeParameterConstraintClauseSyntax *_node) {
    if (_node == NULL)
      throw CsharpException(COLUMBUS_LOCATION, CMSG_EX_THE_NODE_IS_NULL);

    if (&(_node->getFactory()) != this->factory)
      throw CsharpException(COLUMBUS_LOCATION, CMSG_EX_THE_FACTORY_OF_NODES_DOES_NOT_MATCH);

    if (!((_node->getNodeKind() == ndkTypeParameterConstraintClauseSyntax) ))
      throw CsharpException(COLUMBUS_LOCATION, CMSG_EX_INVALID_NODE_KIND);

    ConstraintClausesContainer.push_back(_node->getId());
    setParentEdge(_node,edkDelegateDeclarationSyntax_ConstraintClauses);

    if (factory->reverseEdges)
      factory->reverseEdges->insertEdge(_node, this, edkDelegateDeclarationSyntax_ConstraintClauses);
  }

  void DelegateDeclarationSyntax::addConstraintClauses(NodeId _id) {
    const structure::TypeParameterConstraintClauseSyntax *node = dynamic_cast<structure::TypeParameterConstraintClauseSyntax*>(factory->getPointer(_id));
    if (node == NULL)
      throw CsharpException(COLUMBUS_LOCATION, CMSG_EX_INVALID_NODE_KIND);
    addConstraintClauses( node );
  }

  void DelegateDeclarationSyntax::removeConstraintClauses(NodeId id) {
    if (!factory->getExist(id))
      throw CsharpException(COLUMBUS_LOCATION, CMSG_EX_THE_END_POINT_OF_THE_EDGE_DOES_NOT_EXIST);

    ListIterator<structure::TypeParameterConstraintClauseSyntax>::Container::iterator it = find(ConstraintClausesContainer.begin(), ConstraintClausesContainer.end(), id);

    if (it == ConstraintClausesContainer.end())
      throw CsharpException(COLUMBUS_LOCATION, CMSG_EX_THE_END_POINT_OF_THE_EDGE_DOES_NOT_EXIST);

    ConstraintClausesContainer.erase(it);

    removeParentEdge(id);

    if (factory->getExistsReverseEdges())
      factory->reverseEdges->removeEdge(id, this->getId(), edkDelegateDeclarationSyntax_ConstraintClauses);
  }

  void DelegateDeclarationSyntax::removeConstraintClauses(structure::TypeParameterConstraintClauseSyntax *_node) {
    if (_node == NULL)
      throw CsharpException(COLUMBUS_LOCATION, CMSG_EX_THE_EDGE_IS_NULL);

    removeConstraintClauses(_node->getId());
  }

  void DelegateDeclarationSyntax::setParameterList(NodeId _id) {
    structure::ParameterListSyntax *_node = NULL;
    if (_id) {
      if (!factory->getExist(_id))
        throw CsharpException(COLUMBUS_LOCATION, CMSG_EX_THE_END_POINT_OF_THE_EDGE_DOES_NOT_EXIST);

      _node = dynamic_cast<structure::ParameterListSyntax*> (factory->getPointer(_id));
      if ( _node == NULL) {
        throw CsharpException(COLUMBUS_LOCATION, CMSG_EX_INVALID_NODE_KIND);
      }
      if (&(_node->getFactory()) != this->factory)
        throw CsharpException(COLUMBUS_LOCATION, CMSG_EX_THE_FACTORY_OF_NODES_DOES_NOT_MATCH );

      if (m_ParameterList) {
        removeParentEdge(m_ParameterList);
        if (factory->getExistsReverseEdges())
          factory->reverseEdges->removeEdge(m_ParameterList, m_id, edkDelegateDeclarationSyntax_ParameterList);
      }
      m_ParameterList = _node->getId();
      if (m_ParameterList != 0)
        setParentEdge(factory->getPointer(m_ParameterList), edkDelegateDeclarationSyntax_ParameterList);
      if (factory->getExistsReverseEdges())
        factory->reverseEdges->insertEdge(m_ParameterList, this->getId(), edkDelegateDeclarationSyntax_ParameterList);
    } else {
      if (m_ParameterList) {
        throw CsharpException(COLUMBUS_LOCATION, CMSG_EX_CAN_T_SET_EDGE_TO_NULL);
      }
    }
  }

  void DelegateDeclarationSyntax::setParameterList(structure::ParameterListSyntax *_node) {
    if (_node == NULL)
      throw CsharpException(COLUMBUS_LOCATION, CMSG_EX_CAN_T_SET_EDGE_TO_NULL);

    setParameterList(_node->getId());
  }

  void DelegateDeclarationSyntax::removeParameterList() {
      if (m_ParameterList) {
        removeParentEdge(m_ParameterList);
        if (factory->getExistsReverseEdges())
          factory->reverseEdges->removeEdge(m_ParameterList, m_id, edkDelegateDeclarationSyntax_ParameterList);
      }
      m_ParameterList = 0;
  }

  void DelegateDeclarationSyntax::setReturnType(NodeId _id) {
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
          factory->reverseEdges->removeEdge(m_ReturnType, m_id, edkDelegateDeclarationSyntax_ReturnType);
      }
      m_ReturnType = _node->getId();
      if (m_ReturnType != 0)
        setParentEdge(factory->getPointer(m_ReturnType), edkDelegateDeclarationSyntax_ReturnType);
      if (factory->getExistsReverseEdges())
        factory->reverseEdges->insertEdge(m_ReturnType, this->getId(), edkDelegateDeclarationSyntax_ReturnType);
    } else {
      if (m_ReturnType) {
        throw CsharpException(COLUMBUS_LOCATION, CMSG_EX_CAN_T_SET_EDGE_TO_NULL);
      }
    }
  }

  void DelegateDeclarationSyntax::setReturnType(expression::TypeSyntax *_node) {
    if (_node == NULL)
      throw CsharpException(COLUMBUS_LOCATION, CMSG_EX_CAN_T_SET_EDGE_TO_NULL);

    setReturnType(_node->getId());
  }

  void DelegateDeclarationSyntax::removeReturnType() {
      if (m_ReturnType) {
        removeParentEdge(m_ReturnType);
        if (factory->getExistsReverseEdges())
          factory->reverseEdges->removeEdge(m_ReturnType, m_id, edkDelegateDeclarationSyntax_ReturnType);
      }
      m_ReturnType = 0;
  }

  void DelegateDeclarationSyntax::accept(Visitor &visitor) const {
    visitor.visit(*this);
  }

  void DelegateDeclarationSyntax::acceptEnd(Visitor &visitor) const {
    visitor.visitEnd(*this);
  }

  double DelegateDeclarationSyntax::getSimilarity(const base::Base& base){
    if(base.getNodeKind() == getNodeKind()) {
      const DelegateDeclarationSyntax& node = dynamic_cast<const DelegateDeclarationSyntax&>(base);
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

  void DelegateDeclarationSyntax::swapStringTable(RefDistributorStrTable& newStrTable, std::map<Key,Key>& oldAndNewStrKeyMap ){
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

  NodeHashType DelegateDeclarationSyntax::getHash(std::set<NodeId>& travNodes) const {
    if (hashOk) return nodeHashCache;
    common::WriteMsg::write(CMSG_GET_THE_NODE_HASH_OF_NODE_BEGIN,this->getId()); 
    if (travNodes.count(getId())>0) {
      common::WriteMsg::write(CMSG_GET_THE_NODE_HASH_OF_NODE_SKIP);
      return 0;
    }
    travNodes.insert(getId());
    Crc_type resultHash;
    resultHash.process_bytes( "structure::DelegateDeclarationSyntax", strlen("structure::DelegateDeclarationSyntax"));
    common::WriteMsg::write(CMSG_GET_THE_NODE_HASH_OF_NODE_END,resultHash.checksum()); 
    nodeHashCache = resultHash.checksum();
    hashOk = true;
    return nodeHashCache;
  }

  void DelegateDeclarationSyntax::save(io::BinaryIO &binIo,bool withVirtualBase  /*= true*/) const {
    MemberDeclarationSyntax::save(binIo,false);

    factory->getStringTable().setType(m_identifier, StrTable::strToSave);
    binIo.writeUInt4(m_identifier);

    binIo.writeUInt4(m_ParameterList);
    binIo.writeUInt4(m_ReturnType);


    for (ListIterator<structure::AttributeListSyntax>::Container::const_iterator it = AttributeListsContainer.begin(); it != AttributeListsContainer.end(); ++it) {
      binIo.writeUInt4(*it);
    }
    binIo.writeUInt4(0); // This is the end sign

    for (ListIterator<structure::TypeParameterConstraintClauseSyntax>::Container::const_iterator it = ConstraintClausesContainer.begin(); it != ConstraintClausesContainer.end(); ++it) {
      binIo.writeUInt4(*it);
    }
    binIo.writeUInt4(0); // This is the end sign
  }

  void DelegateDeclarationSyntax::load(io::BinaryIO &binIo, bool withVirtualBase /*= true*/) {
    MemberDeclarationSyntax::load(binIo,false);

    m_identifier = binIo.readUInt4();

    m_ParameterList =  binIo.readUInt4();
    if (m_ParameterList != 0)
      setParentEdge(factory->getPointer(m_ParameterList),edkDelegateDeclarationSyntax_ParameterList);

    m_ReturnType =  binIo.readUInt4();
    if (m_ReturnType != 0)
      setParentEdge(factory->getPointer(m_ReturnType),edkDelegateDeclarationSyntax_ReturnType);

    NodeId _id;

    _id = binIo.readUInt4();
    while (_id) {
      AttributeListsContainer.push_back(_id);
      setParentEdge(factory->getPointer(_id),edkDelegateDeclarationSyntax_AttributeLists);
      _id = binIo.readUInt4();
    }

    _id = binIo.readUInt4();
    while (_id) {
      ConstraintClausesContainer.push_back(_id);
      setParentEdge(factory->getPointer(_id),edkDelegateDeclarationSyntax_ConstraintClauses);
      _id = binIo.readUInt4();
    }
  }


}


}}}
