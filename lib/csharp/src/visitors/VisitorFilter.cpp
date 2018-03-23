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
VisitorFilter::VisitorFilter(bool filter) : Visitor() ,selector( filter?&Factory::setFilteredThisNodeOnly : &Factory::setNotFilteredThisNodeOnly) {
}

VisitorFilter::~VisitorFilter() {
}

void VisitorFilter::visitEnd(const expression::AliasQualifiedNameSyntax& node , bool callVirtualBase /*= true*/) {
  (node.getFactory().*selector)(node.getId());
}

void VisitorFilter::visitEnd(const expression::AnonymousMethodExpressionSyntax& node , bool callVirtualBase /*= true*/) {
  (node.getFactory().*selector)(node.getId());
}

void VisitorFilter::visitEnd(const expression::AnonymousObjectCreationExpressionSyntax& node , bool callVirtualBase /*= true*/) {
  (node.getFactory().*selector)(node.getId());
}

void VisitorFilter::visitEnd(const expression::ArrayCreationExpressionSyntax& node , bool callVirtualBase /*= true*/) {
  (node.getFactory().*selector)(node.getId());
}

void VisitorFilter::visitEnd(const expression::ArrayTypeSyntax& node , bool callVirtualBase /*= true*/) {
  (node.getFactory().*selector)(node.getId());
}

void VisitorFilter::visitEnd(const expression::AssignmentExpressionSyntax& node , bool callVirtualBase /*= true*/) {
  (node.getFactory().*selector)(node.getId());
}

void VisitorFilter::visitEnd(const expression::AwaitExpressionSyntax& node , bool callVirtualBase /*= true*/) {
  (node.getFactory().*selector)(node.getId());
}

void VisitorFilter::visitEnd(const expression::BaseExpressionSyntax& node , bool callVirtualBase /*= true*/) {
  (node.getFactory().*selector)(node.getId());
}

void VisitorFilter::visitEnd(const expression::BinaryExpressionSyntax& node , bool callVirtualBase /*= true*/) {
  (node.getFactory().*selector)(node.getId());
}

void VisitorFilter::visitEnd(const expression::CastExpressionSyntax& node , bool callVirtualBase /*= true*/) {
  (node.getFactory().*selector)(node.getId());
}

void VisitorFilter::visitEnd(const expression::CheckedExpressionSyntax& node , bool callVirtualBase /*= true*/) {
  (node.getFactory().*selector)(node.getId());
}

void VisitorFilter::visitEnd(const expression::ConditionalAccessExpressionSyntax& node , bool callVirtualBase /*= true*/) {
  (node.getFactory().*selector)(node.getId());
}

void VisitorFilter::visitEnd(const expression::ConditionalExpressionSyntax& node , bool callVirtualBase /*= true*/) {
  (node.getFactory().*selector)(node.getId());
}

void VisitorFilter::visitEnd(const expression::DefaultExpressionSyntax& node , bool callVirtualBase /*= true*/) {
  (node.getFactory().*selector)(node.getId());
}

void VisitorFilter::visitEnd(const expression::ElementAccessExpressionSyntax& node , bool callVirtualBase /*= true*/) {
  (node.getFactory().*selector)(node.getId());
}

void VisitorFilter::visitEnd(const expression::ElementBindingExpressionSyntax& node , bool callVirtualBase /*= true*/) {
  (node.getFactory().*selector)(node.getId());
}

void VisitorFilter::visitEnd(const expression::GenericNameSyntax& node , bool callVirtualBase /*= true*/) {
  (node.getFactory().*selector)(node.getId());
}

void VisitorFilter::visitEnd(const expression::IdentifierNameSyntax& node , bool callVirtualBase /*= true*/) {
  (node.getFactory().*selector)(node.getId());
}

void VisitorFilter::visitEnd(const expression::ImplicitArrayCreationExpressionSyntax& node , bool callVirtualBase /*= true*/) {
  (node.getFactory().*selector)(node.getId());
}

void VisitorFilter::visitEnd(const expression::ImplicitElementAccessSyntax& node , bool callVirtualBase /*= true*/) {
  (node.getFactory().*selector)(node.getId());
}

void VisitorFilter::visitEnd(const expression::InitializerExpressionSyntax& node , bool callVirtualBase /*= true*/) {
  (node.getFactory().*selector)(node.getId());
}

void VisitorFilter::visitEnd(const expression::InterpolatedStringExpressionSyntax& node , bool callVirtualBase /*= true*/) {
  (node.getFactory().*selector)(node.getId());
}

void VisitorFilter::visitEnd(const expression::InvocationExpressionSyntax& node , bool callVirtualBase /*= true*/) {
  (node.getFactory().*selector)(node.getId());
}

void VisitorFilter::visitEnd(const expression::LiteralExpressionSyntax& node , bool callVirtualBase /*= true*/) {
  (node.getFactory().*selector)(node.getId());
}

void VisitorFilter::visitEnd(const expression::MakeRefExpressionSyntax& node , bool callVirtualBase /*= true*/) {
  (node.getFactory().*selector)(node.getId());
}

void VisitorFilter::visitEnd(const expression::MemberAccessExpressionSyntax& node , bool callVirtualBase /*= true*/) {
  (node.getFactory().*selector)(node.getId());
}

void VisitorFilter::visitEnd(const expression::MemberBindingExpressionSyntax& node , bool callVirtualBase /*= true*/) {
  (node.getFactory().*selector)(node.getId());
}

void VisitorFilter::visitEnd(const expression::NullableTypeSyntax& node , bool callVirtualBase /*= true*/) {
  (node.getFactory().*selector)(node.getId());
}

void VisitorFilter::visitEnd(const expression::ObjectCreationExpressionSyntax& node , bool callVirtualBase /*= true*/) {
  (node.getFactory().*selector)(node.getId());
}

void VisitorFilter::visitEnd(const expression::OmittedArraySizeExpressionSyntax& node , bool callVirtualBase /*= true*/) {
  (node.getFactory().*selector)(node.getId());
}

void VisitorFilter::visitEnd(const expression::OmittedTypeArgumentSyntax& node , bool callVirtualBase /*= true*/) {
  (node.getFactory().*selector)(node.getId());
}

void VisitorFilter::visitEnd(const expression::ParenthesizedExpressionSyntax& node , bool callVirtualBase /*= true*/) {
  (node.getFactory().*selector)(node.getId());
}

void VisitorFilter::visitEnd(const expression::ParenthesizedLambdaExpressionSyntax& node , bool callVirtualBase /*= true*/) {
  (node.getFactory().*selector)(node.getId());
}

void VisitorFilter::visitEnd(const expression::PointerTypeSyntax& node , bool callVirtualBase /*= true*/) {
  (node.getFactory().*selector)(node.getId());
}

void VisitorFilter::visitEnd(const expression::PostfixUnaryExpressionSyntax& node , bool callVirtualBase /*= true*/) {
  (node.getFactory().*selector)(node.getId());
}

void VisitorFilter::visitEnd(const expression::PredefinedTypeSyntax& node , bool callVirtualBase /*= true*/) {
  (node.getFactory().*selector)(node.getId());
}

void VisitorFilter::visitEnd(const expression::PrefixUnaryExpressionSyntax& node , bool callVirtualBase /*= true*/) {
  (node.getFactory().*selector)(node.getId());
}

void VisitorFilter::visitEnd(const expression::QualifiedNameSyntax& node , bool callVirtualBase /*= true*/) {
  (node.getFactory().*selector)(node.getId());
}

void VisitorFilter::visitEnd(const expression::QueryExpressionSyntax& node , bool callVirtualBase /*= true*/) {
  (node.getFactory().*selector)(node.getId());
}

void VisitorFilter::visitEnd(const expression::RefTypeExpressionSyntax& node , bool callVirtualBase /*= true*/) {
  (node.getFactory().*selector)(node.getId());
}

void VisitorFilter::visitEnd(const expression::RefValueExpressionSyntax& node , bool callVirtualBase /*= true*/) {
  (node.getFactory().*selector)(node.getId());
}

void VisitorFilter::visitEnd(const expression::SimpleLambdaExpressionSyntax& node , bool callVirtualBase /*= true*/) {
  (node.getFactory().*selector)(node.getId());
}

void VisitorFilter::visitEnd(const expression::SizeOfExpressionSyntax& node , bool callVirtualBase /*= true*/) {
  (node.getFactory().*selector)(node.getId());
}

void VisitorFilter::visitEnd(const expression::StackAllocArrayCreationExpressionSyntax& node , bool callVirtualBase /*= true*/) {
  (node.getFactory().*selector)(node.getId());
}

void VisitorFilter::visitEnd(const expression::ThisExpressionSyntax& node , bool callVirtualBase /*= true*/) {
  (node.getFactory().*selector)(node.getId());
}

void VisitorFilter::visitEnd(const expression::TypeOfExpressionSyntax& node , bool callVirtualBase /*= true*/) {
  (node.getFactory().*selector)(node.getId());
}

void VisitorFilter::visitEnd(const statement::BlockSyntax& node , bool callVirtualBase /*= true*/) {
  (node.getFactory().*selector)(node.getId());
}

void VisitorFilter::visitEnd(const statement::BreakStatementSyntax& node , bool callVirtualBase /*= true*/) {
  (node.getFactory().*selector)(node.getId());
}

void VisitorFilter::visitEnd(const statement::CheckedStatementSyntax& node , bool callVirtualBase /*= true*/) {
  (node.getFactory().*selector)(node.getId());
}

void VisitorFilter::visitEnd(const statement::ContinueStatementSyntax& node , bool callVirtualBase /*= true*/) {
  (node.getFactory().*selector)(node.getId());
}

void VisitorFilter::visitEnd(const statement::DoStatementSyntax& node , bool callVirtualBase /*= true*/) {
  (node.getFactory().*selector)(node.getId());
}

void VisitorFilter::visitEnd(const statement::EmptyStatementSyntax& node , bool callVirtualBase /*= true*/) {
  (node.getFactory().*selector)(node.getId());
}

void VisitorFilter::visitEnd(const statement::ExpressionStatementSyntax& node , bool callVirtualBase /*= true*/) {
  (node.getFactory().*selector)(node.getId());
}

void VisitorFilter::visitEnd(const statement::FixedStatementSyntax& node , bool callVirtualBase /*= true*/) {
  (node.getFactory().*selector)(node.getId());
}

void VisitorFilter::visitEnd(const statement::ForEachStatementSyntax& node , bool callVirtualBase /*= true*/) {
  (node.getFactory().*selector)(node.getId());
}

void VisitorFilter::visitEnd(const statement::ForStatementSyntax& node , bool callVirtualBase /*= true*/) {
  (node.getFactory().*selector)(node.getId());
}

void VisitorFilter::visitEnd(const statement::GotoStatementSyntax& node , bool callVirtualBase /*= true*/) {
  (node.getFactory().*selector)(node.getId());
}

void VisitorFilter::visitEnd(const statement::IfStatementSyntax& node , bool callVirtualBase /*= true*/) {
  (node.getFactory().*selector)(node.getId());
}

void VisitorFilter::visitEnd(const statement::LabeledStatementSyntax& node , bool callVirtualBase /*= true*/) {
  (node.getFactory().*selector)(node.getId());
}

void VisitorFilter::visitEnd(const statement::LocalDeclarationStatementSyntax& node , bool callVirtualBase /*= true*/) {
  (node.getFactory().*selector)(node.getId());
}

void VisitorFilter::visitEnd(const statement::LockStatementSyntax& node , bool callVirtualBase /*= true*/) {
  (node.getFactory().*selector)(node.getId());
}

void VisitorFilter::visitEnd(const statement::ReturnStatementSyntax& node , bool callVirtualBase /*= true*/) {
  (node.getFactory().*selector)(node.getId());
}

void VisitorFilter::visitEnd(const statement::SwitchStatementSyntax& node , bool callVirtualBase /*= true*/) {
  (node.getFactory().*selector)(node.getId());
}

void VisitorFilter::visitEnd(const statement::ThrowStatementSyntax& node , bool callVirtualBase /*= true*/) {
  (node.getFactory().*selector)(node.getId());
}

void VisitorFilter::visitEnd(const statement::TryStatementSyntax& node , bool callVirtualBase /*= true*/) {
  (node.getFactory().*selector)(node.getId());
}

void VisitorFilter::visitEnd(const statement::UnsafeStatementSyntax& node , bool callVirtualBase /*= true*/) {
  (node.getFactory().*selector)(node.getId());
}

void VisitorFilter::visitEnd(const statement::UsingStatementSyntax& node , bool callVirtualBase /*= true*/) {
  (node.getFactory().*selector)(node.getId());
}

void VisitorFilter::visitEnd(const statement::WhileStatementSyntax& node , bool callVirtualBase /*= true*/) {
  (node.getFactory().*selector)(node.getId());
}

void VisitorFilter::visitEnd(const statement::YieldStatementSyntax& node , bool callVirtualBase /*= true*/) {
  (node.getFactory().*selector)(node.getId());
}

void VisitorFilter::visitEnd(const structure::AccessorDeclarationSyntax& node , bool callVirtualBase /*= true*/) {
  (node.getFactory().*selector)(node.getId());
}

void VisitorFilter::visitEnd(const structure::AccessorListSyntax& node , bool callVirtualBase /*= true*/) {
  (node.getFactory().*selector)(node.getId());
}

void VisitorFilter::visitEnd(const structure::AnonymousObjectMemberDeclaratorSyntax& node , bool callVirtualBase /*= true*/) {
  (node.getFactory().*selector)(node.getId());
}

void VisitorFilter::visitEnd(const structure::ArgumentListSyntax& node , bool callVirtualBase /*= true*/) {
  (node.getFactory().*selector)(node.getId());
}

void VisitorFilter::visitEnd(const structure::ArgumentSyntax& node , bool callVirtualBase /*= true*/) {
  (node.getFactory().*selector)(node.getId());
}

void VisitorFilter::visitEnd(const structure::ArrayRankSpecifierSyntax& node , bool callVirtualBase /*= true*/) {
  (node.getFactory().*selector)(node.getId());
}

void VisitorFilter::visitEnd(const structure::ArrowExpressionClauseSyntax& node , bool callVirtualBase /*= true*/) {
  (node.getFactory().*selector)(node.getId());
}

void VisitorFilter::visitEnd(const structure::AttributeArgumentListSyntax& node , bool callVirtualBase /*= true*/) {
  (node.getFactory().*selector)(node.getId());
}

void VisitorFilter::visitEnd(const structure::AttributeArgumentSyntax& node , bool callVirtualBase /*= true*/) {
  (node.getFactory().*selector)(node.getId());
}

void VisitorFilter::visitEnd(const structure::AttributeListSyntax& node , bool callVirtualBase /*= true*/) {
  (node.getFactory().*selector)(node.getId());
}

void VisitorFilter::visitEnd(const structure::AttributeSyntax& node , bool callVirtualBase /*= true*/) {
  (node.getFactory().*selector)(node.getId());
}

void VisitorFilter::visitEnd(const structure::AttributeTargetSpecifierSyntax& node , bool callVirtualBase /*= true*/) {
  (node.getFactory().*selector)(node.getId());
}

void VisitorFilter::visitEnd(const structure::BaseListSyntax& node , bool callVirtualBase /*= true*/) {
  (node.getFactory().*selector)(node.getId());
}

void VisitorFilter::visitEnd(const structure::BracketedArgumentListSyntax& node , bool callVirtualBase /*= true*/) {
  (node.getFactory().*selector)(node.getId());
}

void VisitorFilter::visitEnd(const structure::BracketedParameterListSyntax& node , bool callVirtualBase /*= true*/) {
  (node.getFactory().*selector)(node.getId());
}

void VisitorFilter::visitEnd(const structure::CaseSwitchLabelSyntax& node , bool callVirtualBase /*= true*/) {
  (node.getFactory().*selector)(node.getId());
}

void VisitorFilter::visitEnd(const structure::CatchClauseSyntax& node , bool callVirtualBase /*= true*/) {
  (node.getFactory().*selector)(node.getId());
}

void VisitorFilter::visitEnd(const structure::CatchDeclarationSyntax& node , bool callVirtualBase /*= true*/) {
  (node.getFactory().*selector)(node.getId());
}

void VisitorFilter::visitEnd(const structure::CatchFilterClauseSyntax& node , bool callVirtualBase /*= true*/) {
  (node.getFactory().*selector)(node.getId());
}

void VisitorFilter::visitEnd(const structure::ClassDeclarationSyntax& node , bool callVirtualBase /*= true*/) {
  (node.getFactory().*selector)(node.getId());
}

void VisitorFilter::visitEnd(const structure::ClassOrStructConstraintSyntax& node , bool callVirtualBase /*= true*/) {
  (node.getFactory().*selector)(node.getId());
}

void VisitorFilter::visitEnd(const structure::CompilationUnitSyntax& node , bool callVirtualBase /*= true*/) {
  (node.getFactory().*selector)(node.getId());
}

void VisitorFilter::visitEnd(const structure::ConstructorConstraintSyntax& node , bool callVirtualBase /*= true*/) {
  (node.getFactory().*selector)(node.getId());
}

void VisitorFilter::visitEnd(const structure::ConstructorDeclarationSyntax& node , bool callVirtualBase /*= true*/) {
  (node.getFactory().*selector)(node.getId());
}

void VisitorFilter::visitEnd(const structure::ConstructorInitializerSyntax& node , bool callVirtualBase /*= true*/) {
  (node.getFactory().*selector)(node.getId());
}

void VisitorFilter::visitEnd(const structure::ConversionOperatorDeclarationSyntax& node , bool callVirtualBase /*= true*/) {
  (node.getFactory().*selector)(node.getId());
}

void VisitorFilter::visitEnd(const structure::ConversionOperatorMemberCrefSyntax& node , bool callVirtualBase /*= true*/) {
  (node.getFactory().*selector)(node.getId());
}

void VisitorFilter::visitEnd(const structure::CrefBracketedParameterListSyntax& node , bool callVirtualBase /*= true*/) {
  (node.getFactory().*selector)(node.getId());
}

void VisitorFilter::visitEnd(const structure::CrefParameterListSyntax& node , bool callVirtualBase /*= true*/) {
  (node.getFactory().*selector)(node.getId());
}

void VisitorFilter::visitEnd(const structure::CrefParameterSyntax& node , bool callVirtualBase /*= true*/) {
  (node.getFactory().*selector)(node.getId());
}

void VisitorFilter::visitEnd(const structure::DefaultSwitchLabelSyntax& node , bool callVirtualBase /*= true*/) {
  (node.getFactory().*selector)(node.getId());
}

void VisitorFilter::visitEnd(const structure::DelegateDeclarationSyntax& node , bool callVirtualBase /*= true*/) {
  (node.getFactory().*selector)(node.getId());
}

void VisitorFilter::visitEnd(const structure::DestructorDeclarationSyntax& node , bool callVirtualBase /*= true*/) {
  (node.getFactory().*selector)(node.getId());
}

void VisitorFilter::visitEnd(const structure::ElseClauseSyntax& node , bool callVirtualBase /*= true*/) {
  (node.getFactory().*selector)(node.getId());
}

void VisitorFilter::visitEnd(const structure::EnumDeclarationSyntax& node , bool callVirtualBase /*= true*/) {
  (node.getFactory().*selector)(node.getId());
}

void VisitorFilter::visitEnd(const structure::EnumMemberDeclarationSyntax& node , bool callVirtualBase /*= true*/) {
  (node.getFactory().*selector)(node.getId());
}

void VisitorFilter::visitEnd(const structure::EqualsValueClauseSyntax& node , bool callVirtualBase /*= true*/) {
  (node.getFactory().*selector)(node.getId());
}

void VisitorFilter::visitEnd(const structure::EventDeclarationSyntax& node , bool callVirtualBase /*= true*/) {
  (node.getFactory().*selector)(node.getId());
}

void VisitorFilter::visitEnd(const structure::EventFieldDeclarationSyntax& node , bool callVirtualBase /*= true*/) {
  (node.getFactory().*selector)(node.getId());
}

void VisitorFilter::visitEnd(const structure::ExplicitInterfaceSpecifierSyntax& node , bool callVirtualBase /*= true*/) {
  (node.getFactory().*selector)(node.getId());
}

void VisitorFilter::visitEnd(const structure::ExternAliasDirectiveSyntax& node , bool callVirtualBase /*= true*/) {
  (node.getFactory().*selector)(node.getId());
}

void VisitorFilter::visitEnd(const structure::FieldDeclarationSyntax& node , bool callVirtualBase /*= true*/) {
  (node.getFactory().*selector)(node.getId());
}

void VisitorFilter::visitEnd(const structure::FinallyClauseSyntax& node , bool callVirtualBase /*= true*/) {
  (node.getFactory().*selector)(node.getId());
}

void VisitorFilter::visitEnd(const structure::FromClauseSyntax& node , bool callVirtualBase /*= true*/) {
  (node.getFactory().*selector)(node.getId());
}

void VisitorFilter::visitEnd(const structure::GlobalStatementSyntax& node , bool callVirtualBase /*= true*/) {
  (node.getFactory().*selector)(node.getId());
}

void VisitorFilter::visitEnd(const structure::GroupClauseSyntax& node , bool callVirtualBase /*= true*/) {
  (node.getFactory().*selector)(node.getId());
}

void VisitorFilter::visitEnd(const structure::IncompleteMemberSyntax& node , bool callVirtualBase /*= true*/) {
  (node.getFactory().*selector)(node.getId());
}

void VisitorFilter::visitEnd(const structure::IndexerDeclarationSyntax& node , bool callVirtualBase /*= true*/) {
  (node.getFactory().*selector)(node.getId());
}

void VisitorFilter::visitEnd(const structure::IndexerMemberCrefSyntax& node , bool callVirtualBase /*= true*/) {
  (node.getFactory().*selector)(node.getId());
}

void VisitorFilter::visitEnd(const structure::InterfaceDeclarationSyntax& node , bool callVirtualBase /*= true*/) {
  (node.getFactory().*selector)(node.getId());
}

void VisitorFilter::visitEnd(const structure::InterpolatedStringTextSyntax& node , bool callVirtualBase /*= true*/) {
  (node.getFactory().*selector)(node.getId());
}

void VisitorFilter::visitEnd(const structure::InterpolationAlignmentClauseSyntax& node , bool callVirtualBase /*= true*/) {
  (node.getFactory().*selector)(node.getId());
}

void VisitorFilter::visitEnd(const structure::InterpolationFormatClauseSyntax& node , bool callVirtualBase /*= true*/) {
  (node.getFactory().*selector)(node.getId());
}

void VisitorFilter::visitEnd(const structure::InterpolationSyntax& node , bool callVirtualBase /*= true*/) {
  (node.getFactory().*selector)(node.getId());
}

void VisitorFilter::visitEnd(const structure::JoinClauseSyntax& node , bool callVirtualBase /*= true*/) {
  (node.getFactory().*selector)(node.getId());
}

void VisitorFilter::visitEnd(const structure::JoinIntoClauseSyntax& node , bool callVirtualBase /*= true*/) {
  (node.getFactory().*selector)(node.getId());
}

void VisitorFilter::visitEnd(const structure::LetClauseSyntax& node , bool callVirtualBase /*= true*/) {
  (node.getFactory().*selector)(node.getId());
}

void VisitorFilter::visitEnd(const structure::MethodDeclarationSyntax& node , bool callVirtualBase /*= true*/) {
  (node.getFactory().*selector)(node.getId());
}

void VisitorFilter::visitEnd(const structure::NameColonSyntax& node , bool callVirtualBase /*= true*/) {
  (node.getFactory().*selector)(node.getId());
}

void VisitorFilter::visitEnd(const structure::NameEqualsSyntax& node , bool callVirtualBase /*= true*/) {
  (node.getFactory().*selector)(node.getId());
}

void VisitorFilter::visitEnd(const structure::NameMemberCrefSyntax& node , bool callVirtualBase /*= true*/) {
  (node.getFactory().*selector)(node.getId());
}

void VisitorFilter::visitEnd(const structure::NamespaceDeclarationSyntax& node , bool callVirtualBase /*= true*/) {
  (node.getFactory().*selector)(node.getId());
}

void VisitorFilter::visitEnd(const structure::OperatorDeclarationSyntax& node , bool callVirtualBase /*= true*/) {
  (node.getFactory().*selector)(node.getId());
}

void VisitorFilter::visitEnd(const structure::OperatorMemberCrefSyntax& node , bool callVirtualBase /*= true*/) {
  (node.getFactory().*selector)(node.getId());
}

void VisitorFilter::visitEnd(const structure::OrderByClauseSyntax& node , bool callVirtualBase /*= true*/) {
  (node.getFactory().*selector)(node.getId());
}

void VisitorFilter::visitEnd(const structure::OrderingSyntax& node , bool callVirtualBase /*= true*/) {
  (node.getFactory().*selector)(node.getId());
}

void VisitorFilter::visitEnd(const structure::ParameterListSyntax& node , bool callVirtualBase /*= true*/) {
  (node.getFactory().*selector)(node.getId());
}

void VisitorFilter::visitEnd(const structure::ParameterSyntax& node , bool callVirtualBase /*= true*/) {
  (node.getFactory().*selector)(node.getId());
}

void VisitorFilter::visitEnd(const structure::PropertyDeclarationSyntax& node , bool callVirtualBase /*= true*/) {
  (node.getFactory().*selector)(node.getId());
}

void VisitorFilter::visitEnd(const structure::QualifiedCrefSyntax& node , bool callVirtualBase /*= true*/) {
  (node.getFactory().*selector)(node.getId());
}

void VisitorFilter::visitEnd(const structure::QueryBodySyntax& node , bool callVirtualBase /*= true*/) {
  (node.getFactory().*selector)(node.getId());
}

void VisitorFilter::visitEnd(const structure::QueryContinuationSyntax& node , bool callVirtualBase /*= true*/) {
  (node.getFactory().*selector)(node.getId());
}

void VisitorFilter::visitEnd(const structure::SelectClauseSyntax& node , bool callVirtualBase /*= true*/) {
  (node.getFactory().*selector)(node.getId());
}

void VisitorFilter::visitEnd(const structure::SimpleBaseTypeSyntax& node , bool callVirtualBase /*= true*/) {
  (node.getFactory().*selector)(node.getId());
}

void VisitorFilter::visitEnd(const structure::StructDeclarationSyntax& node , bool callVirtualBase /*= true*/) {
  (node.getFactory().*selector)(node.getId());
}

void VisitorFilter::visitEnd(const structure::SwitchSectionSyntax& node , bool callVirtualBase /*= true*/) {
  (node.getFactory().*selector)(node.getId());
}

void VisitorFilter::visitEnd(const structure::SyntaxToken& node , bool callVirtualBase /*= true*/) {
  (node.getFactory().*selector)(node.getId());
}

void VisitorFilter::visitEnd(const structure::TypeArgumentListSyntax& node , bool callVirtualBase /*= true*/) {
  (node.getFactory().*selector)(node.getId());
}

void VisitorFilter::visitEnd(const structure::TypeConstraintSyntax& node , bool callVirtualBase /*= true*/) {
  (node.getFactory().*selector)(node.getId());
}

void VisitorFilter::visitEnd(const structure::TypeCrefSyntax& node , bool callVirtualBase /*= true*/) {
  (node.getFactory().*selector)(node.getId());
}

void VisitorFilter::visitEnd(const structure::TypeParameterConstraintClauseSyntax& node , bool callVirtualBase /*= true*/) {
  (node.getFactory().*selector)(node.getId());
}

void VisitorFilter::visitEnd(const structure::TypeParameterListSyntax& node , bool callVirtualBase /*= true*/) {
  (node.getFactory().*selector)(node.getId());
}

void VisitorFilter::visitEnd(const structure::TypeParameterSyntax& node , bool callVirtualBase /*= true*/) {
  (node.getFactory().*selector)(node.getId());
}

void VisitorFilter::visitEnd(const structure::UsingDirectiveSyntax& node , bool callVirtualBase /*= true*/) {
  (node.getFactory().*selector)(node.getId());
}

void VisitorFilter::visitEnd(const structure::VariableDeclarationSyntax& node , bool callVirtualBase /*= true*/) {
  (node.getFactory().*selector)(node.getId());
}

void VisitorFilter::visitEnd(const structure::VariableDeclaratorSyntax& node , bool callVirtualBase /*= true*/) {
  (node.getFactory().*selector)(node.getId());
}

void VisitorFilter::visitEnd(const structure::WhereClauseSyntax& node , bool callVirtualBase /*= true*/) {
  (node.getFactory().*selector)(node.getId());
}

void VisitorFilter::visitEnd(const structure::XmlCDataSectionSyntax& node , bool callVirtualBase /*= true*/) {
  (node.getFactory().*selector)(node.getId());
}

void VisitorFilter::visitEnd(const structure::XmlCommentSyntax& node , bool callVirtualBase /*= true*/) {
  (node.getFactory().*selector)(node.getId());
}

void VisitorFilter::visitEnd(const structure::XmlCrefAttributeSyntax& node , bool callVirtualBase /*= true*/) {
  (node.getFactory().*selector)(node.getId());
}

void VisitorFilter::visitEnd(const structure::XmlElementEndTagSyntax& node , bool callVirtualBase /*= true*/) {
  (node.getFactory().*selector)(node.getId());
}

void VisitorFilter::visitEnd(const structure::XmlElementStartTagSyntax& node , bool callVirtualBase /*= true*/) {
  (node.getFactory().*selector)(node.getId());
}

void VisitorFilter::visitEnd(const structure::XmlElementSyntax& node , bool callVirtualBase /*= true*/) {
  (node.getFactory().*selector)(node.getId());
}

void VisitorFilter::visitEnd(const structure::XmlEmptyElementSyntax& node , bool callVirtualBase /*= true*/) {
  (node.getFactory().*selector)(node.getId());
}

void VisitorFilter::visitEnd(const structure::XmlNameAttributeSyntax& node , bool callVirtualBase /*= true*/) {
  (node.getFactory().*selector)(node.getId());
}

void VisitorFilter::visitEnd(const structure::XmlNameSyntax& node , bool callVirtualBase /*= true*/) {
  (node.getFactory().*selector)(node.getId());
}

void VisitorFilter::visitEnd(const structure::XmlPrefixSyntax& node , bool callVirtualBase /*= true*/) {
  (node.getFactory().*selector)(node.getId());
}

void VisitorFilter::visitEnd(const structure::XmlProcessingInstructionSyntax& node , bool callVirtualBase /*= true*/) {
  (node.getFactory().*selector)(node.getId());
}

void VisitorFilter::visitEnd(const structure::XmlTextAttributeSyntax& node , bool callVirtualBase /*= true*/) {
  (node.getFactory().*selector)(node.getId());
}

void VisitorFilter::visitEnd(const structure::XmlTextSyntax& node , bool callVirtualBase /*= true*/) {
  (node.getFactory().*selector)(node.getId());
}


}}}
