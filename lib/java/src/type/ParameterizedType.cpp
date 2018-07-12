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
  ParameterizedType::ParameterizedType(NodeId _id, Factory *_factory) :
    ScopedType(_id, _factory),
    m_rawType(0),
    argumentTypesContainer()
  {
  }

  ParameterizedType::~ParameterizedType() {
  }

  void ParameterizedType::clone(const ParameterizedType& other, bool tryOnVirtualParent) {
    type::ScopedType::clone(other, false);

    m_rawType = other.m_rawType;
    argumentTypesContainer = other.argumentTypesContainer;
  }

  void ParameterizedType::prepareDelete(bool tryOnVirtualParent){
    removeRawType();
    while (!argumentTypesContainer.empty()) {
      const NodeId id = *argumentTypesContainer.begin();
      if (factory->getExistsReverseEdges())
        factory->reverseEdges->removeEdge(id, this->getId(), edkParameterizedType_ArgumentTypes);
      argumentTypesContainer.pop_front();
    }
    type::ScopedType::prepareDelete(false);
  }

  NodeKind ParameterizedType::getNodeKind() const {
    return ndkParameterizedType;
  }

  type::Type* ParameterizedType::getRawType() const {
    type::Type *_node = NULL;
    if (m_rawType != 0)
      _node = dynamic_cast<type::Type*>(factory->getPointer(m_rawType));
    if ( (_node == NULL) || factory->getIsFiltered(_node))
      return NULL;

    return _node;
  }

  ListIterator<type::Type> ParameterizedType::getArgumentTypesListIteratorBegin() const {
    return ListIterator<type::Type>(&argumentTypesContainer, factory, true);
  }

  ListIterator<type::Type> ParameterizedType::getArgumentTypesListIteratorEnd() const {
    return ListIterator<type::Type>(&argumentTypesContainer, factory, false);
  }

  bool ParameterizedType::getArgumentTypesIsEmpty() const {
    return getArgumentTypesListIteratorBegin() == getArgumentTypesListIteratorEnd();
  }

  unsigned int ParameterizedType::getArgumentTypesSize() const {
    unsigned int size = 0;
    ListIterator<type::Type> endIt = getArgumentTypesListIteratorEnd();
    for (ListIterator<type::Type> it = getArgumentTypesListIteratorBegin(); it != endIt; ++it) {
      ++size;
    }
    return size;
  }

  bool ParameterizedType::setEdge(EdgeKind edgeKind, NodeId edgeEnd, bool tryOnVirtualParent) {
    switch (edgeKind) {
      case edkParameterizedType_RawType:
        setRawType(edgeEnd);
        return true;
      case edkParameterizedType_ArgumentTypes:
        addArgumentTypes(edgeEnd);
        return true;
      default:
        break;
    }
    if (type::ScopedType::setEdge(edgeKind, edgeEnd, false)) {
      return true;
    }
    return false;
  }

  bool ParameterizedType::removeEdge(EdgeKind edgeKind, NodeId edgeEnd, bool tryOnVirtualParent) {
    switch (edgeKind) {
      case edkParameterizedType_RawType:
        removeRawType();
        return true;
      case edkParameterizedType_ArgumentTypes:
        removeArgumentTypes(edgeEnd);
        return true;
      default:
        break;
    }
    if (type::ScopedType::removeEdge(edgeKind, edgeEnd, false)) {
      return true;
    }
    return false;
  }

  void ParameterizedType::setRawType(NodeId _id) {
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

      if (m_rawType) {
        if (factory->getExistsReverseEdges())
          factory->reverseEdges->removeEdge(m_rawType, m_id, edkParameterizedType_RawType);
      }
      m_rawType = _node->getId();
      if (factory->getExistsReverseEdges())
        factory->reverseEdges->insertEdge(m_rawType, this->getId(), edkParameterizedType_RawType);
    } else {
      if (m_rawType) {
        throw JavaException(COLUMBUS_LOCATION, CMSG_EX_CAN_T_SET_EDGE_TO_NULL);
      }
    }
  }

  void ParameterizedType::setRawType(type::Type *_node) {
    if (_node == NULL)
      throw JavaException(COLUMBUS_LOCATION, CMSG_EX_CAN_T_SET_EDGE_TO_NULL);

    setRawType(_node->getId());
  }

  void ParameterizedType::removeRawType() {
      if (m_rawType) {
        if (factory->getExistsReverseEdges())
          factory->reverseEdges->removeEdge(m_rawType, m_id, edkParameterizedType_RawType);
      }
      m_rawType = 0;
  }

  void ParameterizedType::addArgumentTypes(const type::Type *_node) {
    if (_node == NULL)
      throw JavaException(COLUMBUS_LOCATION, CMSG_EX_THE_NODE_IS_NULL);

    if (&(_node->getFactory()) != this->factory)
      throw JavaException(COLUMBUS_LOCATION, CMSG_EX_THE_FACTORY_OF_NODES_DOES_NOT_MATCH);

    if (!(Common::getIsType(*_node)))
      throw JavaException(COLUMBUS_LOCATION, CMSG_EX_INVALID_NODE_KIND);

    argumentTypesContainer.push_back(_node->getId());
    if (factory->reverseEdges)
      factory->reverseEdges->insertEdge(_node, this, edkParameterizedType_ArgumentTypes);
  }

  void ParameterizedType::addArgumentTypes(NodeId _id) {
    const type::Type *node = dynamic_cast<type::Type*>(factory->getPointer(_id));
    if (node == NULL)
      throw JavaException(COLUMBUS_LOCATION, CMSG_EX_INVALID_NODE_KIND);
    addArgumentTypes( node );
  }

  void ParameterizedType::removeArgumentTypes(NodeId id) {
    if (!factory->getExist(id))
      throw JavaException(COLUMBUS_LOCATION, CMSG_EX_THE_END_POINT_OF_THE_EDGE_DOES_NOT_EXIST);

    ListIterator<type::Type>::Container::iterator it = find(argumentTypesContainer.begin(), argumentTypesContainer.end(), id);

    if (it == argumentTypesContainer.end())
      throw JavaException(COLUMBUS_LOCATION, CMSG_EX_THE_END_POINT_OF_THE_EDGE_DOES_NOT_EXIST);

    argumentTypesContainer.erase(it);

    if (factory->getExistsReverseEdges())
      factory->reverseEdges->removeEdge(id, this->getId(), edkParameterizedType_ArgumentTypes);
  }

  void ParameterizedType::removeArgumentTypes(type::Type *_node) {
    if (_node == NULL)
      throw JavaException(COLUMBUS_LOCATION, CMSG_EX_THE_EDGE_IS_NULL);

    removeArgumentTypes(_node->getId());
  }

  void ParameterizedType::accept(Visitor &visitor) const {
    visitor.visit(*this);
  }

  void ParameterizedType::acceptEnd(Visitor &visitor) const {
    visitor.visitEnd(*this);
  }

  double ParameterizedType::getSimilarity(const base::Base& base){
    if(base.getNodeKind() == getNodeKind()) {
      return 1.0;
    } else {
      return 0.0;
    }
  }

  void ParameterizedType::swapStringTable(RefDistributorStrTable& newStrTable, std::map<Key,Key>& oldAndNewStrKeyMap ){
    std::map<Key,Key>::iterator foundKeyId;

  }

  NodeHashType ParameterizedType::getHash(std::set<NodeId>& travNodes) const {
    if (hashOk) return nodeHashCache;
    common::WriteMsg::write(CMSG_GET_THE_NODE_HASH_OF_NODE_BEGIN,this->getId()); 
    if (travNodes.count(getId())>0) {
      common::WriteMsg::write(CMSG_GET_THE_NODE_HASH_OF_NODE_SKIP);
      return 0;
    }
    travNodes.insert(getId());
    Crc_type resultHash;
    resultHash.process_bytes( "type::ParameterizedType", strlen("type::ParameterizedType"));
    common::WriteMsg::write(CMSG_GET_THE_NODE_HASH_OF_NODE_END,resultHash.checksum()); 
    nodeHashCache = resultHash.checksum();
    hashOk = true;
    return nodeHashCache;
  }

  void ParameterizedType::sort(bool withVirtualBase /* = true */) {
    ScopedType::sort(false);
  }

  void ParameterizedType::save(io::BinaryIO &binIo,bool withVirtualBase  /*= true*/) const {
    ScopedType::save(binIo,false);

    binIo.writeUInt4(m_rawType);


    for (ListIterator<type::Type>::Container::const_iterator it = argumentTypesContainer.begin(); it != argumentTypesContainer.end(); ++it) {
      binIo.writeUInt4(*it);
    }
    binIo.writeUInt4(0); // This is the end sign
  }

  void ParameterizedType::load(io::BinaryIO &binIo, bool withVirtualBase /*= true*/) {
    ScopedType::load(binIo,false);

    m_rawType =  binIo.readUInt4();

    NodeId _id;

    _id = binIo.readUInt4();
    while (_id) {
      argumentTypesContainer.push_back(_id);
      _id = binIo.readUInt4();
    }
  }


}


}}}
