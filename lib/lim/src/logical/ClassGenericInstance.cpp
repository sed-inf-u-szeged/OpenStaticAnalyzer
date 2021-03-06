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
  ClassGenericInstance::ClassGenericInstance(NodeId _id, Factory *_factory) :
    Class(_id, _factory),
    m_isRealInstance(false),
    hasArgumentsContainer()
  {
  }

  ClassGenericInstance::~ClassGenericInstance() {
  }

  void ClassGenericInstance::clone(const ClassGenericInstance& other, bool tryOnVirtualParent) {
    logical::Class::clone(other, false);

    m_isRealInstance = other.m_isRealInstance;
    //isAssocEdge
    hasArgumentsContainer = other.hasArgumentsContainer;
  }

  void ClassGenericInstance::prepareDelete(bool tryOnVirtualParent){
    while (!hasArgumentsContainer.empty()) {
      const NodeId id = *hasArgumentsContainer.begin();
      if (factory->getExistsReverseEdges())
        factory->reverseEdges->removeEdge(id, this->getId(), edkClassGenericInstance_HasArguments);
      hasArgumentsContainer.pop_front();
    }
    logical::Class::prepareDelete(false);
  }

  NodeKind ClassGenericInstance::getNodeKind() const {
    return ndkClassGenericInstance;
  }

  bool ClassGenericInstance::getIsRealInstance() const {
    return m_isRealInstance;
  }

  void ClassGenericInstance::setIsRealInstance(bool _isRealInstance) {
    m_isRealInstance = _isRealInstance;
  }

  ListIteratorAssocTypeArgumentConstraintKind<type::Type> ClassGenericInstance::getArgumentsListIteratorAssocBegin() const {
    return ListIteratorAssocTypeArgumentConstraintKind<type::Type>(&hasArgumentsContainer, factory, true);
  }

  ListIteratorAssocTypeArgumentConstraintKind<type::Type> ClassGenericInstance::getArgumentsListIteratorAssocEnd() const {
    return ListIteratorAssocTypeArgumentConstraintKind<type::Type>(&hasArgumentsContainer, factory, false);
  }

  bool ClassGenericInstance::getArgumentsIsEmpty() const {
    return getArgumentsListIteratorAssocBegin() == getArgumentsListIteratorAssocEnd();
  }

  unsigned int ClassGenericInstance::getArgumentsSize() const {
    unsigned int size = 0;
    ListIteratorAssocTypeArgumentConstraintKind<type::Type> endIt = getArgumentsListIteratorAssocEnd();
    for (ListIteratorAssocTypeArgumentConstraintKind<type::Type> it = getArgumentsListIteratorAssocBegin(); it != endIt; ++it) {
      ++size;
    }
    return size;
  }

  bool ClassGenericInstance::setEdge(EdgeKind edgeKind, NodeId edgeEnd, void* acValue, bool tryOnVirtualParent) {
    switch (edgeKind) {
      case edkClassGenericInstance_HasArguments:
        addArguments(edgeEnd, *((TypeArgumentConstraintKind*)acValue));
        return true;
      default:
        break;
    }
    if (logical::Class::setEdge(edgeKind, edgeEnd, acValue, false)) {
      return true;
    }
    return false;
  }

  bool ClassGenericInstance::removeEdge(EdgeKind edgeKind, NodeId edgeEnd, bool tryOnVirtualParent) {
    switch (edgeKind) {
      case edkClassGenericInstance_HasArguments:
        removeArguments(edgeEnd);
        return true;
      default:
        break;
    }
    if (logical::Class::removeEdge(edgeKind, edgeEnd, false)) {
      return true;
    }
    return false;
  }

  void ClassGenericInstance::addArguments(const type::Type *_node, TypeArgumentConstraintKind acValue) {
    if (_node == NULL)
      throw LimException(COLUMBUS_LOCATION, CMSG_EX_THE_NODE_IS_NULL);

    if (&(_node->getFactory()) != this->factory)
      throw LimException(COLUMBUS_LOCATION, CMSG_EX_THE_FACTORY_OF_NODES_DOES_NOT_MATCH);

    if (!((_node->getNodeKind() == ndkType) ))
      throw LimException(COLUMBUS_LOCATION, CMSG_EX_INVALID_NODE_KIND);

    AssocEdge<NodeId,TypeArgumentConstraintKind> ac(_node->getId(), acValue);
    hasArgumentsContainer.push_back(ac);
    if (factory->reverseEdges)
      factory->reverseEdges->insertEdge(_node, this, edkClassGenericInstance_HasArguments);
  }

  void ClassGenericInstance::addArguments(NodeId _id, TypeArgumentConstraintKind acValue) {
    const type::Type *node = dynamic_cast<type::Type*>(factory->getPointer(_id));
    if (node == NULL)
      throw LimException(COLUMBUS_LOCATION, CMSG_EX_INVALID_NODE_KIND);
    addArguments( node, acValue );
  }

  void ClassGenericInstance::removeArguments(NodeId id) {
    if (!factory->getExist(id))
      throw LimException(COLUMBUS_LOCATION, CMSG_EX_THE_END_POINT_OF_THE_EDGE_DOES_NOT_EXIST);

    ListIteratorAssocTypeArgumentConstraintKind<type::Type>::Container::iterator it = find(hasArgumentsContainer.begin(), hasArgumentsContainer.end(), id);

    if (it == hasArgumentsContainer.end())
      throw LimException(COLUMBUS_LOCATION, CMSG_EX_THE_END_POINT_OF_THE_EDGE_DOES_NOT_EXIST);

    hasArgumentsContainer.erase(it);

    if (factory->getExistsReverseEdges())
      factory->reverseEdges->removeEdge(id, this->getId(), edkClassGenericInstance_HasArguments);
  }

  void ClassGenericInstance::removeArguments(type::Type *_node) {
    if (_node == NULL)
      throw LimException(COLUMBUS_LOCATION, CMSG_EX_THE_EDGE_IS_NULL);

    removeArguments(_node->getId());
  }

  void ClassGenericInstance::accept(Visitor &visitor) const {
    visitor.visit(*this);
  }

  void ClassGenericInstance::acceptEnd(Visitor &visitor) const {
    visitor.visitEnd(*this);
  }

  double ClassGenericInstance::getSimilarity(const base::Base& base){
    if(base.getNodeKind() == getNodeKind()) {
      const ClassGenericInstance& node = dynamic_cast<const ClassGenericInstance&>(base);
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
      if(node.getClassKind() == getClassKind()) ++matchAttrs;
      if(node.getIsAbstract() == getIsAbstract()) ++matchAttrs;
      if(node.getObjectSize() == getObjectSize()) ++matchAttrs;
      if(node.getIsRealInstance() == getIsRealInstance()) ++matchAttrs;
      return matchAttrs / (17 / (1 - Common::SimilarityMinimum)) + Common::SimilarityMinimum;
    } else {
      return 0.0;
    }
  }

  void ClassGenericInstance::swapStringTable(RefDistributorStrTable& newStrTable, std::map<Key,Key>& oldAndNewStrKeyMap ){
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

  NodeHashType ClassGenericInstance::getHash(std::set<NodeId>& travNodes) const {
    if (hashOk) return nodeHashCache;
    common::WriteMsg::write(CMSG_GET_THE_NODE_HASH_OF_NODE_BEGIN,this->getId()); 
    if (travNodes.count(getId())>0) {
      common::WriteMsg::write(CMSG_GET_THE_NODE_HASH_OF_NODE_SKIP);
      return 0;
    }
    travNodes.insert(getId());
    Crc_type resultHash;
    resultHash.process_bytes( "logical::ClassGenericInstance", strlen("logical::ClassGenericInstance"));
    common::WriteMsg::write(CMSG_GET_THE_NODE_HASH_OF_NODE_END,resultHash.checksum()); 
    nodeHashCache = resultHash.checksum();
    hashOk = true;
    return nodeHashCache;
  }

  void ClassGenericInstance::save(io::BinaryIO &binIo,bool withVirtualBase  /*= true*/) const {
    Class::save(binIo,false);

    unsigned char boolValues = 0;
    boolValues <<= 1;
    if (m_isRealInstance) 
      boolValues |= 1;
    binIo.writeUByte1(boolValues);


    for (ListIteratorAssocTypeArgumentConstraintKind<type::Type>::Container::const_iterator ait = hasArgumentsContainer.begin(); ait != hasArgumentsContainer.end(); ++ait) {
      binIo.writeUInt4(ait->node);
      binIo.writeUByte1(ait->assocClass);
    }
    binIo.writeUInt4(0); // This is the end sign
  }

  void ClassGenericInstance::load(io::BinaryIO &binIo, bool withVirtualBase /*= true*/) {
    Class::load(binIo,false);

    unsigned char boolValues = binIo.readUByte1();
    m_isRealInstance = boolValues & 1;
    boolValues >>= 1;

    NodeId _id;

    _id = binIo.readUInt4();
    while (_id) {
      TypeArgumentConstraintKind _ac = static_cast<TypeArgumentConstraintKind>(binIo.readUByte1());
      hasArgumentsContainer.push_back(AssocEdge<NodeId,TypeArgumentConstraintKind>(_id, _ac));
      _id = binIo.readUInt4();
    }
  }


}


}}}
