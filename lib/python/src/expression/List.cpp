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

namespace expression { 
  List::List(NodeId _id, Factory *_factory) :
    Expression(_id, _factory),
    m_isTuple(false),
    hasExpressionContainer()
  {
  }

  List::~List() {
  }

  void List::prepareDelete(bool tryOnVirtualParent){
    while (!hasExpressionContainer.empty()) {
      const NodeId id = *hasExpressionContainer.begin();
      removeParentEdge(id);
      if (factory->getExistsReverseEdges())
        factory->reverseEdges->removeEdge(id, this->getId(), edkList_HasExpression);
      hasExpressionContainer.pop_front();
    }
    expression::Expression::prepareDelete(false);
  }

  NodeKind List::getNodeKind() const {
    return ndkList;
  }

  bool List::getIsTuple() const {
    return m_isTuple;
  }

  void List::setIsTuple(bool _isTuple) {
    m_isTuple = _isTuple;
  }

  ListIterator<expression::Expression> List::getExpressionListIteratorBegin() const {
    return ListIterator<expression::Expression>(&hasExpressionContainer, factory, true);
  }

  ListIterator<expression::Expression> List::getExpressionListIteratorEnd() const {
    return ListIterator<expression::Expression>(&hasExpressionContainer, factory, false);
  }

  bool List::getExpressionIsEmpty() const {
    return getExpressionListIteratorBegin() == getExpressionListIteratorEnd();
  }

  unsigned int List::getExpressionSize() const {
    unsigned int size = 0;
    ListIterator<expression::Expression> endIt = getExpressionListIteratorEnd();
    for (ListIterator<expression::Expression> it = getExpressionListIteratorBegin(); it != endIt; ++it) {
      ++size;
    }
    return size;
  }

  bool List::setEdge(EdgeKind edgeKind, NodeId edgeEnd, bool tryOnVirtualParent) {
    switch (edgeKind) {
      case edkList_HasExpression:
        addExpression(edgeEnd);
        return true;
      default:
        break;
    }
    if (expression::Expression::setEdge(edgeKind, edgeEnd, false)) {
      return true;
    }
    return false;
  }

  bool List::removeEdge(EdgeKind edgeKind, NodeId edgeEnd, bool tryOnVirtualParent) {
    switch (edgeKind) {
      case edkList_HasExpression:
        removeExpression(edgeEnd);
        return true;
      default:
        break;
    }
    if (expression::Expression::removeEdge(edgeKind, edgeEnd, false)) {
      return true;
    }
    return false;
  }

  void List::addExpression(const expression::Expression *_node) {
    if (_node == NULL)
      throw PythonException(COLUMBUS_LOCATION, CMSG_EX_THE_NODE_IS_NULL);

    if (&(_node->getFactory()) != this->factory)
      throw PythonException(COLUMBUS_LOCATION, CMSG_EX_THE_FACTORY_OF_NODES_DOES_NOT_MATCH);

    if (!(Common::getIsExpression(*_node)))
      throw PythonException(COLUMBUS_LOCATION, CMSG_EX_INVALID_NODE_KIND);

    hasExpressionContainer.push_back(_node->getId());
    setParentEdge(_node,edkList_HasExpression);

    if (factory->reverseEdges)
      factory->reverseEdges->insertEdge(_node, this, edkList_HasExpression);
  }

  void List::addExpression(NodeId _id) {
    const expression::Expression *node = dynamic_cast<expression::Expression*>(factory->getPointer(_id));
    if (node == NULL)
      throw PythonException(COLUMBUS_LOCATION, CMSG_EX_INVALID_NODE_KIND);
    addExpression( node );
  }

  void List::removeExpression(NodeId id) {
    if (!factory->getExist(id))
      throw PythonException(COLUMBUS_LOCATION, CMSG_EX_THE_END_POINT_OF_THE_EDGE_DOES_NOT_EXIST);

    ListIterator<expression::Expression>::Container::iterator it = find(hasExpressionContainer.begin(), hasExpressionContainer.end(), id);

    if (it == hasExpressionContainer.end())
      throw PythonException(COLUMBUS_LOCATION, CMSG_EX_THE_END_POINT_OF_THE_EDGE_DOES_NOT_EXIST);

    hasExpressionContainer.erase(it);

    removeParentEdge(id);

    if (factory->getExistsReverseEdges())
      factory->reverseEdges->removeEdge(id, this->getId(), edkList_HasExpression);
  }

  void List::removeExpression(expression::Expression *_node) {
    if (_node == NULL)
      throw PythonException(COLUMBUS_LOCATION, CMSG_EX_THE_EDGE_IS_NULL);

    removeExpression(_node->getId());
  }

  void List::accept(Visitor &visitor) const {
    visitor.visit(*this);
  }

  void List::acceptEnd(Visitor &visitor) const {
    visitor.visitEnd(*this);
  }

  double List::getSimilarity(const base::Base& base){
    if(base.getNodeKind() == getNodeKind()) {
      const List& node = dynamic_cast<const List&>(base);
      double matchAttrs = 0;
      if(node.getIsTuple() == getIsTuple()) ++matchAttrs;
      return matchAttrs / (1 / (1 - Common::SimilarityMinimum)) + Common::SimilarityMinimum;
    } else {
      return 0.0;
    }
  }

  void List::swapStringTable(RefDistributorStrTable& newStrTable, std::map<Key,Key>& oldAndNewStrKeyMap ){
    std::map<Key,Key>::iterator foundKeyId;

  }

  NodeHashType List::getHash(std::set<NodeId>& travNodes) const {
    if (hashOk) return nodeHashCache;
    common::WriteMsg::write(CMSG_GET_THE_NODE_HASH_OF_NODE_BEGIN,this->getId()); 
    if (travNodes.count(getId())>0) {
      common::WriteMsg::write(CMSG_GET_THE_NODE_HASH_OF_NODE_SKIP);
      return 0;
    }
    travNodes.insert(getId());
    Crc_type resultHash;
    resultHash.process_bytes( "expression::List", strlen("expression::List"));
    common::WriteMsg::write(CMSG_GET_THE_NODE_HASH_OF_NODE_END,resultHash.checksum()); 
    nodeHashCache = resultHash.checksum();
    hashOk = true;
    return nodeHashCache;
  }

  void List::save(io::BinaryIO &binIo,bool withVirtualBase  /*= true*/) const {
    Expression::save(binIo,false);

    unsigned char boolValues = 0;
    boolValues <<= 1;
    if (m_isTuple) 
      boolValues |= 1;
    binIo.writeUByte1(boolValues);


    for (ListIterator<expression::Expression>::Container::const_iterator it = hasExpressionContainer.begin(); it != hasExpressionContainer.end(); ++it) {
      binIo.writeUInt4(*it);
    }
    binIo.writeUInt4(0); // This is the end sign
  }

  void List::load(io::BinaryIO &binIo, bool withVirtualBase /*= true*/) {
    Expression::load(binIo,false);

    unsigned char boolValues = binIo.readUByte1();
    m_isTuple = boolValues & 1;
    boolValues >>= 1;

    NodeId _id;

    _id = binIo.readUInt4();
    while (_id) {
      hasExpressionContainer.push_back(_id);
      setParentEdge(factory->getPointer(_id),edkList_HasExpression);
      _id = binIo.readUInt4();
    }
  }


}


}}}
