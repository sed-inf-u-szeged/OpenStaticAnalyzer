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

#include "genealogy/inc/genealogy.h"
#include "common/inc/WriteMessage.h"
#include "genealogy/inc/messages.h"
#include <string.h>

#ifdef DEBUG_PREORDER
#include <iostream>
#endif


namespace columbus { namespace genealogy { 
AlgorithmPreorder::AlgorithmPreorder()
  : Algorithm(),
  safeMode(false),
  visitedNodes(),
  unvisitedNodes(),
  visitCrossEdgeTree(false),
  needPreorderStop(false),
  apRoot(NULL),
  visitorList(false),
  fact(NULL),
  traversaldCrossEdges()
{
  memset(traversaldCrossEdges,false,sizeof(bool)*22);
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

void AlgorithmPreorder::run() {
  mainRun(NULL, NULL, NULL);
}

void AlgorithmPreorder::run(const Base& node) {
  mainRun(NULL, NULL, &node);
}

void AlgorithmPreorder::run(const Factory& fact, Visitor& visitor) {
  mainRun(&fact, &visitor, NULL);
}

void AlgorithmPreorder::run(const Factory& fact, Visitor& visitor, const Base& node) {
  mainRun(&fact, &visitor, &node);
}

void AlgorithmPreorder::run(const Factory& fact, Visitor& visitor, NodeId nodeId) {
  mainRun(&fact, &visitor, fact.getPointer(nodeId));
}

void AlgorithmPreorder::mainRun(const Factory* _fact, Visitor* visitor, const Base* node) {
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
      if ( fact->isIndividual(i)){
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

void AlgorithmPreorder::visitAllEdges(const Base& node, bool callFirst /*= true*/){
}

void AlgorithmPreorder::visitAllEdges(const Project& node, bool callFirst /*= true*/){
  visitAllEdges(dynamic_cast<const Base&>(node),false);

  std::list<Visitor*>::iterator itVisitors;

  // edge: systems
  for (ListIterator<System> it = node.getSystemsListIteratorBegin(); it != node.getSystemsListIteratorEnd(); ++it) {
    const System& endNodeRef = *it;
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitProject_Systems(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;

    endNodeRef.accept(*this);
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitEndProject_Systems(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;
  }
}

void AlgorithmPreorder::visit(const Project& node, bool callFirst /*= true*/){
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

void AlgorithmPreorder::visitAllEdges(const Trackable& node, bool callFirst /*= true*/){
  visitAllEdges(dynamic_cast<const Base&>(node),false);

  std::list<Visitor*>::iterator itVisitors;

  // edge: prev
  for (ListIterator<Trackable> it = node.getPrevListIteratorBegin(); it != node.getPrevListIteratorEnd(); ++it) {
    const Trackable& endNodeRef = *it;
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitTrackable_Prev(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;

    if (apRoot) {
      if (visitCrossEdgeTree) {
        unvisitedNodes[endNodeRef.getId()] = true;
      }
    }
    if (traversaldCrossEdges[edkTrackable_Prev]) {
      endNodeRef.accept(*this);
    }
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitEndTrackable_Prev(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;
  }

  // edge: next
  for (ListIterator<Trackable> it = node.getNextListIteratorBegin(); it != node.getNextListIteratorEnd(); ++it) {
    const Trackable& endNodeRef = *it;
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitTrackable_Next(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;

    if (apRoot) {
      if (visitCrossEdgeTree) {
        unvisitedNodes[endNodeRef.getId()] = true;
      }
    }
    if (traversaldCrossEdges[edkTrackable_Next]) {
      endNodeRef.accept(*this);
    }
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitEndTrackable_Next(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;
  }
}

void AlgorithmPreorder::visit(const Trackable& node, bool callFirst /*= true*/){
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

void AlgorithmPreorder::visitAllEdges(const Component& node, bool callFirst /*= true*/){
  visitAllEdges(dynamic_cast<const Base&>(node),false);
}

void AlgorithmPreorder::visit(const Component& node, bool callFirst /*= true*/){
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

void AlgorithmPreorder::visitAllEdges(const SourceCodeElement& node, bool callFirst /*= true*/){
  visitAllEdges(dynamic_cast<const Base&>(node),false);
}

void AlgorithmPreorder::visit(const SourceCodeElement& node, bool callFirst /*= true*/){
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

void AlgorithmPreorder::visitAllEdges(const System& node, bool callFirst /*= true*/){
  visitAllEdges(dynamic_cast<const Trackable&>(node),false);

  std::list<Visitor*>::iterator itVisitors;

  // edge: components
  for (ListIterator<Component> it = node.getComponentsListIteratorBegin(); it != node.getComponentsListIteratorEnd(); ++it) {
    const Component& endNodeRef = *it;
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitSystem_Components(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;

    endNodeRef.accept(*this);
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitEndSystem_Components(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;
  }

  // edge: cloneClasses
  for (ListIterator<CloneClass> it = node.getCloneClassesListIteratorBegin(); it != node.getCloneClassesListIteratorEnd(); ++it) {
    const CloneClass& endNodeRef = *it;
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitSystem_CloneClasses(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;

    endNodeRef.accept(*this);
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitEndSystem_CloneClasses(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;
  }

  // edge: smells
  for (ListIterator<StructuralClone> it = node.getSmellsListIteratorBegin(); it != node.getSmellsListIteratorEnd(); ++it) {
    const StructuralClone& endNodeRef = *it;
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitSystem_Smells(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;

    endNodeRef.accept(*this);
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitEndSystem_Smells(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;
  }

  const Base* genNodePtr;
  // edge: next
  genNodePtr = node.getNext() ;
  if (genNodePtr) {
    const System& endNodeRef = dynamic_cast<const System&>(*genNodePtr);
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitSystem_Next(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;

    if (apRoot) {
      if (visitCrossEdgeTree) {
        unvisitedNodes[endNodeRef.getId()] = true;
      }
    }
    if (traversaldCrossEdges[edkSystem_Next]) {
      endNodeRef.accept(*this);
    }
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitEndSystem_Next(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;
  }

  // edge: prev
  genNodePtr = node.getPrev() ;
  if (genNodePtr) {
    const System& endNodeRef = dynamic_cast<const System&>(*genNodePtr);
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitSystem_Prev(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;

    if (apRoot) {
      if (visitCrossEdgeTree) {
        unvisitedNodes[endNodeRef.getId()] = true;
      }
    }
    if (traversaldCrossEdges[edkSystem_Prev]) {
      endNodeRef.accept(*this);
    }
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitEndSystem_Prev(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;
  }
}

void AlgorithmPreorder::visit(const System& node, bool callFirst /*= true*/){
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

void AlgorithmPreorder::visitAllEdges(const Clone& node, bool callFirst /*= true*/){
  visitAllEdges(dynamic_cast<const Trackable&>(node),false);
}

void AlgorithmPreorder::visit(const Clone& node, bool callFirst /*= true*/){
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

void AlgorithmPreorder::visitAllEdges(const StructuralClone& node, bool callFirst /*= true*/){
  visitAllEdges(dynamic_cast<const Trackable&>(node),false);
}

void AlgorithmPreorder::visit(const StructuralClone& node, bool callFirst /*= true*/){
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

void AlgorithmPreorder::visitAllEdges(const CloneClass& node, bool callFirst /*= true*/){
  visitAllEdges(dynamic_cast<const Clone&>(node),false);

  std::list<Visitor*>::iterator itVisitors;

  // edge: nextNeighbours
  for (ListIterator<CloneClass> it = node.getNextNeighboursListIteratorBegin(); it != node.getNextNeighboursListIteratorEnd(); ++it) {
    const CloneClass& endNodeRef = *it;
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitCloneClass_NextNeighbours(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;

    if (apRoot) {
      if (visitCrossEdgeTree) {
        unvisitedNodes[endNodeRef.getId()] = true;
      }
    }
    if (traversaldCrossEdges[edkCloneClass_NextNeighbours]) {
      endNodeRef.accept(*this);
    }
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitEndCloneClass_NextNeighbours(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;
  }

  // edge: prevNeighbours
  for (ListIterator<CloneClass> it = node.getPrevNeighboursListIteratorBegin(); it != node.getPrevNeighboursListIteratorEnd(); ++it) {
    const CloneClass& endNodeRef = *it;
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitCloneClass_PrevNeighbours(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;

    if (apRoot) {
      if (visitCrossEdgeTree) {
        unvisitedNodes[endNodeRef.getId()] = true;
      }
    }
    if (traversaldCrossEdges[edkCloneClass_PrevNeighbours]) {
      endNodeRef.accept(*this);
    }
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitEndCloneClass_PrevNeighbours(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;
  }

  // edge: items
  for (ListIterator<CloneInstance> it = node.getItemsListIteratorBegin(); it != node.getItemsListIteratorEnd(); ++it) {
    const CloneInstance& endNodeRef = *it;
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitCloneClass_Items(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;

    endNodeRef.accept(*this);
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitEndCloneClass_Items(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;
  }
}

void AlgorithmPreorder::visit(const CloneClass& node, bool callFirst /*= true*/){
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

void AlgorithmPreorder::visitAllEdges(const CloneInstance& node, bool callFirst /*= true*/){
  visitAllEdges(dynamic_cast<const Clone&>(node),false);

  std::list<Visitor*>::iterator itVisitors;

  // edge: intersects
  for (ListIterator<CloneInstance> it = node.getIntersectsListIteratorBegin(); it != node.getIntersectsListIteratorEnd(); ++it) {
    const CloneInstance& endNodeRef = *it;
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitCloneInstance_Intersects(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;

    if (apRoot) {
      if (visitCrossEdgeTree) {
        unvisitedNodes[endNodeRef.getId()] = true;
      }
    }
    if (traversaldCrossEdges[edkCloneInstance_Intersects]) {
      endNodeRef.accept(*this);
    }
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitEndCloneInstance_Intersects(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;
  }

  const Base* genNodePtr;
  // edge: component
  genNodePtr = node.getComponent() ;
  if (genNodePtr) {
    const Component& endNodeRef = dynamic_cast<const Component&>(*genNodePtr);
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitCloneInstance_Component(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;

    if (apRoot) {
      if (visitCrossEdgeTree) {
        unvisitedNodes[endNodeRef.getId()] = true;
      }
    }
    if (traversaldCrossEdges[edkCloneInstance_Component]) {
      endNodeRef.accept(*this);
    }
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitEndCloneInstance_Component(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;
  }

  // edge: cloneClass
  genNodePtr = node.getCloneClass() ;
  if (genNodePtr) {
    const CloneClass& endNodeRef = dynamic_cast<const CloneClass&>(*genNodePtr);
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitCloneInstance_CloneClass(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;

    if (apRoot) {
      if (visitCrossEdgeTree) {
        unvisitedNodes[endNodeRef.getId()] = true;
      }
    }
    if (traversaldCrossEdges[edkCloneInstance_CloneClass]) {
      endNodeRef.accept(*this);
    }
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitEndCloneInstance_CloneClass(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;
  }
}

void AlgorithmPreorder::visit(const CloneInstance& node, bool callFirst /*= true*/){
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

void AlgorithmPreorder::visitAllEdges(const DataClumpsClass& node, bool callFirst /*= true*/){
  visitAllEdges(dynamic_cast<const StructuralClone&>(node),false);

  std::list<Visitor*>::iterator itVisitors;

  // edge: items
  for (ListIterator<DataClumps> it = node.getItemsListIteratorBegin(); it != node.getItemsListIteratorEnd(); ++it) {
    const DataClumps& endNodeRef = *it;
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitDataClumpsClass_Items(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;

    if (apRoot) {
      if (visitCrossEdgeTree) {
        unvisitedNodes[endNodeRef.getId()] = true;
      }
    }
    if (traversaldCrossEdges[edkDataClumpsClass_Items]) {
      endNodeRef.accept(*this);
    }
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitEndDataClumpsClass_Items(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;
  }
}

void AlgorithmPreorder::visit(const DataClumpsClass& node, bool callFirst /*= true*/){
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

void AlgorithmPreorder::visitAllEdges(const DataClumps& node, bool callFirst /*= true*/){
  visitAllEdges(dynamic_cast<const StructuralClone&>(node),false);

  std::list<Visitor*>::iterator itVisitors;

  const Base* genNodePtr;
  // edge: dataClumpsClass
  genNodePtr = node.getDataClumpsClass() ;
  if (genNodePtr) {
    const DataClumpsClass& endNodeRef = dynamic_cast<const DataClumpsClass&>(*genNodePtr);
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitDataClumps_DataClumpsClass(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;

    if (apRoot) {
      if (visitCrossEdgeTree) {
        unvisitedNodes[endNodeRef.getId()] = true;
      }
    }
    if (traversaldCrossEdges[edkDataClumps_DataClumpsClass]) {
      endNodeRef.accept(*this);
    }
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitEndDataClumps_DataClumpsClass(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;
  }

  // edge: items
  for (ListIterator<DataElement> it = node.getItemsListIteratorBegin(); it != node.getItemsListIteratorEnd(); ++it) {
    const DataElement& endNodeRef = *it;
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitDataClumps_Items(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;

    endNodeRef.accept(*this);
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitEndDataClumps_Items(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;
  }
}

void AlgorithmPreorder::visit(const DataClumps& node, bool callFirst /*= true*/){
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

void AlgorithmPreorder::visitAllEdges(const DataElement& node, bool callFirst /*= true*/){
  visitAllEdges(dynamic_cast<const SourceCodeElement&>(node),false);

  std::list<Visitor*>::iterator itVisitors;

  const Base* genNodePtr;
  // edge: component
  genNodePtr = node.getComponent() ;
  if (genNodePtr) {
    const Component& endNodeRef = dynamic_cast<const Component&>(*genNodePtr);
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitDataElement_Component(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;

    if (apRoot) {
      if (visitCrossEdgeTree) {
        unvisitedNodes[endNodeRef.getId()] = true;
      }
    }
    if (traversaldCrossEdges[edkDataElement_Component]) {
      endNodeRef.accept(*this);
    }
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitEndDataElement_Component(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;
  }
}

void AlgorithmPreorder::visit(const DataElement& node, bool callFirst /*= true*/){
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

void AlgorithmPreorder::visitAllEdges(const SwitchStatementClass& node, bool callFirst /*= true*/){
  visitAllEdges(dynamic_cast<const StructuralClone&>(node),false);

  std::list<Visitor*>::iterator itVisitors;

  // edge: items
  for (ListIterator<SwitchStatement> it = node.getItemsListIteratorBegin(); it != node.getItemsListIteratorEnd(); ++it) {
    const SwitchStatement& endNodeRef = *it;
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitSwitchStatementClass_Items(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;

    if (apRoot) {
      if (visitCrossEdgeTree) {
        unvisitedNodes[endNodeRef.getId()] = true;
      }
    }
    if (traversaldCrossEdges[edkSwitchStatementClass_Items]) {
      endNodeRef.accept(*this);
    }
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitEndSwitchStatementClass_Items(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;
  }
}

void AlgorithmPreorder::visit(const SwitchStatementClass& node, bool callFirst /*= true*/){
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

void AlgorithmPreorder::visitAllEdges(const SwitchStatement& node, bool callFirst /*= true*/){
  visitAllEdges(dynamic_cast<const StructuralClone&>(node),false);

  std::list<Visitor*>::iterator itVisitors;

  const Base* genNodePtr;
  // edge: switchStatementClass
  genNodePtr = node.getSwitchStatementClass() ;
  if (genNodePtr) {
    const SwitchStatementClass& endNodeRef = dynamic_cast<const SwitchStatementClass&>(*genNodePtr);
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitSwitchStatement_SwitchStatementClass(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;

    if (apRoot) {
      if (visitCrossEdgeTree) {
        unvisitedNodes[endNodeRef.getId()] = true;
      }
    }
    if (traversaldCrossEdges[edkSwitchStatement_SwitchStatementClass]) {
      endNodeRef.accept(*this);
    }
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitEndSwitchStatement_SwitchStatementClass(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;
  }

  // edge: items
  for (ListIterator<CaseLabel> it = node.getItemsListIteratorBegin(); it != node.getItemsListIteratorEnd(); ++it) {
    const CaseLabel& endNodeRef = *it;
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitSwitchStatement_Items(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;

    endNodeRef.accept(*this);
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitEndSwitchStatement_Items(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;
  }
}

void AlgorithmPreorder::visit(const SwitchStatement& node, bool callFirst /*= true*/){
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

void AlgorithmPreorder::visitAllEdges(const CaseLabel& node, bool callFirst /*= true*/){
  visitAllEdges(dynamic_cast<const SourceCodeElement&>(node),false);

  std::list<Visitor*>::iterator itVisitors;

  const Base* genNodePtr;
  // edge: component
  genNodePtr = node.getComponent() ;
  if (genNodePtr) {
    const Component& endNodeRef = dynamic_cast<const Component&>(*genNodePtr);
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitCaseLabel_Component(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;

    if (apRoot) {
      if (visitCrossEdgeTree) {
        unvisitedNodes[endNodeRef.getId()] = true;
      }
    }
    if (traversaldCrossEdges[edkCaseLabel_Component]) {
      endNodeRef.accept(*this);
    }
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitEndCaseLabel_Component(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;
  }
}

void AlgorithmPreorder::visit(const CaseLabel& node, bool callFirst /*= true*/){
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
    throw GenealogyException(COLUMBUS_LOCATION, CMSG_EX_YOU_MUST_GIVE_A_FACTORY_AT_FIRST);
  }

  if (visitorList.empty()){
    throw GenealogyException(COLUMBUS_LOCATION, CMSG_EX_DON_T_HAVE_ANY_VISITOR);
  }

  if (safeMode || visitCrossEdgeTree) {
    visitedNodes.clear();
    visitedNodes.resize(fact->size(), false);
  }

  if (visitCrossEdgeTree) {
    unvisitedNodes.clear();
    unvisitedNodes.resize(fact->size(), false);
  }

  for (std::list<Visitor*>::iterator itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
    (*itVisitors)->beginVisit();
  }

}

void AlgorithmPreorder::endPreorder(){

  for (std::list<Visitor*>::iterator itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
    (*itVisitors)->finishVisit();
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
}}
