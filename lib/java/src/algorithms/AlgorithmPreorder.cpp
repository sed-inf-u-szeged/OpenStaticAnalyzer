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

#include "java/inc/java.h"
#include "common/inc/WriteMessage.h"
#include "java/inc/messages.h"
#include <string.h>

#ifdef DEBUG_PREORDER
#include <iostream>
#endif


namespace columbus { namespace java { namespace asg {
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
  memset(traversaldCrossEdges,false,sizeof(bool)*105);
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

void AlgorithmPreorder::visitAllEdges(const base::BlockComment& node, bool callFirst /*= true*/){
  if (callFirst)
    visitAllEdges(dynamic_cast<const base::Base&>(node),false);
  visitAllEdges(dynamic_cast<const base::NonJavadocComment&>(node),false);
}

void AlgorithmPreorder::visit(const base::BlockComment& node, bool callFirst /*= true*/){
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

void AlgorithmPreorder::visitAllEdges(const base::Comment& node, bool callFirst /*= true*/){
  if (callFirst)
    visitAllEdges(dynamic_cast<const base::Base&>(node),false);
  visitAllEdges(dynamic_cast<const base::PositionedWithoutComment&>(node),false);
}

void AlgorithmPreorder::visitAllEdges(const base::Commentable& node, bool callFirst /*= true*/){
  if (callFirst)
    visitAllEdges(dynamic_cast<const base::Base&>(node),false);

  std::list<Visitor*>::iterator itVisitors;

  // edge: comments
  for (ListIterator<base::Comment> it = node.getCommentsListIteratorBegin(); it != node.getCommentsListIteratorEnd(); ++it) {
    const base::Comment& endNodeRef = *it;
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitCommentable_Comments(node, endNodeRef);
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
      if (traversaldCrossEdges[edkCommentable_Comments]) {
        endNodeRef.accept(*this);
      }
    }
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitEndCommentable_Comments(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;
  }
}

void AlgorithmPreorder::visitAllEdges(const base::JavadocComment& node, bool callFirst /*= true*/){
  if (callFirst)
    visitAllEdges(dynamic_cast<const base::Base&>(node),false);
  visitAllEdges(dynamic_cast<const base::Comment&>(node),false);
}

void AlgorithmPreorder::visit(const base::JavadocComment& node, bool callFirst /*= true*/){
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

void AlgorithmPreorder::visitAllEdges(const base::LineComment& node, bool callFirst /*= true*/){
  if (callFirst)
    visitAllEdges(dynamic_cast<const base::Base&>(node),false);
  visitAllEdges(dynamic_cast<const base::NonJavadocComment&>(node),false);
}

void AlgorithmPreorder::visit(const base::LineComment& node, bool callFirst /*= true*/){
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
  if (callFirst)
    visitAllEdges(dynamic_cast<const base::Base&>(node),false);
}

void AlgorithmPreorder::visitAllEdges(const base::NonJavadocComment& node, bool callFirst /*= true*/){
  if (callFirst)
    visitAllEdges(dynamic_cast<const base::Base&>(node),false);
  visitAllEdges(dynamic_cast<const base::Comment&>(node),false);
}

void AlgorithmPreorder::visitAllEdges(const base::Positioned& node, bool callFirst /*= true*/){
  if (callFirst)
    visitAllEdges(dynamic_cast<const base::Base&>(node),false);
  if (callFirst)
    visitAllEdges(dynamic_cast<const base::Commentable&>(node),false);
  visitAllEdges(dynamic_cast<const base::PositionedWithoutComment&>(node),false);
}

void AlgorithmPreorder::visitAllEdges(const base::PositionedWithoutComment& node, bool callFirst /*= true*/){
  if (callFirst)
    visitAllEdges(dynamic_cast<const base::Base&>(node),false);
}

void AlgorithmPreorder::visitAllEdges(const expr::Annotation& node, bool callFirst /*= true*/){
  if (callFirst)
    visitAllEdges(dynamic_cast<const base::Base&>(node),false);
  if (callFirst)
    visitAllEdges(dynamic_cast<const base::Commentable&>(node),false);
  visitAllEdges(dynamic_cast<const expr::Expression&>(node),false);

  std::list<Visitor*>::iterator itVisitors;

  const base::Base* genNodePtr;
  // edge: hasAnnotationName
  genNodePtr = node.getAnnotationName() ;
  if (genNodePtr) {
    const expr::TypeExpression& endNodeRef = dynamic_cast<const expr::TypeExpression&>(*genNodePtr);
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitAnnotation_HasAnnotationName(node, endNodeRef);
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
      (*itVisitors)->visitEndAnnotation_HasAnnotationName(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;
  }
}

void AlgorithmPreorder::visitAllEdges(const expr::ArrayAccess& node, bool callFirst /*= true*/){
  if (callFirst)
    visitAllEdges(dynamic_cast<const base::Base&>(node),false);
  if (callFirst)
    visitAllEdges(dynamic_cast<const base::Commentable&>(node),false);
  visitAllEdges(dynamic_cast<const expr::Binary&>(node),false);
}

void AlgorithmPreorder::visit(const expr::ArrayAccess& node, bool callFirst /*= true*/){
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

void AlgorithmPreorder::visitAllEdges(const expr::ArrayTypeExpression& node, bool callFirst /*= true*/){
  if (callFirst)
    visitAllEdges(dynamic_cast<const base::Base&>(node),false);
  if (callFirst)
    visitAllEdges(dynamic_cast<const base::Commentable&>(node),false);
  visitAllEdges(dynamic_cast<const expr::TypeExpression&>(node),false);

  std::list<Visitor*>::iterator itVisitors;

  const base::Base* genNodePtr;
  // edge: hasComponentType
  genNodePtr = node.getComponentType() ;
  if (genNodePtr) {
    const expr::TypeExpression& endNodeRef = dynamic_cast<const expr::TypeExpression&>(*genNodePtr);
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitArrayTypeExpression_HasComponentType(node, endNodeRef);
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
      (*itVisitors)->visitEndArrayTypeExpression_HasComponentType(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;
  }
}

void AlgorithmPreorder::visit(const expr::ArrayTypeExpression& node, bool callFirst /*= true*/){
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

void AlgorithmPreorder::visitAllEdges(const expr::Assignment& node, bool callFirst /*= true*/){
  if (callFirst)
    visitAllEdges(dynamic_cast<const base::Base&>(node),false);
  if (callFirst)
    visitAllEdges(dynamic_cast<const base::Commentable&>(node),false);
  visitAllEdges(dynamic_cast<const expr::Binary&>(node),false);
}

void AlgorithmPreorder::visit(const expr::Assignment& node, bool callFirst /*= true*/){
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

void AlgorithmPreorder::visitAllEdges(const expr::Binary& node, bool callFirst /*= true*/){
  if (callFirst)
    visitAllEdges(dynamic_cast<const base::Base&>(node),false);
  if (callFirst)
    visitAllEdges(dynamic_cast<const base::Commentable&>(node),false);
  visitAllEdges(dynamic_cast<const expr::Expression&>(node),false);

  std::list<Visitor*>::iterator itVisitors;

  const base::Base* genNodePtr;
  // edge: hasLeftOperand
  genNodePtr = node.getLeftOperand() ;
  if (genNodePtr) {
    const expr::Expression& endNodeRef = dynamic_cast<const expr::Expression&>(*genNodePtr);
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitBinary_HasLeftOperand(node, endNodeRef);
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
      (*itVisitors)->visitEndBinary_HasLeftOperand(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;
  }

  // edge: hasRightOperand
  genNodePtr = node.getRightOperand() ;
  if (genNodePtr) {
    const expr::Expression& endNodeRef = dynamic_cast<const expr::Expression&>(*genNodePtr);
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitBinary_HasRightOperand(node, endNodeRef);
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
      (*itVisitors)->visitEndBinary_HasRightOperand(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;
  }
}

void AlgorithmPreorder::visitAllEdges(const expr::BooleanLiteral& node, bool callFirst /*= true*/){
  if (callFirst)
    visitAllEdges(dynamic_cast<const base::Base&>(node),false);
  if (callFirst)
    visitAllEdges(dynamic_cast<const base::Commentable&>(node),false);
  visitAllEdges(dynamic_cast<const expr::Literal&>(node),false);
}

void AlgorithmPreorder::visit(const expr::BooleanLiteral& node, bool callFirst /*= true*/){
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

void AlgorithmPreorder::visitAllEdges(const expr::CharacterLiteral& node, bool callFirst /*= true*/){
  if (callFirst)
    visitAllEdges(dynamic_cast<const base::Base&>(node),false);
  if (callFirst)
    visitAllEdges(dynamic_cast<const base::Commentable&>(node),false);
  visitAllEdges(dynamic_cast<const expr::Literal&>(node),false);
}

void AlgorithmPreorder::visit(const expr::CharacterLiteral& node, bool callFirst /*= true*/){
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

void AlgorithmPreorder::visitAllEdges(const expr::ClassLiteral& node, bool callFirst /*= true*/){
  if (callFirst)
    visitAllEdges(dynamic_cast<const base::Base&>(node),false);
  if (callFirst)
    visitAllEdges(dynamic_cast<const base::Commentable&>(node),false);
  visitAllEdges(dynamic_cast<const expr::Literal&>(node),false);

  std::list<Visitor*>::iterator itVisitors;

  const base::Base* genNodePtr;
  // edge: hasComponentType
  genNodePtr = node.getComponentType() ;
  if (genNodePtr) {
    const expr::TypeExpression& endNodeRef = dynamic_cast<const expr::TypeExpression&>(*genNodePtr);
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitClassLiteral_HasComponentType(node, endNodeRef);
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
      (*itVisitors)->visitEndClassLiteral_HasComponentType(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;
  }
}

void AlgorithmPreorder::visit(const expr::ClassLiteral& node, bool callFirst /*= true*/){
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

void AlgorithmPreorder::visitAllEdges(const expr::Conditional& node, bool callFirst /*= true*/){
  if (callFirst)
    visitAllEdges(dynamic_cast<const base::Base&>(node),false);
  if (callFirst)
    visitAllEdges(dynamic_cast<const base::Commentable&>(node),false);
  visitAllEdges(dynamic_cast<const expr::Expression&>(node),false);

  std::list<Visitor*>::iterator itVisitors;

  const base::Base* genNodePtr;
  // edge: hasCondition
  genNodePtr = node.getCondition() ;
  if (genNodePtr) {
    const expr::Expression& endNodeRef = dynamic_cast<const expr::Expression&>(*genNodePtr);
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitConditional_HasCondition(node, endNodeRef);
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
      (*itVisitors)->visitEndConditional_HasCondition(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;
  }

  // edge: hasTrueExpression
  genNodePtr = node.getTrueExpression() ;
  if (genNodePtr) {
    const expr::Expression& endNodeRef = dynamic_cast<const expr::Expression&>(*genNodePtr);
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitConditional_HasTrueExpression(node, endNodeRef);
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
      (*itVisitors)->visitEndConditional_HasTrueExpression(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;
  }

  // edge: hasFalseExpression
  genNodePtr = node.getFalseExpression() ;
  if (genNodePtr) {
    const expr::Expression& endNodeRef = dynamic_cast<const expr::Expression&>(*genNodePtr);
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitConditional_HasFalseExpression(node, endNodeRef);
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
      (*itVisitors)->visitEndConditional_HasFalseExpression(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;
  }
}

void AlgorithmPreorder::visit(const expr::Conditional& node, bool callFirst /*= true*/){
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

void AlgorithmPreorder::visitAllEdges(const expr::DoubleLiteral& node, bool callFirst /*= true*/){
  if (callFirst)
    visitAllEdges(dynamic_cast<const base::Base&>(node),false);
  if (callFirst)
    visitAllEdges(dynamic_cast<const base::Commentable&>(node),false);
  visitAllEdges(dynamic_cast<const expr::NumberLiteral&>(node),false);
}

void AlgorithmPreorder::visit(const expr::DoubleLiteral& node, bool callFirst /*= true*/){
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

void AlgorithmPreorder::visitAllEdges(const expr::Erroneous& node, bool callFirst /*= true*/){
  if (callFirst)
    visitAllEdges(dynamic_cast<const base::Base&>(node),false);
  if (callFirst)
    visitAllEdges(dynamic_cast<const base::Commentable&>(node),false);
  visitAllEdges(dynamic_cast<const expr::Expression&>(node),false);

  std::list<Visitor*>::iterator itVisitors;

  // edge: hasErrors
  for (ListIterator<base::Positioned> it = node.getErrorsListIteratorBegin(); it != node.getErrorsListIteratorEnd(); ++it) {
    const base::Positioned& endNodeRef = *it;
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitErroneous_HasErrors(node, endNodeRef);
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
      (*itVisitors)->visitEndErroneous_HasErrors(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;
  }
}

void AlgorithmPreorder::visit(const expr::Erroneous& node, bool callFirst /*= true*/){
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

void AlgorithmPreorder::visitAllEdges(const expr::ErroneousTypeExpression& node, bool callFirst /*= true*/){
  if (callFirst)
    visitAllEdges(dynamic_cast<const base::Base&>(node),false);
  if (callFirst)
    visitAllEdges(dynamic_cast<const base::Commentable&>(node),false);
  visitAllEdges(dynamic_cast<const expr::TypeExpression&>(node),false);

  std::list<Visitor*>::iterator itVisitors;

  // edge: hasErrors
  for (ListIterator<base::Positioned> it = node.getErrorsListIteratorBegin(); it != node.getErrorsListIteratorEnd(); ++it) {
    const base::Positioned& endNodeRef = *it;
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitErroneousTypeExpression_HasErrors(node, endNodeRef);
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
      (*itVisitors)->visitEndErroneousTypeExpression_HasErrors(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;
  }
}

void AlgorithmPreorder::visit(const expr::ErroneousTypeExpression& node, bool callFirst /*= true*/){
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

void AlgorithmPreorder::visitAllEdges(const expr::Expression& node, bool callFirst /*= true*/){
  if (callFirst)
    visitAllEdges(dynamic_cast<const base::Base&>(node),false);
  if (callFirst)
    visitAllEdges(dynamic_cast<const base::Commentable&>(node),false);
  visitAllEdges(dynamic_cast<const base::Positioned&>(node),false);

  std::list<Visitor*>::iterator itVisitors;

  const base::Base* genNodePtr;
  // edge: type
  genNodePtr = node.getType() ;
  if (genNodePtr) {
    const type::Type& endNodeRef = dynamic_cast<const type::Type&>(*genNodePtr);
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitExpression_Type(node, endNodeRef);
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
      if (traversaldCrossEdges[edkExpression_Type]) {
        endNodeRef.accept(*this);
      }
    }
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitEndExpression_Type(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;
  }
}

void AlgorithmPreorder::visitAllEdges(const expr::ExternalTypeExpression& node, bool callFirst /*= true*/){
  if (callFirst)
    visitAllEdges(dynamic_cast<const base::Base&>(node),false);
  if (callFirst)
    visitAllEdges(dynamic_cast<const base::Commentable&>(node),false);
  visitAllEdges(dynamic_cast<const expr::TypeExpression&>(node),false);
}

void AlgorithmPreorder::visit(const expr::ExternalTypeExpression& node, bool callFirst /*= true*/){
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

void AlgorithmPreorder::visitAllEdges(const expr::FieldAccess& node, bool callFirst /*= true*/){
  if (callFirst)
    visitAllEdges(dynamic_cast<const base::Base&>(node),false);
  if (callFirst)
    visitAllEdges(dynamic_cast<const base::Commentable&>(node),false);
  visitAllEdges(dynamic_cast<const expr::Binary&>(node),false);
}

void AlgorithmPreorder::visit(const expr::FieldAccess& node, bool callFirst /*= true*/){
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

void AlgorithmPreorder::visitAllEdges(const expr::FloatLiteral& node, bool callFirst /*= true*/){
  if (callFirst)
    visitAllEdges(dynamic_cast<const base::Base&>(node),false);
  if (callFirst)
    visitAllEdges(dynamic_cast<const base::Commentable&>(node),false);
  visitAllEdges(dynamic_cast<const expr::NumberLiteral&>(node),false);
}

void AlgorithmPreorder::visit(const expr::FloatLiteral& node, bool callFirst /*= true*/){
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

void AlgorithmPreorder::visitAllEdges(const expr::Identifier& node, bool callFirst /*= true*/){
  if (callFirst)
    visitAllEdges(dynamic_cast<const base::Base&>(node),false);
  if (callFirst)
    visitAllEdges(dynamic_cast<const base::Commentable&>(node),false);
  visitAllEdges(dynamic_cast<const expr::Expression&>(node),false);

  std::list<Visitor*>::iterator itVisitors;

  const base::Base* genNodePtr;
  // edge: refersTo
  genNodePtr = node.getRefersTo() ;
  if (genNodePtr) {
    const base::Named& endNodeRef = dynamic_cast<const base::Named&>(*genNodePtr);
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

void AlgorithmPreorder::visit(const expr::Identifier& node, bool callFirst /*= true*/){
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

void AlgorithmPreorder::visitAllEdges(const expr::InfixExpression& node, bool callFirst /*= true*/){
  if (callFirst)
    visitAllEdges(dynamic_cast<const base::Base&>(node),false);
  if (callFirst)
    visitAllEdges(dynamic_cast<const base::Commentable&>(node),false);
  visitAllEdges(dynamic_cast<const expr::Binary&>(node),false);
}

void AlgorithmPreorder::visit(const expr::InfixExpression& node, bool callFirst /*= true*/){
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

void AlgorithmPreorder::visitAllEdges(const expr::InstanceOf& node, bool callFirst /*= true*/){
  if (callFirst)
    visitAllEdges(dynamic_cast<const base::Base&>(node),false);
  if (callFirst)
    visitAllEdges(dynamic_cast<const base::Commentable&>(node),false);
  visitAllEdges(dynamic_cast<const expr::Unary&>(node),false);

  std::list<Visitor*>::iterator itVisitors;

  const base::Base* genNodePtr;
  // edge: hasTypeOperand
  genNodePtr = node.getTypeOperand() ;
  if (genNodePtr) {
    const expr::TypeExpression& endNodeRef = dynamic_cast<const expr::TypeExpression&>(*genNodePtr);
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitInstanceOf_HasTypeOperand(node, endNodeRef);
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
      (*itVisitors)->visitEndInstanceOf_HasTypeOperand(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;
  }
}

void AlgorithmPreorder::visit(const expr::InstanceOf& node, bool callFirst /*= true*/){
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

void AlgorithmPreorder::visitAllEdges(const expr::IntegerLiteral& node, bool callFirst /*= true*/){
  if (callFirst)
    visitAllEdges(dynamic_cast<const base::Base&>(node),false);
  if (callFirst)
    visitAllEdges(dynamic_cast<const base::Commentable&>(node),false);
  visitAllEdges(dynamic_cast<const expr::NumberLiteral&>(node),false);
}

void AlgorithmPreorder::visit(const expr::IntegerLiteral& node, bool callFirst /*= true*/){
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

void AlgorithmPreorder::visitAllEdges(const expr::Literal& node, bool callFirst /*= true*/){
  if (callFirst)
    visitAllEdges(dynamic_cast<const base::Base&>(node),false);
  if (callFirst)
    visitAllEdges(dynamic_cast<const base::Commentable&>(node),false);
  visitAllEdges(dynamic_cast<const expr::Expression&>(node),false);
}

void AlgorithmPreorder::visitAllEdges(const expr::LongLiteral& node, bool callFirst /*= true*/){
  if (callFirst)
    visitAllEdges(dynamic_cast<const base::Base&>(node),false);
  if (callFirst)
    visitAllEdges(dynamic_cast<const base::Commentable&>(node),false);
  visitAllEdges(dynamic_cast<const expr::NumberLiteral&>(node),false);
}

void AlgorithmPreorder::visit(const expr::LongLiteral& node, bool callFirst /*= true*/){
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

void AlgorithmPreorder::visitAllEdges(const expr::MarkerAnnotation& node, bool callFirst /*= true*/){
  if (callFirst)
    visitAllEdges(dynamic_cast<const base::Base&>(node),false);
  if (callFirst)
    visitAllEdges(dynamic_cast<const base::Commentable&>(node),false);
  visitAllEdges(dynamic_cast<const expr::Annotation&>(node),false);
}

void AlgorithmPreorder::visit(const expr::MarkerAnnotation& node, bool callFirst /*= true*/){
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

void AlgorithmPreorder::visitAllEdges(const expr::MethodInvocation& node, bool callFirst /*= true*/){
  if (callFirst)
    visitAllEdges(dynamic_cast<const base::Base&>(node),false);
  if (callFirst)
    visitAllEdges(dynamic_cast<const base::Commentable&>(node),false);
  visitAllEdges(dynamic_cast<const expr::Unary&>(node),false);

  std::list<Visitor*>::iterator itVisitors;

  // edge: hasTypeArguments
  for (ListIterator<expr::TypeExpression> it = node.getTypeArgumentsListIteratorBegin(); it != node.getTypeArgumentsListIteratorEnd(); ++it) {
    const expr::TypeExpression& endNodeRef = *it;
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitMethodInvocation_HasTypeArguments(node, endNodeRef);
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
      (*itVisitors)->visitEndMethodInvocation_HasTypeArguments(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;
  }

  // edge: hasArguments
  for (ListIterator<expr::Expression> it = node.getArgumentsListIteratorBegin(); it != node.getArgumentsListIteratorEnd(); ++it) {
    const expr::Expression& endNodeRef = *it;
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitMethodInvocation_HasArguments(node, endNodeRef);
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
      (*itVisitors)->visitEndMethodInvocation_HasArguments(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;
  }

  const base::Base* genNodePtr;
  // edge: invokes
  genNodePtr = node.getInvokes() ;
  if (genNodePtr) {
    const struc::MethodDeclaration& endNodeRef = dynamic_cast<const struc::MethodDeclaration&>(*genNodePtr);
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitMethodInvocation_Invokes(node, endNodeRef);
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
      if (traversaldCrossEdges[edkMethodInvocation_Invokes]) {
        endNodeRef.accept(*this);
      }
    }
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitEndMethodInvocation_Invokes(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;
  }
}

void AlgorithmPreorder::visit(const expr::MethodInvocation& node, bool callFirst /*= true*/){
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

void AlgorithmPreorder::visitAllEdges(const expr::NewArray& node, bool callFirst /*= true*/){
  if (callFirst)
    visitAllEdges(dynamic_cast<const base::Base&>(node),false);
  if (callFirst)
    visitAllEdges(dynamic_cast<const base::Commentable&>(node),false);
  visitAllEdges(dynamic_cast<const expr::Expression&>(node),false);

  std::list<Visitor*>::iterator itVisitors;

  const base::Base* genNodePtr;
  // edge: hasComponentType
  genNodePtr = node.getComponentType() ;
  if (genNodePtr) {
    const expr::TypeExpression& endNodeRef = dynamic_cast<const expr::TypeExpression&>(*genNodePtr);
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitNewArray_HasComponentType(node, endNodeRef);
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
      (*itVisitors)->visitEndNewArray_HasComponentType(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;
  }

  // edge: hasDimensions
  for (ListIterator<expr::Expression> it = node.getDimensionsListIteratorBegin(); it != node.getDimensionsListIteratorEnd(); ++it) {
    const expr::Expression& endNodeRef = *it;
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitNewArray_HasDimensions(node, endNodeRef);
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
      (*itVisitors)->visitEndNewArray_HasDimensions(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;
  }

  // edge: hasInitializers
  for (ListIterator<expr::Expression> it = node.getInitializersListIteratorBegin(); it != node.getInitializersListIteratorEnd(); ++it) {
    const expr::Expression& endNodeRef = *it;
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitNewArray_HasInitializers(node, endNodeRef);
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
      (*itVisitors)->visitEndNewArray_HasInitializers(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;
  }
}

void AlgorithmPreorder::visit(const expr::NewArray& node, bool callFirst /*= true*/){
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

void AlgorithmPreorder::visitAllEdges(const expr::NewClass& node, bool callFirst /*= true*/){
  if (callFirst)
    visitAllEdges(dynamic_cast<const base::Base&>(node),false);
  if (callFirst)
    visitAllEdges(dynamic_cast<const base::Commentable&>(node),false);
  visitAllEdges(dynamic_cast<const expr::Expression&>(node),false);

  std::list<Visitor*>::iterator itVisitors;

  const base::Base* genNodePtr;
  // edge: hasEnclosingExpression
  genNodePtr = node.getEnclosingExpression() ;
  if (genNodePtr) {
    const expr::Expression& endNodeRef = dynamic_cast<const expr::Expression&>(*genNodePtr);
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitNewClass_HasEnclosingExpression(node, endNodeRef);
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
      (*itVisitors)->visitEndNewClass_HasEnclosingExpression(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;
  }

  // edge: hasTypeArguments
  for (ListIterator<expr::TypeExpression> it = node.getTypeArgumentsListIteratorBegin(); it != node.getTypeArgumentsListIteratorEnd(); ++it) {
    const expr::TypeExpression& endNodeRef = *it;
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitNewClass_HasTypeArguments(node, endNodeRef);
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
      (*itVisitors)->visitEndNewClass_HasTypeArguments(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;
  }

  // edge: hasTypeName
  genNodePtr = node.getTypeName() ;
  if (genNodePtr) {
    const expr::TypeExpression& endNodeRef = dynamic_cast<const expr::TypeExpression&>(*genNodePtr);
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitNewClass_HasTypeName(node, endNodeRef);
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
      (*itVisitors)->visitEndNewClass_HasTypeName(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;
  }

  // edge: hasArguments
  for (ListIterator<expr::Expression> it = node.getArgumentsListIteratorBegin(); it != node.getArgumentsListIteratorEnd(); ++it) {
    const expr::Expression& endNodeRef = *it;
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitNewClass_HasArguments(node, endNodeRef);
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
      (*itVisitors)->visitEndNewClass_HasArguments(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;
  }

  // edge: hasAnonymousClass
  genNodePtr = node.getAnonymousClass() ;
  if (genNodePtr) {
    const struc::AnonymousClass& endNodeRef = dynamic_cast<const struc::AnonymousClass&>(*genNodePtr);
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitNewClass_HasAnonymousClass(node, endNodeRef);
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
      (*itVisitors)->visitEndNewClass_HasAnonymousClass(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;
  }

  // edge: constructor
  genNodePtr = node.getConstructor() ;
  if (genNodePtr) {
    const struc::NormalMethod& endNodeRef = dynamic_cast<const struc::NormalMethod&>(*genNodePtr);
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitNewClass_Constructor(node, endNodeRef);
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
      if (traversaldCrossEdges[edkNewClass_Constructor]) {
        endNodeRef.accept(*this);
      }
    }
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitEndNewClass_Constructor(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;
  }
}

void AlgorithmPreorder::visit(const expr::NewClass& node, bool callFirst /*= true*/){
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

void AlgorithmPreorder::visitAllEdges(const expr::NormalAnnotation& node, bool callFirst /*= true*/){
  if (callFirst)
    visitAllEdges(dynamic_cast<const base::Base&>(node),false);
  if (callFirst)
    visitAllEdges(dynamic_cast<const base::Commentable&>(node),false);
  visitAllEdges(dynamic_cast<const expr::Annotation&>(node),false);

  std::list<Visitor*>::iterator itVisitors;

  // edge: hasArguments
  for (ListIterator<expr::Expression> it = node.getArgumentsListIteratorBegin(); it != node.getArgumentsListIteratorEnd(); ++it) {
    const expr::Expression& endNodeRef = *it;
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitNormalAnnotation_HasArguments(node, endNodeRef);
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
      (*itVisitors)->visitEndNormalAnnotation_HasArguments(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;
  }
}

void AlgorithmPreorder::visit(const expr::NormalAnnotation& node, bool callFirst /*= true*/){
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

void AlgorithmPreorder::visitAllEdges(const expr::NullLiteral& node, bool callFirst /*= true*/){
  if (callFirst)
    visitAllEdges(dynamic_cast<const base::Base&>(node),false);
  if (callFirst)
    visitAllEdges(dynamic_cast<const base::Commentable&>(node),false);
  visitAllEdges(dynamic_cast<const expr::Literal&>(node),false);
}

void AlgorithmPreorder::visit(const expr::NullLiteral& node, bool callFirst /*= true*/){
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

void AlgorithmPreorder::visitAllEdges(const expr::NumberLiteral& node, bool callFirst /*= true*/){
  if (callFirst)
    visitAllEdges(dynamic_cast<const base::Base&>(node),false);
  if (callFirst)
    visitAllEdges(dynamic_cast<const base::Commentable&>(node),false);
  visitAllEdges(dynamic_cast<const expr::Literal&>(node),false);
}

void AlgorithmPreorder::visitAllEdges(const expr::ParenthesizedExpression& node, bool callFirst /*= true*/){
  if (callFirst)
    visitAllEdges(dynamic_cast<const base::Base&>(node),false);
  if (callFirst)
    visitAllEdges(dynamic_cast<const base::Commentable&>(node),false);
  visitAllEdges(dynamic_cast<const expr::Unary&>(node),false);
}

void AlgorithmPreorder::visit(const expr::ParenthesizedExpression& node, bool callFirst /*= true*/){
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

void AlgorithmPreorder::visitAllEdges(const expr::PostfixExpression& node, bool callFirst /*= true*/){
  if (callFirst)
    visitAllEdges(dynamic_cast<const base::Base&>(node),false);
  if (callFirst)
    visitAllEdges(dynamic_cast<const base::Commentable&>(node),false);
  visitAllEdges(dynamic_cast<const expr::Unary&>(node),false);
}

void AlgorithmPreorder::visit(const expr::PostfixExpression& node, bool callFirst /*= true*/){
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

void AlgorithmPreorder::visitAllEdges(const expr::PrefixExpression& node, bool callFirst /*= true*/){
  if (callFirst)
    visitAllEdges(dynamic_cast<const base::Base&>(node),false);
  if (callFirst)
    visitAllEdges(dynamic_cast<const base::Commentable&>(node),false);
  visitAllEdges(dynamic_cast<const expr::Unary&>(node),false);
}

void AlgorithmPreorder::visit(const expr::PrefixExpression& node, bool callFirst /*= true*/){
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

void AlgorithmPreorder::visitAllEdges(const expr::PrimitiveTypeExpression& node, bool callFirst /*= true*/){
  if (callFirst)
    visitAllEdges(dynamic_cast<const base::Base&>(node),false);
  if (callFirst)
    visitAllEdges(dynamic_cast<const base::Commentable&>(node),false);
  visitAllEdges(dynamic_cast<const expr::TypeExpression&>(node),false);
}

void AlgorithmPreorder::visit(const expr::PrimitiveTypeExpression& node, bool callFirst /*= true*/){
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

void AlgorithmPreorder::visitAllEdges(const expr::QualifiedTypeExpression& node, bool callFirst /*= true*/){
  if (callFirst)
    visitAllEdges(dynamic_cast<const base::Base&>(node),false);
  if (callFirst)
    visitAllEdges(dynamic_cast<const base::Commentable&>(node),false);
  visitAllEdges(dynamic_cast<const expr::TypeExpression&>(node),false);

  std::list<Visitor*>::iterator itVisitors;

  const base::Base* genNodePtr;
  // edge: hasQualifierType
  genNodePtr = node.getQualifierType() ;
  if (genNodePtr) {
    const expr::TypeExpression& endNodeRef = dynamic_cast<const expr::TypeExpression&>(*genNodePtr);
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitQualifiedTypeExpression_HasQualifierType(node, endNodeRef);
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
      (*itVisitors)->visitEndQualifiedTypeExpression_HasQualifierType(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;
  }

  // edge: hasSimpleType
  genNodePtr = node.getSimpleType() ;
  if (genNodePtr) {
    const expr::SimpleTypeExpression& endNodeRef = dynamic_cast<const expr::SimpleTypeExpression&>(*genNodePtr);
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitQualifiedTypeExpression_HasSimpleType(node, endNodeRef);
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
      (*itVisitors)->visitEndQualifiedTypeExpression_HasSimpleType(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;
  }
}

void AlgorithmPreorder::visit(const expr::QualifiedTypeExpression& node, bool callFirst /*= true*/){
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

void AlgorithmPreorder::visitAllEdges(const expr::SimpleTypeExpression& node, bool callFirst /*= true*/){
  if (callFirst)
    visitAllEdges(dynamic_cast<const base::Base&>(node),false);
  if (callFirst)
    visitAllEdges(dynamic_cast<const base::Commentable&>(node),false);
  visitAllEdges(dynamic_cast<const expr::TypeExpression&>(node),false);
}

void AlgorithmPreorder::visit(const expr::SimpleTypeExpression& node, bool callFirst /*= true*/){
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

void AlgorithmPreorder::visitAllEdges(const expr::SingleElementAnnotation& node, bool callFirst /*= true*/){
  if (callFirst)
    visitAllEdges(dynamic_cast<const base::Base&>(node),false);
  if (callFirst)
    visitAllEdges(dynamic_cast<const base::Commentable&>(node),false);
  visitAllEdges(dynamic_cast<const expr::Annotation&>(node),false);

  std::list<Visitor*>::iterator itVisitors;

  const base::Base* genNodePtr;
  // edge: hasArgument
  genNodePtr = node.getArgument() ;
  if (genNodePtr) {
    const expr::Expression& endNodeRef = dynamic_cast<const expr::Expression&>(*genNodePtr);
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitSingleElementAnnotation_HasArgument(node, endNodeRef);
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
      (*itVisitors)->visitEndSingleElementAnnotation_HasArgument(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;
  }
}

void AlgorithmPreorder::visit(const expr::SingleElementAnnotation& node, bool callFirst /*= true*/){
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

void AlgorithmPreorder::visitAllEdges(const expr::StringLiteral& node, bool callFirst /*= true*/){
  if (callFirst)
    visitAllEdges(dynamic_cast<const base::Base&>(node),false);
  if (callFirst)
    visitAllEdges(dynamic_cast<const base::Commentable&>(node),false);
  visitAllEdges(dynamic_cast<const expr::Literal&>(node),false);
}

void AlgorithmPreorder::visit(const expr::StringLiteral& node, bool callFirst /*= true*/){
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

void AlgorithmPreorder::visitAllEdges(const expr::Super& node, bool callFirst /*= true*/){
  if (callFirst)
    visitAllEdges(dynamic_cast<const base::Base&>(node),false);
  if (callFirst)
    visitAllEdges(dynamic_cast<const base::Commentable&>(node),false);
  visitAllEdges(dynamic_cast<const expr::Expression&>(node),false);
}

void AlgorithmPreorder::visit(const expr::Super& node, bool callFirst /*= true*/){
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

void AlgorithmPreorder::visitAllEdges(const expr::This& node, bool callFirst /*= true*/){
  if (callFirst)
    visitAllEdges(dynamic_cast<const base::Base&>(node),false);
  if (callFirst)
    visitAllEdges(dynamic_cast<const base::Commentable&>(node),false);
  visitAllEdges(dynamic_cast<const expr::Expression&>(node),false);
}

void AlgorithmPreorder::visit(const expr::This& node, bool callFirst /*= true*/){
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

void AlgorithmPreorder::visitAllEdges(const expr::TypeApplyExpression& node, bool callFirst /*= true*/){
  if (callFirst)
    visitAllEdges(dynamic_cast<const base::Base&>(node),false);
  if (callFirst)
    visitAllEdges(dynamic_cast<const base::Commentable&>(node),false);
  visitAllEdges(dynamic_cast<const expr::TypeExpression&>(node),false);

  std::list<Visitor*>::iterator itVisitors;

  const base::Base* genNodePtr;
  // edge: hasRawType
  genNodePtr = node.getRawType() ;
  if (genNodePtr) {
    const expr::TypeExpression& endNodeRef = dynamic_cast<const expr::TypeExpression&>(*genNodePtr);
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitTypeApplyExpression_HasRawType(node, endNodeRef);
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
      (*itVisitors)->visitEndTypeApplyExpression_HasRawType(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;
  }

  // edge: hasTypeArguments
  for (ListIterator<expr::TypeExpression> it = node.getTypeArgumentsListIteratorBegin(); it != node.getTypeArgumentsListIteratorEnd(); ++it) {
    const expr::TypeExpression& endNodeRef = *it;
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitTypeApplyExpression_HasTypeArguments(node, endNodeRef);
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
      (*itVisitors)->visitEndTypeApplyExpression_HasTypeArguments(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;
  }
}

void AlgorithmPreorder::visit(const expr::TypeApplyExpression& node, bool callFirst /*= true*/){
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

void AlgorithmPreorder::visitAllEdges(const expr::TypeCast& node, bool callFirst /*= true*/){
  if (callFirst)
    visitAllEdges(dynamic_cast<const base::Base&>(node),false);
  if (callFirst)
    visitAllEdges(dynamic_cast<const base::Commentable&>(node),false);
  visitAllEdges(dynamic_cast<const expr::Unary&>(node),false);

  std::list<Visitor*>::iterator itVisitors;

  const base::Base* genNodePtr;
  // edge: hasTypeOperand
  genNodePtr = node.getTypeOperand() ;
  if (genNodePtr) {
    const expr::TypeExpression& endNodeRef = dynamic_cast<const expr::TypeExpression&>(*genNodePtr);
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitTypeCast_HasTypeOperand(node, endNodeRef);
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
      (*itVisitors)->visitEndTypeCast_HasTypeOperand(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;
  }
}

void AlgorithmPreorder::visit(const expr::TypeCast& node, bool callFirst /*= true*/){
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

void AlgorithmPreorder::visitAllEdges(const expr::TypeExpression& node, bool callFirst /*= true*/){
  if (callFirst)
    visitAllEdges(dynamic_cast<const base::Base&>(node),false);
  if (callFirst)
    visitAllEdges(dynamic_cast<const base::Commentable&>(node),false);
  visitAllEdges(dynamic_cast<const expr::Expression&>(node),false);
}

void AlgorithmPreorder::visitAllEdges(const expr::TypeUnionExpression& node, bool callFirst /*= true*/){
  if (callFirst)
    visitAllEdges(dynamic_cast<const base::Base&>(node),false);
  if (callFirst)
    visitAllEdges(dynamic_cast<const base::Commentable&>(node),false);
  visitAllEdges(dynamic_cast<const expr::TypeExpression&>(node),false);

  std::list<Visitor*>::iterator itVisitors;

  // edge: hasAlternatives
  for (ListIterator<expr::TypeExpression> it = node.getAlternativesListIteratorBegin(); it != node.getAlternativesListIteratorEnd(); ++it) {
    const expr::TypeExpression& endNodeRef = *it;
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitTypeUnionExpression_HasAlternatives(node, endNodeRef);
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
      (*itVisitors)->visitEndTypeUnionExpression_HasAlternatives(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;
  }
}

void AlgorithmPreorder::visit(const expr::TypeUnionExpression& node, bool callFirst /*= true*/){
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

void AlgorithmPreorder::visitAllEdges(const expr::Unary& node, bool callFirst /*= true*/){
  if (callFirst)
    visitAllEdges(dynamic_cast<const base::Base&>(node),false);
  if (callFirst)
    visitAllEdges(dynamic_cast<const base::Commentable&>(node),false);
  visitAllEdges(dynamic_cast<const expr::Expression&>(node),false);

  std::list<Visitor*>::iterator itVisitors;

  const base::Base* genNodePtr;
  // edge: hasOperand
  genNodePtr = node.getOperand() ;
  if (genNodePtr) {
    const expr::Expression& endNodeRef = dynamic_cast<const expr::Expression&>(*genNodePtr);
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitUnary_HasOperand(node, endNodeRef);
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
      (*itVisitors)->visitEndUnary_HasOperand(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;
  }
}

void AlgorithmPreorder::visitAllEdges(const expr::WildcardExpression& node, bool callFirst /*= true*/){
  if (callFirst)
    visitAllEdges(dynamic_cast<const base::Base&>(node),false);
  if (callFirst)
    visitAllEdges(dynamic_cast<const base::Commentable&>(node),false);
  visitAllEdges(dynamic_cast<const expr::TypeExpression&>(node),false);

  std::list<Visitor*>::iterator itVisitors;

  const base::Base* genNodePtr;
  // edge: hasBound
  genNodePtr = node.getBound() ;
  if (genNodePtr) {
    const expr::TypeExpression& endNodeRef = dynamic_cast<const expr::TypeExpression&>(*genNodePtr);
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitWildcardExpression_HasBound(node, endNodeRef);
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
      (*itVisitors)->visitEndWildcardExpression_HasBound(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;
  }
}

void AlgorithmPreorder::visit(const expr::WildcardExpression& node, bool callFirst /*= true*/){
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

void AlgorithmPreorder::visitAllEdges(const statm::Assert& node, bool callFirst /*= true*/){
  if (callFirst)
    visitAllEdges(dynamic_cast<const base::Base&>(node),false);
  if (callFirst)
    visitAllEdges(dynamic_cast<const base::Commentable&>(node),false);
  visitAllEdges(dynamic_cast<const statm::Statement&>(node),false);

  std::list<Visitor*>::iterator itVisitors;

  const base::Base* genNodePtr;
  // edge: hasCondition
  genNodePtr = node.getCondition() ;
  if (genNodePtr) {
    const expr::Expression& endNodeRef = dynamic_cast<const expr::Expression&>(*genNodePtr);
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitAssert_HasCondition(node, endNodeRef);
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
      (*itVisitors)->visitEndAssert_HasCondition(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;
  }

  // edge: hasDetail
  genNodePtr = node.getDetail() ;
  if (genNodePtr) {
    const expr::Expression& endNodeRef = dynamic_cast<const expr::Expression&>(*genNodePtr);
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitAssert_HasDetail(node, endNodeRef);
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
      (*itVisitors)->visitEndAssert_HasDetail(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;
  }
}

void AlgorithmPreorder::visit(const statm::Assert& node, bool callFirst /*= true*/){
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

void AlgorithmPreorder::visitAllEdges(const statm::BasicFor& node, bool callFirst /*= true*/){
  if (callFirst)
    visitAllEdges(dynamic_cast<const base::Base&>(node),false);
  if (callFirst)
    visitAllEdges(dynamic_cast<const base::Commentable&>(node),false);
  visitAllEdges(dynamic_cast<const statm::For&>(node),false);

  std::list<Visitor*>::iterator itVisitors;

  // edge: hasInitializers
  for (ListIterator<statm::Statement> it = node.getInitializersListIteratorBegin(); it != node.getInitializersListIteratorEnd(); ++it) {
    const statm::Statement& endNodeRef = *it;
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitBasicFor_HasInitializers(node, endNodeRef);
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
      (*itVisitors)->visitEndBasicFor_HasInitializers(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;
  }

  const base::Base* genNodePtr;
  // edge: hasCondition
  genNodePtr = node.getCondition() ;
  if (genNodePtr) {
    const expr::Expression& endNodeRef = dynamic_cast<const expr::Expression&>(*genNodePtr);
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitBasicFor_HasCondition(node, endNodeRef);
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
      (*itVisitors)->visitEndBasicFor_HasCondition(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;
  }

  // edge: hasUpdates
  for (ListIterator<statm::Statement> it = node.getUpdatesListIteratorBegin(); it != node.getUpdatesListIteratorEnd(); ++it) {
    const statm::Statement& endNodeRef = *it;
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitBasicFor_HasUpdates(node, endNodeRef);
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
      (*itVisitors)->visitEndBasicFor_HasUpdates(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;
  }
}

void AlgorithmPreorder::visit(const statm::BasicFor& node, bool callFirst /*= true*/){
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

void AlgorithmPreorder::visitAllEdges(const statm::Block& node, bool callFirst /*= true*/){
  if (callFirst)
    visitAllEdges(dynamic_cast<const base::Base&>(node),false);
  if (callFirst)
    visitAllEdges(dynamic_cast<const base::Commentable&>(node),false);
  visitAllEdges(dynamic_cast<const statm::Statement&>(node),false);

  std::list<Visitor*>::iterator itVisitors;

  // edge: hasStatements
  for (ListIterator<statm::Statement> it = node.getStatementsListIteratorBegin(); it != node.getStatementsListIteratorEnd(); ++it) {
    const statm::Statement& endNodeRef = *it;
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitBlock_HasStatements(node, endNodeRef);
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
      (*itVisitors)->visitEndBlock_HasStatements(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;
  }
}

void AlgorithmPreorder::visit(const statm::Block& node, bool callFirst /*= true*/){
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

void AlgorithmPreorder::visitAllEdges(const statm::Break& node, bool callFirst /*= true*/){
  if (callFirst)
    visitAllEdges(dynamic_cast<const base::Base&>(node),false);
  if (callFirst)
    visitAllEdges(dynamic_cast<const base::Commentable&>(node),false);
  visitAllEdges(dynamic_cast<const statm::Jump&>(node),false);
}

void AlgorithmPreorder::visit(const statm::Break& node, bool callFirst /*= true*/){
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

void AlgorithmPreorder::visitAllEdges(const statm::Case& node, bool callFirst /*= true*/){
  if (callFirst)
    visitAllEdges(dynamic_cast<const base::Base&>(node),false);
  if (callFirst)
    visitAllEdges(dynamic_cast<const base::Commentable&>(node),false);
  visitAllEdges(dynamic_cast<const statm::SwitchLabel&>(node),false);

  std::list<Visitor*>::iterator itVisitors;

  const base::Base* genNodePtr;
  // edge: hasExpression
  genNodePtr = node.getExpression() ;
  if (genNodePtr) {
    const expr::Expression& endNodeRef = dynamic_cast<const expr::Expression&>(*genNodePtr);
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitCase_HasExpression(node, endNodeRef);
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
      (*itVisitors)->visitEndCase_HasExpression(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;
  }
}

void AlgorithmPreorder::visit(const statm::Case& node, bool callFirst /*= true*/){
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

void AlgorithmPreorder::visitAllEdges(const statm::Continue& node, bool callFirst /*= true*/){
  if (callFirst)
    visitAllEdges(dynamic_cast<const base::Base&>(node),false);
  if (callFirst)
    visitAllEdges(dynamic_cast<const base::Commentable&>(node),false);
  visitAllEdges(dynamic_cast<const statm::Jump&>(node),false);
}

void AlgorithmPreorder::visit(const statm::Continue& node, bool callFirst /*= true*/){
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

void AlgorithmPreorder::visitAllEdges(const statm::Default& node, bool callFirst /*= true*/){
  if (callFirst)
    visitAllEdges(dynamic_cast<const base::Base&>(node),false);
  if (callFirst)
    visitAllEdges(dynamic_cast<const base::Commentable&>(node),false);
  visitAllEdges(dynamic_cast<const statm::SwitchLabel&>(node),false);
}

void AlgorithmPreorder::visit(const statm::Default& node, bool callFirst /*= true*/){
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

void AlgorithmPreorder::visitAllEdges(const statm::Do& node, bool callFirst /*= true*/){
  if (callFirst)
    visitAllEdges(dynamic_cast<const base::Base&>(node),false);
  if (callFirst)
    visitAllEdges(dynamic_cast<const base::Commentable&>(node),false);
  visitAllEdges(dynamic_cast<const statm::Iteration&>(node),false);

  std::list<Visitor*>::iterator itVisitors;

  const base::Base* genNodePtr;
  // edge: hasCondition
  genNodePtr = node.getCondition() ;
  if (genNodePtr) {
    const expr::Expression& endNodeRef = dynamic_cast<const expr::Expression&>(*genNodePtr);
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitDo_HasCondition(node, endNodeRef);
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
      (*itVisitors)->visitEndDo_HasCondition(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;
  }
}

void AlgorithmPreorder::visit(const statm::Do& node, bool callFirst /*= true*/){
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

void AlgorithmPreorder::visitAllEdges(const statm::Empty& node, bool callFirst /*= true*/){
  if (callFirst)
    visitAllEdges(dynamic_cast<const base::Base&>(node),false);
  if (callFirst)
    visitAllEdges(dynamic_cast<const base::Commentable&>(node),false);
  visitAllEdges(dynamic_cast<const statm::Statement&>(node),false);
}

void AlgorithmPreorder::visit(const statm::Empty& node, bool callFirst /*= true*/){
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

void AlgorithmPreorder::visitAllEdges(const statm::EnhancedFor& node, bool callFirst /*= true*/){
  if (callFirst)
    visitAllEdges(dynamic_cast<const base::Base&>(node),false);
  if (callFirst)
    visitAllEdges(dynamic_cast<const base::Commentable&>(node),false);
  visitAllEdges(dynamic_cast<const statm::For&>(node),false);

  std::list<Visitor*>::iterator itVisitors;

  const base::Base* genNodePtr;
  // edge: hasParameter
  genNodePtr = node.getParameter() ;
  if (genNodePtr) {
    const struc::Parameter& endNodeRef = dynamic_cast<const struc::Parameter&>(*genNodePtr);
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitEnhancedFor_HasParameter(node, endNodeRef);
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
      (*itVisitors)->visitEndEnhancedFor_HasParameter(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;
  }

  // edge: hasExpression
  genNodePtr = node.getExpression() ;
  if (genNodePtr) {
    const expr::Expression& endNodeRef = dynamic_cast<const expr::Expression&>(*genNodePtr);
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitEnhancedFor_HasExpression(node, endNodeRef);
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
      (*itVisitors)->visitEndEnhancedFor_HasExpression(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;
  }
}

void AlgorithmPreorder::visit(const statm::EnhancedFor& node, bool callFirst /*= true*/){
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

void AlgorithmPreorder::visitAllEdges(const statm::ExpressionStatement& node, bool callFirst /*= true*/){
  if (callFirst)
    visitAllEdges(dynamic_cast<const base::Base&>(node),false);
  if (callFirst)
    visitAllEdges(dynamic_cast<const base::Commentable&>(node),false);
  visitAllEdges(dynamic_cast<const statm::Statement&>(node),false);

  std::list<Visitor*>::iterator itVisitors;

  const base::Base* genNodePtr;
  // edge: hasExpression
  genNodePtr = node.getExpression() ;
  if (genNodePtr) {
    const expr::Expression& endNodeRef = dynamic_cast<const expr::Expression&>(*genNodePtr);
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitExpressionStatement_HasExpression(node, endNodeRef);
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
      (*itVisitors)->visitEndExpressionStatement_HasExpression(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;
  }
}

void AlgorithmPreorder::visit(const statm::ExpressionStatement& node, bool callFirst /*= true*/){
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

void AlgorithmPreorder::visitAllEdges(const statm::For& node, bool callFirst /*= true*/){
  if (callFirst)
    visitAllEdges(dynamic_cast<const base::Base&>(node),false);
  if (callFirst)
    visitAllEdges(dynamic_cast<const base::Commentable&>(node),false);
  visitAllEdges(dynamic_cast<const statm::Iteration&>(node),false);
}

void AlgorithmPreorder::visitAllEdges(const statm::Handler& node, bool callFirst /*= true*/){
  if (callFirst)
    visitAllEdges(dynamic_cast<const base::Base&>(node),false);
  if (callFirst)
    visitAllEdges(dynamic_cast<const base::Commentable&>(node),false);
  visitAllEdges(dynamic_cast<const base::Positioned&>(node),false);

  std::list<Visitor*>::iterator itVisitors;

  const base::Base* genNodePtr;
  // edge: hasParameter
  genNodePtr = node.getParameter() ;
  if (genNodePtr) {
    const struc::Parameter& endNodeRef = dynamic_cast<const struc::Parameter&>(*genNodePtr);
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitHandler_HasParameter(node, endNodeRef);
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
      (*itVisitors)->visitEndHandler_HasParameter(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;
  }

  // edge: hasBlock
  genNodePtr = node.getBlock() ;
  if (genNodePtr) {
    const statm::Block& endNodeRef = dynamic_cast<const statm::Block&>(*genNodePtr);
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitHandler_HasBlock(node, endNodeRef);
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
      (*itVisitors)->visitEndHandler_HasBlock(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;
  }
}

void AlgorithmPreorder::visit(const statm::Handler& node, bool callFirst /*= true*/){
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

void AlgorithmPreorder::visitAllEdges(const statm::If& node, bool callFirst /*= true*/){
  if (callFirst)
    visitAllEdges(dynamic_cast<const base::Base&>(node),false);
  if (callFirst)
    visitAllEdges(dynamic_cast<const base::Commentable&>(node),false);
  visitAllEdges(dynamic_cast<const statm::Selection&>(node),false);

  std::list<Visitor*>::iterator itVisitors;

  const base::Base* genNodePtr;
  // edge: hasSubstatement
  genNodePtr = node.getSubstatement() ;
  if (genNodePtr) {
    const statm::Statement& endNodeRef = dynamic_cast<const statm::Statement&>(*genNodePtr);
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitIf_HasSubstatement(node, endNodeRef);
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
      (*itVisitors)->visitEndIf_HasSubstatement(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;
  }

  // edge: hasFalseSubstatement
  genNodePtr = node.getFalseSubstatement() ;
  if (genNodePtr) {
    const statm::Statement& endNodeRef = dynamic_cast<const statm::Statement&>(*genNodePtr);
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitIf_HasFalseSubstatement(node, endNodeRef);
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
      (*itVisitors)->visitEndIf_HasFalseSubstatement(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;
  }
}

void AlgorithmPreorder::visit(const statm::If& node, bool callFirst /*= true*/){
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

void AlgorithmPreorder::visitAllEdges(const statm::Iteration& node, bool callFirst /*= true*/){
  if (callFirst)
    visitAllEdges(dynamic_cast<const base::Base&>(node),false);
  if (callFirst)
    visitAllEdges(dynamic_cast<const base::Commentable&>(node),false);
  visitAllEdges(dynamic_cast<const statm::Statement&>(node),false);

  std::list<Visitor*>::iterator itVisitors;

  const base::Base* genNodePtr;
  // edge: hasSubstatement
  genNodePtr = node.getSubstatement() ;
  if (genNodePtr) {
    const statm::Statement& endNodeRef = dynamic_cast<const statm::Statement&>(*genNodePtr);
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitIteration_HasSubstatement(node, endNodeRef);
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
      (*itVisitors)->visitEndIteration_HasSubstatement(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;
  }
}

void AlgorithmPreorder::visitAllEdges(const statm::Jump& node, bool callFirst /*= true*/){
  if (callFirst)
    visitAllEdges(dynamic_cast<const base::Base&>(node),false);
  if (callFirst)
    visitAllEdges(dynamic_cast<const base::Commentable&>(node),false);
  visitAllEdges(dynamic_cast<const statm::Statement&>(node),false);

  std::list<Visitor*>::iterator itVisitors;

  const base::Base* genNodePtr;
  // edge: target
  genNodePtr = node.getTarget() ;
  if (genNodePtr) {
    const statm::Statement& endNodeRef = dynamic_cast<const statm::Statement&>(*genNodePtr);
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitJump_Target(node, endNodeRef);
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
      if (traversaldCrossEdges[edkJump_Target]) {
        endNodeRef.accept(*this);
      }
    }
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitEndJump_Target(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;
  }
}

void AlgorithmPreorder::visitAllEdges(const statm::LabeledStatement& node, bool callFirst /*= true*/){
  if (callFirst)
    visitAllEdges(dynamic_cast<const base::Base&>(node),false);
  if (callFirst)
    visitAllEdges(dynamic_cast<const base::Commentable&>(node),false);
  visitAllEdges(dynamic_cast<const statm::Statement&>(node),false);

  std::list<Visitor*>::iterator itVisitors;

  const base::Base* genNodePtr;
  // edge: hasStatement
  genNodePtr = node.getStatement() ;
  if (genNodePtr) {
    const statm::Statement& endNodeRef = dynamic_cast<const statm::Statement&>(*genNodePtr);
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitLabeledStatement_HasStatement(node, endNodeRef);
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
      (*itVisitors)->visitEndLabeledStatement_HasStatement(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;
  }
}

void AlgorithmPreorder::visit(const statm::LabeledStatement& node, bool callFirst /*= true*/){
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

void AlgorithmPreorder::visitAllEdges(const statm::Return& node, bool callFirst /*= true*/){
  if (callFirst)
    visitAllEdges(dynamic_cast<const base::Base&>(node),false);
  if (callFirst)
    visitAllEdges(dynamic_cast<const base::Commentable&>(node),false);
  visitAllEdges(dynamic_cast<const statm::Statement&>(node),false);

  std::list<Visitor*>::iterator itVisitors;

  const base::Base* genNodePtr;
  // edge: hasExpression
  genNodePtr = node.getExpression() ;
  if (genNodePtr) {
    const expr::Expression& endNodeRef = dynamic_cast<const expr::Expression&>(*genNodePtr);
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

void AlgorithmPreorder::visit(const statm::Return& node, bool callFirst /*= true*/){
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

void AlgorithmPreorder::visitAllEdges(const statm::Selection& node, bool callFirst /*= true*/){
  if (callFirst)
    visitAllEdges(dynamic_cast<const base::Base&>(node),false);
  if (callFirst)
    visitAllEdges(dynamic_cast<const base::Commentable&>(node),false);
  visitAllEdges(dynamic_cast<const statm::Statement&>(node),false);

  std::list<Visitor*>::iterator itVisitors;

  const base::Base* genNodePtr;
  // edge: hasCondition
  genNodePtr = node.getCondition() ;
  if (genNodePtr) {
    const expr::Expression& endNodeRef = dynamic_cast<const expr::Expression&>(*genNodePtr);
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitSelection_HasCondition(node, endNodeRef);
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
      (*itVisitors)->visitEndSelection_HasCondition(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;
  }
}

void AlgorithmPreorder::visitAllEdges(const statm::Statement& node, bool callFirst /*= true*/){
  if (callFirst)
    visitAllEdges(dynamic_cast<const base::Base&>(node),false);
  if (callFirst)
    visitAllEdges(dynamic_cast<const base::Commentable&>(node),false);
  visitAllEdges(dynamic_cast<const base::Positioned&>(node),false);
}

void AlgorithmPreorder::visitAllEdges(const statm::Switch& node, bool callFirst /*= true*/){
  if (callFirst)
    visitAllEdges(dynamic_cast<const base::Base&>(node),false);
  if (callFirst)
    visitAllEdges(dynamic_cast<const base::Commentable&>(node),false);
  visitAllEdges(dynamic_cast<const statm::Selection&>(node),false);

  std::list<Visitor*>::iterator itVisitors;

  // edge: hasCases
  for (ListIterator<statm::SwitchLabel> it = node.getCasesListIteratorBegin(); it != node.getCasesListIteratorEnd(); ++it) {
    const statm::SwitchLabel& endNodeRef = *it;
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitSwitch_HasCases(node, endNodeRef);
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
      (*itVisitors)->visitEndSwitch_HasCases(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;
  }
}

void AlgorithmPreorder::visit(const statm::Switch& node, bool callFirst /*= true*/){
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

void AlgorithmPreorder::visitAllEdges(const statm::SwitchLabel& node, bool callFirst /*= true*/){
  if (callFirst)
    visitAllEdges(dynamic_cast<const base::Base&>(node),false);
  if (callFirst)
    visitAllEdges(dynamic_cast<const base::Commentable&>(node),false);
  visitAllEdges(dynamic_cast<const base::Positioned&>(node),false);

  std::list<Visitor*>::iterator itVisitors;

  // edge: hasStatements
  for (ListIterator<statm::Statement> it = node.getStatementsListIteratorBegin(); it != node.getStatementsListIteratorEnd(); ++it) {
    const statm::Statement& endNodeRef = *it;
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitSwitchLabel_HasStatements(node, endNodeRef);
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
      (*itVisitors)->visitEndSwitchLabel_HasStatements(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;
  }
}

void AlgorithmPreorder::visitAllEdges(const statm::Synchronized& node, bool callFirst /*= true*/){
  if (callFirst)
    visitAllEdges(dynamic_cast<const base::Base&>(node),false);
  if (callFirst)
    visitAllEdges(dynamic_cast<const base::Commentable&>(node),false);
  visitAllEdges(dynamic_cast<const statm::Statement&>(node),false);

  std::list<Visitor*>::iterator itVisitors;

  const base::Base* genNodePtr;
  // edge: hasLock
  genNodePtr = node.getLock() ;
  if (genNodePtr) {
    const expr::Expression& endNodeRef = dynamic_cast<const expr::Expression&>(*genNodePtr);
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitSynchronized_HasLock(node, endNodeRef);
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
      (*itVisitors)->visitEndSynchronized_HasLock(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;
  }

  // edge: hasBlock
  genNodePtr = node.getBlock() ;
  if (genNodePtr) {
    const statm::Block& endNodeRef = dynamic_cast<const statm::Block&>(*genNodePtr);
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitSynchronized_HasBlock(node, endNodeRef);
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
      (*itVisitors)->visitEndSynchronized_HasBlock(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;
  }
}

void AlgorithmPreorder::visit(const statm::Synchronized& node, bool callFirst /*= true*/){
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

void AlgorithmPreorder::visitAllEdges(const statm::Throw& node, bool callFirst /*= true*/){
  if (callFirst)
    visitAllEdges(dynamic_cast<const base::Base&>(node),false);
  if (callFirst)
    visitAllEdges(dynamic_cast<const base::Commentable&>(node),false);
  visitAllEdges(dynamic_cast<const statm::Statement&>(node),false);

  std::list<Visitor*>::iterator itVisitors;

  const base::Base* genNodePtr;
  // edge: hasExpression
  genNodePtr = node.getExpression() ;
  if (genNodePtr) {
    const expr::Expression& endNodeRef = dynamic_cast<const expr::Expression&>(*genNodePtr);
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitThrow_HasExpression(node, endNodeRef);
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
      (*itVisitors)->visitEndThrow_HasExpression(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;
  }
}

void AlgorithmPreorder::visit(const statm::Throw& node, bool callFirst /*= true*/){
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

void AlgorithmPreorder::visitAllEdges(const statm::Try& node, bool callFirst /*= true*/){
  if (callFirst)
    visitAllEdges(dynamic_cast<const base::Base&>(node),false);
  if (callFirst)
    visitAllEdges(dynamic_cast<const base::Commentable&>(node),false);
  visitAllEdges(dynamic_cast<const statm::Statement&>(node),false);

  std::list<Visitor*>::iterator itVisitors;

  // edge: hasResources
  for (ListIterator<struc::Variable> it = node.getResourcesListIteratorBegin(); it != node.getResourcesListIteratorEnd(); ++it) {
    const struc::Variable& endNodeRef = *it;
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitTry_HasResources(node, endNodeRef);
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
      (*itVisitors)->visitEndTry_HasResources(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;
  }

  const base::Base* genNodePtr;
  // edge: hasBlock
  genNodePtr = node.getBlock() ;
  if (genNodePtr) {
    const statm::Block& endNodeRef = dynamic_cast<const statm::Block&>(*genNodePtr);
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitTry_HasBlock(node, endNodeRef);
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
      (*itVisitors)->visitEndTry_HasBlock(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;
  }

  // edge: hasHandlers
  for (ListIterator<statm::Handler> it = node.getHandlersListIteratorBegin(); it != node.getHandlersListIteratorEnd(); ++it) {
    const statm::Handler& endNodeRef = *it;
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitTry_HasHandlers(node, endNodeRef);
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
      (*itVisitors)->visitEndTry_HasHandlers(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;
  }

  // edge: hasFinallyBlock
  genNodePtr = node.getFinallyBlock() ;
  if (genNodePtr) {
    const statm::Block& endNodeRef = dynamic_cast<const statm::Block&>(*genNodePtr);
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitTry_HasFinallyBlock(node, endNodeRef);
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
      (*itVisitors)->visitEndTry_HasFinallyBlock(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;
  }
}

void AlgorithmPreorder::visit(const statm::Try& node, bool callFirst /*= true*/){
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

void AlgorithmPreorder::visitAllEdges(const statm::While& node, bool callFirst /*= true*/){
  if (callFirst)
    visitAllEdges(dynamic_cast<const base::Base&>(node),false);
  if (callFirst)
    visitAllEdges(dynamic_cast<const base::Commentable&>(node),false);
  visitAllEdges(dynamic_cast<const statm::Iteration&>(node),false);

  std::list<Visitor*>::iterator itVisitors;

  const base::Base* genNodePtr;
  // edge: hasCondition
  genNodePtr = node.getCondition() ;
  if (genNodePtr) {
    const expr::Expression& endNodeRef = dynamic_cast<const expr::Expression&>(*genNodePtr);
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitWhile_HasCondition(node, endNodeRef);
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
      (*itVisitors)->visitEndWhile_HasCondition(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;
  }
}

void AlgorithmPreorder::visit(const statm::While& node, bool callFirst /*= true*/){
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

void AlgorithmPreorder::visitAllEdges(const struc::AnnotatedElement& node, bool callFirst /*= true*/){
  if (callFirst)
    visitAllEdges(dynamic_cast<const base::Base&>(node),false);

  std::list<Visitor*>::iterator itVisitors;

  // edge: hasAnnotations
  for (ListIterator<expr::Annotation> it = node.getAnnotationsListIteratorBegin(); it != node.getAnnotationsListIteratorEnd(); ++it) {
    const expr::Annotation& endNodeRef = *it;
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitAnnotatedElement_HasAnnotations(node, endNodeRef);
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
      (*itVisitors)->visitEndAnnotatedElement_HasAnnotations(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;
  }
}

void AlgorithmPreorder::visitAllEdges(const struc::AnnotationType& node, bool callFirst /*= true*/){
  if (callFirst)
    visitAllEdges(dynamic_cast<const base::Base&>(node),false);
  if (callFirst)
    visitAllEdges(dynamic_cast<const base::Commentable&>(node),false);
  if (callFirst)
    visitAllEdges(dynamic_cast<const struc::Member&>(node),false);
  visitAllEdges(dynamic_cast<const struc::TypeDeclaration&>(node),false);
}

void AlgorithmPreorder::visit(const struc::AnnotationType& node, bool callFirst /*= true*/){
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

void AlgorithmPreorder::visitAllEdges(const struc::AnnotationTypeElement& node, bool callFirst /*= true*/){
  if (callFirst)
    visitAllEdges(dynamic_cast<const base::Base&>(node),false);
  if (callFirst)
    visitAllEdges(dynamic_cast<const base::Commentable&>(node),false);
  if (callFirst)
    visitAllEdges(dynamic_cast<const struc::Member&>(node),false);
  visitAllEdges(dynamic_cast<const struc::MethodDeclaration&>(node),false);

  std::list<Visitor*>::iterator itVisitors;

  const base::Base* genNodePtr;
  // edge: hasDefaultValue
  genNodePtr = node.getDefaultValue() ;
  if (genNodePtr) {
    const expr::Expression& endNodeRef = dynamic_cast<const expr::Expression&>(*genNodePtr);
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitAnnotationTypeElement_HasDefaultValue(node, endNodeRef);
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
      (*itVisitors)->visitEndAnnotationTypeElement_HasDefaultValue(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;
  }
}

void AlgorithmPreorder::visit(const struc::AnnotationTypeElement& node, bool callFirst /*= true*/){
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

void AlgorithmPreorder::visitAllEdges(const struc::AnonymousClass& node, bool callFirst /*= true*/){
  if (callFirst)
    visitAllEdges(dynamic_cast<const base::Base&>(node),false);
  if (callFirst)
    visitAllEdges(dynamic_cast<const base::Commentable&>(node),false);
  if (callFirst)
    visitAllEdges(dynamic_cast<const struc::Member&>(node),false);
  visitAllEdges(dynamic_cast<const struc::ClassDeclaration&>(node),false);
}

void AlgorithmPreorder::visit(const struc::AnonymousClass& node, bool callFirst /*= true*/){
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

void AlgorithmPreorder::visitAllEdges(const struc::Class& node, bool callFirst /*= true*/){
  if (callFirst)
    visitAllEdges(dynamic_cast<const base::Base&>(node),false);
  if (callFirst)
    visitAllEdges(dynamic_cast<const base::Commentable&>(node),false);
  if (callFirst)
    visitAllEdges(dynamic_cast<const struc::Member&>(node),false);
  visitAllEdges(dynamic_cast<const struc::ClassDeclaration&>(node),false);
}

void AlgorithmPreorder::visit(const struc::Class& node, bool callFirst /*= true*/){
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

void AlgorithmPreorder::visitAllEdges(const struc::ClassDeclaration& node, bool callFirst /*= true*/){
  if (callFirst)
    visitAllEdges(dynamic_cast<const base::Base&>(node),false);
  if (callFirst)
    visitAllEdges(dynamic_cast<const base::Commentable&>(node),false);
  if (callFirst)
    visitAllEdges(dynamic_cast<const struc::Member&>(node),false);
  visitAllEdges(dynamic_cast<const struc::TypeDeclaration&>(node),false);
}

void AlgorithmPreorder::visitAllEdges(const struc::ClassGeneric& node, bool callFirst /*= true*/){
  if (callFirst)
    visitAllEdges(dynamic_cast<const base::Base&>(node),false);
  if (callFirst)
    visitAllEdges(dynamic_cast<const base::Commentable&>(node),false);
  if (callFirst)
    visitAllEdges(dynamic_cast<const struc::Member&>(node),false);
  visitAllEdges(dynamic_cast<const struc::ClassDeclaration&>(node),false);
  visitAllEdges(dynamic_cast<const struc::GenericDeclaration&>(node),false);
}

void AlgorithmPreorder::visit(const struc::ClassGeneric& node, bool callFirst /*= true*/){
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

void AlgorithmPreorder::visitAllEdges(const struc::CompilationUnit& node, bool callFirst /*= true*/){
  if (callFirst)
    visitAllEdges(dynamic_cast<const base::Base&>(node),false);
  visitAllEdges(dynamic_cast<const base::PositionedWithoutComment&>(node),false);
  visitAllEdges(dynamic_cast<const base::Commentable&>(node),false);

  std::list<Visitor*>::iterator itVisitors;

  const base::Base* genNodePtr;
  // edge: hasPackageDeclaration
  genNodePtr = node.getPackageDeclaration() ;
  if (genNodePtr) {
    const struc::PackageDeclaration& endNodeRef = dynamic_cast<const struc::PackageDeclaration&>(*genNodePtr);
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitCompilationUnit_HasPackageDeclaration(node, endNodeRef);
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
      (*itVisitors)->visitEndCompilationUnit_HasPackageDeclaration(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;
  }

  // edge: hasImports
  for (ListIterator<struc::Import> it = node.getImportsListIteratorBegin(); it != node.getImportsListIteratorEnd(); ++it) {
    const struc::Import& endNodeRef = *it;
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitCompilationUnit_HasImports(node, endNodeRef);
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
      (*itVisitors)->visitEndCompilationUnit_HasImports(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;
  }

  // edge: typeDeclarations
  for (ListIterator<struc::TypeDeclaration> it = node.getTypeDeclarationsListIteratorBegin(); it != node.getTypeDeclarationsListIteratorEnd(); ++it) {
    const struc::TypeDeclaration& endNodeRef = *it;
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitCompilationUnit_TypeDeclarations(node, endNodeRef);
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
      if (traversaldCrossEdges[edkCompilationUnit_TypeDeclarations]) {
        endNodeRef.accept(*this);
      }
    }
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitEndCompilationUnit_TypeDeclarations(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;
  }

  // edge: hasOthers
  for (ListIterator<base::Positioned> it = node.getOthersListIteratorBegin(); it != node.getOthersListIteratorEnd(); ++it) {
    const base::Positioned& endNodeRef = *it;
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitCompilationUnit_HasOthers(node, endNodeRef);
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
      (*itVisitors)->visitEndCompilationUnit_HasOthers(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;
  }
}

void AlgorithmPreorder::visit(const struc::CompilationUnit& node, bool callFirst /*= true*/){
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

void AlgorithmPreorder::visitAllEdges(const struc::Declaration& node, bool callFirst /*= true*/){
  if (callFirst)
    visitAllEdges(dynamic_cast<const base::Base&>(node),false);
  if (callFirst)
    visitAllEdges(dynamic_cast<const base::Commentable&>(node),false);
  if (callFirst)
    visitAllEdges(dynamic_cast<const struc::Member&>(node),false);
  visitAllEdges(dynamic_cast<const statm::Statement&>(node),false);
}

void AlgorithmPreorder::visitAllEdges(const struc::Enum& node, bool callFirst /*= true*/){
  if (callFirst)
    visitAllEdges(dynamic_cast<const base::Base&>(node),false);
  if (callFirst)
    visitAllEdges(dynamic_cast<const base::Commentable&>(node),false);
  if (callFirst)
    visitAllEdges(dynamic_cast<const struc::Member&>(node),false);
  visitAllEdges(dynamic_cast<const struc::TypeDeclaration&>(node),false);
}

void AlgorithmPreorder::visit(const struc::Enum& node, bool callFirst /*= true*/){
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

void AlgorithmPreorder::visitAllEdges(const struc::EnumConstant& node, bool callFirst /*= true*/){
  if (callFirst)
    visitAllEdges(dynamic_cast<const base::Base&>(node),false);
  if (callFirst)
    visitAllEdges(dynamic_cast<const base::Commentable&>(node),false);
  if (callFirst)
    visitAllEdges(dynamic_cast<const struc::Member&>(node),false);
  visitAllEdges(dynamic_cast<const struc::VariableDeclaration&>(node),false);

  std::list<Visitor*>::iterator itVisitors;

  const base::Base* genNodePtr;
  // edge: hasNewClass
  genNodePtr = node.getNewClass() ;
  if (genNodePtr) {
    const expr::NewClass& endNodeRef = dynamic_cast<const expr::NewClass&>(*genNodePtr);
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitEnumConstant_HasNewClass(node, endNodeRef);
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
      (*itVisitors)->visitEndEnumConstant_HasNewClass(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;
  }
}

void AlgorithmPreorder::visit(const struc::EnumConstant& node, bool callFirst /*= true*/){
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

void AlgorithmPreorder::visitAllEdges(const struc::GenericDeclaration& node, bool callFirst /*= true*/){
  if (callFirst)
    visitAllEdges(dynamic_cast<const base::Base&>(node),false);

  std::list<Visitor*>::iterator itVisitors;

  // edge: hasTypeParameters
  for (ListIterator<struc::TypeParameter> it = node.getTypeParametersListIteratorBegin(); it != node.getTypeParametersListIteratorEnd(); ++it) {
    const struc::TypeParameter& endNodeRef = *it;
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitGenericDeclaration_HasTypeParameters(node, endNodeRef);
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
      (*itVisitors)->visitEndGenericDeclaration_HasTypeParameters(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;
  }
}

void AlgorithmPreorder::visitAllEdges(const struc::Import& node, bool callFirst /*= true*/){
  if (callFirst)
    visitAllEdges(dynamic_cast<const base::Base&>(node),false);
  if (callFirst)
    visitAllEdges(dynamic_cast<const base::Commentable&>(node),false);
  visitAllEdges(dynamic_cast<const base::Positioned&>(node),false);

  std::list<Visitor*>::iterator itVisitors;

  const base::Base* genNodePtr;
  // edge: hasTarget
  genNodePtr = node.getTarget() ;
  if (genNodePtr) {
    const expr::Expression& endNodeRef = dynamic_cast<const expr::Expression&>(*genNodePtr);
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitImport_HasTarget(node, endNodeRef);
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
      (*itVisitors)->visitEndImport_HasTarget(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;
  }
}

void AlgorithmPreorder::visit(const struc::Import& node, bool callFirst /*= true*/){
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

void AlgorithmPreorder::visitAllEdges(const struc::InitializerBlock& node, bool callFirst /*= true*/){
  if (callFirst)
    visitAllEdges(dynamic_cast<const base::Base&>(node),false);
  if (callFirst)
    visitAllEdges(dynamic_cast<const base::Commentable&>(node),false);
  if (callFirst)
    visitAllEdges(dynamic_cast<const struc::Member&>(node),false);
  visitAllEdges(dynamic_cast<const struc::Declaration&>(node),false);

  std::list<Visitor*>::iterator itVisitors;

  const base::Base* genNodePtr;
  // edge: hasBody
  genNodePtr = node.getBody() ;
  if (genNodePtr) {
    const statm::Block& endNodeRef = dynamic_cast<const statm::Block&>(*genNodePtr);
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitInitializerBlock_HasBody(node, endNodeRef);
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
      (*itVisitors)->visitEndInitializerBlock_HasBody(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;
  }
}

void AlgorithmPreorder::visitAllEdges(const struc::InstanceInitializerBlock& node, bool callFirst /*= true*/){
  if (callFirst)
    visitAllEdges(dynamic_cast<const base::Base&>(node),false);
  if (callFirst)
    visitAllEdges(dynamic_cast<const base::Commentable&>(node),false);
  if (callFirst)
    visitAllEdges(dynamic_cast<const struc::Member&>(node),false);
  visitAllEdges(dynamic_cast<const struc::InitializerBlock&>(node),false);
}

void AlgorithmPreorder::visit(const struc::InstanceInitializerBlock& node, bool callFirst /*= true*/){
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

void AlgorithmPreorder::visitAllEdges(const struc::Interface& node, bool callFirst /*= true*/){
  if (callFirst)
    visitAllEdges(dynamic_cast<const base::Base&>(node),false);
  if (callFirst)
    visitAllEdges(dynamic_cast<const base::Commentable&>(node),false);
  if (callFirst)
    visitAllEdges(dynamic_cast<const struc::Member&>(node),false);
  visitAllEdges(dynamic_cast<const struc::InterfaceDeclaration&>(node),false);
}

void AlgorithmPreorder::visit(const struc::Interface& node, bool callFirst /*= true*/){
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

void AlgorithmPreorder::visitAllEdges(const struc::InterfaceDeclaration& node, bool callFirst /*= true*/){
  if (callFirst)
    visitAllEdges(dynamic_cast<const base::Base&>(node),false);
  if (callFirst)
    visitAllEdges(dynamic_cast<const base::Commentable&>(node),false);
  if (callFirst)
    visitAllEdges(dynamic_cast<const struc::Member&>(node),false);
  visitAllEdges(dynamic_cast<const struc::TypeDeclaration&>(node),false);
}

void AlgorithmPreorder::visitAllEdges(const struc::InterfaceGeneric& node, bool callFirst /*= true*/){
  if (callFirst)
    visitAllEdges(dynamic_cast<const base::Base&>(node),false);
  if (callFirst)
    visitAllEdges(dynamic_cast<const base::Commentable&>(node),false);
  if (callFirst)
    visitAllEdges(dynamic_cast<const struc::Member&>(node),false);
  visitAllEdges(dynamic_cast<const struc::InterfaceDeclaration&>(node),false);
  visitAllEdges(dynamic_cast<const struc::GenericDeclaration&>(node),false);
}

void AlgorithmPreorder::visit(const struc::InterfaceGeneric& node, bool callFirst /*= true*/){
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

void AlgorithmPreorder::visitAllEdges(const struc::Member& node, bool callFirst /*= true*/){
  if (callFirst)
    visitAllEdges(dynamic_cast<const base::Base&>(node),false);
  if (callFirst)
    visitAllEdges(dynamic_cast<const base::Commentable&>(node),false);
  visitAllEdges(dynamic_cast<const struc::AnnotatedElement&>(node),false);
}

void AlgorithmPreorder::visitAllEdges(const struc::Method& node, bool callFirst /*= true*/){
  if (callFirst)
    visitAllEdges(dynamic_cast<const base::Base&>(node),false);
  if (callFirst)
    visitAllEdges(dynamic_cast<const base::Commentable&>(node),false);
  if (callFirst)
    visitAllEdges(dynamic_cast<const struc::Member&>(node),false);
  visitAllEdges(dynamic_cast<const struc::NormalMethod&>(node),false);
}

void AlgorithmPreorder::visit(const struc::Method& node, bool callFirst /*= true*/){
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

void AlgorithmPreorder::visitAllEdges(const struc::MethodDeclaration& node, bool callFirst /*= true*/){
  if (callFirst)
    visitAllEdges(dynamic_cast<const base::Base&>(node),false);
  if (callFirst)
    visitAllEdges(dynamic_cast<const base::Commentable&>(node),false);
  if (callFirst)
    visitAllEdges(dynamic_cast<const struc::Member&>(node),false);
  visitAllEdges(dynamic_cast<const struc::NamedDeclaration&>(node),false);

  std::list<Visitor*>::iterator itVisitors;

  const base::Base* genNodePtr;
  // edge: hasReturnType
  genNodePtr = node.getReturnType() ;
  if (genNodePtr) {
    const expr::TypeExpression& endNodeRef = dynamic_cast<const expr::TypeExpression&>(*genNodePtr);
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitMethodDeclaration_HasReturnType(node, endNodeRef);
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
      (*itVisitors)->visitEndMethodDeclaration_HasReturnType(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;
  }

  // edge: methodType
  genNodePtr = node.getMethodType() ;
  if (genNodePtr) {
    const type::MethodType& endNodeRef = dynamic_cast<const type::MethodType&>(*genNodePtr);
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitMethodDeclaration_MethodType(node, endNodeRef);
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
      if (traversaldCrossEdges[edkMethodDeclaration_MethodType]) {
        endNodeRef.accept(*this);
      }
    }
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitEndMethodDeclaration_MethodType(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;
  }

  // edge: overrides
  for (ListIterator<struc::MethodDeclaration> it = node.getOverridesListIteratorBegin(); it != node.getOverridesListIteratorEnd(); ++it) {
    const struc::MethodDeclaration& endNodeRef = *it;
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitMethodDeclaration_Overrides(node, endNodeRef);
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
      if (traversaldCrossEdges[edkMethodDeclaration_Overrides]) {
        endNodeRef.accept(*this);
      }
    }
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitEndMethodDeclaration_Overrides(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;
  }
}

void AlgorithmPreorder::visitAllEdges(const struc::MethodGeneric& node, bool callFirst /*= true*/){
  if (callFirst)
    visitAllEdges(dynamic_cast<const base::Base&>(node),false);
  if (callFirst)
    visitAllEdges(dynamic_cast<const base::Commentable&>(node),false);
  if (callFirst)
    visitAllEdges(dynamic_cast<const struc::Member&>(node),false);
  visitAllEdges(dynamic_cast<const struc::NormalMethod&>(node),false);
  visitAllEdges(dynamic_cast<const struc::GenericDeclaration&>(node),false);
}

void AlgorithmPreorder::visit(const struc::MethodGeneric& node, bool callFirst /*= true*/){
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

void AlgorithmPreorder::visitAllEdges(const struc::NamedDeclaration& node, bool callFirst /*= true*/){
  if (callFirst)
    visitAllEdges(dynamic_cast<const base::Base&>(node),false);
  if (callFirst)
    visitAllEdges(dynamic_cast<const base::Commentable&>(node),false);
  if (callFirst)
    visitAllEdges(dynamic_cast<const struc::Member&>(node),false);
  visitAllEdges(dynamic_cast<const struc::Declaration&>(node),false);
  visitAllEdges(dynamic_cast<const base::Named&>(node),false);
}

void AlgorithmPreorder::visitAllEdges(const struc::NormalMethod& node, bool callFirst /*= true*/){
  if (callFirst)
    visitAllEdges(dynamic_cast<const base::Base&>(node),false);
  if (callFirst)
    visitAllEdges(dynamic_cast<const base::Commentable&>(node),false);
  if (callFirst)
    visitAllEdges(dynamic_cast<const struc::Member&>(node),false);
  visitAllEdges(dynamic_cast<const struc::MethodDeclaration&>(node),false);

  std::list<Visitor*>::iterator itVisitors;

  // edge: hasParameters
  for (ListIterator<struc::Parameter> it = node.getParametersListIteratorBegin(); it != node.getParametersListIteratorEnd(); ++it) {
    const struc::Parameter& endNodeRef = *it;
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitNormalMethod_HasParameters(node, endNodeRef);
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
      (*itVisitors)->visitEndNormalMethod_HasParameters(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;
  }

  const base::Base* genNodePtr;
  // edge: hasBody
  genNodePtr = node.getBody() ;
  if (genNodePtr) {
    const statm::Block& endNodeRef = dynamic_cast<const statm::Block&>(*genNodePtr);
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitNormalMethod_HasBody(node, endNodeRef);
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
      (*itVisitors)->visitEndNormalMethod_HasBody(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;
  }

  // edge: hasThrownExceptions
  for (ListIterator<expr::TypeExpression> it = node.getThrownExceptionsListIteratorBegin(); it != node.getThrownExceptionsListIteratorEnd(); ++it) {
    const expr::TypeExpression& endNodeRef = *it;
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitNormalMethod_HasThrownExceptions(node, endNodeRef);
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
      (*itVisitors)->visitEndNormalMethod_HasThrownExceptions(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;
  }
}

void AlgorithmPreorder::visitAllEdges(const struc::Package& node, bool callFirst /*= true*/){
  if (callFirst)
    visitAllEdges(dynamic_cast<const base::Base&>(node),false);
  if (callFirst)
    visitAllEdges(dynamic_cast<const base::Commentable&>(node),false);
  if (callFirst)
    visitAllEdges(dynamic_cast<const struc::Member&>(node),false);
  visitAllEdges(dynamic_cast<const base::Named&>(node),false);
  visitAllEdges(dynamic_cast<const struc::Scope&>(node),false);

  std::list<Visitor*>::iterator itVisitors;

  // edge: hasCompilationUnits
  for (ListIterator<struc::CompilationUnit> it = node.getCompilationUnitsListIteratorBegin(); it != node.getCompilationUnitsListIteratorEnd(); ++it) {
    const struc::CompilationUnit& endNodeRef = *it;
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitPackage_HasCompilationUnits(node, endNodeRef);
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
      (*itVisitors)->visitEndPackage_HasCompilationUnits(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;
  }
}

void AlgorithmPreorder::visit(const struc::Package& node, bool callFirst /*= true*/){
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

void AlgorithmPreorder::visitAllEdges(const struc::PackageDeclaration& node, bool callFirst /*= true*/){
  if (callFirst)
    visitAllEdges(dynamic_cast<const base::Base&>(node),false);
  if (callFirst)
    visitAllEdges(dynamic_cast<const base::Commentable&>(node),false);
  visitAllEdges(dynamic_cast<const base::Positioned&>(node),false);

  std::list<Visitor*>::iterator itVisitors;

  const base::Base* genNodePtr;
  // edge: hasPackageName
  genNodePtr = node.getPackageName() ;
  if (genNodePtr) {
    const expr::Expression& endNodeRef = dynamic_cast<const expr::Expression&>(*genNodePtr);
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitPackageDeclaration_HasPackageName(node, endNodeRef);
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
      (*itVisitors)->visitEndPackageDeclaration_HasPackageName(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;
  }

  // edge: refersTo
  genNodePtr = node.getRefersTo() ;
  if (genNodePtr) {
    const struc::Package& endNodeRef = dynamic_cast<const struc::Package&>(*genNodePtr);
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitPackageDeclaration_RefersTo(node, endNodeRef);
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
      if (traversaldCrossEdges[edkPackageDeclaration_RefersTo]) {
        endNodeRef.accept(*this);
      }
    }
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitEndPackageDeclaration_RefersTo(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;
  }
}

void AlgorithmPreorder::visit(const struc::PackageDeclaration& node, bool callFirst /*= true*/){
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

void AlgorithmPreorder::visitAllEdges(const struc::Parameter& node, bool callFirst /*= true*/){
  if (callFirst)
    visitAllEdges(dynamic_cast<const base::Base&>(node),false);
  if (callFirst)
    visitAllEdges(dynamic_cast<const base::Commentable&>(node),false);
  if (callFirst)
    visitAllEdges(dynamic_cast<const struc::Member&>(node),false);
  visitAllEdges(dynamic_cast<const struc::VariableDeclaration&>(node),false);
}

void AlgorithmPreorder::visit(const struc::Parameter& node, bool callFirst /*= true*/){
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

void AlgorithmPreorder::visitAllEdges(const struc::Scope& node, bool callFirst /*= true*/){
  if (callFirst)
    visitAllEdges(dynamic_cast<const base::Base&>(node),false);
  if (callFirst)
    visitAllEdges(dynamic_cast<const base::Commentable&>(node),false);
  if (callFirst)
    visitAllEdges(dynamic_cast<const struc::Member&>(node),false);

  std::list<Visitor*>::iterator itVisitors;

  // edge: hasMembers
  for (ListIterator<struc::Member> it = node.getMembersListIteratorBegin(); it != node.getMembersListIteratorEnd(); ++it) {
    const struc::Member& endNodeRef = *it;
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitScope_HasMembers(node, endNodeRef);
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
      (*itVisitors)->visitEndScope_HasMembers(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;
  }
}

void AlgorithmPreorder::visitAllEdges(const struc::StaticInitializerBlock& node, bool callFirst /*= true*/){
  if (callFirst)
    visitAllEdges(dynamic_cast<const base::Base&>(node),false);
  if (callFirst)
    visitAllEdges(dynamic_cast<const base::Commentable&>(node),false);
  if (callFirst)
    visitAllEdges(dynamic_cast<const struc::Member&>(node),false);
  visitAllEdges(dynamic_cast<const struc::InitializerBlock&>(node),false);
}

void AlgorithmPreorder::visit(const struc::StaticInitializerBlock& node, bool callFirst /*= true*/){
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

void AlgorithmPreorder::visitAllEdges(const struc::TypeDeclaration& node, bool callFirst /*= true*/){
  if (callFirst)
    visitAllEdges(dynamic_cast<const base::Base&>(node),false);
  if (callFirst)
    visitAllEdges(dynamic_cast<const base::Commentable&>(node),false);
  if (callFirst)
    visitAllEdges(dynamic_cast<const struc::Member&>(node),false);
  visitAllEdges(dynamic_cast<const struc::NamedDeclaration&>(node),false);
  visitAllEdges(dynamic_cast<const struc::Scope&>(node),false);

  std::list<Visitor*>::iterator itVisitors;

  const base::Base* genNodePtr;
  // edge: isInCompilationUnit
  genNodePtr = node.getIsInCompilationUnit() ;
  if (genNodePtr) {
    const struc::CompilationUnit& endNodeRef = dynamic_cast<const struc::CompilationUnit&>(*genNodePtr);
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitTypeDeclaration_IsInCompilationUnit(node, endNodeRef);
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
      if (traversaldCrossEdges[edkTypeDeclaration_IsInCompilationUnit]) {
        endNodeRef.accept(*this);
      }
    }
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitEndTypeDeclaration_IsInCompilationUnit(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;
  }

  // edge: hasSuperClass
  genNodePtr = node.getSuperClass() ;
  if (genNodePtr) {
    const expr::TypeExpression& endNodeRef = dynamic_cast<const expr::TypeExpression&>(*genNodePtr);
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitTypeDeclaration_HasSuperClass(node, endNodeRef);
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
      (*itVisitors)->visitEndTypeDeclaration_HasSuperClass(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;
  }

  // edge: hasSuperInterfaces
  for (ListIterator<expr::TypeExpression> it = node.getSuperInterfacesListIteratorBegin(); it != node.getSuperInterfacesListIteratorEnd(); ++it) {
    const expr::TypeExpression& endNodeRef = *it;
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitTypeDeclaration_HasSuperInterfaces(node, endNodeRef);
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
      (*itVisitors)->visitEndTypeDeclaration_HasSuperInterfaces(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;
  }

  // edge: hasOthers
  for (ListIterator<base::Positioned> it = node.getOthersListIteratorBegin(); it != node.getOthersListIteratorEnd(); ++it) {
    const base::Positioned& endNodeRef = *it;
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitTypeDeclaration_HasOthers(node, endNodeRef);
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
      (*itVisitors)->visitEndTypeDeclaration_HasOthers(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;
  }
}

void AlgorithmPreorder::visitAllEdges(const struc::TypeParameter& node, bool callFirst /*= true*/){
  if (callFirst)
    visitAllEdges(dynamic_cast<const base::Base&>(node),false);
  if (callFirst)
    visitAllEdges(dynamic_cast<const base::Commentable&>(node),false);
  visitAllEdges(dynamic_cast<const base::Positioned&>(node),false);
  visitAllEdges(dynamic_cast<const base::Named&>(node),false);

  std::list<Visitor*>::iterator itVisitors;

  // edge: hasBounds
  for (ListIterator<expr::TypeExpression> it = node.getBoundsListIteratorBegin(); it != node.getBoundsListIteratorEnd(); ++it) {
    const expr::TypeExpression& endNodeRef = *it;
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitTypeParameter_HasBounds(node, endNodeRef);
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
      (*itVisitors)->visitEndTypeParameter_HasBounds(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;
  }
}

void AlgorithmPreorder::visit(const struc::TypeParameter& node, bool callFirst /*= true*/){
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

void AlgorithmPreorder::visitAllEdges(const struc::Variable& node, bool callFirst /*= true*/){
  if (callFirst)
    visitAllEdges(dynamic_cast<const base::Base&>(node),false);
  if (callFirst)
    visitAllEdges(dynamic_cast<const base::Commentable&>(node),false);
  if (callFirst)
    visitAllEdges(dynamic_cast<const struc::Member&>(node),false);
  visitAllEdges(dynamic_cast<const struc::VariableDeclaration&>(node),false);

  std::list<Visitor*>::iterator itVisitors;

  const base::Base* genNodePtr;
  // edge: hasInitialValue
  genNodePtr = node.getInitialValue() ;
  if (genNodePtr) {
    const expr::Expression& endNodeRef = dynamic_cast<const expr::Expression&>(*genNodePtr);
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitVariable_HasInitialValue(node, endNodeRef);
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
      (*itVisitors)->visitEndVariable_HasInitialValue(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;
  }
}

void AlgorithmPreorder::visit(const struc::Variable& node, bool callFirst /*= true*/){
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

void AlgorithmPreorder::visitAllEdges(const struc::VariableDeclaration& node, bool callFirst /*= true*/){
  if (callFirst)
    visitAllEdges(dynamic_cast<const base::Base&>(node),false);
  if (callFirst)
    visitAllEdges(dynamic_cast<const base::Commentable&>(node),false);
  if (callFirst)
    visitAllEdges(dynamic_cast<const struc::Member&>(node),false);
  visitAllEdges(dynamic_cast<const struc::NamedDeclaration&>(node),false);

  std::list<Visitor*>::iterator itVisitors;

  const base::Base* genNodePtr;
  // edge: hasType
  genNodePtr = node.getType() ;
  if (genNodePtr) {
    const expr::TypeExpression& endNodeRef = dynamic_cast<const expr::TypeExpression&>(*genNodePtr);
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitVariableDeclaration_HasType(node, endNodeRef);
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
      (*itVisitors)->visitEndVariableDeclaration_HasType(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;
  }
}

void AlgorithmPreorder::visitAllEdges(const type::ArrayType& node, bool callFirst /*= true*/){
  visitAllEdges(dynamic_cast<const type::Type&>(node),false);

  std::list<Visitor*>::iterator itVisitors;

  const base::Base* genNodePtr;
  // edge: componentType
  genNodePtr = node.getComponentType() ;
  if (genNodePtr) {
    const type::Type& endNodeRef = dynamic_cast<const type::Type&>(*genNodePtr);
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitArrayType_ComponentType(node, endNodeRef);
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
      if (traversaldCrossEdges[edkArrayType_ComponentType]) {
        endNodeRef.accept(*this);
      }
    }
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitEndArrayType_ComponentType(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;
  }
}

void AlgorithmPreorder::visit(const type::ArrayType& node, bool callFirst /*= true*/){
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

void AlgorithmPreorder::visitAllEdges(const type::BooleanType& node, bool callFirst /*= true*/){
  visitAllEdges(dynamic_cast<const type::PrimitiveType&>(node),false);
}

void AlgorithmPreorder::visit(const type::BooleanType& node, bool callFirst /*= true*/){
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

void AlgorithmPreorder::visitAllEdges(const type::BoundedWildcardType& node, bool callFirst /*= true*/){
  visitAllEdges(dynamic_cast<const type::WildcardType&>(node),false);
}

void AlgorithmPreorder::visitAllEdges(const type::ByteType& node, bool callFirst /*= true*/){
  visitAllEdges(dynamic_cast<const type::PrimitiveType&>(node),false);
}

void AlgorithmPreorder::visit(const type::ByteType& node, bool callFirst /*= true*/){
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

void AlgorithmPreorder::visitAllEdges(const type::CharType& node, bool callFirst /*= true*/){
  visitAllEdges(dynamic_cast<const type::PrimitiveType&>(node),false);
}

void AlgorithmPreorder::visit(const type::CharType& node, bool callFirst /*= true*/){
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

void AlgorithmPreorder::visitAllEdges(const type::ClassType& node, bool callFirst /*= true*/){
  visitAllEdges(dynamic_cast<const type::ScopedType&>(node),false);

  std::list<Visitor*>::iterator itVisitors;

  const base::Base* genNodePtr;
  // edge: refersTo
  genNodePtr = node.getRefersTo() ;
  if (genNodePtr) {
    const struc::TypeDeclaration& endNodeRef = dynamic_cast<const struc::TypeDeclaration&>(*genNodePtr);
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitClassType_RefersTo(node, endNodeRef);
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
      if (traversaldCrossEdges[edkClassType_RefersTo]) {
        endNodeRef.accept(*this);
      }
    }
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitEndClassType_RefersTo(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;
  }
}

void AlgorithmPreorder::visit(const type::ClassType& node, bool callFirst /*= true*/){
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

void AlgorithmPreorder::visitAllEdges(const type::DoubleType& node, bool callFirst /*= true*/){
  visitAllEdges(dynamic_cast<const type::PrimitiveType&>(node),false);
}

void AlgorithmPreorder::visit(const type::DoubleType& node, bool callFirst /*= true*/){
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

void AlgorithmPreorder::visitAllEdges(const type::ErrorType& node, bool callFirst /*= true*/){
  visitAllEdges(dynamic_cast<const type::Type&>(node),false);
}

void AlgorithmPreorder::visit(const type::ErrorType& node, bool callFirst /*= true*/){
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

void AlgorithmPreorder::visitAllEdges(const type::FloatType& node, bool callFirst /*= true*/){
  visitAllEdges(dynamic_cast<const type::PrimitiveType&>(node),false);
}

void AlgorithmPreorder::visit(const type::FloatType& node, bool callFirst /*= true*/){
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

void AlgorithmPreorder::visitAllEdges(const type::IntType& node, bool callFirst /*= true*/){
  visitAllEdges(dynamic_cast<const type::PrimitiveType&>(node),false);
}

void AlgorithmPreorder::visit(const type::IntType& node, bool callFirst /*= true*/){
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

void AlgorithmPreorder::visitAllEdges(const type::LongType& node, bool callFirst /*= true*/){
  visitAllEdges(dynamic_cast<const type::PrimitiveType&>(node),false);
}

void AlgorithmPreorder::visit(const type::LongType& node, bool callFirst /*= true*/){
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

void AlgorithmPreorder::visitAllEdges(const type::LowerBoundedWildcardType& node, bool callFirst /*= true*/){
  visitAllEdges(dynamic_cast<const type::BoundedWildcardType&>(node),false);
}

void AlgorithmPreorder::visit(const type::LowerBoundedWildcardType& node, bool callFirst /*= true*/){
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

void AlgorithmPreorder::visitAllEdges(const type::MethodType& node, bool callFirst /*= true*/){
  visitAllEdges(dynamic_cast<const type::Type&>(node),false);

  std::list<Visitor*>::iterator itVisitors;

  const base::Base* genNodePtr;
  // edge: returnType
  genNodePtr = node.getReturnType() ;
  if (genNodePtr) {
    const type::Type& endNodeRef = dynamic_cast<const type::Type&>(*genNodePtr);
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitMethodType_ReturnType(node, endNodeRef);
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
      if (traversaldCrossEdges[edkMethodType_ReturnType]) {
        endNodeRef.accept(*this);
      }
    }
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitEndMethodType_ReturnType(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;
  }

  // edge: parameterTypes
  for (ListIterator<type::Type> it = node.getParameterTypesListIteratorBegin(); it != node.getParameterTypesListIteratorEnd(); ++it) {
    const type::Type& endNodeRef = *it;
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitMethodType_ParameterTypes(node, endNodeRef);
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
      if (traversaldCrossEdges[edkMethodType_ParameterTypes]) {
        endNodeRef.accept(*this);
      }
    }
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitEndMethodType_ParameterTypes(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;
  }

  // edge: thrownTypes
  for (ListIterator<type::Type> it = node.getThrownTypesListIteratorBegin(); it != node.getThrownTypesListIteratorEnd(); ++it) {
    const type::Type& endNodeRef = *it;
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitMethodType_ThrownTypes(node, endNodeRef);
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
      if (traversaldCrossEdges[edkMethodType_ThrownTypes]) {
        endNodeRef.accept(*this);
      }
    }
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitEndMethodType_ThrownTypes(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;
  }
}

void AlgorithmPreorder::visit(const type::MethodType& node, bool callFirst /*= true*/){
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

void AlgorithmPreorder::visitAllEdges(const type::NoType& node, bool callFirst /*= true*/){
  visitAllEdges(dynamic_cast<const type::Type&>(node),false);
}

void AlgorithmPreorder::visit(const type::NoType& node, bool callFirst /*= true*/){
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

void AlgorithmPreorder::visitAllEdges(const type::NullType& node, bool callFirst /*= true*/){
  visitAllEdges(dynamic_cast<const type::Type&>(node),false);
}

void AlgorithmPreorder::visit(const type::NullType& node, bool callFirst /*= true*/){
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

void AlgorithmPreorder::visitAllEdges(const type::PackageType& node, bool callFirst /*= true*/){
  visitAllEdges(dynamic_cast<const type::Type&>(node),false);

  std::list<Visitor*>::iterator itVisitors;

  const base::Base* genNodePtr;
  // edge: refersTo
  genNodePtr = node.getRefersTo() ;
  if (genNodePtr) {
    const struc::Package& endNodeRef = dynamic_cast<const struc::Package&>(*genNodePtr);
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitPackageType_RefersTo(node, endNodeRef);
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
      if (traversaldCrossEdges[edkPackageType_RefersTo]) {
        endNodeRef.accept(*this);
      }
    }
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitEndPackageType_RefersTo(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;
  }
}

void AlgorithmPreorder::visit(const type::PackageType& node, bool callFirst /*= true*/){
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

void AlgorithmPreorder::visitAllEdges(const type::ParameterizedType& node, bool callFirst /*= true*/){
  visitAllEdges(dynamic_cast<const type::ScopedType&>(node),false);

  std::list<Visitor*>::iterator itVisitors;

  const base::Base* genNodePtr;
  // edge: rawType
  genNodePtr = node.getRawType() ;
  if (genNodePtr) {
    const type::Type& endNodeRef = dynamic_cast<const type::Type&>(*genNodePtr);
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitParameterizedType_RawType(node, endNodeRef);
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
      if (traversaldCrossEdges[edkParameterizedType_RawType]) {
        endNodeRef.accept(*this);
      }
    }
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitEndParameterizedType_RawType(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;
  }

  // edge: argumentTypes
  for (ListIterator<type::Type> it = node.getArgumentTypesListIteratorBegin(); it != node.getArgumentTypesListIteratorEnd(); ++it) {
    const type::Type& endNodeRef = *it;
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitParameterizedType_ArgumentTypes(node, endNodeRef);
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
      if (traversaldCrossEdges[edkParameterizedType_ArgumentTypes]) {
        endNodeRef.accept(*this);
      }
    }
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitEndParameterizedType_ArgumentTypes(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;
  }
}

void AlgorithmPreorder::visit(const type::ParameterizedType& node, bool callFirst /*= true*/){
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

void AlgorithmPreorder::visitAllEdges(const type::PrimitiveType& node, bool callFirst /*= true*/){
  visitAllEdges(dynamic_cast<const type::Type&>(node),false);
}

void AlgorithmPreorder::visitAllEdges(const type::ScopedType& node, bool callFirst /*= true*/){
  visitAllEdges(dynamic_cast<const type::Type&>(node),false);

  std::list<Visitor*>::iterator itVisitors;

  const base::Base* genNodePtr;
  // edge: owner
  genNodePtr = node.getOwner() ;
  if (genNodePtr) {
    const type::Type& endNodeRef = dynamic_cast<const type::Type&>(*genNodePtr);
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitScopedType_Owner(node, endNodeRef);
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
      if (traversaldCrossEdges[edkScopedType_Owner]) {
        endNodeRef.accept(*this);
      }
    }
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitEndScopedType_Owner(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;
  }
}

void AlgorithmPreorder::visitAllEdges(const type::ShortType& node, bool callFirst /*= true*/){
  visitAllEdges(dynamic_cast<const type::PrimitiveType&>(node),false);
}

void AlgorithmPreorder::visit(const type::ShortType& node, bool callFirst /*= true*/){
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

void AlgorithmPreorder::visitAllEdges(const type::TypeVariable& node, bool callFirst /*= true*/){
  visitAllEdges(dynamic_cast<const type::Type&>(node),false);

  std::list<Visitor*>::iterator itVisitors;

  const base::Base* genNodePtr;
  // edge: refersTo
  genNodePtr = node.getRefersTo() ;
  if (genNodePtr) {
    const struc::TypeParameter& endNodeRef = dynamic_cast<const struc::TypeParameter&>(*genNodePtr);
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitTypeVariable_RefersTo(node, endNodeRef);
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
      if (traversaldCrossEdges[edkTypeVariable_RefersTo]) {
        endNodeRef.accept(*this);
      }
    }
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitEndTypeVariable_RefersTo(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;
  }
}

void AlgorithmPreorder::visit(const type::TypeVariable& node, bool callFirst /*= true*/){
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

void AlgorithmPreorder::visitAllEdges(const type::UnboundedWildcardType& node, bool callFirst /*= true*/){
  visitAllEdges(dynamic_cast<const type::WildcardType&>(node),false);
}

void AlgorithmPreorder::visit(const type::UnboundedWildcardType& node, bool callFirst /*= true*/){
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

void AlgorithmPreorder::visitAllEdges(const type::UnionType& node, bool callFirst /*= true*/){
  visitAllEdges(dynamic_cast<const type::Type&>(node),false);

  std::list<Visitor*>::iterator itVisitors;

  // edge: alternatives
  for (ListIterator<type::Type> it = node.getAlternativesListIteratorBegin(); it != node.getAlternativesListIteratorEnd(); ++it) {
    const type::Type& endNodeRef = *it;
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitUnionType_Alternatives(node, endNodeRef);
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
      if (traversaldCrossEdges[edkUnionType_Alternatives]) {
        endNodeRef.accept(*this);
      }
    }
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitEndUnionType_Alternatives(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;
  }
}

void AlgorithmPreorder::visit(const type::UnionType& node, bool callFirst /*= true*/){
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

void AlgorithmPreorder::visitAllEdges(const type::UpperBoundedWildcardType& node, bool callFirst /*= true*/){
  visitAllEdges(dynamic_cast<const type::BoundedWildcardType&>(node),false);
}

void AlgorithmPreorder::visit(const type::UpperBoundedWildcardType& node, bool callFirst /*= true*/){
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

void AlgorithmPreorder::visitAllEdges(const type::VoidType& node, bool callFirst /*= true*/){
  visitAllEdges(dynamic_cast<const type::PrimitiveType&>(node),false);
}

void AlgorithmPreorder::visit(const type::VoidType& node, bool callFirst /*= true*/){
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

void AlgorithmPreorder::visitAllEdges(const type::WildcardType& node, bool callFirst /*= true*/){
  visitAllEdges(dynamic_cast<const type::Type&>(node),false);

  std::list<Visitor*>::iterator itVisitors;

  const base::Base* genNodePtr;
  // edge: bound
  genNodePtr = node.getBound() ;
  if (genNodePtr) {
    const type::Type& endNodeRef = dynamic_cast<const type::Type&>(*genNodePtr);
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitWildcardType_Bound(node, endNodeRef);
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
      if (traversaldCrossEdges[edkWildcardType_Bound]) {
        endNodeRef.accept(*this);
      }
    }
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitEndWildcardType_Bound(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;
  }
}

void AlgorithmPreorder::startPreorder(){

  if (!fact){
    throw JavaException(COLUMBUS_LOCATION, CMSG_EX_YOU_MUST_GIVE_A_FACTORY_AT_FIRST);
  }

  if (visitorList.empty()){
    throw JavaException(COLUMBUS_LOCATION, CMSG_EX_DON_T_HAVE_ANY_VISITOR);
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
