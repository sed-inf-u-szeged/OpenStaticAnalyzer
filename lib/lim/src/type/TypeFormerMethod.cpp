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
  TypeFormerMethod::TypeFormerMethod(NodeId _id, Factory *_factory) :
    TypeFormer(_id, _factory),
    hasParameterTypeContainer(),
    m_hasReturnType(0)
  {
  }

  TypeFormerMethod::~TypeFormerMethod() {
  }

  void TypeFormerMethod::clone(const TypeFormerMethod& other, bool tryOnVirtualParent) {
    type::TypeFormer::clone(other, false);

    //isAssocEdge
    hasParameterTypeContainer = other.hasParameterTypeContainer;
    m_hasReturnType = other.m_hasReturnType;
  }

  void TypeFormerMethod::prepareDelete(bool tryOnVirtualParent){
    while (!hasParameterTypeContainer.empty()) {
      const NodeId id = *hasParameterTypeContainer.begin();
      if (factory->getExistsReverseEdges())
        factory->reverseEdges->removeEdge(id, this->getId(), edkTypeFormerMethod_HasParameterType);
      hasParameterTypeContainer.pop_front();
    }
    removeReturnType();
    type::TypeFormer::prepareDelete(false);
  }

  NodeKind TypeFormerMethod::getNodeKind() const {
    return ndkTypeFormerMethod;
  }

  ListIteratorAssocParameterKind<type::Type> TypeFormerMethod::getParameterTypeListIteratorAssocBegin() const {
    return ListIteratorAssocParameterKind<type::Type>(&hasParameterTypeContainer, factory, true);
  }

  ListIteratorAssocParameterKind<type::Type> TypeFormerMethod::getParameterTypeListIteratorAssocEnd() const {
    return ListIteratorAssocParameterKind<type::Type>(&hasParameterTypeContainer, factory, false);
  }

  bool TypeFormerMethod::getParameterTypeIsEmpty() const {
    return getParameterTypeListIteratorAssocBegin() == getParameterTypeListIteratorAssocEnd();
  }

  unsigned int TypeFormerMethod::getParameterTypeSize() const {
    unsigned int size = 0;
    ListIteratorAssocParameterKind<type::Type> endIt = getParameterTypeListIteratorAssocEnd();
    for (ListIteratorAssocParameterKind<type::Type> it = getParameterTypeListIteratorAssocBegin(); it != endIt; ++it) {
      ++size;
    }
    return size;
  }

  type::Type* TypeFormerMethod::getReturnType() const {
    type::Type *_node = NULL;
    if (m_hasReturnType != 0)
      _node = dynamic_cast<type::Type*>(factory->getPointer(m_hasReturnType));
    if ( (_node == NULL) || factory->getIsFiltered(_node))
      return NULL;

    return _node;
  }

  bool TypeFormerMethod::setEdge(EdgeKind edgeKind, NodeId edgeEnd, void* acValue, bool tryOnVirtualParent) {
    switch (edgeKind) {
      case edkTypeFormerMethod_HasParameterType:
        addParameterType(edgeEnd, *((ParameterKind*)acValue));
        return true;
      case edkTypeFormerMethod_HasReturnType:
        setReturnType(edgeEnd);
        return true;
      default:
        break;
    }
    if (type::TypeFormer::setEdge(edgeKind, edgeEnd, acValue, false)) {
      return true;
    }
    return false;
  }

  bool TypeFormerMethod::removeEdge(EdgeKind edgeKind, NodeId edgeEnd, bool tryOnVirtualParent) {
    switch (edgeKind) {
      case edkTypeFormerMethod_HasParameterType:
        removeParameterType(edgeEnd);
        return true;
      case edkTypeFormerMethod_HasReturnType:
        removeReturnType();
        return true;
      default:
        break;
    }
    if (type::TypeFormer::removeEdge(edgeKind, edgeEnd, false)) {
      return true;
    }
    return false;
  }

  void TypeFormerMethod::addParameterType(const type::Type *_node, ParameterKind acValue) {
    if (_node == NULL)
      throw LimException(COLUMBUS_LOCATION, CMSG_EX_THE_NODE_IS_NULL);

    if (&(_node->getFactory()) != this->factory)
      throw LimException(COLUMBUS_LOCATION, CMSG_EX_THE_FACTORY_OF_NODES_DOES_NOT_MATCH);

    if (!((_node->getNodeKind() == ndkType) ))
      throw LimException(COLUMBUS_LOCATION, CMSG_EX_INVALID_NODE_KIND);

    AssocEdge<NodeId,ParameterKind> ac(_node->getId(), acValue);
    hasParameterTypeContainer.push_back(ac);
    if (factory->reverseEdges)
      factory->reverseEdges->insertEdge(_node, this, edkTypeFormerMethod_HasParameterType);
  }

  void TypeFormerMethod::addParameterType(NodeId _id, ParameterKind acValue) {
    const type::Type *node = dynamic_cast<type::Type*>(factory->getPointer(_id));
    if (node == NULL)
      throw LimException(COLUMBUS_LOCATION, CMSG_EX_INVALID_NODE_KIND);
    addParameterType( node, acValue );
  }

  void TypeFormerMethod::removeParameterType(NodeId id) {
    if (!factory->getExist(id))
      throw LimException(COLUMBUS_LOCATION, CMSG_EX_THE_END_POINT_OF_THE_EDGE_DOES_NOT_EXIST);

    ListIteratorAssocParameterKind<type::Type>::Container::iterator it = find(hasParameterTypeContainer.begin(), hasParameterTypeContainer.end(), id);

    if (it == hasParameterTypeContainer.end())
      throw LimException(COLUMBUS_LOCATION, CMSG_EX_THE_END_POINT_OF_THE_EDGE_DOES_NOT_EXIST);

    hasParameterTypeContainer.erase(it);

    if (factory->getExistsReverseEdges())
      factory->reverseEdges->removeEdge(id, this->getId(), edkTypeFormerMethod_HasParameterType);
  }

  void TypeFormerMethod::removeParameterType(type::Type *_node) {
    if (_node == NULL)
      throw LimException(COLUMBUS_LOCATION, CMSG_EX_THE_EDGE_IS_NULL);

    removeParameterType(_node->getId());
  }

  void TypeFormerMethod::setReturnType(NodeId _id) {
    type::Type *_node = NULL;
    if (_id) {
      if (!factory->getExist(_id))
        throw LimException(COLUMBUS_LOCATION, CMSG_EX_THE_END_POINT_OF_THE_EDGE_DOES_NOT_EXIST);

      _node = dynamic_cast<type::Type*> (factory->getPointer(_id));
      if ( _node == NULL) {
        throw LimException(COLUMBUS_LOCATION, CMSG_EX_INVALID_NODE_KIND);
      }
      if (&(_node->getFactory()) != this->factory)
        throw LimException(COLUMBUS_LOCATION, CMSG_EX_THE_FACTORY_OF_NODES_DOES_NOT_MATCH );

      if (m_hasReturnType) {
        if (factory->getExistsReverseEdges())
          factory->reverseEdges->removeEdge(m_hasReturnType, m_id, edkTypeFormerMethod_HasReturnType);
      }
      m_hasReturnType = _node->getId();
      if (factory->getExistsReverseEdges())
        factory->reverseEdges->insertEdge(m_hasReturnType, this->getId(), edkTypeFormerMethod_HasReturnType);
    } else {
      if (m_hasReturnType) {
        throw LimException(COLUMBUS_LOCATION, CMSG_EX_CAN_T_SET_EDGE_TO_NULL);
      }
    }
  }

  void TypeFormerMethod::setReturnType(type::Type *_node) {
    if (_node == NULL)
      throw LimException(COLUMBUS_LOCATION, CMSG_EX_CAN_T_SET_EDGE_TO_NULL);

    setReturnType(_node->getId());
  }

  void TypeFormerMethod::removeReturnType() {
      if (m_hasReturnType) {
        if (factory->getExistsReverseEdges())
          factory->reverseEdges->removeEdge(m_hasReturnType, m_id, edkTypeFormerMethod_HasReturnType);
      }
      m_hasReturnType = 0;
  }

  void TypeFormerMethod::accept(Visitor &visitor) const {
    visitor.visit(*this);
  }

  void TypeFormerMethod::acceptEnd(Visitor &visitor) const {
    visitor.visitEnd(*this);
  }

  double TypeFormerMethod::getSimilarity(const base::Base& base){
    if(base.getNodeKind() == getNodeKind()) {
      return 1.0;
    } else {
      return 0.0;
    }
  }

  void TypeFormerMethod::swapStringTable(RefDistributorStrTable& newStrTable, std::map<Key,Key>& oldAndNewStrKeyMap ){
    std::map<Key,Key>::iterator foundKeyId;

  }

  NodeHashType TypeFormerMethod::getHash(std::set<NodeId>& travNodes) const {
    if (hashOk) return nodeHashCache;
    common::WriteMsg::write(CMSG_GET_THE_NODE_HASH_OF_NODE_BEGIN,this->getId()); 
    if (travNodes.count(getId())>0) {
      common::WriteMsg::write(CMSG_GET_THE_NODE_HASH_OF_NODE_SKIP);
      return 0;
    }
    travNodes.insert(getId());
    Crc_type resultHash;
    resultHash.process_bytes( "type::TypeFormerMethod", strlen("type::TypeFormerMethod"));
    common::WriteMsg::write(CMSG_GET_THE_NODE_HASH_OF_NODE_END,resultHash.checksum()); 
    nodeHashCache = resultHash.checksum();
    hashOk = true;
    return nodeHashCache;
  }

  void TypeFormerMethod::save(io::BinaryIO &binIo,bool withVirtualBase  /*= true*/) const {
    TypeFormer::save(binIo,false);

    binIo.writeUInt4(m_hasReturnType);


    for (ListIteratorAssocParameterKind<type::Type>::Container::const_iterator ait = hasParameterTypeContainer.begin(); ait != hasParameterTypeContainer.end(); ++ait) {
      binIo.writeUInt4(ait->node);
      binIo.writeUByte1(ait->assocClass);
    }
    binIo.writeUInt4(0); // This is the end sign
  }

  void TypeFormerMethod::load(io::BinaryIO &binIo, bool withVirtualBase /*= true*/) {
    TypeFormer::load(binIo,false);

    m_hasReturnType =  binIo.readUInt4();

    NodeId _id;

    _id = binIo.readUInt4();
    while (_id) {
      ParameterKind _ac = static_cast<ParameterKind>(binIo.readUByte1());
      hasParameterTypeContainer.push_back(AssocEdge<NodeId,ParameterKind>(_id, _ac));
      _id = binIo.readUInt4();
    }
  }


}


}}}
