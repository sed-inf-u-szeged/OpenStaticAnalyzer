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

#include "lim/inc/lim.h"
#include "lim/inc/Common.h"
#include "common/inc/WriteMessage.h"

#include "lim/inc/messages.h"
#include <algorithm>
#include <string.h>
#include "common/inc/math/common.h"


namespace columbus { namespace lim { namespace asg {

typedef boost::crc_32_type  Crc_type;

namespace logical { 
  Method::Method(NodeId _id, Factory *_factory) :
    Scope(_id, _factory),
    m_isAbstract(false),
    m_isVirtual(false),
    m_nestingLevel(0),
    m_nestingLevelElseIf(0),
    m_distinctOperands(0),
    m_distinctOperators(0),
    m_methodKind(mekAdd),
    m_numberOfBranches(0),
    m_numberOfStatements(0),
    m_totalOperands(0),
    m_totalOperators(0),
    accessesAttributeContainer(),
    callsContainer(),
    canThrowContainer(),
    hasControlFlowBlockContainer(),
    hasParameterContainer(),
    instantiatesContainer(),
    returnsContainer(),
    throwsContainer()
  {
  }

  Method::~Method() {
  }

  void Method::clone(const Method& other, bool tryOnVirtualParent) {
    logical::Scope::clone(other, false);

    m_distinctOperands = other.m_distinctOperands;
    m_distinctOperators = other.m_distinctOperators;
    m_isAbstract = other.m_isAbstract;
    m_isVirtual = other.m_isVirtual;
    m_methodKind = other.m_methodKind;
    m_nestingLevel = other.m_nestingLevel;
    m_nestingLevelElseIf = other.m_nestingLevelElseIf;
    m_numberOfBranches = other.m_numberOfBranches;
    m_numberOfStatements = other.m_numberOfStatements;
    m_totalOperands = other.m_totalOperands;
    m_totalOperators = other.m_totalOperators;
    accessesAttributeContainer = other.accessesAttributeContainer;
    callsContainer = other.callsContainer;
    canThrowContainer = other.canThrowContainer;
    hasControlFlowBlockContainer = other.hasControlFlowBlockContainer;
    hasParameterContainer = other.hasParameterContainer;
    instantiatesContainer = other.instantiatesContainer;
    returnsContainer = other.returnsContainer;
    throwsContainer = other.throwsContainer;
  }

  void Method::prepareDelete(bool tryOnVirtualParent){
    while (!accessesAttributeContainer.empty()) {
      const NodeId id = *accessesAttributeContainer.begin();
      if (factory->getExistsReverseEdges())
        factory->reverseEdges->removeEdge(id, this->getId(), edkMethod_AccessesAttribute);
      accessesAttributeContainer.pop_front();
    }
    while (!callsContainer.empty()) {
      const NodeId id = *callsContainer.begin();
      if (factory->getExistsReverseEdges())
        factory->reverseEdges->removeEdge(id, this->getId(), edkMethod_Calls);
      callsContainer.pop_front();
    }
    while (!canThrowContainer.empty()) {
      const NodeId id = *canThrowContainer.begin();
      if (factory->getExistsReverseEdges())
        factory->reverseEdges->removeEdge(id, this->getId(), edkMethod_CanThrow);
      canThrowContainer.pop_front();
    }
    while (!hasControlFlowBlockContainer.empty()) {
      const NodeId id = *hasControlFlowBlockContainer.begin();
      removeParentEdge(id);
      if (factory->getExistsReverseEdges())
        factory->reverseEdges->removeEdge(id, this->getId(), edkMethod_HasControlFlowBlock);
      hasControlFlowBlockContainer.pop_front();
    }
    while (!hasParameterContainer.empty()) {
      const NodeId id = *hasParameterContainer.begin();
      removeParentEdge(id);
      if (factory->getExistsReverseEdges())
        factory->reverseEdges->removeEdge(id, this->getId(), edkMethod_HasParameter);
      hasParameterContainer.pop_front();
    }
    while (!instantiatesContainer.empty()) {
      const NodeId id = *instantiatesContainer.begin();
      if (factory->getExistsReverseEdges())
        factory->reverseEdges->removeEdge(id, this->getId(), edkMethod_Instantiates);
      instantiatesContainer.pop_front();
    }
    while (!returnsContainer.empty()) {
      const NodeId id = *returnsContainer.begin();
      if (factory->getExistsReverseEdges())
        factory->reverseEdges->removeEdge(id, this->getId(), edkMethod_Returns);
      returnsContainer.pop_front();
    }
    while (!throwsContainer.empty()) {
      const NodeId id = *throwsContainer.begin();
      if (factory->getExistsReverseEdges())
        factory->reverseEdges->removeEdge(id, this->getId(), edkMethod_Throws);
      throwsContainer.pop_front();
    }
    logical::Scope::prepareDelete(false);
  }

  NodeKind Method::getNodeKind() const {
    return ndkMethod;
  }

  unsigned Method::getDistinctOperands() const {
    return m_distinctOperands;
  }

  unsigned Method::getDistinctOperators() const {
    return m_distinctOperators;
  }

  bool Method::getIsAbstract() const {
    return m_isAbstract;
  }

  bool Method::getIsVirtual() const {
    return m_isVirtual;
  }

  MethodKind Method::getMethodKind() const {
    return m_methodKind;
  }

  unsigned short Method::getNestingLevel() const {
    return m_nestingLevel;
  }

  unsigned short Method::getNestingLevelElseIf() const {
    return m_nestingLevelElseIf;
  }

  unsigned Method::getNumberOfBranches() const {
    return m_numberOfBranches;
  }

  unsigned Method::getNumberOfStatements() const {
    return m_numberOfStatements;
  }

  unsigned Method::getTotalOperands() const {
    return m_totalOperands;
  }

  unsigned Method::getTotalOperators() const {
    return m_totalOperators;
  }

  void Method::setDistinctOperands(unsigned _distinctOperands) {
    m_distinctOperands = _distinctOperands;
  }

  void Method::setDistinctOperators(unsigned _distinctOperators) {
    m_distinctOperators = _distinctOperators;
  }

  void Method::setIsAbstract(bool _isAbstract) {
    m_isAbstract = _isAbstract;
  }

  void Method::setIsVirtual(bool _isVirtual) {
    m_isVirtual = _isVirtual;
  }

  void Method::setMethodKind(MethodKind _methodKind) {
    m_methodKind = _methodKind;
  }

  void Method::setNestingLevel(unsigned short _nestingLevel) {
    m_nestingLevel = _nestingLevel;
  }

  void Method::setNestingLevelElseIf(unsigned short _nestingLevelElseIf) {
    m_nestingLevelElseIf = _nestingLevelElseIf;
  }

  void Method::setNumberOfBranches(unsigned _numberOfBranches) {
    m_numberOfBranches = _numberOfBranches;
  }

  void Method::setNumberOfStatements(unsigned _numberOfStatements) {
    m_numberOfStatements = _numberOfStatements;
  }

  void Method::setTotalOperands(unsigned _totalOperands) {
    m_totalOperands = _totalOperands;
  }

  void Method::setTotalOperators(unsigned _totalOperators) {
    m_totalOperators = _totalOperators;
  }

  ListIterator<logical::AttributeAccess> Method::getAccessesAttributeListIteratorBegin() const {
    return ListIterator<logical::AttributeAccess>(&accessesAttributeContainer, factory, true);
  }

  ListIterator<logical::AttributeAccess> Method::getAccessesAttributeListIteratorEnd() const {
    return ListIterator<logical::AttributeAccess>(&accessesAttributeContainer, factory, false);
  }

  bool Method::getAccessesAttributeIsEmpty() const {
    return getAccessesAttributeListIteratorBegin() == getAccessesAttributeListIteratorEnd();
  }

  unsigned int Method::getAccessesAttributeSize() const {
    unsigned int size = 0;
    ListIterator<logical::AttributeAccess> endIt = getAccessesAttributeListIteratorEnd();
    for (ListIterator<logical::AttributeAccess> it = getAccessesAttributeListIteratorBegin(); it != endIt; ++it) {
      ++size;
    }
    return size;
  }

  ListIterator<logical::MethodCall> Method::getCallsListIteratorBegin() const {
    return ListIterator<logical::MethodCall>(&callsContainer, factory, true);
  }

  ListIterator<logical::MethodCall> Method::getCallsListIteratorEnd() const {
    return ListIterator<logical::MethodCall>(&callsContainer, factory, false);
  }

  bool Method::getCallsIsEmpty() const {
    return getCallsListIteratorBegin() == getCallsListIteratorEnd();
  }

  unsigned int Method::getCallsSize() const {
    unsigned int size = 0;
    ListIterator<logical::MethodCall> endIt = getCallsListIteratorEnd();
    for (ListIterator<logical::MethodCall> it = getCallsListIteratorBegin(); it != endIt; ++it) {
      ++size;
    }
    return size;
  }

  ListIterator<type::Type> Method::getCanThrowListIteratorBegin() const {
    return ListIterator<type::Type>(&canThrowContainer, factory, true);
  }

  ListIterator<type::Type> Method::getCanThrowListIteratorEnd() const {
    return ListIterator<type::Type>(&canThrowContainer, factory, false);
  }

  bool Method::getCanThrowIsEmpty() const {
    return getCanThrowListIteratorBegin() == getCanThrowListIteratorEnd();
  }

  unsigned int Method::getCanThrowSize() const {
    unsigned int size = 0;
    ListIterator<type::Type> endIt = getCanThrowListIteratorEnd();
    for (ListIterator<type::Type> it = getCanThrowListIteratorBegin(); it != endIt; ++it) {
      ++size;
    }
    return size;
  }

  ListIterator<base::ControlFlowBlock> Method::getControlFlowBlockListIteratorBegin() const {
    return ListIterator<base::ControlFlowBlock>(&hasControlFlowBlockContainer, factory, true);
  }

  ListIterator<base::ControlFlowBlock> Method::getControlFlowBlockListIteratorEnd() const {
    return ListIterator<base::ControlFlowBlock>(&hasControlFlowBlockContainer, factory, false);
  }

  bool Method::getControlFlowBlockIsEmpty() const {
    return getControlFlowBlockListIteratorBegin() == getControlFlowBlockListIteratorEnd();
  }

  unsigned int Method::getControlFlowBlockSize() const {
    unsigned int size = 0;
    ListIterator<base::ControlFlowBlock> endIt = getControlFlowBlockListIteratorEnd();
    for (ListIterator<base::ControlFlowBlock> it = getControlFlowBlockListIteratorBegin(); it != endIt; ++it) {
      ++size;
    }
    return size;
  }

  ListIterator<logical::Parameter> Method::getParameterListIteratorBegin() const {
    return ListIterator<logical::Parameter>(&hasParameterContainer, factory, true);
  }

  ListIterator<logical::Parameter> Method::getParameterListIteratorEnd() const {
    return ListIterator<logical::Parameter>(&hasParameterContainer, factory, false);
  }

  bool Method::getParameterIsEmpty() const {
    return getParameterListIteratorBegin() == getParameterListIteratorEnd();
  }

  unsigned int Method::getParameterSize() const {
    unsigned int size = 0;
    ListIterator<logical::Parameter> endIt = getParameterListIteratorEnd();
    for (ListIterator<logical::Parameter> it = getParameterListIteratorBegin(); it != endIt; ++it) {
      ++size;
    }
    return size;
  }

  ListIterator<type::Type> Method::getInstantiatesListIteratorBegin() const {
    return ListIterator<type::Type>(&instantiatesContainer, factory, true);
  }

  ListIterator<type::Type> Method::getInstantiatesListIteratorEnd() const {
    return ListIterator<type::Type>(&instantiatesContainer, factory, false);
  }

  bool Method::getInstantiatesIsEmpty() const {
    return getInstantiatesListIteratorBegin() == getInstantiatesListIteratorEnd();
  }

  unsigned int Method::getInstantiatesSize() const {
    unsigned int size = 0;
    ListIterator<type::Type> endIt = getInstantiatesListIteratorEnd();
    for (ListIterator<type::Type> it = getInstantiatesListIteratorBegin(); it != endIt; ++it) {
      ++size;
    }
    return size;
  }

  ListIterator<type::Type> Method::getReturnsListIteratorBegin() const {
    return ListIterator<type::Type>(&returnsContainer, factory, true);
  }

  ListIterator<type::Type> Method::getReturnsListIteratorEnd() const {
    return ListIterator<type::Type>(&returnsContainer, factory, false);
  }

  bool Method::getReturnsIsEmpty() const {
    return getReturnsListIteratorBegin() == getReturnsListIteratorEnd();
  }

  unsigned int Method::getReturnsSize() const {
    unsigned int size = 0;
    ListIterator<type::Type> endIt = getReturnsListIteratorEnd();
    for (ListIterator<type::Type> it = getReturnsListIteratorBegin(); it != endIt; ++it) {
      ++size;
    }
    return size;
  }

  ListIterator<type::Type> Method::getThrowsListIteratorBegin() const {
    return ListIterator<type::Type>(&throwsContainer, factory, true);
  }

  ListIterator<type::Type> Method::getThrowsListIteratorEnd() const {
    return ListIterator<type::Type>(&throwsContainer, factory, false);
  }

  bool Method::getThrowsIsEmpty() const {
    return getThrowsListIteratorBegin() == getThrowsListIteratorEnd();
  }

  unsigned int Method::getThrowsSize() const {
    unsigned int size = 0;
    ListIterator<type::Type> endIt = getThrowsListIteratorEnd();
    for (ListIterator<type::Type> it = getThrowsListIteratorBegin(); it != endIt; ++it) {
      ++size;
    }
    return size;
  }

  bool Method::setEdge(EdgeKind edgeKind, NodeId edgeEnd, void* acValue, bool tryOnVirtualParent) {
    switch (edgeKind) {
      case edkMethod_AccessesAttribute:
        addAccessesAttribute(edgeEnd);
        return true;
      case edkMethod_Calls:
        addCalls(edgeEnd);
        return true;
      case edkMethod_CanThrow:
        addCanThrow(edgeEnd);
        return true;
      case edkMethod_HasControlFlowBlock:
        addControlFlowBlock(edgeEnd);
        return true;
      case edkMethod_HasParameter:
        addParameter(edgeEnd);
        return true;
      case edkMethod_Instantiates:
        addInstantiates(edgeEnd);
        return true;
      case edkMethod_Returns:
        addReturns(edgeEnd);
        return true;
      case edkMethod_Throws:
        addThrows(edgeEnd);
        return true;
      default:
        break;
    }
    if (logical::Scope::setEdge(edgeKind, edgeEnd, acValue, false)) {
      return true;
    }
    return false;
  }

  bool Method::removeEdge(EdgeKind edgeKind, NodeId edgeEnd, bool tryOnVirtualParent) {
    switch (edgeKind) {
      case edkMethod_AccessesAttribute:
        removeAccessesAttribute(edgeEnd);
        return true;
      case edkMethod_Calls:
        removeCalls(edgeEnd);
        return true;
      case edkMethod_CanThrow:
        removeCanThrow(edgeEnd);
        return true;
      case edkMethod_HasControlFlowBlock:
        removeControlFlowBlock(edgeEnd);
        return true;
      case edkMethod_HasParameter:
        removeParameter(edgeEnd);
        return true;
      case edkMethod_Instantiates:
        removeInstantiates(edgeEnd);
        return true;
      case edkMethod_Returns:
        removeReturns(edgeEnd);
        return true;
      case edkMethod_Throws:
        removeThrows(edgeEnd);
        return true;
      default:
        break;
    }
    if (logical::Scope::removeEdge(edgeKind, edgeEnd, false)) {
      return true;
    }
    return false;
  }

  void Method::addAccessesAttribute(const logical::AttributeAccess *_node) {
    if (_node == NULL)
      throw LimException(COLUMBUS_LOCATION, CMSG_EX_THE_NODE_IS_NULL);

    if (&(_node->getFactory()) != this->factory)
      throw LimException(COLUMBUS_LOCATION, CMSG_EX_THE_FACTORY_OF_NODES_DOES_NOT_MATCH);

    if (!((_node->getNodeKind() == ndkAttributeAccess) ))
      throw LimException(COLUMBUS_LOCATION, CMSG_EX_INVALID_NODE_KIND);

    accessesAttributeContainer.push_back(_node->getId());
    if (factory->reverseEdges)
      factory->reverseEdges->insertEdge(_node, this, edkMethod_AccessesAttribute);
  }

  void Method::addAccessesAttribute(NodeId _id) {
    const logical::AttributeAccess *node = dynamic_cast<logical::AttributeAccess*>(factory->getPointer(_id));
    if (node == NULL)
      throw LimException(COLUMBUS_LOCATION, CMSG_EX_INVALID_NODE_KIND);
    addAccessesAttribute( node );
  }

  void Method::removeAccessesAttribute(NodeId id) {
    if (!factory->getExist(id))
      throw LimException(COLUMBUS_LOCATION, CMSG_EX_THE_END_POINT_OF_THE_EDGE_DOES_NOT_EXIST);

    ListIterator<logical::AttributeAccess>::Container::iterator it = find(accessesAttributeContainer.begin(), accessesAttributeContainer.end(), id);

    if (it == accessesAttributeContainer.end())
      throw LimException(COLUMBUS_LOCATION, CMSG_EX_THE_END_POINT_OF_THE_EDGE_DOES_NOT_EXIST);

    accessesAttributeContainer.erase(it);

    if (factory->getExistsReverseEdges())
      factory->reverseEdges->removeEdge(id, this->getId(), edkMethod_AccessesAttribute);
  }

  void Method::removeAccessesAttribute(logical::AttributeAccess *_node) {
    if (_node == NULL)
      throw LimException(COLUMBUS_LOCATION, CMSG_EX_THE_EDGE_IS_NULL);

    removeAccessesAttribute(_node->getId());
  }

  void Method::addCalls(const logical::MethodCall *_node) {
    if (_node == NULL)
      throw LimException(COLUMBUS_LOCATION, CMSG_EX_THE_NODE_IS_NULL);

    if (&(_node->getFactory()) != this->factory)
      throw LimException(COLUMBUS_LOCATION, CMSG_EX_THE_FACTORY_OF_NODES_DOES_NOT_MATCH);

    if (!((_node->getNodeKind() == ndkMethodCall) ))
      throw LimException(COLUMBUS_LOCATION, CMSG_EX_INVALID_NODE_KIND);

    callsContainer.push_back(_node->getId());
    if (factory->reverseEdges)
      factory->reverseEdges->insertEdge(_node, this, edkMethod_Calls);
  }

  void Method::addCalls(NodeId _id) {
    const logical::MethodCall *node = dynamic_cast<logical::MethodCall*>(factory->getPointer(_id));
    if (node == NULL)
      throw LimException(COLUMBUS_LOCATION, CMSG_EX_INVALID_NODE_KIND);
    addCalls( node );
  }

  void Method::removeCalls(NodeId id) {
    if (!factory->getExist(id))
      throw LimException(COLUMBUS_LOCATION, CMSG_EX_THE_END_POINT_OF_THE_EDGE_DOES_NOT_EXIST);

    ListIterator<logical::MethodCall>::Container::iterator it = find(callsContainer.begin(), callsContainer.end(), id);

    if (it == callsContainer.end())
      throw LimException(COLUMBUS_LOCATION, CMSG_EX_THE_END_POINT_OF_THE_EDGE_DOES_NOT_EXIST);

    callsContainer.erase(it);

    if (factory->getExistsReverseEdges())
      factory->reverseEdges->removeEdge(id, this->getId(), edkMethod_Calls);
  }

  void Method::removeCalls(logical::MethodCall *_node) {
    if (_node == NULL)
      throw LimException(COLUMBUS_LOCATION, CMSG_EX_THE_EDGE_IS_NULL);

    removeCalls(_node->getId());
  }

  void Method::addCanThrow(const type::Type *_node) {
    if (_node == NULL)
      throw LimException(COLUMBUS_LOCATION, CMSG_EX_THE_NODE_IS_NULL);

    if (&(_node->getFactory()) != this->factory)
      throw LimException(COLUMBUS_LOCATION, CMSG_EX_THE_FACTORY_OF_NODES_DOES_NOT_MATCH);

    if (!((_node->getNodeKind() == ndkType) ))
      throw LimException(COLUMBUS_LOCATION, CMSG_EX_INVALID_NODE_KIND);

    canThrowContainer.push_back(_node->getId());
    if (factory->reverseEdges)
      factory->reverseEdges->insertEdge(_node, this, edkMethod_CanThrow);
  }

  void Method::addCanThrow(NodeId _id) {
    const type::Type *node = dynamic_cast<type::Type*>(factory->getPointer(_id));
    if (node == NULL)
      throw LimException(COLUMBUS_LOCATION, CMSG_EX_INVALID_NODE_KIND);
    addCanThrow( node );
  }

  void Method::removeCanThrow(NodeId id) {
    if (!factory->getExist(id))
      throw LimException(COLUMBUS_LOCATION, CMSG_EX_THE_END_POINT_OF_THE_EDGE_DOES_NOT_EXIST);

    ListIterator<type::Type>::Container::iterator it = find(canThrowContainer.begin(), canThrowContainer.end(), id);

    if (it == canThrowContainer.end())
      throw LimException(COLUMBUS_LOCATION, CMSG_EX_THE_END_POINT_OF_THE_EDGE_DOES_NOT_EXIST);

    canThrowContainer.erase(it);

    if (factory->getExistsReverseEdges())
      factory->reverseEdges->removeEdge(id, this->getId(), edkMethod_CanThrow);
  }

  void Method::removeCanThrow(type::Type *_node) {
    if (_node == NULL)
      throw LimException(COLUMBUS_LOCATION, CMSG_EX_THE_EDGE_IS_NULL);

    removeCanThrow(_node->getId());
  }

  void Method::addControlFlowBlock(const base::ControlFlowBlock *_node) {
    if (_node == NULL)
      throw LimException(COLUMBUS_LOCATION, CMSG_EX_THE_NODE_IS_NULL);

    if (&(_node->getFactory()) != this->factory)
      throw LimException(COLUMBUS_LOCATION, CMSG_EX_THE_FACTORY_OF_NODES_DOES_NOT_MATCH);

    if (!((_node->getNodeKind() == ndkControlFlowBlock) ))
      throw LimException(COLUMBUS_LOCATION, CMSG_EX_INVALID_NODE_KIND);

    hasControlFlowBlockContainer.push_back(_node->getId());
    setParentEdge(_node,edkMethod_HasControlFlowBlock);

    if (factory->reverseEdges)
      factory->reverseEdges->insertEdge(_node, this, edkMethod_HasControlFlowBlock);
  }

  void Method::addControlFlowBlock(NodeId _id) {
    const base::ControlFlowBlock *node = dynamic_cast<base::ControlFlowBlock*>(factory->getPointer(_id));
    if (node == NULL)
      throw LimException(COLUMBUS_LOCATION, CMSG_EX_INVALID_NODE_KIND);
    addControlFlowBlock( node );
  }

  void Method::removeControlFlowBlock(NodeId id) {
    if (!factory->getExist(id))
      throw LimException(COLUMBUS_LOCATION, CMSG_EX_THE_END_POINT_OF_THE_EDGE_DOES_NOT_EXIST);

    ListIterator<base::ControlFlowBlock>::Container::iterator it = find(hasControlFlowBlockContainer.begin(), hasControlFlowBlockContainer.end(), id);

    if (it == hasControlFlowBlockContainer.end())
      throw LimException(COLUMBUS_LOCATION, CMSG_EX_THE_END_POINT_OF_THE_EDGE_DOES_NOT_EXIST);

    hasControlFlowBlockContainer.erase(it);

    removeParentEdge(id);

    if (factory->getExistsReverseEdges())
      factory->reverseEdges->removeEdge(id, this->getId(), edkMethod_HasControlFlowBlock);
  }

  void Method::removeControlFlowBlock(base::ControlFlowBlock *_node) {
    if (_node == NULL)
      throw LimException(COLUMBUS_LOCATION, CMSG_EX_THE_EDGE_IS_NULL);

    removeControlFlowBlock(_node->getId());
  }

  void Method::addParameter(const logical::Parameter *_node) {
    if (_node == NULL)
      throw LimException(COLUMBUS_LOCATION, CMSG_EX_THE_NODE_IS_NULL);

    if (&(_node->getFactory()) != this->factory)
      throw LimException(COLUMBUS_LOCATION, CMSG_EX_THE_FACTORY_OF_NODES_DOES_NOT_MATCH);

    if (!((_node->getNodeKind() == ndkParameter) ))
      throw LimException(COLUMBUS_LOCATION, CMSG_EX_INVALID_NODE_KIND);

    hasParameterContainer.push_back(_node->getId());
    setParentEdge(_node,edkMethod_HasParameter);

    if (factory->reverseEdges)
      factory->reverseEdges->insertEdge(_node, this, edkMethod_HasParameter);
  }

  void Method::addParameter(NodeId _id) {
    const logical::Parameter *node = dynamic_cast<logical::Parameter*>(factory->getPointer(_id));
    if (node == NULL)
      throw LimException(COLUMBUS_LOCATION, CMSG_EX_INVALID_NODE_KIND);
    addParameter( node );
  }

  void Method::removeParameter(NodeId id) {
    if (!factory->getExist(id))
      throw LimException(COLUMBUS_LOCATION, CMSG_EX_THE_END_POINT_OF_THE_EDGE_DOES_NOT_EXIST);

    ListIterator<logical::Parameter>::Container::iterator it = find(hasParameterContainer.begin(), hasParameterContainer.end(), id);

    if (it == hasParameterContainer.end())
      throw LimException(COLUMBUS_LOCATION, CMSG_EX_THE_END_POINT_OF_THE_EDGE_DOES_NOT_EXIST);

    hasParameterContainer.erase(it);

    removeParentEdge(id);

    if (factory->getExistsReverseEdges())
      factory->reverseEdges->removeEdge(id, this->getId(), edkMethod_HasParameter);
  }

  void Method::removeParameter(logical::Parameter *_node) {
    if (_node == NULL)
      throw LimException(COLUMBUS_LOCATION, CMSG_EX_THE_EDGE_IS_NULL);

    removeParameter(_node->getId());
  }

  void Method::addInstantiates(const type::Type *_node) {
    if (_node == NULL)
      throw LimException(COLUMBUS_LOCATION, CMSG_EX_THE_NODE_IS_NULL);

    if (&(_node->getFactory()) != this->factory)
      throw LimException(COLUMBUS_LOCATION, CMSG_EX_THE_FACTORY_OF_NODES_DOES_NOT_MATCH);

    if (!((_node->getNodeKind() == ndkType) ))
      throw LimException(COLUMBUS_LOCATION, CMSG_EX_INVALID_NODE_KIND);

    instantiatesContainer.push_back(_node->getId());
    if (factory->reverseEdges)
      factory->reverseEdges->insertEdge(_node, this, edkMethod_Instantiates);
  }

  void Method::addInstantiates(NodeId _id) {
    const type::Type *node = dynamic_cast<type::Type*>(factory->getPointer(_id));
    if (node == NULL)
      throw LimException(COLUMBUS_LOCATION, CMSG_EX_INVALID_NODE_KIND);
    addInstantiates( node );
  }

  void Method::removeInstantiates(NodeId id) {
    if (!factory->getExist(id))
      throw LimException(COLUMBUS_LOCATION, CMSG_EX_THE_END_POINT_OF_THE_EDGE_DOES_NOT_EXIST);

    ListIterator<type::Type>::Container::iterator it = find(instantiatesContainer.begin(), instantiatesContainer.end(), id);

    if (it == instantiatesContainer.end())
      throw LimException(COLUMBUS_LOCATION, CMSG_EX_THE_END_POINT_OF_THE_EDGE_DOES_NOT_EXIST);

    instantiatesContainer.erase(it);

    if (factory->getExistsReverseEdges())
      factory->reverseEdges->removeEdge(id, this->getId(), edkMethod_Instantiates);
  }

  void Method::removeInstantiates(type::Type *_node) {
    if (_node == NULL)
      throw LimException(COLUMBUS_LOCATION, CMSG_EX_THE_EDGE_IS_NULL);

    removeInstantiates(_node->getId());
  }

  void Method::addReturns(const type::Type *_node) {
    if (_node == NULL)
      throw LimException(COLUMBUS_LOCATION, CMSG_EX_THE_NODE_IS_NULL);

    if (&(_node->getFactory()) != this->factory)
      throw LimException(COLUMBUS_LOCATION, CMSG_EX_THE_FACTORY_OF_NODES_DOES_NOT_MATCH);

    if (!((_node->getNodeKind() == ndkType) ))
      throw LimException(COLUMBUS_LOCATION, CMSG_EX_INVALID_NODE_KIND);

    returnsContainer.push_back(_node->getId());
    if (factory->reverseEdges)
      factory->reverseEdges->insertEdge(_node, this, edkMethod_Returns);
  }

  void Method::addReturns(NodeId _id) {
    const type::Type *node = dynamic_cast<type::Type*>(factory->getPointer(_id));
    if (node == NULL)
      throw LimException(COLUMBUS_LOCATION, CMSG_EX_INVALID_NODE_KIND);
    addReturns( node );
  }

  void Method::removeReturns(NodeId id) {
    if (!factory->getExist(id))
      throw LimException(COLUMBUS_LOCATION, CMSG_EX_THE_END_POINT_OF_THE_EDGE_DOES_NOT_EXIST);

    ListIterator<type::Type>::Container::iterator it = find(returnsContainer.begin(), returnsContainer.end(), id);

    if (it == returnsContainer.end())
      throw LimException(COLUMBUS_LOCATION, CMSG_EX_THE_END_POINT_OF_THE_EDGE_DOES_NOT_EXIST);

    returnsContainer.erase(it);

    if (factory->getExistsReverseEdges())
      factory->reverseEdges->removeEdge(id, this->getId(), edkMethod_Returns);
  }

  void Method::removeReturns(type::Type *_node) {
    if (_node == NULL)
      throw LimException(COLUMBUS_LOCATION, CMSG_EX_THE_EDGE_IS_NULL);

    removeReturns(_node->getId());
  }

  void Method::addThrows(const type::Type *_node) {
    if (_node == NULL)
      throw LimException(COLUMBUS_LOCATION, CMSG_EX_THE_NODE_IS_NULL);

    if (&(_node->getFactory()) != this->factory)
      throw LimException(COLUMBUS_LOCATION, CMSG_EX_THE_FACTORY_OF_NODES_DOES_NOT_MATCH);

    if (!((_node->getNodeKind() == ndkType) ))
      throw LimException(COLUMBUS_LOCATION, CMSG_EX_INVALID_NODE_KIND);

    throwsContainer.push_back(_node->getId());
    if (factory->reverseEdges)
      factory->reverseEdges->insertEdge(_node, this, edkMethod_Throws);
  }

  void Method::addThrows(NodeId _id) {
    const type::Type *node = dynamic_cast<type::Type*>(factory->getPointer(_id));
    if (node == NULL)
      throw LimException(COLUMBUS_LOCATION, CMSG_EX_INVALID_NODE_KIND);
    addThrows( node );
  }

  void Method::removeThrows(NodeId id) {
    if (!factory->getExist(id))
      throw LimException(COLUMBUS_LOCATION, CMSG_EX_THE_END_POINT_OF_THE_EDGE_DOES_NOT_EXIST);

    ListIterator<type::Type>::Container::iterator it = find(throwsContainer.begin(), throwsContainer.end(), id);

    if (it == throwsContainer.end())
      throw LimException(COLUMBUS_LOCATION, CMSG_EX_THE_END_POINT_OF_THE_EDGE_DOES_NOT_EXIST);

    throwsContainer.erase(it);

    if (factory->getExistsReverseEdges())
      factory->reverseEdges->removeEdge(id, this->getId(), edkMethod_Throws);
  }

  void Method::removeThrows(type::Type *_node) {
    if (_node == NULL)
      throw LimException(COLUMBUS_LOCATION, CMSG_EX_THE_EDGE_IS_NULL);

    removeThrows(_node->getId());
  }

  void Method::accept(Visitor &visitor) const {
    visitor.visit(*this);
  }

  void Method::acceptEnd(Visitor &visitor) const {
    visitor.visitEnd(*this);
  }

  double Method::getSimilarity(const base::Base& base){
    if(base.getNodeKind() == getNodeKind()) {
      const Method& node = dynamic_cast<const Method&>(base);
      double matchAttrs = 0;
      std::string str1, str2;
      size_t strMax;
      double strSim;
      str1 = getName();
      str2 = node.getName();
      strMax = std::max(str1.size(), str2.size());
      strSim = 1 - ((double)common::math::editDistance(str1, str2) / (strMax > 0 ? strMax : 1));
      if (strSim < Common::SimilarityMinForStrings)
        return 0.0;
      matchAttrs += strSim;
      if(node.getAccessibility() == getAccessibility()) ++matchAttrs;
      if(node.getCommentLines() == getCommentLines()) ++matchAttrs;
      str1 = getDemangledName();
      str2 = node.getDemangledName();
      strMax = std::max(str1.size(), str2.size());
      strSim = 1 - ((double)common::math::editDistance(str1, str2) / (strMax > 0 ? strMax : 1));
      if (strSim < Common::SimilarityMinForStrings)
        return 0.0;
      matchAttrs += strSim;
      if(node.getIsCompilerGenerated() == getIsCompilerGenerated()) ++matchAttrs;
      if(node.getIsStatic() == getIsStatic()) ++matchAttrs;
      if(node.getLanguage() == getLanguage()) ++matchAttrs;
      str1 = getMangledName();
      str2 = node.getMangledName();
      strMax = std::max(str1.size(), str2.size());
      strSim = 1 - ((double)common::math::editDistance(str1, str2) / (strMax > 0 ? strMax : 1));
      if (strSim < Common::SimilarityMinForStrings)
        return 0.0;
      matchAttrs += strSim;
      if(node.getLLOC() == getLLOC()) ++matchAttrs;
      if(node.getLOC() == getLOC()) ++matchAttrs;
      if(node.getTLLOC() == getTLLOC()) ++matchAttrs;
      if(node.getTLOC() == getTLOC()) ++matchAttrs;
      if(node.getIsAnonymous() == getIsAnonymous()) ++matchAttrs;
      if(node.getDistinctOperands() == getDistinctOperands()) ++matchAttrs;
      if(node.getDistinctOperators() == getDistinctOperators()) ++matchAttrs;
      if(node.getIsAbstract() == getIsAbstract()) ++matchAttrs;
      if(node.getIsVirtual() == getIsVirtual()) ++matchAttrs;
      if(node.getMethodKind() == getMethodKind()) ++matchAttrs;
      if(node.getNestingLevel() == getNestingLevel()) ++matchAttrs;
      if(node.getNestingLevelElseIf() == getNestingLevelElseIf()) ++matchAttrs;
      if(node.getNumberOfBranches() == getNumberOfBranches()) ++matchAttrs;
      if(node.getNumberOfStatements() == getNumberOfStatements()) ++matchAttrs;
      if(node.getTotalOperands() == getTotalOperands()) ++matchAttrs;
      if(node.getTotalOperators() == getTotalOperators()) ++matchAttrs;
      return matchAttrs / (24 / (1 - Common::SimilarityMinimum)) + Common::SimilarityMinimum;
    } else {
      return 0.0;
    }
  }

  void Method::swapStringTable(RefDistributorStrTable& newStrTable, std::map<Key,Key>& oldAndNewStrKeyMap ){
    std::map<Key,Key>::iterator foundKeyId;

    foundKeyId = oldAndNewStrKeyMap.find(m_demangledName);
    if (foundKeyId != oldAndNewStrKeyMap.end()) {
      m_demangledName = foundKeyId->second;
    } else {
      Key oldkey = m_demangledName;
      m_demangledName = newStrTable.set(factory->getStringTable().get(m_demangledName));
      oldAndNewStrKeyMap.insert(std::pair<Key,Key>(oldkey,m_demangledName));    }

    foundKeyId = oldAndNewStrKeyMap.find(m_mangledName);
    if (foundKeyId != oldAndNewStrKeyMap.end()) {
      m_mangledName = foundKeyId->second;
    } else {
      Key oldkey = m_mangledName;
      m_mangledName = newStrTable.set(factory->getStringTable().get(m_mangledName));
      oldAndNewStrKeyMap.insert(std::pair<Key,Key>(oldkey,m_mangledName));    }

    foundKeyId = oldAndNewStrKeyMap.find(m_name);
    if (foundKeyId != oldAndNewStrKeyMap.end()) {
      m_name = foundKeyId->second;
    } else {
      Key oldkey = m_name;
      m_name = newStrTable.set(factory->getStringTable().get(m_name));
      oldAndNewStrKeyMap.insert(std::pair<Key,Key>(oldkey,m_name));    }

  }

  NodeHashType Method::getHash(std::set<NodeId>& travNodes) const {
    if (hashOk) return nodeHashCache;
    common::WriteMsg::write(CMSG_GET_THE_NODE_HASH_OF_NODE_BEGIN,this->getId()); 
    if (travNodes.count(getId())>0) {
      common::WriteMsg::write(CMSG_GET_THE_NODE_HASH_OF_NODE_SKIP);
      return 0;
    }
    travNodes.insert(getId());
    Crc_type resultHash;
    resultHash.process_bytes( "logical::Method", strlen("logical::Method"));
    common::WriteMsg::write(CMSG_GET_THE_NODE_HASH_OF_NODE_END,resultHash.checksum()); 
    nodeHashCache = resultHash.checksum();
    hashOk = true;
    return nodeHashCache;
  }

  void Method::save(io::BinaryIO &binIo,bool withVirtualBase  /*= true*/) const {
    Scope::save(binIo,false);

    unsigned char boolValues = 0;
    boolValues <<= 1;
    if (m_isAbstract) 
      boolValues |= 1;
    boolValues <<= 1;
    if (m_isVirtual) 
      boolValues |= 1;
    binIo.writeUByte1(boolValues);
    binIo.writeUInt4(m_distinctOperands);
    binIo.writeUInt4(m_distinctOperators);
    binIo.writeUByte1(m_methodKind);
    binIo.writeUShort2(m_nestingLevel);
    binIo.writeUShort2(m_nestingLevelElseIf);
    binIo.writeUInt4(m_numberOfBranches);
    binIo.writeUInt4(m_numberOfStatements);
    binIo.writeUInt4(m_totalOperands);
    binIo.writeUInt4(m_totalOperators);


    for (ListIterator<logical::AttributeAccess>::Container::const_iterator it = accessesAttributeContainer.begin(); it != accessesAttributeContainer.end(); ++it) {
      binIo.writeUInt4(*it);
    }
    binIo.writeUInt4(0); // This is the end sign

    for (ListIterator<logical::MethodCall>::Container::const_iterator it = callsContainer.begin(); it != callsContainer.end(); ++it) {
      binIo.writeUInt4(*it);
    }
    binIo.writeUInt4(0); // This is the end sign

    for (ListIterator<type::Type>::Container::const_iterator it = canThrowContainer.begin(); it != canThrowContainer.end(); ++it) {
      binIo.writeUInt4(*it);
    }
    binIo.writeUInt4(0); // This is the end sign

    for (ListIterator<base::ControlFlowBlock>::Container::const_iterator it = hasControlFlowBlockContainer.begin(); it != hasControlFlowBlockContainer.end(); ++it) {
      binIo.writeUInt4(*it);
    }
    binIo.writeUInt4(0); // This is the end sign

    for (ListIterator<logical::Parameter>::Container::const_iterator it = hasParameterContainer.begin(); it != hasParameterContainer.end(); ++it) {
      binIo.writeUInt4(*it);
    }
    binIo.writeUInt4(0); // This is the end sign

    for (ListIterator<type::Type>::Container::const_iterator it = instantiatesContainer.begin(); it != instantiatesContainer.end(); ++it) {
      binIo.writeUInt4(*it);
    }
    binIo.writeUInt4(0); // This is the end sign

    for (ListIterator<type::Type>::Container::const_iterator it = returnsContainer.begin(); it != returnsContainer.end(); ++it) {
      binIo.writeUInt4(*it);
    }
    binIo.writeUInt4(0); // This is the end sign

    for (ListIterator<type::Type>::Container::const_iterator it = throwsContainer.begin(); it != throwsContainer.end(); ++it) {
      binIo.writeUInt4(*it);
    }
    binIo.writeUInt4(0); // This is the end sign
  }

  void Method::load(io::BinaryIO &binIo, bool withVirtualBase /*= true*/) {
    Scope::load(binIo,false);

    unsigned char boolValues = binIo.readUByte1();
    m_isVirtual = boolValues & 1;
    boolValues >>= 1;
    m_isAbstract = boolValues & 1;
    boolValues >>= 1;
    m_distinctOperands = binIo.readUInt4();
    m_distinctOperators = binIo.readUInt4();
    m_methodKind = (MethodKind)binIo.readUByte1();
    m_nestingLevel = binIo.readUShort2();
    m_nestingLevelElseIf = binIo.readUShort2();
    m_numberOfBranches = binIo.readUInt4();
    m_numberOfStatements = binIo.readUInt4();
    m_totalOperands = binIo.readUInt4();
    m_totalOperators = binIo.readUInt4();

    NodeId _id;

    _id = binIo.readUInt4();
    while (_id) {
      accessesAttributeContainer.push_back(_id);
      _id = binIo.readUInt4();
    }

    _id = binIo.readUInt4();
    while (_id) {
      callsContainer.push_back(_id);
      _id = binIo.readUInt4();
    }

    _id = binIo.readUInt4();
    while (_id) {
      canThrowContainer.push_back(_id);
      _id = binIo.readUInt4();
    }

    _id = binIo.readUInt4();
    while (_id) {
      hasControlFlowBlockContainer.push_back(_id);
      setParentEdge(factory->getPointer(_id),edkMethod_HasControlFlowBlock);
      _id = binIo.readUInt4();
    }

    _id = binIo.readUInt4();
    while (_id) {
      hasParameterContainer.push_back(_id);
      setParentEdge(factory->getPointer(_id),edkMethod_HasParameter);
      _id = binIo.readUInt4();
    }

    _id = binIo.readUInt4();
    while (_id) {
      instantiatesContainer.push_back(_id);
      _id = binIo.readUInt4();
    }

    _id = binIo.readUInt4();
    while (_id) {
      returnsContainer.push_back(_id);
      _id = binIo.readUInt4();
    }

    _id = binIo.readUInt4();
    while (_id) {
      throwsContainer.push_back(_id);
      _id = binIo.readUInt4();
    }
  }


}


}}}
