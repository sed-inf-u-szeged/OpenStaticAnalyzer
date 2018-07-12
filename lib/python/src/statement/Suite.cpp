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
  Suite::Suite(NodeId _id, Factory *_factory) :
    Positioned(_id, _factory),
    hasStatementContainer()
  {
  }

  Suite::~Suite() {
  }

  void Suite::prepareDelete(bool tryOnVirtualParent){
    while (!hasStatementContainer.empty()) {
      const NodeId id = *hasStatementContainer.begin();
      removeParentEdge(id);
      if (factory->getExistsReverseEdges())
        factory->reverseEdges->removeEdge(id, this->getId(), edkSuite_HasStatement);
      hasStatementContainer.pop_front();
    }
    base::Positioned::prepareDelete(false);
  }

  NodeKind Suite::getNodeKind() const {
    return ndkSuite;
  }

  ListIterator<base::Positioned> Suite::getStatementListIteratorBegin() const {
    return ListIterator<base::Positioned>(&hasStatementContainer, factory, true);
  }

  ListIterator<base::Positioned> Suite::getStatementListIteratorEnd() const {
    return ListIterator<base::Positioned>(&hasStatementContainer, factory, false);
  }

  bool Suite::getStatementIsEmpty() const {
    return getStatementListIteratorBegin() == getStatementListIteratorEnd();
  }

  unsigned int Suite::getStatementSize() const {
    unsigned int size = 0;
    ListIterator<base::Positioned> endIt = getStatementListIteratorEnd();
    for (ListIterator<base::Positioned> it = getStatementListIteratorBegin(); it != endIt; ++it) {
      ++size;
    }
    return size;
  }

  bool Suite::setEdge(EdgeKind edgeKind, NodeId edgeEnd, bool tryOnVirtualParent) {
    switch (edgeKind) {
      case edkSuite_HasStatement:
        addStatement(edgeEnd);
        return true;
      default:
        break;
    }
    if (base::Positioned::setEdge(edgeKind, edgeEnd, false)) {
      return true;
    }
    return false;
  }

  bool Suite::removeEdge(EdgeKind edgeKind, NodeId edgeEnd, bool tryOnVirtualParent) {
    switch (edgeKind) {
      case edkSuite_HasStatement:
        removeStatement(edgeEnd);
        return true;
      default:
        break;
    }
    if (base::Positioned::removeEdge(edgeKind, edgeEnd, false)) {
      return true;
    }
    return false;
  }

  void Suite::addStatement(const base::Positioned *_node) {
    if (_node == NULL)
      throw PythonException(COLUMBUS_LOCATION, CMSG_EX_THE_NODE_IS_NULL);

    if (&(_node->getFactory()) != this->factory)
      throw PythonException(COLUMBUS_LOCATION, CMSG_EX_THE_FACTORY_OF_NODES_DOES_NOT_MATCH);

    if (!(Common::getIsStatement(*_node) || Common::getIsExpression(*_node)))
      throw PythonException(COLUMBUS_LOCATION, CMSG_EX_INVALID_NODE_KIND);

    hasStatementContainer.push_back(_node->getId());
    setParentEdge(_node,edkSuite_HasStatement);

    if (factory->reverseEdges)
      factory->reverseEdges->insertEdge(_node, this, edkSuite_HasStatement);
  }

  void Suite::addStatement(NodeId _id) {
    const base::Positioned *node = dynamic_cast<base::Positioned*>(factory->getPointer(_id));
    if (node == NULL)
      throw PythonException(COLUMBUS_LOCATION, CMSG_EX_INVALID_NODE_KIND);
    addStatement( node );
  }

  void Suite::removeStatement(NodeId id) {
    if (!factory->getExist(id))
      throw PythonException(COLUMBUS_LOCATION, CMSG_EX_THE_END_POINT_OF_THE_EDGE_DOES_NOT_EXIST);

    ListIterator<base::Positioned>::Container::iterator it = find(hasStatementContainer.begin(), hasStatementContainer.end(), id);

    if (it == hasStatementContainer.end())
      throw PythonException(COLUMBUS_LOCATION, CMSG_EX_THE_END_POINT_OF_THE_EDGE_DOES_NOT_EXIST);

    hasStatementContainer.erase(it);

    removeParentEdge(id);

    if (factory->getExistsReverseEdges())
      factory->reverseEdges->removeEdge(id, this->getId(), edkSuite_HasStatement);
  }

  void Suite::removeStatement(base::Positioned *_node) {
    if (_node == NULL)
      throw PythonException(COLUMBUS_LOCATION, CMSG_EX_THE_EDGE_IS_NULL);

    removeStatement(_node->getId());
  }

  void Suite::accept(Visitor &visitor) const {
    visitor.visit(*this);
  }

  void Suite::acceptEnd(Visitor &visitor) const {
    visitor.visitEnd(*this);
  }

  double Suite::getSimilarity(const base::Base& base){
    if(base.getNodeKind() == getNodeKind()) {
      return 1.0;
    } else {
      return 0.0;
    }
  }

  void Suite::swapStringTable(RefDistributorStrTable& newStrTable, std::map<Key,Key>& oldAndNewStrKeyMap ){
    std::map<Key,Key>::iterator foundKeyId;

  }

  NodeHashType Suite::getHash(std::set<NodeId>& travNodes) const {
    if (hashOk) return nodeHashCache;
    common::WriteMsg::write(CMSG_GET_THE_NODE_HASH_OF_NODE_BEGIN,this->getId()); 
    if (travNodes.count(getId())>0) {
      common::WriteMsg::write(CMSG_GET_THE_NODE_HASH_OF_NODE_SKIP);
      return 0;
    }
    travNodes.insert(getId());
    Crc_type resultHash;
    resultHash.process_bytes( "statement::Suite", strlen("statement::Suite"));
    common::WriteMsg::write(CMSG_GET_THE_NODE_HASH_OF_NODE_END,resultHash.checksum()); 
    nodeHashCache = resultHash.checksum();
    hashOk = true;
    return nodeHashCache;
  }

  void Suite::save(io::BinaryIO &binIo,bool withVirtualBase  /*= true*/) const {
    Positioned::save(binIo,false);


    for (ListIterator<base::Positioned>::Container::const_iterator it = hasStatementContainer.begin(); it != hasStatementContainer.end(); ++it) {
      binIo.writeUInt4(*it);
    }
    binIo.writeUInt4(0); // This is the end sign
  }

  void Suite::load(io::BinaryIO &binIo, bool withVirtualBase /*= true*/) {
    Positioned::load(binIo,false);

    NodeId _id;

    _id = binIo.readUInt4();
    while (_id) {
      hasStatementContainer.push_back(_id);
      setParentEdge(factory->getPointer(_id),edkSuite_HasStatement);
      _id = binIo.readUInt4();
    }
  }


}


}}}
