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

#include "csharp/inc/csharp.h"


namespace columbus { namespace csharp { namespace asg {
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

void Visitor::visit(const expression::AliasQualifiedNameSyntax& node , bool callVirtualBase) {}

void Visitor::visitEnd(const expression::AliasQualifiedNameSyntax& node , bool callVirtualBase) { }

void Visitor::visit(const expression::AnonymousMethodExpressionSyntax& node , bool callVirtualBase) {}

void Visitor::visitEnd(const expression::AnonymousMethodExpressionSyntax& node , bool callVirtualBase) { }

void Visitor::visit(const expression::AnonymousObjectCreationExpressionSyntax& node , bool callVirtualBase) {}

void Visitor::visitEnd(const expression::AnonymousObjectCreationExpressionSyntax& node , bool callVirtualBase) { }

void Visitor::visit(const expression::ArrayCreationExpressionSyntax& node , bool callVirtualBase) {}

void Visitor::visitEnd(const expression::ArrayCreationExpressionSyntax& node , bool callVirtualBase) { }

void Visitor::visit(const expression::ArrayTypeSyntax& node , bool callVirtualBase) {}

void Visitor::visitEnd(const expression::ArrayTypeSyntax& node , bool callVirtualBase) { }

void Visitor::visit(const expression::AssignmentExpressionSyntax& node , bool callVirtualBase) {}

void Visitor::visitEnd(const expression::AssignmentExpressionSyntax& node , bool callVirtualBase) { }

void Visitor::visit(const expression::AwaitExpressionSyntax& node , bool callVirtualBase) {}

void Visitor::visitEnd(const expression::AwaitExpressionSyntax& node , bool callVirtualBase) { }

void Visitor::visit(const expression::BaseExpressionSyntax& node , bool callVirtualBase) {}

void Visitor::visitEnd(const expression::BaseExpressionSyntax& node , bool callVirtualBase) { }

void Visitor::visit(const expression::BinaryExpressionSyntax& node , bool callVirtualBase) {}

void Visitor::visitEnd(const expression::BinaryExpressionSyntax& node , bool callVirtualBase) { }

void Visitor::visit(const expression::CastExpressionSyntax& node , bool callVirtualBase) {}

void Visitor::visitEnd(const expression::CastExpressionSyntax& node , bool callVirtualBase) { }

void Visitor::visit(const expression::CheckedExpressionSyntax& node , bool callVirtualBase) {}

void Visitor::visitEnd(const expression::CheckedExpressionSyntax& node , bool callVirtualBase) { }

void Visitor::visit(const expression::ConditionalAccessExpressionSyntax& node , bool callVirtualBase) {}

void Visitor::visitEnd(const expression::ConditionalAccessExpressionSyntax& node , bool callVirtualBase) { }

void Visitor::visit(const expression::ConditionalExpressionSyntax& node , bool callVirtualBase) {}

void Visitor::visitEnd(const expression::ConditionalExpressionSyntax& node , bool callVirtualBase) { }

void Visitor::visit(const expression::DefaultExpressionSyntax& node , bool callVirtualBase) {}

void Visitor::visitEnd(const expression::DefaultExpressionSyntax& node , bool callVirtualBase) { }

void Visitor::visit(const expression::ElementAccessExpressionSyntax& node , bool callVirtualBase) {}

void Visitor::visitEnd(const expression::ElementAccessExpressionSyntax& node , bool callVirtualBase) { }

void Visitor::visit(const expression::ElementBindingExpressionSyntax& node , bool callVirtualBase) {}

void Visitor::visitEnd(const expression::ElementBindingExpressionSyntax& node , bool callVirtualBase) { }

void Visitor::visit(const expression::GenericNameSyntax& node , bool callVirtualBase) {}

void Visitor::visitEnd(const expression::GenericNameSyntax& node , bool callVirtualBase) { }

void Visitor::visit(const expression::IdentifierNameSyntax& node , bool callVirtualBase) {}

void Visitor::visitEnd(const expression::IdentifierNameSyntax& node , bool callVirtualBase) { }

void Visitor::visit(const expression::ImplicitArrayCreationExpressionSyntax& node , bool callVirtualBase) {}

void Visitor::visitEnd(const expression::ImplicitArrayCreationExpressionSyntax& node , bool callVirtualBase) { }

void Visitor::visit(const expression::ImplicitElementAccessSyntax& node , bool callVirtualBase) {}

void Visitor::visitEnd(const expression::ImplicitElementAccessSyntax& node , bool callVirtualBase) { }

void Visitor::visit(const expression::InitializerExpressionSyntax& node , bool callVirtualBase) {}

void Visitor::visitEnd(const expression::InitializerExpressionSyntax& node , bool callVirtualBase) { }

void Visitor::visit(const expression::InterpolatedStringExpressionSyntax& node , bool callVirtualBase) {}

void Visitor::visitEnd(const expression::InterpolatedStringExpressionSyntax& node , bool callVirtualBase) { }

void Visitor::visit(const expression::InvocationExpressionSyntax& node , bool callVirtualBase) {}

void Visitor::visitEnd(const expression::InvocationExpressionSyntax& node , bool callVirtualBase) { }

void Visitor::visit(const expression::LiteralExpressionSyntax& node , bool callVirtualBase) {}

void Visitor::visitEnd(const expression::LiteralExpressionSyntax& node , bool callVirtualBase) { }

void Visitor::visit(const expression::MakeRefExpressionSyntax& node , bool callVirtualBase) {}

void Visitor::visitEnd(const expression::MakeRefExpressionSyntax& node , bool callVirtualBase) { }

void Visitor::visit(const expression::MemberAccessExpressionSyntax& node , bool callVirtualBase) {}

void Visitor::visitEnd(const expression::MemberAccessExpressionSyntax& node , bool callVirtualBase) { }

void Visitor::visit(const expression::MemberBindingExpressionSyntax& node , bool callVirtualBase) {}

void Visitor::visitEnd(const expression::MemberBindingExpressionSyntax& node , bool callVirtualBase) { }

void Visitor::visit(const expression::NullableTypeSyntax& node , bool callVirtualBase) {}

void Visitor::visitEnd(const expression::NullableTypeSyntax& node , bool callVirtualBase) { }

void Visitor::visit(const expression::ObjectCreationExpressionSyntax& node , bool callVirtualBase) {}

void Visitor::visitEnd(const expression::ObjectCreationExpressionSyntax& node , bool callVirtualBase) { }

void Visitor::visit(const expression::OmittedArraySizeExpressionSyntax& node , bool callVirtualBase) {}

void Visitor::visitEnd(const expression::OmittedArraySizeExpressionSyntax& node , bool callVirtualBase) { }

void Visitor::visit(const expression::OmittedTypeArgumentSyntax& node , bool callVirtualBase) {}

void Visitor::visitEnd(const expression::OmittedTypeArgumentSyntax& node , bool callVirtualBase) { }

void Visitor::visit(const expression::ParenthesizedExpressionSyntax& node , bool callVirtualBase) {}

void Visitor::visitEnd(const expression::ParenthesizedExpressionSyntax& node , bool callVirtualBase) { }

void Visitor::visit(const expression::ParenthesizedLambdaExpressionSyntax& node , bool callVirtualBase) {}

void Visitor::visitEnd(const expression::ParenthesizedLambdaExpressionSyntax& node , bool callVirtualBase) { }

void Visitor::visit(const expression::PointerTypeSyntax& node , bool callVirtualBase) {}

void Visitor::visitEnd(const expression::PointerTypeSyntax& node , bool callVirtualBase) { }

void Visitor::visit(const expression::PostfixUnaryExpressionSyntax& node , bool callVirtualBase) {}

void Visitor::visitEnd(const expression::PostfixUnaryExpressionSyntax& node , bool callVirtualBase) { }

void Visitor::visit(const expression::PredefinedTypeSyntax& node , bool callVirtualBase) {}

void Visitor::visitEnd(const expression::PredefinedTypeSyntax& node , bool callVirtualBase) { }

void Visitor::visit(const expression::PrefixUnaryExpressionSyntax& node , bool callVirtualBase) {}

void Visitor::visitEnd(const expression::PrefixUnaryExpressionSyntax& node , bool callVirtualBase) { }

void Visitor::visit(const expression::QualifiedNameSyntax& node , bool callVirtualBase) {}

void Visitor::visitEnd(const expression::QualifiedNameSyntax& node , bool callVirtualBase) { }

void Visitor::visit(const expression::QueryExpressionSyntax& node , bool callVirtualBase) {}

void Visitor::visitEnd(const expression::QueryExpressionSyntax& node , bool callVirtualBase) { }

void Visitor::visit(const expression::RefTypeExpressionSyntax& node , bool callVirtualBase) {}

void Visitor::visitEnd(const expression::RefTypeExpressionSyntax& node , bool callVirtualBase) { }

void Visitor::visit(const expression::RefValueExpressionSyntax& node , bool callVirtualBase) {}

void Visitor::visitEnd(const expression::RefValueExpressionSyntax& node , bool callVirtualBase) { }

void Visitor::visit(const expression::SimpleLambdaExpressionSyntax& node , bool callVirtualBase) {}

void Visitor::visitEnd(const expression::SimpleLambdaExpressionSyntax& node , bool callVirtualBase) { }

void Visitor::visit(const expression::SizeOfExpressionSyntax& node , bool callVirtualBase) {}

void Visitor::visitEnd(const expression::SizeOfExpressionSyntax& node , bool callVirtualBase) { }

void Visitor::visit(const expression::StackAllocArrayCreationExpressionSyntax& node , bool callVirtualBase) {}

void Visitor::visitEnd(const expression::StackAllocArrayCreationExpressionSyntax& node , bool callVirtualBase) { }

void Visitor::visit(const expression::ThisExpressionSyntax& node , bool callVirtualBase) {}

void Visitor::visitEnd(const expression::ThisExpressionSyntax& node , bool callVirtualBase) { }

void Visitor::visit(const expression::TypeOfExpressionSyntax& node , bool callVirtualBase) {}

void Visitor::visitEnd(const expression::TypeOfExpressionSyntax& node , bool callVirtualBase) { }

void Visitor::visit(const statement::BlockSyntax& node , bool callVirtualBase) {}

void Visitor::visitEnd(const statement::BlockSyntax& node , bool callVirtualBase) { }

void Visitor::visit(const statement::BreakStatementSyntax& node , bool callVirtualBase) {}

void Visitor::visitEnd(const statement::BreakStatementSyntax& node , bool callVirtualBase) { }

void Visitor::visit(const statement::CheckedStatementSyntax& node , bool callVirtualBase) {}

void Visitor::visitEnd(const statement::CheckedStatementSyntax& node , bool callVirtualBase) { }

void Visitor::visit(const statement::ContinueStatementSyntax& node , bool callVirtualBase) {}

void Visitor::visitEnd(const statement::ContinueStatementSyntax& node , bool callVirtualBase) { }

void Visitor::visit(const statement::DoStatementSyntax& node , bool callVirtualBase) {}

void Visitor::visitEnd(const statement::DoStatementSyntax& node , bool callVirtualBase) { }

void Visitor::visit(const statement::EmptyStatementSyntax& node , bool callVirtualBase) {}

void Visitor::visitEnd(const statement::EmptyStatementSyntax& node , bool callVirtualBase) { }

void Visitor::visit(const statement::ExpressionStatementSyntax& node , bool callVirtualBase) {}

void Visitor::visitEnd(const statement::ExpressionStatementSyntax& node , bool callVirtualBase) { }

void Visitor::visit(const statement::FixedStatementSyntax& node , bool callVirtualBase) {}

void Visitor::visitEnd(const statement::FixedStatementSyntax& node , bool callVirtualBase) { }

void Visitor::visit(const statement::ForEachStatementSyntax& node , bool callVirtualBase) {}

void Visitor::visitEnd(const statement::ForEachStatementSyntax& node , bool callVirtualBase) { }

void Visitor::visit(const statement::ForStatementSyntax& node , bool callVirtualBase) {}

void Visitor::visitEnd(const statement::ForStatementSyntax& node , bool callVirtualBase) { }

void Visitor::visit(const statement::GotoStatementSyntax& node , bool callVirtualBase) {}

void Visitor::visitEnd(const statement::GotoStatementSyntax& node , bool callVirtualBase) { }

void Visitor::visit(const statement::IfStatementSyntax& node , bool callVirtualBase) {}

void Visitor::visitEnd(const statement::IfStatementSyntax& node , bool callVirtualBase) { }

void Visitor::visit(const statement::LabeledStatementSyntax& node , bool callVirtualBase) {}

void Visitor::visitEnd(const statement::LabeledStatementSyntax& node , bool callVirtualBase) { }

void Visitor::visit(const statement::LocalDeclarationStatementSyntax& node , bool callVirtualBase) {}

void Visitor::visitEnd(const statement::LocalDeclarationStatementSyntax& node , bool callVirtualBase) { }

void Visitor::visit(const statement::LockStatementSyntax& node , bool callVirtualBase) {}

void Visitor::visitEnd(const statement::LockStatementSyntax& node , bool callVirtualBase) { }

void Visitor::visit(const statement::ReturnStatementSyntax& node , bool callVirtualBase) {}

void Visitor::visitEnd(const statement::ReturnStatementSyntax& node , bool callVirtualBase) { }

void Visitor::visit(const statement::SwitchStatementSyntax& node , bool callVirtualBase) {}

void Visitor::visitEnd(const statement::SwitchStatementSyntax& node , bool callVirtualBase) { }

void Visitor::visit(const statement::ThrowStatementSyntax& node , bool callVirtualBase) {}

void Visitor::visitEnd(const statement::ThrowStatementSyntax& node , bool callVirtualBase) { }

void Visitor::visit(const statement::TryStatementSyntax& node , bool callVirtualBase) {}

void Visitor::visitEnd(const statement::TryStatementSyntax& node , bool callVirtualBase) { }

void Visitor::visit(const statement::UnsafeStatementSyntax& node , bool callVirtualBase) {}

void Visitor::visitEnd(const statement::UnsafeStatementSyntax& node , bool callVirtualBase) { }

void Visitor::visit(const statement::UsingStatementSyntax& node , bool callVirtualBase) {}

void Visitor::visitEnd(const statement::UsingStatementSyntax& node , bool callVirtualBase) { }

void Visitor::visit(const statement::WhileStatementSyntax& node , bool callVirtualBase) {}

void Visitor::visitEnd(const statement::WhileStatementSyntax& node , bool callVirtualBase) { }

void Visitor::visit(const statement::YieldStatementSyntax& node , bool callVirtualBase) {}

void Visitor::visitEnd(const statement::YieldStatementSyntax& node , bool callVirtualBase) { }

void Visitor::visit(const structure::AccessorDeclarationSyntax& node , bool callVirtualBase) {}

void Visitor::visitEnd(const structure::AccessorDeclarationSyntax& node , bool callVirtualBase) { }

void Visitor::visit(const structure::AccessorListSyntax& node , bool callVirtualBase) {}

void Visitor::visitEnd(const structure::AccessorListSyntax& node , bool callVirtualBase) { }

void Visitor::visit(const structure::AnonymousObjectMemberDeclaratorSyntax& node , bool callVirtualBase) {}

void Visitor::visitEnd(const structure::AnonymousObjectMemberDeclaratorSyntax& node , bool callVirtualBase) { }

void Visitor::visit(const structure::ArgumentListSyntax& node , bool callVirtualBase) {}

void Visitor::visitEnd(const structure::ArgumentListSyntax& node , bool callVirtualBase) { }

void Visitor::visit(const structure::ArgumentSyntax& node , bool callVirtualBase) {}

void Visitor::visitEnd(const structure::ArgumentSyntax& node , bool callVirtualBase) { }

void Visitor::visit(const structure::ArrayRankSpecifierSyntax& node , bool callVirtualBase) {}

void Visitor::visitEnd(const structure::ArrayRankSpecifierSyntax& node , bool callVirtualBase) { }

void Visitor::visit(const structure::ArrowExpressionClauseSyntax& node , bool callVirtualBase) {}

void Visitor::visitEnd(const structure::ArrowExpressionClauseSyntax& node , bool callVirtualBase) { }

void Visitor::visit(const structure::AttributeArgumentListSyntax& node , bool callVirtualBase) {}

void Visitor::visitEnd(const structure::AttributeArgumentListSyntax& node , bool callVirtualBase) { }

void Visitor::visit(const structure::AttributeArgumentSyntax& node , bool callVirtualBase) {}

void Visitor::visitEnd(const structure::AttributeArgumentSyntax& node , bool callVirtualBase) { }

void Visitor::visit(const structure::AttributeListSyntax& node , bool callVirtualBase) {}

void Visitor::visitEnd(const structure::AttributeListSyntax& node , bool callVirtualBase) { }

void Visitor::visit(const structure::AttributeSyntax& node , bool callVirtualBase) {}

void Visitor::visitEnd(const structure::AttributeSyntax& node , bool callVirtualBase) { }

void Visitor::visit(const structure::AttributeTargetSpecifierSyntax& node , bool callVirtualBase) {}

void Visitor::visitEnd(const structure::AttributeTargetSpecifierSyntax& node , bool callVirtualBase) { }

void Visitor::visit(const structure::BaseListSyntax& node , bool callVirtualBase) {}

void Visitor::visitEnd(const structure::BaseListSyntax& node , bool callVirtualBase) { }

void Visitor::visit(const structure::BracketedArgumentListSyntax& node , bool callVirtualBase) {}

void Visitor::visitEnd(const structure::BracketedArgumentListSyntax& node , bool callVirtualBase) { }

void Visitor::visit(const structure::BracketedParameterListSyntax& node , bool callVirtualBase) {}

void Visitor::visitEnd(const structure::BracketedParameterListSyntax& node , bool callVirtualBase) { }

void Visitor::visit(const structure::CaseSwitchLabelSyntax& node , bool callVirtualBase) {}

void Visitor::visitEnd(const structure::CaseSwitchLabelSyntax& node , bool callVirtualBase) { }

void Visitor::visit(const structure::CatchClauseSyntax& node , bool callVirtualBase) {}

void Visitor::visitEnd(const structure::CatchClauseSyntax& node , bool callVirtualBase) { }

void Visitor::visit(const structure::CatchDeclarationSyntax& node , bool callVirtualBase) {}

void Visitor::visitEnd(const structure::CatchDeclarationSyntax& node , bool callVirtualBase) { }

void Visitor::visit(const structure::CatchFilterClauseSyntax& node , bool callVirtualBase) {}

void Visitor::visitEnd(const structure::CatchFilterClauseSyntax& node , bool callVirtualBase) { }

void Visitor::visit(const structure::ClassDeclarationSyntax& node , bool callVirtualBase) {}

void Visitor::visitEnd(const structure::ClassDeclarationSyntax& node , bool callVirtualBase) { }

void Visitor::visit(const structure::ClassOrStructConstraintSyntax& node , bool callVirtualBase) {}

void Visitor::visitEnd(const structure::ClassOrStructConstraintSyntax& node , bool callVirtualBase) { }

void Visitor::visit(const structure::CompilationUnitSyntax& node , bool callVirtualBase) {}

void Visitor::visitEnd(const structure::CompilationUnitSyntax& node , bool callVirtualBase) { }

void Visitor::visit(const structure::ConstructorConstraintSyntax& node , bool callVirtualBase) {}

void Visitor::visitEnd(const structure::ConstructorConstraintSyntax& node , bool callVirtualBase) { }

void Visitor::visit(const structure::ConstructorDeclarationSyntax& node , bool callVirtualBase) {}

void Visitor::visitEnd(const structure::ConstructorDeclarationSyntax& node , bool callVirtualBase) { }

void Visitor::visit(const structure::ConstructorInitializerSyntax& node , bool callVirtualBase) {}

void Visitor::visitEnd(const structure::ConstructorInitializerSyntax& node , bool callVirtualBase) { }

void Visitor::visit(const structure::ConversionOperatorDeclarationSyntax& node , bool callVirtualBase) {}

void Visitor::visitEnd(const structure::ConversionOperatorDeclarationSyntax& node , bool callVirtualBase) { }

void Visitor::visit(const structure::ConversionOperatorMemberCrefSyntax& node , bool callVirtualBase) {}

void Visitor::visitEnd(const structure::ConversionOperatorMemberCrefSyntax& node , bool callVirtualBase) { }

void Visitor::visit(const structure::CrefBracketedParameterListSyntax& node , bool callVirtualBase) {}

void Visitor::visitEnd(const structure::CrefBracketedParameterListSyntax& node , bool callVirtualBase) { }

void Visitor::visit(const structure::CrefParameterListSyntax& node , bool callVirtualBase) {}

void Visitor::visitEnd(const structure::CrefParameterListSyntax& node , bool callVirtualBase) { }

void Visitor::visit(const structure::CrefParameterSyntax& node , bool callVirtualBase) {}

void Visitor::visitEnd(const structure::CrefParameterSyntax& node , bool callVirtualBase) { }

void Visitor::visit(const structure::DefaultSwitchLabelSyntax& node , bool callVirtualBase) {}

void Visitor::visitEnd(const structure::DefaultSwitchLabelSyntax& node , bool callVirtualBase) { }

void Visitor::visit(const structure::DelegateDeclarationSyntax& node , bool callVirtualBase) {}

void Visitor::visitEnd(const structure::DelegateDeclarationSyntax& node , bool callVirtualBase) { }

void Visitor::visit(const structure::DestructorDeclarationSyntax& node , bool callVirtualBase) {}

void Visitor::visitEnd(const structure::DestructorDeclarationSyntax& node , bool callVirtualBase) { }

void Visitor::visit(const structure::ElseClauseSyntax& node , bool callVirtualBase) {}

void Visitor::visitEnd(const structure::ElseClauseSyntax& node , bool callVirtualBase) { }

void Visitor::visit(const structure::EnumDeclarationSyntax& node , bool callVirtualBase) {}

void Visitor::visitEnd(const structure::EnumDeclarationSyntax& node , bool callVirtualBase) { }

void Visitor::visit(const structure::EnumMemberDeclarationSyntax& node , bool callVirtualBase) {}

void Visitor::visitEnd(const structure::EnumMemberDeclarationSyntax& node , bool callVirtualBase) { }

void Visitor::visit(const structure::EqualsValueClauseSyntax& node , bool callVirtualBase) {}

void Visitor::visitEnd(const structure::EqualsValueClauseSyntax& node , bool callVirtualBase) { }

void Visitor::visit(const structure::EventDeclarationSyntax& node , bool callVirtualBase) {}

void Visitor::visitEnd(const structure::EventDeclarationSyntax& node , bool callVirtualBase) { }

void Visitor::visit(const structure::EventFieldDeclarationSyntax& node , bool callVirtualBase) {}

void Visitor::visitEnd(const structure::EventFieldDeclarationSyntax& node , bool callVirtualBase) { }

void Visitor::visit(const structure::ExplicitInterfaceSpecifierSyntax& node , bool callVirtualBase) {}

void Visitor::visitEnd(const structure::ExplicitInterfaceSpecifierSyntax& node , bool callVirtualBase) { }

void Visitor::visit(const structure::ExternAliasDirectiveSyntax& node , bool callVirtualBase) {}

void Visitor::visitEnd(const structure::ExternAliasDirectiveSyntax& node , bool callVirtualBase) { }

void Visitor::visit(const structure::FieldDeclarationSyntax& node , bool callVirtualBase) {}

void Visitor::visitEnd(const structure::FieldDeclarationSyntax& node , bool callVirtualBase) { }

void Visitor::visit(const structure::FinallyClauseSyntax& node , bool callVirtualBase) {}

void Visitor::visitEnd(const structure::FinallyClauseSyntax& node , bool callVirtualBase) { }

void Visitor::visit(const structure::FromClauseSyntax& node , bool callVirtualBase) {}

void Visitor::visitEnd(const structure::FromClauseSyntax& node , bool callVirtualBase) { }

void Visitor::visit(const structure::GlobalStatementSyntax& node , bool callVirtualBase) {}

void Visitor::visitEnd(const structure::GlobalStatementSyntax& node , bool callVirtualBase) { }

void Visitor::visit(const structure::GroupClauseSyntax& node , bool callVirtualBase) {}

void Visitor::visitEnd(const structure::GroupClauseSyntax& node , bool callVirtualBase) { }

void Visitor::visit(const structure::IncompleteMemberSyntax& node , bool callVirtualBase) {}

void Visitor::visitEnd(const structure::IncompleteMemberSyntax& node , bool callVirtualBase) { }

void Visitor::visit(const structure::IndexerDeclarationSyntax& node , bool callVirtualBase) {}

void Visitor::visitEnd(const structure::IndexerDeclarationSyntax& node , bool callVirtualBase) { }

void Visitor::visit(const structure::IndexerMemberCrefSyntax& node , bool callVirtualBase) {}

void Visitor::visitEnd(const structure::IndexerMemberCrefSyntax& node , bool callVirtualBase) { }

void Visitor::visit(const structure::InterfaceDeclarationSyntax& node , bool callVirtualBase) {}

void Visitor::visitEnd(const structure::InterfaceDeclarationSyntax& node , bool callVirtualBase) { }

void Visitor::visit(const structure::InterpolatedStringTextSyntax& node , bool callVirtualBase) {}

void Visitor::visitEnd(const structure::InterpolatedStringTextSyntax& node , bool callVirtualBase) { }

void Visitor::visit(const structure::InterpolationAlignmentClauseSyntax& node , bool callVirtualBase) {}

void Visitor::visitEnd(const structure::InterpolationAlignmentClauseSyntax& node , bool callVirtualBase) { }

void Visitor::visit(const structure::InterpolationFormatClauseSyntax& node , bool callVirtualBase) {}

void Visitor::visitEnd(const structure::InterpolationFormatClauseSyntax& node , bool callVirtualBase) { }

void Visitor::visit(const structure::InterpolationSyntax& node , bool callVirtualBase) {}

void Visitor::visitEnd(const structure::InterpolationSyntax& node , bool callVirtualBase) { }

void Visitor::visit(const structure::JoinClauseSyntax& node , bool callVirtualBase) {}

void Visitor::visitEnd(const structure::JoinClauseSyntax& node , bool callVirtualBase) { }

void Visitor::visit(const structure::JoinIntoClauseSyntax& node , bool callVirtualBase) {}

void Visitor::visitEnd(const structure::JoinIntoClauseSyntax& node , bool callVirtualBase) { }

void Visitor::visit(const structure::LetClauseSyntax& node , bool callVirtualBase) {}

void Visitor::visitEnd(const structure::LetClauseSyntax& node , bool callVirtualBase) { }

void Visitor::visit(const structure::MethodDeclarationSyntax& node , bool callVirtualBase) {}

void Visitor::visitEnd(const structure::MethodDeclarationSyntax& node , bool callVirtualBase) { }

void Visitor::visit(const structure::NameColonSyntax& node , bool callVirtualBase) {}

void Visitor::visitEnd(const structure::NameColonSyntax& node , bool callVirtualBase) { }

void Visitor::visit(const structure::NameEqualsSyntax& node , bool callVirtualBase) {}

void Visitor::visitEnd(const structure::NameEqualsSyntax& node , bool callVirtualBase) { }

void Visitor::visit(const structure::NameMemberCrefSyntax& node , bool callVirtualBase) {}

void Visitor::visitEnd(const structure::NameMemberCrefSyntax& node , bool callVirtualBase) { }

void Visitor::visit(const structure::NamespaceDeclarationSyntax& node , bool callVirtualBase) {}

void Visitor::visitEnd(const structure::NamespaceDeclarationSyntax& node , bool callVirtualBase) { }

void Visitor::visit(const structure::OperatorDeclarationSyntax& node , bool callVirtualBase) {}

void Visitor::visitEnd(const structure::OperatorDeclarationSyntax& node , bool callVirtualBase) { }

void Visitor::visit(const structure::OperatorMemberCrefSyntax& node , bool callVirtualBase) {}

void Visitor::visitEnd(const structure::OperatorMemberCrefSyntax& node , bool callVirtualBase) { }

void Visitor::visit(const structure::OrderByClauseSyntax& node , bool callVirtualBase) {}

void Visitor::visitEnd(const structure::OrderByClauseSyntax& node , bool callVirtualBase) { }

void Visitor::visit(const structure::OrderingSyntax& node , bool callVirtualBase) {}

void Visitor::visitEnd(const structure::OrderingSyntax& node , bool callVirtualBase) { }

void Visitor::visit(const structure::ParameterListSyntax& node , bool callVirtualBase) {}

void Visitor::visitEnd(const structure::ParameterListSyntax& node , bool callVirtualBase) { }

void Visitor::visit(const structure::ParameterSyntax& node , bool callVirtualBase) {}

void Visitor::visitEnd(const structure::ParameterSyntax& node , bool callVirtualBase) { }

void Visitor::visit(const structure::PropertyDeclarationSyntax& node , bool callVirtualBase) {}

void Visitor::visitEnd(const structure::PropertyDeclarationSyntax& node , bool callVirtualBase) { }

void Visitor::visit(const structure::QualifiedCrefSyntax& node , bool callVirtualBase) {}

void Visitor::visitEnd(const structure::QualifiedCrefSyntax& node , bool callVirtualBase) { }

void Visitor::visit(const structure::QueryBodySyntax& node , bool callVirtualBase) {}

void Visitor::visitEnd(const structure::QueryBodySyntax& node , bool callVirtualBase) { }

void Visitor::visit(const structure::QueryContinuationSyntax& node , bool callVirtualBase) {}

void Visitor::visitEnd(const structure::QueryContinuationSyntax& node , bool callVirtualBase) { }

void Visitor::visit(const structure::SelectClauseSyntax& node , bool callVirtualBase) {}

void Visitor::visitEnd(const structure::SelectClauseSyntax& node , bool callVirtualBase) { }

void Visitor::visit(const structure::SimpleBaseTypeSyntax& node , bool callVirtualBase) {}

void Visitor::visitEnd(const structure::SimpleBaseTypeSyntax& node , bool callVirtualBase) { }

void Visitor::visit(const structure::StructDeclarationSyntax& node , bool callVirtualBase) {}

void Visitor::visitEnd(const structure::StructDeclarationSyntax& node , bool callVirtualBase) { }

void Visitor::visit(const structure::SwitchSectionSyntax& node , bool callVirtualBase) {}

void Visitor::visitEnd(const structure::SwitchSectionSyntax& node , bool callVirtualBase) { }

void Visitor::visit(const structure::SyntaxToken& node , bool callVirtualBase) {}

void Visitor::visitEnd(const structure::SyntaxToken& node , bool callVirtualBase) { }

void Visitor::visit(const structure::TypeArgumentListSyntax& node , bool callVirtualBase) {}

void Visitor::visitEnd(const structure::TypeArgumentListSyntax& node , bool callVirtualBase) { }

void Visitor::visit(const structure::TypeConstraintSyntax& node , bool callVirtualBase) {}

void Visitor::visitEnd(const structure::TypeConstraintSyntax& node , bool callVirtualBase) { }

void Visitor::visit(const structure::TypeCrefSyntax& node , bool callVirtualBase) {}

void Visitor::visitEnd(const structure::TypeCrefSyntax& node , bool callVirtualBase) { }

void Visitor::visit(const structure::TypeParameterConstraintClauseSyntax& node , bool callVirtualBase) {}

void Visitor::visitEnd(const structure::TypeParameterConstraintClauseSyntax& node , bool callVirtualBase) { }

void Visitor::visit(const structure::TypeParameterListSyntax& node , bool callVirtualBase) {}

void Visitor::visitEnd(const structure::TypeParameterListSyntax& node , bool callVirtualBase) { }

void Visitor::visit(const structure::TypeParameterSyntax& node , bool callVirtualBase) {}

void Visitor::visitEnd(const structure::TypeParameterSyntax& node , bool callVirtualBase) { }

void Visitor::visit(const structure::UsingDirectiveSyntax& node , bool callVirtualBase) {}

void Visitor::visitEnd(const structure::UsingDirectiveSyntax& node , bool callVirtualBase) { }

void Visitor::visit(const structure::VariableDeclarationSyntax& node , bool callVirtualBase) {}

void Visitor::visitEnd(const structure::VariableDeclarationSyntax& node , bool callVirtualBase) { }

void Visitor::visit(const structure::VariableDeclaratorSyntax& node , bool callVirtualBase) {}

void Visitor::visitEnd(const structure::VariableDeclaratorSyntax& node , bool callVirtualBase) { }

void Visitor::visit(const structure::WhereClauseSyntax& node , bool callVirtualBase) {}

void Visitor::visitEnd(const structure::WhereClauseSyntax& node , bool callVirtualBase) { }

void Visitor::visit(const structure::XmlCDataSectionSyntax& node , bool callVirtualBase) {}

void Visitor::visitEnd(const structure::XmlCDataSectionSyntax& node , bool callVirtualBase) { }

void Visitor::visit(const structure::XmlCommentSyntax& node , bool callVirtualBase) {}

void Visitor::visitEnd(const structure::XmlCommentSyntax& node , bool callVirtualBase) { }

void Visitor::visit(const structure::XmlCrefAttributeSyntax& node , bool callVirtualBase) {}

void Visitor::visitEnd(const structure::XmlCrefAttributeSyntax& node , bool callVirtualBase) { }

void Visitor::visit(const structure::XmlElementEndTagSyntax& node , bool callVirtualBase) {}

void Visitor::visitEnd(const structure::XmlElementEndTagSyntax& node , bool callVirtualBase) { }

void Visitor::visit(const structure::XmlElementStartTagSyntax& node , bool callVirtualBase) {}

void Visitor::visitEnd(const structure::XmlElementStartTagSyntax& node , bool callVirtualBase) { }

void Visitor::visit(const structure::XmlElementSyntax& node , bool callVirtualBase) {}

void Visitor::visitEnd(const structure::XmlElementSyntax& node , bool callVirtualBase) { }

void Visitor::visit(const structure::XmlEmptyElementSyntax& node , bool callVirtualBase) {}

void Visitor::visitEnd(const structure::XmlEmptyElementSyntax& node , bool callVirtualBase) { }

void Visitor::visit(const structure::XmlNameAttributeSyntax& node , bool callVirtualBase) {}

void Visitor::visitEnd(const structure::XmlNameAttributeSyntax& node , bool callVirtualBase) { }

void Visitor::visit(const structure::XmlNameSyntax& node , bool callVirtualBase) {}

void Visitor::visitEnd(const structure::XmlNameSyntax& node , bool callVirtualBase) { }

void Visitor::visit(const structure::XmlPrefixSyntax& node , bool callVirtualBase) {}

void Visitor::visitEnd(const structure::XmlPrefixSyntax& node , bool callVirtualBase) { }

void Visitor::visit(const structure::XmlProcessingInstructionSyntax& node , bool callVirtualBase) {}

void Visitor::visitEnd(const structure::XmlProcessingInstructionSyntax& node , bool callVirtualBase) { }

void Visitor::visit(const structure::XmlTextAttributeSyntax& node , bool callVirtualBase) {}

void Visitor::visitEnd(const structure::XmlTextAttributeSyntax& node , bool callVirtualBase) { }

void Visitor::visit(const structure::XmlTextSyntax& node , bool callVirtualBase) {}

void Visitor::visitEnd(const structure::XmlTextSyntax& node , bool callVirtualBase) { }

void Visitor::visitAliasQualifiedNameSyntax_Alias(const expression::AliasQualifiedNameSyntax& begin, const expression::IdentifierNameSyntax& end) { }

void Visitor::visitEndAliasQualifiedNameSyntax_Alias(const expression::AliasQualifiedNameSyntax& begin, const expression::IdentifierNameSyntax& end) { }

void Visitor::visitAliasQualifiedNameSyntax_Name(const expression::AliasQualifiedNameSyntax& begin, const expression::SimpleNameSyntax& end) { }

void Visitor::visitEndAliasQualifiedNameSyntax_Name(const expression::AliasQualifiedNameSyntax& begin, const expression::SimpleNameSyntax& end) { }

void Visitor::visitAnonymousFunctionExpressionSyntax_Body(const expression::AnonymousFunctionExpressionSyntax& begin, const base::Positioned& end) { }

void Visitor::visitEndAnonymousFunctionExpressionSyntax_Body(const expression::AnonymousFunctionExpressionSyntax& begin, const base::Positioned& end) { }

void Visitor::visitAnonymousMethodExpressionSyntax_ParameterList(const expression::AnonymousMethodExpressionSyntax& begin, const structure::ParameterListSyntax& end) { }

void Visitor::visitEndAnonymousMethodExpressionSyntax_ParameterList(const expression::AnonymousMethodExpressionSyntax& begin, const structure::ParameterListSyntax& end) { }

void Visitor::visitAnonymousObjectCreationExpressionSyntax_Initializers(const expression::AnonymousObjectCreationExpressionSyntax& begin, const structure::AnonymousObjectMemberDeclaratorSyntax& end) { }

void Visitor::visitEndAnonymousObjectCreationExpressionSyntax_Initializers(const expression::AnonymousObjectCreationExpressionSyntax& begin, const structure::AnonymousObjectMemberDeclaratorSyntax& end) { }

void Visitor::visitArrayCreationExpressionSyntax_Initializer(const expression::ArrayCreationExpressionSyntax& begin, const expression::InitializerExpressionSyntax& end) { }

void Visitor::visitEndArrayCreationExpressionSyntax_Initializer(const expression::ArrayCreationExpressionSyntax& begin, const expression::InitializerExpressionSyntax& end) { }

void Visitor::visitArrayCreationExpressionSyntax_Type(const expression::ArrayCreationExpressionSyntax& begin, const expression::ArrayTypeSyntax& end) { }

void Visitor::visitEndArrayCreationExpressionSyntax_Type(const expression::ArrayCreationExpressionSyntax& begin, const expression::ArrayTypeSyntax& end) { }

void Visitor::visitArrayTypeSyntax_ElementType(const expression::ArrayTypeSyntax& begin, const expression::TypeSyntax& end) { }

void Visitor::visitEndArrayTypeSyntax_ElementType(const expression::ArrayTypeSyntax& begin, const expression::TypeSyntax& end) { }

void Visitor::visitArrayTypeSyntax_RankSpecifiers(const expression::ArrayTypeSyntax& begin, const structure::ArrayRankSpecifierSyntax& end) { }

void Visitor::visitEndArrayTypeSyntax_RankSpecifiers(const expression::ArrayTypeSyntax& begin, const structure::ArrayRankSpecifierSyntax& end) { }

void Visitor::visitAssignmentExpressionSyntax_EventAccessorCall(const expression::AssignmentExpressionSyntax& begin, const structure::AccessorDeclarationSyntax& end) { }

void Visitor::visitEndAssignmentExpressionSyntax_EventAccessorCall(const expression::AssignmentExpressionSyntax& begin, const structure::AccessorDeclarationSyntax& end) { }

void Visitor::visitAssignmentExpressionSyntax_Left(const expression::AssignmentExpressionSyntax& begin, const expression::ExpressionSyntax& end) { }

void Visitor::visitEndAssignmentExpressionSyntax_Left(const expression::AssignmentExpressionSyntax& begin, const expression::ExpressionSyntax& end) { }

void Visitor::visitAssignmentExpressionSyntax_OverloadedOperatorCall(const expression::AssignmentExpressionSyntax& begin, const structure::OperatorDeclarationSyntax& end) { }

void Visitor::visitEndAssignmentExpressionSyntax_OverloadedOperatorCall(const expression::AssignmentExpressionSyntax& begin, const structure::OperatorDeclarationSyntax& end) { }

void Visitor::visitAssignmentExpressionSyntax_Right(const expression::AssignmentExpressionSyntax& begin, const expression::ExpressionSyntax& end) { }

void Visitor::visitEndAssignmentExpressionSyntax_Right(const expression::AssignmentExpressionSyntax& begin, const expression::ExpressionSyntax& end) { }

void Visitor::visitAwaitExpressionSyntax_Expression(const expression::AwaitExpressionSyntax& begin, const expression::ExpressionSyntax& end) { }

void Visitor::visitEndAwaitExpressionSyntax_Expression(const expression::AwaitExpressionSyntax& begin, const expression::ExpressionSyntax& end) { }

void Visitor::visitBinaryExpressionSyntax_Left(const expression::BinaryExpressionSyntax& begin, const expression::ExpressionSyntax& end) { }

void Visitor::visitEndBinaryExpressionSyntax_Left(const expression::BinaryExpressionSyntax& begin, const expression::ExpressionSyntax& end) { }

void Visitor::visitBinaryExpressionSyntax_OverloadedOperatorCall(const expression::BinaryExpressionSyntax& begin, const structure::OperatorDeclarationSyntax& end) { }

void Visitor::visitEndBinaryExpressionSyntax_OverloadedOperatorCall(const expression::BinaryExpressionSyntax& begin, const structure::OperatorDeclarationSyntax& end) { }

void Visitor::visitBinaryExpressionSyntax_Right(const expression::BinaryExpressionSyntax& begin, const expression::ExpressionSyntax& end) { }

void Visitor::visitEndBinaryExpressionSyntax_Right(const expression::BinaryExpressionSyntax& begin, const expression::ExpressionSyntax& end) { }

void Visitor::visitCastExpressionSyntax_ConversionOperatorCall(const expression::CastExpressionSyntax& begin, const structure::ConversionOperatorDeclarationSyntax& end) { }

void Visitor::visitEndCastExpressionSyntax_ConversionOperatorCall(const expression::CastExpressionSyntax& begin, const structure::ConversionOperatorDeclarationSyntax& end) { }

void Visitor::visitCastExpressionSyntax_Expression(const expression::CastExpressionSyntax& begin, const expression::ExpressionSyntax& end) { }

void Visitor::visitEndCastExpressionSyntax_Expression(const expression::CastExpressionSyntax& begin, const expression::ExpressionSyntax& end) { }

void Visitor::visitCastExpressionSyntax_Type(const expression::CastExpressionSyntax& begin, const expression::TypeSyntax& end) { }

void Visitor::visitEndCastExpressionSyntax_Type(const expression::CastExpressionSyntax& begin, const expression::TypeSyntax& end) { }

void Visitor::visitCheckedExpressionSyntax_Expression(const expression::CheckedExpressionSyntax& begin, const expression::ExpressionSyntax& end) { }

void Visitor::visitEndCheckedExpressionSyntax_Expression(const expression::CheckedExpressionSyntax& begin, const expression::ExpressionSyntax& end) { }

void Visitor::visitConditionalAccessExpressionSyntax_Expression(const expression::ConditionalAccessExpressionSyntax& begin, const expression::ExpressionSyntax& end) { }

void Visitor::visitEndConditionalAccessExpressionSyntax_Expression(const expression::ConditionalAccessExpressionSyntax& begin, const expression::ExpressionSyntax& end) { }

void Visitor::visitConditionalAccessExpressionSyntax_WhenNotNull(const expression::ConditionalAccessExpressionSyntax& begin, const expression::ExpressionSyntax& end) { }

void Visitor::visitEndConditionalAccessExpressionSyntax_WhenNotNull(const expression::ConditionalAccessExpressionSyntax& begin, const expression::ExpressionSyntax& end) { }

void Visitor::visitConditionalExpressionSyntax_Condition(const expression::ConditionalExpressionSyntax& begin, const expression::ExpressionSyntax& end) { }

void Visitor::visitEndConditionalExpressionSyntax_Condition(const expression::ConditionalExpressionSyntax& begin, const expression::ExpressionSyntax& end) { }

void Visitor::visitConditionalExpressionSyntax_WhenFalse(const expression::ConditionalExpressionSyntax& begin, const expression::ExpressionSyntax& end) { }

void Visitor::visitEndConditionalExpressionSyntax_WhenFalse(const expression::ConditionalExpressionSyntax& begin, const expression::ExpressionSyntax& end) { }

void Visitor::visitConditionalExpressionSyntax_WhenTrue(const expression::ConditionalExpressionSyntax& begin, const expression::ExpressionSyntax& end) { }

void Visitor::visitEndConditionalExpressionSyntax_WhenTrue(const expression::ConditionalExpressionSyntax& begin, const expression::ExpressionSyntax& end) { }

void Visitor::visitDefaultExpressionSyntax_Type(const expression::DefaultExpressionSyntax& begin, const expression::TypeSyntax& end) { }

void Visitor::visitEndDefaultExpressionSyntax_Type(const expression::DefaultExpressionSyntax& begin, const expression::TypeSyntax& end) { }

void Visitor::visitElementAccessExpressionSyntax_AccessorCall(const expression::ElementAccessExpressionSyntax& begin, const structure::AccessorDeclarationSyntax& end) { }

void Visitor::visitEndElementAccessExpressionSyntax_AccessorCall(const expression::ElementAccessExpressionSyntax& begin, const structure::AccessorDeclarationSyntax& end) { }

void Visitor::visitElementAccessExpressionSyntax_ArgumentList(const expression::ElementAccessExpressionSyntax& begin, const structure::BracketedArgumentListSyntax& end) { }

void Visitor::visitEndElementAccessExpressionSyntax_ArgumentList(const expression::ElementAccessExpressionSyntax& begin, const structure::BracketedArgumentListSyntax& end) { }

void Visitor::visitElementAccessExpressionSyntax_Expression(const expression::ElementAccessExpressionSyntax& begin, const expression::ExpressionSyntax& end) { }

void Visitor::visitEndElementAccessExpressionSyntax_Expression(const expression::ElementAccessExpressionSyntax& begin, const expression::ExpressionSyntax& end) { }

void Visitor::visitElementBindingExpressionSyntax_ArgumentList(const expression::ElementBindingExpressionSyntax& begin, const structure::BracketedArgumentListSyntax& end) { }

void Visitor::visitEndElementBindingExpressionSyntax_ArgumentList(const expression::ElementBindingExpressionSyntax& begin, const structure::BracketedArgumentListSyntax& end) { }

void Visitor::visitGenericNameSyntax_TypeArgumentList(const expression::GenericNameSyntax& begin, const structure::TypeArgumentListSyntax& end) { }

void Visitor::visitEndGenericNameSyntax_TypeArgumentList(const expression::GenericNameSyntax& begin, const structure::TypeArgumentListSyntax& end) { }

void Visitor::visitIdentifierNameSyntax_AccessorCall(const expression::IdentifierNameSyntax& begin, const structure::AccessorDeclarationSyntax& end) { }

void Visitor::visitEndIdentifierNameSyntax_AccessorCall(const expression::IdentifierNameSyntax& begin, const structure::AccessorDeclarationSyntax& end) { }

void Visitor::visitIdentifierNameSyntax_Declaration(const expression::IdentifierNameSyntax& begin, const base::Positioned& end) { }

void Visitor::visitEndIdentifierNameSyntax_Declaration(const expression::IdentifierNameSyntax& begin, const base::Positioned& end) { }

void Visitor::visitImplicitArrayCreationExpressionSyntax_Initializer(const expression::ImplicitArrayCreationExpressionSyntax& begin, const expression::InitializerExpressionSyntax& end) { }

void Visitor::visitEndImplicitArrayCreationExpressionSyntax_Initializer(const expression::ImplicitArrayCreationExpressionSyntax& begin, const expression::InitializerExpressionSyntax& end) { }

void Visitor::visitImplicitElementAccessSyntax_ArgumentList(const expression::ImplicitElementAccessSyntax& begin, const structure::BracketedArgumentListSyntax& end) { }

void Visitor::visitEndImplicitElementAccessSyntax_ArgumentList(const expression::ImplicitElementAccessSyntax& begin, const structure::BracketedArgumentListSyntax& end) { }

void Visitor::visitInitializerExpressionSyntax_Expressions(const expression::InitializerExpressionSyntax& begin, const expression::ExpressionSyntax& end) { }

void Visitor::visitEndInitializerExpressionSyntax_Expressions(const expression::InitializerExpressionSyntax& begin, const expression::ExpressionSyntax& end) { }

void Visitor::visitInterpolatedStringExpressionSyntax_Contents(const expression::InterpolatedStringExpressionSyntax& begin, const structure::InterpolatedStringContentSyntax& end) { }

void Visitor::visitEndInterpolatedStringExpressionSyntax_Contents(const expression::InterpolatedStringExpressionSyntax& begin, const structure::InterpolatedStringContentSyntax& end) { }

void Visitor::visitInvocationExpressionSyntax_ArgumentList(const expression::InvocationExpressionSyntax& begin, const structure::ArgumentListSyntax& end) { }

void Visitor::visitEndInvocationExpressionSyntax_ArgumentList(const expression::InvocationExpressionSyntax& begin, const structure::ArgumentListSyntax& end) { }

void Visitor::visitInvocationExpressionSyntax_Expression(const expression::InvocationExpressionSyntax& begin, const expression::ExpressionSyntax& end) { }

void Visitor::visitEndInvocationExpressionSyntax_Expression(const expression::InvocationExpressionSyntax& begin, const expression::ExpressionSyntax& end) { }

void Visitor::visitInvocationExpressionSyntax_MethodCall(const expression::InvocationExpressionSyntax& begin, const structure::MethodDeclarationSyntax& end) { }

void Visitor::visitEndInvocationExpressionSyntax_MethodCall(const expression::InvocationExpressionSyntax& begin, const structure::MethodDeclarationSyntax& end) { }

void Visitor::visitMakeRefExpressionSyntax_Expression(const expression::MakeRefExpressionSyntax& begin, const expression::ExpressionSyntax& end) { }

void Visitor::visitEndMakeRefExpressionSyntax_Expression(const expression::MakeRefExpressionSyntax& begin, const expression::ExpressionSyntax& end) { }

void Visitor::visitMemberAccessExpressionSyntax_Expression(const expression::MemberAccessExpressionSyntax& begin, const expression::ExpressionSyntax& end) { }

void Visitor::visitEndMemberAccessExpressionSyntax_Expression(const expression::MemberAccessExpressionSyntax& begin, const expression::ExpressionSyntax& end) { }

void Visitor::visitMemberAccessExpressionSyntax_Name(const expression::MemberAccessExpressionSyntax& begin, const expression::SimpleNameSyntax& end) { }

void Visitor::visitEndMemberAccessExpressionSyntax_Name(const expression::MemberAccessExpressionSyntax& begin, const expression::SimpleNameSyntax& end) { }

void Visitor::visitMemberBindingExpressionSyntax_Name(const expression::MemberBindingExpressionSyntax& begin, const expression::SimpleNameSyntax& end) { }

void Visitor::visitEndMemberBindingExpressionSyntax_Name(const expression::MemberBindingExpressionSyntax& begin, const expression::SimpleNameSyntax& end) { }

void Visitor::visitNullableTypeSyntax_ElementType(const expression::NullableTypeSyntax& begin, const expression::TypeSyntax& end) { }

void Visitor::visitEndNullableTypeSyntax_ElementType(const expression::NullableTypeSyntax& begin, const expression::TypeSyntax& end) { }

void Visitor::visitObjectCreationExpressionSyntax_ArgumentList(const expression::ObjectCreationExpressionSyntax& begin, const structure::ArgumentListSyntax& end) { }

void Visitor::visitEndObjectCreationExpressionSyntax_ArgumentList(const expression::ObjectCreationExpressionSyntax& begin, const structure::ArgumentListSyntax& end) { }

void Visitor::visitObjectCreationExpressionSyntax_ConstructorCall(const expression::ObjectCreationExpressionSyntax& begin, const structure::ConstructorDeclarationSyntax& end) { }

void Visitor::visitEndObjectCreationExpressionSyntax_ConstructorCall(const expression::ObjectCreationExpressionSyntax& begin, const structure::ConstructorDeclarationSyntax& end) { }

void Visitor::visitObjectCreationExpressionSyntax_Initializer(const expression::ObjectCreationExpressionSyntax& begin, const expression::InitializerExpressionSyntax& end) { }

void Visitor::visitEndObjectCreationExpressionSyntax_Initializer(const expression::ObjectCreationExpressionSyntax& begin, const expression::InitializerExpressionSyntax& end) { }

void Visitor::visitObjectCreationExpressionSyntax_Type(const expression::ObjectCreationExpressionSyntax& begin, const expression::TypeSyntax& end) { }

void Visitor::visitEndObjectCreationExpressionSyntax_Type(const expression::ObjectCreationExpressionSyntax& begin, const expression::TypeSyntax& end) { }

void Visitor::visitParenthesizedExpressionSyntax_Expression(const expression::ParenthesizedExpressionSyntax& begin, const expression::ExpressionSyntax& end) { }

void Visitor::visitEndParenthesizedExpressionSyntax_Expression(const expression::ParenthesizedExpressionSyntax& begin, const expression::ExpressionSyntax& end) { }

void Visitor::visitParenthesizedLambdaExpressionSyntax_ParameterList(const expression::ParenthesizedLambdaExpressionSyntax& begin, const structure::ParameterListSyntax& end) { }

void Visitor::visitEndParenthesizedLambdaExpressionSyntax_ParameterList(const expression::ParenthesizedLambdaExpressionSyntax& begin, const structure::ParameterListSyntax& end) { }

void Visitor::visitPointerTypeSyntax_ElementType(const expression::PointerTypeSyntax& begin, const expression::TypeSyntax& end) { }

void Visitor::visitEndPointerTypeSyntax_ElementType(const expression::PointerTypeSyntax& begin, const expression::TypeSyntax& end) { }

void Visitor::visitPostfixUnaryExpressionSyntax_Operand(const expression::PostfixUnaryExpressionSyntax& begin, const expression::ExpressionSyntax& end) { }

void Visitor::visitEndPostfixUnaryExpressionSyntax_Operand(const expression::PostfixUnaryExpressionSyntax& begin, const expression::ExpressionSyntax& end) { }

void Visitor::visitPostfixUnaryExpressionSyntax_OverloadedOperatorCall(const expression::PostfixUnaryExpressionSyntax& begin, const structure::OperatorDeclarationSyntax& end) { }

void Visitor::visitEndPostfixUnaryExpressionSyntax_OverloadedOperatorCall(const expression::PostfixUnaryExpressionSyntax& begin, const structure::OperatorDeclarationSyntax& end) { }

void Visitor::visitPrefixUnaryExpressionSyntax_Operand(const expression::PrefixUnaryExpressionSyntax& begin, const expression::ExpressionSyntax& end) { }

void Visitor::visitEndPrefixUnaryExpressionSyntax_Operand(const expression::PrefixUnaryExpressionSyntax& begin, const expression::ExpressionSyntax& end) { }

void Visitor::visitPrefixUnaryExpressionSyntax_OverloadedOperatorCall(const expression::PrefixUnaryExpressionSyntax& begin, const structure::OperatorDeclarationSyntax& end) { }

void Visitor::visitEndPrefixUnaryExpressionSyntax_OverloadedOperatorCall(const expression::PrefixUnaryExpressionSyntax& begin, const structure::OperatorDeclarationSyntax& end) { }

void Visitor::visitQualifiedNameSyntax_Left(const expression::QualifiedNameSyntax& begin, const expression::NameSyntax& end) { }

void Visitor::visitEndQualifiedNameSyntax_Left(const expression::QualifiedNameSyntax& begin, const expression::NameSyntax& end) { }

void Visitor::visitQualifiedNameSyntax_Right(const expression::QualifiedNameSyntax& begin, const expression::SimpleNameSyntax& end) { }

void Visitor::visitEndQualifiedNameSyntax_Right(const expression::QualifiedNameSyntax& begin, const expression::SimpleNameSyntax& end) { }

void Visitor::visitQueryExpressionSyntax_Body(const expression::QueryExpressionSyntax& begin, const structure::QueryBodySyntax& end) { }

void Visitor::visitEndQueryExpressionSyntax_Body(const expression::QueryExpressionSyntax& begin, const structure::QueryBodySyntax& end) { }

void Visitor::visitQueryExpressionSyntax_FromClause(const expression::QueryExpressionSyntax& begin, const structure::FromClauseSyntax& end) { }

void Visitor::visitEndQueryExpressionSyntax_FromClause(const expression::QueryExpressionSyntax& begin, const structure::FromClauseSyntax& end) { }

void Visitor::visitRefTypeExpressionSyntax_Expression(const expression::RefTypeExpressionSyntax& begin, const expression::ExpressionSyntax& end) { }

void Visitor::visitEndRefTypeExpressionSyntax_Expression(const expression::RefTypeExpressionSyntax& begin, const expression::ExpressionSyntax& end) { }

void Visitor::visitRefValueExpressionSyntax_Expression(const expression::RefValueExpressionSyntax& begin, const expression::ExpressionSyntax& end) { }

void Visitor::visitEndRefValueExpressionSyntax_Expression(const expression::RefValueExpressionSyntax& begin, const expression::ExpressionSyntax& end) { }

void Visitor::visitRefValueExpressionSyntax_Type(const expression::RefValueExpressionSyntax& begin, const expression::TypeSyntax& end) { }

void Visitor::visitEndRefValueExpressionSyntax_Type(const expression::RefValueExpressionSyntax& begin, const expression::TypeSyntax& end) { }

void Visitor::visitSimpleLambdaExpressionSyntax_Parameter(const expression::SimpleLambdaExpressionSyntax& begin, const structure::ParameterSyntax& end) { }

void Visitor::visitEndSimpleLambdaExpressionSyntax_Parameter(const expression::SimpleLambdaExpressionSyntax& begin, const structure::ParameterSyntax& end) { }

void Visitor::visitSizeOfExpressionSyntax_Type(const expression::SizeOfExpressionSyntax& begin, const expression::TypeSyntax& end) { }

void Visitor::visitEndSizeOfExpressionSyntax_Type(const expression::SizeOfExpressionSyntax& begin, const expression::TypeSyntax& end) { }

void Visitor::visitStackAllocArrayCreationExpressionSyntax_Type(const expression::StackAllocArrayCreationExpressionSyntax& begin, const expression::TypeSyntax& end) { }

void Visitor::visitEndStackAllocArrayCreationExpressionSyntax_Type(const expression::StackAllocArrayCreationExpressionSyntax& begin, const expression::TypeSyntax& end) { }

void Visitor::visitTypeOfExpressionSyntax_Type(const expression::TypeOfExpressionSyntax& begin, const expression::TypeSyntax& end) { }

void Visitor::visitEndTypeOfExpressionSyntax_Type(const expression::TypeOfExpressionSyntax& begin, const expression::TypeSyntax& end) { }

void Visitor::visitTypeSyntax_OriginalDefinition(const expression::TypeSyntax& begin, const structure::MemberDeclarationSyntax& end) { }

void Visitor::visitEndTypeSyntax_OriginalDefinition(const expression::TypeSyntax& begin, const structure::MemberDeclarationSyntax& end) { }

void Visitor::visitBlockSyntax_Statements(const statement::BlockSyntax& begin, const statement::StatementSyntax& end) { }

void Visitor::visitEndBlockSyntax_Statements(const statement::BlockSyntax& begin, const statement::StatementSyntax& end) { }

void Visitor::visitCheckedStatementSyntax_Block(const statement::CheckedStatementSyntax& begin, const statement::BlockSyntax& end) { }

void Visitor::visitEndCheckedStatementSyntax_Block(const statement::CheckedStatementSyntax& begin, const statement::BlockSyntax& end) { }

void Visitor::visitDoStatementSyntax_Condition(const statement::DoStatementSyntax& begin, const expression::ExpressionSyntax& end) { }

void Visitor::visitEndDoStatementSyntax_Condition(const statement::DoStatementSyntax& begin, const expression::ExpressionSyntax& end) { }

void Visitor::visitDoStatementSyntax_Statement(const statement::DoStatementSyntax& begin, const statement::StatementSyntax& end) { }

void Visitor::visitEndDoStatementSyntax_Statement(const statement::DoStatementSyntax& begin, const statement::StatementSyntax& end) { }

void Visitor::visitExpressionStatementSyntax_Expression(const statement::ExpressionStatementSyntax& begin, const expression::ExpressionSyntax& end) { }

void Visitor::visitEndExpressionStatementSyntax_Expression(const statement::ExpressionStatementSyntax& begin, const expression::ExpressionSyntax& end) { }

void Visitor::visitFixedStatementSyntax_Declaration(const statement::FixedStatementSyntax& begin, const structure::VariableDeclarationSyntax& end) { }

void Visitor::visitEndFixedStatementSyntax_Declaration(const statement::FixedStatementSyntax& begin, const structure::VariableDeclarationSyntax& end) { }

void Visitor::visitFixedStatementSyntax_Statement(const statement::FixedStatementSyntax& begin, const statement::StatementSyntax& end) { }

void Visitor::visitEndFixedStatementSyntax_Statement(const statement::FixedStatementSyntax& begin, const statement::StatementSyntax& end) { }

void Visitor::visitForEachStatementSyntax_Expression(const statement::ForEachStatementSyntax& begin, const expression::ExpressionSyntax& end) { }

void Visitor::visitEndForEachStatementSyntax_Expression(const statement::ForEachStatementSyntax& begin, const expression::ExpressionSyntax& end) { }

void Visitor::visitForEachStatementSyntax_Statement(const statement::ForEachStatementSyntax& begin, const statement::StatementSyntax& end) { }

void Visitor::visitEndForEachStatementSyntax_Statement(const statement::ForEachStatementSyntax& begin, const statement::StatementSyntax& end) { }

void Visitor::visitForEachStatementSyntax_Type(const statement::ForEachStatementSyntax& begin, const expression::TypeSyntax& end) { }

void Visitor::visitEndForEachStatementSyntax_Type(const statement::ForEachStatementSyntax& begin, const expression::TypeSyntax& end) { }

void Visitor::visitForStatementSyntax_Condition(const statement::ForStatementSyntax& begin, const expression::ExpressionSyntax& end) { }

void Visitor::visitEndForStatementSyntax_Condition(const statement::ForStatementSyntax& begin, const expression::ExpressionSyntax& end) { }

void Visitor::visitForStatementSyntax_Declaration(const statement::ForStatementSyntax& begin, const structure::VariableDeclarationSyntax& end) { }

void Visitor::visitEndForStatementSyntax_Declaration(const statement::ForStatementSyntax& begin, const structure::VariableDeclarationSyntax& end) { }

void Visitor::visitForStatementSyntax_Incrementors(const statement::ForStatementSyntax& begin, const expression::ExpressionSyntax& end) { }

void Visitor::visitEndForStatementSyntax_Incrementors(const statement::ForStatementSyntax& begin, const expression::ExpressionSyntax& end) { }

void Visitor::visitForStatementSyntax_Initializers(const statement::ForStatementSyntax& begin, const expression::ExpressionSyntax& end) { }

void Visitor::visitEndForStatementSyntax_Initializers(const statement::ForStatementSyntax& begin, const expression::ExpressionSyntax& end) { }

void Visitor::visitForStatementSyntax_Statement(const statement::ForStatementSyntax& begin, const statement::StatementSyntax& end) { }

void Visitor::visitEndForStatementSyntax_Statement(const statement::ForStatementSyntax& begin, const statement::StatementSyntax& end) { }

void Visitor::visitGotoStatementSyntax_Expression(const statement::GotoStatementSyntax& begin, const expression::ExpressionSyntax& end) { }

void Visitor::visitEndGotoStatementSyntax_Expression(const statement::GotoStatementSyntax& begin, const expression::ExpressionSyntax& end) { }

void Visitor::visitIfStatementSyntax_Condition(const statement::IfStatementSyntax& begin, const expression::ExpressionSyntax& end) { }

void Visitor::visitEndIfStatementSyntax_Condition(const statement::IfStatementSyntax& begin, const expression::ExpressionSyntax& end) { }

void Visitor::visitIfStatementSyntax_Else(const statement::IfStatementSyntax& begin, const structure::ElseClauseSyntax& end) { }

void Visitor::visitEndIfStatementSyntax_Else(const statement::IfStatementSyntax& begin, const structure::ElseClauseSyntax& end) { }

void Visitor::visitIfStatementSyntax_Statement(const statement::IfStatementSyntax& begin, const statement::StatementSyntax& end) { }

void Visitor::visitEndIfStatementSyntax_Statement(const statement::IfStatementSyntax& begin, const statement::StatementSyntax& end) { }

void Visitor::visitLabeledStatementSyntax_Statement(const statement::LabeledStatementSyntax& begin, const statement::StatementSyntax& end) { }

void Visitor::visitEndLabeledStatementSyntax_Statement(const statement::LabeledStatementSyntax& begin, const statement::StatementSyntax& end) { }

void Visitor::visitLocalDeclarationStatementSyntax_Declaration(const statement::LocalDeclarationStatementSyntax& begin, const structure::VariableDeclarationSyntax& end) { }

void Visitor::visitEndLocalDeclarationStatementSyntax_Declaration(const statement::LocalDeclarationStatementSyntax& begin, const structure::VariableDeclarationSyntax& end) { }

void Visitor::visitLockStatementSyntax_Expression(const statement::LockStatementSyntax& begin, const expression::ExpressionSyntax& end) { }

void Visitor::visitEndLockStatementSyntax_Expression(const statement::LockStatementSyntax& begin, const expression::ExpressionSyntax& end) { }

void Visitor::visitLockStatementSyntax_Statement(const statement::LockStatementSyntax& begin, const statement::StatementSyntax& end) { }

void Visitor::visitEndLockStatementSyntax_Statement(const statement::LockStatementSyntax& begin, const statement::StatementSyntax& end) { }

void Visitor::visitReturnStatementSyntax_Expression(const statement::ReturnStatementSyntax& begin, const expression::ExpressionSyntax& end) { }

void Visitor::visitEndReturnStatementSyntax_Expression(const statement::ReturnStatementSyntax& begin, const expression::ExpressionSyntax& end) { }

void Visitor::visitSwitchStatementSyntax_Expression(const statement::SwitchStatementSyntax& begin, const expression::ExpressionSyntax& end) { }

void Visitor::visitEndSwitchStatementSyntax_Expression(const statement::SwitchStatementSyntax& begin, const expression::ExpressionSyntax& end) { }

void Visitor::visitSwitchStatementSyntax_Sections(const statement::SwitchStatementSyntax& begin, const structure::SwitchSectionSyntax& end) { }

void Visitor::visitEndSwitchStatementSyntax_Sections(const statement::SwitchStatementSyntax& begin, const structure::SwitchSectionSyntax& end) { }

void Visitor::visitThrowStatementSyntax_Expression(const statement::ThrowStatementSyntax& begin, const expression::ExpressionSyntax& end) { }

void Visitor::visitEndThrowStatementSyntax_Expression(const statement::ThrowStatementSyntax& begin, const expression::ExpressionSyntax& end) { }

void Visitor::visitTryStatementSyntax_Block(const statement::TryStatementSyntax& begin, const statement::BlockSyntax& end) { }

void Visitor::visitEndTryStatementSyntax_Block(const statement::TryStatementSyntax& begin, const statement::BlockSyntax& end) { }

void Visitor::visitTryStatementSyntax_Catches(const statement::TryStatementSyntax& begin, const structure::CatchClauseSyntax& end) { }

void Visitor::visitEndTryStatementSyntax_Catches(const statement::TryStatementSyntax& begin, const structure::CatchClauseSyntax& end) { }

void Visitor::visitTryStatementSyntax_Finally(const statement::TryStatementSyntax& begin, const structure::FinallyClauseSyntax& end) { }

void Visitor::visitEndTryStatementSyntax_Finally(const statement::TryStatementSyntax& begin, const structure::FinallyClauseSyntax& end) { }

void Visitor::visitUnsafeStatementSyntax_Block(const statement::UnsafeStatementSyntax& begin, const statement::BlockSyntax& end) { }

void Visitor::visitEndUnsafeStatementSyntax_Block(const statement::UnsafeStatementSyntax& begin, const statement::BlockSyntax& end) { }

void Visitor::visitUsingStatementSyntax_Declaration(const statement::UsingStatementSyntax& begin, const structure::VariableDeclarationSyntax& end) { }

void Visitor::visitEndUsingStatementSyntax_Declaration(const statement::UsingStatementSyntax& begin, const structure::VariableDeclarationSyntax& end) { }

void Visitor::visitUsingStatementSyntax_Expression(const statement::UsingStatementSyntax& begin, const expression::ExpressionSyntax& end) { }

void Visitor::visitEndUsingStatementSyntax_Expression(const statement::UsingStatementSyntax& begin, const expression::ExpressionSyntax& end) { }

void Visitor::visitUsingStatementSyntax_Statement(const statement::UsingStatementSyntax& begin, const statement::StatementSyntax& end) { }

void Visitor::visitEndUsingStatementSyntax_Statement(const statement::UsingStatementSyntax& begin, const statement::StatementSyntax& end) { }

void Visitor::visitWhileStatementSyntax_Condition(const statement::WhileStatementSyntax& begin, const expression::ExpressionSyntax& end) { }

void Visitor::visitEndWhileStatementSyntax_Condition(const statement::WhileStatementSyntax& begin, const expression::ExpressionSyntax& end) { }

void Visitor::visitWhileStatementSyntax_Statement(const statement::WhileStatementSyntax& begin, const statement::StatementSyntax& end) { }

void Visitor::visitEndWhileStatementSyntax_Statement(const statement::WhileStatementSyntax& begin, const statement::StatementSyntax& end) { }

void Visitor::visitYieldStatementSyntax_Expression(const statement::YieldStatementSyntax& begin, const expression::ExpressionSyntax& end) { }

void Visitor::visitEndYieldStatementSyntax_Expression(const statement::YieldStatementSyntax& begin, const expression::ExpressionSyntax& end) { }

void Visitor::visitAccessorDeclarationSyntax_AttributeLists(const structure::AccessorDeclarationSyntax& begin, const structure::AttributeListSyntax& end) { }

void Visitor::visitEndAccessorDeclarationSyntax_AttributeLists(const structure::AccessorDeclarationSyntax& begin, const structure::AttributeListSyntax& end) { }

void Visitor::visitAccessorDeclarationSyntax_Body(const structure::AccessorDeclarationSyntax& begin, const statement::BlockSyntax& end) { }

void Visitor::visitEndAccessorDeclarationSyntax_Body(const structure::AccessorDeclarationSyntax& begin, const statement::BlockSyntax& end) { }

void Visitor::visitAccessorListSyntax_Accessors(const structure::AccessorListSyntax& begin, const structure::AccessorDeclarationSyntax& end) { }

void Visitor::visitEndAccessorListSyntax_Accessors(const structure::AccessorListSyntax& begin, const structure::AccessorDeclarationSyntax& end) { }

void Visitor::visitAnonymousObjectMemberDeclaratorSyntax_Expression(const structure::AnonymousObjectMemberDeclaratorSyntax& begin, const expression::ExpressionSyntax& end) { }

void Visitor::visitEndAnonymousObjectMemberDeclaratorSyntax_Expression(const structure::AnonymousObjectMemberDeclaratorSyntax& begin, const expression::ExpressionSyntax& end) { }

void Visitor::visitAnonymousObjectMemberDeclaratorSyntax_NameEquals(const structure::AnonymousObjectMemberDeclaratorSyntax& begin, const structure::NameEqualsSyntax& end) { }

void Visitor::visitEndAnonymousObjectMemberDeclaratorSyntax_NameEquals(const structure::AnonymousObjectMemberDeclaratorSyntax& begin, const structure::NameEqualsSyntax& end) { }

void Visitor::visitArgumentSyntax_Expression(const structure::ArgumentSyntax& begin, const expression::ExpressionSyntax& end) { }

void Visitor::visitEndArgumentSyntax_Expression(const structure::ArgumentSyntax& begin, const expression::ExpressionSyntax& end) { }

void Visitor::visitArgumentSyntax_NameColon(const structure::ArgumentSyntax& begin, const structure::NameColonSyntax& end) { }

void Visitor::visitEndArgumentSyntax_NameColon(const structure::ArgumentSyntax& begin, const structure::NameColonSyntax& end) { }

void Visitor::visitArrayRankSpecifierSyntax_Sizes(const structure::ArrayRankSpecifierSyntax& begin, const expression::ExpressionSyntax& end) { }

void Visitor::visitEndArrayRankSpecifierSyntax_Sizes(const structure::ArrayRankSpecifierSyntax& begin, const expression::ExpressionSyntax& end) { }

void Visitor::visitArrowExpressionClauseSyntax_Expression(const structure::ArrowExpressionClauseSyntax& begin, const expression::ExpressionSyntax& end) { }

void Visitor::visitEndArrowExpressionClauseSyntax_Expression(const structure::ArrowExpressionClauseSyntax& begin, const expression::ExpressionSyntax& end) { }

void Visitor::visitAttributeArgumentListSyntax_Arguments(const structure::AttributeArgumentListSyntax& begin, const structure::AttributeArgumentSyntax& end) { }

void Visitor::visitEndAttributeArgumentListSyntax_Arguments(const structure::AttributeArgumentListSyntax& begin, const structure::AttributeArgumentSyntax& end) { }

void Visitor::visitAttributeArgumentSyntax_Expression(const structure::AttributeArgumentSyntax& begin, const expression::ExpressionSyntax& end) { }

void Visitor::visitEndAttributeArgumentSyntax_Expression(const structure::AttributeArgumentSyntax& begin, const expression::ExpressionSyntax& end) { }

void Visitor::visitAttributeArgumentSyntax_NameColon(const structure::AttributeArgumentSyntax& begin, const structure::NameColonSyntax& end) { }

void Visitor::visitEndAttributeArgumentSyntax_NameColon(const structure::AttributeArgumentSyntax& begin, const structure::NameColonSyntax& end) { }

void Visitor::visitAttributeArgumentSyntax_NameEquals(const structure::AttributeArgumentSyntax& begin, const structure::NameEqualsSyntax& end) { }

void Visitor::visitEndAttributeArgumentSyntax_NameEquals(const structure::AttributeArgumentSyntax& begin, const structure::NameEqualsSyntax& end) { }

void Visitor::visitAttributeListSyntax_Attributes(const structure::AttributeListSyntax& begin, const structure::AttributeSyntax& end) { }

void Visitor::visitEndAttributeListSyntax_Attributes(const structure::AttributeListSyntax& begin, const structure::AttributeSyntax& end) { }

void Visitor::visitAttributeListSyntax_Target(const structure::AttributeListSyntax& begin, const structure::AttributeTargetSpecifierSyntax& end) { }

void Visitor::visitEndAttributeListSyntax_Target(const structure::AttributeListSyntax& begin, const structure::AttributeTargetSpecifierSyntax& end) { }

void Visitor::visitAttributeSyntax_ArgumentList(const structure::AttributeSyntax& begin, const structure::AttributeArgumentListSyntax& end) { }

void Visitor::visitEndAttributeSyntax_ArgumentList(const structure::AttributeSyntax& begin, const structure::AttributeArgumentListSyntax& end) { }

void Visitor::visitAttributeSyntax_Name(const structure::AttributeSyntax& begin, const expression::NameSyntax& end) { }

void Visitor::visitEndAttributeSyntax_Name(const structure::AttributeSyntax& begin, const expression::NameSyntax& end) { }

void Visitor::visitBaseArgumentListSyntax_Arguments(const structure::BaseArgumentListSyntax& begin, const structure::ArgumentSyntax& end) { }

void Visitor::visitEndBaseArgumentListSyntax_Arguments(const structure::BaseArgumentListSyntax& begin, const structure::ArgumentSyntax& end) { }

void Visitor::visitBaseCrefParameterListSyntax_Parameters(const structure::BaseCrefParameterListSyntax& begin, const structure::CrefParameterSyntax& end) { }

void Visitor::visitEndBaseCrefParameterListSyntax_Parameters(const structure::BaseCrefParameterListSyntax& begin, const structure::CrefParameterSyntax& end) { }

void Visitor::visitBaseFieldDeclarationSyntax_AttributeLists(const structure::BaseFieldDeclarationSyntax& begin, const structure::AttributeListSyntax& end) { }

void Visitor::visitEndBaseFieldDeclarationSyntax_AttributeLists(const structure::BaseFieldDeclarationSyntax& begin, const structure::AttributeListSyntax& end) { }

void Visitor::visitBaseFieldDeclarationSyntax_Declaration(const structure::BaseFieldDeclarationSyntax& begin, const structure::VariableDeclarationSyntax& end) { }

void Visitor::visitEndBaseFieldDeclarationSyntax_Declaration(const structure::BaseFieldDeclarationSyntax& begin, const structure::VariableDeclarationSyntax& end) { }

void Visitor::visitBaseListSyntax_Types(const structure::BaseListSyntax& begin, const structure::BaseTypeSyntax& end) { }

void Visitor::visitEndBaseListSyntax_Types(const structure::BaseListSyntax& begin, const structure::BaseTypeSyntax& end) { }

void Visitor::visitBaseMethodDeclarationSyntax_AccessedEnumMembers(const structure::BaseMethodDeclarationSyntax& begin, const structure::EnumMemberDeclarationSyntax& end) { }

void Visitor::visitEndBaseMethodDeclarationSyntax_AccessedEnumMembers(const structure::BaseMethodDeclarationSyntax& begin, const structure::EnumMemberDeclarationSyntax& end) { }

void Visitor::visitBaseMethodDeclarationSyntax_AttributeLists(const structure::BaseMethodDeclarationSyntax& begin, const structure::AttributeListSyntax& end) { }

void Visitor::visitEndBaseMethodDeclarationSyntax_AttributeLists(const structure::BaseMethodDeclarationSyntax& begin, const structure::AttributeListSyntax& end) { }

void Visitor::visitBaseMethodDeclarationSyntax_Body(const structure::BaseMethodDeclarationSyntax& begin, const statement::BlockSyntax& end) { }

void Visitor::visitEndBaseMethodDeclarationSyntax_Body(const structure::BaseMethodDeclarationSyntax& begin, const statement::BlockSyntax& end) { }

void Visitor::visitBaseMethodDeclarationSyntax_ParameterList(const structure::BaseMethodDeclarationSyntax& begin, const structure::ParameterListSyntax& end) { }

void Visitor::visitEndBaseMethodDeclarationSyntax_ParameterList(const structure::BaseMethodDeclarationSyntax& begin, const structure::ParameterListSyntax& end) { }

void Visitor::visitBaseParameterListSyntax_Parameters(const structure::BaseParameterListSyntax& begin, const structure::ParameterSyntax& end) { }

void Visitor::visitEndBaseParameterListSyntax_Parameters(const structure::BaseParameterListSyntax& begin, const structure::ParameterSyntax& end) { }

void Visitor::visitBasePropertyDeclarationSyntax_AccessorList(const structure::BasePropertyDeclarationSyntax& begin, const structure::AccessorListSyntax& end) { }

void Visitor::visitEndBasePropertyDeclarationSyntax_AccessorList(const structure::BasePropertyDeclarationSyntax& begin, const structure::AccessorListSyntax& end) { }

void Visitor::visitBasePropertyDeclarationSyntax_AttributeLists(const structure::BasePropertyDeclarationSyntax& begin, const structure::AttributeListSyntax& end) { }

void Visitor::visitEndBasePropertyDeclarationSyntax_AttributeLists(const structure::BasePropertyDeclarationSyntax& begin, const structure::AttributeListSyntax& end) { }

void Visitor::visitBasePropertyDeclarationSyntax_ExplicitInterfaceSpecifier(const structure::BasePropertyDeclarationSyntax& begin, const structure::ExplicitInterfaceSpecifierSyntax& end) { }

void Visitor::visitEndBasePropertyDeclarationSyntax_ExplicitInterfaceSpecifier(const structure::BasePropertyDeclarationSyntax& begin, const structure::ExplicitInterfaceSpecifierSyntax& end) { }

void Visitor::visitBasePropertyDeclarationSyntax_Type(const structure::BasePropertyDeclarationSyntax& begin, const expression::TypeSyntax& end) { }

void Visitor::visitEndBasePropertyDeclarationSyntax_Type(const structure::BasePropertyDeclarationSyntax& begin, const expression::TypeSyntax& end) { }

void Visitor::visitBaseTypeDeclarationSyntax_AttributeLists(const structure::BaseTypeDeclarationSyntax& begin, const structure::AttributeListSyntax& end) { }

void Visitor::visitEndBaseTypeDeclarationSyntax_AttributeLists(const structure::BaseTypeDeclarationSyntax& begin, const structure::AttributeListSyntax& end) { }

void Visitor::visitBaseTypeDeclarationSyntax_BaseList(const structure::BaseTypeDeclarationSyntax& begin, const structure::BaseListSyntax& end) { }

void Visitor::visitEndBaseTypeDeclarationSyntax_BaseList(const structure::BaseTypeDeclarationSyntax& begin, const structure::BaseListSyntax& end) { }

void Visitor::visitBaseTypeSyntax_Type(const structure::BaseTypeSyntax& begin, const expression::TypeSyntax& end) { }

void Visitor::visitEndBaseTypeSyntax_Type(const structure::BaseTypeSyntax& begin, const expression::TypeSyntax& end) { }

void Visitor::visitCaseSwitchLabelSyntax_Value(const structure::CaseSwitchLabelSyntax& begin, const expression::ExpressionSyntax& end) { }

void Visitor::visitEndCaseSwitchLabelSyntax_Value(const structure::CaseSwitchLabelSyntax& begin, const expression::ExpressionSyntax& end) { }

void Visitor::visitCatchClauseSyntax_Block(const structure::CatchClauseSyntax& begin, const statement::BlockSyntax& end) { }

void Visitor::visitEndCatchClauseSyntax_Block(const structure::CatchClauseSyntax& begin, const statement::BlockSyntax& end) { }

void Visitor::visitCatchClauseSyntax_Declaration(const structure::CatchClauseSyntax& begin, const structure::CatchDeclarationSyntax& end) { }

void Visitor::visitEndCatchClauseSyntax_Declaration(const structure::CatchClauseSyntax& begin, const structure::CatchDeclarationSyntax& end) { }

void Visitor::visitCatchClauseSyntax_Filter(const structure::CatchClauseSyntax& begin, const structure::CatchFilterClauseSyntax& end) { }

void Visitor::visitEndCatchClauseSyntax_Filter(const structure::CatchClauseSyntax& begin, const structure::CatchFilterClauseSyntax& end) { }

void Visitor::visitCatchDeclarationSyntax_Type(const structure::CatchDeclarationSyntax& begin, const expression::TypeSyntax& end) { }

void Visitor::visitEndCatchDeclarationSyntax_Type(const structure::CatchDeclarationSyntax& begin, const expression::TypeSyntax& end) { }

void Visitor::visitCatchFilterClauseSyntax_FilterExpression(const structure::CatchFilterClauseSyntax& begin, const expression::ExpressionSyntax& end) { }

void Visitor::visitEndCatchFilterClauseSyntax_FilterExpression(const structure::CatchFilterClauseSyntax& begin, const expression::ExpressionSyntax& end) { }

void Visitor::visitCompilationUnitSyntax_AttributeLists(const structure::CompilationUnitSyntax& begin, const structure::AttributeListSyntax& end) { }

void Visitor::visitEndCompilationUnitSyntax_AttributeLists(const structure::CompilationUnitSyntax& begin, const structure::AttributeListSyntax& end) { }

void Visitor::visitCompilationUnitSyntax_Externs(const structure::CompilationUnitSyntax& begin, const structure::ExternAliasDirectiveSyntax& end) { }

void Visitor::visitEndCompilationUnitSyntax_Externs(const structure::CompilationUnitSyntax& begin, const structure::ExternAliasDirectiveSyntax& end) { }

void Visitor::visitCompilationUnitSyntax_Members(const structure::CompilationUnitSyntax& begin, const structure::MemberDeclarationSyntax& end) { }

void Visitor::visitEndCompilationUnitSyntax_Members(const structure::CompilationUnitSyntax& begin, const structure::MemberDeclarationSyntax& end) { }

void Visitor::visitCompilationUnitSyntax_Usings(const structure::CompilationUnitSyntax& begin, const structure::UsingDirectiveSyntax& end) { }

void Visitor::visitEndCompilationUnitSyntax_Usings(const structure::CompilationUnitSyntax& begin, const structure::UsingDirectiveSyntax& end) { }

void Visitor::visitConstructorDeclarationSyntax_Initializer(const structure::ConstructorDeclarationSyntax& begin, const structure::ConstructorInitializerSyntax& end) { }

void Visitor::visitEndConstructorDeclarationSyntax_Initializer(const structure::ConstructorDeclarationSyntax& begin, const structure::ConstructorInitializerSyntax& end) { }

void Visitor::visitConstructorInitializerSyntax_ArgumentList(const structure::ConstructorInitializerSyntax& begin, const structure::ArgumentListSyntax& end) { }

void Visitor::visitEndConstructorInitializerSyntax_ArgumentList(const structure::ConstructorInitializerSyntax& begin, const structure::ArgumentListSyntax& end) { }

void Visitor::visitConstructorInitializerSyntax_ConstructorCall(const structure::ConstructorInitializerSyntax& begin, const structure::ConstructorDeclarationSyntax& end) { }

void Visitor::visitEndConstructorInitializerSyntax_ConstructorCall(const structure::ConstructorInitializerSyntax& begin, const structure::ConstructorDeclarationSyntax& end) { }

void Visitor::visitConversionOperatorDeclarationSyntax_ExpressionBody(const structure::ConversionOperatorDeclarationSyntax& begin, const structure::ArrowExpressionClauseSyntax& end) { }

void Visitor::visitEndConversionOperatorDeclarationSyntax_ExpressionBody(const structure::ConversionOperatorDeclarationSyntax& begin, const structure::ArrowExpressionClauseSyntax& end) { }

void Visitor::visitConversionOperatorDeclarationSyntax_Type(const structure::ConversionOperatorDeclarationSyntax& begin, const expression::TypeSyntax& end) { }

void Visitor::visitEndConversionOperatorDeclarationSyntax_Type(const structure::ConversionOperatorDeclarationSyntax& begin, const expression::TypeSyntax& end) { }

void Visitor::visitConversionOperatorMemberCrefSyntax_Parameters(const structure::ConversionOperatorMemberCrefSyntax& begin, const structure::CrefParameterListSyntax& end) { }

void Visitor::visitEndConversionOperatorMemberCrefSyntax_Parameters(const structure::ConversionOperatorMemberCrefSyntax& begin, const structure::CrefParameterListSyntax& end) { }

void Visitor::visitConversionOperatorMemberCrefSyntax_Type(const structure::ConversionOperatorMemberCrefSyntax& begin, const expression::TypeSyntax& end) { }

void Visitor::visitEndConversionOperatorMemberCrefSyntax_Type(const structure::ConversionOperatorMemberCrefSyntax& begin, const expression::TypeSyntax& end) { }

void Visitor::visitCrefParameterSyntax_Type(const structure::CrefParameterSyntax& begin, const expression::TypeSyntax& end) { }

void Visitor::visitEndCrefParameterSyntax_Type(const structure::CrefParameterSyntax& begin, const expression::TypeSyntax& end) { }

void Visitor::visitDelegateDeclarationSyntax_AttributeLists(const structure::DelegateDeclarationSyntax& begin, const structure::AttributeListSyntax& end) { }

void Visitor::visitEndDelegateDeclarationSyntax_AttributeLists(const structure::DelegateDeclarationSyntax& begin, const structure::AttributeListSyntax& end) { }

void Visitor::visitDelegateDeclarationSyntax_ConstraintClauses(const structure::DelegateDeclarationSyntax& begin, const structure::TypeParameterConstraintClauseSyntax& end) { }

void Visitor::visitEndDelegateDeclarationSyntax_ConstraintClauses(const structure::DelegateDeclarationSyntax& begin, const structure::TypeParameterConstraintClauseSyntax& end) { }

void Visitor::visitDelegateDeclarationSyntax_ParameterList(const structure::DelegateDeclarationSyntax& begin, const structure::ParameterListSyntax& end) { }

void Visitor::visitEndDelegateDeclarationSyntax_ParameterList(const structure::DelegateDeclarationSyntax& begin, const structure::ParameterListSyntax& end) { }

void Visitor::visitDelegateDeclarationSyntax_ReturnType(const structure::DelegateDeclarationSyntax& begin, const expression::TypeSyntax& end) { }

void Visitor::visitEndDelegateDeclarationSyntax_ReturnType(const structure::DelegateDeclarationSyntax& begin, const expression::TypeSyntax& end) { }

void Visitor::visitElseClauseSyntax_Statement(const structure::ElseClauseSyntax& begin, const statement::StatementSyntax& end) { }

void Visitor::visitEndElseClauseSyntax_Statement(const structure::ElseClauseSyntax& begin, const statement::StatementSyntax& end) { }

void Visitor::visitEnumDeclarationSyntax_Members(const structure::EnumDeclarationSyntax& begin, const structure::EnumMemberDeclarationSyntax& end) { }

void Visitor::visitEndEnumDeclarationSyntax_Members(const structure::EnumDeclarationSyntax& begin, const structure::EnumMemberDeclarationSyntax& end) { }

void Visitor::visitEnumMemberDeclarationSyntax_AttributeLists(const structure::EnumMemberDeclarationSyntax& begin, const structure::AttributeListSyntax& end) { }

void Visitor::visitEndEnumMemberDeclarationSyntax_AttributeLists(const structure::EnumMemberDeclarationSyntax& begin, const structure::AttributeListSyntax& end) { }

void Visitor::visitEnumMemberDeclarationSyntax_EqualsValue(const structure::EnumMemberDeclarationSyntax& begin, const structure::EqualsValueClauseSyntax& end) { }

void Visitor::visitEndEnumMemberDeclarationSyntax_EqualsValue(const structure::EnumMemberDeclarationSyntax& begin, const structure::EqualsValueClauseSyntax& end) { }

void Visitor::visitEqualsValueClauseSyntax_Value(const structure::EqualsValueClauseSyntax& begin, const expression::ExpressionSyntax& end) { }

void Visitor::visitEndEqualsValueClauseSyntax_Value(const structure::EqualsValueClauseSyntax& begin, const expression::ExpressionSyntax& end) { }

void Visitor::visitExplicitInterfaceSpecifierSyntax_Name(const structure::ExplicitInterfaceSpecifierSyntax& begin, const expression::NameSyntax& end) { }

void Visitor::visitEndExplicitInterfaceSpecifierSyntax_Name(const structure::ExplicitInterfaceSpecifierSyntax& begin, const expression::NameSyntax& end) { }

void Visitor::visitFinallyClauseSyntax_Block(const structure::FinallyClauseSyntax& begin, const statement::BlockSyntax& end) { }

void Visitor::visitEndFinallyClauseSyntax_Block(const structure::FinallyClauseSyntax& begin, const statement::BlockSyntax& end) { }

void Visitor::visitFromClauseSyntax_Expression(const structure::FromClauseSyntax& begin, const expression::ExpressionSyntax& end) { }

void Visitor::visitEndFromClauseSyntax_Expression(const structure::FromClauseSyntax& begin, const expression::ExpressionSyntax& end) { }

void Visitor::visitFromClauseSyntax_Type(const structure::FromClauseSyntax& begin, const expression::TypeSyntax& end) { }

void Visitor::visitEndFromClauseSyntax_Type(const structure::FromClauseSyntax& begin, const expression::TypeSyntax& end) { }

void Visitor::visitGlobalStatementSyntax_Statement(const structure::GlobalStatementSyntax& begin, const statement::StatementSyntax& end) { }

void Visitor::visitEndGlobalStatementSyntax_Statement(const structure::GlobalStatementSyntax& begin, const statement::StatementSyntax& end) { }

void Visitor::visitGroupClauseSyntax_ByExpression(const structure::GroupClauseSyntax& begin, const expression::ExpressionSyntax& end) { }

void Visitor::visitEndGroupClauseSyntax_ByExpression(const structure::GroupClauseSyntax& begin, const expression::ExpressionSyntax& end) { }

void Visitor::visitGroupClauseSyntax_GroupExpression(const structure::GroupClauseSyntax& begin, const expression::ExpressionSyntax& end) { }

void Visitor::visitEndGroupClauseSyntax_GroupExpression(const structure::GroupClauseSyntax& begin, const expression::ExpressionSyntax& end) { }

void Visitor::visitIncompleteMemberSyntax_AttributeLists(const structure::IncompleteMemberSyntax& begin, const structure::AttributeListSyntax& end) { }

void Visitor::visitEndIncompleteMemberSyntax_AttributeLists(const structure::IncompleteMemberSyntax& begin, const structure::AttributeListSyntax& end) { }

void Visitor::visitIncompleteMemberSyntax_Type(const structure::IncompleteMemberSyntax& begin, const expression::TypeSyntax& end) { }

void Visitor::visitEndIncompleteMemberSyntax_Type(const structure::IncompleteMemberSyntax& begin, const expression::TypeSyntax& end) { }

void Visitor::visitIndexerDeclarationSyntax_ExpressionBody(const structure::IndexerDeclarationSyntax& begin, const structure::ArrowExpressionClauseSyntax& end) { }

void Visitor::visitEndIndexerDeclarationSyntax_ExpressionBody(const structure::IndexerDeclarationSyntax& begin, const structure::ArrowExpressionClauseSyntax& end) { }

void Visitor::visitIndexerDeclarationSyntax_ParameterList(const structure::IndexerDeclarationSyntax& begin, const structure::BracketedParameterListSyntax& end) { }

void Visitor::visitEndIndexerDeclarationSyntax_ParameterList(const structure::IndexerDeclarationSyntax& begin, const structure::BracketedParameterListSyntax& end) { }

void Visitor::visitIndexerMemberCrefSyntax_Parameters(const structure::IndexerMemberCrefSyntax& begin, const structure::CrefBracketedParameterListSyntax& end) { }

void Visitor::visitEndIndexerMemberCrefSyntax_Parameters(const structure::IndexerMemberCrefSyntax& begin, const structure::CrefBracketedParameterListSyntax& end) { }

void Visitor::visitInterpolationAlignmentClauseSyntax_Value(const structure::InterpolationAlignmentClauseSyntax& begin, const expression::ExpressionSyntax& end) { }

void Visitor::visitEndInterpolationAlignmentClauseSyntax_Value(const structure::InterpolationAlignmentClauseSyntax& begin, const expression::ExpressionSyntax& end) { }

void Visitor::visitInterpolationSyntax_AlignmentClause(const structure::InterpolationSyntax& begin, const structure::InterpolationAlignmentClauseSyntax& end) { }

void Visitor::visitEndInterpolationSyntax_AlignmentClause(const structure::InterpolationSyntax& begin, const structure::InterpolationAlignmentClauseSyntax& end) { }

void Visitor::visitInterpolationSyntax_Expression(const structure::InterpolationSyntax& begin, const expression::ExpressionSyntax& end) { }

void Visitor::visitEndInterpolationSyntax_Expression(const structure::InterpolationSyntax& begin, const expression::ExpressionSyntax& end) { }

void Visitor::visitInterpolationSyntax_FormatClause(const structure::InterpolationSyntax& begin, const structure::InterpolationFormatClauseSyntax& end) { }

void Visitor::visitEndInterpolationSyntax_FormatClause(const structure::InterpolationSyntax& begin, const structure::InterpolationFormatClauseSyntax& end) { }

void Visitor::visitJoinClauseSyntax_InExpression(const structure::JoinClauseSyntax& begin, const expression::ExpressionSyntax& end) { }

void Visitor::visitEndJoinClauseSyntax_InExpression(const structure::JoinClauseSyntax& begin, const expression::ExpressionSyntax& end) { }

void Visitor::visitJoinClauseSyntax_Into(const structure::JoinClauseSyntax& begin, const structure::JoinIntoClauseSyntax& end) { }

void Visitor::visitEndJoinClauseSyntax_Into(const structure::JoinClauseSyntax& begin, const structure::JoinIntoClauseSyntax& end) { }

void Visitor::visitJoinClauseSyntax_LeftExpression(const structure::JoinClauseSyntax& begin, const expression::ExpressionSyntax& end) { }

void Visitor::visitEndJoinClauseSyntax_LeftExpression(const structure::JoinClauseSyntax& begin, const expression::ExpressionSyntax& end) { }

void Visitor::visitJoinClauseSyntax_RightExpression(const structure::JoinClauseSyntax& begin, const expression::ExpressionSyntax& end) { }

void Visitor::visitEndJoinClauseSyntax_RightExpression(const structure::JoinClauseSyntax& begin, const expression::ExpressionSyntax& end) { }

void Visitor::visitJoinClauseSyntax_Type(const structure::JoinClauseSyntax& begin, const expression::TypeSyntax& end) { }

void Visitor::visitEndJoinClauseSyntax_Type(const structure::JoinClauseSyntax& begin, const expression::TypeSyntax& end) { }

void Visitor::visitLetClauseSyntax_Expression(const structure::LetClauseSyntax& begin, const expression::ExpressionSyntax& end) { }

void Visitor::visitEndLetClauseSyntax_Expression(const structure::LetClauseSyntax& begin, const expression::ExpressionSyntax& end) { }

void Visitor::visitMethodDeclarationSyntax_ConstraintClauses(const structure::MethodDeclarationSyntax& begin, const structure::TypeParameterConstraintClauseSyntax& end) { }

void Visitor::visitEndMethodDeclarationSyntax_ConstraintClauses(const structure::MethodDeclarationSyntax& begin, const structure::TypeParameterConstraintClauseSyntax& end) { }

void Visitor::visitMethodDeclarationSyntax_ExplicitInterfaceSpecifier(const structure::MethodDeclarationSyntax& begin, const structure::ExplicitInterfaceSpecifierSyntax& end) { }

void Visitor::visitEndMethodDeclarationSyntax_ExplicitInterfaceSpecifier(const structure::MethodDeclarationSyntax& begin, const structure::ExplicitInterfaceSpecifierSyntax& end) { }

void Visitor::visitMethodDeclarationSyntax_ExpressionBody(const structure::MethodDeclarationSyntax& begin, const structure::ArrowExpressionClauseSyntax& end) { }

void Visitor::visitEndMethodDeclarationSyntax_ExpressionBody(const structure::MethodDeclarationSyntax& begin, const structure::ArrowExpressionClauseSyntax& end) { }

void Visitor::visitMethodDeclarationSyntax_ReturnType(const structure::MethodDeclarationSyntax& begin, const expression::TypeSyntax& end) { }

void Visitor::visitEndMethodDeclarationSyntax_ReturnType(const structure::MethodDeclarationSyntax& begin, const expression::TypeSyntax& end) { }

void Visitor::visitNameColonSyntax_Name(const structure::NameColonSyntax& begin, const expression::IdentifierNameSyntax& end) { }

void Visitor::visitEndNameColonSyntax_Name(const structure::NameColonSyntax& begin, const expression::IdentifierNameSyntax& end) { }

void Visitor::visitNameEqualsSyntax_Name(const structure::NameEqualsSyntax& begin, const expression::IdentifierNameSyntax& end) { }

void Visitor::visitEndNameEqualsSyntax_Name(const structure::NameEqualsSyntax& begin, const expression::IdentifierNameSyntax& end) { }

void Visitor::visitNameMemberCrefSyntax_Name(const structure::NameMemberCrefSyntax& begin, const expression::TypeSyntax& end) { }

void Visitor::visitEndNameMemberCrefSyntax_Name(const structure::NameMemberCrefSyntax& begin, const expression::TypeSyntax& end) { }

void Visitor::visitNameMemberCrefSyntax_Parameters(const structure::NameMemberCrefSyntax& begin, const structure::CrefParameterListSyntax& end) { }

void Visitor::visitEndNameMemberCrefSyntax_Parameters(const structure::NameMemberCrefSyntax& begin, const structure::CrefParameterListSyntax& end) { }

void Visitor::visitNamespaceDeclarationSyntax_Externs(const structure::NamespaceDeclarationSyntax& begin, const structure::ExternAliasDirectiveSyntax& end) { }

void Visitor::visitEndNamespaceDeclarationSyntax_Externs(const structure::NamespaceDeclarationSyntax& begin, const structure::ExternAliasDirectiveSyntax& end) { }

void Visitor::visitNamespaceDeclarationSyntax_Members(const structure::NamespaceDeclarationSyntax& begin, const structure::MemberDeclarationSyntax& end) { }

void Visitor::visitEndNamespaceDeclarationSyntax_Members(const structure::NamespaceDeclarationSyntax& begin, const structure::MemberDeclarationSyntax& end) { }

void Visitor::visitNamespaceDeclarationSyntax_Name(const structure::NamespaceDeclarationSyntax& begin, const expression::NameSyntax& end) { }

void Visitor::visitEndNamespaceDeclarationSyntax_Name(const structure::NamespaceDeclarationSyntax& begin, const expression::NameSyntax& end) { }

void Visitor::visitNamespaceDeclarationSyntax_Usings(const structure::NamespaceDeclarationSyntax& begin, const structure::UsingDirectiveSyntax& end) { }

void Visitor::visitEndNamespaceDeclarationSyntax_Usings(const structure::NamespaceDeclarationSyntax& begin, const structure::UsingDirectiveSyntax& end) { }

void Visitor::visitOperatorDeclarationSyntax_ExpressionBody(const structure::OperatorDeclarationSyntax& begin, const structure::ArrowExpressionClauseSyntax& end) { }

void Visitor::visitEndOperatorDeclarationSyntax_ExpressionBody(const structure::OperatorDeclarationSyntax& begin, const structure::ArrowExpressionClauseSyntax& end) { }

void Visitor::visitOperatorDeclarationSyntax_ReturnType(const structure::OperatorDeclarationSyntax& begin, const expression::TypeSyntax& end) { }

void Visitor::visitEndOperatorDeclarationSyntax_ReturnType(const structure::OperatorDeclarationSyntax& begin, const expression::TypeSyntax& end) { }

void Visitor::visitOperatorMemberCrefSyntax_Parameters(const structure::OperatorMemberCrefSyntax& begin, const structure::CrefParameterListSyntax& end) { }

void Visitor::visitEndOperatorMemberCrefSyntax_Parameters(const structure::OperatorMemberCrefSyntax& begin, const structure::CrefParameterListSyntax& end) { }

void Visitor::visitOrderByClauseSyntax_Orderings(const structure::OrderByClauseSyntax& begin, const structure::OrderingSyntax& end) { }

void Visitor::visitEndOrderByClauseSyntax_Orderings(const structure::OrderByClauseSyntax& begin, const structure::OrderingSyntax& end) { }

void Visitor::visitOrderingSyntax_Expression(const structure::OrderingSyntax& begin, const expression::ExpressionSyntax& end) { }

void Visitor::visitEndOrderingSyntax_Expression(const structure::OrderingSyntax& begin, const expression::ExpressionSyntax& end) { }

void Visitor::visitParameterSyntax_AttributeLists(const structure::ParameterSyntax& begin, const structure::AttributeListSyntax& end) { }

void Visitor::visitEndParameterSyntax_AttributeLists(const structure::ParameterSyntax& begin, const structure::AttributeListSyntax& end) { }

void Visitor::visitParameterSyntax_Default(const structure::ParameterSyntax& begin, const structure::EqualsValueClauseSyntax& end) { }

void Visitor::visitEndParameterSyntax_Default(const structure::ParameterSyntax& begin, const structure::EqualsValueClauseSyntax& end) { }

void Visitor::visitParameterSyntax_Type(const structure::ParameterSyntax& begin, const expression::TypeSyntax& end) { }

void Visitor::visitEndParameterSyntax_Type(const structure::ParameterSyntax& begin, const expression::TypeSyntax& end) { }

void Visitor::visitPropertyDeclarationSyntax_ExpressionBody(const structure::PropertyDeclarationSyntax& begin, const structure::ArrowExpressionClauseSyntax& end) { }

void Visitor::visitEndPropertyDeclarationSyntax_ExpressionBody(const structure::PropertyDeclarationSyntax& begin, const structure::ArrowExpressionClauseSyntax& end) { }

void Visitor::visitPropertyDeclarationSyntax_Initializer(const structure::PropertyDeclarationSyntax& begin, const structure::EqualsValueClauseSyntax& end) { }

void Visitor::visitEndPropertyDeclarationSyntax_Initializer(const structure::PropertyDeclarationSyntax& begin, const structure::EqualsValueClauseSyntax& end) { }

void Visitor::visitQualifiedCrefSyntax_Container(const structure::QualifiedCrefSyntax& begin, const expression::TypeSyntax& end) { }

void Visitor::visitEndQualifiedCrefSyntax_Container(const structure::QualifiedCrefSyntax& begin, const expression::TypeSyntax& end) { }

void Visitor::visitQualifiedCrefSyntax_Member(const structure::QualifiedCrefSyntax& begin, const structure::MemberCrefSyntax& end) { }

void Visitor::visitEndQualifiedCrefSyntax_Member(const structure::QualifiedCrefSyntax& begin, const structure::MemberCrefSyntax& end) { }

void Visitor::visitQueryBodySyntax_Clauses(const structure::QueryBodySyntax& begin, const structure::QueryClauseSyntax& end) { }

void Visitor::visitEndQueryBodySyntax_Clauses(const structure::QueryBodySyntax& begin, const structure::QueryClauseSyntax& end) { }

void Visitor::visitQueryBodySyntax_Continuation(const structure::QueryBodySyntax& begin, const structure::QueryContinuationSyntax& end) { }

void Visitor::visitEndQueryBodySyntax_Continuation(const structure::QueryBodySyntax& begin, const structure::QueryContinuationSyntax& end) { }

void Visitor::visitQueryBodySyntax_SelectOrGroup(const structure::QueryBodySyntax& begin, const structure::SelectOrGroupClauseSyntax& end) { }

void Visitor::visitEndQueryBodySyntax_SelectOrGroup(const structure::QueryBodySyntax& begin, const structure::SelectOrGroupClauseSyntax& end) { }

void Visitor::visitQueryContinuationSyntax_Body(const structure::QueryContinuationSyntax& begin, const structure::QueryBodySyntax& end) { }

void Visitor::visitEndQueryContinuationSyntax_Body(const structure::QueryContinuationSyntax& begin, const structure::QueryBodySyntax& end) { }

void Visitor::visitSelectClauseSyntax_Expression(const structure::SelectClauseSyntax& begin, const expression::ExpressionSyntax& end) { }

void Visitor::visitEndSelectClauseSyntax_Expression(const structure::SelectClauseSyntax& begin, const expression::ExpressionSyntax& end) { }

void Visitor::visitSwitchSectionSyntax_Labels(const structure::SwitchSectionSyntax& begin, const structure::SwitchLabelSyntax& end) { }

void Visitor::visitEndSwitchSectionSyntax_Labels(const structure::SwitchSectionSyntax& begin, const structure::SwitchLabelSyntax& end) { }

void Visitor::visitSwitchSectionSyntax_Statements(const structure::SwitchSectionSyntax& begin, const statement::StatementSyntax& end) { }

void Visitor::visitEndSwitchSectionSyntax_Statements(const structure::SwitchSectionSyntax& begin, const statement::StatementSyntax& end) { }

void Visitor::visitTypeArgumentListSyntax_Arguments(const structure::TypeArgumentListSyntax& begin, const expression::TypeSyntax& end) { }

void Visitor::visitEndTypeArgumentListSyntax_Arguments(const structure::TypeArgumentListSyntax& begin, const expression::TypeSyntax& end) { }

void Visitor::visitTypeConstraintSyntax_Type(const structure::TypeConstraintSyntax& begin, const expression::TypeSyntax& end) { }

void Visitor::visitEndTypeConstraintSyntax_Type(const structure::TypeConstraintSyntax& begin, const expression::TypeSyntax& end) { }

void Visitor::visitTypeCrefSyntax_Type(const structure::TypeCrefSyntax& begin, const expression::TypeSyntax& end) { }

void Visitor::visitEndTypeCrefSyntax_Type(const structure::TypeCrefSyntax& begin, const expression::TypeSyntax& end) { }

void Visitor::visitTypeDeclarationSyntax_ConstraintClauses(const structure::TypeDeclarationSyntax& begin, const structure::TypeParameterConstraintClauseSyntax& end) { }

void Visitor::visitEndTypeDeclarationSyntax_ConstraintClauses(const structure::TypeDeclarationSyntax& begin, const structure::TypeParameterConstraintClauseSyntax& end) { }

void Visitor::visitTypeDeclarationSyntax_Members(const structure::TypeDeclarationSyntax& begin, const structure::MemberDeclarationSyntax& end) { }

void Visitor::visitEndTypeDeclarationSyntax_Members(const structure::TypeDeclarationSyntax& begin, const structure::MemberDeclarationSyntax& end) { }

void Visitor::visitTypeDeclarationSyntax_TypeParameterList(const structure::TypeDeclarationSyntax& begin, const structure::TypeParameterListSyntax& end) { }

void Visitor::visitEndTypeDeclarationSyntax_TypeParameterList(const structure::TypeDeclarationSyntax& begin, const structure::TypeParameterListSyntax& end) { }

void Visitor::visitTypeParameterConstraintClauseSyntax_Constraints(const structure::TypeParameterConstraintClauseSyntax& begin, const structure::TypeParameterConstraintSyntax& end) { }

void Visitor::visitEndTypeParameterConstraintClauseSyntax_Constraints(const structure::TypeParameterConstraintClauseSyntax& begin, const structure::TypeParameterConstraintSyntax& end) { }

void Visitor::visitTypeParameterConstraintClauseSyntax_Name(const structure::TypeParameterConstraintClauseSyntax& begin, const expression::IdentifierNameSyntax& end) { }

void Visitor::visitEndTypeParameterConstraintClauseSyntax_Name(const structure::TypeParameterConstraintClauseSyntax& begin, const expression::IdentifierNameSyntax& end) { }

void Visitor::visitTypeParameterListSyntax_Parameters(const structure::TypeParameterListSyntax& begin, const structure::TypeParameterSyntax& end) { }

void Visitor::visitEndTypeParameterListSyntax_Parameters(const structure::TypeParameterListSyntax& begin, const structure::TypeParameterSyntax& end) { }

void Visitor::visitTypeParameterSyntax_AttributeLists(const structure::TypeParameterSyntax& begin, const structure::AttributeListSyntax& end) { }

void Visitor::visitEndTypeParameterSyntax_AttributeLists(const structure::TypeParameterSyntax& begin, const structure::AttributeListSyntax& end) { }

void Visitor::visitUsingDirectiveSyntax_Alias(const structure::UsingDirectiveSyntax& begin, const structure::NameEqualsSyntax& end) { }

void Visitor::visitEndUsingDirectiveSyntax_Alias(const structure::UsingDirectiveSyntax& begin, const structure::NameEqualsSyntax& end) { }

void Visitor::visitUsingDirectiveSyntax_Name(const structure::UsingDirectiveSyntax& begin, const expression::NameSyntax& end) { }

void Visitor::visitEndUsingDirectiveSyntax_Name(const structure::UsingDirectiveSyntax& begin, const expression::NameSyntax& end) { }

void Visitor::visitVariableDeclarationSyntax_Type(const structure::VariableDeclarationSyntax& begin, const expression::TypeSyntax& end) { }

void Visitor::visitEndVariableDeclarationSyntax_Type(const structure::VariableDeclarationSyntax& begin, const expression::TypeSyntax& end) { }

void Visitor::visitVariableDeclarationSyntax_Variables(const structure::VariableDeclarationSyntax& begin, const structure::VariableDeclaratorSyntax& end) { }

void Visitor::visitEndVariableDeclarationSyntax_Variables(const structure::VariableDeclarationSyntax& begin, const structure::VariableDeclaratorSyntax& end) { }

void Visitor::visitVariableDeclaratorSyntax_ArgumentList(const structure::VariableDeclaratorSyntax& begin, const structure::BracketedArgumentListSyntax& end) { }

void Visitor::visitEndVariableDeclaratorSyntax_ArgumentList(const structure::VariableDeclaratorSyntax& begin, const structure::BracketedArgumentListSyntax& end) { }

void Visitor::visitVariableDeclaratorSyntax_Initializer(const structure::VariableDeclaratorSyntax& begin, const structure::EqualsValueClauseSyntax& end) { }

void Visitor::visitEndVariableDeclaratorSyntax_Initializer(const structure::VariableDeclaratorSyntax& begin, const structure::EqualsValueClauseSyntax& end) { }

void Visitor::visitWhereClauseSyntax_Condition(const structure::WhereClauseSyntax& begin, const expression::ExpressionSyntax& end) { }

void Visitor::visitEndWhereClauseSyntax_Condition(const structure::WhereClauseSyntax& begin, const expression::ExpressionSyntax& end) { }

void Visitor::visitXmlAttributeSyntax_Name(const structure::XmlAttributeSyntax& begin, const structure::XmlNameSyntax& end) { }

void Visitor::visitEndXmlAttributeSyntax_Name(const structure::XmlAttributeSyntax& begin, const structure::XmlNameSyntax& end) { }

void Visitor::visitXmlCrefAttributeSyntax_Cref(const structure::XmlCrefAttributeSyntax& begin, const structure::CrefSyntax& end) { }

void Visitor::visitEndXmlCrefAttributeSyntax_Cref(const structure::XmlCrefAttributeSyntax& begin, const structure::CrefSyntax& end) { }

void Visitor::visitXmlElementEndTagSyntax_Name(const structure::XmlElementEndTagSyntax& begin, const structure::XmlNameSyntax& end) { }

void Visitor::visitEndXmlElementEndTagSyntax_Name(const structure::XmlElementEndTagSyntax& begin, const structure::XmlNameSyntax& end) { }

void Visitor::visitXmlElementStartTagSyntax_Attributes(const structure::XmlElementStartTagSyntax& begin, const structure::XmlAttributeSyntax& end) { }

void Visitor::visitEndXmlElementStartTagSyntax_Attributes(const structure::XmlElementStartTagSyntax& begin, const structure::XmlAttributeSyntax& end) { }

void Visitor::visitXmlElementStartTagSyntax_Name(const structure::XmlElementStartTagSyntax& begin, const structure::XmlNameSyntax& end) { }

void Visitor::visitEndXmlElementStartTagSyntax_Name(const structure::XmlElementStartTagSyntax& begin, const structure::XmlNameSyntax& end) { }

void Visitor::visitXmlElementSyntax_Content(const structure::XmlElementSyntax& begin, const structure::XmlNodeSyntax& end) { }

void Visitor::visitEndXmlElementSyntax_Content(const structure::XmlElementSyntax& begin, const structure::XmlNodeSyntax& end) { }

void Visitor::visitXmlElementSyntax_EndTag(const structure::XmlElementSyntax& begin, const structure::XmlElementEndTagSyntax& end) { }

void Visitor::visitEndXmlElementSyntax_EndTag(const structure::XmlElementSyntax& begin, const structure::XmlElementEndTagSyntax& end) { }

void Visitor::visitXmlElementSyntax_StartTag(const structure::XmlElementSyntax& begin, const structure::XmlElementStartTagSyntax& end) { }

void Visitor::visitEndXmlElementSyntax_StartTag(const structure::XmlElementSyntax& begin, const structure::XmlElementStartTagSyntax& end) { }

void Visitor::visitXmlEmptyElementSyntax_Attributes(const structure::XmlEmptyElementSyntax& begin, const structure::XmlAttributeSyntax& end) { }

void Visitor::visitEndXmlEmptyElementSyntax_Attributes(const structure::XmlEmptyElementSyntax& begin, const structure::XmlAttributeSyntax& end) { }

void Visitor::visitXmlEmptyElementSyntax_Name(const structure::XmlEmptyElementSyntax& begin, const structure::XmlNameSyntax& end) { }

void Visitor::visitEndXmlEmptyElementSyntax_Name(const structure::XmlEmptyElementSyntax& begin, const structure::XmlNameSyntax& end) { }

void Visitor::visitXmlNameAttributeSyntax_Identifier(const structure::XmlNameAttributeSyntax& begin, const expression::IdentifierNameSyntax& end) { }

void Visitor::visitEndXmlNameAttributeSyntax_Identifier(const structure::XmlNameAttributeSyntax& begin, const expression::IdentifierNameSyntax& end) { }

void Visitor::visitXmlNameSyntax_Prefix(const structure::XmlNameSyntax& begin, const structure::XmlPrefixSyntax& end) { }

void Visitor::visitEndXmlNameSyntax_Prefix(const structure::XmlNameSyntax& begin, const structure::XmlPrefixSyntax& end) { }

void Visitor::visitXmlProcessingInstructionSyntax_Name(const structure::XmlProcessingInstructionSyntax& begin, const structure::XmlNameSyntax& end) { }

void Visitor::visitEndXmlProcessingInstructionSyntax_Name(const structure::XmlProcessingInstructionSyntax& begin, const structure::XmlNameSyntax& end) { }


}}}
