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

namespace statm { 
  Block::Block(NodeId _id, Factory *_factory) :
         Base(_id, _factory),
         Commentable(_id, _factory),
    Statement(_id, _factory),
    hasStatementsContainer()
  {
  }

  Block::~Block() {
  }

  void Block::clone(const Block& other, bool tryOnVirtualParent) {
    if (tryOnVirtualParent) {
      base::Base::clone(other, false);
    }
    if (tryOnVirtualParent) {
      base::Commentable::clone(other, false);
    }
    statm::Statement::clone(other, false);

    hasStatementsContainer = other.hasStatementsContainer;
  }

  void Block::prepareDelete(bool tryOnVirtualParent){
    while (!hasStatementsContainer.empty()) {
      const NodeId id = *hasStatementsContainer.begin();
      removeParentEdge(id);
      if (factory->getExistsReverseEdges())
        factory->reverseEdges->removeEdge(id, this->getId(), edkBlock_HasStatements);
      hasStatementsContainer.pop_front();
    }
    if (tryOnVirtualParent) {
      base::Base::prepareDelete(false);
    }
    if (tryOnVirtualParent) {
      base::Commentable::prepareDelete(false);
    }
    statm::Statement::prepareDelete(false);
  }

  NodeKind Block::getNodeKind() const {
    return ndkBlock;
  }

  ListIterator<statm::Statement> Block::getStatementsListIteratorBegin() const {
    return ListIterator<statm::Statement>(&hasStatementsContainer, factory, true);
  }

  ListIterator<statm::Statement> Block::getStatementsListIteratorEnd() const {
    return ListIterator<statm::Statement>(&hasStatementsContainer, factory, false);
  }

  bool Block::getStatementsIsEmpty() const {
    return getStatementsListIteratorBegin() == getStatementsListIteratorEnd();
  }

  unsigned int Block::getStatementsSize() const {
    unsigned int size = 0;
    ListIterator<statm::Statement> endIt = getStatementsListIteratorEnd();
    for (ListIterator<statm::Statement> it = getStatementsListIteratorBegin(); it != endIt; ++it) {
      ++size;
    }
    return size;
  }

  bool Block::setEdge(EdgeKind edgeKind, NodeId edgeEnd, bool tryOnVirtualParent) {
    switch (edgeKind) {
      case edkBlock_HasStatements:
        addStatements(edgeEnd);
        return true;
      default:
        break;
    }
    if (tryOnVirtualParent) {
      if (base::Base::setEdge(edgeKind, edgeEnd, false)) {
        return true;
      }
    }
    if (tryOnVirtualParent) {
      if (base::Commentable::setEdge(edgeKind, edgeEnd, false)) {
        return true;
      }
    }
    if (statm::Statement::setEdge(edgeKind, edgeEnd, false)) {
      return true;
    }
    return false;
  }

  bool Block::removeEdge(EdgeKind edgeKind, NodeId edgeEnd, bool tryOnVirtualParent) {
    switch (edgeKind) {
      case edkBlock_HasStatements:
        removeStatements(edgeEnd);
        return true;
      default:
        break;
    }
    if (tryOnVirtualParent) {
      if (base::Base::removeEdge(edgeKind, edgeEnd, false)) {
        return true;
      }
    }
    if (tryOnVirtualParent) {
      if (base::Commentable::removeEdge(edgeKind, edgeEnd, false)) {
        return true;
      }
    }
    if (statm::Statement::removeEdge(edgeKind, edgeEnd, false)) {
      return true;
    }
    return false;
  }

  void Block::addStatements(const statm::Statement *_node) {
    if (_node == NULL)
      throw JavaException(COLUMBUS_LOCATION, CMSG_EX_THE_NODE_IS_NULL);

    if (&(_node->getFactory()) != this->factory)
      throw JavaException(COLUMBUS_LOCATION, CMSG_EX_THE_FACTORY_OF_NODES_DOES_NOT_MATCH);

    if (!(Common::getIsStatement(*_node)))
      throw JavaException(COLUMBUS_LOCATION, CMSG_EX_INVALID_NODE_KIND);

    hasStatementsContainer.push_back(_node->getId());
    setParentEdge(_node,edkBlock_HasStatements);

    if (factory->reverseEdges)
      factory->reverseEdges->insertEdge(_node, this, edkBlock_HasStatements);
  }

  void Block::addStatements(NodeId _id) {
    const statm::Statement *node = dynamic_cast<statm::Statement*>(factory->getPointer(_id));
    if (node == NULL)
      throw JavaException(COLUMBUS_LOCATION, CMSG_EX_INVALID_NODE_KIND);
    addStatements( node );
  }

  void Block::removeStatements(NodeId id) {
    if (!factory->getExist(id))
      throw JavaException(COLUMBUS_LOCATION, CMSG_EX_THE_END_POINT_OF_THE_EDGE_DOES_NOT_EXIST);

    ListIterator<statm::Statement>::Container::iterator it = find(hasStatementsContainer.begin(), hasStatementsContainer.end(), id);

    if (it == hasStatementsContainer.end())
      throw JavaException(COLUMBUS_LOCATION, CMSG_EX_THE_END_POINT_OF_THE_EDGE_DOES_NOT_EXIST);

    hasStatementsContainer.erase(it);

    removeParentEdge(id);

    if (factory->getExistsReverseEdges())
      factory->reverseEdges->removeEdge(id, this->getId(), edkBlock_HasStatements);
  }

  void Block::removeStatements(statm::Statement *_node) {
    if (_node == NULL)
      throw JavaException(COLUMBUS_LOCATION, CMSG_EX_THE_EDGE_IS_NULL);

    removeStatements(_node->getId());
  }

  void Block::accept(Visitor &visitor) const {
    visitor.visit(*this);
  }

  void Block::acceptEnd(Visitor &visitor) const {
    visitor.visitEnd(*this);
  }

  double Block::getSimilarity(const base::Base& base){
    if(base.getNodeKind() == getNodeKind()) {
      const Block& node = dynamic_cast<const Block&>(base);
      double matchAttrs = 0;
      if(node.getIsCompilerGenerated() == getIsCompilerGenerated()) ++matchAttrs;
      if(node.getIsToolGenerated() == getIsToolGenerated()) ++matchAttrs;
      return matchAttrs / (2 / (1 - Common::SimilarityMinimum)) + Common::SimilarityMinimum;
    } else {
      return 0.0;
    }
  }

  void Block::swapStringTable(RefDistributorStrTable& newStrTable, std::map<Key,Key>& oldAndNewStrKeyMap ){
    std::map<Key,Key>::iterator foundKeyId;

  }

  NodeHashType Block::getHash(std::set<NodeId>& travNodes) const {
    if (hashOk) return nodeHashCache;
    common::WriteMsg::write(CMSG_GET_THE_NODE_HASH_OF_NODE_BEGIN,this->getId()); 
    if (travNodes.count(getId())>0) {
      common::WriteMsg::write(CMSG_GET_THE_NODE_HASH_OF_NODE_SKIP);
      return 0;
    }
    travNodes.insert(getId());
    Crc_type resultHash;
    resultHash.process_bytes( "statm::Block", strlen("statm::Block"));
    common::WriteMsg::write(CMSG_GET_THE_NODE_HASH_OF_NODE_END,resultHash.checksum()); 
    nodeHashCache = resultHash.checksum();
    hashOk = true;
    return nodeHashCache;
  }

  void Block::sort(bool withVirtualBase /* = true */) {
    if (withVirtualBase)
      Base::sort(false);
    if (withVirtualBase)
      Commentable::sort(false);
    Statement::sort(false);
  }

  void Block::save(io::BinaryIO &binIo,bool withVirtualBase  /*= true*/) const {
    if (withVirtualBase)
      Base::save(binIo,false);

    if (withVirtualBase)
      Commentable::save(binIo,false);

    Statement::save(binIo,false);


    for (ListIterator<statm::Statement>::Container::const_iterator it = hasStatementsContainer.begin(); it != hasStatementsContainer.end(); ++it) {
      binIo.writeUInt4(*it);
    }
    binIo.writeUInt4(0); // This is the end sign
  }

  void Block::load(io::BinaryIO &binIo, bool withVirtualBase /*= true*/) {
    if (withVirtualBase)
      Base::load(binIo, false);

    if (withVirtualBase)
      Commentable::load(binIo, false);

    Statement::load(binIo,false);

    NodeId _id;

    _id = binIo.readUInt4();
    while (_id) {
      hasStatementsContainer.push_back(_id);
      setParentEdge(factory->getPointer(_id),edkBlock_HasStatements);
      _id = binIo.readUInt4();
    }
  }


}


}}}
