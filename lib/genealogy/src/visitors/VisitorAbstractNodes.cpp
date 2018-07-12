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

#include "genealogy/inc/genealogy.h"


namespace columbus { namespace genealogy { 
VisitorAbstractNodes::~VisitorAbstractNodes() { }

void VisitorAbstractNodes::visit   (const Base& node , bool callVirtualBase) { }
void VisitorAbstractNodes::visitEnd(const Base& node , bool callVirtualBase) { }

void VisitorAbstractNodes::visit(const Project& node , bool callVirtualBase) {
  visit   ((Base&)node,false); 
}

void VisitorAbstractNodes::visitEnd(const Project& node , bool callVirtualBase) {
  visitEnd   ((Base&)node,false); 
}

void VisitorAbstractNodes::visit(const Trackable& node , bool callVirtualBase) {
  visit   ((Base&)node,false); 
}

void VisitorAbstractNodes::visitEnd(const Trackable& node , bool callVirtualBase) {
  visitEnd   ((Base&)node,false); 
}

void VisitorAbstractNodes::visit(const Component& node , bool callVirtualBase) {
  visit   ((Base&)node,false); 
}

void VisitorAbstractNodes::visitEnd(const Component& node , bool callVirtualBase) {
  visitEnd   ((Base&)node,false); 
}

void VisitorAbstractNodes::visit(const SourceCodeElement& node , bool callVirtualBase) {
  visit   ((Base&)node,false); 
}

void VisitorAbstractNodes::visitEnd(const SourceCodeElement& node , bool callVirtualBase) {
  visitEnd   ((Base&)node,false); 
}

void VisitorAbstractNodes::visit(const System& node , bool callVirtualBase) {
  visit   ((Trackable&)node,false); 
}

void VisitorAbstractNodes::visitEnd(const System& node , bool callVirtualBase) {
  visitEnd   ((Trackable&)node,false); 
}

void VisitorAbstractNodes::visit(const Clone& node , bool callVirtualBase) {
  visit   ((Trackable&)node,false); 
}

void VisitorAbstractNodes::visitEnd(const Clone& node , bool callVirtualBase) {
  visitEnd   ((Trackable&)node,false); 
}

void VisitorAbstractNodes::visit(const StructuralClone& node , bool callVirtualBase) {
  visit   ((Trackable&)node,false); 
}

void VisitorAbstractNodes::visitEnd(const StructuralClone& node , bool callVirtualBase) {
  visitEnd   ((Trackable&)node,false); 
}

void VisitorAbstractNodes::visit(const CloneClass& node , bool callVirtualBase) {
  visit   ((Clone&)node,false); 
}

void VisitorAbstractNodes::visitEnd(const CloneClass& node , bool callVirtualBase) {
  visitEnd   ((Clone&)node,false); 
}

void VisitorAbstractNodes::visit(const CloneInstance& node , bool callVirtualBase) {
  visit   ((Clone&)node,false); 
}

void VisitorAbstractNodes::visitEnd(const CloneInstance& node , bool callVirtualBase) {
  visitEnd   ((Clone&)node,false); 
}

void VisitorAbstractNodes::visit(const DataClumpsClass& node , bool callVirtualBase) {
  visit   ((StructuralClone&)node,false); 
}

void VisitorAbstractNodes::visitEnd(const DataClumpsClass& node , bool callVirtualBase) {
  visitEnd   ((StructuralClone&)node,false); 
}

void VisitorAbstractNodes::visit(const DataClumps& node , bool callVirtualBase) {
  visit   ((StructuralClone&)node,false); 
}

void VisitorAbstractNodes::visitEnd(const DataClumps& node , bool callVirtualBase) {
  visitEnd   ((StructuralClone&)node,false); 
}

void VisitorAbstractNodes::visit(const DataElement& node , bool callVirtualBase) {
  visit   ((SourceCodeElement&)node,false); 
}

void VisitorAbstractNodes::visitEnd(const DataElement& node , bool callVirtualBase) {
  visitEnd   ((SourceCodeElement&)node,false); 
}

void VisitorAbstractNodes::visit(const SwitchStatementClass& node , bool callVirtualBase) {
  visit   ((StructuralClone&)node,false); 
}

void VisitorAbstractNodes::visitEnd(const SwitchStatementClass& node , bool callVirtualBase) {
  visitEnd   ((StructuralClone&)node,false); 
}

void VisitorAbstractNodes::visit(const SwitchStatement& node , bool callVirtualBase) {
  visit   ((StructuralClone&)node,false); 
}

void VisitorAbstractNodes::visitEnd(const SwitchStatement& node , bool callVirtualBase) {
  visitEnd   ((StructuralClone&)node,false); 
}

void VisitorAbstractNodes::visit(const CaseLabel& node , bool callVirtualBase) {
  visit   ((SourceCodeElement&)node,false); 
}

void VisitorAbstractNodes::visitEnd(const CaseLabel& node , bool callVirtualBase) {
  visitEnd   ((SourceCodeElement&)node,false); 
}


}}
