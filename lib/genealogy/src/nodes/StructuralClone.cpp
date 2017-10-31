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

#include "genealogy/inc/genealogy.h"
#include "genealogy/inc/Common.h"
#include "common/inc/WriteMessage.h"

#include "genealogy/inc/messages.h"
#include <algorithm>
#include <string.h>
#include "common/inc/math/common.h"


namespace columbus { namespace genealogy { 

typedef boost::crc_32_type  Crc_type;

  StructuralClone::StructuralClone(NodeId _id, Factory *_factory) :
    Trackable(_id, _factory),
    m_uniqueName(0),
    m_fullyQualifiedName(0)
  {
  }

  StructuralClone::~StructuralClone() {
  }

  void StructuralClone::prepareDelete(bool tryOnVirtualParent){
    Trackable::prepareDelete(false);
  }

  NodeKind StructuralClone::getNodeKind() const {
    return ndkStructuralClone;
  }

  Key StructuralClone::getUniqueNameKey() const {
    return m_uniqueName;
  }

  const std::string& StructuralClone::getUniqueName() const {
    return factory->getStringTable().get(m_uniqueName);
  }

  Key StructuralClone::getFullyQualifiedNameKey() const {
    return m_fullyQualifiedName;
  }

  const std::string& StructuralClone::getFullyQualifiedName() const {
    return factory->getStringTable().get(m_fullyQualifiedName);
  }

  void StructuralClone::setUniqueNameKey(Key _uniqueName) {
    m_uniqueName = _uniqueName;
  }

  void StructuralClone::setUniqueName(const std::string& _uniqueName) {
    m_uniqueName = factory->getStringTable().set(_uniqueName);
  }

  void StructuralClone::setFullyQualifiedNameKey(Key _fullyQualifiedName) {
    m_fullyQualifiedName = _fullyQualifiedName;
  }

  void StructuralClone::setFullyQualifiedName(const std::string& _fullyQualifiedName) {
    m_fullyQualifiedName = factory->getStringTable().set(_fullyQualifiedName);
  }

  bool StructuralClone::setEdge(EdgeKind edgeKind, NodeId edgeEnd, bool tryOnVirtualParent) {
    if (Trackable::setEdge(edgeKind, edgeEnd, false)) {
      return true;
    }
    return false;
  }

  bool StructuralClone::removeEdge(EdgeKind edgeKind, NodeId edgeEnd, bool tryOnVirtualParent) {
    if (Trackable::removeEdge(edgeKind, edgeEnd, false)) {
      return true;
    }
    return false;
  }

  void StructuralClone::accept(Visitor &visitor) const {
    visitor.visit(*this);
  }

  void StructuralClone::acceptEnd(Visitor &visitor) const {
    visitor.visitEnd(*this);
  }

  double StructuralClone::getSimilarity(const Base& base){
    if(base.getNodeKind() == getNodeKind()) {
      const StructuralClone& node = dynamic_cast<const StructuralClone&>(base);
      double matchAttrs = 0;
      std::string str1, str2;
      size_t strMax;
      double strSim;
      str1 = getUniqueName();
      str2 = node.getUniqueName();
      strMax = std::max(str1.size(), str2.size());
      strSim = 1 - ((double)common::math::editDistance(str1, str2) / (strMax > 0 ? strMax : 1));
      if (strSim < Common::SimilarityMinForStrings)
        return 0.0;
      matchAttrs += strSim;
      str1 = getFullyQualifiedName();
      str2 = node.getFullyQualifiedName();
      strMax = std::max(str1.size(), str2.size());
      strSim = 1 - ((double)common::math::editDistance(str1, str2) / (strMax > 0 ? strMax : 1));
      if (strSim < Common::SimilarityMinForStrings)
        return 0.0;
      matchAttrs += strSim;
      return matchAttrs / (2 / (1 - Common::SimilarityMinimum)) + Common::SimilarityMinimum;
    } else {
      return 0.0;
    }
  }

  void StructuralClone::swapStringTable(RefDistributorStrTable& newStrTable, std::map<Key,Key>& oldAndNewStrKeyMap ){
    std::map<Key,Key>::iterator foundKeyId;

    foundKeyId = oldAndNewStrKeyMap.find(m_uniqueName);
    if (foundKeyId != oldAndNewStrKeyMap.end()) {
      m_uniqueName = foundKeyId->second;
    } else {
      Key oldkey = m_uniqueName;
      m_uniqueName = newStrTable.set(factory->getStringTable().get(m_uniqueName));
      oldAndNewStrKeyMap.insert(std::pair<Key,Key>(oldkey,m_uniqueName));    }

    foundKeyId = oldAndNewStrKeyMap.find(m_fullyQualifiedName);
    if (foundKeyId != oldAndNewStrKeyMap.end()) {
      m_fullyQualifiedName = foundKeyId->second;
    } else {
      Key oldkey = m_fullyQualifiedName;
      m_fullyQualifiedName = newStrTable.set(factory->getStringTable().get(m_fullyQualifiedName));
      oldAndNewStrKeyMap.insert(std::pair<Key,Key>(oldkey,m_fullyQualifiedName));    }

  }

  NodeHashType StructuralClone::getHash(std::set<NodeId>& travNodes) const {
    if (hashOk) return nodeHashCache;
    common::WriteMsg::write(CMSG_GET_THE_NODE_HASH_OF_NODE_BEGIN,this->getId()); 
    if (travNodes.count(getId())>0) {
      common::WriteMsg::write(CMSG_GET_THE_NODE_HASH_OF_NODE_SKIP);
      return 0;
    }
    travNodes.insert(getId());
    Crc_type resultHash;
    resultHash.process_bytes( "StructuralClone", strlen("StructuralClone"));
    common::WriteMsg::write(CMSG_GET_THE_NODE_HASH_OF_NODE_END,resultHash.checksum()); 
    nodeHashCache = resultHash.checksum();
    hashOk = true;
    return nodeHashCache;
  }

  void StructuralClone::save(io::BinaryIO &binIo,bool withVirtualBase  /*= true*/) const {
    Trackable::save(binIo,false);

    factory->getStringTable().setType(m_uniqueName, StrTable::strToSave);
    binIo.writeUInt4(m_uniqueName);
    factory->getStringTable().setType(m_fullyQualifiedName, StrTable::strToSave);
    binIo.writeUInt4(m_fullyQualifiedName);

  }

  void StructuralClone::load(io::BinaryIO &binIo, bool withVirtualBase /*= true*/) {
    Trackable::load(binIo,false);

    m_uniqueName = binIo.readUInt4();
    m_fullyQualifiedName = binIo.readUInt4();

  }



}}
