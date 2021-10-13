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

#ifndef _CSHARP_ALGORITHMDEEPCOPY_H_
#define _CSHARP_ALGORITHMDEEPCOPY_H_

#include "csharp/inc/csharp.h"

#include <map>
#include <set>

/**
* \file AlgorithmDeepCopy.h
* \brief Contains the class `AlgorithmDeepCopy' which implements deep-copying of an arbitary subtree of an ASG.
*/

namespace columbus { namespace csharp { namespace asg {
  /**
  * \brief Implements the deep-copying of a part of the ASG.
  */
  class AlgorithmDeepCopy: public Algorithm {
    private:
      /** \internal \brief The source factory of the ASG. */
      Factory& srcFact;
    private:
      /** \internal \brief The target factory of the ASG. */
      Factory& targetFact;
      /** \internal \brief The id of the node identifying the subtree to be copied. */
      NodeId what;
      /** \internal \brief The last NodeId which was returned by the Factory::createNode method.  */
      base::Base* lastNode;
      /** \internal \brief The cross-reference between the old nodes and the already copied ones. */
      std::map<const base::Base*,base::Base*>& mapped_nodes;
      /**
      * \brief Disable copy of object.
      */
      AlgorithmDeepCopy(const AlgorithmDeepCopy&);

      /**
      * \brief Disable copy of object.
      */
      AlgorithmDeepCopy& operator=(const AlgorithmDeepCopy&);

    public:
      /**
      * \brief Constructor.
      * \param what [in] The id of the node which is to be copied.
      * \param srcFact [in] The source factory belonging to the ASG.
      * \param targetFact [in] The target factory belonging to the ASG.
      * \param mapped_nodes [in] A map (NodeId->NodeId) to store the bijection of original and cloned nodes.
      */
      AlgorithmDeepCopy(NodeId what, Factory& srcFact, Factory& targetFact, std::map<const base::Base*, base::Base*>& mapped_nodes);

      /**
      * \brief Virtual destructor.
      */
      virtual ~AlgorithmDeepCopy();

      /**
      * \brief Executes the cloning algorithm. Returns the NodeId of the newly created copy of the required node
      */
      base::Base* clone();

      /**
      * \brief Returns the mapping between the original subtree and the cloned one.
      */
      std::map<const base::Base*,base::Base* >& getMapping();
    private:
      base::Base* createNode(const base::Base* oldNode, NodeKind ndk);
      base::Base* clone(const base::Base* old);
      base::Base* getMappedNode(const base::Base* old);
      void clone(base::Base* dest, const base::Base* src);
      void clone(base::Positioned* dest, const base::Positioned* src);
      void clone(expression::AliasQualifiedNameSyntax* dest, const expression::AliasQualifiedNameSyntax* src);
      void clone(expression::AnonymousFunctionExpressionSyntax* dest, const expression::AnonymousFunctionExpressionSyntax* src);
      void clone(expression::AnonymousMethodExpressionSyntax* dest, const expression::AnonymousMethodExpressionSyntax* src);
      void clone(expression::AnonymousObjectCreationExpressionSyntax* dest, const expression::AnonymousObjectCreationExpressionSyntax* src);
      void clone(expression::ArrayCreationExpressionSyntax* dest, const expression::ArrayCreationExpressionSyntax* src);
      void clone(expression::ArrayTypeSyntax* dest, const expression::ArrayTypeSyntax* src);
      void clone(expression::AssignmentExpressionSyntax* dest, const expression::AssignmentExpressionSyntax* src);
      void clone(expression::AwaitExpressionSyntax* dest, const expression::AwaitExpressionSyntax* src);
      void clone(expression::BaseExpressionSyntax* dest, const expression::BaseExpressionSyntax* src);
      void clone(expression::BinaryExpressionSyntax* dest, const expression::BinaryExpressionSyntax* src);
      void clone(expression::CastExpressionSyntax* dest, const expression::CastExpressionSyntax* src);
      void clone(expression::CheckedExpressionSyntax* dest, const expression::CheckedExpressionSyntax* src);
      void clone(expression::ConditionalAccessExpressionSyntax* dest, const expression::ConditionalAccessExpressionSyntax* src);
      void clone(expression::ConditionalExpressionSyntax* dest, const expression::ConditionalExpressionSyntax* src);
      void clone(expression::DeclarationExpressionSyntax* dest, const expression::DeclarationExpressionSyntax* src);
      void clone(expression::DefaultExpressionSyntax* dest, const expression::DefaultExpressionSyntax* src);
      void clone(expression::ElementAccessExpressionSyntax* dest, const expression::ElementAccessExpressionSyntax* src);
      void clone(expression::ElementBindingExpressionSyntax* dest, const expression::ElementBindingExpressionSyntax* src);
      void clone(expression::ExpressionSyntax* dest, const expression::ExpressionSyntax* src);
      void clone(expression::GenericNameSyntax* dest, const expression::GenericNameSyntax* src);
      void clone(expression::IdentifierNameSyntax* dest, const expression::IdentifierNameSyntax* src);
      void clone(expression::ImplicitArrayCreationExpressionSyntax* dest, const expression::ImplicitArrayCreationExpressionSyntax* src);
      void clone(expression::ImplicitElementAccessSyntax* dest, const expression::ImplicitElementAccessSyntax* src);
      void clone(expression::ImplicitStackAllocArrayCreationExpressionSyntax* dest, const expression::ImplicitStackAllocArrayCreationExpressionSyntax* src);
      void clone(expression::InitializerExpressionSyntax* dest, const expression::InitializerExpressionSyntax* src);
      void clone(expression::InstanceExpressionSyntax* dest, const expression::InstanceExpressionSyntax* src);
      void clone(expression::InterpolatedStringExpressionSyntax* dest, const expression::InterpolatedStringExpressionSyntax* src);
      void clone(expression::InvocationExpressionSyntax* dest, const expression::InvocationExpressionSyntax* src);
      void clone(expression::IsPatternExpressionSyntax* dest, const expression::IsPatternExpressionSyntax* src);
      void clone(expression::LambdaExpressionSyntax* dest, const expression::LambdaExpressionSyntax* src);
      void clone(expression::LiteralExpressionSyntax* dest, const expression::LiteralExpressionSyntax* src);
      void clone(expression::MakeRefExpressionSyntax* dest, const expression::MakeRefExpressionSyntax* src);
      void clone(expression::MemberAccessExpressionSyntax* dest, const expression::MemberAccessExpressionSyntax* src);
      void clone(expression::MemberBindingExpressionSyntax* dest, const expression::MemberBindingExpressionSyntax* src);
      void clone(expression::NameSyntax* dest, const expression::NameSyntax* src);
      void clone(expression::NullableTypeSyntax* dest, const expression::NullableTypeSyntax* src);
      void clone(expression::ObjectCreationExpressionSyntax* dest, const expression::ObjectCreationExpressionSyntax* src);
      void clone(expression::OmittedArraySizeExpressionSyntax* dest, const expression::OmittedArraySizeExpressionSyntax* src);
      void clone(expression::OmittedTypeArgumentSyntax* dest, const expression::OmittedTypeArgumentSyntax* src);
      void clone(expression::ParenthesizedExpressionSyntax* dest, const expression::ParenthesizedExpressionSyntax* src);
      void clone(expression::ParenthesizedLambdaExpressionSyntax* dest, const expression::ParenthesizedLambdaExpressionSyntax* src);
      void clone(expression::PointerTypeSyntax* dest, const expression::PointerTypeSyntax* src);
      void clone(expression::PostfixUnaryExpressionSyntax* dest, const expression::PostfixUnaryExpressionSyntax* src);
      void clone(expression::PredefinedTypeSyntax* dest, const expression::PredefinedTypeSyntax* src);
      void clone(expression::PrefixUnaryExpressionSyntax* dest, const expression::PrefixUnaryExpressionSyntax* src);
      void clone(expression::QualifiedNameSyntax* dest, const expression::QualifiedNameSyntax* src);
      void clone(expression::QueryExpressionSyntax* dest, const expression::QueryExpressionSyntax* src);
      void clone(expression::RangeExpressionSyntax* dest, const expression::RangeExpressionSyntax* src);
      void clone(expression::RefExpressionSyntax* dest, const expression::RefExpressionSyntax* src);
      void clone(expression::RefTypeExpressionSyntax* dest, const expression::RefTypeExpressionSyntax* src);
      void clone(expression::RefTypeSyntax* dest, const expression::RefTypeSyntax* src);
      void clone(expression::RefValueExpressionSyntax* dest, const expression::RefValueExpressionSyntax* src);
      void clone(expression::SimpleLambdaExpressionSyntax* dest, const expression::SimpleLambdaExpressionSyntax* src);
      void clone(expression::SimpleNameSyntax* dest, const expression::SimpleNameSyntax* src);
      void clone(expression::SizeOfExpressionSyntax* dest, const expression::SizeOfExpressionSyntax* src);
      void clone(expression::StackAllocArrayCreationExpressionSyntax* dest, const expression::StackAllocArrayCreationExpressionSyntax* src);
      void clone(expression::SwitchExpressionSyntax* dest, const expression::SwitchExpressionSyntax* src);
      void clone(expression::ThisExpressionSyntax* dest, const expression::ThisExpressionSyntax* src);
      void clone(expression::ThrowExpressionSyntax* dest, const expression::ThrowExpressionSyntax* src);
      void clone(expression::TupleExpressionSyntax* dest, const expression::TupleExpressionSyntax* src);
      void clone(expression::TupleTypeSyntax* dest, const expression::TupleTypeSyntax* src);
      void clone(expression::TypeOfExpressionSyntax* dest, const expression::TypeOfExpressionSyntax* src);
      void clone(expression::TypeSyntax* dest, const expression::TypeSyntax* src);
      void clone(statement::BlockSyntax* dest, const statement::BlockSyntax* src);
      void clone(statement::BreakStatementSyntax* dest, const statement::BreakStatementSyntax* src);
      void clone(statement::CheckedStatementSyntax* dest, const statement::CheckedStatementSyntax* src);
      void clone(statement::CommonForEachStatementSyntax* dest, const statement::CommonForEachStatementSyntax* src);
      void clone(statement::ContinueStatementSyntax* dest, const statement::ContinueStatementSyntax* src);
      void clone(statement::DoStatementSyntax* dest, const statement::DoStatementSyntax* src);
      void clone(statement::EmptyStatementSyntax* dest, const statement::EmptyStatementSyntax* src);
      void clone(statement::ExpressionStatementSyntax* dest, const statement::ExpressionStatementSyntax* src);
      void clone(statement::FixedStatementSyntax* dest, const statement::FixedStatementSyntax* src);
      void clone(statement::ForEachStatementSyntax* dest, const statement::ForEachStatementSyntax* src);
      void clone(statement::ForEachVariableStatementSyntax* dest, const statement::ForEachVariableStatementSyntax* src);
      void clone(statement::ForStatementSyntax* dest, const statement::ForStatementSyntax* src);
      void clone(statement::GotoStatementSyntax* dest, const statement::GotoStatementSyntax* src);
      void clone(statement::IfStatementSyntax* dest, const statement::IfStatementSyntax* src);
      void clone(statement::LabeledStatementSyntax* dest, const statement::LabeledStatementSyntax* src);
      void clone(statement::LocalDeclarationStatementSyntax* dest, const statement::LocalDeclarationStatementSyntax* src);
      void clone(statement::LocalFunctionStatementSyntax* dest, const statement::LocalFunctionStatementSyntax* src);
      void clone(statement::LockStatementSyntax* dest, const statement::LockStatementSyntax* src);
      void clone(statement::ReturnStatementSyntax* dest, const statement::ReturnStatementSyntax* src);
      void clone(statement::StatementSyntax* dest, const statement::StatementSyntax* src);
      void clone(statement::SwitchStatementSyntax* dest, const statement::SwitchStatementSyntax* src);
      void clone(statement::ThrowStatementSyntax* dest, const statement::ThrowStatementSyntax* src);
      void clone(statement::TryStatementSyntax* dest, const statement::TryStatementSyntax* src);
      void clone(statement::UnsafeStatementSyntax* dest, const statement::UnsafeStatementSyntax* src);
      void clone(statement::UsingStatementSyntax* dest, const statement::UsingStatementSyntax* src);
      void clone(statement::WhileStatementSyntax* dest, const statement::WhileStatementSyntax* src);
      void clone(statement::YieldStatementSyntax* dest, const statement::YieldStatementSyntax* src);
      void clone(structure::AccessorDeclarationSyntax* dest, const structure::AccessorDeclarationSyntax* src);
      void clone(structure::AccessorListSyntax* dest, const structure::AccessorListSyntax* src);
      void clone(structure::AnonymousObjectMemberDeclaratorSyntax* dest, const structure::AnonymousObjectMemberDeclaratorSyntax* src);
      void clone(structure::ArgumentListSyntax* dest, const structure::ArgumentListSyntax* src);
      void clone(structure::ArgumentSyntax* dest, const structure::ArgumentSyntax* src);
      void clone(structure::ArrayRankSpecifierSyntax* dest, const structure::ArrayRankSpecifierSyntax* src);
      void clone(structure::ArrowExpressionClauseSyntax* dest, const structure::ArrowExpressionClauseSyntax* src);
      void clone(structure::AttributeArgumentListSyntax* dest, const structure::AttributeArgumentListSyntax* src);
      void clone(structure::AttributeArgumentSyntax* dest, const structure::AttributeArgumentSyntax* src);
      void clone(structure::AttributeListSyntax* dest, const structure::AttributeListSyntax* src);
      void clone(structure::AttributeSyntax* dest, const structure::AttributeSyntax* src);
      void clone(structure::AttributeTargetSpecifierSyntax* dest, const structure::AttributeTargetSpecifierSyntax* src);
      void clone(structure::BaseArgumentListSyntax* dest, const structure::BaseArgumentListSyntax* src);
      void clone(structure::BaseCrefParameterListSyntax* dest, const structure::BaseCrefParameterListSyntax* src);
      void clone(structure::BaseFieldDeclarationSyntax* dest, const structure::BaseFieldDeclarationSyntax* src);
      void clone(structure::BaseListSyntax* dest, const structure::BaseListSyntax* src);
      void clone(structure::BaseMethodDeclarationSyntax* dest, const structure::BaseMethodDeclarationSyntax* src);
      void clone(structure::BaseParameterListSyntax* dest, const structure::BaseParameterListSyntax* src);
      void clone(structure::BasePropertyDeclarationSyntax* dest, const structure::BasePropertyDeclarationSyntax* src);
      void clone(structure::BaseTypeDeclarationSyntax* dest, const structure::BaseTypeDeclarationSyntax* src);
      void clone(structure::BaseTypeSyntax* dest, const structure::BaseTypeSyntax* src);
      void clone(structure::BracketedArgumentListSyntax* dest, const structure::BracketedArgumentListSyntax* src);
      void clone(structure::BracketedParameterListSyntax* dest, const structure::BracketedParameterListSyntax* src);
      void clone(structure::CasePatternSwitchLabelSyntax* dest, const structure::CasePatternSwitchLabelSyntax* src);
      void clone(structure::CaseSwitchLabelSyntax* dest, const structure::CaseSwitchLabelSyntax* src);
      void clone(structure::CatchClauseSyntax* dest, const structure::CatchClauseSyntax* src);
      void clone(structure::CatchDeclarationSyntax* dest, const structure::CatchDeclarationSyntax* src);
      void clone(structure::CatchFilterClauseSyntax* dest, const structure::CatchFilterClauseSyntax* src);
      void clone(structure::ClassDeclarationSyntax* dest, const structure::ClassDeclarationSyntax* src);
      void clone(structure::ClassOrStructConstraintSyntax* dest, const structure::ClassOrStructConstraintSyntax* src);
      void clone(structure::CompilationUnitSyntax* dest, const structure::CompilationUnitSyntax* src);
      void clone(structure::ConstantPatternSyntax* dest, const structure::ConstantPatternSyntax* src);
      void clone(structure::ConstructorConstraintSyntax* dest, const structure::ConstructorConstraintSyntax* src);
      void clone(structure::ConstructorDeclarationSyntax* dest, const structure::ConstructorDeclarationSyntax* src);
      void clone(structure::ConstructorInitializerSyntax* dest, const structure::ConstructorInitializerSyntax* src);
      void clone(structure::ConversionOperatorDeclarationSyntax* dest, const structure::ConversionOperatorDeclarationSyntax* src);
      void clone(structure::ConversionOperatorMemberCrefSyntax* dest, const structure::ConversionOperatorMemberCrefSyntax* src);
      void clone(structure::CrefBracketedParameterListSyntax* dest, const structure::CrefBracketedParameterListSyntax* src);
      void clone(structure::CrefParameterListSyntax* dest, const structure::CrefParameterListSyntax* src);
      void clone(structure::CrefParameterSyntax* dest, const structure::CrefParameterSyntax* src);
      void clone(structure::CrefSyntax* dest, const structure::CrefSyntax* src);
      void clone(structure::DeclarationPatternSyntax* dest, const structure::DeclarationPatternSyntax* src);
      void clone(structure::DefaultSwitchLabelSyntax* dest, const structure::DefaultSwitchLabelSyntax* src);
      void clone(structure::DelegateDeclarationSyntax* dest, const structure::DelegateDeclarationSyntax* src);
      void clone(structure::DestructorDeclarationSyntax* dest, const structure::DestructorDeclarationSyntax* src);
      void clone(structure::DiscardDesignationSyntax* dest, const structure::DiscardDesignationSyntax* src);
      void clone(structure::DiscardPatternSyntax* dest, const structure::DiscardPatternSyntax* src);
      void clone(structure::ElseClauseSyntax* dest, const structure::ElseClauseSyntax* src);
      void clone(structure::EnumDeclarationSyntax* dest, const structure::EnumDeclarationSyntax* src);
      void clone(structure::EnumMemberDeclarationSyntax* dest, const structure::EnumMemberDeclarationSyntax* src);
      void clone(structure::EqualsValueClauseSyntax* dest, const structure::EqualsValueClauseSyntax* src);
      void clone(structure::EventDeclarationSyntax* dest, const structure::EventDeclarationSyntax* src);
      void clone(structure::EventFieldDeclarationSyntax* dest, const structure::EventFieldDeclarationSyntax* src);
      void clone(structure::ExplicitInterfaceSpecifierSyntax* dest, const structure::ExplicitInterfaceSpecifierSyntax* src);
      void clone(structure::ExternAliasDirectiveSyntax* dest, const structure::ExternAliasDirectiveSyntax* src);
      void clone(structure::FieldDeclarationSyntax* dest, const structure::FieldDeclarationSyntax* src);
      void clone(structure::FinallyClauseSyntax* dest, const structure::FinallyClauseSyntax* src);
      void clone(structure::FromClauseSyntax* dest, const structure::FromClauseSyntax* src);
      void clone(structure::GlobalStatementSyntax* dest, const structure::GlobalStatementSyntax* src);
      void clone(structure::GroupClauseSyntax* dest, const structure::GroupClauseSyntax* src);
      void clone(structure::IncompleteMemberSyntax* dest, const structure::IncompleteMemberSyntax* src);
      void clone(structure::IndexerDeclarationSyntax* dest, const structure::IndexerDeclarationSyntax* src);
      void clone(structure::IndexerMemberCrefSyntax* dest, const structure::IndexerMemberCrefSyntax* src);
      void clone(structure::InterfaceDeclarationSyntax* dest, const structure::InterfaceDeclarationSyntax* src);
      void clone(structure::InterpolatedStringContentSyntax* dest, const structure::InterpolatedStringContentSyntax* src);
      void clone(structure::InterpolatedStringTextSyntax* dest, const structure::InterpolatedStringTextSyntax* src);
      void clone(structure::InterpolationAlignmentClauseSyntax* dest, const structure::InterpolationAlignmentClauseSyntax* src);
      void clone(structure::InterpolationFormatClauseSyntax* dest, const structure::InterpolationFormatClauseSyntax* src);
      void clone(structure::InterpolationSyntax* dest, const structure::InterpolationSyntax* src);
      void clone(structure::JoinClauseSyntax* dest, const structure::JoinClauseSyntax* src);
      void clone(structure::JoinIntoClauseSyntax* dest, const structure::JoinIntoClauseSyntax* src);
      void clone(structure::LetClauseSyntax* dest, const structure::LetClauseSyntax* src);
      void clone(structure::MemberCrefSyntax* dest, const structure::MemberCrefSyntax* src);
      void clone(structure::MemberDeclarationSyntax* dest, const structure::MemberDeclarationSyntax* src);
      void clone(structure::MethodDeclarationSyntax* dest, const structure::MethodDeclarationSyntax* src);
      void clone(structure::NameColonSyntax* dest, const structure::NameColonSyntax* src);
      void clone(structure::NameEqualsSyntax* dest, const structure::NameEqualsSyntax* src);
      void clone(structure::NameMemberCrefSyntax* dest, const structure::NameMemberCrefSyntax* src);
      void clone(structure::NamespaceDeclarationSyntax* dest, const structure::NamespaceDeclarationSyntax* src);
      void clone(structure::OperatorDeclarationSyntax* dest, const structure::OperatorDeclarationSyntax* src);
      void clone(structure::OperatorMemberCrefSyntax* dest, const structure::OperatorMemberCrefSyntax* src);
      void clone(structure::OrderByClauseSyntax* dest, const structure::OrderByClauseSyntax* src);
      void clone(structure::OrderingSyntax* dest, const structure::OrderingSyntax* src);
      void clone(structure::ParameterListSyntax* dest, const structure::ParameterListSyntax* src);
      void clone(structure::ParameterSyntax* dest, const structure::ParameterSyntax* src);
      void clone(structure::ParenthesizedVariableDesignationSyntax* dest, const structure::ParenthesizedVariableDesignationSyntax* src);
      void clone(structure::PatternSyntax* dest, const structure::PatternSyntax* src);
      void clone(structure::PositionalPatternClauseSyntax* dest, const structure::PositionalPatternClauseSyntax* src);
      void clone(structure::PropertyDeclarationSyntax* dest, const structure::PropertyDeclarationSyntax* src);
      void clone(structure::PropertyPatternClauseSyntax* dest, const structure::PropertyPatternClauseSyntax* src);
      void clone(structure::QualifiedCrefSyntax* dest, const structure::QualifiedCrefSyntax* src);
      void clone(structure::QueryBodySyntax* dest, const structure::QueryBodySyntax* src);
      void clone(structure::QueryClauseSyntax* dest, const structure::QueryClauseSyntax* src);
      void clone(structure::QueryContinuationSyntax* dest, const structure::QueryContinuationSyntax* src);
      void clone(structure::RecursivePatternSyntax* dest, const structure::RecursivePatternSyntax* src);
      void clone(structure::SelectClauseSyntax* dest, const structure::SelectClauseSyntax* src);
      void clone(structure::SelectOrGroupClauseSyntax* dest, const structure::SelectOrGroupClauseSyntax* src);
      void clone(structure::SimpleBaseTypeSyntax* dest, const structure::SimpleBaseTypeSyntax* src);
      void clone(structure::SingleVariableDesignationSyntax* dest, const structure::SingleVariableDesignationSyntax* src);
      void clone(structure::StructDeclarationSyntax* dest, const structure::StructDeclarationSyntax* src);
      void clone(structure::SubpatternSyntax* dest, const structure::SubpatternSyntax* src);
      void clone(structure::SwitchExpressionArmSyntax* dest, const structure::SwitchExpressionArmSyntax* src);
      void clone(structure::SwitchLabelSyntax* dest, const structure::SwitchLabelSyntax* src);
      void clone(structure::SwitchSectionSyntax* dest, const structure::SwitchSectionSyntax* src);
      void clone(structure::SyntaxToken* dest, const structure::SyntaxToken* src);
      void clone(structure::TupleElementSyntax* dest, const structure::TupleElementSyntax* src);
      void clone(structure::TypeArgumentListSyntax* dest, const structure::TypeArgumentListSyntax* src);
      void clone(structure::TypeConstraintSyntax* dest, const structure::TypeConstraintSyntax* src);
      void clone(structure::TypeCrefSyntax* dest, const structure::TypeCrefSyntax* src);
      void clone(structure::TypeDeclarationSyntax* dest, const structure::TypeDeclarationSyntax* src);
      void clone(structure::TypeParameterConstraintClauseSyntax* dest, const structure::TypeParameterConstraintClauseSyntax* src);
      void clone(structure::TypeParameterConstraintSyntax* dest, const structure::TypeParameterConstraintSyntax* src);
      void clone(structure::TypeParameterListSyntax* dest, const structure::TypeParameterListSyntax* src);
      void clone(structure::TypeParameterSyntax* dest, const structure::TypeParameterSyntax* src);
      void clone(structure::UsingDirectiveSyntax* dest, const structure::UsingDirectiveSyntax* src);
      void clone(structure::VarPatternSyntax* dest, const structure::VarPatternSyntax* src);
      void clone(structure::VariableDeclarationSyntax* dest, const structure::VariableDeclarationSyntax* src);
      void clone(structure::VariableDeclaratorSyntax* dest, const structure::VariableDeclaratorSyntax* src);
      void clone(structure::VariableDesignationSyntax* dest, const structure::VariableDesignationSyntax* src);
      void clone(structure::WhenClauseSyntax* dest, const structure::WhenClauseSyntax* src);
      void clone(structure::WhereClauseSyntax* dest, const structure::WhereClauseSyntax* src);
      void clone(structure::XmlAttributeSyntax* dest, const structure::XmlAttributeSyntax* src);
      void clone(structure::XmlCDataSectionSyntax* dest, const structure::XmlCDataSectionSyntax* src);
      void clone(structure::XmlCommentSyntax* dest, const structure::XmlCommentSyntax* src);
      void clone(structure::XmlCrefAttributeSyntax* dest, const structure::XmlCrefAttributeSyntax* src);
      void clone(structure::XmlElementEndTagSyntax* dest, const structure::XmlElementEndTagSyntax* src);
      void clone(structure::XmlElementStartTagSyntax* dest, const structure::XmlElementStartTagSyntax* src);
      void clone(structure::XmlElementSyntax* dest, const structure::XmlElementSyntax* src);
      void clone(structure::XmlEmptyElementSyntax* dest, const structure::XmlEmptyElementSyntax* src);
      void clone(structure::XmlNameAttributeSyntax* dest, const structure::XmlNameAttributeSyntax* src);
      void clone(structure::XmlNameSyntax* dest, const structure::XmlNameSyntax* src);
      void clone(structure::XmlNodeSyntax* dest, const structure::XmlNodeSyntax* src);
      void clone(structure::XmlPrefixSyntax* dest, const structure::XmlPrefixSyntax* src);
      void clone(structure::XmlProcessingInstructionSyntax* dest, const structure::XmlProcessingInstructionSyntax* src);
      void clone(structure::XmlTextAttributeSyntax* dest, const structure::XmlTextAttributeSyntax* src);
      void clone(structure::XmlTextSyntax* dest, const structure::XmlTextSyntax* src);
  }; // AlgorithmDeepCopy


}}}
#endif

