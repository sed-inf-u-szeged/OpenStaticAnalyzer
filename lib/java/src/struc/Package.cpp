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

#include "java/inc/java.h"
#include "java/inc/Common.h"
#include "common/inc/WriteMessage.h"
#include "common/inc/StringSup.h"

#include "java/inc/messages.h"
#include <algorithm>
#include <string.h>
#include "common/inc/math/common.h"
#include <sstream>


namespace columbus { namespace java { namespace asg {

typedef boost::crc_32_type  Crc_type;

namespace struc { 
  Package::Package(NodeId _id, Factory *_factory) :
         Base(_id, _factory),
         Commentable(_id, _factory),
         Member(_id, _factory),
    Named(_id, _factory),
    Scope(_id, _factory),
    m_qualifiedName(0),
    hasCompilationUnitsContainer(),
    isInModuleContainer()
  {
  }

  Package::~Package() {
  }

  void Package::clone(const Package& other, bool tryOnVirtualParent) {
    if (tryOnVirtualParent) {
      base::Base::clone(other, false);
    }
    if (tryOnVirtualParent) {
      base::Commentable::clone(other, false);
    }
    if (tryOnVirtualParent) {
      struc::Member::clone(other, false);
    }
    base::Named::clone(other, false);
    struc::Scope::clone(other, false);

    m_qualifiedName = other.m_qualifiedName;
    hasCompilationUnitsContainer = other.hasCompilationUnitsContainer;
    isInModuleContainer = other.isInModuleContainer;
  }

  void Package::prepareDelete(bool tryOnVirtualParent){
    while (!hasCompilationUnitsContainer.empty()) {
      const NodeId id = *hasCompilationUnitsContainer.begin();
      removeParentEdge(id);
      if (factory->getExistsReverseEdges())
        factory->reverseEdges->removeEdge(id, this->getId(), edkPackage_HasCompilationUnits);
      hasCompilationUnitsContainer.pop_front();
    }
    while (!isInModuleContainer.empty()) {
      const NodeId id = *isInModuleContainer.begin();
      if (factory->getExistsReverseEdges())
        factory->reverseEdges->removeEdge(id, this->getId(), edkPackage_IsInModule);
      isInModuleContainer.pop_front();
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
    base::Named::prepareDelete(false);
    struc::Scope::prepareDelete(false);
  }

  NodeKind Package::getNodeKind() const {
    return ndkPackage;
  }

  Key Package::getQualifiedNameKey() const {
    return m_qualifiedName;
  }

  const std::string& Package::getQualifiedName() const {
    return factory->getStringTable().get(m_qualifiedName);
  }

  void Package::setQualifiedNameKey(Key _qualifiedName) {
    m_qualifiedName = _qualifiedName;
  }

  void Package::setQualifiedName(const std::string& _qualifiedName) {
    m_qualifiedName = factory->getStringTable().set(_qualifiedName);
  }

  ListIterator<struc::CompilationUnit> Package::getCompilationUnitsListIteratorBegin() const {
    return ListIterator<struc::CompilationUnit>(&hasCompilationUnitsContainer, factory, true);
  }

  ListIterator<struc::CompilationUnit> Package::getCompilationUnitsListIteratorEnd() const {
    return ListIterator<struc::CompilationUnit>(&hasCompilationUnitsContainer, factory, false);
  }

  bool Package::getCompilationUnitsIsEmpty() const {
    return getCompilationUnitsListIteratorBegin() == getCompilationUnitsListIteratorEnd();
  }

  unsigned int Package::getCompilationUnitsSize() const {
    unsigned int size = 0;
    ListIterator<struc::CompilationUnit> endIt = getCompilationUnitsListIteratorEnd();
    for (ListIterator<struc::CompilationUnit> it = getCompilationUnitsListIteratorBegin(); it != endIt; ++it) {
      ++size;
    }
    return size;
  }

  ListIterator<struc::Module> Package::getIsInModuleListIteratorBegin() const {
    return ListIterator<struc::Module>(&isInModuleContainer, factory, true);
  }

  ListIterator<struc::Module> Package::getIsInModuleListIteratorEnd() const {
    return ListIterator<struc::Module>(&isInModuleContainer, factory, false);
  }

  bool Package::getIsInModuleIsEmpty() const {
    return getIsInModuleListIteratorBegin() == getIsInModuleListIteratorEnd();
  }

  unsigned int Package::getIsInModuleSize() const {
    unsigned int size = 0;
    ListIterator<struc::Module> endIt = getIsInModuleListIteratorEnd();
    for (ListIterator<struc::Module> it = getIsInModuleListIteratorBegin(); it != endIt; ++it) {
      ++size;
    }
    return size;
  }

  bool Package::setEdge(EdgeKind edgeKind, NodeId edgeEnd, bool tryOnVirtualParent) {
    switch (edgeKind) {
      case edkPackage_HasCompilationUnits:
        addCompilationUnits(edgeEnd);
        return true;
      case edkPackage_IsInModule:
        addIsInModule(edgeEnd);
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
    if (base::Named::setEdge(edgeKind, edgeEnd, false)) {
      return true;
    }
    if (struc::Scope::setEdge(edgeKind, edgeEnd, false)) {
      return true;
    }
    return false;
  }

  bool Package::removeEdge(EdgeKind edgeKind, NodeId edgeEnd, bool tryOnVirtualParent) {
    switch (edgeKind) {
      case edkPackage_HasCompilationUnits:
        removeCompilationUnits(edgeEnd);
        return true;
      case edkPackage_IsInModule:
        removeIsInModule(edgeEnd);
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
    if (base::Named::removeEdge(edgeKind, edgeEnd, false)) {
      return true;
    }
    if (struc::Scope::removeEdge(edgeKind, edgeEnd, false)) {
      return true;
    }
    return false;
  }

  void Package::addCompilationUnits(const struc::CompilationUnit *_node) {
    if (_node == NULL)
      throw JavaException(COLUMBUS_LOCATION, CMSG_EX_THE_NODE_IS_NULL);

    if (&(_node->getFactory()) != this->factory)
      throw JavaException(COLUMBUS_LOCATION, CMSG_EX_THE_FACTORY_OF_NODES_DOES_NOT_MATCH);

    if (!((_node->getNodeKind() == ndkCompilationUnit) ))
      throw JavaException(COLUMBUS_LOCATION, CMSG_EX_INVALID_NODE_KIND);

    hasCompilationUnitsContainer.push_back(_node->getId());
    setParentEdge(_node,edkPackage_HasCompilationUnits);

    if (factory->reverseEdges)
      factory->reverseEdges->insertEdge(_node, this, edkPackage_HasCompilationUnits);
  }

  void Package::addCompilationUnits(NodeId _id) {
    const struc::CompilationUnit *node = dynamic_cast<struc::CompilationUnit*>(factory->getPointer(_id));
    if (node == NULL)
      throw JavaException(COLUMBUS_LOCATION, CMSG_EX_INVALID_NODE_KIND);
    addCompilationUnits( node );
  }

  void Package::removeCompilationUnits(NodeId id) {
    if (!factory->getExist(id))
      throw JavaException(COLUMBUS_LOCATION, CMSG_EX_THE_END_POINT_OF_THE_EDGE_DOES_NOT_EXIST);

    ListIterator<struc::CompilationUnit>::Container::iterator it = find(hasCompilationUnitsContainer.begin(), hasCompilationUnitsContainer.end(), id);

    if (it == hasCompilationUnitsContainer.end())
      throw JavaException(COLUMBUS_LOCATION, CMSG_EX_THE_END_POINT_OF_THE_EDGE_DOES_NOT_EXIST);

    hasCompilationUnitsContainer.erase(it);

    removeParentEdge(id);

    if (factory->getExistsReverseEdges())
      factory->reverseEdges->removeEdge(id, this->getId(), edkPackage_HasCompilationUnits);
  }

  void Package::removeCompilationUnits(struc::CompilationUnit *_node) {
    if (_node == NULL)
      throw JavaException(COLUMBUS_LOCATION, CMSG_EX_THE_EDGE_IS_NULL);

    removeCompilationUnits(_node->getId());
  }

  void Package::addIsInModule(const struc::Module *_node) {
    if (_node == NULL)
      throw JavaException(COLUMBUS_LOCATION, CMSG_EX_THE_NODE_IS_NULL);

    if (&(_node->getFactory()) != this->factory)
      throw JavaException(COLUMBUS_LOCATION, CMSG_EX_THE_FACTORY_OF_NODES_DOES_NOT_MATCH);

    if (!((_node->getNodeKind() == ndkModule) ))
      throw JavaException(COLUMBUS_LOCATION, CMSG_EX_INVALID_NODE_KIND);

    isInModuleContainer.push_back(_node->getId());
    if (factory->reverseEdges)
      factory->reverseEdges->insertEdge(_node, this, edkPackage_IsInModule);
  }

  void Package::addIsInModule(NodeId _id) {
    const struc::Module *node = dynamic_cast<struc::Module*>(factory->getPointer(_id));
    if (node == NULL)
      throw JavaException(COLUMBUS_LOCATION, CMSG_EX_INVALID_NODE_KIND);
    addIsInModule( node );
  }

  void Package::removeIsInModule(NodeId id) {
    if (!factory->getExist(id))
      throw JavaException(COLUMBUS_LOCATION, CMSG_EX_THE_END_POINT_OF_THE_EDGE_DOES_NOT_EXIST);

    ListIterator<struc::Module>::Container::iterator it = find(isInModuleContainer.begin(), isInModuleContainer.end(), id);

    if (it == isInModuleContainer.end())
      throw JavaException(COLUMBUS_LOCATION, CMSG_EX_THE_END_POINT_OF_THE_EDGE_DOES_NOT_EXIST);

    isInModuleContainer.erase(it);

    if (factory->getExistsReverseEdges())
      factory->reverseEdges->removeEdge(id, this->getId(), edkPackage_IsInModule);
  }

  void Package::removeIsInModule(struc::Module *_node) {
    if (_node == NULL)
      throw JavaException(COLUMBUS_LOCATION, CMSG_EX_THE_EDGE_IS_NULL);

    removeIsInModule(_node->getId());
  }

  void Package::accept(Visitor &visitor) const {
    visitor.visit(*this);
  }

  void Package::acceptEnd(Visitor &visitor) const {
    visitor.visitEnd(*this);
  }

  double Package::getSimilarity(const base::Base& base){
    if(base.getNodeKind() == getNodeKind()) {
      const Package& node = dynamic_cast<const Package&>(base);
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
      str1 = getQualifiedName();
      str2 = node.getQualifiedName();
      strMax = std::max(str1.size(), str2.size());
      strSim = 1 - ((double)common::math::editDistance(str1, str2) / (strMax > 0 ? strMax : 1));
      if (strSim < Common::SimilarityMinForStrings)
        return 0.0;
      matchAttrs += strSim;
      return matchAttrs / (2 / (1 - Common::SimilarityMinimum)) + Common::SimilarityMinimum;
    } else {
      return 0.0;
    }
  }

  void Package::swapStringTable(RefDistributorStrTable& newStrTable, std::map<Key,Key>& oldAndNewStrKeyMap ){
    std::map<Key,Key>::iterator foundKeyId;

    foundKeyId = oldAndNewStrKeyMap.find(m_qualifiedName);
    if (foundKeyId != oldAndNewStrKeyMap.end()) {
      m_qualifiedName = foundKeyId->second;
    } else {
      Key oldkey = m_qualifiedName;
      m_qualifiedName = newStrTable.set(factory->getStringTable().get(m_qualifiedName));
      oldAndNewStrKeyMap.insert(std::pair<Key,Key>(oldkey,m_qualifiedName));    }

    foundKeyId = oldAndNewStrKeyMap.find(m_name);
    if (foundKeyId != oldAndNewStrKeyMap.end()) {
      m_name = foundKeyId->second;
    } else {
      Key oldkey = m_name;
      m_name = newStrTable.set(factory->getStringTable().get(m_name));
      oldAndNewStrKeyMap.insert(std::pair<Key,Key>(oldkey,m_name));    }

  }

  NodeHashType Package::getHash(std::set<NodeId>& travNodes) const {
    if (hashOk) return nodeHashCache;
    common::WriteMsg::write(CMSG_GET_THE_NODE_HASH_OF_NODE_BEGIN,this->getId()); 
    if (travNodes.count(getId())>0) {
      common::WriteMsg::write(CMSG_GET_THE_NODE_HASH_OF_NODE_SKIP);
      return 0;
    }
    travNodes.insert(getId());
    Crc_type resultHash;
    resultHash.process_bytes( "struc::Package", strlen("struc::Package"));
    common::WriteMsg::write(CMSG_GET_THE_NODE_HASH_OF_NODE_END,resultHash.checksum()); 
    nodeHashCache = resultHash.checksum();
    hashOk = true;
    return nodeHashCache;
  }

  void Package::sort(bool withVirtualBase /* = true */) {
    if (withVirtualBase)
      Base::sort(false);
    if (withVirtualBase)
      Commentable::sort(false);
    if (withVirtualBase)
      Member::sort(false);
    Named::sort(false);
    Scope::sort(false);

    {
      std::map<std::string, NodeId> csUnameMap;
      std::map<std::string, std::set<NodeId>, common::case_insensitive_compare> edgeMap;
      std::map<std::string, std::set<NodeId>, common::case_insensitive_compare>::iterator emapit;
      ListIterator<struc::CompilationUnit>::Container::iterator eit, eit2;

      for (eit = hasCompilationUnitsContainer.begin(); eit != hasCompilationUnitsContainer.end(); ++eit) {
        std::string str = Common::getUniqueStringForSorting(factory->getRef(*eit));
        edgeMap[str].insert(*eit);
        std::pair<std::map<std::string, NodeId>::iterator, bool> unameRes = csUnameMap.insert(make_pair(str, *eit));
        if (!unameRes.second) {
          common::WriteMsg::write(CMSG_SORT_DUPLICATED_EDGE_NAMES_AT_NODE, "hasCompilationUnits", m_id, Common::toString(getNodeKind()).c_str(), str.c_str());
          common::WriteMsg::write(CMSG_SORT_DUPLICATED_EDGE_DATA, unameRes.first->second, Common::toString(factory->getNodeKind(unameRes.first->second)).c_str());
          common::WriteMsg::write(CMSG_SORT_DUPLICATED_EDGE_DATA, *eit, Common::toString(factory->getNodeKind(*eit)).c_str());
        }
      }

      for (emapit = edgeMap.begin(), eit = hasCompilationUnitsContainer.begin(); emapit != edgeMap.end(); ++emapit) {
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
      eit2 = hasCompilationUnitsContainer.end();
      if (eit != eit2) {
        hasCompilationUnitsContainer.erase(eit, eit2);
      }
    }

  }

  void Package::save(io::BinaryIO &binIo,bool withVirtualBase  /*= true*/) const {
    if (withVirtualBase)
      Base::save(binIo,false);

    if (withVirtualBase)
      Commentable::save(binIo,false);

    if (withVirtualBase)
      Member::save(binIo,false);

    Named::save(binIo,false);

    Scope::save(binIo,false);

    factory->getStringTable().setType(m_qualifiedName, StrTable::strToSave);
    binIo.writeUInt4(m_qualifiedName);


    for (ListIterator<struc::CompilationUnit>::Container::const_iterator it = hasCompilationUnitsContainer.begin(); it != hasCompilationUnitsContainer.end(); ++it) {
      binIo.writeUInt4(*it);
    }
    binIo.writeUInt4(0); // This is the end sign

    for (ListIterator<struc::Module>::Container::const_iterator it = isInModuleContainer.begin(); it != isInModuleContainer.end(); ++it) {
      binIo.writeUInt4(*it);
    }
    binIo.writeUInt4(0); // This is the end sign
  }

  void Package::load(io::BinaryIO &binIo, bool withVirtualBase /*= true*/) {
    if (withVirtualBase)
      Base::load(binIo, false);

    if (withVirtualBase)
      Commentable::load(binIo, false);

    if (withVirtualBase)
      Member::load(binIo, false);

    Named::load(binIo,false);

    Scope::load(binIo,false);

    m_qualifiedName = binIo.readUInt4();

    NodeId _id;

    _id = binIo.readUInt4();
    while (_id) {
      hasCompilationUnitsContainer.push_back(_id);
      setParentEdge(factory->getPointer(_id),edkPackage_HasCompilationUnits);
      _id = binIo.readUInt4();
    }

    _id = binIo.readUInt4();
    while (_id) {
      isInModuleContainer.push_back(_id);
      _id = binIo.readUInt4();
    }
  }


}


}}}
