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
  TemplateElement::TemplateElement(NodeId _id, Factory *_factory) :
    Positioned(_id, _factory),
    m_tail(false),
    m_cooked(0),
    m_value(0)
  {
  }

  TemplateElement::~TemplateElement() {
  }

  void TemplateElement::prepareDelete(bool tryOnVirtualParent){
    base::Positioned::prepareDelete(false);
  }

  NodeKind TemplateElement::getNodeKind() const {
    return ndkTemplateElement;
  }

  bool TemplateElement::getTail() const {
    return m_tail;
  }

  Key TemplateElement::getCookedKey() const {
    return m_cooked;
  }

  const std::string& TemplateElement::getCooked() const {
    return factory->getStringTable().get(m_cooked);
  }

  Key TemplateElement::getValueKey() const {
    return m_value;
  }

  const std::string& TemplateElement::getValue() const {
    return factory->getStringTable().get(m_value);
  }

  void TemplateElement::setTail(bool _tail) {
    m_tail = _tail;
  }

  void TemplateElement::setCookedKey(Key _cooked) {
    m_cooked = _cooked;
  }

  void TemplateElement::setCooked(const std::string& _cooked) {
    m_cooked = factory->getStringTable().set(_cooked);
  }

  void TemplateElement::setValueKey(Key _value) {
    m_value = _value;
  }

  void TemplateElement::setValue(const std::string& _value) {
    m_value = factory->getStringTable().set(_value);
  }

  bool TemplateElement::setEdge(EdgeKind edgeKind, NodeId edgeEnd, bool tryOnVirtualParent) {
    if (base::Positioned::setEdge(edgeKind, edgeEnd, false)) {
      return true;
    }
    return false;
  }

  bool TemplateElement::removeEdge(EdgeKind edgeKind, NodeId edgeEnd, bool tryOnVirtualParent) {
    if (base::Positioned::removeEdge(edgeKind, edgeEnd, false)) {
      return true;
    }
    return false;
  }

  void TemplateElement::accept(Visitor &visitor) const {
    visitor.visit(*this);
  }

  void TemplateElement::acceptEnd(Visitor &visitor) const {
    visitor.visitEnd(*this);
  }

  double TemplateElement::getSimilarity(const base::Base& base){
    if(base.getNodeKind() == getNodeKind()) {
      const TemplateElement& node = dynamic_cast<const TemplateElement&>(base);
      double matchAttrs = 0;
      if(node.getTail() == getTail()) ++matchAttrs;
      std::string str1, str2;
      size_t strMax;
      double strSim;
      str1 = getCooked();
      str2 = node.getCooked();
      strMax = std::max(str1.size(), str2.size());
      strSim = 1 - ((double)common::math::editDistance(str1, str2) / (strMax > 0 ? strMax : 1));
      if (strSim < Common::SimilarityMinForStrings)
        return 0.0;
      matchAttrs += strSim;
      str1 = getValue();
      str2 = node.getValue();
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

  void TemplateElement::swapStringTable(RefDistributorStrTable& newStrTable, std::map<Key,Key>& oldAndNewStrKeyMap ){
    std::map<Key,Key>::iterator foundKeyId;

    foundKeyId = oldAndNewStrKeyMap.find(m_cooked);
    if (foundKeyId != oldAndNewStrKeyMap.end()) {
      m_cooked = foundKeyId->second;
    } else {
      Key oldkey = m_cooked;
      m_cooked = newStrTable.set(factory->getStringTable().get(m_cooked));
      oldAndNewStrKeyMap.insert(std::pair<Key,Key>(oldkey,m_cooked));    }

    foundKeyId = oldAndNewStrKeyMap.find(m_value);
    if (foundKeyId != oldAndNewStrKeyMap.end()) {
      m_value = foundKeyId->second;
    } else {
      Key oldkey = m_value;
      m_value = newStrTable.set(factory->getStringTable().get(m_value));
      oldAndNewStrKeyMap.insert(std::pair<Key,Key>(oldkey,m_value));    }

  }

  NodeHashType TemplateElement::getHash(std::set<NodeId>& travNodes) const {
    if (hashOk) return nodeHashCache;
    common::WriteMsg::write(CMSG_GET_THE_NODE_HASH_OF_NODE_BEGIN,this->getId()); 
    if (travNodes.count(getId())>0) {
      common::WriteMsg::write(CMSG_GET_THE_NODE_HASH_OF_NODE_SKIP);
      return 0;
    }
    travNodes.insert(getId());
    Crc_type resultHash;
    resultHash.process_bytes( "expression::TemplateElement", strlen("expression::TemplateElement"));
    common::WriteMsg::write(CMSG_GET_THE_NODE_HASH_OF_NODE_END,resultHash.checksum()); 
    nodeHashCache = resultHash.checksum();
    hashOk = true;
    return nodeHashCache;
  }

  void TemplateElement::save(io::BinaryIO &binIo,bool withVirtualBase  /*= true*/) const {
    Positioned::save(binIo,false);

    unsigned char boolValues = 0;
    boolValues <<= 1;
    if (m_tail) 
      boolValues |= 1;
    binIo.writeUByte1(boolValues);
    factory->getStringTable().setType(m_cooked, StrTable::strToSave);
    binIo.writeUInt4(m_cooked);
    factory->getStringTable().setType(m_value, StrTable::strToSave);
    binIo.writeUInt4(m_value);

  }

  void TemplateElement::load(io::BinaryIO &binIo, bool withVirtualBase /*= true*/) {
    Positioned::load(binIo,false);

    unsigned char boolValues = binIo.readUByte1();
    m_tail = boolValues & 1;
    boolValues >>= 1;
    m_cooked = binIo.readUInt4();
    m_value = binIo.readUInt4();

  }


}


}}}
