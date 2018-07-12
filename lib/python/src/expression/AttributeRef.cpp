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
  AttributeRef::AttributeRef(NodeId _id, Factory *_factory) :
    Binary(_id, _factory)
  {
  }

  AttributeRef::~AttributeRef() {
  }

  void AttributeRef::prepareDelete(bool tryOnVirtualParent){
    expression::Binary::prepareDelete(false);
  }

  NodeKind AttributeRef::getNodeKind() const {
    return ndkAttributeRef;
  }

  bool AttributeRef::setEdge(EdgeKind edgeKind, NodeId edgeEnd, bool tryOnVirtualParent) {
    if (expression::Binary::setEdge(edgeKind, edgeEnd, false)) {
      return true;
    }
    return false;
  }

  bool AttributeRef::removeEdge(EdgeKind edgeKind, NodeId edgeEnd, bool tryOnVirtualParent) {
    if (expression::Binary::removeEdge(edgeKind, edgeEnd, false)) {
      return true;
    }
    return false;
  }

  void AttributeRef::accept(Visitor &visitor) const {
    visitor.visit(*this);
  }

  void AttributeRef::acceptEnd(Visitor &visitor) const {
    visitor.visitEnd(*this);
  }

  double AttributeRef::getSimilarity(const base::Base& base){
    if(base.getNodeKind() == getNodeKind()) {
      return 1.0;
    } else {
      return 0.0;
    }
  }

  void AttributeRef::swapStringTable(RefDistributorStrTable& newStrTable, std::map<Key,Key>& oldAndNewStrKeyMap ){
    std::map<Key,Key>::iterator foundKeyId;

  }

  NodeHashType AttributeRef::getHash(std::set<NodeId>& travNodes) const {
    if (hashOk) return nodeHashCache;
    common::WriteMsg::write(CMSG_GET_THE_NODE_HASH_OF_NODE_BEGIN,this->getId()); 
    if (travNodes.count(getId())>0) {
      common::WriteMsg::write(CMSG_GET_THE_NODE_HASH_OF_NODE_SKIP);
      return 0;
    }
    travNodes.insert(getId());
    Crc_type resultHash;
    resultHash.process_bytes( "expression::AttributeRef", strlen("expression::AttributeRef"));
    common::WriteMsg::write(CMSG_GET_THE_NODE_HASH_OF_NODE_END,resultHash.checksum()); 
    nodeHashCache = resultHash.checksum();
    hashOk = true;
    return nodeHashCache;
  }

  void AttributeRef::save(io::BinaryIO &binIo,bool withVirtualBase  /*= true*/) const {
    Binary::save(binIo,false);

  }

  void AttributeRef::load(io::BinaryIO &binIo, bool withVirtualBase /*= true*/) {
    Binary::load(binIo,false);

  }


}


}}}
