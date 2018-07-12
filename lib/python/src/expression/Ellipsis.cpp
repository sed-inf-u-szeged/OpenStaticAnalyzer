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
  Ellipsis::Ellipsis(NodeId _id, Factory *_factory) :
    Slicing(_id, _factory)
  {
  }

  Ellipsis::~Ellipsis() {
  }

  void Ellipsis::prepareDelete(bool tryOnVirtualParent){
    expression::Slicing::prepareDelete(false);
  }

  NodeKind Ellipsis::getNodeKind() const {
    return ndkEllipsis;
  }

  bool Ellipsis::setEdge(EdgeKind edgeKind, NodeId edgeEnd, bool tryOnVirtualParent) {
    if (expression::Slicing::setEdge(edgeKind, edgeEnd, false)) {
      return true;
    }
    return false;
  }

  bool Ellipsis::removeEdge(EdgeKind edgeKind, NodeId edgeEnd, bool tryOnVirtualParent) {
    if (expression::Slicing::removeEdge(edgeKind, edgeEnd, false)) {
      return true;
    }
    return false;
  }

  void Ellipsis::accept(Visitor &visitor) const {
    visitor.visit(*this);
  }

  void Ellipsis::acceptEnd(Visitor &visitor) const {
    visitor.visitEnd(*this);
  }

  double Ellipsis::getSimilarity(const base::Base& base){
    if(base.getNodeKind() == getNodeKind()) {
      return 1.0;
    } else {
      return 0.0;
    }
  }

  void Ellipsis::swapStringTable(RefDistributorStrTable& newStrTable, std::map<Key,Key>& oldAndNewStrKeyMap ){
    std::map<Key,Key>::iterator foundKeyId;

  }

  NodeHashType Ellipsis::getHash(std::set<NodeId>& travNodes) const {
    if (hashOk) return nodeHashCache;
    common::WriteMsg::write(CMSG_GET_THE_NODE_HASH_OF_NODE_BEGIN,this->getId()); 
    if (travNodes.count(getId())>0) {
      common::WriteMsg::write(CMSG_GET_THE_NODE_HASH_OF_NODE_SKIP);
      return 0;
    }
    travNodes.insert(getId());
    Crc_type resultHash;
    resultHash.process_bytes( "expression::Ellipsis", strlen("expression::Ellipsis"));
    common::WriteMsg::write(CMSG_GET_THE_NODE_HASH_OF_NODE_END,resultHash.checksum()); 
    nodeHashCache = resultHash.checksum();
    hashOk = true;
    return nodeHashCache;
  }

  void Ellipsis::save(io::BinaryIO &binIo,bool withVirtualBase  /*= true*/) const {
    Slicing::save(binIo,false);

  }

  void Ellipsis::load(io::BinaryIO &binIo, bool withVirtualBase /*= true*/) {
    Slicing::load(binIo,false);

  }


}


}}}
