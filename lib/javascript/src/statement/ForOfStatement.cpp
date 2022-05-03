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

namespace statement { 
  ForOfStatement::ForOfStatement(NodeId _id, Factory *_factory) :
         Positioned(_id, _factory),
    ForInStatement(_id, _factory),
    m_await(false)
  {
  }

  ForOfStatement::~ForOfStatement() {
  }

  void ForOfStatement::prepareDelete(bool tryOnVirtualParent){
    if (tryOnVirtualParent) {
      base::Positioned::prepareDelete(false);
    }
    statement::ForInStatement::prepareDelete(false);
  }

  NodeKind ForOfStatement::getNodeKind() const {
    return ndkForOfStatement;
  }

  bool ForOfStatement::getAwait() const {
    return m_await;
  }

  void ForOfStatement::setAwait(bool _await) {
    m_await = _await;
  }

  bool ForOfStatement::setEdge(EdgeKind edgeKind, NodeId edgeEnd, bool tryOnVirtualParent) {
    if (tryOnVirtualParent) {
      if (base::Positioned::setEdge(edgeKind, edgeEnd, false)) {
        return true;
      }
    }
    if (statement::ForInStatement::setEdge(edgeKind, edgeEnd, false)) {
      return true;
    }
    return false;
  }

  bool ForOfStatement::removeEdge(EdgeKind edgeKind, NodeId edgeEnd, bool tryOnVirtualParent) {
    if (tryOnVirtualParent) {
      if (base::Positioned::removeEdge(edgeKind, edgeEnd, false)) {
        return true;
      }
    }
    if (statement::ForInStatement::removeEdge(edgeKind, edgeEnd, false)) {
      return true;
    }
    return false;
  }

  void ForOfStatement::accept(Visitor &visitor) const {
    visitor.visit(*this);
  }

  void ForOfStatement::acceptEnd(Visitor &visitor) const {
    visitor.visitEnd(*this);
  }

  double ForOfStatement::getSimilarity(const base::Base& base){
    if(base.getNodeKind() == getNodeKind()) {
      const ForOfStatement& node = dynamic_cast<const ForOfStatement&>(base);
      double matchAttrs = 0;
      if(node.getAwait() == getAwait()) ++matchAttrs;
      return matchAttrs / (1 / (1 - Common::SimilarityMinimum)) + Common::SimilarityMinimum;
    } else {
      return 0.0;
    }
  }

  void ForOfStatement::swapStringTable(RefDistributorStrTable& newStrTable, std::map<Key,Key>& oldAndNewStrKeyMap ){
    std::map<Key,Key>::iterator foundKeyId;

  }

  NodeHashType ForOfStatement::getHash(std::set<NodeId>& travNodes) const {
    if (hashOk) return nodeHashCache;
    common::WriteMsg::write(CMSG_GET_THE_NODE_HASH_OF_NODE_BEGIN,this->getId()); 
    if (travNodes.count(getId())>0) {
      common::WriteMsg::write(CMSG_GET_THE_NODE_HASH_OF_NODE_SKIP);
      return 0;
    }
    travNodes.insert(getId());
    Crc_type resultHash;
    resultHash.process_bytes( "statement::ForOfStatement", strlen("statement::ForOfStatement"));
    common::WriteMsg::write(CMSG_GET_THE_NODE_HASH_OF_NODE_END,resultHash.checksum()); 
    nodeHashCache = resultHash.checksum();
    hashOk = true;
    return nodeHashCache;
  }

  void ForOfStatement::save(io::BinaryIO &binIo,bool withVirtualBase  /*= true*/) const {
    if (withVirtualBase)
      Positioned::save(binIo,false);

    ForInStatement::save(binIo,false);

    unsigned char boolValues = 0;
    boolValues <<= 1;
    if (m_await) 
      boolValues |= 1;
    binIo.writeUByte1(boolValues);

  }

  void ForOfStatement::load(io::BinaryIO &binIo, bool withVirtualBase /*= true*/) {
    if (withVirtualBase)
      Positioned::load(binIo, false);

    ForInStatement::load(binIo,false);

    unsigned char boolValues = binIo.readUByte1();
    m_await = boolValues & 1;
    boolValues >>= 1;

  }


}


}}}
