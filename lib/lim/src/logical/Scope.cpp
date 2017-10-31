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
  Scope::Scope(NodeId _id, Factory *_factory) :
    Member(_id, _factory),
    m_isAnonymous(false),
    m_LLOC(0),
    m_LOC(0),
    m_TLLOC(0),
    m_TLOC(0),
    hasMemberContainer()
  {
  }

  Scope::~Scope() {
  }

  void Scope::clone(const Scope& other, bool tryOnVirtualParent) {
    logical::Member::clone(other, false);

    m_LLOC = other.m_LLOC;
    m_LOC = other.m_LOC;
    m_TLLOC = other.m_TLLOC;
    m_TLOC = other.m_TLOC;
    m_isAnonymous = other.m_isAnonymous;
    hasMemberContainer = other.hasMemberContainer;
  }

  void Scope::prepareDelete(bool tryOnVirtualParent){
    while (!hasMemberContainer.empty()) {
      const NodeId id = *hasMemberContainer.begin();
      if (factory->getExistsReverseEdges())
        factory->reverseEdges->removeEdge(id, this->getId(), edkScope_HasMember);
      hasMemberContainer.pop_front();
    }
    logical::Member::prepareDelete(false);
  }

  unsigned Scope::getLLOC() const {
    return m_LLOC;
  }

  unsigned Scope::getLOC() const {
    return m_LOC;
  }

  unsigned Scope::getTLLOC() const {
    return m_TLLOC;
  }

  unsigned Scope::getTLOC() const {
    return m_TLOC;
  }

  bool Scope::getIsAnonymous() const {
    return m_isAnonymous;
  }

  void Scope::setLLOC(unsigned _LLOC) {
    m_LLOC = _LLOC;
  }

  void Scope::setLOC(unsigned _LOC) {
    m_LOC = _LOC;
  }

  void Scope::setTLLOC(unsigned _TLLOC) {
    m_TLLOC = _TLLOC;
  }

  void Scope::setTLOC(unsigned _TLOC) {
    m_TLOC = _TLOC;
  }

  void Scope::setIsAnonymous(bool _isAnonymous) {
    m_isAnonymous = _isAnonymous;
  }

  ListIterator<logical::Member> Scope::getMemberListIteratorBegin() const {
    return ListIterator<logical::Member>(&hasMemberContainer, factory, true);
  }

  ListIterator<logical::Member> Scope::getMemberListIteratorEnd() const {
    return ListIterator<logical::Member>(&hasMemberContainer, factory, false);
  }

  bool Scope::getMemberIsEmpty() const {
    return getMemberListIteratorBegin() == getMemberListIteratorEnd();
  }

  unsigned int Scope::getMemberSize() const {
    unsigned int size = 0;
    ListIterator<logical::Member> endIt = getMemberListIteratorEnd();
    for (ListIterator<logical::Member> it = getMemberListIteratorBegin(); it != endIt; ++it) {
      ++size;
    }
    return size;
  }

  bool Scope::setEdge(EdgeKind edgeKind, NodeId edgeEnd, void* acValue, bool tryOnVirtualParent) {
    switch (edgeKind) {
      case edkScope_HasMember:
        addMember(edgeEnd);
        return true;
      default:
        break;
    }
    if (logical::Member::setEdge(edgeKind, edgeEnd, acValue, false)) {
      return true;
    }
    return false;
  }

  bool Scope::removeEdge(EdgeKind edgeKind, NodeId edgeEnd, bool tryOnVirtualParent) {
    switch (edgeKind) {
      case edkScope_HasMember:
        removeMember(edgeEnd);
        return true;
      default:
        break;
    }
    if (logical::Member::removeEdge(edgeKind, edgeEnd, false)) {
      return true;
    }
    return false;
  }

  void Scope::addMember(const logical::Member *_node) {
    if (_node == NULL)
      throw LimException(COLUMBUS_LOCATION, CMSG_EX_THE_NODE_IS_NULL);

    if (&(_node->getFactory()) != this->factory)
      throw LimException(COLUMBUS_LOCATION, CMSG_EX_THE_FACTORY_OF_NODES_DOES_NOT_MATCH);

    if (!(Common::getIsMember(*_node)))
      throw LimException(COLUMBUS_LOCATION, CMSG_EX_INVALID_NODE_KIND);

    hasMemberContainer.push_back(_node->getId());
    if (factory->reverseEdges)
      factory->reverseEdges->insertEdge(_node, this, edkScope_HasMember);
  }

  void Scope::addMember(NodeId _id) {
    const logical::Member *node = dynamic_cast<logical::Member*>(factory->getPointer(_id));
    if (node == NULL)
      throw LimException(COLUMBUS_LOCATION, CMSG_EX_INVALID_NODE_KIND);
    addMember( node );
  }

  void Scope::removeMember(NodeId id) {
    if (!factory->getExist(id))
      throw LimException(COLUMBUS_LOCATION, CMSG_EX_THE_END_POINT_OF_THE_EDGE_DOES_NOT_EXIST);

    ListIterator<logical::Member>::Container::iterator it = find(hasMemberContainer.begin(), hasMemberContainer.end(), id);

    if (it == hasMemberContainer.end())
      throw LimException(COLUMBUS_LOCATION, CMSG_EX_THE_END_POINT_OF_THE_EDGE_DOES_NOT_EXIST);

    hasMemberContainer.erase(it);

    if (factory->getExistsReverseEdges())
      factory->reverseEdges->removeEdge(id, this->getId(), edkScope_HasMember);
  }

  void Scope::removeMember(logical::Member *_node) {
    if (_node == NULL)
      throw LimException(COLUMBUS_LOCATION, CMSG_EX_THE_EDGE_IS_NULL);

    removeMember(_node->getId());
  }

  double Scope::getSimilarity(const base::Base& base){
    if(base.getNodeKind() == getNodeKind()) {
      const Scope& node = dynamic_cast<const Scope&>(base);
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
      return matchAttrs / (13 / (1 - Common::SimilarityMinimum)) + Common::SimilarityMinimum;
    } else {
      return 0.0;
    }
  }

  void Scope::swapStringTable(RefDistributorStrTable& newStrTable, std::map<Key,Key>& oldAndNewStrKeyMap ){
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

  NodeHashType Scope::getHash(std::set<NodeId>& travNodes) const {
    if (hashOk) return nodeHashCache;
    common::WriteMsg::write(CMSG_GET_THE_NODE_HASH_OF_NODE_BEGIN,this->getId()); 
    if (travNodes.count(getId())>0) {
      common::WriteMsg::write(CMSG_GET_THE_NODE_HASH_OF_NODE_SKIP);
      return 0;
    }
    travNodes.insert(getId());
    Crc_type resultHash;
    resultHash.process_bytes( "logical::Scope", strlen("logical::Scope"));
    common::WriteMsg::write(CMSG_GET_THE_NODE_HASH_OF_NODE_END,resultHash.checksum()); 
    nodeHashCache = resultHash.checksum();
    hashOk = true;
    return nodeHashCache;
  }

  void Scope::save(io::BinaryIO &binIo,bool withVirtualBase  /*= true*/) const {
    Member::save(binIo,false);

    unsigned char boolValues = 0;
    boolValues <<= 1;
    if (m_isAnonymous) 
      boolValues |= 1;
    binIo.writeUByte1(boolValues);
    binIo.writeUInt4(m_LLOC);
    binIo.writeUInt4(m_LOC);
    binIo.writeUInt4(m_TLLOC);
    binIo.writeUInt4(m_TLOC);


    for (ListIterator<logical::Member>::Container::const_iterator it = hasMemberContainer.begin(); it != hasMemberContainer.end(); ++it) {
      binIo.writeUInt4(*it);
    }
    binIo.writeUInt4(0); // This is the end sign
  }

  void Scope::load(io::BinaryIO &binIo, bool withVirtualBase /*= true*/) {
    Member::load(binIo,false);

    unsigned char boolValues = binIo.readUByte1();
    m_isAnonymous = boolValues & 1;
    boolValues >>= 1;
    m_LLOC = binIo.readUInt4();
    m_LOC = binIo.readUInt4();
    m_TLLOC = binIo.readUInt4();
    m_TLOC = binIo.readUInt4();

    NodeId _id;

    _id = binIo.readUInt4();
    while (_id) {
      hasMemberContainer.push_back(_id);
      _id = binIo.readUInt4();
    }
  }


}


}}}
