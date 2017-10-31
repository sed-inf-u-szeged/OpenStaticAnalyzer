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

namespace physical { 
  FileSystem::FileSystem(NodeId _id, Factory *_factory) :
    Named(_id, _factory),
    hasFSEntryContainer()
  {
  }

  FileSystem::~FileSystem() {
  }

  void FileSystem::clone(const FileSystem& other, bool tryOnVirtualParent) {
    base::Named::clone(other, false);

    hasFSEntryContainer = other.hasFSEntryContainer;
  }

  void FileSystem::prepareDelete(bool tryOnVirtualParent){
    while (!hasFSEntryContainer.empty()) {
      const NodeId id = *hasFSEntryContainer.begin();
      removeParentEdge(id);
      if (factory->getExistsReverseEdges())
        factory->reverseEdges->removeEdge(id, this->getId(), edkFileSystem_HasFSEntry);
      hasFSEntryContainer.pop_front();
    }
    base::Named::prepareDelete(false);
  }

  NodeKind FileSystem::getNodeKind() const {
    return ndkFileSystem;
  }

  ListIterator<physical::FSEntry> FileSystem::getFSEntryListIteratorBegin() const {
    return ListIterator<physical::FSEntry>(&hasFSEntryContainer, factory, true);
  }

  ListIterator<physical::FSEntry> FileSystem::getFSEntryListIteratorEnd() const {
    return ListIterator<physical::FSEntry>(&hasFSEntryContainer, factory, false);
  }

  bool FileSystem::getFSEntryIsEmpty() const {
    return getFSEntryListIteratorBegin() == getFSEntryListIteratorEnd();
  }

  unsigned int FileSystem::getFSEntrySize() const {
    unsigned int size = 0;
    ListIterator<physical::FSEntry> endIt = getFSEntryListIteratorEnd();
    for (ListIterator<physical::FSEntry> it = getFSEntryListIteratorBegin(); it != endIt; ++it) {
      ++size;
    }
    return size;
  }

  bool FileSystem::setEdge(EdgeKind edgeKind, NodeId edgeEnd, void* acValue, bool tryOnVirtualParent) {
    switch (edgeKind) {
      case edkFileSystem_HasFSEntry:
        addFSEntry(edgeEnd);
        return true;
      default:
        break;
    }
    if (base::Named::setEdge(edgeKind, edgeEnd, acValue, false)) {
      return true;
    }
    return false;
  }

  bool FileSystem::removeEdge(EdgeKind edgeKind, NodeId edgeEnd, bool tryOnVirtualParent) {
    switch (edgeKind) {
      case edkFileSystem_HasFSEntry:
        removeFSEntry(edgeEnd);
        return true;
      default:
        break;
    }
    if (base::Named::removeEdge(edgeKind, edgeEnd, false)) {
      return true;
    }
    return false;
  }

  void FileSystem::addFSEntry(const physical::FSEntry *_node) {
    if (_node == NULL)
      throw LimException(COLUMBUS_LOCATION, CMSG_EX_THE_NODE_IS_NULL);

    if (&(_node->getFactory()) != this->factory)
      throw LimException(COLUMBUS_LOCATION, CMSG_EX_THE_FACTORY_OF_NODES_DOES_NOT_MATCH);

    if (!(Common::getIsFSEntry(*_node)))
      throw LimException(COLUMBUS_LOCATION, CMSG_EX_INVALID_NODE_KIND);

    hasFSEntryContainer.push_back(_node->getId());
    setParentEdge(_node,edkFileSystem_HasFSEntry);

    if (factory->reverseEdges)
      factory->reverseEdges->insertEdge(_node, this, edkFileSystem_HasFSEntry);
  }

  void FileSystem::addFSEntry(NodeId _id) {
    const physical::FSEntry *node = dynamic_cast<physical::FSEntry*>(factory->getPointer(_id));
    if (node == NULL)
      throw LimException(COLUMBUS_LOCATION, CMSG_EX_INVALID_NODE_KIND);
    addFSEntry( node );
  }

  void FileSystem::removeFSEntry(NodeId id) {
    if (!factory->getExist(id))
      throw LimException(COLUMBUS_LOCATION, CMSG_EX_THE_END_POINT_OF_THE_EDGE_DOES_NOT_EXIST);

    ListIterator<physical::FSEntry>::Container::iterator it = find(hasFSEntryContainer.begin(), hasFSEntryContainer.end(), id);

    if (it == hasFSEntryContainer.end())
      throw LimException(COLUMBUS_LOCATION, CMSG_EX_THE_END_POINT_OF_THE_EDGE_DOES_NOT_EXIST);

    hasFSEntryContainer.erase(it);

    removeParentEdge(id);

    if (factory->getExistsReverseEdges())
      factory->reverseEdges->removeEdge(id, this->getId(), edkFileSystem_HasFSEntry);
  }

  void FileSystem::removeFSEntry(physical::FSEntry *_node) {
    if (_node == NULL)
      throw LimException(COLUMBUS_LOCATION, CMSG_EX_THE_EDGE_IS_NULL);

    removeFSEntry(_node->getId());
  }

  void FileSystem::accept(Visitor &visitor) const {
    visitor.visit(*this);
  }

  void FileSystem::acceptEnd(Visitor &visitor) const {
    visitor.visitEnd(*this);
  }

  double FileSystem::getSimilarity(const base::Base& base){
    if(base.getNodeKind() == getNodeKind()) {
      const FileSystem& node = dynamic_cast<const FileSystem&>(base);
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

  void FileSystem::swapStringTable(RefDistributorStrTable& newStrTable, std::map<Key,Key>& oldAndNewStrKeyMap ){
    std::map<Key,Key>::iterator foundKeyId;

    foundKeyId = oldAndNewStrKeyMap.find(m_name);
    if (foundKeyId != oldAndNewStrKeyMap.end()) {
      m_name = foundKeyId->second;
    } else {
      Key oldkey = m_name;
      m_name = newStrTable.set(factory->getStringTable().get(m_name));
      oldAndNewStrKeyMap.insert(std::pair<Key,Key>(oldkey,m_name));    }

  }

  NodeHashType FileSystem::getHash(std::set<NodeId>& travNodes) const {
    if (hashOk) return nodeHashCache;
    common::WriteMsg::write(CMSG_GET_THE_NODE_HASH_OF_NODE_BEGIN,this->getId()); 
    if (travNodes.count(getId())>0) {
      common::WriteMsg::write(CMSG_GET_THE_NODE_HASH_OF_NODE_SKIP);
      return 0;
    }
    travNodes.insert(getId());
    Crc_type resultHash;
    resultHash.process_bytes( "physical::FileSystem", strlen("physical::FileSystem"));
    common::WriteMsg::write(CMSG_GET_THE_NODE_HASH_OF_NODE_END,resultHash.checksum()); 
    nodeHashCache = resultHash.checksum();
    hashOk = true;
    return nodeHashCache;
  }

  void FileSystem::save(io::BinaryIO &binIo,bool withVirtualBase  /*= true*/) const {
    Named::save(binIo,false);


    for (ListIterator<physical::FSEntry>::Container::const_iterator it = hasFSEntryContainer.begin(); it != hasFSEntryContainer.end(); ++it) {
      binIo.writeUInt4(*it);
    }
    binIo.writeUInt4(0); // This is the end sign
  }

  void FileSystem::load(io::BinaryIO &binIo, bool withVirtualBase /*= true*/) {
    Named::load(binIo,false);

    NodeId _id;

    _id = binIo.readUInt4();
    while (_id) {
      hasFSEntryContainer.push_back(_id);
      setParentEdge(factory->getPointer(_id),edkFileSystem_HasFSEntry);
      _id = binIo.readUInt4();
    }
  }


}


}}}
