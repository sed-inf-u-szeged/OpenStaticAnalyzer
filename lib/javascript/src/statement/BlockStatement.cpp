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

#include "javascript/inc/javascript.h"
#include "javascript/inc/Common.h"
#include "common/inc/WriteMessage.h"

#include "javascript/inc/messages.h"
#include <algorithm>
#include <string.h>
#include "common/inc/math/common.h"


namespace columbus { namespace javascript { namespace asg {

typedef boost::crc_32_type  Crc_type;

namespace statement { 
  BlockStatement::BlockStatement(NodeId _id, Factory *_factory) :
         Positioned(_id, _factory),
    Statement(_id, _factory),
    hasBodyContainer()
  {
  }

  BlockStatement::~BlockStatement() {
  }

  void BlockStatement::prepareDelete(bool tryOnVirtualParent){
    while (!hasBodyContainer.empty()) {
      const NodeId id = *hasBodyContainer.begin();
      removeParentEdge(id);
      if (factory->getExistsReverseEdges())
        factory->reverseEdges->removeEdge(id, this->getId(), edkBlockStatement_HasBody);
      hasBodyContainer.pop_front();
    }
    if (tryOnVirtualParent) {
      base::Positioned::prepareDelete(false);
    }
    statement::Statement::prepareDelete(false);
  }

  NodeKind BlockStatement::getNodeKind() const {
    return ndkBlockStatement;
  }

  ListIterator<statement::Statement> BlockStatement::getBodyListIteratorBegin() const {
    return ListIterator<statement::Statement>(&hasBodyContainer, factory, true);
  }

  ListIterator<statement::Statement> BlockStatement::getBodyListIteratorEnd() const {
    return ListIterator<statement::Statement>(&hasBodyContainer, factory, false);
  }

  bool BlockStatement::getBodyIsEmpty() const {
    return getBodyListIteratorBegin() == getBodyListIteratorEnd();
  }

  unsigned int BlockStatement::getBodySize() const {
    unsigned int size = 0;
    ListIterator<statement::Statement> endIt = getBodyListIteratorEnd();
    for (ListIterator<statement::Statement> it = getBodyListIteratorBegin(); it != endIt; ++it) {
      ++size;
    }
    return size;
  }

  bool BlockStatement::setEdge(EdgeKind edgeKind, NodeId edgeEnd, bool tryOnVirtualParent) {
    switch (edgeKind) {
      case edkBlockStatement_HasBody:
        addBody(edgeEnd);
        return true;
      default:
        break;
    }
    if (tryOnVirtualParent) {
      if (base::Positioned::setEdge(edgeKind, edgeEnd, false)) {
        return true;
      }
    }
    if (statement::Statement::setEdge(edgeKind, edgeEnd, false)) {
      return true;
    }
    return false;
  }

  bool BlockStatement::removeEdge(EdgeKind edgeKind, NodeId edgeEnd, bool tryOnVirtualParent) {
    switch (edgeKind) {
      case edkBlockStatement_HasBody:
        removeBody(edgeEnd);
        return true;
      default:
        break;
    }
    if (tryOnVirtualParent) {
      if (base::Positioned::removeEdge(edgeKind, edgeEnd, false)) {
        return true;
      }
    }
    if (statement::Statement::removeEdge(edgeKind, edgeEnd, false)) {
      return true;
    }
    return false;
  }

  void BlockStatement::addBody(const statement::Statement *_node) {
    if (_node == NULL)
      throw JavascriptException(COLUMBUS_LOCATION, CMSG_EX_THE_NODE_IS_NULL);

    if (&(_node->getFactory()) != this->factory)
      throw JavascriptException(COLUMBUS_LOCATION, CMSG_EX_THE_FACTORY_OF_NODES_DOES_NOT_MATCH);

    if (!(Common::getIsStatement(*_node)))
      throw JavascriptException(COLUMBUS_LOCATION, CMSG_EX_INVALID_NODE_KIND);

    hasBodyContainer.push_back(_node->getId());
    setParentEdge(_node,edkBlockStatement_HasBody);

    if (factory->reverseEdges)
      factory->reverseEdges->insertEdge(_node, this, edkBlockStatement_HasBody);
  }

  void BlockStatement::addBody(NodeId _id) {
    const statement::Statement *node = dynamic_cast<statement::Statement*>(factory->getPointer(_id));
    if (node == NULL)
      throw JavascriptException(COLUMBUS_LOCATION, CMSG_EX_INVALID_NODE_KIND);
    addBody( node );
  }

  void BlockStatement::removeBody(NodeId id) {
    if (!factory->getExist(id))
      throw JavascriptException(COLUMBUS_LOCATION, CMSG_EX_THE_END_POINT_OF_THE_EDGE_DOES_NOT_EXIST);

    ListIterator<statement::Statement>::Container::iterator it = find(hasBodyContainer.begin(), hasBodyContainer.end(), id);

    if (it == hasBodyContainer.end())
      throw JavascriptException(COLUMBUS_LOCATION, CMSG_EX_THE_END_POINT_OF_THE_EDGE_DOES_NOT_EXIST);

    hasBodyContainer.erase(it);

    removeParentEdge(id);

    if (factory->getExistsReverseEdges())
      factory->reverseEdges->removeEdge(id, this->getId(), edkBlockStatement_HasBody);
  }

  void BlockStatement::removeBody(statement::Statement *_node) {
    if (_node == NULL)
      throw JavascriptException(COLUMBUS_LOCATION, CMSG_EX_THE_EDGE_IS_NULL);

    removeBody(_node->getId());
  }

  void BlockStatement::accept(Visitor &visitor) const {
    visitor.visit(*this);
  }

  void BlockStatement::acceptEnd(Visitor &visitor) const {
    visitor.visitEnd(*this);
  }

  double BlockStatement::getSimilarity(const base::Base& base){
    if(base.getNodeKind() == getNodeKind()) {
      return 1.0;
    } else {
      return 0.0;
    }
  }

  void BlockStatement::swapStringTable(RefDistributorStrTable& newStrTable, std::map<Key,Key>& oldAndNewStrKeyMap ){
    std::map<Key,Key>::iterator foundKeyId;

  }

  NodeHashType BlockStatement::getHash(std::set<NodeId>& travNodes) const {
    if (hashOk) return nodeHashCache;
    common::WriteMsg::write(CMSG_GET_THE_NODE_HASH_OF_NODE_BEGIN,this->getId()); 
    if (travNodes.count(getId())>0) {
      common::WriteMsg::write(CMSG_GET_THE_NODE_HASH_OF_NODE_SKIP);
      return 0;
    }
    travNodes.insert(getId());
    Crc_type resultHash;
    resultHash.process_bytes( "statement::BlockStatement", strlen("statement::BlockStatement"));
    common::WriteMsg::write(CMSG_GET_THE_NODE_HASH_OF_NODE_END,resultHash.checksum()); 
    nodeHashCache = resultHash.checksum();
    hashOk = true;
    return nodeHashCache;
  }

  void BlockStatement::save(io::BinaryIO &binIo,bool withVirtualBase  /*= true*/) const {
    if (withVirtualBase)
      Positioned::save(binIo,false);

    Statement::save(binIo,false);


    for (ListIterator<statement::Statement>::Container::const_iterator it = hasBodyContainer.begin(); it != hasBodyContainer.end(); ++it) {
      binIo.writeUInt4(*it);
    }
    binIo.writeUInt4(0); // This is the end sign
  }

  void BlockStatement::load(io::BinaryIO &binIo, bool withVirtualBase /*= true*/) {
    if (withVirtualBase)
      Positioned::load(binIo, false);

    Statement::load(binIo,false);

    NodeId _id;

    _id = binIo.readUInt4();
    while (_id) {
      hasBodyContainer.push_back(_id);
      setParentEdge(factory->getPointer(_id),edkBlockStatement_HasBody);
      _id = binIo.readUInt4();
    }
  }


}


}}}
