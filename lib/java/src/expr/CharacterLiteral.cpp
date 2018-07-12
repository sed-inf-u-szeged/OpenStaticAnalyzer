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

#include "java/inc/java.h"
#include "java/inc/Common.h"
#include "common/inc/WriteMessage.h"

#include "java/inc/messages.h"
#include <algorithm>
#include <string.h>
#include "common/inc/math/common.h"
#include <sstream>


namespace columbus { namespace java { namespace asg {

typedef boost::crc_32_type  Crc_type;

namespace expr { 
  CharacterLiteral::CharacterLiteral(NodeId _id, Factory *_factory) :
         Base(_id, _factory),
         Commentable(_id, _factory),
    Literal(_id, _factory),
    m_charValue(0),
    m_formatString(0)
  {
  }

  CharacterLiteral::~CharacterLiteral() {
  }

  void CharacterLiteral::clone(const CharacterLiteral& other, bool tryOnVirtualParent) {
    if (tryOnVirtualParent) {
      base::Base::clone(other, false);
    }
    if (tryOnVirtualParent) {
      base::Commentable::clone(other, false);
    }
    expr::Literal::clone(other, false);

    m_charValue = other.m_charValue;
    m_formatString = other.m_formatString;
  }

  void CharacterLiteral::prepareDelete(bool tryOnVirtualParent){
    if (tryOnVirtualParent) {
      base::Base::prepareDelete(false);
    }
    if (tryOnVirtualParent) {
      base::Commentable::prepareDelete(false);
    }
    expr::Literal::prepareDelete(false);
  }

  NodeKind CharacterLiteral::getNodeKind() const {
    return ndkCharacterLiteral;
  }

  wchar_t CharacterLiteral::getCharValue() const {
    return m_charValue;
  }

  Key CharacterLiteral::getFormatStringKey() const {
    return m_formatString;
  }

  const std::string& CharacterLiteral::getFormatString() const {
    return factory->getStringTable().get(m_formatString);
  }

  void CharacterLiteral::setCharValue(wchar_t _charValue) {
    m_charValue = _charValue;
  }

  void CharacterLiteral::setFormatStringKey(Key _formatString) {
    m_formatString = _formatString;
  }

  void CharacterLiteral::setFormatString(const std::string& _formatString) {
    m_formatString = factory->getStringTable().set(_formatString);
  }

  bool CharacterLiteral::setEdge(EdgeKind edgeKind, NodeId edgeEnd, bool tryOnVirtualParent) {
    if (tryOnVirtualParent) {
      if (base::Base::setEdge(edgeKind, edgeEnd, false)) {
        return true;
      }
    }
    if (tryOnVirtualParent) {
      if (base::Commentable::setEdge(edgeKind, edgeEnd, false)) {
        return true;
      }
    }
    if (expr::Literal::setEdge(edgeKind, edgeEnd, false)) {
      return true;
    }
    return false;
  }

  bool CharacterLiteral::removeEdge(EdgeKind edgeKind, NodeId edgeEnd, bool tryOnVirtualParent) {
    if (tryOnVirtualParent) {
      if (base::Base::removeEdge(edgeKind, edgeEnd, false)) {
        return true;
      }
    }
    if (tryOnVirtualParent) {
      if (base::Commentable::removeEdge(edgeKind, edgeEnd, false)) {
        return true;
      }
    }
    if (expr::Literal::removeEdge(edgeKind, edgeEnd, false)) {
      return true;
    }
    return false;
  }

  void CharacterLiteral::accept(Visitor &visitor) const {
    visitor.visit(*this);
  }

  void CharacterLiteral::acceptEnd(Visitor &visitor) const {
    visitor.visitEnd(*this);
  }

  double CharacterLiteral::getSimilarity(const base::Base& base){
    if(base.getNodeKind() == getNodeKind()) {
      const CharacterLiteral& node = dynamic_cast<const CharacterLiteral&>(base);
      double matchAttrs = 0;
      if(node.getIsCompilerGenerated() == getIsCompilerGenerated()) ++matchAttrs;
      if(node.getIsToolGenerated() == getIsToolGenerated()) ++matchAttrs;
      if(node.getCharValue() == getCharValue()) ++matchAttrs;
      std::string str1, str2;
      size_t strMax;
      double strSim;
      str1 = getFormatString();
      str2 = node.getFormatString();
      strMax = std::max(str1.size(), str2.size());
      strSim = 1 - ((double)common::math::editDistance(str1, str2) / (strMax > 0 ? strMax : 1));
      if (strSim < Common::SimilarityMinForStrings)
        return 0.0;
      matchAttrs += strSim;
      return matchAttrs / (4 / (1 - Common::SimilarityMinimum)) + Common::SimilarityMinimum;
    } else {
      return 0.0;
    }
  }

  void CharacterLiteral::swapStringTable(RefDistributorStrTable& newStrTable, std::map<Key,Key>& oldAndNewStrKeyMap ){
    std::map<Key,Key>::iterator foundKeyId;

    foundKeyId = oldAndNewStrKeyMap.find(m_formatString);
    if (foundKeyId != oldAndNewStrKeyMap.end()) {
      m_formatString = foundKeyId->second;
    } else {
      Key oldkey = m_formatString;
      m_formatString = newStrTable.set(factory->getStringTable().get(m_formatString));
      oldAndNewStrKeyMap.insert(std::pair<Key,Key>(oldkey,m_formatString));    }

  }

  NodeHashType CharacterLiteral::getHash(std::set<NodeId>& travNodes) const {
    if (hashOk) return nodeHashCache;
    common::WriteMsg::write(CMSG_GET_THE_NODE_HASH_OF_NODE_BEGIN,this->getId()); 
    if (travNodes.count(getId())>0) {
      common::WriteMsg::write(CMSG_GET_THE_NODE_HASH_OF_NODE_SKIP);
      return 0;
    }
    travNodes.insert(getId());
    Crc_type resultHash;
    resultHash.process_bytes( "expr::CharacterLiteral", strlen("expr::CharacterLiteral"));
    common::WriteMsg::write(CMSG_GET_THE_NODE_HASH_OF_NODE_END,resultHash.checksum()); 
    nodeHashCache = resultHash.checksum();
    hashOk = true;
    return nodeHashCache;
  }

  void CharacterLiteral::sort(bool withVirtualBase /* = true */) {
    if (withVirtualBase)
      Base::sort(false);
    if (withVirtualBase)
      Commentable::sort(false);
    Literal::sort(false);
  }

  void CharacterLiteral::save(io::BinaryIO &binIo,bool withVirtualBase  /*= true*/) const {
    if (withVirtualBase)
      Base::save(binIo,false);

    if (withVirtualBase)
      Commentable::save(binIo,false);

    Literal::save(binIo,false);

    binIo.writeUShort2(m_charValue);
    factory->getStringTable().setType(m_formatString, StrTable::strToSave);
    binIo.writeUInt4(m_formatString);

  }

  void CharacterLiteral::load(io::BinaryIO &binIo, bool withVirtualBase /*= true*/) {
    if (withVirtualBase)
      Base::load(binIo, false);

    if (withVirtualBase)
      Commentable::load(binIo, false);

    Literal::load(binIo,false);

    m_charValue = binIo.readUShort2();
    m_formatString = binIo.readUInt4();

  }


}


}}}
