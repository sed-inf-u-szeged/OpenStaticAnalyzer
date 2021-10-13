using System.Diagnostics.CodeAnalysis;
using Columbus.CSAN.Contexts;
using Columbus.CSAN.Utils;
using Microsoft.CodeAnalysis;
using Microsoft.CodeAnalysis.CSharp;
using Microsoft.CodeAnalysis.CSharp.Syntax;

namespace Columbus.CSAN
{
    /// <summary>
    /// This class builds our syntax tree (AST) from Roslyn's without any cross edges.
    /// The methods are half-generated, and they follow these steps:
    ///   * GetOrCreate a corresponding node (get only occurs if a previously analyzed file contained a cross reference
    ///     to something defined in this file (eg a method call).
    ///   * Call base.Visit(), so descend on the tree
    ///   * When ascending, fill the tree edges, that can be
    ///     - 1-1 or N-1, in this case two null check is done before setting the edge (the second is needed because of unsupported nodes - missing subtrees)
    ///     - N-M, in this case a foreach and a null check is done, because of the same reasons as above
    /// Watch out for VisitCompilationUnit() because it is a little exception containing one extra check.
    /// </summary>
    [SuppressMessage("ReSharper", "UnusedVariable")]
    [SuppressMessage("ReSharper", "ConditionIsAlwaysTrueOrFalse")]
    class TreeBuilder : BaseASGBuilder
    {
        public TreeBuilder(FileContext fileContext) : base(fileContext)
        {
        }

        public override void Visit(SyntaxNode node)
        {
            base.Visit(node);

            if (Map.ContainsKey((CSharpSyntaxNode)node))
            {
                var ournode = (Columbus.Csharp.Asg.Nodes.Base.Positioned)Factory.getRef(Map[(CSharpSyntaxNode)node]);

                // TODO move this to somewhere else eg comp unit visitor, or out
                // also, do we need the else branch?
                if (FileContext.SoftFiltered)
                    Factory.setFilteredThisNodeOnly(ournode.Id);
                else
                    Factory.setNotFilteredThisNodeOnly(ournode.Id);
            }
        }

        public override void VisitAccessorDeclaration(AccessorDeclarationSyntax node)
        {
            var ournode = GetOrCreateNode<Csharp.Asg.Nodes.Structure.AccessorDeclarationSyntax>(node);

            base.VisitAccessorDeclaration(node);

            if (node.Body != null)
                ournode.setBody(Map[node.Body]);
            foreach (var attributeList in node.AttributeLists)
                ournode.addAttributeLists(Map[attributeList]);
        }

        public override void VisitAccessorList(AccessorListSyntax node)
        {
            var ournode = GetOrCreateNode<Csharp.Asg.Nodes.Structure.AccessorListSyntax>(node);

            base.VisitAccessorList(node);

            foreach (var accessor in node.Accessors)
                ournode.addAccessors(Map[accessor]);
        }

        public override void VisitAnonymousMethodExpression(AnonymousMethodExpressionSyntax node)
        {
            var ournode = GetOrCreateNode<Csharp.Asg.Nodes.Expression.AnonymousMethodExpressionSyntax>(node);

            base.VisitAnonymousMethodExpression(node);

            if (node.Block != null)
                ournode.setBlock(Map[node.Block]);
            if (node.ExpressionBody != null)
                ournode.setExpressionBody(Map[node.ExpressionBody]);
            if (node.ParameterList != null)
                ournode.setParameterList(Map[node.ParameterList]);
        }

        public override void VisitAnonymousObjectCreationExpression(AnonymousObjectCreationExpressionSyntax node)
        {
            var ournode = GetOrCreateNode<Csharp.Asg.Nodes.Expression.AnonymousObjectCreationExpressionSyntax>(node);

            base.VisitAnonymousObjectCreationExpression(node);

            foreach (var initializer in node.Initializers)
                ournode.addInitializers(Map[initializer]);
        }

        public override void VisitAnonymousObjectMemberDeclarator(AnonymousObjectMemberDeclaratorSyntax node)
        {
            var ournode = GetOrCreateNode<Csharp.Asg.Nodes.Structure.AnonymousObjectMemberDeclaratorSyntax>(node);

            base.VisitAnonymousObjectMemberDeclarator(node);

            if (node.Expression != null)
                ournode.setExpression(Map[node.Expression]);
            if (node.NameEquals != null)
                ournode.setNameEquals(Map[node.NameEquals]);
        }

        public override void VisitArgument(ArgumentSyntax node)
        {
            var ournode = GetOrCreateNode<Csharp.Asg.Nodes.Structure.ArgumentSyntax>(node);

            base.VisitArgument(node);

            if (node.Expression != null)
                ournode.setExpression(Map[node.Expression]);
            if (node.NameColon != null)
                ournode.setNameColon(Map[node.NameColon]);
        }

        public override void VisitArgumentList(ArgumentListSyntax node)
        {
            var ournode = GetOrCreateNode<Csharp.Asg.Nodes.Structure.ArgumentListSyntax>(node);

            base.VisitArgumentList(node);

            foreach (var argument in node.Arguments)
                ournode.addArguments(Map[argument]);
        }

        public override void VisitArrayCreationExpression(ArrayCreationExpressionSyntax node)
        {
            var ournode = GetOrCreateNode<Csharp.Asg.Nodes.Expression.ArrayCreationExpressionSyntax>(node);

            base.VisitArrayCreationExpression(node);

            if (node.Initializer != null)
                ournode.setInitializer(Map[node.Initializer]);
            if (node.Type != null)
                ournode.setType(Map[node.Type]);
        }

        public override void VisitArrayRankSpecifier(ArrayRankSpecifierSyntax node)
        {
            var ournode = GetOrCreateNode<Csharp.Asg.Nodes.Structure.ArrayRankSpecifierSyntax>(node);

            base.VisitArrayRankSpecifier(node);

            foreach (var size in node.Sizes)
                ournode.addSizes(Map[size]);
        }

        public override void VisitArrowExpressionClause(ArrowExpressionClauseSyntax node)
        {
            var ournode = GetOrCreateNode<Csharp.Asg.Nodes.Structure.ArrowExpressionClauseSyntax>(node);

            base.VisitArrowExpressionClause(node);

            if (node.Expression != null)
                ournode.setExpression(Map[node.Expression]);
        }

        public override void VisitAssignmentExpression(AssignmentExpressionSyntax node)
        {
            var ournode = GetOrCreateNode<Csharp.Asg.Nodes.Expression.AssignmentExpressionSyntax>(node);

            base.VisitAssignmentExpression(node);

            if (node.Left != null)
                ournode.setLeft(Map[node.Left]);
            if (node.Right != null)
                ournode.setRight(Map[node.Right]);
        }

        public override void VisitAttribute(AttributeSyntax node)
        {
            var ournode = GetOrCreateNode<Csharp.Asg.Nodes.Structure.AttributeSyntax>(node);

            base.VisitAttribute(node);

            if (node.ArgumentList != null)
                ournode.setArgumentList(Map[node.ArgumentList]);
            if (node.Name != null)
                ournode.setName(Map[node.Name]);
        }

        public override void VisitAttributeArgument(AttributeArgumentSyntax node)
        {
            var ournode = GetOrCreateNode<Csharp.Asg.Nodes.Structure.AttributeArgumentSyntax>(node);

            base.VisitAttributeArgument(node);

            if (node.Expression != null)
                ournode.setExpression(Map[node.Expression]);
            if (node.NameColon != null)
                ournode.setNameColon(Map[node.NameColon]);
            if (node.NameEquals != null)
                ournode.setNameEquals(Map[node.NameEquals]);
        }

        public override void VisitAttributeArgumentList(AttributeArgumentListSyntax node)
        {
            var ournode = GetOrCreateNode<Csharp.Asg.Nodes.Structure.AttributeArgumentListSyntax>(node);

            base.VisitAttributeArgumentList(node);

            foreach (var argument in node.Arguments)
                ournode.addArguments(Map[argument]);
        }

        public override void VisitAttributeList(AttributeListSyntax node)
        {
            var ournode = GetOrCreateNode<Csharp.Asg.Nodes.Structure.AttributeListSyntax>(node);

            base.VisitAttributeList(node);

            if (node.Target != null)
                ournode.setTarget(Map[node.Target]);
            foreach (var attribute in node.Attributes)
                ournode.addAttributes(Map[attribute]);
        }

        public override void VisitAttributeTargetSpecifier(AttributeTargetSpecifierSyntax node)
        {
            var ournode = GetOrCreateNode<Csharp.Asg.Nodes.Structure.AttributeTargetSpecifierSyntax>(node);

            base.VisitAttributeTargetSpecifier(node);
        }

        public override void VisitAwaitExpression(AwaitExpressionSyntax node)
        {
            var ournode = GetOrCreateNode<Csharp.Asg.Nodes.Expression.AwaitExpressionSyntax>(node);

            base.VisitAwaitExpression(node);

            if (node.Expression != null)
                ournode.setExpression(Map[node.Expression]);
        }

        public override void VisitBaseExpression(BaseExpressionSyntax node)
        {
            var ournode = GetOrCreateNode<Csharp.Asg.Nodes.Expression.BaseExpressionSyntax>(node);

            base.VisitBaseExpression(node);
        }

        public override void VisitBaseList(BaseListSyntax node)
        {
            var ournode = GetOrCreateNode<Csharp.Asg.Nodes.Structure.BaseListSyntax>(node);

            base.VisitBaseList(node);

            foreach (var type in node.Types)
                ournode.addTypes(Map[type]);
        }

        public override void VisitBinaryExpression(BinaryExpressionSyntax node)
        {
            var ournode = GetOrCreateNode<Csharp.Asg.Nodes.Expression.BinaryExpressionSyntax>(node);

            base.VisitBinaryExpression(node);

            if (node.Left != null)
                ournode.setLeft(Map[node.Left]);
            if (node.Right != null)
                ournode.setRight(Map[node.Right]);
        }

        public override void VisitBlock(BlockSyntax node)
        {
            var ournode = GetOrCreateNode<Csharp.Asg.Nodes.Statement.BlockSyntax>(node);

            base.VisitBlock(node);

            foreach (var statement in node.Statements)
                ournode.addStatements(Map[statement]);
            foreach (var attributeList in node.AttributeLists)
                ournode.addAttributeLists(Map[attributeList]);
        }

        public override void VisitBracketedArgumentList(BracketedArgumentListSyntax node)
        {
            var ournode = GetOrCreateNode<Csharp.Asg.Nodes.Structure.BracketedArgumentListSyntax>(node);

            base.VisitBracketedArgumentList(node);

            foreach (var argument in node.Arguments)
                ournode.addArguments(Map[argument]);
        }

        public override void VisitBracketedParameterList(BracketedParameterListSyntax node)
        {
            var ournode = GetOrCreateNode<Csharp.Asg.Nodes.Structure.BracketedParameterListSyntax>(node);

            base.VisitBracketedParameterList(node);

            foreach (var parameter in node.Parameters)
                ournode.addParameters(Map[parameter]);
        }

        public override void VisitBreakStatement(BreakStatementSyntax node)
        {
            var ournode = GetOrCreateNode<Csharp.Asg.Nodes.Statement.BreakStatementSyntax>(node);

            base.VisitBreakStatement(node);

            foreach (var attributeList in node.AttributeLists)
                ournode.addAttributeLists(Map[attributeList]);
        }

        public override void VisitCaseSwitchLabel(CaseSwitchLabelSyntax node)
        {
            var ournode = GetOrCreateNode<Csharp.Asg.Nodes.Structure.CaseSwitchLabelSyntax>(node);

            base.VisitCaseSwitchLabel(node);

            if (node.Value != null)
                ournode.setValue(Map[node.Value]);
        }

        public override void VisitCastExpression(CastExpressionSyntax node)
        {
            var ournode = GetOrCreateNode<Csharp.Asg.Nodes.Expression.CastExpressionSyntax>(node);

            base.VisitCastExpression(node);

            if (node.Expression != null)
                ournode.setExpression(Map[node.Expression]);
            if (node.Type != null)
                ournode.setType(Map[node.Type]);
        }

        public override void VisitCatchClause(CatchClauseSyntax node)
        {
            var ournode = GetOrCreateNode<Csharp.Asg.Nodes.Structure.CatchClauseSyntax>(node);

            base.VisitCatchClause(node);

            if (node.Block != null)
                ournode.setBlock(Map[node.Block]);
            if (node.Declaration != null)
                ournode.setDeclaration(Map[node.Declaration]);
            if (node.Filter != null)
                ournode.setFilter(Map[node.Filter]);
        }

        public override void VisitCatchDeclaration(CatchDeclarationSyntax node)
        {
            var ournode = GetOrCreateNode<Csharp.Asg.Nodes.Structure.CatchDeclarationSyntax>(node);

            base.VisitCatchDeclaration(node);

            if (node.Type != null)
                ournode.setType(Map[node.Type]);
        }

        public override void VisitCatchFilterClause(CatchFilterClauseSyntax node)
        {
            var ournode = GetOrCreateNode<Csharp.Asg.Nodes.Structure.CatchFilterClauseSyntax>(node);

            base.VisitCatchFilterClause(node);

            if (node.FilterExpression != null)
                ournode.setFilterExpression(Map[node.FilterExpression]);
        }

        public override void VisitCheckedExpression(CheckedExpressionSyntax node)
        {
            var ournode = GetOrCreateNode<Csharp.Asg.Nodes.Expression.CheckedExpressionSyntax>(node);

            base.VisitCheckedExpression(node);

            if (node.Expression != null)
                ournode.setExpression(Map[node.Expression]);
        }

        public override void VisitCheckedStatement(CheckedStatementSyntax node)
        {
            var ournode = GetOrCreateNode<Csharp.Asg.Nodes.Statement.CheckedStatementSyntax>(node);

            base.VisitCheckedStatement(node);

            if (node.Block != null)
                ournode.setBlock(Map[node.Block]);

            foreach (var attributeList in node.AttributeLists)
                ournode.addAttributeLists(Map[attributeList]);
        }

        public override void VisitClassOrStructConstraint(ClassOrStructConstraintSyntax node)
        {
            var ournode = GetOrCreateNode<Csharp.Asg.Nodes.Structure.ClassOrStructConstraintSyntax>(node);

            base.VisitClassOrStructConstraint(node);
        }

        public override void VisitCompilationUnit(CompilationUnitSyntax node)
        {
            Csharp.Asg.Nodes.Structure.CompilationUnitSyntax ournode;
            if (Map.Count == 0 && Factory.getRef(100) != null && Factory.getNodeKind(100) == Csharp.Asg.Types.NodeKind.ndkCompilationUnitSyntax)
            {
                ournode = (Csharp.Asg.Nodes.Structure.CompilationUnitSyntax)Factory.getRef(100);
                FillSourcePosition(ournode, node);
                Map.Add(node, 100);
            }
            else
            {
                ournode = GetOrCreateNode<Csharp.Asg.Nodes.Structure.CompilationUnitSyntax>(node);
            }

            base.VisitCompilationUnit(node);

            foreach (var attributeList in node.AttributeLists)
                ournode.addAttributeLists(Map[attributeList]);
            foreach (var @extern in node.Externs)
                ournode.addExterns(Map[@extern]);
            foreach (var member in node.Members)
                ournode.addMembers(Map[member]);
            foreach (var @using in node.Usings)
                ournode.addUsings(Map[@using]);


            var path = node.GetLocation().GetLineSpan().Path;
            if (path.Contains(Constants.TEMP) && path.Contains(Constants.NET) && path.Contains(Constants.COMMA))
                Factory.setFiltered(ournode.Id);
        }

        public override void VisitConditionalAccessExpression(ConditionalAccessExpressionSyntax node)
        {
            var ournode = GetOrCreateNode<Csharp.Asg.Nodes.Expression.ConditionalAccessExpressionSyntax>(node);

            base.VisitConditionalAccessExpression(node);

            if (node.Expression != null)
                ournode.setExpression(Map[node.Expression]);
            if (node.WhenNotNull != null)
                ournode.setWhenNotNull(Map[node.WhenNotNull]);
        }

        public override void VisitConditionalExpression(ConditionalExpressionSyntax node)
        {
            var ournode = GetOrCreateNode<Csharp.Asg.Nodes.Expression.ConditionalExpressionSyntax>(node);

            base.VisitConditionalExpression(node);

            if (node.Condition != null)
                ournode.setCondition(Map[node.Condition]);
            if (node.WhenFalse != null)
                ournode.setWhenFalse(Map[node.WhenFalse]);
            if (node.WhenTrue != null)
                ournode.setWhenTrue(Map[node.WhenTrue]);
        }

        public override void VisitConstructorConstraint(ConstructorConstraintSyntax node)
        {
            var ournode = GetOrCreateNode<Csharp.Asg.Nodes.Structure.ConstructorConstraintSyntax>(node);

            base.VisitConstructorConstraint(node);
        }

        public override void VisitConstructorDeclaration(ConstructorDeclarationSyntax node)
        {
            var ournode = GetOrCreateNode<Csharp.Asg.Nodes.Structure.ConstructorDeclarationSyntax>(node);

            base.VisitConstructorDeclaration(node);

            if (node.Body != null)
                ournode.setBody(Map[node.Body]);
            if (node.Initializer != null)
                ournode.setInitializer(Map[node.Initializer]);
            if (node.ParameterList != null)
                ournode.setParameterList(Map[node.ParameterList]);
            foreach (var attributeList in node.AttributeLists)
                ournode.addAttributeLists(Map[attributeList]);
        }

        public override void VisitConstructorInitializer(ConstructorInitializerSyntax node)
        {
            var ournode = GetOrCreateNode<Csharp.Asg.Nodes.Structure.ConstructorInitializerSyntax>(node);

            base.VisitConstructorInitializer(node);

            if (node.ArgumentList != null)
                ournode.setArgumentList(Map[node.ArgumentList]);
        }

        public override void VisitContinueStatement(ContinueStatementSyntax node)
        {
            var ournode = GetOrCreateNode<Csharp.Asg.Nodes.Statement.ContinueStatementSyntax>(node);

            base.VisitContinueStatement(node);

            foreach (var attributeList in node.AttributeLists)
                ournode.addAttributeLists(Map[attributeList]);
        }

        public override void VisitConversionOperatorDeclaration(ConversionOperatorDeclarationSyntax node)
        {
            var ournode = GetOrCreateNode<Csharp.Asg.Nodes.Structure.ConversionOperatorDeclarationSyntax>(node);

            base.VisitConversionOperatorDeclaration(node);

            if (node.Body != null)
                ournode.setBody(Map[node.Body]);
            if (node.ExpressionBody != null)
                ournode.setExpressionBody(Map[node.ExpressionBody]);
            if (node.ParameterList != null)
                ournode.setParameterList(Map[node.ParameterList]);
            if (node.Type != null)
                ournode.setType(Map[node.Type]);
            foreach (var attributeList in node.AttributeLists)
                ournode.addAttributeLists(Map[attributeList]);
        }

        public override void VisitConversionOperatorMemberCref(ConversionOperatorMemberCrefSyntax node)
        {
            var ournode = GetOrCreateNode<Csharp.Asg.Nodes.Structure.ConversionOperatorMemberCrefSyntax>(node);

            base.VisitConversionOperatorMemberCref(node);

            if (node.Parameters != null)
                ournode.setParameters(Map[node.Parameters]);
            if (node.Type != null)
                ournode.setType(Map[node.Type]);
        }

        public override void VisitCrefBracketedParameterList(CrefBracketedParameterListSyntax node)
        {
            var ournode = GetOrCreateNode<Csharp.Asg.Nodes.Structure.CrefBracketedParameterListSyntax>(node);

            base.VisitCrefBracketedParameterList(node);

            foreach (var parameter in node.Parameters)
                ournode.addParameters(Map[parameter]);
        }

        public override void VisitCrefParameter(CrefParameterSyntax node)
        {
            var ournode = GetOrCreateNode<Csharp.Asg.Nodes.Structure.CrefParameterSyntax>(node);

            base.VisitCrefParameter(node);

            if (node.Type != null)
                ournode.setType(Map[node.Type]);
        }

        public override void VisitCrefParameterList(CrefParameterListSyntax node)
        {
            var ournode = GetOrCreateNode<Csharp.Asg.Nodes.Structure.CrefParameterListSyntax>(node);

            base.VisitCrefParameterList(node);

            foreach (var parameter in node.Parameters)
                ournode.addParameters(Map[parameter]);
        }

        public override void VisitDefaultExpression(DefaultExpressionSyntax node)
        {
            var ournode = GetOrCreateNode<Csharp.Asg.Nodes.Expression.DefaultExpressionSyntax>(node);

            base.VisitDefaultExpression(node);

            if (node.Type != null)
                ournode.setType(Map[node.Type]);
        }

        public override void VisitDefaultSwitchLabel(DefaultSwitchLabelSyntax node)
        {
            var ournode = GetOrCreateNode<Csharp.Asg.Nodes.Structure.DefaultSwitchLabelSyntax>(node);

            base.VisitDefaultSwitchLabel(node);
        }

        public override void VisitDelegateDeclaration(DelegateDeclarationSyntax node)
        {
            var ournode = GetOrCreateNode<Csharp.Asg.Nodes.Structure.DelegateDeclarationSyntax>(node);

            base.VisitDelegateDeclaration(node);

            if (node.ParameterList != null)
                ournode.setParameterList(Map[node.ParameterList]);
            if (node.ReturnType != null)
                ournode.setReturnType(Map[node.ReturnType]);
            foreach (var attributeList in node.AttributeLists)
                ournode.addAttributeLists(Map[attributeList]);
            foreach (var constraintClause in node.ConstraintClauses)
                ournode.addConstraintClauses(Map[constraintClause]);
        }

        public override void VisitDestructorDeclaration(DestructorDeclarationSyntax node)
        {
            var ournode = GetOrCreateNode<Csharp.Asg.Nodes.Structure.DestructorDeclarationSyntax>(node);

            base.VisitDestructorDeclaration(node);

            if (node.Body != null)
                ournode.setBody(Map[node.Body]);
            if (node.ParameterList != null)
                ournode.setParameterList(Map[node.ParameterList]);
            foreach (var attributeList in node.AttributeLists)
                ournode.addAttributeLists(Map[attributeList]);
        }

        public override void VisitDoStatement(DoStatementSyntax node)
        {
            var ournode = GetOrCreateNode<Csharp.Asg.Nodes.Statement.DoStatementSyntax>(node);

            base.VisitDoStatement(node);

            if (node.Condition != null)
                ournode.setCondition(Map[node.Condition]);
            if (node.Statement != null)
                ournode.setStatement(Map[node.Statement]);

            foreach (var attributeList in node.AttributeLists)
                ournode.addAttributeLists(Map[attributeList]);
        }

        public override void VisitElementAccessExpression(ElementAccessExpressionSyntax node)
        {
            var ournode = GetOrCreateNode<Csharp.Asg.Nodes.Expression.ElementAccessExpressionSyntax>(node);

            base.VisitElementAccessExpression(node);

            if (node.ArgumentList != null)
                ournode.setArgumentList(Map[node.ArgumentList]);
            if (node.Expression != null)
                ournode.setExpression(Map[node.Expression]);
        }

        public override void VisitElementBindingExpression(ElementBindingExpressionSyntax node)
        {
            var ournode = GetOrCreateNode<Csharp.Asg.Nodes.Expression.ElementBindingExpressionSyntax>(node);

            base.VisitElementBindingExpression(node);

            if (node.ArgumentList != null)
                ournode.setArgumentList(Map[node.ArgumentList]);
        }

        public override void VisitElseClause(ElseClauseSyntax node)
        {
            var ournode = GetOrCreateNode<Csharp.Asg.Nodes.Structure.ElseClauseSyntax>(node);

            base.VisitElseClause(node);

            if (node.Statement != null)
                ournode.setStatement(Map[node.Statement]);
        }

        public override void VisitEmptyStatement(EmptyStatementSyntax node)
        {
            var ournode = GetOrCreateNode<Csharp.Asg.Nodes.Statement.EmptyStatementSyntax>(node);

            base.VisitEmptyStatement(node);

            foreach (var attributeList in node.AttributeLists)
                ournode.addAttributeLists(Map[attributeList]);
        }

        public override void VisitEnumDeclaration(EnumDeclarationSyntax node)
        {
            var ournode = GetOrCreateNode<Csharp.Asg.Nodes.Structure.EnumDeclarationSyntax>(node);

            base.VisitEnumDeclaration(node);

            if (node.BaseList != null)
                ournode.setBaseList(Map[node.BaseList]);
            foreach (var attributeList in node.AttributeLists)
                ournode.addAttributeLists(Map[attributeList]);
            foreach (var member in node.Members)
                ournode.addMembers(Map[member]);
        }

        public override void VisitEnumMemberDeclaration(EnumMemberDeclarationSyntax node)
        {
            var ournode = GetOrCreateNode<Csharp.Asg.Nodes.Structure.EnumMemberDeclarationSyntax>(node);

            base.VisitEnumMemberDeclaration(node);

            if (node.EqualsValue != null)
                ournode.setEqualsValue(Map[node.EqualsValue]);
            foreach (var attributeList in node.AttributeLists)
                ournode.addAttributeLists(Map[attributeList]);
        }

        public override void VisitEqualsValueClause(EqualsValueClauseSyntax node)
        {
            var ournode = GetOrCreateNode<Csharp.Asg.Nodes.Structure.EqualsValueClauseSyntax>(node);

            base.VisitEqualsValueClause(node);

            if (node.Value != null)
                ournode.setValue(Map[node.Value]);
        }

        public override void VisitEventFieldDeclaration(EventFieldDeclarationSyntax node)
        {
            var ournode = GetOrCreateNode<Csharp.Asg.Nodes.Structure.EventFieldDeclarationSyntax>(node);

            base.VisitEventFieldDeclaration(node);

            if (node.Declaration != null)
                ournode.setDeclaration(Map[node.Declaration]);
            foreach (var attributeList in node.AttributeLists)
                ournode.addAttributeLists(Map[attributeList]);
        }

        public override void VisitExplicitInterfaceSpecifier(ExplicitInterfaceSpecifierSyntax node)
        {
            var ournode = GetOrCreateNode<Csharp.Asg.Nodes.Structure.ExplicitInterfaceSpecifierSyntax>(node);

            base.VisitExplicitInterfaceSpecifier(node);

            if (node.Name != null)
                ournode.setName(Map[node.Name]);
        }

        public override void VisitExpressionStatement(ExpressionStatementSyntax node)
        {
            var ournode = GetOrCreateNode<Csharp.Asg.Nodes.Statement.ExpressionStatementSyntax>(node);

            base.VisitExpressionStatement(node);

            if (node.Expression != null)
                ournode.setExpression(Map[node.Expression]);

            foreach (var attributeList in node.AttributeLists)
                ournode.addAttributeLists(Map[attributeList]);
        }

        public override void VisitExternAliasDirective(ExternAliasDirectiveSyntax node)
        {
            var ournode = GetOrCreateNode<Csharp.Asg.Nodes.Structure.ExternAliasDirectiveSyntax>(node);

            base.VisitExternAliasDirective(node);
        }

        public override void VisitFieldDeclaration(FieldDeclarationSyntax node)
        {
            var ournode = GetOrCreateNode<Csharp.Asg.Nodes.Structure.FieldDeclarationSyntax>(node);

            base.VisitFieldDeclaration(node);

            if (node.Declaration != null)
                ournode.setDeclaration(Map[node.Declaration]);
            foreach (var attributeList in node.AttributeLists)
                ournode.addAttributeLists(Map[attributeList]);
        }

        public override void VisitFinallyClause(FinallyClauseSyntax node)
        {
            var ournode = GetOrCreateNode<Csharp.Asg.Nodes.Structure.FinallyClauseSyntax>(node);

            base.VisitFinallyClause(node);

            if (node.Block != null)
                ournode.setBlock(Map[node.Block]);
        }

        public override void VisitFixedStatement(FixedStatementSyntax node)
        {
            var ournode = GetOrCreateNode<Csharp.Asg.Nodes.Statement.FixedStatementSyntax>(node);

            base.VisitFixedStatement(node);

            if (node.Declaration != null)
                ournode.setDeclaration(Map[node.Declaration]);
            if (node.Statement != null)
                ournode.setStatement(Map[node.Statement]);

            foreach (var attributeList in node.AttributeLists)
                ournode.addAttributeLists(Map[attributeList]);
        }

        public override void VisitForEachStatement(ForEachStatementSyntax node)
        {
            var ournode = GetOrCreateNode<Csharp.Asg.Nodes.Statement.ForEachStatementSyntax>(node);

            base.VisitForEachStatement(node);

            if (node.Expression != null)
                ournode.setExpression(Map[node.Expression]);
            if (node.Statement != null)
                ournode.setStatement(Map[node.Statement]);
            if (node.Type != null)
                ournode.setType(Map[node.Type]);

            foreach (var attributeList in node.AttributeLists)
                ournode.addAttributeLists(Map[attributeList]);
        }

        public override void VisitForStatement(ForStatementSyntax node)
        {
            var ournode = GetOrCreateNode<Csharp.Asg.Nodes.Statement.ForStatementSyntax>(node);

            base.VisitForStatement(node);

            if (node.Condition != null)
                ournode.setCondition(Map[node.Condition]);
            if (node.Declaration != null)
                ournode.setDeclaration(Map[node.Declaration]);
            if (node.Statement != null)
                ournode.setStatement(Map[node.Statement]);
            foreach (var incrementor in node.Incrementors)
                ournode.addIncrementors(Map[incrementor]);
            foreach (var initializer in node.Initializers)
                ournode.addInitializers(Map[initializer]);
            foreach (var attributeList in node.AttributeLists)
                ournode.addAttributeLists(Map[attributeList]);
        }

        public override void VisitFromClause(FromClauseSyntax node)
        {
            var ournode = GetOrCreateNode<Csharp.Asg.Nodes.Structure.FromClauseSyntax>(node);

            base.VisitFromClause(node);

            if (node.Expression != null)
                ournode.setExpression(Map[node.Expression]);
            if (node.Type != null)
                ournode.setType(Map[node.Type]);
        }

        public override void VisitGlobalStatement(GlobalStatementSyntax node)
        {
            var ournode = GetOrCreateNode<Csharp.Asg.Nodes.Structure.GlobalStatementSyntax>(node);

            base.VisitGlobalStatement(node);

            if (node.Statement != null)
                ournode.setStatement(Map[node.Statement]);
        }

        public override void VisitGotoStatement(GotoStatementSyntax node)
        {
            var ournode = GetOrCreateNode<Csharp.Asg.Nodes.Statement.GotoStatementSyntax>(node);

            base.VisitGotoStatement(node);

            if (node.Expression != null)
                ournode.setExpression(Map[node.Expression]);

            foreach (var attributeList in node.AttributeLists)
                ournode.addAttributeLists(Map[attributeList]);
        }

        public override void VisitGroupClause(GroupClauseSyntax node)
        {
            var ournode = GetOrCreateNode<Csharp.Asg.Nodes.Structure.GroupClauseSyntax>(node);

            base.VisitGroupClause(node);

            if (node.ByExpression != null)
                ournode.setByExpression(Map[node.ByExpression]);
            if (node.GroupExpression != null)
                ournode.setGroupExpression(Map[node.GroupExpression]);
        }

        public override void VisitIfStatement(IfStatementSyntax node)
        {
            var ournode = GetOrCreateNode<Csharp.Asg.Nodes.Statement.IfStatementSyntax>(node);

            base.VisitIfStatement(node);

            if (node.Condition != null)
                ournode.setCondition(Map[node.Condition]);
            if (node.Else != null)
                ournode.setElse(Map[node.Else]);
            if (node.Statement != null)
                ournode.setStatement(Map[node.Statement]);
            foreach (var attributeList in node.AttributeLists)
                ournode.addAttributeLists(Map[attributeList]);
        }

        public override void VisitImplicitArrayCreationExpression(ImplicitArrayCreationExpressionSyntax node)
        {
            var ournode = GetOrCreateNode<Csharp.Asg.Nodes.Expression.ImplicitArrayCreationExpressionSyntax>(node);

            base.VisitImplicitArrayCreationExpression(node);

            if (node.Initializer != null)
                ournode.setInitializer(Map[node.Initializer]);
        }

        public override void VisitImplicitElementAccess(ImplicitElementAccessSyntax node)
        {
            var ournode = GetOrCreateNode<Csharp.Asg.Nodes.Expression.ImplicitElementAccessSyntax>(node);

            base.VisitImplicitElementAccess(node);

            if (node.ArgumentList != null)
                ournode.setArgumentList(Map[node.ArgumentList]);
        }

        public override void VisitIncompleteMember(IncompleteMemberSyntax node)
        {
            var ournode = GetOrCreateNode<Csharp.Asg.Nodes.Structure.IncompleteMemberSyntax>(node);

            base.VisitIncompleteMember(node);

            if (node.Type != null)
                ournode.setType(Map[node.Type]);
            foreach (var attributeList in node.AttributeLists)
                ournode.addAttributeLists(Map[attributeList]);
        }

        public override void VisitIndexerDeclaration(IndexerDeclarationSyntax node)
        {
            var ournode = GetOrCreateNode<Csharp.Asg.Nodes.Structure.IndexerDeclarationSyntax>(node);

            base.VisitIndexerDeclaration(node);

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
            foreach (var attributeList in node.AttributeLists)
                ournode.addAttributeLists(Map[attributeList]);
        }

        public override void VisitIndexerMemberCref(IndexerMemberCrefSyntax node)
        {
            var ournode = GetOrCreateNode<Csharp.Asg.Nodes.Structure.IndexerMemberCrefSyntax>(node);

            base.VisitIndexerMemberCref(node);

            if (node.Parameters != null)
                ournode.setParameters(Map[node.Parameters]);
        }

        public override void VisitInitializerExpression(InitializerExpressionSyntax node)
        {
            var ournode = GetOrCreateNode<Csharp.Asg.Nodes.Expression.InitializerExpressionSyntax>(node);

            base.VisitInitializerExpression(node);

            foreach (var expression in node.Expressions)
                ournode.addExpressions(Map[expression]);
        }

        public override void VisitInterfaceDeclaration(InterfaceDeclarationSyntax node)
        {
            var ournode = GetOrCreateNode<Csharp.Asg.Nodes.Structure.InterfaceDeclarationSyntax>(node);

            base.VisitInterfaceDeclaration(node);

            if (node.BaseList != null)
                ournode.setBaseList(Map[node.BaseList]);
            if (node.TypeParameterList != null)
                ournode.setTypeParameterList(Map[node.TypeParameterList]);
            foreach (var attributeList in node.AttributeLists)
                ournode.addAttributeLists(Map[attributeList]);
            foreach (var constraintClause in node.ConstraintClauses)
                ournode.addConstraintClauses(Map[constraintClause]);
            foreach (var member in node.Members)
                ournode.addMembers(Map[member]);
        }
        public override void VisitInterpolatedStringExpression(InterpolatedStringExpressionSyntax node)
        {
            var ournode = GetOrCreateNode<Csharp.Asg.Nodes.Expression.InterpolatedStringExpressionSyntax>(node);

            base.VisitInterpolatedStringExpression(node);

            foreach (var content in node.Contents)
                ournode.addContents(Map[content]);
        }

        public override void VisitInterpolatedStringText(InterpolatedStringTextSyntax node)
        {
            var ournode = GetOrCreateNode<Csharp.Asg.Nodes.Structure.InterpolatedStringTextSyntax>(node);

            base.VisitInterpolatedStringText(node);

            //TODO: text token?
        }

        public override void VisitInterpolation(InterpolationSyntax node)
        {
            var ournode = GetOrCreateNode<Csharp.Asg.Nodes.Structure.InterpolationSyntax>(node);

            base.VisitInterpolation(node);

            if (node.AlignmentClause != null)
                ournode.setAlignmentClause(Map[node.AlignmentClause]);
            if (node.Expression != null)
                ournode.setExpression(Map[node.Expression]);
            if (node.FormatClause != null)
                ournode.setFormatClause(Map[node.FormatClause]);
        }

        public override void VisitInterpolationAlignmentClause(InterpolationAlignmentClauseSyntax node)
        {
            var ournode = GetOrCreateNode<Csharp.Asg.Nodes.Structure.InterpolationAlignmentClauseSyntax>(node);

            base.VisitInterpolationAlignmentClause(node);

            if (node.Value != null)
                ournode.setValue(Map[node.Value]);
        }

        public override void VisitInterpolationFormatClause(InterpolationFormatClauseSyntax node)
        {
            var ournode = GetOrCreateNode<Csharp.Asg.Nodes.Structure.InterpolationFormatClauseSyntax>(node);

            base.VisitInterpolationFormatClause(node);

            //TODO format string token?
        }

        public override void VisitInvocationExpression(InvocationExpressionSyntax node)
        {
            var ournode = GetOrCreateNode<Csharp.Asg.Nodes.Expression.InvocationExpressionSyntax>(node);

            base.VisitInvocationExpression(node);

            if (node.ArgumentList != null)
                ournode.setArgumentList(Map[node.ArgumentList]);
            if (node.Expression != null)
                ournode.setExpression(Map[node.Expression]);
        }

        public override void VisitJoinClause(JoinClauseSyntax node)
        {
            var ournode = GetOrCreateNode<Csharp.Asg.Nodes.Structure.JoinClauseSyntax>(node);

            base.VisitJoinClause(node);

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
        }

        public override void VisitJoinIntoClause(JoinIntoClauseSyntax node)
        {
            var ournode = GetOrCreateNode<Csharp.Asg.Nodes.Structure.JoinIntoClauseSyntax>(node);

            base.VisitJoinIntoClause(node);
        }

        public override void VisitLabeledStatement(LabeledStatementSyntax node)
        {
            var ournode = GetOrCreateNode<Csharp.Asg.Nodes.Statement.LabeledStatementSyntax>(node);

            base.VisitLabeledStatement(node);

            if (node.Statement != null)
                ournode.setStatement(Map[node.Statement]);

            foreach (var attributeList in node.AttributeLists)
                ournode.addAttributeLists(Map[attributeList]);
        }

        public override void VisitLetClause(LetClauseSyntax node)
        {
            var ournode = GetOrCreateNode<Csharp.Asg.Nodes.Structure.LetClauseSyntax>(node);

            base.VisitLetClause(node);

            if (node.Expression != null)
                ournode.setExpression(Map[node.Expression]);
        }

        public override void VisitLiteralExpression(LiteralExpressionSyntax node)
        {
            var ournode = GetOrCreateNode<Csharp.Asg.Nodes.Expression.LiteralExpressionSyntax>(node);

            base.VisitLiteralExpression(node);

            ournode.Token = node.Token.Text;
        }

        public override void VisitLocalDeclarationStatement(LocalDeclarationStatementSyntax node)
        {
            var ournode = GetOrCreateNode<Csharp.Asg.Nodes.Statement.LocalDeclarationStatementSyntax>(node);

            base.VisitLocalDeclarationStatement(node);

            if (node.Declaration != null)
                ournode.setDeclaration(Map[node.Declaration]);

            foreach (var attributeList in node.AttributeLists)
                ournode.addAttributeLists(Map[attributeList]);
        }

        public override void VisitLockStatement(LockStatementSyntax node)
        {
            var ournode = GetOrCreateNode<Csharp.Asg.Nodes.Statement.LockStatementSyntax>(node);

            base.VisitLockStatement(node);

            if (node.Expression != null)
                ournode.setExpression(Map[node.Expression]);
            if (node.Statement != null)
                ournode.setStatement(Map[node.Statement]);

            foreach (var attributeList in node.AttributeLists)
                ournode.addAttributeLists(Map[attributeList]);
        }

        public override void VisitMakeRefExpression(MakeRefExpressionSyntax node)
        {
            var ournode = GetOrCreateNode<Csharp.Asg.Nodes.Expression.MakeRefExpressionSyntax>(node);

            base.VisitMakeRefExpression(node);

            if (node.Expression != null)
                ournode.setExpression(Map[node.Expression]);
        }

        public override void VisitMemberAccessExpression(MemberAccessExpressionSyntax node)
        {
            var ournode = GetOrCreateNode<Csharp.Asg.Nodes.Expression.MemberAccessExpressionSyntax>(node);

            base.VisitMemberAccessExpression(node);

            if (node.Expression != null)
                ournode.setExpression(Map[node.Expression]);
            if (node.Name != null)
                ournode.setName(Map[node.Name]);
        }

        public override void VisitMemberBindingExpression(MemberBindingExpressionSyntax node)
        {
            var ournode = GetOrCreateNode<Csharp.Asg.Nodes.Expression.MemberBindingExpressionSyntax>(node);

            base.VisitMemberBindingExpression(node);

            if (node.Name != null)
                ournode.setName(Map[node.Name]);
        }

        public override void VisitMethodDeclaration(MethodDeclarationSyntax node)
        {
            var ournode = GetOrCreateNode<Csharp.Asg.Nodes.Structure.MethodDeclarationSyntax>(node);

            base.VisitMethodDeclaration(node);

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

            foreach (var attributeList in node.AttributeLists)
                ournode.addAttributeLists(Map[attributeList]);
            foreach (var constraintClause in node.ConstraintClauses)
                ournode.addConstraintClauses(Map[constraintClause]);
        }

        public override void VisitNameColon(NameColonSyntax node)
        {
            var ournode = GetOrCreateNode<Csharp.Asg.Nodes.Structure.NameColonSyntax>(node);

            base.VisitNameColon(node);

            if (node.Name != null)
                ournode.setName(Map[node.Name]);
        }

        public override void VisitNameEquals(NameEqualsSyntax node)
        {
            var ournode = GetOrCreateNode<Csharp.Asg.Nodes.Structure.NameEqualsSyntax>(node);

            base.VisitNameEquals(node);

            if (node.Name != null)
                ournode.setName(Map[node.Name]);
        }

        public override void VisitNameMemberCref(NameMemberCrefSyntax node)
        {
            var ournode = GetOrCreateNode<Csharp.Asg.Nodes.Structure.NameMemberCrefSyntax>(node);

            base.VisitNameMemberCref(node);

            if (node.Name != null)
                ournode.setName(Map[node.Name]);
            if (node.Parameters != null)
                ournode.setParameters(Map[node.Parameters]);
        }

        public override void VisitNamespaceDeclaration(NamespaceDeclarationSyntax node)
        {
            var ournode = GetOrCreateNode<Csharp.Asg.Nodes.Structure.NamespaceDeclarationSyntax>(node);

            base.VisitNamespaceDeclaration(node);

            if (node.Name != null)
                ournode.setName(Map[node.Name]);
            foreach (var @extern in node.Externs)
                ournode.addExterns(Map[@extern]);
            foreach (var member in node.Members)
                ournode.addMembers(Map[member]);
            foreach (var @using in node.Usings)
                ournode.addUsings(Map[@using]);
        }

        public override void VisitObjectCreationExpression(ObjectCreationExpressionSyntax node)
        {
            var ournode = GetOrCreateNode<Csharp.Asg.Nodes.Expression.ObjectCreationExpressionSyntax>(node);

            base.VisitObjectCreationExpression(node);

            if (node.ArgumentList != null)
                ournode.setArgumentList(Map[node.ArgumentList]);
            if (node.Initializer != null)
                ournode.setInitializer(Map[node.Initializer]);
            if (node.Type != null)
                ournode.setType(Map[node.Type]);
        }

        public override void VisitOmittedArraySizeExpression(OmittedArraySizeExpressionSyntax node)
        {
            var ournode = GetOrCreateNode<Csharp.Asg.Nodes.Expression.OmittedArraySizeExpressionSyntax>(node);

            base.VisitOmittedArraySizeExpression(node);
        }


        public override void VisitOperatorDeclaration(OperatorDeclarationSyntax node)
        {
            var ournode = GetOrCreateNode<Csharp.Asg.Nodes.Structure.OperatorDeclarationSyntax>(node);

            base.VisitOperatorDeclaration(node);

            if (node.Body != null)
                ournode.setBody(Map[node.Body]);
            if (node.ExpressionBody != null)
                ournode.setExpressionBody(Map[node.ExpressionBody]);
            if (node.ParameterList != null)
                ournode.setParameterList(Map[node.ParameterList]);
            if (node.ReturnType != null)
                ournode.setReturnType(Map[node.ReturnType]);
            foreach (var attributeList in node.AttributeLists)
                ournode.addAttributeLists(Map[attributeList]);
        }

        public override void VisitOperatorMemberCref(OperatorMemberCrefSyntax node)
        {
            var ournode = GetOrCreateNode<Csharp.Asg.Nodes.Structure.OperatorMemberCrefSyntax>(node);

            base.VisitOperatorMemberCref(node);

            if (node.Parameters != null)
                ournode.setParameters(Map[node.Parameters]);
        }

        public override void VisitOrderByClause(OrderByClauseSyntax node)
        {
            var ournode = GetOrCreateNode<Csharp.Asg.Nodes.Structure.OrderByClauseSyntax>(node);

            base.VisitOrderByClause(node);

            foreach (var ordering in node.Orderings)
                ournode.addOrderings(Map[ordering]);
        }

        public override void VisitOrdering(OrderingSyntax node)
        {
            var ournode = GetOrCreateNode<Csharp.Asg.Nodes.Structure.OrderingSyntax>(node);

            base.VisitOrdering(node);

            if (node.Expression != null)
                ournode.setExpression(Map[node.Expression]);
        }

        public override void VisitParameter(ParameterSyntax node)
        {
            var ournode = GetOrCreateNode<Csharp.Asg.Nodes.Structure.ParameterSyntax>(node);

            base.VisitParameter(node);

            if (node.Default != null)
                ournode.setDefault(Map[node.Default]);
            if (node.Type != null)
                ournode.setType(Map[node.Type]);
        }

        public override void VisitParameterList(ParameterListSyntax node)
        {
            var ournode = GetOrCreateNode<Csharp.Asg.Nodes.Structure.ParameterListSyntax>(node);

            base.VisitParameterList(node);

            foreach (var parameter in node.Parameters)
                ournode.addParameters(Map[parameter]);
        }

        public override void VisitParenthesizedExpression(ParenthesizedExpressionSyntax node)
        {
            var ournode = GetOrCreateNode<Csharp.Asg.Nodes.Expression.ParenthesizedExpressionSyntax>(node);

            base.VisitParenthesizedExpression(node);

            if (node.Expression != null)
                ournode.setExpression(Map[node.Expression]);
        }

        public override void VisitParenthesizedLambdaExpression(ParenthesizedLambdaExpressionSyntax node)
        {
            var ournode = GetOrCreateNode<Csharp.Asg.Nodes.Expression.ParenthesizedLambdaExpressionSyntax>(node);

            base.VisitParenthesizedLambdaExpression(node);

            if (node.Block != null)
                ournode.setBlock(Map[node.Block]);
            if (node.ExpressionBody != null)
                ournode.setExpressionBody(Map[node.ExpressionBody]);
            if (node.ParameterList != null)
                ournode.setParameterList(Map[node.ParameterList]);
        }

        public override void VisitPostfixUnaryExpression(PostfixUnaryExpressionSyntax node)
        {
            var ournode = GetOrCreateNode<Csharp.Asg.Nodes.Expression.PostfixUnaryExpressionSyntax>(node);

            base.VisitPostfixUnaryExpression(node);

            if (node.Operand != null)
                ournode.setOperand(Map[node.Operand]);
        }

        public override void VisitPrefixUnaryExpression(PrefixUnaryExpressionSyntax node)
        {
            var ournode = GetOrCreateNode<Csharp.Asg.Nodes.Expression.PrefixUnaryExpressionSyntax>(node);

            base.VisitPrefixUnaryExpression(node);

            if (node.Operand != null)
                ournode.setOperand(Map[node.Operand]);
        }

        public override void VisitPropertyDeclaration(PropertyDeclarationSyntax node)
        {
            var ournode = GetOrCreateNode<Csharp.Asg.Nodes.Structure.PropertyDeclarationSyntax>(node);

            base.VisitPropertyDeclaration(node);

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
            foreach (var attributeList in node.AttributeLists)
                ournode.addAttributeLists(Map[attributeList]);
        }

        public override void VisitQualifiedCref(QualifiedCrefSyntax node)
        {
            var ournode = GetOrCreateNode<Csharp.Asg.Nodes.Structure.QualifiedCrefSyntax>(node);

            base.VisitQualifiedCref(node);

            if (node.Container != null)
                ournode.setContainer(Map[node.Container]);
            if (node.Member != null)
                ournode.setMember(Map[node.Member]);
        }

        public override void VisitQueryBody(QueryBodySyntax node)
        {
            var ournode = GetOrCreateNode<Csharp.Asg.Nodes.Structure.QueryBodySyntax>(node);

            base.VisitQueryBody(node);

            if (node.Continuation != null)
                ournode.setContinuation(Map[node.Continuation]);
            if (node.SelectOrGroup != null)
                ournode.setSelectOrGroup(Map[node.SelectOrGroup]);
            foreach (var clause in node.Clauses)
                ournode.addClauses(Map[clause]);
        }

        public override void VisitQueryContinuation(QueryContinuationSyntax node)
        {
            var ournode = GetOrCreateNode<Csharp.Asg.Nodes.Structure.QueryContinuationSyntax>(node);

            base.VisitQueryContinuation(node);

            if (node.Body != null)
                ournode.setBody(Map[node.Body]);
        }

        public override void VisitQueryExpression(QueryExpressionSyntax node)
        {
            var ournode = GetOrCreateNode<Csharp.Asg.Nodes.Expression.QueryExpressionSyntax>(node);

            base.VisitQueryExpression(node);

            if (node.Body != null)
                ournode.setBody(Map[node.Body]);
            if (node.FromClause != null)
                ournode.setFromClause(Map[node.FromClause]);
        }

        public override void VisitRefTypeExpression(RefTypeExpressionSyntax node)
        {
            var ournode = GetOrCreateNode<Csharp.Asg.Nodes.Expression.RefTypeExpressionSyntax>(node);

            base.VisitRefTypeExpression(node);

            if (node.Expression != null)
                ournode.setExpression(Map[node.Expression]);
        }

        public override void VisitRefValueExpression(RefValueExpressionSyntax node)
        {
            var ournode = GetOrCreateNode<Csharp.Asg.Nodes.Expression.RefValueExpressionSyntax>(node);

            base.VisitRefValueExpression(node);

            if (node.Expression != null)
                ournode.setExpression(Map[node.Expression]);
            if (node.Type != null)
                ournode.setType(Map[node.Type]);
        }

        public override void VisitReturnStatement(ReturnStatementSyntax node)
        {
            var ournode = GetOrCreateNode<Csharp.Asg.Nodes.Statement.ReturnStatementSyntax>(node);

            base.VisitReturnStatement(node);

            if (node.Expression != null)
                ournode.setExpression(Map[node.Expression]);

            foreach (var attributeList in node.AttributeLists)
                ournode.addAttributeLists(Map[attributeList]);
        }

        public override void VisitSelectClause(SelectClauseSyntax node)
        {
            var ournode = GetOrCreateNode<Csharp.Asg.Nodes.Structure.SelectClauseSyntax>(node);

            base.VisitSelectClause(node);

            if (node.Expression != null)
                ournode.setExpression(Map[node.Expression]);
        }

        public override void VisitSimpleBaseType(SimpleBaseTypeSyntax node)
        {
            var ournode = GetOrCreateNode<Csharp.Asg.Nodes.Structure.SimpleBaseTypeSyntax>(node);

            base.VisitSimpleBaseType(node);

            if (node.Type != null)
                ournode.setType(Map[node.Type]);
        }

        public override void VisitSimpleLambdaExpression(SimpleLambdaExpressionSyntax node)
        {
            var ournode = GetOrCreateNode<Csharp.Asg.Nodes.Expression.SimpleLambdaExpressionSyntax>(node);

            base.VisitSimpleLambdaExpression(node);

            if (node.Block != null)
                ournode.setBlock(Map[node.Block]);
            if (node.ExpressionBody != null)
                ournode.setExpressionBody(Map[node.ExpressionBody]);
            if (node.Parameter != null)
                ournode.setParameter(Map[node.Parameter]);
        }

        public override void VisitSizeOfExpression(SizeOfExpressionSyntax node)
        {
            var ournode = GetOrCreateNode<Csharp.Asg.Nodes.Expression.SizeOfExpressionSyntax>(node);

            base.VisitSizeOfExpression(node);

            if (node.Type != null)
                ournode.setType(Map[node.Type]);
        }

        public override void VisitStackAllocArrayCreationExpression(StackAllocArrayCreationExpressionSyntax node)
        {
            var ournode = GetOrCreateNode<Csharp.Asg.Nodes.Expression.StackAllocArrayCreationExpressionSyntax>(node);

            base.VisitStackAllocArrayCreationExpression(node);

            if (node.Type != null)
                ournode.setType(Map[node.Type]);
        }

        public override void VisitStructDeclaration(StructDeclarationSyntax node)
        {
            var ournode = GetOrCreateNode<Csharp.Asg.Nodes.Structure.StructDeclarationSyntax>(node);

            base.VisitStructDeclaration(node);

            if (node.BaseList != null)
                ournode.setBaseList(Map[node.BaseList]);
            if (node.TypeParameterList != null)
                ournode.setTypeParameterList(Map[node.TypeParameterList]);
            foreach (var attributeList in node.AttributeLists)
                ournode.addAttributeLists(Map[attributeList]);
            foreach (var constraintClause in node.ConstraintClauses)
                ournode.addConstraintClauses(Map[constraintClause]);
            foreach (var member in node.Members)
                ournode.addMembers(Map[member]);
        }

        public override void VisitSwitchSection(SwitchSectionSyntax node)
        {
            var ournode = GetOrCreateNode<Csharp.Asg.Nodes.Structure.SwitchSectionSyntax>(node);

            base.VisitSwitchSection(node);

            foreach (var label in node.Labels)
                ournode.addLabels(Map[label]);
            foreach (var statement in node.Statements)
                ournode.addStatements(Map[statement]);
        }

        public override void VisitSwitchStatement(SwitchStatementSyntax node)
        {
            var ournode = GetOrCreateNode<Csharp.Asg.Nodes.Statement.SwitchStatementSyntax>(node);

            base.VisitSwitchStatement(node);

            if (node.Expression != null)
                ournode.setExpression(Map[node.Expression]);
            foreach (var section in node.Sections)
                ournode.addSections(Map[section]);
            foreach (var attributeList in node.AttributeLists)
                ournode.addAttributeLists(Map[attributeList]);
        }

        public override void VisitThisExpression(ThisExpressionSyntax node)
        {
            var ournode = GetOrCreateNode<Csharp.Asg.Nodes.Expression.ThisExpressionSyntax>(node);

            base.VisitThisExpression(node);
        }

        public override void VisitThrowStatement(ThrowStatementSyntax node)
        {
            var ournode = GetOrCreateNode<Csharp.Asg.Nodes.Statement.ThrowStatementSyntax>(node);

            base.VisitThrowStatement(node);

            if (node.Expression != null)
                ournode.setExpression(Map[node.Expression]);

            foreach (var attributeList in node.AttributeLists)
                ournode.addAttributeLists(Map[attributeList]);
        }

        public override void VisitTryStatement(TryStatementSyntax node)
        {
            var ournode = GetOrCreateNode<Csharp.Asg.Nodes.Statement.TryStatementSyntax>(node);

            base.VisitTryStatement(node);

            if (node.Block != null)
                ournode.setBlock(Map[node.Block]);
            if (node.Finally != null)
                ournode.setFinally(Map[node.Finally]);
            foreach (var catche in node.Catches)
                ournode.addCatches(Map[catche]);
            foreach (var attributeList in node.AttributeLists)
                ournode.addAttributeLists(Map[attributeList]);
        }

        public override void VisitTypeArgumentList(TypeArgumentListSyntax node)
        {
            var ournode = GetOrCreateNode<Csharp.Asg.Nodes.Structure.TypeArgumentListSyntax>(node);

            base.VisitTypeArgumentList(node);

            foreach (var argument in node.Arguments)
                ournode.addArguments(Map[argument]);
        }

        public override void VisitTypeConstraint(TypeConstraintSyntax node)
        {
            var ournode = GetOrCreateNode<Csharp.Asg.Nodes.Structure.TypeConstraintSyntax>(node);

            base.VisitTypeConstraint(node);

            if (node.Type != null)
                ournode.setType(Map[node.Type]);
        }

        public override void VisitTypeCref(TypeCrefSyntax node)
        {
            var ournode = GetOrCreateNode<Csharp.Asg.Nodes.Structure.TypeCrefSyntax>(node);

            base.VisitTypeCref(node);

            if (node.Type != null)
                ournode.setType(Map[node.Type]);
        }

        public override void VisitTypeOfExpression(TypeOfExpressionSyntax node)
        {
            var ournode = GetOrCreateNode<Csharp.Asg.Nodes.Expression.TypeOfExpressionSyntax>(node);

            base.VisitTypeOfExpression(node);

            if (node.Type != null)
                ournode.setType(Map[node.Type]);
        }

        public override void VisitTypeParameter(TypeParameterSyntax node)
        {
            var ournode = GetOrCreateNode<Csharp.Asg.Nodes.Structure.TypeParameterSyntax>(node);

            base.VisitTypeParameter(node);

            foreach (var attributeList in node.AttributeLists)
                ournode.addAttributeLists(Map[attributeList]);
        }

        public override void VisitTypeParameterConstraintClause(TypeParameterConstraintClauseSyntax node)
        {
            var ournode = GetOrCreateNode<Csharp.Asg.Nodes.Structure.TypeParameterConstraintClauseSyntax>(node);

            base.VisitTypeParameterConstraintClause(node);

            if (node.Name != null)
                ournode.setName(Map[node.Name]);
            foreach (var constraint in node.Constraints)
                ournode.addConstraints(Map[constraint]);
        }

        public override void VisitTypeParameterList(TypeParameterListSyntax node)
        {
            var ournode = GetOrCreateNode<Csharp.Asg.Nodes.Structure.TypeParameterListSyntax>(node);

            base.VisitTypeParameterList(node);

            foreach (var parameter in node.Parameters)
                ournode.addParameters(Map[parameter]);
        }

        public override void VisitUnsafeStatement(UnsafeStatementSyntax node)
        {
            var ournode = GetOrCreateNode<Csharp.Asg.Nodes.Statement.UnsafeStatementSyntax>(node);

            base.VisitUnsafeStatement(node);

            if (node.Block != null)
                ournode.setBlock(Map[node.Block]);

            foreach (var attributeList in node.AttributeLists)
                ournode.addAttributeLists(Map[attributeList]);
        }

        public override void VisitUsingDirective(UsingDirectiveSyntax node)
        {
            var ournode = GetOrCreateNode<Csharp.Asg.Nodes.Structure.UsingDirectiveSyntax>(node);

            base.VisitUsingDirective(node);

            if (node.Alias != null)
                ournode.setAlias(Map[node.Alias]);
            if (node.Name != null)
                ournode.setName(Map[node.Name]);
        }

        public override void VisitUsingStatement(UsingStatementSyntax node)
        {
            var ournode = GetOrCreateNode<Csharp.Asg.Nodes.Statement.UsingStatementSyntax>(node);

            base.VisitUsingStatement(node);

            if (node.Declaration != null)
                ournode.setDeclaration(Map[node.Declaration]);
            if (node.Expression != null)
                ournode.setExpression(Map[node.Expression]);
            if (node.Statement != null)
                ournode.setStatement(Map[node.Statement]);

            foreach (var attributeList in node.AttributeLists)
                ournode.addAttributeLists(Map[attributeList]);
        }

        public override void VisitVariableDeclaration(VariableDeclarationSyntax node)
        {
            var ournode = GetOrCreateNode<Csharp.Asg.Nodes.Structure.VariableDeclarationSyntax>(node);

            base.VisitVariableDeclaration(node);

            if (node.Type != null)
                ournode.setType(Map[node.Type]);
            foreach (var variable in node.Variables)
                ournode.addVariables(Map[variable]);
        }

        public override void VisitVariableDeclarator(VariableDeclaratorSyntax node)
        {
            var ournode = GetOrCreateNode<Csharp.Asg.Nodes.Structure.VariableDeclaratorSyntax>(node);

            base.VisitVariableDeclarator(node);

            if (node.ArgumentList != null)
                ournode.setArgumentList(Map[node.ArgumentList]);
            if (node.Initializer != null)
                ournode.setInitializer(Map[node.Initializer]);
        }

        public override void VisitWhereClause(WhereClauseSyntax node)
        {
            var ournode = GetOrCreateNode<Csharp.Asg.Nodes.Structure.WhereClauseSyntax>(node);

            base.VisitWhereClause(node);

            if (node.Condition != null)
                ournode.setCondition(Map[node.Condition]);
        }

        public override void VisitWhileStatement(WhileStatementSyntax node)
        {
            var ournode = GetOrCreateNode<Csharp.Asg.Nodes.Statement.WhileStatementSyntax>(node);

            base.VisitWhileStatement(node);

            if (node.Condition != null)
                ournode.setCondition(Map[node.Condition]);
            if (node.Statement != null)
                ournode.setStatement(Map[node.Statement]);

            foreach (var attributeList in node.AttributeLists)
                ournode.addAttributeLists(Map[attributeList]);
        }

        public override void VisitXmlComment(XmlCommentSyntax node)
        {
            var ournode = GetOrCreateNode<Csharp.Asg.Nodes.Structure.XmlCommentSyntax>(node);

            base.VisitXmlComment(node);
        }

        public override void VisitXmlCrefAttribute(XmlCrefAttributeSyntax node)
        {
            var ournode = GetOrCreateNode<Csharp.Asg.Nodes.Structure.XmlCrefAttributeSyntax>(node);

            base.VisitXmlCrefAttribute(node);

            if (node.Cref != null)
                ournode.setCref(Map[node.Cref]);
            if (node.Name != null)
                ournode.setName(Map[node.Name]);
        }

        public override void VisitXmlCDataSection(XmlCDataSectionSyntax node)
        {
            var ournode = GetOrCreateNode<Csharp.Asg.Nodes.Structure.XmlCDataSectionSyntax>(node);

            base.VisitXmlCDataSection(node);

            //TODO text token?
        }

        public override void VisitXmlElement(XmlElementSyntax node)
        {
            var ournode = GetOrCreateNode<Csharp.Asg.Nodes.Structure.XmlElementSyntax>(node);

            base.VisitXmlElement(node);

            if (node.EndTag != null)
                ournode.setEndTag(Map[node.EndTag]);
            if (node.StartTag != null)
                ournode.setStartTag(Map[node.StartTag]);
            foreach (var asd in node.Content)
                ournode.addContent(Map[asd]);
        }

        public override void VisitXmlElementEndTag(XmlElementEndTagSyntax node)
        {
            var ournode = GetOrCreateNode<Csharp.Asg.Nodes.Structure.XmlElementEndTagSyntax>(node);

            base.VisitXmlElementEndTag(node);

            if (node.Name != null)
                ournode.setName(Map[node.Name]);
        }

        public override void VisitXmlElementStartTag(XmlElementStartTagSyntax node)
        {
            var ournode = GetOrCreateNode<Csharp.Asg.Nodes.Structure.XmlElementStartTagSyntax>(node);

            base.VisitXmlElementStartTag(node);

            if (node.Name != null)
                ournode.setName(Map[node.Name]);
            foreach (var attribute in node.Attributes)
                ournode.addAttributes(Map[attribute]);
        }

        public override void VisitXmlEmptyElement(XmlEmptyElementSyntax node)
        {
            var ournode = GetOrCreateNode<Csharp.Asg.Nodes.Structure.XmlEmptyElementSyntax>(node);

            base.VisitXmlEmptyElement(node);

            if (node.Name != null)
                ournode.setName(Map[node.Name]);
            foreach (var attribute in node.Attributes)
                ournode.addAttributes(Map[attribute]);
        }

        public override void VisitXmlName(XmlNameSyntax node)
        {
            var ournode = GetOrCreateNode<Csharp.Asg.Nodes.Structure.XmlNameSyntax>(node);

            base.VisitXmlName(node);

            if (node.Prefix != null)
                ournode.setPrefix(Map[node.Prefix]);
        }

        public override void VisitXmlNameAttribute(XmlNameAttributeSyntax node)
        {
            var ournode = GetOrCreateNode<Csharp.Asg.Nodes.Structure.XmlNameAttributeSyntax>(node);

            base.VisitXmlNameAttribute(node);

            if (node.Identifier != null)
                ournode.setIdentifier(Map[node.Identifier]);
            if (node.Name != null)
                ournode.setName(Map[node.Name]);
        }

        public override void VisitXmlPrefix(XmlPrefixSyntax node)
        {
            var ournode = GetOrCreateNode<Csharp.Asg.Nodes.Structure.XmlPrefixSyntax>(node);

            base.VisitXmlPrefix(node);
        }

        public override void VisitXmlProcessingInstruction(XmlProcessingInstructionSyntax node)
        {
            var ournode = GetOrCreateNode<Csharp.Asg.Nodes.Structure.XmlProcessingInstructionSyntax>(node);

            base.VisitXmlProcessingInstruction(node);

            if (node.Name != null)
                ournode.setName(Map[node.Name]);
        }

        public override void VisitXmlText(XmlTextSyntax node)
        {
            var ournode = GetOrCreateNode<Csharp.Asg.Nodes.Structure.XmlTextSyntax>(node);

            base.VisitXmlText(node);
        }

        public override void VisitXmlTextAttribute(XmlTextAttributeSyntax node)
        {
            var ournode = GetOrCreateNode<Csharp.Asg.Nodes.Structure.XmlTextAttributeSyntax>(node);

            base.VisitXmlTextAttribute(node);

            if (node.Name != null)
                ournode.setName(Map[node.Name]);
        }

        public override void VisitYieldStatement(YieldStatementSyntax node)
        {
            var ournode = GetOrCreateNode<Csharp.Asg.Nodes.Statement.YieldStatementSyntax>(node);

            base.VisitYieldStatement(node);

            if (node.Expression != null)
                ournode.setExpression(Map[node.Expression]);

            foreach (var attributeList in node.AttributeLists)
                ournode.addAttributeLists(Map[attributeList]);
        }

        public override void VisitAliasQualifiedName(AliasQualifiedNameSyntax node)
        {
            var ournode = GetOrCreateNode<Csharp.Asg.Nodes.Expression.AliasQualifiedNameSyntax>(node);

            base.VisitAliasQualifiedName(node);

            if (node.Alias != null)
                ournode.setAlias(Map[node.Alias]);
            if (node.Name != null)
                ournode.setName(Map[node.Name]);

            //TODO
            //What should this point to? Using? NamespaceDeclaration? none og them is BaseTypeDeclaration
            //The syntax looks like    global::System.Console.WriteLine()    or    using Cs = System.Console; Cs::WriteLine();
            //It only differs from the regular . in allowing global

            //ournode.setOriginalDefinition();
        }

        public override void VisitArrayType(ArrayTypeSyntax node)
        {
            var ournode = GetOrCreateNode<Csharp.Asg.Nodes.Expression.ArrayTypeSyntax>(node);

            base.VisitArrayType(node);

            if (node.ElementType != null)
                ournode.setElementType(Map[node.ElementType]);
            foreach (var rankSpecifier in node.RankSpecifiers)
                ournode.addRankSpecifiers(Map[rankSpecifier]);
        }

        public override void VisitClassDeclaration(ClassDeclarationSyntax node)
        {
            var ournode = GetOrCreateNode<Csharp.Asg.Nodes.Structure.ClassDeclarationSyntax>(node);

            base.VisitClassDeclaration(node);

            if (node.BaseList != null)
                ournode.setBaseList(Map[node.BaseList]);
            if (node.TypeParameterList != null)
                ournode.setTypeParameterList(Map[node.TypeParameterList]);
            foreach (var attributeList in node.AttributeLists)
                ournode.addAttributeLists(Map[attributeList]);
            foreach (var constraintClause in node.ConstraintClauses)
                ournode.addConstraintClauses(Map[constraintClause]);
            foreach (var member in node.Members)
                ournode.addMembers(Map[member]);
        }

        public override void VisitEventDeclaration(EventDeclarationSyntax node)
        {
            var ournode = GetOrCreateNode<Csharp.Asg.Nodes.Structure.EventDeclarationSyntax>(node);

            base.VisitEventDeclaration(node);

            if (node.AccessorList != null)
                ournode.setAccessorList(Map[node.AccessorList]);
            if (node.ExplicitInterfaceSpecifier != null)
                ournode.setExplicitInterfaceSpecifier(Map[node.ExplicitInterfaceSpecifier]);
            if (node.Type != null)
                ournode.setType(Map[node.Type]);
            foreach (var attributeList in node.AttributeLists)
                ournode.addAttributeLists(Map[attributeList]);
        }

        public override void VisitGenericName(GenericNameSyntax node)
        {
            var ournode = GetOrCreateNode<Csharp.Asg.Nodes.Expression.GenericNameSyntax>(node);

            base.VisitGenericName(node);

            if (node.TypeArgumentList != null)
                ournode.setTypeArgumentList(Map[node.TypeArgumentList]);
        }

        public override void VisitIdentifierName(IdentifierNameSyntax node)
        {
            var ournode = GetOrCreateNode<Csharp.Asg.Nodes.Expression.IdentifierNameSyntax>(node);

            base.VisitIdentifierName(node);
        }

        public override void VisitNullableType(NullableTypeSyntax node)
        {
            var ournode = GetOrCreateNode<Csharp.Asg.Nodes.Expression.NullableTypeSyntax>(node);

            base.VisitNullableType(node);

            if (node.ElementType != null)
                ournode.setElementType(Map[node.ElementType]);
        }

        public override void VisitOmittedTypeArgument(OmittedTypeArgumentSyntax node)
        {
            var ournode = GetOrCreateNode<Csharp.Asg.Nodes.Expression.OmittedTypeArgumentSyntax>(node);

            base.VisitOmittedTypeArgument(node);
        }

        public override void VisitPointerType(PointerTypeSyntax node)
        {
            var ournode = GetOrCreateNode<Csharp.Asg.Nodes.Expression.PointerTypeSyntax>(node);

            base.VisitPointerType(node);

            if (node.ElementType != null)
                ournode.setElementType(Map[node.ElementType]);
        }

        public override void VisitPredefinedType(PredefinedTypeSyntax node)
        {
            var ournode = GetOrCreateNode<Csharp.Asg.Nodes.Expression.PredefinedTypeSyntax>(node);

            base.VisitPredefinedType(node);

            //TODO: store which predefined type it is?
            //System.Console.WriteLine(node.Keyword.Text);
        }

        public override void VisitQualifiedName(QualifiedNameSyntax node)
        {
            var ournode = GetOrCreateNode<Csharp.Asg.Nodes.Expression.QualifiedNameSyntax>(node);

            base.VisitQualifiedName(node);

            if (node.Left != null)
                ournode.setLeft(Map[node.Left]);
            if (node.Right != null)
                ournode.setRight(Map[node.Right]);
        }

#region CSHARP-7.3

        public override void VisitTupleType(TupleTypeSyntax node)
        {
            var ournode = GetOrCreateNode<Csharp.Asg.Nodes.Expression.TupleTypeSyntax>(node);

            base.VisitTupleType(node);

            foreach (var element in node.Elements)
                ournode.addElements(Map[element]);
        }

        public override void VisitTupleElement(TupleElementSyntax node)
        {
            var ournode = GetOrCreateNode<Csharp.Asg.Nodes.Structure.TupleElementSyntax>(node);

            base.VisitTupleElement(node);

            if (node.Type != null)
                ournode.setType(Map[node.Type]);
        }

        public override void VisitRefType(RefTypeSyntax node)
        {
            var ournode = GetOrCreateNode<Csharp.Asg.Nodes.Expression.RefTypeSyntax>(node);

            base.VisitRefType(node);

            if (node.Type != null)
                ournode.setType(Map[node.Type]);
        }

        public override void VisitTupleExpression(TupleExpressionSyntax node)
        {
            var ournode = GetOrCreateNode<Csharp.Asg.Nodes.Expression.TupleExpressionSyntax>(node);

            base.VisitTupleExpression(node);

            foreach (var argument in node.Arguments)
                ournode.addArguments(Map[argument]);
        }

        public override void VisitDeclarationExpression(DeclarationExpressionSyntax node)
        {
            var ournode = GetOrCreateNode<Csharp.Asg.Nodes.Expression.DeclarationExpressionSyntax>(node);

            base.VisitDeclarationExpression(node);

            if (node.Type != null)
                ournode.setType(Map[node.Type]);
            if (node.Designation != null)
                ournode.setDesignation(Map[node.Designation]);
        }

        public override void VisitRefExpression(RefExpressionSyntax node)
        {
            var ournode = GetOrCreateNode<Csharp.Asg.Nodes.Expression.RefExpressionSyntax>(node);

            base.VisitRefExpression(node);

            if (node.Expression != null)
                ournode.setExpression(Map[node.Expression]);
        }

        public override void VisitImplicitStackAllocArrayCreationExpression(ImplicitStackAllocArrayCreationExpressionSyntax node)
        {
            var ournode = GetOrCreateNode<Csharp.Asg.Nodes.Expression.ImplicitStackAllocArrayCreationExpressionSyntax>(node);

            base.VisitImplicitStackAllocArrayCreationExpression(node);

            if (node.Initializer != null)
                ournode.setInitializer(Map[node.Initializer]);
        }

        public override void VisitIsPatternExpression(IsPatternExpressionSyntax node)
        {
            var ournode = GetOrCreateNode<Csharp.Asg.Nodes.Expression.IsPatternExpressionSyntax>(node);

            base.VisitIsPatternExpression(node);

            if (node.Expression != null)
                ournode.setExpression(Map[node.Expression]);
            if (node.Pattern != null)
                ournode.setPattern(Map[node.Pattern]);
        }

        public override void VisitThrowExpression(ThrowExpressionSyntax node)
        {
            var ournode = GetOrCreateNode<Csharp.Asg.Nodes.Expression.ThrowExpressionSyntax>(node);

            base.VisitThrowExpression(node);

            if (node.Expression != null)
                ournode.setExpression(Map[node.Expression]);
        }

        public override void VisitWhenClause(WhenClauseSyntax node)
        {
            var ournode = GetOrCreateNode<Csharp.Asg.Nodes.Structure.WhenClauseSyntax>(node);

            base.VisitWhenClause(node);

            if (node.Condition != null)
                ournode.setCondition(Map[node.Condition]);
        }

        public override void VisitDeclarationPattern(DeclarationPatternSyntax node)
        {
            var ournode = GetOrCreateNode<Csharp.Asg.Nodes.Structure.DeclarationPatternSyntax>(node);

            base.VisitDeclarationPattern(node);

            if (node.Designation != null)
                ournode.setDesignation(Map[node.Designation]);
            if (node.Type != null)
                ournode.setType(Map[node.Type]);
        }

        public override void VisitConstantPattern(ConstantPatternSyntax node)
        {
            var ournode = GetOrCreateNode<Csharp.Asg.Nodes.Structure.ConstantPatternSyntax>(node);

            base.VisitConstantPattern(node);

            if (node.Expression != null)
                ournode.setExpression(Map[node.Expression]);
        }

        public override void VisitLocalFunctionStatement(LocalFunctionStatementSyntax node)
        {
            var ournode = GetOrCreateNode<Csharp.Asg.Nodes.Statement.LocalFunctionStatementSyntax>(node);

            base.VisitLocalFunctionStatement(node);

            if (node.Body != null)
                ournode.setBody(Map[node.Body]);
            if (node.ExpressionBody != null)
                ournode.setExpressionBody(Map[node.ExpressionBody]);
            if (node.ParameterList != null)
                ournode.setParameterList(Map[node.ParameterList]);
            if (node.ReturnType != null)
                ournode.setReturnType(Map[node.ReturnType]);
            if (node.TypeParameterList != null)
                ournode.setTypeParameterList(Map[node.TypeParameterList]);
            foreach (var constraintClause in node.ConstraintClauses)
                ournode.addConstraintClauses(Map[constraintClause]);
            foreach (var attributeList in node.AttributeLists)
                ournode.addAttributeLists(Map[attributeList]);
        }

        public override void VisitSingleVariableDesignation(SingleVariableDesignationSyntax node)
        {
            var ournode = GetOrCreateNode<Csharp.Asg.Nodes.Structure.SingleVariableDesignationSyntax>(node);

            base.VisitSingleVariableDesignation(node);
        }

        public override void VisitDiscardDesignation(DiscardDesignationSyntax node)
        {
            var ournode = GetOrCreateNode<Csharp.Asg.Nodes.Structure.DiscardDesignationSyntax>(node);

            base.VisitDiscardDesignation(node);
        }

        public override void VisitParenthesizedVariableDesignation(ParenthesizedVariableDesignationSyntax node)
        {
            var ournode = GetOrCreateNode<Csharp.Asg.Nodes.Structure.ParenthesizedVariableDesignationSyntax>(node);

            base.VisitParenthesizedVariableDesignation(node);

            foreach (var variable in node.Variables)
                ournode.addVariables(Map[variable]);
        }

        public override void VisitForEachVariableStatement(ForEachVariableStatementSyntax node)
        {
            var ournode = GetOrCreateNode<Csharp.Asg.Nodes.Statement.ForEachVariableStatementSyntax>(node);

            base.VisitForEachVariableStatement(node);

            if (node.Variable != null)
                ournode.setVariable(Map[node.Variable]);
            if (node.Expression != null)
                ournode.setExpression(Map[node.Expression]);
            if (node.Statement != null)
                ournode.setStatement(Map[node.Statement]);

            foreach (var attributeList in node.AttributeLists)
                ournode.addAttributeLists(Map[attributeList]);
        }

        public override void VisitCasePatternSwitchLabel(CasePatternSwitchLabelSyntax node)
        {
            var ournode = GetOrCreateNode<Csharp.Asg.Nodes.Structure.CasePatternSwitchLabelSyntax>(node);

            base.VisitCasePatternSwitchLabel(node);

            if (node.Pattern != null)
                ournode.setPattern(Map[node.Pattern]);
            if (node.WhenClause != null)
                ournode.setWhenClause(Map[node.WhenClause]);
        }

#endregion

#region CSHARP-8

        public override void VisitRangeExpression(RangeExpressionSyntax node)
        {
            var ournode = GetOrCreateNode<Csharp.Asg.Nodes.Expression.RangeExpressionSyntax>(node);

            base.VisitRangeExpression(node);

            if (node.LeftOperand != null)
                ournode.setLeftOperand(Map[node.LeftOperand]);
            if (node.RightOperand != null)
                ournode.setRightOperand(Map[node.RightOperand]);
        }

        public override void VisitSwitchExpression(SwitchExpressionSyntax node)
        {
            var ournode = GetOrCreateNode<Csharp.Asg.Nodes.Expression.SwitchExpressionSyntax>(node);

            base.VisitSwitchExpression(node);

            if (node.GoverningExpression != null)
                ournode.setGoverningExpression(Map[node.GoverningExpression]);

            foreach (var arm in node.Arms)
                ournode.addArms(Map[arm]);
        }

        public override void VisitDiscardPattern(DiscardPatternSyntax node)
        {
            var ournode = GetOrCreateNode<Csharp.Asg.Nodes.Structure.DiscardPatternSyntax>(node);

            base.VisitDiscardPattern(node);
        }

        public override void VisitPositionalPatternClause(PositionalPatternClauseSyntax node)
        {
            var ournode = GetOrCreateNode<Csharp.Asg.Nodes.Structure.PositionalPatternClauseSyntax>(node);

            base.VisitPositionalPatternClause(node);

            foreach (var subpattern in node.Subpatterns)
                ournode.addSubpatterns(Map[subpattern]);
        }

        public override void VisitPropertyPatternClause(PropertyPatternClauseSyntax node)
        {
            var ournode = GetOrCreateNode<Csharp.Asg.Nodes.Structure.PropertyPatternClauseSyntax>(node);

            base.VisitPropertyPatternClause(node);

            foreach (var subpattern in node.Subpatterns)
                ournode.addSubpatterns(Map[subpattern]);
        }

        public override void VisitRecursivePattern(RecursivePatternSyntax node)
        {
            var ournode = GetOrCreateNode<Csharp.Asg.Nodes.Structure.RecursivePatternSyntax>(node);

            base.VisitRecursivePattern(node);

            if (node.Designation != null)
                ournode.setDesignation(Map[node.Designation]);
            if (node.PositionalPatternClause != null)
                ournode.setPositionalPatternClause(Map[node.PositionalPatternClause]);
            if (node.PropertyPatternClause != null)
                ournode.setPropertyPatternClause(Map[node.PropertyPatternClause]);
            if (node.Type != null)
                ournode.setType(Map[node.Type]);
        }

        public override void VisitSubpattern(SubpatternSyntax node)
        {
            var ournode = GetOrCreateNode<Csharp.Asg.Nodes.Structure.SubpatternSyntax>(node);

            base.VisitSubpattern(node);

            if (node.Pattern != null)
                ournode.setPattern(Map[node.Pattern]);
        }

        public override void VisitSwitchExpressionArm(SwitchExpressionArmSyntax node)
        {
            var ournode = GetOrCreateNode<Csharp.Asg.Nodes.Structure.SwitchExpressionArmSyntax>(node);

            base.VisitSwitchExpressionArm(node);

            if (node.Expression != null)
                ournode.setExpression(Map[node.Expression]);
            if (node.Pattern != null)
                ournode.setPattern(Map[node.Pattern]);
            if (node.WhenClause != null)
                ournode.setWhenClause(Map[node.WhenClause]);
        }

        public override void VisitVarPattern(VarPatternSyntax node)
        {
            var ournode = GetOrCreateNode<Csharp.Asg.Nodes.Structure.VarPatternSyntax>(node);

            base.VisitVarPattern(node);

            if (node.Designation != null)
                ournode.setDesignation(Map[node.Designation]);
        }

        #endregion
    }
}
