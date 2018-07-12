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

  SwitchStatementClass::SwitchStatementClass(NodeId _id, Factory *_factory) :
    StructuralClone(_id, _factory),
    itemsContainer()
  {
  }

  SwitchStatementClass::~SwitchStatementClass() {
  }

  void SwitchStatementClass::prepareDelete(bool tryOnVirtualParent){
    while (!itemsContainer.empty()) {
      const NodeId id = *itemsContainer.begin();
      if (factory->getExistsReverseEdges())
        factory->reverseEdges->removeEdge(id, this->getId(), edkSwitchStatementClass_Items);
      itemsContainer.pop_front();
    }
    StructuralClone::prepareDelete(false);
  }

  NodeKind SwitchStatementClass::getNodeKind() const {
    return ndkSwitchStatementClass;
  }

  ListIterator<SwitchStatement> SwitchStatementClass::getItemsListIteratorBegin() const {
    return ListIterator<SwitchStatement>(&itemsContainer, factory, true);
  }

  ListIterator<SwitchStatement> SwitchStatementClass::getItemsListIteratorEnd() const {
    return ListIterator<SwitchStatement>(&itemsContainer, factory, false);
  }

  bool SwitchStatementClass::getItemsIsEmpty() const {
    return itemsContainer.empty();
  }

  unsigned int SwitchStatementClass::getItemsSize() const {
    return (unsigned int)itemsContainer.size();
  }

  bool SwitchStatementClass::setEdge(EdgeKind edgeKind, NodeId edgeEnd, bool tryOnVirtualParent) {
    switch (edgeKind) {
      case edkSwitchStatementClass_Items:
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

  bool SwitchStatementClass::removeEdge(EdgeKind edgeKind, NodeId edgeEnd, bool tryOnVirtualParent) {
    switch (edgeKind) {
      case edkSwitchStatementClass_Items:
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

  void SwitchStatementClass::addItems(const SwitchStatement *_node) {
    if (_node == NULL)
      throw GenealogyException(COLUMBUS_LOCATION, CMSG_EX_THE_NODE_IS_NULL);

    if (&(_node->getFactory()) != this->factory)
      throw GenealogyException(COLUMBUS_LOCATION, CMSG_EX_THE_FACTORY_OF_NODES_DOES_NOT_MATCH);

    if (!((_node->getNodeKind() == ndkSwitchStatement) ))
      throw GenealogyException(COLUMBUS_LOCATION, CMSG_EX_INVALID_NODE_KIND);

    itemsContainer.push_back(_node->getId());
    if (factory->reverseEdges)
      factory->reverseEdges->insertEdge(_node, this, edkSwitchStatementClass_Items);
  }

  void SwitchStatementClass::addItems(NodeId _id) {
    const SwitchStatement *node = dynamic_cast<SwitchStatement*>(factory->getPointer(_id));
    if (node == NULL)
      throw GenealogyException(COLUMBUS_LOCATION, CMSG_EX_INVALID_NODE_KIND);
    addItems( node );
  }

  void SwitchStatementClass::removeItems(NodeId id) {
    if (!factory->getExist(id))
      throw GenealogyException(COLUMBUS_LOCATION, CMSG_EX_THE_END_POINT_OF_THE_EDGE_DOES_NOT_EXIST);

    ListIterator<SwitchStatement>::Container::iterator it = find(itemsContainer.begin(), itemsContainer.end(), id);

    if (it == itemsContainer.end())
      throw GenealogyException(COLUMBUS_LOCATION, CMSG_EX_THE_END_POINT_OF_THE_EDGE_DOES_NOT_EXIST);

    itemsContainer.erase(it);

    if (factory->getExistsReverseEdges())
      factory->reverseEdges->removeEdge(id, this->getId(), edkSwitchStatementClass_Items);
  }

  void SwitchStatementClass::removeItems(SwitchStatement *_node) {
    if (_node == NULL)
      throw GenealogyException(COLUMBUS_LOCATION, CMSG_EX_THE_EDGE_IS_NULL);

    removeItems(_node->getId());
  }

  void SwitchStatementClass::accept(Visitor &visitor) const {
    visitor.visit(*this);
  }

  void SwitchStatementClass::acceptEnd(Visitor &visitor) const {
    visitor.visitEnd(*this);
  }

  double SwitchStatementClass::getSimilarity(const Base& base){
    if(base.getNodeKind() == getNodeKind()) {
      const SwitchStatementClass& node = dynamic_cast<const SwitchStatementClass&>(base);
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

  void SwitchStatementClass::swapStringTable(RefDistributorStrTable& newStrTable, std::map<Key,Key>& oldAndNewStrKeyMap ){
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

  NodeHashType SwitchStatementClass::getHash(std::set<NodeId>& travNodes) const {
    if (hashOk) return nodeHashCache;
    common::WriteMsg::write(CMSG_GET_THE_NODE_HASH_OF_NODE_BEGIN,this->getId()); 
    if (travNodes.count(getId())>0) {
      common::WriteMsg::write(CMSG_GET_THE_NODE_HASH_OF_NODE_SKIP);
      return 0;
    }
    travNodes.insert(getId());
    Crc_type resultHash;
    resultHash.process_bytes( "SwitchStatementClass", strlen("SwitchStatementClass"));
    common::WriteMsg::write(CMSG_GET_THE_NODE_HASH_OF_NODE_END,resultHash.checksum()); 
    nodeHashCache = resultHash.checksum();
    hashOk = true;
    return nodeHashCache;
  }

  void SwitchStatementClass::save(io::BinaryIO &binIo,bool withVirtualBase  /*= true*/) const {
    StructuralClone::save(binIo,false);


    for (ListIterator<SwitchStatement>::Container::const_iterator it = itemsContainer.begin(); it != itemsContainer.end(); ++it) {
      binIo.writeUInt4(*it);
    }
    binIo.writeUInt4(0); // This is the end sign
  }

  void SwitchStatementClass::load(io::BinaryIO &binIo, bool withVirtualBase /*= true*/) {
    StructuralClone::load(binIo,false);

    NodeId _id;

    _id = binIo.readUInt4();
    while (_id) {
      itemsContainer.push_back(_id);
      _id = binIo.readUInt4();
    }
  }



}}
