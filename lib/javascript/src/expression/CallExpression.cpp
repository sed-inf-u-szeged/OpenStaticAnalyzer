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
  CallExpression::CallExpression(NodeId _id, Factory *_factory) :
         Positioned(_id, _factory),
    Expression(_id, _factory),
    m_hasCallee(0),
    hasArgumentsContainer(),
    callsContainer()
  {
  }

  CallExpression::~CallExpression() {
  }

  void CallExpression::prepareDelete(bool tryOnVirtualParent){
    removeCallee();
    while (!hasArgumentsContainer.empty()) {
      const NodeId id = *hasArgumentsContainer.begin();
      removeParentEdge(id);
      if (factory->getExistsReverseEdges())
        factory->reverseEdges->removeEdge(id, this->getId(), edkCallExpression_HasArguments);
      hasArgumentsContainer.pop_front();
    }
    while (!callsContainer.empty()) {
      const NodeId id = *callsContainer.begin();
      if (factory->getExistsReverseEdges())
        factory->reverseEdges->removeEdge(id, this->getId(), edkCallExpression_Calls);
      callsContainer.pop_front();
    }
    if (tryOnVirtualParent) {
      base::Positioned::prepareDelete(false);
    }
    expression::Expression::prepareDelete(false);
  }

  NodeKind CallExpression::getNodeKind() const {
    return ndkCallExpression;
  }

  base::Positioned* CallExpression::getCallee() const {
    base::Positioned *_node = NULL;
    if (m_hasCallee != 0)
      _node = dynamic_cast<base::Positioned*>(factory->getPointer(m_hasCallee));
    if ( (_node == NULL) || factory->getIsFiltered(_node))
      return NULL;

    return _node;
  }

  ListIterator<base::Positioned> CallExpression::getArgumentsListIteratorBegin() const {
    return ListIterator<base::Positioned>(&hasArgumentsContainer, factory, true);
  }

  ListIterator<base::Positioned> CallExpression::getArgumentsListIteratorEnd() const {
    return ListIterator<base::Positioned>(&hasArgumentsContainer, factory, false);
  }

  bool CallExpression::getArgumentsIsEmpty() const {
    return getArgumentsListIteratorBegin() == getArgumentsListIteratorEnd();
  }

  unsigned int CallExpression::getArgumentsSize() const {
    unsigned int size = 0;
    ListIterator<base::Positioned> endIt = getArgumentsListIteratorEnd();
    for (ListIterator<base::Positioned> it = getArgumentsListIteratorBegin(); it != endIt; ++it) {
      ++size;
    }
    return size;
  }

  ListIterator<statement::Function> CallExpression::getCallsListIteratorBegin() const {
    return ListIterator<statement::Function>(&callsContainer, factory, true);
  }

  ListIterator<statement::Function> CallExpression::getCallsListIteratorEnd() const {
    return ListIterator<statement::Function>(&callsContainer, factory, false);
  }

  bool CallExpression::getCallsIsEmpty() const {
    return getCallsListIteratorBegin() == getCallsListIteratorEnd();
  }

  unsigned int CallExpression::getCallsSize() const {
    unsigned int size = 0;
    ListIterator<statement::Function> endIt = getCallsListIteratorEnd();
    for (ListIterator<statement::Function> it = getCallsListIteratorBegin(); it != endIt; ++it) {
      ++size;
    }
    return size;
  }

  bool CallExpression::setEdge(EdgeKind edgeKind, NodeId edgeEnd, bool tryOnVirtualParent) {
    switch (edgeKind) {
      case edkCallExpression_HasCallee:
        setCallee(edgeEnd);
        return true;
      case edkCallExpression_HasArguments:
        addArguments(edgeEnd);
        return true;
      case edkCallExpression_Calls:
        addCalls(edgeEnd);
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

  bool CallExpression::removeEdge(EdgeKind edgeKind, NodeId edgeEnd, bool tryOnVirtualParent) {
    switch (edgeKind) {
      case edkCallExpression_HasCallee:
        removeCallee();
        return true;
      case edkCallExpression_HasArguments:
        removeArguments(edgeEnd);
        return true;
      case edkCallExpression_Calls:
        removeCalls(edgeEnd);
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

  void CallExpression::setCallee(NodeId _id) {
    base::Positioned *_node = NULL;
    if (_id) {
      if (!factory->getExist(_id))
        throw JavascriptException(COLUMBUS_LOCATION, CMSG_EX_THE_END_POINT_OF_THE_EDGE_DOES_NOT_EXIST);

      _node = dynamic_cast<base::Positioned*> (factory->getPointer(_id));
      if ( _node == NULL) {
        throw JavascriptException(COLUMBUS_LOCATION, CMSG_EX_INVALID_NODE_KIND);
      }
      if (&(_node->getFactory()) != this->factory)
        throw JavascriptException(COLUMBUS_LOCATION, CMSG_EX_THE_FACTORY_OF_NODES_DOES_NOT_MATCH );

      if (Common::getIsBaseClassKind(_node->getNodeKind(), ndkExpression) || _node->getNodeKind() == ndkSuper) {
        if (m_hasCallee) {
          removeParentEdge(m_hasCallee);
          if (factory->getExistsReverseEdges())
            factory->reverseEdges->removeEdge(m_hasCallee, m_id, edkCallExpression_HasCallee);
        }
        m_hasCallee = _node->getId();
        if (m_hasCallee != 0)
          setParentEdge(factory->getPointer(m_hasCallee), edkCallExpression_HasCallee);
        if (factory->getExistsReverseEdges())
          factory->reverseEdges->insertEdge(m_hasCallee, this->getId(), edkCallExpression_HasCallee);
      } else {
        throw JavascriptException(COLUMBUS_LOCATION, CMSG_EX_INVALID_NODE_KIND);
      }
    } else {
      if (m_hasCallee) {
        throw JavascriptException(COLUMBUS_LOCATION, CMSG_EX_CAN_T_SET_EDGE_TO_NULL);
      }
    }
  }

  void CallExpression::setCallee(base::Positioned *_node) {
    if (_node == NULL)
      throw JavascriptException(COLUMBUS_LOCATION, CMSG_EX_CAN_T_SET_EDGE_TO_NULL);

    setCallee(_node->getId());
  }

  void CallExpression::removeCallee() {
      if (m_hasCallee) {
        removeParentEdge(m_hasCallee);
        if (factory->getExistsReverseEdges())
          factory->reverseEdges->removeEdge(m_hasCallee, m_id, edkCallExpression_HasCallee);
      }
      m_hasCallee = 0;
  }

  void CallExpression::addArguments(const base::Positioned *_node) {
    if (_node == NULL)
      throw JavascriptException(COLUMBUS_LOCATION, CMSG_EX_THE_NODE_IS_NULL);

    if (&(_node->getFactory()) != this->factory)
      throw JavascriptException(COLUMBUS_LOCATION, CMSG_EX_THE_FACTORY_OF_NODES_DOES_NOT_MATCH);

    if (!(Common::getIsExpression(*_node) || (_node->getNodeKind() == ndkSpreadElement) ))
      throw JavascriptException(COLUMBUS_LOCATION, CMSG_EX_INVALID_NODE_KIND);

    hasArgumentsContainer.push_back(_node->getId());
    setParentEdge(_node,edkCallExpression_HasArguments);

    if (factory->reverseEdges)
      factory->reverseEdges->insertEdge(_node, this, edkCallExpression_HasArguments);
  }

  void CallExpression::addArguments(NodeId _id) {
    const base::Positioned *node = dynamic_cast<base::Positioned*>(factory->getPointer(_id));
    if (node == NULL)
      throw JavascriptException(COLUMBUS_LOCATION, CMSG_EX_INVALID_NODE_KIND);
    addArguments( node );
  }

  void CallExpression::removeArguments(NodeId id) {
    if (!factory->getExist(id))
      throw JavascriptException(COLUMBUS_LOCATION, CMSG_EX_THE_END_POINT_OF_THE_EDGE_DOES_NOT_EXIST);

    ListIterator<base::Positioned>::Container::iterator it = find(hasArgumentsContainer.begin(), hasArgumentsContainer.end(), id);

    if (it == hasArgumentsContainer.end())
      throw JavascriptException(COLUMBUS_LOCATION, CMSG_EX_THE_END_POINT_OF_THE_EDGE_DOES_NOT_EXIST);

    hasArgumentsContainer.erase(it);

    removeParentEdge(id);

    if (factory->getExistsReverseEdges())
      factory->reverseEdges->removeEdge(id, this->getId(), edkCallExpression_HasArguments);
  }

  void CallExpression::removeArguments(base::Positioned *_node) {
    if (_node == NULL)
      throw JavascriptException(COLUMBUS_LOCATION, CMSG_EX_THE_EDGE_IS_NULL);

    removeArguments(_node->getId());
  }

  void CallExpression::addCalls(const statement::Function *_node) {
    if (_node == NULL)
      throw JavascriptException(COLUMBUS_LOCATION, CMSG_EX_THE_NODE_IS_NULL);

    if (&(_node->getFactory()) != this->factory)
      throw JavascriptException(COLUMBUS_LOCATION, CMSG_EX_THE_FACTORY_OF_NODES_DOES_NOT_MATCH);

    if (!(Common::getIsFunction(*_node)))
      throw JavascriptException(COLUMBUS_LOCATION, CMSG_EX_INVALID_NODE_KIND);

    callsContainer.push_back(_node->getId());
    if (factory->reverseEdges)
      factory->reverseEdges->insertEdge(_node, this, edkCallExpression_Calls);
  }

  void CallExpression::addCalls(NodeId _id) {
    const statement::Function *node = dynamic_cast<statement::Function*>(factory->getPointer(_id));
    if (node == NULL)
      throw JavascriptException(COLUMBUS_LOCATION, CMSG_EX_INVALID_NODE_KIND);
    addCalls( node );
  }

  void CallExpression::removeCalls(NodeId id) {
    if (!factory->getExist(id))
      throw JavascriptException(COLUMBUS_LOCATION, CMSG_EX_THE_END_POINT_OF_THE_EDGE_DOES_NOT_EXIST);

    ListIterator<statement::Function>::Container::iterator it = find(callsContainer.begin(), callsContainer.end(), id);

    if (it == callsContainer.end())
      throw JavascriptException(COLUMBUS_LOCATION, CMSG_EX_THE_END_POINT_OF_THE_EDGE_DOES_NOT_EXIST);

    callsContainer.erase(it);

    if (factory->getExistsReverseEdges())
      factory->reverseEdges->removeEdge(id, this->getId(), edkCallExpression_Calls);
  }

  void CallExpression::removeCalls(statement::Function *_node) {
    if (_node == NULL)
      throw JavascriptException(COLUMBUS_LOCATION, CMSG_EX_THE_EDGE_IS_NULL);

    removeCalls(_node->getId());
  }

  void CallExpression::accept(Visitor &visitor) const {
    visitor.visit(*this);
  }

  void CallExpression::acceptEnd(Visitor &visitor) const {
    visitor.visitEnd(*this);
  }

  double CallExpression::getSimilarity(const base::Base& base){
    if(base.getNodeKind() == getNodeKind()) {
      return 1.0;
    } else {
      return 0.0;
    }
  }

  void CallExpression::swapStringTable(RefDistributorStrTable& newStrTable, std::map<Key,Key>& oldAndNewStrKeyMap ){
    std::map<Key,Key>::iterator foundKeyId;

  }

  NodeHashType CallExpression::getHash(std::set<NodeId>& travNodes) const {
    if (hashOk) return nodeHashCache;
    common::WriteMsg::write(CMSG_GET_THE_NODE_HASH_OF_NODE_BEGIN,this->getId()); 
    if (travNodes.count(getId())>0) {
      common::WriteMsg::write(CMSG_GET_THE_NODE_HASH_OF_NODE_SKIP);
      return 0;
    }
    travNodes.insert(getId());
    Crc_type resultHash;
    resultHash.process_bytes( "expression::CallExpression", strlen("expression::CallExpression"));
    common::WriteMsg::write(CMSG_GET_THE_NODE_HASH_OF_NODE_END,resultHash.checksum()); 
    nodeHashCache = resultHash.checksum();
    hashOk = true;
    return nodeHashCache;
  }

  void CallExpression::save(io::BinaryIO &binIo,bool withVirtualBase  /*= true*/) const {
    if (withVirtualBase)
      Positioned::save(binIo,false);

    Expression::save(binIo,false);

    binIo.writeUInt4(m_hasCallee);


    for (ListIterator<base::Positioned>::Container::const_iterator it = hasArgumentsContainer.begin(); it != hasArgumentsContainer.end(); ++it) {
      binIo.writeUInt4(*it);
    }
    binIo.writeUInt4(0); // This is the end sign

    for (ListIterator<statement::Function>::Container::const_iterator it = callsContainer.begin(); it != callsContainer.end(); ++it) {
      binIo.writeUInt4(*it);
    }
    binIo.writeUInt4(0); // This is the end sign
  }

  void CallExpression::load(io::BinaryIO &binIo, bool withVirtualBase /*= true*/) {
    if (withVirtualBase)
      Positioned::load(binIo, false);

    Expression::load(binIo,false);

    m_hasCallee =  binIo.readUInt4();
    if (m_hasCallee != 0)
      setParentEdge(factory->getPointer(m_hasCallee),edkCallExpression_HasCallee);

    NodeId _id;

    _id = binIo.readUInt4();
    while (_id) {
      hasArgumentsContainer.push_back(_id);
      setParentEdge(factory->getPointer(_id),edkCallExpression_HasArguments);
      _id = binIo.readUInt4();
    }

    _id = binIo.readUInt4();
    while (_id) {
      callsContainer.push_back(_id);
      _id = binIo.readUInt4();
    }
  }


}


}}}
