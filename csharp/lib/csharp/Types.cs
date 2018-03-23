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

using System;
using System.Text;

namespace Columbus.Csharp.Asg {

    /// <summary>
    /// Contains some predefined types.
    /// </summary>
#if (CSHARP_INTERNAL)
    internal
#else
    public
#endif
    class Types {

        /// <summary>
        /// Validation kind for the ASG.
        /// </summary>
        [Flags]
        public enum AsgValidationKind {

            /// <summary>The ASG is valid.</summary>
            avkValid = 1,

            /// <summary>The ASG does not contain the FileType information.</summary>
            avkMissingFileType = 2,

            /// <summary>The ASG contains wrong FileType information.</summary>
            avkWrongFileType = 4,

            /// <summary>The ASG does not contain the ApiVersion information.</summary>
            avkMissingApiVersion = 8,

            /// <summary>The ASG contains wrong ApiVersion information.</summary>
            avkWrongApiVersion = 16,

            /// <summary>The ASG does not contain the BinaryVersion information.</summary>
            avkMissingBinaryVersion = 32,

            /// <summary>The ASG contains wrong BinaryVersion information.</summary>
            avkWrongBinaryVersion = 64,

            /// <summary>An unknow error occured when reading the ASG.</summary>
            avkUnknownError = 128

        }

        /// <summary>
        /// Enumeration for the NodeKind kind.
        /// </summary>
        public enum NodeKind {

            /// <summary>Value if the NodeKind is Base.</summary>
            ndkBase,

            /// <summary>Value if the NodeKind is Positioned.</summary>
            ndkPositioned,

            /// <summary>Value if the NodeKind is AliasQualifiedNameSyntax.</summary>
            ndkAliasQualifiedNameSyntax,

            /// <summary>Value if the NodeKind is AnonymousFunctionExpressionSyntax.</summary>
            ndkAnonymousFunctionExpressionSyntax,

            /// <summary>Value if the NodeKind is AnonymousMethodExpressionSyntax.</summary>
            ndkAnonymousMethodExpressionSyntax,

            /// <summary>Value if the NodeKind is AnonymousObjectCreationExpressionSyntax.</summary>
            ndkAnonymousObjectCreationExpressionSyntax,

            /// <summary>Value if the NodeKind is ArrayCreationExpressionSyntax.</summary>
            ndkArrayCreationExpressionSyntax,

            /// <summary>Value if the NodeKind is ArrayTypeSyntax.</summary>
            ndkArrayTypeSyntax,

            /// <summary>Value if the NodeKind is AssignmentExpressionSyntax.</summary>
            ndkAssignmentExpressionSyntax,

            /// <summary>Value if the NodeKind is AwaitExpressionSyntax.</summary>
            ndkAwaitExpressionSyntax,

            /// <summary>Value if the NodeKind is BaseExpressionSyntax.</summary>
            ndkBaseExpressionSyntax,

            /// <summary>Value if the NodeKind is BinaryExpressionSyntax.</summary>
            ndkBinaryExpressionSyntax,

            /// <summary>Value if the NodeKind is CastExpressionSyntax.</summary>
            ndkCastExpressionSyntax,

            /// <summary>Value if the NodeKind is CheckedExpressionSyntax.</summary>
            ndkCheckedExpressionSyntax,

            /// <summary>Value if the NodeKind is ConditionalAccessExpressionSyntax.</summary>
            ndkConditionalAccessExpressionSyntax,

            /// <summary>Value if the NodeKind is ConditionalExpressionSyntax.</summary>
            ndkConditionalExpressionSyntax,

            /// <summary>Value if the NodeKind is DefaultExpressionSyntax.</summary>
            ndkDefaultExpressionSyntax,

            /// <summary>Value if the NodeKind is ElementAccessExpressionSyntax.</summary>
            ndkElementAccessExpressionSyntax,

            /// <summary>Value if the NodeKind is ElementBindingExpressionSyntax.</summary>
            ndkElementBindingExpressionSyntax,

            /// <summary>Value if the NodeKind is ExpressionSyntax.</summary>
            ndkExpressionSyntax,

            /// <summary>Value if the NodeKind is GenericNameSyntax.</summary>
            ndkGenericNameSyntax,

            /// <summary>Value if the NodeKind is IdentifierNameSyntax.</summary>
            ndkIdentifierNameSyntax,

            /// <summary>Value if the NodeKind is ImplicitArrayCreationExpressionSyntax.</summary>
            ndkImplicitArrayCreationExpressionSyntax,

            /// <summary>Value if the NodeKind is ImplicitElementAccessSyntax.</summary>
            ndkImplicitElementAccessSyntax,

            /// <summary>Value if the NodeKind is InitializerExpressionSyntax.</summary>
            ndkInitializerExpressionSyntax,

            /// <summary>Value if the NodeKind is InstanceExpressionSyntax.</summary>
            ndkInstanceExpressionSyntax,

            /// <summary>Value if the NodeKind is InterpolatedStringExpressionSyntax.</summary>
            ndkInterpolatedStringExpressionSyntax,

            /// <summary>Value if the NodeKind is InvocationExpressionSyntax.</summary>
            ndkInvocationExpressionSyntax,

            /// <summary>Value if the NodeKind is LambdaExpressionSyntax.</summary>
            ndkLambdaExpressionSyntax,

            /// <summary>Value if the NodeKind is LiteralExpressionSyntax.</summary>
            ndkLiteralExpressionSyntax,

            /// <summary>Value if the NodeKind is MakeRefExpressionSyntax.</summary>
            ndkMakeRefExpressionSyntax,

            /// <summary>Value if the NodeKind is MemberAccessExpressionSyntax.</summary>
            ndkMemberAccessExpressionSyntax,

            /// <summary>Value if the NodeKind is MemberBindingExpressionSyntax.</summary>
            ndkMemberBindingExpressionSyntax,

            /// <summary>Value if the NodeKind is NameSyntax.</summary>
            ndkNameSyntax,

            /// <summary>Value if the NodeKind is NullableTypeSyntax.</summary>
            ndkNullableTypeSyntax,

            /// <summary>Value if the NodeKind is ObjectCreationExpressionSyntax.</summary>
            ndkObjectCreationExpressionSyntax,

            /// <summary>Value if the NodeKind is OmittedArraySizeExpressionSyntax.</summary>
            ndkOmittedArraySizeExpressionSyntax,

            /// <summary>Value if the NodeKind is OmittedTypeArgumentSyntax.</summary>
            ndkOmittedTypeArgumentSyntax,

            /// <summary>Value if the NodeKind is ParenthesizedExpressionSyntax.</summary>
            ndkParenthesizedExpressionSyntax,

            /// <summary>Value if the NodeKind is ParenthesizedLambdaExpressionSyntax.</summary>
            ndkParenthesizedLambdaExpressionSyntax,

            /// <summary>Value if the NodeKind is PointerTypeSyntax.</summary>
            ndkPointerTypeSyntax,

            /// <summary>Value if the NodeKind is PostfixUnaryExpressionSyntax.</summary>
            ndkPostfixUnaryExpressionSyntax,

            /// <summary>Value if the NodeKind is PredefinedTypeSyntax.</summary>
            ndkPredefinedTypeSyntax,

            /// <summary>Value if the NodeKind is PrefixUnaryExpressionSyntax.</summary>
            ndkPrefixUnaryExpressionSyntax,

            /// <summary>Value if the NodeKind is QualifiedNameSyntax.</summary>
            ndkQualifiedNameSyntax,

            /// <summary>Value if the NodeKind is QueryExpressionSyntax.</summary>
            ndkQueryExpressionSyntax,

            /// <summary>Value if the NodeKind is RefTypeExpressionSyntax.</summary>
            ndkRefTypeExpressionSyntax,

            /// <summary>Value if the NodeKind is RefValueExpressionSyntax.</summary>
            ndkRefValueExpressionSyntax,

            /// <summary>Value if the NodeKind is SimpleLambdaExpressionSyntax.</summary>
            ndkSimpleLambdaExpressionSyntax,

            /// <summary>Value if the NodeKind is SimpleNameSyntax.</summary>
            ndkSimpleNameSyntax,

            /// <summary>Value if the NodeKind is SizeOfExpressionSyntax.</summary>
            ndkSizeOfExpressionSyntax,

            /// <summary>Value if the NodeKind is StackAllocArrayCreationExpressionSyntax.</summary>
            ndkStackAllocArrayCreationExpressionSyntax,

            /// <summary>Value if the NodeKind is ThisExpressionSyntax.</summary>
            ndkThisExpressionSyntax,

            /// <summary>Value if the NodeKind is TypeOfExpressionSyntax.</summary>
            ndkTypeOfExpressionSyntax,

            /// <summary>Value if the NodeKind is TypeSyntax.</summary>
            ndkTypeSyntax,

            /// <summary>Value if the NodeKind is BlockSyntax.</summary>
            ndkBlockSyntax,

            /// <summary>Value if the NodeKind is BreakStatementSyntax.</summary>
            ndkBreakStatementSyntax,

            /// <summary>Value if the NodeKind is CheckedStatementSyntax.</summary>
            ndkCheckedStatementSyntax,

            /// <summary>Value if the NodeKind is ContinueStatementSyntax.</summary>
            ndkContinueStatementSyntax,

            /// <summary>Value if the NodeKind is DoStatementSyntax.</summary>
            ndkDoStatementSyntax,

            /// <summary>Value if the NodeKind is EmptyStatementSyntax.</summary>
            ndkEmptyStatementSyntax,

            /// <summary>Value if the NodeKind is ExpressionStatementSyntax.</summary>
            ndkExpressionStatementSyntax,

            /// <summary>Value if the NodeKind is FixedStatementSyntax.</summary>
            ndkFixedStatementSyntax,

            /// <summary>Value if the NodeKind is ForEachStatementSyntax.</summary>
            ndkForEachStatementSyntax,

            /// <summary>Value if the NodeKind is ForStatementSyntax.</summary>
            ndkForStatementSyntax,

            /// <summary>Value if the NodeKind is GotoStatementSyntax.</summary>
            ndkGotoStatementSyntax,

            /// <summary>Value if the NodeKind is IfStatementSyntax.</summary>
            ndkIfStatementSyntax,

            /// <summary>Value if the NodeKind is LabeledStatementSyntax.</summary>
            ndkLabeledStatementSyntax,

            /// <summary>Value if the NodeKind is LocalDeclarationStatementSyntax.</summary>
            ndkLocalDeclarationStatementSyntax,

            /// <summary>Value if the NodeKind is LockStatementSyntax.</summary>
            ndkLockStatementSyntax,

            /// <summary>Value if the NodeKind is ReturnStatementSyntax.</summary>
            ndkReturnStatementSyntax,

            /// <summary>Value if the NodeKind is StatementSyntax.</summary>
            ndkStatementSyntax,

            /// <summary>Value if the NodeKind is SwitchStatementSyntax.</summary>
            ndkSwitchStatementSyntax,

            /// <summary>Value if the NodeKind is ThrowStatementSyntax.</summary>
            ndkThrowStatementSyntax,

            /// <summary>Value if the NodeKind is TryStatementSyntax.</summary>
            ndkTryStatementSyntax,

            /// <summary>Value if the NodeKind is UnsafeStatementSyntax.</summary>
            ndkUnsafeStatementSyntax,

            /// <summary>Value if the NodeKind is UsingStatementSyntax.</summary>
            ndkUsingStatementSyntax,

            /// <summary>Value if the NodeKind is WhileStatementSyntax.</summary>
            ndkWhileStatementSyntax,

            /// <summary>Value if the NodeKind is YieldStatementSyntax.</summary>
            ndkYieldStatementSyntax,

            /// <summary>Value if the NodeKind is AccessorDeclarationSyntax.</summary>
            ndkAccessorDeclarationSyntax,

            /// <summary>Value if the NodeKind is AccessorListSyntax.</summary>
            ndkAccessorListSyntax,

            /// <summary>Value if the NodeKind is AnonymousObjectMemberDeclaratorSyntax.</summary>
            ndkAnonymousObjectMemberDeclaratorSyntax,

            /// <summary>Value if the NodeKind is ArgumentListSyntax.</summary>
            ndkArgumentListSyntax,

            /// <summary>Value if the NodeKind is ArgumentSyntax.</summary>
            ndkArgumentSyntax,

            /// <summary>Value if the NodeKind is ArrayRankSpecifierSyntax.</summary>
            ndkArrayRankSpecifierSyntax,

            /// <summary>Value if the NodeKind is ArrowExpressionClauseSyntax.</summary>
            ndkArrowExpressionClauseSyntax,

            /// <summary>Value if the NodeKind is AttributeArgumentListSyntax.</summary>
            ndkAttributeArgumentListSyntax,

            /// <summary>Value if the NodeKind is AttributeArgumentSyntax.</summary>
            ndkAttributeArgumentSyntax,

            /// <summary>Value if the NodeKind is AttributeListSyntax.</summary>
            ndkAttributeListSyntax,

            /// <summary>Value if the NodeKind is AttributeSyntax.</summary>
            ndkAttributeSyntax,

            /// <summary>Value if the NodeKind is AttributeTargetSpecifierSyntax.</summary>
            ndkAttributeTargetSpecifierSyntax,

            /// <summary>Value if the NodeKind is BaseArgumentListSyntax.</summary>
            ndkBaseArgumentListSyntax,

            /// <summary>Value if the NodeKind is BaseCrefParameterListSyntax.</summary>
            ndkBaseCrefParameterListSyntax,

            /// <summary>Value if the NodeKind is BaseFieldDeclarationSyntax.</summary>
            ndkBaseFieldDeclarationSyntax,

            /// <summary>Value if the NodeKind is BaseListSyntax.</summary>
            ndkBaseListSyntax,

            /// <summary>Value if the NodeKind is BaseMethodDeclarationSyntax.</summary>
            ndkBaseMethodDeclarationSyntax,

            /// <summary>Value if the NodeKind is BaseParameterListSyntax.</summary>
            ndkBaseParameterListSyntax,

            /// <summary>Value if the NodeKind is BasePropertyDeclarationSyntax.</summary>
            ndkBasePropertyDeclarationSyntax,

            /// <summary>Value if the NodeKind is BaseTypeDeclarationSyntax.</summary>
            ndkBaseTypeDeclarationSyntax,

            /// <summary>Value if the NodeKind is BaseTypeSyntax.</summary>
            ndkBaseTypeSyntax,

            /// <summary>Value if the NodeKind is BracketedArgumentListSyntax.</summary>
            ndkBracketedArgumentListSyntax,

            /// <summary>Value if the NodeKind is BracketedParameterListSyntax.</summary>
            ndkBracketedParameterListSyntax,

            /// <summary>Value if the NodeKind is CaseSwitchLabelSyntax.</summary>
            ndkCaseSwitchLabelSyntax,

            /// <summary>Value if the NodeKind is CatchClauseSyntax.</summary>
            ndkCatchClauseSyntax,

            /// <summary>Value if the NodeKind is CatchDeclarationSyntax.</summary>
            ndkCatchDeclarationSyntax,

            /// <summary>Value if the NodeKind is CatchFilterClauseSyntax.</summary>
            ndkCatchFilterClauseSyntax,

            /// <summary>Value if the NodeKind is ClassDeclarationSyntax.</summary>
            ndkClassDeclarationSyntax,

            /// <summary>Value if the NodeKind is ClassOrStructConstraintSyntax.</summary>
            ndkClassOrStructConstraintSyntax,

            /// <summary>Value if the NodeKind is CompilationUnitSyntax.</summary>
            ndkCompilationUnitSyntax,

            /// <summary>Value if the NodeKind is ConstructorConstraintSyntax.</summary>
            ndkConstructorConstraintSyntax,

            /// <summary>Value if the NodeKind is ConstructorDeclarationSyntax.</summary>
            ndkConstructorDeclarationSyntax,

            /// <summary>Value if the NodeKind is ConstructorInitializerSyntax.</summary>
            ndkConstructorInitializerSyntax,

            /// <summary>Value if the NodeKind is ConversionOperatorDeclarationSyntax.</summary>
            ndkConversionOperatorDeclarationSyntax,

            /// <summary>Value if the NodeKind is ConversionOperatorMemberCrefSyntax.</summary>
            ndkConversionOperatorMemberCrefSyntax,

            /// <summary>Value if the NodeKind is CrefBracketedParameterListSyntax.</summary>
            ndkCrefBracketedParameterListSyntax,

            /// <summary>Value if the NodeKind is CrefParameterListSyntax.</summary>
            ndkCrefParameterListSyntax,

            /// <summary>Value if the NodeKind is CrefParameterSyntax.</summary>
            ndkCrefParameterSyntax,

            /// <summary>Value if the NodeKind is CrefSyntax.</summary>
            ndkCrefSyntax,

            /// <summary>Value if the NodeKind is DefaultSwitchLabelSyntax.</summary>
            ndkDefaultSwitchLabelSyntax,

            /// <summary>Value if the NodeKind is DelegateDeclarationSyntax.</summary>
            ndkDelegateDeclarationSyntax,

            /// <summary>Value if the NodeKind is DestructorDeclarationSyntax.</summary>
            ndkDestructorDeclarationSyntax,

            /// <summary>Value if the NodeKind is ElseClauseSyntax.</summary>
            ndkElseClauseSyntax,

            /// <summary>Value if the NodeKind is EnumDeclarationSyntax.</summary>
            ndkEnumDeclarationSyntax,

            /// <summary>Value if the NodeKind is EnumMemberDeclarationSyntax.</summary>
            ndkEnumMemberDeclarationSyntax,

            /// <summary>Value if the NodeKind is EqualsValueClauseSyntax.</summary>
            ndkEqualsValueClauseSyntax,

            /// <summary>Value if the NodeKind is EventDeclarationSyntax.</summary>
            ndkEventDeclarationSyntax,

            /// <summary>Value if the NodeKind is EventFieldDeclarationSyntax.</summary>
            ndkEventFieldDeclarationSyntax,

            /// <summary>Value if the NodeKind is ExplicitInterfaceSpecifierSyntax.</summary>
            ndkExplicitInterfaceSpecifierSyntax,

            /// <summary>Value if the NodeKind is ExternAliasDirectiveSyntax.</summary>
            ndkExternAliasDirectiveSyntax,

            /// <summary>Value if the NodeKind is FieldDeclarationSyntax.</summary>
            ndkFieldDeclarationSyntax,

            /// <summary>Value if the NodeKind is FinallyClauseSyntax.</summary>
            ndkFinallyClauseSyntax,

            /// <summary>Value if the NodeKind is FromClauseSyntax.</summary>
            ndkFromClauseSyntax,

            /// <summary>Value if the NodeKind is GlobalStatementSyntax.</summary>
            ndkGlobalStatementSyntax,

            /// <summary>Value if the NodeKind is GroupClauseSyntax.</summary>
            ndkGroupClauseSyntax,

            /// <summary>Value if the NodeKind is IncompleteMemberSyntax.</summary>
            ndkIncompleteMemberSyntax,

            /// <summary>Value if the NodeKind is IndexerDeclarationSyntax.</summary>
            ndkIndexerDeclarationSyntax,

            /// <summary>Value if the NodeKind is IndexerMemberCrefSyntax.</summary>
            ndkIndexerMemberCrefSyntax,

            /// <summary>Value if the NodeKind is InterfaceDeclarationSyntax.</summary>
            ndkInterfaceDeclarationSyntax,

            /// <summary>Value if the NodeKind is InterpolatedStringContentSyntax.</summary>
            ndkInterpolatedStringContentSyntax,

            /// <summary>Value if the NodeKind is InterpolatedStringTextSyntax.</summary>
            ndkInterpolatedStringTextSyntax,

            /// <summary>Value if the NodeKind is InterpolationAlignmentClauseSyntax.</summary>
            ndkInterpolationAlignmentClauseSyntax,

            /// <summary>Value if the NodeKind is InterpolationFormatClauseSyntax.</summary>
            ndkInterpolationFormatClauseSyntax,

            /// <summary>Value if the NodeKind is InterpolationSyntax.</summary>
            ndkInterpolationSyntax,

            /// <summary>Value if the NodeKind is JoinClauseSyntax.</summary>
            ndkJoinClauseSyntax,

            /// <summary>Value if the NodeKind is JoinIntoClauseSyntax.</summary>
            ndkJoinIntoClauseSyntax,

            /// <summary>Value if the NodeKind is LetClauseSyntax.</summary>
            ndkLetClauseSyntax,

            /// <summary>Value if the NodeKind is MemberCrefSyntax.</summary>
            ndkMemberCrefSyntax,

            /// <summary>Value if the NodeKind is MemberDeclarationSyntax.</summary>
            ndkMemberDeclarationSyntax,

            /// <summary>Value if the NodeKind is MethodDeclarationSyntax.</summary>
            ndkMethodDeclarationSyntax,

            /// <summary>Value if the NodeKind is NameColonSyntax.</summary>
            ndkNameColonSyntax,

            /// <summary>Value if the NodeKind is NameEqualsSyntax.</summary>
            ndkNameEqualsSyntax,

            /// <summary>Value if the NodeKind is NameMemberCrefSyntax.</summary>
            ndkNameMemberCrefSyntax,

            /// <summary>Value if the NodeKind is NamespaceDeclarationSyntax.</summary>
            ndkNamespaceDeclarationSyntax,

            /// <summary>Value if the NodeKind is OperatorDeclarationSyntax.</summary>
            ndkOperatorDeclarationSyntax,

            /// <summary>Value if the NodeKind is OperatorMemberCrefSyntax.</summary>
            ndkOperatorMemberCrefSyntax,

            /// <summary>Value if the NodeKind is OrderByClauseSyntax.</summary>
            ndkOrderByClauseSyntax,

            /// <summary>Value if the NodeKind is OrderingSyntax.</summary>
            ndkOrderingSyntax,

            /// <summary>Value if the NodeKind is ParameterListSyntax.</summary>
            ndkParameterListSyntax,

            /// <summary>Value if the NodeKind is ParameterSyntax.</summary>
            ndkParameterSyntax,

            /// <summary>Value if the NodeKind is PropertyDeclarationSyntax.</summary>
            ndkPropertyDeclarationSyntax,

            /// <summary>Value if the NodeKind is QualifiedCrefSyntax.</summary>
            ndkQualifiedCrefSyntax,

            /// <summary>Value if the NodeKind is QueryBodySyntax.</summary>
            ndkQueryBodySyntax,

            /// <summary>Value if the NodeKind is QueryClauseSyntax.</summary>
            ndkQueryClauseSyntax,

            /// <summary>Value if the NodeKind is QueryContinuationSyntax.</summary>
            ndkQueryContinuationSyntax,

            /// <summary>Value if the NodeKind is SelectClauseSyntax.</summary>
            ndkSelectClauseSyntax,

            /// <summary>Value if the NodeKind is SelectOrGroupClauseSyntax.</summary>
            ndkSelectOrGroupClauseSyntax,

            /// <summary>Value if the NodeKind is SimpleBaseTypeSyntax.</summary>
            ndkSimpleBaseTypeSyntax,

            /// <summary>Value if the NodeKind is StructDeclarationSyntax.</summary>
            ndkStructDeclarationSyntax,

            /// <summary>Value if the NodeKind is SwitchLabelSyntax.</summary>
            ndkSwitchLabelSyntax,

            /// <summary>Value if the NodeKind is SwitchSectionSyntax.</summary>
            ndkSwitchSectionSyntax,

            /// <summary>Value if the NodeKind is SyntaxToken.</summary>
            ndkSyntaxToken,

            /// <summary>Value if the NodeKind is TypeArgumentListSyntax.</summary>
            ndkTypeArgumentListSyntax,

            /// <summary>Value if the NodeKind is TypeConstraintSyntax.</summary>
            ndkTypeConstraintSyntax,

            /// <summary>Value if the NodeKind is TypeCrefSyntax.</summary>
            ndkTypeCrefSyntax,

            /// <summary>Value if the NodeKind is TypeDeclarationSyntax.</summary>
            ndkTypeDeclarationSyntax,

            /// <summary>Value if the NodeKind is TypeParameterConstraintClauseSyntax.</summary>
            ndkTypeParameterConstraintClauseSyntax,

            /// <summary>Value if the NodeKind is TypeParameterConstraintSyntax.</summary>
            ndkTypeParameterConstraintSyntax,

            /// <summary>Value if the NodeKind is TypeParameterListSyntax.</summary>
            ndkTypeParameterListSyntax,

            /// <summary>Value if the NodeKind is TypeParameterSyntax.</summary>
            ndkTypeParameterSyntax,

            /// <summary>Value if the NodeKind is UsingDirectiveSyntax.</summary>
            ndkUsingDirectiveSyntax,

            /// <summary>Value if the NodeKind is VariableDeclarationSyntax.</summary>
            ndkVariableDeclarationSyntax,

            /// <summary>Value if the NodeKind is VariableDeclaratorSyntax.</summary>
            ndkVariableDeclaratorSyntax,

            /// <summary>Value if the NodeKind is WhereClauseSyntax.</summary>
            ndkWhereClauseSyntax,

            /// <summary>Value if the NodeKind is XmlAttributeSyntax.</summary>
            ndkXmlAttributeSyntax,

            /// <summary>Value if the NodeKind is XmlCDataSectionSyntax.</summary>
            ndkXmlCDataSectionSyntax,

            /// <summary>Value if the NodeKind is XmlCommentSyntax.</summary>
            ndkXmlCommentSyntax,

            /// <summary>Value if the NodeKind is XmlCrefAttributeSyntax.</summary>
            ndkXmlCrefAttributeSyntax,

            /// <summary>Value if the NodeKind is XmlElementEndTagSyntax.</summary>
            ndkXmlElementEndTagSyntax,

            /// <summary>Value if the NodeKind is XmlElementStartTagSyntax.</summary>
            ndkXmlElementStartTagSyntax,

            /// <summary>Value if the NodeKind is XmlElementSyntax.</summary>
            ndkXmlElementSyntax,

            /// <summary>Value if the NodeKind is XmlEmptyElementSyntax.</summary>
            ndkXmlEmptyElementSyntax,

            /// <summary>Value if the NodeKind is XmlNameAttributeSyntax.</summary>
            ndkXmlNameAttributeSyntax,

            /// <summary>Value if the NodeKind is XmlNameSyntax.</summary>
            ndkXmlNameSyntax,

            /// <summary>Value if the NodeKind is XmlNodeSyntax.</summary>
            ndkXmlNodeSyntax,

            /// <summary>Value if the NodeKind is XmlPrefixSyntax.</summary>
            ndkXmlPrefixSyntax,

            /// <summary>Value if the NodeKind is XmlProcessingInstructionSyntax.</summary>
            ndkXmlProcessingInstructionSyntax,

            /// <summary>Value if the NodeKind is XmlTextAttributeSyntax.</summary>
            ndkXmlTextAttributeSyntax,

            /// <summary>Value if the NodeKind is XmlTextSyntax.</summary>
            ndkXmlTextSyntax

        }

        /// <summary>
        /// Enumeration for the EdgeKind kind.
        /// </summary>
        public enum EdgeKind {

            /// <summary>Value if the EdgeKind is AliasQualifiedNameSyntax_Alias.</summary>
            edkAliasQualifiedNameSyntax_Alias,

            /// <summary>Value if the EdgeKind is AliasQualifiedNameSyntax_Name.</summary>
            edkAliasQualifiedNameSyntax_Name,

            /// <summary>Value if the EdgeKind is AnonymousFunctionExpressionSyntax_Body.</summary>
            edkAnonymousFunctionExpressionSyntax_Body,

            /// <summary>Value if the EdgeKind is AnonymousMethodExpressionSyntax_ParameterList.</summary>
            edkAnonymousMethodExpressionSyntax_ParameterList,

            /// <summary>Value if the EdgeKind is AnonymousObjectCreationExpressionSyntax_Initializers.</summary>
            edkAnonymousObjectCreationExpressionSyntax_Initializers,

            /// <summary>Value if the EdgeKind is ArrayCreationExpressionSyntax_Initializer.</summary>
            edkArrayCreationExpressionSyntax_Initializer,

            /// <summary>Value if the EdgeKind is ArrayCreationExpressionSyntax_Type.</summary>
            edkArrayCreationExpressionSyntax_Type,

            /// <summary>Value if the EdgeKind is ArrayTypeSyntax_ElementType.</summary>
            edkArrayTypeSyntax_ElementType,

            /// <summary>Value if the EdgeKind is ArrayTypeSyntax_RankSpecifiers.</summary>
            edkArrayTypeSyntax_RankSpecifiers,

            /// <summary>Value if the EdgeKind is AssignmentExpressionSyntax_EventAccessorCall.</summary>
            edkAssignmentExpressionSyntax_EventAccessorCall,

            /// <summary>Value if the EdgeKind is AssignmentExpressionSyntax_Left.</summary>
            edkAssignmentExpressionSyntax_Left,

            /// <summary>Value if the EdgeKind is AssignmentExpressionSyntax_OverloadedOperatorCall.</summary>
            edkAssignmentExpressionSyntax_OverloadedOperatorCall,

            /// <summary>Value if the EdgeKind is AssignmentExpressionSyntax_Right.</summary>
            edkAssignmentExpressionSyntax_Right,

            /// <summary>Value if the EdgeKind is AwaitExpressionSyntax_Expression.</summary>
            edkAwaitExpressionSyntax_Expression,

            /// <summary>Value if the EdgeKind is BinaryExpressionSyntax_Left.</summary>
            edkBinaryExpressionSyntax_Left,

            /// <summary>Value if the EdgeKind is BinaryExpressionSyntax_OverloadedOperatorCall.</summary>
            edkBinaryExpressionSyntax_OverloadedOperatorCall,

            /// <summary>Value if the EdgeKind is BinaryExpressionSyntax_Right.</summary>
            edkBinaryExpressionSyntax_Right,

            /// <summary>Value if the EdgeKind is CastExpressionSyntax_ConversionOperatorCall.</summary>
            edkCastExpressionSyntax_ConversionOperatorCall,

            /// <summary>Value if the EdgeKind is CastExpressionSyntax_Expression.</summary>
            edkCastExpressionSyntax_Expression,

            /// <summary>Value if the EdgeKind is CastExpressionSyntax_Type.</summary>
            edkCastExpressionSyntax_Type,

            /// <summary>Value if the EdgeKind is CheckedExpressionSyntax_Expression.</summary>
            edkCheckedExpressionSyntax_Expression,

            /// <summary>Value if the EdgeKind is ConditionalAccessExpressionSyntax_Expression.</summary>
            edkConditionalAccessExpressionSyntax_Expression,

            /// <summary>Value if the EdgeKind is ConditionalAccessExpressionSyntax_WhenNotNull.</summary>
            edkConditionalAccessExpressionSyntax_WhenNotNull,

            /// <summary>Value if the EdgeKind is ConditionalExpressionSyntax_Condition.</summary>
            edkConditionalExpressionSyntax_Condition,

            /// <summary>Value if the EdgeKind is ConditionalExpressionSyntax_WhenFalse.</summary>
            edkConditionalExpressionSyntax_WhenFalse,

            /// <summary>Value if the EdgeKind is ConditionalExpressionSyntax_WhenTrue.</summary>
            edkConditionalExpressionSyntax_WhenTrue,

            /// <summary>Value if the EdgeKind is DefaultExpressionSyntax_Type.</summary>
            edkDefaultExpressionSyntax_Type,

            /// <summary>Value if the EdgeKind is ElementAccessExpressionSyntax_AccessorCall.</summary>
            edkElementAccessExpressionSyntax_AccessorCall,

            /// <summary>Value if the EdgeKind is ElementAccessExpressionSyntax_ArgumentList.</summary>
            edkElementAccessExpressionSyntax_ArgumentList,

            /// <summary>Value if the EdgeKind is ElementAccessExpressionSyntax_Expression.</summary>
            edkElementAccessExpressionSyntax_Expression,

            /// <summary>Value if the EdgeKind is ElementBindingExpressionSyntax_ArgumentList.</summary>
            edkElementBindingExpressionSyntax_ArgumentList,

            /// <summary>Value if the EdgeKind is GenericNameSyntax_TypeArgumentList.</summary>
            edkGenericNameSyntax_TypeArgumentList,

            /// <summary>Value if the EdgeKind is IdentifierNameSyntax_AccessorCall.</summary>
            edkIdentifierNameSyntax_AccessorCall,

            /// <summary>Value if the EdgeKind is IdentifierNameSyntax_Declaration.</summary>
            edkIdentifierNameSyntax_Declaration,

            /// <summary>Value if the EdgeKind is ImplicitArrayCreationExpressionSyntax_Initializer.</summary>
            edkImplicitArrayCreationExpressionSyntax_Initializer,

            /// <summary>Value if the EdgeKind is ImplicitElementAccessSyntax_ArgumentList.</summary>
            edkImplicitElementAccessSyntax_ArgumentList,

            /// <summary>Value if the EdgeKind is InitializerExpressionSyntax_Expressions.</summary>
            edkInitializerExpressionSyntax_Expressions,

            /// <summary>Value if the EdgeKind is InterpolatedStringExpressionSyntax_Contents.</summary>
            edkInterpolatedStringExpressionSyntax_Contents,

            /// <summary>Value if the EdgeKind is InvocationExpressionSyntax_ArgumentList.</summary>
            edkInvocationExpressionSyntax_ArgumentList,

            /// <summary>Value if the EdgeKind is InvocationExpressionSyntax_Expression.</summary>
            edkInvocationExpressionSyntax_Expression,

            /// <summary>Value if the EdgeKind is InvocationExpressionSyntax_MethodCall.</summary>
            edkInvocationExpressionSyntax_MethodCall,

            /// <summary>Value if the EdgeKind is MakeRefExpressionSyntax_Expression.</summary>
            edkMakeRefExpressionSyntax_Expression,

            /// <summary>Value if the EdgeKind is MemberAccessExpressionSyntax_Expression.</summary>
            edkMemberAccessExpressionSyntax_Expression,

            /// <summary>Value if the EdgeKind is MemberAccessExpressionSyntax_Name.</summary>
            edkMemberAccessExpressionSyntax_Name,

            /// <summary>Value if the EdgeKind is MemberBindingExpressionSyntax_Name.</summary>
            edkMemberBindingExpressionSyntax_Name,

            /// <summary>Value if the EdgeKind is NullableTypeSyntax_ElementType.</summary>
            edkNullableTypeSyntax_ElementType,

            /// <summary>Value if the EdgeKind is ObjectCreationExpressionSyntax_ArgumentList.</summary>
            edkObjectCreationExpressionSyntax_ArgumentList,

            /// <summary>Value if the EdgeKind is ObjectCreationExpressionSyntax_ConstructorCall.</summary>
            edkObjectCreationExpressionSyntax_ConstructorCall,

            /// <summary>Value if the EdgeKind is ObjectCreationExpressionSyntax_Initializer.</summary>
            edkObjectCreationExpressionSyntax_Initializer,

            /// <summary>Value if the EdgeKind is ObjectCreationExpressionSyntax_Type.</summary>
            edkObjectCreationExpressionSyntax_Type,

            /// <summary>Value if the EdgeKind is ParenthesizedExpressionSyntax_Expression.</summary>
            edkParenthesizedExpressionSyntax_Expression,

            /// <summary>Value if the EdgeKind is ParenthesizedLambdaExpressionSyntax_ParameterList.</summary>
            edkParenthesizedLambdaExpressionSyntax_ParameterList,

            /// <summary>Value if the EdgeKind is PointerTypeSyntax_ElementType.</summary>
            edkPointerTypeSyntax_ElementType,

            /// <summary>Value if the EdgeKind is PostfixUnaryExpressionSyntax_Operand.</summary>
            edkPostfixUnaryExpressionSyntax_Operand,

            /// <summary>Value if the EdgeKind is PostfixUnaryExpressionSyntax_OverloadedOperatorCall.</summary>
            edkPostfixUnaryExpressionSyntax_OverloadedOperatorCall,

            /// <summary>Value if the EdgeKind is PrefixUnaryExpressionSyntax_Operand.</summary>
            edkPrefixUnaryExpressionSyntax_Operand,

            /// <summary>Value if the EdgeKind is PrefixUnaryExpressionSyntax_OverloadedOperatorCall.</summary>
            edkPrefixUnaryExpressionSyntax_OverloadedOperatorCall,

            /// <summary>Value if the EdgeKind is QualifiedNameSyntax_Left.</summary>
            edkQualifiedNameSyntax_Left,

            /// <summary>Value if the EdgeKind is QualifiedNameSyntax_Right.</summary>
            edkQualifiedNameSyntax_Right,

            /// <summary>Value if the EdgeKind is QueryExpressionSyntax_Body.</summary>
            edkQueryExpressionSyntax_Body,

            /// <summary>Value if the EdgeKind is QueryExpressionSyntax_FromClause.</summary>
            edkQueryExpressionSyntax_FromClause,

            /// <summary>Value if the EdgeKind is RefTypeExpressionSyntax_Expression.</summary>
            edkRefTypeExpressionSyntax_Expression,

            /// <summary>Value if the EdgeKind is RefValueExpressionSyntax_Expression.</summary>
            edkRefValueExpressionSyntax_Expression,

            /// <summary>Value if the EdgeKind is RefValueExpressionSyntax_Type.</summary>
            edkRefValueExpressionSyntax_Type,

            /// <summary>Value if the EdgeKind is SimpleLambdaExpressionSyntax_Parameter.</summary>
            edkSimpleLambdaExpressionSyntax_Parameter,

            /// <summary>Value if the EdgeKind is SizeOfExpressionSyntax_Type.</summary>
            edkSizeOfExpressionSyntax_Type,

            /// <summary>Value if the EdgeKind is StackAllocArrayCreationExpressionSyntax_Type.</summary>
            edkStackAllocArrayCreationExpressionSyntax_Type,

            /// <summary>Value if the EdgeKind is TypeOfExpressionSyntax_Type.</summary>
            edkTypeOfExpressionSyntax_Type,

            /// <summary>Value if the EdgeKind is TypeSyntax_OriginalDefinition.</summary>
            edkTypeSyntax_OriginalDefinition,

            /// <summary>Value if the EdgeKind is BlockSyntax_Statements.</summary>
            edkBlockSyntax_Statements,

            /// <summary>Value if the EdgeKind is CheckedStatementSyntax_Block.</summary>
            edkCheckedStatementSyntax_Block,

            /// <summary>Value if the EdgeKind is DoStatementSyntax_Condition.</summary>
            edkDoStatementSyntax_Condition,

            /// <summary>Value if the EdgeKind is DoStatementSyntax_Statement.</summary>
            edkDoStatementSyntax_Statement,

            /// <summary>Value if the EdgeKind is ExpressionStatementSyntax_Expression.</summary>
            edkExpressionStatementSyntax_Expression,

            /// <summary>Value if the EdgeKind is FixedStatementSyntax_Declaration.</summary>
            edkFixedStatementSyntax_Declaration,

            /// <summary>Value if the EdgeKind is FixedStatementSyntax_Statement.</summary>
            edkFixedStatementSyntax_Statement,

            /// <summary>Value if the EdgeKind is ForEachStatementSyntax_Expression.</summary>
            edkForEachStatementSyntax_Expression,

            /// <summary>Value if the EdgeKind is ForEachStatementSyntax_Statement.</summary>
            edkForEachStatementSyntax_Statement,

            /// <summary>Value if the EdgeKind is ForEachStatementSyntax_Type.</summary>
            edkForEachStatementSyntax_Type,

            /// <summary>Value if the EdgeKind is ForStatementSyntax_Condition.</summary>
            edkForStatementSyntax_Condition,

            /// <summary>Value if the EdgeKind is ForStatementSyntax_Declaration.</summary>
            edkForStatementSyntax_Declaration,

            /// <summary>Value if the EdgeKind is ForStatementSyntax_Incrementors.</summary>
            edkForStatementSyntax_Incrementors,

            /// <summary>Value if the EdgeKind is ForStatementSyntax_Initializers.</summary>
            edkForStatementSyntax_Initializers,

            /// <summary>Value if the EdgeKind is ForStatementSyntax_Statement.</summary>
            edkForStatementSyntax_Statement,

            /// <summary>Value if the EdgeKind is GotoStatementSyntax_Expression.</summary>
            edkGotoStatementSyntax_Expression,

            /// <summary>Value if the EdgeKind is IfStatementSyntax_Condition.</summary>
            edkIfStatementSyntax_Condition,

            /// <summary>Value if the EdgeKind is IfStatementSyntax_Else.</summary>
            edkIfStatementSyntax_Else,

            /// <summary>Value if the EdgeKind is IfStatementSyntax_Statement.</summary>
            edkIfStatementSyntax_Statement,

            /// <summary>Value if the EdgeKind is LabeledStatementSyntax_Statement.</summary>
            edkLabeledStatementSyntax_Statement,

            /// <summary>Value if the EdgeKind is LocalDeclarationStatementSyntax_Declaration.</summary>
            edkLocalDeclarationStatementSyntax_Declaration,

            /// <summary>Value if the EdgeKind is LockStatementSyntax_Expression.</summary>
            edkLockStatementSyntax_Expression,

            /// <summary>Value if the EdgeKind is LockStatementSyntax_Statement.</summary>
            edkLockStatementSyntax_Statement,

            /// <summary>Value if the EdgeKind is ReturnStatementSyntax_Expression.</summary>
            edkReturnStatementSyntax_Expression,

            /// <summary>Value if the EdgeKind is SwitchStatementSyntax_Expression.</summary>
            edkSwitchStatementSyntax_Expression,

            /// <summary>Value if the EdgeKind is SwitchStatementSyntax_Sections.</summary>
            edkSwitchStatementSyntax_Sections,

            /// <summary>Value if the EdgeKind is ThrowStatementSyntax_Expression.</summary>
            edkThrowStatementSyntax_Expression,

            /// <summary>Value if the EdgeKind is TryStatementSyntax_Block.</summary>
            edkTryStatementSyntax_Block,

            /// <summary>Value if the EdgeKind is TryStatementSyntax_Catches.</summary>
            edkTryStatementSyntax_Catches,

            /// <summary>Value if the EdgeKind is TryStatementSyntax_Finally.</summary>
            edkTryStatementSyntax_Finally,

            /// <summary>Value if the EdgeKind is UnsafeStatementSyntax_Block.</summary>
            edkUnsafeStatementSyntax_Block,

            /// <summary>Value if the EdgeKind is UsingStatementSyntax_Declaration.</summary>
            edkUsingStatementSyntax_Declaration,

            /// <summary>Value if the EdgeKind is UsingStatementSyntax_Expression.</summary>
            edkUsingStatementSyntax_Expression,

            /// <summary>Value if the EdgeKind is UsingStatementSyntax_Statement.</summary>
            edkUsingStatementSyntax_Statement,

            /// <summary>Value if the EdgeKind is WhileStatementSyntax_Condition.</summary>
            edkWhileStatementSyntax_Condition,

            /// <summary>Value if the EdgeKind is WhileStatementSyntax_Statement.</summary>
            edkWhileStatementSyntax_Statement,

            /// <summary>Value if the EdgeKind is YieldStatementSyntax_Expression.</summary>
            edkYieldStatementSyntax_Expression,

            /// <summary>Value if the EdgeKind is AccessorDeclarationSyntax_AttributeLists.</summary>
            edkAccessorDeclarationSyntax_AttributeLists,

            /// <summary>Value if the EdgeKind is AccessorDeclarationSyntax_Body.</summary>
            edkAccessorDeclarationSyntax_Body,

            /// <summary>Value if the EdgeKind is AccessorListSyntax_Accessors.</summary>
            edkAccessorListSyntax_Accessors,

            /// <summary>Value if the EdgeKind is AnonymousObjectMemberDeclaratorSyntax_Expression.</summary>
            edkAnonymousObjectMemberDeclaratorSyntax_Expression,

            /// <summary>Value if the EdgeKind is AnonymousObjectMemberDeclaratorSyntax_NameEquals.</summary>
            edkAnonymousObjectMemberDeclaratorSyntax_NameEquals,

            /// <summary>Value if the EdgeKind is ArgumentSyntax_Expression.</summary>
            edkArgumentSyntax_Expression,

            /// <summary>Value if the EdgeKind is ArgumentSyntax_NameColon.</summary>
            edkArgumentSyntax_NameColon,

            /// <summary>Value if the EdgeKind is ArrayRankSpecifierSyntax_Sizes.</summary>
            edkArrayRankSpecifierSyntax_Sizes,

            /// <summary>Value if the EdgeKind is ArrowExpressionClauseSyntax_Expression.</summary>
            edkArrowExpressionClauseSyntax_Expression,

            /// <summary>Value if the EdgeKind is AttributeArgumentListSyntax_Arguments.</summary>
            edkAttributeArgumentListSyntax_Arguments,

            /// <summary>Value if the EdgeKind is AttributeArgumentSyntax_Expression.</summary>
            edkAttributeArgumentSyntax_Expression,

            /// <summary>Value if the EdgeKind is AttributeArgumentSyntax_NameColon.</summary>
            edkAttributeArgumentSyntax_NameColon,

            /// <summary>Value if the EdgeKind is AttributeArgumentSyntax_NameEquals.</summary>
            edkAttributeArgumentSyntax_NameEquals,

            /// <summary>Value if the EdgeKind is AttributeListSyntax_Attributes.</summary>
            edkAttributeListSyntax_Attributes,

            /// <summary>Value if the EdgeKind is AttributeListSyntax_Target.</summary>
            edkAttributeListSyntax_Target,

            /// <summary>Value if the EdgeKind is AttributeSyntax_ArgumentList.</summary>
            edkAttributeSyntax_ArgumentList,

            /// <summary>Value if the EdgeKind is AttributeSyntax_Name.</summary>
            edkAttributeSyntax_Name,

            /// <summary>Value if the EdgeKind is BaseArgumentListSyntax_Arguments.</summary>
            edkBaseArgumentListSyntax_Arguments,

            /// <summary>Value if the EdgeKind is BaseCrefParameterListSyntax_Parameters.</summary>
            edkBaseCrefParameterListSyntax_Parameters,

            /// <summary>Value if the EdgeKind is BaseFieldDeclarationSyntax_AttributeLists.</summary>
            edkBaseFieldDeclarationSyntax_AttributeLists,

            /// <summary>Value if the EdgeKind is BaseFieldDeclarationSyntax_Declaration.</summary>
            edkBaseFieldDeclarationSyntax_Declaration,

            /// <summary>Value if the EdgeKind is BaseListSyntax_Types.</summary>
            edkBaseListSyntax_Types,

            /// <summary>Value if the EdgeKind is BaseMethodDeclarationSyntax_AccessedEnumMembers.</summary>
            edkBaseMethodDeclarationSyntax_AccessedEnumMembers,

            /// <summary>Value if the EdgeKind is BaseMethodDeclarationSyntax_AttributeLists.</summary>
            edkBaseMethodDeclarationSyntax_AttributeLists,

            /// <summary>Value if the EdgeKind is BaseMethodDeclarationSyntax_Body.</summary>
            edkBaseMethodDeclarationSyntax_Body,

            /// <summary>Value if the EdgeKind is BaseMethodDeclarationSyntax_ParameterList.</summary>
            edkBaseMethodDeclarationSyntax_ParameterList,

            /// <summary>Value if the EdgeKind is BaseParameterListSyntax_Parameters.</summary>
            edkBaseParameterListSyntax_Parameters,

            /// <summary>Value if the EdgeKind is BasePropertyDeclarationSyntax_AccessorList.</summary>
            edkBasePropertyDeclarationSyntax_AccessorList,

            /// <summary>Value if the EdgeKind is BasePropertyDeclarationSyntax_AttributeLists.</summary>
            edkBasePropertyDeclarationSyntax_AttributeLists,

            /// <summary>Value if the EdgeKind is BasePropertyDeclarationSyntax_ExplicitInterfaceSpecifier.</summary>
            edkBasePropertyDeclarationSyntax_ExplicitInterfaceSpecifier,

            /// <summary>Value if the EdgeKind is BasePropertyDeclarationSyntax_Type.</summary>
            edkBasePropertyDeclarationSyntax_Type,

            /// <summary>Value if the EdgeKind is BaseTypeDeclarationSyntax_AttributeLists.</summary>
            edkBaseTypeDeclarationSyntax_AttributeLists,

            /// <summary>Value if the EdgeKind is BaseTypeDeclarationSyntax_BaseList.</summary>
            edkBaseTypeDeclarationSyntax_BaseList,

            /// <summary>Value if the EdgeKind is BaseTypeSyntax_Type.</summary>
            edkBaseTypeSyntax_Type,

            /// <summary>Value if the EdgeKind is CaseSwitchLabelSyntax_Value.</summary>
            edkCaseSwitchLabelSyntax_Value,

            /// <summary>Value if the EdgeKind is CatchClauseSyntax_Block.</summary>
            edkCatchClauseSyntax_Block,

            /// <summary>Value if the EdgeKind is CatchClauseSyntax_Declaration.</summary>
            edkCatchClauseSyntax_Declaration,

            /// <summary>Value if the EdgeKind is CatchClauseSyntax_Filter.</summary>
            edkCatchClauseSyntax_Filter,

            /// <summary>Value if the EdgeKind is CatchDeclarationSyntax_Type.</summary>
            edkCatchDeclarationSyntax_Type,

            /// <summary>Value if the EdgeKind is CatchFilterClauseSyntax_FilterExpression.</summary>
            edkCatchFilterClauseSyntax_FilterExpression,

            /// <summary>Value if the EdgeKind is CompilationUnitSyntax_AttributeLists.</summary>
            edkCompilationUnitSyntax_AttributeLists,

            /// <summary>Value if the EdgeKind is CompilationUnitSyntax_Externs.</summary>
            edkCompilationUnitSyntax_Externs,

            /// <summary>Value if the EdgeKind is CompilationUnitSyntax_Members.</summary>
            edkCompilationUnitSyntax_Members,

            /// <summary>Value if the EdgeKind is CompilationUnitSyntax_Usings.</summary>
            edkCompilationUnitSyntax_Usings,

            /// <summary>Value if the EdgeKind is ConstructorDeclarationSyntax_Initializer.</summary>
            edkConstructorDeclarationSyntax_Initializer,

            /// <summary>Value if the EdgeKind is ConstructorInitializerSyntax_ArgumentList.</summary>
            edkConstructorInitializerSyntax_ArgumentList,

            /// <summary>Value if the EdgeKind is ConstructorInitializerSyntax_ConstructorCall.</summary>
            edkConstructorInitializerSyntax_ConstructorCall,

            /// <summary>Value if the EdgeKind is ConversionOperatorDeclarationSyntax_ExpressionBody.</summary>
            edkConversionOperatorDeclarationSyntax_ExpressionBody,

            /// <summary>Value if the EdgeKind is ConversionOperatorDeclarationSyntax_Type.</summary>
            edkConversionOperatorDeclarationSyntax_Type,

            /// <summary>Value if the EdgeKind is ConversionOperatorMemberCrefSyntax_Parameters.</summary>
            edkConversionOperatorMemberCrefSyntax_Parameters,

            /// <summary>Value if the EdgeKind is ConversionOperatorMemberCrefSyntax_Type.</summary>
            edkConversionOperatorMemberCrefSyntax_Type,

            /// <summary>Value if the EdgeKind is CrefParameterSyntax_Type.</summary>
            edkCrefParameterSyntax_Type,

            /// <summary>Value if the EdgeKind is DelegateDeclarationSyntax_AttributeLists.</summary>
            edkDelegateDeclarationSyntax_AttributeLists,

            /// <summary>Value if the EdgeKind is DelegateDeclarationSyntax_ConstraintClauses.</summary>
            edkDelegateDeclarationSyntax_ConstraintClauses,

            /// <summary>Value if the EdgeKind is DelegateDeclarationSyntax_ParameterList.</summary>
            edkDelegateDeclarationSyntax_ParameterList,

            /// <summary>Value if the EdgeKind is DelegateDeclarationSyntax_ReturnType.</summary>
            edkDelegateDeclarationSyntax_ReturnType,

            /// <summary>Value if the EdgeKind is ElseClauseSyntax_Statement.</summary>
            edkElseClauseSyntax_Statement,

            /// <summary>Value if the EdgeKind is EnumDeclarationSyntax_Members.</summary>
            edkEnumDeclarationSyntax_Members,

            /// <summary>Value if the EdgeKind is EnumMemberDeclarationSyntax_AttributeLists.</summary>
            edkEnumMemberDeclarationSyntax_AttributeLists,

            /// <summary>Value if the EdgeKind is EnumMemberDeclarationSyntax_EqualsValue.</summary>
            edkEnumMemberDeclarationSyntax_EqualsValue,

            /// <summary>Value if the EdgeKind is EqualsValueClauseSyntax_Value.</summary>
            edkEqualsValueClauseSyntax_Value,

            /// <summary>Value if the EdgeKind is ExplicitInterfaceSpecifierSyntax_Name.</summary>
            edkExplicitInterfaceSpecifierSyntax_Name,

            /// <summary>Value if the EdgeKind is FinallyClauseSyntax_Block.</summary>
            edkFinallyClauseSyntax_Block,

            /// <summary>Value if the EdgeKind is FromClauseSyntax_Expression.</summary>
            edkFromClauseSyntax_Expression,

            /// <summary>Value if the EdgeKind is FromClauseSyntax_Type.</summary>
            edkFromClauseSyntax_Type,

            /// <summary>Value if the EdgeKind is GlobalStatementSyntax_Statement.</summary>
            edkGlobalStatementSyntax_Statement,

            /// <summary>Value if the EdgeKind is GroupClauseSyntax_ByExpression.</summary>
            edkGroupClauseSyntax_ByExpression,

            /// <summary>Value if the EdgeKind is GroupClauseSyntax_GroupExpression.</summary>
            edkGroupClauseSyntax_GroupExpression,

            /// <summary>Value if the EdgeKind is IncompleteMemberSyntax_AttributeLists.</summary>
            edkIncompleteMemberSyntax_AttributeLists,

            /// <summary>Value if the EdgeKind is IncompleteMemberSyntax_Type.</summary>
            edkIncompleteMemberSyntax_Type,

            /// <summary>Value if the EdgeKind is IndexerDeclarationSyntax_ExpressionBody.</summary>
            edkIndexerDeclarationSyntax_ExpressionBody,

            /// <summary>Value if the EdgeKind is IndexerDeclarationSyntax_ParameterList.</summary>
            edkIndexerDeclarationSyntax_ParameterList,

            /// <summary>Value if the EdgeKind is IndexerMemberCrefSyntax_Parameters.</summary>
            edkIndexerMemberCrefSyntax_Parameters,

            /// <summary>Value if the EdgeKind is InterpolationAlignmentClauseSyntax_Value.</summary>
            edkInterpolationAlignmentClauseSyntax_Value,

            /// <summary>Value if the EdgeKind is InterpolationSyntax_AlignmentClause.</summary>
            edkInterpolationSyntax_AlignmentClause,

            /// <summary>Value if the EdgeKind is InterpolationSyntax_Expression.</summary>
            edkInterpolationSyntax_Expression,

            /// <summary>Value if the EdgeKind is InterpolationSyntax_FormatClause.</summary>
            edkInterpolationSyntax_FormatClause,

            /// <summary>Value if the EdgeKind is JoinClauseSyntax_InExpression.</summary>
            edkJoinClauseSyntax_InExpression,

            /// <summary>Value if the EdgeKind is JoinClauseSyntax_Into.</summary>
            edkJoinClauseSyntax_Into,

            /// <summary>Value if the EdgeKind is JoinClauseSyntax_LeftExpression.</summary>
            edkJoinClauseSyntax_LeftExpression,

            /// <summary>Value if the EdgeKind is JoinClauseSyntax_RightExpression.</summary>
            edkJoinClauseSyntax_RightExpression,

            /// <summary>Value if the EdgeKind is JoinClauseSyntax_Type.</summary>
            edkJoinClauseSyntax_Type,

            /// <summary>Value if the EdgeKind is LetClauseSyntax_Expression.</summary>
            edkLetClauseSyntax_Expression,

            /// <summary>Value if the EdgeKind is MethodDeclarationSyntax_ConstraintClauses.</summary>
            edkMethodDeclarationSyntax_ConstraintClauses,

            /// <summary>Value if the EdgeKind is MethodDeclarationSyntax_ExplicitInterfaceSpecifier.</summary>
            edkMethodDeclarationSyntax_ExplicitInterfaceSpecifier,

            /// <summary>Value if the EdgeKind is MethodDeclarationSyntax_ExpressionBody.</summary>
            edkMethodDeclarationSyntax_ExpressionBody,

            /// <summary>Value if the EdgeKind is MethodDeclarationSyntax_ReturnType.</summary>
            edkMethodDeclarationSyntax_ReturnType,

            /// <summary>Value if the EdgeKind is NameColonSyntax_Name.</summary>
            edkNameColonSyntax_Name,

            /// <summary>Value if the EdgeKind is NameEqualsSyntax_Name.</summary>
            edkNameEqualsSyntax_Name,

            /// <summary>Value if the EdgeKind is NameMemberCrefSyntax_Name.</summary>
            edkNameMemberCrefSyntax_Name,

            /// <summary>Value if the EdgeKind is NameMemberCrefSyntax_Parameters.</summary>
            edkNameMemberCrefSyntax_Parameters,

            /// <summary>Value if the EdgeKind is NamespaceDeclarationSyntax_Externs.</summary>
            edkNamespaceDeclarationSyntax_Externs,

            /// <summary>Value if the EdgeKind is NamespaceDeclarationSyntax_Members.</summary>
            edkNamespaceDeclarationSyntax_Members,

            /// <summary>Value if the EdgeKind is NamespaceDeclarationSyntax_Name.</summary>
            edkNamespaceDeclarationSyntax_Name,

            /// <summary>Value if the EdgeKind is NamespaceDeclarationSyntax_Usings.</summary>
            edkNamespaceDeclarationSyntax_Usings,

            /// <summary>Value if the EdgeKind is OperatorDeclarationSyntax_ExpressionBody.</summary>
            edkOperatorDeclarationSyntax_ExpressionBody,

            /// <summary>Value if the EdgeKind is OperatorDeclarationSyntax_ReturnType.</summary>
            edkOperatorDeclarationSyntax_ReturnType,

            /// <summary>Value if the EdgeKind is OperatorMemberCrefSyntax_Parameters.</summary>
            edkOperatorMemberCrefSyntax_Parameters,

            /// <summary>Value if the EdgeKind is OrderByClauseSyntax_Orderings.</summary>
            edkOrderByClauseSyntax_Orderings,

            /// <summary>Value if the EdgeKind is OrderingSyntax_Expression.</summary>
            edkOrderingSyntax_Expression,

            /// <summary>Value if the EdgeKind is ParameterSyntax_AttributeLists.</summary>
            edkParameterSyntax_AttributeLists,

            /// <summary>Value if the EdgeKind is ParameterSyntax_Default.</summary>
            edkParameterSyntax_Default,

            /// <summary>Value if the EdgeKind is ParameterSyntax_Type.</summary>
            edkParameterSyntax_Type,

            /// <summary>Value if the EdgeKind is PropertyDeclarationSyntax_ExpressionBody.</summary>
            edkPropertyDeclarationSyntax_ExpressionBody,

            /// <summary>Value if the EdgeKind is PropertyDeclarationSyntax_Initializer.</summary>
            edkPropertyDeclarationSyntax_Initializer,

            /// <summary>Value if the EdgeKind is QualifiedCrefSyntax_Container.</summary>
            edkQualifiedCrefSyntax_Container,

            /// <summary>Value if the EdgeKind is QualifiedCrefSyntax_Member.</summary>
            edkQualifiedCrefSyntax_Member,

            /// <summary>Value if the EdgeKind is QueryBodySyntax_Clauses.</summary>
            edkQueryBodySyntax_Clauses,

            /// <summary>Value if the EdgeKind is QueryBodySyntax_Continuation.</summary>
            edkQueryBodySyntax_Continuation,

            /// <summary>Value if the EdgeKind is QueryBodySyntax_SelectOrGroup.</summary>
            edkQueryBodySyntax_SelectOrGroup,

            /// <summary>Value if the EdgeKind is QueryContinuationSyntax_Body.</summary>
            edkQueryContinuationSyntax_Body,

            /// <summary>Value if the EdgeKind is SelectClauseSyntax_Expression.</summary>
            edkSelectClauseSyntax_Expression,

            /// <summary>Value if the EdgeKind is SwitchSectionSyntax_Labels.</summary>
            edkSwitchSectionSyntax_Labels,

            /// <summary>Value if the EdgeKind is SwitchSectionSyntax_Statements.</summary>
            edkSwitchSectionSyntax_Statements,

            /// <summary>Value if the EdgeKind is TypeArgumentListSyntax_Arguments.</summary>
            edkTypeArgumentListSyntax_Arguments,

            /// <summary>Value if the EdgeKind is TypeConstraintSyntax_Type.</summary>
            edkTypeConstraintSyntax_Type,

            /// <summary>Value if the EdgeKind is TypeCrefSyntax_Type.</summary>
            edkTypeCrefSyntax_Type,

            /// <summary>Value if the EdgeKind is TypeDeclarationSyntax_ConstraintClauses.</summary>
            edkTypeDeclarationSyntax_ConstraintClauses,

            /// <summary>Value if the EdgeKind is TypeDeclarationSyntax_Members.</summary>
            edkTypeDeclarationSyntax_Members,

            /// <summary>Value if the EdgeKind is TypeDeclarationSyntax_TypeParameterList.</summary>
            edkTypeDeclarationSyntax_TypeParameterList,

            /// <summary>Value if the EdgeKind is TypeParameterConstraintClauseSyntax_Constraints.</summary>
            edkTypeParameterConstraintClauseSyntax_Constraints,

            /// <summary>Value if the EdgeKind is TypeParameterConstraintClauseSyntax_Name.</summary>
            edkTypeParameterConstraintClauseSyntax_Name,

            /// <summary>Value if the EdgeKind is TypeParameterListSyntax_Parameters.</summary>
            edkTypeParameterListSyntax_Parameters,

            /// <summary>Value if the EdgeKind is TypeParameterSyntax_AttributeLists.</summary>
            edkTypeParameterSyntax_AttributeLists,

            /// <summary>Value if the EdgeKind is UsingDirectiveSyntax_Alias.</summary>
            edkUsingDirectiveSyntax_Alias,

            /// <summary>Value if the EdgeKind is UsingDirectiveSyntax_Name.</summary>
            edkUsingDirectiveSyntax_Name,

            /// <summary>Value if the EdgeKind is VariableDeclarationSyntax_Type.</summary>
            edkVariableDeclarationSyntax_Type,

            /// <summary>Value if the EdgeKind is VariableDeclarationSyntax_Variables.</summary>
            edkVariableDeclarationSyntax_Variables,

            /// <summary>Value if the EdgeKind is VariableDeclaratorSyntax_ArgumentList.</summary>
            edkVariableDeclaratorSyntax_ArgumentList,

            /// <summary>Value if the EdgeKind is VariableDeclaratorSyntax_Initializer.</summary>
            edkVariableDeclaratorSyntax_Initializer,

            /// <summary>Value if the EdgeKind is WhereClauseSyntax_Condition.</summary>
            edkWhereClauseSyntax_Condition,

            /// <summary>Value if the EdgeKind is XmlAttributeSyntax_Name.</summary>
            edkXmlAttributeSyntax_Name,

            /// <summary>Value if the EdgeKind is XmlCrefAttributeSyntax_Cref.</summary>
            edkXmlCrefAttributeSyntax_Cref,

            /// <summary>Value if the EdgeKind is XmlElementEndTagSyntax_Name.</summary>
            edkXmlElementEndTagSyntax_Name,

            /// <summary>Value if the EdgeKind is XmlElementStartTagSyntax_Attributes.</summary>
            edkXmlElementStartTagSyntax_Attributes,

            /// <summary>Value if the EdgeKind is XmlElementStartTagSyntax_Name.</summary>
            edkXmlElementStartTagSyntax_Name,

            /// <summary>Value if the EdgeKind is XmlElementSyntax_Content.</summary>
            edkXmlElementSyntax_Content,

            /// <summary>Value if the EdgeKind is XmlElementSyntax_EndTag.</summary>
            edkXmlElementSyntax_EndTag,

            /// <summary>Value if the EdgeKind is XmlElementSyntax_StartTag.</summary>
            edkXmlElementSyntax_StartTag,

            /// <summary>Value if the EdgeKind is XmlEmptyElementSyntax_Attributes.</summary>
            edkXmlEmptyElementSyntax_Attributes,

            /// <summary>Value if the EdgeKind is XmlEmptyElementSyntax_Name.</summary>
            edkXmlEmptyElementSyntax_Name,

            /// <summary>Value if the EdgeKind is XmlNameAttributeSyntax_Identifier.</summary>
            edkXmlNameAttributeSyntax_Identifier,

            /// <summary>Value if the EdgeKind is XmlNameSyntax_Prefix.</summary>
            edkXmlNameSyntax_Prefix,

            /// <summary>Value if the EdgeKind is XmlProcessingInstructionSyntax_Name.</summary>
            edkXmlProcessingInstructionSyntax_Name

        }

    }

}
