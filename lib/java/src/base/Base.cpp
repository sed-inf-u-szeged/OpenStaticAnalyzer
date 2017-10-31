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

namespace base { 
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

  void Base::clone(const Base& other, bool tryOnVirtualParent) {
    if (this->factory != other.factory)
      throw JavaException(COLUMBUS_LOCATION, CMSG_EX_THE_FACTORY_OF_NODES_DOES_NOT_MATCH);

    parent = other.parent;
    parentEdgeKind = other.parentEdgeKind;
    m_id = other.m_id;
  }

  void Base::prepareDelete(bool tryOnVirtualParent){
  }

  void Base::setParentEdge(const base::Base *childNode,EdgeKind _parentEdgeKind) const {
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

  void Base::removeParentEdge(base::Base *childNode) const {
    childNode->parent = 0;
  }

  base::Base* Base::getParent() const {
    if (parent == 0)
      return NULL;
    return factory->getPointer(parent);
  }

  Factory& Base::getFactory() const {
    return *factory;
  }
  NodeId Base::getId() const {
    return m_id;
  }

  void Base::setId(NodeId _id) {
    m_id = _id;
  }

  bool Base::setEdge(EdgeKind edgeKind, base::Base* edgeEnd) {
    return setEdge(edgeKind, edgeEnd->getId(), true);
  }

  bool Base::setEdge(EdgeKind edgeKind, NodeId edgeEnd, bool tryOnVirtualParent) {
    return false;
  }

  bool Base::removeEdge(EdgeKind edgeKind, base::Base* edgeEnd) {
    return removeEdge(edgeKind, edgeEnd->getId(), true);
  }

  bool Base::removeEdge(EdgeKind edgeKind, NodeId edgeEnd, bool tryOnVirtualParent) {
    return false;
  }

  void Base::accept(Visitor &visitor) const {
  }

  void Base::acceptEnd(Visitor &visitor) const {
  }

  double Base::getSimilarity(const base::Base& base){
    if(base.getNodeKind() == getNodeKind()) {
      return 1.0;
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
    resultHash.process_bytes( "base::Base", strlen("base::Base"));
    common::WriteMsg::write(CMSG_GET_THE_NODE_HASH_OF_NODE_END,resultHash.checksum()); 
    nodeHashCache = resultHash.checksum();
    hashOk = true;
    return nodeHashCache;
  }

  void Base::sort(bool withVirtualBase /* = true */) {
  }

  void Base::save(io::BinaryIO &binIo,bool withVirtualBase  /*= true*/) const {
    binIo.writeUInt4(m_id);
    binIo.writeUShort2(getNodeKind());

  }

  void Base::load(io::BinaryIO &binIo, bool withVirtualBase /*= true*/) {

  }


}


}}}
