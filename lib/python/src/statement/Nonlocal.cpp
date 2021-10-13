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

namespace statement { 
  Nonlocal::Nonlocal(NodeId _id, Factory *_factory) :
    SimpleStatement(_id, _factory),
    hasIdentifierContainer()
  {
  }

  Nonlocal::~Nonlocal() {
  }

  void Nonlocal::prepareDelete(bool tryOnVirtualParent){
    while (!hasIdentifierContainer.empty()) {
      const NodeId id = *hasIdentifierContainer.begin();
      removeParentEdge(id);
      if (factory->getExistsReverseEdges())
        factory->reverseEdges->removeEdge(id, this->getId(), edkNonlocal_HasIdentifier);
      hasIdentifierContainer.pop_front();
    }
    statement::SimpleStatement::prepareDelete(false);
  }

  NodeKind Nonlocal::getNodeKind() const {
    return ndkNonlocal;
  }

  ListIterator<expression::Identifier> Nonlocal::getIdentifierListIteratorBegin() const {
    return ListIterator<expression::Identifier>(&hasIdentifierContainer, factory, true);
  }

  ListIterator<expression::Identifier> Nonlocal::getIdentifierListIteratorEnd() const {
    return ListIterator<expression::Identifier>(&hasIdentifierContainer, factory, false);
  }

  bool Nonlocal::getIdentifierIsEmpty() const {
    return getIdentifierListIteratorBegin() == getIdentifierListIteratorEnd();
  }

  unsigned int Nonlocal::getIdentifierSize() const {
    unsigned int size = 0;
    ListIterator<expression::Identifier> endIt = getIdentifierListIteratorEnd();
    for (ListIterator<expression::Identifier> it = getIdentifierListIteratorBegin(); it != endIt; ++it) {
      ++size;
    }
    return size;
  }

  bool Nonlocal::setEdge(EdgeKind edgeKind, NodeId edgeEnd, bool tryOnVirtualParent) {
    switch (edgeKind) {
      case edkNonlocal_HasIdentifier:
        addIdentifier(edgeEnd);
        return true;
      default:
        break;
    }
    if (statement::SimpleStatement::setEdge(edgeKind, edgeEnd, false)) {
      return true;
    }
    return false;
  }

  bool Nonlocal::removeEdge(EdgeKind edgeKind, NodeId edgeEnd, bool tryOnVirtualParent) {
    switch (edgeKind) {
      case edkNonlocal_HasIdentifier:
        removeIdentifier(edgeEnd);
        return true;
      default:
        break;
    }
    if (statement::SimpleStatement::removeEdge(edgeKind, edgeEnd, false)) {
      return true;
    }
    return false;
  }

  void Nonlocal::addIdentifier(const expression::Identifier *_node) {
    if (_node == NULL)
      throw PythonException(COLUMBUS_LOCATION, CMSG_EX_THE_NODE_IS_NULL);

    if (&(_node->getFactory()) != this->factory)
      throw PythonException(COLUMBUS_LOCATION, CMSG_EX_THE_FACTORY_OF_NODES_DOES_NOT_MATCH);

    if (!((_node->getNodeKind() == ndkIdentifier) ))
      throw PythonException(COLUMBUS_LOCATION, CMSG_EX_INVALID_NODE_KIND);

    hasIdentifierContainer.push_back(_node->getId());
    setParentEdge(_node,edkNonlocal_HasIdentifier);

    if (factory->reverseEdges)
      factory->reverseEdges->insertEdge(_node, this, edkNonlocal_HasIdentifier);
  }

  void Nonlocal::addIdentifier(NodeId _id) {
    const expression::Identifier *node = dynamic_cast<expression::Identifier*>(factory->getPointer(_id));
    if (node == NULL)
      throw PythonException(COLUMBUS_LOCATION, CMSG_EX_INVALID_NODE_KIND);
    addIdentifier( node );
  }

  void Nonlocal::removeIdentifier(NodeId id) {
    if (!factory->getExist(id))
      throw PythonException(COLUMBUS_LOCATION, CMSG_EX_THE_END_POINT_OF_THE_EDGE_DOES_NOT_EXIST);

    ListIterator<expression::Identifier>::Container::iterator it = find(hasIdentifierContainer.begin(), hasIdentifierContainer.end(), id);

    if (it == hasIdentifierContainer.end())
      throw PythonException(COLUMBUS_LOCATION, CMSG_EX_THE_END_POINT_OF_THE_EDGE_DOES_NOT_EXIST);

    hasIdentifierContainer.erase(it);

    removeParentEdge(id);

    if (factory->getExistsReverseEdges())
      factory->reverseEdges->removeEdge(id, this->getId(), edkNonlocal_HasIdentifier);
  }

  void Nonlocal::removeIdentifier(expression::Identifier *_node) {
    if (_node == NULL)
      throw PythonException(COLUMBUS_LOCATION, CMSG_EX_THE_EDGE_IS_NULL);

    removeIdentifier(_node->getId());
  }

  void Nonlocal::accept(Visitor &visitor) const {
    visitor.visit(*this);
  }

  void Nonlocal::acceptEnd(Visitor &visitor) const {
    visitor.visitEnd(*this);
  }

  double Nonlocal::getSimilarity(const base::Base& base){
    if(base.getNodeKind() == getNodeKind()) {
      return 1.0;
    } else {
      return 0.0;
    }
  }

  void Nonlocal::swapStringTable(RefDistributorStrTable& newStrTable, std::map<Key,Key>& oldAndNewStrKeyMap ){
    std::map<Key,Key>::iterator foundKeyId;

  }

  NodeHashType Nonlocal::getHash(std::set<NodeId>& travNodes) const {
    if (hashOk) return nodeHashCache;
    common::WriteMsg::write(CMSG_GET_THE_NODE_HASH_OF_NODE_BEGIN,this->getId()); 
    if (travNodes.count(getId())>0) {
      common::WriteMsg::write(CMSG_GET_THE_NODE_HASH_OF_NODE_SKIP);
      return 0;
    }
    travNodes.insert(getId());
    Crc_type resultHash;
    resultHash.process_bytes( "statement::Nonlocal", strlen("statement::Nonlocal"));
    common::WriteMsg::write(CMSG_GET_THE_NODE_HASH_OF_NODE_END,resultHash.checksum()); 
    nodeHashCache = resultHash.checksum();
    hashOk = true;
    return nodeHashCache;
  }

  void Nonlocal::save(io::BinaryIO &binIo,bool withVirtualBase  /*= true*/) const {
    SimpleStatement::save(binIo,false);


    for (ListIterator<expression::Identifier>::Container::const_iterator it = hasIdentifierContainer.begin(); it != hasIdentifierContainer.end(); ++it) {
      binIo.writeUInt4(*it);
    }
    binIo.writeUInt4(0); // This is the end sign
  }

  void Nonlocal::load(io::BinaryIO &binIo, bool withVirtualBase /*= true*/) {
    SimpleStatement::load(binIo,false);

    NodeId _id;

    _id = binIo.readUInt4();
    while (_id) {
      hasIdentifierContainer.push_back(_id);
      setParentEdge(factory->getPointer(_id),edkNonlocal_HasIdentifier);
      _id = binIo.readUInt4();
    }
  }


}


}}}
