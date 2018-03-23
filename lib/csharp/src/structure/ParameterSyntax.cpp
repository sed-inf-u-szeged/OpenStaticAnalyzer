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
  ParameterSyntax::ParameterSyntax(NodeId _id, Factory *_factory) :
    Positioned(_id, _factory),
    m_identifier(0),
    AttributeListsContainer(),
    m_Default(0),
    m_Type(0)
  {
  }

  ParameterSyntax::~ParameterSyntax() {
  }

  void ParameterSyntax::prepareDelete(bool tryOnVirtualParent){
    while (!AttributeListsContainer.empty()) {
      const NodeId id = *AttributeListsContainer.begin();
      removeParentEdge(id);
      if (factory->getExistsReverseEdges())
        factory->reverseEdges->removeEdge(id, this->getId(), edkParameterSyntax_AttributeLists);
      AttributeListsContainer.pop_front();
    }
    removeDefault();
    removeType();
    base::Positioned::prepareDelete(false);
  }

  NodeKind ParameterSyntax::getNodeKind() const {
    return ndkParameterSyntax;
  }

  Key ParameterSyntax::getIdentifierKey() const {
    return m_identifier;
  }

  const std::string& ParameterSyntax::getIdentifier() const {
    return factory->getStringTable().get(m_identifier);
  }

  void ParameterSyntax::setIdentifierKey(Key _identifier) {
    m_identifier = _identifier;
  }

  void ParameterSyntax::setIdentifier(const std::string& _identifier) {
    m_identifier = factory->getStringTable().set(_identifier);
  }

  ListIterator<structure::AttributeListSyntax> ParameterSyntax::getAttributeListsListIteratorBegin() const {
    return ListIterator<structure::AttributeListSyntax>(&AttributeListsContainer, factory, true);
  }

  ListIterator<structure::AttributeListSyntax> ParameterSyntax::getAttributeListsListIteratorEnd() const {
    return ListIterator<structure::AttributeListSyntax>(&AttributeListsContainer, factory, false);
  }

  bool ParameterSyntax::getAttributeListsIsEmpty() const {
    return getAttributeListsListIteratorBegin() == getAttributeListsListIteratorEnd();
  }

  unsigned int ParameterSyntax::getAttributeListsSize() const {
    unsigned int size = 0;
    ListIterator<structure::AttributeListSyntax> endIt = getAttributeListsListIteratorEnd();
    for (ListIterator<structure::AttributeListSyntax> it = getAttributeListsListIteratorBegin(); it != endIt; ++it) {
      ++size;
    }
    return size;
  }

  structure::EqualsValueClauseSyntax* ParameterSyntax::getDefault() const {
    structure::EqualsValueClauseSyntax *_node = NULL;
    if (m_Default != 0)
      _node = dynamic_cast<structure::EqualsValueClauseSyntax*>(factory->getPointer(m_Default));
    if ( (_node == NULL) || factory->getIsFiltered(_node))
      return NULL;

    return _node;
  }

  expression::TypeSyntax* ParameterSyntax::getType() const {
    expression::TypeSyntax *_node = NULL;
    if (m_Type != 0)
      _node = dynamic_cast<expression::TypeSyntax*>(factory->getPointer(m_Type));
    if ( (_node == NULL) || factory->getIsFiltered(_node))
      return NULL;

    return _node;
  }

  bool ParameterSyntax::setEdge(EdgeKind edgeKind, NodeId edgeEnd, bool tryOnVirtualParent) {
    switch (edgeKind) {
      case edkParameterSyntax_AttributeLists:
        addAttributeLists(edgeEnd);
        return true;
      case edkParameterSyntax_Default:
        setDefault(edgeEnd);
        return true;
      case edkParameterSyntax_Type:
        setType(edgeEnd);
        return true;
      default:
        break;
    }
    if (base::Positioned::setEdge(edgeKind, edgeEnd, false)) {
      return true;
    }
    return false;
  }

  bool ParameterSyntax::removeEdge(EdgeKind edgeKind, NodeId edgeEnd, bool tryOnVirtualParent) {
    switch (edgeKind) {
      case edkParameterSyntax_AttributeLists:
        removeAttributeLists(edgeEnd);
        return true;
      case edkParameterSyntax_Default:
        removeDefault();
        return true;
      case edkParameterSyntax_Type:
        removeType();
        return true;
      default:
        break;
    }
    if (base::Positioned::removeEdge(edgeKind, edgeEnd, false)) {
      return true;
    }
    return false;
  }

  void ParameterSyntax::addAttributeLists(const structure::AttributeListSyntax *_node) {
    if (_node == NULL)
      throw CsharpException(COLUMBUS_LOCATION, CMSG_EX_THE_NODE_IS_NULL);

    if (&(_node->getFactory()) != this->factory)
      throw CsharpException(COLUMBUS_LOCATION, CMSG_EX_THE_FACTORY_OF_NODES_DOES_NOT_MATCH);

    if (!((_node->getNodeKind() == ndkAttributeListSyntax) ))
      throw CsharpException(COLUMBUS_LOCATION, CMSG_EX_INVALID_NODE_KIND);

    AttributeListsContainer.push_back(_node->getId());
    setParentEdge(_node,edkParameterSyntax_AttributeLists);

    if (factory->reverseEdges)
      factory->reverseEdges->insertEdge(_node, this, edkParameterSyntax_AttributeLists);
  }

  void ParameterSyntax::addAttributeLists(NodeId _id) {
    const structure::AttributeListSyntax *node = dynamic_cast<structure::AttributeListSyntax*>(factory->getPointer(_id));
    if (node == NULL)
      throw CsharpException(COLUMBUS_LOCATION, CMSG_EX_INVALID_NODE_KIND);
    addAttributeLists( node );
  }

  void ParameterSyntax::removeAttributeLists(NodeId id) {
    if (!factory->getExist(id))
      throw CsharpException(COLUMBUS_LOCATION, CMSG_EX_THE_END_POINT_OF_THE_EDGE_DOES_NOT_EXIST);

    ListIterator<structure::AttributeListSyntax>::Container::iterator it = find(AttributeListsContainer.begin(), AttributeListsContainer.end(), id);

    if (it == AttributeListsContainer.end())
      throw CsharpException(COLUMBUS_LOCATION, CMSG_EX_THE_END_POINT_OF_THE_EDGE_DOES_NOT_EXIST);

    AttributeListsContainer.erase(it);

    removeParentEdge(id);

    if (factory->getExistsReverseEdges())
      factory->reverseEdges->removeEdge(id, this->getId(), edkParameterSyntax_AttributeLists);
  }

  void ParameterSyntax::removeAttributeLists(structure::AttributeListSyntax *_node) {
    if (_node == NULL)
      throw CsharpException(COLUMBUS_LOCATION, CMSG_EX_THE_EDGE_IS_NULL);

    removeAttributeLists(_node->getId());
  }

  void ParameterSyntax::setDefault(NodeId _id) {
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

      if (m_Default) {
        removeParentEdge(m_Default);
        if (factory->getExistsReverseEdges())
          factory->reverseEdges->removeEdge(m_Default, m_id, edkParameterSyntax_Default);
      }
      m_Default = _node->getId();
      if (m_Default != 0)
        setParentEdge(factory->getPointer(m_Default), edkParameterSyntax_Default);
      if (factory->getExistsReverseEdges())
        factory->reverseEdges->insertEdge(m_Default, this->getId(), edkParameterSyntax_Default);
    } else {
      if (m_Default) {
        throw CsharpException(COLUMBUS_LOCATION, CMSG_EX_CAN_T_SET_EDGE_TO_NULL);
      }
    }
  }

  void ParameterSyntax::setDefault(structure::EqualsValueClauseSyntax *_node) {
    if (_node == NULL)
      throw CsharpException(COLUMBUS_LOCATION, CMSG_EX_CAN_T_SET_EDGE_TO_NULL);

    setDefault(_node->getId());
  }

  void ParameterSyntax::removeDefault() {
      if (m_Default) {
        removeParentEdge(m_Default);
        if (factory->getExistsReverseEdges())
          factory->reverseEdges->removeEdge(m_Default, m_id, edkParameterSyntax_Default);
      }
      m_Default = 0;
  }

  void ParameterSyntax::setType(NodeId _id) {
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
          factory->reverseEdges->removeEdge(m_Type, m_id, edkParameterSyntax_Type);
      }
      m_Type = _node->getId();
      if (m_Type != 0)
        setParentEdge(factory->getPointer(m_Type), edkParameterSyntax_Type);
      if (factory->getExistsReverseEdges())
        factory->reverseEdges->insertEdge(m_Type, this->getId(), edkParameterSyntax_Type);
    } else {
      if (m_Type) {
        throw CsharpException(COLUMBUS_LOCATION, CMSG_EX_CAN_T_SET_EDGE_TO_NULL);
      }
    }
  }

  void ParameterSyntax::setType(expression::TypeSyntax *_node) {
    if (_node == NULL)
      throw CsharpException(COLUMBUS_LOCATION, CMSG_EX_CAN_T_SET_EDGE_TO_NULL);

    setType(_node->getId());
  }

  void ParameterSyntax::removeType() {
      if (m_Type) {
        removeParentEdge(m_Type);
        if (factory->getExistsReverseEdges())
          factory->reverseEdges->removeEdge(m_Type, m_id, edkParameterSyntax_Type);
      }
      m_Type = 0;
  }

  void ParameterSyntax::accept(Visitor &visitor) const {
    visitor.visit(*this);
  }

  void ParameterSyntax::acceptEnd(Visitor &visitor) const {
    visitor.visitEnd(*this);
  }

  double ParameterSyntax::getSimilarity(const base::Base& base){
    if(base.getNodeKind() == getNodeKind()) {
      const ParameterSyntax& node = dynamic_cast<const ParameterSyntax&>(base);
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

  void ParameterSyntax::swapStringTable(RefDistributorStrTable& newStrTable, std::map<Key,Key>& oldAndNewStrKeyMap ){
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

  NodeHashType ParameterSyntax::getHash(std::set<NodeId>& travNodes) const {
    if (hashOk) return nodeHashCache;
    common::WriteMsg::write(CMSG_GET_THE_NODE_HASH_OF_NODE_BEGIN,this->getId()); 
    if (travNodes.count(getId())>0) {
      common::WriteMsg::write(CMSG_GET_THE_NODE_HASH_OF_NODE_SKIP);
      return 0;
    }
    travNodes.insert(getId());
    Crc_type resultHash;
    resultHash.process_bytes( "structure::ParameterSyntax", strlen("structure::ParameterSyntax"));
    common::WriteMsg::write(CMSG_GET_THE_NODE_HASH_OF_NODE_END,resultHash.checksum()); 
    nodeHashCache = resultHash.checksum();
    hashOk = true;
    return nodeHashCache;
  }

  void ParameterSyntax::save(io::BinaryIO &binIo,bool withVirtualBase  /*= true*/) const {
    Positioned::save(binIo,false);

    factory->getStringTable().setType(m_identifier, StrTable::strToSave);
    binIo.writeUInt4(m_identifier);

    binIo.writeUInt4(m_Default);
    binIo.writeUInt4(m_Type);


    for (ListIterator<structure::AttributeListSyntax>::Container::const_iterator it = AttributeListsContainer.begin(); it != AttributeListsContainer.end(); ++it) {
      binIo.writeUInt4(*it);
    }
    binIo.writeUInt4(0); // This is the end sign
  }

  void ParameterSyntax::load(io::BinaryIO &binIo, bool withVirtualBase /*= true*/) {
    Positioned::load(binIo,false);

    m_identifier = binIo.readUInt4();

    m_Default =  binIo.readUInt4();
    if (m_Default != 0)
      setParentEdge(factory->getPointer(m_Default),edkParameterSyntax_Default);

    m_Type =  binIo.readUInt4();
    if (m_Type != 0)
      setParentEdge(factory->getPointer(m_Type),edkParameterSyntax_Type);

    NodeId _id;

    _id = binIo.readUInt4();
    while (_id) {
      AttributeListsContainer.push_back(_id);
      setParentEdge(factory->getPointer(_id),edkParameterSyntax_AttributeLists);
      _id = binIo.readUInt4();
    }
  }


}


}}}
