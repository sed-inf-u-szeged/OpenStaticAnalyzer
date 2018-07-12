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

using System.Collections.Generic;

namespace Columbus.CSAN
{
    using CSHARP = Csharp.Asg;
    using ROSLYNCS = Microsoft.CodeAnalysis.CSharp;

    class NodeBuilder : ROSLYNCS.CSharpSyntaxWalker
    {
        public CSHARP.Factory Factory;
        public Dictionary<ROSLYNCS.CSharpSyntaxNode, uint> Map;

        public NodeBuilder(CSHARP.Factory fact, Dictionary<ROSLYNCS.CSharpSyntaxNode, uint> map)
        {
            Factory = fact;
            Map = map;
        }


        public override void VisitAccessorDeclaration(ROSLYNCS.Syntax.AccessorDeclarationSyntax node)
        {
            if (!Map.ContainsKey(node))
                Map.Add(node, Factory.createAccessorDeclarationSyntaxNode().Id);
            base.VisitAccessorDeclaration(node);
        }

        public override void VisitAccessorList(ROSLYNCS.Syntax.AccessorListSyntax node)
        {
            if (!Map.ContainsKey(node))
                Map.Add(node, Factory.createAccessorListSyntaxNode().Id);
            base.VisitAccessorList(node);
        }

        public override void VisitAliasQualifiedName(ROSLYNCS.Syntax.AliasQualifiedNameSyntax node)
        {
            if (!Map.ContainsKey(node))
                Map.Add(node, Factory.createAliasQualifiedNameSyntaxNode().Id);
            base.VisitAliasQualifiedName(node);
        }

        public override void VisitAnonymousMethodExpression(ROSLYNCS.Syntax.AnonymousMethodExpressionSyntax node)
        {
            if (!Map.ContainsKey(node))
                Map.Add(node, Factory.createAnonymousMethodExpressionSyntaxNode().Id);
            base.VisitAnonymousMethodExpression(node);
        }

        public override void VisitAnonymousObjectCreationExpression(ROSLYNCS.Syntax.AnonymousObjectCreationExpressionSyntax node)
        {
            if (!Map.ContainsKey(node))
                Map.Add(node, Factory.createAnonymousObjectCreationExpressionSyntaxNode().Id);
            base.VisitAnonymousObjectCreationExpression(node);
        }

        public override void VisitAnonymousObjectMemberDeclarator(ROSLYNCS.Syntax.AnonymousObjectMemberDeclaratorSyntax node)
        {
            if (!Map.ContainsKey(node))
                Map.Add(node, Factory.createAnonymousObjectMemberDeclaratorSyntaxNode().Id);
            base.VisitAnonymousObjectMemberDeclarator(node);
        }

        public override void VisitArgument(ROSLYNCS.Syntax.ArgumentSyntax node)
        {
            if (!Map.ContainsKey(node))
                Map.Add(node, Factory.createArgumentSyntaxNode().Id);
            base.VisitArgument(node);
        }

        public override void VisitArgumentList(ROSLYNCS.Syntax.ArgumentListSyntax node)
        {
            if (!Map.ContainsKey(node))
                Map.Add(node, Factory.createArgumentListSyntaxNode().Id);
            base.VisitArgumentList(node);
        }

        public override void VisitArrayCreationExpression(ROSLYNCS.Syntax.ArrayCreationExpressionSyntax node)
        {
            if (!Map.ContainsKey(node))
                Map.Add(node, Factory.createArrayCreationExpressionSyntaxNode().Id);
            base.VisitArrayCreationExpression(node);
        }

        public override void VisitArrayRankSpecifier(ROSLYNCS.Syntax.ArrayRankSpecifierSyntax node)
        {
            if (!Map.ContainsKey(node))
                Map.Add(node, Factory.createArrayRankSpecifierSyntaxNode().Id);
            base.VisitArrayRankSpecifier(node);
        }

        public override void VisitArrayType(ROSLYNCS.Syntax.ArrayTypeSyntax node)
        {
            if (!Map.ContainsKey(node))
                Map.Add(node, Factory.createArrayTypeSyntaxNode().Id);
            base.VisitArrayType(node);
        }

        public override void VisitArrowExpressionClause(ROSLYNCS.Syntax.ArrowExpressionClauseSyntax node)
        {
            if (!Map.ContainsKey(node))
                Map.Add(node, Factory.createArrowExpressionClauseSyntaxNode().Id);
            base.VisitArrowExpressionClause(node);
        }

        public override void VisitAssignmentExpression(ROSLYNCS.Syntax.AssignmentExpressionSyntax node)
        {
            if (!Map.ContainsKey(node))
                Map.Add(node, Factory.createAssignmentExpressionSyntaxNode().Id);
            base.VisitAssignmentExpression(node);
        }

        public override void VisitAttribute(ROSLYNCS.Syntax.AttributeSyntax node)
        {
            if (!Map.ContainsKey(node))
                Map.Add(node, Factory.createAttributeSyntaxNode().Id);
            base.VisitAttribute(node);
        }

        public override void VisitAttributeArgument(ROSLYNCS.Syntax.AttributeArgumentSyntax node)
        {
            if (!Map.ContainsKey(node))
                Map.Add(node, Factory.createAttributeArgumentSyntaxNode().Id);
            base.VisitAttributeArgument(node);
        }

        public override void VisitAttributeArgumentList(ROSLYNCS.Syntax.AttributeArgumentListSyntax node)
        {
            if (!Map.ContainsKey(node))
                Map.Add(node, Factory.createAttributeArgumentListSyntaxNode().Id);
            base.VisitAttributeArgumentList(node);
        }

        public override void VisitAttributeList(ROSLYNCS.Syntax.AttributeListSyntax node)
        {
            if (!Map.ContainsKey(node))
                Map.Add(node, Factory.createAttributeListSyntaxNode().Id);
            base.VisitAttributeList(node);
        }

        public override void VisitAttributeTargetSpecifier(ROSLYNCS.Syntax.AttributeTargetSpecifierSyntax node)
        {
            if (!Map.ContainsKey(node))
                Map.Add(node, Factory.createAttributeTargetSpecifierSyntaxNode().Id);
            base.VisitAttributeTargetSpecifier(node);
        }

        public override void VisitAwaitExpression(ROSLYNCS.Syntax.AwaitExpressionSyntax node)
        {
            if (!Map.ContainsKey(node))
                Map.Add(node, Factory.createAwaitExpressionSyntaxNode().Id);
            base.VisitAwaitExpression(node);
        }

        public override void VisitBaseExpression(ROSLYNCS.Syntax.BaseExpressionSyntax node)
        {
            if (!Map.ContainsKey(node))
                Map.Add(node, Factory.createBaseExpressionSyntaxNode().Id);
            base.VisitBaseExpression(node);
        }

        public override void VisitBaseList(ROSLYNCS.Syntax.BaseListSyntax node)
        {
            if (!Map.ContainsKey(node))
                Map.Add(node, Factory.createBaseListSyntaxNode().Id);
            base.VisitBaseList(node);
        }

        public override void VisitBinaryExpression(ROSLYNCS.Syntax.BinaryExpressionSyntax node)
        {
            if (!Map.ContainsKey(node))
                Map.Add(node, Factory.createBinaryExpressionSyntaxNode().Id);
            base.VisitBinaryExpression(node);
        }

        public override void VisitBlock(ROSLYNCS.Syntax.BlockSyntax node)
        {
            if (!Map.ContainsKey(node))
                Map.Add(node, Factory.createBlockSyntaxNode().Id);
            base.VisitBlock(node);
        }

        public override void VisitBracketedArgumentList(ROSLYNCS.Syntax.BracketedArgumentListSyntax node)
        {
            if (!Map.ContainsKey(node))
                Map.Add(node, Factory.createBracketedArgumentListSyntaxNode().Id);
            base.VisitBracketedArgumentList(node);
        }

        public override void VisitBracketedParameterList(ROSLYNCS.Syntax.BracketedParameterListSyntax node)
        {
            if (!Map.ContainsKey(node))
                Map.Add(node, Factory.createBracketedParameterListSyntaxNode().Id);
            base.VisitBracketedParameterList(node);
        }

        public override void VisitBreakStatement(ROSLYNCS.Syntax.BreakStatementSyntax node)
        {
            if (!Map.ContainsKey(node))
                Map.Add(node, Factory.createBreakStatementSyntaxNode().Id);
            base.VisitBreakStatement(node);
        }

        public override void VisitCaseSwitchLabel(ROSLYNCS.Syntax.CaseSwitchLabelSyntax node)
        {
            if (!Map.ContainsKey(node))
                Map.Add(node, Factory.createCaseSwitchLabelSyntaxNode().Id);
            base.VisitCaseSwitchLabel(node);
        }

        public override void VisitCastExpression(ROSLYNCS.Syntax.CastExpressionSyntax node)
        {
            if (!Map.ContainsKey(node))
                Map.Add(node, Factory.createCastExpressionSyntaxNode().Id);
            base.VisitCastExpression(node);
        }

        public override void VisitCatchClause(ROSLYNCS.Syntax.CatchClauseSyntax node)
        {
            if (!Map.ContainsKey(node))
                Map.Add(node, Factory.createCatchClauseSyntaxNode().Id);
            base.VisitCatchClause(node);
        }


        public override void VisitCatchDeclaration(ROSLYNCS.Syntax.CatchDeclarationSyntax node)
        {
            if (!Map.ContainsKey(node))
                Map.Add(node, Factory.createCatchDeclarationSyntaxNode().Id);
            base.VisitCatchDeclaration(node);
        }

        public override void VisitCatchFilterClause(ROSLYNCS.Syntax.CatchFilterClauseSyntax node)
        {
            if (!Map.ContainsKey(node))
                Map.Add(node, Factory.createCatchFilterClauseSyntaxNode().Id);
            base.VisitCatchFilterClause(node);
        }

        public override void VisitCheckedExpression(ROSLYNCS.Syntax.CheckedExpressionSyntax node)
        {
            if (!Map.ContainsKey(node))
                Map.Add(node, Factory.createCheckedExpressionSyntaxNode().Id);
            base.VisitCheckedExpression(node);
        }

        public override void VisitCheckedStatement(ROSLYNCS.Syntax.CheckedStatementSyntax node)
        {
            if (!Map.ContainsKey(node))
                Map.Add(node, Factory.createCheckedStatementSyntaxNode().Id);
            base.VisitCheckedStatement(node);
        }

        public override void VisitClassDeclaration(ROSLYNCS.Syntax.ClassDeclarationSyntax node)
        {
            if (!Map.ContainsKey(node))
                Map.Add(node, Factory.createClassDeclarationSyntaxNode().Id);
            base.VisitClassDeclaration(node);
        }

        public override void VisitClassOrStructConstraint(ROSLYNCS.Syntax.ClassOrStructConstraintSyntax node)
        {
            if (!Map.ContainsKey(node))
                Map.Add(node, Factory.createClassOrStructConstraintSyntaxNode().Id);
            base.VisitClassOrStructConstraint(node);
        }

        public override void VisitCompilationUnit(ROSLYNCS.Syntax.CompilationUnitSyntax node)
        {
            //A CompilationUnit with ID 100 exists by default in the Factory, use that first
            if (Map.Count == 0 && Factory.getRef(100) != null && Factory.getNodeKind(100) == CSHARP.Types.NodeKind.ndkCompilationUnitSyntax)
                Map.Add(node, 100);
            else
                Map.Add(node, Factory.createCompilationUnitSyntaxNode().Id);
            base.VisitCompilationUnit(node);
        }

        public override void VisitConditionalAccessExpression(ROSLYNCS.Syntax.ConditionalAccessExpressionSyntax node)
        {
            if (!Map.ContainsKey(node))
                Map.Add(node, Factory.createConditionalAccessExpressionSyntaxNode().Id);
            base.VisitConditionalAccessExpression(node);
        }

        public override void VisitConditionalExpression(ROSLYNCS.Syntax.ConditionalExpressionSyntax node)
        {
            if (!Map.ContainsKey(node))
                Map.Add(node, Factory.createConditionalExpressionSyntaxNode().Id);
            base.VisitConditionalExpression(node);
        }

        public override void VisitConstructorConstraint(ROSLYNCS.Syntax.ConstructorConstraintSyntax node)
        {
            if (!Map.ContainsKey(node))
                Map.Add(node, Factory.createConstructorConstraintSyntaxNode().Id);
            base.VisitConstructorConstraint(node);
        }

        public override void VisitConstructorDeclaration(ROSLYNCS.Syntax.ConstructorDeclarationSyntax node)
        {
            if (!Map.ContainsKey(node))
                Map.Add(node, Factory.createConstructorDeclarationSyntaxNode().Id);
            base.VisitConstructorDeclaration(node);
        }

        public override void VisitConstructorInitializer(ROSLYNCS.Syntax.ConstructorInitializerSyntax node)
        {
            if (!Map.ContainsKey(node))
                Map.Add(node, Factory.createConstructorInitializerSyntaxNode().Id);
            base.VisitConstructorInitializer(node);
        }

        public override void VisitContinueStatement(ROSLYNCS.Syntax.ContinueStatementSyntax node)
        {
            if (!Map.ContainsKey(node))
                Map.Add(node, Factory.createContinueStatementSyntaxNode().Id);
            base.VisitContinueStatement(node);
        }

        public override void VisitConversionOperatorDeclaration(ROSLYNCS.Syntax.ConversionOperatorDeclarationSyntax node)
        {
            if (!Map.ContainsKey(node))
                Map.Add(node, Factory.createConversionOperatorDeclarationSyntaxNode().Id);
            base.VisitConversionOperatorDeclaration(node);
        }

        public override void VisitConversionOperatorMemberCref(ROSLYNCS.Syntax.ConversionOperatorMemberCrefSyntax node)
        {
            if (!Map.ContainsKey(node))
                Map.Add(node, Factory.createConversionOperatorMemberCrefSyntaxNode().Id);
            base.VisitConversionOperatorMemberCref(node);
        }

        public override void VisitCrefBracketedParameterList(ROSLYNCS.Syntax.CrefBracketedParameterListSyntax node)
        {
            if (!Map.ContainsKey(node))
                Map.Add(node, Factory.createCrefBracketedParameterListSyntaxNode().Id);
            base.VisitCrefBracketedParameterList(node);
        }

        public override void VisitCrefParameter(ROSLYNCS.Syntax.CrefParameterSyntax node)
        {
            if (!Map.ContainsKey(node))
                Map.Add(node, Factory.createCrefParameterSyntaxNode().Id);
            base.VisitCrefParameter(node);
        }

        public override void VisitCrefParameterList(ROSLYNCS.Syntax.CrefParameterListSyntax node)
        {
            if (!Map.ContainsKey(node))
                Map.Add(node, Factory.createCrefParameterListSyntaxNode().Id);
            base.VisitCrefParameterList(node);
        }

        public override void VisitDefaultExpression(ROSLYNCS.Syntax.DefaultExpressionSyntax node)
        {
            if (!Map.ContainsKey(node))
                Map.Add(node, Factory.createDefaultExpressionSyntaxNode().Id);
            base.VisitDefaultExpression(node);
        }

        public override void VisitDefaultSwitchLabel(ROSLYNCS.Syntax.DefaultSwitchLabelSyntax node)
        {
            if (!Map.ContainsKey(node))
                Map.Add(node, Factory.createDefaultSwitchLabelSyntaxNode().Id);
            base.VisitDefaultSwitchLabel(node);
        }

        public override void VisitDelegateDeclaration(ROSLYNCS.Syntax.DelegateDeclarationSyntax node)
        {
            if (!Map.ContainsKey(node))
                Map.Add(node, Factory.createDelegateDeclarationSyntaxNode().Id);
            base.VisitDelegateDeclaration(node);
        }

        public override void VisitDestructorDeclaration(ROSLYNCS.Syntax.DestructorDeclarationSyntax node)
        {
            if (!Map.ContainsKey(node))
                Map.Add(node, Factory.createDestructorDeclarationSyntaxNode().Id);
            base.VisitDestructorDeclaration(node);
        }

        public override void VisitDoStatement(ROSLYNCS.Syntax.DoStatementSyntax node)
        {
            if (!Map.ContainsKey(node))
                Map.Add(node, Factory.createDoStatementSyntaxNode().Id);
            base.VisitDoStatement(node);
        }

        public override void VisitElementAccessExpression(ROSLYNCS.Syntax.ElementAccessExpressionSyntax node)
        {
            if (!Map.ContainsKey(node))
                Map.Add(node, Factory.createElementAccessExpressionSyntaxNode().Id);
            base.VisitElementAccessExpression(node);
        }

        public override void VisitElementBindingExpression(ROSLYNCS.Syntax.ElementBindingExpressionSyntax node)
        {
            if (!Map.ContainsKey(node))
                Map.Add(node, Factory.createElementBindingExpressionSyntaxNode().Id);
            base.VisitElementBindingExpression(node);
        }

        public override void VisitElseClause(ROSLYNCS.Syntax.ElseClauseSyntax node)
        {
            if (!Map.ContainsKey(node))
                Map.Add(node, Factory.createElseClauseSyntaxNode().Id);
            base.VisitElseClause(node);
        }

        public override void VisitEmptyStatement(ROSLYNCS.Syntax.EmptyStatementSyntax node)
        {
            if (!Map.ContainsKey(node))
                Map.Add(node, Factory.createEmptyStatementSyntaxNode().Id);
            base.VisitEmptyStatement(node);
        }

        public override void VisitEnumDeclaration(ROSLYNCS.Syntax.EnumDeclarationSyntax node)
        {
            if (!Map.ContainsKey(node))
                Map.Add(node, Factory.createEnumDeclarationSyntaxNode().Id);
            base.VisitEnumDeclaration(node);
        }

        public override void VisitEnumMemberDeclaration(ROSLYNCS.Syntax.EnumMemberDeclarationSyntax node)
        {
            if (!Map.ContainsKey(node))
                Map.Add(node, Factory.createEnumMemberDeclarationSyntaxNode().Id);
            base.VisitEnumMemberDeclaration(node);
        }

        public override void VisitEqualsValueClause(ROSLYNCS.Syntax.EqualsValueClauseSyntax node)
        {
            if (!Map.ContainsKey(node))
                Map.Add(node, Factory.createEqualsValueClauseSyntaxNode().Id);
            base.VisitEqualsValueClause(node);
        }

        public override void VisitEventDeclaration(ROSLYNCS.Syntax.EventDeclarationSyntax node)
        {
            if (!Map.ContainsKey(node))
                Map.Add(node, Factory.createEventDeclarationSyntaxNode().Id);
            base.VisitEventDeclaration(node);
        }

        public override void VisitEventFieldDeclaration(ROSLYNCS.Syntax.EventFieldDeclarationSyntax node)
        {
            if (!Map.ContainsKey(node))
                Map.Add(node, Factory.createEventFieldDeclarationSyntaxNode().Id);
            base.VisitEventFieldDeclaration(node);
        }

        public override void VisitExplicitInterfaceSpecifier(ROSLYNCS.Syntax.ExplicitInterfaceSpecifierSyntax node)
        {
            if (!Map.ContainsKey(node))
                Map.Add(node, Factory.createExplicitInterfaceSpecifierSyntaxNode().Id);
            base.VisitExplicitInterfaceSpecifier(node);
        }

        public override void VisitExpressionStatement(ROSLYNCS.Syntax.ExpressionStatementSyntax node)
        {
            if (!Map.ContainsKey(node))
                Map.Add(node, Factory.createExpressionStatementSyntaxNode().Id);
            base.VisitExpressionStatement(node);
        }

        public override void VisitExternAliasDirective(ROSLYNCS.Syntax.ExternAliasDirectiveSyntax node)
        {
            if (!Map.ContainsKey(node))
                Map.Add(node, Factory.createExternAliasDirectiveSyntaxNode().Id);
            base.VisitExternAliasDirective(node);
        }

        public override void VisitFieldDeclaration(ROSLYNCS.Syntax.FieldDeclarationSyntax node)
        {
            if (!Map.ContainsKey(node))
                Map.Add(node, Factory.createFieldDeclarationSyntaxNode().Id);
            base.VisitFieldDeclaration(node);
        }

        public override void VisitFinallyClause(ROSLYNCS.Syntax.FinallyClauseSyntax node)
        {
            if (!Map.ContainsKey(node))
                Map.Add(node, Factory.createFinallyClauseSyntaxNode().Id);
            base.VisitFinallyClause(node);
        }

        public override void VisitFixedStatement(ROSLYNCS.Syntax.FixedStatementSyntax node)
        {
            if (!Map.ContainsKey(node))
                Map.Add(node, Factory.createFixedStatementSyntaxNode().Id);
            base.VisitFixedStatement(node);
        }

        public override void VisitForEachStatement(ROSLYNCS.Syntax.ForEachStatementSyntax node)
        {
            if (!Map.ContainsKey(node))
                Map.Add(node, Factory.createForEachStatementSyntaxNode().Id);
            base.VisitForEachStatement(node);
        }

        public override void VisitForStatement(ROSLYNCS.Syntax.ForStatementSyntax node)
        {
            if (!Map.ContainsKey(node))
                Map.Add(node, Factory.createForStatementSyntaxNode().Id);
            base.VisitForStatement(node);
        }

        public override void VisitFromClause(ROSLYNCS.Syntax.FromClauseSyntax node)
        {
            if (!Map.ContainsKey(node))
                Map.Add(node, Factory.createFromClauseSyntaxNode().Id);
            base.VisitFromClause(node);
        }

        public override void VisitGenericName(ROSLYNCS.Syntax.GenericNameSyntax node)
        {
            if (!Map.ContainsKey(node))
                Map.Add(node, Factory.createGenericNameSyntaxNode().Id);
            base.VisitGenericName(node);
        }

        public override void VisitGlobalStatement(ROSLYNCS.Syntax.GlobalStatementSyntax node)
        {
            if (!Map.ContainsKey(node))
                Map.Add(node, Factory.createGlobalStatementSyntaxNode().Id);
            base.VisitGlobalStatement(node);
        }

        public override void VisitGotoStatement(ROSLYNCS.Syntax.GotoStatementSyntax node)
        {
            if (!Map.ContainsKey(node))
                Map.Add(node, Factory.createGotoStatementSyntaxNode().Id);
            base.VisitGotoStatement(node);
        }

        public override void VisitGroupClause(ROSLYNCS.Syntax.GroupClauseSyntax node)
        {
            if (!Map.ContainsKey(node))
                Map.Add(node, Factory.createGroupClauseSyntaxNode().Id);
            base.VisitGroupClause(node);
        }

        public override void VisitIdentifierName(ROSLYNCS.Syntax.IdentifierNameSyntax node)
        {
            if (!Map.ContainsKey(node))
                Map.Add(node, Factory.createIdentifierNameSyntaxNode().Id);
            base.VisitIdentifierName(node);
        }

        public override void VisitIfStatement(ROSLYNCS.Syntax.IfStatementSyntax node)
        {
            if (!Map.ContainsKey(node))
                Map.Add(node, Factory.createIfStatementSyntaxNode().Id);
            base.VisitIfStatement(node);
        }

        public override void VisitImplicitArrayCreationExpression(ROSLYNCS.Syntax.ImplicitArrayCreationExpressionSyntax node)
        {
            if (!Map.ContainsKey(node))
                Map.Add(node, Factory.createImplicitArrayCreationExpressionSyntaxNode().Id);
            base.VisitImplicitArrayCreationExpression(node);
        }

        public override void VisitImplicitElementAccess(ROSLYNCS.Syntax.ImplicitElementAccessSyntax node)
        {
            if (!Map.ContainsKey(node))
                Map.Add(node, Factory.createImplicitElementAccessSyntaxNode().Id);
            base.VisitImplicitElementAccess(node);
        }

        public override void VisitIncompleteMember(ROSLYNCS.Syntax.IncompleteMemberSyntax node)
        {
            if (!Map.ContainsKey(node))
                Map.Add(node, Factory.createIncompleteMemberSyntaxNode().Id);
            base.VisitIncompleteMember(node);
        }

        public override void VisitIndexerDeclaration(ROSLYNCS.Syntax.IndexerDeclarationSyntax node)
        {
            if (!Map.ContainsKey(node))
                Map.Add(node, Factory.createIndexerDeclarationSyntaxNode().Id);
            base.VisitIndexerDeclaration(node);
        }

        public override void VisitIndexerMemberCref(ROSLYNCS.Syntax.IndexerMemberCrefSyntax node)
        {
            if (!Map.ContainsKey(node))
                Map.Add(node, Factory.createIndexerMemberCrefSyntaxNode().Id);
            base.VisitIndexerMemberCref(node);
        }

        public override void VisitInitializerExpression(ROSLYNCS.Syntax.InitializerExpressionSyntax node)
        {
            if (!Map.ContainsKey(node))
                Map.Add(node, Factory.createInitializerExpressionSyntaxNode().Id);
            base.VisitInitializerExpression(node);
        }

        public override void VisitInterfaceDeclaration(ROSLYNCS.Syntax.InterfaceDeclarationSyntax node)
        {
            if (!Map.ContainsKey(node))
                Map.Add(node, Factory.createInterfaceDeclarationSyntaxNode().Id);
            base.VisitInterfaceDeclaration(node);
        }
        public override void VisitInterpolatedStringExpression(ROSLYNCS.Syntax.InterpolatedStringExpressionSyntax node)
        {
            if (!Map.ContainsKey(node))
                Map.Add(node, Factory.createInterpolatedStringExpressionSyntaxNode().Id);

            base.VisitInterpolatedStringExpression(node);
        }

        public override void VisitInterpolatedStringText(ROSLYNCS.Syntax.InterpolatedStringTextSyntax node)
        {
            if (!Map.ContainsKey(node))
                Map.Add(node, Factory.createInterpolatedStringTextSyntaxNode().Id);

            base.VisitInterpolatedStringText(node);
        }

        public override void VisitInterpolation(ROSLYNCS.Syntax.InterpolationSyntax node)
        {
            if (!Map.ContainsKey(node))
                Map.Add(node, Factory.createInterpolationSyntaxNode().Id);

            base.VisitInterpolation(node);
        }

        public override void VisitInterpolationAlignmentClause(ROSLYNCS.Syntax.InterpolationAlignmentClauseSyntax node)
        {
            if (!Map.ContainsKey(node))
                Map.Add(node, Factory.createInterpolationAlignmentClauseSyntaxNode().Id);

            base.VisitInterpolationAlignmentClause(node);
        }

        public override void VisitInterpolationFormatClause(ROSLYNCS.Syntax.InterpolationFormatClauseSyntax node)
        {
            if (!Map.ContainsKey(node))
                Map.Add(node, Factory.createInterpolationFormatClauseSyntaxNode().Id);

            base.VisitInterpolationFormatClause(node);
        }

        public override void VisitInvocationExpression(ROSLYNCS.Syntax.InvocationExpressionSyntax node)
        {
            if (!Map.ContainsKey(node))
                Map.Add(node, Factory.createInvocationExpressionSyntaxNode().Id);
            base.VisitInvocationExpression(node);
        }

        public override void VisitJoinClause(ROSLYNCS.Syntax.JoinClauseSyntax node)
        {
            if (!Map.ContainsKey(node))
                Map.Add(node, Factory.createJoinClauseSyntaxNode().Id);
            base.VisitJoinClause(node);
        }

        public override void VisitJoinIntoClause(ROSLYNCS.Syntax.JoinIntoClauseSyntax node)
        {
            if (!Map.ContainsKey(node))
                Map.Add(node, Factory.createJoinIntoClauseSyntaxNode().Id);
            base.VisitJoinIntoClause(node);
        }

        public override void VisitLabeledStatement(ROSLYNCS.Syntax.LabeledStatementSyntax node)
        {
            if (!Map.ContainsKey(node))
                Map.Add(node, Factory.createLabeledStatementSyntaxNode().Id);
            base.VisitLabeledStatement(node);
        }

        public override void VisitLetClause(ROSLYNCS.Syntax.LetClauseSyntax node)
        {
            if (!Map.ContainsKey(node))
                Map.Add(node, Factory.createLetClauseSyntaxNode().Id);
            base.VisitLetClause(node);
        }

        public override void VisitLiteralExpression(ROSLYNCS.Syntax.LiteralExpressionSyntax node)
        {
            if (!Map.ContainsKey(node))
                Map.Add(node, Factory.createLiteralExpressionSyntaxNode().Id);
            base.VisitLiteralExpression(node);
        }

        public override void VisitLocalDeclarationStatement(ROSLYNCS.Syntax.LocalDeclarationStatementSyntax node)
        {
            if (!Map.ContainsKey(node))
                Map.Add(node, Factory.createLocalDeclarationStatementSyntaxNode().Id);
            base.VisitLocalDeclarationStatement(node);
        }

        public override void VisitLockStatement(ROSLYNCS.Syntax.LockStatementSyntax node)
        {
            if (!Map.ContainsKey(node))
                Map.Add(node, Factory.createLockStatementSyntaxNode().Id);
            base.VisitLockStatement(node);
        }

        public override void VisitMakeRefExpression(ROSLYNCS.Syntax.MakeRefExpressionSyntax node)
        {
            if (!Map.ContainsKey(node))
                Map.Add(node, Factory.createMakeRefExpressionSyntaxNode().Id);
            base.VisitMakeRefExpression(node);
        }

        public override void VisitMemberAccessExpression(ROSLYNCS.Syntax.MemberAccessExpressionSyntax node)
        {
            if (!Map.ContainsKey(node))
                Map.Add(node, Factory.createMemberAccessExpressionSyntaxNode().Id);
            base.VisitMemberAccessExpression(node);
        }

        public override void VisitMemberBindingExpression(ROSLYNCS.Syntax.MemberBindingExpressionSyntax node)
        {
            if (!Map.ContainsKey(node))
                Map.Add(node, Factory.createMemberBindingExpressionSyntaxNode().Id);
            base.VisitMemberBindingExpression(node);
        }

        public override void VisitMethodDeclaration(ROSLYNCS.Syntax.MethodDeclarationSyntax node)
        {
            if (!Map.ContainsKey(node))
                Map.Add(node, Factory.createMethodDeclarationSyntaxNode().Id);
            base.VisitMethodDeclaration(node);
        }

        public override void VisitNameColon(ROSLYNCS.Syntax.NameColonSyntax node)
        {
            if (!Map.ContainsKey(node))
                Map.Add(node, Factory.createNameColonSyntaxNode().Id);
            base.VisitNameColon(node);
        }

        public override void VisitNameEquals(ROSLYNCS.Syntax.NameEqualsSyntax node)
        {
            if (!Map.ContainsKey(node))
                Map.Add(node, Factory.createNameEqualsSyntaxNode().Id);
            base.VisitNameEquals(node);
        }

        public override void VisitNameMemberCref(ROSLYNCS.Syntax.NameMemberCrefSyntax node)
        {
            if (!Map.ContainsKey(node))
                Map.Add(node, Factory.createNameMemberCrefSyntaxNode().Id);
            base.VisitNameMemberCref(node);
        }

        public override void VisitNamespaceDeclaration(ROSLYNCS.Syntax.NamespaceDeclarationSyntax node)
        {
            if (!Map.ContainsKey(node))
                Map.Add(node, Factory.createNamespaceDeclarationSyntaxNode().Id);

            base.VisitNamespaceDeclaration(node);
        }

        public override void VisitNullableType(ROSLYNCS.Syntax.NullableTypeSyntax node)
        {
            if (!Map.ContainsKey(node))
                Map.Add(node, Factory.createNullableTypeSyntaxNode().Id);

            base.VisitNullableType(node);
        }

        public override void VisitObjectCreationExpression(ROSLYNCS.Syntax.ObjectCreationExpressionSyntax node)
        {
            if (!Map.ContainsKey(node))
                Map.Add(node, Factory.createObjectCreationExpressionSyntaxNode().Id);
            base.VisitObjectCreationExpression(node);
        }

        public override void VisitOmittedArraySizeExpression(ROSLYNCS.Syntax.OmittedArraySizeExpressionSyntax node)
        {
            if (!Map.ContainsKey(node))
                Map.Add(node, Factory.createOmittedArraySizeExpressionSyntaxNode().Id);
            base.VisitOmittedArraySizeExpression(node);
        }

        public override void VisitOmittedTypeArgument(ROSLYNCS.Syntax.OmittedTypeArgumentSyntax node)
        {
            if (!Map.ContainsKey(node))
                Map.Add(node, Factory.createOmittedTypeArgumentSyntaxNode().Id);
            base.VisitOmittedTypeArgument(node);
        }

        public override void VisitOperatorDeclaration(ROSLYNCS.Syntax.OperatorDeclarationSyntax node)
        {
            if (!Map.ContainsKey(node))
                Map.Add(node, Factory.createOperatorDeclarationSyntaxNode().Id);
            base.VisitOperatorDeclaration(node);
        }

        public override void VisitOperatorMemberCref(ROSLYNCS.Syntax.OperatorMemberCrefSyntax node)
        {
            if (!Map.ContainsKey(node))
                Map.Add(node, Factory.createOperatorMemberCrefSyntaxNode().Id);
            base.VisitOperatorMemberCref(node);
        }

        public override void VisitOrderByClause(ROSLYNCS.Syntax.OrderByClauseSyntax node)
        {
            if (!Map.ContainsKey(node))
                Map.Add(node, Factory.createOrderByClauseSyntaxNode().Id);
            base.VisitOrderByClause(node);
        }

        public override void VisitOrdering(ROSLYNCS.Syntax.OrderingSyntax node)
        {
            if (!Map.ContainsKey(node))
                Map.Add(node, Factory.createOrderingSyntaxNode().Id);
            base.VisitOrdering(node);
        }

        public override void VisitParameter(ROSLYNCS.Syntax.ParameterSyntax node)
        {
            if (!Map.ContainsKey(node))
                Map.Add(node, Factory.createParameterSyntaxNode().Id);
            base.VisitParameter(node);
        }

        public override void VisitParameterList(ROSLYNCS.Syntax.ParameterListSyntax node)
        {
            if (!Map.ContainsKey(node))
                Map.Add(node, Factory.createParameterListSyntaxNode().Id);
            base.VisitParameterList(node);
        }

        public override void VisitParenthesizedExpression(ROSLYNCS.Syntax.ParenthesizedExpressionSyntax node)
        {
            if (!Map.ContainsKey(node))
                Map.Add(node, Factory.createParenthesizedExpressionSyntaxNode().Id);
            base.VisitParenthesizedExpression(node);
        }

        public override void VisitParenthesizedLambdaExpression(ROSLYNCS.Syntax.ParenthesizedLambdaExpressionSyntax node)
        {
            if (!Map.ContainsKey(node))
                Map.Add(node, Factory.createParenthesizedLambdaExpressionSyntaxNode().Id);
            base.VisitParenthesizedLambdaExpression(node);
        }

        public override void VisitPointerType(ROSLYNCS.Syntax.PointerTypeSyntax node)
        {
            if (!Map.ContainsKey(node))
                Map.Add(node, Factory.createPointerTypeSyntaxNode().Id);
            base.VisitPointerType(node);
        }

        public override void VisitPostfixUnaryExpression(ROSLYNCS.Syntax.PostfixUnaryExpressionSyntax node)
        {
            if (!Map.ContainsKey(node))
                Map.Add(node, Factory.createPostfixUnaryExpressionSyntaxNode().Id);
            base.VisitPostfixUnaryExpression(node);
        }

        public override void VisitPredefinedType(ROSLYNCS.Syntax.PredefinedTypeSyntax node)
        {
            if (!Map.ContainsKey(node))
                Map.Add(node, Factory.createPredefinedTypeSyntaxNode().Id);
            base.VisitPredefinedType(node);
        }

        public override void VisitPrefixUnaryExpression(ROSLYNCS.Syntax.PrefixUnaryExpressionSyntax node)
        {
            if (!Map.ContainsKey(node))
                Map.Add(node, Factory.createPrefixUnaryExpressionSyntaxNode().Id);
            base.VisitPrefixUnaryExpression(node);
        }

        public override void VisitPropertyDeclaration(ROSLYNCS.Syntax.PropertyDeclarationSyntax node)
        {
            if (!Map.ContainsKey(node))
                Map.Add(node, Factory.createPropertyDeclarationSyntaxNode().Id);
            base.VisitPropertyDeclaration(node);
        }

        public override void VisitQualifiedCref(ROSLYNCS.Syntax.QualifiedCrefSyntax node)
        {
            if (!Map.ContainsKey(node))
                Map.Add(node, Factory.createQualifiedCrefSyntaxNode().Id);
            base.VisitQualifiedCref(node);
        }

        public override void VisitQualifiedName(ROSLYNCS.Syntax.QualifiedNameSyntax node)
        {
            if (!Map.ContainsKey(node))
                Map.Add(node, Factory.createQualifiedNameSyntaxNode().Id);
            base.VisitQualifiedName(node);
        }

        public override void VisitQueryBody(ROSLYNCS.Syntax.QueryBodySyntax node)
        {
            if (!Map.ContainsKey(node))
                Map.Add(node, Factory.createQueryBodySyntaxNode().Id);
            base.VisitQueryBody(node);
        }

        public override void VisitQueryContinuation(ROSLYNCS.Syntax.QueryContinuationSyntax node)
        {
            if (!Map.ContainsKey(node))
                Map.Add(node, Factory.createQueryContinuationSyntaxNode().Id);
            base.VisitQueryContinuation(node);
        }

        public override void VisitQueryExpression(ROSLYNCS.Syntax.QueryExpressionSyntax node)
        {
            if (!Map.ContainsKey(node))
                Map.Add(node, Factory.createQueryExpressionSyntaxNode().Id);
            base.VisitQueryExpression(node);
        }

        public override void VisitRefTypeExpression(ROSLYNCS.Syntax.RefTypeExpressionSyntax node)
        {
            if (!Map.ContainsKey(node))
                Map.Add(node, Factory.createRefTypeExpressionSyntaxNode().Id);
            base.VisitRefTypeExpression(node);
        }

        public override void VisitRefValueExpression(ROSLYNCS.Syntax.RefValueExpressionSyntax node)
        {
            if (!Map.ContainsKey(node))
                Map.Add(node, Factory.createRefValueExpressionSyntaxNode().Id);
            base.VisitRefValueExpression(node);
        }

        public override void VisitReturnStatement(ROSLYNCS.Syntax.ReturnStatementSyntax node)
        {
            if (!Map.ContainsKey(node))
                Map.Add(node, Factory.createReturnStatementSyntaxNode().Id);
            base.VisitReturnStatement(node);
        }

        public override void VisitSelectClause(ROSLYNCS.Syntax.SelectClauseSyntax node)
        {
            if (!Map.ContainsKey(node))
                Map.Add(node, Factory.createSelectClauseSyntaxNode().Id);
            base.VisitSelectClause(node);
        }

        public override void VisitSimpleBaseType(ROSLYNCS.Syntax.SimpleBaseTypeSyntax node)
        {
            if (!Map.ContainsKey(node))
                Map.Add(node, Factory.createSimpleBaseTypeSyntaxNode().Id);
            base.VisitSimpleBaseType(node);
        }

        public override void VisitSimpleLambdaExpression(ROSLYNCS.Syntax.SimpleLambdaExpressionSyntax node)
        {
            if (!Map.ContainsKey(node))
                Map.Add(node, Factory.createSimpleLambdaExpressionSyntaxNode().Id);
            base.VisitSimpleLambdaExpression(node);
        }

        public override void VisitSizeOfExpression(ROSLYNCS.Syntax.SizeOfExpressionSyntax node)
        {
            if (!Map.ContainsKey(node))
                Map.Add(node, Factory.createSizeOfExpressionSyntaxNode().Id);
            base.VisitSizeOfExpression(node);
        }

        public override void VisitStackAllocArrayCreationExpression(ROSLYNCS.Syntax.StackAllocArrayCreationExpressionSyntax node)
        {
            if (!Map.ContainsKey(node))
                Map.Add(node, Factory.createStackAllocArrayCreationExpressionSyntaxNode().Id);
            base.VisitStackAllocArrayCreationExpression(node);
        }

        public override void VisitStructDeclaration(ROSLYNCS.Syntax.StructDeclarationSyntax node)
        {
            if (!Map.ContainsKey(node))
                Map.Add(node, Factory.createStructDeclarationSyntaxNode().Id);
            base.VisitStructDeclaration(node);
        }

        public override void VisitSwitchSection(ROSLYNCS.Syntax.SwitchSectionSyntax node)
        {
            if (!Map.ContainsKey(node))
                Map.Add(node, Factory.createSwitchSectionSyntaxNode().Id);
            base.VisitSwitchSection(node);
        }

        public override void VisitSwitchStatement(ROSLYNCS.Syntax.SwitchStatementSyntax node)
        {
            if (!Map.ContainsKey(node))
                Map.Add(node, Factory.createSwitchStatementSyntaxNode().Id);
            base.VisitSwitchStatement(node);
        }

        public override void VisitThisExpression(ROSLYNCS.Syntax.ThisExpressionSyntax node)
        {
            if (!Map.ContainsKey(node))
                Map.Add(node, Factory.createThisExpressionSyntaxNode().Id);
            base.VisitThisExpression(node);
        }

        public override void VisitThrowStatement(ROSLYNCS.Syntax.ThrowStatementSyntax node)
        {
            if (!Map.ContainsKey(node))
                Map.Add(node, Factory.createThrowStatementSyntaxNode().Id);
            base.VisitThrowStatement(node);
        }

        public override void VisitTryStatement(ROSLYNCS.Syntax.TryStatementSyntax node)
        {
            if (!Map.ContainsKey(node))
                Map.Add(node, Factory.createTryStatementSyntaxNode().Id);
            base.VisitTryStatement(node);
        }

        public override void VisitTypeArgumentList(ROSLYNCS.Syntax.TypeArgumentListSyntax node)
        {
            if (!Map.ContainsKey(node))
                Map.Add(node, Factory.createTypeArgumentListSyntaxNode().Id);
            base.VisitTypeArgumentList(node);
        }

        public override void VisitTypeConstraint(ROSLYNCS.Syntax.TypeConstraintSyntax node)
        {
            if (!Map.ContainsKey(node))
                Map.Add(node, Factory.createTypeConstraintSyntaxNode().Id);
            base.VisitTypeConstraint(node);
        }

        public override void VisitTypeCref(ROSLYNCS.Syntax.TypeCrefSyntax node)
        {
            if (!Map.ContainsKey(node))
                Map.Add(node, Factory.createTypeCrefSyntaxNode().Id);
            base.VisitTypeCref(node);
        }

        public override void VisitTypeOfExpression(ROSLYNCS.Syntax.TypeOfExpressionSyntax node)
        {
            if (!Map.ContainsKey(node))
                Map.Add(node, Factory.createTypeOfExpressionSyntaxNode().Id);
            base.VisitTypeOfExpression(node);
        }

        public override void VisitTypeParameter(ROSLYNCS.Syntax.TypeParameterSyntax node)
        {
            if (!Map.ContainsKey(node))
                Map.Add(node, Factory.createTypeParameterSyntaxNode().Id);
            base.VisitTypeParameter(node);
        }

        public override void VisitTypeParameterConstraintClause(ROSLYNCS.Syntax.TypeParameterConstraintClauseSyntax node)
        {
            if (!Map.ContainsKey(node))
                Map.Add(node, Factory.createTypeParameterConstraintClauseSyntaxNode().Id);
            base.VisitTypeParameterConstraintClause(node);
        }

        public override void VisitTypeParameterList(ROSLYNCS.Syntax.TypeParameterListSyntax node)
        {
            if (!Map.ContainsKey(node))
                Map.Add(node, Factory.createTypeParameterListSyntaxNode().Id);
            base.VisitTypeParameterList(node);
        }

        public override void VisitUnsafeStatement(ROSLYNCS.Syntax.UnsafeStatementSyntax node)
        {
            if (!Map.ContainsKey(node))
                Map.Add(node, Factory.createUnsafeStatementSyntaxNode().Id);
            base.VisitUnsafeStatement(node);
        }

        public override void VisitUsingDirective(ROSLYNCS.Syntax.UsingDirectiveSyntax node)
        {
            if (!Map.ContainsKey(node))
                Map.Add(node, Factory.createUsingDirectiveSyntaxNode().Id);
            base.VisitUsingDirective(node);
        }

        public override void VisitUsingStatement(ROSLYNCS.Syntax.UsingStatementSyntax node)
        {
            if (!Map.ContainsKey(node))
                Map.Add(node, Factory.createUsingStatementSyntaxNode().Id);
            base.VisitUsingStatement(node);
        }

        public override void VisitVariableDeclaration(ROSLYNCS.Syntax.VariableDeclarationSyntax node)
        {
            if (!Map.ContainsKey(node))
                Map.Add(node, Factory.createVariableDeclarationSyntaxNode().Id);
            base.VisitVariableDeclaration(node);
        }

        public override void VisitVariableDeclarator(ROSLYNCS.Syntax.VariableDeclaratorSyntax node)
        {
            if (!Map.ContainsKey(node))
                Map.Add(node, Factory.createVariableDeclaratorSyntaxNode().Id);
            base.VisitVariableDeclarator(node);
        }

        public override void VisitWhereClause(ROSLYNCS.Syntax.WhereClauseSyntax node)
        {
            if (!Map.ContainsKey(node))
                Map.Add(node, Factory.createWhereClauseSyntaxNode().Id);
            base.VisitWhereClause(node);
        }

        public override void VisitWhileStatement(ROSLYNCS.Syntax.WhileStatementSyntax node)
        {
            if (!Map.ContainsKey(node))
                Map.Add(node, Factory.createWhileStatementSyntaxNode().Id);
            base.VisitWhileStatement(node);
        }

        public override void VisitXmlCDataSection(ROSLYNCS.Syntax.XmlCDataSectionSyntax node)
        {
            if (!Map.ContainsKey(node))
                Map.Add(node, Factory.createXmlCDataSectionSyntaxNode().Id);
            base.VisitXmlCDataSection(node);
        }

        public override void VisitXmlComment(ROSLYNCS.Syntax.XmlCommentSyntax node)
        {
            if (!Map.ContainsKey(node))
                Map.Add(node, Factory.createXmlCommentSyntaxNode().Id);
            base.VisitXmlComment(node);
        }

        public override void VisitXmlCrefAttribute(ROSLYNCS.Syntax.XmlCrefAttributeSyntax node)
        {
            if (!Map.ContainsKey(node))
                Map.Add(node, Factory.createXmlCrefAttributeSyntaxNode().Id);
            base.VisitXmlCrefAttribute(node);
        }

        public override void VisitXmlElement(ROSLYNCS.Syntax.XmlElementSyntax node)
        {
            if (!Map.ContainsKey(node))
                Map.Add(node, Factory.createXmlElementSyntaxNode().Id);
            base.VisitXmlElement(node);
        }

        public override void VisitXmlElementEndTag(ROSLYNCS.Syntax.XmlElementEndTagSyntax node)
        {
            if (!Map.ContainsKey(node))
                Map.Add(node, Factory.createXmlElementEndTagSyntaxNode().Id);
            base.VisitXmlElementEndTag(node);
        }

        public override void VisitXmlElementStartTag(ROSLYNCS.Syntax.XmlElementStartTagSyntax node)
        {
            if (!Map.ContainsKey(node))
                Map.Add(node, Factory.createXmlElementStartTagSyntaxNode().Id);
            base.VisitXmlElementStartTag(node);
        }

        public override void VisitXmlEmptyElement(ROSLYNCS.Syntax.XmlEmptyElementSyntax node)
        {
            if (!Map.ContainsKey(node))
                Map.Add(node, Factory.createXmlEmptyElementSyntaxNode().Id);
            base.VisitXmlEmptyElement(node);
        }

        public override void VisitXmlName(ROSLYNCS.Syntax.XmlNameSyntax node)
        {
            if (!Map.ContainsKey(node))
                Map.Add(node, Factory.createXmlNameSyntaxNode().Id);
            base.VisitXmlName(node);
        }

        public override void VisitXmlNameAttribute(ROSLYNCS.Syntax.XmlNameAttributeSyntax node)
        {
            if (!Map.ContainsKey(node))
                Map.Add(node, Factory.createXmlNameAttributeSyntaxNode().Id);
            base.VisitXmlNameAttribute(node);
        }

        public override void VisitXmlPrefix(ROSLYNCS.Syntax.XmlPrefixSyntax node)
        {
            if (!Map.ContainsKey(node))
                Map.Add(node, Factory.createXmlPrefixSyntaxNode().Id);
            base.VisitXmlPrefix(node);
        }

        public override void VisitXmlProcessingInstruction(ROSLYNCS.Syntax.XmlProcessingInstructionSyntax node)
        {
            if (!Map.ContainsKey(node))
                Map.Add(node, Factory.createXmlProcessingInstructionSyntaxNode().Id);
            base.VisitXmlProcessingInstruction(node);
        }

        public override void VisitXmlText(ROSLYNCS.Syntax.XmlTextSyntax node)
        {
            if (!Map.ContainsKey(node))
                Map.Add(node, Factory.createXmlTextSyntaxNode().Id);
            base.VisitXmlText(node);
        }

        public override void VisitXmlTextAttribute(ROSLYNCS.Syntax.XmlTextAttributeSyntax node)
        {
            if (!Map.ContainsKey(node))
                Map.Add(node, Factory.createXmlTextAttributeSyntaxNode().Id);
            base.VisitXmlTextAttribute(node);
        }

        public override void VisitYieldStatement(ROSLYNCS.Syntax.YieldStatementSyntax node)
        {
            if (!Map.ContainsKey(node))
                Map.Add(node, Factory.createYieldStatementSyntaxNode().Id);
            base.VisitYieldStatement(node);
        }
    }
}
