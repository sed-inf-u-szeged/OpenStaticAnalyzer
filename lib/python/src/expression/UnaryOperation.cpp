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
  UnaryOperation::UnaryOperation(NodeId _id, Factory *_factory) :
    Unary(_id, _factory),
    m_kind(unkInvert)
  {
  }

  UnaryOperation::~UnaryOperation() {
  }

  void UnaryOperation::prepareDelete(bool tryOnVirtualParent){
    expression::Unary::prepareDelete(false);
  }

  NodeKind UnaryOperation::getNodeKind() const {
    return ndkUnaryOperation;
  }

  UnaryKind UnaryOperation::getKind() const {
    return m_kind;
  }

  void UnaryOperation::setKind(UnaryKind _kind) {
    m_kind = _kind;
  }

  bool UnaryOperation::setEdge(EdgeKind edgeKind, NodeId edgeEnd, bool tryOnVirtualParent) {
    if (expression::Unary::setEdge(edgeKind, edgeEnd, false)) {
      return true;
    }
    return false;
  }

  bool UnaryOperation::removeEdge(EdgeKind edgeKind, NodeId edgeEnd, bool tryOnVirtualParent) {
    if (expression::Unary::removeEdge(edgeKind, edgeEnd, false)) {
      return true;
    }
    return false;
  }

  void UnaryOperation::accept(Visitor &visitor) const {
    visitor.visit(*this);
  }

  void UnaryOperation::acceptEnd(Visitor &visitor) const {
    visitor.visitEnd(*this);
  }

  double UnaryOperation::getSimilarity(const base::Base& base){
    if(base.getNodeKind() == getNodeKind()) {
      const UnaryOperation& node = dynamic_cast<const UnaryOperation&>(base);
      double matchAttrs = 0;
      if(node.getKind() == getKind()) ++matchAttrs;
      return matchAttrs / (1 / (1 - Common::SimilarityMinimum)) + Common::SimilarityMinimum;
    } else {
      return 0.0;
    }
  }

  void UnaryOperation::swapStringTable(RefDistributorStrTable& newStrTable, std::map<Key,Key>& oldAndNewStrKeyMap ){
    std::map<Key,Key>::iterator foundKeyId;

  }

  NodeHashType UnaryOperation::getHash(std::set<NodeId>& travNodes) const {
    if (hashOk) return nodeHashCache;
    common::WriteMsg::write(CMSG_GET_THE_NODE_HASH_OF_NODE_BEGIN,this->getId()); 
    if (travNodes.count(getId())>0) {
      common::WriteMsg::write(CMSG_GET_THE_NODE_HASH_OF_NODE_SKIP);
      return 0;
    }
    travNodes.insert(getId());
    Crc_type resultHash;
    resultHash.process_bytes( "expression::UnaryOperation", strlen("expression::UnaryOperation"));
    common::WriteMsg::write(CMSG_GET_THE_NODE_HASH_OF_NODE_END,resultHash.checksum()); 
    nodeHashCache = resultHash.checksum();
    hashOk = true;
    return nodeHashCache;
  }

  void UnaryOperation::save(io::BinaryIO &binIo,bool withVirtualBase  /*= true*/) const {
    Unary::save(binIo,false);

    binIo.writeUByte1(m_kind);

  }

  void UnaryOperation::load(io::BinaryIO &binIo, bool withVirtualBase /*= true*/) {
    Unary::load(binIo,false);

    m_kind = (UnaryKind)binIo.readUByte1();

  }


}


}}}
