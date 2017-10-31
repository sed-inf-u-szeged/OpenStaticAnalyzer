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

#include "genealogy/inc/genealogy.h"
#include "genealogy/inc/Common.h"
#include "common/inc/WriteMessage.h"

#include "genealogy/inc/messages.h"
#include <algorithm>
#include <string.h>
#include "common/inc/math/common.h"


namespace columbus { namespace genealogy { 

typedef boost::crc_32_type  Crc_type;

  Trackable::Trackable(NodeId _id, Factory *_factory) :
    Base(_id, _factory),
    prevContainer(),
    nextContainer()
  {
  }

  Trackable::~Trackable() {
  }

  void Trackable::prepareDelete(bool tryOnVirtualParent){
    while (!prevContainer.empty()) {
      const NodeId id = *prevContainer.begin();
      if (factory->getExistsReverseEdges())
        factory->reverseEdges->removeEdge(id, this->getId(), edkTrackable_Prev);
      prevContainer.pop_front();
    }
    while (!nextContainer.empty()) {
      const NodeId id = *nextContainer.begin();
      if (factory->getExistsReverseEdges())
        factory->reverseEdges->removeEdge(id, this->getId(), edkTrackable_Next);
      nextContainer.pop_front();
    }
    Base::prepareDelete(false);
  }

  NodeKind Trackable::getNodeKind() const {
    return ndkTrackable;
  }

  ListIterator<Trackable> Trackable::getPrevListIteratorBegin() const {
    return ListIterator<Trackable>(&prevContainer, factory, true);
  }

  ListIterator<Trackable> Trackable::getPrevListIteratorEnd() const {
    return ListIterator<Trackable>(&prevContainer, factory, false);
  }

  bool Trackable::getPrevIsEmpty() const {
    return prevContainer.empty();
  }

  unsigned int Trackable::getPrevSize() const {
    return (unsigned int)prevContainer.size();
  }

  ListIterator<Trackable> Trackable::getNextListIteratorBegin() const {
    return ListIterator<Trackable>(&nextContainer, factory, true);
  }

  ListIterator<Trackable> Trackable::getNextListIteratorEnd() const {
    return ListIterator<Trackable>(&nextContainer, factory, false);
  }

  bool Trackable::getNextIsEmpty() const {
    return nextContainer.empty();
  }

  unsigned int Trackable::getNextSize() const {
    return (unsigned int)nextContainer.size();
  }

  bool Trackable::setEdge(EdgeKind edgeKind, NodeId edgeEnd, bool tryOnVirtualParent) {
    switch (edgeKind) {
      case edkTrackable_Prev:
        addPrev(edgeEnd);
        return true;
      case edkTrackable_Next:
        addNext(edgeEnd);
        return true;
      default:
        break;
    }
    if (Base::setEdge(edgeKind, edgeEnd, false)) {
      return true;
    }
    return false;
  }

  bool Trackable::removeEdge(EdgeKind edgeKind, NodeId edgeEnd, bool tryOnVirtualParent) {
    switch (edgeKind) {
      case edkTrackable_Prev:
        removePrev(edgeEnd);
        return true;
      case edkTrackable_Next:
        removeNext(edgeEnd);
        return true;
      default:
        break;
    }
    if (Base::removeEdge(edgeKind, edgeEnd, false)) {
      return true;
    }
    return false;
  }

  void Trackable::addPrev(const Trackable *_node) {
    if (_node == NULL)
      throw GenealogyException(COLUMBUS_LOCATION, CMSG_EX_THE_NODE_IS_NULL);

    if (&(_node->getFactory()) != this->factory)
      throw GenealogyException(COLUMBUS_LOCATION, CMSG_EX_THE_FACTORY_OF_NODES_DOES_NOT_MATCH);

    if (!(Common::getIsTrackable(*_node)))
      throw GenealogyException(COLUMBUS_LOCATION, CMSG_EX_INVALID_NODE_KIND);

    prevContainer.push_back(_node->getId());
    if (factory->reverseEdges)
      factory->reverseEdges->insertEdge(_node, this, edkTrackable_Prev);
  }

  void Trackable::addPrev(NodeId _id) {
    const Trackable *node = dynamic_cast<Trackable*>(factory->getPointer(_id));
    if (node == NULL)
      throw GenealogyException(COLUMBUS_LOCATION, CMSG_EX_INVALID_NODE_KIND);
    addPrev( node );
  }

  void Trackable::removePrev(NodeId id) {
    if (!factory->getExist(id))
      throw GenealogyException(COLUMBUS_LOCATION, CMSG_EX_THE_END_POINT_OF_THE_EDGE_DOES_NOT_EXIST);

    ListIterator<Trackable>::Container::iterator it = find(prevContainer.begin(), prevContainer.end(), id);

    if (it == prevContainer.end())
      throw GenealogyException(COLUMBUS_LOCATION, CMSG_EX_THE_END_POINT_OF_THE_EDGE_DOES_NOT_EXIST);

    prevContainer.erase(it);

    if (factory->getExistsReverseEdges())
      factory->reverseEdges->removeEdge(id, this->getId(), edkTrackable_Prev);
  }

  void Trackable::removePrev(Trackable *_node) {
    if (_node == NULL)
      throw GenealogyException(COLUMBUS_LOCATION, CMSG_EX_THE_EDGE_IS_NULL);

    removePrev(_node->getId());
  }

  void Trackable::addNext(const Trackable *_node) {
    if (_node == NULL)
      throw GenealogyException(COLUMBUS_LOCATION, CMSG_EX_THE_NODE_IS_NULL);

    if (&(_node->getFactory()) != this->factory)
      throw GenealogyException(COLUMBUS_LOCATION, CMSG_EX_THE_FACTORY_OF_NODES_DOES_NOT_MATCH);

    if (!(Common::getIsTrackable(*_node)))
      throw GenealogyException(COLUMBUS_LOCATION, CMSG_EX_INVALID_NODE_KIND);

    nextContainer.push_back(_node->getId());
    if (factory->reverseEdges)
      factory->reverseEdges->insertEdge(_node, this, edkTrackable_Next);
  }

  void Trackable::addNext(NodeId _id) {
    const Trackable *node = dynamic_cast<Trackable*>(factory->getPointer(_id));
    if (node == NULL)
      throw GenealogyException(COLUMBUS_LOCATION, CMSG_EX_INVALID_NODE_KIND);
    addNext( node );
  }

  void Trackable::removeNext(NodeId id) {
    if (!factory->getExist(id))
      throw GenealogyException(COLUMBUS_LOCATION, CMSG_EX_THE_END_POINT_OF_THE_EDGE_DOES_NOT_EXIST);

    ListIterator<Trackable>::Container::iterator it = find(nextContainer.begin(), nextContainer.end(), id);

    if (it == nextContainer.end())
      throw GenealogyException(COLUMBUS_LOCATION, CMSG_EX_THE_END_POINT_OF_THE_EDGE_DOES_NOT_EXIST);

    nextContainer.erase(it);

    if (factory->getExistsReverseEdges())
      factory->reverseEdges->removeEdge(id, this->getId(), edkTrackable_Next);
  }

  void Trackable::removeNext(Trackable *_node) {
    if (_node == NULL)
      throw GenealogyException(COLUMBUS_LOCATION, CMSG_EX_THE_EDGE_IS_NULL);

    removeNext(_node->getId());
  }

  void Trackable::accept(Visitor &visitor) const {
    visitor.visit(*this);
  }

  void Trackable::acceptEnd(Visitor &visitor) const {
    visitor.visitEnd(*this);
  }

  double Trackable::getSimilarity(const Base& base){
    if(base.getNodeKind() == getNodeKind()) {
      return 1.0;
    } else {
      return 0.0;
    }
  }

  void Trackable::swapStringTable(RefDistributorStrTable& newStrTable, std::map<Key,Key>& oldAndNewStrKeyMap ){
    std::map<Key,Key>::iterator foundKeyId;

  }

  NodeHashType Trackable::getHash(std::set<NodeId>& travNodes) const {
    if (hashOk) return nodeHashCache;
    common::WriteMsg::write(CMSG_GET_THE_NODE_HASH_OF_NODE_BEGIN,this->getId()); 
    if (travNodes.count(getId())>0) {
      common::WriteMsg::write(CMSG_GET_THE_NODE_HASH_OF_NODE_SKIP);
      return 0;
    }
    travNodes.insert(getId());
    Crc_type resultHash;
    resultHash.process_bytes( "Trackable", strlen("Trackable"));
    common::WriteMsg::write(CMSG_GET_THE_NODE_HASH_OF_NODE_END,resultHash.checksum()); 
    nodeHashCache = resultHash.checksum();
    hashOk = true;
    return nodeHashCache;
  }

  void Trackable::save(io::BinaryIO &binIo,bool withVirtualBase  /*= true*/) const {
    Base::save(binIo,false);


    for (ListIterator<Trackable>::Container::const_iterator it = prevContainer.begin(); it != prevContainer.end(); ++it) {
      binIo.writeUInt4(*it);
    }
    binIo.writeUInt4(0); // This is the end sign

    for (ListIterator<Trackable>::Container::const_iterator it = nextContainer.begin(); it != nextContainer.end(); ++it) {
      binIo.writeUInt4(*it);
    }
    binIo.writeUInt4(0); // This is the end sign
  }

  void Trackable::load(io::BinaryIO &binIo, bool withVirtualBase /*= true*/) {
    Base::load(binIo,false);

    NodeId _id;

    _id = binIo.readUInt4();
    while (_id) {
      prevContainer.push_back(_id);
      _id = binIo.readUInt4();
    }

    _id = binIo.readUInt4();
    while (_id) {
      nextContainer.push_back(_id);
      _id = binIo.readUInt4();
    }
  }



}}
