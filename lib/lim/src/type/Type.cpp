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

namespace type { 
  Type::Type(NodeId _id, Factory *_factory) :
    Base(_id, _factory),
    m_refers(0),
    hasTypeFormerContainer()
  {
  }

  Type::~Type() {
  }

  void Type::clone(const Type& other, bool tryOnVirtualParent) {
    base::Base::clone(other, false);

    m_refers = other.m_refers;
    hasTypeFormerContainer = other.hasTypeFormerContainer;
  }

  void Type::prepareDelete(bool tryOnVirtualParent){
    while (!hasTypeFormerContainer.empty()) {
      const NodeId id = *hasTypeFormerContainer.begin();
      if (factory->getExistsReverseEdges())
        factory->reverseEdges->removeEdge(id, this->getId(), edkType_HasTypeFormer);
      hasTypeFormerContainer.pop_front();
    }
    base::Base::prepareDelete(false);
  }

  NodeKind Type::getNodeKind() const {
    return ndkType;
  }

  Key Type::getRefersKey() const {
    return m_refers;
  }

  const std::string& Type::getRefers() const {
    return factory->getStringTable().get(m_refers);
  }

  void Type::setRefersKey(Key _refers) {
    m_refers = _refers;
  }

  void Type::setRefers(const std::string& _refers) {
    m_refers = factory->getStringTable().set(_refers);
  }

  ListIterator<type::TypeFormer> Type::getTypeFormerListIteratorBegin() const {
    return ListIterator<type::TypeFormer>(&hasTypeFormerContainer, factory, true);
  }

  ListIterator<type::TypeFormer> Type::getTypeFormerListIteratorEnd() const {
    return ListIterator<type::TypeFormer>(&hasTypeFormerContainer, factory, false);
  }

  bool Type::getTypeFormerIsEmpty() const {
    return getTypeFormerListIteratorBegin() == getTypeFormerListIteratorEnd();
  }

  unsigned int Type::getTypeFormerSize() const {
    unsigned int size = 0;
    ListIterator<type::TypeFormer> endIt = getTypeFormerListIteratorEnd();
    for (ListIterator<type::TypeFormer> it = getTypeFormerListIteratorBegin(); it != endIt; ++it) {
      ++size;
    }
    return size;
  }

  bool Type::setEdge(EdgeKind edgeKind, NodeId edgeEnd, void* acValue, bool tryOnVirtualParent) {
    switch (edgeKind) {
      case edkType_HasTypeFormer:
        addTypeFormer(edgeEnd);
        return true;
      default:
        break;
    }
    if (base::Base::setEdge(edgeKind, edgeEnd, acValue, false)) {
      return true;
    }
    return false;
  }

  bool Type::removeEdge(EdgeKind edgeKind, NodeId edgeEnd, bool tryOnVirtualParent) {
    switch (edgeKind) {
      case edkType_HasTypeFormer:
        removeTypeFormer(edgeEnd);
        return true;
      default:
        break;
    }
    if (base::Base::removeEdge(edgeKind, edgeEnd, false)) {
      return true;
    }
    return false;
  }

  void Type::addTypeFormer(const type::TypeFormer *_node) {
    if (_node == NULL)
      throw LimException(COLUMBUS_LOCATION, CMSG_EX_THE_NODE_IS_NULL);

    if (&(_node->getFactory()) != this->factory)
      throw LimException(COLUMBUS_LOCATION, CMSG_EX_THE_FACTORY_OF_NODES_DOES_NOT_MATCH);

    if (!(Common::getIsTypeFormer(*_node)))
      throw LimException(COLUMBUS_LOCATION, CMSG_EX_INVALID_NODE_KIND);

    hasTypeFormerContainer.push_back(_node->getId());
    if (factory->reverseEdges)
      factory->reverseEdges->insertEdge(_node, this, edkType_HasTypeFormer);
  }

  void Type::addTypeFormer(NodeId _id) {
    const type::TypeFormer *node = dynamic_cast<type::TypeFormer*>(factory->getPointer(_id));
    if (node == NULL)
      throw LimException(COLUMBUS_LOCATION, CMSG_EX_INVALID_NODE_KIND);
    addTypeFormer( node );
  }

  void Type::removeTypeFormer(NodeId id) {
    if (!factory->getExist(id))
      throw LimException(COLUMBUS_LOCATION, CMSG_EX_THE_END_POINT_OF_THE_EDGE_DOES_NOT_EXIST);

    ListIterator<type::TypeFormer>::Container::iterator it = find(hasTypeFormerContainer.begin(), hasTypeFormerContainer.end(), id);

    if (it == hasTypeFormerContainer.end())
      throw LimException(COLUMBUS_LOCATION, CMSG_EX_THE_END_POINT_OF_THE_EDGE_DOES_NOT_EXIST);

    hasTypeFormerContainer.erase(it);

    if (factory->getExistsReverseEdges())
      factory->reverseEdges->removeEdge(id, this->getId(), edkType_HasTypeFormer);
  }

  void Type::removeTypeFormer(type::TypeFormer *_node) {
    if (_node == NULL)
      throw LimException(COLUMBUS_LOCATION, CMSG_EX_THE_EDGE_IS_NULL);

    removeTypeFormer(_node->getId());
  }

  void Type::accept(Visitor &visitor) const {
    visitor.visit(*this);
  }

  void Type::acceptEnd(Visitor &visitor) const {
    visitor.visitEnd(*this);
  }

  double Type::getSimilarity(const base::Base& base){
    if(base.getNodeKind() == getNodeKind()) {
      const Type& node = dynamic_cast<const Type&>(base);
      double matchAttrs = 0;
      std::string str1, str2;
      size_t strMax;
      double strSim;
      str1 = getRefers();
      str2 = node.getRefers();
      strMax = std::max(str1.size(), str2.size());
      strSim = 1 - ((double)common::math::editDistance(str1, str2) / (strMax > 0 ? strMax : 1));
      if (strSim < Common::SimilarityMinForStrings)
        return 0.0;
      matchAttrs += strSim;
      return matchAttrs / (1 / (1 - Common::SimilarityMinimum)) + Common::SimilarityMinimum;
    } else {
      return 0.0;
    }
  }

  void Type::swapStringTable(RefDistributorStrTable& newStrTable, std::map<Key,Key>& oldAndNewStrKeyMap ){
    std::map<Key,Key>::iterator foundKeyId;

    foundKeyId = oldAndNewStrKeyMap.find(m_refers);
    if (foundKeyId != oldAndNewStrKeyMap.end()) {
      m_refers = foundKeyId->second;
    } else {
      Key oldkey = m_refers;
      m_refers = newStrTable.set(factory->getStringTable().get(m_refers));
      oldAndNewStrKeyMap.insert(std::pair<Key,Key>(oldkey,m_refers));    }

  }

  NodeHashType Type::getHash(std::set<NodeId>& travNodes) const {
    if (hashOk) return nodeHashCache;
    common::WriteMsg::write(CMSG_GET_THE_NODE_HASH_OF_NODE_BEGIN,this->getId()); 
    if (travNodes.count(getId())>0) {
      common::WriteMsg::write(CMSG_GET_THE_NODE_HASH_OF_NODE_SKIP);
      return 0;
    }
    travNodes.insert(getId());
    Crc_type resultHash;
    resultHash.process_bytes( "type::Type", strlen("type::Type"));
    common::WriteMsg::write(CMSG_GET_THE_NODE_HASH_OF_NODE_END,resultHash.checksum()); 
    nodeHashCache = resultHash.checksum();
    hashOk = true;
    return nodeHashCache;
  }

  void Type::save(io::BinaryIO &binIo,bool withVirtualBase  /*= true*/) const {
    Base::save(binIo,false);

    factory->getStringTable().setType(m_refers, StrTable::strToSave);
    binIo.writeUInt4(m_refers);


    for (ListIterator<type::TypeFormer>::Container::const_iterator it = hasTypeFormerContainer.begin(); it != hasTypeFormerContainer.end(); ++it) {
      binIo.writeUInt4(*it);
    }
    binIo.writeUInt4(0); // This is the end sign
  }

  void Type::load(io::BinaryIO &binIo, bool withVirtualBase /*= true*/) {
    Base::load(binIo,false);

    m_refers = binIo.readUInt4();

    NodeId _id;

    _id = binIo.readUInt4();
    while (_id) {
      hasTypeFormerContainer.push_back(_id);
      _id = binIo.readUInt4();
    }
  }


}


}}}
