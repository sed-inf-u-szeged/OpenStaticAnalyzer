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
  BinaryLogical::BinaryLogical(NodeId _id, Factory *_factory) :
    Binary(_id, _factory),
    m_kind(blkEq)
  {
  }

  BinaryLogical::~BinaryLogical() {
  }

  void BinaryLogical::prepareDelete(bool tryOnVirtualParent){
    expression::Binary::prepareDelete(false);
  }

  NodeKind BinaryLogical::getNodeKind() const {
    return ndkBinaryLogical;
  }

  BinaryLogicalKind BinaryLogical::getKind() const {
    return m_kind;
  }

  void BinaryLogical::setKind(BinaryLogicalKind _kind) {
    m_kind = _kind;
  }

  bool BinaryLogical::setEdge(EdgeKind edgeKind, NodeId edgeEnd, bool tryOnVirtualParent) {
    if (expression::Binary::setEdge(edgeKind, edgeEnd, false)) {
      return true;
    }
    return false;
  }

  bool BinaryLogical::removeEdge(EdgeKind edgeKind, NodeId edgeEnd, bool tryOnVirtualParent) {
    if (expression::Binary::removeEdge(edgeKind, edgeEnd, false)) {
      return true;
    }
    return false;
  }

  void BinaryLogical::accept(Visitor &visitor) const {
    visitor.visit(*this);
  }

  void BinaryLogical::acceptEnd(Visitor &visitor) const {
    visitor.visitEnd(*this);
  }

  double BinaryLogical::getSimilarity(const base::Base& base){
    if(base.getNodeKind() == getNodeKind()) {
      const BinaryLogical& node = dynamic_cast<const BinaryLogical&>(base);
      double matchAttrs = 0;
      if(node.getKind() == getKind()) ++matchAttrs;
      return matchAttrs / (1 / (1 - Common::SimilarityMinimum)) + Common::SimilarityMinimum;
    } else {
      return 0.0;
    }
  }

  void BinaryLogical::swapStringTable(RefDistributorStrTable& newStrTable, std::map<Key,Key>& oldAndNewStrKeyMap ){
    std::map<Key,Key>::iterator foundKeyId;

  }

  NodeHashType BinaryLogical::getHash(std::set<NodeId>& travNodes) const {
    if (hashOk) return nodeHashCache;
    common::WriteMsg::write(CMSG_GET_THE_NODE_HASH_OF_NODE_BEGIN,this->getId()); 
    if (travNodes.count(getId())>0) {
      common::WriteMsg::write(CMSG_GET_THE_NODE_HASH_OF_NODE_SKIP);
      return 0;
    }
    travNodes.insert(getId());
    Crc_type resultHash;
    resultHash.process_bytes( "expression::BinaryLogical", strlen("expression::BinaryLogical"));
    common::WriteMsg::write(CMSG_GET_THE_NODE_HASH_OF_NODE_END,resultHash.checksum()); 
    nodeHashCache = resultHash.checksum();
    hashOk = true;
    return nodeHashCache;
  }

  void BinaryLogical::save(io::BinaryIO &binIo,bool withVirtualBase  /*= true*/) const {
    Binary::save(binIo,false);

    binIo.writeUByte1(m_kind);

  }

  void BinaryLogical::load(io::BinaryIO &binIo, bool withVirtualBase /*= true*/) {
    Binary::load(binIo,false);

    m_kind = (BinaryLogicalKind)binIo.readUByte1();

  }


}


}}}
