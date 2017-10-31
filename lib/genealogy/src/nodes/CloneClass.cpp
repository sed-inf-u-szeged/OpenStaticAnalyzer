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

#include "genealogy/inc/genealogy.h"
#include "genealogy/inc/Common.h"
#include "common/inc/WriteMessage.h"

#include "genealogy/inc/messages.h"
#include <algorithm>
#include <string.h>
#include "common/inc/math/common.h"


namespace columbus { namespace genealogy { 

typedef boost::crc_32_type  Crc_type;

  CloneClass::CloneClass(NodeId _id, Factory *_factory) :
    Clone(_id, _factory),
    m_instances(0),
    m_length(0),
    m_headNodeKind(0),
    m_cvCiSmells(0),
    m_ca(0),
    m_cco(0),
    m_ce(0),
    m_type(ctkType1),
    m_fingerprint(0),
    m_risk(0.0),
    m_gain(0.0),
    m_effort(0.0),
    m_clloc(0.0),
    m_cv(0.0),
    m_ncrad(0.0),
    nextNeighboursContainer(),
    prevNeighboursContainer(),
    itemsContainer()
  {
  }

  CloneClass::~CloneClass() {
  }

  void CloneClass::prepareDelete(bool tryOnVirtualParent){
    while (!nextNeighboursContainer.empty()) {
      const NodeId id = *nextNeighboursContainer.begin();
      if (factory->getExistsReverseEdges())
        factory->reverseEdges->removeEdge(id, this->getId(), edkCloneClass_NextNeighbours);
      nextNeighboursContainer.pop_front();
    }
    while (!prevNeighboursContainer.empty()) {
      const NodeId id = *prevNeighboursContainer.begin();
      if (factory->getExistsReverseEdges())
        factory->reverseEdges->removeEdge(id, this->getId(), edkCloneClass_PrevNeighbours);
      prevNeighboursContainer.pop_front();
    }
    while (!itemsContainer.empty()) {
      const NodeId id = *itemsContainer.begin();
      removeParentEdge(id);
      if (factory->getExistsReverseEdges())
        factory->reverseEdges->removeEdge(id, this->getId(), edkCloneClass_Items);
      itemsContainer.pop_front();
    }
    Clone::prepareDelete(false);
  }

  NodeKind CloneClass::getNodeKind() const {
    return ndkCloneClass;
  }

  Key CloneClass::getFingerprintKey() const {
    return m_fingerprint;
  }

  const std::string& CloneClass::getFingerprint() const {
    return factory->getStringTable().get(m_fingerprint);
  }

  unsigned CloneClass::getInstances() const {
    return m_instances;
  }

  unsigned CloneClass::getLength() const {
    return m_length;
  }

  unsigned CloneClass::getHeadNodeKind() const {
    return m_headNodeKind;
  }

  unsigned CloneClass::getCvCiSmells() const {
    return m_cvCiSmells;
  }

  unsigned CloneClass::getCa() const {
    return m_ca;
  }

  double CloneClass::getRisk() const {
    return m_risk;
  }

  double CloneClass::getGain() const {
    return m_gain;
  }

  double CloneClass::getEffort() const {
    return m_effort;
  }

  unsigned CloneClass::getCco() const {
    return m_cco;
  }

  unsigned CloneClass::getCe() const {
    return m_ce;
  }

  double CloneClass::getClloc() const {
    return m_clloc;
  }

  double CloneClass::getCv() const {
    return m_cv;
  }

  double CloneClass::getNcrad() const {
    return m_ncrad;
  }

  CloneType CloneClass::getType() const {
    return m_type;
  }

  void CloneClass::setFingerprintKey(Key _fingerprint) {
    m_fingerprint = _fingerprint;
  }

  void CloneClass::setFingerprint(const std::string& _fingerprint) {
    m_fingerprint = factory->getStringTable().set(_fingerprint);
  }

  void CloneClass::setInstances(unsigned _instances) {
    m_instances = _instances;
  }

  void CloneClass::setLength(unsigned _length) {
    m_length = _length;
  }

  void CloneClass::setHeadNodeKind(unsigned _headNodeKind) {
    m_headNodeKind = _headNodeKind;
  }

  void CloneClass::setCvCiSmells(unsigned _cvCiSmells) {
    m_cvCiSmells = _cvCiSmells;
  }

  void CloneClass::setCa(unsigned _ca) {
    m_ca = _ca;
  }

  void CloneClass::setRisk(double _risk) {
    m_risk = _risk;
  }

  void CloneClass::setGain(double _gain) {
    m_gain = _gain;
  }

  void CloneClass::setEffort(double _effort) {
    m_effort = _effort;
  }

  void CloneClass::setCco(unsigned _cco) {
    m_cco = _cco;
  }

  void CloneClass::setCe(unsigned _ce) {
    m_ce = _ce;
  }

  void CloneClass::setClloc(double _clloc) {
    m_clloc = _clloc;
  }

  void CloneClass::setCv(double _cv) {
    m_cv = _cv;
  }

  void CloneClass::setNcrad(double _ncrad) {
    m_ncrad = _ncrad;
  }

  void CloneClass::setType(CloneType _type) {
    m_type = _type;
  }

  ListIterator<CloneClass> CloneClass::getNextNeighboursListIteratorBegin() const {
    return ListIterator<CloneClass>(&nextNeighboursContainer, factory, true);
  }

  ListIterator<CloneClass> CloneClass::getNextNeighboursListIteratorEnd() const {
    return ListIterator<CloneClass>(&nextNeighboursContainer, factory, false);
  }

  bool CloneClass::getNextNeighboursIsEmpty() const {
    return nextNeighboursContainer.empty();
  }

  unsigned int CloneClass::getNextNeighboursSize() const {
    return (unsigned int)nextNeighboursContainer.size();
  }

  ListIterator<CloneClass> CloneClass::getPrevNeighboursListIteratorBegin() const {
    return ListIterator<CloneClass>(&prevNeighboursContainer, factory, true);
  }

  ListIterator<CloneClass> CloneClass::getPrevNeighboursListIteratorEnd() const {
    return ListIterator<CloneClass>(&prevNeighboursContainer, factory, false);
  }

  bool CloneClass::getPrevNeighboursIsEmpty() const {
    return prevNeighboursContainer.empty();
  }

  unsigned int CloneClass::getPrevNeighboursSize() const {
    return (unsigned int)prevNeighboursContainer.size();
  }

  ListIterator<CloneInstance> CloneClass::getItemsListIteratorBegin() const {
    return ListIterator<CloneInstance>(&itemsContainer, factory, true);
  }

  ListIterator<CloneInstance> CloneClass::getItemsListIteratorEnd() const {
    return ListIterator<CloneInstance>(&itemsContainer, factory, false);
  }

  bool CloneClass::getItemsIsEmpty() const {
    return itemsContainer.empty();
  }

  unsigned int CloneClass::getItemsSize() const {
    return (unsigned int)itemsContainer.size();
  }

  bool CloneClass::setEdge(EdgeKind edgeKind, NodeId edgeEnd, bool tryOnVirtualParent) {
    switch (edgeKind) {
      case edkCloneClass_NextNeighbours:
        addNextNeighbours(edgeEnd);
        return true;
      case edkCloneClass_PrevNeighbours:
        addPrevNeighbours(edgeEnd);
        return true;
      case edkCloneClass_Items:
        addItems(edgeEnd);
        return true;
      default:
        break;
    }
    if (Clone::setEdge(edgeKind, edgeEnd, false)) {
      return true;
    }
    return false;
  }

  bool CloneClass::removeEdge(EdgeKind edgeKind, NodeId edgeEnd, bool tryOnVirtualParent) {
    switch (edgeKind) {
      case edkCloneClass_NextNeighbours:
        removeNextNeighbours(edgeEnd);
        return true;
      case edkCloneClass_PrevNeighbours:
        removePrevNeighbours(edgeEnd);
        return true;
      case edkCloneClass_Items:
        removeItems(edgeEnd);
        return true;
      default:
        break;
    }
    if (Clone::removeEdge(edgeKind, edgeEnd, false)) {
      return true;
    }
    return false;
  }

  void CloneClass::addNextNeighbours(const CloneClass *_node) {
    if (_node == NULL)
      throw GenealogyException(COLUMBUS_LOCATION, CMSG_EX_THE_NODE_IS_NULL);

    if (&(_node->getFactory()) != this->factory)
      throw GenealogyException(COLUMBUS_LOCATION, CMSG_EX_THE_FACTORY_OF_NODES_DOES_NOT_MATCH);

    if (!((_node->getNodeKind() == ndkCloneClass) ))
      throw GenealogyException(COLUMBUS_LOCATION, CMSG_EX_INVALID_NODE_KIND);

    nextNeighboursContainer.push_back(_node->getId());
    if (factory->reverseEdges)
      factory->reverseEdges->insertEdge(_node, this, edkCloneClass_NextNeighbours);
  }

  void CloneClass::addNextNeighbours(NodeId _id) {
    const CloneClass *node = dynamic_cast<CloneClass*>(factory->getPointer(_id));
    if (node == NULL)
      throw GenealogyException(COLUMBUS_LOCATION, CMSG_EX_INVALID_NODE_KIND);
    addNextNeighbours( node );
  }

  void CloneClass::removeNextNeighbours(NodeId id) {
    if (!factory->getExist(id))
      throw GenealogyException(COLUMBUS_LOCATION, CMSG_EX_THE_END_POINT_OF_THE_EDGE_DOES_NOT_EXIST);

    ListIterator<CloneClass>::Container::iterator it = find(nextNeighboursContainer.begin(), nextNeighboursContainer.end(), id);

    if (it == nextNeighboursContainer.end())
      throw GenealogyException(COLUMBUS_LOCATION, CMSG_EX_THE_END_POINT_OF_THE_EDGE_DOES_NOT_EXIST);

    nextNeighboursContainer.erase(it);

    if (factory->getExistsReverseEdges())
      factory->reverseEdges->removeEdge(id, this->getId(), edkCloneClass_NextNeighbours);
  }

  void CloneClass::removeNextNeighbours(CloneClass *_node) {
    if (_node == NULL)
      throw GenealogyException(COLUMBUS_LOCATION, CMSG_EX_THE_EDGE_IS_NULL);

    removeNextNeighbours(_node->getId());
  }

  void CloneClass::addPrevNeighbours(const CloneClass *_node) {
    if (_node == NULL)
      throw GenealogyException(COLUMBUS_LOCATION, CMSG_EX_THE_NODE_IS_NULL);

    if (&(_node->getFactory()) != this->factory)
      throw GenealogyException(COLUMBUS_LOCATION, CMSG_EX_THE_FACTORY_OF_NODES_DOES_NOT_MATCH);

    if (!((_node->getNodeKind() == ndkCloneClass) ))
      throw GenealogyException(COLUMBUS_LOCATION, CMSG_EX_INVALID_NODE_KIND);

    prevNeighboursContainer.push_back(_node->getId());
    if (factory->reverseEdges)
      factory->reverseEdges->insertEdge(_node, this, edkCloneClass_PrevNeighbours);
  }

  void CloneClass::addPrevNeighbours(NodeId _id) {
    const CloneClass *node = dynamic_cast<CloneClass*>(factory->getPointer(_id));
    if (node == NULL)
      throw GenealogyException(COLUMBUS_LOCATION, CMSG_EX_INVALID_NODE_KIND);
    addPrevNeighbours( node );
  }

  void CloneClass::removePrevNeighbours(NodeId id) {
    if (!factory->getExist(id))
      throw GenealogyException(COLUMBUS_LOCATION, CMSG_EX_THE_END_POINT_OF_THE_EDGE_DOES_NOT_EXIST);

    ListIterator<CloneClass>::Container::iterator it = find(prevNeighboursContainer.begin(), prevNeighboursContainer.end(), id);

    if (it == prevNeighboursContainer.end())
      throw GenealogyException(COLUMBUS_LOCATION, CMSG_EX_THE_END_POINT_OF_THE_EDGE_DOES_NOT_EXIST);

    prevNeighboursContainer.erase(it);

    if (factory->getExistsReverseEdges())
      factory->reverseEdges->removeEdge(id, this->getId(), edkCloneClass_PrevNeighbours);
  }

  void CloneClass::removePrevNeighbours(CloneClass *_node) {
    if (_node == NULL)
      throw GenealogyException(COLUMBUS_LOCATION, CMSG_EX_THE_EDGE_IS_NULL);

    removePrevNeighbours(_node->getId());
  }

  void CloneClass::addItems(const CloneInstance *_node) {
    if (_node == NULL)
      throw GenealogyException(COLUMBUS_LOCATION, CMSG_EX_THE_NODE_IS_NULL);

    if (&(_node->getFactory()) != this->factory)
      throw GenealogyException(COLUMBUS_LOCATION, CMSG_EX_THE_FACTORY_OF_NODES_DOES_NOT_MATCH);

    if (!((_node->getNodeKind() == ndkCloneInstance) ))
      throw GenealogyException(COLUMBUS_LOCATION, CMSG_EX_INVALID_NODE_KIND);

    itemsContainer.push_back(_node->getId());
    setParentEdge(_node,edkCloneClass_Items);

    if (factory->reverseEdges)
      factory->reverseEdges->insertEdge(_node, this, edkCloneClass_Items);
  }

  void CloneClass::addItems(NodeId _id) {
    const CloneInstance *node = dynamic_cast<CloneInstance*>(factory->getPointer(_id));
    if (node == NULL)
      throw GenealogyException(COLUMBUS_LOCATION, CMSG_EX_INVALID_NODE_KIND);
    addItems( node );
  }

  void CloneClass::removeItems(NodeId id) {
    if (!factory->getExist(id))
      throw GenealogyException(COLUMBUS_LOCATION, CMSG_EX_THE_END_POINT_OF_THE_EDGE_DOES_NOT_EXIST);

    ListIterator<CloneInstance>::Container::iterator it = find(itemsContainer.begin(), itemsContainer.end(), id);

    if (it == itemsContainer.end())
      throw GenealogyException(COLUMBUS_LOCATION, CMSG_EX_THE_END_POINT_OF_THE_EDGE_DOES_NOT_EXIST);

    itemsContainer.erase(it);

    removeParentEdge(id);

    if (factory->getExistsReverseEdges())
      factory->reverseEdges->removeEdge(id, this->getId(), edkCloneClass_Items);
  }

  void CloneClass::removeItems(CloneInstance *_node) {
    if (_node == NULL)
      throw GenealogyException(COLUMBUS_LOCATION, CMSG_EX_THE_EDGE_IS_NULL);

    removeItems(_node->getId());
  }

  void CloneClass::accept(Visitor &visitor) const {
    visitor.visit(*this);
  }

  void CloneClass::acceptEnd(Visitor &visitor) const {
    visitor.visitEnd(*this);
  }

  double CloneClass::getSimilarity(const Base& base){
    if(base.getNodeKind() == getNodeKind()) {
      const CloneClass& node = dynamic_cast<const CloneClass&>(base);
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
      if(node.getCloneSmellType() == getCloneSmellType()) ++matchAttrs;
      if(node.getIsVirtual() == getIsVirtual()) ++matchAttrs;
      str1 = getFingerprint();
      str2 = node.getFingerprint();
      strMax = std::max(str1.size(), str2.size());
      strSim = 1 - ((double)common::math::editDistance(str1, str2) / (strMax > 0 ? strMax : 1));
      if (strSim < Common::SimilarityMinForStrings)
        return 0.0;
      matchAttrs += strSim;
      if(node.getInstances() == getInstances()) ++matchAttrs;
      if(node.getLength() == getLength()) ++matchAttrs;
      if(node.getHeadNodeKind() == getHeadNodeKind()) ++matchAttrs;
      if(node.getCvCiSmells() == getCvCiSmells()) ++matchAttrs;
      if(node.getCa() == getCa()) ++matchAttrs;
      if(node.getRisk() == getRisk()) ++matchAttrs;
      if(node.getGain() == getGain()) ++matchAttrs;
      if(node.getEffort() == getEffort()) ++matchAttrs;
      if(node.getCco() == getCco()) ++matchAttrs;
      if(node.getCe() == getCe()) ++matchAttrs;
      if(node.getClloc() == getClloc()) ++matchAttrs;
      if(node.getCv() == getCv()) ++matchAttrs;
      if(node.getNcrad() == getNcrad()) ++matchAttrs;
      if(node.getType() == getType()) ++matchAttrs;
      return matchAttrs / (18 / (1 - Common::SimilarityMinimum)) + Common::SimilarityMinimum;
    } else {
      return 0.0;
    }
  }

  void CloneClass::swapStringTable(RefDistributorStrTable& newStrTable, std::map<Key,Key>& oldAndNewStrKeyMap ){
    std::map<Key,Key>::iterator foundKeyId;

    foundKeyId = oldAndNewStrKeyMap.find(m_fingerprint);
    if (foundKeyId != oldAndNewStrKeyMap.end()) {
      m_fingerprint = foundKeyId->second;
    } else {
      Key oldkey = m_fingerprint;
      m_fingerprint = newStrTable.set(factory->getStringTable().get(m_fingerprint));
      oldAndNewStrKeyMap.insert(std::pair<Key,Key>(oldkey,m_fingerprint));    }

    foundKeyId = oldAndNewStrKeyMap.find(m_uniqueName);
    if (foundKeyId != oldAndNewStrKeyMap.end()) {
      m_uniqueName = foundKeyId->second;
    } else {
      Key oldkey = m_uniqueName;
      m_uniqueName = newStrTable.set(factory->getStringTable().get(m_uniqueName));
      oldAndNewStrKeyMap.insert(std::pair<Key,Key>(oldkey,m_uniqueName));    }

  }

  NodeHashType CloneClass::getHash(std::set<NodeId>& travNodes) const {
    if (hashOk) return nodeHashCache;
    common::WriteMsg::write(CMSG_GET_THE_NODE_HASH_OF_NODE_BEGIN,this->getId()); 
    if (travNodes.count(getId())>0) {
      common::WriteMsg::write(CMSG_GET_THE_NODE_HASH_OF_NODE_SKIP);
      return 0;
    }
    travNodes.insert(getId());
    Crc_type resultHash;
    resultHash.process_bytes( "CloneClass", strlen("CloneClass"));
    common::WriteMsg::write(CMSG_GET_THE_NODE_HASH_OF_NODE_END,resultHash.checksum()); 
    nodeHashCache = resultHash.checksum();
    hashOk = true;
    return nodeHashCache;
  }

  void CloneClass::save(io::BinaryIO &binIo,bool withVirtualBase  /*= true*/) const {
    Clone::save(binIo,false);

    factory->getStringTable().setType(m_fingerprint, StrTable::strToSave);
    binIo.writeUInt4(m_fingerprint);
    binIo.writeUInt4(m_instances);
    binIo.writeUInt4(m_length);
    binIo.writeUInt4(m_headNodeKind);
    binIo.writeUInt4(m_cvCiSmells);
    binIo.writeUInt4(m_ca);
    binIo.writeDouble8(m_risk);
    binIo.writeDouble8(m_gain);
    binIo.writeDouble8(m_effort);
    binIo.writeUInt4(m_cco);
    binIo.writeUInt4(m_ce);
    binIo.writeDouble8(m_clloc);
    binIo.writeDouble8(m_cv);
    binIo.writeDouble8(m_ncrad);
    binIo.writeUByte1(m_type);


    for (ListIterator<CloneClass>::Container::const_iterator it = nextNeighboursContainer.begin(); it != nextNeighboursContainer.end(); ++it) {
      binIo.writeUInt4(*it);
    }
    binIo.writeUInt4(0); // This is the end sign

    for (ListIterator<CloneClass>::Container::const_iterator it = prevNeighboursContainer.begin(); it != prevNeighboursContainer.end(); ++it) {
      binIo.writeUInt4(*it);
    }
    binIo.writeUInt4(0); // This is the end sign

    for (ListIterator<CloneInstance>::Container::const_iterator it = itemsContainer.begin(); it != itemsContainer.end(); ++it) {
      binIo.writeUInt4(*it);
    }
    binIo.writeUInt4(0); // This is the end sign
  }

  void CloneClass::load(io::BinaryIO &binIo, bool withVirtualBase /*= true*/) {
    Clone::load(binIo,false);

    m_fingerprint = binIo.readUInt4();
    m_instances = binIo.readUInt4();
    m_length = binIo.readUInt4();
    m_headNodeKind = binIo.readUInt4();
    m_cvCiSmells = binIo.readUInt4();
    m_ca = binIo.readUInt4();
    m_risk = binIo.readDouble8();
    m_gain = binIo.readDouble8();
    m_effort = binIo.readDouble8();
    m_cco = binIo.readUInt4();
    m_ce = binIo.readUInt4();
    m_clloc = binIo.readDouble8();
    m_cv = binIo.readDouble8();
    m_ncrad = binIo.readDouble8();
    m_type = (CloneType)binIo.readUByte1();

    NodeId _id;

    _id = binIo.readUInt4();
    while (_id) {
      nextNeighboursContainer.push_back(_id);
      _id = binIo.readUInt4();
    }

    _id = binIo.readUInt4();
    while (_id) {
      prevNeighboursContainer.push_back(_id);
      _id = binIo.readUInt4();
    }

    _id = binIo.readUInt4();
    while (_id) {
      itemsContainer.push_back(_id);
      setParentEdge(factory->getPointer(_id),edkCloneClass_Items);
      _id = binIo.readUInt4();
    }
  }



}}
