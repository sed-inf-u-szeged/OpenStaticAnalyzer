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


namespace columbus { namespace csharp { namespace asg {
VisitorAbstractNodes::~VisitorAbstractNodes() { }

void VisitorAbstractNodes::visit   (const base::Base& node , bool callVirtualBase) { }
void VisitorAbstractNodes::visitEnd(const base::Base& node , bool callVirtualBase) { }

void VisitorAbstractNodes::visit(const base::Positioned& node , bool callVirtualBase) {
  visit   ((base::Base&)node,false); 
}

void VisitorAbstractNodes::visitEnd(const base::Positioned& node , bool callVirtualBase) {
  visitEnd   ((base::Base&)node,false); 
}

void VisitorAbstractNodes::visit(const expression::AliasQualifiedNameSyntax& node , bool callVirtualBase) {
  visit   ((expression::NameSyntax&)node,false); 
}

void VisitorAbstractNodes::visitEnd(const expression::AliasQualifiedNameSyntax& node , bool callVirtualBase) {
  visitEnd   ((expression::NameSyntax&)node,false); 
}

void VisitorAbstractNodes::visit(const expression::AnonymousFunctionExpressionSyntax& node , bool callVirtualBase) {
  visit   ((expression::ExpressionSyntax&)node,false); 
}

void VisitorAbstractNodes::visitEnd(const expression::AnonymousFunctionExpressionSyntax& node , bool callVirtualBase) {
  visitEnd   ((expression::ExpressionSyntax&)node,false); 
}

void VisitorAbstractNodes::visit(const expression::AnonymousMethodExpressionSyntax& node , bool callVirtualBase) {
  visit   ((expression::AnonymousFunctionExpressionSyntax&)node,false); 
}

void VisitorAbstractNodes::visitEnd(const expression::AnonymousMethodExpressionSyntax& node , bool callVirtualBase) {
  visitEnd   ((expression::AnonymousFunctionExpressionSyntax&)node,false); 
}

void VisitorAbstractNodes::visit(const expression::AnonymousObjectCreationExpressionSyntax& node , bool callVirtualBase) {
  visit   ((expression::ExpressionSyntax&)node,false); 
}

void VisitorAbstractNodes::visitEnd(const expression::AnonymousObjectCreationExpressionSyntax& node , bool callVirtualBase) {
  visitEnd   ((expression::ExpressionSyntax&)node,false); 
}

void VisitorAbstractNodes::visit(const expression::ArrayCreationExpressionSyntax& node , bool callVirtualBase) {
  visit   ((expression::ExpressionSyntax&)node,false); 
}

void VisitorAbstractNodes::visitEnd(const expression::ArrayCreationExpressionSyntax& node , bool callVirtualBase) {
  visitEnd   ((expression::ExpressionSyntax&)node,false); 
}

void VisitorAbstractNodes::visit(const expression::ArrayTypeSyntax& node , bool callVirtualBase) {
  visit   ((expression::TypeSyntax&)node,false); 
}

void VisitorAbstractNodes::visitEnd(const expression::ArrayTypeSyntax& node , bool callVirtualBase) {
  visitEnd   ((expression::TypeSyntax&)node,false); 
}

void VisitorAbstractNodes::visit(const expression::AssignmentExpressionSyntax& node , bool callVirtualBase) {
  visit   ((expression::ExpressionSyntax&)node,false); 
}

void VisitorAbstractNodes::visitEnd(const expression::AssignmentExpressionSyntax& node , bool callVirtualBase) {
  visitEnd   ((expression::ExpressionSyntax&)node,false); 
}

void VisitorAbstractNodes::visit(const expression::AwaitExpressionSyntax& node , bool callVirtualBase) {
  visit   ((expression::ExpressionSyntax&)node,false); 
}

void VisitorAbstractNodes::visitEnd(const expression::AwaitExpressionSyntax& node , bool callVirtualBase) {
  visitEnd   ((expression::ExpressionSyntax&)node,false); 
}

void VisitorAbstractNodes::visit(const expression::BaseExpressionSyntax& node , bool callVirtualBase) {
  visit   ((expression::InstanceExpressionSyntax&)node,false); 
}

void VisitorAbstractNodes::visitEnd(const expression::BaseExpressionSyntax& node , bool callVirtualBase) {
  visitEnd   ((expression::InstanceExpressionSyntax&)node,false); 
}

void VisitorAbstractNodes::visit(const expression::BinaryExpressionSyntax& node , bool callVirtualBase) {
  visit   ((expression::ExpressionSyntax&)node,false); 
}

void VisitorAbstractNodes::visitEnd(const expression::BinaryExpressionSyntax& node , bool callVirtualBase) {
  visitEnd   ((expression::ExpressionSyntax&)node,false); 
}

void VisitorAbstractNodes::visit(const expression::CastExpressionSyntax& node , bool callVirtualBase) {
  visit   ((expression::ExpressionSyntax&)node,false); 
}

void VisitorAbstractNodes::visitEnd(const expression::CastExpressionSyntax& node , bool callVirtualBase) {
  visitEnd   ((expression::ExpressionSyntax&)node,false); 
}

void VisitorAbstractNodes::visit(const expression::CheckedExpressionSyntax& node , bool callVirtualBase) {
  visit   ((expression::ExpressionSyntax&)node,false); 
}

void VisitorAbstractNodes::visitEnd(const expression::CheckedExpressionSyntax& node , bool callVirtualBase) {
  visitEnd   ((expression::ExpressionSyntax&)node,false); 
}

void VisitorAbstractNodes::visit(const expression::ConditionalAccessExpressionSyntax& node , bool callVirtualBase) {
  visit   ((expression::ExpressionSyntax&)node,false); 
}

void VisitorAbstractNodes::visitEnd(const expression::ConditionalAccessExpressionSyntax& node , bool callVirtualBase) {
  visitEnd   ((expression::ExpressionSyntax&)node,false); 
}

void VisitorAbstractNodes::visit(const expression::ConditionalExpressionSyntax& node , bool callVirtualBase) {
  visit   ((expression::ExpressionSyntax&)node,false); 
}

void VisitorAbstractNodes::visitEnd(const expression::ConditionalExpressionSyntax& node , bool callVirtualBase) {
  visitEnd   ((expression::ExpressionSyntax&)node,false); 
}

void VisitorAbstractNodes::visit(const expression::DeclarationExpressionSyntax& node , bool callVirtualBase) {
  visit   ((expression::ExpressionSyntax&)node,false); 
}

void VisitorAbstractNodes::visitEnd(const expression::DeclarationExpressionSyntax& node , bool callVirtualBase) {
  visitEnd   ((expression::ExpressionSyntax&)node,false); 
}

void VisitorAbstractNodes::visit(const expression::DefaultExpressionSyntax& node , bool callVirtualBase) {
  visit   ((expression::ExpressionSyntax&)node,false); 
}

void VisitorAbstractNodes::visitEnd(const expression::DefaultExpressionSyntax& node , bool callVirtualBase) {
  visitEnd   ((expression::ExpressionSyntax&)node,false); 
}

void VisitorAbstractNodes::visit(const expression::ElementAccessExpressionSyntax& node , bool callVirtualBase) {
  visit   ((expression::ExpressionSyntax&)node,false); 
}

void VisitorAbstractNodes::visitEnd(const expression::ElementAccessExpressionSyntax& node , bool callVirtualBase) {
  visitEnd   ((expression::ExpressionSyntax&)node,false); 
}

void VisitorAbstractNodes::visit(const expression::ElementBindingExpressionSyntax& node , bool callVirtualBase) {
  visit   ((expression::ExpressionSyntax&)node,false); 
}

void VisitorAbstractNodes::visitEnd(const expression::ElementBindingExpressionSyntax& node , bool callVirtualBase) {
  visitEnd   ((expression::ExpressionSyntax&)node,false); 
}

void VisitorAbstractNodes::visit(const expression::ExpressionSyntax& node , bool callVirtualBase) {
  visit   ((base::Positioned&)node,false); 
}

void VisitorAbstractNodes::visitEnd(const expression::ExpressionSyntax& node , bool callVirtualBase) {
  visitEnd   ((base::Positioned&)node,false); 
}

void VisitorAbstractNodes::visit(const expression::GenericNameSyntax& node , bool callVirtualBase) {
  visit   ((expression::SimpleNameSyntax&)node,false); 
}

void VisitorAbstractNodes::visitEnd(const expression::GenericNameSyntax& node , bool callVirtualBase) {
  visitEnd   ((expression::SimpleNameSyntax&)node,false); 
}

void VisitorAbstractNodes::visit(const expression::IdentifierNameSyntax& node , bool callVirtualBase) {
  visit   ((expression::SimpleNameSyntax&)node,false); 
}

void VisitorAbstractNodes::visitEnd(const expression::IdentifierNameSyntax& node , bool callVirtualBase) {
  visitEnd   ((expression::SimpleNameSyntax&)node,false); 
}

void VisitorAbstractNodes::visit(const expression::ImplicitArrayCreationExpressionSyntax& node , bool callVirtualBase) {
  visit   ((expression::ExpressionSyntax&)node,false); 
}

void VisitorAbstractNodes::visitEnd(const expression::ImplicitArrayCreationExpressionSyntax& node , bool callVirtualBase) {
  visitEnd   ((expression::ExpressionSyntax&)node,false); 
}

void VisitorAbstractNodes::visit(const expression::ImplicitElementAccessSyntax& node , bool callVirtualBase) {
  visit   ((expression::ExpressionSyntax&)node,false); 
}

void VisitorAbstractNodes::visitEnd(const expression::ImplicitElementAccessSyntax& node , bool callVirtualBase) {
  visitEnd   ((expression::ExpressionSyntax&)node,false); 
}

void VisitorAbstractNodes::visit(const expression::ImplicitStackAllocArrayCreationExpressionSyntax& node , bool callVirtualBase) {
  visit   ((expression::ExpressionSyntax&)node,false); 
}

void VisitorAbstractNodes::visitEnd(const expression::ImplicitStackAllocArrayCreationExpressionSyntax& node , bool callVirtualBase) {
  visitEnd   ((expression::ExpressionSyntax&)node,false); 
}

void VisitorAbstractNodes::visit(const expression::InitializerExpressionSyntax& node , bool callVirtualBase) {
  visit   ((expression::ExpressionSyntax&)node,false); 
}

void VisitorAbstractNodes::visitEnd(const expression::InitializerExpressionSyntax& node , bool callVirtualBase) {
  visitEnd   ((expression::ExpressionSyntax&)node,false); 
}

void VisitorAbstractNodes::visit(const expression::InstanceExpressionSyntax& node , bool callVirtualBase) {
  visit   ((expression::ExpressionSyntax&)node,false); 
}

void VisitorAbstractNodes::visitEnd(const expression::InstanceExpressionSyntax& node , bool callVirtualBase) {
  visitEnd   ((expression::ExpressionSyntax&)node,false); 
}

void VisitorAbstractNodes::visit(const expression::InterpolatedStringExpressionSyntax& node , bool callVirtualBase) {
  visit   ((expression::ExpressionSyntax&)node,false); 
}

void VisitorAbstractNodes::visitEnd(const expression::InterpolatedStringExpressionSyntax& node , bool callVirtualBase) {
  visitEnd   ((expression::ExpressionSyntax&)node,false); 
}

void VisitorAbstractNodes::visit(const expression::InvocationExpressionSyntax& node , bool callVirtualBase) {
  visit   ((expression::ExpressionSyntax&)node,false); 
}

void VisitorAbstractNodes::visitEnd(const expression::InvocationExpressionSyntax& node , bool callVirtualBase) {
  visitEnd   ((expression::ExpressionSyntax&)node,false); 
}

void VisitorAbstractNodes::visit(const expression::IsPatternExpressionSyntax& node , bool callVirtualBase) {
  visit   ((expression::ExpressionSyntax&)node,false); 
}

void VisitorAbstractNodes::visitEnd(const expression::IsPatternExpressionSyntax& node , bool callVirtualBase) {
  visitEnd   ((expression::ExpressionSyntax&)node,false); 
}

void VisitorAbstractNodes::visit(const expression::LambdaExpressionSyntax& node , bool callVirtualBase) {
  visit   ((expression::AnonymousFunctionExpressionSyntax&)node,false); 
}

void VisitorAbstractNodes::visitEnd(const expression::LambdaExpressionSyntax& node , bool callVirtualBase) {
  visitEnd   ((expression::AnonymousFunctionExpressionSyntax&)node,false); 
}

void VisitorAbstractNodes::visit(const expression::LiteralExpressionSyntax& node , bool callVirtualBase) {
  visit   ((expression::ExpressionSyntax&)node,false); 
}

void VisitorAbstractNodes::visitEnd(const expression::LiteralExpressionSyntax& node , bool callVirtualBase) {
  visitEnd   ((expression::ExpressionSyntax&)node,false); 
}

void VisitorAbstractNodes::visit(const expression::MakeRefExpressionSyntax& node , bool callVirtualBase) {
  visit   ((expression::ExpressionSyntax&)node,false); 
}

void VisitorAbstractNodes::visitEnd(const expression::MakeRefExpressionSyntax& node , bool callVirtualBase) {
  visitEnd   ((expression::ExpressionSyntax&)node,false); 
}

void VisitorAbstractNodes::visit(const expression::MemberAccessExpressionSyntax& node , bool callVirtualBase) {
  visit   ((expression::ExpressionSyntax&)node,false); 
}

void VisitorAbstractNodes::visitEnd(const expression::MemberAccessExpressionSyntax& node , bool callVirtualBase) {
  visitEnd   ((expression::ExpressionSyntax&)node,false); 
}

void VisitorAbstractNodes::visit(const expression::MemberBindingExpressionSyntax& node , bool callVirtualBase) {
  visit   ((expression::ExpressionSyntax&)node,false); 
}

void VisitorAbstractNodes::visitEnd(const expression::MemberBindingExpressionSyntax& node , bool callVirtualBase) {
  visitEnd   ((expression::ExpressionSyntax&)node,false); 
}

void VisitorAbstractNodes::visit(const expression::NameSyntax& node , bool callVirtualBase) {
  visit   ((expression::TypeSyntax&)node,false); 
}

void VisitorAbstractNodes::visitEnd(const expression::NameSyntax& node , bool callVirtualBase) {
  visitEnd   ((expression::TypeSyntax&)node,false); 
}

void VisitorAbstractNodes::visit(const expression::NullableTypeSyntax& node , bool callVirtualBase) {
  visit   ((expression::TypeSyntax&)node,false); 
}

void VisitorAbstractNodes::visitEnd(const expression::NullableTypeSyntax& node , bool callVirtualBase) {
  visitEnd   ((expression::TypeSyntax&)node,false); 
}

void VisitorAbstractNodes::visit(const expression::ObjectCreationExpressionSyntax& node , bool callVirtualBase) {
  visit   ((expression::ExpressionSyntax&)node,false); 
}

void VisitorAbstractNodes::visitEnd(const expression::ObjectCreationExpressionSyntax& node , bool callVirtualBase) {
  visitEnd   ((expression::ExpressionSyntax&)node,false); 
}

void VisitorAbstractNodes::visit(const expression::OmittedArraySizeExpressionSyntax& node , bool callVirtualBase) {
  visit   ((expression::ExpressionSyntax&)node,false); 
}

void VisitorAbstractNodes::visitEnd(const expression::OmittedArraySizeExpressionSyntax& node , bool callVirtualBase) {
  visitEnd   ((expression::ExpressionSyntax&)node,false); 
}

void VisitorAbstractNodes::visit(const expression::OmittedTypeArgumentSyntax& node , bool callVirtualBase) {
  visit   ((expression::TypeSyntax&)node,false); 
}

void VisitorAbstractNodes::visitEnd(const expression::OmittedTypeArgumentSyntax& node , bool callVirtualBase) {
  visitEnd   ((expression::TypeSyntax&)node,false); 
}

void VisitorAbstractNodes::visit(const expression::ParenthesizedExpressionSyntax& node , bool callVirtualBase) {
  visit   ((expression::ExpressionSyntax&)node,false); 
}

void VisitorAbstractNodes::visitEnd(const expression::ParenthesizedExpressionSyntax& node , bool callVirtualBase) {
  visitEnd   ((expression::ExpressionSyntax&)node,false); 
}

void VisitorAbstractNodes::visit(const expression::ParenthesizedLambdaExpressionSyntax& node , bool callVirtualBase) {
  visit   ((expression::LambdaExpressionSyntax&)node,false); 
}

void VisitorAbstractNodes::visitEnd(const expression::ParenthesizedLambdaExpressionSyntax& node , bool callVirtualBase) {
  visitEnd   ((expression::LambdaExpressionSyntax&)node,false); 
}

void VisitorAbstractNodes::visit(const expression::PointerTypeSyntax& node , bool callVirtualBase) {
  visit   ((expression::TypeSyntax&)node,false); 
}

void VisitorAbstractNodes::visitEnd(const expression::PointerTypeSyntax& node , bool callVirtualBase) {
  visitEnd   ((expression::TypeSyntax&)node,false); 
}

void VisitorAbstractNodes::visit(const expression::PostfixUnaryExpressionSyntax& node , bool callVirtualBase) {
  visit   ((expression::ExpressionSyntax&)node,false); 
}

void VisitorAbstractNodes::visitEnd(const expression::PostfixUnaryExpressionSyntax& node , bool callVirtualBase) {
  visitEnd   ((expression::ExpressionSyntax&)node,false); 
}

void VisitorAbstractNodes::visit(const expression::PredefinedTypeSyntax& node , bool callVirtualBase) {
  visit   ((expression::TypeSyntax&)node,false); 
}

void VisitorAbstractNodes::visitEnd(const expression::PredefinedTypeSyntax& node , bool callVirtualBase) {
  visitEnd   ((expression::TypeSyntax&)node,false); 
}

void VisitorAbstractNodes::visit(const expression::PrefixUnaryExpressionSyntax& node , bool callVirtualBase) {
  visit   ((expression::ExpressionSyntax&)node,false); 
}

void VisitorAbstractNodes::visitEnd(const expression::PrefixUnaryExpressionSyntax& node , bool callVirtualBase) {
  visitEnd   ((expression::ExpressionSyntax&)node,false); 
}

void VisitorAbstractNodes::visit(const expression::QualifiedNameSyntax& node , bool callVirtualBase) {
  visit   ((expression::NameSyntax&)node,false); 
}

void VisitorAbstractNodes::visitEnd(const expression::QualifiedNameSyntax& node , bool callVirtualBase) {
  visitEnd   ((expression::NameSyntax&)node,false); 
}

void VisitorAbstractNodes::visit(const expression::QueryExpressionSyntax& node , bool callVirtualBase) {
  visit   ((expression::ExpressionSyntax&)node,false); 
}

void VisitorAbstractNodes::visitEnd(const expression::QueryExpressionSyntax& node , bool callVirtualBase) {
  visitEnd   ((expression::ExpressionSyntax&)node,false); 
}

void VisitorAbstractNodes::visit(const expression::RangeExpressionSyntax& node , bool callVirtualBase) {
  visit   ((expression::ExpressionSyntax&)node,false); 
}

void VisitorAbstractNodes::visitEnd(const expression::RangeExpressionSyntax& node , bool callVirtualBase) {
  visitEnd   ((expression::ExpressionSyntax&)node,false); 
}

void VisitorAbstractNodes::visit(const expression::RefExpressionSyntax& node , bool callVirtualBase) {
  visit   ((expression::ExpressionSyntax&)node,false); 
}

void VisitorAbstractNodes::visitEnd(const expression::RefExpressionSyntax& node , bool callVirtualBase) {
  visitEnd   ((expression::ExpressionSyntax&)node,false); 
}

void VisitorAbstractNodes::visit(const expression::RefTypeExpressionSyntax& node , bool callVirtualBase) {
  visit   ((expression::ExpressionSyntax&)node,false); 
}

void VisitorAbstractNodes::visitEnd(const expression::RefTypeExpressionSyntax& node , bool callVirtualBase) {
  visitEnd   ((expression::ExpressionSyntax&)node,false); 
}

void VisitorAbstractNodes::visit(const expression::RefTypeSyntax& node , bool callVirtualBase) {
  visit   ((expression::TypeSyntax&)node,false); 
}

void VisitorAbstractNodes::visitEnd(const expression::RefTypeSyntax& node , bool callVirtualBase) {
  visitEnd   ((expression::TypeSyntax&)node,false); 
}

void VisitorAbstractNodes::visit(const expression::RefValueExpressionSyntax& node , bool callVirtualBase) {
  visit   ((expression::ExpressionSyntax&)node,false); 
}

void VisitorAbstractNodes::visitEnd(const expression::RefValueExpressionSyntax& node , bool callVirtualBase) {
  visitEnd   ((expression::ExpressionSyntax&)node,false); 
}

void VisitorAbstractNodes::visit(const expression::SimpleLambdaExpressionSyntax& node , bool callVirtualBase) {
  visit   ((expression::LambdaExpressionSyntax&)node,false); 
}

void VisitorAbstractNodes::visitEnd(const expression::SimpleLambdaExpressionSyntax& node , bool callVirtualBase) {
  visitEnd   ((expression::LambdaExpressionSyntax&)node,false); 
}

void VisitorAbstractNodes::visit(const expression::SimpleNameSyntax& node , bool callVirtualBase) {
  visit   ((expression::NameSyntax&)node,false); 
}

void VisitorAbstractNodes::visitEnd(const expression::SimpleNameSyntax& node , bool callVirtualBase) {
  visitEnd   ((expression::NameSyntax&)node,false); 
}

void VisitorAbstractNodes::visit(const expression::SizeOfExpressionSyntax& node , bool callVirtualBase) {
  visit   ((expression::ExpressionSyntax&)node,false); 
}

void VisitorAbstractNodes::visitEnd(const expression::SizeOfExpressionSyntax& node , bool callVirtualBase) {
  visitEnd   ((expression::ExpressionSyntax&)node,false); 
}

void VisitorAbstractNodes::visit(const expression::StackAllocArrayCreationExpressionSyntax& node , bool callVirtualBase) {
  visit   ((expression::ExpressionSyntax&)node,false); 
}

void VisitorAbstractNodes::visitEnd(const expression::StackAllocArrayCreationExpressionSyntax& node , bool callVirtualBase) {
  visitEnd   ((expression::ExpressionSyntax&)node,false); 
}

void VisitorAbstractNodes::visit(const expression::SwitchExpressionSyntax& node , bool callVirtualBase) {
  visit   ((expression::ExpressionSyntax&)node,false); 
}

void VisitorAbstractNodes::visitEnd(const expression::SwitchExpressionSyntax& node , bool callVirtualBase) {
  visitEnd   ((expression::ExpressionSyntax&)node,false); 
}

void VisitorAbstractNodes::visit(const expression::ThisExpressionSyntax& node , bool callVirtualBase) {
  visit   ((expression::InstanceExpressionSyntax&)node,false); 
}

void VisitorAbstractNodes::visitEnd(const expression::ThisExpressionSyntax& node , bool callVirtualBase) {
  visitEnd   ((expression::InstanceExpressionSyntax&)node,false); 
}

void VisitorAbstractNodes::visit(const expression::ThrowExpressionSyntax& node , bool callVirtualBase) {
  visit   ((expression::ExpressionSyntax&)node,false); 
}

void VisitorAbstractNodes::visitEnd(const expression::ThrowExpressionSyntax& node , bool callVirtualBase) {
  visitEnd   ((expression::ExpressionSyntax&)node,false); 
}

void VisitorAbstractNodes::visit(const expression::TupleExpressionSyntax& node , bool callVirtualBase) {
  visit   ((expression::ExpressionSyntax&)node,false); 
}

void VisitorAbstractNodes::visitEnd(const expression::TupleExpressionSyntax& node , bool callVirtualBase) {
  visitEnd   ((expression::ExpressionSyntax&)node,false); 
}

void VisitorAbstractNodes::visit(const expression::TupleTypeSyntax& node , bool callVirtualBase) {
  visit   ((expression::TypeSyntax&)node,false); 
}

void VisitorAbstractNodes::visitEnd(const expression::TupleTypeSyntax& node , bool callVirtualBase) {
  visitEnd   ((expression::TypeSyntax&)node,false); 
}

void VisitorAbstractNodes::visit(const expression::TypeOfExpressionSyntax& node , bool callVirtualBase) {
  visit   ((expression::ExpressionSyntax&)node,false); 
}

void VisitorAbstractNodes::visitEnd(const expression::TypeOfExpressionSyntax& node , bool callVirtualBase) {
  visitEnd   ((expression::ExpressionSyntax&)node,false); 
}

void VisitorAbstractNodes::visit(const expression::TypeSyntax& node , bool callVirtualBase) {
  visit   ((expression::ExpressionSyntax&)node,false); 
}

void VisitorAbstractNodes::visitEnd(const expression::TypeSyntax& node , bool callVirtualBase) {
  visitEnd   ((expression::ExpressionSyntax&)node,false); 
}

void VisitorAbstractNodes::visit(const statement::BlockSyntax& node , bool callVirtualBase) {
  visit   ((statement::StatementSyntax&)node,false); 
}

void VisitorAbstractNodes::visitEnd(const statement::BlockSyntax& node , bool callVirtualBase) {
  visitEnd   ((statement::StatementSyntax&)node,false); 
}

void VisitorAbstractNodes::visit(const statement::BreakStatementSyntax& node , bool callVirtualBase) {
  visit   ((statement::StatementSyntax&)node,false); 
}

void VisitorAbstractNodes::visitEnd(const statement::BreakStatementSyntax& node , bool callVirtualBase) {
  visitEnd   ((statement::StatementSyntax&)node,false); 
}

void VisitorAbstractNodes::visit(const statement::CheckedStatementSyntax& node , bool callVirtualBase) {
  visit   ((statement::StatementSyntax&)node,false); 
}

void VisitorAbstractNodes::visitEnd(const statement::CheckedStatementSyntax& node , bool callVirtualBase) {
  visitEnd   ((statement::StatementSyntax&)node,false); 
}

void VisitorAbstractNodes::visit(const statement::CommonForEachStatementSyntax& node , bool callVirtualBase) {
  visit   ((statement::StatementSyntax&)node,false); 
}

void VisitorAbstractNodes::visitEnd(const statement::CommonForEachStatementSyntax& node , bool callVirtualBase) {
  visitEnd   ((statement::StatementSyntax&)node,false); 
}

void VisitorAbstractNodes::visit(const statement::ContinueStatementSyntax& node , bool callVirtualBase) {
  visit   ((statement::StatementSyntax&)node,false); 
}

void VisitorAbstractNodes::visitEnd(const statement::ContinueStatementSyntax& node , bool callVirtualBase) {
  visitEnd   ((statement::StatementSyntax&)node,false); 
}

void VisitorAbstractNodes::visit(const statement::DoStatementSyntax& node , bool callVirtualBase) {
  visit   ((statement::StatementSyntax&)node,false); 
}

void VisitorAbstractNodes::visitEnd(const statement::DoStatementSyntax& node , bool callVirtualBase) {
  visitEnd   ((statement::StatementSyntax&)node,false); 
}

void VisitorAbstractNodes::visit(const statement::EmptyStatementSyntax& node , bool callVirtualBase) {
  visit   ((statement::StatementSyntax&)node,false); 
}

void VisitorAbstractNodes::visitEnd(const statement::EmptyStatementSyntax& node , bool callVirtualBase) {
  visitEnd   ((statement::StatementSyntax&)node,false); 
}

void VisitorAbstractNodes::visit(const statement::ExpressionStatementSyntax& node , bool callVirtualBase) {
  visit   ((statement::StatementSyntax&)node,false); 
}

void VisitorAbstractNodes::visitEnd(const statement::ExpressionStatementSyntax& node , bool callVirtualBase) {
  visitEnd   ((statement::StatementSyntax&)node,false); 
}

void VisitorAbstractNodes::visit(const statement::FixedStatementSyntax& node , bool callVirtualBase) {
  visit   ((statement::StatementSyntax&)node,false); 
}

void VisitorAbstractNodes::visitEnd(const statement::FixedStatementSyntax& node , bool callVirtualBase) {
  visitEnd   ((statement::StatementSyntax&)node,false); 
}

void VisitorAbstractNodes::visit(const statement::ForEachStatementSyntax& node , bool callVirtualBase) {
  visit   ((statement::CommonForEachStatementSyntax&)node,false); 
}

void VisitorAbstractNodes::visitEnd(const statement::ForEachStatementSyntax& node , bool callVirtualBase) {
  visitEnd   ((statement::CommonForEachStatementSyntax&)node,false); 
}

void VisitorAbstractNodes::visit(const statement::ForEachVariableStatementSyntax& node , bool callVirtualBase) {
  visit   ((statement::CommonForEachStatementSyntax&)node,false); 
}

void VisitorAbstractNodes::visitEnd(const statement::ForEachVariableStatementSyntax& node , bool callVirtualBase) {
  visitEnd   ((statement::CommonForEachStatementSyntax&)node,false); 
}

void VisitorAbstractNodes::visit(const statement::ForStatementSyntax& node , bool callVirtualBase) {
  visit   ((statement::StatementSyntax&)node,false); 
}

void VisitorAbstractNodes::visitEnd(const statement::ForStatementSyntax& node , bool callVirtualBase) {
  visitEnd   ((statement::StatementSyntax&)node,false); 
}

void VisitorAbstractNodes::visit(const statement::GotoStatementSyntax& node , bool callVirtualBase) {
  visit   ((statement::StatementSyntax&)node,false); 
}

void VisitorAbstractNodes::visitEnd(const statement::GotoStatementSyntax& node , bool callVirtualBase) {
  visitEnd   ((statement::StatementSyntax&)node,false); 
}

void VisitorAbstractNodes::visit(const statement::IfStatementSyntax& node , bool callVirtualBase) {
  visit   ((statement::StatementSyntax&)node,false); 
}

void VisitorAbstractNodes::visitEnd(const statement::IfStatementSyntax& node , bool callVirtualBase) {
  visitEnd   ((statement::StatementSyntax&)node,false); 
}

void VisitorAbstractNodes::visit(const statement::LabeledStatementSyntax& node , bool callVirtualBase) {
  visit   ((statement::StatementSyntax&)node,false); 
}

void VisitorAbstractNodes::visitEnd(const statement::LabeledStatementSyntax& node , bool callVirtualBase) {
  visitEnd   ((statement::StatementSyntax&)node,false); 
}

void VisitorAbstractNodes::visit(const statement::LocalDeclarationStatementSyntax& node , bool callVirtualBase) {
  visit   ((statement::StatementSyntax&)node,false); 
}

void VisitorAbstractNodes::visitEnd(const statement::LocalDeclarationStatementSyntax& node , bool callVirtualBase) {
  visitEnd   ((statement::StatementSyntax&)node,false); 
}

void VisitorAbstractNodes::visit(const statement::LocalFunctionStatementSyntax& node , bool callVirtualBase) {
  visit   ((statement::StatementSyntax&)node,false); 
}

void VisitorAbstractNodes::visitEnd(const statement::LocalFunctionStatementSyntax& node , bool callVirtualBase) {
  visitEnd   ((statement::StatementSyntax&)node,false); 
}

void VisitorAbstractNodes::visit(const statement::LockStatementSyntax& node , bool callVirtualBase) {
  visit   ((statement::StatementSyntax&)node,false); 
}

void VisitorAbstractNodes::visitEnd(const statement::LockStatementSyntax& node , bool callVirtualBase) {
  visitEnd   ((statement::StatementSyntax&)node,false); 
}

void VisitorAbstractNodes::visit(const statement::ReturnStatementSyntax& node , bool callVirtualBase) {
  visit   ((statement::StatementSyntax&)node,false); 
}

void VisitorAbstractNodes::visitEnd(const statement::ReturnStatementSyntax& node , bool callVirtualBase) {
  visitEnd   ((statement::StatementSyntax&)node,false); 
}

void VisitorAbstractNodes::visit(const statement::StatementSyntax& node , bool callVirtualBase) {
  visit   ((base::Positioned&)node,false); 
}

void VisitorAbstractNodes::visitEnd(const statement::StatementSyntax& node , bool callVirtualBase) {
  visitEnd   ((base::Positioned&)node,false); 
}

void VisitorAbstractNodes::visit(const statement::SwitchStatementSyntax& node , bool callVirtualBase) {
  visit   ((statement::StatementSyntax&)node,false); 
}

void VisitorAbstractNodes::visitEnd(const statement::SwitchStatementSyntax& node , bool callVirtualBase) {
  visitEnd   ((statement::StatementSyntax&)node,false); 
}

void VisitorAbstractNodes::visit(const statement::ThrowStatementSyntax& node , bool callVirtualBase) {
  visit   ((statement::StatementSyntax&)node,false); 
}

void VisitorAbstractNodes::visitEnd(const statement::ThrowStatementSyntax& node , bool callVirtualBase) {
  visitEnd   ((statement::StatementSyntax&)node,false); 
}

void VisitorAbstractNodes::visit(const statement::TryStatementSyntax& node , bool callVirtualBase) {
  visit   ((statement::StatementSyntax&)node,false); 
}

void VisitorAbstractNodes::visitEnd(const statement::TryStatementSyntax& node , bool callVirtualBase) {
  visitEnd   ((statement::StatementSyntax&)node,false); 
}

void VisitorAbstractNodes::visit(const statement::UnsafeStatementSyntax& node , bool callVirtualBase) {
  visit   ((statement::StatementSyntax&)node,false); 
}

void VisitorAbstractNodes::visitEnd(const statement::UnsafeStatementSyntax& node , bool callVirtualBase) {
  visitEnd   ((statement::StatementSyntax&)node,false); 
}

void VisitorAbstractNodes::visit(const statement::UsingStatementSyntax& node , bool callVirtualBase) {
  visit   ((statement::StatementSyntax&)node,false); 
}

void VisitorAbstractNodes::visitEnd(const statement::UsingStatementSyntax& node , bool callVirtualBase) {
  visitEnd   ((statement::StatementSyntax&)node,false); 
}

void VisitorAbstractNodes::visit(const statement::WhileStatementSyntax& node , bool callVirtualBase) {
  visit   ((statement::StatementSyntax&)node,false); 
}

void VisitorAbstractNodes::visitEnd(const statement::WhileStatementSyntax& node , bool callVirtualBase) {
  visitEnd   ((statement::StatementSyntax&)node,false); 
}

void VisitorAbstractNodes::visit(const statement::YieldStatementSyntax& node , bool callVirtualBase) {
  visit   ((statement::StatementSyntax&)node,false); 
}

void VisitorAbstractNodes::visitEnd(const statement::YieldStatementSyntax& node , bool callVirtualBase) {
  visitEnd   ((statement::StatementSyntax&)node,false); 
}

void VisitorAbstractNodes::visit(const structure::AccessorDeclarationSyntax& node , bool callVirtualBase) {
  visit   ((base::Positioned&)node,false); 
}

void VisitorAbstractNodes::visitEnd(const structure::AccessorDeclarationSyntax& node , bool callVirtualBase) {
  visitEnd   ((base::Positioned&)node,false); 
}

void VisitorAbstractNodes::visit(const structure::AccessorListSyntax& node , bool callVirtualBase) {
  visit   ((base::Positioned&)node,false); 
}

void VisitorAbstractNodes::visitEnd(const structure::AccessorListSyntax& node , bool callVirtualBase) {
  visitEnd   ((base::Positioned&)node,false); 
}

void VisitorAbstractNodes::visit(const structure::AnonymousObjectMemberDeclaratorSyntax& node , bool callVirtualBase) {
  visit   ((base::Positioned&)node,false); 
}

void VisitorAbstractNodes::visitEnd(const structure::AnonymousObjectMemberDeclaratorSyntax& node , bool callVirtualBase) {
  visitEnd   ((base::Positioned&)node,false); 
}

void VisitorAbstractNodes::visit(const structure::ArgumentListSyntax& node , bool callVirtualBase) {
  visit   ((structure::BaseArgumentListSyntax&)node,false); 
}

void VisitorAbstractNodes::visitEnd(const structure::ArgumentListSyntax& node , bool callVirtualBase) {
  visitEnd   ((structure::BaseArgumentListSyntax&)node,false); 
}

void VisitorAbstractNodes::visit(const structure::ArgumentSyntax& node , bool callVirtualBase) {
  visit   ((base::Positioned&)node,false); 
}

void VisitorAbstractNodes::visitEnd(const structure::ArgumentSyntax& node , bool callVirtualBase) {
  visitEnd   ((base::Positioned&)node,false); 
}

void VisitorAbstractNodes::visit(const structure::ArrayRankSpecifierSyntax& node , bool callVirtualBase) {
  visit   ((base::Positioned&)node,false); 
}

void VisitorAbstractNodes::visitEnd(const structure::ArrayRankSpecifierSyntax& node , bool callVirtualBase) {
  visitEnd   ((base::Positioned&)node,false); 
}

void VisitorAbstractNodes::visit(const structure::ArrowExpressionClauseSyntax& node , bool callVirtualBase) {
  visit   ((base::Positioned&)node,false); 
}

void VisitorAbstractNodes::visitEnd(const structure::ArrowExpressionClauseSyntax& node , bool callVirtualBase) {
  visitEnd   ((base::Positioned&)node,false); 
}

void VisitorAbstractNodes::visit(const structure::AttributeArgumentListSyntax& node , bool callVirtualBase) {
  visit   ((base::Positioned&)node,false); 
}

void VisitorAbstractNodes::visitEnd(const structure::AttributeArgumentListSyntax& node , bool callVirtualBase) {
  visitEnd   ((base::Positioned&)node,false); 
}

void VisitorAbstractNodes::visit(const structure::AttributeArgumentSyntax& node , bool callVirtualBase) {
  visit   ((base::Positioned&)node,false); 
}

void VisitorAbstractNodes::visitEnd(const structure::AttributeArgumentSyntax& node , bool callVirtualBase) {
  visitEnd   ((base::Positioned&)node,false); 
}

void VisitorAbstractNodes::visit(const structure::AttributeListSyntax& node , bool callVirtualBase) {
  visit   ((base::Positioned&)node,false); 
}

void VisitorAbstractNodes::visitEnd(const structure::AttributeListSyntax& node , bool callVirtualBase) {
  visitEnd   ((base::Positioned&)node,false); 
}

void VisitorAbstractNodes::visit(const structure::AttributeSyntax& node , bool callVirtualBase) {
  visit   ((base::Positioned&)node,false); 
}

void VisitorAbstractNodes::visitEnd(const structure::AttributeSyntax& node , bool callVirtualBase) {
  visitEnd   ((base::Positioned&)node,false); 
}

void VisitorAbstractNodes::visit(const structure::AttributeTargetSpecifierSyntax& node , bool callVirtualBase) {
  visit   ((base::Positioned&)node,false); 
}

void VisitorAbstractNodes::visitEnd(const structure::AttributeTargetSpecifierSyntax& node , bool callVirtualBase) {
  visitEnd   ((base::Positioned&)node,false); 
}

void VisitorAbstractNodes::visit(const structure::BaseArgumentListSyntax& node , bool callVirtualBase) {
  visit   ((base::Positioned&)node,false); 
}

void VisitorAbstractNodes::visitEnd(const structure::BaseArgumentListSyntax& node , bool callVirtualBase) {
  visitEnd   ((base::Positioned&)node,false); 
}

void VisitorAbstractNodes::visit(const structure::BaseCrefParameterListSyntax& node , bool callVirtualBase) {
  visit   ((base::Positioned&)node,false); 
}

void VisitorAbstractNodes::visitEnd(const structure::BaseCrefParameterListSyntax& node , bool callVirtualBase) {
  visitEnd   ((base::Positioned&)node,false); 
}

void VisitorAbstractNodes::visit(const structure::BaseFieldDeclarationSyntax& node , bool callVirtualBase) {
  visit   ((structure::MemberDeclarationSyntax&)node,false); 
}

void VisitorAbstractNodes::visitEnd(const structure::BaseFieldDeclarationSyntax& node , bool callVirtualBase) {
  visitEnd   ((structure::MemberDeclarationSyntax&)node,false); 
}

void VisitorAbstractNodes::visit(const structure::BaseListSyntax& node , bool callVirtualBase) {
  visit   ((base::Positioned&)node,false); 
}

void VisitorAbstractNodes::visitEnd(const structure::BaseListSyntax& node , bool callVirtualBase) {
  visitEnd   ((base::Positioned&)node,false); 
}

void VisitorAbstractNodes::visit(const structure::BaseMethodDeclarationSyntax& node , bool callVirtualBase) {
  visit   ((structure::MemberDeclarationSyntax&)node,false); 
}

void VisitorAbstractNodes::visitEnd(const structure::BaseMethodDeclarationSyntax& node , bool callVirtualBase) {
  visitEnd   ((structure::MemberDeclarationSyntax&)node,false); 
}

void VisitorAbstractNodes::visit(const structure::BaseParameterListSyntax& node , bool callVirtualBase) {
  visit   ((base::Positioned&)node,false); 
}

void VisitorAbstractNodes::visitEnd(const structure::BaseParameterListSyntax& node , bool callVirtualBase) {
  visitEnd   ((base::Positioned&)node,false); 
}

void VisitorAbstractNodes::visit(const structure::BasePropertyDeclarationSyntax& node , bool callVirtualBase) {
  visit   ((structure::MemberDeclarationSyntax&)node,false); 
}

void VisitorAbstractNodes::visitEnd(const structure::BasePropertyDeclarationSyntax& node , bool callVirtualBase) {
  visitEnd   ((structure::MemberDeclarationSyntax&)node,false); 
}

void VisitorAbstractNodes::visit(const structure::BaseTypeDeclarationSyntax& node , bool callVirtualBase) {
  visit   ((structure::MemberDeclarationSyntax&)node,false); 
}

void VisitorAbstractNodes::visitEnd(const structure::BaseTypeDeclarationSyntax& node , bool callVirtualBase) {
  visitEnd   ((structure::MemberDeclarationSyntax&)node,false); 
}

void VisitorAbstractNodes::visit(const structure::BaseTypeSyntax& node , bool callVirtualBase) {
  visit   ((base::Positioned&)node,false); 
}

void VisitorAbstractNodes::visitEnd(const structure::BaseTypeSyntax& node , bool callVirtualBase) {
  visitEnd   ((base::Positioned&)node,false); 
}

void VisitorAbstractNodes::visit(const structure::BracketedArgumentListSyntax& node , bool callVirtualBase) {
  visit   ((structure::BaseArgumentListSyntax&)node,false); 
}

void VisitorAbstractNodes::visitEnd(const structure::BracketedArgumentListSyntax& node , bool callVirtualBase) {
  visitEnd   ((structure::BaseArgumentListSyntax&)node,false); 
}

void VisitorAbstractNodes::visit(const structure::BracketedParameterListSyntax& node , bool callVirtualBase) {
  visit   ((structure::BaseParameterListSyntax&)node,false); 
}

void VisitorAbstractNodes::visitEnd(const structure::BracketedParameterListSyntax& node , bool callVirtualBase) {
  visitEnd   ((structure::BaseParameterListSyntax&)node,false); 
}

void VisitorAbstractNodes::visit(const structure::CasePatternSwitchLabelSyntax& node , bool callVirtualBase) {
  visit   ((structure::SwitchLabelSyntax&)node,false); 
}

void VisitorAbstractNodes::visitEnd(const structure::CasePatternSwitchLabelSyntax& node , bool callVirtualBase) {
  visitEnd   ((structure::SwitchLabelSyntax&)node,false); 
}

void VisitorAbstractNodes::visit(const structure::CaseSwitchLabelSyntax& node , bool callVirtualBase) {
  visit   ((structure::SwitchLabelSyntax&)node,false); 
}

void VisitorAbstractNodes::visitEnd(const structure::CaseSwitchLabelSyntax& node , bool callVirtualBase) {
  visitEnd   ((structure::SwitchLabelSyntax&)node,false); 
}

void VisitorAbstractNodes::visit(const structure::CatchClauseSyntax& node , bool callVirtualBase) {
  visit   ((base::Positioned&)node,false); 
}

void VisitorAbstractNodes::visitEnd(const structure::CatchClauseSyntax& node , bool callVirtualBase) {
  visitEnd   ((base::Positioned&)node,false); 
}

void VisitorAbstractNodes::visit(const structure::CatchDeclarationSyntax& node , bool callVirtualBase) {
  visit   ((base::Positioned&)node,false); 
}

void VisitorAbstractNodes::visitEnd(const structure::CatchDeclarationSyntax& node , bool callVirtualBase) {
  visitEnd   ((base::Positioned&)node,false); 
}

void VisitorAbstractNodes::visit(const structure::CatchFilterClauseSyntax& node , bool callVirtualBase) {
  visit   ((base::Positioned&)node,false); 
}

void VisitorAbstractNodes::visitEnd(const structure::CatchFilterClauseSyntax& node , bool callVirtualBase) {
  visitEnd   ((base::Positioned&)node,false); 
}

void VisitorAbstractNodes::visit(const structure::ClassDeclarationSyntax& node , bool callVirtualBase) {
  visit   ((structure::TypeDeclarationSyntax&)node,false); 
}

void VisitorAbstractNodes::visitEnd(const structure::ClassDeclarationSyntax& node , bool callVirtualBase) {
  visitEnd   ((structure::TypeDeclarationSyntax&)node,false); 
}

void VisitorAbstractNodes::visit(const structure::ClassOrStructConstraintSyntax& node , bool callVirtualBase) {
  visit   ((structure::TypeParameterConstraintSyntax&)node,false); 
}

void VisitorAbstractNodes::visitEnd(const structure::ClassOrStructConstraintSyntax& node , bool callVirtualBase) {
  visitEnd   ((structure::TypeParameterConstraintSyntax&)node,false); 
}

void VisitorAbstractNodes::visit(const structure::CompilationUnitSyntax& node , bool callVirtualBase) {
  visit   ((base::Positioned&)node,false); 
}

void VisitorAbstractNodes::visitEnd(const structure::CompilationUnitSyntax& node , bool callVirtualBase) {
  visitEnd   ((base::Positioned&)node,false); 
}

void VisitorAbstractNodes::visit(const structure::ConstantPatternSyntax& node , bool callVirtualBase) {
  visit   ((structure::PatternSyntax&)node,false); 
}

void VisitorAbstractNodes::visitEnd(const structure::ConstantPatternSyntax& node , bool callVirtualBase) {
  visitEnd   ((structure::PatternSyntax&)node,false); 
}

void VisitorAbstractNodes::visit(const structure::ConstructorConstraintSyntax& node , bool callVirtualBase) {
  visit   ((structure::TypeParameterConstraintSyntax&)node,false); 
}

void VisitorAbstractNodes::visitEnd(const structure::ConstructorConstraintSyntax& node , bool callVirtualBase) {
  visitEnd   ((structure::TypeParameterConstraintSyntax&)node,false); 
}

void VisitorAbstractNodes::visit(const structure::ConstructorDeclarationSyntax& node , bool callVirtualBase) {
  visit   ((structure::BaseMethodDeclarationSyntax&)node,false); 
}

void VisitorAbstractNodes::visitEnd(const structure::ConstructorDeclarationSyntax& node , bool callVirtualBase) {
  visitEnd   ((structure::BaseMethodDeclarationSyntax&)node,false); 
}

void VisitorAbstractNodes::visit(const structure::ConstructorInitializerSyntax& node , bool callVirtualBase) {
  visit   ((base::Positioned&)node,false); 
}

void VisitorAbstractNodes::visitEnd(const structure::ConstructorInitializerSyntax& node , bool callVirtualBase) {
  visitEnd   ((base::Positioned&)node,false); 
}

void VisitorAbstractNodes::visit(const structure::ConversionOperatorDeclarationSyntax& node , bool callVirtualBase) {
  visit   ((structure::BaseMethodDeclarationSyntax&)node,false); 
}

void VisitorAbstractNodes::visitEnd(const structure::ConversionOperatorDeclarationSyntax& node , bool callVirtualBase) {
  visitEnd   ((structure::BaseMethodDeclarationSyntax&)node,false); 
}

void VisitorAbstractNodes::visit(const structure::ConversionOperatorMemberCrefSyntax& node , bool callVirtualBase) {
  visit   ((structure::MemberCrefSyntax&)node,false); 
}

void VisitorAbstractNodes::visitEnd(const structure::ConversionOperatorMemberCrefSyntax& node , bool callVirtualBase) {
  visitEnd   ((structure::MemberCrefSyntax&)node,false); 
}

void VisitorAbstractNodes::visit(const structure::CrefBracketedParameterListSyntax& node , bool callVirtualBase) {
  visit   ((structure::BaseCrefParameterListSyntax&)node,false); 
}

void VisitorAbstractNodes::visitEnd(const structure::CrefBracketedParameterListSyntax& node , bool callVirtualBase) {
  visitEnd   ((structure::BaseCrefParameterListSyntax&)node,false); 
}

void VisitorAbstractNodes::visit(const structure::CrefParameterListSyntax& node , bool callVirtualBase) {
  visit   ((structure::BaseCrefParameterListSyntax&)node,false); 
}

void VisitorAbstractNodes::visitEnd(const structure::CrefParameterListSyntax& node , bool callVirtualBase) {
  visitEnd   ((structure::BaseCrefParameterListSyntax&)node,false); 
}

void VisitorAbstractNodes::visit(const structure::CrefParameterSyntax& node , bool callVirtualBase) {
  visit   ((base::Positioned&)node,false); 
}

void VisitorAbstractNodes::visitEnd(const structure::CrefParameterSyntax& node , bool callVirtualBase) {
  visitEnd   ((base::Positioned&)node,false); 
}

void VisitorAbstractNodes::visit(const structure::CrefSyntax& node , bool callVirtualBase) {
  visit   ((base::Positioned&)node,false); 
}

void VisitorAbstractNodes::visitEnd(const structure::CrefSyntax& node , bool callVirtualBase) {
  visitEnd   ((base::Positioned&)node,false); 
}

void VisitorAbstractNodes::visit(const structure::DeclarationPatternSyntax& node , bool callVirtualBase) {
  visit   ((structure::PatternSyntax&)node,false); 
}

void VisitorAbstractNodes::visitEnd(const structure::DeclarationPatternSyntax& node , bool callVirtualBase) {
  visitEnd   ((structure::PatternSyntax&)node,false); 
}

void VisitorAbstractNodes::visit(const structure::DefaultSwitchLabelSyntax& node , bool callVirtualBase) {
  visit   ((structure::SwitchLabelSyntax&)node,false); 
}

void VisitorAbstractNodes::visitEnd(const structure::DefaultSwitchLabelSyntax& node , bool callVirtualBase) {
  visitEnd   ((structure::SwitchLabelSyntax&)node,false); 
}

void VisitorAbstractNodes::visit(const structure::DelegateDeclarationSyntax& node , bool callVirtualBase) {
  visit   ((structure::MemberDeclarationSyntax&)node,false); 
}

void VisitorAbstractNodes::visitEnd(const structure::DelegateDeclarationSyntax& node , bool callVirtualBase) {
  visitEnd   ((structure::MemberDeclarationSyntax&)node,false); 
}

void VisitorAbstractNodes::visit(const structure::DestructorDeclarationSyntax& node , bool callVirtualBase) {
  visit   ((structure::BaseMethodDeclarationSyntax&)node,false); 
}

void VisitorAbstractNodes::visitEnd(const structure::DestructorDeclarationSyntax& node , bool callVirtualBase) {
  visitEnd   ((structure::BaseMethodDeclarationSyntax&)node,false); 
}

void VisitorAbstractNodes::visit(const structure::DiscardDesignationSyntax& node , bool callVirtualBase) {
  visit   ((structure::VariableDesignationSyntax&)node,false); 
}

void VisitorAbstractNodes::visitEnd(const structure::DiscardDesignationSyntax& node , bool callVirtualBase) {
  visitEnd   ((structure::VariableDesignationSyntax&)node,false); 
}

void VisitorAbstractNodes::visit(const structure::DiscardPatternSyntax& node , bool callVirtualBase) {
  visit   ((structure::PatternSyntax&)node,false); 
}

void VisitorAbstractNodes::visitEnd(const structure::DiscardPatternSyntax& node , bool callVirtualBase) {
  visitEnd   ((structure::PatternSyntax&)node,false); 
}

void VisitorAbstractNodes::visit(const structure::ElseClauseSyntax& node , bool callVirtualBase) {
  visit   ((base::Positioned&)node,false); 
}

void VisitorAbstractNodes::visitEnd(const structure::ElseClauseSyntax& node , bool callVirtualBase) {
  visitEnd   ((base::Positioned&)node,false); 
}

void VisitorAbstractNodes::visit(const structure::EnumDeclarationSyntax& node , bool callVirtualBase) {
  visit   ((structure::BaseTypeDeclarationSyntax&)node,false); 
}

void VisitorAbstractNodes::visitEnd(const structure::EnumDeclarationSyntax& node , bool callVirtualBase) {
  visitEnd   ((structure::BaseTypeDeclarationSyntax&)node,false); 
}

void VisitorAbstractNodes::visit(const structure::EnumMemberDeclarationSyntax& node , bool callVirtualBase) {
  visit   ((structure::MemberDeclarationSyntax&)node,false); 
}

void VisitorAbstractNodes::visitEnd(const structure::EnumMemberDeclarationSyntax& node , bool callVirtualBase) {
  visitEnd   ((structure::MemberDeclarationSyntax&)node,false); 
}

void VisitorAbstractNodes::visit(const structure::EqualsValueClauseSyntax& node , bool callVirtualBase) {
  visit   ((base::Positioned&)node,false); 
}

void VisitorAbstractNodes::visitEnd(const structure::EqualsValueClauseSyntax& node , bool callVirtualBase) {
  visitEnd   ((base::Positioned&)node,false); 
}

void VisitorAbstractNodes::visit(const structure::EventDeclarationSyntax& node , bool callVirtualBase) {
  visit   ((structure::BasePropertyDeclarationSyntax&)node,false); 
}

void VisitorAbstractNodes::visitEnd(const structure::EventDeclarationSyntax& node , bool callVirtualBase) {
  visitEnd   ((structure::BasePropertyDeclarationSyntax&)node,false); 
}

void VisitorAbstractNodes::visit(const structure::EventFieldDeclarationSyntax& node , bool callVirtualBase) {
  visit   ((structure::BaseFieldDeclarationSyntax&)node,false); 
}

void VisitorAbstractNodes::visitEnd(const structure::EventFieldDeclarationSyntax& node , bool callVirtualBase) {
  visitEnd   ((structure::BaseFieldDeclarationSyntax&)node,false); 
}

void VisitorAbstractNodes::visit(const structure::ExplicitInterfaceSpecifierSyntax& node , bool callVirtualBase) {
  visit   ((base::Positioned&)node,false); 
}

void VisitorAbstractNodes::visitEnd(const structure::ExplicitInterfaceSpecifierSyntax& node , bool callVirtualBase) {
  visitEnd   ((base::Positioned&)node,false); 
}

void VisitorAbstractNodes::visit(const structure::ExternAliasDirectiveSyntax& node , bool callVirtualBase) {
  visit   ((base::Positioned&)node,false); 
}

void VisitorAbstractNodes::visitEnd(const structure::ExternAliasDirectiveSyntax& node , bool callVirtualBase) {
  visitEnd   ((base::Positioned&)node,false); 
}

void VisitorAbstractNodes::visit(const structure::FieldDeclarationSyntax& node , bool callVirtualBase) {
  visit   ((structure::BaseFieldDeclarationSyntax&)node,false); 
}

void VisitorAbstractNodes::visitEnd(const structure::FieldDeclarationSyntax& node , bool callVirtualBase) {
  visitEnd   ((structure::BaseFieldDeclarationSyntax&)node,false); 
}

void VisitorAbstractNodes::visit(const structure::FinallyClauseSyntax& node , bool callVirtualBase) {
  visit   ((base::Positioned&)node,false); 
}

void VisitorAbstractNodes::visitEnd(const structure::FinallyClauseSyntax& node , bool callVirtualBase) {
  visitEnd   ((base::Positioned&)node,false); 
}

void VisitorAbstractNodes::visit(const structure::FromClauseSyntax& node , bool callVirtualBase) {
  visit   ((structure::QueryClauseSyntax&)node,false); 
}

void VisitorAbstractNodes::visitEnd(const structure::FromClauseSyntax& node , bool callVirtualBase) {
  visitEnd   ((structure::QueryClauseSyntax&)node,false); 
}

void VisitorAbstractNodes::visit(const structure::GlobalStatementSyntax& node , bool callVirtualBase) {
  visit   ((structure::MemberDeclarationSyntax&)node,false); 
}

void VisitorAbstractNodes::visitEnd(const structure::GlobalStatementSyntax& node , bool callVirtualBase) {
  visitEnd   ((structure::MemberDeclarationSyntax&)node,false); 
}

void VisitorAbstractNodes::visit(const structure::GroupClauseSyntax& node , bool callVirtualBase) {
  visit   ((structure::SelectOrGroupClauseSyntax&)node,false); 
}

void VisitorAbstractNodes::visitEnd(const structure::GroupClauseSyntax& node , bool callVirtualBase) {
  visitEnd   ((structure::SelectOrGroupClauseSyntax&)node,false); 
}

void VisitorAbstractNodes::visit(const structure::IncompleteMemberSyntax& node , bool callVirtualBase) {
  visit   ((structure::MemberDeclarationSyntax&)node,false); 
}

void VisitorAbstractNodes::visitEnd(const structure::IncompleteMemberSyntax& node , bool callVirtualBase) {
  visitEnd   ((structure::MemberDeclarationSyntax&)node,false); 
}

void VisitorAbstractNodes::visit(const structure::IndexerDeclarationSyntax& node , bool callVirtualBase) {
  visit   ((structure::BasePropertyDeclarationSyntax&)node,false); 
}

void VisitorAbstractNodes::visitEnd(const structure::IndexerDeclarationSyntax& node , bool callVirtualBase) {
  visitEnd   ((structure::BasePropertyDeclarationSyntax&)node,false); 
}

void VisitorAbstractNodes::visit(const structure::IndexerMemberCrefSyntax& node , bool callVirtualBase) {
  visit   ((structure::MemberCrefSyntax&)node,false); 
}

void VisitorAbstractNodes::visitEnd(const structure::IndexerMemberCrefSyntax& node , bool callVirtualBase) {
  visitEnd   ((structure::MemberCrefSyntax&)node,false); 
}

void VisitorAbstractNodes::visit(const structure::InterfaceDeclarationSyntax& node , bool callVirtualBase) {
  visit   ((structure::TypeDeclarationSyntax&)node,false); 
}

void VisitorAbstractNodes::visitEnd(const structure::InterfaceDeclarationSyntax& node , bool callVirtualBase) {
  visitEnd   ((structure::TypeDeclarationSyntax&)node,false); 
}

void VisitorAbstractNodes::visit(const structure::InterpolatedStringContentSyntax& node , bool callVirtualBase) {
  visit   ((base::Positioned&)node,false); 
}

void VisitorAbstractNodes::visitEnd(const structure::InterpolatedStringContentSyntax& node , bool callVirtualBase) {
  visitEnd   ((base::Positioned&)node,false); 
}

void VisitorAbstractNodes::visit(const structure::InterpolatedStringTextSyntax& node , bool callVirtualBase) {
  visit   ((structure::InterpolatedStringContentSyntax&)node,false); 
}

void VisitorAbstractNodes::visitEnd(const structure::InterpolatedStringTextSyntax& node , bool callVirtualBase) {
  visitEnd   ((structure::InterpolatedStringContentSyntax&)node,false); 
}

void VisitorAbstractNodes::visit(const structure::InterpolationAlignmentClauseSyntax& node , bool callVirtualBase) {
  visit   ((base::Positioned&)node,false); 
}

void VisitorAbstractNodes::visitEnd(const structure::InterpolationAlignmentClauseSyntax& node , bool callVirtualBase) {
  visitEnd   ((base::Positioned&)node,false); 
}

void VisitorAbstractNodes::visit(const structure::InterpolationFormatClauseSyntax& node , bool callVirtualBase) {
  visit   ((base::Positioned&)node,false); 
}

void VisitorAbstractNodes::visitEnd(const structure::InterpolationFormatClauseSyntax& node , bool callVirtualBase) {
  visitEnd   ((base::Positioned&)node,false); 
}

void VisitorAbstractNodes::visit(const structure::InterpolationSyntax& node , bool callVirtualBase) {
  visit   ((structure::InterpolatedStringContentSyntax&)node,false); 
}

void VisitorAbstractNodes::visitEnd(const structure::InterpolationSyntax& node , bool callVirtualBase) {
  visitEnd   ((structure::InterpolatedStringContentSyntax&)node,false); 
}

void VisitorAbstractNodes::visit(const structure::JoinClauseSyntax& node , bool callVirtualBase) {
  visit   ((structure::QueryClauseSyntax&)node,false); 
}

void VisitorAbstractNodes::visitEnd(const structure::JoinClauseSyntax& node , bool callVirtualBase) {
  visitEnd   ((structure::QueryClauseSyntax&)node,false); 
}

void VisitorAbstractNodes::visit(const structure::JoinIntoClauseSyntax& node , bool callVirtualBase) {
  visit   ((base::Positioned&)node,false); 
}

void VisitorAbstractNodes::visitEnd(const structure::JoinIntoClauseSyntax& node , bool callVirtualBase) {
  visitEnd   ((base::Positioned&)node,false); 
}

void VisitorAbstractNodes::visit(const structure::LetClauseSyntax& node , bool callVirtualBase) {
  visit   ((structure::QueryClauseSyntax&)node,false); 
}

void VisitorAbstractNodes::visitEnd(const structure::LetClauseSyntax& node , bool callVirtualBase) {
  visitEnd   ((structure::QueryClauseSyntax&)node,false); 
}

void VisitorAbstractNodes::visit(const structure::MemberCrefSyntax& node , bool callVirtualBase) {
  visit   ((structure::CrefSyntax&)node,false); 
}

void VisitorAbstractNodes::visitEnd(const structure::MemberCrefSyntax& node , bool callVirtualBase) {
  visitEnd   ((structure::CrefSyntax&)node,false); 
}

void VisitorAbstractNodes::visit(const structure::MemberDeclarationSyntax& node , bool callVirtualBase) {
  visit   ((base::Positioned&)node,false); 
}

void VisitorAbstractNodes::visitEnd(const structure::MemberDeclarationSyntax& node , bool callVirtualBase) {
  visitEnd   ((base::Positioned&)node,false); 
}

void VisitorAbstractNodes::visit(const structure::MethodDeclarationSyntax& node , bool callVirtualBase) {
  visit   ((structure::BaseMethodDeclarationSyntax&)node,false); 
}

void VisitorAbstractNodes::visitEnd(const structure::MethodDeclarationSyntax& node , bool callVirtualBase) {
  visitEnd   ((structure::BaseMethodDeclarationSyntax&)node,false); 
}

void VisitorAbstractNodes::visit(const structure::NameColonSyntax& node , bool callVirtualBase) {
  visit   ((base::Positioned&)node,false); 
}

void VisitorAbstractNodes::visitEnd(const structure::NameColonSyntax& node , bool callVirtualBase) {
  visitEnd   ((base::Positioned&)node,false); 
}

void VisitorAbstractNodes::visit(const structure::NameEqualsSyntax& node , bool callVirtualBase) {
  visit   ((base::Positioned&)node,false); 
}

void VisitorAbstractNodes::visitEnd(const structure::NameEqualsSyntax& node , bool callVirtualBase) {
  visitEnd   ((base::Positioned&)node,false); 
}

void VisitorAbstractNodes::visit(const structure::NameMemberCrefSyntax& node , bool callVirtualBase) {
  visit   ((structure::MemberCrefSyntax&)node,false); 
}

void VisitorAbstractNodes::visitEnd(const structure::NameMemberCrefSyntax& node , bool callVirtualBase) {
  visitEnd   ((structure::MemberCrefSyntax&)node,false); 
}

void VisitorAbstractNodes::visit(const structure::NamespaceDeclarationSyntax& node , bool callVirtualBase) {
  visit   ((structure::MemberDeclarationSyntax&)node,false); 
}

void VisitorAbstractNodes::visitEnd(const structure::NamespaceDeclarationSyntax& node , bool callVirtualBase) {
  visitEnd   ((structure::MemberDeclarationSyntax&)node,false); 
}

void VisitorAbstractNodes::visit(const structure::OperatorDeclarationSyntax& node , bool callVirtualBase) {
  visit   ((structure::BaseMethodDeclarationSyntax&)node,false); 
}

void VisitorAbstractNodes::visitEnd(const structure::OperatorDeclarationSyntax& node , bool callVirtualBase) {
  visitEnd   ((structure::BaseMethodDeclarationSyntax&)node,false); 
}

void VisitorAbstractNodes::visit(const structure::OperatorMemberCrefSyntax& node , bool callVirtualBase) {
  visit   ((structure::MemberCrefSyntax&)node,false); 
}

void VisitorAbstractNodes::visitEnd(const structure::OperatorMemberCrefSyntax& node , bool callVirtualBase) {
  visitEnd   ((structure::MemberCrefSyntax&)node,false); 
}

void VisitorAbstractNodes::visit(const structure::OrderByClauseSyntax& node , bool callVirtualBase) {
  visit   ((structure::QueryClauseSyntax&)node,false); 
}

void VisitorAbstractNodes::visitEnd(const structure::OrderByClauseSyntax& node , bool callVirtualBase) {
  visitEnd   ((structure::QueryClauseSyntax&)node,false); 
}

void VisitorAbstractNodes::visit(const structure::OrderingSyntax& node , bool callVirtualBase) {
  visit   ((base::Positioned&)node,false); 
}

void VisitorAbstractNodes::visitEnd(const structure::OrderingSyntax& node , bool callVirtualBase) {
  visitEnd   ((base::Positioned&)node,false); 
}

void VisitorAbstractNodes::visit(const structure::ParameterListSyntax& node , bool callVirtualBase) {
  visit   ((structure::BaseParameterListSyntax&)node,false); 
}

void VisitorAbstractNodes::visitEnd(const structure::ParameterListSyntax& node , bool callVirtualBase) {
  visitEnd   ((structure::BaseParameterListSyntax&)node,false); 
}

void VisitorAbstractNodes::visit(const structure::ParameterSyntax& node , bool callVirtualBase) {
  visit   ((base::Positioned&)node,false); 
}

void VisitorAbstractNodes::visitEnd(const structure::ParameterSyntax& node , bool callVirtualBase) {
  visitEnd   ((base::Positioned&)node,false); 
}

void VisitorAbstractNodes::visit(const structure::ParenthesizedVariableDesignationSyntax& node , bool callVirtualBase) {
  visit   ((structure::VariableDesignationSyntax&)node,false); 
}

void VisitorAbstractNodes::visitEnd(const structure::ParenthesizedVariableDesignationSyntax& node , bool callVirtualBase) {
  visitEnd   ((structure::VariableDesignationSyntax&)node,false); 
}

void VisitorAbstractNodes::visit(const structure::PatternSyntax& node , bool callVirtualBase) {
  visit   ((base::Positioned&)node,false); 
}

void VisitorAbstractNodes::visitEnd(const structure::PatternSyntax& node , bool callVirtualBase) {
  visitEnd   ((base::Positioned&)node,false); 
}

void VisitorAbstractNodes::visit(const structure::PositionalPatternClauseSyntax& node , bool callVirtualBase) {
  visit   ((base::Positioned&)node,false); 
}

void VisitorAbstractNodes::visitEnd(const structure::PositionalPatternClauseSyntax& node , bool callVirtualBase) {
  visitEnd   ((base::Positioned&)node,false); 
}

void VisitorAbstractNodes::visit(const structure::PropertyDeclarationSyntax& node , bool callVirtualBase) {
  visit   ((structure::BasePropertyDeclarationSyntax&)node,false); 
}

void VisitorAbstractNodes::visitEnd(const structure::PropertyDeclarationSyntax& node , bool callVirtualBase) {
  visitEnd   ((structure::BasePropertyDeclarationSyntax&)node,false); 
}

void VisitorAbstractNodes::visit(const structure::PropertyPatternClauseSyntax& node , bool callVirtualBase) {
  visit   ((base::Positioned&)node,false); 
}

void VisitorAbstractNodes::visitEnd(const structure::PropertyPatternClauseSyntax& node , bool callVirtualBase) {
  visitEnd   ((base::Positioned&)node,false); 
}

void VisitorAbstractNodes::visit(const structure::QualifiedCrefSyntax& node , bool callVirtualBase) {
  visit   ((structure::CrefSyntax&)node,false); 
}

void VisitorAbstractNodes::visitEnd(const structure::QualifiedCrefSyntax& node , bool callVirtualBase) {
  visitEnd   ((structure::CrefSyntax&)node,false); 
}

void VisitorAbstractNodes::visit(const structure::QueryBodySyntax& node , bool callVirtualBase) {
  visit   ((base::Positioned&)node,false); 
}

void VisitorAbstractNodes::visitEnd(const structure::QueryBodySyntax& node , bool callVirtualBase) {
  visitEnd   ((base::Positioned&)node,false); 
}

void VisitorAbstractNodes::visit(const structure::QueryClauseSyntax& node , bool callVirtualBase) {
  visit   ((base::Positioned&)node,false); 
}

void VisitorAbstractNodes::visitEnd(const structure::QueryClauseSyntax& node , bool callVirtualBase) {
  visitEnd   ((base::Positioned&)node,false); 
}

void VisitorAbstractNodes::visit(const structure::QueryContinuationSyntax& node , bool callVirtualBase) {
  visit   ((base::Positioned&)node,false); 
}

void VisitorAbstractNodes::visitEnd(const structure::QueryContinuationSyntax& node , bool callVirtualBase) {
  visitEnd   ((base::Positioned&)node,false); 
}

void VisitorAbstractNodes::visit(const structure::RecursivePatternSyntax& node , bool callVirtualBase) {
  visit   ((structure::PatternSyntax&)node,false); 
}

void VisitorAbstractNodes::visitEnd(const structure::RecursivePatternSyntax& node , bool callVirtualBase) {
  visitEnd   ((structure::PatternSyntax&)node,false); 
}

void VisitorAbstractNodes::visit(const structure::SelectClauseSyntax& node , bool callVirtualBase) {
  visit   ((structure::SelectOrGroupClauseSyntax&)node,false); 
}

void VisitorAbstractNodes::visitEnd(const structure::SelectClauseSyntax& node , bool callVirtualBase) {
  visitEnd   ((structure::SelectOrGroupClauseSyntax&)node,false); 
}

void VisitorAbstractNodes::visit(const structure::SelectOrGroupClauseSyntax& node , bool callVirtualBase) {
  visit   ((base::Positioned&)node,false); 
}

void VisitorAbstractNodes::visitEnd(const structure::SelectOrGroupClauseSyntax& node , bool callVirtualBase) {
  visitEnd   ((base::Positioned&)node,false); 
}

void VisitorAbstractNodes::visit(const structure::SimpleBaseTypeSyntax& node , bool callVirtualBase) {
  visit   ((structure::BaseTypeSyntax&)node,false); 
}

void VisitorAbstractNodes::visitEnd(const structure::SimpleBaseTypeSyntax& node , bool callVirtualBase) {
  visitEnd   ((structure::BaseTypeSyntax&)node,false); 
}

void VisitorAbstractNodes::visit(const structure::SingleVariableDesignationSyntax& node , bool callVirtualBase) {
  visit   ((structure::VariableDesignationSyntax&)node,false); 
}

void VisitorAbstractNodes::visitEnd(const structure::SingleVariableDesignationSyntax& node , bool callVirtualBase) {
  visitEnd   ((structure::VariableDesignationSyntax&)node,false); 
}

void VisitorAbstractNodes::visit(const structure::StructDeclarationSyntax& node , bool callVirtualBase) {
  visit   ((structure::TypeDeclarationSyntax&)node,false); 
}

void VisitorAbstractNodes::visitEnd(const structure::StructDeclarationSyntax& node , bool callVirtualBase) {
  visitEnd   ((structure::TypeDeclarationSyntax&)node,false); 
}

void VisitorAbstractNodes::visit(const structure::SubpatternSyntax& node , bool callVirtualBase) {
  visit   ((base::Positioned&)node,false); 
}

void VisitorAbstractNodes::visitEnd(const structure::SubpatternSyntax& node , bool callVirtualBase) {
  visitEnd   ((base::Positioned&)node,false); 
}

void VisitorAbstractNodes::visit(const structure::SwitchExpressionArmSyntax& node , bool callVirtualBase) {
  visit   ((base::Positioned&)node,false); 
}

void VisitorAbstractNodes::visitEnd(const structure::SwitchExpressionArmSyntax& node , bool callVirtualBase) {
  visitEnd   ((base::Positioned&)node,false); 
}

void VisitorAbstractNodes::visit(const structure::SwitchLabelSyntax& node , bool callVirtualBase) {
  visit   ((base::Positioned&)node,false); 
}

void VisitorAbstractNodes::visitEnd(const structure::SwitchLabelSyntax& node , bool callVirtualBase) {
  visitEnd   ((base::Positioned&)node,false); 
}

void VisitorAbstractNodes::visit(const structure::SwitchSectionSyntax& node , bool callVirtualBase) {
  visit   ((base::Positioned&)node,false); 
}

void VisitorAbstractNodes::visitEnd(const structure::SwitchSectionSyntax& node , bool callVirtualBase) {
  visitEnd   ((base::Positioned&)node,false); 
}

void VisitorAbstractNodes::visit(const structure::SyntaxToken& node , bool callVirtualBase) {
  visit   ((base::Positioned&)node,false); 
}

void VisitorAbstractNodes::visitEnd(const structure::SyntaxToken& node , bool callVirtualBase) {
  visitEnd   ((base::Positioned&)node,false); 
}

void VisitorAbstractNodes::visit(const structure::TupleElementSyntax& node , bool callVirtualBase) {
  visit   ((base::Positioned&)node,false); 
}

void VisitorAbstractNodes::visitEnd(const structure::TupleElementSyntax& node , bool callVirtualBase) {
  visitEnd   ((base::Positioned&)node,false); 
}

void VisitorAbstractNodes::visit(const structure::TypeArgumentListSyntax& node , bool callVirtualBase) {
  visit   ((base::Positioned&)node,false); 
}

void VisitorAbstractNodes::visitEnd(const structure::TypeArgumentListSyntax& node , bool callVirtualBase) {
  visitEnd   ((base::Positioned&)node,false); 
}

void VisitorAbstractNodes::visit(const structure::TypeConstraintSyntax& node , bool callVirtualBase) {
  visit   ((structure::TypeParameterConstraintSyntax&)node,false); 
}

void VisitorAbstractNodes::visitEnd(const structure::TypeConstraintSyntax& node , bool callVirtualBase) {
  visitEnd   ((structure::TypeParameterConstraintSyntax&)node,false); 
}

void VisitorAbstractNodes::visit(const structure::TypeCrefSyntax& node , bool callVirtualBase) {
  visit   ((structure::CrefSyntax&)node,false); 
}

void VisitorAbstractNodes::visitEnd(const structure::TypeCrefSyntax& node , bool callVirtualBase) {
  visitEnd   ((structure::CrefSyntax&)node,false); 
}

void VisitorAbstractNodes::visit(const structure::TypeDeclarationSyntax& node , bool callVirtualBase) {
  visit   ((structure::BaseTypeDeclarationSyntax&)node,false); 
}

void VisitorAbstractNodes::visitEnd(const structure::TypeDeclarationSyntax& node , bool callVirtualBase) {
  visitEnd   ((structure::BaseTypeDeclarationSyntax&)node,false); 
}

void VisitorAbstractNodes::visit(const structure::TypeParameterConstraintClauseSyntax& node , bool callVirtualBase) {
  visit   ((base::Positioned&)node,false); 
}

void VisitorAbstractNodes::visitEnd(const structure::TypeParameterConstraintClauseSyntax& node , bool callVirtualBase) {
  visitEnd   ((base::Positioned&)node,false); 
}

void VisitorAbstractNodes::visit(const structure::TypeParameterConstraintSyntax& node , bool callVirtualBase) {
  visit   ((base::Positioned&)node,false); 
}

void VisitorAbstractNodes::visitEnd(const structure::TypeParameterConstraintSyntax& node , bool callVirtualBase) {
  visitEnd   ((base::Positioned&)node,false); 
}

void VisitorAbstractNodes::visit(const structure::TypeParameterListSyntax& node , bool callVirtualBase) {
  visit   ((base::Positioned&)node,false); 
}

void VisitorAbstractNodes::visitEnd(const structure::TypeParameterListSyntax& node , bool callVirtualBase) {
  visitEnd   ((base::Positioned&)node,false); 
}

void VisitorAbstractNodes::visit(const structure::TypeParameterSyntax& node , bool callVirtualBase) {
  visit   ((base::Positioned&)node,false); 
}

void VisitorAbstractNodes::visitEnd(const structure::TypeParameterSyntax& node , bool callVirtualBase) {
  visitEnd   ((base::Positioned&)node,false); 
}

void VisitorAbstractNodes::visit(const structure::UsingDirectiveSyntax& node , bool callVirtualBase) {
  visit   ((base::Positioned&)node,false); 
}

void VisitorAbstractNodes::visitEnd(const structure::UsingDirectiveSyntax& node , bool callVirtualBase) {
  visitEnd   ((base::Positioned&)node,false); 
}

void VisitorAbstractNodes::visit(const structure::VarPatternSyntax& node , bool callVirtualBase) {
  visit   ((structure::PatternSyntax&)node,false); 
}

void VisitorAbstractNodes::visitEnd(const structure::VarPatternSyntax& node , bool callVirtualBase) {
  visitEnd   ((structure::PatternSyntax&)node,false); 
}

void VisitorAbstractNodes::visit(const structure::VariableDeclarationSyntax& node , bool callVirtualBase) {
  visit   ((base::Positioned&)node,false); 
}

void VisitorAbstractNodes::visitEnd(const structure::VariableDeclarationSyntax& node , bool callVirtualBase) {
  visitEnd   ((base::Positioned&)node,false); 
}

void VisitorAbstractNodes::visit(const structure::VariableDeclaratorSyntax& node , bool callVirtualBase) {
  visit   ((base::Positioned&)node,false); 
}

void VisitorAbstractNodes::visitEnd(const structure::VariableDeclaratorSyntax& node , bool callVirtualBase) {
  visitEnd   ((base::Positioned&)node,false); 
}

void VisitorAbstractNodes::visit(const structure::VariableDesignationSyntax& node , bool callVirtualBase) {
  visit   ((base::Positioned&)node,false); 
}

void VisitorAbstractNodes::visitEnd(const structure::VariableDesignationSyntax& node , bool callVirtualBase) {
  visitEnd   ((base::Positioned&)node,false); 
}

void VisitorAbstractNodes::visit(const structure::WhenClauseSyntax& node , bool callVirtualBase) {
  visit   ((base::Positioned&)node,false); 
}

void VisitorAbstractNodes::visitEnd(const structure::WhenClauseSyntax& node , bool callVirtualBase) {
  visitEnd   ((base::Positioned&)node,false); 
}

void VisitorAbstractNodes::visit(const structure::WhereClauseSyntax& node , bool callVirtualBase) {
  visit   ((structure::QueryClauseSyntax&)node,false); 
}

void VisitorAbstractNodes::visitEnd(const structure::WhereClauseSyntax& node , bool callVirtualBase) {
  visitEnd   ((structure::QueryClauseSyntax&)node,false); 
}

void VisitorAbstractNodes::visit(const structure::XmlAttributeSyntax& node , bool callVirtualBase) {
  visit   ((base::Positioned&)node,false); 
}

void VisitorAbstractNodes::visitEnd(const structure::XmlAttributeSyntax& node , bool callVirtualBase) {
  visitEnd   ((base::Positioned&)node,false); 
}

void VisitorAbstractNodes::visit(const structure::XmlCDataSectionSyntax& node , bool callVirtualBase) {
  visit   ((structure::XmlNodeSyntax&)node,false); 
}

void VisitorAbstractNodes::visitEnd(const structure::XmlCDataSectionSyntax& node , bool callVirtualBase) {
  visitEnd   ((structure::XmlNodeSyntax&)node,false); 
}

void VisitorAbstractNodes::visit(const structure::XmlCommentSyntax& node , bool callVirtualBase) {
  visit   ((structure::XmlNodeSyntax&)node,false); 
}

void VisitorAbstractNodes::visitEnd(const structure::XmlCommentSyntax& node , bool callVirtualBase) {
  visitEnd   ((structure::XmlNodeSyntax&)node,false); 
}

void VisitorAbstractNodes::visit(const structure::XmlCrefAttributeSyntax& node , bool callVirtualBase) {
  visit   ((structure::XmlAttributeSyntax&)node,false); 
}

void VisitorAbstractNodes::visitEnd(const structure::XmlCrefAttributeSyntax& node , bool callVirtualBase) {
  visitEnd   ((structure::XmlAttributeSyntax&)node,false); 
}

void VisitorAbstractNodes::visit(const structure::XmlElementEndTagSyntax& node , bool callVirtualBase) {
  visit   ((base::Positioned&)node,false); 
}

void VisitorAbstractNodes::visitEnd(const structure::XmlElementEndTagSyntax& node , bool callVirtualBase) {
  visitEnd   ((base::Positioned&)node,false); 
}

void VisitorAbstractNodes::visit(const structure::XmlElementStartTagSyntax& node , bool callVirtualBase) {
  visit   ((base::Positioned&)node,false); 
}

void VisitorAbstractNodes::visitEnd(const structure::XmlElementStartTagSyntax& node , bool callVirtualBase) {
  visitEnd   ((base::Positioned&)node,false); 
}

void VisitorAbstractNodes::visit(const structure::XmlElementSyntax& node , bool callVirtualBase) {
  visit   ((structure::XmlNodeSyntax&)node,false); 
}

void VisitorAbstractNodes::visitEnd(const structure::XmlElementSyntax& node , bool callVirtualBase) {
  visitEnd   ((structure::XmlNodeSyntax&)node,false); 
}

void VisitorAbstractNodes::visit(const structure::XmlEmptyElementSyntax& node , bool callVirtualBase) {
  visit   ((structure::XmlNodeSyntax&)node,false); 
}

void VisitorAbstractNodes::visitEnd(const structure::XmlEmptyElementSyntax& node , bool callVirtualBase) {
  visitEnd   ((structure::XmlNodeSyntax&)node,false); 
}

void VisitorAbstractNodes::visit(const structure::XmlNameAttributeSyntax& node , bool callVirtualBase) {
  visit   ((structure::XmlAttributeSyntax&)node,false); 
}

void VisitorAbstractNodes::visitEnd(const structure::XmlNameAttributeSyntax& node , bool callVirtualBase) {
  visitEnd   ((structure::XmlAttributeSyntax&)node,false); 
}

void VisitorAbstractNodes::visit(const structure::XmlNameSyntax& node , bool callVirtualBase) {
  visit   ((base::Positioned&)node,false); 
}

void VisitorAbstractNodes::visitEnd(const structure::XmlNameSyntax& node , bool callVirtualBase) {
  visitEnd   ((base::Positioned&)node,false); 
}

void VisitorAbstractNodes::visit(const structure::XmlNodeSyntax& node , bool callVirtualBase) {
  visit   ((base::Positioned&)node,false); 
}

void VisitorAbstractNodes::visitEnd(const structure::XmlNodeSyntax& node , bool callVirtualBase) {
  visitEnd   ((base::Positioned&)node,false); 
}

void VisitorAbstractNodes::visit(const structure::XmlPrefixSyntax& node , bool callVirtualBase) {
  visit   ((base::Positioned&)node,false); 
}

void VisitorAbstractNodes::visitEnd(const structure::XmlPrefixSyntax& node , bool callVirtualBase) {
  visitEnd   ((base::Positioned&)node,false); 
}

void VisitorAbstractNodes::visit(const structure::XmlProcessingInstructionSyntax& node , bool callVirtualBase) {
  visit   ((structure::XmlNodeSyntax&)node,false); 
}

void VisitorAbstractNodes::visitEnd(const structure::XmlProcessingInstructionSyntax& node , bool callVirtualBase) {
  visitEnd   ((structure::XmlNodeSyntax&)node,false); 
}

void VisitorAbstractNodes::visit(const structure::XmlTextAttributeSyntax& node , bool callVirtualBase) {
  visit   ((structure::XmlAttributeSyntax&)node,false); 
}

void VisitorAbstractNodes::visitEnd(const structure::XmlTextAttributeSyntax& node , bool callVirtualBase) {
  visitEnd   ((structure::XmlAttributeSyntax&)node,false); 
}

void VisitorAbstractNodes::visit(const structure::XmlTextSyntax& node , bool callVirtualBase) {
  visit   ((structure::XmlNodeSyntax&)node,false); 
}

void VisitorAbstractNodes::visitEnd(const structure::XmlTextSyntax& node , bool callVirtualBase) {
  visitEnd   ((structure::XmlNodeSyntax&)node,false); 
}


}}}
