using System;
using System.Text;

namespace Columbus.Csharp.Asg.Visitors {

    /// <summary>
    /// VisitorFilter class filters out nodes from the ASG.
    /// </summary>
#if (CSHARP_INTERNAL)
    internal
#else
    public
#endif
    class VisitorFilter : Visitor {

        /// <summary>Pointer type to the set(Not)FilteredThisNodeOnly() method.</summary>
        protected delegate void SelectorType(uint id);

        /// <summary>Pointer to the set(Not)FilteredThisNodeOnly() method.</summary>
        protected SelectorType selector;

        /// <summary>
        /// Constructor for VisitorFilter.
        /// </summary>
        /// <param name="factory">[in] The factory which contains the ASG.</param>
        /// <param name="filter">[in] If this parameter is true then the visitor will filter the nodes out. If it is false then it set the nodes to not filtered.</param>
        public VisitorFilter(Factory factory, bool filter) {
            if (filter)
                selector = new SelectorType(factory.setFilteredThisNodeOnly);
            else
                selector = new SelectorType(factory.setNotFilteredThisNodeOnly);
        }

        /// <summary>
        /// Deselects the actual node (and only this).
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public override void visitEnd(Columbus.Csharp.Asg.Nodes.Expression.AliasQualifiedNameSyntax node, bool callVirtualBase) { selector(node.Id); } 

        /// <summary>
        /// Deselects the actual node (and only this).
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public override void visitEnd(Columbus.Csharp.Asg.Nodes.Expression.AnonymousMethodExpressionSyntax node, bool callVirtualBase) { selector(node.Id); } 

        /// <summary>
        /// Deselects the actual node (and only this).
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public override void visitEnd(Columbus.Csharp.Asg.Nodes.Expression.AnonymousObjectCreationExpressionSyntax node, bool callVirtualBase) { selector(node.Id); } 

        /// <summary>
        /// Deselects the actual node (and only this).
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public override void visitEnd(Columbus.Csharp.Asg.Nodes.Expression.ArrayCreationExpressionSyntax node, bool callVirtualBase) { selector(node.Id); } 

        /// <summary>
        /// Deselects the actual node (and only this).
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public override void visitEnd(Columbus.Csharp.Asg.Nodes.Expression.ArrayTypeSyntax node, bool callVirtualBase) { selector(node.Id); } 

        /// <summary>
        /// Deselects the actual node (and only this).
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public override void visitEnd(Columbus.Csharp.Asg.Nodes.Expression.AssignmentExpressionSyntax node, bool callVirtualBase) { selector(node.Id); } 

        /// <summary>
        /// Deselects the actual node (and only this).
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public override void visitEnd(Columbus.Csharp.Asg.Nodes.Expression.AwaitExpressionSyntax node, bool callVirtualBase) { selector(node.Id); } 

        /// <summary>
        /// Deselects the actual node (and only this).
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public override void visitEnd(Columbus.Csharp.Asg.Nodes.Expression.BaseExpressionSyntax node, bool callVirtualBase) { selector(node.Id); } 

        /// <summary>
        /// Deselects the actual node (and only this).
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public override void visitEnd(Columbus.Csharp.Asg.Nodes.Expression.BinaryExpressionSyntax node, bool callVirtualBase) { selector(node.Id); } 

        /// <summary>
        /// Deselects the actual node (and only this).
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public override void visitEnd(Columbus.Csharp.Asg.Nodes.Expression.CastExpressionSyntax node, bool callVirtualBase) { selector(node.Id); } 

        /// <summary>
        /// Deselects the actual node (and only this).
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public override void visitEnd(Columbus.Csharp.Asg.Nodes.Expression.CheckedExpressionSyntax node, bool callVirtualBase) { selector(node.Id); } 

        /// <summary>
        /// Deselects the actual node (and only this).
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public override void visitEnd(Columbus.Csharp.Asg.Nodes.Expression.ConditionalAccessExpressionSyntax node, bool callVirtualBase) { selector(node.Id); } 

        /// <summary>
        /// Deselects the actual node (and only this).
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public override void visitEnd(Columbus.Csharp.Asg.Nodes.Expression.ConditionalExpressionSyntax node, bool callVirtualBase) { selector(node.Id); } 

        /// <summary>
        /// Deselects the actual node (and only this).
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public override void visitEnd(Columbus.Csharp.Asg.Nodes.Expression.DeclarationExpressionSyntax node, bool callVirtualBase) { selector(node.Id); } 

        /// <summary>
        /// Deselects the actual node (and only this).
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public override void visitEnd(Columbus.Csharp.Asg.Nodes.Expression.DefaultExpressionSyntax node, bool callVirtualBase) { selector(node.Id); } 

        /// <summary>
        /// Deselects the actual node (and only this).
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public override void visitEnd(Columbus.Csharp.Asg.Nodes.Expression.ElementAccessExpressionSyntax node, bool callVirtualBase) { selector(node.Id); } 

        /// <summary>
        /// Deselects the actual node (and only this).
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public override void visitEnd(Columbus.Csharp.Asg.Nodes.Expression.ElementBindingExpressionSyntax node, bool callVirtualBase) { selector(node.Id); } 

        /// <summary>
        /// Deselects the actual node (and only this).
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public override void visitEnd(Columbus.Csharp.Asg.Nodes.Expression.GenericNameSyntax node, bool callVirtualBase) { selector(node.Id); } 

        /// <summary>
        /// Deselects the actual node (and only this).
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public override void visitEnd(Columbus.Csharp.Asg.Nodes.Expression.IdentifierNameSyntax node, bool callVirtualBase) { selector(node.Id); } 

        /// <summary>
        /// Deselects the actual node (and only this).
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public override void visitEnd(Columbus.Csharp.Asg.Nodes.Expression.ImplicitArrayCreationExpressionSyntax node, bool callVirtualBase) { selector(node.Id); } 

        /// <summary>
        /// Deselects the actual node (and only this).
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public override void visitEnd(Columbus.Csharp.Asg.Nodes.Expression.ImplicitElementAccessSyntax node, bool callVirtualBase) { selector(node.Id); } 

        /// <summary>
        /// Deselects the actual node (and only this).
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public override void visitEnd(Columbus.Csharp.Asg.Nodes.Expression.ImplicitStackAllocArrayCreationExpressionSyntax node, bool callVirtualBase) { selector(node.Id); } 

        /// <summary>
        /// Deselects the actual node (and only this).
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public override void visitEnd(Columbus.Csharp.Asg.Nodes.Expression.InitializerExpressionSyntax node, bool callVirtualBase) { selector(node.Id); } 

        /// <summary>
        /// Deselects the actual node (and only this).
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public override void visitEnd(Columbus.Csharp.Asg.Nodes.Expression.InterpolatedStringExpressionSyntax node, bool callVirtualBase) { selector(node.Id); } 

        /// <summary>
        /// Deselects the actual node (and only this).
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public override void visitEnd(Columbus.Csharp.Asg.Nodes.Expression.InvocationExpressionSyntax node, bool callVirtualBase) { selector(node.Id); } 

        /// <summary>
        /// Deselects the actual node (and only this).
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public override void visitEnd(Columbus.Csharp.Asg.Nodes.Expression.IsPatternExpressionSyntax node, bool callVirtualBase) { selector(node.Id); } 

        /// <summary>
        /// Deselects the actual node (and only this).
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public override void visitEnd(Columbus.Csharp.Asg.Nodes.Expression.LiteralExpressionSyntax node, bool callVirtualBase) { selector(node.Id); } 

        /// <summary>
        /// Deselects the actual node (and only this).
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public override void visitEnd(Columbus.Csharp.Asg.Nodes.Expression.MakeRefExpressionSyntax node, bool callVirtualBase) { selector(node.Id); } 

        /// <summary>
        /// Deselects the actual node (and only this).
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public override void visitEnd(Columbus.Csharp.Asg.Nodes.Expression.MemberAccessExpressionSyntax node, bool callVirtualBase) { selector(node.Id); } 

        /// <summary>
        /// Deselects the actual node (and only this).
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public override void visitEnd(Columbus.Csharp.Asg.Nodes.Expression.MemberBindingExpressionSyntax node, bool callVirtualBase) { selector(node.Id); } 

        /// <summary>
        /// Deselects the actual node (and only this).
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public override void visitEnd(Columbus.Csharp.Asg.Nodes.Expression.NullableTypeSyntax node, bool callVirtualBase) { selector(node.Id); } 

        /// <summary>
        /// Deselects the actual node (and only this).
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public override void visitEnd(Columbus.Csharp.Asg.Nodes.Expression.ObjectCreationExpressionSyntax node, bool callVirtualBase) { selector(node.Id); } 

        /// <summary>
        /// Deselects the actual node (and only this).
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public override void visitEnd(Columbus.Csharp.Asg.Nodes.Expression.OmittedArraySizeExpressionSyntax node, bool callVirtualBase) { selector(node.Id); } 

        /// <summary>
        /// Deselects the actual node (and only this).
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public override void visitEnd(Columbus.Csharp.Asg.Nodes.Expression.OmittedTypeArgumentSyntax node, bool callVirtualBase) { selector(node.Id); } 

        /// <summary>
        /// Deselects the actual node (and only this).
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public override void visitEnd(Columbus.Csharp.Asg.Nodes.Expression.ParenthesizedExpressionSyntax node, bool callVirtualBase) { selector(node.Id); } 

        /// <summary>
        /// Deselects the actual node (and only this).
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public override void visitEnd(Columbus.Csharp.Asg.Nodes.Expression.ParenthesizedLambdaExpressionSyntax node, bool callVirtualBase) { selector(node.Id); } 

        /// <summary>
        /// Deselects the actual node (and only this).
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public override void visitEnd(Columbus.Csharp.Asg.Nodes.Expression.PointerTypeSyntax node, bool callVirtualBase) { selector(node.Id); } 

        /// <summary>
        /// Deselects the actual node (and only this).
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public override void visitEnd(Columbus.Csharp.Asg.Nodes.Expression.PostfixUnaryExpressionSyntax node, bool callVirtualBase) { selector(node.Id); } 

        /// <summary>
        /// Deselects the actual node (and only this).
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public override void visitEnd(Columbus.Csharp.Asg.Nodes.Expression.PredefinedTypeSyntax node, bool callVirtualBase) { selector(node.Id); } 

        /// <summary>
        /// Deselects the actual node (and only this).
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public override void visitEnd(Columbus.Csharp.Asg.Nodes.Expression.PrefixUnaryExpressionSyntax node, bool callVirtualBase) { selector(node.Id); } 

        /// <summary>
        /// Deselects the actual node (and only this).
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public override void visitEnd(Columbus.Csharp.Asg.Nodes.Expression.QualifiedNameSyntax node, bool callVirtualBase) { selector(node.Id); } 

        /// <summary>
        /// Deselects the actual node (and only this).
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public override void visitEnd(Columbus.Csharp.Asg.Nodes.Expression.QueryExpressionSyntax node, bool callVirtualBase) { selector(node.Id); } 

        /// <summary>
        /// Deselects the actual node (and only this).
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public override void visitEnd(Columbus.Csharp.Asg.Nodes.Expression.RangeExpressionSyntax node, bool callVirtualBase) { selector(node.Id); } 

        /// <summary>
        /// Deselects the actual node (and only this).
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public override void visitEnd(Columbus.Csharp.Asg.Nodes.Expression.RefExpressionSyntax node, bool callVirtualBase) { selector(node.Id); } 

        /// <summary>
        /// Deselects the actual node (and only this).
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public override void visitEnd(Columbus.Csharp.Asg.Nodes.Expression.RefTypeExpressionSyntax node, bool callVirtualBase) { selector(node.Id); } 

        /// <summary>
        /// Deselects the actual node (and only this).
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public override void visitEnd(Columbus.Csharp.Asg.Nodes.Expression.RefTypeSyntax node, bool callVirtualBase) { selector(node.Id); } 

        /// <summary>
        /// Deselects the actual node (and only this).
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public override void visitEnd(Columbus.Csharp.Asg.Nodes.Expression.RefValueExpressionSyntax node, bool callVirtualBase) { selector(node.Id); } 

        /// <summary>
        /// Deselects the actual node (and only this).
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public override void visitEnd(Columbus.Csharp.Asg.Nodes.Expression.SimpleLambdaExpressionSyntax node, bool callVirtualBase) { selector(node.Id); } 

        /// <summary>
        /// Deselects the actual node (and only this).
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public override void visitEnd(Columbus.Csharp.Asg.Nodes.Expression.SizeOfExpressionSyntax node, bool callVirtualBase) { selector(node.Id); } 

        /// <summary>
        /// Deselects the actual node (and only this).
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public override void visitEnd(Columbus.Csharp.Asg.Nodes.Expression.StackAllocArrayCreationExpressionSyntax node, bool callVirtualBase) { selector(node.Id); } 

        /// <summary>
        /// Deselects the actual node (and only this).
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public override void visitEnd(Columbus.Csharp.Asg.Nodes.Expression.SwitchExpressionSyntax node, bool callVirtualBase) { selector(node.Id); } 

        /// <summary>
        /// Deselects the actual node (and only this).
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public override void visitEnd(Columbus.Csharp.Asg.Nodes.Expression.ThisExpressionSyntax node, bool callVirtualBase) { selector(node.Id); } 

        /// <summary>
        /// Deselects the actual node (and only this).
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public override void visitEnd(Columbus.Csharp.Asg.Nodes.Expression.ThrowExpressionSyntax node, bool callVirtualBase) { selector(node.Id); } 

        /// <summary>
        /// Deselects the actual node (and only this).
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public override void visitEnd(Columbus.Csharp.Asg.Nodes.Expression.TupleExpressionSyntax node, bool callVirtualBase) { selector(node.Id); } 

        /// <summary>
        /// Deselects the actual node (and only this).
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public override void visitEnd(Columbus.Csharp.Asg.Nodes.Expression.TupleTypeSyntax node, bool callVirtualBase) { selector(node.Id); } 

        /// <summary>
        /// Deselects the actual node (and only this).
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public override void visitEnd(Columbus.Csharp.Asg.Nodes.Expression.TypeOfExpressionSyntax node, bool callVirtualBase) { selector(node.Id); } 

        /// <summary>
        /// Deselects the actual node (and only this).
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public override void visitEnd(Columbus.Csharp.Asg.Nodes.Statement.BlockSyntax node, bool callVirtualBase) { selector(node.Id); } 

        /// <summary>
        /// Deselects the actual node (and only this).
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public override void visitEnd(Columbus.Csharp.Asg.Nodes.Statement.BreakStatementSyntax node, bool callVirtualBase) { selector(node.Id); } 

        /// <summary>
        /// Deselects the actual node (and only this).
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public override void visitEnd(Columbus.Csharp.Asg.Nodes.Statement.CheckedStatementSyntax node, bool callVirtualBase) { selector(node.Id); } 

        /// <summary>
        /// Deselects the actual node (and only this).
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public override void visitEnd(Columbus.Csharp.Asg.Nodes.Statement.ContinueStatementSyntax node, bool callVirtualBase) { selector(node.Id); } 

        /// <summary>
        /// Deselects the actual node (and only this).
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public override void visitEnd(Columbus.Csharp.Asg.Nodes.Statement.DoStatementSyntax node, bool callVirtualBase) { selector(node.Id); } 

        /// <summary>
        /// Deselects the actual node (and only this).
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public override void visitEnd(Columbus.Csharp.Asg.Nodes.Statement.EmptyStatementSyntax node, bool callVirtualBase) { selector(node.Id); } 

        /// <summary>
        /// Deselects the actual node (and only this).
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public override void visitEnd(Columbus.Csharp.Asg.Nodes.Statement.ExpressionStatementSyntax node, bool callVirtualBase) { selector(node.Id); } 

        /// <summary>
        /// Deselects the actual node (and only this).
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public override void visitEnd(Columbus.Csharp.Asg.Nodes.Statement.FixedStatementSyntax node, bool callVirtualBase) { selector(node.Id); } 

        /// <summary>
        /// Deselects the actual node (and only this).
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public override void visitEnd(Columbus.Csharp.Asg.Nodes.Statement.ForEachStatementSyntax node, bool callVirtualBase) { selector(node.Id); } 

        /// <summary>
        /// Deselects the actual node (and only this).
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public override void visitEnd(Columbus.Csharp.Asg.Nodes.Statement.ForEachVariableStatementSyntax node, bool callVirtualBase) { selector(node.Id); } 

        /// <summary>
        /// Deselects the actual node (and only this).
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public override void visitEnd(Columbus.Csharp.Asg.Nodes.Statement.ForStatementSyntax node, bool callVirtualBase) { selector(node.Id); } 

        /// <summary>
        /// Deselects the actual node (and only this).
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public override void visitEnd(Columbus.Csharp.Asg.Nodes.Statement.GotoStatementSyntax node, bool callVirtualBase) { selector(node.Id); } 

        /// <summary>
        /// Deselects the actual node (and only this).
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public override void visitEnd(Columbus.Csharp.Asg.Nodes.Statement.IfStatementSyntax node, bool callVirtualBase) { selector(node.Id); } 

        /// <summary>
        /// Deselects the actual node (and only this).
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public override void visitEnd(Columbus.Csharp.Asg.Nodes.Statement.LabeledStatementSyntax node, bool callVirtualBase) { selector(node.Id); } 

        /// <summary>
        /// Deselects the actual node (and only this).
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public override void visitEnd(Columbus.Csharp.Asg.Nodes.Statement.LocalDeclarationStatementSyntax node, bool callVirtualBase) { selector(node.Id); } 

        /// <summary>
        /// Deselects the actual node (and only this).
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public override void visitEnd(Columbus.Csharp.Asg.Nodes.Statement.LocalFunctionStatementSyntax node, bool callVirtualBase) { selector(node.Id); } 

        /// <summary>
        /// Deselects the actual node (and only this).
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public override void visitEnd(Columbus.Csharp.Asg.Nodes.Statement.LockStatementSyntax node, bool callVirtualBase) { selector(node.Id); } 

        /// <summary>
        /// Deselects the actual node (and only this).
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public override void visitEnd(Columbus.Csharp.Asg.Nodes.Statement.ReturnStatementSyntax node, bool callVirtualBase) { selector(node.Id); } 

        /// <summary>
        /// Deselects the actual node (and only this).
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public override void visitEnd(Columbus.Csharp.Asg.Nodes.Statement.SwitchStatementSyntax node, bool callVirtualBase) { selector(node.Id); } 

        /// <summary>
        /// Deselects the actual node (and only this).
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public override void visitEnd(Columbus.Csharp.Asg.Nodes.Statement.ThrowStatementSyntax node, bool callVirtualBase) { selector(node.Id); } 

        /// <summary>
        /// Deselects the actual node (and only this).
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public override void visitEnd(Columbus.Csharp.Asg.Nodes.Statement.TryStatementSyntax node, bool callVirtualBase) { selector(node.Id); } 

        /// <summary>
        /// Deselects the actual node (and only this).
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public override void visitEnd(Columbus.Csharp.Asg.Nodes.Statement.UnsafeStatementSyntax node, bool callVirtualBase) { selector(node.Id); } 

        /// <summary>
        /// Deselects the actual node (and only this).
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public override void visitEnd(Columbus.Csharp.Asg.Nodes.Statement.UsingStatementSyntax node, bool callVirtualBase) { selector(node.Id); } 

        /// <summary>
        /// Deselects the actual node (and only this).
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public override void visitEnd(Columbus.Csharp.Asg.Nodes.Statement.WhileStatementSyntax node, bool callVirtualBase) { selector(node.Id); } 

        /// <summary>
        /// Deselects the actual node (and only this).
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public override void visitEnd(Columbus.Csharp.Asg.Nodes.Statement.YieldStatementSyntax node, bool callVirtualBase) { selector(node.Id); } 

        /// <summary>
        /// Deselects the actual node (and only this).
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public override void visitEnd(Columbus.Csharp.Asg.Nodes.Structure.AccessorDeclarationSyntax node, bool callVirtualBase) { selector(node.Id); } 

        /// <summary>
        /// Deselects the actual node (and only this).
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public override void visitEnd(Columbus.Csharp.Asg.Nodes.Structure.AccessorListSyntax node, bool callVirtualBase) { selector(node.Id); } 

        /// <summary>
        /// Deselects the actual node (and only this).
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public override void visitEnd(Columbus.Csharp.Asg.Nodes.Structure.AnonymousObjectMemberDeclaratorSyntax node, bool callVirtualBase) { selector(node.Id); } 

        /// <summary>
        /// Deselects the actual node (and only this).
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public override void visitEnd(Columbus.Csharp.Asg.Nodes.Structure.ArgumentListSyntax node, bool callVirtualBase) { selector(node.Id); } 

        /// <summary>
        /// Deselects the actual node (and only this).
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public override void visitEnd(Columbus.Csharp.Asg.Nodes.Structure.ArgumentSyntax node, bool callVirtualBase) { selector(node.Id); } 

        /// <summary>
        /// Deselects the actual node (and only this).
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public override void visitEnd(Columbus.Csharp.Asg.Nodes.Structure.ArrayRankSpecifierSyntax node, bool callVirtualBase) { selector(node.Id); } 

        /// <summary>
        /// Deselects the actual node (and only this).
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public override void visitEnd(Columbus.Csharp.Asg.Nodes.Structure.ArrowExpressionClauseSyntax node, bool callVirtualBase) { selector(node.Id); } 

        /// <summary>
        /// Deselects the actual node (and only this).
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public override void visitEnd(Columbus.Csharp.Asg.Nodes.Structure.AttributeArgumentListSyntax node, bool callVirtualBase) { selector(node.Id); } 

        /// <summary>
        /// Deselects the actual node (and only this).
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public override void visitEnd(Columbus.Csharp.Asg.Nodes.Structure.AttributeArgumentSyntax node, bool callVirtualBase) { selector(node.Id); } 

        /// <summary>
        /// Deselects the actual node (and only this).
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public override void visitEnd(Columbus.Csharp.Asg.Nodes.Structure.AttributeListSyntax node, bool callVirtualBase) { selector(node.Id); } 

        /// <summary>
        /// Deselects the actual node (and only this).
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public override void visitEnd(Columbus.Csharp.Asg.Nodes.Structure.AttributeSyntax node, bool callVirtualBase) { selector(node.Id); } 

        /// <summary>
        /// Deselects the actual node (and only this).
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public override void visitEnd(Columbus.Csharp.Asg.Nodes.Structure.AttributeTargetSpecifierSyntax node, bool callVirtualBase) { selector(node.Id); } 

        /// <summary>
        /// Deselects the actual node (and only this).
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public override void visitEnd(Columbus.Csharp.Asg.Nodes.Structure.BaseListSyntax node, bool callVirtualBase) { selector(node.Id); } 

        /// <summary>
        /// Deselects the actual node (and only this).
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public override void visitEnd(Columbus.Csharp.Asg.Nodes.Structure.BracketedArgumentListSyntax node, bool callVirtualBase) { selector(node.Id); } 

        /// <summary>
        /// Deselects the actual node (and only this).
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public override void visitEnd(Columbus.Csharp.Asg.Nodes.Structure.BracketedParameterListSyntax node, bool callVirtualBase) { selector(node.Id); } 

        /// <summary>
        /// Deselects the actual node (and only this).
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public override void visitEnd(Columbus.Csharp.Asg.Nodes.Structure.CasePatternSwitchLabelSyntax node, bool callVirtualBase) { selector(node.Id); } 

        /// <summary>
        /// Deselects the actual node (and only this).
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public override void visitEnd(Columbus.Csharp.Asg.Nodes.Structure.CaseSwitchLabelSyntax node, bool callVirtualBase) { selector(node.Id); } 

        /// <summary>
        /// Deselects the actual node (and only this).
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public override void visitEnd(Columbus.Csharp.Asg.Nodes.Structure.CatchClauseSyntax node, bool callVirtualBase) { selector(node.Id); } 

        /// <summary>
        /// Deselects the actual node (and only this).
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public override void visitEnd(Columbus.Csharp.Asg.Nodes.Structure.CatchDeclarationSyntax node, bool callVirtualBase) { selector(node.Id); } 

        /// <summary>
        /// Deselects the actual node (and only this).
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public override void visitEnd(Columbus.Csharp.Asg.Nodes.Structure.CatchFilterClauseSyntax node, bool callVirtualBase) { selector(node.Id); } 

        /// <summary>
        /// Deselects the actual node (and only this).
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public override void visitEnd(Columbus.Csharp.Asg.Nodes.Structure.ClassDeclarationSyntax node, bool callVirtualBase) { selector(node.Id); } 

        /// <summary>
        /// Deselects the actual node (and only this).
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public override void visitEnd(Columbus.Csharp.Asg.Nodes.Structure.ClassOrStructConstraintSyntax node, bool callVirtualBase) { selector(node.Id); } 

        /// <summary>
        /// Deselects the actual node (and only this).
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public override void visitEnd(Columbus.Csharp.Asg.Nodes.Structure.CompilationUnitSyntax node, bool callVirtualBase) { selector(node.Id); } 

        /// <summary>
        /// Deselects the actual node (and only this).
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public override void visitEnd(Columbus.Csharp.Asg.Nodes.Structure.ConstantPatternSyntax node, bool callVirtualBase) { selector(node.Id); } 

        /// <summary>
        /// Deselects the actual node (and only this).
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public override void visitEnd(Columbus.Csharp.Asg.Nodes.Structure.ConstructorConstraintSyntax node, bool callVirtualBase) { selector(node.Id); } 

        /// <summary>
        /// Deselects the actual node (and only this).
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public override void visitEnd(Columbus.Csharp.Asg.Nodes.Structure.ConstructorDeclarationSyntax node, bool callVirtualBase) { selector(node.Id); } 

        /// <summary>
        /// Deselects the actual node (and only this).
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public override void visitEnd(Columbus.Csharp.Asg.Nodes.Structure.ConstructorInitializerSyntax node, bool callVirtualBase) { selector(node.Id); } 

        /// <summary>
        /// Deselects the actual node (and only this).
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public override void visitEnd(Columbus.Csharp.Asg.Nodes.Structure.ConversionOperatorDeclarationSyntax node, bool callVirtualBase) { selector(node.Id); } 

        /// <summary>
        /// Deselects the actual node (and only this).
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public override void visitEnd(Columbus.Csharp.Asg.Nodes.Structure.ConversionOperatorMemberCrefSyntax node, bool callVirtualBase) { selector(node.Id); } 

        /// <summary>
        /// Deselects the actual node (and only this).
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public override void visitEnd(Columbus.Csharp.Asg.Nodes.Structure.CrefBracketedParameterListSyntax node, bool callVirtualBase) { selector(node.Id); } 

        /// <summary>
        /// Deselects the actual node (and only this).
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public override void visitEnd(Columbus.Csharp.Asg.Nodes.Structure.CrefParameterListSyntax node, bool callVirtualBase) { selector(node.Id); } 

        /// <summary>
        /// Deselects the actual node (and only this).
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public override void visitEnd(Columbus.Csharp.Asg.Nodes.Structure.CrefParameterSyntax node, bool callVirtualBase) { selector(node.Id); } 

        /// <summary>
        /// Deselects the actual node (and only this).
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public override void visitEnd(Columbus.Csharp.Asg.Nodes.Structure.DeclarationPatternSyntax node, bool callVirtualBase) { selector(node.Id); } 

        /// <summary>
        /// Deselects the actual node (and only this).
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public override void visitEnd(Columbus.Csharp.Asg.Nodes.Structure.DefaultSwitchLabelSyntax node, bool callVirtualBase) { selector(node.Id); } 

        /// <summary>
        /// Deselects the actual node (and only this).
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public override void visitEnd(Columbus.Csharp.Asg.Nodes.Structure.DelegateDeclarationSyntax node, bool callVirtualBase) { selector(node.Id); } 

        /// <summary>
        /// Deselects the actual node (and only this).
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public override void visitEnd(Columbus.Csharp.Asg.Nodes.Structure.DestructorDeclarationSyntax node, bool callVirtualBase) { selector(node.Id); } 

        /// <summary>
        /// Deselects the actual node (and only this).
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public override void visitEnd(Columbus.Csharp.Asg.Nodes.Structure.DiscardDesignationSyntax node, bool callVirtualBase) { selector(node.Id); } 

        /// <summary>
        /// Deselects the actual node (and only this).
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public override void visitEnd(Columbus.Csharp.Asg.Nodes.Structure.DiscardPatternSyntax node, bool callVirtualBase) { selector(node.Id); } 

        /// <summary>
        /// Deselects the actual node (and only this).
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public override void visitEnd(Columbus.Csharp.Asg.Nodes.Structure.ElseClauseSyntax node, bool callVirtualBase) { selector(node.Id); } 

        /// <summary>
        /// Deselects the actual node (and only this).
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public override void visitEnd(Columbus.Csharp.Asg.Nodes.Structure.EnumDeclarationSyntax node, bool callVirtualBase) { selector(node.Id); } 

        /// <summary>
        /// Deselects the actual node (and only this).
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public override void visitEnd(Columbus.Csharp.Asg.Nodes.Structure.EnumMemberDeclarationSyntax node, bool callVirtualBase) { selector(node.Id); } 

        /// <summary>
        /// Deselects the actual node (and only this).
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public override void visitEnd(Columbus.Csharp.Asg.Nodes.Structure.EqualsValueClauseSyntax node, bool callVirtualBase) { selector(node.Id); } 

        /// <summary>
        /// Deselects the actual node (and only this).
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public override void visitEnd(Columbus.Csharp.Asg.Nodes.Structure.EventDeclarationSyntax node, bool callVirtualBase) { selector(node.Id); } 

        /// <summary>
        /// Deselects the actual node (and only this).
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public override void visitEnd(Columbus.Csharp.Asg.Nodes.Structure.EventFieldDeclarationSyntax node, bool callVirtualBase) { selector(node.Id); } 

        /// <summary>
        /// Deselects the actual node (and only this).
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public override void visitEnd(Columbus.Csharp.Asg.Nodes.Structure.ExplicitInterfaceSpecifierSyntax node, bool callVirtualBase) { selector(node.Id); } 

        /// <summary>
        /// Deselects the actual node (and only this).
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public override void visitEnd(Columbus.Csharp.Asg.Nodes.Structure.ExternAliasDirectiveSyntax node, bool callVirtualBase) { selector(node.Id); } 

        /// <summary>
        /// Deselects the actual node (and only this).
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public override void visitEnd(Columbus.Csharp.Asg.Nodes.Structure.FieldDeclarationSyntax node, bool callVirtualBase) { selector(node.Id); } 

        /// <summary>
        /// Deselects the actual node (and only this).
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public override void visitEnd(Columbus.Csharp.Asg.Nodes.Structure.FinallyClauseSyntax node, bool callVirtualBase) { selector(node.Id); } 

        /// <summary>
        /// Deselects the actual node (and only this).
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public override void visitEnd(Columbus.Csharp.Asg.Nodes.Structure.FromClauseSyntax node, bool callVirtualBase) { selector(node.Id); } 

        /// <summary>
        /// Deselects the actual node (and only this).
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public override void visitEnd(Columbus.Csharp.Asg.Nodes.Structure.GlobalStatementSyntax node, bool callVirtualBase) { selector(node.Id); } 

        /// <summary>
        /// Deselects the actual node (and only this).
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public override void visitEnd(Columbus.Csharp.Asg.Nodes.Structure.GroupClauseSyntax node, bool callVirtualBase) { selector(node.Id); } 

        /// <summary>
        /// Deselects the actual node (and only this).
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public override void visitEnd(Columbus.Csharp.Asg.Nodes.Structure.IncompleteMemberSyntax node, bool callVirtualBase) { selector(node.Id); } 

        /// <summary>
        /// Deselects the actual node (and only this).
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public override void visitEnd(Columbus.Csharp.Asg.Nodes.Structure.IndexerDeclarationSyntax node, bool callVirtualBase) { selector(node.Id); } 

        /// <summary>
        /// Deselects the actual node (and only this).
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public override void visitEnd(Columbus.Csharp.Asg.Nodes.Structure.IndexerMemberCrefSyntax node, bool callVirtualBase) { selector(node.Id); } 

        /// <summary>
        /// Deselects the actual node (and only this).
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public override void visitEnd(Columbus.Csharp.Asg.Nodes.Structure.InterfaceDeclarationSyntax node, bool callVirtualBase) { selector(node.Id); } 

        /// <summary>
        /// Deselects the actual node (and only this).
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public override void visitEnd(Columbus.Csharp.Asg.Nodes.Structure.InterpolatedStringTextSyntax node, bool callVirtualBase) { selector(node.Id); } 

        /// <summary>
        /// Deselects the actual node (and only this).
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public override void visitEnd(Columbus.Csharp.Asg.Nodes.Structure.InterpolationAlignmentClauseSyntax node, bool callVirtualBase) { selector(node.Id); } 

        /// <summary>
        /// Deselects the actual node (and only this).
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public override void visitEnd(Columbus.Csharp.Asg.Nodes.Structure.InterpolationFormatClauseSyntax node, bool callVirtualBase) { selector(node.Id); } 

        /// <summary>
        /// Deselects the actual node (and only this).
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public override void visitEnd(Columbus.Csharp.Asg.Nodes.Structure.InterpolationSyntax node, bool callVirtualBase) { selector(node.Id); } 

        /// <summary>
        /// Deselects the actual node (and only this).
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public override void visitEnd(Columbus.Csharp.Asg.Nodes.Structure.JoinClauseSyntax node, bool callVirtualBase) { selector(node.Id); } 

        /// <summary>
        /// Deselects the actual node (and only this).
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public override void visitEnd(Columbus.Csharp.Asg.Nodes.Structure.JoinIntoClauseSyntax node, bool callVirtualBase) { selector(node.Id); } 

        /// <summary>
        /// Deselects the actual node (and only this).
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public override void visitEnd(Columbus.Csharp.Asg.Nodes.Structure.LetClauseSyntax node, bool callVirtualBase) { selector(node.Id); } 

        /// <summary>
        /// Deselects the actual node (and only this).
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public override void visitEnd(Columbus.Csharp.Asg.Nodes.Structure.MethodDeclarationSyntax node, bool callVirtualBase) { selector(node.Id); } 

        /// <summary>
        /// Deselects the actual node (and only this).
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public override void visitEnd(Columbus.Csharp.Asg.Nodes.Structure.NameColonSyntax node, bool callVirtualBase) { selector(node.Id); } 

        /// <summary>
        /// Deselects the actual node (and only this).
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public override void visitEnd(Columbus.Csharp.Asg.Nodes.Structure.NameEqualsSyntax node, bool callVirtualBase) { selector(node.Id); } 

        /// <summary>
        /// Deselects the actual node (and only this).
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public override void visitEnd(Columbus.Csharp.Asg.Nodes.Structure.NameMemberCrefSyntax node, bool callVirtualBase) { selector(node.Id); } 

        /// <summary>
        /// Deselects the actual node (and only this).
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public override void visitEnd(Columbus.Csharp.Asg.Nodes.Structure.NamespaceDeclarationSyntax node, bool callVirtualBase) { selector(node.Id); } 

        /// <summary>
        /// Deselects the actual node (and only this).
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public override void visitEnd(Columbus.Csharp.Asg.Nodes.Structure.OperatorDeclarationSyntax node, bool callVirtualBase) { selector(node.Id); } 

        /// <summary>
        /// Deselects the actual node (and only this).
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public override void visitEnd(Columbus.Csharp.Asg.Nodes.Structure.OperatorMemberCrefSyntax node, bool callVirtualBase) { selector(node.Id); } 

        /// <summary>
        /// Deselects the actual node (and only this).
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public override void visitEnd(Columbus.Csharp.Asg.Nodes.Structure.OrderByClauseSyntax node, bool callVirtualBase) { selector(node.Id); } 

        /// <summary>
        /// Deselects the actual node (and only this).
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public override void visitEnd(Columbus.Csharp.Asg.Nodes.Structure.OrderingSyntax node, bool callVirtualBase) { selector(node.Id); } 

        /// <summary>
        /// Deselects the actual node (and only this).
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public override void visitEnd(Columbus.Csharp.Asg.Nodes.Structure.ParameterListSyntax node, bool callVirtualBase) { selector(node.Id); } 

        /// <summary>
        /// Deselects the actual node (and only this).
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public override void visitEnd(Columbus.Csharp.Asg.Nodes.Structure.ParameterSyntax node, bool callVirtualBase) { selector(node.Id); } 

        /// <summary>
        /// Deselects the actual node (and only this).
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public override void visitEnd(Columbus.Csharp.Asg.Nodes.Structure.ParenthesizedVariableDesignationSyntax node, bool callVirtualBase) { selector(node.Id); } 

        /// <summary>
        /// Deselects the actual node (and only this).
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public override void visitEnd(Columbus.Csharp.Asg.Nodes.Structure.PositionalPatternClauseSyntax node, bool callVirtualBase) { selector(node.Id); } 

        /// <summary>
        /// Deselects the actual node (and only this).
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public override void visitEnd(Columbus.Csharp.Asg.Nodes.Structure.PropertyDeclarationSyntax node, bool callVirtualBase) { selector(node.Id); } 

        /// <summary>
        /// Deselects the actual node (and only this).
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public override void visitEnd(Columbus.Csharp.Asg.Nodes.Structure.PropertyPatternClauseSyntax node, bool callVirtualBase) { selector(node.Id); } 

        /// <summary>
        /// Deselects the actual node (and only this).
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public override void visitEnd(Columbus.Csharp.Asg.Nodes.Structure.QualifiedCrefSyntax node, bool callVirtualBase) { selector(node.Id); } 

        /// <summary>
        /// Deselects the actual node (and only this).
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public override void visitEnd(Columbus.Csharp.Asg.Nodes.Structure.QueryBodySyntax node, bool callVirtualBase) { selector(node.Id); } 

        /// <summary>
        /// Deselects the actual node (and only this).
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public override void visitEnd(Columbus.Csharp.Asg.Nodes.Structure.QueryContinuationSyntax node, bool callVirtualBase) { selector(node.Id); } 

        /// <summary>
        /// Deselects the actual node (and only this).
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public override void visitEnd(Columbus.Csharp.Asg.Nodes.Structure.RecursivePatternSyntax node, bool callVirtualBase) { selector(node.Id); } 

        /// <summary>
        /// Deselects the actual node (and only this).
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public override void visitEnd(Columbus.Csharp.Asg.Nodes.Structure.SelectClauseSyntax node, bool callVirtualBase) { selector(node.Id); } 

        /// <summary>
        /// Deselects the actual node (and only this).
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public override void visitEnd(Columbus.Csharp.Asg.Nodes.Structure.SimpleBaseTypeSyntax node, bool callVirtualBase) { selector(node.Id); } 

        /// <summary>
        /// Deselects the actual node (and only this).
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public override void visitEnd(Columbus.Csharp.Asg.Nodes.Structure.SingleVariableDesignationSyntax node, bool callVirtualBase) { selector(node.Id); } 

        /// <summary>
        /// Deselects the actual node (and only this).
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public override void visitEnd(Columbus.Csharp.Asg.Nodes.Structure.StructDeclarationSyntax node, bool callVirtualBase) { selector(node.Id); } 

        /// <summary>
        /// Deselects the actual node (and only this).
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public override void visitEnd(Columbus.Csharp.Asg.Nodes.Structure.SubpatternSyntax node, bool callVirtualBase) { selector(node.Id); } 

        /// <summary>
        /// Deselects the actual node (and only this).
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public override void visitEnd(Columbus.Csharp.Asg.Nodes.Structure.SwitchExpressionArmSyntax node, bool callVirtualBase) { selector(node.Id); } 

        /// <summary>
        /// Deselects the actual node (and only this).
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public override void visitEnd(Columbus.Csharp.Asg.Nodes.Structure.SwitchSectionSyntax node, bool callVirtualBase) { selector(node.Id); } 

        /// <summary>
        /// Deselects the actual node (and only this).
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public override void visitEnd(Columbus.Csharp.Asg.Nodes.Structure.SyntaxToken node, bool callVirtualBase) { selector(node.Id); } 

        /// <summary>
        /// Deselects the actual node (and only this).
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public override void visitEnd(Columbus.Csharp.Asg.Nodes.Structure.TupleElementSyntax node, bool callVirtualBase) { selector(node.Id); } 

        /// <summary>
        /// Deselects the actual node (and only this).
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public override void visitEnd(Columbus.Csharp.Asg.Nodes.Structure.TypeArgumentListSyntax node, bool callVirtualBase) { selector(node.Id); } 

        /// <summary>
        /// Deselects the actual node (and only this).
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public override void visitEnd(Columbus.Csharp.Asg.Nodes.Structure.TypeConstraintSyntax node, bool callVirtualBase) { selector(node.Id); } 

        /// <summary>
        /// Deselects the actual node (and only this).
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public override void visitEnd(Columbus.Csharp.Asg.Nodes.Structure.TypeCrefSyntax node, bool callVirtualBase) { selector(node.Id); } 

        /// <summary>
        /// Deselects the actual node (and only this).
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public override void visitEnd(Columbus.Csharp.Asg.Nodes.Structure.TypeParameterConstraintClauseSyntax node, bool callVirtualBase) { selector(node.Id); } 

        /// <summary>
        /// Deselects the actual node (and only this).
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public override void visitEnd(Columbus.Csharp.Asg.Nodes.Structure.TypeParameterListSyntax node, bool callVirtualBase) { selector(node.Id); } 

        /// <summary>
        /// Deselects the actual node (and only this).
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public override void visitEnd(Columbus.Csharp.Asg.Nodes.Structure.TypeParameterSyntax node, bool callVirtualBase) { selector(node.Id); } 

        /// <summary>
        /// Deselects the actual node (and only this).
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public override void visitEnd(Columbus.Csharp.Asg.Nodes.Structure.UsingDirectiveSyntax node, bool callVirtualBase) { selector(node.Id); } 

        /// <summary>
        /// Deselects the actual node (and only this).
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public override void visitEnd(Columbus.Csharp.Asg.Nodes.Structure.VarPatternSyntax node, bool callVirtualBase) { selector(node.Id); } 

        /// <summary>
        /// Deselects the actual node (and only this).
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public override void visitEnd(Columbus.Csharp.Asg.Nodes.Structure.VariableDeclarationSyntax node, bool callVirtualBase) { selector(node.Id); } 

        /// <summary>
        /// Deselects the actual node (and only this).
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public override void visitEnd(Columbus.Csharp.Asg.Nodes.Structure.VariableDeclaratorSyntax node, bool callVirtualBase) { selector(node.Id); } 

        /// <summary>
        /// Deselects the actual node (and only this).
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public override void visitEnd(Columbus.Csharp.Asg.Nodes.Structure.WhenClauseSyntax node, bool callVirtualBase) { selector(node.Id); } 

        /// <summary>
        /// Deselects the actual node (and only this).
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public override void visitEnd(Columbus.Csharp.Asg.Nodes.Structure.WhereClauseSyntax node, bool callVirtualBase) { selector(node.Id); } 

        /// <summary>
        /// Deselects the actual node (and only this).
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public override void visitEnd(Columbus.Csharp.Asg.Nodes.Structure.XmlCDataSectionSyntax node, bool callVirtualBase) { selector(node.Id); } 

        /// <summary>
        /// Deselects the actual node (and only this).
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public override void visitEnd(Columbus.Csharp.Asg.Nodes.Structure.XmlCommentSyntax node, bool callVirtualBase) { selector(node.Id); } 

        /// <summary>
        /// Deselects the actual node (and only this).
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public override void visitEnd(Columbus.Csharp.Asg.Nodes.Structure.XmlCrefAttributeSyntax node, bool callVirtualBase) { selector(node.Id); } 

        /// <summary>
        /// Deselects the actual node (and only this).
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public override void visitEnd(Columbus.Csharp.Asg.Nodes.Structure.XmlElementEndTagSyntax node, bool callVirtualBase) { selector(node.Id); } 

        /// <summary>
        /// Deselects the actual node (and only this).
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public override void visitEnd(Columbus.Csharp.Asg.Nodes.Structure.XmlElementStartTagSyntax node, bool callVirtualBase) { selector(node.Id); } 

        /// <summary>
        /// Deselects the actual node (and only this).
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public override void visitEnd(Columbus.Csharp.Asg.Nodes.Structure.XmlElementSyntax node, bool callVirtualBase) { selector(node.Id); } 

        /// <summary>
        /// Deselects the actual node (and only this).
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public override void visitEnd(Columbus.Csharp.Asg.Nodes.Structure.XmlEmptyElementSyntax node, bool callVirtualBase) { selector(node.Id); } 

        /// <summary>
        /// Deselects the actual node (and only this).
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public override void visitEnd(Columbus.Csharp.Asg.Nodes.Structure.XmlNameAttributeSyntax node, bool callVirtualBase) { selector(node.Id); } 

        /// <summary>
        /// Deselects the actual node (and only this).
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public override void visitEnd(Columbus.Csharp.Asg.Nodes.Structure.XmlNameSyntax node, bool callVirtualBase) { selector(node.Id); } 

        /// <summary>
        /// Deselects the actual node (and only this).
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public override void visitEnd(Columbus.Csharp.Asg.Nodes.Structure.XmlPrefixSyntax node, bool callVirtualBase) { selector(node.Id); } 

        /// <summary>
        /// Deselects the actual node (and only this).
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public override void visitEnd(Columbus.Csharp.Asg.Nodes.Structure.XmlProcessingInstructionSyntax node, bool callVirtualBase) { selector(node.Id); } 

        /// <summary>
        /// Deselects the actual node (and only this).
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public override void visitEnd(Columbus.Csharp.Asg.Nodes.Structure.XmlTextAttributeSyntax node, bool callVirtualBase) { selector(node.Id); } 

        /// <summary>
        /// Deselects the actual node (and only this).
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public override void visitEnd(Columbus.Csharp.Asg.Nodes.Structure.XmlTextSyntax node, bool callVirtualBase) { selector(node.Id); } 

    }

}
