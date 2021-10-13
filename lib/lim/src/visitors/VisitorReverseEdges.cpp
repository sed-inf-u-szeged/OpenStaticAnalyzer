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
VisitorReverseEdges::VisitorReverseEdges(ReverseEdges *reverseEdges) : VisitorAbstractNodes(), revEdges(reverseEdges) {
}

VisitorReverseEdges::~VisitorReverseEdges() {
}

void VisitorReverseEdges::visit(const base::Base &node, bool callVirtualBase ) {
  NodeId id = node.getId();
  if (!revEdges->reContainer[id])
    revEdges->reContainer[id] = new ReverseEdges::NodeEdgesType();
}

void VisitorReverseEdges::visitComponent_CompilationUnit(const base::Component& begin, const physical::File& end) {
  revEdges->insertEdge(&end, &begin, edkComponent_CompilationUnit);
}

void VisitorReverseEdges::visitComponent_Contains(const base::Component& begin, const base::Component& end) {
  revEdges->insertEdge(&end, &begin, edkComponent_Contains);
}

void VisitorReverseEdges::visitComponent_HasFiles(const base::Component& begin, const physical::File& end) {
  revEdges->insertEdge(&end, &begin, edkComponent_HasFiles);
}

void VisitorReverseEdges::visitControlFlowBlock_Calls(const base::ControlFlowBlock& begin, const logical::Method& end) {
  revEdges->insertEdge(&end, &begin, edkControlFlowBlock_Calls);
}

void VisitorReverseEdges::visitControlFlowBlock_Pred(const base::ControlFlowBlock& begin, const base::ControlFlowBlock& end) {
  revEdges->insertEdge(&end, &begin, edkControlFlowBlock_Pred);
}

void VisitorReverseEdges::visitNamed_DependsOn(const base::Named& begin, const base::Named& end, const std::string& ac) {
  revEdges->insertEdge(&end, &begin, edkNamed_DependsOn);
}

void VisitorReverseEdges::visitAttribute_Calls(const logical::Attribute& begin, const logical::MethodCall& end) {
  revEdges->insertEdge(&end, &begin, edkAttribute_Calls);
}

void VisitorReverseEdges::visitAttribute_HasType(const logical::Attribute& begin, const type::Type& end) {
  revEdges->insertEdge(&end, &begin, edkAttribute_HasType);
}

void VisitorReverseEdges::visitAttributeAccess_Attribute(const logical::AttributeAccess& begin, const logical::Attribute& end) {
  revEdges->insertEdge(&end, &begin, edkAttributeAccess_Attribute);
}

void VisitorReverseEdges::visitClass_Extends(const logical::Class& begin, const logical::Class& end) {
  revEdges->insertEdge(&end, &begin, edkClass_Extends);
}

void VisitorReverseEdges::visitClass_GrantsFriendship(const logical::Class& begin, const logical::Friendship& end) {
  revEdges->insertEdge(&end, &begin, edkClass_GrantsFriendship);
}

void VisitorReverseEdges::visitClass_IsSubclass(const logical::Class& begin, const type::Type& end) {
  revEdges->insertEdge(&end, &begin, edkClass_IsSubclass);
}

void VisitorReverseEdges::visitClassGeneric_HasGenericParameter(const logical::ClassGeneric& begin, const logical::GenericParameter& end) {
  revEdges->insertEdge(&end, &begin, edkClassGeneric_HasGenericParameter);
}

void VisitorReverseEdges::visitClassGenericInstance_HasArguments(const logical::ClassGenericInstance& begin, const type::Type& end, TypeArgumentConstraintKind ac) {
  revEdges->insertEdge(&end, &begin, edkClassGenericInstance_HasArguments);
}

void VisitorReverseEdges::visitClassGenericSpec_HasArguments(const logical::ClassGenericSpec& begin, const type::Type& end, TypeArgumentConstraintKind ac) {
  revEdges->insertEdge(&end, &begin, edkClassGenericSpec_HasArguments);
}

void VisitorReverseEdges::visitClassGenericSpec_Specialize(const logical::ClassGenericSpec& begin, const logical::ClassGeneric& end) {
  revEdges->insertEdge(&end, &begin, edkClassGenericSpec_Specialize);
}

void VisitorReverseEdges::visitFriendship_Friend(const logical::Friendship& begin, const logical::Scope& end) {
  revEdges->insertEdge(&end, &begin, edkFriendship_Friend);
}

void VisitorReverseEdges::visitGenericParameter_HasParameterConstraint(const logical::GenericParameter& begin, const type::Type& end) {
  revEdges->insertEdge(&end, &begin, edkGenericParameter_HasParameterConstraint);
}

void VisitorReverseEdges::visitMember_Aggregated(const logical::Member& begin, const logical::Member& end) {
  revEdges->insertEdge(&end, &begin, edkMember_Aggregated);
}

void VisitorReverseEdges::visitMember_BelongsTo(const logical::Member& begin, const base::Component& end) {
  revEdges->insertEdge(&end, &begin, edkMember_BelongsTo);
}

void VisitorReverseEdges::visitMember_CompilationUnit(const logical::Member& begin, const physical::File& end) {
  revEdges->insertEdge(&end, &begin, edkMember_CompilationUnit);
}

void VisitorReverseEdges::visitMember_Declares(const logical::Member& begin, const logical::Member& end) {
  revEdges->insertEdge(&end, &begin, edkMember_Declares);
}

void VisitorReverseEdges::visitMember_HasComment(const logical::Member& begin, const base::Comment& end) {
  revEdges->insertEdge(&end, &begin, edkMember_HasComment);
}

void VisitorReverseEdges::visitMember_Instance(const logical::Member& begin, const logical::Member& end) {
  revEdges->insertEdge(&end, &begin, edkMember_Instance);
}

void VisitorReverseEdges::visitMember_IsContainedIn(const logical::Member& begin, const physical::File& end, const SourcePosition& ac) {
  revEdges->insertEdge(&end, &begin, edkMember_IsContainedIn);
}

void VisitorReverseEdges::visitMember_LanguageVariant(const logical::Member& begin, const logical::Member& end) {
  revEdges->insertEdge(&end, &begin, edkMember_LanguageVariant);
}

void VisitorReverseEdges::visitMember_Uses(const logical::Member& begin, const type::Type& end) {
  revEdges->insertEdge(&end, &begin, edkMember_Uses);
}

void VisitorReverseEdges::visitMember_Variant(const logical::Member& begin, const logical::Member& end) {
  revEdges->insertEdge(&end, &begin, edkMember_Variant);
}

void VisitorReverseEdges::visitMethod_AccessesAttribute(const logical::Method& begin, const logical::AttributeAccess& end) {
  revEdges->insertEdge(&end, &begin, edkMethod_AccessesAttribute);
}

void VisitorReverseEdges::visitMethod_Calls(const logical::Method& begin, const logical::MethodCall& end) {
  revEdges->insertEdge(&end, &begin, edkMethod_Calls);
}

void VisitorReverseEdges::visitMethod_CanThrow(const logical::Method& begin, const type::Type& end) {
  revEdges->insertEdge(&end, &begin, edkMethod_CanThrow);
}

void VisitorReverseEdges::visitMethod_HasControlFlowBlock(const logical::Method& begin, const base::ControlFlowBlock& end) {
  revEdges->insertEdge(&end, &begin, edkMethod_HasControlFlowBlock);
}

void VisitorReverseEdges::visitMethod_HasParameter(const logical::Method& begin, const logical::Parameter& end) {
  revEdges->insertEdge(&end, &begin, edkMethod_HasParameter);
}

void VisitorReverseEdges::visitMethod_Instantiates(const logical::Method& begin, const type::Type& end) {
  revEdges->insertEdge(&end, &begin, edkMethod_Instantiates);
}

void VisitorReverseEdges::visitMethod_Returns(const logical::Method& begin, const type::Type& end) {
  revEdges->insertEdge(&end, &begin, edkMethod_Returns);
}

void VisitorReverseEdges::visitMethod_Throws(const logical::Method& begin, const type::Type& end) {
  revEdges->insertEdge(&end, &begin, edkMethod_Throws);
}

void VisitorReverseEdges::visitMethodCall_Method(const logical::MethodCall& begin, const logical::Method& end) {
  revEdges->insertEdge(&end, &begin, edkMethodCall_Method);
}

void VisitorReverseEdges::visitMethodGeneric_HasGenericParameter(const logical::MethodGeneric& begin, const logical::GenericParameter& end) {
  revEdges->insertEdge(&end, &begin, edkMethodGeneric_HasGenericParameter);
}

void VisitorReverseEdges::visitMethodGenericInstance_HasArguments(const logical::MethodGenericInstance& begin, const type::Type& end, TypeArgumentConstraintKind ac) {
  revEdges->insertEdge(&end, &begin, edkMethodGenericInstance_HasArguments);
}

void VisitorReverseEdges::visitMethodGenericSpec_HasArguments(const logical::MethodGenericSpec& begin, const type::Type& end, TypeArgumentConstraintKind ac) {
  revEdges->insertEdge(&end, &begin, edkMethodGenericSpec_HasArguments);
}

void VisitorReverseEdges::visitMethodGenericSpec_Specialize(const logical::MethodGenericSpec& begin, const logical::MethodGeneric& end) {
  revEdges->insertEdge(&end, &begin, edkMethodGenericSpec_Specialize);
}

void VisitorReverseEdges::visitParameter_HasType(const logical::Parameter& begin, const type::Type& end) {
  revEdges->insertEdge(&end, &begin, edkParameter_HasType);
}

void VisitorReverseEdges::visitScope_HasMember(const logical::Scope& begin, const logical::Member& end) {
  revEdges->insertEdge(&end, &begin, edkScope_HasMember);
}

void VisitorReverseEdges::visitFile_HasComment(const physical::File& begin, const base::Comment& end) {
  revEdges->insertEdge(&end, &begin, edkFile_HasComment);
}

void VisitorReverseEdges::visitFile_Includes(const physical::File& begin, const physical::File& end) {
  revEdges->insertEdge(&end, &begin, edkFile_Includes);
}

void VisitorReverseEdges::visitFileSystem_HasFSEntry(const physical::FileSystem& begin, const physical::FSEntry& end) {
  revEdges->insertEdge(&end, &begin, edkFileSystem_HasFSEntry);
}

void VisitorReverseEdges::visitFolder_Contains(const physical::Folder& begin, const physical::FSEntry& end) {
  revEdges->insertEdge(&end, &begin, edkFolder_Contains);
}

void VisitorReverseEdges::visitType_HasTypeFormer(const type::Type& begin, const type::TypeFormer& end) {
  revEdges->insertEdge(&end, &begin, edkType_HasTypeFormer);
}

void VisitorReverseEdges::visitTypeFormerMethod_HasParameterType(const type::TypeFormerMethod& begin, const type::Type& end, ParameterKind ac) {
  revEdges->insertEdge(&end, &begin, edkTypeFormerMethod_HasParameterType);
}

void VisitorReverseEdges::visitTypeFormerMethod_HasReturnType(const type::TypeFormerMethod& begin, const type::Type& end) {
  revEdges->insertEdge(&end, &begin, edkTypeFormerMethod_HasReturnType);
}

void VisitorReverseEdges::visitTypeFormerType_RefersTo(const type::TypeFormerType& begin, const base::Base& end) {
  revEdges->insertEdge(&end, &begin, edkTypeFormerType_RefersTo);
}


}}}
