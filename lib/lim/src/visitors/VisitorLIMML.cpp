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

using namespace std;


namespace columbus { namespace lim { namespace asg {
VisitorLIMML::VisitorLIMML(std::ofstream& targetStream,
                           const std::string& _projectName,
                           bool _noId,
                           bool _noLineInfo) : ofs(targetStream), noId(_noId), noLineInfo(_noLineInfo), projectName(_projectName)
{
}

VisitorLIMML::~VisitorLIMML() {
}

void VisitorLIMML::beginVisit() {
  ofs << "<?xml version='1.0' encoding=\"utf-8\"?>\n";
  ofs << "<Project name='" << projectName << "'"
      << " xmlns:base='columbus_lim_schema/base'"
      << " xmlns:logical='columbus_lim_schema/logical'"
      << " xmlns:physical='columbus_lim_schema/physical'"
      << " xmlns:type='columbus_lim_schema/type'"
      << ">\n";
}

void VisitorLIMML::finishVisit() {
  ofs << "<Filtered id='id1'/>\n";
  ofs << "</Project>\n";
}

void VisitorLIMML::visit(const base::Comment& node , bool callVirtualBase) {
  createIndentation();
  ofs << "<base:Comment";
  writeAttributes(node,false,true);
  ofs << "/>\n";

  writeAttributes(node,true,true);
}

void VisitorLIMML::visitEnd(const base::Comment& node , bool callVirtualBase) {
}

void VisitorLIMML::visit(const base::Component& node , bool callVirtualBase) {
  createIndentation();
  ofs << "<base:Component";
  writeAttributes(node,false,true);
  ofs << ">\n";

  writeAttributes(node,true,true);
}

void VisitorLIMML::visitEnd(const base::Component& node , bool callVirtualBase) {
  createIndentation();
  ofs << "</base:Component>\n";
}

void VisitorLIMML::visit(const base::ControlFlowBlock& node , bool callVirtualBase) {
  createIndentation();
  ofs << "<base:ControlFlowBlock";
  writeAttributes(node,false,true);
  ofs << ">\n";

  writeAttributes(node,true,true);
}

void VisitorLIMML::visitEnd(const base::ControlFlowBlock& node , bool callVirtualBase) {
  createIndentation();
  ofs << "</base:ControlFlowBlock>\n";
}

void VisitorLIMML::visit(const logical::Attribute& node , bool callVirtualBase) {
  createIndentation();
  ofs << "<logical:Attribute";
  writeAttributes(node,false,true);
  ofs << ">\n";

  writeAttributes(node,true,true);
}

void VisitorLIMML::visitEnd(const logical::Attribute& node , bool callVirtualBase) {
  createIndentation();
  ofs << "</logical:Attribute>\n";
}

void VisitorLIMML::visit(const logical::AttributeAccess& node , bool callVirtualBase) {
  createIndentation();
  ofs << "<logical:AttributeAccess";
  writeAttributes(node,false,true);
  ofs << ">\n";

  writeAttributes(node,true,true);
}

void VisitorLIMML::visitEnd(const logical::AttributeAccess& node , bool callVirtualBase) {
  createIndentation();
  ofs << "</logical:AttributeAccess>\n";
}

void VisitorLIMML::visit(const logical::Class& node , bool callVirtualBase) {
  createIndentation();
  ofs << "<logical:Class";
  writeAttributes(node,false,true);
  ofs << ">\n";

  writeAttributes(node,true,true);
}

void VisitorLIMML::visitEnd(const logical::Class& node , bool callVirtualBase) {
  createIndentation();
  ofs << "</logical:Class>\n";
}

void VisitorLIMML::visit(const logical::ClassGeneric& node , bool callVirtualBase) {
  createIndentation();
  ofs << "<logical:ClassGeneric";
  writeAttributes(node,false,true);
  ofs << ">\n";

  writeAttributes(node,true,true);
}

void VisitorLIMML::visitEnd(const logical::ClassGeneric& node , bool callVirtualBase) {
  createIndentation();
  ofs << "</logical:ClassGeneric>\n";
}

void VisitorLIMML::visit(const logical::ClassGenericInstance& node , bool callVirtualBase) {
  createIndentation();
  ofs << "<logical:ClassGenericInstance";
  writeAttributes(node,false,true);
  ofs << ">\n";

  writeAttributes(node,true,true);
}

void VisitorLIMML::visitEnd(const logical::ClassGenericInstance& node , bool callVirtualBase) {
  createIndentation();
  ofs << "</logical:ClassGenericInstance>\n";
}

void VisitorLIMML::visit(const logical::ClassGenericSpec& node , bool callVirtualBase) {
  createIndentation();
  ofs << "<logical:ClassGenericSpec";
  writeAttributes(node,false,true);
  ofs << ">\n";

  writeAttributes(node,true,true);
}

void VisitorLIMML::visitEnd(const logical::ClassGenericSpec& node , bool callVirtualBase) {
  createIndentation();
  ofs << "</logical:ClassGenericSpec>\n";
}

void VisitorLIMML::visit(const logical::Friendship& node , bool callVirtualBase) {
  createIndentation();
  ofs << "<logical:Friendship";
  writeAttributes(node,false,true);
  ofs << ">\n";

  writeAttributes(node,true,true);
}

void VisitorLIMML::visitEnd(const logical::Friendship& node , bool callVirtualBase) {
  createIndentation();
  ofs << "</logical:Friendship>\n";
}

void VisitorLIMML::visit(const logical::GenericParameter& node , bool callVirtualBase) {
  createIndentation();
  ofs << "<logical:GenericParameter";
  writeAttributes(node,false,true);
  ofs << ">\n";

  writeAttributes(node,true,true);
}

void VisitorLIMML::visitEnd(const logical::GenericParameter& node , bool callVirtualBase) {
  createIndentation();
  ofs << "</logical:GenericParameter>\n";
}

void VisitorLIMML::visit(const logical::Method& node , bool callVirtualBase) {
  createIndentation();
  ofs << "<logical:Method";
  writeAttributes(node,false,true);
  ofs << ">\n";

  writeAttributes(node,true,true);
}

void VisitorLIMML::visitEnd(const logical::Method& node , bool callVirtualBase) {
  createIndentation();
  ofs << "</logical:Method>\n";
}

void VisitorLIMML::visit(const logical::MethodCall& node , bool callVirtualBase) {
  createIndentation();
  ofs << "<logical:MethodCall";
  writeAttributes(node,false,true);
  ofs << ">\n";

  writeAttributes(node,true,true);
}

void VisitorLIMML::visitEnd(const logical::MethodCall& node , bool callVirtualBase) {
  createIndentation();
  ofs << "</logical:MethodCall>\n";
}

void VisitorLIMML::visit(const logical::MethodGeneric& node , bool callVirtualBase) {
  createIndentation();
  ofs << "<logical:MethodGeneric";
  writeAttributes(node,false,true);
  ofs << ">\n";

  writeAttributes(node,true,true);
}

void VisitorLIMML::visitEnd(const logical::MethodGeneric& node , bool callVirtualBase) {
  createIndentation();
  ofs << "</logical:MethodGeneric>\n";
}

void VisitorLIMML::visit(const logical::MethodGenericInstance& node , bool callVirtualBase) {
  createIndentation();
  ofs << "<logical:MethodGenericInstance";
  writeAttributes(node,false,true);
  ofs << ">\n";

  writeAttributes(node,true,true);
}

void VisitorLIMML::visitEnd(const logical::MethodGenericInstance& node , bool callVirtualBase) {
  createIndentation();
  ofs << "</logical:MethodGenericInstance>\n";
}

void VisitorLIMML::visit(const logical::MethodGenericSpec& node , bool callVirtualBase) {
  createIndentation();
  ofs << "<logical:MethodGenericSpec";
  writeAttributes(node,false,true);
  ofs << ">\n";

  writeAttributes(node,true,true);
}

void VisitorLIMML::visitEnd(const logical::MethodGenericSpec& node , bool callVirtualBase) {
  createIndentation();
  ofs << "</logical:MethodGenericSpec>\n";
}

void VisitorLIMML::visit(const logical::Package& node , bool callVirtualBase) {
  createIndentation();
  ofs << "<logical:Package";
  writeAttributes(node,false,true);
  ofs << ">\n";

  writeAttributes(node,true,true);
}

void VisitorLIMML::visitEnd(const logical::Package& node , bool callVirtualBase) {
  createIndentation();
  ofs << "</logical:Package>\n";
}

void VisitorLIMML::visit(const logical::Parameter& node , bool callVirtualBase) {
  createIndentation();
  ofs << "<logical:Parameter";
  writeAttributes(node,false,true);
  ofs << ">\n";

  writeAttributes(node,true,true);
}

void VisitorLIMML::visitEnd(const logical::Parameter& node , bool callVirtualBase) {
  createIndentation();
  ofs << "</logical:Parameter>\n";
}

void VisitorLIMML::visit(const physical::File& node , bool callVirtualBase) {
  createIndentation();
  ofs << "<physical:File";
  writeAttributes(node,false,true);
  ofs << ">\n";

  writeAttributes(node,true,true);
}

void VisitorLIMML::visitEnd(const physical::File& node , bool callVirtualBase) {
  createIndentation();
  ofs << "</physical:File>\n";
}

void VisitorLIMML::visit(const physical::FileSystem& node , bool callVirtualBase) {
  createIndentation();
  ofs << "<physical:FileSystem";
  writeAttributes(node,false,true);
  ofs << ">\n";

  writeAttributes(node,true,true);
}

void VisitorLIMML::visitEnd(const physical::FileSystem& node , bool callVirtualBase) {
  createIndentation();
  ofs << "</physical:FileSystem>\n";
}

void VisitorLIMML::visit(const physical::Folder& node , bool callVirtualBase) {
  createIndentation();
  ofs << "<physical:Folder";
  writeAttributes(node,false,true);
  ofs << ">\n";

  writeAttributes(node,true,true);
}

void VisitorLIMML::visitEnd(const physical::Folder& node , bool callVirtualBase) {
  createIndentation();
  ofs << "</physical:Folder>\n";
}

void VisitorLIMML::visit(const type::SimpleType& node , bool callVirtualBase) {
  createIndentation();
  ofs << "<type:SimpleType";
  writeAttributes(node,false,true);
  ofs << "/>\n";

  writeAttributes(node,true,true);
}

void VisitorLIMML::visitEnd(const type::SimpleType& node , bool callVirtualBase) {
}

void VisitorLIMML::visit(const type::Type& node , bool callVirtualBase) {
  createIndentation();
  ofs << "<type:Type";
  writeAttributes(node,false,true);
  ofs << ">\n";

  writeAttributes(node,true,true);
}

void VisitorLIMML::visitEnd(const type::Type& node , bool callVirtualBase) {
  createIndentation();
  ofs << "</type:Type>\n";
}

void VisitorLIMML::visit(const type::TypeFormerArray& node , bool callVirtualBase) {
  createIndentation();
  ofs << "<type:TypeFormerArray";
  writeAttributes(node,false,true);
  ofs << "/>\n";

  writeAttributes(node,true,true);
}

void VisitorLIMML::visitEnd(const type::TypeFormerArray& node , bool callVirtualBase) {
}

void VisitorLIMML::visit(const type::TypeFormerMethod& node , bool callVirtualBase) {
  createIndentation();
  ofs << "<type:TypeFormerMethod";
  writeAttributes(node,false,true);
  ofs << ">\n";

  writeAttributes(node,true,true);
}

void VisitorLIMML::visitEnd(const type::TypeFormerMethod& node , bool callVirtualBase) {
  createIndentation();
  ofs << "</type:TypeFormerMethod>\n";
}

void VisitorLIMML::visit(const type::TypeFormerNonType& node , bool callVirtualBase) {
  createIndentation();
  ofs << "<type:TypeFormerNonType";
  writeAttributes(node,false,true);
  ofs << "/>\n";

  writeAttributes(node,true,true);
}

void VisitorLIMML::visitEnd(const type::TypeFormerNonType& node , bool callVirtualBase) {
}

void VisitorLIMML::visit(const type::TypeFormerPointer& node , bool callVirtualBase) {
  createIndentation();
  ofs << "<type:TypeFormerPointer";
  writeAttributes(node,false,true);
  ofs << "/>\n";

  writeAttributes(node,true,true);
}

void VisitorLIMML::visitEnd(const type::TypeFormerPointer& node , bool callVirtualBase) {
}

void VisitorLIMML::visit(const type::TypeFormerType& node , bool callVirtualBase) {
  createIndentation();
  ofs << "<type:TypeFormerType";
  writeAttributes(node,false,true);
  ofs << ">\n";

  writeAttributes(node,true,true);
}

void VisitorLIMML::visitEnd(const type::TypeFormerType& node , bool callVirtualBase) {
  createIndentation();
  ofs << "</type:TypeFormerType>\n";
}

void VisitorLIMML::visitComponent_CompilationUnit(const base::Component& begin, const physical::File& end) {
  createIndentation();
  ofs << "<Component_CompilationUnit ref='";
  if (!noId)
    ofs << "id" << end.getId();
  ofs << "'/>\n";
}

void VisitorLIMML::visitEndComponent_CompilationUnit(const base::Component& begin, const physical::File& end) {
}

void VisitorLIMML::visitComponent_Contains(const base::Component& begin, const base::Component& end) {
  createIndentation();
  ofs << "<Component_Contains ref='";
  if (!noId)
    ofs << "id" << end.getId();
  ofs << "'/>\n";
}

void VisitorLIMML::visitEndComponent_Contains(const base::Component& begin, const base::Component& end) {
}

void VisitorLIMML::visitComponent_HasFiles(const base::Component& begin, const physical::File& end) {
  createIndentation();
  ofs << "<Component_HasFiles ref='";
  if (!noId)
    ofs << "id" << end.getId();
  ofs << "'/>\n";
}

void VisitorLIMML::visitEndComponent_HasFiles(const base::Component& begin, const physical::File& end) {
}

void VisitorLIMML::visitControlFlowBlock_Calls(const base::ControlFlowBlock& begin, const logical::Method& end) {
  createIndentation();
  ofs << "<ControlFlowBlock_Calls ref='";
  if (!noId)
    ofs << "id" << end.getId();
  ofs << "'/>\n";
}

void VisitorLIMML::visitEndControlFlowBlock_Calls(const base::ControlFlowBlock& begin, const logical::Method& end) {
}

void VisitorLIMML::visitControlFlowBlock_Pred(const base::ControlFlowBlock& begin, const base::ControlFlowBlock& end) {
  createIndentation();
  ofs << "<ControlFlowBlock_Pred ref='";
  if (!noId)
    ofs << "id" << end.getId();
  ofs << "'/>\n";
}

void VisitorLIMML::visitEndControlFlowBlock_Pred(const base::ControlFlowBlock& begin, const base::ControlFlowBlock& end) {
}

void VisitorLIMML::visitNamed_DependsOn(const base::Named& begin, const base::Named& end, const std::string& ac) {
  createIndentation();
  ofs << "<Named_DependsOn ref='";
  if (!noId)
    ofs << "id" << end.getId();
  ofs << "' value='" << ac << "'/>\n";
}

void VisitorLIMML::visitEndNamed_DependsOn(const base::Named& begin, const base::Named& end, const std::string& ac) {
}

void VisitorLIMML::visitAttribute_Calls(const logical::Attribute& begin, const logical::MethodCall& end) {
  createIndentation();
  ofs << "<Attribute_Calls ref='";
  if (!noId)
    ofs << "id" << end.getId();
  ofs << "'/>\n";
}

void VisitorLIMML::visitEndAttribute_Calls(const logical::Attribute& begin, const logical::MethodCall& end) {
}

void VisitorLIMML::visitAttribute_HasType(const logical::Attribute& begin, const type::Type& end) {
  createIndentation();
  ofs << "<Attribute_HasType ref='";
  if (!noId)
    ofs << "id" << end.getId();
  ofs << "'/>\n";
}

void VisitorLIMML::visitEndAttribute_HasType(const logical::Attribute& begin, const type::Type& end) {
}

void VisitorLIMML::visitAttributeAccess_Attribute(const logical::AttributeAccess& begin, const logical::Attribute& end) {
  createIndentation();
  ofs << "<AttributeAccess_Attribute ref='";
  if (!noId)
    ofs << "id" << end.getId();
  ofs << "'/>\n";
}

void VisitorLIMML::visitEndAttributeAccess_Attribute(const logical::AttributeAccess& begin, const logical::Attribute& end) {
}

void VisitorLIMML::visitClass_Extends(const logical::Class& begin, const logical::Class& end) {
  createIndentation();
  ofs << "<Class_Extends ref='";
  if (!noId)
    ofs << "id" << end.getId();
  ofs << "'/>\n";
}

void VisitorLIMML::visitEndClass_Extends(const logical::Class& begin, const logical::Class& end) {
}

void VisitorLIMML::visitClass_GrantsFriendship(const logical::Class& begin, const logical::Friendship& end) {
  createIndentation();
  ofs << "<Class_GrantsFriendship ref='";
  if (!noId)
    ofs << "id" << end.getId();
  ofs << "'/>\n";
}

void VisitorLIMML::visitEndClass_GrantsFriendship(const logical::Class& begin, const logical::Friendship& end) {
}

void VisitorLIMML::visitClass_IsSubclass(const logical::Class& begin, const type::Type& end) {
  createIndentation();
  ofs << "<Class_IsSubclass ref='";
  if (!noId)
    ofs << "id" << end.getId();
  ofs << "'/>\n";
}

void VisitorLIMML::visitEndClass_IsSubclass(const logical::Class& begin, const type::Type& end) {
}

void VisitorLIMML::visitClassGeneric_HasGenericParameter(const logical::ClassGeneric& begin, const logical::GenericParameter& end) {
  createIndentation();
  ofs << "<ClassGeneric_HasGenericParameter>\n";
  incDepth();
}

void VisitorLIMML::visitEndClassGeneric_HasGenericParameter(const logical::ClassGeneric& begin, const logical::GenericParameter& end) {
  decDepth();
  createIndentation();
  ofs << "</ClassGeneric_HasGenericParameter>\n";
}

void VisitorLIMML::visitClassGenericInstance_HasArguments(const logical::ClassGenericInstance& begin, const type::Type& end, TypeArgumentConstraintKind ac) {
  createIndentation();
  ofs << "<ClassGenericInstance_HasArguments ref='";
  if (!noId)
    ofs << "id" << end.getId();
  ofs << "' value='" << Common::toString(ac) << "'/>\n";
}

void VisitorLIMML::visitEndClassGenericInstance_HasArguments(const logical::ClassGenericInstance& begin, const type::Type& end, TypeArgumentConstraintKind ac) {
}

void VisitorLIMML::visitClassGenericSpec_HasArguments(const logical::ClassGenericSpec& begin, const type::Type& end, TypeArgumentConstraintKind ac) {
  createIndentation();
  ofs << "<ClassGenericSpec_HasArguments ref='";
  if (!noId)
    ofs << "id" << end.getId();
  ofs << "' value='" << Common::toString(ac) << "'/>\n";
}

void VisitorLIMML::visitEndClassGenericSpec_HasArguments(const logical::ClassGenericSpec& begin, const type::Type& end, TypeArgumentConstraintKind ac) {
}

void VisitorLIMML::visitClassGenericSpec_Specialize(const logical::ClassGenericSpec& begin, const logical::ClassGeneric& end) {
  createIndentation();
  ofs << "<ClassGenericSpec_Specialize ref='";
  if (!noId)
    ofs << "id" << end.getId();
  ofs << "'/>\n";
}

void VisitorLIMML::visitEndClassGenericSpec_Specialize(const logical::ClassGenericSpec& begin, const logical::ClassGeneric& end) {
}

void VisitorLIMML::visitFriendship_Friend(const logical::Friendship& begin, const logical::Scope& end) {
  createIndentation();
  ofs << "<Friendship_Friend ref='";
  if (!noId)
    ofs << "id" << end.getId();
  ofs << "'/>\n";
}

void VisitorLIMML::visitEndFriendship_Friend(const logical::Friendship& begin, const logical::Scope& end) {
}

void VisitorLIMML::visitGenericParameter_HasParameterConstraint(const logical::GenericParameter& begin, const type::Type& end) {
  createIndentation();
  ofs << "<GenericParameter_HasParameterConstraint ref='";
  if (!noId)
    ofs << "id" << end.getId();
  ofs << "'/>\n";
}

void VisitorLIMML::visitEndGenericParameter_HasParameterConstraint(const logical::GenericParameter& begin, const type::Type& end) {
}

void VisitorLIMML::visitMember_Aggregated(const logical::Member& begin, const logical::Member& end) {
  createIndentation();
  ofs << "<Member_Aggregated ref='";
  if (!noId)
    ofs << "id" << end.getId();
  ofs << "'/>\n";
}

void VisitorLIMML::visitEndMember_Aggregated(const logical::Member& begin, const logical::Member& end) {
}

void VisitorLIMML::visitMember_BelongsTo(const logical::Member& begin, const base::Component& end) {
  createIndentation();
  ofs << "<Member_BelongsTo ref='";
  if (!noId)
    ofs << "id" << end.getId();
  ofs << "'/>\n";
}

void VisitorLIMML::visitEndMember_BelongsTo(const logical::Member& begin, const base::Component& end) {
}

void VisitorLIMML::visitMember_CompilationUnit(const logical::Member& begin, const physical::File& end) {
  createIndentation();
  ofs << "<Member_CompilationUnit ref='";
  if (!noId)
    ofs << "id" << end.getId();
  ofs << "'/>\n";
}

void VisitorLIMML::visitEndMember_CompilationUnit(const logical::Member& begin, const physical::File& end) {
}

void VisitorLIMML::visitMember_Declares(const logical::Member& begin, const logical::Member& end) {
  createIndentation();
  ofs << "<Member_Declares ref='";
  if (!noId)
    ofs << "id" << end.getId();
  ofs << "'/>\n";
}

void VisitorLIMML::visitEndMember_Declares(const logical::Member& begin, const logical::Member& end) {
}

void VisitorLIMML::visitMember_HasComment(const logical::Member& begin, const base::Comment& end) {
  createIndentation();
  ofs << "<Member_HasComment ref='";
  if (!noId)
    ofs << "id" << end.getId();
  ofs << "'/>\n";
}

void VisitorLIMML::visitEndMember_HasComment(const logical::Member& begin, const base::Comment& end) {
}

void VisitorLIMML::visitMember_Instance(const logical::Member& begin, const logical::Member& end) {
  createIndentation();
  ofs << "<Member_Instance ref='";
  if (!noId)
    ofs << "id" << end.getId();
  ofs << "'/>\n";
}

void VisitorLIMML::visitEndMember_Instance(const logical::Member& begin, const logical::Member& end) {
}

void VisitorLIMML::visitMember_IsContainedIn(const logical::Member& begin, const physical::File& end, const SourcePosition& ac) {
  createIndentation();
  ofs << "<Member_IsContainedIn ref='";
  if (!noId)
    ofs << "id" << end.getId();
  ofs << "'>\n";
  incDepth();
  createIndentation();
  ofs << "<SourcePosition";
  writeAttributes(ac,false);
  ofs << "/>\n";
}

void VisitorLIMML::visitEndMember_IsContainedIn(const logical::Member& begin, const physical::File& end, const SourcePosition& ac) {
  decDepth();
  createIndentation();
  ofs << "</Member_IsContainedIn>\n";
}

void VisitorLIMML::visitMember_LanguageVariant(const logical::Member& begin, const logical::Member& end) {
  createIndentation();
  ofs << "<Member_LanguageVariant ref='";
  if (!noId)
    ofs << "id" << end.getId();
  ofs << "'/>\n";
}

void VisitorLIMML::visitEndMember_LanguageVariant(const logical::Member& begin, const logical::Member& end) {
}

void VisitorLIMML::visitMember_Uses(const logical::Member& begin, const type::Type& end) {
  createIndentation();
  ofs << "<Member_Uses ref='";
  if (!noId)
    ofs << "id" << end.getId();
  ofs << "'/>\n";
}

void VisitorLIMML::visitEndMember_Uses(const logical::Member& begin, const type::Type& end) {
}

void VisitorLIMML::visitMember_Variant(const logical::Member& begin, const logical::Member& end) {
  createIndentation();
  ofs << "<Member_Variant ref='";
  if (!noId)
    ofs << "id" << end.getId();
  ofs << "'/>\n";
}

void VisitorLIMML::visitEndMember_Variant(const logical::Member& begin, const logical::Member& end) {
}

void VisitorLIMML::visitMethod_AccessesAttribute(const logical::Method& begin, const logical::AttributeAccess& end) {
  createIndentation();
  ofs << "<Method_AccessesAttribute ref='";
  if (!noId)
    ofs << "id" << end.getId();
  ofs << "'/>\n";
}

void VisitorLIMML::visitEndMethod_AccessesAttribute(const logical::Method& begin, const logical::AttributeAccess& end) {
}

void VisitorLIMML::visitMethod_Calls(const logical::Method& begin, const logical::MethodCall& end) {
  createIndentation();
  ofs << "<Method_Calls ref='";
  if (!noId)
    ofs << "id" << end.getId();
  ofs << "'/>\n";
}

void VisitorLIMML::visitEndMethod_Calls(const logical::Method& begin, const logical::MethodCall& end) {
}

void VisitorLIMML::visitMethod_CanThrow(const logical::Method& begin, const type::Type& end) {
  createIndentation();
  ofs << "<Method_CanThrow ref='";
  if (!noId)
    ofs << "id" << end.getId();
  ofs << "'/>\n";
}

void VisitorLIMML::visitEndMethod_CanThrow(const logical::Method& begin, const type::Type& end) {
}

void VisitorLIMML::visitMethod_HasControlFlowBlock(const logical::Method& begin, const base::ControlFlowBlock& end) {
  createIndentation();
  ofs << "<Method_HasControlFlowBlock>\n";
  incDepth();
}

void VisitorLIMML::visitEndMethod_HasControlFlowBlock(const logical::Method& begin, const base::ControlFlowBlock& end) {
  decDepth();
  createIndentation();
  ofs << "</Method_HasControlFlowBlock>\n";
}

void VisitorLIMML::visitMethod_HasParameter(const logical::Method& begin, const logical::Parameter& end) {
  createIndentation();
  ofs << "<Method_HasParameter>\n";
  incDepth();
}

void VisitorLIMML::visitEndMethod_HasParameter(const logical::Method& begin, const logical::Parameter& end) {
  decDepth();
  createIndentation();
  ofs << "</Method_HasParameter>\n";
}

void VisitorLIMML::visitMethod_Instantiates(const logical::Method& begin, const type::Type& end) {
  createIndentation();
  ofs << "<Method_Instantiates ref='";
  if (!noId)
    ofs << "id" << end.getId();
  ofs << "'/>\n";
}

void VisitorLIMML::visitEndMethod_Instantiates(const logical::Method& begin, const type::Type& end) {
}

void VisitorLIMML::visitMethod_Returns(const logical::Method& begin, const type::Type& end) {
  createIndentation();
  ofs << "<Method_Returns ref='";
  if (!noId)
    ofs << "id" << end.getId();
  ofs << "'/>\n";
}

void VisitorLIMML::visitEndMethod_Returns(const logical::Method& begin, const type::Type& end) {
}

void VisitorLIMML::visitMethod_Throws(const logical::Method& begin, const type::Type& end) {
  createIndentation();
  ofs << "<Method_Throws ref='";
  if (!noId)
    ofs << "id" << end.getId();
  ofs << "'/>\n";
}

void VisitorLIMML::visitEndMethod_Throws(const logical::Method& begin, const type::Type& end) {
}

void VisitorLIMML::visitMethodCall_Method(const logical::MethodCall& begin, const logical::Method& end) {
  createIndentation();
  ofs << "<MethodCall_Method ref='";
  if (!noId)
    ofs << "id" << end.getId();
  ofs << "'/>\n";
}

void VisitorLIMML::visitEndMethodCall_Method(const logical::MethodCall& begin, const logical::Method& end) {
}

void VisitorLIMML::visitMethodGeneric_HasGenericParameter(const logical::MethodGeneric& begin, const logical::GenericParameter& end) {
  createIndentation();
  ofs << "<MethodGeneric_HasGenericParameter>\n";
  incDepth();
}

void VisitorLIMML::visitEndMethodGeneric_HasGenericParameter(const logical::MethodGeneric& begin, const logical::GenericParameter& end) {
  decDepth();
  createIndentation();
  ofs << "</MethodGeneric_HasGenericParameter>\n";
}

void VisitorLIMML::visitMethodGenericInstance_HasArguments(const logical::MethodGenericInstance& begin, const type::Type& end, TypeArgumentConstraintKind ac) {
  createIndentation();
  ofs << "<MethodGenericInstance_HasArguments ref='";
  if (!noId)
    ofs << "id" << end.getId();
  ofs << "' value='" << Common::toString(ac) << "'/>\n";
}

void VisitorLIMML::visitEndMethodGenericInstance_HasArguments(const logical::MethodGenericInstance& begin, const type::Type& end, TypeArgumentConstraintKind ac) {
}

void VisitorLIMML::visitMethodGenericSpec_HasArguments(const logical::MethodGenericSpec& begin, const type::Type& end, TypeArgumentConstraintKind ac) {
  createIndentation();
  ofs << "<MethodGenericSpec_HasArguments ref='";
  if (!noId)
    ofs << "id" << end.getId();
  ofs << "' value='" << Common::toString(ac) << "'/>\n";
}

void VisitorLIMML::visitEndMethodGenericSpec_HasArguments(const logical::MethodGenericSpec& begin, const type::Type& end, TypeArgumentConstraintKind ac) {
}

void VisitorLIMML::visitMethodGenericSpec_Specialize(const logical::MethodGenericSpec& begin, const logical::MethodGeneric& end) {
  createIndentation();
  ofs << "<MethodGenericSpec_Specialize ref='";
  if (!noId)
    ofs << "id" << end.getId();
  ofs << "'/>\n";
}

void VisitorLIMML::visitEndMethodGenericSpec_Specialize(const logical::MethodGenericSpec& begin, const logical::MethodGeneric& end) {
}

void VisitorLIMML::visitParameter_HasType(const logical::Parameter& begin, const type::Type& end) {
  createIndentation();
  ofs << "<Parameter_HasType ref='";
  if (!noId)
    ofs << "id" << end.getId();
  ofs << "'/>\n";
}

void VisitorLIMML::visitEndParameter_HasType(const logical::Parameter& begin, const type::Type& end) {
}

void VisitorLIMML::visitScope_HasMember(const logical::Scope& begin, const logical::Member& end) {
  createIndentation();
  ofs << "<Scope_HasMember ref='";
  if (!noId)
    ofs << "id" << end.getId();
  ofs << "'/>\n";
}

void VisitorLIMML::visitEndScope_HasMember(const logical::Scope& begin, const logical::Member& end) {
}

void VisitorLIMML::visitFile_HasComment(const physical::File& begin, const base::Comment& end) {
  createIndentation();
  ofs << "<File_HasComment ref='";
  if (!noId)
    ofs << "id" << end.getId();
  ofs << "'/>\n";
}

void VisitorLIMML::visitEndFile_HasComment(const physical::File& begin, const base::Comment& end) {
}

void VisitorLIMML::visitFile_Includes(const physical::File& begin, const physical::File& end) {
  createIndentation();
  ofs << "<File_Includes ref='";
  if (!noId)
    ofs << "id" << end.getId();
  ofs << "'/>\n";
}

void VisitorLIMML::visitEndFile_Includes(const physical::File& begin, const physical::File& end) {
}

void VisitorLIMML::visitFileSystem_HasFSEntry(const physical::FileSystem& begin, const physical::FSEntry& end) {
  createIndentation();
  ofs << "<FileSystem_HasFSEntry>\n";
  incDepth();
}

void VisitorLIMML::visitEndFileSystem_HasFSEntry(const physical::FileSystem& begin, const physical::FSEntry& end) {
  decDepth();
  createIndentation();
  ofs << "</FileSystem_HasFSEntry>\n";
}

void VisitorLIMML::visitFolder_Contains(const physical::Folder& begin, const physical::FSEntry& end) {
  createIndentation();
  ofs << "<Folder_Contains>\n";
  incDepth();
}

void VisitorLIMML::visitEndFolder_Contains(const physical::Folder& begin, const physical::FSEntry& end) {
  decDepth();
  createIndentation();
  ofs << "</Folder_Contains>\n";
}

void VisitorLIMML::visitType_HasTypeFormer(const type::Type& begin, const type::TypeFormer& end) {
  createIndentation();
  ofs << "<Type_HasTypeFormer ref='";
  if (!noId)
    ofs << "id" << end.getId();
  ofs << "'/>\n";
}

void VisitorLIMML::visitEndType_HasTypeFormer(const type::Type& begin, const type::TypeFormer& end) {
}

void VisitorLIMML::visitTypeFormerMethod_HasParameterType(const type::TypeFormerMethod& begin, const type::Type& end, ParameterKind ac) {
  createIndentation();
  ofs << "<TypeFormerMethod_HasParameterType ref='";
  if (!noId)
    ofs << "id" << end.getId();
  ofs << "' value='" << Common::toString(ac) << "'/>\n";
}

void VisitorLIMML::visitEndTypeFormerMethod_HasParameterType(const type::TypeFormerMethod& begin, const type::Type& end, ParameterKind ac) {
}

void VisitorLIMML::visitTypeFormerMethod_HasReturnType(const type::TypeFormerMethod& begin, const type::Type& end) {
  createIndentation();
  ofs << "<TypeFormerMethod_HasReturnType ref='";
  if (!noId)
    ofs << "id" << end.getId();
  ofs << "'/>\n";
}

void VisitorLIMML::visitEndTypeFormerMethod_HasReturnType(const type::TypeFormerMethod& begin, const type::Type& end) {
}

void VisitorLIMML::visitTypeFormerType_RefersTo(const type::TypeFormerType& begin, const base::Base& end) {
  createIndentation();
  ofs << "<TypeFormerType_RefersTo ref='";
  if (!noId)
    ofs << "id" << end.getId();
  ofs << "'/>\n";
}

void VisitorLIMML::visitEndTypeFormerType_RefersTo(const type::TypeFormerType& begin, const base::Base& end) {
}

void VisitorLIMML::createIndentation() {
  if (depth)
    ofs << std::string(depth, '\t');
}

string VisitorLIMML::chk(string s) {
  string::size_type pos = (string::size_type)-1;
  while ((pos = s.find("&", pos + 1)) != string::npos)
    s.replace(pos, 1, "&amp;");

  while ((pos = s.find("<", pos + 1)) != string::npos)
    s.replace(pos,1, "&lt;");

  while ((pos = s.find(">", pos + 1)) != string::npos)
    s.replace(pos,1, "&gt;");

  while ((pos = s.find("'", pos + 1)) != string::npos)
    s.replace(pos,1,"&apos;");

  while ((pos = s.find("\"", pos + 1)) != string::npos)
    s.replace(pos,1,"&quot;");

  while ((pos = s.find("\r", pos + 1)) != string::npos)
    s.replace(pos,1, "&#13;");

  while ((pos = s.find("\n", pos + 1)) != string::npos)
    s.replace(pos,1, "&#10;");

  while ((pos = s.find("\t", pos + 1)) != string::npos)
    s.replace(pos,1, "&#09;");

  return s;
}

void VisitorLIMML::writeAttributes(const base::Base& node,bool composite, bool bWithParent /*= true*/ ) {
  if (!composite) {
    ofs << " id='";
    if (!noId)
      ofs << "id" << node.getId();
    ofs << "'";

  }
  if (!composite) {
    ofs << " parent='";
    if (!noId)
      ofs << "id" << (node.getParent() ? node.getParent()->getId() : 0);
    ofs << "'";

  }
  if (!composite) {
  }
}

void VisitorLIMML::writeAttributes(const base::Comment& node,bool composite, bool bWithParent /*= true*/ ) {
  writeAttributes((base::Base&)node,composite,false);

  if (!composite) {
    ofs << " text='" << chk(node.getText()) << "'";
  }
}

void VisitorLIMML::writeAttributes(const base::Component& node,bool composite, bool bWithParent /*= true*/ ) {
  writeAttributes((base::Named&)node,composite,false);

  if (!composite) {
    ofs << " TLLOC='" << node.getTLLOC() << "'";
  }
  if (!composite) {
    ofs << " TLOC='" << node.getTLOC() << "'";
  }
  if (!composite) {
    ofs << " analysisTime='" << Common::toString(node.getAnalysisTime()) << "'";
  }
  if (!composite) {
    ofs << " changesetID='" << chk(node.getChangesetID()) << "'";
  }
  if (!composite) {
    ofs << " shortName='" << chk(node.getShortName()) << "'";
  }
}

void VisitorLIMML::writeAttributes(const base::ControlFlowBlock& node,bool composite, bool bWithParent /*= true*/ ) {
  writeAttributes((base::Base&)node,composite,false);

}

void VisitorLIMML::writeAttributes(const base::Named& node,bool composite, bool bWithParent /*= true*/ ) {
  writeAttributes((base::Base&)node,composite,false);

  if (!composite) {
    ofs << " name='" << chk(node.getName()) << "'";
  }
}

void VisitorLIMML::writeAttributes(const logical::Attribute& node,bool composite, bool bWithParent /*= true*/ ) {
  writeAttributes((logical::Member&)node,composite,false);

}

void VisitorLIMML::writeAttributes(const logical::AttributeAccess& node,bool composite, bool bWithParent /*= true*/ ) {
  writeAttributes((base::Base&)node,composite,false);

  if (!composite) {
    ofs << " accesses='" << chk(node.getAccesses()) << "'";
  }
}

void VisitorLIMML::writeAttributes(const logical::Class& node,bool composite, bool bWithParent /*= true*/ ) {
  writeAttributes((logical::Scope&)node,composite,false);

  if (!composite) {
    ofs << " classKind='" << Common::toString(node.getClassKind()) << "'";
  }
  if (!composite) {
    ofs << " isAbstract='" << (node.getIsAbstract() ? "true" : "false") << "'";
  }
  if (!composite) {
    ofs << " objectSize='" << node.getObjectSize() << "'";
  }
}

void VisitorLIMML::writeAttributes(const logical::ClassGeneric& node,bool composite, bool bWithParent /*= true*/ ) {
  writeAttributes((logical::Class&)node,composite,false);

}

void VisitorLIMML::writeAttributes(const logical::ClassGenericInstance& node,bool composite, bool bWithParent /*= true*/ ) {
  writeAttributes((logical::Class&)node,composite,false);

  if (!composite) {
    ofs << " isRealInstance='" << (node.getIsRealInstance() ? "true" : "false") << "'";
  }
}

void VisitorLIMML::writeAttributes(const logical::ClassGenericSpec& node,bool composite, bool bWithParent /*= true*/ ) {
  writeAttributes((logical::ClassGeneric&)node,composite,false);

}

void VisitorLIMML::writeAttributes(const logical::Friendship& node,bool composite, bool bWithParent /*= true*/ ) {
  writeAttributes((base::Base&)node,composite,false);

  if (!composite) {
    ofs << " grants='" << chk(node.getGrants()) << "'";
  }
}

void VisitorLIMML::writeAttributes(const logical::GenericParameter& node,bool composite, bool bWithParent /*= true*/ ) {
  writeAttributes((base::Named&)node,composite,false);

  if (!composite) {
    ofs << " genericParameterKind='" << Common::toString(node.getGenericParameterKind()) << "'";
  }
}

void VisitorLIMML::writeAttributes(const logical::Member& node,bool composite, bool bWithParent /*= true*/ ) {
  writeAttributes((base::Named&)node,composite,false);

  if (!composite) {
    ofs << " accessibility='" << Common::toString(node.getAccessibility()) << "'";
  }
  if (!composite) {
    ofs << " commentLines='" << node.getCommentLines() << "'";
  }
  if (!composite) {
    ofs << " demangledName='" << chk(node.getDemangledName()) << "'";
  }
  if (!composite) {
    ofs << " isCompilerGenerated='" << (node.getIsCompilerGenerated() ? "true" : "false") << "'";
  }
  if (!composite) {
    ofs << " isStatic='" << (node.getIsStatic() ? "true" : "false") << "'";
  }
  if (!composite) {
    ofs << " language='" << Common::toString(node.getLanguage()) << "'";
  }
  if (!composite) {
    ofs << " mangledName='" << chk(node.getMangledName()) << "'";
  }
}

void VisitorLIMML::writeAttributes(const logical::Method& node,bool composite, bool bWithParent /*= true*/ ) {
  writeAttributes((logical::Scope&)node,composite,false);

  if (!composite) {
    ofs << " distinctOperands='" << node.getDistinctOperands() << "'";
  }
  if (!composite) {
    ofs << " distinctOperators='" << node.getDistinctOperators() << "'";
  }
  if (!composite) {
    ofs << " isAbstract='" << (node.getIsAbstract() ? "true" : "false") << "'";
  }
  if (!composite) {
    ofs << " isVirtual='" << (node.getIsVirtual() ? "true" : "false") << "'";
  }
  if (!composite) {
    ofs << " methodKind='" << Common::toString(node.getMethodKind()) << "'";
  }
  if (!composite) {
    ofs << " nestingLevel='" << node.getNestingLevel() << "'";
  }
  if (!composite) {
    ofs << " nestingLevelElseIf='" << node.getNestingLevelElseIf() << "'";
  }
  if (!composite) {
    ofs << " numberOfBranches='" << node.getNumberOfBranches() << "'";
  }
  if (!composite) {
    ofs << " numberOfStatements='" << node.getNumberOfStatements() << "'";
  }
  if (!composite) {
    ofs << " totalOperands='" << node.getTotalOperands() << "'";
  }
  if (!composite) {
    ofs << " totalOperators='" << node.getTotalOperators() << "'";
  }
}

void VisitorLIMML::writeAttributes(const logical::MethodCall& node,bool composite, bool bWithParent /*= true*/ ) {
  writeAttributes((base::Base&)node,composite,false);

  if (!composite) {
    ofs << " calls='" << chk(node.getCalls()) << "'";
  }
}

void VisitorLIMML::writeAttributes(const logical::MethodGeneric& node,bool composite, bool bWithParent /*= true*/ ) {
  writeAttributes((logical::Method&)node,composite,false);

}

void VisitorLIMML::writeAttributes(const logical::MethodGenericInstance& node,bool composite, bool bWithParent /*= true*/ ) {
  writeAttributes((logical::Method&)node,composite,false);

  if (!composite) {
    ofs << " isRealInstance='" << (node.getIsRealInstance() ? "true" : "false") << "'";
  }
}

void VisitorLIMML::writeAttributes(const logical::MethodGenericSpec& node,bool composite, bool bWithParent /*= true*/ ) {
  writeAttributes((logical::MethodGeneric&)node,composite,false);

}

void VisitorLIMML::writeAttributes(const logical::Package& node,bool composite, bool bWithParent /*= true*/ ) {
  writeAttributes((logical::Scope&)node,composite,false);

  if (!composite) {
    ofs << " packageKind='" << Common::toString(node.getPackageKind()) << "'";
  }
}

void VisitorLIMML::writeAttributes(const logical::Parameter& node,bool composite, bool bWithParent /*= true*/ ) {
  writeAttributes((base::Named&)node,composite,false);

  if (!composite) {
    ofs << " paramKind='" << Common::toString(node.getParamKind()) << "'";
  }
}

void VisitorLIMML::writeAttributes(const logical::Scope& node,bool composite, bool bWithParent /*= true*/ ) {
  writeAttributes((logical::Member&)node,composite,false);

  if (!composite) {
    ofs << " LLOC='" << node.getLLOC() << "'";
  }
  if (!composite) {
    ofs << " LOC='" << node.getLOC() << "'";
  }
  if (!composite) {
    ofs << " TLLOC='" << node.getTLLOC() << "'";
  }
  if (!composite) {
    ofs << " TLOC='" << node.getTLOC() << "'";
  }
  if (!composite) {
    ofs << " isAnonymous='" << (node.getIsAnonymous() ? "true" : "false") << "'";
  }
}

void VisitorLIMML::writeAttributes(const physical::FSEntry& node,bool composite, bool bWithParent /*= true*/ ) {
  writeAttributes((base::Named&)node,composite,false);

}

void VisitorLIMML::writeAttributes(const physical::File& node,bool composite, bool bWithParent /*= true*/ ) {
  writeAttributes((physical::FSEntry&)node,composite,false);

  if (!composite) {
    ofs << " CLOC='" << node.getCLOC() << "'";
  }
  if (!composite) {
    ofs << " LLOC='" << node.getLLOC() << "'";
  }
  if (!composite) {
    ofs << " LOC='" << node.getLOC() << "'";
  }
  if (!composite) {
    ofs << " numberOfBranches='" << node.getNumberOfBranches() << "'";
  }
}

void VisitorLIMML::writeAttributes(const physical::FileSystem& node,bool composite, bool bWithParent /*= true*/ ) {
  writeAttributes((base::Named&)node,composite,false);

}

void VisitorLIMML::writeAttributes(const physical::Folder& node,bool composite, bool bWithParent /*= true*/ ) {
  writeAttributes((physical::FSEntry&)node,composite,false);

}

void VisitorLIMML::writeAttributes(const type::SimpleType& node,bool composite, bool bWithParent /*= true*/ ) {
  writeAttributes((base::Base&)node,composite,false);

  if (!composite) {
    ofs << " simpleTypeKind='" << Common::toString(node.getSimpleTypeKind()) << "'";
  }
}

void VisitorLIMML::writeAttributes(const type::Type& node,bool composite, bool bWithParent /*= true*/ ) {
  writeAttributes((base::Base&)node,composite,false);

  if (!composite) {
    ofs << " refers='" << chk(node.getRefers()) << "'";
  }
}

void VisitorLIMML::writeAttributes(const type::TypeFormer& node,bool composite, bool bWithParent /*= true*/ ) {
  writeAttributes((base::Base&)node,composite,false);

}

void VisitorLIMML::writeAttributes(const type::TypeFormerArray& node,bool composite, bool bWithParent /*= true*/ ) {
  writeAttributes((type::TypeFormer&)node,composite,false);

}

void VisitorLIMML::writeAttributes(const type::TypeFormerMethod& node,bool composite, bool bWithParent /*= true*/ ) {
  writeAttributes((type::TypeFormer&)node,composite,false);

}

void VisitorLIMML::writeAttributes(const type::TypeFormerNonType& node,bool composite, bool bWithParent /*= true*/ ) {
  writeAttributes((type::TypeFormer&)node,composite,false);

}

void VisitorLIMML::writeAttributes(const type::TypeFormerPointer& node,bool composite, bool bWithParent /*= true*/ ) {
  writeAttributes((type::TypeFormer&)node,composite,false);

  if (!composite) {
    ofs << " pointerKind='" << Common::toString(node.getPointerKind()) << "'";
  }
}

void VisitorLIMML::writeAttributes(const type::TypeFormerType& node,bool composite, bool bWithParent /*= true*/ ) {
  writeAttributes((type::TypeFormer&)node,composite,false);

}

void VisitorLIMML::writeAttributes(const SourcePosition& compType,bool composite) {
  if (!composite) {
    ofs << " realizationLevel='" << Common::toString(compType.getRealizationLevel()) << "'";
  }
  if (!composite) {
    ofs << " line='" << compType.getLine() << "'";
  }
  if (!composite) {
    ofs << " column='" << compType.getColumn() << "'";
  }
  if (!composite) {
    ofs << " endLine='" << compType.getEndLine() << "'";
  }
  if (!composite) {
    ofs << " endColumn='" << compType.getEndColumn() << "'";
  }
}


}}}
