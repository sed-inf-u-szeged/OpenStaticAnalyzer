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


namespace columbus { namespace lim { namespace asg {
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

void Visitor::visit(const base::Comment& node , bool callVirtualBase) {}

void Visitor::visitEnd(const base::Comment& node , bool callVirtualBase) { }

void Visitor::visit(const base::Component& node , bool callVirtualBase) {}

void Visitor::visitEnd(const base::Component& node , bool callVirtualBase) { }

void Visitor::visit(const base::ControlFlowBlock& node , bool callVirtualBase) {}

void Visitor::visitEnd(const base::ControlFlowBlock& node , bool callVirtualBase) { }

void Visitor::visit(const logical::Attribute& node , bool callVirtualBase) {}

void Visitor::visitEnd(const logical::Attribute& node , bool callVirtualBase) { }

void Visitor::visit(const logical::AttributeAccess& node , bool callVirtualBase) {}

void Visitor::visitEnd(const logical::AttributeAccess& node , bool callVirtualBase) { }

void Visitor::visit(const logical::Class& node , bool callVirtualBase) {}

void Visitor::visitEnd(const logical::Class& node , bool callVirtualBase) { }

void Visitor::visit(const logical::ClassGeneric& node , bool callVirtualBase) {}

void Visitor::visitEnd(const logical::ClassGeneric& node , bool callVirtualBase) { }

void Visitor::visit(const logical::ClassGenericInstance& node , bool callVirtualBase) {}

void Visitor::visitEnd(const logical::ClassGenericInstance& node , bool callVirtualBase) { }

void Visitor::visit(const logical::ClassGenericSpec& node , bool callVirtualBase) {}

void Visitor::visitEnd(const logical::ClassGenericSpec& node , bool callVirtualBase) { }

void Visitor::visit(const logical::Friendship& node , bool callVirtualBase) {}

void Visitor::visitEnd(const logical::Friendship& node , bool callVirtualBase) { }

void Visitor::visit(const logical::GenericParameter& node , bool callVirtualBase) {}

void Visitor::visitEnd(const logical::GenericParameter& node , bool callVirtualBase) { }

void Visitor::visit(const logical::Method& node , bool callVirtualBase) {}

void Visitor::visitEnd(const logical::Method& node , bool callVirtualBase) { }

void Visitor::visit(const logical::MethodCall& node , bool callVirtualBase) {}

void Visitor::visitEnd(const logical::MethodCall& node , bool callVirtualBase) { }

void Visitor::visit(const logical::MethodGeneric& node , bool callVirtualBase) {}

void Visitor::visitEnd(const logical::MethodGeneric& node , bool callVirtualBase) { }

void Visitor::visit(const logical::MethodGenericInstance& node , bool callVirtualBase) {}

void Visitor::visitEnd(const logical::MethodGenericInstance& node , bool callVirtualBase) { }

void Visitor::visit(const logical::MethodGenericSpec& node , bool callVirtualBase) {}

void Visitor::visitEnd(const logical::MethodGenericSpec& node , bool callVirtualBase) { }

void Visitor::visit(const logical::Package& node , bool callVirtualBase) {}

void Visitor::visitEnd(const logical::Package& node , bool callVirtualBase) { }

void Visitor::visit(const logical::Parameter& node , bool callVirtualBase) {}

void Visitor::visitEnd(const logical::Parameter& node , bool callVirtualBase) { }

void Visitor::visit(const physical::File& node , bool callVirtualBase) {}

void Visitor::visitEnd(const physical::File& node , bool callVirtualBase) { }

void Visitor::visit(const physical::FileSystem& node , bool callVirtualBase) {}

void Visitor::visitEnd(const physical::FileSystem& node , bool callVirtualBase) { }

void Visitor::visit(const physical::Folder& node , bool callVirtualBase) {}

void Visitor::visitEnd(const physical::Folder& node , bool callVirtualBase) { }

void Visitor::visit(const type::SimpleType& node , bool callVirtualBase) {}

void Visitor::visitEnd(const type::SimpleType& node , bool callVirtualBase) { }

void Visitor::visit(const type::Type& node , bool callVirtualBase) {}

void Visitor::visitEnd(const type::Type& node , bool callVirtualBase) { }

void Visitor::visit(const type::TypeFormerArray& node , bool callVirtualBase) {}

void Visitor::visitEnd(const type::TypeFormerArray& node , bool callVirtualBase) { }

void Visitor::visit(const type::TypeFormerMethod& node , bool callVirtualBase) {}

void Visitor::visitEnd(const type::TypeFormerMethod& node , bool callVirtualBase) { }

void Visitor::visit(const type::TypeFormerNonType& node , bool callVirtualBase) {}

void Visitor::visitEnd(const type::TypeFormerNonType& node , bool callVirtualBase) { }

void Visitor::visit(const type::TypeFormerPointer& node , bool callVirtualBase) {}

void Visitor::visitEnd(const type::TypeFormerPointer& node , bool callVirtualBase) { }

void Visitor::visit(const type::TypeFormerType& node , bool callVirtualBase) {}

void Visitor::visitEnd(const type::TypeFormerType& node , bool callVirtualBase) { }

void Visitor::visitComponent_Contains(const base::Component& begin, const base::Component& end) { }

void Visitor::visitEndComponent_Contains(const base::Component& begin, const base::Component& end) { }

void Visitor::visitComponent_HasFiles(const base::Component& begin, const physical::File& end) { }

void Visitor::visitEndComponent_HasFiles(const base::Component& begin, const physical::File& end) { }

void Visitor::visitControlFlowBlock_Calls(const base::ControlFlowBlock& begin, const logical::Method& end) { }

void Visitor::visitEndControlFlowBlock_Calls(const base::ControlFlowBlock& begin, const logical::Method& end) { }

void Visitor::visitControlFlowBlock_Pred(const base::ControlFlowBlock& begin, const base::ControlFlowBlock& end) { }

void Visitor::visitEndControlFlowBlock_Pred(const base::ControlFlowBlock& begin, const base::ControlFlowBlock& end) { }

void Visitor::visitNamed_DependsOn(const base::Named& begin, const base::Named& end, const std::string& ac) { }

void Visitor::visitEndNamed_DependsOn(const base::Named& begin, const base::Named& end, const std::string& ac) { }

void Visitor::visitAttribute_Calls(const logical::Attribute& begin, const logical::MethodCall& end) { }

void Visitor::visitEndAttribute_Calls(const logical::Attribute& begin, const logical::MethodCall& end) { }

void Visitor::visitAttribute_HasType(const logical::Attribute& begin, const type::Type& end) { }

void Visitor::visitEndAttribute_HasType(const logical::Attribute& begin, const type::Type& end) { }

void Visitor::visitAttributeAccess_Attribute(const logical::AttributeAccess& begin, const logical::Attribute& end) { }

void Visitor::visitEndAttributeAccess_Attribute(const logical::AttributeAccess& begin, const logical::Attribute& end) { }

void Visitor::visitClass_GrantsFriendship(const logical::Class& begin, const logical::Friendship& end) { }

void Visitor::visitEndClass_GrantsFriendship(const logical::Class& begin, const logical::Friendship& end) { }

void Visitor::visitClass_IsSubclass(const logical::Class& begin, const type::Type& end) { }

void Visitor::visitEndClass_IsSubclass(const logical::Class& begin, const type::Type& end) { }

void Visitor::visitClassGeneric_HasGenericParameter(const logical::ClassGeneric& begin, const logical::GenericParameter& end) { }

void Visitor::visitEndClassGeneric_HasGenericParameter(const logical::ClassGeneric& begin, const logical::GenericParameter& end) { }

void Visitor::visitClassGenericInstance_HasArguments(const logical::ClassGenericInstance& begin, const type::Type& end, TypeArgumentConstraintKind ac) { }

void Visitor::visitEndClassGenericInstance_HasArguments(const logical::ClassGenericInstance& begin, const type::Type& end, TypeArgumentConstraintKind ac) { }

void Visitor::visitClassGenericSpec_HasArguments(const logical::ClassGenericSpec& begin, const type::Type& end, TypeArgumentConstraintKind ac) { }

void Visitor::visitEndClassGenericSpec_HasArguments(const logical::ClassGenericSpec& begin, const type::Type& end, TypeArgumentConstraintKind ac) { }

void Visitor::visitClassGenericSpec_Specialize(const logical::ClassGenericSpec& begin, const logical::ClassGeneric& end) { }

void Visitor::visitEndClassGenericSpec_Specialize(const logical::ClassGenericSpec& begin, const logical::ClassGeneric& end) { }

void Visitor::visitFriendship_Friend(const logical::Friendship& begin, const logical::Scope& end) { }

void Visitor::visitEndFriendship_Friend(const logical::Friendship& begin, const logical::Scope& end) { }

void Visitor::visitGenericParameter_HasParameterConstraint(const logical::GenericParameter& begin, const type::Type& end) { }

void Visitor::visitEndGenericParameter_HasParameterConstraint(const logical::GenericParameter& begin, const type::Type& end) { }

void Visitor::visitMember_Aggregated(const logical::Member& begin, const logical::Member& end) { }

void Visitor::visitEndMember_Aggregated(const logical::Member& begin, const logical::Member& end) { }

void Visitor::visitMember_BelongsTo(const logical::Member& begin, const base::Component& end) { }

void Visitor::visitEndMember_BelongsTo(const logical::Member& begin, const base::Component& end) { }

void Visitor::visitMember_CompilationUnit(const logical::Member& begin, const physical::File& end) { }

void Visitor::visitEndMember_CompilationUnit(const logical::Member& begin, const physical::File& end) { }

void Visitor::visitMember_Declares(const logical::Member& begin, const logical::Member& end) { }

void Visitor::visitEndMember_Declares(const logical::Member& begin, const logical::Member& end) { }

void Visitor::visitMember_HasComment(const logical::Member& begin, const base::Comment& end) { }

void Visitor::visitEndMember_HasComment(const logical::Member& begin, const base::Comment& end) { }

void Visitor::visitMember_Instance(const logical::Member& begin, const logical::Member& end) { }

void Visitor::visitEndMember_Instance(const logical::Member& begin, const logical::Member& end) { }

void Visitor::visitMember_IsContainedIn(const logical::Member& begin, const physical::File& end, const SourcePosition& ac) { }

void Visitor::visitEndMember_IsContainedIn(const logical::Member& begin, const physical::File& end, const SourcePosition& ac) { }

void Visitor::visitMember_LanguageVariant(const logical::Member& begin, const logical::Member& end) { }

void Visitor::visitEndMember_LanguageVariant(const logical::Member& begin, const logical::Member& end) { }

void Visitor::visitMember_Uses(const logical::Member& begin, const type::Type& end) { }

void Visitor::visitEndMember_Uses(const logical::Member& begin, const type::Type& end) { }

void Visitor::visitMember_Variant(const logical::Member& begin, const logical::Member& end) { }

void Visitor::visitEndMember_Variant(const logical::Member& begin, const logical::Member& end) { }

void Visitor::visitMethod_AccessesAttribute(const logical::Method& begin, const logical::AttributeAccess& end) { }

void Visitor::visitEndMethod_AccessesAttribute(const logical::Method& begin, const logical::AttributeAccess& end) { }

void Visitor::visitMethod_Calls(const logical::Method& begin, const logical::MethodCall& end) { }

void Visitor::visitEndMethod_Calls(const logical::Method& begin, const logical::MethodCall& end) { }

void Visitor::visitMethod_CanThrow(const logical::Method& begin, const type::Type& end) { }

void Visitor::visitEndMethod_CanThrow(const logical::Method& begin, const type::Type& end) { }

void Visitor::visitMethod_HasControlFlowBlock(const logical::Method& begin, const base::ControlFlowBlock& end) { }

void Visitor::visitEndMethod_HasControlFlowBlock(const logical::Method& begin, const base::ControlFlowBlock& end) { }

void Visitor::visitMethod_HasParameter(const logical::Method& begin, const logical::Parameter& end) { }

void Visitor::visitEndMethod_HasParameter(const logical::Method& begin, const logical::Parameter& end) { }

void Visitor::visitMethod_Instantiates(const logical::Method& begin, const type::Type& end) { }

void Visitor::visitEndMethod_Instantiates(const logical::Method& begin, const type::Type& end) { }

void Visitor::visitMethod_Returns(const logical::Method& begin, const type::Type& end) { }

void Visitor::visitEndMethod_Returns(const logical::Method& begin, const type::Type& end) { }

void Visitor::visitMethod_Throws(const logical::Method& begin, const type::Type& end) { }

void Visitor::visitEndMethod_Throws(const logical::Method& begin, const type::Type& end) { }

void Visitor::visitMethodCall_Method(const logical::MethodCall& begin, const logical::Method& end) { }

void Visitor::visitEndMethodCall_Method(const logical::MethodCall& begin, const logical::Method& end) { }

void Visitor::visitMethodGeneric_HasGenericParameter(const logical::MethodGeneric& begin, const logical::GenericParameter& end) { }

void Visitor::visitEndMethodGeneric_HasGenericParameter(const logical::MethodGeneric& begin, const logical::GenericParameter& end) { }

void Visitor::visitMethodGenericInstance_HasArguments(const logical::MethodGenericInstance& begin, const type::Type& end, TypeArgumentConstraintKind ac) { }

void Visitor::visitEndMethodGenericInstance_HasArguments(const logical::MethodGenericInstance& begin, const type::Type& end, TypeArgumentConstraintKind ac) { }

void Visitor::visitMethodGenericSpec_HasArguments(const logical::MethodGenericSpec& begin, const type::Type& end, TypeArgumentConstraintKind ac) { }

void Visitor::visitEndMethodGenericSpec_HasArguments(const logical::MethodGenericSpec& begin, const type::Type& end, TypeArgumentConstraintKind ac) { }

void Visitor::visitMethodGenericSpec_Specialize(const logical::MethodGenericSpec& begin, const logical::MethodGeneric& end) { }

void Visitor::visitEndMethodGenericSpec_Specialize(const logical::MethodGenericSpec& begin, const logical::MethodGeneric& end) { }

void Visitor::visitParameter_HasType(const logical::Parameter& begin, const type::Type& end) { }

void Visitor::visitEndParameter_HasType(const logical::Parameter& begin, const type::Type& end) { }

void Visitor::visitScope_HasMember(const logical::Scope& begin, const logical::Member& end) { }

void Visitor::visitEndScope_HasMember(const logical::Scope& begin, const logical::Member& end) { }

void Visitor::visitFile_HasComment(const physical::File& begin, const base::Comment& end) { }

void Visitor::visitEndFile_HasComment(const physical::File& begin, const base::Comment& end) { }

void Visitor::visitFile_Includes(const physical::File& begin, const physical::File& end) { }

void Visitor::visitEndFile_Includes(const physical::File& begin, const physical::File& end) { }

void Visitor::visitFileSystem_HasFSEntry(const physical::FileSystem& begin, const physical::FSEntry& end) { }

void Visitor::visitEndFileSystem_HasFSEntry(const physical::FileSystem& begin, const physical::FSEntry& end) { }

void Visitor::visitFolder_Contains(const physical::Folder& begin, const physical::FSEntry& end) { }

void Visitor::visitEndFolder_Contains(const physical::Folder& begin, const physical::FSEntry& end) { }

void Visitor::visitType_HasTypeFormer(const type::Type& begin, const type::TypeFormer& end) { }

void Visitor::visitEndType_HasTypeFormer(const type::Type& begin, const type::TypeFormer& end) { }

void Visitor::visitTypeFormerMethod_HasParameterType(const type::TypeFormerMethod& begin, const type::Type& end, ParameterKind ac) { }

void Visitor::visitEndTypeFormerMethod_HasParameterType(const type::TypeFormerMethod& begin, const type::Type& end, ParameterKind ac) { }

void Visitor::visitTypeFormerMethod_HasReturnType(const type::TypeFormerMethod& begin, const type::Type& end) { }

void Visitor::visitEndTypeFormerMethod_HasReturnType(const type::TypeFormerMethod& begin, const type::Type& end) { }

void Visitor::visitTypeFormerType_RefersTo(const type::TypeFormerType& begin, const base::Base& end) { }

void Visitor::visitEndTypeFormerType_RefersTo(const type::TypeFormerType& begin, const base::Base& end) { }


}}}
