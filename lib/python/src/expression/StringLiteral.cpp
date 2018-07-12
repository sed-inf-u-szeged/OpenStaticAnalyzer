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

#include "python/inc/python.h"
#include "python/inc/Common.h"
#include "common/inc/WriteMessage.h"

#include "python/inc/messages.h"
#include <algorithm>
#include <string.h>
#include "common/inc/math/common.h"


namespace columbus { namespace python { namespace asg {

typedef boost::crc_32_type  Crc_type;

namespace expression { 
  StringLiteral::StringLiteral(NodeId _id, Factory *_factory) :
    Literal(_id, _factory),
    m_value(0)
  {
  }

  StringLiteral::~StringLiteral() {
  }

  void StringLiteral::prepareDelete(bool tryOnVirtualParent){
    expression::Literal::prepareDelete(false);
  }

  NodeKind StringLiteral::getNodeKind() const {
    return ndkStringLiteral;
  }

  Key StringLiteral::getValueKey() const {
    return m_value;
  }

  const std::string& StringLiteral::getValue() const {
    return factory->getStringTable().get(m_value);
  }

  void StringLiteral::setValueKey(Key _value) {
    m_value = _value;
  }

  void StringLiteral::setValue(const std::string& _value) {
    m_value = factory->getStringTable().set(_value);
  }

  bool StringLiteral::setEdge(EdgeKind edgeKind, NodeId edgeEnd, bool tryOnVirtualParent) {
    if (expression::Literal::setEdge(edgeKind, edgeEnd, false)) {
      return true;
    }
    return false;
  }

  bool StringLiteral::removeEdge(EdgeKind edgeKind, NodeId edgeEnd, bool tryOnVirtualParent) {
    if (expression::Literal::removeEdge(edgeKind, edgeEnd, false)) {
      return true;
    }
    return false;
  }

  void StringLiteral::accept(Visitor &visitor) const {
    visitor.visit(*this);
  }

  void StringLiteral::acceptEnd(Visitor &visitor) const {
    visitor.visitEnd(*this);
  }

  double StringLiteral::getSimilarity(const base::Base& base){
    if(base.getNodeKind() == getNodeKind()) {
      const StringLiteral& node = dynamic_cast<const StringLiteral&>(base);
      double matchAttrs = 0;
      std::string str1, str2;
      size_t strMax;
      double strSim;
      str1 = getValue();
      str2 = node.getValue();
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

  void StringLiteral::swapStringTable(RefDistributorStrTable& newStrTable, std::map<Key,Key>& oldAndNewStrKeyMap ){
    std::map<Key,Key>::iterator foundKeyId;

    foundKeyId = oldAndNewStrKeyMap.find(m_value);
    if (foundKeyId != oldAndNewStrKeyMap.end()) {
      m_value = foundKeyId->second;
    } else {
      Key oldkey = m_value;
      m_value = newStrTable.set(factory->getStringTable().get(m_value));
      oldAndNewStrKeyMap.insert(std::pair<Key,Key>(oldkey,m_value));    }

  }

  NodeHashType StringLiteral::getHash(std::set<NodeId>& travNodes) const {
    if (hashOk) return nodeHashCache;
    common::WriteMsg::write(CMSG_GET_THE_NODE_HASH_OF_NODE_BEGIN,this->getId()); 
    if (travNodes.count(getId())>0) {
      common::WriteMsg::write(CMSG_GET_THE_NODE_HASH_OF_NODE_SKIP);
      return 0;
    }
    travNodes.insert(getId());
    Crc_type resultHash;
    resultHash.process_bytes( "expression::StringLiteral", strlen("expression::StringLiteral"));
    common::WriteMsg::write(CMSG_GET_THE_NODE_HASH_OF_NODE_END,resultHash.checksum()); 
    nodeHashCache = resultHash.checksum();
    hashOk = true;
    return nodeHashCache;
  }

  void StringLiteral::save(io::BinaryIO &binIo,bool withVirtualBase  /*= true*/) const {
    Literal::save(binIo,false);

    factory->getStringTable().setType(m_value, StrTable::strToSave);
    binIo.writeUInt4(m_value);

  }

  void StringLiteral::load(io::BinaryIO &binIo, bool withVirtualBase /*= true*/) {
    Literal::load(binIo,false);

    m_value = binIo.readUInt4();

  }


}


}}}
