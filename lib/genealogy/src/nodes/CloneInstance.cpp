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

  CloneInstance::CloneInstance(NodeId _id, Factory *_factory) :
    Clone(_id, _factory),
    m_line(0),
    m_col(0),
    m_endLine(0),
    m_endCol(0),
    m_cvMetricVariability(0),
    m_ca(0),
    m_cco(0),
    m_ce(0),
    m_rootBegin(0),
    m_rootLength(0),
    m_F2_OrdinalNumber(0),
    m_F5_L1(0),
    m_F5_L2(0),
    m_F5_L3(0),
    m_path(0),
    m_cv(0.0),
    m_risk(0.0),
    m_rootNodes(0),
    m_F3_HeadNodeUniqueName(0),
    m_F4_AncestorUniqueName(0),
    m_F6_LexicalStructure(0),
    intersectsContainer(),
    m_component(0),
    m_cloneClass(0)
  {
  }

  CloneInstance::~CloneInstance() {
  }

  void CloneInstance::prepareDelete(bool tryOnVirtualParent){
    while (!intersectsContainer.empty()) {
      const NodeId id = *intersectsContainer.begin();
      if (factory->getExistsReverseEdges())
        factory->reverseEdges->removeEdge(id, this->getId(), edkCloneInstance_Intersects);
      intersectsContainer.pop_front();
    }
    removeComponent();
    removeCloneClass();
    Clone::prepareDelete(false);
  }

  NodeKind CloneInstance::getNodeKind() const {
    return ndkCloneInstance;
  }

  Key CloneInstance::getPathKey() const {
    return m_path;
  }

  const std::string& CloneInstance::getPath() const {
    return factory->getStringTable().get(m_path);
  }

  unsigned CloneInstance::getLine() const {
    return m_line;
  }

  unsigned CloneInstance::getCol() const {
    return m_col;
  }

  unsigned CloneInstance::getEndLine() const {
    return m_endLine;
  }

  unsigned CloneInstance::getEndCol() const {
    return m_endCol;
  }

  unsigned CloneInstance::getCvMetricVariability() const {
    return m_cvMetricVariability;
  }

  unsigned CloneInstance::getCa() const {
    return m_ca;
  }

  unsigned CloneInstance::getCco() const {
    return m_cco;
  }

  unsigned CloneInstance::getCe() const {
    return m_ce;
  }

  double CloneInstance::getCv() const {
    return m_cv;
  }

  double CloneInstance::getRisk() const {
    return m_risk;
  }

  Key CloneInstance::getRootNodesKey() const {
    return m_rootNodes;
  }

  const std::string& CloneInstance::getRootNodes() const {
    return factory->getStringTable().get(m_rootNodes);
  }

  unsigned CloneInstance::getRootBegin() const {
    return m_rootBegin;
  }

  unsigned CloneInstance::getRootLength() const {
    return m_rootLength;
  }

  unsigned CloneInstance::getF2_OrdinalNumber() const {
    return m_F2_OrdinalNumber;
  }

  Key CloneInstance::getF3_HeadNodeUniqueNameKey() const {
    return m_F3_HeadNodeUniqueName;
  }

  const std::string& CloneInstance::getF3_HeadNodeUniqueName() const {
    return factory->getStringTable().get(m_F3_HeadNodeUniqueName);
  }

  Key CloneInstance::getF4_AncestorUniqueNameKey() const {
    return m_F4_AncestorUniqueName;
  }

  const std::string& CloneInstance::getF4_AncestorUniqueName() const {
    return factory->getStringTable().get(m_F4_AncestorUniqueName);
  }

  unsigned CloneInstance::getF5_L1() const {
    return m_F5_L1;
  }

  unsigned CloneInstance::getF5_L2() const {
    return m_F5_L2;
  }

  unsigned CloneInstance::getF5_L3() const {
    return m_F5_L3;
  }

  Key CloneInstance::getF6_LexicalStructureKey() const {
    return m_F6_LexicalStructure;
  }

  const std::string& CloneInstance::getF6_LexicalStructure() const {
    return factory->getStringTable().get(m_F6_LexicalStructure);
  }

  void CloneInstance::setPathKey(Key _path) {
    m_path = _path;
  }

  void CloneInstance::setPath(const std::string& _path) {
    m_path = factory->getStringTable().set(_path);
  }

  void CloneInstance::setLine(unsigned _line) {
    m_line = _line;
  }

  void CloneInstance::setCol(unsigned _col) {
    m_col = _col;
  }

  void CloneInstance::setEndLine(unsigned _endLine) {
    m_endLine = _endLine;
  }

  void CloneInstance::setEndCol(unsigned _endCol) {
    m_endCol = _endCol;
  }

  void CloneInstance::setCvMetricVariability(unsigned _cvMetricVariability) {
    m_cvMetricVariability = _cvMetricVariability;
  }

  void CloneInstance::setCa(unsigned _ca) {
    m_ca = _ca;
  }

  void CloneInstance::setCco(unsigned _cco) {
    m_cco = _cco;
  }

  void CloneInstance::setCe(unsigned _ce) {
    m_ce = _ce;
  }

  void CloneInstance::setCv(double _cv) {
    m_cv = _cv;
  }

  void CloneInstance::setRisk(double _risk) {
    m_risk = _risk;
  }

  void CloneInstance::setRootNodesKey(Key _rootNodes) {
    m_rootNodes = _rootNodes;
  }

  void CloneInstance::setRootNodes(const std::string& _rootNodes) {
    m_rootNodes = factory->getStringTable().set(_rootNodes);
  }

  void CloneInstance::setRootBegin(unsigned _rootBegin) {
    m_rootBegin = _rootBegin;
  }

  void CloneInstance::setRootLength(unsigned _rootLength) {
    m_rootLength = _rootLength;
  }

  void CloneInstance::setF2_OrdinalNumber(unsigned _F2_OrdinalNumber) {
    m_F2_OrdinalNumber = _F2_OrdinalNumber;
  }

  void CloneInstance::setF3_HeadNodeUniqueNameKey(Key _F3_HeadNodeUniqueName) {
    m_F3_HeadNodeUniqueName = _F3_HeadNodeUniqueName;
  }

  void CloneInstance::setF3_HeadNodeUniqueName(const std::string& _F3_HeadNodeUniqueName) {
    m_F3_HeadNodeUniqueName = factory->getStringTable().set(_F3_HeadNodeUniqueName);
  }

  void CloneInstance::setF4_AncestorUniqueNameKey(Key _F4_AncestorUniqueName) {
    m_F4_AncestorUniqueName = _F4_AncestorUniqueName;
  }

  void CloneInstance::setF4_AncestorUniqueName(const std::string& _F4_AncestorUniqueName) {
    m_F4_AncestorUniqueName = factory->getStringTable().set(_F4_AncestorUniqueName);
  }

  void CloneInstance::setF5_L1(unsigned _F5_L1) {
    m_F5_L1 = _F5_L1;
  }

  void CloneInstance::setF5_L2(unsigned _F5_L2) {
    m_F5_L2 = _F5_L2;
  }

  void CloneInstance::setF5_L3(unsigned _F5_L3) {
    m_F5_L3 = _F5_L3;
  }

  void CloneInstance::setF6_LexicalStructureKey(Key _F6_LexicalStructure) {
    m_F6_LexicalStructure = _F6_LexicalStructure;
  }

  void CloneInstance::setF6_LexicalStructure(const std::string& _F6_LexicalStructure) {
    m_F6_LexicalStructure = factory->getStringTable().set(_F6_LexicalStructure);
  }

  ListIterator<CloneInstance> CloneInstance::getIntersectsListIteratorBegin() const {
    return ListIterator<CloneInstance>(&intersectsContainer, factory, true);
  }

  ListIterator<CloneInstance> CloneInstance::getIntersectsListIteratorEnd() const {
    return ListIterator<CloneInstance>(&intersectsContainer, factory, false);
  }

  bool CloneInstance::getIntersectsIsEmpty() const {
    return intersectsContainer.empty();
  }

  unsigned int CloneInstance::getIntersectsSize() const {
    return (unsigned int)intersectsContainer.size();
  }

  Component* CloneInstance::getComponent() const {
    Component *_node = NULL;
    if (m_component != 0)
      _node = dynamic_cast<Component*>(factory->getPointer(m_component));
    return _node;
  }

  CloneClass* CloneInstance::getCloneClass() const {
    CloneClass *_node = NULL;
    if (m_cloneClass != 0)
      _node = dynamic_cast<CloneClass*>(factory->getPointer(m_cloneClass));
    return _node;
  }

  bool CloneInstance::setEdge(EdgeKind edgeKind, NodeId edgeEnd, bool tryOnVirtualParent) {
    switch (edgeKind) {
      case edkCloneInstance_Intersects:
        addIntersects(edgeEnd);
        return true;
      case edkCloneInstance_Component:
        setComponent(edgeEnd);
        return true;
      case edkCloneInstance_CloneClass:
        setCloneClass(edgeEnd);
        return true;
      default:
        break;
    }
    if (Clone::setEdge(edgeKind, edgeEnd, false)) {
      return true;
    }
    return false;
  }

  bool CloneInstance::removeEdge(EdgeKind edgeKind, NodeId edgeEnd, bool tryOnVirtualParent) {
    switch (edgeKind) {
      case edkCloneInstance_Intersects:
        removeIntersects(edgeEnd);
        return true;
      case edkCloneInstance_Component:
        removeComponent();
        return true;
      case edkCloneInstance_CloneClass:
        removeCloneClass();
        return true;
      default:
        break;
    }
    if (Clone::removeEdge(edgeKind, edgeEnd, false)) {
      return true;
    }
    return false;
  }

  void CloneInstance::addIntersects(const CloneInstance *_node) {
    if (_node == NULL)
      throw GenealogyException(COLUMBUS_LOCATION, CMSG_EX_THE_NODE_IS_NULL);

    if (&(_node->getFactory()) != this->factory)
      throw GenealogyException(COLUMBUS_LOCATION, CMSG_EX_THE_FACTORY_OF_NODES_DOES_NOT_MATCH);

    if (!((_node->getNodeKind() == ndkCloneInstance) ))
      throw GenealogyException(COLUMBUS_LOCATION, CMSG_EX_INVALID_NODE_KIND);

    intersectsContainer.push_back(_node->getId());
    if (factory->reverseEdges)
      factory->reverseEdges->insertEdge(_node, this, edkCloneInstance_Intersects);
  }

  void CloneInstance::addIntersects(NodeId _id) {
    const CloneInstance *node = dynamic_cast<CloneInstance*>(factory->getPointer(_id));
    if (node == NULL)
      throw GenealogyException(COLUMBUS_LOCATION, CMSG_EX_INVALID_NODE_KIND);
    addIntersects( node );
  }

  void CloneInstance::removeIntersects(NodeId id) {
    if (!factory->getExist(id))
      throw GenealogyException(COLUMBUS_LOCATION, CMSG_EX_THE_END_POINT_OF_THE_EDGE_DOES_NOT_EXIST);

    ListIterator<CloneInstance>::Container::iterator it = find(intersectsContainer.begin(), intersectsContainer.end(), id);

    if (it == intersectsContainer.end())
      throw GenealogyException(COLUMBUS_LOCATION, CMSG_EX_THE_END_POINT_OF_THE_EDGE_DOES_NOT_EXIST);

    intersectsContainer.erase(it);

    if (factory->getExistsReverseEdges())
      factory->reverseEdges->removeEdge(id, this->getId(), edkCloneInstance_Intersects);
  }

  void CloneInstance::removeIntersects(CloneInstance *_node) {
    if (_node == NULL)
      throw GenealogyException(COLUMBUS_LOCATION, CMSG_EX_THE_EDGE_IS_NULL);

    removeIntersects(_node->getId());
  }

  void CloneInstance::setComponent(NodeId _id) {
    Component *_node = NULL;
    if (_id) {
      if (!factory->getExist(_id))
        throw GenealogyException(COLUMBUS_LOCATION, CMSG_EX_THE_END_POINT_OF_THE_EDGE_DOES_NOT_EXIST);

      _node = dynamic_cast<Component*> (factory->getPointer(_id));
      if ( _node == NULL) {
        throw GenealogyException(COLUMBUS_LOCATION, CMSG_EX_INVALID_NODE_KIND);
      }
      if (&(_node->getFactory()) != this->factory)
        throw GenealogyException(COLUMBUS_LOCATION, CMSG_EX_THE_FACTORY_OF_NODES_DOES_NOT_MATCH );

      if (m_component) {
        if (factory->getExistsReverseEdges())
          factory->reverseEdges->removeEdge(m_component, m_id, edkCloneInstance_Component);
      }
      m_component = _node->getId();
      if (factory->getExistsReverseEdges())
        factory->reverseEdges->insertEdge(m_component, this->getId(), edkCloneInstance_Component);
    } else {
      if (m_component) {
        throw GenealogyException(COLUMBUS_LOCATION, CMSG_EX_CAN_T_SET_EDGE_TO_NULL);
      }
    }
  }

  void CloneInstance::setComponent(Component *_node) {
    if (_node == NULL)
      throw GenealogyException(COLUMBUS_LOCATION, CMSG_EX_CAN_T_SET_EDGE_TO_NULL);

    setComponent(_node->getId());
  }

  void CloneInstance::removeComponent() {
      if (m_component) {
        if (factory->getExistsReverseEdges())
          factory->reverseEdges->removeEdge(m_component, m_id, edkCloneInstance_Component);
      }
      m_component = 0;
  }

  void CloneInstance::setCloneClass(NodeId _id) {
    CloneClass *_node = NULL;
    if (_id) {
      if (!factory->getExist(_id))
        throw GenealogyException(COLUMBUS_LOCATION, CMSG_EX_THE_END_POINT_OF_THE_EDGE_DOES_NOT_EXIST);

      _node = dynamic_cast<CloneClass*> (factory->getPointer(_id));
      if ( _node == NULL) {
        throw GenealogyException(COLUMBUS_LOCATION, CMSG_EX_INVALID_NODE_KIND);
      }
      if (&(_node->getFactory()) != this->factory)
        throw GenealogyException(COLUMBUS_LOCATION, CMSG_EX_THE_FACTORY_OF_NODES_DOES_NOT_MATCH );

      if (m_cloneClass) {
        if (factory->getExistsReverseEdges())
          factory->reverseEdges->removeEdge(m_cloneClass, m_id, edkCloneInstance_CloneClass);
      }
      m_cloneClass = _node->getId();
      if (factory->getExistsReverseEdges())
        factory->reverseEdges->insertEdge(m_cloneClass, this->getId(), edkCloneInstance_CloneClass);
    } else {
      if (m_cloneClass) {
        throw GenealogyException(COLUMBUS_LOCATION, CMSG_EX_CAN_T_SET_EDGE_TO_NULL);
      }
    }
  }

  void CloneInstance::setCloneClass(CloneClass *_node) {
    if (_node == NULL)
      throw GenealogyException(COLUMBUS_LOCATION, CMSG_EX_CAN_T_SET_EDGE_TO_NULL);

    setCloneClass(_node->getId());
  }

  void CloneInstance::removeCloneClass() {
      if (m_cloneClass) {
        if (factory->getExistsReverseEdges())
          factory->reverseEdges->removeEdge(m_cloneClass, m_id, edkCloneInstance_CloneClass);
      }
      m_cloneClass = 0;
  }

  void CloneInstance::accept(Visitor &visitor) const {
    visitor.visit(*this);
  }

  void CloneInstance::acceptEnd(Visitor &visitor) const {
    visitor.visitEnd(*this);
  }

  double CloneInstance::getSimilarity(const Base& base){
    if(base.getNodeKind() == getNodeKind()) {
      const CloneInstance& node = dynamic_cast<const CloneInstance&>(base);
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
      str1 = getPath();
      str2 = node.getPath();
      strMax = std::max(str1.size(), str2.size());
      strSim = 1 - ((double)common::math::editDistance(str1, str2) / (strMax > 0 ? strMax : 1));
      if (strSim < Common::SimilarityMinForStrings)
        return 0.0;
      matchAttrs += strSim;
      if(node.getLine() == getLine()) ++matchAttrs;
      if(node.getCol() == getCol()) ++matchAttrs;
      if(node.getEndLine() == getEndLine()) ++matchAttrs;
      if(node.getEndCol() == getEndCol()) ++matchAttrs;
      if(node.getCvMetricVariability() == getCvMetricVariability()) ++matchAttrs;
      if(node.getCa() == getCa()) ++matchAttrs;
      if(node.getCco() == getCco()) ++matchAttrs;
      if(node.getCe() == getCe()) ++matchAttrs;
      if(node.getCv() == getCv()) ++matchAttrs;
      if(node.getRisk() == getRisk()) ++matchAttrs;
      str1 = getRootNodes();
      str2 = node.getRootNodes();
      strMax = std::max(str1.size(), str2.size());
      strSim = 1 - ((double)common::math::editDistance(str1, str2) / (strMax > 0 ? strMax : 1));
      if (strSim < Common::SimilarityMinForStrings)
        return 0.0;
      matchAttrs += strSim;
      if(node.getRootBegin() == getRootBegin()) ++matchAttrs;
      if(node.getRootLength() == getRootLength()) ++matchAttrs;
      if(node.getF2_OrdinalNumber() == getF2_OrdinalNumber()) ++matchAttrs;
      str1 = getF3_HeadNodeUniqueName();
      str2 = node.getF3_HeadNodeUniqueName();
      strMax = std::max(str1.size(), str2.size());
      strSim = 1 - ((double)common::math::editDistance(str1, str2) / (strMax > 0 ? strMax : 1));
      if (strSim < Common::SimilarityMinForStrings)
        return 0.0;
      matchAttrs += strSim;
      str1 = getF4_AncestorUniqueName();
      str2 = node.getF4_AncestorUniqueName();
      strMax = std::max(str1.size(), str2.size());
      strSim = 1 - ((double)common::math::editDistance(str1, str2) / (strMax > 0 ? strMax : 1));
      if (strSim < Common::SimilarityMinForStrings)
        return 0.0;
      matchAttrs += strSim;
      if(node.getF5_L1() == getF5_L1()) ++matchAttrs;
      if(node.getF5_L2() == getF5_L2()) ++matchAttrs;
      if(node.getF5_L3() == getF5_L3()) ++matchAttrs;
      str1 = getF6_LexicalStructure();
      str2 = node.getF6_LexicalStructure();
      strMax = std::max(str1.size(), str2.size());
      strSim = 1 - ((double)common::math::editDistance(str1, str2) / (strMax > 0 ? strMax : 1));
      if (strSim < Common::SimilarityMinForStrings)
        return 0.0;
      matchAttrs += strSim;
      return matchAttrs / (24 / (1 - Common::SimilarityMinimum)) + Common::SimilarityMinimum;
    } else {
      return 0.0;
    }
  }

  void CloneInstance::swapStringTable(RefDistributorStrTable& newStrTable, std::map<Key,Key>& oldAndNewStrKeyMap ){
    std::map<Key,Key>::iterator foundKeyId;

    foundKeyId = oldAndNewStrKeyMap.find(m_path);
    if (foundKeyId != oldAndNewStrKeyMap.end()) {
      m_path = foundKeyId->second;
    } else {
      Key oldkey = m_path;
      m_path = newStrTable.set(factory->getStringTable().get(m_path));
      oldAndNewStrKeyMap.insert(std::pair<Key,Key>(oldkey,m_path));    }

    foundKeyId = oldAndNewStrKeyMap.find(m_rootNodes);
    if (foundKeyId != oldAndNewStrKeyMap.end()) {
      m_rootNodes = foundKeyId->second;
    } else {
      Key oldkey = m_rootNodes;
      m_rootNodes = newStrTable.set(factory->getStringTable().get(m_rootNodes));
      oldAndNewStrKeyMap.insert(std::pair<Key,Key>(oldkey,m_rootNodes));    }

    foundKeyId = oldAndNewStrKeyMap.find(m_F3_HeadNodeUniqueName);
    if (foundKeyId != oldAndNewStrKeyMap.end()) {
      m_F3_HeadNodeUniqueName = foundKeyId->second;
    } else {
      Key oldkey = m_F3_HeadNodeUniqueName;
      m_F3_HeadNodeUniqueName = newStrTable.set(factory->getStringTable().get(m_F3_HeadNodeUniqueName));
      oldAndNewStrKeyMap.insert(std::pair<Key,Key>(oldkey,m_F3_HeadNodeUniqueName));    }

    foundKeyId = oldAndNewStrKeyMap.find(m_F4_AncestorUniqueName);
    if (foundKeyId != oldAndNewStrKeyMap.end()) {
      m_F4_AncestorUniqueName = foundKeyId->second;
    } else {
      Key oldkey = m_F4_AncestorUniqueName;
      m_F4_AncestorUniqueName = newStrTable.set(factory->getStringTable().get(m_F4_AncestorUniqueName));
      oldAndNewStrKeyMap.insert(std::pair<Key,Key>(oldkey,m_F4_AncestorUniqueName));    }

    foundKeyId = oldAndNewStrKeyMap.find(m_F6_LexicalStructure);
    if (foundKeyId != oldAndNewStrKeyMap.end()) {
      m_F6_LexicalStructure = foundKeyId->second;
    } else {
      Key oldkey = m_F6_LexicalStructure;
      m_F6_LexicalStructure = newStrTable.set(factory->getStringTable().get(m_F6_LexicalStructure));
      oldAndNewStrKeyMap.insert(std::pair<Key,Key>(oldkey,m_F6_LexicalStructure));    }

    foundKeyId = oldAndNewStrKeyMap.find(m_uniqueName);
    if (foundKeyId != oldAndNewStrKeyMap.end()) {
      m_uniqueName = foundKeyId->second;
    } else {
      Key oldkey = m_uniqueName;
      m_uniqueName = newStrTable.set(factory->getStringTable().get(m_uniqueName));
      oldAndNewStrKeyMap.insert(std::pair<Key,Key>(oldkey,m_uniqueName));    }

  }

  NodeHashType CloneInstance::getHash(std::set<NodeId>& travNodes) const {
    if (hashOk) return nodeHashCache;
    common::WriteMsg::write(CMSG_GET_THE_NODE_HASH_OF_NODE_BEGIN,this->getId()); 
    if (travNodes.count(getId())>0) {
      common::WriteMsg::write(CMSG_GET_THE_NODE_HASH_OF_NODE_SKIP);
      return 0;
    }
    travNodes.insert(getId());
    Crc_type resultHash;
    resultHash.process_bytes( "CloneInstance", strlen("CloneInstance"));
    common::WriteMsg::write(CMSG_GET_THE_NODE_HASH_OF_NODE_END,resultHash.checksum()); 
    nodeHashCache = resultHash.checksum();
    hashOk = true;
    return nodeHashCache;
  }

  void CloneInstance::save(io::BinaryIO &binIo,bool withVirtualBase  /*= true*/) const {
    Clone::save(binIo,false);

    factory->getStringTable().setType(m_path, StrTable::strToSave);
    binIo.writeUInt4(m_path);
    binIo.writeUInt4(m_line);
    binIo.writeUInt4(m_col);
    binIo.writeUInt4(m_endLine);
    binIo.writeUInt4(m_endCol);
    binIo.writeUInt4(m_cvMetricVariability);
    binIo.writeUInt4(m_ca);
    binIo.writeUInt4(m_cco);
    binIo.writeUInt4(m_ce);
    binIo.writeDouble8(m_cv);
    binIo.writeDouble8(m_risk);
    factory->getStringTable().setType(m_rootNodes, StrTable::strToSave);
    binIo.writeUInt4(m_rootNodes);
    binIo.writeUInt4(m_rootBegin);
    binIo.writeUInt4(m_rootLength);
    binIo.writeUInt4(m_F2_OrdinalNumber);
    factory->getStringTable().setType(m_F3_HeadNodeUniqueName, StrTable::strToSave);
    binIo.writeUInt4(m_F3_HeadNodeUniqueName);
    factory->getStringTable().setType(m_F4_AncestorUniqueName, StrTable::strToSave);
    binIo.writeUInt4(m_F4_AncestorUniqueName);
    binIo.writeUInt4(m_F5_L1);
    binIo.writeUInt4(m_F5_L2);
    binIo.writeUInt4(m_F5_L3);
    factory->getStringTable().setType(m_F6_LexicalStructure, StrTable::strToSave);
    binIo.writeUInt4(m_F6_LexicalStructure);

    binIo.writeUInt4(m_component);
    binIo.writeUInt4(m_cloneClass);


    for (ListIterator<CloneInstance>::Container::const_iterator it = intersectsContainer.begin(); it != intersectsContainer.end(); ++it) {
      binIo.writeUInt4(*it);
    }
    binIo.writeUInt4(0); // This is the end sign
  }

  void CloneInstance::load(io::BinaryIO &binIo, bool withVirtualBase /*= true*/) {
    Clone::load(binIo,false);

    m_path = binIo.readUInt4();
    m_line = binIo.readUInt4();
    m_col = binIo.readUInt4();
    m_endLine = binIo.readUInt4();
    m_endCol = binIo.readUInt4();
    m_cvMetricVariability = binIo.readUInt4();
    m_ca = binIo.readUInt4();
    m_cco = binIo.readUInt4();
    m_ce = binIo.readUInt4();
    m_cv = binIo.readDouble8();
    m_risk = binIo.readDouble8();
    m_rootNodes = binIo.readUInt4();
    m_rootBegin = binIo.readUInt4();
    m_rootLength = binIo.readUInt4();
    m_F2_OrdinalNumber = binIo.readUInt4();
    m_F3_HeadNodeUniqueName = binIo.readUInt4();
    m_F4_AncestorUniqueName = binIo.readUInt4();
    m_F5_L1 = binIo.readUInt4();
    m_F5_L2 = binIo.readUInt4();
    m_F5_L3 = binIo.readUInt4();
    m_F6_LexicalStructure = binIo.readUInt4();

    m_component =  binIo.readUInt4();

    m_cloneClass =  binIo.readUInt4();

    NodeId _id;

    _id = binIo.readUInt4();
    while (_id) {
      intersectsContainer.push_back(_id);
      _id = binIo.readUInt4();
    }
  }



}}
