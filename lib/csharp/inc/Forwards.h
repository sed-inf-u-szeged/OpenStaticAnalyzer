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

#ifndef _CSHARP_Forwards_H_
#define _CSHARP_Forwards_H_

/**
* \file Forwards.h
* \brief Contains forward declarations of the classes.
*/

namespace columbus { namespace csharp { namespace asg {

  class Algorithm;
  class AlgorithmPreorder;
  class ReverseEdges;

  class Visitor;
  class VisitorAbstractNodes;
  class VisitorGraphml;
  class VisitorCSHARPML;
  class VisitorFilter;
  class VisitorReverseEdges;
  class VisitorSave;

  template <typename T>
  class ListIterator;
  class Factory;
  class Filter;

  class SourcePosition;
  namespace base {
    class Base;
    class Positioned;
  }

  namespace expression {
    class AliasQualifiedNameSyntax;
    class AnonymousFunctionExpressionSyntax;
    class AnonymousMethodExpressionSyntax;
    class AnonymousObjectCreationExpressionSyntax;
    class ArrayCreationExpressionSyntax;
    class ArrayTypeSyntax;
    class AssignmentExpressionSyntax;
    class AwaitExpressionSyntax;
    class BaseExpressionSyntax;
    class BinaryExpressionSyntax;
    class CastExpressionSyntax;
    class CheckedExpressionSyntax;
    class ConditionalAccessExpressionSyntax;
    class ConditionalExpressionSyntax;
    class DefaultExpressionSyntax;
    class ElementAccessExpressionSyntax;
    class ElementBindingExpressionSyntax;
    class ExpressionSyntax;
    class GenericNameSyntax;
    class IdentifierNameSyntax;
    class ImplicitArrayCreationExpressionSyntax;
    class ImplicitElementAccessSyntax;
    class InitializerExpressionSyntax;
    class InstanceExpressionSyntax;
    class InterpolatedStringExpressionSyntax;
    class InvocationExpressionSyntax;
    class LambdaExpressionSyntax;
    class LiteralExpressionSyntax;
    class MakeRefExpressionSyntax;
    class MemberAccessExpressionSyntax;
    class MemberBindingExpressionSyntax;
    class NameSyntax;
    class NullableTypeSyntax;
    class ObjectCreationExpressionSyntax;
    class OmittedArraySizeExpressionSyntax;
    class OmittedTypeArgumentSyntax;
    class ParenthesizedExpressionSyntax;
    class ParenthesizedLambdaExpressionSyntax;
    class PointerTypeSyntax;
    class PostfixUnaryExpressionSyntax;
    class PredefinedTypeSyntax;
    class PrefixUnaryExpressionSyntax;
    class QualifiedNameSyntax;
    class QueryExpressionSyntax;
    class RefTypeExpressionSyntax;
    class RefValueExpressionSyntax;
    class SimpleLambdaExpressionSyntax;
    class SimpleNameSyntax;
    class SizeOfExpressionSyntax;
    class StackAllocArrayCreationExpressionSyntax;
    class ThisExpressionSyntax;
    class TypeOfExpressionSyntax;
    class TypeSyntax;
  }

  namespace statement {
    class BlockSyntax;
    class BreakStatementSyntax;
    class CheckedStatementSyntax;
    class ContinueStatementSyntax;
    class DoStatementSyntax;
    class EmptyStatementSyntax;
    class ExpressionStatementSyntax;
    class FixedStatementSyntax;
    class ForEachStatementSyntax;
    class ForStatementSyntax;
    class GotoStatementSyntax;
    class IfStatementSyntax;
    class LabeledStatementSyntax;
    class LocalDeclarationStatementSyntax;
    class LockStatementSyntax;
    class ReturnStatementSyntax;
    class StatementSyntax;
    class SwitchStatementSyntax;
    class ThrowStatementSyntax;
    class TryStatementSyntax;
    class UnsafeStatementSyntax;
    class UsingStatementSyntax;
    class WhileStatementSyntax;
    class YieldStatementSyntax;
  }

  namespace structure {
    class AccessorDeclarationSyntax;
    class AccessorListSyntax;
    class AnonymousObjectMemberDeclaratorSyntax;
    class ArgumentListSyntax;
    class ArgumentSyntax;
    class ArrayRankSpecifierSyntax;
    class ArrowExpressionClauseSyntax;
    class AttributeArgumentListSyntax;
    class AttributeArgumentSyntax;
    class AttributeListSyntax;
    class AttributeSyntax;
    class AttributeTargetSpecifierSyntax;
    class BaseArgumentListSyntax;
    class BaseCrefParameterListSyntax;
    class BaseFieldDeclarationSyntax;
    class BaseListSyntax;
    class BaseMethodDeclarationSyntax;
    class BaseParameterListSyntax;
    class BasePropertyDeclarationSyntax;
    class BaseTypeDeclarationSyntax;
    class BaseTypeSyntax;
    class BracketedArgumentListSyntax;
    class BracketedParameterListSyntax;
    class CaseSwitchLabelSyntax;
    class CatchClauseSyntax;
    class CatchDeclarationSyntax;
    class CatchFilterClauseSyntax;
    class ClassDeclarationSyntax;
    class ClassOrStructConstraintSyntax;
    class CompilationUnitSyntax;
    class ConstructorConstraintSyntax;
    class ConstructorDeclarationSyntax;
    class ConstructorInitializerSyntax;
    class ConversionOperatorDeclarationSyntax;
    class ConversionOperatorMemberCrefSyntax;
    class CrefBracketedParameterListSyntax;
    class CrefParameterListSyntax;
    class CrefParameterSyntax;
    class CrefSyntax;
    class DefaultSwitchLabelSyntax;
    class DelegateDeclarationSyntax;
    class DestructorDeclarationSyntax;
    class ElseClauseSyntax;
    class EnumDeclarationSyntax;
    class EnumMemberDeclarationSyntax;
    class EqualsValueClauseSyntax;
    class EventDeclarationSyntax;
    class EventFieldDeclarationSyntax;
    class ExplicitInterfaceSpecifierSyntax;
    class ExternAliasDirectiveSyntax;
    class FieldDeclarationSyntax;
    class FinallyClauseSyntax;
    class FromClauseSyntax;
    class GlobalStatementSyntax;
    class GroupClauseSyntax;
    class IncompleteMemberSyntax;
    class IndexerDeclarationSyntax;
    class IndexerMemberCrefSyntax;
    class InterfaceDeclarationSyntax;
    class InterpolatedStringContentSyntax;
    class InterpolatedStringTextSyntax;
    class InterpolationAlignmentClauseSyntax;
    class InterpolationFormatClauseSyntax;
    class InterpolationSyntax;
    class JoinClauseSyntax;
    class JoinIntoClauseSyntax;
    class LetClauseSyntax;
    class MemberCrefSyntax;
    class MemberDeclarationSyntax;
    class MethodDeclarationSyntax;
    class NameColonSyntax;
    class NameEqualsSyntax;
    class NameMemberCrefSyntax;
    class NamespaceDeclarationSyntax;
    class OperatorDeclarationSyntax;
    class OperatorMemberCrefSyntax;
    class OrderByClauseSyntax;
    class OrderingSyntax;
    class ParameterListSyntax;
    class ParameterSyntax;
    class PropertyDeclarationSyntax;
    class QualifiedCrefSyntax;
    class QueryBodySyntax;
    class QueryClauseSyntax;
    class QueryContinuationSyntax;
    class SelectClauseSyntax;
    class SelectOrGroupClauseSyntax;
    class SimpleBaseTypeSyntax;
    class StructDeclarationSyntax;
    class SwitchLabelSyntax;
    class SwitchSectionSyntax;
    class SyntaxToken;
    class TypeArgumentListSyntax;
    class TypeConstraintSyntax;
    class TypeCrefSyntax;
    class TypeDeclarationSyntax;
    class TypeParameterConstraintClauseSyntax;
    class TypeParameterConstraintSyntax;
    class TypeParameterListSyntax;
    class TypeParameterSyntax;
    class UsingDirectiveSyntax;
    class VariableDeclarationSyntax;
    class VariableDeclaratorSyntax;
    class WhereClauseSyntax;
    class XmlAttributeSyntax;
    class XmlCDataSectionSyntax;
    class XmlCommentSyntax;
    class XmlCrefAttributeSyntax;
    class XmlElementEndTagSyntax;
    class XmlElementStartTagSyntax;
    class XmlElementSyntax;
    class XmlEmptyElementSyntax;
    class XmlNameAttributeSyntax;
    class XmlNameSyntax;
    class XmlNodeSyntax;
    class XmlPrefixSyntax;
    class XmlProcessingInstructionSyntax;
    class XmlTextAttributeSyntax;
    class XmlTextSyntax;
  }


}}}

#endif

