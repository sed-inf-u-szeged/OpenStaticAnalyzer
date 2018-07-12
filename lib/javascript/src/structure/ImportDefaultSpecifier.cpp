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

namespace structure { 
  ImportDefaultSpecifier::ImportDefaultSpecifier(NodeId _id, Factory *_factory) :
    ImpSpecifier(_id, _factory)
  {
  }

  ImportDefaultSpecifier::~ImportDefaultSpecifier() {
  }

  void ImportDefaultSpecifier::prepareDelete(bool tryOnVirtualParent){
    structure::ImpSpecifier::prepareDelete(false);
  }

  NodeKind ImportDefaultSpecifier::getNodeKind() const {
    return ndkImportDefaultSpecifier;
  }

  bool ImportDefaultSpecifier::setEdge(EdgeKind edgeKind, NodeId edgeEnd, bool tryOnVirtualParent) {
    if (structure::ImpSpecifier::setEdge(edgeKind, edgeEnd, false)) {
      return true;
    }
    return false;
  }

  bool ImportDefaultSpecifier::removeEdge(EdgeKind edgeKind, NodeId edgeEnd, bool tryOnVirtualParent) {
    if (structure::ImpSpecifier::removeEdge(edgeKind, edgeEnd, false)) {
      return true;
    }
    return false;
  }

  void ImportDefaultSpecifier::accept(Visitor &visitor) const {
    visitor.visit(*this);
  }

  void ImportDefaultSpecifier::acceptEnd(Visitor &visitor) const {
    visitor.visitEnd(*this);
  }

  double ImportDefaultSpecifier::getSimilarity(const base::Base& base){
    if(base.getNodeKind() == getNodeKind()) {
      return 1.0;
    } else {
      return 0.0;
    }
  }

  void ImportDefaultSpecifier::swapStringTable(RefDistributorStrTable& newStrTable, std::map<Key,Key>& oldAndNewStrKeyMap ){
    std::map<Key,Key>::iterator foundKeyId;

  }

  NodeHashType ImportDefaultSpecifier::getHash(std::set<NodeId>& travNodes) const {
    if (hashOk) return nodeHashCache;
    common::WriteMsg::write(CMSG_GET_THE_NODE_HASH_OF_NODE_BEGIN,this->getId()); 
    if (travNodes.count(getId())>0) {
      common::WriteMsg::write(CMSG_GET_THE_NODE_HASH_OF_NODE_SKIP);
      return 0;
    }
    travNodes.insert(getId());
    Crc_type resultHash;
    resultHash.process_bytes( "structure::ImportDefaultSpecifier", strlen("structure::ImportDefaultSpecifier"));
    common::WriteMsg::write(CMSG_GET_THE_NODE_HASH_OF_NODE_END,resultHash.checksum()); 
    nodeHashCache = resultHash.checksum();
    hashOk = true;
    return nodeHashCache;
  }

  void ImportDefaultSpecifier::save(io::BinaryIO &binIo,bool withVirtualBase  /*= true*/) const {
    ImpSpecifier::save(binIo,false);

  }

  void ImportDefaultSpecifier::load(io::BinaryIO &binIo, bool withVirtualBase /*= true*/) {
    ImpSpecifier::load(binIo,false);

  }


}


}}}
