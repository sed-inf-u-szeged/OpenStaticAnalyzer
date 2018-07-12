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

namespace type { 
  LowerBoundedWildcardType::LowerBoundedWildcardType(NodeId _id, Factory *_factory) :
    BoundedWildcardType(_id, _factory)
  {
  }

  LowerBoundedWildcardType::~LowerBoundedWildcardType() {
  }

  void LowerBoundedWildcardType::clone(const LowerBoundedWildcardType& other, bool tryOnVirtualParent) {
    type::BoundedWildcardType::clone(other, false);

  }

  void LowerBoundedWildcardType::prepareDelete(bool tryOnVirtualParent){
    type::BoundedWildcardType::prepareDelete(false);
  }

  NodeKind LowerBoundedWildcardType::getNodeKind() const {
    return ndkLowerBoundedWildcardType;
  }

  bool LowerBoundedWildcardType::setEdge(EdgeKind edgeKind, NodeId edgeEnd, bool tryOnVirtualParent) {
    if (type::BoundedWildcardType::setEdge(edgeKind, edgeEnd, false)) {
      return true;
    }
    return false;
  }

  bool LowerBoundedWildcardType::removeEdge(EdgeKind edgeKind, NodeId edgeEnd, bool tryOnVirtualParent) {
    if (type::BoundedWildcardType::removeEdge(edgeKind, edgeEnd, false)) {
      return true;
    }
    return false;
  }

  void LowerBoundedWildcardType::accept(Visitor &visitor) const {
    visitor.visit(*this);
  }

  void LowerBoundedWildcardType::acceptEnd(Visitor &visitor) const {
    visitor.visitEnd(*this);
  }

  double LowerBoundedWildcardType::getSimilarity(const base::Base& base){
    if(base.getNodeKind() == getNodeKind()) {
      return 1.0;
    } else {
      return 0.0;
    }
  }

  void LowerBoundedWildcardType::swapStringTable(RefDistributorStrTable& newStrTable, std::map<Key,Key>& oldAndNewStrKeyMap ){
    std::map<Key,Key>::iterator foundKeyId;

  }

  NodeHashType LowerBoundedWildcardType::getHash(std::set<NodeId>& travNodes) const {
    if (hashOk) return nodeHashCache;
    common::WriteMsg::write(CMSG_GET_THE_NODE_HASH_OF_NODE_BEGIN,this->getId()); 
    if (travNodes.count(getId())>0) {
      common::WriteMsg::write(CMSG_GET_THE_NODE_HASH_OF_NODE_SKIP);
      return 0;
    }
    travNodes.insert(getId());
    Crc_type resultHash;
    resultHash.process_bytes( "type::LowerBoundedWildcardType", strlen("type::LowerBoundedWildcardType"));
    common::WriteMsg::write(CMSG_GET_THE_NODE_HASH_OF_NODE_END,resultHash.checksum()); 
    nodeHashCache = resultHash.checksum();
    hashOk = true;
    return nodeHashCache;
  }

  void LowerBoundedWildcardType::sort(bool withVirtualBase /* = true */) {
    BoundedWildcardType::sort(false);
  }

  void LowerBoundedWildcardType::save(io::BinaryIO &binIo,bool withVirtualBase  /*= true*/) const {
    BoundedWildcardType::save(binIo,false);

  }

  void LowerBoundedWildcardType::load(io::BinaryIO &binIo, bool withVirtualBase /*= true*/) {
    BoundedWildcardType::load(binIo,false);

  }


}


}}}
