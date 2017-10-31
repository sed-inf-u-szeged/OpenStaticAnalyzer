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


namespace columbus { namespace lim { namespace asg {
VisitorAbstractNodes::~VisitorAbstractNodes() { }

void VisitorAbstractNodes::visit   (const base::Base& node , bool callVirtualBase) { }
void VisitorAbstractNodes::visitEnd(const base::Base& node , bool callVirtualBase) { }

void VisitorAbstractNodes::visit(const base::Comment& node , bool callVirtualBase) {
  visit   ((base::Base&)node,false); 
}

void VisitorAbstractNodes::visitEnd(const base::Comment& node , bool callVirtualBase) {
  visitEnd   ((base::Base&)node,false); 
}

void VisitorAbstractNodes::visit(const base::Component& node , bool callVirtualBase) {
  visit   ((base::Named&)node,false); 
}

void VisitorAbstractNodes::visitEnd(const base::Component& node , bool callVirtualBase) {
  visitEnd   ((base::Named&)node,false); 
}

void VisitorAbstractNodes::visit(const base::ControlFlowBlock& node , bool callVirtualBase) {
  visit   ((base::Base&)node,false); 
}

void VisitorAbstractNodes::visitEnd(const base::ControlFlowBlock& node , bool callVirtualBase) {
  visitEnd   ((base::Base&)node,false); 
}

void VisitorAbstractNodes::visit(const base::Named& node , bool callVirtualBase) {
  visit   ((base::Base&)node,false); 
}

void VisitorAbstractNodes::visitEnd(const base::Named& node , bool callVirtualBase) {
  visitEnd   ((base::Base&)node,false); 
}

void VisitorAbstractNodes::visit(const logical::Attribute& node , bool callVirtualBase) {
  visit   ((logical::Member&)node,false); 
}

void VisitorAbstractNodes::visitEnd(const logical::Attribute& node , bool callVirtualBase) {
  visitEnd   ((logical::Member&)node,false); 
}

void VisitorAbstractNodes::visit(const logical::AttributeAccess& node , bool callVirtualBase) {
  visit   ((base::Base&)node,false); 
}

void VisitorAbstractNodes::visitEnd(const logical::AttributeAccess& node , bool callVirtualBase) {
  visitEnd   ((base::Base&)node,false); 
}

void VisitorAbstractNodes::visit(const logical::Class& node , bool callVirtualBase) {
  visit   ((logical::Scope&)node,false); 
}

void VisitorAbstractNodes::visitEnd(const logical::Class& node , bool callVirtualBase) {
  visitEnd   ((logical::Scope&)node,false); 
}

void VisitorAbstractNodes::visit(const logical::ClassGeneric& node , bool callVirtualBase) {
  visit   ((logical::Class&)node,false); 
}

void VisitorAbstractNodes::visitEnd(const logical::ClassGeneric& node , bool callVirtualBase) {
  visitEnd   ((logical::Class&)node,false); 
}

void VisitorAbstractNodes::visit(const logical::ClassGenericInstance& node , bool callVirtualBase) {
  visit   ((logical::Class&)node,false); 
}

void VisitorAbstractNodes::visitEnd(const logical::ClassGenericInstance& node , bool callVirtualBase) {
  visitEnd   ((logical::Class&)node,false); 
}

void VisitorAbstractNodes::visit(const logical::ClassGenericSpec& node , bool callVirtualBase) {
  visit   ((logical::ClassGeneric&)node,false); 
}

void VisitorAbstractNodes::visitEnd(const logical::ClassGenericSpec& node , bool callVirtualBase) {
  visitEnd   ((logical::ClassGeneric&)node,false); 
}

void VisitorAbstractNodes::visit(const logical::Friendship& node , bool callVirtualBase) {
  visit   ((base::Base&)node,false); 
}

void VisitorAbstractNodes::visitEnd(const logical::Friendship& node , bool callVirtualBase) {
  visitEnd   ((base::Base&)node,false); 
}

void VisitorAbstractNodes::visit(const logical::GenericParameter& node , bool callVirtualBase) {
  visit   ((base::Named&)node,false); 
}

void VisitorAbstractNodes::visitEnd(const logical::GenericParameter& node , bool callVirtualBase) {
  visitEnd   ((base::Named&)node,false); 
}

void VisitorAbstractNodes::visit(const logical::Member& node , bool callVirtualBase) {
  visit   ((base::Named&)node,false); 
}

void VisitorAbstractNodes::visitEnd(const logical::Member& node , bool callVirtualBase) {
  visitEnd   ((base::Named&)node,false); 
}

void VisitorAbstractNodes::visit(const logical::Method& node , bool callVirtualBase) {
  visit   ((logical::Scope&)node,false); 
}

void VisitorAbstractNodes::visitEnd(const logical::Method& node , bool callVirtualBase) {
  visitEnd   ((logical::Scope&)node,false); 
}

void VisitorAbstractNodes::visit(const logical::MethodCall& node , bool callVirtualBase) {
  visit   ((base::Base&)node,false); 
}

void VisitorAbstractNodes::visitEnd(const logical::MethodCall& node , bool callVirtualBase) {
  visitEnd   ((base::Base&)node,false); 
}

void VisitorAbstractNodes::visit(const logical::MethodGeneric& node , bool callVirtualBase) {
  visit   ((logical::Method&)node,false); 
}

void VisitorAbstractNodes::visitEnd(const logical::MethodGeneric& node , bool callVirtualBase) {
  visitEnd   ((logical::Method&)node,false); 
}

void VisitorAbstractNodes::visit(const logical::MethodGenericInstance& node , bool callVirtualBase) {
  visit   ((logical::Method&)node,false); 
}

void VisitorAbstractNodes::visitEnd(const logical::MethodGenericInstance& node , bool callVirtualBase) {
  visitEnd   ((logical::Method&)node,false); 
}

void VisitorAbstractNodes::visit(const logical::MethodGenericSpec& node , bool callVirtualBase) {
  visit   ((logical::MethodGeneric&)node,false); 
}

void VisitorAbstractNodes::visitEnd(const logical::MethodGenericSpec& node , bool callVirtualBase) {
  visitEnd   ((logical::MethodGeneric&)node,false); 
}

void VisitorAbstractNodes::visit(const logical::Package& node , bool callVirtualBase) {
  visit   ((logical::Scope&)node,false); 
}

void VisitorAbstractNodes::visitEnd(const logical::Package& node , bool callVirtualBase) {
  visitEnd   ((logical::Scope&)node,false); 
}

void VisitorAbstractNodes::visit(const logical::Parameter& node , bool callVirtualBase) {
  visit   ((base::Named&)node,false); 
}

void VisitorAbstractNodes::visitEnd(const logical::Parameter& node , bool callVirtualBase) {
  visitEnd   ((base::Named&)node,false); 
}

void VisitorAbstractNodes::visit(const logical::Scope& node , bool callVirtualBase) {
  visit   ((logical::Member&)node,false); 
}

void VisitorAbstractNodes::visitEnd(const logical::Scope& node , bool callVirtualBase) {
  visitEnd   ((logical::Member&)node,false); 
}

void VisitorAbstractNodes::visit(const physical::FSEntry& node , bool callVirtualBase) {
  visit   ((base::Named&)node,false); 
}

void VisitorAbstractNodes::visitEnd(const physical::FSEntry& node , bool callVirtualBase) {
  visitEnd   ((base::Named&)node,false); 
}

void VisitorAbstractNodes::visit(const physical::File& node , bool callVirtualBase) {
  visit   ((physical::FSEntry&)node,false); 
}

void VisitorAbstractNodes::visitEnd(const physical::File& node , bool callVirtualBase) {
  visitEnd   ((physical::FSEntry&)node,false); 
}

void VisitorAbstractNodes::visit(const physical::FileSystem& node , bool callVirtualBase) {
  visit   ((base::Named&)node,false); 
}

void VisitorAbstractNodes::visitEnd(const physical::FileSystem& node , bool callVirtualBase) {
  visitEnd   ((base::Named&)node,false); 
}

void VisitorAbstractNodes::visit(const physical::Folder& node , bool callVirtualBase) {
  visit   ((physical::FSEntry&)node,false); 
}

void VisitorAbstractNodes::visitEnd(const physical::Folder& node , bool callVirtualBase) {
  visitEnd   ((physical::FSEntry&)node,false); 
}

void VisitorAbstractNodes::visit(const type::SimpleType& node , bool callVirtualBase) {
  visit   ((base::Base&)node,false); 
}

void VisitorAbstractNodes::visitEnd(const type::SimpleType& node , bool callVirtualBase) {
  visitEnd   ((base::Base&)node,false); 
}

void VisitorAbstractNodes::visit(const type::Type& node , bool callVirtualBase) {
  visit   ((base::Base&)node,false); 
}

void VisitorAbstractNodes::visitEnd(const type::Type& node , bool callVirtualBase) {
  visitEnd   ((base::Base&)node,false); 
}

void VisitorAbstractNodes::visit(const type::TypeFormer& node , bool callVirtualBase) {
  visit   ((base::Base&)node,false); 
}

void VisitorAbstractNodes::visitEnd(const type::TypeFormer& node , bool callVirtualBase) {
  visitEnd   ((base::Base&)node,false); 
}

void VisitorAbstractNodes::visit(const type::TypeFormerArray& node , bool callVirtualBase) {
  visit   ((type::TypeFormer&)node,false); 
}

void VisitorAbstractNodes::visitEnd(const type::TypeFormerArray& node , bool callVirtualBase) {
  visitEnd   ((type::TypeFormer&)node,false); 
}

void VisitorAbstractNodes::visit(const type::TypeFormerMethod& node , bool callVirtualBase) {
  visit   ((type::TypeFormer&)node,false); 
}

void VisitorAbstractNodes::visitEnd(const type::TypeFormerMethod& node , bool callVirtualBase) {
  visitEnd   ((type::TypeFormer&)node,false); 
}

void VisitorAbstractNodes::visit(const type::TypeFormerNonType& node , bool callVirtualBase) {
  visit   ((type::TypeFormer&)node,false); 
}

void VisitorAbstractNodes::visitEnd(const type::TypeFormerNonType& node , bool callVirtualBase) {
  visitEnd   ((type::TypeFormer&)node,false); 
}

void VisitorAbstractNodes::visit(const type::TypeFormerPointer& node , bool callVirtualBase) {
  visit   ((type::TypeFormer&)node,false); 
}

void VisitorAbstractNodes::visitEnd(const type::TypeFormerPointer& node , bool callVirtualBase) {
  visitEnd   ((type::TypeFormer&)node,false); 
}

void VisitorAbstractNodes::visit(const type::TypeFormerType& node , bool callVirtualBase) {
  visit   ((type::TypeFormer&)node,false); 
}

void VisitorAbstractNodes::visitEnd(const type::TypeFormerType& node , bool callVirtualBase) {
  visitEnd   ((type::TypeFormer&)node,false); 
}


}}}
