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
#include <common/inc/StringSup.h>
#include <sstream>


namespace columbus { namespace java { namespace asg {

typedef boost::crc_32_type  Crc_type;

namespace struc { 
  Scope::Scope(NodeId _id, Factory *_factory) :
         Base(_id, _factory),
         Commentable(_id, _factory),
    Member(_id, _factory),
    hasMembersContainer()
  {
  }

  Scope::~Scope() {
  }

  void Scope::clone(const Scope& other, bool tryOnVirtualParent) {
    if (tryOnVirtualParent) {
      base::Base::clone(other, false);
    }
    if (tryOnVirtualParent) {
      base::Commentable::clone(other, false);
    }
    if (tryOnVirtualParent) {
      struc::Member::clone(other, false);
    }

    hasMembersContainer = other.hasMembersContainer;
  }

  void Scope::prepareDelete(bool tryOnVirtualParent){
    while (!hasMembersContainer.empty()) {
      const NodeId id = *hasMembersContainer.begin();
      removeParentEdge(id);
      if (factory->getExistsReverseEdges())
        factory->reverseEdges->removeEdge(id, this->getId(), edkScope_HasMembers);
      hasMembersContainer.pop_front();
    }
    if (tryOnVirtualParent) {
      base::Base::prepareDelete(false);
    }
    if (tryOnVirtualParent) {
      base::Commentable::prepareDelete(false);
    }
    if (tryOnVirtualParent) {
      struc::Member::prepareDelete(false);
    }
  }

  ListIterator<struc::Member> Scope::getMembersListIteratorBegin() const {
    return ListIterator<struc::Member>(&hasMembersContainer, factory, true);
  }

  ListIterator<struc::Member> Scope::getMembersListIteratorEnd() const {
    return ListIterator<struc::Member>(&hasMembersContainer, factory, false);
  }

  bool Scope::getMembersIsEmpty() const {
    return getMembersListIteratorBegin() == getMembersListIteratorEnd();
  }

  unsigned int Scope::getMembersSize() const {
    unsigned int size = 0;
    ListIterator<struc::Member> endIt = getMembersListIteratorEnd();
    for (ListIterator<struc::Member> it = getMembersListIteratorBegin(); it != endIt; ++it) {
      ++size;
    }
    return size;
  }

  bool Scope::setEdge(EdgeKind edgeKind, NodeId edgeEnd, bool tryOnVirtualParent) {
    switch (edgeKind) {
      case edkScope_HasMembers:
        addMembers(edgeEnd);
        return true;
      default:
        break;
    }
    if (tryOnVirtualParent) {
      if (base::Base::setEdge(edgeKind, edgeEnd, false)) {
        return true;
      }
    }
    if (tryOnVirtualParent) {
      if (base::Commentable::setEdge(edgeKind, edgeEnd, false)) {
        return true;
      }
    }
    if (tryOnVirtualParent) {
      if (struc::Member::setEdge(edgeKind, edgeEnd, false)) {
        return true;
      }
    }
    return false;
  }

  bool Scope::removeEdge(EdgeKind edgeKind, NodeId edgeEnd, bool tryOnVirtualParent) {
    switch (edgeKind) {
      case edkScope_HasMembers:
        removeMembers(edgeEnd);
        return true;
      default:
        break;
    }
    if (tryOnVirtualParent) {
      if (base::Base::removeEdge(edgeKind, edgeEnd, false)) {
        return true;
      }
    }
    if (tryOnVirtualParent) {
      if (base::Commentable::removeEdge(edgeKind, edgeEnd, false)) {
        return true;
      }
    }
    if (tryOnVirtualParent) {
      if (struc::Member::removeEdge(edgeKind, edgeEnd, false)) {
        return true;
      }
    }
    return false;
  }

  void Scope::addMembers(const struc::Member *_node) {
    if (_node == NULL)
      throw JavaException(COLUMBUS_LOCATION, CMSG_EX_THE_NODE_IS_NULL);

    if (&(_node->getFactory()) != this->factory)
      throw JavaException(COLUMBUS_LOCATION, CMSG_EX_THE_FACTORY_OF_NODES_DOES_NOT_MATCH);

    if (!(Common::getIsMember(*_node)))
      throw JavaException(COLUMBUS_LOCATION, CMSG_EX_INVALID_NODE_KIND);

    hasMembersContainer.push_back(_node->getId());
    setParentEdge(_node,edkScope_HasMembers);

    if (factory->reverseEdges)
      factory->reverseEdges->insertEdge(_node, this, edkScope_HasMembers);
  }

  void Scope::addMembers(NodeId _id) {
    const struc::Member *node = dynamic_cast<struc::Member*>(factory->getPointer(_id));
    if (node == NULL)
      throw JavaException(COLUMBUS_LOCATION, CMSG_EX_INVALID_NODE_KIND);
    addMembers( node );
  }

  void Scope::removeMembers(NodeId id) {
    if (!factory->getExist(id))
      throw JavaException(COLUMBUS_LOCATION, CMSG_EX_THE_END_POINT_OF_THE_EDGE_DOES_NOT_EXIST);

    ListIterator<struc::Member>::Container::iterator it = find(hasMembersContainer.begin(), hasMembersContainer.end(), id);

    if (it == hasMembersContainer.end())
      throw JavaException(COLUMBUS_LOCATION, CMSG_EX_THE_END_POINT_OF_THE_EDGE_DOES_NOT_EXIST);

    hasMembersContainer.erase(it);

    removeParentEdge(id);

    if (factory->getExistsReverseEdges())
      factory->reverseEdges->removeEdge(id, this->getId(), edkScope_HasMembers);
  }

  void Scope::removeMembers(struc::Member *_node) {
    if (_node == NULL)
      throw JavaException(COLUMBUS_LOCATION, CMSG_EX_THE_EDGE_IS_NULL);

    removeMembers(_node->getId());
  }

  double Scope::getSimilarity(const base::Base& base){
    if(base.getNodeKind() == getNodeKind()) {
      return 1.0;
    } else {
      return 0.0;
    }
  }

  void Scope::swapStringTable(RefDistributorStrTable& newStrTable, std::map<Key,Key>& oldAndNewStrKeyMap ){
    std::map<Key,Key>::iterator foundKeyId;

  }

  NodeHashType Scope::getHash(std::set<NodeId>& travNodes) const {
    if (hashOk) return nodeHashCache;
    common::WriteMsg::write(CMSG_GET_THE_NODE_HASH_OF_NODE_BEGIN,this->getId()); 
    if (travNodes.count(getId())>0) {
      common::WriteMsg::write(CMSG_GET_THE_NODE_HASH_OF_NODE_SKIP);
      return 0;
    }
    travNodes.insert(getId());
    Crc_type resultHash;
    resultHash.process_bytes( "struc::Scope", strlen("struc::Scope"));
    common::WriteMsg::write(CMSG_GET_THE_NODE_HASH_OF_NODE_END,resultHash.checksum()); 
    nodeHashCache = resultHash.checksum();
    hashOk = true;
    return nodeHashCache;
  }

  void Scope::sort(bool withVirtualBase /* = true */) {
    if (withVirtualBase)
      Base::sort(false);
    if (withVirtualBase)
      Commentable::sort(false);
    if (withVirtualBase)
      Member::sort(false);

    {
      std::map<std::string, NodeId> csUnameMap;
      std::map<std::string, std::set<NodeId>, common::case_insensitive_compare> edgeMap;
      std::map<std::string, std::set<NodeId>, common::case_insensitive_compare>::iterator emapit;
      ListIterator<struc::Member>::Container::iterator eit, eit2;

      for (eit = hasMembersContainer.begin(); eit != hasMembersContainer.end(); ++eit) {
        std::string str = Common::getUniqueStringForSorting(factory->getRef(*eit));
        edgeMap[str].insert(*eit);
        std::pair<std::map<std::string, NodeId>::iterator, bool> unameRes = csUnameMap.insert(make_pair(str, *eit));
        if (!unameRes.second) {
          common::WriteMsg::write(CMSG_SORT_DUPLICATED_EDGE_NAMES_AT_NODE, "hasMembers", m_id, Common::toString(getNodeKind()).c_str(), str.c_str());
          common::WriteMsg::write(CMSG_SORT_DUPLICATED_EDGE_DATA, unameRes.first->second, Common::toString(factory->getNodeKind(unameRes.first->second)).c_str());
          common::WriteMsg::write(CMSG_SORT_DUPLICATED_EDGE_DATA, *eit, Common::toString(factory->getNodeKind(*eit)).c_str());
        }
      }

      for (emapit = edgeMap.begin(), eit = hasMembersContainer.begin(); emapit != edgeMap.end(); ++emapit) {
        if (emapit->second.size() != 1) {
          for (std::set<NodeId>::const_iterator it = emapit->second.begin(); it != emapit->second.end(); ++it) {
            *eit = *it;
            ++eit;
          }
        } else {
          *eit = *emapit->second.begin();
          ++eit;
        }
      }
      eit2 = hasMembersContainer.end();
      if (eit != eit2) {
        hasMembersContainer.erase(eit, eit2);
      }
    }

  }

  void Scope::save(io::BinaryIO &binIo,bool withVirtualBase  /*= true*/) const {
    if (withVirtualBase)
      Base::save(binIo,false);

    if (withVirtualBase)
      Commentable::save(binIo,false);

    if (withVirtualBase)
      Member::save(binIo,false);


    for (ListIterator<struc::Member>::Container::const_iterator it = hasMembersContainer.begin(); it != hasMembersContainer.end(); ++it) {
      binIo.writeUInt4(*it);
    }
    binIo.writeUInt4(0); // This is the end sign
  }

  void Scope::load(io::BinaryIO &binIo, bool withVirtualBase /*= true*/) {
    if (withVirtualBase)
      Base::load(binIo, false);

    if (withVirtualBase)
      Commentable::load(binIo, false);

    if (withVirtualBase)
      Member::load(binIo,false);

    NodeId _id;

    _id = binIo.readUInt4();
    while (_id) {
      hasMembersContainer.push_back(_id);
      setParentEdge(factory->getPointer(_id),edkScope_HasMembers);
      _id = binIo.readUInt4();
    }
  }


}


}}}
