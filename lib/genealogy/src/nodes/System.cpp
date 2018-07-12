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

  System::System(NodeId _id, Factory *_factory) :
    Trackable(_id, _factory),
    m_age(0),
    m_firstFreeID(0),
    m_version(0),
    m_name(0),
    m_limFileLocation(0),
    componentsContainer(),
    cloneClassesContainer(),
    smellsContainer(),
    m_next(0),
    m_prev(0)
  {
  }

  System::~System() {
  }

  void System::prepareDelete(bool tryOnVirtualParent){
    while (!componentsContainer.empty()) {
      const NodeId id = *componentsContainer.begin();
      removeParentEdge(id);
      if (factory->getExistsReverseEdges())
        factory->reverseEdges->removeEdge(id, this->getId(), edkSystem_Components);
      componentsContainer.pop_front();
    }
    while (!cloneClassesContainer.empty()) {
      const NodeId id = *cloneClassesContainer.begin();
      removeParentEdge(id);
      if (factory->getExistsReverseEdges())
        factory->reverseEdges->removeEdge(id, this->getId(), edkSystem_CloneClasses);
      cloneClassesContainer.pop_front();
    }
    while (!smellsContainer.empty()) {
      const NodeId id = *smellsContainer.begin();
      removeParentEdge(id);
      if (factory->getExistsReverseEdges())
        factory->reverseEdges->removeEdge(id, this->getId(), edkSystem_Smells);
      smellsContainer.pop_front();
    }
    removeNext();
    removePrev();
    Trackable::prepareDelete(false);
  }

  NodeKind System::getNodeKind() const {
    return ndkSystem;
  }

  unsigned System::getAge() const {
    return m_age;
  }

  Key System::getVersionKey() const {
    return m_version;
  }

  const std::string& System::getVersion() const {
    return factory->getStringTable().get(m_version);
  }

  Key System::getNameKey() const {
    return m_name;
  }

  const std::string& System::getName() const {
    return factory->getStringTable().get(m_name);
  }

  Key System::getLimFileLocationKey() const {
    return m_limFileLocation;
  }

  const std::string& System::getLimFileLocation() const {
    return factory->getStringTable().get(m_limFileLocation);
  }

  unsigned System::getFirstFreeID() const {
    return m_firstFreeID;
  }

  void System::setAge(unsigned _age) {
    m_age = _age;
  }

  void System::setVersionKey(Key _version) {
    m_version = _version;
  }

  void System::setVersion(const std::string& _version) {
    m_version = factory->getStringTable().set(_version);
  }

  void System::setNameKey(Key _name) {
    m_name = _name;
  }

  void System::setName(const std::string& _name) {
    m_name = factory->getStringTable().set(_name);
  }

  void System::setLimFileLocationKey(Key _limFileLocation) {
    m_limFileLocation = _limFileLocation;
  }

  void System::setLimFileLocation(const std::string& _limFileLocation) {
    m_limFileLocation = factory->getStringTable().set(_limFileLocation);
  }

  void System::setFirstFreeID(unsigned _firstFreeID) {
    m_firstFreeID = _firstFreeID;
  }

  ListIterator<Component> System::getComponentsListIteratorBegin() const {
    return ListIterator<Component>(&componentsContainer, factory, true);
  }

  ListIterator<Component> System::getComponentsListIteratorEnd() const {
    return ListIterator<Component>(&componentsContainer, factory, false);
  }

  bool System::getComponentsIsEmpty() const {
    return componentsContainer.empty();
  }

  unsigned int System::getComponentsSize() const {
    return (unsigned int)componentsContainer.size();
  }

  ListIterator<CloneClass> System::getCloneClassesListIteratorBegin() const {
    return ListIterator<CloneClass>(&cloneClassesContainer, factory, true);
  }

  ListIterator<CloneClass> System::getCloneClassesListIteratorEnd() const {
    return ListIterator<CloneClass>(&cloneClassesContainer, factory, false);
  }

  bool System::getCloneClassesIsEmpty() const {
    return cloneClassesContainer.empty();
  }

  unsigned int System::getCloneClassesSize() const {
    return (unsigned int)cloneClassesContainer.size();
  }

  ListIterator<StructuralClone> System::getSmellsListIteratorBegin() const {
    return ListIterator<StructuralClone>(&smellsContainer, factory, true);
  }

  ListIterator<StructuralClone> System::getSmellsListIteratorEnd() const {
    return ListIterator<StructuralClone>(&smellsContainer, factory, false);
  }

  bool System::getSmellsIsEmpty() const {
    return smellsContainer.empty();
  }

  unsigned int System::getSmellsSize() const {
    return (unsigned int)smellsContainer.size();
  }

  System* System::getNext() const {
    System *_node = NULL;
    if (m_next != 0)
      _node = dynamic_cast<System*>(factory->getPointer(m_next));
    return _node;
  }

  System* System::getPrev() const {
    System *_node = NULL;
    if (m_prev != 0)
      _node = dynamic_cast<System*>(factory->getPointer(m_prev));
    return _node;
  }

  bool System::setEdge(EdgeKind edgeKind, NodeId edgeEnd, bool tryOnVirtualParent) {
    switch (edgeKind) {
      case edkSystem_Components:
        addComponents(edgeEnd);
        return true;
      case edkSystem_CloneClasses:
        addCloneClasses(edgeEnd);
        return true;
      case edkSystem_Smells:
        addSmells(edgeEnd);
        return true;
      case edkSystem_Next:
        setNext(edgeEnd);
        return true;
      case edkSystem_Prev:
        setPrev(edgeEnd);
        return true;
      default:
        break;
    }
    if (Trackable::setEdge(edgeKind, edgeEnd, false)) {
      return true;
    }
    return false;
  }

  bool System::removeEdge(EdgeKind edgeKind, NodeId edgeEnd, bool tryOnVirtualParent) {
    switch (edgeKind) {
      case edkSystem_Components:
        removeComponents(edgeEnd);
        return true;
      case edkSystem_CloneClasses:
        removeCloneClasses(edgeEnd);
        return true;
      case edkSystem_Smells:
        removeSmells(edgeEnd);
        return true;
      case edkSystem_Next:
        removeNext();
        return true;
      case edkSystem_Prev:
        removePrev();
        return true;
      default:
        break;
    }
    if (Trackable::removeEdge(edgeKind, edgeEnd, false)) {
      return true;
    }
    return false;
  }

  void System::addComponents(const Component *_node) {
    if (_node == NULL)
      throw GenealogyException(COLUMBUS_LOCATION, CMSG_EX_THE_NODE_IS_NULL);

    if (&(_node->getFactory()) != this->factory)
      throw GenealogyException(COLUMBUS_LOCATION, CMSG_EX_THE_FACTORY_OF_NODES_DOES_NOT_MATCH);

    if (!((_node->getNodeKind() == ndkComponent) ))
      throw GenealogyException(COLUMBUS_LOCATION, CMSG_EX_INVALID_NODE_KIND);

    componentsContainer.push_back(_node->getId());
    setParentEdge(_node,edkSystem_Components);

    if (factory->reverseEdges)
      factory->reverseEdges->insertEdge(_node, this, edkSystem_Components);
  }

  void System::addComponents(NodeId _id) {
    const Component *node = dynamic_cast<Component*>(factory->getPointer(_id));
    if (node == NULL)
      throw GenealogyException(COLUMBUS_LOCATION, CMSG_EX_INVALID_NODE_KIND);
    addComponents( node );
  }

  void System::removeComponents(NodeId id) {
    if (!factory->getExist(id))
      throw GenealogyException(COLUMBUS_LOCATION, CMSG_EX_THE_END_POINT_OF_THE_EDGE_DOES_NOT_EXIST);

    ListIterator<Component>::Container::iterator it = find(componentsContainer.begin(), componentsContainer.end(), id);

    if (it == componentsContainer.end())
      throw GenealogyException(COLUMBUS_LOCATION, CMSG_EX_THE_END_POINT_OF_THE_EDGE_DOES_NOT_EXIST);

    componentsContainer.erase(it);

    removeParentEdge(id);

    if (factory->getExistsReverseEdges())
      factory->reverseEdges->removeEdge(id, this->getId(), edkSystem_Components);
  }

  void System::removeComponents(Component *_node) {
    if (_node == NULL)
      throw GenealogyException(COLUMBUS_LOCATION, CMSG_EX_THE_EDGE_IS_NULL);

    removeComponents(_node->getId());
  }

  void System::addCloneClasses(const CloneClass *_node) {
    if (_node == NULL)
      throw GenealogyException(COLUMBUS_LOCATION, CMSG_EX_THE_NODE_IS_NULL);

    if (&(_node->getFactory()) != this->factory)
      throw GenealogyException(COLUMBUS_LOCATION, CMSG_EX_THE_FACTORY_OF_NODES_DOES_NOT_MATCH);

    if (!((_node->getNodeKind() == ndkCloneClass) ))
      throw GenealogyException(COLUMBUS_LOCATION, CMSG_EX_INVALID_NODE_KIND);

    cloneClassesContainer.push_back(_node->getId());
    setParentEdge(_node,edkSystem_CloneClasses);

    if (factory->reverseEdges)
      factory->reverseEdges->insertEdge(_node, this, edkSystem_CloneClasses);
  }

  void System::addCloneClasses(NodeId _id) {
    const CloneClass *node = dynamic_cast<CloneClass*>(factory->getPointer(_id));
    if (node == NULL)
      throw GenealogyException(COLUMBUS_LOCATION, CMSG_EX_INVALID_NODE_KIND);
    addCloneClasses( node );
  }

  void System::removeCloneClasses(NodeId id) {
    if (!factory->getExist(id))
      throw GenealogyException(COLUMBUS_LOCATION, CMSG_EX_THE_END_POINT_OF_THE_EDGE_DOES_NOT_EXIST);

    ListIterator<CloneClass>::Container::iterator it = find(cloneClassesContainer.begin(), cloneClassesContainer.end(), id);

    if (it == cloneClassesContainer.end())
      throw GenealogyException(COLUMBUS_LOCATION, CMSG_EX_THE_END_POINT_OF_THE_EDGE_DOES_NOT_EXIST);

    cloneClassesContainer.erase(it);

    removeParentEdge(id);

    if (factory->getExistsReverseEdges())
      factory->reverseEdges->removeEdge(id, this->getId(), edkSystem_CloneClasses);
  }

  void System::removeCloneClasses(CloneClass *_node) {
    if (_node == NULL)
      throw GenealogyException(COLUMBUS_LOCATION, CMSG_EX_THE_EDGE_IS_NULL);

    removeCloneClasses(_node->getId());
  }

  void System::addSmells(const StructuralClone *_node) {
    if (_node == NULL)
      throw GenealogyException(COLUMBUS_LOCATION, CMSG_EX_THE_NODE_IS_NULL);

    if (&(_node->getFactory()) != this->factory)
      throw GenealogyException(COLUMBUS_LOCATION, CMSG_EX_THE_FACTORY_OF_NODES_DOES_NOT_MATCH);

    if (!(Common::getIsStructuralClone(*_node)))
      throw GenealogyException(COLUMBUS_LOCATION, CMSG_EX_INVALID_NODE_KIND);

    smellsContainer.push_back(_node->getId());
    setParentEdge(_node,edkSystem_Smells);

    if (factory->reverseEdges)
      factory->reverseEdges->insertEdge(_node, this, edkSystem_Smells);
  }

  void System::addSmells(NodeId _id) {
    const StructuralClone *node = dynamic_cast<StructuralClone*>(factory->getPointer(_id));
    if (node == NULL)
      throw GenealogyException(COLUMBUS_LOCATION, CMSG_EX_INVALID_NODE_KIND);
    addSmells( node );
  }

  void System::removeSmells(NodeId id) {
    if (!factory->getExist(id))
      throw GenealogyException(COLUMBUS_LOCATION, CMSG_EX_THE_END_POINT_OF_THE_EDGE_DOES_NOT_EXIST);

    ListIterator<StructuralClone>::Container::iterator it = find(smellsContainer.begin(), smellsContainer.end(), id);

    if (it == smellsContainer.end())
      throw GenealogyException(COLUMBUS_LOCATION, CMSG_EX_THE_END_POINT_OF_THE_EDGE_DOES_NOT_EXIST);

    smellsContainer.erase(it);

    removeParentEdge(id);

    if (factory->getExistsReverseEdges())
      factory->reverseEdges->removeEdge(id, this->getId(), edkSystem_Smells);
  }

  void System::removeSmells(StructuralClone *_node) {
    if (_node == NULL)
      throw GenealogyException(COLUMBUS_LOCATION, CMSG_EX_THE_EDGE_IS_NULL);

    removeSmells(_node->getId());
  }

  void System::setNext(NodeId _id) {
    System *_node = NULL;
    if (_id) {
      if (!factory->getExist(_id))
        throw GenealogyException(COLUMBUS_LOCATION, CMSG_EX_THE_END_POINT_OF_THE_EDGE_DOES_NOT_EXIST);

      _node = dynamic_cast<System*> (factory->getPointer(_id));
      if ( _node == NULL) {
        throw GenealogyException(COLUMBUS_LOCATION, CMSG_EX_INVALID_NODE_KIND);
      }
      if (&(_node->getFactory()) != this->factory)
        throw GenealogyException(COLUMBUS_LOCATION, CMSG_EX_THE_FACTORY_OF_NODES_DOES_NOT_MATCH );

      if (m_next) {
        if (factory->getExistsReverseEdges())
          factory->reverseEdges->removeEdge(m_next, m_id, edkSystem_Next);
      }
      m_next = _node->getId();
      if (factory->getExistsReverseEdges())
        factory->reverseEdges->insertEdge(m_next, this->getId(), edkSystem_Next);
    } else {
      if (m_next) {
        throw GenealogyException(COLUMBUS_LOCATION, CMSG_EX_CAN_T_SET_EDGE_TO_NULL);
      }
    }
  }

  void System::setNext(System *_node) {
    if (_node == NULL)
      throw GenealogyException(COLUMBUS_LOCATION, CMSG_EX_CAN_T_SET_EDGE_TO_NULL);

    setNext(_node->getId());
  }

  void System::removeNext() {
      if (m_next) {
        if (factory->getExistsReverseEdges())
          factory->reverseEdges->removeEdge(m_next, m_id, edkSystem_Next);
      }
      m_next = 0;
  }

  void System::setPrev(NodeId _id) {
    System *_node = NULL;
    if (_id) {
      if (!factory->getExist(_id))
        throw GenealogyException(COLUMBUS_LOCATION, CMSG_EX_THE_END_POINT_OF_THE_EDGE_DOES_NOT_EXIST);

      _node = dynamic_cast<System*> (factory->getPointer(_id));
      if ( _node == NULL) {
        throw GenealogyException(COLUMBUS_LOCATION, CMSG_EX_INVALID_NODE_KIND);
      }
      if (&(_node->getFactory()) != this->factory)
        throw GenealogyException(COLUMBUS_LOCATION, CMSG_EX_THE_FACTORY_OF_NODES_DOES_NOT_MATCH );

      if (m_prev) {
        if (factory->getExistsReverseEdges())
          factory->reverseEdges->removeEdge(m_prev, m_id, edkSystem_Prev);
      }
      m_prev = _node->getId();
      if (factory->getExistsReverseEdges())
        factory->reverseEdges->insertEdge(m_prev, this->getId(), edkSystem_Prev);
    } else {
      if (m_prev) {
        throw GenealogyException(COLUMBUS_LOCATION, CMSG_EX_CAN_T_SET_EDGE_TO_NULL);
      }
    }
  }

  void System::setPrev(System *_node) {
    if (_node == NULL)
      throw GenealogyException(COLUMBUS_LOCATION, CMSG_EX_CAN_T_SET_EDGE_TO_NULL);

    setPrev(_node->getId());
  }

  void System::removePrev() {
      if (m_prev) {
        if (factory->getExistsReverseEdges())
          factory->reverseEdges->removeEdge(m_prev, m_id, edkSystem_Prev);
      }
      m_prev = 0;
  }

  void System::accept(Visitor &visitor) const {
    visitor.visit(*this);
  }

  void System::acceptEnd(Visitor &visitor) const {
    visitor.visitEnd(*this);
  }

  double System::getSimilarity(const Base& base){
    if(base.getNodeKind() == getNodeKind()) {
      const System& node = dynamic_cast<const System&>(base);
      double matchAttrs = 0;
      if(node.getAge() == getAge()) ++matchAttrs;
      std::string str1, str2;
      size_t strMax;
      double strSim;
      str1 = getVersion();
      str2 = node.getVersion();
      strMax = std::max(str1.size(), str2.size());
      strSim = 1 - ((double)common::math::editDistance(str1, str2) / (strMax > 0 ? strMax : 1));
      if (strSim < Common::SimilarityMinForStrings)
        return 0.0;
      matchAttrs += strSim;
      str1 = getName();
      str2 = node.getName();
      strMax = std::max(str1.size(), str2.size());
      strSim = 1 - ((double)common::math::editDistance(str1, str2) / (strMax > 0 ? strMax : 1));
      if (strSim < Common::SimilarityMinForStrings)
        return 0.0;
      matchAttrs += strSim;
      str1 = getLimFileLocation();
      str2 = node.getLimFileLocation();
      strMax = std::max(str1.size(), str2.size());
      strSim = 1 - ((double)common::math::editDistance(str1, str2) / (strMax > 0 ? strMax : 1));
      if (strSim < Common::SimilarityMinForStrings)
        return 0.0;
      matchAttrs += strSim;
      if(node.getFirstFreeID() == getFirstFreeID()) ++matchAttrs;
      return matchAttrs / (5 / (1 - Common::SimilarityMinimum)) + Common::SimilarityMinimum;
    } else {
      return 0.0;
    }
  }

  void System::swapStringTable(RefDistributorStrTable& newStrTable, std::map<Key,Key>& oldAndNewStrKeyMap ){
    std::map<Key,Key>::iterator foundKeyId;

    foundKeyId = oldAndNewStrKeyMap.find(m_version);
    if (foundKeyId != oldAndNewStrKeyMap.end()) {
      m_version = foundKeyId->second;
    } else {
      Key oldkey = m_version;
      m_version = newStrTable.set(factory->getStringTable().get(m_version));
      oldAndNewStrKeyMap.insert(std::pair<Key,Key>(oldkey,m_version));    }

    foundKeyId = oldAndNewStrKeyMap.find(m_name);
    if (foundKeyId != oldAndNewStrKeyMap.end()) {
      m_name = foundKeyId->second;
    } else {
      Key oldkey = m_name;
      m_name = newStrTable.set(factory->getStringTable().get(m_name));
      oldAndNewStrKeyMap.insert(std::pair<Key,Key>(oldkey,m_name));    }

    foundKeyId = oldAndNewStrKeyMap.find(m_limFileLocation);
    if (foundKeyId != oldAndNewStrKeyMap.end()) {
      m_limFileLocation = foundKeyId->second;
    } else {
      Key oldkey = m_limFileLocation;
      m_limFileLocation = newStrTable.set(factory->getStringTable().get(m_limFileLocation));
      oldAndNewStrKeyMap.insert(std::pair<Key,Key>(oldkey,m_limFileLocation));    }

  }

  NodeHashType System::getHash(std::set<NodeId>& travNodes) const {
    if (hashOk) return nodeHashCache;
    common::WriteMsg::write(CMSG_GET_THE_NODE_HASH_OF_NODE_BEGIN,this->getId()); 
    if (travNodes.count(getId())>0) {
      common::WriteMsg::write(CMSG_GET_THE_NODE_HASH_OF_NODE_SKIP);
      return 0;
    }
    travNodes.insert(getId());
    Crc_type resultHash;
    resultHash.process_bytes( "System", strlen("System"));
    common::WriteMsg::write(CMSG_GET_THE_NODE_HASH_OF_NODE_END,resultHash.checksum()); 
    nodeHashCache = resultHash.checksum();
    hashOk = true;
    return nodeHashCache;
  }

  void System::save(io::BinaryIO &binIo,bool withVirtualBase  /*= true*/) const {
    Trackable::save(binIo,false);

    binIo.writeUInt4(m_age);
    factory->getStringTable().setType(m_version, StrTable::strToSave);
    binIo.writeUInt4(m_version);
    factory->getStringTable().setType(m_name, StrTable::strToSave);
    binIo.writeUInt4(m_name);
    factory->getStringTable().setType(m_limFileLocation, StrTable::strToSave);
    binIo.writeUInt4(m_limFileLocation);
    binIo.writeUInt4(m_firstFreeID);

    binIo.writeUInt4(m_next);
    binIo.writeUInt4(m_prev);


    for (ListIterator<Component>::Container::const_iterator it = componentsContainer.begin(); it != componentsContainer.end(); ++it) {
      binIo.writeUInt4(*it);
    }
    binIo.writeUInt4(0); // This is the end sign

    for (ListIterator<CloneClass>::Container::const_iterator it = cloneClassesContainer.begin(); it != cloneClassesContainer.end(); ++it) {
      binIo.writeUInt4(*it);
    }
    binIo.writeUInt4(0); // This is the end sign

    for (ListIterator<StructuralClone>::Container::const_iterator it = smellsContainer.begin(); it != smellsContainer.end(); ++it) {
      binIo.writeUInt4(*it);
    }
    binIo.writeUInt4(0); // This is the end sign
  }

  void System::load(io::BinaryIO &binIo, bool withVirtualBase /*= true*/) {
    Trackable::load(binIo,false);

    m_age = binIo.readUInt4();
    m_version = binIo.readUInt4();
    m_name = binIo.readUInt4();
    m_limFileLocation = binIo.readUInt4();
    m_firstFreeID = binIo.readUInt4();

    m_next =  binIo.readUInt4();

    m_prev =  binIo.readUInt4();

    NodeId _id;

    _id = binIo.readUInt4();
    while (_id) {
      componentsContainer.push_back(_id);
      setParentEdge(factory->getPointer(_id),edkSystem_Components);
      _id = binIo.readUInt4();
    }

    _id = binIo.readUInt4();
    while (_id) {
      cloneClassesContainer.push_back(_id);
      setParentEdge(factory->getPointer(_id),edkSystem_CloneClasses);
      _id = binIo.readUInt4();
    }

    _id = binIo.readUInt4();
    while (_id) {
      smellsContainer.push_back(_id);
      setParentEdge(factory->getPointer(_id),edkSystem_Smells);
      _id = binIo.readUInt4();
    }
  }



}}
