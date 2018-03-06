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
  ImportStatement::ImportStatement(NodeId _id, Factory *_factory) :
    SimpleStatement(_id, _factory),
    hasAliasContainer()
  {
  }

  ImportStatement::~ImportStatement() {
  }

  void ImportStatement::prepareDelete(bool tryOnVirtualParent){
    while (!hasAliasContainer.empty()) {
      const NodeId id = *hasAliasContainer.begin();
      removeParentEdge(id);
      if (factory->getExistsReverseEdges())
        factory->reverseEdges->removeEdge(id, this->getId(), edkImportStatement_HasAlias);
      hasAliasContainer.pop_front();
    }
    statement::SimpleStatement::prepareDelete(false);
  }

  NodeKind ImportStatement::getNodeKind() const {
    return ndkImportStatement;
  }

  ListIterator<statement::Alias> ImportStatement::getAliasListIteratorBegin() const {
    return ListIterator<statement::Alias>(&hasAliasContainer, factory, true);
  }

  ListIterator<statement::Alias> ImportStatement::getAliasListIteratorEnd() const {
    return ListIterator<statement::Alias>(&hasAliasContainer, factory, false);
  }

  bool ImportStatement::getAliasIsEmpty() const {
    return getAliasListIteratorBegin() == getAliasListIteratorEnd();
  }

  unsigned int ImportStatement::getAliasSize() const {
    unsigned int size = 0;
    ListIterator<statement::Alias> endIt = getAliasListIteratorEnd();
    for (ListIterator<statement::Alias> it = getAliasListIteratorBegin(); it != endIt; ++it) {
      ++size;
    }
    return size;
  }

  bool ImportStatement::setEdge(EdgeKind edgeKind, NodeId edgeEnd, bool tryOnVirtualParent) {
    switch (edgeKind) {
      case edkImportStatement_HasAlias:
        addAlias(edgeEnd);
        return true;
      default:
        break;
    }
    if (statement::SimpleStatement::setEdge(edgeKind, edgeEnd, false)) {
      return true;
    }
    return false;
  }

  bool ImportStatement::removeEdge(EdgeKind edgeKind, NodeId edgeEnd, bool tryOnVirtualParent) {
    switch (edgeKind) {
      case edkImportStatement_HasAlias:
        removeAlias(edgeEnd);
        return true;
      default:
        break;
    }
    if (statement::SimpleStatement::removeEdge(edgeKind, edgeEnd, false)) {
      return true;
    }
    return false;
  }

  void ImportStatement::addAlias(const statement::Alias *_node) {
    if (_node == NULL)
      throw PythonException(COLUMBUS_LOCATION, CMSG_EX_THE_NODE_IS_NULL);

    if (&(_node->getFactory()) != this->factory)
      throw PythonException(COLUMBUS_LOCATION, CMSG_EX_THE_FACTORY_OF_NODES_DOES_NOT_MATCH);

    if (!((_node->getNodeKind() == ndkAlias) ))
      throw PythonException(COLUMBUS_LOCATION, CMSG_EX_INVALID_NODE_KIND);

    hasAliasContainer.push_back(_node->getId());
    setParentEdge(_node,edkImportStatement_HasAlias);

    if (factory->reverseEdges)
      factory->reverseEdges->insertEdge(_node, this, edkImportStatement_HasAlias);
  }

  void ImportStatement::addAlias(NodeId _id) {
    const statement::Alias *node = dynamic_cast<statement::Alias*>(factory->getPointer(_id));
    if (node == NULL)
      throw PythonException(COLUMBUS_LOCATION, CMSG_EX_INVALID_NODE_KIND);
    addAlias( node );
  }

  void ImportStatement::removeAlias(NodeId id) {
    if (!factory->getExist(id))
      throw PythonException(COLUMBUS_LOCATION, CMSG_EX_THE_END_POINT_OF_THE_EDGE_DOES_NOT_EXIST);

    ListIterator<statement::Alias>::Container::iterator it = find(hasAliasContainer.begin(), hasAliasContainer.end(), id);

    if (it == hasAliasContainer.end())
      throw PythonException(COLUMBUS_LOCATION, CMSG_EX_THE_END_POINT_OF_THE_EDGE_DOES_NOT_EXIST);

    hasAliasContainer.erase(it);

    removeParentEdge(id);

    if (factory->getExistsReverseEdges())
      factory->reverseEdges->removeEdge(id, this->getId(), edkImportStatement_HasAlias);
  }

  void ImportStatement::removeAlias(statement::Alias *_node) {
    if (_node == NULL)
      throw PythonException(COLUMBUS_LOCATION, CMSG_EX_THE_EDGE_IS_NULL);

    removeAlias(_node->getId());
  }

  void ImportStatement::accept(Visitor &visitor) const {
    visitor.visit(*this);
  }

  void ImportStatement::acceptEnd(Visitor &visitor) const {
    visitor.visitEnd(*this);
  }

  double ImportStatement::getSimilarity(const base::Base& base){
    if(base.getNodeKind() == getNodeKind()) {
      return 1.0;
    } else {
      return 0.0;
    }
  }

  void ImportStatement::swapStringTable(RefDistributorStrTable& newStrTable, std::map<Key,Key>& oldAndNewStrKeyMap ){
    std::map<Key,Key>::iterator foundKeyId;

  }

  NodeHashType ImportStatement::getHash(std::set<NodeId>& travNodes) const {
    if (hashOk) return nodeHashCache;
    common::WriteMsg::write(CMSG_GET_THE_NODE_HASH_OF_NODE_BEGIN,this->getId()); 
    if (travNodes.count(getId())>0) {
      common::WriteMsg::write(CMSG_GET_THE_NODE_HASH_OF_NODE_SKIP);
      return 0;
    }
    travNodes.insert(getId());
    Crc_type resultHash;
    resultHash.process_bytes( "statement::ImportStatement", strlen("statement::ImportStatement"));
    common::WriteMsg::write(CMSG_GET_THE_NODE_HASH_OF_NODE_END,resultHash.checksum()); 
    nodeHashCache = resultHash.checksum();
    hashOk = true;
    return nodeHashCache;
  }

  void ImportStatement::save(io::BinaryIO &binIo,bool withVirtualBase  /*= true*/) const {
    SimpleStatement::save(binIo,false);


    for (ListIterator<statement::Alias>::Container::const_iterator it = hasAliasContainer.begin(); it != hasAliasContainer.end(); ++it) {
      binIo.writeUInt4(*it);
    }
    binIo.writeUInt4(0); // This is the end sign
  }

  void ImportStatement::load(io::BinaryIO &binIo, bool withVirtualBase /*= true*/) {
    SimpleStatement::load(binIo,false);

    NodeId _id;

    _id = binIo.readUInt4();
    while (_id) {
      hasAliasContainer.push_back(_id);
      setParentEdge(factory->getPointer(_id),edkImportStatement_HasAlias);
      _id = binIo.readUInt4();
    }
  }


}


}}}
