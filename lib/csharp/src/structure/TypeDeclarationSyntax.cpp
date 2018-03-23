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
  TypeDeclarationSyntax::TypeDeclarationSyntax(NodeId _id, Factory *_factory) :
    BaseTypeDeclarationSyntax(_id, _factory),
    ConstraintClausesContainer(),
    MembersContainer(),
    m_TypeParameterList(0)
  {
  }

  TypeDeclarationSyntax::~TypeDeclarationSyntax() {
  }

  void TypeDeclarationSyntax::prepareDelete(bool tryOnVirtualParent){
    while (!ConstraintClausesContainer.empty()) {
      const NodeId id = *ConstraintClausesContainer.begin();
      removeParentEdge(id);
      if (factory->getExistsReverseEdges())
        factory->reverseEdges->removeEdge(id, this->getId(), edkTypeDeclarationSyntax_ConstraintClauses);
      ConstraintClausesContainer.pop_front();
    }
    while (!MembersContainer.empty()) {
      const NodeId id = *MembersContainer.begin();
      removeParentEdge(id);
      if (factory->getExistsReverseEdges())
        factory->reverseEdges->removeEdge(id, this->getId(), edkTypeDeclarationSyntax_Members);
      MembersContainer.pop_front();
    }
    removeTypeParameterList();
    structure::BaseTypeDeclarationSyntax::prepareDelete(false);
  }

  ListIterator<structure::TypeParameterConstraintClauseSyntax> TypeDeclarationSyntax::getConstraintClausesListIteratorBegin() const {
    return ListIterator<structure::TypeParameterConstraintClauseSyntax>(&ConstraintClausesContainer, factory, true);
  }

  ListIterator<structure::TypeParameterConstraintClauseSyntax> TypeDeclarationSyntax::getConstraintClausesListIteratorEnd() const {
    return ListIterator<structure::TypeParameterConstraintClauseSyntax>(&ConstraintClausesContainer, factory, false);
  }

  bool TypeDeclarationSyntax::getConstraintClausesIsEmpty() const {
    return getConstraintClausesListIteratorBegin() == getConstraintClausesListIteratorEnd();
  }

  unsigned int TypeDeclarationSyntax::getConstraintClausesSize() const {
    unsigned int size = 0;
    ListIterator<structure::TypeParameterConstraintClauseSyntax> endIt = getConstraintClausesListIteratorEnd();
    for (ListIterator<structure::TypeParameterConstraintClauseSyntax> it = getConstraintClausesListIteratorBegin(); it != endIt; ++it) {
      ++size;
    }
    return size;
  }

  ListIterator<structure::MemberDeclarationSyntax> TypeDeclarationSyntax::getMembersListIteratorBegin() const {
    return ListIterator<structure::MemberDeclarationSyntax>(&MembersContainer, factory, true);
  }

  ListIterator<structure::MemberDeclarationSyntax> TypeDeclarationSyntax::getMembersListIteratorEnd() const {
    return ListIterator<structure::MemberDeclarationSyntax>(&MembersContainer, factory, false);
  }

  bool TypeDeclarationSyntax::getMembersIsEmpty() const {
    return getMembersListIteratorBegin() == getMembersListIteratorEnd();
  }

  unsigned int TypeDeclarationSyntax::getMembersSize() const {
    unsigned int size = 0;
    ListIterator<structure::MemberDeclarationSyntax> endIt = getMembersListIteratorEnd();
    for (ListIterator<structure::MemberDeclarationSyntax> it = getMembersListIteratorBegin(); it != endIt; ++it) {
      ++size;
    }
    return size;
  }

  structure::TypeParameterListSyntax* TypeDeclarationSyntax::getTypeParameterList() const {
    structure::TypeParameterListSyntax *_node = NULL;
    if (m_TypeParameterList != 0)
      _node = dynamic_cast<structure::TypeParameterListSyntax*>(factory->getPointer(m_TypeParameterList));
    if ( (_node == NULL) || factory->getIsFiltered(_node))
      return NULL;

    return _node;
  }

  bool TypeDeclarationSyntax::setEdge(EdgeKind edgeKind, NodeId edgeEnd, bool tryOnVirtualParent) {
    switch (edgeKind) {
      case edkTypeDeclarationSyntax_ConstraintClauses:
        addConstraintClauses(edgeEnd);
        return true;
      case edkTypeDeclarationSyntax_Members:
        addMembers(edgeEnd);
        return true;
      case edkTypeDeclarationSyntax_TypeParameterList:
        setTypeParameterList(edgeEnd);
        return true;
      default:
        break;
    }
    if (structure::BaseTypeDeclarationSyntax::setEdge(edgeKind, edgeEnd, false)) {
      return true;
    }
    return false;
  }

  bool TypeDeclarationSyntax::removeEdge(EdgeKind edgeKind, NodeId edgeEnd, bool tryOnVirtualParent) {
    switch (edgeKind) {
      case edkTypeDeclarationSyntax_ConstraintClauses:
        removeConstraintClauses(edgeEnd);
        return true;
      case edkTypeDeclarationSyntax_Members:
        removeMembers(edgeEnd);
        return true;
      case edkTypeDeclarationSyntax_TypeParameterList:
        removeTypeParameterList();
        return true;
      default:
        break;
    }
    if (structure::BaseTypeDeclarationSyntax::removeEdge(edgeKind, edgeEnd, false)) {
      return true;
    }
    return false;
  }

  void TypeDeclarationSyntax::addConstraintClauses(const structure::TypeParameterConstraintClauseSyntax *_node) {
    if (_node == NULL)
      throw CsharpException(COLUMBUS_LOCATION, CMSG_EX_THE_NODE_IS_NULL);

    if (&(_node->getFactory()) != this->factory)
      throw CsharpException(COLUMBUS_LOCATION, CMSG_EX_THE_FACTORY_OF_NODES_DOES_NOT_MATCH);

    if (!((_node->getNodeKind() == ndkTypeParameterConstraintClauseSyntax) ))
      throw CsharpException(COLUMBUS_LOCATION, CMSG_EX_INVALID_NODE_KIND);

    ConstraintClausesContainer.push_back(_node->getId());
    setParentEdge(_node,edkTypeDeclarationSyntax_ConstraintClauses);

    if (factory->reverseEdges)
      factory->reverseEdges->insertEdge(_node, this, edkTypeDeclarationSyntax_ConstraintClauses);
  }

  void TypeDeclarationSyntax::addConstraintClauses(NodeId _id) {
    const structure::TypeParameterConstraintClauseSyntax *node = dynamic_cast<structure::TypeParameterConstraintClauseSyntax*>(factory->getPointer(_id));
    if (node == NULL)
      throw CsharpException(COLUMBUS_LOCATION, CMSG_EX_INVALID_NODE_KIND);
    addConstraintClauses( node );
  }

  void TypeDeclarationSyntax::removeConstraintClauses(NodeId id) {
    if (!factory->getExist(id))
      throw CsharpException(COLUMBUS_LOCATION, CMSG_EX_THE_END_POINT_OF_THE_EDGE_DOES_NOT_EXIST);

    ListIterator<structure::TypeParameterConstraintClauseSyntax>::Container::iterator it = find(ConstraintClausesContainer.begin(), ConstraintClausesContainer.end(), id);

    if (it == ConstraintClausesContainer.end())
      throw CsharpException(COLUMBUS_LOCATION, CMSG_EX_THE_END_POINT_OF_THE_EDGE_DOES_NOT_EXIST);

    ConstraintClausesContainer.erase(it);

    removeParentEdge(id);

    if (factory->getExistsReverseEdges())
      factory->reverseEdges->removeEdge(id, this->getId(), edkTypeDeclarationSyntax_ConstraintClauses);
  }

  void TypeDeclarationSyntax::removeConstraintClauses(structure::TypeParameterConstraintClauseSyntax *_node) {
    if (_node == NULL)
      throw CsharpException(COLUMBUS_LOCATION, CMSG_EX_THE_EDGE_IS_NULL);

    removeConstraintClauses(_node->getId());
  }

  void TypeDeclarationSyntax::addMembers(const structure::MemberDeclarationSyntax *_node) {
    if (_node == NULL)
      throw CsharpException(COLUMBUS_LOCATION, CMSG_EX_THE_NODE_IS_NULL);

    if (&(_node->getFactory()) != this->factory)
      throw CsharpException(COLUMBUS_LOCATION, CMSG_EX_THE_FACTORY_OF_NODES_DOES_NOT_MATCH);

    if (!(Common::getIsMemberDeclarationSyntax(*_node)))
      throw CsharpException(COLUMBUS_LOCATION, CMSG_EX_INVALID_NODE_KIND);

    MembersContainer.push_back(_node->getId());
    setParentEdge(_node,edkTypeDeclarationSyntax_Members);

    if (factory->reverseEdges)
      factory->reverseEdges->insertEdge(_node, this, edkTypeDeclarationSyntax_Members);
  }

  void TypeDeclarationSyntax::addMembers(NodeId _id) {
    const structure::MemberDeclarationSyntax *node = dynamic_cast<structure::MemberDeclarationSyntax*>(factory->getPointer(_id));
    if (node == NULL)
      throw CsharpException(COLUMBUS_LOCATION, CMSG_EX_INVALID_NODE_KIND);
    addMembers( node );
  }

  void TypeDeclarationSyntax::removeMembers(NodeId id) {
    if (!factory->getExist(id))
      throw CsharpException(COLUMBUS_LOCATION, CMSG_EX_THE_END_POINT_OF_THE_EDGE_DOES_NOT_EXIST);

    ListIterator<structure::MemberDeclarationSyntax>::Container::iterator it = find(MembersContainer.begin(), MembersContainer.end(), id);

    if (it == MembersContainer.end())
      throw CsharpException(COLUMBUS_LOCATION, CMSG_EX_THE_END_POINT_OF_THE_EDGE_DOES_NOT_EXIST);

    MembersContainer.erase(it);

    removeParentEdge(id);

    if (factory->getExistsReverseEdges())
      factory->reverseEdges->removeEdge(id, this->getId(), edkTypeDeclarationSyntax_Members);
  }

  void TypeDeclarationSyntax::removeMembers(structure::MemberDeclarationSyntax *_node) {
    if (_node == NULL)
      throw CsharpException(COLUMBUS_LOCATION, CMSG_EX_THE_EDGE_IS_NULL);

    removeMembers(_node->getId());
  }

  void TypeDeclarationSyntax::setTypeParameterList(NodeId _id) {
    structure::TypeParameterListSyntax *_node = NULL;
    if (_id) {
      if (!factory->getExist(_id))
        throw CsharpException(COLUMBUS_LOCATION, CMSG_EX_THE_END_POINT_OF_THE_EDGE_DOES_NOT_EXIST);

      _node = dynamic_cast<structure::TypeParameterListSyntax*> (factory->getPointer(_id));
      if ( _node == NULL) {
        throw CsharpException(COLUMBUS_LOCATION, CMSG_EX_INVALID_NODE_KIND);
      }
      if (&(_node->getFactory()) != this->factory)
        throw CsharpException(COLUMBUS_LOCATION, CMSG_EX_THE_FACTORY_OF_NODES_DOES_NOT_MATCH );

      if (m_TypeParameterList) {
        removeParentEdge(m_TypeParameterList);
        if (factory->getExistsReverseEdges())
          factory->reverseEdges->removeEdge(m_TypeParameterList, m_id, edkTypeDeclarationSyntax_TypeParameterList);
      }
      m_TypeParameterList = _node->getId();
      if (m_TypeParameterList != 0)
        setParentEdge(factory->getPointer(m_TypeParameterList), edkTypeDeclarationSyntax_TypeParameterList);
      if (factory->getExistsReverseEdges())
        factory->reverseEdges->insertEdge(m_TypeParameterList, this->getId(), edkTypeDeclarationSyntax_TypeParameterList);
    } else {
      if (m_TypeParameterList) {
        throw CsharpException(COLUMBUS_LOCATION, CMSG_EX_CAN_T_SET_EDGE_TO_NULL);
      }
    }
  }

  void TypeDeclarationSyntax::setTypeParameterList(structure::TypeParameterListSyntax *_node) {
    if (_node == NULL)
      throw CsharpException(COLUMBUS_LOCATION, CMSG_EX_CAN_T_SET_EDGE_TO_NULL);

    setTypeParameterList(_node->getId());
  }

  void TypeDeclarationSyntax::removeTypeParameterList() {
      if (m_TypeParameterList) {
        removeParentEdge(m_TypeParameterList);
        if (factory->getExistsReverseEdges())
          factory->reverseEdges->removeEdge(m_TypeParameterList, m_id, edkTypeDeclarationSyntax_TypeParameterList);
      }
      m_TypeParameterList = 0;
  }

  double TypeDeclarationSyntax::getSimilarity(const base::Base& base){
    if(base.getNodeKind() == getNodeKind()) {
      const TypeDeclarationSyntax& node = dynamic_cast<const TypeDeclarationSyntax&>(base);
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

  void TypeDeclarationSyntax::swapStringTable(RefDistributorStrTable& newStrTable, std::map<Key,Key>& oldAndNewStrKeyMap ){
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

  NodeHashType TypeDeclarationSyntax::getHash(std::set<NodeId>& travNodes) const {
    if (hashOk) return nodeHashCache;
    common::WriteMsg::write(CMSG_GET_THE_NODE_HASH_OF_NODE_BEGIN,this->getId()); 
    if (travNodes.count(getId())>0) {
      common::WriteMsg::write(CMSG_GET_THE_NODE_HASH_OF_NODE_SKIP);
      return 0;
    }
    travNodes.insert(getId());
    Crc_type resultHash;
    resultHash.process_bytes( "structure::TypeDeclarationSyntax", strlen("structure::TypeDeclarationSyntax"));
    common::WriteMsg::write(CMSG_GET_THE_NODE_HASH_OF_NODE_END,resultHash.checksum()); 
    nodeHashCache = resultHash.checksum();
    hashOk = true;
    return nodeHashCache;
  }

  void TypeDeclarationSyntax::save(io::BinaryIO &binIo,bool withVirtualBase  /*= true*/) const {
    BaseTypeDeclarationSyntax::save(binIo,false);

    binIo.writeUInt4(m_TypeParameterList);


    for (ListIterator<structure::TypeParameterConstraintClauseSyntax>::Container::const_iterator it = ConstraintClausesContainer.begin(); it != ConstraintClausesContainer.end(); ++it) {
      binIo.writeUInt4(*it);
    }
    binIo.writeUInt4(0); // This is the end sign

    for (ListIterator<structure::MemberDeclarationSyntax>::Container::const_iterator it = MembersContainer.begin(); it != MembersContainer.end(); ++it) {
      binIo.writeUInt4(*it);
    }
    binIo.writeUInt4(0); // This is the end sign
  }

  void TypeDeclarationSyntax::load(io::BinaryIO &binIo, bool withVirtualBase /*= true*/) {
    BaseTypeDeclarationSyntax::load(binIo,false);

    m_TypeParameterList =  binIo.readUInt4();
    if (m_TypeParameterList != 0)
      setParentEdge(factory->getPointer(m_TypeParameterList),edkTypeDeclarationSyntax_TypeParameterList);

    NodeId _id;

    _id = binIo.readUInt4();
    while (_id) {
      ConstraintClausesContainer.push_back(_id);
      setParentEdge(factory->getPointer(_id),edkTypeDeclarationSyntax_ConstraintClauses);
      _id = binIo.readUInt4();
    }

    _id = binIo.readUInt4();
    while (_id) {
      MembersContainer.push_back(_id);
      setParentEdge(factory->getPointer(_id),edkTypeDeclarationSyntax_Members);
      _id = binIo.readUInt4();
    }
  }


}


}}}
