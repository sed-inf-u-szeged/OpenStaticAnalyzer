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

  CaseLabel::CaseLabel(NodeId _id, Factory *_factory) :
    SourceCodeElement(_id, _factory),
    m_nodeId(0),
    m_caseValue(0),
    m_component(0)
  {
  }

  CaseLabel::~CaseLabel() {
  }

  void CaseLabel::prepareDelete(bool tryOnVirtualParent){
    removeComponent();
    SourceCodeElement::prepareDelete(false);
  }

  NodeKind CaseLabel::getNodeKind() const {
    return ndkCaseLabel;
  }

  Key CaseLabel::getCaseValueKey() const {
    return m_caseValue;
  }

  const std::string& CaseLabel::getCaseValue() const {
    return factory->getStringTable().get(m_caseValue);
  }

  unsigned CaseLabel::getNodeId() const {
    return m_nodeId;
  }

  void CaseLabel::setCaseValueKey(Key _caseValue) {
    m_caseValue = _caseValue;
  }

  void CaseLabel::setCaseValue(const std::string& _caseValue) {
    m_caseValue = factory->getStringTable().set(_caseValue);
  }

  void CaseLabel::setNodeId(unsigned _nodeId) {
    m_nodeId = _nodeId;
  }

  Component* CaseLabel::getComponent() const {
    Component *_node = NULL;
    if (m_component != 0)
      _node = dynamic_cast<Component*>(factory->getPointer(m_component));
    return _node;
  }

  bool CaseLabel::setEdge(EdgeKind edgeKind, NodeId edgeEnd, bool tryOnVirtualParent) {
    switch (edgeKind) {
      case edkCaseLabel_Component:
        setComponent(edgeEnd);
        return true;
      default:
        break;
    }
    if (SourceCodeElement::setEdge(edgeKind, edgeEnd, false)) {
      return true;
    }
    return false;
  }

  bool CaseLabel::removeEdge(EdgeKind edgeKind, NodeId edgeEnd, bool tryOnVirtualParent) {
    switch (edgeKind) {
      case edkCaseLabel_Component:
        removeComponent();
        return true;
      default:
        break;
    }
    if (SourceCodeElement::removeEdge(edgeKind, edgeEnd, false)) {
      return true;
    }
    return false;
  }

  void CaseLabel::setComponent(NodeId _id) {
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
          factory->reverseEdges->removeEdge(m_component, m_id, edkCaseLabel_Component);
      }
      m_component = _node->getId();
      if (factory->getExistsReverseEdges())
        factory->reverseEdges->insertEdge(m_component, this->getId(), edkCaseLabel_Component);
    } else {
      if (m_component) {
        throw GenealogyException(COLUMBUS_LOCATION, CMSG_EX_CAN_T_SET_EDGE_TO_NULL);
      }
    }
  }

  void CaseLabel::setComponent(Component *_node) {
    if (_node == NULL)
      throw GenealogyException(COLUMBUS_LOCATION, CMSG_EX_CAN_T_SET_EDGE_TO_NULL);

    setComponent(_node->getId());
  }

  void CaseLabel::removeComponent() {
      if (m_component) {
        if (factory->getExistsReverseEdges())
          factory->reverseEdges->removeEdge(m_component, m_id, edkCaseLabel_Component);
      }
      m_component = 0;
  }

  void CaseLabel::accept(Visitor &visitor) const {
    visitor.visit(*this);
  }

  void CaseLabel::acceptEnd(Visitor &visitor) const {
    visitor.visitEnd(*this);
  }

  double CaseLabel::getSimilarity(const Base& base){
    if(base.getNodeKind() == getNodeKind()) {
      const CaseLabel& node = dynamic_cast<const CaseLabel&>(base);
      double matchAttrs = 0;
      std::string str1, str2;
      size_t strMax;
      double strSim;
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
      str1 = getCaseValue();
      str2 = node.getCaseValue();
      strMax = std::max(str1.size(), str2.size());
      strSim = 1 - ((double)common::math::editDistance(str1, str2) / (strMax > 0 ? strMax : 1));
      if (strSim < Common::SimilarityMinForStrings)
        return 0.0;
      matchAttrs += strSim;
      if(node.getNodeId() == getNodeId()) ++matchAttrs;
      return matchAttrs / (7 / (1 - Common::SimilarityMinimum)) + Common::SimilarityMinimum;
    } else {
      return 0.0;
    }
  }

  void CaseLabel::swapStringTable(RefDistributorStrTable& newStrTable, std::map<Key,Key>& oldAndNewStrKeyMap ){
    std::map<Key,Key>::iterator foundKeyId;

    foundKeyId = oldAndNewStrKeyMap.find(m_caseValue);
    if (foundKeyId != oldAndNewStrKeyMap.end()) {
      m_caseValue = foundKeyId->second;
    } else {
      Key oldkey = m_caseValue;
      m_caseValue = newStrTable.set(factory->getStringTable().get(m_caseValue));
      oldAndNewStrKeyMap.insert(std::pair<Key,Key>(oldkey,m_caseValue));    }

    foundKeyId = oldAndNewStrKeyMap.find(m_path);
    if (foundKeyId != oldAndNewStrKeyMap.end()) {
      m_path = foundKeyId->second;
    } else {
      Key oldkey = m_path;
      m_path = newStrTable.set(factory->getStringTable().get(m_path));
      oldAndNewStrKeyMap.insert(std::pair<Key,Key>(oldkey,m_path));    }

  }

  NodeHashType CaseLabel::getHash(std::set<NodeId>& travNodes) const {
    if (hashOk) return nodeHashCache;
    common::WriteMsg::write(CMSG_GET_THE_NODE_HASH_OF_NODE_BEGIN,this->getId()); 
    if (travNodes.count(getId())>0) {
      common::WriteMsg::write(CMSG_GET_THE_NODE_HASH_OF_NODE_SKIP);
      return 0;
    }
    travNodes.insert(getId());
    Crc_type resultHash;
    resultHash.process_bytes( "CaseLabel", strlen("CaseLabel"));
    common::WriteMsg::write(CMSG_GET_THE_NODE_HASH_OF_NODE_END,resultHash.checksum()); 
    nodeHashCache = resultHash.checksum();
    hashOk = true;
    return nodeHashCache;
  }

  void CaseLabel::save(io::BinaryIO &binIo,bool withVirtualBase  /*= true*/) const {
    SourceCodeElement::save(binIo,false);

    factory->getStringTable().setType(m_caseValue, StrTable::strToSave);
    binIo.writeUInt4(m_caseValue);
    binIo.writeUInt4(m_nodeId);

    binIo.writeUInt4(m_component);

  }

  void CaseLabel::load(io::BinaryIO &binIo, bool withVirtualBase /*= true*/) {
    SourceCodeElement::load(binIo,false);

    m_caseValue = binIo.readUInt4();
    m_nodeId = binIo.readUInt4();

    m_component =  binIo.readUInt4();

  }



}}
