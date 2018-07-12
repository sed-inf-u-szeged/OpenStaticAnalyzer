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

namespace physical { 
  Folder::Folder(NodeId _id, Factory *_factory) :
    FSEntry(_id, _factory),
    containsContainer()
  {
  }

  Folder::~Folder() {
  }

  void Folder::clone(const Folder& other, bool tryOnVirtualParent) {
    physical::FSEntry::clone(other, false);

    containsContainer = other.containsContainer;
  }

  void Folder::prepareDelete(bool tryOnVirtualParent){
    while (!containsContainer.empty()) {
      const NodeId id = *containsContainer.begin();
      removeParentEdge(id);
      if (factory->getExistsReverseEdges())
        factory->reverseEdges->removeEdge(id, this->getId(), edkFolder_Contains);
      containsContainer.pop_front();
    }
    physical::FSEntry::prepareDelete(false);
  }

  NodeKind Folder::getNodeKind() const {
    return ndkFolder;
  }

  ListIterator<physical::FSEntry> Folder::getContainsListIteratorBegin() const {
    return ListIterator<physical::FSEntry>(&containsContainer, factory, true);
  }

  ListIterator<physical::FSEntry> Folder::getContainsListIteratorEnd() const {
    return ListIterator<physical::FSEntry>(&containsContainer, factory, false);
  }

  bool Folder::getContainsIsEmpty() const {
    return getContainsListIteratorBegin() == getContainsListIteratorEnd();
  }

  unsigned int Folder::getContainsSize() const {
    unsigned int size = 0;
    ListIterator<physical::FSEntry> endIt = getContainsListIteratorEnd();
    for (ListIterator<physical::FSEntry> it = getContainsListIteratorBegin(); it != endIt; ++it) {
      ++size;
    }
    return size;
  }

  bool Folder::setEdge(EdgeKind edgeKind, NodeId edgeEnd, void* acValue, bool tryOnVirtualParent) {
    switch (edgeKind) {
      case edkFolder_Contains:
        addContains(edgeEnd);
        return true;
      default:
        break;
    }
    if (physical::FSEntry::setEdge(edgeKind, edgeEnd, acValue, false)) {
      return true;
    }
    return false;
  }

  bool Folder::removeEdge(EdgeKind edgeKind, NodeId edgeEnd, bool tryOnVirtualParent) {
    switch (edgeKind) {
      case edkFolder_Contains:
        removeContains(edgeEnd);
        return true;
      default:
        break;
    }
    if (physical::FSEntry::removeEdge(edgeKind, edgeEnd, false)) {
      return true;
    }
    return false;
  }

  void Folder::addContains(const physical::FSEntry *_node) {
    if (_node == NULL)
      throw LimException(COLUMBUS_LOCATION, CMSG_EX_THE_NODE_IS_NULL);

    if (&(_node->getFactory()) != this->factory)
      throw LimException(COLUMBUS_LOCATION, CMSG_EX_THE_FACTORY_OF_NODES_DOES_NOT_MATCH);

    if (!(Common::getIsFSEntry(*_node)))
      throw LimException(COLUMBUS_LOCATION, CMSG_EX_INVALID_NODE_KIND);

    containsContainer.push_back(_node->getId());
    setParentEdge(_node,edkFolder_Contains);

    if (factory->reverseEdges)
      factory->reverseEdges->insertEdge(_node, this, edkFolder_Contains);
  }

  void Folder::addContains(NodeId _id) {
    const physical::FSEntry *node = dynamic_cast<physical::FSEntry*>(factory->getPointer(_id));
    if (node == NULL)
      throw LimException(COLUMBUS_LOCATION, CMSG_EX_INVALID_NODE_KIND);
    addContains( node );
  }

  void Folder::removeContains(NodeId id) {
    if (!factory->getExist(id))
      throw LimException(COLUMBUS_LOCATION, CMSG_EX_THE_END_POINT_OF_THE_EDGE_DOES_NOT_EXIST);

    ListIterator<physical::FSEntry>::Container::iterator it = find(containsContainer.begin(), containsContainer.end(), id);

    if (it == containsContainer.end())
      throw LimException(COLUMBUS_LOCATION, CMSG_EX_THE_END_POINT_OF_THE_EDGE_DOES_NOT_EXIST);

    containsContainer.erase(it);

    removeParentEdge(id);

    if (factory->getExistsReverseEdges())
      factory->reverseEdges->removeEdge(id, this->getId(), edkFolder_Contains);
  }

  void Folder::removeContains(physical::FSEntry *_node) {
    if (_node == NULL)
      throw LimException(COLUMBUS_LOCATION, CMSG_EX_THE_EDGE_IS_NULL);

    removeContains(_node->getId());
  }

  void Folder::accept(Visitor &visitor) const {
    visitor.visit(*this);
  }

  void Folder::acceptEnd(Visitor &visitor) const {
    visitor.visitEnd(*this);
  }

  double Folder::getSimilarity(const base::Base& base){
    if(base.getNodeKind() == getNodeKind()) {
      const Folder& node = dynamic_cast<const Folder&>(base);
      double matchAttrs = 0;
      std::string str1, str2;
      size_t strMax;
      double strSim;
      str1 = getName();
      str2 = node.getName();
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

  void Folder::swapStringTable(RefDistributorStrTable& newStrTable, std::map<Key,Key>& oldAndNewStrKeyMap ){
    std::map<Key,Key>::iterator foundKeyId;

    foundKeyId = oldAndNewStrKeyMap.find(m_name);
    if (foundKeyId != oldAndNewStrKeyMap.end()) {
      m_name = foundKeyId->second;
    } else {
      Key oldkey = m_name;
      m_name = newStrTable.set(factory->getStringTable().get(m_name));
      oldAndNewStrKeyMap.insert(std::pair<Key,Key>(oldkey,m_name));    }

  }

  NodeHashType Folder::getHash(std::set<NodeId>& travNodes) const {
    if (hashOk) return nodeHashCache;
    common::WriteMsg::write(CMSG_GET_THE_NODE_HASH_OF_NODE_BEGIN,this->getId()); 
    if (travNodes.count(getId())>0) {
      common::WriteMsg::write(CMSG_GET_THE_NODE_HASH_OF_NODE_SKIP);
      return 0;
    }
    travNodes.insert(getId());
    Crc_type resultHash;
    resultHash.process_bytes( "physical::Folder", strlen("physical::Folder"));
    common::WriteMsg::write(CMSG_GET_THE_NODE_HASH_OF_NODE_END,resultHash.checksum()); 
    nodeHashCache = resultHash.checksum();
    hashOk = true;
    return nodeHashCache;
  }

  void Folder::save(io::BinaryIO &binIo,bool withVirtualBase  /*= true*/) const {
    FSEntry::save(binIo,false);


    for (ListIterator<physical::FSEntry>::Container::const_iterator it = containsContainer.begin(); it != containsContainer.end(); ++it) {
      binIo.writeUInt4(*it);
    }
    binIo.writeUInt4(0); // This is the end sign
  }

  void Folder::load(io::BinaryIO &binIo, bool withVirtualBase /*= true*/) {
    FSEntry::load(binIo,false);

    NodeId _id;

    _id = binIo.readUInt4();
    while (_id) {
      containsContainer.push_back(_id);
      setParentEdge(factory->getPointer(_id),edkFolder_Contains);
      _id = binIo.readUInt4();
    }
  }


}


}}}
