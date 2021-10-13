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
  With::With(NodeId _id, Factory *_factory) :
    CompoundStatement(_id, _factory),
    m_isAsync(false),
    hasWithItemContainer()
  {
  }

  With::~With() {
  }

  void With::prepareDelete(bool tryOnVirtualParent){
    while (!hasWithItemContainer.empty()) {
      const NodeId id = *hasWithItemContainer.begin();
      removeParentEdge(id);
      if (factory->getExistsReverseEdges())
        factory->reverseEdges->removeEdge(id, this->getId(), edkWith_HasWithItem);
      hasWithItemContainer.pop_front();
    }
    statement::CompoundStatement::prepareDelete(false);
  }

  NodeKind With::getNodeKind() const {
    return ndkWith;
  }

  bool With::getIsAsync() const {
    return m_isAsync;
  }

  void With::setIsAsync(bool _isAsync) {
    m_isAsync = _isAsync;
  }

  ListIterator<statement::WithItem> With::getWithItemListIteratorBegin() const {
    return ListIterator<statement::WithItem>(&hasWithItemContainer, factory, true);
  }

  ListIterator<statement::WithItem> With::getWithItemListIteratorEnd() const {
    return ListIterator<statement::WithItem>(&hasWithItemContainer, factory, false);
  }

  bool With::getWithItemIsEmpty() const {
    return getWithItemListIteratorBegin() == getWithItemListIteratorEnd();
  }

  unsigned int With::getWithItemSize() const {
    unsigned int size = 0;
    ListIterator<statement::WithItem> endIt = getWithItemListIteratorEnd();
    for (ListIterator<statement::WithItem> it = getWithItemListIteratorBegin(); it != endIt; ++it) {
      ++size;
    }
    return size;
  }

  bool With::setEdge(EdgeKind edgeKind, NodeId edgeEnd, bool tryOnVirtualParent) {
    switch (edgeKind) {
      case edkWith_HasWithItem:
        addWithItem(edgeEnd);
        return true;
      default:
        break;
    }
    if (statement::CompoundStatement::setEdge(edgeKind, edgeEnd, false)) {
      return true;
    }
    return false;
  }

  bool With::removeEdge(EdgeKind edgeKind, NodeId edgeEnd, bool tryOnVirtualParent) {
    switch (edgeKind) {
      case edkWith_HasWithItem:
        removeWithItem(edgeEnd);
        return true;
      default:
        break;
    }
    if (statement::CompoundStatement::removeEdge(edgeKind, edgeEnd, false)) {
      return true;
    }
    return false;
  }

  void With::addWithItem(const statement::WithItem *_node) {
    if (_node == NULL)
      throw PythonException(COLUMBUS_LOCATION, CMSG_EX_THE_NODE_IS_NULL);

    if (&(_node->getFactory()) != this->factory)
      throw PythonException(COLUMBUS_LOCATION, CMSG_EX_THE_FACTORY_OF_NODES_DOES_NOT_MATCH);

    if (!((_node->getNodeKind() == ndkWithItem) ))
      throw PythonException(COLUMBUS_LOCATION, CMSG_EX_INVALID_NODE_KIND);

    hasWithItemContainer.push_back(_node->getId());
    setParentEdge(_node,edkWith_HasWithItem);

    if (factory->reverseEdges)
      factory->reverseEdges->insertEdge(_node, this, edkWith_HasWithItem);
  }

  void With::addWithItem(NodeId _id) {
    const statement::WithItem *node = dynamic_cast<statement::WithItem*>(factory->getPointer(_id));
    if (node == NULL)
      throw PythonException(COLUMBUS_LOCATION, CMSG_EX_INVALID_NODE_KIND);
    addWithItem( node );
  }

  void With::removeWithItem(NodeId id) {
    if (!factory->getExist(id))
      throw PythonException(COLUMBUS_LOCATION, CMSG_EX_THE_END_POINT_OF_THE_EDGE_DOES_NOT_EXIST);

    ListIterator<statement::WithItem>::Container::iterator it = find(hasWithItemContainer.begin(), hasWithItemContainer.end(), id);

    if (it == hasWithItemContainer.end())
      throw PythonException(COLUMBUS_LOCATION, CMSG_EX_THE_END_POINT_OF_THE_EDGE_DOES_NOT_EXIST);

    hasWithItemContainer.erase(it);

    removeParentEdge(id);

    if (factory->getExistsReverseEdges())
      factory->reverseEdges->removeEdge(id, this->getId(), edkWith_HasWithItem);
  }

  void With::removeWithItem(statement::WithItem *_node) {
    if (_node == NULL)
      throw PythonException(COLUMBUS_LOCATION, CMSG_EX_THE_EDGE_IS_NULL);

    removeWithItem(_node->getId());
  }

  void With::accept(Visitor &visitor) const {
    visitor.visit(*this);
  }

  void With::acceptEnd(Visitor &visitor) const {
    visitor.visitEnd(*this);
  }

  double With::getSimilarity(const base::Base& base){
    if(base.getNodeKind() == getNodeKind()) {
      const With& node = dynamic_cast<const With&>(base);
      double matchAttrs = 0;
      if(node.getIsAsync() == getIsAsync()) ++matchAttrs;
      return matchAttrs / (1 / (1 - Common::SimilarityMinimum)) + Common::SimilarityMinimum;
    } else {
      return 0.0;
    }
  }

  void With::swapStringTable(RefDistributorStrTable& newStrTable, std::map<Key,Key>& oldAndNewStrKeyMap ){
    std::map<Key,Key>::iterator foundKeyId;

  }

  NodeHashType With::getHash(std::set<NodeId>& travNodes) const {
    if (hashOk) return nodeHashCache;
    common::WriteMsg::write(CMSG_GET_THE_NODE_HASH_OF_NODE_BEGIN,this->getId()); 
    if (travNodes.count(getId())>0) {
      common::WriteMsg::write(CMSG_GET_THE_NODE_HASH_OF_NODE_SKIP);
      return 0;
    }
    travNodes.insert(getId());
    Crc_type resultHash;
    resultHash.process_bytes( "statement::With", strlen("statement::With"));
    common::WriteMsg::write(CMSG_GET_THE_NODE_HASH_OF_NODE_END,resultHash.checksum()); 
    nodeHashCache = resultHash.checksum();
    hashOk = true;
    return nodeHashCache;
  }

  void With::save(io::BinaryIO &binIo,bool withVirtualBase  /*= true*/) const {
    CompoundStatement::save(binIo,false);

    unsigned char boolValues = 0;
    boolValues <<= 1;
    if (m_isAsync) 
      boolValues |= 1;
    binIo.writeUByte1(boolValues);


    for (ListIterator<statement::WithItem>::Container::const_iterator it = hasWithItemContainer.begin(); it != hasWithItemContainer.end(); ++it) {
      binIo.writeUInt4(*it);
    }
    binIo.writeUInt4(0); // This is the end sign
  }

  void With::load(io::BinaryIO &binIo, bool withVirtualBase /*= true*/) {
    CompoundStatement::load(binIo,false);

    unsigned char boolValues = binIo.readUByte1();
    m_isAsync = boolValues & 1;
    boolValues >>= 1;

    NodeId _id;

    _id = binIo.readUInt4();
    while (_id) {
      hasWithItemContainer.push_back(_id);
      setParentEdge(factory->getPointer(_id),edkWith_HasWithItem);
      _id = binIo.readUInt4();
    }
  }


}


}}}
