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
  TypeFormerPointer::TypeFormerPointer(NodeId _id, Factory *_factory) :
    TypeFormer(_id, _factory),
    m_pointerKind(ptkPointer)
  {
  }

  TypeFormerPointer::~TypeFormerPointer() {
  }

  void TypeFormerPointer::clone(const TypeFormerPointer& other, bool tryOnVirtualParent) {
    type::TypeFormer::clone(other, false);

    m_pointerKind = other.m_pointerKind;
  }

  void TypeFormerPointer::prepareDelete(bool tryOnVirtualParent){
    type::TypeFormer::prepareDelete(false);
  }

  NodeKind TypeFormerPointer::getNodeKind() const {
    return ndkTypeFormerPointer;
  }

  PointerKind TypeFormerPointer::getPointerKind() const {
    return m_pointerKind;
  }

  void TypeFormerPointer::setPointerKind(PointerKind _pointerKind) {
    m_pointerKind = _pointerKind;
  }

  bool TypeFormerPointer::setEdge(EdgeKind edgeKind, NodeId edgeEnd, void* acValue, bool tryOnVirtualParent) {
    if (type::TypeFormer::setEdge(edgeKind, edgeEnd, acValue, false)) {
      return true;
    }
    return false;
  }

  bool TypeFormerPointer::removeEdge(EdgeKind edgeKind, NodeId edgeEnd, bool tryOnVirtualParent) {
    if (type::TypeFormer::removeEdge(edgeKind, edgeEnd, false)) {
      return true;
    }
    return false;
  }

  void TypeFormerPointer::accept(Visitor &visitor) const {
    visitor.visit(*this);
  }

  void TypeFormerPointer::acceptEnd(Visitor &visitor) const {
    visitor.visitEnd(*this);
  }

  double TypeFormerPointer::getSimilarity(const base::Base& base){
    if(base.getNodeKind() == getNodeKind()) {
      const TypeFormerPointer& node = dynamic_cast<const TypeFormerPointer&>(base);
      double matchAttrs = 0;
      if(node.getPointerKind() == getPointerKind()) ++matchAttrs;
      return matchAttrs / (1 / (1 - Common::SimilarityMinimum)) + Common::SimilarityMinimum;
    } else {
      return 0.0;
    }
  }

  void TypeFormerPointer::swapStringTable(RefDistributorStrTable& newStrTable, std::map<Key,Key>& oldAndNewStrKeyMap ){
    std::map<Key,Key>::iterator foundKeyId;

  }

  NodeHashType TypeFormerPointer::getHash(std::set<NodeId>& travNodes) const {
    if (hashOk) return nodeHashCache;
    common::WriteMsg::write(CMSG_GET_THE_NODE_HASH_OF_NODE_BEGIN,this->getId()); 
    if (travNodes.count(getId())>0) {
      common::WriteMsg::write(CMSG_GET_THE_NODE_HASH_OF_NODE_SKIP);
      return 0;
    }
    travNodes.insert(getId());
    Crc_type resultHash;
    resultHash.process_bytes( "type::TypeFormerPointer", strlen("type::TypeFormerPointer"));
    common::WriteMsg::write(CMSG_GET_THE_NODE_HASH_OF_NODE_END,resultHash.checksum()); 
    nodeHashCache = resultHash.checksum();
    hashOk = true;
    return nodeHashCache;
  }

  void TypeFormerPointer::save(io::BinaryIO &binIo,bool withVirtualBase  /*= true*/) const {
    TypeFormer::save(binIo,false);

    binIo.writeUByte1(m_pointerKind);

  }

  void TypeFormerPointer::load(io::BinaryIO &binIo, bool withVirtualBase /*= true*/) {
    TypeFormer::load(binIo,false);

    m_pointerKind = (PointerKind)binIo.readUByte1();

  }


}


}}}
