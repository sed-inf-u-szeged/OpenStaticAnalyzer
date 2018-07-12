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

#ifndef _CSHARP_VISITORGRAPHML_H_
#define _CSHARP_VISITORGRAPHML_H_

#include "csharp/inc/csharp.h"
#include "io/inc/GraphmlIO.h"

/**
* \file VisitorGraphml.h
* \brief Contains declaration of VisitorGraphml class.
*/

namespace columbus { namespace csharp { namespace asg {

  /**
  * \brief Exports the ASG to Graphml format.
  */
  class VisitorGraphml : public Visitor {
    public:
      typedef bool(*NodeCompareFunc)(const base::Base&);

      /**
      * \brief Constructor for VisitorGraphml.
      */
      VisitorGraphml(columbus::io::GraphmlIO& io, std::set< std::string>& edgeFilter, unsigned int maxDrawingDepth = 0);

      /**
      * \brief Destructor.
      */
      virtual ~VisitorGraphml();

      /**
      * \brief Give back to compare function
      */
      NodeCompareFunc getCompareFunctionToNode( std::string& nodeName);

      /**
      * \brief Create compare map
      */
      static std::map< std::string, NodeCompareFunc> create_map(){
        std::map< std::string, NodeCompareFunc> cmpTable;
        cmpTable.insert( std::make_pair( "Positioned", &Common::getIsPositioned));
        cmpTable.insert( std::make_pair( "AliasQualifiedNameSyntax", &Common::getIsAliasQualifiedNameSyntax));
        cmpTable.insert( std::make_pair( "AnonymousFunctionExpressionSyntax", &Common::getIsAnonymousFunctionExpressionSyntax));
        cmpTable.insert( std::make_pair( "AnonymousMethodExpressionSyntax", &Common::getIsAnonymousMethodExpressionSyntax));
        cmpTable.insert( std::make_pair( "AnonymousObjectCreationExpressionSyntax", &Common::getIsAnonymousObjectCreationExpressionSyntax));
        cmpTable.insert( std::make_pair( "ArrayCreationExpressionSyntax", &Common::getIsArrayCreationExpressionSyntax));
        cmpTable.insert( std::make_pair( "ArrayTypeSyntax", &Common::getIsArrayTypeSyntax));
        cmpTable.insert( std::make_pair( "AssignmentExpressionSyntax", &Common::getIsAssignmentExpressionSyntax));
        cmpTable.insert( std::make_pair( "AwaitExpressionSyntax", &Common::getIsAwaitExpressionSyntax));
        cmpTable.insert( std::make_pair( "BaseExpressionSyntax", &Common::getIsBaseExpressionSyntax));
        cmpTable.insert( std::make_pair( "BinaryExpressionSyntax", &Common::getIsBinaryExpressionSyntax));
        cmpTable.insert( std::make_pair( "CastExpressionSyntax", &Common::getIsCastExpressionSyntax));
        cmpTable.insert( std::make_pair( "CheckedExpressionSyntax", &Common::getIsCheckedExpressionSyntax));
        cmpTable.insert( std::make_pair( "ConditionalAccessExpressionSyntax", &Common::getIsConditionalAccessExpressionSyntax));
        cmpTable.insert( std::make_pair( "ConditionalExpressionSyntax", &Common::getIsConditionalExpressionSyntax));
        cmpTable.insert( std::make_pair( "DefaultExpressionSyntax", &Common::getIsDefaultExpressionSyntax));
        cmpTable.insert( std::make_pair( "ElementAccessExpressionSyntax", &Common::getIsElementAccessExpressionSyntax));
        cmpTable.insert( std::make_pair( "ElementBindingExpressionSyntax", &Common::getIsElementBindingExpressionSyntax));
        cmpTable.insert( std::make_pair( "ExpressionSyntax", &Common::getIsExpressionSyntax));
        cmpTable.insert( std::make_pair( "GenericNameSyntax", &Common::getIsGenericNameSyntax));
        cmpTable.insert( std::make_pair( "IdentifierNameSyntax", &Common::getIsIdentifierNameSyntax));
        cmpTable.insert( std::make_pair( "ImplicitArrayCreationExpressionSyntax", &Common::getIsImplicitArrayCreationExpressionSyntax));
        cmpTable.insert( std::make_pair( "ImplicitElementAccessSyntax", &Common::getIsImplicitElementAccessSyntax));
        cmpTable.insert( std::make_pair( "InitializerExpressionSyntax", &Common::getIsInitializerExpressionSyntax));
        cmpTable.insert( std::make_pair( "InstanceExpressionSyntax", &Common::getIsInstanceExpressionSyntax));
        cmpTable.insert( std::make_pair( "InterpolatedStringExpressionSyntax", &Common::getIsInterpolatedStringExpressionSyntax));
        cmpTable.insert( std::make_pair( "InvocationExpressionSyntax", &Common::getIsInvocationExpressionSyntax));
        cmpTable.insert( std::make_pair( "LambdaExpressionSyntax", &Common::getIsLambdaExpressionSyntax));
        cmpTable.insert( std::make_pair( "LiteralExpressionSyntax", &Common::getIsLiteralExpressionSyntax));
        cmpTable.insert( std::make_pair( "MakeRefExpressionSyntax", &Common::getIsMakeRefExpressionSyntax));
        cmpTable.insert( std::make_pair( "MemberAccessExpressionSyntax", &Common::getIsMemberAccessExpressionSyntax));
        cmpTable.insert( std::make_pair( "MemberBindingExpressionSyntax", &Common::getIsMemberBindingExpressionSyntax));
        cmpTable.insert( std::make_pair( "NameSyntax", &Common::getIsNameSyntax));
        cmpTable.insert( std::make_pair( "NullableTypeSyntax", &Common::getIsNullableTypeSyntax));
        cmpTable.insert( std::make_pair( "ObjectCreationExpressionSyntax", &Common::getIsObjectCreationExpressionSyntax));
        cmpTable.insert( std::make_pair( "OmittedArraySizeExpressionSyntax", &Common::getIsOmittedArraySizeExpressionSyntax));
        cmpTable.insert( std::make_pair( "OmittedTypeArgumentSyntax", &Common::getIsOmittedTypeArgumentSyntax));
        cmpTable.insert( std::make_pair( "ParenthesizedExpressionSyntax", &Common::getIsParenthesizedExpressionSyntax));
        cmpTable.insert( std::make_pair( "ParenthesizedLambdaExpressionSyntax", &Common::getIsParenthesizedLambdaExpressionSyntax));
        cmpTable.insert( std::make_pair( "PointerTypeSyntax", &Common::getIsPointerTypeSyntax));
        cmpTable.insert( std::make_pair( "PostfixUnaryExpressionSyntax", &Common::getIsPostfixUnaryExpressionSyntax));
        cmpTable.insert( std::make_pair( "PredefinedTypeSyntax", &Common::getIsPredefinedTypeSyntax));
        cmpTable.insert( std::make_pair( "PrefixUnaryExpressionSyntax", &Common::getIsPrefixUnaryExpressionSyntax));
        cmpTable.insert( std::make_pair( "QualifiedNameSyntax", &Common::getIsQualifiedNameSyntax));
        cmpTable.insert( std::make_pair( "QueryExpressionSyntax", &Common::getIsQueryExpressionSyntax));
        cmpTable.insert( std::make_pair( "RefTypeExpressionSyntax", &Common::getIsRefTypeExpressionSyntax));
        cmpTable.insert( std::make_pair( "RefValueExpressionSyntax", &Common::getIsRefValueExpressionSyntax));
        cmpTable.insert( std::make_pair( "SimpleLambdaExpressionSyntax", &Common::getIsSimpleLambdaExpressionSyntax));
        cmpTable.insert( std::make_pair( "SimpleNameSyntax", &Common::getIsSimpleNameSyntax));
        cmpTable.insert( std::make_pair( "SizeOfExpressionSyntax", &Common::getIsSizeOfExpressionSyntax));
        cmpTable.insert( std::make_pair( "StackAllocArrayCreationExpressionSyntax", &Common::getIsStackAllocArrayCreationExpressionSyntax));
        cmpTable.insert( std::make_pair( "ThisExpressionSyntax", &Common::getIsThisExpressionSyntax));
        cmpTable.insert( std::make_pair( "TypeOfExpressionSyntax", &Common::getIsTypeOfExpressionSyntax));
        cmpTable.insert( std::make_pair( "TypeSyntax", &Common::getIsTypeSyntax));
        cmpTable.insert( std::make_pair( "BlockSyntax", &Common::getIsBlockSyntax));
        cmpTable.insert( std::make_pair( "BreakStatementSyntax", &Common::getIsBreakStatementSyntax));
        cmpTable.insert( std::make_pair( "CheckedStatementSyntax", &Common::getIsCheckedStatementSyntax));
        cmpTable.insert( std::make_pair( "ContinueStatementSyntax", &Common::getIsContinueStatementSyntax));
        cmpTable.insert( std::make_pair( "DoStatementSyntax", &Common::getIsDoStatementSyntax));
        cmpTable.insert( std::make_pair( "EmptyStatementSyntax", &Common::getIsEmptyStatementSyntax));
        cmpTable.insert( std::make_pair( "ExpressionStatementSyntax", &Common::getIsExpressionStatementSyntax));
        cmpTable.insert( std::make_pair( "FixedStatementSyntax", &Common::getIsFixedStatementSyntax));
        cmpTable.insert( std::make_pair( "ForEachStatementSyntax", &Common::getIsForEachStatementSyntax));
        cmpTable.insert( std::make_pair( "ForStatementSyntax", &Common::getIsForStatementSyntax));
        cmpTable.insert( std::make_pair( "GotoStatementSyntax", &Common::getIsGotoStatementSyntax));
        cmpTable.insert( std::make_pair( "IfStatementSyntax", &Common::getIsIfStatementSyntax));
        cmpTable.insert( std::make_pair( "LabeledStatementSyntax", &Common::getIsLabeledStatementSyntax));
        cmpTable.insert( std::make_pair( "LocalDeclarationStatementSyntax", &Common::getIsLocalDeclarationStatementSyntax));
        cmpTable.insert( std::make_pair( "LockStatementSyntax", &Common::getIsLockStatementSyntax));
        cmpTable.insert( std::make_pair( "ReturnStatementSyntax", &Common::getIsReturnStatementSyntax));
        cmpTable.insert( std::make_pair( "StatementSyntax", &Common::getIsStatementSyntax));
        cmpTable.insert( std::make_pair( "SwitchStatementSyntax", &Common::getIsSwitchStatementSyntax));
        cmpTable.insert( std::make_pair( "ThrowStatementSyntax", &Common::getIsThrowStatementSyntax));
        cmpTable.insert( std::make_pair( "TryStatementSyntax", &Common::getIsTryStatementSyntax));
        cmpTable.insert( std::make_pair( "UnsafeStatementSyntax", &Common::getIsUnsafeStatementSyntax));
        cmpTable.insert( std::make_pair( "UsingStatementSyntax", &Common::getIsUsingStatementSyntax));
        cmpTable.insert( std::make_pair( "WhileStatementSyntax", &Common::getIsWhileStatementSyntax));
        cmpTable.insert( std::make_pair( "YieldStatementSyntax", &Common::getIsYieldStatementSyntax));
        cmpTable.insert( std::make_pair( "AccessorDeclarationSyntax", &Common::getIsAccessorDeclarationSyntax));
        cmpTable.insert( std::make_pair( "AccessorListSyntax", &Common::getIsAccessorListSyntax));
        cmpTable.insert( std::make_pair( "AnonymousObjectMemberDeclaratorSyntax", &Common::getIsAnonymousObjectMemberDeclaratorSyntax));
        cmpTable.insert( std::make_pair( "ArgumentListSyntax", &Common::getIsArgumentListSyntax));
        cmpTable.insert( std::make_pair( "ArgumentSyntax", &Common::getIsArgumentSyntax));
        cmpTable.insert( std::make_pair( "ArrayRankSpecifierSyntax", &Common::getIsArrayRankSpecifierSyntax));
        cmpTable.insert( std::make_pair( "ArrowExpressionClauseSyntax", &Common::getIsArrowExpressionClauseSyntax));
        cmpTable.insert( std::make_pair( "AttributeArgumentListSyntax", &Common::getIsAttributeArgumentListSyntax));
        cmpTable.insert( std::make_pair( "AttributeArgumentSyntax", &Common::getIsAttributeArgumentSyntax));
        cmpTable.insert( std::make_pair( "AttributeListSyntax", &Common::getIsAttributeListSyntax));
        cmpTable.insert( std::make_pair( "AttributeSyntax", &Common::getIsAttributeSyntax));
        cmpTable.insert( std::make_pair( "AttributeTargetSpecifierSyntax", &Common::getIsAttributeTargetSpecifierSyntax));
        cmpTable.insert( std::make_pair( "BaseArgumentListSyntax", &Common::getIsBaseArgumentListSyntax));
        cmpTable.insert( std::make_pair( "BaseCrefParameterListSyntax", &Common::getIsBaseCrefParameterListSyntax));
        cmpTable.insert( std::make_pair( "BaseFieldDeclarationSyntax", &Common::getIsBaseFieldDeclarationSyntax));
        cmpTable.insert( std::make_pair( "BaseListSyntax", &Common::getIsBaseListSyntax));
        cmpTable.insert( std::make_pair( "BaseMethodDeclarationSyntax", &Common::getIsBaseMethodDeclarationSyntax));
        cmpTable.insert( std::make_pair( "BaseParameterListSyntax", &Common::getIsBaseParameterListSyntax));
        cmpTable.insert( std::make_pair( "BasePropertyDeclarationSyntax", &Common::getIsBasePropertyDeclarationSyntax));
        cmpTable.insert( std::make_pair( "BaseTypeDeclarationSyntax", &Common::getIsBaseTypeDeclarationSyntax));
        cmpTable.insert( std::make_pair( "BaseTypeSyntax", &Common::getIsBaseTypeSyntax));
        cmpTable.insert( std::make_pair( "BracketedArgumentListSyntax", &Common::getIsBracketedArgumentListSyntax));
        cmpTable.insert( std::make_pair( "BracketedParameterListSyntax", &Common::getIsBracketedParameterListSyntax));
        cmpTable.insert( std::make_pair( "CaseSwitchLabelSyntax", &Common::getIsCaseSwitchLabelSyntax));
        cmpTable.insert( std::make_pair( "CatchClauseSyntax", &Common::getIsCatchClauseSyntax));
        cmpTable.insert( std::make_pair( "CatchDeclarationSyntax", &Common::getIsCatchDeclarationSyntax));
        cmpTable.insert( std::make_pair( "CatchFilterClauseSyntax", &Common::getIsCatchFilterClauseSyntax));
        cmpTable.insert( std::make_pair( "ClassDeclarationSyntax", &Common::getIsClassDeclarationSyntax));
        cmpTable.insert( std::make_pair( "ClassOrStructConstraintSyntax", &Common::getIsClassOrStructConstraintSyntax));
        cmpTable.insert( std::make_pair( "CompilationUnitSyntax", &Common::getIsCompilationUnitSyntax));
        cmpTable.insert( std::make_pair( "ConstructorConstraintSyntax", &Common::getIsConstructorConstraintSyntax));
        cmpTable.insert( std::make_pair( "ConstructorDeclarationSyntax", &Common::getIsConstructorDeclarationSyntax));
        cmpTable.insert( std::make_pair( "ConstructorInitializerSyntax", &Common::getIsConstructorInitializerSyntax));
        cmpTable.insert( std::make_pair( "ConversionOperatorDeclarationSyntax", &Common::getIsConversionOperatorDeclarationSyntax));
        cmpTable.insert( std::make_pair( "ConversionOperatorMemberCrefSyntax", &Common::getIsConversionOperatorMemberCrefSyntax));
        cmpTable.insert( std::make_pair( "CrefBracketedParameterListSyntax", &Common::getIsCrefBracketedParameterListSyntax));
        cmpTable.insert( std::make_pair( "CrefParameterListSyntax", &Common::getIsCrefParameterListSyntax));
        cmpTable.insert( std::make_pair( "CrefParameterSyntax", &Common::getIsCrefParameterSyntax));
        cmpTable.insert( std::make_pair( "CrefSyntax", &Common::getIsCrefSyntax));
        cmpTable.insert( std::make_pair( "DefaultSwitchLabelSyntax", &Common::getIsDefaultSwitchLabelSyntax));
        cmpTable.insert( std::make_pair( "DelegateDeclarationSyntax", &Common::getIsDelegateDeclarationSyntax));
        cmpTable.insert( std::make_pair( "DestructorDeclarationSyntax", &Common::getIsDestructorDeclarationSyntax));
        cmpTable.insert( std::make_pair( "ElseClauseSyntax", &Common::getIsElseClauseSyntax));
        cmpTable.insert( std::make_pair( "EnumDeclarationSyntax", &Common::getIsEnumDeclarationSyntax));
        cmpTable.insert( std::make_pair( "EnumMemberDeclarationSyntax", &Common::getIsEnumMemberDeclarationSyntax));
        cmpTable.insert( std::make_pair( "EqualsValueClauseSyntax", &Common::getIsEqualsValueClauseSyntax));
        cmpTable.insert( std::make_pair( "EventDeclarationSyntax", &Common::getIsEventDeclarationSyntax));
        cmpTable.insert( std::make_pair( "EventFieldDeclarationSyntax", &Common::getIsEventFieldDeclarationSyntax));
        cmpTable.insert( std::make_pair( "ExplicitInterfaceSpecifierSyntax", &Common::getIsExplicitInterfaceSpecifierSyntax));
        cmpTable.insert( std::make_pair( "ExternAliasDirectiveSyntax", &Common::getIsExternAliasDirectiveSyntax));
        cmpTable.insert( std::make_pair( "FieldDeclarationSyntax", &Common::getIsFieldDeclarationSyntax));
        cmpTable.insert( std::make_pair( "FinallyClauseSyntax", &Common::getIsFinallyClauseSyntax));
        cmpTable.insert( std::make_pair( "FromClauseSyntax", &Common::getIsFromClauseSyntax));
        cmpTable.insert( std::make_pair( "GlobalStatementSyntax", &Common::getIsGlobalStatementSyntax));
        cmpTable.insert( std::make_pair( "GroupClauseSyntax", &Common::getIsGroupClauseSyntax));
        cmpTable.insert( std::make_pair( "IncompleteMemberSyntax", &Common::getIsIncompleteMemberSyntax));
        cmpTable.insert( std::make_pair( "IndexerDeclarationSyntax", &Common::getIsIndexerDeclarationSyntax));
        cmpTable.insert( std::make_pair( "IndexerMemberCrefSyntax", &Common::getIsIndexerMemberCrefSyntax));
        cmpTable.insert( std::make_pair( "InterfaceDeclarationSyntax", &Common::getIsInterfaceDeclarationSyntax));
        cmpTable.insert( std::make_pair( "InterpolatedStringContentSyntax", &Common::getIsInterpolatedStringContentSyntax));
        cmpTable.insert( std::make_pair( "InterpolatedStringTextSyntax", &Common::getIsInterpolatedStringTextSyntax));
        cmpTable.insert( std::make_pair( "InterpolationAlignmentClauseSyntax", &Common::getIsInterpolationAlignmentClauseSyntax));
        cmpTable.insert( std::make_pair( "InterpolationFormatClauseSyntax", &Common::getIsInterpolationFormatClauseSyntax));
        cmpTable.insert( std::make_pair( "InterpolationSyntax", &Common::getIsInterpolationSyntax));
        cmpTable.insert( std::make_pair( "JoinClauseSyntax", &Common::getIsJoinClauseSyntax));
        cmpTable.insert( std::make_pair( "JoinIntoClauseSyntax", &Common::getIsJoinIntoClauseSyntax));
        cmpTable.insert( std::make_pair( "LetClauseSyntax", &Common::getIsLetClauseSyntax));
        cmpTable.insert( std::make_pair( "MemberCrefSyntax", &Common::getIsMemberCrefSyntax));
        cmpTable.insert( std::make_pair( "MemberDeclarationSyntax", &Common::getIsMemberDeclarationSyntax));
        cmpTable.insert( std::make_pair( "MethodDeclarationSyntax", &Common::getIsMethodDeclarationSyntax));
        cmpTable.insert( std::make_pair( "NameColonSyntax", &Common::getIsNameColonSyntax));
        cmpTable.insert( std::make_pair( "NameEqualsSyntax", &Common::getIsNameEqualsSyntax));
        cmpTable.insert( std::make_pair( "NameMemberCrefSyntax", &Common::getIsNameMemberCrefSyntax));
        cmpTable.insert( std::make_pair( "NamespaceDeclarationSyntax", &Common::getIsNamespaceDeclarationSyntax));
        cmpTable.insert( std::make_pair( "OperatorDeclarationSyntax", &Common::getIsOperatorDeclarationSyntax));
        cmpTable.insert( std::make_pair( "OperatorMemberCrefSyntax", &Common::getIsOperatorMemberCrefSyntax));
        cmpTable.insert( std::make_pair( "OrderByClauseSyntax", &Common::getIsOrderByClauseSyntax));
        cmpTable.insert( std::make_pair( "OrderingSyntax", &Common::getIsOrderingSyntax));
        cmpTable.insert( std::make_pair( "ParameterListSyntax", &Common::getIsParameterListSyntax));
        cmpTable.insert( std::make_pair( "ParameterSyntax", &Common::getIsParameterSyntax));
        cmpTable.insert( std::make_pair( "PropertyDeclarationSyntax", &Common::getIsPropertyDeclarationSyntax));
        cmpTable.insert( std::make_pair( "QualifiedCrefSyntax", &Common::getIsQualifiedCrefSyntax));
        cmpTable.insert( std::make_pair( "QueryBodySyntax", &Common::getIsQueryBodySyntax));
        cmpTable.insert( std::make_pair( "QueryClauseSyntax", &Common::getIsQueryClauseSyntax));
        cmpTable.insert( std::make_pair( "QueryContinuationSyntax", &Common::getIsQueryContinuationSyntax));
        cmpTable.insert( std::make_pair( "SelectClauseSyntax", &Common::getIsSelectClauseSyntax));
        cmpTable.insert( std::make_pair( "SelectOrGroupClauseSyntax", &Common::getIsSelectOrGroupClauseSyntax));
        cmpTable.insert( std::make_pair( "SimpleBaseTypeSyntax", &Common::getIsSimpleBaseTypeSyntax));
        cmpTable.insert( std::make_pair( "StructDeclarationSyntax", &Common::getIsStructDeclarationSyntax));
        cmpTable.insert( std::make_pair( "SwitchLabelSyntax", &Common::getIsSwitchLabelSyntax));
        cmpTable.insert( std::make_pair( "SwitchSectionSyntax", &Common::getIsSwitchSectionSyntax));
        cmpTable.insert( std::make_pair( "SyntaxToken", &Common::getIsSyntaxToken));
        cmpTable.insert( std::make_pair( "TypeArgumentListSyntax", &Common::getIsTypeArgumentListSyntax));
        cmpTable.insert( std::make_pair( "TypeConstraintSyntax", &Common::getIsTypeConstraintSyntax));
        cmpTable.insert( std::make_pair( "TypeCrefSyntax", &Common::getIsTypeCrefSyntax));
        cmpTable.insert( std::make_pair( "TypeDeclarationSyntax", &Common::getIsTypeDeclarationSyntax));
        cmpTable.insert( std::make_pair( "TypeParameterConstraintClauseSyntax", &Common::getIsTypeParameterConstraintClauseSyntax));
        cmpTable.insert( std::make_pair( "TypeParameterConstraintSyntax", &Common::getIsTypeParameterConstraintSyntax));
        cmpTable.insert( std::make_pair( "TypeParameterListSyntax", &Common::getIsTypeParameterListSyntax));
        cmpTable.insert( std::make_pair( "TypeParameterSyntax", &Common::getIsTypeParameterSyntax));
        cmpTable.insert( std::make_pair( "UsingDirectiveSyntax", &Common::getIsUsingDirectiveSyntax));
        cmpTable.insert( std::make_pair( "VariableDeclarationSyntax", &Common::getIsVariableDeclarationSyntax));
        cmpTable.insert( std::make_pair( "VariableDeclaratorSyntax", &Common::getIsVariableDeclaratorSyntax));
        cmpTable.insert( std::make_pair( "WhereClauseSyntax", &Common::getIsWhereClauseSyntax));
        cmpTable.insert( std::make_pair( "XmlAttributeSyntax", &Common::getIsXmlAttributeSyntax));
        cmpTable.insert( std::make_pair( "XmlCDataSectionSyntax", &Common::getIsXmlCDataSectionSyntax));
        cmpTable.insert( std::make_pair( "XmlCommentSyntax", &Common::getIsXmlCommentSyntax));
        cmpTable.insert( std::make_pair( "XmlCrefAttributeSyntax", &Common::getIsXmlCrefAttributeSyntax));
        cmpTable.insert( std::make_pair( "XmlElementEndTagSyntax", &Common::getIsXmlElementEndTagSyntax));
        cmpTable.insert( std::make_pair( "XmlElementStartTagSyntax", &Common::getIsXmlElementStartTagSyntax));
        cmpTable.insert( std::make_pair( "XmlElementSyntax", &Common::getIsXmlElementSyntax));
        cmpTable.insert( std::make_pair( "XmlEmptyElementSyntax", &Common::getIsXmlEmptyElementSyntax));
        cmpTable.insert( std::make_pair( "XmlNameAttributeSyntax", &Common::getIsXmlNameAttributeSyntax));
        cmpTable.insert( std::make_pair( "XmlNameSyntax", &Common::getIsXmlNameSyntax));
        cmpTable.insert( std::make_pair( "XmlNodeSyntax", &Common::getIsXmlNodeSyntax));
        cmpTable.insert( std::make_pair( "XmlPrefixSyntax", &Common::getIsXmlPrefixSyntax));
        cmpTable.insert( std::make_pair( "XmlProcessingInstructionSyntax", &Common::getIsXmlProcessingInstructionSyntax));
        cmpTable.insert( std::make_pair( "XmlTextAttributeSyntax", &Common::getIsXmlTextAttributeSyntax));
        cmpTable.insert( std::make_pair( "XmlTextSyntax", &Common::getIsXmlTextSyntax));
        return cmpTable;
      }

      /**
      * \brief Filter node types by matching substring in qualified name
      */
      static const std::set< std::string> getNodeTypeSet(){
        std::set< std::string> types;
        types.insert( "base::Base");
        types.insert( "base::Positioned");
        types.insert( "expression::AliasQualifiedNameSyntax");
        types.insert( "expression::AnonymousFunctionExpressionSyntax");
        types.insert( "expression::AnonymousMethodExpressionSyntax");
        types.insert( "expression::AnonymousObjectCreationExpressionSyntax");
        types.insert( "expression::ArrayCreationExpressionSyntax");
        types.insert( "expression::ArrayTypeSyntax");
        types.insert( "expression::AssignmentExpressionSyntax");
        types.insert( "expression::AwaitExpressionSyntax");
        types.insert( "expression::BaseExpressionSyntax");
        types.insert( "expression::BinaryExpressionSyntax");
        types.insert( "expression::CastExpressionSyntax");
        types.insert( "expression::CheckedExpressionSyntax");
        types.insert( "expression::ConditionalAccessExpressionSyntax");
        types.insert( "expression::ConditionalExpressionSyntax");
        types.insert( "expression::DefaultExpressionSyntax");
        types.insert( "expression::ElementAccessExpressionSyntax");
        types.insert( "expression::ElementBindingExpressionSyntax");
        types.insert( "expression::ExpressionSyntax");
        types.insert( "expression::GenericNameSyntax");
        types.insert( "expression::IdentifierNameSyntax");
        types.insert( "expression::ImplicitArrayCreationExpressionSyntax");
        types.insert( "expression::ImplicitElementAccessSyntax");
        types.insert( "expression::InitializerExpressionSyntax");
        types.insert( "expression::InstanceExpressionSyntax");
        types.insert( "expression::InterpolatedStringExpressionSyntax");
        types.insert( "expression::InvocationExpressionSyntax");
        types.insert( "expression::LambdaExpressionSyntax");
        types.insert( "expression::LiteralExpressionSyntax");
        types.insert( "expression::MakeRefExpressionSyntax");
        types.insert( "expression::MemberAccessExpressionSyntax");
        types.insert( "expression::MemberBindingExpressionSyntax");
        types.insert( "expression::NameSyntax");
        types.insert( "expression::NullableTypeSyntax");
        types.insert( "expression::ObjectCreationExpressionSyntax");
        types.insert( "expression::OmittedArraySizeExpressionSyntax");
        types.insert( "expression::OmittedTypeArgumentSyntax");
        types.insert( "expression::ParenthesizedExpressionSyntax");
        types.insert( "expression::ParenthesizedLambdaExpressionSyntax");
        types.insert( "expression::PointerTypeSyntax");
        types.insert( "expression::PostfixUnaryExpressionSyntax");
        types.insert( "expression::PredefinedTypeSyntax");
        types.insert( "expression::PrefixUnaryExpressionSyntax");
        types.insert( "expression::QualifiedNameSyntax");
        types.insert( "expression::QueryExpressionSyntax");
        types.insert( "expression::RefTypeExpressionSyntax");
        types.insert( "expression::RefValueExpressionSyntax");
        types.insert( "expression::SimpleLambdaExpressionSyntax");
        types.insert( "expression::SimpleNameSyntax");
        types.insert( "expression::SizeOfExpressionSyntax");
        types.insert( "expression::StackAllocArrayCreationExpressionSyntax");
        types.insert( "expression::ThisExpressionSyntax");
        types.insert( "expression::TypeOfExpressionSyntax");
        types.insert( "expression::TypeSyntax");
        types.insert( "statement::BlockSyntax");
        types.insert( "statement::BreakStatementSyntax");
        types.insert( "statement::CheckedStatementSyntax");
        types.insert( "statement::ContinueStatementSyntax");
        types.insert( "statement::DoStatementSyntax");
        types.insert( "statement::EmptyStatementSyntax");
        types.insert( "statement::ExpressionStatementSyntax");
        types.insert( "statement::FixedStatementSyntax");
        types.insert( "statement::ForEachStatementSyntax");
        types.insert( "statement::ForStatementSyntax");
        types.insert( "statement::GotoStatementSyntax");
        types.insert( "statement::IfStatementSyntax");
        types.insert( "statement::LabeledStatementSyntax");
        types.insert( "statement::LocalDeclarationStatementSyntax");
        types.insert( "statement::LockStatementSyntax");
        types.insert( "statement::ReturnStatementSyntax");
        types.insert( "statement::StatementSyntax");
        types.insert( "statement::SwitchStatementSyntax");
        types.insert( "statement::ThrowStatementSyntax");
        types.insert( "statement::TryStatementSyntax");
        types.insert( "statement::UnsafeStatementSyntax");
        types.insert( "statement::UsingStatementSyntax");
        types.insert( "statement::WhileStatementSyntax");
        types.insert( "statement::YieldStatementSyntax");
        types.insert( "structure::AccessorDeclarationSyntax");
        types.insert( "structure::AccessorListSyntax");
        types.insert( "structure::AnonymousObjectMemberDeclaratorSyntax");
        types.insert( "structure::ArgumentListSyntax");
        types.insert( "structure::ArgumentSyntax");
        types.insert( "structure::ArrayRankSpecifierSyntax");
        types.insert( "structure::ArrowExpressionClauseSyntax");
        types.insert( "structure::AttributeArgumentListSyntax");
        types.insert( "structure::AttributeArgumentSyntax");
        types.insert( "structure::AttributeListSyntax");
        types.insert( "structure::AttributeSyntax");
        types.insert( "structure::AttributeTargetSpecifierSyntax");
        types.insert( "structure::BaseArgumentListSyntax");
        types.insert( "structure::BaseCrefParameterListSyntax");
        types.insert( "structure::BaseFieldDeclarationSyntax");
        types.insert( "structure::BaseListSyntax");
        types.insert( "structure::BaseMethodDeclarationSyntax");
        types.insert( "structure::BaseParameterListSyntax");
        types.insert( "structure::BasePropertyDeclarationSyntax");
        types.insert( "structure::BaseTypeDeclarationSyntax");
        types.insert( "structure::BaseTypeSyntax");
        types.insert( "structure::BracketedArgumentListSyntax");
        types.insert( "structure::BracketedParameterListSyntax");
        types.insert( "structure::CaseSwitchLabelSyntax");
        types.insert( "structure::CatchClauseSyntax");
        types.insert( "structure::CatchDeclarationSyntax");
        types.insert( "structure::CatchFilterClauseSyntax");
        types.insert( "structure::ClassDeclarationSyntax");
        types.insert( "structure::ClassOrStructConstraintSyntax");
        types.insert( "structure::CompilationUnitSyntax");
        types.insert( "structure::ConstructorConstraintSyntax");
        types.insert( "structure::ConstructorDeclarationSyntax");
        types.insert( "structure::ConstructorInitializerSyntax");
        types.insert( "structure::ConversionOperatorDeclarationSyntax");
        types.insert( "structure::ConversionOperatorMemberCrefSyntax");
        types.insert( "structure::CrefBracketedParameterListSyntax");
        types.insert( "structure::CrefParameterListSyntax");
        types.insert( "structure::CrefParameterSyntax");
        types.insert( "structure::CrefSyntax");
        types.insert( "structure::DefaultSwitchLabelSyntax");
        types.insert( "structure::DelegateDeclarationSyntax");
        types.insert( "structure::DestructorDeclarationSyntax");
        types.insert( "structure::ElseClauseSyntax");
        types.insert( "structure::EnumDeclarationSyntax");
        types.insert( "structure::EnumMemberDeclarationSyntax");
        types.insert( "structure::EqualsValueClauseSyntax");
        types.insert( "structure::EventDeclarationSyntax");
        types.insert( "structure::EventFieldDeclarationSyntax");
        types.insert( "structure::ExplicitInterfaceSpecifierSyntax");
        types.insert( "structure::ExternAliasDirectiveSyntax");
        types.insert( "structure::FieldDeclarationSyntax");
        types.insert( "structure::FinallyClauseSyntax");
        types.insert( "structure::FromClauseSyntax");
        types.insert( "structure::GlobalStatementSyntax");
        types.insert( "structure::GroupClauseSyntax");
        types.insert( "structure::IncompleteMemberSyntax");
        types.insert( "structure::IndexerDeclarationSyntax");
        types.insert( "structure::IndexerMemberCrefSyntax");
        types.insert( "structure::InterfaceDeclarationSyntax");
        types.insert( "structure::InterpolatedStringContentSyntax");
        types.insert( "structure::InterpolatedStringTextSyntax");
        types.insert( "structure::InterpolationAlignmentClauseSyntax");
        types.insert( "structure::InterpolationFormatClauseSyntax");
        types.insert( "structure::InterpolationSyntax");
        types.insert( "structure::JoinClauseSyntax");
        types.insert( "structure::JoinIntoClauseSyntax");
        types.insert( "structure::LetClauseSyntax");
        types.insert( "structure::MemberCrefSyntax");
        types.insert( "structure::MemberDeclarationSyntax");
        types.insert( "structure::MethodDeclarationSyntax");
        types.insert( "structure::NameColonSyntax");
        types.insert( "structure::NameEqualsSyntax");
        types.insert( "structure::NameMemberCrefSyntax");
        types.insert( "structure::NamespaceDeclarationSyntax");
        types.insert( "structure::OperatorDeclarationSyntax");
        types.insert( "structure::OperatorMemberCrefSyntax");
        types.insert( "structure::OrderByClauseSyntax");
        types.insert( "structure::OrderingSyntax");
        types.insert( "structure::ParameterListSyntax");
        types.insert( "structure::ParameterSyntax");
        types.insert( "structure::PropertyDeclarationSyntax");
        types.insert( "structure::QualifiedCrefSyntax");
        types.insert( "structure::QueryBodySyntax");
        types.insert( "structure::QueryClauseSyntax");
        types.insert( "structure::QueryContinuationSyntax");
        types.insert( "structure::SelectClauseSyntax");
        types.insert( "structure::SelectOrGroupClauseSyntax");
        types.insert( "structure::SimpleBaseTypeSyntax");
        types.insert( "structure::StructDeclarationSyntax");
        types.insert( "structure::SwitchLabelSyntax");
        types.insert( "structure::SwitchSectionSyntax");
        types.insert( "structure::SyntaxToken");
        types.insert( "structure::TypeArgumentListSyntax");
        types.insert( "structure::TypeConstraintSyntax");
        types.insert( "structure::TypeCrefSyntax");
        types.insert( "structure::TypeDeclarationSyntax");
        types.insert( "structure::TypeParameterConstraintClauseSyntax");
        types.insert( "structure::TypeParameterConstraintSyntax");
        types.insert( "structure::TypeParameterListSyntax");
        types.insert( "structure::TypeParameterSyntax");
        types.insert( "structure::UsingDirectiveSyntax");
        types.insert( "structure::VariableDeclarationSyntax");
        types.insert( "structure::VariableDeclaratorSyntax");
        types.insert( "structure::WhereClauseSyntax");
        types.insert( "structure::XmlAttributeSyntax");
        types.insert( "structure::XmlCDataSectionSyntax");
        types.insert( "structure::XmlCommentSyntax");
        types.insert( "structure::XmlCrefAttributeSyntax");
        types.insert( "structure::XmlElementEndTagSyntax");
        types.insert( "structure::XmlElementStartTagSyntax");
        types.insert( "structure::XmlElementSyntax");
        types.insert( "structure::XmlEmptyElementSyntax");
        types.insert( "structure::XmlNameAttributeSyntax");
        types.insert( "structure::XmlNameSyntax");
        types.insert( "structure::XmlNodeSyntax");
        types.insert( "structure::XmlPrefixSyntax");
        types.insert( "structure::XmlProcessingInstructionSyntax");
        types.insert( "structure::XmlTextAttributeSyntax");
        types.insert( "structure::XmlTextSyntax");
        return types;
      }

      /** \internal \brief It contains a table to node names and compare functions */
      static const std::map< std::string, NodeCompareFunc> compareTable;

      /**
      * \brief Set startpoint
      */
      void setStartPoint( NodeId startPoint);

      /**
      * \brief Set it is white color node or not
      */
      void setIsWhiteColor( bool isWhite);

      /**
      * \brief Set it is need to grouping tree nodes or not
      */
      void setIsGroupingTreeNodes( bool groupingTreeNodes);

      /**
      * \brief Set it is enabled to draw cross edges or not
      */
      void setIsEnableCrossEdge( bool isVisitCrossEdge);

      /**
      * \brief Set node type names to show attributes only of these types 
      */
      void addToFilterNodeTypeAttributes( std::string type);

      /**
      * \brief Set node type names to filtering
      */
      void addToFilterNodeType( std::string type);

      /**
      * \brief Set node type names to filtering
      */
      void filterNodeTypeMatch( std::string pattern);

      /**
      * \brief Writes the Graphml representation of the expression::AliasQualifiedNameSyntax node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const expression::AliasQualifiedNameSyntax& node, bool callVirtualBase = true);

      /**
      * \brief Converts the expression::AliasQualifiedNameSyntax node.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const expression::AliasQualifiedNameSyntax& node, bool callVirtualBase = true);

      /**
      * \brief Writes the Graphml representation of the expression::AnonymousMethodExpressionSyntax node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const expression::AnonymousMethodExpressionSyntax& node, bool callVirtualBase = true);

      /**
      * \brief Converts the expression::AnonymousMethodExpressionSyntax node.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const expression::AnonymousMethodExpressionSyntax& node, bool callVirtualBase = true);

      /**
      * \brief Writes the Graphml representation of the expression::AnonymousObjectCreationExpressionSyntax node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const expression::AnonymousObjectCreationExpressionSyntax& node, bool callVirtualBase = true);

      /**
      * \brief Converts the expression::AnonymousObjectCreationExpressionSyntax node.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const expression::AnonymousObjectCreationExpressionSyntax& node, bool callVirtualBase = true);

      /**
      * \brief Writes the Graphml representation of the expression::ArrayCreationExpressionSyntax node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const expression::ArrayCreationExpressionSyntax& node, bool callVirtualBase = true);

      /**
      * \brief Converts the expression::ArrayCreationExpressionSyntax node.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const expression::ArrayCreationExpressionSyntax& node, bool callVirtualBase = true);

      /**
      * \brief Writes the Graphml representation of the expression::ArrayTypeSyntax node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const expression::ArrayTypeSyntax& node, bool callVirtualBase = true);

      /**
      * \brief Converts the expression::ArrayTypeSyntax node.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const expression::ArrayTypeSyntax& node, bool callVirtualBase = true);

      /**
      * \brief Writes the Graphml representation of the expression::AssignmentExpressionSyntax node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const expression::AssignmentExpressionSyntax& node, bool callVirtualBase = true);

      /**
      * \brief Converts the expression::AssignmentExpressionSyntax node.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const expression::AssignmentExpressionSyntax& node, bool callVirtualBase = true);

      /**
      * \brief Writes the Graphml representation of the expression::AwaitExpressionSyntax node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const expression::AwaitExpressionSyntax& node, bool callVirtualBase = true);

      /**
      * \brief Converts the expression::AwaitExpressionSyntax node.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const expression::AwaitExpressionSyntax& node, bool callVirtualBase = true);

      /**
      * \brief Writes the Graphml representation of the expression::BaseExpressionSyntax node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const expression::BaseExpressionSyntax& node, bool callVirtualBase = true);

      /**
      * \brief Converts the expression::BaseExpressionSyntax node.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const expression::BaseExpressionSyntax& node, bool callVirtualBase = true);

      /**
      * \brief Writes the Graphml representation of the expression::BinaryExpressionSyntax node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const expression::BinaryExpressionSyntax& node, bool callVirtualBase = true);

      /**
      * \brief Converts the expression::BinaryExpressionSyntax node.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const expression::BinaryExpressionSyntax& node, bool callVirtualBase = true);

      /**
      * \brief Writes the Graphml representation of the expression::CastExpressionSyntax node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const expression::CastExpressionSyntax& node, bool callVirtualBase = true);

      /**
      * \brief Converts the expression::CastExpressionSyntax node.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const expression::CastExpressionSyntax& node, bool callVirtualBase = true);

      /**
      * \brief Writes the Graphml representation of the expression::CheckedExpressionSyntax node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const expression::CheckedExpressionSyntax& node, bool callVirtualBase = true);

      /**
      * \brief Converts the expression::CheckedExpressionSyntax node.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const expression::CheckedExpressionSyntax& node, bool callVirtualBase = true);

      /**
      * \brief Writes the Graphml representation of the expression::ConditionalAccessExpressionSyntax node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const expression::ConditionalAccessExpressionSyntax& node, bool callVirtualBase = true);

      /**
      * \brief Converts the expression::ConditionalAccessExpressionSyntax node.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const expression::ConditionalAccessExpressionSyntax& node, bool callVirtualBase = true);

      /**
      * \brief Writes the Graphml representation of the expression::ConditionalExpressionSyntax node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const expression::ConditionalExpressionSyntax& node, bool callVirtualBase = true);

      /**
      * \brief Converts the expression::ConditionalExpressionSyntax node.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const expression::ConditionalExpressionSyntax& node, bool callVirtualBase = true);

      /**
      * \brief Writes the Graphml representation of the expression::DefaultExpressionSyntax node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const expression::DefaultExpressionSyntax& node, bool callVirtualBase = true);

      /**
      * \brief Converts the expression::DefaultExpressionSyntax node.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const expression::DefaultExpressionSyntax& node, bool callVirtualBase = true);

      /**
      * \brief Writes the Graphml representation of the expression::ElementAccessExpressionSyntax node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const expression::ElementAccessExpressionSyntax& node, bool callVirtualBase = true);

      /**
      * \brief Converts the expression::ElementAccessExpressionSyntax node.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const expression::ElementAccessExpressionSyntax& node, bool callVirtualBase = true);

      /**
      * \brief Writes the Graphml representation of the expression::ElementBindingExpressionSyntax node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const expression::ElementBindingExpressionSyntax& node, bool callVirtualBase = true);

      /**
      * \brief Converts the expression::ElementBindingExpressionSyntax node.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const expression::ElementBindingExpressionSyntax& node, bool callVirtualBase = true);

      /**
      * \brief Writes the Graphml representation of the expression::GenericNameSyntax node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const expression::GenericNameSyntax& node, bool callVirtualBase = true);

      /**
      * \brief Converts the expression::GenericNameSyntax node.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const expression::GenericNameSyntax& node, bool callVirtualBase = true);

      /**
      * \brief Writes the Graphml representation of the expression::IdentifierNameSyntax node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const expression::IdentifierNameSyntax& node, bool callVirtualBase = true);

      /**
      * \brief Converts the expression::IdentifierNameSyntax node.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const expression::IdentifierNameSyntax& node, bool callVirtualBase = true);

      /**
      * \brief Writes the Graphml representation of the expression::ImplicitArrayCreationExpressionSyntax node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const expression::ImplicitArrayCreationExpressionSyntax& node, bool callVirtualBase = true);

      /**
      * \brief Converts the expression::ImplicitArrayCreationExpressionSyntax node.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const expression::ImplicitArrayCreationExpressionSyntax& node, bool callVirtualBase = true);

      /**
      * \brief Writes the Graphml representation of the expression::ImplicitElementAccessSyntax node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const expression::ImplicitElementAccessSyntax& node, bool callVirtualBase = true);

      /**
      * \brief Converts the expression::ImplicitElementAccessSyntax node.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const expression::ImplicitElementAccessSyntax& node, bool callVirtualBase = true);

      /**
      * \brief Writes the Graphml representation of the expression::InitializerExpressionSyntax node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const expression::InitializerExpressionSyntax& node, bool callVirtualBase = true);

      /**
      * \brief Converts the expression::InitializerExpressionSyntax node.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const expression::InitializerExpressionSyntax& node, bool callVirtualBase = true);

      /**
      * \brief Writes the Graphml representation of the expression::InterpolatedStringExpressionSyntax node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const expression::InterpolatedStringExpressionSyntax& node, bool callVirtualBase = true);

      /**
      * \brief Converts the expression::InterpolatedStringExpressionSyntax node.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const expression::InterpolatedStringExpressionSyntax& node, bool callVirtualBase = true);

      /**
      * \brief Writes the Graphml representation of the expression::InvocationExpressionSyntax node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const expression::InvocationExpressionSyntax& node, bool callVirtualBase = true);

      /**
      * \brief Converts the expression::InvocationExpressionSyntax node.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const expression::InvocationExpressionSyntax& node, bool callVirtualBase = true);

      /**
      * \brief Writes the Graphml representation of the expression::LiteralExpressionSyntax node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const expression::LiteralExpressionSyntax& node, bool callVirtualBase = true);

      /**
      * \brief Converts the expression::LiteralExpressionSyntax node.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const expression::LiteralExpressionSyntax& node, bool callVirtualBase = true);

      /**
      * \brief Writes the Graphml representation of the expression::MakeRefExpressionSyntax node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const expression::MakeRefExpressionSyntax& node, bool callVirtualBase = true);

      /**
      * \brief Converts the expression::MakeRefExpressionSyntax node.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const expression::MakeRefExpressionSyntax& node, bool callVirtualBase = true);

      /**
      * \brief Writes the Graphml representation of the expression::MemberAccessExpressionSyntax node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const expression::MemberAccessExpressionSyntax& node, bool callVirtualBase = true);

      /**
      * \brief Converts the expression::MemberAccessExpressionSyntax node.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const expression::MemberAccessExpressionSyntax& node, bool callVirtualBase = true);

      /**
      * \brief Writes the Graphml representation of the expression::MemberBindingExpressionSyntax node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const expression::MemberBindingExpressionSyntax& node, bool callVirtualBase = true);

      /**
      * \brief Converts the expression::MemberBindingExpressionSyntax node.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const expression::MemberBindingExpressionSyntax& node, bool callVirtualBase = true);

      /**
      * \brief Writes the Graphml representation of the expression::NullableTypeSyntax node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const expression::NullableTypeSyntax& node, bool callVirtualBase = true);

      /**
      * \brief Converts the expression::NullableTypeSyntax node.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const expression::NullableTypeSyntax& node, bool callVirtualBase = true);

      /**
      * \brief Writes the Graphml representation of the expression::ObjectCreationExpressionSyntax node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const expression::ObjectCreationExpressionSyntax& node, bool callVirtualBase = true);

      /**
      * \brief Converts the expression::ObjectCreationExpressionSyntax node.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const expression::ObjectCreationExpressionSyntax& node, bool callVirtualBase = true);

      /**
      * \brief Writes the Graphml representation of the expression::OmittedArraySizeExpressionSyntax node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const expression::OmittedArraySizeExpressionSyntax& node, bool callVirtualBase = true);

      /**
      * \brief Converts the expression::OmittedArraySizeExpressionSyntax node.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const expression::OmittedArraySizeExpressionSyntax& node, bool callVirtualBase = true);

      /**
      * \brief Writes the Graphml representation of the expression::OmittedTypeArgumentSyntax node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const expression::OmittedTypeArgumentSyntax& node, bool callVirtualBase = true);

      /**
      * \brief Converts the expression::OmittedTypeArgumentSyntax node.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const expression::OmittedTypeArgumentSyntax& node, bool callVirtualBase = true);

      /**
      * \brief Writes the Graphml representation of the expression::ParenthesizedExpressionSyntax node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const expression::ParenthesizedExpressionSyntax& node, bool callVirtualBase = true);

      /**
      * \brief Converts the expression::ParenthesizedExpressionSyntax node.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const expression::ParenthesizedExpressionSyntax& node, bool callVirtualBase = true);

      /**
      * \brief Writes the Graphml representation of the expression::ParenthesizedLambdaExpressionSyntax node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const expression::ParenthesizedLambdaExpressionSyntax& node, bool callVirtualBase = true);

      /**
      * \brief Converts the expression::ParenthesizedLambdaExpressionSyntax node.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const expression::ParenthesizedLambdaExpressionSyntax& node, bool callVirtualBase = true);

      /**
      * \brief Writes the Graphml representation of the expression::PointerTypeSyntax node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const expression::PointerTypeSyntax& node, bool callVirtualBase = true);

      /**
      * \brief Converts the expression::PointerTypeSyntax node.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const expression::PointerTypeSyntax& node, bool callVirtualBase = true);

      /**
      * \brief Writes the Graphml representation of the expression::PostfixUnaryExpressionSyntax node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const expression::PostfixUnaryExpressionSyntax& node, bool callVirtualBase = true);

      /**
      * \brief Converts the expression::PostfixUnaryExpressionSyntax node.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const expression::PostfixUnaryExpressionSyntax& node, bool callVirtualBase = true);

      /**
      * \brief Writes the Graphml representation of the expression::PredefinedTypeSyntax node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const expression::PredefinedTypeSyntax& node, bool callVirtualBase = true);

      /**
      * \brief Converts the expression::PredefinedTypeSyntax node.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const expression::PredefinedTypeSyntax& node, bool callVirtualBase = true);

      /**
      * \brief Writes the Graphml representation of the expression::PrefixUnaryExpressionSyntax node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const expression::PrefixUnaryExpressionSyntax& node, bool callVirtualBase = true);

      /**
      * \brief Converts the expression::PrefixUnaryExpressionSyntax node.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const expression::PrefixUnaryExpressionSyntax& node, bool callVirtualBase = true);

      /**
      * \brief Writes the Graphml representation of the expression::QualifiedNameSyntax node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const expression::QualifiedNameSyntax& node, bool callVirtualBase = true);

      /**
      * \brief Converts the expression::QualifiedNameSyntax node.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const expression::QualifiedNameSyntax& node, bool callVirtualBase = true);

      /**
      * \brief Writes the Graphml representation of the expression::QueryExpressionSyntax node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const expression::QueryExpressionSyntax& node, bool callVirtualBase = true);

      /**
      * \brief Converts the expression::QueryExpressionSyntax node.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const expression::QueryExpressionSyntax& node, bool callVirtualBase = true);

      /**
      * \brief Writes the Graphml representation of the expression::RefTypeExpressionSyntax node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const expression::RefTypeExpressionSyntax& node, bool callVirtualBase = true);

      /**
      * \brief Converts the expression::RefTypeExpressionSyntax node.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const expression::RefTypeExpressionSyntax& node, bool callVirtualBase = true);

      /**
      * \brief Writes the Graphml representation of the expression::RefValueExpressionSyntax node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const expression::RefValueExpressionSyntax& node, bool callVirtualBase = true);

      /**
      * \brief Converts the expression::RefValueExpressionSyntax node.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const expression::RefValueExpressionSyntax& node, bool callVirtualBase = true);

      /**
      * \brief Writes the Graphml representation of the expression::SimpleLambdaExpressionSyntax node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const expression::SimpleLambdaExpressionSyntax& node, bool callVirtualBase = true);

      /**
      * \brief Converts the expression::SimpleLambdaExpressionSyntax node.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const expression::SimpleLambdaExpressionSyntax& node, bool callVirtualBase = true);

      /**
      * \brief Writes the Graphml representation of the expression::SizeOfExpressionSyntax node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const expression::SizeOfExpressionSyntax& node, bool callVirtualBase = true);

      /**
      * \brief Converts the expression::SizeOfExpressionSyntax node.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const expression::SizeOfExpressionSyntax& node, bool callVirtualBase = true);

      /**
      * \brief Writes the Graphml representation of the expression::StackAllocArrayCreationExpressionSyntax node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const expression::StackAllocArrayCreationExpressionSyntax& node, bool callVirtualBase = true);

      /**
      * \brief Converts the expression::StackAllocArrayCreationExpressionSyntax node.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const expression::StackAllocArrayCreationExpressionSyntax& node, bool callVirtualBase = true);

      /**
      * \brief Writes the Graphml representation of the expression::ThisExpressionSyntax node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const expression::ThisExpressionSyntax& node, bool callVirtualBase = true);

      /**
      * \brief Converts the expression::ThisExpressionSyntax node.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const expression::ThisExpressionSyntax& node, bool callVirtualBase = true);

      /**
      * \brief Writes the Graphml representation of the expression::TypeOfExpressionSyntax node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const expression::TypeOfExpressionSyntax& node, bool callVirtualBase = true);

      /**
      * \brief Converts the expression::TypeOfExpressionSyntax node.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const expression::TypeOfExpressionSyntax& node, bool callVirtualBase = true);

      /**
      * \brief Writes the Graphml representation of the statement::BlockSyntax node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const statement::BlockSyntax& node, bool callVirtualBase = true);

      /**
      * \brief Converts the statement::BlockSyntax node.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const statement::BlockSyntax& node, bool callVirtualBase = true);

      /**
      * \brief Writes the Graphml representation of the statement::BreakStatementSyntax node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const statement::BreakStatementSyntax& node, bool callVirtualBase = true);

      /**
      * \brief Converts the statement::BreakStatementSyntax node.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const statement::BreakStatementSyntax& node, bool callVirtualBase = true);

      /**
      * \brief Writes the Graphml representation of the statement::CheckedStatementSyntax node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const statement::CheckedStatementSyntax& node, bool callVirtualBase = true);

      /**
      * \brief Converts the statement::CheckedStatementSyntax node.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const statement::CheckedStatementSyntax& node, bool callVirtualBase = true);

      /**
      * \brief Writes the Graphml representation of the statement::ContinueStatementSyntax node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const statement::ContinueStatementSyntax& node, bool callVirtualBase = true);

      /**
      * \brief Converts the statement::ContinueStatementSyntax node.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const statement::ContinueStatementSyntax& node, bool callVirtualBase = true);

      /**
      * \brief Writes the Graphml representation of the statement::DoStatementSyntax node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const statement::DoStatementSyntax& node, bool callVirtualBase = true);

      /**
      * \brief Converts the statement::DoStatementSyntax node.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const statement::DoStatementSyntax& node, bool callVirtualBase = true);

      /**
      * \brief Writes the Graphml representation of the statement::EmptyStatementSyntax node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const statement::EmptyStatementSyntax& node, bool callVirtualBase = true);

      /**
      * \brief Converts the statement::EmptyStatementSyntax node.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const statement::EmptyStatementSyntax& node, bool callVirtualBase = true);

      /**
      * \brief Writes the Graphml representation of the statement::ExpressionStatementSyntax node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const statement::ExpressionStatementSyntax& node, bool callVirtualBase = true);

      /**
      * \brief Converts the statement::ExpressionStatementSyntax node.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const statement::ExpressionStatementSyntax& node, bool callVirtualBase = true);

      /**
      * \brief Writes the Graphml representation of the statement::FixedStatementSyntax node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const statement::FixedStatementSyntax& node, bool callVirtualBase = true);

      /**
      * \brief Converts the statement::FixedStatementSyntax node.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const statement::FixedStatementSyntax& node, bool callVirtualBase = true);

      /**
      * \brief Writes the Graphml representation of the statement::ForEachStatementSyntax node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const statement::ForEachStatementSyntax& node, bool callVirtualBase = true);

      /**
      * \brief Converts the statement::ForEachStatementSyntax node.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const statement::ForEachStatementSyntax& node, bool callVirtualBase = true);

      /**
      * \brief Writes the Graphml representation of the statement::ForStatementSyntax node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const statement::ForStatementSyntax& node, bool callVirtualBase = true);

      /**
      * \brief Converts the statement::ForStatementSyntax node.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const statement::ForStatementSyntax& node, bool callVirtualBase = true);

      /**
      * \brief Writes the Graphml representation of the statement::GotoStatementSyntax node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const statement::GotoStatementSyntax& node, bool callVirtualBase = true);

      /**
      * \brief Converts the statement::GotoStatementSyntax node.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const statement::GotoStatementSyntax& node, bool callVirtualBase = true);

      /**
      * \brief Writes the Graphml representation of the statement::IfStatementSyntax node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const statement::IfStatementSyntax& node, bool callVirtualBase = true);

      /**
      * \brief Converts the statement::IfStatementSyntax node.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const statement::IfStatementSyntax& node, bool callVirtualBase = true);

      /**
      * \brief Writes the Graphml representation of the statement::LabeledStatementSyntax node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const statement::LabeledStatementSyntax& node, bool callVirtualBase = true);

      /**
      * \brief Converts the statement::LabeledStatementSyntax node.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const statement::LabeledStatementSyntax& node, bool callVirtualBase = true);

      /**
      * \brief Writes the Graphml representation of the statement::LocalDeclarationStatementSyntax node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const statement::LocalDeclarationStatementSyntax& node, bool callVirtualBase = true);

      /**
      * \brief Converts the statement::LocalDeclarationStatementSyntax node.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const statement::LocalDeclarationStatementSyntax& node, bool callVirtualBase = true);

      /**
      * \brief Writes the Graphml representation of the statement::LockStatementSyntax node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const statement::LockStatementSyntax& node, bool callVirtualBase = true);

      /**
      * \brief Converts the statement::LockStatementSyntax node.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const statement::LockStatementSyntax& node, bool callVirtualBase = true);

      /**
      * \brief Writes the Graphml representation of the statement::ReturnStatementSyntax node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const statement::ReturnStatementSyntax& node, bool callVirtualBase = true);

      /**
      * \brief Converts the statement::ReturnStatementSyntax node.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const statement::ReturnStatementSyntax& node, bool callVirtualBase = true);

      /**
      * \brief Writes the Graphml representation of the statement::SwitchStatementSyntax node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const statement::SwitchStatementSyntax& node, bool callVirtualBase = true);

      /**
      * \brief Converts the statement::SwitchStatementSyntax node.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const statement::SwitchStatementSyntax& node, bool callVirtualBase = true);

      /**
      * \brief Writes the Graphml representation of the statement::ThrowStatementSyntax node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const statement::ThrowStatementSyntax& node, bool callVirtualBase = true);

      /**
      * \brief Converts the statement::ThrowStatementSyntax node.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const statement::ThrowStatementSyntax& node, bool callVirtualBase = true);

      /**
      * \brief Writes the Graphml representation of the statement::TryStatementSyntax node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const statement::TryStatementSyntax& node, bool callVirtualBase = true);

      /**
      * \brief Converts the statement::TryStatementSyntax node.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const statement::TryStatementSyntax& node, bool callVirtualBase = true);

      /**
      * \brief Writes the Graphml representation of the statement::UnsafeStatementSyntax node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const statement::UnsafeStatementSyntax& node, bool callVirtualBase = true);

      /**
      * \brief Converts the statement::UnsafeStatementSyntax node.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const statement::UnsafeStatementSyntax& node, bool callVirtualBase = true);

      /**
      * \brief Writes the Graphml representation of the statement::UsingStatementSyntax node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const statement::UsingStatementSyntax& node, bool callVirtualBase = true);

      /**
      * \brief Converts the statement::UsingStatementSyntax node.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const statement::UsingStatementSyntax& node, bool callVirtualBase = true);

      /**
      * \brief Writes the Graphml representation of the statement::WhileStatementSyntax node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const statement::WhileStatementSyntax& node, bool callVirtualBase = true);

      /**
      * \brief Converts the statement::WhileStatementSyntax node.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const statement::WhileStatementSyntax& node, bool callVirtualBase = true);

      /**
      * \brief Writes the Graphml representation of the statement::YieldStatementSyntax node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const statement::YieldStatementSyntax& node, bool callVirtualBase = true);

      /**
      * \brief Converts the statement::YieldStatementSyntax node.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const statement::YieldStatementSyntax& node, bool callVirtualBase = true);

      /**
      * \brief Writes the Graphml representation of the structure::AccessorDeclarationSyntax node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const structure::AccessorDeclarationSyntax& node, bool callVirtualBase = true);

      /**
      * \brief Converts the structure::AccessorDeclarationSyntax node.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const structure::AccessorDeclarationSyntax& node, bool callVirtualBase = true);

      /**
      * \brief Writes the Graphml representation of the structure::AccessorListSyntax node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const structure::AccessorListSyntax& node, bool callVirtualBase = true);

      /**
      * \brief Converts the structure::AccessorListSyntax node.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const structure::AccessorListSyntax& node, bool callVirtualBase = true);

      /**
      * \brief Writes the Graphml representation of the structure::AnonymousObjectMemberDeclaratorSyntax node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const structure::AnonymousObjectMemberDeclaratorSyntax& node, bool callVirtualBase = true);

      /**
      * \brief Converts the structure::AnonymousObjectMemberDeclaratorSyntax node.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const structure::AnonymousObjectMemberDeclaratorSyntax& node, bool callVirtualBase = true);

      /**
      * \brief Writes the Graphml representation of the structure::ArgumentListSyntax node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const structure::ArgumentListSyntax& node, bool callVirtualBase = true);

      /**
      * \brief Converts the structure::ArgumentListSyntax node.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const structure::ArgumentListSyntax& node, bool callVirtualBase = true);

      /**
      * \brief Writes the Graphml representation of the structure::ArgumentSyntax node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const structure::ArgumentSyntax& node, bool callVirtualBase = true);

      /**
      * \brief Converts the structure::ArgumentSyntax node.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const structure::ArgumentSyntax& node, bool callVirtualBase = true);

      /**
      * \brief Writes the Graphml representation of the structure::ArrayRankSpecifierSyntax node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const structure::ArrayRankSpecifierSyntax& node, bool callVirtualBase = true);

      /**
      * \brief Converts the structure::ArrayRankSpecifierSyntax node.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const structure::ArrayRankSpecifierSyntax& node, bool callVirtualBase = true);

      /**
      * \brief Writes the Graphml representation of the structure::ArrowExpressionClauseSyntax node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const structure::ArrowExpressionClauseSyntax& node, bool callVirtualBase = true);

      /**
      * \brief Converts the structure::ArrowExpressionClauseSyntax node.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const structure::ArrowExpressionClauseSyntax& node, bool callVirtualBase = true);

      /**
      * \brief Writes the Graphml representation of the structure::AttributeArgumentListSyntax node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const structure::AttributeArgumentListSyntax& node, bool callVirtualBase = true);

      /**
      * \brief Converts the structure::AttributeArgumentListSyntax node.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const structure::AttributeArgumentListSyntax& node, bool callVirtualBase = true);

      /**
      * \brief Writes the Graphml representation of the structure::AttributeArgumentSyntax node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const structure::AttributeArgumentSyntax& node, bool callVirtualBase = true);

      /**
      * \brief Converts the structure::AttributeArgumentSyntax node.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const structure::AttributeArgumentSyntax& node, bool callVirtualBase = true);

      /**
      * \brief Writes the Graphml representation of the structure::AttributeListSyntax node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const structure::AttributeListSyntax& node, bool callVirtualBase = true);

      /**
      * \brief Converts the structure::AttributeListSyntax node.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const structure::AttributeListSyntax& node, bool callVirtualBase = true);

      /**
      * \brief Writes the Graphml representation of the structure::AttributeSyntax node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const structure::AttributeSyntax& node, bool callVirtualBase = true);

      /**
      * \brief Converts the structure::AttributeSyntax node.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const structure::AttributeSyntax& node, bool callVirtualBase = true);

      /**
      * \brief Writes the Graphml representation of the structure::AttributeTargetSpecifierSyntax node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const structure::AttributeTargetSpecifierSyntax& node, bool callVirtualBase = true);

      /**
      * \brief Converts the structure::AttributeTargetSpecifierSyntax node.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const structure::AttributeTargetSpecifierSyntax& node, bool callVirtualBase = true);

      /**
      * \brief Writes the Graphml representation of the structure::BaseListSyntax node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const structure::BaseListSyntax& node, bool callVirtualBase = true);

      /**
      * \brief Converts the structure::BaseListSyntax node.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const structure::BaseListSyntax& node, bool callVirtualBase = true);

      /**
      * \brief Writes the Graphml representation of the structure::BracketedArgumentListSyntax node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const structure::BracketedArgumentListSyntax& node, bool callVirtualBase = true);

      /**
      * \brief Converts the structure::BracketedArgumentListSyntax node.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const structure::BracketedArgumentListSyntax& node, bool callVirtualBase = true);

      /**
      * \brief Writes the Graphml representation of the structure::BracketedParameterListSyntax node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const structure::BracketedParameterListSyntax& node, bool callVirtualBase = true);

      /**
      * \brief Converts the structure::BracketedParameterListSyntax node.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const structure::BracketedParameterListSyntax& node, bool callVirtualBase = true);

      /**
      * \brief Writes the Graphml representation of the structure::CaseSwitchLabelSyntax node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const structure::CaseSwitchLabelSyntax& node, bool callVirtualBase = true);

      /**
      * \brief Converts the structure::CaseSwitchLabelSyntax node.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const structure::CaseSwitchLabelSyntax& node, bool callVirtualBase = true);

      /**
      * \brief Writes the Graphml representation of the structure::CatchClauseSyntax node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const structure::CatchClauseSyntax& node, bool callVirtualBase = true);

      /**
      * \brief Converts the structure::CatchClauseSyntax node.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const structure::CatchClauseSyntax& node, bool callVirtualBase = true);

      /**
      * \brief Writes the Graphml representation of the structure::CatchDeclarationSyntax node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const structure::CatchDeclarationSyntax& node, bool callVirtualBase = true);

      /**
      * \brief Converts the structure::CatchDeclarationSyntax node.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const structure::CatchDeclarationSyntax& node, bool callVirtualBase = true);

      /**
      * \brief Writes the Graphml representation of the structure::CatchFilterClauseSyntax node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const structure::CatchFilterClauseSyntax& node, bool callVirtualBase = true);

      /**
      * \brief Converts the structure::CatchFilterClauseSyntax node.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const structure::CatchFilterClauseSyntax& node, bool callVirtualBase = true);

      /**
      * \brief Writes the Graphml representation of the structure::ClassDeclarationSyntax node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const structure::ClassDeclarationSyntax& node, bool callVirtualBase = true);

      /**
      * \brief Converts the structure::ClassDeclarationSyntax node.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const structure::ClassDeclarationSyntax& node, bool callVirtualBase = true);

      /**
      * \brief Writes the Graphml representation of the structure::ClassOrStructConstraintSyntax node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const structure::ClassOrStructConstraintSyntax& node, bool callVirtualBase = true);

      /**
      * \brief Converts the structure::ClassOrStructConstraintSyntax node.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const structure::ClassOrStructConstraintSyntax& node, bool callVirtualBase = true);

      /**
      * \brief Writes the Graphml representation of the structure::CompilationUnitSyntax node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const structure::CompilationUnitSyntax& node, bool callVirtualBase = true);

      /**
      * \brief Converts the structure::CompilationUnitSyntax node.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const structure::CompilationUnitSyntax& node, bool callVirtualBase = true);

      /**
      * \brief Writes the Graphml representation of the structure::ConstructorConstraintSyntax node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const structure::ConstructorConstraintSyntax& node, bool callVirtualBase = true);

      /**
      * \brief Converts the structure::ConstructorConstraintSyntax node.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const structure::ConstructorConstraintSyntax& node, bool callVirtualBase = true);

      /**
      * \brief Writes the Graphml representation of the structure::ConstructorDeclarationSyntax node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const structure::ConstructorDeclarationSyntax& node, bool callVirtualBase = true);

      /**
      * \brief Converts the structure::ConstructorDeclarationSyntax node.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const structure::ConstructorDeclarationSyntax& node, bool callVirtualBase = true);

      /**
      * \brief Writes the Graphml representation of the structure::ConstructorInitializerSyntax node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const structure::ConstructorInitializerSyntax& node, bool callVirtualBase = true);

      /**
      * \brief Converts the structure::ConstructorInitializerSyntax node.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const structure::ConstructorInitializerSyntax& node, bool callVirtualBase = true);

      /**
      * \brief Writes the Graphml representation of the structure::ConversionOperatorDeclarationSyntax node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const structure::ConversionOperatorDeclarationSyntax& node, bool callVirtualBase = true);

      /**
      * \brief Converts the structure::ConversionOperatorDeclarationSyntax node.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const structure::ConversionOperatorDeclarationSyntax& node, bool callVirtualBase = true);

      /**
      * \brief Writes the Graphml representation of the structure::ConversionOperatorMemberCrefSyntax node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const structure::ConversionOperatorMemberCrefSyntax& node, bool callVirtualBase = true);

      /**
      * \brief Converts the structure::ConversionOperatorMemberCrefSyntax node.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const structure::ConversionOperatorMemberCrefSyntax& node, bool callVirtualBase = true);

      /**
      * \brief Writes the Graphml representation of the structure::CrefBracketedParameterListSyntax node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const structure::CrefBracketedParameterListSyntax& node, bool callVirtualBase = true);

      /**
      * \brief Converts the structure::CrefBracketedParameterListSyntax node.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const structure::CrefBracketedParameterListSyntax& node, bool callVirtualBase = true);

      /**
      * \brief Writes the Graphml representation of the structure::CrefParameterListSyntax node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const structure::CrefParameterListSyntax& node, bool callVirtualBase = true);

      /**
      * \brief Converts the structure::CrefParameterListSyntax node.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const structure::CrefParameterListSyntax& node, bool callVirtualBase = true);

      /**
      * \brief Writes the Graphml representation of the structure::CrefParameterSyntax node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const structure::CrefParameterSyntax& node, bool callVirtualBase = true);

      /**
      * \brief Converts the structure::CrefParameterSyntax node.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const structure::CrefParameterSyntax& node, bool callVirtualBase = true);

      /**
      * \brief Writes the Graphml representation of the structure::DefaultSwitchLabelSyntax node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const structure::DefaultSwitchLabelSyntax& node, bool callVirtualBase = true);

      /**
      * \brief Converts the structure::DefaultSwitchLabelSyntax node.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const structure::DefaultSwitchLabelSyntax& node, bool callVirtualBase = true);

      /**
      * \brief Writes the Graphml representation of the structure::DelegateDeclarationSyntax node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const structure::DelegateDeclarationSyntax& node, bool callVirtualBase = true);

      /**
      * \brief Converts the structure::DelegateDeclarationSyntax node.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const structure::DelegateDeclarationSyntax& node, bool callVirtualBase = true);

      /**
      * \brief Writes the Graphml representation of the structure::DestructorDeclarationSyntax node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const structure::DestructorDeclarationSyntax& node, bool callVirtualBase = true);

      /**
      * \brief Converts the structure::DestructorDeclarationSyntax node.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const structure::DestructorDeclarationSyntax& node, bool callVirtualBase = true);

      /**
      * \brief Writes the Graphml representation of the structure::ElseClauseSyntax node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const structure::ElseClauseSyntax& node, bool callVirtualBase = true);

      /**
      * \brief Converts the structure::ElseClauseSyntax node.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const structure::ElseClauseSyntax& node, bool callVirtualBase = true);

      /**
      * \brief Writes the Graphml representation of the structure::EnumDeclarationSyntax node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const structure::EnumDeclarationSyntax& node, bool callVirtualBase = true);

      /**
      * \brief Converts the structure::EnumDeclarationSyntax node.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const structure::EnumDeclarationSyntax& node, bool callVirtualBase = true);

      /**
      * \brief Writes the Graphml representation of the structure::EnumMemberDeclarationSyntax node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const structure::EnumMemberDeclarationSyntax& node, bool callVirtualBase = true);

      /**
      * \brief Converts the structure::EnumMemberDeclarationSyntax node.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const structure::EnumMemberDeclarationSyntax& node, bool callVirtualBase = true);

      /**
      * \brief Writes the Graphml representation of the structure::EqualsValueClauseSyntax node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const structure::EqualsValueClauseSyntax& node, bool callVirtualBase = true);

      /**
      * \brief Converts the structure::EqualsValueClauseSyntax node.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const structure::EqualsValueClauseSyntax& node, bool callVirtualBase = true);

      /**
      * \brief Writes the Graphml representation of the structure::EventDeclarationSyntax node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const structure::EventDeclarationSyntax& node, bool callVirtualBase = true);

      /**
      * \brief Converts the structure::EventDeclarationSyntax node.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const structure::EventDeclarationSyntax& node, bool callVirtualBase = true);

      /**
      * \brief Writes the Graphml representation of the structure::EventFieldDeclarationSyntax node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const structure::EventFieldDeclarationSyntax& node, bool callVirtualBase = true);

      /**
      * \brief Converts the structure::EventFieldDeclarationSyntax node.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const structure::EventFieldDeclarationSyntax& node, bool callVirtualBase = true);

      /**
      * \brief Writes the Graphml representation of the structure::ExplicitInterfaceSpecifierSyntax node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const structure::ExplicitInterfaceSpecifierSyntax& node, bool callVirtualBase = true);

      /**
      * \brief Converts the structure::ExplicitInterfaceSpecifierSyntax node.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const structure::ExplicitInterfaceSpecifierSyntax& node, bool callVirtualBase = true);

      /**
      * \brief Writes the Graphml representation of the structure::ExternAliasDirectiveSyntax node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const structure::ExternAliasDirectiveSyntax& node, bool callVirtualBase = true);

      /**
      * \brief Converts the structure::ExternAliasDirectiveSyntax node.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const structure::ExternAliasDirectiveSyntax& node, bool callVirtualBase = true);

      /**
      * \brief Writes the Graphml representation of the structure::FieldDeclarationSyntax node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const structure::FieldDeclarationSyntax& node, bool callVirtualBase = true);

      /**
      * \brief Converts the structure::FieldDeclarationSyntax node.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const structure::FieldDeclarationSyntax& node, bool callVirtualBase = true);

      /**
      * \brief Writes the Graphml representation of the structure::FinallyClauseSyntax node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const structure::FinallyClauseSyntax& node, bool callVirtualBase = true);

      /**
      * \brief Converts the structure::FinallyClauseSyntax node.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const structure::FinallyClauseSyntax& node, bool callVirtualBase = true);

      /**
      * \brief Writes the Graphml representation of the structure::FromClauseSyntax node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const structure::FromClauseSyntax& node, bool callVirtualBase = true);

      /**
      * \brief Converts the structure::FromClauseSyntax node.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const structure::FromClauseSyntax& node, bool callVirtualBase = true);

      /**
      * \brief Writes the Graphml representation of the structure::GlobalStatementSyntax node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const structure::GlobalStatementSyntax& node, bool callVirtualBase = true);

      /**
      * \brief Converts the structure::GlobalStatementSyntax node.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const structure::GlobalStatementSyntax& node, bool callVirtualBase = true);

      /**
      * \brief Writes the Graphml representation of the structure::GroupClauseSyntax node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const structure::GroupClauseSyntax& node, bool callVirtualBase = true);

      /**
      * \brief Converts the structure::GroupClauseSyntax node.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const structure::GroupClauseSyntax& node, bool callVirtualBase = true);

      /**
      * \brief Writes the Graphml representation of the structure::IncompleteMemberSyntax node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const structure::IncompleteMemberSyntax& node, bool callVirtualBase = true);

      /**
      * \brief Converts the structure::IncompleteMemberSyntax node.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const structure::IncompleteMemberSyntax& node, bool callVirtualBase = true);

      /**
      * \brief Writes the Graphml representation of the structure::IndexerDeclarationSyntax node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const structure::IndexerDeclarationSyntax& node, bool callVirtualBase = true);

      /**
      * \brief Converts the structure::IndexerDeclarationSyntax node.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const structure::IndexerDeclarationSyntax& node, bool callVirtualBase = true);

      /**
      * \brief Writes the Graphml representation of the structure::IndexerMemberCrefSyntax node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const structure::IndexerMemberCrefSyntax& node, bool callVirtualBase = true);

      /**
      * \brief Converts the structure::IndexerMemberCrefSyntax node.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const structure::IndexerMemberCrefSyntax& node, bool callVirtualBase = true);

      /**
      * \brief Writes the Graphml representation of the structure::InterfaceDeclarationSyntax node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const structure::InterfaceDeclarationSyntax& node, bool callVirtualBase = true);

      /**
      * \brief Converts the structure::InterfaceDeclarationSyntax node.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const structure::InterfaceDeclarationSyntax& node, bool callVirtualBase = true);

      /**
      * \brief Writes the Graphml representation of the structure::InterpolatedStringTextSyntax node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const structure::InterpolatedStringTextSyntax& node, bool callVirtualBase = true);

      /**
      * \brief Converts the structure::InterpolatedStringTextSyntax node.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const structure::InterpolatedStringTextSyntax& node, bool callVirtualBase = true);

      /**
      * \brief Writes the Graphml representation of the structure::InterpolationAlignmentClauseSyntax node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const structure::InterpolationAlignmentClauseSyntax& node, bool callVirtualBase = true);

      /**
      * \brief Converts the structure::InterpolationAlignmentClauseSyntax node.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const structure::InterpolationAlignmentClauseSyntax& node, bool callVirtualBase = true);

      /**
      * \brief Writes the Graphml representation of the structure::InterpolationFormatClauseSyntax node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const structure::InterpolationFormatClauseSyntax& node, bool callVirtualBase = true);

      /**
      * \brief Converts the structure::InterpolationFormatClauseSyntax node.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const structure::InterpolationFormatClauseSyntax& node, bool callVirtualBase = true);

      /**
      * \brief Writes the Graphml representation of the structure::InterpolationSyntax node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const structure::InterpolationSyntax& node, bool callVirtualBase = true);

      /**
      * \brief Converts the structure::InterpolationSyntax node.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const structure::InterpolationSyntax& node, bool callVirtualBase = true);

      /**
      * \brief Writes the Graphml representation of the structure::JoinClauseSyntax node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const structure::JoinClauseSyntax& node, bool callVirtualBase = true);

      /**
      * \brief Converts the structure::JoinClauseSyntax node.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const structure::JoinClauseSyntax& node, bool callVirtualBase = true);

      /**
      * \brief Writes the Graphml representation of the structure::JoinIntoClauseSyntax node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const structure::JoinIntoClauseSyntax& node, bool callVirtualBase = true);

      /**
      * \brief Converts the structure::JoinIntoClauseSyntax node.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const structure::JoinIntoClauseSyntax& node, bool callVirtualBase = true);

      /**
      * \brief Writes the Graphml representation of the structure::LetClauseSyntax node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const structure::LetClauseSyntax& node, bool callVirtualBase = true);

      /**
      * \brief Converts the structure::LetClauseSyntax node.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const structure::LetClauseSyntax& node, bool callVirtualBase = true);

      /**
      * \brief Writes the Graphml representation of the structure::MethodDeclarationSyntax node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const structure::MethodDeclarationSyntax& node, bool callVirtualBase = true);

      /**
      * \brief Converts the structure::MethodDeclarationSyntax node.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const structure::MethodDeclarationSyntax& node, bool callVirtualBase = true);

      /**
      * \brief Writes the Graphml representation of the structure::NameColonSyntax node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const structure::NameColonSyntax& node, bool callVirtualBase = true);

      /**
      * \brief Converts the structure::NameColonSyntax node.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const structure::NameColonSyntax& node, bool callVirtualBase = true);

      /**
      * \brief Writes the Graphml representation of the structure::NameEqualsSyntax node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const structure::NameEqualsSyntax& node, bool callVirtualBase = true);

      /**
      * \brief Converts the structure::NameEqualsSyntax node.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const structure::NameEqualsSyntax& node, bool callVirtualBase = true);

      /**
      * \brief Writes the Graphml representation of the structure::NameMemberCrefSyntax node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const structure::NameMemberCrefSyntax& node, bool callVirtualBase = true);

      /**
      * \brief Converts the structure::NameMemberCrefSyntax node.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const structure::NameMemberCrefSyntax& node, bool callVirtualBase = true);

      /**
      * \brief Writes the Graphml representation of the structure::NamespaceDeclarationSyntax node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const structure::NamespaceDeclarationSyntax& node, bool callVirtualBase = true);

      /**
      * \brief Converts the structure::NamespaceDeclarationSyntax node.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const structure::NamespaceDeclarationSyntax& node, bool callVirtualBase = true);

      /**
      * \brief Writes the Graphml representation of the structure::OperatorDeclarationSyntax node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const structure::OperatorDeclarationSyntax& node, bool callVirtualBase = true);

      /**
      * \brief Converts the structure::OperatorDeclarationSyntax node.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const structure::OperatorDeclarationSyntax& node, bool callVirtualBase = true);

      /**
      * \brief Writes the Graphml representation of the structure::OperatorMemberCrefSyntax node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const structure::OperatorMemberCrefSyntax& node, bool callVirtualBase = true);

      /**
      * \brief Converts the structure::OperatorMemberCrefSyntax node.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const structure::OperatorMemberCrefSyntax& node, bool callVirtualBase = true);

      /**
      * \brief Writes the Graphml representation of the structure::OrderByClauseSyntax node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const structure::OrderByClauseSyntax& node, bool callVirtualBase = true);

      /**
      * \brief Converts the structure::OrderByClauseSyntax node.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const structure::OrderByClauseSyntax& node, bool callVirtualBase = true);

      /**
      * \brief Writes the Graphml representation of the structure::OrderingSyntax node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const structure::OrderingSyntax& node, bool callVirtualBase = true);

      /**
      * \brief Converts the structure::OrderingSyntax node.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const structure::OrderingSyntax& node, bool callVirtualBase = true);

      /**
      * \brief Writes the Graphml representation of the structure::ParameterListSyntax node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const structure::ParameterListSyntax& node, bool callVirtualBase = true);

      /**
      * \brief Converts the structure::ParameterListSyntax node.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const structure::ParameterListSyntax& node, bool callVirtualBase = true);

      /**
      * \brief Writes the Graphml representation of the structure::ParameterSyntax node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const structure::ParameterSyntax& node, bool callVirtualBase = true);

      /**
      * \brief Converts the structure::ParameterSyntax node.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const structure::ParameterSyntax& node, bool callVirtualBase = true);

      /**
      * \brief Writes the Graphml representation of the structure::PropertyDeclarationSyntax node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const structure::PropertyDeclarationSyntax& node, bool callVirtualBase = true);

      /**
      * \brief Converts the structure::PropertyDeclarationSyntax node.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const structure::PropertyDeclarationSyntax& node, bool callVirtualBase = true);

      /**
      * \brief Writes the Graphml representation of the structure::QualifiedCrefSyntax node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const structure::QualifiedCrefSyntax& node, bool callVirtualBase = true);

      /**
      * \brief Converts the structure::QualifiedCrefSyntax node.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const structure::QualifiedCrefSyntax& node, bool callVirtualBase = true);

      /**
      * \brief Writes the Graphml representation of the structure::QueryBodySyntax node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const structure::QueryBodySyntax& node, bool callVirtualBase = true);

      /**
      * \brief Converts the structure::QueryBodySyntax node.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const structure::QueryBodySyntax& node, bool callVirtualBase = true);

      /**
      * \brief Writes the Graphml representation of the structure::QueryContinuationSyntax node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const structure::QueryContinuationSyntax& node, bool callVirtualBase = true);

      /**
      * \brief Converts the structure::QueryContinuationSyntax node.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const structure::QueryContinuationSyntax& node, bool callVirtualBase = true);

      /**
      * \brief Writes the Graphml representation of the structure::SelectClauseSyntax node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const structure::SelectClauseSyntax& node, bool callVirtualBase = true);

      /**
      * \brief Converts the structure::SelectClauseSyntax node.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const structure::SelectClauseSyntax& node, bool callVirtualBase = true);

      /**
      * \brief Writes the Graphml representation of the structure::SimpleBaseTypeSyntax node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const structure::SimpleBaseTypeSyntax& node, bool callVirtualBase = true);

      /**
      * \brief Converts the structure::SimpleBaseTypeSyntax node.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const structure::SimpleBaseTypeSyntax& node, bool callVirtualBase = true);

      /**
      * \brief Writes the Graphml representation of the structure::StructDeclarationSyntax node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const structure::StructDeclarationSyntax& node, bool callVirtualBase = true);

      /**
      * \brief Converts the structure::StructDeclarationSyntax node.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const structure::StructDeclarationSyntax& node, bool callVirtualBase = true);

      /**
      * \brief Writes the Graphml representation of the structure::SwitchSectionSyntax node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const structure::SwitchSectionSyntax& node, bool callVirtualBase = true);

      /**
      * \brief Converts the structure::SwitchSectionSyntax node.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const structure::SwitchSectionSyntax& node, bool callVirtualBase = true);

      /**
      * \brief Writes the Graphml representation of the structure::SyntaxToken node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const structure::SyntaxToken& node, bool callVirtualBase = true);

      /**
      * \brief Converts the structure::SyntaxToken node.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const structure::SyntaxToken& node, bool callVirtualBase = true);

      /**
      * \brief Writes the Graphml representation of the structure::TypeArgumentListSyntax node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const structure::TypeArgumentListSyntax& node, bool callVirtualBase = true);

      /**
      * \brief Converts the structure::TypeArgumentListSyntax node.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const structure::TypeArgumentListSyntax& node, bool callVirtualBase = true);

      /**
      * \brief Writes the Graphml representation of the structure::TypeConstraintSyntax node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const structure::TypeConstraintSyntax& node, bool callVirtualBase = true);

      /**
      * \brief Converts the structure::TypeConstraintSyntax node.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const structure::TypeConstraintSyntax& node, bool callVirtualBase = true);

      /**
      * \brief Writes the Graphml representation of the structure::TypeCrefSyntax node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const structure::TypeCrefSyntax& node, bool callVirtualBase = true);

      /**
      * \brief Converts the structure::TypeCrefSyntax node.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const structure::TypeCrefSyntax& node, bool callVirtualBase = true);

      /**
      * \brief Writes the Graphml representation of the structure::TypeParameterConstraintClauseSyntax node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const structure::TypeParameterConstraintClauseSyntax& node, bool callVirtualBase = true);

      /**
      * \brief Converts the structure::TypeParameterConstraintClauseSyntax node.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const structure::TypeParameterConstraintClauseSyntax& node, bool callVirtualBase = true);

      /**
      * \brief Writes the Graphml representation of the structure::TypeParameterListSyntax node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const structure::TypeParameterListSyntax& node, bool callVirtualBase = true);

      /**
      * \brief Converts the structure::TypeParameterListSyntax node.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const structure::TypeParameterListSyntax& node, bool callVirtualBase = true);

      /**
      * \brief Writes the Graphml representation of the structure::TypeParameterSyntax node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const structure::TypeParameterSyntax& node, bool callVirtualBase = true);

      /**
      * \brief Converts the structure::TypeParameterSyntax node.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const structure::TypeParameterSyntax& node, bool callVirtualBase = true);

      /**
      * \brief Writes the Graphml representation of the structure::UsingDirectiveSyntax node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const structure::UsingDirectiveSyntax& node, bool callVirtualBase = true);

      /**
      * \brief Converts the structure::UsingDirectiveSyntax node.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const structure::UsingDirectiveSyntax& node, bool callVirtualBase = true);

      /**
      * \brief Writes the Graphml representation of the structure::VariableDeclarationSyntax node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const structure::VariableDeclarationSyntax& node, bool callVirtualBase = true);

      /**
      * \brief Converts the structure::VariableDeclarationSyntax node.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const structure::VariableDeclarationSyntax& node, bool callVirtualBase = true);

      /**
      * \brief Writes the Graphml representation of the structure::VariableDeclaratorSyntax node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const structure::VariableDeclaratorSyntax& node, bool callVirtualBase = true);

      /**
      * \brief Converts the structure::VariableDeclaratorSyntax node.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const structure::VariableDeclaratorSyntax& node, bool callVirtualBase = true);

      /**
      * \brief Writes the Graphml representation of the structure::WhereClauseSyntax node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const structure::WhereClauseSyntax& node, bool callVirtualBase = true);

      /**
      * \brief Converts the structure::WhereClauseSyntax node.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const structure::WhereClauseSyntax& node, bool callVirtualBase = true);

      /**
      * \brief Writes the Graphml representation of the structure::XmlCDataSectionSyntax node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const structure::XmlCDataSectionSyntax& node, bool callVirtualBase = true);

      /**
      * \brief Converts the structure::XmlCDataSectionSyntax node.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const structure::XmlCDataSectionSyntax& node, bool callVirtualBase = true);

      /**
      * \brief Writes the Graphml representation of the structure::XmlCommentSyntax node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const structure::XmlCommentSyntax& node, bool callVirtualBase = true);

      /**
      * \brief Converts the structure::XmlCommentSyntax node.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const structure::XmlCommentSyntax& node, bool callVirtualBase = true);

      /**
      * \brief Writes the Graphml representation of the structure::XmlCrefAttributeSyntax node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const structure::XmlCrefAttributeSyntax& node, bool callVirtualBase = true);

      /**
      * \brief Converts the structure::XmlCrefAttributeSyntax node.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const structure::XmlCrefAttributeSyntax& node, bool callVirtualBase = true);

      /**
      * \brief Writes the Graphml representation of the structure::XmlElementEndTagSyntax node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const structure::XmlElementEndTagSyntax& node, bool callVirtualBase = true);

      /**
      * \brief Converts the structure::XmlElementEndTagSyntax node.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const structure::XmlElementEndTagSyntax& node, bool callVirtualBase = true);

      /**
      * \brief Writes the Graphml representation of the structure::XmlElementStartTagSyntax node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const structure::XmlElementStartTagSyntax& node, bool callVirtualBase = true);

      /**
      * \brief Converts the structure::XmlElementStartTagSyntax node.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const structure::XmlElementStartTagSyntax& node, bool callVirtualBase = true);

      /**
      * \brief Writes the Graphml representation of the structure::XmlElementSyntax node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const structure::XmlElementSyntax& node, bool callVirtualBase = true);

      /**
      * \brief Converts the structure::XmlElementSyntax node.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const structure::XmlElementSyntax& node, bool callVirtualBase = true);

      /**
      * \brief Writes the Graphml representation of the structure::XmlEmptyElementSyntax node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const structure::XmlEmptyElementSyntax& node, bool callVirtualBase = true);

      /**
      * \brief Converts the structure::XmlEmptyElementSyntax node.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const structure::XmlEmptyElementSyntax& node, bool callVirtualBase = true);

      /**
      * \brief Writes the Graphml representation of the structure::XmlNameAttributeSyntax node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const structure::XmlNameAttributeSyntax& node, bool callVirtualBase = true);

      /**
      * \brief Converts the structure::XmlNameAttributeSyntax node.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const structure::XmlNameAttributeSyntax& node, bool callVirtualBase = true);

      /**
      * \brief Writes the Graphml representation of the structure::XmlNameSyntax node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const structure::XmlNameSyntax& node, bool callVirtualBase = true);

      /**
      * \brief Converts the structure::XmlNameSyntax node.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const structure::XmlNameSyntax& node, bool callVirtualBase = true);

      /**
      * \brief Writes the Graphml representation of the structure::XmlPrefixSyntax node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const structure::XmlPrefixSyntax& node, bool callVirtualBase = true);

      /**
      * \brief Converts the structure::XmlPrefixSyntax node.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const structure::XmlPrefixSyntax& node, bool callVirtualBase = true);

      /**
      * \brief Writes the Graphml representation of the structure::XmlProcessingInstructionSyntax node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const structure::XmlProcessingInstructionSyntax& node, bool callVirtualBase = true);

      /**
      * \brief Converts the structure::XmlProcessingInstructionSyntax node.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const structure::XmlProcessingInstructionSyntax& node, bool callVirtualBase = true);

      /**
      * \brief Writes the Graphml representation of the structure::XmlTextAttributeSyntax node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const structure::XmlTextAttributeSyntax& node, bool callVirtualBase = true);

      /**
      * \brief Converts the structure::XmlTextAttributeSyntax node.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const structure::XmlTextAttributeSyntax& node, bool callVirtualBase = true);

      /**
      * \brief Writes the Graphml representation of the structure::XmlTextSyntax node into the output file.
      * \param node [in] The node which is visited.
      */
      virtual void visit(const structure::XmlTextSyntax& node, bool callVirtualBase = true);

      /**
      * \brief Converts the structure::XmlTextSyntax node.
      * \param node [in] The node which is visited.
      */
      virtual void visitEnd(const structure::XmlTextSyntax& node, bool callVirtualBase = true);

      /**
      * \brief Edge  visitor for Alias edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitAliasQualifiedNameSyntax_Alias(const expression::AliasQualifiedNameSyntax& begin, const expression::IdentifierNameSyntax& end);

      /**
      * \brief Edge  visitor for Name edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitAliasQualifiedNameSyntax_Name(const expression::AliasQualifiedNameSyntax& begin, const expression::SimpleNameSyntax& end);

      /**
      * \brief Edge  visitor for Body edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitAnonymousFunctionExpressionSyntax_Body(const expression::AnonymousFunctionExpressionSyntax& begin, const base::Positioned& end);

      /**
      * \brief Edge  visitor for ParameterList edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitAnonymousMethodExpressionSyntax_ParameterList(const expression::AnonymousMethodExpressionSyntax& begin, const structure::ParameterListSyntax& end);

      /**
      * \brief Edge  visitor for Initializers edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitAnonymousObjectCreationExpressionSyntax_Initializers(const expression::AnonymousObjectCreationExpressionSyntax& begin, const structure::AnonymousObjectMemberDeclaratorSyntax& end);

      /**
      * \brief Edge  visitor for Initializer edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitArrayCreationExpressionSyntax_Initializer(const expression::ArrayCreationExpressionSyntax& begin, const expression::InitializerExpressionSyntax& end);

      /**
      * \brief Edge  visitor for Type edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitArrayCreationExpressionSyntax_Type(const expression::ArrayCreationExpressionSyntax& begin, const expression::ArrayTypeSyntax& end);

      /**
      * \brief Edge  visitor for ElementType edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitArrayTypeSyntax_ElementType(const expression::ArrayTypeSyntax& begin, const expression::TypeSyntax& end);

      /**
      * \brief Edge  visitor for RankSpecifiers edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitArrayTypeSyntax_RankSpecifiers(const expression::ArrayTypeSyntax& begin, const structure::ArrayRankSpecifierSyntax& end);

      /**
      * \brief Edge visitor for EventAccessorCall edge which.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitAssignmentExpressionSyntax_EventAccessorCall(const expression::AssignmentExpressionSyntax& begin, const structure::AccessorDeclarationSyntax& end);

      /**
      * \brief Edge  visitor for Left edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitAssignmentExpressionSyntax_Left(const expression::AssignmentExpressionSyntax& begin, const expression::ExpressionSyntax& end);

      /**
      * \brief Edge visitor for OverloadedOperatorCall edge which.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitAssignmentExpressionSyntax_OverloadedOperatorCall(const expression::AssignmentExpressionSyntax& begin, const structure::OperatorDeclarationSyntax& end);

      /**
      * \brief Edge  visitor for Right edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitAssignmentExpressionSyntax_Right(const expression::AssignmentExpressionSyntax& begin, const expression::ExpressionSyntax& end);

      /**
      * \brief Edge  visitor for Expression edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitAwaitExpressionSyntax_Expression(const expression::AwaitExpressionSyntax& begin, const expression::ExpressionSyntax& end);

      /**
      * \brief Edge  visitor for Left edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitBinaryExpressionSyntax_Left(const expression::BinaryExpressionSyntax& begin, const expression::ExpressionSyntax& end);

      /**
      * \brief Edge visitor for OverloadedOperatorCall edge which.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitBinaryExpressionSyntax_OverloadedOperatorCall(const expression::BinaryExpressionSyntax& begin, const structure::OperatorDeclarationSyntax& end);

      /**
      * \brief Edge  visitor for Right edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitBinaryExpressionSyntax_Right(const expression::BinaryExpressionSyntax& begin, const expression::ExpressionSyntax& end);

      /**
      * \brief Edge visitor for ConversionOperatorCall edge which.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitCastExpressionSyntax_ConversionOperatorCall(const expression::CastExpressionSyntax& begin, const structure::ConversionOperatorDeclarationSyntax& end);

      /**
      * \brief Edge  visitor for Expression edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitCastExpressionSyntax_Expression(const expression::CastExpressionSyntax& begin, const expression::ExpressionSyntax& end);

      /**
      * \brief Edge  visitor for Type edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitCastExpressionSyntax_Type(const expression::CastExpressionSyntax& begin, const expression::TypeSyntax& end);

      /**
      * \brief Edge  visitor for Expression edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitCheckedExpressionSyntax_Expression(const expression::CheckedExpressionSyntax& begin, const expression::ExpressionSyntax& end);

      /**
      * \brief Edge  visitor for Expression edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitConditionalAccessExpressionSyntax_Expression(const expression::ConditionalAccessExpressionSyntax& begin, const expression::ExpressionSyntax& end);

      /**
      * \brief Edge  visitor for WhenNotNull edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitConditionalAccessExpressionSyntax_WhenNotNull(const expression::ConditionalAccessExpressionSyntax& begin, const expression::ExpressionSyntax& end);

      /**
      * \brief Edge  visitor for Condition edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitConditionalExpressionSyntax_Condition(const expression::ConditionalExpressionSyntax& begin, const expression::ExpressionSyntax& end);

      /**
      * \brief Edge  visitor for WhenFalse edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitConditionalExpressionSyntax_WhenFalse(const expression::ConditionalExpressionSyntax& begin, const expression::ExpressionSyntax& end);

      /**
      * \brief Edge  visitor for WhenTrue edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitConditionalExpressionSyntax_WhenTrue(const expression::ConditionalExpressionSyntax& begin, const expression::ExpressionSyntax& end);

      /**
      * \brief Edge  visitor for Type edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitDefaultExpressionSyntax_Type(const expression::DefaultExpressionSyntax& begin, const expression::TypeSyntax& end);

      /**
      * \brief Edge visitor for AccessorCall edge which.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitElementAccessExpressionSyntax_AccessorCall(const expression::ElementAccessExpressionSyntax& begin, const structure::AccessorDeclarationSyntax& end);

      /**
      * \brief Edge  visitor for ArgumentList edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitElementAccessExpressionSyntax_ArgumentList(const expression::ElementAccessExpressionSyntax& begin, const structure::BracketedArgumentListSyntax& end);

      /**
      * \brief Edge  visitor for Expression edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitElementAccessExpressionSyntax_Expression(const expression::ElementAccessExpressionSyntax& begin, const expression::ExpressionSyntax& end);

      /**
      * \brief Edge  visitor for ArgumentList edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitElementBindingExpressionSyntax_ArgumentList(const expression::ElementBindingExpressionSyntax& begin, const structure::BracketedArgumentListSyntax& end);

      /**
      * \brief Edge  visitor for TypeArgumentList edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitGenericNameSyntax_TypeArgumentList(const expression::GenericNameSyntax& begin, const structure::TypeArgumentListSyntax& end);

      /**
      * \brief Edge visitor for AccessorCall edge which.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitIdentifierNameSyntax_AccessorCall(const expression::IdentifierNameSyntax& begin, const structure::AccessorDeclarationSyntax& end);

      /**
      * \brief Edge visitor for Declaration edge which.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitIdentifierNameSyntax_Declaration(const expression::IdentifierNameSyntax& begin, const base::Positioned& end);

      /**
      * \brief Edge  visitor for Initializer edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitImplicitArrayCreationExpressionSyntax_Initializer(const expression::ImplicitArrayCreationExpressionSyntax& begin, const expression::InitializerExpressionSyntax& end);

      /**
      * \brief Edge  visitor for ArgumentList edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitImplicitElementAccessSyntax_ArgumentList(const expression::ImplicitElementAccessSyntax& begin, const structure::BracketedArgumentListSyntax& end);

      /**
      * \brief Edge  visitor for Expressions edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitInitializerExpressionSyntax_Expressions(const expression::InitializerExpressionSyntax& begin, const expression::ExpressionSyntax& end);

      /**
      * \brief Edge  visitor for Contents edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitInterpolatedStringExpressionSyntax_Contents(const expression::InterpolatedStringExpressionSyntax& begin, const structure::InterpolatedStringContentSyntax& end);

      /**
      * \brief Edge  visitor for ArgumentList edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitInvocationExpressionSyntax_ArgumentList(const expression::InvocationExpressionSyntax& begin, const structure::ArgumentListSyntax& end);

      /**
      * \brief Edge  visitor for Expression edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitInvocationExpressionSyntax_Expression(const expression::InvocationExpressionSyntax& begin, const expression::ExpressionSyntax& end);

      /**
      * \brief Edge visitor for MethodCall edge which.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitInvocationExpressionSyntax_MethodCall(const expression::InvocationExpressionSyntax& begin, const structure::MethodDeclarationSyntax& end);

      /**
      * \brief Edge  visitor for Expression edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitMakeRefExpressionSyntax_Expression(const expression::MakeRefExpressionSyntax& begin, const expression::ExpressionSyntax& end);

      /**
      * \brief Edge  visitor for Expression edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitMemberAccessExpressionSyntax_Expression(const expression::MemberAccessExpressionSyntax& begin, const expression::ExpressionSyntax& end);

      /**
      * \brief Edge  visitor for Name edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitMemberAccessExpressionSyntax_Name(const expression::MemberAccessExpressionSyntax& begin, const expression::SimpleNameSyntax& end);

      /**
      * \brief Edge  visitor for Name edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitMemberBindingExpressionSyntax_Name(const expression::MemberBindingExpressionSyntax& begin, const expression::SimpleNameSyntax& end);

      /**
      * \brief Edge  visitor for ElementType edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitNullableTypeSyntax_ElementType(const expression::NullableTypeSyntax& begin, const expression::TypeSyntax& end);

      /**
      * \brief Edge  visitor for ArgumentList edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitObjectCreationExpressionSyntax_ArgumentList(const expression::ObjectCreationExpressionSyntax& begin, const structure::ArgumentListSyntax& end);

      /**
      * \brief Edge visitor for ConstructorCall edge which.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitObjectCreationExpressionSyntax_ConstructorCall(const expression::ObjectCreationExpressionSyntax& begin, const structure::ConstructorDeclarationSyntax& end);

      /**
      * \brief Edge  visitor for Initializer edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitObjectCreationExpressionSyntax_Initializer(const expression::ObjectCreationExpressionSyntax& begin, const expression::InitializerExpressionSyntax& end);

      /**
      * \brief Edge  visitor for Type edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitObjectCreationExpressionSyntax_Type(const expression::ObjectCreationExpressionSyntax& begin, const expression::TypeSyntax& end);

      /**
      * \brief Edge  visitor for Expression edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitParenthesizedExpressionSyntax_Expression(const expression::ParenthesizedExpressionSyntax& begin, const expression::ExpressionSyntax& end);

      /**
      * \brief Edge  visitor for ParameterList edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitParenthesizedLambdaExpressionSyntax_ParameterList(const expression::ParenthesizedLambdaExpressionSyntax& begin, const structure::ParameterListSyntax& end);

      /**
      * \brief Edge  visitor for ElementType edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitPointerTypeSyntax_ElementType(const expression::PointerTypeSyntax& begin, const expression::TypeSyntax& end);

      /**
      * \brief Edge  visitor for Operand edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitPostfixUnaryExpressionSyntax_Operand(const expression::PostfixUnaryExpressionSyntax& begin, const expression::ExpressionSyntax& end);

      /**
      * \brief Edge visitor for OverloadedOperatorCall edge which.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitPostfixUnaryExpressionSyntax_OverloadedOperatorCall(const expression::PostfixUnaryExpressionSyntax& begin, const structure::OperatorDeclarationSyntax& end);

      /**
      * \brief Edge  visitor for Operand edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitPrefixUnaryExpressionSyntax_Operand(const expression::PrefixUnaryExpressionSyntax& begin, const expression::ExpressionSyntax& end);

      /**
      * \brief Edge visitor for OverloadedOperatorCall edge which.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitPrefixUnaryExpressionSyntax_OverloadedOperatorCall(const expression::PrefixUnaryExpressionSyntax& begin, const structure::OperatorDeclarationSyntax& end);

      /**
      * \brief Edge  visitor for Left edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitQualifiedNameSyntax_Left(const expression::QualifiedNameSyntax& begin, const expression::NameSyntax& end);

      /**
      * \brief Edge  visitor for Right edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitQualifiedNameSyntax_Right(const expression::QualifiedNameSyntax& begin, const expression::SimpleNameSyntax& end);

      /**
      * \brief Edge  visitor for Body edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitQueryExpressionSyntax_Body(const expression::QueryExpressionSyntax& begin, const structure::QueryBodySyntax& end);

      /**
      * \brief Edge  visitor for FromClause edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitQueryExpressionSyntax_FromClause(const expression::QueryExpressionSyntax& begin, const structure::FromClauseSyntax& end);

      /**
      * \brief Edge  visitor for Expression edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitRefTypeExpressionSyntax_Expression(const expression::RefTypeExpressionSyntax& begin, const expression::ExpressionSyntax& end);

      /**
      * \brief Edge  visitor for Expression edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitRefValueExpressionSyntax_Expression(const expression::RefValueExpressionSyntax& begin, const expression::ExpressionSyntax& end);

      /**
      * \brief Edge  visitor for Type edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitRefValueExpressionSyntax_Type(const expression::RefValueExpressionSyntax& begin, const expression::TypeSyntax& end);

      /**
      * \brief Edge  visitor for Parameter edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitSimpleLambdaExpressionSyntax_Parameter(const expression::SimpleLambdaExpressionSyntax& begin, const structure::ParameterSyntax& end);

      /**
      * \brief Edge  visitor for Type edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitSizeOfExpressionSyntax_Type(const expression::SizeOfExpressionSyntax& begin, const expression::TypeSyntax& end);

      /**
      * \brief Edge  visitor for Type edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitStackAllocArrayCreationExpressionSyntax_Type(const expression::StackAllocArrayCreationExpressionSyntax& begin, const expression::TypeSyntax& end);

      /**
      * \brief Edge  visitor for Type edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitTypeOfExpressionSyntax_Type(const expression::TypeOfExpressionSyntax& begin, const expression::TypeSyntax& end);

      /**
      * \brief Edge visitor for OriginalDefinition edge which.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitTypeSyntax_OriginalDefinition(const expression::TypeSyntax& begin, const structure::MemberDeclarationSyntax& end);

      /**
      * \brief Edge  visitor for Statements edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitBlockSyntax_Statements(const statement::BlockSyntax& begin, const statement::StatementSyntax& end);

      /**
      * \brief Edge  visitor for Block edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitCheckedStatementSyntax_Block(const statement::CheckedStatementSyntax& begin, const statement::BlockSyntax& end);

      /**
      * \brief Edge  visitor for Condition edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitDoStatementSyntax_Condition(const statement::DoStatementSyntax& begin, const expression::ExpressionSyntax& end);

      /**
      * \brief Edge  visitor for Statement edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitDoStatementSyntax_Statement(const statement::DoStatementSyntax& begin, const statement::StatementSyntax& end);

      /**
      * \brief Edge  visitor for Expression edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitExpressionStatementSyntax_Expression(const statement::ExpressionStatementSyntax& begin, const expression::ExpressionSyntax& end);

      /**
      * \brief Edge  visitor for Declaration edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitFixedStatementSyntax_Declaration(const statement::FixedStatementSyntax& begin, const structure::VariableDeclarationSyntax& end);

      /**
      * \brief Edge  visitor for Statement edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitFixedStatementSyntax_Statement(const statement::FixedStatementSyntax& begin, const statement::StatementSyntax& end);

      /**
      * \brief Edge  visitor for Expression edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitForEachStatementSyntax_Expression(const statement::ForEachStatementSyntax& begin, const expression::ExpressionSyntax& end);

      /**
      * \brief Edge  visitor for Statement edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitForEachStatementSyntax_Statement(const statement::ForEachStatementSyntax& begin, const statement::StatementSyntax& end);

      /**
      * \brief Edge  visitor for Type edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitForEachStatementSyntax_Type(const statement::ForEachStatementSyntax& begin, const expression::TypeSyntax& end);

      /**
      * \brief Edge  visitor for Condition edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitForStatementSyntax_Condition(const statement::ForStatementSyntax& begin, const expression::ExpressionSyntax& end);

      /**
      * \brief Edge  visitor for Declaration edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitForStatementSyntax_Declaration(const statement::ForStatementSyntax& begin, const structure::VariableDeclarationSyntax& end);

      /**
      * \brief Edge  visitor for Incrementors edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitForStatementSyntax_Incrementors(const statement::ForStatementSyntax& begin, const expression::ExpressionSyntax& end);

      /**
      * \brief Edge  visitor for Initializers edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitForStatementSyntax_Initializers(const statement::ForStatementSyntax& begin, const expression::ExpressionSyntax& end);

      /**
      * \brief Edge  visitor for Statement edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitForStatementSyntax_Statement(const statement::ForStatementSyntax& begin, const statement::StatementSyntax& end);

      /**
      * \brief Edge  visitor for Expression edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitGotoStatementSyntax_Expression(const statement::GotoStatementSyntax& begin, const expression::ExpressionSyntax& end);

      /**
      * \brief Edge  visitor for Condition edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitIfStatementSyntax_Condition(const statement::IfStatementSyntax& begin, const expression::ExpressionSyntax& end);

      /**
      * \brief Edge  visitor for Else edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitIfStatementSyntax_Else(const statement::IfStatementSyntax& begin, const structure::ElseClauseSyntax& end);

      /**
      * \brief Edge  visitor for Statement edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitIfStatementSyntax_Statement(const statement::IfStatementSyntax& begin, const statement::StatementSyntax& end);

      /**
      * \brief Edge  visitor for Statement edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitLabeledStatementSyntax_Statement(const statement::LabeledStatementSyntax& begin, const statement::StatementSyntax& end);

      /**
      * \brief Edge  visitor for Declaration edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitLocalDeclarationStatementSyntax_Declaration(const statement::LocalDeclarationStatementSyntax& begin, const structure::VariableDeclarationSyntax& end);

      /**
      * \brief Edge  visitor for Expression edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitLockStatementSyntax_Expression(const statement::LockStatementSyntax& begin, const expression::ExpressionSyntax& end);

      /**
      * \brief Edge  visitor for Statement edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitLockStatementSyntax_Statement(const statement::LockStatementSyntax& begin, const statement::StatementSyntax& end);

      /**
      * \brief Edge  visitor for Expression edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitReturnStatementSyntax_Expression(const statement::ReturnStatementSyntax& begin, const expression::ExpressionSyntax& end);

      /**
      * \brief Edge  visitor for Expression edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitSwitchStatementSyntax_Expression(const statement::SwitchStatementSyntax& begin, const expression::ExpressionSyntax& end);

      /**
      * \brief Edge  visitor for Sections edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitSwitchStatementSyntax_Sections(const statement::SwitchStatementSyntax& begin, const structure::SwitchSectionSyntax& end);

      /**
      * \brief Edge  visitor for Expression edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitThrowStatementSyntax_Expression(const statement::ThrowStatementSyntax& begin, const expression::ExpressionSyntax& end);

      /**
      * \brief Edge  visitor for Block edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitTryStatementSyntax_Block(const statement::TryStatementSyntax& begin, const statement::BlockSyntax& end);

      /**
      * \brief Edge  visitor for Catches edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitTryStatementSyntax_Catches(const statement::TryStatementSyntax& begin, const structure::CatchClauseSyntax& end);

      /**
      * \brief Edge  visitor for Finally edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitTryStatementSyntax_Finally(const statement::TryStatementSyntax& begin, const structure::FinallyClauseSyntax& end);

      /**
      * \brief Edge  visitor for Block edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitUnsafeStatementSyntax_Block(const statement::UnsafeStatementSyntax& begin, const statement::BlockSyntax& end);

      /**
      * \brief Edge  visitor for Declaration edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitUsingStatementSyntax_Declaration(const statement::UsingStatementSyntax& begin, const structure::VariableDeclarationSyntax& end);

      /**
      * \brief Edge  visitor for Expression edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitUsingStatementSyntax_Expression(const statement::UsingStatementSyntax& begin, const expression::ExpressionSyntax& end);

      /**
      * \brief Edge  visitor for Statement edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitUsingStatementSyntax_Statement(const statement::UsingStatementSyntax& begin, const statement::StatementSyntax& end);

      /**
      * \brief Edge  visitor for Condition edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitWhileStatementSyntax_Condition(const statement::WhileStatementSyntax& begin, const expression::ExpressionSyntax& end);

      /**
      * \brief Edge  visitor for Statement edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitWhileStatementSyntax_Statement(const statement::WhileStatementSyntax& begin, const statement::StatementSyntax& end);

      /**
      * \brief Edge  visitor for Expression edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitYieldStatementSyntax_Expression(const statement::YieldStatementSyntax& begin, const expression::ExpressionSyntax& end);

      /**
      * \brief Edge  visitor for AttributeLists edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitAccessorDeclarationSyntax_AttributeLists(const structure::AccessorDeclarationSyntax& begin, const structure::AttributeListSyntax& end);

      /**
      * \brief Edge  visitor for Body edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitAccessorDeclarationSyntax_Body(const structure::AccessorDeclarationSyntax& begin, const statement::BlockSyntax& end);

      /**
      * \brief Edge  visitor for Accessors edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitAccessorListSyntax_Accessors(const structure::AccessorListSyntax& begin, const structure::AccessorDeclarationSyntax& end);

      /**
      * \brief Edge  visitor for Expression edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitAnonymousObjectMemberDeclaratorSyntax_Expression(const structure::AnonymousObjectMemberDeclaratorSyntax& begin, const expression::ExpressionSyntax& end);

      /**
      * \brief Edge  visitor for NameEquals edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitAnonymousObjectMemberDeclaratorSyntax_NameEquals(const structure::AnonymousObjectMemberDeclaratorSyntax& begin, const structure::NameEqualsSyntax& end);

      /**
      * \brief Edge  visitor for Expression edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitArgumentSyntax_Expression(const structure::ArgumentSyntax& begin, const expression::ExpressionSyntax& end);

      /**
      * \brief Edge  visitor for NameColon edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitArgumentSyntax_NameColon(const structure::ArgumentSyntax& begin, const structure::NameColonSyntax& end);

      /**
      * \brief Edge  visitor for Sizes edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitArrayRankSpecifierSyntax_Sizes(const structure::ArrayRankSpecifierSyntax& begin, const expression::ExpressionSyntax& end);

      /**
      * \brief Edge  visitor for Expression edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitArrowExpressionClauseSyntax_Expression(const structure::ArrowExpressionClauseSyntax& begin, const expression::ExpressionSyntax& end);

      /**
      * \brief Edge  visitor for Arguments edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitAttributeArgumentListSyntax_Arguments(const structure::AttributeArgumentListSyntax& begin, const structure::AttributeArgumentSyntax& end);

      /**
      * \brief Edge  visitor for Expression edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitAttributeArgumentSyntax_Expression(const structure::AttributeArgumentSyntax& begin, const expression::ExpressionSyntax& end);

      /**
      * \brief Edge  visitor for NameColon edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitAttributeArgumentSyntax_NameColon(const structure::AttributeArgumentSyntax& begin, const structure::NameColonSyntax& end);

      /**
      * \brief Edge  visitor for NameEquals edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitAttributeArgumentSyntax_NameEquals(const structure::AttributeArgumentSyntax& begin, const structure::NameEqualsSyntax& end);

      /**
      * \brief Edge  visitor for Attributes edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitAttributeListSyntax_Attributes(const structure::AttributeListSyntax& begin, const structure::AttributeSyntax& end);

      /**
      * \brief Edge  visitor for Target edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitAttributeListSyntax_Target(const structure::AttributeListSyntax& begin, const structure::AttributeTargetSpecifierSyntax& end);

      /**
      * \brief Edge  visitor for ArgumentList edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitAttributeSyntax_ArgumentList(const structure::AttributeSyntax& begin, const structure::AttributeArgumentListSyntax& end);

      /**
      * \brief Edge  visitor for Name edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitAttributeSyntax_Name(const structure::AttributeSyntax& begin, const expression::NameSyntax& end);

      /**
      * \brief Edge  visitor for Arguments edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitBaseArgumentListSyntax_Arguments(const structure::BaseArgumentListSyntax& begin, const structure::ArgumentSyntax& end);

      /**
      * \brief Edge  visitor for Parameters edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitBaseCrefParameterListSyntax_Parameters(const structure::BaseCrefParameterListSyntax& begin, const structure::CrefParameterSyntax& end);

      /**
      * \brief Edge  visitor for AttributeLists edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitBaseFieldDeclarationSyntax_AttributeLists(const structure::BaseFieldDeclarationSyntax& begin, const structure::AttributeListSyntax& end);

      /**
      * \brief Edge  visitor for Declaration edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitBaseFieldDeclarationSyntax_Declaration(const structure::BaseFieldDeclarationSyntax& begin, const structure::VariableDeclarationSyntax& end);

      /**
      * \brief Edge  visitor for Types edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitBaseListSyntax_Types(const structure::BaseListSyntax& begin, const structure::BaseTypeSyntax& end);

      /**
      * \brief Edge visitor for AccessedEnumMembers edge which.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitBaseMethodDeclarationSyntax_AccessedEnumMembers(const structure::BaseMethodDeclarationSyntax& begin, const structure::EnumMemberDeclarationSyntax& end);

      /**
      * \brief Edge  visitor for AttributeLists edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitBaseMethodDeclarationSyntax_AttributeLists(const structure::BaseMethodDeclarationSyntax& begin, const structure::AttributeListSyntax& end);

      /**
      * \brief Edge  visitor for Body edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitBaseMethodDeclarationSyntax_Body(const structure::BaseMethodDeclarationSyntax& begin, const statement::BlockSyntax& end);

      /**
      * \brief Edge  visitor for ParameterList edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitBaseMethodDeclarationSyntax_ParameterList(const structure::BaseMethodDeclarationSyntax& begin, const structure::ParameterListSyntax& end);

      /**
      * \brief Edge  visitor for Parameters edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitBaseParameterListSyntax_Parameters(const structure::BaseParameterListSyntax& begin, const structure::ParameterSyntax& end);

      /**
      * \brief Edge  visitor for AccessorList edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitBasePropertyDeclarationSyntax_AccessorList(const structure::BasePropertyDeclarationSyntax& begin, const structure::AccessorListSyntax& end);

      /**
      * \brief Edge  visitor for AttributeLists edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitBasePropertyDeclarationSyntax_AttributeLists(const structure::BasePropertyDeclarationSyntax& begin, const structure::AttributeListSyntax& end);

      /**
      * \brief Edge  visitor for ExplicitInterfaceSpecifier edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitBasePropertyDeclarationSyntax_ExplicitInterfaceSpecifier(const structure::BasePropertyDeclarationSyntax& begin, const structure::ExplicitInterfaceSpecifierSyntax& end);

      /**
      * \brief Edge  visitor for Type edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitBasePropertyDeclarationSyntax_Type(const structure::BasePropertyDeclarationSyntax& begin, const expression::TypeSyntax& end);

      /**
      * \brief Edge  visitor for AttributeLists edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitBaseTypeDeclarationSyntax_AttributeLists(const structure::BaseTypeDeclarationSyntax& begin, const structure::AttributeListSyntax& end);

      /**
      * \brief Edge  visitor for BaseList edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitBaseTypeDeclarationSyntax_BaseList(const structure::BaseTypeDeclarationSyntax& begin, const structure::BaseListSyntax& end);

      /**
      * \brief Edge  visitor for Type edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitBaseTypeSyntax_Type(const structure::BaseTypeSyntax& begin, const expression::TypeSyntax& end);

      /**
      * \brief Edge  visitor for Value edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitCaseSwitchLabelSyntax_Value(const structure::CaseSwitchLabelSyntax& begin, const expression::ExpressionSyntax& end);

      /**
      * \brief Edge  visitor for Block edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitCatchClauseSyntax_Block(const structure::CatchClauseSyntax& begin, const statement::BlockSyntax& end);

      /**
      * \brief Edge  visitor for Declaration edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitCatchClauseSyntax_Declaration(const structure::CatchClauseSyntax& begin, const structure::CatchDeclarationSyntax& end);

      /**
      * \brief Edge  visitor for Filter edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitCatchClauseSyntax_Filter(const structure::CatchClauseSyntax& begin, const structure::CatchFilterClauseSyntax& end);

      /**
      * \brief Edge  visitor for Type edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitCatchDeclarationSyntax_Type(const structure::CatchDeclarationSyntax& begin, const expression::TypeSyntax& end);

      /**
      * \brief Edge  visitor for FilterExpression edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitCatchFilterClauseSyntax_FilterExpression(const structure::CatchFilterClauseSyntax& begin, const expression::ExpressionSyntax& end);

      /**
      * \brief Edge  visitor for AttributeLists edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitCompilationUnitSyntax_AttributeLists(const structure::CompilationUnitSyntax& begin, const structure::AttributeListSyntax& end);

      /**
      * \brief Edge  visitor for Externs edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitCompilationUnitSyntax_Externs(const structure::CompilationUnitSyntax& begin, const structure::ExternAliasDirectiveSyntax& end);

      /**
      * \brief Edge  visitor for Members edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitCompilationUnitSyntax_Members(const structure::CompilationUnitSyntax& begin, const structure::MemberDeclarationSyntax& end);

      /**
      * \brief Edge  visitor for Usings edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitCompilationUnitSyntax_Usings(const structure::CompilationUnitSyntax& begin, const structure::UsingDirectiveSyntax& end);

      /**
      * \brief Edge  visitor for Initializer edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitConstructorDeclarationSyntax_Initializer(const structure::ConstructorDeclarationSyntax& begin, const structure::ConstructorInitializerSyntax& end);

      /**
      * \brief Edge  visitor for ArgumentList edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitConstructorInitializerSyntax_ArgumentList(const structure::ConstructorInitializerSyntax& begin, const structure::ArgumentListSyntax& end);

      /**
      * \brief Edge visitor for ConstructorCall edge which.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitConstructorInitializerSyntax_ConstructorCall(const structure::ConstructorInitializerSyntax& begin, const structure::ConstructorDeclarationSyntax& end);

      /**
      * \brief Edge  visitor for ExpressionBody edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitConversionOperatorDeclarationSyntax_ExpressionBody(const structure::ConversionOperatorDeclarationSyntax& begin, const structure::ArrowExpressionClauseSyntax& end);

      /**
      * \brief Edge  visitor for Type edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitConversionOperatorDeclarationSyntax_Type(const structure::ConversionOperatorDeclarationSyntax& begin, const expression::TypeSyntax& end);

      /**
      * \brief Edge  visitor for Parameters edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitConversionOperatorMemberCrefSyntax_Parameters(const structure::ConversionOperatorMemberCrefSyntax& begin, const structure::CrefParameterListSyntax& end);

      /**
      * \brief Edge  visitor for Type edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitConversionOperatorMemberCrefSyntax_Type(const structure::ConversionOperatorMemberCrefSyntax& begin, const expression::TypeSyntax& end);

      /**
      * \brief Edge  visitor for Type edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitCrefParameterSyntax_Type(const structure::CrefParameterSyntax& begin, const expression::TypeSyntax& end);

      /**
      * \brief Edge  visitor for AttributeLists edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitDelegateDeclarationSyntax_AttributeLists(const structure::DelegateDeclarationSyntax& begin, const structure::AttributeListSyntax& end);

      /**
      * \brief Edge  visitor for ConstraintClauses edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitDelegateDeclarationSyntax_ConstraintClauses(const structure::DelegateDeclarationSyntax& begin, const structure::TypeParameterConstraintClauseSyntax& end);

      /**
      * \brief Edge  visitor for ParameterList edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitDelegateDeclarationSyntax_ParameterList(const structure::DelegateDeclarationSyntax& begin, const structure::ParameterListSyntax& end);

      /**
      * \brief Edge  visitor for ReturnType edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitDelegateDeclarationSyntax_ReturnType(const structure::DelegateDeclarationSyntax& begin, const expression::TypeSyntax& end);

      /**
      * \brief Edge  visitor for Statement edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitElseClauseSyntax_Statement(const structure::ElseClauseSyntax& begin, const statement::StatementSyntax& end);

      /**
      * \brief Edge  visitor for Members edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEnumDeclarationSyntax_Members(const structure::EnumDeclarationSyntax& begin, const structure::EnumMemberDeclarationSyntax& end);

      /**
      * \brief Edge  visitor for AttributeLists edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEnumMemberDeclarationSyntax_AttributeLists(const structure::EnumMemberDeclarationSyntax& begin, const structure::AttributeListSyntax& end);

      /**
      * \brief Edge  visitor for EqualsValue edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEnumMemberDeclarationSyntax_EqualsValue(const structure::EnumMemberDeclarationSyntax& begin, const structure::EqualsValueClauseSyntax& end);

      /**
      * \brief Edge  visitor for Value edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitEqualsValueClauseSyntax_Value(const structure::EqualsValueClauseSyntax& begin, const expression::ExpressionSyntax& end);

      /**
      * \brief Edge  visitor for Name edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitExplicitInterfaceSpecifierSyntax_Name(const structure::ExplicitInterfaceSpecifierSyntax& begin, const expression::NameSyntax& end);

      /**
      * \brief Edge  visitor for Block edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitFinallyClauseSyntax_Block(const structure::FinallyClauseSyntax& begin, const statement::BlockSyntax& end);

      /**
      * \brief Edge  visitor for Expression edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitFromClauseSyntax_Expression(const structure::FromClauseSyntax& begin, const expression::ExpressionSyntax& end);

      /**
      * \brief Edge  visitor for Type edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitFromClauseSyntax_Type(const structure::FromClauseSyntax& begin, const expression::TypeSyntax& end);

      /**
      * \brief Edge  visitor for Statement edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitGlobalStatementSyntax_Statement(const structure::GlobalStatementSyntax& begin, const statement::StatementSyntax& end);

      /**
      * \brief Edge  visitor for ByExpression edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitGroupClauseSyntax_ByExpression(const structure::GroupClauseSyntax& begin, const expression::ExpressionSyntax& end);

      /**
      * \brief Edge  visitor for GroupExpression edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitGroupClauseSyntax_GroupExpression(const structure::GroupClauseSyntax& begin, const expression::ExpressionSyntax& end);

      /**
      * \brief Edge  visitor for AttributeLists edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitIncompleteMemberSyntax_AttributeLists(const structure::IncompleteMemberSyntax& begin, const structure::AttributeListSyntax& end);

      /**
      * \brief Edge  visitor for Type edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitIncompleteMemberSyntax_Type(const structure::IncompleteMemberSyntax& begin, const expression::TypeSyntax& end);

      /**
      * \brief Edge  visitor for ExpressionBody edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitIndexerDeclarationSyntax_ExpressionBody(const structure::IndexerDeclarationSyntax& begin, const structure::ArrowExpressionClauseSyntax& end);

      /**
      * \brief Edge  visitor for ParameterList edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitIndexerDeclarationSyntax_ParameterList(const structure::IndexerDeclarationSyntax& begin, const structure::BracketedParameterListSyntax& end);

      /**
      * \brief Edge  visitor for Parameters edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitIndexerMemberCrefSyntax_Parameters(const structure::IndexerMemberCrefSyntax& begin, const structure::CrefBracketedParameterListSyntax& end);

      /**
      * \brief Edge  visitor for Value edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitInterpolationAlignmentClauseSyntax_Value(const structure::InterpolationAlignmentClauseSyntax& begin, const expression::ExpressionSyntax& end);

      /**
      * \brief Edge  visitor for AlignmentClause edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitInterpolationSyntax_AlignmentClause(const structure::InterpolationSyntax& begin, const structure::InterpolationAlignmentClauseSyntax& end);

      /**
      * \brief Edge  visitor for Expression edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitInterpolationSyntax_Expression(const structure::InterpolationSyntax& begin, const expression::ExpressionSyntax& end);

      /**
      * \brief Edge  visitor for FormatClause edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitInterpolationSyntax_FormatClause(const structure::InterpolationSyntax& begin, const structure::InterpolationFormatClauseSyntax& end);

      /**
      * \brief Edge  visitor for InExpression edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitJoinClauseSyntax_InExpression(const structure::JoinClauseSyntax& begin, const expression::ExpressionSyntax& end);

      /**
      * \brief Edge  visitor for Into edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitJoinClauseSyntax_Into(const structure::JoinClauseSyntax& begin, const structure::JoinIntoClauseSyntax& end);

      /**
      * \brief Edge  visitor for LeftExpression edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitJoinClauseSyntax_LeftExpression(const structure::JoinClauseSyntax& begin, const expression::ExpressionSyntax& end);

      /**
      * \brief Edge  visitor for RightExpression edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitJoinClauseSyntax_RightExpression(const structure::JoinClauseSyntax& begin, const expression::ExpressionSyntax& end);

      /**
      * \brief Edge  visitor for Type edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitJoinClauseSyntax_Type(const structure::JoinClauseSyntax& begin, const expression::TypeSyntax& end);

      /**
      * \brief Edge  visitor for Expression edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitLetClauseSyntax_Expression(const structure::LetClauseSyntax& begin, const expression::ExpressionSyntax& end);

      /**
      * \brief Edge  visitor for ConstraintClauses edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitMethodDeclarationSyntax_ConstraintClauses(const structure::MethodDeclarationSyntax& begin, const structure::TypeParameterConstraintClauseSyntax& end);

      /**
      * \brief Edge  visitor for ExplicitInterfaceSpecifier edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitMethodDeclarationSyntax_ExplicitInterfaceSpecifier(const structure::MethodDeclarationSyntax& begin, const structure::ExplicitInterfaceSpecifierSyntax& end);

      /**
      * \brief Edge  visitor for ExpressionBody edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitMethodDeclarationSyntax_ExpressionBody(const structure::MethodDeclarationSyntax& begin, const structure::ArrowExpressionClauseSyntax& end);

      /**
      * \brief Edge  visitor for ReturnType edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitMethodDeclarationSyntax_ReturnType(const structure::MethodDeclarationSyntax& begin, const expression::TypeSyntax& end);

      /**
      * \brief Edge  visitor for Name edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitNameColonSyntax_Name(const structure::NameColonSyntax& begin, const expression::IdentifierNameSyntax& end);

      /**
      * \brief Edge  visitor for Name edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitNameEqualsSyntax_Name(const structure::NameEqualsSyntax& begin, const expression::IdentifierNameSyntax& end);

      /**
      * \brief Edge  visitor for Name edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitNameMemberCrefSyntax_Name(const structure::NameMemberCrefSyntax& begin, const expression::TypeSyntax& end);

      /**
      * \brief Edge  visitor for Parameters edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitNameMemberCrefSyntax_Parameters(const structure::NameMemberCrefSyntax& begin, const structure::CrefParameterListSyntax& end);

      /**
      * \brief Edge  visitor for Externs edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitNamespaceDeclarationSyntax_Externs(const structure::NamespaceDeclarationSyntax& begin, const structure::ExternAliasDirectiveSyntax& end);

      /**
      * \brief Edge  visitor for Members edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitNamespaceDeclarationSyntax_Members(const structure::NamespaceDeclarationSyntax& begin, const structure::MemberDeclarationSyntax& end);

      /**
      * \brief Edge  visitor for Name edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitNamespaceDeclarationSyntax_Name(const structure::NamespaceDeclarationSyntax& begin, const expression::NameSyntax& end);

      /**
      * \brief Edge  visitor for Usings edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitNamespaceDeclarationSyntax_Usings(const structure::NamespaceDeclarationSyntax& begin, const structure::UsingDirectiveSyntax& end);

      /**
      * \brief Edge  visitor for ExpressionBody edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitOperatorDeclarationSyntax_ExpressionBody(const structure::OperatorDeclarationSyntax& begin, const structure::ArrowExpressionClauseSyntax& end);

      /**
      * \brief Edge  visitor for ReturnType edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitOperatorDeclarationSyntax_ReturnType(const structure::OperatorDeclarationSyntax& begin, const expression::TypeSyntax& end);

      /**
      * \brief Edge  visitor for Parameters edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitOperatorMemberCrefSyntax_Parameters(const structure::OperatorMemberCrefSyntax& begin, const structure::CrefParameterListSyntax& end);

      /**
      * \brief Edge  visitor for Orderings edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitOrderByClauseSyntax_Orderings(const structure::OrderByClauseSyntax& begin, const structure::OrderingSyntax& end);

      /**
      * \brief Edge  visitor for Expression edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitOrderingSyntax_Expression(const structure::OrderingSyntax& begin, const expression::ExpressionSyntax& end);

      /**
      * \brief Edge  visitor for AttributeLists edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitParameterSyntax_AttributeLists(const structure::ParameterSyntax& begin, const structure::AttributeListSyntax& end);

      /**
      * \brief Edge  visitor for Default edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitParameterSyntax_Default(const structure::ParameterSyntax& begin, const structure::EqualsValueClauseSyntax& end);

      /**
      * \brief Edge  visitor for Type edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitParameterSyntax_Type(const structure::ParameterSyntax& begin, const expression::TypeSyntax& end);

      /**
      * \brief Edge  visitor for ExpressionBody edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitPropertyDeclarationSyntax_ExpressionBody(const structure::PropertyDeclarationSyntax& begin, const structure::ArrowExpressionClauseSyntax& end);

      /**
      * \brief Edge  visitor for Initializer edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitPropertyDeclarationSyntax_Initializer(const structure::PropertyDeclarationSyntax& begin, const structure::EqualsValueClauseSyntax& end);

      /**
      * \brief Edge  visitor for Container edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitQualifiedCrefSyntax_Container(const structure::QualifiedCrefSyntax& begin, const expression::TypeSyntax& end);

      /**
      * \brief Edge  visitor for Member edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitQualifiedCrefSyntax_Member(const structure::QualifiedCrefSyntax& begin, const structure::MemberCrefSyntax& end);

      /**
      * \brief Edge  visitor for Clauses edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitQueryBodySyntax_Clauses(const structure::QueryBodySyntax& begin, const structure::QueryClauseSyntax& end);

      /**
      * \brief Edge  visitor for Continuation edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitQueryBodySyntax_Continuation(const structure::QueryBodySyntax& begin, const structure::QueryContinuationSyntax& end);

      /**
      * \brief Edge  visitor for SelectOrGroup edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitQueryBodySyntax_SelectOrGroup(const structure::QueryBodySyntax& begin, const structure::SelectOrGroupClauseSyntax& end);

      /**
      * \brief Edge  visitor for Body edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitQueryContinuationSyntax_Body(const structure::QueryContinuationSyntax& begin, const structure::QueryBodySyntax& end);

      /**
      * \brief Edge  visitor for Expression edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitSelectClauseSyntax_Expression(const structure::SelectClauseSyntax& begin, const expression::ExpressionSyntax& end);

      /**
      * \brief Edge  visitor for Labels edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitSwitchSectionSyntax_Labels(const structure::SwitchSectionSyntax& begin, const structure::SwitchLabelSyntax& end);

      /**
      * \brief Edge  visitor for Statements edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitSwitchSectionSyntax_Statements(const structure::SwitchSectionSyntax& begin, const statement::StatementSyntax& end);

      /**
      * \brief Edge  visitor for Arguments edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitTypeArgumentListSyntax_Arguments(const structure::TypeArgumentListSyntax& begin, const expression::TypeSyntax& end);

      /**
      * \brief Edge  visitor for Type edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitTypeConstraintSyntax_Type(const structure::TypeConstraintSyntax& begin, const expression::TypeSyntax& end);

      /**
      * \brief Edge  visitor for Type edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitTypeCrefSyntax_Type(const structure::TypeCrefSyntax& begin, const expression::TypeSyntax& end);

      /**
      * \brief Edge  visitor for ConstraintClauses edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitTypeDeclarationSyntax_ConstraintClauses(const structure::TypeDeclarationSyntax& begin, const structure::TypeParameterConstraintClauseSyntax& end);

      /**
      * \brief Edge  visitor for Members edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitTypeDeclarationSyntax_Members(const structure::TypeDeclarationSyntax& begin, const structure::MemberDeclarationSyntax& end);

      /**
      * \brief Edge  visitor for TypeParameterList edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitTypeDeclarationSyntax_TypeParameterList(const structure::TypeDeclarationSyntax& begin, const structure::TypeParameterListSyntax& end);

      /**
      * \brief Edge  visitor for Constraints edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitTypeParameterConstraintClauseSyntax_Constraints(const structure::TypeParameterConstraintClauseSyntax& begin, const structure::TypeParameterConstraintSyntax& end);

      /**
      * \brief Edge  visitor for Name edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitTypeParameterConstraintClauseSyntax_Name(const structure::TypeParameterConstraintClauseSyntax& begin, const expression::IdentifierNameSyntax& end);

      /**
      * \brief Edge visitor for Parameters edge which.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitTypeParameterListSyntax_Parameters(const structure::TypeParameterListSyntax& begin, const structure::TypeParameterSyntax& end);

      /**
      * \brief Edge  visitor for AttributeLists edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitTypeParameterSyntax_AttributeLists(const structure::TypeParameterSyntax& begin, const structure::AttributeListSyntax& end);

      /**
      * \brief Edge  visitor for Alias edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitUsingDirectiveSyntax_Alias(const structure::UsingDirectiveSyntax& begin, const structure::NameEqualsSyntax& end);

      /**
      * \brief Edge  visitor for Name edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitUsingDirectiveSyntax_Name(const structure::UsingDirectiveSyntax& begin, const expression::NameSyntax& end);

      /**
      * \brief Edge  visitor for Type edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitVariableDeclarationSyntax_Type(const structure::VariableDeclarationSyntax& begin, const expression::TypeSyntax& end);

      /**
      * \brief Edge  visitor for Variables edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitVariableDeclarationSyntax_Variables(const structure::VariableDeclarationSyntax& begin, const structure::VariableDeclaratorSyntax& end);

      /**
      * \brief Edge  visitor for ArgumentList edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitVariableDeclaratorSyntax_ArgumentList(const structure::VariableDeclaratorSyntax& begin, const structure::BracketedArgumentListSyntax& end);

      /**
      * \brief Edge  visitor for Initializer edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitVariableDeclaratorSyntax_Initializer(const structure::VariableDeclaratorSyntax& begin, const structure::EqualsValueClauseSyntax& end);

      /**
      * \brief Edge  visitor for Condition edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitWhereClauseSyntax_Condition(const structure::WhereClauseSyntax& begin, const expression::ExpressionSyntax& end);

      /**
      * \brief Edge  visitor for Name edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitXmlAttributeSyntax_Name(const structure::XmlAttributeSyntax& begin, const structure::XmlNameSyntax& end);

      /**
      * \brief Edge  visitor for Cref edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitXmlCrefAttributeSyntax_Cref(const structure::XmlCrefAttributeSyntax& begin, const structure::CrefSyntax& end);

      /**
      * \brief Edge  visitor for Name edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitXmlElementEndTagSyntax_Name(const structure::XmlElementEndTagSyntax& begin, const structure::XmlNameSyntax& end);

      /**
      * \brief Edge  visitor for Attributes edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitXmlElementStartTagSyntax_Attributes(const structure::XmlElementStartTagSyntax& begin, const structure::XmlAttributeSyntax& end);

      /**
      * \brief Edge  visitor for Name edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitXmlElementStartTagSyntax_Name(const structure::XmlElementStartTagSyntax& begin, const structure::XmlNameSyntax& end);

      /**
      * \brief Edge  visitor for Content edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitXmlElementSyntax_Content(const structure::XmlElementSyntax& begin, const structure::XmlNodeSyntax& end);

      /**
      * \brief Edge  visitor for EndTag edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitXmlElementSyntax_EndTag(const structure::XmlElementSyntax& begin, const structure::XmlElementEndTagSyntax& end);

      /**
      * \brief Edge  visitor for StartTag edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitXmlElementSyntax_StartTag(const structure::XmlElementSyntax& begin, const structure::XmlElementStartTagSyntax& end);

      /**
      * \brief Edge  visitor for Attributes edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitXmlEmptyElementSyntax_Attributes(const structure::XmlEmptyElementSyntax& begin, const structure::XmlAttributeSyntax& end);

      /**
      * \brief Edge  visitor for Name edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitXmlEmptyElementSyntax_Name(const structure::XmlEmptyElementSyntax& begin, const structure::XmlNameSyntax& end);

      /**
      * \brief Edge  visitor for Identifier edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitXmlNameAttributeSyntax_Identifier(const structure::XmlNameAttributeSyntax& begin, const expression::IdentifierNameSyntax& end);

      /**
      * \brief Edge  visitor for Prefix edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitXmlNameSyntax_Prefix(const structure::XmlNameSyntax& begin, const structure::XmlPrefixSyntax& end);

      /**
      * \brief Edge  visitor for Name edge which is called when the subtree of this edge is started.
      * \param begin [in] The reference of the node the edge starts from.
      * \param end   [in] The reference of the node the edge points to.
      */
      virtual void visitXmlProcessingInstructionSyntax_Name(const structure::XmlProcessingInstructionSyntax& begin, const structure::XmlNameSyntax& end);

    protected:

      /**
      * \internal
      * \brief Converts the attributes of the base::Base node.
      */
      void addAttributeToContent(const base::Base& node, std::string& content, bool callVirtualBase);

      /**
      * \internal
      * \brief Converts the attributes of the base::Positioned node.
      */
      void addAttributeToContent(const base::Positioned& node, std::string& content, bool callVirtualBase);

      /**
      * \internal
      * \brief Converts the attributes of the expression::AliasQualifiedNameSyntax node.
      */
      void addAttributeToContent(const expression::AliasQualifiedNameSyntax& node, std::string& content, bool callVirtualBase);

      /**
      * \internal
      * \brief Converts the attributes of the expression::AnonymousFunctionExpressionSyntax node.
      */
      void addAttributeToContent(const expression::AnonymousFunctionExpressionSyntax& node, std::string& content, bool callVirtualBase);

      /**
      * \internal
      * \brief Converts the attributes of the expression::AnonymousMethodExpressionSyntax node.
      */
      void addAttributeToContent(const expression::AnonymousMethodExpressionSyntax& node, std::string& content, bool callVirtualBase);

      /**
      * \internal
      * \brief Converts the attributes of the expression::AnonymousObjectCreationExpressionSyntax node.
      */
      void addAttributeToContent(const expression::AnonymousObjectCreationExpressionSyntax& node, std::string& content, bool callVirtualBase);

      /**
      * \internal
      * \brief Converts the attributes of the expression::ArrayCreationExpressionSyntax node.
      */
      void addAttributeToContent(const expression::ArrayCreationExpressionSyntax& node, std::string& content, bool callVirtualBase);

      /**
      * \internal
      * \brief Converts the attributes of the expression::ArrayTypeSyntax node.
      */
      void addAttributeToContent(const expression::ArrayTypeSyntax& node, std::string& content, bool callVirtualBase);

      /**
      * \internal
      * \brief Converts the attributes of the expression::AssignmentExpressionSyntax node.
      */
      void addAttributeToContent(const expression::AssignmentExpressionSyntax& node, std::string& content, bool callVirtualBase);

      /**
      * \internal
      * \brief Converts the attributes of the expression::AwaitExpressionSyntax node.
      */
      void addAttributeToContent(const expression::AwaitExpressionSyntax& node, std::string& content, bool callVirtualBase);

      /**
      * \internal
      * \brief Converts the attributes of the expression::BaseExpressionSyntax node.
      */
      void addAttributeToContent(const expression::BaseExpressionSyntax& node, std::string& content, bool callVirtualBase);

      /**
      * \internal
      * \brief Converts the attributes of the expression::BinaryExpressionSyntax node.
      */
      void addAttributeToContent(const expression::BinaryExpressionSyntax& node, std::string& content, bool callVirtualBase);

      /**
      * \internal
      * \brief Converts the attributes of the expression::CastExpressionSyntax node.
      */
      void addAttributeToContent(const expression::CastExpressionSyntax& node, std::string& content, bool callVirtualBase);

      /**
      * \internal
      * \brief Converts the attributes of the expression::CheckedExpressionSyntax node.
      */
      void addAttributeToContent(const expression::CheckedExpressionSyntax& node, std::string& content, bool callVirtualBase);

      /**
      * \internal
      * \brief Converts the attributes of the expression::ConditionalAccessExpressionSyntax node.
      */
      void addAttributeToContent(const expression::ConditionalAccessExpressionSyntax& node, std::string& content, bool callVirtualBase);

      /**
      * \internal
      * \brief Converts the attributes of the expression::ConditionalExpressionSyntax node.
      */
      void addAttributeToContent(const expression::ConditionalExpressionSyntax& node, std::string& content, bool callVirtualBase);

      /**
      * \internal
      * \brief Converts the attributes of the expression::DefaultExpressionSyntax node.
      */
      void addAttributeToContent(const expression::DefaultExpressionSyntax& node, std::string& content, bool callVirtualBase);

      /**
      * \internal
      * \brief Converts the attributes of the expression::ElementAccessExpressionSyntax node.
      */
      void addAttributeToContent(const expression::ElementAccessExpressionSyntax& node, std::string& content, bool callVirtualBase);

      /**
      * \internal
      * \brief Converts the attributes of the expression::ElementBindingExpressionSyntax node.
      */
      void addAttributeToContent(const expression::ElementBindingExpressionSyntax& node, std::string& content, bool callVirtualBase);

      /**
      * \internal
      * \brief Converts the attributes of the expression::ExpressionSyntax node.
      */
      void addAttributeToContent(const expression::ExpressionSyntax& node, std::string& content, bool callVirtualBase);

      /**
      * \internal
      * \brief Converts the attributes of the expression::GenericNameSyntax node.
      */
      void addAttributeToContent(const expression::GenericNameSyntax& node, std::string& content, bool callVirtualBase);

      /**
      * \internal
      * \brief Converts the attributes of the expression::IdentifierNameSyntax node.
      */
      void addAttributeToContent(const expression::IdentifierNameSyntax& node, std::string& content, bool callVirtualBase);

      /**
      * \internal
      * \brief Converts the attributes of the expression::ImplicitArrayCreationExpressionSyntax node.
      */
      void addAttributeToContent(const expression::ImplicitArrayCreationExpressionSyntax& node, std::string& content, bool callVirtualBase);

      /**
      * \internal
      * \brief Converts the attributes of the expression::ImplicitElementAccessSyntax node.
      */
      void addAttributeToContent(const expression::ImplicitElementAccessSyntax& node, std::string& content, bool callVirtualBase);

      /**
      * \internal
      * \brief Converts the attributes of the expression::InitializerExpressionSyntax node.
      */
      void addAttributeToContent(const expression::InitializerExpressionSyntax& node, std::string& content, bool callVirtualBase);

      /**
      * \internal
      * \brief Converts the attributes of the expression::InstanceExpressionSyntax node.
      */
      void addAttributeToContent(const expression::InstanceExpressionSyntax& node, std::string& content, bool callVirtualBase);

      /**
      * \internal
      * \brief Converts the attributes of the expression::InterpolatedStringExpressionSyntax node.
      */
      void addAttributeToContent(const expression::InterpolatedStringExpressionSyntax& node, std::string& content, bool callVirtualBase);

      /**
      * \internal
      * \brief Converts the attributes of the expression::InvocationExpressionSyntax node.
      */
      void addAttributeToContent(const expression::InvocationExpressionSyntax& node, std::string& content, bool callVirtualBase);

      /**
      * \internal
      * \brief Converts the attributes of the expression::LambdaExpressionSyntax node.
      */
      void addAttributeToContent(const expression::LambdaExpressionSyntax& node, std::string& content, bool callVirtualBase);

      /**
      * \internal
      * \brief Converts the attributes of the expression::LiteralExpressionSyntax node.
      */
      void addAttributeToContent(const expression::LiteralExpressionSyntax& node, std::string& content, bool callVirtualBase);

      /**
      * \internal
      * \brief Converts the attributes of the expression::MakeRefExpressionSyntax node.
      */
      void addAttributeToContent(const expression::MakeRefExpressionSyntax& node, std::string& content, bool callVirtualBase);

      /**
      * \internal
      * \brief Converts the attributes of the expression::MemberAccessExpressionSyntax node.
      */
      void addAttributeToContent(const expression::MemberAccessExpressionSyntax& node, std::string& content, bool callVirtualBase);

      /**
      * \internal
      * \brief Converts the attributes of the expression::MemberBindingExpressionSyntax node.
      */
      void addAttributeToContent(const expression::MemberBindingExpressionSyntax& node, std::string& content, bool callVirtualBase);

      /**
      * \internal
      * \brief Converts the attributes of the expression::NameSyntax node.
      */
      void addAttributeToContent(const expression::NameSyntax& node, std::string& content, bool callVirtualBase);

      /**
      * \internal
      * \brief Converts the attributes of the expression::NullableTypeSyntax node.
      */
      void addAttributeToContent(const expression::NullableTypeSyntax& node, std::string& content, bool callVirtualBase);

      /**
      * \internal
      * \brief Converts the attributes of the expression::ObjectCreationExpressionSyntax node.
      */
      void addAttributeToContent(const expression::ObjectCreationExpressionSyntax& node, std::string& content, bool callVirtualBase);

      /**
      * \internal
      * \brief Converts the attributes of the expression::OmittedArraySizeExpressionSyntax node.
      */
      void addAttributeToContent(const expression::OmittedArraySizeExpressionSyntax& node, std::string& content, bool callVirtualBase);

      /**
      * \internal
      * \brief Converts the attributes of the expression::OmittedTypeArgumentSyntax node.
      */
      void addAttributeToContent(const expression::OmittedTypeArgumentSyntax& node, std::string& content, bool callVirtualBase);

      /**
      * \internal
      * \brief Converts the attributes of the expression::ParenthesizedExpressionSyntax node.
      */
      void addAttributeToContent(const expression::ParenthesizedExpressionSyntax& node, std::string& content, bool callVirtualBase);

      /**
      * \internal
      * \brief Converts the attributes of the expression::ParenthesizedLambdaExpressionSyntax node.
      */
      void addAttributeToContent(const expression::ParenthesizedLambdaExpressionSyntax& node, std::string& content, bool callVirtualBase);

      /**
      * \internal
      * \brief Converts the attributes of the expression::PointerTypeSyntax node.
      */
      void addAttributeToContent(const expression::PointerTypeSyntax& node, std::string& content, bool callVirtualBase);

      /**
      * \internal
      * \brief Converts the attributes of the expression::PostfixUnaryExpressionSyntax node.
      */
      void addAttributeToContent(const expression::PostfixUnaryExpressionSyntax& node, std::string& content, bool callVirtualBase);

      /**
      * \internal
      * \brief Converts the attributes of the expression::PredefinedTypeSyntax node.
      */
      void addAttributeToContent(const expression::PredefinedTypeSyntax& node, std::string& content, bool callVirtualBase);

      /**
      * \internal
      * \brief Converts the attributes of the expression::PrefixUnaryExpressionSyntax node.
      */
      void addAttributeToContent(const expression::PrefixUnaryExpressionSyntax& node, std::string& content, bool callVirtualBase);

      /**
      * \internal
      * \brief Converts the attributes of the expression::QualifiedNameSyntax node.
      */
      void addAttributeToContent(const expression::QualifiedNameSyntax& node, std::string& content, bool callVirtualBase);

      /**
      * \internal
      * \brief Converts the attributes of the expression::QueryExpressionSyntax node.
      */
      void addAttributeToContent(const expression::QueryExpressionSyntax& node, std::string& content, bool callVirtualBase);

      /**
      * \internal
      * \brief Converts the attributes of the expression::RefTypeExpressionSyntax node.
      */
      void addAttributeToContent(const expression::RefTypeExpressionSyntax& node, std::string& content, bool callVirtualBase);

      /**
      * \internal
      * \brief Converts the attributes of the expression::RefValueExpressionSyntax node.
      */
      void addAttributeToContent(const expression::RefValueExpressionSyntax& node, std::string& content, bool callVirtualBase);

      /**
      * \internal
      * \brief Converts the attributes of the expression::SimpleLambdaExpressionSyntax node.
      */
      void addAttributeToContent(const expression::SimpleLambdaExpressionSyntax& node, std::string& content, bool callVirtualBase);

      /**
      * \internal
      * \brief Converts the attributes of the expression::SimpleNameSyntax node.
      */
      void addAttributeToContent(const expression::SimpleNameSyntax& node, std::string& content, bool callVirtualBase);

      /**
      * \internal
      * \brief Converts the attributes of the expression::SizeOfExpressionSyntax node.
      */
      void addAttributeToContent(const expression::SizeOfExpressionSyntax& node, std::string& content, bool callVirtualBase);

      /**
      * \internal
      * \brief Converts the attributes of the expression::StackAllocArrayCreationExpressionSyntax node.
      */
      void addAttributeToContent(const expression::StackAllocArrayCreationExpressionSyntax& node, std::string& content, bool callVirtualBase);

      /**
      * \internal
      * \brief Converts the attributes of the expression::ThisExpressionSyntax node.
      */
      void addAttributeToContent(const expression::ThisExpressionSyntax& node, std::string& content, bool callVirtualBase);

      /**
      * \internal
      * \brief Converts the attributes of the expression::TypeOfExpressionSyntax node.
      */
      void addAttributeToContent(const expression::TypeOfExpressionSyntax& node, std::string& content, bool callVirtualBase);

      /**
      * \internal
      * \brief Converts the attributes of the expression::TypeSyntax node.
      */
      void addAttributeToContent(const expression::TypeSyntax& node, std::string& content, bool callVirtualBase);

      /**
      * \internal
      * \brief Converts the attributes of the statement::BlockSyntax node.
      */
      void addAttributeToContent(const statement::BlockSyntax& node, std::string& content, bool callVirtualBase);

      /**
      * \internal
      * \brief Converts the attributes of the statement::BreakStatementSyntax node.
      */
      void addAttributeToContent(const statement::BreakStatementSyntax& node, std::string& content, bool callVirtualBase);

      /**
      * \internal
      * \brief Converts the attributes of the statement::CheckedStatementSyntax node.
      */
      void addAttributeToContent(const statement::CheckedStatementSyntax& node, std::string& content, bool callVirtualBase);

      /**
      * \internal
      * \brief Converts the attributes of the statement::ContinueStatementSyntax node.
      */
      void addAttributeToContent(const statement::ContinueStatementSyntax& node, std::string& content, bool callVirtualBase);

      /**
      * \internal
      * \brief Converts the attributes of the statement::DoStatementSyntax node.
      */
      void addAttributeToContent(const statement::DoStatementSyntax& node, std::string& content, bool callVirtualBase);

      /**
      * \internal
      * \brief Converts the attributes of the statement::EmptyStatementSyntax node.
      */
      void addAttributeToContent(const statement::EmptyStatementSyntax& node, std::string& content, bool callVirtualBase);

      /**
      * \internal
      * \brief Converts the attributes of the statement::ExpressionStatementSyntax node.
      */
      void addAttributeToContent(const statement::ExpressionStatementSyntax& node, std::string& content, bool callVirtualBase);

      /**
      * \internal
      * \brief Converts the attributes of the statement::FixedStatementSyntax node.
      */
      void addAttributeToContent(const statement::FixedStatementSyntax& node, std::string& content, bool callVirtualBase);

      /**
      * \internal
      * \brief Converts the attributes of the statement::ForEachStatementSyntax node.
      */
      void addAttributeToContent(const statement::ForEachStatementSyntax& node, std::string& content, bool callVirtualBase);

      /**
      * \internal
      * \brief Converts the attributes of the statement::ForStatementSyntax node.
      */
      void addAttributeToContent(const statement::ForStatementSyntax& node, std::string& content, bool callVirtualBase);

      /**
      * \internal
      * \brief Converts the attributes of the statement::GotoStatementSyntax node.
      */
      void addAttributeToContent(const statement::GotoStatementSyntax& node, std::string& content, bool callVirtualBase);

      /**
      * \internal
      * \brief Converts the attributes of the statement::IfStatementSyntax node.
      */
      void addAttributeToContent(const statement::IfStatementSyntax& node, std::string& content, bool callVirtualBase);

      /**
      * \internal
      * \brief Converts the attributes of the statement::LabeledStatementSyntax node.
      */
      void addAttributeToContent(const statement::LabeledStatementSyntax& node, std::string& content, bool callVirtualBase);

      /**
      * \internal
      * \brief Converts the attributes of the statement::LocalDeclarationStatementSyntax node.
      */
      void addAttributeToContent(const statement::LocalDeclarationStatementSyntax& node, std::string& content, bool callVirtualBase);

      /**
      * \internal
      * \brief Converts the attributes of the statement::LockStatementSyntax node.
      */
      void addAttributeToContent(const statement::LockStatementSyntax& node, std::string& content, bool callVirtualBase);

      /**
      * \internal
      * \brief Converts the attributes of the statement::ReturnStatementSyntax node.
      */
      void addAttributeToContent(const statement::ReturnStatementSyntax& node, std::string& content, bool callVirtualBase);

      /**
      * \internal
      * \brief Converts the attributes of the statement::StatementSyntax node.
      */
      void addAttributeToContent(const statement::StatementSyntax& node, std::string& content, bool callVirtualBase);

      /**
      * \internal
      * \brief Converts the attributes of the statement::SwitchStatementSyntax node.
      */
      void addAttributeToContent(const statement::SwitchStatementSyntax& node, std::string& content, bool callVirtualBase);

      /**
      * \internal
      * \brief Converts the attributes of the statement::ThrowStatementSyntax node.
      */
      void addAttributeToContent(const statement::ThrowStatementSyntax& node, std::string& content, bool callVirtualBase);

      /**
      * \internal
      * \brief Converts the attributes of the statement::TryStatementSyntax node.
      */
      void addAttributeToContent(const statement::TryStatementSyntax& node, std::string& content, bool callVirtualBase);

      /**
      * \internal
      * \brief Converts the attributes of the statement::UnsafeStatementSyntax node.
      */
      void addAttributeToContent(const statement::UnsafeStatementSyntax& node, std::string& content, bool callVirtualBase);

      /**
      * \internal
      * \brief Converts the attributes of the statement::UsingStatementSyntax node.
      */
      void addAttributeToContent(const statement::UsingStatementSyntax& node, std::string& content, bool callVirtualBase);

      /**
      * \internal
      * \brief Converts the attributes of the statement::WhileStatementSyntax node.
      */
      void addAttributeToContent(const statement::WhileStatementSyntax& node, std::string& content, bool callVirtualBase);

      /**
      * \internal
      * \brief Converts the attributes of the statement::YieldStatementSyntax node.
      */
      void addAttributeToContent(const statement::YieldStatementSyntax& node, std::string& content, bool callVirtualBase);

      /**
      * \internal
      * \brief Converts the attributes of the structure::AccessorDeclarationSyntax node.
      */
      void addAttributeToContent(const structure::AccessorDeclarationSyntax& node, std::string& content, bool callVirtualBase);

      /**
      * \internal
      * \brief Converts the attributes of the structure::AccessorListSyntax node.
      */
      void addAttributeToContent(const structure::AccessorListSyntax& node, std::string& content, bool callVirtualBase);

      /**
      * \internal
      * \brief Converts the attributes of the structure::AnonymousObjectMemberDeclaratorSyntax node.
      */
      void addAttributeToContent(const structure::AnonymousObjectMemberDeclaratorSyntax& node, std::string& content, bool callVirtualBase);

      /**
      * \internal
      * \brief Converts the attributes of the structure::ArgumentListSyntax node.
      */
      void addAttributeToContent(const structure::ArgumentListSyntax& node, std::string& content, bool callVirtualBase);

      /**
      * \internal
      * \brief Converts the attributes of the structure::ArgumentSyntax node.
      */
      void addAttributeToContent(const structure::ArgumentSyntax& node, std::string& content, bool callVirtualBase);

      /**
      * \internal
      * \brief Converts the attributes of the structure::ArrayRankSpecifierSyntax node.
      */
      void addAttributeToContent(const structure::ArrayRankSpecifierSyntax& node, std::string& content, bool callVirtualBase);

      /**
      * \internal
      * \brief Converts the attributes of the structure::ArrowExpressionClauseSyntax node.
      */
      void addAttributeToContent(const structure::ArrowExpressionClauseSyntax& node, std::string& content, bool callVirtualBase);

      /**
      * \internal
      * \brief Converts the attributes of the structure::AttributeArgumentListSyntax node.
      */
      void addAttributeToContent(const structure::AttributeArgumentListSyntax& node, std::string& content, bool callVirtualBase);

      /**
      * \internal
      * \brief Converts the attributes of the structure::AttributeArgumentSyntax node.
      */
      void addAttributeToContent(const structure::AttributeArgumentSyntax& node, std::string& content, bool callVirtualBase);

      /**
      * \internal
      * \brief Converts the attributes of the structure::AttributeListSyntax node.
      */
      void addAttributeToContent(const structure::AttributeListSyntax& node, std::string& content, bool callVirtualBase);

      /**
      * \internal
      * \brief Converts the attributes of the structure::AttributeSyntax node.
      */
      void addAttributeToContent(const structure::AttributeSyntax& node, std::string& content, bool callVirtualBase);

      /**
      * \internal
      * \brief Converts the attributes of the structure::AttributeTargetSpecifierSyntax node.
      */
      void addAttributeToContent(const structure::AttributeTargetSpecifierSyntax& node, std::string& content, bool callVirtualBase);

      /**
      * \internal
      * \brief Converts the attributes of the structure::BaseArgumentListSyntax node.
      */
      void addAttributeToContent(const structure::BaseArgumentListSyntax& node, std::string& content, bool callVirtualBase);

      /**
      * \internal
      * \brief Converts the attributes of the structure::BaseCrefParameterListSyntax node.
      */
      void addAttributeToContent(const structure::BaseCrefParameterListSyntax& node, std::string& content, bool callVirtualBase);

      /**
      * \internal
      * \brief Converts the attributes of the structure::BaseFieldDeclarationSyntax node.
      */
      void addAttributeToContent(const structure::BaseFieldDeclarationSyntax& node, std::string& content, bool callVirtualBase);

      /**
      * \internal
      * \brief Converts the attributes of the structure::BaseListSyntax node.
      */
      void addAttributeToContent(const structure::BaseListSyntax& node, std::string& content, bool callVirtualBase);

      /**
      * \internal
      * \brief Converts the attributes of the structure::BaseMethodDeclarationSyntax node.
      */
      void addAttributeToContent(const structure::BaseMethodDeclarationSyntax& node, std::string& content, bool callVirtualBase);

      /**
      * \internal
      * \brief Converts the attributes of the structure::BaseParameterListSyntax node.
      */
      void addAttributeToContent(const structure::BaseParameterListSyntax& node, std::string& content, bool callVirtualBase);

      /**
      * \internal
      * \brief Converts the attributes of the structure::BasePropertyDeclarationSyntax node.
      */
      void addAttributeToContent(const structure::BasePropertyDeclarationSyntax& node, std::string& content, bool callVirtualBase);

      /**
      * \internal
      * \brief Converts the attributes of the structure::BaseTypeDeclarationSyntax node.
      */
      void addAttributeToContent(const structure::BaseTypeDeclarationSyntax& node, std::string& content, bool callVirtualBase);

      /**
      * \internal
      * \brief Converts the attributes of the structure::BaseTypeSyntax node.
      */
      void addAttributeToContent(const structure::BaseTypeSyntax& node, std::string& content, bool callVirtualBase);

      /**
      * \internal
      * \brief Converts the attributes of the structure::BracketedArgumentListSyntax node.
      */
      void addAttributeToContent(const structure::BracketedArgumentListSyntax& node, std::string& content, bool callVirtualBase);

      /**
      * \internal
      * \brief Converts the attributes of the structure::BracketedParameterListSyntax node.
      */
      void addAttributeToContent(const structure::BracketedParameterListSyntax& node, std::string& content, bool callVirtualBase);

      /**
      * \internal
      * \brief Converts the attributes of the structure::CaseSwitchLabelSyntax node.
      */
      void addAttributeToContent(const structure::CaseSwitchLabelSyntax& node, std::string& content, bool callVirtualBase);

      /**
      * \internal
      * \brief Converts the attributes of the structure::CatchClauseSyntax node.
      */
      void addAttributeToContent(const structure::CatchClauseSyntax& node, std::string& content, bool callVirtualBase);

      /**
      * \internal
      * \brief Converts the attributes of the structure::CatchDeclarationSyntax node.
      */
      void addAttributeToContent(const structure::CatchDeclarationSyntax& node, std::string& content, bool callVirtualBase);

      /**
      * \internal
      * \brief Converts the attributes of the structure::CatchFilterClauseSyntax node.
      */
      void addAttributeToContent(const structure::CatchFilterClauseSyntax& node, std::string& content, bool callVirtualBase);

      /**
      * \internal
      * \brief Converts the attributes of the structure::ClassDeclarationSyntax node.
      */
      void addAttributeToContent(const structure::ClassDeclarationSyntax& node, std::string& content, bool callVirtualBase);

      /**
      * \internal
      * \brief Converts the attributes of the structure::ClassOrStructConstraintSyntax node.
      */
      void addAttributeToContent(const structure::ClassOrStructConstraintSyntax& node, std::string& content, bool callVirtualBase);

      /**
      * \internal
      * \brief Converts the attributes of the structure::CompilationUnitSyntax node.
      */
      void addAttributeToContent(const structure::CompilationUnitSyntax& node, std::string& content, bool callVirtualBase);

      /**
      * \internal
      * \brief Converts the attributes of the structure::ConstructorConstraintSyntax node.
      */
      void addAttributeToContent(const structure::ConstructorConstraintSyntax& node, std::string& content, bool callVirtualBase);

      /**
      * \internal
      * \brief Converts the attributes of the structure::ConstructorDeclarationSyntax node.
      */
      void addAttributeToContent(const structure::ConstructorDeclarationSyntax& node, std::string& content, bool callVirtualBase);

      /**
      * \internal
      * \brief Converts the attributes of the structure::ConstructorInitializerSyntax node.
      */
      void addAttributeToContent(const structure::ConstructorInitializerSyntax& node, std::string& content, bool callVirtualBase);

      /**
      * \internal
      * \brief Converts the attributes of the structure::ConversionOperatorDeclarationSyntax node.
      */
      void addAttributeToContent(const structure::ConversionOperatorDeclarationSyntax& node, std::string& content, bool callVirtualBase);

      /**
      * \internal
      * \brief Converts the attributes of the structure::ConversionOperatorMemberCrefSyntax node.
      */
      void addAttributeToContent(const structure::ConversionOperatorMemberCrefSyntax& node, std::string& content, bool callVirtualBase);

      /**
      * \internal
      * \brief Converts the attributes of the structure::CrefBracketedParameterListSyntax node.
      */
      void addAttributeToContent(const structure::CrefBracketedParameterListSyntax& node, std::string& content, bool callVirtualBase);

      /**
      * \internal
      * \brief Converts the attributes of the structure::CrefParameterListSyntax node.
      */
      void addAttributeToContent(const structure::CrefParameterListSyntax& node, std::string& content, bool callVirtualBase);

      /**
      * \internal
      * \brief Converts the attributes of the structure::CrefParameterSyntax node.
      */
      void addAttributeToContent(const structure::CrefParameterSyntax& node, std::string& content, bool callVirtualBase);

      /**
      * \internal
      * \brief Converts the attributes of the structure::CrefSyntax node.
      */
      void addAttributeToContent(const structure::CrefSyntax& node, std::string& content, bool callVirtualBase);

      /**
      * \internal
      * \brief Converts the attributes of the structure::DefaultSwitchLabelSyntax node.
      */
      void addAttributeToContent(const structure::DefaultSwitchLabelSyntax& node, std::string& content, bool callVirtualBase);

      /**
      * \internal
      * \brief Converts the attributes of the structure::DelegateDeclarationSyntax node.
      */
      void addAttributeToContent(const structure::DelegateDeclarationSyntax& node, std::string& content, bool callVirtualBase);

      /**
      * \internal
      * \brief Converts the attributes of the structure::DestructorDeclarationSyntax node.
      */
      void addAttributeToContent(const structure::DestructorDeclarationSyntax& node, std::string& content, bool callVirtualBase);

      /**
      * \internal
      * \brief Converts the attributes of the structure::ElseClauseSyntax node.
      */
      void addAttributeToContent(const structure::ElseClauseSyntax& node, std::string& content, bool callVirtualBase);

      /**
      * \internal
      * \brief Converts the attributes of the structure::EnumDeclarationSyntax node.
      */
      void addAttributeToContent(const structure::EnumDeclarationSyntax& node, std::string& content, bool callVirtualBase);

      /**
      * \internal
      * \brief Converts the attributes of the structure::EnumMemberDeclarationSyntax node.
      */
      void addAttributeToContent(const structure::EnumMemberDeclarationSyntax& node, std::string& content, bool callVirtualBase);

      /**
      * \internal
      * \brief Converts the attributes of the structure::EqualsValueClauseSyntax node.
      */
      void addAttributeToContent(const structure::EqualsValueClauseSyntax& node, std::string& content, bool callVirtualBase);

      /**
      * \internal
      * \brief Converts the attributes of the structure::EventDeclarationSyntax node.
      */
      void addAttributeToContent(const structure::EventDeclarationSyntax& node, std::string& content, bool callVirtualBase);

      /**
      * \internal
      * \brief Converts the attributes of the structure::EventFieldDeclarationSyntax node.
      */
      void addAttributeToContent(const structure::EventFieldDeclarationSyntax& node, std::string& content, bool callVirtualBase);

      /**
      * \internal
      * \brief Converts the attributes of the structure::ExplicitInterfaceSpecifierSyntax node.
      */
      void addAttributeToContent(const structure::ExplicitInterfaceSpecifierSyntax& node, std::string& content, bool callVirtualBase);

      /**
      * \internal
      * \brief Converts the attributes of the structure::ExternAliasDirectiveSyntax node.
      */
      void addAttributeToContent(const structure::ExternAliasDirectiveSyntax& node, std::string& content, bool callVirtualBase);

      /**
      * \internal
      * \brief Converts the attributes of the structure::FieldDeclarationSyntax node.
      */
      void addAttributeToContent(const structure::FieldDeclarationSyntax& node, std::string& content, bool callVirtualBase);

      /**
      * \internal
      * \brief Converts the attributes of the structure::FinallyClauseSyntax node.
      */
      void addAttributeToContent(const structure::FinallyClauseSyntax& node, std::string& content, bool callVirtualBase);

      /**
      * \internal
      * \brief Converts the attributes of the structure::FromClauseSyntax node.
      */
      void addAttributeToContent(const structure::FromClauseSyntax& node, std::string& content, bool callVirtualBase);

      /**
      * \internal
      * \brief Converts the attributes of the structure::GlobalStatementSyntax node.
      */
      void addAttributeToContent(const structure::GlobalStatementSyntax& node, std::string& content, bool callVirtualBase);

      /**
      * \internal
      * \brief Converts the attributes of the structure::GroupClauseSyntax node.
      */
      void addAttributeToContent(const structure::GroupClauseSyntax& node, std::string& content, bool callVirtualBase);

      /**
      * \internal
      * \brief Converts the attributes of the structure::IncompleteMemberSyntax node.
      */
      void addAttributeToContent(const structure::IncompleteMemberSyntax& node, std::string& content, bool callVirtualBase);

      /**
      * \internal
      * \brief Converts the attributes of the structure::IndexerDeclarationSyntax node.
      */
      void addAttributeToContent(const structure::IndexerDeclarationSyntax& node, std::string& content, bool callVirtualBase);

      /**
      * \internal
      * \brief Converts the attributes of the structure::IndexerMemberCrefSyntax node.
      */
      void addAttributeToContent(const structure::IndexerMemberCrefSyntax& node, std::string& content, bool callVirtualBase);

      /**
      * \internal
      * \brief Converts the attributes of the structure::InterfaceDeclarationSyntax node.
      */
      void addAttributeToContent(const structure::InterfaceDeclarationSyntax& node, std::string& content, bool callVirtualBase);

      /**
      * \internal
      * \brief Converts the attributes of the structure::InterpolatedStringContentSyntax node.
      */
      void addAttributeToContent(const structure::InterpolatedStringContentSyntax& node, std::string& content, bool callVirtualBase);

      /**
      * \internal
      * \brief Converts the attributes of the structure::InterpolatedStringTextSyntax node.
      */
      void addAttributeToContent(const structure::InterpolatedStringTextSyntax& node, std::string& content, bool callVirtualBase);

      /**
      * \internal
      * \brief Converts the attributes of the structure::InterpolationAlignmentClauseSyntax node.
      */
      void addAttributeToContent(const structure::InterpolationAlignmentClauseSyntax& node, std::string& content, bool callVirtualBase);

      /**
      * \internal
      * \brief Converts the attributes of the structure::InterpolationFormatClauseSyntax node.
      */
      void addAttributeToContent(const structure::InterpolationFormatClauseSyntax& node, std::string& content, bool callVirtualBase);

      /**
      * \internal
      * \brief Converts the attributes of the structure::InterpolationSyntax node.
      */
      void addAttributeToContent(const structure::InterpolationSyntax& node, std::string& content, bool callVirtualBase);

      /**
      * \internal
      * \brief Converts the attributes of the structure::JoinClauseSyntax node.
      */
      void addAttributeToContent(const structure::JoinClauseSyntax& node, std::string& content, bool callVirtualBase);

      /**
      * \internal
      * \brief Converts the attributes of the structure::JoinIntoClauseSyntax node.
      */
      void addAttributeToContent(const structure::JoinIntoClauseSyntax& node, std::string& content, bool callVirtualBase);

      /**
      * \internal
      * \brief Converts the attributes of the structure::LetClauseSyntax node.
      */
      void addAttributeToContent(const structure::LetClauseSyntax& node, std::string& content, bool callVirtualBase);

      /**
      * \internal
      * \brief Converts the attributes of the structure::MemberCrefSyntax node.
      */
      void addAttributeToContent(const structure::MemberCrefSyntax& node, std::string& content, bool callVirtualBase);

      /**
      * \internal
      * \brief Converts the attributes of the structure::MemberDeclarationSyntax node.
      */
      void addAttributeToContent(const structure::MemberDeclarationSyntax& node, std::string& content, bool callVirtualBase);

      /**
      * \internal
      * \brief Converts the attributes of the structure::MethodDeclarationSyntax node.
      */
      void addAttributeToContent(const structure::MethodDeclarationSyntax& node, std::string& content, bool callVirtualBase);

      /**
      * \internal
      * \brief Converts the attributes of the structure::NameColonSyntax node.
      */
      void addAttributeToContent(const structure::NameColonSyntax& node, std::string& content, bool callVirtualBase);

      /**
      * \internal
      * \brief Converts the attributes of the structure::NameEqualsSyntax node.
      */
      void addAttributeToContent(const structure::NameEqualsSyntax& node, std::string& content, bool callVirtualBase);

      /**
      * \internal
      * \brief Converts the attributes of the structure::NameMemberCrefSyntax node.
      */
      void addAttributeToContent(const structure::NameMemberCrefSyntax& node, std::string& content, bool callVirtualBase);

      /**
      * \internal
      * \brief Converts the attributes of the structure::NamespaceDeclarationSyntax node.
      */
      void addAttributeToContent(const structure::NamespaceDeclarationSyntax& node, std::string& content, bool callVirtualBase);

      /**
      * \internal
      * \brief Converts the attributes of the structure::OperatorDeclarationSyntax node.
      */
      void addAttributeToContent(const structure::OperatorDeclarationSyntax& node, std::string& content, bool callVirtualBase);

      /**
      * \internal
      * \brief Converts the attributes of the structure::OperatorMemberCrefSyntax node.
      */
      void addAttributeToContent(const structure::OperatorMemberCrefSyntax& node, std::string& content, bool callVirtualBase);

      /**
      * \internal
      * \brief Converts the attributes of the structure::OrderByClauseSyntax node.
      */
      void addAttributeToContent(const structure::OrderByClauseSyntax& node, std::string& content, bool callVirtualBase);

      /**
      * \internal
      * \brief Converts the attributes of the structure::OrderingSyntax node.
      */
      void addAttributeToContent(const structure::OrderingSyntax& node, std::string& content, bool callVirtualBase);

      /**
      * \internal
      * \brief Converts the attributes of the structure::ParameterListSyntax node.
      */
      void addAttributeToContent(const structure::ParameterListSyntax& node, std::string& content, bool callVirtualBase);

      /**
      * \internal
      * \brief Converts the attributes of the structure::ParameterSyntax node.
      */
      void addAttributeToContent(const structure::ParameterSyntax& node, std::string& content, bool callVirtualBase);

      /**
      * \internal
      * \brief Converts the attributes of the structure::PropertyDeclarationSyntax node.
      */
      void addAttributeToContent(const structure::PropertyDeclarationSyntax& node, std::string& content, bool callVirtualBase);

      /**
      * \internal
      * \brief Converts the attributes of the structure::QualifiedCrefSyntax node.
      */
      void addAttributeToContent(const structure::QualifiedCrefSyntax& node, std::string& content, bool callVirtualBase);

      /**
      * \internal
      * \brief Converts the attributes of the structure::QueryBodySyntax node.
      */
      void addAttributeToContent(const structure::QueryBodySyntax& node, std::string& content, bool callVirtualBase);

      /**
      * \internal
      * \brief Converts the attributes of the structure::QueryClauseSyntax node.
      */
      void addAttributeToContent(const structure::QueryClauseSyntax& node, std::string& content, bool callVirtualBase);

      /**
      * \internal
      * \brief Converts the attributes of the structure::QueryContinuationSyntax node.
      */
      void addAttributeToContent(const structure::QueryContinuationSyntax& node, std::string& content, bool callVirtualBase);

      /**
      * \internal
      * \brief Converts the attributes of the structure::SelectClauseSyntax node.
      */
      void addAttributeToContent(const structure::SelectClauseSyntax& node, std::string& content, bool callVirtualBase);

      /**
      * \internal
      * \brief Converts the attributes of the structure::SelectOrGroupClauseSyntax node.
      */
      void addAttributeToContent(const structure::SelectOrGroupClauseSyntax& node, std::string& content, bool callVirtualBase);

      /**
      * \internal
      * \brief Converts the attributes of the structure::SimpleBaseTypeSyntax node.
      */
      void addAttributeToContent(const structure::SimpleBaseTypeSyntax& node, std::string& content, bool callVirtualBase);

      /**
      * \internal
      * \brief Converts the attributes of the structure::StructDeclarationSyntax node.
      */
      void addAttributeToContent(const structure::StructDeclarationSyntax& node, std::string& content, bool callVirtualBase);

      /**
      * \internal
      * \brief Converts the attributes of the structure::SwitchLabelSyntax node.
      */
      void addAttributeToContent(const structure::SwitchLabelSyntax& node, std::string& content, bool callVirtualBase);

      /**
      * \internal
      * \brief Converts the attributes of the structure::SwitchSectionSyntax node.
      */
      void addAttributeToContent(const structure::SwitchSectionSyntax& node, std::string& content, bool callVirtualBase);

      /**
      * \internal
      * \brief Converts the attributes of the structure::SyntaxToken node.
      */
      void addAttributeToContent(const structure::SyntaxToken& node, std::string& content, bool callVirtualBase);

      /**
      * \internal
      * \brief Converts the attributes of the structure::TypeArgumentListSyntax node.
      */
      void addAttributeToContent(const structure::TypeArgumentListSyntax& node, std::string& content, bool callVirtualBase);

      /**
      * \internal
      * \brief Converts the attributes of the structure::TypeConstraintSyntax node.
      */
      void addAttributeToContent(const structure::TypeConstraintSyntax& node, std::string& content, bool callVirtualBase);

      /**
      * \internal
      * \brief Converts the attributes of the structure::TypeCrefSyntax node.
      */
      void addAttributeToContent(const structure::TypeCrefSyntax& node, std::string& content, bool callVirtualBase);

      /**
      * \internal
      * \brief Converts the attributes of the structure::TypeDeclarationSyntax node.
      */
      void addAttributeToContent(const structure::TypeDeclarationSyntax& node, std::string& content, bool callVirtualBase);

      /**
      * \internal
      * \brief Converts the attributes of the structure::TypeParameterConstraintClauseSyntax node.
      */
      void addAttributeToContent(const structure::TypeParameterConstraintClauseSyntax& node, std::string& content, bool callVirtualBase);

      /**
      * \internal
      * \brief Converts the attributes of the structure::TypeParameterConstraintSyntax node.
      */
      void addAttributeToContent(const structure::TypeParameterConstraintSyntax& node, std::string& content, bool callVirtualBase);

      /**
      * \internal
      * \brief Converts the attributes of the structure::TypeParameterListSyntax node.
      */
      void addAttributeToContent(const structure::TypeParameterListSyntax& node, std::string& content, bool callVirtualBase);

      /**
      * \internal
      * \brief Converts the attributes of the structure::TypeParameterSyntax node.
      */
      void addAttributeToContent(const structure::TypeParameterSyntax& node, std::string& content, bool callVirtualBase);

      /**
      * \internal
      * \brief Converts the attributes of the structure::UsingDirectiveSyntax node.
      */
      void addAttributeToContent(const structure::UsingDirectiveSyntax& node, std::string& content, bool callVirtualBase);

      /**
      * \internal
      * \brief Converts the attributes of the structure::VariableDeclarationSyntax node.
      */
      void addAttributeToContent(const structure::VariableDeclarationSyntax& node, std::string& content, bool callVirtualBase);

      /**
      * \internal
      * \brief Converts the attributes of the structure::VariableDeclaratorSyntax node.
      */
      void addAttributeToContent(const structure::VariableDeclaratorSyntax& node, std::string& content, bool callVirtualBase);

      /**
      * \internal
      * \brief Converts the attributes of the structure::WhereClauseSyntax node.
      */
      void addAttributeToContent(const structure::WhereClauseSyntax& node, std::string& content, bool callVirtualBase);

      /**
      * \internal
      * \brief Converts the attributes of the structure::XmlAttributeSyntax node.
      */
      void addAttributeToContent(const structure::XmlAttributeSyntax& node, std::string& content, bool callVirtualBase);

      /**
      * \internal
      * \brief Converts the attributes of the structure::XmlCDataSectionSyntax node.
      */
      void addAttributeToContent(const structure::XmlCDataSectionSyntax& node, std::string& content, bool callVirtualBase);

      /**
      * \internal
      * \brief Converts the attributes of the structure::XmlCommentSyntax node.
      */
      void addAttributeToContent(const structure::XmlCommentSyntax& node, std::string& content, bool callVirtualBase);

      /**
      * \internal
      * \brief Converts the attributes of the structure::XmlCrefAttributeSyntax node.
      */
      void addAttributeToContent(const structure::XmlCrefAttributeSyntax& node, std::string& content, bool callVirtualBase);

      /**
      * \internal
      * \brief Converts the attributes of the structure::XmlElementEndTagSyntax node.
      */
      void addAttributeToContent(const structure::XmlElementEndTagSyntax& node, std::string& content, bool callVirtualBase);

      /**
      * \internal
      * \brief Converts the attributes of the structure::XmlElementStartTagSyntax node.
      */
      void addAttributeToContent(const structure::XmlElementStartTagSyntax& node, std::string& content, bool callVirtualBase);

      /**
      * \internal
      * \brief Converts the attributes of the structure::XmlElementSyntax node.
      */
      void addAttributeToContent(const structure::XmlElementSyntax& node, std::string& content, bool callVirtualBase);

      /**
      * \internal
      * \brief Converts the attributes of the structure::XmlEmptyElementSyntax node.
      */
      void addAttributeToContent(const structure::XmlEmptyElementSyntax& node, std::string& content, bool callVirtualBase);

      /**
      * \internal
      * \brief Converts the attributes of the structure::XmlNameAttributeSyntax node.
      */
      void addAttributeToContent(const structure::XmlNameAttributeSyntax& node, std::string& content, bool callVirtualBase);

      /**
      * \internal
      * \brief Converts the attributes of the structure::XmlNameSyntax node.
      */
      void addAttributeToContent(const structure::XmlNameSyntax& node, std::string& content, bool callVirtualBase);

      /**
      * \internal
      * \brief Converts the attributes of the structure::XmlNodeSyntax node.
      */
      void addAttributeToContent(const structure::XmlNodeSyntax& node, std::string& content, bool callVirtualBase);

      /**
      * \internal
      * \brief Converts the attributes of the structure::XmlPrefixSyntax node.
      */
      void addAttributeToContent(const structure::XmlPrefixSyntax& node, std::string& content, bool callVirtualBase);

      /**
      * \internal
      * \brief Converts the attributes of the structure::XmlProcessingInstructionSyntax node.
      */
      void addAttributeToContent(const structure::XmlProcessingInstructionSyntax& node, std::string& content, bool callVirtualBase);

      /**
      * \internal
      * \brief Converts the attributes of the structure::XmlTextAttributeSyntax node.
      */
      void addAttributeToContent(const structure::XmlTextAttributeSyntax& node, std::string& content, bool callVirtualBase);

      /**
      * \internal
      * \brief Converts the attributes of the structure::XmlTextSyntax node.
      */
      void addAttributeToContent(const structure::XmlTextSyntax& node, std::string& content, bool callVirtualBase);

      /** \internal \brief The ofstream into the DOT graph will be written. */
      columbus::io::GraphmlIO &io;

      /** \internal \brief Internal counter for generating edges. */
      long long edgeCounter;

    private:

      /** \internal \brief It contains ids of the drawed nodes */
      std::map< NodeId, bool> idsToDrawedNodes;

      /** \internal \brief How many edges are should be draw */
      unsigned int maxDrawingDepth;

      /** \internal \brief Edges names to filtering */
      std::set< std::string> edgeFilter;

      /** \internal \brief The contains is not enable to draw */
      std::set< NodeId> nodeFilter;

      /** \internal \brief The contains is not enable to draw */
      bool visitCrossEdge;

      /** \internal \brief It is need to draw into white */
      bool isColorWhite;

      /** \internal \brief Show attributes only of these node types. If it is empty then show all attributes. */
      std::set< std::string> nodeTypeAttributeFilter;

      /** \internal \brief Helper variable for determine is the actual node groupNode it visitEnd */
      NodeId lastVisitedNodeId;

      /** \internal \brief Helper variable for edgeKind grouping */
      std::list<EdgeKind> edgeKindStack;

      /** \internal \brief Helper variable for edgeKind grouping */
      std::list<NodeId> parentNodeStack;

      /** \internal \brief It is need to grouping tree nodes */
      bool isGroupingTreeNodes;

      /** \internal \brief Node type names to filtering out */
      std::set< std::string> nodeTypeFilter;

  }; // VisitorGraphml


}}}
#endif

