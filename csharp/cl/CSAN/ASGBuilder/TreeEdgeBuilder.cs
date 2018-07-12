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
using Microsoft.CodeAnalysis;

namespace Columbus.CSAN
{
    using Utils;
    using CSHARP = Csharp.Asg;
    using ROSLYNCS = Microsoft.CodeAnalysis.CSharp;
    using System.Runtime.CompilerServices;
    using System;

    class TreeEdgeBuilder : ROSLYNCS.CSharpSyntaxWalker
    {
        private CSHARP.Factory Factory;
        private Dictionary<ROSLYNCS.CSharpSyntaxNode, uint> Map;

        public TreeEdgeBuilder(CSHARP.Factory fact, Dictionary<ROSLYNCS.CSharpSyntaxNode, uint> map)
        {
            Factory = fact;
            Map = map;
        }

        private string GenerateAnonymousName(ROSLYNCS.Syntax.AnonymousFunctionExpressionSyntax node)
        {
            string retType;
            string paramsType = "";

            Commons.MainDeclaration.Instance.RoslynWatch.Start();
            var symbol = (IMethodSymbol)Commons.MainDeclaration.Instance.Model.GetSymbolInfo(node).Symbol;
            Commons.MainDeclaration.Instance.RoslynWatch.Stop();

            if (symbol == null)
                return "<>f__(void)";

            if (symbol.ReturnType == null)
                retType = "void";
            else
                retType = symbol.ReturnType.ToString();

            if (symbol.Parameters != null && symbol.Parameters.Length > 0)
            {
                paramsType = ", [";
                for (int i = 0; i < symbol.Parameters.Length; i++)
                {
                    if (i != 0)
                        paramsType += ", ";
                    paramsType += symbol.Parameters[i];
                }
                paramsType += "]";
            }
            
            return string.Format("<>f__({0}{1})", retType, paramsType);
        }

        private string GenerateAnonymousName(ROSLYNCS.Syntax.AnonymousObjectCreationExpressionSyntax node)
        {
            Commons.MainDeclaration.Instance.RoslynWatch.Start();
            var symbol = Commons.MainDeclaration.Instance.Model.GetSymbolInfo(node).Symbol;
            Commons.MainDeclaration.Instance.RoslynWatch.Stop();
            return symbol != null ? symbol.ToString() : "<anonymous type>";
        }
    
        public override void Visit(SyntaxNode node)
        {
            var ournode = (CSHARP.Nodes.Base.Positioned)Factory.getRef(Map[(ROSLYNCS.CSharpSyntaxNode)node]);
            if (ournode.Position.FileNameKey == 0)
            {
                var lineSpan = node.GetLocation().GetLineSpan();
                ournode.Position = new CSHARP.SourcePosition(
                    Factory.StringTable,
                    (uint)lineSpan.EndLinePosition.Character + 1,
                    (uint)lineSpan.EndLinePosition.Line + 1,
                    Commons.Common.ProcessPath(node.SyntaxTree.FilePath),
                    (uint)lineSpan.StartLinePosition.Character + 1,
                    (uint)lineSpan.StartLinePosition.Line + 1
                );
            }

            Factory.setNotFilteredThisNodeOnly(ournode.Id);

            try
            {
                base.Visit(node);
            }
            catch (InsufficientExecutionStackException)
            {
                RuntimeHelpers.EnsureSufficientExecutionStack();
            }

            if (Commons.MainDeclaration.Instance.CurrentFileIsSoftFiltered)
                Factory.setFilteredThisNodeOnly(ournode.Id);            
        }

        public override void VisitAccessorDeclaration(ROSLYNCS.Syntax.AccessorDeclarationSyntax node)
        {
            var ournode = (CSHARP.Nodes.Structure.AccessorDeclarationSyntax)Factory.getRef(Map[node]);
            if (node.Body != null)
                ournode.setBody(Map[node.Body]);
            foreach (var AttributeList in node.AttributeLists)
                ournode.addAttributeLists(Map[AttributeList]);
            //get, set, add, remove
            ournode.Identifier = node.Keyword.Text;
            base.VisitAccessorDeclaration(node);
        }

        public override void VisitAccessorList(ROSLYNCS.Syntax.AccessorListSyntax node)
        {
            var ournode = (CSHARP.Nodes.Structure.AccessorListSyntax)Factory.getRef(Map[node]);
            foreach (var Accessor in node.Accessors)
                ournode.addAccessors(Map[Accessor]);
            base.VisitAccessorList(node);
        }

        public override void VisitAnonymousMethodExpression(ROSLYNCS.Syntax.AnonymousMethodExpressionSyntax node)
        {
            var ournode = (CSHARP.Nodes.Expression.AnonymousMethodExpressionSyntax)Factory.getRef(Map[node]);
            if (node.Body != null)
                ournode.setBody(Map[node.Body]);
            if (node.ParameterList != null)
                ournode.setParameterList(Map[node.ParameterList]);
            ournode.Identifier = GenerateAnonymousName(node);
            base.VisitAnonymousMethodExpression(node);
        }

        public override void VisitAnonymousObjectCreationExpression(ROSLYNCS.Syntax.AnonymousObjectCreationExpressionSyntax node)
        {
            var ournode = (CSHARP.Nodes.Expression.AnonymousObjectCreationExpressionSyntax)Factory.getRef(Map[node]);
            foreach (var Initializer in node.Initializers)
                ournode.addInitializers(Map[Initializer]);
            ournode.Identifier = GenerateAnonymousName(node);
            base.VisitAnonymousObjectCreationExpression(node);
        }

        public override void VisitAnonymousObjectMemberDeclarator(ROSLYNCS.Syntax.AnonymousObjectMemberDeclaratorSyntax node)
        {
            var ournode = (CSHARP.Nodes.Structure.AnonymousObjectMemberDeclaratorSyntax)Factory.getRef(Map[node]);
            if (node.Expression != null)
                ournode.setExpression(Map[node.Expression]);
            if (node.NameEquals != null)
                ournode.setNameEquals(Map[node.NameEquals]);
            base.VisitAnonymousObjectMemberDeclarator(node);
        }

        public override void VisitArgument(ROSLYNCS.Syntax.ArgumentSyntax node)
        {
            var ournode = (CSHARP.Nodes.Structure.ArgumentSyntax)Factory.getRef(Map[node]);
            if (node.Expression != null)
                ournode.setExpression(Map[node.Expression]);
            if (node.NameColon != null)
                ournode.setNameColon(Map[node.NameColon]);
            base.VisitArgument(node);
        }

        public override void VisitArgumentList(ROSLYNCS.Syntax.ArgumentListSyntax node)
        {
            var ournode = (CSHARP.Nodes.Structure.ArgumentListSyntax)Factory.getRef(Map[node]);
            foreach (var Argument in node.Arguments)
                ournode.addArguments(Map[Argument]);
            base.VisitArgumentList(node);
        }

        public override void VisitArrayCreationExpression(ROSLYNCS.Syntax.ArrayCreationExpressionSyntax node)
        {
            var ournode = (CSHARP.Nodes.Expression.ArrayCreationExpressionSyntax)Factory.getRef(Map[node]);
            if (node.Initializer != null)
                ournode.setInitializer(Map[node.Initializer]);
            if (node.Type != null)
                ournode.setType(Map[node.Type]);
            base.VisitArrayCreationExpression(node);
        }

        public override void VisitArrayRankSpecifier(ROSLYNCS.Syntax.ArrayRankSpecifierSyntax node)
        {
            var ournode = (CSHARP.Nodes.Structure.ArrayRankSpecifierSyntax)Factory.getRef(Map[node]);
            foreach (var Size in node.Sizes)
                ournode.addSizes(Map[Size]);
            base.VisitArrayRankSpecifier(node);
        }

        public override void VisitArrowExpressionClause(ROSLYNCS.Syntax.ArrowExpressionClauseSyntax node)
        {
            var ournode = (CSHARP.Nodes.Structure.ArrowExpressionClauseSyntax)Factory.getRef(Map[node]);
            if (node.Expression != null)
                ournode.setExpression(Map[node.Expression]);
            base.VisitArrowExpressionClause(node);
        }

        public override void VisitAssignmentExpression(ROSLYNCS.Syntax.AssignmentExpressionSyntax node)
        {
            var ournode = (CSHARP.Nodes.Expression.AssignmentExpressionSyntax)Factory.getRef(Map[node]);
            if (node.Left != null)
                ournode.setLeft(Map[node.Left]);
            if (node.Right != null)
                ournode.setRight(Map[node.Right]);
            base.VisitAssignmentExpression(node);
        }

        public override void VisitAttribute(ROSLYNCS.Syntax.AttributeSyntax node)
        {
            var ournode = (CSHARP.Nodes.Structure.AttributeSyntax)Factory.getRef(Map[node]);
            if (node.ArgumentList != null)
                ournode.setArgumentList(Map[node.ArgumentList]);
            if (node.Name != null)
                ournode.setName(Map[node.Name]);
            base.VisitAttribute(node);
        }

        public override void VisitAttributeArgument(ROSLYNCS.Syntax.AttributeArgumentSyntax node)
        {
            var ournode = (CSHARP.Nodes.Structure.AttributeArgumentSyntax)Factory.getRef(Map[node]);
            if (node.Expression != null)
                ournode.setExpression(Map[node.Expression]);
            if (node.NameColon != null)
                ournode.setNameColon(Map[node.NameColon]);
            if (node.NameEquals != null)
                ournode.setNameEquals(Map[node.NameEquals]);
            base.VisitAttributeArgument(node);
        }

        public override void VisitAttributeArgumentList(ROSLYNCS.Syntax.AttributeArgumentListSyntax node)
        {
            var ournode = (CSHARP.Nodes.Structure.AttributeArgumentListSyntax)Factory.getRef(Map[node]);
            foreach (var Argument in node.Arguments)
                ournode.addArguments(Map[Argument]);
            base.VisitAttributeArgumentList(node);
        }

        public override void VisitAttributeList(ROSLYNCS.Syntax.AttributeListSyntax node)
        {
            var ournode = (CSHARP.Nodes.Structure.AttributeListSyntax)Factory.getRef(Map[node]);
            if (node.Target != null)
                ournode.setTarget(Map[node.Target]);
            foreach (var Attribute in node.Attributes)
                ournode.addAttributes(Map[Attribute]);
            base.VisitAttributeList(node);
        }

        public override void VisitAttributeTargetSpecifier(ROSLYNCS.Syntax.AttributeTargetSpecifierSyntax node)
        {
            var ournode = (CSHARP.Nodes.Structure.AttributeTargetSpecifierSyntax)Factory.getRef(Map[node]);
            ournode.Identifier = node.Identifier.Text;
            base.VisitAttributeTargetSpecifier(node);
        }

        public override void VisitAwaitExpression(ROSLYNCS.Syntax.AwaitExpressionSyntax node)
        {
            var ournode = (CSHARP.Nodes.Expression.AwaitExpressionSyntax)Factory.getRef(Map[node]);
            if (node.Expression != null)
                ournode.setExpression(Map[node.Expression]);
            base.VisitAwaitExpression(node);
        }

        public override void VisitBaseExpression(ROSLYNCS.Syntax.BaseExpressionSyntax node)
        {
            var ournode = (CSHARP.Nodes.Expression.BaseExpressionSyntax)Factory.getRef(Map[node]);
            base.VisitBaseExpression(node);
        }

        public override void VisitBaseList(ROSLYNCS.Syntax.BaseListSyntax node)
        {
            var ournode = (CSHARP.Nodes.Structure.BaseListSyntax)Factory.getRef(Map[node]);
            foreach (var Type in node.Types)
                ournode.addTypes(Map[Type]);
            base.VisitBaseList(node);
        }

        public override void VisitBinaryExpression(ROSLYNCS.Syntax.BinaryExpressionSyntax node)
        {
            var ournode = (CSHARP.Nodes.Expression.BinaryExpressionSyntax)Factory.getRef(Map[node]);
            if (node.Left != null)
                ournode.setLeft(Map[node.Left]);
            if (node.Right != null)
                ournode.setRight(Map[node.Right]);
            base.VisitBinaryExpression(node);
        }

        public override void VisitBlock(ROSLYNCS.Syntax.BlockSyntax node)
        {
            var ournode = (CSHARP.Nodes.Statement.BlockSyntax)Factory.getRef(Map[node]);
            foreach (var Statement in node.Statements)
                ournode.addStatements(Map[Statement]);
            base.VisitBlock(node);
        }

        public override void VisitBracketedArgumentList(ROSLYNCS.Syntax.BracketedArgumentListSyntax node)
        {
            var ournode = (CSHARP.Nodes.Structure.BracketedArgumentListSyntax)Factory.getRef(Map[node]);
            foreach (var Argument in node.Arguments)
                ournode.addArguments(Map[Argument]);
            base.VisitBracketedArgumentList(node);
        }

        public override void VisitBracketedParameterList(ROSLYNCS.Syntax.BracketedParameterListSyntax node)
        {
            var ournode = (CSHARP.Nodes.Structure.BracketedParameterListSyntax)Factory.getRef(Map[node]);
            foreach (var Parameter in node.Parameters)
                ournode.addParameters(Map[Parameter]);
            base.VisitBracketedParameterList(node);
        }

        public override void VisitBreakStatement(ROSLYNCS.Syntax.BreakStatementSyntax node)
        {
            var ournode = (CSHARP.Nodes.Statement.BreakStatementSyntax)Factory.getRef(Map[node]);
            base.VisitBreakStatement(node);
        }

        public override void VisitCaseSwitchLabel(ROSLYNCS.Syntax.CaseSwitchLabelSyntax node)
        {
            var ournode = (CSHARP.Nodes.Structure.CaseSwitchLabelSyntax)Factory.getRef(Map[node]);
            if (node.Value != null)
                ournode.setValue(Map[node.Value]);
            base.VisitCaseSwitchLabel(node);
        }

        public override void VisitCastExpression(ROSLYNCS.Syntax.CastExpressionSyntax node)
        {
            var ournode = (CSHARP.Nodes.Expression.CastExpressionSyntax)Factory.getRef(Map[node]);
            if (node.Expression != null)
                ournode.setExpression(Map[node.Expression]);
            if (node.Type != null)
                ournode.setType(Map[node.Type]);
            base.VisitCastExpression(node);
        }

        public override void VisitCatchClause(ROSLYNCS.Syntax.CatchClauseSyntax node)
        {
            var ournode = (CSHARP.Nodes.Structure.CatchClauseSyntax)Factory.getRef(Map[node]);
            if (node.Block != null)
                ournode.setBlock(Map[node.Block]);
            if (node.Declaration != null)
                ournode.setDeclaration(Map[node.Declaration]);
            if (node.Filter != null)
                ournode.setFilter(Map[node.Filter]);
            base.VisitCatchClause(node);
        }

        public override void VisitCatchDeclaration(ROSLYNCS.Syntax.CatchDeclarationSyntax node)
        {
            var ournode = (CSHARP.Nodes.Structure.CatchDeclarationSyntax)Factory.getRef(Map[node]);
            if (node.Type != null)
                ournode.setType(Map[node.Type]);
            base.VisitCatchDeclaration(node);
        }

        public override void VisitCatchFilterClause(ROSLYNCS.Syntax.CatchFilterClauseSyntax node)
        {
            var ournode = (CSHARP.Nodes.Structure.CatchFilterClauseSyntax)Factory.getRef(Map[node]);
            if (node.FilterExpression != null)
                ournode.setFilterExpression(Map[node.FilterExpression]);
            base.VisitCatchFilterClause(node);
        }

        public override void VisitCheckedExpression(ROSLYNCS.Syntax.CheckedExpressionSyntax node)
        {
            var ournode = (CSHARP.Nodes.Expression.CheckedExpressionSyntax)Factory.getRef(Map[node]);
            if (node.Expression != null)
                ournode.setExpression(Map[node.Expression]);
            base.VisitCheckedExpression(node);
        }

        public override void VisitCheckedStatement(ROSLYNCS.Syntax.CheckedStatementSyntax node)
        {
            var ournode = (CSHARP.Nodes.Statement.CheckedStatementSyntax)Factory.getRef(Map[node]);
            if (node.Block != null)
                ournode.setBlock(Map[node.Block]);
            base.VisitCheckedStatement(node);
        }

        public override void VisitClassOrStructConstraint(ROSLYNCS.Syntax.ClassOrStructConstraintSyntax node)
        {
            var ournode = (CSHARP.Nodes.Structure.ClassOrStructConstraintSyntax)Factory.getRef(Map[node]);
            base.VisitClassOrStructConstraint(node);
        }

        public override void VisitCompilationUnit(ROSLYNCS.Syntax.CompilationUnitSyntax node)
        {
            var ournode = (CSHARP.Nodes.Structure.CompilationUnitSyntax)Factory.getRef(Map[node]);
            foreach (var AttributeList in node.AttributeLists)
                ournode.addAttributeLists(Map[AttributeList]);
            foreach (var Extern in node.Externs)
                ournode.addExterns(Map[Extern]);
            foreach (var Member in node.Members)
                ournode.addMembers(Map[Member]);
            foreach (var Using in node.Usings)
                ournode.addUsings(Map[Using]);

            base.VisitCompilationUnit(node);

            var path = node.GetLocation().GetLineSpan().Path;
            if (path.Contains(Constants.TEMP) && path.Contains(Constants.NET) && path.Contains(Constants.COMMA))
                Factory.setFiltered(ournode.Id);
        }

        public override void VisitConditionalAccessExpression(ROSLYNCS.Syntax.ConditionalAccessExpressionSyntax node)
        {
            var ournode = (CSHARP.Nodes.Expression.ConditionalAccessExpressionSyntax)Factory.getRef(Map[node]);
            if (node.Expression != null)
                ournode.setExpression(Map[node.Expression]);
            if (node.WhenNotNull != null)
                ournode.setWhenNotNull(Map[node.WhenNotNull]);
            base.VisitConditionalAccessExpression(node);
        }

        public override void VisitConditionalExpression(ROSLYNCS.Syntax.ConditionalExpressionSyntax node)
        {
            var ournode = (CSHARP.Nodes.Expression.ConditionalExpressionSyntax)Factory.getRef(Map[node]);
            if (node.Condition != null)
                ournode.setCondition(Map[node.Condition]);
            if (node.WhenFalse != null)
                ournode.setWhenFalse(Map[node.WhenFalse]);
            if (node.WhenTrue != null)
                ournode.setWhenTrue(Map[node.WhenTrue]);
            base.VisitConditionalExpression(node);
        }

        public override void VisitConstructorConstraint(ROSLYNCS.Syntax.ConstructorConstraintSyntax node)
        {
            var ournode = (CSHARP.Nodes.Structure.ConstructorConstraintSyntax)Factory.getRef(Map[node]);
            base.VisitConstructorConstraint(node);
        }

        public override void VisitConstructorDeclaration(ROSLYNCS.Syntax.ConstructorDeclarationSyntax node)
        {
            var ournode = (CSHARP.Nodes.Structure.ConstructorDeclarationSyntax)Factory.getRef(Map[node]);
            if (node.Body != null)
                ournode.setBody(Map[node.Body]);
            if (node.Initializer != null)
                ournode.setInitializer(Map[node.Initializer]);
            if (node.ParameterList != null)
                ournode.setParameterList(Map[node.ParameterList]);
            ournode.Identifier = node.Identifier.Text;
            foreach (var AttributeList in node.AttributeLists)
                ournode.addAttributeLists(Map[AttributeList]);
            base.VisitConstructorDeclaration(node);
        }

        public override void VisitConstructorInitializer(ROSLYNCS.Syntax.ConstructorInitializerSyntax node)
        {
            var ournode = (CSHARP.Nodes.Structure.ConstructorInitializerSyntax)Factory.getRef(Map[node]);
            if (node.ArgumentList != null)
                ournode.setArgumentList(Map[node.ArgumentList]);
            base.VisitConstructorInitializer(node);
        }

        public override void VisitContinueStatement(ROSLYNCS.Syntax.ContinueStatementSyntax node)
        {
            var ournode = (CSHARP.Nodes.Statement.ContinueStatementSyntax)Factory.getRef(Map[node]);
            base.VisitContinueStatement(node);
        }

        public override void VisitConversionOperatorDeclaration(ROSLYNCS.Syntax.ConversionOperatorDeclarationSyntax node)
        {
            var ournode = (CSHARP.Nodes.Structure.ConversionOperatorDeclarationSyntax)Factory.getRef(Map[node]);
            if (node.Body != null)
                ournode.setBody(Map[node.Body]);
            if (node.ExpressionBody != null)
                ournode.setExpressionBody(Map[node.ExpressionBody]);
            if (node.ParameterList != null)
                ournode.setParameterList(Map[node.ParameterList]);
            if (node.Type != null)
                ournode.setType(Map[node.Type]);
            foreach (var AttributeList in node.AttributeLists)
                ournode.addAttributeLists(Map[AttributeList]);
            base.VisitConversionOperatorDeclaration(node);
        }

        public override void VisitConversionOperatorMemberCref(ROSLYNCS.Syntax.ConversionOperatorMemberCrefSyntax node)
        {
            var ournode = (CSHARP.Nodes.Structure.ConversionOperatorMemberCrefSyntax)Factory.getRef(Map[node]);
            if (node.Parameters != null)
                ournode.setParameters(Map[node.Parameters]);
            if (node.Type != null)
                ournode.setType(Map[node.Type]);
            base.VisitConversionOperatorMemberCref(node);
        }

        public override void VisitCrefBracketedParameterList(ROSLYNCS.Syntax.CrefBracketedParameterListSyntax node)
        {
            var ournode = (CSHARP.Nodes.Structure.CrefBracketedParameterListSyntax)Factory.getRef(Map[node]);
            foreach (var Parameter in node.Parameters)
                ournode.addParameters(Map[Parameter]);
            base.VisitCrefBracketedParameterList(node);
        }

        public override void VisitCrefParameter(ROSLYNCS.Syntax.CrefParameterSyntax node)
        {
            var ournode = (CSHARP.Nodes.Structure.CrefParameterSyntax)Factory.getRef(Map[node]);
            if (node.Type != null)
                ournode.setType(Map[node.Type]);
            base.VisitCrefParameter(node);
        }

        public override void VisitCrefParameterList(ROSLYNCS.Syntax.CrefParameterListSyntax node)
        {
            var ournode = (CSHARP.Nodes.Structure.CrefParameterListSyntax)Factory.getRef(Map[node]);
            foreach (var Parameter in node.Parameters)
                ournode.addParameters(Map[Parameter]);
            base.VisitCrefParameterList(node);
        }

        public override void VisitDefaultExpression(ROSLYNCS.Syntax.DefaultExpressionSyntax node)
        {
            var ournode = (CSHARP.Nodes.Expression.DefaultExpressionSyntax)Factory.getRef(Map[node]);
            if (node.Type != null)
                ournode.setType(Map[node.Type]);
            base.VisitDefaultExpression(node);
        }

        public override void VisitDefaultSwitchLabel(ROSLYNCS.Syntax.DefaultSwitchLabelSyntax node)
        {
            var ournode = (CSHARP.Nodes.Structure.DefaultSwitchLabelSyntax)Factory.getRef(Map[node]);
            base.VisitDefaultSwitchLabel(node);
        }

        public override void VisitDelegateDeclaration(ROSLYNCS.Syntax.DelegateDeclarationSyntax node)
        {
            var ournode = (CSHARP.Nodes.Structure.DelegateDeclarationSyntax)Factory.getRef(Map[node]);
            if (node.ParameterList != null)
                ournode.setParameterList(Map[node.ParameterList]);
            if (node.ReturnType != null)
                ournode.setReturnType(Map[node.ReturnType]);
            ournode.Identifier = node.Identifier.Text;
            foreach (var AttributeList in node.AttributeLists)
                ournode.addAttributeLists(Map[AttributeList]);
            foreach (var ConstraintClause in node.ConstraintClauses)
                ournode.addConstraintClauses(Map[ConstraintClause]);
            base.VisitDelegateDeclaration(node);
        }

        public override void VisitDestructorDeclaration(ROSLYNCS.Syntax.DestructorDeclarationSyntax node)
        {
            var ournode = (CSHARP.Nodes.Structure.DestructorDeclarationSyntax)Factory.getRef(Map[node]);
            if (node.Body != null)
                ournode.setBody(Map[node.Body]);
            if (node.ParameterList != null)
                ournode.setParameterList(Map[node.ParameterList]);
            ournode.Identifier = node.Identifier.Text;
            foreach (var AttributeList in node.AttributeLists)
                ournode.addAttributeLists(Map[AttributeList]);
            base.VisitDestructorDeclaration(node);
        }

        public override void VisitDoStatement(ROSLYNCS.Syntax.DoStatementSyntax node)
        {
            var ournode = (CSHARP.Nodes.Statement.DoStatementSyntax)Factory.getRef(Map[node]);
            if (node.Condition != null)
                ournode.setCondition(Map[node.Condition]);
            if (node.Statement != null)
                ournode.setStatement(Map[node.Statement]);
            base.VisitDoStatement(node);
        }

        public override void VisitElementAccessExpression(ROSLYNCS.Syntax.ElementAccessExpressionSyntax node)
        {
            var ournode = (CSHARP.Nodes.Expression.ElementAccessExpressionSyntax)Factory.getRef(Map[node]);
            if (node.ArgumentList != null)
                ournode.setArgumentList(Map[node.ArgumentList]);
            if (node.Expression != null)
                ournode.setExpression(Map[node.Expression]);
            base.VisitElementAccessExpression(node);
        }

        public override void VisitElementBindingExpression(ROSLYNCS.Syntax.ElementBindingExpressionSyntax node)
        {
            var ournode = (CSHARP.Nodes.Expression.ElementBindingExpressionSyntax)Factory.getRef(Map[node]);
            if (node.ArgumentList != null)
                ournode.setArgumentList(Map[node.ArgumentList]);
            base.VisitElementBindingExpression(node);
        }

        public override void VisitElseClause(ROSLYNCS.Syntax.ElseClauseSyntax node)
        {
            var ournode = (CSHARP.Nodes.Structure.ElseClauseSyntax)Factory.getRef(Map[node]);
            if (node.Statement != null)
                ournode.setStatement(Map[node.Statement]);
            base.VisitElseClause(node);
        }

        public override void VisitEmptyStatement(ROSLYNCS.Syntax.EmptyStatementSyntax node)
        {
            var ournode = (CSHARP.Nodes.Statement.EmptyStatementSyntax)Factory.getRef(Map[node]);
            base.VisitEmptyStatement(node);
        }

        public override void VisitEnumDeclaration(ROSLYNCS.Syntax.EnumDeclarationSyntax node)
        {
            var ournode = (CSHARP.Nodes.Structure.EnumDeclarationSyntax)Factory.getRef(Map[node]);
            if (node.BaseList != null)
                ournode.setBaseList(Map[node.BaseList]);
            ournode.Identifier = node.Identifier.Text;
            foreach (var AttributeList in node.AttributeLists)
                ournode.addAttributeLists(Map[AttributeList]);
            foreach (var Member in node.Members)
                ournode.addMembers(Map[Member]);
            base.VisitEnumDeclaration(node);
        }

        public override void VisitEnumMemberDeclaration(ROSLYNCS.Syntax.EnumMemberDeclarationSyntax node)
        {
            var ournode = (CSHARP.Nodes.Structure.EnumMemberDeclarationSyntax)Factory.getRef(Map[node]);
            if (node.EqualsValue != null)
                ournode.setEqualsValue(Map[node.EqualsValue]);
            ournode.Identifier = node.Identifier.Text;
            foreach (var AttributeList in node.AttributeLists)
                ournode.addAttributeLists(Map[AttributeList]);
            base.VisitEnumMemberDeclaration(node);
        }

        public override void VisitEqualsValueClause(ROSLYNCS.Syntax.EqualsValueClauseSyntax node)
        {
            var ournode = (CSHARP.Nodes.Structure.EqualsValueClauseSyntax)Factory.getRef(Map[node]);
            if (node.Value != null)
                ournode.setValue(Map[node.Value]);
            base.VisitEqualsValueClause(node);
        }

        public override void VisitEventFieldDeclaration(ROSLYNCS.Syntax.EventFieldDeclarationSyntax node)
        {
            var ournode = (CSHARP.Nodes.Structure.EventFieldDeclarationSyntax)Factory.getRef(Map[node]);
            if (node.Declaration != null)
                ournode.setDeclaration(Map[node.Declaration]);
            foreach (var AttributeList in node.AttributeLists)
                ournode.addAttributeLists(Map[AttributeList]);
            base.VisitEventFieldDeclaration(node);
        }

        public override void VisitExplicitInterfaceSpecifier(ROSLYNCS.Syntax.ExplicitInterfaceSpecifierSyntax node)
        {
            var ournode = (CSHARP.Nodes.Structure.ExplicitInterfaceSpecifierSyntax)Factory.getRef(Map[node]);
            if (node.Name != null)
                ournode.setName(Map[node.Name]);
            base.VisitExplicitInterfaceSpecifier(node);
        }

        public override void VisitExpressionStatement(ROSLYNCS.Syntax.ExpressionStatementSyntax node)
        {
            var ournode = (CSHARP.Nodes.Statement.ExpressionStatementSyntax)Factory.getRef(Map[node]);
            if (node.Expression != null)
                ournode.setExpression(Map[node.Expression]);
            base.VisitExpressionStatement(node);
        }

        public override void VisitExternAliasDirective(ROSLYNCS.Syntax.ExternAliasDirectiveSyntax node)
        {
            var ournode = (CSHARP.Nodes.Structure.ExternAliasDirectiveSyntax)Factory.getRef(Map[node]);
            ournode.Identifier = node.Identifier.Text;
            base.VisitExternAliasDirective(node);
        }

        public override void VisitFieldDeclaration(ROSLYNCS.Syntax.FieldDeclarationSyntax node)
        {
            var ournode = (CSHARP.Nodes.Structure.FieldDeclarationSyntax)Factory.getRef(Map[node]);
            if (node.Declaration != null)
                ournode.setDeclaration(Map[node.Declaration]);
            foreach (var AttributeList in node.AttributeLists)
                ournode.addAttributeLists(Map[AttributeList]);
            base.VisitFieldDeclaration(node);
        }

        public override void VisitFinallyClause(ROSLYNCS.Syntax.FinallyClauseSyntax node)
        {
            var ournode = (CSHARP.Nodes.Structure.FinallyClauseSyntax)Factory.getRef(Map[node]);
            if (node.Block != null)
                ournode.setBlock(Map[node.Block]);
            base.VisitFinallyClause(node);
        }

        public override void VisitFixedStatement(ROSLYNCS.Syntax.FixedStatementSyntax node)
        {
            var ournode = (CSHARP.Nodes.Statement.FixedStatementSyntax)Factory.getRef(Map[node]);
            if (node.Declaration != null)
                ournode.setDeclaration(Map[node.Declaration]);
            if (node.Statement != null)
                ournode.setStatement(Map[node.Statement]);
            base.VisitFixedStatement(node);
        }

        public override void VisitForEachStatement(ROSLYNCS.Syntax.ForEachStatementSyntax node)
        {
            var ournode = (CSHARP.Nodes.Statement.ForEachStatementSyntax)Factory.getRef(Map[node]);
            if (node.Expression != null)
                ournode.setExpression(Map[node.Expression]);
            if (node.Statement != null)
                ournode.setStatement(Map[node.Statement]);
            if (node.Type != null)
                ournode.setType(Map[node.Type]);
            ournode.Identifier = node.Identifier.Text;
            base.VisitForEachStatement(node);
        }

        public override void VisitForStatement(ROSLYNCS.Syntax.ForStatementSyntax node)
        {
            var ournode = (CSHARP.Nodes.Statement.ForStatementSyntax)Factory.getRef(Map[node]);
            if (node.Condition != null)
                ournode.setCondition(Map[node.Condition]);
            if (node.Declaration != null)
                ournode.setDeclaration(Map[node.Declaration]);
            if (node.Statement != null)
                ournode.setStatement(Map[node.Statement]);
            foreach (var Incrementor in node.Incrementors)
                ournode.addIncrementors(Map[Incrementor]);
            foreach (var Initializer in node.Initializers)
                ournode.addInitializers(Map[Initializer]);
            base.VisitForStatement(node);
        }

        public override void VisitFromClause(ROSLYNCS.Syntax.FromClauseSyntax node)
        {
            var ournode = (CSHARP.Nodes.Structure.FromClauseSyntax)Factory.getRef(Map[node]);
            if (node.Expression != null)
                ournode.setExpression(Map[node.Expression]);
            if (node.Type != null)
                ournode.setType(Map[node.Type]);
            ournode.Identifier = node.Identifier.Text;
            base.VisitFromClause(node);
        }

        public override void VisitGlobalStatement(ROSLYNCS.Syntax.GlobalStatementSyntax node)
        {
            var ournode = (CSHARP.Nodes.Structure.GlobalStatementSyntax)Factory.getRef(Map[node]);
            if (node.Statement != null)
                ournode.setStatement(Map[node.Statement]);
            base.VisitGlobalStatement(node);
        }

        public override void VisitGotoStatement(ROSLYNCS.Syntax.GotoStatementSyntax node)
        {
            var ournode = (CSHARP.Nodes.Statement.GotoStatementSyntax)Factory.getRef(Map[node]);
            if (node.Expression != null)
                ournode.setExpression(Map[node.Expression]);
            base.VisitGotoStatement(node);
        }

        public override void VisitGroupClause(ROSLYNCS.Syntax.GroupClauseSyntax node)
        {
            var ournode = (CSHARP.Nodes.Structure.GroupClauseSyntax)Factory.getRef(Map[node]);
            if (node.ByExpression != null)
                ournode.setByExpression(Map[node.ByExpression]);
            if (node.GroupExpression != null)
                ournode.setGroupExpression(Map[node.GroupExpression]);
            base.VisitGroupClause(node);
        }

        public override void VisitIfStatement(ROSLYNCS.Syntax.IfStatementSyntax node)
        {
            var ournode = (CSHARP.Nodes.Statement.IfStatementSyntax)Factory.getRef(Map[node]);
            if (node.Condition != null)
                ournode.setCondition(Map[node.Condition]);
            if (node.Else != null)
                ournode.setElse(Map[node.Else]);
            if (node.Statement != null)
                ournode.setStatement(Map[node.Statement]);
            base.VisitIfStatement(node);
        }

        public override void VisitImplicitArrayCreationExpression(ROSLYNCS.Syntax.ImplicitArrayCreationExpressionSyntax node)
        {
            var ournode = (CSHARP.Nodes.Expression.ImplicitArrayCreationExpressionSyntax)Factory.getRef(Map[node]);
            if (node.Initializer != null)
                ournode.setInitializer(Map[node.Initializer]);
            base.VisitImplicitArrayCreationExpression(node);
        }

        public override void VisitImplicitElementAccess(ROSLYNCS.Syntax.ImplicitElementAccessSyntax node)
        {
            var ournode = (CSHARP.Nodes.Expression.ImplicitElementAccessSyntax)Factory.getRef(Map[node]);
            if (node.ArgumentList != null)
                ournode.setArgumentList(Map[node.ArgumentList]);
            base.VisitImplicitElementAccess(node);
        }

        public override void VisitIncompleteMember(ROSLYNCS.Syntax.IncompleteMemberSyntax node)
        {
            var ournode = (CSHARP.Nodes.Structure.IncompleteMemberSyntax)Factory.getRef(Map[node]);
            if (node.Type != null)
                ournode.setType(Map[node.Type]);
            foreach (var AttributeList in node.AttributeLists)
                ournode.addAttributeLists(Map[AttributeList]);
            base.VisitIncompleteMember(node);
        }

        public override void VisitIndexerDeclaration(ROSLYNCS.Syntax.IndexerDeclarationSyntax node)
        {
            var ournode = (CSHARP.Nodes.Structure.IndexerDeclarationSyntax)Factory.getRef(Map[node]);
            if (node.AccessorList != null)
                ournode.setAccessorList(Map[node.AccessorList]);
            if (node.ExplicitInterfaceSpecifier != null)
                ournode.setExplicitInterfaceSpecifier(Map[node.ExplicitInterfaceSpecifier]);
            if (node.ExpressionBody != null)
                ournode.setExpressionBody(Map[node.ExpressionBody]);
            if (node.ParameterList != null)
                ournode.setParameterList(Map[node.ParameterList]);
            if (node.Type != null)
                ournode.setType(Map[node.Type]);
            foreach (var AttributeList in node.AttributeLists)
                ournode.addAttributeLists(Map[AttributeList]);
            base.VisitIndexerDeclaration(node);
        }

        public override void VisitIndexerMemberCref(ROSLYNCS.Syntax.IndexerMemberCrefSyntax node)
        {
            var ournode = (CSHARP.Nodes.Structure.IndexerMemberCrefSyntax)Factory.getRef(Map[node]);
            if (node.Parameters != null)
                ournode.setParameters(Map[node.Parameters]);
            base.VisitIndexerMemberCref(node);
        }

        public override void VisitInitializerExpression(ROSLYNCS.Syntax.InitializerExpressionSyntax node)
        {
            var ournode = (CSHARP.Nodes.Expression.InitializerExpressionSyntax)Factory.getRef(Map[node]);
            foreach (var Expression in node.Expressions)
                ournode.addExpressions(Map[Expression]);
            base.VisitInitializerExpression(node);
        }

        public override void VisitInterfaceDeclaration(ROSLYNCS.Syntax.InterfaceDeclarationSyntax node)
        {
            var ournode = (CSHARP.Nodes.Structure.InterfaceDeclarationSyntax)Factory.getRef(Map[node]);
            if (node.BaseList != null)
                ournode.setBaseList(Map[node.BaseList]);
            if (node.TypeParameterList != null)
                ournode.setTypeParameterList(Map[node.TypeParameterList]);
            ournode.Identifier = node.Identifier.Text;
            foreach (var AttributeList in node.AttributeLists)
                ournode.addAttributeLists(Map[AttributeList]);
            foreach (var ConstraintClause in node.ConstraintClauses)
                ournode.addConstraintClauses(Map[ConstraintClause]);
            foreach (var Member in node.Members)
                ournode.addMembers(Map[Member]);
            base.VisitInterfaceDeclaration(node);
        }
        public override void VisitInterpolatedStringExpression(ROSLYNCS.Syntax.InterpolatedStringExpressionSyntax node)
        {
            var ournode = (CSHARP.Nodes.Expression.InterpolatedStringExpressionSyntax)Factory.getRef(Map[node]);
            foreach (var Content in node.Contents)
                ournode.addContents(Map[Content]);
            base.VisitInterpolatedStringExpression(node);
        }

        public override void VisitInterpolatedStringText(ROSLYNCS.Syntax.InterpolatedStringTextSyntax node)
        {
            var ournode = (CSHARP.Nodes.Structure.InterpolatedStringTextSyntax)Factory.getRef(Map[node]);
            //TODO: text token?
            base.VisitInterpolatedStringText(node);
        }

        public override void VisitInterpolation(ROSLYNCS.Syntax.InterpolationSyntax node)
        {
            var ournode = (CSHARP.Nodes.Structure.InterpolationSyntax)Factory.getRef(Map[node]);
            if (node.AlignmentClause != null)
                ournode.setAlignmentClause(Map[node.AlignmentClause]);
            if (node.Expression != null)
                ournode.setExpression(Map[node.Expression]);
            if (node.FormatClause != null)
                ournode.setFormatClause(Map[node.FormatClause]);
            base.VisitInterpolation(node);
        }

        public override void VisitInterpolationAlignmentClause(ROSLYNCS.Syntax.InterpolationAlignmentClauseSyntax node)
        {
            var ournode = (CSHARP.Nodes.Structure.InterpolationAlignmentClauseSyntax)Factory.getRef(Map[node]);
            if (node.Value != null)
                ournode.setValue(Map[node.Value]);
            base.VisitInterpolationAlignmentClause(node);
        }

        public override void VisitInterpolationFormatClause(ROSLYNCS.Syntax.InterpolationFormatClauseSyntax node)
        {
            var ournode = (CSHARP.Nodes.Structure.InterpolationFormatClauseSyntax)Factory.getRef(Map[node]);
            //TODO format string token?
            base.VisitInterpolationFormatClause(node);
        }

        public override void VisitInvocationExpression(ROSLYNCS.Syntax.InvocationExpressionSyntax node)
        {
            var ournode = (CSHARP.Nodes.Expression.InvocationExpressionSyntax)Factory.getRef(Map[node]);
            if (node.ArgumentList != null)
                ournode.setArgumentList(Map[node.ArgumentList]);
            if (node.Expression != null)
                ournode.setExpression(Map[node.Expression]);
            base.VisitInvocationExpression(node);
        }

        public override void VisitJoinClause(ROSLYNCS.Syntax.JoinClauseSyntax node)
        {
            var ournode = (CSHARP.Nodes.Structure.JoinClauseSyntax)Factory.getRef(Map[node]);
            if (node.InExpression != null)
                ournode.setInExpression(Map[node.InExpression]);
            if (node.Into != null)
                ournode.setInto(Map[node.Into]);
            if (node.LeftExpression != null)
                ournode.setLeftExpression(Map[node.LeftExpression]);
            if (node.RightExpression != null)
                ournode.setRightExpression(Map[node.RightExpression]);
            if (node.Type != null)
                ournode.setType(Map[node.Type]);
            ournode.Identifier = node.Identifier.Text;
            base.VisitJoinClause(node);
        }

        public override void VisitJoinIntoClause(ROSLYNCS.Syntax.JoinIntoClauseSyntax node)
        {
            var ournode = (CSHARP.Nodes.Structure.JoinIntoClauseSyntax)Factory.getRef(Map[node]);
            ournode.Identifier = node.Identifier.Text;
            base.VisitJoinIntoClause(node);
        }

        public override void VisitLabeledStatement(ROSLYNCS.Syntax.LabeledStatementSyntax node)
        {
            var ournode = (CSHARP.Nodes.Statement.LabeledStatementSyntax)Factory.getRef(Map[node]);
            if (node.Statement != null)
                ournode.setStatement(Map[node.Statement]);
            ournode.Identifier = node.Identifier.Text;
            base.VisitLabeledStatement(node);
        }

        public override void VisitLetClause(ROSLYNCS.Syntax.LetClauseSyntax node)
        {
            var ournode = (CSHARP.Nodes.Structure.LetClauseSyntax)Factory.getRef(Map[node]);
            if (node.Expression != null)
                ournode.setExpression(Map[node.Expression]);
            ournode.Identifier = node.Identifier.Text;
            base.VisitLetClause(node);
        }

        public override void VisitLiteralExpression(ROSLYNCS.Syntax.LiteralExpressionSyntax node)
        {
            var ournode = (CSHARP.Nodes.Expression.LiteralExpressionSyntax)Factory.getRef(Map[node]);
            ournode.Token = node.Token.Text;
            base.VisitLiteralExpression(node);
        }

        public override void VisitLocalDeclarationStatement(ROSLYNCS.Syntax.LocalDeclarationStatementSyntax node)
        {
            var ournode = (CSHARP.Nodes.Statement.LocalDeclarationStatementSyntax)Factory.getRef(Map[node]);
            if (node.Declaration != null)
                ournode.setDeclaration(Map[node.Declaration]);
            base.VisitLocalDeclarationStatement(node);
        }

        public override void VisitLockStatement(ROSLYNCS.Syntax.LockStatementSyntax node)
        {
            var ournode = (CSHARP.Nodes.Statement.LockStatementSyntax)Factory.getRef(Map[node]);
            if (node.Expression != null)
                ournode.setExpression(Map[node.Expression]);
            if (node.Statement != null)
                ournode.setStatement(Map[node.Statement]);
            base.VisitLockStatement(node);
        }

        public override void VisitMakeRefExpression(ROSLYNCS.Syntax.MakeRefExpressionSyntax node)
        {
            var ournode = (CSHARP.Nodes.Expression.MakeRefExpressionSyntax)Factory.getRef(Map[node]);
            if (node.Expression != null)
                ournode.setExpression(Map[node.Expression]);
            base.VisitMakeRefExpression(node);
        }

        public override void VisitMemberAccessExpression(ROSLYNCS.Syntax.MemberAccessExpressionSyntax node)
        {
            var ournode = (CSHARP.Nodes.Expression.MemberAccessExpressionSyntax)Factory.getRef(Map[node]);
            if (node.Expression != null)
                ournode.setExpression(Map[node.Expression]);
            if (node.Name != null)
                ournode.setName(Map[node.Name]);
            base.VisitMemberAccessExpression(node);
        }

        public override void VisitMemberBindingExpression(ROSLYNCS.Syntax.MemberBindingExpressionSyntax node)
        {
            var ournode = (CSHARP.Nodes.Expression.MemberBindingExpressionSyntax)Factory.getRef(Map[node]);
            if (node.Name != null)
                ournode.setName(Map[node.Name]);
            base.VisitMemberBindingExpression(node);
        }

        public override void VisitMethodDeclaration(ROSLYNCS.Syntax.MethodDeclarationSyntax node)
        {
            var ournode = (CSHARP.Nodes.Structure.MethodDeclarationSyntax)Factory.getRef(Map[node]);
            if (node.Body != null)
                ournode.setBody(Map[node.Body]);
            if (node.ExplicitInterfaceSpecifier != null)
                ournode.setExplicitInterfaceSpecifier(Map[node.ExplicitInterfaceSpecifier]);
            if (node.ExpressionBody != null)
                ournode.setExpressionBody(Map[node.ExpressionBody]);
            if (node.ParameterList != null)
                ournode.setParameterList(Map[node.ParameterList]);
            if (node.ReturnType != null)
                ournode.setReturnType(Map[node.ReturnType]);
            ournode.Identifier = node.Identifier.Text;

            //var symbol = Model.GetDeclaredSymbol(node);
            //symbol.

            foreach (var AttributeList in node.AttributeLists)
                ournode.addAttributeLists(Map[AttributeList]);
            foreach (var ConstraintClause in node.ConstraintClauses)
                ournode.addConstraintClauses(Map[ConstraintClause]);
            base.VisitMethodDeclaration(node);
        }

        public override void VisitNameColon(ROSLYNCS.Syntax.NameColonSyntax node)
        {
            var ournode = (CSHARP.Nodes.Structure.NameColonSyntax)Factory.getRef(Map[node]);
            if (node.Name != null)
                ournode.setName(Map[node.Name]);
            base.VisitNameColon(node);
        }

        public override void VisitNameEquals(ROSLYNCS.Syntax.NameEqualsSyntax node)
        {
            var ournode = (CSHARP.Nodes.Structure.NameEqualsSyntax)Factory.getRef(Map[node]);
            if (node.Name != null)
                ournode.setName(Map[node.Name]);
            base.VisitNameEquals(node);
        }

        public override void VisitNameMemberCref(ROSLYNCS.Syntax.NameMemberCrefSyntax node)
        {
            var ournode = (CSHARP.Nodes.Structure.NameMemberCrefSyntax)Factory.getRef(Map[node]);
            if (node.Name != null)
                ournode.setName(Map[node.Name]);
            if (node.Parameters != null)
                ournode.setParameters(Map[node.Parameters]);
            base.VisitNameMemberCref(node);
        }

        public override void VisitNamespaceDeclaration(ROSLYNCS.Syntax.NamespaceDeclarationSyntax node)
        {
            var ournode = (CSHARP.Nodes.Structure.NamespaceDeclarationSyntax)Factory.getRef(Map[node]);
            if (node.Name != null)
                ournode.setName(Map[node.Name]);
            foreach (var Extern in node.Externs)
                ournode.addExterns(Map[Extern]);
            foreach (var Member in node.Members)
                ournode.addMembers(Map[Member]);
            foreach (var Using in node.Usings)
                ournode.addUsings(Map[Using]);
            base.VisitNamespaceDeclaration(node);
        }

        public override void VisitObjectCreationExpression(ROSLYNCS.Syntax.ObjectCreationExpressionSyntax node)
        {
            var ournode = (CSHARP.Nodes.Expression.ObjectCreationExpressionSyntax)Factory.getRef(Map[node]);
            if (node.ArgumentList != null)
                ournode.setArgumentList(Map[node.ArgumentList]);
            if (node.Initializer != null)
                ournode.setInitializer(Map[node.Initializer]);
            if (node.Type != null)
                ournode.setType(Map[node.Type]);
            base.VisitObjectCreationExpression(node);
        }

        public override void VisitOmittedArraySizeExpression(ROSLYNCS.Syntax.OmittedArraySizeExpressionSyntax node)
        {
            var ournode = (CSHARP.Nodes.Expression.OmittedArraySizeExpressionSyntax)Factory.getRef(Map[node]);
            base.VisitOmittedArraySizeExpression(node);
        }


        public override void VisitOperatorDeclaration(ROSLYNCS.Syntax.OperatorDeclarationSyntax node)
        {
            var ournode = (CSHARP.Nodes.Structure.OperatorDeclarationSyntax)Factory.getRef(Map[node]);
            if (node.Body != null)
                ournode.setBody(Map[node.Body]);
            if (node.ExpressionBody != null)
                ournode.setExpressionBody(Map[node.ExpressionBody]);
            if (node.ParameterList != null)
                ournode.setParameterList(Map[node.ParameterList]);
            if (node.ReturnType != null)
                ournode.setReturnType(Map[node.ReturnType]);
            foreach (var AttributeList in node.AttributeLists)
                ournode.addAttributeLists(Map[AttributeList]);
            base.VisitOperatorDeclaration(node);
        }

        public override void VisitOperatorMemberCref(ROSLYNCS.Syntax.OperatorMemberCrefSyntax node)
        {
            var ournode = (CSHARP.Nodes.Structure.OperatorMemberCrefSyntax)Factory.getRef(Map[node]);
            if (node.Parameters != null)
                ournode.setParameters(Map[node.Parameters]);
            base.VisitOperatorMemberCref(node);
        }

        public override void VisitOrderByClause(ROSLYNCS.Syntax.OrderByClauseSyntax node)
        {
            var ournode = (CSHARP.Nodes.Structure.OrderByClauseSyntax)Factory.getRef(Map[node]);
            foreach (var Ordering in node.Orderings)
                ournode.addOrderings(Map[Ordering]);
            base.VisitOrderByClause(node);
        }

        public override void VisitOrdering(ROSLYNCS.Syntax.OrderingSyntax node)
        {
            var ournode = (CSHARP.Nodes.Structure.OrderingSyntax)Factory.getRef(Map[node]);
            if (node.Expression != null)
                ournode.setExpression(Map[node.Expression]);
            base.VisitOrdering(node);
        }

        public override void VisitParameter(ROSLYNCS.Syntax.ParameterSyntax node)
        {
            var ournode = (CSHARP.Nodes.Structure.ParameterSyntax)Factory.getRef(Map[node]);
            if (node.Default != null)
                ournode.setDefault(Map[node.Default]);
            if (node.Type != null)
                ournode.setType(Map[node.Type]);
            ournode.Identifier = node.Identifier.Text;
            base.VisitParameter(node);
        }

        public override void VisitParameterList(ROSLYNCS.Syntax.ParameterListSyntax node)
        {
            var ournode = (CSHARP.Nodes.Structure.ParameterListSyntax)Factory.getRef(Map[node]);
            foreach (var Parameter in node.Parameters)
                ournode.addParameters(Map[Parameter]);
            base.VisitParameterList(node);
        }

        public override void VisitParenthesizedExpression(ROSLYNCS.Syntax.ParenthesizedExpressionSyntax node)
        {
            var ournode = (CSHARP.Nodes.Expression.ParenthesizedExpressionSyntax)Factory.getRef(Map[node]);
            if (node.Expression != null)
                ournode.setExpression(Map[node.Expression]);
            base.VisitParenthesizedExpression(node);
        }

        public override void VisitParenthesizedLambdaExpression(ROSLYNCS.Syntax.ParenthesizedLambdaExpressionSyntax node)
        {
            var ournode = (CSHARP.Nodes.Expression.ParenthesizedLambdaExpressionSyntax)Factory.getRef(Map[node]);
            if (node.Body != null)
                ournode.setBody(Map[node.Body]);
            if (node.ParameterList != null)
                ournode.setParameterList(Map[node.ParameterList]);
            ournode.Identifier = GenerateAnonymousName(node);
            base.VisitParenthesizedLambdaExpression(node);
        }

        public override void VisitPostfixUnaryExpression(ROSLYNCS.Syntax.PostfixUnaryExpressionSyntax node)
        {
            var ournode = (CSHARP.Nodes.Expression.PostfixUnaryExpressionSyntax)Factory.getRef(Map[node]);
            if (node.Operand != null)
                ournode.setOperand(Map[node.Operand]);
            base.VisitPostfixUnaryExpression(node);
        }

        public override void VisitPrefixUnaryExpression(ROSLYNCS.Syntax.PrefixUnaryExpressionSyntax node)
        {
            var ournode = (CSHARP.Nodes.Expression.PrefixUnaryExpressionSyntax)Factory.getRef(Map[node]);
            if (node.Operand != null)
                ournode.setOperand(Map[node.Operand]);
            base.VisitPrefixUnaryExpression(node);
        }

        public override void VisitPropertyDeclaration(ROSLYNCS.Syntax.PropertyDeclarationSyntax node)
        {
            var ournode = (CSHARP.Nodes.Structure.PropertyDeclarationSyntax)Factory.getRef(Map[node]);
            if (node.AccessorList != null)
                ournode.setAccessorList(Map[node.AccessorList]);
            if (node.ExplicitInterfaceSpecifier != null)
                ournode.setExplicitInterfaceSpecifier(Map[node.ExplicitInterfaceSpecifier]);
            if (node.ExpressionBody != null)
                ournode.setExpressionBody(Map[node.ExpressionBody]);
            if (node.Initializer != null)
                ournode.setInitializer(Map[node.Initializer]);
            if (node.Type != null)
                ournode.setType(Map[node.Type]);
            ournode.Identifier = node.Identifier.Text;
            foreach (var AttributeList in node.AttributeLists)
                ournode.addAttributeLists(Map[AttributeList]);
            base.VisitPropertyDeclaration(node);
        }

        public override void VisitQualifiedCref(ROSLYNCS.Syntax.QualifiedCrefSyntax node)
        {
            var ournode = (CSHARP.Nodes.Structure.QualifiedCrefSyntax)Factory.getRef(Map[node]);
            if (node.Container != null)
                ournode.setContainer(Map[node.Container]);
            if (node.Member != null)
                ournode.setMember(Map[node.Member]);
            base.VisitQualifiedCref(node);
        }

        public override void VisitQueryBody(ROSLYNCS.Syntax.QueryBodySyntax node)
        {
            var ournode = (CSHARP.Nodes.Structure.QueryBodySyntax)Factory.getRef(Map[node]);
            if (node.Continuation != null)
                ournode.setContinuation(Map[node.Continuation]);
            if (node.SelectOrGroup != null)
                ournode.setSelectOrGroup(Map[node.SelectOrGroup]);
            foreach (var Clause in node.Clauses)
                ournode.addClauses(Map[Clause]);
            base.VisitQueryBody(node);
        }

        public override void VisitQueryContinuation(ROSLYNCS.Syntax.QueryContinuationSyntax node)
        {
            var ournode = (CSHARP.Nodes.Structure.QueryContinuationSyntax)Factory.getRef(Map[node]);
            if (node.Body != null)
                ournode.setBody(Map[node.Body]);
            ournode.Identifier = node.Identifier.Text;
            base.VisitQueryContinuation(node);
        }

        public override void VisitQueryExpression(ROSLYNCS.Syntax.QueryExpressionSyntax node)
        {
            var ournode = (CSHARP.Nodes.Expression.QueryExpressionSyntax)Factory.getRef(Map[node]);
            if (node.Body != null)
                ournode.setBody(Map[node.Body]);
            if (node.FromClause != null)
                ournode.setFromClause(Map[node.FromClause]);
            base.VisitQueryExpression(node);
        }

        public override void VisitRefTypeExpression(ROSLYNCS.Syntax.RefTypeExpressionSyntax node)
        {
            var ournode = (CSHARP.Nodes.Expression.RefTypeExpressionSyntax)Factory.getRef(Map[node]);
            if (node.Expression != null)
                ournode.setExpression(Map[node.Expression]);
            base.VisitRefTypeExpression(node);
        }

        public override void VisitRefValueExpression(ROSLYNCS.Syntax.RefValueExpressionSyntax node)
        {
            var ournode = (CSHARP.Nodes.Expression.RefValueExpressionSyntax)Factory.getRef(Map[node]);
            if (node.Expression != null)
                ournode.setExpression(Map[node.Expression]);
            if (node.Type != null)
                ournode.setType(Map[node.Type]);
            base.VisitRefValueExpression(node);
        }

        public override void VisitReturnStatement(ROSLYNCS.Syntax.ReturnStatementSyntax node)
        {
            var ournode = (CSHARP.Nodes.Statement.ReturnStatementSyntax)Factory.getRef(Map[node]);
            if (node.Expression != null)
                ournode.setExpression(Map[node.Expression]);
            base.VisitReturnStatement(node);
        }

        public override void VisitSelectClause(ROSLYNCS.Syntax.SelectClauseSyntax node)
        {
            var ournode = (CSHARP.Nodes.Structure.SelectClauseSyntax)Factory.getRef(Map[node]);
            if (node.Expression != null)
                ournode.setExpression(Map[node.Expression]);
            base.VisitSelectClause(node);
        }

        public override void VisitSimpleBaseType(ROSLYNCS.Syntax.SimpleBaseTypeSyntax node)
        {
            var ournode = (CSHARP.Nodes.Structure.SimpleBaseTypeSyntax)Factory.getRef(Map[node]);
            if (node.Type != null)
                ournode.setType(Map[node.Type]);
            base.VisitSimpleBaseType(node);
        }

        public override void VisitSimpleLambdaExpression(ROSLYNCS.Syntax.SimpleLambdaExpressionSyntax node)
        {
            var ournode = (CSHARP.Nodes.Expression.SimpleLambdaExpressionSyntax)Factory.getRef(Map[node]);
            if (node.Body != null)
                ournode.setBody(Map[node.Body]);
            if (node.Parameter != null)
                ournode.setParameter(Map[node.Parameter]);
            ournode.Identifier = GenerateAnonymousName(node);
            base.VisitSimpleLambdaExpression(node);
        }

        public override void VisitSizeOfExpression(ROSLYNCS.Syntax.SizeOfExpressionSyntax node)
        {
            var ournode = (CSHARP.Nodes.Expression.SizeOfExpressionSyntax)Factory.getRef(Map[node]);
            if (node.Type != null)
                ournode.setType(Map[node.Type]);
            base.VisitSizeOfExpression(node);
        }

        public override void VisitStackAllocArrayCreationExpression(ROSLYNCS.Syntax.StackAllocArrayCreationExpressionSyntax node)
        {
            var ournode = (CSHARP.Nodes.Expression.StackAllocArrayCreationExpressionSyntax)Factory.getRef(Map[node]);
            if (node.Type != null)
                ournode.setType(Map[node.Type]);
            base.VisitStackAllocArrayCreationExpression(node);
        }

        public override void VisitStructDeclaration(ROSLYNCS.Syntax.StructDeclarationSyntax node)
        {
            var ournode = (CSHARP.Nodes.Structure.StructDeclarationSyntax)Factory.getRef(Map[node]);
            if (node.BaseList != null)
                ournode.setBaseList(Map[node.BaseList]);
            if (node.TypeParameterList != null)
                ournode.setTypeParameterList(Map[node.TypeParameterList]);
            ournode.Identifier = node.Identifier.Text;
            foreach (var AttributeList in node.AttributeLists)
                ournode.addAttributeLists(Map[AttributeList]);
            foreach (var ConstraintClause in node.ConstraintClauses)
                ournode.addConstraintClauses(Map[ConstraintClause]);
            foreach (var Member in node.Members)
                ournode.addMembers(Map[Member]);
            base.VisitStructDeclaration(node);
        }

        public override void VisitSwitchSection(ROSLYNCS.Syntax.SwitchSectionSyntax node)
        {
            var ournode = (CSHARP.Nodes.Structure.SwitchSectionSyntax)Factory.getRef(Map[node]);
            foreach (var Label in node.Labels)
                ournode.addLabels(Map[Label]);
            foreach (var Statement in node.Statements)
                ournode.addStatements(Map[Statement]);
            base.VisitSwitchSection(node);
        }

        public override void VisitSwitchStatement(ROSLYNCS.Syntax.SwitchStatementSyntax node)
        {
            var ournode = (CSHARP.Nodes.Statement.SwitchStatementSyntax)Factory.getRef(Map[node]);
            if (node.Expression != null)
                ournode.setExpression(Map[node.Expression]);
            foreach (var Section in node.Sections)
                ournode.addSections(Map[Section]);
            base.VisitSwitchStatement(node);
        }

        public override void VisitThisExpression(ROSLYNCS.Syntax.ThisExpressionSyntax node)
        {
            var ournode = (CSHARP.Nodes.Expression.ThisExpressionSyntax)Factory.getRef(Map[node]);
            base.VisitThisExpression(node);
        }

        public override void VisitThrowStatement(ROSLYNCS.Syntax.ThrowStatementSyntax node)
        {
            var ournode = (CSHARP.Nodes.Statement.ThrowStatementSyntax)Factory.getRef(Map[node]);
            if (node.Expression != null)
                ournode.setExpression(Map[node.Expression]);
            base.VisitThrowStatement(node);
        }

        public override void VisitTryStatement(ROSLYNCS.Syntax.TryStatementSyntax node)
        {
            var ournode = (CSHARP.Nodes.Statement.TryStatementSyntax)Factory.getRef(Map[node]);
            if (node.Block != null)
                ournode.setBlock(Map[node.Block]);
            if (node.Finally != null)
                ournode.setFinally(Map[node.Finally]);
            foreach (var Catche in node.Catches)
                ournode.addCatches(Map[Catche]);
            base.VisitTryStatement(node);
        }

        public override void VisitTypeArgumentList(ROSLYNCS.Syntax.TypeArgumentListSyntax node)
        {
            var ournode = (CSHARP.Nodes.Structure.TypeArgumentListSyntax)Factory.getRef(Map[node]);
            foreach (var Argument in node.Arguments)
                ournode.addArguments(Map[Argument]);
            base.VisitTypeArgumentList(node);
        }

        public override void VisitTypeConstraint(ROSLYNCS.Syntax.TypeConstraintSyntax node)
        {
            var ournode = (CSHARP.Nodes.Structure.TypeConstraintSyntax)Factory.getRef(Map[node]);
            if (node.Type != null)
                ournode.setType(Map[node.Type]);
            base.VisitTypeConstraint(node);
        }

        public override void VisitTypeCref(ROSLYNCS.Syntax.TypeCrefSyntax node)
        {
            var ournode = (CSHARP.Nodes.Structure.TypeCrefSyntax)Factory.getRef(Map[node]);
            if (node.Type != null)
                ournode.setType(Map[node.Type]);
            base.VisitTypeCref(node);
        }

        public override void VisitTypeOfExpression(ROSLYNCS.Syntax.TypeOfExpressionSyntax node)
        {
            var ournode = (CSHARP.Nodes.Expression.TypeOfExpressionSyntax)Factory.getRef(Map[node]);
            if (node.Type != null)
                ournode.setType(Map[node.Type]);
            base.VisitTypeOfExpression(node);
        }

        public override void VisitTypeParameter(ROSLYNCS.Syntax.TypeParameterSyntax node)
        {
            var ournode = (CSHARP.Nodes.Structure.TypeParameterSyntax)Factory.getRef(Map[node]);
            ournode.Identifier = node.Identifier.Text;
            foreach (var AttributeList in node.AttributeLists)
                ournode.addAttributeLists(Map[AttributeList]);
            base.VisitTypeParameter(node);
        }

        public override void VisitTypeParameterConstraintClause(ROSLYNCS.Syntax.TypeParameterConstraintClauseSyntax node)
        {
            var ournode = (CSHARP.Nodes.Structure.TypeParameterConstraintClauseSyntax)Factory.getRef(Map[node]);
            if (node.Name != null)
                ournode.setName(Map[node.Name]);
            foreach (var Constraint in node.Constraints)
                ournode.addConstraints(Map[Constraint]);
            base.VisitTypeParameterConstraintClause(node);
        }

        public override void VisitTypeParameterList(ROSLYNCS.Syntax.TypeParameterListSyntax node)
        {
            var ournode = (CSHARP.Nodes.Structure.TypeParameterListSyntax)Factory.getRef(Map[node]);
            foreach (var Parameter in node.Parameters)
                ournode.addParameters(Map[Parameter]);
            base.VisitTypeParameterList(node);
        }

        public override void VisitUnsafeStatement(ROSLYNCS.Syntax.UnsafeStatementSyntax node)
        {
            var ournode = (CSHARP.Nodes.Statement.UnsafeStatementSyntax)Factory.getRef(Map[node]);
            if (node.Block != null)
                ournode.setBlock(Map[node.Block]);
            base.VisitUnsafeStatement(node);
        }

        public override void VisitUsingDirective(ROSLYNCS.Syntax.UsingDirectiveSyntax node)
        {
            var ournode = (CSHARP.Nodes.Structure.UsingDirectiveSyntax)Factory.getRef(Map[node]);
            if (node.Alias != null)
                ournode.setAlias(Map[node.Alias]);
            if (node.Name != null)
                ournode.setName(Map[node.Name]);
            base.VisitUsingDirective(node);
        }

        public override void VisitUsingStatement(ROSLYNCS.Syntax.UsingStatementSyntax node)
        {
            var ournode = (CSHARP.Nodes.Statement.UsingStatementSyntax)Factory.getRef(Map[node]);
            if (node.Declaration != null)
                ournode.setDeclaration(Map[node.Declaration]);
            if (node.Expression != null)
                ournode.setExpression(Map[node.Expression]);
            if (node.Statement != null)
                ournode.setStatement(Map[node.Statement]);
            base.VisitUsingStatement(node);
        }

        public override void VisitVariableDeclaration(ROSLYNCS.Syntax.VariableDeclarationSyntax node)
        {
            var ournode = (CSHARP.Nodes.Structure.VariableDeclarationSyntax)Factory.getRef(Map[node]);
            if (node.Type != null)
                ournode.setType(Map[node.Type]);
            foreach (var Variable in node.Variables)
                ournode.addVariables(Map[Variable]);
            base.VisitVariableDeclaration(node);
        }

        public override void VisitVariableDeclarator(ROSLYNCS.Syntax.VariableDeclaratorSyntax node)
        {
            var ournode = (CSHARP.Nodes.Structure.VariableDeclaratorSyntax)Factory.getRef(Map[node]);
            if (node.ArgumentList != null)
                ournode.setArgumentList(Map[node.ArgumentList]);
            if (node.Initializer != null)
                ournode.setInitializer(Map[node.Initializer]);
            ournode.Identifier = node.Identifier.Text;
            base.VisitVariableDeclarator(node);
        }

        public override void VisitWhereClause(ROSLYNCS.Syntax.WhereClauseSyntax node)
        {
            var ournode = (CSHARP.Nodes.Structure.WhereClauseSyntax)Factory.getRef(Map[node]);
            if (node.Condition != null)
                ournode.setCondition(Map[node.Condition]);
            base.VisitWhereClause(node);
        }

        public override void VisitWhileStatement(ROSLYNCS.Syntax.WhileStatementSyntax node)
        {
            var ournode = (CSHARP.Nodes.Statement.WhileStatementSyntax)Factory.getRef(Map[node]);
            if (node.Condition != null)
                ournode.setCondition(Map[node.Condition]);
            if (node.Statement != null)
                ournode.setStatement(Map[node.Statement]);
            base.VisitWhileStatement(node);
        }

        public override void VisitXmlComment(ROSLYNCS.Syntax.XmlCommentSyntax node)
        {
            var ournode = (CSHARP.Nodes.Structure.XmlCommentSyntax)Factory.getRef(Map[node]);
            base.VisitXmlComment(node);
        }

        public override void VisitXmlCrefAttribute(ROSLYNCS.Syntax.XmlCrefAttributeSyntax node)
        {
            var ournode = (CSHARP.Nodes.Structure.XmlCrefAttributeSyntax)Factory.getRef(Map[node]);
            if (node.Cref != null)
                ournode.setCref(Map[node.Cref]);
            if (node.Name != null)
                ournode.setName(Map[node.Name]);
            base.VisitXmlCrefAttribute(node);
        }

        public override void VisitXmlCDataSection(ROSLYNCS.Syntax.XmlCDataSectionSyntax node)
        {
            var ournode = (CSHARP.Nodes.Structure.XmlCDataSectionSyntax)Factory.getRef(Map[node]);
            //TODO text token?
            base.VisitXmlCDataSection(node);
        }

        public override void VisitXmlElement(ROSLYNCS.Syntax.XmlElementSyntax node)
        {
            var ournode = (CSHARP.Nodes.Structure.XmlElementSyntax)Factory.getRef(Map[node]);
            if (node.EndTag != null)
                ournode.setEndTag(Map[node.EndTag]);
            if (node.StartTag != null)
                ournode.setStartTag(Map[node.StartTag]);
            foreach (var asd in node.Content)
                ournode.addContent(Map[asd]);
            base.VisitXmlElement(node);
        }

        public override void VisitXmlElementEndTag(ROSLYNCS.Syntax.XmlElementEndTagSyntax node)
        {
            var ournode = (CSHARP.Nodes.Structure.XmlElementEndTagSyntax)Factory.getRef(Map[node]);
            if (node.Name != null)
                ournode.setName(Map[node.Name]);
            base.VisitXmlElementEndTag(node);
        }

        public override void VisitXmlElementStartTag(ROSLYNCS.Syntax.XmlElementStartTagSyntax node)
        {
            var ournode = (CSHARP.Nodes.Structure.XmlElementStartTagSyntax)Factory.getRef(Map[node]);
            if (node.Name != null)
                ournode.setName(Map[node.Name]);
            foreach (var Attribute in node.Attributes)
                ournode.addAttributes(Map[Attribute]);
            base.VisitXmlElementStartTag(node);
        }

        public override void VisitXmlEmptyElement(ROSLYNCS.Syntax.XmlEmptyElementSyntax node)
        {
            var ournode = (CSHARP.Nodes.Structure.XmlEmptyElementSyntax)Factory.getRef(Map[node]);
            if (node.Name != null)
                ournode.setName(Map[node.Name]);
            foreach (var Attribute in node.Attributes)
                ournode.addAttributes(Map[Attribute]);
            base.VisitXmlEmptyElement(node);
        }

        public override void VisitXmlName(ROSLYNCS.Syntax.XmlNameSyntax node)
        {
            var ournode = (CSHARP.Nodes.Structure.XmlNameSyntax)Factory.getRef(Map[node]);
            if (node.Prefix != null)
                ournode.setPrefix(Map[node.Prefix]);
            base.VisitXmlName(node);
        }

        public override void VisitXmlNameAttribute(ROSLYNCS.Syntax.XmlNameAttributeSyntax node)
        {
            var ournode = (CSHARP.Nodes.Structure.XmlNameAttributeSyntax)Factory.getRef(Map[node]);
            if (node.Identifier != null)
                ournode.setIdentifier(Map[node.Identifier]);
            if (node.Name != null)
                ournode.setName(Map[node.Name]);
            base.VisitXmlNameAttribute(node);
        }

        public override void VisitXmlPrefix(ROSLYNCS.Syntax.XmlPrefixSyntax node)
        {
            var ournode = (CSHARP.Nodes.Structure.XmlPrefixSyntax)Factory.getRef(Map[node]);
            base.VisitXmlPrefix(node);
        }

        public override void VisitXmlProcessingInstruction(ROSLYNCS.Syntax.XmlProcessingInstructionSyntax node)
        {
            var ournode = (CSHARP.Nodes.Structure.XmlProcessingInstructionSyntax)Factory.getRef(Map[node]);
            if (node.Name != null)
                ournode.setName(Map[node.Name]);
            base.VisitXmlProcessingInstruction(node);
        }

        public override void VisitXmlText(ROSLYNCS.Syntax.XmlTextSyntax node)
        {
            var ournode = (CSHARP.Nodes.Structure.XmlTextSyntax)Factory.getRef(Map[node]);
            base.VisitXmlText(node);
        }

        public override void VisitXmlTextAttribute(ROSLYNCS.Syntax.XmlTextAttributeSyntax node)
        {
            var ournode = (CSHARP.Nodes.Structure.XmlTextAttributeSyntax)Factory.getRef(Map[node]);
            if (node.Name != null)
                ournode.setName(Map[node.Name]);
            base.VisitXmlTextAttribute(node);
        }

        public override void VisitYieldStatement(ROSLYNCS.Syntax.YieldStatementSyntax node)
        {
            var ournode = (CSHARP.Nodes.Statement.YieldStatementSyntax)Factory.getRef(Map[node]);
            if (node.Expression != null)
                ournode.setExpression(Map[node.Expression]);
            base.VisitYieldStatement(node);
        }

        public override void VisitAliasQualifiedName(ROSLYNCS.Syntax.AliasQualifiedNameSyntax node)
        {
            var ournode = Factory.getRef(Map[node]) as CSHARP::Nodes.Expression.AliasQualifiedNameSyntax;
            if (node.Alias != null)
                ournode.setAlias(Map[node.Alias]);
            if (node.Name != null)
                ournode.setName(Map[node.Name]);

            //TODO
            //Mire kéne mutatnia? Using? NamespaceDeclaration? egyik se BaseTypeDeclaration
            //A syntax maga pl    global::System.Console.WriteLine()    vagy    using Cs = System.Console; Cs::WriteLine();
            //Annyiban különbözik a sima ponttól, hogy megengedi a globalt-t

            //ournode.setOriginalDefinition();

            base.VisitAliasQualifiedName(node);
        }

        public override void VisitArrayType(ROSLYNCS.Syntax.ArrayTypeSyntax node)
        {
            var ournode = (CSHARP.Nodes.Expression.ArrayTypeSyntax)Factory.getRef(Map[node]);
            if (node.ElementType != null)
                ournode.setElementType(Map[node.ElementType]);
            foreach (var RankSpecifier in node.RankSpecifiers)
                ournode.addRankSpecifiers(Map[RankSpecifier]);

            base.VisitArrayType(node);
        }

        public override void VisitClassDeclaration(ROSLYNCS.Syntax.ClassDeclarationSyntax node)
        {
            var ournode = (CSHARP.Nodes.Structure.ClassDeclarationSyntax)Factory.getRef(Map[node]);
            if (node.BaseList != null)
                ournode.setBaseList(Map[node.BaseList]);
            if (node.TypeParameterList != null)
                ournode.setTypeParameterList(Map[node.TypeParameterList]);
            ournode.Identifier = node.Identifier.Text;
            foreach (var AttributeList in node.AttributeLists)
                ournode.addAttributeLists(Map[AttributeList]);
            foreach (var ConstraintClause in node.ConstraintClauses)
                ournode.addConstraintClauses(Map[ConstraintClause]);
            foreach (var Member in node.Members)
                ournode.addMembers(Map[Member]);

            base.VisitClassDeclaration(node);
        }

        public override void VisitEventDeclaration(ROSLYNCS.Syntax.EventDeclarationSyntax node)
        {
            var ournode = (CSHARP.Nodes.Structure.EventDeclarationSyntax)Factory.getRef(Map[node]);
            if (node.AccessorList != null)
                ournode.setAccessorList(Map[node.AccessorList]);
            if (node.ExplicitInterfaceSpecifier != null)
                ournode.setExplicitInterfaceSpecifier(Map[node.ExplicitInterfaceSpecifier]);
            if (node.Type != null)
                ournode.setType(Map[node.Type]);
            ournode.Identifier = node.Identifier.Text;
            foreach (var AttributeList in node.AttributeLists)
                ournode.addAttributeLists(Map[AttributeList]);

            base.VisitEventDeclaration(node);
        }

        public override void VisitGenericName(ROSLYNCS.Syntax.GenericNameSyntax node)
        {
            var ournode = (CSHARP.Nodes.Expression.GenericNameSyntax)Factory.getRef(Map[node]);
            if (node.TypeArgumentList != null)
                ournode.setTypeArgumentList(Map[node.TypeArgumentList]);
            ournode.Identifier = node.Identifier.Text;

            base.VisitGenericName(node);
        }

        public override void VisitIdentifierName(ROSLYNCS.Syntax.IdentifierNameSyntax node)
        {
            var ournode = (CSHARP.Nodes.Expression.IdentifierNameSyntax)Factory.getRef(Map[node]);
            ournode.Identifier = node.Identifier.Text;

            base.VisitIdentifierName(node);
        }

        public override void VisitNullableType(ROSLYNCS.Syntax.NullableTypeSyntax node)
        {
            var ournode = (CSHARP.Nodes.Expression.NullableTypeSyntax)Factory.getRef(Map[node]);
            if (node.ElementType != null)
                ournode.setElementType(Map[node.ElementType]);

            base.VisitNullableType(node);
        }

        public override void VisitOmittedTypeArgument(ROSLYNCS.Syntax.OmittedTypeArgumentSyntax node)
        {
            var ournode = (CSHARP.Nodes.Expression.OmittedTypeArgumentSyntax)Factory.getRef(Map[node]);

            base.VisitOmittedTypeArgument(node);
        }

        public override void VisitPointerType(ROSLYNCS.Syntax.PointerTypeSyntax node)
        {
            var ournode = (CSHARP.Nodes.Expression.PointerTypeSyntax)Factory.getRef(Map[node]);
            if (node.ElementType != null)
                ournode.setElementType(Map[node.ElementType]);

            base.VisitPointerType(node);
        }

        public override void VisitPredefinedType(ROSLYNCS.Syntax.PredefinedTypeSyntax node)
        {
            var ournode = (CSHARP.Nodes.Expression.PredefinedTypeSyntax)Factory.getRef(Map[node]);
            //TODO: eltárolni hogy milyen alaptípus?
            //System.Console.WriteLine(node.Keyword.Text);
            base.VisitPredefinedType(node);
        }

        public override void VisitQualifiedName(ROSLYNCS.Syntax.QualifiedNameSyntax node)
        {
            var ournode = (CSHARP.Nodes.Expression.QualifiedNameSyntax)Factory.getRef(Map[node]);
            if (node.Left != null)
                ournode.setLeft(Map[node.Left]);
            if (node.Right != null)
                ournode.setRight(Map[node.Right]);

            base.VisitQualifiedName(node);
        }
    }
}
