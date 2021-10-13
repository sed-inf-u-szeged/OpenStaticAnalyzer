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

#ifndef _CSHARP_ALGORITHMPREORDER_H_
#define _CSHARP_ALGORITHMPREORDER_H_

#include "csharp/inc/csharp.h"

#include <set>

#include <list>

/**
* \file AlgorithmPreorder.h
* \brief Contains the class `AlgorithmPreorder' which implements the preorder traversal of the ASG.
* This is the visitor which when visit a node it call itself for all tree edges.
*/

namespace columbus { namespace csharp { namespace asg {
  /**
  * \brief Implements the preorder traversal of the ASG.
  */
  class AlgorithmPreorder: public Algorithm , public Visitor{
    private:
      /**
      * \brief Disable copy of object.
      */
      AlgorithmPreorder(const AlgorithmPreorder&);

      /**
      * \brief Disable copy of object.
      */
      AlgorithmPreorder& operator=(const AlgorithmPreorder&);

    public:
      /**
      * \brief Constructor.
      */
      AlgorithmPreorder();

      /**
      * \brief Virtual destructor.
      */
      virtual ~AlgorithmPreorder();

      /**
      * \brief Sets that a node will be visited only once in the visiting.
      */
      void setSafeMode();

      /**
      * \brief Sets that the preorder is executed duly the graph (which means that a node can be visited more than once, even if there is a circle in the graph it will be an endless visiting).
      */
      void setUnsafeMode();

      /**
      * \brief Set visit cross edge tree.
      * \param visit [in] If visit parameter is true, cross edge trees are visited, otherwise they are not visited.
      */
      void setVisitCrossEdgeTree(bool visit);

      /**
      * \brief Set visit filtered edges.
      * \param visit [in] If visit parameter is true, filtered edges are visited, otherwise they are not visited.
      */
      void setVisitFilteredEdges(bool visit);

      /**
      * \brief Set the factory
      * \param node    [in] The preorder visits only the subtree of this node.
      */
      void setFactory(Factory& fact);

      /**
      * \brief add visitor
      * \param node    [in] The preorder visits only the subtree of this node.
      */
      void addVisitor(Visitor& visitor);

      /**
      * \brief Starts a preorder traversal which visits all nodes
      */
      void run();

      /**
      * \brief Starts a preorder traversal, recursively processing all subtres
      * \param node    [in] The preorder visits only the subtree of this node.
      */
      void run(const base::Base& node);

      /**
      * \brief Starts a preorder traversal which visits all nodes of the parameter `fact', then recursively processing all subtrees, and at every nodes call the appropriate visit function of the Visitor `visitor'
      * \param fact    [in] The factory of the ASG.
      * \param visitor [in] The visitor which is called to visit the given node or edge.
      * \deprecated  Please set the visitor with add visitor, set the factory with the set factory function
      */
      void run(const Factory& fact, Visitor& visitor);

      /**
      * \brief Starts a preorder traversal which visits all nodes of the parameter `fact' by processing the parameter `node', then recursively processing all subtrees, and at every nodes call the appropriate visit function of the Visitor `visitor'
      * \param fact    [in] The factory of the ASG.
      * \param visitor [in] The visitor which is called to visit the given node or edge.
      * \param node    [in] The preorder visits only the subtree of this node.
      * \deprecated Please set the visitor with add visitor, set the factory with the set factory function
      */
      void run(const Factory& fact, Visitor& visitor, const base::Base& node);

      /**
      * \brief Starts a preorder traversal which visits all nodes of the parameter `fact' by processing the node with the given id, then recursively processing all subtrees, and at every nodes call the appropriate visit function of the Visitor `visitor'
      * \param fact    [in] The factory of the ASG.
      * \param visitor [in] The visitor which is called to visit the given node or edge.
      * \param nodeId  [in] The preorder visits only the subtree of this node.
      * \deprecated Please set the visitor with add visitor, set the factory with the set factory function
      */
      void run(const Factory& fact, Visitor& visitor, NodeId nodeId);

      /**
      * \brief It set the edge as a tree edge
      * \param edgekind [in] The edge which will used as tree edge.
      */
      void setCrossEdgeToTraversal(EdgeKind edgekind);

      /**
      * \brief Adds the visitor to the stopped visitor set.
      * \param visitor [in] The visitor we adds.
      */
      void stop(Visitor* visitor);

      /** \internal \brief The visitor functions owerloades */
      /**
      * \internal
      * \brief The node call back the this function that achive the preorder
      */
      virtual void visit(const expression::AliasQualifiedNameSyntax& node , bool callVirtualBase = true);

      /**
      * \internal
      * \brief The node call back the this function that achive the preorder
      */
      virtual void visit(const expression::AnonymousMethodExpressionSyntax& node , bool callVirtualBase = true);

      /**
      * \internal
      * \brief The node call back the this function that achive the preorder
      */
      virtual void visit(const expression::AnonymousObjectCreationExpressionSyntax& node , bool callVirtualBase = true);

      /**
      * \internal
      * \brief The node call back the this function that achive the preorder
      */
      virtual void visit(const expression::ArrayCreationExpressionSyntax& node , bool callVirtualBase = true);

      /**
      * \internal
      * \brief The node call back the this function that achive the preorder
      */
      virtual void visit(const expression::ArrayTypeSyntax& node , bool callVirtualBase = true);

      /**
      * \internal
      * \brief The node call back the this function that achive the preorder
      */
      virtual void visit(const expression::AssignmentExpressionSyntax& node , bool callVirtualBase = true);

      /**
      * \internal
      * \brief The node call back the this function that achive the preorder
      */
      virtual void visit(const expression::AwaitExpressionSyntax& node , bool callVirtualBase = true);

      /**
      * \internal
      * \brief The node call back the this function that achive the preorder
      */
      virtual void visit(const expression::BaseExpressionSyntax& node , bool callVirtualBase = true);

      /**
      * \internal
      * \brief The node call back the this function that achive the preorder
      */
      virtual void visit(const expression::BinaryExpressionSyntax& node , bool callVirtualBase = true);

      /**
      * \internal
      * \brief The node call back the this function that achive the preorder
      */
      virtual void visit(const expression::CastExpressionSyntax& node , bool callVirtualBase = true);

      /**
      * \internal
      * \brief The node call back the this function that achive the preorder
      */
      virtual void visit(const expression::CheckedExpressionSyntax& node , bool callVirtualBase = true);

      /**
      * \internal
      * \brief The node call back the this function that achive the preorder
      */
      virtual void visit(const expression::ConditionalAccessExpressionSyntax& node , bool callVirtualBase = true);

      /**
      * \internal
      * \brief The node call back the this function that achive the preorder
      */
      virtual void visit(const expression::ConditionalExpressionSyntax& node , bool callVirtualBase = true);

      /**
      * \internal
      * \brief The node call back the this function that achive the preorder
      */
      virtual void visit(const expression::DeclarationExpressionSyntax& node , bool callVirtualBase = true);

      /**
      * \internal
      * \brief The node call back the this function that achive the preorder
      */
      virtual void visit(const expression::DefaultExpressionSyntax& node , bool callVirtualBase = true);

      /**
      * \internal
      * \brief The node call back the this function that achive the preorder
      */
      virtual void visit(const expression::ElementAccessExpressionSyntax& node , bool callVirtualBase = true);

      /**
      * \internal
      * \brief The node call back the this function that achive the preorder
      */
      virtual void visit(const expression::ElementBindingExpressionSyntax& node , bool callVirtualBase = true);

      /**
      * \internal
      * \brief The node call back the this function that achive the preorder
      */
      virtual void visit(const expression::GenericNameSyntax& node , bool callVirtualBase = true);

      /**
      * \internal
      * \brief The node call back the this function that achive the preorder
      */
      virtual void visit(const expression::IdentifierNameSyntax& node , bool callVirtualBase = true);

      /**
      * \internal
      * \brief The node call back the this function that achive the preorder
      */
      virtual void visit(const expression::ImplicitArrayCreationExpressionSyntax& node , bool callVirtualBase = true);

      /**
      * \internal
      * \brief The node call back the this function that achive the preorder
      */
      virtual void visit(const expression::ImplicitElementAccessSyntax& node , bool callVirtualBase = true);

      /**
      * \internal
      * \brief The node call back the this function that achive the preorder
      */
      virtual void visit(const expression::ImplicitStackAllocArrayCreationExpressionSyntax& node , bool callVirtualBase = true);

      /**
      * \internal
      * \brief The node call back the this function that achive the preorder
      */
      virtual void visit(const expression::InitializerExpressionSyntax& node , bool callVirtualBase = true);

      /**
      * \internal
      * \brief The node call back the this function that achive the preorder
      */
      virtual void visit(const expression::InterpolatedStringExpressionSyntax& node , bool callVirtualBase = true);

      /**
      * \internal
      * \brief The node call back the this function that achive the preorder
      */
      virtual void visit(const expression::InvocationExpressionSyntax& node , bool callVirtualBase = true);

      /**
      * \internal
      * \brief The node call back the this function that achive the preorder
      */
      virtual void visit(const expression::IsPatternExpressionSyntax& node , bool callVirtualBase = true);

      /**
      * \internal
      * \brief The node call back the this function that achive the preorder
      */
      virtual void visit(const expression::LiteralExpressionSyntax& node , bool callVirtualBase = true);

      /**
      * \internal
      * \brief The node call back the this function that achive the preorder
      */
      virtual void visit(const expression::MakeRefExpressionSyntax& node , bool callVirtualBase = true);

      /**
      * \internal
      * \brief The node call back the this function that achive the preorder
      */
      virtual void visit(const expression::MemberAccessExpressionSyntax& node , bool callVirtualBase = true);

      /**
      * \internal
      * \brief The node call back the this function that achive the preorder
      */
      virtual void visit(const expression::MemberBindingExpressionSyntax& node , bool callVirtualBase = true);

      /**
      * \internal
      * \brief The node call back the this function that achive the preorder
      */
      virtual void visit(const expression::NullableTypeSyntax& node , bool callVirtualBase = true);

      /**
      * \internal
      * \brief The node call back the this function that achive the preorder
      */
      virtual void visit(const expression::ObjectCreationExpressionSyntax& node , bool callVirtualBase = true);

      /**
      * \internal
      * \brief The node call back the this function that achive the preorder
      */
      virtual void visit(const expression::OmittedArraySizeExpressionSyntax& node , bool callVirtualBase = true);

      /**
      * \internal
      * \brief The node call back the this function that achive the preorder
      */
      virtual void visit(const expression::OmittedTypeArgumentSyntax& node , bool callVirtualBase = true);

      /**
      * \internal
      * \brief The node call back the this function that achive the preorder
      */
      virtual void visit(const expression::ParenthesizedExpressionSyntax& node , bool callVirtualBase = true);

      /**
      * \internal
      * \brief The node call back the this function that achive the preorder
      */
      virtual void visit(const expression::ParenthesizedLambdaExpressionSyntax& node , bool callVirtualBase = true);

      /**
      * \internal
      * \brief The node call back the this function that achive the preorder
      */
      virtual void visit(const expression::PointerTypeSyntax& node , bool callVirtualBase = true);

      /**
      * \internal
      * \brief The node call back the this function that achive the preorder
      */
      virtual void visit(const expression::PostfixUnaryExpressionSyntax& node , bool callVirtualBase = true);

      /**
      * \internal
      * \brief The node call back the this function that achive the preorder
      */
      virtual void visit(const expression::PredefinedTypeSyntax& node , bool callVirtualBase = true);

      /**
      * \internal
      * \brief The node call back the this function that achive the preorder
      */
      virtual void visit(const expression::PrefixUnaryExpressionSyntax& node , bool callVirtualBase = true);

      /**
      * \internal
      * \brief The node call back the this function that achive the preorder
      */
      virtual void visit(const expression::QualifiedNameSyntax& node , bool callVirtualBase = true);

      /**
      * \internal
      * \brief The node call back the this function that achive the preorder
      */
      virtual void visit(const expression::QueryExpressionSyntax& node , bool callVirtualBase = true);

      /**
      * \internal
      * \brief The node call back the this function that achive the preorder
      */
      virtual void visit(const expression::RangeExpressionSyntax& node , bool callVirtualBase = true);

      /**
      * \internal
      * \brief The node call back the this function that achive the preorder
      */
      virtual void visit(const expression::RefExpressionSyntax& node , bool callVirtualBase = true);

      /**
      * \internal
      * \brief The node call back the this function that achive the preorder
      */
      virtual void visit(const expression::RefTypeExpressionSyntax& node , bool callVirtualBase = true);

      /**
      * \internal
      * \brief The node call back the this function that achive the preorder
      */
      virtual void visit(const expression::RefTypeSyntax& node , bool callVirtualBase = true);

      /**
      * \internal
      * \brief The node call back the this function that achive the preorder
      */
      virtual void visit(const expression::RefValueExpressionSyntax& node , bool callVirtualBase = true);

      /**
      * \internal
      * \brief The node call back the this function that achive the preorder
      */
      virtual void visit(const expression::SimpleLambdaExpressionSyntax& node , bool callVirtualBase = true);

      /**
      * \internal
      * \brief The node call back the this function that achive the preorder
      */
      virtual void visit(const expression::SizeOfExpressionSyntax& node , bool callVirtualBase = true);

      /**
      * \internal
      * \brief The node call back the this function that achive the preorder
      */
      virtual void visit(const expression::StackAllocArrayCreationExpressionSyntax& node , bool callVirtualBase = true);

      /**
      * \internal
      * \brief The node call back the this function that achive the preorder
      */
      virtual void visit(const expression::SwitchExpressionSyntax& node , bool callVirtualBase = true);

      /**
      * \internal
      * \brief The node call back the this function that achive the preorder
      */
      virtual void visit(const expression::ThisExpressionSyntax& node , bool callVirtualBase = true);

      /**
      * \internal
      * \brief The node call back the this function that achive the preorder
      */
      virtual void visit(const expression::ThrowExpressionSyntax& node , bool callVirtualBase = true);

      /**
      * \internal
      * \brief The node call back the this function that achive the preorder
      */
      virtual void visit(const expression::TupleExpressionSyntax& node , bool callVirtualBase = true);

      /**
      * \internal
      * \brief The node call back the this function that achive the preorder
      */
      virtual void visit(const expression::TupleTypeSyntax& node , bool callVirtualBase = true);

      /**
      * \internal
      * \brief The node call back the this function that achive the preorder
      */
      virtual void visit(const expression::TypeOfExpressionSyntax& node , bool callVirtualBase = true);

      /**
      * \internal
      * \brief The node call back the this function that achive the preorder
      */
      virtual void visit(const statement::BlockSyntax& node , bool callVirtualBase = true);

      /**
      * \internal
      * \brief The node call back the this function that achive the preorder
      */
      virtual void visit(const statement::BreakStatementSyntax& node , bool callVirtualBase = true);

      /**
      * \internal
      * \brief The node call back the this function that achive the preorder
      */
      virtual void visit(const statement::CheckedStatementSyntax& node , bool callVirtualBase = true);

      /**
      * \internal
      * \brief The node call back the this function that achive the preorder
      */
      virtual void visit(const statement::ContinueStatementSyntax& node , bool callVirtualBase = true);

      /**
      * \internal
      * \brief The node call back the this function that achive the preorder
      */
      virtual void visit(const statement::DoStatementSyntax& node , bool callVirtualBase = true);

      /**
      * \internal
      * \brief The node call back the this function that achive the preorder
      */
      virtual void visit(const statement::EmptyStatementSyntax& node , bool callVirtualBase = true);

      /**
      * \internal
      * \brief The node call back the this function that achive the preorder
      */
      virtual void visit(const statement::ExpressionStatementSyntax& node , bool callVirtualBase = true);

      /**
      * \internal
      * \brief The node call back the this function that achive the preorder
      */
      virtual void visit(const statement::FixedStatementSyntax& node , bool callVirtualBase = true);

      /**
      * \internal
      * \brief The node call back the this function that achive the preorder
      */
      virtual void visit(const statement::ForEachStatementSyntax& node , bool callVirtualBase = true);

      /**
      * \internal
      * \brief The node call back the this function that achive the preorder
      */
      virtual void visit(const statement::ForEachVariableStatementSyntax& node , bool callVirtualBase = true);

      /**
      * \internal
      * \brief The node call back the this function that achive the preorder
      */
      virtual void visit(const statement::ForStatementSyntax& node , bool callVirtualBase = true);

      /**
      * \internal
      * \brief The node call back the this function that achive the preorder
      */
      virtual void visit(const statement::GotoStatementSyntax& node , bool callVirtualBase = true);

      /**
      * \internal
      * \brief The node call back the this function that achive the preorder
      */
      virtual void visit(const statement::IfStatementSyntax& node , bool callVirtualBase = true);

      /**
      * \internal
      * \brief The node call back the this function that achive the preorder
      */
      virtual void visit(const statement::LabeledStatementSyntax& node , bool callVirtualBase = true);

      /**
      * \internal
      * \brief The node call back the this function that achive the preorder
      */
      virtual void visit(const statement::LocalDeclarationStatementSyntax& node , bool callVirtualBase = true);

      /**
      * \internal
      * \brief The node call back the this function that achive the preorder
      */
      virtual void visit(const statement::LocalFunctionStatementSyntax& node , bool callVirtualBase = true);

      /**
      * \internal
      * \brief The node call back the this function that achive the preorder
      */
      virtual void visit(const statement::LockStatementSyntax& node , bool callVirtualBase = true);

      /**
      * \internal
      * \brief The node call back the this function that achive the preorder
      */
      virtual void visit(const statement::ReturnStatementSyntax& node , bool callVirtualBase = true);

      /**
      * \internal
      * \brief The node call back the this function that achive the preorder
      */
      virtual void visit(const statement::SwitchStatementSyntax& node , bool callVirtualBase = true);

      /**
      * \internal
      * \brief The node call back the this function that achive the preorder
      */
      virtual void visit(const statement::ThrowStatementSyntax& node , bool callVirtualBase = true);

      /**
      * \internal
      * \brief The node call back the this function that achive the preorder
      */
      virtual void visit(const statement::TryStatementSyntax& node , bool callVirtualBase = true);

      /**
      * \internal
      * \brief The node call back the this function that achive the preorder
      */
      virtual void visit(const statement::UnsafeStatementSyntax& node , bool callVirtualBase = true);

      /**
      * \internal
      * \brief The node call back the this function that achive the preorder
      */
      virtual void visit(const statement::UsingStatementSyntax& node , bool callVirtualBase = true);

      /**
      * \internal
      * \brief The node call back the this function that achive the preorder
      */
      virtual void visit(const statement::WhileStatementSyntax& node , bool callVirtualBase = true);

      /**
      * \internal
      * \brief The node call back the this function that achive the preorder
      */
      virtual void visit(const statement::YieldStatementSyntax& node , bool callVirtualBase = true);

      /**
      * \internal
      * \brief The node call back the this function that achive the preorder
      */
      virtual void visit(const structure::AccessorDeclarationSyntax& node , bool callVirtualBase = true);

      /**
      * \internal
      * \brief The node call back the this function that achive the preorder
      */
      virtual void visit(const structure::AccessorListSyntax& node , bool callVirtualBase = true);

      /**
      * \internal
      * \brief The node call back the this function that achive the preorder
      */
      virtual void visit(const structure::AnonymousObjectMemberDeclaratorSyntax& node , bool callVirtualBase = true);

      /**
      * \internal
      * \brief The node call back the this function that achive the preorder
      */
      virtual void visit(const structure::ArgumentListSyntax& node , bool callVirtualBase = true);

      /**
      * \internal
      * \brief The node call back the this function that achive the preorder
      */
      virtual void visit(const structure::ArgumentSyntax& node , bool callVirtualBase = true);

      /**
      * \internal
      * \brief The node call back the this function that achive the preorder
      */
      virtual void visit(const structure::ArrayRankSpecifierSyntax& node , bool callVirtualBase = true);

      /**
      * \internal
      * \brief The node call back the this function that achive the preorder
      */
      virtual void visit(const structure::ArrowExpressionClauseSyntax& node , bool callVirtualBase = true);

      /**
      * \internal
      * \brief The node call back the this function that achive the preorder
      */
      virtual void visit(const structure::AttributeArgumentListSyntax& node , bool callVirtualBase = true);

      /**
      * \internal
      * \brief The node call back the this function that achive the preorder
      */
      virtual void visit(const structure::AttributeArgumentSyntax& node , bool callVirtualBase = true);

      /**
      * \internal
      * \brief The node call back the this function that achive the preorder
      */
      virtual void visit(const structure::AttributeListSyntax& node , bool callVirtualBase = true);

      /**
      * \internal
      * \brief The node call back the this function that achive the preorder
      */
      virtual void visit(const structure::AttributeSyntax& node , bool callVirtualBase = true);

      /**
      * \internal
      * \brief The node call back the this function that achive the preorder
      */
      virtual void visit(const structure::AttributeTargetSpecifierSyntax& node , bool callVirtualBase = true);

      /**
      * \internal
      * \brief The node call back the this function that achive the preorder
      */
      virtual void visit(const structure::BaseListSyntax& node , bool callVirtualBase = true);

      /**
      * \internal
      * \brief The node call back the this function that achive the preorder
      */
      virtual void visit(const structure::BracketedArgumentListSyntax& node , bool callVirtualBase = true);

      /**
      * \internal
      * \brief The node call back the this function that achive the preorder
      */
      virtual void visit(const structure::BracketedParameterListSyntax& node , bool callVirtualBase = true);

      /**
      * \internal
      * \brief The node call back the this function that achive the preorder
      */
      virtual void visit(const structure::CasePatternSwitchLabelSyntax& node , bool callVirtualBase = true);

      /**
      * \internal
      * \brief The node call back the this function that achive the preorder
      */
      virtual void visit(const structure::CaseSwitchLabelSyntax& node , bool callVirtualBase = true);

      /**
      * \internal
      * \brief The node call back the this function that achive the preorder
      */
      virtual void visit(const structure::CatchClauseSyntax& node , bool callVirtualBase = true);

      /**
      * \internal
      * \brief The node call back the this function that achive the preorder
      */
      virtual void visit(const structure::CatchDeclarationSyntax& node , bool callVirtualBase = true);

      /**
      * \internal
      * \brief The node call back the this function that achive the preorder
      */
      virtual void visit(const structure::CatchFilterClauseSyntax& node , bool callVirtualBase = true);

      /**
      * \internal
      * \brief The node call back the this function that achive the preorder
      */
      virtual void visit(const structure::ClassDeclarationSyntax& node , bool callVirtualBase = true);

      /**
      * \internal
      * \brief The node call back the this function that achive the preorder
      */
      virtual void visit(const structure::ClassOrStructConstraintSyntax& node , bool callVirtualBase = true);

      /**
      * \internal
      * \brief The node call back the this function that achive the preorder
      */
      virtual void visit(const structure::CompilationUnitSyntax& node , bool callVirtualBase = true);

      /**
      * \internal
      * \brief The node call back the this function that achive the preorder
      */
      virtual void visit(const structure::ConstantPatternSyntax& node , bool callVirtualBase = true);

      /**
      * \internal
      * \brief The node call back the this function that achive the preorder
      */
      virtual void visit(const structure::ConstructorConstraintSyntax& node , bool callVirtualBase = true);

      /**
      * \internal
      * \brief The node call back the this function that achive the preorder
      */
      virtual void visit(const structure::ConstructorDeclarationSyntax& node , bool callVirtualBase = true);

      /**
      * \internal
      * \brief The node call back the this function that achive the preorder
      */
      virtual void visit(const structure::ConstructorInitializerSyntax& node , bool callVirtualBase = true);

      /**
      * \internal
      * \brief The node call back the this function that achive the preorder
      */
      virtual void visit(const structure::ConversionOperatorDeclarationSyntax& node , bool callVirtualBase = true);

      /**
      * \internal
      * \brief The node call back the this function that achive the preorder
      */
      virtual void visit(const structure::ConversionOperatorMemberCrefSyntax& node , bool callVirtualBase = true);

      /**
      * \internal
      * \brief The node call back the this function that achive the preorder
      */
      virtual void visit(const structure::CrefBracketedParameterListSyntax& node , bool callVirtualBase = true);

      /**
      * \internal
      * \brief The node call back the this function that achive the preorder
      */
      virtual void visit(const structure::CrefParameterListSyntax& node , bool callVirtualBase = true);

      /**
      * \internal
      * \brief The node call back the this function that achive the preorder
      */
      virtual void visit(const structure::CrefParameterSyntax& node , bool callVirtualBase = true);

      /**
      * \internal
      * \brief The node call back the this function that achive the preorder
      */
      virtual void visit(const structure::DeclarationPatternSyntax& node , bool callVirtualBase = true);

      /**
      * \internal
      * \brief The node call back the this function that achive the preorder
      */
      virtual void visit(const structure::DefaultSwitchLabelSyntax& node , bool callVirtualBase = true);

      /**
      * \internal
      * \brief The node call back the this function that achive the preorder
      */
      virtual void visit(const structure::DelegateDeclarationSyntax& node , bool callVirtualBase = true);

      /**
      * \internal
      * \brief The node call back the this function that achive the preorder
      */
      virtual void visit(const structure::DestructorDeclarationSyntax& node , bool callVirtualBase = true);

      /**
      * \internal
      * \brief The node call back the this function that achive the preorder
      */
      virtual void visit(const structure::DiscardDesignationSyntax& node , bool callVirtualBase = true);

      /**
      * \internal
      * \brief The node call back the this function that achive the preorder
      */
      virtual void visit(const structure::DiscardPatternSyntax& node , bool callVirtualBase = true);

      /**
      * \internal
      * \brief The node call back the this function that achive the preorder
      */
      virtual void visit(const structure::ElseClauseSyntax& node , bool callVirtualBase = true);

      /**
      * \internal
      * \brief The node call back the this function that achive the preorder
      */
      virtual void visit(const structure::EnumDeclarationSyntax& node , bool callVirtualBase = true);

      /**
      * \internal
      * \brief The node call back the this function that achive the preorder
      */
      virtual void visit(const structure::EnumMemberDeclarationSyntax& node , bool callVirtualBase = true);

      /**
      * \internal
      * \brief The node call back the this function that achive the preorder
      */
      virtual void visit(const structure::EqualsValueClauseSyntax& node , bool callVirtualBase = true);

      /**
      * \internal
      * \brief The node call back the this function that achive the preorder
      */
      virtual void visit(const structure::EventDeclarationSyntax& node , bool callVirtualBase = true);

      /**
      * \internal
      * \brief The node call back the this function that achive the preorder
      */
      virtual void visit(const structure::EventFieldDeclarationSyntax& node , bool callVirtualBase = true);

      /**
      * \internal
      * \brief The node call back the this function that achive the preorder
      */
      virtual void visit(const structure::ExplicitInterfaceSpecifierSyntax& node , bool callVirtualBase = true);

      /**
      * \internal
      * \brief The node call back the this function that achive the preorder
      */
      virtual void visit(const structure::ExternAliasDirectiveSyntax& node , bool callVirtualBase = true);

      /**
      * \internal
      * \brief The node call back the this function that achive the preorder
      */
      virtual void visit(const structure::FieldDeclarationSyntax& node , bool callVirtualBase = true);

      /**
      * \internal
      * \brief The node call back the this function that achive the preorder
      */
      virtual void visit(const structure::FinallyClauseSyntax& node , bool callVirtualBase = true);

      /**
      * \internal
      * \brief The node call back the this function that achive the preorder
      */
      virtual void visit(const structure::FromClauseSyntax& node , bool callVirtualBase = true);

      /**
      * \internal
      * \brief The node call back the this function that achive the preorder
      */
      virtual void visit(const structure::GlobalStatementSyntax& node , bool callVirtualBase = true);

      /**
      * \internal
      * \brief The node call back the this function that achive the preorder
      */
      virtual void visit(const structure::GroupClauseSyntax& node , bool callVirtualBase = true);

      /**
      * \internal
      * \brief The node call back the this function that achive the preorder
      */
      virtual void visit(const structure::IncompleteMemberSyntax& node , bool callVirtualBase = true);

      /**
      * \internal
      * \brief The node call back the this function that achive the preorder
      */
      virtual void visit(const structure::IndexerDeclarationSyntax& node , bool callVirtualBase = true);

      /**
      * \internal
      * \brief The node call back the this function that achive the preorder
      */
      virtual void visit(const structure::IndexerMemberCrefSyntax& node , bool callVirtualBase = true);

      /**
      * \internal
      * \brief The node call back the this function that achive the preorder
      */
      virtual void visit(const structure::InterfaceDeclarationSyntax& node , bool callVirtualBase = true);

      /**
      * \internal
      * \brief The node call back the this function that achive the preorder
      */
      virtual void visit(const structure::InterpolatedStringTextSyntax& node , bool callVirtualBase = true);

      /**
      * \internal
      * \brief The node call back the this function that achive the preorder
      */
      virtual void visit(const structure::InterpolationAlignmentClauseSyntax& node , bool callVirtualBase = true);

      /**
      * \internal
      * \brief The node call back the this function that achive the preorder
      */
      virtual void visit(const structure::InterpolationFormatClauseSyntax& node , bool callVirtualBase = true);

      /**
      * \internal
      * \brief The node call back the this function that achive the preorder
      */
      virtual void visit(const structure::InterpolationSyntax& node , bool callVirtualBase = true);

      /**
      * \internal
      * \brief The node call back the this function that achive the preorder
      */
      virtual void visit(const structure::JoinClauseSyntax& node , bool callVirtualBase = true);

      /**
      * \internal
      * \brief The node call back the this function that achive the preorder
      */
      virtual void visit(const structure::JoinIntoClauseSyntax& node , bool callVirtualBase = true);

      /**
      * \internal
      * \brief The node call back the this function that achive the preorder
      */
      virtual void visit(const structure::LetClauseSyntax& node , bool callVirtualBase = true);

      /**
      * \internal
      * \brief The node call back the this function that achive the preorder
      */
      virtual void visit(const structure::MethodDeclarationSyntax& node , bool callVirtualBase = true);

      /**
      * \internal
      * \brief The node call back the this function that achive the preorder
      */
      virtual void visit(const structure::NameColonSyntax& node , bool callVirtualBase = true);

      /**
      * \internal
      * \brief The node call back the this function that achive the preorder
      */
      virtual void visit(const structure::NameEqualsSyntax& node , bool callVirtualBase = true);

      /**
      * \internal
      * \brief The node call back the this function that achive the preorder
      */
      virtual void visit(const structure::NameMemberCrefSyntax& node , bool callVirtualBase = true);

      /**
      * \internal
      * \brief The node call back the this function that achive the preorder
      */
      virtual void visit(const structure::NamespaceDeclarationSyntax& node , bool callVirtualBase = true);

      /**
      * \internal
      * \brief The node call back the this function that achive the preorder
      */
      virtual void visit(const structure::OperatorDeclarationSyntax& node , bool callVirtualBase = true);

      /**
      * \internal
      * \brief The node call back the this function that achive the preorder
      */
      virtual void visit(const structure::OperatorMemberCrefSyntax& node , bool callVirtualBase = true);

      /**
      * \internal
      * \brief The node call back the this function that achive the preorder
      */
      virtual void visit(const structure::OrderByClauseSyntax& node , bool callVirtualBase = true);

      /**
      * \internal
      * \brief The node call back the this function that achive the preorder
      */
      virtual void visit(const structure::OrderingSyntax& node , bool callVirtualBase = true);

      /**
      * \internal
      * \brief The node call back the this function that achive the preorder
      */
      virtual void visit(const structure::ParameterListSyntax& node , bool callVirtualBase = true);

      /**
      * \internal
      * \brief The node call back the this function that achive the preorder
      */
      virtual void visit(const structure::ParameterSyntax& node , bool callVirtualBase = true);

      /**
      * \internal
      * \brief The node call back the this function that achive the preorder
      */
      virtual void visit(const structure::ParenthesizedVariableDesignationSyntax& node , bool callVirtualBase = true);

      /**
      * \internal
      * \brief The node call back the this function that achive the preorder
      */
      virtual void visit(const structure::PositionalPatternClauseSyntax& node , bool callVirtualBase = true);

      /**
      * \internal
      * \brief The node call back the this function that achive the preorder
      */
      virtual void visit(const structure::PropertyDeclarationSyntax& node , bool callVirtualBase = true);

      /**
      * \internal
      * \brief The node call back the this function that achive the preorder
      */
      virtual void visit(const structure::PropertyPatternClauseSyntax& node , bool callVirtualBase = true);

      /**
      * \internal
      * \brief The node call back the this function that achive the preorder
      */
      virtual void visit(const structure::QualifiedCrefSyntax& node , bool callVirtualBase = true);

      /**
      * \internal
      * \brief The node call back the this function that achive the preorder
      */
      virtual void visit(const structure::QueryBodySyntax& node , bool callVirtualBase = true);

      /**
      * \internal
      * \brief The node call back the this function that achive the preorder
      */
      virtual void visit(const structure::QueryContinuationSyntax& node , bool callVirtualBase = true);

      /**
      * \internal
      * \brief The node call back the this function that achive the preorder
      */
      virtual void visit(const structure::RecursivePatternSyntax& node , bool callVirtualBase = true);

      /**
      * \internal
      * \brief The node call back the this function that achive the preorder
      */
      virtual void visit(const structure::SelectClauseSyntax& node , bool callVirtualBase = true);

      /**
      * \internal
      * \brief The node call back the this function that achive the preorder
      */
      virtual void visit(const structure::SimpleBaseTypeSyntax& node , bool callVirtualBase = true);

      /**
      * \internal
      * \brief The node call back the this function that achive the preorder
      */
      virtual void visit(const structure::SingleVariableDesignationSyntax& node , bool callVirtualBase = true);

      /**
      * \internal
      * \brief The node call back the this function that achive the preorder
      */
      virtual void visit(const structure::StructDeclarationSyntax& node , bool callVirtualBase = true);

      /**
      * \internal
      * \brief The node call back the this function that achive the preorder
      */
      virtual void visit(const structure::SubpatternSyntax& node , bool callVirtualBase = true);

      /**
      * \internal
      * \brief The node call back the this function that achive the preorder
      */
      virtual void visit(const structure::SwitchExpressionArmSyntax& node , bool callVirtualBase = true);

      /**
      * \internal
      * \brief The node call back the this function that achive the preorder
      */
      virtual void visit(const structure::SwitchSectionSyntax& node , bool callVirtualBase = true);

      /**
      * \internal
      * \brief The node call back the this function that achive the preorder
      */
      virtual void visit(const structure::SyntaxToken& node , bool callVirtualBase = true);

      /**
      * \internal
      * \brief The node call back the this function that achive the preorder
      */
      virtual void visit(const structure::TupleElementSyntax& node , bool callVirtualBase = true);

      /**
      * \internal
      * \brief The node call back the this function that achive the preorder
      */
      virtual void visit(const structure::TypeArgumentListSyntax& node , bool callVirtualBase = true);

      /**
      * \internal
      * \brief The node call back the this function that achive the preorder
      */
      virtual void visit(const structure::TypeConstraintSyntax& node , bool callVirtualBase = true);

      /**
      * \internal
      * \brief The node call back the this function that achive the preorder
      */
      virtual void visit(const structure::TypeCrefSyntax& node , bool callVirtualBase = true);

      /**
      * \internal
      * \brief The node call back the this function that achive the preorder
      */
      virtual void visit(const structure::TypeParameterConstraintClauseSyntax& node , bool callVirtualBase = true);

      /**
      * \internal
      * \brief The node call back the this function that achive the preorder
      */
      virtual void visit(const structure::TypeParameterListSyntax& node , bool callVirtualBase = true);

      /**
      * \internal
      * \brief The node call back the this function that achive the preorder
      */
      virtual void visit(const structure::TypeParameterSyntax& node , bool callVirtualBase = true);

      /**
      * \internal
      * \brief The node call back the this function that achive the preorder
      */
      virtual void visit(const structure::UsingDirectiveSyntax& node , bool callVirtualBase = true);

      /**
      * \internal
      * \brief The node call back the this function that achive the preorder
      */
      virtual void visit(const structure::VarPatternSyntax& node , bool callVirtualBase = true);

      /**
      * \internal
      * \brief The node call back the this function that achive the preorder
      */
      virtual void visit(const structure::VariableDeclarationSyntax& node , bool callVirtualBase = true);

      /**
      * \internal
      * \brief The node call back the this function that achive the preorder
      */
      virtual void visit(const structure::VariableDeclaratorSyntax& node , bool callVirtualBase = true);

      /**
      * \internal
      * \brief The node call back the this function that achive the preorder
      */
      virtual void visit(const structure::WhenClauseSyntax& node , bool callVirtualBase = true);

      /**
      * \internal
      * \brief The node call back the this function that achive the preorder
      */
      virtual void visit(const structure::WhereClauseSyntax& node , bool callVirtualBase = true);

      /**
      * \internal
      * \brief The node call back the this function that achive the preorder
      */
      virtual void visit(const structure::XmlCDataSectionSyntax& node , bool callVirtualBase = true);

      /**
      * \internal
      * \brief The node call back the this function that achive the preorder
      */
      virtual void visit(const structure::XmlCommentSyntax& node , bool callVirtualBase = true);

      /**
      * \internal
      * \brief The node call back the this function that achive the preorder
      */
      virtual void visit(const structure::XmlCrefAttributeSyntax& node , bool callVirtualBase = true);

      /**
      * \internal
      * \brief The node call back the this function that achive the preorder
      */
      virtual void visit(const structure::XmlElementEndTagSyntax& node , bool callVirtualBase = true);

      /**
      * \internal
      * \brief The node call back the this function that achive the preorder
      */
      virtual void visit(const structure::XmlElementStartTagSyntax& node , bool callVirtualBase = true);

      /**
      * \internal
      * \brief The node call back the this function that achive the preorder
      */
      virtual void visit(const structure::XmlElementSyntax& node , bool callVirtualBase = true);

      /**
      * \internal
      * \brief The node call back the this function that achive the preorder
      */
      virtual void visit(const structure::XmlEmptyElementSyntax& node , bool callVirtualBase = true);

      /**
      * \internal
      * \brief The node call back the this function that achive the preorder
      */
      virtual void visit(const structure::XmlNameAttributeSyntax& node , bool callVirtualBase = true);

      /**
      * \internal
      * \brief The node call back the this function that achive the preorder
      */
      virtual void visit(const structure::XmlNameSyntax& node , bool callVirtualBase = true);

      /**
      * \internal
      * \brief The node call back the this function that achive the preorder
      */
      virtual void visit(const structure::XmlPrefixSyntax& node , bool callVirtualBase = true);

      /**
      * \internal
      * \brief The node call back the this function that achive the preorder
      */
      virtual void visit(const structure::XmlProcessingInstructionSyntax& node , bool callVirtualBase = true);

      /**
      * \internal
      * \brief The node call back the this function that achive the preorder
      */
      virtual void visit(const structure::XmlTextAttributeSyntax& node , bool callVirtualBase = true);

      /**
      * \internal
      * \brief The node call back the this function that achive the preorder
      */
      virtual void visit(const structure::XmlTextSyntax& node , bool callVirtualBase = true);

      /** \internal \brief End The visitor functions owerloades */
    protected:
      /**
      * \internal
      * \brief It call the traversal for the edges
      * \param node            [in] The node with own type
      * \param callVirtualBase [in] This paramater is don't used just api copatibility used.
      */
      virtual void visitAllEdges(const base::Base& node , bool callVirtualBase = true);

      /**
      * \internal
      * \brief It call the traversal for the edges
      * \param node            [in] The node with own type
      * \param callVirtualBase [in] This paramater is don't used just api copatibility used.
      */
      virtual void visitAllEdges(const base::Positioned& node , bool callVirtualBase = true);

      /**
      * \internal
      * \brief It call the traversal for the edges
      * \param node            [in] The node with own type
      * \param callVirtualBase [in] This paramater is don't used just api copatibility used.
      */
      virtual void visitAllEdges(const expression::AliasQualifiedNameSyntax& node , bool callVirtualBase = true);

      /**
      * \internal
      * \brief It call the traversal for the edges
      * \param node            [in] The node with own type
      * \param callVirtualBase [in] This paramater is don't used just api copatibility used.
      */
      virtual void visitAllEdges(const expression::AnonymousFunctionExpressionSyntax& node , bool callVirtualBase = true);

      /**
      * \internal
      * \brief It call the traversal for the edges
      * \param node            [in] The node with own type
      * \param callVirtualBase [in] This paramater is don't used just api copatibility used.
      */
      virtual void visitAllEdges(const expression::AnonymousMethodExpressionSyntax& node , bool callVirtualBase = true);

      /**
      * \internal
      * \brief It call the traversal for the edges
      * \param node            [in] The node with own type
      * \param callVirtualBase [in] This paramater is don't used just api copatibility used.
      */
      virtual void visitAllEdges(const expression::AnonymousObjectCreationExpressionSyntax& node , bool callVirtualBase = true);

      /**
      * \internal
      * \brief It call the traversal for the edges
      * \param node            [in] The node with own type
      * \param callVirtualBase [in] This paramater is don't used just api copatibility used.
      */
      virtual void visitAllEdges(const expression::ArrayCreationExpressionSyntax& node , bool callVirtualBase = true);

      /**
      * \internal
      * \brief It call the traversal for the edges
      * \param node            [in] The node with own type
      * \param callVirtualBase [in] This paramater is don't used just api copatibility used.
      */
      virtual void visitAllEdges(const expression::ArrayTypeSyntax& node , bool callVirtualBase = true);

      /**
      * \internal
      * \brief It call the traversal for the edges
      * \param node            [in] The node with own type
      * \param callVirtualBase [in] This paramater is don't used just api copatibility used.
      */
      virtual void visitAllEdges(const expression::AssignmentExpressionSyntax& node , bool callVirtualBase = true);

      /**
      * \internal
      * \brief It call the traversal for the edges
      * \param node            [in] The node with own type
      * \param callVirtualBase [in] This paramater is don't used just api copatibility used.
      */
      virtual void visitAllEdges(const expression::AwaitExpressionSyntax& node , bool callVirtualBase = true);

      /**
      * \internal
      * \brief It call the traversal for the edges
      * \param node            [in] The node with own type
      * \param callVirtualBase [in] This paramater is don't used just api copatibility used.
      */
      virtual void visitAllEdges(const expression::BaseExpressionSyntax& node , bool callVirtualBase = true);

      /**
      * \internal
      * \brief It call the traversal for the edges
      * \param node            [in] The node with own type
      * \param callVirtualBase [in] This paramater is don't used just api copatibility used.
      */
      virtual void visitAllEdges(const expression::BinaryExpressionSyntax& node , bool callVirtualBase = true);

      /**
      * \internal
      * \brief It call the traversal for the edges
      * \param node            [in] The node with own type
      * \param callVirtualBase [in] This paramater is don't used just api copatibility used.
      */
      virtual void visitAllEdges(const expression::CastExpressionSyntax& node , bool callVirtualBase = true);

      /**
      * \internal
      * \brief It call the traversal for the edges
      * \param node            [in] The node with own type
      * \param callVirtualBase [in] This paramater is don't used just api copatibility used.
      */
      virtual void visitAllEdges(const expression::CheckedExpressionSyntax& node , bool callVirtualBase = true);

      /**
      * \internal
      * \brief It call the traversal for the edges
      * \param node            [in] The node with own type
      * \param callVirtualBase [in] This paramater is don't used just api copatibility used.
      */
      virtual void visitAllEdges(const expression::ConditionalAccessExpressionSyntax& node , bool callVirtualBase = true);

      /**
      * \internal
      * \brief It call the traversal for the edges
      * \param node            [in] The node with own type
      * \param callVirtualBase [in] This paramater is don't used just api copatibility used.
      */
      virtual void visitAllEdges(const expression::ConditionalExpressionSyntax& node , bool callVirtualBase = true);

      /**
      * \internal
      * \brief It call the traversal for the edges
      * \param node            [in] The node with own type
      * \param callVirtualBase [in] This paramater is don't used just api copatibility used.
      */
      virtual void visitAllEdges(const expression::DeclarationExpressionSyntax& node , bool callVirtualBase = true);

      /**
      * \internal
      * \brief It call the traversal for the edges
      * \param node            [in] The node with own type
      * \param callVirtualBase [in] This paramater is don't used just api copatibility used.
      */
      virtual void visitAllEdges(const expression::DefaultExpressionSyntax& node , bool callVirtualBase = true);

      /**
      * \internal
      * \brief It call the traversal for the edges
      * \param node            [in] The node with own type
      * \param callVirtualBase [in] This paramater is don't used just api copatibility used.
      */
      virtual void visitAllEdges(const expression::ElementAccessExpressionSyntax& node , bool callVirtualBase = true);

      /**
      * \internal
      * \brief It call the traversal for the edges
      * \param node            [in] The node with own type
      * \param callVirtualBase [in] This paramater is don't used just api copatibility used.
      */
      virtual void visitAllEdges(const expression::ElementBindingExpressionSyntax& node , bool callVirtualBase = true);

      /**
      * \internal
      * \brief It call the traversal for the edges
      * \param node            [in] The node with own type
      * \param callVirtualBase [in] This paramater is don't used just api copatibility used.
      */
      virtual void visitAllEdges(const expression::ExpressionSyntax& node , bool callVirtualBase = true);

      /**
      * \internal
      * \brief It call the traversal for the edges
      * \param node            [in] The node with own type
      * \param callVirtualBase [in] This paramater is don't used just api copatibility used.
      */
      virtual void visitAllEdges(const expression::GenericNameSyntax& node , bool callVirtualBase = true);

      /**
      * \internal
      * \brief It call the traversal for the edges
      * \param node            [in] The node with own type
      * \param callVirtualBase [in] This paramater is don't used just api copatibility used.
      */
      virtual void visitAllEdges(const expression::IdentifierNameSyntax& node , bool callVirtualBase = true);

      /**
      * \internal
      * \brief It call the traversal for the edges
      * \param node            [in] The node with own type
      * \param callVirtualBase [in] This paramater is don't used just api copatibility used.
      */
      virtual void visitAllEdges(const expression::ImplicitArrayCreationExpressionSyntax& node , bool callVirtualBase = true);

      /**
      * \internal
      * \brief It call the traversal for the edges
      * \param node            [in] The node with own type
      * \param callVirtualBase [in] This paramater is don't used just api copatibility used.
      */
      virtual void visitAllEdges(const expression::ImplicitElementAccessSyntax& node , bool callVirtualBase = true);

      /**
      * \internal
      * \brief It call the traversal for the edges
      * \param node            [in] The node with own type
      * \param callVirtualBase [in] This paramater is don't used just api copatibility used.
      */
      virtual void visitAllEdges(const expression::ImplicitStackAllocArrayCreationExpressionSyntax& node , bool callVirtualBase = true);

      /**
      * \internal
      * \brief It call the traversal for the edges
      * \param node            [in] The node with own type
      * \param callVirtualBase [in] This paramater is don't used just api copatibility used.
      */
      virtual void visitAllEdges(const expression::InitializerExpressionSyntax& node , bool callVirtualBase = true);

      /**
      * \internal
      * \brief It call the traversal for the edges
      * \param node            [in] The node with own type
      * \param callVirtualBase [in] This paramater is don't used just api copatibility used.
      */
      virtual void visitAllEdges(const expression::InstanceExpressionSyntax& node , bool callVirtualBase = true);

      /**
      * \internal
      * \brief It call the traversal for the edges
      * \param node            [in] The node with own type
      * \param callVirtualBase [in] This paramater is don't used just api copatibility used.
      */
      virtual void visitAllEdges(const expression::InterpolatedStringExpressionSyntax& node , bool callVirtualBase = true);

      /**
      * \internal
      * \brief It call the traversal for the edges
      * \param node            [in] The node with own type
      * \param callVirtualBase [in] This paramater is don't used just api copatibility used.
      */
      virtual void visitAllEdges(const expression::InvocationExpressionSyntax& node , bool callVirtualBase = true);

      /**
      * \internal
      * \brief It call the traversal for the edges
      * \param node            [in] The node with own type
      * \param callVirtualBase [in] This paramater is don't used just api copatibility used.
      */
      virtual void visitAllEdges(const expression::IsPatternExpressionSyntax& node , bool callVirtualBase = true);

      /**
      * \internal
      * \brief It call the traversal for the edges
      * \param node            [in] The node with own type
      * \param callVirtualBase [in] This paramater is don't used just api copatibility used.
      */
      virtual void visitAllEdges(const expression::LambdaExpressionSyntax& node , bool callVirtualBase = true);

      /**
      * \internal
      * \brief It call the traversal for the edges
      * \param node            [in] The node with own type
      * \param callVirtualBase [in] This paramater is don't used just api copatibility used.
      */
      virtual void visitAllEdges(const expression::LiteralExpressionSyntax& node , bool callVirtualBase = true);

      /**
      * \internal
      * \brief It call the traversal for the edges
      * \param node            [in] The node with own type
      * \param callVirtualBase [in] This paramater is don't used just api copatibility used.
      */
      virtual void visitAllEdges(const expression::MakeRefExpressionSyntax& node , bool callVirtualBase = true);

      /**
      * \internal
      * \brief It call the traversal for the edges
      * \param node            [in] The node with own type
      * \param callVirtualBase [in] This paramater is don't used just api copatibility used.
      */
      virtual void visitAllEdges(const expression::MemberAccessExpressionSyntax& node , bool callVirtualBase = true);

      /**
      * \internal
      * \brief It call the traversal for the edges
      * \param node            [in] The node with own type
      * \param callVirtualBase [in] This paramater is don't used just api copatibility used.
      */
      virtual void visitAllEdges(const expression::MemberBindingExpressionSyntax& node , bool callVirtualBase = true);

      /**
      * \internal
      * \brief It call the traversal for the edges
      * \param node            [in] The node with own type
      * \param callVirtualBase [in] This paramater is don't used just api copatibility used.
      */
      virtual void visitAllEdges(const expression::NameSyntax& node , bool callVirtualBase = true);

      /**
      * \internal
      * \brief It call the traversal for the edges
      * \param node            [in] The node with own type
      * \param callVirtualBase [in] This paramater is don't used just api copatibility used.
      */
      virtual void visitAllEdges(const expression::NullableTypeSyntax& node , bool callVirtualBase = true);

      /**
      * \internal
      * \brief It call the traversal for the edges
      * \param node            [in] The node with own type
      * \param callVirtualBase [in] This paramater is don't used just api copatibility used.
      */
      virtual void visitAllEdges(const expression::ObjectCreationExpressionSyntax& node , bool callVirtualBase = true);

      /**
      * \internal
      * \brief It call the traversal for the edges
      * \param node            [in] The node with own type
      * \param callVirtualBase [in] This paramater is don't used just api copatibility used.
      */
      virtual void visitAllEdges(const expression::OmittedArraySizeExpressionSyntax& node , bool callVirtualBase = true);

      /**
      * \internal
      * \brief It call the traversal for the edges
      * \param node            [in] The node with own type
      * \param callVirtualBase [in] This paramater is don't used just api copatibility used.
      */
      virtual void visitAllEdges(const expression::OmittedTypeArgumentSyntax& node , bool callVirtualBase = true);

      /**
      * \internal
      * \brief It call the traversal for the edges
      * \param node            [in] The node with own type
      * \param callVirtualBase [in] This paramater is don't used just api copatibility used.
      */
      virtual void visitAllEdges(const expression::ParenthesizedExpressionSyntax& node , bool callVirtualBase = true);

      /**
      * \internal
      * \brief It call the traversal for the edges
      * \param node            [in] The node with own type
      * \param callVirtualBase [in] This paramater is don't used just api copatibility used.
      */
      virtual void visitAllEdges(const expression::ParenthesizedLambdaExpressionSyntax& node , bool callVirtualBase = true);

      /**
      * \internal
      * \brief It call the traversal for the edges
      * \param node            [in] The node with own type
      * \param callVirtualBase [in] This paramater is don't used just api copatibility used.
      */
      virtual void visitAllEdges(const expression::PointerTypeSyntax& node , bool callVirtualBase = true);

      /**
      * \internal
      * \brief It call the traversal for the edges
      * \param node            [in] The node with own type
      * \param callVirtualBase [in] This paramater is don't used just api copatibility used.
      */
      virtual void visitAllEdges(const expression::PostfixUnaryExpressionSyntax& node , bool callVirtualBase = true);

      /**
      * \internal
      * \brief It call the traversal for the edges
      * \param node            [in] The node with own type
      * \param callVirtualBase [in] This paramater is don't used just api copatibility used.
      */
      virtual void visitAllEdges(const expression::PredefinedTypeSyntax& node , bool callVirtualBase = true);

      /**
      * \internal
      * \brief It call the traversal for the edges
      * \param node            [in] The node with own type
      * \param callVirtualBase [in] This paramater is don't used just api copatibility used.
      */
      virtual void visitAllEdges(const expression::PrefixUnaryExpressionSyntax& node , bool callVirtualBase = true);

      /**
      * \internal
      * \brief It call the traversal for the edges
      * \param node            [in] The node with own type
      * \param callVirtualBase [in] This paramater is don't used just api copatibility used.
      */
      virtual void visitAllEdges(const expression::QualifiedNameSyntax& node , bool callVirtualBase = true);

      /**
      * \internal
      * \brief It call the traversal for the edges
      * \param node            [in] The node with own type
      * \param callVirtualBase [in] This paramater is don't used just api copatibility used.
      */
      virtual void visitAllEdges(const expression::QueryExpressionSyntax& node , bool callVirtualBase = true);

      /**
      * \internal
      * \brief It call the traversal for the edges
      * \param node            [in] The node with own type
      * \param callVirtualBase [in] This paramater is don't used just api copatibility used.
      */
      virtual void visitAllEdges(const expression::RangeExpressionSyntax& node , bool callVirtualBase = true);

      /**
      * \internal
      * \brief It call the traversal for the edges
      * \param node            [in] The node with own type
      * \param callVirtualBase [in] This paramater is don't used just api copatibility used.
      */
      virtual void visitAllEdges(const expression::RefExpressionSyntax& node , bool callVirtualBase = true);

      /**
      * \internal
      * \brief It call the traversal for the edges
      * \param node            [in] The node with own type
      * \param callVirtualBase [in] This paramater is don't used just api copatibility used.
      */
      virtual void visitAllEdges(const expression::RefTypeExpressionSyntax& node , bool callVirtualBase = true);

      /**
      * \internal
      * \brief It call the traversal for the edges
      * \param node            [in] The node with own type
      * \param callVirtualBase [in] This paramater is don't used just api copatibility used.
      */
      virtual void visitAllEdges(const expression::RefTypeSyntax& node , bool callVirtualBase = true);

      /**
      * \internal
      * \brief It call the traversal for the edges
      * \param node            [in] The node with own type
      * \param callVirtualBase [in] This paramater is don't used just api copatibility used.
      */
      virtual void visitAllEdges(const expression::RefValueExpressionSyntax& node , bool callVirtualBase = true);

      /**
      * \internal
      * \brief It call the traversal for the edges
      * \param node            [in] The node with own type
      * \param callVirtualBase [in] This paramater is don't used just api copatibility used.
      */
      virtual void visitAllEdges(const expression::SimpleLambdaExpressionSyntax& node , bool callVirtualBase = true);

      /**
      * \internal
      * \brief It call the traversal for the edges
      * \param node            [in] The node with own type
      * \param callVirtualBase [in] This paramater is don't used just api copatibility used.
      */
      virtual void visitAllEdges(const expression::SimpleNameSyntax& node , bool callVirtualBase = true);

      /**
      * \internal
      * \brief It call the traversal for the edges
      * \param node            [in] The node with own type
      * \param callVirtualBase [in] This paramater is don't used just api copatibility used.
      */
      virtual void visitAllEdges(const expression::SizeOfExpressionSyntax& node , bool callVirtualBase = true);

      /**
      * \internal
      * \brief It call the traversal for the edges
      * \param node            [in] The node with own type
      * \param callVirtualBase [in] This paramater is don't used just api copatibility used.
      */
      virtual void visitAllEdges(const expression::StackAllocArrayCreationExpressionSyntax& node , bool callVirtualBase = true);

      /**
      * \internal
      * \brief It call the traversal for the edges
      * \param node            [in] The node with own type
      * \param callVirtualBase [in] This paramater is don't used just api copatibility used.
      */
      virtual void visitAllEdges(const expression::SwitchExpressionSyntax& node , bool callVirtualBase = true);

      /**
      * \internal
      * \brief It call the traversal for the edges
      * \param node            [in] The node with own type
      * \param callVirtualBase [in] This paramater is don't used just api copatibility used.
      */
      virtual void visitAllEdges(const expression::ThisExpressionSyntax& node , bool callVirtualBase = true);

      /**
      * \internal
      * \brief It call the traversal for the edges
      * \param node            [in] The node with own type
      * \param callVirtualBase [in] This paramater is don't used just api copatibility used.
      */
      virtual void visitAllEdges(const expression::ThrowExpressionSyntax& node , bool callVirtualBase = true);

      /**
      * \internal
      * \brief It call the traversal for the edges
      * \param node            [in] The node with own type
      * \param callVirtualBase [in] This paramater is don't used just api copatibility used.
      */
      virtual void visitAllEdges(const expression::TupleExpressionSyntax& node , bool callVirtualBase = true);

      /**
      * \internal
      * \brief It call the traversal for the edges
      * \param node            [in] The node with own type
      * \param callVirtualBase [in] This paramater is don't used just api copatibility used.
      */
      virtual void visitAllEdges(const expression::TupleTypeSyntax& node , bool callVirtualBase = true);

      /**
      * \internal
      * \brief It call the traversal for the edges
      * \param node            [in] The node with own type
      * \param callVirtualBase [in] This paramater is don't used just api copatibility used.
      */
      virtual void visitAllEdges(const expression::TypeOfExpressionSyntax& node , bool callVirtualBase = true);

      /**
      * \internal
      * \brief It call the traversal for the edges
      * \param node            [in] The node with own type
      * \param callVirtualBase [in] This paramater is don't used just api copatibility used.
      */
      virtual void visitAllEdges(const expression::TypeSyntax& node , bool callVirtualBase = true);

      /**
      * \internal
      * \brief It call the traversal for the edges
      * \param node            [in] The node with own type
      * \param callVirtualBase [in] This paramater is don't used just api copatibility used.
      */
      virtual void visitAllEdges(const statement::BlockSyntax& node , bool callVirtualBase = true);

      /**
      * \internal
      * \brief It call the traversal for the edges
      * \param node            [in] The node with own type
      * \param callVirtualBase [in] This paramater is don't used just api copatibility used.
      */
      virtual void visitAllEdges(const statement::BreakStatementSyntax& node , bool callVirtualBase = true);

      /**
      * \internal
      * \brief It call the traversal for the edges
      * \param node            [in] The node with own type
      * \param callVirtualBase [in] This paramater is don't used just api copatibility used.
      */
      virtual void visitAllEdges(const statement::CheckedStatementSyntax& node , bool callVirtualBase = true);

      /**
      * \internal
      * \brief It call the traversal for the edges
      * \param node            [in] The node with own type
      * \param callVirtualBase [in] This paramater is don't used just api copatibility used.
      */
      virtual void visitAllEdges(const statement::CommonForEachStatementSyntax& node , bool callVirtualBase = true);

      /**
      * \internal
      * \brief It call the traversal for the edges
      * \param node            [in] The node with own type
      * \param callVirtualBase [in] This paramater is don't used just api copatibility used.
      */
      virtual void visitAllEdges(const statement::ContinueStatementSyntax& node , bool callVirtualBase = true);

      /**
      * \internal
      * \brief It call the traversal for the edges
      * \param node            [in] The node with own type
      * \param callVirtualBase [in] This paramater is don't used just api copatibility used.
      */
      virtual void visitAllEdges(const statement::DoStatementSyntax& node , bool callVirtualBase = true);

      /**
      * \internal
      * \brief It call the traversal for the edges
      * \param node            [in] The node with own type
      * \param callVirtualBase [in] This paramater is don't used just api copatibility used.
      */
      virtual void visitAllEdges(const statement::EmptyStatementSyntax& node , bool callVirtualBase = true);

      /**
      * \internal
      * \brief It call the traversal for the edges
      * \param node            [in] The node with own type
      * \param callVirtualBase [in] This paramater is don't used just api copatibility used.
      */
      virtual void visitAllEdges(const statement::ExpressionStatementSyntax& node , bool callVirtualBase = true);

      /**
      * \internal
      * \brief It call the traversal for the edges
      * \param node            [in] The node with own type
      * \param callVirtualBase [in] This paramater is don't used just api copatibility used.
      */
      virtual void visitAllEdges(const statement::FixedStatementSyntax& node , bool callVirtualBase = true);

      /**
      * \internal
      * \brief It call the traversal for the edges
      * \param node            [in] The node with own type
      * \param callVirtualBase [in] This paramater is don't used just api copatibility used.
      */
      virtual void visitAllEdges(const statement::ForEachStatementSyntax& node , bool callVirtualBase = true);

      /**
      * \internal
      * \brief It call the traversal for the edges
      * \param node            [in] The node with own type
      * \param callVirtualBase [in] This paramater is don't used just api copatibility used.
      */
      virtual void visitAllEdges(const statement::ForEachVariableStatementSyntax& node , bool callVirtualBase = true);

      /**
      * \internal
      * \brief It call the traversal for the edges
      * \param node            [in] The node with own type
      * \param callVirtualBase [in] This paramater is don't used just api copatibility used.
      */
      virtual void visitAllEdges(const statement::ForStatementSyntax& node , bool callVirtualBase = true);

      /**
      * \internal
      * \brief It call the traversal for the edges
      * \param node            [in] The node with own type
      * \param callVirtualBase [in] This paramater is don't used just api copatibility used.
      */
      virtual void visitAllEdges(const statement::GotoStatementSyntax& node , bool callVirtualBase = true);

      /**
      * \internal
      * \brief It call the traversal for the edges
      * \param node            [in] The node with own type
      * \param callVirtualBase [in] This paramater is don't used just api copatibility used.
      */
      virtual void visitAllEdges(const statement::IfStatementSyntax& node , bool callVirtualBase = true);

      /**
      * \internal
      * \brief It call the traversal for the edges
      * \param node            [in] The node with own type
      * \param callVirtualBase [in] This paramater is don't used just api copatibility used.
      */
      virtual void visitAllEdges(const statement::LabeledStatementSyntax& node , bool callVirtualBase = true);

      /**
      * \internal
      * \brief It call the traversal for the edges
      * \param node            [in] The node with own type
      * \param callVirtualBase [in] This paramater is don't used just api copatibility used.
      */
      virtual void visitAllEdges(const statement::LocalDeclarationStatementSyntax& node , bool callVirtualBase = true);

      /**
      * \internal
      * \brief It call the traversal for the edges
      * \param node            [in] The node with own type
      * \param callVirtualBase [in] This paramater is don't used just api copatibility used.
      */
      virtual void visitAllEdges(const statement::LocalFunctionStatementSyntax& node , bool callVirtualBase = true);

      /**
      * \internal
      * \brief It call the traversal for the edges
      * \param node            [in] The node with own type
      * \param callVirtualBase [in] This paramater is don't used just api copatibility used.
      */
      virtual void visitAllEdges(const statement::LockStatementSyntax& node , bool callVirtualBase = true);

      /**
      * \internal
      * \brief It call the traversal for the edges
      * \param node            [in] The node with own type
      * \param callVirtualBase [in] This paramater is don't used just api copatibility used.
      */
      virtual void visitAllEdges(const statement::ReturnStatementSyntax& node , bool callVirtualBase = true);

      /**
      * \internal
      * \brief It call the traversal for the edges
      * \param node            [in] The node with own type
      * \param callVirtualBase [in] This paramater is don't used just api copatibility used.
      */
      virtual void visitAllEdges(const statement::StatementSyntax& node , bool callVirtualBase = true);

      /**
      * \internal
      * \brief It call the traversal for the edges
      * \param node            [in] The node with own type
      * \param callVirtualBase [in] This paramater is don't used just api copatibility used.
      */
      virtual void visitAllEdges(const statement::SwitchStatementSyntax& node , bool callVirtualBase = true);

      /**
      * \internal
      * \brief It call the traversal for the edges
      * \param node            [in] The node with own type
      * \param callVirtualBase [in] This paramater is don't used just api copatibility used.
      */
      virtual void visitAllEdges(const statement::ThrowStatementSyntax& node , bool callVirtualBase = true);

      /**
      * \internal
      * \brief It call the traversal for the edges
      * \param node            [in] The node with own type
      * \param callVirtualBase [in] This paramater is don't used just api copatibility used.
      */
      virtual void visitAllEdges(const statement::TryStatementSyntax& node , bool callVirtualBase = true);

      /**
      * \internal
      * \brief It call the traversal for the edges
      * \param node            [in] The node with own type
      * \param callVirtualBase [in] This paramater is don't used just api copatibility used.
      */
      virtual void visitAllEdges(const statement::UnsafeStatementSyntax& node , bool callVirtualBase = true);

      /**
      * \internal
      * \brief It call the traversal for the edges
      * \param node            [in] The node with own type
      * \param callVirtualBase [in] This paramater is don't used just api copatibility used.
      */
      virtual void visitAllEdges(const statement::UsingStatementSyntax& node , bool callVirtualBase = true);

      /**
      * \internal
      * \brief It call the traversal for the edges
      * \param node            [in] The node with own type
      * \param callVirtualBase [in] This paramater is don't used just api copatibility used.
      */
      virtual void visitAllEdges(const statement::WhileStatementSyntax& node , bool callVirtualBase = true);

      /**
      * \internal
      * \brief It call the traversal for the edges
      * \param node            [in] The node with own type
      * \param callVirtualBase [in] This paramater is don't used just api copatibility used.
      */
      virtual void visitAllEdges(const statement::YieldStatementSyntax& node , bool callVirtualBase = true);

      /**
      * \internal
      * \brief It call the traversal for the edges
      * \param node            [in] The node with own type
      * \param callVirtualBase [in] This paramater is don't used just api copatibility used.
      */
      virtual void visitAllEdges(const structure::AccessorDeclarationSyntax& node , bool callVirtualBase = true);

      /**
      * \internal
      * \brief It call the traversal for the edges
      * \param node            [in] The node with own type
      * \param callVirtualBase [in] This paramater is don't used just api copatibility used.
      */
      virtual void visitAllEdges(const structure::AccessorListSyntax& node , bool callVirtualBase = true);

      /**
      * \internal
      * \brief It call the traversal for the edges
      * \param node            [in] The node with own type
      * \param callVirtualBase [in] This paramater is don't used just api copatibility used.
      */
      virtual void visitAllEdges(const structure::AnonymousObjectMemberDeclaratorSyntax& node , bool callVirtualBase = true);

      /**
      * \internal
      * \brief It call the traversal for the edges
      * \param node            [in] The node with own type
      * \param callVirtualBase [in] This paramater is don't used just api copatibility used.
      */
      virtual void visitAllEdges(const structure::ArgumentListSyntax& node , bool callVirtualBase = true);

      /**
      * \internal
      * \brief It call the traversal for the edges
      * \param node            [in] The node with own type
      * \param callVirtualBase [in] This paramater is don't used just api copatibility used.
      */
      virtual void visitAllEdges(const structure::ArgumentSyntax& node , bool callVirtualBase = true);

      /**
      * \internal
      * \brief It call the traversal for the edges
      * \param node            [in] The node with own type
      * \param callVirtualBase [in] This paramater is don't used just api copatibility used.
      */
      virtual void visitAllEdges(const structure::ArrayRankSpecifierSyntax& node , bool callVirtualBase = true);

      /**
      * \internal
      * \brief It call the traversal for the edges
      * \param node            [in] The node with own type
      * \param callVirtualBase [in] This paramater is don't used just api copatibility used.
      */
      virtual void visitAllEdges(const structure::ArrowExpressionClauseSyntax& node , bool callVirtualBase = true);

      /**
      * \internal
      * \brief It call the traversal for the edges
      * \param node            [in] The node with own type
      * \param callVirtualBase [in] This paramater is don't used just api copatibility used.
      */
      virtual void visitAllEdges(const structure::AttributeArgumentListSyntax& node , bool callVirtualBase = true);

      /**
      * \internal
      * \brief It call the traversal for the edges
      * \param node            [in] The node with own type
      * \param callVirtualBase [in] This paramater is don't used just api copatibility used.
      */
      virtual void visitAllEdges(const structure::AttributeArgumentSyntax& node , bool callVirtualBase = true);

      /**
      * \internal
      * \brief It call the traversal for the edges
      * \param node            [in] The node with own type
      * \param callVirtualBase [in] This paramater is don't used just api copatibility used.
      */
      virtual void visitAllEdges(const structure::AttributeListSyntax& node , bool callVirtualBase = true);

      /**
      * \internal
      * \brief It call the traversal for the edges
      * \param node            [in] The node with own type
      * \param callVirtualBase [in] This paramater is don't used just api copatibility used.
      */
      virtual void visitAllEdges(const structure::AttributeSyntax& node , bool callVirtualBase = true);

      /**
      * \internal
      * \brief It call the traversal for the edges
      * \param node            [in] The node with own type
      * \param callVirtualBase [in] This paramater is don't used just api copatibility used.
      */
      virtual void visitAllEdges(const structure::AttributeTargetSpecifierSyntax& node , bool callVirtualBase = true);

      /**
      * \internal
      * \brief It call the traversal for the edges
      * \param node            [in] The node with own type
      * \param callVirtualBase [in] This paramater is don't used just api copatibility used.
      */
      virtual void visitAllEdges(const structure::BaseArgumentListSyntax& node , bool callVirtualBase = true);

      /**
      * \internal
      * \brief It call the traversal for the edges
      * \param node            [in] The node with own type
      * \param callVirtualBase [in] This paramater is don't used just api copatibility used.
      */
      virtual void visitAllEdges(const structure::BaseCrefParameterListSyntax& node , bool callVirtualBase = true);

      /**
      * \internal
      * \brief It call the traversal for the edges
      * \param node            [in] The node with own type
      * \param callVirtualBase [in] This paramater is don't used just api copatibility used.
      */
      virtual void visitAllEdges(const structure::BaseFieldDeclarationSyntax& node , bool callVirtualBase = true);

      /**
      * \internal
      * \brief It call the traversal for the edges
      * \param node            [in] The node with own type
      * \param callVirtualBase [in] This paramater is don't used just api copatibility used.
      */
      virtual void visitAllEdges(const structure::BaseListSyntax& node , bool callVirtualBase = true);

      /**
      * \internal
      * \brief It call the traversal for the edges
      * \param node            [in] The node with own type
      * \param callVirtualBase [in] This paramater is don't used just api copatibility used.
      */
      virtual void visitAllEdges(const structure::BaseMethodDeclarationSyntax& node , bool callVirtualBase = true);

      /**
      * \internal
      * \brief It call the traversal for the edges
      * \param node            [in] The node with own type
      * \param callVirtualBase [in] This paramater is don't used just api copatibility used.
      */
      virtual void visitAllEdges(const structure::BaseParameterListSyntax& node , bool callVirtualBase = true);

      /**
      * \internal
      * \brief It call the traversal for the edges
      * \param node            [in] The node with own type
      * \param callVirtualBase [in] This paramater is don't used just api copatibility used.
      */
      virtual void visitAllEdges(const structure::BasePropertyDeclarationSyntax& node , bool callVirtualBase = true);

      /**
      * \internal
      * \brief It call the traversal for the edges
      * \param node            [in] The node with own type
      * \param callVirtualBase [in] This paramater is don't used just api copatibility used.
      */
      virtual void visitAllEdges(const structure::BaseTypeDeclarationSyntax& node , bool callVirtualBase = true);

      /**
      * \internal
      * \brief It call the traversal for the edges
      * \param node            [in] The node with own type
      * \param callVirtualBase [in] This paramater is don't used just api copatibility used.
      */
      virtual void visitAllEdges(const structure::BaseTypeSyntax& node , bool callVirtualBase = true);

      /**
      * \internal
      * \brief It call the traversal for the edges
      * \param node            [in] The node with own type
      * \param callVirtualBase [in] This paramater is don't used just api copatibility used.
      */
      virtual void visitAllEdges(const structure::BracketedArgumentListSyntax& node , bool callVirtualBase = true);

      /**
      * \internal
      * \brief It call the traversal for the edges
      * \param node            [in] The node with own type
      * \param callVirtualBase [in] This paramater is don't used just api copatibility used.
      */
      virtual void visitAllEdges(const structure::BracketedParameterListSyntax& node , bool callVirtualBase = true);

      /**
      * \internal
      * \brief It call the traversal for the edges
      * \param node            [in] The node with own type
      * \param callVirtualBase [in] This paramater is don't used just api copatibility used.
      */
      virtual void visitAllEdges(const structure::CasePatternSwitchLabelSyntax& node , bool callVirtualBase = true);

      /**
      * \internal
      * \brief It call the traversal for the edges
      * \param node            [in] The node with own type
      * \param callVirtualBase [in] This paramater is don't used just api copatibility used.
      */
      virtual void visitAllEdges(const structure::CaseSwitchLabelSyntax& node , bool callVirtualBase = true);

      /**
      * \internal
      * \brief It call the traversal for the edges
      * \param node            [in] The node with own type
      * \param callVirtualBase [in] This paramater is don't used just api copatibility used.
      */
      virtual void visitAllEdges(const structure::CatchClauseSyntax& node , bool callVirtualBase = true);

      /**
      * \internal
      * \brief It call the traversal for the edges
      * \param node            [in] The node with own type
      * \param callVirtualBase [in] This paramater is don't used just api copatibility used.
      */
      virtual void visitAllEdges(const structure::CatchDeclarationSyntax& node , bool callVirtualBase = true);

      /**
      * \internal
      * \brief It call the traversal for the edges
      * \param node            [in] The node with own type
      * \param callVirtualBase [in] This paramater is don't used just api copatibility used.
      */
      virtual void visitAllEdges(const structure::CatchFilterClauseSyntax& node , bool callVirtualBase = true);

      /**
      * \internal
      * \brief It call the traversal for the edges
      * \param node            [in] The node with own type
      * \param callVirtualBase [in] This paramater is don't used just api copatibility used.
      */
      virtual void visitAllEdges(const structure::ClassDeclarationSyntax& node , bool callVirtualBase = true);

      /**
      * \internal
      * \brief It call the traversal for the edges
      * \param node            [in] The node with own type
      * \param callVirtualBase [in] This paramater is don't used just api copatibility used.
      */
      virtual void visitAllEdges(const structure::ClassOrStructConstraintSyntax& node , bool callVirtualBase = true);

      /**
      * \internal
      * \brief It call the traversal for the edges
      * \param node            [in] The node with own type
      * \param callVirtualBase [in] This paramater is don't used just api copatibility used.
      */
      virtual void visitAllEdges(const structure::CompilationUnitSyntax& node , bool callVirtualBase = true);

      /**
      * \internal
      * \brief It call the traversal for the edges
      * \param node            [in] The node with own type
      * \param callVirtualBase [in] This paramater is don't used just api copatibility used.
      */
      virtual void visitAllEdges(const structure::ConstantPatternSyntax& node , bool callVirtualBase = true);

      /**
      * \internal
      * \brief It call the traversal for the edges
      * \param node            [in] The node with own type
      * \param callVirtualBase [in] This paramater is don't used just api copatibility used.
      */
      virtual void visitAllEdges(const structure::ConstructorConstraintSyntax& node , bool callVirtualBase = true);

      /**
      * \internal
      * \brief It call the traversal for the edges
      * \param node            [in] The node with own type
      * \param callVirtualBase [in] This paramater is don't used just api copatibility used.
      */
      virtual void visitAllEdges(const structure::ConstructorDeclarationSyntax& node , bool callVirtualBase = true);

      /**
      * \internal
      * \brief It call the traversal for the edges
      * \param node            [in] The node with own type
      * \param callVirtualBase [in] This paramater is don't used just api copatibility used.
      */
      virtual void visitAllEdges(const structure::ConstructorInitializerSyntax& node , bool callVirtualBase = true);

      /**
      * \internal
      * \brief It call the traversal for the edges
      * \param node            [in] The node with own type
      * \param callVirtualBase [in] This paramater is don't used just api copatibility used.
      */
      virtual void visitAllEdges(const structure::ConversionOperatorDeclarationSyntax& node , bool callVirtualBase = true);

      /**
      * \internal
      * \brief It call the traversal for the edges
      * \param node            [in] The node with own type
      * \param callVirtualBase [in] This paramater is don't used just api copatibility used.
      */
      virtual void visitAllEdges(const structure::ConversionOperatorMemberCrefSyntax& node , bool callVirtualBase = true);

      /**
      * \internal
      * \brief It call the traversal for the edges
      * \param node            [in] The node with own type
      * \param callVirtualBase [in] This paramater is don't used just api copatibility used.
      */
      virtual void visitAllEdges(const structure::CrefBracketedParameterListSyntax& node , bool callVirtualBase = true);

      /**
      * \internal
      * \brief It call the traversal for the edges
      * \param node            [in] The node with own type
      * \param callVirtualBase [in] This paramater is don't used just api copatibility used.
      */
      virtual void visitAllEdges(const structure::CrefParameterListSyntax& node , bool callVirtualBase = true);

      /**
      * \internal
      * \brief It call the traversal for the edges
      * \param node            [in] The node with own type
      * \param callVirtualBase [in] This paramater is don't used just api copatibility used.
      */
      virtual void visitAllEdges(const structure::CrefParameterSyntax& node , bool callVirtualBase = true);

      /**
      * \internal
      * \brief It call the traversal for the edges
      * \param node            [in] The node with own type
      * \param callVirtualBase [in] This paramater is don't used just api copatibility used.
      */
      virtual void visitAllEdges(const structure::CrefSyntax& node , bool callVirtualBase = true);

      /**
      * \internal
      * \brief It call the traversal for the edges
      * \param node            [in] The node with own type
      * \param callVirtualBase [in] This paramater is don't used just api copatibility used.
      */
      virtual void visitAllEdges(const structure::DeclarationPatternSyntax& node , bool callVirtualBase = true);

      /**
      * \internal
      * \brief It call the traversal for the edges
      * \param node            [in] The node with own type
      * \param callVirtualBase [in] This paramater is don't used just api copatibility used.
      */
      virtual void visitAllEdges(const structure::DefaultSwitchLabelSyntax& node , bool callVirtualBase = true);

      /**
      * \internal
      * \brief It call the traversal for the edges
      * \param node            [in] The node with own type
      * \param callVirtualBase [in] This paramater is don't used just api copatibility used.
      */
      virtual void visitAllEdges(const structure::DelegateDeclarationSyntax& node , bool callVirtualBase = true);

      /**
      * \internal
      * \brief It call the traversal for the edges
      * \param node            [in] The node with own type
      * \param callVirtualBase [in] This paramater is don't used just api copatibility used.
      */
      virtual void visitAllEdges(const structure::DestructorDeclarationSyntax& node , bool callVirtualBase = true);

      /**
      * \internal
      * \brief It call the traversal for the edges
      * \param node            [in] The node with own type
      * \param callVirtualBase [in] This paramater is don't used just api copatibility used.
      */
      virtual void visitAllEdges(const structure::DiscardDesignationSyntax& node , bool callVirtualBase = true);

      /**
      * \internal
      * \brief It call the traversal for the edges
      * \param node            [in] The node with own type
      * \param callVirtualBase [in] This paramater is don't used just api copatibility used.
      */
      virtual void visitAllEdges(const structure::DiscardPatternSyntax& node , bool callVirtualBase = true);

      /**
      * \internal
      * \brief It call the traversal for the edges
      * \param node            [in] The node with own type
      * \param callVirtualBase [in] This paramater is don't used just api copatibility used.
      */
      virtual void visitAllEdges(const structure::ElseClauseSyntax& node , bool callVirtualBase = true);

      /**
      * \internal
      * \brief It call the traversal for the edges
      * \param node            [in] The node with own type
      * \param callVirtualBase [in] This paramater is don't used just api copatibility used.
      */
      virtual void visitAllEdges(const structure::EnumDeclarationSyntax& node , bool callVirtualBase = true);

      /**
      * \internal
      * \brief It call the traversal for the edges
      * \param node            [in] The node with own type
      * \param callVirtualBase [in] This paramater is don't used just api copatibility used.
      */
      virtual void visitAllEdges(const structure::EnumMemberDeclarationSyntax& node , bool callVirtualBase = true);

      /**
      * \internal
      * \brief It call the traversal for the edges
      * \param node            [in] The node with own type
      * \param callVirtualBase [in] This paramater is don't used just api copatibility used.
      */
      virtual void visitAllEdges(const structure::EqualsValueClauseSyntax& node , bool callVirtualBase = true);

      /**
      * \internal
      * \brief It call the traversal for the edges
      * \param node            [in] The node with own type
      * \param callVirtualBase [in] This paramater is don't used just api copatibility used.
      */
      virtual void visitAllEdges(const structure::EventDeclarationSyntax& node , bool callVirtualBase = true);

      /**
      * \internal
      * \brief It call the traversal for the edges
      * \param node            [in] The node with own type
      * \param callVirtualBase [in] This paramater is don't used just api copatibility used.
      */
      virtual void visitAllEdges(const structure::EventFieldDeclarationSyntax& node , bool callVirtualBase = true);

      /**
      * \internal
      * \brief It call the traversal for the edges
      * \param node            [in] The node with own type
      * \param callVirtualBase [in] This paramater is don't used just api copatibility used.
      */
      virtual void visitAllEdges(const structure::ExplicitInterfaceSpecifierSyntax& node , bool callVirtualBase = true);

      /**
      * \internal
      * \brief It call the traversal for the edges
      * \param node            [in] The node with own type
      * \param callVirtualBase [in] This paramater is don't used just api copatibility used.
      */
      virtual void visitAllEdges(const structure::ExternAliasDirectiveSyntax& node , bool callVirtualBase = true);

      /**
      * \internal
      * \brief It call the traversal for the edges
      * \param node            [in] The node with own type
      * \param callVirtualBase [in] This paramater is don't used just api copatibility used.
      */
      virtual void visitAllEdges(const structure::FieldDeclarationSyntax& node , bool callVirtualBase = true);

      /**
      * \internal
      * \brief It call the traversal for the edges
      * \param node            [in] The node with own type
      * \param callVirtualBase [in] This paramater is don't used just api copatibility used.
      */
      virtual void visitAllEdges(const structure::FinallyClauseSyntax& node , bool callVirtualBase = true);

      /**
      * \internal
      * \brief It call the traversal for the edges
      * \param node            [in] The node with own type
      * \param callVirtualBase [in] This paramater is don't used just api copatibility used.
      */
      virtual void visitAllEdges(const structure::FromClauseSyntax& node , bool callVirtualBase = true);

      /**
      * \internal
      * \brief It call the traversal for the edges
      * \param node            [in] The node with own type
      * \param callVirtualBase [in] This paramater is don't used just api copatibility used.
      */
      virtual void visitAllEdges(const structure::GlobalStatementSyntax& node , bool callVirtualBase = true);

      /**
      * \internal
      * \brief It call the traversal for the edges
      * \param node            [in] The node with own type
      * \param callVirtualBase [in] This paramater is don't used just api copatibility used.
      */
      virtual void visitAllEdges(const structure::GroupClauseSyntax& node , bool callVirtualBase = true);

      /**
      * \internal
      * \brief It call the traversal for the edges
      * \param node            [in] The node with own type
      * \param callVirtualBase [in] This paramater is don't used just api copatibility used.
      */
      virtual void visitAllEdges(const structure::IncompleteMemberSyntax& node , bool callVirtualBase = true);

      /**
      * \internal
      * \brief It call the traversal for the edges
      * \param node            [in] The node with own type
      * \param callVirtualBase [in] This paramater is don't used just api copatibility used.
      */
      virtual void visitAllEdges(const structure::IndexerDeclarationSyntax& node , bool callVirtualBase = true);

      /**
      * \internal
      * \brief It call the traversal for the edges
      * \param node            [in] The node with own type
      * \param callVirtualBase [in] This paramater is don't used just api copatibility used.
      */
      virtual void visitAllEdges(const structure::IndexerMemberCrefSyntax& node , bool callVirtualBase = true);

      /**
      * \internal
      * \brief It call the traversal for the edges
      * \param node            [in] The node with own type
      * \param callVirtualBase [in] This paramater is don't used just api copatibility used.
      */
      virtual void visitAllEdges(const structure::InterfaceDeclarationSyntax& node , bool callVirtualBase = true);

      /**
      * \internal
      * \brief It call the traversal for the edges
      * \param node            [in] The node with own type
      * \param callVirtualBase [in] This paramater is don't used just api copatibility used.
      */
      virtual void visitAllEdges(const structure::InterpolatedStringContentSyntax& node , bool callVirtualBase = true);

      /**
      * \internal
      * \brief It call the traversal for the edges
      * \param node            [in] The node with own type
      * \param callVirtualBase [in] This paramater is don't used just api copatibility used.
      */
      virtual void visitAllEdges(const structure::InterpolatedStringTextSyntax& node , bool callVirtualBase = true);

      /**
      * \internal
      * \brief It call the traversal for the edges
      * \param node            [in] The node with own type
      * \param callVirtualBase [in] This paramater is don't used just api copatibility used.
      */
      virtual void visitAllEdges(const structure::InterpolationAlignmentClauseSyntax& node , bool callVirtualBase = true);

      /**
      * \internal
      * \brief It call the traversal for the edges
      * \param node            [in] The node with own type
      * \param callVirtualBase [in] This paramater is don't used just api copatibility used.
      */
      virtual void visitAllEdges(const structure::InterpolationFormatClauseSyntax& node , bool callVirtualBase = true);

      /**
      * \internal
      * \brief It call the traversal for the edges
      * \param node            [in] The node with own type
      * \param callVirtualBase [in] This paramater is don't used just api copatibility used.
      */
      virtual void visitAllEdges(const structure::InterpolationSyntax& node , bool callVirtualBase = true);

      /**
      * \internal
      * \brief It call the traversal for the edges
      * \param node            [in] The node with own type
      * \param callVirtualBase [in] This paramater is don't used just api copatibility used.
      */
      virtual void visitAllEdges(const structure::JoinClauseSyntax& node , bool callVirtualBase = true);

      /**
      * \internal
      * \brief It call the traversal for the edges
      * \param node            [in] The node with own type
      * \param callVirtualBase [in] This paramater is don't used just api copatibility used.
      */
      virtual void visitAllEdges(const structure::JoinIntoClauseSyntax& node , bool callVirtualBase = true);

      /**
      * \internal
      * \brief It call the traversal for the edges
      * \param node            [in] The node with own type
      * \param callVirtualBase [in] This paramater is don't used just api copatibility used.
      */
      virtual void visitAllEdges(const structure::LetClauseSyntax& node , bool callVirtualBase = true);

      /**
      * \internal
      * \brief It call the traversal for the edges
      * \param node            [in] The node with own type
      * \param callVirtualBase [in] This paramater is don't used just api copatibility used.
      */
      virtual void visitAllEdges(const structure::MemberCrefSyntax& node , bool callVirtualBase = true);

      /**
      * \internal
      * \brief It call the traversal for the edges
      * \param node            [in] The node with own type
      * \param callVirtualBase [in] This paramater is don't used just api copatibility used.
      */
      virtual void visitAllEdges(const structure::MemberDeclarationSyntax& node , bool callVirtualBase = true);

      /**
      * \internal
      * \brief It call the traversal for the edges
      * \param node            [in] The node with own type
      * \param callVirtualBase [in] This paramater is don't used just api copatibility used.
      */
      virtual void visitAllEdges(const structure::MethodDeclarationSyntax& node , bool callVirtualBase = true);

      /**
      * \internal
      * \brief It call the traversal for the edges
      * \param node            [in] The node with own type
      * \param callVirtualBase [in] This paramater is don't used just api copatibility used.
      */
      virtual void visitAllEdges(const structure::NameColonSyntax& node , bool callVirtualBase = true);

      /**
      * \internal
      * \brief It call the traversal for the edges
      * \param node            [in] The node with own type
      * \param callVirtualBase [in] This paramater is don't used just api copatibility used.
      */
      virtual void visitAllEdges(const structure::NameEqualsSyntax& node , bool callVirtualBase = true);

      /**
      * \internal
      * \brief It call the traversal for the edges
      * \param node            [in] The node with own type
      * \param callVirtualBase [in] This paramater is don't used just api copatibility used.
      */
      virtual void visitAllEdges(const structure::NameMemberCrefSyntax& node , bool callVirtualBase = true);

      /**
      * \internal
      * \brief It call the traversal for the edges
      * \param node            [in] The node with own type
      * \param callVirtualBase [in] This paramater is don't used just api copatibility used.
      */
      virtual void visitAllEdges(const structure::NamespaceDeclarationSyntax& node , bool callVirtualBase = true);

      /**
      * \internal
      * \brief It call the traversal for the edges
      * \param node            [in] The node with own type
      * \param callVirtualBase [in] This paramater is don't used just api copatibility used.
      */
      virtual void visitAllEdges(const structure::OperatorDeclarationSyntax& node , bool callVirtualBase = true);

      /**
      * \internal
      * \brief It call the traversal for the edges
      * \param node            [in] The node with own type
      * \param callVirtualBase [in] This paramater is don't used just api copatibility used.
      */
      virtual void visitAllEdges(const structure::OperatorMemberCrefSyntax& node , bool callVirtualBase = true);

      /**
      * \internal
      * \brief It call the traversal for the edges
      * \param node            [in] The node with own type
      * \param callVirtualBase [in] This paramater is don't used just api copatibility used.
      */
      virtual void visitAllEdges(const structure::OrderByClauseSyntax& node , bool callVirtualBase = true);

      /**
      * \internal
      * \brief It call the traversal for the edges
      * \param node            [in] The node with own type
      * \param callVirtualBase [in] This paramater is don't used just api copatibility used.
      */
      virtual void visitAllEdges(const structure::OrderingSyntax& node , bool callVirtualBase = true);

      /**
      * \internal
      * \brief It call the traversal for the edges
      * \param node            [in] The node with own type
      * \param callVirtualBase [in] This paramater is don't used just api copatibility used.
      */
      virtual void visitAllEdges(const structure::ParameterListSyntax& node , bool callVirtualBase = true);

      /**
      * \internal
      * \brief It call the traversal for the edges
      * \param node            [in] The node with own type
      * \param callVirtualBase [in] This paramater is don't used just api copatibility used.
      */
      virtual void visitAllEdges(const structure::ParameterSyntax& node , bool callVirtualBase = true);

      /**
      * \internal
      * \brief It call the traversal for the edges
      * \param node            [in] The node with own type
      * \param callVirtualBase [in] This paramater is don't used just api copatibility used.
      */
      virtual void visitAllEdges(const structure::ParenthesizedVariableDesignationSyntax& node , bool callVirtualBase = true);

      /**
      * \internal
      * \brief It call the traversal for the edges
      * \param node            [in] The node with own type
      * \param callVirtualBase [in] This paramater is don't used just api copatibility used.
      */
      virtual void visitAllEdges(const structure::PatternSyntax& node , bool callVirtualBase = true);

      /**
      * \internal
      * \brief It call the traversal for the edges
      * \param node            [in] The node with own type
      * \param callVirtualBase [in] This paramater is don't used just api copatibility used.
      */
      virtual void visitAllEdges(const structure::PositionalPatternClauseSyntax& node , bool callVirtualBase = true);

      /**
      * \internal
      * \brief It call the traversal for the edges
      * \param node            [in] The node with own type
      * \param callVirtualBase [in] This paramater is don't used just api copatibility used.
      */
      virtual void visitAllEdges(const structure::PropertyDeclarationSyntax& node , bool callVirtualBase = true);

      /**
      * \internal
      * \brief It call the traversal for the edges
      * \param node            [in] The node with own type
      * \param callVirtualBase [in] This paramater is don't used just api copatibility used.
      */
      virtual void visitAllEdges(const structure::PropertyPatternClauseSyntax& node , bool callVirtualBase = true);

      /**
      * \internal
      * \brief It call the traversal for the edges
      * \param node            [in] The node with own type
      * \param callVirtualBase [in] This paramater is don't used just api copatibility used.
      */
      virtual void visitAllEdges(const structure::QualifiedCrefSyntax& node , bool callVirtualBase = true);

      /**
      * \internal
      * \brief It call the traversal for the edges
      * \param node            [in] The node with own type
      * \param callVirtualBase [in] This paramater is don't used just api copatibility used.
      */
      virtual void visitAllEdges(const structure::QueryBodySyntax& node , bool callVirtualBase = true);

      /**
      * \internal
      * \brief It call the traversal for the edges
      * \param node            [in] The node with own type
      * \param callVirtualBase [in] This paramater is don't used just api copatibility used.
      */
      virtual void visitAllEdges(const structure::QueryClauseSyntax& node , bool callVirtualBase = true);

      /**
      * \internal
      * \brief It call the traversal for the edges
      * \param node            [in] The node with own type
      * \param callVirtualBase [in] This paramater is don't used just api copatibility used.
      */
      virtual void visitAllEdges(const structure::QueryContinuationSyntax& node , bool callVirtualBase = true);

      /**
      * \internal
      * \brief It call the traversal for the edges
      * \param node            [in] The node with own type
      * \param callVirtualBase [in] This paramater is don't used just api copatibility used.
      */
      virtual void visitAllEdges(const structure::RecursivePatternSyntax& node , bool callVirtualBase = true);

      /**
      * \internal
      * \brief It call the traversal for the edges
      * \param node            [in] The node with own type
      * \param callVirtualBase [in] This paramater is don't used just api copatibility used.
      */
      virtual void visitAllEdges(const structure::SelectClauseSyntax& node , bool callVirtualBase = true);

      /**
      * \internal
      * \brief It call the traversal for the edges
      * \param node            [in] The node with own type
      * \param callVirtualBase [in] This paramater is don't used just api copatibility used.
      */
      virtual void visitAllEdges(const structure::SelectOrGroupClauseSyntax& node , bool callVirtualBase = true);

      /**
      * \internal
      * \brief It call the traversal for the edges
      * \param node            [in] The node with own type
      * \param callVirtualBase [in] This paramater is don't used just api copatibility used.
      */
      virtual void visitAllEdges(const structure::SimpleBaseTypeSyntax& node , bool callVirtualBase = true);

      /**
      * \internal
      * \brief It call the traversal for the edges
      * \param node            [in] The node with own type
      * \param callVirtualBase [in] This paramater is don't used just api copatibility used.
      */
      virtual void visitAllEdges(const structure::SingleVariableDesignationSyntax& node , bool callVirtualBase = true);

      /**
      * \internal
      * \brief It call the traversal for the edges
      * \param node            [in] The node with own type
      * \param callVirtualBase [in] This paramater is don't used just api copatibility used.
      */
      virtual void visitAllEdges(const structure::StructDeclarationSyntax& node , bool callVirtualBase = true);

      /**
      * \internal
      * \brief It call the traversal for the edges
      * \param node            [in] The node with own type
      * \param callVirtualBase [in] This paramater is don't used just api copatibility used.
      */
      virtual void visitAllEdges(const structure::SubpatternSyntax& node , bool callVirtualBase = true);

      /**
      * \internal
      * \brief It call the traversal for the edges
      * \param node            [in] The node with own type
      * \param callVirtualBase [in] This paramater is don't used just api copatibility used.
      */
      virtual void visitAllEdges(const structure::SwitchExpressionArmSyntax& node , bool callVirtualBase = true);

      /**
      * \internal
      * \brief It call the traversal for the edges
      * \param node            [in] The node with own type
      * \param callVirtualBase [in] This paramater is don't used just api copatibility used.
      */
      virtual void visitAllEdges(const structure::SwitchLabelSyntax& node , bool callVirtualBase = true);

      /**
      * \internal
      * \brief It call the traversal for the edges
      * \param node            [in] The node with own type
      * \param callVirtualBase [in] This paramater is don't used just api copatibility used.
      */
      virtual void visitAllEdges(const structure::SwitchSectionSyntax& node , bool callVirtualBase = true);

      /**
      * \internal
      * \brief It call the traversal for the edges
      * \param node            [in] The node with own type
      * \param callVirtualBase [in] This paramater is don't used just api copatibility used.
      */
      virtual void visitAllEdges(const structure::SyntaxToken& node , bool callVirtualBase = true);

      /**
      * \internal
      * \brief It call the traversal for the edges
      * \param node            [in] The node with own type
      * \param callVirtualBase [in] This paramater is don't used just api copatibility used.
      */
      virtual void visitAllEdges(const structure::TupleElementSyntax& node , bool callVirtualBase = true);

      /**
      * \internal
      * \brief It call the traversal for the edges
      * \param node            [in] The node with own type
      * \param callVirtualBase [in] This paramater is don't used just api copatibility used.
      */
      virtual void visitAllEdges(const structure::TypeArgumentListSyntax& node , bool callVirtualBase = true);

      /**
      * \internal
      * \brief It call the traversal for the edges
      * \param node            [in] The node with own type
      * \param callVirtualBase [in] This paramater is don't used just api copatibility used.
      */
      virtual void visitAllEdges(const structure::TypeConstraintSyntax& node , bool callVirtualBase = true);

      /**
      * \internal
      * \brief It call the traversal for the edges
      * \param node            [in] The node with own type
      * \param callVirtualBase [in] This paramater is don't used just api copatibility used.
      */
      virtual void visitAllEdges(const structure::TypeCrefSyntax& node , bool callVirtualBase = true);

      /**
      * \internal
      * \brief It call the traversal for the edges
      * \param node            [in] The node with own type
      * \param callVirtualBase [in] This paramater is don't used just api copatibility used.
      */
      virtual void visitAllEdges(const structure::TypeDeclarationSyntax& node , bool callVirtualBase = true);

      /**
      * \internal
      * \brief It call the traversal for the edges
      * \param node            [in] The node with own type
      * \param callVirtualBase [in] This paramater is don't used just api copatibility used.
      */
      virtual void visitAllEdges(const structure::TypeParameterConstraintClauseSyntax& node , bool callVirtualBase = true);

      /**
      * \internal
      * \brief It call the traversal for the edges
      * \param node            [in] The node with own type
      * \param callVirtualBase [in] This paramater is don't used just api copatibility used.
      */
      virtual void visitAllEdges(const structure::TypeParameterConstraintSyntax& node , bool callVirtualBase = true);

      /**
      * \internal
      * \brief It call the traversal for the edges
      * \param node            [in] The node with own type
      * \param callVirtualBase [in] This paramater is don't used just api copatibility used.
      */
      virtual void visitAllEdges(const structure::TypeParameterListSyntax& node , bool callVirtualBase = true);

      /**
      * \internal
      * \brief It call the traversal for the edges
      * \param node            [in] The node with own type
      * \param callVirtualBase [in] This paramater is don't used just api copatibility used.
      */
      virtual void visitAllEdges(const structure::TypeParameterSyntax& node , bool callVirtualBase = true);

      /**
      * \internal
      * \brief It call the traversal for the edges
      * \param node            [in] The node with own type
      * \param callVirtualBase [in] This paramater is don't used just api copatibility used.
      */
      virtual void visitAllEdges(const structure::UsingDirectiveSyntax& node , bool callVirtualBase = true);

      /**
      * \internal
      * \brief It call the traversal for the edges
      * \param node            [in] The node with own type
      * \param callVirtualBase [in] This paramater is don't used just api copatibility used.
      */
      virtual void visitAllEdges(const structure::VarPatternSyntax& node , bool callVirtualBase = true);

      /**
      * \internal
      * \brief It call the traversal for the edges
      * \param node            [in] The node with own type
      * \param callVirtualBase [in] This paramater is don't used just api copatibility used.
      */
      virtual void visitAllEdges(const structure::VariableDeclarationSyntax& node , bool callVirtualBase = true);

      /**
      * \internal
      * \brief It call the traversal for the edges
      * \param node            [in] The node with own type
      * \param callVirtualBase [in] This paramater is don't used just api copatibility used.
      */
      virtual void visitAllEdges(const structure::VariableDeclaratorSyntax& node , bool callVirtualBase = true);

      /**
      * \internal
      * \brief It call the traversal for the edges
      * \param node            [in] The node with own type
      * \param callVirtualBase [in] This paramater is don't used just api copatibility used.
      */
      virtual void visitAllEdges(const structure::VariableDesignationSyntax& node , bool callVirtualBase = true);

      /**
      * \internal
      * \brief It call the traversal for the edges
      * \param node            [in] The node with own type
      * \param callVirtualBase [in] This paramater is don't used just api copatibility used.
      */
      virtual void visitAllEdges(const structure::WhenClauseSyntax& node , bool callVirtualBase = true);

      /**
      * \internal
      * \brief It call the traversal for the edges
      * \param node            [in] The node with own type
      * \param callVirtualBase [in] This paramater is don't used just api copatibility used.
      */
      virtual void visitAllEdges(const structure::WhereClauseSyntax& node , bool callVirtualBase = true);

      /**
      * \internal
      * \brief It call the traversal for the edges
      * \param node            [in] The node with own type
      * \param callVirtualBase [in] This paramater is don't used just api copatibility used.
      */
      virtual void visitAllEdges(const structure::XmlAttributeSyntax& node , bool callVirtualBase = true);

      /**
      * \internal
      * \brief It call the traversal for the edges
      * \param node            [in] The node with own type
      * \param callVirtualBase [in] This paramater is don't used just api copatibility used.
      */
      virtual void visitAllEdges(const structure::XmlCDataSectionSyntax& node , bool callVirtualBase = true);

      /**
      * \internal
      * \brief It call the traversal for the edges
      * \param node            [in] The node with own type
      * \param callVirtualBase [in] This paramater is don't used just api copatibility used.
      */
      virtual void visitAllEdges(const structure::XmlCommentSyntax& node , bool callVirtualBase = true);

      /**
      * \internal
      * \brief It call the traversal for the edges
      * \param node            [in] The node with own type
      * \param callVirtualBase [in] This paramater is don't used just api copatibility used.
      */
      virtual void visitAllEdges(const structure::XmlCrefAttributeSyntax& node , bool callVirtualBase = true);

      /**
      * \internal
      * \brief It call the traversal for the edges
      * \param node            [in] The node with own type
      * \param callVirtualBase [in] This paramater is don't used just api copatibility used.
      */
      virtual void visitAllEdges(const structure::XmlElementEndTagSyntax& node , bool callVirtualBase = true);

      /**
      * \internal
      * \brief It call the traversal for the edges
      * \param node            [in] The node with own type
      * \param callVirtualBase [in] This paramater is don't used just api copatibility used.
      */
      virtual void visitAllEdges(const structure::XmlElementStartTagSyntax& node , bool callVirtualBase = true);

      /**
      * \internal
      * \brief It call the traversal for the edges
      * \param node            [in] The node with own type
      * \param callVirtualBase [in] This paramater is don't used just api copatibility used.
      */
      virtual void visitAllEdges(const structure::XmlElementSyntax& node , bool callVirtualBase = true);

      /**
      * \internal
      * \brief It call the traversal for the edges
      * \param node            [in] The node with own type
      * \param callVirtualBase [in] This paramater is don't used just api copatibility used.
      */
      virtual void visitAllEdges(const structure::XmlEmptyElementSyntax& node , bool callVirtualBase = true);

      /**
      * \internal
      * \brief It call the traversal for the edges
      * \param node            [in] The node with own type
      * \param callVirtualBase [in] This paramater is don't used just api copatibility used.
      */
      virtual void visitAllEdges(const structure::XmlNameAttributeSyntax& node , bool callVirtualBase = true);

      /**
      * \internal
      * \brief It call the traversal for the edges
      * \param node            [in] The node with own type
      * \param callVirtualBase [in] This paramater is don't used just api copatibility used.
      */
      virtual void visitAllEdges(const structure::XmlNameSyntax& node , bool callVirtualBase = true);

      /**
      * \internal
      * \brief It call the traversal for the edges
      * \param node            [in] The node with own type
      * \param callVirtualBase [in] This paramater is don't used just api copatibility used.
      */
      virtual void visitAllEdges(const structure::XmlNodeSyntax& node , bool callVirtualBase = true);

      /**
      * \internal
      * \brief It call the traversal for the edges
      * \param node            [in] The node with own type
      * \param callVirtualBase [in] This paramater is don't used just api copatibility used.
      */
      virtual void visitAllEdges(const structure::XmlPrefixSyntax& node , bool callVirtualBase = true);

      /**
      * \internal
      * \brief It call the traversal for the edges
      * \param node            [in] The node with own type
      * \param callVirtualBase [in] This paramater is don't used just api copatibility used.
      */
      virtual void visitAllEdges(const structure::XmlProcessingInstructionSyntax& node , bool callVirtualBase = true);

      /**
      * \internal
      * \brief It call the traversal for the edges
      * \param node            [in] The node with own type
      * \param callVirtualBase [in] This paramater is don't used just api copatibility used.
      */
      virtual void visitAllEdges(const structure::XmlTextAttributeSyntax& node , bool callVirtualBase = true);

      /**
      * \internal
      * \brief It call the traversal for the edges
      * \param node            [in] The node with own type
      * \param callVirtualBase [in] This paramater is don't used just api copatibility used.
      */
      virtual void visitAllEdges(const structure::XmlTextSyntax& node , bool callVirtualBase = true);

      /**
      * \internal
      * \brief Starts a preorder traversal.
      */
      void mainRun(const Factory* fact, Visitor* visitor, const base::Base* node);

      /**
      * \internal
      * \brief Prepare for traversal. Modyficcate the filters if need it. Call the startvisit function for the all given vistor. ect.)
      */
      void startPreorder();

      /**
      * \internal
      * \brief Reset enviroment to the origal state. and call the visitFinish functions 
      */
      void endPreorder();

      /**
      * \brief Removes the stopped visitors from the visitorList. Sets the needPreorderStop true if the list becomes empty.
      */
      void clearStoppedVisitors();

      /** \internal \brief If it is true, two node are not visited during preorder. */
      bool safeMode;

      /** \internal \brief Stores the ids of the node which are already visited during the actual run. */
      std::vector<bool> visitedNodes;

      /** \internal \brief The set of ids of nodes which need to be visited. */
      std::vector<bool> unvisitedNodes;

      /** \internal \brief If it is true, it collect the sub trees. */
      bool visitCrossEdgeTree;

      /** \internal \brief If it is true, the preorder is stopped because of a visitor. */
      bool needPreorderStop;

      /** \internal \brief The set of visitors we stop in the next clearStoppedVisitors call. */
      std::set<Visitor*> stoppeds;

      bool visitFilteredEdge;

      bool originalFilterState;

      const base::Base* apRoot;

      std::list<Visitor*> visitorList;

      Factory* fact;

      bool traversaldCrossEdges[293];

  }; // AlgorithmPreorder


}}}
#endif

