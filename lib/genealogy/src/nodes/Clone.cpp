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

#include "genealogy/inc/genealogy.h"
#include "genealogy/inc/Common.h"
#include "common/inc/WriteMessage.h"

#include "genealogy/inc/messages.h"
#include <algorithm>
#include <string.h>
#include "common/inc/math/common.h"


namespace columbus { namespace genealogy { 

typedef boost::crc_32_type  Crc_type;

  Clone::Clone(NodeId _id, Factory *_factory) :
    Trackable(_id, _factory),
    m_isVirtual(false),
    m_cloneSmellType(cstNone),
    m_uniqueName(0)
  {
  }

  Clone::~Clone() {
  }

  void Clone::prepareDelete(bool tryOnVirtualParent){
    Trackable::prepareDelete(false);
  }

  NodeKind Clone::getNodeKind() const {
    return ndkClone;
  }

  Key Clone::getUniqueNameKey() const {
    return m_uniqueName;
  }

  const std::string& Clone::getUniqueName() const {
    return factory->getStringTable().get(m_uniqueName);
  }

  CloneSmellType Clone::getCloneSmellType() const {
    return m_cloneSmellType;
  }

  bool Clone::getIsVirtual() const {
    return m_isVirtual;
  }

  void Clone::setUniqueNameKey(Key _uniqueName) {
    m_uniqueName = _uniqueName;
  }

  void Clone::setUniqueName(const std::string& _uniqueName) {
    m_uniqueName = factory->getStringTable().set(_uniqueName);
  }

  void Clone::setCloneSmellType(CloneSmellType _cloneSmellType) {
    m_cloneSmellType = _cloneSmellType;
  }

  void Clone::setIsVirtual(bool _isVirtual) {
    m_isVirtual = _isVirtual;
  }

  bool Clone::setEdge(EdgeKind edgeKind, NodeId edgeEnd, bool tryOnVirtualParent) {
    if (Trackable::setEdge(edgeKind, edgeEnd, false)) {
      return true;
    }
    return false;
  }

  bool Clone::removeEdge(EdgeKind edgeKind, NodeId edgeEnd, bool tryOnVirtualParent) {
    if (Trackable::removeEdge(edgeKind, edgeEnd, false)) {
      return true;
    }
    return false;
  }

  void Clone::accept(Visitor &visitor) const {
    visitor.visit(*this);
  }

  void Clone::acceptEnd(Visitor &visitor) const {
    visitor.visitEnd(*this);
  }

  double Clone::getSimilarity(const Base& base){
    if(base.getNodeKind() == getNodeKind()) {
      const Clone& node = dynamic_cast<const Clone&>(base);
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
      if(node.getCloneSmellType() == getCloneSmellType()) ++matchAttrs;
      if(node.getIsVirtual() == getIsVirtual()) ++matchAttrs;
      return matchAttrs / (3 / (1 - Common::SimilarityMinimum)) + Common::SimilarityMinimum;
    } else {
      return 0.0;
    }
  }

  void Clone::swapStringTable(RefDistributorStrTable& newStrTable, std::map<Key,Key>& oldAndNewStrKeyMap ){
    std::map<Key,Key>::iterator foundKeyId;

    foundKeyId = oldAndNewStrKeyMap.find(m_uniqueName);
    if (foundKeyId != oldAndNewStrKeyMap.end()) {
      m_uniqueName = foundKeyId->second;
    } else {
      Key oldkey = m_uniqueName;
      m_uniqueName = newStrTable.set(factory->getStringTable().get(m_uniqueName));
      oldAndNewStrKeyMap.insert(std::pair<Key,Key>(oldkey,m_uniqueName));    }

  }

  NodeHashType Clone::getHash(std::set<NodeId>& travNodes) const {
    if (hashOk) return nodeHashCache;
    common::WriteMsg::write(CMSG_GET_THE_NODE_HASH_OF_NODE_BEGIN,this->getId()); 
    if (travNodes.count(getId())>0) {
      common::WriteMsg::write(CMSG_GET_THE_NODE_HASH_OF_NODE_SKIP);
      return 0;
    }
    travNodes.insert(getId());
    Crc_type resultHash;
    resultHash.process_bytes( "Clone", strlen("Clone"));
    common::WriteMsg::write(CMSG_GET_THE_NODE_HASH_OF_NODE_END,resultHash.checksum()); 
    nodeHashCache = resultHash.checksum();
    hashOk = true;
    return nodeHashCache;
  }

  void Clone::save(io::BinaryIO &binIo,bool withVirtualBase  /*= true*/) const {
    Trackable::save(binIo,false);

    unsigned char boolValues = 0;
    boolValues <<= 1;
    if (m_isVirtual) 
      boolValues |= 1;
    binIo.writeUByte1(boolValues);
    factory->getStringTable().setType(m_uniqueName, StrTable::strToSave);
    binIo.writeUInt4(m_uniqueName);
    binIo.writeUByte1(m_cloneSmellType);

  }

  void Clone::load(io::BinaryIO &binIo, bool withVirtualBase /*= true*/) {
    Trackable::load(binIo,false);

    unsigned char boolValues = binIo.readUByte1();
    m_isVirtual = boolValues & 1;
    boolValues >>= 1;
    m_uniqueName = binIo.readUInt4();
    m_cloneSmellType = (CloneSmellType)binIo.readUByte1();

  }



}}
