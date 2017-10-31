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
  GenericParameter::GenericParameter(NodeId _id, Factory *_factory) :
    Named(_id, _factory),
    m_genericParameterKind(gpkConstraint),
    hasParameterConstraintContainer()
  {
  }

  GenericParameter::~GenericParameter() {
  }

  void GenericParameter::clone(const GenericParameter& other, bool tryOnVirtualParent) {
    base::Named::clone(other, false);

    m_genericParameterKind = other.m_genericParameterKind;
    hasParameterConstraintContainer = other.hasParameterConstraintContainer;
  }

  void GenericParameter::prepareDelete(bool tryOnVirtualParent){
    while (!hasParameterConstraintContainer.empty()) {
      const NodeId id = *hasParameterConstraintContainer.begin();
      if (factory->getExistsReverseEdges())
        factory->reverseEdges->removeEdge(id, this->getId(), edkGenericParameter_HasParameterConstraint);
      hasParameterConstraintContainer.pop_front();
    }
    base::Named::prepareDelete(false);
  }

  NodeKind GenericParameter::getNodeKind() const {
    return ndkGenericParameter;
  }

  GenericParameterKind GenericParameter::getGenericParameterKind() const {
    return m_genericParameterKind;
  }

  void GenericParameter::setGenericParameterKind(GenericParameterKind _genericParameterKind) {
    m_genericParameterKind = _genericParameterKind;
  }

  ListIterator<type::Type> GenericParameter::getParameterConstraintListIteratorBegin() const {
    return ListIterator<type::Type>(&hasParameterConstraintContainer, factory, true);
  }

  ListIterator<type::Type> GenericParameter::getParameterConstraintListIteratorEnd() const {
    return ListIterator<type::Type>(&hasParameterConstraintContainer, factory, false);
  }

  bool GenericParameter::getParameterConstraintIsEmpty() const {
    return getParameterConstraintListIteratorBegin() == getParameterConstraintListIteratorEnd();
  }

  unsigned int GenericParameter::getParameterConstraintSize() const {
    unsigned int size = 0;
    ListIterator<type::Type> endIt = getParameterConstraintListIteratorEnd();
    for (ListIterator<type::Type> it = getParameterConstraintListIteratorBegin(); it != endIt; ++it) {
      ++size;
    }
    return size;
  }

  bool GenericParameter::setEdge(EdgeKind edgeKind, NodeId edgeEnd, void* acValue, bool tryOnVirtualParent) {
    switch (edgeKind) {
      case edkGenericParameter_HasParameterConstraint:
        addParameterConstraint(edgeEnd);
        return true;
      default:
        break;
    }
    if (base::Named::setEdge(edgeKind, edgeEnd, acValue, false)) {
      return true;
    }
    return false;
  }

  bool GenericParameter::removeEdge(EdgeKind edgeKind, NodeId edgeEnd, bool tryOnVirtualParent) {
    switch (edgeKind) {
      case edkGenericParameter_HasParameterConstraint:
        removeParameterConstraint(edgeEnd);
        return true;
      default:
        break;
    }
    if (base::Named::removeEdge(edgeKind, edgeEnd, false)) {
      return true;
    }
    return false;
  }

  void GenericParameter::addParameterConstraint(const type::Type *_node) {
    if (_node == NULL)
      throw LimException(COLUMBUS_LOCATION, CMSG_EX_THE_NODE_IS_NULL);

    if (&(_node->getFactory()) != this->factory)
      throw LimException(COLUMBUS_LOCATION, CMSG_EX_THE_FACTORY_OF_NODES_DOES_NOT_MATCH);

    if (!((_node->getNodeKind() == ndkType) ))
      throw LimException(COLUMBUS_LOCATION, CMSG_EX_INVALID_NODE_KIND);

    hasParameterConstraintContainer.push_back(_node->getId());
    if (factory->reverseEdges)
      factory->reverseEdges->insertEdge(_node, this, edkGenericParameter_HasParameterConstraint);
  }

  void GenericParameter::addParameterConstraint(NodeId _id) {
    const type::Type *node = dynamic_cast<type::Type*>(factory->getPointer(_id));
    if (node == NULL)
      throw LimException(COLUMBUS_LOCATION, CMSG_EX_INVALID_NODE_KIND);
    addParameterConstraint( node );
  }

  void GenericParameter::removeParameterConstraint(NodeId id) {
    if (!factory->getExist(id))
      throw LimException(COLUMBUS_LOCATION, CMSG_EX_THE_END_POINT_OF_THE_EDGE_DOES_NOT_EXIST);

    ListIterator<type::Type>::Container::iterator it = find(hasParameterConstraintContainer.begin(), hasParameterConstraintContainer.end(), id);

    if (it == hasParameterConstraintContainer.end())
      throw LimException(COLUMBUS_LOCATION, CMSG_EX_THE_END_POINT_OF_THE_EDGE_DOES_NOT_EXIST);

    hasParameterConstraintContainer.erase(it);

    if (factory->getExistsReverseEdges())
      factory->reverseEdges->removeEdge(id, this->getId(), edkGenericParameter_HasParameterConstraint);
  }

  void GenericParameter::removeParameterConstraint(type::Type *_node) {
    if (_node == NULL)
      throw LimException(COLUMBUS_LOCATION, CMSG_EX_THE_EDGE_IS_NULL);

    removeParameterConstraint(_node->getId());
  }

  void GenericParameter::accept(Visitor &visitor) const {
    visitor.visit(*this);
  }

  void GenericParameter::acceptEnd(Visitor &visitor) const {
    visitor.visitEnd(*this);
  }

  double GenericParameter::getSimilarity(const base::Base& base){
    if(base.getNodeKind() == getNodeKind()) {
      const GenericParameter& node = dynamic_cast<const GenericParameter&>(base);
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
      if(node.getGenericParameterKind() == getGenericParameterKind()) ++matchAttrs;
      return matchAttrs / (2 / (1 - Common::SimilarityMinimum)) + Common::SimilarityMinimum;
    } else {
      return 0.0;
    }
  }

  void GenericParameter::swapStringTable(RefDistributorStrTable& newStrTable, std::map<Key,Key>& oldAndNewStrKeyMap ){
    std::map<Key,Key>::iterator foundKeyId;

    foundKeyId = oldAndNewStrKeyMap.find(m_name);
    if (foundKeyId != oldAndNewStrKeyMap.end()) {
      m_name = foundKeyId->second;
    } else {
      Key oldkey = m_name;
      m_name = newStrTable.set(factory->getStringTable().get(m_name));
      oldAndNewStrKeyMap.insert(std::pair<Key,Key>(oldkey,m_name));    }

  }

  NodeHashType GenericParameter::getHash(std::set<NodeId>& travNodes) const {
    if (hashOk) return nodeHashCache;
    common::WriteMsg::write(CMSG_GET_THE_NODE_HASH_OF_NODE_BEGIN,this->getId()); 
    if (travNodes.count(getId())>0) {
      common::WriteMsg::write(CMSG_GET_THE_NODE_HASH_OF_NODE_SKIP);
      return 0;
    }
    travNodes.insert(getId());
    Crc_type resultHash;
    resultHash.process_bytes( "logical::GenericParameter", strlen("logical::GenericParameter"));
    common::WriteMsg::write(CMSG_GET_THE_NODE_HASH_OF_NODE_END,resultHash.checksum()); 
    nodeHashCache = resultHash.checksum();
    hashOk = true;
    return nodeHashCache;
  }

  void GenericParameter::save(io::BinaryIO &binIo,bool withVirtualBase  /*= true*/) const {
    Named::save(binIo,false);

    binIo.writeUByte1(m_genericParameterKind);


    for (ListIterator<type::Type>::Container::const_iterator it = hasParameterConstraintContainer.begin(); it != hasParameterConstraintContainer.end(); ++it) {
      binIo.writeUInt4(*it);
    }
    binIo.writeUInt4(0); // This is the end sign
  }

  void GenericParameter::load(io::BinaryIO &binIo, bool withVirtualBase /*= true*/) {
    Named::load(binIo,false);

    m_genericParameterKind = (GenericParameterKind)binIo.readUByte1();

    NodeId _id;

    _id = binIo.readUInt4();
    while (_id) {
      hasParameterConstraintContainer.push_back(_id);
      _id = binIo.readUInt4();
    }
  }


}


}}}
