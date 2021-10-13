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

#include "csharp/inc/csharp.h"

using namespace std;


namespace columbus { namespace csharp { namespace asg {
VisitorCSHARPML::VisitorCSHARPML(std::ofstream& targetStream,
                                 const std::string& _projectName,
                                 bool _noId,
                                 bool _noLineInfo) : ofs(targetStream), noId(_noId), noLineInfo(_noLineInfo), projectName(_projectName)
{
}

VisitorCSHARPML::~VisitorCSHARPML() {
}

void VisitorCSHARPML::beginVisit() {
  ofs << "<?xml version='1.0' encoding=\"utf-8\"?>\n";
  ofs << "<Project name='" << projectName << "'"
      << " xmlns:base='columbus_csharp_schema/base'"
      << " xmlns:expression='columbus_csharp_schema/expression'"
      << " xmlns:statement='columbus_csharp_schema/statement'"
      << " xmlns:structure='columbus_csharp_schema/structure'"
      << ">\n";
}

void VisitorCSHARPML::finishVisit() {
  ofs << "<Filtered id='id1'/>\n";
  ofs << "</Project>\n";
}

void VisitorCSHARPML::visit(const expression::AliasQualifiedNameSyntax& node , bool callVirtualBase) {
  createIndentation();
  ofs << "<expression:AliasQualifiedNameSyntax";
  writeAttributes(node,false,true);
  ofs << ">\n";

  writeAttributes(node,true,true);
}

void VisitorCSHARPML::visitEnd(const expression::AliasQualifiedNameSyntax& node , bool callVirtualBase) {
  createIndentation();
  ofs << "</expression:AliasQualifiedNameSyntax>\n";
}

void VisitorCSHARPML::visit(const expression::AnonymousMethodExpressionSyntax& node , bool callVirtualBase) {
  createIndentation();
  ofs << "<expression:AnonymousMethodExpressionSyntax";
  writeAttributes(node,false,true);
  ofs << ">\n";

  writeAttributes(node,true,true);
}

void VisitorCSHARPML::visitEnd(const expression::AnonymousMethodExpressionSyntax& node , bool callVirtualBase) {
  createIndentation();
  ofs << "</expression:AnonymousMethodExpressionSyntax>\n";
}

void VisitorCSHARPML::visit(const expression::AnonymousObjectCreationExpressionSyntax& node , bool callVirtualBase) {
  createIndentation();
  ofs << "<expression:AnonymousObjectCreationExpressionSyntax";
  writeAttributes(node,false,true);
  ofs << ">\n";

  writeAttributes(node,true,true);
}

void VisitorCSHARPML::visitEnd(const expression::AnonymousObjectCreationExpressionSyntax& node , bool callVirtualBase) {
  createIndentation();
  ofs << "</expression:AnonymousObjectCreationExpressionSyntax>\n";
}

void VisitorCSHARPML::visit(const expression::ArrayCreationExpressionSyntax& node , bool callVirtualBase) {
  createIndentation();
  ofs << "<expression:ArrayCreationExpressionSyntax";
  writeAttributes(node,false,true);
  ofs << ">\n";

  writeAttributes(node,true,true);
}

void VisitorCSHARPML::visitEnd(const expression::ArrayCreationExpressionSyntax& node , bool callVirtualBase) {
  createIndentation();
  ofs << "</expression:ArrayCreationExpressionSyntax>\n";
}

void VisitorCSHARPML::visit(const expression::ArrayTypeSyntax& node , bool callVirtualBase) {
  createIndentation();
  ofs << "<expression:ArrayTypeSyntax";
  writeAttributes(node,false,true);
  ofs << ">\n";

  writeAttributes(node,true,true);
}

void VisitorCSHARPML::visitEnd(const expression::ArrayTypeSyntax& node , bool callVirtualBase) {
  createIndentation();
  ofs << "</expression:ArrayTypeSyntax>\n";
}

void VisitorCSHARPML::visit(const expression::AssignmentExpressionSyntax& node , bool callVirtualBase) {
  createIndentation();
  ofs << "<expression:AssignmentExpressionSyntax";
  writeAttributes(node,false,true);
  ofs << ">\n";

  writeAttributes(node,true,true);
}

void VisitorCSHARPML::visitEnd(const expression::AssignmentExpressionSyntax& node , bool callVirtualBase) {
  createIndentation();
  ofs << "</expression:AssignmentExpressionSyntax>\n";
}

void VisitorCSHARPML::visit(const expression::AwaitExpressionSyntax& node , bool callVirtualBase) {
  createIndentation();
  ofs << "<expression:AwaitExpressionSyntax";
  writeAttributes(node,false,true);
  ofs << ">\n";

  writeAttributes(node,true,true);
}

void VisitorCSHARPML::visitEnd(const expression::AwaitExpressionSyntax& node , bool callVirtualBase) {
  createIndentation();
  ofs << "</expression:AwaitExpressionSyntax>\n";
}

void VisitorCSHARPML::visit(const expression::BaseExpressionSyntax& node , bool callVirtualBase) {
  createIndentation();
  ofs << "<expression:BaseExpressionSyntax";
  writeAttributes(node,false,true);
  ofs << ">\n";

  writeAttributes(node,true,true);
}

void VisitorCSHARPML::visitEnd(const expression::BaseExpressionSyntax& node , bool callVirtualBase) {
  createIndentation();
  ofs << "</expression:BaseExpressionSyntax>\n";
}

void VisitorCSHARPML::visit(const expression::BinaryExpressionSyntax& node , bool callVirtualBase) {
  createIndentation();
  ofs << "<expression:BinaryExpressionSyntax";
  writeAttributes(node,false,true);
  ofs << ">\n";

  writeAttributes(node,true,true);
}

void VisitorCSHARPML::visitEnd(const expression::BinaryExpressionSyntax& node , bool callVirtualBase) {
  createIndentation();
  ofs << "</expression:BinaryExpressionSyntax>\n";
}

void VisitorCSHARPML::visit(const expression::CastExpressionSyntax& node , bool callVirtualBase) {
  createIndentation();
  ofs << "<expression:CastExpressionSyntax";
  writeAttributes(node,false,true);
  ofs << ">\n";

  writeAttributes(node,true,true);
}

void VisitorCSHARPML::visitEnd(const expression::CastExpressionSyntax& node , bool callVirtualBase) {
  createIndentation();
  ofs << "</expression:CastExpressionSyntax>\n";
}

void VisitorCSHARPML::visit(const expression::CheckedExpressionSyntax& node , bool callVirtualBase) {
  createIndentation();
  ofs << "<expression:CheckedExpressionSyntax";
  writeAttributes(node,false,true);
  ofs << ">\n";

  writeAttributes(node,true,true);
}

void VisitorCSHARPML::visitEnd(const expression::CheckedExpressionSyntax& node , bool callVirtualBase) {
  createIndentation();
  ofs << "</expression:CheckedExpressionSyntax>\n";
}

void VisitorCSHARPML::visit(const expression::ConditionalAccessExpressionSyntax& node , bool callVirtualBase) {
  createIndentation();
  ofs << "<expression:ConditionalAccessExpressionSyntax";
  writeAttributes(node,false,true);
  ofs << ">\n";

  writeAttributes(node,true,true);
}

void VisitorCSHARPML::visitEnd(const expression::ConditionalAccessExpressionSyntax& node , bool callVirtualBase) {
  createIndentation();
  ofs << "</expression:ConditionalAccessExpressionSyntax>\n";
}

void VisitorCSHARPML::visit(const expression::ConditionalExpressionSyntax& node , bool callVirtualBase) {
  createIndentation();
  ofs << "<expression:ConditionalExpressionSyntax";
  writeAttributes(node,false,true);
  ofs << ">\n";

  writeAttributes(node,true,true);
}

void VisitorCSHARPML::visitEnd(const expression::ConditionalExpressionSyntax& node , bool callVirtualBase) {
  createIndentation();
  ofs << "</expression:ConditionalExpressionSyntax>\n";
}

void VisitorCSHARPML::visit(const expression::DeclarationExpressionSyntax& node , bool callVirtualBase) {
  createIndentation();
  ofs << "<expression:DeclarationExpressionSyntax";
  writeAttributes(node,false,true);
  ofs << ">\n";

  writeAttributes(node,true,true);
}

void VisitorCSHARPML::visitEnd(const expression::DeclarationExpressionSyntax& node , bool callVirtualBase) {
  createIndentation();
  ofs << "</expression:DeclarationExpressionSyntax>\n";
}

void VisitorCSHARPML::visit(const expression::DefaultExpressionSyntax& node , bool callVirtualBase) {
  createIndentation();
  ofs << "<expression:DefaultExpressionSyntax";
  writeAttributes(node,false,true);
  ofs << ">\n";

  writeAttributes(node,true,true);
}

void VisitorCSHARPML::visitEnd(const expression::DefaultExpressionSyntax& node , bool callVirtualBase) {
  createIndentation();
  ofs << "</expression:DefaultExpressionSyntax>\n";
}

void VisitorCSHARPML::visit(const expression::ElementAccessExpressionSyntax& node , bool callVirtualBase) {
  createIndentation();
  ofs << "<expression:ElementAccessExpressionSyntax";
  writeAttributes(node,false,true);
  ofs << ">\n";

  writeAttributes(node,true,true);
}

void VisitorCSHARPML::visitEnd(const expression::ElementAccessExpressionSyntax& node , bool callVirtualBase) {
  createIndentation();
  ofs << "</expression:ElementAccessExpressionSyntax>\n";
}

void VisitorCSHARPML::visit(const expression::ElementBindingExpressionSyntax& node , bool callVirtualBase) {
  createIndentation();
  ofs << "<expression:ElementBindingExpressionSyntax";
  writeAttributes(node,false,true);
  ofs << ">\n";

  writeAttributes(node,true,true);
}

void VisitorCSHARPML::visitEnd(const expression::ElementBindingExpressionSyntax& node , bool callVirtualBase) {
  createIndentation();
  ofs << "</expression:ElementBindingExpressionSyntax>\n";
}

void VisitorCSHARPML::visit(const expression::GenericNameSyntax& node , bool callVirtualBase) {
  createIndentation();
  ofs << "<expression:GenericNameSyntax";
  writeAttributes(node,false,true);
  ofs << ">\n";

  writeAttributes(node,true,true);
}

void VisitorCSHARPML::visitEnd(const expression::GenericNameSyntax& node , bool callVirtualBase) {
  createIndentation();
  ofs << "</expression:GenericNameSyntax>\n";
}

void VisitorCSHARPML::visit(const expression::IdentifierNameSyntax& node , bool callVirtualBase) {
  createIndentation();
  ofs << "<expression:IdentifierNameSyntax";
  writeAttributes(node,false,true);
  ofs << ">\n";

  writeAttributes(node,true,true);
}

void VisitorCSHARPML::visitEnd(const expression::IdentifierNameSyntax& node , bool callVirtualBase) {
  createIndentation();
  ofs << "</expression:IdentifierNameSyntax>\n";
}

void VisitorCSHARPML::visit(const expression::ImplicitArrayCreationExpressionSyntax& node , bool callVirtualBase) {
  createIndentation();
  ofs << "<expression:ImplicitArrayCreationExpressionSyntax";
  writeAttributes(node,false,true);
  ofs << ">\n";

  writeAttributes(node,true,true);
}

void VisitorCSHARPML::visitEnd(const expression::ImplicitArrayCreationExpressionSyntax& node , bool callVirtualBase) {
  createIndentation();
  ofs << "</expression:ImplicitArrayCreationExpressionSyntax>\n";
}

void VisitorCSHARPML::visit(const expression::ImplicitElementAccessSyntax& node , bool callVirtualBase) {
  createIndentation();
  ofs << "<expression:ImplicitElementAccessSyntax";
  writeAttributes(node,false,true);
  ofs << ">\n";

  writeAttributes(node,true,true);
}

void VisitorCSHARPML::visitEnd(const expression::ImplicitElementAccessSyntax& node , bool callVirtualBase) {
  createIndentation();
  ofs << "</expression:ImplicitElementAccessSyntax>\n";
}

void VisitorCSHARPML::visit(const expression::ImplicitStackAllocArrayCreationExpressionSyntax& node , bool callVirtualBase) {
  createIndentation();
  ofs << "<expression:ImplicitStackAllocArrayCreationExpressionSyntax";
  writeAttributes(node,false,true);
  ofs << ">\n";

  writeAttributes(node,true,true);
}

void VisitorCSHARPML::visitEnd(const expression::ImplicitStackAllocArrayCreationExpressionSyntax& node , bool callVirtualBase) {
  createIndentation();
  ofs << "</expression:ImplicitStackAllocArrayCreationExpressionSyntax>\n";
}

void VisitorCSHARPML::visit(const expression::InitializerExpressionSyntax& node , bool callVirtualBase) {
  createIndentation();
  ofs << "<expression:InitializerExpressionSyntax";
  writeAttributes(node,false,true);
  ofs << ">\n";

  writeAttributes(node,true,true);
}

void VisitorCSHARPML::visitEnd(const expression::InitializerExpressionSyntax& node , bool callVirtualBase) {
  createIndentation();
  ofs << "</expression:InitializerExpressionSyntax>\n";
}

void VisitorCSHARPML::visit(const expression::InterpolatedStringExpressionSyntax& node , bool callVirtualBase) {
  createIndentation();
  ofs << "<expression:InterpolatedStringExpressionSyntax";
  writeAttributes(node,false,true);
  ofs << ">\n";

  writeAttributes(node,true,true);
}

void VisitorCSHARPML::visitEnd(const expression::InterpolatedStringExpressionSyntax& node , bool callVirtualBase) {
  createIndentation();
  ofs << "</expression:InterpolatedStringExpressionSyntax>\n";
}

void VisitorCSHARPML::visit(const expression::InvocationExpressionSyntax& node , bool callVirtualBase) {
  createIndentation();
  ofs << "<expression:InvocationExpressionSyntax";
  writeAttributes(node,false,true);
  ofs << ">\n";

  writeAttributes(node,true,true);
}

void VisitorCSHARPML::visitEnd(const expression::InvocationExpressionSyntax& node , bool callVirtualBase) {
  createIndentation();
  ofs << "</expression:InvocationExpressionSyntax>\n";
}

void VisitorCSHARPML::visit(const expression::IsPatternExpressionSyntax& node , bool callVirtualBase) {
  createIndentation();
  ofs << "<expression:IsPatternExpressionSyntax";
  writeAttributes(node,false,true);
  ofs << ">\n";

  writeAttributes(node,true,true);
}

void VisitorCSHARPML::visitEnd(const expression::IsPatternExpressionSyntax& node , bool callVirtualBase) {
  createIndentation();
  ofs << "</expression:IsPatternExpressionSyntax>\n";
}

void VisitorCSHARPML::visit(const expression::LiteralExpressionSyntax& node , bool callVirtualBase) {
  createIndentation();
  ofs << "<expression:LiteralExpressionSyntax";
  writeAttributes(node,false,true);
  ofs << ">\n";

  writeAttributes(node,true,true);
}

void VisitorCSHARPML::visitEnd(const expression::LiteralExpressionSyntax& node , bool callVirtualBase) {
  createIndentation();
  ofs << "</expression:LiteralExpressionSyntax>\n";
}

void VisitorCSHARPML::visit(const expression::MakeRefExpressionSyntax& node , bool callVirtualBase) {
  createIndentation();
  ofs << "<expression:MakeRefExpressionSyntax";
  writeAttributes(node,false,true);
  ofs << ">\n";

  writeAttributes(node,true,true);
}

void VisitorCSHARPML::visitEnd(const expression::MakeRefExpressionSyntax& node , bool callVirtualBase) {
  createIndentation();
  ofs << "</expression:MakeRefExpressionSyntax>\n";
}

void VisitorCSHARPML::visit(const expression::MemberAccessExpressionSyntax& node , bool callVirtualBase) {
  createIndentation();
  ofs << "<expression:MemberAccessExpressionSyntax";
  writeAttributes(node,false,true);
  ofs << ">\n";

  writeAttributes(node,true,true);
}

void VisitorCSHARPML::visitEnd(const expression::MemberAccessExpressionSyntax& node , bool callVirtualBase) {
  createIndentation();
  ofs << "</expression:MemberAccessExpressionSyntax>\n";
}

void VisitorCSHARPML::visit(const expression::MemberBindingExpressionSyntax& node , bool callVirtualBase) {
  createIndentation();
  ofs << "<expression:MemberBindingExpressionSyntax";
  writeAttributes(node,false,true);
  ofs << ">\n";

  writeAttributes(node,true,true);
}

void VisitorCSHARPML::visitEnd(const expression::MemberBindingExpressionSyntax& node , bool callVirtualBase) {
  createIndentation();
  ofs << "</expression:MemberBindingExpressionSyntax>\n";
}

void VisitorCSHARPML::visit(const expression::NullableTypeSyntax& node , bool callVirtualBase) {
  createIndentation();
  ofs << "<expression:NullableTypeSyntax";
  writeAttributes(node,false,true);
  ofs << ">\n";

  writeAttributes(node,true,true);
}

void VisitorCSHARPML::visitEnd(const expression::NullableTypeSyntax& node , bool callVirtualBase) {
  createIndentation();
  ofs << "</expression:NullableTypeSyntax>\n";
}

void VisitorCSHARPML::visit(const expression::ObjectCreationExpressionSyntax& node , bool callVirtualBase) {
  createIndentation();
  ofs << "<expression:ObjectCreationExpressionSyntax";
  writeAttributes(node,false,true);
  ofs << ">\n";

  writeAttributes(node,true,true);
}

void VisitorCSHARPML::visitEnd(const expression::ObjectCreationExpressionSyntax& node , bool callVirtualBase) {
  createIndentation();
  ofs << "</expression:ObjectCreationExpressionSyntax>\n";
}

void VisitorCSHARPML::visit(const expression::OmittedArraySizeExpressionSyntax& node , bool callVirtualBase) {
  createIndentation();
  ofs << "<expression:OmittedArraySizeExpressionSyntax";
  writeAttributes(node,false,true);
  ofs << ">\n";

  writeAttributes(node,true,true);
}

void VisitorCSHARPML::visitEnd(const expression::OmittedArraySizeExpressionSyntax& node , bool callVirtualBase) {
  createIndentation();
  ofs << "</expression:OmittedArraySizeExpressionSyntax>\n";
}

void VisitorCSHARPML::visit(const expression::OmittedTypeArgumentSyntax& node , bool callVirtualBase) {
  createIndentation();
  ofs << "<expression:OmittedTypeArgumentSyntax";
  writeAttributes(node,false,true);
  ofs << ">\n";

  writeAttributes(node,true,true);
}

void VisitorCSHARPML::visitEnd(const expression::OmittedTypeArgumentSyntax& node , bool callVirtualBase) {
  createIndentation();
  ofs << "</expression:OmittedTypeArgumentSyntax>\n";
}

void VisitorCSHARPML::visit(const expression::ParenthesizedExpressionSyntax& node , bool callVirtualBase) {
  createIndentation();
  ofs << "<expression:ParenthesizedExpressionSyntax";
  writeAttributes(node,false,true);
  ofs << ">\n";

  writeAttributes(node,true,true);
}

void VisitorCSHARPML::visitEnd(const expression::ParenthesizedExpressionSyntax& node , bool callVirtualBase) {
  createIndentation();
  ofs << "</expression:ParenthesizedExpressionSyntax>\n";
}

void VisitorCSHARPML::visit(const expression::ParenthesizedLambdaExpressionSyntax& node , bool callVirtualBase) {
  createIndentation();
  ofs << "<expression:ParenthesizedLambdaExpressionSyntax";
  writeAttributes(node,false,true);
  ofs << ">\n";

  writeAttributes(node,true,true);
}

void VisitorCSHARPML::visitEnd(const expression::ParenthesizedLambdaExpressionSyntax& node , bool callVirtualBase) {
  createIndentation();
  ofs << "</expression:ParenthesizedLambdaExpressionSyntax>\n";
}

void VisitorCSHARPML::visit(const expression::PointerTypeSyntax& node , bool callVirtualBase) {
  createIndentation();
  ofs << "<expression:PointerTypeSyntax";
  writeAttributes(node,false,true);
  ofs << ">\n";

  writeAttributes(node,true,true);
}

void VisitorCSHARPML::visitEnd(const expression::PointerTypeSyntax& node , bool callVirtualBase) {
  createIndentation();
  ofs << "</expression:PointerTypeSyntax>\n";
}

void VisitorCSHARPML::visit(const expression::PostfixUnaryExpressionSyntax& node , bool callVirtualBase) {
  createIndentation();
  ofs << "<expression:PostfixUnaryExpressionSyntax";
  writeAttributes(node,false,true);
  ofs << ">\n";

  writeAttributes(node,true,true);
}

void VisitorCSHARPML::visitEnd(const expression::PostfixUnaryExpressionSyntax& node , bool callVirtualBase) {
  createIndentation();
  ofs << "</expression:PostfixUnaryExpressionSyntax>\n";
}

void VisitorCSHARPML::visit(const expression::PredefinedTypeSyntax& node , bool callVirtualBase) {
  createIndentation();
  ofs << "<expression:PredefinedTypeSyntax";
  writeAttributes(node,false,true);
  ofs << ">\n";

  writeAttributes(node,true,true);
}

void VisitorCSHARPML::visitEnd(const expression::PredefinedTypeSyntax& node , bool callVirtualBase) {
  createIndentation();
  ofs << "</expression:PredefinedTypeSyntax>\n";
}

void VisitorCSHARPML::visit(const expression::PrefixUnaryExpressionSyntax& node , bool callVirtualBase) {
  createIndentation();
  ofs << "<expression:PrefixUnaryExpressionSyntax";
  writeAttributes(node,false,true);
  ofs << ">\n";

  writeAttributes(node,true,true);
}

void VisitorCSHARPML::visitEnd(const expression::PrefixUnaryExpressionSyntax& node , bool callVirtualBase) {
  createIndentation();
  ofs << "</expression:PrefixUnaryExpressionSyntax>\n";
}

void VisitorCSHARPML::visit(const expression::QualifiedNameSyntax& node , bool callVirtualBase) {
  createIndentation();
  ofs << "<expression:QualifiedNameSyntax";
  writeAttributes(node,false,true);
  ofs << ">\n";

  writeAttributes(node,true,true);
}

void VisitorCSHARPML::visitEnd(const expression::QualifiedNameSyntax& node , bool callVirtualBase) {
  createIndentation();
  ofs << "</expression:QualifiedNameSyntax>\n";
}

void VisitorCSHARPML::visit(const expression::QueryExpressionSyntax& node , bool callVirtualBase) {
  createIndentation();
  ofs << "<expression:QueryExpressionSyntax";
  writeAttributes(node,false,true);
  ofs << ">\n";

  writeAttributes(node,true,true);
}

void VisitorCSHARPML::visitEnd(const expression::QueryExpressionSyntax& node , bool callVirtualBase) {
  createIndentation();
  ofs << "</expression:QueryExpressionSyntax>\n";
}

void VisitorCSHARPML::visit(const expression::RangeExpressionSyntax& node , bool callVirtualBase) {
  createIndentation();
  ofs << "<expression:RangeExpressionSyntax";
  writeAttributes(node,false,true);
  ofs << ">\n";

  writeAttributes(node,true,true);
}

void VisitorCSHARPML::visitEnd(const expression::RangeExpressionSyntax& node , bool callVirtualBase) {
  createIndentation();
  ofs << "</expression:RangeExpressionSyntax>\n";
}

void VisitorCSHARPML::visit(const expression::RefExpressionSyntax& node , bool callVirtualBase) {
  createIndentation();
  ofs << "<expression:RefExpressionSyntax";
  writeAttributes(node,false,true);
  ofs << ">\n";

  writeAttributes(node,true,true);
}

void VisitorCSHARPML::visitEnd(const expression::RefExpressionSyntax& node , bool callVirtualBase) {
  createIndentation();
  ofs << "</expression:RefExpressionSyntax>\n";
}

void VisitorCSHARPML::visit(const expression::RefTypeExpressionSyntax& node , bool callVirtualBase) {
  createIndentation();
  ofs << "<expression:RefTypeExpressionSyntax";
  writeAttributes(node,false,true);
  ofs << ">\n";

  writeAttributes(node,true,true);
}

void VisitorCSHARPML::visitEnd(const expression::RefTypeExpressionSyntax& node , bool callVirtualBase) {
  createIndentation();
  ofs << "</expression:RefTypeExpressionSyntax>\n";
}

void VisitorCSHARPML::visit(const expression::RefTypeSyntax& node , bool callVirtualBase) {
  createIndentation();
  ofs << "<expression:RefTypeSyntax";
  writeAttributes(node,false,true);
  ofs << ">\n";

  writeAttributes(node,true,true);
}

void VisitorCSHARPML::visitEnd(const expression::RefTypeSyntax& node , bool callVirtualBase) {
  createIndentation();
  ofs << "</expression:RefTypeSyntax>\n";
}

void VisitorCSHARPML::visit(const expression::RefValueExpressionSyntax& node , bool callVirtualBase) {
  createIndentation();
  ofs << "<expression:RefValueExpressionSyntax";
  writeAttributes(node,false,true);
  ofs << ">\n";

  writeAttributes(node,true,true);
}

void VisitorCSHARPML::visitEnd(const expression::RefValueExpressionSyntax& node , bool callVirtualBase) {
  createIndentation();
  ofs << "</expression:RefValueExpressionSyntax>\n";
}

void VisitorCSHARPML::visit(const expression::SimpleLambdaExpressionSyntax& node , bool callVirtualBase) {
  createIndentation();
  ofs << "<expression:SimpleLambdaExpressionSyntax";
  writeAttributes(node,false,true);
  ofs << ">\n";

  writeAttributes(node,true,true);
}

void VisitorCSHARPML::visitEnd(const expression::SimpleLambdaExpressionSyntax& node , bool callVirtualBase) {
  createIndentation();
  ofs << "</expression:SimpleLambdaExpressionSyntax>\n";
}

void VisitorCSHARPML::visit(const expression::SizeOfExpressionSyntax& node , bool callVirtualBase) {
  createIndentation();
  ofs << "<expression:SizeOfExpressionSyntax";
  writeAttributes(node,false,true);
  ofs << ">\n";

  writeAttributes(node,true,true);
}

void VisitorCSHARPML::visitEnd(const expression::SizeOfExpressionSyntax& node , bool callVirtualBase) {
  createIndentation();
  ofs << "</expression:SizeOfExpressionSyntax>\n";
}

void VisitorCSHARPML::visit(const expression::StackAllocArrayCreationExpressionSyntax& node , bool callVirtualBase) {
  createIndentation();
  ofs << "<expression:StackAllocArrayCreationExpressionSyntax";
  writeAttributes(node,false,true);
  ofs << ">\n";

  writeAttributes(node,true,true);
}

void VisitorCSHARPML::visitEnd(const expression::StackAllocArrayCreationExpressionSyntax& node , bool callVirtualBase) {
  createIndentation();
  ofs << "</expression:StackAllocArrayCreationExpressionSyntax>\n";
}

void VisitorCSHARPML::visit(const expression::SwitchExpressionSyntax& node , bool callVirtualBase) {
  createIndentation();
  ofs << "<expression:SwitchExpressionSyntax";
  writeAttributes(node,false,true);
  ofs << ">\n";

  writeAttributes(node,true,true);
}

void VisitorCSHARPML::visitEnd(const expression::SwitchExpressionSyntax& node , bool callVirtualBase) {
  createIndentation();
  ofs << "</expression:SwitchExpressionSyntax>\n";
}

void VisitorCSHARPML::visit(const expression::ThisExpressionSyntax& node , bool callVirtualBase) {
  createIndentation();
  ofs << "<expression:ThisExpressionSyntax";
  writeAttributes(node,false,true);
  ofs << ">\n";

  writeAttributes(node,true,true);
}

void VisitorCSHARPML::visitEnd(const expression::ThisExpressionSyntax& node , bool callVirtualBase) {
  createIndentation();
  ofs << "</expression:ThisExpressionSyntax>\n";
}

void VisitorCSHARPML::visit(const expression::ThrowExpressionSyntax& node , bool callVirtualBase) {
  createIndentation();
  ofs << "<expression:ThrowExpressionSyntax";
  writeAttributes(node,false,true);
  ofs << ">\n";

  writeAttributes(node,true,true);
}

void VisitorCSHARPML::visitEnd(const expression::ThrowExpressionSyntax& node , bool callVirtualBase) {
  createIndentation();
  ofs << "</expression:ThrowExpressionSyntax>\n";
}

void VisitorCSHARPML::visit(const expression::TupleExpressionSyntax& node , bool callVirtualBase) {
  createIndentation();
  ofs << "<expression:TupleExpressionSyntax";
  writeAttributes(node,false,true);
  ofs << ">\n";

  writeAttributes(node,true,true);
}

void VisitorCSHARPML::visitEnd(const expression::TupleExpressionSyntax& node , bool callVirtualBase) {
  createIndentation();
  ofs << "</expression:TupleExpressionSyntax>\n";
}

void VisitorCSHARPML::visit(const expression::TupleTypeSyntax& node , bool callVirtualBase) {
  createIndentation();
  ofs << "<expression:TupleTypeSyntax";
  writeAttributes(node,false,true);
  ofs << ">\n";

  writeAttributes(node,true,true);
}

void VisitorCSHARPML::visitEnd(const expression::TupleTypeSyntax& node , bool callVirtualBase) {
  createIndentation();
  ofs << "</expression:TupleTypeSyntax>\n";
}

void VisitorCSHARPML::visit(const expression::TypeOfExpressionSyntax& node , bool callVirtualBase) {
  createIndentation();
  ofs << "<expression:TypeOfExpressionSyntax";
  writeAttributes(node,false,true);
  ofs << ">\n";

  writeAttributes(node,true,true);
}

void VisitorCSHARPML::visitEnd(const expression::TypeOfExpressionSyntax& node , bool callVirtualBase) {
  createIndentation();
  ofs << "</expression:TypeOfExpressionSyntax>\n";
}

void VisitorCSHARPML::visit(const statement::BlockSyntax& node , bool callVirtualBase) {
  createIndentation();
  ofs << "<statement:BlockSyntax";
  writeAttributes(node,false,true);
  ofs << ">\n";

  writeAttributes(node,true,true);
}

void VisitorCSHARPML::visitEnd(const statement::BlockSyntax& node , bool callVirtualBase) {
  createIndentation();
  ofs << "</statement:BlockSyntax>\n";
}

void VisitorCSHARPML::visit(const statement::BreakStatementSyntax& node , bool callVirtualBase) {
  createIndentation();
  ofs << "<statement:BreakStatementSyntax";
  writeAttributes(node,false,true);
  ofs << ">\n";

  writeAttributes(node,true,true);
}

void VisitorCSHARPML::visitEnd(const statement::BreakStatementSyntax& node , bool callVirtualBase) {
  createIndentation();
  ofs << "</statement:BreakStatementSyntax>\n";
}

void VisitorCSHARPML::visit(const statement::CheckedStatementSyntax& node , bool callVirtualBase) {
  createIndentation();
  ofs << "<statement:CheckedStatementSyntax";
  writeAttributes(node,false,true);
  ofs << ">\n";

  writeAttributes(node,true,true);
}

void VisitorCSHARPML::visitEnd(const statement::CheckedStatementSyntax& node , bool callVirtualBase) {
  createIndentation();
  ofs << "</statement:CheckedStatementSyntax>\n";
}

void VisitorCSHARPML::visit(const statement::ContinueStatementSyntax& node , bool callVirtualBase) {
  createIndentation();
  ofs << "<statement:ContinueStatementSyntax";
  writeAttributes(node,false,true);
  ofs << ">\n";

  writeAttributes(node,true,true);
}

void VisitorCSHARPML::visitEnd(const statement::ContinueStatementSyntax& node , bool callVirtualBase) {
  createIndentation();
  ofs << "</statement:ContinueStatementSyntax>\n";
}

void VisitorCSHARPML::visit(const statement::DoStatementSyntax& node , bool callVirtualBase) {
  createIndentation();
  ofs << "<statement:DoStatementSyntax";
  writeAttributes(node,false,true);
  ofs << ">\n";

  writeAttributes(node,true,true);
}

void VisitorCSHARPML::visitEnd(const statement::DoStatementSyntax& node , bool callVirtualBase) {
  createIndentation();
  ofs << "</statement:DoStatementSyntax>\n";
}

void VisitorCSHARPML::visit(const statement::EmptyStatementSyntax& node , bool callVirtualBase) {
  createIndentation();
  ofs << "<statement:EmptyStatementSyntax";
  writeAttributes(node,false,true);
  ofs << ">\n";

  writeAttributes(node,true,true);
}

void VisitorCSHARPML::visitEnd(const statement::EmptyStatementSyntax& node , bool callVirtualBase) {
  createIndentation();
  ofs << "</statement:EmptyStatementSyntax>\n";
}

void VisitorCSHARPML::visit(const statement::ExpressionStatementSyntax& node , bool callVirtualBase) {
  createIndentation();
  ofs << "<statement:ExpressionStatementSyntax";
  writeAttributes(node,false,true);
  ofs << ">\n";

  writeAttributes(node,true,true);
}

void VisitorCSHARPML::visitEnd(const statement::ExpressionStatementSyntax& node , bool callVirtualBase) {
  createIndentation();
  ofs << "</statement:ExpressionStatementSyntax>\n";
}

void VisitorCSHARPML::visit(const statement::FixedStatementSyntax& node , bool callVirtualBase) {
  createIndentation();
  ofs << "<statement:FixedStatementSyntax";
  writeAttributes(node,false,true);
  ofs << ">\n";

  writeAttributes(node,true,true);
}

void VisitorCSHARPML::visitEnd(const statement::FixedStatementSyntax& node , bool callVirtualBase) {
  createIndentation();
  ofs << "</statement:FixedStatementSyntax>\n";
}

void VisitorCSHARPML::visit(const statement::ForEachStatementSyntax& node , bool callVirtualBase) {
  createIndentation();
  ofs << "<statement:ForEachStatementSyntax";
  writeAttributes(node,false,true);
  ofs << ">\n";

  writeAttributes(node,true,true);
}

void VisitorCSHARPML::visitEnd(const statement::ForEachStatementSyntax& node , bool callVirtualBase) {
  createIndentation();
  ofs << "</statement:ForEachStatementSyntax>\n";
}

void VisitorCSHARPML::visit(const statement::ForEachVariableStatementSyntax& node , bool callVirtualBase) {
  createIndentation();
  ofs << "<statement:ForEachVariableStatementSyntax";
  writeAttributes(node,false,true);
  ofs << ">\n";

  writeAttributes(node,true,true);
}

void VisitorCSHARPML::visitEnd(const statement::ForEachVariableStatementSyntax& node , bool callVirtualBase) {
  createIndentation();
  ofs << "</statement:ForEachVariableStatementSyntax>\n";
}

void VisitorCSHARPML::visit(const statement::ForStatementSyntax& node , bool callVirtualBase) {
  createIndentation();
  ofs << "<statement:ForStatementSyntax";
  writeAttributes(node,false,true);
  ofs << ">\n";

  writeAttributes(node,true,true);
}

void VisitorCSHARPML::visitEnd(const statement::ForStatementSyntax& node , bool callVirtualBase) {
  createIndentation();
  ofs << "</statement:ForStatementSyntax>\n";
}

void VisitorCSHARPML::visit(const statement::GotoStatementSyntax& node , bool callVirtualBase) {
  createIndentation();
  ofs << "<statement:GotoStatementSyntax";
  writeAttributes(node,false,true);
  ofs << ">\n";

  writeAttributes(node,true,true);
}

void VisitorCSHARPML::visitEnd(const statement::GotoStatementSyntax& node , bool callVirtualBase) {
  createIndentation();
  ofs << "</statement:GotoStatementSyntax>\n";
}

void VisitorCSHARPML::visit(const statement::IfStatementSyntax& node , bool callVirtualBase) {
  createIndentation();
  ofs << "<statement:IfStatementSyntax";
  writeAttributes(node,false,true);
  ofs << ">\n";

  writeAttributes(node,true,true);
}

void VisitorCSHARPML::visitEnd(const statement::IfStatementSyntax& node , bool callVirtualBase) {
  createIndentation();
  ofs << "</statement:IfStatementSyntax>\n";
}

void VisitorCSHARPML::visit(const statement::LabeledStatementSyntax& node , bool callVirtualBase) {
  createIndentation();
  ofs << "<statement:LabeledStatementSyntax";
  writeAttributes(node,false,true);
  ofs << ">\n";

  writeAttributes(node,true,true);
}

void VisitorCSHARPML::visitEnd(const statement::LabeledStatementSyntax& node , bool callVirtualBase) {
  createIndentation();
  ofs << "</statement:LabeledStatementSyntax>\n";
}

void VisitorCSHARPML::visit(const statement::LocalDeclarationStatementSyntax& node , bool callVirtualBase) {
  createIndentation();
  ofs << "<statement:LocalDeclarationStatementSyntax";
  writeAttributes(node,false,true);
  ofs << ">\n";

  writeAttributes(node,true,true);
}

void VisitorCSHARPML::visitEnd(const statement::LocalDeclarationStatementSyntax& node , bool callVirtualBase) {
  createIndentation();
  ofs << "</statement:LocalDeclarationStatementSyntax>\n";
}

void VisitorCSHARPML::visit(const statement::LocalFunctionStatementSyntax& node , bool callVirtualBase) {
  createIndentation();
  ofs << "<statement:LocalFunctionStatementSyntax";
  writeAttributes(node,false,true);
  ofs << ">\n";

  writeAttributes(node,true,true);
}

void VisitorCSHARPML::visitEnd(const statement::LocalFunctionStatementSyntax& node , bool callVirtualBase) {
  createIndentation();
  ofs << "</statement:LocalFunctionStatementSyntax>\n";
}

void VisitorCSHARPML::visit(const statement::LockStatementSyntax& node , bool callVirtualBase) {
  createIndentation();
  ofs << "<statement:LockStatementSyntax";
  writeAttributes(node,false,true);
  ofs << ">\n";

  writeAttributes(node,true,true);
}

void VisitorCSHARPML::visitEnd(const statement::LockStatementSyntax& node , bool callVirtualBase) {
  createIndentation();
  ofs << "</statement:LockStatementSyntax>\n";
}

void VisitorCSHARPML::visit(const statement::ReturnStatementSyntax& node , bool callVirtualBase) {
  createIndentation();
  ofs << "<statement:ReturnStatementSyntax";
  writeAttributes(node,false,true);
  ofs << ">\n";

  writeAttributes(node,true,true);
}

void VisitorCSHARPML::visitEnd(const statement::ReturnStatementSyntax& node , bool callVirtualBase) {
  createIndentation();
  ofs << "</statement:ReturnStatementSyntax>\n";
}

void VisitorCSHARPML::visit(const statement::SwitchStatementSyntax& node , bool callVirtualBase) {
  createIndentation();
  ofs << "<statement:SwitchStatementSyntax";
  writeAttributes(node,false,true);
  ofs << ">\n";

  writeAttributes(node,true,true);
}

void VisitorCSHARPML::visitEnd(const statement::SwitchStatementSyntax& node , bool callVirtualBase) {
  createIndentation();
  ofs << "</statement:SwitchStatementSyntax>\n";
}

void VisitorCSHARPML::visit(const statement::ThrowStatementSyntax& node , bool callVirtualBase) {
  createIndentation();
  ofs << "<statement:ThrowStatementSyntax";
  writeAttributes(node,false,true);
  ofs << ">\n";

  writeAttributes(node,true,true);
}

void VisitorCSHARPML::visitEnd(const statement::ThrowStatementSyntax& node , bool callVirtualBase) {
  createIndentation();
  ofs << "</statement:ThrowStatementSyntax>\n";
}

void VisitorCSHARPML::visit(const statement::TryStatementSyntax& node , bool callVirtualBase) {
  createIndentation();
  ofs << "<statement:TryStatementSyntax";
  writeAttributes(node,false,true);
  ofs << ">\n";

  writeAttributes(node,true,true);
}

void VisitorCSHARPML::visitEnd(const statement::TryStatementSyntax& node , bool callVirtualBase) {
  createIndentation();
  ofs << "</statement:TryStatementSyntax>\n";
}

void VisitorCSHARPML::visit(const statement::UnsafeStatementSyntax& node , bool callVirtualBase) {
  createIndentation();
  ofs << "<statement:UnsafeStatementSyntax";
  writeAttributes(node,false,true);
  ofs << ">\n";

  writeAttributes(node,true,true);
}

void VisitorCSHARPML::visitEnd(const statement::UnsafeStatementSyntax& node , bool callVirtualBase) {
  createIndentation();
  ofs << "</statement:UnsafeStatementSyntax>\n";
}

void VisitorCSHARPML::visit(const statement::UsingStatementSyntax& node , bool callVirtualBase) {
  createIndentation();
  ofs << "<statement:UsingStatementSyntax";
  writeAttributes(node,false,true);
  ofs << ">\n";

  writeAttributes(node,true,true);
}

void VisitorCSHARPML::visitEnd(const statement::UsingStatementSyntax& node , bool callVirtualBase) {
  createIndentation();
  ofs << "</statement:UsingStatementSyntax>\n";
}

void VisitorCSHARPML::visit(const statement::WhileStatementSyntax& node , bool callVirtualBase) {
  createIndentation();
  ofs << "<statement:WhileStatementSyntax";
  writeAttributes(node,false,true);
  ofs << ">\n";

  writeAttributes(node,true,true);
}

void VisitorCSHARPML::visitEnd(const statement::WhileStatementSyntax& node , bool callVirtualBase) {
  createIndentation();
  ofs << "</statement:WhileStatementSyntax>\n";
}

void VisitorCSHARPML::visit(const statement::YieldStatementSyntax& node , bool callVirtualBase) {
  createIndentation();
  ofs << "<statement:YieldStatementSyntax";
  writeAttributes(node,false,true);
  ofs << ">\n";

  writeAttributes(node,true,true);
}

void VisitorCSHARPML::visitEnd(const statement::YieldStatementSyntax& node , bool callVirtualBase) {
  createIndentation();
  ofs << "</statement:YieldStatementSyntax>\n";
}

void VisitorCSHARPML::visit(const structure::AccessorDeclarationSyntax& node , bool callVirtualBase) {
  createIndentation();
  ofs << "<structure:AccessorDeclarationSyntax";
  writeAttributes(node,false,true);
  ofs << ">\n";

  writeAttributes(node,true,true);
}

void VisitorCSHARPML::visitEnd(const structure::AccessorDeclarationSyntax& node , bool callVirtualBase) {
  createIndentation();
  ofs << "</structure:AccessorDeclarationSyntax>\n";
}

void VisitorCSHARPML::visit(const structure::AccessorListSyntax& node , bool callVirtualBase) {
  createIndentation();
  ofs << "<structure:AccessorListSyntax";
  writeAttributes(node,false,true);
  ofs << ">\n";

  writeAttributes(node,true,true);
}

void VisitorCSHARPML::visitEnd(const structure::AccessorListSyntax& node , bool callVirtualBase) {
  createIndentation();
  ofs << "</structure:AccessorListSyntax>\n";
}

void VisitorCSHARPML::visit(const structure::AnonymousObjectMemberDeclaratorSyntax& node , bool callVirtualBase) {
  createIndentation();
  ofs << "<structure:AnonymousObjectMemberDeclaratorSyntax";
  writeAttributes(node,false,true);
  ofs << ">\n";

  writeAttributes(node,true,true);
}

void VisitorCSHARPML::visitEnd(const structure::AnonymousObjectMemberDeclaratorSyntax& node , bool callVirtualBase) {
  createIndentation();
  ofs << "</structure:AnonymousObjectMemberDeclaratorSyntax>\n";
}

void VisitorCSHARPML::visit(const structure::ArgumentListSyntax& node , bool callVirtualBase) {
  createIndentation();
  ofs << "<structure:ArgumentListSyntax";
  writeAttributes(node,false,true);
  ofs << ">\n";

  writeAttributes(node,true,true);
}

void VisitorCSHARPML::visitEnd(const structure::ArgumentListSyntax& node , bool callVirtualBase) {
  createIndentation();
  ofs << "</structure:ArgumentListSyntax>\n";
}

void VisitorCSHARPML::visit(const structure::ArgumentSyntax& node , bool callVirtualBase) {
  createIndentation();
  ofs << "<structure:ArgumentSyntax";
  writeAttributes(node,false,true);
  ofs << ">\n";

  writeAttributes(node,true,true);
}

void VisitorCSHARPML::visitEnd(const structure::ArgumentSyntax& node , bool callVirtualBase) {
  createIndentation();
  ofs << "</structure:ArgumentSyntax>\n";
}

void VisitorCSHARPML::visit(const structure::ArrayRankSpecifierSyntax& node , bool callVirtualBase) {
  createIndentation();
  ofs << "<structure:ArrayRankSpecifierSyntax";
  writeAttributes(node,false,true);
  ofs << ">\n";

  writeAttributes(node,true,true);
}

void VisitorCSHARPML::visitEnd(const structure::ArrayRankSpecifierSyntax& node , bool callVirtualBase) {
  createIndentation();
  ofs << "</structure:ArrayRankSpecifierSyntax>\n";
}

void VisitorCSHARPML::visit(const structure::ArrowExpressionClauseSyntax& node , bool callVirtualBase) {
  createIndentation();
  ofs << "<structure:ArrowExpressionClauseSyntax";
  writeAttributes(node,false,true);
  ofs << ">\n";

  writeAttributes(node,true,true);
}

void VisitorCSHARPML::visitEnd(const structure::ArrowExpressionClauseSyntax& node , bool callVirtualBase) {
  createIndentation();
  ofs << "</structure:ArrowExpressionClauseSyntax>\n";
}

void VisitorCSHARPML::visit(const structure::AttributeArgumentListSyntax& node , bool callVirtualBase) {
  createIndentation();
  ofs << "<structure:AttributeArgumentListSyntax";
  writeAttributes(node,false,true);
  ofs << ">\n";

  writeAttributes(node,true,true);
}

void VisitorCSHARPML::visitEnd(const structure::AttributeArgumentListSyntax& node , bool callVirtualBase) {
  createIndentation();
  ofs << "</structure:AttributeArgumentListSyntax>\n";
}

void VisitorCSHARPML::visit(const structure::AttributeArgumentSyntax& node , bool callVirtualBase) {
  createIndentation();
  ofs << "<structure:AttributeArgumentSyntax";
  writeAttributes(node,false,true);
  ofs << ">\n";

  writeAttributes(node,true,true);
}

void VisitorCSHARPML::visitEnd(const structure::AttributeArgumentSyntax& node , bool callVirtualBase) {
  createIndentation();
  ofs << "</structure:AttributeArgumentSyntax>\n";
}

void VisitorCSHARPML::visit(const structure::AttributeListSyntax& node , bool callVirtualBase) {
  createIndentation();
  ofs << "<structure:AttributeListSyntax";
  writeAttributes(node,false,true);
  ofs << ">\n";

  writeAttributes(node,true,true);
}

void VisitorCSHARPML::visitEnd(const structure::AttributeListSyntax& node , bool callVirtualBase) {
  createIndentation();
  ofs << "</structure:AttributeListSyntax>\n";
}

void VisitorCSHARPML::visit(const structure::AttributeSyntax& node , bool callVirtualBase) {
  createIndentation();
  ofs << "<structure:AttributeSyntax";
  writeAttributes(node,false,true);
  ofs << ">\n";

  writeAttributes(node,true,true);
}

void VisitorCSHARPML::visitEnd(const structure::AttributeSyntax& node , bool callVirtualBase) {
  createIndentation();
  ofs << "</structure:AttributeSyntax>\n";
}

void VisitorCSHARPML::visit(const structure::AttributeTargetSpecifierSyntax& node , bool callVirtualBase) {
  createIndentation();
  ofs << "<structure:AttributeTargetSpecifierSyntax";
  writeAttributes(node,false,true);
  ofs << ">\n";

  writeAttributes(node,true,true);
}

void VisitorCSHARPML::visitEnd(const structure::AttributeTargetSpecifierSyntax& node , bool callVirtualBase) {
  createIndentation();
  ofs << "</structure:AttributeTargetSpecifierSyntax>\n";
}

void VisitorCSHARPML::visit(const structure::BaseListSyntax& node , bool callVirtualBase) {
  createIndentation();
  ofs << "<structure:BaseListSyntax";
  writeAttributes(node,false,true);
  ofs << ">\n";

  writeAttributes(node,true,true);
}

void VisitorCSHARPML::visitEnd(const structure::BaseListSyntax& node , bool callVirtualBase) {
  createIndentation();
  ofs << "</structure:BaseListSyntax>\n";
}

void VisitorCSHARPML::visit(const structure::BracketedArgumentListSyntax& node , bool callVirtualBase) {
  createIndentation();
  ofs << "<structure:BracketedArgumentListSyntax";
  writeAttributes(node,false,true);
  ofs << ">\n";

  writeAttributes(node,true,true);
}

void VisitorCSHARPML::visitEnd(const structure::BracketedArgumentListSyntax& node , bool callVirtualBase) {
  createIndentation();
  ofs << "</structure:BracketedArgumentListSyntax>\n";
}

void VisitorCSHARPML::visit(const structure::BracketedParameterListSyntax& node , bool callVirtualBase) {
  createIndentation();
  ofs << "<structure:BracketedParameterListSyntax";
  writeAttributes(node,false,true);
  ofs << ">\n";

  writeAttributes(node,true,true);
}

void VisitorCSHARPML::visitEnd(const structure::BracketedParameterListSyntax& node , bool callVirtualBase) {
  createIndentation();
  ofs << "</structure:BracketedParameterListSyntax>\n";
}

void VisitorCSHARPML::visit(const structure::CasePatternSwitchLabelSyntax& node , bool callVirtualBase) {
  createIndentation();
  ofs << "<structure:CasePatternSwitchLabelSyntax";
  writeAttributes(node,false,true);
  ofs << ">\n";

  writeAttributes(node,true,true);
}

void VisitorCSHARPML::visitEnd(const structure::CasePatternSwitchLabelSyntax& node , bool callVirtualBase) {
  createIndentation();
  ofs << "</structure:CasePatternSwitchLabelSyntax>\n";
}

void VisitorCSHARPML::visit(const structure::CaseSwitchLabelSyntax& node , bool callVirtualBase) {
  createIndentation();
  ofs << "<structure:CaseSwitchLabelSyntax";
  writeAttributes(node,false,true);
  ofs << ">\n";

  writeAttributes(node,true,true);
}

void VisitorCSHARPML::visitEnd(const structure::CaseSwitchLabelSyntax& node , bool callVirtualBase) {
  createIndentation();
  ofs << "</structure:CaseSwitchLabelSyntax>\n";
}

void VisitorCSHARPML::visit(const structure::CatchClauseSyntax& node , bool callVirtualBase) {
  createIndentation();
  ofs << "<structure:CatchClauseSyntax";
  writeAttributes(node,false,true);
  ofs << ">\n";

  writeAttributes(node,true,true);
}

void VisitorCSHARPML::visitEnd(const structure::CatchClauseSyntax& node , bool callVirtualBase) {
  createIndentation();
  ofs << "</structure:CatchClauseSyntax>\n";
}

void VisitorCSHARPML::visit(const structure::CatchDeclarationSyntax& node , bool callVirtualBase) {
  createIndentation();
  ofs << "<structure:CatchDeclarationSyntax";
  writeAttributes(node,false,true);
  ofs << ">\n";

  writeAttributes(node,true,true);
}

void VisitorCSHARPML::visitEnd(const structure::CatchDeclarationSyntax& node , bool callVirtualBase) {
  createIndentation();
  ofs << "</structure:CatchDeclarationSyntax>\n";
}

void VisitorCSHARPML::visit(const structure::CatchFilterClauseSyntax& node , bool callVirtualBase) {
  createIndentation();
  ofs << "<structure:CatchFilterClauseSyntax";
  writeAttributes(node,false,true);
  ofs << ">\n";

  writeAttributes(node,true,true);
}

void VisitorCSHARPML::visitEnd(const structure::CatchFilterClauseSyntax& node , bool callVirtualBase) {
  createIndentation();
  ofs << "</structure:CatchFilterClauseSyntax>\n";
}

void VisitorCSHARPML::visit(const structure::ClassDeclarationSyntax& node , bool callVirtualBase) {
  createIndentation();
  ofs << "<structure:ClassDeclarationSyntax";
  writeAttributes(node,false,true);
  ofs << ">\n";

  writeAttributes(node,true,true);
}

void VisitorCSHARPML::visitEnd(const structure::ClassDeclarationSyntax& node , bool callVirtualBase) {
  createIndentation();
  ofs << "</structure:ClassDeclarationSyntax>\n";
}

void VisitorCSHARPML::visit(const structure::ClassOrStructConstraintSyntax& node , bool callVirtualBase) {
  createIndentation();
  ofs << "<structure:ClassOrStructConstraintSyntax";
  writeAttributes(node,false,true);
  ofs << ">\n";

  writeAttributes(node,true,true);
}

void VisitorCSHARPML::visitEnd(const structure::ClassOrStructConstraintSyntax& node , bool callVirtualBase) {
  createIndentation();
  ofs << "</structure:ClassOrStructConstraintSyntax>\n";
}

void VisitorCSHARPML::visit(const structure::CompilationUnitSyntax& node , bool callVirtualBase) {
  createIndentation();
  ofs << "<structure:CompilationUnitSyntax";
  writeAttributes(node,false,true);
  ofs << ">\n";

  writeAttributes(node,true,true);
}

void VisitorCSHARPML::visitEnd(const structure::CompilationUnitSyntax& node , bool callVirtualBase) {
  createIndentation();
  ofs << "</structure:CompilationUnitSyntax>\n";
}

void VisitorCSHARPML::visit(const structure::ConstantPatternSyntax& node , bool callVirtualBase) {
  createIndentation();
  ofs << "<structure:ConstantPatternSyntax";
  writeAttributes(node,false,true);
  ofs << ">\n";

  writeAttributes(node,true,true);
}

void VisitorCSHARPML::visitEnd(const structure::ConstantPatternSyntax& node , bool callVirtualBase) {
  createIndentation();
  ofs << "</structure:ConstantPatternSyntax>\n";
}

void VisitorCSHARPML::visit(const structure::ConstructorConstraintSyntax& node , bool callVirtualBase) {
  createIndentation();
  ofs << "<structure:ConstructorConstraintSyntax";
  writeAttributes(node,false,true);
  ofs << ">\n";

  writeAttributes(node,true,true);
}

void VisitorCSHARPML::visitEnd(const structure::ConstructorConstraintSyntax& node , bool callVirtualBase) {
  createIndentation();
  ofs << "</structure:ConstructorConstraintSyntax>\n";
}

void VisitorCSHARPML::visit(const structure::ConstructorDeclarationSyntax& node , bool callVirtualBase) {
  createIndentation();
  ofs << "<structure:ConstructorDeclarationSyntax";
  writeAttributes(node,false,true);
  ofs << ">\n";

  writeAttributes(node,true,true);
}

void VisitorCSHARPML::visitEnd(const structure::ConstructorDeclarationSyntax& node , bool callVirtualBase) {
  createIndentation();
  ofs << "</structure:ConstructorDeclarationSyntax>\n";
}

void VisitorCSHARPML::visit(const structure::ConstructorInitializerSyntax& node , bool callVirtualBase) {
  createIndentation();
  ofs << "<structure:ConstructorInitializerSyntax";
  writeAttributes(node,false,true);
  ofs << ">\n";

  writeAttributes(node,true,true);
}

void VisitorCSHARPML::visitEnd(const structure::ConstructorInitializerSyntax& node , bool callVirtualBase) {
  createIndentation();
  ofs << "</structure:ConstructorInitializerSyntax>\n";
}

void VisitorCSHARPML::visit(const structure::ConversionOperatorDeclarationSyntax& node , bool callVirtualBase) {
  createIndentation();
  ofs << "<structure:ConversionOperatorDeclarationSyntax";
  writeAttributes(node,false,true);
  ofs << ">\n";

  writeAttributes(node,true,true);
}

void VisitorCSHARPML::visitEnd(const structure::ConversionOperatorDeclarationSyntax& node , bool callVirtualBase) {
  createIndentation();
  ofs << "</structure:ConversionOperatorDeclarationSyntax>\n";
}

void VisitorCSHARPML::visit(const structure::ConversionOperatorMemberCrefSyntax& node , bool callVirtualBase) {
  createIndentation();
  ofs << "<structure:ConversionOperatorMemberCrefSyntax";
  writeAttributes(node,false,true);
  ofs << ">\n";

  writeAttributes(node,true,true);
}

void VisitorCSHARPML::visitEnd(const structure::ConversionOperatorMemberCrefSyntax& node , bool callVirtualBase) {
  createIndentation();
  ofs << "</structure:ConversionOperatorMemberCrefSyntax>\n";
}

void VisitorCSHARPML::visit(const structure::CrefBracketedParameterListSyntax& node , bool callVirtualBase) {
  createIndentation();
  ofs << "<structure:CrefBracketedParameterListSyntax";
  writeAttributes(node,false,true);
  ofs << ">\n";

  writeAttributes(node,true,true);
}

void VisitorCSHARPML::visitEnd(const structure::CrefBracketedParameterListSyntax& node , bool callVirtualBase) {
  createIndentation();
  ofs << "</structure:CrefBracketedParameterListSyntax>\n";
}

void VisitorCSHARPML::visit(const structure::CrefParameterListSyntax& node , bool callVirtualBase) {
  createIndentation();
  ofs << "<structure:CrefParameterListSyntax";
  writeAttributes(node,false,true);
  ofs << ">\n";

  writeAttributes(node,true,true);
}

void VisitorCSHARPML::visitEnd(const structure::CrefParameterListSyntax& node , bool callVirtualBase) {
  createIndentation();
  ofs << "</structure:CrefParameterListSyntax>\n";
}

void VisitorCSHARPML::visit(const structure::CrefParameterSyntax& node , bool callVirtualBase) {
  createIndentation();
  ofs << "<structure:CrefParameterSyntax";
  writeAttributes(node,false,true);
  ofs << ">\n";

  writeAttributes(node,true,true);
}

void VisitorCSHARPML::visitEnd(const structure::CrefParameterSyntax& node , bool callVirtualBase) {
  createIndentation();
  ofs << "</structure:CrefParameterSyntax>\n";
}

void VisitorCSHARPML::visit(const structure::DeclarationPatternSyntax& node , bool callVirtualBase) {
  createIndentation();
  ofs << "<structure:DeclarationPatternSyntax";
  writeAttributes(node,false,true);
  ofs << ">\n";

  writeAttributes(node,true,true);
}

void VisitorCSHARPML::visitEnd(const structure::DeclarationPatternSyntax& node , bool callVirtualBase) {
  createIndentation();
  ofs << "</structure:DeclarationPatternSyntax>\n";
}

void VisitorCSHARPML::visit(const structure::DefaultSwitchLabelSyntax& node , bool callVirtualBase) {
  createIndentation();
  ofs << "<structure:DefaultSwitchLabelSyntax";
  writeAttributes(node,false,true);
  ofs << ">\n";

  writeAttributes(node,true,true);
}

void VisitorCSHARPML::visitEnd(const structure::DefaultSwitchLabelSyntax& node , bool callVirtualBase) {
  createIndentation();
  ofs << "</structure:DefaultSwitchLabelSyntax>\n";
}

void VisitorCSHARPML::visit(const structure::DelegateDeclarationSyntax& node , bool callVirtualBase) {
  createIndentation();
  ofs << "<structure:DelegateDeclarationSyntax";
  writeAttributes(node,false,true);
  ofs << ">\n";

  writeAttributes(node,true,true);
}

void VisitorCSHARPML::visitEnd(const structure::DelegateDeclarationSyntax& node , bool callVirtualBase) {
  createIndentation();
  ofs << "</structure:DelegateDeclarationSyntax>\n";
}

void VisitorCSHARPML::visit(const structure::DestructorDeclarationSyntax& node , bool callVirtualBase) {
  createIndentation();
  ofs << "<structure:DestructorDeclarationSyntax";
  writeAttributes(node,false,true);
  ofs << ">\n";

  writeAttributes(node,true,true);
}

void VisitorCSHARPML::visitEnd(const structure::DestructorDeclarationSyntax& node , bool callVirtualBase) {
  createIndentation();
  ofs << "</structure:DestructorDeclarationSyntax>\n";
}

void VisitorCSHARPML::visit(const structure::DiscardDesignationSyntax& node , bool callVirtualBase) {
  createIndentation();
  ofs << "<structure:DiscardDesignationSyntax";
  writeAttributes(node,false,true);
  ofs << ">\n";

  writeAttributes(node,true,true);
}

void VisitorCSHARPML::visitEnd(const structure::DiscardDesignationSyntax& node , bool callVirtualBase) {
  createIndentation();
  ofs << "</structure:DiscardDesignationSyntax>\n";
}

void VisitorCSHARPML::visit(const structure::DiscardPatternSyntax& node , bool callVirtualBase) {
  createIndentation();
  ofs << "<structure:DiscardPatternSyntax";
  writeAttributes(node,false,true);
  ofs << ">\n";

  writeAttributes(node,true,true);
}

void VisitorCSHARPML::visitEnd(const structure::DiscardPatternSyntax& node , bool callVirtualBase) {
  createIndentation();
  ofs << "</structure:DiscardPatternSyntax>\n";
}

void VisitorCSHARPML::visit(const structure::ElseClauseSyntax& node , bool callVirtualBase) {
  createIndentation();
  ofs << "<structure:ElseClauseSyntax";
  writeAttributes(node,false,true);
  ofs << ">\n";

  writeAttributes(node,true,true);
}

void VisitorCSHARPML::visitEnd(const structure::ElseClauseSyntax& node , bool callVirtualBase) {
  createIndentation();
  ofs << "</structure:ElseClauseSyntax>\n";
}

void VisitorCSHARPML::visit(const structure::EnumDeclarationSyntax& node , bool callVirtualBase) {
  createIndentation();
  ofs << "<structure:EnumDeclarationSyntax";
  writeAttributes(node,false,true);
  ofs << ">\n";

  writeAttributes(node,true,true);
}

void VisitorCSHARPML::visitEnd(const structure::EnumDeclarationSyntax& node , bool callVirtualBase) {
  createIndentation();
  ofs << "</structure:EnumDeclarationSyntax>\n";
}

void VisitorCSHARPML::visit(const structure::EnumMemberDeclarationSyntax& node , bool callVirtualBase) {
  createIndentation();
  ofs << "<structure:EnumMemberDeclarationSyntax";
  writeAttributes(node,false,true);
  ofs << ">\n";

  writeAttributes(node,true,true);
}

void VisitorCSHARPML::visitEnd(const structure::EnumMemberDeclarationSyntax& node , bool callVirtualBase) {
  createIndentation();
  ofs << "</structure:EnumMemberDeclarationSyntax>\n";
}

void VisitorCSHARPML::visit(const structure::EqualsValueClauseSyntax& node , bool callVirtualBase) {
  createIndentation();
  ofs << "<structure:EqualsValueClauseSyntax";
  writeAttributes(node,false,true);
  ofs << ">\n";

  writeAttributes(node,true,true);
}

void VisitorCSHARPML::visitEnd(const structure::EqualsValueClauseSyntax& node , bool callVirtualBase) {
  createIndentation();
  ofs << "</structure:EqualsValueClauseSyntax>\n";
}

void VisitorCSHARPML::visit(const structure::EventDeclarationSyntax& node , bool callVirtualBase) {
  createIndentation();
  ofs << "<structure:EventDeclarationSyntax";
  writeAttributes(node,false,true);
  ofs << ">\n";

  writeAttributes(node,true,true);
}

void VisitorCSHARPML::visitEnd(const structure::EventDeclarationSyntax& node , bool callVirtualBase) {
  createIndentation();
  ofs << "</structure:EventDeclarationSyntax>\n";
}

void VisitorCSHARPML::visit(const structure::EventFieldDeclarationSyntax& node , bool callVirtualBase) {
  createIndentation();
  ofs << "<structure:EventFieldDeclarationSyntax";
  writeAttributes(node,false,true);
  ofs << ">\n";

  writeAttributes(node,true,true);
}

void VisitorCSHARPML::visitEnd(const structure::EventFieldDeclarationSyntax& node , bool callVirtualBase) {
  createIndentation();
  ofs << "</structure:EventFieldDeclarationSyntax>\n";
}

void VisitorCSHARPML::visit(const structure::ExplicitInterfaceSpecifierSyntax& node , bool callVirtualBase) {
  createIndentation();
  ofs << "<structure:ExplicitInterfaceSpecifierSyntax";
  writeAttributes(node,false,true);
  ofs << ">\n";

  writeAttributes(node,true,true);
}

void VisitorCSHARPML::visitEnd(const structure::ExplicitInterfaceSpecifierSyntax& node , bool callVirtualBase) {
  createIndentation();
  ofs << "</structure:ExplicitInterfaceSpecifierSyntax>\n";
}

void VisitorCSHARPML::visit(const structure::ExternAliasDirectiveSyntax& node , bool callVirtualBase) {
  createIndentation();
  ofs << "<structure:ExternAliasDirectiveSyntax";
  writeAttributes(node,false,true);
  ofs << ">\n";

  writeAttributes(node,true,true);
}

void VisitorCSHARPML::visitEnd(const structure::ExternAliasDirectiveSyntax& node , bool callVirtualBase) {
  createIndentation();
  ofs << "</structure:ExternAliasDirectiveSyntax>\n";
}

void VisitorCSHARPML::visit(const structure::FieldDeclarationSyntax& node , bool callVirtualBase) {
  createIndentation();
  ofs << "<structure:FieldDeclarationSyntax";
  writeAttributes(node,false,true);
  ofs << ">\n";

  writeAttributes(node,true,true);
}

void VisitorCSHARPML::visitEnd(const structure::FieldDeclarationSyntax& node , bool callVirtualBase) {
  createIndentation();
  ofs << "</structure:FieldDeclarationSyntax>\n";
}

void VisitorCSHARPML::visit(const structure::FinallyClauseSyntax& node , bool callVirtualBase) {
  createIndentation();
  ofs << "<structure:FinallyClauseSyntax";
  writeAttributes(node,false,true);
  ofs << ">\n";

  writeAttributes(node,true,true);
}

void VisitorCSHARPML::visitEnd(const structure::FinallyClauseSyntax& node , bool callVirtualBase) {
  createIndentation();
  ofs << "</structure:FinallyClauseSyntax>\n";
}

void VisitorCSHARPML::visit(const structure::FromClauseSyntax& node , bool callVirtualBase) {
  createIndentation();
  ofs << "<structure:FromClauseSyntax";
  writeAttributes(node,false,true);
  ofs << ">\n";

  writeAttributes(node,true,true);
}

void VisitorCSHARPML::visitEnd(const structure::FromClauseSyntax& node , bool callVirtualBase) {
  createIndentation();
  ofs << "</structure:FromClauseSyntax>\n";
}

void VisitorCSHARPML::visit(const structure::GlobalStatementSyntax& node , bool callVirtualBase) {
  createIndentation();
  ofs << "<structure:GlobalStatementSyntax";
  writeAttributes(node,false,true);
  ofs << ">\n";

  writeAttributes(node,true,true);
}

void VisitorCSHARPML::visitEnd(const structure::GlobalStatementSyntax& node , bool callVirtualBase) {
  createIndentation();
  ofs << "</structure:GlobalStatementSyntax>\n";
}

void VisitorCSHARPML::visit(const structure::GroupClauseSyntax& node , bool callVirtualBase) {
  createIndentation();
  ofs << "<structure:GroupClauseSyntax";
  writeAttributes(node,false,true);
  ofs << ">\n";

  writeAttributes(node,true,true);
}

void VisitorCSHARPML::visitEnd(const structure::GroupClauseSyntax& node , bool callVirtualBase) {
  createIndentation();
  ofs << "</structure:GroupClauseSyntax>\n";
}

void VisitorCSHARPML::visit(const structure::IncompleteMemberSyntax& node , bool callVirtualBase) {
  createIndentation();
  ofs << "<structure:IncompleteMemberSyntax";
  writeAttributes(node,false,true);
  ofs << ">\n";

  writeAttributes(node,true,true);
}

void VisitorCSHARPML::visitEnd(const structure::IncompleteMemberSyntax& node , bool callVirtualBase) {
  createIndentation();
  ofs << "</structure:IncompleteMemberSyntax>\n";
}

void VisitorCSHARPML::visit(const structure::IndexerDeclarationSyntax& node , bool callVirtualBase) {
  createIndentation();
  ofs << "<structure:IndexerDeclarationSyntax";
  writeAttributes(node,false,true);
  ofs << ">\n";

  writeAttributes(node,true,true);
}

void VisitorCSHARPML::visitEnd(const structure::IndexerDeclarationSyntax& node , bool callVirtualBase) {
  createIndentation();
  ofs << "</structure:IndexerDeclarationSyntax>\n";
}

void VisitorCSHARPML::visit(const structure::IndexerMemberCrefSyntax& node , bool callVirtualBase) {
  createIndentation();
  ofs << "<structure:IndexerMemberCrefSyntax";
  writeAttributes(node,false,true);
  ofs << ">\n";

  writeAttributes(node,true,true);
}

void VisitorCSHARPML::visitEnd(const structure::IndexerMemberCrefSyntax& node , bool callVirtualBase) {
  createIndentation();
  ofs << "</structure:IndexerMemberCrefSyntax>\n";
}

void VisitorCSHARPML::visit(const structure::InterfaceDeclarationSyntax& node , bool callVirtualBase) {
  createIndentation();
  ofs << "<structure:InterfaceDeclarationSyntax";
  writeAttributes(node,false,true);
  ofs << ">\n";

  writeAttributes(node,true,true);
}

void VisitorCSHARPML::visitEnd(const structure::InterfaceDeclarationSyntax& node , bool callVirtualBase) {
  createIndentation();
  ofs << "</structure:InterfaceDeclarationSyntax>\n";
}

void VisitorCSHARPML::visit(const structure::InterpolatedStringTextSyntax& node , bool callVirtualBase) {
  createIndentation();
  ofs << "<structure:InterpolatedStringTextSyntax";
  writeAttributes(node,false,true);
  ofs << ">\n";

  writeAttributes(node,true,true);
}

void VisitorCSHARPML::visitEnd(const structure::InterpolatedStringTextSyntax& node , bool callVirtualBase) {
  createIndentation();
  ofs << "</structure:InterpolatedStringTextSyntax>\n";
}

void VisitorCSHARPML::visit(const structure::InterpolationAlignmentClauseSyntax& node , bool callVirtualBase) {
  createIndentation();
  ofs << "<structure:InterpolationAlignmentClauseSyntax";
  writeAttributes(node,false,true);
  ofs << ">\n";

  writeAttributes(node,true,true);
}

void VisitorCSHARPML::visitEnd(const structure::InterpolationAlignmentClauseSyntax& node , bool callVirtualBase) {
  createIndentation();
  ofs << "</structure:InterpolationAlignmentClauseSyntax>\n";
}

void VisitorCSHARPML::visit(const structure::InterpolationFormatClauseSyntax& node , bool callVirtualBase) {
  createIndentation();
  ofs << "<structure:InterpolationFormatClauseSyntax";
  writeAttributes(node,false,true);
  ofs << ">\n";

  writeAttributes(node,true,true);
}

void VisitorCSHARPML::visitEnd(const structure::InterpolationFormatClauseSyntax& node , bool callVirtualBase) {
  createIndentation();
  ofs << "</structure:InterpolationFormatClauseSyntax>\n";
}

void VisitorCSHARPML::visit(const structure::InterpolationSyntax& node , bool callVirtualBase) {
  createIndentation();
  ofs << "<structure:InterpolationSyntax";
  writeAttributes(node,false,true);
  ofs << ">\n";

  writeAttributes(node,true,true);
}

void VisitorCSHARPML::visitEnd(const structure::InterpolationSyntax& node , bool callVirtualBase) {
  createIndentation();
  ofs << "</structure:InterpolationSyntax>\n";
}

void VisitorCSHARPML::visit(const structure::JoinClauseSyntax& node , bool callVirtualBase) {
  createIndentation();
  ofs << "<structure:JoinClauseSyntax";
  writeAttributes(node,false,true);
  ofs << ">\n";

  writeAttributes(node,true,true);
}

void VisitorCSHARPML::visitEnd(const structure::JoinClauseSyntax& node , bool callVirtualBase) {
  createIndentation();
  ofs << "</structure:JoinClauseSyntax>\n";
}

void VisitorCSHARPML::visit(const structure::JoinIntoClauseSyntax& node , bool callVirtualBase) {
  createIndentation();
  ofs << "<structure:JoinIntoClauseSyntax";
  writeAttributes(node,false,true);
  ofs << ">\n";

  writeAttributes(node,true,true);
}

void VisitorCSHARPML::visitEnd(const structure::JoinIntoClauseSyntax& node , bool callVirtualBase) {
  createIndentation();
  ofs << "</structure:JoinIntoClauseSyntax>\n";
}

void VisitorCSHARPML::visit(const structure::LetClauseSyntax& node , bool callVirtualBase) {
  createIndentation();
  ofs << "<structure:LetClauseSyntax";
  writeAttributes(node,false,true);
  ofs << ">\n";

  writeAttributes(node,true,true);
}

void VisitorCSHARPML::visitEnd(const structure::LetClauseSyntax& node , bool callVirtualBase) {
  createIndentation();
  ofs << "</structure:LetClauseSyntax>\n";
}

void VisitorCSHARPML::visit(const structure::MethodDeclarationSyntax& node , bool callVirtualBase) {
  createIndentation();
  ofs << "<structure:MethodDeclarationSyntax";
  writeAttributes(node,false,true);
  ofs << ">\n";

  writeAttributes(node,true,true);
}

void VisitorCSHARPML::visitEnd(const structure::MethodDeclarationSyntax& node , bool callVirtualBase) {
  createIndentation();
  ofs << "</structure:MethodDeclarationSyntax>\n";
}

void VisitorCSHARPML::visit(const structure::NameColonSyntax& node , bool callVirtualBase) {
  createIndentation();
  ofs << "<structure:NameColonSyntax";
  writeAttributes(node,false,true);
  ofs << ">\n";

  writeAttributes(node,true,true);
}

void VisitorCSHARPML::visitEnd(const structure::NameColonSyntax& node , bool callVirtualBase) {
  createIndentation();
  ofs << "</structure:NameColonSyntax>\n";
}

void VisitorCSHARPML::visit(const structure::NameEqualsSyntax& node , bool callVirtualBase) {
  createIndentation();
  ofs << "<structure:NameEqualsSyntax";
  writeAttributes(node,false,true);
  ofs << ">\n";

  writeAttributes(node,true,true);
}

void VisitorCSHARPML::visitEnd(const structure::NameEqualsSyntax& node , bool callVirtualBase) {
  createIndentation();
  ofs << "</structure:NameEqualsSyntax>\n";
}

void VisitorCSHARPML::visit(const structure::NameMemberCrefSyntax& node , bool callVirtualBase) {
  createIndentation();
  ofs << "<structure:NameMemberCrefSyntax";
  writeAttributes(node,false,true);
  ofs << ">\n";

  writeAttributes(node,true,true);
}

void VisitorCSHARPML::visitEnd(const structure::NameMemberCrefSyntax& node , bool callVirtualBase) {
  createIndentation();
  ofs << "</structure:NameMemberCrefSyntax>\n";
}

void VisitorCSHARPML::visit(const structure::NamespaceDeclarationSyntax& node , bool callVirtualBase) {
  createIndentation();
  ofs << "<structure:NamespaceDeclarationSyntax";
  writeAttributes(node,false,true);
  ofs << ">\n";

  writeAttributes(node,true,true);
}

void VisitorCSHARPML::visitEnd(const structure::NamespaceDeclarationSyntax& node , bool callVirtualBase) {
  createIndentation();
  ofs << "</structure:NamespaceDeclarationSyntax>\n";
}

void VisitorCSHARPML::visit(const structure::OperatorDeclarationSyntax& node , bool callVirtualBase) {
  createIndentation();
  ofs << "<structure:OperatorDeclarationSyntax";
  writeAttributes(node,false,true);
  ofs << ">\n";

  writeAttributes(node,true,true);
}

void VisitorCSHARPML::visitEnd(const structure::OperatorDeclarationSyntax& node , bool callVirtualBase) {
  createIndentation();
  ofs << "</structure:OperatorDeclarationSyntax>\n";
}

void VisitorCSHARPML::visit(const structure::OperatorMemberCrefSyntax& node , bool callVirtualBase) {
  createIndentation();
  ofs << "<structure:OperatorMemberCrefSyntax";
  writeAttributes(node,false,true);
  ofs << ">\n";

  writeAttributes(node,true,true);
}

void VisitorCSHARPML::visitEnd(const structure::OperatorMemberCrefSyntax& node , bool callVirtualBase) {
  createIndentation();
  ofs << "</structure:OperatorMemberCrefSyntax>\n";
}

void VisitorCSHARPML::visit(const structure::OrderByClauseSyntax& node , bool callVirtualBase) {
  createIndentation();
  ofs << "<structure:OrderByClauseSyntax";
  writeAttributes(node,false,true);
  ofs << ">\n";

  writeAttributes(node,true,true);
}

void VisitorCSHARPML::visitEnd(const structure::OrderByClauseSyntax& node , bool callVirtualBase) {
  createIndentation();
  ofs << "</structure:OrderByClauseSyntax>\n";
}

void VisitorCSHARPML::visit(const structure::OrderingSyntax& node , bool callVirtualBase) {
  createIndentation();
  ofs << "<structure:OrderingSyntax";
  writeAttributes(node,false,true);
  ofs << ">\n";

  writeAttributes(node,true,true);
}

void VisitorCSHARPML::visitEnd(const structure::OrderingSyntax& node , bool callVirtualBase) {
  createIndentation();
  ofs << "</structure:OrderingSyntax>\n";
}

void VisitorCSHARPML::visit(const structure::ParameterListSyntax& node , bool callVirtualBase) {
  createIndentation();
  ofs << "<structure:ParameterListSyntax";
  writeAttributes(node,false,true);
  ofs << ">\n";

  writeAttributes(node,true,true);
}

void VisitorCSHARPML::visitEnd(const structure::ParameterListSyntax& node , bool callVirtualBase) {
  createIndentation();
  ofs << "</structure:ParameterListSyntax>\n";
}

void VisitorCSHARPML::visit(const structure::ParameterSyntax& node , bool callVirtualBase) {
  createIndentation();
  ofs << "<structure:ParameterSyntax";
  writeAttributes(node,false,true);
  ofs << ">\n";

  writeAttributes(node,true,true);
}

void VisitorCSHARPML::visitEnd(const structure::ParameterSyntax& node , bool callVirtualBase) {
  createIndentation();
  ofs << "</structure:ParameterSyntax>\n";
}

void VisitorCSHARPML::visit(const structure::ParenthesizedVariableDesignationSyntax& node , bool callVirtualBase) {
  createIndentation();
  ofs << "<structure:ParenthesizedVariableDesignationSyntax";
  writeAttributes(node,false,true);
  ofs << ">\n";

  writeAttributes(node,true,true);
}

void VisitorCSHARPML::visitEnd(const structure::ParenthesizedVariableDesignationSyntax& node , bool callVirtualBase) {
  createIndentation();
  ofs << "</structure:ParenthesizedVariableDesignationSyntax>\n";
}

void VisitorCSHARPML::visit(const structure::PositionalPatternClauseSyntax& node , bool callVirtualBase) {
  createIndentation();
  ofs << "<structure:PositionalPatternClauseSyntax";
  writeAttributes(node,false,true);
  ofs << ">\n";

  writeAttributes(node,true,true);
}

void VisitorCSHARPML::visitEnd(const structure::PositionalPatternClauseSyntax& node , bool callVirtualBase) {
  createIndentation();
  ofs << "</structure:PositionalPatternClauseSyntax>\n";
}

void VisitorCSHARPML::visit(const structure::PropertyDeclarationSyntax& node , bool callVirtualBase) {
  createIndentation();
  ofs << "<structure:PropertyDeclarationSyntax";
  writeAttributes(node,false,true);
  ofs << ">\n";

  writeAttributes(node,true,true);
}

void VisitorCSHARPML::visitEnd(const structure::PropertyDeclarationSyntax& node , bool callVirtualBase) {
  createIndentation();
  ofs << "</structure:PropertyDeclarationSyntax>\n";
}

void VisitorCSHARPML::visit(const structure::PropertyPatternClauseSyntax& node , bool callVirtualBase) {
  createIndentation();
  ofs << "<structure:PropertyPatternClauseSyntax";
  writeAttributes(node,false,true);
  ofs << ">\n";

  writeAttributes(node,true,true);
}

void VisitorCSHARPML::visitEnd(const structure::PropertyPatternClauseSyntax& node , bool callVirtualBase) {
  createIndentation();
  ofs << "</structure:PropertyPatternClauseSyntax>\n";
}

void VisitorCSHARPML::visit(const structure::QualifiedCrefSyntax& node , bool callVirtualBase) {
  createIndentation();
  ofs << "<structure:QualifiedCrefSyntax";
  writeAttributes(node,false,true);
  ofs << ">\n";

  writeAttributes(node,true,true);
}

void VisitorCSHARPML::visitEnd(const structure::QualifiedCrefSyntax& node , bool callVirtualBase) {
  createIndentation();
  ofs << "</structure:QualifiedCrefSyntax>\n";
}

void VisitorCSHARPML::visit(const structure::QueryBodySyntax& node , bool callVirtualBase) {
  createIndentation();
  ofs << "<structure:QueryBodySyntax";
  writeAttributes(node,false,true);
  ofs << ">\n";

  writeAttributes(node,true,true);
}

void VisitorCSHARPML::visitEnd(const structure::QueryBodySyntax& node , bool callVirtualBase) {
  createIndentation();
  ofs << "</structure:QueryBodySyntax>\n";
}

void VisitorCSHARPML::visit(const structure::QueryContinuationSyntax& node , bool callVirtualBase) {
  createIndentation();
  ofs << "<structure:QueryContinuationSyntax";
  writeAttributes(node,false,true);
  ofs << ">\n";

  writeAttributes(node,true,true);
}

void VisitorCSHARPML::visitEnd(const structure::QueryContinuationSyntax& node , bool callVirtualBase) {
  createIndentation();
  ofs << "</structure:QueryContinuationSyntax>\n";
}

void VisitorCSHARPML::visit(const structure::RecursivePatternSyntax& node , bool callVirtualBase) {
  createIndentation();
  ofs << "<structure:RecursivePatternSyntax";
  writeAttributes(node,false,true);
  ofs << ">\n";

  writeAttributes(node,true,true);
}

void VisitorCSHARPML::visitEnd(const structure::RecursivePatternSyntax& node , bool callVirtualBase) {
  createIndentation();
  ofs << "</structure:RecursivePatternSyntax>\n";
}

void VisitorCSHARPML::visit(const structure::SelectClauseSyntax& node , bool callVirtualBase) {
  createIndentation();
  ofs << "<structure:SelectClauseSyntax";
  writeAttributes(node,false,true);
  ofs << ">\n";

  writeAttributes(node,true,true);
}

void VisitorCSHARPML::visitEnd(const structure::SelectClauseSyntax& node , bool callVirtualBase) {
  createIndentation();
  ofs << "</structure:SelectClauseSyntax>\n";
}

void VisitorCSHARPML::visit(const structure::SimpleBaseTypeSyntax& node , bool callVirtualBase) {
  createIndentation();
  ofs << "<structure:SimpleBaseTypeSyntax";
  writeAttributes(node,false,true);
  ofs << ">\n";

  writeAttributes(node,true,true);
}

void VisitorCSHARPML::visitEnd(const structure::SimpleBaseTypeSyntax& node , bool callVirtualBase) {
  createIndentation();
  ofs << "</structure:SimpleBaseTypeSyntax>\n";
}

void VisitorCSHARPML::visit(const structure::SingleVariableDesignationSyntax& node , bool callVirtualBase) {
  createIndentation();
  ofs << "<structure:SingleVariableDesignationSyntax";
  writeAttributes(node,false,true);
  ofs << ">\n";

  writeAttributes(node,true,true);
}

void VisitorCSHARPML::visitEnd(const structure::SingleVariableDesignationSyntax& node , bool callVirtualBase) {
  createIndentation();
  ofs << "</structure:SingleVariableDesignationSyntax>\n";
}

void VisitorCSHARPML::visit(const structure::StructDeclarationSyntax& node , bool callVirtualBase) {
  createIndentation();
  ofs << "<structure:StructDeclarationSyntax";
  writeAttributes(node,false,true);
  ofs << ">\n";

  writeAttributes(node,true,true);
}

void VisitorCSHARPML::visitEnd(const structure::StructDeclarationSyntax& node , bool callVirtualBase) {
  createIndentation();
  ofs << "</structure:StructDeclarationSyntax>\n";
}

void VisitorCSHARPML::visit(const structure::SubpatternSyntax& node , bool callVirtualBase) {
  createIndentation();
  ofs << "<structure:SubpatternSyntax";
  writeAttributes(node,false,true);
  ofs << ">\n";

  writeAttributes(node,true,true);
}

void VisitorCSHARPML::visitEnd(const structure::SubpatternSyntax& node , bool callVirtualBase) {
  createIndentation();
  ofs << "</structure:SubpatternSyntax>\n";
}

void VisitorCSHARPML::visit(const structure::SwitchExpressionArmSyntax& node , bool callVirtualBase) {
  createIndentation();
  ofs << "<structure:SwitchExpressionArmSyntax";
  writeAttributes(node,false,true);
  ofs << ">\n";

  writeAttributes(node,true,true);
}

void VisitorCSHARPML::visitEnd(const structure::SwitchExpressionArmSyntax& node , bool callVirtualBase) {
  createIndentation();
  ofs << "</structure:SwitchExpressionArmSyntax>\n";
}

void VisitorCSHARPML::visit(const structure::SwitchSectionSyntax& node , bool callVirtualBase) {
  createIndentation();
  ofs << "<structure:SwitchSectionSyntax";
  writeAttributes(node,false,true);
  ofs << ">\n";

  writeAttributes(node,true,true);
}

void VisitorCSHARPML::visitEnd(const structure::SwitchSectionSyntax& node , bool callVirtualBase) {
  createIndentation();
  ofs << "</structure:SwitchSectionSyntax>\n";
}

void VisitorCSHARPML::visit(const structure::SyntaxToken& node , bool callVirtualBase) {
  createIndentation();
  ofs << "<structure:SyntaxToken";
  writeAttributes(node,false,true);
  ofs << ">\n";

  writeAttributes(node,true,true);
}

void VisitorCSHARPML::visitEnd(const structure::SyntaxToken& node , bool callVirtualBase) {
  createIndentation();
  ofs << "</structure:SyntaxToken>\n";
}

void VisitorCSHARPML::visit(const structure::TupleElementSyntax& node , bool callVirtualBase) {
  createIndentation();
  ofs << "<structure:TupleElementSyntax";
  writeAttributes(node,false,true);
  ofs << ">\n";

  writeAttributes(node,true,true);
}

void VisitorCSHARPML::visitEnd(const structure::TupleElementSyntax& node , bool callVirtualBase) {
  createIndentation();
  ofs << "</structure:TupleElementSyntax>\n";
}

void VisitorCSHARPML::visit(const structure::TypeArgumentListSyntax& node , bool callVirtualBase) {
  createIndentation();
  ofs << "<structure:TypeArgumentListSyntax";
  writeAttributes(node,false,true);
  ofs << ">\n";

  writeAttributes(node,true,true);
}

void VisitorCSHARPML::visitEnd(const structure::TypeArgumentListSyntax& node , bool callVirtualBase) {
  createIndentation();
  ofs << "</structure:TypeArgumentListSyntax>\n";
}

void VisitorCSHARPML::visit(const structure::TypeConstraintSyntax& node , bool callVirtualBase) {
  createIndentation();
  ofs << "<structure:TypeConstraintSyntax";
  writeAttributes(node,false,true);
  ofs << ">\n";

  writeAttributes(node,true,true);
}

void VisitorCSHARPML::visitEnd(const structure::TypeConstraintSyntax& node , bool callVirtualBase) {
  createIndentation();
  ofs << "</structure:TypeConstraintSyntax>\n";
}

void VisitorCSHARPML::visit(const structure::TypeCrefSyntax& node , bool callVirtualBase) {
  createIndentation();
  ofs << "<structure:TypeCrefSyntax";
  writeAttributes(node,false,true);
  ofs << ">\n";

  writeAttributes(node,true,true);
}

void VisitorCSHARPML::visitEnd(const structure::TypeCrefSyntax& node , bool callVirtualBase) {
  createIndentation();
  ofs << "</structure:TypeCrefSyntax>\n";
}

void VisitorCSHARPML::visit(const structure::TypeParameterConstraintClauseSyntax& node , bool callVirtualBase) {
  createIndentation();
  ofs << "<structure:TypeParameterConstraintClauseSyntax";
  writeAttributes(node,false,true);
  ofs << ">\n";

  writeAttributes(node,true,true);
}

void VisitorCSHARPML::visitEnd(const structure::TypeParameterConstraintClauseSyntax& node , bool callVirtualBase) {
  createIndentation();
  ofs << "</structure:TypeParameterConstraintClauseSyntax>\n";
}

void VisitorCSHARPML::visit(const structure::TypeParameterListSyntax& node , bool callVirtualBase) {
  createIndentation();
  ofs << "<structure:TypeParameterListSyntax";
  writeAttributes(node,false,true);
  ofs << ">\n";

  writeAttributes(node,true,true);
}

void VisitorCSHARPML::visitEnd(const structure::TypeParameterListSyntax& node , bool callVirtualBase) {
  createIndentation();
  ofs << "</structure:TypeParameterListSyntax>\n";
}

void VisitorCSHARPML::visit(const structure::TypeParameterSyntax& node , bool callVirtualBase) {
  createIndentation();
  ofs << "<structure:TypeParameterSyntax";
  writeAttributes(node,false,true);
  ofs << ">\n";

  writeAttributes(node,true,true);
}

void VisitorCSHARPML::visitEnd(const structure::TypeParameterSyntax& node , bool callVirtualBase) {
  createIndentation();
  ofs << "</structure:TypeParameterSyntax>\n";
}

void VisitorCSHARPML::visit(const structure::UsingDirectiveSyntax& node , bool callVirtualBase) {
  createIndentation();
  ofs << "<structure:UsingDirectiveSyntax";
  writeAttributes(node,false,true);
  ofs << ">\n";

  writeAttributes(node,true,true);
}

void VisitorCSHARPML::visitEnd(const structure::UsingDirectiveSyntax& node , bool callVirtualBase) {
  createIndentation();
  ofs << "</structure:UsingDirectiveSyntax>\n";
}

void VisitorCSHARPML::visit(const structure::VarPatternSyntax& node , bool callVirtualBase) {
  createIndentation();
  ofs << "<structure:VarPatternSyntax";
  writeAttributes(node,false,true);
  ofs << ">\n";

  writeAttributes(node,true,true);
}

void VisitorCSHARPML::visitEnd(const structure::VarPatternSyntax& node , bool callVirtualBase) {
  createIndentation();
  ofs << "</structure:VarPatternSyntax>\n";
}

void VisitorCSHARPML::visit(const structure::VariableDeclarationSyntax& node , bool callVirtualBase) {
  createIndentation();
  ofs << "<structure:VariableDeclarationSyntax";
  writeAttributes(node,false,true);
  ofs << ">\n";

  writeAttributes(node,true,true);
}

void VisitorCSHARPML::visitEnd(const structure::VariableDeclarationSyntax& node , bool callVirtualBase) {
  createIndentation();
  ofs << "</structure:VariableDeclarationSyntax>\n";
}

void VisitorCSHARPML::visit(const structure::VariableDeclaratorSyntax& node , bool callVirtualBase) {
  createIndentation();
  ofs << "<structure:VariableDeclaratorSyntax";
  writeAttributes(node,false,true);
  ofs << ">\n";

  writeAttributes(node,true,true);
}

void VisitorCSHARPML::visitEnd(const structure::VariableDeclaratorSyntax& node , bool callVirtualBase) {
  createIndentation();
  ofs << "</structure:VariableDeclaratorSyntax>\n";
}

void VisitorCSHARPML::visit(const structure::WhenClauseSyntax& node , bool callVirtualBase) {
  createIndentation();
  ofs << "<structure:WhenClauseSyntax";
  writeAttributes(node,false,true);
  ofs << ">\n";

  writeAttributes(node,true,true);
}

void VisitorCSHARPML::visitEnd(const structure::WhenClauseSyntax& node , bool callVirtualBase) {
  createIndentation();
  ofs << "</structure:WhenClauseSyntax>\n";
}

void VisitorCSHARPML::visit(const structure::WhereClauseSyntax& node , bool callVirtualBase) {
  createIndentation();
  ofs << "<structure:WhereClauseSyntax";
  writeAttributes(node,false,true);
  ofs << ">\n";

  writeAttributes(node,true,true);
}

void VisitorCSHARPML::visitEnd(const structure::WhereClauseSyntax& node , bool callVirtualBase) {
  createIndentation();
  ofs << "</structure:WhereClauseSyntax>\n";
}

void VisitorCSHARPML::visit(const structure::XmlCDataSectionSyntax& node , bool callVirtualBase) {
  createIndentation();
  ofs << "<structure:XmlCDataSectionSyntax";
  writeAttributes(node,false,true);
  ofs << ">\n";

  writeAttributes(node,true,true);
}

void VisitorCSHARPML::visitEnd(const structure::XmlCDataSectionSyntax& node , bool callVirtualBase) {
  createIndentation();
  ofs << "</structure:XmlCDataSectionSyntax>\n";
}

void VisitorCSHARPML::visit(const structure::XmlCommentSyntax& node , bool callVirtualBase) {
  createIndentation();
  ofs << "<structure:XmlCommentSyntax";
  writeAttributes(node,false,true);
  ofs << ">\n";

  writeAttributes(node,true,true);
}

void VisitorCSHARPML::visitEnd(const structure::XmlCommentSyntax& node , bool callVirtualBase) {
  createIndentation();
  ofs << "</structure:XmlCommentSyntax>\n";
}

void VisitorCSHARPML::visit(const structure::XmlCrefAttributeSyntax& node , bool callVirtualBase) {
  createIndentation();
  ofs << "<structure:XmlCrefAttributeSyntax";
  writeAttributes(node,false,true);
  ofs << ">\n";

  writeAttributes(node,true,true);
}

void VisitorCSHARPML::visitEnd(const structure::XmlCrefAttributeSyntax& node , bool callVirtualBase) {
  createIndentation();
  ofs << "</structure:XmlCrefAttributeSyntax>\n";
}

void VisitorCSHARPML::visit(const structure::XmlElementEndTagSyntax& node , bool callVirtualBase) {
  createIndentation();
  ofs << "<structure:XmlElementEndTagSyntax";
  writeAttributes(node,false,true);
  ofs << ">\n";

  writeAttributes(node,true,true);
}

void VisitorCSHARPML::visitEnd(const structure::XmlElementEndTagSyntax& node , bool callVirtualBase) {
  createIndentation();
  ofs << "</structure:XmlElementEndTagSyntax>\n";
}

void VisitorCSHARPML::visit(const structure::XmlElementStartTagSyntax& node , bool callVirtualBase) {
  createIndentation();
  ofs << "<structure:XmlElementStartTagSyntax";
  writeAttributes(node,false,true);
  ofs << ">\n";

  writeAttributes(node,true,true);
}

void VisitorCSHARPML::visitEnd(const structure::XmlElementStartTagSyntax& node , bool callVirtualBase) {
  createIndentation();
  ofs << "</structure:XmlElementStartTagSyntax>\n";
}

void VisitorCSHARPML::visit(const structure::XmlElementSyntax& node , bool callVirtualBase) {
  createIndentation();
  ofs << "<structure:XmlElementSyntax";
  writeAttributes(node,false,true);
  ofs << ">\n";

  writeAttributes(node,true,true);
}

void VisitorCSHARPML::visitEnd(const structure::XmlElementSyntax& node , bool callVirtualBase) {
  createIndentation();
  ofs << "</structure:XmlElementSyntax>\n";
}

void VisitorCSHARPML::visit(const structure::XmlEmptyElementSyntax& node , bool callVirtualBase) {
  createIndentation();
  ofs << "<structure:XmlEmptyElementSyntax";
  writeAttributes(node,false,true);
  ofs << ">\n";

  writeAttributes(node,true,true);
}

void VisitorCSHARPML::visitEnd(const structure::XmlEmptyElementSyntax& node , bool callVirtualBase) {
  createIndentation();
  ofs << "</structure:XmlEmptyElementSyntax>\n";
}

void VisitorCSHARPML::visit(const structure::XmlNameAttributeSyntax& node , bool callVirtualBase) {
  createIndentation();
  ofs << "<structure:XmlNameAttributeSyntax";
  writeAttributes(node,false,true);
  ofs << ">\n";

  writeAttributes(node,true,true);
}

void VisitorCSHARPML::visitEnd(const structure::XmlNameAttributeSyntax& node , bool callVirtualBase) {
  createIndentation();
  ofs << "</structure:XmlNameAttributeSyntax>\n";
}

void VisitorCSHARPML::visit(const structure::XmlNameSyntax& node , bool callVirtualBase) {
  createIndentation();
  ofs << "<structure:XmlNameSyntax";
  writeAttributes(node,false,true);
  ofs << ">\n";

  writeAttributes(node,true,true);
}

void VisitorCSHARPML::visitEnd(const structure::XmlNameSyntax& node , bool callVirtualBase) {
  createIndentation();
  ofs << "</structure:XmlNameSyntax>\n";
}

void VisitorCSHARPML::visit(const structure::XmlPrefixSyntax& node , bool callVirtualBase) {
  createIndentation();
  ofs << "<structure:XmlPrefixSyntax";
  writeAttributes(node,false,true);
  ofs << ">\n";

  writeAttributes(node,true,true);
}

void VisitorCSHARPML::visitEnd(const structure::XmlPrefixSyntax& node , bool callVirtualBase) {
  createIndentation();
  ofs << "</structure:XmlPrefixSyntax>\n";
}

void VisitorCSHARPML::visit(const structure::XmlProcessingInstructionSyntax& node , bool callVirtualBase) {
  createIndentation();
  ofs << "<structure:XmlProcessingInstructionSyntax";
  writeAttributes(node,false,true);
  ofs << ">\n";

  writeAttributes(node,true,true);
}

void VisitorCSHARPML::visitEnd(const structure::XmlProcessingInstructionSyntax& node , bool callVirtualBase) {
  createIndentation();
  ofs << "</structure:XmlProcessingInstructionSyntax>\n";
}

void VisitorCSHARPML::visit(const structure::XmlTextAttributeSyntax& node , bool callVirtualBase) {
  createIndentation();
  ofs << "<structure:XmlTextAttributeSyntax";
  writeAttributes(node,false,true);
  ofs << ">\n";

  writeAttributes(node,true,true);
}

void VisitorCSHARPML::visitEnd(const structure::XmlTextAttributeSyntax& node , bool callVirtualBase) {
  createIndentation();
  ofs << "</structure:XmlTextAttributeSyntax>\n";
}

void VisitorCSHARPML::visit(const structure::XmlTextSyntax& node , bool callVirtualBase) {
  createIndentation();
  ofs << "<structure:XmlTextSyntax";
  writeAttributes(node,false,true);
  ofs << ">\n";

  writeAttributes(node,true,true);
}

void VisitorCSHARPML::visitEnd(const structure::XmlTextSyntax& node , bool callVirtualBase) {
  createIndentation();
  ofs << "</structure:XmlTextSyntax>\n";
}

void VisitorCSHARPML::visitAliasQualifiedNameSyntax_Alias(const expression::AliasQualifiedNameSyntax& begin, const expression::IdentifierNameSyntax& end) {
  createIndentation();
  ofs << "<AliasQualifiedNameSyntax_Alias>\n";
  incDepth();
}

void VisitorCSHARPML::visitEndAliasQualifiedNameSyntax_Alias(const expression::AliasQualifiedNameSyntax& begin, const expression::IdentifierNameSyntax& end) {
  decDepth();
  createIndentation();
  ofs << "</AliasQualifiedNameSyntax_Alias>\n";
}

void VisitorCSHARPML::visitAliasQualifiedNameSyntax_Name(const expression::AliasQualifiedNameSyntax& begin, const expression::SimpleNameSyntax& end) {
  createIndentation();
  ofs << "<AliasQualifiedNameSyntax_Name>\n";
  incDepth();
}

void VisitorCSHARPML::visitEndAliasQualifiedNameSyntax_Name(const expression::AliasQualifiedNameSyntax& begin, const expression::SimpleNameSyntax& end) {
  decDepth();
  createIndentation();
  ofs << "</AliasQualifiedNameSyntax_Name>\n";
}

void VisitorCSHARPML::visitAnonymousFunctionExpressionSyntax_Block(const expression::AnonymousFunctionExpressionSyntax& begin, const statement::BlockSyntax& end) {
  createIndentation();
  ofs << "<AnonymousFunctionExpressionSyntax_Block>\n";
  incDepth();
}

void VisitorCSHARPML::visitEndAnonymousFunctionExpressionSyntax_Block(const expression::AnonymousFunctionExpressionSyntax& begin, const statement::BlockSyntax& end) {
  decDepth();
  createIndentation();
  ofs << "</AnonymousFunctionExpressionSyntax_Block>\n";
}

void VisitorCSHARPML::visitAnonymousFunctionExpressionSyntax_ExpressionBody(const expression::AnonymousFunctionExpressionSyntax& begin, const expression::ExpressionSyntax& end) {
  createIndentation();
  ofs << "<AnonymousFunctionExpressionSyntax_ExpressionBody>\n";
  incDepth();
}

void VisitorCSHARPML::visitEndAnonymousFunctionExpressionSyntax_ExpressionBody(const expression::AnonymousFunctionExpressionSyntax& begin, const expression::ExpressionSyntax& end) {
  decDepth();
  createIndentation();
  ofs << "</AnonymousFunctionExpressionSyntax_ExpressionBody>\n";
}

void VisitorCSHARPML::visitAnonymousMethodExpressionSyntax_ParameterList(const expression::AnonymousMethodExpressionSyntax& begin, const structure::ParameterListSyntax& end) {
  createIndentation();
  ofs << "<AnonymousMethodExpressionSyntax_ParameterList>\n";
  incDepth();
}

void VisitorCSHARPML::visitEndAnonymousMethodExpressionSyntax_ParameterList(const expression::AnonymousMethodExpressionSyntax& begin, const structure::ParameterListSyntax& end) {
  decDepth();
  createIndentation();
  ofs << "</AnonymousMethodExpressionSyntax_ParameterList>\n";
}

void VisitorCSHARPML::visitAnonymousObjectCreationExpressionSyntax_Initializers(const expression::AnonymousObjectCreationExpressionSyntax& begin, const structure::AnonymousObjectMemberDeclaratorSyntax& end) {
  createIndentation();
  ofs << "<AnonymousObjectCreationExpressionSyntax_Initializers>\n";
  incDepth();
}

void VisitorCSHARPML::visitEndAnonymousObjectCreationExpressionSyntax_Initializers(const expression::AnonymousObjectCreationExpressionSyntax& begin, const structure::AnonymousObjectMemberDeclaratorSyntax& end) {
  decDepth();
  createIndentation();
  ofs << "</AnonymousObjectCreationExpressionSyntax_Initializers>\n";
}

void VisitorCSHARPML::visitArrayCreationExpressionSyntax_Initializer(const expression::ArrayCreationExpressionSyntax& begin, const expression::InitializerExpressionSyntax& end) {
  createIndentation();
  ofs << "<ArrayCreationExpressionSyntax_Initializer>\n";
  incDepth();
}

void VisitorCSHARPML::visitEndArrayCreationExpressionSyntax_Initializer(const expression::ArrayCreationExpressionSyntax& begin, const expression::InitializerExpressionSyntax& end) {
  decDepth();
  createIndentation();
  ofs << "</ArrayCreationExpressionSyntax_Initializer>\n";
}

void VisitorCSHARPML::visitArrayCreationExpressionSyntax_Type(const expression::ArrayCreationExpressionSyntax& begin, const expression::ArrayTypeSyntax& end) {
  createIndentation();
  ofs << "<ArrayCreationExpressionSyntax_Type>\n";
  incDepth();
}

void VisitorCSHARPML::visitEndArrayCreationExpressionSyntax_Type(const expression::ArrayCreationExpressionSyntax& begin, const expression::ArrayTypeSyntax& end) {
  decDepth();
  createIndentation();
  ofs << "</ArrayCreationExpressionSyntax_Type>\n";
}

void VisitorCSHARPML::visitArrayTypeSyntax_ElementType(const expression::ArrayTypeSyntax& begin, const expression::TypeSyntax& end) {
  createIndentation();
  ofs << "<ArrayTypeSyntax_ElementType>\n";
  incDepth();
}

void VisitorCSHARPML::visitEndArrayTypeSyntax_ElementType(const expression::ArrayTypeSyntax& begin, const expression::TypeSyntax& end) {
  decDepth();
  createIndentation();
  ofs << "</ArrayTypeSyntax_ElementType>\n";
}

void VisitorCSHARPML::visitArrayTypeSyntax_RankSpecifiers(const expression::ArrayTypeSyntax& begin, const structure::ArrayRankSpecifierSyntax& end) {
  createIndentation();
  ofs << "<ArrayTypeSyntax_RankSpecifiers>\n";
  incDepth();
}

void VisitorCSHARPML::visitEndArrayTypeSyntax_RankSpecifiers(const expression::ArrayTypeSyntax& begin, const structure::ArrayRankSpecifierSyntax& end) {
  decDepth();
  createIndentation();
  ofs << "</ArrayTypeSyntax_RankSpecifiers>\n";
}

void VisitorCSHARPML::visitAssignmentExpressionSyntax_EventAccessorCall(const expression::AssignmentExpressionSyntax& begin, const structure::AccessorDeclarationSyntax& end) {
  createIndentation();
  ofs << "<AssignmentExpressionSyntax_EventAccessorCall ref='";
  if (!noId)
    ofs << "id" << end.getId();
  ofs << "'/>\n";
}

void VisitorCSHARPML::visitEndAssignmentExpressionSyntax_EventAccessorCall(const expression::AssignmentExpressionSyntax& begin, const structure::AccessorDeclarationSyntax& end) {
}

void VisitorCSHARPML::visitAssignmentExpressionSyntax_Left(const expression::AssignmentExpressionSyntax& begin, const expression::ExpressionSyntax& end) {
  createIndentation();
  ofs << "<AssignmentExpressionSyntax_Left>\n";
  incDepth();
}

void VisitorCSHARPML::visitEndAssignmentExpressionSyntax_Left(const expression::AssignmentExpressionSyntax& begin, const expression::ExpressionSyntax& end) {
  decDepth();
  createIndentation();
  ofs << "</AssignmentExpressionSyntax_Left>\n";
}

void VisitorCSHARPML::visitAssignmentExpressionSyntax_OverloadedOperatorCall(const expression::AssignmentExpressionSyntax& begin, const structure::OperatorDeclarationSyntax& end) {
  createIndentation();
  ofs << "<AssignmentExpressionSyntax_OverloadedOperatorCall ref='";
  if (!noId)
    ofs << "id" << end.getId();
  ofs << "'/>\n";
}

void VisitorCSHARPML::visitEndAssignmentExpressionSyntax_OverloadedOperatorCall(const expression::AssignmentExpressionSyntax& begin, const structure::OperatorDeclarationSyntax& end) {
}

void VisitorCSHARPML::visitAssignmentExpressionSyntax_Right(const expression::AssignmentExpressionSyntax& begin, const expression::ExpressionSyntax& end) {
  createIndentation();
  ofs << "<AssignmentExpressionSyntax_Right>\n";
  incDepth();
}

void VisitorCSHARPML::visitEndAssignmentExpressionSyntax_Right(const expression::AssignmentExpressionSyntax& begin, const expression::ExpressionSyntax& end) {
  decDepth();
  createIndentation();
  ofs << "</AssignmentExpressionSyntax_Right>\n";
}

void VisitorCSHARPML::visitAwaitExpressionSyntax_Expression(const expression::AwaitExpressionSyntax& begin, const expression::ExpressionSyntax& end) {
  createIndentation();
  ofs << "<AwaitExpressionSyntax_Expression>\n";
  incDepth();
}

void VisitorCSHARPML::visitEndAwaitExpressionSyntax_Expression(const expression::AwaitExpressionSyntax& begin, const expression::ExpressionSyntax& end) {
  decDepth();
  createIndentation();
  ofs << "</AwaitExpressionSyntax_Expression>\n";
}

void VisitorCSHARPML::visitBinaryExpressionSyntax_Left(const expression::BinaryExpressionSyntax& begin, const expression::ExpressionSyntax& end) {
  createIndentation();
  ofs << "<BinaryExpressionSyntax_Left>\n";
  incDepth();
}

void VisitorCSHARPML::visitEndBinaryExpressionSyntax_Left(const expression::BinaryExpressionSyntax& begin, const expression::ExpressionSyntax& end) {
  decDepth();
  createIndentation();
  ofs << "</BinaryExpressionSyntax_Left>\n";
}

void VisitorCSHARPML::visitBinaryExpressionSyntax_OverloadedOperatorCall(const expression::BinaryExpressionSyntax& begin, const structure::OperatorDeclarationSyntax& end) {
  createIndentation();
  ofs << "<BinaryExpressionSyntax_OverloadedOperatorCall ref='";
  if (!noId)
    ofs << "id" << end.getId();
  ofs << "'/>\n";
}

void VisitorCSHARPML::visitEndBinaryExpressionSyntax_OverloadedOperatorCall(const expression::BinaryExpressionSyntax& begin, const structure::OperatorDeclarationSyntax& end) {
}

void VisitorCSHARPML::visitBinaryExpressionSyntax_Right(const expression::BinaryExpressionSyntax& begin, const expression::ExpressionSyntax& end) {
  createIndentation();
  ofs << "<BinaryExpressionSyntax_Right>\n";
  incDepth();
}

void VisitorCSHARPML::visitEndBinaryExpressionSyntax_Right(const expression::BinaryExpressionSyntax& begin, const expression::ExpressionSyntax& end) {
  decDepth();
  createIndentation();
  ofs << "</BinaryExpressionSyntax_Right>\n";
}

void VisitorCSHARPML::visitCastExpressionSyntax_ConversionOperatorCall(const expression::CastExpressionSyntax& begin, const structure::ConversionOperatorDeclarationSyntax& end) {
  createIndentation();
  ofs << "<CastExpressionSyntax_ConversionOperatorCall ref='";
  if (!noId)
    ofs << "id" << end.getId();
  ofs << "'/>\n";
}

void VisitorCSHARPML::visitEndCastExpressionSyntax_ConversionOperatorCall(const expression::CastExpressionSyntax& begin, const structure::ConversionOperatorDeclarationSyntax& end) {
}

void VisitorCSHARPML::visitCastExpressionSyntax_Expression(const expression::CastExpressionSyntax& begin, const expression::ExpressionSyntax& end) {
  createIndentation();
  ofs << "<CastExpressionSyntax_Expression>\n";
  incDepth();
}

void VisitorCSHARPML::visitEndCastExpressionSyntax_Expression(const expression::CastExpressionSyntax& begin, const expression::ExpressionSyntax& end) {
  decDepth();
  createIndentation();
  ofs << "</CastExpressionSyntax_Expression>\n";
}

void VisitorCSHARPML::visitCastExpressionSyntax_Type(const expression::CastExpressionSyntax& begin, const expression::TypeSyntax& end) {
  createIndentation();
  ofs << "<CastExpressionSyntax_Type>\n";
  incDepth();
}

void VisitorCSHARPML::visitEndCastExpressionSyntax_Type(const expression::CastExpressionSyntax& begin, const expression::TypeSyntax& end) {
  decDepth();
  createIndentation();
  ofs << "</CastExpressionSyntax_Type>\n";
}

void VisitorCSHARPML::visitCheckedExpressionSyntax_Expression(const expression::CheckedExpressionSyntax& begin, const expression::ExpressionSyntax& end) {
  createIndentation();
  ofs << "<CheckedExpressionSyntax_Expression>\n";
  incDepth();
}

void VisitorCSHARPML::visitEndCheckedExpressionSyntax_Expression(const expression::CheckedExpressionSyntax& begin, const expression::ExpressionSyntax& end) {
  decDepth();
  createIndentation();
  ofs << "</CheckedExpressionSyntax_Expression>\n";
}

void VisitorCSHARPML::visitConditionalAccessExpressionSyntax_Expression(const expression::ConditionalAccessExpressionSyntax& begin, const expression::ExpressionSyntax& end) {
  createIndentation();
  ofs << "<ConditionalAccessExpressionSyntax_Expression>\n";
  incDepth();
}

void VisitorCSHARPML::visitEndConditionalAccessExpressionSyntax_Expression(const expression::ConditionalAccessExpressionSyntax& begin, const expression::ExpressionSyntax& end) {
  decDepth();
  createIndentation();
  ofs << "</ConditionalAccessExpressionSyntax_Expression>\n";
}

void VisitorCSHARPML::visitConditionalAccessExpressionSyntax_WhenNotNull(const expression::ConditionalAccessExpressionSyntax& begin, const expression::ExpressionSyntax& end) {
  createIndentation();
  ofs << "<ConditionalAccessExpressionSyntax_WhenNotNull>\n";
  incDepth();
}

void VisitorCSHARPML::visitEndConditionalAccessExpressionSyntax_WhenNotNull(const expression::ConditionalAccessExpressionSyntax& begin, const expression::ExpressionSyntax& end) {
  decDepth();
  createIndentation();
  ofs << "</ConditionalAccessExpressionSyntax_WhenNotNull>\n";
}

void VisitorCSHARPML::visitConditionalExpressionSyntax_Condition(const expression::ConditionalExpressionSyntax& begin, const expression::ExpressionSyntax& end) {
  createIndentation();
  ofs << "<ConditionalExpressionSyntax_Condition>\n";
  incDepth();
}

void VisitorCSHARPML::visitEndConditionalExpressionSyntax_Condition(const expression::ConditionalExpressionSyntax& begin, const expression::ExpressionSyntax& end) {
  decDepth();
  createIndentation();
  ofs << "</ConditionalExpressionSyntax_Condition>\n";
}

void VisitorCSHARPML::visitConditionalExpressionSyntax_WhenFalse(const expression::ConditionalExpressionSyntax& begin, const expression::ExpressionSyntax& end) {
  createIndentation();
  ofs << "<ConditionalExpressionSyntax_WhenFalse>\n";
  incDepth();
}

void VisitorCSHARPML::visitEndConditionalExpressionSyntax_WhenFalse(const expression::ConditionalExpressionSyntax& begin, const expression::ExpressionSyntax& end) {
  decDepth();
  createIndentation();
  ofs << "</ConditionalExpressionSyntax_WhenFalse>\n";
}

void VisitorCSHARPML::visitConditionalExpressionSyntax_WhenTrue(const expression::ConditionalExpressionSyntax& begin, const expression::ExpressionSyntax& end) {
  createIndentation();
  ofs << "<ConditionalExpressionSyntax_WhenTrue>\n";
  incDepth();
}

void VisitorCSHARPML::visitEndConditionalExpressionSyntax_WhenTrue(const expression::ConditionalExpressionSyntax& begin, const expression::ExpressionSyntax& end) {
  decDepth();
  createIndentation();
  ofs << "</ConditionalExpressionSyntax_WhenTrue>\n";
}

void VisitorCSHARPML::visitDeclarationExpressionSyntax_Designation(const expression::DeclarationExpressionSyntax& begin, const structure::VariableDesignationSyntax& end) {
  createIndentation();
  ofs << "<DeclarationExpressionSyntax_Designation>\n";
  incDepth();
}

void VisitorCSHARPML::visitEndDeclarationExpressionSyntax_Designation(const expression::DeclarationExpressionSyntax& begin, const structure::VariableDesignationSyntax& end) {
  decDepth();
  createIndentation();
  ofs << "</DeclarationExpressionSyntax_Designation>\n";
}

void VisitorCSHARPML::visitDeclarationExpressionSyntax_Type(const expression::DeclarationExpressionSyntax& begin, const expression::TypeSyntax& end) {
  createIndentation();
  ofs << "<DeclarationExpressionSyntax_Type>\n";
  incDepth();
}

void VisitorCSHARPML::visitEndDeclarationExpressionSyntax_Type(const expression::DeclarationExpressionSyntax& begin, const expression::TypeSyntax& end) {
  decDepth();
  createIndentation();
  ofs << "</DeclarationExpressionSyntax_Type>\n";
}

void VisitorCSHARPML::visitDefaultExpressionSyntax_Type(const expression::DefaultExpressionSyntax& begin, const expression::TypeSyntax& end) {
  createIndentation();
  ofs << "<DefaultExpressionSyntax_Type>\n";
  incDepth();
}

void VisitorCSHARPML::visitEndDefaultExpressionSyntax_Type(const expression::DefaultExpressionSyntax& begin, const expression::TypeSyntax& end) {
  decDepth();
  createIndentation();
  ofs << "</DefaultExpressionSyntax_Type>\n";
}

void VisitorCSHARPML::visitElementAccessExpressionSyntax_AccessorCall(const expression::ElementAccessExpressionSyntax& begin, const structure::AccessorDeclarationSyntax& end) {
  createIndentation();
  ofs << "<ElementAccessExpressionSyntax_AccessorCall ref='";
  if (!noId)
    ofs << "id" << end.getId();
  ofs << "'/>\n";
}

void VisitorCSHARPML::visitEndElementAccessExpressionSyntax_AccessorCall(const expression::ElementAccessExpressionSyntax& begin, const structure::AccessorDeclarationSyntax& end) {
}

void VisitorCSHARPML::visitElementAccessExpressionSyntax_ArgumentList(const expression::ElementAccessExpressionSyntax& begin, const structure::BracketedArgumentListSyntax& end) {
  createIndentation();
  ofs << "<ElementAccessExpressionSyntax_ArgumentList>\n";
  incDepth();
}

void VisitorCSHARPML::visitEndElementAccessExpressionSyntax_ArgumentList(const expression::ElementAccessExpressionSyntax& begin, const structure::BracketedArgumentListSyntax& end) {
  decDepth();
  createIndentation();
  ofs << "</ElementAccessExpressionSyntax_ArgumentList>\n";
}

void VisitorCSHARPML::visitElementAccessExpressionSyntax_Expression(const expression::ElementAccessExpressionSyntax& begin, const expression::ExpressionSyntax& end) {
  createIndentation();
  ofs << "<ElementAccessExpressionSyntax_Expression>\n";
  incDepth();
}

void VisitorCSHARPML::visitEndElementAccessExpressionSyntax_Expression(const expression::ElementAccessExpressionSyntax& begin, const expression::ExpressionSyntax& end) {
  decDepth();
  createIndentation();
  ofs << "</ElementAccessExpressionSyntax_Expression>\n";
}

void VisitorCSHARPML::visitElementBindingExpressionSyntax_ArgumentList(const expression::ElementBindingExpressionSyntax& begin, const structure::BracketedArgumentListSyntax& end) {
  createIndentation();
  ofs << "<ElementBindingExpressionSyntax_ArgumentList>\n";
  incDepth();
}

void VisitorCSHARPML::visitEndElementBindingExpressionSyntax_ArgumentList(const expression::ElementBindingExpressionSyntax& begin, const structure::BracketedArgumentListSyntax& end) {
  decDepth();
  createIndentation();
  ofs << "</ElementBindingExpressionSyntax_ArgumentList>\n";
}

void VisitorCSHARPML::visitGenericNameSyntax_TypeArgumentList(const expression::GenericNameSyntax& begin, const structure::TypeArgumentListSyntax& end) {
  createIndentation();
  ofs << "<GenericNameSyntax_TypeArgumentList>\n";
  incDepth();
}

void VisitorCSHARPML::visitEndGenericNameSyntax_TypeArgumentList(const expression::GenericNameSyntax& begin, const structure::TypeArgumentListSyntax& end) {
  decDepth();
  createIndentation();
  ofs << "</GenericNameSyntax_TypeArgumentList>\n";
}

void VisitorCSHARPML::visitIdentifierNameSyntax_AccessorCall(const expression::IdentifierNameSyntax& begin, const structure::AccessorDeclarationSyntax& end) {
  createIndentation();
  ofs << "<IdentifierNameSyntax_AccessorCall ref='";
  if (!noId)
    ofs << "id" << end.getId();
  ofs << "'/>\n";
}

void VisitorCSHARPML::visitEndIdentifierNameSyntax_AccessorCall(const expression::IdentifierNameSyntax& begin, const structure::AccessorDeclarationSyntax& end) {
}

void VisitorCSHARPML::visitIdentifierNameSyntax_Declaration(const expression::IdentifierNameSyntax& begin, const base::Positioned& end) {
  createIndentation();
  ofs << "<IdentifierNameSyntax_Declaration ref='";
  if (!noId)
    ofs << "id" << end.getId();
  ofs << "'/>\n";
}

void VisitorCSHARPML::visitEndIdentifierNameSyntax_Declaration(const expression::IdentifierNameSyntax& begin, const base::Positioned& end) {
}

void VisitorCSHARPML::visitImplicitArrayCreationExpressionSyntax_Initializer(const expression::ImplicitArrayCreationExpressionSyntax& begin, const expression::InitializerExpressionSyntax& end) {
  createIndentation();
  ofs << "<ImplicitArrayCreationExpressionSyntax_Initializer>\n";
  incDepth();
}

void VisitorCSHARPML::visitEndImplicitArrayCreationExpressionSyntax_Initializer(const expression::ImplicitArrayCreationExpressionSyntax& begin, const expression::InitializerExpressionSyntax& end) {
  decDepth();
  createIndentation();
  ofs << "</ImplicitArrayCreationExpressionSyntax_Initializer>\n";
}

void VisitorCSHARPML::visitImplicitElementAccessSyntax_ArgumentList(const expression::ImplicitElementAccessSyntax& begin, const structure::BracketedArgumentListSyntax& end) {
  createIndentation();
  ofs << "<ImplicitElementAccessSyntax_ArgumentList>\n";
  incDepth();
}

void VisitorCSHARPML::visitEndImplicitElementAccessSyntax_ArgumentList(const expression::ImplicitElementAccessSyntax& begin, const structure::BracketedArgumentListSyntax& end) {
  decDepth();
  createIndentation();
  ofs << "</ImplicitElementAccessSyntax_ArgumentList>\n";
}

void VisitorCSHARPML::visitImplicitStackAllocArrayCreationExpressionSyntax_Initializer(const expression::ImplicitStackAllocArrayCreationExpressionSyntax& begin, const expression::InitializerExpressionSyntax& end) {
  createIndentation();
  ofs << "<ImplicitStackAllocArrayCreationExpressionSyntax_Initializer>\n";
  incDepth();
}

void VisitorCSHARPML::visitEndImplicitStackAllocArrayCreationExpressionSyntax_Initializer(const expression::ImplicitStackAllocArrayCreationExpressionSyntax& begin, const expression::InitializerExpressionSyntax& end) {
  decDepth();
  createIndentation();
  ofs << "</ImplicitStackAllocArrayCreationExpressionSyntax_Initializer>\n";
}

void VisitorCSHARPML::visitInitializerExpressionSyntax_Expressions(const expression::InitializerExpressionSyntax& begin, const expression::ExpressionSyntax& end) {
  createIndentation();
  ofs << "<InitializerExpressionSyntax_Expressions>\n";
  incDepth();
}

void VisitorCSHARPML::visitEndInitializerExpressionSyntax_Expressions(const expression::InitializerExpressionSyntax& begin, const expression::ExpressionSyntax& end) {
  decDepth();
  createIndentation();
  ofs << "</InitializerExpressionSyntax_Expressions>\n";
}

void VisitorCSHARPML::visitInterpolatedStringExpressionSyntax_Contents(const expression::InterpolatedStringExpressionSyntax& begin, const structure::InterpolatedStringContentSyntax& end) {
  createIndentation();
  ofs << "<InterpolatedStringExpressionSyntax_Contents>\n";
  incDepth();
}

void VisitorCSHARPML::visitEndInterpolatedStringExpressionSyntax_Contents(const expression::InterpolatedStringExpressionSyntax& begin, const structure::InterpolatedStringContentSyntax& end) {
  decDepth();
  createIndentation();
  ofs << "</InterpolatedStringExpressionSyntax_Contents>\n";
}

void VisitorCSHARPML::visitInvocationExpressionSyntax_ArgumentList(const expression::InvocationExpressionSyntax& begin, const structure::ArgumentListSyntax& end) {
  createIndentation();
  ofs << "<InvocationExpressionSyntax_ArgumentList>\n";
  incDepth();
}

void VisitorCSHARPML::visitEndInvocationExpressionSyntax_ArgumentList(const expression::InvocationExpressionSyntax& begin, const structure::ArgumentListSyntax& end) {
  decDepth();
  createIndentation();
  ofs << "</InvocationExpressionSyntax_ArgumentList>\n";
}

void VisitorCSHARPML::visitInvocationExpressionSyntax_Expression(const expression::InvocationExpressionSyntax& begin, const expression::ExpressionSyntax& end) {
  createIndentation();
  ofs << "<InvocationExpressionSyntax_Expression>\n";
  incDepth();
}

void VisitorCSHARPML::visitEndInvocationExpressionSyntax_Expression(const expression::InvocationExpressionSyntax& begin, const expression::ExpressionSyntax& end) {
  decDepth();
  createIndentation();
  ofs << "</InvocationExpressionSyntax_Expression>\n";
}

void VisitorCSHARPML::visitInvocationExpressionSyntax_LocalFunctionCall(const expression::InvocationExpressionSyntax& begin, const statement::LocalFunctionStatementSyntax& end) {
  createIndentation();
  ofs << "<InvocationExpressionSyntax_LocalFunctionCall ref='";
  if (!noId)
    ofs << "id" << end.getId();
  ofs << "'/>\n";
}

void VisitorCSHARPML::visitEndInvocationExpressionSyntax_LocalFunctionCall(const expression::InvocationExpressionSyntax& begin, const statement::LocalFunctionStatementSyntax& end) {
}

void VisitorCSHARPML::visitInvocationExpressionSyntax_MethodCall(const expression::InvocationExpressionSyntax& begin, const structure::MethodDeclarationSyntax& end) {
  createIndentation();
  ofs << "<InvocationExpressionSyntax_MethodCall ref='";
  if (!noId)
    ofs << "id" << end.getId();
  ofs << "'/>\n";
}

void VisitorCSHARPML::visitEndInvocationExpressionSyntax_MethodCall(const expression::InvocationExpressionSyntax& begin, const structure::MethodDeclarationSyntax& end) {
}

void VisitorCSHARPML::visitIsPatternExpressionSyntax_Expression(const expression::IsPatternExpressionSyntax& begin, const expression::ExpressionSyntax& end) {
  createIndentation();
  ofs << "<IsPatternExpressionSyntax_Expression>\n";
  incDepth();
}

void VisitorCSHARPML::visitEndIsPatternExpressionSyntax_Expression(const expression::IsPatternExpressionSyntax& begin, const expression::ExpressionSyntax& end) {
  decDepth();
  createIndentation();
  ofs << "</IsPatternExpressionSyntax_Expression>\n";
}

void VisitorCSHARPML::visitIsPatternExpressionSyntax_Pattern(const expression::IsPatternExpressionSyntax& begin, const structure::PatternSyntax& end) {
  createIndentation();
  ofs << "<IsPatternExpressionSyntax_Pattern>\n";
  incDepth();
}

void VisitorCSHARPML::visitEndIsPatternExpressionSyntax_Pattern(const expression::IsPatternExpressionSyntax& begin, const structure::PatternSyntax& end) {
  decDepth();
  createIndentation();
  ofs << "</IsPatternExpressionSyntax_Pattern>\n";
}

void VisitorCSHARPML::visitMakeRefExpressionSyntax_Expression(const expression::MakeRefExpressionSyntax& begin, const expression::ExpressionSyntax& end) {
  createIndentation();
  ofs << "<MakeRefExpressionSyntax_Expression>\n";
  incDepth();
}

void VisitorCSHARPML::visitEndMakeRefExpressionSyntax_Expression(const expression::MakeRefExpressionSyntax& begin, const expression::ExpressionSyntax& end) {
  decDepth();
  createIndentation();
  ofs << "</MakeRefExpressionSyntax_Expression>\n";
}

void VisitorCSHARPML::visitMemberAccessExpressionSyntax_Expression(const expression::MemberAccessExpressionSyntax& begin, const expression::ExpressionSyntax& end) {
  createIndentation();
  ofs << "<MemberAccessExpressionSyntax_Expression>\n";
  incDepth();
}

void VisitorCSHARPML::visitEndMemberAccessExpressionSyntax_Expression(const expression::MemberAccessExpressionSyntax& begin, const expression::ExpressionSyntax& end) {
  decDepth();
  createIndentation();
  ofs << "</MemberAccessExpressionSyntax_Expression>\n";
}

void VisitorCSHARPML::visitMemberAccessExpressionSyntax_Name(const expression::MemberAccessExpressionSyntax& begin, const expression::SimpleNameSyntax& end) {
  createIndentation();
  ofs << "<MemberAccessExpressionSyntax_Name>\n";
  incDepth();
}

void VisitorCSHARPML::visitEndMemberAccessExpressionSyntax_Name(const expression::MemberAccessExpressionSyntax& begin, const expression::SimpleNameSyntax& end) {
  decDepth();
  createIndentation();
  ofs << "</MemberAccessExpressionSyntax_Name>\n";
}

void VisitorCSHARPML::visitMemberBindingExpressionSyntax_Name(const expression::MemberBindingExpressionSyntax& begin, const expression::SimpleNameSyntax& end) {
  createIndentation();
  ofs << "<MemberBindingExpressionSyntax_Name>\n";
  incDepth();
}

void VisitorCSHARPML::visitEndMemberBindingExpressionSyntax_Name(const expression::MemberBindingExpressionSyntax& begin, const expression::SimpleNameSyntax& end) {
  decDepth();
  createIndentation();
  ofs << "</MemberBindingExpressionSyntax_Name>\n";
}

void VisitorCSHARPML::visitNullableTypeSyntax_ElementType(const expression::NullableTypeSyntax& begin, const expression::TypeSyntax& end) {
  createIndentation();
  ofs << "<NullableTypeSyntax_ElementType>\n";
  incDepth();
}

void VisitorCSHARPML::visitEndNullableTypeSyntax_ElementType(const expression::NullableTypeSyntax& begin, const expression::TypeSyntax& end) {
  decDepth();
  createIndentation();
  ofs << "</NullableTypeSyntax_ElementType>\n";
}

void VisitorCSHARPML::visitObjectCreationExpressionSyntax_ArgumentList(const expression::ObjectCreationExpressionSyntax& begin, const structure::ArgumentListSyntax& end) {
  createIndentation();
  ofs << "<ObjectCreationExpressionSyntax_ArgumentList>\n";
  incDepth();
}

void VisitorCSHARPML::visitEndObjectCreationExpressionSyntax_ArgumentList(const expression::ObjectCreationExpressionSyntax& begin, const structure::ArgumentListSyntax& end) {
  decDepth();
  createIndentation();
  ofs << "</ObjectCreationExpressionSyntax_ArgumentList>\n";
}

void VisitorCSHARPML::visitObjectCreationExpressionSyntax_ConstructorCall(const expression::ObjectCreationExpressionSyntax& begin, const structure::ConstructorDeclarationSyntax& end) {
  createIndentation();
  ofs << "<ObjectCreationExpressionSyntax_ConstructorCall ref='";
  if (!noId)
    ofs << "id" << end.getId();
  ofs << "'/>\n";
}

void VisitorCSHARPML::visitEndObjectCreationExpressionSyntax_ConstructorCall(const expression::ObjectCreationExpressionSyntax& begin, const structure::ConstructorDeclarationSyntax& end) {
}

void VisitorCSHARPML::visitObjectCreationExpressionSyntax_Initializer(const expression::ObjectCreationExpressionSyntax& begin, const expression::InitializerExpressionSyntax& end) {
  createIndentation();
  ofs << "<ObjectCreationExpressionSyntax_Initializer>\n";
  incDepth();
}

void VisitorCSHARPML::visitEndObjectCreationExpressionSyntax_Initializer(const expression::ObjectCreationExpressionSyntax& begin, const expression::InitializerExpressionSyntax& end) {
  decDepth();
  createIndentation();
  ofs << "</ObjectCreationExpressionSyntax_Initializer>\n";
}

void VisitorCSHARPML::visitObjectCreationExpressionSyntax_Type(const expression::ObjectCreationExpressionSyntax& begin, const expression::TypeSyntax& end) {
  createIndentation();
  ofs << "<ObjectCreationExpressionSyntax_Type>\n";
  incDepth();
}

void VisitorCSHARPML::visitEndObjectCreationExpressionSyntax_Type(const expression::ObjectCreationExpressionSyntax& begin, const expression::TypeSyntax& end) {
  decDepth();
  createIndentation();
  ofs << "</ObjectCreationExpressionSyntax_Type>\n";
}

void VisitorCSHARPML::visitParenthesizedExpressionSyntax_Expression(const expression::ParenthesizedExpressionSyntax& begin, const expression::ExpressionSyntax& end) {
  createIndentation();
  ofs << "<ParenthesizedExpressionSyntax_Expression>\n";
  incDepth();
}

void VisitorCSHARPML::visitEndParenthesizedExpressionSyntax_Expression(const expression::ParenthesizedExpressionSyntax& begin, const expression::ExpressionSyntax& end) {
  decDepth();
  createIndentation();
  ofs << "</ParenthesizedExpressionSyntax_Expression>\n";
}

void VisitorCSHARPML::visitParenthesizedLambdaExpressionSyntax_ParameterList(const expression::ParenthesizedLambdaExpressionSyntax& begin, const structure::ParameterListSyntax& end) {
  createIndentation();
  ofs << "<ParenthesizedLambdaExpressionSyntax_ParameterList>\n";
  incDepth();
}

void VisitorCSHARPML::visitEndParenthesizedLambdaExpressionSyntax_ParameterList(const expression::ParenthesizedLambdaExpressionSyntax& begin, const structure::ParameterListSyntax& end) {
  decDepth();
  createIndentation();
  ofs << "</ParenthesizedLambdaExpressionSyntax_ParameterList>\n";
}

void VisitorCSHARPML::visitPointerTypeSyntax_ElementType(const expression::PointerTypeSyntax& begin, const expression::TypeSyntax& end) {
  createIndentation();
  ofs << "<PointerTypeSyntax_ElementType>\n";
  incDepth();
}

void VisitorCSHARPML::visitEndPointerTypeSyntax_ElementType(const expression::PointerTypeSyntax& begin, const expression::TypeSyntax& end) {
  decDepth();
  createIndentation();
  ofs << "</PointerTypeSyntax_ElementType>\n";
}

void VisitorCSHARPML::visitPostfixUnaryExpressionSyntax_Operand(const expression::PostfixUnaryExpressionSyntax& begin, const expression::ExpressionSyntax& end) {
  createIndentation();
  ofs << "<PostfixUnaryExpressionSyntax_Operand>\n";
  incDepth();
}

void VisitorCSHARPML::visitEndPostfixUnaryExpressionSyntax_Operand(const expression::PostfixUnaryExpressionSyntax& begin, const expression::ExpressionSyntax& end) {
  decDepth();
  createIndentation();
  ofs << "</PostfixUnaryExpressionSyntax_Operand>\n";
}

void VisitorCSHARPML::visitPostfixUnaryExpressionSyntax_OverloadedOperatorCall(const expression::PostfixUnaryExpressionSyntax& begin, const structure::OperatorDeclarationSyntax& end) {
  createIndentation();
  ofs << "<PostfixUnaryExpressionSyntax_OverloadedOperatorCall ref='";
  if (!noId)
    ofs << "id" << end.getId();
  ofs << "'/>\n";
}

void VisitorCSHARPML::visitEndPostfixUnaryExpressionSyntax_OverloadedOperatorCall(const expression::PostfixUnaryExpressionSyntax& begin, const structure::OperatorDeclarationSyntax& end) {
}

void VisitorCSHARPML::visitPrefixUnaryExpressionSyntax_Operand(const expression::PrefixUnaryExpressionSyntax& begin, const expression::ExpressionSyntax& end) {
  createIndentation();
  ofs << "<PrefixUnaryExpressionSyntax_Operand>\n";
  incDepth();
}

void VisitorCSHARPML::visitEndPrefixUnaryExpressionSyntax_Operand(const expression::PrefixUnaryExpressionSyntax& begin, const expression::ExpressionSyntax& end) {
  decDepth();
  createIndentation();
  ofs << "</PrefixUnaryExpressionSyntax_Operand>\n";
}

void VisitorCSHARPML::visitPrefixUnaryExpressionSyntax_OverloadedOperatorCall(const expression::PrefixUnaryExpressionSyntax& begin, const structure::OperatorDeclarationSyntax& end) {
  createIndentation();
  ofs << "<PrefixUnaryExpressionSyntax_OverloadedOperatorCall ref='";
  if (!noId)
    ofs << "id" << end.getId();
  ofs << "'/>\n";
}

void VisitorCSHARPML::visitEndPrefixUnaryExpressionSyntax_OverloadedOperatorCall(const expression::PrefixUnaryExpressionSyntax& begin, const structure::OperatorDeclarationSyntax& end) {
}

void VisitorCSHARPML::visitQualifiedNameSyntax_Left(const expression::QualifiedNameSyntax& begin, const expression::NameSyntax& end) {
  createIndentation();
  ofs << "<QualifiedNameSyntax_Left>\n";
  incDepth();
}

void VisitorCSHARPML::visitEndQualifiedNameSyntax_Left(const expression::QualifiedNameSyntax& begin, const expression::NameSyntax& end) {
  decDepth();
  createIndentation();
  ofs << "</QualifiedNameSyntax_Left>\n";
}

void VisitorCSHARPML::visitQualifiedNameSyntax_Right(const expression::QualifiedNameSyntax& begin, const expression::SimpleNameSyntax& end) {
  createIndentation();
  ofs << "<QualifiedNameSyntax_Right>\n";
  incDepth();
}

void VisitorCSHARPML::visitEndQualifiedNameSyntax_Right(const expression::QualifiedNameSyntax& begin, const expression::SimpleNameSyntax& end) {
  decDepth();
  createIndentation();
  ofs << "</QualifiedNameSyntax_Right>\n";
}

void VisitorCSHARPML::visitQueryExpressionSyntax_Body(const expression::QueryExpressionSyntax& begin, const structure::QueryBodySyntax& end) {
  createIndentation();
  ofs << "<QueryExpressionSyntax_Body>\n";
  incDepth();
}

void VisitorCSHARPML::visitEndQueryExpressionSyntax_Body(const expression::QueryExpressionSyntax& begin, const structure::QueryBodySyntax& end) {
  decDepth();
  createIndentation();
  ofs << "</QueryExpressionSyntax_Body>\n";
}

void VisitorCSHARPML::visitQueryExpressionSyntax_FromClause(const expression::QueryExpressionSyntax& begin, const structure::FromClauseSyntax& end) {
  createIndentation();
  ofs << "<QueryExpressionSyntax_FromClause>\n";
  incDepth();
}

void VisitorCSHARPML::visitEndQueryExpressionSyntax_FromClause(const expression::QueryExpressionSyntax& begin, const structure::FromClauseSyntax& end) {
  decDepth();
  createIndentation();
  ofs << "</QueryExpressionSyntax_FromClause>\n";
}

void VisitorCSHARPML::visitRangeExpressionSyntax_LeftOperand(const expression::RangeExpressionSyntax& begin, const expression::ExpressionSyntax& end) {
  createIndentation();
  ofs << "<RangeExpressionSyntax_LeftOperand>\n";
  incDepth();
}

void VisitorCSHARPML::visitEndRangeExpressionSyntax_LeftOperand(const expression::RangeExpressionSyntax& begin, const expression::ExpressionSyntax& end) {
  decDepth();
  createIndentation();
  ofs << "</RangeExpressionSyntax_LeftOperand>\n";
}

void VisitorCSHARPML::visitRangeExpressionSyntax_RightOperand(const expression::RangeExpressionSyntax& begin, const expression::ExpressionSyntax& end) {
  createIndentation();
  ofs << "<RangeExpressionSyntax_RightOperand>\n";
  incDepth();
}

void VisitorCSHARPML::visitEndRangeExpressionSyntax_RightOperand(const expression::RangeExpressionSyntax& begin, const expression::ExpressionSyntax& end) {
  decDepth();
  createIndentation();
  ofs << "</RangeExpressionSyntax_RightOperand>\n";
}

void VisitorCSHARPML::visitRefExpressionSyntax_Expression(const expression::RefExpressionSyntax& begin, const expression::ExpressionSyntax& end) {
  createIndentation();
  ofs << "<RefExpressionSyntax_Expression>\n";
  incDepth();
}

void VisitorCSHARPML::visitEndRefExpressionSyntax_Expression(const expression::RefExpressionSyntax& begin, const expression::ExpressionSyntax& end) {
  decDepth();
  createIndentation();
  ofs << "</RefExpressionSyntax_Expression>\n";
}

void VisitorCSHARPML::visitRefTypeExpressionSyntax_Expression(const expression::RefTypeExpressionSyntax& begin, const expression::ExpressionSyntax& end) {
  createIndentation();
  ofs << "<RefTypeExpressionSyntax_Expression>\n";
  incDepth();
}

void VisitorCSHARPML::visitEndRefTypeExpressionSyntax_Expression(const expression::RefTypeExpressionSyntax& begin, const expression::ExpressionSyntax& end) {
  decDepth();
  createIndentation();
  ofs << "</RefTypeExpressionSyntax_Expression>\n";
}

void VisitorCSHARPML::visitRefTypeSyntax_Type(const expression::RefTypeSyntax& begin, const expression::TypeSyntax& end) {
  createIndentation();
  ofs << "<RefTypeSyntax_Type>\n";
  incDepth();
}

void VisitorCSHARPML::visitEndRefTypeSyntax_Type(const expression::RefTypeSyntax& begin, const expression::TypeSyntax& end) {
  decDepth();
  createIndentation();
  ofs << "</RefTypeSyntax_Type>\n";
}

void VisitorCSHARPML::visitRefValueExpressionSyntax_Expression(const expression::RefValueExpressionSyntax& begin, const expression::ExpressionSyntax& end) {
  createIndentation();
  ofs << "<RefValueExpressionSyntax_Expression>\n";
  incDepth();
}

void VisitorCSHARPML::visitEndRefValueExpressionSyntax_Expression(const expression::RefValueExpressionSyntax& begin, const expression::ExpressionSyntax& end) {
  decDepth();
  createIndentation();
  ofs << "</RefValueExpressionSyntax_Expression>\n";
}

void VisitorCSHARPML::visitRefValueExpressionSyntax_Type(const expression::RefValueExpressionSyntax& begin, const expression::TypeSyntax& end) {
  createIndentation();
  ofs << "<RefValueExpressionSyntax_Type>\n";
  incDepth();
}

void VisitorCSHARPML::visitEndRefValueExpressionSyntax_Type(const expression::RefValueExpressionSyntax& begin, const expression::TypeSyntax& end) {
  decDepth();
  createIndentation();
  ofs << "</RefValueExpressionSyntax_Type>\n";
}

void VisitorCSHARPML::visitSimpleLambdaExpressionSyntax_Parameter(const expression::SimpleLambdaExpressionSyntax& begin, const structure::ParameterSyntax& end) {
  createIndentation();
  ofs << "<SimpleLambdaExpressionSyntax_Parameter>\n";
  incDepth();
}

void VisitorCSHARPML::visitEndSimpleLambdaExpressionSyntax_Parameter(const expression::SimpleLambdaExpressionSyntax& begin, const structure::ParameterSyntax& end) {
  decDepth();
  createIndentation();
  ofs << "</SimpleLambdaExpressionSyntax_Parameter>\n";
}

void VisitorCSHARPML::visitSizeOfExpressionSyntax_Type(const expression::SizeOfExpressionSyntax& begin, const expression::TypeSyntax& end) {
  createIndentation();
  ofs << "<SizeOfExpressionSyntax_Type>\n";
  incDepth();
}

void VisitorCSHARPML::visitEndSizeOfExpressionSyntax_Type(const expression::SizeOfExpressionSyntax& begin, const expression::TypeSyntax& end) {
  decDepth();
  createIndentation();
  ofs << "</SizeOfExpressionSyntax_Type>\n";
}

void VisitorCSHARPML::visitStackAllocArrayCreationExpressionSyntax_Initializer(const expression::StackAllocArrayCreationExpressionSyntax& begin, const expression::InitializerExpressionSyntax& end) {
  createIndentation();
  ofs << "<StackAllocArrayCreationExpressionSyntax_Initializer>\n";
  incDepth();
}

void VisitorCSHARPML::visitEndStackAllocArrayCreationExpressionSyntax_Initializer(const expression::StackAllocArrayCreationExpressionSyntax& begin, const expression::InitializerExpressionSyntax& end) {
  decDepth();
  createIndentation();
  ofs << "</StackAllocArrayCreationExpressionSyntax_Initializer>\n";
}

void VisitorCSHARPML::visitStackAllocArrayCreationExpressionSyntax_Type(const expression::StackAllocArrayCreationExpressionSyntax& begin, const expression::TypeSyntax& end) {
  createIndentation();
  ofs << "<StackAllocArrayCreationExpressionSyntax_Type>\n";
  incDepth();
}

void VisitorCSHARPML::visitEndStackAllocArrayCreationExpressionSyntax_Type(const expression::StackAllocArrayCreationExpressionSyntax& begin, const expression::TypeSyntax& end) {
  decDepth();
  createIndentation();
  ofs << "</StackAllocArrayCreationExpressionSyntax_Type>\n";
}

void VisitorCSHARPML::visitSwitchExpressionSyntax_Arms(const expression::SwitchExpressionSyntax& begin, const structure::SwitchExpressionArmSyntax& end) {
  createIndentation();
  ofs << "<SwitchExpressionSyntax_Arms>\n";
  incDepth();
}

void VisitorCSHARPML::visitEndSwitchExpressionSyntax_Arms(const expression::SwitchExpressionSyntax& begin, const structure::SwitchExpressionArmSyntax& end) {
  decDepth();
  createIndentation();
  ofs << "</SwitchExpressionSyntax_Arms>\n";
}

void VisitorCSHARPML::visitSwitchExpressionSyntax_GoverningExpression(const expression::SwitchExpressionSyntax& begin, const expression::ExpressionSyntax& end) {
  createIndentation();
  ofs << "<SwitchExpressionSyntax_GoverningExpression>\n";
  incDepth();
}

void VisitorCSHARPML::visitEndSwitchExpressionSyntax_GoverningExpression(const expression::SwitchExpressionSyntax& begin, const expression::ExpressionSyntax& end) {
  decDepth();
  createIndentation();
  ofs << "</SwitchExpressionSyntax_GoverningExpression>\n";
}

void VisitorCSHARPML::visitThrowExpressionSyntax_Expression(const expression::ThrowExpressionSyntax& begin, const expression::ExpressionSyntax& end) {
  createIndentation();
  ofs << "<ThrowExpressionSyntax_Expression>\n";
  incDepth();
}

void VisitorCSHARPML::visitEndThrowExpressionSyntax_Expression(const expression::ThrowExpressionSyntax& begin, const expression::ExpressionSyntax& end) {
  decDepth();
  createIndentation();
  ofs << "</ThrowExpressionSyntax_Expression>\n";
}

void VisitorCSHARPML::visitTupleExpressionSyntax_Arguments(const expression::TupleExpressionSyntax& begin, const structure::ArgumentSyntax& end) {
  createIndentation();
  ofs << "<TupleExpressionSyntax_Arguments>\n";
  incDepth();
}

void VisitorCSHARPML::visitEndTupleExpressionSyntax_Arguments(const expression::TupleExpressionSyntax& begin, const structure::ArgumentSyntax& end) {
  decDepth();
  createIndentation();
  ofs << "</TupleExpressionSyntax_Arguments>\n";
}

void VisitorCSHARPML::visitTupleTypeSyntax_Elements(const expression::TupleTypeSyntax& begin, const structure::TupleElementSyntax& end) {
  createIndentation();
  ofs << "<TupleTypeSyntax_Elements>\n";
  incDepth();
}

void VisitorCSHARPML::visitEndTupleTypeSyntax_Elements(const expression::TupleTypeSyntax& begin, const structure::TupleElementSyntax& end) {
  decDepth();
  createIndentation();
  ofs << "</TupleTypeSyntax_Elements>\n";
}

void VisitorCSHARPML::visitTypeOfExpressionSyntax_Type(const expression::TypeOfExpressionSyntax& begin, const expression::TypeSyntax& end) {
  createIndentation();
  ofs << "<TypeOfExpressionSyntax_Type>\n";
  incDepth();
}

void VisitorCSHARPML::visitEndTypeOfExpressionSyntax_Type(const expression::TypeOfExpressionSyntax& begin, const expression::TypeSyntax& end) {
  decDepth();
  createIndentation();
  ofs << "</TypeOfExpressionSyntax_Type>\n";
}

void VisitorCSHARPML::visitTypeSyntax_OriginalDefinition(const expression::TypeSyntax& begin, const structure::MemberDeclarationSyntax& end) {
  createIndentation();
  ofs << "<TypeSyntax_OriginalDefinition ref='";
  if (!noId)
    ofs << "id" << end.getId();
  ofs << "'/>\n";
}

void VisitorCSHARPML::visitEndTypeSyntax_OriginalDefinition(const expression::TypeSyntax& begin, const structure::MemberDeclarationSyntax& end) {
}

void VisitorCSHARPML::visitBlockSyntax_Statements(const statement::BlockSyntax& begin, const statement::StatementSyntax& end) {
  createIndentation();
  ofs << "<BlockSyntax_Statements>\n";
  incDepth();
}

void VisitorCSHARPML::visitEndBlockSyntax_Statements(const statement::BlockSyntax& begin, const statement::StatementSyntax& end) {
  decDepth();
  createIndentation();
  ofs << "</BlockSyntax_Statements>\n";
}

void VisitorCSHARPML::visitCheckedStatementSyntax_Block(const statement::CheckedStatementSyntax& begin, const statement::BlockSyntax& end) {
  createIndentation();
  ofs << "<CheckedStatementSyntax_Block>\n";
  incDepth();
}

void VisitorCSHARPML::visitEndCheckedStatementSyntax_Block(const statement::CheckedStatementSyntax& begin, const statement::BlockSyntax& end) {
  decDepth();
  createIndentation();
  ofs << "</CheckedStatementSyntax_Block>\n";
}

void VisitorCSHARPML::visitCommonForEachStatementSyntax_Expression(const statement::CommonForEachStatementSyntax& begin, const expression::ExpressionSyntax& end) {
  createIndentation();
  ofs << "<CommonForEachStatementSyntax_Expression>\n";
  incDepth();
}

void VisitorCSHARPML::visitEndCommonForEachStatementSyntax_Expression(const statement::CommonForEachStatementSyntax& begin, const expression::ExpressionSyntax& end) {
  decDepth();
  createIndentation();
  ofs << "</CommonForEachStatementSyntax_Expression>\n";
}

void VisitorCSHARPML::visitCommonForEachStatementSyntax_Statement(const statement::CommonForEachStatementSyntax& begin, const statement::StatementSyntax& end) {
  createIndentation();
  ofs << "<CommonForEachStatementSyntax_Statement>\n";
  incDepth();
}

void VisitorCSHARPML::visitEndCommonForEachStatementSyntax_Statement(const statement::CommonForEachStatementSyntax& begin, const statement::StatementSyntax& end) {
  decDepth();
  createIndentation();
  ofs << "</CommonForEachStatementSyntax_Statement>\n";
}

void VisitorCSHARPML::visitDoStatementSyntax_Condition(const statement::DoStatementSyntax& begin, const expression::ExpressionSyntax& end) {
  createIndentation();
  ofs << "<DoStatementSyntax_Condition>\n";
  incDepth();
}

void VisitorCSHARPML::visitEndDoStatementSyntax_Condition(const statement::DoStatementSyntax& begin, const expression::ExpressionSyntax& end) {
  decDepth();
  createIndentation();
  ofs << "</DoStatementSyntax_Condition>\n";
}

void VisitorCSHARPML::visitDoStatementSyntax_Statement(const statement::DoStatementSyntax& begin, const statement::StatementSyntax& end) {
  createIndentation();
  ofs << "<DoStatementSyntax_Statement>\n";
  incDepth();
}

void VisitorCSHARPML::visitEndDoStatementSyntax_Statement(const statement::DoStatementSyntax& begin, const statement::StatementSyntax& end) {
  decDepth();
  createIndentation();
  ofs << "</DoStatementSyntax_Statement>\n";
}

void VisitorCSHARPML::visitExpressionStatementSyntax_Expression(const statement::ExpressionStatementSyntax& begin, const expression::ExpressionSyntax& end) {
  createIndentation();
  ofs << "<ExpressionStatementSyntax_Expression>\n";
  incDepth();
}

void VisitorCSHARPML::visitEndExpressionStatementSyntax_Expression(const statement::ExpressionStatementSyntax& begin, const expression::ExpressionSyntax& end) {
  decDepth();
  createIndentation();
  ofs << "</ExpressionStatementSyntax_Expression>\n";
}

void VisitorCSHARPML::visitFixedStatementSyntax_Declaration(const statement::FixedStatementSyntax& begin, const structure::VariableDeclarationSyntax& end) {
  createIndentation();
  ofs << "<FixedStatementSyntax_Declaration>\n";
  incDepth();
}

void VisitorCSHARPML::visitEndFixedStatementSyntax_Declaration(const statement::FixedStatementSyntax& begin, const structure::VariableDeclarationSyntax& end) {
  decDepth();
  createIndentation();
  ofs << "</FixedStatementSyntax_Declaration>\n";
}

void VisitorCSHARPML::visitFixedStatementSyntax_Statement(const statement::FixedStatementSyntax& begin, const statement::StatementSyntax& end) {
  createIndentation();
  ofs << "<FixedStatementSyntax_Statement>\n";
  incDepth();
}

void VisitorCSHARPML::visitEndFixedStatementSyntax_Statement(const statement::FixedStatementSyntax& begin, const statement::StatementSyntax& end) {
  decDepth();
  createIndentation();
  ofs << "</FixedStatementSyntax_Statement>\n";
}

void VisitorCSHARPML::visitForEachStatementSyntax_Type(const statement::ForEachStatementSyntax& begin, const expression::TypeSyntax& end) {
  createIndentation();
  ofs << "<ForEachStatementSyntax_Type>\n";
  incDepth();
}

void VisitorCSHARPML::visitEndForEachStatementSyntax_Type(const statement::ForEachStatementSyntax& begin, const expression::TypeSyntax& end) {
  decDepth();
  createIndentation();
  ofs << "</ForEachStatementSyntax_Type>\n";
}

void VisitorCSHARPML::visitForEachVariableStatementSyntax_Variable(const statement::ForEachVariableStatementSyntax& begin, const expression::ExpressionSyntax& end) {
  createIndentation();
  ofs << "<ForEachVariableStatementSyntax_Variable>\n";
  incDepth();
}

void VisitorCSHARPML::visitEndForEachVariableStatementSyntax_Variable(const statement::ForEachVariableStatementSyntax& begin, const expression::ExpressionSyntax& end) {
  decDepth();
  createIndentation();
  ofs << "</ForEachVariableStatementSyntax_Variable>\n";
}

void VisitorCSHARPML::visitForStatementSyntax_Condition(const statement::ForStatementSyntax& begin, const expression::ExpressionSyntax& end) {
  createIndentation();
  ofs << "<ForStatementSyntax_Condition>\n";
  incDepth();
}

void VisitorCSHARPML::visitEndForStatementSyntax_Condition(const statement::ForStatementSyntax& begin, const expression::ExpressionSyntax& end) {
  decDepth();
  createIndentation();
  ofs << "</ForStatementSyntax_Condition>\n";
}

void VisitorCSHARPML::visitForStatementSyntax_Declaration(const statement::ForStatementSyntax& begin, const structure::VariableDeclarationSyntax& end) {
  createIndentation();
  ofs << "<ForStatementSyntax_Declaration>\n";
  incDepth();
}

void VisitorCSHARPML::visitEndForStatementSyntax_Declaration(const statement::ForStatementSyntax& begin, const structure::VariableDeclarationSyntax& end) {
  decDepth();
  createIndentation();
  ofs << "</ForStatementSyntax_Declaration>\n";
}

void VisitorCSHARPML::visitForStatementSyntax_Incrementors(const statement::ForStatementSyntax& begin, const expression::ExpressionSyntax& end) {
  createIndentation();
  ofs << "<ForStatementSyntax_Incrementors>\n";
  incDepth();
}

void VisitorCSHARPML::visitEndForStatementSyntax_Incrementors(const statement::ForStatementSyntax& begin, const expression::ExpressionSyntax& end) {
  decDepth();
  createIndentation();
  ofs << "</ForStatementSyntax_Incrementors>\n";
}

void VisitorCSHARPML::visitForStatementSyntax_Initializers(const statement::ForStatementSyntax& begin, const expression::ExpressionSyntax& end) {
  createIndentation();
  ofs << "<ForStatementSyntax_Initializers>\n";
  incDepth();
}

void VisitorCSHARPML::visitEndForStatementSyntax_Initializers(const statement::ForStatementSyntax& begin, const expression::ExpressionSyntax& end) {
  decDepth();
  createIndentation();
  ofs << "</ForStatementSyntax_Initializers>\n";
}

void VisitorCSHARPML::visitForStatementSyntax_Statement(const statement::ForStatementSyntax& begin, const statement::StatementSyntax& end) {
  createIndentation();
  ofs << "<ForStatementSyntax_Statement>\n";
  incDepth();
}

void VisitorCSHARPML::visitEndForStatementSyntax_Statement(const statement::ForStatementSyntax& begin, const statement::StatementSyntax& end) {
  decDepth();
  createIndentation();
  ofs << "</ForStatementSyntax_Statement>\n";
}

void VisitorCSHARPML::visitGotoStatementSyntax_Expression(const statement::GotoStatementSyntax& begin, const expression::ExpressionSyntax& end) {
  createIndentation();
  ofs << "<GotoStatementSyntax_Expression>\n";
  incDepth();
}

void VisitorCSHARPML::visitEndGotoStatementSyntax_Expression(const statement::GotoStatementSyntax& begin, const expression::ExpressionSyntax& end) {
  decDepth();
  createIndentation();
  ofs << "</GotoStatementSyntax_Expression>\n";
}

void VisitorCSHARPML::visitIfStatementSyntax_Condition(const statement::IfStatementSyntax& begin, const expression::ExpressionSyntax& end) {
  createIndentation();
  ofs << "<IfStatementSyntax_Condition>\n";
  incDepth();
}

void VisitorCSHARPML::visitEndIfStatementSyntax_Condition(const statement::IfStatementSyntax& begin, const expression::ExpressionSyntax& end) {
  decDepth();
  createIndentation();
  ofs << "</IfStatementSyntax_Condition>\n";
}

void VisitorCSHARPML::visitIfStatementSyntax_Else(const statement::IfStatementSyntax& begin, const structure::ElseClauseSyntax& end) {
  createIndentation();
  ofs << "<IfStatementSyntax_Else>\n";
  incDepth();
}

void VisitorCSHARPML::visitEndIfStatementSyntax_Else(const statement::IfStatementSyntax& begin, const structure::ElseClauseSyntax& end) {
  decDepth();
  createIndentation();
  ofs << "</IfStatementSyntax_Else>\n";
}

void VisitorCSHARPML::visitIfStatementSyntax_Statement(const statement::IfStatementSyntax& begin, const statement::StatementSyntax& end) {
  createIndentation();
  ofs << "<IfStatementSyntax_Statement>\n";
  incDepth();
}

void VisitorCSHARPML::visitEndIfStatementSyntax_Statement(const statement::IfStatementSyntax& begin, const statement::StatementSyntax& end) {
  decDepth();
  createIndentation();
  ofs << "</IfStatementSyntax_Statement>\n";
}

void VisitorCSHARPML::visitLabeledStatementSyntax_Statement(const statement::LabeledStatementSyntax& begin, const statement::StatementSyntax& end) {
  createIndentation();
  ofs << "<LabeledStatementSyntax_Statement>\n";
  incDepth();
}

void VisitorCSHARPML::visitEndLabeledStatementSyntax_Statement(const statement::LabeledStatementSyntax& begin, const statement::StatementSyntax& end) {
  decDepth();
  createIndentation();
  ofs << "</LabeledStatementSyntax_Statement>\n";
}

void VisitorCSHARPML::visitLocalDeclarationStatementSyntax_Declaration(const statement::LocalDeclarationStatementSyntax& begin, const structure::VariableDeclarationSyntax& end) {
  createIndentation();
  ofs << "<LocalDeclarationStatementSyntax_Declaration>\n";
  incDepth();
}

void VisitorCSHARPML::visitEndLocalDeclarationStatementSyntax_Declaration(const statement::LocalDeclarationStatementSyntax& begin, const structure::VariableDeclarationSyntax& end) {
  decDepth();
  createIndentation();
  ofs << "</LocalDeclarationStatementSyntax_Declaration>\n";
}

void VisitorCSHARPML::visitLocalFunctionStatementSyntax_Body(const statement::LocalFunctionStatementSyntax& begin, const statement::BlockSyntax& end) {
  createIndentation();
  ofs << "<LocalFunctionStatementSyntax_Body>\n";
  incDepth();
}

void VisitorCSHARPML::visitEndLocalFunctionStatementSyntax_Body(const statement::LocalFunctionStatementSyntax& begin, const statement::BlockSyntax& end) {
  decDepth();
  createIndentation();
  ofs << "</LocalFunctionStatementSyntax_Body>\n";
}

void VisitorCSHARPML::visitLocalFunctionStatementSyntax_ConstraintClauses(const statement::LocalFunctionStatementSyntax& begin, const structure::TypeParameterConstraintClauseSyntax& end) {
  createIndentation();
  ofs << "<LocalFunctionStatementSyntax_ConstraintClauses>\n";
  incDepth();
}

void VisitorCSHARPML::visitEndLocalFunctionStatementSyntax_ConstraintClauses(const statement::LocalFunctionStatementSyntax& begin, const structure::TypeParameterConstraintClauseSyntax& end) {
  decDepth();
  createIndentation();
  ofs << "</LocalFunctionStatementSyntax_ConstraintClauses>\n";
}

void VisitorCSHARPML::visitLocalFunctionStatementSyntax_ExpressionBody(const statement::LocalFunctionStatementSyntax& begin, const structure::ArrowExpressionClauseSyntax& end) {
  createIndentation();
  ofs << "<LocalFunctionStatementSyntax_ExpressionBody>\n";
  incDepth();
}

void VisitorCSHARPML::visitEndLocalFunctionStatementSyntax_ExpressionBody(const statement::LocalFunctionStatementSyntax& begin, const structure::ArrowExpressionClauseSyntax& end) {
  decDepth();
  createIndentation();
  ofs << "</LocalFunctionStatementSyntax_ExpressionBody>\n";
}

void VisitorCSHARPML::visitLocalFunctionStatementSyntax_ParameterList(const statement::LocalFunctionStatementSyntax& begin, const structure::ParameterListSyntax& end) {
  createIndentation();
  ofs << "<LocalFunctionStatementSyntax_ParameterList>\n";
  incDepth();
}

void VisitorCSHARPML::visitEndLocalFunctionStatementSyntax_ParameterList(const statement::LocalFunctionStatementSyntax& begin, const structure::ParameterListSyntax& end) {
  decDepth();
  createIndentation();
  ofs << "</LocalFunctionStatementSyntax_ParameterList>\n";
}

void VisitorCSHARPML::visitLocalFunctionStatementSyntax_ReturnType(const statement::LocalFunctionStatementSyntax& begin, const expression::TypeSyntax& end) {
  createIndentation();
  ofs << "<LocalFunctionStatementSyntax_ReturnType>\n";
  incDepth();
}

void VisitorCSHARPML::visitEndLocalFunctionStatementSyntax_ReturnType(const statement::LocalFunctionStatementSyntax& begin, const expression::TypeSyntax& end) {
  decDepth();
  createIndentation();
  ofs << "</LocalFunctionStatementSyntax_ReturnType>\n";
}

void VisitorCSHARPML::visitLocalFunctionStatementSyntax_TypeParameterList(const statement::LocalFunctionStatementSyntax& begin, const structure::TypeParameterListSyntax& end) {
  createIndentation();
  ofs << "<LocalFunctionStatementSyntax_TypeParameterList>\n";
  incDepth();
}

void VisitorCSHARPML::visitEndLocalFunctionStatementSyntax_TypeParameterList(const statement::LocalFunctionStatementSyntax& begin, const structure::TypeParameterListSyntax& end) {
  decDepth();
  createIndentation();
  ofs << "</LocalFunctionStatementSyntax_TypeParameterList>\n";
}

void VisitorCSHARPML::visitLockStatementSyntax_Expression(const statement::LockStatementSyntax& begin, const expression::ExpressionSyntax& end) {
  createIndentation();
  ofs << "<LockStatementSyntax_Expression>\n";
  incDepth();
}

void VisitorCSHARPML::visitEndLockStatementSyntax_Expression(const statement::LockStatementSyntax& begin, const expression::ExpressionSyntax& end) {
  decDepth();
  createIndentation();
  ofs << "</LockStatementSyntax_Expression>\n";
}

void VisitorCSHARPML::visitLockStatementSyntax_Statement(const statement::LockStatementSyntax& begin, const statement::StatementSyntax& end) {
  createIndentation();
  ofs << "<LockStatementSyntax_Statement>\n";
  incDepth();
}

void VisitorCSHARPML::visitEndLockStatementSyntax_Statement(const statement::LockStatementSyntax& begin, const statement::StatementSyntax& end) {
  decDepth();
  createIndentation();
  ofs << "</LockStatementSyntax_Statement>\n";
}

void VisitorCSHARPML::visitReturnStatementSyntax_Expression(const statement::ReturnStatementSyntax& begin, const expression::ExpressionSyntax& end) {
  createIndentation();
  ofs << "<ReturnStatementSyntax_Expression>\n";
  incDepth();
}

void VisitorCSHARPML::visitEndReturnStatementSyntax_Expression(const statement::ReturnStatementSyntax& begin, const expression::ExpressionSyntax& end) {
  decDepth();
  createIndentation();
  ofs << "</ReturnStatementSyntax_Expression>\n";
}

void VisitorCSHARPML::visitStatementSyntax_AttributeLists(const statement::StatementSyntax& begin, const structure::AttributeListSyntax& end) {
  createIndentation();
  ofs << "<StatementSyntax_AttributeLists>\n";
  incDepth();
}

void VisitorCSHARPML::visitEndStatementSyntax_AttributeLists(const statement::StatementSyntax& begin, const structure::AttributeListSyntax& end) {
  decDepth();
  createIndentation();
  ofs << "</StatementSyntax_AttributeLists>\n";
}

void VisitorCSHARPML::visitSwitchStatementSyntax_Expression(const statement::SwitchStatementSyntax& begin, const expression::ExpressionSyntax& end) {
  createIndentation();
  ofs << "<SwitchStatementSyntax_Expression>\n";
  incDepth();
}

void VisitorCSHARPML::visitEndSwitchStatementSyntax_Expression(const statement::SwitchStatementSyntax& begin, const expression::ExpressionSyntax& end) {
  decDepth();
  createIndentation();
  ofs << "</SwitchStatementSyntax_Expression>\n";
}

void VisitorCSHARPML::visitSwitchStatementSyntax_Sections(const statement::SwitchStatementSyntax& begin, const structure::SwitchSectionSyntax& end) {
  createIndentation();
  ofs << "<SwitchStatementSyntax_Sections>\n";
  incDepth();
}

void VisitorCSHARPML::visitEndSwitchStatementSyntax_Sections(const statement::SwitchStatementSyntax& begin, const structure::SwitchSectionSyntax& end) {
  decDepth();
  createIndentation();
  ofs << "</SwitchStatementSyntax_Sections>\n";
}

void VisitorCSHARPML::visitThrowStatementSyntax_Expression(const statement::ThrowStatementSyntax& begin, const expression::ExpressionSyntax& end) {
  createIndentation();
  ofs << "<ThrowStatementSyntax_Expression>\n";
  incDepth();
}

void VisitorCSHARPML::visitEndThrowStatementSyntax_Expression(const statement::ThrowStatementSyntax& begin, const expression::ExpressionSyntax& end) {
  decDepth();
  createIndentation();
  ofs << "</ThrowStatementSyntax_Expression>\n";
}

void VisitorCSHARPML::visitTryStatementSyntax_Block(const statement::TryStatementSyntax& begin, const statement::BlockSyntax& end) {
  createIndentation();
  ofs << "<TryStatementSyntax_Block>\n";
  incDepth();
}

void VisitorCSHARPML::visitEndTryStatementSyntax_Block(const statement::TryStatementSyntax& begin, const statement::BlockSyntax& end) {
  decDepth();
  createIndentation();
  ofs << "</TryStatementSyntax_Block>\n";
}

void VisitorCSHARPML::visitTryStatementSyntax_Catches(const statement::TryStatementSyntax& begin, const structure::CatchClauseSyntax& end) {
  createIndentation();
  ofs << "<TryStatementSyntax_Catches>\n";
  incDepth();
}

void VisitorCSHARPML::visitEndTryStatementSyntax_Catches(const statement::TryStatementSyntax& begin, const structure::CatchClauseSyntax& end) {
  decDepth();
  createIndentation();
  ofs << "</TryStatementSyntax_Catches>\n";
}

void VisitorCSHARPML::visitTryStatementSyntax_Finally(const statement::TryStatementSyntax& begin, const structure::FinallyClauseSyntax& end) {
  createIndentation();
  ofs << "<TryStatementSyntax_Finally>\n";
  incDepth();
}

void VisitorCSHARPML::visitEndTryStatementSyntax_Finally(const statement::TryStatementSyntax& begin, const structure::FinallyClauseSyntax& end) {
  decDepth();
  createIndentation();
  ofs << "</TryStatementSyntax_Finally>\n";
}

void VisitorCSHARPML::visitUnsafeStatementSyntax_Block(const statement::UnsafeStatementSyntax& begin, const statement::BlockSyntax& end) {
  createIndentation();
  ofs << "<UnsafeStatementSyntax_Block>\n";
  incDepth();
}

void VisitorCSHARPML::visitEndUnsafeStatementSyntax_Block(const statement::UnsafeStatementSyntax& begin, const statement::BlockSyntax& end) {
  decDepth();
  createIndentation();
  ofs << "</UnsafeStatementSyntax_Block>\n";
}

void VisitorCSHARPML::visitUsingStatementSyntax_Declaration(const statement::UsingStatementSyntax& begin, const structure::VariableDeclarationSyntax& end) {
  createIndentation();
  ofs << "<UsingStatementSyntax_Declaration>\n";
  incDepth();
}

void VisitorCSHARPML::visitEndUsingStatementSyntax_Declaration(const statement::UsingStatementSyntax& begin, const structure::VariableDeclarationSyntax& end) {
  decDepth();
  createIndentation();
  ofs << "</UsingStatementSyntax_Declaration>\n";
}

void VisitorCSHARPML::visitUsingStatementSyntax_Expression(const statement::UsingStatementSyntax& begin, const expression::ExpressionSyntax& end) {
  createIndentation();
  ofs << "<UsingStatementSyntax_Expression>\n";
  incDepth();
}

void VisitorCSHARPML::visitEndUsingStatementSyntax_Expression(const statement::UsingStatementSyntax& begin, const expression::ExpressionSyntax& end) {
  decDepth();
  createIndentation();
  ofs << "</UsingStatementSyntax_Expression>\n";
}

void VisitorCSHARPML::visitUsingStatementSyntax_Statement(const statement::UsingStatementSyntax& begin, const statement::StatementSyntax& end) {
  createIndentation();
  ofs << "<UsingStatementSyntax_Statement>\n";
  incDepth();
}

void VisitorCSHARPML::visitEndUsingStatementSyntax_Statement(const statement::UsingStatementSyntax& begin, const statement::StatementSyntax& end) {
  decDepth();
  createIndentation();
  ofs << "</UsingStatementSyntax_Statement>\n";
}

void VisitorCSHARPML::visitWhileStatementSyntax_Condition(const statement::WhileStatementSyntax& begin, const expression::ExpressionSyntax& end) {
  createIndentation();
  ofs << "<WhileStatementSyntax_Condition>\n";
  incDepth();
}

void VisitorCSHARPML::visitEndWhileStatementSyntax_Condition(const statement::WhileStatementSyntax& begin, const expression::ExpressionSyntax& end) {
  decDepth();
  createIndentation();
  ofs << "</WhileStatementSyntax_Condition>\n";
}

void VisitorCSHARPML::visitWhileStatementSyntax_Statement(const statement::WhileStatementSyntax& begin, const statement::StatementSyntax& end) {
  createIndentation();
  ofs << "<WhileStatementSyntax_Statement>\n";
  incDepth();
}

void VisitorCSHARPML::visitEndWhileStatementSyntax_Statement(const statement::WhileStatementSyntax& begin, const statement::StatementSyntax& end) {
  decDepth();
  createIndentation();
  ofs << "</WhileStatementSyntax_Statement>\n";
}

void VisitorCSHARPML::visitYieldStatementSyntax_Expression(const statement::YieldStatementSyntax& begin, const expression::ExpressionSyntax& end) {
  createIndentation();
  ofs << "<YieldStatementSyntax_Expression>\n";
  incDepth();
}

void VisitorCSHARPML::visitEndYieldStatementSyntax_Expression(const statement::YieldStatementSyntax& begin, const expression::ExpressionSyntax& end) {
  decDepth();
  createIndentation();
  ofs << "</YieldStatementSyntax_Expression>\n";
}

void VisitorCSHARPML::visitAccessorDeclarationSyntax_AttributeLists(const structure::AccessorDeclarationSyntax& begin, const structure::AttributeListSyntax& end) {
  createIndentation();
  ofs << "<AccessorDeclarationSyntax_AttributeLists>\n";
  incDepth();
}

void VisitorCSHARPML::visitEndAccessorDeclarationSyntax_AttributeLists(const structure::AccessorDeclarationSyntax& begin, const structure::AttributeListSyntax& end) {
  decDepth();
  createIndentation();
  ofs << "</AccessorDeclarationSyntax_AttributeLists>\n";
}

void VisitorCSHARPML::visitAccessorDeclarationSyntax_Body(const structure::AccessorDeclarationSyntax& begin, const statement::BlockSyntax& end) {
  createIndentation();
  ofs << "<AccessorDeclarationSyntax_Body>\n";
  incDepth();
}

void VisitorCSHARPML::visitEndAccessorDeclarationSyntax_Body(const structure::AccessorDeclarationSyntax& begin, const statement::BlockSyntax& end) {
  decDepth();
  createIndentation();
  ofs << "</AccessorDeclarationSyntax_Body>\n";
}

void VisitorCSHARPML::visitAccessorDeclarationSyntax_ExpressionBody(const structure::AccessorDeclarationSyntax& begin, const structure::ArrowExpressionClauseSyntax& end) {
  createIndentation();
  ofs << "<AccessorDeclarationSyntax_ExpressionBody>\n";
  incDepth();
}

void VisitorCSHARPML::visitEndAccessorDeclarationSyntax_ExpressionBody(const structure::AccessorDeclarationSyntax& begin, const structure::ArrowExpressionClauseSyntax& end) {
  decDepth();
  createIndentation();
  ofs << "</AccessorDeclarationSyntax_ExpressionBody>\n";
}

void VisitorCSHARPML::visitAccessorListSyntax_Accessors(const structure::AccessorListSyntax& begin, const structure::AccessorDeclarationSyntax& end) {
  createIndentation();
  ofs << "<AccessorListSyntax_Accessors>\n";
  incDepth();
}

void VisitorCSHARPML::visitEndAccessorListSyntax_Accessors(const structure::AccessorListSyntax& begin, const structure::AccessorDeclarationSyntax& end) {
  decDepth();
  createIndentation();
  ofs << "</AccessorListSyntax_Accessors>\n";
}

void VisitorCSHARPML::visitAnonymousObjectMemberDeclaratorSyntax_Expression(const structure::AnonymousObjectMemberDeclaratorSyntax& begin, const expression::ExpressionSyntax& end) {
  createIndentation();
  ofs << "<AnonymousObjectMemberDeclaratorSyntax_Expression>\n";
  incDepth();
}

void VisitorCSHARPML::visitEndAnonymousObjectMemberDeclaratorSyntax_Expression(const structure::AnonymousObjectMemberDeclaratorSyntax& begin, const expression::ExpressionSyntax& end) {
  decDepth();
  createIndentation();
  ofs << "</AnonymousObjectMemberDeclaratorSyntax_Expression>\n";
}

void VisitorCSHARPML::visitAnonymousObjectMemberDeclaratorSyntax_NameEquals(const structure::AnonymousObjectMemberDeclaratorSyntax& begin, const structure::NameEqualsSyntax& end) {
  createIndentation();
  ofs << "<AnonymousObjectMemberDeclaratorSyntax_NameEquals>\n";
  incDepth();
}

void VisitorCSHARPML::visitEndAnonymousObjectMemberDeclaratorSyntax_NameEquals(const structure::AnonymousObjectMemberDeclaratorSyntax& begin, const structure::NameEqualsSyntax& end) {
  decDepth();
  createIndentation();
  ofs << "</AnonymousObjectMemberDeclaratorSyntax_NameEquals>\n";
}

void VisitorCSHARPML::visitArgumentSyntax_Expression(const structure::ArgumentSyntax& begin, const expression::ExpressionSyntax& end) {
  createIndentation();
  ofs << "<ArgumentSyntax_Expression>\n";
  incDepth();
}

void VisitorCSHARPML::visitEndArgumentSyntax_Expression(const structure::ArgumentSyntax& begin, const expression::ExpressionSyntax& end) {
  decDepth();
  createIndentation();
  ofs << "</ArgumentSyntax_Expression>\n";
}

void VisitorCSHARPML::visitArgumentSyntax_NameColon(const structure::ArgumentSyntax& begin, const structure::NameColonSyntax& end) {
  createIndentation();
  ofs << "<ArgumentSyntax_NameColon>\n";
  incDepth();
}

void VisitorCSHARPML::visitEndArgumentSyntax_NameColon(const structure::ArgumentSyntax& begin, const structure::NameColonSyntax& end) {
  decDepth();
  createIndentation();
  ofs << "</ArgumentSyntax_NameColon>\n";
}

void VisitorCSHARPML::visitArrayRankSpecifierSyntax_Sizes(const structure::ArrayRankSpecifierSyntax& begin, const expression::ExpressionSyntax& end) {
  createIndentation();
  ofs << "<ArrayRankSpecifierSyntax_Sizes>\n";
  incDepth();
}

void VisitorCSHARPML::visitEndArrayRankSpecifierSyntax_Sizes(const structure::ArrayRankSpecifierSyntax& begin, const expression::ExpressionSyntax& end) {
  decDepth();
  createIndentation();
  ofs << "</ArrayRankSpecifierSyntax_Sizes>\n";
}

void VisitorCSHARPML::visitArrowExpressionClauseSyntax_Expression(const structure::ArrowExpressionClauseSyntax& begin, const expression::ExpressionSyntax& end) {
  createIndentation();
  ofs << "<ArrowExpressionClauseSyntax_Expression>\n";
  incDepth();
}

void VisitorCSHARPML::visitEndArrowExpressionClauseSyntax_Expression(const structure::ArrowExpressionClauseSyntax& begin, const expression::ExpressionSyntax& end) {
  decDepth();
  createIndentation();
  ofs << "</ArrowExpressionClauseSyntax_Expression>\n";
}

void VisitorCSHARPML::visitAttributeArgumentListSyntax_Arguments(const structure::AttributeArgumentListSyntax& begin, const structure::AttributeArgumentSyntax& end) {
  createIndentation();
  ofs << "<AttributeArgumentListSyntax_Arguments>\n";
  incDepth();
}

void VisitorCSHARPML::visitEndAttributeArgumentListSyntax_Arguments(const structure::AttributeArgumentListSyntax& begin, const structure::AttributeArgumentSyntax& end) {
  decDepth();
  createIndentation();
  ofs << "</AttributeArgumentListSyntax_Arguments>\n";
}

void VisitorCSHARPML::visitAttributeArgumentSyntax_Expression(const structure::AttributeArgumentSyntax& begin, const expression::ExpressionSyntax& end) {
  createIndentation();
  ofs << "<AttributeArgumentSyntax_Expression>\n";
  incDepth();
}

void VisitorCSHARPML::visitEndAttributeArgumentSyntax_Expression(const structure::AttributeArgumentSyntax& begin, const expression::ExpressionSyntax& end) {
  decDepth();
  createIndentation();
  ofs << "</AttributeArgumentSyntax_Expression>\n";
}

void VisitorCSHARPML::visitAttributeArgumentSyntax_NameColon(const structure::AttributeArgumentSyntax& begin, const structure::NameColonSyntax& end) {
  createIndentation();
  ofs << "<AttributeArgumentSyntax_NameColon>\n";
  incDepth();
}

void VisitorCSHARPML::visitEndAttributeArgumentSyntax_NameColon(const structure::AttributeArgumentSyntax& begin, const structure::NameColonSyntax& end) {
  decDepth();
  createIndentation();
  ofs << "</AttributeArgumentSyntax_NameColon>\n";
}

void VisitorCSHARPML::visitAttributeArgumentSyntax_NameEquals(const structure::AttributeArgumentSyntax& begin, const structure::NameEqualsSyntax& end) {
  createIndentation();
  ofs << "<AttributeArgumentSyntax_NameEquals>\n";
  incDepth();
}

void VisitorCSHARPML::visitEndAttributeArgumentSyntax_NameEquals(const structure::AttributeArgumentSyntax& begin, const structure::NameEqualsSyntax& end) {
  decDepth();
  createIndentation();
  ofs << "</AttributeArgumentSyntax_NameEquals>\n";
}

void VisitorCSHARPML::visitAttributeListSyntax_Attributes(const structure::AttributeListSyntax& begin, const structure::AttributeSyntax& end) {
  createIndentation();
  ofs << "<AttributeListSyntax_Attributes>\n";
  incDepth();
}

void VisitorCSHARPML::visitEndAttributeListSyntax_Attributes(const structure::AttributeListSyntax& begin, const structure::AttributeSyntax& end) {
  decDepth();
  createIndentation();
  ofs << "</AttributeListSyntax_Attributes>\n";
}

void VisitorCSHARPML::visitAttributeListSyntax_Target(const structure::AttributeListSyntax& begin, const structure::AttributeTargetSpecifierSyntax& end) {
  createIndentation();
  ofs << "<AttributeListSyntax_Target>\n";
  incDepth();
}

void VisitorCSHARPML::visitEndAttributeListSyntax_Target(const structure::AttributeListSyntax& begin, const structure::AttributeTargetSpecifierSyntax& end) {
  decDepth();
  createIndentation();
  ofs << "</AttributeListSyntax_Target>\n";
}

void VisitorCSHARPML::visitAttributeSyntax_ArgumentList(const structure::AttributeSyntax& begin, const structure::AttributeArgumentListSyntax& end) {
  createIndentation();
  ofs << "<AttributeSyntax_ArgumentList>\n";
  incDepth();
}

void VisitorCSHARPML::visitEndAttributeSyntax_ArgumentList(const structure::AttributeSyntax& begin, const structure::AttributeArgumentListSyntax& end) {
  decDepth();
  createIndentation();
  ofs << "</AttributeSyntax_ArgumentList>\n";
}

void VisitorCSHARPML::visitAttributeSyntax_Name(const structure::AttributeSyntax& begin, const expression::NameSyntax& end) {
  createIndentation();
  ofs << "<AttributeSyntax_Name>\n";
  incDepth();
}

void VisitorCSHARPML::visitEndAttributeSyntax_Name(const structure::AttributeSyntax& begin, const expression::NameSyntax& end) {
  decDepth();
  createIndentation();
  ofs << "</AttributeSyntax_Name>\n";
}

void VisitorCSHARPML::visitBaseArgumentListSyntax_Arguments(const structure::BaseArgumentListSyntax& begin, const structure::ArgumentSyntax& end) {
  createIndentation();
  ofs << "<BaseArgumentListSyntax_Arguments>\n";
  incDepth();
}

void VisitorCSHARPML::visitEndBaseArgumentListSyntax_Arguments(const structure::BaseArgumentListSyntax& begin, const structure::ArgumentSyntax& end) {
  decDepth();
  createIndentation();
  ofs << "</BaseArgumentListSyntax_Arguments>\n";
}

void VisitorCSHARPML::visitBaseCrefParameterListSyntax_Parameters(const structure::BaseCrefParameterListSyntax& begin, const structure::CrefParameterSyntax& end) {
  createIndentation();
  ofs << "<BaseCrefParameterListSyntax_Parameters>\n";
  incDepth();
}

void VisitorCSHARPML::visitEndBaseCrefParameterListSyntax_Parameters(const structure::BaseCrefParameterListSyntax& begin, const structure::CrefParameterSyntax& end) {
  decDepth();
  createIndentation();
  ofs << "</BaseCrefParameterListSyntax_Parameters>\n";
}

void VisitorCSHARPML::visitBaseFieldDeclarationSyntax_AttributeLists(const structure::BaseFieldDeclarationSyntax& begin, const structure::AttributeListSyntax& end) {
  createIndentation();
  ofs << "<BaseFieldDeclarationSyntax_AttributeLists>\n";
  incDepth();
}

void VisitorCSHARPML::visitEndBaseFieldDeclarationSyntax_AttributeLists(const structure::BaseFieldDeclarationSyntax& begin, const structure::AttributeListSyntax& end) {
  decDepth();
  createIndentation();
  ofs << "</BaseFieldDeclarationSyntax_AttributeLists>\n";
}

void VisitorCSHARPML::visitBaseFieldDeclarationSyntax_Declaration(const structure::BaseFieldDeclarationSyntax& begin, const structure::VariableDeclarationSyntax& end) {
  createIndentation();
  ofs << "<BaseFieldDeclarationSyntax_Declaration>\n";
  incDepth();
}

void VisitorCSHARPML::visitEndBaseFieldDeclarationSyntax_Declaration(const structure::BaseFieldDeclarationSyntax& begin, const structure::VariableDeclarationSyntax& end) {
  decDepth();
  createIndentation();
  ofs << "</BaseFieldDeclarationSyntax_Declaration>\n";
}

void VisitorCSHARPML::visitBaseListSyntax_Types(const structure::BaseListSyntax& begin, const structure::BaseTypeSyntax& end) {
  createIndentation();
  ofs << "<BaseListSyntax_Types>\n";
  incDepth();
}

void VisitorCSHARPML::visitEndBaseListSyntax_Types(const structure::BaseListSyntax& begin, const structure::BaseTypeSyntax& end) {
  decDepth();
  createIndentation();
  ofs << "</BaseListSyntax_Types>\n";
}

void VisitorCSHARPML::visitBaseMethodDeclarationSyntax_AccessedEnumMembers(const structure::BaseMethodDeclarationSyntax& begin, const structure::EnumMemberDeclarationSyntax& end) {
  createIndentation();
  ofs << "<BaseMethodDeclarationSyntax_AccessedEnumMembers ref='";
  if (!noId)
    ofs << "id" << end.getId();
  ofs << "'/>\n";
}

void VisitorCSHARPML::visitEndBaseMethodDeclarationSyntax_AccessedEnumMembers(const structure::BaseMethodDeclarationSyntax& begin, const structure::EnumMemberDeclarationSyntax& end) {
}

void VisitorCSHARPML::visitBaseMethodDeclarationSyntax_AttributeLists(const structure::BaseMethodDeclarationSyntax& begin, const structure::AttributeListSyntax& end) {
  createIndentation();
  ofs << "<BaseMethodDeclarationSyntax_AttributeLists>\n";
  incDepth();
}

void VisitorCSHARPML::visitEndBaseMethodDeclarationSyntax_AttributeLists(const structure::BaseMethodDeclarationSyntax& begin, const structure::AttributeListSyntax& end) {
  decDepth();
  createIndentation();
  ofs << "</BaseMethodDeclarationSyntax_AttributeLists>\n";
}

void VisitorCSHARPML::visitBaseMethodDeclarationSyntax_Body(const structure::BaseMethodDeclarationSyntax& begin, const statement::BlockSyntax& end) {
  createIndentation();
  ofs << "<BaseMethodDeclarationSyntax_Body>\n";
  incDepth();
}

void VisitorCSHARPML::visitEndBaseMethodDeclarationSyntax_Body(const structure::BaseMethodDeclarationSyntax& begin, const statement::BlockSyntax& end) {
  decDepth();
  createIndentation();
  ofs << "</BaseMethodDeclarationSyntax_Body>\n";
}

void VisitorCSHARPML::visitBaseMethodDeclarationSyntax_ExpressionBody(const structure::BaseMethodDeclarationSyntax& begin, const structure::ArrowExpressionClauseSyntax& end) {
  createIndentation();
  ofs << "<BaseMethodDeclarationSyntax_ExpressionBody>\n";
  incDepth();
}

void VisitorCSHARPML::visitEndBaseMethodDeclarationSyntax_ExpressionBody(const structure::BaseMethodDeclarationSyntax& begin, const structure::ArrowExpressionClauseSyntax& end) {
  decDepth();
  createIndentation();
  ofs << "</BaseMethodDeclarationSyntax_ExpressionBody>\n";
}

void VisitorCSHARPML::visitBaseMethodDeclarationSyntax_ParameterList(const structure::BaseMethodDeclarationSyntax& begin, const structure::ParameterListSyntax& end) {
  createIndentation();
  ofs << "<BaseMethodDeclarationSyntax_ParameterList>\n";
  incDepth();
}

void VisitorCSHARPML::visitEndBaseMethodDeclarationSyntax_ParameterList(const structure::BaseMethodDeclarationSyntax& begin, const structure::ParameterListSyntax& end) {
  decDepth();
  createIndentation();
  ofs << "</BaseMethodDeclarationSyntax_ParameterList>\n";
}

void VisitorCSHARPML::visitBaseParameterListSyntax_Parameters(const structure::BaseParameterListSyntax& begin, const structure::ParameterSyntax& end) {
  createIndentation();
  ofs << "<BaseParameterListSyntax_Parameters>\n";
  incDepth();
}

void VisitorCSHARPML::visitEndBaseParameterListSyntax_Parameters(const structure::BaseParameterListSyntax& begin, const structure::ParameterSyntax& end) {
  decDepth();
  createIndentation();
  ofs << "</BaseParameterListSyntax_Parameters>\n";
}

void VisitorCSHARPML::visitBasePropertyDeclarationSyntax_AccessorList(const structure::BasePropertyDeclarationSyntax& begin, const structure::AccessorListSyntax& end) {
  createIndentation();
  ofs << "<BasePropertyDeclarationSyntax_AccessorList>\n";
  incDepth();
}

void VisitorCSHARPML::visitEndBasePropertyDeclarationSyntax_AccessorList(const structure::BasePropertyDeclarationSyntax& begin, const structure::AccessorListSyntax& end) {
  decDepth();
  createIndentation();
  ofs << "</BasePropertyDeclarationSyntax_AccessorList>\n";
}

void VisitorCSHARPML::visitBasePropertyDeclarationSyntax_AttributeLists(const structure::BasePropertyDeclarationSyntax& begin, const structure::AttributeListSyntax& end) {
  createIndentation();
  ofs << "<BasePropertyDeclarationSyntax_AttributeLists>\n";
  incDepth();
}

void VisitorCSHARPML::visitEndBasePropertyDeclarationSyntax_AttributeLists(const structure::BasePropertyDeclarationSyntax& begin, const structure::AttributeListSyntax& end) {
  decDepth();
  createIndentation();
  ofs << "</BasePropertyDeclarationSyntax_AttributeLists>\n";
}

void VisitorCSHARPML::visitBasePropertyDeclarationSyntax_ExplicitInterfaceSpecifier(const structure::BasePropertyDeclarationSyntax& begin, const structure::ExplicitInterfaceSpecifierSyntax& end) {
  createIndentation();
  ofs << "<BasePropertyDeclarationSyntax_ExplicitInterfaceSpecifier>\n";
  incDepth();
}

void VisitorCSHARPML::visitEndBasePropertyDeclarationSyntax_ExplicitInterfaceSpecifier(const structure::BasePropertyDeclarationSyntax& begin, const structure::ExplicitInterfaceSpecifierSyntax& end) {
  decDepth();
  createIndentation();
  ofs << "</BasePropertyDeclarationSyntax_ExplicitInterfaceSpecifier>\n";
}

void VisitorCSHARPML::visitBasePropertyDeclarationSyntax_Type(const structure::BasePropertyDeclarationSyntax& begin, const expression::TypeSyntax& end) {
  createIndentation();
  ofs << "<BasePropertyDeclarationSyntax_Type>\n";
  incDepth();
}

void VisitorCSHARPML::visitEndBasePropertyDeclarationSyntax_Type(const structure::BasePropertyDeclarationSyntax& begin, const expression::TypeSyntax& end) {
  decDepth();
  createIndentation();
  ofs << "</BasePropertyDeclarationSyntax_Type>\n";
}

void VisitorCSHARPML::visitBaseTypeDeclarationSyntax_AttributeLists(const structure::BaseTypeDeclarationSyntax& begin, const structure::AttributeListSyntax& end) {
  createIndentation();
  ofs << "<BaseTypeDeclarationSyntax_AttributeLists>\n";
  incDepth();
}

void VisitorCSHARPML::visitEndBaseTypeDeclarationSyntax_AttributeLists(const structure::BaseTypeDeclarationSyntax& begin, const structure::AttributeListSyntax& end) {
  decDepth();
  createIndentation();
  ofs << "</BaseTypeDeclarationSyntax_AttributeLists>\n";
}

void VisitorCSHARPML::visitBaseTypeDeclarationSyntax_BaseList(const structure::BaseTypeDeclarationSyntax& begin, const structure::BaseListSyntax& end) {
  createIndentation();
  ofs << "<BaseTypeDeclarationSyntax_BaseList>\n";
  incDepth();
}

void VisitorCSHARPML::visitEndBaseTypeDeclarationSyntax_BaseList(const structure::BaseTypeDeclarationSyntax& begin, const structure::BaseListSyntax& end) {
  decDepth();
  createIndentation();
  ofs << "</BaseTypeDeclarationSyntax_BaseList>\n";
}

void VisitorCSHARPML::visitBaseTypeSyntax_Type(const structure::BaseTypeSyntax& begin, const expression::TypeSyntax& end) {
  createIndentation();
  ofs << "<BaseTypeSyntax_Type>\n";
  incDepth();
}

void VisitorCSHARPML::visitEndBaseTypeSyntax_Type(const structure::BaseTypeSyntax& begin, const expression::TypeSyntax& end) {
  decDepth();
  createIndentation();
  ofs << "</BaseTypeSyntax_Type>\n";
}

void VisitorCSHARPML::visitCasePatternSwitchLabelSyntax_Pattern(const structure::CasePatternSwitchLabelSyntax& begin, const structure::PatternSyntax& end) {
  createIndentation();
  ofs << "<CasePatternSwitchLabelSyntax_Pattern>\n";
  incDepth();
}

void VisitorCSHARPML::visitEndCasePatternSwitchLabelSyntax_Pattern(const structure::CasePatternSwitchLabelSyntax& begin, const structure::PatternSyntax& end) {
  decDepth();
  createIndentation();
  ofs << "</CasePatternSwitchLabelSyntax_Pattern>\n";
}

void VisitorCSHARPML::visitCasePatternSwitchLabelSyntax_WhenClause(const structure::CasePatternSwitchLabelSyntax& begin, const structure::WhenClauseSyntax& end) {
  createIndentation();
  ofs << "<CasePatternSwitchLabelSyntax_WhenClause>\n";
  incDepth();
}

void VisitorCSHARPML::visitEndCasePatternSwitchLabelSyntax_WhenClause(const structure::CasePatternSwitchLabelSyntax& begin, const structure::WhenClauseSyntax& end) {
  decDepth();
  createIndentation();
  ofs << "</CasePatternSwitchLabelSyntax_WhenClause>\n";
}

void VisitorCSHARPML::visitCaseSwitchLabelSyntax_Value(const structure::CaseSwitchLabelSyntax& begin, const expression::ExpressionSyntax& end) {
  createIndentation();
  ofs << "<CaseSwitchLabelSyntax_Value>\n";
  incDepth();
}

void VisitorCSHARPML::visitEndCaseSwitchLabelSyntax_Value(const structure::CaseSwitchLabelSyntax& begin, const expression::ExpressionSyntax& end) {
  decDepth();
  createIndentation();
  ofs << "</CaseSwitchLabelSyntax_Value>\n";
}

void VisitorCSHARPML::visitCatchClauseSyntax_Block(const structure::CatchClauseSyntax& begin, const statement::BlockSyntax& end) {
  createIndentation();
  ofs << "<CatchClauseSyntax_Block>\n";
  incDepth();
}

void VisitorCSHARPML::visitEndCatchClauseSyntax_Block(const structure::CatchClauseSyntax& begin, const statement::BlockSyntax& end) {
  decDepth();
  createIndentation();
  ofs << "</CatchClauseSyntax_Block>\n";
}

void VisitorCSHARPML::visitCatchClauseSyntax_Declaration(const structure::CatchClauseSyntax& begin, const structure::CatchDeclarationSyntax& end) {
  createIndentation();
  ofs << "<CatchClauseSyntax_Declaration>\n";
  incDepth();
}

void VisitorCSHARPML::visitEndCatchClauseSyntax_Declaration(const structure::CatchClauseSyntax& begin, const structure::CatchDeclarationSyntax& end) {
  decDepth();
  createIndentation();
  ofs << "</CatchClauseSyntax_Declaration>\n";
}

void VisitorCSHARPML::visitCatchClauseSyntax_Filter(const structure::CatchClauseSyntax& begin, const structure::CatchFilterClauseSyntax& end) {
  createIndentation();
  ofs << "<CatchClauseSyntax_Filter>\n";
  incDepth();
}

void VisitorCSHARPML::visitEndCatchClauseSyntax_Filter(const structure::CatchClauseSyntax& begin, const structure::CatchFilterClauseSyntax& end) {
  decDepth();
  createIndentation();
  ofs << "</CatchClauseSyntax_Filter>\n";
}

void VisitorCSHARPML::visitCatchDeclarationSyntax_Type(const structure::CatchDeclarationSyntax& begin, const expression::TypeSyntax& end) {
  createIndentation();
  ofs << "<CatchDeclarationSyntax_Type>\n";
  incDepth();
}

void VisitorCSHARPML::visitEndCatchDeclarationSyntax_Type(const structure::CatchDeclarationSyntax& begin, const expression::TypeSyntax& end) {
  decDepth();
  createIndentation();
  ofs << "</CatchDeclarationSyntax_Type>\n";
}

void VisitorCSHARPML::visitCatchFilterClauseSyntax_FilterExpression(const structure::CatchFilterClauseSyntax& begin, const expression::ExpressionSyntax& end) {
  createIndentation();
  ofs << "<CatchFilterClauseSyntax_FilterExpression>\n";
  incDepth();
}

void VisitorCSHARPML::visitEndCatchFilterClauseSyntax_FilterExpression(const structure::CatchFilterClauseSyntax& begin, const expression::ExpressionSyntax& end) {
  decDepth();
  createIndentation();
  ofs << "</CatchFilterClauseSyntax_FilterExpression>\n";
}

void VisitorCSHARPML::visitCompilationUnitSyntax_AttributeLists(const structure::CompilationUnitSyntax& begin, const structure::AttributeListSyntax& end) {
  createIndentation();
  ofs << "<CompilationUnitSyntax_AttributeLists>\n";
  incDepth();
}

void VisitorCSHARPML::visitEndCompilationUnitSyntax_AttributeLists(const structure::CompilationUnitSyntax& begin, const structure::AttributeListSyntax& end) {
  decDepth();
  createIndentation();
  ofs << "</CompilationUnitSyntax_AttributeLists>\n";
}

void VisitorCSHARPML::visitCompilationUnitSyntax_Externs(const structure::CompilationUnitSyntax& begin, const structure::ExternAliasDirectiveSyntax& end) {
  createIndentation();
  ofs << "<CompilationUnitSyntax_Externs>\n";
  incDepth();
}

void VisitorCSHARPML::visitEndCompilationUnitSyntax_Externs(const structure::CompilationUnitSyntax& begin, const structure::ExternAliasDirectiveSyntax& end) {
  decDepth();
  createIndentation();
  ofs << "</CompilationUnitSyntax_Externs>\n";
}

void VisitorCSHARPML::visitCompilationUnitSyntax_Members(const structure::CompilationUnitSyntax& begin, const structure::MemberDeclarationSyntax& end) {
  createIndentation();
  ofs << "<CompilationUnitSyntax_Members>\n";
  incDepth();
}

void VisitorCSHARPML::visitEndCompilationUnitSyntax_Members(const structure::CompilationUnitSyntax& begin, const structure::MemberDeclarationSyntax& end) {
  decDepth();
  createIndentation();
  ofs << "</CompilationUnitSyntax_Members>\n";
}

void VisitorCSHARPML::visitCompilationUnitSyntax_Usings(const structure::CompilationUnitSyntax& begin, const structure::UsingDirectiveSyntax& end) {
  createIndentation();
  ofs << "<CompilationUnitSyntax_Usings>\n";
  incDepth();
}

void VisitorCSHARPML::visitEndCompilationUnitSyntax_Usings(const structure::CompilationUnitSyntax& begin, const structure::UsingDirectiveSyntax& end) {
  decDepth();
  createIndentation();
  ofs << "</CompilationUnitSyntax_Usings>\n";
}

void VisitorCSHARPML::visitConstantPatternSyntax_Expression(const structure::ConstantPatternSyntax& begin, const expression::ExpressionSyntax& end) {
  createIndentation();
  ofs << "<ConstantPatternSyntax_Expression>\n";
  incDepth();
}

void VisitorCSHARPML::visitEndConstantPatternSyntax_Expression(const structure::ConstantPatternSyntax& begin, const expression::ExpressionSyntax& end) {
  decDepth();
  createIndentation();
  ofs << "</ConstantPatternSyntax_Expression>\n";
}

void VisitorCSHARPML::visitConstructorDeclarationSyntax_Initializer(const structure::ConstructorDeclarationSyntax& begin, const structure::ConstructorInitializerSyntax& end) {
  createIndentation();
  ofs << "<ConstructorDeclarationSyntax_Initializer>\n";
  incDepth();
}

void VisitorCSHARPML::visitEndConstructorDeclarationSyntax_Initializer(const structure::ConstructorDeclarationSyntax& begin, const structure::ConstructorInitializerSyntax& end) {
  decDepth();
  createIndentation();
  ofs << "</ConstructorDeclarationSyntax_Initializer>\n";
}

void VisitorCSHARPML::visitConstructorInitializerSyntax_ArgumentList(const structure::ConstructorInitializerSyntax& begin, const structure::ArgumentListSyntax& end) {
  createIndentation();
  ofs << "<ConstructorInitializerSyntax_ArgumentList>\n";
  incDepth();
}

void VisitorCSHARPML::visitEndConstructorInitializerSyntax_ArgumentList(const structure::ConstructorInitializerSyntax& begin, const structure::ArgumentListSyntax& end) {
  decDepth();
  createIndentation();
  ofs << "</ConstructorInitializerSyntax_ArgumentList>\n";
}

void VisitorCSHARPML::visitConstructorInitializerSyntax_ConstructorCall(const structure::ConstructorInitializerSyntax& begin, const structure::ConstructorDeclarationSyntax& end) {
  createIndentation();
  ofs << "<ConstructorInitializerSyntax_ConstructorCall ref='";
  if (!noId)
    ofs << "id" << end.getId();
  ofs << "'/>\n";
}

void VisitorCSHARPML::visitEndConstructorInitializerSyntax_ConstructorCall(const structure::ConstructorInitializerSyntax& begin, const structure::ConstructorDeclarationSyntax& end) {
}

void VisitorCSHARPML::visitConversionOperatorDeclarationSyntax_Type(const structure::ConversionOperatorDeclarationSyntax& begin, const expression::TypeSyntax& end) {
  createIndentation();
  ofs << "<ConversionOperatorDeclarationSyntax_Type>\n";
  incDepth();
}

void VisitorCSHARPML::visitEndConversionOperatorDeclarationSyntax_Type(const structure::ConversionOperatorDeclarationSyntax& begin, const expression::TypeSyntax& end) {
  decDepth();
  createIndentation();
  ofs << "</ConversionOperatorDeclarationSyntax_Type>\n";
}

void VisitorCSHARPML::visitConversionOperatorMemberCrefSyntax_Parameters(const structure::ConversionOperatorMemberCrefSyntax& begin, const structure::CrefParameterListSyntax& end) {
  createIndentation();
  ofs << "<ConversionOperatorMemberCrefSyntax_Parameters>\n";
  incDepth();
}

void VisitorCSHARPML::visitEndConversionOperatorMemberCrefSyntax_Parameters(const structure::ConversionOperatorMemberCrefSyntax& begin, const structure::CrefParameterListSyntax& end) {
  decDepth();
  createIndentation();
  ofs << "</ConversionOperatorMemberCrefSyntax_Parameters>\n";
}

void VisitorCSHARPML::visitConversionOperatorMemberCrefSyntax_Type(const structure::ConversionOperatorMemberCrefSyntax& begin, const expression::TypeSyntax& end) {
  createIndentation();
  ofs << "<ConversionOperatorMemberCrefSyntax_Type>\n";
  incDepth();
}

void VisitorCSHARPML::visitEndConversionOperatorMemberCrefSyntax_Type(const structure::ConversionOperatorMemberCrefSyntax& begin, const expression::TypeSyntax& end) {
  decDepth();
  createIndentation();
  ofs << "</ConversionOperatorMemberCrefSyntax_Type>\n";
}

void VisitorCSHARPML::visitCrefParameterSyntax_Type(const structure::CrefParameterSyntax& begin, const expression::TypeSyntax& end) {
  createIndentation();
  ofs << "<CrefParameterSyntax_Type>\n";
  incDepth();
}

void VisitorCSHARPML::visitEndCrefParameterSyntax_Type(const structure::CrefParameterSyntax& begin, const expression::TypeSyntax& end) {
  decDepth();
  createIndentation();
  ofs << "</CrefParameterSyntax_Type>\n";
}

void VisitorCSHARPML::visitDeclarationPatternSyntax_Designation(const structure::DeclarationPatternSyntax& begin, const structure::VariableDesignationSyntax& end) {
  createIndentation();
  ofs << "<DeclarationPatternSyntax_Designation>\n";
  incDepth();
}

void VisitorCSHARPML::visitEndDeclarationPatternSyntax_Designation(const structure::DeclarationPatternSyntax& begin, const structure::VariableDesignationSyntax& end) {
  decDepth();
  createIndentation();
  ofs << "</DeclarationPatternSyntax_Designation>\n";
}

void VisitorCSHARPML::visitDeclarationPatternSyntax_Type(const structure::DeclarationPatternSyntax& begin, const expression::TypeSyntax& end) {
  createIndentation();
  ofs << "<DeclarationPatternSyntax_Type>\n";
  incDepth();
}

void VisitorCSHARPML::visitEndDeclarationPatternSyntax_Type(const structure::DeclarationPatternSyntax& begin, const expression::TypeSyntax& end) {
  decDepth();
  createIndentation();
  ofs << "</DeclarationPatternSyntax_Type>\n";
}

void VisitorCSHARPML::visitDelegateDeclarationSyntax_AttributeLists(const structure::DelegateDeclarationSyntax& begin, const structure::AttributeListSyntax& end) {
  createIndentation();
  ofs << "<DelegateDeclarationSyntax_AttributeLists>\n";
  incDepth();
}

void VisitorCSHARPML::visitEndDelegateDeclarationSyntax_AttributeLists(const structure::DelegateDeclarationSyntax& begin, const structure::AttributeListSyntax& end) {
  decDepth();
  createIndentation();
  ofs << "</DelegateDeclarationSyntax_AttributeLists>\n";
}

void VisitorCSHARPML::visitDelegateDeclarationSyntax_ConstraintClauses(const structure::DelegateDeclarationSyntax& begin, const structure::TypeParameterConstraintClauseSyntax& end) {
  createIndentation();
  ofs << "<DelegateDeclarationSyntax_ConstraintClauses>\n";
  incDepth();
}

void VisitorCSHARPML::visitEndDelegateDeclarationSyntax_ConstraintClauses(const structure::DelegateDeclarationSyntax& begin, const structure::TypeParameterConstraintClauseSyntax& end) {
  decDepth();
  createIndentation();
  ofs << "</DelegateDeclarationSyntax_ConstraintClauses>\n";
}

void VisitorCSHARPML::visitDelegateDeclarationSyntax_ParameterList(const structure::DelegateDeclarationSyntax& begin, const structure::ParameterListSyntax& end) {
  createIndentation();
  ofs << "<DelegateDeclarationSyntax_ParameterList>\n";
  incDepth();
}

void VisitorCSHARPML::visitEndDelegateDeclarationSyntax_ParameterList(const structure::DelegateDeclarationSyntax& begin, const structure::ParameterListSyntax& end) {
  decDepth();
  createIndentation();
  ofs << "</DelegateDeclarationSyntax_ParameterList>\n";
}

void VisitorCSHARPML::visitDelegateDeclarationSyntax_ReturnType(const structure::DelegateDeclarationSyntax& begin, const expression::TypeSyntax& end) {
  createIndentation();
  ofs << "<DelegateDeclarationSyntax_ReturnType>\n";
  incDepth();
}

void VisitorCSHARPML::visitEndDelegateDeclarationSyntax_ReturnType(const structure::DelegateDeclarationSyntax& begin, const expression::TypeSyntax& end) {
  decDepth();
  createIndentation();
  ofs << "</DelegateDeclarationSyntax_ReturnType>\n";
}

void VisitorCSHARPML::visitElseClauseSyntax_Statement(const structure::ElseClauseSyntax& begin, const statement::StatementSyntax& end) {
  createIndentation();
  ofs << "<ElseClauseSyntax_Statement>\n";
  incDepth();
}

void VisitorCSHARPML::visitEndElseClauseSyntax_Statement(const structure::ElseClauseSyntax& begin, const statement::StatementSyntax& end) {
  decDepth();
  createIndentation();
  ofs << "</ElseClauseSyntax_Statement>\n";
}

void VisitorCSHARPML::visitEnumDeclarationSyntax_Members(const structure::EnumDeclarationSyntax& begin, const structure::EnumMemberDeclarationSyntax& end) {
  createIndentation();
  ofs << "<EnumDeclarationSyntax_Members>\n";
  incDepth();
}

void VisitorCSHARPML::visitEndEnumDeclarationSyntax_Members(const structure::EnumDeclarationSyntax& begin, const structure::EnumMemberDeclarationSyntax& end) {
  decDepth();
  createIndentation();
  ofs << "</EnumDeclarationSyntax_Members>\n";
}

void VisitorCSHARPML::visitEnumMemberDeclarationSyntax_AttributeLists(const structure::EnumMemberDeclarationSyntax& begin, const structure::AttributeListSyntax& end) {
  createIndentation();
  ofs << "<EnumMemberDeclarationSyntax_AttributeLists>\n";
  incDepth();
}

void VisitorCSHARPML::visitEndEnumMemberDeclarationSyntax_AttributeLists(const structure::EnumMemberDeclarationSyntax& begin, const structure::AttributeListSyntax& end) {
  decDepth();
  createIndentation();
  ofs << "</EnumMemberDeclarationSyntax_AttributeLists>\n";
}

void VisitorCSHARPML::visitEnumMemberDeclarationSyntax_EqualsValue(const structure::EnumMemberDeclarationSyntax& begin, const structure::EqualsValueClauseSyntax& end) {
  createIndentation();
  ofs << "<EnumMemberDeclarationSyntax_EqualsValue>\n";
  incDepth();
}

void VisitorCSHARPML::visitEndEnumMemberDeclarationSyntax_EqualsValue(const structure::EnumMemberDeclarationSyntax& begin, const structure::EqualsValueClauseSyntax& end) {
  decDepth();
  createIndentation();
  ofs << "</EnumMemberDeclarationSyntax_EqualsValue>\n";
}

void VisitorCSHARPML::visitEqualsValueClauseSyntax_Value(const structure::EqualsValueClauseSyntax& begin, const expression::ExpressionSyntax& end) {
  createIndentation();
  ofs << "<EqualsValueClauseSyntax_Value>\n";
  incDepth();
}

void VisitorCSHARPML::visitEndEqualsValueClauseSyntax_Value(const structure::EqualsValueClauseSyntax& begin, const expression::ExpressionSyntax& end) {
  decDepth();
  createIndentation();
  ofs << "</EqualsValueClauseSyntax_Value>\n";
}

void VisitorCSHARPML::visitExplicitInterfaceSpecifierSyntax_Name(const structure::ExplicitInterfaceSpecifierSyntax& begin, const expression::NameSyntax& end) {
  createIndentation();
  ofs << "<ExplicitInterfaceSpecifierSyntax_Name>\n";
  incDepth();
}

void VisitorCSHARPML::visitEndExplicitInterfaceSpecifierSyntax_Name(const structure::ExplicitInterfaceSpecifierSyntax& begin, const expression::NameSyntax& end) {
  decDepth();
  createIndentation();
  ofs << "</ExplicitInterfaceSpecifierSyntax_Name>\n";
}

void VisitorCSHARPML::visitFinallyClauseSyntax_Block(const structure::FinallyClauseSyntax& begin, const statement::BlockSyntax& end) {
  createIndentation();
  ofs << "<FinallyClauseSyntax_Block>\n";
  incDepth();
}

void VisitorCSHARPML::visitEndFinallyClauseSyntax_Block(const structure::FinallyClauseSyntax& begin, const statement::BlockSyntax& end) {
  decDepth();
  createIndentation();
  ofs << "</FinallyClauseSyntax_Block>\n";
}

void VisitorCSHARPML::visitFromClauseSyntax_Expression(const structure::FromClauseSyntax& begin, const expression::ExpressionSyntax& end) {
  createIndentation();
  ofs << "<FromClauseSyntax_Expression>\n";
  incDepth();
}

void VisitorCSHARPML::visitEndFromClauseSyntax_Expression(const structure::FromClauseSyntax& begin, const expression::ExpressionSyntax& end) {
  decDepth();
  createIndentation();
  ofs << "</FromClauseSyntax_Expression>\n";
}

void VisitorCSHARPML::visitFromClauseSyntax_Type(const structure::FromClauseSyntax& begin, const expression::TypeSyntax& end) {
  createIndentation();
  ofs << "<FromClauseSyntax_Type>\n";
  incDepth();
}

void VisitorCSHARPML::visitEndFromClauseSyntax_Type(const structure::FromClauseSyntax& begin, const expression::TypeSyntax& end) {
  decDepth();
  createIndentation();
  ofs << "</FromClauseSyntax_Type>\n";
}

void VisitorCSHARPML::visitGlobalStatementSyntax_Statement(const structure::GlobalStatementSyntax& begin, const statement::StatementSyntax& end) {
  createIndentation();
  ofs << "<GlobalStatementSyntax_Statement>\n";
  incDepth();
}

void VisitorCSHARPML::visitEndGlobalStatementSyntax_Statement(const structure::GlobalStatementSyntax& begin, const statement::StatementSyntax& end) {
  decDepth();
  createIndentation();
  ofs << "</GlobalStatementSyntax_Statement>\n";
}

void VisitorCSHARPML::visitGroupClauseSyntax_ByExpression(const structure::GroupClauseSyntax& begin, const expression::ExpressionSyntax& end) {
  createIndentation();
  ofs << "<GroupClauseSyntax_ByExpression>\n";
  incDepth();
}

void VisitorCSHARPML::visitEndGroupClauseSyntax_ByExpression(const structure::GroupClauseSyntax& begin, const expression::ExpressionSyntax& end) {
  decDepth();
  createIndentation();
  ofs << "</GroupClauseSyntax_ByExpression>\n";
}

void VisitorCSHARPML::visitGroupClauseSyntax_GroupExpression(const structure::GroupClauseSyntax& begin, const expression::ExpressionSyntax& end) {
  createIndentation();
  ofs << "<GroupClauseSyntax_GroupExpression>\n";
  incDepth();
}

void VisitorCSHARPML::visitEndGroupClauseSyntax_GroupExpression(const structure::GroupClauseSyntax& begin, const expression::ExpressionSyntax& end) {
  decDepth();
  createIndentation();
  ofs << "</GroupClauseSyntax_GroupExpression>\n";
}

void VisitorCSHARPML::visitIncompleteMemberSyntax_AttributeLists(const structure::IncompleteMemberSyntax& begin, const structure::AttributeListSyntax& end) {
  createIndentation();
  ofs << "<IncompleteMemberSyntax_AttributeLists>\n";
  incDepth();
}

void VisitorCSHARPML::visitEndIncompleteMemberSyntax_AttributeLists(const structure::IncompleteMemberSyntax& begin, const structure::AttributeListSyntax& end) {
  decDepth();
  createIndentation();
  ofs << "</IncompleteMemberSyntax_AttributeLists>\n";
}

void VisitorCSHARPML::visitIncompleteMemberSyntax_Type(const structure::IncompleteMemberSyntax& begin, const expression::TypeSyntax& end) {
  createIndentation();
  ofs << "<IncompleteMemberSyntax_Type>\n";
  incDepth();
}

void VisitorCSHARPML::visitEndIncompleteMemberSyntax_Type(const structure::IncompleteMemberSyntax& begin, const expression::TypeSyntax& end) {
  decDepth();
  createIndentation();
  ofs << "</IncompleteMemberSyntax_Type>\n";
}

void VisitorCSHARPML::visitIndexerDeclarationSyntax_ExpressionBody(const structure::IndexerDeclarationSyntax& begin, const structure::ArrowExpressionClauseSyntax& end) {
  createIndentation();
  ofs << "<IndexerDeclarationSyntax_ExpressionBody>\n";
  incDepth();
}

void VisitorCSHARPML::visitEndIndexerDeclarationSyntax_ExpressionBody(const structure::IndexerDeclarationSyntax& begin, const structure::ArrowExpressionClauseSyntax& end) {
  decDepth();
  createIndentation();
  ofs << "</IndexerDeclarationSyntax_ExpressionBody>\n";
}

void VisitorCSHARPML::visitIndexerDeclarationSyntax_ParameterList(const structure::IndexerDeclarationSyntax& begin, const structure::BracketedParameterListSyntax& end) {
  createIndentation();
  ofs << "<IndexerDeclarationSyntax_ParameterList>\n";
  incDepth();
}

void VisitorCSHARPML::visitEndIndexerDeclarationSyntax_ParameterList(const structure::IndexerDeclarationSyntax& begin, const structure::BracketedParameterListSyntax& end) {
  decDepth();
  createIndentation();
  ofs << "</IndexerDeclarationSyntax_ParameterList>\n";
}

void VisitorCSHARPML::visitIndexerMemberCrefSyntax_Parameters(const structure::IndexerMemberCrefSyntax& begin, const structure::CrefBracketedParameterListSyntax& end) {
  createIndentation();
  ofs << "<IndexerMemberCrefSyntax_Parameters>\n";
  incDepth();
}

void VisitorCSHARPML::visitEndIndexerMemberCrefSyntax_Parameters(const structure::IndexerMemberCrefSyntax& begin, const structure::CrefBracketedParameterListSyntax& end) {
  decDepth();
  createIndentation();
  ofs << "</IndexerMemberCrefSyntax_Parameters>\n";
}

void VisitorCSHARPML::visitInterpolationAlignmentClauseSyntax_Value(const structure::InterpolationAlignmentClauseSyntax& begin, const expression::ExpressionSyntax& end) {
  createIndentation();
  ofs << "<InterpolationAlignmentClauseSyntax_Value>\n";
  incDepth();
}

void VisitorCSHARPML::visitEndInterpolationAlignmentClauseSyntax_Value(const structure::InterpolationAlignmentClauseSyntax& begin, const expression::ExpressionSyntax& end) {
  decDepth();
  createIndentation();
  ofs << "</InterpolationAlignmentClauseSyntax_Value>\n";
}

void VisitorCSHARPML::visitInterpolationSyntax_AlignmentClause(const structure::InterpolationSyntax& begin, const structure::InterpolationAlignmentClauseSyntax& end) {
  createIndentation();
  ofs << "<InterpolationSyntax_AlignmentClause>\n";
  incDepth();
}

void VisitorCSHARPML::visitEndInterpolationSyntax_AlignmentClause(const structure::InterpolationSyntax& begin, const structure::InterpolationAlignmentClauseSyntax& end) {
  decDepth();
  createIndentation();
  ofs << "</InterpolationSyntax_AlignmentClause>\n";
}

void VisitorCSHARPML::visitInterpolationSyntax_Expression(const structure::InterpolationSyntax& begin, const expression::ExpressionSyntax& end) {
  createIndentation();
  ofs << "<InterpolationSyntax_Expression>\n";
  incDepth();
}

void VisitorCSHARPML::visitEndInterpolationSyntax_Expression(const structure::InterpolationSyntax& begin, const expression::ExpressionSyntax& end) {
  decDepth();
  createIndentation();
  ofs << "</InterpolationSyntax_Expression>\n";
}

void VisitorCSHARPML::visitInterpolationSyntax_FormatClause(const structure::InterpolationSyntax& begin, const structure::InterpolationFormatClauseSyntax& end) {
  createIndentation();
  ofs << "<InterpolationSyntax_FormatClause>\n";
  incDepth();
}

void VisitorCSHARPML::visitEndInterpolationSyntax_FormatClause(const structure::InterpolationSyntax& begin, const structure::InterpolationFormatClauseSyntax& end) {
  decDepth();
  createIndentation();
  ofs << "</InterpolationSyntax_FormatClause>\n";
}

void VisitorCSHARPML::visitJoinClauseSyntax_InExpression(const structure::JoinClauseSyntax& begin, const expression::ExpressionSyntax& end) {
  createIndentation();
  ofs << "<JoinClauseSyntax_InExpression>\n";
  incDepth();
}

void VisitorCSHARPML::visitEndJoinClauseSyntax_InExpression(const structure::JoinClauseSyntax& begin, const expression::ExpressionSyntax& end) {
  decDepth();
  createIndentation();
  ofs << "</JoinClauseSyntax_InExpression>\n";
}

void VisitorCSHARPML::visitJoinClauseSyntax_Into(const structure::JoinClauseSyntax& begin, const structure::JoinIntoClauseSyntax& end) {
  createIndentation();
  ofs << "<JoinClauseSyntax_Into>\n";
  incDepth();
}

void VisitorCSHARPML::visitEndJoinClauseSyntax_Into(const structure::JoinClauseSyntax& begin, const structure::JoinIntoClauseSyntax& end) {
  decDepth();
  createIndentation();
  ofs << "</JoinClauseSyntax_Into>\n";
}

void VisitorCSHARPML::visitJoinClauseSyntax_LeftExpression(const structure::JoinClauseSyntax& begin, const expression::ExpressionSyntax& end) {
  createIndentation();
  ofs << "<JoinClauseSyntax_LeftExpression>\n";
  incDepth();
}

void VisitorCSHARPML::visitEndJoinClauseSyntax_LeftExpression(const structure::JoinClauseSyntax& begin, const expression::ExpressionSyntax& end) {
  decDepth();
  createIndentation();
  ofs << "</JoinClauseSyntax_LeftExpression>\n";
}

void VisitorCSHARPML::visitJoinClauseSyntax_RightExpression(const structure::JoinClauseSyntax& begin, const expression::ExpressionSyntax& end) {
  createIndentation();
  ofs << "<JoinClauseSyntax_RightExpression>\n";
  incDepth();
}

void VisitorCSHARPML::visitEndJoinClauseSyntax_RightExpression(const structure::JoinClauseSyntax& begin, const expression::ExpressionSyntax& end) {
  decDepth();
  createIndentation();
  ofs << "</JoinClauseSyntax_RightExpression>\n";
}

void VisitorCSHARPML::visitJoinClauseSyntax_Type(const structure::JoinClauseSyntax& begin, const expression::TypeSyntax& end) {
  createIndentation();
  ofs << "<JoinClauseSyntax_Type>\n";
  incDepth();
}

void VisitorCSHARPML::visitEndJoinClauseSyntax_Type(const structure::JoinClauseSyntax& begin, const expression::TypeSyntax& end) {
  decDepth();
  createIndentation();
  ofs << "</JoinClauseSyntax_Type>\n";
}

void VisitorCSHARPML::visitLetClauseSyntax_Expression(const structure::LetClauseSyntax& begin, const expression::ExpressionSyntax& end) {
  createIndentation();
  ofs << "<LetClauseSyntax_Expression>\n";
  incDepth();
}

void VisitorCSHARPML::visitEndLetClauseSyntax_Expression(const structure::LetClauseSyntax& begin, const expression::ExpressionSyntax& end) {
  decDepth();
  createIndentation();
  ofs << "</LetClauseSyntax_Expression>\n";
}

void VisitorCSHARPML::visitMethodDeclarationSyntax_ConstraintClauses(const structure::MethodDeclarationSyntax& begin, const structure::TypeParameterConstraintClauseSyntax& end) {
  createIndentation();
  ofs << "<MethodDeclarationSyntax_ConstraintClauses>\n";
  incDepth();
}

void VisitorCSHARPML::visitEndMethodDeclarationSyntax_ConstraintClauses(const structure::MethodDeclarationSyntax& begin, const structure::TypeParameterConstraintClauseSyntax& end) {
  decDepth();
  createIndentation();
  ofs << "</MethodDeclarationSyntax_ConstraintClauses>\n";
}

void VisitorCSHARPML::visitMethodDeclarationSyntax_ExplicitInterfaceSpecifier(const structure::MethodDeclarationSyntax& begin, const structure::ExplicitInterfaceSpecifierSyntax& end) {
  createIndentation();
  ofs << "<MethodDeclarationSyntax_ExplicitInterfaceSpecifier>\n";
  incDepth();
}

void VisitorCSHARPML::visitEndMethodDeclarationSyntax_ExplicitInterfaceSpecifier(const structure::MethodDeclarationSyntax& begin, const structure::ExplicitInterfaceSpecifierSyntax& end) {
  decDepth();
  createIndentation();
  ofs << "</MethodDeclarationSyntax_ExplicitInterfaceSpecifier>\n";
}

void VisitorCSHARPML::visitMethodDeclarationSyntax_ReturnType(const structure::MethodDeclarationSyntax& begin, const expression::TypeSyntax& end) {
  createIndentation();
  ofs << "<MethodDeclarationSyntax_ReturnType>\n";
  incDepth();
}

void VisitorCSHARPML::visitEndMethodDeclarationSyntax_ReturnType(const structure::MethodDeclarationSyntax& begin, const expression::TypeSyntax& end) {
  decDepth();
  createIndentation();
  ofs << "</MethodDeclarationSyntax_ReturnType>\n";
}

void VisitorCSHARPML::visitNameColonSyntax_Name(const structure::NameColonSyntax& begin, const expression::IdentifierNameSyntax& end) {
  createIndentation();
  ofs << "<NameColonSyntax_Name>\n";
  incDepth();
}

void VisitorCSHARPML::visitEndNameColonSyntax_Name(const structure::NameColonSyntax& begin, const expression::IdentifierNameSyntax& end) {
  decDepth();
  createIndentation();
  ofs << "</NameColonSyntax_Name>\n";
}

void VisitorCSHARPML::visitNameEqualsSyntax_Name(const structure::NameEqualsSyntax& begin, const expression::IdentifierNameSyntax& end) {
  createIndentation();
  ofs << "<NameEqualsSyntax_Name>\n";
  incDepth();
}

void VisitorCSHARPML::visitEndNameEqualsSyntax_Name(const structure::NameEqualsSyntax& begin, const expression::IdentifierNameSyntax& end) {
  decDepth();
  createIndentation();
  ofs << "</NameEqualsSyntax_Name>\n";
}

void VisitorCSHARPML::visitNameMemberCrefSyntax_Name(const structure::NameMemberCrefSyntax& begin, const expression::TypeSyntax& end) {
  createIndentation();
  ofs << "<NameMemberCrefSyntax_Name>\n";
  incDepth();
}

void VisitorCSHARPML::visitEndNameMemberCrefSyntax_Name(const structure::NameMemberCrefSyntax& begin, const expression::TypeSyntax& end) {
  decDepth();
  createIndentation();
  ofs << "</NameMemberCrefSyntax_Name>\n";
}

void VisitorCSHARPML::visitNameMemberCrefSyntax_Parameters(const structure::NameMemberCrefSyntax& begin, const structure::CrefParameterListSyntax& end) {
  createIndentation();
  ofs << "<NameMemberCrefSyntax_Parameters>\n";
  incDepth();
}

void VisitorCSHARPML::visitEndNameMemberCrefSyntax_Parameters(const structure::NameMemberCrefSyntax& begin, const structure::CrefParameterListSyntax& end) {
  decDepth();
  createIndentation();
  ofs << "</NameMemberCrefSyntax_Parameters>\n";
}

void VisitorCSHARPML::visitNamespaceDeclarationSyntax_Externs(const structure::NamespaceDeclarationSyntax& begin, const structure::ExternAliasDirectiveSyntax& end) {
  createIndentation();
  ofs << "<NamespaceDeclarationSyntax_Externs>\n";
  incDepth();
}

void VisitorCSHARPML::visitEndNamespaceDeclarationSyntax_Externs(const structure::NamespaceDeclarationSyntax& begin, const structure::ExternAliasDirectiveSyntax& end) {
  decDepth();
  createIndentation();
  ofs << "</NamespaceDeclarationSyntax_Externs>\n";
}

void VisitorCSHARPML::visitNamespaceDeclarationSyntax_Members(const structure::NamespaceDeclarationSyntax& begin, const structure::MemberDeclarationSyntax& end) {
  createIndentation();
  ofs << "<NamespaceDeclarationSyntax_Members>\n";
  incDepth();
}

void VisitorCSHARPML::visitEndNamespaceDeclarationSyntax_Members(const structure::NamespaceDeclarationSyntax& begin, const structure::MemberDeclarationSyntax& end) {
  decDepth();
  createIndentation();
  ofs << "</NamespaceDeclarationSyntax_Members>\n";
}

void VisitorCSHARPML::visitNamespaceDeclarationSyntax_Name(const structure::NamespaceDeclarationSyntax& begin, const expression::NameSyntax& end) {
  createIndentation();
  ofs << "<NamespaceDeclarationSyntax_Name>\n";
  incDepth();
}

void VisitorCSHARPML::visitEndNamespaceDeclarationSyntax_Name(const structure::NamespaceDeclarationSyntax& begin, const expression::NameSyntax& end) {
  decDepth();
  createIndentation();
  ofs << "</NamespaceDeclarationSyntax_Name>\n";
}

void VisitorCSHARPML::visitNamespaceDeclarationSyntax_Usings(const structure::NamespaceDeclarationSyntax& begin, const structure::UsingDirectiveSyntax& end) {
  createIndentation();
  ofs << "<NamespaceDeclarationSyntax_Usings>\n";
  incDepth();
}

void VisitorCSHARPML::visitEndNamespaceDeclarationSyntax_Usings(const structure::NamespaceDeclarationSyntax& begin, const structure::UsingDirectiveSyntax& end) {
  decDepth();
  createIndentation();
  ofs << "</NamespaceDeclarationSyntax_Usings>\n";
}

void VisitorCSHARPML::visitOperatorDeclarationSyntax_ReturnType(const structure::OperatorDeclarationSyntax& begin, const expression::TypeSyntax& end) {
  createIndentation();
  ofs << "<OperatorDeclarationSyntax_ReturnType>\n";
  incDepth();
}

void VisitorCSHARPML::visitEndOperatorDeclarationSyntax_ReturnType(const structure::OperatorDeclarationSyntax& begin, const expression::TypeSyntax& end) {
  decDepth();
  createIndentation();
  ofs << "</OperatorDeclarationSyntax_ReturnType>\n";
}

void VisitorCSHARPML::visitOperatorMemberCrefSyntax_Parameters(const structure::OperatorMemberCrefSyntax& begin, const structure::CrefParameterListSyntax& end) {
  createIndentation();
  ofs << "<OperatorMemberCrefSyntax_Parameters>\n";
  incDepth();
}

void VisitorCSHARPML::visitEndOperatorMemberCrefSyntax_Parameters(const structure::OperatorMemberCrefSyntax& begin, const structure::CrefParameterListSyntax& end) {
  decDepth();
  createIndentation();
  ofs << "</OperatorMemberCrefSyntax_Parameters>\n";
}

void VisitorCSHARPML::visitOrderByClauseSyntax_Orderings(const structure::OrderByClauseSyntax& begin, const structure::OrderingSyntax& end) {
  createIndentation();
  ofs << "<OrderByClauseSyntax_Orderings>\n";
  incDepth();
}

void VisitorCSHARPML::visitEndOrderByClauseSyntax_Orderings(const structure::OrderByClauseSyntax& begin, const structure::OrderingSyntax& end) {
  decDepth();
  createIndentation();
  ofs << "</OrderByClauseSyntax_Orderings>\n";
}

void VisitorCSHARPML::visitOrderingSyntax_Expression(const structure::OrderingSyntax& begin, const expression::ExpressionSyntax& end) {
  createIndentation();
  ofs << "<OrderingSyntax_Expression>\n";
  incDepth();
}

void VisitorCSHARPML::visitEndOrderingSyntax_Expression(const structure::OrderingSyntax& begin, const expression::ExpressionSyntax& end) {
  decDepth();
  createIndentation();
  ofs << "</OrderingSyntax_Expression>\n";
}

void VisitorCSHARPML::visitParameterSyntax_AttributeLists(const structure::ParameterSyntax& begin, const structure::AttributeListSyntax& end) {
  createIndentation();
  ofs << "<ParameterSyntax_AttributeLists>\n";
  incDepth();
}

void VisitorCSHARPML::visitEndParameterSyntax_AttributeLists(const structure::ParameterSyntax& begin, const structure::AttributeListSyntax& end) {
  decDepth();
  createIndentation();
  ofs << "</ParameterSyntax_AttributeLists>\n";
}

void VisitorCSHARPML::visitParameterSyntax_Default(const structure::ParameterSyntax& begin, const structure::EqualsValueClauseSyntax& end) {
  createIndentation();
  ofs << "<ParameterSyntax_Default>\n";
  incDepth();
}

void VisitorCSHARPML::visitEndParameterSyntax_Default(const structure::ParameterSyntax& begin, const structure::EqualsValueClauseSyntax& end) {
  decDepth();
  createIndentation();
  ofs << "</ParameterSyntax_Default>\n";
}

void VisitorCSHARPML::visitParameterSyntax_Type(const structure::ParameterSyntax& begin, const expression::TypeSyntax& end) {
  createIndentation();
  ofs << "<ParameterSyntax_Type>\n";
  incDepth();
}

void VisitorCSHARPML::visitEndParameterSyntax_Type(const structure::ParameterSyntax& begin, const expression::TypeSyntax& end) {
  decDepth();
  createIndentation();
  ofs << "</ParameterSyntax_Type>\n";
}

void VisitorCSHARPML::visitParenthesizedVariableDesignationSyntax_Variables(const structure::ParenthesizedVariableDesignationSyntax& begin, const structure::VariableDesignationSyntax& end) {
  createIndentation();
  ofs << "<ParenthesizedVariableDesignationSyntax_Variables>\n";
  incDepth();
}

void VisitorCSHARPML::visitEndParenthesizedVariableDesignationSyntax_Variables(const structure::ParenthesizedVariableDesignationSyntax& begin, const structure::VariableDesignationSyntax& end) {
  decDepth();
  createIndentation();
  ofs << "</ParenthesizedVariableDesignationSyntax_Variables>\n";
}

void VisitorCSHARPML::visitPositionalPatternClauseSyntax_Subpatterns(const structure::PositionalPatternClauseSyntax& begin, const structure::SubpatternSyntax& end) {
  createIndentation();
  ofs << "<PositionalPatternClauseSyntax_Subpatterns>\n";
  incDepth();
}

void VisitorCSHARPML::visitEndPositionalPatternClauseSyntax_Subpatterns(const structure::PositionalPatternClauseSyntax& begin, const structure::SubpatternSyntax& end) {
  decDepth();
  createIndentation();
  ofs << "</PositionalPatternClauseSyntax_Subpatterns>\n";
}

void VisitorCSHARPML::visitPropertyDeclarationSyntax_ExpressionBody(const structure::PropertyDeclarationSyntax& begin, const structure::ArrowExpressionClauseSyntax& end) {
  createIndentation();
  ofs << "<PropertyDeclarationSyntax_ExpressionBody>\n";
  incDepth();
}

void VisitorCSHARPML::visitEndPropertyDeclarationSyntax_ExpressionBody(const structure::PropertyDeclarationSyntax& begin, const structure::ArrowExpressionClauseSyntax& end) {
  decDepth();
  createIndentation();
  ofs << "</PropertyDeclarationSyntax_ExpressionBody>\n";
}

void VisitorCSHARPML::visitPropertyDeclarationSyntax_Initializer(const structure::PropertyDeclarationSyntax& begin, const structure::EqualsValueClauseSyntax& end) {
  createIndentation();
  ofs << "<PropertyDeclarationSyntax_Initializer>\n";
  incDepth();
}

void VisitorCSHARPML::visitEndPropertyDeclarationSyntax_Initializer(const structure::PropertyDeclarationSyntax& begin, const structure::EqualsValueClauseSyntax& end) {
  decDepth();
  createIndentation();
  ofs << "</PropertyDeclarationSyntax_Initializer>\n";
}

void VisitorCSHARPML::visitPropertyPatternClauseSyntax_Subpatterns(const structure::PropertyPatternClauseSyntax& begin, const structure::SubpatternSyntax& end) {
  createIndentation();
  ofs << "<PropertyPatternClauseSyntax_Subpatterns>\n";
  incDepth();
}

void VisitorCSHARPML::visitEndPropertyPatternClauseSyntax_Subpatterns(const structure::PropertyPatternClauseSyntax& begin, const structure::SubpatternSyntax& end) {
  decDepth();
  createIndentation();
  ofs << "</PropertyPatternClauseSyntax_Subpatterns>\n";
}

void VisitorCSHARPML::visitQualifiedCrefSyntax_Container(const structure::QualifiedCrefSyntax& begin, const expression::TypeSyntax& end) {
  createIndentation();
  ofs << "<QualifiedCrefSyntax_Container>\n";
  incDepth();
}

void VisitorCSHARPML::visitEndQualifiedCrefSyntax_Container(const structure::QualifiedCrefSyntax& begin, const expression::TypeSyntax& end) {
  decDepth();
  createIndentation();
  ofs << "</QualifiedCrefSyntax_Container>\n";
}

void VisitorCSHARPML::visitQualifiedCrefSyntax_Member(const structure::QualifiedCrefSyntax& begin, const structure::MemberCrefSyntax& end) {
  createIndentation();
  ofs << "<QualifiedCrefSyntax_Member>\n";
  incDepth();
}

void VisitorCSHARPML::visitEndQualifiedCrefSyntax_Member(const structure::QualifiedCrefSyntax& begin, const structure::MemberCrefSyntax& end) {
  decDepth();
  createIndentation();
  ofs << "</QualifiedCrefSyntax_Member>\n";
}

void VisitorCSHARPML::visitQueryBodySyntax_Clauses(const structure::QueryBodySyntax& begin, const structure::QueryClauseSyntax& end) {
  createIndentation();
  ofs << "<QueryBodySyntax_Clauses>\n";
  incDepth();
}

void VisitorCSHARPML::visitEndQueryBodySyntax_Clauses(const structure::QueryBodySyntax& begin, const structure::QueryClauseSyntax& end) {
  decDepth();
  createIndentation();
  ofs << "</QueryBodySyntax_Clauses>\n";
}

void VisitorCSHARPML::visitQueryBodySyntax_Continuation(const structure::QueryBodySyntax& begin, const structure::QueryContinuationSyntax& end) {
  createIndentation();
  ofs << "<QueryBodySyntax_Continuation>\n";
  incDepth();
}

void VisitorCSHARPML::visitEndQueryBodySyntax_Continuation(const structure::QueryBodySyntax& begin, const structure::QueryContinuationSyntax& end) {
  decDepth();
  createIndentation();
  ofs << "</QueryBodySyntax_Continuation>\n";
}

void VisitorCSHARPML::visitQueryBodySyntax_SelectOrGroup(const structure::QueryBodySyntax& begin, const structure::SelectOrGroupClauseSyntax& end) {
  createIndentation();
  ofs << "<QueryBodySyntax_SelectOrGroup>\n";
  incDepth();
}

void VisitorCSHARPML::visitEndQueryBodySyntax_SelectOrGroup(const structure::QueryBodySyntax& begin, const structure::SelectOrGroupClauseSyntax& end) {
  decDepth();
  createIndentation();
  ofs << "</QueryBodySyntax_SelectOrGroup>\n";
}

void VisitorCSHARPML::visitQueryContinuationSyntax_Body(const structure::QueryContinuationSyntax& begin, const structure::QueryBodySyntax& end) {
  createIndentation();
  ofs << "<QueryContinuationSyntax_Body>\n";
  incDepth();
}

void VisitorCSHARPML::visitEndQueryContinuationSyntax_Body(const structure::QueryContinuationSyntax& begin, const structure::QueryBodySyntax& end) {
  decDepth();
  createIndentation();
  ofs << "</QueryContinuationSyntax_Body>\n";
}

void VisitorCSHARPML::visitRecursivePatternSyntax_Designation(const structure::RecursivePatternSyntax& begin, const structure::VariableDesignationSyntax& end) {
  createIndentation();
  ofs << "<RecursivePatternSyntax_Designation>\n";
  incDepth();
}

void VisitorCSHARPML::visitEndRecursivePatternSyntax_Designation(const structure::RecursivePatternSyntax& begin, const structure::VariableDesignationSyntax& end) {
  decDepth();
  createIndentation();
  ofs << "</RecursivePatternSyntax_Designation>\n";
}

void VisitorCSHARPML::visitRecursivePatternSyntax_PositionalPatternClause(const structure::RecursivePatternSyntax& begin, const structure::PositionalPatternClauseSyntax& end) {
  createIndentation();
  ofs << "<RecursivePatternSyntax_PositionalPatternClause>\n";
  incDepth();
}

void VisitorCSHARPML::visitEndRecursivePatternSyntax_PositionalPatternClause(const structure::RecursivePatternSyntax& begin, const structure::PositionalPatternClauseSyntax& end) {
  decDepth();
  createIndentation();
  ofs << "</RecursivePatternSyntax_PositionalPatternClause>\n";
}

void VisitorCSHARPML::visitRecursivePatternSyntax_PropertyPatternClause(const structure::RecursivePatternSyntax& begin, const structure::PropertyPatternClauseSyntax& end) {
  createIndentation();
  ofs << "<RecursivePatternSyntax_PropertyPatternClause>\n";
  incDepth();
}

void VisitorCSHARPML::visitEndRecursivePatternSyntax_PropertyPatternClause(const structure::RecursivePatternSyntax& begin, const structure::PropertyPatternClauseSyntax& end) {
  decDepth();
  createIndentation();
  ofs << "</RecursivePatternSyntax_PropertyPatternClause>\n";
}

void VisitorCSHARPML::visitRecursivePatternSyntax_Type(const structure::RecursivePatternSyntax& begin, const expression::TypeSyntax& end) {
  createIndentation();
  ofs << "<RecursivePatternSyntax_Type>\n";
  incDepth();
}

void VisitorCSHARPML::visitEndRecursivePatternSyntax_Type(const structure::RecursivePatternSyntax& begin, const expression::TypeSyntax& end) {
  decDepth();
  createIndentation();
  ofs << "</RecursivePatternSyntax_Type>\n";
}

void VisitorCSHARPML::visitSelectClauseSyntax_Expression(const structure::SelectClauseSyntax& begin, const expression::ExpressionSyntax& end) {
  createIndentation();
  ofs << "<SelectClauseSyntax_Expression>\n";
  incDepth();
}

void VisitorCSHARPML::visitEndSelectClauseSyntax_Expression(const structure::SelectClauseSyntax& begin, const expression::ExpressionSyntax& end) {
  decDepth();
  createIndentation();
  ofs << "</SelectClauseSyntax_Expression>\n";
}

void VisitorCSHARPML::visitSubpatternSyntax_Pattern(const structure::SubpatternSyntax& begin, const structure::PatternSyntax& end) {
  createIndentation();
  ofs << "<SubpatternSyntax_Pattern>\n";
  incDepth();
}

void VisitorCSHARPML::visitEndSubpatternSyntax_Pattern(const structure::SubpatternSyntax& begin, const structure::PatternSyntax& end) {
  decDepth();
  createIndentation();
  ofs << "</SubpatternSyntax_Pattern>\n";
}

void VisitorCSHARPML::visitSwitchExpressionArmSyntax_Expression(const structure::SwitchExpressionArmSyntax& begin, const expression::ExpressionSyntax& end) {
  createIndentation();
  ofs << "<SwitchExpressionArmSyntax_Expression>\n";
  incDepth();
}

void VisitorCSHARPML::visitEndSwitchExpressionArmSyntax_Expression(const structure::SwitchExpressionArmSyntax& begin, const expression::ExpressionSyntax& end) {
  decDepth();
  createIndentation();
  ofs << "</SwitchExpressionArmSyntax_Expression>\n";
}

void VisitorCSHARPML::visitSwitchExpressionArmSyntax_Pattern(const structure::SwitchExpressionArmSyntax& begin, const structure::PatternSyntax& end) {
  createIndentation();
  ofs << "<SwitchExpressionArmSyntax_Pattern>\n";
  incDepth();
}

void VisitorCSHARPML::visitEndSwitchExpressionArmSyntax_Pattern(const structure::SwitchExpressionArmSyntax& begin, const structure::PatternSyntax& end) {
  decDepth();
  createIndentation();
  ofs << "</SwitchExpressionArmSyntax_Pattern>\n";
}

void VisitorCSHARPML::visitSwitchExpressionArmSyntax_WhenClause(const structure::SwitchExpressionArmSyntax& begin, const structure::WhenClauseSyntax& end) {
  createIndentation();
  ofs << "<SwitchExpressionArmSyntax_WhenClause>\n";
  incDepth();
}

void VisitorCSHARPML::visitEndSwitchExpressionArmSyntax_WhenClause(const structure::SwitchExpressionArmSyntax& begin, const structure::WhenClauseSyntax& end) {
  decDepth();
  createIndentation();
  ofs << "</SwitchExpressionArmSyntax_WhenClause>\n";
}

void VisitorCSHARPML::visitSwitchSectionSyntax_Labels(const structure::SwitchSectionSyntax& begin, const structure::SwitchLabelSyntax& end) {
  createIndentation();
  ofs << "<SwitchSectionSyntax_Labels>\n";
  incDepth();
}

void VisitorCSHARPML::visitEndSwitchSectionSyntax_Labels(const structure::SwitchSectionSyntax& begin, const structure::SwitchLabelSyntax& end) {
  decDepth();
  createIndentation();
  ofs << "</SwitchSectionSyntax_Labels>\n";
}

void VisitorCSHARPML::visitSwitchSectionSyntax_Statements(const structure::SwitchSectionSyntax& begin, const statement::StatementSyntax& end) {
  createIndentation();
  ofs << "<SwitchSectionSyntax_Statements>\n";
  incDepth();
}

void VisitorCSHARPML::visitEndSwitchSectionSyntax_Statements(const structure::SwitchSectionSyntax& begin, const statement::StatementSyntax& end) {
  decDepth();
  createIndentation();
  ofs << "</SwitchSectionSyntax_Statements>\n";
}

void VisitorCSHARPML::visitTupleElementSyntax_Type(const structure::TupleElementSyntax& begin, const expression::TypeSyntax& end) {
  createIndentation();
  ofs << "<TupleElementSyntax_Type>\n";
  incDepth();
}

void VisitorCSHARPML::visitEndTupleElementSyntax_Type(const structure::TupleElementSyntax& begin, const expression::TypeSyntax& end) {
  decDepth();
  createIndentation();
  ofs << "</TupleElementSyntax_Type>\n";
}

void VisitorCSHARPML::visitTypeArgumentListSyntax_Arguments(const structure::TypeArgumentListSyntax& begin, const expression::TypeSyntax& end) {
  createIndentation();
  ofs << "<TypeArgumentListSyntax_Arguments>\n";
  incDepth();
}

void VisitorCSHARPML::visitEndTypeArgumentListSyntax_Arguments(const structure::TypeArgumentListSyntax& begin, const expression::TypeSyntax& end) {
  decDepth();
  createIndentation();
  ofs << "</TypeArgumentListSyntax_Arguments>\n";
}

void VisitorCSHARPML::visitTypeConstraintSyntax_Type(const structure::TypeConstraintSyntax& begin, const expression::TypeSyntax& end) {
  createIndentation();
  ofs << "<TypeConstraintSyntax_Type>\n";
  incDepth();
}

void VisitorCSHARPML::visitEndTypeConstraintSyntax_Type(const structure::TypeConstraintSyntax& begin, const expression::TypeSyntax& end) {
  decDepth();
  createIndentation();
  ofs << "</TypeConstraintSyntax_Type>\n";
}

void VisitorCSHARPML::visitTypeCrefSyntax_Type(const structure::TypeCrefSyntax& begin, const expression::TypeSyntax& end) {
  createIndentation();
  ofs << "<TypeCrefSyntax_Type>\n";
  incDepth();
}

void VisitorCSHARPML::visitEndTypeCrefSyntax_Type(const structure::TypeCrefSyntax& begin, const expression::TypeSyntax& end) {
  decDepth();
  createIndentation();
  ofs << "</TypeCrefSyntax_Type>\n";
}

void VisitorCSHARPML::visitTypeDeclarationSyntax_ConstraintClauses(const structure::TypeDeclarationSyntax& begin, const structure::TypeParameterConstraintClauseSyntax& end) {
  createIndentation();
  ofs << "<TypeDeclarationSyntax_ConstraintClauses>\n";
  incDepth();
}

void VisitorCSHARPML::visitEndTypeDeclarationSyntax_ConstraintClauses(const structure::TypeDeclarationSyntax& begin, const structure::TypeParameterConstraintClauseSyntax& end) {
  decDepth();
  createIndentation();
  ofs << "</TypeDeclarationSyntax_ConstraintClauses>\n";
}

void VisitorCSHARPML::visitTypeDeclarationSyntax_Members(const structure::TypeDeclarationSyntax& begin, const structure::MemberDeclarationSyntax& end) {
  createIndentation();
  ofs << "<TypeDeclarationSyntax_Members>\n";
  incDepth();
}

void VisitorCSHARPML::visitEndTypeDeclarationSyntax_Members(const structure::TypeDeclarationSyntax& begin, const structure::MemberDeclarationSyntax& end) {
  decDepth();
  createIndentation();
  ofs << "</TypeDeclarationSyntax_Members>\n";
}

void VisitorCSHARPML::visitTypeDeclarationSyntax_TypeParameterList(const structure::TypeDeclarationSyntax& begin, const structure::TypeParameterListSyntax& end) {
  createIndentation();
  ofs << "<TypeDeclarationSyntax_TypeParameterList>\n";
  incDepth();
}

void VisitorCSHARPML::visitEndTypeDeclarationSyntax_TypeParameterList(const structure::TypeDeclarationSyntax& begin, const structure::TypeParameterListSyntax& end) {
  decDepth();
  createIndentation();
  ofs << "</TypeDeclarationSyntax_TypeParameterList>\n";
}

void VisitorCSHARPML::visitTypeParameterConstraintClauseSyntax_Constraints(const structure::TypeParameterConstraintClauseSyntax& begin, const structure::TypeParameterConstraintSyntax& end) {
  createIndentation();
  ofs << "<TypeParameterConstraintClauseSyntax_Constraints>\n";
  incDepth();
}

void VisitorCSHARPML::visitEndTypeParameterConstraintClauseSyntax_Constraints(const structure::TypeParameterConstraintClauseSyntax& begin, const structure::TypeParameterConstraintSyntax& end) {
  decDepth();
  createIndentation();
  ofs << "</TypeParameterConstraintClauseSyntax_Constraints>\n";
}

void VisitorCSHARPML::visitTypeParameterConstraintClauseSyntax_Name(const structure::TypeParameterConstraintClauseSyntax& begin, const expression::IdentifierNameSyntax& end) {
  createIndentation();
  ofs << "<TypeParameterConstraintClauseSyntax_Name>\n";
  incDepth();
}

void VisitorCSHARPML::visitEndTypeParameterConstraintClauseSyntax_Name(const structure::TypeParameterConstraintClauseSyntax& begin, const expression::IdentifierNameSyntax& end) {
  decDepth();
  createIndentation();
  ofs << "</TypeParameterConstraintClauseSyntax_Name>\n";
}

void VisitorCSHARPML::visitTypeParameterListSyntax_Parameters(const structure::TypeParameterListSyntax& begin, const structure::TypeParameterSyntax& end) {
  createIndentation();
  ofs << "<TypeParameterListSyntax_Parameters>\n";
  incDepth();
}

void VisitorCSHARPML::visitEndTypeParameterListSyntax_Parameters(const structure::TypeParameterListSyntax& begin, const structure::TypeParameterSyntax& end) {
  decDepth();
  createIndentation();
  ofs << "</TypeParameterListSyntax_Parameters>\n";
}

void VisitorCSHARPML::visitTypeParameterSyntax_AttributeLists(const structure::TypeParameterSyntax& begin, const structure::AttributeListSyntax& end) {
  createIndentation();
  ofs << "<TypeParameterSyntax_AttributeLists>\n";
  incDepth();
}

void VisitorCSHARPML::visitEndTypeParameterSyntax_AttributeLists(const structure::TypeParameterSyntax& begin, const structure::AttributeListSyntax& end) {
  decDepth();
  createIndentation();
  ofs << "</TypeParameterSyntax_AttributeLists>\n";
}

void VisitorCSHARPML::visitUsingDirectiveSyntax_Alias(const structure::UsingDirectiveSyntax& begin, const structure::NameEqualsSyntax& end) {
  createIndentation();
  ofs << "<UsingDirectiveSyntax_Alias>\n";
  incDepth();
}

void VisitorCSHARPML::visitEndUsingDirectiveSyntax_Alias(const structure::UsingDirectiveSyntax& begin, const structure::NameEqualsSyntax& end) {
  decDepth();
  createIndentation();
  ofs << "</UsingDirectiveSyntax_Alias>\n";
}

void VisitorCSHARPML::visitUsingDirectiveSyntax_Name(const structure::UsingDirectiveSyntax& begin, const expression::NameSyntax& end) {
  createIndentation();
  ofs << "<UsingDirectiveSyntax_Name>\n";
  incDepth();
}

void VisitorCSHARPML::visitEndUsingDirectiveSyntax_Name(const structure::UsingDirectiveSyntax& begin, const expression::NameSyntax& end) {
  decDepth();
  createIndentation();
  ofs << "</UsingDirectiveSyntax_Name>\n";
}

void VisitorCSHARPML::visitVarPatternSyntax_Designation(const structure::VarPatternSyntax& begin, const structure::VariableDesignationSyntax& end) {
  createIndentation();
  ofs << "<VarPatternSyntax_Designation>\n";
  incDepth();
}

void VisitorCSHARPML::visitEndVarPatternSyntax_Designation(const structure::VarPatternSyntax& begin, const structure::VariableDesignationSyntax& end) {
  decDepth();
  createIndentation();
  ofs << "</VarPatternSyntax_Designation>\n";
}

void VisitorCSHARPML::visitVariableDeclarationSyntax_Type(const structure::VariableDeclarationSyntax& begin, const expression::TypeSyntax& end) {
  createIndentation();
  ofs << "<VariableDeclarationSyntax_Type>\n";
  incDepth();
}

void VisitorCSHARPML::visitEndVariableDeclarationSyntax_Type(const structure::VariableDeclarationSyntax& begin, const expression::TypeSyntax& end) {
  decDepth();
  createIndentation();
  ofs << "</VariableDeclarationSyntax_Type>\n";
}

void VisitorCSHARPML::visitVariableDeclarationSyntax_Variables(const structure::VariableDeclarationSyntax& begin, const structure::VariableDeclaratorSyntax& end) {
  createIndentation();
  ofs << "<VariableDeclarationSyntax_Variables>\n";
  incDepth();
}

void VisitorCSHARPML::visitEndVariableDeclarationSyntax_Variables(const structure::VariableDeclarationSyntax& begin, const structure::VariableDeclaratorSyntax& end) {
  decDepth();
  createIndentation();
  ofs << "</VariableDeclarationSyntax_Variables>\n";
}

void VisitorCSHARPML::visitVariableDeclaratorSyntax_ArgumentList(const structure::VariableDeclaratorSyntax& begin, const structure::BracketedArgumentListSyntax& end) {
  createIndentation();
  ofs << "<VariableDeclaratorSyntax_ArgumentList>\n";
  incDepth();
}

void VisitorCSHARPML::visitEndVariableDeclaratorSyntax_ArgumentList(const structure::VariableDeclaratorSyntax& begin, const structure::BracketedArgumentListSyntax& end) {
  decDepth();
  createIndentation();
  ofs << "</VariableDeclaratorSyntax_ArgumentList>\n";
}

void VisitorCSHARPML::visitVariableDeclaratorSyntax_Initializer(const structure::VariableDeclaratorSyntax& begin, const structure::EqualsValueClauseSyntax& end) {
  createIndentation();
  ofs << "<VariableDeclaratorSyntax_Initializer>\n";
  incDepth();
}

void VisitorCSHARPML::visitEndVariableDeclaratorSyntax_Initializer(const structure::VariableDeclaratorSyntax& begin, const structure::EqualsValueClauseSyntax& end) {
  decDepth();
  createIndentation();
  ofs << "</VariableDeclaratorSyntax_Initializer>\n";
}

void VisitorCSHARPML::visitWhenClauseSyntax_Condition(const structure::WhenClauseSyntax& begin, const expression::ExpressionSyntax& end) {
  createIndentation();
  ofs << "<WhenClauseSyntax_Condition>\n";
  incDepth();
}

void VisitorCSHARPML::visitEndWhenClauseSyntax_Condition(const structure::WhenClauseSyntax& begin, const expression::ExpressionSyntax& end) {
  decDepth();
  createIndentation();
  ofs << "</WhenClauseSyntax_Condition>\n";
}

void VisitorCSHARPML::visitWhereClauseSyntax_Condition(const structure::WhereClauseSyntax& begin, const expression::ExpressionSyntax& end) {
  createIndentation();
  ofs << "<WhereClauseSyntax_Condition>\n";
  incDepth();
}

void VisitorCSHARPML::visitEndWhereClauseSyntax_Condition(const structure::WhereClauseSyntax& begin, const expression::ExpressionSyntax& end) {
  decDepth();
  createIndentation();
  ofs << "</WhereClauseSyntax_Condition>\n";
}

void VisitorCSHARPML::visitXmlAttributeSyntax_Name(const structure::XmlAttributeSyntax& begin, const structure::XmlNameSyntax& end) {
  createIndentation();
  ofs << "<XmlAttributeSyntax_Name>\n";
  incDepth();
}

void VisitorCSHARPML::visitEndXmlAttributeSyntax_Name(const structure::XmlAttributeSyntax& begin, const structure::XmlNameSyntax& end) {
  decDepth();
  createIndentation();
  ofs << "</XmlAttributeSyntax_Name>\n";
}

void VisitorCSHARPML::visitXmlCrefAttributeSyntax_Cref(const structure::XmlCrefAttributeSyntax& begin, const structure::CrefSyntax& end) {
  createIndentation();
  ofs << "<XmlCrefAttributeSyntax_Cref>\n";
  incDepth();
}

void VisitorCSHARPML::visitEndXmlCrefAttributeSyntax_Cref(const structure::XmlCrefAttributeSyntax& begin, const structure::CrefSyntax& end) {
  decDepth();
  createIndentation();
  ofs << "</XmlCrefAttributeSyntax_Cref>\n";
}

void VisitorCSHARPML::visitXmlElementEndTagSyntax_Name(const structure::XmlElementEndTagSyntax& begin, const structure::XmlNameSyntax& end) {
  createIndentation();
  ofs << "<XmlElementEndTagSyntax_Name>\n";
  incDepth();
}

void VisitorCSHARPML::visitEndXmlElementEndTagSyntax_Name(const structure::XmlElementEndTagSyntax& begin, const structure::XmlNameSyntax& end) {
  decDepth();
  createIndentation();
  ofs << "</XmlElementEndTagSyntax_Name>\n";
}

void VisitorCSHARPML::visitXmlElementStartTagSyntax_Attributes(const structure::XmlElementStartTagSyntax& begin, const structure::XmlAttributeSyntax& end) {
  createIndentation();
  ofs << "<XmlElementStartTagSyntax_Attributes>\n";
  incDepth();
}

void VisitorCSHARPML::visitEndXmlElementStartTagSyntax_Attributes(const structure::XmlElementStartTagSyntax& begin, const structure::XmlAttributeSyntax& end) {
  decDepth();
  createIndentation();
  ofs << "</XmlElementStartTagSyntax_Attributes>\n";
}

void VisitorCSHARPML::visitXmlElementStartTagSyntax_Name(const structure::XmlElementStartTagSyntax& begin, const structure::XmlNameSyntax& end) {
  createIndentation();
  ofs << "<XmlElementStartTagSyntax_Name>\n";
  incDepth();
}

void VisitorCSHARPML::visitEndXmlElementStartTagSyntax_Name(const structure::XmlElementStartTagSyntax& begin, const structure::XmlNameSyntax& end) {
  decDepth();
  createIndentation();
  ofs << "</XmlElementStartTagSyntax_Name>\n";
}

void VisitorCSHARPML::visitXmlElementSyntax_Content(const structure::XmlElementSyntax& begin, const structure::XmlNodeSyntax& end) {
  createIndentation();
  ofs << "<XmlElementSyntax_Content>\n";
  incDepth();
}

void VisitorCSHARPML::visitEndXmlElementSyntax_Content(const structure::XmlElementSyntax& begin, const structure::XmlNodeSyntax& end) {
  decDepth();
  createIndentation();
  ofs << "</XmlElementSyntax_Content>\n";
}

void VisitorCSHARPML::visitXmlElementSyntax_EndTag(const structure::XmlElementSyntax& begin, const structure::XmlElementEndTagSyntax& end) {
  createIndentation();
  ofs << "<XmlElementSyntax_EndTag>\n";
  incDepth();
}

void VisitorCSHARPML::visitEndXmlElementSyntax_EndTag(const structure::XmlElementSyntax& begin, const structure::XmlElementEndTagSyntax& end) {
  decDepth();
  createIndentation();
  ofs << "</XmlElementSyntax_EndTag>\n";
}

void VisitorCSHARPML::visitXmlElementSyntax_StartTag(const structure::XmlElementSyntax& begin, const structure::XmlElementStartTagSyntax& end) {
  createIndentation();
  ofs << "<XmlElementSyntax_StartTag>\n";
  incDepth();
}

void VisitorCSHARPML::visitEndXmlElementSyntax_StartTag(const structure::XmlElementSyntax& begin, const structure::XmlElementStartTagSyntax& end) {
  decDepth();
  createIndentation();
  ofs << "</XmlElementSyntax_StartTag>\n";
}

void VisitorCSHARPML::visitXmlEmptyElementSyntax_Attributes(const structure::XmlEmptyElementSyntax& begin, const structure::XmlAttributeSyntax& end) {
  createIndentation();
  ofs << "<XmlEmptyElementSyntax_Attributes>\n";
  incDepth();
}

void VisitorCSHARPML::visitEndXmlEmptyElementSyntax_Attributes(const structure::XmlEmptyElementSyntax& begin, const structure::XmlAttributeSyntax& end) {
  decDepth();
  createIndentation();
  ofs << "</XmlEmptyElementSyntax_Attributes>\n";
}

void VisitorCSHARPML::visitXmlEmptyElementSyntax_Name(const structure::XmlEmptyElementSyntax& begin, const structure::XmlNameSyntax& end) {
  createIndentation();
  ofs << "<XmlEmptyElementSyntax_Name>\n";
  incDepth();
}

void VisitorCSHARPML::visitEndXmlEmptyElementSyntax_Name(const structure::XmlEmptyElementSyntax& begin, const structure::XmlNameSyntax& end) {
  decDepth();
  createIndentation();
  ofs << "</XmlEmptyElementSyntax_Name>\n";
}

void VisitorCSHARPML::visitXmlNameAttributeSyntax_Identifier(const structure::XmlNameAttributeSyntax& begin, const expression::IdentifierNameSyntax& end) {
  createIndentation();
  ofs << "<XmlNameAttributeSyntax_Identifier>\n";
  incDepth();
}

void VisitorCSHARPML::visitEndXmlNameAttributeSyntax_Identifier(const structure::XmlNameAttributeSyntax& begin, const expression::IdentifierNameSyntax& end) {
  decDepth();
  createIndentation();
  ofs << "</XmlNameAttributeSyntax_Identifier>\n";
}

void VisitorCSHARPML::visitXmlNameSyntax_Prefix(const structure::XmlNameSyntax& begin, const structure::XmlPrefixSyntax& end) {
  createIndentation();
  ofs << "<XmlNameSyntax_Prefix>\n";
  incDepth();
}

void VisitorCSHARPML::visitEndXmlNameSyntax_Prefix(const structure::XmlNameSyntax& begin, const structure::XmlPrefixSyntax& end) {
  decDepth();
  createIndentation();
  ofs << "</XmlNameSyntax_Prefix>\n";
}

void VisitorCSHARPML::visitXmlProcessingInstructionSyntax_Name(const structure::XmlProcessingInstructionSyntax& begin, const structure::XmlNameSyntax& end) {
  createIndentation();
  ofs << "<XmlProcessingInstructionSyntax_Name>\n";
  incDepth();
}

void VisitorCSHARPML::visitEndXmlProcessingInstructionSyntax_Name(const structure::XmlProcessingInstructionSyntax& begin, const structure::XmlNameSyntax& end) {
  decDepth();
  createIndentation();
  ofs << "</XmlProcessingInstructionSyntax_Name>\n";
}

void VisitorCSHARPML::createIndentation() {
  if (depth)
    ofs << std::string(depth, '\t');
}

string VisitorCSHARPML::chk(string s) {
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

void VisitorCSHARPML::writeAttributes(const base::Base& node,bool composite, bool bWithParent /*= true*/ ) {
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

void VisitorCSHARPML::writeAttributes(const base::Positioned& node,bool composite, bool bWithParent /*= true*/ ) {
  writeAttributes((base::Base&)node,composite,false);

  if (composite) {
    incDepth();
    createIndentation();
    ofs << "<SourcePosition name='position'";
    writeAttributes(node.getPosition(),false);
    ofs << "/>\n";
    decDepth();
  }
}

void VisitorCSHARPML::writeAttributes(const expression::AliasQualifiedNameSyntax& node,bool composite, bool bWithParent /*= true*/ ) {
  writeAttributes((expression::NameSyntax&)node,composite,false);

}

void VisitorCSHARPML::writeAttributes(const expression::AnonymousFunctionExpressionSyntax& node,bool composite, bool bWithParent /*= true*/ ) {
  writeAttributes((expression::ExpressionSyntax&)node,composite,false);

  if (!composite) {
    ofs << " identifier='" << chk(node.getIdentifier()) << "'";
  }
}

void VisitorCSHARPML::writeAttributes(const expression::AnonymousMethodExpressionSyntax& node,bool composite, bool bWithParent /*= true*/ ) {
  writeAttributes((expression::AnonymousFunctionExpressionSyntax&)node,composite,false);

}

void VisitorCSHARPML::writeAttributes(const expression::AnonymousObjectCreationExpressionSyntax& node,bool composite, bool bWithParent /*= true*/ ) {
  writeAttributes((expression::ExpressionSyntax&)node,composite,false);

  if (!composite) {
    ofs << " identifier='" << chk(node.getIdentifier()) << "'";
  }
}

void VisitorCSHARPML::writeAttributes(const expression::ArrayCreationExpressionSyntax& node,bool composite, bool bWithParent /*= true*/ ) {
  writeAttributes((expression::ExpressionSyntax&)node,composite,false);

}

void VisitorCSHARPML::writeAttributes(const expression::ArrayTypeSyntax& node,bool composite, bool bWithParent /*= true*/ ) {
  writeAttributes((expression::TypeSyntax&)node,composite,false);

}

void VisitorCSHARPML::writeAttributes(const expression::AssignmentExpressionSyntax& node,bool composite, bool bWithParent /*= true*/ ) {
  writeAttributes((expression::ExpressionSyntax&)node,composite,false);

}

void VisitorCSHARPML::writeAttributes(const expression::AwaitExpressionSyntax& node,bool composite, bool bWithParent /*= true*/ ) {
  writeAttributes((expression::ExpressionSyntax&)node,composite,false);

}

void VisitorCSHARPML::writeAttributes(const expression::BaseExpressionSyntax& node,bool composite, bool bWithParent /*= true*/ ) {
  writeAttributes((expression::InstanceExpressionSyntax&)node,composite,false);

}

void VisitorCSHARPML::writeAttributes(const expression::BinaryExpressionSyntax& node,bool composite, bool bWithParent /*= true*/ ) {
  writeAttributes((expression::ExpressionSyntax&)node,composite,false);

}

void VisitorCSHARPML::writeAttributes(const expression::CastExpressionSyntax& node,bool composite, bool bWithParent /*= true*/ ) {
  writeAttributes((expression::ExpressionSyntax&)node,composite,false);

}

void VisitorCSHARPML::writeAttributes(const expression::CheckedExpressionSyntax& node,bool composite, bool bWithParent /*= true*/ ) {
  writeAttributes((expression::ExpressionSyntax&)node,composite,false);

}

void VisitorCSHARPML::writeAttributes(const expression::ConditionalAccessExpressionSyntax& node,bool composite, bool bWithParent /*= true*/ ) {
  writeAttributes((expression::ExpressionSyntax&)node,composite,false);

}

void VisitorCSHARPML::writeAttributes(const expression::ConditionalExpressionSyntax& node,bool composite, bool bWithParent /*= true*/ ) {
  writeAttributes((expression::ExpressionSyntax&)node,composite,false);

}

void VisitorCSHARPML::writeAttributes(const expression::DeclarationExpressionSyntax& node,bool composite, bool bWithParent /*= true*/ ) {
  writeAttributes((expression::ExpressionSyntax&)node,composite,false);

}

void VisitorCSHARPML::writeAttributes(const expression::DefaultExpressionSyntax& node,bool composite, bool bWithParent /*= true*/ ) {
  writeAttributes((expression::ExpressionSyntax&)node,composite,false);

}

void VisitorCSHARPML::writeAttributes(const expression::ElementAccessExpressionSyntax& node,bool composite, bool bWithParent /*= true*/ ) {
  writeAttributes((expression::ExpressionSyntax&)node,composite,false);

}

void VisitorCSHARPML::writeAttributes(const expression::ElementBindingExpressionSyntax& node,bool composite, bool bWithParent /*= true*/ ) {
  writeAttributes((expression::ExpressionSyntax&)node,composite,false);

}

void VisitorCSHARPML::writeAttributes(const expression::ExpressionSyntax& node,bool composite, bool bWithParent /*= true*/ ) {
  writeAttributes((base::Positioned&)node,composite,false);

}

void VisitorCSHARPML::writeAttributes(const expression::GenericNameSyntax& node,bool composite, bool bWithParent /*= true*/ ) {
  writeAttributes((expression::SimpleNameSyntax&)node,composite,false);

}

void VisitorCSHARPML::writeAttributes(const expression::IdentifierNameSyntax& node,bool composite, bool bWithParent /*= true*/ ) {
  writeAttributes((expression::SimpleNameSyntax&)node,composite,false);

}

void VisitorCSHARPML::writeAttributes(const expression::ImplicitArrayCreationExpressionSyntax& node,bool composite, bool bWithParent /*= true*/ ) {
  writeAttributes((expression::ExpressionSyntax&)node,composite,false);

}

void VisitorCSHARPML::writeAttributes(const expression::ImplicitElementAccessSyntax& node,bool composite, bool bWithParent /*= true*/ ) {
  writeAttributes((expression::ExpressionSyntax&)node,composite,false);

}

void VisitorCSHARPML::writeAttributes(const expression::ImplicitStackAllocArrayCreationExpressionSyntax& node,bool composite, bool bWithParent /*= true*/ ) {
  writeAttributes((expression::ExpressionSyntax&)node,composite,false);

}

void VisitorCSHARPML::writeAttributes(const expression::InitializerExpressionSyntax& node,bool composite, bool bWithParent /*= true*/ ) {
  writeAttributes((expression::ExpressionSyntax&)node,composite,false);

}

void VisitorCSHARPML::writeAttributes(const expression::InstanceExpressionSyntax& node,bool composite, bool bWithParent /*= true*/ ) {
  writeAttributes((expression::ExpressionSyntax&)node,composite,false);

}

void VisitorCSHARPML::writeAttributes(const expression::InterpolatedStringExpressionSyntax& node,bool composite, bool bWithParent /*= true*/ ) {
  writeAttributes((expression::ExpressionSyntax&)node,composite,false);

}

void VisitorCSHARPML::writeAttributes(const expression::InvocationExpressionSyntax& node,bool composite, bool bWithParent /*= true*/ ) {
  writeAttributes((expression::ExpressionSyntax&)node,composite,false);

}

void VisitorCSHARPML::writeAttributes(const expression::IsPatternExpressionSyntax& node,bool composite, bool bWithParent /*= true*/ ) {
  writeAttributes((expression::ExpressionSyntax&)node,composite,false);

}

void VisitorCSHARPML::writeAttributes(const expression::LambdaExpressionSyntax& node,bool composite, bool bWithParent /*= true*/ ) {
  writeAttributes((expression::AnonymousFunctionExpressionSyntax&)node,composite,false);

}

void VisitorCSHARPML::writeAttributes(const expression::LiteralExpressionSyntax& node,bool composite, bool bWithParent /*= true*/ ) {
  writeAttributes((expression::ExpressionSyntax&)node,composite,false);

  if (!composite) {
    ofs << " token='" << chk(node.getToken()) << "'";
  }
}

void VisitorCSHARPML::writeAttributes(const expression::MakeRefExpressionSyntax& node,bool composite, bool bWithParent /*= true*/ ) {
  writeAttributes((expression::ExpressionSyntax&)node,composite,false);

}

void VisitorCSHARPML::writeAttributes(const expression::MemberAccessExpressionSyntax& node,bool composite, bool bWithParent /*= true*/ ) {
  writeAttributes((expression::ExpressionSyntax&)node,composite,false);

}

void VisitorCSHARPML::writeAttributes(const expression::MemberBindingExpressionSyntax& node,bool composite, bool bWithParent /*= true*/ ) {
  writeAttributes((expression::ExpressionSyntax&)node,composite,false);

}

void VisitorCSHARPML::writeAttributes(const expression::NameSyntax& node,bool composite, bool bWithParent /*= true*/ ) {
  writeAttributes((expression::TypeSyntax&)node,composite,false);

}

void VisitorCSHARPML::writeAttributes(const expression::NullableTypeSyntax& node,bool composite, bool bWithParent /*= true*/ ) {
  writeAttributes((expression::TypeSyntax&)node,composite,false);

}

void VisitorCSHARPML::writeAttributes(const expression::ObjectCreationExpressionSyntax& node,bool composite, bool bWithParent /*= true*/ ) {
  writeAttributes((expression::ExpressionSyntax&)node,composite,false);

}

void VisitorCSHARPML::writeAttributes(const expression::OmittedArraySizeExpressionSyntax& node,bool composite, bool bWithParent /*= true*/ ) {
  writeAttributes((expression::ExpressionSyntax&)node,composite,false);

}

void VisitorCSHARPML::writeAttributes(const expression::OmittedTypeArgumentSyntax& node,bool composite, bool bWithParent /*= true*/ ) {
  writeAttributes((expression::TypeSyntax&)node,composite,false);

}

void VisitorCSHARPML::writeAttributes(const expression::ParenthesizedExpressionSyntax& node,bool composite, bool bWithParent /*= true*/ ) {
  writeAttributes((expression::ExpressionSyntax&)node,composite,false);

}

void VisitorCSHARPML::writeAttributes(const expression::ParenthesizedLambdaExpressionSyntax& node,bool composite, bool bWithParent /*= true*/ ) {
  writeAttributes((expression::LambdaExpressionSyntax&)node,composite,false);

}

void VisitorCSHARPML::writeAttributes(const expression::PointerTypeSyntax& node,bool composite, bool bWithParent /*= true*/ ) {
  writeAttributes((expression::TypeSyntax&)node,composite,false);

}

void VisitorCSHARPML::writeAttributes(const expression::PostfixUnaryExpressionSyntax& node,bool composite, bool bWithParent /*= true*/ ) {
  writeAttributes((expression::ExpressionSyntax&)node,composite,false);

}

void VisitorCSHARPML::writeAttributes(const expression::PredefinedTypeSyntax& node,bool composite, bool bWithParent /*= true*/ ) {
  writeAttributes((expression::TypeSyntax&)node,composite,false);

}

void VisitorCSHARPML::writeAttributes(const expression::PrefixUnaryExpressionSyntax& node,bool composite, bool bWithParent /*= true*/ ) {
  writeAttributes((expression::ExpressionSyntax&)node,composite,false);

}

void VisitorCSHARPML::writeAttributes(const expression::QualifiedNameSyntax& node,bool composite, bool bWithParent /*= true*/ ) {
  writeAttributes((expression::NameSyntax&)node,composite,false);

}

void VisitorCSHARPML::writeAttributes(const expression::QueryExpressionSyntax& node,bool composite, bool bWithParent /*= true*/ ) {
  writeAttributes((expression::ExpressionSyntax&)node,composite,false);

}

void VisitorCSHARPML::writeAttributes(const expression::RangeExpressionSyntax& node,bool composite, bool bWithParent /*= true*/ ) {
  writeAttributes((expression::ExpressionSyntax&)node,composite,false);

}

void VisitorCSHARPML::writeAttributes(const expression::RefExpressionSyntax& node,bool composite, bool bWithParent /*= true*/ ) {
  writeAttributes((expression::ExpressionSyntax&)node,composite,false);

}

void VisitorCSHARPML::writeAttributes(const expression::RefTypeExpressionSyntax& node,bool composite, bool bWithParent /*= true*/ ) {
  writeAttributes((expression::ExpressionSyntax&)node,composite,false);

}

void VisitorCSHARPML::writeAttributes(const expression::RefTypeSyntax& node,bool composite, bool bWithParent /*= true*/ ) {
  writeAttributes((expression::TypeSyntax&)node,composite,false);

}

void VisitorCSHARPML::writeAttributes(const expression::RefValueExpressionSyntax& node,bool composite, bool bWithParent /*= true*/ ) {
  writeAttributes((expression::ExpressionSyntax&)node,composite,false);

}

void VisitorCSHARPML::writeAttributes(const expression::SimpleLambdaExpressionSyntax& node,bool composite, bool bWithParent /*= true*/ ) {
  writeAttributes((expression::LambdaExpressionSyntax&)node,composite,false);

}

void VisitorCSHARPML::writeAttributes(const expression::SimpleNameSyntax& node,bool composite, bool bWithParent /*= true*/ ) {
  writeAttributes((expression::NameSyntax&)node,composite,false);

  if (!composite) {
    ofs << " identifier='" << chk(node.getIdentifier()) << "'";
  }
}

void VisitorCSHARPML::writeAttributes(const expression::SizeOfExpressionSyntax& node,bool composite, bool bWithParent /*= true*/ ) {
  writeAttributes((expression::ExpressionSyntax&)node,composite,false);

}

void VisitorCSHARPML::writeAttributes(const expression::StackAllocArrayCreationExpressionSyntax& node,bool composite, bool bWithParent /*= true*/ ) {
  writeAttributes((expression::ExpressionSyntax&)node,composite,false);

}

void VisitorCSHARPML::writeAttributes(const expression::SwitchExpressionSyntax& node,bool composite, bool bWithParent /*= true*/ ) {
  writeAttributes((expression::ExpressionSyntax&)node,composite,false);

}

void VisitorCSHARPML::writeAttributes(const expression::ThisExpressionSyntax& node,bool composite, bool bWithParent /*= true*/ ) {
  writeAttributes((expression::InstanceExpressionSyntax&)node,composite,false);

}

void VisitorCSHARPML::writeAttributes(const expression::ThrowExpressionSyntax& node,bool composite, bool bWithParent /*= true*/ ) {
  writeAttributes((expression::ExpressionSyntax&)node,composite,false);

}

void VisitorCSHARPML::writeAttributes(const expression::TupleExpressionSyntax& node,bool composite, bool bWithParent /*= true*/ ) {
  writeAttributes((expression::ExpressionSyntax&)node,composite,false);

}

void VisitorCSHARPML::writeAttributes(const expression::TupleTypeSyntax& node,bool composite, bool bWithParent /*= true*/ ) {
  writeAttributes((expression::TypeSyntax&)node,composite,false);

}

void VisitorCSHARPML::writeAttributes(const expression::TypeOfExpressionSyntax& node,bool composite, bool bWithParent /*= true*/ ) {
  writeAttributes((expression::ExpressionSyntax&)node,composite,false);

}

void VisitorCSHARPML::writeAttributes(const expression::TypeSyntax& node,bool composite, bool bWithParent /*= true*/ ) {
  writeAttributes((expression::ExpressionSyntax&)node,composite,false);

}

void VisitorCSHARPML::writeAttributes(const statement::BlockSyntax& node,bool composite, bool bWithParent /*= true*/ ) {
  writeAttributes((statement::StatementSyntax&)node,composite,false);

}

void VisitorCSHARPML::writeAttributes(const statement::BreakStatementSyntax& node,bool composite, bool bWithParent /*= true*/ ) {
  writeAttributes((statement::StatementSyntax&)node,composite,false);

}

void VisitorCSHARPML::writeAttributes(const statement::CheckedStatementSyntax& node,bool composite, bool bWithParent /*= true*/ ) {
  writeAttributes((statement::StatementSyntax&)node,composite,false);

}

void VisitorCSHARPML::writeAttributes(const statement::CommonForEachStatementSyntax& node,bool composite, bool bWithParent /*= true*/ ) {
  writeAttributes((statement::StatementSyntax&)node,composite,false);

}

void VisitorCSHARPML::writeAttributes(const statement::ContinueStatementSyntax& node,bool composite, bool bWithParent /*= true*/ ) {
  writeAttributes((statement::StatementSyntax&)node,composite,false);

}

void VisitorCSHARPML::writeAttributes(const statement::DoStatementSyntax& node,bool composite, bool bWithParent /*= true*/ ) {
  writeAttributes((statement::StatementSyntax&)node,composite,false);

}

void VisitorCSHARPML::writeAttributes(const statement::EmptyStatementSyntax& node,bool composite, bool bWithParent /*= true*/ ) {
  writeAttributes((statement::StatementSyntax&)node,composite,false);

}

void VisitorCSHARPML::writeAttributes(const statement::ExpressionStatementSyntax& node,bool composite, bool bWithParent /*= true*/ ) {
  writeAttributes((statement::StatementSyntax&)node,composite,false);

}

void VisitorCSHARPML::writeAttributes(const statement::FixedStatementSyntax& node,bool composite, bool bWithParent /*= true*/ ) {
  writeAttributes((statement::StatementSyntax&)node,composite,false);

}

void VisitorCSHARPML::writeAttributes(const statement::ForEachStatementSyntax& node,bool composite, bool bWithParent /*= true*/ ) {
  writeAttributes((statement::CommonForEachStatementSyntax&)node,composite,false);

  if (!composite) {
    ofs << " identifier='" << chk(node.getIdentifier()) << "'";
  }
}

void VisitorCSHARPML::writeAttributes(const statement::ForEachVariableStatementSyntax& node,bool composite, bool bWithParent /*= true*/ ) {
  writeAttributes((statement::CommonForEachStatementSyntax&)node,composite,false);

}

void VisitorCSHARPML::writeAttributes(const statement::ForStatementSyntax& node,bool composite, bool bWithParent /*= true*/ ) {
  writeAttributes((statement::StatementSyntax&)node,composite,false);

}

void VisitorCSHARPML::writeAttributes(const statement::GotoStatementSyntax& node,bool composite, bool bWithParent /*= true*/ ) {
  writeAttributes((statement::StatementSyntax&)node,composite,false);

}

void VisitorCSHARPML::writeAttributes(const statement::IfStatementSyntax& node,bool composite, bool bWithParent /*= true*/ ) {
  writeAttributes((statement::StatementSyntax&)node,composite,false);

}

void VisitorCSHARPML::writeAttributes(const statement::LabeledStatementSyntax& node,bool composite, bool bWithParent /*= true*/ ) {
  writeAttributes((statement::StatementSyntax&)node,composite,false);

  if (!composite) {
    ofs << " identifier='" << chk(node.getIdentifier()) << "'";
  }
}

void VisitorCSHARPML::writeAttributes(const statement::LocalDeclarationStatementSyntax& node,bool composite, bool bWithParent /*= true*/ ) {
  writeAttributes((statement::StatementSyntax&)node,composite,false);

}

void VisitorCSHARPML::writeAttributes(const statement::LocalFunctionStatementSyntax& node,bool composite, bool bWithParent /*= true*/ ) {
  writeAttributes((statement::StatementSyntax&)node,composite,false);

  if (!composite) {
    ofs << " identifier='" << chk(node.getIdentifier()) << "'";
  }
}

void VisitorCSHARPML::writeAttributes(const statement::LockStatementSyntax& node,bool composite, bool bWithParent /*= true*/ ) {
  writeAttributes((statement::StatementSyntax&)node,composite,false);

}

void VisitorCSHARPML::writeAttributes(const statement::ReturnStatementSyntax& node,bool composite, bool bWithParent /*= true*/ ) {
  writeAttributes((statement::StatementSyntax&)node,composite,false);

}

void VisitorCSHARPML::writeAttributes(const statement::StatementSyntax& node,bool composite, bool bWithParent /*= true*/ ) {
  writeAttributes((base::Positioned&)node,composite,false);

}

void VisitorCSHARPML::writeAttributes(const statement::SwitchStatementSyntax& node,bool composite, bool bWithParent /*= true*/ ) {
  writeAttributes((statement::StatementSyntax&)node,composite,false);

}

void VisitorCSHARPML::writeAttributes(const statement::ThrowStatementSyntax& node,bool composite, bool bWithParent /*= true*/ ) {
  writeAttributes((statement::StatementSyntax&)node,composite,false);

}

void VisitorCSHARPML::writeAttributes(const statement::TryStatementSyntax& node,bool composite, bool bWithParent /*= true*/ ) {
  writeAttributes((statement::StatementSyntax&)node,composite,false);

}

void VisitorCSHARPML::writeAttributes(const statement::UnsafeStatementSyntax& node,bool composite, bool bWithParent /*= true*/ ) {
  writeAttributes((statement::StatementSyntax&)node,composite,false);

}

void VisitorCSHARPML::writeAttributes(const statement::UsingStatementSyntax& node,bool composite, bool bWithParent /*= true*/ ) {
  writeAttributes((statement::StatementSyntax&)node,composite,false);

}

void VisitorCSHARPML::writeAttributes(const statement::WhileStatementSyntax& node,bool composite, bool bWithParent /*= true*/ ) {
  writeAttributes((statement::StatementSyntax&)node,composite,false);

}

void VisitorCSHARPML::writeAttributes(const statement::YieldStatementSyntax& node,bool composite, bool bWithParent /*= true*/ ) {
  writeAttributes((statement::StatementSyntax&)node,composite,false);

}

void VisitorCSHARPML::writeAttributes(const structure::AccessorDeclarationSyntax& node,bool composite, bool bWithParent /*= true*/ ) {
  writeAttributes((base::Positioned&)node,composite,false);

  if (!composite) {
    ofs << " identifier='" << chk(node.getIdentifier()) << "'";
  }
}

void VisitorCSHARPML::writeAttributes(const structure::AccessorListSyntax& node,bool composite, bool bWithParent /*= true*/ ) {
  writeAttributes((base::Positioned&)node,composite,false);

}

void VisitorCSHARPML::writeAttributes(const structure::AnonymousObjectMemberDeclaratorSyntax& node,bool composite, bool bWithParent /*= true*/ ) {
  writeAttributes((base::Positioned&)node,composite,false);

}

void VisitorCSHARPML::writeAttributes(const structure::ArgumentListSyntax& node,bool composite, bool bWithParent /*= true*/ ) {
  writeAttributes((structure::BaseArgumentListSyntax&)node,composite,false);

}

void VisitorCSHARPML::writeAttributes(const structure::ArgumentSyntax& node,bool composite, bool bWithParent /*= true*/ ) {
  writeAttributes((base::Positioned&)node,composite,false);

}

void VisitorCSHARPML::writeAttributes(const structure::ArrayRankSpecifierSyntax& node,bool composite, bool bWithParent /*= true*/ ) {
  writeAttributes((base::Positioned&)node,composite,false);

}

void VisitorCSHARPML::writeAttributes(const structure::ArrowExpressionClauseSyntax& node,bool composite, bool bWithParent /*= true*/ ) {
  writeAttributes((base::Positioned&)node,composite,false);

}

void VisitorCSHARPML::writeAttributes(const structure::AttributeArgumentListSyntax& node,bool composite, bool bWithParent /*= true*/ ) {
  writeAttributes((base::Positioned&)node,composite,false);

}

void VisitorCSHARPML::writeAttributes(const structure::AttributeArgumentSyntax& node,bool composite, bool bWithParent /*= true*/ ) {
  writeAttributes((base::Positioned&)node,composite,false);

}

void VisitorCSHARPML::writeAttributes(const structure::AttributeListSyntax& node,bool composite, bool bWithParent /*= true*/ ) {
  writeAttributes((base::Positioned&)node,composite,false);

}

void VisitorCSHARPML::writeAttributes(const structure::AttributeSyntax& node,bool composite, bool bWithParent /*= true*/ ) {
  writeAttributes((base::Positioned&)node,composite,false);

}

void VisitorCSHARPML::writeAttributes(const structure::AttributeTargetSpecifierSyntax& node,bool composite, bool bWithParent /*= true*/ ) {
  writeAttributes((base::Positioned&)node,composite,false);

  if (!composite) {
    ofs << " identifier='" << chk(node.getIdentifier()) << "'";
  }
}

void VisitorCSHARPML::writeAttributes(const structure::BaseArgumentListSyntax& node,bool composite, bool bWithParent /*= true*/ ) {
  writeAttributes((base::Positioned&)node,composite,false);

}

void VisitorCSHARPML::writeAttributes(const structure::BaseCrefParameterListSyntax& node,bool composite, bool bWithParent /*= true*/ ) {
  writeAttributes((base::Positioned&)node,composite,false);

}

void VisitorCSHARPML::writeAttributes(const structure::BaseFieldDeclarationSyntax& node,bool composite, bool bWithParent /*= true*/ ) {
  writeAttributes((structure::MemberDeclarationSyntax&)node,composite,false);

}

void VisitorCSHARPML::writeAttributes(const structure::BaseListSyntax& node,bool composite, bool bWithParent /*= true*/ ) {
  writeAttributes((base::Positioned&)node,composite,false);

}

void VisitorCSHARPML::writeAttributes(const structure::BaseMethodDeclarationSyntax& node,bool composite, bool bWithParent /*= true*/ ) {
  writeAttributes((structure::MemberDeclarationSyntax&)node,composite,false);

}

void VisitorCSHARPML::writeAttributes(const structure::BaseParameterListSyntax& node,bool composite, bool bWithParent /*= true*/ ) {
  writeAttributes((base::Positioned&)node,composite,false);

}

void VisitorCSHARPML::writeAttributes(const structure::BasePropertyDeclarationSyntax& node,bool composite, bool bWithParent /*= true*/ ) {
  writeAttributes((structure::MemberDeclarationSyntax&)node,composite,false);

}

void VisitorCSHARPML::writeAttributes(const structure::BaseTypeDeclarationSyntax& node,bool composite, bool bWithParent /*= true*/ ) {
  writeAttributes((structure::MemberDeclarationSyntax&)node,composite,false);

  if (!composite) {
    ofs << " identifier='" << chk(node.getIdentifier()) << "'";
  }
}

void VisitorCSHARPML::writeAttributes(const structure::BaseTypeSyntax& node,bool composite, bool bWithParent /*= true*/ ) {
  writeAttributes((base::Positioned&)node,composite,false);

}

void VisitorCSHARPML::writeAttributes(const structure::BracketedArgumentListSyntax& node,bool composite, bool bWithParent /*= true*/ ) {
  writeAttributes((structure::BaseArgumentListSyntax&)node,composite,false);

}

void VisitorCSHARPML::writeAttributes(const structure::BracketedParameterListSyntax& node,bool composite, bool bWithParent /*= true*/ ) {
  writeAttributes((structure::BaseParameterListSyntax&)node,composite,false);

}

void VisitorCSHARPML::writeAttributes(const structure::CasePatternSwitchLabelSyntax& node,bool composite, bool bWithParent /*= true*/ ) {
  writeAttributes((structure::SwitchLabelSyntax&)node,composite,false);

}

void VisitorCSHARPML::writeAttributes(const structure::CaseSwitchLabelSyntax& node,bool composite, bool bWithParent /*= true*/ ) {
  writeAttributes((structure::SwitchLabelSyntax&)node,composite,false);

}

void VisitorCSHARPML::writeAttributes(const structure::CatchClauseSyntax& node,bool composite, bool bWithParent /*= true*/ ) {
  writeAttributes((base::Positioned&)node,composite,false);

}

void VisitorCSHARPML::writeAttributes(const structure::CatchDeclarationSyntax& node,bool composite, bool bWithParent /*= true*/ ) {
  writeAttributes((base::Positioned&)node,composite,false);

}

void VisitorCSHARPML::writeAttributes(const structure::CatchFilterClauseSyntax& node,bool composite, bool bWithParent /*= true*/ ) {
  writeAttributes((base::Positioned&)node,composite,false);

}

void VisitorCSHARPML::writeAttributes(const structure::ClassDeclarationSyntax& node,bool composite, bool bWithParent /*= true*/ ) {
  writeAttributes((structure::TypeDeclarationSyntax&)node,composite,false);

}

void VisitorCSHARPML::writeAttributes(const structure::ClassOrStructConstraintSyntax& node,bool composite, bool bWithParent /*= true*/ ) {
  writeAttributes((structure::TypeParameterConstraintSyntax&)node,composite,false);

}

void VisitorCSHARPML::writeAttributes(const structure::CompilationUnitSyntax& node,bool composite, bool bWithParent /*= true*/ ) {
  writeAttributes((base::Positioned&)node,composite,false);

}

void VisitorCSHARPML::writeAttributes(const structure::ConstantPatternSyntax& node,bool composite, bool bWithParent /*= true*/ ) {
  writeAttributes((structure::PatternSyntax&)node,composite,false);

}

void VisitorCSHARPML::writeAttributes(const structure::ConstructorConstraintSyntax& node,bool composite, bool bWithParent /*= true*/ ) {
  writeAttributes((structure::TypeParameterConstraintSyntax&)node,composite,false);

}

void VisitorCSHARPML::writeAttributes(const structure::ConstructorDeclarationSyntax& node,bool composite, bool bWithParent /*= true*/ ) {
  writeAttributes((structure::BaseMethodDeclarationSyntax&)node,composite,false);

  if (!composite) {
    ofs << " identifier='" << chk(node.getIdentifier()) << "'";
  }
}

void VisitorCSHARPML::writeAttributes(const structure::ConstructorInitializerSyntax& node,bool composite, bool bWithParent /*= true*/ ) {
  writeAttributes((base::Positioned&)node,composite,false);

}

void VisitorCSHARPML::writeAttributes(const structure::ConversionOperatorDeclarationSyntax& node,bool composite, bool bWithParent /*= true*/ ) {
  writeAttributes((structure::BaseMethodDeclarationSyntax&)node,composite,false);

}

void VisitorCSHARPML::writeAttributes(const structure::ConversionOperatorMemberCrefSyntax& node,bool composite, bool bWithParent /*= true*/ ) {
  writeAttributes((structure::MemberCrefSyntax&)node,composite,false);

}

void VisitorCSHARPML::writeAttributes(const structure::CrefBracketedParameterListSyntax& node,bool composite, bool bWithParent /*= true*/ ) {
  writeAttributes((structure::BaseCrefParameterListSyntax&)node,composite,false);

}

void VisitorCSHARPML::writeAttributes(const structure::CrefParameterListSyntax& node,bool composite, bool bWithParent /*= true*/ ) {
  writeAttributes((structure::BaseCrefParameterListSyntax&)node,composite,false);

}

void VisitorCSHARPML::writeAttributes(const structure::CrefParameterSyntax& node,bool composite, bool bWithParent /*= true*/ ) {
  writeAttributes((base::Positioned&)node,composite,false);

}

void VisitorCSHARPML::writeAttributes(const structure::CrefSyntax& node,bool composite, bool bWithParent /*= true*/ ) {
  writeAttributes((base::Positioned&)node,composite,false);

}

void VisitorCSHARPML::writeAttributes(const structure::DeclarationPatternSyntax& node,bool composite, bool bWithParent /*= true*/ ) {
  writeAttributes((structure::PatternSyntax&)node,composite,false);

}

void VisitorCSHARPML::writeAttributes(const structure::DefaultSwitchLabelSyntax& node,bool composite, bool bWithParent /*= true*/ ) {
  writeAttributes((structure::SwitchLabelSyntax&)node,composite,false);

}

void VisitorCSHARPML::writeAttributes(const structure::DelegateDeclarationSyntax& node,bool composite, bool bWithParent /*= true*/ ) {
  writeAttributes((structure::MemberDeclarationSyntax&)node,composite,false);

  if (!composite) {
    ofs << " identifier='" << chk(node.getIdentifier()) << "'";
  }
}

void VisitorCSHARPML::writeAttributes(const structure::DestructorDeclarationSyntax& node,bool composite, bool bWithParent /*= true*/ ) {
  writeAttributes((structure::BaseMethodDeclarationSyntax&)node,composite,false);

  if (!composite) {
    ofs << " identifier='" << chk(node.getIdentifier()) << "'";
  }
}

void VisitorCSHARPML::writeAttributes(const structure::DiscardDesignationSyntax& node,bool composite, bool bWithParent /*= true*/ ) {
  writeAttributes((structure::VariableDesignationSyntax&)node,composite,false);

}

void VisitorCSHARPML::writeAttributes(const structure::DiscardPatternSyntax& node,bool composite, bool bWithParent /*= true*/ ) {
  writeAttributes((structure::PatternSyntax&)node,composite,false);

}

void VisitorCSHARPML::writeAttributes(const structure::ElseClauseSyntax& node,bool composite, bool bWithParent /*= true*/ ) {
  writeAttributes((base::Positioned&)node,composite,false);

}

void VisitorCSHARPML::writeAttributes(const structure::EnumDeclarationSyntax& node,bool composite, bool bWithParent /*= true*/ ) {
  writeAttributes((structure::BaseTypeDeclarationSyntax&)node,composite,false);

}

void VisitorCSHARPML::writeAttributes(const structure::EnumMemberDeclarationSyntax& node,bool composite, bool bWithParent /*= true*/ ) {
  writeAttributes((structure::MemberDeclarationSyntax&)node,composite,false);

  if (!composite) {
    ofs << " identifier='" << chk(node.getIdentifier()) << "'";
  }
}

void VisitorCSHARPML::writeAttributes(const structure::EqualsValueClauseSyntax& node,bool composite, bool bWithParent /*= true*/ ) {
  writeAttributes((base::Positioned&)node,composite,false);

}

void VisitorCSHARPML::writeAttributes(const structure::EventDeclarationSyntax& node,bool composite, bool bWithParent /*= true*/ ) {
  writeAttributes((structure::BasePropertyDeclarationSyntax&)node,composite,false);

  if (!composite) {
    ofs << " identifier='" << chk(node.getIdentifier()) << "'";
  }
}

void VisitorCSHARPML::writeAttributes(const structure::EventFieldDeclarationSyntax& node,bool composite, bool bWithParent /*= true*/ ) {
  writeAttributes((structure::BaseFieldDeclarationSyntax&)node,composite,false);

}

void VisitorCSHARPML::writeAttributes(const structure::ExplicitInterfaceSpecifierSyntax& node,bool composite, bool bWithParent /*= true*/ ) {
  writeAttributes((base::Positioned&)node,composite,false);

}

void VisitorCSHARPML::writeAttributes(const structure::ExternAliasDirectiveSyntax& node,bool composite, bool bWithParent /*= true*/ ) {
  writeAttributes((base::Positioned&)node,composite,false);

  if (!composite) {
    ofs << " identifier='" << chk(node.getIdentifier()) << "'";
  }
}

void VisitorCSHARPML::writeAttributes(const structure::FieldDeclarationSyntax& node,bool composite, bool bWithParent /*= true*/ ) {
  writeAttributes((structure::BaseFieldDeclarationSyntax&)node,composite,false);

}

void VisitorCSHARPML::writeAttributes(const structure::FinallyClauseSyntax& node,bool composite, bool bWithParent /*= true*/ ) {
  writeAttributes((base::Positioned&)node,composite,false);

}

void VisitorCSHARPML::writeAttributes(const structure::FromClauseSyntax& node,bool composite, bool bWithParent /*= true*/ ) {
  writeAttributes((structure::QueryClauseSyntax&)node,composite,false);

  if (!composite) {
    ofs << " identifier='" << chk(node.getIdentifier()) << "'";
  }
}

void VisitorCSHARPML::writeAttributes(const structure::GlobalStatementSyntax& node,bool composite, bool bWithParent /*= true*/ ) {
  writeAttributes((structure::MemberDeclarationSyntax&)node,composite,false);

}

void VisitorCSHARPML::writeAttributes(const structure::GroupClauseSyntax& node,bool composite, bool bWithParent /*= true*/ ) {
  writeAttributes((structure::SelectOrGroupClauseSyntax&)node,composite,false);

}

void VisitorCSHARPML::writeAttributes(const structure::IncompleteMemberSyntax& node,bool composite, bool bWithParent /*= true*/ ) {
  writeAttributes((structure::MemberDeclarationSyntax&)node,composite,false);

}

void VisitorCSHARPML::writeAttributes(const structure::IndexerDeclarationSyntax& node,bool composite, bool bWithParent /*= true*/ ) {
  writeAttributes((structure::BasePropertyDeclarationSyntax&)node,composite,false);

}

void VisitorCSHARPML::writeAttributes(const structure::IndexerMemberCrefSyntax& node,bool composite, bool bWithParent /*= true*/ ) {
  writeAttributes((structure::MemberCrefSyntax&)node,composite,false);

}

void VisitorCSHARPML::writeAttributes(const structure::InterfaceDeclarationSyntax& node,bool composite, bool bWithParent /*= true*/ ) {
  writeAttributes((structure::TypeDeclarationSyntax&)node,composite,false);

}

void VisitorCSHARPML::writeAttributes(const structure::InterpolatedStringContentSyntax& node,bool composite, bool bWithParent /*= true*/ ) {
  writeAttributes((base::Positioned&)node,composite,false);

}

void VisitorCSHARPML::writeAttributes(const structure::InterpolatedStringTextSyntax& node,bool composite, bool bWithParent /*= true*/ ) {
  writeAttributes((structure::InterpolatedStringContentSyntax&)node,composite,false);

}

void VisitorCSHARPML::writeAttributes(const structure::InterpolationAlignmentClauseSyntax& node,bool composite, bool bWithParent /*= true*/ ) {
  writeAttributes((base::Positioned&)node,composite,false);

}

void VisitorCSHARPML::writeAttributes(const structure::InterpolationFormatClauseSyntax& node,bool composite, bool bWithParent /*= true*/ ) {
  writeAttributes((base::Positioned&)node,composite,false);

}

void VisitorCSHARPML::writeAttributes(const structure::InterpolationSyntax& node,bool composite, bool bWithParent /*= true*/ ) {
  writeAttributes((structure::InterpolatedStringContentSyntax&)node,composite,false);

}

void VisitorCSHARPML::writeAttributes(const structure::JoinClauseSyntax& node,bool composite, bool bWithParent /*= true*/ ) {
  writeAttributes((structure::QueryClauseSyntax&)node,composite,false);

  if (!composite) {
    ofs << " identifier='" << chk(node.getIdentifier()) << "'";
  }
}

void VisitorCSHARPML::writeAttributes(const structure::JoinIntoClauseSyntax& node,bool composite, bool bWithParent /*= true*/ ) {
  writeAttributes((base::Positioned&)node,composite,false);

  if (!composite) {
    ofs << " identifier='" << chk(node.getIdentifier()) << "'";
  }
}

void VisitorCSHARPML::writeAttributes(const structure::LetClauseSyntax& node,bool composite, bool bWithParent /*= true*/ ) {
  writeAttributes((structure::QueryClauseSyntax&)node,composite,false);

  if (!composite) {
    ofs << " identifier='" << chk(node.getIdentifier()) << "'";
  }
}

void VisitorCSHARPML::writeAttributes(const structure::MemberCrefSyntax& node,bool composite, bool bWithParent /*= true*/ ) {
  writeAttributes((structure::CrefSyntax&)node,composite,false);

}

void VisitorCSHARPML::writeAttributes(const structure::MemberDeclarationSyntax& node,bool composite, bool bWithParent /*= true*/ ) {
  writeAttributes((base::Positioned&)node,composite,false);

}

void VisitorCSHARPML::writeAttributes(const structure::MethodDeclarationSyntax& node,bool composite, bool bWithParent /*= true*/ ) {
  writeAttributes((structure::BaseMethodDeclarationSyntax&)node,composite,false);

  if (!composite) {
    ofs << " identifier='" << chk(node.getIdentifier()) << "'";
  }
}

void VisitorCSHARPML::writeAttributes(const structure::NameColonSyntax& node,bool composite, bool bWithParent /*= true*/ ) {
  writeAttributes((base::Positioned&)node,composite,false);

}

void VisitorCSHARPML::writeAttributes(const structure::NameEqualsSyntax& node,bool composite, bool bWithParent /*= true*/ ) {
  writeAttributes((base::Positioned&)node,composite,false);

}

void VisitorCSHARPML::writeAttributes(const structure::NameMemberCrefSyntax& node,bool composite, bool bWithParent /*= true*/ ) {
  writeAttributes((structure::MemberCrefSyntax&)node,composite,false);

}

void VisitorCSHARPML::writeAttributes(const structure::NamespaceDeclarationSyntax& node,bool composite, bool bWithParent /*= true*/ ) {
  writeAttributes((structure::MemberDeclarationSyntax&)node,composite,false);

}

void VisitorCSHARPML::writeAttributes(const structure::OperatorDeclarationSyntax& node,bool composite, bool bWithParent /*= true*/ ) {
  writeAttributes((structure::BaseMethodDeclarationSyntax&)node,composite,false);

}

void VisitorCSHARPML::writeAttributes(const structure::OperatorMemberCrefSyntax& node,bool composite, bool bWithParent /*= true*/ ) {
  writeAttributes((structure::MemberCrefSyntax&)node,composite,false);

}

void VisitorCSHARPML::writeAttributes(const structure::OrderByClauseSyntax& node,bool composite, bool bWithParent /*= true*/ ) {
  writeAttributes((structure::QueryClauseSyntax&)node,composite,false);

}

void VisitorCSHARPML::writeAttributes(const structure::OrderingSyntax& node,bool composite, bool bWithParent /*= true*/ ) {
  writeAttributes((base::Positioned&)node,composite,false);

}

void VisitorCSHARPML::writeAttributes(const structure::ParameterListSyntax& node,bool composite, bool bWithParent /*= true*/ ) {
  writeAttributes((structure::BaseParameterListSyntax&)node,composite,false);

}

void VisitorCSHARPML::writeAttributes(const structure::ParameterSyntax& node,bool composite, bool bWithParent /*= true*/ ) {
  writeAttributes((base::Positioned&)node,composite,false);

  if (!composite) {
    ofs << " identifier='" << chk(node.getIdentifier()) << "'";
  }
}

void VisitorCSHARPML::writeAttributes(const structure::ParenthesizedVariableDesignationSyntax& node,bool composite, bool bWithParent /*= true*/ ) {
  writeAttributes((structure::VariableDesignationSyntax&)node,composite,false);

}

void VisitorCSHARPML::writeAttributes(const structure::PatternSyntax& node,bool composite, bool bWithParent /*= true*/ ) {
  writeAttributes((base::Positioned&)node,composite,false);

}

void VisitorCSHARPML::writeAttributes(const structure::PositionalPatternClauseSyntax& node,bool composite, bool bWithParent /*= true*/ ) {
  writeAttributes((base::Positioned&)node,composite,false);

}

void VisitorCSHARPML::writeAttributes(const structure::PropertyDeclarationSyntax& node,bool composite, bool bWithParent /*= true*/ ) {
  writeAttributes((structure::BasePropertyDeclarationSyntax&)node,composite,false);

  if (!composite) {
    ofs << " identifier='" << chk(node.getIdentifier()) << "'";
  }
}

void VisitorCSHARPML::writeAttributes(const structure::PropertyPatternClauseSyntax& node,bool composite, bool bWithParent /*= true*/ ) {
  writeAttributes((base::Positioned&)node,composite,false);

}

void VisitorCSHARPML::writeAttributes(const structure::QualifiedCrefSyntax& node,bool composite, bool bWithParent /*= true*/ ) {
  writeAttributes((structure::CrefSyntax&)node,composite,false);

}

void VisitorCSHARPML::writeAttributes(const structure::QueryBodySyntax& node,bool composite, bool bWithParent /*= true*/ ) {
  writeAttributes((base::Positioned&)node,composite,false);

}

void VisitorCSHARPML::writeAttributes(const structure::QueryClauseSyntax& node,bool composite, bool bWithParent /*= true*/ ) {
  writeAttributes((base::Positioned&)node,composite,false);

}

void VisitorCSHARPML::writeAttributes(const structure::QueryContinuationSyntax& node,bool composite, bool bWithParent /*= true*/ ) {
  writeAttributes((base::Positioned&)node,composite,false);

  if (!composite) {
    ofs << " identifier='" << chk(node.getIdentifier()) << "'";
  }
}

void VisitorCSHARPML::writeAttributes(const structure::RecursivePatternSyntax& node,bool composite, bool bWithParent /*= true*/ ) {
  writeAttributes((structure::PatternSyntax&)node,composite,false);

}

void VisitorCSHARPML::writeAttributes(const structure::SelectClauseSyntax& node,bool composite, bool bWithParent /*= true*/ ) {
  writeAttributes((structure::SelectOrGroupClauseSyntax&)node,composite,false);

}

void VisitorCSHARPML::writeAttributes(const structure::SelectOrGroupClauseSyntax& node,bool composite, bool bWithParent /*= true*/ ) {
  writeAttributes((base::Positioned&)node,composite,false);

}

void VisitorCSHARPML::writeAttributes(const structure::SimpleBaseTypeSyntax& node,bool composite, bool bWithParent /*= true*/ ) {
  writeAttributes((structure::BaseTypeSyntax&)node,composite,false);

}

void VisitorCSHARPML::writeAttributes(const structure::SingleVariableDesignationSyntax& node,bool composite, bool bWithParent /*= true*/ ) {
  writeAttributes((structure::VariableDesignationSyntax&)node,composite,false);

  if (!composite) {
    ofs << " identifier='" << chk(node.getIdentifier()) << "'";
  }
}

void VisitorCSHARPML::writeAttributes(const structure::StructDeclarationSyntax& node,bool composite, bool bWithParent /*= true*/ ) {
  writeAttributes((structure::TypeDeclarationSyntax&)node,composite,false);

}

void VisitorCSHARPML::writeAttributes(const structure::SubpatternSyntax& node,bool composite, bool bWithParent /*= true*/ ) {
  writeAttributes((base::Positioned&)node,composite,false);

}

void VisitorCSHARPML::writeAttributes(const structure::SwitchExpressionArmSyntax& node,bool composite, bool bWithParent /*= true*/ ) {
  writeAttributes((base::Positioned&)node,composite,false);

}

void VisitorCSHARPML::writeAttributes(const structure::SwitchLabelSyntax& node,bool composite, bool bWithParent /*= true*/ ) {
  writeAttributes((base::Positioned&)node,composite,false);

}

void VisitorCSHARPML::writeAttributes(const structure::SwitchSectionSyntax& node,bool composite, bool bWithParent /*= true*/ ) {
  writeAttributes((base::Positioned&)node,composite,false);

}

void VisitorCSHARPML::writeAttributes(const structure::SyntaxToken& node,bool composite, bool bWithParent /*= true*/ ) {
  writeAttributes((base::Positioned&)node,composite,false);

}

void VisitorCSHARPML::writeAttributes(const structure::TupleElementSyntax& node,bool composite, bool bWithParent /*= true*/ ) {
  writeAttributes((base::Positioned&)node,composite,false);

  if (!composite) {
    ofs << " identifier='" << chk(node.getIdentifier()) << "'";
  }
}

void VisitorCSHARPML::writeAttributes(const structure::TypeArgumentListSyntax& node,bool composite, bool bWithParent /*= true*/ ) {
  writeAttributes((base::Positioned&)node,composite,false);

}

void VisitorCSHARPML::writeAttributes(const structure::TypeConstraintSyntax& node,bool composite, bool bWithParent /*= true*/ ) {
  writeAttributes((structure::TypeParameterConstraintSyntax&)node,composite,false);

}

void VisitorCSHARPML::writeAttributes(const structure::TypeCrefSyntax& node,bool composite, bool bWithParent /*= true*/ ) {
  writeAttributes((structure::CrefSyntax&)node,composite,false);

}

void VisitorCSHARPML::writeAttributes(const structure::TypeDeclarationSyntax& node,bool composite, bool bWithParent /*= true*/ ) {
  writeAttributes((structure::BaseTypeDeclarationSyntax&)node,composite,false);

}

void VisitorCSHARPML::writeAttributes(const structure::TypeParameterConstraintClauseSyntax& node,bool composite, bool bWithParent /*= true*/ ) {
  writeAttributes((base::Positioned&)node,composite,false);

}

void VisitorCSHARPML::writeAttributes(const structure::TypeParameterConstraintSyntax& node,bool composite, bool bWithParent /*= true*/ ) {
  writeAttributes((base::Positioned&)node,composite,false);

}

void VisitorCSHARPML::writeAttributes(const structure::TypeParameterListSyntax& node,bool composite, bool bWithParent /*= true*/ ) {
  writeAttributes((base::Positioned&)node,composite,false);

}

void VisitorCSHARPML::writeAttributes(const structure::TypeParameterSyntax& node,bool composite, bool bWithParent /*= true*/ ) {
  writeAttributes((base::Positioned&)node,composite,false);

  if (!composite) {
    ofs << " identifier='" << chk(node.getIdentifier()) << "'";
  }
}

void VisitorCSHARPML::writeAttributes(const structure::UsingDirectiveSyntax& node,bool composite, bool bWithParent /*= true*/ ) {
  writeAttributes((base::Positioned&)node,composite,false);

}

void VisitorCSHARPML::writeAttributes(const structure::VarPatternSyntax& node,bool composite, bool bWithParent /*= true*/ ) {
  writeAttributes((structure::PatternSyntax&)node,composite,false);

}

void VisitorCSHARPML::writeAttributes(const structure::VariableDeclarationSyntax& node,bool composite, bool bWithParent /*= true*/ ) {
  writeAttributes((base::Positioned&)node,composite,false);

}

void VisitorCSHARPML::writeAttributes(const structure::VariableDeclaratorSyntax& node,bool composite, bool bWithParent /*= true*/ ) {
  writeAttributes((base::Positioned&)node,composite,false);

  if (!composite) {
    ofs << " identifier='" << chk(node.getIdentifier()) << "'";
  }
}

void VisitorCSHARPML::writeAttributes(const structure::VariableDesignationSyntax& node,bool composite, bool bWithParent /*= true*/ ) {
  writeAttributes((base::Positioned&)node,composite,false);

}

void VisitorCSHARPML::writeAttributes(const structure::WhenClauseSyntax& node,bool composite, bool bWithParent /*= true*/ ) {
  writeAttributes((base::Positioned&)node,composite,false);

}

void VisitorCSHARPML::writeAttributes(const structure::WhereClauseSyntax& node,bool composite, bool bWithParent /*= true*/ ) {
  writeAttributes((structure::QueryClauseSyntax&)node,composite,false);

}

void VisitorCSHARPML::writeAttributes(const structure::XmlAttributeSyntax& node,bool composite, bool bWithParent /*= true*/ ) {
  writeAttributes((base::Positioned&)node,composite,false);

}

void VisitorCSHARPML::writeAttributes(const structure::XmlCDataSectionSyntax& node,bool composite, bool bWithParent /*= true*/ ) {
  writeAttributes((structure::XmlNodeSyntax&)node,composite,false);

}

void VisitorCSHARPML::writeAttributes(const structure::XmlCommentSyntax& node,bool composite, bool bWithParent /*= true*/ ) {
  writeAttributes((structure::XmlNodeSyntax&)node,composite,false);

}

void VisitorCSHARPML::writeAttributes(const structure::XmlCrefAttributeSyntax& node,bool composite, bool bWithParent /*= true*/ ) {
  writeAttributes((structure::XmlAttributeSyntax&)node,composite,false);

}

void VisitorCSHARPML::writeAttributes(const structure::XmlElementEndTagSyntax& node,bool composite, bool bWithParent /*= true*/ ) {
  writeAttributes((base::Positioned&)node,composite,false);

}

void VisitorCSHARPML::writeAttributes(const structure::XmlElementStartTagSyntax& node,bool composite, bool bWithParent /*= true*/ ) {
  writeAttributes((base::Positioned&)node,composite,false);

}

void VisitorCSHARPML::writeAttributes(const structure::XmlElementSyntax& node,bool composite, bool bWithParent /*= true*/ ) {
  writeAttributes((structure::XmlNodeSyntax&)node,composite,false);

}

void VisitorCSHARPML::writeAttributes(const structure::XmlEmptyElementSyntax& node,bool composite, bool bWithParent /*= true*/ ) {
  writeAttributes((structure::XmlNodeSyntax&)node,composite,false);

}

void VisitorCSHARPML::writeAttributes(const structure::XmlNameAttributeSyntax& node,bool composite, bool bWithParent /*= true*/ ) {
  writeAttributes((structure::XmlAttributeSyntax&)node,composite,false);

}

void VisitorCSHARPML::writeAttributes(const structure::XmlNameSyntax& node,bool composite, bool bWithParent /*= true*/ ) {
  writeAttributes((base::Positioned&)node,composite,false);

}

void VisitorCSHARPML::writeAttributes(const structure::XmlNodeSyntax& node,bool composite, bool bWithParent /*= true*/ ) {
  writeAttributes((base::Positioned&)node,composite,false);

}

void VisitorCSHARPML::writeAttributes(const structure::XmlPrefixSyntax& node,bool composite, bool bWithParent /*= true*/ ) {
  writeAttributes((base::Positioned&)node,composite,false);

}

void VisitorCSHARPML::writeAttributes(const structure::XmlProcessingInstructionSyntax& node,bool composite, bool bWithParent /*= true*/ ) {
  writeAttributes((structure::XmlNodeSyntax&)node,composite,false);

}

void VisitorCSHARPML::writeAttributes(const structure::XmlTextAttributeSyntax& node,bool composite, bool bWithParent /*= true*/ ) {
  writeAttributes((structure::XmlAttributeSyntax&)node,composite,false);

}

void VisitorCSHARPML::writeAttributes(const structure::XmlTextSyntax& node,bool composite, bool bWithParent /*= true*/ ) {
  writeAttributes((structure::XmlNodeSyntax&)node,composite,false);

}

void VisitorCSHARPML::writeAttributes(const SourcePosition& compType,bool composite) {
  if (!composite) {
    ofs << " endColumn='" << compType.getEndColumn() << "'";
  }
  if (!composite) {
    ofs << " endLine='" << compType.getEndLine() << "'";
  }
  if (!composite) {
    ofs << " fileName='" << chk(compType.getFileName()) << "'";
  }
  if (!composite) {
    ofs << " startColumn='" << compType.getStartColumn() << "'";
  }
  if (!composite) {
    ofs << " startLine='" << compType.getStartLine() << "'";
  }
}


}}}
