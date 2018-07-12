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

    /// <summary>
    /// Class for setting semantic cross edges in the ASG, eg. method calls, type definitions, etc.
    /// </summary>
    class CrossEdgeFiller
    {
        CSHARP.Factory Factory;
        Dictionary<ROSLYNCS.CSharpSyntaxNode, uint> Map;

        public CrossEdgeFiller(CSHARP.Factory fact, Dictionary<ROSLYNCS.CSharpSyntaxNode, uint> map)
        {
            Factory = fact;
            Map = map;
        }

        public void AccessorCallFiller(ROSLYNCS.Syntax.AccessorDeclarationSyntax node, ROSLYNCS.Syntax.ElementAccessExpressionSyntax reference)
        {
            if(reference != null)
            {
                var accessorDeclaration = GetOrCreateNode<CSHARP.Nodes.Structure.AccessorDeclarationSyntax>(node);
                GetOrCreateNode<CSHARP.Nodes.Expression.ElementAccessExpressionSyntax>(reference).addAccessorCall(accessorDeclaration);           
            }
        }

        public void AccessorCallFiller(ROSLYNCS.Syntax.AccessorDeclarationSyntax node, ROSLYNCS.Syntax.IdentifierNameSyntax reference)
        {
            if(reference != null)
            {
                var accessorDeclaration = GetOrCreateNode<CSHARP.Nodes.Structure.AccessorDeclarationSyntax>(node);
                GetOrCreateNode<CSHARP.Nodes.Expression.IdentifierNameSyntax>(reference).addAccessorCall(accessorDeclaration);
            }
        }

        public void ConstructorCallFiller(ROSLYNCS.Syntax.ConstructorDeclarationSyntax node, ROSLYNCS.Syntax.ConstructorInitializerSyntax reference)
        {
            if (reference != null)
            {
                var constructorDeclarartion = GetOrCreateNode<CSHARP.Nodes.Structure.ConstructorDeclarationSyntax>(node);
                GetOrCreateNode<CSHARP.Nodes.Structure.ConstructorInitializerSyntax>(reference).setConstructorCall(constructorDeclarartion);
            }
        }

        public void ConstructorCallFiller(ROSLYNCS.Syntax.ConstructorDeclarationSyntax node, ROSLYNCS.Syntax.ObjectCreationExpressionSyntax reference)
        {
            if (reference != null)
            {
                var constructorDeclarartion = GetOrCreateNode<CSHARP.Nodes.Structure.ConstructorDeclarationSyntax>(node);
                GetOrCreateNode<CSHARP.Nodes.Expression.ObjectCreationExpressionSyntax>(reference).setConstructorCall(constructorDeclarartion);
            }
        }

        public void ConversionOperatorCallFiller(ROSLYNCS.Syntax.ConversionOperatorDeclarationSyntax node, ROSLYNCS.Syntax.CastExpressionSyntax reference)
        {
            if(reference != null)
            {
                var conversionOperatorDeclaration = GetOrCreateNode<CSHARP.Nodes.Structure.ConversionOperatorDeclarationSyntax>(node);
                GetOrCreateNode<CSHARP.Nodes.Expression.CastExpressionSyntax>(reference).setConversionOperatorCall(conversionOperatorDeclaration);
            }
        }

        /// <summary>
        /// Sets the Identifier's declaration
        /// </summary>
        /// <param name="node">A VariableDeclaration, Parameter, ForeachStatement, CatchDeclaration, MethodDeclaration and DelegateDeclaration</param>
        /// <param name="reference">The Identifier</param>
        public void DeclarationFiller(ROSLYNCS.CSharpSyntaxNode node, ROSLYNCS.Syntax.IdentifierNameSyntax reference)
        {
            if (reference != null)
            {
                if (node.Kind() != ROSLYNCS.SyntaxKind.VariableDeclarator
                    && node.Kind() != ROSLYNCS.SyntaxKind.Parameter
                    && node.Kind() != ROSLYNCS.SyntaxKind.ForEachStatement
                    && node.Kind() != ROSLYNCS.SyntaxKind.CatchDeclaration
                    && node.Kind() != ROSLYNCS.SyntaxKind.MethodDeclaration
                    && node.Kind() != ROSLYNCS.SyntaxKind.DelegateDeclaration)
                {
                    WriteMsg.WriteLine("Warning: Invalid node kind ({0}) given to CrossEdGeFiller.DeclarationFiller()", WriteMsg.MsgLevel.Warning, node.Kind());
                    return;
                }
                var declaration = GetOrCreateNode<CSHARP.Nodes.Base.Positioned>(node);
                GetOrCreateNode<CSHARP.Nodes.Expression.IdentifierNameSyntax>(reference).setDeclaration(declaration);
            }
        }

        public void EventAccessorCallFiller(ROSLYNCS.Syntax.AccessorDeclarationSyntax node, ROSLYNCS.Syntax.AssignmentExpressionSyntax reference)
        {
            if(reference != null)
            {
                var accessorDeclaration = GetOrCreateNode<CSHARP.Nodes.Structure.AccessorDeclarationSyntax>(node);
                GetOrCreateNode<CSHARP.Nodes.Expression.AssignmentExpressionSyntax>(reference).setEventAccessorCall(accessorDeclaration);
            }
        }

        public void MethodCallFiller(ROSLYNCS.Syntax.MethodDeclarationSyntax node, ROSLYNCS.Syntax.InvocationExpressionSyntax reference)
        {
            if (reference != null)
            {
                var methodDeclaration = GetOrCreateNode<CSHARP.Nodes.Structure.MethodDeclarationSyntax>(node);
                GetOrCreateNode<CSHARP.Nodes.Expression.InvocationExpressionSyntax>(reference).setMethodCall(methodDeclaration);
            }
        }

        public void OriginalDefinitionFiller(ROSLYNCS.Syntax.MemberDeclarationSyntax node, ROSLYNCS.Syntax.TypeSyntax reference)
        {
            if (reference != null)
            {
                var memberDeclaration = GetOrCreateNode<CSHARP.Nodes.Structure.MemberDeclarationSyntax>(node);
                GetOrCreateNode<CSHARP.Nodes.Expression.TypeSyntax>(reference).setOriginalDefinition(memberDeclaration);
            }
        }

        public void OverloadedOperatorCallFiller(ROSLYNCS.Syntax.OperatorDeclarationSyntax node, ROSLYNCS.Syntax.BinaryExpressionSyntax reference)
        {
            if(reference != null)
            {
                var operatorDeclaration = GetOrCreateNode<CSHARP.Nodes.Structure.OperatorDeclarationSyntax>(node);
                GetOrCreateNode<CSHARP.Nodes.Expression.BinaryExpressionSyntax>(reference).setOverloadedOperatorCall(operatorDeclaration);
            }
        }

        public void OverloadedOperatorCallFiller(ROSLYNCS.Syntax.OperatorDeclarationSyntax node, ROSLYNCS.Syntax.PostfixUnaryExpressionSyntax reference)
        {
            if (reference != null)
            {
                var operatorDeclaration = GetOrCreateNode<CSHARP.Nodes.Structure.OperatorDeclarationSyntax>(node);
                GetOrCreateNode<CSHARP.Nodes.Expression.PostfixUnaryExpressionSyntax>(reference).setOverloadedOperatorCall(operatorDeclaration);
            }
        }

        public void OverloadedOperatorCallFiller(ROSLYNCS.Syntax.OperatorDeclarationSyntax node, ROSLYNCS.Syntax.PrefixUnaryExpressionSyntax reference)
        {
            if (reference != null)
            {
                var operatorDeclaration = GetOrCreateNode<CSHARP.Nodes.Structure.OperatorDeclarationSyntax>(node);
                GetOrCreateNode<CSHARP.Nodes.Expression.PrefixUnaryExpressionSyntax>(reference).setOverloadedOperatorCall(operatorDeclaration);
            }
        }

        public void OverloadedOperatorCallFiller(ROSLYNCS.Syntax.OperatorDeclarationSyntax node, ROSLYNCS.Syntax.AssignmentExpressionSyntax reference)
        {
            if (reference != null)
            {
                var operatorDeclaration = GetOrCreateNode<CSHARP.Nodes.Structure.OperatorDeclarationSyntax>(node);
                GetOrCreateNode<CSHARP.Nodes.Expression.AssignmentExpressionSyntax>(reference).setOverloadedOperatorCall(operatorDeclaration);
            }
        }

        /// <summary>
        /// Tries to get the corresponding Columbus node for the Roslyn node provided.
        /// Creates a dummy node based on the Roslyn nodekind if it does not exist yet.
        /// </summary>
        /// <typeparam name="T">The type of the Columbus node expected</typeparam>
        /// <param name="node">A Roslyn node</param>
        /// <exception cref="System.InvalidCastException">Thrown if casting to <paramref name="T"/> is illegal</exception>
        public T GetOrCreateNode<T>(ROSLYNCS.CSharpSyntaxNode node) where T : CSHARP.Nodes.Base.Positioned
        {
            uint id;
            if (Map.TryGetValue(node, out id))
                return (T)Factory.getRef(id);

            CSHARP.Nodes.Base.Positioned dummyNode;
            var lineSpan = node.GetLocation().GetLineSpan();
            var kind = node.Kind();

            #region switch
            switch (kind)
            {
                case ROSLYNCS.SyntaxKind.AddAccessorDeclaration:
                case ROSLYNCS.SyntaxKind.GetAccessorDeclaration:
                case ROSLYNCS.SyntaxKind.RemoveAccessorDeclaration:
                case ROSLYNCS.SyntaxKind.SetAccessorDeclaration:
                case ROSLYNCS.SyntaxKind.UnknownAccessorDeclaration:
                    dummyNode = Factory.createAccessorDeclarationSyntaxNode();
                    if(((ROSLYNCS.Syntax.AccessorDeclarationSyntax)node).Keyword != null)
                        ((CSHARP.Nodes.Structure.AccessorDeclarationSyntax)dummyNode).Identifier = ((ROSLYNCS.Syntax.AccessorDeclarationSyntax)node).Keyword.Text;
                    break;
                case ROSLYNCS.SyntaxKind.AccessorList:
                    dummyNode = Factory.createAccessorListSyntaxNode();
                    break;
                case ROSLYNCS.SyntaxKind.AliasQualifiedName:
                    dummyNode = Factory.createAliasQualifiedNameSyntaxNode();
                    break;
                case ROSLYNCS.SyntaxKind.AnonymousMethodExpression:
                    dummyNode = Factory.createAnonymousMethodExpressionSyntaxNode();
                    break;
                case ROSLYNCS.SyntaxKind.AnonymousObjectCreationExpression:
                    dummyNode = Factory.createAnonymousObjectCreationExpressionSyntaxNode();
                    break;
                case ROSLYNCS.SyntaxKind.AnonymousObjectMemberDeclarator:
                    dummyNode = Factory.createAnonymousObjectMemberDeclaratorSyntaxNode();
                    break;
                case ROSLYNCS.SyntaxKind.Argument:
                    dummyNode = Factory.createArgumentSyntaxNode();
                    break;
                case ROSLYNCS.SyntaxKind.ArgumentList:
                    dummyNode = Factory.createArgumentListSyntaxNode();
                    break;
                case ROSLYNCS.SyntaxKind.ArrayCreationExpression:
                    dummyNode = Factory.createArrayCreationExpressionSyntaxNode();
                    break;
                case ROSLYNCS.SyntaxKind.ArrayRankSpecifier:
                    dummyNode = Factory.createArrayRankSpecifierSyntaxNode();
                    break;
                case ROSLYNCS.SyntaxKind.ArrayType:
                    dummyNode = Factory.createArrayTypeSyntaxNode();
                    break;
                case ROSLYNCS.SyntaxKind.ArrowExpressionClause:
                    dummyNode = Factory.createArrowExpressionClauseSyntaxNode();
                    break;
                case ROSLYNCS.SyntaxKind.AddAssignmentExpression:
                case ROSLYNCS.SyntaxKind.AndAssignmentExpression:
                case ROSLYNCS.SyntaxKind.DivideAssignmentExpression:
                case ROSLYNCS.SyntaxKind.ExclusiveOrAssignmentExpression:
                case ROSLYNCS.SyntaxKind.LeftShiftAssignmentExpression:
                case ROSLYNCS.SyntaxKind.ModuloAssignmentExpression:
                case ROSLYNCS.SyntaxKind.MultiplyAssignmentExpression:
                case ROSLYNCS.SyntaxKind.OrAssignmentExpression:
                case ROSLYNCS.SyntaxKind.RightShiftAssignmentExpression:
                case ROSLYNCS.SyntaxKind.SimpleAssignmentExpression:
                case ROSLYNCS.SyntaxKind.SubtractAssignmentExpression:
                    dummyNode = Factory.createAssignmentExpressionSyntaxNode();
                    break;
                case ROSLYNCS.SyntaxKind.Attribute:
                    dummyNode = Factory.createAttributeSyntaxNode();
                    break;
                case ROSLYNCS.SyntaxKind.AttributeArgument:
                    dummyNode = Factory.createAttributeArgumentSyntaxNode();
                    break;
                case ROSLYNCS.SyntaxKind.AttributeArgumentList:
                    dummyNode = Factory.createAttributeArgumentListSyntaxNode();
                    break;
                case ROSLYNCS.SyntaxKind.AttributeList:
                    dummyNode = Factory.createAttributeListSyntaxNode();
                    break;
                case ROSLYNCS.SyntaxKind.AttributeTargetSpecifier:
                    dummyNode = Factory.createAttributeTargetSpecifierSyntaxNode();
                    ((CSHARP.Nodes.Structure.AttributeTargetSpecifierSyntax)dummyNode).Identifier = ((ROSLYNCS.Syntax.AttributeTargetSpecifierSyntax)node).Identifier.Text;
                    break;
                case ROSLYNCS.SyntaxKind.AwaitExpression:
                    dummyNode = Factory.createAwaitExpressionSyntaxNode();
                    break;
                case ROSLYNCS.SyntaxKind.BaseExpression:
                    dummyNode = Factory.createBaseExpressionSyntaxNode();
                    break;
                case ROSLYNCS.SyntaxKind.BaseList:
                    dummyNode = Factory.createBaseListSyntaxNode();
                    break;
                case ROSLYNCS.SyntaxKind.AddExpression:
                case ROSLYNCS.SyntaxKind.SubtractExpression:
                case ROSLYNCS.SyntaxKind.MultiplyExpression:
                case ROSLYNCS.SyntaxKind.DivideExpression:
                case ROSLYNCS.SyntaxKind.ModuloExpression:
                case ROSLYNCS.SyntaxKind.LeftShiftExpression:
                case ROSLYNCS.SyntaxKind.RightShiftExpression:
                case ROSLYNCS.SyntaxKind.LogicalOrExpression:
                case ROSLYNCS.SyntaxKind.LogicalAndExpression:
                case ROSLYNCS.SyntaxKind.BitwiseOrExpression:
                case ROSLYNCS.SyntaxKind.BitwiseAndExpression:
                case ROSLYNCS.SyntaxKind.ExclusiveOrExpression:
                case ROSLYNCS.SyntaxKind.EqualsExpression:
                case ROSLYNCS.SyntaxKind.NotEqualsExpression:
                case ROSLYNCS.SyntaxKind.LessThanExpression:
                case ROSLYNCS.SyntaxKind.LessThanOrEqualExpression:
                case ROSLYNCS.SyntaxKind.GreaterThanExpression:
                case ROSLYNCS.SyntaxKind.GreaterThanOrEqualExpression:
                case ROSLYNCS.SyntaxKind.IsExpression:
                case ROSLYNCS.SyntaxKind.AsExpression:
                case ROSLYNCS.SyntaxKind.CoalesceExpression:
                    dummyNode = Factory.createBinaryExpressionSyntaxNode();
                    break;
                case ROSLYNCS.SyntaxKind.Block:
                    dummyNode = Factory.createBlockSyntaxNode();
                    break;
                case ROSLYNCS.SyntaxKind.BracketedArgumentList:
                    dummyNode = Factory.createBracketedArgumentListSyntaxNode();
                    break;
                case ROSLYNCS.SyntaxKind.BracketedParameterList:
                    dummyNode = Factory.createBracketedParameterListSyntaxNode();
                    break;
                case ROSLYNCS.SyntaxKind.BreakStatement:
                    dummyNode = Factory.createBreakStatementSyntaxNode();
                    break;
                case ROSLYNCS.SyntaxKind.CaseSwitchLabel:
                    dummyNode = Factory.createCaseSwitchLabelSyntaxNode();
                    break;
                case ROSLYNCS.SyntaxKind.CastExpression:
                    dummyNode = Factory.createCastExpressionSyntaxNode();
                    break;
                case ROSLYNCS.SyntaxKind.CatchClause:
                    dummyNode = Factory.createCatchClauseSyntaxNode();
                    break;
                case ROSLYNCS.SyntaxKind.CatchDeclaration:
                    dummyNode = Factory.createCatchDeclarationSyntaxNode();
                    break;
                case ROSLYNCS.SyntaxKind.CatchFilterClause:
                    dummyNode = Factory.createCatchFilterClauseSyntaxNode();
                    break;
                case ROSLYNCS.SyntaxKind.CheckedExpression:
                    dummyNode = Factory.createCheckedExpressionSyntaxNode();
                    break;
                case ROSLYNCS.SyntaxKind.CheckedStatement:
                    dummyNode = Factory.createCheckedStatementSyntaxNode();
                    break;
                case ROSLYNCS.SyntaxKind.ClassDeclaration:
                    dummyNode = Factory.createClassDeclarationSyntaxNode();
                    ((CSHARP.Nodes.Structure.ClassDeclarationSyntax)dummyNode).Identifier = ((ROSLYNCS.Syntax.ClassDeclarationSyntax)node).Identifier.Text;
                    break;
                case ROSLYNCS.SyntaxKind.ClassConstraint:
                case ROSLYNCS.SyntaxKind.StructConstraint:
                    dummyNode = Factory.createClassOrStructConstraintSyntaxNode();
                    break;
                case ROSLYNCS.SyntaxKind.CompilationUnit:
                    dummyNode = Factory.createCompilationUnitSyntaxNode();
                    break;
                case ROSLYNCS.SyntaxKind.ConditionalAccessExpression:
                    dummyNode = Factory.createConditionalAccessExpressionSyntaxNode();
                    break;
                case ROSLYNCS.SyntaxKind.ConditionalExpression:
                    dummyNode = Factory.createConditionalExpressionSyntaxNode();
                    break;
                case ROSLYNCS.SyntaxKind.ConstructorConstraint:
                    dummyNode = Factory.createConstructorConstraintSyntaxNode();
                    break;
                case ROSLYNCS.SyntaxKind.ConstructorDeclaration:
                    dummyNode = Factory.createConstructorDeclarationSyntaxNode();
                    ((CSHARP.Nodes.Structure.ConstructorDeclarationSyntax)dummyNode).Identifier = ((ROSLYNCS.Syntax.ConstructorDeclarationSyntax)node).Identifier.Text;
                    break;
                case ROSLYNCS.SyntaxKind.BaseConstructorInitializer:
                case ROSLYNCS.SyntaxKind.ThisConstructorInitializer:
                    dummyNode = Factory.createConstructorInitializerSyntaxNode();
                    break;
                case ROSLYNCS.SyntaxKind.ContinueStatement:
                    dummyNode = Factory.createContinueStatementSyntaxNode();
                    break;
                case ROSLYNCS.SyntaxKind.ConversionOperatorDeclaration:
                    dummyNode = Factory.createConversionOperatorDeclarationSyntaxNode();
                    break;
                case ROSLYNCS.SyntaxKind.ConversionOperatorMemberCref:
                    dummyNode = Factory.createConversionOperatorMemberCrefSyntaxNode();
                    break;
                case ROSLYNCS.SyntaxKind.CrefBracketedParameterList:
                    dummyNode = Factory.createCrefBracketedParameterListSyntaxNode();
                    break;
                case ROSLYNCS.SyntaxKind.CrefParameter:
                    dummyNode = Factory.createCrefParameterSyntaxNode();
                    break;
                case ROSLYNCS.SyntaxKind.CrefParameterList:
                    dummyNode = Factory.createCrefParameterListSyntaxNode();
                    break;
                case ROSLYNCS.SyntaxKind.DefaultExpression:
                    dummyNode = Factory.createDefaultExpressionSyntaxNode();
                    break;
                case ROSLYNCS.SyntaxKind.DefaultSwitchLabel:
                    dummyNode = Factory.createDefaultSwitchLabelSyntaxNode();
                    break;
                case ROSLYNCS.SyntaxKind.DelegateDeclaration:
                    dummyNode = Factory.createDelegateDeclarationSyntaxNode();
                    ((CSHARP.Nodes.Structure.DelegateDeclarationSyntax)dummyNode).Identifier = ((ROSLYNCS.Syntax.DelegateDeclarationSyntax)node).Identifier.Text;
                    break;
                case ROSLYNCS.SyntaxKind.DestructorDeclaration:
                    dummyNode = Factory.createDestructorDeclarationSyntaxNode();
                    ((CSHARP.Nodes.Structure.DestructorDeclarationSyntax)dummyNode).Identifier = ((ROSLYNCS.Syntax.DestructorDeclarationSyntax)node).Identifier.Text;
                    break;
                case ROSLYNCS.SyntaxKind.DoStatement:
                    dummyNode = Factory.createDoStatementSyntaxNode();
                    break;
                case ROSLYNCS.SyntaxKind.ElementAccessExpression:
                    dummyNode = Factory.createElementAccessExpressionSyntaxNode();
                    break;
                case ROSLYNCS.SyntaxKind.ElementBindingExpression:
                    dummyNode = Factory.createElementBindingExpressionSyntaxNode();
                    break;
                case ROSLYNCS.SyntaxKind.ElseClause:
                    dummyNode = Factory.createElseClauseSyntaxNode();
                    break;
                case ROSLYNCS.SyntaxKind.EmptyStatement:
                    dummyNode = Factory.createEmptyStatementSyntaxNode();
                    break;
                case ROSLYNCS.SyntaxKind.EnumDeclaration:
                    dummyNode = Factory.createEnumDeclarationSyntaxNode();
                    ((CSHARP.Nodes.Structure.EnumDeclarationSyntax)dummyNode).Identifier = ((ROSLYNCS.Syntax.EnumDeclarationSyntax)node).Identifier.Text;
                    break;
                case ROSLYNCS.SyntaxKind.EnumMemberDeclaration:
                    dummyNode = Factory.createEnumMemberDeclarationSyntaxNode();
                    ((CSHARP.Nodes.Structure.EnumMemberDeclarationSyntax)dummyNode).Identifier = ((ROSLYNCS.Syntax.EnumMemberDeclarationSyntax)node).Identifier.Text;
                    break;
                case ROSLYNCS.SyntaxKind.EqualsValueClause:
                    dummyNode = Factory.createEqualsValueClauseSyntaxNode();
                    break;
                case ROSLYNCS.SyntaxKind.EventDeclaration:
                    dummyNode = Factory.createEventDeclarationSyntaxNode();
                    ((CSHARP.Nodes.Structure.EventDeclarationSyntax)dummyNode).Identifier = ((ROSLYNCS.Syntax.EventDeclarationSyntax)node).Identifier.Text;
                    break;
                case ROSLYNCS.SyntaxKind.EventFieldDeclaration:
                    dummyNode = Factory.createEventFieldDeclarationSyntaxNode();
                    break;
                case ROSLYNCS.SyntaxKind.ExplicitInterfaceSpecifier:
                    dummyNode = Factory.createExplicitInterfaceSpecifierSyntaxNode();
                    break;
                case ROSLYNCS.SyntaxKind.ExpressionStatement:
                    dummyNode = Factory.createExpressionStatementSyntaxNode();
                    break;
                case ROSLYNCS.SyntaxKind.ExternAliasDirective:
                    dummyNode = Factory.createExternAliasDirectiveSyntaxNode();
                    ((CSHARP.Nodes.Structure.ExternAliasDirectiveSyntax)dummyNode).Identifier = ((ROSLYNCS.Syntax.ExternAliasDirectiveSyntax)node).Identifier.Text;
                    break;
                case ROSLYNCS.SyntaxKind.FieldDeclaration:
                    dummyNode = Factory.createFieldDeclarationSyntaxNode();
                    break;
                case ROSLYNCS.SyntaxKind.FinallyClause:
                    dummyNode = Factory.createFinallyClauseSyntaxNode();
                    break;
                case ROSLYNCS.SyntaxKind.FixedStatement:
                    dummyNode = Factory.createFixedStatementSyntaxNode();
                    break;
                case ROSLYNCS.SyntaxKind.ForEachStatement:
                    dummyNode = Factory.createForEachStatementSyntaxNode();
                    ((CSHARP.Nodes.Statement.ForEachStatementSyntax)dummyNode).Identifier = ((ROSLYNCS.Syntax.ForEachStatementSyntax)node).Identifier.Text;
                    break;
                case ROSLYNCS.SyntaxKind.ForStatement:
                    dummyNode = Factory.createForStatementSyntaxNode();
                    break;
                case ROSLYNCS.SyntaxKind.FromClause:
                    dummyNode = Factory.createFromClauseSyntaxNode();
                    ((CSHARP.Nodes.Structure.FromClauseSyntax)dummyNode).Identifier = ((ROSLYNCS.Syntax.FromClauseSyntax)node).Identifier.Text;
                    break;
                case ROSLYNCS.SyntaxKind.GenericName:
                    dummyNode = Factory.createGenericNameSyntaxNode();
                    ((CSHARP.Nodes.Expression.GenericNameSyntax)dummyNode).Identifier = ((ROSLYNCS.Syntax.GenericNameSyntax)node).Identifier.Text;
                    break;
                case ROSLYNCS.SyntaxKind.GlobalStatement:
                    dummyNode = Factory.createGlobalStatementSyntaxNode();
                    break;
                case ROSLYNCS.SyntaxKind.GotoStatement:
                    dummyNode = Factory.createGotoStatementSyntaxNode();
                    break;
                case ROSLYNCS.SyntaxKind.GroupClause:
                    dummyNode = Factory.createGroupClauseSyntaxNode();
                    break;
                case ROSLYNCS.SyntaxKind.IdentifierName:
                    dummyNode = Factory.createIdentifierNameSyntaxNode();
                    ((CSHARP.Nodes.Expression.IdentifierNameSyntax)dummyNode).Identifier = ((ROSLYNCS.Syntax.IdentifierNameSyntax)node).Identifier.Text;
                    break;
                case ROSLYNCS.SyntaxKind.IfStatement:
                    dummyNode = Factory.createIfStatementSyntaxNode();
                    break;
                case ROSLYNCS.SyntaxKind.ImplicitArrayCreationExpression:
                    dummyNode = Factory.createImplicitArrayCreationExpressionSyntaxNode();
                    break;
                case ROSLYNCS.SyntaxKind.ImplicitElementAccess:
                    dummyNode = Factory.createImplicitElementAccessSyntaxNode();
                    break;
                case ROSLYNCS.SyntaxKind.IncompleteMember:
                    dummyNode = Factory.createIncompleteMemberSyntaxNode();
                    break;
                case ROSLYNCS.SyntaxKind.IndexerDeclaration:
                    dummyNode = Factory.createIndexerDeclarationSyntaxNode();
                    break;
                case ROSLYNCS.SyntaxKind.IndexerMemberCref:
                    dummyNode = Factory.createIndexerMemberCrefSyntaxNode();
                    break;
                case ROSLYNCS.SyntaxKind.ArrayInitializerExpression:
                case ROSLYNCS.SyntaxKind.CollectionInitializerExpression:
                case ROSLYNCS.SyntaxKind.ComplexElementInitializerExpression:
                case ROSLYNCS.SyntaxKind.ObjectInitializerExpression:
                    dummyNode = Factory.createInitializerExpressionSyntaxNode();
                    break;
                case ROSLYNCS.SyntaxKind.InterfaceDeclaration:
                    dummyNode = Factory.createInterfaceDeclarationSyntaxNode();
                    ((CSHARP.Nodes.Structure.InterfaceDeclarationSyntax)dummyNode).Identifier = ((ROSLYNCS.Syntax.InterfaceDeclarationSyntax)node).Identifier.Text;
                    break;
                case ROSLYNCS.SyntaxKind.InterpolatedStringExpression:
                    dummyNode = Factory.createInterpolatedStringExpressionSyntaxNode();
                    break;
                case ROSLYNCS.SyntaxKind.InterpolatedStringText:
                    dummyNode = Factory.createInterpolatedStringTextSyntaxNode();
                    break;
                case ROSLYNCS.SyntaxKind.Interpolation:
                    dummyNode = Factory.createInterpolationSyntaxNode();
                    break;
                case ROSLYNCS.SyntaxKind.InterpolationAlignmentClause:
                    dummyNode = Factory.createInterpolationAlignmentClauseSyntaxNode();
                    break;
                case ROSLYNCS.SyntaxKind.InterpolationFormatClause:
                    dummyNode = Factory.createInterpolationFormatClauseSyntaxNode();
                    break;
                case ROSLYNCS.SyntaxKind.InvocationExpression:
                    dummyNode = Factory.createInvocationExpressionSyntaxNode();
                    break;
                case ROSLYNCS.SyntaxKind.JoinClause:
                    dummyNode = Factory.createJoinClauseSyntaxNode();
                    ((CSHARP.Nodes.Structure.JoinClauseSyntax)dummyNode).Identifier = ((ROSLYNCS.Syntax.JoinClauseSyntax)node).Identifier.Text;
                    break;
                case ROSLYNCS.SyntaxKind.JoinIntoClause:
                    dummyNode = Factory.createJoinIntoClauseSyntaxNode();
                    ((CSHARP.Nodes.Structure.JoinIntoClauseSyntax)dummyNode).Identifier = ((ROSLYNCS.Syntax.JoinIntoClauseSyntax)node).Identifier.Text;
                    break;
                case ROSLYNCS.SyntaxKind.LabeledStatement:
                    dummyNode = Factory.createLabeledStatementSyntaxNode();
                    ((CSHARP.Nodes.Statement.LabeledStatementSyntax)dummyNode).Identifier = ((ROSLYNCS.Syntax.LabeledStatementSyntax)node).Identifier.Text;
                    break;
                case ROSLYNCS.SyntaxKind.LetClause:
                    dummyNode = Factory.createLetClauseSyntaxNode();
                    ((CSHARP.Nodes.Structure.LetClauseSyntax)dummyNode).Identifier = ((ROSLYNCS.Syntax.LetClauseSyntax)node).Identifier.Text;
                    break;
                case ROSLYNCS.SyntaxKind.NumericLiteralExpression:
                case ROSLYNCS.SyntaxKind.StringLiteralExpression:
                case ROSLYNCS.SyntaxKind.CharacterLiteralExpression:
                case ROSLYNCS.SyntaxKind.TrueLiteralExpression:
                case ROSLYNCS.SyntaxKind.FalseLiteralExpression:
                case ROSLYNCS.SyntaxKind.NullLiteralExpression:
                    dummyNode = Factory.createLiteralExpressionSyntaxNode();
                    break;
                case ROSLYNCS.SyntaxKind.LocalDeclarationStatement:
                    dummyNode = Factory.createLocalDeclarationStatementSyntaxNode();
                    break;
                case ROSLYNCS.SyntaxKind.LockStatement:
                    dummyNode = Factory.createLockStatementSyntaxNode();
                    break;
                case ROSLYNCS.SyntaxKind.MakeRefExpression:
                    dummyNode = Factory.createMakeRefExpressionSyntaxNode();
                    break;
                case ROSLYNCS.SyntaxKind.PointerMemberAccessExpression:
                case ROSLYNCS.SyntaxKind.SimpleMemberAccessExpression:
                    dummyNode = Factory.createMemberAccessExpressionSyntaxNode();
                    break;
                case ROSLYNCS.SyntaxKind.MemberBindingExpression:
                    dummyNode = Factory.createMemberBindingExpressionSyntaxNode();
                    break;
                case ROSLYNCS.SyntaxKind.MethodDeclaration:
                    dummyNode = Factory.createMethodDeclarationSyntaxNode();
                    ((CSHARP.Nodes.Structure.MethodDeclarationSyntax)dummyNode).Identifier = ((ROSLYNCS.Syntax.MethodDeclarationSyntax)node).Identifier.Text;
                    break;
                case ROSLYNCS.SyntaxKind.NameColon:
                    dummyNode = Factory.createNameColonSyntaxNode();
                    break;
                case ROSLYNCS.SyntaxKind.NameEquals:
                    dummyNode = Factory.createNameEqualsSyntaxNode();
                    break;
                case ROSLYNCS.SyntaxKind.NameMemberCref:
                    dummyNode = Factory.createNameMemberCrefSyntaxNode();
                    break;
                case ROSLYNCS.SyntaxKind.NamespaceDeclaration:
                    dummyNode = Factory.createNamespaceDeclarationSyntaxNode();
                    break;
                case ROSLYNCS.SyntaxKind.NullableType:
                    dummyNode = Factory.createNullableTypeSyntaxNode();
                    break;
                case ROSLYNCS.SyntaxKind.ObjectCreationExpression:
                    dummyNode = Factory.createObjectCreationExpressionSyntaxNode();
                    break;
                case ROSLYNCS.SyntaxKind.OmittedArraySizeExpression:
                    dummyNode = Factory.createOmittedArraySizeExpressionSyntaxNode();
                    break;
                case ROSLYNCS.SyntaxKind.OmittedTypeArgument:
                    dummyNode = Factory.createOmittedTypeArgumentSyntaxNode();
                    break;
                case ROSLYNCS.SyntaxKind.OperatorDeclaration:
                    dummyNode = Factory.createOperatorDeclarationSyntaxNode();
                    break;
                case ROSLYNCS.SyntaxKind.OperatorMemberCref:
                    dummyNode = Factory.createOperatorMemberCrefSyntaxNode();
                    break;
                case ROSLYNCS.SyntaxKind.OrderByClause:
                    dummyNode = Factory.createOrderByClauseSyntaxNode();
                    break;
                case ROSLYNCS.SyntaxKind.AscendingOrdering:
                case ROSLYNCS.SyntaxKind.DescendingOrdering:
                    dummyNode = Factory.createOrderingSyntaxNode();
                    break;
                case ROSLYNCS.SyntaxKind.Parameter:
                    dummyNode = Factory.createParameterSyntaxNode();
                    ((CSHARP.Nodes.Structure.ParameterSyntax)dummyNode).Identifier = ((ROSLYNCS.Syntax.ParameterSyntax)node).Identifier.Text;
                    break;
                case ROSLYNCS.SyntaxKind.ParameterList:
                    dummyNode = Factory.createParameterListSyntaxNode();
                    break;
                case ROSLYNCS.SyntaxKind.ParenthesizedExpression:
                    dummyNode = Factory.createParenthesizedExpressionSyntaxNode();
                    break;
                case ROSLYNCS.SyntaxKind.ParenthesizedLambdaExpression:
                    dummyNode = Factory.createParenthesizedLambdaExpressionSyntaxNode();
                    break;
                case ROSLYNCS.SyntaxKind.PointerType:
                    dummyNode = Factory.createPointerTypeSyntaxNode();
                    break;
                case ROSLYNCS.SyntaxKind.PostDecrementExpression:
                case ROSLYNCS.SyntaxKind.PostIncrementExpression:
                    dummyNode = Factory.createPostfixUnaryExpressionSyntaxNode();
                    break;
                case ROSLYNCS.SyntaxKind.PredefinedType:
                    dummyNode = Factory.createPredefinedTypeSyntaxNode();
                    break;
                case ROSLYNCS.SyntaxKind.PreDecrementExpression:
                case ROSLYNCS.SyntaxKind.PreIncrementExpression:
                    dummyNode = Factory.createPrefixUnaryExpressionSyntaxNode();
                    break;
                case ROSLYNCS.SyntaxKind.PropertyDeclaration:
                    dummyNode = Factory.createPropertyDeclarationSyntaxNode();
                    ((CSHARP.Nodes.Structure.PropertyDeclarationSyntax)dummyNode).Identifier = ((ROSLYNCS.Syntax.PropertyDeclarationSyntax)node).Identifier.Text;
                    break;
                case ROSLYNCS.SyntaxKind.QualifiedCref:
                    dummyNode = Factory.createQualifiedCrefSyntaxNode();
                    break;
                case ROSLYNCS.SyntaxKind.QualifiedName:
                    dummyNode = Factory.createQualifiedNameSyntaxNode();
                    break;
                case ROSLYNCS.SyntaxKind.QueryBody:
                    dummyNode = Factory.createQueryBodySyntaxNode();
                    break;
                case ROSLYNCS.SyntaxKind.QueryContinuation:
                    dummyNode = Factory.createQueryContinuationSyntaxNode();
                    ((CSHARP.Nodes.Structure.QueryContinuationSyntax)dummyNode).Identifier = ((ROSLYNCS.Syntax.QueryContinuationSyntax)node).Identifier.Text;
                    break;
                case ROSLYNCS.SyntaxKind.QueryExpression:
                    dummyNode = Factory.createQueryExpressionSyntaxNode();
                    break;
                case ROSLYNCS.SyntaxKind.RefTypeExpression:
                    dummyNode = Factory.createRefTypeExpressionSyntaxNode();
                    break;
                case ROSLYNCS.SyntaxKind.RefValueExpression:
                    dummyNode = Factory.createRefValueExpressionSyntaxNode();
                    break;
                case ROSLYNCS.SyntaxKind.ReturnStatement:
                    dummyNode = Factory.createReturnStatementSyntaxNode();
                    break;
                case ROSLYNCS.SyntaxKind.SelectClause:
                    dummyNode = Factory.createSelectClauseSyntaxNode();
                    break;
                case ROSLYNCS.SyntaxKind.SimpleBaseType:
                    dummyNode = Factory.createSimpleBaseTypeSyntaxNode();
                    break;
                case ROSLYNCS.SyntaxKind.SimpleLambdaExpression:
                    dummyNode = Factory.createSimpleLambdaExpressionSyntaxNode();
                    break;
                case ROSLYNCS.SyntaxKind.SizeOfExpression:
                    dummyNode = Factory.createSizeOfExpressionSyntaxNode();
                    break;
                case ROSLYNCS.SyntaxKind.StackAllocArrayCreationExpression:
                    dummyNode = Factory.createStackAllocArrayCreationExpressionSyntaxNode();
                    break;
                case ROSLYNCS.SyntaxKind.StructDeclaration:
                    dummyNode = Factory.createStructDeclarationSyntaxNode();
                    ((CSHARP.Nodes.Structure.StructDeclarationSyntax)dummyNode).Identifier = ((ROSLYNCS.Syntax.StructDeclarationSyntax)node).Identifier.Text;
                    break;
                case ROSLYNCS.SyntaxKind.SwitchSection:
                    dummyNode = Factory.createSwitchSectionSyntaxNode();
                    break;
                case ROSLYNCS.SyntaxKind.SwitchStatement:
                    dummyNode = Factory.createSwitchStatementSyntaxNode();
                    break;
                case ROSLYNCS.SyntaxKind.ThisExpression:
                    dummyNode = Factory.createThisExpressionSyntaxNode();
                    break;
                case ROSLYNCS.SyntaxKind.ThrowStatement:
                    dummyNode = Factory.createThrowStatementSyntaxNode();
                    break;
                case ROSLYNCS.SyntaxKind.TryStatement:
                    dummyNode = Factory.createTryStatementSyntaxNode();
                    break;
                case ROSLYNCS.SyntaxKind.TypeArgumentList:
                    dummyNode = Factory.createTypeArgumentListSyntaxNode();
                    break;
                case ROSLYNCS.SyntaxKind.TypeConstraint:
                    dummyNode = Factory.createTypeConstraintSyntaxNode();
                    break;
                case ROSLYNCS.SyntaxKind.TypeCref:
                    dummyNode = Factory.createTypeCrefSyntaxNode();
                    break;
                case ROSLYNCS.SyntaxKind.TypeOfExpression:
                    dummyNode = Factory.createTypeOfExpressionSyntaxNode();
                    break;
                case ROSLYNCS.SyntaxKind.TypeParameter:
                    dummyNode = Factory.createTypeParameterSyntaxNode();
                    ((CSHARP.Nodes.Structure.TypeParameterSyntax)dummyNode).Identifier = ((ROSLYNCS.Syntax.TypeParameterSyntax)node).Identifier.Text;
                    break;
                case ROSLYNCS.SyntaxKind.TypeParameterConstraintClause:
                    dummyNode = Factory.createTypeParameterConstraintClauseSyntaxNode();
                    break;
                case ROSLYNCS.SyntaxKind.TypeParameterList:
                    dummyNode = Factory.createTypeParameterListSyntaxNode();
                    break;
                case ROSLYNCS.SyntaxKind.UnsafeStatement:
                    dummyNode = Factory.createUnsafeStatementSyntaxNode();
                    break;
                case ROSLYNCS.SyntaxKind.UsingDirective:
                    dummyNode = Factory.createUsingDirectiveSyntaxNode();
                    break;
                case ROSLYNCS.SyntaxKind.UsingStatement:
                    dummyNode = Factory.createUsingStatementSyntaxNode();
                    break;
                case ROSLYNCS.SyntaxKind.VariableDeclaration:
                    dummyNode = Factory.createVariableDeclarationSyntaxNode();
                    ((CSHARP.Nodes.Structure.VariableDeclaratorSyntax)dummyNode).Identifier = ((ROSLYNCS.Syntax.VariableDeclaratorSyntax)node).Identifier.Text;
                    break;
                case ROSLYNCS.SyntaxKind.VariableDeclarator:
                    dummyNode = Factory.createVariableDeclaratorSyntaxNode();
                    break;
                case ROSLYNCS.SyntaxKind.WhereClause:
                    dummyNode = Factory.createWhereClauseSyntaxNode();
                    break;
                case ROSLYNCS.SyntaxKind.WhileStatement:
                    dummyNode = Factory.createWhileStatementSyntaxNode();
                    break;
                case ROSLYNCS.SyntaxKind.XmlCDataSection:
                    dummyNode = Factory.createXmlCDataSectionSyntaxNode();
                    break;
                case ROSLYNCS.SyntaxKind.XmlComment:
                    dummyNode = Factory.createXmlCommentSyntaxNode();
                    break;
                case ROSLYNCS.SyntaxKind.XmlCrefAttribute:
                    dummyNode = Factory.createXmlCrefAttributeSyntaxNode();
                    break;
                case ROSLYNCS.SyntaxKind.XmlElement:
                    dummyNode = Factory.createXmlElementSyntaxNode();
                    break;
                case ROSLYNCS.SyntaxKind.XmlElementEndTag:
                    dummyNode = Factory.createXmlElementEndTagSyntaxNode();
                    break;
                case ROSLYNCS.SyntaxKind.XmlElementStartTag:
                    dummyNode = Factory.createXmlElementStartTagSyntaxNode();
                    break;
                case ROSLYNCS.SyntaxKind.XmlEmptyElement:
                    dummyNode = Factory.createXmlEmptyElementSyntaxNode();
                    break;
                case ROSLYNCS.SyntaxKind.XmlName:
                    dummyNode = Factory.createXmlNameSyntaxNode();
                    break;
                case ROSLYNCS.SyntaxKind.XmlNameAttribute:
                    dummyNode = Factory.createXmlNameAttributeSyntaxNode();
                    break;
                case ROSLYNCS.SyntaxKind.XmlPrefix:
                    dummyNode = Factory.createXmlPrefixSyntaxNode();
                    break;
                case ROSLYNCS.SyntaxKind.XmlProcessingInstruction:
                    dummyNode = Factory.createXmlProcessingInstructionSyntaxNode();
                    break;
                case ROSLYNCS.SyntaxKind.XmlText:
                    dummyNode = Factory.createXmlTextSyntaxNode();
                    break;
                case ROSLYNCS.SyntaxKind.XmlTextAttribute:
                    dummyNode = Factory.createXmlTextAttributeSyntaxNode();
                    break;
                case ROSLYNCS.SyntaxKind.YieldBreakStatement:
                case ROSLYNCS.SyntaxKind.YieldReturnStatement:
                    dummyNode = Factory.createYieldStatementSyntaxNode();
                    break;
                default:
                    return null;
            }
            #endregion

            dummyNode.Position = new CSHARP.SourcePosition(
                Factory.StringTable,
                (uint)lineSpan.EndLinePosition.Character,
                (uint)lineSpan.EndLinePosition.Line,
                Commons.Common.ProcessPath(node.SyntaxTree.FilePath),
                (uint)lineSpan.StartLinePosition.Character,
                (uint)lineSpan.StartLinePosition.Line
            );

            Map.Add(node, dummyNode.Id);
            Factory.setFilteredThisNodeOnly(dummyNode.Id);
            return (T)dummyNode;
        }
    }
}
