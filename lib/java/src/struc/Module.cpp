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

#include "java/inc/messages.h"
#include <algorithm>
#include <string.h>
#include "common/inc/math/common.h"
#include <sstream>


namespace columbus { namespace java { namespace asg {

typedef boost::crc_32_type  Crc_type;

namespace struc { 
  Module::Module(NodeId _id, Factory *_factory) :
         Base(_id, _factory),
    Named(_id, _factory),
    packagesContainer()
  {
  }

  Module::~Module() {
  }

  void Module::clone(const Module& other, bool tryOnVirtualParent) {
    if (tryOnVirtualParent) {
      base::Base::clone(other, false);
    }
    base::Named::clone(other, false);

    packagesContainer = other.packagesContainer;
  }

  void Module::prepareDelete(bool tryOnVirtualParent){
    while (!packagesContainer.empty()) {
      const NodeId id = *packagesContainer.begin();
      if (factory->getExistsReverseEdges())
        factory->reverseEdges->removeEdge(id, this->getId(), edkModule_Packages);
      packagesContainer.pop_front();
    }
    if (tryOnVirtualParent) {
      base::Base::prepareDelete(false);
    }
    base::Named::prepareDelete(false);
  }

  NodeKind Module::getNodeKind() const {
    return ndkModule;
  }

  ListIterator<struc::Package> Module::getPackagesListIteratorBegin() const {
    return ListIterator<struc::Package>(&packagesContainer, factory, true);
  }

  ListIterator<struc::Package> Module::getPackagesListIteratorEnd() const {
    return ListIterator<struc::Package>(&packagesContainer, factory, false);
  }

  bool Module::getPackagesIsEmpty() const {
    return getPackagesListIteratorBegin() == getPackagesListIteratorEnd();
  }

  unsigned int Module::getPackagesSize() const {
    unsigned int size = 0;
    ListIterator<struc::Package> endIt = getPackagesListIteratorEnd();
    for (ListIterator<struc::Package> it = getPackagesListIteratorBegin(); it != endIt; ++it) {
      ++size;
    }
    return size;
  }

  bool Module::setEdge(EdgeKind edgeKind, NodeId edgeEnd, bool tryOnVirtualParent) {
    switch (edgeKind) {
      case edkModule_Packages:
        addPackages(edgeEnd);
        return true;
      default:
        break;
    }
    if (tryOnVirtualParent) {
      if (base::Base::setEdge(edgeKind, edgeEnd, false)) {
        return true;
      }
    }
    if (base::Named::setEdge(edgeKind, edgeEnd, false)) {
      return true;
    }
    return false;
  }

  bool Module::removeEdge(EdgeKind edgeKind, NodeId edgeEnd, bool tryOnVirtualParent) {
    switch (edgeKind) {
      case edkModule_Packages:
        removePackages(edgeEnd);
        return true;
      default:
        break;
    }
    if (tryOnVirtualParent) {
      if (base::Base::removeEdge(edgeKind, edgeEnd, false)) {
        return true;
      }
    }
    if (base::Named::removeEdge(edgeKind, edgeEnd, false)) {
      return true;
    }
    return false;
  }

  void Module::addPackages(const struc::Package *_node) {
    if (_node == NULL)
      throw JavaException(COLUMBUS_LOCATION, CMSG_EX_THE_NODE_IS_NULL);

    if (&(_node->getFactory()) != this->factory)
      throw JavaException(COLUMBUS_LOCATION, CMSG_EX_THE_FACTORY_OF_NODES_DOES_NOT_MATCH);

    if (!((_node->getNodeKind() == ndkPackage) ))
      throw JavaException(COLUMBUS_LOCATION, CMSG_EX_INVALID_NODE_KIND);

    packagesContainer.push_back(_node->getId());
    if (factory->reverseEdges)
      factory->reverseEdges->insertEdge(_node, this, edkModule_Packages);
  }

  void Module::addPackages(NodeId _id) {
    const struc::Package *node = dynamic_cast<struc::Package*>(factory->getPointer(_id));
    if (node == NULL)
      throw JavaException(COLUMBUS_LOCATION, CMSG_EX_INVALID_NODE_KIND);
    addPackages( node );
  }

  void Module::removePackages(NodeId id) {
    if (!factory->getExist(id))
      throw JavaException(COLUMBUS_LOCATION, CMSG_EX_THE_END_POINT_OF_THE_EDGE_DOES_NOT_EXIST);

    ListIterator<struc::Package>::Container::iterator it = find(packagesContainer.begin(), packagesContainer.end(), id);

    if (it == packagesContainer.end())
      throw JavaException(COLUMBUS_LOCATION, CMSG_EX_THE_END_POINT_OF_THE_EDGE_DOES_NOT_EXIST);

    packagesContainer.erase(it);

    if (factory->getExistsReverseEdges())
      factory->reverseEdges->removeEdge(id, this->getId(), edkModule_Packages);
  }

  void Module::removePackages(struc::Package *_node) {
    if (_node == NULL)
      throw JavaException(COLUMBUS_LOCATION, CMSG_EX_THE_EDGE_IS_NULL);

    removePackages(_node->getId());
  }

  void Module::accept(Visitor &visitor) const {
    visitor.visit(*this);
  }

  void Module::acceptEnd(Visitor &visitor) const {
    visitor.visitEnd(*this);
  }

  double Module::getSimilarity(const base::Base& base){
    if(base.getNodeKind() == getNodeKind()) {
      const Module& node = dynamic_cast<const Module&>(base);
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

  void Module::swapStringTable(RefDistributorStrTable& newStrTable, std::map<Key,Key>& oldAndNewStrKeyMap ){
    std::map<Key,Key>::iterator foundKeyId;

    foundKeyId = oldAndNewStrKeyMap.find(m_name);
    if (foundKeyId != oldAndNewStrKeyMap.end()) {
      m_name = foundKeyId->second;
    } else {
      Key oldkey = m_name;
      m_name = newStrTable.set(factory->getStringTable().get(m_name));
      oldAndNewStrKeyMap.insert(std::pair<Key,Key>(oldkey,m_name));    }

  }

  NodeHashType Module::getHash(std::set<NodeId>& travNodes) const {
    if (hashOk) return nodeHashCache;
    common::WriteMsg::write(CMSG_GET_THE_NODE_HASH_OF_NODE_BEGIN,this->getId()); 
    if (travNodes.count(getId())>0) {
      common::WriteMsg::write(CMSG_GET_THE_NODE_HASH_OF_NODE_SKIP);
      return 0;
    }
    travNodes.insert(getId());
    Crc_type resultHash;
    resultHash.process_bytes( "struc::Module", strlen("struc::Module"));
    common::WriteMsg::write(CMSG_GET_THE_NODE_HASH_OF_NODE_END,resultHash.checksum()); 
    nodeHashCache = resultHash.checksum();
    hashOk = true;
    return nodeHashCache;
  }

  void Module::sort(bool withVirtualBase /* = true */) {
    if (withVirtualBase)
      Base::sort(false);
    Named::sort(false);
  }

  void Module::save(io::BinaryIO &binIo,bool withVirtualBase  /*= true*/) const {
    if (withVirtualBase)
      Base::save(binIo,false);

    Named::save(binIo,false);


    for (ListIterator<struc::Package>::Container::const_iterator it = packagesContainer.begin(); it != packagesContainer.end(); ++it) {
      binIo.writeUInt4(*it);
    }
    binIo.writeUInt4(0); // This is the end sign
  }

  void Module::load(io::BinaryIO &binIo, bool withVirtualBase /*= true*/) {
    if (withVirtualBase)
      Base::load(binIo, false);

    Named::load(binIo,false);

    NodeId _id;

    _id = binIo.readUInt4();
    while (_id) {
      packagesContainer.push_back(_id);
      _id = binIo.readUInt4();
    }
  }


}


}}}
