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

#include <set>
#include <map>
using namespace std;


namespace columbus { namespace csharp { namespace asg {
AlgorithmDeepCopy::AlgorithmDeepCopy(NodeId what, Factory& srcFact, Factory& targetFact, std::map<const base::Base*,base::Base*>& mapped_nodes) : 
  srcFact(srcFact), targetFact(targetFact), what(what), lastNode(0), mapped_nodes(mapped_nodes) {
}

AlgorithmDeepCopy::~AlgorithmDeepCopy() {}

base::Base* AlgorithmDeepCopy::clone() {
  base::Base* rv = clone(srcFact.getPointer(what));
  return rv;
}

std::map<const base::Base*, base::Base*>& AlgorithmDeepCopy::getMapping() {
  return mapped_nodes;
}

base::Base* AlgorithmDeepCopy::createNode(const base::Base* oldNode, NodeKind ndk) {
  base::Base* newNode = targetFact.createNode(ndk);
  lastNode = newNode;
  mapped_nodes[oldNode] = newNode;
  return newNode;
}

base::Base* AlgorithmDeepCopy::getMappedNode(const base::Base* oldNode) {
  if(oldNode == NULL) return NULL;
  map<const base::Base*, base::Base*>::iterator iter=mapped_nodes.find(oldNode);
  if(iter == mapped_nodes.end()) {
    base::Base* newNode = clone(oldNode);
    return newNode ;
  } else {
    return iter->second;
  }
}

base::Base* AlgorithmDeepCopy::clone(const base::Base* old) {
  base::Base* newNode;
  switch(old->getNodeKind()) {
    case ndkAliasQualifiedNameSyntax: 
      newNode = createNode(old,ndkAliasQualifiedNameSyntax);
      clone(dynamic_cast<expression::AliasQualifiedNameSyntax*>(newNode), dynamic_cast<const expression::AliasQualifiedNameSyntax*>(old));
      break;
    case ndkAnonymousMethodExpressionSyntax: 
      newNode = createNode(old,ndkAnonymousMethodExpressionSyntax);
      clone(dynamic_cast<expression::AnonymousMethodExpressionSyntax*>(newNode), dynamic_cast<const expression::AnonymousMethodExpressionSyntax*>(old));
      break;
    case ndkAnonymousObjectCreationExpressionSyntax: 
      newNode = createNode(old,ndkAnonymousObjectCreationExpressionSyntax);
      clone(dynamic_cast<expression::AnonymousObjectCreationExpressionSyntax*>(newNode), dynamic_cast<const expression::AnonymousObjectCreationExpressionSyntax*>(old));
      break;
    case ndkArrayCreationExpressionSyntax: 
      newNode = createNode(old,ndkArrayCreationExpressionSyntax);
      clone(dynamic_cast<expression::ArrayCreationExpressionSyntax*>(newNode), dynamic_cast<const expression::ArrayCreationExpressionSyntax*>(old));
      break;
    case ndkArrayTypeSyntax: 
      newNode = createNode(old,ndkArrayTypeSyntax);
      clone(dynamic_cast<expression::ArrayTypeSyntax*>(newNode), dynamic_cast<const expression::ArrayTypeSyntax*>(old));
      break;
    case ndkAssignmentExpressionSyntax: 
      newNode = createNode(old,ndkAssignmentExpressionSyntax);
      clone(dynamic_cast<expression::AssignmentExpressionSyntax*>(newNode), dynamic_cast<const expression::AssignmentExpressionSyntax*>(old));
      break;
    case ndkAwaitExpressionSyntax: 
      newNode = createNode(old,ndkAwaitExpressionSyntax);
      clone(dynamic_cast<expression::AwaitExpressionSyntax*>(newNode), dynamic_cast<const expression::AwaitExpressionSyntax*>(old));
      break;
    case ndkBaseExpressionSyntax: 
      newNode = createNode(old,ndkBaseExpressionSyntax);
      clone(dynamic_cast<expression::BaseExpressionSyntax*>(newNode), dynamic_cast<const expression::BaseExpressionSyntax*>(old));
      break;
    case ndkBinaryExpressionSyntax: 
      newNode = createNode(old,ndkBinaryExpressionSyntax);
      clone(dynamic_cast<expression::BinaryExpressionSyntax*>(newNode), dynamic_cast<const expression::BinaryExpressionSyntax*>(old));
      break;
    case ndkCastExpressionSyntax: 
      newNode = createNode(old,ndkCastExpressionSyntax);
      clone(dynamic_cast<expression::CastExpressionSyntax*>(newNode), dynamic_cast<const expression::CastExpressionSyntax*>(old));
      break;
    case ndkCheckedExpressionSyntax: 
      newNode = createNode(old,ndkCheckedExpressionSyntax);
      clone(dynamic_cast<expression::CheckedExpressionSyntax*>(newNode), dynamic_cast<const expression::CheckedExpressionSyntax*>(old));
      break;
    case ndkConditionalAccessExpressionSyntax: 
      newNode = createNode(old,ndkConditionalAccessExpressionSyntax);
      clone(dynamic_cast<expression::ConditionalAccessExpressionSyntax*>(newNode), dynamic_cast<const expression::ConditionalAccessExpressionSyntax*>(old));
      break;
    case ndkConditionalExpressionSyntax: 
      newNode = createNode(old,ndkConditionalExpressionSyntax);
      clone(dynamic_cast<expression::ConditionalExpressionSyntax*>(newNode), dynamic_cast<const expression::ConditionalExpressionSyntax*>(old));
      break;
    case ndkDeclarationExpressionSyntax: 
      newNode = createNode(old,ndkDeclarationExpressionSyntax);
      clone(dynamic_cast<expression::DeclarationExpressionSyntax*>(newNode), dynamic_cast<const expression::DeclarationExpressionSyntax*>(old));
      break;
    case ndkDefaultExpressionSyntax: 
      newNode = createNode(old,ndkDefaultExpressionSyntax);
      clone(dynamic_cast<expression::DefaultExpressionSyntax*>(newNode), dynamic_cast<const expression::DefaultExpressionSyntax*>(old));
      break;
    case ndkElementAccessExpressionSyntax: 
      newNode = createNode(old,ndkElementAccessExpressionSyntax);
      clone(dynamic_cast<expression::ElementAccessExpressionSyntax*>(newNode), dynamic_cast<const expression::ElementAccessExpressionSyntax*>(old));
      break;
    case ndkElementBindingExpressionSyntax: 
      newNode = createNode(old,ndkElementBindingExpressionSyntax);
      clone(dynamic_cast<expression::ElementBindingExpressionSyntax*>(newNode), dynamic_cast<const expression::ElementBindingExpressionSyntax*>(old));
      break;
    case ndkGenericNameSyntax: 
      newNode = createNode(old,ndkGenericNameSyntax);
      clone(dynamic_cast<expression::GenericNameSyntax*>(newNode), dynamic_cast<const expression::GenericNameSyntax*>(old));
      break;
    case ndkIdentifierNameSyntax: 
      newNode = createNode(old,ndkIdentifierNameSyntax);
      clone(dynamic_cast<expression::IdentifierNameSyntax*>(newNode), dynamic_cast<const expression::IdentifierNameSyntax*>(old));
      break;
    case ndkImplicitArrayCreationExpressionSyntax: 
      newNode = createNode(old,ndkImplicitArrayCreationExpressionSyntax);
      clone(dynamic_cast<expression::ImplicitArrayCreationExpressionSyntax*>(newNode), dynamic_cast<const expression::ImplicitArrayCreationExpressionSyntax*>(old));
      break;
    case ndkImplicitElementAccessSyntax: 
      newNode = createNode(old,ndkImplicitElementAccessSyntax);
      clone(dynamic_cast<expression::ImplicitElementAccessSyntax*>(newNode), dynamic_cast<const expression::ImplicitElementAccessSyntax*>(old));
      break;
    case ndkImplicitStackAllocArrayCreationExpressionSyntax: 
      newNode = createNode(old,ndkImplicitStackAllocArrayCreationExpressionSyntax);
      clone(dynamic_cast<expression::ImplicitStackAllocArrayCreationExpressionSyntax*>(newNode), dynamic_cast<const expression::ImplicitStackAllocArrayCreationExpressionSyntax*>(old));
      break;
    case ndkInitializerExpressionSyntax: 
      newNode = createNode(old,ndkInitializerExpressionSyntax);
      clone(dynamic_cast<expression::InitializerExpressionSyntax*>(newNode), dynamic_cast<const expression::InitializerExpressionSyntax*>(old));
      break;
    case ndkInterpolatedStringExpressionSyntax: 
      newNode = createNode(old,ndkInterpolatedStringExpressionSyntax);
      clone(dynamic_cast<expression::InterpolatedStringExpressionSyntax*>(newNode), dynamic_cast<const expression::InterpolatedStringExpressionSyntax*>(old));
      break;
    case ndkInvocationExpressionSyntax: 
      newNode = createNode(old,ndkInvocationExpressionSyntax);
      clone(dynamic_cast<expression::InvocationExpressionSyntax*>(newNode), dynamic_cast<const expression::InvocationExpressionSyntax*>(old));
      break;
    case ndkIsPatternExpressionSyntax: 
      newNode = createNode(old,ndkIsPatternExpressionSyntax);
      clone(dynamic_cast<expression::IsPatternExpressionSyntax*>(newNode), dynamic_cast<const expression::IsPatternExpressionSyntax*>(old));
      break;
    case ndkLiteralExpressionSyntax: 
      newNode = createNode(old,ndkLiteralExpressionSyntax);
      clone(dynamic_cast<expression::LiteralExpressionSyntax*>(newNode), dynamic_cast<const expression::LiteralExpressionSyntax*>(old));
      break;
    case ndkMakeRefExpressionSyntax: 
      newNode = createNode(old,ndkMakeRefExpressionSyntax);
      clone(dynamic_cast<expression::MakeRefExpressionSyntax*>(newNode), dynamic_cast<const expression::MakeRefExpressionSyntax*>(old));
      break;
    case ndkMemberAccessExpressionSyntax: 
      newNode = createNode(old,ndkMemberAccessExpressionSyntax);
      clone(dynamic_cast<expression::MemberAccessExpressionSyntax*>(newNode), dynamic_cast<const expression::MemberAccessExpressionSyntax*>(old));
      break;
    case ndkMemberBindingExpressionSyntax: 
      newNode = createNode(old,ndkMemberBindingExpressionSyntax);
      clone(dynamic_cast<expression::MemberBindingExpressionSyntax*>(newNode), dynamic_cast<const expression::MemberBindingExpressionSyntax*>(old));
      break;
    case ndkNullableTypeSyntax: 
      newNode = createNode(old,ndkNullableTypeSyntax);
      clone(dynamic_cast<expression::NullableTypeSyntax*>(newNode), dynamic_cast<const expression::NullableTypeSyntax*>(old));
      break;
    case ndkObjectCreationExpressionSyntax: 
      newNode = createNode(old,ndkObjectCreationExpressionSyntax);
      clone(dynamic_cast<expression::ObjectCreationExpressionSyntax*>(newNode), dynamic_cast<const expression::ObjectCreationExpressionSyntax*>(old));
      break;
    case ndkOmittedArraySizeExpressionSyntax: 
      newNode = createNode(old,ndkOmittedArraySizeExpressionSyntax);
      clone(dynamic_cast<expression::OmittedArraySizeExpressionSyntax*>(newNode), dynamic_cast<const expression::OmittedArraySizeExpressionSyntax*>(old));
      break;
    case ndkOmittedTypeArgumentSyntax: 
      newNode = createNode(old,ndkOmittedTypeArgumentSyntax);
      clone(dynamic_cast<expression::OmittedTypeArgumentSyntax*>(newNode), dynamic_cast<const expression::OmittedTypeArgumentSyntax*>(old));
      break;
    case ndkParenthesizedExpressionSyntax: 
      newNode = createNode(old,ndkParenthesizedExpressionSyntax);
      clone(dynamic_cast<expression::ParenthesizedExpressionSyntax*>(newNode), dynamic_cast<const expression::ParenthesizedExpressionSyntax*>(old));
      break;
    case ndkParenthesizedLambdaExpressionSyntax: 
      newNode = createNode(old,ndkParenthesizedLambdaExpressionSyntax);
      clone(dynamic_cast<expression::ParenthesizedLambdaExpressionSyntax*>(newNode), dynamic_cast<const expression::ParenthesizedLambdaExpressionSyntax*>(old));
      break;
    case ndkPointerTypeSyntax: 
      newNode = createNode(old,ndkPointerTypeSyntax);
      clone(dynamic_cast<expression::PointerTypeSyntax*>(newNode), dynamic_cast<const expression::PointerTypeSyntax*>(old));
      break;
    case ndkPostfixUnaryExpressionSyntax: 
      newNode = createNode(old,ndkPostfixUnaryExpressionSyntax);
      clone(dynamic_cast<expression::PostfixUnaryExpressionSyntax*>(newNode), dynamic_cast<const expression::PostfixUnaryExpressionSyntax*>(old));
      break;
    case ndkPredefinedTypeSyntax: 
      newNode = createNode(old,ndkPredefinedTypeSyntax);
      clone(dynamic_cast<expression::PredefinedTypeSyntax*>(newNode), dynamic_cast<const expression::PredefinedTypeSyntax*>(old));
      break;
    case ndkPrefixUnaryExpressionSyntax: 
      newNode = createNode(old,ndkPrefixUnaryExpressionSyntax);
      clone(dynamic_cast<expression::PrefixUnaryExpressionSyntax*>(newNode), dynamic_cast<const expression::PrefixUnaryExpressionSyntax*>(old));
      break;
    case ndkQualifiedNameSyntax: 
      newNode = createNode(old,ndkQualifiedNameSyntax);
      clone(dynamic_cast<expression::QualifiedNameSyntax*>(newNode), dynamic_cast<const expression::QualifiedNameSyntax*>(old));
      break;
    case ndkQueryExpressionSyntax: 
      newNode = createNode(old,ndkQueryExpressionSyntax);
      clone(dynamic_cast<expression::QueryExpressionSyntax*>(newNode), dynamic_cast<const expression::QueryExpressionSyntax*>(old));
      break;
    case ndkRangeExpressionSyntax: 
      newNode = createNode(old,ndkRangeExpressionSyntax);
      clone(dynamic_cast<expression::RangeExpressionSyntax*>(newNode), dynamic_cast<const expression::RangeExpressionSyntax*>(old));
      break;
    case ndkRefExpressionSyntax: 
      newNode = createNode(old,ndkRefExpressionSyntax);
      clone(dynamic_cast<expression::RefExpressionSyntax*>(newNode), dynamic_cast<const expression::RefExpressionSyntax*>(old));
      break;
    case ndkRefTypeExpressionSyntax: 
      newNode = createNode(old,ndkRefTypeExpressionSyntax);
      clone(dynamic_cast<expression::RefTypeExpressionSyntax*>(newNode), dynamic_cast<const expression::RefTypeExpressionSyntax*>(old));
      break;
    case ndkRefTypeSyntax: 
      newNode = createNode(old,ndkRefTypeSyntax);
      clone(dynamic_cast<expression::RefTypeSyntax*>(newNode), dynamic_cast<const expression::RefTypeSyntax*>(old));
      break;
    case ndkRefValueExpressionSyntax: 
      newNode = createNode(old,ndkRefValueExpressionSyntax);
      clone(dynamic_cast<expression::RefValueExpressionSyntax*>(newNode), dynamic_cast<const expression::RefValueExpressionSyntax*>(old));
      break;
    case ndkSimpleLambdaExpressionSyntax: 
      newNode = createNode(old,ndkSimpleLambdaExpressionSyntax);
      clone(dynamic_cast<expression::SimpleLambdaExpressionSyntax*>(newNode), dynamic_cast<const expression::SimpleLambdaExpressionSyntax*>(old));
      break;
    case ndkSizeOfExpressionSyntax: 
      newNode = createNode(old,ndkSizeOfExpressionSyntax);
      clone(dynamic_cast<expression::SizeOfExpressionSyntax*>(newNode), dynamic_cast<const expression::SizeOfExpressionSyntax*>(old));
      break;
    case ndkStackAllocArrayCreationExpressionSyntax: 
      newNode = createNode(old,ndkStackAllocArrayCreationExpressionSyntax);
      clone(dynamic_cast<expression::StackAllocArrayCreationExpressionSyntax*>(newNode), dynamic_cast<const expression::StackAllocArrayCreationExpressionSyntax*>(old));
      break;
    case ndkSwitchExpressionSyntax: 
      newNode = createNode(old,ndkSwitchExpressionSyntax);
      clone(dynamic_cast<expression::SwitchExpressionSyntax*>(newNode), dynamic_cast<const expression::SwitchExpressionSyntax*>(old));
      break;
    case ndkThisExpressionSyntax: 
      newNode = createNode(old,ndkThisExpressionSyntax);
      clone(dynamic_cast<expression::ThisExpressionSyntax*>(newNode), dynamic_cast<const expression::ThisExpressionSyntax*>(old));
      break;
    case ndkThrowExpressionSyntax: 
      newNode = createNode(old,ndkThrowExpressionSyntax);
      clone(dynamic_cast<expression::ThrowExpressionSyntax*>(newNode), dynamic_cast<const expression::ThrowExpressionSyntax*>(old));
      break;
    case ndkTupleExpressionSyntax: 
      newNode = createNode(old,ndkTupleExpressionSyntax);
      clone(dynamic_cast<expression::TupleExpressionSyntax*>(newNode), dynamic_cast<const expression::TupleExpressionSyntax*>(old));
      break;
    case ndkTupleTypeSyntax: 
      newNode = createNode(old,ndkTupleTypeSyntax);
      clone(dynamic_cast<expression::TupleTypeSyntax*>(newNode), dynamic_cast<const expression::TupleTypeSyntax*>(old));
      break;
    case ndkTypeOfExpressionSyntax: 
      newNode = createNode(old,ndkTypeOfExpressionSyntax);
      clone(dynamic_cast<expression::TypeOfExpressionSyntax*>(newNode), dynamic_cast<const expression::TypeOfExpressionSyntax*>(old));
      break;
    case ndkBlockSyntax: 
      newNode = createNode(old,ndkBlockSyntax);
      clone(dynamic_cast<statement::BlockSyntax*>(newNode), dynamic_cast<const statement::BlockSyntax*>(old));
      break;
    case ndkBreakStatementSyntax: 
      newNode = createNode(old,ndkBreakStatementSyntax);
      clone(dynamic_cast<statement::BreakStatementSyntax*>(newNode), dynamic_cast<const statement::BreakStatementSyntax*>(old));
      break;
    case ndkCheckedStatementSyntax: 
      newNode = createNode(old,ndkCheckedStatementSyntax);
      clone(dynamic_cast<statement::CheckedStatementSyntax*>(newNode), dynamic_cast<const statement::CheckedStatementSyntax*>(old));
      break;
    case ndkContinueStatementSyntax: 
      newNode = createNode(old,ndkContinueStatementSyntax);
      clone(dynamic_cast<statement::ContinueStatementSyntax*>(newNode), dynamic_cast<const statement::ContinueStatementSyntax*>(old));
      break;
    case ndkDoStatementSyntax: 
      newNode = createNode(old,ndkDoStatementSyntax);
      clone(dynamic_cast<statement::DoStatementSyntax*>(newNode), dynamic_cast<const statement::DoStatementSyntax*>(old));
      break;
    case ndkEmptyStatementSyntax: 
      newNode = createNode(old,ndkEmptyStatementSyntax);
      clone(dynamic_cast<statement::EmptyStatementSyntax*>(newNode), dynamic_cast<const statement::EmptyStatementSyntax*>(old));
      break;
    case ndkExpressionStatementSyntax: 
      newNode = createNode(old,ndkExpressionStatementSyntax);
      clone(dynamic_cast<statement::ExpressionStatementSyntax*>(newNode), dynamic_cast<const statement::ExpressionStatementSyntax*>(old));
      break;
    case ndkFixedStatementSyntax: 
      newNode = createNode(old,ndkFixedStatementSyntax);
      clone(dynamic_cast<statement::FixedStatementSyntax*>(newNode), dynamic_cast<const statement::FixedStatementSyntax*>(old));
      break;
    case ndkForEachStatementSyntax: 
      newNode = createNode(old,ndkForEachStatementSyntax);
      clone(dynamic_cast<statement::ForEachStatementSyntax*>(newNode), dynamic_cast<const statement::ForEachStatementSyntax*>(old));
      break;
    case ndkForEachVariableStatementSyntax: 
      newNode = createNode(old,ndkForEachVariableStatementSyntax);
      clone(dynamic_cast<statement::ForEachVariableStatementSyntax*>(newNode), dynamic_cast<const statement::ForEachVariableStatementSyntax*>(old));
      break;
    case ndkForStatementSyntax: 
      newNode = createNode(old,ndkForStatementSyntax);
      clone(dynamic_cast<statement::ForStatementSyntax*>(newNode), dynamic_cast<const statement::ForStatementSyntax*>(old));
      break;
    case ndkGotoStatementSyntax: 
      newNode = createNode(old,ndkGotoStatementSyntax);
      clone(dynamic_cast<statement::GotoStatementSyntax*>(newNode), dynamic_cast<const statement::GotoStatementSyntax*>(old));
      break;
    case ndkIfStatementSyntax: 
      newNode = createNode(old,ndkIfStatementSyntax);
      clone(dynamic_cast<statement::IfStatementSyntax*>(newNode), dynamic_cast<const statement::IfStatementSyntax*>(old));
      break;
    case ndkLabeledStatementSyntax: 
      newNode = createNode(old,ndkLabeledStatementSyntax);
      clone(dynamic_cast<statement::LabeledStatementSyntax*>(newNode), dynamic_cast<const statement::LabeledStatementSyntax*>(old));
      break;
    case ndkLocalDeclarationStatementSyntax: 
      newNode = createNode(old,ndkLocalDeclarationStatementSyntax);
      clone(dynamic_cast<statement::LocalDeclarationStatementSyntax*>(newNode), dynamic_cast<const statement::LocalDeclarationStatementSyntax*>(old));
      break;
    case ndkLocalFunctionStatementSyntax: 
      newNode = createNode(old,ndkLocalFunctionStatementSyntax);
      clone(dynamic_cast<statement::LocalFunctionStatementSyntax*>(newNode), dynamic_cast<const statement::LocalFunctionStatementSyntax*>(old));
      break;
    case ndkLockStatementSyntax: 
      newNode = createNode(old,ndkLockStatementSyntax);
      clone(dynamic_cast<statement::LockStatementSyntax*>(newNode), dynamic_cast<const statement::LockStatementSyntax*>(old));
      break;
    case ndkReturnStatementSyntax: 
      newNode = createNode(old,ndkReturnStatementSyntax);
      clone(dynamic_cast<statement::ReturnStatementSyntax*>(newNode), dynamic_cast<const statement::ReturnStatementSyntax*>(old));
      break;
    case ndkSwitchStatementSyntax: 
      newNode = createNode(old,ndkSwitchStatementSyntax);
      clone(dynamic_cast<statement::SwitchStatementSyntax*>(newNode), dynamic_cast<const statement::SwitchStatementSyntax*>(old));
      break;
    case ndkThrowStatementSyntax: 
      newNode = createNode(old,ndkThrowStatementSyntax);
      clone(dynamic_cast<statement::ThrowStatementSyntax*>(newNode), dynamic_cast<const statement::ThrowStatementSyntax*>(old));
      break;
    case ndkTryStatementSyntax: 
      newNode = createNode(old,ndkTryStatementSyntax);
      clone(dynamic_cast<statement::TryStatementSyntax*>(newNode), dynamic_cast<const statement::TryStatementSyntax*>(old));
      break;
    case ndkUnsafeStatementSyntax: 
      newNode = createNode(old,ndkUnsafeStatementSyntax);
      clone(dynamic_cast<statement::UnsafeStatementSyntax*>(newNode), dynamic_cast<const statement::UnsafeStatementSyntax*>(old));
      break;
    case ndkUsingStatementSyntax: 
      newNode = createNode(old,ndkUsingStatementSyntax);
      clone(dynamic_cast<statement::UsingStatementSyntax*>(newNode), dynamic_cast<const statement::UsingStatementSyntax*>(old));
      break;
    case ndkWhileStatementSyntax: 
      newNode = createNode(old,ndkWhileStatementSyntax);
      clone(dynamic_cast<statement::WhileStatementSyntax*>(newNode), dynamic_cast<const statement::WhileStatementSyntax*>(old));
      break;
    case ndkYieldStatementSyntax: 
      newNode = createNode(old,ndkYieldStatementSyntax);
      clone(dynamic_cast<statement::YieldStatementSyntax*>(newNode), dynamic_cast<const statement::YieldStatementSyntax*>(old));
      break;
    case ndkAccessorDeclarationSyntax: 
      newNode = createNode(old,ndkAccessorDeclarationSyntax);
      clone(dynamic_cast<structure::AccessorDeclarationSyntax*>(newNode), dynamic_cast<const structure::AccessorDeclarationSyntax*>(old));
      break;
    case ndkAccessorListSyntax: 
      newNode = createNode(old,ndkAccessorListSyntax);
      clone(dynamic_cast<structure::AccessorListSyntax*>(newNode), dynamic_cast<const structure::AccessorListSyntax*>(old));
      break;
    case ndkAnonymousObjectMemberDeclaratorSyntax: 
      newNode = createNode(old,ndkAnonymousObjectMemberDeclaratorSyntax);
      clone(dynamic_cast<structure::AnonymousObjectMemberDeclaratorSyntax*>(newNode), dynamic_cast<const structure::AnonymousObjectMemberDeclaratorSyntax*>(old));
      break;
    case ndkArgumentListSyntax: 
      newNode = createNode(old,ndkArgumentListSyntax);
      clone(dynamic_cast<structure::ArgumentListSyntax*>(newNode), dynamic_cast<const structure::ArgumentListSyntax*>(old));
      break;
    case ndkArgumentSyntax: 
      newNode = createNode(old,ndkArgumentSyntax);
      clone(dynamic_cast<structure::ArgumentSyntax*>(newNode), dynamic_cast<const structure::ArgumentSyntax*>(old));
      break;
    case ndkArrayRankSpecifierSyntax: 
      newNode = createNode(old,ndkArrayRankSpecifierSyntax);
      clone(dynamic_cast<structure::ArrayRankSpecifierSyntax*>(newNode), dynamic_cast<const structure::ArrayRankSpecifierSyntax*>(old));
      break;
    case ndkArrowExpressionClauseSyntax: 
      newNode = createNode(old,ndkArrowExpressionClauseSyntax);
      clone(dynamic_cast<structure::ArrowExpressionClauseSyntax*>(newNode), dynamic_cast<const structure::ArrowExpressionClauseSyntax*>(old));
      break;
    case ndkAttributeArgumentListSyntax: 
      newNode = createNode(old,ndkAttributeArgumentListSyntax);
      clone(dynamic_cast<structure::AttributeArgumentListSyntax*>(newNode), dynamic_cast<const structure::AttributeArgumentListSyntax*>(old));
      break;
    case ndkAttributeArgumentSyntax: 
      newNode = createNode(old,ndkAttributeArgumentSyntax);
      clone(dynamic_cast<structure::AttributeArgumentSyntax*>(newNode), dynamic_cast<const structure::AttributeArgumentSyntax*>(old));
      break;
    case ndkAttributeListSyntax: 
      newNode = createNode(old,ndkAttributeListSyntax);
      clone(dynamic_cast<structure::AttributeListSyntax*>(newNode), dynamic_cast<const structure::AttributeListSyntax*>(old));
      break;
    case ndkAttributeSyntax: 
      newNode = createNode(old,ndkAttributeSyntax);
      clone(dynamic_cast<structure::AttributeSyntax*>(newNode), dynamic_cast<const structure::AttributeSyntax*>(old));
      break;
    case ndkAttributeTargetSpecifierSyntax: 
      newNode = createNode(old,ndkAttributeTargetSpecifierSyntax);
      clone(dynamic_cast<structure::AttributeTargetSpecifierSyntax*>(newNode), dynamic_cast<const structure::AttributeTargetSpecifierSyntax*>(old));
      break;
    case ndkBaseListSyntax: 
      newNode = createNode(old,ndkBaseListSyntax);
      clone(dynamic_cast<structure::BaseListSyntax*>(newNode), dynamic_cast<const structure::BaseListSyntax*>(old));
      break;
    case ndkBracketedArgumentListSyntax: 
      newNode = createNode(old,ndkBracketedArgumentListSyntax);
      clone(dynamic_cast<structure::BracketedArgumentListSyntax*>(newNode), dynamic_cast<const structure::BracketedArgumentListSyntax*>(old));
      break;
    case ndkBracketedParameterListSyntax: 
      newNode = createNode(old,ndkBracketedParameterListSyntax);
      clone(dynamic_cast<structure::BracketedParameterListSyntax*>(newNode), dynamic_cast<const structure::BracketedParameterListSyntax*>(old));
      break;
    case ndkCasePatternSwitchLabelSyntax: 
      newNode = createNode(old,ndkCasePatternSwitchLabelSyntax);
      clone(dynamic_cast<structure::CasePatternSwitchLabelSyntax*>(newNode), dynamic_cast<const structure::CasePatternSwitchLabelSyntax*>(old));
      break;
    case ndkCaseSwitchLabelSyntax: 
      newNode = createNode(old,ndkCaseSwitchLabelSyntax);
      clone(dynamic_cast<structure::CaseSwitchLabelSyntax*>(newNode), dynamic_cast<const structure::CaseSwitchLabelSyntax*>(old));
      break;
    case ndkCatchClauseSyntax: 
      newNode = createNode(old,ndkCatchClauseSyntax);
      clone(dynamic_cast<structure::CatchClauseSyntax*>(newNode), dynamic_cast<const structure::CatchClauseSyntax*>(old));
      break;
    case ndkCatchDeclarationSyntax: 
      newNode = createNode(old,ndkCatchDeclarationSyntax);
      clone(dynamic_cast<structure::CatchDeclarationSyntax*>(newNode), dynamic_cast<const structure::CatchDeclarationSyntax*>(old));
      break;
    case ndkCatchFilterClauseSyntax: 
      newNode = createNode(old,ndkCatchFilterClauseSyntax);
      clone(dynamic_cast<structure::CatchFilterClauseSyntax*>(newNode), dynamic_cast<const structure::CatchFilterClauseSyntax*>(old));
      break;
    case ndkClassDeclarationSyntax: 
      newNode = createNode(old,ndkClassDeclarationSyntax);
      clone(dynamic_cast<structure::ClassDeclarationSyntax*>(newNode), dynamic_cast<const structure::ClassDeclarationSyntax*>(old));
      break;
    case ndkClassOrStructConstraintSyntax: 
      newNode = createNode(old,ndkClassOrStructConstraintSyntax);
      clone(dynamic_cast<structure::ClassOrStructConstraintSyntax*>(newNode), dynamic_cast<const structure::ClassOrStructConstraintSyntax*>(old));
      break;
    case ndkCompilationUnitSyntax: 
      newNode = createNode(old,ndkCompilationUnitSyntax);
      clone(dynamic_cast<structure::CompilationUnitSyntax*>(newNode), dynamic_cast<const structure::CompilationUnitSyntax*>(old));
      break;
    case ndkConstantPatternSyntax: 
      newNode = createNode(old,ndkConstantPatternSyntax);
      clone(dynamic_cast<structure::ConstantPatternSyntax*>(newNode), dynamic_cast<const structure::ConstantPatternSyntax*>(old));
      break;
    case ndkConstructorConstraintSyntax: 
      newNode = createNode(old,ndkConstructorConstraintSyntax);
      clone(dynamic_cast<structure::ConstructorConstraintSyntax*>(newNode), dynamic_cast<const structure::ConstructorConstraintSyntax*>(old));
      break;
    case ndkConstructorDeclarationSyntax: 
      newNode = createNode(old,ndkConstructorDeclarationSyntax);
      clone(dynamic_cast<structure::ConstructorDeclarationSyntax*>(newNode), dynamic_cast<const structure::ConstructorDeclarationSyntax*>(old));
      break;
    case ndkConstructorInitializerSyntax: 
      newNode = createNode(old,ndkConstructorInitializerSyntax);
      clone(dynamic_cast<structure::ConstructorInitializerSyntax*>(newNode), dynamic_cast<const structure::ConstructorInitializerSyntax*>(old));
      break;
    case ndkConversionOperatorDeclarationSyntax: 
      newNode = createNode(old,ndkConversionOperatorDeclarationSyntax);
      clone(dynamic_cast<structure::ConversionOperatorDeclarationSyntax*>(newNode), dynamic_cast<const structure::ConversionOperatorDeclarationSyntax*>(old));
      break;
    case ndkConversionOperatorMemberCrefSyntax: 
      newNode = createNode(old,ndkConversionOperatorMemberCrefSyntax);
      clone(dynamic_cast<structure::ConversionOperatorMemberCrefSyntax*>(newNode), dynamic_cast<const structure::ConversionOperatorMemberCrefSyntax*>(old));
      break;
    case ndkCrefBracketedParameterListSyntax: 
      newNode = createNode(old,ndkCrefBracketedParameterListSyntax);
      clone(dynamic_cast<structure::CrefBracketedParameterListSyntax*>(newNode), dynamic_cast<const structure::CrefBracketedParameterListSyntax*>(old));
      break;
    case ndkCrefParameterListSyntax: 
      newNode = createNode(old,ndkCrefParameterListSyntax);
      clone(dynamic_cast<structure::CrefParameterListSyntax*>(newNode), dynamic_cast<const structure::CrefParameterListSyntax*>(old));
      break;
    case ndkCrefParameterSyntax: 
      newNode = createNode(old,ndkCrefParameterSyntax);
      clone(dynamic_cast<structure::CrefParameterSyntax*>(newNode), dynamic_cast<const structure::CrefParameterSyntax*>(old));
      break;
    case ndkDeclarationPatternSyntax: 
      newNode = createNode(old,ndkDeclarationPatternSyntax);
      clone(dynamic_cast<structure::DeclarationPatternSyntax*>(newNode), dynamic_cast<const structure::DeclarationPatternSyntax*>(old));
      break;
    case ndkDefaultSwitchLabelSyntax: 
      newNode = createNode(old,ndkDefaultSwitchLabelSyntax);
      clone(dynamic_cast<structure::DefaultSwitchLabelSyntax*>(newNode), dynamic_cast<const structure::DefaultSwitchLabelSyntax*>(old));
      break;
    case ndkDelegateDeclarationSyntax: 
      newNode = createNode(old,ndkDelegateDeclarationSyntax);
      clone(dynamic_cast<structure::DelegateDeclarationSyntax*>(newNode), dynamic_cast<const structure::DelegateDeclarationSyntax*>(old));
      break;
    case ndkDestructorDeclarationSyntax: 
      newNode = createNode(old,ndkDestructorDeclarationSyntax);
      clone(dynamic_cast<structure::DestructorDeclarationSyntax*>(newNode), dynamic_cast<const structure::DestructorDeclarationSyntax*>(old));
      break;
    case ndkDiscardDesignationSyntax: 
      newNode = createNode(old,ndkDiscardDesignationSyntax);
      clone(dynamic_cast<structure::DiscardDesignationSyntax*>(newNode), dynamic_cast<const structure::DiscardDesignationSyntax*>(old));
      break;
    case ndkDiscardPatternSyntax: 
      newNode = createNode(old,ndkDiscardPatternSyntax);
      clone(dynamic_cast<structure::DiscardPatternSyntax*>(newNode), dynamic_cast<const structure::DiscardPatternSyntax*>(old));
      break;
    case ndkElseClauseSyntax: 
      newNode = createNode(old,ndkElseClauseSyntax);
      clone(dynamic_cast<structure::ElseClauseSyntax*>(newNode), dynamic_cast<const structure::ElseClauseSyntax*>(old));
      break;
    case ndkEnumDeclarationSyntax: 
      newNode = createNode(old,ndkEnumDeclarationSyntax);
      clone(dynamic_cast<structure::EnumDeclarationSyntax*>(newNode), dynamic_cast<const structure::EnumDeclarationSyntax*>(old));
      break;
    case ndkEnumMemberDeclarationSyntax: 
      newNode = createNode(old,ndkEnumMemberDeclarationSyntax);
      clone(dynamic_cast<structure::EnumMemberDeclarationSyntax*>(newNode), dynamic_cast<const structure::EnumMemberDeclarationSyntax*>(old));
      break;
    case ndkEqualsValueClauseSyntax: 
      newNode = createNode(old,ndkEqualsValueClauseSyntax);
      clone(dynamic_cast<structure::EqualsValueClauseSyntax*>(newNode), dynamic_cast<const structure::EqualsValueClauseSyntax*>(old));
      break;
    case ndkEventDeclarationSyntax: 
      newNode = createNode(old,ndkEventDeclarationSyntax);
      clone(dynamic_cast<structure::EventDeclarationSyntax*>(newNode), dynamic_cast<const structure::EventDeclarationSyntax*>(old));
      break;
    case ndkEventFieldDeclarationSyntax: 
      newNode = createNode(old,ndkEventFieldDeclarationSyntax);
      clone(dynamic_cast<structure::EventFieldDeclarationSyntax*>(newNode), dynamic_cast<const structure::EventFieldDeclarationSyntax*>(old));
      break;
    case ndkExplicitInterfaceSpecifierSyntax: 
      newNode = createNode(old,ndkExplicitInterfaceSpecifierSyntax);
      clone(dynamic_cast<structure::ExplicitInterfaceSpecifierSyntax*>(newNode), dynamic_cast<const structure::ExplicitInterfaceSpecifierSyntax*>(old));
      break;
    case ndkExternAliasDirectiveSyntax: 
      newNode = createNode(old,ndkExternAliasDirectiveSyntax);
      clone(dynamic_cast<structure::ExternAliasDirectiveSyntax*>(newNode), dynamic_cast<const structure::ExternAliasDirectiveSyntax*>(old));
      break;
    case ndkFieldDeclarationSyntax: 
      newNode = createNode(old,ndkFieldDeclarationSyntax);
      clone(dynamic_cast<structure::FieldDeclarationSyntax*>(newNode), dynamic_cast<const structure::FieldDeclarationSyntax*>(old));
      break;
    case ndkFinallyClauseSyntax: 
      newNode = createNode(old,ndkFinallyClauseSyntax);
      clone(dynamic_cast<structure::FinallyClauseSyntax*>(newNode), dynamic_cast<const structure::FinallyClauseSyntax*>(old));
      break;
    case ndkFromClauseSyntax: 
      newNode = createNode(old,ndkFromClauseSyntax);
      clone(dynamic_cast<structure::FromClauseSyntax*>(newNode), dynamic_cast<const structure::FromClauseSyntax*>(old));
      break;
    case ndkGlobalStatementSyntax: 
      newNode = createNode(old,ndkGlobalStatementSyntax);
      clone(dynamic_cast<structure::GlobalStatementSyntax*>(newNode), dynamic_cast<const structure::GlobalStatementSyntax*>(old));
      break;
    case ndkGroupClauseSyntax: 
      newNode = createNode(old,ndkGroupClauseSyntax);
      clone(dynamic_cast<structure::GroupClauseSyntax*>(newNode), dynamic_cast<const structure::GroupClauseSyntax*>(old));
      break;
    case ndkIncompleteMemberSyntax: 
      newNode = createNode(old,ndkIncompleteMemberSyntax);
      clone(dynamic_cast<structure::IncompleteMemberSyntax*>(newNode), dynamic_cast<const structure::IncompleteMemberSyntax*>(old));
      break;
    case ndkIndexerDeclarationSyntax: 
      newNode = createNode(old,ndkIndexerDeclarationSyntax);
      clone(dynamic_cast<structure::IndexerDeclarationSyntax*>(newNode), dynamic_cast<const structure::IndexerDeclarationSyntax*>(old));
      break;
    case ndkIndexerMemberCrefSyntax: 
      newNode = createNode(old,ndkIndexerMemberCrefSyntax);
      clone(dynamic_cast<structure::IndexerMemberCrefSyntax*>(newNode), dynamic_cast<const structure::IndexerMemberCrefSyntax*>(old));
      break;
    case ndkInterfaceDeclarationSyntax: 
      newNode = createNode(old,ndkInterfaceDeclarationSyntax);
      clone(dynamic_cast<structure::InterfaceDeclarationSyntax*>(newNode), dynamic_cast<const structure::InterfaceDeclarationSyntax*>(old));
      break;
    case ndkInterpolatedStringTextSyntax: 
      newNode = createNode(old,ndkInterpolatedStringTextSyntax);
      clone(dynamic_cast<structure::InterpolatedStringTextSyntax*>(newNode), dynamic_cast<const structure::InterpolatedStringTextSyntax*>(old));
      break;
    case ndkInterpolationAlignmentClauseSyntax: 
      newNode = createNode(old,ndkInterpolationAlignmentClauseSyntax);
      clone(dynamic_cast<structure::InterpolationAlignmentClauseSyntax*>(newNode), dynamic_cast<const structure::InterpolationAlignmentClauseSyntax*>(old));
      break;
    case ndkInterpolationFormatClauseSyntax: 
      newNode = createNode(old,ndkInterpolationFormatClauseSyntax);
      clone(dynamic_cast<structure::InterpolationFormatClauseSyntax*>(newNode), dynamic_cast<const structure::InterpolationFormatClauseSyntax*>(old));
      break;
    case ndkInterpolationSyntax: 
      newNode = createNode(old,ndkInterpolationSyntax);
      clone(dynamic_cast<structure::InterpolationSyntax*>(newNode), dynamic_cast<const structure::InterpolationSyntax*>(old));
      break;
    case ndkJoinClauseSyntax: 
      newNode = createNode(old,ndkJoinClauseSyntax);
      clone(dynamic_cast<structure::JoinClauseSyntax*>(newNode), dynamic_cast<const structure::JoinClauseSyntax*>(old));
      break;
    case ndkJoinIntoClauseSyntax: 
      newNode = createNode(old,ndkJoinIntoClauseSyntax);
      clone(dynamic_cast<structure::JoinIntoClauseSyntax*>(newNode), dynamic_cast<const structure::JoinIntoClauseSyntax*>(old));
      break;
    case ndkLetClauseSyntax: 
      newNode = createNode(old,ndkLetClauseSyntax);
      clone(dynamic_cast<structure::LetClauseSyntax*>(newNode), dynamic_cast<const structure::LetClauseSyntax*>(old));
      break;
    case ndkMethodDeclarationSyntax: 
      newNode = createNode(old,ndkMethodDeclarationSyntax);
      clone(dynamic_cast<structure::MethodDeclarationSyntax*>(newNode), dynamic_cast<const structure::MethodDeclarationSyntax*>(old));
      break;
    case ndkNameColonSyntax: 
      newNode = createNode(old,ndkNameColonSyntax);
      clone(dynamic_cast<structure::NameColonSyntax*>(newNode), dynamic_cast<const structure::NameColonSyntax*>(old));
      break;
    case ndkNameEqualsSyntax: 
      newNode = createNode(old,ndkNameEqualsSyntax);
      clone(dynamic_cast<structure::NameEqualsSyntax*>(newNode), dynamic_cast<const structure::NameEqualsSyntax*>(old));
      break;
    case ndkNameMemberCrefSyntax: 
      newNode = createNode(old,ndkNameMemberCrefSyntax);
      clone(dynamic_cast<structure::NameMemberCrefSyntax*>(newNode), dynamic_cast<const structure::NameMemberCrefSyntax*>(old));
      break;
    case ndkNamespaceDeclarationSyntax: 
      newNode = createNode(old,ndkNamespaceDeclarationSyntax);
      clone(dynamic_cast<structure::NamespaceDeclarationSyntax*>(newNode), dynamic_cast<const structure::NamespaceDeclarationSyntax*>(old));
      break;
    case ndkOperatorDeclarationSyntax: 
      newNode = createNode(old,ndkOperatorDeclarationSyntax);
      clone(dynamic_cast<structure::OperatorDeclarationSyntax*>(newNode), dynamic_cast<const structure::OperatorDeclarationSyntax*>(old));
      break;
    case ndkOperatorMemberCrefSyntax: 
      newNode = createNode(old,ndkOperatorMemberCrefSyntax);
      clone(dynamic_cast<structure::OperatorMemberCrefSyntax*>(newNode), dynamic_cast<const structure::OperatorMemberCrefSyntax*>(old));
      break;
    case ndkOrderByClauseSyntax: 
      newNode = createNode(old,ndkOrderByClauseSyntax);
      clone(dynamic_cast<structure::OrderByClauseSyntax*>(newNode), dynamic_cast<const structure::OrderByClauseSyntax*>(old));
      break;
    case ndkOrderingSyntax: 
      newNode = createNode(old,ndkOrderingSyntax);
      clone(dynamic_cast<structure::OrderingSyntax*>(newNode), dynamic_cast<const structure::OrderingSyntax*>(old));
      break;
    case ndkParameterListSyntax: 
      newNode = createNode(old,ndkParameterListSyntax);
      clone(dynamic_cast<structure::ParameterListSyntax*>(newNode), dynamic_cast<const structure::ParameterListSyntax*>(old));
      break;
    case ndkParameterSyntax: 
      newNode = createNode(old,ndkParameterSyntax);
      clone(dynamic_cast<structure::ParameterSyntax*>(newNode), dynamic_cast<const structure::ParameterSyntax*>(old));
      break;
    case ndkParenthesizedVariableDesignationSyntax: 
      newNode = createNode(old,ndkParenthesizedVariableDesignationSyntax);
      clone(dynamic_cast<structure::ParenthesizedVariableDesignationSyntax*>(newNode), dynamic_cast<const structure::ParenthesizedVariableDesignationSyntax*>(old));
      break;
    case ndkPositionalPatternClauseSyntax: 
      newNode = createNode(old,ndkPositionalPatternClauseSyntax);
      clone(dynamic_cast<structure::PositionalPatternClauseSyntax*>(newNode), dynamic_cast<const structure::PositionalPatternClauseSyntax*>(old));
      break;
    case ndkPropertyDeclarationSyntax: 
      newNode = createNode(old,ndkPropertyDeclarationSyntax);
      clone(dynamic_cast<structure::PropertyDeclarationSyntax*>(newNode), dynamic_cast<const structure::PropertyDeclarationSyntax*>(old));
      break;
    case ndkPropertyPatternClauseSyntax: 
      newNode = createNode(old,ndkPropertyPatternClauseSyntax);
      clone(dynamic_cast<structure::PropertyPatternClauseSyntax*>(newNode), dynamic_cast<const structure::PropertyPatternClauseSyntax*>(old));
      break;
    case ndkQualifiedCrefSyntax: 
      newNode = createNode(old,ndkQualifiedCrefSyntax);
      clone(dynamic_cast<structure::QualifiedCrefSyntax*>(newNode), dynamic_cast<const structure::QualifiedCrefSyntax*>(old));
      break;
    case ndkQueryBodySyntax: 
      newNode = createNode(old,ndkQueryBodySyntax);
      clone(dynamic_cast<structure::QueryBodySyntax*>(newNode), dynamic_cast<const structure::QueryBodySyntax*>(old));
      break;
    case ndkQueryContinuationSyntax: 
      newNode = createNode(old,ndkQueryContinuationSyntax);
      clone(dynamic_cast<structure::QueryContinuationSyntax*>(newNode), dynamic_cast<const structure::QueryContinuationSyntax*>(old));
      break;
    case ndkRecursivePatternSyntax: 
      newNode = createNode(old,ndkRecursivePatternSyntax);
      clone(dynamic_cast<structure::RecursivePatternSyntax*>(newNode), dynamic_cast<const structure::RecursivePatternSyntax*>(old));
      break;
    case ndkSelectClauseSyntax: 
      newNode = createNode(old,ndkSelectClauseSyntax);
      clone(dynamic_cast<structure::SelectClauseSyntax*>(newNode), dynamic_cast<const structure::SelectClauseSyntax*>(old));
      break;
    case ndkSimpleBaseTypeSyntax: 
      newNode = createNode(old,ndkSimpleBaseTypeSyntax);
      clone(dynamic_cast<structure::SimpleBaseTypeSyntax*>(newNode), dynamic_cast<const structure::SimpleBaseTypeSyntax*>(old));
      break;
    case ndkSingleVariableDesignationSyntax: 
      newNode = createNode(old,ndkSingleVariableDesignationSyntax);
      clone(dynamic_cast<structure::SingleVariableDesignationSyntax*>(newNode), dynamic_cast<const structure::SingleVariableDesignationSyntax*>(old));
      break;
    case ndkStructDeclarationSyntax: 
      newNode = createNode(old,ndkStructDeclarationSyntax);
      clone(dynamic_cast<structure::StructDeclarationSyntax*>(newNode), dynamic_cast<const structure::StructDeclarationSyntax*>(old));
      break;
    case ndkSubpatternSyntax: 
      newNode = createNode(old,ndkSubpatternSyntax);
      clone(dynamic_cast<structure::SubpatternSyntax*>(newNode), dynamic_cast<const structure::SubpatternSyntax*>(old));
      break;
    case ndkSwitchExpressionArmSyntax: 
      newNode = createNode(old,ndkSwitchExpressionArmSyntax);
      clone(dynamic_cast<structure::SwitchExpressionArmSyntax*>(newNode), dynamic_cast<const structure::SwitchExpressionArmSyntax*>(old));
      break;
    case ndkSwitchSectionSyntax: 
      newNode = createNode(old,ndkSwitchSectionSyntax);
      clone(dynamic_cast<structure::SwitchSectionSyntax*>(newNode), dynamic_cast<const structure::SwitchSectionSyntax*>(old));
      break;
    case ndkSyntaxToken: 
      newNode = createNode(old,ndkSyntaxToken);
      clone(dynamic_cast<structure::SyntaxToken*>(newNode), dynamic_cast<const structure::SyntaxToken*>(old));
      break;
    case ndkTupleElementSyntax: 
      newNode = createNode(old,ndkTupleElementSyntax);
      clone(dynamic_cast<structure::TupleElementSyntax*>(newNode), dynamic_cast<const structure::TupleElementSyntax*>(old));
      break;
    case ndkTypeArgumentListSyntax: 
      newNode = createNode(old,ndkTypeArgumentListSyntax);
      clone(dynamic_cast<structure::TypeArgumentListSyntax*>(newNode), dynamic_cast<const structure::TypeArgumentListSyntax*>(old));
      break;
    case ndkTypeConstraintSyntax: 
      newNode = createNode(old,ndkTypeConstraintSyntax);
      clone(dynamic_cast<structure::TypeConstraintSyntax*>(newNode), dynamic_cast<const structure::TypeConstraintSyntax*>(old));
      break;
    case ndkTypeCrefSyntax: 
      newNode = createNode(old,ndkTypeCrefSyntax);
      clone(dynamic_cast<structure::TypeCrefSyntax*>(newNode), dynamic_cast<const structure::TypeCrefSyntax*>(old));
      break;
    case ndkTypeParameterConstraintClauseSyntax: 
      newNode = createNode(old,ndkTypeParameterConstraintClauseSyntax);
      clone(dynamic_cast<structure::TypeParameterConstraintClauseSyntax*>(newNode), dynamic_cast<const structure::TypeParameterConstraintClauseSyntax*>(old));
      break;
    case ndkTypeParameterListSyntax: 
      newNode = createNode(old,ndkTypeParameterListSyntax);
      clone(dynamic_cast<structure::TypeParameterListSyntax*>(newNode), dynamic_cast<const structure::TypeParameterListSyntax*>(old));
      break;
    case ndkTypeParameterSyntax: 
      newNode = createNode(old,ndkTypeParameterSyntax);
      clone(dynamic_cast<structure::TypeParameterSyntax*>(newNode), dynamic_cast<const structure::TypeParameterSyntax*>(old));
      break;
    case ndkUsingDirectiveSyntax: 
      newNode = createNode(old,ndkUsingDirectiveSyntax);
      clone(dynamic_cast<structure::UsingDirectiveSyntax*>(newNode), dynamic_cast<const structure::UsingDirectiveSyntax*>(old));
      break;
    case ndkVarPatternSyntax: 
      newNode = createNode(old,ndkVarPatternSyntax);
      clone(dynamic_cast<structure::VarPatternSyntax*>(newNode), dynamic_cast<const structure::VarPatternSyntax*>(old));
      break;
    case ndkVariableDeclarationSyntax: 
      newNode = createNode(old,ndkVariableDeclarationSyntax);
      clone(dynamic_cast<structure::VariableDeclarationSyntax*>(newNode), dynamic_cast<const structure::VariableDeclarationSyntax*>(old));
      break;
    case ndkVariableDeclaratorSyntax: 
      newNode = createNode(old,ndkVariableDeclaratorSyntax);
      clone(dynamic_cast<structure::VariableDeclaratorSyntax*>(newNode), dynamic_cast<const structure::VariableDeclaratorSyntax*>(old));
      break;
    case ndkWhenClauseSyntax: 
      newNode = createNode(old,ndkWhenClauseSyntax);
      clone(dynamic_cast<structure::WhenClauseSyntax*>(newNode), dynamic_cast<const structure::WhenClauseSyntax*>(old));
      break;
    case ndkWhereClauseSyntax: 
      newNode = createNode(old,ndkWhereClauseSyntax);
      clone(dynamic_cast<structure::WhereClauseSyntax*>(newNode), dynamic_cast<const structure::WhereClauseSyntax*>(old));
      break;
    case ndkXmlCDataSectionSyntax: 
      newNode = createNode(old,ndkXmlCDataSectionSyntax);
      clone(dynamic_cast<structure::XmlCDataSectionSyntax*>(newNode), dynamic_cast<const structure::XmlCDataSectionSyntax*>(old));
      break;
    case ndkXmlCommentSyntax: 
      newNode = createNode(old,ndkXmlCommentSyntax);
      clone(dynamic_cast<structure::XmlCommentSyntax*>(newNode), dynamic_cast<const structure::XmlCommentSyntax*>(old));
      break;
    case ndkXmlCrefAttributeSyntax: 
      newNode = createNode(old,ndkXmlCrefAttributeSyntax);
      clone(dynamic_cast<structure::XmlCrefAttributeSyntax*>(newNode), dynamic_cast<const structure::XmlCrefAttributeSyntax*>(old));
      break;
    case ndkXmlElementEndTagSyntax: 
      newNode = createNode(old,ndkXmlElementEndTagSyntax);
      clone(dynamic_cast<structure::XmlElementEndTagSyntax*>(newNode), dynamic_cast<const structure::XmlElementEndTagSyntax*>(old));
      break;
    case ndkXmlElementStartTagSyntax: 
      newNode = createNode(old,ndkXmlElementStartTagSyntax);
      clone(dynamic_cast<structure::XmlElementStartTagSyntax*>(newNode), dynamic_cast<const structure::XmlElementStartTagSyntax*>(old));
      break;
    case ndkXmlElementSyntax: 
      newNode = createNode(old,ndkXmlElementSyntax);
      clone(dynamic_cast<structure::XmlElementSyntax*>(newNode), dynamic_cast<const structure::XmlElementSyntax*>(old));
      break;
    case ndkXmlEmptyElementSyntax: 
      newNode = createNode(old,ndkXmlEmptyElementSyntax);
      clone(dynamic_cast<structure::XmlEmptyElementSyntax*>(newNode), dynamic_cast<const structure::XmlEmptyElementSyntax*>(old));
      break;
    case ndkXmlNameAttributeSyntax: 
      newNode = createNode(old,ndkXmlNameAttributeSyntax);
      clone(dynamic_cast<structure::XmlNameAttributeSyntax*>(newNode), dynamic_cast<const structure::XmlNameAttributeSyntax*>(old));
      break;
    case ndkXmlNameSyntax: 
      newNode = createNode(old,ndkXmlNameSyntax);
      clone(dynamic_cast<structure::XmlNameSyntax*>(newNode), dynamic_cast<const structure::XmlNameSyntax*>(old));
      break;
    case ndkXmlPrefixSyntax: 
      newNode = createNode(old,ndkXmlPrefixSyntax);
      clone(dynamic_cast<structure::XmlPrefixSyntax*>(newNode), dynamic_cast<const structure::XmlPrefixSyntax*>(old));
      break;
    case ndkXmlProcessingInstructionSyntax: 
      newNode = createNode(old,ndkXmlProcessingInstructionSyntax);
      clone(dynamic_cast<structure::XmlProcessingInstructionSyntax*>(newNode), dynamic_cast<const structure::XmlProcessingInstructionSyntax*>(old));
      break;
    case ndkXmlTextAttributeSyntax: 
      newNode = createNode(old,ndkXmlTextAttributeSyntax);
      clone(dynamic_cast<structure::XmlTextAttributeSyntax*>(newNode), dynamic_cast<const structure::XmlTextAttributeSyntax*>(old));
      break;
    case ndkXmlTextSyntax: 
      newNode = createNode(old,ndkXmlTextSyntax);
      clone(dynamic_cast<structure::XmlTextSyntax*>(newNode), dynamic_cast<const structure::XmlTextSyntax*>(old));
      break;
    default: newNode = NULL; break;
  }
  return newNode;
}
void AlgorithmDeepCopy::clone(base::Base* dest, const base::Base* src) {
}

void AlgorithmDeepCopy::clone(base::Positioned* dest, const base::Positioned* src) {
  // Copying attributes
  // Copying edges
  // Copying attributes
  dest->setPosition(src->getPosition());
  // Copying edges
}

void AlgorithmDeepCopy::clone(expression::AliasQualifiedNameSyntax* dest, const expression::AliasQualifiedNameSyntax* src) {
  // Copying attributes
  // Copying edges
  // Copying attributes
  dest->setPosition(src->getPosition());
  // Copying edges
  // Copying attributes
  // Copying edges
  // Copying attributes
  // Copying edges
  base::Base* pNewSingleEdge;
  pNewSingleEdge = getMappedNode(src->getOriginalDefinition());
  if (pNewSingleEdge)
    dest->setOriginalDefinition(dynamic_cast<structure::MemberDeclarationSyntax*>(pNewSingleEdge));
  // Copying attributes
  // Copying edges
  // Copying attributes
  // Copying edges
  pNewSingleEdge = getMappedNode(src->getAlias());
  if (pNewSingleEdge)
    dest->setAlias(dynamic_cast<expression::IdentifierNameSyntax*>(pNewSingleEdge));
  pNewSingleEdge = getMappedNode(src->getName());
  if (pNewSingleEdge)
    dest->setName(dynamic_cast<expression::SimpleNameSyntax*>(pNewSingleEdge));
}

void AlgorithmDeepCopy::clone(expression::AnonymousFunctionExpressionSyntax* dest, const expression::AnonymousFunctionExpressionSyntax* src) {
  // Copying attributes
  // Copying edges
  // Copying attributes
  dest->setPosition(src->getPosition());
  // Copying edges
  // Copying attributes
  // Copying edges
  // Copying attributes
  dest->setIdentifier(src->getIdentifier());
  // Copying edges
  base::Base* pNewSingleEdge;
  pNewSingleEdge = getMappedNode(src->getBlock());
  if (pNewSingleEdge)
    dest->setBlock(dynamic_cast<statement::BlockSyntax*>(pNewSingleEdge));
  pNewSingleEdge = getMappedNode(src->getExpressionBody());
  if (pNewSingleEdge)
    dest->setExpressionBody(dynamic_cast<expression::ExpressionSyntax*>(pNewSingleEdge));
}

void AlgorithmDeepCopy::clone(expression::AnonymousMethodExpressionSyntax* dest, const expression::AnonymousMethodExpressionSyntax* src) {
  // Copying attributes
  // Copying edges
  // Copying attributes
  dest->setPosition(src->getPosition());
  // Copying edges
  // Copying attributes
  // Copying edges
  // Copying attributes
  dest->setIdentifier(src->getIdentifier());
  // Copying edges
  base::Base* pNewSingleEdge;
  pNewSingleEdge = getMappedNode(src->getBlock());
  if (pNewSingleEdge)
    dest->setBlock(dynamic_cast<statement::BlockSyntax*>(pNewSingleEdge));
  pNewSingleEdge = getMappedNode(src->getExpressionBody());
  if (pNewSingleEdge)
    dest->setExpressionBody(dynamic_cast<expression::ExpressionSyntax*>(pNewSingleEdge));
  // Copying attributes
  // Copying edges
  pNewSingleEdge = getMappedNode(src->getParameterList());
  if (pNewSingleEdge)
    dest->setParameterList(dynamic_cast<structure::ParameterListSyntax*>(pNewSingleEdge));
}

void AlgorithmDeepCopy::clone(expression::AnonymousObjectCreationExpressionSyntax* dest, const expression::AnonymousObjectCreationExpressionSyntax* src) {
  // Copying attributes
  // Copying edges
  // Copying attributes
  dest->setPosition(src->getPosition());
  // Copying edges
  // Copying attributes
  // Copying edges
  // Copying attributes
  dest->setIdentifier(src->getIdentifier());
  // Copying edges
  for ( ListIterator<structure::AnonymousObjectMemberDeclaratorSyntax> it = src->getInitializersListIteratorBegin(); it != src->getInitializersListIteratorEnd(); ++it ) {
    structure::AnonymousObjectMemberDeclaratorSyntax* pNewEdge = dynamic_cast<structure::AnonymousObjectMemberDeclaratorSyntax*>(getMappedNode(&(*it)));
    if (pNewEdge)
      dest->addInitializers(pNewEdge);
  }
}

void AlgorithmDeepCopy::clone(expression::ArrayCreationExpressionSyntax* dest, const expression::ArrayCreationExpressionSyntax* src) {
  // Copying attributes
  // Copying edges
  // Copying attributes
  dest->setPosition(src->getPosition());
  // Copying edges
  // Copying attributes
  // Copying edges
  // Copying attributes
  // Copying edges
  base::Base* pNewSingleEdge;
  pNewSingleEdge = getMappedNode(src->getInitializer());
  if (pNewSingleEdge)
    dest->setInitializer(dynamic_cast<expression::InitializerExpressionSyntax*>(pNewSingleEdge));
  pNewSingleEdge = getMappedNode(src->getType());
  if (pNewSingleEdge)
    dest->setType(dynamic_cast<expression::ArrayTypeSyntax*>(pNewSingleEdge));
}

void AlgorithmDeepCopy::clone(expression::ArrayTypeSyntax* dest, const expression::ArrayTypeSyntax* src) {
  // Copying attributes
  // Copying edges
  // Copying attributes
  dest->setPosition(src->getPosition());
  // Copying edges
  // Copying attributes
  // Copying edges
  // Copying attributes
  // Copying edges
  base::Base* pNewSingleEdge;
  pNewSingleEdge = getMappedNode(src->getOriginalDefinition());
  if (pNewSingleEdge)
    dest->setOriginalDefinition(dynamic_cast<structure::MemberDeclarationSyntax*>(pNewSingleEdge));
  // Copying attributes
  // Copying edges
  pNewSingleEdge = getMappedNode(src->getElementType());
  if (pNewSingleEdge)
    dest->setElementType(dynamic_cast<expression::TypeSyntax*>(pNewSingleEdge));
  for ( ListIterator<structure::ArrayRankSpecifierSyntax> it = src->getRankSpecifiersListIteratorBegin(); it != src->getRankSpecifiersListIteratorEnd(); ++it ) {
    structure::ArrayRankSpecifierSyntax* pNewEdge = dynamic_cast<structure::ArrayRankSpecifierSyntax*>(getMappedNode(&(*it)));
    if (pNewEdge)
      dest->addRankSpecifiers(pNewEdge);
  }
}

void AlgorithmDeepCopy::clone(expression::AssignmentExpressionSyntax* dest, const expression::AssignmentExpressionSyntax* src) {
  // Copying attributes
  // Copying edges
  // Copying attributes
  dest->setPosition(src->getPosition());
  // Copying edges
  // Copying attributes
  // Copying edges
  // Copying attributes
  // Copying edges
  base::Base* pNewSingleEdge;
  pNewSingleEdge = getMappedNode(src->getEventAccessorCall());
  if (pNewSingleEdge)
    dest->setEventAccessorCall(dynamic_cast<structure::AccessorDeclarationSyntax*>(pNewSingleEdge));
  pNewSingleEdge = getMappedNode(src->getLeft());
  if (pNewSingleEdge)
    dest->setLeft(dynamic_cast<expression::ExpressionSyntax*>(pNewSingleEdge));
  pNewSingleEdge = getMappedNode(src->getOverloadedOperatorCall());
  if (pNewSingleEdge)
    dest->setOverloadedOperatorCall(dynamic_cast<structure::OperatorDeclarationSyntax*>(pNewSingleEdge));
  pNewSingleEdge = getMappedNode(src->getRight());
  if (pNewSingleEdge)
    dest->setRight(dynamic_cast<expression::ExpressionSyntax*>(pNewSingleEdge));
}

void AlgorithmDeepCopy::clone(expression::AwaitExpressionSyntax* dest, const expression::AwaitExpressionSyntax* src) {
  // Copying attributes
  // Copying edges
  // Copying attributes
  dest->setPosition(src->getPosition());
  // Copying edges
  // Copying attributes
  // Copying edges
  // Copying attributes
  // Copying edges
  base::Base* pNewSingleEdge;
  pNewSingleEdge = getMappedNode(src->getExpression());
  if (pNewSingleEdge)
    dest->setExpression(dynamic_cast<expression::ExpressionSyntax*>(pNewSingleEdge));
}

void AlgorithmDeepCopy::clone(expression::BaseExpressionSyntax* dest, const expression::BaseExpressionSyntax* src) {
  // Copying attributes
  // Copying edges
  // Copying attributes
  dest->setPosition(src->getPosition());
  // Copying edges
  // Copying attributes
  // Copying edges
  // Copying attributes
  // Copying edges
  // Copying attributes
  // Copying edges
}

void AlgorithmDeepCopy::clone(expression::BinaryExpressionSyntax* dest, const expression::BinaryExpressionSyntax* src) {
  // Copying attributes
  // Copying edges
  // Copying attributes
  dest->setPosition(src->getPosition());
  // Copying edges
  // Copying attributes
  // Copying edges
  // Copying attributes
  // Copying edges
  base::Base* pNewSingleEdge;
  pNewSingleEdge = getMappedNode(src->getLeft());
  if (pNewSingleEdge)
    dest->setLeft(dynamic_cast<expression::ExpressionSyntax*>(pNewSingleEdge));
  pNewSingleEdge = getMappedNode(src->getOverloadedOperatorCall());
  if (pNewSingleEdge)
    dest->setOverloadedOperatorCall(dynamic_cast<structure::OperatorDeclarationSyntax*>(pNewSingleEdge));
  pNewSingleEdge = getMappedNode(src->getRight());
  if (pNewSingleEdge)
    dest->setRight(dynamic_cast<expression::ExpressionSyntax*>(pNewSingleEdge));
}

void AlgorithmDeepCopy::clone(expression::CastExpressionSyntax* dest, const expression::CastExpressionSyntax* src) {
  // Copying attributes
  // Copying edges
  // Copying attributes
  dest->setPosition(src->getPosition());
  // Copying edges
  // Copying attributes
  // Copying edges
  // Copying attributes
  // Copying edges
  base::Base* pNewSingleEdge;
  pNewSingleEdge = getMappedNode(src->getConversionOperatorCall());
  if (pNewSingleEdge)
    dest->setConversionOperatorCall(dynamic_cast<structure::ConversionOperatorDeclarationSyntax*>(pNewSingleEdge));
  pNewSingleEdge = getMappedNode(src->getExpression());
  if (pNewSingleEdge)
    dest->setExpression(dynamic_cast<expression::ExpressionSyntax*>(pNewSingleEdge));
  pNewSingleEdge = getMappedNode(src->getType());
  if (pNewSingleEdge)
    dest->setType(dynamic_cast<expression::TypeSyntax*>(pNewSingleEdge));
}

void AlgorithmDeepCopy::clone(expression::CheckedExpressionSyntax* dest, const expression::CheckedExpressionSyntax* src) {
  // Copying attributes
  // Copying edges
  // Copying attributes
  dest->setPosition(src->getPosition());
  // Copying edges
  // Copying attributes
  // Copying edges
  // Copying attributes
  // Copying edges
  base::Base* pNewSingleEdge;
  pNewSingleEdge = getMappedNode(src->getExpression());
  if (pNewSingleEdge)
    dest->setExpression(dynamic_cast<expression::ExpressionSyntax*>(pNewSingleEdge));
}

void AlgorithmDeepCopy::clone(expression::ConditionalAccessExpressionSyntax* dest, const expression::ConditionalAccessExpressionSyntax* src) {
  // Copying attributes
  // Copying edges
  // Copying attributes
  dest->setPosition(src->getPosition());
  // Copying edges
  // Copying attributes
  // Copying edges
  // Copying attributes
  // Copying edges
  base::Base* pNewSingleEdge;
  pNewSingleEdge = getMappedNode(src->getExpression());
  if (pNewSingleEdge)
    dest->setExpression(dynamic_cast<expression::ExpressionSyntax*>(pNewSingleEdge));
  pNewSingleEdge = getMappedNode(src->getWhenNotNull());
  if (pNewSingleEdge)
    dest->setWhenNotNull(dynamic_cast<expression::ExpressionSyntax*>(pNewSingleEdge));
}

void AlgorithmDeepCopy::clone(expression::ConditionalExpressionSyntax* dest, const expression::ConditionalExpressionSyntax* src) {
  // Copying attributes
  // Copying edges
  // Copying attributes
  dest->setPosition(src->getPosition());
  // Copying edges
  // Copying attributes
  // Copying edges
  // Copying attributes
  // Copying edges
  base::Base* pNewSingleEdge;
  pNewSingleEdge = getMappedNode(src->getCondition());
  if (pNewSingleEdge)
    dest->setCondition(dynamic_cast<expression::ExpressionSyntax*>(pNewSingleEdge));
  pNewSingleEdge = getMappedNode(src->getWhenFalse());
  if (pNewSingleEdge)
    dest->setWhenFalse(dynamic_cast<expression::ExpressionSyntax*>(pNewSingleEdge));
  pNewSingleEdge = getMappedNode(src->getWhenTrue());
  if (pNewSingleEdge)
    dest->setWhenTrue(dynamic_cast<expression::ExpressionSyntax*>(pNewSingleEdge));
}

void AlgorithmDeepCopy::clone(expression::DeclarationExpressionSyntax* dest, const expression::DeclarationExpressionSyntax* src) {
  // Copying attributes
  // Copying edges
  // Copying attributes
  dest->setPosition(src->getPosition());
  // Copying edges
  // Copying attributes
  // Copying edges
  // Copying attributes
  // Copying edges
  base::Base* pNewSingleEdge;
  pNewSingleEdge = getMappedNode(src->getDesignation());
  if (pNewSingleEdge)
    dest->setDesignation(dynamic_cast<structure::VariableDesignationSyntax*>(pNewSingleEdge));
  pNewSingleEdge = getMappedNode(src->getType());
  if (pNewSingleEdge)
    dest->setType(dynamic_cast<expression::TypeSyntax*>(pNewSingleEdge));
}

void AlgorithmDeepCopy::clone(expression::DefaultExpressionSyntax* dest, const expression::DefaultExpressionSyntax* src) {
  // Copying attributes
  // Copying edges
  // Copying attributes
  dest->setPosition(src->getPosition());
  // Copying edges
  // Copying attributes
  // Copying edges
  // Copying attributes
  // Copying edges
  base::Base* pNewSingleEdge;
  pNewSingleEdge = getMappedNode(src->getType());
  if (pNewSingleEdge)
    dest->setType(dynamic_cast<expression::TypeSyntax*>(pNewSingleEdge));
}

void AlgorithmDeepCopy::clone(expression::ElementAccessExpressionSyntax* dest, const expression::ElementAccessExpressionSyntax* src) {
  // Copying attributes
  // Copying edges
  // Copying attributes
  dest->setPosition(src->getPosition());
  // Copying edges
  // Copying attributes
  // Copying edges
  // Copying attributes
  // Copying edges
  for ( ListIterator<structure::AccessorDeclarationSyntax> it = src->getAccessorCallListIteratorBegin(); it != src->getAccessorCallListIteratorEnd(); ++it ) {
    structure::AccessorDeclarationSyntax* pNewEdge = dynamic_cast<structure::AccessorDeclarationSyntax*>(getMappedNode(&(*it)));
    if (pNewEdge)
      dest->addAccessorCall(pNewEdge);
  }
  base::Base* pNewSingleEdge;
  pNewSingleEdge = getMappedNode(src->getArgumentList());
  if (pNewSingleEdge)
    dest->setArgumentList(dynamic_cast<structure::BracketedArgumentListSyntax*>(pNewSingleEdge));
  pNewSingleEdge = getMappedNode(src->getExpression());
  if (pNewSingleEdge)
    dest->setExpression(dynamic_cast<expression::ExpressionSyntax*>(pNewSingleEdge));
}

void AlgorithmDeepCopy::clone(expression::ElementBindingExpressionSyntax* dest, const expression::ElementBindingExpressionSyntax* src) {
  // Copying attributes
  // Copying edges
  // Copying attributes
  dest->setPosition(src->getPosition());
  // Copying edges
  // Copying attributes
  // Copying edges
  // Copying attributes
  // Copying edges
  base::Base* pNewSingleEdge;
  pNewSingleEdge = getMappedNode(src->getArgumentList());
  if (pNewSingleEdge)
    dest->setArgumentList(dynamic_cast<structure::BracketedArgumentListSyntax*>(pNewSingleEdge));
}

void AlgorithmDeepCopy::clone(expression::ExpressionSyntax* dest, const expression::ExpressionSyntax* src) {
  // Copying attributes
  // Copying edges
  // Copying attributes
  dest->setPosition(src->getPosition());
  // Copying edges
  // Copying attributes
  // Copying edges
}

void AlgorithmDeepCopy::clone(expression::GenericNameSyntax* dest, const expression::GenericNameSyntax* src) {
  // Copying attributes
  // Copying edges
  // Copying attributes
  dest->setPosition(src->getPosition());
  // Copying edges
  // Copying attributes
  // Copying edges
  // Copying attributes
  // Copying edges
  base::Base* pNewSingleEdge;
  pNewSingleEdge = getMappedNode(src->getOriginalDefinition());
  if (pNewSingleEdge)
    dest->setOriginalDefinition(dynamic_cast<structure::MemberDeclarationSyntax*>(pNewSingleEdge));
  // Copying attributes
  // Copying edges
  // Copying attributes
  dest->setIdentifier(src->getIdentifier());
  // Copying edges
  // Copying attributes
  // Copying edges
  pNewSingleEdge = getMappedNode(src->getTypeArgumentList());
  if (pNewSingleEdge)
    dest->setTypeArgumentList(dynamic_cast<structure::TypeArgumentListSyntax*>(pNewSingleEdge));
}

void AlgorithmDeepCopy::clone(expression::IdentifierNameSyntax* dest, const expression::IdentifierNameSyntax* src) {
  // Copying attributes
  // Copying edges
  // Copying attributes
  dest->setPosition(src->getPosition());
  // Copying edges
  // Copying attributes
  // Copying edges
  // Copying attributes
  // Copying edges
  base::Base* pNewSingleEdge;
  pNewSingleEdge = getMappedNode(src->getOriginalDefinition());
  if (pNewSingleEdge)
    dest->setOriginalDefinition(dynamic_cast<structure::MemberDeclarationSyntax*>(pNewSingleEdge));
  // Copying attributes
  // Copying edges
  // Copying attributes
  dest->setIdentifier(src->getIdentifier());
  // Copying edges
  // Copying attributes
  // Copying edges
  for ( ListIterator<structure::AccessorDeclarationSyntax> it = src->getAccessorCallListIteratorBegin(); it != src->getAccessorCallListIteratorEnd(); ++it ) {
    structure::AccessorDeclarationSyntax* pNewEdge = dynamic_cast<structure::AccessorDeclarationSyntax*>(getMappedNode(&(*it)));
    if (pNewEdge)
      dest->addAccessorCall(pNewEdge);
  }
  pNewSingleEdge = getMappedNode(src->getDeclaration());
  if (pNewSingleEdge)
    dest->setDeclaration(dynamic_cast<base::Positioned*>(pNewSingleEdge));
}

void AlgorithmDeepCopy::clone(expression::ImplicitArrayCreationExpressionSyntax* dest, const expression::ImplicitArrayCreationExpressionSyntax* src) {
  // Copying attributes
  // Copying edges
  // Copying attributes
  dest->setPosition(src->getPosition());
  // Copying edges
  // Copying attributes
  // Copying edges
  // Copying attributes
  // Copying edges
  base::Base* pNewSingleEdge;
  pNewSingleEdge = getMappedNode(src->getInitializer());
  if (pNewSingleEdge)
    dest->setInitializer(dynamic_cast<expression::InitializerExpressionSyntax*>(pNewSingleEdge));
}

void AlgorithmDeepCopy::clone(expression::ImplicitElementAccessSyntax* dest, const expression::ImplicitElementAccessSyntax* src) {
  // Copying attributes
  // Copying edges
  // Copying attributes
  dest->setPosition(src->getPosition());
  // Copying edges
  // Copying attributes
  // Copying edges
  // Copying attributes
  // Copying edges
  base::Base* pNewSingleEdge;
  pNewSingleEdge = getMappedNode(src->getArgumentList());
  if (pNewSingleEdge)
    dest->setArgumentList(dynamic_cast<structure::BracketedArgumentListSyntax*>(pNewSingleEdge));
}

void AlgorithmDeepCopy::clone(expression::ImplicitStackAllocArrayCreationExpressionSyntax* dest, const expression::ImplicitStackAllocArrayCreationExpressionSyntax* src) {
  // Copying attributes
  // Copying edges
  // Copying attributes
  dest->setPosition(src->getPosition());
  // Copying edges
  // Copying attributes
  // Copying edges
  // Copying attributes
  // Copying edges
  base::Base* pNewSingleEdge;
  pNewSingleEdge = getMappedNode(src->getInitializer());
  if (pNewSingleEdge)
    dest->setInitializer(dynamic_cast<expression::InitializerExpressionSyntax*>(pNewSingleEdge));
}

void AlgorithmDeepCopy::clone(expression::InitializerExpressionSyntax* dest, const expression::InitializerExpressionSyntax* src) {
  // Copying attributes
  // Copying edges
  // Copying attributes
  dest->setPosition(src->getPosition());
  // Copying edges
  // Copying attributes
  // Copying edges
  // Copying attributes
  // Copying edges
  for ( ListIterator<expression::ExpressionSyntax> it = src->getExpressionsListIteratorBegin(); it != src->getExpressionsListIteratorEnd(); ++it ) {
    expression::ExpressionSyntax* pNewEdge = dynamic_cast<expression::ExpressionSyntax*>(getMappedNode(&(*it)));
    if (pNewEdge)
      dest->addExpressions(pNewEdge);
  }
}

void AlgorithmDeepCopy::clone(expression::InstanceExpressionSyntax* dest, const expression::InstanceExpressionSyntax* src) {
  // Copying attributes
  // Copying edges
  // Copying attributes
  dest->setPosition(src->getPosition());
  // Copying edges
  // Copying attributes
  // Copying edges
  // Copying attributes
  // Copying edges
}

void AlgorithmDeepCopy::clone(expression::InterpolatedStringExpressionSyntax* dest, const expression::InterpolatedStringExpressionSyntax* src) {
  // Copying attributes
  // Copying edges
  // Copying attributes
  dest->setPosition(src->getPosition());
  // Copying edges
  // Copying attributes
  // Copying edges
  // Copying attributes
  // Copying edges
  for ( ListIterator<structure::InterpolatedStringContentSyntax> it = src->getContentsListIteratorBegin(); it != src->getContentsListIteratorEnd(); ++it ) {
    structure::InterpolatedStringContentSyntax* pNewEdge = dynamic_cast<structure::InterpolatedStringContentSyntax*>(getMappedNode(&(*it)));
    if (pNewEdge)
      dest->addContents(pNewEdge);
  }
}

void AlgorithmDeepCopy::clone(expression::InvocationExpressionSyntax* dest, const expression::InvocationExpressionSyntax* src) {
  // Copying attributes
  // Copying edges
  // Copying attributes
  dest->setPosition(src->getPosition());
  // Copying edges
  // Copying attributes
  // Copying edges
  // Copying attributes
  // Copying edges
  base::Base* pNewSingleEdge;
  pNewSingleEdge = getMappedNode(src->getArgumentList());
  if (pNewSingleEdge)
    dest->setArgumentList(dynamic_cast<structure::ArgumentListSyntax*>(pNewSingleEdge));
  pNewSingleEdge = getMappedNode(src->getExpression());
  if (pNewSingleEdge)
    dest->setExpression(dynamic_cast<expression::ExpressionSyntax*>(pNewSingleEdge));
  pNewSingleEdge = getMappedNode(src->getLocalFunctionCall());
  if (pNewSingleEdge)
    dest->setLocalFunctionCall(dynamic_cast<statement::LocalFunctionStatementSyntax*>(pNewSingleEdge));
  pNewSingleEdge = getMappedNode(src->getMethodCall());
  if (pNewSingleEdge)
    dest->setMethodCall(dynamic_cast<structure::MethodDeclarationSyntax*>(pNewSingleEdge));
}

void AlgorithmDeepCopy::clone(expression::IsPatternExpressionSyntax* dest, const expression::IsPatternExpressionSyntax* src) {
  // Copying attributes
  // Copying edges
  // Copying attributes
  dest->setPosition(src->getPosition());
  // Copying edges
  // Copying attributes
  // Copying edges
  // Copying attributes
  // Copying edges
  base::Base* pNewSingleEdge;
  pNewSingleEdge = getMappedNode(src->getExpression());
  if (pNewSingleEdge)
    dest->setExpression(dynamic_cast<expression::ExpressionSyntax*>(pNewSingleEdge));
  pNewSingleEdge = getMappedNode(src->getPattern());
  if (pNewSingleEdge)
    dest->setPattern(dynamic_cast<structure::PatternSyntax*>(pNewSingleEdge));
}

void AlgorithmDeepCopy::clone(expression::LambdaExpressionSyntax* dest, const expression::LambdaExpressionSyntax* src) {
  // Copying attributes
  // Copying edges
  // Copying attributes
  dest->setPosition(src->getPosition());
  // Copying edges
  // Copying attributes
  // Copying edges
  // Copying attributes
  dest->setIdentifier(src->getIdentifier());
  // Copying edges
  base::Base* pNewSingleEdge;
  pNewSingleEdge = getMappedNode(src->getBlock());
  if (pNewSingleEdge)
    dest->setBlock(dynamic_cast<statement::BlockSyntax*>(pNewSingleEdge));
  pNewSingleEdge = getMappedNode(src->getExpressionBody());
  if (pNewSingleEdge)
    dest->setExpressionBody(dynamic_cast<expression::ExpressionSyntax*>(pNewSingleEdge));
  // Copying attributes
  // Copying edges
}

void AlgorithmDeepCopy::clone(expression::LiteralExpressionSyntax* dest, const expression::LiteralExpressionSyntax* src) {
  // Copying attributes
  // Copying edges
  // Copying attributes
  dest->setPosition(src->getPosition());
  // Copying edges
  // Copying attributes
  // Copying edges
  // Copying attributes
  dest->setToken(src->getToken());
  // Copying edges
}

void AlgorithmDeepCopy::clone(expression::MakeRefExpressionSyntax* dest, const expression::MakeRefExpressionSyntax* src) {
  // Copying attributes
  // Copying edges
  // Copying attributes
  dest->setPosition(src->getPosition());
  // Copying edges
  // Copying attributes
  // Copying edges
  // Copying attributes
  // Copying edges
  base::Base* pNewSingleEdge;
  pNewSingleEdge = getMappedNode(src->getExpression());
  if (pNewSingleEdge)
    dest->setExpression(dynamic_cast<expression::ExpressionSyntax*>(pNewSingleEdge));
}

void AlgorithmDeepCopy::clone(expression::MemberAccessExpressionSyntax* dest, const expression::MemberAccessExpressionSyntax* src) {
  // Copying attributes
  // Copying edges
  // Copying attributes
  dest->setPosition(src->getPosition());
  // Copying edges
  // Copying attributes
  // Copying edges
  // Copying attributes
  // Copying edges
  base::Base* pNewSingleEdge;
  pNewSingleEdge = getMappedNode(src->getExpression());
  if (pNewSingleEdge)
    dest->setExpression(dynamic_cast<expression::ExpressionSyntax*>(pNewSingleEdge));
  pNewSingleEdge = getMappedNode(src->getName());
  if (pNewSingleEdge)
    dest->setName(dynamic_cast<expression::SimpleNameSyntax*>(pNewSingleEdge));
}

void AlgorithmDeepCopy::clone(expression::MemberBindingExpressionSyntax* dest, const expression::MemberBindingExpressionSyntax* src) {
  // Copying attributes
  // Copying edges
  // Copying attributes
  dest->setPosition(src->getPosition());
  // Copying edges
  // Copying attributes
  // Copying edges
  // Copying attributes
  // Copying edges
  base::Base* pNewSingleEdge;
  pNewSingleEdge = getMappedNode(src->getName());
  if (pNewSingleEdge)
    dest->setName(dynamic_cast<expression::SimpleNameSyntax*>(pNewSingleEdge));
}

void AlgorithmDeepCopy::clone(expression::NameSyntax* dest, const expression::NameSyntax* src) {
  // Copying attributes
  // Copying edges
  // Copying attributes
  dest->setPosition(src->getPosition());
  // Copying edges
  // Copying attributes
  // Copying edges
  // Copying attributes
  // Copying edges
  base::Base* pNewSingleEdge;
  pNewSingleEdge = getMappedNode(src->getOriginalDefinition());
  if (pNewSingleEdge)
    dest->setOriginalDefinition(dynamic_cast<structure::MemberDeclarationSyntax*>(pNewSingleEdge));
  // Copying attributes
  // Copying edges
}

void AlgorithmDeepCopy::clone(expression::NullableTypeSyntax* dest, const expression::NullableTypeSyntax* src) {
  // Copying attributes
  // Copying edges
  // Copying attributes
  dest->setPosition(src->getPosition());
  // Copying edges
  // Copying attributes
  // Copying edges
  // Copying attributes
  // Copying edges
  base::Base* pNewSingleEdge;
  pNewSingleEdge = getMappedNode(src->getOriginalDefinition());
  if (pNewSingleEdge)
    dest->setOriginalDefinition(dynamic_cast<structure::MemberDeclarationSyntax*>(pNewSingleEdge));
  // Copying attributes
  // Copying edges
  pNewSingleEdge = getMappedNode(src->getElementType());
  if (pNewSingleEdge)
    dest->setElementType(dynamic_cast<expression::TypeSyntax*>(pNewSingleEdge));
}

void AlgorithmDeepCopy::clone(expression::ObjectCreationExpressionSyntax* dest, const expression::ObjectCreationExpressionSyntax* src) {
  // Copying attributes
  // Copying edges
  // Copying attributes
  dest->setPosition(src->getPosition());
  // Copying edges
  // Copying attributes
  // Copying edges
  // Copying attributes
  // Copying edges
  base::Base* pNewSingleEdge;
  pNewSingleEdge = getMappedNode(src->getArgumentList());
  if (pNewSingleEdge)
    dest->setArgumentList(dynamic_cast<structure::ArgumentListSyntax*>(pNewSingleEdge));
  pNewSingleEdge = getMappedNode(src->getConstructorCall());
  if (pNewSingleEdge)
    dest->setConstructorCall(dynamic_cast<structure::ConstructorDeclarationSyntax*>(pNewSingleEdge));
  pNewSingleEdge = getMappedNode(src->getInitializer());
  if (pNewSingleEdge)
    dest->setInitializer(dynamic_cast<expression::InitializerExpressionSyntax*>(pNewSingleEdge));
  pNewSingleEdge = getMappedNode(src->getType());
  if (pNewSingleEdge)
    dest->setType(dynamic_cast<expression::TypeSyntax*>(pNewSingleEdge));
}

void AlgorithmDeepCopy::clone(expression::OmittedArraySizeExpressionSyntax* dest, const expression::OmittedArraySizeExpressionSyntax* src) {
  // Copying attributes
  // Copying edges
  // Copying attributes
  dest->setPosition(src->getPosition());
  // Copying edges
  // Copying attributes
  // Copying edges
  // Copying attributes
  // Copying edges
}

void AlgorithmDeepCopy::clone(expression::OmittedTypeArgumentSyntax* dest, const expression::OmittedTypeArgumentSyntax* src) {
  // Copying attributes
  // Copying edges
  // Copying attributes
  dest->setPosition(src->getPosition());
  // Copying edges
  // Copying attributes
  // Copying edges
  // Copying attributes
  // Copying edges
  base::Base* pNewSingleEdge;
  pNewSingleEdge = getMappedNode(src->getOriginalDefinition());
  if (pNewSingleEdge)
    dest->setOriginalDefinition(dynamic_cast<structure::MemberDeclarationSyntax*>(pNewSingleEdge));
  // Copying attributes
  // Copying edges
}

void AlgorithmDeepCopy::clone(expression::ParenthesizedExpressionSyntax* dest, const expression::ParenthesizedExpressionSyntax* src) {
  // Copying attributes
  // Copying edges
  // Copying attributes
  dest->setPosition(src->getPosition());
  // Copying edges
  // Copying attributes
  // Copying edges
  // Copying attributes
  // Copying edges
  base::Base* pNewSingleEdge;
  pNewSingleEdge = getMappedNode(src->getExpression());
  if (pNewSingleEdge)
    dest->setExpression(dynamic_cast<expression::ExpressionSyntax*>(pNewSingleEdge));
}

void AlgorithmDeepCopy::clone(expression::ParenthesizedLambdaExpressionSyntax* dest, const expression::ParenthesizedLambdaExpressionSyntax* src) {
  // Copying attributes
  // Copying edges
  // Copying attributes
  dest->setPosition(src->getPosition());
  // Copying edges
  // Copying attributes
  // Copying edges
  // Copying attributes
  dest->setIdentifier(src->getIdentifier());
  // Copying edges
  base::Base* pNewSingleEdge;
  pNewSingleEdge = getMappedNode(src->getBlock());
  if (pNewSingleEdge)
    dest->setBlock(dynamic_cast<statement::BlockSyntax*>(pNewSingleEdge));
  pNewSingleEdge = getMappedNode(src->getExpressionBody());
  if (pNewSingleEdge)
    dest->setExpressionBody(dynamic_cast<expression::ExpressionSyntax*>(pNewSingleEdge));
  // Copying attributes
  // Copying edges
  // Copying attributes
  // Copying edges
  pNewSingleEdge = getMappedNode(src->getParameterList());
  if (pNewSingleEdge)
    dest->setParameterList(dynamic_cast<structure::ParameterListSyntax*>(pNewSingleEdge));
}

void AlgorithmDeepCopy::clone(expression::PointerTypeSyntax* dest, const expression::PointerTypeSyntax* src) {
  // Copying attributes
  // Copying edges
  // Copying attributes
  dest->setPosition(src->getPosition());
  // Copying edges
  // Copying attributes
  // Copying edges
  // Copying attributes
  // Copying edges
  base::Base* pNewSingleEdge;
  pNewSingleEdge = getMappedNode(src->getOriginalDefinition());
  if (pNewSingleEdge)
    dest->setOriginalDefinition(dynamic_cast<structure::MemberDeclarationSyntax*>(pNewSingleEdge));
  // Copying attributes
  // Copying edges
  pNewSingleEdge = getMappedNode(src->getElementType());
  if (pNewSingleEdge)
    dest->setElementType(dynamic_cast<expression::TypeSyntax*>(pNewSingleEdge));
}

void AlgorithmDeepCopy::clone(expression::PostfixUnaryExpressionSyntax* dest, const expression::PostfixUnaryExpressionSyntax* src) {
  // Copying attributes
  // Copying edges
  // Copying attributes
  dest->setPosition(src->getPosition());
  // Copying edges
  // Copying attributes
  // Copying edges
  // Copying attributes
  // Copying edges
  base::Base* pNewSingleEdge;
  pNewSingleEdge = getMappedNode(src->getOperand());
  if (pNewSingleEdge)
    dest->setOperand(dynamic_cast<expression::ExpressionSyntax*>(pNewSingleEdge));
  pNewSingleEdge = getMappedNode(src->getOverloadedOperatorCall());
  if (pNewSingleEdge)
    dest->setOverloadedOperatorCall(dynamic_cast<structure::OperatorDeclarationSyntax*>(pNewSingleEdge));
}

void AlgorithmDeepCopy::clone(expression::PredefinedTypeSyntax* dest, const expression::PredefinedTypeSyntax* src) {
  // Copying attributes
  // Copying edges
  // Copying attributes
  dest->setPosition(src->getPosition());
  // Copying edges
  // Copying attributes
  // Copying edges
  // Copying attributes
  // Copying edges
  base::Base* pNewSingleEdge;
  pNewSingleEdge = getMappedNode(src->getOriginalDefinition());
  if (pNewSingleEdge)
    dest->setOriginalDefinition(dynamic_cast<structure::MemberDeclarationSyntax*>(pNewSingleEdge));
  // Copying attributes
  // Copying edges
}

void AlgorithmDeepCopy::clone(expression::PrefixUnaryExpressionSyntax* dest, const expression::PrefixUnaryExpressionSyntax* src) {
  // Copying attributes
  // Copying edges
  // Copying attributes
  dest->setPosition(src->getPosition());
  // Copying edges
  // Copying attributes
  // Copying edges
  // Copying attributes
  // Copying edges
  base::Base* pNewSingleEdge;
  pNewSingleEdge = getMappedNode(src->getOperand());
  if (pNewSingleEdge)
    dest->setOperand(dynamic_cast<expression::ExpressionSyntax*>(pNewSingleEdge));
  pNewSingleEdge = getMappedNode(src->getOverloadedOperatorCall());
  if (pNewSingleEdge)
    dest->setOverloadedOperatorCall(dynamic_cast<structure::OperatorDeclarationSyntax*>(pNewSingleEdge));
}

void AlgorithmDeepCopy::clone(expression::QualifiedNameSyntax* dest, const expression::QualifiedNameSyntax* src) {
  // Copying attributes
  // Copying edges
  // Copying attributes
  dest->setPosition(src->getPosition());
  // Copying edges
  // Copying attributes
  // Copying edges
  // Copying attributes
  // Copying edges
  base::Base* pNewSingleEdge;
  pNewSingleEdge = getMappedNode(src->getOriginalDefinition());
  if (pNewSingleEdge)
    dest->setOriginalDefinition(dynamic_cast<structure::MemberDeclarationSyntax*>(pNewSingleEdge));
  // Copying attributes
  // Copying edges
  // Copying attributes
  // Copying edges
  pNewSingleEdge = getMappedNode(src->getLeft());
  if (pNewSingleEdge)
    dest->setLeft(dynamic_cast<expression::NameSyntax*>(pNewSingleEdge));
  pNewSingleEdge = getMappedNode(src->getRight());
  if (pNewSingleEdge)
    dest->setRight(dynamic_cast<expression::SimpleNameSyntax*>(pNewSingleEdge));
}

void AlgorithmDeepCopy::clone(expression::QueryExpressionSyntax* dest, const expression::QueryExpressionSyntax* src) {
  // Copying attributes
  // Copying edges
  // Copying attributes
  dest->setPosition(src->getPosition());
  // Copying edges
  // Copying attributes
  // Copying edges
  // Copying attributes
  // Copying edges
  base::Base* pNewSingleEdge;
  pNewSingleEdge = getMappedNode(src->getBody());
  if (pNewSingleEdge)
    dest->setBody(dynamic_cast<structure::QueryBodySyntax*>(pNewSingleEdge));
  pNewSingleEdge = getMappedNode(src->getFromClause());
  if (pNewSingleEdge)
    dest->setFromClause(dynamic_cast<structure::FromClauseSyntax*>(pNewSingleEdge));
}

void AlgorithmDeepCopy::clone(expression::RangeExpressionSyntax* dest, const expression::RangeExpressionSyntax* src) {
  // Copying attributes
  // Copying edges
  // Copying attributes
  dest->setPosition(src->getPosition());
  // Copying edges
  // Copying attributes
  // Copying edges
  // Copying attributes
  // Copying edges
  base::Base* pNewSingleEdge;
  pNewSingleEdge = getMappedNode(src->getLeftOperand());
  if (pNewSingleEdge)
    dest->setLeftOperand(dynamic_cast<expression::ExpressionSyntax*>(pNewSingleEdge));
  pNewSingleEdge = getMappedNode(src->getRightOperand());
  if (pNewSingleEdge)
    dest->setRightOperand(dynamic_cast<expression::ExpressionSyntax*>(pNewSingleEdge));
}

void AlgorithmDeepCopy::clone(expression::RefExpressionSyntax* dest, const expression::RefExpressionSyntax* src) {
  // Copying attributes
  // Copying edges
  // Copying attributes
  dest->setPosition(src->getPosition());
  // Copying edges
  // Copying attributes
  // Copying edges
  // Copying attributes
  // Copying edges
  base::Base* pNewSingleEdge;
  pNewSingleEdge = getMappedNode(src->getExpression());
  if (pNewSingleEdge)
    dest->setExpression(dynamic_cast<expression::ExpressionSyntax*>(pNewSingleEdge));
}

void AlgorithmDeepCopy::clone(expression::RefTypeExpressionSyntax* dest, const expression::RefTypeExpressionSyntax* src) {
  // Copying attributes
  // Copying edges
  // Copying attributes
  dest->setPosition(src->getPosition());
  // Copying edges
  // Copying attributes
  // Copying edges
  // Copying attributes
  // Copying edges
  base::Base* pNewSingleEdge;
  pNewSingleEdge = getMappedNode(src->getExpression());
  if (pNewSingleEdge)
    dest->setExpression(dynamic_cast<expression::ExpressionSyntax*>(pNewSingleEdge));
}

void AlgorithmDeepCopy::clone(expression::RefTypeSyntax* dest, const expression::RefTypeSyntax* src) {
  // Copying attributes
  // Copying edges
  // Copying attributes
  dest->setPosition(src->getPosition());
  // Copying edges
  // Copying attributes
  // Copying edges
  // Copying attributes
  // Copying edges
  base::Base* pNewSingleEdge;
  pNewSingleEdge = getMappedNode(src->getOriginalDefinition());
  if (pNewSingleEdge)
    dest->setOriginalDefinition(dynamic_cast<structure::MemberDeclarationSyntax*>(pNewSingleEdge));
  // Copying attributes
  // Copying edges
  pNewSingleEdge = getMappedNode(src->getType());
  if (pNewSingleEdge)
    dest->setType(dynamic_cast<expression::TypeSyntax*>(pNewSingleEdge));
}

void AlgorithmDeepCopy::clone(expression::RefValueExpressionSyntax* dest, const expression::RefValueExpressionSyntax* src) {
  // Copying attributes
  // Copying edges
  // Copying attributes
  dest->setPosition(src->getPosition());
  // Copying edges
  // Copying attributes
  // Copying edges
  // Copying attributes
  // Copying edges
  base::Base* pNewSingleEdge;
  pNewSingleEdge = getMappedNode(src->getExpression());
  if (pNewSingleEdge)
    dest->setExpression(dynamic_cast<expression::ExpressionSyntax*>(pNewSingleEdge));
  pNewSingleEdge = getMappedNode(src->getType());
  if (pNewSingleEdge)
    dest->setType(dynamic_cast<expression::TypeSyntax*>(pNewSingleEdge));
}

void AlgorithmDeepCopy::clone(expression::SimpleLambdaExpressionSyntax* dest, const expression::SimpleLambdaExpressionSyntax* src) {
  // Copying attributes
  // Copying edges
  // Copying attributes
  dest->setPosition(src->getPosition());
  // Copying edges
  // Copying attributes
  // Copying edges
  // Copying attributes
  dest->setIdentifier(src->getIdentifier());
  // Copying edges
  base::Base* pNewSingleEdge;
  pNewSingleEdge = getMappedNode(src->getBlock());
  if (pNewSingleEdge)
    dest->setBlock(dynamic_cast<statement::BlockSyntax*>(pNewSingleEdge));
  pNewSingleEdge = getMappedNode(src->getExpressionBody());
  if (pNewSingleEdge)
    dest->setExpressionBody(dynamic_cast<expression::ExpressionSyntax*>(pNewSingleEdge));
  // Copying attributes
  // Copying edges
  // Copying attributes
  // Copying edges
  pNewSingleEdge = getMappedNode(src->getParameter());
  if (pNewSingleEdge)
    dest->setParameter(dynamic_cast<structure::ParameterSyntax*>(pNewSingleEdge));
}

void AlgorithmDeepCopy::clone(expression::SimpleNameSyntax* dest, const expression::SimpleNameSyntax* src) {
  // Copying attributes
  // Copying edges
  // Copying attributes
  dest->setPosition(src->getPosition());
  // Copying edges
  // Copying attributes
  // Copying edges
  // Copying attributes
  // Copying edges
  base::Base* pNewSingleEdge;
  pNewSingleEdge = getMappedNode(src->getOriginalDefinition());
  if (pNewSingleEdge)
    dest->setOriginalDefinition(dynamic_cast<structure::MemberDeclarationSyntax*>(pNewSingleEdge));
  // Copying attributes
  // Copying edges
  // Copying attributes
  dest->setIdentifier(src->getIdentifier());
  // Copying edges
}

void AlgorithmDeepCopy::clone(expression::SizeOfExpressionSyntax* dest, const expression::SizeOfExpressionSyntax* src) {
  // Copying attributes
  // Copying edges
  // Copying attributes
  dest->setPosition(src->getPosition());
  // Copying edges
  // Copying attributes
  // Copying edges
  // Copying attributes
  // Copying edges
  base::Base* pNewSingleEdge;
  pNewSingleEdge = getMappedNode(src->getType());
  if (pNewSingleEdge)
    dest->setType(dynamic_cast<expression::TypeSyntax*>(pNewSingleEdge));
}

void AlgorithmDeepCopy::clone(expression::StackAllocArrayCreationExpressionSyntax* dest, const expression::StackAllocArrayCreationExpressionSyntax* src) {
  // Copying attributes
  // Copying edges
  // Copying attributes
  dest->setPosition(src->getPosition());
  // Copying edges
  // Copying attributes
  // Copying edges
  // Copying attributes
  // Copying edges
  base::Base* pNewSingleEdge;
  pNewSingleEdge = getMappedNode(src->getInitializer());
  if (pNewSingleEdge)
    dest->setInitializer(dynamic_cast<expression::InitializerExpressionSyntax*>(pNewSingleEdge));
  pNewSingleEdge = getMappedNode(src->getType());
  if (pNewSingleEdge)
    dest->setType(dynamic_cast<expression::TypeSyntax*>(pNewSingleEdge));
}

void AlgorithmDeepCopy::clone(expression::SwitchExpressionSyntax* dest, const expression::SwitchExpressionSyntax* src) {
  // Copying attributes
  // Copying edges
  // Copying attributes
  dest->setPosition(src->getPosition());
  // Copying edges
  // Copying attributes
  // Copying edges
  // Copying attributes
  // Copying edges
  for ( ListIterator<structure::SwitchExpressionArmSyntax> it = src->getArmsListIteratorBegin(); it != src->getArmsListIteratorEnd(); ++it ) {
    structure::SwitchExpressionArmSyntax* pNewEdge = dynamic_cast<structure::SwitchExpressionArmSyntax*>(getMappedNode(&(*it)));
    if (pNewEdge)
      dest->addArms(pNewEdge);
  }
  base::Base* pNewSingleEdge;
  pNewSingleEdge = getMappedNode(src->getGoverningExpression());
  if (pNewSingleEdge)
    dest->setGoverningExpression(dynamic_cast<expression::ExpressionSyntax*>(pNewSingleEdge));
}

void AlgorithmDeepCopy::clone(expression::ThisExpressionSyntax* dest, const expression::ThisExpressionSyntax* src) {
  // Copying attributes
  // Copying edges
  // Copying attributes
  dest->setPosition(src->getPosition());
  // Copying edges
  // Copying attributes
  // Copying edges
  // Copying attributes
  // Copying edges
  // Copying attributes
  // Copying edges
}

void AlgorithmDeepCopy::clone(expression::ThrowExpressionSyntax* dest, const expression::ThrowExpressionSyntax* src) {
  // Copying attributes
  // Copying edges
  // Copying attributes
  dest->setPosition(src->getPosition());
  // Copying edges
  // Copying attributes
  // Copying edges
  // Copying attributes
  // Copying edges
  base::Base* pNewSingleEdge;
  pNewSingleEdge = getMappedNode(src->getExpression());
  if (pNewSingleEdge)
    dest->setExpression(dynamic_cast<expression::ExpressionSyntax*>(pNewSingleEdge));
}

void AlgorithmDeepCopy::clone(expression::TupleExpressionSyntax* dest, const expression::TupleExpressionSyntax* src) {
  // Copying attributes
  // Copying edges
  // Copying attributes
  dest->setPosition(src->getPosition());
  // Copying edges
  // Copying attributes
  // Copying edges
  // Copying attributes
  // Copying edges
  for ( ListIterator<structure::ArgumentSyntax> it = src->getArgumentsListIteratorBegin(); it != src->getArgumentsListIteratorEnd(); ++it ) {
    structure::ArgumentSyntax* pNewEdge = dynamic_cast<structure::ArgumentSyntax*>(getMappedNode(&(*it)));
    if (pNewEdge)
      dest->addArguments(pNewEdge);
  }
}

void AlgorithmDeepCopy::clone(expression::TupleTypeSyntax* dest, const expression::TupleTypeSyntax* src) {
  // Copying attributes
  // Copying edges
  // Copying attributes
  dest->setPosition(src->getPosition());
  // Copying edges
  // Copying attributes
  // Copying edges
  // Copying attributes
  // Copying edges
  base::Base* pNewSingleEdge;
  pNewSingleEdge = getMappedNode(src->getOriginalDefinition());
  if (pNewSingleEdge)
    dest->setOriginalDefinition(dynamic_cast<structure::MemberDeclarationSyntax*>(pNewSingleEdge));
  // Copying attributes
  // Copying edges
  for ( ListIterator<structure::TupleElementSyntax> it = src->getElementsListIteratorBegin(); it != src->getElementsListIteratorEnd(); ++it ) {
    structure::TupleElementSyntax* pNewEdge = dynamic_cast<structure::TupleElementSyntax*>(getMappedNode(&(*it)));
    if (pNewEdge)
      dest->addElements(pNewEdge);
  }
}

void AlgorithmDeepCopy::clone(expression::TypeOfExpressionSyntax* dest, const expression::TypeOfExpressionSyntax* src) {
  // Copying attributes
  // Copying edges
  // Copying attributes
  dest->setPosition(src->getPosition());
  // Copying edges
  // Copying attributes
  // Copying edges
  // Copying attributes
  // Copying edges
  base::Base* pNewSingleEdge;
  pNewSingleEdge = getMappedNode(src->getType());
  if (pNewSingleEdge)
    dest->setType(dynamic_cast<expression::TypeSyntax*>(pNewSingleEdge));
}

void AlgorithmDeepCopy::clone(expression::TypeSyntax* dest, const expression::TypeSyntax* src) {
  // Copying attributes
  // Copying edges
  // Copying attributes
  dest->setPosition(src->getPosition());
  // Copying edges
  // Copying attributes
  // Copying edges
  // Copying attributes
  // Copying edges
  base::Base* pNewSingleEdge;
  pNewSingleEdge = getMappedNode(src->getOriginalDefinition());
  if (pNewSingleEdge)
    dest->setOriginalDefinition(dynamic_cast<structure::MemberDeclarationSyntax*>(pNewSingleEdge));
}

void AlgorithmDeepCopy::clone(statement::BlockSyntax* dest, const statement::BlockSyntax* src) {
  // Copying attributes
  // Copying edges
  // Copying attributes
  dest->setPosition(src->getPosition());
  // Copying edges
  // Copying attributes
  // Copying edges
  for ( ListIterator<structure::AttributeListSyntax> it = src->getAttributeListsListIteratorBegin(); it != src->getAttributeListsListIteratorEnd(); ++it ) {
    structure::AttributeListSyntax* pNewEdge = dynamic_cast<structure::AttributeListSyntax*>(getMappedNode(&(*it)));
    if (pNewEdge)
      dest->addAttributeLists(pNewEdge);
  }
  // Copying attributes
  // Copying edges
  for ( ListIterator<statement::StatementSyntax> it = src->getStatementsListIteratorBegin(); it != src->getStatementsListIteratorEnd(); ++it ) {
    statement::StatementSyntax* pNewEdge = dynamic_cast<statement::StatementSyntax*>(getMappedNode(&(*it)));
    if (pNewEdge)
      dest->addStatements(pNewEdge);
  }
}

void AlgorithmDeepCopy::clone(statement::BreakStatementSyntax* dest, const statement::BreakStatementSyntax* src) {
  // Copying attributes
  // Copying edges
  // Copying attributes
  dest->setPosition(src->getPosition());
  // Copying edges
  // Copying attributes
  // Copying edges
  for ( ListIterator<structure::AttributeListSyntax> it = src->getAttributeListsListIteratorBegin(); it != src->getAttributeListsListIteratorEnd(); ++it ) {
    structure::AttributeListSyntax* pNewEdge = dynamic_cast<structure::AttributeListSyntax*>(getMappedNode(&(*it)));
    if (pNewEdge)
      dest->addAttributeLists(pNewEdge);
  }
  // Copying attributes
  // Copying edges
}

void AlgorithmDeepCopy::clone(statement::CheckedStatementSyntax* dest, const statement::CheckedStatementSyntax* src) {
  // Copying attributes
  // Copying edges
  // Copying attributes
  dest->setPosition(src->getPosition());
  // Copying edges
  // Copying attributes
  // Copying edges
  for ( ListIterator<structure::AttributeListSyntax> it = src->getAttributeListsListIteratorBegin(); it != src->getAttributeListsListIteratorEnd(); ++it ) {
    structure::AttributeListSyntax* pNewEdge = dynamic_cast<structure::AttributeListSyntax*>(getMappedNode(&(*it)));
    if (pNewEdge)
      dest->addAttributeLists(pNewEdge);
  }
  // Copying attributes
  // Copying edges
  base::Base* pNewSingleEdge;
  pNewSingleEdge = getMappedNode(src->getBlock());
  if (pNewSingleEdge)
    dest->setBlock(dynamic_cast<statement::BlockSyntax*>(pNewSingleEdge));
}

void AlgorithmDeepCopy::clone(statement::CommonForEachStatementSyntax* dest, const statement::CommonForEachStatementSyntax* src) {
  // Copying attributes
  // Copying edges
  // Copying attributes
  dest->setPosition(src->getPosition());
  // Copying edges
  // Copying attributes
  // Copying edges
  for ( ListIterator<structure::AttributeListSyntax> it = src->getAttributeListsListIteratorBegin(); it != src->getAttributeListsListIteratorEnd(); ++it ) {
    structure::AttributeListSyntax* pNewEdge = dynamic_cast<structure::AttributeListSyntax*>(getMappedNode(&(*it)));
    if (pNewEdge)
      dest->addAttributeLists(pNewEdge);
  }
  // Copying attributes
  // Copying edges
  base::Base* pNewSingleEdge;
  pNewSingleEdge = getMappedNode(src->getExpression());
  if (pNewSingleEdge)
    dest->setExpression(dynamic_cast<expression::ExpressionSyntax*>(pNewSingleEdge));
  pNewSingleEdge = getMappedNode(src->getStatement());
  if (pNewSingleEdge)
    dest->setStatement(dynamic_cast<statement::StatementSyntax*>(pNewSingleEdge));
}

void AlgorithmDeepCopy::clone(statement::ContinueStatementSyntax* dest, const statement::ContinueStatementSyntax* src) {
  // Copying attributes
  // Copying edges
  // Copying attributes
  dest->setPosition(src->getPosition());
  // Copying edges
  // Copying attributes
  // Copying edges
  for ( ListIterator<structure::AttributeListSyntax> it = src->getAttributeListsListIteratorBegin(); it != src->getAttributeListsListIteratorEnd(); ++it ) {
    structure::AttributeListSyntax* pNewEdge = dynamic_cast<structure::AttributeListSyntax*>(getMappedNode(&(*it)));
    if (pNewEdge)
      dest->addAttributeLists(pNewEdge);
  }
  // Copying attributes
  // Copying edges
}

void AlgorithmDeepCopy::clone(statement::DoStatementSyntax* dest, const statement::DoStatementSyntax* src) {
  // Copying attributes
  // Copying edges
  // Copying attributes
  dest->setPosition(src->getPosition());
  // Copying edges
  // Copying attributes
  // Copying edges
  for ( ListIterator<structure::AttributeListSyntax> it = src->getAttributeListsListIteratorBegin(); it != src->getAttributeListsListIteratorEnd(); ++it ) {
    structure::AttributeListSyntax* pNewEdge = dynamic_cast<structure::AttributeListSyntax*>(getMappedNode(&(*it)));
    if (pNewEdge)
      dest->addAttributeLists(pNewEdge);
  }
  // Copying attributes
  // Copying edges
  base::Base* pNewSingleEdge;
  pNewSingleEdge = getMappedNode(src->getCondition());
  if (pNewSingleEdge)
    dest->setCondition(dynamic_cast<expression::ExpressionSyntax*>(pNewSingleEdge));
  pNewSingleEdge = getMappedNode(src->getStatement());
  if (pNewSingleEdge)
    dest->setStatement(dynamic_cast<statement::StatementSyntax*>(pNewSingleEdge));
}

void AlgorithmDeepCopy::clone(statement::EmptyStatementSyntax* dest, const statement::EmptyStatementSyntax* src) {
  // Copying attributes
  // Copying edges
  // Copying attributes
  dest->setPosition(src->getPosition());
  // Copying edges
  // Copying attributes
  // Copying edges
  for ( ListIterator<structure::AttributeListSyntax> it = src->getAttributeListsListIteratorBegin(); it != src->getAttributeListsListIteratorEnd(); ++it ) {
    structure::AttributeListSyntax* pNewEdge = dynamic_cast<structure::AttributeListSyntax*>(getMappedNode(&(*it)));
    if (pNewEdge)
      dest->addAttributeLists(pNewEdge);
  }
  // Copying attributes
  // Copying edges
}

void AlgorithmDeepCopy::clone(statement::ExpressionStatementSyntax* dest, const statement::ExpressionStatementSyntax* src) {
  // Copying attributes
  // Copying edges
  // Copying attributes
  dest->setPosition(src->getPosition());
  // Copying edges
  // Copying attributes
  // Copying edges
  for ( ListIterator<structure::AttributeListSyntax> it = src->getAttributeListsListIteratorBegin(); it != src->getAttributeListsListIteratorEnd(); ++it ) {
    structure::AttributeListSyntax* pNewEdge = dynamic_cast<structure::AttributeListSyntax*>(getMappedNode(&(*it)));
    if (pNewEdge)
      dest->addAttributeLists(pNewEdge);
  }
  // Copying attributes
  // Copying edges
  base::Base* pNewSingleEdge;
  pNewSingleEdge = getMappedNode(src->getExpression());
  if (pNewSingleEdge)
    dest->setExpression(dynamic_cast<expression::ExpressionSyntax*>(pNewSingleEdge));
}

void AlgorithmDeepCopy::clone(statement::FixedStatementSyntax* dest, const statement::FixedStatementSyntax* src) {
  // Copying attributes
  // Copying edges
  // Copying attributes
  dest->setPosition(src->getPosition());
  // Copying edges
  // Copying attributes
  // Copying edges
  for ( ListIterator<structure::AttributeListSyntax> it = src->getAttributeListsListIteratorBegin(); it != src->getAttributeListsListIteratorEnd(); ++it ) {
    structure::AttributeListSyntax* pNewEdge = dynamic_cast<structure::AttributeListSyntax*>(getMappedNode(&(*it)));
    if (pNewEdge)
      dest->addAttributeLists(pNewEdge);
  }
  // Copying attributes
  // Copying edges
  base::Base* pNewSingleEdge;
  pNewSingleEdge = getMappedNode(src->getDeclaration());
  if (pNewSingleEdge)
    dest->setDeclaration(dynamic_cast<structure::VariableDeclarationSyntax*>(pNewSingleEdge));
  pNewSingleEdge = getMappedNode(src->getStatement());
  if (pNewSingleEdge)
    dest->setStatement(dynamic_cast<statement::StatementSyntax*>(pNewSingleEdge));
}

void AlgorithmDeepCopy::clone(statement::ForEachStatementSyntax* dest, const statement::ForEachStatementSyntax* src) {
  // Copying attributes
  // Copying edges
  // Copying attributes
  dest->setPosition(src->getPosition());
  // Copying edges
  // Copying attributes
  // Copying edges
  for ( ListIterator<structure::AttributeListSyntax> it = src->getAttributeListsListIteratorBegin(); it != src->getAttributeListsListIteratorEnd(); ++it ) {
    structure::AttributeListSyntax* pNewEdge = dynamic_cast<structure::AttributeListSyntax*>(getMappedNode(&(*it)));
    if (pNewEdge)
      dest->addAttributeLists(pNewEdge);
  }
  // Copying attributes
  // Copying edges
  base::Base* pNewSingleEdge;
  pNewSingleEdge = getMappedNode(src->getExpression());
  if (pNewSingleEdge)
    dest->setExpression(dynamic_cast<expression::ExpressionSyntax*>(pNewSingleEdge));
  pNewSingleEdge = getMappedNode(src->getStatement());
  if (pNewSingleEdge)
    dest->setStatement(dynamic_cast<statement::StatementSyntax*>(pNewSingleEdge));
  // Copying attributes
  dest->setIdentifier(src->getIdentifier());
  // Copying edges
  pNewSingleEdge = getMappedNode(src->getType());
  if (pNewSingleEdge)
    dest->setType(dynamic_cast<expression::TypeSyntax*>(pNewSingleEdge));
}

void AlgorithmDeepCopy::clone(statement::ForEachVariableStatementSyntax* dest, const statement::ForEachVariableStatementSyntax* src) {
  // Copying attributes
  // Copying edges
  // Copying attributes
  dest->setPosition(src->getPosition());
  // Copying edges
  // Copying attributes
  // Copying edges
  for ( ListIterator<structure::AttributeListSyntax> it = src->getAttributeListsListIteratorBegin(); it != src->getAttributeListsListIteratorEnd(); ++it ) {
    structure::AttributeListSyntax* pNewEdge = dynamic_cast<structure::AttributeListSyntax*>(getMappedNode(&(*it)));
    if (pNewEdge)
      dest->addAttributeLists(pNewEdge);
  }
  // Copying attributes
  // Copying edges
  base::Base* pNewSingleEdge;
  pNewSingleEdge = getMappedNode(src->getExpression());
  if (pNewSingleEdge)
    dest->setExpression(dynamic_cast<expression::ExpressionSyntax*>(pNewSingleEdge));
  pNewSingleEdge = getMappedNode(src->getStatement());
  if (pNewSingleEdge)
    dest->setStatement(dynamic_cast<statement::StatementSyntax*>(pNewSingleEdge));
  // Copying attributes
  // Copying edges
  pNewSingleEdge = getMappedNode(src->getVariable());
  if (pNewSingleEdge)
    dest->setVariable(dynamic_cast<expression::ExpressionSyntax*>(pNewSingleEdge));
}

void AlgorithmDeepCopy::clone(statement::ForStatementSyntax* dest, const statement::ForStatementSyntax* src) {
  // Copying attributes
  // Copying edges
  // Copying attributes
  dest->setPosition(src->getPosition());
  // Copying edges
  // Copying attributes
  // Copying edges
  for ( ListIterator<structure::AttributeListSyntax> it = src->getAttributeListsListIteratorBegin(); it != src->getAttributeListsListIteratorEnd(); ++it ) {
    structure::AttributeListSyntax* pNewEdge = dynamic_cast<structure::AttributeListSyntax*>(getMappedNode(&(*it)));
    if (pNewEdge)
      dest->addAttributeLists(pNewEdge);
  }
  // Copying attributes
  // Copying edges
  base::Base* pNewSingleEdge;
  pNewSingleEdge = getMappedNode(src->getCondition());
  if (pNewSingleEdge)
    dest->setCondition(dynamic_cast<expression::ExpressionSyntax*>(pNewSingleEdge));
  pNewSingleEdge = getMappedNode(src->getDeclaration());
  if (pNewSingleEdge)
    dest->setDeclaration(dynamic_cast<structure::VariableDeclarationSyntax*>(pNewSingleEdge));
  for ( ListIterator<expression::ExpressionSyntax> it = src->getIncrementorsListIteratorBegin(); it != src->getIncrementorsListIteratorEnd(); ++it ) {
    expression::ExpressionSyntax* pNewEdge = dynamic_cast<expression::ExpressionSyntax*>(getMappedNode(&(*it)));
    if (pNewEdge)
      dest->addIncrementors(pNewEdge);
  }
  for ( ListIterator<expression::ExpressionSyntax> it = src->getInitializersListIteratorBegin(); it != src->getInitializersListIteratorEnd(); ++it ) {
    expression::ExpressionSyntax* pNewEdge = dynamic_cast<expression::ExpressionSyntax*>(getMappedNode(&(*it)));
    if (pNewEdge)
      dest->addInitializers(pNewEdge);
  }
  pNewSingleEdge = getMappedNode(src->getStatement());
  if (pNewSingleEdge)
    dest->setStatement(dynamic_cast<statement::StatementSyntax*>(pNewSingleEdge));
}

void AlgorithmDeepCopy::clone(statement::GotoStatementSyntax* dest, const statement::GotoStatementSyntax* src) {
  // Copying attributes
  // Copying edges
  // Copying attributes
  dest->setPosition(src->getPosition());
  // Copying edges
  // Copying attributes
  // Copying edges
  for ( ListIterator<structure::AttributeListSyntax> it = src->getAttributeListsListIteratorBegin(); it != src->getAttributeListsListIteratorEnd(); ++it ) {
    structure::AttributeListSyntax* pNewEdge = dynamic_cast<structure::AttributeListSyntax*>(getMappedNode(&(*it)));
    if (pNewEdge)
      dest->addAttributeLists(pNewEdge);
  }
  // Copying attributes
  // Copying edges
  base::Base* pNewSingleEdge;
  pNewSingleEdge = getMappedNode(src->getExpression());
  if (pNewSingleEdge)
    dest->setExpression(dynamic_cast<expression::ExpressionSyntax*>(pNewSingleEdge));
}

void AlgorithmDeepCopy::clone(statement::IfStatementSyntax* dest, const statement::IfStatementSyntax* src) {
  // Copying attributes
  // Copying edges
  // Copying attributes
  dest->setPosition(src->getPosition());
  // Copying edges
  // Copying attributes
  // Copying edges
  for ( ListIterator<structure::AttributeListSyntax> it = src->getAttributeListsListIteratorBegin(); it != src->getAttributeListsListIteratorEnd(); ++it ) {
    structure::AttributeListSyntax* pNewEdge = dynamic_cast<structure::AttributeListSyntax*>(getMappedNode(&(*it)));
    if (pNewEdge)
      dest->addAttributeLists(pNewEdge);
  }
  // Copying attributes
  // Copying edges
  base::Base* pNewSingleEdge;
  pNewSingleEdge = getMappedNode(src->getCondition());
  if (pNewSingleEdge)
    dest->setCondition(dynamic_cast<expression::ExpressionSyntax*>(pNewSingleEdge));
  pNewSingleEdge = getMappedNode(src->getElse());
  if (pNewSingleEdge)
    dest->setElse(dynamic_cast<structure::ElseClauseSyntax*>(pNewSingleEdge));
  pNewSingleEdge = getMappedNode(src->getStatement());
  if (pNewSingleEdge)
    dest->setStatement(dynamic_cast<statement::StatementSyntax*>(pNewSingleEdge));
}

void AlgorithmDeepCopy::clone(statement::LabeledStatementSyntax* dest, const statement::LabeledStatementSyntax* src) {
  // Copying attributes
  // Copying edges
  // Copying attributes
  dest->setPosition(src->getPosition());
  // Copying edges
  // Copying attributes
  // Copying edges
  for ( ListIterator<structure::AttributeListSyntax> it = src->getAttributeListsListIteratorBegin(); it != src->getAttributeListsListIteratorEnd(); ++it ) {
    structure::AttributeListSyntax* pNewEdge = dynamic_cast<structure::AttributeListSyntax*>(getMappedNode(&(*it)));
    if (pNewEdge)
      dest->addAttributeLists(pNewEdge);
  }
  // Copying attributes
  dest->setIdentifier(src->getIdentifier());
  // Copying edges
  base::Base* pNewSingleEdge;
  pNewSingleEdge = getMappedNode(src->getStatement());
  if (pNewSingleEdge)
    dest->setStatement(dynamic_cast<statement::StatementSyntax*>(pNewSingleEdge));
}

void AlgorithmDeepCopy::clone(statement::LocalDeclarationStatementSyntax* dest, const statement::LocalDeclarationStatementSyntax* src) {
  // Copying attributes
  // Copying edges
  // Copying attributes
  dest->setPosition(src->getPosition());
  // Copying edges
  // Copying attributes
  // Copying edges
  for ( ListIterator<structure::AttributeListSyntax> it = src->getAttributeListsListIteratorBegin(); it != src->getAttributeListsListIteratorEnd(); ++it ) {
    structure::AttributeListSyntax* pNewEdge = dynamic_cast<structure::AttributeListSyntax*>(getMappedNode(&(*it)));
    if (pNewEdge)
      dest->addAttributeLists(pNewEdge);
  }
  // Copying attributes
  // Copying edges
  base::Base* pNewSingleEdge;
  pNewSingleEdge = getMappedNode(src->getDeclaration());
  if (pNewSingleEdge)
    dest->setDeclaration(dynamic_cast<structure::VariableDeclarationSyntax*>(pNewSingleEdge));
}

void AlgorithmDeepCopy::clone(statement::LocalFunctionStatementSyntax* dest, const statement::LocalFunctionStatementSyntax* src) {
  // Copying attributes
  // Copying edges
  // Copying attributes
  dest->setPosition(src->getPosition());
  // Copying edges
  // Copying attributes
  // Copying edges
  for ( ListIterator<structure::AttributeListSyntax> it = src->getAttributeListsListIteratorBegin(); it != src->getAttributeListsListIteratorEnd(); ++it ) {
    structure::AttributeListSyntax* pNewEdge = dynamic_cast<structure::AttributeListSyntax*>(getMappedNode(&(*it)));
    if (pNewEdge)
      dest->addAttributeLists(pNewEdge);
  }
  // Copying attributes
  dest->setIdentifier(src->getIdentifier());
  // Copying edges
  base::Base* pNewSingleEdge;
  pNewSingleEdge = getMappedNode(src->getBody());
  if (pNewSingleEdge)
    dest->setBody(dynamic_cast<statement::BlockSyntax*>(pNewSingleEdge));
  for ( ListIterator<structure::TypeParameterConstraintClauseSyntax> it = src->getConstraintClausesListIteratorBegin(); it != src->getConstraintClausesListIteratorEnd(); ++it ) {
    structure::TypeParameterConstraintClauseSyntax* pNewEdge = dynamic_cast<structure::TypeParameterConstraintClauseSyntax*>(getMappedNode(&(*it)));
    if (pNewEdge)
      dest->addConstraintClauses(pNewEdge);
  }
  pNewSingleEdge = getMappedNode(src->getExpressionBody());
  if (pNewSingleEdge)
    dest->setExpressionBody(dynamic_cast<structure::ArrowExpressionClauseSyntax*>(pNewSingleEdge));
  pNewSingleEdge = getMappedNode(src->getParameterList());
  if (pNewSingleEdge)
    dest->setParameterList(dynamic_cast<structure::ParameterListSyntax*>(pNewSingleEdge));
  pNewSingleEdge = getMappedNode(src->getReturnType());
  if (pNewSingleEdge)
    dest->setReturnType(dynamic_cast<expression::TypeSyntax*>(pNewSingleEdge));
  pNewSingleEdge = getMappedNode(src->getTypeParameterList());
  if (pNewSingleEdge)
    dest->setTypeParameterList(dynamic_cast<structure::TypeParameterListSyntax*>(pNewSingleEdge));
}

void AlgorithmDeepCopy::clone(statement::LockStatementSyntax* dest, const statement::LockStatementSyntax* src) {
  // Copying attributes
  // Copying edges
  // Copying attributes
  dest->setPosition(src->getPosition());
  // Copying edges
  // Copying attributes
  // Copying edges
  for ( ListIterator<structure::AttributeListSyntax> it = src->getAttributeListsListIteratorBegin(); it != src->getAttributeListsListIteratorEnd(); ++it ) {
    structure::AttributeListSyntax* pNewEdge = dynamic_cast<structure::AttributeListSyntax*>(getMappedNode(&(*it)));
    if (pNewEdge)
      dest->addAttributeLists(pNewEdge);
  }
  // Copying attributes
  // Copying edges
  base::Base* pNewSingleEdge;
  pNewSingleEdge = getMappedNode(src->getExpression());
  if (pNewSingleEdge)
    dest->setExpression(dynamic_cast<expression::ExpressionSyntax*>(pNewSingleEdge));
  pNewSingleEdge = getMappedNode(src->getStatement());
  if (pNewSingleEdge)
    dest->setStatement(dynamic_cast<statement::StatementSyntax*>(pNewSingleEdge));
}

void AlgorithmDeepCopy::clone(statement::ReturnStatementSyntax* dest, const statement::ReturnStatementSyntax* src) {
  // Copying attributes
  // Copying edges
  // Copying attributes
  dest->setPosition(src->getPosition());
  // Copying edges
  // Copying attributes
  // Copying edges
  for ( ListIterator<structure::AttributeListSyntax> it = src->getAttributeListsListIteratorBegin(); it != src->getAttributeListsListIteratorEnd(); ++it ) {
    structure::AttributeListSyntax* pNewEdge = dynamic_cast<structure::AttributeListSyntax*>(getMappedNode(&(*it)));
    if (pNewEdge)
      dest->addAttributeLists(pNewEdge);
  }
  // Copying attributes
  // Copying edges
  base::Base* pNewSingleEdge;
  pNewSingleEdge = getMappedNode(src->getExpression());
  if (pNewSingleEdge)
    dest->setExpression(dynamic_cast<expression::ExpressionSyntax*>(pNewSingleEdge));
}

void AlgorithmDeepCopy::clone(statement::StatementSyntax* dest, const statement::StatementSyntax* src) {
  // Copying attributes
  // Copying edges
  // Copying attributes
  dest->setPosition(src->getPosition());
  // Copying edges
  // Copying attributes
  // Copying edges
  for ( ListIterator<structure::AttributeListSyntax> it = src->getAttributeListsListIteratorBegin(); it != src->getAttributeListsListIteratorEnd(); ++it ) {
    structure::AttributeListSyntax* pNewEdge = dynamic_cast<structure::AttributeListSyntax*>(getMappedNode(&(*it)));
    if (pNewEdge)
      dest->addAttributeLists(pNewEdge);
  }
}

void AlgorithmDeepCopy::clone(statement::SwitchStatementSyntax* dest, const statement::SwitchStatementSyntax* src) {
  // Copying attributes
  // Copying edges
  // Copying attributes
  dest->setPosition(src->getPosition());
  // Copying edges
  // Copying attributes
  // Copying edges
  for ( ListIterator<structure::AttributeListSyntax> it = src->getAttributeListsListIteratorBegin(); it != src->getAttributeListsListIteratorEnd(); ++it ) {
    structure::AttributeListSyntax* pNewEdge = dynamic_cast<structure::AttributeListSyntax*>(getMappedNode(&(*it)));
    if (pNewEdge)
      dest->addAttributeLists(pNewEdge);
  }
  // Copying attributes
  // Copying edges
  base::Base* pNewSingleEdge;
  pNewSingleEdge = getMappedNode(src->getExpression());
  if (pNewSingleEdge)
    dest->setExpression(dynamic_cast<expression::ExpressionSyntax*>(pNewSingleEdge));
  for ( ListIterator<structure::SwitchSectionSyntax> it = src->getSectionsListIteratorBegin(); it != src->getSectionsListIteratorEnd(); ++it ) {
    structure::SwitchSectionSyntax* pNewEdge = dynamic_cast<structure::SwitchSectionSyntax*>(getMappedNode(&(*it)));
    if (pNewEdge)
      dest->addSections(pNewEdge);
  }
}

void AlgorithmDeepCopy::clone(statement::ThrowStatementSyntax* dest, const statement::ThrowStatementSyntax* src) {
  // Copying attributes
  // Copying edges
  // Copying attributes
  dest->setPosition(src->getPosition());
  // Copying edges
  // Copying attributes
  // Copying edges
  for ( ListIterator<structure::AttributeListSyntax> it = src->getAttributeListsListIteratorBegin(); it != src->getAttributeListsListIteratorEnd(); ++it ) {
    structure::AttributeListSyntax* pNewEdge = dynamic_cast<structure::AttributeListSyntax*>(getMappedNode(&(*it)));
    if (pNewEdge)
      dest->addAttributeLists(pNewEdge);
  }
  // Copying attributes
  // Copying edges
  base::Base* pNewSingleEdge;
  pNewSingleEdge = getMappedNode(src->getExpression());
  if (pNewSingleEdge)
    dest->setExpression(dynamic_cast<expression::ExpressionSyntax*>(pNewSingleEdge));
}

void AlgorithmDeepCopy::clone(statement::TryStatementSyntax* dest, const statement::TryStatementSyntax* src) {
  // Copying attributes
  // Copying edges
  // Copying attributes
  dest->setPosition(src->getPosition());
  // Copying edges
  // Copying attributes
  // Copying edges
  for ( ListIterator<structure::AttributeListSyntax> it = src->getAttributeListsListIteratorBegin(); it != src->getAttributeListsListIteratorEnd(); ++it ) {
    structure::AttributeListSyntax* pNewEdge = dynamic_cast<structure::AttributeListSyntax*>(getMappedNode(&(*it)));
    if (pNewEdge)
      dest->addAttributeLists(pNewEdge);
  }
  // Copying attributes
  // Copying edges
  base::Base* pNewSingleEdge;
  pNewSingleEdge = getMappedNode(src->getBlock());
  if (pNewSingleEdge)
    dest->setBlock(dynamic_cast<statement::BlockSyntax*>(pNewSingleEdge));
  for ( ListIterator<structure::CatchClauseSyntax> it = src->getCatchesListIteratorBegin(); it != src->getCatchesListIteratorEnd(); ++it ) {
    structure::CatchClauseSyntax* pNewEdge = dynamic_cast<structure::CatchClauseSyntax*>(getMappedNode(&(*it)));
    if (pNewEdge)
      dest->addCatches(pNewEdge);
  }
  pNewSingleEdge = getMappedNode(src->getFinally());
  if (pNewSingleEdge)
    dest->setFinally(dynamic_cast<structure::FinallyClauseSyntax*>(pNewSingleEdge));
}

void AlgorithmDeepCopy::clone(statement::UnsafeStatementSyntax* dest, const statement::UnsafeStatementSyntax* src) {
  // Copying attributes
  // Copying edges
  // Copying attributes
  dest->setPosition(src->getPosition());
  // Copying edges
  // Copying attributes
  // Copying edges
  for ( ListIterator<structure::AttributeListSyntax> it = src->getAttributeListsListIteratorBegin(); it != src->getAttributeListsListIteratorEnd(); ++it ) {
    structure::AttributeListSyntax* pNewEdge = dynamic_cast<structure::AttributeListSyntax*>(getMappedNode(&(*it)));
    if (pNewEdge)
      dest->addAttributeLists(pNewEdge);
  }
  // Copying attributes
  // Copying edges
  base::Base* pNewSingleEdge;
  pNewSingleEdge = getMappedNode(src->getBlock());
  if (pNewSingleEdge)
    dest->setBlock(dynamic_cast<statement::BlockSyntax*>(pNewSingleEdge));
}

void AlgorithmDeepCopy::clone(statement::UsingStatementSyntax* dest, const statement::UsingStatementSyntax* src) {
  // Copying attributes
  // Copying edges
  // Copying attributes
  dest->setPosition(src->getPosition());
  // Copying edges
  // Copying attributes
  // Copying edges
  for ( ListIterator<structure::AttributeListSyntax> it = src->getAttributeListsListIteratorBegin(); it != src->getAttributeListsListIteratorEnd(); ++it ) {
    structure::AttributeListSyntax* pNewEdge = dynamic_cast<structure::AttributeListSyntax*>(getMappedNode(&(*it)));
    if (pNewEdge)
      dest->addAttributeLists(pNewEdge);
  }
  // Copying attributes
  // Copying edges
  base::Base* pNewSingleEdge;
  pNewSingleEdge = getMappedNode(src->getDeclaration());
  if (pNewSingleEdge)
    dest->setDeclaration(dynamic_cast<structure::VariableDeclarationSyntax*>(pNewSingleEdge));
  pNewSingleEdge = getMappedNode(src->getExpression());
  if (pNewSingleEdge)
    dest->setExpression(dynamic_cast<expression::ExpressionSyntax*>(pNewSingleEdge));
  pNewSingleEdge = getMappedNode(src->getStatement());
  if (pNewSingleEdge)
    dest->setStatement(dynamic_cast<statement::StatementSyntax*>(pNewSingleEdge));
}

void AlgorithmDeepCopy::clone(statement::WhileStatementSyntax* dest, const statement::WhileStatementSyntax* src) {
  // Copying attributes
  // Copying edges
  // Copying attributes
  dest->setPosition(src->getPosition());
  // Copying edges
  // Copying attributes
  // Copying edges
  for ( ListIterator<structure::AttributeListSyntax> it = src->getAttributeListsListIteratorBegin(); it != src->getAttributeListsListIteratorEnd(); ++it ) {
    structure::AttributeListSyntax* pNewEdge = dynamic_cast<structure::AttributeListSyntax*>(getMappedNode(&(*it)));
    if (pNewEdge)
      dest->addAttributeLists(pNewEdge);
  }
  // Copying attributes
  // Copying edges
  base::Base* pNewSingleEdge;
  pNewSingleEdge = getMappedNode(src->getCondition());
  if (pNewSingleEdge)
    dest->setCondition(dynamic_cast<expression::ExpressionSyntax*>(pNewSingleEdge));
  pNewSingleEdge = getMappedNode(src->getStatement());
  if (pNewSingleEdge)
    dest->setStatement(dynamic_cast<statement::StatementSyntax*>(pNewSingleEdge));
}

void AlgorithmDeepCopy::clone(statement::YieldStatementSyntax* dest, const statement::YieldStatementSyntax* src) {
  // Copying attributes
  // Copying edges
  // Copying attributes
  dest->setPosition(src->getPosition());
  // Copying edges
  // Copying attributes
  // Copying edges
  for ( ListIterator<structure::AttributeListSyntax> it = src->getAttributeListsListIteratorBegin(); it != src->getAttributeListsListIteratorEnd(); ++it ) {
    structure::AttributeListSyntax* pNewEdge = dynamic_cast<structure::AttributeListSyntax*>(getMappedNode(&(*it)));
    if (pNewEdge)
      dest->addAttributeLists(pNewEdge);
  }
  // Copying attributes
  // Copying edges
  base::Base* pNewSingleEdge;
  pNewSingleEdge = getMappedNode(src->getExpression());
  if (pNewSingleEdge)
    dest->setExpression(dynamic_cast<expression::ExpressionSyntax*>(pNewSingleEdge));
}

void AlgorithmDeepCopy::clone(structure::AccessorDeclarationSyntax* dest, const structure::AccessorDeclarationSyntax* src) {
  // Copying attributes
  // Copying edges
  // Copying attributes
  dest->setPosition(src->getPosition());
  // Copying edges
  // Copying attributes
  dest->setIdentifier(src->getIdentifier());
  // Copying edges
  for ( ListIterator<structure::AttributeListSyntax> it = src->getAttributeListsListIteratorBegin(); it != src->getAttributeListsListIteratorEnd(); ++it ) {
    structure::AttributeListSyntax* pNewEdge = dynamic_cast<structure::AttributeListSyntax*>(getMappedNode(&(*it)));
    if (pNewEdge)
      dest->addAttributeLists(pNewEdge);
  }
  base::Base* pNewSingleEdge;
  pNewSingleEdge = getMappedNode(src->getBody());
  if (pNewSingleEdge)
    dest->setBody(dynamic_cast<statement::BlockSyntax*>(pNewSingleEdge));
  pNewSingleEdge = getMappedNode(src->getExpressionBody());
  if (pNewSingleEdge)
    dest->setExpressionBody(dynamic_cast<structure::ArrowExpressionClauseSyntax*>(pNewSingleEdge));
}

void AlgorithmDeepCopy::clone(structure::AccessorListSyntax* dest, const structure::AccessorListSyntax* src) {
  // Copying attributes
  // Copying edges
  // Copying attributes
  dest->setPosition(src->getPosition());
  // Copying edges
  // Copying attributes
  // Copying edges
  for ( ListIterator<structure::AccessorDeclarationSyntax> it = src->getAccessorsListIteratorBegin(); it != src->getAccessorsListIteratorEnd(); ++it ) {
    structure::AccessorDeclarationSyntax* pNewEdge = dynamic_cast<structure::AccessorDeclarationSyntax*>(getMappedNode(&(*it)));
    if (pNewEdge)
      dest->addAccessors(pNewEdge);
  }
}

void AlgorithmDeepCopy::clone(structure::AnonymousObjectMemberDeclaratorSyntax* dest, const structure::AnonymousObjectMemberDeclaratorSyntax* src) {
  // Copying attributes
  // Copying edges
  // Copying attributes
  dest->setPosition(src->getPosition());
  // Copying edges
  // Copying attributes
  // Copying edges
  base::Base* pNewSingleEdge;
  pNewSingleEdge = getMappedNode(src->getExpression());
  if (pNewSingleEdge)
    dest->setExpression(dynamic_cast<expression::ExpressionSyntax*>(pNewSingleEdge));
  pNewSingleEdge = getMappedNode(src->getNameEquals());
  if (pNewSingleEdge)
    dest->setNameEquals(dynamic_cast<structure::NameEqualsSyntax*>(pNewSingleEdge));
}

void AlgorithmDeepCopy::clone(structure::ArgumentListSyntax* dest, const structure::ArgumentListSyntax* src) {
  // Copying attributes
  // Copying edges
  // Copying attributes
  dest->setPosition(src->getPosition());
  // Copying edges
  // Copying attributes
  // Copying edges
  for ( ListIterator<structure::ArgumentSyntax> it = src->getArgumentsListIteratorBegin(); it != src->getArgumentsListIteratorEnd(); ++it ) {
    structure::ArgumentSyntax* pNewEdge = dynamic_cast<structure::ArgumentSyntax*>(getMappedNode(&(*it)));
    if (pNewEdge)
      dest->addArguments(pNewEdge);
  }
  // Copying attributes
  // Copying edges
}

void AlgorithmDeepCopy::clone(structure::ArgumentSyntax* dest, const structure::ArgumentSyntax* src) {
  // Copying attributes
  // Copying edges
  // Copying attributes
  dest->setPosition(src->getPosition());
  // Copying edges
  // Copying attributes
  // Copying edges
  base::Base* pNewSingleEdge;
  pNewSingleEdge = getMappedNode(src->getExpression());
  if (pNewSingleEdge)
    dest->setExpression(dynamic_cast<expression::ExpressionSyntax*>(pNewSingleEdge));
  pNewSingleEdge = getMappedNode(src->getNameColon());
  if (pNewSingleEdge)
    dest->setNameColon(dynamic_cast<structure::NameColonSyntax*>(pNewSingleEdge));
}

void AlgorithmDeepCopy::clone(structure::ArrayRankSpecifierSyntax* dest, const structure::ArrayRankSpecifierSyntax* src) {
  // Copying attributes
  // Copying edges
  // Copying attributes
  dest->setPosition(src->getPosition());
  // Copying edges
  // Copying attributes
  // Copying edges
  for ( ListIterator<expression::ExpressionSyntax> it = src->getSizesListIteratorBegin(); it != src->getSizesListIteratorEnd(); ++it ) {
    expression::ExpressionSyntax* pNewEdge = dynamic_cast<expression::ExpressionSyntax*>(getMappedNode(&(*it)));
    if (pNewEdge)
      dest->addSizes(pNewEdge);
  }
}

void AlgorithmDeepCopy::clone(structure::ArrowExpressionClauseSyntax* dest, const structure::ArrowExpressionClauseSyntax* src) {
  // Copying attributes
  // Copying edges
  // Copying attributes
  dest->setPosition(src->getPosition());
  // Copying edges
  // Copying attributes
  // Copying edges
  base::Base* pNewSingleEdge;
  pNewSingleEdge = getMappedNode(src->getExpression());
  if (pNewSingleEdge)
    dest->setExpression(dynamic_cast<expression::ExpressionSyntax*>(pNewSingleEdge));
}

void AlgorithmDeepCopy::clone(structure::AttributeArgumentListSyntax* dest, const structure::AttributeArgumentListSyntax* src) {
  // Copying attributes
  // Copying edges
  // Copying attributes
  dest->setPosition(src->getPosition());
  // Copying edges
  // Copying attributes
  // Copying edges
  for ( ListIterator<structure::AttributeArgumentSyntax> it = src->getArgumentsListIteratorBegin(); it != src->getArgumentsListIteratorEnd(); ++it ) {
    structure::AttributeArgumentSyntax* pNewEdge = dynamic_cast<structure::AttributeArgumentSyntax*>(getMappedNode(&(*it)));
    if (pNewEdge)
      dest->addArguments(pNewEdge);
  }
}

void AlgorithmDeepCopy::clone(structure::AttributeArgumentSyntax* dest, const structure::AttributeArgumentSyntax* src) {
  // Copying attributes
  // Copying edges
  // Copying attributes
  dest->setPosition(src->getPosition());
  // Copying edges
  // Copying attributes
  // Copying edges
  base::Base* pNewSingleEdge;
  pNewSingleEdge = getMappedNode(src->getExpression());
  if (pNewSingleEdge)
    dest->setExpression(dynamic_cast<expression::ExpressionSyntax*>(pNewSingleEdge));
  pNewSingleEdge = getMappedNode(src->getNameColon());
  if (pNewSingleEdge)
    dest->setNameColon(dynamic_cast<structure::NameColonSyntax*>(pNewSingleEdge));
  pNewSingleEdge = getMappedNode(src->getNameEquals());
  if (pNewSingleEdge)
    dest->setNameEquals(dynamic_cast<structure::NameEqualsSyntax*>(pNewSingleEdge));
}

void AlgorithmDeepCopy::clone(structure::AttributeListSyntax* dest, const structure::AttributeListSyntax* src) {
  // Copying attributes
  // Copying edges
  // Copying attributes
  dest->setPosition(src->getPosition());
  // Copying edges
  // Copying attributes
  // Copying edges
  for ( ListIterator<structure::AttributeSyntax> it = src->getAttributesListIteratorBegin(); it != src->getAttributesListIteratorEnd(); ++it ) {
    structure::AttributeSyntax* pNewEdge = dynamic_cast<structure::AttributeSyntax*>(getMappedNode(&(*it)));
    if (pNewEdge)
      dest->addAttributes(pNewEdge);
  }
  base::Base* pNewSingleEdge;
  pNewSingleEdge = getMappedNode(src->getTarget());
  if (pNewSingleEdge)
    dest->setTarget(dynamic_cast<structure::AttributeTargetSpecifierSyntax*>(pNewSingleEdge));
}

void AlgorithmDeepCopy::clone(structure::AttributeSyntax* dest, const structure::AttributeSyntax* src) {
  // Copying attributes
  // Copying edges
  // Copying attributes
  dest->setPosition(src->getPosition());
  // Copying edges
  // Copying attributes
  // Copying edges
  base::Base* pNewSingleEdge;
  pNewSingleEdge = getMappedNode(src->getArgumentList());
  if (pNewSingleEdge)
    dest->setArgumentList(dynamic_cast<structure::AttributeArgumentListSyntax*>(pNewSingleEdge));
  pNewSingleEdge = getMappedNode(src->getName());
  if (pNewSingleEdge)
    dest->setName(dynamic_cast<expression::NameSyntax*>(pNewSingleEdge));
}

void AlgorithmDeepCopy::clone(structure::AttributeTargetSpecifierSyntax* dest, const structure::AttributeTargetSpecifierSyntax* src) {
  // Copying attributes
  // Copying edges
  // Copying attributes
  dest->setPosition(src->getPosition());
  // Copying edges
  // Copying attributes
  dest->setIdentifier(src->getIdentifier());
  // Copying edges
}

void AlgorithmDeepCopy::clone(structure::BaseArgumentListSyntax* dest, const structure::BaseArgumentListSyntax* src) {
  // Copying attributes
  // Copying edges
  // Copying attributes
  dest->setPosition(src->getPosition());
  // Copying edges
  // Copying attributes
  // Copying edges
  for ( ListIterator<structure::ArgumentSyntax> it = src->getArgumentsListIteratorBegin(); it != src->getArgumentsListIteratorEnd(); ++it ) {
    structure::ArgumentSyntax* pNewEdge = dynamic_cast<structure::ArgumentSyntax*>(getMappedNode(&(*it)));
    if (pNewEdge)
      dest->addArguments(pNewEdge);
  }
}

void AlgorithmDeepCopy::clone(structure::BaseCrefParameterListSyntax* dest, const structure::BaseCrefParameterListSyntax* src) {
  // Copying attributes
  // Copying edges
  // Copying attributes
  dest->setPosition(src->getPosition());
  // Copying edges
  // Copying attributes
  // Copying edges
  for ( ListIterator<structure::CrefParameterSyntax> it = src->getParametersListIteratorBegin(); it != src->getParametersListIteratorEnd(); ++it ) {
    structure::CrefParameterSyntax* pNewEdge = dynamic_cast<structure::CrefParameterSyntax*>(getMappedNode(&(*it)));
    if (pNewEdge)
      dest->addParameters(pNewEdge);
  }
}

void AlgorithmDeepCopy::clone(structure::BaseFieldDeclarationSyntax* dest, const structure::BaseFieldDeclarationSyntax* src) {
  // Copying attributes
  // Copying edges
  // Copying attributes
  dest->setPosition(src->getPosition());
  // Copying edges
  // Copying attributes
  // Copying edges
  // Copying attributes
  // Copying edges
  for ( ListIterator<structure::AttributeListSyntax> it = src->getAttributeListsListIteratorBegin(); it != src->getAttributeListsListIteratorEnd(); ++it ) {
    structure::AttributeListSyntax* pNewEdge = dynamic_cast<structure::AttributeListSyntax*>(getMappedNode(&(*it)));
    if (pNewEdge)
      dest->addAttributeLists(pNewEdge);
  }
  base::Base* pNewSingleEdge;
  pNewSingleEdge = getMappedNode(src->getDeclaration());
  if (pNewSingleEdge)
    dest->setDeclaration(dynamic_cast<structure::VariableDeclarationSyntax*>(pNewSingleEdge));
}

void AlgorithmDeepCopy::clone(structure::BaseListSyntax* dest, const structure::BaseListSyntax* src) {
  // Copying attributes
  // Copying edges
  // Copying attributes
  dest->setPosition(src->getPosition());
  // Copying edges
  // Copying attributes
  // Copying edges
  for ( ListIterator<structure::BaseTypeSyntax> it = src->getTypesListIteratorBegin(); it != src->getTypesListIteratorEnd(); ++it ) {
    structure::BaseTypeSyntax* pNewEdge = dynamic_cast<structure::BaseTypeSyntax*>(getMappedNode(&(*it)));
    if (pNewEdge)
      dest->addTypes(pNewEdge);
  }
}

void AlgorithmDeepCopy::clone(structure::BaseMethodDeclarationSyntax* dest, const structure::BaseMethodDeclarationSyntax* src) {
  // Copying attributes
  // Copying edges
  // Copying attributes
  dest->setPosition(src->getPosition());
  // Copying edges
  // Copying attributes
  // Copying edges
  // Copying attributes
  // Copying edges
  for ( ListIterator<structure::EnumMemberDeclarationSyntax> it = src->getAccessedEnumMembersListIteratorBegin(); it != src->getAccessedEnumMembersListIteratorEnd(); ++it ) {
    structure::EnumMemberDeclarationSyntax* pNewEdge = dynamic_cast<structure::EnumMemberDeclarationSyntax*>(getMappedNode(&(*it)));
    if (pNewEdge)
      dest->addAccessedEnumMembers(pNewEdge);
  }
  for ( ListIterator<structure::AttributeListSyntax> it = src->getAttributeListsListIteratorBegin(); it != src->getAttributeListsListIteratorEnd(); ++it ) {
    structure::AttributeListSyntax* pNewEdge = dynamic_cast<structure::AttributeListSyntax*>(getMappedNode(&(*it)));
    if (pNewEdge)
      dest->addAttributeLists(pNewEdge);
  }
  base::Base* pNewSingleEdge;
  pNewSingleEdge = getMappedNode(src->getBody());
  if (pNewSingleEdge)
    dest->setBody(dynamic_cast<statement::BlockSyntax*>(pNewSingleEdge));
  pNewSingleEdge = getMappedNode(src->getExpressionBody());
  if (pNewSingleEdge)
    dest->setExpressionBody(dynamic_cast<structure::ArrowExpressionClauseSyntax*>(pNewSingleEdge));
  pNewSingleEdge = getMappedNode(src->getParameterList());
  if (pNewSingleEdge)
    dest->setParameterList(dynamic_cast<structure::ParameterListSyntax*>(pNewSingleEdge));
}

void AlgorithmDeepCopy::clone(structure::BaseParameterListSyntax* dest, const structure::BaseParameterListSyntax* src) {
  // Copying attributes
  // Copying edges
  // Copying attributes
  dest->setPosition(src->getPosition());
  // Copying edges
  // Copying attributes
  // Copying edges
  for ( ListIterator<structure::ParameterSyntax> it = src->getParametersListIteratorBegin(); it != src->getParametersListIteratorEnd(); ++it ) {
    structure::ParameterSyntax* pNewEdge = dynamic_cast<structure::ParameterSyntax*>(getMappedNode(&(*it)));
    if (pNewEdge)
      dest->addParameters(pNewEdge);
  }
}

void AlgorithmDeepCopy::clone(structure::BasePropertyDeclarationSyntax* dest, const structure::BasePropertyDeclarationSyntax* src) {
  // Copying attributes
  // Copying edges
  // Copying attributes
  dest->setPosition(src->getPosition());
  // Copying edges
  // Copying attributes
  // Copying edges
  // Copying attributes
  // Copying edges
  base::Base* pNewSingleEdge;
  pNewSingleEdge = getMappedNode(src->getAccessorList());
  if (pNewSingleEdge)
    dest->setAccessorList(dynamic_cast<structure::AccessorListSyntax*>(pNewSingleEdge));
  for ( ListIterator<structure::AttributeListSyntax> it = src->getAttributeListsListIteratorBegin(); it != src->getAttributeListsListIteratorEnd(); ++it ) {
    structure::AttributeListSyntax* pNewEdge = dynamic_cast<structure::AttributeListSyntax*>(getMappedNode(&(*it)));
    if (pNewEdge)
      dest->addAttributeLists(pNewEdge);
  }
  pNewSingleEdge = getMappedNode(src->getExplicitInterfaceSpecifier());
  if (pNewSingleEdge)
    dest->setExplicitInterfaceSpecifier(dynamic_cast<structure::ExplicitInterfaceSpecifierSyntax*>(pNewSingleEdge));
  pNewSingleEdge = getMappedNode(src->getType());
  if (pNewSingleEdge)
    dest->setType(dynamic_cast<expression::TypeSyntax*>(pNewSingleEdge));
}

void AlgorithmDeepCopy::clone(structure::BaseTypeDeclarationSyntax* dest, const structure::BaseTypeDeclarationSyntax* src) {
  // Copying attributes
  // Copying edges
  // Copying attributes
  dest->setPosition(src->getPosition());
  // Copying edges
  // Copying attributes
  // Copying edges
  // Copying attributes
  dest->setIdentifier(src->getIdentifier());
  // Copying edges
  for ( ListIterator<structure::AttributeListSyntax> it = src->getAttributeListsListIteratorBegin(); it != src->getAttributeListsListIteratorEnd(); ++it ) {
    structure::AttributeListSyntax* pNewEdge = dynamic_cast<structure::AttributeListSyntax*>(getMappedNode(&(*it)));
    if (pNewEdge)
      dest->addAttributeLists(pNewEdge);
  }
  base::Base* pNewSingleEdge;
  pNewSingleEdge = getMappedNode(src->getBaseList());
  if (pNewSingleEdge)
    dest->setBaseList(dynamic_cast<structure::BaseListSyntax*>(pNewSingleEdge));
}

void AlgorithmDeepCopy::clone(structure::BaseTypeSyntax* dest, const structure::BaseTypeSyntax* src) {
  // Copying attributes
  // Copying edges
  // Copying attributes
  dest->setPosition(src->getPosition());
  // Copying edges
  // Copying attributes
  // Copying edges
  base::Base* pNewSingleEdge;
  pNewSingleEdge = getMappedNode(src->getType());
  if (pNewSingleEdge)
    dest->setType(dynamic_cast<expression::TypeSyntax*>(pNewSingleEdge));
}

void AlgorithmDeepCopy::clone(structure::BracketedArgumentListSyntax* dest, const structure::BracketedArgumentListSyntax* src) {
  // Copying attributes
  // Copying edges
  // Copying attributes
  dest->setPosition(src->getPosition());
  // Copying edges
  // Copying attributes
  // Copying edges
  for ( ListIterator<structure::ArgumentSyntax> it = src->getArgumentsListIteratorBegin(); it != src->getArgumentsListIteratorEnd(); ++it ) {
    structure::ArgumentSyntax* pNewEdge = dynamic_cast<structure::ArgumentSyntax*>(getMappedNode(&(*it)));
    if (pNewEdge)
      dest->addArguments(pNewEdge);
  }
  // Copying attributes
  // Copying edges
}

void AlgorithmDeepCopy::clone(structure::BracketedParameterListSyntax* dest, const structure::BracketedParameterListSyntax* src) {
  // Copying attributes
  // Copying edges
  // Copying attributes
  dest->setPosition(src->getPosition());
  // Copying edges
  // Copying attributes
  // Copying edges
  for ( ListIterator<structure::ParameterSyntax> it = src->getParametersListIteratorBegin(); it != src->getParametersListIteratorEnd(); ++it ) {
    structure::ParameterSyntax* pNewEdge = dynamic_cast<structure::ParameterSyntax*>(getMappedNode(&(*it)));
    if (pNewEdge)
      dest->addParameters(pNewEdge);
  }
  // Copying attributes
  // Copying edges
}

void AlgorithmDeepCopy::clone(structure::CasePatternSwitchLabelSyntax* dest, const structure::CasePatternSwitchLabelSyntax* src) {
  // Copying attributes
  // Copying edges
  // Copying attributes
  dest->setPosition(src->getPosition());
  // Copying edges
  // Copying attributes
  // Copying edges
  // Copying attributes
  // Copying edges
  base::Base* pNewSingleEdge;
  pNewSingleEdge = getMappedNode(src->getPattern());
  if (pNewSingleEdge)
    dest->setPattern(dynamic_cast<structure::PatternSyntax*>(pNewSingleEdge));
  pNewSingleEdge = getMappedNode(src->getWhenClause());
  if (pNewSingleEdge)
    dest->setWhenClause(dynamic_cast<structure::WhenClauseSyntax*>(pNewSingleEdge));
}

void AlgorithmDeepCopy::clone(structure::CaseSwitchLabelSyntax* dest, const structure::CaseSwitchLabelSyntax* src) {
  // Copying attributes
  // Copying edges
  // Copying attributes
  dest->setPosition(src->getPosition());
  // Copying edges
  // Copying attributes
  // Copying edges
  // Copying attributes
  // Copying edges
  base::Base* pNewSingleEdge;
  pNewSingleEdge = getMappedNode(src->getValue());
  if (pNewSingleEdge)
    dest->setValue(dynamic_cast<expression::ExpressionSyntax*>(pNewSingleEdge));
}

void AlgorithmDeepCopy::clone(structure::CatchClauseSyntax* dest, const structure::CatchClauseSyntax* src) {
  // Copying attributes
  // Copying edges
  // Copying attributes
  dest->setPosition(src->getPosition());
  // Copying edges
  // Copying attributes
  // Copying edges
  base::Base* pNewSingleEdge;
  pNewSingleEdge = getMappedNode(src->getBlock());
  if (pNewSingleEdge)
    dest->setBlock(dynamic_cast<statement::BlockSyntax*>(pNewSingleEdge));
  pNewSingleEdge = getMappedNode(src->getDeclaration());
  if (pNewSingleEdge)
    dest->setDeclaration(dynamic_cast<structure::CatchDeclarationSyntax*>(pNewSingleEdge));
  pNewSingleEdge = getMappedNode(src->getFilter());
  if (pNewSingleEdge)
    dest->setFilter(dynamic_cast<structure::CatchFilterClauseSyntax*>(pNewSingleEdge));
}

void AlgorithmDeepCopy::clone(structure::CatchDeclarationSyntax* dest, const structure::CatchDeclarationSyntax* src) {
  // Copying attributes
  // Copying edges
  // Copying attributes
  dest->setPosition(src->getPosition());
  // Copying edges
  // Copying attributes
  // Copying edges
  base::Base* pNewSingleEdge;
  pNewSingleEdge = getMappedNode(src->getType());
  if (pNewSingleEdge)
    dest->setType(dynamic_cast<expression::TypeSyntax*>(pNewSingleEdge));
}

void AlgorithmDeepCopy::clone(structure::CatchFilterClauseSyntax* dest, const structure::CatchFilterClauseSyntax* src) {
  // Copying attributes
  // Copying edges
  // Copying attributes
  dest->setPosition(src->getPosition());
  // Copying edges
  // Copying attributes
  // Copying edges
  base::Base* pNewSingleEdge;
  pNewSingleEdge = getMappedNode(src->getFilterExpression());
  if (pNewSingleEdge)
    dest->setFilterExpression(dynamic_cast<expression::ExpressionSyntax*>(pNewSingleEdge));
}

void AlgorithmDeepCopy::clone(structure::ClassDeclarationSyntax* dest, const structure::ClassDeclarationSyntax* src) {
  // Copying attributes
  // Copying edges
  // Copying attributes
  dest->setPosition(src->getPosition());
  // Copying edges
  // Copying attributes
  // Copying edges
  // Copying attributes
  dest->setIdentifier(src->getIdentifier());
  // Copying edges
  for ( ListIterator<structure::AttributeListSyntax> it = src->getAttributeListsListIteratorBegin(); it != src->getAttributeListsListIteratorEnd(); ++it ) {
    structure::AttributeListSyntax* pNewEdge = dynamic_cast<structure::AttributeListSyntax*>(getMappedNode(&(*it)));
    if (pNewEdge)
      dest->addAttributeLists(pNewEdge);
  }
  base::Base* pNewSingleEdge;
  pNewSingleEdge = getMappedNode(src->getBaseList());
  if (pNewSingleEdge)
    dest->setBaseList(dynamic_cast<structure::BaseListSyntax*>(pNewSingleEdge));
  // Copying attributes
  // Copying edges
  for ( ListIterator<structure::TypeParameterConstraintClauseSyntax> it = src->getConstraintClausesListIteratorBegin(); it != src->getConstraintClausesListIteratorEnd(); ++it ) {
    structure::TypeParameterConstraintClauseSyntax* pNewEdge = dynamic_cast<structure::TypeParameterConstraintClauseSyntax*>(getMappedNode(&(*it)));
    if (pNewEdge)
      dest->addConstraintClauses(pNewEdge);
  }
  for ( ListIterator<structure::MemberDeclarationSyntax> it = src->getMembersListIteratorBegin(); it != src->getMembersListIteratorEnd(); ++it ) {
    structure::MemberDeclarationSyntax* pNewEdge = dynamic_cast<structure::MemberDeclarationSyntax*>(getMappedNode(&(*it)));
    if (pNewEdge)
      dest->addMembers(pNewEdge);
  }
  pNewSingleEdge = getMappedNode(src->getTypeParameterList());
  if (pNewSingleEdge)
    dest->setTypeParameterList(dynamic_cast<structure::TypeParameterListSyntax*>(pNewSingleEdge));
  // Copying attributes
  // Copying edges
}

void AlgorithmDeepCopy::clone(structure::ClassOrStructConstraintSyntax* dest, const structure::ClassOrStructConstraintSyntax* src) {
  // Copying attributes
  // Copying edges
  // Copying attributes
  dest->setPosition(src->getPosition());
  // Copying edges
  // Copying attributes
  // Copying edges
  // Copying attributes
  // Copying edges
}

void AlgorithmDeepCopy::clone(structure::CompilationUnitSyntax* dest, const structure::CompilationUnitSyntax* src) {
  // Copying attributes
  // Copying edges
  // Copying attributes
  dest->setPosition(src->getPosition());
  // Copying edges
  // Copying attributes
  // Copying edges
  for ( ListIterator<structure::AttributeListSyntax> it = src->getAttributeListsListIteratorBegin(); it != src->getAttributeListsListIteratorEnd(); ++it ) {
    structure::AttributeListSyntax* pNewEdge = dynamic_cast<structure::AttributeListSyntax*>(getMappedNode(&(*it)));
    if (pNewEdge)
      dest->addAttributeLists(pNewEdge);
  }
  for ( ListIterator<structure::ExternAliasDirectiveSyntax> it = src->getExternsListIteratorBegin(); it != src->getExternsListIteratorEnd(); ++it ) {
    structure::ExternAliasDirectiveSyntax* pNewEdge = dynamic_cast<structure::ExternAliasDirectiveSyntax*>(getMappedNode(&(*it)));
    if (pNewEdge)
      dest->addExterns(pNewEdge);
  }
  for ( ListIterator<structure::MemberDeclarationSyntax> it = src->getMembersListIteratorBegin(); it != src->getMembersListIteratorEnd(); ++it ) {
    structure::MemberDeclarationSyntax* pNewEdge = dynamic_cast<structure::MemberDeclarationSyntax*>(getMappedNode(&(*it)));
    if (pNewEdge)
      dest->addMembers(pNewEdge);
  }
  for ( ListIterator<structure::UsingDirectiveSyntax> it = src->getUsingsListIteratorBegin(); it != src->getUsingsListIteratorEnd(); ++it ) {
    structure::UsingDirectiveSyntax* pNewEdge = dynamic_cast<structure::UsingDirectiveSyntax*>(getMappedNode(&(*it)));
    if (pNewEdge)
      dest->addUsings(pNewEdge);
  }
}

void AlgorithmDeepCopy::clone(structure::ConstantPatternSyntax* dest, const structure::ConstantPatternSyntax* src) {
  // Copying attributes
  // Copying edges
  // Copying attributes
  dest->setPosition(src->getPosition());
  // Copying edges
  // Copying attributes
  // Copying edges
  // Copying attributes
  // Copying edges
  base::Base* pNewSingleEdge;
  pNewSingleEdge = getMappedNode(src->getExpression());
  if (pNewSingleEdge)
    dest->setExpression(dynamic_cast<expression::ExpressionSyntax*>(pNewSingleEdge));
}

void AlgorithmDeepCopy::clone(structure::ConstructorConstraintSyntax* dest, const structure::ConstructorConstraintSyntax* src) {
  // Copying attributes
  // Copying edges
  // Copying attributes
  dest->setPosition(src->getPosition());
  // Copying edges
  // Copying attributes
  // Copying edges
  // Copying attributes
  // Copying edges
}

void AlgorithmDeepCopy::clone(structure::ConstructorDeclarationSyntax* dest, const structure::ConstructorDeclarationSyntax* src) {
  // Copying attributes
  // Copying edges
  // Copying attributes
  dest->setPosition(src->getPosition());
  // Copying edges
  // Copying attributes
  // Copying edges
  // Copying attributes
  // Copying edges
  for ( ListIterator<structure::EnumMemberDeclarationSyntax> it = src->getAccessedEnumMembersListIteratorBegin(); it != src->getAccessedEnumMembersListIteratorEnd(); ++it ) {
    structure::EnumMemberDeclarationSyntax* pNewEdge = dynamic_cast<structure::EnumMemberDeclarationSyntax*>(getMappedNode(&(*it)));
    if (pNewEdge)
      dest->addAccessedEnumMembers(pNewEdge);
  }
  for ( ListIterator<structure::AttributeListSyntax> it = src->getAttributeListsListIteratorBegin(); it != src->getAttributeListsListIteratorEnd(); ++it ) {
    structure::AttributeListSyntax* pNewEdge = dynamic_cast<structure::AttributeListSyntax*>(getMappedNode(&(*it)));
    if (pNewEdge)
      dest->addAttributeLists(pNewEdge);
  }
  base::Base* pNewSingleEdge;
  pNewSingleEdge = getMappedNode(src->getBody());
  if (pNewSingleEdge)
    dest->setBody(dynamic_cast<statement::BlockSyntax*>(pNewSingleEdge));
  pNewSingleEdge = getMappedNode(src->getExpressionBody());
  if (pNewSingleEdge)
    dest->setExpressionBody(dynamic_cast<structure::ArrowExpressionClauseSyntax*>(pNewSingleEdge));
  pNewSingleEdge = getMappedNode(src->getParameterList());
  if (pNewSingleEdge)
    dest->setParameterList(dynamic_cast<structure::ParameterListSyntax*>(pNewSingleEdge));
  // Copying attributes
  dest->setIdentifier(src->getIdentifier());
  // Copying edges
  pNewSingleEdge = getMappedNode(src->getInitializer());
  if (pNewSingleEdge)
    dest->setInitializer(dynamic_cast<structure::ConstructorInitializerSyntax*>(pNewSingleEdge));
}

void AlgorithmDeepCopy::clone(structure::ConstructorInitializerSyntax* dest, const structure::ConstructorInitializerSyntax* src) {
  // Copying attributes
  // Copying edges
  // Copying attributes
  dest->setPosition(src->getPosition());
  // Copying edges
  // Copying attributes
  // Copying edges
  base::Base* pNewSingleEdge;
  pNewSingleEdge = getMappedNode(src->getArgumentList());
  if (pNewSingleEdge)
    dest->setArgumentList(dynamic_cast<structure::ArgumentListSyntax*>(pNewSingleEdge));
  pNewSingleEdge = getMappedNode(src->getConstructorCall());
  if (pNewSingleEdge)
    dest->setConstructorCall(dynamic_cast<structure::ConstructorDeclarationSyntax*>(pNewSingleEdge));
}

void AlgorithmDeepCopy::clone(structure::ConversionOperatorDeclarationSyntax* dest, const structure::ConversionOperatorDeclarationSyntax* src) {
  // Copying attributes
  // Copying edges
  // Copying attributes
  dest->setPosition(src->getPosition());
  // Copying edges
  // Copying attributes
  // Copying edges
  // Copying attributes
  // Copying edges
  for ( ListIterator<structure::EnumMemberDeclarationSyntax> it = src->getAccessedEnumMembersListIteratorBegin(); it != src->getAccessedEnumMembersListIteratorEnd(); ++it ) {
    structure::EnumMemberDeclarationSyntax* pNewEdge = dynamic_cast<structure::EnumMemberDeclarationSyntax*>(getMappedNode(&(*it)));
    if (pNewEdge)
      dest->addAccessedEnumMembers(pNewEdge);
  }
  for ( ListIterator<structure::AttributeListSyntax> it = src->getAttributeListsListIteratorBegin(); it != src->getAttributeListsListIteratorEnd(); ++it ) {
    structure::AttributeListSyntax* pNewEdge = dynamic_cast<structure::AttributeListSyntax*>(getMappedNode(&(*it)));
    if (pNewEdge)
      dest->addAttributeLists(pNewEdge);
  }
  base::Base* pNewSingleEdge;
  pNewSingleEdge = getMappedNode(src->getBody());
  if (pNewSingleEdge)
    dest->setBody(dynamic_cast<statement::BlockSyntax*>(pNewSingleEdge));
  pNewSingleEdge = getMappedNode(src->getExpressionBody());
  if (pNewSingleEdge)
    dest->setExpressionBody(dynamic_cast<structure::ArrowExpressionClauseSyntax*>(pNewSingleEdge));
  pNewSingleEdge = getMappedNode(src->getParameterList());
  if (pNewSingleEdge)
    dest->setParameterList(dynamic_cast<structure::ParameterListSyntax*>(pNewSingleEdge));
  // Copying attributes
  // Copying edges
  pNewSingleEdge = getMappedNode(src->getType());
  if (pNewSingleEdge)
    dest->setType(dynamic_cast<expression::TypeSyntax*>(pNewSingleEdge));
}

void AlgorithmDeepCopy::clone(structure::ConversionOperatorMemberCrefSyntax* dest, const structure::ConversionOperatorMemberCrefSyntax* src) {
  // Copying attributes
  // Copying edges
  // Copying attributes
  dest->setPosition(src->getPosition());
  // Copying edges
  // Copying attributes
  // Copying edges
  // Copying attributes
  // Copying edges
  // Copying attributes
  // Copying edges
  base::Base* pNewSingleEdge;
  pNewSingleEdge = getMappedNode(src->getParameters());
  if (pNewSingleEdge)
    dest->setParameters(dynamic_cast<structure::CrefParameterListSyntax*>(pNewSingleEdge));
  pNewSingleEdge = getMappedNode(src->getType());
  if (pNewSingleEdge)
    dest->setType(dynamic_cast<expression::TypeSyntax*>(pNewSingleEdge));
}

void AlgorithmDeepCopy::clone(structure::CrefBracketedParameterListSyntax* dest, const structure::CrefBracketedParameterListSyntax* src) {
  // Copying attributes
  // Copying edges
  // Copying attributes
  dest->setPosition(src->getPosition());
  // Copying edges
  // Copying attributes
  // Copying edges
  for ( ListIterator<structure::CrefParameterSyntax> it = src->getParametersListIteratorBegin(); it != src->getParametersListIteratorEnd(); ++it ) {
    structure::CrefParameterSyntax* pNewEdge = dynamic_cast<structure::CrefParameterSyntax*>(getMappedNode(&(*it)));
    if (pNewEdge)
      dest->addParameters(pNewEdge);
  }
  // Copying attributes
  // Copying edges
}

void AlgorithmDeepCopy::clone(structure::CrefParameterListSyntax* dest, const structure::CrefParameterListSyntax* src) {
  // Copying attributes
  // Copying edges
  // Copying attributes
  dest->setPosition(src->getPosition());
  // Copying edges
  // Copying attributes
  // Copying edges
  for ( ListIterator<structure::CrefParameterSyntax> it = src->getParametersListIteratorBegin(); it != src->getParametersListIteratorEnd(); ++it ) {
    structure::CrefParameterSyntax* pNewEdge = dynamic_cast<structure::CrefParameterSyntax*>(getMappedNode(&(*it)));
    if (pNewEdge)
      dest->addParameters(pNewEdge);
  }
  // Copying attributes
  // Copying edges
}

void AlgorithmDeepCopy::clone(structure::CrefParameterSyntax* dest, const structure::CrefParameterSyntax* src) {
  // Copying attributes
  // Copying edges
  // Copying attributes
  dest->setPosition(src->getPosition());
  // Copying edges
  // Copying attributes
  // Copying edges
  base::Base* pNewSingleEdge;
  pNewSingleEdge = getMappedNode(src->getType());
  if (pNewSingleEdge)
    dest->setType(dynamic_cast<expression::TypeSyntax*>(pNewSingleEdge));
}

void AlgorithmDeepCopy::clone(structure::CrefSyntax* dest, const structure::CrefSyntax* src) {
  // Copying attributes
  // Copying edges
  // Copying attributes
  dest->setPosition(src->getPosition());
  // Copying edges
  // Copying attributes
  // Copying edges
}

void AlgorithmDeepCopy::clone(structure::DeclarationPatternSyntax* dest, const structure::DeclarationPatternSyntax* src) {
  // Copying attributes
  // Copying edges
  // Copying attributes
  dest->setPosition(src->getPosition());
  // Copying edges
  // Copying attributes
  // Copying edges
  // Copying attributes
  // Copying edges
  base::Base* pNewSingleEdge;
  pNewSingleEdge = getMappedNode(src->getDesignation());
  if (pNewSingleEdge)
    dest->setDesignation(dynamic_cast<structure::VariableDesignationSyntax*>(pNewSingleEdge));
  pNewSingleEdge = getMappedNode(src->getType());
  if (pNewSingleEdge)
    dest->setType(dynamic_cast<expression::TypeSyntax*>(pNewSingleEdge));
}

void AlgorithmDeepCopy::clone(structure::DefaultSwitchLabelSyntax* dest, const structure::DefaultSwitchLabelSyntax* src) {
  // Copying attributes
  // Copying edges
  // Copying attributes
  dest->setPosition(src->getPosition());
  // Copying edges
  // Copying attributes
  // Copying edges
  // Copying attributes
  // Copying edges
}

void AlgorithmDeepCopy::clone(structure::DelegateDeclarationSyntax* dest, const structure::DelegateDeclarationSyntax* src) {
  // Copying attributes
  // Copying edges
  // Copying attributes
  dest->setPosition(src->getPosition());
  // Copying edges
  // Copying attributes
  // Copying edges
  // Copying attributes
  dest->setIdentifier(src->getIdentifier());
  // Copying edges
  for ( ListIterator<structure::AttributeListSyntax> it = src->getAttributeListsListIteratorBegin(); it != src->getAttributeListsListIteratorEnd(); ++it ) {
    structure::AttributeListSyntax* pNewEdge = dynamic_cast<structure::AttributeListSyntax*>(getMappedNode(&(*it)));
    if (pNewEdge)
      dest->addAttributeLists(pNewEdge);
  }
  for ( ListIterator<structure::TypeParameterConstraintClauseSyntax> it = src->getConstraintClausesListIteratorBegin(); it != src->getConstraintClausesListIteratorEnd(); ++it ) {
    structure::TypeParameterConstraintClauseSyntax* pNewEdge = dynamic_cast<structure::TypeParameterConstraintClauseSyntax*>(getMappedNode(&(*it)));
    if (pNewEdge)
      dest->addConstraintClauses(pNewEdge);
  }
  base::Base* pNewSingleEdge;
  pNewSingleEdge = getMappedNode(src->getParameterList());
  if (pNewSingleEdge)
    dest->setParameterList(dynamic_cast<structure::ParameterListSyntax*>(pNewSingleEdge));
  pNewSingleEdge = getMappedNode(src->getReturnType());
  if (pNewSingleEdge)
    dest->setReturnType(dynamic_cast<expression::TypeSyntax*>(pNewSingleEdge));
}

void AlgorithmDeepCopy::clone(structure::DestructorDeclarationSyntax* dest, const structure::DestructorDeclarationSyntax* src) {
  // Copying attributes
  // Copying edges
  // Copying attributes
  dest->setPosition(src->getPosition());
  // Copying edges
  // Copying attributes
  // Copying edges
  // Copying attributes
  // Copying edges
  for ( ListIterator<structure::EnumMemberDeclarationSyntax> it = src->getAccessedEnumMembersListIteratorBegin(); it != src->getAccessedEnumMembersListIteratorEnd(); ++it ) {
    structure::EnumMemberDeclarationSyntax* pNewEdge = dynamic_cast<structure::EnumMemberDeclarationSyntax*>(getMappedNode(&(*it)));
    if (pNewEdge)
      dest->addAccessedEnumMembers(pNewEdge);
  }
  for ( ListIterator<structure::AttributeListSyntax> it = src->getAttributeListsListIteratorBegin(); it != src->getAttributeListsListIteratorEnd(); ++it ) {
    structure::AttributeListSyntax* pNewEdge = dynamic_cast<structure::AttributeListSyntax*>(getMappedNode(&(*it)));
    if (pNewEdge)
      dest->addAttributeLists(pNewEdge);
  }
  base::Base* pNewSingleEdge;
  pNewSingleEdge = getMappedNode(src->getBody());
  if (pNewSingleEdge)
    dest->setBody(dynamic_cast<statement::BlockSyntax*>(pNewSingleEdge));
  pNewSingleEdge = getMappedNode(src->getExpressionBody());
  if (pNewSingleEdge)
    dest->setExpressionBody(dynamic_cast<structure::ArrowExpressionClauseSyntax*>(pNewSingleEdge));
  pNewSingleEdge = getMappedNode(src->getParameterList());
  if (pNewSingleEdge)
    dest->setParameterList(dynamic_cast<structure::ParameterListSyntax*>(pNewSingleEdge));
  // Copying attributes
  dest->setIdentifier(src->getIdentifier());
  // Copying edges
}

void AlgorithmDeepCopy::clone(structure::DiscardDesignationSyntax* dest, const structure::DiscardDesignationSyntax* src) {
  // Copying attributes
  // Copying edges
  // Copying attributes
  dest->setPosition(src->getPosition());
  // Copying edges
  // Copying attributes
  // Copying edges
  // Copying attributes
  // Copying edges
}

void AlgorithmDeepCopy::clone(structure::DiscardPatternSyntax* dest, const structure::DiscardPatternSyntax* src) {
  // Copying attributes
  // Copying edges
  // Copying attributes
  dest->setPosition(src->getPosition());
  // Copying edges
  // Copying attributes
  // Copying edges
  // Copying attributes
  // Copying edges
}

void AlgorithmDeepCopy::clone(structure::ElseClauseSyntax* dest, const structure::ElseClauseSyntax* src) {
  // Copying attributes
  // Copying edges
  // Copying attributes
  dest->setPosition(src->getPosition());
  // Copying edges
  // Copying attributes
  // Copying edges
  base::Base* pNewSingleEdge;
  pNewSingleEdge = getMappedNode(src->getStatement());
  if (pNewSingleEdge)
    dest->setStatement(dynamic_cast<statement::StatementSyntax*>(pNewSingleEdge));
}

void AlgorithmDeepCopy::clone(structure::EnumDeclarationSyntax* dest, const structure::EnumDeclarationSyntax* src) {
  // Copying attributes
  // Copying edges
  // Copying attributes
  dest->setPosition(src->getPosition());
  // Copying edges
  // Copying attributes
  // Copying edges
  // Copying attributes
  dest->setIdentifier(src->getIdentifier());
  // Copying edges
  for ( ListIterator<structure::AttributeListSyntax> it = src->getAttributeListsListIteratorBegin(); it != src->getAttributeListsListIteratorEnd(); ++it ) {
    structure::AttributeListSyntax* pNewEdge = dynamic_cast<structure::AttributeListSyntax*>(getMappedNode(&(*it)));
    if (pNewEdge)
      dest->addAttributeLists(pNewEdge);
  }
  base::Base* pNewSingleEdge;
  pNewSingleEdge = getMappedNode(src->getBaseList());
  if (pNewSingleEdge)
    dest->setBaseList(dynamic_cast<structure::BaseListSyntax*>(pNewSingleEdge));
  // Copying attributes
  // Copying edges
  for ( ListIterator<structure::EnumMemberDeclarationSyntax> it = src->getMembersListIteratorBegin(); it != src->getMembersListIteratorEnd(); ++it ) {
    structure::EnumMemberDeclarationSyntax* pNewEdge = dynamic_cast<structure::EnumMemberDeclarationSyntax*>(getMappedNode(&(*it)));
    if (pNewEdge)
      dest->addMembers(pNewEdge);
  }
}

void AlgorithmDeepCopy::clone(structure::EnumMemberDeclarationSyntax* dest, const structure::EnumMemberDeclarationSyntax* src) {
  // Copying attributes
  // Copying edges
  // Copying attributes
  dest->setPosition(src->getPosition());
  // Copying edges
  // Copying attributes
  // Copying edges
  // Copying attributes
  dest->setIdentifier(src->getIdentifier());
  // Copying edges
  for ( ListIterator<structure::AttributeListSyntax> it = src->getAttributeListsListIteratorBegin(); it != src->getAttributeListsListIteratorEnd(); ++it ) {
    structure::AttributeListSyntax* pNewEdge = dynamic_cast<structure::AttributeListSyntax*>(getMappedNode(&(*it)));
    if (pNewEdge)
      dest->addAttributeLists(pNewEdge);
  }
  base::Base* pNewSingleEdge;
  pNewSingleEdge = getMappedNode(src->getEqualsValue());
  if (pNewSingleEdge)
    dest->setEqualsValue(dynamic_cast<structure::EqualsValueClauseSyntax*>(pNewSingleEdge));
}

void AlgorithmDeepCopy::clone(structure::EqualsValueClauseSyntax* dest, const structure::EqualsValueClauseSyntax* src) {
  // Copying attributes
  // Copying edges
  // Copying attributes
  dest->setPosition(src->getPosition());
  // Copying edges
  // Copying attributes
  // Copying edges
  base::Base* pNewSingleEdge;
  pNewSingleEdge = getMappedNode(src->getValue());
  if (pNewSingleEdge)
    dest->setValue(dynamic_cast<expression::ExpressionSyntax*>(pNewSingleEdge));
}

void AlgorithmDeepCopy::clone(structure::EventDeclarationSyntax* dest, const structure::EventDeclarationSyntax* src) {
  // Copying attributes
  // Copying edges
  // Copying attributes
  dest->setPosition(src->getPosition());
  // Copying edges
  // Copying attributes
  // Copying edges
  // Copying attributes
  // Copying edges
  base::Base* pNewSingleEdge;
  pNewSingleEdge = getMappedNode(src->getAccessorList());
  if (pNewSingleEdge)
    dest->setAccessorList(dynamic_cast<structure::AccessorListSyntax*>(pNewSingleEdge));
  for ( ListIterator<structure::AttributeListSyntax> it = src->getAttributeListsListIteratorBegin(); it != src->getAttributeListsListIteratorEnd(); ++it ) {
    structure::AttributeListSyntax* pNewEdge = dynamic_cast<structure::AttributeListSyntax*>(getMappedNode(&(*it)));
    if (pNewEdge)
      dest->addAttributeLists(pNewEdge);
  }
  pNewSingleEdge = getMappedNode(src->getExplicitInterfaceSpecifier());
  if (pNewSingleEdge)
    dest->setExplicitInterfaceSpecifier(dynamic_cast<structure::ExplicitInterfaceSpecifierSyntax*>(pNewSingleEdge));
  pNewSingleEdge = getMappedNode(src->getType());
  if (pNewSingleEdge)
    dest->setType(dynamic_cast<expression::TypeSyntax*>(pNewSingleEdge));
  // Copying attributes
  dest->setIdentifier(src->getIdentifier());
  // Copying edges
}

void AlgorithmDeepCopy::clone(structure::EventFieldDeclarationSyntax* dest, const structure::EventFieldDeclarationSyntax* src) {
  // Copying attributes
  // Copying edges
  // Copying attributes
  dest->setPosition(src->getPosition());
  // Copying edges
  // Copying attributes
  // Copying edges
  // Copying attributes
  // Copying edges
  for ( ListIterator<structure::AttributeListSyntax> it = src->getAttributeListsListIteratorBegin(); it != src->getAttributeListsListIteratorEnd(); ++it ) {
    structure::AttributeListSyntax* pNewEdge = dynamic_cast<structure::AttributeListSyntax*>(getMappedNode(&(*it)));
    if (pNewEdge)
      dest->addAttributeLists(pNewEdge);
  }
  base::Base* pNewSingleEdge;
  pNewSingleEdge = getMappedNode(src->getDeclaration());
  if (pNewSingleEdge)
    dest->setDeclaration(dynamic_cast<structure::VariableDeclarationSyntax*>(pNewSingleEdge));
  // Copying attributes
  // Copying edges
}

void AlgorithmDeepCopy::clone(structure::ExplicitInterfaceSpecifierSyntax* dest, const structure::ExplicitInterfaceSpecifierSyntax* src) {
  // Copying attributes
  // Copying edges
  // Copying attributes
  dest->setPosition(src->getPosition());
  // Copying edges
  // Copying attributes
  // Copying edges
  base::Base* pNewSingleEdge;
  pNewSingleEdge = getMappedNode(src->getName());
  if (pNewSingleEdge)
    dest->setName(dynamic_cast<expression::NameSyntax*>(pNewSingleEdge));
}

void AlgorithmDeepCopy::clone(structure::ExternAliasDirectiveSyntax* dest, const structure::ExternAliasDirectiveSyntax* src) {
  // Copying attributes
  // Copying edges
  // Copying attributes
  dest->setPosition(src->getPosition());
  // Copying edges
  // Copying attributes
  dest->setIdentifier(src->getIdentifier());
  // Copying edges
}

void AlgorithmDeepCopy::clone(structure::FieldDeclarationSyntax* dest, const structure::FieldDeclarationSyntax* src) {
  // Copying attributes
  // Copying edges
  // Copying attributes
  dest->setPosition(src->getPosition());
  // Copying edges
  // Copying attributes
  // Copying edges
  // Copying attributes
  // Copying edges
  for ( ListIterator<structure::AttributeListSyntax> it = src->getAttributeListsListIteratorBegin(); it != src->getAttributeListsListIteratorEnd(); ++it ) {
    structure::AttributeListSyntax* pNewEdge = dynamic_cast<structure::AttributeListSyntax*>(getMappedNode(&(*it)));
    if (pNewEdge)
      dest->addAttributeLists(pNewEdge);
  }
  base::Base* pNewSingleEdge;
  pNewSingleEdge = getMappedNode(src->getDeclaration());
  if (pNewSingleEdge)
    dest->setDeclaration(dynamic_cast<structure::VariableDeclarationSyntax*>(pNewSingleEdge));
  // Copying attributes
  // Copying edges
}

void AlgorithmDeepCopy::clone(structure::FinallyClauseSyntax* dest, const structure::FinallyClauseSyntax* src) {
  // Copying attributes
  // Copying edges
  // Copying attributes
  dest->setPosition(src->getPosition());
  // Copying edges
  // Copying attributes
  // Copying edges
  base::Base* pNewSingleEdge;
  pNewSingleEdge = getMappedNode(src->getBlock());
  if (pNewSingleEdge)
    dest->setBlock(dynamic_cast<statement::BlockSyntax*>(pNewSingleEdge));
}

void AlgorithmDeepCopy::clone(structure::FromClauseSyntax* dest, const structure::FromClauseSyntax* src) {
  // Copying attributes
  // Copying edges
  // Copying attributes
  dest->setPosition(src->getPosition());
  // Copying edges
  // Copying attributes
  // Copying edges
  // Copying attributes
  dest->setIdentifier(src->getIdentifier());
  // Copying edges
  base::Base* pNewSingleEdge;
  pNewSingleEdge = getMappedNode(src->getExpression());
  if (pNewSingleEdge)
    dest->setExpression(dynamic_cast<expression::ExpressionSyntax*>(pNewSingleEdge));
  pNewSingleEdge = getMappedNode(src->getType());
  if (pNewSingleEdge)
    dest->setType(dynamic_cast<expression::TypeSyntax*>(pNewSingleEdge));
}

void AlgorithmDeepCopy::clone(structure::GlobalStatementSyntax* dest, const structure::GlobalStatementSyntax* src) {
  // Copying attributes
  // Copying edges
  // Copying attributes
  dest->setPosition(src->getPosition());
  // Copying edges
  // Copying attributes
  // Copying edges
  // Copying attributes
  // Copying edges
  base::Base* pNewSingleEdge;
  pNewSingleEdge = getMappedNode(src->getStatement());
  if (pNewSingleEdge)
    dest->setStatement(dynamic_cast<statement::StatementSyntax*>(pNewSingleEdge));
}

void AlgorithmDeepCopy::clone(structure::GroupClauseSyntax* dest, const structure::GroupClauseSyntax* src) {
  // Copying attributes
  // Copying edges
  // Copying attributes
  dest->setPosition(src->getPosition());
  // Copying edges
  // Copying attributes
  // Copying edges
  // Copying attributes
  // Copying edges
  base::Base* pNewSingleEdge;
  pNewSingleEdge = getMappedNode(src->getByExpression());
  if (pNewSingleEdge)
    dest->setByExpression(dynamic_cast<expression::ExpressionSyntax*>(pNewSingleEdge));
  pNewSingleEdge = getMappedNode(src->getGroupExpression());
  if (pNewSingleEdge)
    dest->setGroupExpression(dynamic_cast<expression::ExpressionSyntax*>(pNewSingleEdge));
}

void AlgorithmDeepCopy::clone(structure::IncompleteMemberSyntax* dest, const structure::IncompleteMemberSyntax* src) {
  // Copying attributes
  // Copying edges
  // Copying attributes
  dest->setPosition(src->getPosition());
  // Copying edges
  // Copying attributes
  // Copying edges
  // Copying attributes
  // Copying edges
  for ( ListIterator<structure::AttributeListSyntax> it = src->getAttributeListsListIteratorBegin(); it != src->getAttributeListsListIteratorEnd(); ++it ) {
    structure::AttributeListSyntax* pNewEdge = dynamic_cast<structure::AttributeListSyntax*>(getMappedNode(&(*it)));
    if (pNewEdge)
      dest->addAttributeLists(pNewEdge);
  }
  base::Base* pNewSingleEdge;
  pNewSingleEdge = getMappedNode(src->getType());
  if (pNewSingleEdge)
    dest->setType(dynamic_cast<expression::TypeSyntax*>(pNewSingleEdge));
}

void AlgorithmDeepCopy::clone(structure::IndexerDeclarationSyntax* dest, const structure::IndexerDeclarationSyntax* src) {
  // Copying attributes
  // Copying edges
  // Copying attributes
  dest->setPosition(src->getPosition());
  // Copying edges
  // Copying attributes
  // Copying edges
  // Copying attributes
  // Copying edges
  base::Base* pNewSingleEdge;
  pNewSingleEdge = getMappedNode(src->getAccessorList());
  if (pNewSingleEdge)
    dest->setAccessorList(dynamic_cast<structure::AccessorListSyntax*>(pNewSingleEdge));
  for ( ListIterator<structure::AttributeListSyntax> it = src->getAttributeListsListIteratorBegin(); it != src->getAttributeListsListIteratorEnd(); ++it ) {
    structure::AttributeListSyntax* pNewEdge = dynamic_cast<structure::AttributeListSyntax*>(getMappedNode(&(*it)));
    if (pNewEdge)
      dest->addAttributeLists(pNewEdge);
  }
  pNewSingleEdge = getMappedNode(src->getExplicitInterfaceSpecifier());
  if (pNewSingleEdge)
    dest->setExplicitInterfaceSpecifier(dynamic_cast<structure::ExplicitInterfaceSpecifierSyntax*>(pNewSingleEdge));
  pNewSingleEdge = getMappedNode(src->getType());
  if (pNewSingleEdge)
    dest->setType(dynamic_cast<expression::TypeSyntax*>(pNewSingleEdge));
  // Copying attributes
  // Copying edges
  pNewSingleEdge = getMappedNode(src->getExpressionBody());
  if (pNewSingleEdge)
    dest->setExpressionBody(dynamic_cast<structure::ArrowExpressionClauseSyntax*>(pNewSingleEdge));
  pNewSingleEdge = getMappedNode(src->getParameterList());
  if (pNewSingleEdge)
    dest->setParameterList(dynamic_cast<structure::BracketedParameterListSyntax*>(pNewSingleEdge));
}

void AlgorithmDeepCopy::clone(structure::IndexerMemberCrefSyntax* dest, const structure::IndexerMemberCrefSyntax* src) {
  // Copying attributes
  // Copying edges
  // Copying attributes
  dest->setPosition(src->getPosition());
  // Copying edges
  // Copying attributes
  // Copying edges
  // Copying attributes
  // Copying edges
  // Copying attributes
  // Copying edges
  base::Base* pNewSingleEdge;
  pNewSingleEdge = getMappedNode(src->getParameters());
  if (pNewSingleEdge)
    dest->setParameters(dynamic_cast<structure::CrefBracketedParameterListSyntax*>(pNewSingleEdge));
}

void AlgorithmDeepCopy::clone(structure::InterfaceDeclarationSyntax* dest, const structure::InterfaceDeclarationSyntax* src) {
  // Copying attributes
  // Copying edges
  // Copying attributes
  dest->setPosition(src->getPosition());
  // Copying edges
  // Copying attributes
  // Copying edges
  // Copying attributes
  dest->setIdentifier(src->getIdentifier());
  // Copying edges
  for ( ListIterator<structure::AttributeListSyntax> it = src->getAttributeListsListIteratorBegin(); it != src->getAttributeListsListIteratorEnd(); ++it ) {
    structure::AttributeListSyntax* pNewEdge = dynamic_cast<structure::AttributeListSyntax*>(getMappedNode(&(*it)));
    if (pNewEdge)
      dest->addAttributeLists(pNewEdge);
  }
  base::Base* pNewSingleEdge;
  pNewSingleEdge = getMappedNode(src->getBaseList());
  if (pNewSingleEdge)
    dest->setBaseList(dynamic_cast<structure::BaseListSyntax*>(pNewSingleEdge));
  // Copying attributes
  // Copying edges
  for ( ListIterator<structure::TypeParameterConstraintClauseSyntax> it = src->getConstraintClausesListIteratorBegin(); it != src->getConstraintClausesListIteratorEnd(); ++it ) {
    structure::TypeParameterConstraintClauseSyntax* pNewEdge = dynamic_cast<structure::TypeParameterConstraintClauseSyntax*>(getMappedNode(&(*it)));
    if (pNewEdge)
      dest->addConstraintClauses(pNewEdge);
  }
  for ( ListIterator<structure::MemberDeclarationSyntax> it = src->getMembersListIteratorBegin(); it != src->getMembersListIteratorEnd(); ++it ) {
    structure::MemberDeclarationSyntax* pNewEdge = dynamic_cast<structure::MemberDeclarationSyntax*>(getMappedNode(&(*it)));
    if (pNewEdge)
      dest->addMembers(pNewEdge);
  }
  pNewSingleEdge = getMappedNode(src->getTypeParameterList());
  if (pNewSingleEdge)
    dest->setTypeParameterList(dynamic_cast<structure::TypeParameterListSyntax*>(pNewSingleEdge));
  // Copying attributes
  // Copying edges
}

void AlgorithmDeepCopy::clone(structure::InterpolatedStringContentSyntax* dest, const structure::InterpolatedStringContentSyntax* src) {
  // Copying attributes
  // Copying edges
  // Copying attributes
  dest->setPosition(src->getPosition());
  // Copying edges
  // Copying attributes
  // Copying edges
}

void AlgorithmDeepCopy::clone(structure::InterpolatedStringTextSyntax* dest, const structure::InterpolatedStringTextSyntax* src) {
  // Copying attributes
  // Copying edges
  // Copying attributes
  dest->setPosition(src->getPosition());
  // Copying edges
  // Copying attributes
  // Copying edges
  // Copying attributes
  // Copying edges
}

void AlgorithmDeepCopy::clone(structure::InterpolationAlignmentClauseSyntax* dest, const structure::InterpolationAlignmentClauseSyntax* src) {
  // Copying attributes
  // Copying edges
  // Copying attributes
  dest->setPosition(src->getPosition());
  // Copying edges
  // Copying attributes
  // Copying edges
  base::Base* pNewSingleEdge;
  pNewSingleEdge = getMappedNode(src->getValue());
  if (pNewSingleEdge)
    dest->setValue(dynamic_cast<expression::ExpressionSyntax*>(pNewSingleEdge));
}

void AlgorithmDeepCopy::clone(structure::InterpolationFormatClauseSyntax* dest, const structure::InterpolationFormatClauseSyntax* src) {
  // Copying attributes
  // Copying edges
  // Copying attributes
  dest->setPosition(src->getPosition());
  // Copying edges
  // Copying attributes
  // Copying edges
}

void AlgorithmDeepCopy::clone(structure::InterpolationSyntax* dest, const structure::InterpolationSyntax* src) {
  // Copying attributes
  // Copying edges
  // Copying attributes
  dest->setPosition(src->getPosition());
  // Copying edges
  // Copying attributes
  // Copying edges
  // Copying attributes
  // Copying edges
  base::Base* pNewSingleEdge;
  pNewSingleEdge = getMappedNode(src->getAlignmentClause());
  if (pNewSingleEdge)
    dest->setAlignmentClause(dynamic_cast<structure::InterpolationAlignmentClauseSyntax*>(pNewSingleEdge));
  pNewSingleEdge = getMappedNode(src->getExpression());
  if (pNewSingleEdge)
    dest->setExpression(dynamic_cast<expression::ExpressionSyntax*>(pNewSingleEdge));
  pNewSingleEdge = getMappedNode(src->getFormatClause());
  if (pNewSingleEdge)
    dest->setFormatClause(dynamic_cast<structure::InterpolationFormatClauseSyntax*>(pNewSingleEdge));
}

void AlgorithmDeepCopy::clone(structure::JoinClauseSyntax* dest, const structure::JoinClauseSyntax* src) {
  // Copying attributes
  // Copying edges
  // Copying attributes
  dest->setPosition(src->getPosition());
  // Copying edges
  // Copying attributes
  // Copying edges
  // Copying attributes
  dest->setIdentifier(src->getIdentifier());
  // Copying edges
  base::Base* pNewSingleEdge;
  pNewSingleEdge = getMappedNode(src->getInExpression());
  if (pNewSingleEdge)
    dest->setInExpression(dynamic_cast<expression::ExpressionSyntax*>(pNewSingleEdge));
  pNewSingleEdge = getMappedNode(src->getInto());
  if (pNewSingleEdge)
    dest->setInto(dynamic_cast<structure::JoinIntoClauseSyntax*>(pNewSingleEdge));
  pNewSingleEdge = getMappedNode(src->getLeftExpression());
  if (pNewSingleEdge)
    dest->setLeftExpression(dynamic_cast<expression::ExpressionSyntax*>(pNewSingleEdge));
  pNewSingleEdge = getMappedNode(src->getRightExpression());
  if (pNewSingleEdge)
    dest->setRightExpression(dynamic_cast<expression::ExpressionSyntax*>(pNewSingleEdge));
  pNewSingleEdge = getMappedNode(src->getType());
  if (pNewSingleEdge)
    dest->setType(dynamic_cast<expression::TypeSyntax*>(pNewSingleEdge));
}

void AlgorithmDeepCopy::clone(structure::JoinIntoClauseSyntax* dest, const structure::JoinIntoClauseSyntax* src) {
  // Copying attributes
  // Copying edges
  // Copying attributes
  dest->setPosition(src->getPosition());
  // Copying edges
  // Copying attributes
  dest->setIdentifier(src->getIdentifier());
  // Copying edges
}

void AlgorithmDeepCopy::clone(structure::LetClauseSyntax* dest, const structure::LetClauseSyntax* src) {
  // Copying attributes
  // Copying edges
  // Copying attributes
  dest->setPosition(src->getPosition());
  // Copying edges
  // Copying attributes
  // Copying edges
  // Copying attributes
  dest->setIdentifier(src->getIdentifier());
  // Copying edges
  base::Base* pNewSingleEdge;
  pNewSingleEdge = getMappedNode(src->getExpression());
  if (pNewSingleEdge)
    dest->setExpression(dynamic_cast<expression::ExpressionSyntax*>(pNewSingleEdge));
}

void AlgorithmDeepCopy::clone(structure::MemberCrefSyntax* dest, const structure::MemberCrefSyntax* src) {
  // Copying attributes
  // Copying edges
  // Copying attributes
  dest->setPosition(src->getPosition());
  // Copying edges
  // Copying attributes
  // Copying edges
  // Copying attributes
  // Copying edges
}

void AlgorithmDeepCopy::clone(structure::MemberDeclarationSyntax* dest, const structure::MemberDeclarationSyntax* src) {
  // Copying attributes
  // Copying edges
  // Copying attributes
  dest->setPosition(src->getPosition());
  // Copying edges
  // Copying attributes
  // Copying edges
}

void AlgorithmDeepCopy::clone(structure::MethodDeclarationSyntax* dest, const structure::MethodDeclarationSyntax* src) {
  // Copying attributes
  // Copying edges
  // Copying attributes
  dest->setPosition(src->getPosition());
  // Copying edges
  // Copying attributes
  // Copying edges
  // Copying attributes
  // Copying edges
  for ( ListIterator<structure::EnumMemberDeclarationSyntax> it = src->getAccessedEnumMembersListIteratorBegin(); it != src->getAccessedEnumMembersListIteratorEnd(); ++it ) {
    structure::EnumMemberDeclarationSyntax* pNewEdge = dynamic_cast<structure::EnumMemberDeclarationSyntax*>(getMappedNode(&(*it)));
    if (pNewEdge)
      dest->addAccessedEnumMembers(pNewEdge);
  }
  for ( ListIterator<structure::AttributeListSyntax> it = src->getAttributeListsListIteratorBegin(); it != src->getAttributeListsListIteratorEnd(); ++it ) {
    structure::AttributeListSyntax* pNewEdge = dynamic_cast<structure::AttributeListSyntax*>(getMappedNode(&(*it)));
    if (pNewEdge)
      dest->addAttributeLists(pNewEdge);
  }
  base::Base* pNewSingleEdge;
  pNewSingleEdge = getMappedNode(src->getBody());
  if (pNewSingleEdge)
    dest->setBody(dynamic_cast<statement::BlockSyntax*>(pNewSingleEdge));
  pNewSingleEdge = getMappedNode(src->getExpressionBody());
  if (pNewSingleEdge)
    dest->setExpressionBody(dynamic_cast<structure::ArrowExpressionClauseSyntax*>(pNewSingleEdge));
  pNewSingleEdge = getMappedNode(src->getParameterList());
  if (pNewSingleEdge)
    dest->setParameterList(dynamic_cast<structure::ParameterListSyntax*>(pNewSingleEdge));
  // Copying attributes
  dest->setIdentifier(src->getIdentifier());
  // Copying edges
  for ( ListIterator<structure::TypeParameterConstraintClauseSyntax> it = src->getConstraintClausesListIteratorBegin(); it != src->getConstraintClausesListIteratorEnd(); ++it ) {
    structure::TypeParameterConstraintClauseSyntax* pNewEdge = dynamic_cast<structure::TypeParameterConstraintClauseSyntax*>(getMappedNode(&(*it)));
    if (pNewEdge)
      dest->addConstraintClauses(pNewEdge);
  }
  pNewSingleEdge = getMappedNode(src->getExplicitInterfaceSpecifier());
  if (pNewSingleEdge)
    dest->setExplicitInterfaceSpecifier(dynamic_cast<structure::ExplicitInterfaceSpecifierSyntax*>(pNewSingleEdge));
  pNewSingleEdge = getMappedNode(src->getReturnType());
  if (pNewSingleEdge)
    dest->setReturnType(dynamic_cast<expression::TypeSyntax*>(pNewSingleEdge));
}

void AlgorithmDeepCopy::clone(structure::NameColonSyntax* dest, const structure::NameColonSyntax* src) {
  // Copying attributes
  // Copying edges
  // Copying attributes
  dest->setPosition(src->getPosition());
  // Copying edges
  // Copying attributes
  // Copying edges
  base::Base* pNewSingleEdge;
  pNewSingleEdge = getMappedNode(src->getName());
  if (pNewSingleEdge)
    dest->setName(dynamic_cast<expression::IdentifierNameSyntax*>(pNewSingleEdge));
}

void AlgorithmDeepCopy::clone(structure::NameEqualsSyntax* dest, const structure::NameEqualsSyntax* src) {
  // Copying attributes
  // Copying edges
  // Copying attributes
  dest->setPosition(src->getPosition());
  // Copying edges
  // Copying attributes
  // Copying edges
  base::Base* pNewSingleEdge;
  pNewSingleEdge = getMappedNode(src->getName());
  if (pNewSingleEdge)
    dest->setName(dynamic_cast<expression::IdentifierNameSyntax*>(pNewSingleEdge));
}

void AlgorithmDeepCopy::clone(structure::NameMemberCrefSyntax* dest, const structure::NameMemberCrefSyntax* src) {
  // Copying attributes
  // Copying edges
  // Copying attributes
  dest->setPosition(src->getPosition());
  // Copying edges
  // Copying attributes
  // Copying edges
  // Copying attributes
  // Copying edges
  // Copying attributes
  // Copying edges
  base::Base* pNewSingleEdge;
  pNewSingleEdge = getMappedNode(src->getName());
  if (pNewSingleEdge)
    dest->setName(dynamic_cast<expression::TypeSyntax*>(pNewSingleEdge));
  pNewSingleEdge = getMappedNode(src->getParameters());
  if (pNewSingleEdge)
    dest->setParameters(dynamic_cast<structure::CrefParameterListSyntax*>(pNewSingleEdge));
}

void AlgorithmDeepCopy::clone(structure::NamespaceDeclarationSyntax* dest, const structure::NamespaceDeclarationSyntax* src) {
  // Copying attributes
  // Copying edges
  // Copying attributes
  dest->setPosition(src->getPosition());
  // Copying edges
  // Copying attributes
  // Copying edges
  // Copying attributes
  // Copying edges
  for ( ListIterator<structure::ExternAliasDirectiveSyntax> it = src->getExternsListIteratorBegin(); it != src->getExternsListIteratorEnd(); ++it ) {
    structure::ExternAliasDirectiveSyntax* pNewEdge = dynamic_cast<structure::ExternAliasDirectiveSyntax*>(getMappedNode(&(*it)));
    if (pNewEdge)
      dest->addExterns(pNewEdge);
  }
  for ( ListIterator<structure::MemberDeclarationSyntax> it = src->getMembersListIteratorBegin(); it != src->getMembersListIteratorEnd(); ++it ) {
    structure::MemberDeclarationSyntax* pNewEdge = dynamic_cast<structure::MemberDeclarationSyntax*>(getMappedNode(&(*it)));
    if (pNewEdge)
      dest->addMembers(pNewEdge);
  }
  base::Base* pNewSingleEdge;
  pNewSingleEdge = getMappedNode(src->getName());
  if (pNewSingleEdge)
    dest->setName(dynamic_cast<expression::NameSyntax*>(pNewSingleEdge));
  for ( ListIterator<structure::UsingDirectiveSyntax> it = src->getUsingsListIteratorBegin(); it != src->getUsingsListIteratorEnd(); ++it ) {
    structure::UsingDirectiveSyntax* pNewEdge = dynamic_cast<structure::UsingDirectiveSyntax*>(getMappedNode(&(*it)));
    if (pNewEdge)
      dest->addUsings(pNewEdge);
  }
}

void AlgorithmDeepCopy::clone(structure::OperatorDeclarationSyntax* dest, const structure::OperatorDeclarationSyntax* src) {
  // Copying attributes
  // Copying edges
  // Copying attributes
  dest->setPosition(src->getPosition());
  // Copying edges
  // Copying attributes
  // Copying edges
  // Copying attributes
  // Copying edges
  for ( ListIterator<structure::EnumMemberDeclarationSyntax> it = src->getAccessedEnumMembersListIteratorBegin(); it != src->getAccessedEnumMembersListIteratorEnd(); ++it ) {
    structure::EnumMemberDeclarationSyntax* pNewEdge = dynamic_cast<structure::EnumMemberDeclarationSyntax*>(getMappedNode(&(*it)));
    if (pNewEdge)
      dest->addAccessedEnumMembers(pNewEdge);
  }
  for ( ListIterator<structure::AttributeListSyntax> it = src->getAttributeListsListIteratorBegin(); it != src->getAttributeListsListIteratorEnd(); ++it ) {
    structure::AttributeListSyntax* pNewEdge = dynamic_cast<structure::AttributeListSyntax*>(getMappedNode(&(*it)));
    if (pNewEdge)
      dest->addAttributeLists(pNewEdge);
  }
  base::Base* pNewSingleEdge;
  pNewSingleEdge = getMappedNode(src->getBody());
  if (pNewSingleEdge)
    dest->setBody(dynamic_cast<statement::BlockSyntax*>(pNewSingleEdge));
  pNewSingleEdge = getMappedNode(src->getExpressionBody());
  if (pNewSingleEdge)
    dest->setExpressionBody(dynamic_cast<structure::ArrowExpressionClauseSyntax*>(pNewSingleEdge));
  pNewSingleEdge = getMappedNode(src->getParameterList());
  if (pNewSingleEdge)
    dest->setParameterList(dynamic_cast<structure::ParameterListSyntax*>(pNewSingleEdge));
  // Copying attributes
  // Copying edges
  pNewSingleEdge = getMappedNode(src->getReturnType());
  if (pNewSingleEdge)
    dest->setReturnType(dynamic_cast<expression::TypeSyntax*>(pNewSingleEdge));
}

void AlgorithmDeepCopy::clone(structure::OperatorMemberCrefSyntax* dest, const structure::OperatorMemberCrefSyntax* src) {
  // Copying attributes
  // Copying edges
  // Copying attributes
  dest->setPosition(src->getPosition());
  // Copying edges
  // Copying attributes
  // Copying edges
  // Copying attributes
  // Copying edges
  // Copying attributes
  // Copying edges
  base::Base* pNewSingleEdge;
  pNewSingleEdge = getMappedNode(src->getParameters());
  if (pNewSingleEdge)
    dest->setParameters(dynamic_cast<structure::CrefParameterListSyntax*>(pNewSingleEdge));
}

void AlgorithmDeepCopy::clone(structure::OrderByClauseSyntax* dest, const structure::OrderByClauseSyntax* src) {
  // Copying attributes
  // Copying edges
  // Copying attributes
  dest->setPosition(src->getPosition());
  // Copying edges
  // Copying attributes
  // Copying edges
  // Copying attributes
  // Copying edges
  for ( ListIterator<structure::OrderingSyntax> it = src->getOrderingsListIteratorBegin(); it != src->getOrderingsListIteratorEnd(); ++it ) {
    structure::OrderingSyntax* pNewEdge = dynamic_cast<structure::OrderingSyntax*>(getMappedNode(&(*it)));
    if (pNewEdge)
      dest->addOrderings(pNewEdge);
  }
}

void AlgorithmDeepCopy::clone(structure::OrderingSyntax* dest, const structure::OrderingSyntax* src) {
  // Copying attributes
  // Copying edges
  // Copying attributes
  dest->setPosition(src->getPosition());
  // Copying edges
  // Copying attributes
  // Copying edges
  base::Base* pNewSingleEdge;
  pNewSingleEdge = getMappedNode(src->getExpression());
  if (pNewSingleEdge)
    dest->setExpression(dynamic_cast<expression::ExpressionSyntax*>(pNewSingleEdge));
}

void AlgorithmDeepCopy::clone(structure::ParameterListSyntax* dest, const structure::ParameterListSyntax* src) {
  // Copying attributes
  // Copying edges
  // Copying attributes
  dest->setPosition(src->getPosition());
  // Copying edges
  // Copying attributes
  // Copying edges
  for ( ListIterator<structure::ParameterSyntax> it = src->getParametersListIteratorBegin(); it != src->getParametersListIteratorEnd(); ++it ) {
    structure::ParameterSyntax* pNewEdge = dynamic_cast<structure::ParameterSyntax*>(getMappedNode(&(*it)));
    if (pNewEdge)
      dest->addParameters(pNewEdge);
  }
  // Copying attributes
  // Copying edges
}

void AlgorithmDeepCopy::clone(structure::ParameterSyntax* dest, const structure::ParameterSyntax* src) {
  // Copying attributes
  // Copying edges
  // Copying attributes
  dest->setPosition(src->getPosition());
  // Copying edges
  // Copying attributes
  dest->setIdentifier(src->getIdentifier());
  // Copying edges
  for ( ListIterator<structure::AttributeListSyntax> it = src->getAttributeListsListIteratorBegin(); it != src->getAttributeListsListIteratorEnd(); ++it ) {
    structure::AttributeListSyntax* pNewEdge = dynamic_cast<structure::AttributeListSyntax*>(getMappedNode(&(*it)));
    if (pNewEdge)
      dest->addAttributeLists(pNewEdge);
  }
  base::Base* pNewSingleEdge;
  pNewSingleEdge = getMappedNode(src->getDefault());
  if (pNewSingleEdge)
    dest->setDefault(dynamic_cast<structure::EqualsValueClauseSyntax*>(pNewSingleEdge));
  pNewSingleEdge = getMappedNode(src->getType());
  if (pNewSingleEdge)
    dest->setType(dynamic_cast<expression::TypeSyntax*>(pNewSingleEdge));
}

void AlgorithmDeepCopy::clone(structure::ParenthesizedVariableDesignationSyntax* dest, const structure::ParenthesizedVariableDesignationSyntax* src) {
  // Copying attributes
  // Copying edges
  // Copying attributes
  dest->setPosition(src->getPosition());
  // Copying edges
  // Copying attributes
  // Copying edges
  // Copying attributes
  // Copying edges
  for ( ListIterator<structure::VariableDesignationSyntax> it = src->getVariablesListIteratorBegin(); it != src->getVariablesListIteratorEnd(); ++it ) {
    structure::VariableDesignationSyntax* pNewEdge = dynamic_cast<structure::VariableDesignationSyntax*>(getMappedNode(&(*it)));
    if (pNewEdge)
      dest->addVariables(pNewEdge);
  }
}

void AlgorithmDeepCopy::clone(structure::PatternSyntax* dest, const structure::PatternSyntax* src) {
  // Copying attributes
  // Copying edges
  // Copying attributes
  dest->setPosition(src->getPosition());
  // Copying edges
  // Copying attributes
  // Copying edges
}

void AlgorithmDeepCopy::clone(structure::PositionalPatternClauseSyntax* dest, const structure::PositionalPatternClauseSyntax* src) {
  // Copying attributes
  // Copying edges
  // Copying attributes
  dest->setPosition(src->getPosition());
  // Copying edges
  // Copying attributes
  // Copying edges
  for ( ListIterator<structure::SubpatternSyntax> it = src->getSubpatternsListIteratorBegin(); it != src->getSubpatternsListIteratorEnd(); ++it ) {
    structure::SubpatternSyntax* pNewEdge = dynamic_cast<structure::SubpatternSyntax*>(getMappedNode(&(*it)));
    if (pNewEdge)
      dest->addSubpatterns(pNewEdge);
  }
}

void AlgorithmDeepCopy::clone(structure::PropertyDeclarationSyntax* dest, const structure::PropertyDeclarationSyntax* src) {
  // Copying attributes
  // Copying edges
  // Copying attributes
  dest->setPosition(src->getPosition());
  // Copying edges
  // Copying attributes
  // Copying edges
  // Copying attributes
  // Copying edges
  base::Base* pNewSingleEdge;
  pNewSingleEdge = getMappedNode(src->getAccessorList());
  if (pNewSingleEdge)
    dest->setAccessorList(dynamic_cast<structure::AccessorListSyntax*>(pNewSingleEdge));
  for ( ListIterator<structure::AttributeListSyntax> it = src->getAttributeListsListIteratorBegin(); it != src->getAttributeListsListIteratorEnd(); ++it ) {
    structure::AttributeListSyntax* pNewEdge = dynamic_cast<structure::AttributeListSyntax*>(getMappedNode(&(*it)));
    if (pNewEdge)
      dest->addAttributeLists(pNewEdge);
  }
  pNewSingleEdge = getMappedNode(src->getExplicitInterfaceSpecifier());
  if (pNewSingleEdge)
    dest->setExplicitInterfaceSpecifier(dynamic_cast<structure::ExplicitInterfaceSpecifierSyntax*>(pNewSingleEdge));
  pNewSingleEdge = getMappedNode(src->getType());
  if (pNewSingleEdge)
    dest->setType(dynamic_cast<expression::TypeSyntax*>(pNewSingleEdge));
  // Copying attributes
  dest->setIdentifier(src->getIdentifier());
  // Copying edges
  pNewSingleEdge = getMappedNode(src->getExpressionBody());
  if (pNewSingleEdge)
    dest->setExpressionBody(dynamic_cast<structure::ArrowExpressionClauseSyntax*>(pNewSingleEdge));
  pNewSingleEdge = getMappedNode(src->getInitializer());
  if (pNewSingleEdge)
    dest->setInitializer(dynamic_cast<structure::EqualsValueClauseSyntax*>(pNewSingleEdge));
}

void AlgorithmDeepCopy::clone(structure::PropertyPatternClauseSyntax* dest, const structure::PropertyPatternClauseSyntax* src) {
  // Copying attributes
  // Copying edges
  // Copying attributes
  dest->setPosition(src->getPosition());
  // Copying edges
  // Copying attributes
  // Copying edges
  for ( ListIterator<structure::SubpatternSyntax> it = src->getSubpatternsListIteratorBegin(); it != src->getSubpatternsListIteratorEnd(); ++it ) {
    structure::SubpatternSyntax* pNewEdge = dynamic_cast<structure::SubpatternSyntax*>(getMappedNode(&(*it)));
    if (pNewEdge)
      dest->addSubpatterns(pNewEdge);
  }
}

void AlgorithmDeepCopy::clone(structure::QualifiedCrefSyntax* dest, const structure::QualifiedCrefSyntax* src) {
  // Copying attributes
  // Copying edges
  // Copying attributes
  dest->setPosition(src->getPosition());
  // Copying edges
  // Copying attributes
  // Copying edges
  // Copying attributes
  // Copying edges
  base::Base* pNewSingleEdge;
  pNewSingleEdge = getMappedNode(src->getContainer());
  if (pNewSingleEdge)
    dest->setContainer(dynamic_cast<expression::TypeSyntax*>(pNewSingleEdge));
  pNewSingleEdge = getMappedNode(src->getMember());
  if (pNewSingleEdge)
    dest->setMember(dynamic_cast<structure::MemberCrefSyntax*>(pNewSingleEdge));
}

void AlgorithmDeepCopy::clone(structure::QueryBodySyntax* dest, const structure::QueryBodySyntax* src) {
  // Copying attributes
  // Copying edges
  // Copying attributes
  dest->setPosition(src->getPosition());
  // Copying edges
  // Copying attributes
  // Copying edges
  for ( ListIterator<structure::QueryClauseSyntax> it = src->getClausesListIteratorBegin(); it != src->getClausesListIteratorEnd(); ++it ) {
    structure::QueryClauseSyntax* pNewEdge = dynamic_cast<structure::QueryClauseSyntax*>(getMappedNode(&(*it)));
    if (pNewEdge)
      dest->addClauses(pNewEdge);
  }
  base::Base* pNewSingleEdge;
  pNewSingleEdge = getMappedNode(src->getContinuation());
  if (pNewSingleEdge)
    dest->setContinuation(dynamic_cast<structure::QueryContinuationSyntax*>(pNewSingleEdge));
  pNewSingleEdge = getMappedNode(src->getSelectOrGroup());
  if (pNewSingleEdge)
    dest->setSelectOrGroup(dynamic_cast<structure::SelectOrGroupClauseSyntax*>(pNewSingleEdge));
}

void AlgorithmDeepCopy::clone(structure::QueryClauseSyntax* dest, const structure::QueryClauseSyntax* src) {
  // Copying attributes
  // Copying edges
  // Copying attributes
  dest->setPosition(src->getPosition());
  // Copying edges
  // Copying attributes
  // Copying edges
}

void AlgorithmDeepCopy::clone(structure::QueryContinuationSyntax* dest, const structure::QueryContinuationSyntax* src) {
  // Copying attributes
  // Copying edges
  // Copying attributes
  dest->setPosition(src->getPosition());
  // Copying edges
  // Copying attributes
  dest->setIdentifier(src->getIdentifier());
  // Copying edges
  base::Base* pNewSingleEdge;
  pNewSingleEdge = getMappedNode(src->getBody());
  if (pNewSingleEdge)
    dest->setBody(dynamic_cast<structure::QueryBodySyntax*>(pNewSingleEdge));
}

void AlgorithmDeepCopy::clone(structure::RecursivePatternSyntax* dest, const structure::RecursivePatternSyntax* src) {
  // Copying attributes
  // Copying edges
  // Copying attributes
  dest->setPosition(src->getPosition());
  // Copying edges
  // Copying attributes
  // Copying edges
  // Copying attributes
  // Copying edges
  base::Base* pNewSingleEdge;
  pNewSingleEdge = getMappedNode(src->getDesignation());
  if (pNewSingleEdge)
    dest->setDesignation(dynamic_cast<structure::VariableDesignationSyntax*>(pNewSingleEdge));
  pNewSingleEdge = getMappedNode(src->getPositionalPatternClause());
  if (pNewSingleEdge)
    dest->setPositionalPatternClause(dynamic_cast<structure::PositionalPatternClauseSyntax*>(pNewSingleEdge));
  pNewSingleEdge = getMappedNode(src->getPropertyPatternClause());
  if (pNewSingleEdge)
    dest->setPropertyPatternClause(dynamic_cast<structure::PropertyPatternClauseSyntax*>(pNewSingleEdge));
  pNewSingleEdge = getMappedNode(src->getType());
  if (pNewSingleEdge)
    dest->setType(dynamic_cast<expression::TypeSyntax*>(pNewSingleEdge));
}

void AlgorithmDeepCopy::clone(structure::SelectClauseSyntax* dest, const structure::SelectClauseSyntax* src) {
  // Copying attributes
  // Copying edges
  // Copying attributes
  dest->setPosition(src->getPosition());
  // Copying edges
  // Copying attributes
  // Copying edges
  // Copying attributes
  // Copying edges
  base::Base* pNewSingleEdge;
  pNewSingleEdge = getMappedNode(src->getExpression());
  if (pNewSingleEdge)
    dest->setExpression(dynamic_cast<expression::ExpressionSyntax*>(pNewSingleEdge));
}

void AlgorithmDeepCopy::clone(structure::SelectOrGroupClauseSyntax* dest, const structure::SelectOrGroupClauseSyntax* src) {
  // Copying attributes
  // Copying edges
  // Copying attributes
  dest->setPosition(src->getPosition());
  // Copying edges
  // Copying attributes
  // Copying edges
}

void AlgorithmDeepCopy::clone(structure::SimpleBaseTypeSyntax* dest, const structure::SimpleBaseTypeSyntax* src) {
  // Copying attributes
  // Copying edges
  // Copying attributes
  dest->setPosition(src->getPosition());
  // Copying edges
  // Copying attributes
  // Copying edges
  base::Base* pNewSingleEdge;
  pNewSingleEdge = getMappedNode(src->getType());
  if (pNewSingleEdge)
    dest->setType(dynamic_cast<expression::TypeSyntax*>(pNewSingleEdge));
  // Copying attributes
  // Copying edges
}

void AlgorithmDeepCopy::clone(structure::SingleVariableDesignationSyntax* dest, const structure::SingleVariableDesignationSyntax* src) {
  // Copying attributes
  // Copying edges
  // Copying attributes
  dest->setPosition(src->getPosition());
  // Copying edges
  // Copying attributes
  // Copying edges
  // Copying attributes
  dest->setIdentifier(src->getIdentifier());
  // Copying edges
}

void AlgorithmDeepCopy::clone(structure::StructDeclarationSyntax* dest, const structure::StructDeclarationSyntax* src) {
  // Copying attributes
  // Copying edges
  // Copying attributes
  dest->setPosition(src->getPosition());
  // Copying edges
  // Copying attributes
  // Copying edges
  // Copying attributes
  dest->setIdentifier(src->getIdentifier());
  // Copying edges
  for ( ListIterator<structure::AttributeListSyntax> it = src->getAttributeListsListIteratorBegin(); it != src->getAttributeListsListIteratorEnd(); ++it ) {
    structure::AttributeListSyntax* pNewEdge = dynamic_cast<structure::AttributeListSyntax*>(getMappedNode(&(*it)));
    if (pNewEdge)
      dest->addAttributeLists(pNewEdge);
  }
  base::Base* pNewSingleEdge;
  pNewSingleEdge = getMappedNode(src->getBaseList());
  if (pNewSingleEdge)
    dest->setBaseList(dynamic_cast<structure::BaseListSyntax*>(pNewSingleEdge));
  // Copying attributes
  // Copying edges
  for ( ListIterator<structure::TypeParameterConstraintClauseSyntax> it = src->getConstraintClausesListIteratorBegin(); it != src->getConstraintClausesListIteratorEnd(); ++it ) {
    structure::TypeParameterConstraintClauseSyntax* pNewEdge = dynamic_cast<structure::TypeParameterConstraintClauseSyntax*>(getMappedNode(&(*it)));
    if (pNewEdge)
      dest->addConstraintClauses(pNewEdge);
  }
  for ( ListIterator<structure::MemberDeclarationSyntax> it = src->getMembersListIteratorBegin(); it != src->getMembersListIteratorEnd(); ++it ) {
    structure::MemberDeclarationSyntax* pNewEdge = dynamic_cast<structure::MemberDeclarationSyntax*>(getMappedNode(&(*it)));
    if (pNewEdge)
      dest->addMembers(pNewEdge);
  }
  pNewSingleEdge = getMappedNode(src->getTypeParameterList());
  if (pNewSingleEdge)
    dest->setTypeParameterList(dynamic_cast<structure::TypeParameterListSyntax*>(pNewSingleEdge));
  // Copying attributes
  // Copying edges
}

void AlgorithmDeepCopy::clone(structure::SubpatternSyntax* dest, const structure::SubpatternSyntax* src) {
  // Copying attributes
  // Copying edges
  // Copying attributes
  dest->setPosition(src->getPosition());
  // Copying edges
  // Copying attributes
  // Copying edges
  base::Base* pNewSingleEdge;
  pNewSingleEdge = getMappedNode(src->getPattern());
  if (pNewSingleEdge)
    dest->setPattern(dynamic_cast<structure::PatternSyntax*>(pNewSingleEdge));
}

void AlgorithmDeepCopy::clone(structure::SwitchExpressionArmSyntax* dest, const structure::SwitchExpressionArmSyntax* src) {
  // Copying attributes
  // Copying edges
  // Copying attributes
  dest->setPosition(src->getPosition());
  // Copying edges
  // Copying attributes
  // Copying edges
  base::Base* pNewSingleEdge;
  pNewSingleEdge = getMappedNode(src->getExpression());
  if (pNewSingleEdge)
    dest->setExpression(dynamic_cast<expression::ExpressionSyntax*>(pNewSingleEdge));
  pNewSingleEdge = getMappedNode(src->getPattern());
  if (pNewSingleEdge)
    dest->setPattern(dynamic_cast<structure::PatternSyntax*>(pNewSingleEdge));
  pNewSingleEdge = getMappedNode(src->getWhenClause());
  if (pNewSingleEdge)
    dest->setWhenClause(dynamic_cast<structure::WhenClauseSyntax*>(pNewSingleEdge));
}

void AlgorithmDeepCopy::clone(structure::SwitchLabelSyntax* dest, const structure::SwitchLabelSyntax* src) {
  // Copying attributes
  // Copying edges
  // Copying attributes
  dest->setPosition(src->getPosition());
  // Copying edges
  // Copying attributes
  // Copying edges
}

void AlgorithmDeepCopy::clone(structure::SwitchSectionSyntax* dest, const structure::SwitchSectionSyntax* src) {
  // Copying attributes
  // Copying edges
  // Copying attributes
  dest->setPosition(src->getPosition());
  // Copying edges
  // Copying attributes
  // Copying edges
  for ( ListIterator<structure::SwitchLabelSyntax> it = src->getLabelsListIteratorBegin(); it != src->getLabelsListIteratorEnd(); ++it ) {
    structure::SwitchLabelSyntax* pNewEdge = dynamic_cast<structure::SwitchLabelSyntax*>(getMappedNode(&(*it)));
    if (pNewEdge)
      dest->addLabels(pNewEdge);
  }
  for ( ListIterator<statement::StatementSyntax> it = src->getStatementsListIteratorBegin(); it != src->getStatementsListIteratorEnd(); ++it ) {
    statement::StatementSyntax* pNewEdge = dynamic_cast<statement::StatementSyntax*>(getMappedNode(&(*it)));
    if (pNewEdge)
      dest->addStatements(pNewEdge);
  }
}

void AlgorithmDeepCopy::clone(structure::SyntaxToken* dest, const structure::SyntaxToken* src) {
  // Copying attributes
  // Copying edges
  // Copying attributes
  dest->setPosition(src->getPosition());
  // Copying edges
  // Copying attributes
  // Copying edges
}

void AlgorithmDeepCopy::clone(structure::TupleElementSyntax* dest, const structure::TupleElementSyntax* src) {
  // Copying attributes
  // Copying edges
  // Copying attributes
  dest->setPosition(src->getPosition());
  // Copying edges
  // Copying attributes
  dest->setIdentifier(src->getIdentifier());
  // Copying edges
  base::Base* pNewSingleEdge;
  pNewSingleEdge = getMappedNode(src->getType());
  if (pNewSingleEdge)
    dest->setType(dynamic_cast<expression::TypeSyntax*>(pNewSingleEdge));
}

void AlgorithmDeepCopy::clone(structure::TypeArgumentListSyntax* dest, const structure::TypeArgumentListSyntax* src) {
  // Copying attributes
  // Copying edges
  // Copying attributes
  dest->setPosition(src->getPosition());
  // Copying edges
  // Copying attributes
  // Copying edges
  for ( ListIterator<expression::TypeSyntax> it = src->getArgumentsListIteratorBegin(); it != src->getArgumentsListIteratorEnd(); ++it ) {
    expression::TypeSyntax* pNewEdge = dynamic_cast<expression::TypeSyntax*>(getMappedNode(&(*it)));
    if (pNewEdge)
      dest->addArguments(pNewEdge);
  }
}

void AlgorithmDeepCopy::clone(structure::TypeConstraintSyntax* dest, const structure::TypeConstraintSyntax* src) {
  // Copying attributes
  // Copying edges
  // Copying attributes
  dest->setPosition(src->getPosition());
  // Copying edges
  // Copying attributes
  // Copying edges
  // Copying attributes
  // Copying edges
  base::Base* pNewSingleEdge;
  pNewSingleEdge = getMappedNode(src->getType());
  if (pNewSingleEdge)
    dest->setType(dynamic_cast<expression::TypeSyntax*>(pNewSingleEdge));
}

void AlgorithmDeepCopy::clone(structure::TypeCrefSyntax* dest, const structure::TypeCrefSyntax* src) {
  // Copying attributes
  // Copying edges
  // Copying attributes
  dest->setPosition(src->getPosition());
  // Copying edges
  // Copying attributes
  // Copying edges
  // Copying attributes
  // Copying edges
  base::Base* pNewSingleEdge;
  pNewSingleEdge = getMappedNode(src->getType());
  if (pNewSingleEdge)
    dest->setType(dynamic_cast<expression::TypeSyntax*>(pNewSingleEdge));
}

void AlgorithmDeepCopy::clone(structure::TypeDeclarationSyntax* dest, const structure::TypeDeclarationSyntax* src) {
  // Copying attributes
  // Copying edges
  // Copying attributes
  dest->setPosition(src->getPosition());
  // Copying edges
  // Copying attributes
  // Copying edges
  // Copying attributes
  dest->setIdentifier(src->getIdentifier());
  // Copying edges
  for ( ListIterator<structure::AttributeListSyntax> it = src->getAttributeListsListIteratorBegin(); it != src->getAttributeListsListIteratorEnd(); ++it ) {
    structure::AttributeListSyntax* pNewEdge = dynamic_cast<structure::AttributeListSyntax*>(getMappedNode(&(*it)));
    if (pNewEdge)
      dest->addAttributeLists(pNewEdge);
  }
  base::Base* pNewSingleEdge;
  pNewSingleEdge = getMappedNode(src->getBaseList());
  if (pNewSingleEdge)
    dest->setBaseList(dynamic_cast<structure::BaseListSyntax*>(pNewSingleEdge));
  // Copying attributes
  // Copying edges
  for ( ListIterator<structure::TypeParameterConstraintClauseSyntax> it = src->getConstraintClausesListIteratorBegin(); it != src->getConstraintClausesListIteratorEnd(); ++it ) {
    structure::TypeParameterConstraintClauseSyntax* pNewEdge = dynamic_cast<structure::TypeParameterConstraintClauseSyntax*>(getMappedNode(&(*it)));
    if (pNewEdge)
      dest->addConstraintClauses(pNewEdge);
  }
  for ( ListIterator<structure::MemberDeclarationSyntax> it = src->getMembersListIteratorBegin(); it != src->getMembersListIteratorEnd(); ++it ) {
    structure::MemberDeclarationSyntax* pNewEdge = dynamic_cast<structure::MemberDeclarationSyntax*>(getMappedNode(&(*it)));
    if (pNewEdge)
      dest->addMembers(pNewEdge);
  }
  pNewSingleEdge = getMappedNode(src->getTypeParameterList());
  if (pNewSingleEdge)
    dest->setTypeParameterList(dynamic_cast<structure::TypeParameterListSyntax*>(pNewSingleEdge));
}

void AlgorithmDeepCopy::clone(structure::TypeParameterConstraintClauseSyntax* dest, const structure::TypeParameterConstraintClauseSyntax* src) {
  // Copying attributes
  // Copying edges
  // Copying attributes
  dest->setPosition(src->getPosition());
  // Copying edges
  // Copying attributes
  // Copying edges
  for ( ListIterator<structure::TypeParameterConstraintSyntax> it = src->getConstraintsListIteratorBegin(); it != src->getConstraintsListIteratorEnd(); ++it ) {
    structure::TypeParameterConstraintSyntax* pNewEdge = dynamic_cast<structure::TypeParameterConstraintSyntax*>(getMappedNode(&(*it)));
    if (pNewEdge)
      dest->addConstraints(pNewEdge);
  }
  base::Base* pNewSingleEdge;
  pNewSingleEdge = getMappedNode(src->getName());
  if (pNewSingleEdge)
    dest->setName(dynamic_cast<expression::IdentifierNameSyntax*>(pNewSingleEdge));
}

void AlgorithmDeepCopy::clone(structure::TypeParameterConstraintSyntax* dest, const structure::TypeParameterConstraintSyntax* src) {
  // Copying attributes
  // Copying edges
  // Copying attributes
  dest->setPosition(src->getPosition());
  // Copying edges
  // Copying attributes
  // Copying edges
}

void AlgorithmDeepCopy::clone(structure::TypeParameterListSyntax* dest, const structure::TypeParameterListSyntax* src) {
  // Copying attributes
  // Copying edges
  // Copying attributes
  dest->setPosition(src->getPosition());
  // Copying edges
  // Copying attributes
  // Copying edges
  for ( ListIterator<structure::TypeParameterSyntax> it = src->getParametersListIteratorBegin(); it != src->getParametersListIteratorEnd(); ++it ) {
    structure::TypeParameterSyntax* pNewEdge = dynamic_cast<structure::TypeParameterSyntax*>(getMappedNode(&(*it)));
    if (pNewEdge)
      dest->addParameters(pNewEdge);
  }
}

void AlgorithmDeepCopy::clone(structure::TypeParameterSyntax* dest, const structure::TypeParameterSyntax* src) {
  // Copying attributes
  // Copying edges
  // Copying attributes
  dest->setPosition(src->getPosition());
  // Copying edges
  // Copying attributes
  dest->setIdentifier(src->getIdentifier());
  // Copying edges
  for ( ListIterator<structure::AttributeListSyntax> it = src->getAttributeListsListIteratorBegin(); it != src->getAttributeListsListIteratorEnd(); ++it ) {
    structure::AttributeListSyntax* pNewEdge = dynamic_cast<structure::AttributeListSyntax*>(getMappedNode(&(*it)));
    if (pNewEdge)
      dest->addAttributeLists(pNewEdge);
  }
}

void AlgorithmDeepCopy::clone(structure::UsingDirectiveSyntax* dest, const structure::UsingDirectiveSyntax* src) {
  // Copying attributes
  // Copying edges
  // Copying attributes
  dest->setPosition(src->getPosition());
  // Copying edges
  // Copying attributes
  // Copying edges
  base::Base* pNewSingleEdge;
  pNewSingleEdge = getMappedNode(src->getAlias());
  if (pNewSingleEdge)
    dest->setAlias(dynamic_cast<structure::NameEqualsSyntax*>(pNewSingleEdge));
  pNewSingleEdge = getMappedNode(src->getName());
  if (pNewSingleEdge)
    dest->setName(dynamic_cast<expression::NameSyntax*>(pNewSingleEdge));
}

void AlgorithmDeepCopy::clone(structure::VarPatternSyntax* dest, const structure::VarPatternSyntax* src) {
  // Copying attributes
  // Copying edges
  // Copying attributes
  dest->setPosition(src->getPosition());
  // Copying edges
  // Copying attributes
  // Copying edges
  // Copying attributes
  // Copying edges
  base::Base* pNewSingleEdge;
  pNewSingleEdge = getMappedNode(src->getDesignation());
  if (pNewSingleEdge)
    dest->setDesignation(dynamic_cast<structure::VariableDesignationSyntax*>(pNewSingleEdge));
}

void AlgorithmDeepCopy::clone(structure::VariableDeclarationSyntax* dest, const structure::VariableDeclarationSyntax* src) {
  // Copying attributes
  // Copying edges
  // Copying attributes
  dest->setPosition(src->getPosition());
  // Copying edges
  // Copying attributes
  // Copying edges
  base::Base* pNewSingleEdge;
  pNewSingleEdge = getMappedNode(src->getType());
  if (pNewSingleEdge)
    dest->setType(dynamic_cast<expression::TypeSyntax*>(pNewSingleEdge));
  for ( ListIterator<structure::VariableDeclaratorSyntax> it = src->getVariablesListIteratorBegin(); it != src->getVariablesListIteratorEnd(); ++it ) {
    structure::VariableDeclaratorSyntax* pNewEdge = dynamic_cast<structure::VariableDeclaratorSyntax*>(getMappedNode(&(*it)));
    if (pNewEdge)
      dest->addVariables(pNewEdge);
  }
}

void AlgorithmDeepCopy::clone(structure::VariableDeclaratorSyntax* dest, const structure::VariableDeclaratorSyntax* src) {
  // Copying attributes
  // Copying edges
  // Copying attributes
  dest->setPosition(src->getPosition());
  // Copying edges
  // Copying attributes
  dest->setIdentifier(src->getIdentifier());
  // Copying edges
  base::Base* pNewSingleEdge;
  pNewSingleEdge = getMappedNode(src->getArgumentList());
  if (pNewSingleEdge)
    dest->setArgumentList(dynamic_cast<structure::BracketedArgumentListSyntax*>(pNewSingleEdge));
  pNewSingleEdge = getMappedNode(src->getInitializer());
  if (pNewSingleEdge)
    dest->setInitializer(dynamic_cast<structure::EqualsValueClauseSyntax*>(pNewSingleEdge));
}

void AlgorithmDeepCopy::clone(structure::VariableDesignationSyntax* dest, const structure::VariableDesignationSyntax* src) {
  // Copying attributes
  // Copying edges
  // Copying attributes
  dest->setPosition(src->getPosition());
  // Copying edges
  // Copying attributes
  // Copying edges
}

void AlgorithmDeepCopy::clone(structure::WhenClauseSyntax* dest, const structure::WhenClauseSyntax* src) {
  // Copying attributes
  // Copying edges
  // Copying attributes
  dest->setPosition(src->getPosition());
  // Copying edges
  // Copying attributes
  // Copying edges
  base::Base* pNewSingleEdge;
  pNewSingleEdge = getMappedNode(src->getCondition());
  if (pNewSingleEdge)
    dest->setCondition(dynamic_cast<expression::ExpressionSyntax*>(pNewSingleEdge));
}

void AlgorithmDeepCopy::clone(structure::WhereClauseSyntax* dest, const structure::WhereClauseSyntax* src) {
  // Copying attributes
  // Copying edges
  // Copying attributes
  dest->setPosition(src->getPosition());
  // Copying edges
  // Copying attributes
  // Copying edges
  // Copying attributes
  // Copying edges
  base::Base* pNewSingleEdge;
  pNewSingleEdge = getMappedNode(src->getCondition());
  if (pNewSingleEdge)
    dest->setCondition(dynamic_cast<expression::ExpressionSyntax*>(pNewSingleEdge));
}

void AlgorithmDeepCopy::clone(structure::XmlAttributeSyntax* dest, const structure::XmlAttributeSyntax* src) {
  // Copying attributes
  // Copying edges
  // Copying attributes
  dest->setPosition(src->getPosition());
  // Copying edges
  // Copying attributes
  // Copying edges
  base::Base* pNewSingleEdge;
  pNewSingleEdge = getMappedNode(src->getName());
  if (pNewSingleEdge)
    dest->setName(dynamic_cast<structure::XmlNameSyntax*>(pNewSingleEdge));
}

void AlgorithmDeepCopy::clone(structure::XmlCDataSectionSyntax* dest, const structure::XmlCDataSectionSyntax* src) {
  // Copying attributes
  // Copying edges
  // Copying attributes
  dest->setPosition(src->getPosition());
  // Copying edges
  // Copying attributes
  // Copying edges
  // Copying attributes
  // Copying edges
}

void AlgorithmDeepCopy::clone(structure::XmlCommentSyntax* dest, const structure::XmlCommentSyntax* src) {
  // Copying attributes
  // Copying edges
  // Copying attributes
  dest->setPosition(src->getPosition());
  // Copying edges
  // Copying attributes
  // Copying edges
  // Copying attributes
  // Copying edges
}

void AlgorithmDeepCopy::clone(structure::XmlCrefAttributeSyntax* dest, const structure::XmlCrefAttributeSyntax* src) {
  // Copying attributes
  // Copying edges
  // Copying attributes
  dest->setPosition(src->getPosition());
  // Copying edges
  // Copying attributes
  // Copying edges
  base::Base* pNewSingleEdge;
  pNewSingleEdge = getMappedNode(src->getName());
  if (pNewSingleEdge)
    dest->setName(dynamic_cast<structure::XmlNameSyntax*>(pNewSingleEdge));
  // Copying attributes
  // Copying edges
  pNewSingleEdge = getMappedNode(src->getCref());
  if (pNewSingleEdge)
    dest->setCref(dynamic_cast<structure::CrefSyntax*>(pNewSingleEdge));
}

void AlgorithmDeepCopy::clone(structure::XmlElementEndTagSyntax* dest, const structure::XmlElementEndTagSyntax* src) {
  // Copying attributes
  // Copying edges
  // Copying attributes
  dest->setPosition(src->getPosition());
  // Copying edges
  // Copying attributes
  // Copying edges
  base::Base* pNewSingleEdge;
  pNewSingleEdge = getMappedNode(src->getName());
  if (pNewSingleEdge)
    dest->setName(dynamic_cast<structure::XmlNameSyntax*>(pNewSingleEdge));
}

void AlgorithmDeepCopy::clone(structure::XmlElementStartTagSyntax* dest, const structure::XmlElementStartTagSyntax* src) {
  // Copying attributes
  // Copying edges
  // Copying attributes
  dest->setPosition(src->getPosition());
  // Copying edges
  // Copying attributes
  // Copying edges
  for ( ListIterator<structure::XmlAttributeSyntax> it = src->getAttributesListIteratorBegin(); it != src->getAttributesListIteratorEnd(); ++it ) {
    structure::XmlAttributeSyntax* pNewEdge = dynamic_cast<structure::XmlAttributeSyntax*>(getMappedNode(&(*it)));
    if (pNewEdge)
      dest->addAttributes(pNewEdge);
  }
  base::Base* pNewSingleEdge;
  pNewSingleEdge = getMappedNode(src->getName());
  if (pNewSingleEdge)
    dest->setName(dynamic_cast<structure::XmlNameSyntax*>(pNewSingleEdge));
}

void AlgorithmDeepCopy::clone(structure::XmlElementSyntax* dest, const structure::XmlElementSyntax* src) {
  // Copying attributes
  // Copying edges
  // Copying attributes
  dest->setPosition(src->getPosition());
  // Copying edges
  // Copying attributes
  // Copying edges
  // Copying attributes
  // Copying edges
  for ( ListIterator<structure::XmlNodeSyntax> it = src->getContentListIteratorBegin(); it != src->getContentListIteratorEnd(); ++it ) {
    structure::XmlNodeSyntax* pNewEdge = dynamic_cast<structure::XmlNodeSyntax*>(getMappedNode(&(*it)));
    if (pNewEdge)
      dest->addContent(pNewEdge);
  }
  base::Base* pNewSingleEdge;
  pNewSingleEdge = getMappedNode(src->getEndTag());
  if (pNewSingleEdge)
    dest->setEndTag(dynamic_cast<structure::XmlElementEndTagSyntax*>(pNewSingleEdge));
  pNewSingleEdge = getMappedNode(src->getStartTag());
  if (pNewSingleEdge)
    dest->setStartTag(dynamic_cast<structure::XmlElementStartTagSyntax*>(pNewSingleEdge));
}

void AlgorithmDeepCopy::clone(structure::XmlEmptyElementSyntax* dest, const structure::XmlEmptyElementSyntax* src) {
  // Copying attributes
  // Copying edges
  // Copying attributes
  dest->setPosition(src->getPosition());
  // Copying edges
  // Copying attributes
  // Copying edges
  // Copying attributes
  // Copying edges
  for ( ListIterator<structure::XmlAttributeSyntax> it = src->getAttributesListIteratorBegin(); it != src->getAttributesListIteratorEnd(); ++it ) {
    structure::XmlAttributeSyntax* pNewEdge = dynamic_cast<structure::XmlAttributeSyntax*>(getMappedNode(&(*it)));
    if (pNewEdge)
      dest->addAttributes(pNewEdge);
  }
  base::Base* pNewSingleEdge;
  pNewSingleEdge = getMappedNode(src->getName());
  if (pNewSingleEdge)
    dest->setName(dynamic_cast<structure::XmlNameSyntax*>(pNewSingleEdge));
}

void AlgorithmDeepCopy::clone(structure::XmlNameAttributeSyntax* dest, const structure::XmlNameAttributeSyntax* src) {
  // Copying attributes
  // Copying edges
  // Copying attributes
  dest->setPosition(src->getPosition());
  // Copying edges
  // Copying attributes
  // Copying edges
  base::Base* pNewSingleEdge;
  pNewSingleEdge = getMappedNode(src->getName());
  if (pNewSingleEdge)
    dest->setName(dynamic_cast<structure::XmlNameSyntax*>(pNewSingleEdge));
  // Copying attributes
  // Copying edges
  pNewSingleEdge = getMappedNode(src->getIdentifier());
  if (pNewSingleEdge)
    dest->setIdentifier(dynamic_cast<expression::IdentifierNameSyntax*>(pNewSingleEdge));
}

void AlgorithmDeepCopy::clone(structure::XmlNameSyntax* dest, const structure::XmlNameSyntax* src) {
  // Copying attributes
  // Copying edges
  // Copying attributes
  dest->setPosition(src->getPosition());
  // Copying edges
  // Copying attributes
  // Copying edges
  base::Base* pNewSingleEdge;
  pNewSingleEdge = getMappedNode(src->getPrefix());
  if (pNewSingleEdge)
    dest->setPrefix(dynamic_cast<structure::XmlPrefixSyntax*>(pNewSingleEdge));
}

void AlgorithmDeepCopy::clone(structure::XmlNodeSyntax* dest, const structure::XmlNodeSyntax* src) {
  // Copying attributes
  // Copying edges
  // Copying attributes
  dest->setPosition(src->getPosition());
  // Copying edges
  // Copying attributes
  // Copying edges
}

void AlgorithmDeepCopy::clone(structure::XmlPrefixSyntax* dest, const structure::XmlPrefixSyntax* src) {
  // Copying attributes
  // Copying edges
  // Copying attributes
  dest->setPosition(src->getPosition());
  // Copying edges
  // Copying attributes
  // Copying edges
}

void AlgorithmDeepCopy::clone(structure::XmlProcessingInstructionSyntax* dest, const structure::XmlProcessingInstructionSyntax* src) {
  // Copying attributes
  // Copying edges
  // Copying attributes
  dest->setPosition(src->getPosition());
  // Copying edges
  // Copying attributes
  // Copying edges
  // Copying attributes
  // Copying edges
  base::Base* pNewSingleEdge;
  pNewSingleEdge = getMappedNode(src->getName());
  if (pNewSingleEdge)
    dest->setName(dynamic_cast<structure::XmlNameSyntax*>(pNewSingleEdge));
}

void AlgorithmDeepCopy::clone(structure::XmlTextAttributeSyntax* dest, const structure::XmlTextAttributeSyntax* src) {
  // Copying attributes
  // Copying edges
  // Copying attributes
  dest->setPosition(src->getPosition());
  // Copying edges
  // Copying attributes
  // Copying edges
  base::Base* pNewSingleEdge;
  pNewSingleEdge = getMappedNode(src->getName());
  if (pNewSingleEdge)
    dest->setName(dynamic_cast<structure::XmlNameSyntax*>(pNewSingleEdge));
  // Copying attributes
  // Copying edges
}

void AlgorithmDeepCopy::clone(structure::XmlTextSyntax* dest, const structure::XmlTextSyntax* src) {
  // Copying attributes
  // Copying edges
  // Copying attributes
  dest->setPosition(src->getPosition());
  // Copying edges
  // Copying attributes
  // Copying edges
  // Copying attributes
  // Copying edges
}


}}}
