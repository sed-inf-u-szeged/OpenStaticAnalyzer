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
#include "common/inc/WriteMessage.h"
#include "javascript/inc/messages.h"
#include <string.h>

#ifdef DEBUG_PREORDER
#include <iostream>
#endif


namespace columbus { namespace javascript { namespace asg {
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
  memset(traversaldCrossEdges,false,sizeof(bool)*93);
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

void AlgorithmPreorder::visitAllEdges(const base::Comment& node, bool callFirst /*= true*/){
  visitAllEdges(dynamic_cast<const base::Positioned&>(node),false);
}

void AlgorithmPreorder::visit(const base::Comment& node, bool callFirst /*= true*/){
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

void AlgorithmPreorder::visitAllEdges(const base::Named& node, bool callFirst /*= true*/){
  if (callFirst)
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
        if (visitCrossEdgeTree) {
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

void AlgorithmPreorder::visitAllEdges(const base::Program& node, bool callFirst /*= true*/){
  if (callFirst)
    visitAllEdges(dynamic_cast<const base::Positioned&>(node),false);
  visitAllEdges(dynamic_cast<const base::Named&>(node),false);

  std::list<Visitor*>::iterator itVisitors;

  // edge: hasBody
  for (ListIterator<base::Positioned> it = node.getBodyListIteratorBegin(); it != node.getBodyListIteratorEnd(); ++it) {
    const base::Positioned& endNodeRef = *it;
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitProgram_HasBody(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;

    if ((!fact->getIsFilterTurnedOn() && !visitFilteredEdge) || (fact->getFilterState(endNodeRef.getId()) == Filter::NotFiltered) || (!originalFilterState && visitFilteredEdge)) {
      endNodeRef.accept(*this);
    }
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitEndProgram_HasBody(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;
  }
}

void AlgorithmPreorder::visit(const base::Program& node, bool callFirst /*= true*/){
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

void AlgorithmPreorder::visitAllEdges(const base::System& node, bool callFirst /*= true*/){
  visitAllEdges(dynamic_cast<const base::Base&>(node),false);

  std::list<Visitor*>::iterator itVisitors;

  // edge: hasPrograms
  for (ListIterator<base::Program> it = node.getProgramsListIteratorBegin(); it != node.getProgramsListIteratorEnd(); ++it) {
    const base::Program& endNodeRef = *it;
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitSystem_HasPrograms(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;

    if ((!fact->getIsFilterTurnedOn() && !visitFilteredEdge) || (fact->getFilterState(endNodeRef.getId()) == Filter::NotFiltered) || (!originalFilterState && visitFilteredEdge)) {
      endNodeRef.accept(*this);
    }
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitEndSystem_HasPrograms(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;
  }
}

void AlgorithmPreorder::visit(const base::System& node, bool callFirst /*= true*/){
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

void AlgorithmPreorder::visitAllEdges(const declaration::ClassDeclaration& node, bool callFirst /*= true*/){
  if (callFirst)
    visitAllEdges(dynamic_cast<const base::Positioned&>(node),false);
  visitAllEdges(dynamic_cast<const declaration::Declaration&>(node),false);
  visitAllEdges(dynamic_cast<const structure::Class&>(node),false);
}

void AlgorithmPreorder::visit(const declaration::ClassDeclaration& node, bool callFirst /*= true*/){
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

void AlgorithmPreorder::visitAllEdges(const declaration::Declaration& node, bool callFirst /*= true*/){
  if (callFirst)
    visitAllEdges(dynamic_cast<const base::Positioned&>(node),false);
  visitAllEdges(dynamic_cast<const statement::Statement&>(node),false);
}

void AlgorithmPreorder::visitAllEdges(const declaration::ExportAllDeclaration& node, bool callFirst /*= true*/){
  if (callFirst)
    visitAllEdges(dynamic_cast<const base::Positioned&>(node),false);
  visitAllEdges(dynamic_cast<const declaration::Declaration&>(node),false);

  std::list<Visitor*>::iterator itVisitors;

  const base::Base* genNodePtr;
  // edge: hasSource
  genNodePtr = node.getSource() ;
  if (genNodePtr) {
    const expression::Literal& endNodeRef = dynamic_cast<const expression::Literal&>(*genNodePtr);
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitExportAllDeclaration_HasSource(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;

    if ((!fact->getIsFilterTurnedOn() && !visitFilteredEdge) || (fact->getFilterState(endNodeRef.getId()) == Filter::NotFiltered) || (!originalFilterState && visitFilteredEdge)) {
      endNodeRef.accept(*this);
    }
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitEndExportAllDeclaration_HasSource(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;
  }
}

void AlgorithmPreorder::visit(const declaration::ExportAllDeclaration& node, bool callFirst /*= true*/){
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

void AlgorithmPreorder::visitAllEdges(const declaration::ExportDefaultDeclaration& node, bool callFirst /*= true*/){
  if (callFirst)
    visitAllEdges(dynamic_cast<const base::Positioned&>(node),false);
  visitAllEdges(dynamic_cast<const declaration::Declaration&>(node),false);

  std::list<Visitor*>::iterator itVisitors;

  const base::Base* genNodePtr;
  // edge: hasDeclaration
  genNodePtr = node.getDeclaration() ;
  if (genNodePtr) {
    const base::Positioned& endNodeRef = dynamic_cast<const base::Positioned&>(*genNodePtr);
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitExportDefaultDeclaration_HasDeclaration(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;

    if ((!fact->getIsFilterTurnedOn() && !visitFilteredEdge) || (fact->getFilterState(endNodeRef.getId()) == Filter::NotFiltered) || (!originalFilterState && visitFilteredEdge)) {
      endNodeRef.accept(*this);
    }
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitEndExportDefaultDeclaration_HasDeclaration(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;
  }
}

void AlgorithmPreorder::visit(const declaration::ExportDefaultDeclaration& node, bool callFirst /*= true*/){
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

void AlgorithmPreorder::visitAllEdges(const declaration::ExportNamedDeclaration& node, bool callFirst /*= true*/){
  visitAllEdges(dynamic_cast<const declaration::ModuleDeclaration&>(node),false);

  std::list<Visitor*>::iterator itVisitors;

  const base::Base* genNodePtr;
  // edge: hasDeclaration
  genNodePtr = node.getDeclaration() ;
  if (genNodePtr) {
    const declaration::Declaration& endNodeRef = dynamic_cast<const declaration::Declaration&>(*genNodePtr);
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitExportNamedDeclaration_HasDeclaration(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;

    if ((!fact->getIsFilterTurnedOn() && !visitFilteredEdge) || (fact->getFilterState(endNodeRef.getId()) == Filter::NotFiltered) || (!originalFilterState && visitFilteredEdge)) {
      endNodeRef.accept(*this);
    }
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitEndExportNamedDeclaration_HasDeclaration(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;
  }

  // edge: hasSpecifiers
  for (ListIterator<structure::ExportSpecifier> it = node.getSpecifiersListIteratorBegin(); it != node.getSpecifiersListIteratorEnd(); ++it) {
    const structure::ExportSpecifier& endNodeRef = *it;
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitExportNamedDeclaration_HasSpecifiers(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;

    if ((!fact->getIsFilterTurnedOn() && !visitFilteredEdge) || (fact->getFilterState(endNodeRef.getId()) == Filter::NotFiltered) || (!originalFilterState && visitFilteredEdge)) {
      endNodeRef.accept(*this);
    }
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitEndExportNamedDeclaration_HasSpecifiers(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;
  }

  // edge: hasSource
  genNodePtr = node.getSource() ;
  if (genNodePtr) {
    const expression::Literal& endNodeRef = dynamic_cast<const expression::Literal&>(*genNodePtr);
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitExportNamedDeclaration_HasSource(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;

    if ((!fact->getIsFilterTurnedOn() && !visitFilteredEdge) || (fact->getFilterState(endNodeRef.getId()) == Filter::NotFiltered) || (!originalFilterState && visitFilteredEdge)) {
      endNodeRef.accept(*this);
    }
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitEndExportNamedDeclaration_HasSource(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;
  }
}

void AlgorithmPreorder::visit(const declaration::ExportNamedDeclaration& node, bool callFirst /*= true*/){
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

void AlgorithmPreorder::visitAllEdges(const declaration::FunctionDeclaration& node, bool callFirst /*= true*/){
  if (callFirst)
    visitAllEdges(dynamic_cast<const base::Positioned&>(node),false);
  visitAllEdges(dynamic_cast<const statement::Function&>(node),false);
  visitAllEdges(dynamic_cast<const declaration::Declaration&>(node),false);
}

void AlgorithmPreorder::visit(const declaration::FunctionDeclaration& node, bool callFirst /*= true*/){
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

void AlgorithmPreorder::visitAllEdges(const declaration::ImportDeclaration& node, bool callFirst /*= true*/){
  visitAllEdges(dynamic_cast<const declaration::ModuleDeclaration&>(node),false);

  std::list<Visitor*>::iterator itVisitors;

  // edge: hasSpecifiers
  for (ListIterator<structure::ImpSpecifier> it = node.getSpecifiersListIteratorBegin(); it != node.getSpecifiersListIteratorEnd(); ++it) {
    const structure::ImpSpecifier& endNodeRef = *it;
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitImportDeclaration_HasSpecifiers(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;

    if ((!fact->getIsFilterTurnedOn() && !visitFilteredEdge) || (fact->getFilterState(endNodeRef.getId()) == Filter::NotFiltered) || (!originalFilterState && visitFilteredEdge)) {
      endNodeRef.accept(*this);
    }
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitEndImportDeclaration_HasSpecifiers(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;
  }

  const base::Base* genNodePtr;
  // edge: hasSource
  genNodePtr = node.getSource() ;
  if (genNodePtr) {
    const expression::Literal& endNodeRef = dynamic_cast<const expression::Literal&>(*genNodePtr);
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitImportDeclaration_HasSource(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;

    if ((!fact->getIsFilterTurnedOn() && !visitFilteredEdge) || (fact->getFilterState(endNodeRef.getId()) == Filter::NotFiltered) || (!originalFilterState && visitFilteredEdge)) {
      endNodeRef.accept(*this);
    }
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitEndImportDeclaration_HasSource(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;
  }
}

void AlgorithmPreorder::visit(const declaration::ImportDeclaration& node, bool callFirst /*= true*/){
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

void AlgorithmPreorder::visitAllEdges(const declaration::ModuleDeclaration& node, bool callFirst /*= true*/){
  visitAllEdges(dynamic_cast<const base::Positioned&>(node),false);
}

void AlgorithmPreorder::visit(const declaration::ModuleDeclaration& node, bool callFirst /*= true*/){
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

void AlgorithmPreorder::visitAllEdges(const declaration::VariableDeclaration& node, bool callFirst /*= true*/){
  if (callFirst)
    visitAllEdges(dynamic_cast<const base::Positioned&>(node),false);
  visitAllEdges(dynamic_cast<const declaration::Declaration&>(node),false);

  std::list<Visitor*>::iterator itVisitors;

  // edge: hasDeclarations
  for (ListIterator<declaration::VariableDeclarator> it = node.getDeclarationsListIteratorBegin(); it != node.getDeclarationsListIteratorEnd(); ++it) {
    const declaration::VariableDeclarator& endNodeRef = *it;
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitVariableDeclaration_HasDeclarations(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;

    if ((!fact->getIsFilterTurnedOn() && !visitFilteredEdge) || (fact->getFilterState(endNodeRef.getId()) == Filter::NotFiltered) || (!originalFilterState && visitFilteredEdge)) {
      endNodeRef.accept(*this);
    }
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitEndVariableDeclaration_HasDeclarations(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;
  }
}

void AlgorithmPreorder::visit(const declaration::VariableDeclaration& node, bool callFirst /*= true*/){
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

void AlgorithmPreorder::visitAllEdges(const declaration::VariableDeclarator& node, bool callFirst /*= true*/){
  visitAllEdges(dynamic_cast<const base::Positioned&>(node),false);

  std::list<Visitor*>::iterator itVisitors;

  const base::Base* genNodePtr;
  // edge: hasIdentifier
  genNodePtr = node.getIdentifier() ;
  if (genNodePtr) {
    const statement::Pattern& endNodeRef = dynamic_cast<const statement::Pattern&>(*genNodePtr);
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitVariableDeclarator_HasIdentifier(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;

    if ((!fact->getIsFilterTurnedOn() && !visitFilteredEdge) || (fact->getFilterState(endNodeRef.getId()) == Filter::NotFiltered) || (!originalFilterState && visitFilteredEdge)) {
      endNodeRef.accept(*this);
    }
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitEndVariableDeclarator_HasIdentifier(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;
  }

  // edge: hasInit
  genNodePtr = node.getInit() ;
  if (genNodePtr) {
    const expression::Expression& endNodeRef = dynamic_cast<const expression::Expression&>(*genNodePtr);
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitVariableDeclarator_HasInit(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;

    if ((!fact->getIsFilterTurnedOn() && !visitFilteredEdge) || (fact->getFilterState(endNodeRef.getId()) == Filter::NotFiltered) || (!originalFilterState && visitFilteredEdge)) {
      endNodeRef.accept(*this);
    }
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitEndVariableDeclarator_HasInit(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;
  }
}

void AlgorithmPreorder::visit(const declaration::VariableDeclarator& node, bool callFirst /*= true*/){
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

void AlgorithmPreorder::visitAllEdges(const expression::ArrayExpression& node, bool callFirst /*= true*/){
  if (callFirst)
    visitAllEdges(dynamic_cast<const base::Positioned&>(node),false);
  visitAllEdges(dynamic_cast<const expression::Expression&>(node),false);

  std::list<Visitor*>::iterator itVisitors;

  // edge: hasElements
  for (ListIterator<base::Positioned> it = node.getElementsListIteratorBegin(); it != node.getElementsListIteratorEnd(); ++it) {
    const base::Positioned& endNodeRef = *it;
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitArrayExpression_HasElements(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;

    if ((!fact->getIsFilterTurnedOn() && !visitFilteredEdge) || (fact->getFilterState(endNodeRef.getId()) == Filter::NotFiltered) || (!originalFilterState && visitFilteredEdge)) {
      endNodeRef.accept(*this);
    }
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitEndArrayExpression_HasElements(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;
  }
}

void AlgorithmPreorder::visit(const expression::ArrayExpression& node, bool callFirst /*= true*/){
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

void AlgorithmPreorder::visitAllEdges(const expression::ArrowFunctionExpression& node, bool callFirst /*= true*/){
  if (callFirst)
    visitAllEdges(dynamic_cast<const base::Positioned&>(node),false);
  visitAllEdges(dynamic_cast<const expression::Expression&>(node),false);
  visitAllEdges(dynamic_cast<const statement::Function&>(node),false);
}

void AlgorithmPreorder::visit(const expression::ArrowFunctionExpression& node, bool callFirst /*= true*/){
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

void AlgorithmPreorder::visitAllEdges(const expression::AssignmentExpression& node, bool callFirst /*= true*/){
  if (callFirst)
    visitAllEdges(dynamic_cast<const base::Positioned&>(node),false);
  visitAllEdges(dynamic_cast<const expression::Expression&>(node),false);

  std::list<Visitor*>::iterator itVisitors;

  const base::Base* genNodePtr;
  // edge: hasLeft
  genNodePtr = node.getLeft() ;
  if (genNodePtr) {
    const base::Positioned& endNodeRef = dynamic_cast<const base::Positioned&>(*genNodePtr);
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitAssignmentExpression_HasLeft(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;

    if ((!fact->getIsFilterTurnedOn() && !visitFilteredEdge) || (fact->getFilterState(endNodeRef.getId()) == Filter::NotFiltered) || (!originalFilterState && visitFilteredEdge)) {
      endNodeRef.accept(*this);
    }
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitEndAssignmentExpression_HasLeft(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;
  }

  // edge: hasRight
  genNodePtr = node.getRight() ;
  if (genNodePtr) {
    const expression::Expression& endNodeRef = dynamic_cast<const expression::Expression&>(*genNodePtr);
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitAssignmentExpression_HasRight(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;

    if ((!fact->getIsFilterTurnedOn() && !visitFilteredEdge) || (fact->getFilterState(endNodeRef.getId()) == Filter::NotFiltered) || (!originalFilterState && visitFilteredEdge)) {
      endNodeRef.accept(*this);
    }
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitEndAssignmentExpression_HasRight(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;
  }
}

void AlgorithmPreorder::visit(const expression::AssignmentExpression& node, bool callFirst /*= true*/){
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

void AlgorithmPreorder::visitAllEdges(const expression::AssignmentProperty& node, bool callFirst /*= true*/){
  visitAllEdges(dynamic_cast<const expression::Property&>(node),false);
}

void AlgorithmPreorder::visit(const expression::AssignmentProperty& node, bool callFirst /*= true*/){
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

void AlgorithmPreorder::visitAllEdges(const expression::AwaitExpression& node, bool callFirst /*= true*/){
  if (callFirst)
    visitAllEdges(dynamic_cast<const base::Positioned&>(node),false);
  visitAllEdges(dynamic_cast<const expression::Expression&>(node),false);

  std::list<Visitor*>::iterator itVisitors;

  const base::Base* genNodePtr;
  // edge: hasArgument
  genNodePtr = node.getArgument() ;
  if (genNodePtr) {
    const expression::Expression& endNodeRef = dynamic_cast<const expression::Expression&>(*genNodePtr);
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitAwaitExpression_HasArgument(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;

    if ((!fact->getIsFilterTurnedOn() && !visitFilteredEdge) || (fact->getFilterState(endNodeRef.getId()) == Filter::NotFiltered) || (!originalFilterState && visitFilteredEdge)) {
      endNodeRef.accept(*this);
    }
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitEndAwaitExpression_HasArgument(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;
  }
}

void AlgorithmPreorder::visit(const expression::AwaitExpression& node, bool callFirst /*= true*/){
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

void AlgorithmPreorder::visitAllEdges(const expression::BinaryExpression& node, bool callFirst /*= true*/){
  if (callFirst)
    visitAllEdges(dynamic_cast<const base::Positioned&>(node),false);
  visitAllEdges(dynamic_cast<const expression::Expression&>(node),false);

  std::list<Visitor*>::iterator itVisitors;

  const base::Base* genNodePtr;
  // edge: hasLeft
  genNodePtr = node.getLeft() ;
  if (genNodePtr) {
    const expression::Expression& endNodeRef = dynamic_cast<const expression::Expression&>(*genNodePtr);
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitBinaryExpression_HasLeft(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;

    if ((!fact->getIsFilterTurnedOn() && !visitFilteredEdge) || (fact->getFilterState(endNodeRef.getId()) == Filter::NotFiltered) || (!originalFilterState && visitFilteredEdge)) {
      endNodeRef.accept(*this);
    }
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitEndBinaryExpression_HasLeft(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;
  }

  // edge: hasRight
  genNodePtr = node.getRight() ;
  if (genNodePtr) {
    const expression::Expression& endNodeRef = dynamic_cast<const expression::Expression&>(*genNodePtr);
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitBinaryExpression_HasRight(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;

    if ((!fact->getIsFilterTurnedOn() && !visitFilteredEdge) || (fact->getFilterState(endNodeRef.getId()) == Filter::NotFiltered) || (!originalFilterState && visitFilteredEdge)) {
      endNodeRef.accept(*this);
    }
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitEndBinaryExpression_HasRight(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;
  }
}

void AlgorithmPreorder::visit(const expression::BinaryExpression& node, bool callFirst /*= true*/){
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

void AlgorithmPreorder::visitAllEdges(const expression::BooleanLiteral& node, bool callFirst /*= true*/){
  if (callFirst)
    visitAllEdges(dynamic_cast<const base::Positioned&>(node),false);
  visitAllEdges(dynamic_cast<const expression::Literal&>(node),false);
}

void AlgorithmPreorder::visit(const expression::BooleanLiteral& node, bool callFirst /*= true*/){
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

void AlgorithmPreorder::visitAllEdges(const expression::CallExpression& node, bool callFirst /*= true*/){
  if (callFirst)
    visitAllEdges(dynamic_cast<const base::Positioned&>(node),false);
  visitAllEdges(dynamic_cast<const expression::Expression&>(node),false);

  std::list<Visitor*>::iterator itVisitors;

  const base::Base* genNodePtr;
  // edge: hasCallee
  genNodePtr = node.getCallee() ;
  if (genNodePtr) {
    const base::Positioned& endNodeRef = dynamic_cast<const base::Positioned&>(*genNodePtr);
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitCallExpression_HasCallee(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;

    if ((!fact->getIsFilterTurnedOn() && !visitFilteredEdge) || (fact->getFilterState(endNodeRef.getId()) == Filter::NotFiltered) || (!originalFilterState && visitFilteredEdge)) {
      endNodeRef.accept(*this);
    }
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitEndCallExpression_HasCallee(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;
  }

  // edge: hasArguments
  for (ListIterator<base::Positioned> it = node.getArgumentsListIteratorBegin(); it != node.getArgumentsListIteratorEnd(); ++it) {
    const base::Positioned& endNodeRef = *it;
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitCallExpression_HasArguments(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;

    if ((!fact->getIsFilterTurnedOn() && !visitFilteredEdge) || (fact->getFilterState(endNodeRef.getId()) == Filter::NotFiltered) || (!originalFilterState && visitFilteredEdge)) {
      endNodeRef.accept(*this);
    }
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitEndCallExpression_HasArguments(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;
  }
}

void AlgorithmPreorder::visit(const expression::CallExpression& node, bool callFirst /*= true*/){
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

void AlgorithmPreorder::visitAllEdges(const expression::ClassExpression& node, bool callFirst /*= true*/){
  if (callFirst)
    visitAllEdges(dynamic_cast<const base::Positioned&>(node),false);
  visitAllEdges(dynamic_cast<const expression::Expression&>(node),false);
  visitAllEdges(dynamic_cast<const structure::Class&>(node),false);
}

void AlgorithmPreorder::visit(const expression::ClassExpression& node, bool callFirst /*= true*/){
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

void AlgorithmPreorder::visitAllEdges(const expression::ConditionalExpression& node, bool callFirst /*= true*/){
  if (callFirst)
    visitAllEdges(dynamic_cast<const base::Positioned&>(node),false);
  visitAllEdges(dynamic_cast<const expression::Expression&>(node),false);

  std::list<Visitor*>::iterator itVisitors;

  const base::Base* genNodePtr;
  // edge: hasAlternate
  genNodePtr = node.getAlternate() ;
  if (genNodePtr) {
    const expression::Expression& endNodeRef = dynamic_cast<const expression::Expression&>(*genNodePtr);
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitConditionalExpression_HasAlternate(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;

    if ((!fact->getIsFilterTurnedOn() && !visitFilteredEdge) || (fact->getFilterState(endNodeRef.getId()) == Filter::NotFiltered) || (!originalFilterState && visitFilteredEdge)) {
      endNodeRef.accept(*this);
    }
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitEndConditionalExpression_HasAlternate(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;
  }

  // edge: hasConsequent
  genNodePtr = node.getConsequent() ;
  if (genNodePtr) {
    const expression::Expression& endNodeRef = dynamic_cast<const expression::Expression&>(*genNodePtr);
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitConditionalExpression_HasConsequent(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;

    if ((!fact->getIsFilterTurnedOn() && !visitFilteredEdge) || (fact->getFilterState(endNodeRef.getId()) == Filter::NotFiltered) || (!originalFilterState && visitFilteredEdge)) {
      endNodeRef.accept(*this);
    }
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitEndConditionalExpression_HasConsequent(node, endNodeRef);
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
      (*itVisitors)->visitConditionalExpression_HasTest(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;

    if ((!fact->getIsFilterTurnedOn() && !visitFilteredEdge) || (fact->getFilterState(endNodeRef.getId()) == Filter::NotFiltered) || (!originalFilterState && visitFilteredEdge)) {
      endNodeRef.accept(*this);
    }
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitEndConditionalExpression_HasTest(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;
  }
}

void AlgorithmPreorder::visit(const expression::ConditionalExpression& node, bool callFirst /*= true*/){
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

void AlgorithmPreorder::visitAllEdges(const expression::Expression& node, bool callFirst /*= true*/){
  if (callFirst)
    visitAllEdges(dynamic_cast<const base::Positioned&>(node),false);
}

void AlgorithmPreorder::visitAllEdges(const expression::FunctionExpression& node, bool callFirst /*= true*/){
  if (callFirst)
    visitAllEdges(dynamic_cast<const base::Positioned&>(node),false);
  visitAllEdges(dynamic_cast<const expression::Expression&>(node),false);
  visitAllEdges(dynamic_cast<const statement::Function&>(node),false);
}

void AlgorithmPreorder::visit(const expression::FunctionExpression& node, bool callFirst /*= true*/){
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

void AlgorithmPreorder::visitAllEdges(const expression::Identifier& node, bool callFirst /*= true*/){
  if (callFirst)
    visitAllEdges(dynamic_cast<const base::Positioned&>(node),false);
  visitAllEdges(dynamic_cast<const expression::Expression&>(node),false);
  visitAllEdges(dynamic_cast<const statement::Pattern&>(node),false);
  visitAllEdges(dynamic_cast<const base::Named&>(node),false);

  std::list<Visitor*>::iterator itVisitors;

  const base::Base* genNodePtr;
  // edge: refersTo
  genNodePtr = node.getRefersTo() ;
  if (genNodePtr) {
    const base::Positioned& endNodeRef = dynamic_cast<const base::Positioned&>(*genNodePtr);
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitIdentifier_RefersTo(node, endNodeRef);
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

void AlgorithmPreorder::visitAllEdges(const expression::Literal& node, bool callFirst /*= true*/){
  if (callFirst)
    visitAllEdges(dynamic_cast<const base::Positioned&>(node),false);
  visitAllEdges(dynamic_cast<const expression::Expression&>(node),false);
}

void AlgorithmPreorder::visitAllEdges(const expression::LogicalExpression& node, bool callFirst /*= true*/){
  if (callFirst)
    visitAllEdges(dynamic_cast<const base::Positioned&>(node),false);
  visitAllEdges(dynamic_cast<const expression::Expression&>(node),false);

  std::list<Visitor*>::iterator itVisitors;

  const base::Base* genNodePtr;
  // edge: hasLeft
  genNodePtr = node.getLeft() ;
  if (genNodePtr) {
    const expression::Expression& endNodeRef = dynamic_cast<const expression::Expression&>(*genNodePtr);
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitLogicalExpression_HasLeft(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;

    if ((!fact->getIsFilterTurnedOn() && !visitFilteredEdge) || (fact->getFilterState(endNodeRef.getId()) == Filter::NotFiltered) || (!originalFilterState && visitFilteredEdge)) {
      endNodeRef.accept(*this);
    }
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitEndLogicalExpression_HasLeft(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;
  }

  // edge: hasRight
  genNodePtr = node.getRight() ;
  if (genNodePtr) {
    const expression::Expression& endNodeRef = dynamic_cast<const expression::Expression&>(*genNodePtr);
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitLogicalExpression_HasRight(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;

    if ((!fact->getIsFilterTurnedOn() && !visitFilteredEdge) || (fact->getFilterState(endNodeRef.getId()) == Filter::NotFiltered) || (!originalFilterState && visitFilteredEdge)) {
      endNodeRef.accept(*this);
    }
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitEndLogicalExpression_HasRight(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;
  }
}

void AlgorithmPreorder::visit(const expression::LogicalExpression& node, bool callFirst /*= true*/){
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

void AlgorithmPreorder::visitAllEdges(const expression::MemberExpression& node, bool callFirst /*= true*/){
  if (callFirst)
    visitAllEdges(dynamic_cast<const base::Positioned&>(node),false);
  visitAllEdges(dynamic_cast<const expression::Expression&>(node),false);
  visitAllEdges(dynamic_cast<const statement::Pattern&>(node),false);

  std::list<Visitor*>::iterator itVisitors;

  const base::Base* genNodePtr;
  // edge: hasProperty
  genNodePtr = node.getProperty() ;
  if (genNodePtr) {
    const expression::Expression& endNodeRef = dynamic_cast<const expression::Expression&>(*genNodePtr);
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitMemberExpression_HasProperty(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;

    if ((!fact->getIsFilterTurnedOn() && !visitFilteredEdge) || (fact->getFilterState(endNodeRef.getId()) == Filter::NotFiltered) || (!originalFilterState && visitFilteredEdge)) {
      endNodeRef.accept(*this);
    }
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitEndMemberExpression_HasProperty(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;
  }

  // edge: hasObject
  genNodePtr = node.getObject() ;
  if (genNodePtr) {
    const base::Positioned& endNodeRef = dynamic_cast<const base::Positioned&>(*genNodePtr);
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitMemberExpression_HasObject(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;

    if ((!fact->getIsFilterTurnedOn() && !visitFilteredEdge) || (fact->getFilterState(endNodeRef.getId()) == Filter::NotFiltered) || (!originalFilterState && visitFilteredEdge)) {
      endNodeRef.accept(*this);
    }
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitEndMemberExpression_HasObject(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;
  }
}

void AlgorithmPreorder::visit(const expression::MemberExpression& node, bool callFirst /*= true*/){
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

void AlgorithmPreorder::visitAllEdges(const expression::MetaProperty& node, bool callFirst /*= true*/){
  if (callFirst)
    visitAllEdges(dynamic_cast<const base::Positioned&>(node),false);
  visitAllEdges(dynamic_cast<const expression::Expression&>(node),false);

  std::list<Visitor*>::iterator itVisitors;

  const base::Base* genNodePtr;
  // edge: hasMeta
  genNodePtr = node.getMeta() ;
  if (genNodePtr) {
    const expression::Identifier& endNodeRef = dynamic_cast<const expression::Identifier&>(*genNodePtr);
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitMetaProperty_HasMeta(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;

    if ((!fact->getIsFilterTurnedOn() && !visitFilteredEdge) || (fact->getFilterState(endNodeRef.getId()) == Filter::NotFiltered) || (!originalFilterState && visitFilteredEdge)) {
      endNodeRef.accept(*this);
    }
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitEndMetaProperty_HasMeta(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;
  }

  // edge: hasProperty
  genNodePtr = node.getProperty() ;
  if (genNodePtr) {
    const expression::Identifier& endNodeRef = dynamic_cast<const expression::Identifier&>(*genNodePtr);
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitMetaProperty_HasProperty(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;

    if ((!fact->getIsFilterTurnedOn() && !visitFilteredEdge) || (fact->getFilterState(endNodeRef.getId()) == Filter::NotFiltered) || (!originalFilterState && visitFilteredEdge)) {
      endNodeRef.accept(*this);
    }
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitEndMetaProperty_HasProperty(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;
  }
}

void AlgorithmPreorder::visit(const expression::MetaProperty& node, bool callFirst /*= true*/){
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

void AlgorithmPreorder::visitAllEdges(const expression::NewExpression& node, bool callFirst /*= true*/){
  if (callFirst)
    visitAllEdges(dynamic_cast<const base::Positioned&>(node),false);
  visitAllEdges(dynamic_cast<const expression::Expression&>(node),false);

  std::list<Visitor*>::iterator itVisitors;

  const base::Base* genNodePtr;
  // edge: hasCallee
  genNodePtr = node.getCallee() ;
  if (genNodePtr) {
    const expression::Expression& endNodeRef = dynamic_cast<const expression::Expression&>(*genNodePtr);
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitNewExpression_HasCallee(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;

    if ((!fact->getIsFilterTurnedOn() && !visitFilteredEdge) || (fact->getFilterState(endNodeRef.getId()) == Filter::NotFiltered) || (!originalFilterState && visitFilteredEdge)) {
      endNodeRef.accept(*this);
    }
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitEndNewExpression_HasCallee(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;
  }

  // edge: hasArguments
  for (ListIterator<base::Positioned> it = node.getArgumentsListIteratorBegin(); it != node.getArgumentsListIteratorEnd(); ++it) {
    const base::Positioned& endNodeRef = *it;
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitNewExpression_HasArguments(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;

    if ((!fact->getIsFilterTurnedOn() && !visitFilteredEdge) || (fact->getFilterState(endNodeRef.getId()) == Filter::NotFiltered) || (!originalFilterState && visitFilteredEdge)) {
      endNodeRef.accept(*this);
    }
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitEndNewExpression_HasArguments(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;
  }
}

void AlgorithmPreorder::visit(const expression::NewExpression& node, bool callFirst /*= true*/){
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

void AlgorithmPreorder::visitAllEdges(const expression::NullLiteral& node, bool callFirst /*= true*/){
  if (callFirst)
    visitAllEdges(dynamic_cast<const base::Positioned&>(node),false);
  visitAllEdges(dynamic_cast<const expression::Literal&>(node),false);
}

void AlgorithmPreorder::visit(const expression::NullLiteral& node, bool callFirst /*= true*/){
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

void AlgorithmPreorder::visitAllEdges(const expression::NumberLiteral& node, bool callFirst /*= true*/){
  if (callFirst)
    visitAllEdges(dynamic_cast<const base::Positioned&>(node),false);
  visitAllEdges(dynamic_cast<const expression::Literal&>(node),false);
}

void AlgorithmPreorder::visit(const expression::NumberLiteral& node, bool callFirst /*= true*/){
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

void AlgorithmPreorder::visitAllEdges(const expression::ObjectExpression& node, bool callFirst /*= true*/){
  if (callFirst)
    visitAllEdges(dynamic_cast<const base::Positioned&>(node),false);
  visitAllEdges(dynamic_cast<const expression::Expression&>(node),false);

  std::list<Visitor*>::iterator itVisitors;

  // edge: hasProperties
  for (ListIterator<expression::Property> it = node.getPropertiesListIteratorBegin(); it != node.getPropertiesListIteratorEnd(); ++it) {
    const expression::Property& endNodeRef = *it;
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitObjectExpression_HasProperties(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;

    if ((!fact->getIsFilterTurnedOn() && !visitFilteredEdge) || (fact->getFilterState(endNodeRef.getId()) == Filter::NotFiltered) || (!originalFilterState && visitFilteredEdge)) {
      endNodeRef.accept(*this);
    }
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitEndObjectExpression_HasProperties(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;
  }
}

void AlgorithmPreorder::visit(const expression::ObjectExpression& node, bool callFirst /*= true*/){
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

void AlgorithmPreorder::visitAllEdges(const expression::Property& node, bool callFirst /*= true*/){
  visitAllEdges(dynamic_cast<const base::Positioned&>(node),false);

  std::list<Visitor*>::iterator itVisitors;

  const base::Base* genNodePtr;
  // edge: hasValue
  genNodePtr = node.getValue() ;
  if (genNodePtr) {
    const base::Positioned& endNodeRef = dynamic_cast<const base::Positioned&>(*genNodePtr);
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitProperty_HasValue(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;

    if ((!fact->getIsFilterTurnedOn() && !visitFilteredEdge) || (fact->getFilterState(endNodeRef.getId()) == Filter::NotFiltered) || (!originalFilterState && visitFilteredEdge)) {
      endNodeRef.accept(*this);
    }
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitEndProperty_HasValue(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;
  }

  // edge: hasKey
  genNodePtr = node.getKey() ;
  if (genNodePtr) {
    const expression::Expression& endNodeRef = dynamic_cast<const expression::Expression&>(*genNodePtr);
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitProperty_HasKey(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;

    if ((!fact->getIsFilterTurnedOn() && !visitFilteredEdge) || (fact->getFilterState(endNodeRef.getId()) == Filter::NotFiltered) || (!originalFilterState && visitFilteredEdge)) {
      endNodeRef.accept(*this);
    }
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitEndProperty_HasKey(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;
  }
}

void AlgorithmPreorder::visit(const expression::Property& node, bool callFirst /*= true*/){
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

void AlgorithmPreorder::visitAllEdges(const expression::RegExpLiteral& node, bool callFirst /*= true*/){
  if (callFirst)
    visitAllEdges(dynamic_cast<const base::Positioned&>(node),false);
  visitAllEdges(dynamic_cast<const expression::Literal&>(node),false);
}

void AlgorithmPreorder::visit(const expression::RegExpLiteral& node, bool callFirst /*= true*/){
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

void AlgorithmPreorder::visitAllEdges(const expression::SequenceExpression& node, bool callFirst /*= true*/){
  if (callFirst)
    visitAllEdges(dynamic_cast<const base::Positioned&>(node),false);
  visitAllEdges(dynamic_cast<const expression::Expression&>(node),false);

  std::list<Visitor*>::iterator itVisitors;

  // edge: hasExpressions
  for (ListIterator<expression::Expression> it = node.getExpressionsListIteratorBegin(); it != node.getExpressionsListIteratorEnd(); ++it) {
    const expression::Expression& endNodeRef = *it;
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitSequenceExpression_HasExpressions(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;

    if ((!fact->getIsFilterTurnedOn() && !visitFilteredEdge) || (fact->getFilterState(endNodeRef.getId()) == Filter::NotFiltered) || (!originalFilterState && visitFilteredEdge)) {
      endNodeRef.accept(*this);
    }
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitEndSequenceExpression_HasExpressions(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;
  }
}

void AlgorithmPreorder::visit(const expression::SequenceExpression& node, bool callFirst /*= true*/){
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

void AlgorithmPreorder::visitAllEdges(const expression::SpreadElement& node, bool callFirst /*= true*/){
  visitAllEdges(dynamic_cast<const base::Positioned&>(node),false);

  std::list<Visitor*>::iterator itVisitors;

  const base::Base* genNodePtr;
  // edge: hasArgument
  genNodePtr = node.getArgument() ;
  if (genNodePtr) {
    const expression::Expression& endNodeRef = dynamic_cast<const expression::Expression&>(*genNodePtr);
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitSpreadElement_HasArgument(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;

    if ((!fact->getIsFilterTurnedOn() && !visitFilteredEdge) || (fact->getFilterState(endNodeRef.getId()) == Filter::NotFiltered) || (!originalFilterState && visitFilteredEdge)) {
      endNodeRef.accept(*this);
    }
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitEndSpreadElement_HasArgument(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;
  }
}

void AlgorithmPreorder::visit(const expression::SpreadElement& node, bool callFirst /*= true*/){
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

void AlgorithmPreorder::visitAllEdges(const expression::StringLiteral& node, bool callFirst /*= true*/){
  if (callFirst)
    visitAllEdges(dynamic_cast<const base::Positioned&>(node),false);
  visitAllEdges(dynamic_cast<const expression::Literal&>(node),false);
}

void AlgorithmPreorder::visit(const expression::StringLiteral& node, bool callFirst /*= true*/){
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

void AlgorithmPreorder::visitAllEdges(const expression::Super& node, bool callFirst /*= true*/){
  visitAllEdges(dynamic_cast<const base::Positioned&>(node),false);
}

void AlgorithmPreorder::visit(const expression::Super& node, bool callFirst /*= true*/){
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

void AlgorithmPreorder::visitAllEdges(const expression::TaggedTemplateExpression& node, bool callFirst /*= true*/){
  if (callFirst)
    visitAllEdges(dynamic_cast<const base::Positioned&>(node),false);
  visitAllEdges(dynamic_cast<const expression::Expression&>(node),false);

  std::list<Visitor*>::iterator itVisitors;

  const base::Base* genNodePtr;
  // edge: hasTag
  genNodePtr = node.getTag() ;
  if (genNodePtr) {
    const expression::Expression& endNodeRef = dynamic_cast<const expression::Expression&>(*genNodePtr);
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitTaggedTemplateExpression_HasTag(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;

    if ((!fact->getIsFilterTurnedOn() && !visitFilteredEdge) || (fact->getFilterState(endNodeRef.getId()) == Filter::NotFiltered) || (!originalFilterState && visitFilteredEdge)) {
      endNodeRef.accept(*this);
    }
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitEndTaggedTemplateExpression_HasTag(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;
  }

  // edge: hasQuasi
  genNodePtr = node.getQuasi() ;
  if (genNodePtr) {
    const expression::TemplateLiteral& endNodeRef = dynamic_cast<const expression::TemplateLiteral&>(*genNodePtr);
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitTaggedTemplateExpression_HasQuasi(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;

    if ((!fact->getIsFilterTurnedOn() && !visitFilteredEdge) || (fact->getFilterState(endNodeRef.getId()) == Filter::NotFiltered) || (!originalFilterState && visitFilteredEdge)) {
      endNodeRef.accept(*this);
    }
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitEndTaggedTemplateExpression_HasQuasi(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;
  }
}

void AlgorithmPreorder::visit(const expression::TaggedTemplateExpression& node, bool callFirst /*= true*/){
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

void AlgorithmPreorder::visitAllEdges(const expression::TemplateElement& node, bool callFirst /*= true*/){
  visitAllEdges(dynamic_cast<const base::Positioned&>(node),false);
}

void AlgorithmPreorder::visit(const expression::TemplateElement& node, bool callFirst /*= true*/){
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

void AlgorithmPreorder::visitAllEdges(const expression::TemplateLiteral& node, bool callFirst /*= true*/){
  if (callFirst)
    visitAllEdges(dynamic_cast<const base::Positioned&>(node),false);
  visitAllEdges(dynamic_cast<const expression::Expression&>(node),false);

  std::list<Visitor*>::iterator itVisitors;

  // edge: hasQuasis
  for (ListIterator<expression::TemplateElement> it = node.getQuasisListIteratorBegin(); it != node.getQuasisListIteratorEnd(); ++it) {
    const expression::TemplateElement& endNodeRef = *it;
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitTemplateLiteral_HasQuasis(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;

    if ((!fact->getIsFilterTurnedOn() && !visitFilteredEdge) || (fact->getFilterState(endNodeRef.getId()) == Filter::NotFiltered) || (!originalFilterState && visitFilteredEdge)) {
      endNodeRef.accept(*this);
    }
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitEndTemplateLiteral_HasQuasis(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;
  }

  // edge: hasExpressions
  for (ListIterator<expression::Expression> it = node.getExpressionsListIteratorBegin(); it != node.getExpressionsListIteratorEnd(); ++it) {
    const expression::Expression& endNodeRef = *it;
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitTemplateLiteral_HasExpressions(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;

    if ((!fact->getIsFilterTurnedOn() && !visitFilteredEdge) || (fact->getFilterState(endNodeRef.getId()) == Filter::NotFiltered) || (!originalFilterState && visitFilteredEdge)) {
      endNodeRef.accept(*this);
    }
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitEndTemplateLiteral_HasExpressions(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;
  }
}

void AlgorithmPreorder::visit(const expression::TemplateLiteral& node, bool callFirst /*= true*/){
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

void AlgorithmPreorder::visitAllEdges(const expression::ThisExpression& node, bool callFirst /*= true*/){
  if (callFirst)
    visitAllEdges(dynamic_cast<const base::Positioned&>(node),false);
  visitAllEdges(dynamic_cast<const expression::Expression&>(node),false);
}

void AlgorithmPreorder::visit(const expression::ThisExpression& node, bool callFirst /*= true*/){
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

void AlgorithmPreorder::visitAllEdges(const expression::UnaryExpression& node, bool callFirst /*= true*/){
  if (callFirst)
    visitAllEdges(dynamic_cast<const base::Positioned&>(node),false);
  visitAllEdges(dynamic_cast<const expression::Expression&>(node),false);

  std::list<Visitor*>::iterator itVisitors;

  const base::Base* genNodePtr;
  // edge: hasArgument
  genNodePtr = node.getArgument() ;
  if (genNodePtr) {
    const expression::Expression& endNodeRef = dynamic_cast<const expression::Expression&>(*genNodePtr);
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitUnaryExpression_HasArgument(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;

    if ((!fact->getIsFilterTurnedOn() && !visitFilteredEdge) || (fact->getFilterState(endNodeRef.getId()) == Filter::NotFiltered) || (!originalFilterState && visitFilteredEdge)) {
      endNodeRef.accept(*this);
    }
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitEndUnaryExpression_HasArgument(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;
  }
}

void AlgorithmPreorder::visit(const expression::UnaryExpression& node, bool callFirst /*= true*/){
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

void AlgorithmPreorder::visitAllEdges(const expression::UpdateExpression& node, bool callFirst /*= true*/){
  if (callFirst)
    visitAllEdges(dynamic_cast<const base::Positioned&>(node),false);
  visitAllEdges(dynamic_cast<const expression::Expression&>(node),false);

  std::list<Visitor*>::iterator itVisitors;

  const base::Base* genNodePtr;
  // edge: hasArgument
  genNodePtr = node.getArgument() ;
  if (genNodePtr) {
    const expression::Expression& endNodeRef = dynamic_cast<const expression::Expression&>(*genNodePtr);
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitUpdateExpression_HasArgument(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;

    if ((!fact->getIsFilterTurnedOn() && !visitFilteredEdge) || (fact->getFilterState(endNodeRef.getId()) == Filter::NotFiltered) || (!originalFilterState && visitFilteredEdge)) {
      endNodeRef.accept(*this);
    }
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitEndUpdateExpression_HasArgument(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;
  }
}

void AlgorithmPreorder::visit(const expression::UpdateExpression& node, bool callFirst /*= true*/){
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

void AlgorithmPreorder::visitAllEdges(const expression::YieldExpression& node, bool callFirst /*= true*/){
  if (callFirst)
    visitAllEdges(dynamic_cast<const base::Positioned&>(node),false);
  visitAllEdges(dynamic_cast<const expression::Expression&>(node),false);

  std::list<Visitor*>::iterator itVisitors;

  const base::Base* genNodePtr;
  // edge: hasArgument
  genNodePtr = node.getArgument() ;
  if (genNodePtr) {
    const expression::Expression& endNodeRef = dynamic_cast<const expression::Expression&>(*genNodePtr);
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitYieldExpression_HasArgument(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;

    if ((!fact->getIsFilterTurnedOn() && !visitFilteredEdge) || (fact->getFilterState(endNodeRef.getId()) == Filter::NotFiltered) || (!originalFilterState && visitFilteredEdge)) {
      endNodeRef.accept(*this);
    }
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitEndYieldExpression_HasArgument(node, endNodeRef);
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

void AlgorithmPreorder::visitAllEdges(const statement::ArrayPattern& node, bool callFirst /*= true*/){
  if (callFirst)
    visitAllEdges(dynamic_cast<const base::Positioned&>(node),false);
  visitAllEdges(dynamic_cast<const statement::Pattern&>(node),false);

  std::list<Visitor*>::iterator itVisitors;

  // edge: hasElements
  for (ListIterator<statement::Pattern> it = node.getElementsListIteratorBegin(); it != node.getElementsListIteratorEnd(); ++it) {
    const statement::Pattern& endNodeRef = *it;
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitArrayPattern_HasElements(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;

    if ((!fact->getIsFilterTurnedOn() && !visitFilteredEdge) || (fact->getFilterState(endNodeRef.getId()) == Filter::NotFiltered) || (!originalFilterState && visitFilteredEdge)) {
      endNodeRef.accept(*this);
    }
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitEndArrayPattern_HasElements(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;
  }
}

void AlgorithmPreorder::visit(const statement::ArrayPattern& node, bool callFirst /*= true*/){
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

void AlgorithmPreorder::visitAllEdges(const statement::AssignmentPattern& node, bool callFirst /*= true*/){
  if (callFirst)
    visitAllEdges(dynamic_cast<const base::Positioned&>(node),false);
  visitAllEdges(dynamic_cast<const statement::Pattern&>(node),false);

  std::list<Visitor*>::iterator itVisitors;

  const base::Base* genNodePtr;
  // edge: hasLeft
  genNodePtr = node.getLeft() ;
  if (genNodePtr) {
    const statement::Pattern& endNodeRef = dynamic_cast<const statement::Pattern&>(*genNodePtr);
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitAssignmentPattern_HasLeft(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;

    if ((!fact->getIsFilterTurnedOn() && !visitFilteredEdge) || (fact->getFilterState(endNodeRef.getId()) == Filter::NotFiltered) || (!originalFilterState && visitFilteredEdge)) {
      endNodeRef.accept(*this);
    }
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitEndAssignmentPattern_HasLeft(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;
  }

  // edge: hasRight
  genNodePtr = node.getRight() ;
  if (genNodePtr) {
    const expression::Expression& endNodeRef = dynamic_cast<const expression::Expression&>(*genNodePtr);
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitAssignmentPattern_HasRight(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;

    if ((!fact->getIsFilterTurnedOn() && !visitFilteredEdge) || (fact->getFilterState(endNodeRef.getId()) == Filter::NotFiltered) || (!originalFilterState && visitFilteredEdge)) {
      endNodeRef.accept(*this);
    }
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitEndAssignmentPattern_HasRight(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;
  }
}

void AlgorithmPreorder::visit(const statement::AssignmentPattern& node, bool callFirst /*= true*/){
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

void AlgorithmPreorder::visitAllEdges(const statement::BlockStatement& node, bool callFirst /*= true*/){
  if (callFirst)
    visitAllEdges(dynamic_cast<const base::Positioned&>(node),false);
  visitAllEdges(dynamic_cast<const statement::Statement&>(node),false);

  std::list<Visitor*>::iterator itVisitors;

  // edge: hasBody
  for (ListIterator<statement::Statement> it = node.getBodyListIteratorBegin(); it != node.getBodyListIteratorEnd(); ++it) {
    const statement::Statement& endNodeRef = *it;
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitBlockStatement_HasBody(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;

    if ((!fact->getIsFilterTurnedOn() && !visitFilteredEdge) || (fact->getFilterState(endNodeRef.getId()) == Filter::NotFiltered) || (!originalFilterState && visitFilteredEdge)) {
      endNodeRef.accept(*this);
    }
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitEndBlockStatement_HasBody(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;
  }
}

void AlgorithmPreorder::visit(const statement::BlockStatement& node, bool callFirst /*= true*/){
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

void AlgorithmPreorder::visitAllEdges(const statement::BreakStatement& node, bool callFirst /*= true*/){
  if (callFirst)
    visitAllEdges(dynamic_cast<const base::Positioned&>(node),false);
  visitAllEdges(dynamic_cast<const statement::Statement&>(node),false);

  std::list<Visitor*>::iterator itVisitors;

  const base::Base* genNodePtr;
  // edge: hasLabel
  genNodePtr = node.getLabel() ;
  if (genNodePtr) {
    const expression::Identifier& endNodeRef = dynamic_cast<const expression::Identifier&>(*genNodePtr);
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitBreakStatement_HasLabel(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;

    if ((!fact->getIsFilterTurnedOn() && !visitFilteredEdge) || (fact->getFilterState(endNodeRef.getId()) == Filter::NotFiltered) || (!originalFilterState && visitFilteredEdge)) {
      endNodeRef.accept(*this);
    }
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitEndBreakStatement_HasLabel(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;
  }
}

void AlgorithmPreorder::visit(const statement::BreakStatement& node, bool callFirst /*= true*/){
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

void AlgorithmPreorder::visitAllEdges(const statement::CatchClause& node, bool callFirst /*= true*/){
  visitAllEdges(dynamic_cast<const base::Positioned&>(node),false);

  std::list<Visitor*>::iterator itVisitors;

  const base::Base* genNodePtr;
  // edge: hasParam
  genNodePtr = node.getParam() ;
  if (genNodePtr) {
    const statement::Pattern& endNodeRef = dynamic_cast<const statement::Pattern&>(*genNodePtr);
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitCatchClause_HasParam(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;

    if ((!fact->getIsFilterTurnedOn() && !visitFilteredEdge) || (fact->getFilterState(endNodeRef.getId()) == Filter::NotFiltered) || (!originalFilterState && visitFilteredEdge)) {
      endNodeRef.accept(*this);
    }
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitEndCatchClause_HasParam(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;
  }

  // edge: hasBody
  genNodePtr = node.getBody() ;
  if (genNodePtr) {
    const statement::BlockStatement& endNodeRef = dynamic_cast<const statement::BlockStatement&>(*genNodePtr);
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitCatchClause_HasBody(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;

    if ((!fact->getIsFilterTurnedOn() && !visitFilteredEdge) || (fact->getFilterState(endNodeRef.getId()) == Filter::NotFiltered) || (!originalFilterState && visitFilteredEdge)) {
      endNodeRef.accept(*this);
    }
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitEndCatchClause_HasBody(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;
  }
}

void AlgorithmPreorder::visit(const statement::CatchClause& node, bool callFirst /*= true*/){
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

void AlgorithmPreorder::visitAllEdges(const statement::ContinueStatement& node, bool callFirst /*= true*/){
  if (callFirst)
    visitAllEdges(dynamic_cast<const base::Positioned&>(node),false);
  visitAllEdges(dynamic_cast<const statement::Statement&>(node),false);

  std::list<Visitor*>::iterator itVisitors;

  const base::Base* genNodePtr;
  // edge: hasLabel
  genNodePtr = node.getLabel() ;
  if (genNodePtr) {
    const expression::Identifier& endNodeRef = dynamic_cast<const expression::Identifier&>(*genNodePtr);
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitContinueStatement_HasLabel(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;

    if ((!fact->getIsFilterTurnedOn() && !visitFilteredEdge) || (fact->getFilterState(endNodeRef.getId()) == Filter::NotFiltered) || (!originalFilterState && visitFilteredEdge)) {
      endNodeRef.accept(*this);
    }
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitEndContinueStatement_HasLabel(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;
  }
}

void AlgorithmPreorder::visit(const statement::ContinueStatement& node, bool callFirst /*= true*/){
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

void AlgorithmPreorder::visitAllEdges(const statement::DebuggerStatement& node, bool callFirst /*= true*/){
  if (callFirst)
    visitAllEdges(dynamic_cast<const base::Positioned&>(node),false);
  visitAllEdges(dynamic_cast<const statement::Statement&>(node),false);
}

void AlgorithmPreorder::visit(const statement::DebuggerStatement& node, bool callFirst /*= true*/){
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

void AlgorithmPreorder::visitAllEdges(const statement::DoWhileStatement& node, bool callFirst /*= true*/){
  if (callFirst)
    visitAllEdges(dynamic_cast<const base::Positioned&>(node),false);
  visitAllEdges(dynamic_cast<const statement::WhileStatement&>(node),false);
}

void AlgorithmPreorder::visit(const statement::DoWhileStatement& node, bool callFirst /*= true*/){
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

void AlgorithmPreorder::visitAllEdges(const statement::EmptyStatement& node, bool callFirst /*= true*/){
  if (callFirst)
    visitAllEdges(dynamic_cast<const base::Positioned&>(node),false);
  visitAllEdges(dynamic_cast<const statement::Statement&>(node),false);
}

void AlgorithmPreorder::visit(const statement::EmptyStatement& node, bool callFirst /*= true*/){
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

void AlgorithmPreorder::visitAllEdges(const statement::ExpressionStatement& node, bool callFirst /*= true*/){
  if (callFirst)
    visitAllEdges(dynamic_cast<const base::Positioned&>(node),false);
  visitAllEdges(dynamic_cast<const statement::Statement&>(node),false);

  std::list<Visitor*>::iterator itVisitors;

  const base::Base* genNodePtr;
  // edge: hasExpression
  genNodePtr = node.getExpression() ;
  if (genNodePtr) {
    const expression::Expression& endNodeRef = dynamic_cast<const expression::Expression&>(*genNodePtr);
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitExpressionStatement_HasExpression(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;

    if ((!fact->getIsFilterTurnedOn() && !visitFilteredEdge) || (fact->getFilterState(endNodeRef.getId()) == Filter::NotFiltered) || (!originalFilterState && visitFilteredEdge)) {
      endNodeRef.accept(*this);
    }
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitEndExpressionStatement_HasExpression(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;
  }
}

void AlgorithmPreorder::visit(const statement::ExpressionStatement& node, bool callFirst /*= true*/){
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

void AlgorithmPreorder::visitAllEdges(const statement::ForInStatement& node, bool callFirst /*= true*/){
  if (callFirst)
    visitAllEdges(dynamic_cast<const base::Positioned&>(node),false);
  visitAllEdges(dynamic_cast<const statement::Statement&>(node),false);

  std::list<Visitor*>::iterator itVisitors;

  const base::Base* genNodePtr;
  // edge: hasRight
  genNodePtr = node.getRight() ;
  if (genNodePtr) {
    const expression::Expression& endNodeRef = dynamic_cast<const expression::Expression&>(*genNodePtr);
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitForInStatement_HasRight(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;

    if ((!fact->getIsFilterTurnedOn() && !visitFilteredEdge) || (fact->getFilterState(endNodeRef.getId()) == Filter::NotFiltered) || (!originalFilterState && visitFilteredEdge)) {
      endNodeRef.accept(*this);
    }
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitEndForInStatement_HasRight(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;
  }

  // edge: hasBody
  genNodePtr = node.getBody() ;
  if (genNodePtr) {
    const statement::Statement& endNodeRef = dynamic_cast<const statement::Statement&>(*genNodePtr);
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitForInStatement_HasBody(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;

    if ((!fact->getIsFilterTurnedOn() && !visitFilteredEdge) || (fact->getFilterState(endNodeRef.getId()) == Filter::NotFiltered) || (!originalFilterState && visitFilteredEdge)) {
      endNodeRef.accept(*this);
    }
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitEndForInStatement_HasBody(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;
  }

  // edge: hasLeft
  genNodePtr = node.getLeft() ;
  if (genNodePtr) {
    const base::Positioned& endNodeRef = dynamic_cast<const base::Positioned&>(*genNodePtr);
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitForInStatement_HasLeft(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;

    if ((!fact->getIsFilterTurnedOn() && !visitFilteredEdge) || (fact->getFilterState(endNodeRef.getId()) == Filter::NotFiltered) || (!originalFilterState && visitFilteredEdge)) {
      endNodeRef.accept(*this);
    }
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitEndForInStatement_HasLeft(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;
  }
}

void AlgorithmPreorder::visit(const statement::ForInStatement& node, bool callFirst /*= true*/){
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

void AlgorithmPreorder::visitAllEdges(const statement::ForOfStatement& node, bool callFirst /*= true*/){
  if (callFirst)
    visitAllEdges(dynamic_cast<const base::Positioned&>(node),false);
  visitAllEdges(dynamic_cast<const statement::ForInStatement&>(node),false);
}

void AlgorithmPreorder::visit(const statement::ForOfStatement& node, bool callFirst /*= true*/){
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

void AlgorithmPreorder::visitAllEdges(const statement::ForStatement& node, bool callFirst /*= true*/){
  if (callFirst)
    visitAllEdges(dynamic_cast<const base::Positioned&>(node),false);
  visitAllEdges(dynamic_cast<const statement::Statement&>(node),false);

  std::list<Visitor*>::iterator itVisitors;

  const base::Base* genNodePtr;
  // edge: hasBody
  genNodePtr = node.getBody() ;
  if (genNodePtr) {
    const statement::Statement& endNodeRef = dynamic_cast<const statement::Statement&>(*genNodePtr);
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitForStatement_HasBody(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;

    if ((!fact->getIsFilterTurnedOn() && !visitFilteredEdge) || (fact->getFilterState(endNodeRef.getId()) == Filter::NotFiltered) || (!originalFilterState && visitFilteredEdge)) {
      endNodeRef.accept(*this);
    }
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitEndForStatement_HasBody(node, endNodeRef);
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
      (*itVisitors)->visitForStatement_HasTest(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;

    if ((!fact->getIsFilterTurnedOn() && !visitFilteredEdge) || (fact->getFilterState(endNodeRef.getId()) == Filter::NotFiltered) || (!originalFilterState && visitFilteredEdge)) {
      endNodeRef.accept(*this);
    }
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitEndForStatement_HasTest(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;
  }

  // edge: hasUpdate
  genNodePtr = node.getUpdate() ;
  if (genNodePtr) {
    const expression::Expression& endNodeRef = dynamic_cast<const expression::Expression&>(*genNodePtr);
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitForStatement_HasUpdate(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;

    if ((!fact->getIsFilterTurnedOn() && !visitFilteredEdge) || (fact->getFilterState(endNodeRef.getId()) == Filter::NotFiltered) || (!originalFilterState && visitFilteredEdge)) {
      endNodeRef.accept(*this);
    }
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitEndForStatement_HasUpdate(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;
  }

  // edge: hasInit
  genNodePtr = node.getInit() ;
  if (genNodePtr) {
    const base::Positioned& endNodeRef = dynamic_cast<const base::Positioned&>(*genNodePtr);
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitForStatement_HasInit(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;

    if ((!fact->getIsFilterTurnedOn() && !visitFilteredEdge) || (fact->getFilterState(endNodeRef.getId()) == Filter::NotFiltered) || (!originalFilterState && visitFilteredEdge)) {
      endNodeRef.accept(*this);
    }
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitEndForStatement_HasInit(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;
  }
}

void AlgorithmPreorder::visit(const statement::ForStatement& node, bool callFirst /*= true*/){
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

void AlgorithmPreorder::visitAllEdges(const statement::Function& node, bool callFirst /*= true*/){
  if (callFirst)
    visitAllEdges(dynamic_cast<const base::Positioned&>(node),false);

  std::list<Visitor*>::iterator itVisitors;

  // edge: hasParams
  for (ListIterator<statement::Pattern> it = node.getParamsListIteratorBegin(); it != node.getParamsListIteratorEnd(); ++it) {
    const statement::Pattern& endNodeRef = *it;
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitFunction_HasParams(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;

    if ((!fact->getIsFilterTurnedOn() && !visitFilteredEdge) || (fact->getFilterState(endNodeRef.getId()) == Filter::NotFiltered) || (!originalFilterState && visitFilteredEdge)) {
      endNodeRef.accept(*this);
    }
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitEndFunction_HasParams(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;
  }

  const base::Base* genNodePtr;
  // edge: hasBody
  genNodePtr = node.getBody() ;
  if (genNodePtr) {
    const base::Positioned& endNodeRef = dynamic_cast<const base::Positioned&>(*genNodePtr);
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitFunction_HasBody(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;

    if ((!fact->getIsFilterTurnedOn() && !visitFilteredEdge) || (fact->getFilterState(endNodeRef.getId()) == Filter::NotFiltered) || (!originalFilterState && visitFilteredEdge)) {
      endNodeRef.accept(*this);
    }
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitEndFunction_HasBody(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;
  }

  // edge: hasIdentifier
  genNodePtr = node.getIdentifier() ;
  if (genNodePtr) {
    const expression::Identifier& endNodeRef = dynamic_cast<const expression::Identifier&>(*genNodePtr);
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitFunction_HasIdentifier(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;

    if ((!fact->getIsFilterTurnedOn() && !visitFilteredEdge) || (fact->getFilterState(endNodeRef.getId()) == Filter::NotFiltered) || (!originalFilterState && visitFilteredEdge)) {
      endNodeRef.accept(*this);
    }
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitEndFunction_HasIdentifier(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;
  }
}

void AlgorithmPreorder::visit(const statement::Function& node, bool callFirst /*= true*/){
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

void AlgorithmPreorder::visitAllEdges(const statement::IfStatement& node, bool callFirst /*= true*/){
  if (callFirst)
    visitAllEdges(dynamic_cast<const base::Positioned&>(node),false);
  visitAllEdges(dynamic_cast<const statement::Statement&>(node),false);

  std::list<Visitor*>::iterator itVisitors;

  const base::Base* genNodePtr;
  // edge: hasTest
  genNodePtr = node.getTest() ;
  if (genNodePtr) {
    const expression::Expression& endNodeRef = dynamic_cast<const expression::Expression&>(*genNodePtr);
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitIfStatement_HasTest(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;

    if ((!fact->getIsFilterTurnedOn() && !visitFilteredEdge) || (fact->getFilterState(endNodeRef.getId()) == Filter::NotFiltered) || (!originalFilterState && visitFilteredEdge)) {
      endNodeRef.accept(*this);
    }
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitEndIfStatement_HasTest(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;
  }

  // edge: hasConsequent
  genNodePtr = node.getConsequent() ;
  if (genNodePtr) {
    const statement::Statement& endNodeRef = dynamic_cast<const statement::Statement&>(*genNodePtr);
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitIfStatement_HasConsequent(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;

    if ((!fact->getIsFilterTurnedOn() && !visitFilteredEdge) || (fact->getFilterState(endNodeRef.getId()) == Filter::NotFiltered) || (!originalFilterState && visitFilteredEdge)) {
      endNodeRef.accept(*this);
    }
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitEndIfStatement_HasConsequent(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;
  }

  // edge: hasAlternate
  genNodePtr = node.getAlternate() ;
  if (genNodePtr) {
    const statement::Statement& endNodeRef = dynamic_cast<const statement::Statement&>(*genNodePtr);
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitIfStatement_HasAlternate(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;

    if ((!fact->getIsFilterTurnedOn() && !visitFilteredEdge) || (fact->getFilterState(endNodeRef.getId()) == Filter::NotFiltered) || (!originalFilterState && visitFilteredEdge)) {
      endNodeRef.accept(*this);
    }
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitEndIfStatement_HasAlternate(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;
  }
}

void AlgorithmPreorder::visit(const statement::IfStatement& node, bool callFirst /*= true*/){
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

void AlgorithmPreorder::visitAllEdges(const statement::LabeledStatement& node, bool callFirst /*= true*/){
  if (callFirst)
    visitAllEdges(dynamic_cast<const base::Positioned&>(node),false);
  visitAllEdges(dynamic_cast<const statement::Statement&>(node),false);

  std::list<Visitor*>::iterator itVisitors;

  const base::Base* genNodePtr;
  // edge: hasLabel
  genNodePtr = node.getLabel() ;
  if (genNodePtr) {
    const expression::Identifier& endNodeRef = dynamic_cast<const expression::Identifier&>(*genNodePtr);
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitLabeledStatement_HasLabel(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;

    if ((!fact->getIsFilterTurnedOn() && !visitFilteredEdge) || (fact->getFilterState(endNodeRef.getId()) == Filter::NotFiltered) || (!originalFilterState && visitFilteredEdge)) {
      endNodeRef.accept(*this);
    }
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitEndLabeledStatement_HasLabel(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;
  }

  // edge: hasBody
  genNodePtr = node.getBody() ;
  if (genNodePtr) {
    const statement::Statement& endNodeRef = dynamic_cast<const statement::Statement&>(*genNodePtr);
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitLabeledStatement_HasBody(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;

    if ((!fact->getIsFilterTurnedOn() && !visitFilteredEdge) || (fact->getFilterState(endNodeRef.getId()) == Filter::NotFiltered) || (!originalFilterState && visitFilteredEdge)) {
      endNodeRef.accept(*this);
    }
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitEndLabeledStatement_HasBody(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;
  }
}

void AlgorithmPreorder::visit(const statement::LabeledStatement& node, bool callFirst /*= true*/){
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

void AlgorithmPreorder::visitAllEdges(const statement::ObjectPattern& node, bool callFirst /*= true*/){
  if (callFirst)
    visitAllEdges(dynamic_cast<const base::Positioned&>(node),false);
  visitAllEdges(dynamic_cast<const statement::Pattern&>(node),false);

  std::list<Visitor*>::iterator itVisitors;

  // edge: hasProperties
  for (ListIterator<expression::Property> it = node.getPropertiesListIteratorBegin(); it != node.getPropertiesListIteratorEnd(); ++it) {
    const expression::Property& endNodeRef = *it;
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitObjectPattern_HasProperties(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;

    if ((!fact->getIsFilterTurnedOn() && !visitFilteredEdge) || (fact->getFilterState(endNodeRef.getId()) == Filter::NotFiltered) || (!originalFilterState && visitFilteredEdge)) {
      endNodeRef.accept(*this);
    }
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitEndObjectPattern_HasProperties(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;
  }
}

void AlgorithmPreorder::visit(const statement::ObjectPattern& node, bool callFirst /*= true*/){
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

void AlgorithmPreorder::visitAllEdges(const statement::Pattern& node, bool callFirst /*= true*/){
  if (callFirst)
    visitAllEdges(dynamic_cast<const base::Positioned&>(node),false);
}

void AlgorithmPreorder::visitAllEdges(const statement::RestElement& node, bool callFirst /*= true*/){
  if (callFirst)
    visitAllEdges(dynamic_cast<const base::Positioned&>(node),false);
  visitAllEdges(dynamic_cast<const statement::Pattern&>(node),false);

  std::list<Visitor*>::iterator itVisitors;

  const base::Base* genNodePtr;
  // edge: hasArgument
  genNodePtr = node.getArgument() ;
  if (genNodePtr) {
    const statement::Pattern& endNodeRef = dynamic_cast<const statement::Pattern&>(*genNodePtr);
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitRestElement_HasArgument(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;

    if ((!fact->getIsFilterTurnedOn() && !visitFilteredEdge) || (fact->getFilterState(endNodeRef.getId()) == Filter::NotFiltered) || (!originalFilterState && visitFilteredEdge)) {
      endNodeRef.accept(*this);
    }
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitEndRestElement_HasArgument(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;
  }
}

void AlgorithmPreorder::visit(const statement::RestElement& node, bool callFirst /*= true*/){
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

void AlgorithmPreorder::visitAllEdges(const statement::ReturnStatement& node, bool callFirst /*= true*/){
  if (callFirst)
    visitAllEdges(dynamic_cast<const base::Positioned&>(node),false);
  visitAllEdges(dynamic_cast<const statement::Statement&>(node),false);

  std::list<Visitor*>::iterator itVisitors;

  const base::Base* genNodePtr;
  // edge: hasArgument
  genNodePtr = node.getArgument() ;
  if (genNodePtr) {
    const expression::Expression& endNodeRef = dynamic_cast<const expression::Expression&>(*genNodePtr);
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitReturnStatement_HasArgument(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;

    if ((!fact->getIsFilterTurnedOn() && !visitFilteredEdge) || (fact->getFilterState(endNodeRef.getId()) == Filter::NotFiltered) || (!originalFilterState && visitFilteredEdge)) {
      endNodeRef.accept(*this);
    }
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitEndReturnStatement_HasArgument(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;
  }
}

void AlgorithmPreorder::visit(const statement::ReturnStatement& node, bool callFirst /*= true*/){
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

void AlgorithmPreorder::visitAllEdges(const statement::Statement& node, bool callFirst /*= true*/){
  if (callFirst)
    visitAllEdges(dynamic_cast<const base::Positioned&>(node),false);
}

void AlgorithmPreorder::visitAllEdges(const statement::SwitchCase& node, bool callFirst /*= true*/){
  visitAllEdges(dynamic_cast<const base::Positioned&>(node),false);

  std::list<Visitor*>::iterator itVisitors;

  const base::Base* genNodePtr;
  // edge: hasTest
  genNodePtr = node.getTest() ;
  if (genNodePtr) {
    const expression::Expression& endNodeRef = dynamic_cast<const expression::Expression&>(*genNodePtr);
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitSwitchCase_HasTest(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;

    if ((!fact->getIsFilterTurnedOn() && !visitFilteredEdge) || (fact->getFilterState(endNodeRef.getId()) == Filter::NotFiltered) || (!originalFilterState && visitFilteredEdge)) {
      endNodeRef.accept(*this);
    }
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitEndSwitchCase_HasTest(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;
  }

  // edge: hasConsequent
  for (ListIterator<statement::Statement> it = node.getConsequentListIteratorBegin(); it != node.getConsequentListIteratorEnd(); ++it) {
    const statement::Statement& endNodeRef = *it;
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitSwitchCase_HasConsequent(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;

    if ((!fact->getIsFilterTurnedOn() && !visitFilteredEdge) || (fact->getFilterState(endNodeRef.getId()) == Filter::NotFiltered) || (!originalFilterState && visitFilteredEdge)) {
      endNodeRef.accept(*this);
    }
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitEndSwitchCase_HasConsequent(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;
  }
}

void AlgorithmPreorder::visit(const statement::SwitchCase& node, bool callFirst /*= true*/){
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

void AlgorithmPreorder::visitAllEdges(const statement::SwitchStatement& node, bool callFirst /*= true*/){
  if (callFirst)
    visitAllEdges(dynamic_cast<const base::Positioned&>(node),false);
  visitAllEdges(dynamic_cast<const statement::Statement&>(node),false);

  std::list<Visitor*>::iterator itVisitors;

  const base::Base* genNodePtr;
  // edge: hasDiscriminant
  genNodePtr = node.getDiscriminant() ;
  if (genNodePtr) {
    const expression::Expression& endNodeRef = dynamic_cast<const expression::Expression&>(*genNodePtr);
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitSwitchStatement_HasDiscriminant(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;

    if ((!fact->getIsFilterTurnedOn() && !visitFilteredEdge) || (fact->getFilterState(endNodeRef.getId()) == Filter::NotFiltered) || (!originalFilterState && visitFilteredEdge)) {
      endNodeRef.accept(*this);
    }
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitEndSwitchStatement_HasDiscriminant(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;
  }

  // edge: hasCases
  for (ListIterator<statement::SwitchCase> it = node.getCasesListIteratorBegin(); it != node.getCasesListIteratorEnd(); ++it) {
    const statement::SwitchCase& endNodeRef = *it;
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitSwitchStatement_HasCases(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;

    if ((!fact->getIsFilterTurnedOn() && !visitFilteredEdge) || (fact->getFilterState(endNodeRef.getId()) == Filter::NotFiltered) || (!originalFilterState && visitFilteredEdge)) {
      endNodeRef.accept(*this);
    }
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitEndSwitchStatement_HasCases(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;
  }
}

void AlgorithmPreorder::visit(const statement::SwitchStatement& node, bool callFirst /*= true*/){
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

void AlgorithmPreorder::visitAllEdges(const statement::ThrowStatement& node, bool callFirst /*= true*/){
  if (callFirst)
    visitAllEdges(dynamic_cast<const base::Positioned&>(node),false);
  visitAllEdges(dynamic_cast<const statement::Statement&>(node),false);

  std::list<Visitor*>::iterator itVisitors;

  const base::Base* genNodePtr;
  // edge: hasArgument
  genNodePtr = node.getArgument() ;
  if (genNodePtr) {
    const expression::Expression& endNodeRef = dynamic_cast<const expression::Expression&>(*genNodePtr);
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitThrowStatement_HasArgument(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;

    if ((!fact->getIsFilterTurnedOn() && !visitFilteredEdge) || (fact->getFilterState(endNodeRef.getId()) == Filter::NotFiltered) || (!originalFilterState && visitFilteredEdge)) {
      endNodeRef.accept(*this);
    }
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitEndThrowStatement_HasArgument(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;
  }
}

void AlgorithmPreorder::visit(const statement::ThrowStatement& node, bool callFirst /*= true*/){
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

void AlgorithmPreorder::visitAllEdges(const statement::TryStatement& node, bool callFirst /*= true*/){
  if (callFirst)
    visitAllEdges(dynamic_cast<const base::Positioned&>(node),false);
  visitAllEdges(dynamic_cast<const statement::Statement&>(node),false);

  std::list<Visitor*>::iterator itVisitors;

  const base::Base* genNodePtr;
  // edge: hasBlock
  genNodePtr = node.getBlock() ;
  if (genNodePtr) {
    const statement::BlockStatement& endNodeRef = dynamic_cast<const statement::BlockStatement&>(*genNodePtr);
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitTryStatement_HasBlock(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;

    if ((!fact->getIsFilterTurnedOn() && !visitFilteredEdge) || (fact->getFilterState(endNodeRef.getId()) == Filter::NotFiltered) || (!originalFilterState && visitFilteredEdge)) {
      endNodeRef.accept(*this);
    }
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitEndTryStatement_HasBlock(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;
  }

  // edge: hasFinalizer
  genNodePtr = node.getFinalizer() ;
  if (genNodePtr) {
    const statement::BlockStatement& endNodeRef = dynamic_cast<const statement::BlockStatement&>(*genNodePtr);
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitTryStatement_HasFinalizer(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;

    if ((!fact->getIsFilterTurnedOn() && !visitFilteredEdge) || (fact->getFilterState(endNodeRef.getId()) == Filter::NotFiltered) || (!originalFilterState && visitFilteredEdge)) {
      endNodeRef.accept(*this);
    }
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitEndTryStatement_HasFinalizer(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;
  }

  // edge: hasHandler
  genNodePtr = node.getHandler() ;
  if (genNodePtr) {
    const statement::CatchClause& endNodeRef = dynamic_cast<const statement::CatchClause&>(*genNodePtr);
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitTryStatement_HasHandler(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;

    if ((!fact->getIsFilterTurnedOn() && !visitFilteredEdge) || (fact->getFilterState(endNodeRef.getId()) == Filter::NotFiltered) || (!originalFilterState && visitFilteredEdge)) {
      endNodeRef.accept(*this);
    }
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitEndTryStatement_HasHandler(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;
  }
}

void AlgorithmPreorder::visit(const statement::TryStatement& node, bool callFirst /*= true*/){
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

void AlgorithmPreorder::visitAllEdges(const statement::WhileStatement& node, bool callFirst /*= true*/){
  if (callFirst)
    visitAllEdges(dynamic_cast<const base::Positioned&>(node),false);
  visitAllEdges(dynamic_cast<const statement::Statement&>(node),false);

  std::list<Visitor*>::iterator itVisitors;

  const base::Base* genNodePtr;
  // edge: hasBody
  genNodePtr = node.getBody() ;
  if (genNodePtr) {
    const statement::Statement& endNodeRef = dynamic_cast<const statement::Statement&>(*genNodePtr);
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitWhileStatement_HasBody(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;

    if ((!fact->getIsFilterTurnedOn() && !visitFilteredEdge) || (fact->getFilterState(endNodeRef.getId()) == Filter::NotFiltered) || (!originalFilterState && visitFilteredEdge)) {
      endNodeRef.accept(*this);
    }
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitEndWhileStatement_HasBody(node, endNodeRef);
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
      (*itVisitors)->visitWhileStatement_HasTest(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;

    if ((!fact->getIsFilterTurnedOn() && !visitFilteredEdge) || (fact->getFilterState(endNodeRef.getId()) == Filter::NotFiltered) || (!originalFilterState && visitFilteredEdge)) {
      endNodeRef.accept(*this);
    }
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitEndWhileStatement_HasTest(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;
  }
}

void AlgorithmPreorder::visit(const statement::WhileStatement& node, bool callFirst /*= true*/){
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

void AlgorithmPreorder::visitAllEdges(const statement::WithStatement& node, bool callFirst /*= true*/){
  if (callFirst)
    visitAllEdges(dynamic_cast<const base::Positioned&>(node),false);
  visitAllEdges(dynamic_cast<const statement::Statement&>(node),false);

  std::list<Visitor*>::iterator itVisitors;

  const base::Base* genNodePtr;
  // edge: hasObject
  genNodePtr = node.getObject() ;
  if (genNodePtr) {
    const expression::Expression& endNodeRef = dynamic_cast<const expression::Expression&>(*genNodePtr);
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitWithStatement_HasObject(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;

    if ((!fact->getIsFilterTurnedOn() && !visitFilteredEdge) || (fact->getFilterState(endNodeRef.getId()) == Filter::NotFiltered) || (!originalFilterState && visitFilteredEdge)) {
      endNodeRef.accept(*this);
    }
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitEndWithStatement_HasObject(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;
  }

  // edge: hasBody
  genNodePtr = node.getBody() ;
  if (genNodePtr) {
    const statement::Statement& endNodeRef = dynamic_cast<const statement::Statement&>(*genNodePtr);
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitWithStatement_HasBody(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;

    if ((!fact->getIsFilterTurnedOn() && !visitFilteredEdge) || (fact->getFilterState(endNodeRef.getId()) == Filter::NotFiltered) || (!originalFilterState && visitFilteredEdge)) {
      endNodeRef.accept(*this);
    }
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitEndWithStatement_HasBody(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;
  }
}

void AlgorithmPreorder::visit(const statement::WithStatement& node, bool callFirst /*= true*/){
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

void AlgorithmPreorder::visitAllEdges(const structure::Class& node, bool callFirst /*= true*/){
  if (callFirst)
    visitAllEdges(dynamic_cast<const base::Positioned&>(node),false);

  std::list<Visitor*>::iterator itVisitors;

  const base::Base* genNodePtr;
  // edge: hasBody
  genNodePtr = node.getBody() ;
  if (genNodePtr) {
    const structure::ClassBody& endNodeRef = dynamic_cast<const structure::ClassBody&>(*genNodePtr);
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitClass_HasBody(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;

    if ((!fact->getIsFilterTurnedOn() && !visitFilteredEdge) || (fact->getFilterState(endNodeRef.getId()) == Filter::NotFiltered) || (!originalFilterState && visitFilteredEdge)) {
      endNodeRef.accept(*this);
    }
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitEndClass_HasBody(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;
  }

  // edge: hasSuperClass
  genNodePtr = node.getSuperClass() ;
  if (genNodePtr) {
    const expression::Expression& endNodeRef = dynamic_cast<const expression::Expression&>(*genNodePtr);
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitClass_HasSuperClass(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;

    if ((!fact->getIsFilterTurnedOn() && !visitFilteredEdge) || (fact->getFilterState(endNodeRef.getId()) == Filter::NotFiltered) || (!originalFilterState && visitFilteredEdge)) {
      endNodeRef.accept(*this);
    }
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitEndClass_HasSuperClass(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;
  }

  // edge: hasIdentifier
  genNodePtr = node.getIdentifier() ;
  if (genNodePtr) {
    const expression::Identifier& endNodeRef = dynamic_cast<const expression::Identifier&>(*genNodePtr);
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitClass_HasIdentifier(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;

    if ((!fact->getIsFilterTurnedOn() && !visitFilteredEdge) || (fact->getFilterState(endNodeRef.getId()) == Filter::NotFiltered) || (!originalFilterState && visitFilteredEdge)) {
      endNodeRef.accept(*this);
    }
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitEndClass_HasIdentifier(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;
  }
}

void AlgorithmPreorder::visitAllEdges(const structure::ClassBody& node, bool callFirst /*= true*/){
  visitAllEdges(dynamic_cast<const base::Positioned&>(node),false);

  std::list<Visitor*>::iterator itVisitors;

  // edge: hasBody
  for (ListIterator<structure::MethodDefinition> it = node.getBodyListIteratorBegin(); it != node.getBodyListIteratorEnd(); ++it) {
    const structure::MethodDefinition& endNodeRef = *it;
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitClassBody_HasBody(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;

    if ((!fact->getIsFilterTurnedOn() && !visitFilteredEdge) || (fact->getFilterState(endNodeRef.getId()) == Filter::NotFiltered) || (!originalFilterState && visitFilteredEdge)) {
      endNodeRef.accept(*this);
    }
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitEndClassBody_HasBody(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;
  }
}

void AlgorithmPreorder::visit(const structure::ClassBody& node, bool callFirst /*= true*/){
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

void AlgorithmPreorder::visitAllEdges(const structure::ExportSpecifier& node, bool callFirst /*= true*/){
  visitAllEdges(dynamic_cast<const structure::ModuleSpecifier&>(node),false);

  std::list<Visitor*>::iterator itVisitors;

  const base::Base* genNodePtr;
  // edge: hasExported
  genNodePtr = node.getExported() ;
  if (genNodePtr) {
    const expression::Identifier& endNodeRef = dynamic_cast<const expression::Identifier&>(*genNodePtr);
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitExportSpecifier_HasExported(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;

    if ((!fact->getIsFilterTurnedOn() && !visitFilteredEdge) || (fact->getFilterState(endNodeRef.getId()) == Filter::NotFiltered) || (!originalFilterState && visitFilteredEdge)) {
      endNodeRef.accept(*this);
    }
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitEndExportSpecifier_HasExported(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;
  }
}

void AlgorithmPreorder::visit(const structure::ExportSpecifier& node, bool callFirst /*= true*/){
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

void AlgorithmPreorder::visitAllEdges(const structure::ImpSpecifier& node, bool callFirst /*= true*/){
  visitAllEdges(dynamic_cast<const structure::ModuleSpecifier&>(node),false);
}

void AlgorithmPreorder::visitAllEdges(const structure::ImportDefaultSpecifier& node, bool callFirst /*= true*/){
  visitAllEdges(dynamic_cast<const structure::ImpSpecifier&>(node),false);
}

void AlgorithmPreorder::visit(const structure::ImportDefaultSpecifier& node, bool callFirst /*= true*/){
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

void AlgorithmPreorder::visitAllEdges(const structure::ImportNamespaceSpecifier& node, bool callFirst /*= true*/){
  visitAllEdges(dynamic_cast<const structure::ImpSpecifier&>(node),false);
}

void AlgorithmPreorder::visit(const structure::ImportNamespaceSpecifier& node, bool callFirst /*= true*/){
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

void AlgorithmPreorder::visitAllEdges(const structure::ImportSpecifier& node, bool callFirst /*= true*/){
  visitAllEdges(dynamic_cast<const structure::ImpSpecifier&>(node),false);

  std::list<Visitor*>::iterator itVisitors;

  const base::Base* genNodePtr;
  // edge: hasImported
  genNodePtr = node.getImported() ;
  if (genNodePtr) {
    const expression::Identifier& endNodeRef = dynamic_cast<const expression::Identifier&>(*genNodePtr);
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitImportSpecifier_HasImported(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;

    if ((!fact->getIsFilterTurnedOn() && !visitFilteredEdge) || (fact->getFilterState(endNodeRef.getId()) == Filter::NotFiltered) || (!originalFilterState && visitFilteredEdge)) {
      endNodeRef.accept(*this);
    }
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitEndImportSpecifier_HasImported(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;
  }
}

void AlgorithmPreorder::visit(const structure::ImportSpecifier& node, bool callFirst /*= true*/){
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

void AlgorithmPreorder::visitAllEdges(const structure::MethodDefinition& node, bool callFirst /*= true*/){
  visitAllEdges(dynamic_cast<const base::Positioned&>(node),false);

  std::list<Visitor*>::iterator itVisitors;

  const base::Base* genNodePtr;
  // edge: hasKey
  genNodePtr = node.getKey() ;
  if (genNodePtr) {
    const expression::Expression& endNodeRef = dynamic_cast<const expression::Expression&>(*genNodePtr);
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitMethodDefinition_HasKey(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;

    if ((!fact->getIsFilterTurnedOn() && !visitFilteredEdge) || (fact->getFilterState(endNodeRef.getId()) == Filter::NotFiltered) || (!originalFilterState && visitFilteredEdge)) {
      endNodeRef.accept(*this);
    }
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitEndMethodDefinition_HasKey(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;
  }

  // edge: hasValue
  genNodePtr = node.getValue() ;
  if (genNodePtr) {
    const expression::FunctionExpression& endNodeRef = dynamic_cast<const expression::FunctionExpression&>(*genNodePtr);
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitMethodDefinition_HasValue(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;

    if ((!fact->getIsFilterTurnedOn() && !visitFilteredEdge) || (fact->getFilterState(endNodeRef.getId()) == Filter::NotFiltered) || (!originalFilterState && visitFilteredEdge)) {
      endNodeRef.accept(*this);
    }
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitEndMethodDefinition_HasValue(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;
  }
}

void AlgorithmPreorder::visit(const structure::MethodDefinition& node, bool callFirst /*= true*/){
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

void AlgorithmPreorder::visitAllEdges(const structure::ModuleSpecifier& node, bool callFirst /*= true*/){
  visitAllEdges(dynamic_cast<const base::Positioned&>(node),false);

  std::list<Visitor*>::iterator itVisitors;

  const base::Base* genNodePtr;
  // edge: hasLocal
  genNodePtr = node.getLocal() ;
  if (genNodePtr) {
    const expression::Identifier& endNodeRef = dynamic_cast<const expression::Identifier&>(*genNodePtr);
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitModuleSpecifier_HasLocal(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;

    if ((!fact->getIsFilterTurnedOn() && !visitFilteredEdge) || (fact->getFilterState(endNodeRef.getId()) == Filter::NotFiltered) || (!originalFilterState && visitFilteredEdge)) {
      endNodeRef.accept(*this);
    }
    for (itVisitors = visitorList.begin(); itVisitors != visitorList.end(); ++itVisitors) {
      (*itVisitors)->visitEndModuleSpecifier_HasLocal(node, endNodeRef);
    }

    clearStoppedVisitors();
    if(needPreorderStop)
      return;
  }
}

void AlgorithmPreorder::startPreorder(){

  if (!fact){
    throw JavaScriptException(COLUMBUS_LOCATION, CMSG_EX_YOU_MUST_GIVE_A_FACTORY_AT_FIRST);
  }

  if (visitorList.empty()){
    throw JavaScriptException(COLUMBUS_LOCATION, CMSG_EX_DON_T_HAVE_ANY_VISITOR);
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
