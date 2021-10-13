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

#include "lim/inc/lim.h"
#include "lim/inc/Common.h"
#include "common/inc/WriteMessage.h"

#include "lim/inc/messages.h"
#include <algorithm>
#include <string.h>
#include "common/inc/math/common.h"


namespace columbus { namespace lim { namespace asg {

typedef boost::crc_32_type  Crc_type;

namespace logical { 
  Class::Class(NodeId _id, Factory *_factory) :
    Scope(_id, _factory),
    m_isAbstract(false),
    m_classKind(clkAnnotation),
    m_objectSize(0),
    extendsContainer(),
    grantsFriendshipContainer(),
    isSubclassContainer()
  {
  }

  Class::~Class() {
  }

  void Class::clone(const Class& other, bool tryOnVirtualParent) {
    logical::Scope::clone(other, false);

    m_classKind = other.m_classKind;
    m_isAbstract = other.m_isAbstract;
    m_objectSize = other.m_objectSize;
    extendsContainer = other.extendsContainer;
    grantsFriendshipContainer = other.grantsFriendshipContainer;
    isSubclassContainer = other.isSubclassContainer;
  }

  void Class::prepareDelete(bool tryOnVirtualParent){
    while (!extendsContainer.empty()) {
      const NodeId id = *extendsContainer.begin();
      if (factory->getExistsReverseEdges())
        factory->reverseEdges->removeEdge(id, this->getId(), edkClass_Extends);
      extendsContainer.pop_front();
    }
    while (!grantsFriendshipContainer.empty()) {
      const NodeId id = *grantsFriendshipContainer.begin();
      if (factory->getExistsReverseEdges())
        factory->reverseEdges->removeEdge(id, this->getId(), edkClass_GrantsFriendship);
      grantsFriendshipContainer.pop_front();
    }
    while (!isSubclassContainer.empty()) {
      const NodeId id = *isSubclassContainer.begin();
      if (factory->getExistsReverseEdges())
        factory->reverseEdges->removeEdge(id, this->getId(), edkClass_IsSubclass);
      isSubclassContainer.pop_front();
    }
    logical::Scope::prepareDelete(false);
  }

  NodeKind Class::getNodeKind() const {
    return ndkClass;
  }

  ClassKind Class::getClassKind() const {
    return m_classKind;
  }

  bool Class::getIsAbstract() const {
    return m_isAbstract;
  }

  unsigned Class::getObjectSize() const {
    return m_objectSize;
  }

  void Class::setClassKind(ClassKind _classKind) {
    m_classKind = _classKind;
  }

  void Class::setIsAbstract(bool _isAbstract) {
    m_isAbstract = _isAbstract;
  }

  void Class::setObjectSize(unsigned _objectSize) {
    m_objectSize = _objectSize;
  }

  ListIterator<logical::Class> Class::getExtendsListIteratorBegin() const {
    return ListIterator<logical::Class>(&extendsContainer, factory, true);
  }

  ListIterator<logical::Class> Class::getExtendsListIteratorEnd() const {
    return ListIterator<logical::Class>(&extendsContainer, factory, false);
  }

  bool Class::getExtendsIsEmpty() const {
    return getExtendsListIteratorBegin() == getExtendsListIteratorEnd();
  }

  unsigned int Class::getExtendsSize() const {
    unsigned int size = 0;
    ListIterator<logical::Class> endIt = getExtendsListIteratorEnd();
    for (ListIterator<logical::Class> it = getExtendsListIteratorBegin(); it != endIt; ++it) {
      ++size;
    }
    return size;
  }

  ListIterator<logical::Friendship> Class::getGrantsFriendshipListIteratorBegin() const {
    return ListIterator<logical::Friendship>(&grantsFriendshipContainer, factory, true);
  }

  ListIterator<logical::Friendship> Class::getGrantsFriendshipListIteratorEnd() const {
    return ListIterator<logical::Friendship>(&grantsFriendshipContainer, factory, false);
  }

  bool Class::getGrantsFriendshipIsEmpty() const {
    return getGrantsFriendshipListIteratorBegin() == getGrantsFriendshipListIteratorEnd();
  }

  unsigned int Class::getGrantsFriendshipSize() const {
    unsigned int size = 0;
    ListIterator<logical::Friendship> endIt = getGrantsFriendshipListIteratorEnd();
    for (ListIterator<logical::Friendship> it = getGrantsFriendshipListIteratorBegin(); it != endIt; ++it) {
      ++size;
    }
    return size;
  }

  ListIterator<type::Type> Class::getIsSubclassListIteratorBegin() const {
    return ListIterator<type::Type>(&isSubclassContainer, factory, true);
  }

  ListIterator<type::Type> Class::getIsSubclassListIteratorEnd() const {
    return ListIterator<type::Type>(&isSubclassContainer, factory, false);
  }

  bool Class::getIsSubclassIsEmpty() const {
    return getIsSubclassListIteratorBegin() == getIsSubclassListIteratorEnd();
  }

  unsigned int Class::getIsSubclassSize() const {
    unsigned int size = 0;
    ListIterator<type::Type> endIt = getIsSubclassListIteratorEnd();
    for (ListIterator<type::Type> it = getIsSubclassListIteratorBegin(); it != endIt; ++it) {
      ++size;
    }
    return size;
  }

  bool Class::setEdge(EdgeKind edgeKind, NodeId edgeEnd, void* acValue, bool tryOnVirtualParent) {
    switch (edgeKind) {
      case edkClass_Extends:
        addExtends(edgeEnd);
        return true;
      case edkClass_GrantsFriendship:
        addGrantsFriendship(edgeEnd);
        return true;
      case edkClass_IsSubclass:
        addIsSubclass(edgeEnd);
        return true;
      default:
        break;
    }
    if (logical::Scope::setEdge(edgeKind, edgeEnd, acValue, false)) {
      return true;
    }
    return false;
  }

  bool Class::removeEdge(EdgeKind edgeKind, NodeId edgeEnd, bool tryOnVirtualParent) {
    switch (edgeKind) {
      case edkClass_Extends:
        removeExtends(edgeEnd);
        return true;
      case edkClass_GrantsFriendship:
        removeGrantsFriendship(edgeEnd);
        return true;
      case edkClass_IsSubclass:
        removeIsSubclass(edgeEnd);
        return true;
      default:
        break;
    }
    if (logical::Scope::removeEdge(edgeKind, edgeEnd, false)) {
      return true;
    }
    return false;
  }

  void Class::addExtends(const logical::Class *_node) {
    if (_node == NULL)
      throw LimException(COLUMBUS_LOCATION, CMSG_EX_THE_NODE_IS_NULL);

    if (&(_node->getFactory()) != this->factory)
      throw LimException(COLUMBUS_LOCATION, CMSG_EX_THE_FACTORY_OF_NODES_DOES_NOT_MATCH);

    if (!(Common::getIsClass(*_node)))
      throw LimException(COLUMBUS_LOCATION, CMSG_EX_INVALID_NODE_KIND);

    extendsContainer.push_back(_node->getId());
    if (factory->reverseEdges)
      factory->reverseEdges->insertEdge(_node, this, edkClass_Extends);
  }

  void Class::addExtends(NodeId _id) {
    const logical::Class *node = dynamic_cast<logical::Class*>(factory->getPointer(_id));
    if (node == NULL)
      throw LimException(COLUMBUS_LOCATION, CMSG_EX_INVALID_NODE_KIND);
    addExtends( node );
  }

  void Class::removeExtends(NodeId id) {
    if (!factory->getExist(id))
      throw LimException(COLUMBUS_LOCATION, CMSG_EX_THE_END_POINT_OF_THE_EDGE_DOES_NOT_EXIST);

    ListIterator<logical::Class>::Container::iterator it = find(extendsContainer.begin(), extendsContainer.end(), id);

    if (it == extendsContainer.end())
      throw LimException(COLUMBUS_LOCATION, CMSG_EX_THE_END_POINT_OF_THE_EDGE_DOES_NOT_EXIST);

    extendsContainer.erase(it);

    if (factory->getExistsReverseEdges())
      factory->reverseEdges->removeEdge(id, this->getId(), edkClass_Extends);
  }

  void Class::removeExtends(logical::Class *_node) {
    if (_node == NULL)
      throw LimException(COLUMBUS_LOCATION, CMSG_EX_THE_EDGE_IS_NULL);

    removeExtends(_node->getId());
  }

  void Class::addGrantsFriendship(const logical::Friendship *_node) {
    if (_node == NULL)
      throw LimException(COLUMBUS_LOCATION, CMSG_EX_THE_NODE_IS_NULL);

    if (&(_node->getFactory()) != this->factory)
      throw LimException(COLUMBUS_LOCATION, CMSG_EX_THE_FACTORY_OF_NODES_DOES_NOT_MATCH);

    if (!((_node->getNodeKind() == ndkFriendship) ))
      throw LimException(COLUMBUS_LOCATION, CMSG_EX_INVALID_NODE_KIND);

    grantsFriendshipContainer.push_back(_node->getId());
    if (factory->reverseEdges)
      factory->reverseEdges->insertEdge(_node, this, edkClass_GrantsFriendship);
  }

  void Class::addGrantsFriendship(NodeId _id) {
    const logical::Friendship *node = dynamic_cast<logical::Friendship*>(factory->getPointer(_id));
    if (node == NULL)
      throw LimException(COLUMBUS_LOCATION, CMSG_EX_INVALID_NODE_KIND);
    addGrantsFriendship( node );
  }

  void Class::removeGrantsFriendship(NodeId id) {
    if (!factory->getExist(id))
      throw LimException(COLUMBUS_LOCATION, CMSG_EX_THE_END_POINT_OF_THE_EDGE_DOES_NOT_EXIST);

    ListIterator<logical::Friendship>::Container::iterator it = find(grantsFriendshipContainer.begin(), grantsFriendshipContainer.end(), id);

    if (it == grantsFriendshipContainer.end())
      throw LimException(COLUMBUS_LOCATION, CMSG_EX_THE_END_POINT_OF_THE_EDGE_DOES_NOT_EXIST);

    grantsFriendshipContainer.erase(it);

    if (factory->getExistsReverseEdges())
      factory->reverseEdges->removeEdge(id, this->getId(), edkClass_GrantsFriendship);
  }

  void Class::removeGrantsFriendship(logical::Friendship *_node) {
    if (_node == NULL)
      throw LimException(COLUMBUS_LOCATION, CMSG_EX_THE_EDGE_IS_NULL);

    removeGrantsFriendship(_node->getId());
  }

  void Class::addIsSubclass(const type::Type *_node) {
    if (_node == NULL)
      throw LimException(COLUMBUS_LOCATION, CMSG_EX_THE_NODE_IS_NULL);

    if (&(_node->getFactory()) != this->factory)
      throw LimException(COLUMBUS_LOCATION, CMSG_EX_THE_FACTORY_OF_NODES_DOES_NOT_MATCH);

    if (!((_node->getNodeKind() == ndkType) ))
      throw LimException(COLUMBUS_LOCATION, CMSG_EX_INVALID_NODE_KIND);

    isSubclassContainer.push_back(_node->getId());
    if (factory->reverseEdges)
      factory->reverseEdges->insertEdge(_node, this, edkClass_IsSubclass);
  }

  void Class::addIsSubclass(NodeId _id) {
    const type::Type *node = dynamic_cast<type::Type*>(factory->getPointer(_id));
    if (node == NULL)
      throw LimException(COLUMBUS_LOCATION, CMSG_EX_INVALID_NODE_KIND);
    addIsSubclass( node );
  }

  void Class::removeIsSubclass(NodeId id) {
    if (!factory->getExist(id))
      throw LimException(COLUMBUS_LOCATION, CMSG_EX_THE_END_POINT_OF_THE_EDGE_DOES_NOT_EXIST);

    ListIterator<type::Type>::Container::iterator it = find(isSubclassContainer.begin(), isSubclassContainer.end(), id);

    if (it == isSubclassContainer.end())
      throw LimException(COLUMBUS_LOCATION, CMSG_EX_THE_END_POINT_OF_THE_EDGE_DOES_NOT_EXIST);

    isSubclassContainer.erase(it);

    if (factory->getExistsReverseEdges())
      factory->reverseEdges->removeEdge(id, this->getId(), edkClass_IsSubclass);
  }

  void Class::removeIsSubclass(type::Type *_node) {
    if (_node == NULL)
      throw LimException(COLUMBUS_LOCATION, CMSG_EX_THE_EDGE_IS_NULL);

    removeIsSubclass(_node->getId());
  }

  void Class::accept(Visitor &visitor) const {
    visitor.visit(*this);
  }

  void Class::acceptEnd(Visitor &visitor) const {
    visitor.visitEnd(*this);
  }

  double Class::getSimilarity(const base::Base& base){
    if(base.getNodeKind() == getNodeKind()) {
      const Class& node = dynamic_cast<const Class&>(base);
      double matchAttrs = 0;
      std::string str1, str2;
      size_t strMax;
      double strSim;
      str1 = getName();
      str2 = node.getName();
      strMax = std::max(str1.size(), str2.size());
      strSim = 1 - ((double)common::math::editDistance(str1, str2) / (strMax > 0 ? strMax : 1));
      if (strSim < Common::SimilarityMinForStrings)
        return 0.0;
      matchAttrs += strSim;
      if(node.getAccessibility() == getAccessibility()) ++matchAttrs;
      if(node.getCommentLines() == getCommentLines()) ++matchAttrs;
      str1 = getDemangledName();
      str2 = node.getDemangledName();
      strMax = std::max(str1.size(), str2.size());
      strSim = 1 - ((double)common::math::editDistance(str1, str2) / (strMax > 0 ? strMax : 1));
      if (strSim < Common::SimilarityMinForStrings)
        return 0.0;
      matchAttrs += strSim;
      if(node.getIsCompilerGenerated() == getIsCompilerGenerated()) ++matchAttrs;
      if(node.getIsStatic() == getIsStatic()) ++matchAttrs;
      if(node.getLanguage() == getLanguage()) ++matchAttrs;
      str1 = getMangledName();
      str2 = node.getMangledName();
      strMax = std::max(str1.size(), str2.size());
      strSim = 1 - ((double)common::math::editDistance(str1, str2) / (strMax > 0 ? strMax : 1));
      if (strSim < Common::SimilarityMinForStrings)
        return 0.0;
      matchAttrs += strSim;
      if(node.getLLOC() == getLLOC()) ++matchAttrs;
      if(node.getLOC() == getLOC()) ++matchAttrs;
      if(node.getTLLOC() == getTLLOC()) ++matchAttrs;
      if(node.getTLOC() == getTLOC()) ++matchAttrs;
      if(node.getIsAnonymous() == getIsAnonymous()) ++matchAttrs;
      if(node.getClassKind() == getClassKind()) ++matchAttrs;
      if(node.getIsAbstract() == getIsAbstract()) ++matchAttrs;
      if(node.getObjectSize() == getObjectSize()) ++matchAttrs;
      return matchAttrs / (16 / (1 - Common::SimilarityMinimum)) + Common::SimilarityMinimum;
    } else {
      return 0.0;
    }
  }

  void Class::swapStringTable(RefDistributorStrTable& newStrTable, std::map<Key,Key>& oldAndNewStrKeyMap ){
    std::map<Key,Key>::iterator foundKeyId;

    foundKeyId = oldAndNewStrKeyMap.find(m_demangledName);
    if (foundKeyId != oldAndNewStrKeyMap.end()) {
      m_demangledName = foundKeyId->second;
    } else {
      Key oldkey = m_demangledName;
      m_demangledName = newStrTable.set(factory->getStringTable().get(m_demangledName));
      oldAndNewStrKeyMap.insert(std::pair<Key,Key>(oldkey,m_demangledName));    }

    foundKeyId = oldAndNewStrKeyMap.find(m_mangledName);
    if (foundKeyId != oldAndNewStrKeyMap.end()) {
      m_mangledName = foundKeyId->second;
    } else {
      Key oldkey = m_mangledName;
      m_mangledName = newStrTable.set(factory->getStringTable().get(m_mangledName));
      oldAndNewStrKeyMap.insert(std::pair<Key,Key>(oldkey,m_mangledName));    }

    foundKeyId = oldAndNewStrKeyMap.find(m_name);
    if (foundKeyId != oldAndNewStrKeyMap.end()) {
      m_name = foundKeyId->second;
    } else {
      Key oldkey = m_name;
      m_name = newStrTable.set(factory->getStringTable().get(m_name));
      oldAndNewStrKeyMap.insert(std::pair<Key,Key>(oldkey,m_name));    }

  }

  NodeHashType Class::getHash(std::set<NodeId>& travNodes) const {
    if (hashOk) return nodeHashCache;
    common::WriteMsg::write(CMSG_GET_THE_NODE_HASH_OF_NODE_BEGIN,this->getId()); 
    if (travNodes.count(getId())>0) {
      common::WriteMsg::write(CMSG_GET_THE_NODE_HASH_OF_NODE_SKIP);
      return 0;
    }
    travNodes.insert(getId());
    Crc_type resultHash;
    resultHash.process_bytes( "logical::Class", strlen("logical::Class"));
    common::WriteMsg::write(CMSG_GET_THE_NODE_HASH_OF_NODE_END,resultHash.checksum()); 
    nodeHashCache = resultHash.checksum();
    hashOk = true;
    return nodeHashCache;
  }

  void Class::save(io::BinaryIO &binIo,bool withVirtualBase  /*= true*/) const {
    Scope::save(binIo,false);

    unsigned char boolValues = 0;
    boolValues <<= 1;
    if (m_isAbstract) 
      boolValues |= 1;
    binIo.writeUByte1(boolValues);
    binIo.writeUByte1(m_classKind);
    binIo.writeUInt4(m_objectSize);


    for (ListIterator<logical::Class>::Container::const_iterator it = extendsContainer.begin(); it != extendsContainer.end(); ++it) {
      binIo.writeUInt4(*it);
    }
    binIo.writeUInt4(0); // This is the end sign

    for (ListIterator<logical::Friendship>::Container::const_iterator it = grantsFriendshipContainer.begin(); it != grantsFriendshipContainer.end(); ++it) {
      binIo.writeUInt4(*it);
    }
    binIo.writeUInt4(0); // This is the end sign

    for (ListIterator<type::Type>::Container::const_iterator it = isSubclassContainer.begin(); it != isSubclassContainer.end(); ++it) {
      binIo.writeUInt4(*it);
    }
    binIo.writeUInt4(0); // This is the end sign
  }

  void Class::load(io::BinaryIO &binIo, bool withVirtualBase /*= true*/) {
    Scope::load(binIo,false);

    unsigned char boolValues = binIo.readUByte1();
    m_isAbstract = boolValues & 1;
    boolValues >>= 1;
    m_classKind = (ClassKind)binIo.readUByte1();
    m_objectSize = binIo.readUInt4();

    NodeId _id;

    _id = binIo.readUInt4();
    while (_id) {
      extendsContainer.push_back(_id);
      _id = binIo.readUInt4();
    }

    _id = binIo.readUInt4();
    while (_id) {
      grantsFriendshipContainer.push_back(_id);
      _id = binIo.readUInt4();
    }

    _id = binIo.readUInt4();
    while (_id) {
      isSubclassContainer.push_back(_id);
      _id = binIo.readUInt4();
    }
  }


}


}}}
