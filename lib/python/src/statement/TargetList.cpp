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

#include "python/inc/python.h"
#include "python/inc/Common.h"
#include "common/inc/WriteMessage.h"

#include "python/inc/messages.h"
#include <algorithm>
#include <string.h>
#include "common/inc/math/common.h"


namespace columbus { namespace python { namespace asg {

typedef boost::crc_32_type  Crc_type;

namespace statement { 
  TargetList::TargetList(NodeId _id, Factory *_factory) :
    Positioned(_id, _factory),
    hasTargetContainer()
  {
  }

  TargetList::~TargetList() {
  }

  void TargetList::prepareDelete(bool tryOnVirtualParent){
    while (!hasTargetContainer.empty()) {
      const NodeId id = *hasTargetContainer.begin();
      removeParentEdge(id);
      if (factory->getExistsReverseEdges())
        factory->reverseEdges->removeEdge(id, this->getId(), edkTargetList_HasTarget);
      hasTargetContainer.pop_front();
    }
    base::Positioned::prepareDelete(false);
  }

  NodeKind TargetList::getNodeKind() const {
    return ndkTargetList;
  }

  ListIterator<expression::Expression> TargetList::getTargetListIteratorBegin() const {
    return ListIterator<expression::Expression>(&hasTargetContainer, factory, true);
  }

  ListIterator<expression::Expression> TargetList::getTargetListIteratorEnd() const {
    return ListIterator<expression::Expression>(&hasTargetContainer, factory, false);
  }

  bool TargetList::getTargetIsEmpty() const {
    return getTargetListIteratorBegin() == getTargetListIteratorEnd();
  }

  unsigned int TargetList::getTargetSize() const {
    unsigned int size = 0;
    ListIterator<expression::Expression> endIt = getTargetListIteratorEnd();
    for (ListIterator<expression::Expression> it = getTargetListIteratorBegin(); it != endIt; ++it) {
      ++size;
    }
    return size;
  }

  bool TargetList::setEdge(EdgeKind edgeKind, NodeId edgeEnd, bool tryOnVirtualParent) {
    switch (edgeKind) {
      case edkTargetList_HasTarget:
        addTarget(edgeEnd);
        return true;
      default:
        break;
    }
    if (base::Positioned::setEdge(edgeKind, edgeEnd, false)) {
      return true;
    }
    return false;
  }

  bool TargetList::removeEdge(EdgeKind edgeKind, NodeId edgeEnd, bool tryOnVirtualParent) {
    switch (edgeKind) {
      case edkTargetList_HasTarget:
        removeTarget(edgeEnd);
        return true;
      default:
        break;
    }
    if (base::Positioned::removeEdge(edgeKind, edgeEnd, false)) {
      return true;
    }
    return false;
  }

  void TargetList::addTarget(const expression::Expression *_node) {
    if (_node == NULL)
      throw PythonException(COLUMBUS_LOCATION, CMSG_EX_THE_NODE_IS_NULL);

    if (&(_node->getFactory()) != this->factory)
      throw PythonException(COLUMBUS_LOCATION, CMSG_EX_THE_FACTORY_OF_NODES_DOES_NOT_MATCH);

    if (!((_node->getNodeKind() == ndkList)  || (_node->getNodeKind() == ndkSubscription)  || (_node->getNodeKind() == ndkAttributeRef)  || Common::getIsSlicing(*_node) || (_node->getNodeKind() == ndkIdentifier) ))
      throw PythonException(COLUMBUS_LOCATION, CMSG_EX_INVALID_NODE_KIND);

    hasTargetContainer.push_back(_node->getId());
    setParentEdge(_node,edkTargetList_HasTarget);

    if (factory->reverseEdges)
      factory->reverseEdges->insertEdge(_node, this, edkTargetList_HasTarget);
  }

  void TargetList::addTarget(NodeId _id) {
    const expression::Expression *node = dynamic_cast<expression::Expression*>(factory->getPointer(_id));
    if (node == NULL)
      throw PythonException(COLUMBUS_LOCATION, CMSG_EX_INVALID_NODE_KIND);
    addTarget( node );
  }

  void TargetList::removeTarget(NodeId id) {
    if (!factory->getExist(id))
      throw PythonException(COLUMBUS_LOCATION, CMSG_EX_THE_END_POINT_OF_THE_EDGE_DOES_NOT_EXIST);

    ListIterator<expression::Expression>::Container::iterator it = find(hasTargetContainer.begin(), hasTargetContainer.end(), id);

    if (it == hasTargetContainer.end())
      throw PythonException(COLUMBUS_LOCATION, CMSG_EX_THE_END_POINT_OF_THE_EDGE_DOES_NOT_EXIST);

    hasTargetContainer.erase(it);

    removeParentEdge(id);

    if (factory->getExistsReverseEdges())
      factory->reverseEdges->removeEdge(id, this->getId(), edkTargetList_HasTarget);
  }

  void TargetList::removeTarget(expression::Expression *_node) {
    if (_node == NULL)
      throw PythonException(COLUMBUS_LOCATION, CMSG_EX_THE_EDGE_IS_NULL);

    removeTarget(_node->getId());
  }

  void TargetList::accept(Visitor &visitor) const {
    visitor.visit(*this);
  }

  void TargetList::acceptEnd(Visitor &visitor) const {
    visitor.visitEnd(*this);
  }

  double TargetList::getSimilarity(const base::Base& base){
    if(base.getNodeKind() == getNodeKind()) {
      return 1.0;
    } else {
      return 0.0;
    }
  }

  void TargetList::swapStringTable(RefDistributorStrTable& newStrTable, std::map<Key,Key>& oldAndNewStrKeyMap ){
    std::map<Key,Key>::iterator foundKeyId;

  }

  NodeHashType TargetList::getHash(std::set<NodeId>& travNodes) const {
    if (hashOk) return nodeHashCache;
    common::WriteMsg::write(CMSG_GET_THE_NODE_HASH_OF_NODE_BEGIN,this->getId()); 
    if (travNodes.count(getId())>0) {
      common::WriteMsg::write(CMSG_GET_THE_NODE_HASH_OF_NODE_SKIP);
      return 0;
    }
    travNodes.insert(getId());
    Crc_type resultHash;
    resultHash.process_bytes( "statement::TargetList", strlen("statement::TargetList"));
    common::WriteMsg::write(CMSG_GET_THE_NODE_HASH_OF_NODE_END,resultHash.checksum()); 
    nodeHashCache = resultHash.checksum();
    hashOk = true;
    return nodeHashCache;
  }

  void TargetList::save(io::BinaryIO &binIo,bool withVirtualBase  /*= true*/) const {
    Positioned::save(binIo,false);


    for (ListIterator<expression::Expression>::Container::const_iterator it = hasTargetContainer.begin(); it != hasTargetContainer.end(); ++it) {
      binIo.writeUInt4(*it);
    }
    binIo.writeUInt4(0); // This is the end sign
  }

  void TargetList::load(io::BinaryIO &binIo, bool withVirtualBase /*= true*/) {
    Positioned::load(binIo,false);

    NodeId _id;

    _id = binIo.readUInt4();
    while (_id) {
      hasTargetContainer.push_back(_id);
      setParentEdge(factory->getPointer(_id),edkTargetList_HasTarget);
      _id = binIo.readUInt4();
    }
  }


}


}}}
