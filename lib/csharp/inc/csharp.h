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

#ifndef _CSHARP_H_
#define _CSHARP_H_

/**
* \file CSHARP.h
* \brief Header can be used for precompiled header.
*/
/*********** Options *************************
 *  SchemaGenerator347b651cde
 *  IndentInNamespace = 1
 *  IndentInClass = 1
 *  IndentUnderPubProtPri = 1
 *  UseShortRange = true
 *  ACommonGetIsForLeaf = true
 *  AlgPreorderSafeMode = true
 *  GenerateInOutForComment = true
 *  GenerateFilter = true
 *  GenerateReverseEdges = true
 *  GenerateAsgStat = false
 *  GenerateSpecFilterVisitor = false
 *  GenerateSpecXml = false
 *  GenerateDOT = false
 *  GenerateGraphml = true
 *  GenerateJSON = false
 *  GenerateSerialize = false
 *  GenerateParentEdge = true
 *  FactoryModes = 
 *  APIVersion = 0.9
 *  BinaryVersion = 0.9
 *  CSIHeaderText = CSharpLanguage
 *********************************************/
#include <list>
#include <cstring>
#include <map>
#include <set>
#include <string>
#include <boost/crc.hpp>

#include "csi/inc/HeaderData.h" 
#include "csi/inc/PropertyData.h" 
#include "Forwards.h"

// externals
#include "AsgCommon.h"
#include "strtable/inc/RefDistributorStrTable.h"
#include "csi/inc/csi.h"
#include "Exception.h"

#include "Constant.h"
#include "Types.h"
#include "CsharpException.h"
#include "ListIterator.h"
#include "Common.h"
#include "ReverseEdges.h"

#include "SourcePosition.h"

 /***********************NODES******************/
#include "base/Base.h"
#include "base/Positioned.h"
#include "expression/ExpressionSyntax.h"
#include "statement/StatementSyntax.h"
#include "structure/AccessorDeclarationSyntax.h"
#include "structure/AccessorListSyntax.h"
#include "structure/AnonymousObjectMemberDeclaratorSyntax.h"
#include "structure/ArgumentSyntax.h"
#include "structure/ArrayRankSpecifierSyntax.h"
#include "structure/ArrowExpressionClauseSyntax.h"
#include "structure/AttributeArgumentListSyntax.h"
#include "structure/AttributeArgumentSyntax.h"
#include "structure/AttributeListSyntax.h"
#include "structure/AttributeSyntax.h"
#include "structure/AttributeTargetSpecifierSyntax.h"
#include "structure/BaseArgumentListSyntax.h"
#include "structure/BaseCrefParameterListSyntax.h"
#include "structure/BaseListSyntax.h"
#include "structure/BaseParameterListSyntax.h"
#include "structure/BaseTypeSyntax.h"
#include "structure/CatchClauseSyntax.h"
#include "structure/CatchDeclarationSyntax.h"
#include "structure/CatchFilterClauseSyntax.h"
#include "structure/CompilationUnitSyntax.h"
#include "structure/ConstructorInitializerSyntax.h"
#include "structure/CrefParameterSyntax.h"
#include "structure/CrefSyntax.h"
#include "structure/ElseClauseSyntax.h"
#include "structure/EqualsValueClauseSyntax.h"
#include "structure/ExplicitInterfaceSpecifierSyntax.h"
#include "structure/ExternAliasDirectiveSyntax.h"
#include "structure/FinallyClauseSyntax.h"
#include "structure/InterpolatedStringContentSyntax.h"
#include "structure/InterpolationAlignmentClauseSyntax.h"
#include "structure/InterpolationFormatClauseSyntax.h"
#include "structure/JoinIntoClauseSyntax.h"
#include "structure/MemberDeclarationSyntax.h"
#include "structure/NameColonSyntax.h"
#include "structure/NameEqualsSyntax.h"
#include "structure/OrderingSyntax.h"
#include "structure/ParameterSyntax.h"
#include "structure/QueryBodySyntax.h"
#include "structure/QueryClauseSyntax.h"
#include "structure/QueryContinuationSyntax.h"
#include "structure/SelectOrGroupClauseSyntax.h"
#include "structure/SwitchLabelSyntax.h"
#include "structure/SwitchSectionSyntax.h"
#include "structure/SyntaxToken.h"
#include "structure/TypeArgumentListSyntax.h"
#include "structure/TypeParameterConstraintClauseSyntax.h"
#include "structure/TypeParameterConstraintSyntax.h"
#include "structure/TypeParameterListSyntax.h"
#include "structure/TypeParameterSyntax.h"
#include "structure/UsingDirectiveSyntax.h"
#include "structure/VariableDeclarationSyntax.h"
#include "structure/VariableDeclaratorSyntax.h"
#include "structure/XmlAttributeSyntax.h"
#include "structure/XmlElementEndTagSyntax.h"
#include "structure/XmlElementStartTagSyntax.h"
#include "structure/XmlNameSyntax.h"
#include "structure/XmlNodeSyntax.h"
#include "structure/XmlPrefixSyntax.h"
#include "expression/AnonymousFunctionExpressionSyntax.h"
#include "expression/AnonymousObjectCreationExpressionSyntax.h"
#include "expression/ArrayCreationExpressionSyntax.h"
#include "expression/AssignmentExpressionSyntax.h"
#include "expression/AwaitExpressionSyntax.h"
#include "expression/BinaryExpressionSyntax.h"
#include "expression/CastExpressionSyntax.h"
#include "expression/CheckedExpressionSyntax.h"
#include "expression/ConditionalAccessExpressionSyntax.h"
#include "expression/ConditionalExpressionSyntax.h"
#include "expression/DefaultExpressionSyntax.h"
#include "expression/ElementAccessExpressionSyntax.h"
#include "expression/ElementBindingExpressionSyntax.h"
#include "expression/ImplicitArrayCreationExpressionSyntax.h"
#include "expression/ImplicitElementAccessSyntax.h"
#include "expression/InitializerExpressionSyntax.h"
#include "expression/InstanceExpressionSyntax.h"
#include "expression/InterpolatedStringExpressionSyntax.h"
#include "expression/InvocationExpressionSyntax.h"
#include "expression/LiteralExpressionSyntax.h"
#include "expression/MakeRefExpressionSyntax.h"
#include "expression/MemberAccessExpressionSyntax.h"
#include "expression/MemberBindingExpressionSyntax.h"
#include "expression/ObjectCreationExpressionSyntax.h"
#include "expression/OmittedArraySizeExpressionSyntax.h"
#include "expression/ParenthesizedExpressionSyntax.h"
#include "expression/PostfixUnaryExpressionSyntax.h"
#include "expression/PrefixUnaryExpressionSyntax.h"
#include "expression/QueryExpressionSyntax.h"
#include "expression/RefTypeExpressionSyntax.h"
#include "expression/RefValueExpressionSyntax.h"
#include "expression/SizeOfExpressionSyntax.h"
#include "expression/StackAllocArrayCreationExpressionSyntax.h"
#include "expression/TypeOfExpressionSyntax.h"
#include "expression/TypeSyntax.h"
#include "statement/BlockSyntax.h"
#include "statement/BreakStatementSyntax.h"
#include "statement/CheckedStatementSyntax.h"
#include "statement/ContinueStatementSyntax.h"
#include "statement/DoStatementSyntax.h"
#include "statement/EmptyStatementSyntax.h"
#include "statement/ExpressionStatementSyntax.h"
#include "statement/FixedStatementSyntax.h"
#include "statement/ForEachStatementSyntax.h"
#include "statement/ForStatementSyntax.h"
#include "statement/GotoStatementSyntax.h"
#include "statement/IfStatementSyntax.h"
#include "statement/LabeledStatementSyntax.h"
#include "statement/LocalDeclarationStatementSyntax.h"
#include "statement/LockStatementSyntax.h"
#include "statement/ReturnStatementSyntax.h"
#include "statement/SwitchStatementSyntax.h"
#include "statement/ThrowStatementSyntax.h"
#include "statement/TryStatementSyntax.h"
#include "statement/UnsafeStatementSyntax.h"
#include "statement/UsingStatementSyntax.h"
#include "statement/WhileStatementSyntax.h"
#include "statement/YieldStatementSyntax.h"
#include "structure/ArgumentListSyntax.h"
#include "structure/BracketedArgumentListSyntax.h"
#include "structure/CrefBracketedParameterListSyntax.h"
#include "structure/CrefParameterListSyntax.h"
#include "structure/BracketedParameterListSyntax.h"
#include "structure/ParameterListSyntax.h"
#include "structure/SimpleBaseTypeSyntax.h"
#include "structure/MemberCrefSyntax.h"
#include "structure/QualifiedCrefSyntax.h"
#include "structure/TypeCrefSyntax.h"
#include "structure/InterpolatedStringTextSyntax.h"
#include "structure/InterpolationSyntax.h"
#include "structure/BaseFieldDeclarationSyntax.h"
#include "structure/BaseMethodDeclarationSyntax.h"
#include "structure/BasePropertyDeclarationSyntax.h"
#include "structure/BaseTypeDeclarationSyntax.h"
#include "structure/DelegateDeclarationSyntax.h"
#include "structure/EnumMemberDeclarationSyntax.h"
#include "structure/GlobalStatementSyntax.h"
#include "structure/IncompleteMemberSyntax.h"
#include "structure/NamespaceDeclarationSyntax.h"
#include "structure/FromClauseSyntax.h"
#include "structure/JoinClauseSyntax.h"
#include "structure/LetClauseSyntax.h"
#include "structure/OrderByClauseSyntax.h"
#include "structure/WhereClauseSyntax.h"
#include "structure/GroupClauseSyntax.h"
#include "structure/SelectClauseSyntax.h"
#include "structure/CaseSwitchLabelSyntax.h"
#include "structure/DefaultSwitchLabelSyntax.h"
#include "structure/ClassOrStructConstraintSyntax.h"
#include "structure/ConstructorConstraintSyntax.h"
#include "structure/TypeConstraintSyntax.h"
#include "structure/XmlCrefAttributeSyntax.h"
#include "structure/XmlNameAttributeSyntax.h"
#include "structure/XmlTextAttributeSyntax.h"
#include "structure/XmlCDataSectionSyntax.h"
#include "structure/XmlCommentSyntax.h"
#include "structure/XmlElementSyntax.h"
#include "structure/XmlEmptyElementSyntax.h"
#include "structure/XmlProcessingInstructionSyntax.h"
#include "structure/XmlTextSyntax.h"
#include "expression/AnonymousMethodExpressionSyntax.h"
#include "expression/LambdaExpressionSyntax.h"
#include "expression/BaseExpressionSyntax.h"
#include "expression/ThisExpressionSyntax.h"
#include "expression/ArrayTypeSyntax.h"
#include "expression/NameSyntax.h"
#include "expression/NullableTypeSyntax.h"
#include "expression/OmittedTypeArgumentSyntax.h"
#include "expression/PointerTypeSyntax.h"
#include "expression/PredefinedTypeSyntax.h"
#include "structure/ConversionOperatorMemberCrefSyntax.h"
#include "structure/IndexerMemberCrefSyntax.h"
#include "structure/NameMemberCrefSyntax.h"
#include "structure/OperatorMemberCrefSyntax.h"
#include "structure/EventFieldDeclarationSyntax.h"
#include "structure/FieldDeclarationSyntax.h"
#include "structure/ConstructorDeclarationSyntax.h"
#include "structure/ConversionOperatorDeclarationSyntax.h"
#include "structure/DestructorDeclarationSyntax.h"
#include "structure/MethodDeclarationSyntax.h"
#include "structure/OperatorDeclarationSyntax.h"
#include "structure/EventDeclarationSyntax.h"
#include "structure/IndexerDeclarationSyntax.h"
#include "structure/PropertyDeclarationSyntax.h"
#include "structure/EnumDeclarationSyntax.h"
#include "structure/TypeDeclarationSyntax.h"
#include "expression/ParenthesizedLambdaExpressionSyntax.h"
#include "expression/SimpleLambdaExpressionSyntax.h"
#include "expression/AliasQualifiedNameSyntax.h"
#include "expression/QualifiedNameSyntax.h"
#include "expression/SimpleNameSyntax.h"
#include "structure/ClassDeclarationSyntax.h"
#include "structure/InterfaceDeclarationSyntax.h"
#include "structure/StructDeclarationSyntax.h"
#include "expression/GenericNameSyntax.h"
#include "expression/IdentifierNameSyntax.h"


#include "Filter.h"
#include "Factory.h"

#include "visitors/Visitor.h"
#include "visitors/VisitorAbstractNodes.h"
#include "visitors/VisitorGraphml.h"
#include "visitors/VisitorCSHARPML.h"
#include "visitors/VisitorFilter.h"
#include "visitors/VisitorReverseEdges.h"
#include "visitors/VisitorSave.h"
#include "visitors/VisitorSubtreeCollector.h"
#include "visitors/VisitorSimpleEdge.h"

#include "algorithms/Algorithm.h"
#include "algorithms/AlgorithmPreorder.h"
#include "algorithms/AlgorithmDeepCopy.h"

#endif

