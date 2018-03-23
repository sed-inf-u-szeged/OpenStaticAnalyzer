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

#include "csharp/inc/csharp.h"
#include "common/inc/WriteMessage.h"
#include "csharp/inc/messages.h"
#include <string.h>

#ifdef DEBUG_PREORDER
#include <iostream>
#endif


namespace columbus { namespace csharp { namespace asg {
AlgorithmPreorder::AlgorithmPreorder()
  : Algorithm(),
  safeMode(false),
  visitedNodes(),
  unvisitedNodes(),
  visitCrossEdgeTree(false),
  needPreorderStop(false),
  visitFilteredEdge(false),
  originalFilterState(false),
  apRoot(NULL),
  visitorList(false),
  fact(NULL),
  traversaldCrossEdges()
{
  memset(traversaldCrossEdges,false,sizeof(bool)*250);
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

    if (!needPreorderStop && (visitCrossEdgeTree)) {
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

void AlgorithmPreorder::visitAllEdges(const base::Positioned& node, bool callFirst /*= true*/){
  visitAllEdges(dynamic_cast<const base::Base&>(node),false);
}

void AlgorithmPreorder::visitAllEdges(const expression::AliasQualifiedNameSyntax& node, bool callFirst /*= true*/){
  visitAllEdges(dynamic_cast<const expression::NameSyntax&>(node),false);

  std::list<Visitor*>::iterator itVisitors;

  const base::Base* genNodePtr;
  // edge: Alias
  genNodePtr = node.getAlias() ;
  if (genNodePtr) {
    const expression::IdentifierNameSyntax& endNodeRef = dynamic_cast<const expression::IdentifierNameSyntax&>(*genNodePtr);
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitAliasQualifiedNameSyntax_Alias(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;

    if ((!fact->getIsFilterTurnedOn() && !visitFilteredEdge) || (fact->getFilterState(endNodeRef.getId()) == Filter::NotFiltered) || (!originalFilterState && visitFilteredEdge)) {
      endNodeRef.accept(*this);
    }
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitEndAliasQualifiedNameSyntax_Alias(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;
  }

  // edge: Name
  genNodePtr = node.getName() ;
  if (genNodePtr) {
    const expression::SimpleNameSyntax& endNodeRef = dynamic_cast<const expression::SimpleNameSyntax&>(*genNodePtr);
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitAliasQualifiedNameSyntax_Name(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;

    if ((!fact->getIsFilterTurnedOn() && !visitFilteredEdge) || (fact->getFilterState(endNodeRef.getId()) == Filter::NotFiltered) || (!originalFilterState && visitFilteredEdge)) {
      endNodeRef.accept(*this);
    }
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitEndAliasQualifiedNameSyntax_Name(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;
  }
}

void AlgorithmPreorder::visit(const expression::AliasQualifiedNameSyntax& node, bool callFirst /*= true*/){
#ifdef DEBUG_PREORDER
  std::cout << "Rec. run: " << (unsigned int)&node << " " << node.getId() << " " << Common::toString(node.getNodeKind()) << std::endl;
#endif
  if (safeMode || visitCrossEdgeTree) {
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

void AlgorithmPreorder::visitAllEdges(const expression::AnonymousFunctionExpressionSyntax& node, bool callFirst /*= true*/){
  visitAllEdges(dynamic_cast<const expression::ExpressionSyntax&>(node),false);

  std::list<Visitor*>::iterator itVisitors;

  const base::Base* genNodePtr;
  // edge: Body
  genNodePtr = node.getBody() ;
  if (genNodePtr) {
    const base::Positioned& endNodeRef = dynamic_cast<const base::Positioned&>(*genNodePtr);
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitAnonymousFunctionExpressionSyntax_Body(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;

    if ((!fact->getIsFilterTurnedOn() && !visitFilteredEdge) || (fact->getFilterState(endNodeRef.getId()) == Filter::NotFiltered) || (!originalFilterState && visitFilteredEdge)) {
      endNodeRef.accept(*this);
    }
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitEndAnonymousFunctionExpressionSyntax_Body(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;
  }
}

void AlgorithmPreorder::visitAllEdges(const expression::AnonymousMethodExpressionSyntax& node, bool callFirst /*= true*/){
  visitAllEdges(dynamic_cast<const expression::AnonymousFunctionExpressionSyntax&>(node),false);

  std::list<Visitor*>::iterator itVisitors;

  const base::Base* genNodePtr;
  // edge: ParameterList
  genNodePtr = node.getParameterList() ;
  if (genNodePtr) {
    const structure::ParameterListSyntax& endNodeRef = dynamic_cast<const structure::ParameterListSyntax&>(*genNodePtr);
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitAnonymousMethodExpressionSyntax_ParameterList(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;

    if ((!fact->getIsFilterTurnedOn() && !visitFilteredEdge) || (fact->getFilterState(endNodeRef.getId()) == Filter::NotFiltered) || (!originalFilterState && visitFilteredEdge)) {
      endNodeRef.accept(*this);
    }
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitEndAnonymousMethodExpressionSyntax_ParameterList(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;
  }
}

void AlgorithmPreorder::visit(const expression::AnonymousMethodExpressionSyntax& node, bool callFirst /*= true*/){
#ifdef DEBUG_PREORDER
  std::cout << "Rec. run: " << (unsigned int)&node << " " << node.getId() << " " << Common::toString(node.getNodeKind()) << std::endl;
#endif
  if (safeMode || visitCrossEdgeTree) {
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

void AlgorithmPreorder::visitAllEdges(const expression::AnonymousObjectCreationExpressionSyntax& node, bool callFirst /*= true*/){
  visitAllEdges(dynamic_cast<const expression::ExpressionSyntax&>(node),false);

  std::list<Visitor*>::iterator itVisitors;

  // edge: Initializers
  for (ListIterator<structure::AnonymousObjectMemberDeclaratorSyntax> it = node.getInitializersListIteratorBegin(); it != node.getInitializersListIteratorEnd(); ++it) {
    const structure::AnonymousObjectMemberDeclaratorSyntax& endNodeRef = *it;
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitAnonymousObjectCreationExpressionSyntax_Initializers(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;

    if ((!fact->getIsFilterTurnedOn() && !visitFilteredEdge) || (fact->getFilterState(endNodeRef.getId()) == Filter::NotFiltered) || (!originalFilterState && visitFilteredEdge)) {
      endNodeRef.accept(*this);
    }
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitEndAnonymousObjectCreationExpressionSyntax_Initializers(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;
  }
}

void AlgorithmPreorder::visit(const expression::AnonymousObjectCreationExpressionSyntax& node, bool callFirst /*= true*/){
#ifdef DEBUG_PREORDER
  std::cout << "Rec. run: " << (unsigned int)&node << " " << node.getId() << " " << Common::toString(node.getNodeKind()) << std::endl;
#endif
  if (safeMode || visitCrossEdgeTree) {
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

void AlgorithmPreorder::visitAllEdges(const expression::ArrayCreationExpressionSyntax& node, bool callFirst /*= true*/){
  visitAllEdges(dynamic_cast<const expression::ExpressionSyntax&>(node),false);

  std::list<Visitor*>::iterator itVisitors;

  const base::Base* genNodePtr;
  // edge: Initializer
  genNodePtr = node.getInitializer() ;
  if (genNodePtr) {
    const expression::InitializerExpressionSyntax& endNodeRef = dynamic_cast<const expression::InitializerExpressionSyntax&>(*genNodePtr);
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitArrayCreationExpressionSyntax_Initializer(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;

    if ((!fact->getIsFilterTurnedOn() && !visitFilteredEdge) || (fact->getFilterState(endNodeRef.getId()) == Filter::NotFiltered) || (!originalFilterState && visitFilteredEdge)) {
      endNodeRef.accept(*this);
    }
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitEndArrayCreationExpressionSyntax_Initializer(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;
  }

  // edge: Type
  genNodePtr = node.getType() ;
  if (genNodePtr) {
    const expression::ArrayTypeSyntax& endNodeRef = dynamic_cast<const expression::ArrayTypeSyntax&>(*genNodePtr);
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitArrayCreationExpressionSyntax_Type(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;

    if ((!fact->getIsFilterTurnedOn() && !visitFilteredEdge) || (fact->getFilterState(endNodeRef.getId()) == Filter::NotFiltered) || (!originalFilterState && visitFilteredEdge)) {
      endNodeRef.accept(*this);
    }
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitEndArrayCreationExpressionSyntax_Type(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;
  }
}

void AlgorithmPreorder::visit(const expression::ArrayCreationExpressionSyntax& node, bool callFirst /*= true*/){
#ifdef DEBUG_PREORDER
  std::cout << "Rec. run: " << (unsigned int)&node << " " << node.getId() << " " << Common::toString(node.getNodeKind()) << std::endl;
#endif
  if (safeMode || visitCrossEdgeTree) {
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

void AlgorithmPreorder::visitAllEdges(const expression::ArrayTypeSyntax& node, bool callFirst /*= true*/){
  visitAllEdges(dynamic_cast<const expression::TypeSyntax&>(node),false);

  std::list<Visitor*>::iterator itVisitors;

  const base::Base* genNodePtr;
  // edge: ElementType
  genNodePtr = node.getElementType() ;
  if (genNodePtr) {
    const expression::TypeSyntax& endNodeRef = dynamic_cast<const expression::TypeSyntax&>(*genNodePtr);
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitArrayTypeSyntax_ElementType(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;

    if ((!fact->getIsFilterTurnedOn() && !visitFilteredEdge) || (fact->getFilterState(endNodeRef.getId()) == Filter::NotFiltered) || (!originalFilterState && visitFilteredEdge)) {
      endNodeRef.accept(*this);
    }
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitEndArrayTypeSyntax_ElementType(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;
  }

  // edge: RankSpecifiers
  for (ListIterator<structure::ArrayRankSpecifierSyntax> it = node.getRankSpecifiersListIteratorBegin(); it != node.getRankSpecifiersListIteratorEnd(); ++it) {
    const structure::ArrayRankSpecifierSyntax& endNodeRef = *it;
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitArrayTypeSyntax_RankSpecifiers(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;

    if ((!fact->getIsFilterTurnedOn() && !visitFilteredEdge) || (fact->getFilterState(endNodeRef.getId()) == Filter::NotFiltered) || (!originalFilterState && visitFilteredEdge)) {
      endNodeRef.accept(*this);
    }
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitEndArrayTypeSyntax_RankSpecifiers(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;
  }
}

void AlgorithmPreorder::visit(const expression::ArrayTypeSyntax& node, bool callFirst /*= true*/){
#ifdef DEBUG_PREORDER
  std::cout << "Rec. run: " << (unsigned int)&node << " " << node.getId() << " " << Common::toString(node.getNodeKind()) << std::endl;
#endif
  if (safeMode || visitCrossEdgeTree) {
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

void AlgorithmPreorder::visitAllEdges(const expression::AssignmentExpressionSyntax& node, bool callFirst /*= true*/){
  visitAllEdges(dynamic_cast<const expression::ExpressionSyntax&>(node),false);

  std::list<Visitor*>::iterator itVisitors;

  const base::Base* genNodePtr;
  // edge: EventAccessorCall
  genNodePtr = node.getEventAccessorCall() ;
  if (genNodePtr) {
    const structure::AccessorDeclarationSyntax& endNodeRef = dynamic_cast<const structure::AccessorDeclarationSyntax&>(*genNodePtr);
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitAssignmentExpressionSyntax_EventAccessorCall(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;

    if ((!fact->getIsFilterTurnedOn() && !visitFilteredEdge) || (fact->getFilterState(endNodeRef.getId()) == Filter::NotFiltered) || (!originalFilterState && visitFilteredEdge)) {
      if (apRoot) {
        if (visitCrossEdgeTree) {
          unvisitedNodes[endNodeRef.getId()] = true;
        }
      }
      if (traversaldCrossEdges[edkAssignmentExpressionSyntax_EventAccessorCall]) {
        endNodeRef.accept(*this);
      }
    }
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitEndAssignmentExpressionSyntax_EventAccessorCall(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;
  }

  // edge: Left
  genNodePtr = node.getLeft() ;
  if (genNodePtr) {
    const expression::ExpressionSyntax& endNodeRef = dynamic_cast<const expression::ExpressionSyntax&>(*genNodePtr);
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitAssignmentExpressionSyntax_Left(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;

    if ((!fact->getIsFilterTurnedOn() && !visitFilteredEdge) || (fact->getFilterState(endNodeRef.getId()) == Filter::NotFiltered) || (!originalFilterState && visitFilteredEdge)) {
      endNodeRef.accept(*this);
    }
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitEndAssignmentExpressionSyntax_Left(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;
  }

  // edge: OverloadedOperatorCall
  genNodePtr = node.getOverloadedOperatorCall() ;
  if (genNodePtr) {
    const structure::OperatorDeclarationSyntax& endNodeRef = dynamic_cast<const structure::OperatorDeclarationSyntax&>(*genNodePtr);
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitAssignmentExpressionSyntax_OverloadedOperatorCall(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;

    if ((!fact->getIsFilterTurnedOn() && !visitFilteredEdge) || (fact->getFilterState(endNodeRef.getId()) == Filter::NotFiltered) || (!originalFilterState && visitFilteredEdge)) {
      if (apRoot) {
        if (visitCrossEdgeTree) {
          unvisitedNodes[endNodeRef.getId()] = true;
        }
      }
      if (traversaldCrossEdges[edkAssignmentExpressionSyntax_OverloadedOperatorCall]) {
        endNodeRef.accept(*this);
      }
    }
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitEndAssignmentExpressionSyntax_OverloadedOperatorCall(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;
  }

  // edge: Right
  genNodePtr = node.getRight() ;
  if (genNodePtr) {
    const expression::ExpressionSyntax& endNodeRef = dynamic_cast<const expression::ExpressionSyntax&>(*genNodePtr);
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitAssignmentExpressionSyntax_Right(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;

    if ((!fact->getIsFilterTurnedOn() && !visitFilteredEdge) || (fact->getFilterState(endNodeRef.getId()) == Filter::NotFiltered) || (!originalFilterState && visitFilteredEdge)) {
      endNodeRef.accept(*this);
    }
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitEndAssignmentExpressionSyntax_Right(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;
  }
}

void AlgorithmPreorder::visit(const expression::AssignmentExpressionSyntax& node, bool callFirst /*= true*/){
#ifdef DEBUG_PREORDER
  std::cout << "Rec. run: " << (unsigned int)&node << " " << node.getId() << " " << Common::toString(node.getNodeKind()) << std::endl;
#endif
  if (safeMode || visitCrossEdgeTree) {
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

void AlgorithmPreorder::visitAllEdges(const expression::AwaitExpressionSyntax& node, bool callFirst /*= true*/){
  visitAllEdges(dynamic_cast<const expression::ExpressionSyntax&>(node),false);

  std::list<Visitor*>::iterator itVisitors;

  const base::Base* genNodePtr;
  // edge: Expression
  genNodePtr = node.getExpression() ;
  if (genNodePtr) {
    const expression::ExpressionSyntax& endNodeRef = dynamic_cast<const expression::ExpressionSyntax&>(*genNodePtr);
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitAwaitExpressionSyntax_Expression(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;

    if ((!fact->getIsFilterTurnedOn() && !visitFilteredEdge) || (fact->getFilterState(endNodeRef.getId()) == Filter::NotFiltered) || (!originalFilterState && visitFilteredEdge)) {
      endNodeRef.accept(*this);
    }
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitEndAwaitExpressionSyntax_Expression(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;
  }
}

void AlgorithmPreorder::visit(const expression::AwaitExpressionSyntax& node, bool callFirst /*= true*/){
#ifdef DEBUG_PREORDER
  std::cout << "Rec. run: " << (unsigned int)&node << " " << node.getId() << " " << Common::toString(node.getNodeKind()) << std::endl;
#endif
  if (safeMode || visitCrossEdgeTree) {
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

void AlgorithmPreorder::visitAllEdges(const expression::BaseExpressionSyntax& node, bool callFirst /*= true*/){
  visitAllEdges(dynamic_cast<const expression::InstanceExpressionSyntax&>(node),false);
}

void AlgorithmPreorder::visit(const expression::BaseExpressionSyntax& node, bool callFirst /*= true*/){
#ifdef DEBUG_PREORDER
  std::cout << "Rec. run: " << (unsigned int)&node << " " << node.getId() << " " << Common::toString(node.getNodeKind()) << std::endl;
#endif
  if (safeMode || visitCrossEdgeTree) {
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

void AlgorithmPreorder::visitAllEdges(const expression::BinaryExpressionSyntax& node, bool callFirst /*= true*/){
  visitAllEdges(dynamic_cast<const expression::ExpressionSyntax&>(node),false);

  std::list<Visitor*>::iterator itVisitors;

  const base::Base* genNodePtr;
  // edge: Left
  genNodePtr = node.getLeft() ;
  if (genNodePtr) {
    const expression::ExpressionSyntax& endNodeRef = dynamic_cast<const expression::ExpressionSyntax&>(*genNodePtr);
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitBinaryExpressionSyntax_Left(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;

    if ((!fact->getIsFilterTurnedOn() && !visitFilteredEdge) || (fact->getFilterState(endNodeRef.getId()) == Filter::NotFiltered) || (!originalFilterState && visitFilteredEdge)) {
      endNodeRef.accept(*this);
    }
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitEndBinaryExpressionSyntax_Left(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;
  }

  // edge: OverloadedOperatorCall
  genNodePtr = node.getOverloadedOperatorCall() ;
  if (genNodePtr) {
    const structure::OperatorDeclarationSyntax& endNodeRef = dynamic_cast<const structure::OperatorDeclarationSyntax&>(*genNodePtr);
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitBinaryExpressionSyntax_OverloadedOperatorCall(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;

    if ((!fact->getIsFilterTurnedOn() && !visitFilteredEdge) || (fact->getFilterState(endNodeRef.getId()) == Filter::NotFiltered) || (!originalFilterState && visitFilteredEdge)) {
      if (apRoot) {
        if (visitCrossEdgeTree) {
          unvisitedNodes[endNodeRef.getId()] = true;
        }
      }
      if (traversaldCrossEdges[edkBinaryExpressionSyntax_OverloadedOperatorCall]) {
        endNodeRef.accept(*this);
      }
    }
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitEndBinaryExpressionSyntax_OverloadedOperatorCall(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;
  }

  // edge: Right
  genNodePtr = node.getRight() ;
  if (genNodePtr) {
    const expression::ExpressionSyntax& endNodeRef = dynamic_cast<const expression::ExpressionSyntax&>(*genNodePtr);
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitBinaryExpressionSyntax_Right(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;

    if ((!fact->getIsFilterTurnedOn() && !visitFilteredEdge) || (fact->getFilterState(endNodeRef.getId()) == Filter::NotFiltered) || (!originalFilterState && visitFilteredEdge)) {
      endNodeRef.accept(*this);
    }
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitEndBinaryExpressionSyntax_Right(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;
  }
}

void AlgorithmPreorder::visit(const expression::BinaryExpressionSyntax& node, bool callFirst /*= true*/){
#ifdef DEBUG_PREORDER
  std::cout << "Rec. run: " << (unsigned int)&node << " " << node.getId() << " " << Common::toString(node.getNodeKind()) << std::endl;
#endif
  if (safeMode || visitCrossEdgeTree) {
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

void AlgorithmPreorder::visitAllEdges(const expression::CastExpressionSyntax& node, bool callFirst /*= true*/){
  visitAllEdges(dynamic_cast<const expression::ExpressionSyntax&>(node),false);

  std::list<Visitor*>::iterator itVisitors;

  const base::Base* genNodePtr;
  // edge: ConversionOperatorCall
  genNodePtr = node.getConversionOperatorCall() ;
  if (genNodePtr) {
    const structure::ConversionOperatorDeclarationSyntax& endNodeRef = dynamic_cast<const structure::ConversionOperatorDeclarationSyntax&>(*genNodePtr);
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitCastExpressionSyntax_ConversionOperatorCall(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;

    if ((!fact->getIsFilterTurnedOn() && !visitFilteredEdge) || (fact->getFilterState(endNodeRef.getId()) == Filter::NotFiltered) || (!originalFilterState && visitFilteredEdge)) {
      if (apRoot) {
        if (visitCrossEdgeTree) {
          unvisitedNodes[endNodeRef.getId()] = true;
        }
      }
      if (traversaldCrossEdges[edkCastExpressionSyntax_ConversionOperatorCall]) {
        endNodeRef.accept(*this);
      }
    }
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitEndCastExpressionSyntax_ConversionOperatorCall(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;
  }

  // edge: Expression
  genNodePtr = node.getExpression() ;
  if (genNodePtr) {
    const expression::ExpressionSyntax& endNodeRef = dynamic_cast<const expression::ExpressionSyntax&>(*genNodePtr);
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitCastExpressionSyntax_Expression(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;

    if ((!fact->getIsFilterTurnedOn() && !visitFilteredEdge) || (fact->getFilterState(endNodeRef.getId()) == Filter::NotFiltered) || (!originalFilterState && visitFilteredEdge)) {
      endNodeRef.accept(*this);
    }
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitEndCastExpressionSyntax_Expression(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;
  }

  // edge: Type
  genNodePtr = node.getType() ;
  if (genNodePtr) {
    const expression::TypeSyntax& endNodeRef = dynamic_cast<const expression::TypeSyntax&>(*genNodePtr);
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitCastExpressionSyntax_Type(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;

    if ((!fact->getIsFilterTurnedOn() && !visitFilteredEdge) || (fact->getFilterState(endNodeRef.getId()) == Filter::NotFiltered) || (!originalFilterState && visitFilteredEdge)) {
      endNodeRef.accept(*this);
    }
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitEndCastExpressionSyntax_Type(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;
  }
}

void AlgorithmPreorder::visit(const expression::CastExpressionSyntax& node, bool callFirst /*= true*/){
#ifdef DEBUG_PREORDER
  std::cout << "Rec. run: " << (unsigned int)&node << " " << node.getId() << " " << Common::toString(node.getNodeKind()) << std::endl;
#endif
  if (safeMode || visitCrossEdgeTree) {
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

void AlgorithmPreorder::visitAllEdges(const expression::CheckedExpressionSyntax& node, bool callFirst /*= true*/){
  visitAllEdges(dynamic_cast<const expression::ExpressionSyntax&>(node),false);

  std::list<Visitor*>::iterator itVisitors;

  const base::Base* genNodePtr;
  // edge: Expression
  genNodePtr = node.getExpression() ;
  if (genNodePtr) {
    const expression::ExpressionSyntax& endNodeRef = dynamic_cast<const expression::ExpressionSyntax&>(*genNodePtr);
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitCheckedExpressionSyntax_Expression(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;

    if ((!fact->getIsFilterTurnedOn() && !visitFilteredEdge) || (fact->getFilterState(endNodeRef.getId()) == Filter::NotFiltered) || (!originalFilterState && visitFilteredEdge)) {
      endNodeRef.accept(*this);
    }
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitEndCheckedExpressionSyntax_Expression(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;
  }
}

void AlgorithmPreorder::visit(const expression::CheckedExpressionSyntax& node, bool callFirst /*= true*/){
#ifdef DEBUG_PREORDER
  std::cout << "Rec. run: " << (unsigned int)&node << " " << node.getId() << " " << Common::toString(node.getNodeKind()) << std::endl;
#endif
  if (safeMode || visitCrossEdgeTree) {
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

void AlgorithmPreorder::visitAllEdges(const expression::ConditionalAccessExpressionSyntax& node, bool callFirst /*= true*/){
  visitAllEdges(dynamic_cast<const expression::ExpressionSyntax&>(node),false);

  std::list<Visitor*>::iterator itVisitors;

  const base::Base* genNodePtr;
  // edge: Expression
  genNodePtr = node.getExpression() ;
  if (genNodePtr) {
    const expression::ExpressionSyntax& endNodeRef = dynamic_cast<const expression::ExpressionSyntax&>(*genNodePtr);
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitConditionalAccessExpressionSyntax_Expression(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;

    if ((!fact->getIsFilterTurnedOn() && !visitFilteredEdge) || (fact->getFilterState(endNodeRef.getId()) == Filter::NotFiltered) || (!originalFilterState && visitFilteredEdge)) {
      endNodeRef.accept(*this);
    }
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitEndConditionalAccessExpressionSyntax_Expression(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;
  }

  // edge: WhenNotNull
  genNodePtr = node.getWhenNotNull() ;
  if (genNodePtr) {
    const expression::ExpressionSyntax& endNodeRef = dynamic_cast<const expression::ExpressionSyntax&>(*genNodePtr);
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitConditionalAccessExpressionSyntax_WhenNotNull(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;

    if ((!fact->getIsFilterTurnedOn() && !visitFilteredEdge) || (fact->getFilterState(endNodeRef.getId()) == Filter::NotFiltered) || (!originalFilterState && visitFilteredEdge)) {
      endNodeRef.accept(*this);
    }
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitEndConditionalAccessExpressionSyntax_WhenNotNull(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;
  }
}

void AlgorithmPreorder::visit(const expression::ConditionalAccessExpressionSyntax& node, bool callFirst /*= true*/){
#ifdef DEBUG_PREORDER
  std::cout << "Rec. run: " << (unsigned int)&node << " " << node.getId() << " " << Common::toString(node.getNodeKind()) << std::endl;
#endif
  if (safeMode || visitCrossEdgeTree) {
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

void AlgorithmPreorder::visitAllEdges(const expression::ConditionalExpressionSyntax& node, bool callFirst /*= true*/){
  visitAllEdges(dynamic_cast<const expression::ExpressionSyntax&>(node),false);

  std::list<Visitor*>::iterator itVisitors;

  const base::Base* genNodePtr;
  // edge: Condition
  genNodePtr = node.getCondition() ;
  if (genNodePtr) {
    const expression::ExpressionSyntax& endNodeRef = dynamic_cast<const expression::ExpressionSyntax&>(*genNodePtr);
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitConditionalExpressionSyntax_Condition(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;

    if ((!fact->getIsFilterTurnedOn() && !visitFilteredEdge) || (fact->getFilterState(endNodeRef.getId()) == Filter::NotFiltered) || (!originalFilterState && visitFilteredEdge)) {
      endNodeRef.accept(*this);
    }
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitEndConditionalExpressionSyntax_Condition(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;
  }

  // edge: WhenFalse
  genNodePtr = node.getWhenFalse() ;
  if (genNodePtr) {
    const expression::ExpressionSyntax& endNodeRef = dynamic_cast<const expression::ExpressionSyntax&>(*genNodePtr);
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitConditionalExpressionSyntax_WhenFalse(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;

    if ((!fact->getIsFilterTurnedOn() && !visitFilteredEdge) || (fact->getFilterState(endNodeRef.getId()) == Filter::NotFiltered) || (!originalFilterState && visitFilteredEdge)) {
      endNodeRef.accept(*this);
    }
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitEndConditionalExpressionSyntax_WhenFalse(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;
  }

  // edge: WhenTrue
  genNodePtr = node.getWhenTrue() ;
  if (genNodePtr) {
    const expression::ExpressionSyntax& endNodeRef = dynamic_cast<const expression::ExpressionSyntax&>(*genNodePtr);
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitConditionalExpressionSyntax_WhenTrue(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;

    if ((!fact->getIsFilterTurnedOn() && !visitFilteredEdge) || (fact->getFilterState(endNodeRef.getId()) == Filter::NotFiltered) || (!originalFilterState && visitFilteredEdge)) {
      endNodeRef.accept(*this);
    }
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitEndConditionalExpressionSyntax_WhenTrue(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;
  }
}

void AlgorithmPreorder::visit(const expression::ConditionalExpressionSyntax& node, bool callFirst /*= true*/){
#ifdef DEBUG_PREORDER
  std::cout << "Rec. run: " << (unsigned int)&node << " " << node.getId() << " " << Common::toString(node.getNodeKind()) << std::endl;
#endif
  if (safeMode || visitCrossEdgeTree) {
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

void AlgorithmPreorder::visitAllEdges(const expression::DefaultExpressionSyntax& node, bool callFirst /*= true*/){
  visitAllEdges(dynamic_cast<const expression::ExpressionSyntax&>(node),false);

  std::list<Visitor*>::iterator itVisitors;

  const base::Base* genNodePtr;
  // edge: Type
  genNodePtr = node.getType() ;
  if (genNodePtr) {
    const expression::TypeSyntax& endNodeRef = dynamic_cast<const expression::TypeSyntax&>(*genNodePtr);
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitDefaultExpressionSyntax_Type(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;

    if ((!fact->getIsFilterTurnedOn() && !visitFilteredEdge) || (fact->getFilterState(endNodeRef.getId()) == Filter::NotFiltered) || (!originalFilterState && visitFilteredEdge)) {
      endNodeRef.accept(*this);
    }
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitEndDefaultExpressionSyntax_Type(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;
  }
}

void AlgorithmPreorder::visit(const expression::DefaultExpressionSyntax& node, bool callFirst /*= true*/){
#ifdef DEBUG_PREORDER
  std::cout << "Rec. run: " << (unsigned int)&node << " " << node.getId() << " " << Common::toString(node.getNodeKind()) << std::endl;
#endif
  if (safeMode || visitCrossEdgeTree) {
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

void AlgorithmPreorder::visitAllEdges(const expression::ElementAccessExpressionSyntax& node, bool callFirst /*= true*/){
  visitAllEdges(dynamic_cast<const expression::ExpressionSyntax&>(node),false);

  std::list<Visitor*>::iterator itVisitors;

  // edge: AccessorCall
  for (ListIterator<structure::AccessorDeclarationSyntax> it = node.getAccessorCallListIteratorBegin(); it != node.getAccessorCallListIteratorEnd(); ++it) {
    const structure::AccessorDeclarationSyntax& endNodeRef = *it;
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitElementAccessExpressionSyntax_AccessorCall(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;

    if ((!fact->getIsFilterTurnedOn() && !visitFilteredEdge) || (fact->getFilterState(endNodeRef.getId()) == Filter::NotFiltered) || (!originalFilterState && visitFilteredEdge)) {
      if (apRoot) {
        if (visitCrossEdgeTree) {
          unvisitedNodes[endNodeRef.getId()] = true;
        }
      }
      if (traversaldCrossEdges[edkElementAccessExpressionSyntax_AccessorCall]) {
        endNodeRef.accept(*this);
      }
    }
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitEndElementAccessExpressionSyntax_AccessorCall(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;
  }

  const base::Base* genNodePtr;
  // edge: ArgumentList
  genNodePtr = node.getArgumentList() ;
  if (genNodePtr) {
    const structure::BracketedArgumentListSyntax& endNodeRef = dynamic_cast<const structure::BracketedArgumentListSyntax&>(*genNodePtr);
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitElementAccessExpressionSyntax_ArgumentList(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;

    if ((!fact->getIsFilterTurnedOn() && !visitFilteredEdge) || (fact->getFilterState(endNodeRef.getId()) == Filter::NotFiltered) || (!originalFilterState && visitFilteredEdge)) {
      endNodeRef.accept(*this);
    }
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitEndElementAccessExpressionSyntax_ArgumentList(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;
  }

  // edge: Expression
  genNodePtr = node.getExpression() ;
  if (genNodePtr) {
    const expression::ExpressionSyntax& endNodeRef = dynamic_cast<const expression::ExpressionSyntax&>(*genNodePtr);
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitElementAccessExpressionSyntax_Expression(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;

    if ((!fact->getIsFilterTurnedOn() && !visitFilteredEdge) || (fact->getFilterState(endNodeRef.getId()) == Filter::NotFiltered) || (!originalFilterState && visitFilteredEdge)) {
      endNodeRef.accept(*this);
    }
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitEndElementAccessExpressionSyntax_Expression(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;
  }
}

void AlgorithmPreorder::visit(const expression::ElementAccessExpressionSyntax& node, bool callFirst /*= true*/){
#ifdef DEBUG_PREORDER
  std::cout << "Rec. run: " << (unsigned int)&node << " " << node.getId() << " " << Common::toString(node.getNodeKind()) << std::endl;
#endif
  if (safeMode || visitCrossEdgeTree) {
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

void AlgorithmPreorder::visitAllEdges(const expression::ElementBindingExpressionSyntax& node, bool callFirst /*= true*/){
  visitAllEdges(dynamic_cast<const expression::ExpressionSyntax&>(node),false);

  std::list<Visitor*>::iterator itVisitors;

  const base::Base* genNodePtr;
  // edge: ArgumentList
  genNodePtr = node.getArgumentList() ;
  if (genNodePtr) {
    const structure::BracketedArgumentListSyntax& endNodeRef = dynamic_cast<const structure::BracketedArgumentListSyntax&>(*genNodePtr);
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitElementBindingExpressionSyntax_ArgumentList(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;

    if ((!fact->getIsFilterTurnedOn() && !visitFilteredEdge) || (fact->getFilterState(endNodeRef.getId()) == Filter::NotFiltered) || (!originalFilterState && visitFilteredEdge)) {
      endNodeRef.accept(*this);
    }
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitEndElementBindingExpressionSyntax_ArgumentList(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;
  }
}

void AlgorithmPreorder::visit(const expression::ElementBindingExpressionSyntax& node, bool callFirst /*= true*/){
#ifdef DEBUG_PREORDER
  std::cout << "Rec. run: " << (unsigned int)&node << " " << node.getId() << " " << Common::toString(node.getNodeKind()) << std::endl;
#endif
  if (safeMode || visitCrossEdgeTree) {
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

void AlgorithmPreorder::visitAllEdges(const expression::ExpressionSyntax& node, bool callFirst /*= true*/){
  visitAllEdges(dynamic_cast<const base::Positioned&>(node),false);
}

void AlgorithmPreorder::visitAllEdges(const expression::GenericNameSyntax& node, bool callFirst /*= true*/){
  visitAllEdges(dynamic_cast<const expression::SimpleNameSyntax&>(node),false);

  std::list<Visitor*>::iterator itVisitors;

  const base::Base* genNodePtr;
  // edge: TypeArgumentList
  genNodePtr = node.getTypeArgumentList() ;
  if (genNodePtr) {
    const structure::TypeArgumentListSyntax& endNodeRef = dynamic_cast<const structure::TypeArgumentListSyntax&>(*genNodePtr);
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitGenericNameSyntax_TypeArgumentList(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;

    if ((!fact->getIsFilterTurnedOn() && !visitFilteredEdge) || (fact->getFilterState(endNodeRef.getId()) == Filter::NotFiltered) || (!originalFilterState && visitFilteredEdge)) {
      endNodeRef.accept(*this);
    }
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitEndGenericNameSyntax_TypeArgumentList(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;
  }
}

void AlgorithmPreorder::visit(const expression::GenericNameSyntax& node, bool callFirst /*= true*/){
#ifdef DEBUG_PREORDER
  std::cout << "Rec. run: " << (unsigned int)&node << " " << node.getId() << " " << Common::toString(node.getNodeKind()) << std::endl;
#endif
  if (safeMode || visitCrossEdgeTree) {
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

void AlgorithmPreorder::visitAllEdges(const expression::IdentifierNameSyntax& node, bool callFirst /*= true*/){
  visitAllEdges(dynamic_cast<const expression::SimpleNameSyntax&>(node),false);

  std::list<Visitor*>::iterator itVisitors;

  // edge: AccessorCall
  for (ListIterator<structure::AccessorDeclarationSyntax> it = node.getAccessorCallListIteratorBegin(); it != node.getAccessorCallListIteratorEnd(); ++it) {
    const structure::AccessorDeclarationSyntax& endNodeRef = *it;
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitIdentifierNameSyntax_AccessorCall(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;

    if ((!fact->getIsFilterTurnedOn() && !visitFilteredEdge) || (fact->getFilterState(endNodeRef.getId()) == Filter::NotFiltered) || (!originalFilterState && visitFilteredEdge)) {
      if (apRoot) {
        if (visitCrossEdgeTree) {
          unvisitedNodes[endNodeRef.getId()] = true;
        }
      }
      if (traversaldCrossEdges[edkIdentifierNameSyntax_AccessorCall]) {
        endNodeRef.accept(*this);
      }
    }
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitEndIdentifierNameSyntax_AccessorCall(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;
  }

  const base::Base* genNodePtr;
  // edge: Declaration
  genNodePtr = node.getDeclaration() ;
  if (genNodePtr) {
    const base::Positioned& endNodeRef = dynamic_cast<const base::Positioned&>(*genNodePtr);
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitIdentifierNameSyntax_Declaration(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;

    if ((!fact->getIsFilterTurnedOn() && !visitFilteredEdge) || (fact->getFilterState(endNodeRef.getId()) == Filter::NotFiltered) || (!originalFilterState && visitFilteredEdge)) {
      if (apRoot) {
        if (visitCrossEdgeTree) {
          unvisitedNodes[endNodeRef.getId()] = true;
        }
      }
      if (traversaldCrossEdges[edkIdentifierNameSyntax_Declaration]) {
        endNodeRef.accept(*this);
      }
    }
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitEndIdentifierNameSyntax_Declaration(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;
  }
}

void AlgorithmPreorder::visit(const expression::IdentifierNameSyntax& node, bool callFirst /*= true*/){
#ifdef DEBUG_PREORDER
  std::cout << "Rec. run: " << (unsigned int)&node << " " << node.getId() << " " << Common::toString(node.getNodeKind()) << std::endl;
#endif
  if (safeMode || visitCrossEdgeTree) {
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

void AlgorithmPreorder::visitAllEdges(const expression::ImplicitArrayCreationExpressionSyntax& node, bool callFirst /*= true*/){
  visitAllEdges(dynamic_cast<const expression::ExpressionSyntax&>(node),false);

  std::list<Visitor*>::iterator itVisitors;

  const base::Base* genNodePtr;
  // edge: Initializer
  genNodePtr = node.getInitializer() ;
  if (genNodePtr) {
    const expression::InitializerExpressionSyntax& endNodeRef = dynamic_cast<const expression::InitializerExpressionSyntax&>(*genNodePtr);
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitImplicitArrayCreationExpressionSyntax_Initializer(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;

    if ((!fact->getIsFilterTurnedOn() && !visitFilteredEdge) || (fact->getFilterState(endNodeRef.getId()) == Filter::NotFiltered) || (!originalFilterState && visitFilteredEdge)) {
      endNodeRef.accept(*this);
    }
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitEndImplicitArrayCreationExpressionSyntax_Initializer(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;
  }
}

void AlgorithmPreorder::visit(const expression::ImplicitArrayCreationExpressionSyntax& node, bool callFirst /*= true*/){
#ifdef DEBUG_PREORDER
  std::cout << "Rec. run: " << (unsigned int)&node << " " << node.getId() << " " << Common::toString(node.getNodeKind()) << std::endl;
#endif
  if (safeMode || visitCrossEdgeTree) {
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

void AlgorithmPreorder::visitAllEdges(const expression::ImplicitElementAccessSyntax& node, bool callFirst /*= true*/){
  visitAllEdges(dynamic_cast<const expression::ExpressionSyntax&>(node),false);

  std::list<Visitor*>::iterator itVisitors;

  const base::Base* genNodePtr;
  // edge: ArgumentList
  genNodePtr = node.getArgumentList() ;
  if (genNodePtr) {
    const structure::BracketedArgumentListSyntax& endNodeRef = dynamic_cast<const structure::BracketedArgumentListSyntax&>(*genNodePtr);
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitImplicitElementAccessSyntax_ArgumentList(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;

    if ((!fact->getIsFilterTurnedOn() && !visitFilteredEdge) || (fact->getFilterState(endNodeRef.getId()) == Filter::NotFiltered) || (!originalFilterState && visitFilteredEdge)) {
      endNodeRef.accept(*this);
    }
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitEndImplicitElementAccessSyntax_ArgumentList(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;
  }
}

void AlgorithmPreorder::visit(const expression::ImplicitElementAccessSyntax& node, bool callFirst /*= true*/){
#ifdef DEBUG_PREORDER
  std::cout << "Rec. run: " << (unsigned int)&node << " " << node.getId() << " " << Common::toString(node.getNodeKind()) << std::endl;
#endif
  if (safeMode || visitCrossEdgeTree) {
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

void AlgorithmPreorder::visitAllEdges(const expression::InitializerExpressionSyntax& node, bool callFirst /*= true*/){
  visitAllEdges(dynamic_cast<const expression::ExpressionSyntax&>(node),false);

  std::list<Visitor*>::iterator itVisitors;

  // edge: Expressions
  for (ListIterator<expression::ExpressionSyntax> it = node.getExpressionsListIteratorBegin(); it != node.getExpressionsListIteratorEnd(); ++it) {
    const expression::ExpressionSyntax& endNodeRef = *it;
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitInitializerExpressionSyntax_Expressions(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;

    if ((!fact->getIsFilterTurnedOn() && !visitFilteredEdge) || (fact->getFilterState(endNodeRef.getId()) == Filter::NotFiltered) || (!originalFilterState && visitFilteredEdge)) {
      endNodeRef.accept(*this);
    }
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitEndInitializerExpressionSyntax_Expressions(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;
  }
}

void AlgorithmPreorder::visit(const expression::InitializerExpressionSyntax& node, bool callFirst /*= true*/){
#ifdef DEBUG_PREORDER
  std::cout << "Rec. run: " << (unsigned int)&node << " " << node.getId() << " " << Common::toString(node.getNodeKind()) << std::endl;
#endif
  if (safeMode || visitCrossEdgeTree) {
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

void AlgorithmPreorder::visitAllEdges(const expression::InstanceExpressionSyntax& node, bool callFirst /*= true*/){
  visitAllEdges(dynamic_cast<const expression::ExpressionSyntax&>(node),false);
}

void AlgorithmPreorder::visitAllEdges(const expression::InterpolatedStringExpressionSyntax& node, bool callFirst /*= true*/){
  visitAllEdges(dynamic_cast<const expression::ExpressionSyntax&>(node),false);

  std::list<Visitor*>::iterator itVisitors;

  // edge: Contents
  for (ListIterator<structure::InterpolatedStringContentSyntax> it = node.getContentsListIteratorBegin(); it != node.getContentsListIteratorEnd(); ++it) {
    const structure::InterpolatedStringContentSyntax& endNodeRef = *it;
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitInterpolatedStringExpressionSyntax_Contents(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;

    if ((!fact->getIsFilterTurnedOn() && !visitFilteredEdge) || (fact->getFilterState(endNodeRef.getId()) == Filter::NotFiltered) || (!originalFilterState && visitFilteredEdge)) {
      endNodeRef.accept(*this);
    }
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitEndInterpolatedStringExpressionSyntax_Contents(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;
  }
}

void AlgorithmPreorder::visit(const expression::InterpolatedStringExpressionSyntax& node, bool callFirst /*= true*/){
#ifdef DEBUG_PREORDER
  std::cout << "Rec. run: " << (unsigned int)&node << " " << node.getId() << " " << Common::toString(node.getNodeKind()) << std::endl;
#endif
  if (safeMode || visitCrossEdgeTree) {
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

void AlgorithmPreorder::visitAllEdges(const expression::InvocationExpressionSyntax& node, bool callFirst /*= true*/){
  visitAllEdges(dynamic_cast<const expression::ExpressionSyntax&>(node),false);

  std::list<Visitor*>::iterator itVisitors;

  const base::Base* genNodePtr;
  // edge: ArgumentList
  genNodePtr = node.getArgumentList() ;
  if (genNodePtr) {
    const structure::ArgumentListSyntax& endNodeRef = dynamic_cast<const structure::ArgumentListSyntax&>(*genNodePtr);
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitInvocationExpressionSyntax_ArgumentList(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;

    if ((!fact->getIsFilterTurnedOn() && !visitFilteredEdge) || (fact->getFilterState(endNodeRef.getId()) == Filter::NotFiltered) || (!originalFilterState && visitFilteredEdge)) {
      endNodeRef.accept(*this);
    }
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitEndInvocationExpressionSyntax_ArgumentList(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;
  }

  // edge: Expression
  genNodePtr = node.getExpression() ;
  if (genNodePtr) {
    const expression::ExpressionSyntax& endNodeRef = dynamic_cast<const expression::ExpressionSyntax&>(*genNodePtr);
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitInvocationExpressionSyntax_Expression(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;

    if ((!fact->getIsFilterTurnedOn() && !visitFilteredEdge) || (fact->getFilterState(endNodeRef.getId()) == Filter::NotFiltered) || (!originalFilterState && visitFilteredEdge)) {
      endNodeRef.accept(*this);
    }
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitEndInvocationExpressionSyntax_Expression(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;
  }

  // edge: MethodCall
  genNodePtr = node.getMethodCall() ;
  if (genNodePtr) {
    const structure::MethodDeclarationSyntax& endNodeRef = dynamic_cast<const structure::MethodDeclarationSyntax&>(*genNodePtr);
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitInvocationExpressionSyntax_MethodCall(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;

    if ((!fact->getIsFilterTurnedOn() && !visitFilteredEdge) || (fact->getFilterState(endNodeRef.getId()) == Filter::NotFiltered) || (!originalFilterState && visitFilteredEdge)) {
      if (apRoot) {
        if (visitCrossEdgeTree) {
          unvisitedNodes[endNodeRef.getId()] = true;
        }
      }
      if (traversaldCrossEdges[edkInvocationExpressionSyntax_MethodCall]) {
        endNodeRef.accept(*this);
      }
    }
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitEndInvocationExpressionSyntax_MethodCall(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;
  }
}

void AlgorithmPreorder::visit(const expression::InvocationExpressionSyntax& node, bool callFirst /*= true*/){
#ifdef DEBUG_PREORDER
  std::cout << "Rec. run: " << (unsigned int)&node << " " << node.getId() << " " << Common::toString(node.getNodeKind()) << std::endl;
#endif
  if (safeMode || visitCrossEdgeTree) {
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

void AlgorithmPreorder::visitAllEdges(const expression::LambdaExpressionSyntax& node, bool callFirst /*= true*/){
  visitAllEdges(dynamic_cast<const expression::AnonymousFunctionExpressionSyntax&>(node),false);
}

void AlgorithmPreorder::visitAllEdges(const expression::LiteralExpressionSyntax& node, bool callFirst /*= true*/){
  visitAllEdges(dynamic_cast<const expression::ExpressionSyntax&>(node),false);
}

void AlgorithmPreorder::visit(const expression::LiteralExpressionSyntax& node, bool callFirst /*= true*/){
#ifdef DEBUG_PREORDER
  std::cout << "Rec. run: " << (unsigned int)&node << " " << node.getId() << " " << Common::toString(node.getNodeKind()) << std::endl;
#endif
  if (safeMode || visitCrossEdgeTree) {
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

void AlgorithmPreorder::visitAllEdges(const expression::MakeRefExpressionSyntax& node, bool callFirst /*= true*/){
  visitAllEdges(dynamic_cast<const expression::ExpressionSyntax&>(node),false);

  std::list<Visitor*>::iterator itVisitors;

  const base::Base* genNodePtr;
  // edge: Expression
  genNodePtr = node.getExpression() ;
  if (genNodePtr) {
    const expression::ExpressionSyntax& endNodeRef = dynamic_cast<const expression::ExpressionSyntax&>(*genNodePtr);
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitMakeRefExpressionSyntax_Expression(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;

    if ((!fact->getIsFilterTurnedOn() && !visitFilteredEdge) || (fact->getFilterState(endNodeRef.getId()) == Filter::NotFiltered) || (!originalFilterState && visitFilteredEdge)) {
      endNodeRef.accept(*this);
    }
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitEndMakeRefExpressionSyntax_Expression(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;
  }
}

void AlgorithmPreorder::visit(const expression::MakeRefExpressionSyntax& node, bool callFirst /*= true*/){
#ifdef DEBUG_PREORDER
  std::cout << "Rec. run: " << (unsigned int)&node << " " << node.getId() << " " << Common::toString(node.getNodeKind()) << std::endl;
#endif
  if (safeMode || visitCrossEdgeTree) {
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

void AlgorithmPreorder::visitAllEdges(const expression::MemberAccessExpressionSyntax& node, bool callFirst /*= true*/){
  visitAllEdges(dynamic_cast<const expression::ExpressionSyntax&>(node),false);

  std::list<Visitor*>::iterator itVisitors;

  const base::Base* genNodePtr;
  // edge: Expression
  genNodePtr = node.getExpression() ;
  if (genNodePtr) {
    const expression::ExpressionSyntax& endNodeRef = dynamic_cast<const expression::ExpressionSyntax&>(*genNodePtr);
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitMemberAccessExpressionSyntax_Expression(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;

    if ((!fact->getIsFilterTurnedOn() && !visitFilteredEdge) || (fact->getFilterState(endNodeRef.getId()) == Filter::NotFiltered) || (!originalFilterState && visitFilteredEdge)) {
      endNodeRef.accept(*this);
    }
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitEndMemberAccessExpressionSyntax_Expression(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;
  }

  // edge: Name
  genNodePtr = node.getName() ;
  if (genNodePtr) {
    const expression::SimpleNameSyntax& endNodeRef = dynamic_cast<const expression::SimpleNameSyntax&>(*genNodePtr);
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitMemberAccessExpressionSyntax_Name(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;

    if ((!fact->getIsFilterTurnedOn() && !visitFilteredEdge) || (fact->getFilterState(endNodeRef.getId()) == Filter::NotFiltered) || (!originalFilterState && visitFilteredEdge)) {
      endNodeRef.accept(*this);
    }
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitEndMemberAccessExpressionSyntax_Name(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;
  }
}

void AlgorithmPreorder::visit(const expression::MemberAccessExpressionSyntax& node, bool callFirst /*= true*/){
#ifdef DEBUG_PREORDER
  std::cout << "Rec. run: " << (unsigned int)&node << " " << node.getId() << " " << Common::toString(node.getNodeKind()) << std::endl;
#endif
  if (safeMode || visitCrossEdgeTree) {
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

void AlgorithmPreorder::visitAllEdges(const expression::MemberBindingExpressionSyntax& node, bool callFirst /*= true*/){
  visitAllEdges(dynamic_cast<const expression::ExpressionSyntax&>(node),false);

  std::list<Visitor*>::iterator itVisitors;

  const base::Base* genNodePtr;
  // edge: Name
  genNodePtr = node.getName() ;
  if (genNodePtr) {
    const expression::SimpleNameSyntax& endNodeRef = dynamic_cast<const expression::SimpleNameSyntax&>(*genNodePtr);
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitMemberBindingExpressionSyntax_Name(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;

    if ((!fact->getIsFilterTurnedOn() && !visitFilteredEdge) || (fact->getFilterState(endNodeRef.getId()) == Filter::NotFiltered) || (!originalFilterState && visitFilteredEdge)) {
      endNodeRef.accept(*this);
    }
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitEndMemberBindingExpressionSyntax_Name(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;
  }
}

void AlgorithmPreorder::visit(const expression::MemberBindingExpressionSyntax& node, bool callFirst /*= true*/){
#ifdef DEBUG_PREORDER
  std::cout << "Rec. run: " << (unsigned int)&node << " " << node.getId() << " " << Common::toString(node.getNodeKind()) << std::endl;
#endif
  if (safeMode || visitCrossEdgeTree) {
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

void AlgorithmPreorder::visitAllEdges(const expression::NameSyntax& node, bool callFirst /*= true*/){
  visitAllEdges(dynamic_cast<const expression::TypeSyntax&>(node),false);
}

void AlgorithmPreorder::visitAllEdges(const expression::NullableTypeSyntax& node, bool callFirst /*= true*/){
  visitAllEdges(dynamic_cast<const expression::TypeSyntax&>(node),false);

  std::list<Visitor*>::iterator itVisitors;

  const base::Base* genNodePtr;
  // edge: ElementType
  genNodePtr = node.getElementType() ;
  if (genNodePtr) {
    const expression::TypeSyntax& endNodeRef = dynamic_cast<const expression::TypeSyntax&>(*genNodePtr);
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitNullableTypeSyntax_ElementType(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;

    if ((!fact->getIsFilterTurnedOn() && !visitFilteredEdge) || (fact->getFilterState(endNodeRef.getId()) == Filter::NotFiltered) || (!originalFilterState && visitFilteredEdge)) {
      endNodeRef.accept(*this);
    }
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitEndNullableTypeSyntax_ElementType(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;
  }
}

void AlgorithmPreorder::visit(const expression::NullableTypeSyntax& node, bool callFirst /*= true*/){
#ifdef DEBUG_PREORDER
  std::cout << "Rec. run: " << (unsigned int)&node << " " << node.getId() << " " << Common::toString(node.getNodeKind()) << std::endl;
#endif
  if (safeMode || visitCrossEdgeTree) {
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

void AlgorithmPreorder::visitAllEdges(const expression::ObjectCreationExpressionSyntax& node, bool callFirst /*= true*/){
  visitAllEdges(dynamic_cast<const expression::ExpressionSyntax&>(node),false);

  std::list<Visitor*>::iterator itVisitors;

  const base::Base* genNodePtr;
  // edge: ArgumentList
  genNodePtr = node.getArgumentList() ;
  if (genNodePtr) {
    const structure::ArgumentListSyntax& endNodeRef = dynamic_cast<const structure::ArgumentListSyntax&>(*genNodePtr);
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitObjectCreationExpressionSyntax_ArgumentList(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;

    if ((!fact->getIsFilterTurnedOn() && !visitFilteredEdge) || (fact->getFilterState(endNodeRef.getId()) == Filter::NotFiltered) || (!originalFilterState && visitFilteredEdge)) {
      endNodeRef.accept(*this);
    }
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitEndObjectCreationExpressionSyntax_ArgumentList(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;
  }

  // edge: ConstructorCall
  genNodePtr = node.getConstructorCall() ;
  if (genNodePtr) {
    const structure::ConstructorDeclarationSyntax& endNodeRef = dynamic_cast<const structure::ConstructorDeclarationSyntax&>(*genNodePtr);
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitObjectCreationExpressionSyntax_ConstructorCall(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;

    if ((!fact->getIsFilterTurnedOn() && !visitFilteredEdge) || (fact->getFilterState(endNodeRef.getId()) == Filter::NotFiltered) || (!originalFilterState && visitFilteredEdge)) {
      if (apRoot) {
        if (visitCrossEdgeTree) {
          unvisitedNodes[endNodeRef.getId()] = true;
        }
      }
      if (traversaldCrossEdges[edkObjectCreationExpressionSyntax_ConstructorCall]) {
        endNodeRef.accept(*this);
      }
    }
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitEndObjectCreationExpressionSyntax_ConstructorCall(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;
  }

  // edge: Initializer
  genNodePtr = node.getInitializer() ;
  if (genNodePtr) {
    const expression::InitializerExpressionSyntax& endNodeRef = dynamic_cast<const expression::InitializerExpressionSyntax&>(*genNodePtr);
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitObjectCreationExpressionSyntax_Initializer(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;

    if ((!fact->getIsFilterTurnedOn() && !visitFilteredEdge) || (fact->getFilterState(endNodeRef.getId()) == Filter::NotFiltered) || (!originalFilterState && visitFilteredEdge)) {
      endNodeRef.accept(*this);
    }
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitEndObjectCreationExpressionSyntax_Initializer(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;
  }

  // edge: Type
  genNodePtr = node.getType() ;
  if (genNodePtr) {
    const expression::TypeSyntax& endNodeRef = dynamic_cast<const expression::TypeSyntax&>(*genNodePtr);
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitObjectCreationExpressionSyntax_Type(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;

    if ((!fact->getIsFilterTurnedOn() && !visitFilteredEdge) || (fact->getFilterState(endNodeRef.getId()) == Filter::NotFiltered) || (!originalFilterState && visitFilteredEdge)) {
      endNodeRef.accept(*this);
    }
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitEndObjectCreationExpressionSyntax_Type(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;
  }
}

void AlgorithmPreorder::visit(const expression::ObjectCreationExpressionSyntax& node, bool callFirst /*= true*/){
#ifdef DEBUG_PREORDER
  std::cout << "Rec. run: " << (unsigned int)&node << " " << node.getId() << " " << Common::toString(node.getNodeKind()) << std::endl;
#endif
  if (safeMode || visitCrossEdgeTree) {
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

void AlgorithmPreorder::visitAllEdges(const expression::OmittedArraySizeExpressionSyntax& node, bool callFirst /*= true*/){
  visitAllEdges(dynamic_cast<const expression::ExpressionSyntax&>(node),false);
}

void AlgorithmPreorder::visit(const expression::OmittedArraySizeExpressionSyntax& node, bool callFirst /*= true*/){
#ifdef DEBUG_PREORDER
  std::cout << "Rec. run: " << (unsigned int)&node << " " << node.getId() << " " << Common::toString(node.getNodeKind()) << std::endl;
#endif
  if (safeMode || visitCrossEdgeTree) {
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

void AlgorithmPreorder::visitAllEdges(const expression::OmittedTypeArgumentSyntax& node, bool callFirst /*= true*/){
  visitAllEdges(dynamic_cast<const expression::TypeSyntax&>(node),false);
}

void AlgorithmPreorder::visit(const expression::OmittedTypeArgumentSyntax& node, bool callFirst /*= true*/){
#ifdef DEBUG_PREORDER
  std::cout << "Rec. run: " << (unsigned int)&node << " " << node.getId() << " " << Common::toString(node.getNodeKind()) << std::endl;
#endif
  if (safeMode || visitCrossEdgeTree) {
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

void AlgorithmPreorder::visitAllEdges(const expression::ParenthesizedExpressionSyntax& node, bool callFirst /*= true*/){
  visitAllEdges(dynamic_cast<const expression::ExpressionSyntax&>(node),false);

  std::list<Visitor*>::iterator itVisitors;

  const base::Base* genNodePtr;
  // edge: Expression
  genNodePtr = node.getExpression() ;
  if (genNodePtr) {
    const expression::ExpressionSyntax& endNodeRef = dynamic_cast<const expression::ExpressionSyntax&>(*genNodePtr);
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitParenthesizedExpressionSyntax_Expression(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;

    if ((!fact->getIsFilterTurnedOn() && !visitFilteredEdge) || (fact->getFilterState(endNodeRef.getId()) == Filter::NotFiltered) || (!originalFilterState && visitFilteredEdge)) {
      endNodeRef.accept(*this);
    }
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitEndParenthesizedExpressionSyntax_Expression(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;
  }
}

void AlgorithmPreorder::visit(const expression::ParenthesizedExpressionSyntax& node, bool callFirst /*= true*/){
#ifdef DEBUG_PREORDER
  std::cout << "Rec. run: " << (unsigned int)&node << " " << node.getId() << " " << Common::toString(node.getNodeKind()) << std::endl;
#endif
  if (safeMode || visitCrossEdgeTree) {
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

void AlgorithmPreorder::visitAllEdges(const expression::ParenthesizedLambdaExpressionSyntax& node, bool callFirst /*= true*/){
  visitAllEdges(dynamic_cast<const expression::LambdaExpressionSyntax&>(node),false);

  std::list<Visitor*>::iterator itVisitors;

  const base::Base* genNodePtr;
  // edge: ParameterList
  genNodePtr = node.getParameterList() ;
  if (genNodePtr) {
    const structure::ParameterListSyntax& endNodeRef = dynamic_cast<const structure::ParameterListSyntax&>(*genNodePtr);
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitParenthesizedLambdaExpressionSyntax_ParameterList(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;

    if ((!fact->getIsFilterTurnedOn() && !visitFilteredEdge) || (fact->getFilterState(endNodeRef.getId()) == Filter::NotFiltered) || (!originalFilterState && visitFilteredEdge)) {
      endNodeRef.accept(*this);
    }
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitEndParenthesizedLambdaExpressionSyntax_ParameterList(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;
  }
}

void AlgorithmPreorder::visit(const expression::ParenthesizedLambdaExpressionSyntax& node, bool callFirst /*= true*/){
#ifdef DEBUG_PREORDER
  std::cout << "Rec. run: " << (unsigned int)&node << " " << node.getId() << " " << Common::toString(node.getNodeKind()) << std::endl;
#endif
  if (safeMode || visitCrossEdgeTree) {
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

void AlgorithmPreorder::visitAllEdges(const expression::PointerTypeSyntax& node, bool callFirst /*= true*/){
  visitAllEdges(dynamic_cast<const expression::TypeSyntax&>(node),false);

  std::list<Visitor*>::iterator itVisitors;

  const base::Base* genNodePtr;
  // edge: ElementType
  genNodePtr = node.getElementType() ;
  if (genNodePtr) {
    const expression::TypeSyntax& endNodeRef = dynamic_cast<const expression::TypeSyntax&>(*genNodePtr);
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitPointerTypeSyntax_ElementType(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;

    if ((!fact->getIsFilterTurnedOn() && !visitFilteredEdge) || (fact->getFilterState(endNodeRef.getId()) == Filter::NotFiltered) || (!originalFilterState && visitFilteredEdge)) {
      endNodeRef.accept(*this);
    }
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitEndPointerTypeSyntax_ElementType(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;
  }
}

void AlgorithmPreorder::visit(const expression::PointerTypeSyntax& node, bool callFirst /*= true*/){
#ifdef DEBUG_PREORDER
  std::cout << "Rec. run: " << (unsigned int)&node << " " << node.getId() << " " << Common::toString(node.getNodeKind()) << std::endl;
#endif
  if (safeMode || visitCrossEdgeTree) {
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

void AlgorithmPreorder::visitAllEdges(const expression::PostfixUnaryExpressionSyntax& node, bool callFirst /*= true*/){
  visitAllEdges(dynamic_cast<const expression::ExpressionSyntax&>(node),false);

  std::list<Visitor*>::iterator itVisitors;

  const base::Base* genNodePtr;
  // edge: Operand
  genNodePtr = node.getOperand() ;
  if (genNodePtr) {
    const expression::ExpressionSyntax& endNodeRef = dynamic_cast<const expression::ExpressionSyntax&>(*genNodePtr);
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitPostfixUnaryExpressionSyntax_Operand(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;

    if ((!fact->getIsFilterTurnedOn() && !visitFilteredEdge) || (fact->getFilterState(endNodeRef.getId()) == Filter::NotFiltered) || (!originalFilterState && visitFilteredEdge)) {
      endNodeRef.accept(*this);
    }
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitEndPostfixUnaryExpressionSyntax_Operand(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;
  }

  // edge: OverloadedOperatorCall
  genNodePtr = node.getOverloadedOperatorCall() ;
  if (genNodePtr) {
    const structure::OperatorDeclarationSyntax& endNodeRef = dynamic_cast<const structure::OperatorDeclarationSyntax&>(*genNodePtr);
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitPostfixUnaryExpressionSyntax_OverloadedOperatorCall(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;

    if ((!fact->getIsFilterTurnedOn() && !visitFilteredEdge) || (fact->getFilterState(endNodeRef.getId()) == Filter::NotFiltered) || (!originalFilterState && visitFilteredEdge)) {
      if (apRoot) {
        if (visitCrossEdgeTree) {
          unvisitedNodes[endNodeRef.getId()] = true;
        }
      }
      if (traversaldCrossEdges[edkPostfixUnaryExpressionSyntax_OverloadedOperatorCall]) {
        endNodeRef.accept(*this);
      }
    }
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitEndPostfixUnaryExpressionSyntax_OverloadedOperatorCall(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;
  }
}

void AlgorithmPreorder::visit(const expression::PostfixUnaryExpressionSyntax& node, bool callFirst /*= true*/){
#ifdef DEBUG_PREORDER
  std::cout << "Rec. run: " << (unsigned int)&node << " " << node.getId() << " " << Common::toString(node.getNodeKind()) << std::endl;
#endif
  if (safeMode || visitCrossEdgeTree) {
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

void AlgorithmPreorder::visitAllEdges(const expression::PredefinedTypeSyntax& node, bool callFirst /*= true*/){
  visitAllEdges(dynamic_cast<const expression::TypeSyntax&>(node),false);
}

void AlgorithmPreorder::visit(const expression::PredefinedTypeSyntax& node, bool callFirst /*= true*/){
#ifdef DEBUG_PREORDER
  std::cout << "Rec. run: " << (unsigned int)&node << " " << node.getId() << " " << Common::toString(node.getNodeKind()) << std::endl;
#endif
  if (safeMode || visitCrossEdgeTree) {
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

void AlgorithmPreorder::visitAllEdges(const expression::PrefixUnaryExpressionSyntax& node, bool callFirst /*= true*/){
  visitAllEdges(dynamic_cast<const expression::ExpressionSyntax&>(node),false);

  std::list<Visitor*>::iterator itVisitors;

  const base::Base* genNodePtr;
  // edge: Operand
  genNodePtr = node.getOperand() ;
  if (genNodePtr) {
    const expression::ExpressionSyntax& endNodeRef = dynamic_cast<const expression::ExpressionSyntax&>(*genNodePtr);
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitPrefixUnaryExpressionSyntax_Operand(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;

    if ((!fact->getIsFilterTurnedOn() && !visitFilteredEdge) || (fact->getFilterState(endNodeRef.getId()) == Filter::NotFiltered) || (!originalFilterState && visitFilteredEdge)) {
      endNodeRef.accept(*this);
    }
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitEndPrefixUnaryExpressionSyntax_Operand(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;
  }

  // edge: OverloadedOperatorCall
  genNodePtr = node.getOverloadedOperatorCall() ;
  if (genNodePtr) {
    const structure::OperatorDeclarationSyntax& endNodeRef = dynamic_cast<const structure::OperatorDeclarationSyntax&>(*genNodePtr);
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitPrefixUnaryExpressionSyntax_OverloadedOperatorCall(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;

    if ((!fact->getIsFilterTurnedOn() && !visitFilteredEdge) || (fact->getFilterState(endNodeRef.getId()) == Filter::NotFiltered) || (!originalFilterState && visitFilteredEdge)) {
      if (apRoot) {
        if (visitCrossEdgeTree) {
          unvisitedNodes[endNodeRef.getId()] = true;
        }
      }
      if (traversaldCrossEdges[edkPrefixUnaryExpressionSyntax_OverloadedOperatorCall]) {
        endNodeRef.accept(*this);
      }
    }
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitEndPrefixUnaryExpressionSyntax_OverloadedOperatorCall(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;
  }
}

void AlgorithmPreorder::visit(const expression::PrefixUnaryExpressionSyntax& node, bool callFirst /*= true*/){
#ifdef DEBUG_PREORDER
  std::cout << "Rec. run: " << (unsigned int)&node << " " << node.getId() << " " << Common::toString(node.getNodeKind()) << std::endl;
#endif
  if (safeMode || visitCrossEdgeTree) {
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

void AlgorithmPreorder::visitAllEdges(const expression::QualifiedNameSyntax& node, bool callFirst /*= true*/){
  visitAllEdges(dynamic_cast<const expression::NameSyntax&>(node),false);

  std::list<Visitor*>::iterator itVisitors;

  const base::Base* genNodePtr;
  // edge: Left
  genNodePtr = node.getLeft() ;
  if (genNodePtr) {
    const expression::NameSyntax& endNodeRef = dynamic_cast<const expression::NameSyntax&>(*genNodePtr);
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitQualifiedNameSyntax_Left(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;

    if ((!fact->getIsFilterTurnedOn() && !visitFilteredEdge) || (fact->getFilterState(endNodeRef.getId()) == Filter::NotFiltered) || (!originalFilterState && visitFilteredEdge)) {
      endNodeRef.accept(*this);
    }
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitEndQualifiedNameSyntax_Left(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;
  }

  // edge: Right
  genNodePtr = node.getRight() ;
  if (genNodePtr) {
    const expression::SimpleNameSyntax& endNodeRef = dynamic_cast<const expression::SimpleNameSyntax&>(*genNodePtr);
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitQualifiedNameSyntax_Right(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;

    if ((!fact->getIsFilterTurnedOn() && !visitFilteredEdge) || (fact->getFilterState(endNodeRef.getId()) == Filter::NotFiltered) || (!originalFilterState && visitFilteredEdge)) {
      endNodeRef.accept(*this);
    }
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitEndQualifiedNameSyntax_Right(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;
  }
}

void AlgorithmPreorder::visit(const expression::QualifiedNameSyntax& node, bool callFirst /*= true*/){
#ifdef DEBUG_PREORDER
  std::cout << "Rec. run: " << (unsigned int)&node << " " << node.getId() << " " << Common::toString(node.getNodeKind()) << std::endl;
#endif
  if (safeMode || visitCrossEdgeTree) {
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

void AlgorithmPreorder::visitAllEdges(const expression::QueryExpressionSyntax& node, bool callFirst /*= true*/){
  visitAllEdges(dynamic_cast<const expression::ExpressionSyntax&>(node),false);

  std::list<Visitor*>::iterator itVisitors;

  const base::Base* genNodePtr;
  // edge: Body
  genNodePtr = node.getBody() ;
  if (genNodePtr) {
    const structure::QueryBodySyntax& endNodeRef = dynamic_cast<const structure::QueryBodySyntax&>(*genNodePtr);
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitQueryExpressionSyntax_Body(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;

    if ((!fact->getIsFilterTurnedOn() && !visitFilteredEdge) || (fact->getFilterState(endNodeRef.getId()) == Filter::NotFiltered) || (!originalFilterState && visitFilteredEdge)) {
      endNodeRef.accept(*this);
    }
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitEndQueryExpressionSyntax_Body(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;
  }

  // edge: FromClause
  genNodePtr = node.getFromClause() ;
  if (genNodePtr) {
    const structure::FromClauseSyntax& endNodeRef = dynamic_cast<const structure::FromClauseSyntax&>(*genNodePtr);
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitQueryExpressionSyntax_FromClause(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;

    if ((!fact->getIsFilterTurnedOn() && !visitFilteredEdge) || (fact->getFilterState(endNodeRef.getId()) == Filter::NotFiltered) || (!originalFilterState && visitFilteredEdge)) {
      endNodeRef.accept(*this);
    }
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitEndQueryExpressionSyntax_FromClause(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;
  }
}

void AlgorithmPreorder::visit(const expression::QueryExpressionSyntax& node, bool callFirst /*= true*/){
#ifdef DEBUG_PREORDER
  std::cout << "Rec. run: " << (unsigned int)&node << " " << node.getId() << " " << Common::toString(node.getNodeKind()) << std::endl;
#endif
  if (safeMode || visitCrossEdgeTree) {
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

void AlgorithmPreorder::visitAllEdges(const expression::RefTypeExpressionSyntax& node, bool callFirst /*= true*/){
  visitAllEdges(dynamic_cast<const expression::ExpressionSyntax&>(node),false);

  std::list<Visitor*>::iterator itVisitors;

  const base::Base* genNodePtr;
  // edge: Expression
  genNodePtr = node.getExpression() ;
  if (genNodePtr) {
    const expression::ExpressionSyntax& endNodeRef = dynamic_cast<const expression::ExpressionSyntax&>(*genNodePtr);
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitRefTypeExpressionSyntax_Expression(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;

    if ((!fact->getIsFilterTurnedOn() && !visitFilteredEdge) || (fact->getFilterState(endNodeRef.getId()) == Filter::NotFiltered) || (!originalFilterState && visitFilteredEdge)) {
      endNodeRef.accept(*this);
    }
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitEndRefTypeExpressionSyntax_Expression(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;
  }
}

void AlgorithmPreorder::visit(const expression::RefTypeExpressionSyntax& node, bool callFirst /*= true*/){
#ifdef DEBUG_PREORDER
  std::cout << "Rec. run: " << (unsigned int)&node << " " << node.getId() << " " << Common::toString(node.getNodeKind()) << std::endl;
#endif
  if (safeMode || visitCrossEdgeTree) {
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

void AlgorithmPreorder::visitAllEdges(const expression::RefValueExpressionSyntax& node, bool callFirst /*= true*/){
  visitAllEdges(dynamic_cast<const expression::ExpressionSyntax&>(node),false);

  std::list<Visitor*>::iterator itVisitors;

  const base::Base* genNodePtr;
  // edge: Expression
  genNodePtr = node.getExpression() ;
  if (genNodePtr) {
    const expression::ExpressionSyntax& endNodeRef = dynamic_cast<const expression::ExpressionSyntax&>(*genNodePtr);
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitRefValueExpressionSyntax_Expression(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;

    if ((!fact->getIsFilterTurnedOn() && !visitFilteredEdge) || (fact->getFilterState(endNodeRef.getId()) == Filter::NotFiltered) || (!originalFilterState && visitFilteredEdge)) {
      endNodeRef.accept(*this);
    }
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitEndRefValueExpressionSyntax_Expression(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;
  }

  // edge: Type
  genNodePtr = node.getType() ;
  if (genNodePtr) {
    const expression::TypeSyntax& endNodeRef = dynamic_cast<const expression::TypeSyntax&>(*genNodePtr);
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitRefValueExpressionSyntax_Type(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;

    if ((!fact->getIsFilterTurnedOn() && !visitFilteredEdge) || (fact->getFilterState(endNodeRef.getId()) == Filter::NotFiltered) || (!originalFilterState && visitFilteredEdge)) {
      endNodeRef.accept(*this);
    }
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitEndRefValueExpressionSyntax_Type(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;
  }
}

void AlgorithmPreorder::visit(const expression::RefValueExpressionSyntax& node, bool callFirst /*= true*/){
#ifdef DEBUG_PREORDER
  std::cout << "Rec. run: " << (unsigned int)&node << " " << node.getId() << " " << Common::toString(node.getNodeKind()) << std::endl;
#endif
  if (safeMode || visitCrossEdgeTree) {
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

void AlgorithmPreorder::visitAllEdges(const expression::SimpleLambdaExpressionSyntax& node, bool callFirst /*= true*/){
  visitAllEdges(dynamic_cast<const expression::LambdaExpressionSyntax&>(node),false);

  std::list<Visitor*>::iterator itVisitors;

  const base::Base* genNodePtr;
  // edge: Parameter
  genNodePtr = node.getParameter() ;
  if (genNodePtr) {
    const structure::ParameterSyntax& endNodeRef = dynamic_cast<const structure::ParameterSyntax&>(*genNodePtr);
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitSimpleLambdaExpressionSyntax_Parameter(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;

    if ((!fact->getIsFilterTurnedOn() && !visitFilteredEdge) || (fact->getFilterState(endNodeRef.getId()) == Filter::NotFiltered) || (!originalFilterState && visitFilteredEdge)) {
      endNodeRef.accept(*this);
    }
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitEndSimpleLambdaExpressionSyntax_Parameter(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;
  }
}

void AlgorithmPreorder::visit(const expression::SimpleLambdaExpressionSyntax& node, bool callFirst /*= true*/){
#ifdef DEBUG_PREORDER
  std::cout << "Rec. run: " << (unsigned int)&node << " " << node.getId() << " " << Common::toString(node.getNodeKind()) << std::endl;
#endif
  if (safeMode || visitCrossEdgeTree) {
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

void AlgorithmPreorder::visitAllEdges(const expression::SimpleNameSyntax& node, bool callFirst /*= true*/){
  visitAllEdges(dynamic_cast<const expression::NameSyntax&>(node),false);
}

void AlgorithmPreorder::visitAllEdges(const expression::SizeOfExpressionSyntax& node, bool callFirst /*= true*/){
  visitAllEdges(dynamic_cast<const expression::ExpressionSyntax&>(node),false);

  std::list<Visitor*>::iterator itVisitors;

  const base::Base* genNodePtr;
  // edge: Type
  genNodePtr = node.getType() ;
  if (genNodePtr) {
    const expression::TypeSyntax& endNodeRef = dynamic_cast<const expression::TypeSyntax&>(*genNodePtr);
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitSizeOfExpressionSyntax_Type(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;

    if ((!fact->getIsFilterTurnedOn() && !visitFilteredEdge) || (fact->getFilterState(endNodeRef.getId()) == Filter::NotFiltered) || (!originalFilterState && visitFilteredEdge)) {
      endNodeRef.accept(*this);
    }
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitEndSizeOfExpressionSyntax_Type(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;
  }
}

void AlgorithmPreorder::visit(const expression::SizeOfExpressionSyntax& node, bool callFirst /*= true*/){
#ifdef DEBUG_PREORDER
  std::cout << "Rec. run: " << (unsigned int)&node << " " << node.getId() << " " << Common::toString(node.getNodeKind()) << std::endl;
#endif
  if (safeMode || visitCrossEdgeTree) {
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

void AlgorithmPreorder::visitAllEdges(const expression::StackAllocArrayCreationExpressionSyntax& node, bool callFirst /*= true*/){
  visitAllEdges(dynamic_cast<const expression::ExpressionSyntax&>(node),false);

  std::list<Visitor*>::iterator itVisitors;

  const base::Base* genNodePtr;
  // edge: Type
  genNodePtr = node.getType() ;
  if (genNodePtr) {
    const expression::TypeSyntax& endNodeRef = dynamic_cast<const expression::TypeSyntax&>(*genNodePtr);
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitStackAllocArrayCreationExpressionSyntax_Type(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;

    if ((!fact->getIsFilterTurnedOn() && !visitFilteredEdge) || (fact->getFilterState(endNodeRef.getId()) == Filter::NotFiltered) || (!originalFilterState && visitFilteredEdge)) {
      endNodeRef.accept(*this);
    }
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitEndStackAllocArrayCreationExpressionSyntax_Type(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;
  }
}

void AlgorithmPreorder::visit(const expression::StackAllocArrayCreationExpressionSyntax& node, bool callFirst /*= true*/){
#ifdef DEBUG_PREORDER
  std::cout << "Rec. run: " << (unsigned int)&node << " " << node.getId() << " " << Common::toString(node.getNodeKind()) << std::endl;
#endif
  if (safeMode || visitCrossEdgeTree) {
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

void AlgorithmPreorder::visitAllEdges(const expression::ThisExpressionSyntax& node, bool callFirst /*= true*/){
  visitAllEdges(dynamic_cast<const expression::InstanceExpressionSyntax&>(node),false);
}

void AlgorithmPreorder::visit(const expression::ThisExpressionSyntax& node, bool callFirst /*= true*/){
#ifdef DEBUG_PREORDER
  std::cout << "Rec. run: " << (unsigned int)&node << " " << node.getId() << " " << Common::toString(node.getNodeKind()) << std::endl;
#endif
  if (safeMode || visitCrossEdgeTree) {
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

void AlgorithmPreorder::visitAllEdges(const expression::TypeOfExpressionSyntax& node, bool callFirst /*= true*/){
  visitAllEdges(dynamic_cast<const expression::ExpressionSyntax&>(node),false);

  std::list<Visitor*>::iterator itVisitors;

  const base::Base* genNodePtr;
  // edge: Type
  genNodePtr = node.getType() ;
  if (genNodePtr) {
    const expression::TypeSyntax& endNodeRef = dynamic_cast<const expression::TypeSyntax&>(*genNodePtr);
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitTypeOfExpressionSyntax_Type(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;

    if ((!fact->getIsFilterTurnedOn() && !visitFilteredEdge) || (fact->getFilterState(endNodeRef.getId()) == Filter::NotFiltered) || (!originalFilterState && visitFilteredEdge)) {
      endNodeRef.accept(*this);
    }
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitEndTypeOfExpressionSyntax_Type(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;
  }
}

void AlgorithmPreorder::visit(const expression::TypeOfExpressionSyntax& node, bool callFirst /*= true*/){
#ifdef DEBUG_PREORDER
  std::cout << "Rec. run: " << (unsigned int)&node << " " << node.getId() << " " << Common::toString(node.getNodeKind()) << std::endl;
#endif
  if (safeMode || visitCrossEdgeTree) {
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

void AlgorithmPreorder::visitAllEdges(const expression::TypeSyntax& node, bool callFirst /*= true*/){
  visitAllEdges(dynamic_cast<const expression::ExpressionSyntax&>(node),false);

  std::list<Visitor*>::iterator itVisitors;

  const base::Base* genNodePtr;
  // edge: OriginalDefinition
  genNodePtr = node.getOriginalDefinition() ;
  if (genNodePtr) {
    const structure::MemberDeclarationSyntax& endNodeRef = dynamic_cast<const structure::MemberDeclarationSyntax&>(*genNodePtr);
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitTypeSyntax_OriginalDefinition(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;

    if ((!fact->getIsFilterTurnedOn() && !visitFilteredEdge) || (fact->getFilterState(endNodeRef.getId()) == Filter::NotFiltered) || (!originalFilterState && visitFilteredEdge)) {
      if (apRoot) {
        if (visitCrossEdgeTree) {
          unvisitedNodes[endNodeRef.getId()] = true;
        }
      }
      if (traversaldCrossEdges[edkTypeSyntax_OriginalDefinition]) {
        endNodeRef.accept(*this);
      }
    }
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitEndTypeSyntax_OriginalDefinition(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;
  }
}

void AlgorithmPreorder::visitAllEdges(const statement::BlockSyntax& node, bool callFirst /*= true*/){
  visitAllEdges(dynamic_cast<const statement::StatementSyntax&>(node),false);

  std::list<Visitor*>::iterator itVisitors;

  // edge: Statements
  for (ListIterator<statement::StatementSyntax> it = node.getStatementsListIteratorBegin(); it != node.getStatementsListIteratorEnd(); ++it) {
    const statement::StatementSyntax& endNodeRef = *it;
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitBlockSyntax_Statements(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;

    if ((!fact->getIsFilterTurnedOn() && !visitFilteredEdge) || (fact->getFilterState(endNodeRef.getId()) == Filter::NotFiltered) || (!originalFilterState && visitFilteredEdge)) {
      endNodeRef.accept(*this);
    }
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitEndBlockSyntax_Statements(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;
  }
}

void AlgorithmPreorder::visit(const statement::BlockSyntax& node, bool callFirst /*= true*/){
#ifdef DEBUG_PREORDER
  std::cout << "Rec. run: " << (unsigned int)&node << " " << node.getId() << " " << Common::toString(node.getNodeKind()) << std::endl;
#endif
  if (safeMode || visitCrossEdgeTree) {
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

void AlgorithmPreorder::visitAllEdges(const statement::BreakStatementSyntax& node, bool callFirst /*= true*/){
  visitAllEdges(dynamic_cast<const statement::StatementSyntax&>(node),false);
}

void AlgorithmPreorder::visit(const statement::BreakStatementSyntax& node, bool callFirst /*= true*/){
#ifdef DEBUG_PREORDER
  std::cout << "Rec. run: " << (unsigned int)&node << " " << node.getId() << " " << Common::toString(node.getNodeKind()) << std::endl;
#endif
  if (safeMode || visitCrossEdgeTree) {
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

void AlgorithmPreorder::visitAllEdges(const statement::CheckedStatementSyntax& node, bool callFirst /*= true*/){
  visitAllEdges(dynamic_cast<const statement::StatementSyntax&>(node),false);

  std::list<Visitor*>::iterator itVisitors;

  const base::Base* genNodePtr;
  // edge: Block
  genNodePtr = node.getBlock() ;
  if (genNodePtr) {
    const statement::BlockSyntax& endNodeRef = dynamic_cast<const statement::BlockSyntax&>(*genNodePtr);
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitCheckedStatementSyntax_Block(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;

    if ((!fact->getIsFilterTurnedOn() && !visitFilteredEdge) || (fact->getFilterState(endNodeRef.getId()) == Filter::NotFiltered) || (!originalFilterState && visitFilteredEdge)) {
      endNodeRef.accept(*this);
    }
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitEndCheckedStatementSyntax_Block(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;
  }
}

void AlgorithmPreorder::visit(const statement::CheckedStatementSyntax& node, bool callFirst /*= true*/){
#ifdef DEBUG_PREORDER
  std::cout << "Rec. run: " << (unsigned int)&node << " " << node.getId() << " " << Common::toString(node.getNodeKind()) << std::endl;
#endif
  if (safeMode || visitCrossEdgeTree) {
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

void AlgorithmPreorder::visitAllEdges(const statement::ContinueStatementSyntax& node, bool callFirst /*= true*/){
  visitAllEdges(dynamic_cast<const statement::StatementSyntax&>(node),false);
}

void AlgorithmPreorder::visit(const statement::ContinueStatementSyntax& node, bool callFirst /*= true*/){
#ifdef DEBUG_PREORDER
  std::cout << "Rec. run: " << (unsigned int)&node << " " << node.getId() << " " << Common::toString(node.getNodeKind()) << std::endl;
#endif
  if (safeMode || visitCrossEdgeTree) {
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

void AlgorithmPreorder::visitAllEdges(const statement::DoStatementSyntax& node, bool callFirst /*= true*/){
  visitAllEdges(dynamic_cast<const statement::StatementSyntax&>(node),false);

  std::list<Visitor*>::iterator itVisitors;

  const base::Base* genNodePtr;
  // edge: Condition
  genNodePtr = node.getCondition() ;
  if (genNodePtr) {
    const expression::ExpressionSyntax& endNodeRef = dynamic_cast<const expression::ExpressionSyntax&>(*genNodePtr);
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitDoStatementSyntax_Condition(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;

    if ((!fact->getIsFilterTurnedOn() && !visitFilteredEdge) || (fact->getFilterState(endNodeRef.getId()) == Filter::NotFiltered) || (!originalFilterState && visitFilteredEdge)) {
      endNodeRef.accept(*this);
    }
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitEndDoStatementSyntax_Condition(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;
  }

  // edge: Statement
  genNodePtr = node.getStatement() ;
  if (genNodePtr) {
    const statement::StatementSyntax& endNodeRef = dynamic_cast<const statement::StatementSyntax&>(*genNodePtr);
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitDoStatementSyntax_Statement(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;

    if ((!fact->getIsFilterTurnedOn() && !visitFilteredEdge) || (fact->getFilterState(endNodeRef.getId()) == Filter::NotFiltered) || (!originalFilterState && visitFilteredEdge)) {
      endNodeRef.accept(*this);
    }
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitEndDoStatementSyntax_Statement(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;
  }
}

void AlgorithmPreorder::visit(const statement::DoStatementSyntax& node, bool callFirst /*= true*/){
#ifdef DEBUG_PREORDER
  std::cout << "Rec. run: " << (unsigned int)&node << " " << node.getId() << " " << Common::toString(node.getNodeKind()) << std::endl;
#endif
  if (safeMode || visitCrossEdgeTree) {
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

void AlgorithmPreorder::visitAllEdges(const statement::EmptyStatementSyntax& node, bool callFirst /*= true*/){
  visitAllEdges(dynamic_cast<const statement::StatementSyntax&>(node),false);
}

void AlgorithmPreorder::visit(const statement::EmptyStatementSyntax& node, bool callFirst /*= true*/){
#ifdef DEBUG_PREORDER
  std::cout << "Rec. run: " << (unsigned int)&node << " " << node.getId() << " " << Common::toString(node.getNodeKind()) << std::endl;
#endif
  if (safeMode || visitCrossEdgeTree) {
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

void AlgorithmPreorder::visitAllEdges(const statement::ExpressionStatementSyntax& node, bool callFirst /*= true*/){
  visitAllEdges(dynamic_cast<const statement::StatementSyntax&>(node),false);

  std::list<Visitor*>::iterator itVisitors;

  const base::Base* genNodePtr;
  // edge: Expression
  genNodePtr = node.getExpression() ;
  if (genNodePtr) {
    const expression::ExpressionSyntax& endNodeRef = dynamic_cast<const expression::ExpressionSyntax&>(*genNodePtr);
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitExpressionStatementSyntax_Expression(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;

    if ((!fact->getIsFilterTurnedOn() && !visitFilteredEdge) || (fact->getFilterState(endNodeRef.getId()) == Filter::NotFiltered) || (!originalFilterState && visitFilteredEdge)) {
      endNodeRef.accept(*this);
    }
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitEndExpressionStatementSyntax_Expression(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;
  }
}

void AlgorithmPreorder::visit(const statement::ExpressionStatementSyntax& node, bool callFirst /*= true*/){
#ifdef DEBUG_PREORDER
  std::cout << "Rec. run: " << (unsigned int)&node << " " << node.getId() << " " << Common::toString(node.getNodeKind()) << std::endl;
#endif
  if (safeMode || visitCrossEdgeTree) {
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

void AlgorithmPreorder::visitAllEdges(const statement::FixedStatementSyntax& node, bool callFirst /*= true*/){
  visitAllEdges(dynamic_cast<const statement::StatementSyntax&>(node),false);

  std::list<Visitor*>::iterator itVisitors;

  const base::Base* genNodePtr;
  // edge: Declaration
  genNodePtr = node.getDeclaration() ;
  if (genNodePtr) {
    const structure::VariableDeclarationSyntax& endNodeRef = dynamic_cast<const structure::VariableDeclarationSyntax&>(*genNodePtr);
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitFixedStatementSyntax_Declaration(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;

    if ((!fact->getIsFilterTurnedOn() && !visitFilteredEdge) || (fact->getFilterState(endNodeRef.getId()) == Filter::NotFiltered) || (!originalFilterState && visitFilteredEdge)) {
      endNodeRef.accept(*this);
    }
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitEndFixedStatementSyntax_Declaration(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;
  }

  // edge: Statement
  genNodePtr = node.getStatement() ;
  if (genNodePtr) {
    const statement::StatementSyntax& endNodeRef = dynamic_cast<const statement::StatementSyntax&>(*genNodePtr);
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitFixedStatementSyntax_Statement(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;

    if ((!fact->getIsFilterTurnedOn() && !visitFilteredEdge) || (fact->getFilterState(endNodeRef.getId()) == Filter::NotFiltered) || (!originalFilterState && visitFilteredEdge)) {
      endNodeRef.accept(*this);
    }
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitEndFixedStatementSyntax_Statement(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;
  }
}

void AlgorithmPreorder::visit(const statement::FixedStatementSyntax& node, bool callFirst /*= true*/){
#ifdef DEBUG_PREORDER
  std::cout << "Rec. run: " << (unsigned int)&node << " " << node.getId() << " " << Common::toString(node.getNodeKind()) << std::endl;
#endif
  if (safeMode || visitCrossEdgeTree) {
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

void AlgorithmPreorder::visitAllEdges(const statement::ForEachStatementSyntax& node, bool callFirst /*= true*/){
  visitAllEdges(dynamic_cast<const statement::StatementSyntax&>(node),false);

  std::list<Visitor*>::iterator itVisitors;

  const base::Base* genNodePtr;
  // edge: Expression
  genNodePtr = node.getExpression() ;
  if (genNodePtr) {
    const expression::ExpressionSyntax& endNodeRef = dynamic_cast<const expression::ExpressionSyntax&>(*genNodePtr);
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitForEachStatementSyntax_Expression(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;

    if ((!fact->getIsFilterTurnedOn() && !visitFilteredEdge) || (fact->getFilterState(endNodeRef.getId()) == Filter::NotFiltered) || (!originalFilterState && visitFilteredEdge)) {
      endNodeRef.accept(*this);
    }
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitEndForEachStatementSyntax_Expression(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;
  }

  // edge: Statement
  genNodePtr = node.getStatement() ;
  if (genNodePtr) {
    const statement::StatementSyntax& endNodeRef = dynamic_cast<const statement::StatementSyntax&>(*genNodePtr);
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitForEachStatementSyntax_Statement(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;

    if ((!fact->getIsFilterTurnedOn() && !visitFilteredEdge) || (fact->getFilterState(endNodeRef.getId()) == Filter::NotFiltered) || (!originalFilterState && visitFilteredEdge)) {
      endNodeRef.accept(*this);
    }
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitEndForEachStatementSyntax_Statement(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;
  }

  // edge: Type
  genNodePtr = node.getType() ;
  if (genNodePtr) {
    const expression::TypeSyntax& endNodeRef = dynamic_cast<const expression::TypeSyntax&>(*genNodePtr);
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitForEachStatementSyntax_Type(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;

    if ((!fact->getIsFilterTurnedOn() && !visitFilteredEdge) || (fact->getFilterState(endNodeRef.getId()) == Filter::NotFiltered) || (!originalFilterState && visitFilteredEdge)) {
      endNodeRef.accept(*this);
    }
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitEndForEachStatementSyntax_Type(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;
  }
}

void AlgorithmPreorder::visit(const statement::ForEachStatementSyntax& node, bool callFirst /*= true*/){
#ifdef DEBUG_PREORDER
  std::cout << "Rec. run: " << (unsigned int)&node << " " << node.getId() << " " << Common::toString(node.getNodeKind()) << std::endl;
#endif
  if (safeMode || visitCrossEdgeTree) {
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

void AlgorithmPreorder::visitAllEdges(const statement::ForStatementSyntax& node, bool callFirst /*= true*/){
  visitAllEdges(dynamic_cast<const statement::StatementSyntax&>(node),false);

  std::list<Visitor*>::iterator itVisitors;

  const base::Base* genNodePtr;
  // edge: Condition
  genNodePtr = node.getCondition() ;
  if (genNodePtr) {
    const expression::ExpressionSyntax& endNodeRef = dynamic_cast<const expression::ExpressionSyntax&>(*genNodePtr);
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitForStatementSyntax_Condition(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;

    if ((!fact->getIsFilterTurnedOn() && !visitFilteredEdge) || (fact->getFilterState(endNodeRef.getId()) == Filter::NotFiltered) || (!originalFilterState && visitFilteredEdge)) {
      endNodeRef.accept(*this);
    }
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitEndForStatementSyntax_Condition(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;
  }

  // edge: Declaration
  genNodePtr = node.getDeclaration() ;
  if (genNodePtr) {
    const structure::VariableDeclarationSyntax& endNodeRef = dynamic_cast<const structure::VariableDeclarationSyntax&>(*genNodePtr);
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitForStatementSyntax_Declaration(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;

    if ((!fact->getIsFilterTurnedOn() && !visitFilteredEdge) || (fact->getFilterState(endNodeRef.getId()) == Filter::NotFiltered) || (!originalFilterState && visitFilteredEdge)) {
      endNodeRef.accept(*this);
    }
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitEndForStatementSyntax_Declaration(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;
  }

  // edge: Incrementors
  for (ListIterator<expression::ExpressionSyntax> it = node.getIncrementorsListIteratorBegin(); it != node.getIncrementorsListIteratorEnd(); ++it) {
    const expression::ExpressionSyntax& endNodeRef = *it;
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitForStatementSyntax_Incrementors(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;

    if ((!fact->getIsFilterTurnedOn() && !visitFilteredEdge) || (fact->getFilterState(endNodeRef.getId()) == Filter::NotFiltered) || (!originalFilterState && visitFilteredEdge)) {
      endNodeRef.accept(*this);
    }
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitEndForStatementSyntax_Incrementors(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;
  }

  // edge: Initializers
  for (ListIterator<expression::ExpressionSyntax> it = node.getInitializersListIteratorBegin(); it != node.getInitializersListIteratorEnd(); ++it) {
    const expression::ExpressionSyntax& endNodeRef = *it;
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitForStatementSyntax_Initializers(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;

    if ((!fact->getIsFilterTurnedOn() && !visitFilteredEdge) || (fact->getFilterState(endNodeRef.getId()) == Filter::NotFiltered) || (!originalFilterState && visitFilteredEdge)) {
      endNodeRef.accept(*this);
    }
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitEndForStatementSyntax_Initializers(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;
  }

  // edge: Statement
  genNodePtr = node.getStatement() ;
  if (genNodePtr) {
    const statement::StatementSyntax& endNodeRef = dynamic_cast<const statement::StatementSyntax&>(*genNodePtr);
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitForStatementSyntax_Statement(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;

    if ((!fact->getIsFilterTurnedOn() && !visitFilteredEdge) || (fact->getFilterState(endNodeRef.getId()) == Filter::NotFiltered) || (!originalFilterState && visitFilteredEdge)) {
      endNodeRef.accept(*this);
    }
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitEndForStatementSyntax_Statement(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;
  }
}

void AlgorithmPreorder::visit(const statement::ForStatementSyntax& node, bool callFirst /*= true*/){
#ifdef DEBUG_PREORDER
  std::cout << "Rec. run: " << (unsigned int)&node << " " << node.getId() << " " << Common::toString(node.getNodeKind()) << std::endl;
#endif
  if (safeMode || visitCrossEdgeTree) {
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

void AlgorithmPreorder::visitAllEdges(const statement::GotoStatementSyntax& node, bool callFirst /*= true*/){
  visitAllEdges(dynamic_cast<const statement::StatementSyntax&>(node),false);

  std::list<Visitor*>::iterator itVisitors;

  const base::Base* genNodePtr;
  // edge: Expression
  genNodePtr = node.getExpression() ;
  if (genNodePtr) {
    const expression::ExpressionSyntax& endNodeRef = dynamic_cast<const expression::ExpressionSyntax&>(*genNodePtr);
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitGotoStatementSyntax_Expression(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;

    if ((!fact->getIsFilterTurnedOn() && !visitFilteredEdge) || (fact->getFilterState(endNodeRef.getId()) == Filter::NotFiltered) || (!originalFilterState && visitFilteredEdge)) {
      endNodeRef.accept(*this);
    }
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitEndGotoStatementSyntax_Expression(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;
  }
}

void AlgorithmPreorder::visit(const statement::GotoStatementSyntax& node, bool callFirst /*= true*/){
#ifdef DEBUG_PREORDER
  std::cout << "Rec. run: " << (unsigned int)&node << " " << node.getId() << " " << Common::toString(node.getNodeKind()) << std::endl;
#endif
  if (safeMode || visitCrossEdgeTree) {
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

void AlgorithmPreorder::visitAllEdges(const statement::IfStatementSyntax& node, bool callFirst /*= true*/){
  visitAllEdges(dynamic_cast<const statement::StatementSyntax&>(node),false);

  std::list<Visitor*>::iterator itVisitors;

  const base::Base* genNodePtr;
  // edge: Condition
  genNodePtr = node.getCondition() ;
  if (genNodePtr) {
    const expression::ExpressionSyntax& endNodeRef = dynamic_cast<const expression::ExpressionSyntax&>(*genNodePtr);
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitIfStatementSyntax_Condition(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;

    if ((!fact->getIsFilterTurnedOn() && !visitFilteredEdge) || (fact->getFilterState(endNodeRef.getId()) == Filter::NotFiltered) || (!originalFilterState && visitFilteredEdge)) {
      endNodeRef.accept(*this);
    }
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitEndIfStatementSyntax_Condition(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;
  }

  // edge: Else
  genNodePtr = node.getElse() ;
  if (genNodePtr) {
    const structure::ElseClauseSyntax& endNodeRef = dynamic_cast<const structure::ElseClauseSyntax&>(*genNodePtr);
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitIfStatementSyntax_Else(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;

    if ((!fact->getIsFilterTurnedOn() && !visitFilteredEdge) || (fact->getFilterState(endNodeRef.getId()) == Filter::NotFiltered) || (!originalFilterState && visitFilteredEdge)) {
      endNodeRef.accept(*this);
    }
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitEndIfStatementSyntax_Else(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;
  }

  // edge: Statement
  genNodePtr = node.getStatement() ;
  if (genNodePtr) {
    const statement::StatementSyntax& endNodeRef = dynamic_cast<const statement::StatementSyntax&>(*genNodePtr);
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitIfStatementSyntax_Statement(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;

    if ((!fact->getIsFilterTurnedOn() && !visitFilteredEdge) || (fact->getFilterState(endNodeRef.getId()) == Filter::NotFiltered) || (!originalFilterState && visitFilteredEdge)) {
      endNodeRef.accept(*this);
    }
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitEndIfStatementSyntax_Statement(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;
  }
}

void AlgorithmPreorder::visit(const statement::IfStatementSyntax& node, bool callFirst /*= true*/){
#ifdef DEBUG_PREORDER
  std::cout << "Rec. run: " << (unsigned int)&node << " " << node.getId() << " " << Common::toString(node.getNodeKind()) << std::endl;
#endif
  if (safeMode || visitCrossEdgeTree) {
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

void AlgorithmPreorder::visitAllEdges(const statement::LabeledStatementSyntax& node, bool callFirst /*= true*/){
  visitAllEdges(dynamic_cast<const statement::StatementSyntax&>(node),false);

  std::list<Visitor*>::iterator itVisitors;

  const base::Base* genNodePtr;
  // edge: Statement
  genNodePtr = node.getStatement() ;
  if (genNodePtr) {
    const statement::StatementSyntax& endNodeRef = dynamic_cast<const statement::StatementSyntax&>(*genNodePtr);
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitLabeledStatementSyntax_Statement(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;

    if ((!fact->getIsFilterTurnedOn() && !visitFilteredEdge) || (fact->getFilterState(endNodeRef.getId()) == Filter::NotFiltered) || (!originalFilterState && visitFilteredEdge)) {
      endNodeRef.accept(*this);
    }
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitEndLabeledStatementSyntax_Statement(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;
  }
}

void AlgorithmPreorder::visit(const statement::LabeledStatementSyntax& node, bool callFirst /*= true*/){
#ifdef DEBUG_PREORDER
  std::cout << "Rec. run: " << (unsigned int)&node << " " << node.getId() << " " << Common::toString(node.getNodeKind()) << std::endl;
#endif
  if (safeMode || visitCrossEdgeTree) {
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

void AlgorithmPreorder::visitAllEdges(const statement::LocalDeclarationStatementSyntax& node, bool callFirst /*= true*/){
  visitAllEdges(dynamic_cast<const statement::StatementSyntax&>(node),false);

  std::list<Visitor*>::iterator itVisitors;

  const base::Base* genNodePtr;
  // edge: Declaration
  genNodePtr = node.getDeclaration() ;
  if (genNodePtr) {
    const structure::VariableDeclarationSyntax& endNodeRef = dynamic_cast<const structure::VariableDeclarationSyntax&>(*genNodePtr);
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitLocalDeclarationStatementSyntax_Declaration(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;

    if ((!fact->getIsFilterTurnedOn() && !visitFilteredEdge) || (fact->getFilterState(endNodeRef.getId()) == Filter::NotFiltered) || (!originalFilterState && visitFilteredEdge)) {
      endNodeRef.accept(*this);
    }
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitEndLocalDeclarationStatementSyntax_Declaration(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;
  }
}

void AlgorithmPreorder::visit(const statement::LocalDeclarationStatementSyntax& node, bool callFirst /*= true*/){
#ifdef DEBUG_PREORDER
  std::cout << "Rec. run: " << (unsigned int)&node << " " << node.getId() << " " << Common::toString(node.getNodeKind()) << std::endl;
#endif
  if (safeMode || visitCrossEdgeTree) {
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

void AlgorithmPreorder::visitAllEdges(const statement::LockStatementSyntax& node, bool callFirst /*= true*/){
  visitAllEdges(dynamic_cast<const statement::StatementSyntax&>(node),false);

  std::list<Visitor*>::iterator itVisitors;

  const base::Base* genNodePtr;
  // edge: Expression
  genNodePtr = node.getExpression() ;
  if (genNodePtr) {
    const expression::ExpressionSyntax& endNodeRef = dynamic_cast<const expression::ExpressionSyntax&>(*genNodePtr);
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitLockStatementSyntax_Expression(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;

    if ((!fact->getIsFilterTurnedOn() && !visitFilteredEdge) || (fact->getFilterState(endNodeRef.getId()) == Filter::NotFiltered) || (!originalFilterState && visitFilteredEdge)) {
      endNodeRef.accept(*this);
    }
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitEndLockStatementSyntax_Expression(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;
  }

  // edge: Statement
  genNodePtr = node.getStatement() ;
  if (genNodePtr) {
    const statement::StatementSyntax& endNodeRef = dynamic_cast<const statement::StatementSyntax&>(*genNodePtr);
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitLockStatementSyntax_Statement(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;

    if ((!fact->getIsFilterTurnedOn() && !visitFilteredEdge) || (fact->getFilterState(endNodeRef.getId()) == Filter::NotFiltered) || (!originalFilterState && visitFilteredEdge)) {
      endNodeRef.accept(*this);
    }
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitEndLockStatementSyntax_Statement(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;
  }
}

void AlgorithmPreorder::visit(const statement::LockStatementSyntax& node, bool callFirst /*= true*/){
#ifdef DEBUG_PREORDER
  std::cout << "Rec. run: " << (unsigned int)&node << " " << node.getId() << " " << Common::toString(node.getNodeKind()) << std::endl;
#endif
  if (safeMode || visitCrossEdgeTree) {
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

void AlgorithmPreorder::visitAllEdges(const statement::ReturnStatementSyntax& node, bool callFirst /*= true*/){
  visitAllEdges(dynamic_cast<const statement::StatementSyntax&>(node),false);

  std::list<Visitor*>::iterator itVisitors;

  const base::Base* genNodePtr;
  // edge: Expression
  genNodePtr = node.getExpression() ;
  if (genNodePtr) {
    const expression::ExpressionSyntax& endNodeRef = dynamic_cast<const expression::ExpressionSyntax&>(*genNodePtr);
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitReturnStatementSyntax_Expression(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;

    if ((!fact->getIsFilterTurnedOn() && !visitFilteredEdge) || (fact->getFilterState(endNodeRef.getId()) == Filter::NotFiltered) || (!originalFilterState && visitFilteredEdge)) {
      endNodeRef.accept(*this);
    }
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitEndReturnStatementSyntax_Expression(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;
  }
}

void AlgorithmPreorder::visit(const statement::ReturnStatementSyntax& node, bool callFirst /*= true*/){
#ifdef DEBUG_PREORDER
  std::cout << "Rec. run: " << (unsigned int)&node << " " << node.getId() << " " << Common::toString(node.getNodeKind()) << std::endl;
#endif
  if (safeMode || visitCrossEdgeTree) {
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

void AlgorithmPreorder::visitAllEdges(const statement::StatementSyntax& node, bool callFirst /*= true*/){
  visitAllEdges(dynamic_cast<const base::Positioned&>(node),false);
}

void AlgorithmPreorder::visitAllEdges(const statement::SwitchStatementSyntax& node, bool callFirst /*= true*/){
  visitAllEdges(dynamic_cast<const statement::StatementSyntax&>(node),false);

  std::list<Visitor*>::iterator itVisitors;

  const base::Base* genNodePtr;
  // edge: Expression
  genNodePtr = node.getExpression() ;
  if (genNodePtr) {
    const expression::ExpressionSyntax& endNodeRef = dynamic_cast<const expression::ExpressionSyntax&>(*genNodePtr);
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitSwitchStatementSyntax_Expression(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;

    if ((!fact->getIsFilterTurnedOn() && !visitFilteredEdge) || (fact->getFilterState(endNodeRef.getId()) == Filter::NotFiltered) || (!originalFilterState && visitFilteredEdge)) {
      endNodeRef.accept(*this);
    }
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitEndSwitchStatementSyntax_Expression(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;
  }

  // edge: Sections
  for (ListIterator<structure::SwitchSectionSyntax> it = node.getSectionsListIteratorBegin(); it != node.getSectionsListIteratorEnd(); ++it) {
    const structure::SwitchSectionSyntax& endNodeRef = *it;
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitSwitchStatementSyntax_Sections(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;

    if ((!fact->getIsFilterTurnedOn() && !visitFilteredEdge) || (fact->getFilterState(endNodeRef.getId()) == Filter::NotFiltered) || (!originalFilterState && visitFilteredEdge)) {
      endNodeRef.accept(*this);
    }
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitEndSwitchStatementSyntax_Sections(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;
  }
}

void AlgorithmPreorder::visit(const statement::SwitchStatementSyntax& node, bool callFirst /*= true*/){
#ifdef DEBUG_PREORDER
  std::cout << "Rec. run: " << (unsigned int)&node << " " << node.getId() << " " << Common::toString(node.getNodeKind()) << std::endl;
#endif
  if (safeMode || visitCrossEdgeTree) {
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

void AlgorithmPreorder::visitAllEdges(const statement::ThrowStatementSyntax& node, bool callFirst /*= true*/){
  visitAllEdges(dynamic_cast<const statement::StatementSyntax&>(node),false);

  std::list<Visitor*>::iterator itVisitors;

  const base::Base* genNodePtr;
  // edge: Expression
  genNodePtr = node.getExpression() ;
  if (genNodePtr) {
    const expression::ExpressionSyntax& endNodeRef = dynamic_cast<const expression::ExpressionSyntax&>(*genNodePtr);
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitThrowStatementSyntax_Expression(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;

    if ((!fact->getIsFilterTurnedOn() && !visitFilteredEdge) || (fact->getFilterState(endNodeRef.getId()) == Filter::NotFiltered) || (!originalFilterState && visitFilteredEdge)) {
      endNodeRef.accept(*this);
    }
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitEndThrowStatementSyntax_Expression(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;
  }
}

void AlgorithmPreorder::visit(const statement::ThrowStatementSyntax& node, bool callFirst /*= true*/){
#ifdef DEBUG_PREORDER
  std::cout << "Rec. run: " << (unsigned int)&node << " " << node.getId() << " " << Common::toString(node.getNodeKind()) << std::endl;
#endif
  if (safeMode || visitCrossEdgeTree) {
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

void AlgorithmPreorder::visitAllEdges(const statement::TryStatementSyntax& node, bool callFirst /*= true*/){
  visitAllEdges(dynamic_cast<const statement::StatementSyntax&>(node),false);

  std::list<Visitor*>::iterator itVisitors;

  const base::Base* genNodePtr;
  // edge: Block
  genNodePtr = node.getBlock() ;
  if (genNodePtr) {
    const statement::BlockSyntax& endNodeRef = dynamic_cast<const statement::BlockSyntax&>(*genNodePtr);
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitTryStatementSyntax_Block(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;

    if ((!fact->getIsFilterTurnedOn() && !visitFilteredEdge) || (fact->getFilterState(endNodeRef.getId()) == Filter::NotFiltered) || (!originalFilterState && visitFilteredEdge)) {
      endNodeRef.accept(*this);
    }
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitEndTryStatementSyntax_Block(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;
  }

  // edge: Catches
  for (ListIterator<structure::CatchClauseSyntax> it = node.getCatchesListIteratorBegin(); it != node.getCatchesListIteratorEnd(); ++it) {
    const structure::CatchClauseSyntax& endNodeRef = *it;
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitTryStatementSyntax_Catches(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;

    if ((!fact->getIsFilterTurnedOn() && !visitFilteredEdge) || (fact->getFilterState(endNodeRef.getId()) == Filter::NotFiltered) || (!originalFilterState && visitFilteredEdge)) {
      endNodeRef.accept(*this);
    }
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitEndTryStatementSyntax_Catches(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;
  }

  // edge: Finally
  genNodePtr = node.getFinally() ;
  if (genNodePtr) {
    const structure::FinallyClauseSyntax& endNodeRef = dynamic_cast<const structure::FinallyClauseSyntax&>(*genNodePtr);
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitTryStatementSyntax_Finally(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;

    if ((!fact->getIsFilterTurnedOn() && !visitFilteredEdge) || (fact->getFilterState(endNodeRef.getId()) == Filter::NotFiltered) || (!originalFilterState && visitFilteredEdge)) {
      endNodeRef.accept(*this);
    }
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitEndTryStatementSyntax_Finally(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;
  }
}

void AlgorithmPreorder::visit(const statement::TryStatementSyntax& node, bool callFirst /*= true*/){
#ifdef DEBUG_PREORDER
  std::cout << "Rec. run: " << (unsigned int)&node << " " << node.getId() << " " << Common::toString(node.getNodeKind()) << std::endl;
#endif
  if (safeMode || visitCrossEdgeTree) {
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

void AlgorithmPreorder::visitAllEdges(const statement::UnsafeStatementSyntax& node, bool callFirst /*= true*/){
  visitAllEdges(dynamic_cast<const statement::StatementSyntax&>(node),false);

  std::list<Visitor*>::iterator itVisitors;

  const base::Base* genNodePtr;
  // edge: Block
  genNodePtr = node.getBlock() ;
  if (genNodePtr) {
    const statement::BlockSyntax& endNodeRef = dynamic_cast<const statement::BlockSyntax&>(*genNodePtr);
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitUnsafeStatementSyntax_Block(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;

    if ((!fact->getIsFilterTurnedOn() && !visitFilteredEdge) || (fact->getFilterState(endNodeRef.getId()) == Filter::NotFiltered) || (!originalFilterState && visitFilteredEdge)) {
      endNodeRef.accept(*this);
    }
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitEndUnsafeStatementSyntax_Block(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;
  }
}

void AlgorithmPreorder::visit(const statement::UnsafeStatementSyntax& node, bool callFirst /*= true*/){
#ifdef DEBUG_PREORDER
  std::cout << "Rec. run: " << (unsigned int)&node << " " << node.getId() << " " << Common::toString(node.getNodeKind()) << std::endl;
#endif
  if (safeMode || visitCrossEdgeTree) {
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

void AlgorithmPreorder::visitAllEdges(const statement::UsingStatementSyntax& node, bool callFirst /*= true*/){
  visitAllEdges(dynamic_cast<const statement::StatementSyntax&>(node),false);

  std::list<Visitor*>::iterator itVisitors;

  const base::Base* genNodePtr;
  // edge: Declaration
  genNodePtr = node.getDeclaration() ;
  if (genNodePtr) {
    const structure::VariableDeclarationSyntax& endNodeRef = dynamic_cast<const structure::VariableDeclarationSyntax&>(*genNodePtr);
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitUsingStatementSyntax_Declaration(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;

    if ((!fact->getIsFilterTurnedOn() && !visitFilteredEdge) || (fact->getFilterState(endNodeRef.getId()) == Filter::NotFiltered) || (!originalFilterState && visitFilteredEdge)) {
      endNodeRef.accept(*this);
    }
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitEndUsingStatementSyntax_Declaration(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;
  }

  // edge: Expression
  genNodePtr = node.getExpression() ;
  if (genNodePtr) {
    const expression::ExpressionSyntax& endNodeRef = dynamic_cast<const expression::ExpressionSyntax&>(*genNodePtr);
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitUsingStatementSyntax_Expression(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;

    if ((!fact->getIsFilterTurnedOn() && !visitFilteredEdge) || (fact->getFilterState(endNodeRef.getId()) == Filter::NotFiltered) || (!originalFilterState && visitFilteredEdge)) {
      endNodeRef.accept(*this);
    }
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitEndUsingStatementSyntax_Expression(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;
  }

  // edge: Statement
  genNodePtr = node.getStatement() ;
  if (genNodePtr) {
    const statement::StatementSyntax& endNodeRef = dynamic_cast<const statement::StatementSyntax&>(*genNodePtr);
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitUsingStatementSyntax_Statement(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;

    if ((!fact->getIsFilterTurnedOn() && !visitFilteredEdge) || (fact->getFilterState(endNodeRef.getId()) == Filter::NotFiltered) || (!originalFilterState && visitFilteredEdge)) {
      endNodeRef.accept(*this);
    }
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitEndUsingStatementSyntax_Statement(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;
  }
}

void AlgorithmPreorder::visit(const statement::UsingStatementSyntax& node, bool callFirst /*= true*/){
#ifdef DEBUG_PREORDER
  std::cout << "Rec. run: " << (unsigned int)&node << " " << node.getId() << " " << Common::toString(node.getNodeKind()) << std::endl;
#endif
  if (safeMode || visitCrossEdgeTree) {
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

void AlgorithmPreorder::visitAllEdges(const statement::WhileStatementSyntax& node, bool callFirst /*= true*/){
  visitAllEdges(dynamic_cast<const statement::StatementSyntax&>(node),false);

  std::list<Visitor*>::iterator itVisitors;

  const base::Base* genNodePtr;
  // edge: Condition
  genNodePtr = node.getCondition() ;
  if (genNodePtr) {
    const expression::ExpressionSyntax& endNodeRef = dynamic_cast<const expression::ExpressionSyntax&>(*genNodePtr);
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitWhileStatementSyntax_Condition(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;

    if ((!fact->getIsFilterTurnedOn() && !visitFilteredEdge) || (fact->getFilterState(endNodeRef.getId()) == Filter::NotFiltered) || (!originalFilterState && visitFilteredEdge)) {
      endNodeRef.accept(*this);
    }
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitEndWhileStatementSyntax_Condition(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;
  }

  // edge: Statement
  genNodePtr = node.getStatement() ;
  if (genNodePtr) {
    const statement::StatementSyntax& endNodeRef = dynamic_cast<const statement::StatementSyntax&>(*genNodePtr);
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitWhileStatementSyntax_Statement(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;

    if ((!fact->getIsFilterTurnedOn() && !visitFilteredEdge) || (fact->getFilterState(endNodeRef.getId()) == Filter::NotFiltered) || (!originalFilterState && visitFilteredEdge)) {
      endNodeRef.accept(*this);
    }
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitEndWhileStatementSyntax_Statement(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;
  }
}

void AlgorithmPreorder::visit(const statement::WhileStatementSyntax& node, bool callFirst /*= true*/){
#ifdef DEBUG_PREORDER
  std::cout << "Rec. run: " << (unsigned int)&node << " " << node.getId() << " " << Common::toString(node.getNodeKind()) << std::endl;
#endif
  if (safeMode || visitCrossEdgeTree) {
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

void AlgorithmPreorder::visitAllEdges(const statement::YieldStatementSyntax& node, bool callFirst /*= true*/){
  visitAllEdges(dynamic_cast<const statement::StatementSyntax&>(node),false);

  std::list<Visitor*>::iterator itVisitors;

  const base::Base* genNodePtr;
  // edge: Expression
  genNodePtr = node.getExpression() ;
  if (genNodePtr) {
    const expression::ExpressionSyntax& endNodeRef = dynamic_cast<const expression::ExpressionSyntax&>(*genNodePtr);
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitYieldStatementSyntax_Expression(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;

    if ((!fact->getIsFilterTurnedOn() && !visitFilteredEdge) || (fact->getFilterState(endNodeRef.getId()) == Filter::NotFiltered) || (!originalFilterState && visitFilteredEdge)) {
      endNodeRef.accept(*this);
    }
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitEndYieldStatementSyntax_Expression(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;
  }
}

void AlgorithmPreorder::visit(const statement::YieldStatementSyntax& node, bool callFirst /*= true*/){
#ifdef DEBUG_PREORDER
  std::cout << "Rec. run: " << (unsigned int)&node << " " << node.getId() << " " << Common::toString(node.getNodeKind()) << std::endl;
#endif
  if (safeMode || visitCrossEdgeTree) {
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

void AlgorithmPreorder::visitAllEdges(const structure::AccessorDeclarationSyntax& node, bool callFirst /*= true*/){
  visitAllEdges(dynamic_cast<const base::Positioned&>(node),false);

  std::list<Visitor*>::iterator itVisitors;

  // edge: AttributeLists
  for (ListIterator<structure::AttributeListSyntax> it = node.getAttributeListsListIteratorBegin(); it != node.getAttributeListsListIteratorEnd(); ++it) {
    const structure::AttributeListSyntax& endNodeRef = *it;
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitAccessorDeclarationSyntax_AttributeLists(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;

    if ((!fact->getIsFilterTurnedOn() && !visitFilteredEdge) || (fact->getFilterState(endNodeRef.getId()) == Filter::NotFiltered) || (!originalFilterState && visitFilteredEdge)) {
      endNodeRef.accept(*this);
    }
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitEndAccessorDeclarationSyntax_AttributeLists(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;
  }

  const base::Base* genNodePtr;
  // edge: Body
  genNodePtr = node.getBody() ;
  if (genNodePtr) {
    const statement::BlockSyntax& endNodeRef = dynamic_cast<const statement::BlockSyntax&>(*genNodePtr);
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitAccessorDeclarationSyntax_Body(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;

    if ((!fact->getIsFilterTurnedOn() && !visitFilteredEdge) || (fact->getFilterState(endNodeRef.getId()) == Filter::NotFiltered) || (!originalFilterState && visitFilteredEdge)) {
      endNodeRef.accept(*this);
    }
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitEndAccessorDeclarationSyntax_Body(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;
  }
}

void AlgorithmPreorder::visit(const structure::AccessorDeclarationSyntax& node, bool callFirst /*= true*/){
#ifdef DEBUG_PREORDER
  std::cout << "Rec. run: " << (unsigned int)&node << " " << node.getId() << " " << Common::toString(node.getNodeKind()) << std::endl;
#endif
  if (safeMode || visitCrossEdgeTree) {
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

void AlgorithmPreorder::visitAllEdges(const structure::AccessorListSyntax& node, bool callFirst /*= true*/){
  visitAllEdges(dynamic_cast<const base::Positioned&>(node),false);

  std::list<Visitor*>::iterator itVisitors;

  // edge: Accessors
  for (ListIterator<structure::AccessorDeclarationSyntax> it = node.getAccessorsListIteratorBegin(); it != node.getAccessorsListIteratorEnd(); ++it) {
    const structure::AccessorDeclarationSyntax& endNodeRef = *it;
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitAccessorListSyntax_Accessors(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;

    if ((!fact->getIsFilterTurnedOn() && !visitFilteredEdge) || (fact->getFilterState(endNodeRef.getId()) == Filter::NotFiltered) || (!originalFilterState && visitFilteredEdge)) {
      endNodeRef.accept(*this);
    }
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitEndAccessorListSyntax_Accessors(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;
  }
}

void AlgorithmPreorder::visit(const structure::AccessorListSyntax& node, bool callFirst /*= true*/){
#ifdef DEBUG_PREORDER
  std::cout << "Rec. run: " << (unsigned int)&node << " " << node.getId() << " " << Common::toString(node.getNodeKind()) << std::endl;
#endif
  if (safeMode || visitCrossEdgeTree) {
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

void AlgorithmPreorder::visitAllEdges(const structure::AnonymousObjectMemberDeclaratorSyntax& node, bool callFirst /*= true*/){
  visitAllEdges(dynamic_cast<const base::Positioned&>(node),false);

  std::list<Visitor*>::iterator itVisitors;

  const base::Base* genNodePtr;
  // edge: Expression
  genNodePtr = node.getExpression() ;
  if (genNodePtr) {
    const expression::ExpressionSyntax& endNodeRef = dynamic_cast<const expression::ExpressionSyntax&>(*genNodePtr);
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitAnonymousObjectMemberDeclaratorSyntax_Expression(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;

    if ((!fact->getIsFilterTurnedOn() && !visitFilteredEdge) || (fact->getFilterState(endNodeRef.getId()) == Filter::NotFiltered) || (!originalFilterState && visitFilteredEdge)) {
      endNodeRef.accept(*this);
    }
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitEndAnonymousObjectMemberDeclaratorSyntax_Expression(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;
  }

  // edge: NameEquals
  genNodePtr = node.getNameEquals() ;
  if (genNodePtr) {
    const structure::NameEqualsSyntax& endNodeRef = dynamic_cast<const structure::NameEqualsSyntax&>(*genNodePtr);
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitAnonymousObjectMemberDeclaratorSyntax_NameEquals(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;

    if ((!fact->getIsFilterTurnedOn() && !visitFilteredEdge) || (fact->getFilterState(endNodeRef.getId()) == Filter::NotFiltered) || (!originalFilterState && visitFilteredEdge)) {
      endNodeRef.accept(*this);
    }
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitEndAnonymousObjectMemberDeclaratorSyntax_NameEquals(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;
  }
}

void AlgorithmPreorder::visit(const structure::AnonymousObjectMemberDeclaratorSyntax& node, bool callFirst /*= true*/){
#ifdef DEBUG_PREORDER
  std::cout << "Rec. run: " << (unsigned int)&node << " " << node.getId() << " " << Common::toString(node.getNodeKind()) << std::endl;
#endif
  if (safeMode || visitCrossEdgeTree) {
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

void AlgorithmPreorder::visitAllEdges(const structure::ArgumentListSyntax& node, bool callFirst /*= true*/){
  visitAllEdges(dynamic_cast<const structure::BaseArgumentListSyntax&>(node),false);
}

void AlgorithmPreorder::visit(const structure::ArgumentListSyntax& node, bool callFirst /*= true*/){
#ifdef DEBUG_PREORDER
  std::cout << "Rec. run: " << (unsigned int)&node << " " << node.getId() << " " << Common::toString(node.getNodeKind()) << std::endl;
#endif
  if (safeMode || visitCrossEdgeTree) {
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

void AlgorithmPreorder::visitAllEdges(const structure::ArgumentSyntax& node, bool callFirst /*= true*/){
  visitAllEdges(dynamic_cast<const base::Positioned&>(node),false);

  std::list<Visitor*>::iterator itVisitors;

  const base::Base* genNodePtr;
  // edge: Expression
  genNodePtr = node.getExpression() ;
  if (genNodePtr) {
    const expression::ExpressionSyntax& endNodeRef = dynamic_cast<const expression::ExpressionSyntax&>(*genNodePtr);
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitArgumentSyntax_Expression(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;

    if ((!fact->getIsFilterTurnedOn() && !visitFilteredEdge) || (fact->getFilterState(endNodeRef.getId()) == Filter::NotFiltered) || (!originalFilterState && visitFilteredEdge)) {
      endNodeRef.accept(*this);
    }
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitEndArgumentSyntax_Expression(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;
  }

  // edge: NameColon
  genNodePtr = node.getNameColon() ;
  if (genNodePtr) {
    const structure::NameColonSyntax& endNodeRef = dynamic_cast<const structure::NameColonSyntax&>(*genNodePtr);
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitArgumentSyntax_NameColon(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;

    if ((!fact->getIsFilterTurnedOn() && !visitFilteredEdge) || (fact->getFilterState(endNodeRef.getId()) == Filter::NotFiltered) || (!originalFilterState && visitFilteredEdge)) {
      endNodeRef.accept(*this);
    }
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitEndArgumentSyntax_NameColon(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;
  }
}

void AlgorithmPreorder::visit(const structure::ArgumentSyntax& node, bool callFirst /*= true*/){
#ifdef DEBUG_PREORDER
  std::cout << "Rec. run: " << (unsigned int)&node << " " << node.getId() << " " << Common::toString(node.getNodeKind()) << std::endl;
#endif
  if (safeMode || visitCrossEdgeTree) {
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

void AlgorithmPreorder::visitAllEdges(const structure::ArrayRankSpecifierSyntax& node, bool callFirst /*= true*/){
  visitAllEdges(dynamic_cast<const base::Positioned&>(node),false);

  std::list<Visitor*>::iterator itVisitors;

  // edge: Sizes
  for (ListIterator<expression::ExpressionSyntax> it = node.getSizesListIteratorBegin(); it != node.getSizesListIteratorEnd(); ++it) {
    const expression::ExpressionSyntax& endNodeRef = *it;
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitArrayRankSpecifierSyntax_Sizes(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;

    if ((!fact->getIsFilterTurnedOn() && !visitFilteredEdge) || (fact->getFilterState(endNodeRef.getId()) == Filter::NotFiltered) || (!originalFilterState && visitFilteredEdge)) {
      endNodeRef.accept(*this);
    }
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitEndArrayRankSpecifierSyntax_Sizes(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;
  }
}

void AlgorithmPreorder::visit(const structure::ArrayRankSpecifierSyntax& node, bool callFirst /*= true*/){
#ifdef DEBUG_PREORDER
  std::cout << "Rec. run: " << (unsigned int)&node << " " << node.getId() << " " << Common::toString(node.getNodeKind()) << std::endl;
#endif
  if (safeMode || visitCrossEdgeTree) {
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

void AlgorithmPreorder::visitAllEdges(const structure::ArrowExpressionClauseSyntax& node, bool callFirst /*= true*/){
  visitAllEdges(dynamic_cast<const base::Positioned&>(node),false);

  std::list<Visitor*>::iterator itVisitors;

  const base::Base* genNodePtr;
  // edge: Expression
  genNodePtr = node.getExpression() ;
  if (genNodePtr) {
    const expression::ExpressionSyntax& endNodeRef = dynamic_cast<const expression::ExpressionSyntax&>(*genNodePtr);
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitArrowExpressionClauseSyntax_Expression(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;

    if ((!fact->getIsFilterTurnedOn() && !visitFilteredEdge) || (fact->getFilterState(endNodeRef.getId()) == Filter::NotFiltered) || (!originalFilterState && visitFilteredEdge)) {
      endNodeRef.accept(*this);
    }
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitEndArrowExpressionClauseSyntax_Expression(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;
  }
}

void AlgorithmPreorder::visit(const structure::ArrowExpressionClauseSyntax& node, bool callFirst /*= true*/){
#ifdef DEBUG_PREORDER
  std::cout << "Rec. run: " << (unsigned int)&node << " " << node.getId() << " " << Common::toString(node.getNodeKind()) << std::endl;
#endif
  if (safeMode || visitCrossEdgeTree) {
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

void AlgorithmPreorder::visitAllEdges(const structure::AttributeArgumentListSyntax& node, bool callFirst /*= true*/){
  visitAllEdges(dynamic_cast<const base::Positioned&>(node),false);

  std::list<Visitor*>::iterator itVisitors;

  // edge: Arguments
  for (ListIterator<structure::AttributeArgumentSyntax> it = node.getArgumentsListIteratorBegin(); it != node.getArgumentsListIteratorEnd(); ++it) {
    const structure::AttributeArgumentSyntax& endNodeRef = *it;
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitAttributeArgumentListSyntax_Arguments(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;

    if ((!fact->getIsFilterTurnedOn() && !visitFilteredEdge) || (fact->getFilterState(endNodeRef.getId()) == Filter::NotFiltered) || (!originalFilterState && visitFilteredEdge)) {
      endNodeRef.accept(*this);
    }
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitEndAttributeArgumentListSyntax_Arguments(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;
  }
}

void AlgorithmPreorder::visit(const structure::AttributeArgumentListSyntax& node, bool callFirst /*= true*/){
#ifdef DEBUG_PREORDER
  std::cout << "Rec. run: " << (unsigned int)&node << " " << node.getId() << " " << Common::toString(node.getNodeKind()) << std::endl;
#endif
  if (safeMode || visitCrossEdgeTree) {
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

void AlgorithmPreorder::visitAllEdges(const structure::AttributeArgumentSyntax& node, bool callFirst /*= true*/){
  visitAllEdges(dynamic_cast<const base::Positioned&>(node),false);

  std::list<Visitor*>::iterator itVisitors;

  const base::Base* genNodePtr;
  // edge: Expression
  genNodePtr = node.getExpression() ;
  if (genNodePtr) {
    const expression::ExpressionSyntax& endNodeRef = dynamic_cast<const expression::ExpressionSyntax&>(*genNodePtr);
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitAttributeArgumentSyntax_Expression(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;

    if ((!fact->getIsFilterTurnedOn() && !visitFilteredEdge) || (fact->getFilterState(endNodeRef.getId()) == Filter::NotFiltered) || (!originalFilterState && visitFilteredEdge)) {
      endNodeRef.accept(*this);
    }
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitEndAttributeArgumentSyntax_Expression(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;
  }

  // edge: NameColon
  genNodePtr = node.getNameColon() ;
  if (genNodePtr) {
    const structure::NameColonSyntax& endNodeRef = dynamic_cast<const structure::NameColonSyntax&>(*genNodePtr);
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitAttributeArgumentSyntax_NameColon(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;

    if ((!fact->getIsFilterTurnedOn() && !visitFilteredEdge) || (fact->getFilterState(endNodeRef.getId()) == Filter::NotFiltered) || (!originalFilterState && visitFilteredEdge)) {
      endNodeRef.accept(*this);
    }
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitEndAttributeArgumentSyntax_NameColon(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;
  }

  // edge: NameEquals
  genNodePtr = node.getNameEquals() ;
  if (genNodePtr) {
    const structure::NameEqualsSyntax& endNodeRef = dynamic_cast<const structure::NameEqualsSyntax&>(*genNodePtr);
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitAttributeArgumentSyntax_NameEquals(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;

    if ((!fact->getIsFilterTurnedOn() && !visitFilteredEdge) || (fact->getFilterState(endNodeRef.getId()) == Filter::NotFiltered) || (!originalFilterState && visitFilteredEdge)) {
      endNodeRef.accept(*this);
    }
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitEndAttributeArgumentSyntax_NameEquals(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;
  }
}

void AlgorithmPreorder::visit(const structure::AttributeArgumentSyntax& node, bool callFirst /*= true*/){
#ifdef DEBUG_PREORDER
  std::cout << "Rec. run: " << (unsigned int)&node << " " << node.getId() << " " << Common::toString(node.getNodeKind()) << std::endl;
#endif
  if (safeMode || visitCrossEdgeTree) {
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

void AlgorithmPreorder::visitAllEdges(const structure::AttributeListSyntax& node, bool callFirst /*= true*/){
  visitAllEdges(dynamic_cast<const base::Positioned&>(node),false);

  std::list<Visitor*>::iterator itVisitors;

  // edge: Attributes
  for (ListIterator<structure::AttributeSyntax> it = node.getAttributesListIteratorBegin(); it != node.getAttributesListIteratorEnd(); ++it) {
    const structure::AttributeSyntax& endNodeRef = *it;
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitAttributeListSyntax_Attributes(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;

    if ((!fact->getIsFilterTurnedOn() && !visitFilteredEdge) || (fact->getFilterState(endNodeRef.getId()) == Filter::NotFiltered) || (!originalFilterState && visitFilteredEdge)) {
      endNodeRef.accept(*this);
    }
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitEndAttributeListSyntax_Attributes(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;
  }

  const base::Base* genNodePtr;
  // edge: Target
  genNodePtr = node.getTarget() ;
  if (genNodePtr) {
    const structure::AttributeTargetSpecifierSyntax& endNodeRef = dynamic_cast<const structure::AttributeTargetSpecifierSyntax&>(*genNodePtr);
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitAttributeListSyntax_Target(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;

    if ((!fact->getIsFilterTurnedOn() && !visitFilteredEdge) || (fact->getFilterState(endNodeRef.getId()) == Filter::NotFiltered) || (!originalFilterState && visitFilteredEdge)) {
      endNodeRef.accept(*this);
    }
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitEndAttributeListSyntax_Target(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;
  }
}

void AlgorithmPreorder::visit(const structure::AttributeListSyntax& node, bool callFirst /*= true*/){
#ifdef DEBUG_PREORDER
  std::cout << "Rec. run: " << (unsigned int)&node << " " << node.getId() << " " << Common::toString(node.getNodeKind()) << std::endl;
#endif
  if (safeMode || visitCrossEdgeTree) {
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

void AlgorithmPreorder::visitAllEdges(const structure::AttributeSyntax& node, bool callFirst /*= true*/){
  visitAllEdges(dynamic_cast<const base::Positioned&>(node),false);

  std::list<Visitor*>::iterator itVisitors;

  const base::Base* genNodePtr;
  // edge: ArgumentList
  genNodePtr = node.getArgumentList() ;
  if (genNodePtr) {
    const structure::AttributeArgumentListSyntax& endNodeRef = dynamic_cast<const structure::AttributeArgumentListSyntax&>(*genNodePtr);
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitAttributeSyntax_ArgumentList(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;

    if ((!fact->getIsFilterTurnedOn() && !visitFilteredEdge) || (fact->getFilterState(endNodeRef.getId()) == Filter::NotFiltered) || (!originalFilterState && visitFilteredEdge)) {
      endNodeRef.accept(*this);
    }
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitEndAttributeSyntax_ArgumentList(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;
  }

  // edge: Name
  genNodePtr = node.getName() ;
  if (genNodePtr) {
    const expression::NameSyntax& endNodeRef = dynamic_cast<const expression::NameSyntax&>(*genNodePtr);
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitAttributeSyntax_Name(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;

    if ((!fact->getIsFilterTurnedOn() && !visitFilteredEdge) || (fact->getFilterState(endNodeRef.getId()) == Filter::NotFiltered) || (!originalFilterState && visitFilteredEdge)) {
      endNodeRef.accept(*this);
    }
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitEndAttributeSyntax_Name(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;
  }
}

void AlgorithmPreorder::visit(const structure::AttributeSyntax& node, bool callFirst /*= true*/){
#ifdef DEBUG_PREORDER
  std::cout << "Rec. run: " << (unsigned int)&node << " " << node.getId() << " " << Common::toString(node.getNodeKind()) << std::endl;
#endif
  if (safeMode || visitCrossEdgeTree) {
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

void AlgorithmPreorder::visitAllEdges(const structure::AttributeTargetSpecifierSyntax& node, bool callFirst /*= true*/){
  visitAllEdges(dynamic_cast<const base::Positioned&>(node),false);
}

void AlgorithmPreorder::visit(const structure::AttributeTargetSpecifierSyntax& node, bool callFirst /*= true*/){
#ifdef DEBUG_PREORDER
  std::cout << "Rec. run: " << (unsigned int)&node << " " << node.getId() << " " << Common::toString(node.getNodeKind()) << std::endl;
#endif
  if (safeMode || visitCrossEdgeTree) {
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

void AlgorithmPreorder::visitAllEdges(const structure::BaseArgumentListSyntax& node, bool callFirst /*= true*/){
  visitAllEdges(dynamic_cast<const base::Positioned&>(node),false);

  std::list<Visitor*>::iterator itVisitors;

  // edge: Arguments
  for (ListIterator<structure::ArgumentSyntax> it = node.getArgumentsListIteratorBegin(); it != node.getArgumentsListIteratorEnd(); ++it) {
    const structure::ArgumentSyntax& endNodeRef = *it;
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitBaseArgumentListSyntax_Arguments(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;

    if ((!fact->getIsFilterTurnedOn() && !visitFilteredEdge) || (fact->getFilterState(endNodeRef.getId()) == Filter::NotFiltered) || (!originalFilterState && visitFilteredEdge)) {
      endNodeRef.accept(*this);
    }
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitEndBaseArgumentListSyntax_Arguments(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;
  }
}

void AlgorithmPreorder::visitAllEdges(const structure::BaseCrefParameterListSyntax& node, bool callFirst /*= true*/){
  visitAllEdges(dynamic_cast<const base::Positioned&>(node),false);

  std::list<Visitor*>::iterator itVisitors;

  // edge: Parameters
  for (ListIterator<structure::CrefParameterSyntax> it = node.getParametersListIteratorBegin(); it != node.getParametersListIteratorEnd(); ++it) {
    const structure::CrefParameterSyntax& endNodeRef = *it;
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitBaseCrefParameterListSyntax_Parameters(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;

    if ((!fact->getIsFilterTurnedOn() && !visitFilteredEdge) || (fact->getFilterState(endNodeRef.getId()) == Filter::NotFiltered) || (!originalFilterState && visitFilteredEdge)) {
      endNodeRef.accept(*this);
    }
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitEndBaseCrefParameterListSyntax_Parameters(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;
  }
}

void AlgorithmPreorder::visitAllEdges(const structure::BaseFieldDeclarationSyntax& node, bool callFirst /*= true*/){
  visitAllEdges(dynamic_cast<const structure::MemberDeclarationSyntax&>(node),false);

  std::list<Visitor*>::iterator itVisitors;

  // edge: AttributeLists
  for (ListIterator<structure::AttributeListSyntax> it = node.getAttributeListsListIteratorBegin(); it != node.getAttributeListsListIteratorEnd(); ++it) {
    const structure::AttributeListSyntax& endNodeRef = *it;
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitBaseFieldDeclarationSyntax_AttributeLists(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;

    if ((!fact->getIsFilterTurnedOn() && !visitFilteredEdge) || (fact->getFilterState(endNodeRef.getId()) == Filter::NotFiltered) || (!originalFilterState && visitFilteredEdge)) {
      endNodeRef.accept(*this);
    }
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitEndBaseFieldDeclarationSyntax_AttributeLists(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;
  }

  const base::Base* genNodePtr;
  // edge: Declaration
  genNodePtr = node.getDeclaration() ;
  if (genNodePtr) {
    const structure::VariableDeclarationSyntax& endNodeRef = dynamic_cast<const structure::VariableDeclarationSyntax&>(*genNodePtr);
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitBaseFieldDeclarationSyntax_Declaration(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;

    if ((!fact->getIsFilterTurnedOn() && !visitFilteredEdge) || (fact->getFilterState(endNodeRef.getId()) == Filter::NotFiltered) || (!originalFilterState && visitFilteredEdge)) {
      endNodeRef.accept(*this);
    }
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitEndBaseFieldDeclarationSyntax_Declaration(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;
  }
}

void AlgorithmPreorder::visitAllEdges(const structure::BaseListSyntax& node, bool callFirst /*= true*/){
  visitAllEdges(dynamic_cast<const base::Positioned&>(node),false);

  std::list<Visitor*>::iterator itVisitors;

  // edge: Types
  for (ListIterator<structure::BaseTypeSyntax> it = node.getTypesListIteratorBegin(); it != node.getTypesListIteratorEnd(); ++it) {
    const structure::BaseTypeSyntax& endNodeRef = *it;
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitBaseListSyntax_Types(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;

    if ((!fact->getIsFilterTurnedOn() && !visitFilteredEdge) || (fact->getFilterState(endNodeRef.getId()) == Filter::NotFiltered) || (!originalFilterState && visitFilteredEdge)) {
      endNodeRef.accept(*this);
    }
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitEndBaseListSyntax_Types(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;
  }
}

void AlgorithmPreorder::visit(const structure::BaseListSyntax& node, bool callFirst /*= true*/){
#ifdef DEBUG_PREORDER
  std::cout << "Rec. run: " << (unsigned int)&node << " " << node.getId() << " " << Common::toString(node.getNodeKind()) << std::endl;
#endif
  if (safeMode || visitCrossEdgeTree) {
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

void AlgorithmPreorder::visitAllEdges(const structure::BaseMethodDeclarationSyntax& node, bool callFirst /*= true*/){
  visitAllEdges(dynamic_cast<const structure::MemberDeclarationSyntax&>(node),false);

  std::list<Visitor*>::iterator itVisitors;

  // edge: AccessedEnumMembers
  for (ListIterator<structure::EnumMemberDeclarationSyntax> it = node.getAccessedEnumMembersListIteratorBegin(); it != node.getAccessedEnumMembersListIteratorEnd(); ++it) {
    const structure::EnumMemberDeclarationSyntax& endNodeRef = *it;
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitBaseMethodDeclarationSyntax_AccessedEnumMembers(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;

    if ((!fact->getIsFilterTurnedOn() && !visitFilteredEdge) || (fact->getFilterState(endNodeRef.getId()) == Filter::NotFiltered) || (!originalFilterState && visitFilteredEdge)) {
      if (apRoot) {
        if (visitCrossEdgeTree) {
          unvisitedNodes[endNodeRef.getId()] = true;
        }
      }
      if (traversaldCrossEdges[edkBaseMethodDeclarationSyntax_AccessedEnumMembers]) {
        endNodeRef.accept(*this);
      }
    }
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitEndBaseMethodDeclarationSyntax_AccessedEnumMembers(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;
  }

  // edge: AttributeLists
  for (ListIterator<structure::AttributeListSyntax> it = node.getAttributeListsListIteratorBegin(); it != node.getAttributeListsListIteratorEnd(); ++it) {
    const structure::AttributeListSyntax& endNodeRef = *it;
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitBaseMethodDeclarationSyntax_AttributeLists(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;

    if ((!fact->getIsFilterTurnedOn() && !visitFilteredEdge) || (fact->getFilterState(endNodeRef.getId()) == Filter::NotFiltered) || (!originalFilterState && visitFilteredEdge)) {
      endNodeRef.accept(*this);
    }
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitEndBaseMethodDeclarationSyntax_AttributeLists(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;
  }

  const base::Base* genNodePtr;
  // edge: Body
  genNodePtr = node.getBody() ;
  if (genNodePtr) {
    const statement::BlockSyntax& endNodeRef = dynamic_cast<const statement::BlockSyntax&>(*genNodePtr);
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitBaseMethodDeclarationSyntax_Body(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;

    if ((!fact->getIsFilterTurnedOn() && !visitFilteredEdge) || (fact->getFilterState(endNodeRef.getId()) == Filter::NotFiltered) || (!originalFilterState && visitFilteredEdge)) {
      endNodeRef.accept(*this);
    }
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitEndBaseMethodDeclarationSyntax_Body(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;
  }

  // edge: ParameterList
  genNodePtr = node.getParameterList() ;
  if (genNodePtr) {
    const structure::ParameterListSyntax& endNodeRef = dynamic_cast<const structure::ParameterListSyntax&>(*genNodePtr);
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitBaseMethodDeclarationSyntax_ParameterList(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;

    if ((!fact->getIsFilterTurnedOn() && !visitFilteredEdge) || (fact->getFilterState(endNodeRef.getId()) == Filter::NotFiltered) || (!originalFilterState && visitFilteredEdge)) {
      endNodeRef.accept(*this);
    }
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitEndBaseMethodDeclarationSyntax_ParameterList(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;
  }
}

void AlgorithmPreorder::visitAllEdges(const structure::BaseParameterListSyntax& node, bool callFirst /*= true*/){
  visitAllEdges(dynamic_cast<const base::Positioned&>(node),false);

  std::list<Visitor*>::iterator itVisitors;

  // edge: Parameters
  for (ListIterator<structure::ParameterSyntax> it = node.getParametersListIteratorBegin(); it != node.getParametersListIteratorEnd(); ++it) {
    const structure::ParameterSyntax& endNodeRef = *it;
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitBaseParameterListSyntax_Parameters(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;

    if ((!fact->getIsFilterTurnedOn() && !visitFilteredEdge) || (fact->getFilterState(endNodeRef.getId()) == Filter::NotFiltered) || (!originalFilterState && visitFilteredEdge)) {
      endNodeRef.accept(*this);
    }
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitEndBaseParameterListSyntax_Parameters(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;
  }
}

void AlgorithmPreorder::visitAllEdges(const structure::BasePropertyDeclarationSyntax& node, bool callFirst /*= true*/){
  visitAllEdges(dynamic_cast<const structure::MemberDeclarationSyntax&>(node),false);

  std::list<Visitor*>::iterator itVisitors;

  const base::Base* genNodePtr;
  // edge: AccessorList
  genNodePtr = node.getAccessorList() ;
  if (genNodePtr) {
    const structure::AccessorListSyntax& endNodeRef = dynamic_cast<const structure::AccessorListSyntax&>(*genNodePtr);
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitBasePropertyDeclarationSyntax_AccessorList(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;

    if ((!fact->getIsFilterTurnedOn() && !visitFilteredEdge) || (fact->getFilterState(endNodeRef.getId()) == Filter::NotFiltered) || (!originalFilterState && visitFilteredEdge)) {
      endNodeRef.accept(*this);
    }
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitEndBasePropertyDeclarationSyntax_AccessorList(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;
  }

  // edge: AttributeLists
  for (ListIterator<structure::AttributeListSyntax> it = node.getAttributeListsListIteratorBegin(); it != node.getAttributeListsListIteratorEnd(); ++it) {
    const structure::AttributeListSyntax& endNodeRef = *it;
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitBasePropertyDeclarationSyntax_AttributeLists(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;

    if ((!fact->getIsFilterTurnedOn() && !visitFilteredEdge) || (fact->getFilterState(endNodeRef.getId()) == Filter::NotFiltered) || (!originalFilterState && visitFilteredEdge)) {
      endNodeRef.accept(*this);
    }
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitEndBasePropertyDeclarationSyntax_AttributeLists(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;
  }

  // edge: ExplicitInterfaceSpecifier
  genNodePtr = node.getExplicitInterfaceSpecifier() ;
  if (genNodePtr) {
    const structure::ExplicitInterfaceSpecifierSyntax& endNodeRef = dynamic_cast<const structure::ExplicitInterfaceSpecifierSyntax&>(*genNodePtr);
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitBasePropertyDeclarationSyntax_ExplicitInterfaceSpecifier(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;

    if ((!fact->getIsFilterTurnedOn() && !visitFilteredEdge) || (fact->getFilterState(endNodeRef.getId()) == Filter::NotFiltered) || (!originalFilterState && visitFilteredEdge)) {
      endNodeRef.accept(*this);
    }
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitEndBasePropertyDeclarationSyntax_ExplicitInterfaceSpecifier(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;
  }

  // edge: Type
  genNodePtr = node.getType() ;
  if (genNodePtr) {
    const expression::TypeSyntax& endNodeRef = dynamic_cast<const expression::TypeSyntax&>(*genNodePtr);
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitBasePropertyDeclarationSyntax_Type(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;

    if ((!fact->getIsFilterTurnedOn() && !visitFilteredEdge) || (fact->getFilterState(endNodeRef.getId()) == Filter::NotFiltered) || (!originalFilterState && visitFilteredEdge)) {
      endNodeRef.accept(*this);
    }
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitEndBasePropertyDeclarationSyntax_Type(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;
  }
}

void AlgorithmPreorder::visitAllEdges(const structure::BaseTypeDeclarationSyntax& node, bool callFirst /*= true*/){
  visitAllEdges(dynamic_cast<const structure::MemberDeclarationSyntax&>(node),false);

  std::list<Visitor*>::iterator itVisitors;

  // edge: AttributeLists
  for (ListIterator<structure::AttributeListSyntax> it = node.getAttributeListsListIteratorBegin(); it != node.getAttributeListsListIteratorEnd(); ++it) {
    const structure::AttributeListSyntax& endNodeRef = *it;
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitBaseTypeDeclarationSyntax_AttributeLists(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;

    if ((!fact->getIsFilterTurnedOn() && !visitFilteredEdge) || (fact->getFilterState(endNodeRef.getId()) == Filter::NotFiltered) || (!originalFilterState && visitFilteredEdge)) {
      endNodeRef.accept(*this);
    }
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitEndBaseTypeDeclarationSyntax_AttributeLists(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;
  }

  const base::Base* genNodePtr;
  // edge: BaseList
  genNodePtr = node.getBaseList() ;
  if (genNodePtr) {
    const structure::BaseListSyntax& endNodeRef = dynamic_cast<const structure::BaseListSyntax&>(*genNodePtr);
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitBaseTypeDeclarationSyntax_BaseList(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;

    if ((!fact->getIsFilterTurnedOn() && !visitFilteredEdge) || (fact->getFilterState(endNodeRef.getId()) == Filter::NotFiltered) || (!originalFilterState && visitFilteredEdge)) {
      endNodeRef.accept(*this);
    }
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitEndBaseTypeDeclarationSyntax_BaseList(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;
  }
}

void AlgorithmPreorder::visitAllEdges(const structure::BaseTypeSyntax& node, bool callFirst /*= true*/){
  visitAllEdges(dynamic_cast<const base::Positioned&>(node),false);

  std::list<Visitor*>::iterator itVisitors;

  const base::Base* genNodePtr;
  // edge: Type
  genNodePtr = node.getType() ;
  if (genNodePtr) {
    const expression::TypeSyntax& endNodeRef = dynamic_cast<const expression::TypeSyntax&>(*genNodePtr);
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitBaseTypeSyntax_Type(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;

    if ((!fact->getIsFilterTurnedOn() && !visitFilteredEdge) || (fact->getFilterState(endNodeRef.getId()) == Filter::NotFiltered) || (!originalFilterState && visitFilteredEdge)) {
      endNodeRef.accept(*this);
    }
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitEndBaseTypeSyntax_Type(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;
  }
}

void AlgorithmPreorder::visitAllEdges(const structure::BracketedArgumentListSyntax& node, bool callFirst /*= true*/){
  visitAllEdges(dynamic_cast<const structure::BaseArgumentListSyntax&>(node),false);
}

void AlgorithmPreorder::visit(const structure::BracketedArgumentListSyntax& node, bool callFirst /*= true*/){
#ifdef DEBUG_PREORDER
  std::cout << "Rec. run: " << (unsigned int)&node << " " << node.getId() << " " << Common::toString(node.getNodeKind()) << std::endl;
#endif
  if (safeMode || visitCrossEdgeTree) {
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

void AlgorithmPreorder::visitAllEdges(const structure::BracketedParameterListSyntax& node, bool callFirst /*= true*/){
  visitAllEdges(dynamic_cast<const structure::BaseParameterListSyntax&>(node),false);
}

void AlgorithmPreorder::visit(const structure::BracketedParameterListSyntax& node, bool callFirst /*= true*/){
#ifdef DEBUG_PREORDER
  std::cout << "Rec. run: " << (unsigned int)&node << " " << node.getId() << " " << Common::toString(node.getNodeKind()) << std::endl;
#endif
  if (safeMode || visitCrossEdgeTree) {
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

void AlgorithmPreorder::visitAllEdges(const structure::CaseSwitchLabelSyntax& node, bool callFirst /*= true*/){
  visitAllEdges(dynamic_cast<const structure::SwitchLabelSyntax&>(node),false);

  std::list<Visitor*>::iterator itVisitors;

  const base::Base* genNodePtr;
  // edge: Value
  genNodePtr = node.getValue() ;
  if (genNodePtr) {
    const expression::ExpressionSyntax& endNodeRef = dynamic_cast<const expression::ExpressionSyntax&>(*genNodePtr);
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitCaseSwitchLabelSyntax_Value(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;

    if ((!fact->getIsFilterTurnedOn() && !visitFilteredEdge) || (fact->getFilterState(endNodeRef.getId()) == Filter::NotFiltered) || (!originalFilterState && visitFilteredEdge)) {
      endNodeRef.accept(*this);
    }
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitEndCaseSwitchLabelSyntax_Value(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;
  }
}

void AlgorithmPreorder::visit(const structure::CaseSwitchLabelSyntax& node, bool callFirst /*= true*/){
#ifdef DEBUG_PREORDER
  std::cout << "Rec. run: " << (unsigned int)&node << " " << node.getId() << " " << Common::toString(node.getNodeKind()) << std::endl;
#endif
  if (safeMode || visitCrossEdgeTree) {
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

void AlgorithmPreorder::visitAllEdges(const structure::CatchClauseSyntax& node, bool callFirst /*= true*/){
  visitAllEdges(dynamic_cast<const base::Positioned&>(node),false);

  std::list<Visitor*>::iterator itVisitors;

  const base::Base* genNodePtr;
  // edge: Block
  genNodePtr = node.getBlock() ;
  if (genNodePtr) {
    const statement::BlockSyntax& endNodeRef = dynamic_cast<const statement::BlockSyntax&>(*genNodePtr);
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitCatchClauseSyntax_Block(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;

    if ((!fact->getIsFilterTurnedOn() && !visitFilteredEdge) || (fact->getFilterState(endNodeRef.getId()) == Filter::NotFiltered) || (!originalFilterState && visitFilteredEdge)) {
      endNodeRef.accept(*this);
    }
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitEndCatchClauseSyntax_Block(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;
  }

  // edge: Declaration
  genNodePtr = node.getDeclaration() ;
  if (genNodePtr) {
    const structure::CatchDeclarationSyntax& endNodeRef = dynamic_cast<const structure::CatchDeclarationSyntax&>(*genNodePtr);
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitCatchClauseSyntax_Declaration(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;

    if ((!fact->getIsFilterTurnedOn() && !visitFilteredEdge) || (fact->getFilterState(endNodeRef.getId()) == Filter::NotFiltered) || (!originalFilterState && visitFilteredEdge)) {
      endNodeRef.accept(*this);
    }
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitEndCatchClauseSyntax_Declaration(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;
  }

  // edge: Filter
  genNodePtr = node.getFilter() ;
  if (genNodePtr) {
    const structure::CatchFilterClauseSyntax& endNodeRef = dynamic_cast<const structure::CatchFilterClauseSyntax&>(*genNodePtr);
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitCatchClauseSyntax_Filter(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;

    if ((!fact->getIsFilterTurnedOn() && !visitFilteredEdge) || (fact->getFilterState(endNodeRef.getId()) == Filter::NotFiltered) || (!originalFilterState && visitFilteredEdge)) {
      endNodeRef.accept(*this);
    }
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitEndCatchClauseSyntax_Filter(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;
  }
}

void AlgorithmPreorder::visit(const structure::CatchClauseSyntax& node, bool callFirst /*= true*/){
#ifdef DEBUG_PREORDER
  std::cout << "Rec. run: " << (unsigned int)&node << " " << node.getId() << " " << Common::toString(node.getNodeKind()) << std::endl;
#endif
  if (safeMode || visitCrossEdgeTree) {
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

void AlgorithmPreorder::visitAllEdges(const structure::CatchDeclarationSyntax& node, bool callFirst /*= true*/){
  visitAllEdges(dynamic_cast<const base::Positioned&>(node),false);

  std::list<Visitor*>::iterator itVisitors;

  const base::Base* genNodePtr;
  // edge: Type
  genNodePtr = node.getType() ;
  if (genNodePtr) {
    const expression::TypeSyntax& endNodeRef = dynamic_cast<const expression::TypeSyntax&>(*genNodePtr);
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitCatchDeclarationSyntax_Type(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;

    if ((!fact->getIsFilterTurnedOn() && !visitFilteredEdge) || (fact->getFilterState(endNodeRef.getId()) == Filter::NotFiltered) || (!originalFilterState && visitFilteredEdge)) {
      endNodeRef.accept(*this);
    }
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitEndCatchDeclarationSyntax_Type(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;
  }
}

void AlgorithmPreorder::visit(const structure::CatchDeclarationSyntax& node, bool callFirst /*= true*/){
#ifdef DEBUG_PREORDER
  std::cout << "Rec. run: " << (unsigned int)&node << " " << node.getId() << " " << Common::toString(node.getNodeKind()) << std::endl;
#endif
  if (safeMode || visitCrossEdgeTree) {
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

void AlgorithmPreorder::visitAllEdges(const structure::CatchFilterClauseSyntax& node, bool callFirst /*= true*/){
  visitAllEdges(dynamic_cast<const base::Positioned&>(node),false);

  std::list<Visitor*>::iterator itVisitors;

  const base::Base* genNodePtr;
  // edge: FilterExpression
  genNodePtr = node.getFilterExpression() ;
  if (genNodePtr) {
    const expression::ExpressionSyntax& endNodeRef = dynamic_cast<const expression::ExpressionSyntax&>(*genNodePtr);
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitCatchFilterClauseSyntax_FilterExpression(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;

    if ((!fact->getIsFilterTurnedOn() && !visitFilteredEdge) || (fact->getFilterState(endNodeRef.getId()) == Filter::NotFiltered) || (!originalFilterState && visitFilteredEdge)) {
      endNodeRef.accept(*this);
    }
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitEndCatchFilterClauseSyntax_FilterExpression(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;
  }
}

void AlgorithmPreorder::visit(const structure::CatchFilterClauseSyntax& node, bool callFirst /*= true*/){
#ifdef DEBUG_PREORDER
  std::cout << "Rec. run: " << (unsigned int)&node << " " << node.getId() << " " << Common::toString(node.getNodeKind()) << std::endl;
#endif
  if (safeMode || visitCrossEdgeTree) {
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

void AlgorithmPreorder::visitAllEdges(const structure::ClassDeclarationSyntax& node, bool callFirst /*= true*/){
  visitAllEdges(dynamic_cast<const structure::TypeDeclarationSyntax&>(node),false);
}

void AlgorithmPreorder::visit(const structure::ClassDeclarationSyntax& node, bool callFirst /*= true*/){
#ifdef DEBUG_PREORDER
  std::cout << "Rec. run: " << (unsigned int)&node << " " << node.getId() << " " << Common::toString(node.getNodeKind()) << std::endl;
#endif
  if (safeMode || visitCrossEdgeTree) {
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

void AlgorithmPreorder::visitAllEdges(const structure::ClassOrStructConstraintSyntax& node, bool callFirst /*= true*/){
  visitAllEdges(dynamic_cast<const structure::TypeParameterConstraintSyntax&>(node),false);
}

void AlgorithmPreorder::visit(const structure::ClassOrStructConstraintSyntax& node, bool callFirst /*= true*/){
#ifdef DEBUG_PREORDER
  std::cout << "Rec. run: " << (unsigned int)&node << " " << node.getId() << " " << Common::toString(node.getNodeKind()) << std::endl;
#endif
  if (safeMode || visitCrossEdgeTree) {
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

void AlgorithmPreorder::visitAllEdges(const structure::CompilationUnitSyntax& node, bool callFirst /*= true*/){
  visitAllEdges(dynamic_cast<const base::Positioned&>(node),false);

  std::list<Visitor*>::iterator itVisitors;

  // edge: AttributeLists
  for (ListIterator<structure::AttributeListSyntax> it = node.getAttributeListsListIteratorBegin(); it != node.getAttributeListsListIteratorEnd(); ++it) {
    const structure::AttributeListSyntax& endNodeRef = *it;
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitCompilationUnitSyntax_AttributeLists(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;

    if ((!fact->getIsFilterTurnedOn() && !visitFilteredEdge) || (fact->getFilterState(endNodeRef.getId()) == Filter::NotFiltered) || (!originalFilterState && visitFilteredEdge)) {
      endNodeRef.accept(*this);
    }
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitEndCompilationUnitSyntax_AttributeLists(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;
  }

  // edge: Externs
  for (ListIterator<structure::ExternAliasDirectiveSyntax> it = node.getExternsListIteratorBegin(); it != node.getExternsListIteratorEnd(); ++it) {
    const structure::ExternAliasDirectiveSyntax& endNodeRef = *it;
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitCompilationUnitSyntax_Externs(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;

    if ((!fact->getIsFilterTurnedOn() && !visitFilteredEdge) || (fact->getFilterState(endNodeRef.getId()) == Filter::NotFiltered) || (!originalFilterState && visitFilteredEdge)) {
      endNodeRef.accept(*this);
    }
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitEndCompilationUnitSyntax_Externs(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;
  }

  // edge: Members
  for (ListIterator<structure::MemberDeclarationSyntax> it = node.getMembersListIteratorBegin(); it != node.getMembersListIteratorEnd(); ++it) {
    const structure::MemberDeclarationSyntax& endNodeRef = *it;
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitCompilationUnitSyntax_Members(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;

    if ((!fact->getIsFilterTurnedOn() && !visitFilteredEdge) || (fact->getFilterState(endNodeRef.getId()) == Filter::NotFiltered) || (!originalFilterState && visitFilteredEdge)) {
      endNodeRef.accept(*this);
    }
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitEndCompilationUnitSyntax_Members(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;
  }

  // edge: Usings
  for (ListIterator<structure::UsingDirectiveSyntax> it = node.getUsingsListIteratorBegin(); it != node.getUsingsListIteratorEnd(); ++it) {
    const structure::UsingDirectiveSyntax& endNodeRef = *it;
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitCompilationUnitSyntax_Usings(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;

    if ((!fact->getIsFilterTurnedOn() && !visitFilteredEdge) || (fact->getFilterState(endNodeRef.getId()) == Filter::NotFiltered) || (!originalFilterState && visitFilteredEdge)) {
      endNodeRef.accept(*this);
    }
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitEndCompilationUnitSyntax_Usings(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;
  }
}

void AlgorithmPreorder::visit(const structure::CompilationUnitSyntax& node, bool callFirst /*= true*/){
#ifdef DEBUG_PREORDER
  std::cout << "Rec. run: " << (unsigned int)&node << " " << node.getId() << " " << Common::toString(node.getNodeKind()) << std::endl;
#endif
  if (safeMode || visitCrossEdgeTree) {
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

void AlgorithmPreorder::visitAllEdges(const structure::ConstructorConstraintSyntax& node, bool callFirst /*= true*/){
  visitAllEdges(dynamic_cast<const structure::TypeParameterConstraintSyntax&>(node),false);
}

void AlgorithmPreorder::visit(const structure::ConstructorConstraintSyntax& node, bool callFirst /*= true*/){
#ifdef DEBUG_PREORDER
  std::cout << "Rec. run: " << (unsigned int)&node << " " << node.getId() << " " << Common::toString(node.getNodeKind()) << std::endl;
#endif
  if (safeMode || visitCrossEdgeTree) {
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

void AlgorithmPreorder::visitAllEdges(const structure::ConstructorDeclarationSyntax& node, bool callFirst /*= true*/){
  visitAllEdges(dynamic_cast<const structure::BaseMethodDeclarationSyntax&>(node),false);

  std::list<Visitor*>::iterator itVisitors;

  const base::Base* genNodePtr;
  // edge: Initializer
  genNodePtr = node.getInitializer() ;
  if (genNodePtr) {
    const structure::ConstructorInitializerSyntax& endNodeRef = dynamic_cast<const structure::ConstructorInitializerSyntax&>(*genNodePtr);
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitConstructorDeclarationSyntax_Initializer(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;

    if ((!fact->getIsFilterTurnedOn() && !visitFilteredEdge) || (fact->getFilterState(endNodeRef.getId()) == Filter::NotFiltered) || (!originalFilterState && visitFilteredEdge)) {
      endNodeRef.accept(*this);
    }
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitEndConstructorDeclarationSyntax_Initializer(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;
  }
}

void AlgorithmPreorder::visit(const structure::ConstructorDeclarationSyntax& node, bool callFirst /*= true*/){
#ifdef DEBUG_PREORDER
  std::cout << "Rec. run: " << (unsigned int)&node << " " << node.getId() << " " << Common::toString(node.getNodeKind()) << std::endl;
#endif
  if (safeMode || visitCrossEdgeTree) {
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

void AlgorithmPreorder::visitAllEdges(const structure::ConstructorInitializerSyntax& node, bool callFirst /*= true*/){
  visitAllEdges(dynamic_cast<const base::Positioned&>(node),false);

  std::list<Visitor*>::iterator itVisitors;

  const base::Base* genNodePtr;
  // edge: ArgumentList
  genNodePtr = node.getArgumentList() ;
  if (genNodePtr) {
    const structure::ArgumentListSyntax& endNodeRef = dynamic_cast<const structure::ArgumentListSyntax&>(*genNodePtr);
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitConstructorInitializerSyntax_ArgumentList(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;

    if ((!fact->getIsFilterTurnedOn() && !visitFilteredEdge) || (fact->getFilterState(endNodeRef.getId()) == Filter::NotFiltered) || (!originalFilterState && visitFilteredEdge)) {
      endNodeRef.accept(*this);
    }
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitEndConstructorInitializerSyntax_ArgumentList(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;
  }

  // edge: ConstructorCall
  genNodePtr = node.getConstructorCall() ;
  if (genNodePtr) {
    const structure::ConstructorDeclarationSyntax& endNodeRef = dynamic_cast<const structure::ConstructorDeclarationSyntax&>(*genNodePtr);
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitConstructorInitializerSyntax_ConstructorCall(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;

    if ((!fact->getIsFilterTurnedOn() && !visitFilteredEdge) || (fact->getFilterState(endNodeRef.getId()) == Filter::NotFiltered) || (!originalFilterState && visitFilteredEdge)) {
      if (apRoot) {
        if (visitCrossEdgeTree) {
          unvisitedNodes[endNodeRef.getId()] = true;
        }
      }
      if (traversaldCrossEdges[edkConstructorInitializerSyntax_ConstructorCall]) {
        endNodeRef.accept(*this);
      }
    }
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitEndConstructorInitializerSyntax_ConstructorCall(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;
  }
}

void AlgorithmPreorder::visit(const structure::ConstructorInitializerSyntax& node, bool callFirst /*= true*/){
#ifdef DEBUG_PREORDER
  std::cout << "Rec. run: " << (unsigned int)&node << " " << node.getId() << " " << Common::toString(node.getNodeKind()) << std::endl;
#endif
  if (safeMode || visitCrossEdgeTree) {
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

void AlgorithmPreorder::visitAllEdges(const structure::ConversionOperatorDeclarationSyntax& node, bool callFirst /*= true*/){
  visitAllEdges(dynamic_cast<const structure::BaseMethodDeclarationSyntax&>(node),false);

  std::list<Visitor*>::iterator itVisitors;

  const base::Base* genNodePtr;
  // edge: ExpressionBody
  genNodePtr = node.getExpressionBody() ;
  if (genNodePtr) {
    const structure::ArrowExpressionClauseSyntax& endNodeRef = dynamic_cast<const structure::ArrowExpressionClauseSyntax&>(*genNodePtr);
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitConversionOperatorDeclarationSyntax_ExpressionBody(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;

    if ((!fact->getIsFilterTurnedOn() && !visitFilteredEdge) || (fact->getFilterState(endNodeRef.getId()) == Filter::NotFiltered) || (!originalFilterState && visitFilteredEdge)) {
      endNodeRef.accept(*this);
    }
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitEndConversionOperatorDeclarationSyntax_ExpressionBody(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;
  }

  // edge: Type
  genNodePtr = node.getType() ;
  if (genNodePtr) {
    const expression::TypeSyntax& endNodeRef = dynamic_cast<const expression::TypeSyntax&>(*genNodePtr);
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitConversionOperatorDeclarationSyntax_Type(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;

    if ((!fact->getIsFilterTurnedOn() && !visitFilteredEdge) || (fact->getFilterState(endNodeRef.getId()) == Filter::NotFiltered) || (!originalFilterState && visitFilteredEdge)) {
      endNodeRef.accept(*this);
    }
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitEndConversionOperatorDeclarationSyntax_Type(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;
  }
}

void AlgorithmPreorder::visit(const structure::ConversionOperatorDeclarationSyntax& node, bool callFirst /*= true*/){
#ifdef DEBUG_PREORDER
  std::cout << "Rec. run: " << (unsigned int)&node << " " << node.getId() << " " << Common::toString(node.getNodeKind()) << std::endl;
#endif
  if (safeMode || visitCrossEdgeTree) {
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

void AlgorithmPreorder::visitAllEdges(const structure::ConversionOperatorMemberCrefSyntax& node, bool callFirst /*= true*/){
  visitAllEdges(dynamic_cast<const structure::MemberCrefSyntax&>(node),false);

  std::list<Visitor*>::iterator itVisitors;

  const base::Base* genNodePtr;
  // edge: Parameters
  genNodePtr = node.getParameters() ;
  if (genNodePtr) {
    const structure::CrefParameterListSyntax& endNodeRef = dynamic_cast<const structure::CrefParameterListSyntax&>(*genNodePtr);
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitConversionOperatorMemberCrefSyntax_Parameters(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;

    if ((!fact->getIsFilterTurnedOn() && !visitFilteredEdge) || (fact->getFilterState(endNodeRef.getId()) == Filter::NotFiltered) || (!originalFilterState && visitFilteredEdge)) {
      endNodeRef.accept(*this);
    }
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitEndConversionOperatorMemberCrefSyntax_Parameters(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;
  }

  // edge: Type
  genNodePtr = node.getType() ;
  if (genNodePtr) {
    const expression::TypeSyntax& endNodeRef = dynamic_cast<const expression::TypeSyntax&>(*genNodePtr);
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitConversionOperatorMemberCrefSyntax_Type(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;

    if ((!fact->getIsFilterTurnedOn() && !visitFilteredEdge) || (fact->getFilterState(endNodeRef.getId()) == Filter::NotFiltered) || (!originalFilterState && visitFilteredEdge)) {
      endNodeRef.accept(*this);
    }
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitEndConversionOperatorMemberCrefSyntax_Type(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;
  }
}

void AlgorithmPreorder::visit(const structure::ConversionOperatorMemberCrefSyntax& node, bool callFirst /*= true*/){
#ifdef DEBUG_PREORDER
  std::cout << "Rec. run: " << (unsigned int)&node << " " << node.getId() << " " << Common::toString(node.getNodeKind()) << std::endl;
#endif
  if (safeMode || visitCrossEdgeTree) {
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

void AlgorithmPreorder::visitAllEdges(const structure::CrefBracketedParameterListSyntax& node, bool callFirst /*= true*/){
  visitAllEdges(dynamic_cast<const structure::BaseCrefParameterListSyntax&>(node),false);
}

void AlgorithmPreorder::visit(const structure::CrefBracketedParameterListSyntax& node, bool callFirst /*= true*/){
#ifdef DEBUG_PREORDER
  std::cout << "Rec. run: " << (unsigned int)&node << " " << node.getId() << " " << Common::toString(node.getNodeKind()) << std::endl;
#endif
  if (safeMode || visitCrossEdgeTree) {
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

void AlgorithmPreorder::visitAllEdges(const structure::CrefParameterListSyntax& node, bool callFirst /*= true*/){
  visitAllEdges(dynamic_cast<const structure::BaseCrefParameterListSyntax&>(node),false);
}

void AlgorithmPreorder::visit(const structure::CrefParameterListSyntax& node, bool callFirst /*= true*/){
#ifdef DEBUG_PREORDER
  std::cout << "Rec. run: " << (unsigned int)&node << " " << node.getId() << " " << Common::toString(node.getNodeKind()) << std::endl;
#endif
  if (safeMode || visitCrossEdgeTree) {
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

void AlgorithmPreorder::visitAllEdges(const structure::CrefParameterSyntax& node, bool callFirst /*= true*/){
  visitAllEdges(dynamic_cast<const base::Positioned&>(node),false);

  std::list<Visitor*>::iterator itVisitors;

  const base::Base* genNodePtr;
  // edge: Type
  genNodePtr = node.getType() ;
  if (genNodePtr) {
    const expression::TypeSyntax& endNodeRef = dynamic_cast<const expression::TypeSyntax&>(*genNodePtr);
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitCrefParameterSyntax_Type(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;

    if ((!fact->getIsFilterTurnedOn() && !visitFilteredEdge) || (fact->getFilterState(endNodeRef.getId()) == Filter::NotFiltered) || (!originalFilterState && visitFilteredEdge)) {
      endNodeRef.accept(*this);
    }
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitEndCrefParameterSyntax_Type(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;
  }
}

void AlgorithmPreorder::visit(const structure::CrefParameterSyntax& node, bool callFirst /*= true*/){
#ifdef DEBUG_PREORDER
  std::cout << "Rec. run: " << (unsigned int)&node << " " << node.getId() << " " << Common::toString(node.getNodeKind()) << std::endl;
#endif
  if (safeMode || visitCrossEdgeTree) {
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

void AlgorithmPreorder::visitAllEdges(const structure::CrefSyntax& node, bool callFirst /*= true*/){
  visitAllEdges(dynamic_cast<const base::Positioned&>(node),false);
}

void AlgorithmPreorder::visitAllEdges(const structure::DefaultSwitchLabelSyntax& node, bool callFirst /*= true*/){
  visitAllEdges(dynamic_cast<const structure::SwitchLabelSyntax&>(node),false);
}

void AlgorithmPreorder::visit(const structure::DefaultSwitchLabelSyntax& node, bool callFirst /*= true*/){
#ifdef DEBUG_PREORDER
  std::cout << "Rec. run: " << (unsigned int)&node << " " << node.getId() << " " << Common::toString(node.getNodeKind()) << std::endl;
#endif
  if (safeMode || visitCrossEdgeTree) {
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

void AlgorithmPreorder::visitAllEdges(const structure::DelegateDeclarationSyntax& node, bool callFirst /*= true*/){
  visitAllEdges(dynamic_cast<const structure::MemberDeclarationSyntax&>(node),false);

  std::list<Visitor*>::iterator itVisitors;

  // edge: AttributeLists
  for (ListIterator<structure::AttributeListSyntax> it = node.getAttributeListsListIteratorBegin(); it != node.getAttributeListsListIteratorEnd(); ++it) {
    const structure::AttributeListSyntax& endNodeRef = *it;
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitDelegateDeclarationSyntax_AttributeLists(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;

    if ((!fact->getIsFilterTurnedOn() && !visitFilteredEdge) || (fact->getFilterState(endNodeRef.getId()) == Filter::NotFiltered) || (!originalFilterState && visitFilteredEdge)) {
      endNodeRef.accept(*this);
    }
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitEndDelegateDeclarationSyntax_AttributeLists(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;
  }

  // edge: ConstraintClauses
  for (ListIterator<structure::TypeParameterConstraintClauseSyntax> it = node.getConstraintClausesListIteratorBegin(); it != node.getConstraintClausesListIteratorEnd(); ++it) {
    const structure::TypeParameterConstraintClauseSyntax& endNodeRef = *it;
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitDelegateDeclarationSyntax_ConstraintClauses(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;

    if ((!fact->getIsFilterTurnedOn() && !visitFilteredEdge) || (fact->getFilterState(endNodeRef.getId()) == Filter::NotFiltered) || (!originalFilterState && visitFilteredEdge)) {
      endNodeRef.accept(*this);
    }
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitEndDelegateDeclarationSyntax_ConstraintClauses(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;
  }

  const base::Base* genNodePtr;
  // edge: ParameterList
  genNodePtr = node.getParameterList() ;
  if (genNodePtr) {
    const structure::ParameterListSyntax& endNodeRef = dynamic_cast<const structure::ParameterListSyntax&>(*genNodePtr);
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitDelegateDeclarationSyntax_ParameterList(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;

    if ((!fact->getIsFilterTurnedOn() && !visitFilteredEdge) || (fact->getFilterState(endNodeRef.getId()) == Filter::NotFiltered) || (!originalFilterState && visitFilteredEdge)) {
      endNodeRef.accept(*this);
    }
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitEndDelegateDeclarationSyntax_ParameterList(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;
  }

  // edge: ReturnType
  genNodePtr = node.getReturnType() ;
  if (genNodePtr) {
    const expression::TypeSyntax& endNodeRef = dynamic_cast<const expression::TypeSyntax&>(*genNodePtr);
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitDelegateDeclarationSyntax_ReturnType(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;

    if ((!fact->getIsFilterTurnedOn() && !visitFilteredEdge) || (fact->getFilterState(endNodeRef.getId()) == Filter::NotFiltered) || (!originalFilterState && visitFilteredEdge)) {
      endNodeRef.accept(*this);
    }
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitEndDelegateDeclarationSyntax_ReturnType(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;
  }
}

void AlgorithmPreorder::visit(const structure::DelegateDeclarationSyntax& node, bool callFirst /*= true*/){
#ifdef DEBUG_PREORDER
  std::cout << "Rec. run: " << (unsigned int)&node << " " << node.getId() << " " << Common::toString(node.getNodeKind()) << std::endl;
#endif
  if (safeMode || visitCrossEdgeTree) {
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

void AlgorithmPreorder::visitAllEdges(const structure::DestructorDeclarationSyntax& node, bool callFirst /*= true*/){
  visitAllEdges(dynamic_cast<const structure::BaseMethodDeclarationSyntax&>(node),false);
}

void AlgorithmPreorder::visit(const structure::DestructorDeclarationSyntax& node, bool callFirst /*= true*/){
#ifdef DEBUG_PREORDER
  std::cout << "Rec. run: " << (unsigned int)&node << " " << node.getId() << " " << Common::toString(node.getNodeKind()) << std::endl;
#endif
  if (safeMode || visitCrossEdgeTree) {
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

void AlgorithmPreorder::visitAllEdges(const structure::ElseClauseSyntax& node, bool callFirst /*= true*/){
  visitAllEdges(dynamic_cast<const base::Positioned&>(node),false);

  std::list<Visitor*>::iterator itVisitors;

  const base::Base* genNodePtr;
  // edge: Statement
  genNodePtr = node.getStatement() ;
  if (genNodePtr) {
    const statement::StatementSyntax& endNodeRef = dynamic_cast<const statement::StatementSyntax&>(*genNodePtr);
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitElseClauseSyntax_Statement(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;

    if ((!fact->getIsFilterTurnedOn() && !visitFilteredEdge) || (fact->getFilterState(endNodeRef.getId()) == Filter::NotFiltered) || (!originalFilterState && visitFilteredEdge)) {
      endNodeRef.accept(*this);
    }
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitEndElseClauseSyntax_Statement(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;
  }
}

void AlgorithmPreorder::visit(const structure::ElseClauseSyntax& node, bool callFirst /*= true*/){
#ifdef DEBUG_PREORDER
  std::cout << "Rec. run: " << (unsigned int)&node << " " << node.getId() << " " << Common::toString(node.getNodeKind()) << std::endl;
#endif
  if (safeMode || visitCrossEdgeTree) {
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

void AlgorithmPreorder::visitAllEdges(const structure::EnumDeclarationSyntax& node, bool callFirst /*= true*/){
  visitAllEdges(dynamic_cast<const structure::BaseTypeDeclarationSyntax&>(node),false);

  std::list<Visitor*>::iterator itVisitors;

  // edge: Members
  for (ListIterator<structure::EnumMemberDeclarationSyntax> it = node.getMembersListIteratorBegin(); it != node.getMembersListIteratorEnd(); ++it) {
    const structure::EnumMemberDeclarationSyntax& endNodeRef = *it;
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitEnumDeclarationSyntax_Members(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;

    if ((!fact->getIsFilterTurnedOn() && !visitFilteredEdge) || (fact->getFilterState(endNodeRef.getId()) == Filter::NotFiltered) || (!originalFilterState && visitFilteredEdge)) {
      endNodeRef.accept(*this);
    }
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitEndEnumDeclarationSyntax_Members(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;
  }
}

void AlgorithmPreorder::visit(const structure::EnumDeclarationSyntax& node, bool callFirst /*= true*/){
#ifdef DEBUG_PREORDER
  std::cout << "Rec. run: " << (unsigned int)&node << " " << node.getId() << " " << Common::toString(node.getNodeKind()) << std::endl;
#endif
  if (safeMode || visitCrossEdgeTree) {
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

void AlgorithmPreorder::visitAllEdges(const structure::EnumMemberDeclarationSyntax& node, bool callFirst /*= true*/){
  visitAllEdges(dynamic_cast<const structure::MemberDeclarationSyntax&>(node),false);

  std::list<Visitor*>::iterator itVisitors;

  // edge: AttributeLists
  for (ListIterator<structure::AttributeListSyntax> it = node.getAttributeListsListIteratorBegin(); it != node.getAttributeListsListIteratorEnd(); ++it) {
    const structure::AttributeListSyntax& endNodeRef = *it;
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitEnumMemberDeclarationSyntax_AttributeLists(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;

    if ((!fact->getIsFilterTurnedOn() && !visitFilteredEdge) || (fact->getFilterState(endNodeRef.getId()) == Filter::NotFiltered) || (!originalFilterState && visitFilteredEdge)) {
      endNodeRef.accept(*this);
    }
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitEndEnumMemberDeclarationSyntax_AttributeLists(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;
  }

  const base::Base* genNodePtr;
  // edge: EqualsValue
  genNodePtr = node.getEqualsValue() ;
  if (genNodePtr) {
    const structure::EqualsValueClauseSyntax& endNodeRef = dynamic_cast<const structure::EqualsValueClauseSyntax&>(*genNodePtr);
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitEnumMemberDeclarationSyntax_EqualsValue(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;

    if ((!fact->getIsFilterTurnedOn() && !visitFilteredEdge) || (fact->getFilterState(endNodeRef.getId()) == Filter::NotFiltered) || (!originalFilterState && visitFilteredEdge)) {
      endNodeRef.accept(*this);
    }
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitEndEnumMemberDeclarationSyntax_EqualsValue(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;
  }
}

void AlgorithmPreorder::visit(const structure::EnumMemberDeclarationSyntax& node, bool callFirst /*= true*/){
#ifdef DEBUG_PREORDER
  std::cout << "Rec. run: " << (unsigned int)&node << " " << node.getId() << " " << Common::toString(node.getNodeKind()) << std::endl;
#endif
  if (safeMode || visitCrossEdgeTree) {
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

void AlgorithmPreorder::visitAllEdges(const structure::EqualsValueClauseSyntax& node, bool callFirst /*= true*/){
  visitAllEdges(dynamic_cast<const base::Positioned&>(node),false);

  std::list<Visitor*>::iterator itVisitors;

  const base::Base* genNodePtr;
  // edge: Value
  genNodePtr = node.getValue() ;
  if (genNodePtr) {
    const expression::ExpressionSyntax& endNodeRef = dynamic_cast<const expression::ExpressionSyntax&>(*genNodePtr);
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitEqualsValueClauseSyntax_Value(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;

    if ((!fact->getIsFilterTurnedOn() && !visitFilteredEdge) || (fact->getFilterState(endNodeRef.getId()) == Filter::NotFiltered) || (!originalFilterState && visitFilteredEdge)) {
      endNodeRef.accept(*this);
    }
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitEndEqualsValueClauseSyntax_Value(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;
  }
}

void AlgorithmPreorder::visit(const structure::EqualsValueClauseSyntax& node, bool callFirst /*= true*/){
#ifdef DEBUG_PREORDER
  std::cout << "Rec. run: " << (unsigned int)&node << " " << node.getId() << " " << Common::toString(node.getNodeKind()) << std::endl;
#endif
  if (safeMode || visitCrossEdgeTree) {
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

void AlgorithmPreorder::visitAllEdges(const structure::EventDeclarationSyntax& node, bool callFirst /*= true*/){
  visitAllEdges(dynamic_cast<const structure::BasePropertyDeclarationSyntax&>(node),false);
}

void AlgorithmPreorder::visit(const structure::EventDeclarationSyntax& node, bool callFirst /*= true*/){
#ifdef DEBUG_PREORDER
  std::cout << "Rec. run: " << (unsigned int)&node << " " << node.getId() << " " << Common::toString(node.getNodeKind()) << std::endl;
#endif
  if (safeMode || visitCrossEdgeTree) {
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

void AlgorithmPreorder::visitAllEdges(const structure::EventFieldDeclarationSyntax& node, bool callFirst /*= true*/){
  visitAllEdges(dynamic_cast<const structure::BaseFieldDeclarationSyntax&>(node),false);
}

void AlgorithmPreorder::visit(const structure::EventFieldDeclarationSyntax& node, bool callFirst /*= true*/){
#ifdef DEBUG_PREORDER
  std::cout << "Rec. run: " << (unsigned int)&node << " " << node.getId() << " " << Common::toString(node.getNodeKind()) << std::endl;
#endif
  if (safeMode || visitCrossEdgeTree) {
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

void AlgorithmPreorder::visitAllEdges(const structure::ExplicitInterfaceSpecifierSyntax& node, bool callFirst /*= true*/){
  visitAllEdges(dynamic_cast<const base::Positioned&>(node),false);

  std::list<Visitor*>::iterator itVisitors;

  const base::Base* genNodePtr;
  // edge: Name
  genNodePtr = node.getName() ;
  if (genNodePtr) {
    const expression::NameSyntax& endNodeRef = dynamic_cast<const expression::NameSyntax&>(*genNodePtr);
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitExplicitInterfaceSpecifierSyntax_Name(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;

    if ((!fact->getIsFilterTurnedOn() && !visitFilteredEdge) || (fact->getFilterState(endNodeRef.getId()) == Filter::NotFiltered) || (!originalFilterState && visitFilteredEdge)) {
      endNodeRef.accept(*this);
    }
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitEndExplicitInterfaceSpecifierSyntax_Name(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;
  }
}

void AlgorithmPreorder::visit(const structure::ExplicitInterfaceSpecifierSyntax& node, bool callFirst /*= true*/){
#ifdef DEBUG_PREORDER
  std::cout << "Rec. run: " << (unsigned int)&node << " " << node.getId() << " " << Common::toString(node.getNodeKind()) << std::endl;
#endif
  if (safeMode || visitCrossEdgeTree) {
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

void AlgorithmPreorder::visitAllEdges(const structure::ExternAliasDirectiveSyntax& node, bool callFirst /*= true*/){
  visitAllEdges(dynamic_cast<const base::Positioned&>(node),false);
}

void AlgorithmPreorder::visit(const structure::ExternAliasDirectiveSyntax& node, bool callFirst /*= true*/){
#ifdef DEBUG_PREORDER
  std::cout << "Rec. run: " << (unsigned int)&node << " " << node.getId() << " " << Common::toString(node.getNodeKind()) << std::endl;
#endif
  if (safeMode || visitCrossEdgeTree) {
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

void AlgorithmPreorder::visitAllEdges(const structure::FieldDeclarationSyntax& node, bool callFirst /*= true*/){
  visitAllEdges(dynamic_cast<const structure::BaseFieldDeclarationSyntax&>(node),false);
}

void AlgorithmPreorder::visit(const structure::FieldDeclarationSyntax& node, bool callFirst /*= true*/){
#ifdef DEBUG_PREORDER
  std::cout << "Rec. run: " << (unsigned int)&node << " " << node.getId() << " " << Common::toString(node.getNodeKind()) << std::endl;
#endif
  if (safeMode || visitCrossEdgeTree) {
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

void AlgorithmPreorder::visitAllEdges(const structure::FinallyClauseSyntax& node, bool callFirst /*= true*/){
  visitAllEdges(dynamic_cast<const base::Positioned&>(node),false);

  std::list<Visitor*>::iterator itVisitors;

  const base::Base* genNodePtr;
  // edge: Block
  genNodePtr = node.getBlock() ;
  if (genNodePtr) {
    const statement::BlockSyntax& endNodeRef = dynamic_cast<const statement::BlockSyntax&>(*genNodePtr);
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitFinallyClauseSyntax_Block(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;

    if ((!fact->getIsFilterTurnedOn() && !visitFilteredEdge) || (fact->getFilterState(endNodeRef.getId()) == Filter::NotFiltered) || (!originalFilterState && visitFilteredEdge)) {
      endNodeRef.accept(*this);
    }
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitEndFinallyClauseSyntax_Block(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;
  }
}

void AlgorithmPreorder::visit(const structure::FinallyClauseSyntax& node, bool callFirst /*= true*/){
#ifdef DEBUG_PREORDER
  std::cout << "Rec. run: " << (unsigned int)&node << " " << node.getId() << " " << Common::toString(node.getNodeKind()) << std::endl;
#endif
  if (safeMode || visitCrossEdgeTree) {
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

void AlgorithmPreorder::visitAllEdges(const structure::FromClauseSyntax& node, bool callFirst /*= true*/){
  visitAllEdges(dynamic_cast<const structure::QueryClauseSyntax&>(node),false);

  std::list<Visitor*>::iterator itVisitors;

  const base::Base* genNodePtr;
  // edge: Expression
  genNodePtr = node.getExpression() ;
  if (genNodePtr) {
    const expression::ExpressionSyntax& endNodeRef = dynamic_cast<const expression::ExpressionSyntax&>(*genNodePtr);
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitFromClauseSyntax_Expression(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;

    if ((!fact->getIsFilterTurnedOn() && !visitFilteredEdge) || (fact->getFilterState(endNodeRef.getId()) == Filter::NotFiltered) || (!originalFilterState && visitFilteredEdge)) {
      endNodeRef.accept(*this);
    }
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitEndFromClauseSyntax_Expression(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;
  }

  // edge: Type
  genNodePtr = node.getType() ;
  if (genNodePtr) {
    const expression::TypeSyntax& endNodeRef = dynamic_cast<const expression::TypeSyntax&>(*genNodePtr);
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitFromClauseSyntax_Type(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;

    if ((!fact->getIsFilterTurnedOn() && !visitFilteredEdge) || (fact->getFilterState(endNodeRef.getId()) == Filter::NotFiltered) || (!originalFilterState && visitFilteredEdge)) {
      endNodeRef.accept(*this);
    }
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitEndFromClauseSyntax_Type(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;
  }
}

void AlgorithmPreorder::visit(const structure::FromClauseSyntax& node, bool callFirst /*= true*/){
#ifdef DEBUG_PREORDER
  std::cout << "Rec. run: " << (unsigned int)&node << " " << node.getId() << " " << Common::toString(node.getNodeKind()) << std::endl;
#endif
  if (safeMode || visitCrossEdgeTree) {
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

void AlgorithmPreorder::visitAllEdges(const structure::GlobalStatementSyntax& node, bool callFirst /*= true*/){
  visitAllEdges(dynamic_cast<const structure::MemberDeclarationSyntax&>(node),false);

  std::list<Visitor*>::iterator itVisitors;

  const base::Base* genNodePtr;
  // edge: Statement
  genNodePtr = node.getStatement() ;
  if (genNodePtr) {
    const statement::StatementSyntax& endNodeRef = dynamic_cast<const statement::StatementSyntax&>(*genNodePtr);
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitGlobalStatementSyntax_Statement(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;

    if ((!fact->getIsFilterTurnedOn() && !visitFilteredEdge) || (fact->getFilterState(endNodeRef.getId()) == Filter::NotFiltered) || (!originalFilterState && visitFilteredEdge)) {
      endNodeRef.accept(*this);
    }
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitEndGlobalStatementSyntax_Statement(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;
  }
}

void AlgorithmPreorder::visit(const structure::GlobalStatementSyntax& node, bool callFirst /*= true*/){
#ifdef DEBUG_PREORDER
  std::cout << "Rec. run: " << (unsigned int)&node << " " << node.getId() << " " << Common::toString(node.getNodeKind()) << std::endl;
#endif
  if (safeMode || visitCrossEdgeTree) {
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

void AlgorithmPreorder::visitAllEdges(const structure::GroupClauseSyntax& node, bool callFirst /*= true*/){
  visitAllEdges(dynamic_cast<const structure::SelectOrGroupClauseSyntax&>(node),false);

  std::list<Visitor*>::iterator itVisitors;

  const base::Base* genNodePtr;
  // edge: ByExpression
  genNodePtr = node.getByExpression() ;
  if (genNodePtr) {
    const expression::ExpressionSyntax& endNodeRef = dynamic_cast<const expression::ExpressionSyntax&>(*genNodePtr);
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitGroupClauseSyntax_ByExpression(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;

    if ((!fact->getIsFilterTurnedOn() && !visitFilteredEdge) || (fact->getFilterState(endNodeRef.getId()) == Filter::NotFiltered) || (!originalFilterState && visitFilteredEdge)) {
      endNodeRef.accept(*this);
    }
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitEndGroupClauseSyntax_ByExpression(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;
  }

  // edge: GroupExpression
  genNodePtr = node.getGroupExpression() ;
  if (genNodePtr) {
    const expression::ExpressionSyntax& endNodeRef = dynamic_cast<const expression::ExpressionSyntax&>(*genNodePtr);
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitGroupClauseSyntax_GroupExpression(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;

    if ((!fact->getIsFilterTurnedOn() && !visitFilteredEdge) || (fact->getFilterState(endNodeRef.getId()) == Filter::NotFiltered) || (!originalFilterState && visitFilteredEdge)) {
      endNodeRef.accept(*this);
    }
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitEndGroupClauseSyntax_GroupExpression(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;
  }
}

void AlgorithmPreorder::visit(const structure::GroupClauseSyntax& node, bool callFirst /*= true*/){
#ifdef DEBUG_PREORDER
  std::cout << "Rec. run: " << (unsigned int)&node << " " << node.getId() << " " << Common::toString(node.getNodeKind()) << std::endl;
#endif
  if (safeMode || visitCrossEdgeTree) {
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

void AlgorithmPreorder::visitAllEdges(const structure::IncompleteMemberSyntax& node, bool callFirst /*= true*/){
  visitAllEdges(dynamic_cast<const structure::MemberDeclarationSyntax&>(node),false);

  std::list<Visitor*>::iterator itVisitors;

  // edge: AttributeLists
  for (ListIterator<structure::AttributeListSyntax> it = node.getAttributeListsListIteratorBegin(); it != node.getAttributeListsListIteratorEnd(); ++it) {
    const structure::AttributeListSyntax& endNodeRef = *it;
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitIncompleteMemberSyntax_AttributeLists(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;

    if ((!fact->getIsFilterTurnedOn() && !visitFilteredEdge) || (fact->getFilterState(endNodeRef.getId()) == Filter::NotFiltered) || (!originalFilterState && visitFilteredEdge)) {
      endNodeRef.accept(*this);
    }
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitEndIncompleteMemberSyntax_AttributeLists(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;
  }

  const base::Base* genNodePtr;
  // edge: Type
  genNodePtr = node.getType() ;
  if (genNodePtr) {
    const expression::TypeSyntax& endNodeRef = dynamic_cast<const expression::TypeSyntax&>(*genNodePtr);
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitIncompleteMemberSyntax_Type(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;

    if ((!fact->getIsFilterTurnedOn() && !visitFilteredEdge) || (fact->getFilterState(endNodeRef.getId()) == Filter::NotFiltered) || (!originalFilterState && visitFilteredEdge)) {
      endNodeRef.accept(*this);
    }
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitEndIncompleteMemberSyntax_Type(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;
  }
}

void AlgorithmPreorder::visit(const structure::IncompleteMemberSyntax& node, bool callFirst /*= true*/){
#ifdef DEBUG_PREORDER
  std::cout << "Rec. run: " << (unsigned int)&node << " " << node.getId() << " " << Common::toString(node.getNodeKind()) << std::endl;
#endif
  if (safeMode || visitCrossEdgeTree) {
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

void AlgorithmPreorder::visitAllEdges(const structure::IndexerDeclarationSyntax& node, bool callFirst /*= true*/){
  visitAllEdges(dynamic_cast<const structure::BasePropertyDeclarationSyntax&>(node),false);

  std::list<Visitor*>::iterator itVisitors;

  const base::Base* genNodePtr;
  // edge: ExpressionBody
  genNodePtr = node.getExpressionBody() ;
  if (genNodePtr) {
    const structure::ArrowExpressionClauseSyntax& endNodeRef = dynamic_cast<const structure::ArrowExpressionClauseSyntax&>(*genNodePtr);
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitIndexerDeclarationSyntax_ExpressionBody(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;

    if ((!fact->getIsFilterTurnedOn() && !visitFilteredEdge) || (fact->getFilterState(endNodeRef.getId()) == Filter::NotFiltered) || (!originalFilterState && visitFilteredEdge)) {
      endNodeRef.accept(*this);
    }
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitEndIndexerDeclarationSyntax_ExpressionBody(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;
  }

  // edge: ParameterList
  genNodePtr = node.getParameterList() ;
  if (genNodePtr) {
    const structure::BracketedParameterListSyntax& endNodeRef = dynamic_cast<const structure::BracketedParameterListSyntax&>(*genNodePtr);
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitIndexerDeclarationSyntax_ParameterList(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;

    if ((!fact->getIsFilterTurnedOn() && !visitFilteredEdge) || (fact->getFilterState(endNodeRef.getId()) == Filter::NotFiltered) || (!originalFilterState && visitFilteredEdge)) {
      endNodeRef.accept(*this);
    }
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitEndIndexerDeclarationSyntax_ParameterList(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;
  }
}

void AlgorithmPreorder::visit(const structure::IndexerDeclarationSyntax& node, bool callFirst /*= true*/){
#ifdef DEBUG_PREORDER
  std::cout << "Rec. run: " << (unsigned int)&node << " " << node.getId() << " " << Common::toString(node.getNodeKind()) << std::endl;
#endif
  if (safeMode || visitCrossEdgeTree) {
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

void AlgorithmPreorder::visitAllEdges(const structure::IndexerMemberCrefSyntax& node, bool callFirst /*= true*/){
  visitAllEdges(dynamic_cast<const structure::MemberCrefSyntax&>(node),false);

  std::list<Visitor*>::iterator itVisitors;

  const base::Base* genNodePtr;
  // edge: Parameters
  genNodePtr = node.getParameters() ;
  if (genNodePtr) {
    const structure::CrefBracketedParameterListSyntax& endNodeRef = dynamic_cast<const structure::CrefBracketedParameterListSyntax&>(*genNodePtr);
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitIndexerMemberCrefSyntax_Parameters(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;

    if ((!fact->getIsFilterTurnedOn() && !visitFilteredEdge) || (fact->getFilterState(endNodeRef.getId()) == Filter::NotFiltered) || (!originalFilterState && visitFilteredEdge)) {
      endNodeRef.accept(*this);
    }
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitEndIndexerMemberCrefSyntax_Parameters(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;
  }
}

void AlgorithmPreorder::visit(const structure::IndexerMemberCrefSyntax& node, bool callFirst /*= true*/){
#ifdef DEBUG_PREORDER
  std::cout << "Rec. run: " << (unsigned int)&node << " " << node.getId() << " " << Common::toString(node.getNodeKind()) << std::endl;
#endif
  if (safeMode || visitCrossEdgeTree) {
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

void AlgorithmPreorder::visitAllEdges(const structure::InterfaceDeclarationSyntax& node, bool callFirst /*= true*/){
  visitAllEdges(dynamic_cast<const structure::TypeDeclarationSyntax&>(node),false);
}

void AlgorithmPreorder::visit(const structure::InterfaceDeclarationSyntax& node, bool callFirst /*= true*/){
#ifdef DEBUG_PREORDER
  std::cout << "Rec. run: " << (unsigned int)&node << " " << node.getId() << " " << Common::toString(node.getNodeKind()) << std::endl;
#endif
  if (safeMode || visitCrossEdgeTree) {
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

void AlgorithmPreorder::visitAllEdges(const structure::InterpolatedStringContentSyntax& node, bool callFirst /*= true*/){
  visitAllEdges(dynamic_cast<const base::Positioned&>(node),false);
}

void AlgorithmPreorder::visitAllEdges(const structure::InterpolatedStringTextSyntax& node, bool callFirst /*= true*/){
  visitAllEdges(dynamic_cast<const structure::InterpolatedStringContentSyntax&>(node),false);
}

void AlgorithmPreorder::visit(const structure::InterpolatedStringTextSyntax& node, bool callFirst /*= true*/){
#ifdef DEBUG_PREORDER
  std::cout << "Rec. run: " << (unsigned int)&node << " " << node.getId() << " " << Common::toString(node.getNodeKind()) << std::endl;
#endif
  if (safeMode || visitCrossEdgeTree) {
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

void AlgorithmPreorder::visitAllEdges(const structure::InterpolationAlignmentClauseSyntax& node, bool callFirst /*= true*/){
  visitAllEdges(dynamic_cast<const base::Positioned&>(node),false);

  std::list<Visitor*>::iterator itVisitors;

  const base::Base* genNodePtr;
  // edge: Value
  genNodePtr = node.getValue() ;
  if (genNodePtr) {
    const expression::ExpressionSyntax& endNodeRef = dynamic_cast<const expression::ExpressionSyntax&>(*genNodePtr);
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitInterpolationAlignmentClauseSyntax_Value(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;

    if ((!fact->getIsFilterTurnedOn() && !visitFilteredEdge) || (fact->getFilterState(endNodeRef.getId()) == Filter::NotFiltered) || (!originalFilterState && visitFilteredEdge)) {
      endNodeRef.accept(*this);
    }
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitEndInterpolationAlignmentClauseSyntax_Value(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;
  }
}

void AlgorithmPreorder::visit(const structure::InterpolationAlignmentClauseSyntax& node, bool callFirst /*= true*/){
#ifdef DEBUG_PREORDER
  std::cout << "Rec. run: " << (unsigned int)&node << " " << node.getId() << " " << Common::toString(node.getNodeKind()) << std::endl;
#endif
  if (safeMode || visitCrossEdgeTree) {
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

void AlgorithmPreorder::visitAllEdges(const structure::InterpolationFormatClauseSyntax& node, bool callFirst /*= true*/){
  visitAllEdges(dynamic_cast<const base::Positioned&>(node),false);
}

void AlgorithmPreorder::visit(const structure::InterpolationFormatClauseSyntax& node, bool callFirst /*= true*/){
#ifdef DEBUG_PREORDER
  std::cout << "Rec. run: " << (unsigned int)&node << " " << node.getId() << " " << Common::toString(node.getNodeKind()) << std::endl;
#endif
  if (safeMode || visitCrossEdgeTree) {
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

void AlgorithmPreorder::visitAllEdges(const structure::InterpolationSyntax& node, bool callFirst /*= true*/){
  visitAllEdges(dynamic_cast<const structure::InterpolatedStringContentSyntax&>(node),false);

  std::list<Visitor*>::iterator itVisitors;

  const base::Base* genNodePtr;
  // edge: AlignmentClause
  genNodePtr = node.getAlignmentClause() ;
  if (genNodePtr) {
    const structure::InterpolationAlignmentClauseSyntax& endNodeRef = dynamic_cast<const structure::InterpolationAlignmentClauseSyntax&>(*genNodePtr);
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitInterpolationSyntax_AlignmentClause(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;

    if ((!fact->getIsFilterTurnedOn() && !visitFilteredEdge) || (fact->getFilterState(endNodeRef.getId()) == Filter::NotFiltered) || (!originalFilterState && visitFilteredEdge)) {
      endNodeRef.accept(*this);
    }
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitEndInterpolationSyntax_AlignmentClause(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;
  }

  // edge: Expression
  genNodePtr = node.getExpression() ;
  if (genNodePtr) {
    const expression::ExpressionSyntax& endNodeRef = dynamic_cast<const expression::ExpressionSyntax&>(*genNodePtr);
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitInterpolationSyntax_Expression(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;

    if ((!fact->getIsFilterTurnedOn() && !visitFilteredEdge) || (fact->getFilterState(endNodeRef.getId()) == Filter::NotFiltered) || (!originalFilterState && visitFilteredEdge)) {
      endNodeRef.accept(*this);
    }
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitEndInterpolationSyntax_Expression(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;
  }

  // edge: FormatClause
  genNodePtr = node.getFormatClause() ;
  if (genNodePtr) {
    const structure::InterpolationFormatClauseSyntax& endNodeRef = dynamic_cast<const structure::InterpolationFormatClauseSyntax&>(*genNodePtr);
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitInterpolationSyntax_FormatClause(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;

    if ((!fact->getIsFilterTurnedOn() && !visitFilteredEdge) || (fact->getFilterState(endNodeRef.getId()) == Filter::NotFiltered) || (!originalFilterState && visitFilteredEdge)) {
      endNodeRef.accept(*this);
    }
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitEndInterpolationSyntax_FormatClause(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;
  }
}

void AlgorithmPreorder::visit(const structure::InterpolationSyntax& node, bool callFirst /*= true*/){
#ifdef DEBUG_PREORDER
  std::cout << "Rec. run: " << (unsigned int)&node << " " << node.getId() << " " << Common::toString(node.getNodeKind()) << std::endl;
#endif
  if (safeMode || visitCrossEdgeTree) {
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

void AlgorithmPreorder::visitAllEdges(const structure::JoinClauseSyntax& node, bool callFirst /*= true*/){
  visitAllEdges(dynamic_cast<const structure::QueryClauseSyntax&>(node),false);

  std::list<Visitor*>::iterator itVisitors;

  const base::Base* genNodePtr;
  // edge: InExpression
  genNodePtr = node.getInExpression() ;
  if (genNodePtr) {
    const expression::ExpressionSyntax& endNodeRef = dynamic_cast<const expression::ExpressionSyntax&>(*genNodePtr);
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitJoinClauseSyntax_InExpression(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;

    if ((!fact->getIsFilterTurnedOn() && !visitFilteredEdge) || (fact->getFilterState(endNodeRef.getId()) == Filter::NotFiltered) || (!originalFilterState && visitFilteredEdge)) {
      endNodeRef.accept(*this);
    }
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitEndJoinClauseSyntax_InExpression(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;
  }

  // edge: Into
  genNodePtr = node.getInto() ;
  if (genNodePtr) {
    const structure::JoinIntoClauseSyntax& endNodeRef = dynamic_cast<const structure::JoinIntoClauseSyntax&>(*genNodePtr);
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitJoinClauseSyntax_Into(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;

    if ((!fact->getIsFilterTurnedOn() && !visitFilteredEdge) || (fact->getFilterState(endNodeRef.getId()) == Filter::NotFiltered) || (!originalFilterState && visitFilteredEdge)) {
      endNodeRef.accept(*this);
    }
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitEndJoinClauseSyntax_Into(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;
  }

  // edge: LeftExpression
  genNodePtr = node.getLeftExpression() ;
  if (genNodePtr) {
    const expression::ExpressionSyntax& endNodeRef = dynamic_cast<const expression::ExpressionSyntax&>(*genNodePtr);
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitJoinClauseSyntax_LeftExpression(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;

    if ((!fact->getIsFilterTurnedOn() && !visitFilteredEdge) || (fact->getFilterState(endNodeRef.getId()) == Filter::NotFiltered) || (!originalFilterState && visitFilteredEdge)) {
      endNodeRef.accept(*this);
    }
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitEndJoinClauseSyntax_LeftExpression(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;
  }

  // edge: RightExpression
  genNodePtr = node.getRightExpression() ;
  if (genNodePtr) {
    const expression::ExpressionSyntax& endNodeRef = dynamic_cast<const expression::ExpressionSyntax&>(*genNodePtr);
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitJoinClauseSyntax_RightExpression(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;

    if ((!fact->getIsFilterTurnedOn() && !visitFilteredEdge) || (fact->getFilterState(endNodeRef.getId()) == Filter::NotFiltered) || (!originalFilterState && visitFilteredEdge)) {
      endNodeRef.accept(*this);
    }
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitEndJoinClauseSyntax_RightExpression(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;
  }

  // edge: Type
  genNodePtr = node.getType() ;
  if (genNodePtr) {
    const expression::TypeSyntax& endNodeRef = dynamic_cast<const expression::TypeSyntax&>(*genNodePtr);
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitJoinClauseSyntax_Type(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;

    if ((!fact->getIsFilterTurnedOn() && !visitFilteredEdge) || (fact->getFilterState(endNodeRef.getId()) == Filter::NotFiltered) || (!originalFilterState && visitFilteredEdge)) {
      endNodeRef.accept(*this);
    }
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitEndJoinClauseSyntax_Type(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;
  }
}

void AlgorithmPreorder::visit(const structure::JoinClauseSyntax& node, bool callFirst /*= true*/){
#ifdef DEBUG_PREORDER
  std::cout << "Rec. run: " << (unsigned int)&node << " " << node.getId() << " " << Common::toString(node.getNodeKind()) << std::endl;
#endif
  if (safeMode || visitCrossEdgeTree) {
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

void AlgorithmPreorder::visitAllEdges(const structure::JoinIntoClauseSyntax& node, bool callFirst /*= true*/){
  visitAllEdges(dynamic_cast<const base::Positioned&>(node),false);
}

void AlgorithmPreorder::visit(const structure::JoinIntoClauseSyntax& node, bool callFirst /*= true*/){
#ifdef DEBUG_PREORDER
  std::cout << "Rec. run: " << (unsigned int)&node << " " << node.getId() << " " << Common::toString(node.getNodeKind()) << std::endl;
#endif
  if (safeMode || visitCrossEdgeTree) {
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

void AlgorithmPreorder::visitAllEdges(const structure::LetClauseSyntax& node, bool callFirst /*= true*/){
  visitAllEdges(dynamic_cast<const structure::QueryClauseSyntax&>(node),false);

  std::list<Visitor*>::iterator itVisitors;

  const base::Base* genNodePtr;
  // edge: Expression
  genNodePtr = node.getExpression() ;
  if (genNodePtr) {
    const expression::ExpressionSyntax& endNodeRef = dynamic_cast<const expression::ExpressionSyntax&>(*genNodePtr);
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitLetClauseSyntax_Expression(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;

    if ((!fact->getIsFilterTurnedOn() && !visitFilteredEdge) || (fact->getFilterState(endNodeRef.getId()) == Filter::NotFiltered) || (!originalFilterState && visitFilteredEdge)) {
      endNodeRef.accept(*this);
    }
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitEndLetClauseSyntax_Expression(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;
  }
}

void AlgorithmPreorder::visit(const structure::LetClauseSyntax& node, bool callFirst /*= true*/){
#ifdef DEBUG_PREORDER
  std::cout << "Rec. run: " << (unsigned int)&node << " " << node.getId() << " " << Common::toString(node.getNodeKind()) << std::endl;
#endif
  if (safeMode || visitCrossEdgeTree) {
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

void AlgorithmPreorder::visitAllEdges(const structure::MemberCrefSyntax& node, bool callFirst /*= true*/){
  visitAllEdges(dynamic_cast<const structure::CrefSyntax&>(node),false);
}

void AlgorithmPreorder::visitAllEdges(const structure::MemberDeclarationSyntax& node, bool callFirst /*= true*/){
  visitAllEdges(dynamic_cast<const base::Positioned&>(node),false);
}

void AlgorithmPreorder::visitAllEdges(const structure::MethodDeclarationSyntax& node, bool callFirst /*= true*/){
  visitAllEdges(dynamic_cast<const structure::BaseMethodDeclarationSyntax&>(node),false);

  std::list<Visitor*>::iterator itVisitors;

  // edge: ConstraintClauses
  for (ListIterator<structure::TypeParameterConstraintClauseSyntax> it = node.getConstraintClausesListIteratorBegin(); it != node.getConstraintClausesListIteratorEnd(); ++it) {
    const structure::TypeParameterConstraintClauseSyntax& endNodeRef = *it;
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitMethodDeclarationSyntax_ConstraintClauses(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;

    if ((!fact->getIsFilterTurnedOn() && !visitFilteredEdge) || (fact->getFilterState(endNodeRef.getId()) == Filter::NotFiltered) || (!originalFilterState && visitFilteredEdge)) {
      endNodeRef.accept(*this);
    }
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitEndMethodDeclarationSyntax_ConstraintClauses(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;
  }

  const base::Base* genNodePtr;
  // edge: ExplicitInterfaceSpecifier
  genNodePtr = node.getExplicitInterfaceSpecifier() ;
  if (genNodePtr) {
    const structure::ExplicitInterfaceSpecifierSyntax& endNodeRef = dynamic_cast<const structure::ExplicitInterfaceSpecifierSyntax&>(*genNodePtr);
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitMethodDeclarationSyntax_ExplicitInterfaceSpecifier(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;

    if ((!fact->getIsFilterTurnedOn() && !visitFilteredEdge) || (fact->getFilterState(endNodeRef.getId()) == Filter::NotFiltered) || (!originalFilterState && visitFilteredEdge)) {
      endNodeRef.accept(*this);
    }
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitEndMethodDeclarationSyntax_ExplicitInterfaceSpecifier(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;
  }

  // edge: ExpressionBody
  genNodePtr = node.getExpressionBody() ;
  if (genNodePtr) {
    const structure::ArrowExpressionClauseSyntax& endNodeRef = dynamic_cast<const structure::ArrowExpressionClauseSyntax&>(*genNodePtr);
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitMethodDeclarationSyntax_ExpressionBody(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;

    if ((!fact->getIsFilterTurnedOn() && !visitFilteredEdge) || (fact->getFilterState(endNodeRef.getId()) == Filter::NotFiltered) || (!originalFilterState && visitFilteredEdge)) {
      endNodeRef.accept(*this);
    }
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitEndMethodDeclarationSyntax_ExpressionBody(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;
  }

  // edge: ReturnType
  genNodePtr = node.getReturnType() ;
  if (genNodePtr) {
    const expression::TypeSyntax& endNodeRef = dynamic_cast<const expression::TypeSyntax&>(*genNodePtr);
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitMethodDeclarationSyntax_ReturnType(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;

    if ((!fact->getIsFilterTurnedOn() && !visitFilteredEdge) || (fact->getFilterState(endNodeRef.getId()) == Filter::NotFiltered) || (!originalFilterState && visitFilteredEdge)) {
      endNodeRef.accept(*this);
    }
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitEndMethodDeclarationSyntax_ReturnType(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;
  }
}

void AlgorithmPreorder::visit(const structure::MethodDeclarationSyntax& node, bool callFirst /*= true*/){
#ifdef DEBUG_PREORDER
  std::cout << "Rec. run: " << (unsigned int)&node << " " << node.getId() << " " << Common::toString(node.getNodeKind()) << std::endl;
#endif
  if (safeMode || visitCrossEdgeTree) {
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

void AlgorithmPreorder::visitAllEdges(const structure::NameColonSyntax& node, bool callFirst /*= true*/){
  visitAllEdges(dynamic_cast<const base::Positioned&>(node),false);

  std::list<Visitor*>::iterator itVisitors;

  const base::Base* genNodePtr;
  // edge: Name
  genNodePtr = node.getName() ;
  if (genNodePtr) {
    const expression::IdentifierNameSyntax& endNodeRef = dynamic_cast<const expression::IdentifierNameSyntax&>(*genNodePtr);
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitNameColonSyntax_Name(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;

    if ((!fact->getIsFilterTurnedOn() && !visitFilteredEdge) || (fact->getFilterState(endNodeRef.getId()) == Filter::NotFiltered) || (!originalFilterState && visitFilteredEdge)) {
      endNodeRef.accept(*this);
    }
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitEndNameColonSyntax_Name(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;
  }
}

void AlgorithmPreorder::visit(const structure::NameColonSyntax& node, bool callFirst /*= true*/){
#ifdef DEBUG_PREORDER
  std::cout << "Rec. run: " << (unsigned int)&node << " " << node.getId() << " " << Common::toString(node.getNodeKind()) << std::endl;
#endif
  if (safeMode || visitCrossEdgeTree) {
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

void AlgorithmPreorder::visitAllEdges(const structure::NameEqualsSyntax& node, bool callFirst /*= true*/){
  visitAllEdges(dynamic_cast<const base::Positioned&>(node),false);

  std::list<Visitor*>::iterator itVisitors;

  const base::Base* genNodePtr;
  // edge: Name
  genNodePtr = node.getName() ;
  if (genNodePtr) {
    const expression::IdentifierNameSyntax& endNodeRef = dynamic_cast<const expression::IdentifierNameSyntax&>(*genNodePtr);
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitNameEqualsSyntax_Name(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;

    if ((!fact->getIsFilterTurnedOn() && !visitFilteredEdge) || (fact->getFilterState(endNodeRef.getId()) == Filter::NotFiltered) || (!originalFilterState && visitFilteredEdge)) {
      endNodeRef.accept(*this);
    }
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitEndNameEqualsSyntax_Name(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;
  }
}

void AlgorithmPreorder::visit(const structure::NameEqualsSyntax& node, bool callFirst /*= true*/){
#ifdef DEBUG_PREORDER
  std::cout << "Rec. run: " << (unsigned int)&node << " " << node.getId() << " " << Common::toString(node.getNodeKind()) << std::endl;
#endif
  if (safeMode || visitCrossEdgeTree) {
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

void AlgorithmPreorder::visitAllEdges(const structure::NameMemberCrefSyntax& node, bool callFirst /*= true*/){
  visitAllEdges(dynamic_cast<const structure::MemberCrefSyntax&>(node),false);

  std::list<Visitor*>::iterator itVisitors;

  const base::Base* genNodePtr;
  // edge: Name
  genNodePtr = node.getName() ;
  if (genNodePtr) {
    const expression::TypeSyntax& endNodeRef = dynamic_cast<const expression::TypeSyntax&>(*genNodePtr);
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitNameMemberCrefSyntax_Name(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;

    if ((!fact->getIsFilterTurnedOn() && !visitFilteredEdge) || (fact->getFilterState(endNodeRef.getId()) == Filter::NotFiltered) || (!originalFilterState && visitFilteredEdge)) {
      endNodeRef.accept(*this);
    }
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitEndNameMemberCrefSyntax_Name(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;
  }

  // edge: Parameters
  genNodePtr = node.getParameters() ;
  if (genNodePtr) {
    const structure::CrefParameterListSyntax& endNodeRef = dynamic_cast<const structure::CrefParameterListSyntax&>(*genNodePtr);
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitNameMemberCrefSyntax_Parameters(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;

    if ((!fact->getIsFilterTurnedOn() && !visitFilteredEdge) || (fact->getFilterState(endNodeRef.getId()) == Filter::NotFiltered) || (!originalFilterState && visitFilteredEdge)) {
      endNodeRef.accept(*this);
    }
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitEndNameMemberCrefSyntax_Parameters(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;
  }
}

void AlgorithmPreorder::visit(const structure::NameMemberCrefSyntax& node, bool callFirst /*= true*/){
#ifdef DEBUG_PREORDER
  std::cout << "Rec. run: " << (unsigned int)&node << " " << node.getId() << " " << Common::toString(node.getNodeKind()) << std::endl;
#endif
  if (safeMode || visitCrossEdgeTree) {
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

void AlgorithmPreorder::visitAllEdges(const structure::NamespaceDeclarationSyntax& node, bool callFirst /*= true*/){
  visitAllEdges(dynamic_cast<const structure::MemberDeclarationSyntax&>(node),false);

  std::list<Visitor*>::iterator itVisitors;

  // edge: Externs
  for (ListIterator<structure::ExternAliasDirectiveSyntax> it = node.getExternsListIteratorBegin(); it != node.getExternsListIteratorEnd(); ++it) {
    const structure::ExternAliasDirectiveSyntax& endNodeRef = *it;
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitNamespaceDeclarationSyntax_Externs(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;

    if ((!fact->getIsFilterTurnedOn() && !visitFilteredEdge) || (fact->getFilterState(endNodeRef.getId()) == Filter::NotFiltered) || (!originalFilterState && visitFilteredEdge)) {
      endNodeRef.accept(*this);
    }
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitEndNamespaceDeclarationSyntax_Externs(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;
  }

  // edge: Members
  for (ListIterator<structure::MemberDeclarationSyntax> it = node.getMembersListIteratorBegin(); it != node.getMembersListIteratorEnd(); ++it) {
    const structure::MemberDeclarationSyntax& endNodeRef = *it;
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitNamespaceDeclarationSyntax_Members(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;

    if ((!fact->getIsFilterTurnedOn() && !visitFilteredEdge) || (fact->getFilterState(endNodeRef.getId()) == Filter::NotFiltered) || (!originalFilterState && visitFilteredEdge)) {
      endNodeRef.accept(*this);
    }
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitEndNamespaceDeclarationSyntax_Members(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;
  }

  const base::Base* genNodePtr;
  // edge: Name
  genNodePtr = node.getName() ;
  if (genNodePtr) {
    const expression::NameSyntax& endNodeRef = dynamic_cast<const expression::NameSyntax&>(*genNodePtr);
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitNamespaceDeclarationSyntax_Name(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;

    if ((!fact->getIsFilterTurnedOn() && !visitFilteredEdge) || (fact->getFilterState(endNodeRef.getId()) == Filter::NotFiltered) || (!originalFilterState && visitFilteredEdge)) {
      endNodeRef.accept(*this);
    }
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitEndNamespaceDeclarationSyntax_Name(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;
  }

  // edge: Usings
  for (ListIterator<structure::UsingDirectiveSyntax> it = node.getUsingsListIteratorBegin(); it != node.getUsingsListIteratorEnd(); ++it) {
    const structure::UsingDirectiveSyntax& endNodeRef = *it;
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitNamespaceDeclarationSyntax_Usings(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;

    if ((!fact->getIsFilterTurnedOn() && !visitFilteredEdge) || (fact->getFilterState(endNodeRef.getId()) == Filter::NotFiltered) || (!originalFilterState && visitFilteredEdge)) {
      endNodeRef.accept(*this);
    }
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitEndNamespaceDeclarationSyntax_Usings(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;
  }
}

void AlgorithmPreorder::visit(const structure::NamespaceDeclarationSyntax& node, bool callFirst /*= true*/){
#ifdef DEBUG_PREORDER
  std::cout << "Rec. run: " << (unsigned int)&node << " " << node.getId() << " " << Common::toString(node.getNodeKind()) << std::endl;
#endif
  if (safeMode || visitCrossEdgeTree) {
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

void AlgorithmPreorder::visitAllEdges(const structure::OperatorDeclarationSyntax& node, bool callFirst /*= true*/){
  visitAllEdges(dynamic_cast<const structure::BaseMethodDeclarationSyntax&>(node),false);

  std::list<Visitor*>::iterator itVisitors;

  const base::Base* genNodePtr;
  // edge: ExpressionBody
  genNodePtr = node.getExpressionBody() ;
  if (genNodePtr) {
    const structure::ArrowExpressionClauseSyntax& endNodeRef = dynamic_cast<const structure::ArrowExpressionClauseSyntax&>(*genNodePtr);
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitOperatorDeclarationSyntax_ExpressionBody(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;

    if ((!fact->getIsFilterTurnedOn() && !visitFilteredEdge) || (fact->getFilterState(endNodeRef.getId()) == Filter::NotFiltered) || (!originalFilterState && visitFilteredEdge)) {
      endNodeRef.accept(*this);
    }
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitEndOperatorDeclarationSyntax_ExpressionBody(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;
  }

  // edge: ReturnType
  genNodePtr = node.getReturnType() ;
  if (genNodePtr) {
    const expression::TypeSyntax& endNodeRef = dynamic_cast<const expression::TypeSyntax&>(*genNodePtr);
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitOperatorDeclarationSyntax_ReturnType(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;

    if ((!fact->getIsFilterTurnedOn() && !visitFilteredEdge) || (fact->getFilterState(endNodeRef.getId()) == Filter::NotFiltered) || (!originalFilterState && visitFilteredEdge)) {
      endNodeRef.accept(*this);
    }
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitEndOperatorDeclarationSyntax_ReturnType(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;
  }
}

void AlgorithmPreorder::visit(const structure::OperatorDeclarationSyntax& node, bool callFirst /*= true*/){
#ifdef DEBUG_PREORDER
  std::cout << "Rec. run: " << (unsigned int)&node << " " << node.getId() << " " << Common::toString(node.getNodeKind()) << std::endl;
#endif
  if (safeMode || visitCrossEdgeTree) {
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

void AlgorithmPreorder::visitAllEdges(const structure::OperatorMemberCrefSyntax& node, bool callFirst /*= true*/){
  visitAllEdges(dynamic_cast<const structure::MemberCrefSyntax&>(node),false);

  std::list<Visitor*>::iterator itVisitors;

  const base::Base* genNodePtr;
  // edge: Parameters
  genNodePtr = node.getParameters() ;
  if (genNodePtr) {
    const structure::CrefParameterListSyntax& endNodeRef = dynamic_cast<const structure::CrefParameterListSyntax&>(*genNodePtr);
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitOperatorMemberCrefSyntax_Parameters(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;

    if ((!fact->getIsFilterTurnedOn() && !visitFilteredEdge) || (fact->getFilterState(endNodeRef.getId()) == Filter::NotFiltered) || (!originalFilterState && visitFilteredEdge)) {
      endNodeRef.accept(*this);
    }
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitEndOperatorMemberCrefSyntax_Parameters(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;
  }
}

void AlgorithmPreorder::visit(const structure::OperatorMemberCrefSyntax& node, bool callFirst /*= true*/){
#ifdef DEBUG_PREORDER
  std::cout << "Rec. run: " << (unsigned int)&node << " " << node.getId() << " " << Common::toString(node.getNodeKind()) << std::endl;
#endif
  if (safeMode || visitCrossEdgeTree) {
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

void AlgorithmPreorder::visitAllEdges(const structure::OrderByClauseSyntax& node, bool callFirst /*= true*/){
  visitAllEdges(dynamic_cast<const structure::QueryClauseSyntax&>(node),false);

  std::list<Visitor*>::iterator itVisitors;

  // edge: Orderings
  for (ListIterator<structure::OrderingSyntax> it = node.getOrderingsListIteratorBegin(); it != node.getOrderingsListIteratorEnd(); ++it) {
    const structure::OrderingSyntax& endNodeRef = *it;
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitOrderByClauseSyntax_Orderings(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;

    if ((!fact->getIsFilterTurnedOn() && !visitFilteredEdge) || (fact->getFilterState(endNodeRef.getId()) == Filter::NotFiltered) || (!originalFilterState && visitFilteredEdge)) {
      endNodeRef.accept(*this);
    }
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitEndOrderByClauseSyntax_Orderings(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;
  }
}

void AlgorithmPreorder::visit(const structure::OrderByClauseSyntax& node, bool callFirst /*= true*/){
#ifdef DEBUG_PREORDER
  std::cout << "Rec. run: " << (unsigned int)&node << " " << node.getId() << " " << Common::toString(node.getNodeKind()) << std::endl;
#endif
  if (safeMode || visitCrossEdgeTree) {
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

void AlgorithmPreorder::visitAllEdges(const structure::OrderingSyntax& node, bool callFirst /*= true*/){
  visitAllEdges(dynamic_cast<const base::Positioned&>(node),false);

  std::list<Visitor*>::iterator itVisitors;

  const base::Base* genNodePtr;
  // edge: Expression
  genNodePtr = node.getExpression() ;
  if (genNodePtr) {
    const expression::ExpressionSyntax& endNodeRef = dynamic_cast<const expression::ExpressionSyntax&>(*genNodePtr);
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitOrderingSyntax_Expression(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;

    if ((!fact->getIsFilterTurnedOn() && !visitFilteredEdge) || (fact->getFilterState(endNodeRef.getId()) == Filter::NotFiltered) || (!originalFilterState && visitFilteredEdge)) {
      endNodeRef.accept(*this);
    }
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitEndOrderingSyntax_Expression(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;
  }
}

void AlgorithmPreorder::visit(const structure::OrderingSyntax& node, bool callFirst /*= true*/){
#ifdef DEBUG_PREORDER
  std::cout << "Rec. run: " << (unsigned int)&node << " " << node.getId() << " " << Common::toString(node.getNodeKind()) << std::endl;
#endif
  if (safeMode || visitCrossEdgeTree) {
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

void AlgorithmPreorder::visitAllEdges(const structure::ParameterListSyntax& node, bool callFirst /*= true*/){
  visitAllEdges(dynamic_cast<const structure::BaseParameterListSyntax&>(node),false);
}

void AlgorithmPreorder::visit(const structure::ParameterListSyntax& node, bool callFirst /*= true*/){
#ifdef DEBUG_PREORDER
  std::cout << "Rec. run: " << (unsigned int)&node << " " << node.getId() << " " << Common::toString(node.getNodeKind()) << std::endl;
#endif
  if (safeMode || visitCrossEdgeTree) {
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

void AlgorithmPreorder::visitAllEdges(const structure::ParameterSyntax& node, bool callFirst /*= true*/){
  visitAllEdges(dynamic_cast<const base::Positioned&>(node),false);

  std::list<Visitor*>::iterator itVisitors;

  // edge: AttributeLists
  for (ListIterator<structure::AttributeListSyntax> it = node.getAttributeListsListIteratorBegin(); it != node.getAttributeListsListIteratorEnd(); ++it) {
    const structure::AttributeListSyntax& endNodeRef = *it;
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitParameterSyntax_AttributeLists(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;

    if ((!fact->getIsFilterTurnedOn() && !visitFilteredEdge) || (fact->getFilterState(endNodeRef.getId()) == Filter::NotFiltered) || (!originalFilterState && visitFilteredEdge)) {
      endNodeRef.accept(*this);
    }
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitEndParameterSyntax_AttributeLists(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;
  }

  const base::Base* genNodePtr;
  // edge: Default
  genNodePtr = node.getDefault() ;
  if (genNodePtr) {
    const structure::EqualsValueClauseSyntax& endNodeRef = dynamic_cast<const structure::EqualsValueClauseSyntax&>(*genNodePtr);
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitParameterSyntax_Default(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;

    if ((!fact->getIsFilterTurnedOn() && !visitFilteredEdge) || (fact->getFilterState(endNodeRef.getId()) == Filter::NotFiltered) || (!originalFilterState && visitFilteredEdge)) {
      endNodeRef.accept(*this);
    }
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitEndParameterSyntax_Default(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;
  }

  // edge: Type
  genNodePtr = node.getType() ;
  if (genNodePtr) {
    const expression::TypeSyntax& endNodeRef = dynamic_cast<const expression::TypeSyntax&>(*genNodePtr);
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitParameterSyntax_Type(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;

    if ((!fact->getIsFilterTurnedOn() && !visitFilteredEdge) || (fact->getFilterState(endNodeRef.getId()) == Filter::NotFiltered) || (!originalFilterState && visitFilteredEdge)) {
      endNodeRef.accept(*this);
    }
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitEndParameterSyntax_Type(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;
  }
}

void AlgorithmPreorder::visit(const structure::ParameterSyntax& node, bool callFirst /*= true*/){
#ifdef DEBUG_PREORDER
  std::cout << "Rec. run: " << (unsigned int)&node << " " << node.getId() << " " << Common::toString(node.getNodeKind()) << std::endl;
#endif
  if (safeMode || visitCrossEdgeTree) {
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

void AlgorithmPreorder::visitAllEdges(const structure::PropertyDeclarationSyntax& node, bool callFirst /*= true*/){
  visitAllEdges(dynamic_cast<const structure::BasePropertyDeclarationSyntax&>(node),false);

  std::list<Visitor*>::iterator itVisitors;

  const base::Base* genNodePtr;
  // edge: ExpressionBody
  genNodePtr = node.getExpressionBody() ;
  if (genNodePtr) {
    const structure::ArrowExpressionClauseSyntax& endNodeRef = dynamic_cast<const structure::ArrowExpressionClauseSyntax&>(*genNodePtr);
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitPropertyDeclarationSyntax_ExpressionBody(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;

    if ((!fact->getIsFilterTurnedOn() && !visitFilteredEdge) || (fact->getFilterState(endNodeRef.getId()) == Filter::NotFiltered) || (!originalFilterState && visitFilteredEdge)) {
      endNodeRef.accept(*this);
    }
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitEndPropertyDeclarationSyntax_ExpressionBody(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;
  }

  // edge: Initializer
  genNodePtr = node.getInitializer() ;
  if (genNodePtr) {
    const structure::EqualsValueClauseSyntax& endNodeRef = dynamic_cast<const structure::EqualsValueClauseSyntax&>(*genNodePtr);
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitPropertyDeclarationSyntax_Initializer(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;

    if ((!fact->getIsFilterTurnedOn() && !visitFilteredEdge) || (fact->getFilterState(endNodeRef.getId()) == Filter::NotFiltered) || (!originalFilterState && visitFilteredEdge)) {
      endNodeRef.accept(*this);
    }
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitEndPropertyDeclarationSyntax_Initializer(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;
  }
}

void AlgorithmPreorder::visit(const structure::PropertyDeclarationSyntax& node, bool callFirst /*= true*/){
#ifdef DEBUG_PREORDER
  std::cout << "Rec. run: " << (unsigned int)&node << " " << node.getId() << " " << Common::toString(node.getNodeKind()) << std::endl;
#endif
  if (safeMode || visitCrossEdgeTree) {
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

void AlgorithmPreorder::visitAllEdges(const structure::QualifiedCrefSyntax& node, bool callFirst /*= true*/){
  visitAllEdges(dynamic_cast<const structure::CrefSyntax&>(node),false);

  std::list<Visitor*>::iterator itVisitors;

  const base::Base* genNodePtr;
  // edge: Container
  genNodePtr = node.getContainer() ;
  if (genNodePtr) {
    const expression::TypeSyntax& endNodeRef = dynamic_cast<const expression::TypeSyntax&>(*genNodePtr);
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitQualifiedCrefSyntax_Container(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;

    if ((!fact->getIsFilterTurnedOn() && !visitFilteredEdge) || (fact->getFilterState(endNodeRef.getId()) == Filter::NotFiltered) || (!originalFilterState && visitFilteredEdge)) {
      endNodeRef.accept(*this);
    }
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitEndQualifiedCrefSyntax_Container(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;
  }

  // edge: Member
  genNodePtr = node.getMember() ;
  if (genNodePtr) {
    const structure::MemberCrefSyntax& endNodeRef = dynamic_cast<const structure::MemberCrefSyntax&>(*genNodePtr);
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitQualifiedCrefSyntax_Member(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;

    if ((!fact->getIsFilterTurnedOn() && !visitFilteredEdge) || (fact->getFilterState(endNodeRef.getId()) == Filter::NotFiltered) || (!originalFilterState && visitFilteredEdge)) {
      endNodeRef.accept(*this);
    }
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitEndQualifiedCrefSyntax_Member(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;
  }
}

void AlgorithmPreorder::visit(const structure::QualifiedCrefSyntax& node, bool callFirst /*= true*/){
#ifdef DEBUG_PREORDER
  std::cout << "Rec. run: " << (unsigned int)&node << " " << node.getId() << " " << Common::toString(node.getNodeKind()) << std::endl;
#endif
  if (safeMode || visitCrossEdgeTree) {
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

void AlgorithmPreorder::visitAllEdges(const structure::QueryBodySyntax& node, bool callFirst /*= true*/){
  visitAllEdges(dynamic_cast<const base::Positioned&>(node),false);

  std::list<Visitor*>::iterator itVisitors;

  // edge: Clauses
  for (ListIterator<structure::QueryClauseSyntax> it = node.getClausesListIteratorBegin(); it != node.getClausesListIteratorEnd(); ++it) {
    const structure::QueryClauseSyntax& endNodeRef = *it;
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitQueryBodySyntax_Clauses(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;

    if ((!fact->getIsFilterTurnedOn() && !visitFilteredEdge) || (fact->getFilterState(endNodeRef.getId()) == Filter::NotFiltered) || (!originalFilterState && visitFilteredEdge)) {
      endNodeRef.accept(*this);
    }
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitEndQueryBodySyntax_Clauses(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;
  }

  const base::Base* genNodePtr;
  // edge: Continuation
  genNodePtr = node.getContinuation() ;
  if (genNodePtr) {
    const structure::QueryContinuationSyntax& endNodeRef = dynamic_cast<const structure::QueryContinuationSyntax&>(*genNodePtr);
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitQueryBodySyntax_Continuation(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;

    if ((!fact->getIsFilterTurnedOn() && !visitFilteredEdge) || (fact->getFilterState(endNodeRef.getId()) == Filter::NotFiltered) || (!originalFilterState && visitFilteredEdge)) {
      endNodeRef.accept(*this);
    }
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitEndQueryBodySyntax_Continuation(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;
  }

  // edge: SelectOrGroup
  genNodePtr = node.getSelectOrGroup() ;
  if (genNodePtr) {
    const structure::SelectOrGroupClauseSyntax& endNodeRef = dynamic_cast<const structure::SelectOrGroupClauseSyntax&>(*genNodePtr);
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitQueryBodySyntax_SelectOrGroup(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;

    if ((!fact->getIsFilterTurnedOn() && !visitFilteredEdge) || (fact->getFilterState(endNodeRef.getId()) == Filter::NotFiltered) || (!originalFilterState && visitFilteredEdge)) {
      endNodeRef.accept(*this);
    }
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitEndQueryBodySyntax_SelectOrGroup(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;
  }
}

void AlgorithmPreorder::visit(const structure::QueryBodySyntax& node, bool callFirst /*= true*/){
#ifdef DEBUG_PREORDER
  std::cout << "Rec. run: " << (unsigned int)&node << " " << node.getId() << " " << Common::toString(node.getNodeKind()) << std::endl;
#endif
  if (safeMode || visitCrossEdgeTree) {
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

void AlgorithmPreorder::visitAllEdges(const structure::QueryClauseSyntax& node, bool callFirst /*= true*/){
  visitAllEdges(dynamic_cast<const base::Positioned&>(node),false);
}

void AlgorithmPreorder::visitAllEdges(const structure::QueryContinuationSyntax& node, bool callFirst /*= true*/){
  visitAllEdges(dynamic_cast<const base::Positioned&>(node),false);

  std::list<Visitor*>::iterator itVisitors;

  const base::Base* genNodePtr;
  // edge: Body
  genNodePtr = node.getBody() ;
  if (genNodePtr) {
    const structure::QueryBodySyntax& endNodeRef = dynamic_cast<const structure::QueryBodySyntax&>(*genNodePtr);
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitQueryContinuationSyntax_Body(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;

    if ((!fact->getIsFilterTurnedOn() && !visitFilteredEdge) || (fact->getFilterState(endNodeRef.getId()) == Filter::NotFiltered) || (!originalFilterState && visitFilteredEdge)) {
      endNodeRef.accept(*this);
    }
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitEndQueryContinuationSyntax_Body(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;
  }
}

void AlgorithmPreorder::visit(const structure::QueryContinuationSyntax& node, bool callFirst /*= true*/){
#ifdef DEBUG_PREORDER
  std::cout << "Rec. run: " << (unsigned int)&node << " " << node.getId() << " " << Common::toString(node.getNodeKind()) << std::endl;
#endif
  if (safeMode || visitCrossEdgeTree) {
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

void AlgorithmPreorder::visitAllEdges(const structure::SelectClauseSyntax& node, bool callFirst /*= true*/){
  visitAllEdges(dynamic_cast<const structure::SelectOrGroupClauseSyntax&>(node),false);

  std::list<Visitor*>::iterator itVisitors;

  const base::Base* genNodePtr;
  // edge: Expression
  genNodePtr = node.getExpression() ;
  if (genNodePtr) {
    const expression::ExpressionSyntax& endNodeRef = dynamic_cast<const expression::ExpressionSyntax&>(*genNodePtr);
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitSelectClauseSyntax_Expression(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;

    if ((!fact->getIsFilterTurnedOn() && !visitFilteredEdge) || (fact->getFilterState(endNodeRef.getId()) == Filter::NotFiltered) || (!originalFilterState && visitFilteredEdge)) {
      endNodeRef.accept(*this);
    }
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitEndSelectClauseSyntax_Expression(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;
  }
}

void AlgorithmPreorder::visit(const structure::SelectClauseSyntax& node, bool callFirst /*= true*/){
#ifdef DEBUG_PREORDER
  std::cout << "Rec. run: " << (unsigned int)&node << " " << node.getId() << " " << Common::toString(node.getNodeKind()) << std::endl;
#endif
  if (safeMode || visitCrossEdgeTree) {
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

void AlgorithmPreorder::visitAllEdges(const structure::SelectOrGroupClauseSyntax& node, bool callFirst /*= true*/){
  visitAllEdges(dynamic_cast<const base::Positioned&>(node),false);
}

void AlgorithmPreorder::visitAllEdges(const structure::SimpleBaseTypeSyntax& node, bool callFirst /*= true*/){
  visitAllEdges(dynamic_cast<const structure::BaseTypeSyntax&>(node),false);
}

void AlgorithmPreorder::visit(const structure::SimpleBaseTypeSyntax& node, bool callFirst /*= true*/){
#ifdef DEBUG_PREORDER
  std::cout << "Rec. run: " << (unsigned int)&node << " " << node.getId() << " " << Common::toString(node.getNodeKind()) << std::endl;
#endif
  if (safeMode || visitCrossEdgeTree) {
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

void AlgorithmPreorder::visitAllEdges(const structure::StructDeclarationSyntax& node, bool callFirst /*= true*/){
  visitAllEdges(dynamic_cast<const structure::TypeDeclarationSyntax&>(node),false);
}

void AlgorithmPreorder::visit(const structure::StructDeclarationSyntax& node, bool callFirst /*= true*/){
#ifdef DEBUG_PREORDER
  std::cout << "Rec. run: " << (unsigned int)&node << " " << node.getId() << " " << Common::toString(node.getNodeKind()) << std::endl;
#endif
  if (safeMode || visitCrossEdgeTree) {
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

void AlgorithmPreorder::visitAllEdges(const structure::SwitchLabelSyntax& node, bool callFirst /*= true*/){
  visitAllEdges(dynamic_cast<const base::Positioned&>(node),false);
}

void AlgorithmPreorder::visitAllEdges(const structure::SwitchSectionSyntax& node, bool callFirst /*= true*/){
  visitAllEdges(dynamic_cast<const base::Positioned&>(node),false);

  std::list<Visitor*>::iterator itVisitors;

  // edge: Labels
  for (ListIterator<structure::SwitchLabelSyntax> it = node.getLabelsListIteratorBegin(); it != node.getLabelsListIteratorEnd(); ++it) {
    const structure::SwitchLabelSyntax& endNodeRef = *it;
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitSwitchSectionSyntax_Labels(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;

    if ((!fact->getIsFilterTurnedOn() && !visitFilteredEdge) || (fact->getFilterState(endNodeRef.getId()) == Filter::NotFiltered) || (!originalFilterState && visitFilteredEdge)) {
      endNodeRef.accept(*this);
    }
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitEndSwitchSectionSyntax_Labels(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;
  }

  // edge: Statements
  for (ListIterator<statement::StatementSyntax> it = node.getStatementsListIteratorBegin(); it != node.getStatementsListIteratorEnd(); ++it) {
    const statement::StatementSyntax& endNodeRef = *it;
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitSwitchSectionSyntax_Statements(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;

    if ((!fact->getIsFilterTurnedOn() && !visitFilteredEdge) || (fact->getFilterState(endNodeRef.getId()) == Filter::NotFiltered) || (!originalFilterState && visitFilteredEdge)) {
      endNodeRef.accept(*this);
    }
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitEndSwitchSectionSyntax_Statements(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;
  }
}

void AlgorithmPreorder::visit(const structure::SwitchSectionSyntax& node, bool callFirst /*= true*/){
#ifdef DEBUG_PREORDER
  std::cout << "Rec. run: " << (unsigned int)&node << " " << node.getId() << " " << Common::toString(node.getNodeKind()) << std::endl;
#endif
  if (safeMode || visitCrossEdgeTree) {
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

void AlgorithmPreorder::visitAllEdges(const structure::SyntaxToken& node, bool callFirst /*= true*/){
  visitAllEdges(dynamic_cast<const base::Positioned&>(node),false);
}

void AlgorithmPreorder::visit(const structure::SyntaxToken& node, bool callFirst /*= true*/){
#ifdef DEBUG_PREORDER
  std::cout << "Rec. run: " << (unsigned int)&node << " " << node.getId() << " " << Common::toString(node.getNodeKind()) << std::endl;
#endif
  if (safeMode || visitCrossEdgeTree) {
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

void AlgorithmPreorder::visitAllEdges(const structure::TypeArgumentListSyntax& node, bool callFirst /*= true*/){
  visitAllEdges(dynamic_cast<const base::Positioned&>(node),false);

  std::list<Visitor*>::iterator itVisitors;

  // edge: Arguments
  for (ListIterator<expression::TypeSyntax> it = node.getArgumentsListIteratorBegin(); it != node.getArgumentsListIteratorEnd(); ++it) {
    const expression::TypeSyntax& endNodeRef = *it;
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitTypeArgumentListSyntax_Arguments(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;

    if ((!fact->getIsFilterTurnedOn() && !visitFilteredEdge) || (fact->getFilterState(endNodeRef.getId()) == Filter::NotFiltered) || (!originalFilterState && visitFilteredEdge)) {
      endNodeRef.accept(*this);
    }
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitEndTypeArgumentListSyntax_Arguments(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;
  }
}

void AlgorithmPreorder::visit(const structure::TypeArgumentListSyntax& node, bool callFirst /*= true*/){
#ifdef DEBUG_PREORDER
  std::cout << "Rec. run: " << (unsigned int)&node << " " << node.getId() << " " << Common::toString(node.getNodeKind()) << std::endl;
#endif
  if (safeMode || visitCrossEdgeTree) {
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

void AlgorithmPreorder::visitAllEdges(const structure::TypeConstraintSyntax& node, bool callFirst /*= true*/){
  visitAllEdges(dynamic_cast<const structure::TypeParameterConstraintSyntax&>(node),false);

  std::list<Visitor*>::iterator itVisitors;

  const base::Base* genNodePtr;
  // edge: Type
  genNodePtr = node.getType() ;
  if (genNodePtr) {
    const expression::TypeSyntax& endNodeRef = dynamic_cast<const expression::TypeSyntax&>(*genNodePtr);
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitTypeConstraintSyntax_Type(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;

    if ((!fact->getIsFilterTurnedOn() && !visitFilteredEdge) || (fact->getFilterState(endNodeRef.getId()) == Filter::NotFiltered) || (!originalFilterState && visitFilteredEdge)) {
      endNodeRef.accept(*this);
    }
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitEndTypeConstraintSyntax_Type(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;
  }
}

void AlgorithmPreorder::visit(const structure::TypeConstraintSyntax& node, bool callFirst /*= true*/){
#ifdef DEBUG_PREORDER
  std::cout << "Rec. run: " << (unsigned int)&node << " " << node.getId() << " " << Common::toString(node.getNodeKind()) << std::endl;
#endif
  if (safeMode || visitCrossEdgeTree) {
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

void AlgorithmPreorder::visitAllEdges(const structure::TypeCrefSyntax& node, bool callFirst /*= true*/){
  visitAllEdges(dynamic_cast<const structure::CrefSyntax&>(node),false);

  std::list<Visitor*>::iterator itVisitors;

  const base::Base* genNodePtr;
  // edge: Type
  genNodePtr = node.getType() ;
  if (genNodePtr) {
    const expression::TypeSyntax& endNodeRef = dynamic_cast<const expression::TypeSyntax&>(*genNodePtr);
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitTypeCrefSyntax_Type(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;

    if ((!fact->getIsFilterTurnedOn() && !visitFilteredEdge) || (fact->getFilterState(endNodeRef.getId()) == Filter::NotFiltered) || (!originalFilterState && visitFilteredEdge)) {
      endNodeRef.accept(*this);
    }
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitEndTypeCrefSyntax_Type(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;
  }
}

void AlgorithmPreorder::visit(const structure::TypeCrefSyntax& node, bool callFirst /*= true*/){
#ifdef DEBUG_PREORDER
  std::cout << "Rec. run: " << (unsigned int)&node << " " << node.getId() << " " << Common::toString(node.getNodeKind()) << std::endl;
#endif
  if (safeMode || visitCrossEdgeTree) {
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

void AlgorithmPreorder::visitAllEdges(const structure::TypeDeclarationSyntax& node, bool callFirst /*= true*/){
  visitAllEdges(dynamic_cast<const structure::BaseTypeDeclarationSyntax&>(node),false);

  std::list<Visitor*>::iterator itVisitors;

  // edge: ConstraintClauses
  for (ListIterator<structure::TypeParameterConstraintClauseSyntax> it = node.getConstraintClausesListIteratorBegin(); it != node.getConstraintClausesListIteratorEnd(); ++it) {
    const structure::TypeParameterConstraintClauseSyntax& endNodeRef = *it;
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitTypeDeclarationSyntax_ConstraintClauses(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;

    if ((!fact->getIsFilterTurnedOn() && !visitFilteredEdge) || (fact->getFilterState(endNodeRef.getId()) == Filter::NotFiltered) || (!originalFilterState && visitFilteredEdge)) {
      endNodeRef.accept(*this);
    }
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitEndTypeDeclarationSyntax_ConstraintClauses(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;
  }

  // edge: Members
  for (ListIterator<structure::MemberDeclarationSyntax> it = node.getMembersListIteratorBegin(); it != node.getMembersListIteratorEnd(); ++it) {
    const structure::MemberDeclarationSyntax& endNodeRef = *it;
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitTypeDeclarationSyntax_Members(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;

    if ((!fact->getIsFilterTurnedOn() && !visitFilteredEdge) || (fact->getFilterState(endNodeRef.getId()) == Filter::NotFiltered) || (!originalFilterState && visitFilteredEdge)) {
      endNodeRef.accept(*this);
    }
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitEndTypeDeclarationSyntax_Members(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;
  }

  const base::Base* genNodePtr;
  // edge: TypeParameterList
  genNodePtr = node.getTypeParameterList() ;
  if (genNodePtr) {
    const structure::TypeParameterListSyntax& endNodeRef = dynamic_cast<const structure::TypeParameterListSyntax&>(*genNodePtr);
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitTypeDeclarationSyntax_TypeParameterList(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;

    if ((!fact->getIsFilterTurnedOn() && !visitFilteredEdge) || (fact->getFilterState(endNodeRef.getId()) == Filter::NotFiltered) || (!originalFilterState && visitFilteredEdge)) {
      endNodeRef.accept(*this);
    }
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitEndTypeDeclarationSyntax_TypeParameterList(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;
  }
}

void AlgorithmPreorder::visitAllEdges(const structure::TypeParameterConstraintClauseSyntax& node, bool callFirst /*= true*/){
  visitAllEdges(dynamic_cast<const base::Positioned&>(node),false);

  std::list<Visitor*>::iterator itVisitors;

  // edge: Constraints
  for (ListIterator<structure::TypeParameterConstraintSyntax> it = node.getConstraintsListIteratorBegin(); it != node.getConstraintsListIteratorEnd(); ++it) {
    const structure::TypeParameterConstraintSyntax& endNodeRef = *it;
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitTypeParameterConstraintClauseSyntax_Constraints(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;

    if ((!fact->getIsFilterTurnedOn() && !visitFilteredEdge) || (fact->getFilterState(endNodeRef.getId()) == Filter::NotFiltered) || (!originalFilterState && visitFilteredEdge)) {
      endNodeRef.accept(*this);
    }
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitEndTypeParameterConstraintClauseSyntax_Constraints(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;
  }

  const base::Base* genNodePtr;
  // edge: Name
  genNodePtr = node.getName() ;
  if (genNodePtr) {
    const expression::IdentifierNameSyntax& endNodeRef = dynamic_cast<const expression::IdentifierNameSyntax&>(*genNodePtr);
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitTypeParameterConstraintClauseSyntax_Name(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;

    if ((!fact->getIsFilterTurnedOn() && !visitFilteredEdge) || (fact->getFilterState(endNodeRef.getId()) == Filter::NotFiltered) || (!originalFilterState && visitFilteredEdge)) {
      endNodeRef.accept(*this);
    }
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitEndTypeParameterConstraintClauseSyntax_Name(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;
  }
}

void AlgorithmPreorder::visit(const structure::TypeParameterConstraintClauseSyntax& node, bool callFirst /*= true*/){
#ifdef DEBUG_PREORDER
  std::cout << "Rec. run: " << (unsigned int)&node << " " << node.getId() << " " << Common::toString(node.getNodeKind()) << std::endl;
#endif
  if (safeMode || visitCrossEdgeTree) {
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

void AlgorithmPreorder::visitAllEdges(const structure::TypeParameterConstraintSyntax& node, bool callFirst /*= true*/){
  visitAllEdges(dynamic_cast<const base::Positioned&>(node),false);
}

void AlgorithmPreorder::visitAllEdges(const structure::TypeParameterListSyntax& node, bool callFirst /*= true*/){
  visitAllEdges(dynamic_cast<const base::Positioned&>(node),false);

  std::list<Visitor*>::iterator itVisitors;

  // edge: Parameters
  for (ListIterator<structure::TypeParameterSyntax> it = node.getParametersListIteratorBegin(); it != node.getParametersListIteratorEnd(); ++it) {
    const structure::TypeParameterSyntax& endNodeRef = *it;
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitTypeParameterListSyntax_Parameters(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;

    if ((!fact->getIsFilterTurnedOn() && !visitFilteredEdge) || (fact->getFilterState(endNodeRef.getId()) == Filter::NotFiltered) || (!originalFilterState && visitFilteredEdge)) {
      if (apRoot) {
        if (visitCrossEdgeTree) {
          unvisitedNodes[endNodeRef.getId()] = true;
        }
      }
      if (traversaldCrossEdges[edkTypeParameterListSyntax_Parameters]) {
        endNodeRef.accept(*this);
      }
    }
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitEndTypeParameterListSyntax_Parameters(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;
  }
}

void AlgorithmPreorder::visit(const structure::TypeParameterListSyntax& node, bool callFirst /*= true*/){
#ifdef DEBUG_PREORDER
  std::cout << "Rec. run: " << (unsigned int)&node << " " << node.getId() << " " << Common::toString(node.getNodeKind()) << std::endl;
#endif
  if (safeMode || visitCrossEdgeTree) {
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

void AlgorithmPreorder::visitAllEdges(const structure::TypeParameterSyntax& node, bool callFirst /*= true*/){
  visitAllEdges(dynamic_cast<const base::Positioned&>(node),false);

  std::list<Visitor*>::iterator itVisitors;

  // edge: AttributeLists
  for (ListIterator<structure::AttributeListSyntax> it = node.getAttributeListsListIteratorBegin(); it != node.getAttributeListsListIteratorEnd(); ++it) {
    const structure::AttributeListSyntax& endNodeRef = *it;
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitTypeParameterSyntax_AttributeLists(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;

    if ((!fact->getIsFilterTurnedOn() && !visitFilteredEdge) || (fact->getFilterState(endNodeRef.getId()) == Filter::NotFiltered) || (!originalFilterState && visitFilteredEdge)) {
      endNodeRef.accept(*this);
    }
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitEndTypeParameterSyntax_AttributeLists(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;
  }
}

void AlgorithmPreorder::visit(const structure::TypeParameterSyntax& node, bool callFirst /*= true*/){
#ifdef DEBUG_PREORDER
  std::cout << "Rec. run: " << (unsigned int)&node << " " << node.getId() << " " << Common::toString(node.getNodeKind()) << std::endl;
#endif
  if (safeMode || visitCrossEdgeTree) {
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

void AlgorithmPreorder::visitAllEdges(const structure::UsingDirectiveSyntax& node, bool callFirst /*= true*/){
  visitAllEdges(dynamic_cast<const base::Positioned&>(node),false);

  std::list<Visitor*>::iterator itVisitors;

  const base::Base* genNodePtr;
  // edge: Alias
  genNodePtr = node.getAlias() ;
  if (genNodePtr) {
    const structure::NameEqualsSyntax& endNodeRef = dynamic_cast<const structure::NameEqualsSyntax&>(*genNodePtr);
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitUsingDirectiveSyntax_Alias(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;

    if ((!fact->getIsFilterTurnedOn() && !visitFilteredEdge) || (fact->getFilterState(endNodeRef.getId()) == Filter::NotFiltered) || (!originalFilterState && visitFilteredEdge)) {
      endNodeRef.accept(*this);
    }
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitEndUsingDirectiveSyntax_Alias(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;
  }

  // edge: Name
  genNodePtr = node.getName() ;
  if (genNodePtr) {
    const expression::NameSyntax& endNodeRef = dynamic_cast<const expression::NameSyntax&>(*genNodePtr);
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitUsingDirectiveSyntax_Name(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;

    if ((!fact->getIsFilterTurnedOn() && !visitFilteredEdge) || (fact->getFilterState(endNodeRef.getId()) == Filter::NotFiltered) || (!originalFilterState && visitFilteredEdge)) {
      endNodeRef.accept(*this);
    }
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitEndUsingDirectiveSyntax_Name(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;
  }
}

void AlgorithmPreorder::visit(const structure::UsingDirectiveSyntax& node, bool callFirst /*= true*/){
#ifdef DEBUG_PREORDER
  std::cout << "Rec. run: " << (unsigned int)&node << " " << node.getId() << " " << Common::toString(node.getNodeKind()) << std::endl;
#endif
  if (safeMode || visitCrossEdgeTree) {
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

void AlgorithmPreorder::visitAllEdges(const structure::VariableDeclarationSyntax& node, bool callFirst /*= true*/){
  visitAllEdges(dynamic_cast<const base::Positioned&>(node),false);

  std::list<Visitor*>::iterator itVisitors;

  const base::Base* genNodePtr;
  // edge: Type
  genNodePtr = node.getType() ;
  if (genNodePtr) {
    const expression::TypeSyntax& endNodeRef = dynamic_cast<const expression::TypeSyntax&>(*genNodePtr);
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitVariableDeclarationSyntax_Type(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;

    if ((!fact->getIsFilterTurnedOn() && !visitFilteredEdge) || (fact->getFilterState(endNodeRef.getId()) == Filter::NotFiltered) || (!originalFilterState && visitFilteredEdge)) {
      endNodeRef.accept(*this);
    }
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitEndVariableDeclarationSyntax_Type(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;
  }

  // edge: Variables
  for (ListIterator<structure::VariableDeclaratorSyntax> it = node.getVariablesListIteratorBegin(); it != node.getVariablesListIteratorEnd(); ++it) {
    const structure::VariableDeclaratorSyntax& endNodeRef = *it;
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitVariableDeclarationSyntax_Variables(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;

    if ((!fact->getIsFilterTurnedOn() && !visitFilteredEdge) || (fact->getFilterState(endNodeRef.getId()) == Filter::NotFiltered) || (!originalFilterState && visitFilteredEdge)) {
      endNodeRef.accept(*this);
    }
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitEndVariableDeclarationSyntax_Variables(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;
  }
}

void AlgorithmPreorder::visit(const structure::VariableDeclarationSyntax& node, bool callFirst /*= true*/){
#ifdef DEBUG_PREORDER
  std::cout << "Rec. run: " << (unsigned int)&node << " " << node.getId() << " " << Common::toString(node.getNodeKind()) << std::endl;
#endif
  if (safeMode || visitCrossEdgeTree) {
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

void AlgorithmPreorder::visitAllEdges(const structure::VariableDeclaratorSyntax& node, bool callFirst /*= true*/){
  visitAllEdges(dynamic_cast<const base::Positioned&>(node),false);

  std::list<Visitor*>::iterator itVisitors;

  const base::Base* genNodePtr;
  // edge: ArgumentList
  genNodePtr = node.getArgumentList() ;
  if (genNodePtr) {
    const structure::BracketedArgumentListSyntax& endNodeRef = dynamic_cast<const structure::BracketedArgumentListSyntax&>(*genNodePtr);
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitVariableDeclaratorSyntax_ArgumentList(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;

    if ((!fact->getIsFilterTurnedOn() && !visitFilteredEdge) || (fact->getFilterState(endNodeRef.getId()) == Filter::NotFiltered) || (!originalFilterState && visitFilteredEdge)) {
      endNodeRef.accept(*this);
    }
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitEndVariableDeclaratorSyntax_ArgumentList(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;
  }

  // edge: Initializer
  genNodePtr = node.getInitializer() ;
  if (genNodePtr) {
    const structure::EqualsValueClauseSyntax& endNodeRef = dynamic_cast<const structure::EqualsValueClauseSyntax&>(*genNodePtr);
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitVariableDeclaratorSyntax_Initializer(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;

    if ((!fact->getIsFilterTurnedOn() && !visitFilteredEdge) || (fact->getFilterState(endNodeRef.getId()) == Filter::NotFiltered) || (!originalFilterState && visitFilteredEdge)) {
      endNodeRef.accept(*this);
    }
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitEndVariableDeclaratorSyntax_Initializer(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;
  }
}

void AlgorithmPreorder::visit(const structure::VariableDeclaratorSyntax& node, bool callFirst /*= true*/){
#ifdef DEBUG_PREORDER
  std::cout << "Rec. run: " << (unsigned int)&node << " " << node.getId() << " " << Common::toString(node.getNodeKind()) << std::endl;
#endif
  if (safeMode || visitCrossEdgeTree) {
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

void AlgorithmPreorder::visitAllEdges(const structure::WhereClauseSyntax& node, bool callFirst /*= true*/){
  visitAllEdges(dynamic_cast<const structure::QueryClauseSyntax&>(node),false);

  std::list<Visitor*>::iterator itVisitors;

  const base::Base* genNodePtr;
  // edge: Condition
  genNodePtr = node.getCondition() ;
  if (genNodePtr) {
    const expression::ExpressionSyntax& endNodeRef = dynamic_cast<const expression::ExpressionSyntax&>(*genNodePtr);
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitWhereClauseSyntax_Condition(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;

    if ((!fact->getIsFilterTurnedOn() && !visitFilteredEdge) || (fact->getFilterState(endNodeRef.getId()) == Filter::NotFiltered) || (!originalFilterState && visitFilteredEdge)) {
      endNodeRef.accept(*this);
    }
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitEndWhereClauseSyntax_Condition(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;
  }
}

void AlgorithmPreorder::visit(const structure::WhereClauseSyntax& node, bool callFirst /*= true*/){
#ifdef DEBUG_PREORDER
  std::cout << "Rec. run: " << (unsigned int)&node << " " << node.getId() << " " << Common::toString(node.getNodeKind()) << std::endl;
#endif
  if (safeMode || visitCrossEdgeTree) {
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

void AlgorithmPreorder::visitAllEdges(const structure::XmlAttributeSyntax& node, bool callFirst /*= true*/){
  visitAllEdges(dynamic_cast<const base::Positioned&>(node),false);

  std::list<Visitor*>::iterator itVisitors;

  const base::Base* genNodePtr;
  // edge: Name
  genNodePtr = node.getName() ;
  if (genNodePtr) {
    const structure::XmlNameSyntax& endNodeRef = dynamic_cast<const structure::XmlNameSyntax&>(*genNodePtr);
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitXmlAttributeSyntax_Name(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;

    if ((!fact->getIsFilterTurnedOn() && !visitFilteredEdge) || (fact->getFilterState(endNodeRef.getId()) == Filter::NotFiltered) || (!originalFilterState && visitFilteredEdge)) {
      endNodeRef.accept(*this);
    }
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitEndXmlAttributeSyntax_Name(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;
  }
}

void AlgorithmPreorder::visitAllEdges(const structure::XmlCDataSectionSyntax& node, bool callFirst /*= true*/){
  visitAllEdges(dynamic_cast<const structure::XmlNodeSyntax&>(node),false);
}

void AlgorithmPreorder::visit(const structure::XmlCDataSectionSyntax& node, bool callFirst /*= true*/){
#ifdef DEBUG_PREORDER
  std::cout << "Rec. run: " << (unsigned int)&node << " " << node.getId() << " " << Common::toString(node.getNodeKind()) << std::endl;
#endif
  if (safeMode || visitCrossEdgeTree) {
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

void AlgorithmPreorder::visitAllEdges(const structure::XmlCommentSyntax& node, bool callFirst /*= true*/){
  visitAllEdges(dynamic_cast<const structure::XmlNodeSyntax&>(node),false);
}

void AlgorithmPreorder::visit(const structure::XmlCommentSyntax& node, bool callFirst /*= true*/){
#ifdef DEBUG_PREORDER
  std::cout << "Rec. run: " << (unsigned int)&node << " " << node.getId() << " " << Common::toString(node.getNodeKind()) << std::endl;
#endif
  if (safeMode || visitCrossEdgeTree) {
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

void AlgorithmPreorder::visitAllEdges(const structure::XmlCrefAttributeSyntax& node, bool callFirst /*= true*/){
  visitAllEdges(dynamic_cast<const structure::XmlAttributeSyntax&>(node),false);

  std::list<Visitor*>::iterator itVisitors;

  const base::Base* genNodePtr;
  // edge: Cref
  genNodePtr = node.getCref() ;
  if (genNodePtr) {
    const structure::CrefSyntax& endNodeRef = dynamic_cast<const structure::CrefSyntax&>(*genNodePtr);
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitXmlCrefAttributeSyntax_Cref(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;

    if ((!fact->getIsFilterTurnedOn() && !visitFilteredEdge) || (fact->getFilterState(endNodeRef.getId()) == Filter::NotFiltered) || (!originalFilterState && visitFilteredEdge)) {
      endNodeRef.accept(*this);
    }
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitEndXmlCrefAttributeSyntax_Cref(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;
  }
}

void AlgorithmPreorder::visit(const structure::XmlCrefAttributeSyntax& node, bool callFirst /*= true*/){
#ifdef DEBUG_PREORDER
  std::cout << "Rec. run: " << (unsigned int)&node << " " << node.getId() << " " << Common::toString(node.getNodeKind()) << std::endl;
#endif
  if (safeMode || visitCrossEdgeTree) {
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

void AlgorithmPreorder::visitAllEdges(const structure::XmlElementEndTagSyntax& node, bool callFirst /*= true*/){
  visitAllEdges(dynamic_cast<const base::Positioned&>(node),false);

  std::list<Visitor*>::iterator itVisitors;

  const base::Base* genNodePtr;
  // edge: Name
  genNodePtr = node.getName() ;
  if (genNodePtr) {
    const structure::XmlNameSyntax& endNodeRef = dynamic_cast<const structure::XmlNameSyntax&>(*genNodePtr);
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitXmlElementEndTagSyntax_Name(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;

    if ((!fact->getIsFilterTurnedOn() && !visitFilteredEdge) || (fact->getFilterState(endNodeRef.getId()) == Filter::NotFiltered) || (!originalFilterState && visitFilteredEdge)) {
      endNodeRef.accept(*this);
    }
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitEndXmlElementEndTagSyntax_Name(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;
  }
}

void AlgorithmPreorder::visit(const structure::XmlElementEndTagSyntax& node, bool callFirst /*= true*/){
#ifdef DEBUG_PREORDER
  std::cout << "Rec. run: " << (unsigned int)&node << " " << node.getId() << " " << Common::toString(node.getNodeKind()) << std::endl;
#endif
  if (safeMode || visitCrossEdgeTree) {
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

void AlgorithmPreorder::visitAllEdges(const structure::XmlElementStartTagSyntax& node, bool callFirst /*= true*/){
  visitAllEdges(dynamic_cast<const base::Positioned&>(node),false);

  std::list<Visitor*>::iterator itVisitors;

  // edge: Attributes
  for (ListIterator<structure::XmlAttributeSyntax> it = node.getAttributesListIteratorBegin(); it != node.getAttributesListIteratorEnd(); ++it) {
    const structure::XmlAttributeSyntax& endNodeRef = *it;
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitXmlElementStartTagSyntax_Attributes(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;

    if ((!fact->getIsFilterTurnedOn() && !visitFilteredEdge) || (fact->getFilterState(endNodeRef.getId()) == Filter::NotFiltered) || (!originalFilterState && visitFilteredEdge)) {
      endNodeRef.accept(*this);
    }
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitEndXmlElementStartTagSyntax_Attributes(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;
  }

  const base::Base* genNodePtr;
  // edge: Name
  genNodePtr = node.getName() ;
  if (genNodePtr) {
    const structure::XmlNameSyntax& endNodeRef = dynamic_cast<const structure::XmlNameSyntax&>(*genNodePtr);
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitXmlElementStartTagSyntax_Name(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;

    if ((!fact->getIsFilterTurnedOn() && !visitFilteredEdge) || (fact->getFilterState(endNodeRef.getId()) == Filter::NotFiltered) || (!originalFilterState && visitFilteredEdge)) {
      endNodeRef.accept(*this);
    }
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitEndXmlElementStartTagSyntax_Name(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;
  }
}

void AlgorithmPreorder::visit(const structure::XmlElementStartTagSyntax& node, bool callFirst /*= true*/){
#ifdef DEBUG_PREORDER
  std::cout << "Rec. run: " << (unsigned int)&node << " " << node.getId() << " " << Common::toString(node.getNodeKind()) << std::endl;
#endif
  if (safeMode || visitCrossEdgeTree) {
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

void AlgorithmPreorder::visitAllEdges(const structure::XmlElementSyntax& node, bool callFirst /*= true*/){
  visitAllEdges(dynamic_cast<const structure::XmlNodeSyntax&>(node),false);

  std::list<Visitor*>::iterator itVisitors;

  // edge: Content
  for (ListIterator<structure::XmlNodeSyntax> it = node.getContentListIteratorBegin(); it != node.getContentListIteratorEnd(); ++it) {
    const structure::XmlNodeSyntax& endNodeRef = *it;
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitXmlElementSyntax_Content(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;

    if ((!fact->getIsFilterTurnedOn() && !visitFilteredEdge) || (fact->getFilterState(endNodeRef.getId()) == Filter::NotFiltered) || (!originalFilterState && visitFilteredEdge)) {
      endNodeRef.accept(*this);
    }
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitEndXmlElementSyntax_Content(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;
  }

  const base::Base* genNodePtr;
  // edge: EndTag
  genNodePtr = node.getEndTag() ;
  if (genNodePtr) {
    const structure::XmlElementEndTagSyntax& endNodeRef = dynamic_cast<const structure::XmlElementEndTagSyntax&>(*genNodePtr);
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitXmlElementSyntax_EndTag(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;

    if ((!fact->getIsFilterTurnedOn() && !visitFilteredEdge) || (fact->getFilterState(endNodeRef.getId()) == Filter::NotFiltered) || (!originalFilterState && visitFilteredEdge)) {
      endNodeRef.accept(*this);
    }
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitEndXmlElementSyntax_EndTag(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;
  }

  // edge: StartTag
  genNodePtr = node.getStartTag() ;
  if (genNodePtr) {
    const structure::XmlElementStartTagSyntax& endNodeRef = dynamic_cast<const structure::XmlElementStartTagSyntax&>(*genNodePtr);
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitXmlElementSyntax_StartTag(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;

    if ((!fact->getIsFilterTurnedOn() && !visitFilteredEdge) || (fact->getFilterState(endNodeRef.getId()) == Filter::NotFiltered) || (!originalFilterState && visitFilteredEdge)) {
      endNodeRef.accept(*this);
    }
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitEndXmlElementSyntax_StartTag(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;
  }
}

void AlgorithmPreorder::visit(const structure::XmlElementSyntax& node, bool callFirst /*= true*/){
#ifdef DEBUG_PREORDER
  std::cout << "Rec. run: " << (unsigned int)&node << " " << node.getId() << " " << Common::toString(node.getNodeKind()) << std::endl;
#endif
  if (safeMode || visitCrossEdgeTree) {
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

void AlgorithmPreorder::visitAllEdges(const structure::XmlEmptyElementSyntax& node, bool callFirst /*= true*/){
  visitAllEdges(dynamic_cast<const structure::XmlNodeSyntax&>(node),false);

  std::list<Visitor*>::iterator itVisitors;

  // edge: Attributes
  for (ListIterator<structure::XmlAttributeSyntax> it = node.getAttributesListIteratorBegin(); it != node.getAttributesListIteratorEnd(); ++it) {
    const structure::XmlAttributeSyntax& endNodeRef = *it;
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitXmlEmptyElementSyntax_Attributes(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;

    if ((!fact->getIsFilterTurnedOn() && !visitFilteredEdge) || (fact->getFilterState(endNodeRef.getId()) == Filter::NotFiltered) || (!originalFilterState && visitFilteredEdge)) {
      endNodeRef.accept(*this);
    }
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitEndXmlEmptyElementSyntax_Attributes(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;
  }

  const base::Base* genNodePtr;
  // edge: Name
  genNodePtr = node.getName() ;
  if (genNodePtr) {
    const structure::XmlNameSyntax& endNodeRef = dynamic_cast<const structure::XmlNameSyntax&>(*genNodePtr);
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitXmlEmptyElementSyntax_Name(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;

    if ((!fact->getIsFilterTurnedOn() && !visitFilteredEdge) || (fact->getFilterState(endNodeRef.getId()) == Filter::NotFiltered) || (!originalFilterState && visitFilteredEdge)) {
      endNodeRef.accept(*this);
    }
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitEndXmlEmptyElementSyntax_Name(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;
  }
}

void AlgorithmPreorder::visit(const structure::XmlEmptyElementSyntax& node, bool callFirst /*= true*/){
#ifdef DEBUG_PREORDER
  std::cout << "Rec. run: " << (unsigned int)&node << " " << node.getId() << " " << Common::toString(node.getNodeKind()) << std::endl;
#endif
  if (safeMode || visitCrossEdgeTree) {
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

void AlgorithmPreorder::visitAllEdges(const structure::XmlNameAttributeSyntax& node, bool callFirst /*= true*/){
  visitAllEdges(dynamic_cast<const structure::XmlAttributeSyntax&>(node),false);

  std::list<Visitor*>::iterator itVisitors;

  const base::Base* genNodePtr;
  // edge: Identifier
  genNodePtr = node.getIdentifier() ;
  if (genNodePtr) {
    const expression::IdentifierNameSyntax& endNodeRef = dynamic_cast<const expression::IdentifierNameSyntax&>(*genNodePtr);
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitXmlNameAttributeSyntax_Identifier(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;

    if ((!fact->getIsFilterTurnedOn() && !visitFilteredEdge) || (fact->getFilterState(endNodeRef.getId()) == Filter::NotFiltered) || (!originalFilterState && visitFilteredEdge)) {
      endNodeRef.accept(*this);
    }
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitEndXmlNameAttributeSyntax_Identifier(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;
  }
}

void AlgorithmPreorder::visit(const structure::XmlNameAttributeSyntax& node, bool callFirst /*= true*/){
#ifdef DEBUG_PREORDER
  std::cout << "Rec. run: " << (unsigned int)&node << " " << node.getId() << " " << Common::toString(node.getNodeKind()) << std::endl;
#endif
  if (safeMode || visitCrossEdgeTree) {
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

void AlgorithmPreorder::visitAllEdges(const structure::XmlNameSyntax& node, bool callFirst /*= true*/){
  visitAllEdges(dynamic_cast<const base::Positioned&>(node),false);

  std::list<Visitor*>::iterator itVisitors;

  const base::Base* genNodePtr;
  // edge: Prefix
  genNodePtr = node.getPrefix() ;
  if (genNodePtr) {
    const structure::XmlPrefixSyntax& endNodeRef = dynamic_cast<const structure::XmlPrefixSyntax&>(*genNodePtr);
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitXmlNameSyntax_Prefix(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;

    if ((!fact->getIsFilterTurnedOn() && !visitFilteredEdge) || (fact->getFilterState(endNodeRef.getId()) == Filter::NotFiltered) || (!originalFilterState && visitFilteredEdge)) {
      endNodeRef.accept(*this);
    }
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitEndXmlNameSyntax_Prefix(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;
  }
}

void AlgorithmPreorder::visit(const structure::XmlNameSyntax& node, bool callFirst /*= true*/){
#ifdef DEBUG_PREORDER
  std::cout << "Rec. run: " << (unsigned int)&node << " " << node.getId() << " " << Common::toString(node.getNodeKind()) << std::endl;
#endif
  if (safeMode || visitCrossEdgeTree) {
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

void AlgorithmPreorder::visitAllEdges(const structure::XmlNodeSyntax& node, bool callFirst /*= true*/){
  visitAllEdges(dynamic_cast<const base::Positioned&>(node),false);
}

void AlgorithmPreorder::visitAllEdges(const structure::XmlPrefixSyntax& node, bool callFirst /*= true*/){
  visitAllEdges(dynamic_cast<const base::Positioned&>(node),false);
}

void AlgorithmPreorder::visit(const structure::XmlPrefixSyntax& node, bool callFirst /*= true*/){
#ifdef DEBUG_PREORDER
  std::cout << "Rec. run: " << (unsigned int)&node << " " << node.getId() << " " << Common::toString(node.getNodeKind()) << std::endl;
#endif
  if (safeMode || visitCrossEdgeTree) {
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

void AlgorithmPreorder::visitAllEdges(const structure::XmlProcessingInstructionSyntax& node, bool callFirst /*= true*/){
  visitAllEdges(dynamic_cast<const structure::XmlNodeSyntax&>(node),false);

  std::list<Visitor*>::iterator itVisitors;

  const base::Base* genNodePtr;
  // edge: Name
  genNodePtr = node.getName() ;
  if (genNodePtr) {
    const structure::XmlNameSyntax& endNodeRef = dynamic_cast<const structure::XmlNameSyntax&>(*genNodePtr);
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitXmlProcessingInstructionSyntax_Name(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;

    if ((!fact->getIsFilterTurnedOn() && !visitFilteredEdge) || (fact->getFilterState(endNodeRef.getId()) == Filter::NotFiltered) || (!originalFilterState && visitFilteredEdge)) {
      endNodeRef.accept(*this);
    }
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitEndXmlProcessingInstructionSyntax_Name(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;
  }
}

void AlgorithmPreorder::visit(const structure::XmlProcessingInstructionSyntax& node, bool callFirst /*= true*/){
#ifdef DEBUG_PREORDER
  std::cout << "Rec. run: " << (unsigned int)&node << " " << node.getId() << " " << Common::toString(node.getNodeKind()) << std::endl;
#endif
  if (safeMode || visitCrossEdgeTree) {
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

void AlgorithmPreorder::visitAllEdges(const structure::XmlTextAttributeSyntax& node, bool callFirst /*= true*/){
  visitAllEdges(dynamic_cast<const structure::XmlAttributeSyntax&>(node),false);
}

void AlgorithmPreorder::visit(const structure::XmlTextAttributeSyntax& node, bool callFirst /*= true*/){
#ifdef DEBUG_PREORDER
  std::cout << "Rec. run: " << (unsigned int)&node << " " << node.getId() << " " << Common::toString(node.getNodeKind()) << std::endl;
#endif
  if (safeMode || visitCrossEdgeTree) {
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

void AlgorithmPreorder::visitAllEdges(const structure::XmlTextSyntax& node, bool callFirst /*= true*/){
  visitAllEdges(dynamic_cast<const structure::XmlNodeSyntax&>(node),false);
}

void AlgorithmPreorder::visit(const structure::XmlTextSyntax& node, bool callFirst /*= true*/){
#ifdef DEBUG_PREORDER
  std::cout << "Rec. run: " << (unsigned int)&node << " " << node.getId() << " " << Common::toString(node.getNodeKind()) << std::endl;
#endif
  if (safeMode || visitCrossEdgeTree) {
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

void AlgorithmPreorder::startPreorder(){

  if (!fact){
    throw CsharpException(COLUMBUS_LOCATION, CMSG_EX_YOU_MUST_GIVE_A_FACTORY_AT_FIRST);
  }

  if (visitorList.empty()){
    throw CsharpException(COLUMBUS_LOCATION, CMSG_EX_DON_T_HAVE_ANY_VISITOR);
  }

  if (safeMode || visitCrossEdgeTree) {
    visitedNodes.clear();
    visitedNodes.resize(fact->size(), false);
  }

  if (visitCrossEdgeTree) {
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
