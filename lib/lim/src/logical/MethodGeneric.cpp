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

#include "lim/inc/lim.h"
#include "lim/inc/Common.h"
#include "common/inc/WriteMessage.h"

#include "lim/inc/messages.h"
#include <algorithm>
#include <string.h>
#include "common/inc/math/common.h"


namespace columbus { namespace lim { namespace asg {

typedef boost::crc_32_type  Crc_type;

namespace logical { 
  MethodGeneric::MethodGeneric(NodeId _id, Factory *_factory) :
    Method(_id, _factory),
    hasGenericParameterContainer()
  {
  }

  MethodGeneric::~MethodGeneric() {
  }

  void MethodGeneric::clone(const MethodGeneric& other, bool tryOnVirtualParent) {
    logical::Method::clone(other, false);

    hasGenericParameterContainer = other.hasGenericParameterContainer;
  }

  void MethodGeneric::prepareDelete(bool tryOnVirtualParent){
    while (!hasGenericParameterContainer.empty()) {
      const NodeId id = *hasGenericParameterContainer.begin();
      removeParentEdge(id);
      if (factory->getExistsReverseEdges())
        factory->reverseEdges->removeEdge(id, this->getId(), edkMethodGeneric_HasGenericParameter);
      hasGenericParameterContainer.pop_front();
    }
    logical::Method::prepareDelete(false);
  }

  NodeKind MethodGeneric::getNodeKind() const {
    return ndkMethodGeneric;
  }

  ListIterator<logical::GenericParameter> MethodGeneric::getGenericParameterListIteratorBegin() const {
    return ListIterator<logical::GenericParameter>(&hasGenericParameterContainer, factory, true);
  }

  ListIterator<logical::GenericParameter> MethodGeneric::getGenericParameterListIteratorEnd() const {
    return ListIterator<logical::GenericParameter>(&hasGenericParameterContainer, factory, false);
  }

  bool MethodGeneric::getGenericParameterIsEmpty() const {
    return getGenericParameterListIteratorBegin() == getGenericParameterListIteratorEnd();
  }

  unsigned int MethodGeneric::getGenericParameterSize() const {
    unsigned int size = 0;
    ListIterator<logical::GenericParameter> endIt = getGenericParameterListIteratorEnd();
    for (ListIterator<logical::GenericParameter> it = getGenericParameterListIteratorBegin(); it != endIt; ++it) {
      ++size;
    }
    return size;
  }

  bool MethodGeneric::setEdge(EdgeKind edgeKind, NodeId edgeEnd, void* acValue, bool tryOnVirtualParent) {
    switch (edgeKind) {
      case edkMethodGeneric_HasGenericParameter:
        addGenericParameter(edgeEnd);
        return true;
      default:
        break;
    }
    if (logical::Method::setEdge(edgeKind, edgeEnd, acValue, false)) {
      return true;
    }
    return false;
  }

  bool MethodGeneric::removeEdge(EdgeKind edgeKind, NodeId edgeEnd, bool tryOnVirtualParent) {
    switch (edgeKind) {
      case edkMethodGeneric_HasGenericParameter:
        removeGenericParameter(edgeEnd);
        return true;
      default:
        break;
    }
    if (logical::Method::removeEdge(edgeKind, edgeEnd, false)) {
      return true;
    }
    return false;
  }

  void MethodGeneric::addGenericParameter(const logical::GenericParameter *_node) {
    if (_node == NULL)
      throw LimException(COLUMBUS_LOCATION, CMSG_EX_THE_NODE_IS_NULL);

    if (&(_node->getFactory()) != this->factory)
      throw LimException(COLUMBUS_LOCATION, CMSG_EX_THE_FACTORY_OF_NODES_DOES_NOT_MATCH);

    if (!((_node->getNodeKind() == ndkGenericParameter) ))
      throw LimException(COLUMBUS_LOCATION, CMSG_EX_INVALID_NODE_KIND);

    hasGenericParameterContainer.push_back(_node->getId());
    setParentEdge(_node,edkMethodGeneric_HasGenericParameter);

    if (factory->reverseEdges)
      factory->reverseEdges->insertEdge(_node, this, edkMethodGeneric_HasGenericParameter);
  }

  void MethodGeneric::addGenericParameter(NodeId _id) {
    const logical::GenericParameter *node = dynamic_cast<logical::GenericParameter*>(factory->getPointer(_id));
    if (node == NULL)
      throw LimException(COLUMBUS_LOCATION, CMSG_EX_INVALID_NODE_KIND);
    addGenericParameter( node );
  }

  void MethodGeneric::removeGenericParameter(NodeId id) {
    if (!factory->getExist(id))
      throw LimException(COLUMBUS_LOCATION, CMSG_EX_THE_END_POINT_OF_THE_EDGE_DOES_NOT_EXIST);

    ListIterator<logical::GenericParameter>::Container::iterator it = find(hasGenericParameterContainer.begin(), hasGenericParameterContainer.end(), id);

    if (it == hasGenericParameterContainer.end())
      throw LimException(COLUMBUS_LOCATION, CMSG_EX_THE_END_POINT_OF_THE_EDGE_DOES_NOT_EXIST);

    hasGenericParameterContainer.erase(it);

    removeParentEdge(id);

    if (factory->getExistsReverseEdges())
      factory->reverseEdges->removeEdge(id, this->getId(), edkMethodGeneric_HasGenericParameter);
  }

  void MethodGeneric::removeGenericParameter(logical::GenericParameter *_node) {
    if (_node == NULL)
      throw LimException(COLUMBUS_LOCATION, CMSG_EX_THE_EDGE_IS_NULL);

    removeGenericParameter(_node->getId());
  }

  void MethodGeneric::accept(Visitor &visitor) const {
    visitor.visit(*this);
  }

  void MethodGeneric::acceptEnd(Visitor &visitor) const {
    visitor.visitEnd(*this);
  }

  double MethodGeneric::getSimilarity(const base::Base& base){
    if(base.getNodeKind() == getNodeKind()) {
      const MethodGeneric& node = dynamic_cast<const MethodGeneric&>(base);
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
      if(node.getAccessibility() == getAccessibility()) ++matchAttrs;
      if(node.getCommentLines() == getCommentLines()) ++matchAttrs;
      str1 = getDemangledName();
      str2 = node.getDemangledName();
      strMax = std::max(str1.size(), str2.size());
      strSim = 1 - ((double)common::math::editDistance(str1, str2) / (strMax > 0 ? strMax : 1));
      if (strSim < Common::SimilarityMinForStrings)
        return 0.0;
      matchAttrs += strSim;
      if(node.getIsCompilerGenerated() == getIsCompilerGenerated()) ++matchAttrs;
      if(node.getIsStatic() == getIsStatic()) ++matchAttrs;
      if(node.getLanguage() == getLanguage()) ++matchAttrs;
      str1 = getMangledName();
      str2 = node.getMangledName();
      strMax = std::max(str1.size(), str2.size());
      strSim = 1 - ((double)common::math::editDistance(str1, str2) / (strMax > 0 ? strMax : 1));
      if (strSim < Common::SimilarityMinForStrings)
        return 0.0;
      matchAttrs += strSim;
      if(node.getLLOC() == getLLOC()) ++matchAttrs;
      if(node.getLOC() == getLOC()) ++matchAttrs;
      if(node.getTLLOC() == getTLLOC()) ++matchAttrs;
      if(node.getTLOC() == getTLOC()) ++matchAttrs;
      if(node.getIsAnonymous() == getIsAnonymous()) ++matchAttrs;
      if(node.getDistinctOperands() == getDistinctOperands()) ++matchAttrs;
      if(node.getDistinctOperators() == getDistinctOperators()) ++matchAttrs;
      if(node.getIsAbstract() == getIsAbstract()) ++matchAttrs;
      if(node.getIsVirtual() == getIsVirtual()) ++matchAttrs;
      if(node.getMethodKind() == getMethodKind()) ++matchAttrs;
      if(node.getNestingLevel() == getNestingLevel()) ++matchAttrs;
      if(node.getNestingLevelElseIf() == getNestingLevelElseIf()) ++matchAttrs;
      if(node.getNumberOfBranches() == getNumberOfBranches()) ++matchAttrs;
      if(node.getNumberOfStatements() == getNumberOfStatements()) ++matchAttrs;
      if(node.getTotalOperands() == getTotalOperands()) ++matchAttrs;
      if(node.getTotalOperators() == getTotalOperators()) ++matchAttrs;
      return matchAttrs / (24 / (1 - Common::SimilarityMinimum)) + Common::SimilarityMinimum;
    } else {
      return 0.0;
    }
  }

  void MethodGeneric::swapStringTable(RefDistributorStrTable& newStrTable, std::map<Key,Key>& oldAndNewStrKeyMap ){
    std::map<Key,Key>::iterator foundKeyId;

    foundKeyId = oldAndNewStrKeyMap.find(m_demangledName);
    if (foundKeyId != oldAndNewStrKeyMap.end()) {
      m_demangledName = foundKeyId->second;
    } else {
      Key oldkey = m_demangledName;
      m_demangledName = newStrTable.set(factory->getStringTable().get(m_demangledName));
      oldAndNewStrKeyMap.insert(std::pair<Key,Key>(oldkey,m_demangledName));    }

    foundKeyId = oldAndNewStrKeyMap.find(m_mangledName);
    if (foundKeyId != oldAndNewStrKeyMap.end()) {
      m_mangledName = foundKeyId->second;
    } else {
      Key oldkey = m_mangledName;
      m_mangledName = newStrTable.set(factory->getStringTable().get(m_mangledName));
      oldAndNewStrKeyMap.insert(std::pair<Key,Key>(oldkey,m_mangledName));    }

    foundKeyId = oldAndNewStrKeyMap.find(m_name);
    if (foundKeyId != oldAndNewStrKeyMap.end()) {
      m_name = foundKeyId->second;
    } else {
      Key oldkey = m_name;
      m_name = newStrTable.set(factory->getStringTable().get(m_name));
      oldAndNewStrKeyMap.insert(std::pair<Key,Key>(oldkey,m_name));    }

  }

  NodeHashType MethodGeneric::getHash(std::set<NodeId>& travNodes) const {
    if (hashOk) return nodeHashCache;
    common::WriteMsg::write(CMSG_GET_THE_NODE_HASH_OF_NODE_BEGIN,this->getId()); 
    if (travNodes.count(getId())>0) {
      common::WriteMsg::write(CMSG_GET_THE_NODE_HASH_OF_NODE_SKIP);
      return 0;
    }
    travNodes.insert(getId());
    Crc_type resultHash;
    resultHash.process_bytes( "logical::MethodGeneric", strlen("logical::MethodGeneric"));
    common::WriteMsg::write(CMSG_GET_THE_NODE_HASH_OF_NODE_END,resultHash.checksum()); 
    nodeHashCache = resultHash.checksum();
    hashOk = true;
    return nodeHashCache;
  }

  void MethodGeneric::save(io::BinaryIO &binIo,bool withVirtualBase  /*= true*/) const {
    Method::save(binIo,false);


    for (ListIterator<logical::GenericParameter>::Container::const_iterator it = hasGenericParameterContainer.begin(); it != hasGenericParameterContainer.end(); ++it) {
      binIo.writeUInt4(*it);
    }
    binIo.writeUInt4(0); // This is the end sign
  }

  void MethodGeneric::load(io::BinaryIO &binIo, bool withVirtualBase /*= true*/) {
    Method::load(binIo,false);

    NodeId _id;

    _id = binIo.readUInt4();
    while (_id) {
      hasGenericParameterContainer.push_back(_id);
      setParentEdge(factory->getPointer(_id),edkMethodGeneric_HasGenericParameter);
      _id = binIo.readUInt4();
    }
  }


}


}}}
