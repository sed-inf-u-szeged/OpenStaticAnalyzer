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

  Project::Project(NodeId _id, Factory *_factory) :
    Base(_id, _factory),
    m_project(0),
    systemsContainer()
  {
  }

  Project::~Project() {
  }

  void Project::prepareDelete(bool tryOnVirtualParent){
    while (!systemsContainer.empty()) {
      const NodeId id = *systemsContainer.begin();
      removeParentEdge(id);
      if (factory->getExistsReverseEdges())
        factory->reverseEdges->removeEdge(id, this->getId(), edkProject_Systems);
      systemsContainer.pop_front();
    }
    Base::prepareDelete(false);
  }

  NodeKind Project::getNodeKind() const {
    return ndkProject;
  }

  Key Project::getProjectKey() const {
    return m_project;
  }

  const std::string& Project::getProject() const {
    return factory->getStringTable().get(m_project);
  }

  void Project::setProjectKey(Key _project) {
    m_project = _project;
  }

  void Project::setProject(const std::string& _project) {
    m_project = factory->getStringTable().set(_project);
  }

  ListIterator<System> Project::getSystemsListIteratorBegin() const {
    return ListIterator<System>(&systemsContainer, factory, true);
  }

  ListIterator<System> Project::getSystemsListIteratorEnd() const {
    return ListIterator<System>(&systemsContainer, factory, false);
  }

  bool Project::getSystemsIsEmpty() const {
    return systemsContainer.empty();
  }

  unsigned int Project::getSystemsSize() const {
    return (unsigned int)systemsContainer.size();
  }

  bool Project::setEdge(EdgeKind edgeKind, NodeId edgeEnd, bool tryOnVirtualParent) {
    switch (edgeKind) {
      case edkProject_Systems:
        addSystems(edgeEnd);
        return true;
      default:
        break;
    }
    if (Base::setEdge(edgeKind, edgeEnd, false)) {
      return true;
    }
    return false;
  }

  bool Project::removeEdge(EdgeKind edgeKind, NodeId edgeEnd, bool tryOnVirtualParent) {
    switch (edgeKind) {
      case edkProject_Systems:
        removeSystems(edgeEnd);
        return true;
      default:
        break;
    }
    if (Base::removeEdge(edgeKind, edgeEnd, false)) {
      return true;
    }
    return false;
  }

  void Project::addSystems(const System *_node) {
    if (_node == NULL)
      throw GenealogyException(COLUMBUS_LOCATION, CMSG_EX_THE_NODE_IS_NULL);

    if (&(_node->getFactory()) != this->factory)
      throw GenealogyException(COLUMBUS_LOCATION, CMSG_EX_THE_FACTORY_OF_NODES_DOES_NOT_MATCH);

    if (!((_node->getNodeKind() == ndkSystem) ))
      throw GenealogyException(COLUMBUS_LOCATION, CMSG_EX_INVALID_NODE_KIND);

    systemsContainer.push_back(_node->getId());
    setParentEdge(_node,edkProject_Systems);

    if (factory->reverseEdges)
      factory->reverseEdges->insertEdge(_node, this, edkProject_Systems);
  }

  void Project::addSystems(NodeId _id) {
    const System *node = dynamic_cast<System*>(factory->getPointer(_id));
    if (node == NULL)
      throw GenealogyException(COLUMBUS_LOCATION, CMSG_EX_INVALID_NODE_KIND);
    addSystems( node );
  }

  void Project::removeSystems(NodeId id) {
    if (!factory->getExist(id))
      throw GenealogyException(COLUMBUS_LOCATION, CMSG_EX_THE_END_POINT_OF_THE_EDGE_DOES_NOT_EXIST);

    ListIterator<System>::Container::iterator it = find(systemsContainer.begin(), systemsContainer.end(), id);

    if (it == systemsContainer.end())
      throw GenealogyException(COLUMBUS_LOCATION, CMSG_EX_THE_END_POINT_OF_THE_EDGE_DOES_NOT_EXIST);

    systemsContainer.erase(it);

    removeParentEdge(id);

    if (factory->getExistsReverseEdges())
      factory->reverseEdges->removeEdge(id, this->getId(), edkProject_Systems);
  }

  void Project::removeSystems(System *_node) {
    if (_node == NULL)
      throw GenealogyException(COLUMBUS_LOCATION, CMSG_EX_THE_EDGE_IS_NULL);

    removeSystems(_node->getId());
  }

  void Project::accept(Visitor &visitor) const {
    visitor.visit(*this);
  }

  void Project::acceptEnd(Visitor &visitor) const {
    visitor.visitEnd(*this);
  }

  double Project::getSimilarity(const Base& base){
    if(base.getNodeKind() == getNodeKind()) {
      const Project& node = dynamic_cast<const Project&>(base);
      double matchAttrs = 0;
      std::string str1, str2;
      size_t strMax;
      double strSim;
      str1 = getProject();
      str2 = node.getProject();
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

  void Project::swapStringTable(RefDistributorStrTable& newStrTable, std::map<Key,Key>& oldAndNewStrKeyMap ){
    std::map<Key,Key>::iterator foundKeyId;

    foundKeyId = oldAndNewStrKeyMap.find(m_project);
    if (foundKeyId != oldAndNewStrKeyMap.end()) {
      m_project = foundKeyId->second;
    } else {
      Key oldkey = m_project;
      m_project = newStrTable.set(factory->getStringTable().get(m_project));
      oldAndNewStrKeyMap.insert(std::pair<Key,Key>(oldkey,m_project));    }

  }

  NodeHashType Project::getHash(std::set<NodeId>& travNodes) const {
    if (hashOk) return nodeHashCache;
    common::WriteMsg::write(CMSG_GET_THE_NODE_HASH_OF_NODE_BEGIN,this->getId()); 
    if (travNodes.count(getId())>0) {
      common::WriteMsg::write(CMSG_GET_THE_NODE_HASH_OF_NODE_SKIP);
      return 0;
    }
    travNodes.insert(getId());
    Crc_type resultHash;
    resultHash.process_bytes( "Project", strlen("Project"));
    common::WriteMsg::write(CMSG_GET_THE_NODE_HASH_OF_NODE_END,resultHash.checksum()); 
    nodeHashCache = resultHash.checksum();
    hashOk = true;
    return nodeHashCache;
  }

  void Project::save(io::BinaryIO &binIo,bool withVirtualBase  /*= true*/) const {
    Base::save(binIo,false);

    factory->getStringTable().setType(m_project, StrTable::strToSave);
    binIo.writeUInt4(m_project);


    for (ListIterator<System>::Container::const_iterator it = systemsContainer.begin(); it != systemsContainer.end(); ++it) {
      binIo.writeUInt4(*it);
    }
    binIo.writeUInt4(0); // This is the end sign
  }

  void Project::load(io::BinaryIO &binIo, bool withVirtualBase /*= true*/) {
    Base::load(binIo,false);

    m_project = binIo.readUInt4();

    NodeId _id;

    _id = binIo.readUInt4();
    while (_id) {
      systemsContainer.push_back(_id);
      setParentEdge(factory->getPointer(_id),edkProject_Systems);
      _id = binIo.readUInt4();
    }
  }



}}
