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
  MethodType::MethodType(NodeId _id, Factory *_factory) :
    Type(_id, _factory),
    m_returnType(0),
    parameterTypesContainer(),
    thrownTypesContainer()
  {
  }

  MethodType::~MethodType() {
  }

  void MethodType::clone(const MethodType& other, bool tryOnVirtualParent) {
    type::Type::clone(other, false);

    m_returnType = other.m_returnType;
    parameterTypesContainer = other.parameterTypesContainer;
    thrownTypesContainer = other.thrownTypesContainer;
  }

  void MethodType::prepareDelete(bool tryOnVirtualParent){
    removeReturnType();
    while (!parameterTypesContainer.empty()) {
      const NodeId id = *parameterTypesContainer.begin();
      if (factory->getExistsReverseEdges())
        factory->reverseEdges->removeEdge(id, this->getId(), edkMethodType_ParameterTypes);
      parameterTypesContainer.pop_front();
    }
    while (!thrownTypesContainer.empty()) {
      const NodeId id = *thrownTypesContainer.begin();
      if (factory->getExistsReverseEdges())
        factory->reverseEdges->removeEdge(id, this->getId(), edkMethodType_ThrownTypes);
      thrownTypesContainer.pop_front();
    }
    type::Type::prepareDelete(false);
  }

  NodeKind MethodType::getNodeKind() const {
    return ndkMethodType;
  }

  type::Type* MethodType::getReturnType() const {
    type::Type *_node = NULL;
    if (m_returnType != 0)
      _node = dynamic_cast<type::Type*>(factory->getPointer(m_returnType));
    if ( (_node == NULL) || factory->getIsFiltered(_node))
      return NULL;

    return _node;
  }

  ListIterator<type::Type> MethodType::getParameterTypesListIteratorBegin() const {
    return ListIterator<type::Type>(&parameterTypesContainer, factory, true);
  }

  ListIterator<type::Type> MethodType::getParameterTypesListIteratorEnd() const {
    return ListIterator<type::Type>(&parameterTypesContainer, factory, false);
  }

  bool MethodType::getParameterTypesIsEmpty() const {
    return getParameterTypesListIteratorBegin() == getParameterTypesListIteratorEnd();
  }

  unsigned int MethodType::getParameterTypesSize() const {
    unsigned int size = 0;
    ListIterator<type::Type> endIt = getParameterTypesListIteratorEnd();
    for (ListIterator<type::Type> it = getParameterTypesListIteratorBegin(); it != endIt; ++it) {
      ++size;
    }
    return size;
  }

  ListIterator<type::Type> MethodType::getThrownTypesListIteratorBegin() const {
    return ListIterator<type::Type>(&thrownTypesContainer, factory, true);
  }

  ListIterator<type::Type> MethodType::getThrownTypesListIteratorEnd() const {
    return ListIterator<type::Type>(&thrownTypesContainer, factory, false);
  }

  bool MethodType::getThrownTypesIsEmpty() const {
    return getThrownTypesListIteratorBegin() == getThrownTypesListIteratorEnd();
  }

  unsigned int MethodType::getThrownTypesSize() const {
    unsigned int size = 0;
    ListIterator<type::Type> endIt = getThrownTypesListIteratorEnd();
    for (ListIterator<type::Type> it = getThrownTypesListIteratorBegin(); it != endIt; ++it) {
      ++size;
    }
    return size;
  }

  bool MethodType::setEdge(EdgeKind edgeKind, NodeId edgeEnd, bool tryOnVirtualParent) {
    switch (edgeKind) {
      case edkMethodType_ReturnType:
        setReturnType(edgeEnd);
        return true;
      case edkMethodType_ParameterTypes:
        addParameterTypes(edgeEnd);
        return true;
      case edkMethodType_ThrownTypes:
        addThrownTypes(edgeEnd);
        return true;
      default:
        break;
    }
    if (type::Type::setEdge(edgeKind, edgeEnd, false)) {
      return true;
    }
    return false;
  }

  bool MethodType::removeEdge(EdgeKind edgeKind, NodeId edgeEnd, bool tryOnVirtualParent) {
    switch (edgeKind) {
      case edkMethodType_ReturnType:
        removeReturnType();
        return true;
      case edkMethodType_ParameterTypes:
        removeParameterTypes(edgeEnd);
        return true;
      case edkMethodType_ThrownTypes:
        removeThrownTypes(edgeEnd);
        return true;
      default:
        break;
    }
    if (type::Type::removeEdge(edgeKind, edgeEnd, false)) {
      return true;
    }
    return false;
  }

  void MethodType::setReturnType(NodeId _id) {
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

      if (m_returnType) {
        if (factory->getExistsReverseEdges())
          factory->reverseEdges->removeEdge(m_returnType, m_id, edkMethodType_ReturnType);
      }
      m_returnType = _node->getId();
      if (factory->getExistsReverseEdges())
        factory->reverseEdges->insertEdge(m_returnType, this->getId(), edkMethodType_ReturnType);
    } else {
      if (m_returnType) {
        throw JavaException(COLUMBUS_LOCATION, CMSG_EX_CAN_T_SET_EDGE_TO_NULL);
      }
    }
  }

  void MethodType::setReturnType(type::Type *_node) {
    if (_node == NULL)
      throw JavaException(COLUMBUS_LOCATION, CMSG_EX_CAN_T_SET_EDGE_TO_NULL);

    setReturnType(_node->getId());
  }

  void MethodType::removeReturnType() {
      if (m_returnType) {
        if (factory->getExistsReverseEdges())
          factory->reverseEdges->removeEdge(m_returnType, m_id, edkMethodType_ReturnType);
      }
      m_returnType = 0;
  }

  void MethodType::addParameterTypes(const type::Type *_node) {
    if (_node == NULL)
      throw JavaException(COLUMBUS_LOCATION, CMSG_EX_THE_NODE_IS_NULL);

    if (&(_node->getFactory()) != this->factory)
      throw JavaException(COLUMBUS_LOCATION, CMSG_EX_THE_FACTORY_OF_NODES_DOES_NOT_MATCH);

    if (!(Common::getIsType(*_node)))
      throw JavaException(COLUMBUS_LOCATION, CMSG_EX_INVALID_NODE_KIND);

    parameterTypesContainer.push_back(_node->getId());
    if (factory->reverseEdges)
      factory->reverseEdges->insertEdge(_node, this, edkMethodType_ParameterTypes);
  }

  void MethodType::addParameterTypes(NodeId _id) {
    const type::Type *node = dynamic_cast<type::Type*>(factory->getPointer(_id));
    if (node == NULL)
      throw JavaException(COLUMBUS_LOCATION, CMSG_EX_INVALID_NODE_KIND);
    addParameterTypes( node );
  }

  void MethodType::removeParameterTypes(NodeId id) {
    if (!factory->getExist(id))
      throw JavaException(COLUMBUS_LOCATION, CMSG_EX_THE_END_POINT_OF_THE_EDGE_DOES_NOT_EXIST);

    ListIterator<type::Type>::Container::iterator it = find(parameterTypesContainer.begin(), parameterTypesContainer.end(), id);

    if (it == parameterTypesContainer.end())
      throw JavaException(COLUMBUS_LOCATION, CMSG_EX_THE_END_POINT_OF_THE_EDGE_DOES_NOT_EXIST);

    parameterTypesContainer.erase(it);

    if (factory->getExistsReverseEdges())
      factory->reverseEdges->removeEdge(id, this->getId(), edkMethodType_ParameterTypes);
  }

  void MethodType::removeParameterTypes(type::Type *_node) {
    if (_node == NULL)
      throw JavaException(COLUMBUS_LOCATION, CMSG_EX_THE_EDGE_IS_NULL);

    removeParameterTypes(_node->getId());
  }

  void MethodType::addThrownTypes(const type::Type *_node) {
    if (_node == NULL)
      throw JavaException(COLUMBUS_LOCATION, CMSG_EX_THE_NODE_IS_NULL);

    if (&(_node->getFactory()) != this->factory)
      throw JavaException(COLUMBUS_LOCATION, CMSG_EX_THE_FACTORY_OF_NODES_DOES_NOT_MATCH);

    if (!(Common::getIsType(*_node)))
      throw JavaException(COLUMBUS_LOCATION, CMSG_EX_INVALID_NODE_KIND);

    thrownTypesContainer.push_back(_node->getId());
    if (factory->reverseEdges)
      factory->reverseEdges->insertEdge(_node, this, edkMethodType_ThrownTypes);
  }

  void MethodType::addThrownTypes(NodeId _id) {
    const type::Type *node = dynamic_cast<type::Type*>(factory->getPointer(_id));
    if (node == NULL)
      throw JavaException(COLUMBUS_LOCATION, CMSG_EX_INVALID_NODE_KIND);
    addThrownTypes( node );
  }

  void MethodType::removeThrownTypes(NodeId id) {
    if (!factory->getExist(id))
      throw JavaException(COLUMBUS_LOCATION, CMSG_EX_THE_END_POINT_OF_THE_EDGE_DOES_NOT_EXIST);

    ListIterator<type::Type>::Container::iterator it = find(thrownTypesContainer.begin(), thrownTypesContainer.end(), id);

    if (it == thrownTypesContainer.end())
      throw JavaException(COLUMBUS_LOCATION, CMSG_EX_THE_END_POINT_OF_THE_EDGE_DOES_NOT_EXIST);

    thrownTypesContainer.erase(it);

    if (factory->getExistsReverseEdges())
      factory->reverseEdges->removeEdge(id, this->getId(), edkMethodType_ThrownTypes);
  }

  void MethodType::removeThrownTypes(type::Type *_node) {
    if (_node == NULL)
      throw JavaException(COLUMBUS_LOCATION, CMSG_EX_THE_EDGE_IS_NULL);

    removeThrownTypes(_node->getId());
  }

  void MethodType::accept(Visitor &visitor) const {
    visitor.visit(*this);
  }

  void MethodType::acceptEnd(Visitor &visitor) const {
    visitor.visitEnd(*this);
  }

  double MethodType::getSimilarity(const base::Base& base){
    if(base.getNodeKind() == getNodeKind()) {
      return 1.0;
    } else {
      return 0.0;
    }
  }

  void MethodType::swapStringTable(RefDistributorStrTable& newStrTable, std::map<Key,Key>& oldAndNewStrKeyMap ){
    std::map<Key,Key>::iterator foundKeyId;

  }

  NodeHashType MethodType::getHash(std::set<NodeId>& travNodes) const {
    if (hashOk) return nodeHashCache;
    common::WriteMsg::write(CMSG_GET_THE_NODE_HASH_OF_NODE_BEGIN,this->getId()); 
    if (travNodes.count(getId())>0) {
      common::WriteMsg::write(CMSG_GET_THE_NODE_HASH_OF_NODE_SKIP);
      return 0;
    }
    travNodes.insert(getId());
    Crc_type resultHash;
    resultHash.process_bytes( "type::MethodType", strlen("type::MethodType"));
    common::WriteMsg::write(CMSG_GET_THE_NODE_HASH_OF_NODE_END,resultHash.checksum()); 
    nodeHashCache = resultHash.checksum();
    hashOk = true;
    return nodeHashCache;
  }

  void MethodType::sort(bool withVirtualBase /* = true */) {
    Type::sort(false);
  }

  void MethodType::save(io::BinaryIO &binIo,bool withVirtualBase  /*= true*/) const {
    Type::save(binIo,false);

    binIo.writeUInt4(m_returnType);


    for (ListIterator<type::Type>::Container::const_iterator it = parameterTypesContainer.begin(); it != parameterTypesContainer.end(); ++it) {
      binIo.writeUInt4(*it);
    }
    binIo.writeUInt4(0); // This is the end sign

    for (ListIterator<type::Type>::Container::const_iterator it = thrownTypesContainer.begin(); it != thrownTypesContainer.end(); ++it) {
      binIo.writeUInt4(*it);
    }
    binIo.writeUInt4(0); // This is the end sign
  }

  void MethodType::load(io::BinaryIO &binIo, bool withVirtualBase /*= true*/) {
    Type::load(binIo,false);

    m_returnType =  binIo.readUInt4();

    NodeId _id;

    _id = binIo.readUInt4();
    while (_id) {
      parameterTypesContainer.push_back(_id);
      _id = binIo.readUInt4();
    }

    _id = binIo.readUInt4();
    while (_id) {
      thrownTypesContainer.push_back(_id);
      _id = binIo.readUInt4();
    }
  }


}


}}}
