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
Visitor::Visitor(): depth(0) {
}

Visitor::~Visitor() {
}

unsigned Visitor::getDepth() const {
  return depth;
}

void Visitor::incDepth() {
  ++depth;
}

void Visitor::decDepth() {
  --depth;
}

void Visitor::beginVisit() {
}

void Visitor::finishVisit() {
}

void Visitor::visit(const Project& node , bool callVirtualBase) {}

void Visitor::visitEnd(const Project& node , bool callVirtualBase) { }

void Visitor::visit(const Trackable& node , bool callVirtualBase) {}

void Visitor::visitEnd(const Trackable& node , bool callVirtualBase) { }

void Visitor::visit(const Component& node , bool callVirtualBase) {}

void Visitor::visitEnd(const Component& node , bool callVirtualBase) { }

void Visitor::visit(const SourceCodeElement& node , bool callVirtualBase) {}

void Visitor::visitEnd(const SourceCodeElement& node , bool callVirtualBase) { }

void Visitor::visit(const System& node , bool callVirtualBase) {}

void Visitor::visitEnd(const System& node , bool callVirtualBase) { }

void Visitor::visit(const Clone& node , bool callVirtualBase) {}

void Visitor::visitEnd(const Clone& node , bool callVirtualBase) { }

void Visitor::visit(const StructuralClone& node , bool callVirtualBase) {}

void Visitor::visitEnd(const StructuralClone& node , bool callVirtualBase) { }

void Visitor::visit(const CloneClass& node , bool callVirtualBase) {}

void Visitor::visitEnd(const CloneClass& node , bool callVirtualBase) { }

void Visitor::visit(const CloneInstance& node , bool callVirtualBase) {}

void Visitor::visitEnd(const CloneInstance& node , bool callVirtualBase) { }

void Visitor::visit(const DataClumpsClass& node , bool callVirtualBase) {}

void Visitor::visitEnd(const DataClumpsClass& node , bool callVirtualBase) { }

void Visitor::visit(const DataClumps& node , bool callVirtualBase) {}

void Visitor::visitEnd(const DataClumps& node , bool callVirtualBase) { }

void Visitor::visit(const DataElement& node , bool callVirtualBase) {}

void Visitor::visitEnd(const DataElement& node , bool callVirtualBase) { }

void Visitor::visit(const SwitchStatementClass& node , bool callVirtualBase) {}

void Visitor::visitEnd(const SwitchStatementClass& node , bool callVirtualBase) { }

void Visitor::visit(const SwitchStatement& node , bool callVirtualBase) {}

void Visitor::visitEnd(const SwitchStatement& node , bool callVirtualBase) { }

void Visitor::visit(const CaseLabel& node , bool callVirtualBase) {}

void Visitor::visitEnd(const CaseLabel& node , bool callVirtualBase) { }

void Visitor::visitProject_Systems(const Project& begin, const System& end) { }

void Visitor::visitEndProject_Systems(const Project& begin, const System& end) { }

void Visitor::visitTrackable_Prev(const Trackable& begin, const Trackable& end) { }

void Visitor::visitEndTrackable_Prev(const Trackable& begin, const Trackable& end) { }

void Visitor::visitTrackable_Next(const Trackable& begin, const Trackable& end) { }

void Visitor::visitEndTrackable_Next(const Trackable& begin, const Trackable& end) { }

void Visitor::visitSystem_Components(const System& begin, const Component& end) { }

void Visitor::visitEndSystem_Components(const System& begin, const Component& end) { }

void Visitor::visitSystem_CloneClasses(const System& begin, const CloneClass& end) { }

void Visitor::visitEndSystem_CloneClasses(const System& begin, const CloneClass& end) { }

void Visitor::visitSystem_Smells(const System& begin, const StructuralClone& end) { }

void Visitor::visitEndSystem_Smells(const System& begin, const StructuralClone& end) { }

void Visitor::visitSystem_Next(const System& begin, const System& end) { }

void Visitor::visitEndSystem_Next(const System& begin, const System& end) { }

void Visitor::visitSystem_Prev(const System& begin, const System& end) { }

void Visitor::visitEndSystem_Prev(const System& begin, const System& end) { }

void Visitor::visitCloneClass_NextNeighbours(const CloneClass& begin, const CloneClass& end) { }

void Visitor::visitEndCloneClass_NextNeighbours(const CloneClass& begin, const CloneClass& end) { }

void Visitor::visitCloneClass_PrevNeighbours(const CloneClass& begin, const CloneClass& end) { }

void Visitor::visitEndCloneClass_PrevNeighbours(const CloneClass& begin, const CloneClass& end) { }

void Visitor::visitCloneClass_Items(const CloneClass& begin, const CloneInstance& end) { }

void Visitor::visitEndCloneClass_Items(const CloneClass& begin, const CloneInstance& end) { }

void Visitor::visitCloneInstance_Intersects(const CloneInstance& begin, const CloneInstance& end) { }

void Visitor::visitEndCloneInstance_Intersects(const CloneInstance& begin, const CloneInstance& end) { }

void Visitor::visitCloneInstance_Component(const CloneInstance& begin, const Component& end) { }

void Visitor::visitEndCloneInstance_Component(const CloneInstance& begin, const Component& end) { }

void Visitor::visitCloneInstance_CloneClass(const CloneInstance& begin, const CloneClass& end) { }

void Visitor::visitEndCloneInstance_CloneClass(const CloneInstance& begin, const CloneClass& end) { }

void Visitor::visitDataClumpsClass_Items(const DataClumpsClass& begin, const DataClumps& end) { }

void Visitor::visitEndDataClumpsClass_Items(const DataClumpsClass& begin, const DataClumps& end) { }

void Visitor::visitDataClumps_DataClumpsClass(const DataClumps& begin, const DataClumpsClass& end) { }

void Visitor::visitEndDataClumps_DataClumpsClass(const DataClumps& begin, const DataClumpsClass& end) { }

void Visitor::visitDataClumps_Items(const DataClumps& begin, const DataElement& end) { }

void Visitor::visitEndDataClumps_Items(const DataClumps& begin, const DataElement& end) { }

void Visitor::visitDataElement_Component(const DataElement& begin, const Component& end) { }

void Visitor::visitEndDataElement_Component(const DataElement& begin, const Component& end) { }

void Visitor::visitSwitchStatementClass_Items(const SwitchStatementClass& begin, const SwitchStatement& end) { }

void Visitor::visitEndSwitchStatementClass_Items(const SwitchStatementClass& begin, const SwitchStatement& end) { }

void Visitor::visitSwitchStatement_SwitchStatementClass(const SwitchStatement& begin, const SwitchStatementClass& end) { }

void Visitor::visitEndSwitchStatement_SwitchStatementClass(const SwitchStatement& begin, const SwitchStatementClass& end) { }

void Visitor::visitSwitchStatement_Items(const SwitchStatement& begin, const CaseLabel& end) { }

void Visitor::visitEndSwitchStatement_Items(const SwitchStatement& begin, const CaseLabel& end) { }

void Visitor::visitCaseLabel_Component(const CaseLabel& begin, const Component& end) { }

void Visitor::visitEndCaseLabel_Component(const CaseLabel& begin, const Component& end) { }


}}
