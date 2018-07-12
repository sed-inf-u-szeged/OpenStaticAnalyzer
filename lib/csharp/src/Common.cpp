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
#include "csharp/inc/messages.h"
#include <sstream>

namespace columbus { namespace csharp { namespace asg {
namespace Common {

bool getIsPositioned(const base::Base& node) {
  NodeKind ndk = node.getNodeKind();
  return
    ndk == ndkPositioned ||
    ndk == ndkAnonymousMethodExpressionSyntax ||
    ndk == ndkParenthesizedLambdaExpressionSyntax ||
    ndk == ndkSimpleLambdaExpressionSyntax ||
    ndk == ndkAnonymousObjectCreationExpressionSyntax ||
    ndk == ndkArrayCreationExpressionSyntax ||
    ndk == ndkAssignmentExpressionSyntax ||
    ndk == ndkAwaitExpressionSyntax ||
    ndk == ndkBinaryExpressionSyntax ||
    ndk == ndkCastExpressionSyntax ||
    ndk == ndkCheckedExpressionSyntax ||
    ndk == ndkConditionalAccessExpressionSyntax ||
    ndk == ndkConditionalExpressionSyntax ||
    ndk == ndkDefaultExpressionSyntax ||
    ndk == ndkElementAccessExpressionSyntax ||
    ndk == ndkElementBindingExpressionSyntax ||
    ndk == ndkImplicitArrayCreationExpressionSyntax ||
    ndk == ndkImplicitElementAccessSyntax ||
    ndk == ndkInitializerExpressionSyntax ||
    ndk == ndkBaseExpressionSyntax ||
    ndk == ndkThisExpressionSyntax ||
    ndk == ndkInterpolatedStringExpressionSyntax ||
    ndk == ndkInvocationExpressionSyntax ||
    ndk == ndkLiteralExpressionSyntax ||
    ndk == ndkMakeRefExpressionSyntax ||
    ndk == ndkMemberAccessExpressionSyntax ||
    ndk == ndkMemberBindingExpressionSyntax ||
    ndk == ndkObjectCreationExpressionSyntax ||
    ndk == ndkOmittedArraySizeExpressionSyntax ||
    ndk == ndkParenthesizedExpressionSyntax ||
    ndk == ndkPostfixUnaryExpressionSyntax ||
    ndk == ndkPrefixUnaryExpressionSyntax ||
    ndk == ndkQueryExpressionSyntax ||
    ndk == ndkRefTypeExpressionSyntax ||
    ndk == ndkRefValueExpressionSyntax ||
    ndk == ndkSizeOfExpressionSyntax ||
    ndk == ndkStackAllocArrayCreationExpressionSyntax ||
    ndk == ndkTypeOfExpressionSyntax ||
    ndk == ndkArrayTypeSyntax ||
    ndk == ndkAliasQualifiedNameSyntax ||
    ndk == ndkQualifiedNameSyntax ||
    ndk == ndkGenericNameSyntax ||
    ndk == ndkIdentifierNameSyntax ||
    ndk == ndkNullableTypeSyntax ||
    ndk == ndkOmittedTypeArgumentSyntax ||
    ndk == ndkPointerTypeSyntax ||
    ndk == ndkPredefinedTypeSyntax ||
    ndk == ndkBlockSyntax ||
    ndk == ndkBreakStatementSyntax ||
    ndk == ndkCheckedStatementSyntax ||
    ndk == ndkContinueStatementSyntax ||
    ndk == ndkDoStatementSyntax ||
    ndk == ndkEmptyStatementSyntax ||
    ndk == ndkExpressionStatementSyntax ||
    ndk == ndkFixedStatementSyntax ||
    ndk == ndkForEachStatementSyntax ||
    ndk == ndkForStatementSyntax ||
    ndk == ndkGotoStatementSyntax ||
    ndk == ndkIfStatementSyntax ||
    ndk == ndkLabeledStatementSyntax ||
    ndk == ndkLocalDeclarationStatementSyntax ||
    ndk == ndkLockStatementSyntax ||
    ndk == ndkReturnStatementSyntax ||
    ndk == ndkSwitchStatementSyntax ||
    ndk == ndkThrowStatementSyntax ||
    ndk == ndkTryStatementSyntax ||
    ndk == ndkUnsafeStatementSyntax ||
    ndk == ndkUsingStatementSyntax ||
    ndk == ndkWhileStatementSyntax ||
    ndk == ndkYieldStatementSyntax ||
    ndk == ndkAccessorDeclarationSyntax ||
    ndk == ndkAccessorListSyntax ||
    ndk == ndkAnonymousObjectMemberDeclaratorSyntax ||
    ndk == ndkArgumentSyntax ||
    ndk == ndkArrayRankSpecifierSyntax ||
    ndk == ndkArrowExpressionClauseSyntax ||
    ndk == ndkAttributeArgumentListSyntax ||
    ndk == ndkAttributeArgumentSyntax ||
    ndk == ndkAttributeListSyntax ||
    ndk == ndkAttributeSyntax ||
    ndk == ndkAttributeTargetSpecifierSyntax ||
    ndk == ndkArgumentListSyntax ||
    ndk == ndkBracketedArgumentListSyntax ||
    ndk == ndkCrefBracketedParameterListSyntax ||
    ndk == ndkCrefParameterListSyntax ||
    ndk == ndkBaseListSyntax ||
    ndk == ndkBracketedParameterListSyntax ||
    ndk == ndkParameterListSyntax ||
    ndk == ndkSimpleBaseTypeSyntax ||
    ndk == ndkCatchClauseSyntax ||
    ndk == ndkCatchDeclarationSyntax ||
    ndk == ndkCatchFilterClauseSyntax ||
    ndk == ndkCompilationUnitSyntax ||
    ndk == ndkConstructorInitializerSyntax ||
    ndk == ndkCrefParameterSyntax ||
    ndk == ndkConversionOperatorMemberCrefSyntax ||
    ndk == ndkIndexerMemberCrefSyntax ||
    ndk == ndkNameMemberCrefSyntax ||
    ndk == ndkOperatorMemberCrefSyntax ||
    ndk == ndkQualifiedCrefSyntax ||
    ndk == ndkTypeCrefSyntax ||
    ndk == ndkElseClauseSyntax ||
    ndk == ndkEqualsValueClauseSyntax ||
    ndk == ndkExplicitInterfaceSpecifierSyntax ||
    ndk == ndkExternAliasDirectiveSyntax ||
    ndk == ndkFinallyClauseSyntax ||
    ndk == ndkInterpolatedStringTextSyntax ||
    ndk == ndkInterpolationSyntax ||
    ndk == ndkInterpolationAlignmentClauseSyntax ||
    ndk == ndkInterpolationFormatClauseSyntax ||
    ndk == ndkJoinIntoClauseSyntax ||
    ndk == ndkEventFieldDeclarationSyntax ||
    ndk == ndkFieldDeclarationSyntax ||
    ndk == ndkConstructorDeclarationSyntax ||
    ndk == ndkConversionOperatorDeclarationSyntax ||
    ndk == ndkDestructorDeclarationSyntax ||
    ndk == ndkMethodDeclarationSyntax ||
    ndk == ndkOperatorDeclarationSyntax ||
    ndk == ndkEventDeclarationSyntax ||
    ndk == ndkIndexerDeclarationSyntax ||
    ndk == ndkPropertyDeclarationSyntax ||
    ndk == ndkEnumDeclarationSyntax ||
    ndk == ndkClassDeclarationSyntax ||
    ndk == ndkInterfaceDeclarationSyntax ||
    ndk == ndkStructDeclarationSyntax ||
    ndk == ndkDelegateDeclarationSyntax ||
    ndk == ndkEnumMemberDeclarationSyntax ||
    ndk == ndkGlobalStatementSyntax ||
    ndk == ndkIncompleteMemberSyntax ||
    ndk == ndkNamespaceDeclarationSyntax ||
    ndk == ndkNameColonSyntax ||
    ndk == ndkNameEqualsSyntax ||
    ndk == ndkOrderingSyntax ||
    ndk == ndkParameterSyntax ||
    ndk == ndkQueryBodySyntax ||
    ndk == ndkFromClauseSyntax ||
    ndk == ndkJoinClauseSyntax ||
    ndk == ndkLetClauseSyntax ||
    ndk == ndkOrderByClauseSyntax ||
    ndk == ndkWhereClauseSyntax ||
    ndk == ndkQueryContinuationSyntax ||
    ndk == ndkGroupClauseSyntax ||
    ndk == ndkSelectClauseSyntax ||
    ndk == ndkCaseSwitchLabelSyntax ||
    ndk == ndkDefaultSwitchLabelSyntax ||
    ndk == ndkSwitchSectionSyntax ||
    ndk == ndkSyntaxToken ||
    ndk == ndkTypeArgumentListSyntax ||
    ndk == ndkTypeParameterConstraintClauseSyntax ||
    ndk == ndkClassOrStructConstraintSyntax ||
    ndk == ndkConstructorConstraintSyntax ||
    ndk == ndkTypeConstraintSyntax ||
    ndk == ndkTypeParameterListSyntax ||
    ndk == ndkTypeParameterSyntax ||
    ndk == ndkUsingDirectiveSyntax ||
    ndk == ndkVariableDeclarationSyntax ||
    ndk == ndkVariableDeclaratorSyntax ||
    ndk == ndkXmlCrefAttributeSyntax ||
    ndk == ndkXmlNameAttributeSyntax ||
    ndk == ndkXmlTextAttributeSyntax ||
    ndk == ndkXmlElementEndTagSyntax ||
    ndk == ndkXmlElementStartTagSyntax ||
    ndk == ndkXmlNameSyntax ||
    ndk == ndkXmlCDataSectionSyntax ||
    ndk == ndkXmlCommentSyntax ||
    ndk == ndkXmlElementSyntax ||
    ndk == ndkXmlEmptyElementSyntax ||
    ndk == ndkXmlProcessingInstructionSyntax ||
    ndk == ndkXmlTextSyntax ||
    ndk == ndkXmlPrefixSyntax;
}

bool getIsAliasQualifiedNameSyntax(const base::Base& node) {
  NodeKind ndk = node.getNodeKind();
  return
    ndk == ndkAliasQualifiedNameSyntax;
}

bool getIsAnonymousFunctionExpressionSyntax(const base::Base& node) {
  NodeKind ndk = node.getNodeKind();
  return
    ndk == ndkAnonymousFunctionExpressionSyntax ||
    ndk == ndkAnonymousMethodExpressionSyntax ||
    ndk == ndkParenthesizedLambdaExpressionSyntax ||
    ndk == ndkSimpleLambdaExpressionSyntax;
}

bool getIsAnonymousMethodExpressionSyntax(const base::Base& node) {
  NodeKind ndk = node.getNodeKind();
  return
    ndk == ndkAnonymousMethodExpressionSyntax;
}

bool getIsAnonymousObjectCreationExpressionSyntax(const base::Base& node) {
  NodeKind ndk = node.getNodeKind();
  return
    ndk == ndkAnonymousObjectCreationExpressionSyntax;
}

bool getIsArrayCreationExpressionSyntax(const base::Base& node) {
  NodeKind ndk = node.getNodeKind();
  return
    ndk == ndkArrayCreationExpressionSyntax;
}

bool getIsArrayTypeSyntax(const base::Base& node) {
  NodeKind ndk = node.getNodeKind();
  return
    ndk == ndkArrayTypeSyntax;
}

bool getIsAssignmentExpressionSyntax(const base::Base& node) {
  NodeKind ndk = node.getNodeKind();
  return
    ndk == ndkAssignmentExpressionSyntax;
}

bool getIsAwaitExpressionSyntax(const base::Base& node) {
  NodeKind ndk = node.getNodeKind();
  return
    ndk == ndkAwaitExpressionSyntax;
}

bool getIsBaseExpressionSyntax(const base::Base& node) {
  NodeKind ndk = node.getNodeKind();
  return
    ndk == ndkBaseExpressionSyntax;
}

bool getIsBinaryExpressionSyntax(const base::Base& node) {
  NodeKind ndk = node.getNodeKind();
  return
    ndk == ndkBinaryExpressionSyntax;
}

bool getIsCastExpressionSyntax(const base::Base& node) {
  NodeKind ndk = node.getNodeKind();
  return
    ndk == ndkCastExpressionSyntax;
}

bool getIsCheckedExpressionSyntax(const base::Base& node) {
  NodeKind ndk = node.getNodeKind();
  return
    ndk == ndkCheckedExpressionSyntax;
}

bool getIsConditionalAccessExpressionSyntax(const base::Base& node) {
  NodeKind ndk = node.getNodeKind();
  return
    ndk == ndkConditionalAccessExpressionSyntax;
}

bool getIsConditionalExpressionSyntax(const base::Base& node) {
  NodeKind ndk = node.getNodeKind();
  return
    ndk == ndkConditionalExpressionSyntax;
}

bool getIsDefaultExpressionSyntax(const base::Base& node) {
  NodeKind ndk = node.getNodeKind();
  return
    ndk == ndkDefaultExpressionSyntax;
}

bool getIsElementAccessExpressionSyntax(const base::Base& node) {
  NodeKind ndk = node.getNodeKind();
  return
    ndk == ndkElementAccessExpressionSyntax;
}

bool getIsElementBindingExpressionSyntax(const base::Base& node) {
  NodeKind ndk = node.getNodeKind();
  return
    ndk == ndkElementBindingExpressionSyntax;
}

bool getIsExpressionSyntax(const base::Base& node) {
  NodeKind ndk = node.getNodeKind();
  return
    ndk == ndkExpressionSyntax ||
    ndk == ndkAnonymousMethodExpressionSyntax ||
    ndk == ndkParenthesizedLambdaExpressionSyntax ||
    ndk == ndkSimpleLambdaExpressionSyntax ||
    ndk == ndkAnonymousObjectCreationExpressionSyntax ||
    ndk == ndkArrayCreationExpressionSyntax ||
    ndk == ndkAssignmentExpressionSyntax ||
    ndk == ndkAwaitExpressionSyntax ||
    ndk == ndkBinaryExpressionSyntax ||
    ndk == ndkCastExpressionSyntax ||
    ndk == ndkCheckedExpressionSyntax ||
    ndk == ndkConditionalAccessExpressionSyntax ||
    ndk == ndkConditionalExpressionSyntax ||
    ndk == ndkDefaultExpressionSyntax ||
    ndk == ndkElementAccessExpressionSyntax ||
    ndk == ndkElementBindingExpressionSyntax ||
    ndk == ndkImplicitArrayCreationExpressionSyntax ||
    ndk == ndkImplicitElementAccessSyntax ||
    ndk == ndkInitializerExpressionSyntax ||
    ndk == ndkBaseExpressionSyntax ||
    ndk == ndkThisExpressionSyntax ||
    ndk == ndkInterpolatedStringExpressionSyntax ||
    ndk == ndkInvocationExpressionSyntax ||
    ndk == ndkLiteralExpressionSyntax ||
    ndk == ndkMakeRefExpressionSyntax ||
    ndk == ndkMemberAccessExpressionSyntax ||
    ndk == ndkMemberBindingExpressionSyntax ||
    ndk == ndkObjectCreationExpressionSyntax ||
    ndk == ndkOmittedArraySizeExpressionSyntax ||
    ndk == ndkParenthesizedExpressionSyntax ||
    ndk == ndkPostfixUnaryExpressionSyntax ||
    ndk == ndkPrefixUnaryExpressionSyntax ||
    ndk == ndkQueryExpressionSyntax ||
    ndk == ndkRefTypeExpressionSyntax ||
    ndk == ndkRefValueExpressionSyntax ||
    ndk == ndkSizeOfExpressionSyntax ||
    ndk == ndkStackAllocArrayCreationExpressionSyntax ||
    ndk == ndkTypeOfExpressionSyntax ||
    ndk == ndkArrayTypeSyntax ||
    ndk == ndkAliasQualifiedNameSyntax ||
    ndk == ndkQualifiedNameSyntax ||
    ndk == ndkGenericNameSyntax ||
    ndk == ndkIdentifierNameSyntax ||
    ndk == ndkNullableTypeSyntax ||
    ndk == ndkOmittedTypeArgumentSyntax ||
    ndk == ndkPointerTypeSyntax ||
    ndk == ndkPredefinedTypeSyntax;
}

bool getIsGenericNameSyntax(const base::Base& node) {
  NodeKind ndk = node.getNodeKind();
  return
    ndk == ndkGenericNameSyntax;
}

bool getIsIdentifierNameSyntax(const base::Base& node) {
  NodeKind ndk = node.getNodeKind();
  return
    ndk == ndkIdentifierNameSyntax;
}

bool getIsImplicitArrayCreationExpressionSyntax(const base::Base& node) {
  NodeKind ndk = node.getNodeKind();
  return
    ndk == ndkImplicitArrayCreationExpressionSyntax;
}

bool getIsImplicitElementAccessSyntax(const base::Base& node) {
  NodeKind ndk = node.getNodeKind();
  return
    ndk == ndkImplicitElementAccessSyntax;
}

bool getIsInitializerExpressionSyntax(const base::Base& node) {
  NodeKind ndk = node.getNodeKind();
  return
    ndk == ndkInitializerExpressionSyntax;
}

bool getIsInstanceExpressionSyntax(const base::Base& node) {
  NodeKind ndk = node.getNodeKind();
  return
    ndk == ndkInstanceExpressionSyntax ||
    ndk == ndkBaseExpressionSyntax ||
    ndk == ndkThisExpressionSyntax;
}

bool getIsInterpolatedStringExpressionSyntax(const base::Base& node) {
  NodeKind ndk = node.getNodeKind();
  return
    ndk == ndkInterpolatedStringExpressionSyntax;
}

bool getIsInvocationExpressionSyntax(const base::Base& node) {
  NodeKind ndk = node.getNodeKind();
  return
    ndk == ndkInvocationExpressionSyntax;
}

bool getIsLambdaExpressionSyntax(const base::Base& node) {
  NodeKind ndk = node.getNodeKind();
  return
    ndk == ndkLambdaExpressionSyntax ||
    ndk == ndkParenthesizedLambdaExpressionSyntax ||
    ndk == ndkSimpleLambdaExpressionSyntax;
}

bool getIsLiteralExpressionSyntax(const base::Base& node) {
  NodeKind ndk = node.getNodeKind();
  return
    ndk == ndkLiteralExpressionSyntax;
}

bool getIsMakeRefExpressionSyntax(const base::Base& node) {
  NodeKind ndk = node.getNodeKind();
  return
    ndk == ndkMakeRefExpressionSyntax;
}

bool getIsMemberAccessExpressionSyntax(const base::Base& node) {
  NodeKind ndk = node.getNodeKind();
  return
    ndk == ndkMemberAccessExpressionSyntax;
}

bool getIsMemberBindingExpressionSyntax(const base::Base& node) {
  NodeKind ndk = node.getNodeKind();
  return
    ndk == ndkMemberBindingExpressionSyntax;
}

bool getIsNameSyntax(const base::Base& node) {
  NodeKind ndk = node.getNodeKind();
  return
    ndk == ndkNameSyntax ||
    ndk == ndkAliasQualifiedNameSyntax ||
    ndk == ndkQualifiedNameSyntax ||
    ndk == ndkGenericNameSyntax ||
    ndk == ndkIdentifierNameSyntax;
}

bool getIsNullableTypeSyntax(const base::Base& node) {
  NodeKind ndk = node.getNodeKind();
  return
    ndk == ndkNullableTypeSyntax;
}

bool getIsObjectCreationExpressionSyntax(const base::Base& node) {
  NodeKind ndk = node.getNodeKind();
  return
    ndk == ndkObjectCreationExpressionSyntax;
}

bool getIsOmittedArraySizeExpressionSyntax(const base::Base& node) {
  NodeKind ndk = node.getNodeKind();
  return
    ndk == ndkOmittedArraySizeExpressionSyntax;
}

bool getIsOmittedTypeArgumentSyntax(const base::Base& node) {
  NodeKind ndk = node.getNodeKind();
  return
    ndk == ndkOmittedTypeArgumentSyntax;
}

bool getIsParenthesizedExpressionSyntax(const base::Base& node) {
  NodeKind ndk = node.getNodeKind();
  return
    ndk == ndkParenthesizedExpressionSyntax;
}

bool getIsParenthesizedLambdaExpressionSyntax(const base::Base& node) {
  NodeKind ndk = node.getNodeKind();
  return
    ndk == ndkParenthesizedLambdaExpressionSyntax;
}

bool getIsPointerTypeSyntax(const base::Base& node) {
  NodeKind ndk = node.getNodeKind();
  return
    ndk == ndkPointerTypeSyntax;
}

bool getIsPostfixUnaryExpressionSyntax(const base::Base& node) {
  NodeKind ndk = node.getNodeKind();
  return
    ndk == ndkPostfixUnaryExpressionSyntax;
}

bool getIsPredefinedTypeSyntax(const base::Base& node) {
  NodeKind ndk = node.getNodeKind();
  return
    ndk == ndkPredefinedTypeSyntax;
}

bool getIsPrefixUnaryExpressionSyntax(const base::Base& node) {
  NodeKind ndk = node.getNodeKind();
  return
    ndk == ndkPrefixUnaryExpressionSyntax;
}

bool getIsQualifiedNameSyntax(const base::Base& node) {
  NodeKind ndk = node.getNodeKind();
  return
    ndk == ndkQualifiedNameSyntax;
}

bool getIsQueryExpressionSyntax(const base::Base& node) {
  NodeKind ndk = node.getNodeKind();
  return
    ndk == ndkQueryExpressionSyntax;
}

bool getIsRefTypeExpressionSyntax(const base::Base& node) {
  NodeKind ndk = node.getNodeKind();
  return
    ndk == ndkRefTypeExpressionSyntax;
}

bool getIsRefValueExpressionSyntax(const base::Base& node) {
  NodeKind ndk = node.getNodeKind();
  return
    ndk == ndkRefValueExpressionSyntax;
}

bool getIsSimpleLambdaExpressionSyntax(const base::Base& node) {
  NodeKind ndk = node.getNodeKind();
  return
    ndk == ndkSimpleLambdaExpressionSyntax;
}

bool getIsSimpleNameSyntax(const base::Base& node) {
  NodeKind ndk = node.getNodeKind();
  return
    ndk == ndkSimpleNameSyntax ||
    ndk == ndkGenericNameSyntax ||
    ndk == ndkIdentifierNameSyntax;
}

bool getIsSizeOfExpressionSyntax(const base::Base& node) {
  NodeKind ndk = node.getNodeKind();
  return
    ndk == ndkSizeOfExpressionSyntax;
}

bool getIsStackAllocArrayCreationExpressionSyntax(const base::Base& node) {
  NodeKind ndk = node.getNodeKind();
  return
    ndk == ndkStackAllocArrayCreationExpressionSyntax;
}

bool getIsThisExpressionSyntax(const base::Base& node) {
  NodeKind ndk = node.getNodeKind();
  return
    ndk == ndkThisExpressionSyntax;
}

bool getIsTypeOfExpressionSyntax(const base::Base& node) {
  NodeKind ndk = node.getNodeKind();
  return
    ndk == ndkTypeOfExpressionSyntax;
}

bool getIsTypeSyntax(const base::Base& node) {
  NodeKind ndk = node.getNodeKind();
  return
    ndk == ndkTypeSyntax ||
    ndk == ndkArrayTypeSyntax ||
    ndk == ndkAliasQualifiedNameSyntax ||
    ndk == ndkQualifiedNameSyntax ||
    ndk == ndkGenericNameSyntax ||
    ndk == ndkIdentifierNameSyntax ||
    ndk == ndkNullableTypeSyntax ||
    ndk == ndkOmittedTypeArgumentSyntax ||
    ndk == ndkPointerTypeSyntax ||
    ndk == ndkPredefinedTypeSyntax;
}

bool getIsBlockSyntax(const base::Base& node) {
  NodeKind ndk = node.getNodeKind();
  return
    ndk == ndkBlockSyntax;
}

bool getIsBreakStatementSyntax(const base::Base& node) {
  NodeKind ndk = node.getNodeKind();
  return
    ndk == ndkBreakStatementSyntax;
}

bool getIsCheckedStatementSyntax(const base::Base& node) {
  NodeKind ndk = node.getNodeKind();
  return
    ndk == ndkCheckedStatementSyntax;
}

bool getIsContinueStatementSyntax(const base::Base& node) {
  NodeKind ndk = node.getNodeKind();
  return
    ndk == ndkContinueStatementSyntax;
}

bool getIsDoStatementSyntax(const base::Base& node) {
  NodeKind ndk = node.getNodeKind();
  return
    ndk == ndkDoStatementSyntax;
}

bool getIsEmptyStatementSyntax(const base::Base& node) {
  NodeKind ndk = node.getNodeKind();
  return
    ndk == ndkEmptyStatementSyntax;
}

bool getIsExpressionStatementSyntax(const base::Base& node) {
  NodeKind ndk = node.getNodeKind();
  return
    ndk == ndkExpressionStatementSyntax;
}

bool getIsFixedStatementSyntax(const base::Base& node) {
  NodeKind ndk = node.getNodeKind();
  return
    ndk == ndkFixedStatementSyntax;
}

bool getIsForEachStatementSyntax(const base::Base& node) {
  NodeKind ndk = node.getNodeKind();
  return
    ndk == ndkForEachStatementSyntax;
}

bool getIsForStatementSyntax(const base::Base& node) {
  NodeKind ndk = node.getNodeKind();
  return
    ndk == ndkForStatementSyntax;
}

bool getIsGotoStatementSyntax(const base::Base& node) {
  NodeKind ndk = node.getNodeKind();
  return
    ndk == ndkGotoStatementSyntax;
}

bool getIsIfStatementSyntax(const base::Base& node) {
  NodeKind ndk = node.getNodeKind();
  return
    ndk == ndkIfStatementSyntax;
}

bool getIsLabeledStatementSyntax(const base::Base& node) {
  NodeKind ndk = node.getNodeKind();
  return
    ndk == ndkLabeledStatementSyntax;
}

bool getIsLocalDeclarationStatementSyntax(const base::Base& node) {
  NodeKind ndk = node.getNodeKind();
  return
    ndk == ndkLocalDeclarationStatementSyntax;
}

bool getIsLockStatementSyntax(const base::Base& node) {
  NodeKind ndk = node.getNodeKind();
  return
    ndk == ndkLockStatementSyntax;
}

bool getIsReturnStatementSyntax(const base::Base& node) {
  NodeKind ndk = node.getNodeKind();
  return
    ndk == ndkReturnStatementSyntax;
}

bool getIsStatementSyntax(const base::Base& node) {
  NodeKind ndk = node.getNodeKind();
  return
    ndk == ndkStatementSyntax ||
    ndk == ndkBlockSyntax ||
    ndk == ndkBreakStatementSyntax ||
    ndk == ndkCheckedStatementSyntax ||
    ndk == ndkContinueStatementSyntax ||
    ndk == ndkDoStatementSyntax ||
    ndk == ndkEmptyStatementSyntax ||
    ndk == ndkExpressionStatementSyntax ||
    ndk == ndkFixedStatementSyntax ||
    ndk == ndkForEachStatementSyntax ||
    ndk == ndkForStatementSyntax ||
    ndk == ndkGotoStatementSyntax ||
    ndk == ndkIfStatementSyntax ||
    ndk == ndkLabeledStatementSyntax ||
    ndk == ndkLocalDeclarationStatementSyntax ||
    ndk == ndkLockStatementSyntax ||
    ndk == ndkReturnStatementSyntax ||
    ndk == ndkSwitchStatementSyntax ||
    ndk == ndkThrowStatementSyntax ||
    ndk == ndkTryStatementSyntax ||
    ndk == ndkUnsafeStatementSyntax ||
    ndk == ndkUsingStatementSyntax ||
    ndk == ndkWhileStatementSyntax ||
    ndk == ndkYieldStatementSyntax;
}

bool getIsSwitchStatementSyntax(const base::Base& node) {
  NodeKind ndk = node.getNodeKind();
  return
    ndk == ndkSwitchStatementSyntax;
}

bool getIsThrowStatementSyntax(const base::Base& node) {
  NodeKind ndk = node.getNodeKind();
  return
    ndk == ndkThrowStatementSyntax;
}

bool getIsTryStatementSyntax(const base::Base& node) {
  NodeKind ndk = node.getNodeKind();
  return
    ndk == ndkTryStatementSyntax;
}

bool getIsUnsafeStatementSyntax(const base::Base& node) {
  NodeKind ndk = node.getNodeKind();
  return
    ndk == ndkUnsafeStatementSyntax;
}

bool getIsUsingStatementSyntax(const base::Base& node) {
  NodeKind ndk = node.getNodeKind();
  return
    ndk == ndkUsingStatementSyntax;
}

bool getIsWhileStatementSyntax(const base::Base& node) {
  NodeKind ndk = node.getNodeKind();
  return
    ndk == ndkWhileStatementSyntax;
}

bool getIsYieldStatementSyntax(const base::Base& node) {
  NodeKind ndk = node.getNodeKind();
  return
    ndk == ndkYieldStatementSyntax;
}

bool getIsAccessorDeclarationSyntax(const base::Base& node) {
  NodeKind ndk = node.getNodeKind();
  return
    ndk == ndkAccessorDeclarationSyntax;
}

bool getIsAccessorListSyntax(const base::Base& node) {
  NodeKind ndk = node.getNodeKind();
  return
    ndk == ndkAccessorListSyntax;
}

bool getIsAnonymousObjectMemberDeclaratorSyntax(const base::Base& node) {
  NodeKind ndk = node.getNodeKind();
  return
    ndk == ndkAnonymousObjectMemberDeclaratorSyntax;
}

bool getIsArgumentListSyntax(const base::Base& node) {
  NodeKind ndk = node.getNodeKind();
  return
    ndk == ndkArgumentListSyntax;
}

bool getIsArgumentSyntax(const base::Base& node) {
  NodeKind ndk = node.getNodeKind();
  return
    ndk == ndkArgumentSyntax;
}

bool getIsArrayRankSpecifierSyntax(const base::Base& node) {
  NodeKind ndk = node.getNodeKind();
  return
    ndk == ndkArrayRankSpecifierSyntax;
}

bool getIsArrowExpressionClauseSyntax(const base::Base& node) {
  NodeKind ndk = node.getNodeKind();
  return
    ndk == ndkArrowExpressionClauseSyntax;
}

bool getIsAttributeArgumentListSyntax(const base::Base& node) {
  NodeKind ndk = node.getNodeKind();
  return
    ndk == ndkAttributeArgumentListSyntax;
}

bool getIsAttributeArgumentSyntax(const base::Base& node) {
  NodeKind ndk = node.getNodeKind();
  return
    ndk == ndkAttributeArgumentSyntax;
}

bool getIsAttributeListSyntax(const base::Base& node) {
  NodeKind ndk = node.getNodeKind();
  return
    ndk == ndkAttributeListSyntax;
}

bool getIsAttributeSyntax(const base::Base& node) {
  NodeKind ndk = node.getNodeKind();
  return
    ndk == ndkAttributeSyntax;
}

bool getIsAttributeTargetSpecifierSyntax(const base::Base& node) {
  NodeKind ndk = node.getNodeKind();
  return
    ndk == ndkAttributeTargetSpecifierSyntax;
}

bool getIsBaseArgumentListSyntax(const base::Base& node) {
  NodeKind ndk = node.getNodeKind();
  return
    ndk == ndkBaseArgumentListSyntax ||
    ndk == ndkArgumentListSyntax ||
    ndk == ndkBracketedArgumentListSyntax;
}

bool getIsBaseCrefParameterListSyntax(const base::Base& node) {
  NodeKind ndk = node.getNodeKind();
  return
    ndk == ndkBaseCrefParameterListSyntax ||
    ndk == ndkCrefBracketedParameterListSyntax ||
    ndk == ndkCrefParameterListSyntax;
}

bool getIsBaseFieldDeclarationSyntax(const base::Base& node) {
  NodeKind ndk = node.getNodeKind();
  return
    ndk == ndkBaseFieldDeclarationSyntax ||
    ndk == ndkEventFieldDeclarationSyntax ||
    ndk == ndkFieldDeclarationSyntax;
}

bool getIsBaseListSyntax(const base::Base& node) {
  NodeKind ndk = node.getNodeKind();
  return
    ndk == ndkBaseListSyntax;
}

bool getIsBaseMethodDeclarationSyntax(const base::Base& node) {
  NodeKind ndk = node.getNodeKind();
  return
    ndk == ndkBaseMethodDeclarationSyntax ||
    ndk == ndkConstructorDeclarationSyntax ||
    ndk == ndkConversionOperatorDeclarationSyntax ||
    ndk == ndkDestructorDeclarationSyntax ||
    ndk == ndkMethodDeclarationSyntax ||
    ndk == ndkOperatorDeclarationSyntax;
}

bool getIsBaseParameterListSyntax(const base::Base& node) {
  NodeKind ndk = node.getNodeKind();
  return
    ndk == ndkBaseParameterListSyntax ||
    ndk == ndkBracketedParameterListSyntax ||
    ndk == ndkParameterListSyntax;
}

bool getIsBasePropertyDeclarationSyntax(const base::Base& node) {
  NodeKind ndk = node.getNodeKind();
  return
    ndk == ndkBasePropertyDeclarationSyntax ||
    ndk == ndkEventDeclarationSyntax ||
    ndk == ndkIndexerDeclarationSyntax ||
    ndk == ndkPropertyDeclarationSyntax;
}

bool getIsBaseTypeDeclarationSyntax(const base::Base& node) {
  NodeKind ndk = node.getNodeKind();
  return
    ndk == ndkBaseTypeDeclarationSyntax ||
    ndk == ndkEnumDeclarationSyntax ||
    ndk == ndkClassDeclarationSyntax ||
    ndk == ndkInterfaceDeclarationSyntax ||
    ndk == ndkStructDeclarationSyntax;
}

bool getIsBaseTypeSyntax(const base::Base& node) {
  NodeKind ndk = node.getNodeKind();
  return
    ndk == ndkBaseTypeSyntax ||
    ndk == ndkSimpleBaseTypeSyntax;
}

bool getIsBracketedArgumentListSyntax(const base::Base& node) {
  NodeKind ndk = node.getNodeKind();
  return
    ndk == ndkBracketedArgumentListSyntax;
}

bool getIsBracketedParameterListSyntax(const base::Base& node) {
  NodeKind ndk = node.getNodeKind();
  return
    ndk == ndkBracketedParameterListSyntax;
}

bool getIsCaseSwitchLabelSyntax(const base::Base& node) {
  NodeKind ndk = node.getNodeKind();
  return
    ndk == ndkCaseSwitchLabelSyntax;
}

bool getIsCatchClauseSyntax(const base::Base& node) {
  NodeKind ndk = node.getNodeKind();
  return
    ndk == ndkCatchClauseSyntax;
}

bool getIsCatchDeclarationSyntax(const base::Base& node) {
  NodeKind ndk = node.getNodeKind();
  return
    ndk == ndkCatchDeclarationSyntax;
}

bool getIsCatchFilterClauseSyntax(const base::Base& node) {
  NodeKind ndk = node.getNodeKind();
  return
    ndk == ndkCatchFilterClauseSyntax;
}

bool getIsClassDeclarationSyntax(const base::Base& node) {
  NodeKind ndk = node.getNodeKind();
  return
    ndk == ndkClassDeclarationSyntax;
}

bool getIsClassOrStructConstraintSyntax(const base::Base& node) {
  NodeKind ndk = node.getNodeKind();
  return
    ndk == ndkClassOrStructConstraintSyntax;
}

bool getIsCompilationUnitSyntax(const base::Base& node) {
  NodeKind ndk = node.getNodeKind();
  return
    ndk == ndkCompilationUnitSyntax;
}

bool getIsConstructorConstraintSyntax(const base::Base& node) {
  NodeKind ndk = node.getNodeKind();
  return
    ndk == ndkConstructorConstraintSyntax;
}

bool getIsConstructorDeclarationSyntax(const base::Base& node) {
  NodeKind ndk = node.getNodeKind();
  return
    ndk == ndkConstructorDeclarationSyntax;
}

bool getIsConstructorInitializerSyntax(const base::Base& node) {
  NodeKind ndk = node.getNodeKind();
  return
    ndk == ndkConstructorInitializerSyntax;
}

bool getIsConversionOperatorDeclarationSyntax(const base::Base& node) {
  NodeKind ndk = node.getNodeKind();
  return
    ndk == ndkConversionOperatorDeclarationSyntax;
}

bool getIsConversionOperatorMemberCrefSyntax(const base::Base& node) {
  NodeKind ndk = node.getNodeKind();
  return
    ndk == ndkConversionOperatorMemberCrefSyntax;
}

bool getIsCrefBracketedParameterListSyntax(const base::Base& node) {
  NodeKind ndk = node.getNodeKind();
  return
    ndk == ndkCrefBracketedParameterListSyntax;
}

bool getIsCrefParameterListSyntax(const base::Base& node) {
  NodeKind ndk = node.getNodeKind();
  return
    ndk == ndkCrefParameterListSyntax;
}

bool getIsCrefParameterSyntax(const base::Base& node) {
  NodeKind ndk = node.getNodeKind();
  return
    ndk == ndkCrefParameterSyntax;
}

bool getIsCrefSyntax(const base::Base& node) {
  NodeKind ndk = node.getNodeKind();
  return
    ndk == ndkCrefSyntax ||
    ndk == ndkConversionOperatorMemberCrefSyntax ||
    ndk == ndkIndexerMemberCrefSyntax ||
    ndk == ndkNameMemberCrefSyntax ||
    ndk == ndkOperatorMemberCrefSyntax ||
    ndk == ndkQualifiedCrefSyntax ||
    ndk == ndkTypeCrefSyntax;
}

bool getIsDefaultSwitchLabelSyntax(const base::Base& node) {
  NodeKind ndk = node.getNodeKind();
  return
    ndk == ndkDefaultSwitchLabelSyntax;
}

bool getIsDelegateDeclarationSyntax(const base::Base& node) {
  NodeKind ndk = node.getNodeKind();
  return
    ndk == ndkDelegateDeclarationSyntax;
}

bool getIsDestructorDeclarationSyntax(const base::Base& node) {
  NodeKind ndk = node.getNodeKind();
  return
    ndk == ndkDestructorDeclarationSyntax;
}

bool getIsElseClauseSyntax(const base::Base& node) {
  NodeKind ndk = node.getNodeKind();
  return
    ndk == ndkElseClauseSyntax;
}

bool getIsEnumDeclarationSyntax(const base::Base& node) {
  NodeKind ndk = node.getNodeKind();
  return
    ndk == ndkEnumDeclarationSyntax;
}

bool getIsEnumMemberDeclarationSyntax(const base::Base& node) {
  NodeKind ndk = node.getNodeKind();
  return
    ndk == ndkEnumMemberDeclarationSyntax;
}

bool getIsEqualsValueClauseSyntax(const base::Base& node) {
  NodeKind ndk = node.getNodeKind();
  return
    ndk == ndkEqualsValueClauseSyntax;
}

bool getIsEventDeclarationSyntax(const base::Base& node) {
  NodeKind ndk = node.getNodeKind();
  return
    ndk == ndkEventDeclarationSyntax;
}

bool getIsEventFieldDeclarationSyntax(const base::Base& node) {
  NodeKind ndk = node.getNodeKind();
  return
    ndk == ndkEventFieldDeclarationSyntax;
}

bool getIsExplicitInterfaceSpecifierSyntax(const base::Base& node) {
  NodeKind ndk = node.getNodeKind();
  return
    ndk == ndkExplicitInterfaceSpecifierSyntax;
}

bool getIsExternAliasDirectiveSyntax(const base::Base& node) {
  NodeKind ndk = node.getNodeKind();
  return
    ndk == ndkExternAliasDirectiveSyntax;
}

bool getIsFieldDeclarationSyntax(const base::Base& node) {
  NodeKind ndk = node.getNodeKind();
  return
    ndk == ndkFieldDeclarationSyntax;
}

bool getIsFinallyClauseSyntax(const base::Base& node) {
  NodeKind ndk = node.getNodeKind();
  return
    ndk == ndkFinallyClauseSyntax;
}

bool getIsFromClauseSyntax(const base::Base& node) {
  NodeKind ndk = node.getNodeKind();
  return
    ndk == ndkFromClauseSyntax;
}

bool getIsGlobalStatementSyntax(const base::Base& node) {
  NodeKind ndk = node.getNodeKind();
  return
    ndk == ndkGlobalStatementSyntax;
}

bool getIsGroupClauseSyntax(const base::Base& node) {
  NodeKind ndk = node.getNodeKind();
  return
    ndk == ndkGroupClauseSyntax;
}

bool getIsIncompleteMemberSyntax(const base::Base& node) {
  NodeKind ndk = node.getNodeKind();
  return
    ndk == ndkIncompleteMemberSyntax;
}

bool getIsIndexerDeclarationSyntax(const base::Base& node) {
  NodeKind ndk = node.getNodeKind();
  return
    ndk == ndkIndexerDeclarationSyntax;
}

bool getIsIndexerMemberCrefSyntax(const base::Base& node) {
  NodeKind ndk = node.getNodeKind();
  return
    ndk == ndkIndexerMemberCrefSyntax;
}

bool getIsInterfaceDeclarationSyntax(const base::Base& node) {
  NodeKind ndk = node.getNodeKind();
  return
    ndk == ndkInterfaceDeclarationSyntax;
}

bool getIsInterpolatedStringContentSyntax(const base::Base& node) {
  NodeKind ndk = node.getNodeKind();
  return
    ndk == ndkInterpolatedStringContentSyntax ||
    ndk == ndkInterpolatedStringTextSyntax ||
    ndk == ndkInterpolationSyntax;
}

bool getIsInterpolatedStringTextSyntax(const base::Base& node) {
  NodeKind ndk = node.getNodeKind();
  return
    ndk == ndkInterpolatedStringTextSyntax;
}

bool getIsInterpolationAlignmentClauseSyntax(const base::Base& node) {
  NodeKind ndk = node.getNodeKind();
  return
    ndk == ndkInterpolationAlignmentClauseSyntax;
}

bool getIsInterpolationFormatClauseSyntax(const base::Base& node) {
  NodeKind ndk = node.getNodeKind();
  return
    ndk == ndkInterpolationFormatClauseSyntax;
}

bool getIsInterpolationSyntax(const base::Base& node) {
  NodeKind ndk = node.getNodeKind();
  return
    ndk == ndkInterpolationSyntax;
}

bool getIsJoinClauseSyntax(const base::Base& node) {
  NodeKind ndk = node.getNodeKind();
  return
    ndk == ndkJoinClauseSyntax;
}

bool getIsJoinIntoClauseSyntax(const base::Base& node) {
  NodeKind ndk = node.getNodeKind();
  return
    ndk == ndkJoinIntoClauseSyntax;
}

bool getIsLetClauseSyntax(const base::Base& node) {
  NodeKind ndk = node.getNodeKind();
  return
    ndk == ndkLetClauseSyntax;
}

bool getIsMemberCrefSyntax(const base::Base& node) {
  NodeKind ndk = node.getNodeKind();
  return
    ndk == ndkMemberCrefSyntax ||
    ndk == ndkConversionOperatorMemberCrefSyntax ||
    ndk == ndkIndexerMemberCrefSyntax ||
    ndk == ndkNameMemberCrefSyntax ||
    ndk == ndkOperatorMemberCrefSyntax;
}

bool getIsMemberDeclarationSyntax(const base::Base& node) {
  NodeKind ndk = node.getNodeKind();
  return
    ndk == ndkMemberDeclarationSyntax ||
    ndk == ndkEventFieldDeclarationSyntax ||
    ndk == ndkFieldDeclarationSyntax ||
    ndk == ndkConstructorDeclarationSyntax ||
    ndk == ndkConversionOperatorDeclarationSyntax ||
    ndk == ndkDestructorDeclarationSyntax ||
    ndk == ndkMethodDeclarationSyntax ||
    ndk == ndkOperatorDeclarationSyntax ||
    ndk == ndkEventDeclarationSyntax ||
    ndk == ndkIndexerDeclarationSyntax ||
    ndk == ndkPropertyDeclarationSyntax ||
    ndk == ndkEnumDeclarationSyntax ||
    ndk == ndkClassDeclarationSyntax ||
    ndk == ndkInterfaceDeclarationSyntax ||
    ndk == ndkStructDeclarationSyntax ||
    ndk == ndkDelegateDeclarationSyntax ||
    ndk == ndkEnumMemberDeclarationSyntax ||
    ndk == ndkGlobalStatementSyntax ||
    ndk == ndkIncompleteMemberSyntax ||
    ndk == ndkNamespaceDeclarationSyntax;
}

bool getIsMethodDeclarationSyntax(const base::Base& node) {
  NodeKind ndk = node.getNodeKind();
  return
    ndk == ndkMethodDeclarationSyntax;
}

bool getIsNameColonSyntax(const base::Base& node) {
  NodeKind ndk = node.getNodeKind();
  return
    ndk == ndkNameColonSyntax;
}

bool getIsNameEqualsSyntax(const base::Base& node) {
  NodeKind ndk = node.getNodeKind();
  return
    ndk == ndkNameEqualsSyntax;
}

bool getIsNameMemberCrefSyntax(const base::Base& node) {
  NodeKind ndk = node.getNodeKind();
  return
    ndk == ndkNameMemberCrefSyntax;
}

bool getIsNamespaceDeclarationSyntax(const base::Base& node) {
  NodeKind ndk = node.getNodeKind();
  return
    ndk == ndkNamespaceDeclarationSyntax;
}

bool getIsOperatorDeclarationSyntax(const base::Base& node) {
  NodeKind ndk = node.getNodeKind();
  return
    ndk == ndkOperatorDeclarationSyntax;
}

bool getIsOperatorMemberCrefSyntax(const base::Base& node) {
  NodeKind ndk = node.getNodeKind();
  return
    ndk == ndkOperatorMemberCrefSyntax;
}

bool getIsOrderByClauseSyntax(const base::Base& node) {
  NodeKind ndk = node.getNodeKind();
  return
    ndk == ndkOrderByClauseSyntax;
}

bool getIsOrderingSyntax(const base::Base& node) {
  NodeKind ndk = node.getNodeKind();
  return
    ndk == ndkOrderingSyntax;
}

bool getIsParameterListSyntax(const base::Base& node) {
  NodeKind ndk = node.getNodeKind();
  return
    ndk == ndkParameterListSyntax;
}

bool getIsParameterSyntax(const base::Base& node) {
  NodeKind ndk = node.getNodeKind();
  return
    ndk == ndkParameterSyntax;
}

bool getIsPropertyDeclarationSyntax(const base::Base& node) {
  NodeKind ndk = node.getNodeKind();
  return
    ndk == ndkPropertyDeclarationSyntax;
}

bool getIsQualifiedCrefSyntax(const base::Base& node) {
  NodeKind ndk = node.getNodeKind();
  return
    ndk == ndkQualifiedCrefSyntax;
}

bool getIsQueryBodySyntax(const base::Base& node) {
  NodeKind ndk = node.getNodeKind();
  return
    ndk == ndkQueryBodySyntax;
}

bool getIsQueryClauseSyntax(const base::Base& node) {
  NodeKind ndk = node.getNodeKind();
  return
    ndk == ndkQueryClauseSyntax ||
    ndk == ndkFromClauseSyntax ||
    ndk == ndkJoinClauseSyntax ||
    ndk == ndkLetClauseSyntax ||
    ndk == ndkOrderByClauseSyntax ||
    ndk == ndkWhereClauseSyntax;
}

bool getIsQueryContinuationSyntax(const base::Base& node) {
  NodeKind ndk = node.getNodeKind();
  return
    ndk == ndkQueryContinuationSyntax;
}

bool getIsSelectClauseSyntax(const base::Base& node) {
  NodeKind ndk = node.getNodeKind();
  return
    ndk == ndkSelectClauseSyntax;
}

bool getIsSelectOrGroupClauseSyntax(const base::Base& node) {
  NodeKind ndk = node.getNodeKind();
  return
    ndk == ndkSelectOrGroupClauseSyntax ||
    ndk == ndkGroupClauseSyntax ||
    ndk == ndkSelectClauseSyntax;
}

bool getIsSimpleBaseTypeSyntax(const base::Base& node) {
  NodeKind ndk = node.getNodeKind();
  return
    ndk == ndkSimpleBaseTypeSyntax;
}

bool getIsStructDeclarationSyntax(const base::Base& node) {
  NodeKind ndk = node.getNodeKind();
  return
    ndk == ndkStructDeclarationSyntax;
}

bool getIsSwitchLabelSyntax(const base::Base& node) {
  NodeKind ndk = node.getNodeKind();
  return
    ndk == ndkSwitchLabelSyntax ||
    ndk == ndkCaseSwitchLabelSyntax ||
    ndk == ndkDefaultSwitchLabelSyntax;
}

bool getIsSwitchSectionSyntax(const base::Base& node) {
  NodeKind ndk = node.getNodeKind();
  return
    ndk == ndkSwitchSectionSyntax;
}

bool getIsSyntaxToken(const base::Base& node) {
  NodeKind ndk = node.getNodeKind();
  return
    ndk == ndkSyntaxToken;
}

bool getIsTypeArgumentListSyntax(const base::Base& node) {
  NodeKind ndk = node.getNodeKind();
  return
    ndk == ndkTypeArgumentListSyntax;
}

bool getIsTypeConstraintSyntax(const base::Base& node) {
  NodeKind ndk = node.getNodeKind();
  return
    ndk == ndkTypeConstraintSyntax;
}

bool getIsTypeCrefSyntax(const base::Base& node) {
  NodeKind ndk = node.getNodeKind();
  return
    ndk == ndkTypeCrefSyntax;
}

bool getIsTypeDeclarationSyntax(const base::Base& node) {
  NodeKind ndk = node.getNodeKind();
  return
    ndk == ndkTypeDeclarationSyntax ||
    ndk == ndkClassDeclarationSyntax ||
    ndk == ndkInterfaceDeclarationSyntax ||
    ndk == ndkStructDeclarationSyntax;
}

bool getIsTypeParameterConstraintClauseSyntax(const base::Base& node) {
  NodeKind ndk = node.getNodeKind();
  return
    ndk == ndkTypeParameterConstraintClauseSyntax;
}

bool getIsTypeParameterConstraintSyntax(const base::Base& node) {
  NodeKind ndk = node.getNodeKind();
  return
    ndk == ndkTypeParameterConstraintSyntax ||
    ndk == ndkClassOrStructConstraintSyntax ||
    ndk == ndkConstructorConstraintSyntax ||
    ndk == ndkTypeConstraintSyntax;
}

bool getIsTypeParameterListSyntax(const base::Base& node) {
  NodeKind ndk = node.getNodeKind();
  return
    ndk == ndkTypeParameterListSyntax;
}

bool getIsTypeParameterSyntax(const base::Base& node) {
  NodeKind ndk = node.getNodeKind();
  return
    ndk == ndkTypeParameterSyntax;
}

bool getIsUsingDirectiveSyntax(const base::Base& node) {
  NodeKind ndk = node.getNodeKind();
  return
    ndk == ndkUsingDirectiveSyntax;
}

bool getIsVariableDeclarationSyntax(const base::Base& node) {
  NodeKind ndk = node.getNodeKind();
  return
    ndk == ndkVariableDeclarationSyntax;
}

bool getIsVariableDeclaratorSyntax(const base::Base& node) {
  NodeKind ndk = node.getNodeKind();
  return
    ndk == ndkVariableDeclaratorSyntax;
}

bool getIsWhereClauseSyntax(const base::Base& node) {
  NodeKind ndk = node.getNodeKind();
  return
    ndk == ndkWhereClauseSyntax;
}

bool getIsXmlAttributeSyntax(const base::Base& node) {
  NodeKind ndk = node.getNodeKind();
  return
    ndk == ndkXmlAttributeSyntax ||
    ndk == ndkXmlCrefAttributeSyntax ||
    ndk == ndkXmlNameAttributeSyntax ||
    ndk == ndkXmlTextAttributeSyntax;
}

bool getIsXmlCDataSectionSyntax(const base::Base& node) {
  NodeKind ndk = node.getNodeKind();
  return
    ndk == ndkXmlCDataSectionSyntax;
}

bool getIsXmlCommentSyntax(const base::Base& node) {
  NodeKind ndk = node.getNodeKind();
  return
    ndk == ndkXmlCommentSyntax;
}

bool getIsXmlCrefAttributeSyntax(const base::Base& node) {
  NodeKind ndk = node.getNodeKind();
  return
    ndk == ndkXmlCrefAttributeSyntax;
}

bool getIsXmlElementEndTagSyntax(const base::Base& node) {
  NodeKind ndk = node.getNodeKind();
  return
    ndk == ndkXmlElementEndTagSyntax;
}

bool getIsXmlElementStartTagSyntax(const base::Base& node) {
  NodeKind ndk = node.getNodeKind();
  return
    ndk == ndkXmlElementStartTagSyntax;
}

bool getIsXmlElementSyntax(const base::Base& node) {
  NodeKind ndk = node.getNodeKind();
  return
    ndk == ndkXmlElementSyntax;
}

bool getIsXmlEmptyElementSyntax(const base::Base& node) {
  NodeKind ndk = node.getNodeKind();
  return
    ndk == ndkXmlEmptyElementSyntax;
}

bool getIsXmlNameAttributeSyntax(const base::Base& node) {
  NodeKind ndk = node.getNodeKind();
  return
    ndk == ndkXmlNameAttributeSyntax;
}

bool getIsXmlNameSyntax(const base::Base& node) {
  NodeKind ndk = node.getNodeKind();
  return
    ndk == ndkXmlNameSyntax;
}

bool getIsXmlNodeSyntax(const base::Base& node) {
  NodeKind ndk = node.getNodeKind();
  return
    ndk == ndkXmlNodeSyntax ||
    ndk == ndkXmlCDataSectionSyntax ||
    ndk == ndkXmlCommentSyntax ||
    ndk == ndkXmlElementSyntax ||
    ndk == ndkXmlEmptyElementSyntax ||
    ndk == ndkXmlProcessingInstructionSyntax ||
    ndk == ndkXmlTextSyntax;
}

bool getIsXmlPrefixSyntax(const base::Base& node) {
  NodeKind ndk = node.getNodeKind();
  return
    ndk == ndkXmlPrefixSyntax;
}

bool getIsXmlProcessingInstructionSyntax(const base::Base& node) {
  NodeKind ndk = node.getNodeKind();
  return
    ndk == ndkXmlProcessingInstructionSyntax;
}

bool getIsXmlTextAttributeSyntax(const base::Base& node) {
  NodeKind ndk = node.getNodeKind();
  return
    ndk == ndkXmlTextAttributeSyntax;
}

bool getIsXmlTextSyntax(const base::Base& node) {
  NodeKind ndk = node.getNodeKind();
  return
    ndk == ndkXmlTextSyntax;
}

bool getIsComposite(const base::Base& node) {
  return !getIsNotComposite(node);
}

bool getIsNamed(const base::Base& node) {
  NodeKind ndk = node.getNodeKind();
  return
    ndk == ndkAnonymousFunctionExpressionSyntax ||
    ndk == ndkAnonymousMethodExpressionSyntax ||
    ndk == ndkParenthesizedLambdaExpressionSyntax ||
    ndk == ndkSimpleLambdaExpressionSyntax ||
    ndk == ndkAnonymousObjectCreationExpressionSyntax ||
    ndk == ndkSimpleNameSyntax ||
    ndk == ndkGenericNameSyntax ||
    ndk == ndkIdentifierNameSyntax ||
    ndk == ndkForEachStatementSyntax ||
    ndk == ndkLabeledStatementSyntax ||
    ndk == ndkAccessorDeclarationSyntax ||
    ndk == ndkAttributeTargetSpecifierSyntax ||
    ndk == ndkExternAliasDirectiveSyntax ||
    ndk == ndkJoinIntoClauseSyntax ||
    ndk == ndkConstructorDeclarationSyntax ||
    ndk == ndkDestructorDeclarationSyntax ||
    ndk == ndkMethodDeclarationSyntax ||
    ndk == ndkEventDeclarationSyntax ||
    ndk == ndkPropertyDeclarationSyntax ||
    ndk == ndkBaseTypeDeclarationSyntax ||
    ndk == ndkEnumDeclarationSyntax ||
    ndk == ndkClassDeclarationSyntax ||
    ndk == ndkInterfaceDeclarationSyntax ||
    ndk == ndkStructDeclarationSyntax ||
    ndk == ndkDelegateDeclarationSyntax ||
    ndk == ndkEnumMemberDeclarationSyntax ||
    ndk == ndkParameterSyntax ||
    ndk == ndkFromClauseSyntax ||
    ndk == ndkJoinClauseSyntax ||
    ndk == ndkLetClauseSyntax ||
    ndk == ndkQueryContinuationSyntax ||
    ndk == ndkTypeParameterSyntax ||
    ndk == ndkVariableDeclaratorSyntax;
}

const std::string& getName(const base::Base& node) {
  NodeKind ndk = node.getNodeKind();
  switch (ndk) {
    case ndkAnonymousMethodExpressionSyntax:
    case ndkParenthesizedLambdaExpressionSyntax:
    case ndkSimpleLambdaExpressionSyntax:
    case ndkAnonymousFunctionExpressionSyntax: return dynamic_cast<const expression::AnonymousFunctionExpressionSyntax&>(node).getIdentifier();
    case ndkAnonymousObjectCreationExpressionSyntax: return dynamic_cast<const expression::AnonymousObjectCreationExpressionSyntax&>(node).getIdentifier();
    case ndkGenericNameSyntax:
    case ndkIdentifierNameSyntax:
    case ndkSimpleNameSyntax: return dynamic_cast<const expression::SimpleNameSyntax&>(node).getIdentifier();
    case ndkForEachStatementSyntax: return dynamic_cast<const statement::ForEachStatementSyntax&>(node).getIdentifier();
    case ndkLabeledStatementSyntax: return dynamic_cast<const statement::LabeledStatementSyntax&>(node).getIdentifier();
    case ndkAccessorDeclarationSyntax: return dynamic_cast<const structure::AccessorDeclarationSyntax&>(node).getIdentifier();
    case ndkAttributeTargetSpecifierSyntax: return dynamic_cast<const structure::AttributeTargetSpecifierSyntax&>(node).getIdentifier();
    case ndkExternAliasDirectiveSyntax: return dynamic_cast<const structure::ExternAliasDirectiveSyntax&>(node).getIdentifier();
    case ndkJoinIntoClauseSyntax: return dynamic_cast<const structure::JoinIntoClauseSyntax&>(node).getIdentifier();
    case ndkConstructorDeclarationSyntax: return dynamic_cast<const structure::ConstructorDeclarationSyntax&>(node).getIdentifier();
    case ndkDestructorDeclarationSyntax: return dynamic_cast<const structure::DestructorDeclarationSyntax&>(node).getIdentifier();
    case ndkMethodDeclarationSyntax: return dynamic_cast<const structure::MethodDeclarationSyntax&>(node).getIdentifier();
    case ndkEventDeclarationSyntax: return dynamic_cast<const structure::EventDeclarationSyntax&>(node).getIdentifier();
    case ndkPropertyDeclarationSyntax: return dynamic_cast<const structure::PropertyDeclarationSyntax&>(node).getIdentifier();
    case ndkEnumDeclarationSyntax:
    case ndkClassDeclarationSyntax:
    case ndkInterfaceDeclarationSyntax:
    case ndkStructDeclarationSyntax:
    case ndkBaseTypeDeclarationSyntax: return dynamic_cast<const structure::BaseTypeDeclarationSyntax&>(node).getIdentifier();
    case ndkDelegateDeclarationSyntax: return dynamic_cast<const structure::DelegateDeclarationSyntax&>(node).getIdentifier();
    case ndkEnumMemberDeclarationSyntax: return dynamic_cast<const structure::EnumMemberDeclarationSyntax&>(node).getIdentifier();
    case ndkParameterSyntax: return dynamic_cast<const structure::ParameterSyntax&>(node).getIdentifier();
    case ndkFromClauseSyntax: return dynamic_cast<const structure::FromClauseSyntax&>(node).getIdentifier();
    case ndkJoinClauseSyntax: return dynamic_cast<const structure::JoinClauseSyntax&>(node).getIdentifier();
    case ndkLetClauseSyntax: return dynamic_cast<const structure::LetClauseSyntax&>(node).getIdentifier();
    case ndkQueryContinuationSyntax: return dynamic_cast<const structure::QueryContinuationSyntax&>(node).getIdentifier();
    case ndkTypeParameterSyntax: return dynamic_cast<const structure::TypeParameterSyntax&>(node).getIdentifier();
    case ndkVariableDeclaratorSyntax: return dynamic_cast<const structure::VariableDeclaratorSyntax&>(node).getIdentifier();
    default: throw CsharpException(COLUMBUS_LOCATION, CMSG_EX_INVALID_NODE_KIND);
  }
}

bool getIsNotComposite(const base::Base& node) {
  NodeKind ndk = node.getNodeKind();
  return
    ndk == ndkBaseExpressionSyntax ||
    ndk == ndkThisExpressionSyntax ||
    ndk == ndkLiteralExpressionSyntax ||
    ndk == ndkOmittedArraySizeExpressionSyntax ||
    ndk == ndkIdentifierNameSyntax ||
    ndk == ndkOmittedTypeArgumentSyntax ||
    ndk == ndkPredefinedTypeSyntax ||
    ndk == ndkBreakStatementSyntax ||
    ndk == ndkContinueStatementSyntax ||
    ndk == ndkEmptyStatementSyntax ||
    ndk == ndkAttributeTargetSpecifierSyntax ||
    ndk == ndkExternAliasDirectiveSyntax ||
    ndk == ndkInterpolatedStringTextSyntax ||
    ndk == ndkInterpolationFormatClauseSyntax ||
    ndk == ndkJoinIntoClauseSyntax ||
    ndk == ndkDefaultSwitchLabelSyntax ||
    ndk == ndkSyntaxToken ||
    ndk == ndkClassOrStructConstraintSyntax ||
    ndk == ndkConstructorConstraintSyntax ||
    ndk == ndkTypeParameterListSyntax ||
    ndk == ndkXmlCDataSectionSyntax ||
    ndk == ndkXmlCommentSyntax ||
    ndk == ndkXmlTextSyntax ||
    ndk == ndkXmlPrefixSyntax;
}

const std::string toString(NodeId id) {
  std::stringstream s;
  s << id;
  return s.str();
}

bool getIsBaseClassKind(NodeKind what, NodeKind base) {
  NodeKind type = what;
  if (type == base)
    return true;
  switch (type) {
      case ndkBase:
        return false;
      case ndkPositioned:
        return getIsBaseClassKind(ndkBase, base);
      case ndkAliasQualifiedNameSyntax:
        return getIsBaseClassKind(ndkNameSyntax, base);
      case ndkAnonymousFunctionExpressionSyntax:
        return getIsBaseClassKind(ndkExpressionSyntax, base);
      case ndkAnonymousMethodExpressionSyntax:
        return getIsBaseClassKind(ndkAnonymousFunctionExpressionSyntax, base);
      case ndkAnonymousObjectCreationExpressionSyntax:
        return getIsBaseClassKind(ndkExpressionSyntax, base);
      case ndkArrayCreationExpressionSyntax:
        return getIsBaseClassKind(ndkExpressionSyntax, base);
      case ndkArrayTypeSyntax:
        return getIsBaseClassKind(ndkTypeSyntax, base);
      case ndkAssignmentExpressionSyntax:
        return getIsBaseClassKind(ndkExpressionSyntax, base);
      case ndkAwaitExpressionSyntax:
        return getIsBaseClassKind(ndkExpressionSyntax, base);
      case ndkBaseExpressionSyntax:
        return getIsBaseClassKind(ndkInstanceExpressionSyntax, base);
      case ndkBinaryExpressionSyntax:
        return getIsBaseClassKind(ndkExpressionSyntax, base);
      case ndkCastExpressionSyntax:
        return getIsBaseClassKind(ndkExpressionSyntax, base);
      case ndkCheckedExpressionSyntax:
        return getIsBaseClassKind(ndkExpressionSyntax, base);
      case ndkConditionalAccessExpressionSyntax:
        return getIsBaseClassKind(ndkExpressionSyntax, base);
      case ndkConditionalExpressionSyntax:
        return getIsBaseClassKind(ndkExpressionSyntax, base);
      case ndkDefaultExpressionSyntax:
        return getIsBaseClassKind(ndkExpressionSyntax, base);
      case ndkElementAccessExpressionSyntax:
        return getIsBaseClassKind(ndkExpressionSyntax, base);
      case ndkElementBindingExpressionSyntax:
        return getIsBaseClassKind(ndkExpressionSyntax, base);
      case ndkExpressionSyntax:
        return getIsBaseClassKind(ndkPositioned, base);
      case ndkGenericNameSyntax:
        return getIsBaseClassKind(ndkSimpleNameSyntax, base);
      case ndkIdentifierNameSyntax:
        return getIsBaseClassKind(ndkSimpleNameSyntax, base);
      case ndkImplicitArrayCreationExpressionSyntax:
        return getIsBaseClassKind(ndkExpressionSyntax, base);
      case ndkImplicitElementAccessSyntax:
        return getIsBaseClassKind(ndkExpressionSyntax, base);
      case ndkInitializerExpressionSyntax:
        return getIsBaseClassKind(ndkExpressionSyntax, base);
      case ndkInstanceExpressionSyntax:
        return getIsBaseClassKind(ndkExpressionSyntax, base);
      case ndkInterpolatedStringExpressionSyntax:
        return getIsBaseClassKind(ndkExpressionSyntax, base);
      case ndkInvocationExpressionSyntax:
        return getIsBaseClassKind(ndkExpressionSyntax, base);
      case ndkLambdaExpressionSyntax:
        return getIsBaseClassKind(ndkAnonymousFunctionExpressionSyntax, base);
      case ndkLiteralExpressionSyntax:
        return getIsBaseClassKind(ndkExpressionSyntax, base);
      case ndkMakeRefExpressionSyntax:
        return getIsBaseClassKind(ndkExpressionSyntax, base);
      case ndkMemberAccessExpressionSyntax:
        return getIsBaseClassKind(ndkExpressionSyntax, base);
      case ndkMemberBindingExpressionSyntax:
        return getIsBaseClassKind(ndkExpressionSyntax, base);
      case ndkNameSyntax:
        return getIsBaseClassKind(ndkTypeSyntax, base);
      case ndkNullableTypeSyntax:
        return getIsBaseClassKind(ndkTypeSyntax, base);
      case ndkObjectCreationExpressionSyntax:
        return getIsBaseClassKind(ndkExpressionSyntax, base);
      case ndkOmittedArraySizeExpressionSyntax:
        return getIsBaseClassKind(ndkExpressionSyntax, base);
      case ndkOmittedTypeArgumentSyntax:
        return getIsBaseClassKind(ndkTypeSyntax, base);
      case ndkParenthesizedExpressionSyntax:
        return getIsBaseClassKind(ndkExpressionSyntax, base);
      case ndkParenthesizedLambdaExpressionSyntax:
        return getIsBaseClassKind(ndkLambdaExpressionSyntax, base);
      case ndkPointerTypeSyntax:
        return getIsBaseClassKind(ndkTypeSyntax, base);
      case ndkPostfixUnaryExpressionSyntax:
        return getIsBaseClassKind(ndkExpressionSyntax, base);
      case ndkPredefinedTypeSyntax:
        return getIsBaseClassKind(ndkTypeSyntax, base);
      case ndkPrefixUnaryExpressionSyntax:
        return getIsBaseClassKind(ndkExpressionSyntax, base);
      case ndkQualifiedNameSyntax:
        return getIsBaseClassKind(ndkNameSyntax, base);
      case ndkQueryExpressionSyntax:
        return getIsBaseClassKind(ndkExpressionSyntax, base);
      case ndkRefTypeExpressionSyntax:
        return getIsBaseClassKind(ndkExpressionSyntax, base);
      case ndkRefValueExpressionSyntax:
        return getIsBaseClassKind(ndkExpressionSyntax, base);
      case ndkSimpleLambdaExpressionSyntax:
        return getIsBaseClassKind(ndkLambdaExpressionSyntax, base);
      case ndkSimpleNameSyntax:
        return getIsBaseClassKind(ndkNameSyntax, base);
      case ndkSizeOfExpressionSyntax:
        return getIsBaseClassKind(ndkExpressionSyntax, base);
      case ndkStackAllocArrayCreationExpressionSyntax:
        return getIsBaseClassKind(ndkExpressionSyntax, base);
      case ndkThisExpressionSyntax:
        return getIsBaseClassKind(ndkInstanceExpressionSyntax, base);
      case ndkTypeOfExpressionSyntax:
        return getIsBaseClassKind(ndkExpressionSyntax, base);
      case ndkTypeSyntax:
        return getIsBaseClassKind(ndkExpressionSyntax, base);
      case ndkBlockSyntax:
        return getIsBaseClassKind(ndkStatementSyntax, base);
      case ndkBreakStatementSyntax:
        return getIsBaseClassKind(ndkStatementSyntax, base);
      case ndkCheckedStatementSyntax:
        return getIsBaseClassKind(ndkStatementSyntax, base);
      case ndkContinueStatementSyntax:
        return getIsBaseClassKind(ndkStatementSyntax, base);
      case ndkDoStatementSyntax:
        return getIsBaseClassKind(ndkStatementSyntax, base);
      case ndkEmptyStatementSyntax:
        return getIsBaseClassKind(ndkStatementSyntax, base);
      case ndkExpressionStatementSyntax:
        return getIsBaseClassKind(ndkStatementSyntax, base);
      case ndkFixedStatementSyntax:
        return getIsBaseClassKind(ndkStatementSyntax, base);
      case ndkForEachStatementSyntax:
        return getIsBaseClassKind(ndkStatementSyntax, base);
      case ndkForStatementSyntax:
        return getIsBaseClassKind(ndkStatementSyntax, base);
      case ndkGotoStatementSyntax:
        return getIsBaseClassKind(ndkStatementSyntax, base);
      case ndkIfStatementSyntax:
        return getIsBaseClassKind(ndkStatementSyntax, base);
      case ndkLabeledStatementSyntax:
        return getIsBaseClassKind(ndkStatementSyntax, base);
      case ndkLocalDeclarationStatementSyntax:
        return getIsBaseClassKind(ndkStatementSyntax, base);
      case ndkLockStatementSyntax:
        return getIsBaseClassKind(ndkStatementSyntax, base);
      case ndkReturnStatementSyntax:
        return getIsBaseClassKind(ndkStatementSyntax, base);
      case ndkStatementSyntax:
        return getIsBaseClassKind(ndkPositioned, base);
      case ndkSwitchStatementSyntax:
        return getIsBaseClassKind(ndkStatementSyntax, base);
      case ndkThrowStatementSyntax:
        return getIsBaseClassKind(ndkStatementSyntax, base);
      case ndkTryStatementSyntax:
        return getIsBaseClassKind(ndkStatementSyntax, base);
      case ndkUnsafeStatementSyntax:
        return getIsBaseClassKind(ndkStatementSyntax, base);
      case ndkUsingStatementSyntax:
        return getIsBaseClassKind(ndkStatementSyntax, base);
      case ndkWhileStatementSyntax:
        return getIsBaseClassKind(ndkStatementSyntax, base);
      case ndkYieldStatementSyntax:
        return getIsBaseClassKind(ndkStatementSyntax, base);
      case ndkAccessorDeclarationSyntax:
        return getIsBaseClassKind(ndkPositioned, base);
      case ndkAccessorListSyntax:
        return getIsBaseClassKind(ndkPositioned, base);
      case ndkAnonymousObjectMemberDeclaratorSyntax:
        return getIsBaseClassKind(ndkPositioned, base);
      case ndkArgumentListSyntax:
        return getIsBaseClassKind(ndkBaseArgumentListSyntax, base);
      case ndkArgumentSyntax:
        return getIsBaseClassKind(ndkPositioned, base);
      case ndkArrayRankSpecifierSyntax:
        return getIsBaseClassKind(ndkPositioned, base);
      case ndkArrowExpressionClauseSyntax:
        return getIsBaseClassKind(ndkPositioned, base);
      case ndkAttributeArgumentListSyntax:
        return getIsBaseClassKind(ndkPositioned, base);
      case ndkAttributeArgumentSyntax:
        return getIsBaseClassKind(ndkPositioned, base);
      case ndkAttributeListSyntax:
        return getIsBaseClassKind(ndkPositioned, base);
      case ndkAttributeSyntax:
        return getIsBaseClassKind(ndkPositioned, base);
      case ndkAttributeTargetSpecifierSyntax:
        return getIsBaseClassKind(ndkPositioned, base);
      case ndkBaseArgumentListSyntax:
        return getIsBaseClassKind(ndkPositioned, base);
      case ndkBaseCrefParameterListSyntax:
        return getIsBaseClassKind(ndkPositioned, base);
      case ndkBaseFieldDeclarationSyntax:
        return getIsBaseClassKind(ndkMemberDeclarationSyntax, base);
      case ndkBaseListSyntax:
        return getIsBaseClassKind(ndkPositioned, base);
      case ndkBaseMethodDeclarationSyntax:
        return getIsBaseClassKind(ndkMemberDeclarationSyntax, base);
      case ndkBaseParameterListSyntax:
        return getIsBaseClassKind(ndkPositioned, base);
      case ndkBasePropertyDeclarationSyntax:
        return getIsBaseClassKind(ndkMemberDeclarationSyntax, base);
      case ndkBaseTypeDeclarationSyntax:
        return getIsBaseClassKind(ndkMemberDeclarationSyntax, base);
      case ndkBaseTypeSyntax:
        return getIsBaseClassKind(ndkPositioned, base);
      case ndkBracketedArgumentListSyntax:
        return getIsBaseClassKind(ndkBaseArgumentListSyntax, base);
      case ndkBracketedParameterListSyntax:
        return getIsBaseClassKind(ndkBaseParameterListSyntax, base);
      case ndkCaseSwitchLabelSyntax:
        return getIsBaseClassKind(ndkSwitchLabelSyntax, base);
      case ndkCatchClauseSyntax:
        return getIsBaseClassKind(ndkPositioned, base);
      case ndkCatchDeclarationSyntax:
        return getIsBaseClassKind(ndkPositioned, base);
      case ndkCatchFilterClauseSyntax:
        return getIsBaseClassKind(ndkPositioned, base);
      case ndkClassDeclarationSyntax:
        return getIsBaseClassKind(ndkTypeDeclarationSyntax, base);
      case ndkClassOrStructConstraintSyntax:
        return getIsBaseClassKind(ndkTypeParameterConstraintSyntax, base);
      case ndkCompilationUnitSyntax:
        return getIsBaseClassKind(ndkPositioned, base);
      case ndkConstructorConstraintSyntax:
        return getIsBaseClassKind(ndkTypeParameterConstraintSyntax, base);
      case ndkConstructorDeclarationSyntax:
        return getIsBaseClassKind(ndkBaseMethodDeclarationSyntax, base);
      case ndkConstructorInitializerSyntax:
        return getIsBaseClassKind(ndkPositioned, base);
      case ndkConversionOperatorDeclarationSyntax:
        return getIsBaseClassKind(ndkBaseMethodDeclarationSyntax, base);
      case ndkConversionOperatorMemberCrefSyntax:
        return getIsBaseClassKind(ndkMemberCrefSyntax, base);
      case ndkCrefBracketedParameterListSyntax:
        return getIsBaseClassKind(ndkBaseCrefParameterListSyntax, base);
      case ndkCrefParameterListSyntax:
        return getIsBaseClassKind(ndkBaseCrefParameterListSyntax, base);
      case ndkCrefParameterSyntax:
        return getIsBaseClassKind(ndkPositioned, base);
      case ndkCrefSyntax:
        return getIsBaseClassKind(ndkPositioned, base);
      case ndkDefaultSwitchLabelSyntax:
        return getIsBaseClassKind(ndkSwitchLabelSyntax, base);
      case ndkDelegateDeclarationSyntax:
        return getIsBaseClassKind(ndkMemberDeclarationSyntax, base);
      case ndkDestructorDeclarationSyntax:
        return getIsBaseClassKind(ndkBaseMethodDeclarationSyntax, base);
      case ndkElseClauseSyntax:
        return getIsBaseClassKind(ndkPositioned, base);
      case ndkEnumDeclarationSyntax:
        return getIsBaseClassKind(ndkBaseTypeDeclarationSyntax, base);
      case ndkEnumMemberDeclarationSyntax:
        return getIsBaseClassKind(ndkMemberDeclarationSyntax, base);
      case ndkEqualsValueClauseSyntax:
        return getIsBaseClassKind(ndkPositioned, base);
      case ndkEventDeclarationSyntax:
        return getIsBaseClassKind(ndkBasePropertyDeclarationSyntax, base);
      case ndkEventFieldDeclarationSyntax:
        return getIsBaseClassKind(ndkBaseFieldDeclarationSyntax, base);
      case ndkExplicitInterfaceSpecifierSyntax:
        return getIsBaseClassKind(ndkPositioned, base);
      case ndkExternAliasDirectiveSyntax:
        return getIsBaseClassKind(ndkPositioned, base);
      case ndkFieldDeclarationSyntax:
        return getIsBaseClassKind(ndkBaseFieldDeclarationSyntax, base);
      case ndkFinallyClauseSyntax:
        return getIsBaseClassKind(ndkPositioned, base);
      case ndkFromClauseSyntax:
        return getIsBaseClassKind(ndkQueryClauseSyntax, base);
      case ndkGlobalStatementSyntax:
        return getIsBaseClassKind(ndkMemberDeclarationSyntax, base);
      case ndkGroupClauseSyntax:
        return getIsBaseClassKind(ndkSelectOrGroupClauseSyntax, base);
      case ndkIncompleteMemberSyntax:
        return getIsBaseClassKind(ndkMemberDeclarationSyntax, base);
      case ndkIndexerDeclarationSyntax:
        return getIsBaseClassKind(ndkBasePropertyDeclarationSyntax, base);
      case ndkIndexerMemberCrefSyntax:
        return getIsBaseClassKind(ndkMemberCrefSyntax, base);
      case ndkInterfaceDeclarationSyntax:
        return getIsBaseClassKind(ndkTypeDeclarationSyntax, base);
      case ndkInterpolatedStringContentSyntax:
        return getIsBaseClassKind(ndkPositioned, base);
      case ndkInterpolatedStringTextSyntax:
        return getIsBaseClassKind(ndkInterpolatedStringContentSyntax, base);
      case ndkInterpolationAlignmentClauseSyntax:
        return getIsBaseClassKind(ndkPositioned, base);
      case ndkInterpolationFormatClauseSyntax:
        return getIsBaseClassKind(ndkPositioned, base);
      case ndkInterpolationSyntax:
        return getIsBaseClassKind(ndkInterpolatedStringContentSyntax, base);
      case ndkJoinClauseSyntax:
        return getIsBaseClassKind(ndkQueryClauseSyntax, base);
      case ndkJoinIntoClauseSyntax:
        return getIsBaseClassKind(ndkPositioned, base);
      case ndkLetClauseSyntax:
        return getIsBaseClassKind(ndkQueryClauseSyntax, base);
      case ndkMemberCrefSyntax:
        return getIsBaseClassKind(ndkCrefSyntax, base);
      case ndkMemberDeclarationSyntax:
        return getIsBaseClassKind(ndkPositioned, base);
      case ndkMethodDeclarationSyntax:
        return getIsBaseClassKind(ndkBaseMethodDeclarationSyntax, base);
      case ndkNameColonSyntax:
        return getIsBaseClassKind(ndkPositioned, base);
      case ndkNameEqualsSyntax:
        return getIsBaseClassKind(ndkPositioned, base);
      case ndkNameMemberCrefSyntax:
        return getIsBaseClassKind(ndkMemberCrefSyntax, base);
      case ndkNamespaceDeclarationSyntax:
        return getIsBaseClassKind(ndkMemberDeclarationSyntax, base);
      case ndkOperatorDeclarationSyntax:
        return getIsBaseClassKind(ndkBaseMethodDeclarationSyntax, base);
      case ndkOperatorMemberCrefSyntax:
        return getIsBaseClassKind(ndkMemberCrefSyntax, base);
      case ndkOrderByClauseSyntax:
        return getIsBaseClassKind(ndkQueryClauseSyntax, base);
      case ndkOrderingSyntax:
        return getIsBaseClassKind(ndkPositioned, base);
      case ndkParameterListSyntax:
        return getIsBaseClassKind(ndkBaseParameterListSyntax, base);
      case ndkParameterSyntax:
        return getIsBaseClassKind(ndkPositioned, base);
      case ndkPropertyDeclarationSyntax:
        return getIsBaseClassKind(ndkBasePropertyDeclarationSyntax, base);
      case ndkQualifiedCrefSyntax:
        return getIsBaseClassKind(ndkCrefSyntax, base);
      case ndkQueryBodySyntax:
        return getIsBaseClassKind(ndkPositioned, base);
      case ndkQueryClauseSyntax:
        return getIsBaseClassKind(ndkPositioned, base);
      case ndkQueryContinuationSyntax:
        return getIsBaseClassKind(ndkPositioned, base);
      case ndkSelectClauseSyntax:
        return getIsBaseClassKind(ndkSelectOrGroupClauseSyntax, base);
      case ndkSelectOrGroupClauseSyntax:
        return getIsBaseClassKind(ndkPositioned, base);
      case ndkSimpleBaseTypeSyntax:
        return getIsBaseClassKind(ndkBaseTypeSyntax, base);
      case ndkStructDeclarationSyntax:
        return getIsBaseClassKind(ndkTypeDeclarationSyntax, base);
      case ndkSwitchLabelSyntax:
        return getIsBaseClassKind(ndkPositioned, base);
      case ndkSwitchSectionSyntax:
        return getIsBaseClassKind(ndkPositioned, base);
      case ndkSyntaxToken:
        return getIsBaseClassKind(ndkPositioned, base);
      case ndkTypeArgumentListSyntax:
        return getIsBaseClassKind(ndkPositioned, base);
      case ndkTypeConstraintSyntax:
        return getIsBaseClassKind(ndkTypeParameterConstraintSyntax, base);
      case ndkTypeCrefSyntax:
        return getIsBaseClassKind(ndkCrefSyntax, base);
      case ndkTypeDeclarationSyntax:
        return getIsBaseClassKind(ndkBaseTypeDeclarationSyntax, base);
      case ndkTypeParameterConstraintClauseSyntax:
        return getIsBaseClassKind(ndkPositioned, base);
      case ndkTypeParameterConstraintSyntax:
        return getIsBaseClassKind(ndkPositioned, base);
      case ndkTypeParameterListSyntax:
        return getIsBaseClassKind(ndkPositioned, base);
      case ndkTypeParameterSyntax:
        return getIsBaseClassKind(ndkPositioned, base);
      case ndkUsingDirectiveSyntax:
        return getIsBaseClassKind(ndkPositioned, base);
      case ndkVariableDeclarationSyntax:
        return getIsBaseClassKind(ndkPositioned, base);
      case ndkVariableDeclaratorSyntax:
        return getIsBaseClassKind(ndkPositioned, base);
      case ndkWhereClauseSyntax:
        return getIsBaseClassKind(ndkQueryClauseSyntax, base);
      case ndkXmlAttributeSyntax:
        return getIsBaseClassKind(ndkPositioned, base);
      case ndkXmlCDataSectionSyntax:
        return getIsBaseClassKind(ndkXmlNodeSyntax, base);
      case ndkXmlCommentSyntax:
        return getIsBaseClassKind(ndkXmlNodeSyntax, base);
      case ndkXmlCrefAttributeSyntax:
        return getIsBaseClassKind(ndkXmlAttributeSyntax, base);
      case ndkXmlElementEndTagSyntax:
        return getIsBaseClassKind(ndkPositioned, base);
      case ndkXmlElementStartTagSyntax:
        return getIsBaseClassKind(ndkPositioned, base);
      case ndkXmlElementSyntax:
        return getIsBaseClassKind(ndkXmlNodeSyntax, base);
      case ndkXmlEmptyElementSyntax:
        return getIsBaseClassKind(ndkXmlNodeSyntax, base);
      case ndkXmlNameAttributeSyntax:
        return getIsBaseClassKind(ndkXmlAttributeSyntax, base);
      case ndkXmlNameSyntax:
        return getIsBaseClassKind(ndkPositioned, base);
      case ndkXmlNodeSyntax:
        return getIsBaseClassKind(ndkPositioned, base);
      case ndkXmlPrefixSyntax:
        return getIsBaseClassKind(ndkPositioned, base);
      case ndkXmlProcessingInstructionSyntax:
        return getIsBaseClassKind(ndkXmlNodeSyntax, base);
      case ndkXmlTextAttributeSyntax:
        return getIsBaseClassKind(ndkXmlAttributeSyntax, base);
      case ndkXmlTextSyntax:
        return getIsBaseClassKind(ndkXmlNodeSyntax, base);
      default:
        return false;
  }
  return false;
}

const std::string toString(NodeKind kind) {
  switch (kind) {
    case ndkBase: return "ndkBase";
    case ndkPositioned: return "ndkPositioned";
    case ndkAliasQualifiedNameSyntax: return "ndkAliasQualifiedNameSyntax";
    case ndkAnonymousFunctionExpressionSyntax: return "ndkAnonymousFunctionExpressionSyntax";
    case ndkAnonymousMethodExpressionSyntax: return "ndkAnonymousMethodExpressionSyntax";
    case ndkAnonymousObjectCreationExpressionSyntax: return "ndkAnonymousObjectCreationExpressionSyntax";
    case ndkArrayCreationExpressionSyntax: return "ndkArrayCreationExpressionSyntax";
    case ndkArrayTypeSyntax: return "ndkArrayTypeSyntax";
    case ndkAssignmentExpressionSyntax: return "ndkAssignmentExpressionSyntax";
    case ndkAwaitExpressionSyntax: return "ndkAwaitExpressionSyntax";
    case ndkBaseExpressionSyntax: return "ndkBaseExpressionSyntax";
    case ndkBinaryExpressionSyntax: return "ndkBinaryExpressionSyntax";
    case ndkCastExpressionSyntax: return "ndkCastExpressionSyntax";
    case ndkCheckedExpressionSyntax: return "ndkCheckedExpressionSyntax";
    case ndkConditionalAccessExpressionSyntax: return "ndkConditionalAccessExpressionSyntax";
    case ndkConditionalExpressionSyntax: return "ndkConditionalExpressionSyntax";
    case ndkDefaultExpressionSyntax: return "ndkDefaultExpressionSyntax";
    case ndkElementAccessExpressionSyntax: return "ndkElementAccessExpressionSyntax";
    case ndkElementBindingExpressionSyntax: return "ndkElementBindingExpressionSyntax";
    case ndkExpressionSyntax: return "ndkExpressionSyntax";
    case ndkGenericNameSyntax: return "ndkGenericNameSyntax";
    case ndkIdentifierNameSyntax: return "ndkIdentifierNameSyntax";
    case ndkImplicitArrayCreationExpressionSyntax: return "ndkImplicitArrayCreationExpressionSyntax";
    case ndkImplicitElementAccessSyntax: return "ndkImplicitElementAccessSyntax";
    case ndkInitializerExpressionSyntax: return "ndkInitializerExpressionSyntax";
    case ndkInstanceExpressionSyntax: return "ndkInstanceExpressionSyntax";
    case ndkInterpolatedStringExpressionSyntax: return "ndkInterpolatedStringExpressionSyntax";
    case ndkInvocationExpressionSyntax: return "ndkInvocationExpressionSyntax";
    case ndkLambdaExpressionSyntax: return "ndkLambdaExpressionSyntax";
    case ndkLiteralExpressionSyntax: return "ndkLiteralExpressionSyntax";
    case ndkMakeRefExpressionSyntax: return "ndkMakeRefExpressionSyntax";
    case ndkMemberAccessExpressionSyntax: return "ndkMemberAccessExpressionSyntax";
    case ndkMemberBindingExpressionSyntax: return "ndkMemberBindingExpressionSyntax";
    case ndkNameSyntax: return "ndkNameSyntax";
    case ndkNullableTypeSyntax: return "ndkNullableTypeSyntax";
    case ndkObjectCreationExpressionSyntax: return "ndkObjectCreationExpressionSyntax";
    case ndkOmittedArraySizeExpressionSyntax: return "ndkOmittedArraySizeExpressionSyntax";
    case ndkOmittedTypeArgumentSyntax: return "ndkOmittedTypeArgumentSyntax";
    case ndkParenthesizedExpressionSyntax: return "ndkParenthesizedExpressionSyntax";
    case ndkParenthesizedLambdaExpressionSyntax: return "ndkParenthesizedLambdaExpressionSyntax";
    case ndkPointerTypeSyntax: return "ndkPointerTypeSyntax";
    case ndkPostfixUnaryExpressionSyntax: return "ndkPostfixUnaryExpressionSyntax";
    case ndkPredefinedTypeSyntax: return "ndkPredefinedTypeSyntax";
    case ndkPrefixUnaryExpressionSyntax: return "ndkPrefixUnaryExpressionSyntax";
    case ndkQualifiedNameSyntax: return "ndkQualifiedNameSyntax";
    case ndkQueryExpressionSyntax: return "ndkQueryExpressionSyntax";
    case ndkRefTypeExpressionSyntax: return "ndkRefTypeExpressionSyntax";
    case ndkRefValueExpressionSyntax: return "ndkRefValueExpressionSyntax";
    case ndkSimpleLambdaExpressionSyntax: return "ndkSimpleLambdaExpressionSyntax";
    case ndkSimpleNameSyntax: return "ndkSimpleNameSyntax";
    case ndkSizeOfExpressionSyntax: return "ndkSizeOfExpressionSyntax";
    case ndkStackAllocArrayCreationExpressionSyntax: return "ndkStackAllocArrayCreationExpressionSyntax";
    case ndkThisExpressionSyntax: return "ndkThisExpressionSyntax";
    case ndkTypeOfExpressionSyntax: return "ndkTypeOfExpressionSyntax";
    case ndkTypeSyntax: return "ndkTypeSyntax";
    case ndkBlockSyntax: return "ndkBlockSyntax";
    case ndkBreakStatementSyntax: return "ndkBreakStatementSyntax";
    case ndkCheckedStatementSyntax: return "ndkCheckedStatementSyntax";
    case ndkContinueStatementSyntax: return "ndkContinueStatementSyntax";
    case ndkDoStatementSyntax: return "ndkDoStatementSyntax";
    case ndkEmptyStatementSyntax: return "ndkEmptyStatementSyntax";
    case ndkExpressionStatementSyntax: return "ndkExpressionStatementSyntax";
    case ndkFixedStatementSyntax: return "ndkFixedStatementSyntax";
    case ndkForEachStatementSyntax: return "ndkForEachStatementSyntax";
    case ndkForStatementSyntax: return "ndkForStatementSyntax";
    case ndkGotoStatementSyntax: return "ndkGotoStatementSyntax";
    case ndkIfStatementSyntax: return "ndkIfStatementSyntax";
    case ndkLabeledStatementSyntax: return "ndkLabeledStatementSyntax";
    case ndkLocalDeclarationStatementSyntax: return "ndkLocalDeclarationStatementSyntax";
    case ndkLockStatementSyntax: return "ndkLockStatementSyntax";
    case ndkReturnStatementSyntax: return "ndkReturnStatementSyntax";
    case ndkStatementSyntax: return "ndkStatementSyntax";
    case ndkSwitchStatementSyntax: return "ndkSwitchStatementSyntax";
    case ndkThrowStatementSyntax: return "ndkThrowStatementSyntax";
    case ndkTryStatementSyntax: return "ndkTryStatementSyntax";
    case ndkUnsafeStatementSyntax: return "ndkUnsafeStatementSyntax";
    case ndkUsingStatementSyntax: return "ndkUsingStatementSyntax";
    case ndkWhileStatementSyntax: return "ndkWhileStatementSyntax";
    case ndkYieldStatementSyntax: return "ndkYieldStatementSyntax";
    case ndkAccessorDeclarationSyntax: return "ndkAccessorDeclarationSyntax";
    case ndkAccessorListSyntax: return "ndkAccessorListSyntax";
    case ndkAnonymousObjectMemberDeclaratorSyntax: return "ndkAnonymousObjectMemberDeclaratorSyntax";
    case ndkArgumentListSyntax: return "ndkArgumentListSyntax";
    case ndkArgumentSyntax: return "ndkArgumentSyntax";
    case ndkArrayRankSpecifierSyntax: return "ndkArrayRankSpecifierSyntax";
    case ndkArrowExpressionClauseSyntax: return "ndkArrowExpressionClauseSyntax";
    case ndkAttributeArgumentListSyntax: return "ndkAttributeArgumentListSyntax";
    case ndkAttributeArgumentSyntax: return "ndkAttributeArgumentSyntax";
    case ndkAttributeListSyntax: return "ndkAttributeListSyntax";
    case ndkAttributeSyntax: return "ndkAttributeSyntax";
    case ndkAttributeTargetSpecifierSyntax: return "ndkAttributeTargetSpecifierSyntax";
    case ndkBaseArgumentListSyntax: return "ndkBaseArgumentListSyntax";
    case ndkBaseCrefParameterListSyntax: return "ndkBaseCrefParameterListSyntax";
    case ndkBaseFieldDeclarationSyntax: return "ndkBaseFieldDeclarationSyntax";
    case ndkBaseListSyntax: return "ndkBaseListSyntax";
    case ndkBaseMethodDeclarationSyntax: return "ndkBaseMethodDeclarationSyntax";
    case ndkBaseParameterListSyntax: return "ndkBaseParameterListSyntax";
    case ndkBasePropertyDeclarationSyntax: return "ndkBasePropertyDeclarationSyntax";
    case ndkBaseTypeDeclarationSyntax: return "ndkBaseTypeDeclarationSyntax";
    case ndkBaseTypeSyntax: return "ndkBaseTypeSyntax";
    case ndkBracketedArgumentListSyntax: return "ndkBracketedArgumentListSyntax";
    case ndkBracketedParameterListSyntax: return "ndkBracketedParameterListSyntax";
    case ndkCaseSwitchLabelSyntax: return "ndkCaseSwitchLabelSyntax";
    case ndkCatchClauseSyntax: return "ndkCatchClauseSyntax";
    case ndkCatchDeclarationSyntax: return "ndkCatchDeclarationSyntax";
    case ndkCatchFilterClauseSyntax: return "ndkCatchFilterClauseSyntax";
    case ndkClassDeclarationSyntax: return "ndkClassDeclarationSyntax";
    case ndkClassOrStructConstraintSyntax: return "ndkClassOrStructConstraintSyntax";
    case ndkCompilationUnitSyntax: return "ndkCompilationUnitSyntax";
    case ndkConstructorConstraintSyntax: return "ndkConstructorConstraintSyntax";
    case ndkConstructorDeclarationSyntax: return "ndkConstructorDeclarationSyntax";
    case ndkConstructorInitializerSyntax: return "ndkConstructorInitializerSyntax";
    case ndkConversionOperatorDeclarationSyntax: return "ndkConversionOperatorDeclarationSyntax";
    case ndkConversionOperatorMemberCrefSyntax: return "ndkConversionOperatorMemberCrefSyntax";
    case ndkCrefBracketedParameterListSyntax: return "ndkCrefBracketedParameterListSyntax";
    case ndkCrefParameterListSyntax: return "ndkCrefParameterListSyntax";
    case ndkCrefParameterSyntax: return "ndkCrefParameterSyntax";
    case ndkCrefSyntax: return "ndkCrefSyntax";
    case ndkDefaultSwitchLabelSyntax: return "ndkDefaultSwitchLabelSyntax";
    case ndkDelegateDeclarationSyntax: return "ndkDelegateDeclarationSyntax";
    case ndkDestructorDeclarationSyntax: return "ndkDestructorDeclarationSyntax";
    case ndkElseClauseSyntax: return "ndkElseClauseSyntax";
    case ndkEnumDeclarationSyntax: return "ndkEnumDeclarationSyntax";
    case ndkEnumMemberDeclarationSyntax: return "ndkEnumMemberDeclarationSyntax";
    case ndkEqualsValueClauseSyntax: return "ndkEqualsValueClauseSyntax";
    case ndkEventDeclarationSyntax: return "ndkEventDeclarationSyntax";
    case ndkEventFieldDeclarationSyntax: return "ndkEventFieldDeclarationSyntax";
    case ndkExplicitInterfaceSpecifierSyntax: return "ndkExplicitInterfaceSpecifierSyntax";
    case ndkExternAliasDirectiveSyntax: return "ndkExternAliasDirectiveSyntax";
    case ndkFieldDeclarationSyntax: return "ndkFieldDeclarationSyntax";
    case ndkFinallyClauseSyntax: return "ndkFinallyClauseSyntax";
    case ndkFromClauseSyntax: return "ndkFromClauseSyntax";
    case ndkGlobalStatementSyntax: return "ndkGlobalStatementSyntax";
    case ndkGroupClauseSyntax: return "ndkGroupClauseSyntax";
    case ndkIncompleteMemberSyntax: return "ndkIncompleteMemberSyntax";
    case ndkIndexerDeclarationSyntax: return "ndkIndexerDeclarationSyntax";
    case ndkIndexerMemberCrefSyntax: return "ndkIndexerMemberCrefSyntax";
    case ndkInterfaceDeclarationSyntax: return "ndkInterfaceDeclarationSyntax";
    case ndkInterpolatedStringContentSyntax: return "ndkInterpolatedStringContentSyntax";
    case ndkInterpolatedStringTextSyntax: return "ndkInterpolatedStringTextSyntax";
    case ndkInterpolationAlignmentClauseSyntax: return "ndkInterpolationAlignmentClauseSyntax";
    case ndkInterpolationFormatClauseSyntax: return "ndkInterpolationFormatClauseSyntax";
    case ndkInterpolationSyntax: return "ndkInterpolationSyntax";
    case ndkJoinClauseSyntax: return "ndkJoinClauseSyntax";
    case ndkJoinIntoClauseSyntax: return "ndkJoinIntoClauseSyntax";
    case ndkLetClauseSyntax: return "ndkLetClauseSyntax";
    case ndkMemberCrefSyntax: return "ndkMemberCrefSyntax";
    case ndkMemberDeclarationSyntax: return "ndkMemberDeclarationSyntax";
    case ndkMethodDeclarationSyntax: return "ndkMethodDeclarationSyntax";
    case ndkNameColonSyntax: return "ndkNameColonSyntax";
    case ndkNameEqualsSyntax: return "ndkNameEqualsSyntax";
    case ndkNameMemberCrefSyntax: return "ndkNameMemberCrefSyntax";
    case ndkNamespaceDeclarationSyntax: return "ndkNamespaceDeclarationSyntax";
    case ndkOperatorDeclarationSyntax: return "ndkOperatorDeclarationSyntax";
    case ndkOperatorMemberCrefSyntax: return "ndkOperatorMemberCrefSyntax";
    case ndkOrderByClauseSyntax: return "ndkOrderByClauseSyntax";
    case ndkOrderingSyntax: return "ndkOrderingSyntax";
    case ndkParameterListSyntax: return "ndkParameterListSyntax";
    case ndkParameterSyntax: return "ndkParameterSyntax";
    case ndkPropertyDeclarationSyntax: return "ndkPropertyDeclarationSyntax";
    case ndkQualifiedCrefSyntax: return "ndkQualifiedCrefSyntax";
    case ndkQueryBodySyntax: return "ndkQueryBodySyntax";
    case ndkQueryClauseSyntax: return "ndkQueryClauseSyntax";
    case ndkQueryContinuationSyntax: return "ndkQueryContinuationSyntax";
    case ndkSelectClauseSyntax: return "ndkSelectClauseSyntax";
    case ndkSelectOrGroupClauseSyntax: return "ndkSelectOrGroupClauseSyntax";
    case ndkSimpleBaseTypeSyntax: return "ndkSimpleBaseTypeSyntax";
    case ndkStructDeclarationSyntax: return "ndkStructDeclarationSyntax";
    case ndkSwitchLabelSyntax: return "ndkSwitchLabelSyntax";
    case ndkSwitchSectionSyntax: return "ndkSwitchSectionSyntax";
    case ndkSyntaxToken: return "ndkSyntaxToken";
    case ndkTypeArgumentListSyntax: return "ndkTypeArgumentListSyntax";
    case ndkTypeConstraintSyntax: return "ndkTypeConstraintSyntax";
    case ndkTypeCrefSyntax: return "ndkTypeCrefSyntax";
    case ndkTypeDeclarationSyntax: return "ndkTypeDeclarationSyntax";
    case ndkTypeParameterConstraintClauseSyntax: return "ndkTypeParameterConstraintClauseSyntax";
    case ndkTypeParameterConstraintSyntax: return "ndkTypeParameterConstraintSyntax";
    case ndkTypeParameterListSyntax: return "ndkTypeParameterListSyntax";
    case ndkTypeParameterSyntax: return "ndkTypeParameterSyntax";
    case ndkUsingDirectiveSyntax: return "ndkUsingDirectiveSyntax";
    case ndkVariableDeclarationSyntax: return "ndkVariableDeclarationSyntax";
    case ndkVariableDeclaratorSyntax: return "ndkVariableDeclaratorSyntax";
    case ndkWhereClauseSyntax: return "ndkWhereClauseSyntax";
    case ndkXmlAttributeSyntax: return "ndkXmlAttributeSyntax";
    case ndkXmlCDataSectionSyntax: return "ndkXmlCDataSectionSyntax";
    case ndkXmlCommentSyntax: return "ndkXmlCommentSyntax";
    case ndkXmlCrefAttributeSyntax: return "ndkXmlCrefAttributeSyntax";
    case ndkXmlElementEndTagSyntax: return "ndkXmlElementEndTagSyntax";
    case ndkXmlElementStartTagSyntax: return "ndkXmlElementStartTagSyntax";
    case ndkXmlElementSyntax: return "ndkXmlElementSyntax";
    case ndkXmlEmptyElementSyntax: return "ndkXmlEmptyElementSyntax";
    case ndkXmlNameAttributeSyntax: return "ndkXmlNameAttributeSyntax";
    case ndkXmlNameSyntax: return "ndkXmlNameSyntax";
    case ndkXmlNodeSyntax: return "ndkXmlNodeSyntax";
    case ndkXmlPrefixSyntax: return "ndkXmlPrefixSyntax";
    case ndkXmlProcessingInstructionSyntax: return "ndkXmlProcessingInstructionSyntax";
    case ndkXmlTextAttributeSyntax: return "ndkXmlTextAttributeSyntax";
    case ndkXmlTextSyntax: return "ndkXmlTextSyntax";
    default: throw CsharpException(COLUMBUS_LOCATION, CMSG_EX_INVALID_NODE_KIND);
  }
}

const std::string toString(EdgeKind kind) {
  switch (kind) {
    case edkAliasQualifiedNameSyntax_Alias: return "edkAliasQualifiedNameSyntax_Alias";
    case edkAliasQualifiedNameSyntax_Name: return "edkAliasQualifiedNameSyntax_Name";
    case edkAnonymousFunctionExpressionSyntax_Body: return "edkAnonymousFunctionExpressionSyntax_Body";
    case edkAnonymousMethodExpressionSyntax_ParameterList: return "edkAnonymousMethodExpressionSyntax_ParameterList";
    case edkAnonymousObjectCreationExpressionSyntax_Initializers: return "edkAnonymousObjectCreationExpressionSyntax_Initializers";
    case edkArrayCreationExpressionSyntax_Initializer: return "edkArrayCreationExpressionSyntax_Initializer";
    case edkArrayCreationExpressionSyntax_Type: return "edkArrayCreationExpressionSyntax_Type";
    case edkArrayTypeSyntax_ElementType: return "edkArrayTypeSyntax_ElementType";
    case edkArrayTypeSyntax_RankSpecifiers: return "edkArrayTypeSyntax_RankSpecifiers";
    case edkAssignmentExpressionSyntax_EventAccessorCall: return "edkAssignmentExpressionSyntax_EventAccessorCall";
    case edkAssignmentExpressionSyntax_Left: return "edkAssignmentExpressionSyntax_Left";
    case edkAssignmentExpressionSyntax_OverloadedOperatorCall: return "edkAssignmentExpressionSyntax_OverloadedOperatorCall";
    case edkAssignmentExpressionSyntax_Right: return "edkAssignmentExpressionSyntax_Right";
    case edkAwaitExpressionSyntax_Expression: return "edkAwaitExpressionSyntax_Expression";
    case edkBinaryExpressionSyntax_Left: return "edkBinaryExpressionSyntax_Left";
    case edkBinaryExpressionSyntax_OverloadedOperatorCall: return "edkBinaryExpressionSyntax_OverloadedOperatorCall";
    case edkBinaryExpressionSyntax_Right: return "edkBinaryExpressionSyntax_Right";
    case edkCastExpressionSyntax_ConversionOperatorCall: return "edkCastExpressionSyntax_ConversionOperatorCall";
    case edkCastExpressionSyntax_Expression: return "edkCastExpressionSyntax_Expression";
    case edkCastExpressionSyntax_Type: return "edkCastExpressionSyntax_Type";
    case edkCheckedExpressionSyntax_Expression: return "edkCheckedExpressionSyntax_Expression";
    case edkConditionalAccessExpressionSyntax_Expression: return "edkConditionalAccessExpressionSyntax_Expression";
    case edkConditionalAccessExpressionSyntax_WhenNotNull: return "edkConditionalAccessExpressionSyntax_WhenNotNull";
    case edkConditionalExpressionSyntax_Condition: return "edkConditionalExpressionSyntax_Condition";
    case edkConditionalExpressionSyntax_WhenFalse: return "edkConditionalExpressionSyntax_WhenFalse";
    case edkConditionalExpressionSyntax_WhenTrue: return "edkConditionalExpressionSyntax_WhenTrue";
    case edkDefaultExpressionSyntax_Type: return "edkDefaultExpressionSyntax_Type";
    case edkElementAccessExpressionSyntax_AccessorCall: return "edkElementAccessExpressionSyntax_AccessorCall";
    case edkElementAccessExpressionSyntax_ArgumentList: return "edkElementAccessExpressionSyntax_ArgumentList";
    case edkElementAccessExpressionSyntax_Expression: return "edkElementAccessExpressionSyntax_Expression";
    case edkElementBindingExpressionSyntax_ArgumentList: return "edkElementBindingExpressionSyntax_ArgumentList";
    case edkGenericNameSyntax_TypeArgumentList: return "edkGenericNameSyntax_TypeArgumentList";
    case edkIdentifierNameSyntax_AccessorCall: return "edkIdentifierNameSyntax_AccessorCall";
    case edkIdentifierNameSyntax_Declaration: return "edkIdentifierNameSyntax_Declaration";
    case edkImplicitArrayCreationExpressionSyntax_Initializer: return "edkImplicitArrayCreationExpressionSyntax_Initializer";
    case edkImplicitElementAccessSyntax_ArgumentList: return "edkImplicitElementAccessSyntax_ArgumentList";
    case edkInitializerExpressionSyntax_Expressions: return "edkInitializerExpressionSyntax_Expressions";
    case edkInterpolatedStringExpressionSyntax_Contents: return "edkInterpolatedStringExpressionSyntax_Contents";
    case edkInvocationExpressionSyntax_ArgumentList: return "edkInvocationExpressionSyntax_ArgumentList";
    case edkInvocationExpressionSyntax_Expression: return "edkInvocationExpressionSyntax_Expression";
    case edkInvocationExpressionSyntax_MethodCall: return "edkInvocationExpressionSyntax_MethodCall";
    case edkMakeRefExpressionSyntax_Expression: return "edkMakeRefExpressionSyntax_Expression";
    case edkMemberAccessExpressionSyntax_Expression: return "edkMemberAccessExpressionSyntax_Expression";
    case edkMemberAccessExpressionSyntax_Name: return "edkMemberAccessExpressionSyntax_Name";
    case edkMemberBindingExpressionSyntax_Name: return "edkMemberBindingExpressionSyntax_Name";
    case edkNullableTypeSyntax_ElementType: return "edkNullableTypeSyntax_ElementType";
    case edkObjectCreationExpressionSyntax_ArgumentList: return "edkObjectCreationExpressionSyntax_ArgumentList";
    case edkObjectCreationExpressionSyntax_ConstructorCall: return "edkObjectCreationExpressionSyntax_ConstructorCall";
    case edkObjectCreationExpressionSyntax_Initializer: return "edkObjectCreationExpressionSyntax_Initializer";
    case edkObjectCreationExpressionSyntax_Type: return "edkObjectCreationExpressionSyntax_Type";
    case edkParenthesizedExpressionSyntax_Expression: return "edkParenthesizedExpressionSyntax_Expression";
    case edkParenthesizedLambdaExpressionSyntax_ParameterList: return "edkParenthesizedLambdaExpressionSyntax_ParameterList";
    case edkPointerTypeSyntax_ElementType: return "edkPointerTypeSyntax_ElementType";
    case edkPostfixUnaryExpressionSyntax_Operand: return "edkPostfixUnaryExpressionSyntax_Operand";
    case edkPostfixUnaryExpressionSyntax_OverloadedOperatorCall: return "edkPostfixUnaryExpressionSyntax_OverloadedOperatorCall";
    case edkPrefixUnaryExpressionSyntax_Operand: return "edkPrefixUnaryExpressionSyntax_Operand";
    case edkPrefixUnaryExpressionSyntax_OverloadedOperatorCall: return "edkPrefixUnaryExpressionSyntax_OverloadedOperatorCall";
    case edkQualifiedNameSyntax_Left: return "edkQualifiedNameSyntax_Left";
    case edkQualifiedNameSyntax_Right: return "edkQualifiedNameSyntax_Right";
    case edkQueryExpressionSyntax_Body: return "edkQueryExpressionSyntax_Body";
    case edkQueryExpressionSyntax_FromClause: return "edkQueryExpressionSyntax_FromClause";
    case edkRefTypeExpressionSyntax_Expression: return "edkRefTypeExpressionSyntax_Expression";
    case edkRefValueExpressionSyntax_Expression: return "edkRefValueExpressionSyntax_Expression";
    case edkRefValueExpressionSyntax_Type: return "edkRefValueExpressionSyntax_Type";
    case edkSimpleLambdaExpressionSyntax_Parameter: return "edkSimpleLambdaExpressionSyntax_Parameter";
    case edkSizeOfExpressionSyntax_Type: return "edkSizeOfExpressionSyntax_Type";
    case edkStackAllocArrayCreationExpressionSyntax_Type: return "edkStackAllocArrayCreationExpressionSyntax_Type";
    case edkTypeOfExpressionSyntax_Type: return "edkTypeOfExpressionSyntax_Type";
    case edkTypeSyntax_OriginalDefinition: return "edkTypeSyntax_OriginalDefinition";
    case edkBlockSyntax_Statements: return "edkBlockSyntax_Statements";
    case edkCheckedStatementSyntax_Block: return "edkCheckedStatementSyntax_Block";
    case edkDoStatementSyntax_Condition: return "edkDoStatementSyntax_Condition";
    case edkDoStatementSyntax_Statement: return "edkDoStatementSyntax_Statement";
    case edkExpressionStatementSyntax_Expression: return "edkExpressionStatementSyntax_Expression";
    case edkFixedStatementSyntax_Declaration: return "edkFixedStatementSyntax_Declaration";
    case edkFixedStatementSyntax_Statement: return "edkFixedStatementSyntax_Statement";
    case edkForEachStatementSyntax_Expression: return "edkForEachStatementSyntax_Expression";
    case edkForEachStatementSyntax_Statement: return "edkForEachStatementSyntax_Statement";
    case edkForEachStatementSyntax_Type: return "edkForEachStatementSyntax_Type";
    case edkForStatementSyntax_Condition: return "edkForStatementSyntax_Condition";
    case edkForStatementSyntax_Declaration: return "edkForStatementSyntax_Declaration";
    case edkForStatementSyntax_Incrementors: return "edkForStatementSyntax_Incrementors";
    case edkForStatementSyntax_Initializers: return "edkForStatementSyntax_Initializers";
    case edkForStatementSyntax_Statement: return "edkForStatementSyntax_Statement";
    case edkGotoStatementSyntax_Expression: return "edkGotoStatementSyntax_Expression";
    case edkIfStatementSyntax_Condition: return "edkIfStatementSyntax_Condition";
    case edkIfStatementSyntax_Else: return "edkIfStatementSyntax_Else";
    case edkIfStatementSyntax_Statement: return "edkIfStatementSyntax_Statement";
    case edkLabeledStatementSyntax_Statement: return "edkLabeledStatementSyntax_Statement";
    case edkLocalDeclarationStatementSyntax_Declaration: return "edkLocalDeclarationStatementSyntax_Declaration";
    case edkLockStatementSyntax_Expression: return "edkLockStatementSyntax_Expression";
    case edkLockStatementSyntax_Statement: return "edkLockStatementSyntax_Statement";
    case edkReturnStatementSyntax_Expression: return "edkReturnStatementSyntax_Expression";
    case edkSwitchStatementSyntax_Expression: return "edkSwitchStatementSyntax_Expression";
    case edkSwitchStatementSyntax_Sections: return "edkSwitchStatementSyntax_Sections";
    case edkThrowStatementSyntax_Expression: return "edkThrowStatementSyntax_Expression";
    case edkTryStatementSyntax_Block: return "edkTryStatementSyntax_Block";
    case edkTryStatementSyntax_Catches: return "edkTryStatementSyntax_Catches";
    case edkTryStatementSyntax_Finally: return "edkTryStatementSyntax_Finally";
    case edkUnsafeStatementSyntax_Block: return "edkUnsafeStatementSyntax_Block";
    case edkUsingStatementSyntax_Declaration: return "edkUsingStatementSyntax_Declaration";
    case edkUsingStatementSyntax_Expression: return "edkUsingStatementSyntax_Expression";
    case edkUsingStatementSyntax_Statement: return "edkUsingStatementSyntax_Statement";
    case edkWhileStatementSyntax_Condition: return "edkWhileStatementSyntax_Condition";
    case edkWhileStatementSyntax_Statement: return "edkWhileStatementSyntax_Statement";
    case edkYieldStatementSyntax_Expression: return "edkYieldStatementSyntax_Expression";
    case edkAccessorDeclarationSyntax_AttributeLists: return "edkAccessorDeclarationSyntax_AttributeLists";
    case edkAccessorDeclarationSyntax_Body: return "edkAccessorDeclarationSyntax_Body";
    case edkAccessorListSyntax_Accessors: return "edkAccessorListSyntax_Accessors";
    case edkAnonymousObjectMemberDeclaratorSyntax_Expression: return "edkAnonymousObjectMemberDeclaratorSyntax_Expression";
    case edkAnonymousObjectMemberDeclaratorSyntax_NameEquals: return "edkAnonymousObjectMemberDeclaratorSyntax_NameEquals";
    case edkArgumentSyntax_Expression: return "edkArgumentSyntax_Expression";
    case edkArgumentSyntax_NameColon: return "edkArgumentSyntax_NameColon";
    case edkArrayRankSpecifierSyntax_Sizes: return "edkArrayRankSpecifierSyntax_Sizes";
    case edkArrowExpressionClauseSyntax_Expression: return "edkArrowExpressionClauseSyntax_Expression";
    case edkAttributeArgumentListSyntax_Arguments: return "edkAttributeArgumentListSyntax_Arguments";
    case edkAttributeArgumentSyntax_Expression: return "edkAttributeArgumentSyntax_Expression";
    case edkAttributeArgumentSyntax_NameColon: return "edkAttributeArgumentSyntax_NameColon";
    case edkAttributeArgumentSyntax_NameEquals: return "edkAttributeArgumentSyntax_NameEquals";
    case edkAttributeListSyntax_Attributes: return "edkAttributeListSyntax_Attributes";
    case edkAttributeListSyntax_Target: return "edkAttributeListSyntax_Target";
    case edkAttributeSyntax_ArgumentList: return "edkAttributeSyntax_ArgumentList";
    case edkAttributeSyntax_Name: return "edkAttributeSyntax_Name";
    case edkBaseArgumentListSyntax_Arguments: return "edkBaseArgumentListSyntax_Arguments";
    case edkBaseCrefParameterListSyntax_Parameters: return "edkBaseCrefParameterListSyntax_Parameters";
    case edkBaseFieldDeclarationSyntax_AttributeLists: return "edkBaseFieldDeclarationSyntax_AttributeLists";
    case edkBaseFieldDeclarationSyntax_Declaration: return "edkBaseFieldDeclarationSyntax_Declaration";
    case edkBaseListSyntax_Types: return "edkBaseListSyntax_Types";
    case edkBaseMethodDeclarationSyntax_AccessedEnumMembers: return "edkBaseMethodDeclarationSyntax_AccessedEnumMembers";
    case edkBaseMethodDeclarationSyntax_AttributeLists: return "edkBaseMethodDeclarationSyntax_AttributeLists";
    case edkBaseMethodDeclarationSyntax_Body: return "edkBaseMethodDeclarationSyntax_Body";
    case edkBaseMethodDeclarationSyntax_ParameterList: return "edkBaseMethodDeclarationSyntax_ParameterList";
    case edkBaseParameterListSyntax_Parameters: return "edkBaseParameterListSyntax_Parameters";
    case edkBasePropertyDeclarationSyntax_AccessorList: return "edkBasePropertyDeclarationSyntax_AccessorList";
    case edkBasePropertyDeclarationSyntax_AttributeLists: return "edkBasePropertyDeclarationSyntax_AttributeLists";
    case edkBasePropertyDeclarationSyntax_ExplicitInterfaceSpecifier: return "edkBasePropertyDeclarationSyntax_ExplicitInterfaceSpecifier";
    case edkBasePropertyDeclarationSyntax_Type: return "edkBasePropertyDeclarationSyntax_Type";
    case edkBaseTypeDeclarationSyntax_AttributeLists: return "edkBaseTypeDeclarationSyntax_AttributeLists";
    case edkBaseTypeDeclarationSyntax_BaseList: return "edkBaseTypeDeclarationSyntax_BaseList";
    case edkBaseTypeSyntax_Type: return "edkBaseTypeSyntax_Type";
    case edkCaseSwitchLabelSyntax_Value: return "edkCaseSwitchLabelSyntax_Value";
    case edkCatchClauseSyntax_Block: return "edkCatchClauseSyntax_Block";
    case edkCatchClauseSyntax_Declaration: return "edkCatchClauseSyntax_Declaration";
    case edkCatchClauseSyntax_Filter: return "edkCatchClauseSyntax_Filter";
    case edkCatchDeclarationSyntax_Type: return "edkCatchDeclarationSyntax_Type";
    case edkCatchFilterClauseSyntax_FilterExpression: return "edkCatchFilterClauseSyntax_FilterExpression";
    case edkCompilationUnitSyntax_AttributeLists: return "edkCompilationUnitSyntax_AttributeLists";
    case edkCompilationUnitSyntax_Externs: return "edkCompilationUnitSyntax_Externs";
    case edkCompilationUnitSyntax_Members: return "edkCompilationUnitSyntax_Members";
    case edkCompilationUnitSyntax_Usings: return "edkCompilationUnitSyntax_Usings";
    case edkConstructorDeclarationSyntax_Initializer: return "edkConstructorDeclarationSyntax_Initializer";
    case edkConstructorInitializerSyntax_ArgumentList: return "edkConstructorInitializerSyntax_ArgumentList";
    case edkConstructorInitializerSyntax_ConstructorCall: return "edkConstructorInitializerSyntax_ConstructorCall";
    case edkConversionOperatorDeclarationSyntax_ExpressionBody: return "edkConversionOperatorDeclarationSyntax_ExpressionBody";
    case edkConversionOperatorDeclarationSyntax_Type: return "edkConversionOperatorDeclarationSyntax_Type";
    case edkConversionOperatorMemberCrefSyntax_Parameters: return "edkConversionOperatorMemberCrefSyntax_Parameters";
    case edkConversionOperatorMemberCrefSyntax_Type: return "edkConversionOperatorMemberCrefSyntax_Type";
    case edkCrefParameterSyntax_Type: return "edkCrefParameterSyntax_Type";
    case edkDelegateDeclarationSyntax_AttributeLists: return "edkDelegateDeclarationSyntax_AttributeLists";
    case edkDelegateDeclarationSyntax_ConstraintClauses: return "edkDelegateDeclarationSyntax_ConstraintClauses";
    case edkDelegateDeclarationSyntax_ParameterList: return "edkDelegateDeclarationSyntax_ParameterList";
    case edkDelegateDeclarationSyntax_ReturnType: return "edkDelegateDeclarationSyntax_ReturnType";
    case edkElseClauseSyntax_Statement: return "edkElseClauseSyntax_Statement";
    case edkEnumDeclarationSyntax_Members: return "edkEnumDeclarationSyntax_Members";
    case edkEnumMemberDeclarationSyntax_AttributeLists: return "edkEnumMemberDeclarationSyntax_AttributeLists";
    case edkEnumMemberDeclarationSyntax_EqualsValue: return "edkEnumMemberDeclarationSyntax_EqualsValue";
    case edkEqualsValueClauseSyntax_Value: return "edkEqualsValueClauseSyntax_Value";
    case edkExplicitInterfaceSpecifierSyntax_Name: return "edkExplicitInterfaceSpecifierSyntax_Name";
    case edkFinallyClauseSyntax_Block: return "edkFinallyClauseSyntax_Block";
    case edkFromClauseSyntax_Expression: return "edkFromClauseSyntax_Expression";
    case edkFromClauseSyntax_Type: return "edkFromClauseSyntax_Type";
    case edkGlobalStatementSyntax_Statement: return "edkGlobalStatementSyntax_Statement";
    case edkGroupClauseSyntax_ByExpression: return "edkGroupClauseSyntax_ByExpression";
    case edkGroupClauseSyntax_GroupExpression: return "edkGroupClauseSyntax_GroupExpression";
    case edkIncompleteMemberSyntax_AttributeLists: return "edkIncompleteMemberSyntax_AttributeLists";
    case edkIncompleteMemberSyntax_Type: return "edkIncompleteMemberSyntax_Type";
    case edkIndexerDeclarationSyntax_ExpressionBody: return "edkIndexerDeclarationSyntax_ExpressionBody";
    case edkIndexerDeclarationSyntax_ParameterList: return "edkIndexerDeclarationSyntax_ParameterList";
    case edkIndexerMemberCrefSyntax_Parameters: return "edkIndexerMemberCrefSyntax_Parameters";
    case edkInterpolationAlignmentClauseSyntax_Value: return "edkInterpolationAlignmentClauseSyntax_Value";
    case edkInterpolationSyntax_AlignmentClause: return "edkInterpolationSyntax_AlignmentClause";
    case edkInterpolationSyntax_Expression: return "edkInterpolationSyntax_Expression";
    case edkInterpolationSyntax_FormatClause: return "edkInterpolationSyntax_FormatClause";
    case edkJoinClauseSyntax_InExpression: return "edkJoinClauseSyntax_InExpression";
    case edkJoinClauseSyntax_Into: return "edkJoinClauseSyntax_Into";
    case edkJoinClauseSyntax_LeftExpression: return "edkJoinClauseSyntax_LeftExpression";
    case edkJoinClauseSyntax_RightExpression: return "edkJoinClauseSyntax_RightExpression";
    case edkJoinClauseSyntax_Type: return "edkJoinClauseSyntax_Type";
    case edkLetClauseSyntax_Expression: return "edkLetClauseSyntax_Expression";
    case edkMethodDeclarationSyntax_ConstraintClauses: return "edkMethodDeclarationSyntax_ConstraintClauses";
    case edkMethodDeclarationSyntax_ExplicitInterfaceSpecifier: return "edkMethodDeclarationSyntax_ExplicitInterfaceSpecifier";
    case edkMethodDeclarationSyntax_ExpressionBody: return "edkMethodDeclarationSyntax_ExpressionBody";
    case edkMethodDeclarationSyntax_ReturnType: return "edkMethodDeclarationSyntax_ReturnType";
    case edkNameColonSyntax_Name: return "edkNameColonSyntax_Name";
    case edkNameEqualsSyntax_Name: return "edkNameEqualsSyntax_Name";
    case edkNameMemberCrefSyntax_Name: return "edkNameMemberCrefSyntax_Name";
    case edkNameMemberCrefSyntax_Parameters: return "edkNameMemberCrefSyntax_Parameters";
    case edkNamespaceDeclarationSyntax_Externs: return "edkNamespaceDeclarationSyntax_Externs";
    case edkNamespaceDeclarationSyntax_Members: return "edkNamespaceDeclarationSyntax_Members";
    case edkNamespaceDeclarationSyntax_Name: return "edkNamespaceDeclarationSyntax_Name";
    case edkNamespaceDeclarationSyntax_Usings: return "edkNamespaceDeclarationSyntax_Usings";
    case edkOperatorDeclarationSyntax_ExpressionBody: return "edkOperatorDeclarationSyntax_ExpressionBody";
    case edkOperatorDeclarationSyntax_ReturnType: return "edkOperatorDeclarationSyntax_ReturnType";
    case edkOperatorMemberCrefSyntax_Parameters: return "edkOperatorMemberCrefSyntax_Parameters";
    case edkOrderByClauseSyntax_Orderings: return "edkOrderByClauseSyntax_Orderings";
    case edkOrderingSyntax_Expression: return "edkOrderingSyntax_Expression";
    case edkParameterSyntax_AttributeLists: return "edkParameterSyntax_AttributeLists";
    case edkParameterSyntax_Default: return "edkParameterSyntax_Default";
    case edkParameterSyntax_Type: return "edkParameterSyntax_Type";
    case edkPropertyDeclarationSyntax_ExpressionBody: return "edkPropertyDeclarationSyntax_ExpressionBody";
    case edkPropertyDeclarationSyntax_Initializer: return "edkPropertyDeclarationSyntax_Initializer";
    case edkQualifiedCrefSyntax_Container: return "edkQualifiedCrefSyntax_Container";
    case edkQualifiedCrefSyntax_Member: return "edkQualifiedCrefSyntax_Member";
    case edkQueryBodySyntax_Clauses: return "edkQueryBodySyntax_Clauses";
    case edkQueryBodySyntax_Continuation: return "edkQueryBodySyntax_Continuation";
    case edkQueryBodySyntax_SelectOrGroup: return "edkQueryBodySyntax_SelectOrGroup";
    case edkQueryContinuationSyntax_Body: return "edkQueryContinuationSyntax_Body";
    case edkSelectClauseSyntax_Expression: return "edkSelectClauseSyntax_Expression";
    case edkSwitchSectionSyntax_Labels: return "edkSwitchSectionSyntax_Labels";
    case edkSwitchSectionSyntax_Statements: return "edkSwitchSectionSyntax_Statements";
    case edkTypeArgumentListSyntax_Arguments: return "edkTypeArgumentListSyntax_Arguments";
    case edkTypeConstraintSyntax_Type: return "edkTypeConstraintSyntax_Type";
    case edkTypeCrefSyntax_Type: return "edkTypeCrefSyntax_Type";
    case edkTypeDeclarationSyntax_ConstraintClauses: return "edkTypeDeclarationSyntax_ConstraintClauses";
    case edkTypeDeclarationSyntax_Members: return "edkTypeDeclarationSyntax_Members";
    case edkTypeDeclarationSyntax_TypeParameterList: return "edkTypeDeclarationSyntax_TypeParameterList";
    case edkTypeParameterConstraintClauseSyntax_Constraints: return "edkTypeParameterConstraintClauseSyntax_Constraints";
    case edkTypeParameterConstraintClauseSyntax_Name: return "edkTypeParameterConstraintClauseSyntax_Name";
    case edkTypeParameterListSyntax_Parameters: return "edkTypeParameterListSyntax_Parameters";
    case edkTypeParameterSyntax_AttributeLists: return "edkTypeParameterSyntax_AttributeLists";
    case edkUsingDirectiveSyntax_Alias: return "edkUsingDirectiveSyntax_Alias";
    case edkUsingDirectiveSyntax_Name: return "edkUsingDirectiveSyntax_Name";
    case edkVariableDeclarationSyntax_Type: return "edkVariableDeclarationSyntax_Type";
    case edkVariableDeclarationSyntax_Variables: return "edkVariableDeclarationSyntax_Variables";
    case edkVariableDeclaratorSyntax_ArgumentList: return "edkVariableDeclaratorSyntax_ArgumentList";
    case edkVariableDeclaratorSyntax_Initializer: return "edkVariableDeclaratorSyntax_Initializer";
    case edkWhereClauseSyntax_Condition: return "edkWhereClauseSyntax_Condition";
    case edkXmlAttributeSyntax_Name: return "edkXmlAttributeSyntax_Name";
    case edkXmlCrefAttributeSyntax_Cref: return "edkXmlCrefAttributeSyntax_Cref";
    case edkXmlElementEndTagSyntax_Name: return "edkXmlElementEndTagSyntax_Name";
    case edkXmlElementStartTagSyntax_Attributes: return "edkXmlElementStartTagSyntax_Attributes";
    case edkXmlElementStartTagSyntax_Name: return "edkXmlElementStartTagSyntax_Name";
    case edkXmlElementSyntax_Content: return "edkXmlElementSyntax_Content";
    case edkXmlElementSyntax_EndTag: return "edkXmlElementSyntax_EndTag";
    case edkXmlElementSyntax_StartTag: return "edkXmlElementSyntax_StartTag";
    case edkXmlEmptyElementSyntax_Attributes: return "edkXmlEmptyElementSyntax_Attributes";
    case edkXmlEmptyElementSyntax_Name: return "edkXmlEmptyElementSyntax_Name";
    case edkXmlNameAttributeSyntax_Identifier: return "edkXmlNameAttributeSyntax_Identifier";
    case edkXmlNameSyntax_Prefix: return "edkXmlNameSyntax_Prefix";
    case edkXmlProcessingInstructionSyntax_Name: return "edkXmlProcessingInstructionSyntax_Name";
    default: throw CsharpException(COLUMBUS_LOCATION, CMSG_EX_INVALID_NODE_KIND);
  }
}

bool getIsValid(NodeId id) {
  return id > 1;
}

double SimilarityMinimum = 0.1;

double getSimilarityMinimum() {
  return SimilarityMinimum;
}

void setSimilarityMinimum(double value) {
  SimilarityMinimum = value;
}

double SimilarityMinForStrings = 0.0;

double getSimilarityMinForStrings() {
  return SimilarityMinForStrings;
}

void setSimilarityMinForStrings(double value) {
  SimilarityMinForStrings = value;
}

double SimilarityMinForEdges = 0.0;

double getSimilarityMinForEdges() {
  return SimilarityMinForEdges;
}

void setSimilarityMinForEdges(double value) {
  SimilarityMinForEdges = value;
}


base::Base* getScopeParent(const Factory* factory, NodeId nodeId, bool (*getIs) (const base::Base&)) {
  if (nodeId  ==  factory->getRoot()->getId())
    return NULL;
  
  base::Base* node = factory->getPointer(nodeId);
  if (!getIsPositioned(*node))
      return NULL;
  do {
      node = node->getParent();
      if (node && getIsMemberDeclarationSyntax(*node)) {
          structure::MemberDeclarationSyntax* memberDeclarationSyntaxNode = dynamic_cast<structure::MemberDeclarationSyntax*>(node);
          node = memberDeclarationSyntaxNode;
      }
  } while ((node != NULL) && !getIs(*node) && node != factory->getRoot());

  if (node == NULL)
      return NULL;

  if (!getIs(*node))
      return NULL;

  return node;
}} // Common 

}}}
