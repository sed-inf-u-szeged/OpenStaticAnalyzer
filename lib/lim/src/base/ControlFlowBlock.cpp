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

namespace base { 
  ControlFlowBlock::ControlFlowBlock(NodeId _id, Factory *_factory) :
    Base(_id, _factory),
    callsContainer(),
    predContainer()
  {
  }

  ControlFlowBlock::~ControlFlowBlock() {
  }

  void ControlFlowBlock::clone(const ControlFlowBlock& other, bool tryOnVirtualParent) {
    base::Base::clone(other, false);

    callsContainer = other.callsContainer;
    predContainer = other.predContainer;
  }

  void ControlFlowBlock::prepareDelete(bool tryOnVirtualParent){
    while (!callsContainer.empty()) {
      const NodeId id = *callsContainer.begin();
      if (factory->getExistsReverseEdges())
        factory->reverseEdges->removeEdge(id, this->getId(), edkControlFlowBlock_Calls);
      callsContainer.pop_front();
    }
    while (!predContainer.empty()) {
      const NodeId id = *predContainer.begin();
      if (factory->getExistsReverseEdges())
        factory->reverseEdges->removeEdge(id, this->getId(), edkControlFlowBlock_Pred);
      predContainer.pop_front();
    }
    base::Base::prepareDelete(false);
  }

  NodeKind ControlFlowBlock::getNodeKind() const {
    return ndkControlFlowBlock;
  }

  ListIterator<logical::Method> ControlFlowBlock::getCallsListIteratorBegin() const {
    return ListIterator<logical::Method>(&callsContainer, factory, true);
  }

  ListIterator<logical::Method> ControlFlowBlock::getCallsListIteratorEnd() const {
    return ListIterator<logical::Method>(&callsContainer, factory, false);
  }

  bool ControlFlowBlock::getCallsIsEmpty() const {
    return getCallsListIteratorBegin() == getCallsListIteratorEnd();
  }

  unsigned int ControlFlowBlock::getCallsSize() const {
    unsigned int size = 0;
    ListIterator<logical::Method> endIt = getCallsListIteratorEnd();
    for (ListIterator<logical::Method> it = getCallsListIteratorBegin(); it != endIt; ++it) {
      ++size;
    }
    return size;
  }

  ListIterator<base::ControlFlowBlock> ControlFlowBlock::getPredListIteratorBegin() const {
    return ListIterator<base::ControlFlowBlock>(&predContainer, factory, true);
  }

  ListIterator<base::ControlFlowBlock> ControlFlowBlock::getPredListIteratorEnd() const {
    return ListIterator<base::ControlFlowBlock>(&predContainer, factory, false);
  }

  bool ControlFlowBlock::getPredIsEmpty() const {
    return getPredListIteratorBegin() == getPredListIteratorEnd();
  }

  unsigned int ControlFlowBlock::getPredSize() const {
    unsigned int size = 0;
    ListIterator<base::ControlFlowBlock> endIt = getPredListIteratorEnd();
    for (ListIterator<base::ControlFlowBlock> it = getPredListIteratorBegin(); it != endIt; ++it) {
      ++size;
    }
    return size;
  }

  bool ControlFlowBlock::setEdge(EdgeKind edgeKind, NodeId edgeEnd, void* acValue, bool tryOnVirtualParent) {
    switch (edgeKind) {
      case edkControlFlowBlock_Calls:
        addCalls(edgeEnd);
        return true;
      case edkControlFlowBlock_Pred:
        addPred(edgeEnd);
        return true;
      default:
        break;
    }
    if (base::Base::setEdge(edgeKind, edgeEnd, acValue, false)) {
      return true;
    }
    return false;
  }

  bool ControlFlowBlock::removeEdge(EdgeKind edgeKind, NodeId edgeEnd, bool tryOnVirtualParent) {
    switch (edgeKind) {
      case edkControlFlowBlock_Calls:
        removeCalls(edgeEnd);
        return true;
      case edkControlFlowBlock_Pred:
        removePred(edgeEnd);
        return true;
      default:
        break;
    }
    if (base::Base::removeEdge(edgeKind, edgeEnd, false)) {
      return true;
    }
    return false;
  }

  void ControlFlowBlock::addCalls(const logical::Method *_node) {
    if (_node == NULL)
      throw LimException(COLUMBUS_LOCATION, CMSG_EX_THE_NODE_IS_NULL);

    if (&(_node->getFactory()) != this->factory)
      throw LimException(COLUMBUS_LOCATION, CMSG_EX_THE_FACTORY_OF_NODES_DOES_NOT_MATCH);

    if (!(Common::getIsMethod(*_node)))
      throw LimException(COLUMBUS_LOCATION, CMSG_EX_INVALID_NODE_KIND);

    callsContainer.push_back(_node->getId());
    if (factory->reverseEdges)
      factory->reverseEdges->insertEdge(_node, this, edkControlFlowBlock_Calls);
  }

  void ControlFlowBlock::addCalls(NodeId _id) {
    const logical::Method *node = dynamic_cast<logical::Method*>(factory->getPointer(_id));
    if (node == NULL)
      throw LimException(COLUMBUS_LOCATION, CMSG_EX_INVALID_NODE_KIND);
    addCalls( node );
  }

  void ControlFlowBlock::removeCalls(NodeId id) {
    if (!factory->getExist(id))
      throw LimException(COLUMBUS_LOCATION, CMSG_EX_THE_END_POINT_OF_THE_EDGE_DOES_NOT_EXIST);

    ListIterator<logical::Method>::Container::iterator it = find(callsContainer.begin(), callsContainer.end(), id);

    if (it == callsContainer.end())
      throw LimException(COLUMBUS_LOCATION, CMSG_EX_THE_END_POINT_OF_THE_EDGE_DOES_NOT_EXIST);

    callsContainer.erase(it);

    if (factory->getExistsReverseEdges())
      factory->reverseEdges->removeEdge(id, this->getId(), edkControlFlowBlock_Calls);
  }

  void ControlFlowBlock::removeCalls(logical::Method *_node) {
    if (_node == NULL)
      throw LimException(COLUMBUS_LOCATION, CMSG_EX_THE_EDGE_IS_NULL);

    removeCalls(_node->getId());
  }

  void ControlFlowBlock::addPred(const base::ControlFlowBlock *_node) {
    if (_node == NULL)
      throw LimException(COLUMBUS_LOCATION, CMSG_EX_THE_NODE_IS_NULL);

    if (&(_node->getFactory()) != this->factory)
      throw LimException(COLUMBUS_LOCATION, CMSG_EX_THE_FACTORY_OF_NODES_DOES_NOT_MATCH);

    if (!((_node->getNodeKind() == ndkControlFlowBlock) ))
      throw LimException(COLUMBUS_LOCATION, CMSG_EX_INVALID_NODE_KIND);

    predContainer.push_back(_node->getId());
    if (factory->reverseEdges)
      factory->reverseEdges->insertEdge(_node, this, edkControlFlowBlock_Pred);
  }

  void ControlFlowBlock::addPred(NodeId _id) {
    const base::ControlFlowBlock *node = dynamic_cast<base::ControlFlowBlock*>(factory->getPointer(_id));
    if (node == NULL)
      throw LimException(COLUMBUS_LOCATION, CMSG_EX_INVALID_NODE_KIND);
    addPred( node );
  }

  void ControlFlowBlock::removePred(NodeId id) {
    if (!factory->getExist(id))
      throw LimException(COLUMBUS_LOCATION, CMSG_EX_THE_END_POINT_OF_THE_EDGE_DOES_NOT_EXIST);

    ListIterator<base::ControlFlowBlock>::Container::iterator it = find(predContainer.begin(), predContainer.end(), id);

    if (it == predContainer.end())
      throw LimException(COLUMBUS_LOCATION, CMSG_EX_THE_END_POINT_OF_THE_EDGE_DOES_NOT_EXIST);

    predContainer.erase(it);

    if (factory->getExistsReverseEdges())
      factory->reverseEdges->removeEdge(id, this->getId(), edkControlFlowBlock_Pred);
  }

  void ControlFlowBlock::removePred(base::ControlFlowBlock *_node) {
    if (_node == NULL)
      throw LimException(COLUMBUS_LOCATION, CMSG_EX_THE_EDGE_IS_NULL);

    removePred(_node->getId());
  }

  void ControlFlowBlock::accept(Visitor &visitor) const {
    visitor.visit(*this);
  }

  void ControlFlowBlock::acceptEnd(Visitor &visitor) const {
    visitor.visitEnd(*this);
  }

  double ControlFlowBlock::getSimilarity(const base::Base& base){
    if(base.getNodeKind() == getNodeKind()) {
      return 1.0;
    } else {
      return 0.0;
    }
  }

  void ControlFlowBlock::swapStringTable(RefDistributorStrTable& newStrTable, std::map<Key,Key>& oldAndNewStrKeyMap ){
    std::map<Key,Key>::iterator foundKeyId;

  }

  NodeHashType ControlFlowBlock::getHash(std::set<NodeId>& travNodes) const {
    if (hashOk) return nodeHashCache;
    common::WriteMsg::write(CMSG_GET_THE_NODE_HASH_OF_NODE_BEGIN,this->getId()); 
    if (travNodes.count(getId())>0) {
      common::WriteMsg::write(CMSG_GET_THE_NODE_HASH_OF_NODE_SKIP);
      return 0;
    }
    travNodes.insert(getId());
    Crc_type resultHash;
    resultHash.process_bytes( "base::ControlFlowBlock", strlen("base::ControlFlowBlock"));
    common::WriteMsg::write(CMSG_GET_THE_NODE_HASH_OF_NODE_END,resultHash.checksum()); 
    nodeHashCache = resultHash.checksum();
    hashOk = true;
    return nodeHashCache;
  }

  void ControlFlowBlock::save(io::BinaryIO &binIo,bool withVirtualBase  /*= true*/) const {
    Base::save(binIo,false);


    for (ListIterator<logical::Method>::Container::const_iterator it = callsContainer.begin(); it != callsContainer.end(); ++it) {
      binIo.writeUInt4(*it);
    }
    binIo.writeUInt4(0); // This is the end sign

    for (ListIterator<base::ControlFlowBlock>::Container::const_iterator it = predContainer.begin(); it != predContainer.end(); ++it) {
      binIo.writeUInt4(*it);
    }
    binIo.writeUInt4(0); // This is the end sign
  }

  void ControlFlowBlock::load(io::BinaryIO &binIo, bool withVirtualBase /*= true*/) {
    Base::load(binIo,false);

    NodeId _id;

    _id = binIo.readUInt4();
    while (_id) {
      callsContainer.push_back(_id);
      _id = binIo.readUInt4();
    }

    _id = binIo.readUInt4();
    while (_id) {
      predContainer.push_back(_id);
      _id = binIo.readUInt4();
    }
  }


}


}}}
