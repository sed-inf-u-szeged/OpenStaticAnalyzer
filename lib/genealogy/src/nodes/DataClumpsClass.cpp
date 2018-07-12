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

  DataClumpsClass::DataClumpsClass(NodeId _id, Factory *_factory) :
    StructuralClone(_id, _factory),
    itemsContainer()
  {
  }

  DataClumpsClass::~DataClumpsClass() {
  }

  void DataClumpsClass::prepareDelete(bool tryOnVirtualParent){
    while (!itemsContainer.empty()) {
      const NodeId id = *itemsContainer.begin();
      if (factory->getExistsReverseEdges())
        factory->reverseEdges->removeEdge(id, this->getId(), edkDataClumpsClass_Items);
      itemsContainer.pop_front();
    }
    StructuralClone::prepareDelete(false);
  }

  NodeKind DataClumpsClass::getNodeKind() const {
    return ndkDataClumpsClass;
  }

  ListIterator<DataClumps> DataClumpsClass::getItemsListIteratorBegin() const {
    return ListIterator<DataClumps>(&itemsContainer, factory, true);
  }

  ListIterator<DataClumps> DataClumpsClass::getItemsListIteratorEnd() const {
    return ListIterator<DataClumps>(&itemsContainer, factory, false);
  }

  bool DataClumpsClass::getItemsIsEmpty() const {
    return itemsContainer.empty();
  }

  unsigned int DataClumpsClass::getItemsSize() const {
    return (unsigned int)itemsContainer.size();
  }

  bool DataClumpsClass::setEdge(EdgeKind edgeKind, NodeId edgeEnd, bool tryOnVirtualParent) {
    switch (edgeKind) {
      case edkDataClumpsClass_Items:
        addItems(edgeEnd);
        return true;
      default:
        break;
    }
    if (StructuralClone::setEdge(edgeKind, edgeEnd, false)) {
      return true;
    }
    return false;
  }

  bool DataClumpsClass::removeEdge(EdgeKind edgeKind, NodeId edgeEnd, bool tryOnVirtualParent) {
    switch (edgeKind) {
      case edkDataClumpsClass_Items:
        removeItems(edgeEnd);
        return true;
      default:
        break;
    }
    if (StructuralClone::removeEdge(edgeKind, edgeEnd, false)) {
      return true;
    }
    return false;
  }

  void DataClumpsClass::addItems(const DataClumps *_node) {
    if (_node == NULL)
      throw GenealogyException(COLUMBUS_LOCATION, CMSG_EX_THE_NODE_IS_NULL);

    if (&(_node->getFactory()) != this->factory)
      throw GenealogyException(COLUMBUS_LOCATION, CMSG_EX_THE_FACTORY_OF_NODES_DOES_NOT_MATCH);

    if (!((_node->getNodeKind() == ndkDataClumps) ))
      throw GenealogyException(COLUMBUS_LOCATION, CMSG_EX_INVALID_NODE_KIND);

    itemsContainer.push_back(_node->getId());
    if (factory->reverseEdges)
      factory->reverseEdges->insertEdge(_node, this, edkDataClumpsClass_Items);
  }

  void DataClumpsClass::addItems(NodeId _id) {
    const DataClumps *node = dynamic_cast<DataClumps*>(factory->getPointer(_id));
    if (node == NULL)
      throw GenealogyException(COLUMBUS_LOCATION, CMSG_EX_INVALID_NODE_KIND);
    addItems( node );
  }

  void DataClumpsClass::removeItems(NodeId id) {
    if (!factory->getExist(id))
      throw GenealogyException(COLUMBUS_LOCATION, CMSG_EX_THE_END_POINT_OF_THE_EDGE_DOES_NOT_EXIST);

    ListIterator<DataClumps>::Container::iterator it = find(itemsContainer.begin(), itemsContainer.end(), id);

    if (it == itemsContainer.end())
      throw GenealogyException(COLUMBUS_LOCATION, CMSG_EX_THE_END_POINT_OF_THE_EDGE_DOES_NOT_EXIST);

    itemsContainer.erase(it);

    if (factory->getExistsReverseEdges())
      factory->reverseEdges->removeEdge(id, this->getId(), edkDataClumpsClass_Items);
  }

  void DataClumpsClass::removeItems(DataClumps *_node) {
    if (_node == NULL)
      throw GenealogyException(COLUMBUS_LOCATION, CMSG_EX_THE_EDGE_IS_NULL);

    removeItems(_node->getId());
  }

  void DataClumpsClass::accept(Visitor &visitor) const {
    visitor.visit(*this);
  }

  void DataClumpsClass::acceptEnd(Visitor &visitor) const {
    visitor.visitEnd(*this);
  }

  double DataClumpsClass::getSimilarity(const Base& base){
    if(base.getNodeKind() == getNodeKind()) {
      const DataClumpsClass& node = dynamic_cast<const DataClumpsClass&>(base);
      double matchAttrs = 0;
      std::string str1, str2;
      size_t strMax;
      double strSim;
      str1 = getUniqueName();
      str2 = node.getUniqueName();
      strMax = std::max(str1.size(), str2.size());
      strSim = 1 - ((double)common::math::editDistance(str1, str2) / (strMax > 0 ? strMax : 1));
      if (strSim < Common::SimilarityMinForStrings)
        return 0.0;
      matchAttrs += strSim;
      str1 = getFullyQualifiedName();
      str2 = node.getFullyQualifiedName();
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

  void DataClumpsClass::swapStringTable(RefDistributorStrTable& newStrTable, std::map<Key,Key>& oldAndNewStrKeyMap ){
    std::map<Key,Key>::iterator foundKeyId;

    foundKeyId = oldAndNewStrKeyMap.find(m_uniqueName);
    if (foundKeyId != oldAndNewStrKeyMap.end()) {
      m_uniqueName = foundKeyId->second;
    } else {
      Key oldkey = m_uniqueName;
      m_uniqueName = newStrTable.set(factory->getStringTable().get(m_uniqueName));
      oldAndNewStrKeyMap.insert(std::pair<Key,Key>(oldkey,m_uniqueName));    }

    foundKeyId = oldAndNewStrKeyMap.find(m_fullyQualifiedName);
    if (foundKeyId != oldAndNewStrKeyMap.end()) {
      m_fullyQualifiedName = foundKeyId->second;
    } else {
      Key oldkey = m_fullyQualifiedName;
      m_fullyQualifiedName = newStrTable.set(factory->getStringTable().get(m_fullyQualifiedName));
      oldAndNewStrKeyMap.insert(std::pair<Key,Key>(oldkey,m_fullyQualifiedName));    }

  }

  NodeHashType DataClumpsClass::getHash(std::set<NodeId>& travNodes) const {
    if (hashOk) return nodeHashCache;
    common::WriteMsg::write(CMSG_GET_THE_NODE_HASH_OF_NODE_BEGIN,this->getId()); 
    if (travNodes.count(getId())>0) {
      common::WriteMsg::write(CMSG_GET_THE_NODE_HASH_OF_NODE_SKIP);
      return 0;
    }
    travNodes.insert(getId());
    Crc_type resultHash;
    resultHash.process_bytes( "DataClumpsClass", strlen("DataClumpsClass"));
    common::WriteMsg::write(CMSG_GET_THE_NODE_HASH_OF_NODE_END,resultHash.checksum()); 
    nodeHashCache = resultHash.checksum();
    hashOk = true;
    return nodeHashCache;
  }

  void DataClumpsClass::save(io::BinaryIO &binIo,bool withVirtualBase  /*= true*/) const {
    StructuralClone::save(binIo,false);


    for (ListIterator<DataClumps>::Container::const_iterator it = itemsContainer.begin(); it != itemsContainer.end(); ++it) {
      binIo.writeUInt4(*it);
    }
    binIo.writeUInt4(0); // This is the end sign
  }

  void DataClumpsClass::load(io::BinaryIO &binIo, bool withVirtualBase /*= true*/) {
    StructuralClone::load(binIo,false);

    NodeId _id;

    _id = binIo.readUInt4();
    while (_id) {
      itemsContainer.push_back(_id);
      _id = binIo.readUInt4();
    }
  }



}}
