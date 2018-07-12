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

#include "python/inc/python.h"
#include "python/inc/Common.h"
#include "common/inc/WriteMessage.h"

#include "python/inc/messages.h"
#include <algorithm>
#include <string.h>
#include "common/inc/math/common.h"


namespace columbus { namespace python { namespace asg {

typedef boost::crc_32_type  Crc_type;

namespace expression { 
  ExtSlice::ExtSlice(NodeId _id, Factory *_factory) :
    Slicing(_id, _factory),
    hasItemContainer()
  {
  }

  ExtSlice::~ExtSlice() {
  }

  void ExtSlice::prepareDelete(bool tryOnVirtualParent){
    while (!hasItemContainer.empty()) {
      const NodeId id = *hasItemContainer.begin();
      removeParentEdge(id);
      if (factory->getExistsReverseEdges())
        factory->reverseEdges->removeEdge(id, this->getId(), edkExtSlice_HasItem);
      hasItemContainer.pop_front();
    }
    expression::Slicing::prepareDelete(false);
  }

  NodeKind ExtSlice::getNodeKind() const {
    return ndkExtSlice;
  }

  ListIterator<expression::Slicing> ExtSlice::getItemListIteratorBegin() const {
    return ListIterator<expression::Slicing>(&hasItemContainer, factory, true);
  }

  ListIterator<expression::Slicing> ExtSlice::getItemListIteratorEnd() const {
    return ListIterator<expression::Slicing>(&hasItemContainer, factory, false);
  }

  bool ExtSlice::getItemIsEmpty() const {
    return getItemListIteratorBegin() == getItemListIteratorEnd();
  }

  unsigned int ExtSlice::getItemSize() const {
    unsigned int size = 0;
    ListIterator<expression::Slicing> endIt = getItemListIteratorEnd();
    for (ListIterator<expression::Slicing> it = getItemListIteratorBegin(); it != endIt; ++it) {
      ++size;
    }
    return size;
  }

  bool ExtSlice::setEdge(EdgeKind edgeKind, NodeId edgeEnd, bool tryOnVirtualParent) {
    switch (edgeKind) {
      case edkExtSlice_HasItem:
        addItem(edgeEnd);
        return true;
      default:
        break;
    }
    if (expression::Slicing::setEdge(edgeKind, edgeEnd, false)) {
      return true;
    }
    return false;
  }

  bool ExtSlice::removeEdge(EdgeKind edgeKind, NodeId edgeEnd, bool tryOnVirtualParent) {
    switch (edgeKind) {
      case edkExtSlice_HasItem:
        removeItem(edgeEnd);
        return true;
      default:
        break;
    }
    if (expression::Slicing::removeEdge(edgeKind, edgeEnd, false)) {
      return true;
    }
    return false;
  }

  void ExtSlice::addItem(const expression::Slicing *_node) {
    if (_node == NULL)
      throw PythonException(COLUMBUS_LOCATION, CMSG_EX_THE_NODE_IS_NULL);

    if (&(_node->getFactory()) != this->factory)
      throw PythonException(COLUMBUS_LOCATION, CMSG_EX_THE_FACTORY_OF_NODES_DOES_NOT_MATCH);

    if (!(Common::getIsSlicing(*_node)))
      throw PythonException(COLUMBUS_LOCATION, CMSG_EX_INVALID_NODE_KIND);

    hasItemContainer.push_back(_node->getId());
    setParentEdge(_node,edkExtSlice_HasItem);

    if (factory->reverseEdges)
      factory->reverseEdges->insertEdge(_node, this, edkExtSlice_HasItem);
  }

  void ExtSlice::addItem(NodeId _id) {
    const expression::Slicing *node = dynamic_cast<expression::Slicing*>(factory->getPointer(_id));
    if (node == NULL)
      throw PythonException(COLUMBUS_LOCATION, CMSG_EX_INVALID_NODE_KIND);
    addItem( node );
  }

  void ExtSlice::removeItem(NodeId id) {
    if (!factory->getExist(id))
      throw PythonException(COLUMBUS_LOCATION, CMSG_EX_THE_END_POINT_OF_THE_EDGE_DOES_NOT_EXIST);

    ListIterator<expression::Slicing>::Container::iterator it = find(hasItemContainer.begin(), hasItemContainer.end(), id);

    if (it == hasItemContainer.end())
      throw PythonException(COLUMBUS_LOCATION, CMSG_EX_THE_END_POINT_OF_THE_EDGE_DOES_NOT_EXIST);

    hasItemContainer.erase(it);

    removeParentEdge(id);

    if (factory->getExistsReverseEdges())
      factory->reverseEdges->removeEdge(id, this->getId(), edkExtSlice_HasItem);
  }

  void ExtSlice::removeItem(expression::Slicing *_node) {
    if (_node == NULL)
      throw PythonException(COLUMBUS_LOCATION, CMSG_EX_THE_EDGE_IS_NULL);

    removeItem(_node->getId());
  }

  void ExtSlice::accept(Visitor &visitor) const {
    visitor.visit(*this);
  }

  void ExtSlice::acceptEnd(Visitor &visitor) const {
    visitor.visitEnd(*this);
  }

  double ExtSlice::getSimilarity(const base::Base& base){
    if(base.getNodeKind() == getNodeKind()) {
      return 1.0;
    } else {
      return 0.0;
    }
  }

  void ExtSlice::swapStringTable(RefDistributorStrTable& newStrTable, std::map<Key,Key>& oldAndNewStrKeyMap ){
    std::map<Key,Key>::iterator foundKeyId;

  }

  NodeHashType ExtSlice::getHash(std::set<NodeId>& travNodes) const {
    if (hashOk) return nodeHashCache;
    common::WriteMsg::write(CMSG_GET_THE_NODE_HASH_OF_NODE_BEGIN,this->getId()); 
    if (travNodes.count(getId())>0) {
      common::WriteMsg::write(CMSG_GET_THE_NODE_HASH_OF_NODE_SKIP);
      return 0;
    }
    travNodes.insert(getId());
    Crc_type resultHash;
    resultHash.process_bytes( "expression::ExtSlice", strlen("expression::ExtSlice"));
    common::WriteMsg::write(CMSG_GET_THE_NODE_HASH_OF_NODE_END,resultHash.checksum()); 
    nodeHashCache = resultHash.checksum();
    hashOk = true;
    return nodeHashCache;
  }

  void ExtSlice::save(io::BinaryIO &binIo,bool withVirtualBase  /*= true*/) const {
    Slicing::save(binIo,false);


    for (ListIterator<expression::Slicing>::Container::const_iterator it = hasItemContainer.begin(); it != hasItemContainer.end(); ++it) {
      binIo.writeUInt4(*it);
    }
    binIo.writeUInt4(0); // This is the end sign
  }

  void ExtSlice::load(io::BinaryIO &binIo, bool withVirtualBase /*= true*/) {
    Slicing::load(binIo,false);

    NodeId _id;

    _id = binIo.readUInt4();
    while (_id) {
      hasItemContainer.push_back(_id);
      setParentEdge(factory->getPointer(_id),edkExtSlice_HasItem);
      _id = binIo.readUInt4();
    }
  }


}


}}}
