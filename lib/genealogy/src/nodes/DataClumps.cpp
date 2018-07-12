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

  DataClumps::DataClumps(NodeId _id, Factory *_factory) :
    StructuralClone(_id, _factory),
    m_kind(dckNone),
    m_dataClumpsClass(0),
    itemsContainer()
  {
  }

  DataClumps::~DataClumps() {
  }

  void DataClumps::prepareDelete(bool tryOnVirtualParent){
    removeDataClumpsClass();
    while (!itemsContainer.empty()) {
      const NodeId id = *itemsContainer.begin();
      removeParentEdge(id);
      if (factory->getExistsReverseEdges())
        factory->reverseEdges->removeEdge(id, this->getId(), edkDataClumps_Items);
      itemsContainer.pop_front();
    }
    StructuralClone::prepareDelete(false);
  }

  NodeKind DataClumps::getNodeKind() const {
    return ndkDataClumps;
  }

  DataClumpsKind DataClumps::getKind() const {
    return m_kind;
  }

  void DataClumps::setKind(DataClumpsKind _kind) {
    m_kind = _kind;
  }

  DataClumpsClass* DataClumps::getDataClumpsClass() const {
    DataClumpsClass *_node = NULL;
    if (m_dataClumpsClass != 0)
      _node = dynamic_cast<DataClumpsClass*>(factory->getPointer(m_dataClumpsClass));
    return _node;
  }

  ListIterator<DataElement> DataClumps::getItemsListIteratorBegin() const {
    return ListIterator<DataElement>(&itemsContainer, factory, true);
  }

  ListIterator<DataElement> DataClumps::getItemsListIteratorEnd() const {
    return ListIterator<DataElement>(&itemsContainer, factory, false);
  }

  bool DataClumps::getItemsIsEmpty() const {
    return itemsContainer.empty();
  }

  unsigned int DataClumps::getItemsSize() const {
    return (unsigned int)itemsContainer.size();
  }

  bool DataClumps::setEdge(EdgeKind edgeKind, NodeId edgeEnd, bool tryOnVirtualParent) {
    switch (edgeKind) {
      case edkDataClumps_DataClumpsClass:
        setDataClumpsClass(edgeEnd);
        return true;
      case edkDataClumps_Items:
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

  bool DataClumps::removeEdge(EdgeKind edgeKind, NodeId edgeEnd, bool tryOnVirtualParent) {
    switch (edgeKind) {
      case edkDataClumps_DataClumpsClass:
        removeDataClumpsClass();
        return true;
      case edkDataClumps_Items:
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

  void DataClumps::setDataClumpsClass(NodeId _id) {
    DataClumpsClass *_node = NULL;
    if (_id) {
      if (!factory->getExist(_id))
        throw GenealogyException(COLUMBUS_LOCATION, CMSG_EX_THE_END_POINT_OF_THE_EDGE_DOES_NOT_EXIST);

      _node = dynamic_cast<DataClumpsClass*> (factory->getPointer(_id));
      if ( _node == NULL) {
        throw GenealogyException(COLUMBUS_LOCATION, CMSG_EX_INVALID_NODE_KIND);
      }
      if (&(_node->getFactory()) != this->factory)
        throw GenealogyException(COLUMBUS_LOCATION, CMSG_EX_THE_FACTORY_OF_NODES_DOES_NOT_MATCH );

      if (m_dataClumpsClass) {
        if (factory->getExistsReverseEdges())
          factory->reverseEdges->removeEdge(m_dataClumpsClass, m_id, edkDataClumps_DataClumpsClass);
      }
      m_dataClumpsClass = _node->getId();
      if (factory->getExistsReverseEdges())
        factory->reverseEdges->insertEdge(m_dataClumpsClass, this->getId(), edkDataClumps_DataClumpsClass);
    } else {
      if (m_dataClumpsClass) {
        throw GenealogyException(COLUMBUS_LOCATION, CMSG_EX_CAN_T_SET_EDGE_TO_NULL);
      }
    }
  }

  void DataClumps::setDataClumpsClass(DataClumpsClass *_node) {
    if (_node == NULL)
      throw GenealogyException(COLUMBUS_LOCATION, CMSG_EX_CAN_T_SET_EDGE_TO_NULL);

    setDataClumpsClass(_node->getId());
  }

  void DataClumps::removeDataClumpsClass() {
      if (m_dataClumpsClass) {
        if (factory->getExistsReverseEdges())
          factory->reverseEdges->removeEdge(m_dataClumpsClass, m_id, edkDataClumps_DataClumpsClass);
      }
      m_dataClumpsClass = 0;
  }

  void DataClumps::addItems(const DataElement *_node) {
    if (_node == NULL)
      throw GenealogyException(COLUMBUS_LOCATION, CMSG_EX_THE_NODE_IS_NULL);

    if (&(_node->getFactory()) != this->factory)
      throw GenealogyException(COLUMBUS_LOCATION, CMSG_EX_THE_FACTORY_OF_NODES_DOES_NOT_MATCH);

    if (!((_node->getNodeKind() == ndkDataElement) ))
      throw GenealogyException(COLUMBUS_LOCATION, CMSG_EX_INVALID_NODE_KIND);

    itemsContainer.push_back(_node->getId());
    setParentEdge(_node,edkDataClumps_Items);

    if (factory->reverseEdges)
      factory->reverseEdges->insertEdge(_node, this, edkDataClumps_Items);
  }

  void DataClumps::addItems(NodeId _id) {
    const DataElement *node = dynamic_cast<DataElement*>(factory->getPointer(_id));
    if (node == NULL)
      throw GenealogyException(COLUMBUS_LOCATION, CMSG_EX_INVALID_NODE_KIND);
    addItems( node );
  }

  void DataClumps::removeItems(NodeId id) {
    if (!factory->getExist(id))
      throw GenealogyException(COLUMBUS_LOCATION, CMSG_EX_THE_END_POINT_OF_THE_EDGE_DOES_NOT_EXIST);

    ListIterator<DataElement>::Container::iterator it = find(itemsContainer.begin(), itemsContainer.end(), id);

    if (it == itemsContainer.end())
      throw GenealogyException(COLUMBUS_LOCATION, CMSG_EX_THE_END_POINT_OF_THE_EDGE_DOES_NOT_EXIST);

    itemsContainer.erase(it);

    removeParentEdge(id);

    if (factory->getExistsReverseEdges())
      factory->reverseEdges->removeEdge(id, this->getId(), edkDataClumps_Items);
  }

  void DataClumps::removeItems(DataElement *_node) {
    if (_node == NULL)
      throw GenealogyException(COLUMBUS_LOCATION, CMSG_EX_THE_EDGE_IS_NULL);

    removeItems(_node->getId());
  }

  void DataClumps::accept(Visitor &visitor) const {
    visitor.visit(*this);
  }

  void DataClumps::acceptEnd(Visitor &visitor) const {
    visitor.visitEnd(*this);
  }

  double DataClumps::getSimilarity(const Base& base){
    if(base.getNodeKind() == getNodeKind()) {
      const DataClumps& node = dynamic_cast<const DataClumps&>(base);
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
      if(node.getKind() == getKind()) ++matchAttrs;
      return matchAttrs / (3 / (1 - Common::SimilarityMinimum)) + Common::SimilarityMinimum;
    } else {
      return 0.0;
    }
  }

  void DataClumps::swapStringTable(RefDistributorStrTable& newStrTable, std::map<Key,Key>& oldAndNewStrKeyMap ){
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

  NodeHashType DataClumps::getHash(std::set<NodeId>& travNodes) const {
    if (hashOk) return nodeHashCache;
    common::WriteMsg::write(CMSG_GET_THE_NODE_HASH_OF_NODE_BEGIN,this->getId()); 
    if (travNodes.count(getId())>0) {
      common::WriteMsg::write(CMSG_GET_THE_NODE_HASH_OF_NODE_SKIP);
      return 0;
    }
    travNodes.insert(getId());
    Crc_type resultHash;
    resultHash.process_bytes( "DataClumps", strlen("DataClumps"));
    common::WriteMsg::write(CMSG_GET_THE_NODE_HASH_OF_NODE_END,resultHash.checksum()); 
    nodeHashCache = resultHash.checksum();
    hashOk = true;
    return nodeHashCache;
  }

  void DataClumps::save(io::BinaryIO &binIo,bool withVirtualBase  /*= true*/) const {
    StructuralClone::save(binIo,false);

    binIo.writeUByte1(m_kind);

    binIo.writeUInt4(m_dataClumpsClass);


    for (ListIterator<DataElement>::Container::const_iterator it = itemsContainer.begin(); it != itemsContainer.end(); ++it) {
      binIo.writeUInt4(*it);
    }
    binIo.writeUInt4(0); // This is the end sign
  }

  void DataClumps::load(io::BinaryIO &binIo, bool withVirtualBase /*= true*/) {
    StructuralClone::load(binIo,false);

    m_kind = (DataClumpsKind)binIo.readUByte1();

    m_dataClumpsClass =  binIo.readUInt4();

    NodeId _id;

    _id = binIo.readUInt4();
    while (_id) {
      itemsContainer.push_back(_id);
      setParentEdge(factory->getPointer(_id),edkDataClumps_Items);
      _id = binIo.readUInt4();
    }
  }



}}
