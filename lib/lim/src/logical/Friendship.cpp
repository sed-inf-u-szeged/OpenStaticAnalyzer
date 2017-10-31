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

#include "lim/inc/lim.h"
#include "lim/inc/Common.h"
#include "common/inc/WriteMessage.h"

#include "lim/inc/messages.h"
#include <algorithm>
#include <string.h>
#include "common/inc/math/common.h"


namespace columbus { namespace lim { namespace asg {

typedef boost::crc_32_type  Crc_type;

namespace logical { 
  Friendship::Friendship(NodeId _id, Factory *_factory) :
    Base(_id, _factory),
    m_grants(0),
    m_friend(0)
  {
  }

  Friendship::~Friendship() {
  }

  void Friendship::clone(const Friendship& other, bool tryOnVirtualParent) {
    base::Base::clone(other, false);

    m_grants = other.m_grants;
    m_friend = other.m_friend;
  }

  void Friendship::prepareDelete(bool tryOnVirtualParent){
    removeFriend();
    base::Base::prepareDelete(false);
  }

  NodeKind Friendship::getNodeKind() const {
    return ndkFriendship;
  }

  Key Friendship::getGrantsKey() const {
    return m_grants;
  }

  const std::string& Friendship::getGrants() const {
    return factory->getStringTable().get(m_grants);
  }

  void Friendship::setGrantsKey(Key _grants) {
    m_grants = _grants;
  }

  void Friendship::setGrants(const std::string& _grants) {
    m_grants = factory->getStringTable().set(_grants);
  }

  logical::Scope* Friendship::getFriend() const {
    logical::Scope *_node = NULL;
    if (m_friend != 0)
      _node = dynamic_cast<logical::Scope*>(factory->getPointer(m_friend));
    if ( (_node == NULL) || factory->getIsFiltered(_node))
      return NULL;

    return _node;
  }

  bool Friendship::setEdge(EdgeKind edgeKind, NodeId edgeEnd, void* acValue, bool tryOnVirtualParent) {
    switch (edgeKind) {
      case edkFriendship_Friend:
        setFriend(edgeEnd);
        return true;
      default:
        break;
    }
    if (base::Base::setEdge(edgeKind, edgeEnd, acValue, false)) {
      return true;
    }
    return false;
  }

  bool Friendship::removeEdge(EdgeKind edgeKind, NodeId edgeEnd, bool tryOnVirtualParent) {
    switch (edgeKind) {
      case edkFriendship_Friend:
        removeFriend();
        return true;
      default:
        break;
    }
    if (base::Base::removeEdge(edgeKind, edgeEnd, false)) {
      return true;
    }
    return false;
  }

  void Friendship::setFriend(NodeId _id) {
    logical::Scope *_node = NULL;
    if (_id) {
      if (!factory->getExist(_id))
        throw LimException(COLUMBUS_LOCATION, CMSG_EX_THE_END_POINT_OF_THE_EDGE_DOES_NOT_EXIST);

      _node = dynamic_cast<logical::Scope*> (factory->getPointer(_id));
      if ( _node == NULL) {
        throw LimException(COLUMBUS_LOCATION, CMSG_EX_INVALID_NODE_KIND);
      }
      if (&(_node->getFactory()) != this->factory)
        throw LimException(COLUMBUS_LOCATION, CMSG_EX_THE_FACTORY_OF_NODES_DOES_NOT_MATCH );

      if (Common::getIsBaseClassKind(_node->getNodeKind(), ndkMethod) || Common::getIsBaseClassKind(_node->getNodeKind(), ndkClass)) {
        if (m_friend) {
          if (factory->getExistsReverseEdges())
            factory->reverseEdges->removeEdge(m_friend, m_id, edkFriendship_Friend);
        }
        m_friend = _node->getId();
        if (factory->getExistsReverseEdges())
          factory->reverseEdges->insertEdge(m_friend, this->getId(), edkFriendship_Friend);
      } else {
        throw LimException(COLUMBUS_LOCATION, CMSG_EX_INVALID_NODE_KIND);
      }
    } else {
      if (m_friend) {
        throw LimException(COLUMBUS_LOCATION, CMSG_EX_CAN_T_SET_EDGE_TO_NULL);
      }
    }
  }

  void Friendship::setFriend(logical::Scope *_node) {
    if (_node == NULL)
      throw LimException(COLUMBUS_LOCATION, CMSG_EX_CAN_T_SET_EDGE_TO_NULL);

    setFriend(_node->getId());
  }

  void Friendship::removeFriend() {
      if (m_friend) {
        if (factory->getExistsReverseEdges())
          factory->reverseEdges->removeEdge(m_friend, m_id, edkFriendship_Friend);
      }
      m_friend = 0;
  }

  void Friendship::accept(Visitor &visitor) const {
    visitor.visit(*this);
  }

  void Friendship::acceptEnd(Visitor &visitor) const {
    visitor.visitEnd(*this);
  }

  double Friendship::getSimilarity(const base::Base& base){
    if(base.getNodeKind() == getNodeKind()) {
      const Friendship& node = dynamic_cast<const Friendship&>(base);
      double matchAttrs = 0;
      std::string str1, str2;
      size_t strMax;
      double strSim;
      str1 = getGrants();
      str2 = node.getGrants();
      strMax = std::max(str1.size(), str2.size());
      strSim = 1 - ((double)common::math::editDistance(str1, str2) / (strMax > 0 ? strMax : 1));
      if (strSim < Common::SimilarityMinForStrings)
        return 0.0;
      matchAttrs += strSim;
      return matchAttrs / (1 / (1 - Common::SimilarityMinimum)) + Common::SimilarityMinimum;
    } else {
      return 0.0;
    }
  }

  void Friendship::swapStringTable(RefDistributorStrTable& newStrTable, std::map<Key,Key>& oldAndNewStrKeyMap ){
    std::map<Key,Key>::iterator foundKeyId;

    foundKeyId = oldAndNewStrKeyMap.find(m_grants);
    if (foundKeyId != oldAndNewStrKeyMap.end()) {
      m_grants = foundKeyId->second;
    } else {
      Key oldkey = m_grants;
      m_grants = newStrTable.set(factory->getStringTable().get(m_grants));
      oldAndNewStrKeyMap.insert(std::pair<Key,Key>(oldkey,m_grants));    }

  }

  NodeHashType Friendship::getHash(std::set<NodeId>& travNodes) const {
    if (hashOk) return nodeHashCache;
    common::WriteMsg::write(CMSG_GET_THE_NODE_HASH_OF_NODE_BEGIN,this->getId()); 
    if (travNodes.count(getId())>0) {
      common::WriteMsg::write(CMSG_GET_THE_NODE_HASH_OF_NODE_SKIP);
      return 0;
    }
    travNodes.insert(getId());
    Crc_type resultHash;
    resultHash.process_bytes( "logical::Friendship", strlen("logical::Friendship"));
    common::WriteMsg::write(CMSG_GET_THE_NODE_HASH_OF_NODE_END,resultHash.checksum()); 
    nodeHashCache = resultHash.checksum();
    hashOk = true;
    return nodeHashCache;
  }

  void Friendship::save(io::BinaryIO &binIo,bool withVirtualBase  /*= true*/) const {
    Base::save(binIo,false);

    factory->getStringTable().setType(m_grants, StrTable::strToSave);
    binIo.writeUInt4(m_grants);

    binIo.writeUInt4(m_friend);

  }

  void Friendship::load(io::BinaryIO &binIo, bool withVirtualBase /*= true*/) {
    Base::load(binIo,false);

    m_grants = binIo.readUInt4();

    m_friend =  binIo.readUInt4();

  }


}


}}}
