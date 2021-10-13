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
  IntersectionType::IntersectionType(NodeId _id, Factory *_factory) :
    Type(_id, _factory),
    boundsContainer()
  {
  }

  IntersectionType::~IntersectionType() {
  }

  void IntersectionType::clone(const IntersectionType& other, bool tryOnVirtualParent) {
    type::Type::clone(other, false);

    boundsContainer = other.boundsContainer;
  }

  void IntersectionType::prepareDelete(bool tryOnVirtualParent){
    while (!boundsContainer.empty()) {
      const NodeId id = *boundsContainer.begin();
      if (factory->getExistsReverseEdges())
        factory->reverseEdges->removeEdge(id, this->getId(), edkIntersectionType_Bounds);
      boundsContainer.pop_front();
    }
    type::Type::prepareDelete(false);
  }

  NodeKind IntersectionType::getNodeKind() const {
    return ndkIntersectionType;
  }

  ListIterator<type::Type> IntersectionType::getBoundsListIteratorBegin() const {
    return ListIterator<type::Type>(&boundsContainer, factory, true);
  }

  ListIterator<type::Type> IntersectionType::getBoundsListIteratorEnd() const {
    return ListIterator<type::Type>(&boundsContainer, factory, false);
  }

  bool IntersectionType::getBoundsIsEmpty() const {
    return getBoundsListIteratorBegin() == getBoundsListIteratorEnd();
  }

  unsigned int IntersectionType::getBoundsSize() const {
    unsigned int size = 0;
    ListIterator<type::Type> endIt = getBoundsListIteratorEnd();
    for (ListIterator<type::Type> it = getBoundsListIteratorBegin(); it != endIt; ++it) {
      ++size;
    }
    return size;
  }

  bool IntersectionType::setEdge(EdgeKind edgeKind, NodeId edgeEnd, bool tryOnVirtualParent) {
    switch (edgeKind) {
      case edkIntersectionType_Bounds:
        addBounds(edgeEnd);
        return true;
      default:
        break;
    }
    if (type::Type::setEdge(edgeKind, edgeEnd, false)) {
      return true;
    }
    return false;
  }

  bool IntersectionType::removeEdge(EdgeKind edgeKind, NodeId edgeEnd, bool tryOnVirtualParent) {
    switch (edgeKind) {
      case edkIntersectionType_Bounds:
        removeBounds(edgeEnd);
        return true;
      default:
        break;
    }
    if (type::Type::removeEdge(edgeKind, edgeEnd, false)) {
      return true;
    }
    return false;
  }

  void IntersectionType::addBounds(const type::Type *_node) {
    if (_node == NULL)
      throw JavaException(COLUMBUS_LOCATION, CMSG_EX_THE_NODE_IS_NULL);

    if (&(_node->getFactory()) != this->factory)
      throw JavaException(COLUMBUS_LOCATION, CMSG_EX_THE_FACTORY_OF_NODES_DOES_NOT_MATCH);

    if (!(Common::getIsType(*_node)))
      throw JavaException(COLUMBUS_LOCATION, CMSG_EX_INVALID_NODE_KIND);

    boundsContainer.push_back(_node->getId());
    if (factory->reverseEdges)
      factory->reverseEdges->insertEdge(_node, this, edkIntersectionType_Bounds);
  }

  void IntersectionType::addBounds(NodeId _id) {
    const type::Type *node = dynamic_cast<type::Type*>(factory->getPointer(_id));
    if (node == NULL)
      throw JavaException(COLUMBUS_LOCATION, CMSG_EX_INVALID_NODE_KIND);
    addBounds( node );
  }

  void IntersectionType::removeBounds(NodeId id) {
    if (!factory->getExist(id))
      throw JavaException(COLUMBUS_LOCATION, CMSG_EX_THE_END_POINT_OF_THE_EDGE_DOES_NOT_EXIST);

    ListIterator<type::Type>::Container::iterator it = find(boundsContainer.begin(), boundsContainer.end(), id);

    if (it == boundsContainer.end())
      throw JavaException(COLUMBUS_LOCATION, CMSG_EX_THE_END_POINT_OF_THE_EDGE_DOES_NOT_EXIST);

    boundsContainer.erase(it);

    if (factory->getExistsReverseEdges())
      factory->reverseEdges->removeEdge(id, this->getId(), edkIntersectionType_Bounds);
  }

  void IntersectionType::removeBounds(type::Type *_node) {
    if (_node == NULL)
      throw JavaException(COLUMBUS_LOCATION, CMSG_EX_THE_EDGE_IS_NULL);

    removeBounds(_node->getId());
  }

  void IntersectionType::accept(Visitor &visitor) const {
    visitor.visit(*this);
  }

  void IntersectionType::acceptEnd(Visitor &visitor) const {
    visitor.visitEnd(*this);
  }

  double IntersectionType::getSimilarity(const base::Base& base){
    if(base.getNodeKind() == getNodeKind()) {
      return 1.0;
    } else {
      return 0.0;
    }
  }

  void IntersectionType::swapStringTable(RefDistributorStrTable& newStrTable, std::map<Key,Key>& oldAndNewStrKeyMap ){
    std::map<Key,Key>::iterator foundKeyId;

  }

  NodeHashType IntersectionType::getHash(std::set<NodeId>& travNodes) const {
    if (hashOk) return nodeHashCache;
    common::WriteMsg::write(CMSG_GET_THE_NODE_HASH_OF_NODE_BEGIN,this->getId()); 
    if (travNodes.count(getId())>0) {
      common::WriteMsg::write(CMSG_GET_THE_NODE_HASH_OF_NODE_SKIP);
      return 0;
    }
    travNodes.insert(getId());
    Crc_type resultHash;
    resultHash.process_bytes( "type::IntersectionType", strlen("type::IntersectionType"));
    common::WriteMsg::write(CMSG_GET_THE_NODE_HASH_OF_NODE_END,resultHash.checksum()); 
    nodeHashCache = resultHash.checksum();
    hashOk = true;
    return nodeHashCache;
  }

  void IntersectionType::sort(bool withVirtualBase /* = true */) {
    Type::sort(false);
  }

  void IntersectionType::save(io::BinaryIO &binIo,bool withVirtualBase  /*= true*/) const {
    Type::save(binIo,false);


    for (ListIterator<type::Type>::Container::const_iterator it = boundsContainer.begin(); it != boundsContainer.end(); ++it) {
      binIo.writeUInt4(*it);
    }
    binIo.writeUInt4(0); // This is the end sign
  }

  void IntersectionType::load(io::BinaryIO &binIo, bool withVirtualBase /*= true*/) {
    Type::load(binIo,false);

    NodeId _id;

    _id = binIo.readUInt4();
    while (_id) {
      boundsContainer.push_back(_id);
      _id = binIo.readUInt4();
    }
  }


}


}}}
