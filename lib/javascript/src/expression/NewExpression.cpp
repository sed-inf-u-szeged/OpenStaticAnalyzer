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
  NewExpression::NewExpression(NodeId _id, Factory *_factory) :
         Positioned(_id, _factory),
    Expression(_id, _factory),
    m_hasCallee(0),
    hasArgumentsContainer()
  {
  }

  NewExpression::~NewExpression() {
  }

  void NewExpression::prepareDelete(bool tryOnVirtualParent){
    removeCallee();
    while (!hasArgumentsContainer.empty()) {
      const NodeId id = *hasArgumentsContainer.begin();
      removeParentEdge(id);
      if (factory->getExistsReverseEdges())
        factory->reverseEdges->removeEdge(id, this->getId(), edkNewExpression_HasArguments);
      hasArgumentsContainer.pop_front();
    }
    if (tryOnVirtualParent) {
      base::Positioned::prepareDelete(false);
    }
    expression::Expression::prepareDelete(false);
  }

  NodeKind NewExpression::getNodeKind() const {
    return ndkNewExpression;
  }

  expression::Expression* NewExpression::getCallee() const {
    expression::Expression *_node = NULL;
    if (m_hasCallee != 0)
      _node = dynamic_cast<expression::Expression*>(factory->getPointer(m_hasCallee));
    if ( (_node == NULL) || factory->getIsFiltered(_node))
      return NULL;

    return _node;
  }

  ListIterator<base::Positioned> NewExpression::getArgumentsListIteratorBegin() const {
    return ListIterator<base::Positioned>(&hasArgumentsContainer, factory, true);
  }

  ListIterator<base::Positioned> NewExpression::getArgumentsListIteratorEnd() const {
    return ListIterator<base::Positioned>(&hasArgumentsContainer, factory, false);
  }

  bool NewExpression::getArgumentsIsEmpty() const {
    return getArgumentsListIteratorBegin() == getArgumentsListIteratorEnd();
  }

  unsigned int NewExpression::getArgumentsSize() const {
    unsigned int size = 0;
    ListIterator<base::Positioned> endIt = getArgumentsListIteratorEnd();
    for (ListIterator<base::Positioned> it = getArgumentsListIteratorBegin(); it != endIt; ++it) {
      ++size;
    }
    return size;
  }

  bool NewExpression::setEdge(EdgeKind edgeKind, NodeId edgeEnd, bool tryOnVirtualParent) {
    switch (edgeKind) {
      case edkNewExpression_HasCallee:
        setCallee(edgeEnd);
        return true;
      case edkNewExpression_HasArguments:
        addArguments(edgeEnd);
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

  bool NewExpression::removeEdge(EdgeKind edgeKind, NodeId edgeEnd, bool tryOnVirtualParent) {
    switch (edgeKind) {
      case edkNewExpression_HasCallee:
        removeCallee();
        return true;
      case edkNewExpression_HasArguments:
        removeArguments(edgeEnd);
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

  void NewExpression::setCallee(NodeId _id) {
    expression::Expression *_node = NULL;
    if (_id) {
      if (!factory->getExist(_id))
        throw JavaScriptException(COLUMBUS_LOCATION, CMSG_EX_THE_END_POINT_OF_THE_EDGE_DOES_NOT_EXIST);

      _node = dynamic_cast<expression::Expression*> (factory->getPointer(_id));
      if ( _node == NULL) {
        throw JavaScriptException(COLUMBUS_LOCATION, CMSG_EX_INVALID_NODE_KIND);
      }
      if (&(_node->getFactory()) != this->factory)
        throw JavaScriptException(COLUMBUS_LOCATION, CMSG_EX_THE_FACTORY_OF_NODES_DOES_NOT_MATCH );

      if (m_hasCallee) {
        removeParentEdge(m_hasCallee);
        if (factory->getExistsReverseEdges())
          factory->reverseEdges->removeEdge(m_hasCallee, m_id, edkNewExpression_HasCallee);
      }
      m_hasCallee = _node->getId();
      if (m_hasCallee != 0)
        setParentEdge(factory->getPointer(m_hasCallee), edkNewExpression_HasCallee);
      if (factory->getExistsReverseEdges())
        factory->reverseEdges->insertEdge(m_hasCallee, this->getId(), edkNewExpression_HasCallee);
    } else {
      if (m_hasCallee) {
        throw JavaScriptException(COLUMBUS_LOCATION, CMSG_EX_CAN_T_SET_EDGE_TO_NULL);
      }
    }
  }

  void NewExpression::setCallee(expression::Expression *_node) {
    if (_node == NULL)
      throw JavaScriptException(COLUMBUS_LOCATION, CMSG_EX_CAN_T_SET_EDGE_TO_NULL);

    setCallee(_node->getId());
  }

  void NewExpression::removeCallee() {
      if (m_hasCallee) {
        removeParentEdge(m_hasCallee);
        if (factory->getExistsReverseEdges())
          factory->reverseEdges->removeEdge(m_hasCallee, m_id, edkNewExpression_HasCallee);
      }
      m_hasCallee = 0;
  }

  void NewExpression::addArguments(const base::Positioned *_node) {
    if (_node == NULL)
      throw JavaScriptException(COLUMBUS_LOCATION, CMSG_EX_THE_NODE_IS_NULL);

    if (&(_node->getFactory()) != this->factory)
      throw JavaScriptException(COLUMBUS_LOCATION, CMSG_EX_THE_FACTORY_OF_NODES_DOES_NOT_MATCH);

    if (!(Common::getIsExpression(*_node) || (_node->getNodeKind() == ndkSpreadElement) ))
      throw JavaScriptException(COLUMBUS_LOCATION, CMSG_EX_INVALID_NODE_KIND);

    hasArgumentsContainer.push_back(_node->getId());
    setParentEdge(_node,edkNewExpression_HasArguments);

    if (factory->reverseEdges)
      factory->reverseEdges->insertEdge(_node, this, edkNewExpression_HasArguments);
  }

  void NewExpression::addArguments(NodeId _id) {
    const base::Positioned *node = dynamic_cast<base::Positioned*>(factory->getPointer(_id));
    if (node == NULL)
      throw JavaScriptException(COLUMBUS_LOCATION, CMSG_EX_INVALID_NODE_KIND);
    addArguments( node );
  }

  void NewExpression::removeArguments(NodeId id) {
    if (!factory->getExist(id))
      throw JavaScriptException(COLUMBUS_LOCATION, CMSG_EX_THE_END_POINT_OF_THE_EDGE_DOES_NOT_EXIST);

    ListIterator<base::Positioned>::Container::iterator it = find(hasArgumentsContainer.begin(), hasArgumentsContainer.end(), id);

    if (it == hasArgumentsContainer.end())
      throw JavaScriptException(COLUMBUS_LOCATION, CMSG_EX_THE_END_POINT_OF_THE_EDGE_DOES_NOT_EXIST);

    hasArgumentsContainer.erase(it);

    removeParentEdge(id);

    if (factory->getExistsReverseEdges())
      factory->reverseEdges->removeEdge(id, this->getId(), edkNewExpression_HasArguments);
  }

  void NewExpression::removeArguments(base::Positioned *_node) {
    if (_node == NULL)
      throw JavaScriptException(COLUMBUS_LOCATION, CMSG_EX_THE_EDGE_IS_NULL);

    removeArguments(_node->getId());
  }

  void NewExpression::accept(Visitor &visitor) const {
    visitor.visit(*this);
  }

  void NewExpression::acceptEnd(Visitor &visitor) const {
    visitor.visitEnd(*this);
  }

  double NewExpression::getSimilarity(const base::Base& base){
    if(base.getNodeKind() == getNodeKind()) {
      return 1.0;
    } else {
      return 0.0;
    }
  }

  void NewExpression::swapStringTable(RefDistributorStrTable& newStrTable, std::map<Key,Key>& oldAndNewStrKeyMap ){
    std::map<Key,Key>::iterator foundKeyId;

  }

  NodeHashType NewExpression::getHash(std::set<NodeId>& travNodes) const {
    if (hashOk) return nodeHashCache;
    common::WriteMsg::write(CMSG_GET_THE_NODE_HASH_OF_NODE_BEGIN,this->getId()); 
    if (travNodes.count(getId())>0) {
      common::WriteMsg::write(CMSG_GET_THE_NODE_HASH_OF_NODE_SKIP);
      return 0;
    }
    travNodes.insert(getId());
    Crc_type resultHash;
    resultHash.process_bytes( "expression::NewExpression", strlen("expression::NewExpression"));
    common::WriteMsg::write(CMSG_GET_THE_NODE_HASH_OF_NODE_END,resultHash.checksum()); 
    nodeHashCache = resultHash.checksum();
    hashOk = true;
    return nodeHashCache;
  }

  void NewExpression::save(io::BinaryIO &binIo,bool withVirtualBase  /*= true*/) const {
    if (withVirtualBase)
      Positioned::save(binIo,false);

    Expression::save(binIo,false);

    binIo.writeUInt4(m_hasCallee);


    for (ListIterator<base::Positioned>::Container::const_iterator it = hasArgumentsContainer.begin(); it != hasArgumentsContainer.end(); ++it) {
      binIo.writeUInt4(*it);
    }
    binIo.writeUInt4(0); // This is the end sign
  }

  void NewExpression::load(io::BinaryIO &binIo, bool withVirtualBase /*= true*/) {
    if (withVirtualBase)
      Positioned::load(binIo, false);

    Expression::load(binIo,false);

    m_hasCallee =  binIo.readUInt4();
    if (m_hasCallee != 0)
      setParentEdge(factory->getPointer(m_hasCallee),edkNewExpression_HasCallee);

    NodeId _id;

    _id = binIo.readUInt4();
    while (_id) {
      hasArgumentsContainer.push_back(_id);
      setParentEdge(factory->getPointer(_id),edkNewExpression_HasArguments);
      _id = binIo.readUInt4();
    }
  }


}


}}}
