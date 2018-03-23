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

#ifndef _CSHARP_VISITOR_H_
#define _CSHARP_VISITOR_H_

#include "csharp/inc/csharp.h"

/**
* \file Visitor.h
* \brief Contains declaration of Visitor class.
*/

namespace columbus { namespace csharp { namespace asg {
  /**
  * \brief Visitor for each non-abstract nodes and all edges of the graph.
  */
  class Visitor {
    public:
      /**
      * \brief Constructor for Visitor.
      */
      Visitor();

      /**
      * \brief Destructor.
      */
      virtual ~Visitor();

      /**
      * \brief Gives back the the actual position's depth in the ASG.
      * \return The depth of the actual position.
      */
      unsigned getDepth() const;

      /**
      * \brief Increasing the depth by one in the ASG.
      */
      void incDepth();

      /**
      * \brief Decreasing the depth by one in the ASG.
      */
      void decDepth();

      /**
      * \brief This function is calling before the beginning of visiting process.
      */
      virtual void beginVisit();

      /**
      * \brief This function is calling when the visiting process has finished.
      */
      virtual void finishVisit();

      /**
      * \brief Visitor which is called at the beginning of the expression::AliasQualifiedNameSyntax node visiting.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const expression::AliasQualifiedNameSyntax& node , bool callVirtualBase = true);

      /**
      * \brief Visitor which is called at the end of the expression::AliasQualifiedNameSyntax node visiting.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const expression::AliasQualifiedNameSyntax& node , bool callVirtualBase = true);

      /**
      * \brief Visitor which is called at the beginning of the expression::AnonymousMethodExpressionSyntax node visiting.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const expression::AnonymousMethodExpressionSyntax& node , bool callVirtualBase = true);

      /**
      * \brief Visitor which is called at the end of the expression::AnonymousMethodExpressionSyntax node visiting.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const expression::AnonymousMethodExpressionSyntax& node , bool callVirtualBase = true);

      /**
      * \brief Visitor which is called at the beginning of the expression::AnonymousObjectCreationExpressionSyntax node visiting.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const expression::AnonymousObjectCreationExpressionSyntax& node , bool callVirtualBase = true);

      /**
      * \brief Visitor which is called at the end of the expression::AnonymousObjectCreationExpressionSyntax node visiting.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const expression::AnonymousObjectCreationExpressionSyntax& node , bool callVirtualBase = true);

      /**
      * \brief Visitor which is called at the beginning of the expression::ArrayCreationExpressionSyntax node visiting.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const expression::ArrayCreationExpressionSyntax& node , bool callVirtualBase = true);

      /**
      * \brief Visitor which is called at the end of the expression::ArrayCreationExpressionSyntax node visiting.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const expression::ArrayCreationExpressionSyntax& node , bool callVirtualBase = true);

      /**
      * \brief Visitor which is called at the beginning of the expression::ArrayTypeSyntax node visiting.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const expression::ArrayTypeSyntax& node , bool callVirtualBase = true);

      /**
      * \brief Visitor which is called at the end of the expression::ArrayTypeSyntax node visiting.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const expression::ArrayTypeSyntax& node , bool callVirtualBase = true);

      /**
      * \brief Visitor which is called at the beginning of the expression::AssignmentExpressionSyntax node visiting.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const expression::AssignmentExpressionSyntax& node , bool callVirtualBase = true);

      /**
      * \brief Visitor which is called at the end of the expression::AssignmentExpressionSyntax node visiting.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const expression::AssignmentExpressionSyntax& node , bool callVirtualBase = true);

      /**
      * \brief Visitor which is called at the beginning of the expression::AwaitExpressionSyntax node visiting.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const expression::AwaitExpressionSyntax& node , bool callVirtualBase = true);

      /**
      * \brief Visitor which is called at the end of the expression::AwaitExpressionSyntax node visiting.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const expression::AwaitExpressionSyntax& node , bool callVirtualBase = true);

      /**
      * \brief Visitor which is called at the beginning of the expression::BaseExpressionSyntax node visiting.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const expression::BaseExpressionSyntax& node , bool callVirtualBase = true);

      /**
      * \brief Visitor which is called at the end of the expression::BaseExpressionSyntax node visiting.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const expression::BaseExpressionSyntax& node , bool callVirtualBase = true);

      /**
      * \brief Visitor which is called at the beginning of the expression::BinaryExpressionSyntax node visiting.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const expression::BinaryExpressionSyntax& node , bool callVirtualBase = true);

      /**
      * \brief Visitor which is called at the end of the expression::BinaryExpressionSyntax node visiting.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const expression::BinaryExpressionSyntax& node , bool callVirtualBase = true);

      /**
      * \brief Visitor which is called at the beginning of the expression::CastExpressionSyntax node visiting.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const expression::CastExpressionSyntax& node , bool callVirtualBase = true);

      /**
      * \brief Visitor which is called at the end of the expression::CastExpressionSyntax node visiting.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const expression::CastExpressionSyntax& node , bool callVirtualBase = true);

      /**
      * \brief Visitor which is called at the beginning of the expression::CheckedExpressionSyntax node visiting.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const expression::CheckedExpressionSyntax& node , bool callVirtualBase = true);

      /**
      * \brief Visitor which is called at the end of the expression::CheckedExpressionSyntax node visiting.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const expression::CheckedExpressionSyntax& node , bool callVirtualBase = true);

      /**
      * \brief Visitor which is called at the beginning of the expression::ConditionalAccessExpressionSyntax node visiting.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const expression::ConditionalAccessExpressionSyntax& node , bool callVirtualBase = true);

      /**
      * \brief Visitor which is called at the end of the expression::ConditionalAccessExpressionSyntax node visiting.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const expression::ConditionalAccessExpressionSyntax& node , bool callVirtualBase = true);

      /**
      * \brief Visitor which is called at the beginning of the expression::ConditionalExpressionSyntax node visiting.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const expression::ConditionalExpressionSyntax& node , bool callVirtualBase = true);

      /**
      * \brief Visitor which is called at the end of the expression::ConditionalExpressionSyntax node visiting.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const expression::ConditionalExpressionSyntax& node , bool callVirtualBase = true);

      /**
      * \brief Visitor which is called at the beginning of the expression::DefaultExpressionSyntax node visiting.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const expression::DefaultExpressionSyntax& node , bool callVirtualBase = true);

      /**
      * \brief Visitor which is called at the end of the expression::DefaultExpressionSyntax node visiting.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const expression::DefaultExpressionSyntax& node , bool callVirtualBase = true);

      /**
      * \brief Visitor which is called at the beginning of the expression::ElementAccessExpressionSyntax node visiting.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const expression::ElementAccessExpressionSyntax& node , bool callVirtualBase = true);

      /**
      * \brief Visitor which is called at the end of the expression::ElementAccessExpressionSyntax node visiting.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const expression::ElementAccessExpressionSyntax& node , bool callVirtualBase = true);

      /**
      * \brief Visitor which is called at the beginning of the expression::ElementBindingExpressionSyntax node visiting.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const expression::ElementBindingExpressionSyntax& node , bool callVirtualBase = true);

      /**
      * \brief Visitor which is called at the end of the expression::ElementBindingExpressionSyntax node visiting.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const expression::ElementBindingExpressionSyntax& node , bool callVirtualBase = true);

      /**
      * \brief Visitor which is called at the beginning of the expression::GenericNameSyntax node visiting.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const expression::GenericNameSyntax& node , bool callVirtualBase = true);

      /**
      * \brief Visitor which is called at the end of the expression::GenericNameSyntax node visiting.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const expression::GenericNameSyntax& node , bool callVirtualBase = true);

      /**
      * \brief Visitor which is called at the beginning of the expression::IdentifierNameSyntax node visiting.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const expression::IdentifierNameSyntax& node , bool callVirtualBase = true);

      /**
      * \brief Visitor which is called at the end of the expression::IdentifierNameSyntax node visiting.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const expression::IdentifierNameSyntax& node , bool callVirtualBase = true);

      /**
      * \brief Visitor which is called at the beginning of the expression::ImplicitArrayCreationExpressionSyntax node visiting.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const expression::ImplicitArrayCreationExpressionSyntax& node , bool callVirtualBase = true);

      /**
      * \brief Visitor which is called at the end of the expression::ImplicitArrayCreationExpressionSyntax node visiting.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const expression::ImplicitArrayCreationExpressionSyntax& node , bool callVirtualBase = true);

      /**
      * \brief Visitor which is called at the beginning of the expression::ImplicitElementAccessSyntax node visiting.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const expression::ImplicitElementAccessSyntax& node , bool callVirtualBase = true);

      /**
      * \brief Visitor which is called at the end of the expression::ImplicitElementAccessSyntax node visiting.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const expression::ImplicitElementAccessSyntax& node , bool callVirtualBase = true);

      /**
      * \brief Visitor which is called at the beginning of the expression::InitializerExpressionSyntax node visiting.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const expression::InitializerExpressionSyntax& node , bool callVirtualBase = true);

      /**
      * \brief Visitor which is called at the end of the expression::InitializerExpressionSyntax node visiting.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const expression::InitializerExpressionSyntax& node , bool callVirtualBase = true);

      /**
      * \brief Visitor which is called at the beginning of the expression::InterpolatedStringExpressionSyntax node visiting.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const expression::InterpolatedStringExpressionSyntax& node , bool callVirtualBase = true);

      /**
      * \brief Visitor which is called at the end of the expression::InterpolatedStringExpressionSyntax node visiting.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const expression::InterpolatedStringExpressionSyntax& node , bool callVirtualBase = true);

      /**
      * \brief Visitor which is called at the beginning of the expression::InvocationExpressionSyntax node visiting.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const expression::InvocationExpressionSyntax& node , bool callVirtualBase = true);

      /**
      * \brief Visitor which is called at the end of the expression::InvocationExpressionSyntax node visiting.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const expression::InvocationExpressionSyntax& node , bool callVirtualBase = true);

      /**
      * \brief Visitor which is called at the beginning of the expression::LiteralExpressionSyntax node visiting.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const expression::LiteralExpressionSyntax& node , bool callVirtualBase = true);

      /**
      * \brief Visitor which is called at the end of the expression::LiteralExpressionSyntax node visiting.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const expression::LiteralExpressionSyntax& node , bool callVirtualBase = true);

      /**
      * \brief Visitor which is called at the beginning of the expression::MakeRefExpressionSyntax node visiting.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const expression::MakeRefExpressionSyntax& node , bool callVirtualBase = true);

      /**
      * \brief Visitor which is called at the end of the expression::MakeRefExpressionSyntax node visiting.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const expression::MakeRefExpressionSyntax& node , bool callVirtualBase = true);

      /**
      * \brief Visitor which is called at the beginning of the expression::MemberAccessExpressionSyntax node visiting.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const expression::MemberAccessExpressionSyntax& node , bool callVirtualBase = true);

      /**
      * \brief Visitor which is called at the end of the expression::MemberAccessExpressionSyntax node visiting.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const expression::MemberAccessExpressionSyntax& node , bool callVirtualBase = true);

      /**
      * \brief Visitor which is called at the beginning of the expression::MemberBindingExpressionSyntax node visiting.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const expression::MemberBindingExpressionSyntax& node , bool callVirtualBase = true);

      /**
      * \brief Visitor which is called at the end of the expression::MemberBindingExpressionSyntax node visiting.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const expression::MemberBindingExpressionSyntax& node , bool callVirtualBase = true);

      /**
      * \brief Visitor which is called at the beginning of the expression::NullableTypeSyntax node visiting.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const expression::NullableTypeSyntax& node , bool callVirtualBase = true);

      /**
      * \brief Visitor which is called at the end of the expression::NullableTypeSyntax node visiting.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const expression::NullableTypeSyntax& node , bool callVirtualBase = true);

      /**
      * \brief Visitor which is called at the beginning of the expression::ObjectCreationExpressionSyntax node visiting.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const expression::ObjectCreationExpressionSyntax& node , bool callVirtualBase = true);

      /**
      * \brief Visitor which is called at the end of the expression::ObjectCreationExpressionSyntax node visiting.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const expression::ObjectCreationExpressionSyntax& node , bool callVirtualBase = true);

      /**
      * \brief Visitor which is called at the beginning of the expression::OmittedArraySizeExpressionSyntax node visiting.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const expression::OmittedArraySizeExpressionSyntax& node , bool callVirtualBase = true);

      /**
      * \brief Visitor which is called at the end of the expression::OmittedArraySizeExpressionSyntax node visiting.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const expression::OmittedArraySizeExpressionSyntax& node , bool callVirtualBase = true);

      /**
      * \brief Visitor which is called at the beginning of the expression::OmittedTypeArgumentSyntax node visiting.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const expression::OmittedTypeArgumentSyntax& node , bool callVirtualBase = true);

      /**
      * \brief Visitor which is called at the end of the expression::OmittedTypeArgumentSyntax node visiting.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const expression::OmittedTypeArgumentSyntax& node , bool callVirtualBase = true);

      /**
      * \brief Visitor which is called at the beginning of the expression::ParenthesizedExpressionSyntax node visiting.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const expression::ParenthesizedExpressionSyntax& node , bool callVirtualBase = true);

      /**
      * \brief Visitor which is called at the end of the expression::ParenthesizedExpressionSyntax node visiting.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const expression::ParenthesizedExpressionSyntax& node , bool callVirtualBase = true);

      /**
      * \brief Visitor which is called at the beginning of the expression::ParenthesizedLambdaExpressionSyntax node visiting.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const expression::ParenthesizedLambdaExpressionSyntax& node , bool callVirtualBase = true);

      /**
      * \brief Visitor which is called at the end of the expression::ParenthesizedLambdaExpressionSyntax node visiting.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const expression::ParenthesizedLambdaExpressionSyntax& node , bool callVirtualBase = true);

      /**
      * \brief Visitor which is called at the beginning of the expression::PointerTypeSyntax node visiting.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const expression::PointerTypeSyntax& node , bool callVirtualBase = true);

      /**
      * \brief Visitor which is called at the end of the expression::PointerTypeSyntax node visiting.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const expression::PointerTypeSyntax& node , bool callVirtualBase = true);

      /**
      * \brief Visitor which is called at the beginning of the expression::PostfixUnaryExpressionSyntax node visiting.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const expression::PostfixUnaryExpressionSyntax& node , bool callVirtualBase = true);

      /**
      * \brief Visitor which is called at the end of the expression::PostfixUnaryExpressionSyntax node visiting.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const expression::PostfixUnaryExpressionSyntax& node , bool callVirtualBase = true);

      /**
      * \brief Visitor which is called at the beginning of the expression::PredefinedTypeSyntax node visiting.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const expression::PredefinedTypeSyntax& node , bool callVirtualBase = true);

      /**
      * \brief Visitor which is called at the end of the expression::PredefinedTypeSyntax node visiting.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const expression::PredefinedTypeSyntax& node , bool callVirtualBase = true);

      /**
      * \brief Visitor which is called at the beginning of the expression::PrefixUnaryExpressionSyntax node visiting.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const expression::PrefixUnaryExpressionSyntax& node , bool callVirtualBase = true);

      /**
      * \brief Visitor which is called at the end of the expression::PrefixUnaryExpressionSyntax node visiting.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const expression::PrefixUnaryExpressionSyntax& node , bool callVirtualBase = true);

      /**
      * \brief Visitor which is called at the beginning of the expression::QualifiedNameSyntax node visiting.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const expression::QualifiedNameSyntax& node , bool callVirtualBase = true);

      /**
      * \brief Visitor which is called at the end of the expression::QualifiedNameSyntax node visiting.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const expression::QualifiedNameSyntax& node , bool callVirtualBase = true);

      /**
      * \brief Visitor which is called at the beginning of the expression::QueryExpressionSyntax node visiting.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const expression::QueryExpressionSyntax& node , bool callVirtualBase = true);

      /**
      * \brief Visitor which is called at the end of the expression::QueryExpressionSyntax node visiting.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const expression::QueryExpressionSyntax& node , bool callVirtualBase = true);

      /**
      * \brief Visitor which is called at the beginning of the expression::RefTypeExpressionSyntax node visiting.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const expression::RefTypeExpressionSyntax& node , bool callVirtualBase = true);

      /**
      * \brief Visitor which is called at the end of the expression::RefTypeExpressionSyntax node visiting.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const expression::RefTypeExpressionSyntax& node , bool callVirtualBase = true);

      /**
      * \brief Visitor which is called at the beginning of the expression::RefValueExpressionSyntax node visiting.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const expression::RefValueExpressionSyntax& node , bool callVirtualBase = true);

      /**
      * \brief Visitor which is called at the end of the expression::RefValueExpressionSyntax node visiting.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const expression::RefValueExpressionSyntax& node , bool callVirtualBase = true);

      /**
      * \brief Visitor which is called at the beginning of the expression::SimpleLambdaExpressionSyntax node visiting.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const expression::SimpleLambdaExpressionSyntax& node , bool callVirtualBase = true);

      /**
      * \brief Visitor which is called at the end of the expression::SimpleLambdaExpressionSyntax node visiting.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const expression::SimpleLambdaExpressionSyntax& node , bool callVirtualBase = true);

      /**
      * \brief Visitor which is called at the beginning of the expression::SizeOfExpressionSyntax node visiting.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const expression::SizeOfExpressionSyntax& node , bool callVirtualBase = true);

      /**
      * \brief Visitor which is called at the end of the expression::SizeOfExpressionSyntax node visiting.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const expression::SizeOfExpressionSyntax& node , bool callVirtualBase = true);

      /**
      * \brief Visitor which is called at the beginning of the expression::StackAllocArrayCreationExpressionSyntax node visiting.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const expression::StackAllocArrayCreationExpressionSyntax& node , bool callVirtualBase = true);

      /**
      * \brief Visitor which is called at the end of the expression::StackAllocArrayCreationExpressionSyntax node visiting.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const expression::StackAllocArrayCreationExpressionSyntax& node , bool callVirtualBase = true);

      /**
      * \brief Visitor which is called at the beginning of the expression::ThisExpressionSyntax node visiting.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const expression::ThisExpressionSyntax& node , bool callVirtualBase = true);

      /**
      * \brief Visitor which is called at the end of the expression::ThisExpressionSyntax node visiting.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const expression::ThisExpressionSyntax& node , bool callVirtualBase = true);

      /**
      * \brief Visitor which is called at the beginning of the expression::TypeOfExpressionSyntax node visiting.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const expression::TypeOfExpressionSyntax& node , bool callVirtualBase = true);

      /**
      * \brief Visitor which is called at the end of the expression::TypeOfExpressionSyntax node visiting.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const expression::TypeOfExpressionSyntax& node , bool callVirtualBase = true);

      /**
      * \brief Visitor which is called at the beginning of the statement::BlockSyntax node visiting.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const statement::BlockSyntax& node , bool callVirtualBase = true);

      /**
      * \brief Visitor which is called at the end of the statement::BlockSyntax node visiting.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const statement::BlockSyntax& node , bool callVirtualBase = true);

      /**
      * \brief Visitor which is called at the beginning of the statement::BreakStatementSyntax node visiting.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const statement::BreakStatementSyntax& node , bool callVirtualBase = true);

      /**
      * \brief Visitor which is called at the end of the statement::BreakStatementSyntax node visiting.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const statement::BreakStatementSyntax& node , bool callVirtualBase = true);

      /**
      * \brief Visitor which is called at the beginning of the statement::CheckedStatementSyntax node visiting.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const statement::CheckedStatementSyntax& node , bool callVirtualBase = true);

      /**
      * \brief Visitor which is called at the end of the statement::CheckedStatementSyntax node visiting.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const statement::CheckedStatementSyntax& node , bool callVirtualBase = true);

      /**
      * \brief Visitor which is called at the beginning of the statement::ContinueStatementSyntax node visiting.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const statement::ContinueStatementSyntax& node , bool callVirtualBase = true);

      /**
      * \brief Visitor which is called at the end of the statement::ContinueStatementSyntax node visiting.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const statement::ContinueStatementSyntax& node , bool callVirtualBase = true);

      /**
      * \brief Visitor which is called at the beginning of the statement::DoStatementSyntax node visiting.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const statement::DoStatementSyntax& node , bool callVirtualBase = true);

      /**
      * \brief Visitor which is called at the end of the statement::DoStatementSyntax node visiting.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const statement::DoStatementSyntax& node , bool callVirtualBase = true);

      /**
      * \brief Visitor which is called at the beginning of the statement::EmptyStatementSyntax node visiting.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const statement::EmptyStatementSyntax& node , bool callVirtualBase = true);

      /**
      * \brief Visitor which is called at the end of the statement::EmptyStatementSyntax node visiting.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const statement::EmptyStatementSyntax& node , bool callVirtualBase = true);

      /**
      * \brief Visitor which is called at the beginning of the statement::ExpressionStatementSyntax node visiting.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const statement::ExpressionStatementSyntax& node , bool callVirtualBase = true);

      /**
      * \brief Visitor which is called at the end of the statement::ExpressionStatementSyntax node visiting.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const statement::ExpressionStatementSyntax& node , bool callVirtualBase = true);

      /**
      * \brief Visitor which is called at the beginning of the statement::FixedStatementSyntax node visiting.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const statement::FixedStatementSyntax& node , bool callVirtualBase = true);

      /**
      * \brief Visitor which is called at the end of the statement::FixedStatementSyntax node visiting.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const statement::FixedStatementSyntax& node , bool callVirtualBase = true);

      /**
      * \brief Visitor which is called at the beginning of the statement::ForEachStatementSyntax node visiting.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const statement::ForEachStatementSyntax& node , bool callVirtualBase = true);

      /**
      * \brief Visitor which is called at the end of the statement::ForEachStatementSyntax node visiting.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const statement::ForEachStatementSyntax& node , bool callVirtualBase = true);

      /**
      * \brief Visitor which is called at the beginning of the statement::ForStatementSyntax node visiting.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const statement::ForStatementSyntax& node , bool callVirtualBase = true);

      /**
      * \brief Visitor which is called at the end of the statement::ForStatementSyntax node visiting.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const statement::ForStatementSyntax& node , bool callVirtualBase = true);

      /**
      * \brief Visitor which is called at the beginning of the statement::GotoStatementSyntax node visiting.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const statement::GotoStatementSyntax& node , bool callVirtualBase = true);

      /**
      * \brief Visitor which is called at the end of the statement::GotoStatementSyntax node visiting.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const statement::GotoStatementSyntax& node , bool callVirtualBase = true);

      /**
      * \brief Visitor which is called at the beginning of the statement::IfStatementSyntax node visiting.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const statement::IfStatementSyntax& node , bool callVirtualBase = true);

      /**
      * \brief Visitor which is called at the end of the statement::IfStatementSyntax node visiting.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const statement::IfStatementSyntax& node , bool callVirtualBase = true);

      /**
      * \brief Visitor which is called at the beginning of the statement::LabeledStatementSyntax node visiting.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const statement::LabeledStatementSyntax& node , bool callVirtualBase = true);

      /**
      * \brief Visitor which is called at the end of the statement::LabeledStatementSyntax node visiting.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const statement::LabeledStatementSyntax& node , bool callVirtualBase = true);

      /**
      * \brief Visitor which is called at the beginning of the statement::LocalDeclarationStatementSyntax node visiting.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const statement::LocalDeclarationStatementSyntax& node , bool callVirtualBase = true);

      /**
      * \brief Visitor which is called at the end of the statement::LocalDeclarationStatementSyntax node visiting.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const statement::LocalDeclarationStatementSyntax& node , bool callVirtualBase = true);

      /**
      * \brief Visitor which is called at the beginning of the statement::LockStatementSyntax node visiting.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const statement::LockStatementSyntax& node , bool callVirtualBase = true);

      /**
      * \brief Visitor which is called at the end of the statement::LockStatementSyntax node visiting.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const statement::LockStatementSyntax& node , bool callVirtualBase = true);

      /**
      * \brief Visitor which is called at the beginning of the statement::ReturnStatementSyntax node visiting.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const statement::ReturnStatementSyntax& node , bool callVirtualBase = true);

      /**
      * \brief Visitor which is called at the end of the statement::ReturnStatementSyntax node visiting.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const statement::ReturnStatementSyntax& node , bool callVirtualBase = true);

      /**
      * \brief Visitor which is called at the beginning of the statement::SwitchStatementSyntax node visiting.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const statement::SwitchStatementSyntax& node , bool callVirtualBase = true);

      /**
      * \brief Visitor which is called at the end of the statement::SwitchStatementSyntax node visiting.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const statement::SwitchStatementSyntax& node , bool callVirtualBase = true);

      /**
      * \brief Visitor which is called at the beginning of the statement::ThrowStatementSyntax node visiting.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const statement::ThrowStatementSyntax& node , bool callVirtualBase = true);

      /**
      * \brief Visitor which is called at the end of the statement::ThrowStatementSyntax node visiting.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const statement::ThrowStatementSyntax& node , bool callVirtualBase = true);

      /**
      * \brief Visitor which is called at the beginning of the statement::TryStatementSyntax node visiting.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const statement::TryStatementSyntax& node , bool callVirtualBase = true);

      /**
      * \brief Visitor which is called at the end of the statement::TryStatementSyntax node visiting.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const statement::TryStatementSyntax& node , bool callVirtualBase = true);

      /**
      * \brief Visitor which is called at the beginning of the statement::UnsafeStatementSyntax node visiting.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const statement::UnsafeStatementSyntax& node , bool callVirtualBase = true);

      /**
      * \brief Visitor which is called at the end of the statement::UnsafeStatementSyntax node visiting.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const statement::UnsafeStatementSyntax& node , bool callVirtualBase = true);

      /**
      * \brief Visitor which is called at the beginning of the statement::UsingStatementSyntax node visiting.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const statement::UsingStatementSyntax& node , bool callVirtualBase = true);

      /**
      * \brief Visitor which is called at the end of the statement::UsingStatementSyntax node visiting.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const statement::UsingStatementSyntax& node , bool callVirtualBase = true);

      /**
      * \brief Visitor which is called at the beginning of the statement::WhileStatementSyntax node visiting.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const statement::WhileStatementSyntax& node , bool callVirtualBase = true);

      /**
      * \brief Visitor which is called at the end of the statement::WhileStatementSyntax node visiting.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const statement::WhileStatementSyntax& node , bool callVirtualBase = true);

      /**
      * \brief Visitor which is called at the beginning of the statement::YieldStatementSyntax node visiting.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const statement::YieldStatementSyntax& node , bool callVirtualBase = true);

      /**
      * \brief Visitor which is called at the end of the statement::YieldStatementSyntax node visiting.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const statement::YieldStatementSyntax& node , bool callVirtualBase = true);

      /**
      * \brief Visitor which is called at the beginning of the structure::AccessorDeclarationSyntax node visiting.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const structure::AccessorDeclarationSyntax& node , bool callVirtualBase = true);

      /**
      * \brief Visitor which is called at the end of the structure::AccessorDeclarationSyntax node visiting.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const structure::AccessorDeclarationSyntax& node , bool callVirtualBase = true);

      /**
      * \brief Visitor which is called at the beginning of the structure::AccessorListSyntax node visiting.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const structure::AccessorListSyntax& node , bool callVirtualBase = true);

      /**
      * \brief Visitor which is called at the end of the structure::AccessorListSyntax node visiting.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const structure::AccessorListSyntax& node , bool callVirtualBase = true);

      /**
      * \brief Visitor which is called at the beginning of the structure::AnonymousObjectMemberDeclaratorSyntax node visiting.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const structure::AnonymousObjectMemberDeclaratorSyntax& node , bool callVirtualBase = true);

      /**
      * \brief Visitor which is called at the end of the structure::AnonymousObjectMemberDeclaratorSyntax node visiting.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const structure::AnonymousObjectMemberDeclaratorSyntax& node , bool callVirtualBase = true);

      /**
      * \brief Visitor which is called at the beginning of the structure::ArgumentListSyntax node visiting.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const structure::ArgumentListSyntax& node , bool callVirtualBase = true);

      /**
      * \brief Visitor which is called at the end of the structure::ArgumentListSyntax node visiting.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const structure::ArgumentListSyntax& node , bool callVirtualBase = true);

      /**
      * \brief Visitor which is called at the beginning of the structure::ArgumentSyntax node visiting.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const structure::ArgumentSyntax& node , bool callVirtualBase = true);

      /**
      * \brief Visitor which is called at the end of the structure::ArgumentSyntax node visiting.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const structure::ArgumentSyntax& node , bool callVirtualBase = true);

      /**
      * \brief Visitor which is called at the beginning of the structure::ArrayRankSpecifierSyntax node visiting.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const structure::ArrayRankSpecifierSyntax& node , bool callVirtualBase = true);

      /**
      * \brief Visitor which is called at the end of the structure::ArrayRankSpecifierSyntax node visiting.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const structure::ArrayRankSpecifierSyntax& node , bool callVirtualBase = true);

      /**
      * \brief Visitor which is called at the beginning of the structure::ArrowExpressionClauseSyntax node visiting.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const structure::ArrowExpressionClauseSyntax& node , bool callVirtualBase = true);

      /**
      * \brief Visitor which is called at the end of the structure::ArrowExpressionClauseSyntax node visiting.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const structure::ArrowExpressionClauseSyntax& node , bool callVirtualBase = true);

      /**
      * \brief Visitor which is called at the beginning of the structure::AttributeArgumentListSyntax node visiting.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const structure::AttributeArgumentListSyntax& node , bool callVirtualBase = true);

      /**
      * \brief Visitor which is called at the end of the structure::AttributeArgumentListSyntax node visiting.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const structure::AttributeArgumentListSyntax& node , bool callVirtualBase = true);

      /**
      * \brief Visitor which is called at the beginning of the structure::AttributeArgumentSyntax node visiting.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const structure::AttributeArgumentSyntax& node , bool callVirtualBase = true);

      /**
      * \brief Visitor which is called at the end of the structure::AttributeArgumentSyntax node visiting.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const structure::AttributeArgumentSyntax& node , bool callVirtualBase = true);

      /**
      * \brief Visitor which is called at the beginning of the structure::AttributeListSyntax node visiting.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const structure::AttributeListSyntax& node , bool callVirtualBase = true);

      /**
      * \brief Visitor which is called at the end of the structure::AttributeListSyntax node visiting.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const structure::AttributeListSyntax& node , bool callVirtualBase = true);

      /**
      * \brief Visitor which is called at the beginning of the structure::AttributeSyntax node visiting.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const structure::AttributeSyntax& node , bool callVirtualBase = true);

      /**
      * \brief Visitor which is called at the end of the structure::AttributeSyntax node visiting.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const structure::AttributeSyntax& node , bool callVirtualBase = true);

      /**
      * \brief Visitor which is called at the beginning of the structure::AttributeTargetSpecifierSyntax node visiting.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const structure::AttributeTargetSpecifierSyntax& node , bool callVirtualBase = true);

      /**
      * \brief Visitor which is called at the end of the structure::AttributeTargetSpecifierSyntax node visiting.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const structure::AttributeTargetSpecifierSyntax& node , bool callVirtualBase = true);

      /**
      * \brief Visitor which is called at the beginning of the structure::BaseListSyntax node visiting.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const structure::BaseListSyntax& node , bool callVirtualBase = true);

      /**
      * \brief Visitor which is called at the end of the structure::BaseListSyntax node visiting.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const structure::BaseListSyntax& node , bool callVirtualBase = true);

      /**
      * \brief Visitor which is called at the beginning of the structure::BracketedArgumentListSyntax node visiting.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const structure::BracketedArgumentListSyntax& node , bool callVirtualBase = true);

      /**
      * \brief Visitor which is called at the end of the structure::BracketedArgumentListSyntax node visiting.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const structure::BracketedArgumentListSyntax& node , bool callVirtualBase = true);

      /**
      * \brief Visitor which is called at the beginning of the structure::BracketedParameterListSyntax node visiting.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const structure::BracketedParameterListSyntax& node , bool callVirtualBase = true);

      /**
      * \brief Visitor which is called at the end of the structure::BracketedParameterListSyntax node visiting.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const structure::BracketedParameterListSyntax& node , bool callVirtualBase = true);

      /**
      * \brief Visitor which is called at the beginning of the structure::CaseSwitchLabelSyntax node visiting.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const structure::CaseSwitchLabelSyntax& node , bool callVirtualBase = true);

      /**
      * \brief Visitor which is called at the end of the structure::CaseSwitchLabelSyntax node visiting.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const structure::CaseSwitchLabelSyntax& node , bool callVirtualBase = true);

      /**
      * \brief Visitor which is called at the beginning of the structure::CatchClauseSyntax node visiting.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const structure::CatchClauseSyntax& node , bool callVirtualBase = true);

      /**
      * \brief Visitor which is called at the end of the structure::CatchClauseSyntax node visiting.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const structure::CatchClauseSyntax& node , bool callVirtualBase = true);

      /**
      * \brief Visitor which is called at the beginning of the structure::CatchDeclarationSyntax node visiting.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const structure::CatchDeclarationSyntax& node , bool callVirtualBase = true);

      /**
      * \brief Visitor which is called at the end of the structure::CatchDeclarationSyntax node visiting.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const structure::CatchDeclarationSyntax& node , bool callVirtualBase = true);

      /**
      * \brief Visitor which is called at the beginning of the structure::CatchFilterClauseSyntax node visiting.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const structure::CatchFilterClauseSyntax& node , bool callVirtualBase = true);

      /**
      * \brief Visitor which is called at the end of the structure::CatchFilterClauseSyntax node visiting.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const structure::CatchFilterClauseSyntax& node , bool callVirtualBase = true);

      /**
      * \brief Visitor which is called at the beginning of the structure::ClassDeclarationSyntax node visiting.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const structure::ClassDeclarationSyntax& node , bool callVirtualBase = true);

      /**
      * \brief Visitor which is called at the end of the structure::ClassDeclarationSyntax node visiting.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const structure::ClassDeclarationSyntax& node , bool callVirtualBase = true);

      /**
      * \brief Visitor which is called at the beginning of the structure::ClassOrStructConstraintSyntax node visiting.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const structure::ClassOrStructConstraintSyntax& node , bool callVirtualBase = true);

      /**
      * \brief Visitor which is called at the end of the structure::ClassOrStructConstraintSyntax node visiting.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const structure::ClassOrStructConstraintSyntax& node , bool callVirtualBase = true);

      /**
      * \brief Visitor which is called at the beginning of the structure::CompilationUnitSyntax node visiting.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const structure::CompilationUnitSyntax& node , bool callVirtualBase = true);

      /**
      * \brief Visitor which is called at the end of the structure::CompilationUnitSyntax node visiting.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const structure::CompilationUnitSyntax& node , bool callVirtualBase = true);

      /**
      * \brief Visitor which is called at the beginning of the structure::ConstructorConstraintSyntax node visiting.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const structure::ConstructorConstraintSyntax& node , bool callVirtualBase = true);

      /**
      * \brief Visitor which is called at the end of the structure::ConstructorConstraintSyntax node visiting.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const structure::ConstructorConstraintSyntax& node , bool callVirtualBase = true);

      /**
      * \brief Visitor which is called at the beginning of the structure::ConstructorDeclarationSyntax node visiting.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const structure::ConstructorDeclarationSyntax& node , bool callVirtualBase = true);

      /**
      * \brief Visitor which is called at the end of the structure::ConstructorDeclarationSyntax node visiting.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const structure::ConstructorDeclarationSyntax& node , bool callVirtualBase = true);

      /**
      * \brief Visitor which is called at the beginning of the structure::ConstructorInitializerSyntax node visiting.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const structure::ConstructorInitializerSyntax& node , bool callVirtualBase = true);

      /**
      * \brief Visitor which is called at the end of the structure::ConstructorInitializerSyntax node visiting.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const structure::ConstructorInitializerSyntax& node , bool callVirtualBase = true);

      /**
      * \brief Visitor which is called at the beginning of the structure::ConversionOperatorDeclarationSyntax node visiting.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const structure::ConversionOperatorDeclarationSyntax& node , bool callVirtualBase = true);

      /**
      * \brief Visitor which is called at the end of the structure::ConversionOperatorDeclarationSyntax node visiting.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const structure::ConversionOperatorDeclarationSyntax& node , bool callVirtualBase = true);

      /**
      * \brief Visitor which is called at the beginning of the structure::ConversionOperatorMemberCrefSyntax node visiting.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const structure::ConversionOperatorMemberCrefSyntax& node , bool callVirtualBase = true);

      /**
      * \brief Visitor which is called at the end of the structure::ConversionOperatorMemberCrefSyntax node visiting.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const structure::ConversionOperatorMemberCrefSyntax& node , bool callVirtualBase = true);

      /**
      * \brief Visitor which is called at the beginning of the structure::CrefBracketedParameterListSyntax node visiting.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const structure::CrefBracketedParameterListSyntax& node , bool callVirtualBase = true);

      /**
      * \brief Visitor which is called at the end of the structure::CrefBracketedParameterListSyntax node visiting.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const structure::CrefBracketedParameterListSyntax& node , bool callVirtualBase = true);

      /**
      * \brief Visitor which is called at the beginning of the structure::CrefParameterListSyntax node visiting.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const structure::CrefParameterListSyntax& node , bool callVirtualBase = true);

      /**
      * \brief Visitor which is called at the end of the structure::CrefParameterListSyntax node visiting.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const structure::CrefParameterListSyntax& node , bool callVirtualBase = true);

      /**
      * \brief Visitor which is called at the beginning of the structure::CrefParameterSyntax node visiting.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const structure::CrefParameterSyntax& node , bool callVirtualBase = true);

      /**
      * \brief Visitor which is called at the end of the structure::CrefParameterSyntax node visiting.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const structure::CrefParameterSyntax& node , bool callVirtualBase = true);

      /**
      * \brief Visitor which is called at the beginning of the structure::DefaultSwitchLabelSyntax node visiting.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const structure::DefaultSwitchLabelSyntax& node , bool callVirtualBase = true);

      /**
      * \brief Visitor which is called at the end of the structure::DefaultSwitchLabelSyntax node visiting.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const structure::DefaultSwitchLabelSyntax& node , bool callVirtualBase = true);

      /**
      * \brief Visitor which is called at the beginning of the structure::DelegateDeclarationSyntax node visiting.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const structure::DelegateDeclarationSyntax& node , bool callVirtualBase = true);

      /**
      * \brief Visitor which is called at the end of the structure::DelegateDeclarationSyntax node visiting.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const structure::DelegateDeclarationSyntax& node , bool callVirtualBase = true);

      /**
      * \brief Visitor which is called at the beginning of the structure::DestructorDeclarationSyntax node visiting.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const structure::DestructorDeclarationSyntax& node , bool callVirtualBase = true);

      /**
      * \brief Visitor which is called at the end of the structure::DestructorDeclarationSyntax node visiting.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const structure::DestructorDeclarationSyntax& node , bool callVirtualBase = true);

      /**
      * \brief Visitor which is called at the beginning of the structure::ElseClauseSyntax node visiting.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const structure::ElseClauseSyntax& node , bool callVirtualBase = true);

      /**
      * \brief Visitor which is called at the end of the structure::ElseClauseSyntax node visiting.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const structure::ElseClauseSyntax& node , bool callVirtualBase = true);

      /**
      * \brief Visitor which is called at the beginning of the structure::EnumDeclarationSyntax node visiting.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const structure::EnumDeclarationSyntax& node , bool callVirtualBase = true);

      /**
      * \brief Visitor which is called at the end of the structure::EnumDeclarationSyntax node visiting.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const structure::EnumDeclarationSyntax& node , bool callVirtualBase = true);

      /**
      * \brief Visitor which is called at the beginning of the structure::EnumMemberDeclarationSyntax node visiting.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const structure::EnumMemberDeclarationSyntax& node , bool callVirtualBase = true);

      /**
      * \brief Visitor which is called at the end of the structure::EnumMemberDeclarationSyntax node visiting.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const structure::EnumMemberDeclarationSyntax& node , bool callVirtualBase = true);

      /**
      * \brief Visitor which is called at the beginning of the structure::EqualsValueClauseSyntax node visiting.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const structure::EqualsValueClauseSyntax& node , bool callVirtualBase = true);

      /**
      * \brief Visitor which is called at the end of the structure::EqualsValueClauseSyntax node visiting.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const structure::EqualsValueClauseSyntax& node , bool callVirtualBase = true);

      /**
      * \brief Visitor which is called at the beginning of the structure::EventDeclarationSyntax node visiting.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const structure::EventDeclarationSyntax& node , bool callVirtualBase = true);

      /**
      * \brief Visitor which is called at the end of the structure::EventDeclarationSyntax node visiting.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const structure::EventDeclarationSyntax& node , bool callVirtualBase = true);

      /**
      * \brief Visitor which is called at the beginning of the structure::EventFieldDeclarationSyntax node visiting.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const structure::EventFieldDeclarationSyntax& node , bool callVirtualBase = true);

      /**
      * \brief Visitor which is called at the end of the structure::EventFieldDeclarationSyntax node visiting.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const structure::EventFieldDeclarationSyntax& node , bool callVirtualBase = true);

      /**
      * \brief Visitor which is called at the beginning of the structure::ExplicitInterfaceSpecifierSyntax node visiting.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const structure::ExplicitInterfaceSpecifierSyntax& node , bool callVirtualBase = true);

      /**
      * \brief Visitor which is called at the end of the structure::ExplicitInterfaceSpecifierSyntax node visiting.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const structure::ExplicitInterfaceSpecifierSyntax& node , bool callVirtualBase = true);

      /**
      * \brief Visitor which is called at the beginning of the structure::ExternAliasDirectiveSyntax node visiting.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const structure::ExternAliasDirectiveSyntax& node , bool callVirtualBase = true);

      /**
      * \brief Visitor which is called at the end of the structure::ExternAliasDirectiveSyntax node visiting.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const structure::ExternAliasDirectiveSyntax& node , bool callVirtualBase = true);

      /**
      * \brief Visitor which is called at the beginning of the structure::FieldDeclarationSyntax node visiting.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const structure::FieldDeclarationSyntax& node , bool callVirtualBase = true);

      /**
      * \brief Visitor which is called at the end of the structure::FieldDeclarationSyntax node visiting.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const structure::FieldDeclarationSyntax& node , bool callVirtualBase = true);

      /**
      * \brief Visitor which is called at the beginning of the structure::FinallyClauseSyntax node visiting.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const structure::FinallyClauseSyntax& node , bool callVirtualBase = true);

      /**
      * \brief Visitor which is called at the end of the structure::FinallyClauseSyntax node visiting.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const structure::FinallyClauseSyntax& node , bool callVirtualBase = true);

      /**
      * \brief Visitor which is called at the beginning of the structure::FromClauseSyntax node visiting.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const structure::FromClauseSyntax& node , bool callVirtualBase = true);

      /**
      * \brief Visitor which is called at the end of the structure::FromClauseSyntax node visiting.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const structure::FromClauseSyntax& node , bool callVirtualBase = true);

      /**
      * \brief Visitor which is called at the beginning of the structure::GlobalStatementSyntax node visiting.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const structure::GlobalStatementSyntax& node , bool callVirtualBase = true);

      /**
      * \brief Visitor which is called at the end of the structure::GlobalStatementSyntax node visiting.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const structure::GlobalStatementSyntax& node , bool callVirtualBase = true);

      /**
      * \brief Visitor which is called at the beginning of the structure::GroupClauseSyntax node visiting.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const structure::GroupClauseSyntax& node , bool callVirtualBase = true);

      /**
      * \brief Visitor which is called at the end of the structure::GroupClauseSyntax node visiting.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const structure::GroupClauseSyntax& node , bool callVirtualBase = true);

      /**
      * \brief Visitor which is called at the beginning of the structure::IncompleteMemberSyntax node visiting.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const structure::IncompleteMemberSyntax& node , bool callVirtualBase = true);

      /**
      * \brief Visitor which is called at the end of the structure::IncompleteMemberSyntax node visiting.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const structure::IncompleteMemberSyntax& node , bool callVirtualBase = true);

      /**
      * \brief Visitor which is called at the beginning of the structure::IndexerDeclarationSyntax node visiting.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const structure::IndexerDeclarationSyntax& node , bool callVirtualBase = true);

      /**
      * \brief Visitor which is called at the end of the structure::IndexerDeclarationSyntax node visiting.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const structure::IndexerDeclarationSyntax& node , bool callVirtualBase = true);

      /**
      * \brief Visitor which is called at the beginning of the structure::IndexerMemberCrefSyntax node visiting.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const structure::IndexerMemberCrefSyntax& node , bool callVirtualBase = true);

      /**
      * \brief Visitor which is called at the end of the structure::IndexerMemberCrefSyntax node visiting.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const structure::IndexerMemberCrefSyntax& node , bool callVirtualBase = true);

      /**
      * \brief Visitor which is called at the beginning of the structure::InterfaceDeclarationSyntax node visiting.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const structure::InterfaceDeclarationSyntax& node , bool callVirtualBase = true);

      /**
      * \brief Visitor which is called at the end of the structure::InterfaceDeclarationSyntax node visiting.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const structure::InterfaceDeclarationSyntax& node , bool callVirtualBase = true);

      /**
      * \brief Visitor which is called at the beginning of the structure::InterpolatedStringTextSyntax node visiting.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const structure::InterpolatedStringTextSyntax& node , bool callVirtualBase = true);

      /**
      * \brief Visitor which is called at the end of the structure::InterpolatedStringTextSyntax node visiting.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const structure::InterpolatedStringTextSyntax& node , bool callVirtualBase = true);

      /**
      * \brief Visitor which is called at the beginning of the structure::InterpolationAlignmentClauseSyntax node visiting.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const structure::InterpolationAlignmentClauseSyntax& node , bool callVirtualBase = true);

      /**
      * \brief Visitor which is called at the end of the structure::InterpolationAlignmentClauseSyntax node visiting.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const structure::InterpolationAlignmentClauseSyntax& node , bool callVirtualBase = true);

      /**
      * \brief Visitor which is called at the beginning of the structure::InterpolationFormatClauseSyntax node visiting.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const structure::InterpolationFormatClauseSyntax& node , bool callVirtualBase = true);

      /**
      * \brief Visitor which is called at the end of the structure::InterpolationFormatClauseSyntax node visiting.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const structure::InterpolationFormatClauseSyntax& node , bool callVirtualBase = true);

      /**
      * \brief Visitor which is called at the beginning of the structure::InterpolationSyntax node visiting.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const structure::InterpolationSyntax& node , bool callVirtualBase = true);

      /**
      * \brief Visitor which is called at the end of the structure::InterpolationSyntax node visiting.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const structure::InterpolationSyntax& node , bool callVirtualBase = true);

      /**
      * \brief Visitor which is called at the beginning of the structure::JoinClauseSyntax node visiting.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const structure::JoinClauseSyntax& node , bool callVirtualBase = true);

      /**
      * \brief Visitor which is called at the end of the structure::JoinClauseSyntax node visiting.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const structure::JoinClauseSyntax& node , bool callVirtualBase = true);

      /**
      * \brief Visitor which is called at the beginning of the structure::JoinIntoClauseSyntax node visiting.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const structure::JoinIntoClauseSyntax& node , bool callVirtualBase = true);

      /**
      * \brief Visitor which is called at the end of the structure::JoinIntoClauseSyntax node visiting.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const structure::JoinIntoClauseSyntax& node , bool callVirtualBase = true);

      /**
      * \brief Visitor which is called at the beginning of the structure::LetClauseSyntax node visiting.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const structure::LetClauseSyntax& node , bool callVirtualBase = true);

      /**
      * \brief Visitor which is called at the end of the structure::LetClauseSyntax node visiting.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const structure::LetClauseSyntax& node , bool callVirtualBase = true);

      /**
      * \brief Visitor which is called at the beginning of the structure::MethodDeclarationSyntax node visiting.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const structure::MethodDeclarationSyntax& node , bool callVirtualBase = true);

      /**
      * \brief Visitor which is called at the end of the structure::MethodDeclarationSyntax node visiting.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const structure::MethodDeclarationSyntax& node , bool callVirtualBase = true);

      /**
      * \brief Visitor which is called at the beginning of the structure::NameColonSyntax node visiting.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const structure::NameColonSyntax& node , bool callVirtualBase = true);

      /**
      * \brief Visitor which is called at the end of the structure::NameColonSyntax node visiting.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const structure::NameColonSyntax& node , bool callVirtualBase = true);

      /**
      * \brief Visitor which is called at the beginning of the structure::NameEqualsSyntax node visiting.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const structure::NameEqualsSyntax& node , bool callVirtualBase = true);

      /**
      * \brief Visitor which is called at the end of the structure::NameEqualsSyntax node visiting.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const structure::NameEqualsSyntax& node , bool callVirtualBase = true);

      /**
      * \brief Visitor which is called at the beginning of the structure::NameMemberCrefSyntax node visiting.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const structure::NameMemberCrefSyntax& node , bool callVirtualBase = true);

      /**
      * \brief Visitor which is called at the end of the structure::NameMemberCrefSyntax node visiting.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const structure::NameMemberCrefSyntax& node , bool callVirtualBase = true);

      /**
      * \brief Visitor which is called at the beginning of the structure::NamespaceDeclarationSyntax node visiting.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const structure::NamespaceDeclarationSyntax& node , bool callVirtualBase = true);

      /**
      * \brief Visitor which is called at the end of the structure::NamespaceDeclarationSyntax node visiting.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const structure::NamespaceDeclarationSyntax& node , bool callVirtualBase = true);

      /**
      * \brief Visitor which is called at the beginning of the structure::OperatorDeclarationSyntax node visiting.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const structure::OperatorDeclarationSyntax& node , bool callVirtualBase = true);

      /**
      * \brief Visitor which is called at the end of the structure::OperatorDeclarationSyntax node visiting.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const structure::OperatorDeclarationSyntax& node , bool callVirtualBase = true);

      /**
      * \brief Visitor which is called at the beginning of the structure::OperatorMemberCrefSyntax node visiting.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const structure::OperatorMemberCrefSyntax& node , bool callVirtualBase = true);

      /**
      * \brief Visitor which is called at the end of the structure::OperatorMemberCrefSyntax node visiting.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const structure::OperatorMemberCrefSyntax& node , bool callVirtualBase = true);

      /**
      * \brief Visitor which is called at the beginning of the structure::OrderByClauseSyntax node visiting.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const structure::OrderByClauseSyntax& node , bool callVirtualBase = true);

      /**
      * \brief Visitor which is called at the end of the structure::OrderByClauseSyntax node visiting.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const structure::OrderByClauseSyntax& node , bool callVirtualBase = true);

      /**
      * \brief Visitor which is called at the beginning of the structure::OrderingSyntax node visiting.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const structure::OrderingSyntax& node , bool callVirtualBase = true);

      /**
      * \brief Visitor which is called at the end of the structure::OrderingSyntax node visiting.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const structure::OrderingSyntax& node , bool callVirtualBase = true);

      /**
      * \brief Visitor which is called at the beginning of the structure::ParameterListSyntax node visiting.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const structure::ParameterListSyntax& node , bool callVirtualBase = true);

      /**
      * \brief Visitor which is called at the end of the structure::ParameterListSyntax node visiting.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const structure::ParameterListSyntax& node , bool callVirtualBase = true);

      /**
      * \brief Visitor which is called at the beginning of the structure::ParameterSyntax node visiting.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const structure::ParameterSyntax& node , bool callVirtualBase = true);

      /**
      * \brief Visitor which is called at the end of the structure::ParameterSyntax node visiting.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const structure::ParameterSyntax& node , bool callVirtualBase = true);

      /**
      * \brief Visitor which is called at the beginning of the structure::PropertyDeclarationSyntax node visiting.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const structure::PropertyDeclarationSyntax& node , bool callVirtualBase = true);

      /**
      * \brief Visitor which is called at the end of the structure::PropertyDeclarationSyntax node visiting.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const structure::PropertyDeclarationSyntax& node , bool callVirtualBase = true);

      /**
      * \brief Visitor which is called at the beginning of the structure::QualifiedCrefSyntax node visiting.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const structure::QualifiedCrefSyntax& node , bool callVirtualBase = true);

      /**
      * \brief Visitor which is called at the end of the structure::QualifiedCrefSyntax node visiting.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const structure::QualifiedCrefSyntax& node , bool callVirtualBase = true);

      /**
      * \brief Visitor which is called at the beginning of the structure::QueryBodySyntax node visiting.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const structure::QueryBodySyntax& node , bool callVirtualBase = true);

      /**
      * \brief Visitor which is called at the end of the structure::QueryBodySyntax node visiting.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const structure::QueryBodySyntax& node , bool callVirtualBase = true);

      /**
      * \brief Visitor which is called at the beginning of the structure::QueryContinuationSyntax node visiting.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const structure::QueryContinuationSyntax& node , bool callVirtualBase = true);

      /**
      * \brief Visitor which is called at the end of the structure::QueryContinuationSyntax node visiting.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const structure::QueryContinuationSyntax& node , bool callVirtualBase = true);

      /**
      * \brief Visitor which is called at the beginning of the structure::SelectClauseSyntax node visiting.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const structure::SelectClauseSyntax& node , bool callVirtualBase = true);

      /**
      * \brief Visitor which is called at the end of the structure::SelectClauseSyntax node visiting.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const structure::SelectClauseSyntax& node , bool callVirtualBase = true);

      /**
      * \brief Visitor which is called at the beginning of the structure::SimpleBaseTypeSyntax node visiting.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const structure::SimpleBaseTypeSyntax& node , bool callVirtualBase = true);

      /**
      * \brief Visitor which is called at the end of the structure::SimpleBaseTypeSyntax node visiting.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const structure::SimpleBaseTypeSyntax& node , bool callVirtualBase = true);

      /**
      * \brief Visitor which is called at the beginning of the structure::StructDeclarationSyntax node visiting.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const structure::StructDeclarationSyntax& node , bool callVirtualBase = true);

      /**
      * \brief Visitor which is called at the end of the structure::StructDeclarationSyntax node visiting.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const structure::StructDeclarationSyntax& node , bool callVirtualBase = true);

      /**
      * \brief Visitor which is called at the beginning of the structure::SwitchSectionSyntax node visiting.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const structure::SwitchSectionSyntax& node , bool callVirtualBase = true);

      /**
      * \brief Visitor which is called at the end of the structure::SwitchSectionSyntax node visiting.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const structure::SwitchSectionSyntax& node , bool callVirtualBase = true);

      /**
      * \brief Visitor which is called at the beginning of the structure::SyntaxToken node visiting.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const structure::SyntaxToken& node , bool callVirtualBase = true);

      /**
      * \brief Visitor which is called at the end of the structure::SyntaxToken node visiting.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const structure::SyntaxToken& node , bool callVirtualBase = true);

      /**
      * \brief Visitor which is called at the beginning of the structure::TypeArgumentListSyntax node visiting.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const structure::TypeArgumentListSyntax& node , bool callVirtualBase = true);

      /**
      * \brief Visitor which is called at the end of the structure::TypeArgumentListSyntax node visiting.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const structure::TypeArgumentListSyntax& node , bool callVirtualBase = true);

      /**
      * \brief Visitor which is called at the beginning of the structure::TypeConstraintSyntax node visiting.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const structure::TypeConstraintSyntax& node , bool callVirtualBase = true);

      /**
      * \brief Visitor which is called at the end of the structure::TypeConstraintSyntax node visiting.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const structure::TypeConstraintSyntax& node , bool callVirtualBase = true);

      /**
      * \brief Visitor which is called at the beginning of the structure::TypeCrefSyntax node visiting.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const structure::TypeCrefSyntax& node , bool callVirtualBase = true);

      /**
      * \brief Visitor which is called at the end of the structure::TypeCrefSyntax node visiting.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const structure::TypeCrefSyntax& node , bool callVirtualBase = true);

      /**
      * \brief Visitor which is called at the beginning of the structure::TypeParameterConstraintClauseSyntax node visiting.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const structure::TypeParameterConstraintClauseSyntax& node , bool callVirtualBase = true);

      /**
      * \brief Visitor which is called at the end of the structure::TypeParameterConstraintClauseSyntax node visiting.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const structure::TypeParameterConstraintClauseSyntax& node , bool callVirtualBase = true);

      /**
      * \brief Visitor which is called at the beginning of the structure::TypeParameterListSyntax node visiting.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const structure::TypeParameterListSyntax& node , bool callVirtualBase = true);

      /**
      * \brief Visitor which is called at the end of the structure::TypeParameterListSyntax node visiting.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const structure::TypeParameterListSyntax& node , bool callVirtualBase = true);

      /**
      * \brief Visitor which is called at the beginning of the structure::TypeParameterSyntax node visiting.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const structure::TypeParameterSyntax& node , bool callVirtualBase = true);

      /**
      * \brief Visitor which is called at the end of the structure::TypeParameterSyntax node visiting.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const structure::TypeParameterSyntax& node , bool callVirtualBase = true);

      /**
      * \brief Visitor which is called at the beginning of the structure::UsingDirectiveSyntax node visiting.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const structure::UsingDirectiveSyntax& node , bool callVirtualBase = true);

      /**
      * \brief Visitor which is called at the end of the structure::UsingDirectiveSyntax node visiting.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const structure::UsingDirectiveSyntax& node , bool callVirtualBase = true);

      /**
      * \brief Visitor which is called at the beginning of the structure::VariableDeclarationSyntax node visiting.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const structure::VariableDeclarationSyntax& node , bool callVirtualBase = true);

      /**
      * \brief Visitor which is called at the end of the structure::VariableDeclarationSyntax node visiting.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const structure::VariableDeclarationSyntax& node , bool callVirtualBase = true);

      /**
      * \brief Visitor which is called at the beginning of the structure::VariableDeclaratorSyntax node visiting.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const structure::VariableDeclaratorSyntax& node , bool callVirtualBase = true);

      /**
      * \brief Visitor which is called at the end of the structure::VariableDeclaratorSyntax node visiting.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const structure::VariableDeclaratorSyntax& node , bool callVirtualBase = true);

      /**
      * \brief Visitor which is called at the beginning of the structure::WhereClauseSyntax node visiting.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const structure::WhereClauseSyntax& node , bool callVirtualBase = true);

      /**
      * \brief Visitor which is called at the end of the structure::WhereClauseSyntax node visiting.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const structure::WhereClauseSyntax& node , bool callVirtualBase = true);

      /**
      * \brief Visitor which is called at the beginning of the structure::XmlCDataSectionSyntax node visiting.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const structure::XmlCDataSectionSyntax& node , bool callVirtualBase = true);

      /**
      * \brief Visitor which is called at the end of the structure::XmlCDataSectionSyntax node visiting.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const structure::XmlCDataSectionSyntax& node , bool callVirtualBase = true);

      /**
      * \brief Visitor which is called at the beginning of the structure::XmlCommentSyntax node visiting.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const structure::XmlCommentSyntax& node , bool callVirtualBase = true);

      /**
      * \brief Visitor which is called at the end of the structure::XmlCommentSyntax node visiting.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const structure::XmlCommentSyntax& node , bool callVirtualBase = true);

      /**
      * \brief Visitor which is called at the beginning of the structure::XmlCrefAttributeSyntax node visiting.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const structure::XmlCrefAttributeSyntax& node , bool callVirtualBase = true);

      /**
      * \brief Visitor which is called at the end of the structure::XmlCrefAttributeSyntax node visiting.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const structure::XmlCrefAttributeSyntax& node , bool callVirtualBase = true);

      /**
      * \brief Visitor which is called at the beginning of the structure::XmlElementEndTagSyntax node visiting.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const structure::XmlElementEndTagSyntax& node , bool callVirtualBase = true);

      /**
      * \brief Visitor which is called at the end of the structure::XmlElementEndTagSyntax node visiting.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const structure::XmlElementEndTagSyntax& node , bool callVirtualBase = true);

      /**
      * \brief Visitor which is called at the beginning of the structure::XmlElementStartTagSyntax node visiting.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const structure::XmlElementStartTagSyntax& node , bool callVirtualBase = true);

      /**
      * \brief Visitor which is called at the end of the structure::XmlElementStartTagSyntax node visiting.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const structure::XmlElementStartTagSyntax& node , bool callVirtualBase = true);

      /**
      * \brief Visitor which is called at the beginning of the structure::XmlElementSyntax node visiting.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const structure::XmlElementSyntax& node , bool callVirtualBase = true);

      /**
      * \brief Visitor which is called at the end of the structure::XmlElementSyntax node visiting.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const structure::XmlElementSyntax& node , bool callVirtualBase = true);

      /**
      * \brief Visitor which is called at the beginning of the structure::XmlEmptyElementSyntax node visiting.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const structure::XmlEmptyElementSyntax& node , bool callVirtualBase = true);

      /**
      * \brief Visitor which is called at the end of the structure::XmlEmptyElementSyntax node visiting.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const structure::XmlEmptyElementSyntax& node , bool callVirtualBase = true);

      /**
      * \brief Visitor which is called at the beginning of the structure::XmlNameAttributeSyntax node visiting.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const structure::XmlNameAttributeSyntax& node , bool callVirtualBase = true);

      /**
      * \brief Visitor which is called at the end of the structure::XmlNameAttributeSyntax node visiting.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const structure::XmlNameAttributeSyntax& node , bool callVirtualBase = true);

      /**
      * \brief Visitor which is called at the beginning of the structure::XmlNameSyntax node visiting.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const structure::XmlNameSyntax& node , bool callVirtualBase = true);

      /**
      * \brief Visitor which is called at the end of the structure::XmlNameSyntax node visiting.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const structure::XmlNameSyntax& node , bool callVirtualBase = true);

      /**
      * \brief Visitor which is called at the beginning of the structure::XmlPrefixSyntax node visiting.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const structure::XmlPrefixSyntax& node , bool callVirtualBase = true);

      /**
      * \brief Visitor which is called at the end of the structure::XmlPrefixSyntax node visiting.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const structure::XmlPrefixSyntax& node , bool callVirtualBase = true);

      /**
      * \brief Visitor which is called at the beginning of the structure::XmlProcessingInstructionSyntax node visiting.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const structure::XmlProcessingInstructionSyntax& node , bool callVirtualBase = true);

      /**
      * \brief Visitor which is called at the end of the structure::XmlProcessingInstructionSyntax node visiting.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const structure::XmlProcessingInstructionSyntax& node , bool callVirtualBase = true);

      /**
      * \brief Visitor which is called at the beginning of the structure::XmlTextAttributeSyntax node visiting.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const structure::XmlTextAttributeSyntax& node , bool callVirtualBase = true);

      /**
      * \brief Visitor which is called at the end of the structure::XmlTextAttributeSyntax node visiting.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const structure::XmlTextAttributeSyntax& node , bool callVirtualBase = true);

      /**
      * \brief Visitor which is called at the beginning of the structure::XmlTextSyntax node visiting.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const structure::XmlTextSyntax& node , bool callVirtualBase = true);

      /**
      * \brief Visitor which is called at the end of the structure::XmlTextSyntax node visiting.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const structure::XmlTextSyntax& node , bool callVirtualBase = true);

      /**
      * \brief Edge  visitor for Alias edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitAliasQualifiedNameSyntax_Alias(const expression::AliasQualifiedNameSyntax& begin, const expression::IdentifierNameSyntax& end);

      /**
      * \brief Edge end visitor for Alias edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndAliasQualifiedNameSyntax_Alias(const expression::AliasQualifiedNameSyntax& begin, const expression::IdentifierNameSyntax& end);

      /**
      * \brief Edge  visitor for Name edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitAliasQualifiedNameSyntax_Name(const expression::AliasQualifiedNameSyntax& begin, const expression::SimpleNameSyntax& end);

      /**
      * \brief Edge end visitor for Name edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndAliasQualifiedNameSyntax_Name(const expression::AliasQualifiedNameSyntax& begin, const expression::SimpleNameSyntax& end);

      /**
      * \brief Edge  visitor for Body edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitAnonymousFunctionExpressionSyntax_Body(const expression::AnonymousFunctionExpressionSyntax& begin, const base::Positioned& end);

      /**
      * \brief Edge end visitor for Body edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndAnonymousFunctionExpressionSyntax_Body(const expression::AnonymousFunctionExpressionSyntax& begin, const base::Positioned& end);

      /**
      * \brief Edge  visitor for ParameterList edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitAnonymousMethodExpressionSyntax_ParameterList(const expression::AnonymousMethodExpressionSyntax& begin, const structure::ParameterListSyntax& end);

      /**
      * \brief Edge end visitor for ParameterList edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndAnonymousMethodExpressionSyntax_ParameterList(const expression::AnonymousMethodExpressionSyntax& begin, const structure::ParameterListSyntax& end);

      /**
      * \brief Edge  visitor for Initializers edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitAnonymousObjectCreationExpressionSyntax_Initializers(const expression::AnonymousObjectCreationExpressionSyntax& begin, const structure::AnonymousObjectMemberDeclaratorSyntax& end);

      /**
      * \brief Edge end visitor for Initializers edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndAnonymousObjectCreationExpressionSyntax_Initializers(const expression::AnonymousObjectCreationExpressionSyntax& begin, const structure::AnonymousObjectMemberDeclaratorSyntax& end);

      /**
      * \brief Edge  visitor for Initializer edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitArrayCreationExpressionSyntax_Initializer(const expression::ArrayCreationExpressionSyntax& begin, const expression::InitializerExpressionSyntax& end);

      /**
      * \brief Edge end visitor for Initializer edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndArrayCreationExpressionSyntax_Initializer(const expression::ArrayCreationExpressionSyntax& begin, const expression::InitializerExpressionSyntax& end);

      /**
      * \brief Edge  visitor for Type edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitArrayCreationExpressionSyntax_Type(const expression::ArrayCreationExpressionSyntax& begin, const expression::ArrayTypeSyntax& end);

      /**
      * \brief Edge end visitor for Type edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndArrayCreationExpressionSyntax_Type(const expression::ArrayCreationExpressionSyntax& begin, const expression::ArrayTypeSyntax& end);

      /**
      * \brief Edge  visitor for ElementType edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitArrayTypeSyntax_ElementType(const expression::ArrayTypeSyntax& begin, const expression::TypeSyntax& end);

      /**
      * \brief Edge end visitor for ElementType edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndArrayTypeSyntax_ElementType(const expression::ArrayTypeSyntax& begin, const expression::TypeSyntax& end);

      /**
      * \brief Edge  visitor for RankSpecifiers edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitArrayTypeSyntax_RankSpecifiers(const expression::ArrayTypeSyntax& begin, const structure::ArrayRankSpecifierSyntax& end);

      /**
      * \brief Edge end visitor for RankSpecifiers edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndArrayTypeSyntax_RankSpecifiers(const expression::ArrayTypeSyntax& begin, const structure::ArrayRankSpecifierSyntax& end);

      /**
      * \brief Edge visitor for EventAccessorCall edge which.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitAssignmentExpressionSyntax_EventAccessorCall(const expression::AssignmentExpressionSyntax& begin, const structure::AccessorDeclarationSyntax& end);

      /**
      * \brief Edge visitor for EventAccessorCall edge which.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndAssignmentExpressionSyntax_EventAccessorCall(const expression::AssignmentExpressionSyntax& begin, const structure::AccessorDeclarationSyntax& end);

      /**
      * \brief Edge  visitor for Left edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitAssignmentExpressionSyntax_Left(const expression::AssignmentExpressionSyntax& begin, const expression::ExpressionSyntax& end);

      /**
      * \brief Edge end visitor for Left edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndAssignmentExpressionSyntax_Left(const expression::AssignmentExpressionSyntax& begin, const expression::ExpressionSyntax& end);

      /**
      * \brief Edge visitor for OverloadedOperatorCall edge which.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitAssignmentExpressionSyntax_OverloadedOperatorCall(const expression::AssignmentExpressionSyntax& begin, const structure::OperatorDeclarationSyntax& end);

      /**
      * \brief Edge visitor for OverloadedOperatorCall edge which.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndAssignmentExpressionSyntax_OverloadedOperatorCall(const expression::AssignmentExpressionSyntax& begin, const structure::OperatorDeclarationSyntax& end);

      /**
      * \brief Edge  visitor for Right edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitAssignmentExpressionSyntax_Right(const expression::AssignmentExpressionSyntax& begin, const expression::ExpressionSyntax& end);

      /**
      * \brief Edge end visitor for Right edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndAssignmentExpressionSyntax_Right(const expression::AssignmentExpressionSyntax& begin, const expression::ExpressionSyntax& end);

      /**
      * \brief Edge  visitor for Expression edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitAwaitExpressionSyntax_Expression(const expression::AwaitExpressionSyntax& begin, const expression::ExpressionSyntax& end);

      /**
      * \brief Edge end visitor for Expression edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndAwaitExpressionSyntax_Expression(const expression::AwaitExpressionSyntax& begin, const expression::ExpressionSyntax& end);

      /**
      * \brief Edge  visitor for Left edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitBinaryExpressionSyntax_Left(const expression::BinaryExpressionSyntax& begin, const expression::ExpressionSyntax& end);

      /**
      * \brief Edge end visitor for Left edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndBinaryExpressionSyntax_Left(const expression::BinaryExpressionSyntax& begin, const expression::ExpressionSyntax& end);

      /**
      * \brief Edge visitor for OverloadedOperatorCall edge which.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitBinaryExpressionSyntax_OverloadedOperatorCall(const expression::BinaryExpressionSyntax& begin, const structure::OperatorDeclarationSyntax& end);

      /**
      * \brief Edge visitor for OverloadedOperatorCall edge which.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndBinaryExpressionSyntax_OverloadedOperatorCall(const expression::BinaryExpressionSyntax& begin, const structure::OperatorDeclarationSyntax& end);

      /**
      * \brief Edge  visitor for Right edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitBinaryExpressionSyntax_Right(const expression::BinaryExpressionSyntax& begin, const expression::ExpressionSyntax& end);

      /**
      * \brief Edge end visitor for Right edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndBinaryExpressionSyntax_Right(const expression::BinaryExpressionSyntax& begin, const expression::ExpressionSyntax& end);

      /**
      * \brief Edge visitor for ConversionOperatorCall edge which.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitCastExpressionSyntax_ConversionOperatorCall(const expression::CastExpressionSyntax& begin, const structure::ConversionOperatorDeclarationSyntax& end);

      /**
      * \brief Edge visitor for ConversionOperatorCall edge which.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndCastExpressionSyntax_ConversionOperatorCall(const expression::CastExpressionSyntax& begin, const structure::ConversionOperatorDeclarationSyntax& end);

      /**
      * \brief Edge  visitor for Expression edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitCastExpressionSyntax_Expression(const expression::CastExpressionSyntax& begin, const expression::ExpressionSyntax& end);

      /**
      * \brief Edge end visitor for Expression edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndCastExpressionSyntax_Expression(const expression::CastExpressionSyntax& begin, const expression::ExpressionSyntax& end);

      /**
      * \brief Edge  visitor for Type edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitCastExpressionSyntax_Type(const expression::CastExpressionSyntax& begin, const expression::TypeSyntax& end);

      /**
      * \brief Edge end visitor for Type edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndCastExpressionSyntax_Type(const expression::CastExpressionSyntax& begin, const expression::TypeSyntax& end);

      /**
      * \brief Edge  visitor for Expression edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitCheckedExpressionSyntax_Expression(const expression::CheckedExpressionSyntax& begin, const expression::ExpressionSyntax& end);

      /**
      * \brief Edge end visitor for Expression edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndCheckedExpressionSyntax_Expression(const expression::CheckedExpressionSyntax& begin, const expression::ExpressionSyntax& end);

      /**
      * \brief Edge  visitor for Expression edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitConditionalAccessExpressionSyntax_Expression(const expression::ConditionalAccessExpressionSyntax& begin, const expression::ExpressionSyntax& end);

      /**
      * \brief Edge end visitor for Expression edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndConditionalAccessExpressionSyntax_Expression(const expression::ConditionalAccessExpressionSyntax& begin, const expression::ExpressionSyntax& end);

      /**
      * \brief Edge  visitor for WhenNotNull edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitConditionalAccessExpressionSyntax_WhenNotNull(const expression::ConditionalAccessExpressionSyntax& begin, const expression::ExpressionSyntax& end);

      /**
      * \brief Edge end visitor for WhenNotNull edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndConditionalAccessExpressionSyntax_WhenNotNull(const expression::ConditionalAccessExpressionSyntax& begin, const expression::ExpressionSyntax& end);

      /**
      * \brief Edge  visitor for Condition edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitConditionalExpressionSyntax_Condition(const expression::ConditionalExpressionSyntax& begin, const expression::ExpressionSyntax& end);

      /**
      * \brief Edge end visitor for Condition edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndConditionalExpressionSyntax_Condition(const expression::ConditionalExpressionSyntax& begin, const expression::ExpressionSyntax& end);

      /**
      * \brief Edge  visitor for WhenFalse edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitConditionalExpressionSyntax_WhenFalse(const expression::ConditionalExpressionSyntax& begin, const expression::ExpressionSyntax& end);

      /**
      * \brief Edge end visitor for WhenFalse edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndConditionalExpressionSyntax_WhenFalse(const expression::ConditionalExpressionSyntax& begin, const expression::ExpressionSyntax& end);

      /**
      * \brief Edge  visitor for WhenTrue edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitConditionalExpressionSyntax_WhenTrue(const expression::ConditionalExpressionSyntax& begin, const expression::ExpressionSyntax& end);

      /**
      * \brief Edge end visitor for WhenTrue edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndConditionalExpressionSyntax_WhenTrue(const expression::ConditionalExpressionSyntax& begin, const expression::ExpressionSyntax& end);

      /**
      * \brief Edge  visitor for Type edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitDefaultExpressionSyntax_Type(const expression::DefaultExpressionSyntax& begin, const expression::TypeSyntax& end);

      /**
      * \brief Edge end visitor for Type edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndDefaultExpressionSyntax_Type(const expression::DefaultExpressionSyntax& begin, const expression::TypeSyntax& end);

      /**
      * \brief Edge visitor for AccessorCall edge which.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitElementAccessExpressionSyntax_AccessorCall(const expression::ElementAccessExpressionSyntax& begin, const structure::AccessorDeclarationSyntax& end);

      /**
      * \brief Edge visitor for AccessorCall edge which.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndElementAccessExpressionSyntax_AccessorCall(const expression::ElementAccessExpressionSyntax& begin, const structure::AccessorDeclarationSyntax& end);

      /**
      * \brief Edge  visitor for ArgumentList edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitElementAccessExpressionSyntax_ArgumentList(const expression::ElementAccessExpressionSyntax& begin, const structure::BracketedArgumentListSyntax& end);

      /**
      * \brief Edge end visitor for ArgumentList edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndElementAccessExpressionSyntax_ArgumentList(const expression::ElementAccessExpressionSyntax& begin, const structure::BracketedArgumentListSyntax& end);

      /**
      * \brief Edge  visitor for Expression edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitElementAccessExpressionSyntax_Expression(const expression::ElementAccessExpressionSyntax& begin, const expression::ExpressionSyntax& end);

      /**
      * \brief Edge end visitor for Expression edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndElementAccessExpressionSyntax_Expression(const expression::ElementAccessExpressionSyntax& begin, const expression::ExpressionSyntax& end);

      /**
      * \brief Edge  visitor for ArgumentList edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitElementBindingExpressionSyntax_ArgumentList(const expression::ElementBindingExpressionSyntax& begin, const structure::BracketedArgumentListSyntax& end);

      /**
      * \brief Edge end visitor for ArgumentList edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndElementBindingExpressionSyntax_ArgumentList(const expression::ElementBindingExpressionSyntax& begin, const structure::BracketedArgumentListSyntax& end);

      /**
      * \brief Edge  visitor for TypeArgumentList edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitGenericNameSyntax_TypeArgumentList(const expression::GenericNameSyntax& begin, const structure::TypeArgumentListSyntax& end);

      /**
      * \brief Edge end visitor for TypeArgumentList edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndGenericNameSyntax_TypeArgumentList(const expression::GenericNameSyntax& begin, const structure::TypeArgumentListSyntax& end);

      /**
      * \brief Edge visitor for AccessorCall edge which.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitIdentifierNameSyntax_AccessorCall(const expression::IdentifierNameSyntax& begin, const structure::AccessorDeclarationSyntax& end);

      /**
      * \brief Edge visitor for AccessorCall edge which.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndIdentifierNameSyntax_AccessorCall(const expression::IdentifierNameSyntax& begin, const structure::AccessorDeclarationSyntax& end);

      /**
      * \brief Edge visitor for Declaration edge which.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitIdentifierNameSyntax_Declaration(const expression::IdentifierNameSyntax& begin, const base::Positioned& end);

      /**
      * \brief Edge visitor for Declaration edge which.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndIdentifierNameSyntax_Declaration(const expression::IdentifierNameSyntax& begin, const base::Positioned& end);

      /**
      * \brief Edge  visitor for Initializer edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitImplicitArrayCreationExpressionSyntax_Initializer(const expression::ImplicitArrayCreationExpressionSyntax& begin, const expression::InitializerExpressionSyntax& end);

      /**
      * \brief Edge end visitor for Initializer edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndImplicitArrayCreationExpressionSyntax_Initializer(const expression::ImplicitArrayCreationExpressionSyntax& begin, const expression::InitializerExpressionSyntax& end);

      /**
      * \brief Edge  visitor for ArgumentList edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitImplicitElementAccessSyntax_ArgumentList(const expression::ImplicitElementAccessSyntax& begin, const structure::BracketedArgumentListSyntax& end);

      /**
      * \brief Edge end visitor for ArgumentList edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndImplicitElementAccessSyntax_ArgumentList(const expression::ImplicitElementAccessSyntax& begin, const structure::BracketedArgumentListSyntax& end);

      /**
      * \brief Edge  visitor for Expressions edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitInitializerExpressionSyntax_Expressions(const expression::InitializerExpressionSyntax& begin, const expression::ExpressionSyntax& end);

      /**
      * \brief Edge end visitor for Expressions edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndInitializerExpressionSyntax_Expressions(const expression::InitializerExpressionSyntax& begin, const expression::ExpressionSyntax& end);

      /**
      * \brief Edge  visitor for Contents edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitInterpolatedStringExpressionSyntax_Contents(const expression::InterpolatedStringExpressionSyntax& begin, const structure::InterpolatedStringContentSyntax& end);

      /**
      * \brief Edge end visitor for Contents edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndInterpolatedStringExpressionSyntax_Contents(const expression::InterpolatedStringExpressionSyntax& begin, const structure::InterpolatedStringContentSyntax& end);

      /**
      * \brief Edge  visitor for ArgumentList edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitInvocationExpressionSyntax_ArgumentList(const expression::InvocationExpressionSyntax& begin, const structure::ArgumentListSyntax& end);

      /**
      * \brief Edge end visitor for ArgumentList edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndInvocationExpressionSyntax_ArgumentList(const expression::InvocationExpressionSyntax& begin, const structure::ArgumentListSyntax& end);

      /**
      * \brief Edge  visitor for Expression edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitInvocationExpressionSyntax_Expression(const expression::InvocationExpressionSyntax& begin, const expression::ExpressionSyntax& end);

      /**
      * \brief Edge end visitor for Expression edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndInvocationExpressionSyntax_Expression(const expression::InvocationExpressionSyntax& begin, const expression::ExpressionSyntax& end);

      /**
      * \brief Edge visitor for MethodCall edge which.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitInvocationExpressionSyntax_MethodCall(const expression::InvocationExpressionSyntax& begin, const structure::MethodDeclarationSyntax& end);

      /**
      * \brief Edge visitor for MethodCall edge which.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndInvocationExpressionSyntax_MethodCall(const expression::InvocationExpressionSyntax& begin, const structure::MethodDeclarationSyntax& end);

      /**
      * \brief Edge  visitor for Expression edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitMakeRefExpressionSyntax_Expression(const expression::MakeRefExpressionSyntax& begin, const expression::ExpressionSyntax& end);

      /**
      * \brief Edge end visitor for Expression edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndMakeRefExpressionSyntax_Expression(const expression::MakeRefExpressionSyntax& begin, const expression::ExpressionSyntax& end);

      /**
      * \brief Edge  visitor for Expression edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitMemberAccessExpressionSyntax_Expression(const expression::MemberAccessExpressionSyntax& begin, const expression::ExpressionSyntax& end);

      /**
      * \brief Edge end visitor for Expression edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndMemberAccessExpressionSyntax_Expression(const expression::MemberAccessExpressionSyntax& begin, const expression::ExpressionSyntax& end);

      /**
      * \brief Edge  visitor for Name edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitMemberAccessExpressionSyntax_Name(const expression::MemberAccessExpressionSyntax& begin, const expression::SimpleNameSyntax& end);

      /**
      * \brief Edge end visitor for Name edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndMemberAccessExpressionSyntax_Name(const expression::MemberAccessExpressionSyntax& begin, const expression::SimpleNameSyntax& end);

      /**
      * \brief Edge  visitor for Name edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitMemberBindingExpressionSyntax_Name(const expression::MemberBindingExpressionSyntax& begin, const expression::SimpleNameSyntax& end);

      /**
      * \brief Edge end visitor for Name edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndMemberBindingExpressionSyntax_Name(const expression::MemberBindingExpressionSyntax& begin, const expression::SimpleNameSyntax& end);

      /**
      * \brief Edge  visitor for ElementType edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitNullableTypeSyntax_ElementType(const expression::NullableTypeSyntax& begin, const expression::TypeSyntax& end);

      /**
      * \brief Edge end visitor for ElementType edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndNullableTypeSyntax_ElementType(const expression::NullableTypeSyntax& begin, const expression::TypeSyntax& end);

      /**
      * \brief Edge  visitor for ArgumentList edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitObjectCreationExpressionSyntax_ArgumentList(const expression::ObjectCreationExpressionSyntax& begin, const structure::ArgumentListSyntax& end);

      /**
      * \brief Edge end visitor for ArgumentList edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndObjectCreationExpressionSyntax_ArgumentList(const expression::ObjectCreationExpressionSyntax& begin, const structure::ArgumentListSyntax& end);

      /**
      * \brief Edge visitor for ConstructorCall edge which.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitObjectCreationExpressionSyntax_ConstructorCall(const expression::ObjectCreationExpressionSyntax& begin, const structure::ConstructorDeclarationSyntax& end);

      /**
      * \brief Edge visitor for ConstructorCall edge which.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndObjectCreationExpressionSyntax_ConstructorCall(const expression::ObjectCreationExpressionSyntax& begin, const structure::ConstructorDeclarationSyntax& end);

      /**
      * \brief Edge  visitor for Initializer edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitObjectCreationExpressionSyntax_Initializer(const expression::ObjectCreationExpressionSyntax& begin, const expression::InitializerExpressionSyntax& end);

      /**
      * \brief Edge end visitor for Initializer edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndObjectCreationExpressionSyntax_Initializer(const expression::ObjectCreationExpressionSyntax& begin, const expression::InitializerExpressionSyntax& end);

      /**
      * \brief Edge  visitor for Type edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitObjectCreationExpressionSyntax_Type(const expression::ObjectCreationExpressionSyntax& begin, const expression::TypeSyntax& end);

      /**
      * \brief Edge end visitor for Type edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndObjectCreationExpressionSyntax_Type(const expression::ObjectCreationExpressionSyntax& begin, const expression::TypeSyntax& end);

      /**
      * \brief Edge  visitor for Expression edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitParenthesizedExpressionSyntax_Expression(const expression::ParenthesizedExpressionSyntax& begin, const expression::ExpressionSyntax& end);

      /**
      * \brief Edge end visitor for Expression edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndParenthesizedExpressionSyntax_Expression(const expression::ParenthesizedExpressionSyntax& begin, const expression::ExpressionSyntax& end);

      /**
      * \brief Edge  visitor for ParameterList edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitParenthesizedLambdaExpressionSyntax_ParameterList(const expression::ParenthesizedLambdaExpressionSyntax& begin, const structure::ParameterListSyntax& end);

      /**
      * \brief Edge end visitor for ParameterList edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndParenthesizedLambdaExpressionSyntax_ParameterList(const expression::ParenthesizedLambdaExpressionSyntax& begin, const structure::ParameterListSyntax& end);

      /**
      * \brief Edge  visitor for ElementType edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitPointerTypeSyntax_ElementType(const expression::PointerTypeSyntax& begin, const expression::TypeSyntax& end);

      /**
      * \brief Edge end visitor for ElementType edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndPointerTypeSyntax_ElementType(const expression::PointerTypeSyntax& begin, const expression::TypeSyntax& end);

      /**
      * \brief Edge  visitor for Operand edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitPostfixUnaryExpressionSyntax_Operand(const expression::PostfixUnaryExpressionSyntax& begin, const expression::ExpressionSyntax& end);

      /**
      * \brief Edge end visitor for Operand edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndPostfixUnaryExpressionSyntax_Operand(const expression::PostfixUnaryExpressionSyntax& begin, const expression::ExpressionSyntax& end);

      /**
      * \brief Edge visitor for OverloadedOperatorCall edge which.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitPostfixUnaryExpressionSyntax_OverloadedOperatorCall(const expression::PostfixUnaryExpressionSyntax& begin, const structure::OperatorDeclarationSyntax& end);

      /**
      * \brief Edge visitor for OverloadedOperatorCall edge which.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndPostfixUnaryExpressionSyntax_OverloadedOperatorCall(const expression::PostfixUnaryExpressionSyntax& begin, const structure::OperatorDeclarationSyntax& end);

      /**
      * \brief Edge  visitor for Operand edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitPrefixUnaryExpressionSyntax_Operand(const expression::PrefixUnaryExpressionSyntax& begin, const expression::ExpressionSyntax& end);

      /**
      * \brief Edge end visitor for Operand edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndPrefixUnaryExpressionSyntax_Operand(const expression::PrefixUnaryExpressionSyntax& begin, const expression::ExpressionSyntax& end);

      /**
      * \brief Edge visitor for OverloadedOperatorCall edge which.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitPrefixUnaryExpressionSyntax_OverloadedOperatorCall(const expression::PrefixUnaryExpressionSyntax& begin, const structure::OperatorDeclarationSyntax& end);

      /**
      * \brief Edge visitor for OverloadedOperatorCall edge which.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndPrefixUnaryExpressionSyntax_OverloadedOperatorCall(const expression::PrefixUnaryExpressionSyntax& begin, const structure::OperatorDeclarationSyntax& end);

      /**
      * \brief Edge  visitor for Left edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitQualifiedNameSyntax_Left(const expression::QualifiedNameSyntax& begin, const expression::NameSyntax& end);

      /**
      * \brief Edge end visitor for Left edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndQualifiedNameSyntax_Left(const expression::QualifiedNameSyntax& begin, const expression::NameSyntax& end);

      /**
      * \brief Edge  visitor for Right edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitQualifiedNameSyntax_Right(const expression::QualifiedNameSyntax& begin, const expression::SimpleNameSyntax& end);

      /**
      * \brief Edge end visitor for Right edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndQualifiedNameSyntax_Right(const expression::QualifiedNameSyntax& begin, const expression::SimpleNameSyntax& end);

      /**
      * \brief Edge  visitor for Body edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitQueryExpressionSyntax_Body(const expression::QueryExpressionSyntax& begin, const structure::QueryBodySyntax& end);

      /**
      * \brief Edge end visitor for Body edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndQueryExpressionSyntax_Body(const expression::QueryExpressionSyntax& begin, const structure::QueryBodySyntax& end);

      /**
      * \brief Edge  visitor for FromClause edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitQueryExpressionSyntax_FromClause(const expression::QueryExpressionSyntax& begin, const structure::FromClauseSyntax& end);

      /**
      * \brief Edge end visitor for FromClause edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndQueryExpressionSyntax_FromClause(const expression::QueryExpressionSyntax& begin, const structure::FromClauseSyntax& end);

      /**
      * \brief Edge  visitor for Expression edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitRefTypeExpressionSyntax_Expression(const expression::RefTypeExpressionSyntax& begin, const expression::ExpressionSyntax& end);

      /**
      * \brief Edge end visitor for Expression edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndRefTypeExpressionSyntax_Expression(const expression::RefTypeExpressionSyntax& begin, const expression::ExpressionSyntax& end);

      /**
      * \brief Edge  visitor for Expression edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitRefValueExpressionSyntax_Expression(const expression::RefValueExpressionSyntax& begin, const expression::ExpressionSyntax& end);

      /**
      * \brief Edge end visitor for Expression edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndRefValueExpressionSyntax_Expression(const expression::RefValueExpressionSyntax& begin, const expression::ExpressionSyntax& end);

      /**
      * \brief Edge  visitor for Type edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitRefValueExpressionSyntax_Type(const expression::RefValueExpressionSyntax& begin, const expression::TypeSyntax& end);

      /**
      * \brief Edge end visitor for Type edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndRefValueExpressionSyntax_Type(const expression::RefValueExpressionSyntax& begin, const expression::TypeSyntax& end);

      /**
      * \brief Edge  visitor for Parameter edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitSimpleLambdaExpressionSyntax_Parameter(const expression::SimpleLambdaExpressionSyntax& begin, const structure::ParameterSyntax& end);

      /**
      * \brief Edge end visitor for Parameter edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndSimpleLambdaExpressionSyntax_Parameter(const expression::SimpleLambdaExpressionSyntax& begin, const structure::ParameterSyntax& end);

      /**
      * \brief Edge  visitor for Type edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitSizeOfExpressionSyntax_Type(const expression::SizeOfExpressionSyntax& begin, const expression::TypeSyntax& end);

      /**
      * \brief Edge end visitor for Type edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndSizeOfExpressionSyntax_Type(const expression::SizeOfExpressionSyntax& begin, const expression::TypeSyntax& end);

      /**
      * \brief Edge  visitor for Type edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitStackAllocArrayCreationExpressionSyntax_Type(const expression::StackAllocArrayCreationExpressionSyntax& begin, const expression::TypeSyntax& end);

      /**
      * \brief Edge end visitor for Type edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndStackAllocArrayCreationExpressionSyntax_Type(const expression::StackAllocArrayCreationExpressionSyntax& begin, const expression::TypeSyntax& end);

      /**
      * \brief Edge  visitor for Type edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitTypeOfExpressionSyntax_Type(const expression::TypeOfExpressionSyntax& begin, const expression::TypeSyntax& end);

      /**
      * \brief Edge end visitor for Type edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndTypeOfExpressionSyntax_Type(const expression::TypeOfExpressionSyntax& begin, const expression::TypeSyntax& end);

      /**
      * \brief Edge visitor for OriginalDefinition edge which.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitTypeSyntax_OriginalDefinition(const expression::TypeSyntax& begin, const structure::MemberDeclarationSyntax& end);

      /**
      * \brief Edge visitor for OriginalDefinition edge which.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndTypeSyntax_OriginalDefinition(const expression::TypeSyntax& begin, const structure::MemberDeclarationSyntax& end);

      /**
      * \brief Edge  visitor for Statements edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitBlockSyntax_Statements(const statement::BlockSyntax& begin, const statement::StatementSyntax& end);

      /**
      * \brief Edge end visitor for Statements edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndBlockSyntax_Statements(const statement::BlockSyntax& begin, const statement::StatementSyntax& end);

      /**
      * \brief Edge  visitor for Block edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitCheckedStatementSyntax_Block(const statement::CheckedStatementSyntax& begin, const statement::BlockSyntax& end);

      /**
      * \brief Edge end visitor for Block edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndCheckedStatementSyntax_Block(const statement::CheckedStatementSyntax& begin, const statement::BlockSyntax& end);

      /**
      * \brief Edge  visitor for Condition edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitDoStatementSyntax_Condition(const statement::DoStatementSyntax& begin, const expression::ExpressionSyntax& end);

      /**
      * \brief Edge end visitor for Condition edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndDoStatementSyntax_Condition(const statement::DoStatementSyntax& begin, const expression::ExpressionSyntax& end);

      /**
      * \brief Edge  visitor for Statement edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitDoStatementSyntax_Statement(const statement::DoStatementSyntax& begin, const statement::StatementSyntax& end);

      /**
      * \brief Edge end visitor for Statement edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndDoStatementSyntax_Statement(const statement::DoStatementSyntax& begin, const statement::StatementSyntax& end);

      /**
      * \brief Edge  visitor for Expression edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitExpressionStatementSyntax_Expression(const statement::ExpressionStatementSyntax& begin, const expression::ExpressionSyntax& end);

      /**
      * \brief Edge end visitor for Expression edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndExpressionStatementSyntax_Expression(const statement::ExpressionStatementSyntax& begin, const expression::ExpressionSyntax& end);

      /**
      * \brief Edge  visitor for Declaration edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitFixedStatementSyntax_Declaration(const statement::FixedStatementSyntax& begin, const structure::VariableDeclarationSyntax& end);

      /**
      * \brief Edge end visitor for Declaration edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndFixedStatementSyntax_Declaration(const statement::FixedStatementSyntax& begin, const structure::VariableDeclarationSyntax& end);

      /**
      * \brief Edge  visitor for Statement edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitFixedStatementSyntax_Statement(const statement::FixedStatementSyntax& begin, const statement::StatementSyntax& end);

      /**
      * \brief Edge end visitor for Statement edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndFixedStatementSyntax_Statement(const statement::FixedStatementSyntax& begin, const statement::StatementSyntax& end);

      /**
      * \brief Edge  visitor for Expression edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitForEachStatementSyntax_Expression(const statement::ForEachStatementSyntax& begin, const expression::ExpressionSyntax& end);

      /**
      * \brief Edge end visitor for Expression edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndForEachStatementSyntax_Expression(const statement::ForEachStatementSyntax& begin, const expression::ExpressionSyntax& end);

      /**
      * \brief Edge  visitor for Statement edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitForEachStatementSyntax_Statement(const statement::ForEachStatementSyntax& begin, const statement::StatementSyntax& end);

      /**
      * \brief Edge end visitor for Statement edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndForEachStatementSyntax_Statement(const statement::ForEachStatementSyntax& begin, const statement::StatementSyntax& end);

      /**
      * \brief Edge  visitor for Type edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitForEachStatementSyntax_Type(const statement::ForEachStatementSyntax& begin, const expression::TypeSyntax& end);

      /**
      * \brief Edge end visitor for Type edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndForEachStatementSyntax_Type(const statement::ForEachStatementSyntax& begin, const expression::TypeSyntax& end);

      /**
      * \brief Edge  visitor for Condition edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitForStatementSyntax_Condition(const statement::ForStatementSyntax& begin, const expression::ExpressionSyntax& end);

      /**
      * \brief Edge end visitor for Condition edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndForStatementSyntax_Condition(const statement::ForStatementSyntax& begin, const expression::ExpressionSyntax& end);

      /**
      * \brief Edge  visitor for Declaration edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitForStatementSyntax_Declaration(const statement::ForStatementSyntax& begin, const structure::VariableDeclarationSyntax& end);

      /**
      * \brief Edge end visitor for Declaration edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndForStatementSyntax_Declaration(const statement::ForStatementSyntax& begin, const structure::VariableDeclarationSyntax& end);

      /**
      * \brief Edge  visitor for Incrementors edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitForStatementSyntax_Incrementors(const statement::ForStatementSyntax& begin, const expression::ExpressionSyntax& end);

      /**
      * \brief Edge end visitor for Incrementors edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndForStatementSyntax_Incrementors(const statement::ForStatementSyntax& begin, const expression::ExpressionSyntax& end);

      /**
      * \brief Edge  visitor for Initializers edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitForStatementSyntax_Initializers(const statement::ForStatementSyntax& begin, const expression::ExpressionSyntax& end);

      /**
      * \brief Edge end visitor for Initializers edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndForStatementSyntax_Initializers(const statement::ForStatementSyntax& begin, const expression::ExpressionSyntax& end);

      /**
      * \brief Edge  visitor for Statement edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitForStatementSyntax_Statement(const statement::ForStatementSyntax& begin, const statement::StatementSyntax& end);

      /**
      * \brief Edge end visitor for Statement edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndForStatementSyntax_Statement(const statement::ForStatementSyntax& begin, const statement::StatementSyntax& end);

      /**
      * \brief Edge  visitor for Expression edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitGotoStatementSyntax_Expression(const statement::GotoStatementSyntax& begin, const expression::ExpressionSyntax& end);

      /**
      * \brief Edge end visitor for Expression edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndGotoStatementSyntax_Expression(const statement::GotoStatementSyntax& begin, const expression::ExpressionSyntax& end);

      /**
      * \brief Edge  visitor for Condition edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitIfStatementSyntax_Condition(const statement::IfStatementSyntax& begin, const expression::ExpressionSyntax& end);

      /**
      * \brief Edge end visitor for Condition edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndIfStatementSyntax_Condition(const statement::IfStatementSyntax& begin, const expression::ExpressionSyntax& end);

      /**
      * \brief Edge  visitor for Else edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitIfStatementSyntax_Else(const statement::IfStatementSyntax& begin, const structure::ElseClauseSyntax& end);

      /**
      * \brief Edge end visitor for Else edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndIfStatementSyntax_Else(const statement::IfStatementSyntax& begin, const structure::ElseClauseSyntax& end);

      /**
      * \brief Edge  visitor for Statement edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitIfStatementSyntax_Statement(const statement::IfStatementSyntax& begin, const statement::StatementSyntax& end);

      /**
      * \brief Edge end visitor for Statement edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndIfStatementSyntax_Statement(const statement::IfStatementSyntax& begin, const statement::StatementSyntax& end);

      /**
      * \brief Edge  visitor for Statement edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitLabeledStatementSyntax_Statement(const statement::LabeledStatementSyntax& begin, const statement::StatementSyntax& end);

      /**
      * \brief Edge end visitor for Statement edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndLabeledStatementSyntax_Statement(const statement::LabeledStatementSyntax& begin, const statement::StatementSyntax& end);

      /**
      * \brief Edge  visitor for Declaration edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitLocalDeclarationStatementSyntax_Declaration(const statement::LocalDeclarationStatementSyntax& begin, const structure::VariableDeclarationSyntax& end);

      /**
      * \brief Edge end visitor for Declaration edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndLocalDeclarationStatementSyntax_Declaration(const statement::LocalDeclarationStatementSyntax& begin, const structure::VariableDeclarationSyntax& end);

      /**
      * \brief Edge  visitor for Expression edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitLockStatementSyntax_Expression(const statement::LockStatementSyntax& begin, const expression::ExpressionSyntax& end);

      /**
      * \brief Edge end visitor for Expression edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndLockStatementSyntax_Expression(const statement::LockStatementSyntax& begin, const expression::ExpressionSyntax& end);

      /**
      * \brief Edge  visitor for Statement edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitLockStatementSyntax_Statement(const statement::LockStatementSyntax& begin, const statement::StatementSyntax& end);

      /**
      * \brief Edge end visitor for Statement edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndLockStatementSyntax_Statement(const statement::LockStatementSyntax& begin, const statement::StatementSyntax& end);

      /**
      * \brief Edge  visitor for Expression edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitReturnStatementSyntax_Expression(const statement::ReturnStatementSyntax& begin, const expression::ExpressionSyntax& end);

      /**
      * \brief Edge end visitor for Expression edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndReturnStatementSyntax_Expression(const statement::ReturnStatementSyntax& begin, const expression::ExpressionSyntax& end);

      /**
      * \brief Edge  visitor for Expression edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitSwitchStatementSyntax_Expression(const statement::SwitchStatementSyntax& begin, const expression::ExpressionSyntax& end);

      /**
      * \brief Edge end visitor for Expression edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndSwitchStatementSyntax_Expression(const statement::SwitchStatementSyntax& begin, const expression::ExpressionSyntax& end);

      /**
      * \brief Edge  visitor for Sections edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitSwitchStatementSyntax_Sections(const statement::SwitchStatementSyntax& begin, const structure::SwitchSectionSyntax& end);

      /**
      * \brief Edge end visitor for Sections edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndSwitchStatementSyntax_Sections(const statement::SwitchStatementSyntax& begin, const structure::SwitchSectionSyntax& end);

      /**
      * \brief Edge  visitor for Expression edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitThrowStatementSyntax_Expression(const statement::ThrowStatementSyntax& begin, const expression::ExpressionSyntax& end);

      /**
      * \brief Edge end visitor for Expression edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndThrowStatementSyntax_Expression(const statement::ThrowStatementSyntax& begin, const expression::ExpressionSyntax& end);

      /**
      * \brief Edge  visitor for Block edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitTryStatementSyntax_Block(const statement::TryStatementSyntax& begin, const statement::BlockSyntax& end);

      /**
      * \brief Edge end visitor for Block edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndTryStatementSyntax_Block(const statement::TryStatementSyntax& begin, const statement::BlockSyntax& end);

      /**
      * \brief Edge  visitor for Catches edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitTryStatementSyntax_Catches(const statement::TryStatementSyntax& begin, const structure::CatchClauseSyntax& end);

      /**
      * \brief Edge end visitor for Catches edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndTryStatementSyntax_Catches(const statement::TryStatementSyntax& begin, const structure::CatchClauseSyntax& end);

      /**
      * \brief Edge  visitor for Finally edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitTryStatementSyntax_Finally(const statement::TryStatementSyntax& begin, const structure::FinallyClauseSyntax& end);

      /**
      * \brief Edge end visitor for Finally edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndTryStatementSyntax_Finally(const statement::TryStatementSyntax& begin, const structure::FinallyClauseSyntax& end);

      /**
      * \brief Edge  visitor for Block edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitUnsafeStatementSyntax_Block(const statement::UnsafeStatementSyntax& begin, const statement::BlockSyntax& end);

      /**
      * \brief Edge end visitor for Block edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndUnsafeStatementSyntax_Block(const statement::UnsafeStatementSyntax& begin, const statement::BlockSyntax& end);

      /**
      * \brief Edge  visitor for Declaration edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitUsingStatementSyntax_Declaration(const statement::UsingStatementSyntax& begin, const structure::VariableDeclarationSyntax& end);

      /**
      * \brief Edge end visitor for Declaration edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndUsingStatementSyntax_Declaration(const statement::UsingStatementSyntax& begin, const structure::VariableDeclarationSyntax& end);

      /**
      * \brief Edge  visitor for Expression edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitUsingStatementSyntax_Expression(const statement::UsingStatementSyntax& begin, const expression::ExpressionSyntax& end);

      /**
      * \brief Edge end visitor for Expression edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndUsingStatementSyntax_Expression(const statement::UsingStatementSyntax& begin, const expression::ExpressionSyntax& end);

      /**
      * \brief Edge  visitor for Statement edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitUsingStatementSyntax_Statement(const statement::UsingStatementSyntax& begin, const statement::StatementSyntax& end);

      /**
      * \brief Edge end visitor for Statement edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndUsingStatementSyntax_Statement(const statement::UsingStatementSyntax& begin, const statement::StatementSyntax& end);

      /**
      * \brief Edge  visitor for Condition edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitWhileStatementSyntax_Condition(const statement::WhileStatementSyntax& begin, const expression::ExpressionSyntax& end);

      /**
      * \brief Edge end visitor for Condition edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndWhileStatementSyntax_Condition(const statement::WhileStatementSyntax& begin, const expression::ExpressionSyntax& end);

      /**
      * \brief Edge  visitor for Statement edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitWhileStatementSyntax_Statement(const statement::WhileStatementSyntax& begin, const statement::StatementSyntax& end);

      /**
      * \brief Edge end visitor for Statement edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndWhileStatementSyntax_Statement(const statement::WhileStatementSyntax& begin, const statement::StatementSyntax& end);

      /**
      * \brief Edge  visitor for Expression edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitYieldStatementSyntax_Expression(const statement::YieldStatementSyntax& begin, const expression::ExpressionSyntax& end);

      /**
      * \brief Edge end visitor for Expression edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndYieldStatementSyntax_Expression(const statement::YieldStatementSyntax& begin, const expression::ExpressionSyntax& end);

      /**
      * \brief Edge  visitor for AttributeLists edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitAccessorDeclarationSyntax_AttributeLists(const structure::AccessorDeclarationSyntax& begin, const structure::AttributeListSyntax& end);

      /**
      * \brief Edge end visitor for AttributeLists edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndAccessorDeclarationSyntax_AttributeLists(const structure::AccessorDeclarationSyntax& begin, const structure::AttributeListSyntax& end);

      /**
      * \brief Edge  visitor for Body edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitAccessorDeclarationSyntax_Body(const structure::AccessorDeclarationSyntax& begin, const statement::BlockSyntax& end);

      /**
      * \brief Edge end visitor for Body edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndAccessorDeclarationSyntax_Body(const structure::AccessorDeclarationSyntax& begin, const statement::BlockSyntax& end);

      /**
      * \brief Edge  visitor for Accessors edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitAccessorListSyntax_Accessors(const structure::AccessorListSyntax& begin, const structure::AccessorDeclarationSyntax& end);

      /**
      * \brief Edge end visitor for Accessors edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndAccessorListSyntax_Accessors(const structure::AccessorListSyntax& begin, const structure::AccessorDeclarationSyntax& end);

      /**
      * \brief Edge  visitor for Expression edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitAnonymousObjectMemberDeclaratorSyntax_Expression(const structure::AnonymousObjectMemberDeclaratorSyntax& begin, const expression::ExpressionSyntax& end);

      /**
      * \brief Edge end visitor for Expression edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndAnonymousObjectMemberDeclaratorSyntax_Expression(const structure::AnonymousObjectMemberDeclaratorSyntax& begin, const expression::ExpressionSyntax& end);

      /**
      * \brief Edge  visitor for NameEquals edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitAnonymousObjectMemberDeclaratorSyntax_NameEquals(const structure::AnonymousObjectMemberDeclaratorSyntax& begin, const structure::NameEqualsSyntax& end);

      /**
      * \brief Edge end visitor for NameEquals edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndAnonymousObjectMemberDeclaratorSyntax_NameEquals(const structure::AnonymousObjectMemberDeclaratorSyntax& begin, const structure::NameEqualsSyntax& end);

      /**
      * \brief Edge  visitor for Expression edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitArgumentSyntax_Expression(const structure::ArgumentSyntax& begin, const expression::ExpressionSyntax& end);

      /**
      * \brief Edge end visitor for Expression edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndArgumentSyntax_Expression(const structure::ArgumentSyntax& begin, const expression::ExpressionSyntax& end);

      /**
      * \brief Edge  visitor for NameColon edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitArgumentSyntax_NameColon(const structure::ArgumentSyntax& begin, const structure::NameColonSyntax& end);

      /**
      * \brief Edge end visitor for NameColon edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndArgumentSyntax_NameColon(const structure::ArgumentSyntax& begin, const structure::NameColonSyntax& end);

      /**
      * \brief Edge  visitor for Sizes edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitArrayRankSpecifierSyntax_Sizes(const structure::ArrayRankSpecifierSyntax& begin, const expression::ExpressionSyntax& end);

      /**
      * \brief Edge end visitor for Sizes edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndArrayRankSpecifierSyntax_Sizes(const structure::ArrayRankSpecifierSyntax& begin, const expression::ExpressionSyntax& end);

      /**
      * \brief Edge  visitor for Expression edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitArrowExpressionClauseSyntax_Expression(const structure::ArrowExpressionClauseSyntax& begin, const expression::ExpressionSyntax& end);

      /**
      * \brief Edge end visitor for Expression edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndArrowExpressionClauseSyntax_Expression(const structure::ArrowExpressionClauseSyntax& begin, const expression::ExpressionSyntax& end);

      /**
      * \brief Edge  visitor for Arguments edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitAttributeArgumentListSyntax_Arguments(const structure::AttributeArgumentListSyntax& begin, const structure::AttributeArgumentSyntax& end);

      /**
      * \brief Edge end visitor for Arguments edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndAttributeArgumentListSyntax_Arguments(const structure::AttributeArgumentListSyntax& begin, const structure::AttributeArgumentSyntax& end);

      /**
      * \brief Edge  visitor for Expression edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitAttributeArgumentSyntax_Expression(const structure::AttributeArgumentSyntax& begin, const expression::ExpressionSyntax& end);

      /**
      * \brief Edge end visitor for Expression edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndAttributeArgumentSyntax_Expression(const structure::AttributeArgumentSyntax& begin, const expression::ExpressionSyntax& end);

      /**
      * \brief Edge  visitor for NameColon edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitAttributeArgumentSyntax_NameColon(const structure::AttributeArgumentSyntax& begin, const structure::NameColonSyntax& end);

      /**
      * \brief Edge end visitor for NameColon edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndAttributeArgumentSyntax_NameColon(const structure::AttributeArgumentSyntax& begin, const structure::NameColonSyntax& end);

      /**
      * \brief Edge  visitor for NameEquals edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitAttributeArgumentSyntax_NameEquals(const structure::AttributeArgumentSyntax& begin, const structure::NameEqualsSyntax& end);

      /**
      * \brief Edge end visitor for NameEquals edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndAttributeArgumentSyntax_NameEquals(const structure::AttributeArgumentSyntax& begin, const structure::NameEqualsSyntax& end);

      /**
      * \brief Edge  visitor for Attributes edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitAttributeListSyntax_Attributes(const structure::AttributeListSyntax& begin, const structure::AttributeSyntax& end);

      /**
      * \brief Edge end visitor for Attributes edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndAttributeListSyntax_Attributes(const structure::AttributeListSyntax& begin, const structure::AttributeSyntax& end);

      /**
      * \brief Edge  visitor for Target edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitAttributeListSyntax_Target(const structure::AttributeListSyntax& begin, const structure::AttributeTargetSpecifierSyntax& end);

      /**
      * \brief Edge end visitor for Target edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndAttributeListSyntax_Target(const structure::AttributeListSyntax& begin, const structure::AttributeTargetSpecifierSyntax& end);

      /**
      * \brief Edge  visitor for ArgumentList edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitAttributeSyntax_ArgumentList(const structure::AttributeSyntax& begin, const structure::AttributeArgumentListSyntax& end);

      /**
      * \brief Edge end visitor for ArgumentList edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndAttributeSyntax_ArgumentList(const structure::AttributeSyntax& begin, const structure::AttributeArgumentListSyntax& end);

      /**
      * \brief Edge  visitor for Name edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitAttributeSyntax_Name(const structure::AttributeSyntax& begin, const expression::NameSyntax& end);

      /**
      * \brief Edge end visitor for Name edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndAttributeSyntax_Name(const structure::AttributeSyntax& begin, const expression::NameSyntax& end);

      /**
      * \brief Edge  visitor for Arguments edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitBaseArgumentListSyntax_Arguments(const structure::BaseArgumentListSyntax& begin, const structure::ArgumentSyntax& end);

      /**
      * \brief Edge end visitor for Arguments edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndBaseArgumentListSyntax_Arguments(const structure::BaseArgumentListSyntax& begin, const structure::ArgumentSyntax& end);

      /**
      * \brief Edge  visitor for Parameters edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitBaseCrefParameterListSyntax_Parameters(const structure::BaseCrefParameterListSyntax& begin, const structure::CrefParameterSyntax& end);

      /**
      * \brief Edge end visitor for Parameters edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndBaseCrefParameterListSyntax_Parameters(const structure::BaseCrefParameterListSyntax& begin, const structure::CrefParameterSyntax& end);

      /**
      * \brief Edge  visitor for AttributeLists edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitBaseFieldDeclarationSyntax_AttributeLists(const structure::BaseFieldDeclarationSyntax& begin, const structure::AttributeListSyntax& end);

      /**
      * \brief Edge end visitor for AttributeLists edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndBaseFieldDeclarationSyntax_AttributeLists(const structure::BaseFieldDeclarationSyntax& begin, const structure::AttributeListSyntax& end);

      /**
      * \brief Edge  visitor for Declaration edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitBaseFieldDeclarationSyntax_Declaration(const structure::BaseFieldDeclarationSyntax& begin, const structure::VariableDeclarationSyntax& end);

      /**
      * \brief Edge end visitor for Declaration edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndBaseFieldDeclarationSyntax_Declaration(const structure::BaseFieldDeclarationSyntax& begin, const structure::VariableDeclarationSyntax& end);

      /**
      * \brief Edge  visitor for Types edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitBaseListSyntax_Types(const structure::BaseListSyntax& begin, const structure::BaseTypeSyntax& end);

      /**
      * \brief Edge end visitor for Types edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndBaseListSyntax_Types(const structure::BaseListSyntax& begin, const structure::BaseTypeSyntax& end);

      /**
      * \brief Edge visitor for AccessedEnumMembers edge which.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitBaseMethodDeclarationSyntax_AccessedEnumMembers(const structure::BaseMethodDeclarationSyntax& begin, const structure::EnumMemberDeclarationSyntax& end);

      /**
      * \brief Edge visitor for AccessedEnumMembers edge which.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndBaseMethodDeclarationSyntax_AccessedEnumMembers(const structure::BaseMethodDeclarationSyntax& begin, const structure::EnumMemberDeclarationSyntax& end);

      /**
      * \brief Edge  visitor for AttributeLists edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitBaseMethodDeclarationSyntax_AttributeLists(const structure::BaseMethodDeclarationSyntax& begin, const structure::AttributeListSyntax& end);

      /**
      * \brief Edge end visitor for AttributeLists edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndBaseMethodDeclarationSyntax_AttributeLists(const structure::BaseMethodDeclarationSyntax& begin, const structure::AttributeListSyntax& end);

      /**
      * \brief Edge  visitor for Body edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitBaseMethodDeclarationSyntax_Body(const structure::BaseMethodDeclarationSyntax& begin, const statement::BlockSyntax& end);

      /**
      * \brief Edge end visitor for Body edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndBaseMethodDeclarationSyntax_Body(const structure::BaseMethodDeclarationSyntax& begin, const statement::BlockSyntax& end);

      /**
      * \brief Edge  visitor for ParameterList edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitBaseMethodDeclarationSyntax_ParameterList(const structure::BaseMethodDeclarationSyntax& begin, const structure::ParameterListSyntax& end);

      /**
      * \brief Edge end visitor for ParameterList edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndBaseMethodDeclarationSyntax_ParameterList(const structure::BaseMethodDeclarationSyntax& begin, const structure::ParameterListSyntax& end);

      /**
      * \brief Edge  visitor for Parameters edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitBaseParameterListSyntax_Parameters(const structure::BaseParameterListSyntax& begin, const structure::ParameterSyntax& end);

      /**
      * \brief Edge end visitor for Parameters edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndBaseParameterListSyntax_Parameters(const structure::BaseParameterListSyntax& begin, const structure::ParameterSyntax& end);

      /**
      * \brief Edge  visitor for AccessorList edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitBasePropertyDeclarationSyntax_AccessorList(const structure::BasePropertyDeclarationSyntax& begin, const structure::AccessorListSyntax& end);

      /**
      * \brief Edge end visitor for AccessorList edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndBasePropertyDeclarationSyntax_AccessorList(const structure::BasePropertyDeclarationSyntax& begin, const structure::AccessorListSyntax& end);

      /**
      * \brief Edge  visitor for AttributeLists edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitBasePropertyDeclarationSyntax_AttributeLists(const structure::BasePropertyDeclarationSyntax& begin, const structure::AttributeListSyntax& end);

      /**
      * \brief Edge end visitor for AttributeLists edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndBasePropertyDeclarationSyntax_AttributeLists(const structure::BasePropertyDeclarationSyntax& begin, const structure::AttributeListSyntax& end);

      /**
      * \brief Edge  visitor for ExplicitInterfaceSpecifier edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitBasePropertyDeclarationSyntax_ExplicitInterfaceSpecifier(const structure::BasePropertyDeclarationSyntax& begin, const structure::ExplicitInterfaceSpecifierSyntax& end);

      /**
      * \brief Edge end visitor for ExplicitInterfaceSpecifier edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndBasePropertyDeclarationSyntax_ExplicitInterfaceSpecifier(const structure::BasePropertyDeclarationSyntax& begin, const structure::ExplicitInterfaceSpecifierSyntax& end);

      /**
      * \brief Edge  visitor for Type edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitBasePropertyDeclarationSyntax_Type(const structure::BasePropertyDeclarationSyntax& begin, const expression::TypeSyntax& end);

      /**
      * \brief Edge end visitor for Type edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndBasePropertyDeclarationSyntax_Type(const structure::BasePropertyDeclarationSyntax& begin, const expression::TypeSyntax& end);

      /**
      * \brief Edge  visitor for AttributeLists edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitBaseTypeDeclarationSyntax_AttributeLists(const structure::BaseTypeDeclarationSyntax& begin, const structure::AttributeListSyntax& end);

      /**
      * \brief Edge end visitor for AttributeLists edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndBaseTypeDeclarationSyntax_AttributeLists(const structure::BaseTypeDeclarationSyntax& begin, const structure::AttributeListSyntax& end);

      /**
      * \brief Edge  visitor for BaseList edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitBaseTypeDeclarationSyntax_BaseList(const structure::BaseTypeDeclarationSyntax& begin, const structure::BaseListSyntax& end);

      /**
      * \brief Edge end visitor for BaseList edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndBaseTypeDeclarationSyntax_BaseList(const structure::BaseTypeDeclarationSyntax& begin, const structure::BaseListSyntax& end);

      /**
      * \brief Edge  visitor for Type edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitBaseTypeSyntax_Type(const structure::BaseTypeSyntax& begin, const expression::TypeSyntax& end);

      /**
      * \brief Edge end visitor for Type edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndBaseTypeSyntax_Type(const structure::BaseTypeSyntax& begin, const expression::TypeSyntax& end);

      /**
      * \brief Edge  visitor for Value edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitCaseSwitchLabelSyntax_Value(const structure::CaseSwitchLabelSyntax& begin, const expression::ExpressionSyntax& end);

      /**
      * \brief Edge end visitor for Value edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndCaseSwitchLabelSyntax_Value(const structure::CaseSwitchLabelSyntax& begin, const expression::ExpressionSyntax& end);

      /**
      * \brief Edge  visitor for Block edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitCatchClauseSyntax_Block(const structure::CatchClauseSyntax& begin, const statement::BlockSyntax& end);

      /**
      * \brief Edge end visitor for Block edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndCatchClauseSyntax_Block(const structure::CatchClauseSyntax& begin, const statement::BlockSyntax& end);

      /**
      * \brief Edge  visitor for Declaration edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitCatchClauseSyntax_Declaration(const structure::CatchClauseSyntax& begin, const structure::CatchDeclarationSyntax& end);

      /**
      * \brief Edge end visitor for Declaration edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndCatchClauseSyntax_Declaration(const structure::CatchClauseSyntax& begin, const structure::CatchDeclarationSyntax& end);

      /**
      * \brief Edge  visitor for Filter edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitCatchClauseSyntax_Filter(const structure::CatchClauseSyntax& begin, const structure::CatchFilterClauseSyntax& end);

      /**
      * \brief Edge end visitor for Filter edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndCatchClauseSyntax_Filter(const structure::CatchClauseSyntax& begin, const structure::CatchFilterClauseSyntax& end);

      /**
      * \brief Edge  visitor for Type edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitCatchDeclarationSyntax_Type(const structure::CatchDeclarationSyntax& begin, const expression::TypeSyntax& end);

      /**
      * \brief Edge end visitor for Type edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndCatchDeclarationSyntax_Type(const structure::CatchDeclarationSyntax& begin, const expression::TypeSyntax& end);

      /**
      * \brief Edge  visitor for FilterExpression edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitCatchFilterClauseSyntax_FilterExpression(const structure::CatchFilterClauseSyntax& begin, const expression::ExpressionSyntax& end);

      /**
      * \brief Edge end visitor for FilterExpression edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndCatchFilterClauseSyntax_FilterExpression(const structure::CatchFilterClauseSyntax& begin, const expression::ExpressionSyntax& end);

      /**
      * \brief Edge  visitor for AttributeLists edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitCompilationUnitSyntax_AttributeLists(const structure::CompilationUnitSyntax& begin, const structure::AttributeListSyntax& end);

      /**
      * \brief Edge end visitor for AttributeLists edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndCompilationUnitSyntax_AttributeLists(const structure::CompilationUnitSyntax& begin, const structure::AttributeListSyntax& end);

      /**
      * \brief Edge  visitor for Externs edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitCompilationUnitSyntax_Externs(const structure::CompilationUnitSyntax& begin, const structure::ExternAliasDirectiveSyntax& end);

      /**
      * \brief Edge end visitor for Externs edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndCompilationUnitSyntax_Externs(const structure::CompilationUnitSyntax& begin, const structure::ExternAliasDirectiveSyntax& end);

      /**
      * \brief Edge  visitor for Members edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitCompilationUnitSyntax_Members(const structure::CompilationUnitSyntax& begin, const structure::MemberDeclarationSyntax& end);

      /**
      * \brief Edge end visitor for Members edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndCompilationUnitSyntax_Members(const structure::CompilationUnitSyntax& begin, const structure::MemberDeclarationSyntax& end);

      /**
      * \brief Edge  visitor for Usings edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitCompilationUnitSyntax_Usings(const structure::CompilationUnitSyntax& begin, const structure::UsingDirectiveSyntax& end);

      /**
      * \brief Edge end visitor for Usings edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndCompilationUnitSyntax_Usings(const structure::CompilationUnitSyntax& begin, const structure::UsingDirectiveSyntax& end);

      /**
      * \brief Edge  visitor for Initializer edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitConstructorDeclarationSyntax_Initializer(const structure::ConstructorDeclarationSyntax& begin, const structure::ConstructorInitializerSyntax& end);

      /**
      * \brief Edge end visitor for Initializer edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndConstructorDeclarationSyntax_Initializer(const structure::ConstructorDeclarationSyntax& begin, const structure::ConstructorInitializerSyntax& end);

      /**
      * \brief Edge  visitor for ArgumentList edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitConstructorInitializerSyntax_ArgumentList(const structure::ConstructorInitializerSyntax& begin, const structure::ArgumentListSyntax& end);

      /**
      * \brief Edge end visitor for ArgumentList edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndConstructorInitializerSyntax_ArgumentList(const structure::ConstructorInitializerSyntax& begin, const structure::ArgumentListSyntax& end);

      /**
      * \brief Edge visitor for ConstructorCall edge which.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitConstructorInitializerSyntax_ConstructorCall(const structure::ConstructorInitializerSyntax& begin, const structure::ConstructorDeclarationSyntax& end);

      /**
      * \brief Edge visitor for ConstructorCall edge which.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndConstructorInitializerSyntax_ConstructorCall(const structure::ConstructorInitializerSyntax& begin, const structure::ConstructorDeclarationSyntax& end);

      /**
      * \brief Edge  visitor for ExpressionBody edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitConversionOperatorDeclarationSyntax_ExpressionBody(const structure::ConversionOperatorDeclarationSyntax& begin, const structure::ArrowExpressionClauseSyntax& end);

      /**
      * \brief Edge end visitor for ExpressionBody edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndConversionOperatorDeclarationSyntax_ExpressionBody(const structure::ConversionOperatorDeclarationSyntax& begin, const structure::ArrowExpressionClauseSyntax& end);

      /**
      * \brief Edge  visitor for Type edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitConversionOperatorDeclarationSyntax_Type(const structure::ConversionOperatorDeclarationSyntax& begin, const expression::TypeSyntax& end);

      /**
      * \brief Edge end visitor for Type edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndConversionOperatorDeclarationSyntax_Type(const structure::ConversionOperatorDeclarationSyntax& begin, const expression::TypeSyntax& end);

      /**
      * \brief Edge  visitor for Parameters edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitConversionOperatorMemberCrefSyntax_Parameters(const structure::ConversionOperatorMemberCrefSyntax& begin, const structure::CrefParameterListSyntax& end);

      /**
      * \brief Edge end visitor for Parameters edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndConversionOperatorMemberCrefSyntax_Parameters(const structure::ConversionOperatorMemberCrefSyntax& begin, const structure::CrefParameterListSyntax& end);

      /**
      * \brief Edge  visitor for Type edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitConversionOperatorMemberCrefSyntax_Type(const structure::ConversionOperatorMemberCrefSyntax& begin, const expression::TypeSyntax& end);

      /**
      * \brief Edge end visitor for Type edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndConversionOperatorMemberCrefSyntax_Type(const structure::ConversionOperatorMemberCrefSyntax& begin, const expression::TypeSyntax& end);

      /**
      * \brief Edge  visitor for Type edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitCrefParameterSyntax_Type(const structure::CrefParameterSyntax& begin, const expression::TypeSyntax& end);

      /**
      * \brief Edge end visitor for Type edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndCrefParameterSyntax_Type(const structure::CrefParameterSyntax& begin, const expression::TypeSyntax& end);

      /**
      * \brief Edge  visitor for AttributeLists edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitDelegateDeclarationSyntax_AttributeLists(const structure::DelegateDeclarationSyntax& begin, const structure::AttributeListSyntax& end);

      /**
      * \brief Edge end visitor for AttributeLists edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndDelegateDeclarationSyntax_AttributeLists(const structure::DelegateDeclarationSyntax& begin, const structure::AttributeListSyntax& end);

      /**
      * \brief Edge  visitor for ConstraintClauses edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitDelegateDeclarationSyntax_ConstraintClauses(const structure::DelegateDeclarationSyntax& begin, const structure::TypeParameterConstraintClauseSyntax& end);

      /**
      * \brief Edge end visitor for ConstraintClauses edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndDelegateDeclarationSyntax_ConstraintClauses(const structure::DelegateDeclarationSyntax& begin, const structure::TypeParameterConstraintClauseSyntax& end);

      /**
      * \brief Edge  visitor for ParameterList edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitDelegateDeclarationSyntax_ParameterList(const structure::DelegateDeclarationSyntax& begin, const structure::ParameterListSyntax& end);

      /**
      * \brief Edge end visitor for ParameterList edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndDelegateDeclarationSyntax_ParameterList(const structure::DelegateDeclarationSyntax& begin, const structure::ParameterListSyntax& end);

      /**
      * \brief Edge  visitor for ReturnType edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitDelegateDeclarationSyntax_ReturnType(const structure::DelegateDeclarationSyntax& begin, const expression::TypeSyntax& end);

      /**
      * \brief Edge end visitor for ReturnType edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndDelegateDeclarationSyntax_ReturnType(const structure::DelegateDeclarationSyntax& begin, const expression::TypeSyntax& end);

      /**
      * \brief Edge  visitor for Statement edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitElseClauseSyntax_Statement(const structure::ElseClauseSyntax& begin, const statement::StatementSyntax& end);

      /**
      * \brief Edge end visitor for Statement edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndElseClauseSyntax_Statement(const structure::ElseClauseSyntax& begin, const statement::StatementSyntax& end);

      /**
      * \brief Edge  visitor for Members edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEnumDeclarationSyntax_Members(const structure::EnumDeclarationSyntax& begin, const structure::EnumMemberDeclarationSyntax& end);

      /**
      * \brief Edge end visitor for Members edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndEnumDeclarationSyntax_Members(const structure::EnumDeclarationSyntax& begin, const structure::EnumMemberDeclarationSyntax& end);

      /**
      * \brief Edge  visitor for AttributeLists edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEnumMemberDeclarationSyntax_AttributeLists(const structure::EnumMemberDeclarationSyntax& begin, const structure::AttributeListSyntax& end);

      /**
      * \brief Edge end visitor for AttributeLists edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndEnumMemberDeclarationSyntax_AttributeLists(const structure::EnumMemberDeclarationSyntax& begin, const structure::AttributeListSyntax& end);

      /**
      * \brief Edge  visitor for EqualsValue edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEnumMemberDeclarationSyntax_EqualsValue(const structure::EnumMemberDeclarationSyntax& begin, const structure::EqualsValueClauseSyntax& end);

      /**
      * \brief Edge end visitor for EqualsValue edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndEnumMemberDeclarationSyntax_EqualsValue(const structure::EnumMemberDeclarationSyntax& begin, const structure::EqualsValueClauseSyntax& end);

      /**
      * \brief Edge  visitor for Value edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEqualsValueClauseSyntax_Value(const structure::EqualsValueClauseSyntax& begin, const expression::ExpressionSyntax& end);

      /**
      * \brief Edge end visitor for Value edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndEqualsValueClauseSyntax_Value(const structure::EqualsValueClauseSyntax& begin, const expression::ExpressionSyntax& end);

      /**
      * \brief Edge  visitor for Name edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitExplicitInterfaceSpecifierSyntax_Name(const structure::ExplicitInterfaceSpecifierSyntax& begin, const expression::NameSyntax& end);

      /**
      * \brief Edge end visitor for Name edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndExplicitInterfaceSpecifierSyntax_Name(const structure::ExplicitInterfaceSpecifierSyntax& begin, const expression::NameSyntax& end);

      /**
      * \brief Edge  visitor for Block edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitFinallyClauseSyntax_Block(const structure::FinallyClauseSyntax& begin, const statement::BlockSyntax& end);

      /**
      * \brief Edge end visitor for Block edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndFinallyClauseSyntax_Block(const structure::FinallyClauseSyntax& begin, const statement::BlockSyntax& end);

      /**
      * \brief Edge  visitor for Expression edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitFromClauseSyntax_Expression(const structure::FromClauseSyntax& begin, const expression::ExpressionSyntax& end);

      /**
      * \brief Edge end visitor for Expression edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndFromClauseSyntax_Expression(const structure::FromClauseSyntax& begin, const expression::ExpressionSyntax& end);

      /**
      * \brief Edge  visitor for Type edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitFromClauseSyntax_Type(const structure::FromClauseSyntax& begin, const expression::TypeSyntax& end);

      /**
      * \brief Edge end visitor for Type edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndFromClauseSyntax_Type(const structure::FromClauseSyntax& begin, const expression::TypeSyntax& end);

      /**
      * \brief Edge  visitor for Statement edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitGlobalStatementSyntax_Statement(const structure::GlobalStatementSyntax& begin, const statement::StatementSyntax& end);

      /**
      * \brief Edge end visitor for Statement edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndGlobalStatementSyntax_Statement(const structure::GlobalStatementSyntax& begin, const statement::StatementSyntax& end);

      /**
      * \brief Edge  visitor for ByExpression edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitGroupClauseSyntax_ByExpression(const structure::GroupClauseSyntax& begin, const expression::ExpressionSyntax& end);

      /**
      * \brief Edge end visitor for ByExpression edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndGroupClauseSyntax_ByExpression(const structure::GroupClauseSyntax& begin, const expression::ExpressionSyntax& end);

      /**
      * \brief Edge  visitor for GroupExpression edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitGroupClauseSyntax_GroupExpression(const structure::GroupClauseSyntax& begin, const expression::ExpressionSyntax& end);

      /**
      * \brief Edge end visitor for GroupExpression edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndGroupClauseSyntax_GroupExpression(const structure::GroupClauseSyntax& begin, const expression::ExpressionSyntax& end);

      /**
      * \brief Edge  visitor for AttributeLists edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitIncompleteMemberSyntax_AttributeLists(const structure::IncompleteMemberSyntax& begin, const structure::AttributeListSyntax& end);

      /**
      * \brief Edge end visitor for AttributeLists edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndIncompleteMemberSyntax_AttributeLists(const structure::IncompleteMemberSyntax& begin, const structure::AttributeListSyntax& end);

      /**
      * \brief Edge  visitor for Type edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitIncompleteMemberSyntax_Type(const structure::IncompleteMemberSyntax& begin, const expression::TypeSyntax& end);

      /**
      * \brief Edge end visitor for Type edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndIncompleteMemberSyntax_Type(const structure::IncompleteMemberSyntax& begin, const expression::TypeSyntax& end);

      /**
      * \brief Edge  visitor for ExpressionBody edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitIndexerDeclarationSyntax_ExpressionBody(const structure::IndexerDeclarationSyntax& begin, const structure::ArrowExpressionClauseSyntax& end);

      /**
      * \brief Edge end visitor for ExpressionBody edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndIndexerDeclarationSyntax_ExpressionBody(const structure::IndexerDeclarationSyntax& begin, const structure::ArrowExpressionClauseSyntax& end);

      /**
      * \brief Edge  visitor for ParameterList edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitIndexerDeclarationSyntax_ParameterList(const structure::IndexerDeclarationSyntax& begin, const structure::BracketedParameterListSyntax& end);

      /**
      * \brief Edge end visitor for ParameterList edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndIndexerDeclarationSyntax_ParameterList(const structure::IndexerDeclarationSyntax& begin, const structure::BracketedParameterListSyntax& end);

      /**
      * \brief Edge  visitor for Parameters edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitIndexerMemberCrefSyntax_Parameters(const structure::IndexerMemberCrefSyntax& begin, const structure::CrefBracketedParameterListSyntax& end);

      /**
      * \brief Edge end visitor for Parameters edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndIndexerMemberCrefSyntax_Parameters(const structure::IndexerMemberCrefSyntax& begin, const structure::CrefBracketedParameterListSyntax& end);

      /**
      * \brief Edge  visitor for Value edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitInterpolationAlignmentClauseSyntax_Value(const structure::InterpolationAlignmentClauseSyntax& begin, const expression::ExpressionSyntax& end);

      /**
      * \brief Edge end visitor for Value edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndInterpolationAlignmentClauseSyntax_Value(const structure::InterpolationAlignmentClauseSyntax& begin, const expression::ExpressionSyntax& end);

      /**
      * \brief Edge  visitor for AlignmentClause edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitInterpolationSyntax_AlignmentClause(const structure::InterpolationSyntax& begin, const structure::InterpolationAlignmentClauseSyntax& end);

      /**
      * \brief Edge end visitor for AlignmentClause edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndInterpolationSyntax_AlignmentClause(const structure::InterpolationSyntax& begin, const structure::InterpolationAlignmentClauseSyntax& end);

      /**
      * \brief Edge  visitor for Expression edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitInterpolationSyntax_Expression(const structure::InterpolationSyntax& begin, const expression::ExpressionSyntax& end);

      /**
      * \brief Edge end visitor for Expression edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndInterpolationSyntax_Expression(const structure::InterpolationSyntax& begin, const expression::ExpressionSyntax& end);

      /**
      * \brief Edge  visitor for FormatClause edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitInterpolationSyntax_FormatClause(const structure::InterpolationSyntax& begin, const structure::InterpolationFormatClauseSyntax& end);

      /**
      * \brief Edge end visitor for FormatClause edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndInterpolationSyntax_FormatClause(const structure::InterpolationSyntax& begin, const structure::InterpolationFormatClauseSyntax& end);

      /**
      * \brief Edge  visitor for InExpression edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitJoinClauseSyntax_InExpression(const structure::JoinClauseSyntax& begin, const expression::ExpressionSyntax& end);

      /**
      * \brief Edge end visitor for InExpression edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndJoinClauseSyntax_InExpression(const structure::JoinClauseSyntax& begin, const expression::ExpressionSyntax& end);

      /**
      * \brief Edge  visitor for Into edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitJoinClauseSyntax_Into(const structure::JoinClauseSyntax& begin, const structure::JoinIntoClauseSyntax& end);

      /**
      * \brief Edge end visitor for Into edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndJoinClauseSyntax_Into(const structure::JoinClauseSyntax& begin, const structure::JoinIntoClauseSyntax& end);

      /**
      * \brief Edge  visitor for LeftExpression edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitJoinClauseSyntax_LeftExpression(const structure::JoinClauseSyntax& begin, const expression::ExpressionSyntax& end);

      /**
      * \brief Edge end visitor for LeftExpression edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndJoinClauseSyntax_LeftExpression(const structure::JoinClauseSyntax& begin, const expression::ExpressionSyntax& end);

      /**
      * \brief Edge  visitor for RightExpression edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitJoinClauseSyntax_RightExpression(const structure::JoinClauseSyntax& begin, const expression::ExpressionSyntax& end);

      /**
      * \brief Edge end visitor for RightExpression edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndJoinClauseSyntax_RightExpression(const structure::JoinClauseSyntax& begin, const expression::ExpressionSyntax& end);

      /**
      * \brief Edge  visitor for Type edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitJoinClauseSyntax_Type(const structure::JoinClauseSyntax& begin, const expression::TypeSyntax& end);

      /**
      * \brief Edge end visitor for Type edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndJoinClauseSyntax_Type(const structure::JoinClauseSyntax& begin, const expression::TypeSyntax& end);

      /**
      * \brief Edge  visitor for Expression edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitLetClauseSyntax_Expression(const structure::LetClauseSyntax& begin, const expression::ExpressionSyntax& end);

      /**
      * \brief Edge end visitor for Expression edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndLetClauseSyntax_Expression(const structure::LetClauseSyntax& begin, const expression::ExpressionSyntax& end);

      /**
      * \brief Edge  visitor for ConstraintClauses edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitMethodDeclarationSyntax_ConstraintClauses(const structure::MethodDeclarationSyntax& begin, const structure::TypeParameterConstraintClauseSyntax& end);

      /**
      * \brief Edge end visitor for ConstraintClauses edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndMethodDeclarationSyntax_ConstraintClauses(const structure::MethodDeclarationSyntax& begin, const structure::TypeParameterConstraintClauseSyntax& end);

      /**
      * \brief Edge  visitor for ExplicitInterfaceSpecifier edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitMethodDeclarationSyntax_ExplicitInterfaceSpecifier(const structure::MethodDeclarationSyntax& begin, const structure::ExplicitInterfaceSpecifierSyntax& end);

      /**
      * \brief Edge end visitor for ExplicitInterfaceSpecifier edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndMethodDeclarationSyntax_ExplicitInterfaceSpecifier(const structure::MethodDeclarationSyntax& begin, const structure::ExplicitInterfaceSpecifierSyntax& end);

      /**
      * \brief Edge  visitor for ExpressionBody edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitMethodDeclarationSyntax_ExpressionBody(const structure::MethodDeclarationSyntax& begin, const structure::ArrowExpressionClauseSyntax& end);

      /**
      * \brief Edge end visitor for ExpressionBody edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndMethodDeclarationSyntax_ExpressionBody(const structure::MethodDeclarationSyntax& begin, const structure::ArrowExpressionClauseSyntax& end);

      /**
      * \brief Edge  visitor for ReturnType edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitMethodDeclarationSyntax_ReturnType(const structure::MethodDeclarationSyntax& begin, const expression::TypeSyntax& end);

      /**
      * \brief Edge end visitor for ReturnType edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndMethodDeclarationSyntax_ReturnType(const structure::MethodDeclarationSyntax& begin, const expression::TypeSyntax& end);

      /**
      * \brief Edge  visitor for Name edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitNameColonSyntax_Name(const structure::NameColonSyntax& begin, const expression::IdentifierNameSyntax& end);

      /**
      * \brief Edge end visitor for Name edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndNameColonSyntax_Name(const structure::NameColonSyntax& begin, const expression::IdentifierNameSyntax& end);

      /**
      * \brief Edge  visitor for Name edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitNameEqualsSyntax_Name(const structure::NameEqualsSyntax& begin, const expression::IdentifierNameSyntax& end);

      /**
      * \brief Edge end visitor for Name edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndNameEqualsSyntax_Name(const structure::NameEqualsSyntax& begin, const expression::IdentifierNameSyntax& end);

      /**
      * \brief Edge  visitor for Name edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitNameMemberCrefSyntax_Name(const structure::NameMemberCrefSyntax& begin, const expression::TypeSyntax& end);

      /**
      * \brief Edge end visitor for Name edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndNameMemberCrefSyntax_Name(const structure::NameMemberCrefSyntax& begin, const expression::TypeSyntax& end);

      /**
      * \brief Edge  visitor for Parameters edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitNameMemberCrefSyntax_Parameters(const structure::NameMemberCrefSyntax& begin, const structure::CrefParameterListSyntax& end);

      /**
      * \brief Edge end visitor for Parameters edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndNameMemberCrefSyntax_Parameters(const structure::NameMemberCrefSyntax& begin, const structure::CrefParameterListSyntax& end);

      /**
      * \brief Edge  visitor for Externs edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitNamespaceDeclarationSyntax_Externs(const structure::NamespaceDeclarationSyntax& begin, const structure::ExternAliasDirectiveSyntax& end);

      /**
      * \brief Edge end visitor for Externs edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndNamespaceDeclarationSyntax_Externs(const structure::NamespaceDeclarationSyntax& begin, const structure::ExternAliasDirectiveSyntax& end);

      /**
      * \brief Edge  visitor for Members edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitNamespaceDeclarationSyntax_Members(const structure::NamespaceDeclarationSyntax& begin, const structure::MemberDeclarationSyntax& end);

      /**
      * \brief Edge end visitor for Members edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndNamespaceDeclarationSyntax_Members(const structure::NamespaceDeclarationSyntax& begin, const structure::MemberDeclarationSyntax& end);

      /**
      * \brief Edge  visitor for Name edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitNamespaceDeclarationSyntax_Name(const structure::NamespaceDeclarationSyntax& begin, const expression::NameSyntax& end);

      /**
      * \brief Edge end visitor for Name edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndNamespaceDeclarationSyntax_Name(const structure::NamespaceDeclarationSyntax& begin, const expression::NameSyntax& end);

      /**
      * \brief Edge  visitor for Usings edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitNamespaceDeclarationSyntax_Usings(const structure::NamespaceDeclarationSyntax& begin, const structure::UsingDirectiveSyntax& end);

      /**
      * \brief Edge end visitor for Usings edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndNamespaceDeclarationSyntax_Usings(const structure::NamespaceDeclarationSyntax& begin, const structure::UsingDirectiveSyntax& end);

      /**
      * \brief Edge  visitor for ExpressionBody edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitOperatorDeclarationSyntax_ExpressionBody(const structure::OperatorDeclarationSyntax& begin, const structure::ArrowExpressionClauseSyntax& end);

      /**
      * \brief Edge end visitor for ExpressionBody edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndOperatorDeclarationSyntax_ExpressionBody(const structure::OperatorDeclarationSyntax& begin, const structure::ArrowExpressionClauseSyntax& end);

      /**
      * \brief Edge  visitor for ReturnType edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitOperatorDeclarationSyntax_ReturnType(const structure::OperatorDeclarationSyntax& begin, const expression::TypeSyntax& end);

      /**
      * \brief Edge end visitor for ReturnType edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndOperatorDeclarationSyntax_ReturnType(const structure::OperatorDeclarationSyntax& begin, const expression::TypeSyntax& end);

      /**
      * \brief Edge  visitor for Parameters edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitOperatorMemberCrefSyntax_Parameters(const structure::OperatorMemberCrefSyntax& begin, const structure::CrefParameterListSyntax& end);

      /**
      * \brief Edge end visitor for Parameters edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndOperatorMemberCrefSyntax_Parameters(const structure::OperatorMemberCrefSyntax& begin, const structure::CrefParameterListSyntax& end);

      /**
      * \brief Edge  visitor for Orderings edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitOrderByClauseSyntax_Orderings(const structure::OrderByClauseSyntax& begin, const structure::OrderingSyntax& end);

      /**
      * \brief Edge end visitor for Orderings edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndOrderByClauseSyntax_Orderings(const structure::OrderByClauseSyntax& begin, const structure::OrderingSyntax& end);

      /**
      * \brief Edge  visitor for Expression edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitOrderingSyntax_Expression(const structure::OrderingSyntax& begin, const expression::ExpressionSyntax& end);

      /**
      * \brief Edge end visitor for Expression edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndOrderingSyntax_Expression(const structure::OrderingSyntax& begin, const expression::ExpressionSyntax& end);

      /**
      * \brief Edge  visitor for AttributeLists edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitParameterSyntax_AttributeLists(const structure::ParameterSyntax& begin, const structure::AttributeListSyntax& end);

      /**
      * \brief Edge end visitor for AttributeLists edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndParameterSyntax_AttributeLists(const structure::ParameterSyntax& begin, const structure::AttributeListSyntax& end);

      /**
      * \brief Edge  visitor for Default edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitParameterSyntax_Default(const structure::ParameterSyntax& begin, const structure::EqualsValueClauseSyntax& end);

      /**
      * \brief Edge end visitor for Default edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndParameterSyntax_Default(const structure::ParameterSyntax& begin, const structure::EqualsValueClauseSyntax& end);

      /**
      * \brief Edge  visitor for Type edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitParameterSyntax_Type(const structure::ParameterSyntax& begin, const expression::TypeSyntax& end);

      /**
      * \brief Edge end visitor for Type edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndParameterSyntax_Type(const structure::ParameterSyntax& begin, const expression::TypeSyntax& end);

      /**
      * \brief Edge  visitor for ExpressionBody edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitPropertyDeclarationSyntax_ExpressionBody(const structure::PropertyDeclarationSyntax& begin, const structure::ArrowExpressionClauseSyntax& end);

      /**
      * \brief Edge end visitor for ExpressionBody edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndPropertyDeclarationSyntax_ExpressionBody(const structure::PropertyDeclarationSyntax& begin, const structure::ArrowExpressionClauseSyntax& end);

      /**
      * \brief Edge  visitor for Initializer edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitPropertyDeclarationSyntax_Initializer(const structure::PropertyDeclarationSyntax& begin, const structure::EqualsValueClauseSyntax& end);

      /**
      * \brief Edge end visitor for Initializer edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndPropertyDeclarationSyntax_Initializer(const structure::PropertyDeclarationSyntax& begin, const structure::EqualsValueClauseSyntax& end);

      /**
      * \brief Edge  visitor for Container edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitQualifiedCrefSyntax_Container(const structure::QualifiedCrefSyntax& begin, const expression::TypeSyntax& end);

      /**
      * \brief Edge end visitor for Container edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndQualifiedCrefSyntax_Container(const structure::QualifiedCrefSyntax& begin, const expression::TypeSyntax& end);

      /**
      * \brief Edge  visitor for Member edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitQualifiedCrefSyntax_Member(const structure::QualifiedCrefSyntax& begin, const structure::MemberCrefSyntax& end);

      /**
      * \brief Edge end visitor for Member edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndQualifiedCrefSyntax_Member(const structure::QualifiedCrefSyntax& begin, const structure::MemberCrefSyntax& end);

      /**
      * \brief Edge  visitor for Clauses edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitQueryBodySyntax_Clauses(const structure::QueryBodySyntax& begin, const structure::QueryClauseSyntax& end);

      /**
      * \brief Edge end visitor for Clauses edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndQueryBodySyntax_Clauses(const structure::QueryBodySyntax& begin, const structure::QueryClauseSyntax& end);

      /**
      * \brief Edge  visitor for Continuation edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitQueryBodySyntax_Continuation(const structure::QueryBodySyntax& begin, const structure::QueryContinuationSyntax& end);

      /**
      * \brief Edge end visitor for Continuation edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndQueryBodySyntax_Continuation(const structure::QueryBodySyntax& begin, const structure::QueryContinuationSyntax& end);

      /**
      * \brief Edge  visitor for SelectOrGroup edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitQueryBodySyntax_SelectOrGroup(const structure::QueryBodySyntax& begin, const structure::SelectOrGroupClauseSyntax& end);

      /**
      * \brief Edge end visitor for SelectOrGroup edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndQueryBodySyntax_SelectOrGroup(const structure::QueryBodySyntax& begin, const structure::SelectOrGroupClauseSyntax& end);

      /**
      * \brief Edge  visitor for Body edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitQueryContinuationSyntax_Body(const structure::QueryContinuationSyntax& begin, const structure::QueryBodySyntax& end);

      /**
      * \brief Edge end visitor for Body edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndQueryContinuationSyntax_Body(const structure::QueryContinuationSyntax& begin, const structure::QueryBodySyntax& end);

      /**
      * \brief Edge  visitor for Expression edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitSelectClauseSyntax_Expression(const structure::SelectClauseSyntax& begin, const expression::ExpressionSyntax& end);

      /**
      * \brief Edge end visitor for Expression edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndSelectClauseSyntax_Expression(const structure::SelectClauseSyntax& begin, const expression::ExpressionSyntax& end);

      /**
      * \brief Edge  visitor for Labels edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitSwitchSectionSyntax_Labels(const structure::SwitchSectionSyntax& begin, const structure::SwitchLabelSyntax& end);

      /**
      * \brief Edge end visitor for Labels edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndSwitchSectionSyntax_Labels(const structure::SwitchSectionSyntax& begin, const structure::SwitchLabelSyntax& end);

      /**
      * \brief Edge  visitor for Statements edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitSwitchSectionSyntax_Statements(const structure::SwitchSectionSyntax& begin, const statement::StatementSyntax& end);

      /**
      * \brief Edge end visitor for Statements edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndSwitchSectionSyntax_Statements(const structure::SwitchSectionSyntax& begin, const statement::StatementSyntax& end);

      /**
      * \brief Edge  visitor for Arguments edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitTypeArgumentListSyntax_Arguments(const structure::TypeArgumentListSyntax& begin, const expression::TypeSyntax& end);

      /**
      * \brief Edge end visitor for Arguments edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndTypeArgumentListSyntax_Arguments(const structure::TypeArgumentListSyntax& begin, const expression::TypeSyntax& end);

      /**
      * \brief Edge  visitor for Type edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitTypeConstraintSyntax_Type(const structure::TypeConstraintSyntax& begin, const expression::TypeSyntax& end);

      /**
      * \brief Edge end visitor for Type edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndTypeConstraintSyntax_Type(const structure::TypeConstraintSyntax& begin, const expression::TypeSyntax& end);

      /**
      * \brief Edge  visitor for Type edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitTypeCrefSyntax_Type(const structure::TypeCrefSyntax& begin, const expression::TypeSyntax& end);

      /**
      * \brief Edge end visitor for Type edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndTypeCrefSyntax_Type(const structure::TypeCrefSyntax& begin, const expression::TypeSyntax& end);

      /**
      * \brief Edge  visitor for ConstraintClauses edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitTypeDeclarationSyntax_ConstraintClauses(const structure::TypeDeclarationSyntax& begin, const structure::TypeParameterConstraintClauseSyntax& end);

      /**
      * \brief Edge end visitor for ConstraintClauses edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndTypeDeclarationSyntax_ConstraintClauses(const structure::TypeDeclarationSyntax& begin, const structure::TypeParameterConstraintClauseSyntax& end);

      /**
      * \brief Edge  visitor for Members edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitTypeDeclarationSyntax_Members(const structure::TypeDeclarationSyntax& begin, const structure::MemberDeclarationSyntax& end);

      /**
      * \brief Edge end visitor for Members edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndTypeDeclarationSyntax_Members(const structure::TypeDeclarationSyntax& begin, const structure::MemberDeclarationSyntax& end);

      /**
      * \brief Edge  visitor for TypeParameterList edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitTypeDeclarationSyntax_TypeParameterList(const structure::TypeDeclarationSyntax& begin, const structure::TypeParameterListSyntax& end);

      /**
      * \brief Edge end visitor for TypeParameterList edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndTypeDeclarationSyntax_TypeParameterList(const structure::TypeDeclarationSyntax& begin, const structure::TypeParameterListSyntax& end);

      /**
      * \brief Edge  visitor for Constraints edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitTypeParameterConstraintClauseSyntax_Constraints(const structure::TypeParameterConstraintClauseSyntax& begin, const structure::TypeParameterConstraintSyntax& end);

      /**
      * \brief Edge end visitor for Constraints edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndTypeParameterConstraintClauseSyntax_Constraints(const structure::TypeParameterConstraintClauseSyntax& begin, const structure::TypeParameterConstraintSyntax& end);

      /**
      * \brief Edge  visitor for Name edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitTypeParameterConstraintClauseSyntax_Name(const structure::TypeParameterConstraintClauseSyntax& begin, const expression::IdentifierNameSyntax& end);

      /**
      * \brief Edge end visitor for Name edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndTypeParameterConstraintClauseSyntax_Name(const structure::TypeParameterConstraintClauseSyntax& begin, const expression::IdentifierNameSyntax& end);

      /**
      * \brief Edge visitor for Parameters edge which.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitTypeParameterListSyntax_Parameters(const structure::TypeParameterListSyntax& begin, const structure::TypeParameterSyntax& end);

      /**
      * \brief Edge visitor for Parameters edge which.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndTypeParameterListSyntax_Parameters(const structure::TypeParameterListSyntax& begin, const structure::TypeParameterSyntax& end);

      /**
      * \brief Edge  visitor for AttributeLists edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitTypeParameterSyntax_AttributeLists(const structure::TypeParameterSyntax& begin, const structure::AttributeListSyntax& end);

      /**
      * \brief Edge end visitor for AttributeLists edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndTypeParameterSyntax_AttributeLists(const structure::TypeParameterSyntax& begin, const structure::AttributeListSyntax& end);

      /**
      * \brief Edge  visitor for Alias edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitUsingDirectiveSyntax_Alias(const structure::UsingDirectiveSyntax& begin, const structure::NameEqualsSyntax& end);

      /**
      * \brief Edge end visitor for Alias edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndUsingDirectiveSyntax_Alias(const structure::UsingDirectiveSyntax& begin, const structure::NameEqualsSyntax& end);

      /**
      * \brief Edge  visitor for Name edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitUsingDirectiveSyntax_Name(const structure::UsingDirectiveSyntax& begin, const expression::NameSyntax& end);

      /**
      * \brief Edge end visitor for Name edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndUsingDirectiveSyntax_Name(const structure::UsingDirectiveSyntax& begin, const expression::NameSyntax& end);

      /**
      * \brief Edge  visitor for Type edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitVariableDeclarationSyntax_Type(const structure::VariableDeclarationSyntax& begin, const expression::TypeSyntax& end);

      /**
      * \brief Edge end visitor for Type edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndVariableDeclarationSyntax_Type(const structure::VariableDeclarationSyntax& begin, const expression::TypeSyntax& end);

      /**
      * \brief Edge  visitor for Variables edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitVariableDeclarationSyntax_Variables(const structure::VariableDeclarationSyntax& begin, const structure::VariableDeclaratorSyntax& end);

      /**
      * \brief Edge end visitor for Variables edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndVariableDeclarationSyntax_Variables(const structure::VariableDeclarationSyntax& begin, const structure::VariableDeclaratorSyntax& end);

      /**
      * \brief Edge  visitor for ArgumentList edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitVariableDeclaratorSyntax_ArgumentList(const structure::VariableDeclaratorSyntax& begin, const structure::BracketedArgumentListSyntax& end);

      /**
      * \brief Edge end visitor for ArgumentList edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndVariableDeclaratorSyntax_ArgumentList(const structure::VariableDeclaratorSyntax& begin, const structure::BracketedArgumentListSyntax& end);

      /**
      * \brief Edge  visitor for Initializer edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitVariableDeclaratorSyntax_Initializer(const structure::VariableDeclaratorSyntax& begin, const structure::EqualsValueClauseSyntax& end);

      /**
      * \brief Edge end visitor for Initializer edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndVariableDeclaratorSyntax_Initializer(const structure::VariableDeclaratorSyntax& begin, const structure::EqualsValueClauseSyntax& end);

      /**
      * \brief Edge  visitor for Condition edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitWhereClauseSyntax_Condition(const structure::WhereClauseSyntax& begin, const expression::ExpressionSyntax& end);

      /**
      * \brief Edge end visitor for Condition edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndWhereClauseSyntax_Condition(const structure::WhereClauseSyntax& begin, const expression::ExpressionSyntax& end);

      /**
      * \brief Edge  visitor for Name edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitXmlAttributeSyntax_Name(const structure::XmlAttributeSyntax& begin, const structure::XmlNameSyntax& end);

      /**
      * \brief Edge end visitor for Name edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndXmlAttributeSyntax_Name(const structure::XmlAttributeSyntax& begin, const structure::XmlNameSyntax& end);

      /**
      * \brief Edge  visitor for Cref edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitXmlCrefAttributeSyntax_Cref(const structure::XmlCrefAttributeSyntax& begin, const structure::CrefSyntax& end);

      /**
      * \brief Edge end visitor for Cref edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndXmlCrefAttributeSyntax_Cref(const structure::XmlCrefAttributeSyntax& begin, const structure::CrefSyntax& end);

      /**
      * \brief Edge  visitor for Name edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitXmlElementEndTagSyntax_Name(const structure::XmlElementEndTagSyntax& begin, const structure::XmlNameSyntax& end);

      /**
      * \brief Edge end visitor for Name edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndXmlElementEndTagSyntax_Name(const structure::XmlElementEndTagSyntax& begin, const structure::XmlNameSyntax& end);

      /**
      * \brief Edge  visitor for Attributes edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitXmlElementStartTagSyntax_Attributes(const structure::XmlElementStartTagSyntax& begin, const structure::XmlAttributeSyntax& end);

      /**
      * \brief Edge end visitor for Attributes edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndXmlElementStartTagSyntax_Attributes(const structure::XmlElementStartTagSyntax& begin, const structure::XmlAttributeSyntax& end);

      /**
      * \brief Edge  visitor for Name edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitXmlElementStartTagSyntax_Name(const structure::XmlElementStartTagSyntax& begin, const structure::XmlNameSyntax& end);

      /**
      * \brief Edge end visitor for Name edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndXmlElementStartTagSyntax_Name(const structure::XmlElementStartTagSyntax& begin, const structure::XmlNameSyntax& end);

      /**
      * \brief Edge  visitor for Content edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitXmlElementSyntax_Content(const structure::XmlElementSyntax& begin, const structure::XmlNodeSyntax& end);

      /**
      * \brief Edge end visitor for Content edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndXmlElementSyntax_Content(const structure::XmlElementSyntax& begin, const structure::XmlNodeSyntax& end);

      /**
      * \brief Edge  visitor for EndTag edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitXmlElementSyntax_EndTag(const structure::XmlElementSyntax& begin, const structure::XmlElementEndTagSyntax& end);

      /**
      * \brief Edge end visitor for EndTag edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndXmlElementSyntax_EndTag(const structure::XmlElementSyntax& begin, const structure::XmlElementEndTagSyntax& end);

      /**
      * \brief Edge  visitor for StartTag edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitXmlElementSyntax_StartTag(const structure::XmlElementSyntax& begin, const structure::XmlElementStartTagSyntax& end);

      /**
      * \brief Edge end visitor for StartTag edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndXmlElementSyntax_StartTag(const structure::XmlElementSyntax& begin, const structure::XmlElementStartTagSyntax& end);

      /**
      * \brief Edge  visitor for Attributes edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitXmlEmptyElementSyntax_Attributes(const structure::XmlEmptyElementSyntax& begin, const structure::XmlAttributeSyntax& end);

      /**
      * \brief Edge end visitor for Attributes edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndXmlEmptyElementSyntax_Attributes(const structure::XmlEmptyElementSyntax& begin, const structure::XmlAttributeSyntax& end);

      /**
      * \brief Edge  visitor for Name edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitXmlEmptyElementSyntax_Name(const structure::XmlEmptyElementSyntax& begin, const structure::XmlNameSyntax& end);

      /**
      * \brief Edge end visitor for Name edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndXmlEmptyElementSyntax_Name(const structure::XmlEmptyElementSyntax& begin, const structure::XmlNameSyntax& end);

      /**
      * \brief Edge  visitor for Identifier edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitXmlNameAttributeSyntax_Identifier(const structure::XmlNameAttributeSyntax& begin, const expression::IdentifierNameSyntax& end);

      /**
      * \brief Edge end visitor for Identifier edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndXmlNameAttributeSyntax_Identifier(const structure::XmlNameAttributeSyntax& begin, const expression::IdentifierNameSyntax& end);

      /**
      * \brief Edge  visitor for Prefix edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitXmlNameSyntax_Prefix(const structure::XmlNameSyntax& begin, const structure::XmlPrefixSyntax& end);

      /**
      * \brief Edge end visitor for Prefix edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndXmlNameSyntax_Prefix(const structure::XmlNameSyntax& begin, const structure::XmlPrefixSyntax& end);

      /**
      * \brief Edge  visitor for Name edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitXmlProcessingInstructionSyntax_Name(const structure::XmlProcessingInstructionSyntax& begin, const structure::XmlNameSyntax& end);

      /**
      * \brief Edge end visitor for Name edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEndXmlProcessingInstructionSyntax_Name(const structure::XmlProcessingInstructionSyntax& begin, const structure::XmlNameSyntax& end);

    protected:
      /** \internal \brief Stores the depth position in the ASG. */
      unsigned depth;
  }; // Visitor


}}}
#endif

