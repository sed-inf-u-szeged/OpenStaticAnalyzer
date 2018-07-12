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

#include "java/inc/java.h"
#include "java/inc/Common.h"
#include "common/inc/WriteMessage.h"

#include "java/inc/messages.h"
#include <algorithm>
#include <string.h>
#include "common/inc/math/common.h"
#include <sstream>


namespace columbus { namespace java { namespace asg {

typedef boost::crc_32_type  Crc_type;

namespace type { 
  ArrayType::ArrayType(NodeId _id, Factory *_factory) :
    Type(_id, _factory),
    m_size(0),
    m_componentType(0)
  {
  }

  ArrayType::~ArrayType() {
  }

  void ArrayType::clone(const ArrayType& other, bool tryOnVirtualParent) {
    type::Type::clone(other, false);

    m_size = other.m_size;
    m_componentType = other.m_componentType;
  }

  void ArrayType::prepareDelete(bool tryOnVirtualParent){
    removeComponentType();
    type::Type::prepareDelete(false);
  }

  NodeKind ArrayType::getNodeKind() const {
    return ndkArrayType;
  }

  unsigned ArrayType::getSize() const {
    return m_size;
  }

  void ArrayType::setSize(unsigned _size) {
    m_size = _size;
  }

  type::Type* ArrayType::getComponentType() const {
    type::Type *_node = NULL;
    if (m_componentType != 0)
      _node = dynamic_cast<type::Type*>(factory->getPointer(m_componentType));
    if ( (_node == NULL) || factory->getIsFiltered(_node))
      return NULL;

    return _node;
  }

  bool ArrayType::setEdge(EdgeKind edgeKind, NodeId edgeEnd, bool tryOnVirtualParent) {
    switch (edgeKind) {
      case edkArrayType_ComponentType:
        setComponentType(edgeEnd);
        return true;
      default:
        break;
    }
    if (type::Type::setEdge(edgeKind, edgeEnd, false)) {
      return true;
    }
    return false;
  }

  bool ArrayType::removeEdge(EdgeKind edgeKind, NodeId edgeEnd, bool tryOnVirtualParent) {
    switch (edgeKind) {
      case edkArrayType_ComponentType:
        removeComponentType();
        return true;
      default:
        break;
    }
    if (type::Type::removeEdge(edgeKind, edgeEnd, false)) {
      return true;
    }
    return false;
  }

  void ArrayType::setComponentType(NodeId _id) {
    type::Type *_node = NULL;
    if (_id) {
      if (!factory->getExist(_id))
        throw JavaException(COLUMBUS_LOCATION, CMSG_EX_THE_END_POINT_OF_THE_EDGE_DOES_NOT_EXIST);

      _node = dynamic_cast<type::Type*> (factory->getPointer(_id));
      if ( _node == NULL) {
        throw JavaException(COLUMBUS_LOCATION, CMSG_EX_INVALID_NODE_KIND);
      }
      if (&(_node->getFactory()) != this->factory)
        throw JavaException(COLUMBUS_LOCATION, CMSG_EX_THE_FACTORY_OF_NODES_DOES_NOT_MATCH );

      if (m_componentType) {
        if (factory->getExistsReverseEdges())
          factory->reverseEdges->removeEdge(m_componentType, m_id, edkArrayType_ComponentType);
      }
      m_componentType = _node->getId();
      if (factory->getExistsReverseEdges())
        factory->reverseEdges->insertEdge(m_componentType, this->getId(), edkArrayType_ComponentType);
    } else {
      if (m_componentType) {
        throw JavaException(COLUMBUS_LOCATION, CMSG_EX_CAN_T_SET_EDGE_TO_NULL);
      }
    }
  }

  void ArrayType::setComponentType(type::Type *_node) {
    if (_node == NULL)
      throw JavaException(COLUMBUS_LOCATION, CMSG_EX_CAN_T_SET_EDGE_TO_NULL);

    setComponentType(_node->getId());
  }

  void ArrayType::removeComponentType() {
      if (m_componentType) {
        if (factory->getExistsReverseEdges())
          factory->reverseEdges->removeEdge(m_componentType, m_id, edkArrayType_ComponentType);
      }
      m_componentType = 0;
  }

  void ArrayType::accept(Visitor &visitor) const {
    visitor.visit(*this);
  }

  void ArrayType::acceptEnd(Visitor &visitor) const {
    visitor.visitEnd(*this);
  }

  double ArrayType::getSimilarity(const base::Base& base){
    if(base.getNodeKind() == getNodeKind()) {
      const ArrayType& node = dynamic_cast<const ArrayType&>(base);
      double matchAttrs = 0;
      if(node.getSize() == getSize()) ++matchAttrs;
      return matchAttrs / (1 / (1 - Common::SimilarityMinimum)) + Common::SimilarityMinimum;
    } else {
      return 0.0;
    }
  }

  void ArrayType::swapStringTable(RefDistributorStrTable& newStrTable, std::map<Key,Key>& oldAndNewStrKeyMap ){
    std::map<Key,Key>::iterator foundKeyId;

  }

  NodeHashType ArrayType::getHash(std::set<NodeId>& travNodes) const {
    if (hashOk) return nodeHashCache;
    common::WriteMsg::write(CMSG_GET_THE_NODE_HASH_OF_NODE_BEGIN,this->getId()); 
    if (travNodes.count(getId())>0) {
      common::WriteMsg::write(CMSG_GET_THE_NODE_HASH_OF_NODE_SKIP);
      return 0;
    }
    travNodes.insert(getId());
    Crc_type resultHash;
    resultHash.process_bytes( "type::ArrayType", strlen("type::ArrayType"));
    common::WriteMsg::write(CMSG_GET_THE_NODE_HASH_OF_NODE_END,resultHash.checksum()); 
    nodeHashCache = resultHash.checksum();
    hashOk = true;
    return nodeHashCache;
  }

  void ArrayType::sort(bool withVirtualBase /* = true */) {
    Type::sort(false);
  }

  void ArrayType::save(io::BinaryIO &binIo,bool withVirtualBase  /*= true*/) const {
    Type::save(binIo,false);

    binIo.writeUInt4(m_size);

    binIo.writeUInt4(m_componentType);

  }

  void ArrayType::load(io::BinaryIO &binIo, bool withVirtualBase /*= true*/) {
    Type::load(binIo,false);

    m_size = binIo.readUInt4();

    m_componentType =  binIo.readUInt4();

  }


}


}}}
