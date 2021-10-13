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

namespace expression { 
  ArrayExpression::ArrayExpression(NodeId _id, Factory *_factory) :
         Positioned(_id, _factory),
    Expression(_id, _factory),
    hasElementsContainer()
  {
  }

  ArrayExpression::~ArrayExpression() {
  }

  void ArrayExpression::prepareDelete(bool tryOnVirtualParent){
    while (!hasElementsContainer.empty()) {
      const NodeId id = *hasElementsContainer.begin();
      removeParentEdge(id);
      if (factory->getExistsReverseEdges())
        factory->reverseEdges->removeEdge(id, this->getId(), edkArrayExpression_HasElements);
      hasElementsContainer.pop_front();
    }
    if (tryOnVirtualParent) {
      base::Positioned::prepareDelete(false);
    }
    expression::Expression::prepareDelete(false);
  }

  NodeKind ArrayExpression::getNodeKind() const {
    return ndkArrayExpression;
  }

  ListIterator<base::Positioned> ArrayExpression::getElementsListIteratorBegin() const {
    return ListIterator<base::Positioned>(&hasElementsContainer, factory, true);
  }

  ListIterator<base::Positioned> ArrayExpression::getElementsListIteratorEnd() const {
    return ListIterator<base::Positioned>(&hasElementsContainer, factory, false);
  }

  bool ArrayExpression::getElementsIsEmpty() const {
    return getElementsListIteratorBegin() == getElementsListIteratorEnd();
  }

  unsigned int ArrayExpression::getElementsSize() const {
    unsigned int size = 0;
    ListIterator<base::Positioned> endIt = getElementsListIteratorEnd();
    for (ListIterator<base::Positioned> it = getElementsListIteratorBegin(); it != endIt; ++it) {
      ++size;
    }
    return size;
  }

  bool ArrayExpression::setEdge(EdgeKind edgeKind, NodeId edgeEnd, bool tryOnVirtualParent) {
    switch (edgeKind) {
      case edkArrayExpression_HasElements:
        addElements(edgeEnd);
        return true;
      default:
        break;
    }
    if (tryOnVirtualParent) {
      if (base::Positioned::setEdge(edgeKind, edgeEnd, false)) {
        return true;
      }
    }
    if (expression::Expression::setEdge(edgeKind, edgeEnd, false)) {
      return true;
    }
    return false;
  }

  bool ArrayExpression::removeEdge(EdgeKind edgeKind, NodeId edgeEnd, bool tryOnVirtualParent) {
    switch (edgeKind) {
      case edkArrayExpression_HasElements:
        removeElements(edgeEnd);
        return true;
      default:
        break;
    }
    if (tryOnVirtualParent) {
      if (base::Positioned::removeEdge(edgeKind, edgeEnd, false)) {
        return true;
      }
    }
    if (expression::Expression::removeEdge(edgeKind, edgeEnd, false)) {
      return true;
    }
    return false;
  }

  void ArrayExpression::addElements(const base::Positioned *_node) {
    if (_node == NULL)
      throw JavascriptException(COLUMBUS_LOCATION, CMSG_EX_THE_NODE_IS_NULL);

    if (&(_node->getFactory()) != this->factory)
      throw JavascriptException(COLUMBUS_LOCATION, CMSG_EX_THE_FACTORY_OF_NODES_DOES_NOT_MATCH);

    if (!((_node->getNodeKind() == ndkSpreadElement)  || Common::getIsExpression(*_node)))
      throw JavascriptException(COLUMBUS_LOCATION, CMSG_EX_INVALID_NODE_KIND);

    hasElementsContainer.push_back(_node->getId());
    setParentEdge(_node,edkArrayExpression_HasElements);

    if (factory->reverseEdges)
      factory->reverseEdges->insertEdge(_node, this, edkArrayExpression_HasElements);
  }

  void ArrayExpression::addElements(NodeId _id) {
    const base::Positioned *node = dynamic_cast<base::Positioned*>(factory->getPointer(_id));
    if (node == NULL)
      throw JavascriptException(COLUMBUS_LOCATION, CMSG_EX_INVALID_NODE_KIND);
    addElements( node );
  }

  void ArrayExpression::removeElements(NodeId id) {
    if (!factory->getExist(id))
      throw JavascriptException(COLUMBUS_LOCATION, CMSG_EX_THE_END_POINT_OF_THE_EDGE_DOES_NOT_EXIST);

    ListIterator<base::Positioned>::Container::iterator it = find(hasElementsContainer.begin(), hasElementsContainer.end(), id);

    if (it == hasElementsContainer.end())
      throw JavascriptException(COLUMBUS_LOCATION, CMSG_EX_THE_END_POINT_OF_THE_EDGE_DOES_NOT_EXIST);

    hasElementsContainer.erase(it);

    removeParentEdge(id);

    if (factory->getExistsReverseEdges())
      factory->reverseEdges->removeEdge(id, this->getId(), edkArrayExpression_HasElements);
  }

  void ArrayExpression::removeElements(base::Positioned *_node) {
    if (_node == NULL)
      throw JavascriptException(COLUMBUS_LOCATION, CMSG_EX_THE_EDGE_IS_NULL);

    removeElements(_node->getId());
  }

  void ArrayExpression::accept(Visitor &visitor) const {
    visitor.visit(*this);
  }

  void ArrayExpression::acceptEnd(Visitor &visitor) const {
    visitor.visitEnd(*this);
  }

  double ArrayExpression::getSimilarity(const base::Base& base){
    if(base.getNodeKind() == getNodeKind()) {
      return 1.0;
    } else {
      return 0.0;
    }
  }

  void ArrayExpression::swapStringTable(RefDistributorStrTable& newStrTable, std::map<Key,Key>& oldAndNewStrKeyMap ){
    std::map<Key,Key>::iterator foundKeyId;

  }

  NodeHashType ArrayExpression::getHash(std::set<NodeId>& travNodes) const {
    if (hashOk) return nodeHashCache;
    common::WriteMsg::write(CMSG_GET_THE_NODE_HASH_OF_NODE_BEGIN,this->getId()); 
    if (travNodes.count(getId())>0) {
      common::WriteMsg::write(CMSG_GET_THE_NODE_HASH_OF_NODE_SKIP);
      return 0;
    }
    travNodes.insert(getId());
    Crc_type resultHash;
    resultHash.process_bytes( "expression::ArrayExpression", strlen("expression::ArrayExpression"));
    common::WriteMsg::write(CMSG_GET_THE_NODE_HASH_OF_NODE_END,resultHash.checksum()); 
    nodeHashCache = resultHash.checksum();
    hashOk = true;
    return nodeHashCache;
  }

  void ArrayExpression::save(io::BinaryIO &binIo,bool withVirtualBase  /*= true*/) const {
    if (withVirtualBase)
      Positioned::save(binIo,false);

    Expression::save(binIo,false);


    for (ListIterator<base::Positioned>::Container::const_iterator it = hasElementsContainer.begin(); it != hasElementsContainer.end(); ++it) {
      binIo.writeUInt4(*it);
    }
    binIo.writeUInt4(0); // This is the end sign
  }

  void ArrayExpression::load(io::BinaryIO &binIo, bool withVirtualBase /*= true*/) {
    if (withVirtualBase)
      Positioned::load(binIo, false);

    Expression::load(binIo,false);

    NodeId _id;

    _id = binIo.readUInt4();
    while (_id) {
      hasElementsContainer.push_back(_id);
      setParentEdge(factory->getPointer(_id),edkArrayExpression_HasElements);
      _id = binIo.readUInt4();
    }
  }


}


}}}
