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

namespace base { 
  Component::Component(NodeId _id, Factory *_factory) :
    Named(_id, _factory),
    m_TLLOC(0),
    m_TLOC(0),
    m_analysisTime(atkNow),
    m_changesetID(0),
    m_shortName(0),
    compilationUnitContainer(),
    containsContainer(),
    hasFilesContainer()
  {
  }

  Component::~Component() {
  }

  void Component::clone(const Component& other, bool tryOnVirtualParent) {
    base::Named::clone(other, false);

    m_TLLOC = other.m_TLLOC;
    m_TLOC = other.m_TLOC;
    m_analysisTime = other.m_analysisTime;
    m_changesetID = other.m_changesetID;
    m_shortName = other.m_shortName;
    compilationUnitContainer = other.compilationUnitContainer;
    containsContainer = other.containsContainer;
    hasFilesContainer = other.hasFilesContainer;
  }

  void Component::prepareDelete(bool tryOnVirtualParent){
    while (!compilationUnitContainer.empty()) {
      const NodeId id = *compilationUnitContainer.begin();
      if (factory->getExistsReverseEdges())
        factory->reverseEdges->removeEdge(id, this->getId(), edkComponent_CompilationUnit);
      compilationUnitContainer.pop_front();
    }
    while (!containsContainer.empty()) {
      const NodeId id = *containsContainer.begin();
      if (factory->getExistsReverseEdges())
        factory->reverseEdges->removeEdge(id, this->getId(), edkComponent_Contains);
      containsContainer.pop_front();
    }
    while (!hasFilesContainer.empty()) {
      const NodeId id = *hasFilesContainer.begin();
      if (factory->getExistsReverseEdges())
        factory->reverseEdges->removeEdge(id, this->getId(), edkComponent_HasFiles);
      hasFilesContainer.pop_front();
    }
    base::Named::prepareDelete(false);
  }

  NodeKind Component::getNodeKind() const {
    return ndkComponent;
  }

  unsigned Component::getTLLOC() const {
    return m_TLLOC;
  }

  unsigned Component::getTLOC() const {
    return m_TLOC;
  }

  AnalysisTimeKind Component::getAnalysisTime() const {
    return m_analysisTime;
  }

  Key Component::getChangesetIDKey() const {
    return m_changesetID;
  }

  const std::string& Component::getChangesetID() const {
    return factory->getStringTable().get(m_changesetID);
  }

  Key Component::getShortNameKey() const {
    return m_shortName;
  }

  const std::string& Component::getShortName() const {
    return factory->getStringTable().get(m_shortName);
  }

  void Component::setTLLOC(unsigned _TLLOC) {
    m_TLLOC = _TLLOC;
  }

  void Component::setTLOC(unsigned _TLOC) {
    m_TLOC = _TLOC;
  }

  void Component::setAnalysisTime(AnalysisTimeKind _analysisTime) {
    m_analysisTime = _analysisTime;
  }

  void Component::setChangesetIDKey(Key _changesetID) {
    m_changesetID = _changesetID;
  }

  void Component::setChangesetID(const std::string& _changesetID) {
    m_changesetID = factory->getStringTable().set(_changesetID);
  }

  void Component::setShortNameKey(Key _shortName) {
    m_shortName = _shortName;
  }

  void Component::setShortName(const std::string& _shortName) {
    m_shortName = factory->getStringTable().set(_shortName);
  }

  ListIterator<physical::File> Component::getCompilationUnitListIteratorBegin() const {
    return ListIterator<physical::File>(&compilationUnitContainer, factory, true);
  }

  ListIterator<physical::File> Component::getCompilationUnitListIteratorEnd() const {
    return ListIterator<physical::File>(&compilationUnitContainer, factory, false);
  }

  bool Component::getCompilationUnitIsEmpty() const {
    return getCompilationUnitListIteratorBegin() == getCompilationUnitListIteratorEnd();
  }

  unsigned int Component::getCompilationUnitSize() const {
    unsigned int size = 0;
    ListIterator<physical::File> endIt = getCompilationUnitListIteratorEnd();
    for (ListIterator<physical::File> it = getCompilationUnitListIteratorBegin(); it != endIt; ++it) {
      ++size;
    }
    return size;
  }

  ListIterator<base::Component> Component::getContainsListIteratorBegin() const {
    return ListIterator<base::Component>(&containsContainer, factory, true);
  }

  ListIterator<base::Component> Component::getContainsListIteratorEnd() const {
    return ListIterator<base::Component>(&containsContainer, factory, false);
  }

  bool Component::getContainsIsEmpty() const {
    return getContainsListIteratorBegin() == getContainsListIteratorEnd();
  }

  unsigned int Component::getContainsSize() const {
    unsigned int size = 0;
    ListIterator<base::Component> endIt = getContainsListIteratorEnd();
    for (ListIterator<base::Component> it = getContainsListIteratorBegin(); it != endIt; ++it) {
      ++size;
    }
    return size;
  }

  ListIterator<physical::File> Component::getFilesListIteratorBegin() const {
    return ListIterator<physical::File>(&hasFilesContainer, factory, true);
  }

  ListIterator<physical::File> Component::getFilesListIteratorEnd() const {
    return ListIterator<physical::File>(&hasFilesContainer, factory, false);
  }

  bool Component::getFilesIsEmpty() const {
    return getFilesListIteratorBegin() == getFilesListIteratorEnd();
  }

  unsigned int Component::getFilesSize() const {
    unsigned int size = 0;
    ListIterator<physical::File> endIt = getFilesListIteratorEnd();
    for (ListIterator<physical::File> it = getFilesListIteratorBegin(); it != endIt; ++it) {
      ++size;
    }
    return size;
  }

  bool Component::setEdge(EdgeKind edgeKind, NodeId edgeEnd, void* acValue, bool tryOnVirtualParent) {
    switch (edgeKind) {
      case edkComponent_CompilationUnit:
        addCompilationUnit(edgeEnd);
        return true;
      case edkComponent_Contains:
        addContains(edgeEnd);
        return true;
      case edkComponent_HasFiles:
        addFiles(edgeEnd);
        return true;
      default:
        break;
    }
    if (base::Named::setEdge(edgeKind, edgeEnd, acValue, false)) {
      return true;
    }
    return false;
  }

  bool Component::removeEdge(EdgeKind edgeKind, NodeId edgeEnd, bool tryOnVirtualParent) {
    switch (edgeKind) {
      case edkComponent_CompilationUnit:
        removeCompilationUnit(edgeEnd);
        return true;
      case edkComponent_Contains:
        removeContains(edgeEnd);
        return true;
      case edkComponent_HasFiles:
        removeFiles(edgeEnd);
        return true;
      default:
        break;
    }
    if (base::Named::removeEdge(edgeKind, edgeEnd, false)) {
      return true;
    }
    return false;
  }

  void Component::addCompilationUnit(const physical::File *_node) {
    if (_node == NULL)
      throw LimException(COLUMBUS_LOCATION, CMSG_EX_THE_NODE_IS_NULL);

    if (&(_node->getFactory()) != this->factory)
      throw LimException(COLUMBUS_LOCATION, CMSG_EX_THE_FACTORY_OF_NODES_DOES_NOT_MATCH);

    if (!((_node->getNodeKind() == ndkFile) ))
      throw LimException(COLUMBUS_LOCATION, CMSG_EX_INVALID_NODE_KIND);

    compilationUnitContainer.push_back(_node->getId());
    if (factory->reverseEdges)
      factory->reverseEdges->insertEdge(_node, this, edkComponent_CompilationUnit);
  }

  void Component::addCompilationUnit(NodeId _id) {
    const physical::File *node = dynamic_cast<physical::File*>(factory->getPointer(_id));
    if (node == NULL)
      throw LimException(COLUMBUS_LOCATION, CMSG_EX_INVALID_NODE_KIND);
    addCompilationUnit( node );
  }

  void Component::removeCompilationUnit(NodeId id) {
    if (!factory->getExist(id))
      throw LimException(COLUMBUS_LOCATION, CMSG_EX_THE_END_POINT_OF_THE_EDGE_DOES_NOT_EXIST);

    ListIterator<physical::File>::Container::iterator it = find(compilationUnitContainer.begin(), compilationUnitContainer.end(), id);

    if (it == compilationUnitContainer.end())
      throw LimException(COLUMBUS_LOCATION, CMSG_EX_THE_END_POINT_OF_THE_EDGE_DOES_NOT_EXIST);

    compilationUnitContainer.erase(it);

    if (factory->getExistsReverseEdges())
      factory->reverseEdges->removeEdge(id, this->getId(), edkComponent_CompilationUnit);
  }

  void Component::removeCompilationUnit(physical::File *_node) {
    if (_node == NULL)
      throw LimException(COLUMBUS_LOCATION, CMSG_EX_THE_EDGE_IS_NULL);

    removeCompilationUnit(_node->getId());
  }

  void Component::addContains(const base::Component *_node) {
    if (_node == NULL)
      throw LimException(COLUMBUS_LOCATION, CMSG_EX_THE_NODE_IS_NULL);

    if (&(_node->getFactory()) != this->factory)
      throw LimException(COLUMBUS_LOCATION, CMSG_EX_THE_FACTORY_OF_NODES_DOES_NOT_MATCH);

    if (!((_node->getNodeKind() == ndkComponent) ))
      throw LimException(COLUMBUS_LOCATION, CMSG_EX_INVALID_NODE_KIND);

    containsContainer.push_back(_node->getId());
    if (factory->reverseEdges)
      factory->reverseEdges->insertEdge(_node, this, edkComponent_Contains);
  }

  void Component::addContains(NodeId _id) {
    const base::Component *node = dynamic_cast<base::Component*>(factory->getPointer(_id));
    if (node == NULL)
      throw LimException(COLUMBUS_LOCATION, CMSG_EX_INVALID_NODE_KIND);
    addContains( node );
  }

  void Component::removeContains(NodeId id) {
    if (!factory->getExist(id))
      throw LimException(COLUMBUS_LOCATION, CMSG_EX_THE_END_POINT_OF_THE_EDGE_DOES_NOT_EXIST);

    ListIterator<base::Component>::Container::iterator it = find(containsContainer.begin(), containsContainer.end(), id);

    if (it == containsContainer.end())
      throw LimException(COLUMBUS_LOCATION, CMSG_EX_THE_END_POINT_OF_THE_EDGE_DOES_NOT_EXIST);

    containsContainer.erase(it);

    if (factory->getExistsReverseEdges())
      factory->reverseEdges->removeEdge(id, this->getId(), edkComponent_Contains);
  }

  void Component::removeContains(base::Component *_node) {
    if (_node == NULL)
      throw LimException(COLUMBUS_LOCATION, CMSG_EX_THE_EDGE_IS_NULL);

    removeContains(_node->getId());
  }

  void Component::addFiles(const physical::File *_node) {
    if (_node == NULL)
      throw LimException(COLUMBUS_LOCATION, CMSG_EX_THE_NODE_IS_NULL);

    if (&(_node->getFactory()) != this->factory)
      throw LimException(COLUMBUS_LOCATION, CMSG_EX_THE_FACTORY_OF_NODES_DOES_NOT_MATCH);

    if (!((_node->getNodeKind() == ndkFile) ))
      throw LimException(COLUMBUS_LOCATION, CMSG_EX_INVALID_NODE_KIND);

    hasFilesContainer.push_back(_node->getId());
    if (factory->reverseEdges)
      factory->reverseEdges->insertEdge(_node, this, edkComponent_HasFiles);
  }

  void Component::addFiles(NodeId _id) {
    const physical::File *node = dynamic_cast<physical::File*>(factory->getPointer(_id));
    if (node == NULL)
      throw LimException(COLUMBUS_LOCATION, CMSG_EX_INVALID_NODE_KIND);
    addFiles( node );
  }

  void Component::removeFiles(NodeId id) {
    if (!factory->getExist(id))
      throw LimException(COLUMBUS_LOCATION, CMSG_EX_THE_END_POINT_OF_THE_EDGE_DOES_NOT_EXIST);

    ListIterator<physical::File>::Container::iterator it = find(hasFilesContainer.begin(), hasFilesContainer.end(), id);

    if (it == hasFilesContainer.end())
      throw LimException(COLUMBUS_LOCATION, CMSG_EX_THE_END_POINT_OF_THE_EDGE_DOES_NOT_EXIST);

    hasFilesContainer.erase(it);

    if (factory->getExistsReverseEdges())
      factory->reverseEdges->removeEdge(id, this->getId(), edkComponent_HasFiles);
  }

  void Component::removeFiles(physical::File *_node) {
    if (_node == NULL)
      throw LimException(COLUMBUS_LOCATION, CMSG_EX_THE_EDGE_IS_NULL);

    removeFiles(_node->getId());
  }

  void Component::accept(Visitor &visitor) const {
    visitor.visit(*this);
  }

  void Component::acceptEnd(Visitor &visitor) const {
    visitor.visitEnd(*this);
  }

  double Component::getSimilarity(const base::Base& base){
    if(base.getNodeKind() == getNodeKind()) {
      const Component& node = dynamic_cast<const Component&>(base);
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
      if(node.getTLLOC() == getTLLOC()) ++matchAttrs;
      if(node.getTLOC() == getTLOC()) ++matchAttrs;
      if(node.getAnalysisTime() == getAnalysisTime()) ++matchAttrs;
      str1 = getChangesetID();
      str2 = node.getChangesetID();
      strMax = std::max(str1.size(), str2.size());
      strSim = 1 - ((double)common::math::editDistance(str1, str2) / (strMax > 0 ? strMax : 1));
      if (strSim < Common::SimilarityMinForStrings)
        return 0.0;
      matchAttrs += strSim;
      str1 = getShortName();
      str2 = node.getShortName();
      strMax = std::max(str1.size(), str2.size());
      strSim = 1 - ((double)common::math::editDistance(str1, str2) / (strMax > 0 ? strMax : 1));
      if (strSim < Common::SimilarityMinForStrings)
        return 0.0;
      matchAttrs += strSim;
      return matchAttrs / (6 / (1 - Common::SimilarityMinimum)) + Common::SimilarityMinimum;
    } else {
      return 0.0;
    }
  }

  void Component::swapStringTable(RefDistributorStrTable& newStrTable, std::map<Key,Key>& oldAndNewStrKeyMap ){
    std::map<Key,Key>::iterator foundKeyId;

    foundKeyId = oldAndNewStrKeyMap.find(m_changesetID);
    if (foundKeyId != oldAndNewStrKeyMap.end()) {
      m_changesetID = foundKeyId->second;
    } else {
      Key oldkey = m_changesetID;
      m_changesetID = newStrTable.set(factory->getStringTable().get(m_changesetID));
      oldAndNewStrKeyMap.insert(std::pair<Key,Key>(oldkey,m_changesetID));    }

    foundKeyId = oldAndNewStrKeyMap.find(m_shortName);
    if (foundKeyId != oldAndNewStrKeyMap.end()) {
      m_shortName = foundKeyId->second;
    } else {
      Key oldkey = m_shortName;
      m_shortName = newStrTable.set(factory->getStringTable().get(m_shortName));
      oldAndNewStrKeyMap.insert(std::pair<Key,Key>(oldkey,m_shortName));    }

    foundKeyId = oldAndNewStrKeyMap.find(m_name);
    if (foundKeyId != oldAndNewStrKeyMap.end()) {
      m_name = foundKeyId->second;
    } else {
      Key oldkey = m_name;
      m_name = newStrTable.set(factory->getStringTable().get(m_name));
      oldAndNewStrKeyMap.insert(std::pair<Key,Key>(oldkey,m_name));    }

  }

  NodeHashType Component::getHash(std::set<NodeId>& travNodes) const {
    if (hashOk) return nodeHashCache;
    common::WriteMsg::write(CMSG_GET_THE_NODE_HASH_OF_NODE_BEGIN,this->getId()); 
    if (travNodes.count(getId())>0) {
      common::WriteMsg::write(CMSG_GET_THE_NODE_HASH_OF_NODE_SKIP);
      return 0;
    }
    travNodes.insert(getId());
    Crc_type resultHash;
    resultHash.process_bytes( "base::Component", strlen("base::Component"));
    common::WriteMsg::write(CMSG_GET_THE_NODE_HASH_OF_NODE_END,resultHash.checksum()); 
    nodeHashCache = resultHash.checksum();
    hashOk = true;
    return nodeHashCache;
  }

  void Component::save(io::BinaryIO &binIo,bool withVirtualBase  /*= true*/) const {
    Named::save(binIo,false);

    binIo.writeUInt4(m_TLLOC);
    binIo.writeUInt4(m_TLOC);
    binIo.writeUByte1(m_analysisTime);
    factory->getStringTable().setType(m_changesetID, StrTable::strToSave);
    binIo.writeUInt4(m_changesetID);
    factory->getStringTable().setType(m_shortName, StrTable::strToSave);
    binIo.writeUInt4(m_shortName);


    for (ListIterator<physical::File>::Container::const_iterator it = compilationUnitContainer.begin(); it != compilationUnitContainer.end(); ++it) {
      binIo.writeUInt4(*it);
    }
    binIo.writeUInt4(0); // This is the end sign

    for (ListIterator<base::Component>::Container::const_iterator it = containsContainer.begin(); it != containsContainer.end(); ++it) {
      binIo.writeUInt4(*it);
    }
    binIo.writeUInt4(0); // This is the end sign

    for (ListIterator<physical::File>::Container::const_iterator it = hasFilesContainer.begin(); it != hasFilesContainer.end(); ++it) {
      binIo.writeUInt4(*it);
    }
    binIo.writeUInt4(0); // This is the end sign
  }

  void Component::load(io::BinaryIO &binIo, bool withVirtualBase /*= true*/) {
    Named::load(binIo,false);

    m_TLLOC = binIo.readUInt4();
    m_TLOC = binIo.readUInt4();
    m_analysisTime = (AnalysisTimeKind)binIo.readUByte1();
    m_changesetID = binIo.readUInt4();
    m_shortName = binIo.readUInt4();

    NodeId _id;

    _id = binIo.readUInt4();
    while (_id) {
      compilationUnitContainer.push_back(_id);
      _id = binIo.readUInt4();
    }

    _id = binIo.readUInt4();
    while (_id) {
      containsContainer.push_back(_id);
      _id = binIo.readUInt4();
    }

    _id = binIo.readUInt4();
    while (_id) {
      hasFilesContainer.push_back(_id);
      _id = binIo.readUInt4();
    }
  }


}


}}}
