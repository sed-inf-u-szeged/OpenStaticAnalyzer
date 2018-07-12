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

#ifndef _CSHARP_REVERSEEDGES_H_
#define _CSHARP_REVERSEEDGES_H_

#include "csharp/inc/csharp.h"

/**
* \file ReverseEdges.h
* \brief Contains declaration of ReverseEdges class.
*/

namespace columbus { namespace csharp { namespace asg {
  /**
  * \brief Collects the inverse relation of any "one way" defined edges.
  * The reverse relation tells for a given node the non trivial nodes
  * for which it has an incoming edge from.
  */
  class ReverseEdges {
    public:

      /** \internal \brief Type which will be use to select node types to revers edges. */
      typedef bool(*FuncPtrWithBaseParameterType)(const base::Base*);

    protected:

      /** \internal \brief The nodes of the same edges. */
      typedef ListIterator<base::Base>::Container NodeListType;

      /** \internal \brief Type which represent one node and its edges. */
      typedef std::map<EdgeKind, NodeListType> NodeEdgesType;

      /** \internal \brief Type which stores for all nodes their reversed edges. */
      typedef std::vector<NodeEdgesType*> RevEdgesContainer;

      /**
      * \internal
      * \brief Constructor.
      * \param factory [in] Revesred edges stored for this Factory.
      */
      ReverseEdges(const Factory* factory, FuncPtrWithBaseParameterType selectorFunction = NULL);

      /**
      * \internal
      * \brief Destructor.
      */
      ~ReverseEdges();

    private:

      /**
      * \internal
      * \brief Copy constructor.It not implemented it make linker error so it disable the copy of this object
      */
      ReverseEdges(const ReverseEdges&);

      /**
      * \internal
      * \brief It not implemented it make linker error so it disable the copy of this object.
      */
      ReverseEdges& operator=(ReverseEdges);

    public:

      /**
      * \brief Gives back a ListIterator for the given node with the given edge kind.
      * \param id              [in] The id of the node whose edges will be iterated.
      * \param edge            [in] The kind of the edge.
      * \throw CsharpException Throws exception if there is node for the id or the edge kind is invalid for this node (it is not invalid if the node can have such edge but it has not got at that moment).
      * \return Returns with a iterator which iterates the node's reverse edges of the given kind.
      */
      const ListIterator<base::Base> constIteratorBegin(NodeId id, EdgeKind edge) const;

      /**
      * \brief Gives back a ListIterator for the given node with the given edge kind.
      * \param id              [in] The id of the node whose edges will be iterated.
      * \param edge            [in] The kind of the edge.
      * \throw CsharpException Throws exception if there is node for the id or the edge kind is invalid for this node (it is not invalid if the node can have such edge but it has not got at that moment).
      * \return Returns with a iterator which iterates the node's reverse edges of the given kind.
      */
      const ListIterator<base::Base> constIteratorEnd(NodeId id, EdgeKind edge) const;

      /**
      * \brief Tells all kind of edges the node actually has.
      * \param id              [in] The id of the node whose edges we want to know.
      * \param edges           [out] A vector containing all kind of edges the node has (the vector is cleared before inserting new elements).
      * \throw CsharpException Throws exception if the node does not exist.
      */
      void getAllExistingEdges(NodeId id, std::vector<EdgeKind>& edges) const;

      /**
      * \brief Tells all kind of edges the node actually has.
      * \param id              [in] The id of the node whose edges we want to know.
      * \param edges           [out] A set containing all kind of edges the node has (the vector is cleared before inserting new elements).
      * \throw CsharpException Throws exception if the node does not exist.
      */
      void getAllExistingEdges(NodeId id, std::set<EdgeKind>& edges) const;

      /**
      * \brief Tells all kind of edges this kind of node can have.
      * \param kind            [in] The kind of the node whose edges we want to know.
      * \param edges           [out] A vector containing all kind of edges this kind of node can have (the vector is cleared before inserting new elements).
      * \throw CsharpException Throws exception if the kind is invalid.
      */
      void getAllPossibleEdges(NodeKind kind, std::vector<EdgeKind>& edges) const;

      /**
      * \brief Tells all kind of edges this kind of node can have.
      * \param kind            [in] The kind of the node whose edges we want to know.
      * \param edges           [out] A set containing all kind of edges this kind of node can have (the vector is cleared before inserting new elements).
      * \throw CsharpException Throws exception if the kind is invalid.
      */
      void getAllPossibleEdges(NodeKind kind, std::set<EdgeKind>& edges) const;

    private:

      /**
      * \internal
      * \brief Inserts a node (if the node has already been inserted nothing happens, otherwise the node is inserted without its edges).
      * \param id              [in] The id of the node which will be inserted.
      * \throw CsharpException Throws Exception if the node does not exist.
      */
      void insertNode(NodeId id);

      /**
      * \internal
      * \brief Removes a node (with out without its edges?).
      * \param id              [in] The id of the node which will be removed.
      * \throw CsharpException Throws CsharpException if there is no node for the id.
      */
      void removeNode(NodeId id);

      /**
      * \internal
      * \brief Inserts an edge.
      * \param from            [in] The reversed edge starts from that node (originally it was the target of the edge).
      * \param to              [in] The target of the reversed edge (originally it was the start of the edge).
      * \param edge            [in] The kind of the edge.
      * \throw CsharpException Throws CsharpException if the from node is not valid.
      */
      void insertEdge(const base::Base* from, const base::Base* to, EdgeKind edge);

      /**
      * \internal
      * \brief Inserts an edge.
      * \param from            [in] The reversed edge starts from that node (originally it was the target of the edge).
      * \param to              [in] The target of the reversed edge (originally it was the start of the edge).
      * \param edge            [in] The kind of the edge.
      * \throw CsharpException Throws CsharpException if the from node is not valid.
      */
      void insertEdge(NodeId from, NodeId to, EdgeKind edge);

      /**
      * \internal
      * \brief Removes an edge.
      * \param from            [in] The reversed edge starts from that node (originally it was the target of the edge).
      * \param to              [in] The target of the reversed edge (originally it was the start of the edge).
      * \param edge            [in] The kind of the edge.
      * \throw CsharpException todo.
      */
      void removeEdge(NodeId from, NodeId to, EdgeKind edge);

      /** \internal \brief Pointer to the Factory (the edges belong to it). */
      const Factory* fact;

      /** \internal \brief Pointer to selector function. */
      FuncPtrWithBaseParameterType selectorFunc;

      /** \internal \brief The Container (the edges are stored in it). */
      RevEdgesContainer reContainer;

      /** \internal \brief The possible edges by nodes. */
      static bool possibleEdges[198][250];

      friend class Factory;
      friend class VisitorReverseEdges;

      friend class base::Base;
      friend class base::Positioned;
      friend class expression::AliasQualifiedNameSyntax;
      friend class expression::AnonymousFunctionExpressionSyntax;
      friend class expression::AnonymousMethodExpressionSyntax;
      friend class expression::AnonymousObjectCreationExpressionSyntax;
      friend class expression::ArrayCreationExpressionSyntax;
      friend class expression::ArrayTypeSyntax;
      friend class expression::AssignmentExpressionSyntax;
      friend class expression::AwaitExpressionSyntax;
      friend class expression::BaseExpressionSyntax;
      friend class expression::BinaryExpressionSyntax;
      friend class expression::CastExpressionSyntax;
      friend class expression::CheckedExpressionSyntax;
      friend class expression::ConditionalAccessExpressionSyntax;
      friend class expression::ConditionalExpressionSyntax;
      friend class expression::DefaultExpressionSyntax;
      friend class expression::ElementAccessExpressionSyntax;
      friend class expression::ElementBindingExpressionSyntax;
      friend class expression::ExpressionSyntax;
      friend class expression::GenericNameSyntax;
      friend class expression::IdentifierNameSyntax;
      friend class expression::ImplicitArrayCreationExpressionSyntax;
      friend class expression::ImplicitElementAccessSyntax;
      friend class expression::InitializerExpressionSyntax;
      friend class expression::InstanceExpressionSyntax;
      friend class expression::InterpolatedStringExpressionSyntax;
      friend class expression::InvocationExpressionSyntax;
      friend class expression::LambdaExpressionSyntax;
      friend class expression::LiteralExpressionSyntax;
      friend class expression::MakeRefExpressionSyntax;
      friend class expression::MemberAccessExpressionSyntax;
      friend class expression::MemberBindingExpressionSyntax;
      friend class expression::NameSyntax;
      friend class expression::NullableTypeSyntax;
      friend class expression::ObjectCreationExpressionSyntax;
      friend class expression::OmittedArraySizeExpressionSyntax;
      friend class expression::OmittedTypeArgumentSyntax;
      friend class expression::ParenthesizedExpressionSyntax;
      friend class expression::ParenthesizedLambdaExpressionSyntax;
      friend class expression::PointerTypeSyntax;
      friend class expression::PostfixUnaryExpressionSyntax;
      friend class expression::PredefinedTypeSyntax;
      friend class expression::PrefixUnaryExpressionSyntax;
      friend class expression::QualifiedNameSyntax;
      friend class expression::QueryExpressionSyntax;
      friend class expression::RefTypeExpressionSyntax;
      friend class expression::RefValueExpressionSyntax;
      friend class expression::SimpleLambdaExpressionSyntax;
      friend class expression::SimpleNameSyntax;
      friend class expression::SizeOfExpressionSyntax;
      friend class expression::StackAllocArrayCreationExpressionSyntax;
      friend class expression::ThisExpressionSyntax;
      friend class expression::TypeOfExpressionSyntax;
      friend class expression::TypeSyntax;
      friend class statement::BlockSyntax;
      friend class statement::BreakStatementSyntax;
      friend class statement::CheckedStatementSyntax;
      friend class statement::ContinueStatementSyntax;
      friend class statement::DoStatementSyntax;
      friend class statement::EmptyStatementSyntax;
      friend class statement::ExpressionStatementSyntax;
      friend class statement::FixedStatementSyntax;
      friend class statement::ForEachStatementSyntax;
      friend class statement::ForStatementSyntax;
      friend class statement::GotoStatementSyntax;
      friend class statement::IfStatementSyntax;
      friend class statement::LabeledStatementSyntax;
      friend class statement::LocalDeclarationStatementSyntax;
      friend class statement::LockStatementSyntax;
      friend class statement::ReturnStatementSyntax;
      friend class statement::StatementSyntax;
      friend class statement::SwitchStatementSyntax;
      friend class statement::ThrowStatementSyntax;
      friend class statement::TryStatementSyntax;
      friend class statement::UnsafeStatementSyntax;
      friend class statement::UsingStatementSyntax;
      friend class statement::WhileStatementSyntax;
      friend class statement::YieldStatementSyntax;
      friend class structure::AccessorDeclarationSyntax;
      friend class structure::AccessorListSyntax;
      friend class structure::AnonymousObjectMemberDeclaratorSyntax;
      friend class structure::ArgumentListSyntax;
      friend class structure::ArgumentSyntax;
      friend class structure::ArrayRankSpecifierSyntax;
      friend class structure::ArrowExpressionClauseSyntax;
      friend class structure::AttributeArgumentListSyntax;
      friend class structure::AttributeArgumentSyntax;
      friend class structure::AttributeListSyntax;
      friend class structure::AttributeSyntax;
      friend class structure::AttributeTargetSpecifierSyntax;
      friend class structure::BaseArgumentListSyntax;
      friend class structure::BaseCrefParameterListSyntax;
      friend class structure::BaseFieldDeclarationSyntax;
      friend class structure::BaseListSyntax;
      friend class structure::BaseMethodDeclarationSyntax;
      friend class structure::BaseParameterListSyntax;
      friend class structure::BasePropertyDeclarationSyntax;
      friend class structure::BaseTypeDeclarationSyntax;
      friend class structure::BaseTypeSyntax;
      friend class structure::BracketedArgumentListSyntax;
      friend class structure::BracketedParameterListSyntax;
      friend class structure::CaseSwitchLabelSyntax;
      friend class structure::CatchClauseSyntax;
      friend class structure::CatchDeclarationSyntax;
      friend class structure::CatchFilterClauseSyntax;
      friend class structure::ClassDeclarationSyntax;
      friend class structure::ClassOrStructConstraintSyntax;
      friend class structure::CompilationUnitSyntax;
      friend class structure::ConstructorConstraintSyntax;
      friend class structure::ConstructorDeclarationSyntax;
      friend class structure::ConstructorInitializerSyntax;
      friend class structure::ConversionOperatorDeclarationSyntax;
      friend class structure::ConversionOperatorMemberCrefSyntax;
      friend class structure::CrefBracketedParameterListSyntax;
      friend class structure::CrefParameterListSyntax;
      friend class structure::CrefParameterSyntax;
      friend class structure::CrefSyntax;
      friend class structure::DefaultSwitchLabelSyntax;
      friend class structure::DelegateDeclarationSyntax;
      friend class structure::DestructorDeclarationSyntax;
      friend class structure::ElseClauseSyntax;
      friend class structure::EnumDeclarationSyntax;
      friend class structure::EnumMemberDeclarationSyntax;
      friend class structure::EqualsValueClauseSyntax;
      friend class structure::EventDeclarationSyntax;
      friend class structure::EventFieldDeclarationSyntax;
      friend class structure::ExplicitInterfaceSpecifierSyntax;
      friend class structure::ExternAliasDirectiveSyntax;
      friend class structure::FieldDeclarationSyntax;
      friend class structure::FinallyClauseSyntax;
      friend class structure::FromClauseSyntax;
      friend class structure::GlobalStatementSyntax;
      friend class structure::GroupClauseSyntax;
      friend class structure::IncompleteMemberSyntax;
      friend class structure::IndexerDeclarationSyntax;
      friend class structure::IndexerMemberCrefSyntax;
      friend class structure::InterfaceDeclarationSyntax;
      friend class structure::InterpolatedStringContentSyntax;
      friend class structure::InterpolatedStringTextSyntax;
      friend class structure::InterpolationAlignmentClauseSyntax;
      friend class structure::InterpolationFormatClauseSyntax;
      friend class structure::InterpolationSyntax;
      friend class structure::JoinClauseSyntax;
      friend class structure::JoinIntoClauseSyntax;
      friend class structure::LetClauseSyntax;
      friend class structure::MemberCrefSyntax;
      friend class structure::MemberDeclarationSyntax;
      friend class structure::MethodDeclarationSyntax;
      friend class structure::NameColonSyntax;
      friend class structure::NameEqualsSyntax;
      friend class structure::NameMemberCrefSyntax;
      friend class structure::NamespaceDeclarationSyntax;
      friend class structure::OperatorDeclarationSyntax;
      friend class structure::OperatorMemberCrefSyntax;
      friend class structure::OrderByClauseSyntax;
      friend class structure::OrderingSyntax;
      friend class structure::ParameterListSyntax;
      friend class structure::ParameterSyntax;
      friend class structure::PropertyDeclarationSyntax;
      friend class structure::QualifiedCrefSyntax;
      friend class structure::QueryBodySyntax;
      friend class structure::QueryClauseSyntax;
      friend class structure::QueryContinuationSyntax;
      friend class structure::SelectClauseSyntax;
      friend class structure::SelectOrGroupClauseSyntax;
      friend class structure::SimpleBaseTypeSyntax;
      friend class structure::StructDeclarationSyntax;
      friend class structure::SwitchLabelSyntax;
      friend class structure::SwitchSectionSyntax;
      friend class structure::SyntaxToken;
      friend class structure::TypeArgumentListSyntax;
      friend class structure::TypeConstraintSyntax;
      friend class structure::TypeCrefSyntax;
      friend class structure::TypeDeclarationSyntax;
      friend class structure::TypeParameterConstraintClauseSyntax;
      friend class structure::TypeParameterConstraintSyntax;
      friend class structure::TypeParameterListSyntax;
      friend class structure::TypeParameterSyntax;
      friend class structure::UsingDirectiveSyntax;
      friend class structure::VariableDeclarationSyntax;
      friend class structure::VariableDeclaratorSyntax;
      friend class structure::WhereClauseSyntax;
      friend class structure::XmlAttributeSyntax;
      friend class structure::XmlCDataSectionSyntax;
      friend class structure::XmlCommentSyntax;
      friend class structure::XmlCrefAttributeSyntax;
      friend class structure::XmlElementEndTagSyntax;
      friend class structure::XmlElementStartTagSyntax;
      friend class structure::XmlElementSyntax;
      friend class structure::XmlEmptyElementSyntax;
      friend class structure::XmlNameAttributeSyntax;
      friend class structure::XmlNameSyntax;
      friend class structure::XmlNodeSyntax;
      friend class structure::XmlPrefixSyntax;
      friend class structure::XmlProcessingInstructionSyntax;
      friend class structure::XmlTextAttributeSyntax;
      friend class structure::XmlTextSyntax;
  }; // ReverseEdges


}}}
#endif

