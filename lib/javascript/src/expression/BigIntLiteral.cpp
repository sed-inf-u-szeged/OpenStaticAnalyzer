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
  BigIntLiteral::BigIntLiteral(NodeId _id, Factory *_factory) :
         Positioned(_id, _factory),
    Literal(_id, _factory),
    m_bigint(0)
  {
  }

  BigIntLiteral::~BigIntLiteral() {
  }

  void BigIntLiteral::prepareDelete(bool tryOnVirtualParent){
    if (tryOnVirtualParent) {
      base::Positioned::prepareDelete(false);
    }
    expression::Literal::prepareDelete(false);
  }

  NodeKind BigIntLiteral::getNodeKind() const {
    return ndkBigIntLiteral;
  }

  Key BigIntLiteral::getBigintKey() const {
    return m_bigint;
  }

  const std::string& BigIntLiteral::getBigint() const {
    return factory->getStringTable().get(m_bigint);
  }

  void BigIntLiteral::setBigintKey(Key _bigint) {
    m_bigint = _bigint;
  }

  void BigIntLiteral::setBigint(const std::string& _bigint) {
    m_bigint = factory->getStringTable().set(_bigint);
  }

  bool BigIntLiteral::setEdge(EdgeKind edgeKind, NodeId edgeEnd, bool tryOnVirtualParent) {
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

  bool BigIntLiteral::removeEdge(EdgeKind edgeKind, NodeId edgeEnd, bool tryOnVirtualParent) {
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

  void BigIntLiteral::accept(Visitor &visitor) const {
    visitor.visit(*this);
  }

  void BigIntLiteral::acceptEnd(Visitor &visitor) const {
    visitor.visitEnd(*this);
  }

  double BigIntLiteral::getSimilarity(const base::Base& base){
    if(base.getNodeKind() == getNodeKind()) {
      const BigIntLiteral& node = dynamic_cast<const BigIntLiteral&>(base);
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
      str1 = getBigint();
      str2 = node.getBigint();
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

  void BigIntLiteral::swapStringTable(RefDistributorStrTable& newStrTable, std::map<Key,Key>& oldAndNewStrKeyMap ){
    std::map<Key,Key>::iterator foundKeyId;

    foundKeyId = oldAndNewStrKeyMap.find(m_bigint);
    if (foundKeyId != oldAndNewStrKeyMap.end()) {
      m_bigint = foundKeyId->second;
    } else {
      Key oldkey = m_bigint;
      m_bigint = newStrTable.set(factory->getStringTable().get(m_bigint));
      oldAndNewStrKeyMap.insert(std::pair<Key,Key>(oldkey,m_bigint));    }

    foundKeyId = oldAndNewStrKeyMap.find(m_raw);
    if (foundKeyId != oldAndNewStrKeyMap.end()) {
      m_raw = foundKeyId->second;
    } else {
      Key oldkey = m_raw;
      m_raw = newStrTable.set(factory->getStringTable().get(m_raw));
      oldAndNewStrKeyMap.insert(std::pair<Key,Key>(oldkey,m_raw));    }

  }

  NodeHashType BigIntLiteral::getHash(std::set<NodeId>& travNodes) const {
    if (hashOk) return nodeHashCache;
    common::WriteMsg::write(CMSG_GET_THE_NODE_HASH_OF_NODE_BEGIN,this->getId()); 
    if (travNodes.count(getId())>0) {
      common::WriteMsg::write(CMSG_GET_THE_NODE_HASH_OF_NODE_SKIP);
      return 0;
    }
    travNodes.insert(getId());
    Crc_type resultHash;
    resultHash.process_bytes( "expression::BigIntLiteral", strlen("expression::BigIntLiteral"));
    common::WriteMsg::write(CMSG_GET_THE_NODE_HASH_OF_NODE_END,resultHash.checksum()); 
    nodeHashCache = resultHash.checksum();
    hashOk = true;
    return nodeHashCache;
  }

  void BigIntLiteral::save(io::BinaryIO &binIo,bool withVirtualBase  /*= true*/) const {
    if (withVirtualBase)
      Positioned::save(binIo,false);

    Literal::save(binIo,false);

    factory->getStringTable().setType(m_bigint, StrTable::strToSave);
    binIo.writeUInt4(m_bigint);

  }

  void BigIntLiteral::load(io::BinaryIO &binIo, bool withVirtualBase /*= true*/) {
    if (withVirtualBase)
      Positioned::load(binIo, false);

    Literal::load(binIo,false);

    m_bigint = binIo.readUInt4();

  }


}


}}}
