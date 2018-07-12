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

#include "python/inc/python.h"
#include "python/inc/Common.h"
#include "common/inc/WriteMessage.h"

#include "python/inc/messages.h"
#include <algorithm>
#include <string.h>
#include "common/inc/math/common.h"


namespace columbus { namespace python { namespace asg {

typedef boost::crc_32_type  Crc_type;

namespace module { 
  Package::Package(NodeId _id, Factory *_factory) :
    Base(_id, _factory),
    m_name(0),
    m_path(0),
    hasModuleContainer(),
    hasPackageContainer()
  {
  }

  Package::~Package() {
  }

  void Package::prepareDelete(bool tryOnVirtualParent){
    while (!hasModuleContainer.empty()) {
      const NodeId id = *hasModuleContainer.begin();
      removeParentEdge(id);
      if (factory->getExistsReverseEdges())
        factory->reverseEdges->removeEdge(id, this->getId(), edkPackage_HasModule);
      hasModuleContainer.pop_front();
    }
    while (!hasPackageContainer.empty()) {
      const NodeId id = *hasPackageContainer.begin();
      removeParentEdge(id);
      if (factory->getExistsReverseEdges())
        factory->reverseEdges->removeEdge(id, this->getId(), edkPackage_HasPackage);
      hasPackageContainer.pop_front();
    }
    base::Base::prepareDelete(false);
  }

  NodeKind Package::getNodeKind() const {
    return ndkPackage;
  }

  Key Package::getNameKey() const {
    return m_name;
  }

  const std::string& Package::getName() const {
    return factory->getStringTable().get(m_name);
  }

  Key Package::getPathKey() const {
    return m_path;
  }

  const std::string& Package::getPath() const {
    return factory->getStringTable().get(m_path);
  }

  void Package::setNameKey(Key _name) {
    m_name = _name;
  }

  void Package::setName(const std::string& _name) {
    m_name = factory->getStringTable().set(_name);
  }

  void Package::setPathKey(Key _path) {
    m_path = _path;
  }

  void Package::setPath(const std::string& _path) {
    m_path = factory->getStringTable().set(_path);
  }

  ListIterator<module::Module> Package::getModuleListIteratorBegin() const {
    return ListIterator<module::Module>(&hasModuleContainer, factory, true);
  }

  ListIterator<module::Module> Package::getModuleListIteratorEnd() const {
    return ListIterator<module::Module>(&hasModuleContainer, factory, false);
  }

  bool Package::getModuleIsEmpty() const {
    return getModuleListIteratorBegin() == getModuleListIteratorEnd();
  }

  unsigned int Package::getModuleSize() const {
    unsigned int size = 0;
    ListIterator<module::Module> endIt = getModuleListIteratorEnd();
    for (ListIterator<module::Module> it = getModuleListIteratorBegin(); it != endIt; ++it) {
      ++size;
    }
    return size;
  }

  ListIterator<module::Package> Package::getPackageListIteratorBegin() const {
    return ListIterator<module::Package>(&hasPackageContainer, factory, true);
  }

  ListIterator<module::Package> Package::getPackageListIteratorEnd() const {
    return ListIterator<module::Package>(&hasPackageContainer, factory, false);
  }

  bool Package::getPackageIsEmpty() const {
    return getPackageListIteratorBegin() == getPackageListIteratorEnd();
  }

  unsigned int Package::getPackageSize() const {
    unsigned int size = 0;
    ListIterator<module::Package> endIt = getPackageListIteratorEnd();
    for (ListIterator<module::Package> it = getPackageListIteratorBegin(); it != endIt; ++it) {
      ++size;
    }
    return size;
  }

  bool Package::setEdge(EdgeKind edgeKind, NodeId edgeEnd, bool tryOnVirtualParent) {
    switch (edgeKind) {
      case edkPackage_HasModule:
        addModule(edgeEnd);
        return true;
      case edkPackage_HasPackage:
        addPackage(edgeEnd);
        return true;
      default:
        break;
    }
    if (base::Base::setEdge(edgeKind, edgeEnd, false)) {
      return true;
    }
    return false;
  }

  bool Package::removeEdge(EdgeKind edgeKind, NodeId edgeEnd, bool tryOnVirtualParent) {
    switch (edgeKind) {
      case edkPackage_HasModule:
        removeModule(edgeEnd);
        return true;
      case edkPackage_HasPackage:
        removePackage(edgeEnd);
        return true;
      default:
        break;
    }
    if (base::Base::removeEdge(edgeKind, edgeEnd, false)) {
      return true;
    }
    return false;
  }

  void Package::addModule(const module::Module *_node) {
    if (_node == NULL)
      throw PythonException(COLUMBUS_LOCATION, CMSG_EX_THE_NODE_IS_NULL);

    if (&(_node->getFactory()) != this->factory)
      throw PythonException(COLUMBUS_LOCATION, CMSG_EX_THE_FACTORY_OF_NODES_DOES_NOT_MATCH);

    if (!((_node->getNodeKind() == ndkModule) ))
      throw PythonException(COLUMBUS_LOCATION, CMSG_EX_INVALID_NODE_KIND);

    hasModuleContainer.push_back(_node->getId());
    setParentEdge(_node,edkPackage_HasModule);

    if (factory->reverseEdges)
      factory->reverseEdges->insertEdge(_node, this, edkPackage_HasModule);
  }

  void Package::addModule(NodeId _id) {
    const module::Module *node = dynamic_cast<module::Module*>(factory->getPointer(_id));
    if (node == NULL)
      throw PythonException(COLUMBUS_LOCATION, CMSG_EX_INVALID_NODE_KIND);
    addModule( node );
  }

  void Package::removeModule(NodeId id) {
    if (!factory->getExist(id))
      throw PythonException(COLUMBUS_LOCATION, CMSG_EX_THE_END_POINT_OF_THE_EDGE_DOES_NOT_EXIST);

    ListIterator<module::Module>::Container::iterator it = find(hasModuleContainer.begin(), hasModuleContainer.end(), id);

    if (it == hasModuleContainer.end())
      throw PythonException(COLUMBUS_LOCATION, CMSG_EX_THE_END_POINT_OF_THE_EDGE_DOES_NOT_EXIST);

    hasModuleContainer.erase(it);

    removeParentEdge(id);

    if (factory->getExistsReverseEdges())
      factory->reverseEdges->removeEdge(id, this->getId(), edkPackage_HasModule);
  }

  void Package::removeModule(module::Module *_node) {
    if (_node == NULL)
      throw PythonException(COLUMBUS_LOCATION, CMSG_EX_THE_EDGE_IS_NULL);

    removeModule(_node->getId());
  }

  void Package::addPackage(const module::Package *_node) {
    if (_node == NULL)
      throw PythonException(COLUMBUS_LOCATION, CMSG_EX_THE_NODE_IS_NULL);

    if (&(_node->getFactory()) != this->factory)
      throw PythonException(COLUMBUS_LOCATION, CMSG_EX_THE_FACTORY_OF_NODES_DOES_NOT_MATCH);

    if (!((_node->getNodeKind() == ndkPackage) ))
      throw PythonException(COLUMBUS_LOCATION, CMSG_EX_INVALID_NODE_KIND);

    hasPackageContainer.push_back(_node->getId());
    setParentEdge(_node,edkPackage_HasPackage);

    if (factory->reverseEdges)
      factory->reverseEdges->insertEdge(_node, this, edkPackage_HasPackage);
  }

  void Package::addPackage(NodeId _id) {
    const module::Package *node = dynamic_cast<module::Package*>(factory->getPointer(_id));
    if (node == NULL)
      throw PythonException(COLUMBUS_LOCATION, CMSG_EX_INVALID_NODE_KIND);
    addPackage( node );
  }

  void Package::removePackage(NodeId id) {
    if (!factory->getExist(id))
      throw PythonException(COLUMBUS_LOCATION, CMSG_EX_THE_END_POINT_OF_THE_EDGE_DOES_NOT_EXIST);

    ListIterator<module::Package>::Container::iterator it = find(hasPackageContainer.begin(), hasPackageContainer.end(), id);

    if (it == hasPackageContainer.end())
      throw PythonException(COLUMBUS_LOCATION, CMSG_EX_THE_END_POINT_OF_THE_EDGE_DOES_NOT_EXIST);

    hasPackageContainer.erase(it);

    removeParentEdge(id);

    if (factory->getExistsReverseEdges())
      factory->reverseEdges->removeEdge(id, this->getId(), edkPackage_HasPackage);
  }

  void Package::removePackage(module::Package *_node) {
    if (_node == NULL)
      throw PythonException(COLUMBUS_LOCATION, CMSG_EX_THE_EDGE_IS_NULL);

    removePackage(_node->getId());
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
      str1 = getPath();
      str2 = node.getPath();
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

    foundKeyId = oldAndNewStrKeyMap.find(m_name);
    if (foundKeyId != oldAndNewStrKeyMap.end()) {
      m_name = foundKeyId->second;
    } else {
      Key oldkey = m_name;
      m_name = newStrTable.set(factory->getStringTable().get(m_name));
      oldAndNewStrKeyMap.insert(std::pair<Key,Key>(oldkey,m_name));    }

    foundKeyId = oldAndNewStrKeyMap.find(m_path);
    if (foundKeyId != oldAndNewStrKeyMap.end()) {
      m_path = foundKeyId->second;
    } else {
      Key oldkey = m_path;
      m_path = newStrTable.set(factory->getStringTable().get(m_path));
      oldAndNewStrKeyMap.insert(std::pair<Key,Key>(oldkey,m_path));    }

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
    resultHash.process_bytes( "module::Package", strlen("module::Package"));
    common::WriteMsg::write(CMSG_GET_THE_NODE_HASH_OF_NODE_END,resultHash.checksum()); 
    nodeHashCache = resultHash.checksum();
    hashOk = true;
    return nodeHashCache;
  }

  void Package::save(io::BinaryIO &binIo,bool withVirtualBase  /*= true*/) const {
    Base::save(binIo,false);

    factory->getStringTable().setType(m_name, StrTable::strToSave);
    binIo.writeUInt4(m_name);
    factory->getStringTable().setType(m_path, StrTable::strToSave);
    binIo.writeUInt4(m_path);


    for (ListIterator<module::Module>::Container::const_iterator it = hasModuleContainer.begin(); it != hasModuleContainer.end(); ++it) {
      binIo.writeUInt4(*it);
    }
    binIo.writeUInt4(0); // This is the end sign

    for (ListIterator<module::Package>::Container::const_iterator it = hasPackageContainer.begin(); it != hasPackageContainer.end(); ++it) {
      binIo.writeUInt4(*it);
    }
    binIo.writeUInt4(0); // This is the end sign
  }

  void Package::load(io::BinaryIO &binIo, bool withVirtualBase /*= true*/) {
    Base::load(binIo,false);

    m_name = binIo.readUInt4();
    m_path = binIo.readUInt4();

    NodeId _id;

    _id = binIo.readUInt4();
    while (_id) {
      hasModuleContainer.push_back(_id);
      setParentEdge(factory->getPointer(_id),edkPackage_HasModule);
      _id = binIo.readUInt4();
    }

    _id = binIo.readUInt4();
    while (_id) {
      hasPackageContainer.push_back(_id);
      setParentEdge(factory->getPointer(_id),edkPackage_HasPackage);
      _id = binIo.readUInt4();
    }
  }


}


}}}
