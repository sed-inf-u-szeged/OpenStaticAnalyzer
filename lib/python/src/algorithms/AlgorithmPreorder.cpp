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
#include "common/inc/WriteMessage.h"
#include "python/inc/messages.h"
#include <string.h>

#ifdef DEBUG_PREORDER
#include <iostream>
#endif


namespace columbus { namespace python { namespace asg {
AlgorithmPreorder::AlgorithmPreorder()
  : Algorithm(),
  safeMode(false),
  visitedNodes(),
  unvisitedNodes(),
  visitCrossEdgeTree(false),
  needPreorderStop(false),
  visitSpecialNodes(true),
  visitUsedSpecialNodesOnly(false),
  visitFilteredEdge(false),
  originalFilterState(false),
  apRoot(NULL),
  visitorList(false),
  fact(NULL),
  traversaldCrossEdges()
{
  memset(traversaldCrossEdges,false,sizeof(bool)*102);
}

AlgorithmPreorder::~AlgorithmPreorder() {
}

void AlgorithmPreorder::setSafeMode() {
  safeMode = true;
}

void AlgorithmPreorder::setUnsafeMode() {
  safeMode = false;
}

void AlgorithmPreorder::setVisitCrossEdgeTree(bool visit) {
  visitCrossEdgeTree = visit;
}

void AlgorithmPreorder::setVisitFilteredEdges(bool visit) {
  visitFilteredEdge = visit;
}

void AlgorithmPreorder::setVisitSpecialNodes(bool visit, bool usedOnly) {
  visitSpecialNodes = visit;
  visitUsedSpecialNodesOnly = visit && usedOnly;
}

void AlgorithmPreorder::run() {
  mainRun(NULL, NULL, NULL);
}

void AlgorithmPreorder::run(const base::Base& node) {
  mainRun(NULL, NULL, &node);
}

void AlgorithmPreorder::run(const Factory& fact, Visitor& visitor) {
  mainRun(&fact, &visitor, NULL);
}

void AlgorithmPreorder::run(const Factory& fact, Visitor& visitor, const base::Base& node) {
  mainRun(&fact, &visitor, &node);
}

void AlgorithmPreorder::run(const Factory& fact, Visitor& visitor, NodeId nodeId) {
  mainRun(&fact, &visitor, fact.getPointer(nodeId));
}

void AlgorithmPreorder::mainRun(const Factory* _fact, Visitor* visitor, const base::Base* node) {
  if (_fact ) {
    this->fact = const_cast<Factory*>(_fact);
  }
  if (visitor) {
    this->visitorList.clear();
    this->visitorList.push_back(visitor);
  }
  this->apRoot = node;

  startPreorder();

  if (apRoot) {
    apRoot->accept(*this);

    if (!needPreorderStop && visitSpecialNodes && !visitUsedSpecialNodesOnly) {
      Factory::ConstIterator it = fact->constIterator();
      while (it.hasNext()) {
        const base::Base& b = it.next();
        if (!visitedNodes[b.getId()] && Common::getIsAPSpecNode(b)) {
          b.accept(*this);

          if(needPreorderStop)
            return;
        }
      }
    }

    if (!needPreorderStop && (visitCrossEdgeTree || visitUsedSpecialNodesOnly)) {
      bool wasNodeToTraversal = false;
      size_t factSize = fact->size();
      do {
        wasNodeToTraversal = false;
        for (size_t i = 0; i < factSize; ++i) {
          if (unvisitedNodes[i] && !visitedNodes[i]) {
            fact->getPointer(i)->accept(*this);
            wasNodeToTraversal = true;
            unvisitedNodes[i] = false;

            if(needPreorderStop)
              return;
          }
        }
      } while (wasNodeToTraversal);
    }

  } else {
    size_t factSize = fact->size();
    for (size_t i = 0; i < factSize; ++i) {
      if ((!fact->getIsFiltered(i)) &&  fact->isIndividual(i)){
        (fact->getPointer(i))->accept(*this);

        if(needPreorderStop)
          return;
      }
    }
  }

  endPreorder();
}

void AlgorithmPreorder::setFactory(Factory& _fact) {
  fact = &_fact;
}

void AlgorithmPreorder::addVisitor(Visitor& visitor) {
  visitorList.push_back( &visitor);
}

void AlgorithmPreorder::visitAllEdges(const base::Base& node, bool callFirst /*= true*/){
}

void AlgorithmPreorder::visitAllEdges(const base::Comment& node, bool callFirst /*= true*/){
  visitAllEdges(dynamic_cast<const base::Positioned&>(node),false);
}

void AlgorithmPreorder::visit(const base::Comment& node, bool callFirst /*= true*/){
#ifdef DEBUG_PREORDER
  std::cout << "Rec. run: " << (unsigned int)&node << " " << node.getId() << " " << Common::toString(node.getNodeKind()) << std::endl;
#endif
  if (safeMode || visitCrossEdgeTree || visitSpecialNodes) {
    if (safeMode) {
      if (visitedNodes[node.getId()]) { // for safemode
        common::WriteMsg::write(CMSG_THE_PRE_ORDER_HAS_TOUCHED_A_NODE_TWICE,node.getId(),Common::toString(node.getNodeKind()).c_str() );
        return;
      }
    }
    visitedNodes[node.getId()] = true;
  }

  for (std::list<Visitor*>::iterator itVisitors = visitorList.begin();itVisitors != visitorList.end(); ++itVisitors) {
    (*itVisitors)->visit(node);
    incVisitorDepth((**itVisitors));
  }

  clearStoppedVisitors();
  if(needPreorderStop)
    return;

  visitAllEdges(node,true);

  for (std::list<Visitor*>::iterator itVisitors = visitorList.begin();itVisitors != visitorList.end(); ++itVisitors) {
    decVisitorDepth(**itVisitors);
    (*itVisitors)->visitEnd(node);
  }

  clearStoppedVisitors();
}

void AlgorithmPreorder::visitAllEdges(const base::Docstring& node, bool callFirst /*= true*/){
  visitAllEdges(dynamic_cast<const base::Positioned&>(node),false);
}

void AlgorithmPreorder::visit(const base::Docstring& node, bool callFirst /*= true*/){
#ifdef DEBUG_PREORDER
  std::cout << "Rec. run: " << (unsigned int)&node << " " << node.getId() << " " << Common::toString(node.getNodeKind()) << std::endl;
#endif
  if (safeMode || visitCrossEdgeTree || visitSpecialNodes) {
    if (safeMode) {
      if (visitedNodes[node.getId()]) { // for safemode
        common::WriteMsg::write(CMSG_THE_PRE_ORDER_HAS_TOUCHED_A_NODE_TWICE,node.getId(),Common::toString(node.getNodeKind()).c_str() );
        return;
      }
    }
    visitedNodes[node.getId()] = true;
  }

  for (std::list<Visitor*>::iterator itVisitors = visitorList.begin();itVisitors != visitorList.end(); ++itVisitors) {
    (*itVisitors)->visit(node);
    incVisitorDepth((**itVisitors));
  }

  clearStoppedVisitors();
  if(needPreorderStop)
    return;

  visitAllEdges(node,true);

  for (std::list<Visitor*>::iterator itVisitors = visitorList.begin();itVisitors != visitorList.end(); ++itVisitors) {
    decVisitorDepth(**itVisitors);
    (*itVisitors)->visitEnd(node);
  }

  clearStoppedVisitors();
}

void AlgorithmPreorder::visitAllEdges(const base::Named& node, bool callFirst /*= true*/){
  visitAllEdges(dynamic_cast<const base::Positioned&>(node),false);
}

void AlgorithmPreorder::visitAllEdges(const base::Positioned& node, bool callFirst /*= true*/){
  visitAllEdges(dynamic_cast<const base::Base&>(node),false);

  std::list<Visitor*>::iterator itVisitors;

  // edge: comments
  for (ListIterator<base::Comment> it = node.getCommentsListIteratorBegin(); it != node.getCommentsListIteratorEnd(); ++it) {
    const base::Comment& endNodeRef = *it;
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitPositioned_Comments(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;

    if ((!fact->getIsFilterTurnedOn() && !visitFilteredEdge) || (fact->getFilterState(endNodeRef.getId()) == Filter::NotFiltered) || (!originalFilterState && visitFilteredEdge)) {
      if (apRoot) {
        if (visitCrossEdgeTree || (visitUsedSpecialNodesOnly && Common::getIsAPSpecNode(endNodeRef))) {
          unvisitedNodes[endNodeRef.getId()] = true;
        }
      }
      if (traversaldCrossEdges[edkPositioned_Comments]) {
        endNodeRef.accept(*this);
      }
    }
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitEndPositioned_Comments(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;
  }
}

void AlgorithmPreorder::visitAllEdges(const expression::ArgumentList& node, bool callFirst /*= true*/){
  visitAllEdges(dynamic_cast<const base::Positioned&>(node),false);

  std::list<Visitor*>::iterator itVisitors;

  const base::Base* genNodePtr;
  // edge: hasPositionalArguments
  genNodePtr = node.getPositionalArguments() ;
  if (genNodePtr) {
    const expression::ExpressionList& endNodeRef = dynamic_cast<const expression::ExpressionList&>(*genNodePtr);
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitArgumentList_HasPositionalArguments(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;

    if ((!fact->getIsFilterTurnedOn() && !visitFilteredEdge) || (fact->getFilterState(endNodeRef.getId()) == Filter::NotFiltered) || (!originalFilterState && visitFilteredEdge)) {
      if (apRoot && visitUsedSpecialNodesOnly && Common::getIsAPSpecNode(endNodeRef)) {
        unvisitedNodes[endNodeRef.getId()] = true;
      } else {
        endNodeRef.accept(*this);
      }
    }
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitEndArgumentList_HasPositionalArguments(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;
  }

  // edge: hasDictionary
  genNodePtr = node.getDictionary() ;
  if (genNodePtr) {
    const expression::Expression& endNodeRef = dynamic_cast<const expression::Expression&>(*genNodePtr);
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitArgumentList_HasDictionary(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;

    if ((!fact->getIsFilterTurnedOn() && !visitFilteredEdge) || (fact->getFilterState(endNodeRef.getId()) == Filter::NotFiltered) || (!originalFilterState && visitFilteredEdge)) {
      if (apRoot && visitUsedSpecialNodesOnly && Common::getIsAPSpecNode(endNodeRef)) {
        unvisitedNodes[endNodeRef.getId()] = true;
      } else {
        endNodeRef.accept(*this);
      }
    }
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitEndArgumentList_HasDictionary(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;
  }

  // edge: hasKeyword
  for (ListIterator<expression::Keyword> it = node.getKeywordListIteratorBegin(); it != node.getKeywordListIteratorEnd(); ++it) {
    const expression::Keyword& endNodeRef = *it;
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitArgumentList_HasKeyword(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;

    if ((!fact->getIsFilterTurnedOn() && !visitFilteredEdge) || (fact->getFilterState(endNodeRef.getId()) == Filter::NotFiltered) || (!originalFilterState && visitFilteredEdge)) {
      if (apRoot && visitUsedSpecialNodesOnly && Common::getIsAPSpecNode(endNodeRef)) {
        unvisitedNodes[endNodeRef.getId()] = true;
      } else {
        endNodeRef.accept(*this);
      }
    }
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitEndArgumentList_HasKeyword(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;
  }

  // edge: hasTuple
  genNodePtr = node.getTuple() ;
  if (genNodePtr) {
    const expression::Expression& endNodeRef = dynamic_cast<const expression::Expression&>(*genNodePtr);
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitArgumentList_HasTuple(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;

    if ((!fact->getIsFilterTurnedOn() && !visitFilteredEdge) || (fact->getFilterState(endNodeRef.getId()) == Filter::NotFiltered) || (!originalFilterState && visitFilteredEdge)) {
      if (apRoot && visitUsedSpecialNodesOnly && Common::getIsAPSpecNode(endNodeRef)) {
        unvisitedNodes[endNodeRef.getId()] = true;
      } else {
        endNodeRef.accept(*this);
      }
    }
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitEndArgumentList_HasTuple(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;
  }
}

void AlgorithmPreorder::visit(const expression::ArgumentList& node, bool callFirst /*= true*/){
#ifdef DEBUG_PREORDER
  std::cout << "Rec. run: " << (unsigned int)&node << " " << node.getId() << " " << Common::toString(node.getNodeKind()) << std::endl;
#endif
  if (safeMode || visitCrossEdgeTree || visitSpecialNodes) {
    if (safeMode) {
      if (visitedNodes[node.getId()]) { // for safemode
        common::WriteMsg::write(CMSG_THE_PRE_ORDER_HAS_TOUCHED_A_NODE_TWICE,node.getId(),Common::toString(node.getNodeKind()).c_str() );
        return;
      }
    }
    visitedNodes[node.getId()] = true;
  }

  for (std::list<Visitor*>::iterator itVisitors = visitorList.begin();itVisitors != visitorList.end(); ++itVisitors) {
    (*itVisitors)->visit(node);
    incVisitorDepth((**itVisitors));
  }

  clearStoppedVisitors();
  if(needPreorderStop)
    return;

  visitAllEdges(node,true);

  for (std::list<Visitor*>::iterator itVisitors = visitorList.begin();itVisitors != visitorList.end(); ++itVisitors) {
    decVisitorDepth(**itVisitors);
    (*itVisitors)->visitEnd(node);
  }

  clearStoppedVisitors();
}

void AlgorithmPreorder::visitAllEdges(const expression::AttributeRef& node, bool callFirst /*= true*/){
  visitAllEdges(dynamic_cast<const expression::Binary&>(node),false);
}

void AlgorithmPreorder::visit(const expression::AttributeRef& node, bool callFirst /*= true*/){
#ifdef DEBUG_PREORDER
  std::cout << "Rec. run: " << (unsigned int)&node << " " << node.getId() << " " << Common::toString(node.getNodeKind()) << std::endl;
#endif
  if (safeMode || visitCrossEdgeTree || visitSpecialNodes) {
    if (safeMode) {
      if (visitedNodes[node.getId()]) { // for safemode
        common::WriteMsg::write(CMSG_THE_PRE_ORDER_HAS_TOUCHED_A_NODE_TWICE,node.getId(),Common::toString(node.getNodeKind()).c_str() );
        return;
      }
    }
    visitedNodes[node.getId()] = true;
  }

  for (std::list<Visitor*>::iterator itVisitors = visitorList.begin();itVisitors != visitorList.end(); ++itVisitors) {
    (*itVisitors)->visit(node);
    incVisitorDepth((**itVisitors));
  }

  clearStoppedVisitors();
  if(needPreorderStop)
    return;

  visitAllEdges(node,true);

  for (std::list<Visitor*>::iterator itVisitors = visitorList.begin();itVisitors != visitorList.end(); ++itVisitors) {
    decVisitorDepth(**itVisitors);
    (*itVisitors)->visitEnd(node);
  }

  clearStoppedVisitors();
}

void AlgorithmPreorder::visitAllEdges(const expression::Binary& node, bool callFirst /*= true*/){
  visitAllEdges(dynamic_cast<const expression::Expression&>(node),false);

  std::list<Visitor*>::iterator itVisitors;

  const base::Base* genNodePtr;
  // edge: hasLeftExpression
  genNodePtr = node.getLeftExpression() ;
  if (genNodePtr) {
    const expression::Expression& endNodeRef = dynamic_cast<const expression::Expression&>(*genNodePtr);
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitBinary_HasLeftExpression(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;

    if ((!fact->getIsFilterTurnedOn() && !visitFilteredEdge) || (fact->getFilterState(endNodeRef.getId()) == Filter::NotFiltered) || (!originalFilterState && visitFilteredEdge)) {
      if (apRoot && visitUsedSpecialNodesOnly && Common::getIsAPSpecNode(endNodeRef)) {
        unvisitedNodes[endNodeRef.getId()] = true;
      } else {
        endNodeRef.accept(*this);
      }
    }
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitEndBinary_HasLeftExpression(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;
  }

  // edge: hasRightExpression
  genNodePtr = node.getRightExpression() ;
  if (genNodePtr) {
    const expression::Expression& endNodeRef = dynamic_cast<const expression::Expression&>(*genNodePtr);
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitBinary_HasRightExpression(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;

    if ((!fact->getIsFilterTurnedOn() && !visitFilteredEdge) || (fact->getFilterState(endNodeRef.getId()) == Filter::NotFiltered) || (!originalFilterState && visitFilteredEdge)) {
      if (apRoot && visitUsedSpecialNodesOnly && Common::getIsAPSpecNode(endNodeRef)) {
        unvisitedNodes[endNodeRef.getId()] = true;
      } else {
        endNodeRef.accept(*this);
      }
    }
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitEndBinary_HasRightExpression(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;
  }
}

void AlgorithmPreorder::visitAllEdges(const expression::BinaryArithmetic& node, bool callFirst /*= true*/){
  visitAllEdges(dynamic_cast<const expression::Binary&>(node),false);
}

void AlgorithmPreorder::visit(const expression::BinaryArithmetic& node, bool callFirst /*= true*/){
#ifdef DEBUG_PREORDER
  std::cout << "Rec. run: " << (unsigned int)&node << " " << node.getId() << " " << Common::toString(node.getNodeKind()) << std::endl;
#endif
  if (safeMode || visitCrossEdgeTree || visitSpecialNodes) {
    if (safeMode) {
      if (visitedNodes[node.getId()]) { // for safemode
        common::WriteMsg::write(CMSG_THE_PRE_ORDER_HAS_TOUCHED_A_NODE_TWICE,node.getId(),Common::toString(node.getNodeKind()).c_str() );
        return;
      }
    }
    visitedNodes[node.getId()] = true;
  }

  for (std::list<Visitor*>::iterator itVisitors = visitorList.begin();itVisitors != visitorList.end(); ++itVisitors) {
    (*itVisitors)->visit(node);
    incVisitorDepth((**itVisitors));
  }

  clearStoppedVisitors();
  if(needPreorderStop)
    return;

  visitAllEdges(node,true);

  for (std::list<Visitor*>::iterator itVisitors = visitorList.begin();itVisitors != visitorList.end(); ++itVisitors) {
    decVisitorDepth(**itVisitors);
    (*itVisitors)->visitEnd(node);
  }

  clearStoppedVisitors();
}

void AlgorithmPreorder::visitAllEdges(const expression::BinaryLogical& node, bool callFirst /*= true*/){
  visitAllEdges(dynamic_cast<const expression::Binary&>(node),false);
}

void AlgorithmPreorder::visit(const expression::BinaryLogical& node, bool callFirst /*= true*/){
#ifdef DEBUG_PREORDER
  std::cout << "Rec. run: " << (unsigned int)&node << " " << node.getId() << " " << Common::toString(node.getNodeKind()) << std::endl;
#endif
  if (safeMode || visitCrossEdgeTree || visitSpecialNodes) {
    if (safeMode) {
      if (visitedNodes[node.getId()]) { // for safemode
        common::WriteMsg::write(CMSG_THE_PRE_ORDER_HAS_TOUCHED_A_NODE_TWICE,node.getId(),Common::toString(node.getNodeKind()).c_str() );
        return;
      }
    }
    visitedNodes[node.getId()] = true;
  }

  for (std::list<Visitor*>::iterator itVisitors = visitorList.begin();itVisitors != visitorList.end(); ++itVisitors) {
    (*itVisitors)->visit(node);
    incVisitorDepth((**itVisitors));
  }

  clearStoppedVisitors();
  if(needPreorderStop)
    return;

  visitAllEdges(node,true);

  for (std::list<Visitor*>::iterator itVisitors = visitorList.begin();itVisitors != visitorList.end(); ++itVisitors) {
    decVisitorDepth(**itVisitors);
    (*itVisitors)->visitEnd(node);
  }

  clearStoppedVisitors();
}

void AlgorithmPreorder::visitAllEdges(const expression::Call& node, bool callFirst /*= true*/){
  visitAllEdges(dynamic_cast<const expression::Unary&>(node),false);

  std::list<Visitor*>::iterator itVisitors;

  const base::Base* genNodePtr;
  // edge: hasArgumentList
  genNodePtr = node.getArgumentList() ;
  if (genNodePtr) {
    const expression::ArgumentList& endNodeRef = dynamic_cast<const expression::ArgumentList&>(*genNodePtr);
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitCall_HasArgumentList(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;

    if ((!fact->getIsFilterTurnedOn() && !visitFilteredEdge) || (fact->getFilterState(endNodeRef.getId()) == Filter::NotFiltered) || (!originalFilterState && visitFilteredEdge)) {
      if (apRoot && visitUsedSpecialNodesOnly && Common::getIsAPSpecNode(endNodeRef)) {
        unvisitedNodes[endNodeRef.getId()] = true;
      } else {
        endNodeRef.accept(*this);
      }
    }
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitEndCall_HasArgumentList(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;
  }

  // edge: refersTo
  genNodePtr = node.getRefersTo() ;
  if (genNodePtr) {
    const statement::CompoundStatement& endNodeRef = dynamic_cast<const statement::CompoundStatement&>(*genNodePtr);
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitCall_RefersTo(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;

    if ((!fact->getIsFilterTurnedOn() && !visitFilteredEdge) || (fact->getFilterState(endNodeRef.getId()) == Filter::NotFiltered) || (!originalFilterState && visitFilteredEdge)) {
      if (apRoot) {
        if (visitCrossEdgeTree || (visitUsedSpecialNodesOnly && Common::getIsAPSpecNode(endNodeRef))) {
          unvisitedNodes[endNodeRef.getId()] = true;
        }
      }
      if (traversaldCrossEdges[edkCall_RefersTo]) {
        endNodeRef.accept(*this);
      }
    }
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitEndCall_RefersTo(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;
  }
}

void AlgorithmPreorder::visit(const expression::Call& node, bool callFirst /*= true*/){
#ifdef DEBUG_PREORDER
  std::cout << "Rec. run: " << (unsigned int)&node << " " << node.getId() << " " << Common::toString(node.getNodeKind()) << std::endl;
#endif
  if (safeMode || visitCrossEdgeTree || visitSpecialNodes) {
    if (safeMode) {
      if (visitedNodes[node.getId()]) { // for safemode
        common::WriteMsg::write(CMSG_THE_PRE_ORDER_HAS_TOUCHED_A_NODE_TWICE,node.getId(),Common::toString(node.getNodeKind()).c_str() );
        return;
      }
    }
    visitedNodes[node.getId()] = true;
  }

  for (std::list<Visitor*>::iterator itVisitors = visitorList.begin();itVisitors != visitorList.end(); ++itVisitors) {
    (*itVisitors)->visit(node);
    incVisitorDepth((**itVisitors));
  }

  clearStoppedVisitors();
  if(needPreorderStop)
    return;

  visitAllEdges(node,true);

  for (std::list<Visitor*>::iterator itVisitors = visitorList.begin();itVisitors != visitorList.end(); ++itVisitors) {
    decVisitorDepth(**itVisitors);
    (*itVisitors)->visitEnd(node);
  }

  clearStoppedVisitors();
}

void AlgorithmPreorder::visitAllEdges(const expression::DictComp& node, bool callFirst /*= true*/){
  visitAllEdges(dynamic_cast<const expression::Expression&>(node),false);

  std::list<Visitor*>::iterator itVisitors;

  const base::Base* genNodePtr;
  // edge: hasKeyValue
  genNodePtr = node.getKeyValue() ;
  if (genNodePtr) {
    const expression::KeyValue& endNodeRef = dynamic_cast<const expression::KeyValue&>(*genNodePtr);
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitDictComp_HasKeyValue(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;

    if ((!fact->getIsFilterTurnedOn() && !visitFilteredEdge) || (fact->getFilterState(endNodeRef.getId()) == Filter::NotFiltered) || (!originalFilterState && visitFilteredEdge)) {
      if (apRoot && visitUsedSpecialNodesOnly && Common::getIsAPSpecNode(endNodeRef)) {
        unvisitedNodes[endNodeRef.getId()] = true;
      } else {
        endNodeRef.accept(*this);
      }
    }
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitEndDictComp_HasKeyValue(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;
  }

  // edge: hasGenerator
  for (ListIterator<expression::Generator> it = node.getGeneratorListIteratorBegin(); it != node.getGeneratorListIteratorEnd(); ++it) {
    const expression::Generator& endNodeRef = *it;
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitDictComp_HasGenerator(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;

    if ((!fact->getIsFilterTurnedOn() && !visitFilteredEdge) || (fact->getFilterState(endNodeRef.getId()) == Filter::NotFiltered) || (!originalFilterState && visitFilteredEdge)) {
      if (apRoot && visitUsedSpecialNodesOnly && Common::getIsAPSpecNode(endNodeRef)) {
        unvisitedNodes[endNodeRef.getId()] = true;
      } else {
        endNodeRef.accept(*this);
      }
    }
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitEndDictComp_HasGenerator(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;
  }
}

void AlgorithmPreorder::visit(const expression::DictComp& node, bool callFirst /*= true*/){
#ifdef DEBUG_PREORDER
  std::cout << "Rec. run: " << (unsigned int)&node << " " << node.getId() << " " << Common::toString(node.getNodeKind()) << std::endl;
#endif
  if (safeMode || visitCrossEdgeTree || visitSpecialNodes) {
    if (safeMode) {
      if (visitedNodes[node.getId()]) { // for safemode
        common::WriteMsg::write(CMSG_THE_PRE_ORDER_HAS_TOUCHED_A_NODE_TWICE,node.getId(),Common::toString(node.getNodeKind()).c_str() );
        return;
      }
    }
    visitedNodes[node.getId()] = true;
  }

  for (std::list<Visitor*>::iterator itVisitors = visitorList.begin();itVisitors != visitorList.end(); ++itVisitors) {
    (*itVisitors)->visit(node);
    incVisitorDepth((**itVisitors));
  }

  clearStoppedVisitors();
  if(needPreorderStop)
    return;

  visitAllEdges(node,true);

  for (std::list<Visitor*>::iterator itVisitors = visitorList.begin();itVisitors != visitorList.end(); ++itVisitors) {
    decVisitorDepth(**itVisitors);
    (*itVisitors)->visitEnd(node);
  }

  clearStoppedVisitors();
}

void AlgorithmPreorder::visitAllEdges(const expression::Dictionary& node, bool callFirst /*= true*/){
  visitAllEdges(dynamic_cast<const expression::Expression&>(node),false);

  std::list<Visitor*>::iterator itVisitors;

  // edge: hasKeyValue
  for (ListIterator<expression::KeyValue> it = node.getKeyValueListIteratorBegin(); it != node.getKeyValueListIteratorEnd(); ++it) {
    const expression::KeyValue& endNodeRef = *it;
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitDictionary_HasKeyValue(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;

    if ((!fact->getIsFilterTurnedOn() && !visitFilteredEdge) || (fact->getFilterState(endNodeRef.getId()) == Filter::NotFiltered) || (!originalFilterState && visitFilteredEdge)) {
      if (apRoot && visitUsedSpecialNodesOnly && Common::getIsAPSpecNode(endNodeRef)) {
        unvisitedNodes[endNodeRef.getId()] = true;
      } else {
        endNodeRef.accept(*this);
      }
    }
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitEndDictionary_HasKeyValue(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;
  }
}

void AlgorithmPreorder::visit(const expression::Dictionary& node, bool callFirst /*= true*/){
#ifdef DEBUG_PREORDER
  std::cout << "Rec. run: " << (unsigned int)&node << " " << node.getId() << " " << Common::toString(node.getNodeKind()) << std::endl;
#endif
  if (safeMode || visitCrossEdgeTree || visitSpecialNodes) {
    if (safeMode) {
      if (visitedNodes[node.getId()]) { // for safemode
        common::WriteMsg::write(CMSG_THE_PRE_ORDER_HAS_TOUCHED_A_NODE_TWICE,node.getId(),Common::toString(node.getNodeKind()).c_str() );
        return;
      }
    }
    visitedNodes[node.getId()] = true;
  }

  for (std::list<Visitor*>::iterator itVisitors = visitorList.begin();itVisitors != visitorList.end(); ++itVisitors) {
    (*itVisitors)->visit(node);
    incVisitorDepth((**itVisitors));
  }

  clearStoppedVisitors();
  if(needPreorderStop)
    return;

  visitAllEdges(node,true);

  for (std::list<Visitor*>::iterator itVisitors = visitorList.begin();itVisitors != visitorList.end(); ++itVisitors) {
    decVisitorDepth(**itVisitors);
    (*itVisitors)->visitEnd(node);
  }

  clearStoppedVisitors();
}

void AlgorithmPreorder::visitAllEdges(const expression::Ellipsis& node, bool callFirst /*= true*/){
  visitAllEdges(dynamic_cast<const expression::Slicing&>(node),false);
}

void AlgorithmPreorder::visit(const expression::Ellipsis& node, bool callFirst /*= true*/){
#ifdef DEBUG_PREORDER
  std::cout << "Rec. run: " << (unsigned int)&node << " " << node.getId() << " " << Common::toString(node.getNodeKind()) << std::endl;
#endif
  if (safeMode || visitCrossEdgeTree || visitSpecialNodes) {
    if (safeMode) {
      if (visitedNodes[node.getId()]) { // for safemode
        common::WriteMsg::write(CMSG_THE_PRE_ORDER_HAS_TOUCHED_A_NODE_TWICE,node.getId(),Common::toString(node.getNodeKind()).c_str() );
        return;
      }
    }
    visitedNodes[node.getId()] = true;
  }

  for (std::list<Visitor*>::iterator itVisitors = visitorList.begin();itVisitors != visitorList.end(); ++itVisitors) {
    (*itVisitors)->visit(node);
    incVisitorDepth((**itVisitors));
  }

  clearStoppedVisitors();
  if(needPreorderStop)
    return;

  visitAllEdges(node,true);

  for (std::list<Visitor*>::iterator itVisitors = visitorList.begin();itVisitors != visitorList.end(); ++itVisitors) {
    decVisitorDepth(**itVisitors);
    (*itVisitors)->visitEnd(node);
  }

  clearStoppedVisitors();
}

void AlgorithmPreorder::visitAllEdges(const expression::Expression& node, bool callFirst /*= true*/){
  visitAllEdges(dynamic_cast<const base::Positioned&>(node),false);

  std::list<Visitor*>::iterator itVisitors;

  const base::Base* genNodePtr;
  // edge: hasType
  genNodePtr = node.getType() ;
  if (genNodePtr) {
    const type::Type& endNodeRef = dynamic_cast<const type::Type&>(*genNodePtr);
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitExpression_HasType(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;

    if ((!fact->getIsFilterTurnedOn() && !visitFilteredEdge) || (fact->getFilterState(endNodeRef.getId()) == Filter::NotFiltered) || (!originalFilterState && visitFilteredEdge)) {
      if (apRoot) {
        if (visitCrossEdgeTree || (visitUsedSpecialNodesOnly && Common::getIsAPSpecNode(endNodeRef))) {
          unvisitedNodes[endNodeRef.getId()] = true;
        }
      }
      if (traversaldCrossEdges[edkExpression_HasType]) {
        endNodeRef.accept(*this);
      }
    }
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitEndExpression_HasType(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;
  }
}

void AlgorithmPreorder::visitAllEdges(const expression::ExpressionList& node, bool callFirst /*= true*/){
  visitAllEdges(dynamic_cast<const expression::Expression&>(node),false);

  std::list<Visitor*>::iterator itVisitors;

  // edge: hasExpression
  for (ListIterator<expression::Expression> it = node.getExpressionListIteratorBegin(); it != node.getExpressionListIteratorEnd(); ++it) {
    const expression::Expression& endNodeRef = *it;
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitExpressionList_HasExpression(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;

    if ((!fact->getIsFilterTurnedOn() && !visitFilteredEdge) || (fact->getFilterState(endNodeRef.getId()) == Filter::NotFiltered) || (!originalFilterState && visitFilteredEdge)) {
      if (apRoot && visitUsedSpecialNodesOnly && Common::getIsAPSpecNode(endNodeRef)) {
        unvisitedNodes[endNodeRef.getId()] = true;
      } else {
        endNodeRef.accept(*this);
      }
    }
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitEndExpressionList_HasExpression(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;
  }
}

void AlgorithmPreorder::visit(const expression::ExpressionList& node, bool callFirst /*= true*/){
#ifdef DEBUG_PREORDER
  std::cout << "Rec. run: " << (unsigned int)&node << " " << node.getId() << " " << Common::toString(node.getNodeKind()) << std::endl;
#endif
  if (safeMode || visitCrossEdgeTree || visitSpecialNodes) {
    if (safeMode) {
      if (visitedNodes[node.getId()]) { // for safemode
        common::WriteMsg::write(CMSG_THE_PRE_ORDER_HAS_TOUCHED_A_NODE_TWICE,node.getId(),Common::toString(node.getNodeKind()).c_str() );
        return;
      }
    }
    visitedNodes[node.getId()] = true;
  }

  for (std::list<Visitor*>::iterator itVisitors = visitorList.begin();itVisitors != visitorList.end(); ++itVisitors) {
    (*itVisitors)->visit(node);
    incVisitorDepth((**itVisitors));
  }

  clearStoppedVisitors();
  if(needPreorderStop)
    return;

  visitAllEdges(node,true);

  for (std::list<Visitor*>::iterator itVisitors = visitorList.begin();itVisitors != visitorList.end(); ++itVisitors) {
    decVisitorDepth(**itVisitors);
    (*itVisitors)->visitEnd(node);
  }

  clearStoppedVisitors();
}

void AlgorithmPreorder::visitAllEdges(const expression::ExtSlice& node, bool callFirst /*= true*/){
  visitAllEdges(dynamic_cast<const expression::Slicing&>(node),false);

  std::list<Visitor*>::iterator itVisitors;

  // edge: hasItem
  for (ListIterator<expression::Slicing> it = node.getItemListIteratorBegin(); it != node.getItemListIteratorEnd(); ++it) {
    const expression::Slicing& endNodeRef = *it;
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitExtSlice_HasItem(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;

    if ((!fact->getIsFilterTurnedOn() && !visitFilteredEdge) || (fact->getFilterState(endNodeRef.getId()) == Filter::NotFiltered) || (!originalFilterState && visitFilteredEdge)) {
      if (apRoot && visitUsedSpecialNodesOnly && Common::getIsAPSpecNode(endNodeRef)) {
        unvisitedNodes[endNodeRef.getId()] = true;
      } else {
        endNodeRef.accept(*this);
      }
    }
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitEndExtSlice_HasItem(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;
  }
}

void AlgorithmPreorder::visit(const expression::ExtSlice& node, bool callFirst /*= true*/){
#ifdef DEBUG_PREORDER
  std::cout << "Rec. run: " << (unsigned int)&node << " " << node.getId() << " " << Common::toString(node.getNodeKind()) << std::endl;
#endif
  if (safeMode || visitCrossEdgeTree || visitSpecialNodes) {
    if (safeMode) {
      if (visitedNodes[node.getId()]) { // for safemode
        common::WriteMsg::write(CMSG_THE_PRE_ORDER_HAS_TOUCHED_A_NODE_TWICE,node.getId(),Common::toString(node.getNodeKind()).c_str() );
        return;
      }
    }
    visitedNodes[node.getId()] = true;
  }

  for (std::list<Visitor*>::iterator itVisitors = visitorList.begin();itVisitors != visitorList.end(); ++itVisitors) {
    (*itVisitors)->visit(node);
    incVisitorDepth((**itVisitors));
  }

  clearStoppedVisitors();
  if(needPreorderStop)
    return;

  visitAllEdges(node,true);

  for (std::list<Visitor*>::iterator itVisitors = visitorList.begin();itVisitors != visitorList.end(); ++itVisitors) {
    decVisitorDepth(**itVisitors);
    (*itVisitors)->visitEnd(node);
  }

  clearStoppedVisitors();
}

void AlgorithmPreorder::visitAllEdges(const expression::FloatNumber& node, bool callFirst /*= true*/){
  visitAllEdges(dynamic_cast<const expression::Literal&>(node),false);
}

void AlgorithmPreorder::visit(const expression::FloatNumber& node, bool callFirst /*= true*/){
#ifdef DEBUG_PREORDER
  std::cout << "Rec. run: " << (unsigned int)&node << " " << node.getId() << " " << Common::toString(node.getNodeKind()) << std::endl;
#endif
  if (safeMode || visitCrossEdgeTree || visitSpecialNodes) {
    if (safeMode) {
      if (visitedNodes[node.getId()]) { // for safemode
        common::WriteMsg::write(CMSG_THE_PRE_ORDER_HAS_TOUCHED_A_NODE_TWICE,node.getId(),Common::toString(node.getNodeKind()).c_str() );
        return;
      }
    }
    visitedNodes[node.getId()] = true;
  }

  for (std::list<Visitor*>::iterator itVisitors = visitorList.begin();itVisitors != visitorList.end(); ++itVisitors) {
    (*itVisitors)->visit(node);
    incVisitorDepth((**itVisitors));
  }

  clearStoppedVisitors();
  if(needPreorderStop)
    return;

  visitAllEdges(node,true);

  for (std::list<Visitor*>::iterator itVisitors = visitorList.begin();itVisitors != visitorList.end(); ++itVisitors) {
    decVisitorDepth(**itVisitors);
    (*itVisitors)->visitEnd(node);
  }

  clearStoppedVisitors();
}

void AlgorithmPreorder::visitAllEdges(const expression::Generator& node, bool callFirst /*= true*/){
  visitAllEdges(dynamic_cast<const base::Positioned&>(node),false);

  std::list<Visitor*>::iterator itVisitors;

  // edge: hasCondition
  for (ListIterator<expression::Expression> it = node.getConditionListIteratorBegin(); it != node.getConditionListIteratorEnd(); ++it) {
    const expression::Expression& endNodeRef = *it;
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitGenerator_HasCondition(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;

    if ((!fact->getIsFilterTurnedOn() && !visitFilteredEdge) || (fact->getFilterState(endNodeRef.getId()) == Filter::NotFiltered) || (!originalFilterState && visitFilteredEdge)) {
      if (apRoot && visitUsedSpecialNodesOnly && Common::getIsAPSpecNode(endNodeRef)) {
        unvisitedNodes[endNodeRef.getId()] = true;
      } else {
        endNodeRef.accept(*this);
      }
    }
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitEndGenerator_HasCondition(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;
  }

  const base::Base* genNodePtr;
  // edge: hasIter
  genNodePtr = node.getIter() ;
  if (genNodePtr) {
    const expression::Expression& endNodeRef = dynamic_cast<const expression::Expression&>(*genNodePtr);
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitGenerator_HasIter(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;

    if ((!fact->getIsFilterTurnedOn() && !visitFilteredEdge) || (fact->getFilterState(endNodeRef.getId()) == Filter::NotFiltered) || (!originalFilterState && visitFilteredEdge)) {
      if (apRoot && visitUsedSpecialNodesOnly && Common::getIsAPSpecNode(endNodeRef)) {
        unvisitedNodes[endNodeRef.getId()] = true;
      } else {
        endNodeRef.accept(*this);
      }
    }
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitEndGenerator_HasIter(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;
  }

  // edge: hasTarget
  genNodePtr = node.getTarget() ;
  if (genNodePtr) {
    const expression::Expression& endNodeRef = dynamic_cast<const expression::Expression&>(*genNodePtr);
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitGenerator_HasTarget(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;

    if ((!fact->getIsFilterTurnedOn() && !visitFilteredEdge) || (fact->getFilterState(endNodeRef.getId()) == Filter::NotFiltered) || (!originalFilterState && visitFilteredEdge)) {
      if (apRoot && visitUsedSpecialNodesOnly && Common::getIsAPSpecNode(endNodeRef)) {
        unvisitedNodes[endNodeRef.getId()] = true;
      } else {
        endNodeRef.accept(*this);
      }
    }
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitEndGenerator_HasTarget(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;
  }
}

void AlgorithmPreorder::visit(const expression::Generator& node, bool callFirst /*= true*/){
#ifdef DEBUG_PREORDER
  std::cout << "Rec. run: " << (unsigned int)&node << " " << node.getId() << " " << Common::toString(node.getNodeKind()) << std::endl;
#endif
  if (safeMode || visitCrossEdgeTree || visitSpecialNodes) {
    if (safeMode) {
      if (visitedNodes[node.getId()]) { // for safemode
        common::WriteMsg::write(CMSG_THE_PRE_ORDER_HAS_TOUCHED_A_NODE_TWICE,node.getId(),Common::toString(node.getNodeKind()).c_str() );
        return;
      }
    }
    visitedNodes[node.getId()] = true;
  }

  for (std::list<Visitor*>::iterator itVisitors = visitorList.begin();itVisitors != visitorList.end(); ++itVisitors) {
    (*itVisitors)->visit(node);
    incVisitorDepth((**itVisitors));
  }

  clearStoppedVisitors();
  if(needPreorderStop)
    return;

  visitAllEdges(node,true);

  for (std::list<Visitor*>::iterator itVisitors = visitorList.begin();itVisitors != visitorList.end(); ++itVisitors) {
    decVisitorDepth(**itVisitors);
    (*itVisitors)->visitEnd(node);
  }

  clearStoppedVisitors();
}

void AlgorithmPreorder::visitAllEdges(const expression::GeneratorExpression& node, bool callFirst /*= true*/){
  visitAllEdges(dynamic_cast<const expression::Expression&>(node),false);

  std::list<Visitor*>::iterator itVisitors;

  const base::Base* genNodePtr;
  // edge: hasExpression
  genNodePtr = node.getExpression() ;
  if (genNodePtr) {
    const expression::Expression& endNodeRef = dynamic_cast<const expression::Expression&>(*genNodePtr);
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitGeneratorExpression_HasExpression(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;

    if ((!fact->getIsFilterTurnedOn() && !visitFilteredEdge) || (fact->getFilterState(endNodeRef.getId()) == Filter::NotFiltered) || (!originalFilterState && visitFilteredEdge)) {
      if (apRoot && visitUsedSpecialNodesOnly && Common::getIsAPSpecNode(endNodeRef)) {
        unvisitedNodes[endNodeRef.getId()] = true;
      } else {
        endNodeRef.accept(*this);
      }
    }
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitEndGeneratorExpression_HasExpression(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;
  }

  // edge: hasGenerator
  for (ListIterator<expression::Generator> it = node.getGeneratorListIteratorBegin(); it != node.getGeneratorListIteratorEnd(); ++it) {
    const expression::Generator& endNodeRef = *it;
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitGeneratorExpression_HasGenerator(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;

    if ((!fact->getIsFilterTurnedOn() && !visitFilteredEdge) || (fact->getFilterState(endNodeRef.getId()) == Filter::NotFiltered) || (!originalFilterState && visitFilteredEdge)) {
      if (apRoot && visitUsedSpecialNodesOnly && Common::getIsAPSpecNode(endNodeRef)) {
        unvisitedNodes[endNodeRef.getId()] = true;
      } else {
        endNodeRef.accept(*this);
      }
    }
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitEndGeneratorExpression_HasGenerator(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;
  }
}

void AlgorithmPreorder::visit(const expression::GeneratorExpression& node, bool callFirst /*= true*/){
#ifdef DEBUG_PREORDER
  std::cout << "Rec. run: " << (unsigned int)&node << " " << node.getId() << " " << Common::toString(node.getNodeKind()) << std::endl;
#endif
  if (safeMode || visitCrossEdgeTree || visitSpecialNodes) {
    if (safeMode) {
      if (visitedNodes[node.getId()]) { // for safemode
        common::WriteMsg::write(CMSG_THE_PRE_ORDER_HAS_TOUCHED_A_NODE_TWICE,node.getId(),Common::toString(node.getNodeKind()).c_str() );
        return;
      }
    }
    visitedNodes[node.getId()] = true;
  }

  for (std::list<Visitor*>::iterator itVisitors = visitorList.begin();itVisitors != visitorList.end(); ++itVisitors) {
    (*itVisitors)->visit(node);
    incVisitorDepth((**itVisitors));
  }

  clearStoppedVisitors();
  if(needPreorderStop)
    return;

  visitAllEdges(node,true);

  for (std::list<Visitor*>::iterator itVisitors = visitorList.begin();itVisitors != visitorList.end(); ++itVisitors) {
    decVisitorDepth(**itVisitors);
    (*itVisitors)->visitEnd(node);
  }

  clearStoppedVisitors();
}

void AlgorithmPreorder::visitAllEdges(const expression::Identifier& node, bool callFirst /*= true*/){
  visitAllEdges(dynamic_cast<const expression::Expression&>(node),false);

  std::list<Visitor*>::iterator itVisitors;

  const base::Base* genNodePtr;
  // edge: refersTo
  genNodePtr = node.getRefersTo() ;
  if (genNodePtr) {
    const module::Object& endNodeRef = dynamic_cast<const module::Object&>(*genNodePtr);
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitIdentifier_RefersTo(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;

    if ((!fact->getIsFilterTurnedOn() && !visitFilteredEdge) || (fact->getFilterState(endNodeRef.getId()) == Filter::NotFiltered) || (!originalFilterState && visitFilteredEdge)) {
      if (apRoot) {
        if (visitCrossEdgeTree || (visitUsedSpecialNodesOnly && Common::getIsAPSpecNode(endNodeRef))) {
          unvisitedNodes[endNodeRef.getId()] = true;
        }
      }
      if (traversaldCrossEdges[edkIdentifier_RefersTo]) {
        endNodeRef.accept(*this);
      }
    }
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitEndIdentifier_RefersTo(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;
  }
}

void AlgorithmPreorder::visit(const expression::Identifier& node, bool callFirst /*= true*/){
#ifdef DEBUG_PREORDER
  std::cout << "Rec. run: " << (unsigned int)&node << " " << node.getId() << " " << Common::toString(node.getNodeKind()) << std::endl;
#endif
  if (safeMode || visitCrossEdgeTree || visitSpecialNodes) {
    if (safeMode) {
      if (visitedNodes[node.getId()]) { // for safemode
        common::WriteMsg::write(CMSG_THE_PRE_ORDER_HAS_TOUCHED_A_NODE_TWICE,node.getId(),Common::toString(node.getNodeKind()).c_str() );
        return;
      }
    }
    visitedNodes[node.getId()] = true;
  }

  for (std::list<Visitor*>::iterator itVisitors = visitorList.begin();itVisitors != visitorList.end(); ++itVisitors) {
    (*itVisitors)->visit(node);
    incVisitorDepth((**itVisitors));
  }

  clearStoppedVisitors();
  if(needPreorderStop)
    return;

  visitAllEdges(node,true);

  for (std::list<Visitor*>::iterator itVisitors = visitorList.begin();itVisitors != visitorList.end(); ++itVisitors) {
    decVisitorDepth(**itVisitors);
    (*itVisitors)->visitEnd(node);
  }

  clearStoppedVisitors();
}

void AlgorithmPreorder::visitAllEdges(const expression::IfExpression& node, bool callFirst /*= true*/){
  visitAllEdges(dynamic_cast<const expression::Expression&>(node),false);

  std::list<Visitor*>::iterator itVisitors;

  const base::Base* genNodePtr;
  // edge: hasBody
  genNodePtr = node.getBody() ;
  if (genNodePtr) {
    const expression::Expression& endNodeRef = dynamic_cast<const expression::Expression&>(*genNodePtr);
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitIfExpression_HasBody(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;

    if ((!fact->getIsFilterTurnedOn() && !visitFilteredEdge) || (fact->getFilterState(endNodeRef.getId()) == Filter::NotFiltered) || (!originalFilterState && visitFilteredEdge)) {
      if (apRoot && visitUsedSpecialNodesOnly && Common::getIsAPSpecNode(endNodeRef)) {
        unvisitedNodes[endNodeRef.getId()] = true;
      } else {
        endNodeRef.accept(*this);
      }
    }
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitEndIfExpression_HasBody(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;
  }

  // edge: hasElseBody
  genNodePtr = node.getElseBody() ;
  if (genNodePtr) {
    const expression::Expression& endNodeRef = dynamic_cast<const expression::Expression&>(*genNodePtr);
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitIfExpression_HasElseBody(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;

    if ((!fact->getIsFilterTurnedOn() && !visitFilteredEdge) || (fact->getFilterState(endNodeRef.getId()) == Filter::NotFiltered) || (!originalFilterState && visitFilteredEdge)) {
      if (apRoot && visitUsedSpecialNodesOnly && Common::getIsAPSpecNode(endNodeRef)) {
        unvisitedNodes[endNodeRef.getId()] = true;
      } else {
        endNodeRef.accept(*this);
      }
    }
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitEndIfExpression_HasElseBody(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;
  }

  // edge: hasTest
  genNodePtr = node.getTest() ;
  if (genNodePtr) {
    const expression::Expression& endNodeRef = dynamic_cast<const expression::Expression&>(*genNodePtr);
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitIfExpression_HasTest(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;

    if ((!fact->getIsFilterTurnedOn() && !visitFilteredEdge) || (fact->getFilterState(endNodeRef.getId()) == Filter::NotFiltered) || (!originalFilterState && visitFilteredEdge)) {
      if (apRoot && visitUsedSpecialNodesOnly && Common::getIsAPSpecNode(endNodeRef)) {
        unvisitedNodes[endNodeRef.getId()] = true;
      } else {
        endNodeRef.accept(*this);
      }
    }
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitEndIfExpression_HasTest(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;
  }
}

void AlgorithmPreorder::visit(const expression::IfExpression& node, bool callFirst /*= true*/){
#ifdef DEBUG_PREORDER
  std::cout << "Rec. run: " << (unsigned int)&node << " " << node.getId() << " " << Common::toString(node.getNodeKind()) << std::endl;
#endif
  if (safeMode || visitCrossEdgeTree || visitSpecialNodes) {
    if (safeMode) {
      if (visitedNodes[node.getId()]) { // for safemode
        common::WriteMsg::write(CMSG_THE_PRE_ORDER_HAS_TOUCHED_A_NODE_TWICE,node.getId(),Common::toString(node.getNodeKind()).c_str() );
        return;
      }
    }
    visitedNodes[node.getId()] = true;
  }

  for (std::list<Visitor*>::iterator itVisitors = visitorList.begin();itVisitors != visitorList.end(); ++itVisitors) {
    (*itVisitors)->visit(node);
    incVisitorDepth((**itVisitors));
  }

  clearStoppedVisitors();
  if(needPreorderStop)
    return;

  visitAllEdges(node,true);

  for (std::list<Visitor*>::iterator itVisitors = visitorList.begin();itVisitors != visitorList.end(); ++itVisitors) {
    decVisitorDepth(**itVisitors);
    (*itVisitors)->visitEnd(node);
  }

  clearStoppedVisitors();
}

void AlgorithmPreorder::visitAllEdges(const expression::ImagNumber& node, bool callFirst /*= true*/){
  visitAllEdges(dynamic_cast<const expression::Literal&>(node),false);
}

void AlgorithmPreorder::visit(const expression::ImagNumber& node, bool callFirst /*= true*/){
#ifdef DEBUG_PREORDER
  std::cout << "Rec. run: " << (unsigned int)&node << " " << node.getId() << " " << Common::toString(node.getNodeKind()) << std::endl;
#endif
  if (safeMode || visitCrossEdgeTree || visitSpecialNodes) {
    if (safeMode) {
      if (visitedNodes[node.getId()]) { // for safemode
        common::WriteMsg::write(CMSG_THE_PRE_ORDER_HAS_TOUCHED_A_NODE_TWICE,node.getId(),Common::toString(node.getNodeKind()).c_str() );
        return;
      }
    }
    visitedNodes[node.getId()] = true;
  }

  for (std::list<Visitor*>::iterator itVisitors = visitorList.begin();itVisitors != visitorList.end(); ++itVisitors) {
    (*itVisitors)->visit(node);
    incVisitorDepth((**itVisitors));
  }

  clearStoppedVisitors();
  if(needPreorderStop)
    return;

  visitAllEdges(node,true);

  for (std::list<Visitor*>::iterator itVisitors = visitorList.begin();itVisitors != visitorList.end(); ++itVisitors) {
    decVisitorDepth(**itVisitors);
    (*itVisitors)->visitEnd(node);
  }

  clearStoppedVisitors();
}

void AlgorithmPreorder::visitAllEdges(const expression::Index& node, bool callFirst /*= true*/){
  visitAllEdges(dynamic_cast<const expression::Slicing&>(node),false);
}

void AlgorithmPreorder::visit(const expression::Index& node, bool callFirst /*= true*/){
#ifdef DEBUG_PREORDER
  std::cout << "Rec. run: " << (unsigned int)&node << " " << node.getId() << " " << Common::toString(node.getNodeKind()) << std::endl;
#endif
  if (safeMode || visitCrossEdgeTree || visitSpecialNodes) {
    if (safeMode) {
      if (visitedNodes[node.getId()]) { // for safemode
        common::WriteMsg::write(CMSG_THE_PRE_ORDER_HAS_TOUCHED_A_NODE_TWICE,node.getId(),Common::toString(node.getNodeKind()).c_str() );
        return;
      }
    }
    visitedNodes[node.getId()] = true;
  }

  for (std::list<Visitor*>::iterator itVisitors = visitorList.begin();itVisitors != visitorList.end(); ++itVisitors) {
    (*itVisitors)->visit(node);
    incVisitorDepth((**itVisitors));
  }

  clearStoppedVisitors();
  if(needPreorderStop)
    return;

  visitAllEdges(node,true);

  for (std::list<Visitor*>::iterator itVisitors = visitorList.begin();itVisitors != visitorList.end(); ++itVisitors) {
    decVisitorDepth(**itVisitors);
    (*itVisitors)->visitEnd(node);
  }

  clearStoppedVisitors();
}

void AlgorithmPreorder::visitAllEdges(const expression::IntegerLiteral& node, bool callFirst /*= true*/){
  visitAllEdges(dynamic_cast<const expression::Literal&>(node),false);
}

void AlgorithmPreorder::visit(const expression::IntegerLiteral& node, bool callFirst /*= true*/){
#ifdef DEBUG_PREORDER
  std::cout << "Rec. run: " << (unsigned int)&node << " " << node.getId() << " " << Common::toString(node.getNodeKind()) << std::endl;
#endif
  if (safeMode || visitCrossEdgeTree || visitSpecialNodes) {
    if (safeMode) {
      if (visitedNodes[node.getId()]) { // for safemode
        common::WriteMsg::write(CMSG_THE_PRE_ORDER_HAS_TOUCHED_A_NODE_TWICE,node.getId(),Common::toString(node.getNodeKind()).c_str() );
        return;
      }
    }
    visitedNodes[node.getId()] = true;
  }

  for (std::list<Visitor*>::iterator itVisitors = visitorList.begin();itVisitors != visitorList.end(); ++itVisitors) {
    (*itVisitors)->visit(node);
    incVisitorDepth((**itVisitors));
  }

  clearStoppedVisitors();
  if(needPreorderStop)
    return;

  visitAllEdges(node,true);

  for (std::list<Visitor*>::iterator itVisitors = visitorList.begin();itVisitors != visitorList.end(); ++itVisitors) {
    decVisitorDepth(**itVisitors);
    (*itVisitors)->visitEnd(node);
  }

  clearStoppedVisitors();
}

void AlgorithmPreorder::visitAllEdges(const expression::KeyValue& node, bool callFirst /*= true*/){
  visitAllEdges(dynamic_cast<const base::Positioned&>(node),false);

  std::list<Visitor*>::iterator itVisitors;

  const base::Base* genNodePtr;
  // edge: hasKey
  genNodePtr = node.getKey() ;
  if (genNodePtr) {
    const expression::Expression& endNodeRef = dynamic_cast<const expression::Expression&>(*genNodePtr);
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitKeyValue_HasKey(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;

    if ((!fact->getIsFilterTurnedOn() && !visitFilteredEdge) || (fact->getFilterState(endNodeRef.getId()) == Filter::NotFiltered) || (!originalFilterState && visitFilteredEdge)) {
      if (apRoot && visitUsedSpecialNodesOnly && Common::getIsAPSpecNode(endNodeRef)) {
        unvisitedNodes[endNodeRef.getId()] = true;
      } else {
        endNodeRef.accept(*this);
      }
    }
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitEndKeyValue_HasKey(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;
  }

  // edge: hasValue
  genNodePtr = node.getValue() ;
  if (genNodePtr) {
    const expression::Expression& endNodeRef = dynamic_cast<const expression::Expression&>(*genNodePtr);
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitKeyValue_HasValue(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;

    if ((!fact->getIsFilterTurnedOn() && !visitFilteredEdge) || (fact->getFilterState(endNodeRef.getId()) == Filter::NotFiltered) || (!originalFilterState && visitFilteredEdge)) {
      if (apRoot && visitUsedSpecialNodesOnly && Common::getIsAPSpecNode(endNodeRef)) {
        unvisitedNodes[endNodeRef.getId()] = true;
      } else {
        endNodeRef.accept(*this);
      }
    }
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitEndKeyValue_HasValue(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;
  }
}

void AlgorithmPreorder::visit(const expression::KeyValue& node, bool callFirst /*= true*/){
#ifdef DEBUG_PREORDER
  std::cout << "Rec. run: " << (unsigned int)&node << " " << node.getId() << " " << Common::toString(node.getNodeKind()) << std::endl;
#endif
  if (safeMode || visitCrossEdgeTree || visitSpecialNodes) {
    if (safeMode) {
      if (visitedNodes[node.getId()]) { // for safemode
        common::WriteMsg::write(CMSG_THE_PRE_ORDER_HAS_TOUCHED_A_NODE_TWICE,node.getId(),Common::toString(node.getNodeKind()).c_str() );
        return;
      }
    }
    visitedNodes[node.getId()] = true;
  }

  for (std::list<Visitor*>::iterator itVisitors = visitorList.begin();itVisitors != visitorList.end(); ++itVisitors) {
    (*itVisitors)->visit(node);
    incVisitorDepth((**itVisitors));
  }

  clearStoppedVisitors();
  if(needPreorderStop)
    return;

  visitAllEdges(node,true);

  for (std::list<Visitor*>::iterator itVisitors = visitorList.begin();itVisitors != visitorList.end(); ++itVisitors) {
    decVisitorDepth(**itVisitors);
    (*itVisitors)->visitEnd(node);
  }

  clearStoppedVisitors();
}

void AlgorithmPreorder::visitAllEdges(const expression::Keyword& node, bool callFirst /*= true*/){
  visitAllEdges(dynamic_cast<const base::Positioned&>(node),false);

  std::list<Visitor*>::iterator itVisitors;

  const base::Base* genNodePtr;
  // edge: hasKey
  genNodePtr = node.getKey() ;
  if (genNodePtr) {
    const expression::Identifier& endNodeRef = dynamic_cast<const expression::Identifier&>(*genNodePtr);
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitKeyword_HasKey(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;

    if ((!fact->getIsFilterTurnedOn() && !visitFilteredEdge) || (fact->getFilterState(endNodeRef.getId()) == Filter::NotFiltered) || (!originalFilterState && visitFilteredEdge)) {
      if (apRoot && visitUsedSpecialNodesOnly && Common::getIsAPSpecNode(endNodeRef)) {
        unvisitedNodes[endNodeRef.getId()] = true;
      } else {
        endNodeRef.accept(*this);
      }
    }
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitEndKeyword_HasKey(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;
  }

  // edge: hasValue
  genNodePtr = node.getValue() ;
  if (genNodePtr) {
    const expression::Expression& endNodeRef = dynamic_cast<const expression::Expression&>(*genNodePtr);
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitKeyword_HasValue(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;

    if ((!fact->getIsFilterTurnedOn() && !visitFilteredEdge) || (fact->getFilterState(endNodeRef.getId()) == Filter::NotFiltered) || (!originalFilterState && visitFilteredEdge)) {
      if (apRoot && visitUsedSpecialNodesOnly && Common::getIsAPSpecNode(endNodeRef)) {
        unvisitedNodes[endNodeRef.getId()] = true;
      } else {
        endNodeRef.accept(*this);
      }
    }
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitEndKeyword_HasValue(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;
  }
}

void AlgorithmPreorder::visit(const expression::Keyword& node, bool callFirst /*= true*/){
#ifdef DEBUG_PREORDER
  std::cout << "Rec. run: " << (unsigned int)&node << " " << node.getId() << " " << Common::toString(node.getNodeKind()) << std::endl;
#endif
  if (safeMode || visitCrossEdgeTree || visitSpecialNodes) {
    if (safeMode) {
      if (visitedNodes[node.getId()]) { // for safemode
        common::WriteMsg::write(CMSG_THE_PRE_ORDER_HAS_TOUCHED_A_NODE_TWICE,node.getId(),Common::toString(node.getNodeKind()).c_str() );
        return;
      }
    }
    visitedNodes[node.getId()] = true;
  }

  for (std::list<Visitor*>::iterator itVisitors = visitorList.begin();itVisitors != visitorList.end(); ++itVisitors) {
    (*itVisitors)->visit(node);
    incVisitorDepth((**itVisitors));
  }

  clearStoppedVisitors();
  if(needPreorderStop)
    return;

  visitAllEdges(node,true);

  for (std::list<Visitor*>::iterator itVisitors = visitorList.begin();itVisitors != visitorList.end(); ++itVisitors) {
    decVisitorDepth(**itVisitors);
    (*itVisitors)->visitEnd(node);
  }

  clearStoppedVisitors();
}

void AlgorithmPreorder::visitAllEdges(const expression::Lambda& node, bool callFirst /*= true*/){
  visitAllEdges(dynamic_cast<const expression::Expression&>(node),false);

  std::list<Visitor*>::iterator itVisitors;

  // edge: hasObject
  for (ListIterator<module::Object> it = node.getObjectListIteratorBegin(); it != node.getObjectListIteratorEnd(); ++it) {
    const module::Object& endNodeRef = *it;
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitLambda_HasObject(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;

    if ((!fact->getIsFilterTurnedOn() && !visitFilteredEdge) || (fact->getFilterState(endNodeRef.getId()) == Filter::NotFiltered) || (!originalFilterState && visitFilteredEdge)) {
      if (apRoot && visitUsedSpecialNodesOnly && Common::getIsAPSpecNode(endNodeRef)) {
        unvisitedNodes[endNodeRef.getId()] = true;
      } else {
        endNodeRef.accept(*this);
      }
    }
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitEndLambda_HasObject(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;
  }

  // edge: hasParameter
  for (ListIterator<statement::Parameter> it = node.getParameterListIteratorBegin(); it != node.getParameterListIteratorEnd(); ++it) {
    const statement::Parameter& endNodeRef = *it;
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitLambda_HasParameter(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;

    if ((!fact->getIsFilterTurnedOn() && !visitFilteredEdge) || (fact->getFilterState(endNodeRef.getId()) == Filter::NotFiltered) || (!originalFilterState && visitFilteredEdge)) {
      if (apRoot && visitUsedSpecialNodesOnly && Common::getIsAPSpecNode(endNodeRef)) {
        unvisitedNodes[endNodeRef.getId()] = true;
      } else {
        endNodeRef.accept(*this);
      }
    }
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitEndLambda_HasParameter(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;
  }

  const base::Base* genNodePtr;
  // edge: hasExpression
  genNodePtr = node.getExpression() ;
  if (genNodePtr) {
    const expression::Expression& endNodeRef = dynamic_cast<const expression::Expression&>(*genNodePtr);
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitLambda_HasExpression(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;

    if ((!fact->getIsFilterTurnedOn() && !visitFilteredEdge) || (fact->getFilterState(endNodeRef.getId()) == Filter::NotFiltered) || (!originalFilterState && visitFilteredEdge)) {
      if (apRoot && visitUsedSpecialNodesOnly && Common::getIsAPSpecNode(endNodeRef)) {
        unvisitedNodes[endNodeRef.getId()] = true;
      } else {
        endNodeRef.accept(*this);
      }
    }
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitEndLambda_HasExpression(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;
  }
}

void AlgorithmPreorder::visit(const expression::Lambda& node, bool callFirst /*= true*/){
#ifdef DEBUG_PREORDER
  std::cout << "Rec. run: " << (unsigned int)&node << " " << node.getId() << " " << Common::toString(node.getNodeKind()) << std::endl;
#endif
  if (safeMode || visitCrossEdgeTree || visitSpecialNodes) {
    if (safeMode) {
      if (visitedNodes[node.getId()]) { // for safemode
        common::WriteMsg::write(CMSG_THE_PRE_ORDER_HAS_TOUCHED_A_NODE_TWICE,node.getId(),Common::toString(node.getNodeKind()).c_str() );
        return;
      }
    }
    visitedNodes[node.getId()] = true;
  }

  for (std::list<Visitor*>::iterator itVisitors = visitorList.begin();itVisitors != visitorList.end(); ++itVisitors) {
    (*itVisitors)->visit(node);
    incVisitorDepth((**itVisitors));
  }

  clearStoppedVisitors();
  if(needPreorderStop)
    return;

  visitAllEdges(node,true);

  for (std::list<Visitor*>::iterator itVisitors = visitorList.begin();itVisitors != visitorList.end(); ++itVisitors) {
    decVisitorDepth(**itVisitors);
    (*itVisitors)->visitEnd(node);
  }

  clearStoppedVisitors();
}

void AlgorithmPreorder::visitAllEdges(const expression::List& node, bool callFirst /*= true*/){
  visitAllEdges(dynamic_cast<const expression::Expression&>(node),false);

  std::list<Visitor*>::iterator itVisitors;

  // edge: hasExpression
  for (ListIterator<expression::Expression> it = node.getExpressionListIteratorBegin(); it != node.getExpressionListIteratorEnd(); ++it) {
    const expression::Expression& endNodeRef = *it;
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitList_HasExpression(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;

    if ((!fact->getIsFilterTurnedOn() && !visitFilteredEdge) || (fact->getFilterState(endNodeRef.getId()) == Filter::NotFiltered) || (!originalFilterState && visitFilteredEdge)) {
      if (apRoot && visitUsedSpecialNodesOnly && Common::getIsAPSpecNode(endNodeRef)) {
        unvisitedNodes[endNodeRef.getId()] = true;
      } else {
        endNodeRef.accept(*this);
      }
    }
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitEndList_HasExpression(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;
  }
}

void AlgorithmPreorder::visit(const expression::List& node, bool callFirst /*= true*/){
#ifdef DEBUG_PREORDER
  std::cout << "Rec. run: " << (unsigned int)&node << " " << node.getId() << " " << Common::toString(node.getNodeKind()) << std::endl;
#endif
  if (safeMode || visitCrossEdgeTree || visitSpecialNodes) {
    if (safeMode) {
      if (visitedNodes[node.getId()]) { // for safemode
        common::WriteMsg::write(CMSG_THE_PRE_ORDER_HAS_TOUCHED_A_NODE_TWICE,node.getId(),Common::toString(node.getNodeKind()).c_str() );
        return;
      }
    }
    visitedNodes[node.getId()] = true;
  }

  for (std::list<Visitor*>::iterator itVisitors = visitorList.begin();itVisitors != visitorList.end(); ++itVisitors) {
    (*itVisitors)->visit(node);
    incVisitorDepth((**itVisitors));
  }

  clearStoppedVisitors();
  if(needPreorderStop)
    return;

  visitAllEdges(node,true);

  for (std::list<Visitor*>::iterator itVisitors = visitorList.begin();itVisitors != visitorList.end(); ++itVisitors) {
    decVisitorDepth(**itVisitors);
    (*itVisitors)->visitEnd(node);
  }

  clearStoppedVisitors();
}

void AlgorithmPreorder::visitAllEdges(const expression::ListComp& node, bool callFirst /*= true*/){
  visitAllEdges(dynamic_cast<const expression::Expression&>(node),false);

  std::list<Visitor*>::iterator itVisitors;

  const base::Base* genNodePtr;
  // edge: hasExpression
  genNodePtr = node.getExpression() ;
  if (genNodePtr) {
    const expression::Expression& endNodeRef = dynamic_cast<const expression::Expression&>(*genNodePtr);
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitListComp_HasExpression(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;

    if ((!fact->getIsFilterTurnedOn() && !visitFilteredEdge) || (fact->getFilterState(endNodeRef.getId()) == Filter::NotFiltered) || (!originalFilterState && visitFilteredEdge)) {
      if (apRoot && visitUsedSpecialNodesOnly && Common::getIsAPSpecNode(endNodeRef)) {
        unvisitedNodes[endNodeRef.getId()] = true;
      } else {
        endNodeRef.accept(*this);
      }
    }
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitEndListComp_HasExpression(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;
  }

  // edge: hasGenerator
  for (ListIterator<expression::Generator> it = node.getGeneratorListIteratorBegin(); it != node.getGeneratorListIteratorEnd(); ++it) {
    const expression::Generator& endNodeRef = *it;
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitListComp_HasGenerator(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;

    if ((!fact->getIsFilterTurnedOn() && !visitFilteredEdge) || (fact->getFilterState(endNodeRef.getId()) == Filter::NotFiltered) || (!originalFilterState && visitFilteredEdge)) {
      if (apRoot && visitUsedSpecialNodesOnly && Common::getIsAPSpecNode(endNodeRef)) {
        unvisitedNodes[endNodeRef.getId()] = true;
      } else {
        endNodeRef.accept(*this);
      }
    }
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitEndListComp_HasGenerator(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;
  }
}

void AlgorithmPreorder::visit(const expression::ListComp& node, bool callFirst /*= true*/){
#ifdef DEBUG_PREORDER
  std::cout << "Rec. run: " << (unsigned int)&node << " " << node.getId() << " " << Common::toString(node.getNodeKind()) << std::endl;
#endif
  if (safeMode || visitCrossEdgeTree || visitSpecialNodes) {
    if (safeMode) {
      if (visitedNodes[node.getId()]) { // for safemode
        common::WriteMsg::write(CMSG_THE_PRE_ORDER_HAS_TOUCHED_A_NODE_TWICE,node.getId(),Common::toString(node.getNodeKind()).c_str() );
        return;
      }
    }
    visitedNodes[node.getId()] = true;
  }

  for (std::list<Visitor*>::iterator itVisitors = visitorList.begin();itVisitors != visitorList.end(); ++itVisitors) {
    (*itVisitors)->visit(node);
    incVisitorDepth((**itVisitors));
  }

  clearStoppedVisitors();
  if(needPreorderStop)
    return;

  visitAllEdges(node,true);

  for (std::list<Visitor*>::iterator itVisitors = visitorList.begin();itVisitors != visitorList.end(); ++itVisitors) {
    decVisitorDepth(**itVisitors);
    (*itVisitors)->visitEnd(node);
  }

  clearStoppedVisitors();
}

void AlgorithmPreorder::visitAllEdges(const expression::Literal& node, bool callFirst /*= true*/){
  visitAllEdges(dynamic_cast<const expression::Expression&>(node),false);
}

void AlgorithmPreorder::visitAllEdges(const expression::LongInteger& node, bool callFirst /*= true*/){
  visitAllEdges(dynamic_cast<const expression::Literal&>(node),false);
}

void AlgorithmPreorder::visit(const expression::LongInteger& node, bool callFirst /*= true*/){
#ifdef DEBUG_PREORDER
  std::cout << "Rec. run: " << (unsigned int)&node << " " << node.getId() << " " << Common::toString(node.getNodeKind()) << std::endl;
#endif
  if (safeMode || visitCrossEdgeTree || visitSpecialNodes) {
    if (safeMode) {
      if (visitedNodes[node.getId()]) { // for safemode
        common::WriteMsg::write(CMSG_THE_PRE_ORDER_HAS_TOUCHED_A_NODE_TWICE,node.getId(),Common::toString(node.getNodeKind()).c_str() );
        return;
      }
    }
    visitedNodes[node.getId()] = true;
  }

  for (std::list<Visitor*>::iterator itVisitors = visitorList.begin();itVisitors != visitorList.end(); ++itVisitors) {
    (*itVisitors)->visit(node);
    incVisitorDepth((**itVisitors));
  }

  clearStoppedVisitors();
  if(needPreorderStop)
    return;

  visitAllEdges(node,true);

  for (std::list<Visitor*>::iterator itVisitors = visitorList.begin();itVisitors != visitorList.end(); ++itVisitors) {
    decVisitorDepth(**itVisitors);
    (*itVisitors)->visitEnd(node);
  }

  clearStoppedVisitors();
}

void AlgorithmPreorder::visitAllEdges(const expression::Set& node, bool callFirst /*= true*/){
  visitAllEdges(dynamic_cast<const expression::Expression&>(node),false);

  std::list<Visitor*>::iterator itVisitors;

  // edge: hasExpression
  for (ListIterator<expression::Expression> it = node.getExpressionListIteratorBegin(); it != node.getExpressionListIteratorEnd(); ++it) {
    const expression::Expression& endNodeRef = *it;
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitSet_HasExpression(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;

    if ((!fact->getIsFilterTurnedOn() && !visitFilteredEdge) || (fact->getFilterState(endNodeRef.getId()) == Filter::NotFiltered) || (!originalFilterState && visitFilteredEdge)) {
      if (apRoot && visitUsedSpecialNodesOnly && Common::getIsAPSpecNode(endNodeRef)) {
        unvisitedNodes[endNodeRef.getId()] = true;
      } else {
        endNodeRef.accept(*this);
      }
    }
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitEndSet_HasExpression(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;
  }
}

void AlgorithmPreorder::visit(const expression::Set& node, bool callFirst /*= true*/){
#ifdef DEBUG_PREORDER
  std::cout << "Rec. run: " << (unsigned int)&node << " " << node.getId() << " " << Common::toString(node.getNodeKind()) << std::endl;
#endif
  if (safeMode || visitCrossEdgeTree || visitSpecialNodes) {
    if (safeMode) {
      if (visitedNodes[node.getId()]) { // for safemode
        common::WriteMsg::write(CMSG_THE_PRE_ORDER_HAS_TOUCHED_A_NODE_TWICE,node.getId(),Common::toString(node.getNodeKind()).c_str() );
        return;
      }
    }
    visitedNodes[node.getId()] = true;
  }

  for (std::list<Visitor*>::iterator itVisitors = visitorList.begin();itVisitors != visitorList.end(); ++itVisitors) {
    (*itVisitors)->visit(node);
    incVisitorDepth((**itVisitors));
  }

  clearStoppedVisitors();
  if(needPreorderStop)
    return;

  visitAllEdges(node,true);

  for (std::list<Visitor*>::iterator itVisitors = visitorList.begin();itVisitors != visitorList.end(); ++itVisitors) {
    decVisitorDepth(**itVisitors);
    (*itVisitors)->visitEnd(node);
  }

  clearStoppedVisitors();
}

void AlgorithmPreorder::visitAllEdges(const expression::SetComp& node, bool callFirst /*= true*/){
  visitAllEdges(dynamic_cast<const expression::Expression&>(node),false);

  std::list<Visitor*>::iterator itVisitors;

  const base::Base* genNodePtr;
  // edge: hasExpression
  genNodePtr = node.getExpression() ;
  if (genNodePtr) {
    const expression::Expression& endNodeRef = dynamic_cast<const expression::Expression&>(*genNodePtr);
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitSetComp_HasExpression(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;

    if ((!fact->getIsFilterTurnedOn() && !visitFilteredEdge) || (fact->getFilterState(endNodeRef.getId()) == Filter::NotFiltered) || (!originalFilterState && visitFilteredEdge)) {
      if (apRoot && visitUsedSpecialNodesOnly && Common::getIsAPSpecNode(endNodeRef)) {
        unvisitedNodes[endNodeRef.getId()] = true;
      } else {
        endNodeRef.accept(*this);
      }
    }
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitEndSetComp_HasExpression(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;
  }

  // edge: hasGenerator
  for (ListIterator<expression::Generator> it = node.getGeneratorListIteratorBegin(); it != node.getGeneratorListIteratorEnd(); ++it) {
    const expression::Generator& endNodeRef = *it;
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitSetComp_HasGenerator(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;

    if ((!fact->getIsFilterTurnedOn() && !visitFilteredEdge) || (fact->getFilterState(endNodeRef.getId()) == Filter::NotFiltered) || (!originalFilterState && visitFilteredEdge)) {
      if (apRoot && visitUsedSpecialNodesOnly && Common::getIsAPSpecNode(endNodeRef)) {
        unvisitedNodes[endNodeRef.getId()] = true;
      } else {
        endNodeRef.accept(*this);
      }
    }
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitEndSetComp_HasGenerator(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;
  }
}

void AlgorithmPreorder::visit(const expression::SetComp& node, bool callFirst /*= true*/){
#ifdef DEBUG_PREORDER
  std::cout << "Rec. run: " << (unsigned int)&node << " " << node.getId() << " " << Common::toString(node.getNodeKind()) << std::endl;
#endif
  if (safeMode || visitCrossEdgeTree || visitSpecialNodes) {
    if (safeMode) {
      if (visitedNodes[node.getId()]) { // for safemode
        common::WriteMsg::write(CMSG_THE_PRE_ORDER_HAS_TOUCHED_A_NODE_TWICE,node.getId(),Common::toString(node.getNodeKind()).c_str() );
        return;
      }
    }
    visitedNodes[node.getId()] = true;
  }

  for (std::list<Visitor*>::iterator itVisitors = visitorList.begin();itVisitors != visitorList.end(); ++itVisitors) {
    (*itVisitors)->visit(node);
    incVisitorDepth((**itVisitors));
  }

  clearStoppedVisitors();
  if(needPreorderStop)
    return;

  visitAllEdges(node,true);

  for (std::list<Visitor*>::iterator itVisitors = visitorList.begin();itVisitors != visitorList.end(); ++itVisitors) {
    decVisitorDepth(**itVisitors);
    (*itVisitors)->visitEnd(node);
  }

  clearStoppedVisitors();
}

void AlgorithmPreorder::visitAllEdges(const expression::Slice& node, bool callFirst /*= true*/){
  visitAllEdges(dynamic_cast<const expression::Slicing&>(node),false);

  std::list<Visitor*>::iterator itVisitors;

  const base::Base* genNodePtr;
  // edge: hasLowerBound
  genNodePtr = node.getLowerBound() ;
  if (genNodePtr) {
    const expression::Expression& endNodeRef = dynamic_cast<const expression::Expression&>(*genNodePtr);
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitSlice_HasLowerBound(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;

    if ((!fact->getIsFilterTurnedOn() && !visitFilteredEdge) || (fact->getFilterState(endNodeRef.getId()) == Filter::NotFiltered) || (!originalFilterState && visitFilteredEdge)) {
      if (apRoot && visitUsedSpecialNodesOnly && Common::getIsAPSpecNode(endNodeRef)) {
        unvisitedNodes[endNodeRef.getId()] = true;
      } else {
        endNodeRef.accept(*this);
      }
    }
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitEndSlice_HasLowerBound(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;
  }

  // edge: hasStride
  genNodePtr = node.getStride() ;
  if (genNodePtr) {
    const expression::Expression& endNodeRef = dynamic_cast<const expression::Expression&>(*genNodePtr);
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitSlice_HasStride(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;

    if ((!fact->getIsFilterTurnedOn() && !visitFilteredEdge) || (fact->getFilterState(endNodeRef.getId()) == Filter::NotFiltered) || (!originalFilterState && visitFilteredEdge)) {
      if (apRoot && visitUsedSpecialNodesOnly && Common::getIsAPSpecNode(endNodeRef)) {
        unvisitedNodes[endNodeRef.getId()] = true;
      } else {
        endNodeRef.accept(*this);
      }
    }
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitEndSlice_HasStride(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;
  }

  // edge: hasUpperBound
  genNodePtr = node.getUpperBound() ;
  if (genNodePtr) {
    const expression::Expression& endNodeRef = dynamic_cast<const expression::Expression&>(*genNodePtr);
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitSlice_HasUpperBound(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;

    if ((!fact->getIsFilterTurnedOn() && !visitFilteredEdge) || (fact->getFilterState(endNodeRef.getId()) == Filter::NotFiltered) || (!originalFilterState && visitFilteredEdge)) {
      if (apRoot && visitUsedSpecialNodesOnly && Common::getIsAPSpecNode(endNodeRef)) {
        unvisitedNodes[endNodeRef.getId()] = true;
      } else {
        endNodeRef.accept(*this);
      }
    }
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitEndSlice_HasUpperBound(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;
  }
}

void AlgorithmPreorder::visit(const expression::Slice& node, bool callFirst /*= true*/){
#ifdef DEBUG_PREORDER
  std::cout << "Rec. run: " << (unsigned int)&node << " " << node.getId() << " " << Common::toString(node.getNodeKind()) << std::endl;
#endif
  if (safeMode || visitCrossEdgeTree || visitSpecialNodes) {
    if (safeMode) {
      if (visitedNodes[node.getId()]) { // for safemode
        common::WriteMsg::write(CMSG_THE_PRE_ORDER_HAS_TOUCHED_A_NODE_TWICE,node.getId(),Common::toString(node.getNodeKind()).c_str() );
        return;
      }
    }
    visitedNodes[node.getId()] = true;
  }

  for (std::list<Visitor*>::iterator itVisitors = visitorList.begin();itVisitors != visitorList.end(); ++itVisitors) {
    (*itVisitors)->visit(node);
    incVisitorDepth((**itVisitors));
  }

  clearStoppedVisitors();
  if(needPreorderStop)
    return;

  visitAllEdges(node,true);

  for (std::list<Visitor*>::iterator itVisitors = visitorList.begin();itVisitors != visitorList.end(); ++itVisitors) {
    decVisitorDepth(**itVisitors);
    (*itVisitors)->visitEnd(node);
  }

  clearStoppedVisitors();
}

void AlgorithmPreorder::visitAllEdges(const expression::Slicing& node, bool callFirst /*= true*/){
  visitAllEdges(dynamic_cast<const expression::Unary&>(node),false);
}

void AlgorithmPreorder::visitAllEdges(const expression::StringConversion& node, bool callFirst /*= true*/){
  visitAllEdges(dynamic_cast<const expression::Expression&>(node),false);

  std::list<Visitor*>::iterator itVisitors;

  const base::Base* genNodePtr;
  // edge: hasExpressionList
  genNodePtr = node.getExpressionList() ;
  if (genNodePtr) {
    const expression::ExpressionList& endNodeRef = dynamic_cast<const expression::ExpressionList&>(*genNodePtr);
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitStringConversion_HasExpressionList(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;

    if ((!fact->getIsFilterTurnedOn() && !visitFilteredEdge) || (fact->getFilterState(endNodeRef.getId()) == Filter::NotFiltered) || (!originalFilterState && visitFilteredEdge)) {
      if (apRoot && visitUsedSpecialNodesOnly && Common::getIsAPSpecNode(endNodeRef)) {
        unvisitedNodes[endNodeRef.getId()] = true;
      } else {
        endNodeRef.accept(*this);
      }
    }
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitEndStringConversion_HasExpressionList(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;
  }
}

void AlgorithmPreorder::visit(const expression::StringConversion& node, bool callFirst /*= true*/){
#ifdef DEBUG_PREORDER
  std::cout << "Rec. run: " << (unsigned int)&node << " " << node.getId() << " " << Common::toString(node.getNodeKind()) << std::endl;
#endif
  if (safeMode || visitCrossEdgeTree || visitSpecialNodes) {
    if (safeMode) {
      if (visitedNodes[node.getId()]) { // for safemode
        common::WriteMsg::write(CMSG_THE_PRE_ORDER_HAS_TOUCHED_A_NODE_TWICE,node.getId(),Common::toString(node.getNodeKind()).c_str() );
        return;
      }
    }
    visitedNodes[node.getId()] = true;
  }

  for (std::list<Visitor*>::iterator itVisitors = visitorList.begin();itVisitors != visitorList.end(); ++itVisitors) {
    (*itVisitors)->visit(node);
    incVisitorDepth((**itVisitors));
  }

  clearStoppedVisitors();
  if(needPreorderStop)
    return;

  visitAllEdges(node,true);

  for (std::list<Visitor*>::iterator itVisitors = visitorList.begin();itVisitors != visitorList.end(); ++itVisitors) {
    decVisitorDepth(**itVisitors);
    (*itVisitors)->visitEnd(node);
  }

  clearStoppedVisitors();
}

void AlgorithmPreorder::visitAllEdges(const expression::StringLiteral& node, bool callFirst /*= true*/){
  visitAllEdges(dynamic_cast<const expression::Literal&>(node),false);
}

void AlgorithmPreorder::visit(const expression::StringLiteral& node, bool callFirst /*= true*/){
#ifdef DEBUG_PREORDER
  std::cout << "Rec. run: " << (unsigned int)&node << " " << node.getId() << " " << Common::toString(node.getNodeKind()) << std::endl;
#endif
  if (safeMode || visitCrossEdgeTree || visitSpecialNodes) {
    if (safeMode) {
      if (visitedNodes[node.getId()]) { // for safemode
        common::WriteMsg::write(CMSG_THE_PRE_ORDER_HAS_TOUCHED_A_NODE_TWICE,node.getId(),Common::toString(node.getNodeKind()).c_str() );
        return;
      }
    }
    visitedNodes[node.getId()] = true;
  }

  for (std::list<Visitor*>::iterator itVisitors = visitorList.begin();itVisitors != visitorList.end(); ++itVisitors) {
    (*itVisitors)->visit(node);
    incVisitorDepth((**itVisitors));
  }

  clearStoppedVisitors();
  if(needPreorderStop)
    return;

  visitAllEdges(node,true);

  for (std::list<Visitor*>::iterator itVisitors = visitorList.begin();itVisitors != visitorList.end(); ++itVisitors) {
    decVisitorDepth(**itVisitors);
    (*itVisitors)->visitEnd(node);
  }

  clearStoppedVisitors();
}

void AlgorithmPreorder::visitAllEdges(const expression::Subscription& node, bool callFirst /*= true*/){
  visitAllEdges(dynamic_cast<const expression::Unary&>(node),false);

  std::list<Visitor*>::iterator itVisitors;

  const base::Base* genNodePtr;
  // edge: hasSlicing
  genNodePtr = node.getSlicing() ;
  if (genNodePtr) {
    const expression::Slicing& endNodeRef = dynamic_cast<const expression::Slicing&>(*genNodePtr);
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitSubscription_HasSlicing(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;

    if ((!fact->getIsFilterTurnedOn() && !visitFilteredEdge) || (fact->getFilterState(endNodeRef.getId()) == Filter::NotFiltered) || (!originalFilterState && visitFilteredEdge)) {
      if (apRoot && visitUsedSpecialNodesOnly && Common::getIsAPSpecNode(endNodeRef)) {
        unvisitedNodes[endNodeRef.getId()] = true;
      } else {
        endNodeRef.accept(*this);
      }
    }
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitEndSubscription_HasSlicing(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;
  }
}

void AlgorithmPreorder::visit(const expression::Subscription& node, bool callFirst /*= true*/){
#ifdef DEBUG_PREORDER
  std::cout << "Rec. run: " << (unsigned int)&node << " " << node.getId() << " " << Common::toString(node.getNodeKind()) << std::endl;
#endif
  if (safeMode || visitCrossEdgeTree || visitSpecialNodes) {
    if (safeMode) {
      if (visitedNodes[node.getId()]) { // for safemode
        common::WriteMsg::write(CMSG_THE_PRE_ORDER_HAS_TOUCHED_A_NODE_TWICE,node.getId(),Common::toString(node.getNodeKind()).c_str() );
        return;
      }
    }
    visitedNodes[node.getId()] = true;
  }

  for (std::list<Visitor*>::iterator itVisitors = visitorList.begin();itVisitors != visitorList.end(); ++itVisitors) {
    (*itVisitors)->visit(node);
    incVisitorDepth((**itVisitors));
  }

  clearStoppedVisitors();
  if(needPreorderStop)
    return;

  visitAllEdges(node,true);

  for (std::list<Visitor*>::iterator itVisitors = visitorList.begin();itVisitors != visitorList.end(); ++itVisitors) {
    decVisitorDepth(**itVisitors);
    (*itVisitors)->visitEnd(node);
  }

  clearStoppedVisitors();
}

void AlgorithmPreorder::visitAllEdges(const expression::Unary& node, bool callFirst /*= true*/){
  visitAllEdges(dynamic_cast<const expression::Expression&>(node),false);

  std::list<Visitor*>::iterator itVisitors;

  const base::Base* genNodePtr;
  // edge: hasExpression
  genNodePtr = node.getExpression() ;
  if (genNodePtr) {
    const expression::Expression& endNodeRef = dynamic_cast<const expression::Expression&>(*genNodePtr);
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitUnary_HasExpression(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;

    if ((!fact->getIsFilterTurnedOn() && !visitFilteredEdge) || (fact->getFilterState(endNodeRef.getId()) == Filter::NotFiltered) || (!originalFilterState && visitFilteredEdge)) {
      if (apRoot && visitUsedSpecialNodesOnly && Common::getIsAPSpecNode(endNodeRef)) {
        unvisitedNodes[endNodeRef.getId()] = true;
      } else {
        endNodeRef.accept(*this);
      }
    }
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitEndUnary_HasExpression(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;
  }
}

void AlgorithmPreorder::visitAllEdges(const expression::UnaryOperation& node, bool callFirst /*= true*/){
  visitAllEdges(dynamic_cast<const expression::Unary&>(node),false);
}

void AlgorithmPreorder::visit(const expression::UnaryOperation& node, bool callFirst /*= true*/){
#ifdef DEBUG_PREORDER
  std::cout << "Rec. run: " << (unsigned int)&node << " " << node.getId() << " " << Common::toString(node.getNodeKind()) << std::endl;
#endif
  if (safeMode || visitCrossEdgeTree || visitSpecialNodes) {
    if (safeMode) {
      if (visitedNodes[node.getId()]) { // for safemode
        common::WriteMsg::write(CMSG_THE_PRE_ORDER_HAS_TOUCHED_A_NODE_TWICE,node.getId(),Common::toString(node.getNodeKind()).c_str() );
        return;
      }
    }
    visitedNodes[node.getId()] = true;
  }

  for (std::list<Visitor*>::iterator itVisitors = visitorList.begin();itVisitors != visitorList.end(); ++itVisitors) {
    (*itVisitors)->visit(node);
    incVisitorDepth((**itVisitors));
  }

  clearStoppedVisitors();
  if(needPreorderStop)
    return;

  visitAllEdges(node,true);

  for (std::list<Visitor*>::iterator itVisitors = visitorList.begin();itVisitors != visitorList.end(); ++itVisitors) {
    decVisitorDepth(**itVisitors);
    (*itVisitors)->visitEnd(node);
  }

  clearStoppedVisitors();
}

void AlgorithmPreorder::visitAllEdges(const expression::YieldExpression& node, bool callFirst /*= true*/){
  visitAllEdges(dynamic_cast<const expression::Expression&>(node),false);

  std::list<Visitor*>::iterator itVisitors;

  const base::Base* genNodePtr;
  // edge: hasYieldExpression
  genNodePtr = node.getYieldExpression() ;
  if (genNodePtr) {
    const expression::ExpressionList& endNodeRef = dynamic_cast<const expression::ExpressionList&>(*genNodePtr);
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitYieldExpression_HasYieldExpression(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;

    if ((!fact->getIsFilterTurnedOn() && !visitFilteredEdge) || (fact->getFilterState(endNodeRef.getId()) == Filter::NotFiltered) || (!originalFilterState && visitFilteredEdge)) {
      if (apRoot && visitUsedSpecialNodesOnly && Common::getIsAPSpecNode(endNodeRef)) {
        unvisitedNodes[endNodeRef.getId()] = true;
      } else {
        endNodeRef.accept(*this);
      }
    }
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitEndYieldExpression_HasYieldExpression(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;
  }
}

void AlgorithmPreorder::visit(const expression::YieldExpression& node, bool callFirst /*= true*/){
#ifdef DEBUG_PREORDER
  std::cout << "Rec. run: " << (unsigned int)&node << " " << node.getId() << " " << Common::toString(node.getNodeKind()) << std::endl;
#endif
  if (safeMode || visitCrossEdgeTree || visitSpecialNodes) {
    if (safeMode) {
      if (visitedNodes[node.getId()]) { // for safemode
        common::WriteMsg::write(CMSG_THE_PRE_ORDER_HAS_TOUCHED_A_NODE_TWICE,node.getId(),Common::toString(node.getNodeKind()).c_str() );
        return;
      }
    }
    visitedNodes[node.getId()] = true;
  }

  for (std::list<Visitor*>::iterator itVisitors = visitorList.begin();itVisitors != visitorList.end(); ++itVisitors) {
    (*itVisitors)->visit(node);
    incVisitorDepth((**itVisitors));
  }

  clearStoppedVisitors();
  if(needPreorderStop)
    return;

  visitAllEdges(node,true);

  for (std::list<Visitor*>::iterator itVisitors = visitorList.begin();itVisitors != visitorList.end(); ++itVisitors) {
    decVisitorDepth(**itVisitors);
    (*itVisitors)->visitEnd(node);
  }

  clearStoppedVisitors();
}

void AlgorithmPreorder::visitAllEdges(const module::Module& node, bool callFirst /*= true*/){
  visitAllEdges(dynamic_cast<const base::Named&>(node),false);

  std::list<Visitor*>::iterator itVisitors;

  // edge: hasObject
  for (ListIterator<module::Object> it = node.getObjectListIteratorBegin(); it != node.getObjectListIteratorEnd(); ++it) {
    const module::Object& endNodeRef = *it;
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitModule_HasObject(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;

    if ((!fact->getIsFilterTurnedOn() && !visitFilteredEdge) || (fact->getFilterState(endNodeRef.getId()) == Filter::NotFiltered) || (!originalFilterState && visitFilteredEdge)) {
      if (apRoot && visitUsedSpecialNodesOnly && Common::getIsAPSpecNode(endNodeRef)) {
        unvisitedNodes[endNodeRef.getId()] = true;
      } else {
        endNodeRef.accept(*this);
      }
    }
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitEndModule_HasObject(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;
  }

  // edge: hasStatement
  for (ListIterator<base::Positioned> it = node.getStatementListIteratorBegin(); it != node.getStatementListIteratorEnd(); ++it) {
    const base::Positioned& endNodeRef = *it;
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitModule_HasStatement(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;

    if ((!fact->getIsFilterTurnedOn() && !visitFilteredEdge) || (fact->getFilterState(endNodeRef.getId()) == Filter::NotFiltered) || (!originalFilterState && visitFilteredEdge)) {
      if (apRoot && visitUsedSpecialNodesOnly && Common::getIsAPSpecNode(endNodeRef)) {
        unvisitedNodes[endNodeRef.getId()] = true;
      } else {
        endNodeRef.accept(*this);
      }
    }
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitEndModule_HasStatement(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;
  }

  const base::Base* genNodePtr;
  // edge: docstring
  genNodePtr = node.getDocstring() ;
  if (genNodePtr) {
    const base::Docstring& endNodeRef = dynamic_cast<const base::Docstring&>(*genNodePtr);
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitModule_Docstring(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;

    if ((!fact->getIsFilterTurnedOn() && !visitFilteredEdge) || (fact->getFilterState(endNodeRef.getId()) == Filter::NotFiltered) || (!originalFilterState && visitFilteredEdge)) {
      if (apRoot) {
        if (visitCrossEdgeTree || (visitUsedSpecialNodesOnly && Common::getIsAPSpecNode(endNodeRef))) {
          unvisitedNodes[endNodeRef.getId()] = true;
        }
      }
      if (traversaldCrossEdges[edkModule_Docstring]) {
        endNodeRef.accept(*this);
      }
    }
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitEndModule_Docstring(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;
  }
}

void AlgorithmPreorder::visit(const module::Module& node, bool callFirst /*= true*/){
#ifdef DEBUG_PREORDER
  std::cout << "Rec. run: " << (unsigned int)&node << " " << node.getId() << " " << Common::toString(node.getNodeKind()) << std::endl;
#endif
  if (safeMode || visitCrossEdgeTree || visitSpecialNodes) {
    if (safeMode) {
      if (visitedNodes[node.getId()]) { // for safemode
        common::WriteMsg::write(CMSG_THE_PRE_ORDER_HAS_TOUCHED_A_NODE_TWICE,node.getId(),Common::toString(node.getNodeKind()).c_str() );
        return;
      }
    }
    visitedNodes[node.getId()] = true;
  }

  for (std::list<Visitor*>::iterator itVisitors = visitorList.begin();itVisitors != visitorList.end(); ++itVisitors) {
    (*itVisitors)->visit(node);
    incVisitorDepth((**itVisitors));
  }

  clearStoppedVisitors();
  if(needPreorderStop)
    return;

  visitAllEdges(node,true);

  for (std::list<Visitor*>::iterator itVisitors = visitorList.begin();itVisitors != visitorList.end(); ++itVisitors) {
    decVisitorDepth(**itVisitors);
    (*itVisitors)->visitEnd(node);
  }

  clearStoppedVisitors();
}

void AlgorithmPreorder::visitAllEdges(const module::Object& node, bool callFirst /*= true*/){
  visitAllEdges(dynamic_cast<const base::Base&>(node),false);

  std::list<Visitor*>::iterator itVisitors;

  // edge: refersTo
  for (ListIterator<base::Positioned> it = node.getRefersToListIteratorBegin(); it != node.getRefersToListIteratorEnd(); ++it) {
    const base::Positioned& endNodeRef = *it;
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitObject_RefersTo(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;

    if ((!fact->getIsFilterTurnedOn() && !visitFilteredEdge) || (fact->getFilterState(endNodeRef.getId()) == Filter::NotFiltered) || (!originalFilterState && visitFilteredEdge)) {
      if (apRoot) {
        if (visitCrossEdgeTree || (visitUsedSpecialNodesOnly && Common::getIsAPSpecNode(endNodeRef))) {
          unvisitedNodes[endNodeRef.getId()] = true;
        }
      }
      if (traversaldCrossEdges[edkObject_RefersTo]) {
        endNodeRef.accept(*this);
      }
    }
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitEndObject_RefersTo(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;
  }

  // edge: hasType
  for (ListIterator<type::Type> it = node.getTypeListIteratorBegin(); it != node.getTypeListIteratorEnd(); ++it) {
    const type::Type& endNodeRef = *it;
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitObject_HasType(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;

    if ((!fact->getIsFilterTurnedOn() && !visitFilteredEdge) || (fact->getFilterState(endNodeRef.getId()) == Filter::NotFiltered) || (!originalFilterState && visitFilteredEdge)) {
      if (apRoot) {
        if (visitCrossEdgeTree || (visitUsedSpecialNodesOnly && Common::getIsAPSpecNode(endNodeRef))) {
          unvisitedNodes[endNodeRef.getId()] = true;
        }
      }
      if (traversaldCrossEdges[edkObject_HasType]) {
        endNodeRef.accept(*this);
      }
    }
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitEndObject_HasType(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;
  }
}

void AlgorithmPreorder::visit(const module::Object& node, bool callFirst /*= true*/){
#ifdef DEBUG_PREORDER
  std::cout << "Rec. run: " << (unsigned int)&node << " " << node.getId() << " " << Common::toString(node.getNodeKind()) << std::endl;
#endif
  if (safeMode || visitCrossEdgeTree || visitSpecialNodes) {
    if (safeMode) {
      if (visitedNodes[node.getId()]) { // for safemode
        common::WriteMsg::write(CMSG_THE_PRE_ORDER_HAS_TOUCHED_A_NODE_TWICE,node.getId(),Common::toString(node.getNodeKind()).c_str() );
        return;
      }
    }
    visitedNodes[node.getId()] = true;
  }

  for (std::list<Visitor*>::iterator itVisitors = visitorList.begin();itVisitors != visitorList.end(); ++itVisitors) {
    (*itVisitors)->visit(node);
    incVisitorDepth((**itVisitors));
  }

  clearStoppedVisitors();
  if(needPreorderStop)
    return;

  visitAllEdges(node,true);

  for (std::list<Visitor*>::iterator itVisitors = visitorList.begin();itVisitors != visitorList.end(); ++itVisitors) {
    decVisitorDepth(**itVisitors);
    (*itVisitors)->visitEnd(node);
  }

  clearStoppedVisitors();
}

void AlgorithmPreorder::visitAllEdges(const module::Package& node, bool callFirst /*= true*/){
  visitAllEdges(dynamic_cast<const base::Base&>(node),false);

  std::list<Visitor*>::iterator itVisitors;

  // edge: hasModule
  for (ListIterator<module::Module> it = node.getModuleListIteratorBegin(); it != node.getModuleListIteratorEnd(); ++it) {
    const module::Module& endNodeRef = *it;
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitPackage_HasModule(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;

    if ((!fact->getIsFilterTurnedOn() && !visitFilteredEdge) || (fact->getFilterState(endNodeRef.getId()) == Filter::NotFiltered) || (!originalFilterState && visitFilteredEdge)) {
      if (apRoot && visitUsedSpecialNodesOnly && Common::getIsAPSpecNode(endNodeRef)) {
        unvisitedNodes[endNodeRef.getId()] = true;
      } else {
        endNodeRef.accept(*this);
      }
    }
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitEndPackage_HasModule(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;
  }

  // edge: hasPackage
  for (ListIterator<module::Package> it = node.getPackageListIteratorBegin(); it != node.getPackageListIteratorEnd(); ++it) {
    const module::Package& endNodeRef = *it;
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitPackage_HasPackage(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;

    if ((!fact->getIsFilterTurnedOn() && !visitFilteredEdge) || (fact->getFilterState(endNodeRef.getId()) == Filter::NotFiltered) || (!originalFilterState && visitFilteredEdge)) {
      if (apRoot && visitUsedSpecialNodesOnly && Common::getIsAPSpecNode(endNodeRef)) {
        unvisitedNodes[endNodeRef.getId()] = true;
      } else {
        endNodeRef.accept(*this);
      }
    }
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitEndPackage_HasPackage(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;
  }
}

void AlgorithmPreorder::visit(const module::Package& node, bool callFirst /*= true*/){
#ifdef DEBUG_PREORDER
  std::cout << "Rec. run: " << (unsigned int)&node << " " << node.getId() << " " << Common::toString(node.getNodeKind()) << std::endl;
#endif
  if (safeMode || visitCrossEdgeTree || visitSpecialNodes) {
    if (safeMode) {
      if (visitedNodes[node.getId()]) { // for safemode
        common::WriteMsg::write(CMSG_THE_PRE_ORDER_HAS_TOUCHED_A_NODE_TWICE,node.getId(),Common::toString(node.getNodeKind()).c_str() );
        return;
      }
    }
    visitedNodes[node.getId()] = true;
  }

  for (std::list<Visitor*>::iterator itVisitors = visitorList.begin();itVisitors != visitorList.end(); ++itVisitors) {
    (*itVisitors)->visit(node);
    incVisitorDepth((**itVisitors));
  }

  clearStoppedVisitors();
  if(needPreorderStop)
    return;

  visitAllEdges(node,true);

  for (std::list<Visitor*>::iterator itVisitors = visitorList.begin();itVisitors != visitorList.end(); ++itVisitors) {
    decVisitorDepth(**itVisitors);
    (*itVisitors)->visitEnd(node);
  }

  clearStoppedVisitors();
}

void AlgorithmPreorder::visitAllEdges(const statement::Alias& node, bool callFirst /*= true*/){
  visitAllEdges(dynamic_cast<const base::Named&>(node),false);

  std::list<Visitor*>::iterator itVisitors;

  const base::Base* genNodePtr;
  // edge: refersTo
  genNodePtr = node.getRefersTo() ;
  if (genNodePtr) {
    const base::Base& endNodeRef = *genNodePtr;
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitAlias_RefersTo(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;

    if ((!fact->getIsFilterTurnedOn() && !visitFilteredEdge) || (fact->getFilterState(endNodeRef.getId()) == Filter::NotFiltered) || (!originalFilterState && visitFilteredEdge)) {
      if (apRoot) {
        if (visitCrossEdgeTree || (visitUsedSpecialNodesOnly && Common::getIsAPSpecNode(endNodeRef))) {
          unvisitedNodes[endNodeRef.getId()] = true;
        }
      }
      if (traversaldCrossEdges[edkAlias_RefersTo]) {
        endNodeRef.accept(*this);
      }
    }
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitEndAlias_RefersTo(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;
  }
}

void AlgorithmPreorder::visit(const statement::Alias& node, bool callFirst /*= true*/){
#ifdef DEBUG_PREORDER
  std::cout << "Rec. run: " << (unsigned int)&node << " " << node.getId() << " " << Common::toString(node.getNodeKind()) << std::endl;
#endif
  if (safeMode || visitCrossEdgeTree || visitSpecialNodes) {
    if (safeMode) {
      if (visitedNodes[node.getId()]) { // for safemode
        common::WriteMsg::write(CMSG_THE_PRE_ORDER_HAS_TOUCHED_A_NODE_TWICE,node.getId(),Common::toString(node.getNodeKind()).c_str() );
        return;
      }
    }
    visitedNodes[node.getId()] = true;
  }

  for (std::list<Visitor*>::iterator itVisitors = visitorList.begin();itVisitors != visitorList.end(); ++itVisitors) {
    (*itVisitors)->visit(node);
    incVisitorDepth((**itVisitors));
  }

  clearStoppedVisitors();
  if(needPreorderStop)
    return;

  visitAllEdges(node,true);

  for (std::list<Visitor*>::iterator itVisitors = visitorList.begin();itVisitors != visitorList.end(); ++itVisitors) {
    decVisitorDepth(**itVisitors);
    (*itVisitors)->visitEnd(node);
  }

  clearStoppedVisitors();
}

void AlgorithmPreorder::visitAllEdges(const statement::Assert& node, bool callFirst /*= true*/){
  visitAllEdges(dynamic_cast<const statement::SimpleStatement&>(node),false);

  std::list<Visitor*>::iterator itVisitors;

  const base::Base* genNodePtr;
  // edge: hasMsgExpression
  genNodePtr = node.getMsgExpression() ;
  if (genNodePtr) {
    const expression::Expression& endNodeRef = dynamic_cast<const expression::Expression&>(*genNodePtr);
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitAssert_HasMsgExpression(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;

    if ((!fact->getIsFilterTurnedOn() && !visitFilteredEdge) || (fact->getFilterState(endNodeRef.getId()) == Filter::NotFiltered) || (!originalFilterState && visitFilteredEdge)) {
      if (apRoot && visitUsedSpecialNodesOnly && Common::getIsAPSpecNode(endNodeRef)) {
        unvisitedNodes[endNodeRef.getId()] = true;
      } else {
        endNodeRef.accept(*this);
      }
    }
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitEndAssert_HasMsgExpression(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;
  }

  // edge: hasTestExpression
  genNodePtr = node.getTestExpression() ;
  if (genNodePtr) {
    const expression::Expression& endNodeRef = dynamic_cast<const expression::Expression&>(*genNodePtr);
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitAssert_HasTestExpression(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;

    if ((!fact->getIsFilterTurnedOn() && !visitFilteredEdge) || (fact->getFilterState(endNodeRef.getId()) == Filter::NotFiltered) || (!originalFilterState && visitFilteredEdge)) {
      if (apRoot && visitUsedSpecialNodesOnly && Common::getIsAPSpecNode(endNodeRef)) {
        unvisitedNodes[endNodeRef.getId()] = true;
      } else {
        endNodeRef.accept(*this);
      }
    }
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitEndAssert_HasTestExpression(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;
  }
}

void AlgorithmPreorder::visit(const statement::Assert& node, bool callFirst /*= true*/){
#ifdef DEBUG_PREORDER
  std::cout << "Rec. run: " << (unsigned int)&node << " " << node.getId() << " " << Common::toString(node.getNodeKind()) << std::endl;
#endif
  if (safeMode || visitCrossEdgeTree || visitSpecialNodes) {
    if (safeMode) {
      if (visitedNodes[node.getId()]) { // for safemode
        common::WriteMsg::write(CMSG_THE_PRE_ORDER_HAS_TOUCHED_A_NODE_TWICE,node.getId(),Common::toString(node.getNodeKind()).c_str() );
        return;
      }
    }
    visitedNodes[node.getId()] = true;
  }

  for (std::list<Visitor*>::iterator itVisitors = visitorList.begin();itVisitors != visitorList.end(); ++itVisitors) {
    (*itVisitors)->visit(node);
    incVisitorDepth((**itVisitors));
  }

  clearStoppedVisitors();
  if(needPreorderStop)
    return;

  visitAllEdges(node,true);

  for (std::list<Visitor*>::iterator itVisitors = visitorList.begin();itVisitors != visitorList.end(); ++itVisitors) {
    decVisitorDepth(**itVisitors);
    (*itVisitors)->visitEnd(node);
  }

  clearStoppedVisitors();
}

void AlgorithmPreorder::visitAllEdges(const statement::Assign& node, bool callFirst /*= true*/){
  visitAllEdges(dynamic_cast<const statement::SimpleStatement&>(node),false);

  std::list<Visitor*>::iterator itVisitors;

  const base::Base* genNodePtr;
  // edge: hasExpression
  genNodePtr = node.getExpression() ;
  if (genNodePtr) {
    const expression::Expression& endNodeRef = dynamic_cast<const expression::Expression&>(*genNodePtr);
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitAssign_HasExpression(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;

    if ((!fact->getIsFilterTurnedOn() && !visitFilteredEdge) || (fact->getFilterState(endNodeRef.getId()) == Filter::NotFiltered) || (!originalFilterState && visitFilteredEdge)) {
      if (apRoot && visitUsedSpecialNodesOnly && Common::getIsAPSpecNode(endNodeRef)) {
        unvisitedNodes[endNodeRef.getId()] = true;
      } else {
        endNodeRef.accept(*this);
      }
    }
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitEndAssign_HasExpression(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;
  }

  // edge: hasTargetList
  genNodePtr = node.getTargetList() ;
  if (genNodePtr) {
    const statement::TargetList& endNodeRef = dynamic_cast<const statement::TargetList&>(*genNodePtr);
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitAssign_HasTargetList(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;

    if ((!fact->getIsFilterTurnedOn() && !visitFilteredEdge) || (fact->getFilterState(endNodeRef.getId()) == Filter::NotFiltered) || (!originalFilterState && visitFilteredEdge)) {
      if (apRoot && visitUsedSpecialNodesOnly && Common::getIsAPSpecNode(endNodeRef)) {
        unvisitedNodes[endNodeRef.getId()] = true;
      } else {
        endNodeRef.accept(*this);
      }
    }
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitEndAssign_HasTargetList(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;
  }
}

void AlgorithmPreorder::visit(const statement::Assign& node, bool callFirst /*= true*/){
#ifdef DEBUG_PREORDER
  std::cout << "Rec. run: " << (unsigned int)&node << " " << node.getId() << " " << Common::toString(node.getNodeKind()) << std::endl;
#endif
  if (safeMode || visitCrossEdgeTree || visitSpecialNodes) {
    if (safeMode) {
      if (visitedNodes[node.getId()]) { // for safemode
        common::WriteMsg::write(CMSG_THE_PRE_ORDER_HAS_TOUCHED_A_NODE_TWICE,node.getId(),Common::toString(node.getNodeKind()).c_str() );
        return;
      }
    }
    visitedNodes[node.getId()] = true;
  }

  for (std::list<Visitor*>::iterator itVisitors = visitorList.begin();itVisitors != visitorList.end(); ++itVisitors) {
    (*itVisitors)->visit(node);
    incVisitorDepth((**itVisitors));
  }

  clearStoppedVisitors();
  if(needPreorderStop)
    return;

  visitAllEdges(node,true);

  for (std::list<Visitor*>::iterator itVisitors = visitorList.begin();itVisitors != visitorList.end(); ++itVisitors) {
    decVisitorDepth(**itVisitors);
    (*itVisitors)->visitEnd(node);
  }

  clearStoppedVisitors();
}

void AlgorithmPreorder::visitAllEdges(const statement::AugAssign& node, bool callFirst /*= true*/){
  visitAllEdges(dynamic_cast<const statement::Assign&>(node),false);
}

void AlgorithmPreorder::visit(const statement::AugAssign& node, bool callFirst /*= true*/){
#ifdef DEBUG_PREORDER
  std::cout << "Rec. run: " << (unsigned int)&node << " " << node.getId() << " " << Common::toString(node.getNodeKind()) << std::endl;
#endif
  if (safeMode || visitCrossEdgeTree || visitSpecialNodes) {
    if (safeMode) {
      if (visitedNodes[node.getId()]) { // for safemode
        common::WriteMsg::write(CMSG_THE_PRE_ORDER_HAS_TOUCHED_A_NODE_TWICE,node.getId(),Common::toString(node.getNodeKind()).c_str() );
        return;
      }
    }
    visitedNodes[node.getId()] = true;
  }

  for (std::list<Visitor*>::iterator itVisitors = visitorList.begin();itVisitors != visitorList.end(); ++itVisitors) {
    (*itVisitors)->visit(node);
    incVisitorDepth((**itVisitors));
  }

  clearStoppedVisitors();
  if(needPreorderStop)
    return;

  visitAllEdges(node,true);

  for (std::list<Visitor*>::iterator itVisitors = visitorList.begin();itVisitors != visitorList.end(); ++itVisitors) {
    decVisitorDepth(**itVisitors);
    (*itVisitors)->visitEnd(node);
  }

  clearStoppedVisitors();
}

void AlgorithmPreorder::visitAllEdges(const statement::BaseSpecifier& node, bool callFirst /*= true*/){
  visitAllEdges(dynamic_cast<const base::Positioned&>(node),false);

  std::list<Visitor*>::iterator itVisitors;

  const base::Base* genNodePtr;
  // edge: hasName
  genNodePtr = node.getName() ;
  if (genNodePtr) {
    const expression::Expression& endNodeRef = dynamic_cast<const expression::Expression&>(*genNodePtr);
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitBaseSpecifier_HasName(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;

    if ((!fact->getIsFilterTurnedOn() && !visitFilteredEdge) || (fact->getFilterState(endNodeRef.getId()) == Filter::NotFiltered) || (!originalFilterState && visitFilteredEdge)) {
      if (apRoot && visitUsedSpecialNodesOnly && Common::getIsAPSpecNode(endNodeRef)) {
        unvisitedNodes[endNodeRef.getId()] = true;
      } else {
        endNodeRef.accept(*this);
      }
    }
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitEndBaseSpecifier_HasName(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;
  }

  // edge: derivesFrom
  genNodePtr = node.getDerivesFrom() ;
  if (genNodePtr) {
    const statement::ClassDef& endNodeRef = dynamic_cast<const statement::ClassDef&>(*genNodePtr);
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitBaseSpecifier_DerivesFrom(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;

    if ((!fact->getIsFilterTurnedOn() && !visitFilteredEdge) || (fact->getFilterState(endNodeRef.getId()) == Filter::NotFiltered) || (!originalFilterState && visitFilteredEdge)) {
      if (apRoot) {
        if (visitCrossEdgeTree || (visitUsedSpecialNodesOnly && Common::getIsAPSpecNode(endNodeRef))) {
          unvisitedNodes[endNodeRef.getId()] = true;
        }
      }
      if (traversaldCrossEdges[edkBaseSpecifier_DerivesFrom]) {
        endNodeRef.accept(*this);
      }
    }
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitEndBaseSpecifier_DerivesFrom(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;
  }
}

void AlgorithmPreorder::visit(const statement::BaseSpecifier& node, bool callFirst /*= true*/){
#ifdef DEBUG_PREORDER
  std::cout << "Rec. run: " << (unsigned int)&node << " " << node.getId() << " " << Common::toString(node.getNodeKind()) << std::endl;
#endif
  if (safeMode || visitCrossEdgeTree || visitSpecialNodes) {
    if (safeMode) {
      if (visitedNodes[node.getId()]) { // for safemode
        common::WriteMsg::write(CMSG_THE_PRE_ORDER_HAS_TOUCHED_A_NODE_TWICE,node.getId(),Common::toString(node.getNodeKind()).c_str() );
        return;
      }
    }
    visitedNodes[node.getId()] = true;
  }

  for (std::list<Visitor*>::iterator itVisitors = visitorList.begin();itVisitors != visitorList.end(); ++itVisitors) {
    (*itVisitors)->visit(node);
    incVisitorDepth((**itVisitors));
  }

  clearStoppedVisitors();
  if(needPreorderStop)
    return;

  visitAllEdges(node,true);

  for (std::list<Visitor*>::iterator itVisitors = visitorList.begin();itVisitors != visitorList.end(); ++itVisitors) {
    decVisitorDepth(**itVisitors);
    (*itVisitors)->visitEnd(node);
  }

  clearStoppedVisitors();
}

void AlgorithmPreorder::visitAllEdges(const statement::Break& node, bool callFirst /*= true*/){
  visitAllEdges(dynamic_cast<const statement::SimpleStatement&>(node),false);
}

void AlgorithmPreorder::visit(const statement::Break& node, bool callFirst /*= true*/){
#ifdef DEBUG_PREORDER
  std::cout << "Rec. run: " << (unsigned int)&node << " " << node.getId() << " " << Common::toString(node.getNodeKind()) << std::endl;
#endif
  if (safeMode || visitCrossEdgeTree || visitSpecialNodes) {
    if (safeMode) {
      if (visitedNodes[node.getId()]) { // for safemode
        common::WriteMsg::write(CMSG_THE_PRE_ORDER_HAS_TOUCHED_A_NODE_TWICE,node.getId(),Common::toString(node.getNodeKind()).c_str() );
        return;
      }
    }
    visitedNodes[node.getId()] = true;
  }

  for (std::list<Visitor*>::iterator itVisitors = visitorList.begin();itVisitors != visitorList.end(); ++itVisitors) {
    (*itVisitors)->visit(node);
    incVisitorDepth((**itVisitors));
  }

  clearStoppedVisitors();
  if(needPreorderStop)
    return;

  visitAllEdges(node,true);

  for (std::list<Visitor*>::iterator itVisitors = visitorList.begin();itVisitors != visitorList.end(); ++itVisitors) {
    decVisitorDepth(**itVisitors);
    (*itVisitors)->visitEnd(node);
  }

  clearStoppedVisitors();
}

void AlgorithmPreorder::visitAllEdges(const statement::ClassDef& node, bool callFirst /*= true*/){
  visitAllEdges(dynamic_cast<const statement::CompoundStatement&>(node),false);

  std::list<Visitor*>::iterator itVisitors;

  // edge: hasObject
  for (ListIterator<module::Object> it = node.getObjectListIteratorBegin(); it != node.getObjectListIteratorEnd(); ++it) {
    const module::Object& endNodeRef = *it;
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitClassDef_HasObject(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;

    if ((!fact->getIsFilterTurnedOn() && !visitFilteredEdge) || (fact->getFilterState(endNodeRef.getId()) == Filter::NotFiltered) || (!originalFilterState && visitFilteredEdge)) {
      if (apRoot && visitUsedSpecialNodesOnly && Common::getIsAPSpecNode(endNodeRef)) {
        unvisitedNodes[endNodeRef.getId()] = true;
      } else {
        endNodeRef.accept(*this);
      }
    }
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitEndClassDef_HasObject(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;
  }

  // edge: hasBaseSpecifier
  for (ListIterator<statement::BaseSpecifier> it = node.getBaseSpecifierListIteratorBegin(); it != node.getBaseSpecifierListIteratorEnd(); ++it) {
    const statement::BaseSpecifier& endNodeRef = *it;
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitClassDef_HasBaseSpecifier(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;

    if ((!fact->getIsFilterTurnedOn() && !visitFilteredEdge) || (fact->getFilterState(endNodeRef.getId()) == Filter::NotFiltered) || (!originalFilterState && visitFilteredEdge)) {
      if (apRoot && visitUsedSpecialNodesOnly && Common::getIsAPSpecNode(endNodeRef)) {
        unvisitedNodes[endNodeRef.getId()] = true;
      } else {
        endNodeRef.accept(*this);
      }
    }
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitEndClassDef_HasBaseSpecifier(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;
  }

  // edge: hasDecorator
  for (ListIterator<expression::Expression> it = node.getDecoratorListIteratorBegin(); it != node.getDecoratorListIteratorEnd(); ++it) {
    const expression::Expression& endNodeRef = *it;
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitClassDef_HasDecorator(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;

    if ((!fact->getIsFilterTurnedOn() && !visitFilteredEdge) || (fact->getFilterState(endNodeRef.getId()) == Filter::NotFiltered) || (!originalFilterState && visitFilteredEdge)) {
      if (apRoot && visitUsedSpecialNodesOnly && Common::getIsAPSpecNode(endNodeRef)) {
        unvisitedNodes[endNodeRef.getId()] = true;
      } else {
        endNodeRef.accept(*this);
      }
    }
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitEndClassDef_HasDecorator(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;
  }

  const base::Base* genNodePtr;
  // edge: refersTo
  genNodePtr = node.getRefersTo() ;
  if (genNodePtr) {
    const module::Object& endNodeRef = dynamic_cast<const module::Object&>(*genNodePtr);
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitClassDef_RefersTo(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;

    if ((!fact->getIsFilterTurnedOn() && !visitFilteredEdge) || (fact->getFilterState(endNodeRef.getId()) == Filter::NotFiltered) || (!originalFilterState && visitFilteredEdge)) {
      if (apRoot) {
        if (visitCrossEdgeTree || (visitUsedSpecialNodesOnly && Common::getIsAPSpecNode(endNodeRef))) {
          unvisitedNodes[endNodeRef.getId()] = true;
        }
      }
      if (traversaldCrossEdges[edkClassDef_RefersTo]) {
        endNodeRef.accept(*this);
      }
    }
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitEndClassDef_RefersTo(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;
  }

  // edge: docstring
  genNodePtr = node.getDocstring() ;
  if (genNodePtr) {
    const base::Docstring& endNodeRef = dynamic_cast<const base::Docstring&>(*genNodePtr);
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitClassDef_Docstring(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;

    if ((!fact->getIsFilterTurnedOn() && !visitFilteredEdge) || (fact->getFilterState(endNodeRef.getId()) == Filter::NotFiltered) || (!originalFilterState && visitFilteredEdge)) {
      if (apRoot) {
        if (visitCrossEdgeTree || (visitUsedSpecialNodesOnly && Common::getIsAPSpecNode(endNodeRef))) {
          unvisitedNodes[endNodeRef.getId()] = true;
        }
      }
      if (traversaldCrossEdges[edkClassDef_Docstring]) {
        endNodeRef.accept(*this);
      }
    }
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitEndClassDef_Docstring(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;
  }
}

void AlgorithmPreorder::visit(const statement::ClassDef& node, bool callFirst /*= true*/){
#ifdef DEBUG_PREORDER
  std::cout << "Rec. run: " << (unsigned int)&node << " " << node.getId() << " " << Common::toString(node.getNodeKind()) << std::endl;
#endif
  if (safeMode || visitCrossEdgeTree || visitSpecialNodes) {
    if (safeMode) {
      if (visitedNodes[node.getId()]) { // for safemode
        common::WriteMsg::write(CMSG_THE_PRE_ORDER_HAS_TOUCHED_A_NODE_TWICE,node.getId(),Common::toString(node.getNodeKind()).c_str() );
        return;
      }
    }
    visitedNodes[node.getId()] = true;
  }

  for (std::list<Visitor*>::iterator itVisitors = visitorList.begin();itVisitors != visitorList.end(); ++itVisitors) {
    (*itVisitors)->visit(node);
    incVisitorDepth((**itVisitors));
  }

  clearStoppedVisitors();
  if(needPreorderStop)
    return;

  visitAllEdges(node,true);

  for (std::list<Visitor*>::iterator itVisitors = visitorList.begin();itVisitors != visitorList.end(); ++itVisitors) {
    decVisitorDepth(**itVisitors);
    (*itVisitors)->visitEnd(node);
  }

  clearStoppedVisitors();
}

void AlgorithmPreorder::visitAllEdges(const statement::CompoundStatement& node, bool callFirst /*= true*/){
  visitAllEdges(dynamic_cast<const statement::Statement&>(node),false);

  std::list<Visitor*>::iterator itVisitors;

  const base::Base* genNodePtr;
  // edge: hasBody
  genNodePtr = node.getBody() ;
  if (genNodePtr) {
    const statement::Suite& endNodeRef = dynamic_cast<const statement::Suite&>(*genNodePtr);
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitCompoundStatement_HasBody(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;

    if ((!fact->getIsFilterTurnedOn() && !visitFilteredEdge) || (fact->getFilterState(endNodeRef.getId()) == Filter::NotFiltered) || (!originalFilterState && visitFilteredEdge)) {
      if (apRoot && visitUsedSpecialNodesOnly && Common::getIsAPSpecNode(endNodeRef)) {
        unvisitedNodes[endNodeRef.getId()] = true;
      } else {
        endNodeRef.accept(*this);
      }
    }
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitEndCompoundStatement_HasBody(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;
  }
}

void AlgorithmPreorder::visitAllEdges(const statement::Continue& node, bool callFirst /*= true*/){
  visitAllEdges(dynamic_cast<const statement::SimpleStatement&>(node),false);
}

void AlgorithmPreorder::visit(const statement::Continue& node, bool callFirst /*= true*/){
#ifdef DEBUG_PREORDER
  std::cout << "Rec. run: " << (unsigned int)&node << " " << node.getId() << " " << Common::toString(node.getNodeKind()) << std::endl;
#endif
  if (safeMode || visitCrossEdgeTree || visitSpecialNodes) {
    if (safeMode) {
      if (visitedNodes[node.getId()]) { // for safemode
        common::WriteMsg::write(CMSG_THE_PRE_ORDER_HAS_TOUCHED_A_NODE_TWICE,node.getId(),Common::toString(node.getNodeKind()).c_str() );
        return;
      }
    }
    visitedNodes[node.getId()] = true;
  }

  for (std::list<Visitor*>::iterator itVisitors = visitorList.begin();itVisitors != visitorList.end(); ++itVisitors) {
    (*itVisitors)->visit(node);
    incVisitorDepth((**itVisitors));
  }

  clearStoppedVisitors();
  if(needPreorderStop)
    return;

  visitAllEdges(node,true);

  for (std::list<Visitor*>::iterator itVisitors = visitorList.begin();itVisitors != visitorList.end(); ++itVisitors) {
    decVisitorDepth(**itVisitors);
    (*itVisitors)->visitEnd(node);
  }

  clearStoppedVisitors();
}

void AlgorithmPreorder::visitAllEdges(const statement::Delete& node, bool callFirst /*= true*/){
  visitAllEdges(dynamic_cast<const statement::SimpleStatement&>(node),false);

  std::list<Visitor*>::iterator itVisitors;

  const base::Base* genNodePtr;
  // edge: hasTargetList
  genNodePtr = node.getTargetList() ;
  if (genNodePtr) {
    const statement::TargetList& endNodeRef = dynamic_cast<const statement::TargetList&>(*genNodePtr);
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitDelete_HasTargetList(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;

    if ((!fact->getIsFilterTurnedOn() && !visitFilteredEdge) || (fact->getFilterState(endNodeRef.getId()) == Filter::NotFiltered) || (!originalFilterState && visitFilteredEdge)) {
      if (apRoot && visitUsedSpecialNodesOnly && Common::getIsAPSpecNode(endNodeRef)) {
        unvisitedNodes[endNodeRef.getId()] = true;
      } else {
        endNodeRef.accept(*this);
      }
    }
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitEndDelete_HasTargetList(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;
  }
}

void AlgorithmPreorder::visit(const statement::Delete& node, bool callFirst /*= true*/){
#ifdef DEBUG_PREORDER
  std::cout << "Rec. run: " << (unsigned int)&node << " " << node.getId() << " " << Common::toString(node.getNodeKind()) << std::endl;
#endif
  if (safeMode || visitCrossEdgeTree || visitSpecialNodes) {
    if (safeMode) {
      if (visitedNodes[node.getId()]) { // for safemode
        common::WriteMsg::write(CMSG_THE_PRE_ORDER_HAS_TOUCHED_A_NODE_TWICE,node.getId(),Common::toString(node.getNodeKind()).c_str() );
        return;
      }
    }
    visitedNodes[node.getId()] = true;
  }

  for (std::list<Visitor*>::iterator itVisitors = visitorList.begin();itVisitors != visitorList.end(); ++itVisitors) {
    (*itVisitors)->visit(node);
    incVisitorDepth((**itVisitors));
  }

  clearStoppedVisitors();
  if(needPreorderStop)
    return;

  visitAllEdges(node,true);

  for (std::list<Visitor*>::iterator itVisitors = visitorList.begin();itVisitors != visitorList.end(); ++itVisitors) {
    decVisitorDepth(**itVisitors);
    (*itVisitors)->visitEnd(node);
  }

  clearStoppedVisitors();
}

void AlgorithmPreorder::visitAllEdges(const statement::Exec& node, bool callFirst /*= true*/){
  visitAllEdges(dynamic_cast<const statement::SimpleStatement&>(node),false);

  std::list<Visitor*>::iterator itVisitors;

  const base::Base* genNodePtr;
  // edge: hasExpression
  genNodePtr = node.getExpression() ;
  if (genNodePtr) {
    const expression::Expression& endNodeRef = dynamic_cast<const expression::Expression&>(*genNodePtr);
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitExec_HasExpression(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;

    if ((!fact->getIsFilterTurnedOn() && !visitFilteredEdge) || (fact->getFilterState(endNodeRef.getId()) == Filter::NotFiltered) || (!originalFilterState && visitFilteredEdge)) {
      if (apRoot && visitUsedSpecialNodesOnly && Common::getIsAPSpecNode(endNodeRef)) {
        unvisitedNodes[endNodeRef.getId()] = true;
      } else {
        endNodeRef.accept(*this);
      }
    }
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitEndExec_HasExpression(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;
  }

  // edge: hasGlobals
  genNodePtr = node.getGlobals() ;
  if (genNodePtr) {
    const expression::Expression& endNodeRef = dynamic_cast<const expression::Expression&>(*genNodePtr);
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitExec_HasGlobals(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;

    if ((!fact->getIsFilterTurnedOn() && !visitFilteredEdge) || (fact->getFilterState(endNodeRef.getId()) == Filter::NotFiltered) || (!originalFilterState && visitFilteredEdge)) {
      if (apRoot && visitUsedSpecialNodesOnly && Common::getIsAPSpecNode(endNodeRef)) {
        unvisitedNodes[endNodeRef.getId()] = true;
      } else {
        endNodeRef.accept(*this);
      }
    }
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitEndExec_HasGlobals(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;
  }

  // edge: hasLocals
  genNodePtr = node.getLocals() ;
  if (genNodePtr) {
    const expression::Expression& endNodeRef = dynamic_cast<const expression::Expression&>(*genNodePtr);
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitExec_HasLocals(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;

    if ((!fact->getIsFilterTurnedOn() && !visitFilteredEdge) || (fact->getFilterState(endNodeRef.getId()) == Filter::NotFiltered) || (!originalFilterState && visitFilteredEdge)) {
      if (apRoot && visitUsedSpecialNodesOnly && Common::getIsAPSpecNode(endNodeRef)) {
        unvisitedNodes[endNodeRef.getId()] = true;
      } else {
        endNodeRef.accept(*this);
      }
    }
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitEndExec_HasLocals(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;
  }
}

void AlgorithmPreorder::visit(const statement::Exec& node, bool callFirst /*= true*/){
#ifdef DEBUG_PREORDER
  std::cout << "Rec. run: " << (unsigned int)&node << " " << node.getId() << " " << Common::toString(node.getNodeKind()) << std::endl;
#endif
  if (safeMode || visitCrossEdgeTree || visitSpecialNodes) {
    if (safeMode) {
      if (visitedNodes[node.getId()]) { // for safemode
        common::WriteMsg::write(CMSG_THE_PRE_ORDER_HAS_TOUCHED_A_NODE_TWICE,node.getId(),Common::toString(node.getNodeKind()).c_str() );
        return;
      }
    }
    visitedNodes[node.getId()] = true;
  }

  for (std::list<Visitor*>::iterator itVisitors = visitorList.begin();itVisitors != visitorList.end(); ++itVisitors) {
    (*itVisitors)->visit(node);
    incVisitorDepth((**itVisitors));
  }

  clearStoppedVisitors();
  if(needPreorderStop)
    return;

  visitAllEdges(node,true);

  for (std::list<Visitor*>::iterator itVisitors = visitorList.begin();itVisitors != visitorList.end(); ++itVisitors) {
    decVisitorDepth(**itVisitors);
    (*itVisitors)->visitEnd(node);
  }

  clearStoppedVisitors();
}

void AlgorithmPreorder::visitAllEdges(const statement::For& node, bool callFirst /*= true*/){
  visitAllEdges(dynamic_cast<const statement::Iteration&>(node),false);

  std::list<Visitor*>::iterator itVisitors;

  const base::Base* genNodePtr;
  // edge: hasExpressionList
  genNodePtr = node.getExpressionList() ;
  if (genNodePtr) {
    const expression::ExpressionList& endNodeRef = dynamic_cast<const expression::ExpressionList&>(*genNodePtr);
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitFor_HasExpressionList(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;

    if ((!fact->getIsFilterTurnedOn() && !visitFilteredEdge) || (fact->getFilterState(endNodeRef.getId()) == Filter::NotFiltered) || (!originalFilterState && visitFilteredEdge)) {
      if (apRoot && visitUsedSpecialNodesOnly && Common::getIsAPSpecNode(endNodeRef)) {
        unvisitedNodes[endNodeRef.getId()] = true;
      } else {
        endNodeRef.accept(*this);
      }
    }
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitEndFor_HasExpressionList(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;
  }

  // edge: hasTargetList
  genNodePtr = node.getTargetList() ;
  if (genNodePtr) {
    const statement::TargetList& endNodeRef = dynamic_cast<const statement::TargetList&>(*genNodePtr);
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitFor_HasTargetList(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;

    if ((!fact->getIsFilterTurnedOn() && !visitFilteredEdge) || (fact->getFilterState(endNodeRef.getId()) == Filter::NotFiltered) || (!originalFilterState && visitFilteredEdge)) {
      if (apRoot && visitUsedSpecialNodesOnly && Common::getIsAPSpecNode(endNodeRef)) {
        unvisitedNodes[endNodeRef.getId()] = true;
      } else {
        endNodeRef.accept(*this);
      }
    }
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitEndFor_HasTargetList(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;
  }
}

void AlgorithmPreorder::visit(const statement::For& node, bool callFirst /*= true*/){
#ifdef DEBUG_PREORDER
  std::cout << "Rec. run: " << (unsigned int)&node << " " << node.getId() << " " << Common::toString(node.getNodeKind()) << std::endl;
#endif
  if (safeMode || visitCrossEdgeTree || visitSpecialNodes) {
    if (safeMode) {
      if (visitedNodes[node.getId()]) { // for safemode
        common::WriteMsg::write(CMSG_THE_PRE_ORDER_HAS_TOUCHED_A_NODE_TWICE,node.getId(),Common::toString(node.getNodeKind()).c_str() );
        return;
      }
    }
    visitedNodes[node.getId()] = true;
  }

  for (std::list<Visitor*>::iterator itVisitors = visitorList.begin();itVisitors != visitorList.end(); ++itVisitors) {
    (*itVisitors)->visit(node);
    incVisitorDepth((**itVisitors));
  }

  clearStoppedVisitors();
  if(needPreorderStop)
    return;

  visitAllEdges(node,true);

  for (std::list<Visitor*>::iterator itVisitors = visitorList.begin();itVisitors != visitorList.end(); ++itVisitors) {
    decVisitorDepth(**itVisitors);
    (*itVisitors)->visitEnd(node);
  }

  clearStoppedVisitors();
}

void AlgorithmPreorder::visitAllEdges(const statement::FunctionDef& node, bool callFirst /*= true*/){
  visitAllEdges(dynamic_cast<const statement::CompoundStatement&>(node),false);

  std::list<Visitor*>::iterator itVisitors;

  // edge: hasDecorator
  for (ListIterator<expression::Expression> it = node.getDecoratorListIteratorBegin(); it != node.getDecoratorListIteratorEnd(); ++it) {
    const expression::Expression& endNodeRef = *it;
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitFunctionDef_HasDecorator(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;

    if ((!fact->getIsFilterTurnedOn() && !visitFilteredEdge) || (fact->getFilterState(endNodeRef.getId()) == Filter::NotFiltered) || (!originalFilterState && visitFilteredEdge)) {
      if (apRoot && visitUsedSpecialNodesOnly && Common::getIsAPSpecNode(endNodeRef)) {
        unvisitedNodes[endNodeRef.getId()] = true;
      } else {
        endNodeRef.accept(*this);
      }
    }
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitEndFunctionDef_HasDecorator(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;
  }

  // edge: hasObject
  for (ListIterator<module::Object> it = node.getObjectListIteratorBegin(); it != node.getObjectListIteratorEnd(); ++it) {
    const module::Object& endNodeRef = *it;
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitFunctionDef_HasObject(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;

    if ((!fact->getIsFilterTurnedOn() && !visitFilteredEdge) || (fact->getFilterState(endNodeRef.getId()) == Filter::NotFiltered) || (!originalFilterState && visitFilteredEdge)) {
      if (apRoot && visitUsedSpecialNodesOnly && Common::getIsAPSpecNode(endNodeRef)) {
        unvisitedNodes[endNodeRef.getId()] = true;
      } else {
        endNodeRef.accept(*this);
      }
    }
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitEndFunctionDef_HasObject(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;
  }

  // edge: hasParameter
  for (ListIterator<statement::Parameter> it = node.getParameterListIteratorBegin(); it != node.getParameterListIteratorEnd(); ++it) {
    const statement::Parameter& endNodeRef = *it;
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitFunctionDef_HasParameter(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;

    if ((!fact->getIsFilterTurnedOn() && !visitFilteredEdge) || (fact->getFilterState(endNodeRef.getId()) == Filter::NotFiltered) || (!originalFilterState && visitFilteredEdge)) {
      if (apRoot && visitUsedSpecialNodesOnly && Common::getIsAPSpecNode(endNodeRef)) {
        unvisitedNodes[endNodeRef.getId()] = true;
      } else {
        endNodeRef.accept(*this);
      }
    }
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitEndFunctionDef_HasParameter(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;
  }

  const base::Base* genNodePtr;
  // edge: refersTo
  genNodePtr = node.getRefersTo() ;
  if (genNodePtr) {
    const module::Object& endNodeRef = dynamic_cast<const module::Object&>(*genNodePtr);
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitFunctionDef_RefersTo(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;

    if ((!fact->getIsFilterTurnedOn() && !visitFilteredEdge) || (fact->getFilterState(endNodeRef.getId()) == Filter::NotFiltered) || (!originalFilterState && visitFilteredEdge)) {
      if (apRoot) {
        if (visitCrossEdgeTree || (visitUsedSpecialNodesOnly && Common::getIsAPSpecNode(endNodeRef))) {
          unvisitedNodes[endNodeRef.getId()] = true;
        }
      }
      if (traversaldCrossEdges[edkFunctionDef_RefersTo]) {
        endNodeRef.accept(*this);
      }
    }
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitEndFunctionDef_RefersTo(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;
  }

  // edge: returnType
  genNodePtr = node.getReturnType() ;
  if (genNodePtr) {
    const type::Type& endNodeRef = dynamic_cast<const type::Type&>(*genNodePtr);
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitFunctionDef_ReturnType(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;

    if ((!fact->getIsFilterTurnedOn() && !visitFilteredEdge) || (fact->getFilterState(endNodeRef.getId()) == Filter::NotFiltered) || (!originalFilterState && visitFilteredEdge)) {
      if (apRoot) {
        if (visitCrossEdgeTree || (visitUsedSpecialNodesOnly && Common::getIsAPSpecNode(endNodeRef))) {
          unvisitedNodes[endNodeRef.getId()] = true;
        }
      }
      if (traversaldCrossEdges[edkFunctionDef_ReturnType]) {
        endNodeRef.accept(*this);
      }
    }
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitEndFunctionDef_ReturnType(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;
  }

  // edge: docstring
  genNodePtr = node.getDocstring() ;
  if (genNodePtr) {
    const base::Docstring& endNodeRef = dynamic_cast<const base::Docstring&>(*genNodePtr);
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitFunctionDef_Docstring(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;

    if ((!fact->getIsFilterTurnedOn() && !visitFilteredEdge) || (fact->getFilterState(endNodeRef.getId()) == Filter::NotFiltered) || (!originalFilterState && visitFilteredEdge)) {
      if (apRoot) {
        if (visitCrossEdgeTree || (visitUsedSpecialNodesOnly && Common::getIsAPSpecNode(endNodeRef))) {
          unvisitedNodes[endNodeRef.getId()] = true;
        }
      }
      if (traversaldCrossEdges[edkFunctionDef_Docstring]) {
        endNodeRef.accept(*this);
      }
    }
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitEndFunctionDef_Docstring(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;
  }
}

void AlgorithmPreorder::visit(const statement::FunctionDef& node, bool callFirst /*= true*/){
#ifdef DEBUG_PREORDER
  std::cout << "Rec. run: " << (unsigned int)&node << " " << node.getId() << " " << Common::toString(node.getNodeKind()) << std::endl;
#endif
  if (safeMode || visitCrossEdgeTree || visitSpecialNodes) {
    if (safeMode) {
      if (visitedNodes[node.getId()]) { // for safemode
        common::WriteMsg::write(CMSG_THE_PRE_ORDER_HAS_TOUCHED_A_NODE_TWICE,node.getId(),Common::toString(node.getNodeKind()).c_str() );
        return;
      }
    }
    visitedNodes[node.getId()] = true;
  }

  for (std::list<Visitor*>::iterator itVisitors = visitorList.begin();itVisitors != visitorList.end(); ++itVisitors) {
    (*itVisitors)->visit(node);
    incVisitorDepth((**itVisitors));
  }

  clearStoppedVisitors();
  if(needPreorderStop)
    return;

  visitAllEdges(node,true);

  for (std::list<Visitor*>::iterator itVisitors = visitorList.begin();itVisitors != visitorList.end(); ++itVisitors) {
    decVisitorDepth(**itVisitors);
    (*itVisitors)->visitEnd(node);
  }

  clearStoppedVisitors();
}

void AlgorithmPreorder::visitAllEdges(const statement::Global& node, bool callFirst /*= true*/){
  visitAllEdges(dynamic_cast<const statement::SimpleStatement&>(node),false);

  std::list<Visitor*>::iterator itVisitors;

  // edge: hasIdentifier
  for (ListIterator<expression::Identifier> it = node.getIdentifierListIteratorBegin(); it != node.getIdentifierListIteratorEnd(); ++it) {
    const expression::Identifier& endNodeRef = *it;
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitGlobal_HasIdentifier(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;

    if ((!fact->getIsFilterTurnedOn() && !visitFilteredEdge) || (fact->getFilterState(endNodeRef.getId()) == Filter::NotFiltered) || (!originalFilterState && visitFilteredEdge)) {
      if (apRoot && visitUsedSpecialNodesOnly && Common::getIsAPSpecNode(endNodeRef)) {
        unvisitedNodes[endNodeRef.getId()] = true;
      } else {
        endNodeRef.accept(*this);
      }
    }
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitEndGlobal_HasIdentifier(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;
  }
}

void AlgorithmPreorder::visit(const statement::Global& node, bool callFirst /*= true*/){
#ifdef DEBUG_PREORDER
  std::cout << "Rec. run: " << (unsigned int)&node << " " << node.getId() << " " << Common::toString(node.getNodeKind()) << std::endl;
#endif
  if (safeMode || visitCrossEdgeTree || visitSpecialNodes) {
    if (safeMode) {
      if (visitedNodes[node.getId()]) { // for safemode
        common::WriteMsg::write(CMSG_THE_PRE_ORDER_HAS_TOUCHED_A_NODE_TWICE,node.getId(),Common::toString(node.getNodeKind()).c_str() );
        return;
      }
    }
    visitedNodes[node.getId()] = true;
  }

  for (std::list<Visitor*>::iterator itVisitors = visitorList.begin();itVisitors != visitorList.end(); ++itVisitors) {
    (*itVisitors)->visit(node);
    incVisitorDepth((**itVisitors));
  }

  clearStoppedVisitors();
  if(needPreorderStop)
    return;

  visitAllEdges(node,true);

  for (std::list<Visitor*>::iterator itVisitors = visitorList.begin();itVisitors != visitorList.end(); ++itVisitors) {
    decVisitorDepth(**itVisitors);
    (*itVisitors)->visitEnd(node);
  }

  clearStoppedVisitors();
}

void AlgorithmPreorder::visitAllEdges(const statement::Handler& node, bool callFirst /*= true*/){
  visitAllEdges(dynamic_cast<const statement::Statement&>(node),false);

  std::list<Visitor*>::iterator itVisitors;

  const base::Base* genNodePtr;
  // edge: hasName
  genNodePtr = node.getName() ;
  if (genNodePtr) {
    const expression::Expression& endNodeRef = dynamic_cast<const expression::Expression&>(*genNodePtr);
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitHandler_HasName(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;

    if ((!fact->getIsFilterTurnedOn() && !visitFilteredEdge) || (fact->getFilterState(endNodeRef.getId()) == Filter::NotFiltered) || (!originalFilterState && visitFilteredEdge)) {
      if (apRoot && visitUsedSpecialNodesOnly && Common::getIsAPSpecNode(endNodeRef)) {
        unvisitedNodes[endNodeRef.getId()] = true;
      } else {
        endNodeRef.accept(*this);
      }
    }
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitEndHandler_HasName(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;
  }

  // edge: hasExceptBody
  genNodePtr = node.getExceptBody() ;
  if (genNodePtr) {
    const statement::Suite& endNodeRef = dynamic_cast<const statement::Suite&>(*genNodePtr);
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitHandler_HasExceptBody(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;

    if ((!fact->getIsFilterTurnedOn() && !visitFilteredEdge) || (fact->getFilterState(endNodeRef.getId()) == Filter::NotFiltered) || (!originalFilterState && visitFilteredEdge)) {
      if (apRoot && visitUsedSpecialNodesOnly && Common::getIsAPSpecNode(endNodeRef)) {
        unvisitedNodes[endNodeRef.getId()] = true;
      } else {
        endNodeRef.accept(*this);
      }
    }
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitEndHandler_HasExceptBody(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;
  }

  // edge: hasType
  genNodePtr = node.getType() ;
  if (genNodePtr) {
    const expression::Expression& endNodeRef = dynamic_cast<const expression::Expression&>(*genNodePtr);
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitHandler_HasType(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;

    if ((!fact->getIsFilterTurnedOn() && !visitFilteredEdge) || (fact->getFilterState(endNodeRef.getId()) == Filter::NotFiltered) || (!originalFilterState && visitFilteredEdge)) {
      if (apRoot && visitUsedSpecialNodesOnly && Common::getIsAPSpecNode(endNodeRef)) {
        unvisitedNodes[endNodeRef.getId()] = true;
      } else {
        endNodeRef.accept(*this);
      }
    }
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitEndHandler_HasType(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;
  }
}

void AlgorithmPreorder::visit(const statement::Handler& node, bool callFirst /*= true*/){
#ifdef DEBUG_PREORDER
  std::cout << "Rec. run: " << (unsigned int)&node << " " << node.getId() << " " << Common::toString(node.getNodeKind()) << std::endl;
#endif
  if (safeMode || visitCrossEdgeTree || visitSpecialNodes) {
    if (safeMode) {
      if (visitedNodes[node.getId()]) { // for safemode
        common::WriteMsg::write(CMSG_THE_PRE_ORDER_HAS_TOUCHED_A_NODE_TWICE,node.getId(),Common::toString(node.getNodeKind()).c_str() );
        return;
      }
    }
    visitedNodes[node.getId()] = true;
  }

  for (std::list<Visitor*>::iterator itVisitors = visitorList.begin();itVisitors != visitorList.end(); ++itVisitors) {
    (*itVisitors)->visit(node);
    incVisitorDepth((**itVisitors));
  }

  clearStoppedVisitors();
  if(needPreorderStop)
    return;

  visitAllEdges(node,true);

  for (std::list<Visitor*>::iterator itVisitors = visitorList.begin();itVisitors != visitorList.end(); ++itVisitors) {
    decVisitorDepth(**itVisitors);
    (*itVisitors)->visitEnd(node);
  }

  clearStoppedVisitors();
}

void AlgorithmPreorder::visitAllEdges(const statement::If& node, bool callFirst /*= true*/){
  visitAllEdges(dynamic_cast<const statement::CompoundStatement&>(node),false);

  std::list<Visitor*>::iterator itVisitors;

  const base::Base* genNodePtr;
  // edge: hasElseBody
  genNodePtr = node.getElseBody() ;
  if (genNodePtr) {
    const statement::Suite& endNodeRef = dynamic_cast<const statement::Suite&>(*genNodePtr);
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitIf_HasElseBody(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;

    if ((!fact->getIsFilterTurnedOn() && !visitFilteredEdge) || (fact->getFilterState(endNodeRef.getId()) == Filter::NotFiltered) || (!originalFilterState && visitFilteredEdge)) {
      if (apRoot && visitUsedSpecialNodesOnly && Common::getIsAPSpecNode(endNodeRef)) {
        unvisitedNodes[endNodeRef.getId()] = true;
      } else {
        endNodeRef.accept(*this);
      }
    }
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitEndIf_HasElseBody(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;
  }

  // edge: hasTestExpression
  genNodePtr = node.getTestExpression() ;
  if (genNodePtr) {
    const expression::Expression& endNodeRef = dynamic_cast<const expression::Expression&>(*genNodePtr);
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitIf_HasTestExpression(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;

    if ((!fact->getIsFilterTurnedOn() && !visitFilteredEdge) || (fact->getFilterState(endNodeRef.getId()) == Filter::NotFiltered) || (!originalFilterState && visitFilteredEdge)) {
      if (apRoot && visitUsedSpecialNodesOnly && Common::getIsAPSpecNode(endNodeRef)) {
        unvisitedNodes[endNodeRef.getId()] = true;
      } else {
        endNodeRef.accept(*this);
      }
    }
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitEndIf_HasTestExpression(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;
  }
}

void AlgorithmPreorder::visit(const statement::If& node, bool callFirst /*= true*/){
#ifdef DEBUG_PREORDER
  std::cout << "Rec. run: " << (unsigned int)&node << " " << node.getId() << " " << Common::toString(node.getNodeKind()) << std::endl;
#endif
  if (safeMode || visitCrossEdgeTree || visitSpecialNodes) {
    if (safeMode) {
      if (visitedNodes[node.getId()]) { // for safemode
        common::WriteMsg::write(CMSG_THE_PRE_ORDER_HAS_TOUCHED_A_NODE_TWICE,node.getId(),Common::toString(node.getNodeKind()).c_str() );
        return;
      }
    }
    visitedNodes[node.getId()] = true;
  }

  for (std::list<Visitor*>::iterator itVisitors = visitorList.begin();itVisitors != visitorList.end(); ++itVisitors) {
    (*itVisitors)->visit(node);
    incVisitorDepth((**itVisitors));
  }

  clearStoppedVisitors();
  if(needPreorderStop)
    return;

  visitAllEdges(node,true);

  for (std::list<Visitor*>::iterator itVisitors = visitorList.begin();itVisitors != visitorList.end(); ++itVisitors) {
    decVisitorDepth(**itVisitors);
    (*itVisitors)->visitEnd(node);
  }

  clearStoppedVisitors();
}

void AlgorithmPreorder::visitAllEdges(const statement::ImportFrom& node, bool callFirst /*= true*/){
  visitAllEdges(dynamic_cast<const statement::ImportStatement&>(node),false);
}

void AlgorithmPreorder::visit(const statement::ImportFrom& node, bool callFirst /*= true*/){
#ifdef DEBUG_PREORDER
  std::cout << "Rec. run: " << (unsigned int)&node << " " << node.getId() << " " << Common::toString(node.getNodeKind()) << std::endl;
#endif
  if (safeMode || visitCrossEdgeTree || visitSpecialNodes) {
    if (safeMode) {
      if (visitedNodes[node.getId()]) { // for safemode
        common::WriteMsg::write(CMSG_THE_PRE_ORDER_HAS_TOUCHED_A_NODE_TWICE,node.getId(),Common::toString(node.getNodeKind()).c_str() );
        return;
      }
    }
    visitedNodes[node.getId()] = true;
  }

  for (std::list<Visitor*>::iterator itVisitors = visitorList.begin();itVisitors != visitorList.end(); ++itVisitors) {
    (*itVisitors)->visit(node);
    incVisitorDepth((**itVisitors));
  }

  clearStoppedVisitors();
  if(needPreorderStop)
    return;

  visitAllEdges(node,true);

  for (std::list<Visitor*>::iterator itVisitors = visitorList.begin();itVisitors != visitorList.end(); ++itVisitors) {
    decVisitorDepth(**itVisitors);
    (*itVisitors)->visitEnd(node);
  }

  clearStoppedVisitors();
}

void AlgorithmPreorder::visitAllEdges(const statement::ImportStatement& node, bool callFirst /*= true*/){
  visitAllEdges(dynamic_cast<const statement::SimpleStatement&>(node),false);

  std::list<Visitor*>::iterator itVisitors;

  // edge: hasAlias
  for (ListIterator<statement::Alias> it = node.getAliasListIteratorBegin(); it != node.getAliasListIteratorEnd(); ++it) {
    const statement::Alias& endNodeRef = *it;
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitImportStatement_HasAlias(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;

    if ((!fact->getIsFilterTurnedOn() && !visitFilteredEdge) || (fact->getFilterState(endNodeRef.getId()) == Filter::NotFiltered) || (!originalFilterState && visitFilteredEdge)) {
      if (apRoot && visitUsedSpecialNodesOnly && Common::getIsAPSpecNode(endNodeRef)) {
        unvisitedNodes[endNodeRef.getId()] = true;
      } else {
        endNodeRef.accept(*this);
      }
    }
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitEndImportStatement_HasAlias(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;
  }
}

void AlgorithmPreorder::visit(const statement::ImportStatement& node, bool callFirst /*= true*/){
#ifdef DEBUG_PREORDER
  std::cout << "Rec. run: " << (unsigned int)&node << " " << node.getId() << " " << Common::toString(node.getNodeKind()) << std::endl;
#endif
  if (safeMode || visitCrossEdgeTree || visitSpecialNodes) {
    if (safeMode) {
      if (visitedNodes[node.getId()]) { // for safemode
        common::WriteMsg::write(CMSG_THE_PRE_ORDER_HAS_TOUCHED_A_NODE_TWICE,node.getId(),Common::toString(node.getNodeKind()).c_str() );
        return;
      }
    }
    visitedNodes[node.getId()] = true;
  }

  for (std::list<Visitor*>::iterator itVisitors = visitorList.begin();itVisitors != visitorList.end(); ++itVisitors) {
    (*itVisitors)->visit(node);
    incVisitorDepth((**itVisitors));
  }

  clearStoppedVisitors();
  if(needPreorderStop)
    return;

  visitAllEdges(node,true);

  for (std::list<Visitor*>::iterator itVisitors = visitorList.begin();itVisitors != visitorList.end(); ++itVisitors) {
    decVisitorDepth(**itVisitors);
    (*itVisitors)->visitEnd(node);
  }

  clearStoppedVisitors();
}

void AlgorithmPreorder::visitAllEdges(const statement::Iteration& node, bool callFirst /*= true*/){
  visitAllEdges(dynamic_cast<const statement::CompoundStatement&>(node),false);

  std::list<Visitor*>::iterator itVisitors;

  const base::Base* genNodePtr;
  // edge: hasElseBody
  genNodePtr = node.getElseBody() ;
  if (genNodePtr) {
    const statement::Suite& endNodeRef = dynamic_cast<const statement::Suite&>(*genNodePtr);
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitIteration_HasElseBody(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;

    if ((!fact->getIsFilterTurnedOn() && !visitFilteredEdge) || (fact->getFilterState(endNodeRef.getId()) == Filter::NotFiltered) || (!originalFilterState && visitFilteredEdge)) {
      if (apRoot && visitUsedSpecialNodesOnly && Common::getIsAPSpecNode(endNodeRef)) {
        unvisitedNodes[endNodeRef.getId()] = true;
      } else {
        endNodeRef.accept(*this);
      }
    }
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitEndIteration_HasElseBody(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;
  }
}

void AlgorithmPreorder::visitAllEdges(const statement::Parameter& node, bool callFirst /*= true*/){
  visitAllEdges(dynamic_cast<const base::Named&>(node),false);

  std::list<Visitor*>::iterator itVisitors;

  const base::Base* genNodePtr;
  // edge: hasDefaultValue
  genNodePtr = node.getDefaultValue() ;
  if (genNodePtr) {
    const expression::Expression& endNodeRef = dynamic_cast<const expression::Expression&>(*genNodePtr);
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitParameter_HasDefaultValue(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;

    if ((!fact->getIsFilterTurnedOn() && !visitFilteredEdge) || (fact->getFilterState(endNodeRef.getId()) == Filter::NotFiltered) || (!originalFilterState && visitFilteredEdge)) {
      if (apRoot && visitUsedSpecialNodesOnly && Common::getIsAPSpecNode(endNodeRef)) {
        unvisitedNodes[endNodeRef.getId()] = true;
      } else {
        endNodeRef.accept(*this);
      }
    }
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitEndParameter_HasDefaultValue(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;
  }

  // edge: refersTo
  genNodePtr = node.getRefersTo() ;
  if (genNodePtr) {
    const module::Object& endNodeRef = dynamic_cast<const module::Object&>(*genNodePtr);
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitParameter_RefersTo(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;

    if ((!fact->getIsFilterTurnedOn() && !visitFilteredEdge) || (fact->getFilterState(endNodeRef.getId()) == Filter::NotFiltered) || (!originalFilterState && visitFilteredEdge)) {
      if (apRoot) {
        if (visitCrossEdgeTree || (visitUsedSpecialNodesOnly && Common::getIsAPSpecNode(endNodeRef))) {
          unvisitedNodes[endNodeRef.getId()] = true;
        }
      }
      if (traversaldCrossEdges[edkParameter_RefersTo]) {
        endNodeRef.accept(*this);
      }
    }
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitEndParameter_RefersTo(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;
  }
}

void AlgorithmPreorder::visit(const statement::Parameter& node, bool callFirst /*= true*/){
#ifdef DEBUG_PREORDER
  std::cout << "Rec. run: " << (unsigned int)&node << " " << node.getId() << " " << Common::toString(node.getNodeKind()) << std::endl;
#endif
  if (safeMode || visitCrossEdgeTree || visitSpecialNodes) {
    if (safeMode) {
      if (visitedNodes[node.getId()]) { // for safemode
        common::WriteMsg::write(CMSG_THE_PRE_ORDER_HAS_TOUCHED_A_NODE_TWICE,node.getId(),Common::toString(node.getNodeKind()).c_str() );
        return;
      }
    }
    visitedNodes[node.getId()] = true;
  }

  for (std::list<Visitor*>::iterator itVisitors = visitorList.begin();itVisitors != visitorList.end(); ++itVisitors) {
    (*itVisitors)->visit(node);
    incVisitorDepth((**itVisitors));
  }

  clearStoppedVisitors();
  if(needPreorderStop)
    return;

  visitAllEdges(node,true);

  for (std::list<Visitor*>::iterator itVisitors = visitorList.begin();itVisitors != visitorList.end(); ++itVisitors) {
    decVisitorDepth(**itVisitors);
    (*itVisitors)->visitEnd(node);
  }

  clearStoppedVisitors();
}

void AlgorithmPreorder::visitAllEdges(const statement::Pass& node, bool callFirst /*= true*/){
  visitAllEdges(dynamic_cast<const statement::SimpleStatement&>(node),false);
}

void AlgorithmPreorder::visit(const statement::Pass& node, bool callFirst /*= true*/){
#ifdef DEBUG_PREORDER
  std::cout << "Rec. run: " << (unsigned int)&node << " " << node.getId() << " " << Common::toString(node.getNodeKind()) << std::endl;
#endif
  if (safeMode || visitCrossEdgeTree || visitSpecialNodes) {
    if (safeMode) {
      if (visitedNodes[node.getId()]) { // for safemode
        common::WriteMsg::write(CMSG_THE_PRE_ORDER_HAS_TOUCHED_A_NODE_TWICE,node.getId(),Common::toString(node.getNodeKind()).c_str() );
        return;
      }
    }
    visitedNodes[node.getId()] = true;
  }

  for (std::list<Visitor*>::iterator itVisitors = visitorList.begin();itVisitors != visitorList.end(); ++itVisitors) {
    (*itVisitors)->visit(node);
    incVisitorDepth((**itVisitors));
  }

  clearStoppedVisitors();
  if(needPreorderStop)
    return;

  visitAllEdges(node,true);

  for (std::list<Visitor*>::iterator itVisitors = visitorList.begin();itVisitors != visitorList.end(); ++itVisitors) {
    decVisitorDepth(**itVisitors);
    (*itVisitors)->visitEnd(node);
  }

  clearStoppedVisitors();
}

void AlgorithmPreorder::visitAllEdges(const statement::Print& node, bool callFirst /*= true*/){
  visitAllEdges(dynamic_cast<const statement::SimpleStatement&>(node),false);

  std::list<Visitor*>::iterator itVisitors;

  const base::Base* genNodePtr;
  // edge: hasExpressionList
  genNodePtr = node.getExpressionList() ;
  if (genNodePtr) {
    const expression::ExpressionList& endNodeRef = dynamic_cast<const expression::ExpressionList&>(*genNodePtr);
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitPrint_HasExpressionList(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;

    if ((!fact->getIsFilterTurnedOn() && !visitFilteredEdge) || (fact->getFilterState(endNodeRef.getId()) == Filter::NotFiltered) || (!originalFilterState && visitFilteredEdge)) {
      if (apRoot && visitUsedSpecialNodesOnly && Common::getIsAPSpecNode(endNodeRef)) {
        unvisitedNodes[endNodeRef.getId()] = true;
      } else {
        endNodeRef.accept(*this);
      }
    }
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitEndPrint_HasExpressionList(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;
  }

  // edge: hasDestination
  genNodePtr = node.getDestination() ;
  if (genNodePtr) {
    const expression::Expression& endNodeRef = dynamic_cast<const expression::Expression&>(*genNodePtr);
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitPrint_HasDestination(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;

    if ((!fact->getIsFilterTurnedOn() && !visitFilteredEdge) || (fact->getFilterState(endNodeRef.getId()) == Filter::NotFiltered) || (!originalFilterState && visitFilteredEdge)) {
      if (apRoot && visitUsedSpecialNodesOnly && Common::getIsAPSpecNode(endNodeRef)) {
        unvisitedNodes[endNodeRef.getId()] = true;
      } else {
        endNodeRef.accept(*this);
      }
    }
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitEndPrint_HasDestination(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;
  }
}

void AlgorithmPreorder::visit(const statement::Print& node, bool callFirst /*= true*/){
#ifdef DEBUG_PREORDER
  std::cout << "Rec. run: " << (unsigned int)&node << " " << node.getId() << " " << Common::toString(node.getNodeKind()) << std::endl;
#endif
  if (safeMode || visitCrossEdgeTree || visitSpecialNodes) {
    if (safeMode) {
      if (visitedNodes[node.getId()]) { // for safemode
        common::WriteMsg::write(CMSG_THE_PRE_ORDER_HAS_TOUCHED_A_NODE_TWICE,node.getId(),Common::toString(node.getNodeKind()).c_str() );
        return;
      }
    }
    visitedNodes[node.getId()] = true;
  }

  for (std::list<Visitor*>::iterator itVisitors = visitorList.begin();itVisitors != visitorList.end(); ++itVisitors) {
    (*itVisitors)->visit(node);
    incVisitorDepth((**itVisitors));
  }

  clearStoppedVisitors();
  if(needPreorderStop)
    return;

  visitAllEdges(node,true);

  for (std::list<Visitor*>::iterator itVisitors = visitorList.begin();itVisitors != visitorList.end(); ++itVisitors) {
    decVisitorDepth(**itVisitors);
    (*itVisitors)->visitEnd(node);
  }

  clearStoppedVisitors();
}

void AlgorithmPreorder::visitAllEdges(const statement::Raise& node, bool callFirst /*= true*/){
  visitAllEdges(dynamic_cast<const statement::SimpleStatement&>(node),false);

  std::list<Visitor*>::iterator itVisitors;

  const base::Base* genNodePtr;
  // edge: hasTracebackExpression
  genNodePtr = node.getTracebackExpression() ;
  if (genNodePtr) {
    const expression::Expression& endNodeRef = dynamic_cast<const expression::Expression&>(*genNodePtr);
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitRaise_HasTracebackExpression(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;

    if ((!fact->getIsFilterTurnedOn() && !visitFilteredEdge) || (fact->getFilterState(endNodeRef.getId()) == Filter::NotFiltered) || (!originalFilterState && visitFilteredEdge)) {
      if (apRoot && visitUsedSpecialNodesOnly && Common::getIsAPSpecNode(endNodeRef)) {
        unvisitedNodes[endNodeRef.getId()] = true;
      } else {
        endNodeRef.accept(*this);
      }
    }
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitEndRaise_HasTracebackExpression(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;
  }

  // edge: hasTypeExpression
  genNodePtr = node.getTypeExpression() ;
  if (genNodePtr) {
    const expression::Expression& endNodeRef = dynamic_cast<const expression::Expression&>(*genNodePtr);
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitRaise_HasTypeExpression(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;

    if ((!fact->getIsFilterTurnedOn() && !visitFilteredEdge) || (fact->getFilterState(endNodeRef.getId()) == Filter::NotFiltered) || (!originalFilterState && visitFilteredEdge)) {
      if (apRoot && visitUsedSpecialNodesOnly && Common::getIsAPSpecNode(endNodeRef)) {
        unvisitedNodes[endNodeRef.getId()] = true;
      } else {
        endNodeRef.accept(*this);
      }
    }
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitEndRaise_HasTypeExpression(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;
  }

  // edge: hasValueExpression
  genNodePtr = node.getValueExpression() ;
  if (genNodePtr) {
    const expression::Expression& endNodeRef = dynamic_cast<const expression::Expression&>(*genNodePtr);
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitRaise_HasValueExpression(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;

    if ((!fact->getIsFilterTurnedOn() && !visitFilteredEdge) || (fact->getFilterState(endNodeRef.getId()) == Filter::NotFiltered) || (!originalFilterState && visitFilteredEdge)) {
      if (apRoot && visitUsedSpecialNodesOnly && Common::getIsAPSpecNode(endNodeRef)) {
        unvisitedNodes[endNodeRef.getId()] = true;
      } else {
        endNodeRef.accept(*this);
      }
    }
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitEndRaise_HasValueExpression(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;
  }
}

void AlgorithmPreorder::visit(const statement::Raise& node, bool callFirst /*= true*/){
#ifdef DEBUG_PREORDER
  std::cout << "Rec. run: " << (unsigned int)&node << " " << node.getId() << " " << Common::toString(node.getNodeKind()) << std::endl;
#endif
  if (safeMode || visitCrossEdgeTree || visitSpecialNodes) {
    if (safeMode) {
      if (visitedNodes[node.getId()]) { // for safemode
        common::WriteMsg::write(CMSG_THE_PRE_ORDER_HAS_TOUCHED_A_NODE_TWICE,node.getId(),Common::toString(node.getNodeKind()).c_str() );
        return;
      }
    }
    visitedNodes[node.getId()] = true;
  }

  for (std::list<Visitor*>::iterator itVisitors = visitorList.begin();itVisitors != visitorList.end(); ++itVisitors) {
    (*itVisitors)->visit(node);
    incVisitorDepth((**itVisitors));
  }

  clearStoppedVisitors();
  if(needPreorderStop)
    return;

  visitAllEdges(node,true);

  for (std::list<Visitor*>::iterator itVisitors = visitorList.begin();itVisitors != visitorList.end(); ++itVisitors) {
    decVisitorDepth(**itVisitors);
    (*itVisitors)->visitEnd(node);
  }

  clearStoppedVisitors();
}

void AlgorithmPreorder::visitAllEdges(const statement::Return& node, bool callFirst /*= true*/){
  visitAllEdges(dynamic_cast<const statement::SimpleStatement&>(node),false);

  std::list<Visitor*>::iterator itVisitors;

  const base::Base* genNodePtr;
  // edge: hasExpression
  genNodePtr = node.getExpression() ;
  if (genNodePtr) {
    const expression::Expression& endNodeRef = dynamic_cast<const expression::Expression&>(*genNodePtr);
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitReturn_HasExpression(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;

    if ((!fact->getIsFilterTurnedOn() && !visitFilteredEdge) || (fact->getFilterState(endNodeRef.getId()) == Filter::NotFiltered) || (!originalFilterState && visitFilteredEdge)) {
      if (apRoot && visitUsedSpecialNodesOnly && Common::getIsAPSpecNode(endNodeRef)) {
        unvisitedNodes[endNodeRef.getId()] = true;
      } else {
        endNodeRef.accept(*this);
      }
    }
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitEndReturn_HasExpression(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;
  }
}

void AlgorithmPreorder::visit(const statement::Return& node, bool callFirst /*= true*/){
#ifdef DEBUG_PREORDER
  std::cout << "Rec. run: " << (unsigned int)&node << " " << node.getId() << " " << Common::toString(node.getNodeKind()) << std::endl;
#endif
  if (safeMode || visitCrossEdgeTree || visitSpecialNodes) {
    if (safeMode) {
      if (visitedNodes[node.getId()]) { // for safemode
        common::WriteMsg::write(CMSG_THE_PRE_ORDER_HAS_TOUCHED_A_NODE_TWICE,node.getId(),Common::toString(node.getNodeKind()).c_str() );
        return;
      }
    }
    visitedNodes[node.getId()] = true;
  }

  for (std::list<Visitor*>::iterator itVisitors = visitorList.begin();itVisitors != visitorList.end(); ++itVisitors) {
    (*itVisitors)->visit(node);
    incVisitorDepth((**itVisitors));
  }

  clearStoppedVisitors();
  if(needPreorderStop)
    return;

  visitAllEdges(node,true);

  for (std::list<Visitor*>::iterator itVisitors = visitorList.begin();itVisitors != visitorList.end(); ++itVisitors) {
    decVisitorDepth(**itVisitors);
    (*itVisitors)->visitEnd(node);
  }

  clearStoppedVisitors();
}

void AlgorithmPreorder::visitAllEdges(const statement::SimpleStatement& node, bool callFirst /*= true*/){
  visitAllEdges(dynamic_cast<const statement::Statement&>(node),false);
}

void AlgorithmPreorder::visitAllEdges(const statement::Statement& node, bool callFirst /*= true*/){
  visitAllEdges(dynamic_cast<const base::Positioned&>(node),false);
}

void AlgorithmPreorder::visitAllEdges(const statement::Suite& node, bool callFirst /*= true*/){
  visitAllEdges(dynamic_cast<const base::Positioned&>(node),false);

  std::list<Visitor*>::iterator itVisitors;

  // edge: hasStatement
  for (ListIterator<base::Positioned> it = node.getStatementListIteratorBegin(); it != node.getStatementListIteratorEnd(); ++it) {
    const base::Positioned& endNodeRef = *it;
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitSuite_HasStatement(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;

    if ((!fact->getIsFilterTurnedOn() && !visitFilteredEdge) || (fact->getFilterState(endNodeRef.getId()) == Filter::NotFiltered) || (!originalFilterState && visitFilteredEdge)) {
      if (apRoot && visitUsedSpecialNodesOnly && Common::getIsAPSpecNode(endNodeRef)) {
        unvisitedNodes[endNodeRef.getId()] = true;
      } else {
        endNodeRef.accept(*this);
      }
    }
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitEndSuite_HasStatement(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;
  }
}

void AlgorithmPreorder::visit(const statement::Suite& node, bool callFirst /*= true*/){
#ifdef DEBUG_PREORDER
  std::cout << "Rec. run: " << (unsigned int)&node << " " << node.getId() << " " << Common::toString(node.getNodeKind()) << std::endl;
#endif
  if (safeMode || visitCrossEdgeTree || visitSpecialNodes) {
    if (safeMode) {
      if (visitedNodes[node.getId()]) { // for safemode
        common::WriteMsg::write(CMSG_THE_PRE_ORDER_HAS_TOUCHED_A_NODE_TWICE,node.getId(),Common::toString(node.getNodeKind()).c_str() );
        return;
      }
    }
    visitedNodes[node.getId()] = true;
  }

  for (std::list<Visitor*>::iterator itVisitors = visitorList.begin();itVisitors != visitorList.end(); ++itVisitors) {
    (*itVisitors)->visit(node);
    incVisitorDepth((**itVisitors));
  }

  clearStoppedVisitors();
  if(needPreorderStop)
    return;

  visitAllEdges(node,true);

  for (std::list<Visitor*>::iterator itVisitors = visitorList.begin();itVisitors != visitorList.end(); ++itVisitors) {
    decVisitorDepth(**itVisitors);
    (*itVisitors)->visitEnd(node);
  }

  clearStoppedVisitors();
}

void AlgorithmPreorder::visitAllEdges(const statement::TargetList& node, bool callFirst /*= true*/){
  visitAllEdges(dynamic_cast<const base::Positioned&>(node),false);

  std::list<Visitor*>::iterator itVisitors;

  // edge: hasTarget
  for (ListIterator<expression::Expression> it = node.getTargetListIteratorBegin(); it != node.getTargetListIteratorEnd(); ++it) {
    const expression::Expression& endNodeRef = *it;
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitTargetList_HasTarget(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;

    if ((!fact->getIsFilterTurnedOn() && !visitFilteredEdge) || (fact->getFilterState(endNodeRef.getId()) == Filter::NotFiltered) || (!originalFilterState && visitFilteredEdge)) {
      if (apRoot && visitUsedSpecialNodesOnly && Common::getIsAPSpecNode(endNodeRef)) {
        unvisitedNodes[endNodeRef.getId()] = true;
      } else {
        endNodeRef.accept(*this);
      }
    }
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitEndTargetList_HasTarget(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;
  }
}

void AlgorithmPreorder::visit(const statement::TargetList& node, bool callFirst /*= true*/){
#ifdef DEBUG_PREORDER
  std::cout << "Rec. run: " << (unsigned int)&node << " " << node.getId() << " " << Common::toString(node.getNodeKind()) << std::endl;
#endif
  if (safeMode || visitCrossEdgeTree || visitSpecialNodes) {
    if (safeMode) {
      if (visitedNodes[node.getId()]) { // for safemode
        common::WriteMsg::write(CMSG_THE_PRE_ORDER_HAS_TOUCHED_A_NODE_TWICE,node.getId(),Common::toString(node.getNodeKind()).c_str() );
        return;
      }
    }
    visitedNodes[node.getId()] = true;
  }

  for (std::list<Visitor*>::iterator itVisitors = visitorList.begin();itVisitors != visitorList.end(); ++itVisitors) {
    (*itVisitors)->visit(node);
    incVisitorDepth((**itVisitors));
  }

  clearStoppedVisitors();
  if(needPreorderStop)
    return;

  visitAllEdges(node,true);

  for (std::list<Visitor*>::iterator itVisitors = visitorList.begin();itVisitors != visitorList.end(); ++itVisitors) {
    decVisitorDepth(**itVisitors);
    (*itVisitors)->visitEnd(node);
  }

  clearStoppedVisitors();
}

void AlgorithmPreorder::visitAllEdges(const statement::Try& node, bool callFirst /*= true*/){
  visitAllEdges(dynamic_cast<const statement::CompoundStatement&>(node),false);
}

void AlgorithmPreorder::visitAllEdges(const statement::TryExcept& node, bool callFirst /*= true*/){
  visitAllEdges(dynamic_cast<const statement::Try&>(node),false);

  std::list<Visitor*>::iterator itVisitors;

  const base::Base* genNodePtr;
  // edge: hasElseBody
  genNodePtr = node.getElseBody() ;
  if (genNodePtr) {
    const statement::Suite& endNodeRef = dynamic_cast<const statement::Suite&>(*genNodePtr);
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitTryExcept_HasElseBody(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;

    if ((!fact->getIsFilterTurnedOn() && !visitFilteredEdge) || (fact->getFilterState(endNodeRef.getId()) == Filter::NotFiltered) || (!originalFilterState && visitFilteredEdge)) {
      if (apRoot && visitUsedSpecialNodesOnly && Common::getIsAPSpecNode(endNodeRef)) {
        unvisitedNodes[endNodeRef.getId()] = true;
      } else {
        endNodeRef.accept(*this);
      }
    }
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitEndTryExcept_HasElseBody(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;
  }

  // edge: hasHandler
  for (ListIterator<statement::Handler> it = node.getHandlerListIteratorBegin(); it != node.getHandlerListIteratorEnd(); ++it) {
    const statement::Handler& endNodeRef = *it;
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitTryExcept_HasHandler(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;

    if ((!fact->getIsFilterTurnedOn() && !visitFilteredEdge) || (fact->getFilterState(endNodeRef.getId()) == Filter::NotFiltered) || (!originalFilterState && visitFilteredEdge)) {
      if (apRoot && visitUsedSpecialNodesOnly && Common::getIsAPSpecNode(endNodeRef)) {
        unvisitedNodes[endNodeRef.getId()] = true;
      } else {
        endNodeRef.accept(*this);
      }
    }
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitEndTryExcept_HasHandler(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;
  }

  // edge: hasFinallyBody
  genNodePtr = node.getFinallyBody() ;
  if (genNodePtr) {
    const statement::Suite& endNodeRef = dynamic_cast<const statement::Suite&>(*genNodePtr);
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitTryExcept_HasFinallyBody(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;

    if ((!fact->getIsFilterTurnedOn() && !visitFilteredEdge) || (fact->getFilterState(endNodeRef.getId()) == Filter::NotFiltered) || (!originalFilterState && visitFilteredEdge)) {
      if (apRoot && visitUsedSpecialNodesOnly && Common::getIsAPSpecNode(endNodeRef)) {
        unvisitedNodes[endNodeRef.getId()] = true;
      } else {
        endNodeRef.accept(*this);
      }
    }
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitEndTryExcept_HasFinallyBody(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;
  }
}

void AlgorithmPreorder::visit(const statement::TryExcept& node, bool callFirst /*= true*/){
#ifdef DEBUG_PREORDER
  std::cout << "Rec. run: " << (unsigned int)&node << " " << node.getId() << " " << Common::toString(node.getNodeKind()) << std::endl;
#endif
  if (safeMode || visitCrossEdgeTree || visitSpecialNodes) {
    if (safeMode) {
      if (visitedNodes[node.getId()]) { // for safemode
        common::WriteMsg::write(CMSG_THE_PRE_ORDER_HAS_TOUCHED_A_NODE_TWICE,node.getId(),Common::toString(node.getNodeKind()).c_str() );
        return;
      }
    }
    visitedNodes[node.getId()] = true;
  }

  for (std::list<Visitor*>::iterator itVisitors = visitorList.begin();itVisitors != visitorList.end(); ++itVisitors) {
    (*itVisitors)->visit(node);
    incVisitorDepth((**itVisitors));
  }

  clearStoppedVisitors();
  if(needPreorderStop)
    return;

  visitAllEdges(node,true);

  for (std::list<Visitor*>::iterator itVisitors = visitorList.begin();itVisitors != visitorList.end(); ++itVisitors) {
    decVisitorDepth(**itVisitors);
    (*itVisitors)->visitEnd(node);
  }

  clearStoppedVisitors();
}

void AlgorithmPreorder::visitAllEdges(const statement::TryFinal& node, bool callFirst /*= true*/){
  visitAllEdges(dynamic_cast<const statement::Try&>(node),false);

  std::list<Visitor*>::iterator itVisitors;

  const base::Base* genNodePtr;
  // edge: hasFinallyBody
  genNodePtr = node.getFinallyBody() ;
  if (genNodePtr) {
    const statement::Suite& endNodeRef = dynamic_cast<const statement::Suite&>(*genNodePtr);
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitTryFinal_HasFinallyBody(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;

    if ((!fact->getIsFilterTurnedOn() && !visitFilteredEdge) || (fact->getFilterState(endNodeRef.getId()) == Filter::NotFiltered) || (!originalFilterState && visitFilteredEdge)) {
      if (apRoot && visitUsedSpecialNodesOnly && Common::getIsAPSpecNode(endNodeRef)) {
        unvisitedNodes[endNodeRef.getId()] = true;
      } else {
        endNodeRef.accept(*this);
      }
    }
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitEndTryFinal_HasFinallyBody(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;
  }
}

void AlgorithmPreorder::visit(const statement::TryFinal& node, bool callFirst /*= true*/){
#ifdef DEBUG_PREORDER
  std::cout << "Rec. run: " << (unsigned int)&node << " " << node.getId() << " " << Common::toString(node.getNodeKind()) << std::endl;
#endif
  if (safeMode || visitCrossEdgeTree || visitSpecialNodes) {
    if (safeMode) {
      if (visitedNodes[node.getId()]) { // for safemode
        common::WriteMsg::write(CMSG_THE_PRE_ORDER_HAS_TOUCHED_A_NODE_TWICE,node.getId(),Common::toString(node.getNodeKind()).c_str() );
        return;
      }
    }
    visitedNodes[node.getId()] = true;
  }

  for (std::list<Visitor*>::iterator itVisitors = visitorList.begin();itVisitors != visitorList.end(); ++itVisitors) {
    (*itVisitors)->visit(node);
    incVisitorDepth((**itVisitors));
  }

  clearStoppedVisitors();
  if(needPreorderStop)
    return;

  visitAllEdges(node,true);

  for (std::list<Visitor*>::iterator itVisitors = visitorList.begin();itVisitors != visitorList.end(); ++itVisitors) {
    decVisitorDepth(**itVisitors);
    (*itVisitors)->visitEnd(node);
  }

  clearStoppedVisitors();
}

void AlgorithmPreorder::visitAllEdges(const statement::While& node, bool callFirst /*= true*/){
  visitAllEdges(dynamic_cast<const statement::Iteration&>(node),false);

  std::list<Visitor*>::iterator itVisitors;

  const base::Base* genNodePtr;
  // edge: hasTestExpression
  genNodePtr = node.getTestExpression() ;
  if (genNodePtr) {
    const expression::Expression& endNodeRef = dynamic_cast<const expression::Expression&>(*genNodePtr);
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitWhile_HasTestExpression(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;

    if ((!fact->getIsFilterTurnedOn() && !visitFilteredEdge) || (fact->getFilterState(endNodeRef.getId()) == Filter::NotFiltered) || (!originalFilterState && visitFilteredEdge)) {
      if (apRoot && visitUsedSpecialNodesOnly && Common::getIsAPSpecNode(endNodeRef)) {
        unvisitedNodes[endNodeRef.getId()] = true;
      } else {
        endNodeRef.accept(*this);
      }
    }
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitEndWhile_HasTestExpression(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;
  }
}

void AlgorithmPreorder::visit(const statement::While& node, bool callFirst /*= true*/){
#ifdef DEBUG_PREORDER
  std::cout << "Rec. run: " << (unsigned int)&node << " " << node.getId() << " " << Common::toString(node.getNodeKind()) << std::endl;
#endif
  if (safeMode || visitCrossEdgeTree || visitSpecialNodes) {
    if (safeMode) {
      if (visitedNodes[node.getId()]) { // for safemode
        common::WriteMsg::write(CMSG_THE_PRE_ORDER_HAS_TOUCHED_A_NODE_TWICE,node.getId(),Common::toString(node.getNodeKind()).c_str() );
        return;
      }
    }
    visitedNodes[node.getId()] = true;
  }

  for (std::list<Visitor*>::iterator itVisitors = visitorList.begin();itVisitors != visitorList.end(); ++itVisitors) {
    (*itVisitors)->visit(node);
    incVisitorDepth((**itVisitors));
  }

  clearStoppedVisitors();
  if(needPreorderStop)
    return;

  visitAllEdges(node,true);

  for (std::list<Visitor*>::iterator itVisitors = visitorList.begin();itVisitors != visitorList.end(); ++itVisitors) {
    decVisitorDepth(**itVisitors);
    (*itVisitors)->visitEnd(node);
  }

  clearStoppedVisitors();
}

void AlgorithmPreorder::visitAllEdges(const statement::With& node, bool callFirst /*= true*/){
  visitAllEdges(dynamic_cast<const statement::CompoundStatement&>(node),false);

  std::list<Visitor*>::iterator itVisitors;

  const base::Base* genNodePtr;
  // edge: hasExpression
  genNodePtr = node.getExpression() ;
  if (genNodePtr) {
    const expression::Expression& endNodeRef = dynamic_cast<const expression::Expression&>(*genNodePtr);
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitWith_HasExpression(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;

    if ((!fact->getIsFilterTurnedOn() && !visitFilteredEdge) || (fact->getFilterState(endNodeRef.getId()) == Filter::NotFiltered) || (!originalFilterState && visitFilteredEdge)) {
      if (apRoot && visitUsedSpecialNodesOnly && Common::getIsAPSpecNode(endNodeRef)) {
        unvisitedNodes[endNodeRef.getId()] = true;
      } else {
        endNodeRef.accept(*this);
      }
    }
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitEndWith_HasExpression(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;
  }

  // edge: hasTargetList
  genNodePtr = node.getTargetList() ;
  if (genNodePtr) {
    const statement::TargetList& endNodeRef = dynamic_cast<const statement::TargetList&>(*genNodePtr);
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitWith_HasTargetList(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;

    if ((!fact->getIsFilterTurnedOn() && !visitFilteredEdge) || (fact->getFilterState(endNodeRef.getId()) == Filter::NotFiltered) || (!originalFilterState && visitFilteredEdge)) {
      if (apRoot && visitUsedSpecialNodesOnly && Common::getIsAPSpecNode(endNodeRef)) {
        unvisitedNodes[endNodeRef.getId()] = true;
      } else {
        endNodeRef.accept(*this);
      }
    }
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitEndWith_HasTargetList(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;
  }
}

void AlgorithmPreorder::visit(const statement::With& node, bool callFirst /*= true*/){
#ifdef DEBUG_PREORDER
  std::cout << "Rec. run: " << (unsigned int)&node << " " << node.getId() << " " << Common::toString(node.getNodeKind()) << std::endl;
#endif
  if (safeMode || visitCrossEdgeTree || visitSpecialNodes) {
    if (safeMode) {
      if (visitedNodes[node.getId()]) { // for safemode
        common::WriteMsg::write(CMSG_THE_PRE_ORDER_HAS_TOUCHED_A_NODE_TWICE,node.getId(),Common::toString(node.getNodeKind()).c_str() );
        return;
      }
    }
    visitedNodes[node.getId()] = true;
  }

  for (std::list<Visitor*>::iterator itVisitors = visitorList.begin();itVisitors != visitorList.end(); ++itVisitors) {
    (*itVisitors)->visit(node);
    incVisitorDepth((**itVisitors));
  }

  clearStoppedVisitors();
  if(needPreorderStop)
    return;

  visitAllEdges(node,true);

  for (std::list<Visitor*>::iterator itVisitors = visitorList.begin();itVisitors != visitorList.end(); ++itVisitors) {
    decVisitorDepth(**itVisitors);
    (*itVisitors)->visitEnd(node);
  }

  clearStoppedVisitors();
}

void AlgorithmPreorder::visitAllEdges(const type::DictType& node, bool callFirst /*= true*/){
  visitAllEdges(dynamic_cast<const type::Type&>(node),false);
}

void AlgorithmPreorder::visit(const type::DictType& node, bool callFirst /*= true*/){
#ifdef DEBUG_PREORDER
  std::cout << "Rec. run: " << (unsigned int)&node << " " << node.getId() << " " << Common::toString(node.getNodeKind()) << std::endl;
#endif
  if (safeMode || visitCrossEdgeTree || visitSpecialNodes) {
    if (safeMode) {
      if (visitedNodes[node.getId()]) { // for safemode
        common::WriteMsg::write(CMSG_THE_PRE_ORDER_HAS_TOUCHED_A_NODE_TWICE,node.getId(),Common::toString(node.getNodeKind()).c_str() );
        return;
      }
    }
    visitedNodes[node.getId()] = true;
  }

  for (std::list<Visitor*>::iterator itVisitors = visitorList.begin();itVisitors != visitorList.end(); ++itVisitors) {
    (*itVisitors)->visit(node);
    incVisitorDepth((**itVisitors));
  }

  clearStoppedVisitors();
  if(needPreorderStop)
    return;

  visitAllEdges(node,true);

  for (std::list<Visitor*>::iterator itVisitors = visitorList.begin();itVisitors != visitorList.end(); ++itVisitors) {
    decVisitorDepth(**itVisitors);
    (*itVisitors)->visitEnd(node);
  }

  clearStoppedVisitors();
}

void AlgorithmPreorder::visitAllEdges(const type::ReferenceType& node, bool callFirst /*= true*/){
  visitAllEdges(dynamic_cast<const type::Type&>(node),false);

  std::list<Visitor*>::iterator itVisitors;

  const base::Base* genNodePtr;
  // edge: refersTo
  genNodePtr = node.getRefersTo() ;
  if (genNodePtr) {
    const base::Positioned& endNodeRef = dynamic_cast<const base::Positioned&>(*genNodePtr);
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitReferenceType_RefersTo(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;

    if ((!fact->getIsFilterTurnedOn() && !visitFilteredEdge) || (fact->getFilterState(endNodeRef.getId()) == Filter::NotFiltered) || (!originalFilterState && visitFilteredEdge)) {
      if (apRoot) {
        if (visitCrossEdgeTree || (visitUsedSpecialNodesOnly && Common::getIsAPSpecNode(endNodeRef))) {
          unvisitedNodes[endNodeRef.getId()] = true;
        }
      }
      if (traversaldCrossEdges[edkReferenceType_RefersTo]) {
        endNodeRef.accept(*this);
      }
    }
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitEndReferenceType_RefersTo(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;
  }
}

void AlgorithmPreorder::visit(const type::ReferenceType& node, bool callFirst /*= true*/){
#ifdef DEBUG_PREORDER
  std::cout << "Rec. run: " << (unsigned int)&node << " " << node.getId() << " " << Common::toString(node.getNodeKind()) << std::endl;
#endif
  if (safeMode || visitCrossEdgeTree || visitSpecialNodes) {
    if (safeMode) {
      if (visitedNodes[node.getId()]) { // for safemode
        common::WriteMsg::write(CMSG_THE_PRE_ORDER_HAS_TOUCHED_A_NODE_TWICE,node.getId(),Common::toString(node.getNodeKind()).c_str() );
        return;
      }
    }
    visitedNodes[node.getId()] = true;
  }

  for (std::list<Visitor*>::iterator itVisitors = visitorList.begin();itVisitors != visitorList.end(); ++itVisitors) {
    (*itVisitors)->visit(node);
    incVisitorDepth((**itVisitors));
  }

  clearStoppedVisitors();
  if(needPreorderStop)
    return;

  visitAllEdges(node,true);

  for (std::list<Visitor*>::iterator itVisitors = visitorList.begin();itVisitors != visitorList.end(); ++itVisitors) {
    decVisitorDepth(**itVisitors);
    (*itVisitors)->visitEnd(node);
  }

  clearStoppedVisitors();
}

void AlgorithmPreorder::visitAllEdges(const type::SequenceType& node, bool callFirst /*= true*/){
  visitAllEdges(dynamic_cast<const type::Type&>(node),false);
}

void AlgorithmPreorder::visit(const type::SequenceType& node, bool callFirst /*= true*/){
#ifdef DEBUG_PREORDER
  std::cout << "Rec. run: " << (unsigned int)&node << " " << node.getId() << " " << Common::toString(node.getNodeKind()) << std::endl;
#endif
  if (safeMode || visitCrossEdgeTree || visitSpecialNodes) {
    if (safeMode) {
      if (visitedNodes[node.getId()]) { // for safemode
        common::WriteMsg::write(CMSG_THE_PRE_ORDER_HAS_TOUCHED_A_NODE_TWICE,node.getId(),Common::toString(node.getNodeKind()).c_str() );
        return;
      }
    }
    visitedNodes[node.getId()] = true;
  }

  for (std::list<Visitor*>::iterator itVisitors = visitorList.begin();itVisitors != visitorList.end(); ++itVisitors) {
    (*itVisitors)->visit(node);
    incVisitorDepth((**itVisitors));
  }

  clearStoppedVisitors();
  if(needPreorderStop)
    return;

  visitAllEdges(node,true);

  for (std::list<Visitor*>::iterator itVisitors = visitorList.begin();itVisitors != visitorList.end(); ++itVisitors) {
    decVisitorDepth(**itVisitors);
    (*itVisitors)->visitEnd(node);
  }

  clearStoppedVisitors();
}

void AlgorithmPreorder::visitAllEdges(const type::SimpleType& node, bool callFirst /*= true*/){
  visitAllEdges(dynamic_cast<const type::Type&>(node),false);
}

void AlgorithmPreorder::visit(const type::SimpleType& node, bool callFirst /*= true*/){
#ifdef DEBUG_PREORDER
  std::cout << "Rec. run: " << (unsigned int)&node << " " << node.getId() << " " << Common::toString(node.getNodeKind()) << std::endl;
#endif
  if (safeMode || visitCrossEdgeTree || visitSpecialNodes) {
    if (safeMode) {
      if (visitedNodes[node.getId()]) { // for safemode
        common::WriteMsg::write(CMSG_THE_PRE_ORDER_HAS_TOUCHED_A_NODE_TWICE,node.getId(),Common::toString(node.getNodeKind()).c_str() );
        return;
      }
    }
    visitedNodes[node.getId()] = true;
  }

  for (std::list<Visitor*>::iterator itVisitors = visitorList.begin();itVisitors != visitorList.end(); ++itVisitors) {
    (*itVisitors)->visit(node);
    incVisitorDepth((**itVisitors));
  }

  clearStoppedVisitors();
  if(needPreorderStop)
    return;

  visitAllEdges(node,true);

  for (std::list<Visitor*>::iterator itVisitors = visitorList.begin();itVisitors != visitorList.end(); ++itVisitors) {
    decVisitorDepth(**itVisitors);
    (*itVisitors)->visitEnd(node);
  }

  clearStoppedVisitors();
}

void AlgorithmPreorder::visitAllEdges(const type::Type& node, bool callFirst /*= true*/){
  visitAllEdges(dynamic_cast<const base::Base&>(node),false);
}

void AlgorithmPreorder::startPreorder(){

  if (!fact){
    throw PythonException(COLUMBUS_LOCATION, CMSG_EX_YOU_MUST_GIVE_A_FACTORY_AT_FIRST);
  }

  if (visitorList.empty()){
    throw PythonException(COLUMBUS_LOCATION, CMSG_EX_DON_T_HAVE_ANY_VISITOR);
  }

  if (safeMode || visitCrossEdgeTree || visitSpecialNodes) {
    visitedNodes.clear();
    visitedNodes.resize(fact->size(), false);
  }

  if (visitCrossEdgeTree || visitSpecialNodes) {
    unvisitedNodes.clear();
    unvisitedNodes.resize(fact->size(), false);
  }

  if (visitFilteredEdge){
    originalFilterState = fact->getIsFilterTurnedOn();
    fact->turnFilterOff();
  }

  for (std::list<Visitor*>::iterator itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
    (*itVisitors)->beginVisit();
  }

}

void AlgorithmPreorder::endPreorder(){

  for (std::list<Visitor*>::iterator itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
    (*itVisitors)->finishVisit();
  }

  if (visitFilteredEdge){
    if (originalFilterState)
      fact->turnFilterOn();
  }

}

void AlgorithmPreorder::setCrossEdgeToTraversal(EdgeKind edgekind){

  traversaldCrossEdges[edgekind] = true;}

void AlgorithmPreorder::stop(Visitor* visitor){
  stoppeds.insert(visitor);}

void AlgorithmPreorder::clearStoppedVisitors(){
  if(stoppeds.empty()){
    return;
  }

  std::set<Visitor*>::iterator iter = stoppeds.begin();
  std::set<Visitor*>::iterator iter_end = stoppeds.end();

  for(; iter != iter_end; ++iter){
    visitorList.remove(*iter);
  }

  stoppeds.clear();
  needPreorderStop = visitorList.empty();
}
}}}
