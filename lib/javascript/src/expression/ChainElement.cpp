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
  ChainElement::ChainElement(NodeId _id, Factory *_factory) :
    Positioned(_id, _factory),
    m_optional(false)
  {
  }

  ChainElement::~ChainElement() {
  }

  void ChainElement::prepareDelete(bool tryOnVirtualParent){
    if (tryOnVirtualParent) {
      base::Positioned::prepareDelete(false);
    }
  }

  NodeKind ChainElement::getNodeKind() const {
    return ndkChainElement;
  }

  bool ChainElement::getOptional() const {
    return m_optional;
  }

  void ChainElement::setOptional(bool _optional) {
    m_optional = _optional;
  }

  bool ChainElement::setEdge(EdgeKind edgeKind, NodeId edgeEnd, bool tryOnVirtualParent) {
    if (tryOnVirtualParent) {
      if (base::Positioned::setEdge(edgeKind, edgeEnd, false)) {
        return true;
      }
    }
    return false;
  }

  bool ChainElement::removeEdge(EdgeKind edgeKind, NodeId edgeEnd, bool tryOnVirtualParent) {
    if (tryOnVirtualParent) {
      if (base::Positioned::removeEdge(edgeKind, edgeEnd, false)) {
        return true;
      }
    }
    return false;
  }

  void ChainElement::accept(Visitor &visitor) const {
    visitor.visit(*this);
  }

  void ChainElement::acceptEnd(Visitor &visitor) const {
    visitor.visitEnd(*this);
  }

  double ChainElement::getSimilarity(const base::Base& base){
    if(base.getNodeKind() == getNodeKind()) {
      const ChainElement& node = dynamic_cast<const ChainElement&>(base);
      double matchAttrs = 0;
      if(node.getOptional() == getOptional()) ++matchAttrs;
      return matchAttrs / (1 / (1 - Common::SimilarityMinimum)) + Common::SimilarityMinimum;
    } else {
      return 0.0;
    }
  }

  void ChainElement::swapStringTable(RefDistributorStrTable& newStrTable, std::map<Key,Key>& oldAndNewStrKeyMap ){
    std::map<Key,Key>::iterator foundKeyId;

  }

  NodeHashType ChainElement::getHash(std::set<NodeId>& travNodes) const {
    if (hashOk) return nodeHashCache;
    common::WriteMsg::write(CMSG_GET_THE_NODE_HASH_OF_NODE_BEGIN,this->getId()); 
    if (travNodes.count(getId())>0) {
      common::WriteMsg::write(CMSG_GET_THE_NODE_HASH_OF_NODE_SKIP);
      return 0;
    }
    travNodes.insert(getId());
    Crc_type resultHash;
    resultHash.process_bytes( "expression::ChainElement", strlen("expression::ChainElement"));
    common::WriteMsg::write(CMSG_GET_THE_NODE_HASH_OF_NODE_END,resultHash.checksum()); 
    nodeHashCache = resultHash.checksum();
    hashOk = true;
    return nodeHashCache;
  }

  void ChainElement::save(io::BinaryIO &binIo,bool withVirtualBase  /*= true*/) const {
    if (withVirtualBase)
      Positioned::save(binIo,false);

    unsigned char boolValues = 0;
    boolValues <<= 1;
    if (m_optional) 
      boolValues |= 1;
    binIo.writeUByte1(boolValues);

  }

  void ChainElement::load(io::BinaryIO &binIo, bool withVirtualBase /*= true*/) {
    if (withVirtualBase)
      Positioned::load(binIo,false);

    unsigned char boolValues = binIo.readUByte1();
    m_optional = boolValues & 1;
    boolValues >>= 1;

  }


}


}}}
