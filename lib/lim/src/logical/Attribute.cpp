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
  Attribute::Attribute(NodeId _id, Factory *_factory) :
    Member(_id, _factory),
    callsContainer(),
    hasTypeContainer()
  {
  }

  Attribute::~Attribute() {
  }

  void Attribute::clone(const Attribute& other, bool tryOnVirtualParent) {
    logical::Member::clone(other, false);

    callsContainer = other.callsContainer;
    hasTypeContainer = other.hasTypeContainer;
  }

  void Attribute::prepareDelete(bool tryOnVirtualParent){
    while (!callsContainer.empty()) {
      const NodeId id = *callsContainer.begin();
      if (factory->getExistsReverseEdges())
        factory->reverseEdges->removeEdge(id, this->getId(), edkAttribute_Calls);
      callsContainer.pop_front();
    }
    while (!hasTypeContainer.empty()) {
      const NodeId id = *hasTypeContainer.begin();
      if (factory->getExistsReverseEdges())
        factory->reverseEdges->removeEdge(id, this->getId(), edkAttribute_HasType);
      hasTypeContainer.pop_front();
    }
    logical::Member::prepareDelete(false);
  }

  NodeKind Attribute::getNodeKind() const {
    return ndkAttribute;
  }

  ListIterator<logical::MethodCall> Attribute::getCallsListIteratorBegin() const {
    return ListIterator<logical::MethodCall>(&callsContainer, factory, true);
  }

  ListIterator<logical::MethodCall> Attribute::getCallsListIteratorEnd() const {
    return ListIterator<logical::MethodCall>(&callsContainer, factory, false);
  }

  bool Attribute::getCallsIsEmpty() const {
    return getCallsListIteratorBegin() == getCallsListIteratorEnd();
  }

  unsigned int Attribute::getCallsSize() const {
    unsigned int size = 0;
    ListIterator<logical::MethodCall> endIt = getCallsListIteratorEnd();
    for (ListIterator<logical::MethodCall> it = getCallsListIteratorBegin(); it != endIt; ++it) {
      ++size;
    }
    return size;
  }

  ListIterator<type::Type> Attribute::getTypeListIteratorBegin() const {
    return ListIterator<type::Type>(&hasTypeContainer, factory, true);
  }

  ListIterator<type::Type> Attribute::getTypeListIteratorEnd() const {
    return ListIterator<type::Type>(&hasTypeContainer, factory, false);
  }

  bool Attribute::getTypeIsEmpty() const {
    return getTypeListIteratorBegin() == getTypeListIteratorEnd();
  }

  unsigned int Attribute::getTypeSize() const {
    unsigned int size = 0;
    ListIterator<type::Type> endIt = getTypeListIteratorEnd();
    for (ListIterator<type::Type> it = getTypeListIteratorBegin(); it != endIt; ++it) {
      ++size;
    }
    return size;
  }

  bool Attribute::setEdge(EdgeKind edgeKind, NodeId edgeEnd, void* acValue, bool tryOnVirtualParent) {
    switch (edgeKind) {
      case edkAttribute_Calls:
        addCalls(edgeEnd);
        return true;
      case edkAttribute_HasType:
        addType(edgeEnd);
        return true;
      default:
        break;
    }
    if (logical::Member::setEdge(edgeKind, edgeEnd, acValue, false)) {
      return true;
    }
    return false;
  }

  bool Attribute::removeEdge(EdgeKind edgeKind, NodeId edgeEnd, bool tryOnVirtualParent) {
    switch (edgeKind) {
      case edkAttribute_Calls:
        removeCalls(edgeEnd);
        return true;
      case edkAttribute_HasType:
        removeType(edgeEnd);
        return true;
      default:
        break;
    }
    if (logical::Member::removeEdge(edgeKind, edgeEnd, false)) {
      return true;
    }
    return false;
  }

  void Attribute::addCalls(const logical::MethodCall *_node) {
    if (_node == NULL)
      throw LimException(COLUMBUS_LOCATION, CMSG_EX_THE_NODE_IS_NULL);

    if (&(_node->getFactory()) != this->factory)
      throw LimException(COLUMBUS_LOCATION, CMSG_EX_THE_FACTORY_OF_NODES_DOES_NOT_MATCH);

    if (!((_node->getNodeKind() == ndkMethodCall) ))
      throw LimException(COLUMBUS_LOCATION, CMSG_EX_INVALID_NODE_KIND);

    callsContainer.push_back(_node->getId());
    if (factory->reverseEdges)
      factory->reverseEdges->insertEdge(_node, this, edkAttribute_Calls);
  }

  void Attribute::addCalls(NodeId _id) {
    const logical::MethodCall *node = dynamic_cast<logical::MethodCall*>(factory->getPointer(_id));
    if (node == NULL)
      throw LimException(COLUMBUS_LOCATION, CMSG_EX_INVALID_NODE_KIND);
    addCalls( node );
  }

  void Attribute::removeCalls(NodeId id) {
    if (!factory->getExist(id))
      throw LimException(COLUMBUS_LOCATION, CMSG_EX_THE_END_POINT_OF_THE_EDGE_DOES_NOT_EXIST);

    ListIterator<logical::MethodCall>::Container::iterator it = find(callsContainer.begin(), callsContainer.end(), id);

    if (it == callsContainer.end())
      throw LimException(COLUMBUS_LOCATION, CMSG_EX_THE_END_POINT_OF_THE_EDGE_DOES_NOT_EXIST);

    callsContainer.erase(it);

    if (factory->getExistsReverseEdges())
      factory->reverseEdges->removeEdge(id, this->getId(), edkAttribute_Calls);
  }

  void Attribute::removeCalls(logical::MethodCall *_node) {
    if (_node == NULL)
      throw LimException(COLUMBUS_LOCATION, CMSG_EX_THE_EDGE_IS_NULL);

    removeCalls(_node->getId());
  }

  void Attribute::addType(const type::Type *_node) {
    if (_node == NULL)
      throw LimException(COLUMBUS_LOCATION, CMSG_EX_THE_NODE_IS_NULL);

    if (&(_node->getFactory()) != this->factory)
      throw LimException(COLUMBUS_LOCATION, CMSG_EX_THE_FACTORY_OF_NODES_DOES_NOT_MATCH);

    if (!((_node->getNodeKind() == ndkType) ))
      throw LimException(COLUMBUS_LOCATION, CMSG_EX_INVALID_NODE_KIND);

    hasTypeContainer.push_back(_node->getId());
    if (factory->reverseEdges)
      factory->reverseEdges->insertEdge(_node, this, edkAttribute_HasType);
  }

  void Attribute::addType(NodeId _id) {
    const type::Type *node = dynamic_cast<type::Type*>(factory->getPointer(_id));
    if (node == NULL)
      throw LimException(COLUMBUS_LOCATION, CMSG_EX_INVALID_NODE_KIND);
    addType( node );
  }

  void Attribute::removeType(NodeId id) {
    if (!factory->getExist(id))
      throw LimException(COLUMBUS_LOCATION, CMSG_EX_THE_END_POINT_OF_THE_EDGE_DOES_NOT_EXIST);

    ListIterator<type::Type>::Container::iterator it = find(hasTypeContainer.begin(), hasTypeContainer.end(), id);

    if (it == hasTypeContainer.end())
      throw LimException(COLUMBUS_LOCATION, CMSG_EX_THE_END_POINT_OF_THE_EDGE_DOES_NOT_EXIST);

    hasTypeContainer.erase(it);

    if (factory->getExistsReverseEdges())
      factory->reverseEdges->removeEdge(id, this->getId(), edkAttribute_HasType);
  }

  void Attribute::removeType(type::Type *_node) {
    if (_node == NULL)
      throw LimException(COLUMBUS_LOCATION, CMSG_EX_THE_EDGE_IS_NULL);

    removeType(_node->getId());
  }

  void Attribute::accept(Visitor &visitor) const {
    visitor.visit(*this);
  }

  void Attribute::acceptEnd(Visitor &visitor) const {
    visitor.visitEnd(*this);
  }

  double Attribute::getSimilarity(const base::Base& base){
    if(base.getNodeKind() == getNodeKind()) {
      const Attribute& node = dynamic_cast<const Attribute&>(base);
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
      return matchAttrs / (8 / (1 - Common::SimilarityMinimum)) + Common::SimilarityMinimum;
    } else {
      return 0.0;
    }
  }

  void Attribute::swapStringTable(RefDistributorStrTable& newStrTable, std::map<Key,Key>& oldAndNewStrKeyMap ){
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

  NodeHashType Attribute::getHash(std::set<NodeId>& travNodes) const {
    if (hashOk) return nodeHashCache;
    common::WriteMsg::write(CMSG_GET_THE_NODE_HASH_OF_NODE_BEGIN,this->getId()); 
    if (travNodes.count(getId())>0) {
      common::WriteMsg::write(CMSG_GET_THE_NODE_HASH_OF_NODE_SKIP);
      return 0;
    }
    travNodes.insert(getId());
    Crc_type resultHash;
    resultHash.process_bytes( "logical::Attribute", strlen("logical::Attribute"));
    common::WriteMsg::write(CMSG_GET_THE_NODE_HASH_OF_NODE_END,resultHash.checksum()); 
    nodeHashCache = resultHash.checksum();
    hashOk = true;
    return nodeHashCache;
  }

  void Attribute::save(io::BinaryIO &binIo,bool withVirtualBase  /*= true*/) const {
    Member::save(binIo,false);


    for (ListIterator<logical::MethodCall>::Container::const_iterator it = callsContainer.begin(); it != callsContainer.end(); ++it) {
      binIo.writeUInt4(*it);
    }
    binIo.writeUInt4(0); // This is the end sign

    for (ListIterator<type::Type>::Container::const_iterator it = hasTypeContainer.begin(); it != hasTypeContainer.end(); ++it) {
      binIo.writeUInt4(*it);
    }
    binIo.writeUInt4(0); // This is the end sign
  }

  void Attribute::load(io::BinaryIO &binIo, bool withVirtualBase /*= true*/) {
    Member::load(binIo,false);

    NodeId _id;

    _id = binIo.readUInt4();
    while (_id) {
      callsContainer.push_back(_id);
      _id = binIo.readUInt4();
    }

    _id = binIo.readUInt4();
    while (_id) {
      hasTypeContainer.push_back(_id);
      _id = binIo.readUInt4();
    }
  }


}


}}}
