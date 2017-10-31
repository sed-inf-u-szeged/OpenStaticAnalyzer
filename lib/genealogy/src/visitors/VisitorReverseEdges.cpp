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

namespace columbus { namespace genealogy { 
VisitorReverseEdges::VisitorReverseEdges(ReverseEdges *reverseEdges) : VisitorAbstractNodes(), revEdges(reverseEdges) {
}

VisitorReverseEdges::~VisitorReverseEdges() {
}

void VisitorReverseEdges::visit(const Base &node, bool callVirtualBase ) {
  NodeId id = node.getId();
  if (!revEdges->reContainer[id])
    revEdges->reContainer[id] = new ReverseEdges::NodeEdgesType();
}

void VisitorReverseEdges::visitProject_Systems(const Project& begin, const System& end) {
  revEdges->insertEdge(&end, &begin, edkProject_Systems);
}

void VisitorReverseEdges::visitTrackable_Prev(const Trackable& begin, const Trackable& end) {
  revEdges->insertEdge(&end, &begin, edkTrackable_Prev);
}

void VisitorReverseEdges::visitTrackable_Next(const Trackable& begin, const Trackable& end) {
  revEdges->insertEdge(&end, &begin, edkTrackable_Next);
}

void VisitorReverseEdges::visitSystem_Components(const System& begin, const Component& end) {
  revEdges->insertEdge(&end, &begin, edkSystem_Components);
}

void VisitorReverseEdges::visitSystem_CloneClasses(const System& begin, const CloneClass& end) {
  revEdges->insertEdge(&end, &begin, edkSystem_CloneClasses);
}

void VisitorReverseEdges::visitSystem_Smells(const System& begin, const StructuralClone& end) {
  revEdges->insertEdge(&end, &begin, edkSystem_Smells);
}

void VisitorReverseEdges::visitSystem_Next(const System& begin, const System& end) {
  revEdges->insertEdge(&end, &begin, edkSystem_Next);
}

void VisitorReverseEdges::visitSystem_Prev(const System& begin, const System& end) {
  revEdges->insertEdge(&end, &begin, edkSystem_Prev);
}

void VisitorReverseEdges::visitCloneClass_NextNeighbours(const CloneClass& begin, const CloneClass& end) {
  revEdges->insertEdge(&end, &begin, edkCloneClass_NextNeighbours);
}

void VisitorReverseEdges::visitCloneClass_PrevNeighbours(const CloneClass& begin, const CloneClass& end) {
  revEdges->insertEdge(&end, &begin, edkCloneClass_PrevNeighbours);
}

void VisitorReverseEdges::visitCloneClass_Items(const CloneClass& begin, const CloneInstance& end) {
  revEdges->insertEdge(&end, &begin, edkCloneClass_Items);
}

void VisitorReverseEdges::visitCloneInstance_Intersects(const CloneInstance& begin, const CloneInstance& end) {
  revEdges->insertEdge(&end, &begin, edkCloneInstance_Intersects);
}

void VisitorReverseEdges::visitCloneInstance_Component(const CloneInstance& begin, const Component& end) {
  revEdges->insertEdge(&end, &begin, edkCloneInstance_Component);
}

void VisitorReverseEdges::visitCloneInstance_CloneClass(const CloneInstance& begin, const CloneClass& end) {
  revEdges->insertEdge(&end, &begin, edkCloneInstance_CloneClass);
}

void VisitorReverseEdges::visitDataClumpsClass_Items(const DataClumpsClass& begin, const DataClumps& end) {
  revEdges->insertEdge(&end, &begin, edkDataClumpsClass_Items);
}

void VisitorReverseEdges::visitDataClumps_DataClumpsClass(const DataClumps& begin, const DataClumpsClass& end) {
  revEdges->insertEdge(&end, &begin, edkDataClumps_DataClumpsClass);
}

void VisitorReverseEdges::visitDataClumps_Items(const DataClumps& begin, const DataElement& end) {
  revEdges->insertEdge(&end, &begin, edkDataClumps_Items);
}

void VisitorReverseEdges::visitDataElement_Component(const DataElement& begin, const Component& end) {
  revEdges->insertEdge(&end, &begin, edkDataElement_Component);
}

void VisitorReverseEdges::visitSwitchStatementClass_Items(const SwitchStatementClass& begin, const SwitchStatement& end) {
  revEdges->insertEdge(&end, &begin, edkSwitchStatementClass_Items);
}

void VisitorReverseEdges::visitSwitchStatement_SwitchStatementClass(const SwitchStatement& begin, const SwitchStatementClass& end) {
  revEdges->insertEdge(&end, &begin, edkSwitchStatement_SwitchStatementClass);
}

void VisitorReverseEdges::visitSwitchStatement_Items(const SwitchStatement& begin, const CaseLabel& end) {
  revEdges->insertEdge(&end, &begin, edkSwitchStatement_Items);
}

void VisitorReverseEdges::visitCaseLabel_Component(const CaseLabel& begin, const Component& end) {
  revEdges->insertEdge(&end, &begin, edkCaseLabel_Component);
}


}}
