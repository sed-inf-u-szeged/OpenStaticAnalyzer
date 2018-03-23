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
  EnumMemberDeclarationSyntax::EnumMemberDeclarationSyntax(NodeId _id, Factory *_factory) :
    MemberDeclarationSyntax(_id, _factory),
    m_identifier(0),
    AttributeListsContainer(),
    m_EqualsValue(0)
  {
  }

  EnumMemberDeclarationSyntax::~EnumMemberDeclarationSyntax() {
  }

  void EnumMemberDeclarationSyntax::prepareDelete(bool tryOnVirtualParent){
    while (!AttributeListsContainer.empty()) {
      const NodeId id = *AttributeListsContainer.begin();
      removeParentEdge(id);
      if (factory->getExistsReverseEdges())
        factory->reverseEdges->removeEdge(id, this->getId(), edkEnumMemberDeclarationSyntax_AttributeLists);
      AttributeListsContainer.pop_front();
    }
    removeEqualsValue();
    structure::MemberDeclarationSyntax::prepareDelete(false);
  }

  NodeKind EnumMemberDeclarationSyntax::getNodeKind() const {
    return ndkEnumMemberDeclarationSyntax;
  }

  Key EnumMemberDeclarationSyntax::getIdentifierKey() const {
    return m_identifier;
  }

  const std::string& EnumMemberDeclarationSyntax::getIdentifier() const {
    return factory->getStringTable().get(m_identifier);
  }

  void EnumMemberDeclarationSyntax::setIdentifierKey(Key _identifier) {
    m_identifier = _identifier;
  }

  void EnumMemberDeclarationSyntax::setIdentifier(const std::string& _identifier) {
    m_identifier = factory->getStringTable().set(_identifier);
  }

  ListIterator<structure::AttributeListSyntax> EnumMemberDeclarationSyntax::getAttributeListsListIteratorBegin() const {
    return ListIterator<structure::AttributeListSyntax>(&AttributeListsContainer, factory, true);
  }

  ListIterator<structure::AttributeListSyntax> EnumMemberDeclarationSyntax::getAttributeListsListIteratorEnd() const {
    return ListIterator<structure::AttributeListSyntax>(&AttributeListsContainer, factory, false);
  }

  bool EnumMemberDeclarationSyntax::getAttributeListsIsEmpty() const {
    return getAttributeListsListIteratorBegin() == getAttributeListsListIteratorEnd();
  }

  unsigned int EnumMemberDeclarationSyntax::getAttributeListsSize() const {
    unsigned int size = 0;
    ListIterator<structure::AttributeListSyntax> endIt = getAttributeListsListIteratorEnd();
    for (ListIterator<structure::AttributeListSyntax> it = getAttributeListsListIteratorBegin(); it != endIt; ++it) {
      ++size;
    }
    return size;
  }

  structure::EqualsValueClauseSyntax* EnumMemberDeclarationSyntax::getEqualsValue() const {
    structure::EqualsValueClauseSyntax *_node = NULL;
    if (m_EqualsValue != 0)
      _node = dynamic_cast<structure::EqualsValueClauseSyntax*>(factory->getPointer(m_EqualsValue));
    if ( (_node == NULL) || factory->getIsFiltered(_node))
      return NULL;

    return _node;
  }

  bool EnumMemberDeclarationSyntax::setEdge(EdgeKind edgeKind, NodeId edgeEnd, bool tryOnVirtualParent) {
    switch (edgeKind) {
      case edkEnumMemberDeclarationSyntax_AttributeLists:
        addAttributeLists(edgeEnd);
        return true;
      case edkEnumMemberDeclarationSyntax_EqualsValue:
        setEqualsValue(edgeEnd);
        return true;
      default:
        break;
    }
    if (structure::MemberDeclarationSyntax::setEdge(edgeKind, edgeEnd, false)) {
      return true;
    }
    return false;
  }

  bool EnumMemberDeclarationSyntax::removeEdge(EdgeKind edgeKind, NodeId edgeEnd, bool tryOnVirtualParent) {
    switch (edgeKind) {
      case edkEnumMemberDeclarationSyntax_AttributeLists:
        removeAttributeLists(edgeEnd);
        return true;
      case edkEnumMemberDeclarationSyntax_EqualsValue:
        removeEqualsValue();
        return true;
      default:
        break;
    }
    if (structure::MemberDeclarationSyntax::removeEdge(edgeKind, edgeEnd, false)) {
      return true;
    }
    return false;
  }

  void EnumMemberDeclarationSyntax::addAttributeLists(const structure::AttributeListSyntax *_node) {
    if (_node == NULL)
      throw CsharpException(COLUMBUS_LOCATION, CMSG_EX_THE_NODE_IS_NULL);

    if (&(_node->getFactory()) != this->factory)
      throw CsharpException(COLUMBUS_LOCATION, CMSG_EX_THE_FACTORY_OF_NODES_DOES_NOT_MATCH);

    if (!((_node->getNodeKind() == ndkAttributeListSyntax) ))
      throw CsharpException(COLUMBUS_LOCATION, CMSG_EX_INVALID_NODE_KIND);

    AttributeListsContainer.push_back(_node->getId());
    setParentEdge(_node,edkEnumMemberDeclarationSyntax_AttributeLists);

    if (factory->reverseEdges)
      factory->reverseEdges->insertEdge(_node, this, edkEnumMemberDeclarationSyntax_AttributeLists);
  }

  void EnumMemberDeclarationSyntax::addAttributeLists(NodeId _id) {
    const structure::AttributeListSyntax *node = dynamic_cast<structure::AttributeListSyntax*>(factory->getPointer(_id));
    if (node == NULL)
      throw CsharpException(COLUMBUS_LOCATION, CMSG_EX_INVALID_NODE_KIND);
    addAttributeLists( node );
  }

  void EnumMemberDeclarationSyntax::removeAttributeLists(NodeId id) {
    if (!factory->getExist(id))
      throw CsharpException(COLUMBUS_LOCATION, CMSG_EX_THE_END_POINT_OF_THE_EDGE_DOES_NOT_EXIST);

    ListIterator<structure::AttributeListSyntax>::Container::iterator it = find(AttributeListsContainer.begin(), AttributeListsContainer.end(), id);

    if (it == AttributeListsContainer.end())
      throw CsharpException(COLUMBUS_LOCATION, CMSG_EX_THE_END_POINT_OF_THE_EDGE_DOES_NOT_EXIST);

    AttributeListsContainer.erase(it);

    removeParentEdge(id);

    if (factory->getExistsReverseEdges())
      factory->reverseEdges->removeEdge(id, this->getId(), edkEnumMemberDeclarationSyntax_AttributeLists);
  }

  void EnumMemberDeclarationSyntax::removeAttributeLists(structure::AttributeListSyntax *_node) {
    if (_node == NULL)
      throw CsharpException(COLUMBUS_LOCATION, CMSG_EX_THE_EDGE_IS_NULL);

    removeAttributeLists(_node->getId());
  }

  void EnumMemberDeclarationSyntax::setEqualsValue(NodeId _id) {
    structure::EqualsValueClauseSyntax *_node = NULL;
    if (_id) {
      if (!factory->getExist(_id))
        throw CsharpException(COLUMBUS_LOCATION, CMSG_EX_THE_END_POINT_OF_THE_EDGE_DOES_NOT_EXIST);

      _node = dynamic_cast<structure::EqualsValueClauseSyntax*> (factory->getPointer(_id));
      if ( _node == NULL) {
        throw CsharpException(COLUMBUS_LOCATION, CMSG_EX_INVALID_NODE_KIND);
      }
      if (&(_node->getFactory()) != this->factory)
        throw CsharpException(COLUMBUS_LOCATION, CMSG_EX_THE_FACTORY_OF_NODES_DOES_NOT_MATCH );

      if (m_EqualsValue) {
        removeParentEdge(m_EqualsValue);
        if (factory->getExistsReverseEdges())
          factory->reverseEdges->removeEdge(m_EqualsValue, m_id, edkEnumMemberDeclarationSyntax_EqualsValue);
      }
      m_EqualsValue = _node->getId();
      if (m_EqualsValue != 0)
        setParentEdge(factory->getPointer(m_EqualsValue), edkEnumMemberDeclarationSyntax_EqualsValue);
      if (factory->getExistsReverseEdges())
        factory->reverseEdges->insertEdge(m_EqualsValue, this->getId(), edkEnumMemberDeclarationSyntax_EqualsValue);
    } else {
      if (m_EqualsValue) {
        throw CsharpException(COLUMBUS_LOCATION, CMSG_EX_CAN_T_SET_EDGE_TO_NULL);
      }
    }
  }

  void EnumMemberDeclarationSyntax::setEqualsValue(structure::EqualsValueClauseSyntax *_node) {
    if (_node == NULL)
      throw CsharpException(COLUMBUS_LOCATION, CMSG_EX_CAN_T_SET_EDGE_TO_NULL);

    setEqualsValue(_node->getId());
  }

  void EnumMemberDeclarationSyntax::removeEqualsValue() {
      if (m_EqualsValue) {
        removeParentEdge(m_EqualsValue);
        if (factory->getExistsReverseEdges())
          factory->reverseEdges->removeEdge(m_EqualsValue, m_id, edkEnumMemberDeclarationSyntax_EqualsValue);
      }
      m_EqualsValue = 0;
  }

  void EnumMemberDeclarationSyntax::accept(Visitor &visitor) const {
    visitor.visit(*this);
  }

  void EnumMemberDeclarationSyntax::acceptEnd(Visitor &visitor) const {
    visitor.visitEnd(*this);
  }

  double EnumMemberDeclarationSyntax::getSimilarity(const base::Base& base){
    if(base.getNodeKind() == getNodeKind()) {
      const EnumMemberDeclarationSyntax& node = dynamic_cast<const EnumMemberDeclarationSyntax&>(base);
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

  void EnumMemberDeclarationSyntax::swapStringTable(RefDistributorStrTable& newStrTable, std::map<Key,Key>& oldAndNewStrKeyMap ){
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

  NodeHashType EnumMemberDeclarationSyntax::getHash(std::set<NodeId>& travNodes) const {
    if (hashOk) return nodeHashCache;
    common::WriteMsg::write(CMSG_GET_THE_NODE_HASH_OF_NODE_BEGIN,this->getId()); 
    if (travNodes.count(getId())>0) {
      common::WriteMsg::write(CMSG_GET_THE_NODE_HASH_OF_NODE_SKIP);
      return 0;
    }
    travNodes.insert(getId());
    Crc_type resultHash;
    resultHash.process_bytes( "structure::EnumMemberDeclarationSyntax", strlen("structure::EnumMemberDeclarationSyntax"));
    common::WriteMsg::write(CMSG_GET_THE_NODE_HASH_OF_NODE_END,resultHash.checksum()); 
    nodeHashCache = resultHash.checksum();
    hashOk = true;
    return nodeHashCache;
  }

  void EnumMemberDeclarationSyntax::save(io::BinaryIO &binIo,bool withVirtualBase  /*= true*/) const {
    MemberDeclarationSyntax::save(binIo,false);

    factory->getStringTable().setType(m_identifier, StrTable::strToSave);
    binIo.writeUInt4(m_identifier);

    binIo.writeUInt4(m_EqualsValue);


    for (ListIterator<structure::AttributeListSyntax>::Container::const_iterator it = AttributeListsContainer.begin(); it != AttributeListsContainer.end(); ++it) {
      binIo.writeUInt4(*it);
    }
    binIo.writeUInt4(0); // This is the end sign
  }

  void EnumMemberDeclarationSyntax::load(io::BinaryIO &binIo, bool withVirtualBase /*= true*/) {
    MemberDeclarationSyntax::load(binIo,false);

    m_identifier = binIo.readUInt4();

    m_EqualsValue =  binIo.readUInt4();
    if (m_EqualsValue != 0)
      setParentEdge(factory->getPointer(m_EqualsValue),edkEnumMemberDeclarationSyntax_EqualsValue);

    NodeId _id;

    _id = binIo.readUInt4();
    while (_id) {
      AttributeListsContainer.push_back(_id);
      setParentEdge(factory->getPointer(_id),edkEnumMemberDeclarationSyntax_AttributeLists);
      _id = binIo.readUInt4();
    }
  }


}


}}}
