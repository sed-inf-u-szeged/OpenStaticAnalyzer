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
  AttributeAccess::AttributeAccess(NodeId _id, Factory *_factory) :
    Base(_id, _factory),
    m_accesses(0),
    m_attribute(0)
  {
  }

  AttributeAccess::~AttributeAccess() {
  }

  void AttributeAccess::clone(const AttributeAccess& other, bool tryOnVirtualParent) {
    base::Base::clone(other, false);

    m_accesses = other.m_accesses;
    m_attribute = other.m_attribute;
  }

  void AttributeAccess::prepareDelete(bool tryOnVirtualParent){
    removeAttribute();
    base::Base::prepareDelete(false);
  }

  NodeKind AttributeAccess::getNodeKind() const {
    return ndkAttributeAccess;
  }

  Key AttributeAccess::getAccessesKey() const {
    return m_accesses;
  }

  const std::string& AttributeAccess::getAccesses() const {
    return factory->getStringTable().get(m_accesses);
  }

  void AttributeAccess::setAccessesKey(Key _accesses) {
    m_accesses = _accesses;
  }

  void AttributeAccess::setAccesses(const std::string& _accesses) {
    m_accesses = factory->getStringTable().set(_accesses);
  }

  logical::Attribute* AttributeAccess::getAttribute() const {
    logical::Attribute *_node = NULL;
    if (m_attribute != 0)
      _node = dynamic_cast<logical::Attribute*>(factory->getPointer(m_attribute));
    if ( (_node == NULL) || factory->getIsFiltered(_node))
      return NULL;

    return _node;
  }

  bool AttributeAccess::setEdge(EdgeKind edgeKind, NodeId edgeEnd, void* acValue, bool tryOnVirtualParent) {
    switch (edgeKind) {
      case edkAttributeAccess_Attribute:
        setAttribute(edgeEnd);
        return true;
      default:
        break;
    }
    if (base::Base::setEdge(edgeKind, edgeEnd, acValue, false)) {
      return true;
    }
    return false;
  }

  bool AttributeAccess::removeEdge(EdgeKind edgeKind, NodeId edgeEnd, bool tryOnVirtualParent) {
    switch (edgeKind) {
      case edkAttributeAccess_Attribute:
        removeAttribute();
        return true;
      default:
        break;
    }
    if (base::Base::removeEdge(edgeKind, edgeEnd, false)) {
      return true;
    }
    return false;
  }

  void AttributeAccess::setAttribute(NodeId _id) {
    logical::Attribute *_node = NULL;
    if (_id) {
      if (!factory->getExist(_id))
        throw LimException(COLUMBUS_LOCATION, CMSG_EX_THE_END_POINT_OF_THE_EDGE_DOES_NOT_EXIST);

      _node = dynamic_cast<logical::Attribute*> (factory->getPointer(_id));
      if ( _node == NULL) {
        throw LimException(COLUMBUS_LOCATION, CMSG_EX_INVALID_NODE_KIND);
      }
      if (&(_node->getFactory()) != this->factory)
        throw LimException(COLUMBUS_LOCATION, CMSG_EX_THE_FACTORY_OF_NODES_DOES_NOT_MATCH );

      if (m_attribute) {
        if (factory->getExistsReverseEdges())
          factory->reverseEdges->removeEdge(m_attribute, m_id, edkAttributeAccess_Attribute);
      }
      m_attribute = _node->getId();
      if (factory->getExistsReverseEdges())
        factory->reverseEdges->insertEdge(m_attribute, this->getId(), edkAttributeAccess_Attribute);
    } else {
      if (m_attribute) {
        throw LimException(COLUMBUS_LOCATION, CMSG_EX_CAN_T_SET_EDGE_TO_NULL);
      }
    }
  }

  void AttributeAccess::setAttribute(logical::Attribute *_node) {
    if (_node == NULL)
      throw LimException(COLUMBUS_LOCATION, CMSG_EX_CAN_T_SET_EDGE_TO_NULL);

    setAttribute(_node->getId());
  }

  void AttributeAccess::removeAttribute() {
      if (m_attribute) {
        if (factory->getExistsReverseEdges())
          factory->reverseEdges->removeEdge(m_attribute, m_id, edkAttributeAccess_Attribute);
      }
      m_attribute = 0;
  }

  void AttributeAccess::accept(Visitor &visitor) const {
    visitor.visit(*this);
  }

  void AttributeAccess::acceptEnd(Visitor &visitor) const {
    visitor.visitEnd(*this);
  }

  double AttributeAccess::getSimilarity(const base::Base& base){
    if(base.getNodeKind() == getNodeKind()) {
      const AttributeAccess& node = dynamic_cast<const AttributeAccess&>(base);
      double matchAttrs = 0;
      std::string str1, str2;
      size_t strMax;
      double strSim;
      str1 = getAccesses();
      str2 = node.getAccesses();
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

  void AttributeAccess::swapStringTable(RefDistributorStrTable& newStrTable, std::map<Key,Key>& oldAndNewStrKeyMap ){
    std::map<Key,Key>::iterator foundKeyId;

    foundKeyId = oldAndNewStrKeyMap.find(m_accesses);
    if (foundKeyId != oldAndNewStrKeyMap.end()) {
      m_accesses = foundKeyId->second;
    } else {
      Key oldkey = m_accesses;
      m_accesses = newStrTable.set(factory->getStringTable().get(m_accesses));
      oldAndNewStrKeyMap.insert(std::pair<Key,Key>(oldkey,m_accesses));    }

  }

  NodeHashType AttributeAccess::getHash(std::set<NodeId>& travNodes) const {
    if (hashOk) return nodeHashCache;
    common::WriteMsg::write(CMSG_GET_THE_NODE_HASH_OF_NODE_BEGIN,this->getId()); 
    if (travNodes.count(getId())>0) {
      common::WriteMsg::write(CMSG_GET_THE_NODE_HASH_OF_NODE_SKIP);
      return 0;
    }
    travNodes.insert(getId());
    Crc_type resultHash;
    resultHash.process_bytes( "logical::AttributeAccess", strlen("logical::AttributeAccess"));
    common::WriteMsg::write(CMSG_GET_THE_NODE_HASH_OF_NODE_END,resultHash.checksum()); 
    nodeHashCache = resultHash.checksum();
    hashOk = true;
    return nodeHashCache;
  }

  void AttributeAccess::save(io::BinaryIO &binIo,bool withVirtualBase  /*= true*/) const {
    Base::save(binIo,false);

    factory->getStringTable().setType(m_accesses, StrTable::strToSave);
    binIo.writeUInt4(m_accesses);

    binIo.writeUInt4(m_attribute);

  }

  void AttributeAccess::load(io::BinaryIO &binIo, bool withVirtualBase /*= true*/) {
    Base::load(binIo,false);

    m_accesses = binIo.readUInt4();

    m_attribute =  binIo.readUInt4();

  }


}


}}}
