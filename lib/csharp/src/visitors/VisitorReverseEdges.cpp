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
VisitorReverseEdges::VisitorReverseEdges(ReverseEdges *reverseEdges) : VisitorAbstractNodes(), revEdges(reverseEdges) {
}

VisitorReverseEdges::~VisitorReverseEdges() {
}

void VisitorReverseEdges::visit(const base::Base &node, bool callVirtualBase ) {
  NodeId id = node.getId();
  if (!revEdges->reContainer[id])
    revEdges->reContainer[id] = new ReverseEdges::NodeEdgesType();
}

void VisitorReverseEdges::visitAliasQualifiedNameSyntax_Alias(const expression::AliasQualifiedNameSyntax& begin, const expression::IdentifierNameSyntax& end) {
  revEdges->insertEdge(&end, &begin, edkAliasQualifiedNameSyntax_Alias);
}

void VisitorReverseEdges::visitAliasQualifiedNameSyntax_Name(const expression::AliasQualifiedNameSyntax& begin, const expression::SimpleNameSyntax& end) {
  revEdges->insertEdge(&end, &begin, edkAliasQualifiedNameSyntax_Name);
}

void VisitorReverseEdges::visitAnonymousFunctionExpressionSyntax_Block(const expression::AnonymousFunctionExpressionSyntax& begin, const statement::BlockSyntax& end) {
  revEdges->insertEdge(&end, &begin, edkAnonymousFunctionExpressionSyntax_Block);
}

void VisitorReverseEdges::visitAnonymousFunctionExpressionSyntax_ExpressionBody(const expression::AnonymousFunctionExpressionSyntax& begin, const expression::ExpressionSyntax& end) {
  revEdges->insertEdge(&end, &begin, edkAnonymousFunctionExpressionSyntax_ExpressionBody);
}

void VisitorReverseEdges::visitAnonymousMethodExpressionSyntax_ParameterList(const expression::AnonymousMethodExpressionSyntax& begin, const structure::ParameterListSyntax& end) {
  revEdges->insertEdge(&end, &begin, edkAnonymousMethodExpressionSyntax_ParameterList);
}

void VisitorReverseEdges::visitAnonymousObjectCreationExpressionSyntax_Initializers(const expression::AnonymousObjectCreationExpressionSyntax& begin, const structure::AnonymousObjectMemberDeclaratorSyntax& end) {
  revEdges->insertEdge(&end, &begin, edkAnonymousObjectCreationExpressionSyntax_Initializers);
}

void VisitorReverseEdges::visitArrayCreationExpressionSyntax_Initializer(const expression::ArrayCreationExpressionSyntax& begin, const expression::InitializerExpressionSyntax& end) {
  revEdges->insertEdge(&end, &begin, edkArrayCreationExpressionSyntax_Initializer);
}

void VisitorReverseEdges::visitArrayCreationExpressionSyntax_Type(const expression::ArrayCreationExpressionSyntax& begin, const expression::ArrayTypeSyntax& end) {
  revEdges->insertEdge(&end, &begin, edkArrayCreationExpressionSyntax_Type);
}

void VisitorReverseEdges::visitArrayTypeSyntax_ElementType(const expression::ArrayTypeSyntax& begin, const expression::TypeSyntax& end) {
  revEdges->insertEdge(&end, &begin, edkArrayTypeSyntax_ElementType);
}

void VisitorReverseEdges::visitArrayTypeSyntax_RankSpecifiers(const expression::ArrayTypeSyntax& begin, const structure::ArrayRankSpecifierSyntax& end) {
  revEdges->insertEdge(&end, &begin, edkArrayTypeSyntax_RankSpecifiers);
}

void VisitorReverseEdges::visitAssignmentExpressionSyntax_EventAccessorCall(const expression::AssignmentExpressionSyntax& begin, const structure::AccessorDeclarationSyntax& end) {
  revEdges->insertEdge(&end, &begin, edkAssignmentExpressionSyntax_EventAccessorCall);
}

void VisitorReverseEdges::visitAssignmentExpressionSyntax_Left(const expression::AssignmentExpressionSyntax& begin, const expression::ExpressionSyntax& end) {
  revEdges->insertEdge(&end, &begin, edkAssignmentExpressionSyntax_Left);
}

void VisitorReverseEdges::visitAssignmentExpressionSyntax_OverloadedOperatorCall(const expression::AssignmentExpressionSyntax& begin, const structure::OperatorDeclarationSyntax& end) {
  revEdges->insertEdge(&end, &begin, edkAssignmentExpressionSyntax_OverloadedOperatorCall);
}

void VisitorReverseEdges::visitAssignmentExpressionSyntax_Right(const expression::AssignmentExpressionSyntax& begin, const expression::ExpressionSyntax& end) {
  revEdges->insertEdge(&end, &begin, edkAssignmentExpressionSyntax_Right);
}

void VisitorReverseEdges::visitAwaitExpressionSyntax_Expression(const expression::AwaitExpressionSyntax& begin, const expression::ExpressionSyntax& end) {
  revEdges->insertEdge(&end, &begin, edkAwaitExpressionSyntax_Expression);
}

void VisitorReverseEdges::visitBinaryExpressionSyntax_Left(const expression::BinaryExpressionSyntax& begin, const expression::ExpressionSyntax& end) {
  revEdges->insertEdge(&end, &begin, edkBinaryExpressionSyntax_Left);
}

void VisitorReverseEdges::visitBinaryExpressionSyntax_OverloadedOperatorCall(const expression::BinaryExpressionSyntax& begin, const structure::OperatorDeclarationSyntax& end) {
  revEdges->insertEdge(&end, &begin, edkBinaryExpressionSyntax_OverloadedOperatorCall);
}

void VisitorReverseEdges::visitBinaryExpressionSyntax_Right(const expression::BinaryExpressionSyntax& begin, const expression::ExpressionSyntax& end) {
  revEdges->insertEdge(&end, &begin, edkBinaryExpressionSyntax_Right);
}

void VisitorReverseEdges::visitCastExpressionSyntax_ConversionOperatorCall(const expression::CastExpressionSyntax& begin, const structure::ConversionOperatorDeclarationSyntax& end) {
  revEdges->insertEdge(&end, &begin, edkCastExpressionSyntax_ConversionOperatorCall);
}

void VisitorReverseEdges::visitCastExpressionSyntax_Expression(const expression::CastExpressionSyntax& begin, const expression::ExpressionSyntax& end) {
  revEdges->insertEdge(&end, &begin, edkCastExpressionSyntax_Expression);
}

void VisitorReverseEdges::visitCastExpressionSyntax_Type(const expression::CastExpressionSyntax& begin, const expression::TypeSyntax& end) {
  revEdges->insertEdge(&end, &begin, edkCastExpressionSyntax_Type);
}

void VisitorReverseEdges::visitCheckedExpressionSyntax_Expression(const expression::CheckedExpressionSyntax& begin, const expression::ExpressionSyntax& end) {
  revEdges->insertEdge(&end, &begin, edkCheckedExpressionSyntax_Expression);
}

void VisitorReverseEdges::visitConditionalAccessExpressionSyntax_Expression(const expression::ConditionalAccessExpressionSyntax& begin, const expression::ExpressionSyntax& end) {
  revEdges->insertEdge(&end, &begin, edkConditionalAccessExpressionSyntax_Expression);
}

void VisitorReverseEdges::visitConditionalAccessExpressionSyntax_WhenNotNull(const expression::ConditionalAccessExpressionSyntax& begin, const expression::ExpressionSyntax& end) {
  revEdges->insertEdge(&end, &begin, edkConditionalAccessExpressionSyntax_WhenNotNull);
}

void VisitorReverseEdges::visitConditionalExpressionSyntax_Condition(const expression::ConditionalExpressionSyntax& begin, const expression::ExpressionSyntax& end) {
  revEdges->insertEdge(&end, &begin, edkConditionalExpressionSyntax_Condition);
}

void VisitorReverseEdges::visitConditionalExpressionSyntax_WhenFalse(const expression::ConditionalExpressionSyntax& begin, const expression::ExpressionSyntax& end) {
  revEdges->insertEdge(&end, &begin, edkConditionalExpressionSyntax_WhenFalse);
}

void VisitorReverseEdges::visitConditionalExpressionSyntax_WhenTrue(const expression::ConditionalExpressionSyntax& begin, const expression::ExpressionSyntax& end) {
  revEdges->insertEdge(&end, &begin, edkConditionalExpressionSyntax_WhenTrue);
}

void VisitorReverseEdges::visitDeclarationExpressionSyntax_Designation(const expression::DeclarationExpressionSyntax& begin, const structure::VariableDesignationSyntax& end) {
  revEdges->insertEdge(&end, &begin, edkDeclarationExpressionSyntax_Designation);
}

void VisitorReverseEdges::visitDeclarationExpressionSyntax_Type(const expression::DeclarationExpressionSyntax& begin, const expression::TypeSyntax& end) {
  revEdges->insertEdge(&end, &begin, edkDeclarationExpressionSyntax_Type);
}

void VisitorReverseEdges::visitDefaultExpressionSyntax_Type(const expression::DefaultExpressionSyntax& begin, const expression::TypeSyntax& end) {
  revEdges->insertEdge(&end, &begin, edkDefaultExpressionSyntax_Type);
}

void VisitorReverseEdges::visitElementAccessExpressionSyntax_AccessorCall(const expression::ElementAccessExpressionSyntax& begin, const structure::AccessorDeclarationSyntax& end) {
  revEdges->insertEdge(&end, &begin, edkElementAccessExpressionSyntax_AccessorCall);
}

void VisitorReverseEdges::visitElementAccessExpressionSyntax_ArgumentList(const expression::ElementAccessExpressionSyntax& begin, const structure::BracketedArgumentListSyntax& end) {
  revEdges->insertEdge(&end, &begin, edkElementAccessExpressionSyntax_ArgumentList);
}

void VisitorReverseEdges::visitElementAccessExpressionSyntax_Expression(const expression::ElementAccessExpressionSyntax& begin, const expression::ExpressionSyntax& end) {
  revEdges->insertEdge(&end, &begin, edkElementAccessExpressionSyntax_Expression);
}

void VisitorReverseEdges::visitElementBindingExpressionSyntax_ArgumentList(const expression::ElementBindingExpressionSyntax& begin, const structure::BracketedArgumentListSyntax& end) {
  revEdges->insertEdge(&end, &begin, edkElementBindingExpressionSyntax_ArgumentList);
}

void VisitorReverseEdges::visitGenericNameSyntax_TypeArgumentList(const expression::GenericNameSyntax& begin, const structure::TypeArgumentListSyntax& end) {
  revEdges->insertEdge(&end, &begin, edkGenericNameSyntax_TypeArgumentList);
}

void VisitorReverseEdges::visitIdentifierNameSyntax_AccessorCall(const expression::IdentifierNameSyntax& begin, const structure::AccessorDeclarationSyntax& end) {
  revEdges->insertEdge(&end, &begin, edkIdentifierNameSyntax_AccessorCall);
}

void VisitorReverseEdges::visitIdentifierNameSyntax_Declaration(const expression::IdentifierNameSyntax& begin, const base::Positioned& end) {
  revEdges->insertEdge(&end, &begin, edkIdentifierNameSyntax_Declaration);
}

void VisitorReverseEdges::visitImplicitArrayCreationExpressionSyntax_Initializer(const expression::ImplicitArrayCreationExpressionSyntax& begin, const expression::InitializerExpressionSyntax& end) {
  revEdges->insertEdge(&end, &begin, edkImplicitArrayCreationExpressionSyntax_Initializer);
}

void VisitorReverseEdges::visitImplicitElementAccessSyntax_ArgumentList(const expression::ImplicitElementAccessSyntax& begin, const structure::BracketedArgumentListSyntax& end) {
  revEdges->insertEdge(&end, &begin, edkImplicitElementAccessSyntax_ArgumentList);
}

void VisitorReverseEdges::visitImplicitStackAllocArrayCreationExpressionSyntax_Initializer(const expression::ImplicitStackAllocArrayCreationExpressionSyntax& begin, const expression::InitializerExpressionSyntax& end) {
  revEdges->insertEdge(&end, &begin, edkImplicitStackAllocArrayCreationExpressionSyntax_Initializer);
}

void VisitorReverseEdges::visitInitializerExpressionSyntax_Expressions(const expression::InitializerExpressionSyntax& begin, const expression::ExpressionSyntax& end) {
  revEdges->insertEdge(&end, &begin, edkInitializerExpressionSyntax_Expressions);
}

void VisitorReverseEdges::visitInterpolatedStringExpressionSyntax_Contents(const expression::InterpolatedStringExpressionSyntax& begin, const structure::InterpolatedStringContentSyntax& end) {
  revEdges->insertEdge(&end, &begin, edkInterpolatedStringExpressionSyntax_Contents);
}

void VisitorReverseEdges::visitInvocationExpressionSyntax_ArgumentList(const expression::InvocationExpressionSyntax& begin, const structure::ArgumentListSyntax& end) {
  revEdges->insertEdge(&end, &begin, edkInvocationExpressionSyntax_ArgumentList);
}

void VisitorReverseEdges::visitInvocationExpressionSyntax_Expression(const expression::InvocationExpressionSyntax& begin, const expression::ExpressionSyntax& end) {
  revEdges->insertEdge(&end, &begin, edkInvocationExpressionSyntax_Expression);
}

void VisitorReverseEdges::visitInvocationExpressionSyntax_LocalFunctionCall(const expression::InvocationExpressionSyntax& begin, const statement::LocalFunctionStatementSyntax& end) {
  revEdges->insertEdge(&end, &begin, edkInvocationExpressionSyntax_LocalFunctionCall);
}

void VisitorReverseEdges::visitInvocationExpressionSyntax_MethodCall(const expression::InvocationExpressionSyntax& begin, const structure::MethodDeclarationSyntax& end) {
  revEdges->insertEdge(&end, &begin, edkInvocationExpressionSyntax_MethodCall);
}

void VisitorReverseEdges::visitIsPatternExpressionSyntax_Expression(const expression::IsPatternExpressionSyntax& begin, const expression::ExpressionSyntax& end) {
  revEdges->insertEdge(&end, &begin, edkIsPatternExpressionSyntax_Expression);
}

void VisitorReverseEdges::visitIsPatternExpressionSyntax_Pattern(const expression::IsPatternExpressionSyntax& begin, const structure::PatternSyntax& end) {
  revEdges->insertEdge(&end, &begin, edkIsPatternExpressionSyntax_Pattern);
}

void VisitorReverseEdges::visitMakeRefExpressionSyntax_Expression(const expression::MakeRefExpressionSyntax& begin, const expression::ExpressionSyntax& end) {
  revEdges->insertEdge(&end, &begin, edkMakeRefExpressionSyntax_Expression);
}

void VisitorReverseEdges::visitMemberAccessExpressionSyntax_Expression(const expression::MemberAccessExpressionSyntax& begin, const expression::ExpressionSyntax& end) {
  revEdges->insertEdge(&end, &begin, edkMemberAccessExpressionSyntax_Expression);
}

void VisitorReverseEdges::visitMemberAccessExpressionSyntax_Name(const expression::MemberAccessExpressionSyntax& begin, const expression::SimpleNameSyntax& end) {
  revEdges->insertEdge(&end, &begin, edkMemberAccessExpressionSyntax_Name);
}

void VisitorReverseEdges::visitMemberBindingExpressionSyntax_Name(const expression::MemberBindingExpressionSyntax& begin, const expression::SimpleNameSyntax& end) {
  revEdges->insertEdge(&end, &begin, edkMemberBindingExpressionSyntax_Name);
}

void VisitorReverseEdges::visitNullableTypeSyntax_ElementType(const expression::NullableTypeSyntax& begin, const expression::TypeSyntax& end) {
  revEdges->insertEdge(&end, &begin, edkNullableTypeSyntax_ElementType);
}

void VisitorReverseEdges::visitObjectCreationExpressionSyntax_ArgumentList(const expression::ObjectCreationExpressionSyntax& begin, const structure::ArgumentListSyntax& end) {
  revEdges->insertEdge(&end, &begin, edkObjectCreationExpressionSyntax_ArgumentList);
}

void VisitorReverseEdges::visitObjectCreationExpressionSyntax_ConstructorCall(const expression::ObjectCreationExpressionSyntax& begin, const structure::ConstructorDeclarationSyntax& end) {
  revEdges->insertEdge(&end, &begin, edkObjectCreationExpressionSyntax_ConstructorCall);
}

void VisitorReverseEdges::visitObjectCreationExpressionSyntax_Initializer(const expression::ObjectCreationExpressionSyntax& begin, const expression::InitializerExpressionSyntax& end) {
  revEdges->insertEdge(&end, &begin, edkObjectCreationExpressionSyntax_Initializer);
}

void VisitorReverseEdges::visitObjectCreationExpressionSyntax_Type(const expression::ObjectCreationExpressionSyntax& begin, const expression::TypeSyntax& end) {
  revEdges->insertEdge(&end, &begin, edkObjectCreationExpressionSyntax_Type);
}

void VisitorReverseEdges::visitParenthesizedExpressionSyntax_Expression(const expression::ParenthesizedExpressionSyntax& begin, const expression::ExpressionSyntax& end) {
  revEdges->insertEdge(&end, &begin, edkParenthesizedExpressionSyntax_Expression);
}

void VisitorReverseEdges::visitParenthesizedLambdaExpressionSyntax_ParameterList(const expression::ParenthesizedLambdaExpressionSyntax& begin, const structure::ParameterListSyntax& end) {
  revEdges->insertEdge(&end, &begin, edkParenthesizedLambdaExpressionSyntax_ParameterList);
}

void VisitorReverseEdges::visitPointerTypeSyntax_ElementType(const expression::PointerTypeSyntax& begin, const expression::TypeSyntax& end) {
  revEdges->insertEdge(&end, &begin, edkPointerTypeSyntax_ElementType);
}

void VisitorReverseEdges::visitPostfixUnaryExpressionSyntax_Operand(const expression::PostfixUnaryExpressionSyntax& begin, const expression::ExpressionSyntax& end) {
  revEdges->insertEdge(&end, &begin, edkPostfixUnaryExpressionSyntax_Operand);
}

void VisitorReverseEdges::visitPostfixUnaryExpressionSyntax_OverloadedOperatorCall(const expression::PostfixUnaryExpressionSyntax& begin, const structure::OperatorDeclarationSyntax& end) {
  revEdges->insertEdge(&end, &begin, edkPostfixUnaryExpressionSyntax_OverloadedOperatorCall);
}

void VisitorReverseEdges::visitPrefixUnaryExpressionSyntax_Operand(const expression::PrefixUnaryExpressionSyntax& begin, const expression::ExpressionSyntax& end) {
  revEdges->insertEdge(&end, &begin, edkPrefixUnaryExpressionSyntax_Operand);
}

void VisitorReverseEdges::visitPrefixUnaryExpressionSyntax_OverloadedOperatorCall(const expression::PrefixUnaryExpressionSyntax& begin, const structure::OperatorDeclarationSyntax& end) {
  revEdges->insertEdge(&end, &begin, edkPrefixUnaryExpressionSyntax_OverloadedOperatorCall);
}

void VisitorReverseEdges::visitQualifiedNameSyntax_Left(const expression::QualifiedNameSyntax& begin, const expression::NameSyntax& end) {
  revEdges->insertEdge(&end, &begin, edkQualifiedNameSyntax_Left);
}

void VisitorReverseEdges::visitQualifiedNameSyntax_Right(const expression::QualifiedNameSyntax& begin, const expression::SimpleNameSyntax& end) {
  revEdges->insertEdge(&end, &begin, edkQualifiedNameSyntax_Right);
}

void VisitorReverseEdges::visitQueryExpressionSyntax_Body(const expression::QueryExpressionSyntax& begin, const structure::QueryBodySyntax& end) {
  revEdges->insertEdge(&end, &begin, edkQueryExpressionSyntax_Body);
}

void VisitorReverseEdges::visitQueryExpressionSyntax_FromClause(const expression::QueryExpressionSyntax& begin, const structure::FromClauseSyntax& end) {
  revEdges->insertEdge(&end, &begin, edkQueryExpressionSyntax_FromClause);
}

void VisitorReverseEdges::visitRangeExpressionSyntax_LeftOperand(const expression::RangeExpressionSyntax& begin, const expression::ExpressionSyntax& end) {
  revEdges->insertEdge(&end, &begin, edkRangeExpressionSyntax_LeftOperand);
}

void VisitorReverseEdges::visitRangeExpressionSyntax_RightOperand(const expression::RangeExpressionSyntax& begin, const expression::ExpressionSyntax& end) {
  revEdges->insertEdge(&end, &begin, edkRangeExpressionSyntax_RightOperand);
}

void VisitorReverseEdges::visitRefExpressionSyntax_Expression(const expression::RefExpressionSyntax& begin, const expression::ExpressionSyntax& end) {
  revEdges->insertEdge(&end, &begin, edkRefExpressionSyntax_Expression);
}

void VisitorReverseEdges::visitRefTypeExpressionSyntax_Expression(const expression::RefTypeExpressionSyntax& begin, const expression::ExpressionSyntax& end) {
  revEdges->insertEdge(&end, &begin, edkRefTypeExpressionSyntax_Expression);
}

void VisitorReverseEdges::visitRefTypeSyntax_Type(const expression::RefTypeSyntax& begin, const expression::TypeSyntax& end) {
  revEdges->insertEdge(&end, &begin, edkRefTypeSyntax_Type);
}

void VisitorReverseEdges::visitRefValueExpressionSyntax_Expression(const expression::RefValueExpressionSyntax& begin, const expression::ExpressionSyntax& end) {
  revEdges->insertEdge(&end, &begin, edkRefValueExpressionSyntax_Expression);
}

void VisitorReverseEdges::visitRefValueExpressionSyntax_Type(const expression::RefValueExpressionSyntax& begin, const expression::TypeSyntax& end) {
  revEdges->insertEdge(&end, &begin, edkRefValueExpressionSyntax_Type);
}

void VisitorReverseEdges::visitSimpleLambdaExpressionSyntax_Parameter(const expression::SimpleLambdaExpressionSyntax& begin, const structure::ParameterSyntax& end) {
  revEdges->insertEdge(&end, &begin, edkSimpleLambdaExpressionSyntax_Parameter);
}

void VisitorReverseEdges::visitSizeOfExpressionSyntax_Type(const expression::SizeOfExpressionSyntax& begin, const expression::TypeSyntax& end) {
  revEdges->insertEdge(&end, &begin, edkSizeOfExpressionSyntax_Type);
}

void VisitorReverseEdges::visitStackAllocArrayCreationExpressionSyntax_Initializer(const expression::StackAllocArrayCreationExpressionSyntax& begin, const expression::InitializerExpressionSyntax& end) {
  revEdges->insertEdge(&end, &begin, edkStackAllocArrayCreationExpressionSyntax_Initializer);
}

void VisitorReverseEdges::visitStackAllocArrayCreationExpressionSyntax_Type(const expression::StackAllocArrayCreationExpressionSyntax& begin, const expression::TypeSyntax& end) {
  revEdges->insertEdge(&end, &begin, edkStackAllocArrayCreationExpressionSyntax_Type);
}

void VisitorReverseEdges::visitSwitchExpressionSyntax_Arms(const expression::SwitchExpressionSyntax& begin, const structure::SwitchExpressionArmSyntax& end) {
  revEdges->insertEdge(&end, &begin, edkSwitchExpressionSyntax_Arms);
}

void VisitorReverseEdges::visitSwitchExpressionSyntax_GoverningExpression(const expression::SwitchExpressionSyntax& begin, const expression::ExpressionSyntax& end) {
  revEdges->insertEdge(&end, &begin, edkSwitchExpressionSyntax_GoverningExpression);
}

void VisitorReverseEdges::visitThrowExpressionSyntax_Expression(const expression::ThrowExpressionSyntax& begin, const expression::ExpressionSyntax& end) {
  revEdges->insertEdge(&end, &begin, edkThrowExpressionSyntax_Expression);
}

void VisitorReverseEdges::visitTupleExpressionSyntax_Arguments(const expression::TupleExpressionSyntax& begin, const structure::ArgumentSyntax& end) {
  revEdges->insertEdge(&end, &begin, edkTupleExpressionSyntax_Arguments);
}

void VisitorReverseEdges::visitTupleTypeSyntax_Elements(const expression::TupleTypeSyntax& begin, const structure::TupleElementSyntax& end) {
  revEdges->insertEdge(&end, &begin, edkTupleTypeSyntax_Elements);
}

void VisitorReverseEdges::visitTypeOfExpressionSyntax_Type(const expression::TypeOfExpressionSyntax& begin, const expression::TypeSyntax& end) {
  revEdges->insertEdge(&end, &begin, edkTypeOfExpressionSyntax_Type);
}

void VisitorReverseEdges::visitTypeSyntax_OriginalDefinition(const expression::TypeSyntax& begin, const structure::MemberDeclarationSyntax& end) {
  revEdges->insertEdge(&end, &begin, edkTypeSyntax_OriginalDefinition);
}

void VisitorReverseEdges::visitBlockSyntax_Statements(const statement::BlockSyntax& begin, const statement::StatementSyntax& end) {
  revEdges->insertEdge(&end, &begin, edkBlockSyntax_Statements);
}

void VisitorReverseEdges::visitCheckedStatementSyntax_Block(const statement::CheckedStatementSyntax& begin, const statement::BlockSyntax& end) {
  revEdges->insertEdge(&end, &begin, edkCheckedStatementSyntax_Block);
}

void VisitorReverseEdges::visitCommonForEachStatementSyntax_Expression(const statement::CommonForEachStatementSyntax& begin, const expression::ExpressionSyntax& end) {
  revEdges->insertEdge(&end, &begin, edkCommonForEachStatementSyntax_Expression);
}

void VisitorReverseEdges::visitCommonForEachStatementSyntax_Statement(const statement::CommonForEachStatementSyntax& begin, const statement::StatementSyntax& end) {
  revEdges->insertEdge(&end, &begin, edkCommonForEachStatementSyntax_Statement);
}

void VisitorReverseEdges::visitDoStatementSyntax_Condition(const statement::DoStatementSyntax& begin, const expression::ExpressionSyntax& end) {
  revEdges->insertEdge(&end, &begin, edkDoStatementSyntax_Condition);
}

void VisitorReverseEdges::visitDoStatementSyntax_Statement(const statement::DoStatementSyntax& begin, const statement::StatementSyntax& end) {
  revEdges->insertEdge(&end, &begin, edkDoStatementSyntax_Statement);
}

void VisitorReverseEdges::visitExpressionStatementSyntax_Expression(const statement::ExpressionStatementSyntax& begin, const expression::ExpressionSyntax& end) {
  revEdges->insertEdge(&end, &begin, edkExpressionStatementSyntax_Expression);
}

void VisitorReverseEdges::visitFixedStatementSyntax_Declaration(const statement::FixedStatementSyntax& begin, const structure::VariableDeclarationSyntax& end) {
  revEdges->insertEdge(&end, &begin, edkFixedStatementSyntax_Declaration);
}

void VisitorReverseEdges::visitFixedStatementSyntax_Statement(const statement::FixedStatementSyntax& begin, const statement::StatementSyntax& end) {
  revEdges->insertEdge(&end, &begin, edkFixedStatementSyntax_Statement);
}

void VisitorReverseEdges::visitForEachStatementSyntax_Type(const statement::ForEachStatementSyntax& begin, const expression::TypeSyntax& end) {
  revEdges->insertEdge(&end, &begin, edkForEachStatementSyntax_Type);
}

void VisitorReverseEdges::visitForEachVariableStatementSyntax_Variable(const statement::ForEachVariableStatementSyntax& begin, const expression::ExpressionSyntax& end) {
  revEdges->insertEdge(&end, &begin, edkForEachVariableStatementSyntax_Variable);
}

void VisitorReverseEdges::visitForStatementSyntax_Condition(const statement::ForStatementSyntax& begin, const expression::ExpressionSyntax& end) {
  revEdges->insertEdge(&end, &begin, edkForStatementSyntax_Condition);
}

void VisitorReverseEdges::visitForStatementSyntax_Declaration(const statement::ForStatementSyntax& begin, const structure::VariableDeclarationSyntax& end) {
  revEdges->insertEdge(&end, &begin, edkForStatementSyntax_Declaration);
}

void VisitorReverseEdges::visitForStatementSyntax_Incrementors(const statement::ForStatementSyntax& begin, const expression::ExpressionSyntax& end) {
  revEdges->insertEdge(&end, &begin, edkForStatementSyntax_Incrementors);
}

void VisitorReverseEdges::visitForStatementSyntax_Initializers(const statement::ForStatementSyntax& begin, const expression::ExpressionSyntax& end) {
  revEdges->insertEdge(&end, &begin, edkForStatementSyntax_Initializers);
}

void VisitorReverseEdges::visitForStatementSyntax_Statement(const statement::ForStatementSyntax& begin, const statement::StatementSyntax& end) {
  revEdges->insertEdge(&end, &begin, edkForStatementSyntax_Statement);
}

void VisitorReverseEdges::visitGotoStatementSyntax_Expression(const statement::GotoStatementSyntax& begin, const expression::ExpressionSyntax& end) {
  revEdges->insertEdge(&end, &begin, edkGotoStatementSyntax_Expression);
}

void VisitorReverseEdges::visitIfStatementSyntax_Condition(const statement::IfStatementSyntax& begin, const expression::ExpressionSyntax& end) {
  revEdges->insertEdge(&end, &begin, edkIfStatementSyntax_Condition);
}

void VisitorReverseEdges::visitIfStatementSyntax_Else(const statement::IfStatementSyntax& begin, const structure::ElseClauseSyntax& end) {
  revEdges->insertEdge(&end, &begin, edkIfStatementSyntax_Else);
}

void VisitorReverseEdges::visitIfStatementSyntax_Statement(const statement::IfStatementSyntax& begin, const statement::StatementSyntax& end) {
  revEdges->insertEdge(&end, &begin, edkIfStatementSyntax_Statement);
}

void VisitorReverseEdges::visitLabeledStatementSyntax_Statement(const statement::LabeledStatementSyntax& begin, const statement::StatementSyntax& end) {
  revEdges->insertEdge(&end, &begin, edkLabeledStatementSyntax_Statement);
}

void VisitorReverseEdges::visitLocalDeclarationStatementSyntax_Declaration(const statement::LocalDeclarationStatementSyntax& begin, const structure::VariableDeclarationSyntax& end) {
  revEdges->insertEdge(&end, &begin, edkLocalDeclarationStatementSyntax_Declaration);
}

void VisitorReverseEdges::visitLocalFunctionStatementSyntax_Body(const statement::LocalFunctionStatementSyntax& begin, const statement::BlockSyntax& end) {
  revEdges->insertEdge(&end, &begin, edkLocalFunctionStatementSyntax_Body);
}

void VisitorReverseEdges::visitLocalFunctionStatementSyntax_ConstraintClauses(const statement::LocalFunctionStatementSyntax& begin, const structure::TypeParameterConstraintClauseSyntax& end) {
  revEdges->insertEdge(&end, &begin, edkLocalFunctionStatementSyntax_ConstraintClauses);
}

void VisitorReverseEdges::visitLocalFunctionStatementSyntax_ExpressionBody(const statement::LocalFunctionStatementSyntax& begin, const structure::ArrowExpressionClauseSyntax& end) {
  revEdges->insertEdge(&end, &begin, edkLocalFunctionStatementSyntax_ExpressionBody);
}

void VisitorReverseEdges::visitLocalFunctionStatementSyntax_ParameterList(const statement::LocalFunctionStatementSyntax& begin, const structure::ParameterListSyntax& end) {
  revEdges->insertEdge(&end, &begin, edkLocalFunctionStatementSyntax_ParameterList);
}

void VisitorReverseEdges::visitLocalFunctionStatementSyntax_ReturnType(const statement::LocalFunctionStatementSyntax& begin, const expression::TypeSyntax& end) {
  revEdges->insertEdge(&end, &begin, edkLocalFunctionStatementSyntax_ReturnType);
}

void VisitorReverseEdges::visitLocalFunctionStatementSyntax_TypeParameterList(const statement::LocalFunctionStatementSyntax& begin, const structure::TypeParameterListSyntax& end) {
  revEdges->insertEdge(&end, &begin, edkLocalFunctionStatementSyntax_TypeParameterList);
}

void VisitorReverseEdges::visitLockStatementSyntax_Expression(const statement::LockStatementSyntax& begin, const expression::ExpressionSyntax& end) {
  revEdges->insertEdge(&end, &begin, edkLockStatementSyntax_Expression);
}

void VisitorReverseEdges::visitLockStatementSyntax_Statement(const statement::LockStatementSyntax& begin, const statement::StatementSyntax& end) {
  revEdges->insertEdge(&end, &begin, edkLockStatementSyntax_Statement);
}

void VisitorReverseEdges::visitReturnStatementSyntax_Expression(const statement::ReturnStatementSyntax& begin, const expression::ExpressionSyntax& end) {
  revEdges->insertEdge(&end, &begin, edkReturnStatementSyntax_Expression);
}

void VisitorReverseEdges::visitStatementSyntax_AttributeLists(const statement::StatementSyntax& begin, const structure::AttributeListSyntax& end) {
  revEdges->insertEdge(&end, &begin, edkStatementSyntax_AttributeLists);
}

void VisitorReverseEdges::visitSwitchStatementSyntax_Expression(const statement::SwitchStatementSyntax& begin, const expression::ExpressionSyntax& end) {
  revEdges->insertEdge(&end, &begin, edkSwitchStatementSyntax_Expression);
}

void VisitorReverseEdges::visitSwitchStatementSyntax_Sections(const statement::SwitchStatementSyntax& begin, const structure::SwitchSectionSyntax& end) {
  revEdges->insertEdge(&end, &begin, edkSwitchStatementSyntax_Sections);
}

void VisitorReverseEdges::visitThrowStatementSyntax_Expression(const statement::ThrowStatementSyntax& begin, const expression::ExpressionSyntax& end) {
  revEdges->insertEdge(&end, &begin, edkThrowStatementSyntax_Expression);
}

void VisitorReverseEdges::visitTryStatementSyntax_Block(const statement::TryStatementSyntax& begin, const statement::BlockSyntax& end) {
  revEdges->insertEdge(&end, &begin, edkTryStatementSyntax_Block);
}

void VisitorReverseEdges::visitTryStatementSyntax_Catches(const statement::TryStatementSyntax& begin, const structure::CatchClauseSyntax& end) {
  revEdges->insertEdge(&end, &begin, edkTryStatementSyntax_Catches);
}

void VisitorReverseEdges::visitTryStatementSyntax_Finally(const statement::TryStatementSyntax& begin, const structure::FinallyClauseSyntax& end) {
  revEdges->insertEdge(&end, &begin, edkTryStatementSyntax_Finally);
}

void VisitorReverseEdges::visitUnsafeStatementSyntax_Block(const statement::UnsafeStatementSyntax& begin, const statement::BlockSyntax& end) {
  revEdges->insertEdge(&end, &begin, edkUnsafeStatementSyntax_Block);
}

void VisitorReverseEdges::visitUsingStatementSyntax_Declaration(const statement::UsingStatementSyntax& begin, const structure::VariableDeclarationSyntax& end) {
  revEdges->insertEdge(&end, &begin, edkUsingStatementSyntax_Declaration);
}

void VisitorReverseEdges::visitUsingStatementSyntax_Expression(const statement::UsingStatementSyntax& begin, const expression::ExpressionSyntax& end) {
  revEdges->insertEdge(&end, &begin, edkUsingStatementSyntax_Expression);
}

void VisitorReverseEdges::visitUsingStatementSyntax_Statement(const statement::UsingStatementSyntax& begin, const statement::StatementSyntax& end) {
  revEdges->insertEdge(&end, &begin, edkUsingStatementSyntax_Statement);
}

void VisitorReverseEdges::visitWhileStatementSyntax_Condition(const statement::WhileStatementSyntax& begin, const expression::ExpressionSyntax& end) {
  revEdges->insertEdge(&end, &begin, edkWhileStatementSyntax_Condition);
}

void VisitorReverseEdges::visitWhileStatementSyntax_Statement(const statement::WhileStatementSyntax& begin, const statement::StatementSyntax& end) {
  revEdges->insertEdge(&end, &begin, edkWhileStatementSyntax_Statement);
}

void VisitorReverseEdges::visitYieldStatementSyntax_Expression(const statement::YieldStatementSyntax& begin, const expression::ExpressionSyntax& end) {
  revEdges->insertEdge(&end, &begin, edkYieldStatementSyntax_Expression);
}

void VisitorReverseEdges::visitAccessorDeclarationSyntax_AttributeLists(const structure::AccessorDeclarationSyntax& begin, const structure::AttributeListSyntax& end) {
  revEdges->insertEdge(&end, &begin, edkAccessorDeclarationSyntax_AttributeLists);
}

void VisitorReverseEdges::visitAccessorDeclarationSyntax_Body(const structure::AccessorDeclarationSyntax& begin, const statement::BlockSyntax& end) {
  revEdges->insertEdge(&end, &begin, edkAccessorDeclarationSyntax_Body);
}

void VisitorReverseEdges::visitAccessorDeclarationSyntax_ExpressionBody(const structure::AccessorDeclarationSyntax& begin, const structure::ArrowExpressionClauseSyntax& end) {
  revEdges->insertEdge(&end, &begin, edkAccessorDeclarationSyntax_ExpressionBody);
}

void VisitorReverseEdges::visitAccessorListSyntax_Accessors(const structure::AccessorListSyntax& begin, const structure::AccessorDeclarationSyntax& end) {
  revEdges->insertEdge(&end, &begin, edkAccessorListSyntax_Accessors);
}

void VisitorReverseEdges::visitAnonymousObjectMemberDeclaratorSyntax_Expression(const structure::AnonymousObjectMemberDeclaratorSyntax& begin, const expression::ExpressionSyntax& end) {
  revEdges->insertEdge(&end, &begin, edkAnonymousObjectMemberDeclaratorSyntax_Expression);
}

void VisitorReverseEdges::visitAnonymousObjectMemberDeclaratorSyntax_NameEquals(const structure::AnonymousObjectMemberDeclaratorSyntax& begin, const structure::NameEqualsSyntax& end) {
  revEdges->insertEdge(&end, &begin, edkAnonymousObjectMemberDeclaratorSyntax_NameEquals);
}

void VisitorReverseEdges::visitArgumentSyntax_Expression(const structure::ArgumentSyntax& begin, const expression::ExpressionSyntax& end) {
  revEdges->insertEdge(&end, &begin, edkArgumentSyntax_Expression);
}

void VisitorReverseEdges::visitArgumentSyntax_NameColon(const structure::ArgumentSyntax& begin, const structure::NameColonSyntax& end) {
  revEdges->insertEdge(&end, &begin, edkArgumentSyntax_NameColon);
}

void VisitorReverseEdges::visitArrayRankSpecifierSyntax_Sizes(const structure::ArrayRankSpecifierSyntax& begin, const expression::ExpressionSyntax& end) {
  revEdges->insertEdge(&end, &begin, edkArrayRankSpecifierSyntax_Sizes);
}

void VisitorReverseEdges::visitArrowExpressionClauseSyntax_Expression(const structure::ArrowExpressionClauseSyntax& begin, const expression::ExpressionSyntax& end) {
  revEdges->insertEdge(&end, &begin, edkArrowExpressionClauseSyntax_Expression);
}

void VisitorReverseEdges::visitAttributeArgumentListSyntax_Arguments(const structure::AttributeArgumentListSyntax& begin, const structure::AttributeArgumentSyntax& end) {
  revEdges->insertEdge(&end, &begin, edkAttributeArgumentListSyntax_Arguments);
}

void VisitorReverseEdges::visitAttributeArgumentSyntax_Expression(const structure::AttributeArgumentSyntax& begin, const expression::ExpressionSyntax& end) {
  revEdges->insertEdge(&end, &begin, edkAttributeArgumentSyntax_Expression);
}

void VisitorReverseEdges::visitAttributeArgumentSyntax_NameColon(const structure::AttributeArgumentSyntax& begin, const structure::NameColonSyntax& end) {
  revEdges->insertEdge(&end, &begin, edkAttributeArgumentSyntax_NameColon);
}

void VisitorReverseEdges::visitAttributeArgumentSyntax_NameEquals(const structure::AttributeArgumentSyntax& begin, const structure::NameEqualsSyntax& end) {
  revEdges->insertEdge(&end, &begin, edkAttributeArgumentSyntax_NameEquals);
}

void VisitorReverseEdges::visitAttributeListSyntax_Attributes(const structure::AttributeListSyntax& begin, const structure::AttributeSyntax& end) {
  revEdges->insertEdge(&end, &begin, edkAttributeListSyntax_Attributes);
}

void VisitorReverseEdges::visitAttributeListSyntax_Target(const structure::AttributeListSyntax& begin, const structure::AttributeTargetSpecifierSyntax& end) {
  revEdges->insertEdge(&end, &begin, edkAttributeListSyntax_Target);
}

void VisitorReverseEdges::visitAttributeSyntax_ArgumentList(const structure::AttributeSyntax& begin, const structure::AttributeArgumentListSyntax& end) {
  revEdges->insertEdge(&end, &begin, edkAttributeSyntax_ArgumentList);
}

void VisitorReverseEdges::visitAttributeSyntax_Name(const structure::AttributeSyntax& begin, const expression::NameSyntax& end) {
  revEdges->insertEdge(&end, &begin, edkAttributeSyntax_Name);
}

void VisitorReverseEdges::visitBaseArgumentListSyntax_Arguments(const structure::BaseArgumentListSyntax& begin, const structure::ArgumentSyntax& end) {
  revEdges->insertEdge(&end, &begin, edkBaseArgumentListSyntax_Arguments);
}

void VisitorReverseEdges::visitBaseCrefParameterListSyntax_Parameters(const structure::BaseCrefParameterListSyntax& begin, const structure::CrefParameterSyntax& end) {
  revEdges->insertEdge(&end, &begin, edkBaseCrefParameterListSyntax_Parameters);
}

void VisitorReverseEdges::visitBaseFieldDeclarationSyntax_AttributeLists(const structure::BaseFieldDeclarationSyntax& begin, const structure::AttributeListSyntax& end) {
  revEdges->insertEdge(&end, &begin, edkBaseFieldDeclarationSyntax_AttributeLists);
}

void VisitorReverseEdges::visitBaseFieldDeclarationSyntax_Declaration(const structure::BaseFieldDeclarationSyntax& begin, const structure::VariableDeclarationSyntax& end) {
  revEdges->insertEdge(&end, &begin, edkBaseFieldDeclarationSyntax_Declaration);
}

void VisitorReverseEdges::visitBaseListSyntax_Types(const structure::BaseListSyntax& begin, const structure::BaseTypeSyntax& end) {
  revEdges->insertEdge(&end, &begin, edkBaseListSyntax_Types);
}

void VisitorReverseEdges::visitBaseMethodDeclarationSyntax_AccessedEnumMembers(const structure::BaseMethodDeclarationSyntax& begin, const structure::EnumMemberDeclarationSyntax& end) {
  revEdges->insertEdge(&end, &begin, edkBaseMethodDeclarationSyntax_AccessedEnumMembers);
}

void VisitorReverseEdges::visitBaseMethodDeclarationSyntax_AttributeLists(const structure::BaseMethodDeclarationSyntax& begin, const structure::AttributeListSyntax& end) {
  revEdges->insertEdge(&end, &begin, edkBaseMethodDeclarationSyntax_AttributeLists);
}

void VisitorReverseEdges::visitBaseMethodDeclarationSyntax_Body(const structure::BaseMethodDeclarationSyntax& begin, const statement::BlockSyntax& end) {
  revEdges->insertEdge(&end, &begin, edkBaseMethodDeclarationSyntax_Body);
}

void VisitorReverseEdges::visitBaseMethodDeclarationSyntax_ExpressionBody(const structure::BaseMethodDeclarationSyntax& begin, const structure::ArrowExpressionClauseSyntax& end) {
  revEdges->insertEdge(&end, &begin, edkBaseMethodDeclarationSyntax_ExpressionBody);
}

void VisitorReverseEdges::visitBaseMethodDeclarationSyntax_ParameterList(const structure::BaseMethodDeclarationSyntax& begin, const structure::ParameterListSyntax& end) {
  revEdges->insertEdge(&end, &begin, edkBaseMethodDeclarationSyntax_ParameterList);
}

void VisitorReverseEdges::visitBaseParameterListSyntax_Parameters(const structure::BaseParameterListSyntax& begin, const structure::ParameterSyntax& end) {
  revEdges->insertEdge(&end, &begin, edkBaseParameterListSyntax_Parameters);
}

void VisitorReverseEdges::visitBasePropertyDeclarationSyntax_AccessorList(const structure::BasePropertyDeclarationSyntax& begin, const structure::AccessorListSyntax& end) {
  revEdges->insertEdge(&end, &begin, edkBasePropertyDeclarationSyntax_AccessorList);
}

void VisitorReverseEdges::visitBasePropertyDeclarationSyntax_AttributeLists(const structure::BasePropertyDeclarationSyntax& begin, const structure::AttributeListSyntax& end) {
  revEdges->insertEdge(&end, &begin, edkBasePropertyDeclarationSyntax_AttributeLists);
}

void VisitorReverseEdges::visitBasePropertyDeclarationSyntax_ExplicitInterfaceSpecifier(const structure::BasePropertyDeclarationSyntax& begin, const structure::ExplicitInterfaceSpecifierSyntax& end) {
  revEdges->insertEdge(&end, &begin, edkBasePropertyDeclarationSyntax_ExplicitInterfaceSpecifier);
}

void VisitorReverseEdges::visitBasePropertyDeclarationSyntax_Type(const structure::BasePropertyDeclarationSyntax& begin, const expression::TypeSyntax& end) {
  revEdges->insertEdge(&end, &begin, edkBasePropertyDeclarationSyntax_Type);
}

void VisitorReverseEdges::visitBaseTypeDeclarationSyntax_AttributeLists(const structure::BaseTypeDeclarationSyntax& begin, const structure::AttributeListSyntax& end) {
  revEdges->insertEdge(&end, &begin, edkBaseTypeDeclarationSyntax_AttributeLists);
}

void VisitorReverseEdges::visitBaseTypeDeclarationSyntax_BaseList(const structure::BaseTypeDeclarationSyntax& begin, const structure::BaseListSyntax& end) {
  revEdges->insertEdge(&end, &begin, edkBaseTypeDeclarationSyntax_BaseList);
}

void VisitorReverseEdges::visitBaseTypeSyntax_Type(const structure::BaseTypeSyntax& begin, const expression::TypeSyntax& end) {
  revEdges->insertEdge(&end, &begin, edkBaseTypeSyntax_Type);
}

void VisitorReverseEdges::visitCasePatternSwitchLabelSyntax_Pattern(const structure::CasePatternSwitchLabelSyntax& begin, const structure::PatternSyntax& end) {
  revEdges->insertEdge(&end, &begin, edkCasePatternSwitchLabelSyntax_Pattern);
}

void VisitorReverseEdges::visitCasePatternSwitchLabelSyntax_WhenClause(const structure::CasePatternSwitchLabelSyntax& begin, const structure::WhenClauseSyntax& end) {
  revEdges->insertEdge(&end, &begin, edkCasePatternSwitchLabelSyntax_WhenClause);
}

void VisitorReverseEdges::visitCaseSwitchLabelSyntax_Value(const structure::CaseSwitchLabelSyntax& begin, const expression::ExpressionSyntax& end) {
  revEdges->insertEdge(&end, &begin, edkCaseSwitchLabelSyntax_Value);
}

void VisitorReverseEdges::visitCatchClauseSyntax_Block(const structure::CatchClauseSyntax& begin, const statement::BlockSyntax& end) {
  revEdges->insertEdge(&end, &begin, edkCatchClauseSyntax_Block);
}

void VisitorReverseEdges::visitCatchClauseSyntax_Declaration(const structure::CatchClauseSyntax& begin, const structure::CatchDeclarationSyntax& end) {
  revEdges->insertEdge(&end, &begin, edkCatchClauseSyntax_Declaration);
}

void VisitorReverseEdges::visitCatchClauseSyntax_Filter(const structure::CatchClauseSyntax& begin, const structure::CatchFilterClauseSyntax& end) {
  revEdges->insertEdge(&end, &begin, edkCatchClauseSyntax_Filter);
}

void VisitorReverseEdges::visitCatchDeclarationSyntax_Type(const structure::CatchDeclarationSyntax& begin, const expression::TypeSyntax& end) {
  revEdges->insertEdge(&end, &begin, edkCatchDeclarationSyntax_Type);
}

void VisitorReverseEdges::visitCatchFilterClauseSyntax_FilterExpression(const structure::CatchFilterClauseSyntax& begin, const expression::ExpressionSyntax& end) {
  revEdges->insertEdge(&end, &begin, edkCatchFilterClauseSyntax_FilterExpression);
}

void VisitorReverseEdges::visitCompilationUnitSyntax_AttributeLists(const structure::CompilationUnitSyntax& begin, const structure::AttributeListSyntax& end) {
  revEdges->insertEdge(&end, &begin, edkCompilationUnitSyntax_AttributeLists);
}

void VisitorReverseEdges::visitCompilationUnitSyntax_Externs(const structure::CompilationUnitSyntax& begin, const structure::ExternAliasDirectiveSyntax& end) {
  revEdges->insertEdge(&end, &begin, edkCompilationUnitSyntax_Externs);
}

void VisitorReverseEdges::visitCompilationUnitSyntax_Members(const structure::CompilationUnitSyntax& begin, const structure::MemberDeclarationSyntax& end) {
  revEdges->insertEdge(&end, &begin, edkCompilationUnitSyntax_Members);
}

void VisitorReverseEdges::visitCompilationUnitSyntax_Usings(const structure::CompilationUnitSyntax& begin, const structure::UsingDirectiveSyntax& end) {
  revEdges->insertEdge(&end, &begin, edkCompilationUnitSyntax_Usings);
}

void VisitorReverseEdges::visitConstantPatternSyntax_Expression(const structure::ConstantPatternSyntax& begin, const expression::ExpressionSyntax& end) {
  revEdges->insertEdge(&end, &begin, edkConstantPatternSyntax_Expression);
}

void VisitorReverseEdges::visitConstructorDeclarationSyntax_Initializer(const structure::ConstructorDeclarationSyntax& begin, const structure::ConstructorInitializerSyntax& end) {
  revEdges->insertEdge(&end, &begin, edkConstructorDeclarationSyntax_Initializer);
}

void VisitorReverseEdges::visitConstructorInitializerSyntax_ArgumentList(const structure::ConstructorInitializerSyntax& begin, const structure::ArgumentListSyntax& end) {
  revEdges->insertEdge(&end, &begin, edkConstructorInitializerSyntax_ArgumentList);
}

void VisitorReverseEdges::visitConstructorInitializerSyntax_ConstructorCall(const structure::ConstructorInitializerSyntax& begin, const structure::ConstructorDeclarationSyntax& end) {
  revEdges->insertEdge(&end, &begin, edkConstructorInitializerSyntax_ConstructorCall);
}

void VisitorReverseEdges::visitConversionOperatorDeclarationSyntax_Type(const structure::ConversionOperatorDeclarationSyntax& begin, const expression::TypeSyntax& end) {
  revEdges->insertEdge(&end, &begin, edkConversionOperatorDeclarationSyntax_Type);
}

void VisitorReverseEdges::visitConversionOperatorMemberCrefSyntax_Parameters(const structure::ConversionOperatorMemberCrefSyntax& begin, const structure::CrefParameterListSyntax& end) {
  revEdges->insertEdge(&end, &begin, edkConversionOperatorMemberCrefSyntax_Parameters);
}

void VisitorReverseEdges::visitConversionOperatorMemberCrefSyntax_Type(const structure::ConversionOperatorMemberCrefSyntax& begin, const expression::TypeSyntax& end) {
  revEdges->insertEdge(&end, &begin, edkConversionOperatorMemberCrefSyntax_Type);
}

void VisitorReverseEdges::visitCrefParameterSyntax_Type(const structure::CrefParameterSyntax& begin, const expression::TypeSyntax& end) {
  revEdges->insertEdge(&end, &begin, edkCrefParameterSyntax_Type);
}

void VisitorReverseEdges::visitDeclarationPatternSyntax_Designation(const structure::DeclarationPatternSyntax& begin, const structure::VariableDesignationSyntax& end) {
  revEdges->insertEdge(&end, &begin, edkDeclarationPatternSyntax_Designation);
}

void VisitorReverseEdges::visitDeclarationPatternSyntax_Type(const structure::DeclarationPatternSyntax& begin, const expression::TypeSyntax& end) {
  revEdges->insertEdge(&end, &begin, edkDeclarationPatternSyntax_Type);
}

void VisitorReverseEdges::visitDelegateDeclarationSyntax_AttributeLists(const structure::DelegateDeclarationSyntax& begin, const structure::AttributeListSyntax& end) {
  revEdges->insertEdge(&end, &begin, edkDelegateDeclarationSyntax_AttributeLists);
}

void VisitorReverseEdges::visitDelegateDeclarationSyntax_ConstraintClauses(const structure::DelegateDeclarationSyntax& begin, const structure::TypeParameterConstraintClauseSyntax& end) {
  revEdges->insertEdge(&end, &begin, edkDelegateDeclarationSyntax_ConstraintClauses);
}

void VisitorReverseEdges::visitDelegateDeclarationSyntax_ParameterList(const structure::DelegateDeclarationSyntax& begin, const structure::ParameterListSyntax& end) {
  revEdges->insertEdge(&end, &begin, edkDelegateDeclarationSyntax_ParameterList);
}

void VisitorReverseEdges::visitDelegateDeclarationSyntax_ReturnType(const structure::DelegateDeclarationSyntax& begin, const expression::TypeSyntax& end) {
  revEdges->insertEdge(&end, &begin, edkDelegateDeclarationSyntax_ReturnType);
}

void VisitorReverseEdges::visitElseClauseSyntax_Statement(const structure::ElseClauseSyntax& begin, const statement::StatementSyntax& end) {
  revEdges->insertEdge(&end, &begin, edkElseClauseSyntax_Statement);
}

void VisitorReverseEdges::visitEnumDeclarationSyntax_Members(const structure::EnumDeclarationSyntax& begin, const structure::EnumMemberDeclarationSyntax& end) {
  revEdges->insertEdge(&end, &begin, edkEnumDeclarationSyntax_Members);
}

void VisitorReverseEdges::visitEnumMemberDeclarationSyntax_AttributeLists(const structure::EnumMemberDeclarationSyntax& begin, const structure::AttributeListSyntax& end) {
  revEdges->insertEdge(&end, &begin, edkEnumMemberDeclarationSyntax_AttributeLists);
}

void VisitorReverseEdges::visitEnumMemberDeclarationSyntax_EqualsValue(const structure::EnumMemberDeclarationSyntax& begin, const structure::EqualsValueClauseSyntax& end) {
  revEdges->insertEdge(&end, &begin, edkEnumMemberDeclarationSyntax_EqualsValue);
}

void VisitorReverseEdges::visitEqualsValueClauseSyntax_Value(const structure::EqualsValueClauseSyntax& begin, const expression::ExpressionSyntax& end) {
  revEdges->insertEdge(&end, &begin, edkEqualsValueClauseSyntax_Value);
}

void VisitorReverseEdges::visitExplicitInterfaceSpecifierSyntax_Name(const structure::ExplicitInterfaceSpecifierSyntax& begin, const expression::NameSyntax& end) {
  revEdges->insertEdge(&end, &begin, edkExplicitInterfaceSpecifierSyntax_Name);
}

void VisitorReverseEdges::visitFinallyClauseSyntax_Block(const structure::FinallyClauseSyntax& begin, const statement::BlockSyntax& end) {
  revEdges->insertEdge(&end, &begin, edkFinallyClauseSyntax_Block);
}

void VisitorReverseEdges::visitFromClauseSyntax_Expression(const structure::FromClauseSyntax& begin, const expression::ExpressionSyntax& end) {
  revEdges->insertEdge(&end, &begin, edkFromClauseSyntax_Expression);
}

void VisitorReverseEdges::visitFromClauseSyntax_Type(const structure::FromClauseSyntax& begin, const expression::TypeSyntax& end) {
  revEdges->insertEdge(&end, &begin, edkFromClauseSyntax_Type);
}

void VisitorReverseEdges::visitGlobalStatementSyntax_Statement(const structure::GlobalStatementSyntax& begin, const statement::StatementSyntax& end) {
  revEdges->insertEdge(&end, &begin, edkGlobalStatementSyntax_Statement);
}

void VisitorReverseEdges::visitGroupClauseSyntax_ByExpression(const structure::GroupClauseSyntax& begin, const expression::ExpressionSyntax& end) {
  revEdges->insertEdge(&end, &begin, edkGroupClauseSyntax_ByExpression);
}

void VisitorReverseEdges::visitGroupClauseSyntax_GroupExpression(const structure::GroupClauseSyntax& begin, const expression::ExpressionSyntax& end) {
  revEdges->insertEdge(&end, &begin, edkGroupClauseSyntax_GroupExpression);
}

void VisitorReverseEdges::visitIncompleteMemberSyntax_AttributeLists(const structure::IncompleteMemberSyntax& begin, const structure::AttributeListSyntax& end) {
  revEdges->insertEdge(&end, &begin, edkIncompleteMemberSyntax_AttributeLists);
}

void VisitorReverseEdges::visitIncompleteMemberSyntax_Type(const structure::IncompleteMemberSyntax& begin, const expression::TypeSyntax& end) {
  revEdges->insertEdge(&end, &begin, edkIncompleteMemberSyntax_Type);
}

void VisitorReverseEdges::visitIndexerDeclarationSyntax_ExpressionBody(const structure::IndexerDeclarationSyntax& begin, const structure::ArrowExpressionClauseSyntax& end) {
  revEdges->insertEdge(&end, &begin, edkIndexerDeclarationSyntax_ExpressionBody);
}

void VisitorReverseEdges::visitIndexerDeclarationSyntax_ParameterList(const structure::IndexerDeclarationSyntax& begin, const structure::BracketedParameterListSyntax& end) {
  revEdges->insertEdge(&end, &begin, edkIndexerDeclarationSyntax_ParameterList);
}

void VisitorReverseEdges::visitIndexerMemberCrefSyntax_Parameters(const structure::IndexerMemberCrefSyntax& begin, const structure::CrefBracketedParameterListSyntax& end) {
  revEdges->insertEdge(&end, &begin, edkIndexerMemberCrefSyntax_Parameters);
}

void VisitorReverseEdges::visitInterpolationAlignmentClauseSyntax_Value(const structure::InterpolationAlignmentClauseSyntax& begin, const expression::ExpressionSyntax& end) {
  revEdges->insertEdge(&end, &begin, edkInterpolationAlignmentClauseSyntax_Value);
}

void VisitorReverseEdges::visitInterpolationSyntax_AlignmentClause(const structure::InterpolationSyntax& begin, const structure::InterpolationAlignmentClauseSyntax& end) {
  revEdges->insertEdge(&end, &begin, edkInterpolationSyntax_AlignmentClause);
}

void VisitorReverseEdges::visitInterpolationSyntax_Expression(const structure::InterpolationSyntax& begin, const expression::ExpressionSyntax& end) {
  revEdges->insertEdge(&end, &begin, edkInterpolationSyntax_Expression);
}

void VisitorReverseEdges::visitInterpolationSyntax_FormatClause(const structure::InterpolationSyntax& begin, const structure::InterpolationFormatClauseSyntax& end) {
  revEdges->insertEdge(&end, &begin, edkInterpolationSyntax_FormatClause);
}

void VisitorReverseEdges::visitJoinClauseSyntax_InExpression(const structure::JoinClauseSyntax& begin, const expression::ExpressionSyntax& end) {
  revEdges->insertEdge(&end, &begin, edkJoinClauseSyntax_InExpression);
}

void VisitorReverseEdges::visitJoinClauseSyntax_Into(const structure::JoinClauseSyntax& begin, const structure::JoinIntoClauseSyntax& end) {
  revEdges->insertEdge(&end, &begin, edkJoinClauseSyntax_Into);
}

void VisitorReverseEdges::visitJoinClauseSyntax_LeftExpression(const structure::JoinClauseSyntax& begin, const expression::ExpressionSyntax& end) {
  revEdges->insertEdge(&end, &begin, edkJoinClauseSyntax_LeftExpression);
}

void VisitorReverseEdges::visitJoinClauseSyntax_RightExpression(const structure::JoinClauseSyntax& begin, const expression::ExpressionSyntax& end) {
  revEdges->insertEdge(&end, &begin, edkJoinClauseSyntax_RightExpression);
}

void VisitorReverseEdges::visitJoinClauseSyntax_Type(const structure::JoinClauseSyntax& begin, const expression::TypeSyntax& end) {
  revEdges->insertEdge(&end, &begin, edkJoinClauseSyntax_Type);
}

void VisitorReverseEdges::visitLetClauseSyntax_Expression(const structure::LetClauseSyntax& begin, const expression::ExpressionSyntax& end) {
  revEdges->insertEdge(&end, &begin, edkLetClauseSyntax_Expression);
}

void VisitorReverseEdges::visitMethodDeclarationSyntax_ConstraintClauses(const structure::MethodDeclarationSyntax& begin, const structure::TypeParameterConstraintClauseSyntax& end) {
  revEdges->insertEdge(&end, &begin, edkMethodDeclarationSyntax_ConstraintClauses);
}

void VisitorReverseEdges::visitMethodDeclarationSyntax_ExplicitInterfaceSpecifier(const structure::MethodDeclarationSyntax& begin, const structure::ExplicitInterfaceSpecifierSyntax& end) {
  revEdges->insertEdge(&end, &begin, edkMethodDeclarationSyntax_ExplicitInterfaceSpecifier);
}

void VisitorReverseEdges::visitMethodDeclarationSyntax_ReturnType(const structure::MethodDeclarationSyntax& begin, const expression::TypeSyntax& end) {
  revEdges->insertEdge(&end, &begin, edkMethodDeclarationSyntax_ReturnType);
}

void VisitorReverseEdges::visitNameColonSyntax_Name(const structure::NameColonSyntax& begin, const expression::IdentifierNameSyntax& end) {
  revEdges->insertEdge(&end, &begin, edkNameColonSyntax_Name);
}

void VisitorReverseEdges::visitNameEqualsSyntax_Name(const structure::NameEqualsSyntax& begin, const expression::IdentifierNameSyntax& end) {
  revEdges->insertEdge(&end, &begin, edkNameEqualsSyntax_Name);
}

void VisitorReverseEdges::visitNameMemberCrefSyntax_Name(const structure::NameMemberCrefSyntax& begin, const expression::TypeSyntax& end) {
  revEdges->insertEdge(&end, &begin, edkNameMemberCrefSyntax_Name);
}

void VisitorReverseEdges::visitNameMemberCrefSyntax_Parameters(const structure::NameMemberCrefSyntax& begin, const structure::CrefParameterListSyntax& end) {
  revEdges->insertEdge(&end, &begin, edkNameMemberCrefSyntax_Parameters);
}

void VisitorReverseEdges::visitNamespaceDeclarationSyntax_Externs(const structure::NamespaceDeclarationSyntax& begin, const structure::ExternAliasDirectiveSyntax& end) {
  revEdges->insertEdge(&end, &begin, edkNamespaceDeclarationSyntax_Externs);
}

void VisitorReverseEdges::visitNamespaceDeclarationSyntax_Members(const structure::NamespaceDeclarationSyntax& begin, const structure::MemberDeclarationSyntax& end) {
  revEdges->insertEdge(&end, &begin, edkNamespaceDeclarationSyntax_Members);
}

void VisitorReverseEdges::visitNamespaceDeclarationSyntax_Name(const structure::NamespaceDeclarationSyntax& begin, const expression::NameSyntax& end) {
  revEdges->insertEdge(&end, &begin, edkNamespaceDeclarationSyntax_Name);
}

void VisitorReverseEdges::visitNamespaceDeclarationSyntax_Usings(const structure::NamespaceDeclarationSyntax& begin, const structure::UsingDirectiveSyntax& end) {
  revEdges->insertEdge(&end, &begin, edkNamespaceDeclarationSyntax_Usings);
}

void VisitorReverseEdges::visitOperatorDeclarationSyntax_ReturnType(const structure::OperatorDeclarationSyntax& begin, const expression::TypeSyntax& end) {
  revEdges->insertEdge(&end, &begin, edkOperatorDeclarationSyntax_ReturnType);
}

void VisitorReverseEdges::visitOperatorMemberCrefSyntax_Parameters(const structure::OperatorMemberCrefSyntax& begin, const structure::CrefParameterListSyntax& end) {
  revEdges->insertEdge(&end, &begin, edkOperatorMemberCrefSyntax_Parameters);
}

void VisitorReverseEdges::visitOrderByClauseSyntax_Orderings(const structure::OrderByClauseSyntax& begin, const structure::OrderingSyntax& end) {
  revEdges->insertEdge(&end, &begin, edkOrderByClauseSyntax_Orderings);
}

void VisitorReverseEdges::visitOrderingSyntax_Expression(const structure::OrderingSyntax& begin, const expression::ExpressionSyntax& end) {
  revEdges->insertEdge(&end, &begin, edkOrderingSyntax_Expression);
}

void VisitorReverseEdges::visitParameterSyntax_AttributeLists(const structure::ParameterSyntax& begin, const structure::AttributeListSyntax& end) {
  revEdges->insertEdge(&end, &begin, edkParameterSyntax_AttributeLists);
}

void VisitorReverseEdges::visitParameterSyntax_Default(const structure::ParameterSyntax& begin, const structure::EqualsValueClauseSyntax& end) {
  revEdges->insertEdge(&end, &begin, edkParameterSyntax_Default);
}

void VisitorReverseEdges::visitParameterSyntax_Type(const structure::ParameterSyntax& begin, const expression::TypeSyntax& end) {
  revEdges->insertEdge(&end, &begin, edkParameterSyntax_Type);
}

void VisitorReverseEdges::visitParenthesizedVariableDesignationSyntax_Variables(const structure::ParenthesizedVariableDesignationSyntax& begin, const structure::VariableDesignationSyntax& end) {
  revEdges->insertEdge(&end, &begin, edkParenthesizedVariableDesignationSyntax_Variables);
}

void VisitorReverseEdges::visitPositionalPatternClauseSyntax_Subpatterns(const structure::PositionalPatternClauseSyntax& begin, const structure::SubpatternSyntax& end) {
  revEdges->insertEdge(&end, &begin, edkPositionalPatternClauseSyntax_Subpatterns);
}

void VisitorReverseEdges::visitPropertyDeclarationSyntax_ExpressionBody(const structure::PropertyDeclarationSyntax& begin, const structure::ArrowExpressionClauseSyntax& end) {
  revEdges->insertEdge(&end, &begin, edkPropertyDeclarationSyntax_ExpressionBody);
}

void VisitorReverseEdges::visitPropertyDeclarationSyntax_Initializer(const structure::PropertyDeclarationSyntax& begin, const structure::EqualsValueClauseSyntax& end) {
  revEdges->insertEdge(&end, &begin, edkPropertyDeclarationSyntax_Initializer);
}

void VisitorReverseEdges::visitPropertyPatternClauseSyntax_Subpatterns(const structure::PropertyPatternClauseSyntax& begin, const structure::SubpatternSyntax& end) {
  revEdges->insertEdge(&end, &begin, edkPropertyPatternClauseSyntax_Subpatterns);
}

void VisitorReverseEdges::visitQualifiedCrefSyntax_Container(const structure::QualifiedCrefSyntax& begin, const expression::TypeSyntax& end) {
  revEdges->insertEdge(&end, &begin, edkQualifiedCrefSyntax_Container);
}

void VisitorReverseEdges::visitQualifiedCrefSyntax_Member(const structure::QualifiedCrefSyntax& begin, const structure::MemberCrefSyntax& end) {
  revEdges->insertEdge(&end, &begin, edkQualifiedCrefSyntax_Member);
}

void VisitorReverseEdges::visitQueryBodySyntax_Clauses(const structure::QueryBodySyntax& begin, const structure::QueryClauseSyntax& end) {
  revEdges->insertEdge(&end, &begin, edkQueryBodySyntax_Clauses);
}

void VisitorReverseEdges::visitQueryBodySyntax_Continuation(const structure::QueryBodySyntax& begin, const structure::QueryContinuationSyntax& end) {
  revEdges->insertEdge(&end, &begin, edkQueryBodySyntax_Continuation);
}

void VisitorReverseEdges::visitQueryBodySyntax_SelectOrGroup(const structure::QueryBodySyntax& begin, const structure::SelectOrGroupClauseSyntax& end) {
  revEdges->insertEdge(&end, &begin, edkQueryBodySyntax_SelectOrGroup);
}

void VisitorReverseEdges::visitQueryContinuationSyntax_Body(const structure::QueryContinuationSyntax& begin, const structure::QueryBodySyntax& end) {
  revEdges->insertEdge(&end, &begin, edkQueryContinuationSyntax_Body);
}

void VisitorReverseEdges::visitRecursivePatternSyntax_Designation(const structure::RecursivePatternSyntax& begin, const structure::VariableDesignationSyntax& end) {
  revEdges->insertEdge(&end, &begin, edkRecursivePatternSyntax_Designation);
}

void VisitorReverseEdges::visitRecursivePatternSyntax_PositionalPatternClause(const structure::RecursivePatternSyntax& begin, const structure::PositionalPatternClauseSyntax& end) {
  revEdges->insertEdge(&end, &begin, edkRecursivePatternSyntax_PositionalPatternClause);
}

void VisitorReverseEdges::visitRecursivePatternSyntax_PropertyPatternClause(const structure::RecursivePatternSyntax& begin, const structure::PropertyPatternClauseSyntax& end) {
  revEdges->insertEdge(&end, &begin, edkRecursivePatternSyntax_PropertyPatternClause);
}

void VisitorReverseEdges::visitRecursivePatternSyntax_Type(const structure::RecursivePatternSyntax& begin, const expression::TypeSyntax& end) {
  revEdges->insertEdge(&end, &begin, edkRecursivePatternSyntax_Type);
}

void VisitorReverseEdges::visitSelectClauseSyntax_Expression(const structure::SelectClauseSyntax& begin, const expression::ExpressionSyntax& end) {
  revEdges->insertEdge(&end, &begin, edkSelectClauseSyntax_Expression);
}

void VisitorReverseEdges::visitSubpatternSyntax_Pattern(const structure::SubpatternSyntax& begin, const structure::PatternSyntax& end) {
  revEdges->insertEdge(&end, &begin, edkSubpatternSyntax_Pattern);
}

void VisitorReverseEdges::visitSwitchExpressionArmSyntax_Expression(const structure::SwitchExpressionArmSyntax& begin, const expression::ExpressionSyntax& end) {
  revEdges->insertEdge(&end, &begin, edkSwitchExpressionArmSyntax_Expression);
}

void VisitorReverseEdges::visitSwitchExpressionArmSyntax_Pattern(const structure::SwitchExpressionArmSyntax& begin, const structure::PatternSyntax& end) {
  revEdges->insertEdge(&end, &begin, edkSwitchExpressionArmSyntax_Pattern);
}

void VisitorReverseEdges::visitSwitchExpressionArmSyntax_WhenClause(const structure::SwitchExpressionArmSyntax& begin, const structure::WhenClauseSyntax& end) {
  revEdges->insertEdge(&end, &begin, edkSwitchExpressionArmSyntax_WhenClause);
}

void VisitorReverseEdges::visitSwitchSectionSyntax_Labels(const structure::SwitchSectionSyntax& begin, const structure::SwitchLabelSyntax& end) {
  revEdges->insertEdge(&end, &begin, edkSwitchSectionSyntax_Labels);
}

void VisitorReverseEdges::visitSwitchSectionSyntax_Statements(const structure::SwitchSectionSyntax& begin, const statement::StatementSyntax& end) {
  revEdges->insertEdge(&end, &begin, edkSwitchSectionSyntax_Statements);
}

void VisitorReverseEdges::visitTupleElementSyntax_Type(const structure::TupleElementSyntax& begin, const expression::TypeSyntax& end) {
  revEdges->insertEdge(&end, &begin, edkTupleElementSyntax_Type);
}

void VisitorReverseEdges::visitTypeArgumentListSyntax_Arguments(const structure::TypeArgumentListSyntax& begin, const expression::TypeSyntax& end) {
  revEdges->insertEdge(&end, &begin, edkTypeArgumentListSyntax_Arguments);
}

void VisitorReverseEdges::visitTypeConstraintSyntax_Type(const structure::TypeConstraintSyntax& begin, const expression::TypeSyntax& end) {
  revEdges->insertEdge(&end, &begin, edkTypeConstraintSyntax_Type);
}

void VisitorReverseEdges::visitTypeCrefSyntax_Type(const structure::TypeCrefSyntax& begin, const expression::TypeSyntax& end) {
  revEdges->insertEdge(&end, &begin, edkTypeCrefSyntax_Type);
}

void VisitorReverseEdges::visitTypeDeclarationSyntax_ConstraintClauses(const structure::TypeDeclarationSyntax& begin, const structure::TypeParameterConstraintClauseSyntax& end) {
  revEdges->insertEdge(&end, &begin, edkTypeDeclarationSyntax_ConstraintClauses);
}

void VisitorReverseEdges::visitTypeDeclarationSyntax_Members(const structure::TypeDeclarationSyntax& begin, const structure::MemberDeclarationSyntax& end) {
  revEdges->insertEdge(&end, &begin, edkTypeDeclarationSyntax_Members);
}

void VisitorReverseEdges::visitTypeDeclarationSyntax_TypeParameterList(const structure::TypeDeclarationSyntax& begin, const structure::TypeParameterListSyntax& end) {
  revEdges->insertEdge(&end, &begin, edkTypeDeclarationSyntax_TypeParameterList);
}

void VisitorReverseEdges::visitTypeParameterConstraintClauseSyntax_Constraints(const structure::TypeParameterConstraintClauseSyntax& begin, const structure::TypeParameterConstraintSyntax& end) {
  revEdges->insertEdge(&end, &begin, edkTypeParameterConstraintClauseSyntax_Constraints);
}

void VisitorReverseEdges::visitTypeParameterConstraintClauseSyntax_Name(const structure::TypeParameterConstraintClauseSyntax& begin, const expression::IdentifierNameSyntax& end) {
  revEdges->insertEdge(&end, &begin, edkTypeParameterConstraintClauseSyntax_Name);
}

void VisitorReverseEdges::visitTypeParameterListSyntax_Parameters(const structure::TypeParameterListSyntax& begin, const structure::TypeParameterSyntax& end) {
  revEdges->insertEdge(&end, &begin, edkTypeParameterListSyntax_Parameters);
}

void VisitorReverseEdges::visitTypeParameterSyntax_AttributeLists(const structure::TypeParameterSyntax& begin, const structure::AttributeListSyntax& end) {
  revEdges->insertEdge(&end, &begin, edkTypeParameterSyntax_AttributeLists);
}

void VisitorReverseEdges::visitUsingDirectiveSyntax_Alias(const structure::UsingDirectiveSyntax& begin, const structure::NameEqualsSyntax& end) {
  revEdges->insertEdge(&end, &begin, edkUsingDirectiveSyntax_Alias);
}

void VisitorReverseEdges::visitUsingDirectiveSyntax_Name(const structure::UsingDirectiveSyntax& begin, const expression::NameSyntax& end) {
  revEdges->insertEdge(&end, &begin, edkUsingDirectiveSyntax_Name);
}

void VisitorReverseEdges::visitVarPatternSyntax_Designation(const structure::VarPatternSyntax& begin, const structure::VariableDesignationSyntax& end) {
  revEdges->insertEdge(&end, &begin, edkVarPatternSyntax_Designation);
}

void VisitorReverseEdges::visitVariableDeclarationSyntax_Type(const structure::VariableDeclarationSyntax& begin, const expression::TypeSyntax& end) {
  revEdges->insertEdge(&end, &begin, edkVariableDeclarationSyntax_Type);
}

void VisitorReverseEdges::visitVariableDeclarationSyntax_Variables(const structure::VariableDeclarationSyntax& begin, const structure::VariableDeclaratorSyntax& end) {
  revEdges->insertEdge(&end, &begin, edkVariableDeclarationSyntax_Variables);
}

void VisitorReverseEdges::visitVariableDeclaratorSyntax_ArgumentList(const structure::VariableDeclaratorSyntax& begin, const structure::BracketedArgumentListSyntax& end) {
  revEdges->insertEdge(&end, &begin, edkVariableDeclaratorSyntax_ArgumentList);
}

void VisitorReverseEdges::visitVariableDeclaratorSyntax_Initializer(const structure::VariableDeclaratorSyntax& begin, const structure::EqualsValueClauseSyntax& end) {
  revEdges->insertEdge(&end, &begin, edkVariableDeclaratorSyntax_Initializer);
}

void VisitorReverseEdges::visitWhenClauseSyntax_Condition(const structure::WhenClauseSyntax& begin, const expression::ExpressionSyntax& end) {
  revEdges->insertEdge(&end, &begin, edkWhenClauseSyntax_Condition);
}

void VisitorReverseEdges::visitWhereClauseSyntax_Condition(const structure::WhereClauseSyntax& begin, const expression::ExpressionSyntax& end) {
  revEdges->insertEdge(&end, &begin, edkWhereClauseSyntax_Condition);
}

void VisitorReverseEdges::visitXmlAttributeSyntax_Name(const structure::XmlAttributeSyntax& begin, const structure::XmlNameSyntax& end) {
  revEdges->insertEdge(&end, &begin, edkXmlAttributeSyntax_Name);
}

void VisitorReverseEdges::visitXmlCrefAttributeSyntax_Cref(const structure::XmlCrefAttributeSyntax& begin, const structure::CrefSyntax& end) {
  revEdges->insertEdge(&end, &begin, edkXmlCrefAttributeSyntax_Cref);
}

void VisitorReverseEdges::visitXmlElementEndTagSyntax_Name(const structure::XmlElementEndTagSyntax& begin, const structure::XmlNameSyntax& end) {
  revEdges->insertEdge(&end, &begin, edkXmlElementEndTagSyntax_Name);
}

void VisitorReverseEdges::visitXmlElementStartTagSyntax_Attributes(const structure::XmlElementStartTagSyntax& begin, const structure::XmlAttributeSyntax& end) {
  revEdges->insertEdge(&end, &begin, edkXmlElementStartTagSyntax_Attributes);
}

void VisitorReverseEdges::visitXmlElementStartTagSyntax_Name(const structure::XmlElementStartTagSyntax& begin, const structure::XmlNameSyntax& end) {
  revEdges->insertEdge(&end, &begin, edkXmlElementStartTagSyntax_Name);
}

void VisitorReverseEdges::visitXmlElementSyntax_Content(const structure::XmlElementSyntax& begin, const structure::XmlNodeSyntax& end) {
  revEdges->insertEdge(&end, &begin, edkXmlElementSyntax_Content);
}

void VisitorReverseEdges::visitXmlElementSyntax_EndTag(const structure::XmlElementSyntax& begin, const structure::XmlElementEndTagSyntax& end) {
  revEdges->insertEdge(&end, &begin, edkXmlElementSyntax_EndTag);
}

void VisitorReverseEdges::visitXmlElementSyntax_StartTag(const structure::XmlElementSyntax& begin, const structure::XmlElementStartTagSyntax& end) {
  revEdges->insertEdge(&end, &begin, edkXmlElementSyntax_StartTag);
}

void VisitorReverseEdges::visitXmlEmptyElementSyntax_Attributes(const structure::XmlEmptyElementSyntax& begin, const structure::XmlAttributeSyntax& end) {
  revEdges->insertEdge(&end, &begin, edkXmlEmptyElementSyntax_Attributes);
}

void VisitorReverseEdges::visitXmlEmptyElementSyntax_Name(const structure::XmlEmptyElementSyntax& begin, const structure::XmlNameSyntax& end) {
  revEdges->insertEdge(&end, &begin, edkXmlEmptyElementSyntax_Name);
}

void VisitorReverseEdges::visitXmlNameAttributeSyntax_Identifier(const structure::XmlNameAttributeSyntax& begin, const expression::IdentifierNameSyntax& end) {
  revEdges->insertEdge(&end, &begin, edkXmlNameAttributeSyntax_Identifier);
}

void VisitorReverseEdges::visitXmlNameSyntax_Prefix(const structure::XmlNameSyntax& begin, const structure::XmlPrefixSyntax& end) {
  revEdges->insertEdge(&end, &begin, edkXmlNameSyntax_Prefix);
}

void VisitorReverseEdges::visitXmlProcessingInstructionSyntax_Name(const structure::XmlProcessingInstructionSyntax& begin, const structure::XmlNameSyntax& end) {
  revEdges->insertEdge(&end, &begin, edkXmlProcessingInstructionSyntax_Name);
}


}}}
