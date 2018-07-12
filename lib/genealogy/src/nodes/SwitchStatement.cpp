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

  SwitchStatement::SwitchStatement(NodeId _id, Factory *_factory) :
    StructuralClone(_id, _factory),
    m_hasDefaultLabel(false),
    m_switchStatementClass(0),
    itemsContainer()
  {
  }

  SwitchStatement::~SwitchStatement() {
  }

  void SwitchStatement::prepareDelete(bool tryOnVirtualParent){
    removeSwitchStatementClass();
    while (!itemsContainer.empty()) {
      const NodeId id = *itemsContainer.begin();
      removeParentEdge(id);
      if (factory->getExistsReverseEdges())
        factory->reverseEdges->removeEdge(id, this->getId(), edkSwitchStatement_Items);
      itemsContainer.pop_front();
    }
    StructuralClone::prepareDelete(false);
  }

  NodeKind SwitchStatement::getNodeKind() const {
    return ndkSwitchStatement;
  }

  bool SwitchStatement::getHasDefaultLabel() const {
    return m_hasDefaultLabel;
  }

  void SwitchStatement::setHasDefaultLabel(bool _hasDefaultLabel) {
    m_hasDefaultLabel = _hasDefaultLabel;
  }

  SwitchStatementClass* SwitchStatement::getSwitchStatementClass() const {
    SwitchStatementClass *_node = NULL;
    if (m_switchStatementClass != 0)
      _node = dynamic_cast<SwitchStatementClass*>(factory->getPointer(m_switchStatementClass));
    return _node;
  }

  ListIterator<CaseLabel> SwitchStatement::getItemsListIteratorBegin() const {
    return ListIterator<CaseLabel>(&itemsContainer, factory, true);
  }

  ListIterator<CaseLabel> SwitchStatement::getItemsListIteratorEnd() const {
    return ListIterator<CaseLabel>(&itemsContainer, factory, false);
  }

  bool SwitchStatement::getItemsIsEmpty() const {
    return itemsContainer.empty();
  }

  unsigned int SwitchStatement::getItemsSize() const {
    return (unsigned int)itemsContainer.size();
  }

  bool SwitchStatement::setEdge(EdgeKind edgeKind, NodeId edgeEnd, bool tryOnVirtualParent) {
    switch (edgeKind) {
      case edkSwitchStatement_SwitchStatementClass:
        setSwitchStatementClass(edgeEnd);
        return true;
      case edkSwitchStatement_Items:
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

  bool SwitchStatement::removeEdge(EdgeKind edgeKind, NodeId edgeEnd, bool tryOnVirtualParent) {
    switch (edgeKind) {
      case edkSwitchStatement_SwitchStatementClass:
        removeSwitchStatementClass();
        return true;
      case edkSwitchStatement_Items:
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

  void SwitchStatement::setSwitchStatementClass(NodeId _id) {
    SwitchStatementClass *_node = NULL;
    if (_id) {
      if (!factory->getExist(_id))
        throw GenealogyException(COLUMBUS_LOCATION, CMSG_EX_THE_END_POINT_OF_THE_EDGE_DOES_NOT_EXIST);

      _node = dynamic_cast<SwitchStatementClass*> (factory->getPointer(_id));
      if ( _node == NULL) {
        throw GenealogyException(COLUMBUS_LOCATION, CMSG_EX_INVALID_NODE_KIND);
      }
      if (&(_node->getFactory()) != this->factory)
        throw GenealogyException(COLUMBUS_LOCATION, CMSG_EX_THE_FACTORY_OF_NODES_DOES_NOT_MATCH );

      if (m_switchStatementClass) {
        if (factory->getExistsReverseEdges())
          factory->reverseEdges->removeEdge(m_switchStatementClass, m_id, edkSwitchStatement_SwitchStatementClass);
      }
      m_switchStatementClass = _node->getId();
      if (factory->getExistsReverseEdges())
        factory->reverseEdges->insertEdge(m_switchStatementClass, this->getId(), edkSwitchStatement_SwitchStatementClass);
    } else {
      if (m_switchStatementClass) {
        throw GenealogyException(COLUMBUS_LOCATION, CMSG_EX_CAN_T_SET_EDGE_TO_NULL);
      }
    }
  }

  void SwitchStatement::setSwitchStatementClass(SwitchStatementClass *_node) {
    if (_node == NULL)
      throw GenealogyException(COLUMBUS_LOCATION, CMSG_EX_CAN_T_SET_EDGE_TO_NULL);

    setSwitchStatementClass(_node->getId());
  }

  void SwitchStatement::removeSwitchStatementClass() {
      if (m_switchStatementClass) {
        if (factory->getExistsReverseEdges())
          factory->reverseEdges->removeEdge(m_switchStatementClass, m_id, edkSwitchStatement_SwitchStatementClass);
      }
      m_switchStatementClass = 0;
  }

  void SwitchStatement::addItems(const CaseLabel *_node) {
    if (_node == NULL)
      throw GenealogyException(COLUMBUS_LOCATION, CMSG_EX_THE_NODE_IS_NULL);

    if (&(_node->getFactory()) != this->factory)
      throw GenealogyException(COLUMBUS_LOCATION, CMSG_EX_THE_FACTORY_OF_NODES_DOES_NOT_MATCH);

    if (!((_node->getNodeKind() == ndkCaseLabel) ))
      throw GenealogyException(COLUMBUS_LOCATION, CMSG_EX_INVALID_NODE_KIND);

    itemsContainer.push_back(_node->getId());
    setParentEdge(_node,edkSwitchStatement_Items);

    if (factory->reverseEdges)
      factory->reverseEdges->insertEdge(_node, this, edkSwitchStatement_Items);
  }

  void SwitchStatement::addItems(NodeId _id) {
    const CaseLabel *node = dynamic_cast<CaseLabel*>(factory->getPointer(_id));
    if (node == NULL)
      throw GenealogyException(COLUMBUS_LOCATION, CMSG_EX_INVALID_NODE_KIND);
    addItems( node );
  }

  void SwitchStatement::removeItems(NodeId id) {
    if (!factory->getExist(id))
      throw GenealogyException(COLUMBUS_LOCATION, CMSG_EX_THE_END_POINT_OF_THE_EDGE_DOES_NOT_EXIST);

    ListIterator<CaseLabel>::Container::iterator it = find(itemsContainer.begin(), itemsContainer.end(), id);

    if (it == itemsContainer.end())
      throw GenealogyException(COLUMBUS_LOCATION, CMSG_EX_THE_END_POINT_OF_THE_EDGE_DOES_NOT_EXIST);

    itemsContainer.erase(it);

    removeParentEdge(id);

    if (factory->getExistsReverseEdges())
      factory->reverseEdges->removeEdge(id, this->getId(), edkSwitchStatement_Items);
  }

  void SwitchStatement::removeItems(CaseLabel *_node) {
    if (_node == NULL)
      throw GenealogyException(COLUMBUS_LOCATION, CMSG_EX_THE_EDGE_IS_NULL);

    removeItems(_node->getId());
  }

  void SwitchStatement::accept(Visitor &visitor) const {
    visitor.visit(*this);
  }

  void SwitchStatement::acceptEnd(Visitor &visitor) const {
    visitor.visitEnd(*this);
  }

  double SwitchStatement::getSimilarity(const Base& base){
    if(base.getNodeKind() == getNodeKind()) {
      const SwitchStatement& node = dynamic_cast<const SwitchStatement&>(base);
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
      if(node.getHasDefaultLabel() == getHasDefaultLabel()) ++matchAttrs;
      return matchAttrs / (3 / (1 - Common::SimilarityMinimum)) + Common::SimilarityMinimum;
    } else {
      return 0.0;
    }
  }

  void SwitchStatement::swapStringTable(RefDistributorStrTable& newStrTable, std::map<Key,Key>& oldAndNewStrKeyMap ){
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

  NodeHashType SwitchStatement::getHash(std::set<NodeId>& travNodes) const {
    if (hashOk) return nodeHashCache;
    common::WriteMsg::write(CMSG_GET_THE_NODE_HASH_OF_NODE_BEGIN,this->getId()); 
    if (travNodes.count(getId())>0) {
      common::WriteMsg::write(CMSG_GET_THE_NODE_HASH_OF_NODE_SKIP);
      return 0;
    }
    travNodes.insert(getId());
    Crc_type resultHash;
    resultHash.process_bytes( "SwitchStatement", strlen("SwitchStatement"));
    common::WriteMsg::write(CMSG_GET_THE_NODE_HASH_OF_NODE_END,resultHash.checksum()); 
    nodeHashCache = resultHash.checksum();
    hashOk = true;
    return nodeHashCache;
  }

  void SwitchStatement::save(io::BinaryIO &binIo,bool withVirtualBase  /*= true*/) const {
    StructuralClone::save(binIo,false);

    unsigned char boolValues = 0;
    boolValues <<= 1;
    if (m_hasDefaultLabel) 
      boolValues |= 1;
    binIo.writeUByte1(boolValues);

    binIo.writeUInt4(m_switchStatementClass);


    for (ListIterator<CaseLabel>::Container::const_iterator it = itemsContainer.begin(); it != itemsContainer.end(); ++it) {
      binIo.writeUInt4(*it);
    }
    binIo.writeUInt4(0); // This is the end sign
  }

  void SwitchStatement::load(io::BinaryIO &binIo, bool withVirtualBase /*= true*/) {
    StructuralClone::load(binIo,false);

    unsigned char boolValues = binIo.readUByte1();
    m_hasDefaultLabel = boolValues & 1;
    boolValues >>= 1;

    m_switchStatementClass =  binIo.readUInt4();

    NodeId _id;

    _id = binIo.readUInt4();
    while (_id) {
      itemsContainer.push_back(_id);
      setParentEdge(factory->getPointer(_id),edkSwitchStatement_Items);
      _id = binIo.readUInt4();
    }
  }



}}
