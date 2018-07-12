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

#include "javascript/inc/javascript.h"
#include "javascript/inc/Common.h"
#include "common/inc/WriteMessage.h"

#include "javascript/inc/messages.h"
#include <algorithm>
#include <string.h>
#include "common/inc/math/common.h"


namespace columbus { namespace javascript { namespace asg {

typedef boost::crc_32_type  Crc_type;

namespace expression { 
  RegExpLiteral::RegExpLiteral(NodeId _id, Factory *_factory) :
         Positioned(_id, _factory),
    Literal(_id, _factory),
    m_pattern(0),
    m_flags(0)
  {
  }

  RegExpLiteral::~RegExpLiteral() {
  }

  void RegExpLiteral::prepareDelete(bool tryOnVirtualParent){
    if (tryOnVirtualParent) {
      base::Positioned::prepareDelete(false);
    }
    expression::Literal::prepareDelete(false);
  }

  NodeKind RegExpLiteral::getNodeKind() const {
    return ndkRegExpLiteral;
  }

  Key RegExpLiteral::getPatternKey() const {
    return m_pattern;
  }

  const std::string& RegExpLiteral::getPattern() const {
    return factory->getStringTable().get(m_pattern);
  }

  Key RegExpLiteral::getFlagsKey() const {
    return m_flags;
  }

  const std::string& RegExpLiteral::getFlags() const {
    return factory->getStringTable().get(m_flags);
  }

  void RegExpLiteral::setPatternKey(Key _pattern) {
    m_pattern = _pattern;
  }

  void RegExpLiteral::setPattern(const std::string& _pattern) {
    m_pattern = factory->getStringTable().set(_pattern);
  }

  void RegExpLiteral::setFlagsKey(Key _flags) {
    m_flags = _flags;
  }

  void RegExpLiteral::setFlags(const std::string& _flags) {
    m_flags = factory->getStringTable().set(_flags);
  }

  bool RegExpLiteral::setEdge(EdgeKind edgeKind, NodeId edgeEnd, bool tryOnVirtualParent) {
    if (tryOnVirtualParent) {
      if (base::Positioned::setEdge(edgeKind, edgeEnd, false)) {
        return true;
      }
    }
    if (expression::Literal::setEdge(edgeKind, edgeEnd, false)) {
      return true;
    }
    return false;
  }

  bool RegExpLiteral::removeEdge(EdgeKind edgeKind, NodeId edgeEnd, bool tryOnVirtualParent) {
    if (tryOnVirtualParent) {
      if (base::Positioned::removeEdge(edgeKind, edgeEnd, false)) {
        return true;
      }
    }
    if (expression::Literal::removeEdge(edgeKind, edgeEnd, false)) {
      return true;
    }
    return false;
  }

  void RegExpLiteral::accept(Visitor &visitor) const {
    visitor.visit(*this);
  }

  void RegExpLiteral::acceptEnd(Visitor &visitor) const {
    visitor.visitEnd(*this);
  }

  double RegExpLiteral::getSimilarity(const base::Base& base){
    if(base.getNodeKind() == getNodeKind()) {
      const RegExpLiteral& node = dynamic_cast<const RegExpLiteral&>(base);
      double matchAttrs = 0;
      std::string str1, str2;
      size_t strMax;
      double strSim;
      str1 = getRaw();
      str2 = node.getRaw();
      strMax = std::max(str1.size(), str2.size());
      strSim = 1 - ((double)common::math::editDistance(str1, str2) / (strMax > 0 ? strMax : 1));
      if (strSim < Common::SimilarityMinForStrings)
        return 0.0;
      matchAttrs += strSim;
      str1 = getPattern();
      str2 = node.getPattern();
      strMax = std::max(str1.size(), str2.size());
      strSim = 1 - ((double)common::math::editDistance(str1, str2) / (strMax > 0 ? strMax : 1));
      if (strSim < Common::SimilarityMinForStrings)
        return 0.0;
      matchAttrs += strSim;
      str1 = getFlags();
      str2 = node.getFlags();
      strMax = std::max(str1.size(), str2.size());
      strSim = 1 - ((double)common::math::editDistance(str1, str2) / (strMax > 0 ? strMax : 1));
      if (strSim < Common::SimilarityMinForStrings)
        return 0.0;
      matchAttrs += strSim;
      return matchAttrs / (3 / (1 - Common::SimilarityMinimum)) + Common::SimilarityMinimum;
    } else {
      return 0.0;
    }
  }

  void RegExpLiteral::swapStringTable(RefDistributorStrTable& newStrTable, std::map<Key,Key>& oldAndNewStrKeyMap ){
    std::map<Key,Key>::iterator foundKeyId;

    foundKeyId = oldAndNewStrKeyMap.find(m_pattern);
    if (foundKeyId != oldAndNewStrKeyMap.end()) {
      m_pattern = foundKeyId->second;
    } else {
      Key oldkey = m_pattern;
      m_pattern = newStrTable.set(factory->getStringTable().get(m_pattern));
      oldAndNewStrKeyMap.insert(std::pair<Key,Key>(oldkey,m_pattern));    }

    foundKeyId = oldAndNewStrKeyMap.find(m_flags);
    if (foundKeyId != oldAndNewStrKeyMap.end()) {
      m_flags = foundKeyId->second;
    } else {
      Key oldkey = m_flags;
      m_flags = newStrTable.set(factory->getStringTable().get(m_flags));
      oldAndNewStrKeyMap.insert(std::pair<Key,Key>(oldkey,m_flags));    }

    foundKeyId = oldAndNewStrKeyMap.find(m_raw);
    if (foundKeyId != oldAndNewStrKeyMap.end()) {
      m_raw = foundKeyId->second;
    } else {
      Key oldkey = m_raw;
      m_raw = newStrTable.set(factory->getStringTable().get(m_raw));
      oldAndNewStrKeyMap.insert(std::pair<Key,Key>(oldkey,m_raw));    }

  }

  NodeHashType RegExpLiteral::getHash(std::set<NodeId>& travNodes) const {
    if (hashOk) return nodeHashCache;
    common::WriteMsg::write(CMSG_GET_THE_NODE_HASH_OF_NODE_BEGIN,this->getId()); 
    if (travNodes.count(getId())>0) {
      common::WriteMsg::write(CMSG_GET_THE_NODE_HASH_OF_NODE_SKIP);
      return 0;
    }
    travNodes.insert(getId());
    Crc_type resultHash;
    resultHash.process_bytes( "expression::RegExpLiteral", strlen("expression::RegExpLiteral"));
    common::WriteMsg::write(CMSG_GET_THE_NODE_HASH_OF_NODE_END,resultHash.checksum()); 
    nodeHashCache = resultHash.checksum();
    hashOk = true;
    return nodeHashCache;
  }

  void RegExpLiteral::save(io::BinaryIO &binIo,bool withVirtualBase  /*= true*/) const {
    if (withVirtualBase)
      Positioned::save(binIo,false);

    Literal::save(binIo,false);

    factory->getStringTable().setType(m_pattern, StrTable::strToSave);
    binIo.writeUInt4(m_pattern);
    factory->getStringTable().setType(m_flags, StrTable::strToSave);
    binIo.writeUInt4(m_flags);

  }

  void RegExpLiteral::load(io::BinaryIO &binIo, bool withVirtualBase /*= true*/) {
    if (withVirtualBase)
      Positioned::load(binIo, false);

    Literal::load(binIo,false);

    m_pattern = binIo.readUInt4();
    m_flags = binIo.readUInt4();

  }


}


}}}
