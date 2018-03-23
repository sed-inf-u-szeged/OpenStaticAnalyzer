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

#ifndef _CSHARP_Common_H_
#define _CSHARP_Common_H_

#include "csharp/inc/csharp.h"

/**
* \file Common.h
* \brief Contains declaration of Common namespace.
*/

namespace columbus { namespace csharp { namespace asg {
  typedef unsigned int NodeHashType;
  /**
  * \brief Common contains general graph algorithms and common functions
  */
  namespace Common {
      /**
      * \brief Decides whether the node is base::Positioned or not.
      * \param node [in] The node whose kind is examined.
      * \return Returns true if the node is base::Positioned.
      */
      bool getIsPositioned(const base::Base& node);

      /**
      * \brief Decides whether the node is expression::AliasQualifiedNameSyntax or not.
      * \param node [in] The node whose kind is examined.
      * \return Returns true if the node is expression::AliasQualifiedNameSyntax.
      */
      bool getIsAliasQualifiedNameSyntax(const base::Base& node);

      /**
      * \brief Decides whether the node is expression::AnonymousFunctionExpressionSyntax or not.
      * \param node [in] The node whose kind is examined.
      * \return Returns true if the node is expression::AnonymousFunctionExpressionSyntax.
      */
      bool getIsAnonymousFunctionExpressionSyntax(const base::Base& node);

      /**
      * \brief Decides whether the node is expression::AnonymousMethodExpressionSyntax or not.
      * \param node [in] The node whose kind is examined.
      * \return Returns true if the node is expression::AnonymousMethodExpressionSyntax.
      */
      bool getIsAnonymousMethodExpressionSyntax(const base::Base& node);

      /**
      * \brief Decides whether the node is expression::AnonymousObjectCreationExpressionSyntax or not.
      * \param node [in] The node whose kind is examined.
      * \return Returns true if the node is expression::AnonymousObjectCreationExpressionSyntax.
      */
      bool getIsAnonymousObjectCreationExpressionSyntax(const base::Base& node);

      /**
      * \brief Decides whether the node is expression::ArrayCreationExpressionSyntax or not.
      * \param node [in] The node whose kind is examined.
      * \return Returns true if the node is expression::ArrayCreationExpressionSyntax.
      */
      bool getIsArrayCreationExpressionSyntax(const base::Base& node);

      /**
      * \brief Decides whether the node is expression::ArrayTypeSyntax or not.
      * \param node [in] The node whose kind is examined.
      * \return Returns true if the node is expression::ArrayTypeSyntax.
      */
      bool getIsArrayTypeSyntax(const base::Base& node);

      /**
      * \brief Decides whether the node is expression::AssignmentExpressionSyntax or not.
      * \param node [in] The node whose kind is examined.
      * \return Returns true if the node is expression::AssignmentExpressionSyntax.
      */
      bool getIsAssignmentExpressionSyntax(const base::Base& node);

      /**
      * \brief Decides whether the node is expression::AwaitExpressionSyntax or not.
      * \param node [in] The node whose kind is examined.
      * \return Returns true if the node is expression::AwaitExpressionSyntax.
      */
      bool getIsAwaitExpressionSyntax(const base::Base& node);

      /**
      * \brief Decides whether the node is expression::BaseExpressionSyntax or not.
      * \param node [in] The node whose kind is examined.
      * \return Returns true if the node is expression::BaseExpressionSyntax.
      */
      bool getIsBaseExpressionSyntax(const base::Base& node);

      /**
      * \brief Decides whether the node is expression::BinaryExpressionSyntax or not.
      * \param node [in] The node whose kind is examined.
      * \return Returns true if the node is expression::BinaryExpressionSyntax.
      */
      bool getIsBinaryExpressionSyntax(const base::Base& node);

      /**
      * \brief Decides whether the node is expression::CastExpressionSyntax or not.
      * \param node [in] The node whose kind is examined.
      * \return Returns true if the node is expression::CastExpressionSyntax.
      */
      bool getIsCastExpressionSyntax(const base::Base& node);

      /**
      * \brief Decides whether the node is expression::CheckedExpressionSyntax or not.
      * \param node [in] The node whose kind is examined.
      * \return Returns true if the node is expression::CheckedExpressionSyntax.
      */
      bool getIsCheckedExpressionSyntax(const base::Base& node);

      /**
      * \brief Decides whether the node is expression::ConditionalAccessExpressionSyntax or not.
      * \param node [in] The node whose kind is examined.
      * \return Returns true if the node is expression::ConditionalAccessExpressionSyntax.
      */
      bool getIsConditionalAccessExpressionSyntax(const base::Base& node);

      /**
      * \brief Decides whether the node is expression::ConditionalExpressionSyntax or not.
      * \param node [in] The node whose kind is examined.
      * \return Returns true if the node is expression::ConditionalExpressionSyntax.
      */
      bool getIsConditionalExpressionSyntax(const base::Base& node);

      /**
      * \brief Decides whether the node is expression::DefaultExpressionSyntax or not.
      * \param node [in] The node whose kind is examined.
      * \return Returns true if the node is expression::DefaultExpressionSyntax.
      */
      bool getIsDefaultExpressionSyntax(const base::Base& node);

      /**
      * \brief Decides whether the node is expression::ElementAccessExpressionSyntax or not.
      * \param node [in] The node whose kind is examined.
      * \return Returns true if the node is expression::ElementAccessExpressionSyntax.
      */
      bool getIsElementAccessExpressionSyntax(const base::Base& node);

      /**
      * \brief Decides whether the node is expression::ElementBindingExpressionSyntax or not.
      * \param node [in] The node whose kind is examined.
      * \return Returns true if the node is expression::ElementBindingExpressionSyntax.
      */
      bool getIsElementBindingExpressionSyntax(const base::Base& node);

      /**
      * \brief Decides whether the node is expression::ExpressionSyntax or not.
      * \param node [in] The node whose kind is examined.
      * \return Returns true if the node is expression::ExpressionSyntax.
      */
      bool getIsExpressionSyntax(const base::Base& node);

      /**
      * \brief Decides whether the node is expression::GenericNameSyntax or not.
      * \param node [in] The node whose kind is examined.
      * \return Returns true if the node is expression::GenericNameSyntax.
      */
      bool getIsGenericNameSyntax(const base::Base& node);

      /**
      * \brief Decides whether the node is expression::IdentifierNameSyntax or not.
      * \param node [in] The node whose kind is examined.
      * \return Returns true if the node is expression::IdentifierNameSyntax.
      */
      bool getIsIdentifierNameSyntax(const base::Base& node);

      /**
      * \brief Decides whether the node is expression::ImplicitArrayCreationExpressionSyntax or not.
      * \param node [in] The node whose kind is examined.
      * \return Returns true if the node is expression::ImplicitArrayCreationExpressionSyntax.
      */
      bool getIsImplicitArrayCreationExpressionSyntax(const base::Base& node);

      /**
      * \brief Decides whether the node is expression::ImplicitElementAccessSyntax or not.
      * \param node [in] The node whose kind is examined.
      * \return Returns true if the node is expression::ImplicitElementAccessSyntax.
      */
      bool getIsImplicitElementAccessSyntax(const base::Base& node);

      /**
      * \brief Decides whether the node is expression::InitializerExpressionSyntax or not.
      * \param node [in] The node whose kind is examined.
      * \return Returns true if the node is expression::InitializerExpressionSyntax.
      */
      bool getIsInitializerExpressionSyntax(const base::Base& node);

      /**
      * \brief Decides whether the node is expression::InstanceExpressionSyntax or not.
      * \param node [in] The node whose kind is examined.
      * \return Returns true if the node is expression::InstanceExpressionSyntax.
      */
      bool getIsInstanceExpressionSyntax(const base::Base& node);

      /**
      * \brief Decides whether the node is expression::InterpolatedStringExpressionSyntax or not.
      * \param node [in] The node whose kind is examined.
      * \return Returns true if the node is expression::InterpolatedStringExpressionSyntax.
      */
      bool getIsInterpolatedStringExpressionSyntax(const base::Base& node);

      /**
      * \brief Decides whether the node is expression::InvocationExpressionSyntax or not.
      * \param node [in] The node whose kind is examined.
      * \return Returns true if the node is expression::InvocationExpressionSyntax.
      */
      bool getIsInvocationExpressionSyntax(const base::Base& node);

      /**
      * \brief Decides whether the node is expression::LambdaExpressionSyntax or not.
      * \param node [in] The node whose kind is examined.
      * \return Returns true if the node is expression::LambdaExpressionSyntax.
      */
      bool getIsLambdaExpressionSyntax(const base::Base& node);

      /**
      * \brief Decides whether the node is expression::LiteralExpressionSyntax or not.
      * \param node [in] The node whose kind is examined.
      * \return Returns true if the node is expression::LiteralExpressionSyntax.
      */
      bool getIsLiteralExpressionSyntax(const base::Base& node);

      /**
      * \brief Decides whether the node is expression::MakeRefExpressionSyntax or not.
      * \param node [in] The node whose kind is examined.
      * \return Returns true if the node is expression::MakeRefExpressionSyntax.
      */
      bool getIsMakeRefExpressionSyntax(const base::Base& node);

      /**
      * \brief Decides whether the node is expression::MemberAccessExpressionSyntax or not.
      * \param node [in] The node whose kind is examined.
      * \return Returns true if the node is expression::MemberAccessExpressionSyntax.
      */
      bool getIsMemberAccessExpressionSyntax(const base::Base& node);

      /**
      * \brief Decides whether the node is expression::MemberBindingExpressionSyntax or not.
      * \param node [in] The node whose kind is examined.
      * \return Returns true if the node is expression::MemberBindingExpressionSyntax.
      */
      bool getIsMemberBindingExpressionSyntax(const base::Base& node);

      /**
      * \brief Decides whether the node is expression::NameSyntax or not.
      * \param node [in] The node whose kind is examined.
      * \return Returns true if the node is expression::NameSyntax.
      */
      bool getIsNameSyntax(const base::Base& node);

      /**
      * \brief Decides whether the node is expression::NullableTypeSyntax or not.
      * \param node [in] The node whose kind is examined.
      * \return Returns true if the node is expression::NullableTypeSyntax.
      */
      bool getIsNullableTypeSyntax(const base::Base& node);

      /**
      * \brief Decides whether the node is expression::ObjectCreationExpressionSyntax or not.
      * \param node [in] The node whose kind is examined.
      * \return Returns true if the node is expression::ObjectCreationExpressionSyntax.
      */
      bool getIsObjectCreationExpressionSyntax(const base::Base& node);

      /**
      * \brief Decides whether the node is expression::OmittedArraySizeExpressionSyntax or not.
      * \param node [in] The node whose kind is examined.
      * \return Returns true if the node is expression::OmittedArraySizeExpressionSyntax.
      */
      bool getIsOmittedArraySizeExpressionSyntax(const base::Base& node);

      /**
      * \brief Decides whether the node is expression::OmittedTypeArgumentSyntax or not.
      * \param node [in] The node whose kind is examined.
      * \return Returns true if the node is expression::OmittedTypeArgumentSyntax.
      */
      bool getIsOmittedTypeArgumentSyntax(const base::Base& node);

      /**
      * \brief Decides whether the node is expression::ParenthesizedExpressionSyntax or not.
      * \param node [in] The node whose kind is examined.
      * \return Returns true if the node is expression::ParenthesizedExpressionSyntax.
      */
      bool getIsParenthesizedExpressionSyntax(const base::Base& node);

      /**
      * \brief Decides whether the node is expression::ParenthesizedLambdaExpressionSyntax or not.
      * \param node [in] The node whose kind is examined.
      * \return Returns true if the node is expression::ParenthesizedLambdaExpressionSyntax.
      */
      bool getIsParenthesizedLambdaExpressionSyntax(const base::Base& node);

      /**
      * \brief Decides whether the node is expression::PointerTypeSyntax or not.
      * \param node [in] The node whose kind is examined.
      * \return Returns true if the node is expression::PointerTypeSyntax.
      */
      bool getIsPointerTypeSyntax(const base::Base& node);

      /**
      * \brief Decides whether the node is expression::PostfixUnaryExpressionSyntax or not.
      * \param node [in] The node whose kind is examined.
      * \return Returns true if the node is expression::PostfixUnaryExpressionSyntax.
      */
      bool getIsPostfixUnaryExpressionSyntax(const base::Base& node);

      /**
      * \brief Decides whether the node is expression::PredefinedTypeSyntax or not.
      * \param node [in] The node whose kind is examined.
      * \return Returns true if the node is expression::PredefinedTypeSyntax.
      */
      bool getIsPredefinedTypeSyntax(const base::Base& node);

      /**
      * \brief Decides whether the node is expression::PrefixUnaryExpressionSyntax or not.
      * \param node [in] The node whose kind is examined.
      * \return Returns true if the node is expression::PrefixUnaryExpressionSyntax.
      */
      bool getIsPrefixUnaryExpressionSyntax(const base::Base& node);

      /**
      * \brief Decides whether the node is expression::QualifiedNameSyntax or not.
      * \param node [in] The node whose kind is examined.
      * \return Returns true if the node is expression::QualifiedNameSyntax.
      */
      bool getIsQualifiedNameSyntax(const base::Base& node);

      /**
      * \brief Decides whether the node is expression::QueryExpressionSyntax or not.
      * \param node [in] The node whose kind is examined.
      * \return Returns true if the node is expression::QueryExpressionSyntax.
      */
      bool getIsQueryExpressionSyntax(const base::Base& node);

      /**
      * \brief Decides whether the node is expression::RefTypeExpressionSyntax or not.
      * \param node [in] The node whose kind is examined.
      * \return Returns true if the node is expression::RefTypeExpressionSyntax.
      */
      bool getIsRefTypeExpressionSyntax(const base::Base& node);

      /**
      * \brief Decides whether the node is expression::RefValueExpressionSyntax or not.
      * \param node [in] The node whose kind is examined.
      * \return Returns true if the node is expression::RefValueExpressionSyntax.
      */
      bool getIsRefValueExpressionSyntax(const base::Base& node);

      /**
      * \brief Decides whether the node is expression::SimpleLambdaExpressionSyntax or not.
      * \param node [in] The node whose kind is examined.
      * \return Returns true if the node is expression::SimpleLambdaExpressionSyntax.
      */
      bool getIsSimpleLambdaExpressionSyntax(const base::Base& node);

      /**
      * \brief Decides whether the node is expression::SimpleNameSyntax or not.
      * \param node [in] The node whose kind is examined.
      * \return Returns true if the node is expression::SimpleNameSyntax.
      */
      bool getIsSimpleNameSyntax(const base::Base& node);

      /**
      * \brief Decides whether the node is expression::SizeOfExpressionSyntax or not.
      * \param node [in] The node whose kind is examined.
      * \return Returns true if the node is expression::SizeOfExpressionSyntax.
      */
      bool getIsSizeOfExpressionSyntax(const base::Base& node);

      /**
      * \brief Decides whether the node is expression::StackAllocArrayCreationExpressionSyntax or not.
      * \param node [in] The node whose kind is examined.
      * \return Returns true if the node is expression::StackAllocArrayCreationExpressionSyntax.
      */
      bool getIsStackAllocArrayCreationExpressionSyntax(const base::Base& node);

      /**
      * \brief Decides whether the node is expression::ThisExpressionSyntax or not.
      * \param node [in] The node whose kind is examined.
      * \return Returns true if the node is expression::ThisExpressionSyntax.
      */
      bool getIsThisExpressionSyntax(const base::Base& node);

      /**
      * \brief Decides whether the node is expression::TypeOfExpressionSyntax or not.
      * \param node [in] The node whose kind is examined.
      * \return Returns true if the node is expression::TypeOfExpressionSyntax.
      */
      bool getIsTypeOfExpressionSyntax(const base::Base& node);

      /**
      * \brief Decides whether the node is expression::TypeSyntax or not.
      * \param node [in] The node whose kind is examined.
      * \return Returns true if the node is expression::TypeSyntax.
      */
      bool getIsTypeSyntax(const base::Base& node);

      /**
      * \brief Decides whether the node is statement::BlockSyntax or not.
      * \param node [in] The node whose kind is examined.
      * \return Returns true if the node is statement::BlockSyntax.
      */
      bool getIsBlockSyntax(const base::Base& node);

      /**
      * \brief Decides whether the node is statement::BreakStatementSyntax or not.
      * \param node [in] The node whose kind is examined.
      * \return Returns true if the node is statement::BreakStatementSyntax.
      */
      bool getIsBreakStatementSyntax(const base::Base& node);

      /**
      * \brief Decides whether the node is statement::CheckedStatementSyntax or not.
      * \param node [in] The node whose kind is examined.
      * \return Returns true if the node is statement::CheckedStatementSyntax.
      */
      bool getIsCheckedStatementSyntax(const base::Base& node);

      /**
      * \brief Decides whether the node is statement::ContinueStatementSyntax or not.
      * \param node [in] The node whose kind is examined.
      * \return Returns true if the node is statement::ContinueStatementSyntax.
      */
      bool getIsContinueStatementSyntax(const base::Base& node);

      /**
      * \brief Decides whether the node is statement::DoStatementSyntax or not.
      * \param node [in] The node whose kind is examined.
      * \return Returns true if the node is statement::DoStatementSyntax.
      */
      bool getIsDoStatementSyntax(const base::Base& node);

      /**
      * \brief Decides whether the node is statement::EmptyStatementSyntax or not.
      * \param node [in] The node whose kind is examined.
      * \return Returns true if the node is statement::EmptyStatementSyntax.
      */
      bool getIsEmptyStatementSyntax(const base::Base& node);

      /**
      * \brief Decides whether the node is statement::ExpressionStatementSyntax or not.
      * \param node [in] The node whose kind is examined.
      * \return Returns true if the node is statement::ExpressionStatementSyntax.
      */
      bool getIsExpressionStatementSyntax(const base::Base& node);

      /**
      * \brief Decides whether the node is statement::FixedStatementSyntax or not.
      * \param node [in] The node whose kind is examined.
      * \return Returns true if the node is statement::FixedStatementSyntax.
      */
      bool getIsFixedStatementSyntax(const base::Base& node);

      /**
      * \brief Decides whether the node is statement::ForEachStatementSyntax or not.
      * \param node [in] The node whose kind is examined.
      * \return Returns true if the node is statement::ForEachStatementSyntax.
      */
      bool getIsForEachStatementSyntax(const base::Base& node);

      /**
      * \brief Decides whether the node is statement::ForStatementSyntax or not.
      * \param node [in] The node whose kind is examined.
      * \return Returns true if the node is statement::ForStatementSyntax.
      */
      bool getIsForStatementSyntax(const base::Base& node);

      /**
      * \brief Decides whether the node is statement::GotoStatementSyntax or not.
      * \param node [in] The node whose kind is examined.
      * \return Returns true if the node is statement::GotoStatementSyntax.
      */
      bool getIsGotoStatementSyntax(const base::Base& node);

      /**
      * \brief Decides whether the node is statement::IfStatementSyntax or not.
      * \param node [in] The node whose kind is examined.
      * \return Returns true if the node is statement::IfStatementSyntax.
      */
      bool getIsIfStatementSyntax(const base::Base& node);

      /**
      * \brief Decides whether the node is statement::LabeledStatementSyntax or not.
      * \param node [in] The node whose kind is examined.
      * \return Returns true if the node is statement::LabeledStatementSyntax.
      */
      bool getIsLabeledStatementSyntax(const base::Base& node);

      /**
      * \brief Decides whether the node is statement::LocalDeclarationStatementSyntax or not.
      * \param node [in] The node whose kind is examined.
      * \return Returns true if the node is statement::LocalDeclarationStatementSyntax.
      */
      bool getIsLocalDeclarationStatementSyntax(const base::Base& node);

      /**
      * \brief Decides whether the node is statement::LockStatementSyntax or not.
      * \param node [in] The node whose kind is examined.
      * \return Returns true if the node is statement::LockStatementSyntax.
      */
      bool getIsLockStatementSyntax(const base::Base& node);

      /**
      * \brief Decides whether the node is statement::ReturnStatementSyntax or not.
      * \param node [in] The node whose kind is examined.
      * \return Returns true if the node is statement::ReturnStatementSyntax.
      */
      bool getIsReturnStatementSyntax(const base::Base& node);

      /**
      * \brief Decides whether the node is statement::StatementSyntax or not.
      * \param node [in] The node whose kind is examined.
      * \return Returns true if the node is statement::StatementSyntax.
      */
      bool getIsStatementSyntax(const base::Base& node);

      /**
      * \brief Decides whether the node is statement::SwitchStatementSyntax or not.
      * \param node [in] The node whose kind is examined.
      * \return Returns true if the node is statement::SwitchStatementSyntax.
      */
      bool getIsSwitchStatementSyntax(const base::Base& node);

      /**
      * \brief Decides whether the node is statement::ThrowStatementSyntax or not.
      * \param node [in] The node whose kind is examined.
      * \return Returns true if the node is statement::ThrowStatementSyntax.
      */
      bool getIsThrowStatementSyntax(const base::Base& node);

      /**
      * \brief Decides whether the node is statement::TryStatementSyntax or not.
      * \param node [in] The node whose kind is examined.
      * \return Returns true if the node is statement::TryStatementSyntax.
      */
      bool getIsTryStatementSyntax(const base::Base& node);

      /**
      * \brief Decides whether the node is statement::UnsafeStatementSyntax or not.
      * \param node [in] The node whose kind is examined.
      * \return Returns true if the node is statement::UnsafeStatementSyntax.
      */
      bool getIsUnsafeStatementSyntax(const base::Base& node);

      /**
      * \brief Decides whether the node is statement::UsingStatementSyntax or not.
      * \param node [in] The node whose kind is examined.
      * \return Returns true if the node is statement::UsingStatementSyntax.
      */
      bool getIsUsingStatementSyntax(const base::Base& node);

      /**
      * \brief Decides whether the node is statement::WhileStatementSyntax or not.
      * \param node [in] The node whose kind is examined.
      * \return Returns true if the node is statement::WhileStatementSyntax.
      */
      bool getIsWhileStatementSyntax(const base::Base& node);

      /**
      * \brief Decides whether the node is statement::YieldStatementSyntax or not.
      * \param node [in] The node whose kind is examined.
      * \return Returns true if the node is statement::YieldStatementSyntax.
      */
      bool getIsYieldStatementSyntax(const base::Base& node);

      /**
      * \brief Decides whether the node is structure::AccessorDeclarationSyntax or not.
      * \param node [in] The node whose kind is examined.
      * \return Returns true if the node is structure::AccessorDeclarationSyntax.
      */
      bool getIsAccessorDeclarationSyntax(const base::Base& node);

      /**
      * \brief Decides whether the node is structure::AccessorListSyntax or not.
      * \param node [in] The node whose kind is examined.
      * \return Returns true if the node is structure::AccessorListSyntax.
      */
      bool getIsAccessorListSyntax(const base::Base& node);

      /**
      * \brief Decides whether the node is structure::AnonymousObjectMemberDeclaratorSyntax or not.
      * \param node [in] The node whose kind is examined.
      * \return Returns true if the node is structure::AnonymousObjectMemberDeclaratorSyntax.
      */
      bool getIsAnonymousObjectMemberDeclaratorSyntax(const base::Base& node);

      /**
      * \brief Decides whether the node is structure::ArgumentListSyntax or not.
      * \param node [in] The node whose kind is examined.
      * \return Returns true if the node is structure::ArgumentListSyntax.
      */
      bool getIsArgumentListSyntax(const base::Base& node);

      /**
      * \brief Decides whether the node is structure::ArgumentSyntax or not.
      * \param node [in] The node whose kind is examined.
      * \return Returns true if the node is structure::ArgumentSyntax.
      */
      bool getIsArgumentSyntax(const base::Base& node);

      /**
      * \brief Decides whether the node is structure::ArrayRankSpecifierSyntax or not.
      * \param node [in] The node whose kind is examined.
      * \return Returns true if the node is structure::ArrayRankSpecifierSyntax.
      */
      bool getIsArrayRankSpecifierSyntax(const base::Base& node);

      /**
      * \brief Decides whether the node is structure::ArrowExpressionClauseSyntax or not.
      * \param node [in] The node whose kind is examined.
      * \return Returns true if the node is structure::ArrowExpressionClauseSyntax.
      */
      bool getIsArrowExpressionClauseSyntax(const base::Base& node);

      /**
      * \brief Decides whether the node is structure::AttributeArgumentListSyntax or not.
      * \param node [in] The node whose kind is examined.
      * \return Returns true if the node is structure::AttributeArgumentListSyntax.
      */
      bool getIsAttributeArgumentListSyntax(const base::Base& node);

      /**
      * \brief Decides whether the node is structure::AttributeArgumentSyntax or not.
      * \param node [in] The node whose kind is examined.
      * \return Returns true if the node is structure::AttributeArgumentSyntax.
      */
      bool getIsAttributeArgumentSyntax(const base::Base& node);

      /**
      * \brief Decides whether the node is structure::AttributeListSyntax or not.
      * \param node [in] The node whose kind is examined.
      * \return Returns true if the node is structure::AttributeListSyntax.
      */
      bool getIsAttributeListSyntax(const base::Base& node);

      /**
      * \brief Decides whether the node is structure::AttributeSyntax or not.
      * \param node [in] The node whose kind is examined.
      * \return Returns true if the node is structure::AttributeSyntax.
      */
      bool getIsAttributeSyntax(const base::Base& node);

      /**
      * \brief Decides whether the node is structure::AttributeTargetSpecifierSyntax or not.
      * \param node [in] The node whose kind is examined.
      * \return Returns true if the node is structure::AttributeTargetSpecifierSyntax.
      */
      bool getIsAttributeTargetSpecifierSyntax(const base::Base& node);

      /**
      * \brief Decides whether the node is structure::BaseArgumentListSyntax or not.
      * \param node [in] The node whose kind is examined.
      * \return Returns true if the node is structure::BaseArgumentListSyntax.
      */
      bool getIsBaseArgumentListSyntax(const base::Base& node);

      /**
      * \brief Decides whether the node is structure::BaseCrefParameterListSyntax or not.
      * \param node [in] The node whose kind is examined.
      * \return Returns true if the node is structure::BaseCrefParameterListSyntax.
      */
      bool getIsBaseCrefParameterListSyntax(const base::Base& node);

      /**
      * \brief Decides whether the node is structure::BaseFieldDeclarationSyntax or not.
      * \param node [in] The node whose kind is examined.
      * \return Returns true if the node is structure::BaseFieldDeclarationSyntax.
      */
      bool getIsBaseFieldDeclarationSyntax(const base::Base& node);

      /**
      * \brief Decides whether the node is structure::BaseListSyntax or not.
      * \param node [in] The node whose kind is examined.
      * \return Returns true if the node is structure::BaseListSyntax.
      */
      bool getIsBaseListSyntax(const base::Base& node);

      /**
      * \brief Decides whether the node is structure::BaseMethodDeclarationSyntax or not.
      * \param node [in] The node whose kind is examined.
      * \return Returns true if the node is structure::BaseMethodDeclarationSyntax.
      */
      bool getIsBaseMethodDeclarationSyntax(const base::Base& node);

      /**
      * \brief Decides whether the node is structure::BaseParameterListSyntax or not.
      * \param node [in] The node whose kind is examined.
      * \return Returns true if the node is structure::BaseParameterListSyntax.
      */
      bool getIsBaseParameterListSyntax(const base::Base& node);

      /**
      * \brief Decides whether the node is structure::BasePropertyDeclarationSyntax or not.
      * \param node [in] The node whose kind is examined.
      * \return Returns true if the node is structure::BasePropertyDeclarationSyntax.
      */
      bool getIsBasePropertyDeclarationSyntax(const base::Base& node);

      /**
      * \brief Decides whether the node is structure::BaseTypeDeclarationSyntax or not.
      * \param node [in] The node whose kind is examined.
      * \return Returns true if the node is structure::BaseTypeDeclarationSyntax.
      */
      bool getIsBaseTypeDeclarationSyntax(const base::Base& node);

      /**
      * \brief Decides whether the node is structure::BaseTypeSyntax or not.
      * \param node [in] The node whose kind is examined.
      * \return Returns true if the node is structure::BaseTypeSyntax.
      */
      bool getIsBaseTypeSyntax(const base::Base& node);

      /**
      * \brief Decides whether the node is structure::BracketedArgumentListSyntax or not.
      * \param node [in] The node whose kind is examined.
      * \return Returns true if the node is structure::BracketedArgumentListSyntax.
      */
      bool getIsBracketedArgumentListSyntax(const base::Base& node);

      /**
      * \brief Decides whether the node is structure::BracketedParameterListSyntax or not.
      * \param node [in] The node whose kind is examined.
      * \return Returns true if the node is structure::BracketedParameterListSyntax.
      */
      bool getIsBracketedParameterListSyntax(const base::Base& node);

      /**
      * \brief Decides whether the node is structure::CaseSwitchLabelSyntax or not.
      * \param node [in] The node whose kind is examined.
      * \return Returns true if the node is structure::CaseSwitchLabelSyntax.
      */
      bool getIsCaseSwitchLabelSyntax(const base::Base& node);

      /**
      * \brief Decides whether the node is structure::CatchClauseSyntax or not.
      * \param node [in] The node whose kind is examined.
      * \return Returns true if the node is structure::CatchClauseSyntax.
      */
      bool getIsCatchClauseSyntax(const base::Base& node);

      /**
      * \brief Decides whether the node is structure::CatchDeclarationSyntax or not.
      * \param node [in] The node whose kind is examined.
      * \return Returns true if the node is structure::CatchDeclarationSyntax.
      */
      bool getIsCatchDeclarationSyntax(const base::Base& node);

      /**
      * \brief Decides whether the node is structure::CatchFilterClauseSyntax or not.
      * \param node [in] The node whose kind is examined.
      * \return Returns true if the node is structure::CatchFilterClauseSyntax.
      */
      bool getIsCatchFilterClauseSyntax(const base::Base& node);

      /**
      * \brief Decides whether the node is structure::ClassDeclarationSyntax or not.
      * \param node [in] The node whose kind is examined.
      * \return Returns true if the node is structure::ClassDeclarationSyntax.
      */
      bool getIsClassDeclarationSyntax(const base::Base& node);

      /**
      * \brief Decides whether the node is structure::ClassOrStructConstraintSyntax or not.
      * \param node [in] The node whose kind is examined.
      * \return Returns true if the node is structure::ClassOrStructConstraintSyntax.
      */
      bool getIsClassOrStructConstraintSyntax(const base::Base& node);

      /**
      * \brief Decides whether the node is structure::CompilationUnitSyntax or not.
      * \param node [in] The node whose kind is examined.
      * \return Returns true if the node is structure::CompilationUnitSyntax.
      */
      bool getIsCompilationUnitSyntax(const base::Base& node);

      /**
      * \brief Decides whether the node is structure::ConstructorConstraintSyntax or not.
      * \param node [in] The node whose kind is examined.
      * \return Returns true if the node is structure::ConstructorConstraintSyntax.
      */
      bool getIsConstructorConstraintSyntax(const base::Base& node);

      /**
      * \brief Decides whether the node is structure::ConstructorDeclarationSyntax or not.
      * \param node [in] The node whose kind is examined.
      * \return Returns true if the node is structure::ConstructorDeclarationSyntax.
      */
      bool getIsConstructorDeclarationSyntax(const base::Base& node);

      /**
      * \brief Decides whether the node is structure::ConstructorInitializerSyntax or not.
      * \param node [in] The node whose kind is examined.
      * \return Returns true if the node is structure::ConstructorInitializerSyntax.
      */
      bool getIsConstructorInitializerSyntax(const base::Base& node);

      /**
      * \brief Decides whether the node is structure::ConversionOperatorDeclarationSyntax or not.
      * \param node [in] The node whose kind is examined.
      * \return Returns true if the node is structure::ConversionOperatorDeclarationSyntax.
      */
      bool getIsConversionOperatorDeclarationSyntax(const base::Base& node);

      /**
      * \brief Decides whether the node is structure::ConversionOperatorMemberCrefSyntax or not.
      * \param node [in] The node whose kind is examined.
      * \return Returns true if the node is structure::ConversionOperatorMemberCrefSyntax.
      */
      bool getIsConversionOperatorMemberCrefSyntax(const base::Base& node);

      /**
      * \brief Decides whether the node is structure::CrefBracketedParameterListSyntax or not.
      * \param node [in] The node whose kind is examined.
      * \return Returns true if the node is structure::CrefBracketedParameterListSyntax.
      */
      bool getIsCrefBracketedParameterListSyntax(const base::Base& node);

      /**
      * \brief Decides whether the node is structure::CrefParameterListSyntax or not.
      * \param node [in] The node whose kind is examined.
      * \return Returns true if the node is structure::CrefParameterListSyntax.
      */
      bool getIsCrefParameterListSyntax(const base::Base& node);

      /**
      * \brief Decides whether the node is structure::CrefParameterSyntax or not.
      * \param node [in] The node whose kind is examined.
      * \return Returns true if the node is structure::CrefParameterSyntax.
      */
      bool getIsCrefParameterSyntax(const base::Base& node);

      /**
      * \brief Decides whether the node is structure::CrefSyntax or not.
      * \param node [in] The node whose kind is examined.
      * \return Returns true if the node is structure::CrefSyntax.
      */
      bool getIsCrefSyntax(const base::Base& node);

      /**
      * \brief Decides whether the node is structure::DefaultSwitchLabelSyntax or not.
      * \param node [in] The node whose kind is examined.
      * \return Returns true if the node is structure::DefaultSwitchLabelSyntax.
      */
      bool getIsDefaultSwitchLabelSyntax(const base::Base& node);

      /**
      * \brief Decides whether the node is structure::DelegateDeclarationSyntax or not.
      * \param node [in] The node whose kind is examined.
      * \return Returns true if the node is structure::DelegateDeclarationSyntax.
      */
      bool getIsDelegateDeclarationSyntax(const base::Base& node);

      /**
      * \brief Decides whether the node is structure::DestructorDeclarationSyntax or not.
      * \param node [in] The node whose kind is examined.
      * \return Returns true if the node is structure::DestructorDeclarationSyntax.
      */
      bool getIsDestructorDeclarationSyntax(const base::Base& node);

      /**
      * \brief Decides whether the node is structure::ElseClauseSyntax or not.
      * \param node [in] The node whose kind is examined.
      * \return Returns true if the node is structure::ElseClauseSyntax.
      */
      bool getIsElseClauseSyntax(const base::Base& node);

      /**
      * \brief Decides whether the node is structure::EnumDeclarationSyntax or not.
      * \param node [in] The node whose kind is examined.
      * \return Returns true if the node is structure::EnumDeclarationSyntax.
      */
      bool getIsEnumDeclarationSyntax(const base::Base& node);

      /**
      * \brief Decides whether the node is structure::EnumMemberDeclarationSyntax or not.
      * \param node [in] The node whose kind is examined.
      * \return Returns true if the node is structure::EnumMemberDeclarationSyntax.
      */
      bool getIsEnumMemberDeclarationSyntax(const base::Base& node);

      /**
      * \brief Decides whether the node is structure::EqualsValueClauseSyntax or not.
      * \param node [in] The node whose kind is examined.
      * \return Returns true if the node is structure::EqualsValueClauseSyntax.
      */
      bool getIsEqualsValueClauseSyntax(const base::Base& node);

      /**
      * \brief Decides whether the node is structure::EventDeclarationSyntax or not.
      * \param node [in] The node whose kind is examined.
      * \return Returns true if the node is structure::EventDeclarationSyntax.
      */
      bool getIsEventDeclarationSyntax(const base::Base& node);

      /**
      * \brief Decides whether the node is structure::EventFieldDeclarationSyntax or not.
      * \param node [in] The node whose kind is examined.
      * \return Returns true if the node is structure::EventFieldDeclarationSyntax.
      */
      bool getIsEventFieldDeclarationSyntax(const base::Base& node);

      /**
      * \brief Decides whether the node is structure::ExplicitInterfaceSpecifierSyntax or not.
      * \param node [in] The node whose kind is examined.
      * \return Returns true if the node is structure::ExplicitInterfaceSpecifierSyntax.
      */
      bool getIsExplicitInterfaceSpecifierSyntax(const base::Base& node);

      /**
      * \brief Decides whether the node is structure::ExternAliasDirectiveSyntax or not.
      * \param node [in] The node whose kind is examined.
      * \return Returns true if the node is structure::ExternAliasDirectiveSyntax.
      */
      bool getIsExternAliasDirectiveSyntax(const base::Base& node);

      /**
      * \brief Decides whether the node is structure::FieldDeclarationSyntax or not.
      * \param node [in] The node whose kind is examined.
      * \return Returns true if the node is structure::FieldDeclarationSyntax.
      */
      bool getIsFieldDeclarationSyntax(const base::Base& node);

      /**
      * \brief Decides whether the node is structure::FinallyClauseSyntax or not.
      * \param node [in] The node whose kind is examined.
      * \return Returns true if the node is structure::FinallyClauseSyntax.
      */
      bool getIsFinallyClauseSyntax(const base::Base& node);

      /**
      * \brief Decides whether the node is structure::FromClauseSyntax or not.
      * \param node [in] The node whose kind is examined.
      * \return Returns true if the node is structure::FromClauseSyntax.
      */
      bool getIsFromClauseSyntax(const base::Base& node);

      /**
      * \brief Decides whether the node is structure::GlobalStatementSyntax or not.
      * \param node [in] The node whose kind is examined.
      * \return Returns true if the node is structure::GlobalStatementSyntax.
      */
      bool getIsGlobalStatementSyntax(const base::Base& node);

      /**
      * \brief Decides whether the node is structure::GroupClauseSyntax or not.
      * \param node [in] The node whose kind is examined.
      * \return Returns true if the node is structure::GroupClauseSyntax.
      */
      bool getIsGroupClauseSyntax(const base::Base& node);

      /**
      * \brief Decides whether the node is structure::IncompleteMemberSyntax or not.
      * \param node [in] The node whose kind is examined.
      * \return Returns true if the node is structure::IncompleteMemberSyntax.
      */
      bool getIsIncompleteMemberSyntax(const base::Base& node);

      /**
      * \brief Decides whether the node is structure::IndexerDeclarationSyntax or not.
      * \param node [in] The node whose kind is examined.
      * \return Returns true if the node is structure::IndexerDeclarationSyntax.
      */
      bool getIsIndexerDeclarationSyntax(const base::Base& node);

      /**
      * \brief Decides whether the node is structure::IndexerMemberCrefSyntax or not.
      * \param node [in] The node whose kind is examined.
      * \return Returns true if the node is structure::IndexerMemberCrefSyntax.
      */
      bool getIsIndexerMemberCrefSyntax(const base::Base& node);

      /**
      * \brief Decides whether the node is structure::InterfaceDeclarationSyntax or not.
      * \param node [in] The node whose kind is examined.
      * \return Returns true if the node is structure::InterfaceDeclarationSyntax.
      */
      bool getIsInterfaceDeclarationSyntax(const base::Base& node);

      /**
      * \brief Decides whether the node is structure::InterpolatedStringContentSyntax or not.
      * \param node [in] The node whose kind is examined.
      * \return Returns true if the node is structure::InterpolatedStringContentSyntax.
      */
      bool getIsInterpolatedStringContentSyntax(const base::Base& node);

      /**
      * \brief Decides whether the node is structure::InterpolatedStringTextSyntax or not.
      * \param node [in] The node whose kind is examined.
      * \return Returns true if the node is structure::InterpolatedStringTextSyntax.
      */
      bool getIsInterpolatedStringTextSyntax(const base::Base& node);

      /**
      * \brief Decides whether the node is structure::InterpolationAlignmentClauseSyntax or not.
      * \param node [in] The node whose kind is examined.
      * \return Returns true if the node is structure::InterpolationAlignmentClauseSyntax.
      */
      bool getIsInterpolationAlignmentClauseSyntax(const base::Base& node);

      /**
      * \brief Decides whether the node is structure::InterpolationFormatClauseSyntax or not.
      * \param node [in] The node whose kind is examined.
      * \return Returns true if the node is structure::InterpolationFormatClauseSyntax.
      */
      bool getIsInterpolationFormatClauseSyntax(const base::Base& node);

      /**
      * \brief Decides whether the node is structure::InterpolationSyntax or not.
      * \param node [in] The node whose kind is examined.
      * \return Returns true if the node is structure::InterpolationSyntax.
      */
      bool getIsInterpolationSyntax(const base::Base& node);

      /**
      * \brief Decides whether the node is structure::JoinClauseSyntax or not.
      * \param node [in] The node whose kind is examined.
      * \return Returns true if the node is structure::JoinClauseSyntax.
      */
      bool getIsJoinClauseSyntax(const base::Base& node);

      /**
      * \brief Decides whether the node is structure::JoinIntoClauseSyntax or not.
      * \param node [in] The node whose kind is examined.
      * \return Returns true if the node is structure::JoinIntoClauseSyntax.
      */
      bool getIsJoinIntoClauseSyntax(const base::Base& node);

      /**
      * \brief Decides whether the node is structure::LetClauseSyntax or not.
      * \param node [in] The node whose kind is examined.
      * \return Returns true if the node is structure::LetClauseSyntax.
      */
      bool getIsLetClauseSyntax(const base::Base& node);

      /**
      * \brief Decides whether the node is structure::MemberCrefSyntax or not.
      * \param node [in] The node whose kind is examined.
      * \return Returns true if the node is structure::MemberCrefSyntax.
      */
      bool getIsMemberCrefSyntax(const base::Base& node);

      /**
      * \brief Decides whether the node is structure::MemberDeclarationSyntax or not.
      * \param node [in] The node whose kind is examined.
      * \return Returns true if the node is structure::MemberDeclarationSyntax.
      */
      bool getIsMemberDeclarationSyntax(const base::Base& node);

      /**
      * \brief Decides whether the node is structure::MethodDeclarationSyntax or not.
      * \param node [in] The node whose kind is examined.
      * \return Returns true if the node is structure::MethodDeclarationSyntax.
      */
      bool getIsMethodDeclarationSyntax(const base::Base& node);

      /**
      * \brief Decides whether the node is structure::NameColonSyntax or not.
      * \param node [in] The node whose kind is examined.
      * \return Returns true if the node is structure::NameColonSyntax.
      */
      bool getIsNameColonSyntax(const base::Base& node);

      /**
      * \brief Decides whether the node is structure::NameEqualsSyntax or not.
      * \param node [in] The node whose kind is examined.
      * \return Returns true if the node is structure::NameEqualsSyntax.
      */
      bool getIsNameEqualsSyntax(const base::Base& node);

      /**
      * \brief Decides whether the node is structure::NameMemberCrefSyntax or not.
      * \param node [in] The node whose kind is examined.
      * \return Returns true if the node is structure::NameMemberCrefSyntax.
      */
      bool getIsNameMemberCrefSyntax(const base::Base& node);

      /**
      * \brief Decides whether the node is structure::NamespaceDeclarationSyntax or not.
      * \param node [in] The node whose kind is examined.
      * \return Returns true if the node is structure::NamespaceDeclarationSyntax.
      */
      bool getIsNamespaceDeclarationSyntax(const base::Base& node);

      /**
      * \brief Decides whether the node is structure::OperatorDeclarationSyntax or not.
      * \param node [in] The node whose kind is examined.
      * \return Returns true if the node is structure::OperatorDeclarationSyntax.
      */
      bool getIsOperatorDeclarationSyntax(const base::Base& node);

      /**
      * \brief Decides whether the node is structure::OperatorMemberCrefSyntax or not.
      * \param node [in] The node whose kind is examined.
      * \return Returns true if the node is structure::OperatorMemberCrefSyntax.
      */
      bool getIsOperatorMemberCrefSyntax(const base::Base& node);

      /**
      * \brief Decides whether the node is structure::OrderByClauseSyntax or not.
      * \param node [in] The node whose kind is examined.
      * \return Returns true if the node is structure::OrderByClauseSyntax.
      */
      bool getIsOrderByClauseSyntax(const base::Base& node);

      /**
      * \brief Decides whether the node is structure::OrderingSyntax or not.
      * \param node [in] The node whose kind is examined.
      * \return Returns true if the node is structure::OrderingSyntax.
      */
      bool getIsOrderingSyntax(const base::Base& node);

      /**
      * \brief Decides whether the node is structure::ParameterListSyntax or not.
      * \param node [in] The node whose kind is examined.
      * \return Returns true if the node is structure::ParameterListSyntax.
      */
      bool getIsParameterListSyntax(const base::Base& node);

      /**
      * \brief Decides whether the node is structure::ParameterSyntax or not.
      * \param node [in] The node whose kind is examined.
      * \return Returns true if the node is structure::ParameterSyntax.
      */
      bool getIsParameterSyntax(const base::Base& node);

      /**
      * \brief Decides whether the node is structure::PropertyDeclarationSyntax or not.
      * \param node [in] The node whose kind is examined.
      * \return Returns true if the node is structure::PropertyDeclarationSyntax.
      */
      bool getIsPropertyDeclarationSyntax(const base::Base& node);

      /**
      * \brief Decides whether the node is structure::QualifiedCrefSyntax or not.
      * \param node [in] The node whose kind is examined.
      * \return Returns true if the node is structure::QualifiedCrefSyntax.
      */
      bool getIsQualifiedCrefSyntax(const base::Base& node);

      /**
      * \brief Decides whether the node is structure::QueryBodySyntax or not.
      * \param node [in] The node whose kind is examined.
      * \return Returns true if the node is structure::QueryBodySyntax.
      */
      bool getIsQueryBodySyntax(const base::Base& node);

      /**
      * \brief Decides whether the node is structure::QueryClauseSyntax or not.
      * \param node [in] The node whose kind is examined.
      * \return Returns true if the node is structure::QueryClauseSyntax.
      */
      bool getIsQueryClauseSyntax(const base::Base& node);

      /**
      * \brief Decides whether the node is structure::QueryContinuationSyntax or not.
      * \param node [in] The node whose kind is examined.
      * \return Returns true if the node is structure::QueryContinuationSyntax.
      */
      bool getIsQueryContinuationSyntax(const base::Base& node);

      /**
      * \brief Decides whether the node is structure::SelectClauseSyntax or not.
      * \param node [in] The node whose kind is examined.
      * \return Returns true if the node is structure::SelectClauseSyntax.
      */
      bool getIsSelectClauseSyntax(const base::Base& node);

      /**
      * \brief Decides whether the node is structure::SelectOrGroupClauseSyntax or not.
      * \param node [in] The node whose kind is examined.
      * \return Returns true if the node is structure::SelectOrGroupClauseSyntax.
      */
      bool getIsSelectOrGroupClauseSyntax(const base::Base& node);

      /**
      * \brief Decides whether the node is structure::SimpleBaseTypeSyntax or not.
      * \param node [in] The node whose kind is examined.
      * \return Returns true if the node is structure::SimpleBaseTypeSyntax.
      */
      bool getIsSimpleBaseTypeSyntax(const base::Base& node);

      /**
      * \brief Decides whether the node is structure::StructDeclarationSyntax or not.
      * \param node [in] The node whose kind is examined.
      * \return Returns true if the node is structure::StructDeclarationSyntax.
      */
      bool getIsStructDeclarationSyntax(const base::Base& node);

      /**
      * \brief Decides whether the node is structure::SwitchLabelSyntax or not.
      * \param node [in] The node whose kind is examined.
      * \return Returns true if the node is structure::SwitchLabelSyntax.
      */
      bool getIsSwitchLabelSyntax(const base::Base& node);

      /**
      * \brief Decides whether the node is structure::SwitchSectionSyntax or not.
      * \param node [in] The node whose kind is examined.
      * \return Returns true if the node is structure::SwitchSectionSyntax.
      */
      bool getIsSwitchSectionSyntax(const base::Base& node);

      /**
      * \brief Decides whether the node is structure::SyntaxToken or not.
      * \param node [in] The node whose kind is examined.
      * \return Returns true if the node is structure::SyntaxToken.
      */
      bool getIsSyntaxToken(const base::Base& node);

      /**
      * \brief Decides whether the node is structure::TypeArgumentListSyntax or not.
      * \param node [in] The node whose kind is examined.
      * \return Returns true if the node is structure::TypeArgumentListSyntax.
      */
      bool getIsTypeArgumentListSyntax(const base::Base& node);

      /**
      * \brief Decides whether the node is structure::TypeConstraintSyntax or not.
      * \param node [in] The node whose kind is examined.
      * \return Returns true if the node is structure::TypeConstraintSyntax.
      */
      bool getIsTypeConstraintSyntax(const base::Base& node);

      /**
      * \brief Decides whether the node is structure::TypeCrefSyntax or not.
      * \param node [in] The node whose kind is examined.
      * \return Returns true if the node is structure::TypeCrefSyntax.
      */
      bool getIsTypeCrefSyntax(const base::Base& node);

      /**
      * \brief Decides whether the node is structure::TypeDeclarationSyntax or not.
      * \param node [in] The node whose kind is examined.
      * \return Returns true if the node is structure::TypeDeclarationSyntax.
      */
      bool getIsTypeDeclarationSyntax(const base::Base& node);

      /**
      * \brief Decides whether the node is structure::TypeParameterConstraintClauseSyntax or not.
      * \param node [in] The node whose kind is examined.
      * \return Returns true if the node is structure::TypeParameterConstraintClauseSyntax.
      */
      bool getIsTypeParameterConstraintClauseSyntax(const base::Base& node);

      /**
      * \brief Decides whether the node is structure::TypeParameterConstraintSyntax or not.
      * \param node [in] The node whose kind is examined.
      * \return Returns true if the node is structure::TypeParameterConstraintSyntax.
      */
      bool getIsTypeParameterConstraintSyntax(const base::Base& node);

      /**
      * \brief Decides whether the node is structure::TypeParameterListSyntax or not.
      * \param node [in] The node whose kind is examined.
      * \return Returns true if the node is structure::TypeParameterListSyntax.
      */
      bool getIsTypeParameterListSyntax(const base::Base& node);

      /**
      * \brief Decides whether the node is structure::TypeParameterSyntax or not.
      * \param node [in] The node whose kind is examined.
      * \return Returns true if the node is structure::TypeParameterSyntax.
      */
      bool getIsTypeParameterSyntax(const base::Base& node);

      /**
      * \brief Decides whether the node is structure::UsingDirectiveSyntax or not.
      * \param node [in] The node whose kind is examined.
      * \return Returns true if the node is structure::UsingDirectiveSyntax.
      */
      bool getIsUsingDirectiveSyntax(const base::Base& node);

      /**
      * \brief Decides whether the node is structure::VariableDeclarationSyntax or not.
      * \param node [in] The node whose kind is examined.
      * \return Returns true if the node is structure::VariableDeclarationSyntax.
      */
      bool getIsVariableDeclarationSyntax(const base::Base& node);

      /**
      * \brief Decides whether the node is structure::VariableDeclaratorSyntax or not.
      * \param node [in] The node whose kind is examined.
      * \return Returns true if the node is structure::VariableDeclaratorSyntax.
      */
      bool getIsVariableDeclaratorSyntax(const base::Base& node);

      /**
      * \brief Decides whether the node is structure::WhereClauseSyntax or not.
      * \param node [in] The node whose kind is examined.
      * \return Returns true if the node is structure::WhereClauseSyntax.
      */
      bool getIsWhereClauseSyntax(const base::Base& node);

      /**
      * \brief Decides whether the node is structure::XmlAttributeSyntax or not.
      * \param node [in] The node whose kind is examined.
      * \return Returns true if the node is structure::XmlAttributeSyntax.
      */
      bool getIsXmlAttributeSyntax(const base::Base& node);

      /**
      * \brief Decides whether the node is structure::XmlCDataSectionSyntax or not.
      * \param node [in] The node whose kind is examined.
      * \return Returns true if the node is structure::XmlCDataSectionSyntax.
      */
      bool getIsXmlCDataSectionSyntax(const base::Base& node);

      /**
      * \brief Decides whether the node is structure::XmlCommentSyntax or not.
      * \param node [in] The node whose kind is examined.
      * \return Returns true if the node is structure::XmlCommentSyntax.
      */
      bool getIsXmlCommentSyntax(const base::Base& node);

      /**
      * \brief Decides whether the node is structure::XmlCrefAttributeSyntax or not.
      * \param node [in] The node whose kind is examined.
      * \return Returns true if the node is structure::XmlCrefAttributeSyntax.
      */
      bool getIsXmlCrefAttributeSyntax(const base::Base& node);

      /**
      * \brief Decides whether the node is structure::XmlElementEndTagSyntax or not.
      * \param node [in] The node whose kind is examined.
      * \return Returns true if the node is structure::XmlElementEndTagSyntax.
      */
      bool getIsXmlElementEndTagSyntax(const base::Base& node);

      /**
      * \brief Decides whether the node is structure::XmlElementStartTagSyntax or not.
      * \param node [in] The node whose kind is examined.
      * \return Returns true if the node is structure::XmlElementStartTagSyntax.
      */
      bool getIsXmlElementStartTagSyntax(const base::Base& node);

      /**
      * \brief Decides whether the node is structure::XmlElementSyntax or not.
      * \param node [in] The node whose kind is examined.
      * \return Returns true if the node is structure::XmlElementSyntax.
      */
      bool getIsXmlElementSyntax(const base::Base& node);

      /**
      * \brief Decides whether the node is structure::XmlEmptyElementSyntax or not.
      * \param node [in] The node whose kind is examined.
      * \return Returns true if the node is structure::XmlEmptyElementSyntax.
      */
      bool getIsXmlEmptyElementSyntax(const base::Base& node);

      /**
      * \brief Decides whether the node is structure::XmlNameAttributeSyntax or not.
      * \param node [in] The node whose kind is examined.
      * \return Returns true if the node is structure::XmlNameAttributeSyntax.
      */
      bool getIsXmlNameAttributeSyntax(const base::Base& node);

      /**
      * \brief Decides whether the node is structure::XmlNameSyntax or not.
      * \param node [in] The node whose kind is examined.
      * \return Returns true if the node is structure::XmlNameSyntax.
      */
      bool getIsXmlNameSyntax(const base::Base& node);

      /**
      * \brief Decides whether the node is structure::XmlNodeSyntax or not.
      * \param node [in] The node whose kind is examined.
      * \return Returns true if the node is structure::XmlNodeSyntax.
      */
      bool getIsXmlNodeSyntax(const base::Base& node);

      /**
      * \brief Decides whether the node is structure::XmlPrefixSyntax or not.
      * \param node [in] The node whose kind is examined.
      * \return Returns true if the node is structure::XmlPrefixSyntax.
      */
      bool getIsXmlPrefixSyntax(const base::Base& node);

      /**
      * \brief Decides whether the node is structure::XmlProcessingInstructionSyntax or not.
      * \param node [in] The node whose kind is examined.
      * \return Returns true if the node is structure::XmlProcessingInstructionSyntax.
      */
      bool getIsXmlProcessingInstructionSyntax(const base::Base& node);

      /**
      * \brief Decides whether the node is structure::XmlTextAttributeSyntax or not.
      * \param node [in] The node whose kind is examined.
      * \return Returns true if the node is structure::XmlTextAttributeSyntax.
      */
      bool getIsXmlTextAttributeSyntax(const base::Base& node);

      /**
      * \brief Decides whether the node is structure::XmlTextSyntax or not.
      * \param node [in] The node whose kind is examined.
      * \return Returns true if the node is structure::XmlTextSyntax.
      */
      bool getIsXmlTextSyntax(const base::Base& node);

      /**
      * \brief Decides whether the node is base::Base or not.
      * \param node [in] The node whose kind is examined.
      * \return Returns true if the node is base::Base.
      */
      bool getIsNamed(const base::Base& node);
      /**
      * \brief Decides whether the node is base::Base or not.
      * \param node [in] The node whose kind is examined.
      * \return Returns std::string& if the node have getidentifier().
      */
      const std::string& getName(const base::Base& node);
      /**
      * \brief Decides whether the 'base' is one of the base kinds (transitive) of 'what'.
      * \param what [in] The examined node kind.
      * \param base [in] The base node kind.
      * \return Returns true if 'base' is a base kind of 'what'.
      */
      bool getIsBaseClassKind(NodeKind what, NodeKind base);

      /**
      * \brief Decides whether the node is composite or not.
      * \param node [in] The node which is being examined.
      * \return Returns true if the node is composite.
      */
      bool getIsComposite(const base::Base& node);

      /**
      * \brief Decides whether the node is composite or not.
      * \param node [in] The node which is being examined.
      * \return Returns true if the node is not composite.
      */
      bool getIsNotComposite(const base::Base& node);

      /**
      * \brief Gives back the string representation of the NodeId.
      * \param nodeId [in] The NodeId.
      * \return The string representation of the nodeId given in the parameter.
      */
      const std::string toString(NodeId nodeId);

      /**
      * \brief Gives back the string representation of the NodeKind kind.
      * \param kind            [in] The NodeKind.
      * \throw CsharpException If the kind is not "valid" CsharpException is thrown.
      * \return The string representation of the kind given in the parameter.
      */
      const std::string toString(NodeKind kind);

      /**
      * \brief Gives back the string representation of the EdgeKind kind.
      * \param kind            [in] The EdgeKind.
      * \throw CsharpException If the kind is not "valid" CsharpException is thrown.
      * \return The string representation of the kind given in the parameter.
      */
      const std::string toString(EdgeKind kind);

      /**
      * \brief Returns true if the node exists and is not filtered out.
      * \param id [in] The examined node ID.
      * \return True if the node exists and is not filtered out.
      */
      bool getIsValid(NodeId id);

      /**
      * \brief Minimum of same type node similarity.
      */
      extern double SimilarityMinimum;

      /**
      * \brief Returns the minimum similarity value of same type nodes.
      * \return Minimum of same type node similarity.
      */
      double getSimilarityMinimum();

      /**
      * \brief Sets the minimum similarity value of same type nodes.
      * \param value [in] Minimum of same type node similarity.
      */
      void setSimilarityMinimum(double value);

      /**
      * \brief Minimum similarity for string type attributes.
      */
      extern double SimilarityMinForStrings;

      /**
      * \brief Returns the minimum similarity value for string type attributes.
      * \return Minimum similarity for string type attributes.
      */
      double getSimilarityMinForStrings();

      /**
      * \brief Sets the minimum similarity value for string type attributes.
      * \param value [in] Minimum similarity for string type attributes.
      */
      void setSimilarityMinForStrings(double value);

      /**
      * \brief Minimum similarity for AP spec edges.
      */
      extern double SimilarityMinForEdges;

      /**
      * \brief Returns the minimum similarity value for AP spec edges.
      * \return Minimum similarity for AP spec edges.
      */
      double getSimilarityMinForEdges();

      /**
      * \brief Sets the minimum similarity value for AP spec edges.
      * \param value [in] Minimum similarity for AP spec edges.
      */
      void setSimilarityMinForEdges(double value);


      base::Base* getScopeParent(const Factory* factory, NodeId node, bool (*getIs) (const base::Base&));
      
  } // Common


}}}
#endif

