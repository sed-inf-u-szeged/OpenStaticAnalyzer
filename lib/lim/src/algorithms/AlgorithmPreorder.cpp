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

#include "lim/inc/lim.h"
#include "common/inc/WriteMessage.h"
#include "lim/inc/messages.h"
#include <string.h>

#ifdef DEBUG_PREORDER
#include <iostream>
#endif


namespace columbus { namespace lim { namespace asg {
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
  memset(traversaldCrossEdges,false,sizeof(bool)*51);
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
  visitAllEdges(dynamic_cast<const base::Base&>(node),false);
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

void AlgorithmPreorder::visitAllEdges(const base::Component& node, bool callFirst /*= true*/){
  visitAllEdges(dynamic_cast<const base::Named&>(node),false);

  std::list<Visitor*>::iterator itVisitors;

  // edge: compilationUnit
  for (ListIterator<physical::File> it = node.getCompilationUnitListIteratorBegin(); it != node.getCompilationUnitListIteratorEnd(); ++it) {
    const physical::File& endNodeRef = *it;
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitComponent_CompilationUnit(node, endNodeRef);
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
      if (traversaldCrossEdges[edkComponent_CompilationUnit]) {
        endNodeRef.accept(*this);
      }
    }
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitEndComponent_CompilationUnit(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;
  }

  // edge: contains
  for (ListIterator<base::Component> it = node.getContainsListIteratorBegin(); it != node.getContainsListIteratorEnd(); ++it) {
    const base::Component& endNodeRef = *it;
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitComponent_Contains(node, endNodeRef);
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
      if (traversaldCrossEdges[edkComponent_Contains]) {
        endNodeRef.accept(*this);
      }
    }
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitEndComponent_Contains(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;
  }

  // edge: hasFiles
  for (ListIterator<physical::File> it = node.getFilesListIteratorBegin(); it != node.getFilesListIteratorEnd(); ++it) {
    const physical::File& endNodeRef = *it;
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitComponent_HasFiles(node, endNodeRef);
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
      if (traversaldCrossEdges[edkComponent_HasFiles]) {
        endNodeRef.accept(*this);
      }
    }
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitEndComponent_HasFiles(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;
  }
}

void AlgorithmPreorder::visit(const base::Component& node, bool callFirst /*= true*/){
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

void AlgorithmPreorder::visitAllEdges(const base::ControlFlowBlock& node, bool callFirst /*= true*/){
  visitAllEdges(dynamic_cast<const base::Base&>(node),false);

  std::list<Visitor*>::iterator itVisitors;

  // edge: calls
  for (ListIterator<logical::Method> it = node.getCallsListIteratorBegin(); it != node.getCallsListIteratorEnd(); ++it) {
    const logical::Method& endNodeRef = *it;
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitControlFlowBlock_Calls(node, endNodeRef);
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
      if (traversaldCrossEdges[edkControlFlowBlock_Calls]) {
        endNodeRef.accept(*this);
      }
    }
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitEndControlFlowBlock_Calls(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;
  }

  // edge: pred
  for (ListIterator<base::ControlFlowBlock> it = node.getPredListIteratorBegin(); it != node.getPredListIteratorEnd(); ++it) {
    const base::ControlFlowBlock& endNodeRef = *it;
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitControlFlowBlock_Pred(node, endNodeRef);
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
      if (traversaldCrossEdges[edkControlFlowBlock_Pred]) {
        endNodeRef.accept(*this);
      }
    }
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitEndControlFlowBlock_Pred(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;
  }
}

void AlgorithmPreorder::visit(const base::ControlFlowBlock& node, bool callFirst /*= true*/){
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
  visitAllEdges(dynamic_cast<const base::Base&>(node),false);

  std::list<Visitor*>::iterator itVisitors;

  // edge: dependsOn
  for (ListIteratorAssocString<base::Named> it = node.getDependsOnListIteratorAssocBegin(); it != node.getDependsOnListIteratorAssocEnd(); ++it) {
    const base::Named& endNodeRef = *it;
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitNamed_DependsOn(node, endNodeRef, it.getAssocClass());
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
      if (traversaldCrossEdges[edkNamed_DependsOn]) {
        endNodeRef.accept(*this);
      }
    }
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitEndNamed_DependsOn(node, endNodeRef, it.getAssocClass());
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;
  }
}

void AlgorithmPreorder::visitAllEdges(const logical::Attribute& node, bool callFirst /*= true*/){
  visitAllEdges(dynamic_cast<const logical::Member&>(node),false);

  std::list<Visitor*>::iterator itVisitors;

  // edge: calls
  for (ListIterator<logical::MethodCall> it = node.getCallsListIteratorBegin(); it != node.getCallsListIteratorEnd(); ++it) {
    const logical::MethodCall& endNodeRef = *it;
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitAttribute_Calls(node, endNodeRef);
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
      if (traversaldCrossEdges[edkAttribute_Calls]) {
        endNodeRef.accept(*this);
      }
    }
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitEndAttribute_Calls(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;
  }

  // edge: hasType
  for (ListIterator<type::Type> it = node.getTypeListIteratorBegin(); it != node.getTypeListIteratorEnd(); ++it) {
    const type::Type& endNodeRef = *it;
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitAttribute_HasType(node, endNodeRef);
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
      if (traversaldCrossEdges[edkAttribute_HasType]) {
        endNodeRef.accept(*this);
      }
    }
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitEndAttribute_HasType(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;
  }
}

void AlgorithmPreorder::visit(const logical::Attribute& node, bool callFirst /*= true*/){
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

void AlgorithmPreorder::visitAllEdges(const logical::AttributeAccess& node, bool callFirst /*= true*/){
  visitAllEdges(dynamic_cast<const base::Base&>(node),false);

  std::list<Visitor*>::iterator itVisitors;

  const base::Base* genNodePtr;
  // edge: attribute
  genNodePtr = node.getAttribute() ;
  if (genNodePtr) {
    const logical::Attribute& endNodeRef = dynamic_cast<const logical::Attribute&>(*genNodePtr);
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitAttributeAccess_Attribute(node, endNodeRef);
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
      if (traversaldCrossEdges[edkAttributeAccess_Attribute]) {
        endNodeRef.accept(*this);
      }
    }
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitEndAttributeAccess_Attribute(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;
  }
}

void AlgorithmPreorder::visit(const logical::AttributeAccess& node, bool callFirst /*= true*/){
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

void AlgorithmPreorder::visitAllEdges(const logical::Class& node, bool callFirst /*= true*/){
  visitAllEdges(dynamic_cast<const logical::Scope&>(node),false);

  std::list<Visitor*>::iterator itVisitors;

  // edge: extends
  for (ListIterator<logical::Class> it = node.getExtendsListIteratorBegin(); it != node.getExtendsListIteratorEnd(); ++it) {
    const logical::Class& endNodeRef = *it;
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitClass_Extends(node, endNodeRef);
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
      if (traversaldCrossEdges[edkClass_Extends]) {
        endNodeRef.accept(*this);
      }
    }
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitEndClass_Extends(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;
  }

  // edge: grantsFriendship
  for (ListIterator<logical::Friendship> it = node.getGrantsFriendshipListIteratorBegin(); it != node.getGrantsFriendshipListIteratorEnd(); ++it) {
    const logical::Friendship& endNodeRef = *it;
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitClass_GrantsFriendship(node, endNodeRef);
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
      if (traversaldCrossEdges[edkClass_GrantsFriendship]) {
        endNodeRef.accept(*this);
      }
    }
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitEndClass_GrantsFriendship(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;
  }

  // edge: isSubclass
  for (ListIterator<type::Type> it = node.getIsSubclassListIteratorBegin(); it != node.getIsSubclassListIteratorEnd(); ++it) {
    const type::Type& endNodeRef = *it;
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitClass_IsSubclass(node, endNodeRef);
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
      if (traversaldCrossEdges[edkClass_IsSubclass]) {
        endNodeRef.accept(*this);
      }
    }
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitEndClass_IsSubclass(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;
  }
}

void AlgorithmPreorder::visit(const logical::Class& node, bool callFirst /*= true*/){
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

void AlgorithmPreorder::visitAllEdges(const logical::ClassGeneric& node, bool callFirst /*= true*/){
  visitAllEdges(dynamic_cast<const logical::Class&>(node),false);

  std::list<Visitor*>::iterator itVisitors;

  // edge: hasGenericParameter
  for (ListIterator<logical::GenericParameter> it = node.getGenericParameterListIteratorBegin(); it != node.getGenericParameterListIteratorEnd(); ++it) {
    const logical::GenericParameter& endNodeRef = *it;
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitClassGeneric_HasGenericParameter(node, endNodeRef);
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
      (*itVisitors)->visitEndClassGeneric_HasGenericParameter(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;
  }
}

void AlgorithmPreorder::visit(const logical::ClassGeneric& node, bool callFirst /*= true*/){
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

void AlgorithmPreorder::visitAllEdges(const logical::ClassGenericInstance& node, bool callFirst /*= true*/){
  visitAllEdges(dynamic_cast<const logical::Class&>(node),false);

  std::list<Visitor*>::iterator itVisitors;

  // edge: hasArguments
  for (ListIteratorAssocTypeArgumentConstraintKind<type::Type> it = node.getArgumentsListIteratorAssocBegin(); it != node.getArgumentsListIteratorAssocEnd(); ++it) {
    const type::Type& endNodeRef = *it;
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitClassGenericInstance_HasArguments(node, endNodeRef, it.getAssocClass());
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
      if (traversaldCrossEdges[edkClassGenericInstance_HasArguments]) {
        endNodeRef.accept(*this);
      }
    }
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitEndClassGenericInstance_HasArguments(node, endNodeRef, it.getAssocClass());
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;
  }
}

void AlgorithmPreorder::visit(const logical::ClassGenericInstance& node, bool callFirst /*= true*/){
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

void AlgorithmPreorder::visitAllEdges(const logical::ClassGenericSpec& node, bool callFirst /*= true*/){
  visitAllEdges(dynamic_cast<const logical::ClassGeneric&>(node),false);

  std::list<Visitor*>::iterator itVisitors;

  // edge: hasArguments
  for (ListIteratorAssocTypeArgumentConstraintKind<type::Type> it = node.getArgumentsListIteratorAssocBegin(); it != node.getArgumentsListIteratorAssocEnd(); ++it) {
    const type::Type& endNodeRef = *it;
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitClassGenericSpec_HasArguments(node, endNodeRef, it.getAssocClass());
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
      if (traversaldCrossEdges[edkClassGenericSpec_HasArguments]) {
        endNodeRef.accept(*this);
      }
    }
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitEndClassGenericSpec_HasArguments(node, endNodeRef, it.getAssocClass());
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;
  }

  const base::Base* genNodePtr;
  // edge: specialize
  genNodePtr = node.getSpecialize() ;
  if (genNodePtr) {
    const logical::ClassGeneric& endNodeRef = dynamic_cast<const logical::ClassGeneric&>(*genNodePtr);
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitClassGenericSpec_Specialize(node, endNodeRef);
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
      if (traversaldCrossEdges[edkClassGenericSpec_Specialize]) {
        endNodeRef.accept(*this);
      }
    }
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitEndClassGenericSpec_Specialize(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;
  }
}

void AlgorithmPreorder::visit(const logical::ClassGenericSpec& node, bool callFirst /*= true*/){
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

void AlgorithmPreorder::visitAllEdges(const logical::Friendship& node, bool callFirst /*= true*/){
  visitAllEdges(dynamic_cast<const base::Base&>(node),false);

  std::list<Visitor*>::iterator itVisitors;

  const base::Base* genNodePtr;
  // edge: friend
  genNodePtr = node.getFriend() ;
  if (genNodePtr) {
    const logical::Scope& endNodeRef = dynamic_cast<const logical::Scope&>(*genNodePtr);
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitFriendship_Friend(node, endNodeRef);
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
      if (traversaldCrossEdges[edkFriendship_Friend]) {
        endNodeRef.accept(*this);
      }
    }
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitEndFriendship_Friend(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;
  }
}

void AlgorithmPreorder::visit(const logical::Friendship& node, bool callFirst /*= true*/){
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

void AlgorithmPreorder::visitAllEdges(const logical::GenericParameter& node, bool callFirst /*= true*/){
  visitAllEdges(dynamic_cast<const base::Named&>(node),false);

  std::list<Visitor*>::iterator itVisitors;

  // edge: hasParameterConstraint
  for (ListIterator<type::Type> it = node.getParameterConstraintListIteratorBegin(); it != node.getParameterConstraintListIteratorEnd(); ++it) {
    const type::Type& endNodeRef = *it;
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitGenericParameter_HasParameterConstraint(node, endNodeRef);
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
      if (traversaldCrossEdges[edkGenericParameter_HasParameterConstraint]) {
        endNodeRef.accept(*this);
      }
    }
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitEndGenericParameter_HasParameterConstraint(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;
  }
}

void AlgorithmPreorder::visit(const logical::GenericParameter& node, bool callFirst /*= true*/){
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

void AlgorithmPreorder::visitAllEdges(const logical::Member& node, bool callFirst /*= true*/){
  visitAllEdges(dynamic_cast<const base::Named&>(node),false);

  std::list<Visitor*>::iterator itVisitors;

  const base::Base* genNodePtr;
  // edge: aggregated
  genNodePtr = node.getAggregated() ;
  if (genNodePtr) {
    const logical::Member& endNodeRef = dynamic_cast<const logical::Member&>(*genNodePtr);
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitMember_Aggregated(node, endNodeRef);
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
      if (traversaldCrossEdges[edkMember_Aggregated]) {
        endNodeRef.accept(*this);
      }
    }
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitEndMember_Aggregated(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;
  }

  // edge: belongsTo
  for (ListIterator<base::Component> it = node.getBelongsToListIteratorBegin(); it != node.getBelongsToListIteratorEnd(); ++it) {
    const base::Component& endNodeRef = *it;
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitMember_BelongsTo(node, endNodeRef);
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
      if (traversaldCrossEdges[edkMember_BelongsTo]) {
        endNodeRef.accept(*this);
      }
    }
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitEndMember_BelongsTo(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;
  }

  // edge: compilationUnit
  for (ListIterator<physical::File> it = node.getCompilationUnitListIteratorBegin(); it != node.getCompilationUnitListIteratorEnd(); ++it) {
    const physical::File& endNodeRef = *it;
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitMember_CompilationUnit(node, endNodeRef);
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
      if (traversaldCrossEdges[edkMember_CompilationUnit]) {
        endNodeRef.accept(*this);
      }
    }
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitEndMember_CompilationUnit(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;
  }

  // edge: declares
  genNodePtr = node.getDeclares() ;
  if (genNodePtr) {
    const logical::Member& endNodeRef = dynamic_cast<const logical::Member&>(*genNodePtr);
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitMember_Declares(node, endNodeRef);
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
      if (traversaldCrossEdges[edkMember_Declares]) {
        endNodeRef.accept(*this);
      }
    }
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitEndMember_Declares(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;
  }

  // edge: hasComment
  for (ListIterator<base::Comment> it = node.getCommentListIteratorBegin(); it != node.getCommentListIteratorEnd(); ++it) {
    const base::Comment& endNodeRef = *it;
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitMember_HasComment(node, endNodeRef);
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
      if (traversaldCrossEdges[edkMember_HasComment]) {
        endNodeRef.accept(*this);
      }
    }
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitEndMember_HasComment(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;
  }

  // edge: instance
  for (ListIterator<logical::Member> it = node.getInstanceListIteratorBegin(); it != node.getInstanceListIteratorEnd(); ++it) {
    const logical::Member& endNodeRef = *it;
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitMember_Instance(node, endNodeRef);
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
      if (traversaldCrossEdges[edkMember_Instance]) {
        endNodeRef.accept(*this);
      }
    }
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitEndMember_Instance(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;
  }

  // edge: isContainedIn
  for (ListIteratorAssocSourcePosition<physical::File> it = node.getIsContainedInListIteratorAssocBegin(); it != node.getIsContainedInListIteratorAssocEnd(); ++it) {
    const physical::File& endNodeRef = *it;
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitMember_IsContainedIn(node, endNodeRef, it.getAssocClass());
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
      if (traversaldCrossEdges[edkMember_IsContainedIn]) {
        endNodeRef.accept(*this);
      }
    }
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitEndMember_IsContainedIn(node, endNodeRef, it.getAssocClass());
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;
  }

  // edge: languageVariant
  genNodePtr = node.getLanguageVariant() ;
  if (genNodePtr) {
    const logical::Member& endNodeRef = dynamic_cast<const logical::Member&>(*genNodePtr);
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitMember_LanguageVariant(node, endNodeRef);
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
      if (traversaldCrossEdges[edkMember_LanguageVariant]) {
        endNodeRef.accept(*this);
      }
    }
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitEndMember_LanguageVariant(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;
  }

  // edge: uses
  for (ListIterator<type::Type> it = node.getUsesListIteratorBegin(); it != node.getUsesListIteratorEnd(); ++it) {
    const type::Type& endNodeRef = *it;
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitMember_Uses(node, endNodeRef);
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
      if (traversaldCrossEdges[edkMember_Uses]) {
        endNodeRef.accept(*this);
      }
    }
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitEndMember_Uses(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;
  }

  // edge: variant
  for (ListIterator<logical::Member> it = node.getVariantListIteratorBegin(); it != node.getVariantListIteratorEnd(); ++it) {
    const logical::Member& endNodeRef = *it;
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitMember_Variant(node, endNodeRef);
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
      if (traversaldCrossEdges[edkMember_Variant]) {
        endNodeRef.accept(*this);
      }
    }
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitEndMember_Variant(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;
  }
}

void AlgorithmPreorder::visitAllEdges(const logical::Method& node, bool callFirst /*= true*/){
  visitAllEdges(dynamic_cast<const logical::Scope&>(node),false);

  std::list<Visitor*>::iterator itVisitors;

  // edge: accessesAttribute
  for (ListIterator<logical::AttributeAccess> it = node.getAccessesAttributeListIteratorBegin(); it != node.getAccessesAttributeListIteratorEnd(); ++it) {
    const logical::AttributeAccess& endNodeRef = *it;
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitMethod_AccessesAttribute(node, endNodeRef);
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
      if (traversaldCrossEdges[edkMethod_AccessesAttribute]) {
        endNodeRef.accept(*this);
      }
    }
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitEndMethod_AccessesAttribute(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;
  }

  // edge: calls
  for (ListIterator<logical::MethodCall> it = node.getCallsListIteratorBegin(); it != node.getCallsListIteratorEnd(); ++it) {
    const logical::MethodCall& endNodeRef = *it;
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitMethod_Calls(node, endNodeRef);
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
      if (traversaldCrossEdges[edkMethod_Calls]) {
        endNodeRef.accept(*this);
      }
    }
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitEndMethod_Calls(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;
  }

  // edge: canThrow
  for (ListIterator<type::Type> it = node.getCanThrowListIteratorBegin(); it != node.getCanThrowListIteratorEnd(); ++it) {
    const type::Type& endNodeRef = *it;
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitMethod_CanThrow(node, endNodeRef);
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
      if (traversaldCrossEdges[edkMethod_CanThrow]) {
        endNodeRef.accept(*this);
      }
    }
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitEndMethod_CanThrow(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;
  }

  // edge: hasControlFlowBlock
  for (ListIterator<base::ControlFlowBlock> it = node.getControlFlowBlockListIteratorBegin(); it != node.getControlFlowBlockListIteratorEnd(); ++it) {
    const base::ControlFlowBlock& endNodeRef = *it;
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitMethod_HasControlFlowBlock(node, endNodeRef);
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
      (*itVisitors)->visitEndMethod_HasControlFlowBlock(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;
  }

  // edge: hasParameter
  for (ListIterator<logical::Parameter> it = node.getParameterListIteratorBegin(); it != node.getParameterListIteratorEnd(); ++it) {
    const logical::Parameter& endNodeRef = *it;
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitMethod_HasParameter(node, endNodeRef);
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
      (*itVisitors)->visitEndMethod_HasParameter(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;
  }

  // edge: instantiates
  for (ListIterator<type::Type> it = node.getInstantiatesListIteratorBegin(); it != node.getInstantiatesListIteratorEnd(); ++it) {
    const type::Type& endNodeRef = *it;
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitMethod_Instantiates(node, endNodeRef);
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
      if (traversaldCrossEdges[edkMethod_Instantiates]) {
        endNodeRef.accept(*this);
      }
    }
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitEndMethod_Instantiates(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;
  }

  // edge: returns
  for (ListIterator<type::Type> it = node.getReturnsListIteratorBegin(); it != node.getReturnsListIteratorEnd(); ++it) {
    const type::Type& endNodeRef = *it;
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitMethod_Returns(node, endNodeRef);
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
      if (traversaldCrossEdges[edkMethod_Returns]) {
        endNodeRef.accept(*this);
      }
    }
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitEndMethod_Returns(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;
  }

  // edge: throws
  for (ListIterator<type::Type> it = node.getThrowsListIteratorBegin(); it != node.getThrowsListIteratorEnd(); ++it) {
    const type::Type& endNodeRef = *it;
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitMethod_Throws(node, endNodeRef);
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
      if (traversaldCrossEdges[edkMethod_Throws]) {
        endNodeRef.accept(*this);
      }
    }
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitEndMethod_Throws(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;
  }
}

void AlgorithmPreorder::visit(const logical::Method& node, bool callFirst /*= true*/){
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

void AlgorithmPreorder::visitAllEdges(const logical::MethodCall& node, bool callFirst /*= true*/){
  visitAllEdges(dynamic_cast<const base::Base&>(node),false);

  std::list<Visitor*>::iterator itVisitors;

  const base::Base* genNodePtr;
  // edge: method
  genNodePtr = node.getMethod() ;
  if (genNodePtr) {
    const logical::Method& endNodeRef = dynamic_cast<const logical::Method&>(*genNodePtr);
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitMethodCall_Method(node, endNodeRef);
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
      if (traversaldCrossEdges[edkMethodCall_Method]) {
        endNodeRef.accept(*this);
      }
    }
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitEndMethodCall_Method(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;
  }
}

void AlgorithmPreorder::visit(const logical::MethodCall& node, bool callFirst /*= true*/){
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

void AlgorithmPreorder::visitAllEdges(const logical::MethodGeneric& node, bool callFirst /*= true*/){
  visitAllEdges(dynamic_cast<const logical::Method&>(node),false);

  std::list<Visitor*>::iterator itVisitors;

  // edge: hasGenericParameter
  for (ListIterator<logical::GenericParameter> it = node.getGenericParameterListIteratorBegin(); it != node.getGenericParameterListIteratorEnd(); ++it) {
    const logical::GenericParameter& endNodeRef = *it;
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitMethodGeneric_HasGenericParameter(node, endNodeRef);
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
      (*itVisitors)->visitEndMethodGeneric_HasGenericParameter(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;
  }
}

void AlgorithmPreorder::visit(const logical::MethodGeneric& node, bool callFirst /*= true*/){
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

void AlgorithmPreorder::visitAllEdges(const logical::MethodGenericInstance& node, bool callFirst /*= true*/){
  visitAllEdges(dynamic_cast<const logical::Method&>(node),false);

  std::list<Visitor*>::iterator itVisitors;

  // edge: hasArguments
  for (ListIteratorAssocTypeArgumentConstraintKind<type::Type> it = node.getArgumentsListIteratorAssocBegin(); it != node.getArgumentsListIteratorAssocEnd(); ++it) {
    const type::Type& endNodeRef = *it;
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitMethodGenericInstance_HasArguments(node, endNodeRef, it.getAssocClass());
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
      if (traversaldCrossEdges[edkMethodGenericInstance_HasArguments]) {
        endNodeRef.accept(*this);
      }
    }
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitEndMethodGenericInstance_HasArguments(node, endNodeRef, it.getAssocClass());
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;
  }
}

void AlgorithmPreorder::visit(const logical::MethodGenericInstance& node, bool callFirst /*= true*/){
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

void AlgorithmPreorder::visitAllEdges(const logical::MethodGenericSpec& node, bool callFirst /*= true*/){
  visitAllEdges(dynamic_cast<const logical::MethodGeneric&>(node),false);

  std::list<Visitor*>::iterator itVisitors;

  // edge: hasArguments
  for (ListIteratorAssocTypeArgumentConstraintKind<type::Type> it = node.getArgumentsListIteratorAssocBegin(); it != node.getArgumentsListIteratorAssocEnd(); ++it) {
    const type::Type& endNodeRef = *it;
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitMethodGenericSpec_HasArguments(node, endNodeRef, it.getAssocClass());
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
      if (traversaldCrossEdges[edkMethodGenericSpec_HasArguments]) {
        endNodeRef.accept(*this);
      }
    }
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitEndMethodGenericSpec_HasArguments(node, endNodeRef, it.getAssocClass());
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;
  }

  const base::Base* genNodePtr;
  // edge: specialize
  genNodePtr = node.getSpecialize() ;
  if (genNodePtr) {
    const logical::MethodGeneric& endNodeRef = dynamic_cast<const logical::MethodGeneric&>(*genNodePtr);
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitMethodGenericSpec_Specialize(node, endNodeRef);
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
      if (traversaldCrossEdges[edkMethodGenericSpec_Specialize]) {
        endNodeRef.accept(*this);
      }
    }
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitEndMethodGenericSpec_Specialize(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;
  }
}

void AlgorithmPreorder::visit(const logical::MethodGenericSpec& node, bool callFirst /*= true*/){
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

void AlgorithmPreorder::visitAllEdges(const logical::Package& node, bool callFirst /*= true*/){
  visitAllEdges(dynamic_cast<const logical::Scope&>(node),false);
}

void AlgorithmPreorder::visit(const logical::Package& node, bool callFirst /*= true*/){
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

void AlgorithmPreorder::visitAllEdges(const logical::Parameter& node, bool callFirst /*= true*/){
  visitAllEdges(dynamic_cast<const base::Named&>(node),false);

  std::list<Visitor*>::iterator itVisitors;

  const base::Base* genNodePtr;
  // edge: hasType
  genNodePtr = node.getType() ;
  if (genNodePtr) {
    const type::Type& endNodeRef = dynamic_cast<const type::Type&>(*genNodePtr);
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitParameter_HasType(node, endNodeRef);
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
      if (traversaldCrossEdges[edkParameter_HasType]) {
        endNodeRef.accept(*this);
      }
    }
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitEndParameter_HasType(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;
  }
}

void AlgorithmPreorder::visit(const logical::Parameter& node, bool callFirst /*= true*/){
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

void AlgorithmPreorder::visitAllEdges(const logical::Scope& node, bool callFirst /*= true*/){
  visitAllEdges(dynamic_cast<const logical::Member&>(node),false);

  std::list<Visitor*>::iterator itVisitors;

  // edge: hasMember
  for (ListIterator<logical::Member> it = node.getMemberListIteratorBegin(); it != node.getMemberListIteratorEnd(); ++it) {
    const logical::Member& endNodeRef = *it;
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitScope_HasMember(node, endNodeRef);
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
      if (traversaldCrossEdges[edkScope_HasMember]) {
        endNodeRef.accept(*this);
      }
    }
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitEndScope_HasMember(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;
  }
}

void AlgorithmPreorder::visitAllEdges(const physical::FSEntry& node, bool callFirst /*= true*/){
  visitAllEdges(dynamic_cast<const base::Named&>(node),false);
}

void AlgorithmPreorder::visitAllEdges(const physical::File& node, bool callFirst /*= true*/){
  visitAllEdges(dynamic_cast<const physical::FSEntry&>(node),false);

  std::list<Visitor*>::iterator itVisitors;

  // edge: hasComment
  for (ListIterator<base::Comment> it = node.getCommentListIteratorBegin(); it != node.getCommentListIteratorEnd(); ++it) {
    const base::Comment& endNodeRef = *it;
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitFile_HasComment(node, endNodeRef);
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
      if (traversaldCrossEdges[edkFile_HasComment]) {
        endNodeRef.accept(*this);
      }
    }
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitEndFile_HasComment(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;
  }

  // edge: includes
  for (ListIterator<physical::File> it = node.getIncludesListIteratorBegin(); it != node.getIncludesListIteratorEnd(); ++it) {
    const physical::File& endNodeRef = *it;
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitFile_Includes(node, endNodeRef);
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
      if (traversaldCrossEdges[edkFile_Includes]) {
        endNodeRef.accept(*this);
      }
    }
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitEndFile_Includes(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;
  }
}

void AlgorithmPreorder::visit(const physical::File& node, bool callFirst /*= true*/){
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

void AlgorithmPreorder::visitAllEdges(const physical::FileSystem& node, bool callFirst /*= true*/){
  visitAllEdges(dynamic_cast<const base::Named&>(node),false);

  std::list<Visitor*>::iterator itVisitors;

  // edge: hasFSEntry
  for (ListIterator<physical::FSEntry> it = node.getFSEntryListIteratorBegin(); it != node.getFSEntryListIteratorEnd(); ++it) {
    const physical::FSEntry& endNodeRef = *it;
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitFileSystem_HasFSEntry(node, endNodeRef);
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
      (*itVisitors)->visitEndFileSystem_HasFSEntry(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;
  }
}

void AlgorithmPreorder::visit(const physical::FileSystem& node, bool callFirst /*= true*/){
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

void AlgorithmPreorder::visitAllEdges(const physical::Folder& node, bool callFirst /*= true*/){
  visitAllEdges(dynamic_cast<const physical::FSEntry&>(node),false);

  std::list<Visitor*>::iterator itVisitors;

  // edge: contains
  for (ListIterator<physical::FSEntry> it = node.getContainsListIteratorBegin(); it != node.getContainsListIteratorEnd(); ++it) {
    const physical::FSEntry& endNodeRef = *it;
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitFolder_Contains(node, endNodeRef);
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
      (*itVisitors)->visitEndFolder_Contains(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;
  }
}

void AlgorithmPreorder::visit(const physical::Folder& node, bool callFirst /*= true*/){
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
  visitAllEdges(dynamic_cast<const base::Base&>(node),false);
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

  std::list<Visitor*>::iterator itVisitors;

  // edge: hasTypeFormer
  for (ListIterator<type::TypeFormer> it = node.getTypeFormerListIteratorBegin(); it != node.getTypeFormerListIteratorEnd(); ++it) {
    const type::TypeFormer& endNodeRef = *it;
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitType_HasTypeFormer(node, endNodeRef);
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
      if (traversaldCrossEdges[edkType_HasTypeFormer]) {
        endNodeRef.accept(*this);
      }
    }
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitEndType_HasTypeFormer(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;
  }
}

void AlgorithmPreorder::visit(const type::Type& node, bool callFirst /*= true*/){
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

void AlgorithmPreorder::visitAllEdges(const type::TypeFormer& node, bool callFirst /*= true*/){
  visitAllEdges(dynamic_cast<const base::Base&>(node),false);
}

void AlgorithmPreorder::visitAllEdges(const type::TypeFormerArray& node, bool callFirst /*= true*/){
  visitAllEdges(dynamic_cast<const type::TypeFormer&>(node),false);
}

void AlgorithmPreorder::visit(const type::TypeFormerArray& node, bool callFirst /*= true*/){
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

void AlgorithmPreorder::visitAllEdges(const type::TypeFormerMethod& node, bool callFirst /*= true*/){
  visitAllEdges(dynamic_cast<const type::TypeFormer&>(node),false);

  std::list<Visitor*>::iterator itVisitors;

  // edge: hasParameterType
  for (ListIteratorAssocParameterKind<type::Type> it = node.getParameterTypeListIteratorAssocBegin(); it != node.getParameterTypeListIteratorAssocEnd(); ++it) {
    const type::Type& endNodeRef = *it;
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitTypeFormerMethod_HasParameterType(node, endNodeRef, it.getAssocClass());
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
      if (traversaldCrossEdges[edkTypeFormerMethod_HasParameterType]) {
        endNodeRef.accept(*this);
      }
    }
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitEndTypeFormerMethod_HasParameterType(node, endNodeRef, it.getAssocClass());
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;
  }

  const base::Base* genNodePtr;
  // edge: hasReturnType
  genNodePtr = node.getReturnType() ;
  if (genNodePtr) {
    const type::Type& endNodeRef = dynamic_cast<const type::Type&>(*genNodePtr);
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitTypeFormerMethod_HasReturnType(node, endNodeRef);
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
      if (traversaldCrossEdges[edkTypeFormerMethod_HasReturnType]) {
        endNodeRef.accept(*this);
      }
    }
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitEndTypeFormerMethod_HasReturnType(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;
  }
}

void AlgorithmPreorder::visit(const type::TypeFormerMethod& node, bool callFirst /*= true*/){
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

void AlgorithmPreorder::visitAllEdges(const type::TypeFormerNonType& node, bool callFirst /*= true*/){
  visitAllEdges(dynamic_cast<const type::TypeFormer&>(node),false);
}

void AlgorithmPreorder::visit(const type::TypeFormerNonType& node, bool callFirst /*= true*/){
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

void AlgorithmPreorder::visitAllEdges(const type::TypeFormerPointer& node, bool callFirst /*= true*/){
  visitAllEdges(dynamic_cast<const type::TypeFormer&>(node),false);
}

void AlgorithmPreorder::visit(const type::TypeFormerPointer& node, bool callFirst /*= true*/){
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

void AlgorithmPreorder::visitAllEdges(const type::TypeFormerType& node, bool callFirst /*= true*/){
  visitAllEdges(dynamic_cast<const type::TypeFormer&>(node),false);

  std::list<Visitor*>::iterator itVisitors;

  const base::Base* genNodePtr;
  // edge: refersTo
  genNodePtr = node.getRefersTo() ;
  if (genNodePtr) {
    const base::Base& endNodeRef = *genNodePtr;
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitTypeFormerType_RefersTo(node, endNodeRef);
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
      if (traversaldCrossEdges[edkTypeFormerType_RefersTo]) {
        endNodeRef.accept(*this);
      }
    }
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitEndTypeFormerType_RefersTo(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;
  }
}

void AlgorithmPreorder::visit(const type::TypeFormerType& node, bool callFirst /*= true*/){
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

void AlgorithmPreorder::startPreorder(){

  if (!fact){
    throw LimException(COLUMBUS_LOCATION, CMSG_EX_YOU_MUST_GIVE_A_FACTORY_AT_FIRST);
  }

  if (visitorList.empty()){
    throw LimException(COLUMBUS_LOCATION, CMSG_EX_DON_T_HAVE_ANY_VISITOR);
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
