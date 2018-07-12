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

#include "genealogy/inc/genealogy.h"
#include "genealogy/inc/Common.h"
#include "common/inc/WriteMessage.h"

#include "genealogy/inc/messages.h"
#include <algorithm>
#include <string.h>
#include "common/inc/math/common.h"


namespace columbus { namespace genealogy { 

typedef boost::crc_32_type  Crc_type;

  Base::Base(NodeId _id, Factory *_factory) :

    hashOk(false),
    m_id(_id),
    nodeHashCache(0),
    parentEdgeKind((EdgeKind)0),
    parent(0),
    factory(_factory)
  {
  }

  Base::~Base() {
  }

  void Base::prepareDelete(bool tryOnVirtualParent){
  }

  void Base::setParentEdge(const Base *childNode,EdgeKind _parentEdgeKind) const {
    if (childNode) {
      if (childNode->parent != 0) {
        common::WriteMsg::write(CMSG_HAS_ALREADY_PARENT_THE_PARENT_WAS,childNode->getId(),Common::toString(childNode->getNodeKind()).c_str(),childNode->parent,Common::toString(childNode->getParent()->getNodeKind()).c_str() ,this->getId(),Common::toString(this->getNodeKind()).c_str()); 
      }
      childNode->parent = m_id;
      childNode->parentEdgeKind = _parentEdgeKind;
    }
  }

  void Base::removeParentEdge(NodeId childNode) const {
    factory->getRef(childNode).parent = 0;
  }

  void Base::removeParentEdge(Base *childNode) const {
    childNode->parent = 0;
  }

  Base* Base::getParent() const {
    if (parent == 0)
      return NULL;
    return factory->getPointer(parent);
  }

  Factory& Base::getFactory() const {
    return *factory;
  }
  unsigned Base::getId() const {
    return m_id;
  }

  void Base::setId(unsigned _id) {
    m_id = _id;
  }

  bool Base::setEdge(EdgeKind edgeKind, Base* edgeEnd) {
    return setEdge(edgeKind, edgeEnd->getId(), true);
  }

  bool Base::setEdge(EdgeKind edgeKind, NodeId edgeEnd, bool tryOnVirtualParent) {
    return false;
  }

  bool Base::removeEdge(EdgeKind edgeKind, Base* edgeEnd) {
    return removeEdge(edgeKind, edgeEnd->getId(), true);
  }

  bool Base::removeEdge(EdgeKind edgeKind, NodeId edgeEnd, bool tryOnVirtualParent) {
    return false;
  }

  void Base::accept(Visitor &visitor) const {
  }

  void Base::acceptEnd(Visitor &visitor) const {
  }

  double Base::getSimilarity(const Base& base){
    if(base.getNodeKind() == getNodeKind()) {
      const Base& node = dynamic_cast<const Base&>(base);
      double matchAttrs = 0;
      if(node.getId() == getId()) ++matchAttrs;
      return matchAttrs / (1 / (1 - Common::SimilarityMinimum)) + Common::SimilarityMinimum;
    } else {
      return 0.0;
    }
  }

  void Base::swapStringTable(RefDistributorStrTable& newStrTable, std::map<Key,Key>& oldAndNewStrKeyMap ){
    std::map<Key,Key>::iterator foundKeyId;

  }

  NodeHashType Base::getHash(std::set<NodeId>& travNodes) const {
    if (hashOk) return nodeHashCache;
    common::WriteMsg::write(CMSG_GET_THE_NODE_HASH_OF_NODE_BEGIN,this->getId()); 
    if (travNodes.count(getId())>0) {
      common::WriteMsg::write(CMSG_GET_THE_NODE_HASH_OF_NODE_SKIP);
      return 0;
    }
    travNodes.insert(getId());
    Crc_type resultHash;
    resultHash.process_bytes( "Base", strlen("Base"));
    common::WriteMsg::write(CMSG_GET_THE_NODE_HASH_OF_NODE_END,resultHash.checksum()); 
    nodeHashCache = resultHash.checksum();
    hashOk = true;
    return nodeHashCache;
  }

  void Base::save(io::BinaryIO &binIo,bool withVirtualBase  /*= true*/) const {
    binIo.writeUInt4(m_id);
    binIo.writeUShort2(getNodeKind());

  }

  void Base::load(io::BinaryIO &binIo, bool withVirtualBase /*= true*/) {

  }



}}
