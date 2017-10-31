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

  Component::Component(NodeId _id, Factory *_factory) :
    Base(_id, _factory),
    m_location(0),
    m_name(0),
    m_code(0)
  {
  }

  Component::~Component() {
  }

  void Component::prepareDelete(bool tryOnVirtualParent){
    Base::prepareDelete(false);
  }

  NodeKind Component::getNodeKind() const {
    return ndkComponent;
  }

  Key Component::getLocationKey() const {
    return m_location;
  }

  const std::string& Component::getLocation() const {
    return factory->getStringTable().get(m_location);
  }

  Key Component::getNameKey() const {
    return m_name;
  }

  const std::string& Component::getName() const {
    return factory->getStringTable().get(m_name);
  }

  unsigned long long Component::getCode() const {
    return m_code;
  }

  void Component::setLocationKey(Key _location) {
    m_location = _location;
  }

  void Component::setLocation(const std::string& _location) {
    m_location = factory->getStringTable().set(_location);
  }

  void Component::setNameKey(Key _name) {
    m_name = _name;
  }

  void Component::setName(const std::string& _name) {
    m_name = factory->getStringTable().set(_name);
  }

  void Component::setCode(unsigned long long _code) {
    m_code = _code;
  }

  bool Component::setEdge(EdgeKind edgeKind, NodeId edgeEnd, bool tryOnVirtualParent) {
    if (Base::setEdge(edgeKind, edgeEnd, false)) {
      return true;
    }
    return false;
  }

  bool Component::removeEdge(EdgeKind edgeKind, NodeId edgeEnd, bool tryOnVirtualParent) {
    if (Base::removeEdge(edgeKind, edgeEnd, false)) {
      return true;
    }
    return false;
  }

  void Component::accept(Visitor &visitor) const {
    visitor.visit(*this);
  }

  void Component::acceptEnd(Visitor &visitor) const {
    visitor.visitEnd(*this);
  }

  double Component::getSimilarity(const Base& base){
    if(base.getNodeKind() == getNodeKind()) {
      const Component& node = dynamic_cast<const Component&>(base);
      double matchAttrs = 0;
      std::string str1, str2;
      size_t strMax;
      double strSim;
      str1 = getLocation();
      str2 = node.getLocation();
      strMax = std::max(str1.size(), str2.size());
      strSim = 1 - ((double)common::math::editDistance(str1, str2) / (strMax > 0 ? strMax : 1));
      if (strSim < Common::SimilarityMinForStrings)
        return 0.0;
      matchAttrs += strSim;
      str1 = getName();
      str2 = node.getName();
      strMax = std::max(str1.size(), str2.size());
      strSim = 1 - ((double)common::math::editDistance(str1, str2) / (strMax > 0 ? strMax : 1));
      if (strSim < Common::SimilarityMinForStrings)
        return 0.0;
      matchAttrs += strSim;
      if(node.getCode() == getCode()) ++matchAttrs;
      return matchAttrs / (3 / (1 - Common::SimilarityMinimum)) + Common::SimilarityMinimum;
    } else {
      return 0.0;
    }
  }

  void Component::swapStringTable(RefDistributorStrTable& newStrTable, std::map<Key,Key>& oldAndNewStrKeyMap ){
    std::map<Key,Key>::iterator foundKeyId;

    foundKeyId = oldAndNewStrKeyMap.find(m_location);
    if (foundKeyId != oldAndNewStrKeyMap.end()) {
      m_location = foundKeyId->second;
    } else {
      Key oldkey = m_location;
      m_location = newStrTable.set(factory->getStringTable().get(m_location));
      oldAndNewStrKeyMap.insert(std::pair<Key,Key>(oldkey,m_location));    }

    foundKeyId = oldAndNewStrKeyMap.find(m_name);
    if (foundKeyId != oldAndNewStrKeyMap.end()) {
      m_name = foundKeyId->second;
    } else {
      Key oldkey = m_name;
      m_name = newStrTable.set(factory->getStringTable().get(m_name));
      oldAndNewStrKeyMap.insert(std::pair<Key,Key>(oldkey,m_name));    }

  }

  NodeHashType Component::getHash(std::set<NodeId>& travNodes) const {
    if (hashOk) return nodeHashCache;
    common::WriteMsg::write(CMSG_GET_THE_NODE_HASH_OF_NODE_BEGIN,this->getId()); 
    if (travNodes.count(getId())>0) {
      common::WriteMsg::write(CMSG_GET_THE_NODE_HASH_OF_NODE_SKIP);
      return 0;
    }
    travNodes.insert(getId());
    Crc_type resultHash;
    resultHash.process_bytes( "Component", strlen("Component"));
    common::WriteMsg::write(CMSG_GET_THE_NODE_HASH_OF_NODE_END,resultHash.checksum()); 
    nodeHashCache = resultHash.checksum();
    hashOk = true;
    return nodeHashCache;
  }

  void Component::save(io::BinaryIO &binIo,bool withVirtualBase  /*= true*/) const {
    Base::save(binIo,false);

    factory->getStringTable().setType(m_location, StrTable::strToSave);
    binIo.writeUInt4(m_location);
    factory->getStringTable().setType(m_name, StrTable::strToSave);
    binIo.writeUInt4(m_name);
    binIo.writeULongLong8(m_code);

  }

  void Component::load(io::BinaryIO &binIo, bool withVirtualBase /*= true*/) {
    Base::load(binIo,false);

    m_location = binIo.readUInt4();
    m_name = binIo.readUInt4();
    m_code = binIo.readULongLong8();

  }



}}
