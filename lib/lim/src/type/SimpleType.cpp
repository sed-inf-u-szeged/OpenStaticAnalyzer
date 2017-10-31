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

namespace type { 
  SimpleType::SimpleType(NodeId _id, Factory *_factory) :
    Base(_id, _factory),
    m_simpleTypeKind(stkBoolean)
  {
  }

  SimpleType::~SimpleType() {
  }

  void SimpleType::clone(const SimpleType& other, bool tryOnVirtualParent) {
    base::Base::clone(other, false);

    m_simpleTypeKind = other.m_simpleTypeKind;
  }

  void SimpleType::prepareDelete(bool tryOnVirtualParent){
    base::Base::prepareDelete(false);
  }

  NodeKind SimpleType::getNodeKind() const {
    return ndkSimpleType;
  }

  SimpleTypeKind SimpleType::getSimpleTypeKind() const {
    return m_simpleTypeKind;
  }

  void SimpleType::setSimpleTypeKind(SimpleTypeKind _simpleTypeKind) {
    m_simpleTypeKind = _simpleTypeKind;
  }

  bool SimpleType::setEdge(EdgeKind edgeKind, NodeId edgeEnd, void* acValue, bool tryOnVirtualParent) {
    if (base::Base::setEdge(edgeKind, edgeEnd, acValue, false)) {
      return true;
    }
    return false;
  }

  bool SimpleType::removeEdge(EdgeKind edgeKind, NodeId edgeEnd, bool tryOnVirtualParent) {
    if (base::Base::removeEdge(edgeKind, edgeEnd, false)) {
      return true;
    }
    return false;
  }

  void SimpleType::accept(Visitor &visitor) const {
    visitor.visit(*this);
  }

  void SimpleType::acceptEnd(Visitor &visitor) const {
    visitor.visitEnd(*this);
  }

  double SimpleType::getSimilarity(const base::Base& base){
    if(base.getNodeKind() == getNodeKind()) {
      const SimpleType& node = dynamic_cast<const SimpleType&>(base);
      double matchAttrs = 0;
      if(node.getSimpleTypeKind() == getSimpleTypeKind()) ++matchAttrs;
      return matchAttrs / (1 / (1 - Common::SimilarityMinimum)) + Common::SimilarityMinimum;
    } else {
      return 0.0;
    }
  }

  void SimpleType::swapStringTable(RefDistributorStrTable& newStrTable, std::map<Key,Key>& oldAndNewStrKeyMap ){
    std::map<Key,Key>::iterator foundKeyId;

  }

  NodeHashType SimpleType::getHash(std::set<NodeId>& travNodes) const {
    if (hashOk) return nodeHashCache;
    common::WriteMsg::write(CMSG_GET_THE_NODE_HASH_OF_NODE_BEGIN,this->getId()); 
    if (travNodes.count(getId())>0) {
      common::WriteMsg::write(CMSG_GET_THE_NODE_HASH_OF_NODE_SKIP);
      return 0;
    }
    travNodes.insert(getId());
    Crc_type resultHash;
    resultHash.process_bytes( "type::SimpleType", strlen("type::SimpleType"));
    common::WriteMsg::write(CMSG_GET_THE_NODE_HASH_OF_NODE_END,resultHash.checksum()); 
    nodeHashCache = resultHash.checksum();
    hashOk = true;
    return nodeHashCache;
  }

  void SimpleType::save(io::BinaryIO &binIo,bool withVirtualBase  /*= true*/) const {
    Base::save(binIo,false);

    binIo.writeUByte1(m_simpleTypeKind);

  }

  void SimpleType::load(io::BinaryIO &binIo, bool withVirtualBase /*= true*/) {
    Base::load(binIo,false);

    m_simpleTypeKind = (SimpleTypeKind)binIo.readUByte1();

  }


}


}}}
