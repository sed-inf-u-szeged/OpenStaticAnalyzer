using System;
using System.Text;

namespace Columbus.Csharp.Asg.Visitors {

    /// <summary>
    /// Visitor for each non-abstract nodes and all edges of the graph.
    /// </summary>
#if (CSHARP_INTERNAL)
    internal
#else
    public
#endif
    class VisitorAbstractNodes : Visitor {

        /// <summary>
        /// Constructor for VisitorAbstractNodes.
        /// </summary>
        public VisitorAbstractNodes() : base() {
        }

        /// <summary>
        /// Empty abstract visitor for Columbus.Csharp.Asg.Nodes.Base.Base node.
        /// </summary>
        public virtual void visit(Columbus.Csharp.Asg.Nodes.Base.Base node, bool callVirtualBase) {}

        public virtual void visitEnd(Columbus.Csharp.Asg.Nodes.Base.Base node, bool callVirtualBase) {}

        /// <summary>
        /// Abstract visitor, which calls the visitor of the base class (Columbus.Csharp.Asg.Nodes.Base.Base) of the Columbus.Csharp.Asg.Nodes.Base.Positioned node.
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public virtual void visit(Columbus.Csharp.Asg.Nodes.Base.Positioned node, bool callVirtualBase) {
            visit((Columbus.Csharp.Asg.Nodes.Base.Base)node, false);
        }

        /// <summary>
        /// Abstract end visitor, which calls the end visitor of the base class (Columbus.Csharp.Asg.Nodes.Base.Base) of the Columbus.Csharp.Asg.Nodes.Base.Positioned node.
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public virtual void visitEnd(Columbus.Csharp.Asg.Nodes.Base.Positioned node, bool callVirtualBase) {
            visitEnd((Columbus.Csharp.Asg.Nodes.Base.Base)node, false);
        }

        /// <summary>
        /// Abstract visitor, which calls the visitor of the base class (Columbus.Csharp.Asg.Nodes.Expression.NameSyntax) of the Columbus.Csharp.Asg.Nodes.Expression.AliasQualifiedNameSyntax node.
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public override void visit(Columbus.Csharp.Asg.Nodes.Expression.AliasQualifiedNameSyntax node, bool callVirtualBase) {
            visit((Columbus.Csharp.Asg.Nodes.Expression.NameSyntax)node, false);
        }

        /// <summary>
        /// Abstract end visitor, which calls the end visitor of the base class (Columbus.Csharp.Asg.Nodes.Expression.NameSyntax) of the Columbus.Csharp.Asg.Nodes.Expression.AliasQualifiedNameSyntax node.
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public override void visitEnd(Columbus.Csharp.Asg.Nodes.Expression.AliasQualifiedNameSyntax node, bool callVirtualBase) {
            visitEnd((Columbus.Csharp.Asg.Nodes.Expression.NameSyntax)node, false);
        }

        /// <summary>
        /// Abstract visitor, which calls the visitor of the base class (Columbus.Csharp.Asg.Nodes.Expression.ExpressionSyntax) of the Columbus.Csharp.Asg.Nodes.Expression.AnonymousFunctionExpressionSyntax node.
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public virtual void visit(Columbus.Csharp.Asg.Nodes.Expression.AnonymousFunctionExpressionSyntax node, bool callVirtualBase) {
            visit((Columbus.Csharp.Asg.Nodes.Expression.ExpressionSyntax)node, false);
        }

        /// <summary>
        /// Abstract end visitor, which calls the end visitor of the base class (Columbus.Csharp.Asg.Nodes.Expression.ExpressionSyntax) of the Columbus.Csharp.Asg.Nodes.Expression.AnonymousFunctionExpressionSyntax node.
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public virtual void visitEnd(Columbus.Csharp.Asg.Nodes.Expression.AnonymousFunctionExpressionSyntax node, bool callVirtualBase) {
            visitEnd((Columbus.Csharp.Asg.Nodes.Expression.ExpressionSyntax)node, false);
        }

        /// <summary>
        /// Abstract visitor, which calls the visitor of the base class (Columbus.Csharp.Asg.Nodes.Expression.AnonymousFunctionExpressionSyntax) of the Columbus.Csharp.Asg.Nodes.Expression.AnonymousMethodExpressionSyntax node.
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public override void visit(Columbus.Csharp.Asg.Nodes.Expression.AnonymousMethodExpressionSyntax node, bool callVirtualBase) {
            visit((Columbus.Csharp.Asg.Nodes.Expression.AnonymousFunctionExpressionSyntax)node, false);
        }

        /// <summary>
        /// Abstract end visitor, which calls the end visitor of the base class (Columbus.Csharp.Asg.Nodes.Expression.AnonymousFunctionExpressionSyntax) of the Columbus.Csharp.Asg.Nodes.Expression.AnonymousMethodExpressionSyntax node.
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public override void visitEnd(Columbus.Csharp.Asg.Nodes.Expression.AnonymousMethodExpressionSyntax node, bool callVirtualBase) {
            visitEnd((Columbus.Csharp.Asg.Nodes.Expression.AnonymousFunctionExpressionSyntax)node, false);
        }

        /// <summary>
        /// Abstract visitor, which calls the visitor of the base class (Columbus.Csharp.Asg.Nodes.Expression.ExpressionSyntax) of the Columbus.Csharp.Asg.Nodes.Expression.AnonymousObjectCreationExpressionSyntax node.
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public override void visit(Columbus.Csharp.Asg.Nodes.Expression.AnonymousObjectCreationExpressionSyntax node, bool callVirtualBase) {
            visit((Columbus.Csharp.Asg.Nodes.Expression.ExpressionSyntax)node, false);
        }

        /// <summary>
        /// Abstract end visitor, which calls the end visitor of the base class (Columbus.Csharp.Asg.Nodes.Expression.ExpressionSyntax) of the Columbus.Csharp.Asg.Nodes.Expression.AnonymousObjectCreationExpressionSyntax node.
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public override void visitEnd(Columbus.Csharp.Asg.Nodes.Expression.AnonymousObjectCreationExpressionSyntax node, bool callVirtualBase) {
            visitEnd((Columbus.Csharp.Asg.Nodes.Expression.ExpressionSyntax)node, false);
        }

        /// <summary>
        /// Abstract visitor, which calls the visitor of the base class (Columbus.Csharp.Asg.Nodes.Expression.ExpressionSyntax) of the Columbus.Csharp.Asg.Nodes.Expression.ArrayCreationExpressionSyntax node.
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public override void visit(Columbus.Csharp.Asg.Nodes.Expression.ArrayCreationExpressionSyntax node, bool callVirtualBase) {
            visit((Columbus.Csharp.Asg.Nodes.Expression.ExpressionSyntax)node, false);
        }

        /// <summary>
        /// Abstract end visitor, which calls the end visitor of the base class (Columbus.Csharp.Asg.Nodes.Expression.ExpressionSyntax) of the Columbus.Csharp.Asg.Nodes.Expression.ArrayCreationExpressionSyntax node.
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public override void visitEnd(Columbus.Csharp.Asg.Nodes.Expression.ArrayCreationExpressionSyntax node, bool callVirtualBase) {
            visitEnd((Columbus.Csharp.Asg.Nodes.Expression.ExpressionSyntax)node, false);
        }

        /// <summary>
        /// Abstract visitor, which calls the visitor of the base class (Columbus.Csharp.Asg.Nodes.Expression.TypeSyntax) of the Columbus.Csharp.Asg.Nodes.Expression.ArrayTypeSyntax node.
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public override void visit(Columbus.Csharp.Asg.Nodes.Expression.ArrayTypeSyntax node, bool callVirtualBase) {
            visit((Columbus.Csharp.Asg.Nodes.Expression.TypeSyntax)node, false);
        }

        /// <summary>
        /// Abstract end visitor, which calls the end visitor of the base class (Columbus.Csharp.Asg.Nodes.Expression.TypeSyntax) of the Columbus.Csharp.Asg.Nodes.Expression.ArrayTypeSyntax node.
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public override void visitEnd(Columbus.Csharp.Asg.Nodes.Expression.ArrayTypeSyntax node, bool callVirtualBase) {
            visitEnd((Columbus.Csharp.Asg.Nodes.Expression.TypeSyntax)node, false);
        }

        /// <summary>
        /// Abstract visitor, which calls the visitor of the base class (Columbus.Csharp.Asg.Nodes.Expression.ExpressionSyntax) of the Columbus.Csharp.Asg.Nodes.Expression.AssignmentExpressionSyntax node.
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public override void visit(Columbus.Csharp.Asg.Nodes.Expression.AssignmentExpressionSyntax node, bool callVirtualBase) {
            visit((Columbus.Csharp.Asg.Nodes.Expression.ExpressionSyntax)node, false);
        }

        /// <summary>
        /// Abstract end visitor, which calls the end visitor of the base class (Columbus.Csharp.Asg.Nodes.Expression.ExpressionSyntax) of the Columbus.Csharp.Asg.Nodes.Expression.AssignmentExpressionSyntax node.
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public override void visitEnd(Columbus.Csharp.Asg.Nodes.Expression.AssignmentExpressionSyntax node, bool callVirtualBase) {
            visitEnd((Columbus.Csharp.Asg.Nodes.Expression.ExpressionSyntax)node, false);
        }

        /// <summary>
        /// Abstract visitor, which calls the visitor of the base class (Columbus.Csharp.Asg.Nodes.Expression.ExpressionSyntax) of the Columbus.Csharp.Asg.Nodes.Expression.AwaitExpressionSyntax node.
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public override void visit(Columbus.Csharp.Asg.Nodes.Expression.AwaitExpressionSyntax node, bool callVirtualBase) {
            visit((Columbus.Csharp.Asg.Nodes.Expression.ExpressionSyntax)node, false);
        }

        /// <summary>
        /// Abstract end visitor, which calls the end visitor of the base class (Columbus.Csharp.Asg.Nodes.Expression.ExpressionSyntax) of the Columbus.Csharp.Asg.Nodes.Expression.AwaitExpressionSyntax node.
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public override void visitEnd(Columbus.Csharp.Asg.Nodes.Expression.AwaitExpressionSyntax node, bool callVirtualBase) {
            visitEnd((Columbus.Csharp.Asg.Nodes.Expression.ExpressionSyntax)node, false);
        }

        /// <summary>
        /// Abstract visitor, which calls the visitor of the base class (Columbus.Csharp.Asg.Nodes.Expression.InstanceExpressionSyntax) of the Columbus.Csharp.Asg.Nodes.Expression.BaseExpressionSyntax node.
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public override void visit(Columbus.Csharp.Asg.Nodes.Expression.BaseExpressionSyntax node, bool callVirtualBase) {
            visit((Columbus.Csharp.Asg.Nodes.Expression.InstanceExpressionSyntax)node, false);
        }

        /// <summary>
        /// Abstract end visitor, which calls the end visitor of the base class (Columbus.Csharp.Asg.Nodes.Expression.InstanceExpressionSyntax) of the Columbus.Csharp.Asg.Nodes.Expression.BaseExpressionSyntax node.
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public override void visitEnd(Columbus.Csharp.Asg.Nodes.Expression.BaseExpressionSyntax node, bool callVirtualBase) {
            visitEnd((Columbus.Csharp.Asg.Nodes.Expression.InstanceExpressionSyntax)node, false);
        }

        /// <summary>
        /// Abstract visitor, which calls the visitor of the base class (Columbus.Csharp.Asg.Nodes.Expression.ExpressionSyntax) of the Columbus.Csharp.Asg.Nodes.Expression.BinaryExpressionSyntax node.
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public override void visit(Columbus.Csharp.Asg.Nodes.Expression.BinaryExpressionSyntax node, bool callVirtualBase) {
            visit((Columbus.Csharp.Asg.Nodes.Expression.ExpressionSyntax)node, false);
        }

        /// <summary>
        /// Abstract end visitor, which calls the end visitor of the base class (Columbus.Csharp.Asg.Nodes.Expression.ExpressionSyntax) of the Columbus.Csharp.Asg.Nodes.Expression.BinaryExpressionSyntax node.
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public override void visitEnd(Columbus.Csharp.Asg.Nodes.Expression.BinaryExpressionSyntax node, bool callVirtualBase) {
            visitEnd((Columbus.Csharp.Asg.Nodes.Expression.ExpressionSyntax)node, false);
        }

        /// <summary>
        /// Abstract visitor, which calls the visitor of the base class (Columbus.Csharp.Asg.Nodes.Expression.ExpressionSyntax) of the Columbus.Csharp.Asg.Nodes.Expression.CastExpressionSyntax node.
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public override void visit(Columbus.Csharp.Asg.Nodes.Expression.CastExpressionSyntax node, bool callVirtualBase) {
            visit((Columbus.Csharp.Asg.Nodes.Expression.ExpressionSyntax)node, false);
        }

        /// <summary>
        /// Abstract end visitor, which calls the end visitor of the base class (Columbus.Csharp.Asg.Nodes.Expression.ExpressionSyntax) of the Columbus.Csharp.Asg.Nodes.Expression.CastExpressionSyntax node.
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public override void visitEnd(Columbus.Csharp.Asg.Nodes.Expression.CastExpressionSyntax node, bool callVirtualBase) {
            visitEnd((Columbus.Csharp.Asg.Nodes.Expression.ExpressionSyntax)node, false);
        }

        /// <summary>
        /// Abstract visitor, which calls the visitor of the base class (Columbus.Csharp.Asg.Nodes.Expression.ExpressionSyntax) of the Columbus.Csharp.Asg.Nodes.Expression.CheckedExpressionSyntax node.
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public override void visit(Columbus.Csharp.Asg.Nodes.Expression.CheckedExpressionSyntax node, bool callVirtualBase) {
            visit((Columbus.Csharp.Asg.Nodes.Expression.ExpressionSyntax)node, false);
        }

        /// <summary>
        /// Abstract end visitor, which calls the end visitor of the base class (Columbus.Csharp.Asg.Nodes.Expression.ExpressionSyntax) of the Columbus.Csharp.Asg.Nodes.Expression.CheckedExpressionSyntax node.
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public override void visitEnd(Columbus.Csharp.Asg.Nodes.Expression.CheckedExpressionSyntax node, bool callVirtualBase) {
            visitEnd((Columbus.Csharp.Asg.Nodes.Expression.ExpressionSyntax)node, false);
        }

        /// <summary>
        /// Abstract visitor, which calls the visitor of the base class (Columbus.Csharp.Asg.Nodes.Expression.ExpressionSyntax) of the Columbus.Csharp.Asg.Nodes.Expression.ConditionalAccessExpressionSyntax node.
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public override void visit(Columbus.Csharp.Asg.Nodes.Expression.ConditionalAccessExpressionSyntax node, bool callVirtualBase) {
            visit((Columbus.Csharp.Asg.Nodes.Expression.ExpressionSyntax)node, false);
        }

        /// <summary>
        /// Abstract end visitor, which calls the end visitor of the base class (Columbus.Csharp.Asg.Nodes.Expression.ExpressionSyntax) of the Columbus.Csharp.Asg.Nodes.Expression.ConditionalAccessExpressionSyntax node.
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public override void visitEnd(Columbus.Csharp.Asg.Nodes.Expression.ConditionalAccessExpressionSyntax node, bool callVirtualBase) {
            visitEnd((Columbus.Csharp.Asg.Nodes.Expression.ExpressionSyntax)node, false);
        }

        /// <summary>
        /// Abstract visitor, which calls the visitor of the base class (Columbus.Csharp.Asg.Nodes.Expression.ExpressionSyntax) of the Columbus.Csharp.Asg.Nodes.Expression.ConditionalExpressionSyntax node.
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public override void visit(Columbus.Csharp.Asg.Nodes.Expression.ConditionalExpressionSyntax node, bool callVirtualBase) {
            visit((Columbus.Csharp.Asg.Nodes.Expression.ExpressionSyntax)node, false);
        }

        /// <summary>
        /// Abstract end visitor, which calls the end visitor of the base class (Columbus.Csharp.Asg.Nodes.Expression.ExpressionSyntax) of the Columbus.Csharp.Asg.Nodes.Expression.ConditionalExpressionSyntax node.
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public override void visitEnd(Columbus.Csharp.Asg.Nodes.Expression.ConditionalExpressionSyntax node, bool callVirtualBase) {
            visitEnd((Columbus.Csharp.Asg.Nodes.Expression.ExpressionSyntax)node, false);
        }

        /// <summary>
        /// Abstract visitor, which calls the visitor of the base class (Columbus.Csharp.Asg.Nodes.Expression.ExpressionSyntax) of the Columbus.Csharp.Asg.Nodes.Expression.DeclarationExpressionSyntax node.
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public override void visit(Columbus.Csharp.Asg.Nodes.Expression.DeclarationExpressionSyntax node, bool callVirtualBase) {
            visit((Columbus.Csharp.Asg.Nodes.Expression.ExpressionSyntax)node, false);
        }

        /// <summary>
        /// Abstract end visitor, which calls the end visitor of the base class (Columbus.Csharp.Asg.Nodes.Expression.ExpressionSyntax) of the Columbus.Csharp.Asg.Nodes.Expression.DeclarationExpressionSyntax node.
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public override void visitEnd(Columbus.Csharp.Asg.Nodes.Expression.DeclarationExpressionSyntax node, bool callVirtualBase) {
            visitEnd((Columbus.Csharp.Asg.Nodes.Expression.ExpressionSyntax)node, false);
        }

        /// <summary>
        /// Abstract visitor, which calls the visitor of the base class (Columbus.Csharp.Asg.Nodes.Expression.ExpressionSyntax) of the Columbus.Csharp.Asg.Nodes.Expression.DefaultExpressionSyntax node.
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public override void visit(Columbus.Csharp.Asg.Nodes.Expression.DefaultExpressionSyntax node, bool callVirtualBase) {
            visit((Columbus.Csharp.Asg.Nodes.Expression.ExpressionSyntax)node, false);
        }

        /// <summary>
        /// Abstract end visitor, which calls the end visitor of the base class (Columbus.Csharp.Asg.Nodes.Expression.ExpressionSyntax) of the Columbus.Csharp.Asg.Nodes.Expression.DefaultExpressionSyntax node.
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public override void visitEnd(Columbus.Csharp.Asg.Nodes.Expression.DefaultExpressionSyntax node, bool callVirtualBase) {
            visitEnd((Columbus.Csharp.Asg.Nodes.Expression.ExpressionSyntax)node, false);
        }

        /// <summary>
        /// Abstract visitor, which calls the visitor of the base class (Columbus.Csharp.Asg.Nodes.Expression.ExpressionSyntax) of the Columbus.Csharp.Asg.Nodes.Expression.ElementAccessExpressionSyntax node.
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public override void visit(Columbus.Csharp.Asg.Nodes.Expression.ElementAccessExpressionSyntax node, bool callVirtualBase) {
            visit((Columbus.Csharp.Asg.Nodes.Expression.ExpressionSyntax)node, false);
        }

        /// <summary>
        /// Abstract end visitor, which calls the end visitor of the base class (Columbus.Csharp.Asg.Nodes.Expression.ExpressionSyntax) of the Columbus.Csharp.Asg.Nodes.Expression.ElementAccessExpressionSyntax node.
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public override void visitEnd(Columbus.Csharp.Asg.Nodes.Expression.ElementAccessExpressionSyntax node, bool callVirtualBase) {
            visitEnd((Columbus.Csharp.Asg.Nodes.Expression.ExpressionSyntax)node, false);
        }

        /// <summary>
        /// Abstract visitor, which calls the visitor of the base class (Columbus.Csharp.Asg.Nodes.Expression.ExpressionSyntax) of the Columbus.Csharp.Asg.Nodes.Expression.ElementBindingExpressionSyntax node.
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public override void visit(Columbus.Csharp.Asg.Nodes.Expression.ElementBindingExpressionSyntax node, bool callVirtualBase) {
            visit((Columbus.Csharp.Asg.Nodes.Expression.ExpressionSyntax)node, false);
        }

        /// <summary>
        /// Abstract end visitor, which calls the end visitor of the base class (Columbus.Csharp.Asg.Nodes.Expression.ExpressionSyntax) of the Columbus.Csharp.Asg.Nodes.Expression.ElementBindingExpressionSyntax node.
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public override void visitEnd(Columbus.Csharp.Asg.Nodes.Expression.ElementBindingExpressionSyntax node, bool callVirtualBase) {
            visitEnd((Columbus.Csharp.Asg.Nodes.Expression.ExpressionSyntax)node, false);
        }

        /// <summary>
        /// Abstract visitor, which calls the visitor of the base class (Columbus.Csharp.Asg.Nodes.Base.Positioned) of the Columbus.Csharp.Asg.Nodes.Expression.ExpressionSyntax node.
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public virtual void visit(Columbus.Csharp.Asg.Nodes.Expression.ExpressionSyntax node, bool callVirtualBase) {
            visit((Columbus.Csharp.Asg.Nodes.Base.Positioned)node, false);
        }

        /// <summary>
        /// Abstract end visitor, which calls the end visitor of the base class (Columbus.Csharp.Asg.Nodes.Base.Positioned) of the Columbus.Csharp.Asg.Nodes.Expression.ExpressionSyntax node.
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public virtual void visitEnd(Columbus.Csharp.Asg.Nodes.Expression.ExpressionSyntax node, bool callVirtualBase) {
            visitEnd((Columbus.Csharp.Asg.Nodes.Base.Positioned)node, false);
        }

        /// <summary>
        /// Abstract visitor, which calls the visitor of the base class (Columbus.Csharp.Asg.Nodes.Expression.SimpleNameSyntax) of the Columbus.Csharp.Asg.Nodes.Expression.GenericNameSyntax node.
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public override void visit(Columbus.Csharp.Asg.Nodes.Expression.GenericNameSyntax node, bool callVirtualBase) {
            visit((Columbus.Csharp.Asg.Nodes.Expression.SimpleNameSyntax)node, false);
        }

        /// <summary>
        /// Abstract end visitor, which calls the end visitor of the base class (Columbus.Csharp.Asg.Nodes.Expression.SimpleNameSyntax) of the Columbus.Csharp.Asg.Nodes.Expression.GenericNameSyntax node.
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public override void visitEnd(Columbus.Csharp.Asg.Nodes.Expression.GenericNameSyntax node, bool callVirtualBase) {
            visitEnd((Columbus.Csharp.Asg.Nodes.Expression.SimpleNameSyntax)node, false);
        }

        /// <summary>
        /// Abstract visitor, which calls the visitor of the base class (Columbus.Csharp.Asg.Nodes.Expression.SimpleNameSyntax) of the Columbus.Csharp.Asg.Nodes.Expression.IdentifierNameSyntax node.
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public override void visit(Columbus.Csharp.Asg.Nodes.Expression.IdentifierNameSyntax node, bool callVirtualBase) {
            visit((Columbus.Csharp.Asg.Nodes.Expression.SimpleNameSyntax)node, false);
        }

        /// <summary>
        /// Abstract end visitor, which calls the end visitor of the base class (Columbus.Csharp.Asg.Nodes.Expression.SimpleNameSyntax) of the Columbus.Csharp.Asg.Nodes.Expression.IdentifierNameSyntax node.
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public override void visitEnd(Columbus.Csharp.Asg.Nodes.Expression.IdentifierNameSyntax node, bool callVirtualBase) {
            visitEnd((Columbus.Csharp.Asg.Nodes.Expression.SimpleNameSyntax)node, false);
        }

        /// <summary>
        /// Abstract visitor, which calls the visitor of the base class (Columbus.Csharp.Asg.Nodes.Expression.ExpressionSyntax) of the Columbus.Csharp.Asg.Nodes.Expression.ImplicitArrayCreationExpressionSyntax node.
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public override void visit(Columbus.Csharp.Asg.Nodes.Expression.ImplicitArrayCreationExpressionSyntax node, bool callVirtualBase) {
            visit((Columbus.Csharp.Asg.Nodes.Expression.ExpressionSyntax)node, false);
        }

        /// <summary>
        /// Abstract end visitor, which calls the end visitor of the base class (Columbus.Csharp.Asg.Nodes.Expression.ExpressionSyntax) of the Columbus.Csharp.Asg.Nodes.Expression.ImplicitArrayCreationExpressionSyntax node.
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public override void visitEnd(Columbus.Csharp.Asg.Nodes.Expression.ImplicitArrayCreationExpressionSyntax node, bool callVirtualBase) {
            visitEnd((Columbus.Csharp.Asg.Nodes.Expression.ExpressionSyntax)node, false);
        }

        /// <summary>
        /// Abstract visitor, which calls the visitor of the base class (Columbus.Csharp.Asg.Nodes.Expression.ExpressionSyntax) of the Columbus.Csharp.Asg.Nodes.Expression.ImplicitElementAccessSyntax node.
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public override void visit(Columbus.Csharp.Asg.Nodes.Expression.ImplicitElementAccessSyntax node, bool callVirtualBase) {
            visit((Columbus.Csharp.Asg.Nodes.Expression.ExpressionSyntax)node, false);
        }

        /// <summary>
        /// Abstract end visitor, which calls the end visitor of the base class (Columbus.Csharp.Asg.Nodes.Expression.ExpressionSyntax) of the Columbus.Csharp.Asg.Nodes.Expression.ImplicitElementAccessSyntax node.
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public override void visitEnd(Columbus.Csharp.Asg.Nodes.Expression.ImplicitElementAccessSyntax node, bool callVirtualBase) {
            visitEnd((Columbus.Csharp.Asg.Nodes.Expression.ExpressionSyntax)node, false);
        }

        /// <summary>
        /// Abstract visitor, which calls the visitor of the base class (Columbus.Csharp.Asg.Nodes.Expression.ExpressionSyntax) of the Columbus.Csharp.Asg.Nodes.Expression.ImplicitStackAllocArrayCreationExpressionSyntax node.
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public override void visit(Columbus.Csharp.Asg.Nodes.Expression.ImplicitStackAllocArrayCreationExpressionSyntax node, bool callVirtualBase) {
            visit((Columbus.Csharp.Asg.Nodes.Expression.ExpressionSyntax)node, false);
        }

        /// <summary>
        /// Abstract end visitor, which calls the end visitor of the base class (Columbus.Csharp.Asg.Nodes.Expression.ExpressionSyntax) of the Columbus.Csharp.Asg.Nodes.Expression.ImplicitStackAllocArrayCreationExpressionSyntax node.
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public override void visitEnd(Columbus.Csharp.Asg.Nodes.Expression.ImplicitStackAllocArrayCreationExpressionSyntax node, bool callVirtualBase) {
            visitEnd((Columbus.Csharp.Asg.Nodes.Expression.ExpressionSyntax)node, false);
        }

        /// <summary>
        /// Abstract visitor, which calls the visitor of the base class (Columbus.Csharp.Asg.Nodes.Expression.ExpressionSyntax) of the Columbus.Csharp.Asg.Nodes.Expression.InitializerExpressionSyntax node.
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public override void visit(Columbus.Csharp.Asg.Nodes.Expression.InitializerExpressionSyntax node, bool callVirtualBase) {
            visit((Columbus.Csharp.Asg.Nodes.Expression.ExpressionSyntax)node, false);
        }

        /// <summary>
        /// Abstract end visitor, which calls the end visitor of the base class (Columbus.Csharp.Asg.Nodes.Expression.ExpressionSyntax) of the Columbus.Csharp.Asg.Nodes.Expression.InitializerExpressionSyntax node.
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public override void visitEnd(Columbus.Csharp.Asg.Nodes.Expression.InitializerExpressionSyntax node, bool callVirtualBase) {
            visitEnd((Columbus.Csharp.Asg.Nodes.Expression.ExpressionSyntax)node, false);
        }

        /// <summary>
        /// Abstract visitor, which calls the visitor of the base class (Columbus.Csharp.Asg.Nodes.Expression.ExpressionSyntax) of the Columbus.Csharp.Asg.Nodes.Expression.InstanceExpressionSyntax node.
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public virtual void visit(Columbus.Csharp.Asg.Nodes.Expression.InstanceExpressionSyntax node, bool callVirtualBase) {
            visit((Columbus.Csharp.Asg.Nodes.Expression.ExpressionSyntax)node, false);
        }

        /// <summary>
        /// Abstract end visitor, which calls the end visitor of the base class (Columbus.Csharp.Asg.Nodes.Expression.ExpressionSyntax) of the Columbus.Csharp.Asg.Nodes.Expression.InstanceExpressionSyntax node.
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public virtual void visitEnd(Columbus.Csharp.Asg.Nodes.Expression.InstanceExpressionSyntax node, bool callVirtualBase) {
            visitEnd((Columbus.Csharp.Asg.Nodes.Expression.ExpressionSyntax)node, false);
        }

        /// <summary>
        /// Abstract visitor, which calls the visitor of the base class (Columbus.Csharp.Asg.Nodes.Expression.ExpressionSyntax) of the Columbus.Csharp.Asg.Nodes.Expression.InterpolatedStringExpressionSyntax node.
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public override void visit(Columbus.Csharp.Asg.Nodes.Expression.InterpolatedStringExpressionSyntax node, bool callVirtualBase) {
            visit((Columbus.Csharp.Asg.Nodes.Expression.ExpressionSyntax)node, false);
        }

        /// <summary>
        /// Abstract end visitor, which calls the end visitor of the base class (Columbus.Csharp.Asg.Nodes.Expression.ExpressionSyntax) of the Columbus.Csharp.Asg.Nodes.Expression.InterpolatedStringExpressionSyntax node.
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public override void visitEnd(Columbus.Csharp.Asg.Nodes.Expression.InterpolatedStringExpressionSyntax node, bool callVirtualBase) {
            visitEnd((Columbus.Csharp.Asg.Nodes.Expression.ExpressionSyntax)node, false);
        }

        /// <summary>
        /// Abstract visitor, which calls the visitor of the base class (Columbus.Csharp.Asg.Nodes.Expression.ExpressionSyntax) of the Columbus.Csharp.Asg.Nodes.Expression.InvocationExpressionSyntax node.
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public override void visit(Columbus.Csharp.Asg.Nodes.Expression.InvocationExpressionSyntax node, bool callVirtualBase) {
            visit((Columbus.Csharp.Asg.Nodes.Expression.ExpressionSyntax)node, false);
        }

        /// <summary>
        /// Abstract end visitor, which calls the end visitor of the base class (Columbus.Csharp.Asg.Nodes.Expression.ExpressionSyntax) of the Columbus.Csharp.Asg.Nodes.Expression.InvocationExpressionSyntax node.
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public override void visitEnd(Columbus.Csharp.Asg.Nodes.Expression.InvocationExpressionSyntax node, bool callVirtualBase) {
            visitEnd((Columbus.Csharp.Asg.Nodes.Expression.ExpressionSyntax)node, false);
        }

        /// <summary>
        /// Abstract visitor, which calls the visitor of the base class (Columbus.Csharp.Asg.Nodes.Expression.ExpressionSyntax) of the Columbus.Csharp.Asg.Nodes.Expression.IsPatternExpressionSyntax node.
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public override void visit(Columbus.Csharp.Asg.Nodes.Expression.IsPatternExpressionSyntax node, bool callVirtualBase) {
            visit((Columbus.Csharp.Asg.Nodes.Expression.ExpressionSyntax)node, false);
        }

        /// <summary>
        /// Abstract end visitor, which calls the end visitor of the base class (Columbus.Csharp.Asg.Nodes.Expression.ExpressionSyntax) of the Columbus.Csharp.Asg.Nodes.Expression.IsPatternExpressionSyntax node.
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public override void visitEnd(Columbus.Csharp.Asg.Nodes.Expression.IsPatternExpressionSyntax node, bool callVirtualBase) {
            visitEnd((Columbus.Csharp.Asg.Nodes.Expression.ExpressionSyntax)node, false);
        }

        /// <summary>
        /// Abstract visitor, which calls the visitor of the base class (Columbus.Csharp.Asg.Nodes.Expression.AnonymousFunctionExpressionSyntax) of the Columbus.Csharp.Asg.Nodes.Expression.LambdaExpressionSyntax node.
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public virtual void visit(Columbus.Csharp.Asg.Nodes.Expression.LambdaExpressionSyntax node, bool callVirtualBase) {
            visit((Columbus.Csharp.Asg.Nodes.Expression.AnonymousFunctionExpressionSyntax)node, false);
        }

        /// <summary>
        /// Abstract end visitor, which calls the end visitor of the base class (Columbus.Csharp.Asg.Nodes.Expression.AnonymousFunctionExpressionSyntax) of the Columbus.Csharp.Asg.Nodes.Expression.LambdaExpressionSyntax node.
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public virtual void visitEnd(Columbus.Csharp.Asg.Nodes.Expression.LambdaExpressionSyntax node, bool callVirtualBase) {
            visitEnd((Columbus.Csharp.Asg.Nodes.Expression.AnonymousFunctionExpressionSyntax)node, false);
        }

        /// <summary>
        /// Abstract visitor, which calls the visitor of the base class (Columbus.Csharp.Asg.Nodes.Expression.ExpressionSyntax) of the Columbus.Csharp.Asg.Nodes.Expression.LiteralExpressionSyntax node.
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public override void visit(Columbus.Csharp.Asg.Nodes.Expression.LiteralExpressionSyntax node, bool callVirtualBase) {
            visit((Columbus.Csharp.Asg.Nodes.Expression.ExpressionSyntax)node, false);
        }

        /// <summary>
        /// Abstract end visitor, which calls the end visitor of the base class (Columbus.Csharp.Asg.Nodes.Expression.ExpressionSyntax) of the Columbus.Csharp.Asg.Nodes.Expression.LiteralExpressionSyntax node.
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public override void visitEnd(Columbus.Csharp.Asg.Nodes.Expression.LiteralExpressionSyntax node, bool callVirtualBase) {
            visitEnd((Columbus.Csharp.Asg.Nodes.Expression.ExpressionSyntax)node, false);
        }

        /// <summary>
        /// Abstract visitor, which calls the visitor of the base class (Columbus.Csharp.Asg.Nodes.Expression.ExpressionSyntax) of the Columbus.Csharp.Asg.Nodes.Expression.MakeRefExpressionSyntax node.
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public override void visit(Columbus.Csharp.Asg.Nodes.Expression.MakeRefExpressionSyntax node, bool callVirtualBase) {
            visit((Columbus.Csharp.Asg.Nodes.Expression.ExpressionSyntax)node, false);
        }

        /// <summary>
        /// Abstract end visitor, which calls the end visitor of the base class (Columbus.Csharp.Asg.Nodes.Expression.ExpressionSyntax) of the Columbus.Csharp.Asg.Nodes.Expression.MakeRefExpressionSyntax node.
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public override void visitEnd(Columbus.Csharp.Asg.Nodes.Expression.MakeRefExpressionSyntax node, bool callVirtualBase) {
            visitEnd((Columbus.Csharp.Asg.Nodes.Expression.ExpressionSyntax)node, false);
        }

        /// <summary>
        /// Abstract visitor, which calls the visitor of the base class (Columbus.Csharp.Asg.Nodes.Expression.ExpressionSyntax) of the Columbus.Csharp.Asg.Nodes.Expression.MemberAccessExpressionSyntax node.
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public override void visit(Columbus.Csharp.Asg.Nodes.Expression.MemberAccessExpressionSyntax node, bool callVirtualBase) {
            visit((Columbus.Csharp.Asg.Nodes.Expression.ExpressionSyntax)node, false);
        }

        /// <summary>
        /// Abstract end visitor, which calls the end visitor of the base class (Columbus.Csharp.Asg.Nodes.Expression.ExpressionSyntax) of the Columbus.Csharp.Asg.Nodes.Expression.MemberAccessExpressionSyntax node.
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public override void visitEnd(Columbus.Csharp.Asg.Nodes.Expression.MemberAccessExpressionSyntax node, bool callVirtualBase) {
            visitEnd((Columbus.Csharp.Asg.Nodes.Expression.ExpressionSyntax)node, false);
        }

        /// <summary>
        /// Abstract visitor, which calls the visitor of the base class (Columbus.Csharp.Asg.Nodes.Expression.ExpressionSyntax) of the Columbus.Csharp.Asg.Nodes.Expression.MemberBindingExpressionSyntax node.
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public override void visit(Columbus.Csharp.Asg.Nodes.Expression.MemberBindingExpressionSyntax node, bool callVirtualBase) {
            visit((Columbus.Csharp.Asg.Nodes.Expression.ExpressionSyntax)node, false);
        }

        /// <summary>
        /// Abstract end visitor, which calls the end visitor of the base class (Columbus.Csharp.Asg.Nodes.Expression.ExpressionSyntax) of the Columbus.Csharp.Asg.Nodes.Expression.MemberBindingExpressionSyntax node.
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public override void visitEnd(Columbus.Csharp.Asg.Nodes.Expression.MemberBindingExpressionSyntax node, bool callVirtualBase) {
            visitEnd((Columbus.Csharp.Asg.Nodes.Expression.ExpressionSyntax)node, false);
        }

        /// <summary>
        /// Abstract visitor, which calls the visitor of the base class (Columbus.Csharp.Asg.Nodes.Expression.TypeSyntax) of the Columbus.Csharp.Asg.Nodes.Expression.NameSyntax node.
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public virtual void visit(Columbus.Csharp.Asg.Nodes.Expression.NameSyntax node, bool callVirtualBase) {
            visit((Columbus.Csharp.Asg.Nodes.Expression.TypeSyntax)node, false);
        }

        /// <summary>
        /// Abstract end visitor, which calls the end visitor of the base class (Columbus.Csharp.Asg.Nodes.Expression.TypeSyntax) of the Columbus.Csharp.Asg.Nodes.Expression.NameSyntax node.
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public virtual void visitEnd(Columbus.Csharp.Asg.Nodes.Expression.NameSyntax node, bool callVirtualBase) {
            visitEnd((Columbus.Csharp.Asg.Nodes.Expression.TypeSyntax)node, false);
        }

        /// <summary>
        /// Abstract visitor, which calls the visitor of the base class (Columbus.Csharp.Asg.Nodes.Expression.TypeSyntax) of the Columbus.Csharp.Asg.Nodes.Expression.NullableTypeSyntax node.
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public override void visit(Columbus.Csharp.Asg.Nodes.Expression.NullableTypeSyntax node, bool callVirtualBase) {
            visit((Columbus.Csharp.Asg.Nodes.Expression.TypeSyntax)node, false);
        }

        /// <summary>
        /// Abstract end visitor, which calls the end visitor of the base class (Columbus.Csharp.Asg.Nodes.Expression.TypeSyntax) of the Columbus.Csharp.Asg.Nodes.Expression.NullableTypeSyntax node.
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public override void visitEnd(Columbus.Csharp.Asg.Nodes.Expression.NullableTypeSyntax node, bool callVirtualBase) {
            visitEnd((Columbus.Csharp.Asg.Nodes.Expression.TypeSyntax)node, false);
        }

        /// <summary>
        /// Abstract visitor, which calls the visitor of the base class (Columbus.Csharp.Asg.Nodes.Expression.ExpressionSyntax) of the Columbus.Csharp.Asg.Nodes.Expression.ObjectCreationExpressionSyntax node.
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public override void visit(Columbus.Csharp.Asg.Nodes.Expression.ObjectCreationExpressionSyntax node, bool callVirtualBase) {
            visit((Columbus.Csharp.Asg.Nodes.Expression.ExpressionSyntax)node, false);
        }

        /// <summary>
        /// Abstract end visitor, which calls the end visitor of the base class (Columbus.Csharp.Asg.Nodes.Expression.ExpressionSyntax) of the Columbus.Csharp.Asg.Nodes.Expression.ObjectCreationExpressionSyntax node.
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public override void visitEnd(Columbus.Csharp.Asg.Nodes.Expression.ObjectCreationExpressionSyntax node, bool callVirtualBase) {
            visitEnd((Columbus.Csharp.Asg.Nodes.Expression.ExpressionSyntax)node, false);
        }

        /// <summary>
        /// Abstract visitor, which calls the visitor of the base class (Columbus.Csharp.Asg.Nodes.Expression.ExpressionSyntax) of the Columbus.Csharp.Asg.Nodes.Expression.OmittedArraySizeExpressionSyntax node.
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public override void visit(Columbus.Csharp.Asg.Nodes.Expression.OmittedArraySizeExpressionSyntax node, bool callVirtualBase) {
            visit((Columbus.Csharp.Asg.Nodes.Expression.ExpressionSyntax)node, false);
        }

        /// <summary>
        /// Abstract end visitor, which calls the end visitor of the base class (Columbus.Csharp.Asg.Nodes.Expression.ExpressionSyntax) of the Columbus.Csharp.Asg.Nodes.Expression.OmittedArraySizeExpressionSyntax node.
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public override void visitEnd(Columbus.Csharp.Asg.Nodes.Expression.OmittedArraySizeExpressionSyntax node, bool callVirtualBase) {
            visitEnd((Columbus.Csharp.Asg.Nodes.Expression.ExpressionSyntax)node, false);
        }

        /// <summary>
        /// Abstract visitor, which calls the visitor of the base class (Columbus.Csharp.Asg.Nodes.Expression.TypeSyntax) of the Columbus.Csharp.Asg.Nodes.Expression.OmittedTypeArgumentSyntax node.
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public override void visit(Columbus.Csharp.Asg.Nodes.Expression.OmittedTypeArgumentSyntax node, bool callVirtualBase) {
            visit((Columbus.Csharp.Asg.Nodes.Expression.TypeSyntax)node, false);
        }

        /// <summary>
        /// Abstract end visitor, which calls the end visitor of the base class (Columbus.Csharp.Asg.Nodes.Expression.TypeSyntax) of the Columbus.Csharp.Asg.Nodes.Expression.OmittedTypeArgumentSyntax node.
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public override void visitEnd(Columbus.Csharp.Asg.Nodes.Expression.OmittedTypeArgumentSyntax node, bool callVirtualBase) {
            visitEnd((Columbus.Csharp.Asg.Nodes.Expression.TypeSyntax)node, false);
        }

        /// <summary>
        /// Abstract visitor, which calls the visitor of the base class (Columbus.Csharp.Asg.Nodes.Expression.ExpressionSyntax) of the Columbus.Csharp.Asg.Nodes.Expression.ParenthesizedExpressionSyntax node.
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public override void visit(Columbus.Csharp.Asg.Nodes.Expression.ParenthesizedExpressionSyntax node, bool callVirtualBase) {
            visit((Columbus.Csharp.Asg.Nodes.Expression.ExpressionSyntax)node, false);
        }

        /// <summary>
        /// Abstract end visitor, which calls the end visitor of the base class (Columbus.Csharp.Asg.Nodes.Expression.ExpressionSyntax) of the Columbus.Csharp.Asg.Nodes.Expression.ParenthesizedExpressionSyntax node.
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public override void visitEnd(Columbus.Csharp.Asg.Nodes.Expression.ParenthesizedExpressionSyntax node, bool callVirtualBase) {
            visitEnd((Columbus.Csharp.Asg.Nodes.Expression.ExpressionSyntax)node, false);
        }

        /// <summary>
        /// Abstract visitor, which calls the visitor of the base class (Columbus.Csharp.Asg.Nodes.Expression.LambdaExpressionSyntax) of the Columbus.Csharp.Asg.Nodes.Expression.ParenthesizedLambdaExpressionSyntax node.
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public override void visit(Columbus.Csharp.Asg.Nodes.Expression.ParenthesizedLambdaExpressionSyntax node, bool callVirtualBase) {
            visit((Columbus.Csharp.Asg.Nodes.Expression.LambdaExpressionSyntax)node, false);
        }

        /// <summary>
        /// Abstract end visitor, which calls the end visitor of the base class (Columbus.Csharp.Asg.Nodes.Expression.LambdaExpressionSyntax) of the Columbus.Csharp.Asg.Nodes.Expression.ParenthesizedLambdaExpressionSyntax node.
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public override void visitEnd(Columbus.Csharp.Asg.Nodes.Expression.ParenthesizedLambdaExpressionSyntax node, bool callVirtualBase) {
            visitEnd((Columbus.Csharp.Asg.Nodes.Expression.LambdaExpressionSyntax)node, false);
        }

        /// <summary>
        /// Abstract visitor, which calls the visitor of the base class (Columbus.Csharp.Asg.Nodes.Expression.TypeSyntax) of the Columbus.Csharp.Asg.Nodes.Expression.PointerTypeSyntax node.
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public override void visit(Columbus.Csharp.Asg.Nodes.Expression.PointerTypeSyntax node, bool callVirtualBase) {
            visit((Columbus.Csharp.Asg.Nodes.Expression.TypeSyntax)node, false);
        }

        /// <summary>
        /// Abstract end visitor, which calls the end visitor of the base class (Columbus.Csharp.Asg.Nodes.Expression.TypeSyntax) of the Columbus.Csharp.Asg.Nodes.Expression.PointerTypeSyntax node.
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public override void visitEnd(Columbus.Csharp.Asg.Nodes.Expression.PointerTypeSyntax node, bool callVirtualBase) {
            visitEnd((Columbus.Csharp.Asg.Nodes.Expression.TypeSyntax)node, false);
        }

        /// <summary>
        /// Abstract visitor, which calls the visitor of the base class (Columbus.Csharp.Asg.Nodes.Expression.ExpressionSyntax) of the Columbus.Csharp.Asg.Nodes.Expression.PostfixUnaryExpressionSyntax node.
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public override void visit(Columbus.Csharp.Asg.Nodes.Expression.PostfixUnaryExpressionSyntax node, bool callVirtualBase) {
            visit((Columbus.Csharp.Asg.Nodes.Expression.ExpressionSyntax)node, false);
        }

        /// <summary>
        /// Abstract end visitor, which calls the end visitor of the base class (Columbus.Csharp.Asg.Nodes.Expression.ExpressionSyntax) of the Columbus.Csharp.Asg.Nodes.Expression.PostfixUnaryExpressionSyntax node.
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public override void visitEnd(Columbus.Csharp.Asg.Nodes.Expression.PostfixUnaryExpressionSyntax node, bool callVirtualBase) {
            visitEnd((Columbus.Csharp.Asg.Nodes.Expression.ExpressionSyntax)node, false);
        }

        /// <summary>
        /// Abstract visitor, which calls the visitor of the base class (Columbus.Csharp.Asg.Nodes.Expression.TypeSyntax) of the Columbus.Csharp.Asg.Nodes.Expression.PredefinedTypeSyntax node.
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public override void visit(Columbus.Csharp.Asg.Nodes.Expression.PredefinedTypeSyntax node, bool callVirtualBase) {
            visit((Columbus.Csharp.Asg.Nodes.Expression.TypeSyntax)node, false);
        }

        /// <summary>
        /// Abstract end visitor, which calls the end visitor of the base class (Columbus.Csharp.Asg.Nodes.Expression.TypeSyntax) of the Columbus.Csharp.Asg.Nodes.Expression.PredefinedTypeSyntax node.
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public override void visitEnd(Columbus.Csharp.Asg.Nodes.Expression.PredefinedTypeSyntax node, bool callVirtualBase) {
            visitEnd((Columbus.Csharp.Asg.Nodes.Expression.TypeSyntax)node, false);
        }

        /// <summary>
        /// Abstract visitor, which calls the visitor of the base class (Columbus.Csharp.Asg.Nodes.Expression.ExpressionSyntax) of the Columbus.Csharp.Asg.Nodes.Expression.PrefixUnaryExpressionSyntax node.
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public override void visit(Columbus.Csharp.Asg.Nodes.Expression.PrefixUnaryExpressionSyntax node, bool callVirtualBase) {
            visit((Columbus.Csharp.Asg.Nodes.Expression.ExpressionSyntax)node, false);
        }

        /// <summary>
        /// Abstract end visitor, which calls the end visitor of the base class (Columbus.Csharp.Asg.Nodes.Expression.ExpressionSyntax) of the Columbus.Csharp.Asg.Nodes.Expression.PrefixUnaryExpressionSyntax node.
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public override void visitEnd(Columbus.Csharp.Asg.Nodes.Expression.PrefixUnaryExpressionSyntax node, bool callVirtualBase) {
            visitEnd((Columbus.Csharp.Asg.Nodes.Expression.ExpressionSyntax)node, false);
        }

        /// <summary>
        /// Abstract visitor, which calls the visitor of the base class (Columbus.Csharp.Asg.Nodes.Expression.NameSyntax) of the Columbus.Csharp.Asg.Nodes.Expression.QualifiedNameSyntax node.
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public override void visit(Columbus.Csharp.Asg.Nodes.Expression.QualifiedNameSyntax node, bool callVirtualBase) {
            visit((Columbus.Csharp.Asg.Nodes.Expression.NameSyntax)node, false);
        }

        /// <summary>
        /// Abstract end visitor, which calls the end visitor of the base class (Columbus.Csharp.Asg.Nodes.Expression.NameSyntax) of the Columbus.Csharp.Asg.Nodes.Expression.QualifiedNameSyntax node.
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public override void visitEnd(Columbus.Csharp.Asg.Nodes.Expression.QualifiedNameSyntax node, bool callVirtualBase) {
            visitEnd((Columbus.Csharp.Asg.Nodes.Expression.NameSyntax)node, false);
        }

        /// <summary>
        /// Abstract visitor, which calls the visitor of the base class (Columbus.Csharp.Asg.Nodes.Expression.ExpressionSyntax) of the Columbus.Csharp.Asg.Nodes.Expression.QueryExpressionSyntax node.
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public override void visit(Columbus.Csharp.Asg.Nodes.Expression.QueryExpressionSyntax node, bool callVirtualBase) {
            visit((Columbus.Csharp.Asg.Nodes.Expression.ExpressionSyntax)node, false);
        }

        /// <summary>
        /// Abstract end visitor, which calls the end visitor of the base class (Columbus.Csharp.Asg.Nodes.Expression.ExpressionSyntax) of the Columbus.Csharp.Asg.Nodes.Expression.QueryExpressionSyntax node.
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public override void visitEnd(Columbus.Csharp.Asg.Nodes.Expression.QueryExpressionSyntax node, bool callVirtualBase) {
            visitEnd((Columbus.Csharp.Asg.Nodes.Expression.ExpressionSyntax)node, false);
        }

        /// <summary>
        /// Abstract visitor, which calls the visitor of the base class (Columbus.Csharp.Asg.Nodes.Expression.ExpressionSyntax) of the Columbus.Csharp.Asg.Nodes.Expression.RangeExpressionSyntax node.
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public override void visit(Columbus.Csharp.Asg.Nodes.Expression.RangeExpressionSyntax node, bool callVirtualBase) {
            visit((Columbus.Csharp.Asg.Nodes.Expression.ExpressionSyntax)node, false);
        }

        /// <summary>
        /// Abstract end visitor, which calls the end visitor of the base class (Columbus.Csharp.Asg.Nodes.Expression.ExpressionSyntax) of the Columbus.Csharp.Asg.Nodes.Expression.RangeExpressionSyntax node.
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public override void visitEnd(Columbus.Csharp.Asg.Nodes.Expression.RangeExpressionSyntax node, bool callVirtualBase) {
            visitEnd((Columbus.Csharp.Asg.Nodes.Expression.ExpressionSyntax)node, false);
        }

        /// <summary>
        /// Abstract visitor, which calls the visitor of the base class (Columbus.Csharp.Asg.Nodes.Expression.ExpressionSyntax) of the Columbus.Csharp.Asg.Nodes.Expression.RefExpressionSyntax node.
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public override void visit(Columbus.Csharp.Asg.Nodes.Expression.RefExpressionSyntax node, bool callVirtualBase) {
            visit((Columbus.Csharp.Asg.Nodes.Expression.ExpressionSyntax)node, false);
        }

        /// <summary>
        /// Abstract end visitor, which calls the end visitor of the base class (Columbus.Csharp.Asg.Nodes.Expression.ExpressionSyntax) of the Columbus.Csharp.Asg.Nodes.Expression.RefExpressionSyntax node.
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public override void visitEnd(Columbus.Csharp.Asg.Nodes.Expression.RefExpressionSyntax node, bool callVirtualBase) {
            visitEnd((Columbus.Csharp.Asg.Nodes.Expression.ExpressionSyntax)node, false);
        }

        /// <summary>
        /// Abstract visitor, which calls the visitor of the base class (Columbus.Csharp.Asg.Nodes.Expression.ExpressionSyntax) of the Columbus.Csharp.Asg.Nodes.Expression.RefTypeExpressionSyntax node.
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public override void visit(Columbus.Csharp.Asg.Nodes.Expression.RefTypeExpressionSyntax node, bool callVirtualBase) {
            visit((Columbus.Csharp.Asg.Nodes.Expression.ExpressionSyntax)node, false);
        }

        /// <summary>
        /// Abstract end visitor, which calls the end visitor of the base class (Columbus.Csharp.Asg.Nodes.Expression.ExpressionSyntax) of the Columbus.Csharp.Asg.Nodes.Expression.RefTypeExpressionSyntax node.
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public override void visitEnd(Columbus.Csharp.Asg.Nodes.Expression.RefTypeExpressionSyntax node, bool callVirtualBase) {
            visitEnd((Columbus.Csharp.Asg.Nodes.Expression.ExpressionSyntax)node, false);
        }

        /// <summary>
        /// Abstract visitor, which calls the visitor of the base class (Columbus.Csharp.Asg.Nodes.Expression.TypeSyntax) of the Columbus.Csharp.Asg.Nodes.Expression.RefTypeSyntax node.
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public override void visit(Columbus.Csharp.Asg.Nodes.Expression.RefTypeSyntax node, bool callVirtualBase) {
            visit((Columbus.Csharp.Asg.Nodes.Expression.TypeSyntax)node, false);
        }

        /// <summary>
        /// Abstract end visitor, which calls the end visitor of the base class (Columbus.Csharp.Asg.Nodes.Expression.TypeSyntax) of the Columbus.Csharp.Asg.Nodes.Expression.RefTypeSyntax node.
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public override void visitEnd(Columbus.Csharp.Asg.Nodes.Expression.RefTypeSyntax node, bool callVirtualBase) {
            visitEnd((Columbus.Csharp.Asg.Nodes.Expression.TypeSyntax)node, false);
        }

        /// <summary>
        /// Abstract visitor, which calls the visitor of the base class (Columbus.Csharp.Asg.Nodes.Expression.ExpressionSyntax) of the Columbus.Csharp.Asg.Nodes.Expression.RefValueExpressionSyntax node.
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public override void visit(Columbus.Csharp.Asg.Nodes.Expression.RefValueExpressionSyntax node, bool callVirtualBase) {
            visit((Columbus.Csharp.Asg.Nodes.Expression.ExpressionSyntax)node, false);
        }

        /// <summary>
        /// Abstract end visitor, which calls the end visitor of the base class (Columbus.Csharp.Asg.Nodes.Expression.ExpressionSyntax) of the Columbus.Csharp.Asg.Nodes.Expression.RefValueExpressionSyntax node.
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public override void visitEnd(Columbus.Csharp.Asg.Nodes.Expression.RefValueExpressionSyntax node, bool callVirtualBase) {
            visitEnd((Columbus.Csharp.Asg.Nodes.Expression.ExpressionSyntax)node, false);
        }

        /// <summary>
        /// Abstract visitor, which calls the visitor of the base class (Columbus.Csharp.Asg.Nodes.Expression.LambdaExpressionSyntax) of the Columbus.Csharp.Asg.Nodes.Expression.SimpleLambdaExpressionSyntax node.
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public override void visit(Columbus.Csharp.Asg.Nodes.Expression.SimpleLambdaExpressionSyntax node, bool callVirtualBase) {
            visit((Columbus.Csharp.Asg.Nodes.Expression.LambdaExpressionSyntax)node, false);
        }

        /// <summary>
        /// Abstract end visitor, which calls the end visitor of the base class (Columbus.Csharp.Asg.Nodes.Expression.LambdaExpressionSyntax) of the Columbus.Csharp.Asg.Nodes.Expression.SimpleLambdaExpressionSyntax node.
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public override void visitEnd(Columbus.Csharp.Asg.Nodes.Expression.SimpleLambdaExpressionSyntax node, bool callVirtualBase) {
            visitEnd((Columbus.Csharp.Asg.Nodes.Expression.LambdaExpressionSyntax)node, false);
        }

        /// <summary>
        /// Abstract visitor, which calls the visitor of the base class (Columbus.Csharp.Asg.Nodes.Expression.NameSyntax) of the Columbus.Csharp.Asg.Nodes.Expression.SimpleNameSyntax node.
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public virtual void visit(Columbus.Csharp.Asg.Nodes.Expression.SimpleNameSyntax node, bool callVirtualBase) {
            visit((Columbus.Csharp.Asg.Nodes.Expression.NameSyntax)node, false);
        }

        /// <summary>
        /// Abstract end visitor, which calls the end visitor of the base class (Columbus.Csharp.Asg.Nodes.Expression.NameSyntax) of the Columbus.Csharp.Asg.Nodes.Expression.SimpleNameSyntax node.
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public virtual void visitEnd(Columbus.Csharp.Asg.Nodes.Expression.SimpleNameSyntax node, bool callVirtualBase) {
            visitEnd((Columbus.Csharp.Asg.Nodes.Expression.NameSyntax)node, false);
        }

        /// <summary>
        /// Abstract visitor, which calls the visitor of the base class (Columbus.Csharp.Asg.Nodes.Expression.ExpressionSyntax) of the Columbus.Csharp.Asg.Nodes.Expression.SizeOfExpressionSyntax node.
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public override void visit(Columbus.Csharp.Asg.Nodes.Expression.SizeOfExpressionSyntax node, bool callVirtualBase) {
            visit((Columbus.Csharp.Asg.Nodes.Expression.ExpressionSyntax)node, false);
        }

        /// <summary>
        /// Abstract end visitor, which calls the end visitor of the base class (Columbus.Csharp.Asg.Nodes.Expression.ExpressionSyntax) of the Columbus.Csharp.Asg.Nodes.Expression.SizeOfExpressionSyntax node.
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public override void visitEnd(Columbus.Csharp.Asg.Nodes.Expression.SizeOfExpressionSyntax node, bool callVirtualBase) {
            visitEnd((Columbus.Csharp.Asg.Nodes.Expression.ExpressionSyntax)node, false);
        }

        /// <summary>
        /// Abstract visitor, which calls the visitor of the base class (Columbus.Csharp.Asg.Nodes.Expression.ExpressionSyntax) of the Columbus.Csharp.Asg.Nodes.Expression.StackAllocArrayCreationExpressionSyntax node.
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public override void visit(Columbus.Csharp.Asg.Nodes.Expression.StackAllocArrayCreationExpressionSyntax node, bool callVirtualBase) {
            visit((Columbus.Csharp.Asg.Nodes.Expression.ExpressionSyntax)node, false);
        }

        /// <summary>
        /// Abstract end visitor, which calls the end visitor of the base class (Columbus.Csharp.Asg.Nodes.Expression.ExpressionSyntax) of the Columbus.Csharp.Asg.Nodes.Expression.StackAllocArrayCreationExpressionSyntax node.
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public override void visitEnd(Columbus.Csharp.Asg.Nodes.Expression.StackAllocArrayCreationExpressionSyntax node, bool callVirtualBase) {
            visitEnd((Columbus.Csharp.Asg.Nodes.Expression.ExpressionSyntax)node, false);
        }

        /// <summary>
        /// Abstract visitor, which calls the visitor of the base class (Columbus.Csharp.Asg.Nodes.Expression.ExpressionSyntax) of the Columbus.Csharp.Asg.Nodes.Expression.SwitchExpressionSyntax node.
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public override void visit(Columbus.Csharp.Asg.Nodes.Expression.SwitchExpressionSyntax node, bool callVirtualBase) {
            visit((Columbus.Csharp.Asg.Nodes.Expression.ExpressionSyntax)node, false);
        }

        /// <summary>
        /// Abstract end visitor, which calls the end visitor of the base class (Columbus.Csharp.Asg.Nodes.Expression.ExpressionSyntax) of the Columbus.Csharp.Asg.Nodes.Expression.SwitchExpressionSyntax node.
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public override void visitEnd(Columbus.Csharp.Asg.Nodes.Expression.SwitchExpressionSyntax node, bool callVirtualBase) {
            visitEnd((Columbus.Csharp.Asg.Nodes.Expression.ExpressionSyntax)node, false);
        }

        /// <summary>
        /// Abstract visitor, which calls the visitor of the base class (Columbus.Csharp.Asg.Nodes.Expression.InstanceExpressionSyntax) of the Columbus.Csharp.Asg.Nodes.Expression.ThisExpressionSyntax node.
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public override void visit(Columbus.Csharp.Asg.Nodes.Expression.ThisExpressionSyntax node, bool callVirtualBase) {
            visit((Columbus.Csharp.Asg.Nodes.Expression.InstanceExpressionSyntax)node, false);
        }

        /// <summary>
        /// Abstract end visitor, which calls the end visitor of the base class (Columbus.Csharp.Asg.Nodes.Expression.InstanceExpressionSyntax) of the Columbus.Csharp.Asg.Nodes.Expression.ThisExpressionSyntax node.
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public override void visitEnd(Columbus.Csharp.Asg.Nodes.Expression.ThisExpressionSyntax node, bool callVirtualBase) {
            visitEnd((Columbus.Csharp.Asg.Nodes.Expression.InstanceExpressionSyntax)node, false);
        }

        /// <summary>
        /// Abstract visitor, which calls the visitor of the base class (Columbus.Csharp.Asg.Nodes.Expression.ExpressionSyntax) of the Columbus.Csharp.Asg.Nodes.Expression.ThrowExpressionSyntax node.
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public override void visit(Columbus.Csharp.Asg.Nodes.Expression.ThrowExpressionSyntax node, bool callVirtualBase) {
            visit((Columbus.Csharp.Asg.Nodes.Expression.ExpressionSyntax)node, false);
        }

        /// <summary>
        /// Abstract end visitor, which calls the end visitor of the base class (Columbus.Csharp.Asg.Nodes.Expression.ExpressionSyntax) of the Columbus.Csharp.Asg.Nodes.Expression.ThrowExpressionSyntax node.
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public override void visitEnd(Columbus.Csharp.Asg.Nodes.Expression.ThrowExpressionSyntax node, bool callVirtualBase) {
            visitEnd((Columbus.Csharp.Asg.Nodes.Expression.ExpressionSyntax)node, false);
        }

        /// <summary>
        /// Abstract visitor, which calls the visitor of the base class (Columbus.Csharp.Asg.Nodes.Expression.ExpressionSyntax) of the Columbus.Csharp.Asg.Nodes.Expression.TupleExpressionSyntax node.
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public override void visit(Columbus.Csharp.Asg.Nodes.Expression.TupleExpressionSyntax node, bool callVirtualBase) {
            visit((Columbus.Csharp.Asg.Nodes.Expression.ExpressionSyntax)node, false);
        }

        /// <summary>
        /// Abstract end visitor, which calls the end visitor of the base class (Columbus.Csharp.Asg.Nodes.Expression.ExpressionSyntax) of the Columbus.Csharp.Asg.Nodes.Expression.TupleExpressionSyntax node.
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public override void visitEnd(Columbus.Csharp.Asg.Nodes.Expression.TupleExpressionSyntax node, bool callVirtualBase) {
            visitEnd((Columbus.Csharp.Asg.Nodes.Expression.ExpressionSyntax)node, false);
        }

        /// <summary>
        /// Abstract visitor, which calls the visitor of the base class (Columbus.Csharp.Asg.Nodes.Expression.TypeSyntax) of the Columbus.Csharp.Asg.Nodes.Expression.TupleTypeSyntax node.
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public override void visit(Columbus.Csharp.Asg.Nodes.Expression.TupleTypeSyntax node, bool callVirtualBase) {
            visit((Columbus.Csharp.Asg.Nodes.Expression.TypeSyntax)node, false);
        }

        /// <summary>
        /// Abstract end visitor, which calls the end visitor of the base class (Columbus.Csharp.Asg.Nodes.Expression.TypeSyntax) of the Columbus.Csharp.Asg.Nodes.Expression.TupleTypeSyntax node.
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public override void visitEnd(Columbus.Csharp.Asg.Nodes.Expression.TupleTypeSyntax node, bool callVirtualBase) {
            visitEnd((Columbus.Csharp.Asg.Nodes.Expression.TypeSyntax)node, false);
        }

        /// <summary>
        /// Abstract visitor, which calls the visitor of the base class (Columbus.Csharp.Asg.Nodes.Expression.ExpressionSyntax) of the Columbus.Csharp.Asg.Nodes.Expression.TypeOfExpressionSyntax node.
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public override void visit(Columbus.Csharp.Asg.Nodes.Expression.TypeOfExpressionSyntax node, bool callVirtualBase) {
            visit((Columbus.Csharp.Asg.Nodes.Expression.ExpressionSyntax)node, false);
        }

        /// <summary>
        /// Abstract end visitor, which calls the end visitor of the base class (Columbus.Csharp.Asg.Nodes.Expression.ExpressionSyntax) of the Columbus.Csharp.Asg.Nodes.Expression.TypeOfExpressionSyntax node.
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public override void visitEnd(Columbus.Csharp.Asg.Nodes.Expression.TypeOfExpressionSyntax node, bool callVirtualBase) {
            visitEnd((Columbus.Csharp.Asg.Nodes.Expression.ExpressionSyntax)node, false);
        }

        /// <summary>
        /// Abstract visitor, which calls the visitor of the base class (Columbus.Csharp.Asg.Nodes.Expression.ExpressionSyntax) of the Columbus.Csharp.Asg.Nodes.Expression.TypeSyntax node.
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public virtual void visit(Columbus.Csharp.Asg.Nodes.Expression.TypeSyntax node, bool callVirtualBase) {
            visit((Columbus.Csharp.Asg.Nodes.Expression.ExpressionSyntax)node, false);
        }

        /// <summary>
        /// Abstract end visitor, which calls the end visitor of the base class (Columbus.Csharp.Asg.Nodes.Expression.ExpressionSyntax) of the Columbus.Csharp.Asg.Nodes.Expression.TypeSyntax node.
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public virtual void visitEnd(Columbus.Csharp.Asg.Nodes.Expression.TypeSyntax node, bool callVirtualBase) {
            visitEnd((Columbus.Csharp.Asg.Nodes.Expression.ExpressionSyntax)node, false);
        }

        /// <summary>
        /// Abstract visitor, which calls the visitor of the base class (Columbus.Csharp.Asg.Nodes.Statement.StatementSyntax) of the Columbus.Csharp.Asg.Nodes.Statement.BlockSyntax node.
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public override void visit(Columbus.Csharp.Asg.Nodes.Statement.BlockSyntax node, bool callVirtualBase) {
            visit((Columbus.Csharp.Asg.Nodes.Statement.StatementSyntax)node, false);
        }

        /// <summary>
        /// Abstract end visitor, which calls the end visitor of the base class (Columbus.Csharp.Asg.Nodes.Statement.StatementSyntax) of the Columbus.Csharp.Asg.Nodes.Statement.BlockSyntax node.
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public override void visitEnd(Columbus.Csharp.Asg.Nodes.Statement.BlockSyntax node, bool callVirtualBase) {
            visitEnd((Columbus.Csharp.Asg.Nodes.Statement.StatementSyntax)node, false);
        }

        /// <summary>
        /// Abstract visitor, which calls the visitor of the base class (Columbus.Csharp.Asg.Nodes.Statement.StatementSyntax) of the Columbus.Csharp.Asg.Nodes.Statement.BreakStatementSyntax node.
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public override void visit(Columbus.Csharp.Asg.Nodes.Statement.BreakStatementSyntax node, bool callVirtualBase) {
            visit((Columbus.Csharp.Asg.Nodes.Statement.StatementSyntax)node, false);
        }

        /// <summary>
        /// Abstract end visitor, which calls the end visitor of the base class (Columbus.Csharp.Asg.Nodes.Statement.StatementSyntax) of the Columbus.Csharp.Asg.Nodes.Statement.BreakStatementSyntax node.
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public override void visitEnd(Columbus.Csharp.Asg.Nodes.Statement.BreakStatementSyntax node, bool callVirtualBase) {
            visitEnd((Columbus.Csharp.Asg.Nodes.Statement.StatementSyntax)node, false);
        }

        /// <summary>
        /// Abstract visitor, which calls the visitor of the base class (Columbus.Csharp.Asg.Nodes.Statement.StatementSyntax) of the Columbus.Csharp.Asg.Nodes.Statement.CheckedStatementSyntax node.
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public override void visit(Columbus.Csharp.Asg.Nodes.Statement.CheckedStatementSyntax node, bool callVirtualBase) {
            visit((Columbus.Csharp.Asg.Nodes.Statement.StatementSyntax)node, false);
        }

        /// <summary>
        /// Abstract end visitor, which calls the end visitor of the base class (Columbus.Csharp.Asg.Nodes.Statement.StatementSyntax) of the Columbus.Csharp.Asg.Nodes.Statement.CheckedStatementSyntax node.
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public override void visitEnd(Columbus.Csharp.Asg.Nodes.Statement.CheckedStatementSyntax node, bool callVirtualBase) {
            visitEnd((Columbus.Csharp.Asg.Nodes.Statement.StatementSyntax)node, false);
        }

        /// <summary>
        /// Abstract visitor, which calls the visitor of the base class (Columbus.Csharp.Asg.Nodes.Statement.StatementSyntax) of the Columbus.Csharp.Asg.Nodes.Statement.CommonForEachStatementSyntax node.
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public virtual void visit(Columbus.Csharp.Asg.Nodes.Statement.CommonForEachStatementSyntax node, bool callVirtualBase) {
            visit((Columbus.Csharp.Asg.Nodes.Statement.StatementSyntax)node, false);
        }

        /// <summary>
        /// Abstract end visitor, which calls the end visitor of the base class (Columbus.Csharp.Asg.Nodes.Statement.StatementSyntax) of the Columbus.Csharp.Asg.Nodes.Statement.CommonForEachStatementSyntax node.
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public virtual void visitEnd(Columbus.Csharp.Asg.Nodes.Statement.CommonForEachStatementSyntax node, bool callVirtualBase) {
            visitEnd((Columbus.Csharp.Asg.Nodes.Statement.StatementSyntax)node, false);
        }

        /// <summary>
        /// Abstract visitor, which calls the visitor of the base class (Columbus.Csharp.Asg.Nodes.Statement.StatementSyntax) of the Columbus.Csharp.Asg.Nodes.Statement.ContinueStatementSyntax node.
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public override void visit(Columbus.Csharp.Asg.Nodes.Statement.ContinueStatementSyntax node, bool callVirtualBase) {
            visit((Columbus.Csharp.Asg.Nodes.Statement.StatementSyntax)node, false);
        }

        /// <summary>
        /// Abstract end visitor, which calls the end visitor of the base class (Columbus.Csharp.Asg.Nodes.Statement.StatementSyntax) of the Columbus.Csharp.Asg.Nodes.Statement.ContinueStatementSyntax node.
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public override void visitEnd(Columbus.Csharp.Asg.Nodes.Statement.ContinueStatementSyntax node, bool callVirtualBase) {
            visitEnd((Columbus.Csharp.Asg.Nodes.Statement.StatementSyntax)node, false);
        }

        /// <summary>
        /// Abstract visitor, which calls the visitor of the base class (Columbus.Csharp.Asg.Nodes.Statement.StatementSyntax) of the Columbus.Csharp.Asg.Nodes.Statement.DoStatementSyntax node.
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public override void visit(Columbus.Csharp.Asg.Nodes.Statement.DoStatementSyntax node, bool callVirtualBase) {
            visit((Columbus.Csharp.Asg.Nodes.Statement.StatementSyntax)node, false);
        }

        /// <summary>
        /// Abstract end visitor, which calls the end visitor of the base class (Columbus.Csharp.Asg.Nodes.Statement.StatementSyntax) of the Columbus.Csharp.Asg.Nodes.Statement.DoStatementSyntax node.
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public override void visitEnd(Columbus.Csharp.Asg.Nodes.Statement.DoStatementSyntax node, bool callVirtualBase) {
            visitEnd((Columbus.Csharp.Asg.Nodes.Statement.StatementSyntax)node, false);
        }

        /// <summary>
        /// Abstract visitor, which calls the visitor of the base class (Columbus.Csharp.Asg.Nodes.Statement.StatementSyntax) of the Columbus.Csharp.Asg.Nodes.Statement.EmptyStatementSyntax node.
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public override void visit(Columbus.Csharp.Asg.Nodes.Statement.EmptyStatementSyntax node, bool callVirtualBase) {
            visit((Columbus.Csharp.Asg.Nodes.Statement.StatementSyntax)node, false);
        }

        /// <summary>
        /// Abstract end visitor, which calls the end visitor of the base class (Columbus.Csharp.Asg.Nodes.Statement.StatementSyntax) of the Columbus.Csharp.Asg.Nodes.Statement.EmptyStatementSyntax node.
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public override void visitEnd(Columbus.Csharp.Asg.Nodes.Statement.EmptyStatementSyntax node, bool callVirtualBase) {
            visitEnd((Columbus.Csharp.Asg.Nodes.Statement.StatementSyntax)node, false);
        }

        /// <summary>
        /// Abstract visitor, which calls the visitor of the base class (Columbus.Csharp.Asg.Nodes.Statement.StatementSyntax) of the Columbus.Csharp.Asg.Nodes.Statement.ExpressionStatementSyntax node.
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public override void visit(Columbus.Csharp.Asg.Nodes.Statement.ExpressionStatementSyntax node, bool callVirtualBase) {
            visit((Columbus.Csharp.Asg.Nodes.Statement.StatementSyntax)node, false);
        }

        /// <summary>
        /// Abstract end visitor, which calls the end visitor of the base class (Columbus.Csharp.Asg.Nodes.Statement.StatementSyntax) of the Columbus.Csharp.Asg.Nodes.Statement.ExpressionStatementSyntax node.
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public override void visitEnd(Columbus.Csharp.Asg.Nodes.Statement.ExpressionStatementSyntax node, bool callVirtualBase) {
            visitEnd((Columbus.Csharp.Asg.Nodes.Statement.StatementSyntax)node, false);
        }

        /// <summary>
        /// Abstract visitor, which calls the visitor of the base class (Columbus.Csharp.Asg.Nodes.Statement.StatementSyntax) of the Columbus.Csharp.Asg.Nodes.Statement.FixedStatementSyntax node.
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public override void visit(Columbus.Csharp.Asg.Nodes.Statement.FixedStatementSyntax node, bool callVirtualBase) {
            visit((Columbus.Csharp.Asg.Nodes.Statement.StatementSyntax)node, false);
        }

        /// <summary>
        /// Abstract end visitor, which calls the end visitor of the base class (Columbus.Csharp.Asg.Nodes.Statement.StatementSyntax) of the Columbus.Csharp.Asg.Nodes.Statement.FixedStatementSyntax node.
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public override void visitEnd(Columbus.Csharp.Asg.Nodes.Statement.FixedStatementSyntax node, bool callVirtualBase) {
            visitEnd((Columbus.Csharp.Asg.Nodes.Statement.StatementSyntax)node, false);
        }

        /// <summary>
        /// Abstract visitor, which calls the visitor of the base class (Columbus.Csharp.Asg.Nodes.Statement.CommonForEachStatementSyntax) of the Columbus.Csharp.Asg.Nodes.Statement.ForEachStatementSyntax node.
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public override void visit(Columbus.Csharp.Asg.Nodes.Statement.ForEachStatementSyntax node, bool callVirtualBase) {
            visit((Columbus.Csharp.Asg.Nodes.Statement.CommonForEachStatementSyntax)node, false);
        }

        /// <summary>
        /// Abstract end visitor, which calls the end visitor of the base class (Columbus.Csharp.Asg.Nodes.Statement.CommonForEachStatementSyntax) of the Columbus.Csharp.Asg.Nodes.Statement.ForEachStatementSyntax node.
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public override void visitEnd(Columbus.Csharp.Asg.Nodes.Statement.ForEachStatementSyntax node, bool callVirtualBase) {
            visitEnd((Columbus.Csharp.Asg.Nodes.Statement.CommonForEachStatementSyntax)node, false);
        }

        /// <summary>
        /// Abstract visitor, which calls the visitor of the base class (Columbus.Csharp.Asg.Nodes.Statement.CommonForEachStatementSyntax) of the Columbus.Csharp.Asg.Nodes.Statement.ForEachVariableStatementSyntax node.
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public override void visit(Columbus.Csharp.Asg.Nodes.Statement.ForEachVariableStatementSyntax node, bool callVirtualBase) {
            visit((Columbus.Csharp.Asg.Nodes.Statement.CommonForEachStatementSyntax)node, false);
        }

        /// <summary>
        /// Abstract end visitor, which calls the end visitor of the base class (Columbus.Csharp.Asg.Nodes.Statement.CommonForEachStatementSyntax) of the Columbus.Csharp.Asg.Nodes.Statement.ForEachVariableStatementSyntax node.
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public override void visitEnd(Columbus.Csharp.Asg.Nodes.Statement.ForEachVariableStatementSyntax node, bool callVirtualBase) {
            visitEnd((Columbus.Csharp.Asg.Nodes.Statement.CommonForEachStatementSyntax)node, false);
        }

        /// <summary>
        /// Abstract visitor, which calls the visitor of the base class (Columbus.Csharp.Asg.Nodes.Statement.StatementSyntax) of the Columbus.Csharp.Asg.Nodes.Statement.ForStatementSyntax node.
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public override void visit(Columbus.Csharp.Asg.Nodes.Statement.ForStatementSyntax node, bool callVirtualBase) {
            visit((Columbus.Csharp.Asg.Nodes.Statement.StatementSyntax)node, false);
        }

        /// <summary>
        /// Abstract end visitor, which calls the end visitor of the base class (Columbus.Csharp.Asg.Nodes.Statement.StatementSyntax) of the Columbus.Csharp.Asg.Nodes.Statement.ForStatementSyntax node.
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public override void visitEnd(Columbus.Csharp.Asg.Nodes.Statement.ForStatementSyntax node, bool callVirtualBase) {
            visitEnd((Columbus.Csharp.Asg.Nodes.Statement.StatementSyntax)node, false);
        }

        /// <summary>
        /// Abstract visitor, which calls the visitor of the base class (Columbus.Csharp.Asg.Nodes.Statement.StatementSyntax) of the Columbus.Csharp.Asg.Nodes.Statement.GotoStatementSyntax node.
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public override void visit(Columbus.Csharp.Asg.Nodes.Statement.GotoStatementSyntax node, bool callVirtualBase) {
            visit((Columbus.Csharp.Asg.Nodes.Statement.StatementSyntax)node, false);
        }

        /// <summary>
        /// Abstract end visitor, which calls the end visitor of the base class (Columbus.Csharp.Asg.Nodes.Statement.StatementSyntax) of the Columbus.Csharp.Asg.Nodes.Statement.GotoStatementSyntax node.
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public override void visitEnd(Columbus.Csharp.Asg.Nodes.Statement.GotoStatementSyntax node, bool callVirtualBase) {
            visitEnd((Columbus.Csharp.Asg.Nodes.Statement.StatementSyntax)node, false);
        }

        /// <summary>
        /// Abstract visitor, which calls the visitor of the base class (Columbus.Csharp.Asg.Nodes.Statement.StatementSyntax) of the Columbus.Csharp.Asg.Nodes.Statement.IfStatementSyntax node.
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public override void visit(Columbus.Csharp.Asg.Nodes.Statement.IfStatementSyntax node, bool callVirtualBase) {
            visit((Columbus.Csharp.Asg.Nodes.Statement.StatementSyntax)node, false);
        }

        /// <summary>
        /// Abstract end visitor, which calls the end visitor of the base class (Columbus.Csharp.Asg.Nodes.Statement.StatementSyntax) of the Columbus.Csharp.Asg.Nodes.Statement.IfStatementSyntax node.
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public override void visitEnd(Columbus.Csharp.Asg.Nodes.Statement.IfStatementSyntax node, bool callVirtualBase) {
            visitEnd((Columbus.Csharp.Asg.Nodes.Statement.StatementSyntax)node, false);
        }

        /// <summary>
        /// Abstract visitor, which calls the visitor of the base class (Columbus.Csharp.Asg.Nodes.Statement.StatementSyntax) of the Columbus.Csharp.Asg.Nodes.Statement.LabeledStatementSyntax node.
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public override void visit(Columbus.Csharp.Asg.Nodes.Statement.LabeledStatementSyntax node, bool callVirtualBase) {
            visit((Columbus.Csharp.Asg.Nodes.Statement.StatementSyntax)node, false);
        }

        /// <summary>
        /// Abstract end visitor, which calls the end visitor of the base class (Columbus.Csharp.Asg.Nodes.Statement.StatementSyntax) of the Columbus.Csharp.Asg.Nodes.Statement.LabeledStatementSyntax node.
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public override void visitEnd(Columbus.Csharp.Asg.Nodes.Statement.LabeledStatementSyntax node, bool callVirtualBase) {
            visitEnd((Columbus.Csharp.Asg.Nodes.Statement.StatementSyntax)node, false);
        }

        /// <summary>
        /// Abstract visitor, which calls the visitor of the base class (Columbus.Csharp.Asg.Nodes.Statement.StatementSyntax) of the Columbus.Csharp.Asg.Nodes.Statement.LocalDeclarationStatementSyntax node.
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public override void visit(Columbus.Csharp.Asg.Nodes.Statement.LocalDeclarationStatementSyntax node, bool callVirtualBase) {
            visit((Columbus.Csharp.Asg.Nodes.Statement.StatementSyntax)node, false);
        }

        /// <summary>
        /// Abstract end visitor, which calls the end visitor of the base class (Columbus.Csharp.Asg.Nodes.Statement.StatementSyntax) of the Columbus.Csharp.Asg.Nodes.Statement.LocalDeclarationStatementSyntax node.
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public override void visitEnd(Columbus.Csharp.Asg.Nodes.Statement.LocalDeclarationStatementSyntax node, bool callVirtualBase) {
            visitEnd((Columbus.Csharp.Asg.Nodes.Statement.StatementSyntax)node, false);
        }

        /// <summary>
        /// Abstract visitor, which calls the visitor of the base class (Columbus.Csharp.Asg.Nodes.Statement.StatementSyntax) of the Columbus.Csharp.Asg.Nodes.Statement.LocalFunctionStatementSyntax node.
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public override void visit(Columbus.Csharp.Asg.Nodes.Statement.LocalFunctionStatementSyntax node, bool callVirtualBase) {
            visit((Columbus.Csharp.Asg.Nodes.Statement.StatementSyntax)node, false);
        }

        /// <summary>
        /// Abstract end visitor, which calls the end visitor of the base class (Columbus.Csharp.Asg.Nodes.Statement.StatementSyntax) of the Columbus.Csharp.Asg.Nodes.Statement.LocalFunctionStatementSyntax node.
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public override void visitEnd(Columbus.Csharp.Asg.Nodes.Statement.LocalFunctionStatementSyntax node, bool callVirtualBase) {
            visitEnd((Columbus.Csharp.Asg.Nodes.Statement.StatementSyntax)node, false);
        }

        /// <summary>
        /// Abstract visitor, which calls the visitor of the base class (Columbus.Csharp.Asg.Nodes.Statement.StatementSyntax) of the Columbus.Csharp.Asg.Nodes.Statement.LockStatementSyntax node.
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public override void visit(Columbus.Csharp.Asg.Nodes.Statement.LockStatementSyntax node, bool callVirtualBase) {
            visit((Columbus.Csharp.Asg.Nodes.Statement.StatementSyntax)node, false);
        }

        /// <summary>
        /// Abstract end visitor, which calls the end visitor of the base class (Columbus.Csharp.Asg.Nodes.Statement.StatementSyntax) of the Columbus.Csharp.Asg.Nodes.Statement.LockStatementSyntax node.
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public override void visitEnd(Columbus.Csharp.Asg.Nodes.Statement.LockStatementSyntax node, bool callVirtualBase) {
            visitEnd((Columbus.Csharp.Asg.Nodes.Statement.StatementSyntax)node, false);
        }

        /// <summary>
        /// Abstract visitor, which calls the visitor of the base class (Columbus.Csharp.Asg.Nodes.Statement.StatementSyntax) of the Columbus.Csharp.Asg.Nodes.Statement.ReturnStatementSyntax node.
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public override void visit(Columbus.Csharp.Asg.Nodes.Statement.ReturnStatementSyntax node, bool callVirtualBase) {
            visit((Columbus.Csharp.Asg.Nodes.Statement.StatementSyntax)node, false);
        }

        /// <summary>
        /// Abstract end visitor, which calls the end visitor of the base class (Columbus.Csharp.Asg.Nodes.Statement.StatementSyntax) of the Columbus.Csharp.Asg.Nodes.Statement.ReturnStatementSyntax node.
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public override void visitEnd(Columbus.Csharp.Asg.Nodes.Statement.ReturnStatementSyntax node, bool callVirtualBase) {
            visitEnd((Columbus.Csharp.Asg.Nodes.Statement.StatementSyntax)node, false);
        }

        /// <summary>
        /// Abstract visitor, which calls the visitor of the base class (Columbus.Csharp.Asg.Nodes.Base.Positioned) of the Columbus.Csharp.Asg.Nodes.Statement.StatementSyntax node.
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public virtual void visit(Columbus.Csharp.Asg.Nodes.Statement.StatementSyntax node, bool callVirtualBase) {
            visit((Columbus.Csharp.Asg.Nodes.Base.Positioned)node, false);
        }

        /// <summary>
        /// Abstract end visitor, which calls the end visitor of the base class (Columbus.Csharp.Asg.Nodes.Base.Positioned) of the Columbus.Csharp.Asg.Nodes.Statement.StatementSyntax node.
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public virtual void visitEnd(Columbus.Csharp.Asg.Nodes.Statement.StatementSyntax node, bool callVirtualBase) {
            visitEnd((Columbus.Csharp.Asg.Nodes.Base.Positioned)node, false);
        }

        /// <summary>
        /// Abstract visitor, which calls the visitor of the base class (Columbus.Csharp.Asg.Nodes.Statement.StatementSyntax) of the Columbus.Csharp.Asg.Nodes.Statement.SwitchStatementSyntax node.
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public override void visit(Columbus.Csharp.Asg.Nodes.Statement.SwitchStatementSyntax node, bool callVirtualBase) {
            visit((Columbus.Csharp.Asg.Nodes.Statement.StatementSyntax)node, false);
        }

        /// <summary>
        /// Abstract end visitor, which calls the end visitor of the base class (Columbus.Csharp.Asg.Nodes.Statement.StatementSyntax) of the Columbus.Csharp.Asg.Nodes.Statement.SwitchStatementSyntax node.
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public override void visitEnd(Columbus.Csharp.Asg.Nodes.Statement.SwitchStatementSyntax node, bool callVirtualBase) {
            visitEnd((Columbus.Csharp.Asg.Nodes.Statement.StatementSyntax)node, false);
        }

        /// <summary>
        /// Abstract visitor, which calls the visitor of the base class (Columbus.Csharp.Asg.Nodes.Statement.StatementSyntax) of the Columbus.Csharp.Asg.Nodes.Statement.ThrowStatementSyntax node.
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public override void visit(Columbus.Csharp.Asg.Nodes.Statement.ThrowStatementSyntax node, bool callVirtualBase) {
            visit((Columbus.Csharp.Asg.Nodes.Statement.StatementSyntax)node, false);
        }

        /// <summary>
        /// Abstract end visitor, which calls the end visitor of the base class (Columbus.Csharp.Asg.Nodes.Statement.StatementSyntax) of the Columbus.Csharp.Asg.Nodes.Statement.ThrowStatementSyntax node.
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public override void visitEnd(Columbus.Csharp.Asg.Nodes.Statement.ThrowStatementSyntax node, bool callVirtualBase) {
            visitEnd((Columbus.Csharp.Asg.Nodes.Statement.StatementSyntax)node, false);
        }

        /// <summary>
        /// Abstract visitor, which calls the visitor of the base class (Columbus.Csharp.Asg.Nodes.Statement.StatementSyntax) of the Columbus.Csharp.Asg.Nodes.Statement.TryStatementSyntax node.
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public override void visit(Columbus.Csharp.Asg.Nodes.Statement.TryStatementSyntax node, bool callVirtualBase) {
            visit((Columbus.Csharp.Asg.Nodes.Statement.StatementSyntax)node, false);
        }

        /// <summary>
        /// Abstract end visitor, which calls the end visitor of the base class (Columbus.Csharp.Asg.Nodes.Statement.StatementSyntax) of the Columbus.Csharp.Asg.Nodes.Statement.TryStatementSyntax node.
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public override void visitEnd(Columbus.Csharp.Asg.Nodes.Statement.TryStatementSyntax node, bool callVirtualBase) {
            visitEnd((Columbus.Csharp.Asg.Nodes.Statement.StatementSyntax)node, false);
        }

        /// <summary>
        /// Abstract visitor, which calls the visitor of the base class (Columbus.Csharp.Asg.Nodes.Statement.StatementSyntax) of the Columbus.Csharp.Asg.Nodes.Statement.UnsafeStatementSyntax node.
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public override void visit(Columbus.Csharp.Asg.Nodes.Statement.UnsafeStatementSyntax node, bool callVirtualBase) {
            visit((Columbus.Csharp.Asg.Nodes.Statement.StatementSyntax)node, false);
        }

        /// <summary>
        /// Abstract end visitor, which calls the end visitor of the base class (Columbus.Csharp.Asg.Nodes.Statement.StatementSyntax) of the Columbus.Csharp.Asg.Nodes.Statement.UnsafeStatementSyntax node.
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public override void visitEnd(Columbus.Csharp.Asg.Nodes.Statement.UnsafeStatementSyntax node, bool callVirtualBase) {
            visitEnd((Columbus.Csharp.Asg.Nodes.Statement.StatementSyntax)node, false);
        }

        /// <summary>
        /// Abstract visitor, which calls the visitor of the base class (Columbus.Csharp.Asg.Nodes.Statement.StatementSyntax) of the Columbus.Csharp.Asg.Nodes.Statement.UsingStatementSyntax node.
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public override void visit(Columbus.Csharp.Asg.Nodes.Statement.UsingStatementSyntax node, bool callVirtualBase) {
            visit((Columbus.Csharp.Asg.Nodes.Statement.StatementSyntax)node, false);
        }

        /// <summary>
        /// Abstract end visitor, which calls the end visitor of the base class (Columbus.Csharp.Asg.Nodes.Statement.StatementSyntax) of the Columbus.Csharp.Asg.Nodes.Statement.UsingStatementSyntax node.
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public override void visitEnd(Columbus.Csharp.Asg.Nodes.Statement.UsingStatementSyntax node, bool callVirtualBase) {
            visitEnd((Columbus.Csharp.Asg.Nodes.Statement.StatementSyntax)node, false);
        }

        /// <summary>
        /// Abstract visitor, which calls the visitor of the base class (Columbus.Csharp.Asg.Nodes.Statement.StatementSyntax) of the Columbus.Csharp.Asg.Nodes.Statement.WhileStatementSyntax node.
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public override void visit(Columbus.Csharp.Asg.Nodes.Statement.WhileStatementSyntax node, bool callVirtualBase) {
            visit((Columbus.Csharp.Asg.Nodes.Statement.StatementSyntax)node, false);
        }

        /// <summary>
        /// Abstract end visitor, which calls the end visitor of the base class (Columbus.Csharp.Asg.Nodes.Statement.StatementSyntax) of the Columbus.Csharp.Asg.Nodes.Statement.WhileStatementSyntax node.
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public override void visitEnd(Columbus.Csharp.Asg.Nodes.Statement.WhileStatementSyntax node, bool callVirtualBase) {
            visitEnd((Columbus.Csharp.Asg.Nodes.Statement.StatementSyntax)node, false);
        }

        /// <summary>
        /// Abstract visitor, which calls the visitor of the base class (Columbus.Csharp.Asg.Nodes.Statement.StatementSyntax) of the Columbus.Csharp.Asg.Nodes.Statement.YieldStatementSyntax node.
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public override void visit(Columbus.Csharp.Asg.Nodes.Statement.YieldStatementSyntax node, bool callVirtualBase) {
            visit((Columbus.Csharp.Asg.Nodes.Statement.StatementSyntax)node, false);
        }

        /// <summary>
        /// Abstract end visitor, which calls the end visitor of the base class (Columbus.Csharp.Asg.Nodes.Statement.StatementSyntax) of the Columbus.Csharp.Asg.Nodes.Statement.YieldStatementSyntax node.
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public override void visitEnd(Columbus.Csharp.Asg.Nodes.Statement.YieldStatementSyntax node, bool callVirtualBase) {
            visitEnd((Columbus.Csharp.Asg.Nodes.Statement.StatementSyntax)node, false);
        }

        /// <summary>
        /// Abstract visitor, which calls the visitor of the base class (Columbus.Csharp.Asg.Nodes.Base.Positioned) of the Columbus.Csharp.Asg.Nodes.Structure.AccessorDeclarationSyntax node.
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public override void visit(Columbus.Csharp.Asg.Nodes.Structure.AccessorDeclarationSyntax node, bool callVirtualBase) {
            visit((Columbus.Csharp.Asg.Nodes.Base.Positioned)node, false);
        }

        /// <summary>
        /// Abstract end visitor, which calls the end visitor of the base class (Columbus.Csharp.Asg.Nodes.Base.Positioned) of the Columbus.Csharp.Asg.Nodes.Structure.AccessorDeclarationSyntax node.
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public override void visitEnd(Columbus.Csharp.Asg.Nodes.Structure.AccessorDeclarationSyntax node, bool callVirtualBase) {
            visitEnd((Columbus.Csharp.Asg.Nodes.Base.Positioned)node, false);
        }

        /// <summary>
        /// Abstract visitor, which calls the visitor of the base class (Columbus.Csharp.Asg.Nodes.Base.Positioned) of the Columbus.Csharp.Asg.Nodes.Structure.AccessorListSyntax node.
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public override void visit(Columbus.Csharp.Asg.Nodes.Structure.AccessorListSyntax node, bool callVirtualBase) {
            visit((Columbus.Csharp.Asg.Nodes.Base.Positioned)node, false);
        }

        /// <summary>
        /// Abstract end visitor, which calls the end visitor of the base class (Columbus.Csharp.Asg.Nodes.Base.Positioned) of the Columbus.Csharp.Asg.Nodes.Structure.AccessorListSyntax node.
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public override void visitEnd(Columbus.Csharp.Asg.Nodes.Structure.AccessorListSyntax node, bool callVirtualBase) {
            visitEnd((Columbus.Csharp.Asg.Nodes.Base.Positioned)node, false);
        }

        /// <summary>
        /// Abstract visitor, which calls the visitor of the base class (Columbus.Csharp.Asg.Nodes.Base.Positioned) of the Columbus.Csharp.Asg.Nodes.Structure.AnonymousObjectMemberDeclaratorSyntax node.
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public override void visit(Columbus.Csharp.Asg.Nodes.Structure.AnonymousObjectMemberDeclaratorSyntax node, bool callVirtualBase) {
            visit((Columbus.Csharp.Asg.Nodes.Base.Positioned)node, false);
        }

        /// <summary>
        /// Abstract end visitor, which calls the end visitor of the base class (Columbus.Csharp.Asg.Nodes.Base.Positioned) of the Columbus.Csharp.Asg.Nodes.Structure.AnonymousObjectMemberDeclaratorSyntax node.
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public override void visitEnd(Columbus.Csharp.Asg.Nodes.Structure.AnonymousObjectMemberDeclaratorSyntax node, bool callVirtualBase) {
            visitEnd((Columbus.Csharp.Asg.Nodes.Base.Positioned)node, false);
        }

        /// <summary>
        /// Abstract visitor, which calls the visitor of the base class (Columbus.Csharp.Asg.Nodes.Structure.BaseArgumentListSyntax) of the Columbus.Csharp.Asg.Nodes.Structure.ArgumentListSyntax node.
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public override void visit(Columbus.Csharp.Asg.Nodes.Structure.ArgumentListSyntax node, bool callVirtualBase) {
            visit((Columbus.Csharp.Asg.Nodes.Structure.BaseArgumentListSyntax)node, false);
        }

        /// <summary>
        /// Abstract end visitor, which calls the end visitor of the base class (Columbus.Csharp.Asg.Nodes.Structure.BaseArgumentListSyntax) of the Columbus.Csharp.Asg.Nodes.Structure.ArgumentListSyntax node.
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public override void visitEnd(Columbus.Csharp.Asg.Nodes.Structure.ArgumentListSyntax node, bool callVirtualBase) {
            visitEnd((Columbus.Csharp.Asg.Nodes.Structure.BaseArgumentListSyntax)node, false);
        }

        /// <summary>
        /// Abstract visitor, which calls the visitor of the base class (Columbus.Csharp.Asg.Nodes.Base.Positioned) of the Columbus.Csharp.Asg.Nodes.Structure.ArgumentSyntax node.
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public override void visit(Columbus.Csharp.Asg.Nodes.Structure.ArgumentSyntax node, bool callVirtualBase) {
            visit((Columbus.Csharp.Asg.Nodes.Base.Positioned)node, false);
        }

        /// <summary>
        /// Abstract end visitor, which calls the end visitor of the base class (Columbus.Csharp.Asg.Nodes.Base.Positioned) of the Columbus.Csharp.Asg.Nodes.Structure.ArgumentSyntax node.
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public override void visitEnd(Columbus.Csharp.Asg.Nodes.Structure.ArgumentSyntax node, bool callVirtualBase) {
            visitEnd((Columbus.Csharp.Asg.Nodes.Base.Positioned)node, false);
        }

        /// <summary>
        /// Abstract visitor, which calls the visitor of the base class (Columbus.Csharp.Asg.Nodes.Base.Positioned) of the Columbus.Csharp.Asg.Nodes.Structure.ArrayRankSpecifierSyntax node.
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public override void visit(Columbus.Csharp.Asg.Nodes.Structure.ArrayRankSpecifierSyntax node, bool callVirtualBase) {
            visit((Columbus.Csharp.Asg.Nodes.Base.Positioned)node, false);
        }

        /// <summary>
        /// Abstract end visitor, which calls the end visitor of the base class (Columbus.Csharp.Asg.Nodes.Base.Positioned) of the Columbus.Csharp.Asg.Nodes.Structure.ArrayRankSpecifierSyntax node.
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public override void visitEnd(Columbus.Csharp.Asg.Nodes.Structure.ArrayRankSpecifierSyntax node, bool callVirtualBase) {
            visitEnd((Columbus.Csharp.Asg.Nodes.Base.Positioned)node, false);
        }

        /// <summary>
        /// Abstract visitor, which calls the visitor of the base class (Columbus.Csharp.Asg.Nodes.Base.Positioned) of the Columbus.Csharp.Asg.Nodes.Structure.ArrowExpressionClauseSyntax node.
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public override void visit(Columbus.Csharp.Asg.Nodes.Structure.ArrowExpressionClauseSyntax node, bool callVirtualBase) {
            visit((Columbus.Csharp.Asg.Nodes.Base.Positioned)node, false);
        }

        /// <summary>
        /// Abstract end visitor, which calls the end visitor of the base class (Columbus.Csharp.Asg.Nodes.Base.Positioned) of the Columbus.Csharp.Asg.Nodes.Structure.ArrowExpressionClauseSyntax node.
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public override void visitEnd(Columbus.Csharp.Asg.Nodes.Structure.ArrowExpressionClauseSyntax node, bool callVirtualBase) {
            visitEnd((Columbus.Csharp.Asg.Nodes.Base.Positioned)node, false);
        }

        /// <summary>
        /// Abstract visitor, which calls the visitor of the base class (Columbus.Csharp.Asg.Nodes.Base.Positioned) of the Columbus.Csharp.Asg.Nodes.Structure.AttributeArgumentListSyntax node.
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public override void visit(Columbus.Csharp.Asg.Nodes.Structure.AttributeArgumentListSyntax node, bool callVirtualBase) {
            visit((Columbus.Csharp.Asg.Nodes.Base.Positioned)node, false);
        }

        /// <summary>
        /// Abstract end visitor, which calls the end visitor of the base class (Columbus.Csharp.Asg.Nodes.Base.Positioned) of the Columbus.Csharp.Asg.Nodes.Structure.AttributeArgumentListSyntax node.
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public override void visitEnd(Columbus.Csharp.Asg.Nodes.Structure.AttributeArgumentListSyntax node, bool callVirtualBase) {
            visitEnd((Columbus.Csharp.Asg.Nodes.Base.Positioned)node, false);
        }

        /// <summary>
        /// Abstract visitor, which calls the visitor of the base class (Columbus.Csharp.Asg.Nodes.Base.Positioned) of the Columbus.Csharp.Asg.Nodes.Structure.AttributeArgumentSyntax node.
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public override void visit(Columbus.Csharp.Asg.Nodes.Structure.AttributeArgumentSyntax node, bool callVirtualBase) {
            visit((Columbus.Csharp.Asg.Nodes.Base.Positioned)node, false);
        }

        /// <summary>
        /// Abstract end visitor, which calls the end visitor of the base class (Columbus.Csharp.Asg.Nodes.Base.Positioned) of the Columbus.Csharp.Asg.Nodes.Structure.AttributeArgumentSyntax node.
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public override void visitEnd(Columbus.Csharp.Asg.Nodes.Structure.AttributeArgumentSyntax node, bool callVirtualBase) {
            visitEnd((Columbus.Csharp.Asg.Nodes.Base.Positioned)node, false);
        }

        /// <summary>
        /// Abstract visitor, which calls the visitor of the base class (Columbus.Csharp.Asg.Nodes.Base.Positioned) of the Columbus.Csharp.Asg.Nodes.Structure.AttributeListSyntax node.
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public override void visit(Columbus.Csharp.Asg.Nodes.Structure.AttributeListSyntax node, bool callVirtualBase) {
            visit((Columbus.Csharp.Asg.Nodes.Base.Positioned)node, false);
        }

        /// <summary>
        /// Abstract end visitor, which calls the end visitor of the base class (Columbus.Csharp.Asg.Nodes.Base.Positioned) of the Columbus.Csharp.Asg.Nodes.Structure.AttributeListSyntax node.
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public override void visitEnd(Columbus.Csharp.Asg.Nodes.Structure.AttributeListSyntax node, bool callVirtualBase) {
            visitEnd((Columbus.Csharp.Asg.Nodes.Base.Positioned)node, false);
        }

        /// <summary>
        /// Abstract visitor, which calls the visitor of the base class (Columbus.Csharp.Asg.Nodes.Base.Positioned) of the Columbus.Csharp.Asg.Nodes.Structure.AttributeSyntax node.
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public override void visit(Columbus.Csharp.Asg.Nodes.Structure.AttributeSyntax node, bool callVirtualBase) {
            visit((Columbus.Csharp.Asg.Nodes.Base.Positioned)node, false);
        }

        /// <summary>
        /// Abstract end visitor, which calls the end visitor of the base class (Columbus.Csharp.Asg.Nodes.Base.Positioned) of the Columbus.Csharp.Asg.Nodes.Structure.AttributeSyntax node.
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public override void visitEnd(Columbus.Csharp.Asg.Nodes.Structure.AttributeSyntax node, bool callVirtualBase) {
            visitEnd((Columbus.Csharp.Asg.Nodes.Base.Positioned)node, false);
        }

        /// <summary>
        /// Abstract visitor, which calls the visitor of the base class (Columbus.Csharp.Asg.Nodes.Base.Positioned) of the Columbus.Csharp.Asg.Nodes.Structure.AttributeTargetSpecifierSyntax node.
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public override void visit(Columbus.Csharp.Asg.Nodes.Structure.AttributeTargetSpecifierSyntax node, bool callVirtualBase) {
            visit((Columbus.Csharp.Asg.Nodes.Base.Positioned)node, false);
        }

        /// <summary>
        /// Abstract end visitor, which calls the end visitor of the base class (Columbus.Csharp.Asg.Nodes.Base.Positioned) of the Columbus.Csharp.Asg.Nodes.Structure.AttributeTargetSpecifierSyntax node.
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public override void visitEnd(Columbus.Csharp.Asg.Nodes.Structure.AttributeTargetSpecifierSyntax node, bool callVirtualBase) {
            visitEnd((Columbus.Csharp.Asg.Nodes.Base.Positioned)node, false);
        }

        /// <summary>
        /// Abstract visitor, which calls the visitor of the base class (Columbus.Csharp.Asg.Nodes.Base.Positioned) of the Columbus.Csharp.Asg.Nodes.Structure.BaseArgumentListSyntax node.
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public virtual void visit(Columbus.Csharp.Asg.Nodes.Structure.BaseArgumentListSyntax node, bool callVirtualBase) {
            visit((Columbus.Csharp.Asg.Nodes.Base.Positioned)node, false);
        }

        /// <summary>
        /// Abstract end visitor, which calls the end visitor of the base class (Columbus.Csharp.Asg.Nodes.Base.Positioned) of the Columbus.Csharp.Asg.Nodes.Structure.BaseArgumentListSyntax node.
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public virtual void visitEnd(Columbus.Csharp.Asg.Nodes.Structure.BaseArgumentListSyntax node, bool callVirtualBase) {
            visitEnd((Columbus.Csharp.Asg.Nodes.Base.Positioned)node, false);
        }

        /// <summary>
        /// Abstract visitor, which calls the visitor of the base class (Columbus.Csharp.Asg.Nodes.Base.Positioned) of the Columbus.Csharp.Asg.Nodes.Structure.BaseCrefParameterListSyntax node.
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public virtual void visit(Columbus.Csharp.Asg.Nodes.Structure.BaseCrefParameterListSyntax node, bool callVirtualBase) {
            visit((Columbus.Csharp.Asg.Nodes.Base.Positioned)node, false);
        }

        /// <summary>
        /// Abstract end visitor, which calls the end visitor of the base class (Columbus.Csharp.Asg.Nodes.Base.Positioned) of the Columbus.Csharp.Asg.Nodes.Structure.BaseCrefParameterListSyntax node.
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public virtual void visitEnd(Columbus.Csharp.Asg.Nodes.Structure.BaseCrefParameterListSyntax node, bool callVirtualBase) {
            visitEnd((Columbus.Csharp.Asg.Nodes.Base.Positioned)node, false);
        }

        /// <summary>
        /// Abstract visitor, which calls the visitor of the base class (Columbus.Csharp.Asg.Nodes.Structure.MemberDeclarationSyntax) of the Columbus.Csharp.Asg.Nodes.Structure.BaseFieldDeclarationSyntax node.
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public virtual void visit(Columbus.Csharp.Asg.Nodes.Structure.BaseFieldDeclarationSyntax node, bool callVirtualBase) {
            visit((Columbus.Csharp.Asg.Nodes.Structure.MemberDeclarationSyntax)node, false);
        }

        /// <summary>
        /// Abstract end visitor, which calls the end visitor of the base class (Columbus.Csharp.Asg.Nodes.Structure.MemberDeclarationSyntax) of the Columbus.Csharp.Asg.Nodes.Structure.BaseFieldDeclarationSyntax node.
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public virtual void visitEnd(Columbus.Csharp.Asg.Nodes.Structure.BaseFieldDeclarationSyntax node, bool callVirtualBase) {
            visitEnd((Columbus.Csharp.Asg.Nodes.Structure.MemberDeclarationSyntax)node, false);
        }

        /// <summary>
        /// Abstract visitor, which calls the visitor of the base class (Columbus.Csharp.Asg.Nodes.Base.Positioned) of the Columbus.Csharp.Asg.Nodes.Structure.BaseListSyntax node.
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public override void visit(Columbus.Csharp.Asg.Nodes.Structure.BaseListSyntax node, bool callVirtualBase) {
            visit((Columbus.Csharp.Asg.Nodes.Base.Positioned)node, false);
        }

        /// <summary>
        /// Abstract end visitor, which calls the end visitor of the base class (Columbus.Csharp.Asg.Nodes.Base.Positioned) of the Columbus.Csharp.Asg.Nodes.Structure.BaseListSyntax node.
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public override void visitEnd(Columbus.Csharp.Asg.Nodes.Structure.BaseListSyntax node, bool callVirtualBase) {
            visitEnd((Columbus.Csharp.Asg.Nodes.Base.Positioned)node, false);
        }

        /// <summary>
        /// Abstract visitor, which calls the visitor of the base class (Columbus.Csharp.Asg.Nodes.Structure.MemberDeclarationSyntax) of the Columbus.Csharp.Asg.Nodes.Structure.BaseMethodDeclarationSyntax node.
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public virtual void visit(Columbus.Csharp.Asg.Nodes.Structure.BaseMethodDeclarationSyntax node, bool callVirtualBase) {
            visit((Columbus.Csharp.Asg.Nodes.Structure.MemberDeclarationSyntax)node, false);
        }

        /// <summary>
        /// Abstract end visitor, which calls the end visitor of the base class (Columbus.Csharp.Asg.Nodes.Structure.MemberDeclarationSyntax) of the Columbus.Csharp.Asg.Nodes.Structure.BaseMethodDeclarationSyntax node.
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public virtual void visitEnd(Columbus.Csharp.Asg.Nodes.Structure.BaseMethodDeclarationSyntax node, bool callVirtualBase) {
            visitEnd((Columbus.Csharp.Asg.Nodes.Structure.MemberDeclarationSyntax)node, false);
        }

        /// <summary>
        /// Abstract visitor, which calls the visitor of the base class (Columbus.Csharp.Asg.Nodes.Base.Positioned) of the Columbus.Csharp.Asg.Nodes.Structure.BaseParameterListSyntax node.
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public virtual void visit(Columbus.Csharp.Asg.Nodes.Structure.BaseParameterListSyntax node, bool callVirtualBase) {
            visit((Columbus.Csharp.Asg.Nodes.Base.Positioned)node, false);
        }

        /// <summary>
        /// Abstract end visitor, which calls the end visitor of the base class (Columbus.Csharp.Asg.Nodes.Base.Positioned) of the Columbus.Csharp.Asg.Nodes.Structure.BaseParameterListSyntax node.
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public virtual void visitEnd(Columbus.Csharp.Asg.Nodes.Structure.BaseParameterListSyntax node, bool callVirtualBase) {
            visitEnd((Columbus.Csharp.Asg.Nodes.Base.Positioned)node, false);
        }

        /// <summary>
        /// Abstract visitor, which calls the visitor of the base class (Columbus.Csharp.Asg.Nodes.Structure.MemberDeclarationSyntax) of the Columbus.Csharp.Asg.Nodes.Structure.BasePropertyDeclarationSyntax node.
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public virtual void visit(Columbus.Csharp.Asg.Nodes.Structure.BasePropertyDeclarationSyntax node, bool callVirtualBase) {
            visit((Columbus.Csharp.Asg.Nodes.Structure.MemberDeclarationSyntax)node, false);
        }

        /// <summary>
        /// Abstract end visitor, which calls the end visitor of the base class (Columbus.Csharp.Asg.Nodes.Structure.MemberDeclarationSyntax) of the Columbus.Csharp.Asg.Nodes.Structure.BasePropertyDeclarationSyntax node.
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public virtual void visitEnd(Columbus.Csharp.Asg.Nodes.Structure.BasePropertyDeclarationSyntax node, bool callVirtualBase) {
            visitEnd((Columbus.Csharp.Asg.Nodes.Structure.MemberDeclarationSyntax)node, false);
        }

        /// <summary>
        /// Abstract visitor, which calls the visitor of the base class (Columbus.Csharp.Asg.Nodes.Structure.MemberDeclarationSyntax) of the Columbus.Csharp.Asg.Nodes.Structure.BaseTypeDeclarationSyntax node.
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public virtual void visit(Columbus.Csharp.Asg.Nodes.Structure.BaseTypeDeclarationSyntax node, bool callVirtualBase) {
            visit((Columbus.Csharp.Asg.Nodes.Structure.MemberDeclarationSyntax)node, false);
        }

        /// <summary>
        /// Abstract end visitor, which calls the end visitor of the base class (Columbus.Csharp.Asg.Nodes.Structure.MemberDeclarationSyntax) of the Columbus.Csharp.Asg.Nodes.Structure.BaseTypeDeclarationSyntax node.
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public virtual void visitEnd(Columbus.Csharp.Asg.Nodes.Structure.BaseTypeDeclarationSyntax node, bool callVirtualBase) {
            visitEnd((Columbus.Csharp.Asg.Nodes.Structure.MemberDeclarationSyntax)node, false);
        }

        /// <summary>
        /// Abstract visitor, which calls the visitor of the base class (Columbus.Csharp.Asg.Nodes.Base.Positioned) of the Columbus.Csharp.Asg.Nodes.Structure.BaseTypeSyntax node.
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public virtual void visit(Columbus.Csharp.Asg.Nodes.Structure.BaseTypeSyntax node, bool callVirtualBase) {
            visit((Columbus.Csharp.Asg.Nodes.Base.Positioned)node, false);
        }

        /// <summary>
        /// Abstract end visitor, which calls the end visitor of the base class (Columbus.Csharp.Asg.Nodes.Base.Positioned) of the Columbus.Csharp.Asg.Nodes.Structure.BaseTypeSyntax node.
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public virtual void visitEnd(Columbus.Csharp.Asg.Nodes.Structure.BaseTypeSyntax node, bool callVirtualBase) {
            visitEnd((Columbus.Csharp.Asg.Nodes.Base.Positioned)node, false);
        }

        /// <summary>
        /// Abstract visitor, which calls the visitor of the base class (Columbus.Csharp.Asg.Nodes.Structure.BaseArgumentListSyntax) of the Columbus.Csharp.Asg.Nodes.Structure.BracketedArgumentListSyntax node.
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public override void visit(Columbus.Csharp.Asg.Nodes.Structure.BracketedArgumentListSyntax node, bool callVirtualBase) {
            visit((Columbus.Csharp.Asg.Nodes.Structure.BaseArgumentListSyntax)node, false);
        }

        /// <summary>
        /// Abstract end visitor, which calls the end visitor of the base class (Columbus.Csharp.Asg.Nodes.Structure.BaseArgumentListSyntax) of the Columbus.Csharp.Asg.Nodes.Structure.BracketedArgumentListSyntax node.
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public override void visitEnd(Columbus.Csharp.Asg.Nodes.Structure.BracketedArgumentListSyntax node, bool callVirtualBase) {
            visitEnd((Columbus.Csharp.Asg.Nodes.Structure.BaseArgumentListSyntax)node, false);
        }

        /// <summary>
        /// Abstract visitor, which calls the visitor of the base class (Columbus.Csharp.Asg.Nodes.Structure.BaseParameterListSyntax) of the Columbus.Csharp.Asg.Nodes.Structure.BracketedParameterListSyntax node.
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public override void visit(Columbus.Csharp.Asg.Nodes.Structure.BracketedParameterListSyntax node, bool callVirtualBase) {
            visit((Columbus.Csharp.Asg.Nodes.Structure.BaseParameterListSyntax)node, false);
        }

        /// <summary>
        /// Abstract end visitor, which calls the end visitor of the base class (Columbus.Csharp.Asg.Nodes.Structure.BaseParameterListSyntax) of the Columbus.Csharp.Asg.Nodes.Structure.BracketedParameterListSyntax node.
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public override void visitEnd(Columbus.Csharp.Asg.Nodes.Structure.BracketedParameterListSyntax node, bool callVirtualBase) {
            visitEnd((Columbus.Csharp.Asg.Nodes.Structure.BaseParameterListSyntax)node, false);
        }

        /// <summary>
        /// Abstract visitor, which calls the visitor of the base class (Columbus.Csharp.Asg.Nodes.Structure.SwitchLabelSyntax) of the Columbus.Csharp.Asg.Nodes.Structure.CasePatternSwitchLabelSyntax node.
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public override void visit(Columbus.Csharp.Asg.Nodes.Structure.CasePatternSwitchLabelSyntax node, bool callVirtualBase) {
            visit((Columbus.Csharp.Asg.Nodes.Structure.SwitchLabelSyntax)node, false);
        }

        /// <summary>
        /// Abstract end visitor, which calls the end visitor of the base class (Columbus.Csharp.Asg.Nodes.Structure.SwitchLabelSyntax) of the Columbus.Csharp.Asg.Nodes.Structure.CasePatternSwitchLabelSyntax node.
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public override void visitEnd(Columbus.Csharp.Asg.Nodes.Structure.CasePatternSwitchLabelSyntax node, bool callVirtualBase) {
            visitEnd((Columbus.Csharp.Asg.Nodes.Structure.SwitchLabelSyntax)node, false);
        }

        /// <summary>
        /// Abstract visitor, which calls the visitor of the base class (Columbus.Csharp.Asg.Nodes.Structure.SwitchLabelSyntax) of the Columbus.Csharp.Asg.Nodes.Structure.CaseSwitchLabelSyntax node.
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public override void visit(Columbus.Csharp.Asg.Nodes.Structure.CaseSwitchLabelSyntax node, bool callVirtualBase) {
            visit((Columbus.Csharp.Asg.Nodes.Structure.SwitchLabelSyntax)node, false);
        }

        /// <summary>
        /// Abstract end visitor, which calls the end visitor of the base class (Columbus.Csharp.Asg.Nodes.Structure.SwitchLabelSyntax) of the Columbus.Csharp.Asg.Nodes.Structure.CaseSwitchLabelSyntax node.
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public override void visitEnd(Columbus.Csharp.Asg.Nodes.Structure.CaseSwitchLabelSyntax node, bool callVirtualBase) {
            visitEnd((Columbus.Csharp.Asg.Nodes.Structure.SwitchLabelSyntax)node, false);
        }

        /// <summary>
        /// Abstract visitor, which calls the visitor of the base class (Columbus.Csharp.Asg.Nodes.Base.Positioned) of the Columbus.Csharp.Asg.Nodes.Structure.CatchClauseSyntax node.
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public override void visit(Columbus.Csharp.Asg.Nodes.Structure.CatchClauseSyntax node, bool callVirtualBase) {
            visit((Columbus.Csharp.Asg.Nodes.Base.Positioned)node, false);
        }

        /// <summary>
        /// Abstract end visitor, which calls the end visitor of the base class (Columbus.Csharp.Asg.Nodes.Base.Positioned) of the Columbus.Csharp.Asg.Nodes.Structure.CatchClauseSyntax node.
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public override void visitEnd(Columbus.Csharp.Asg.Nodes.Structure.CatchClauseSyntax node, bool callVirtualBase) {
            visitEnd((Columbus.Csharp.Asg.Nodes.Base.Positioned)node, false);
        }

        /// <summary>
        /// Abstract visitor, which calls the visitor of the base class (Columbus.Csharp.Asg.Nodes.Base.Positioned) of the Columbus.Csharp.Asg.Nodes.Structure.CatchDeclarationSyntax node.
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public override void visit(Columbus.Csharp.Asg.Nodes.Structure.CatchDeclarationSyntax node, bool callVirtualBase) {
            visit((Columbus.Csharp.Asg.Nodes.Base.Positioned)node, false);
        }

        /// <summary>
        /// Abstract end visitor, which calls the end visitor of the base class (Columbus.Csharp.Asg.Nodes.Base.Positioned) of the Columbus.Csharp.Asg.Nodes.Structure.CatchDeclarationSyntax node.
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public override void visitEnd(Columbus.Csharp.Asg.Nodes.Structure.CatchDeclarationSyntax node, bool callVirtualBase) {
            visitEnd((Columbus.Csharp.Asg.Nodes.Base.Positioned)node, false);
        }

        /// <summary>
        /// Abstract visitor, which calls the visitor of the base class (Columbus.Csharp.Asg.Nodes.Base.Positioned) of the Columbus.Csharp.Asg.Nodes.Structure.CatchFilterClauseSyntax node.
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public override void visit(Columbus.Csharp.Asg.Nodes.Structure.CatchFilterClauseSyntax node, bool callVirtualBase) {
            visit((Columbus.Csharp.Asg.Nodes.Base.Positioned)node, false);
        }

        /// <summary>
        /// Abstract end visitor, which calls the end visitor of the base class (Columbus.Csharp.Asg.Nodes.Base.Positioned) of the Columbus.Csharp.Asg.Nodes.Structure.CatchFilterClauseSyntax node.
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public override void visitEnd(Columbus.Csharp.Asg.Nodes.Structure.CatchFilterClauseSyntax node, bool callVirtualBase) {
            visitEnd((Columbus.Csharp.Asg.Nodes.Base.Positioned)node, false);
        }

        /// <summary>
        /// Abstract visitor, which calls the visitor of the base class (Columbus.Csharp.Asg.Nodes.Structure.TypeDeclarationSyntax) of the Columbus.Csharp.Asg.Nodes.Structure.ClassDeclarationSyntax node.
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public override void visit(Columbus.Csharp.Asg.Nodes.Structure.ClassDeclarationSyntax node, bool callVirtualBase) {
            visit((Columbus.Csharp.Asg.Nodes.Structure.TypeDeclarationSyntax)node, false);
        }

        /// <summary>
        /// Abstract end visitor, which calls the end visitor of the base class (Columbus.Csharp.Asg.Nodes.Structure.TypeDeclarationSyntax) of the Columbus.Csharp.Asg.Nodes.Structure.ClassDeclarationSyntax node.
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public override void visitEnd(Columbus.Csharp.Asg.Nodes.Structure.ClassDeclarationSyntax node, bool callVirtualBase) {
            visitEnd((Columbus.Csharp.Asg.Nodes.Structure.TypeDeclarationSyntax)node, false);
        }

        /// <summary>
        /// Abstract visitor, which calls the visitor of the base class (Columbus.Csharp.Asg.Nodes.Structure.TypeParameterConstraintSyntax) of the Columbus.Csharp.Asg.Nodes.Structure.ClassOrStructConstraintSyntax node.
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public override void visit(Columbus.Csharp.Asg.Nodes.Structure.ClassOrStructConstraintSyntax node, bool callVirtualBase) {
            visit((Columbus.Csharp.Asg.Nodes.Structure.TypeParameterConstraintSyntax)node, false);
        }

        /// <summary>
        /// Abstract end visitor, which calls the end visitor of the base class (Columbus.Csharp.Asg.Nodes.Structure.TypeParameterConstraintSyntax) of the Columbus.Csharp.Asg.Nodes.Structure.ClassOrStructConstraintSyntax node.
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public override void visitEnd(Columbus.Csharp.Asg.Nodes.Structure.ClassOrStructConstraintSyntax node, bool callVirtualBase) {
            visitEnd((Columbus.Csharp.Asg.Nodes.Structure.TypeParameterConstraintSyntax)node, false);
        }

        /// <summary>
        /// Abstract visitor, which calls the visitor of the base class (Columbus.Csharp.Asg.Nodes.Base.Positioned) of the Columbus.Csharp.Asg.Nodes.Structure.CompilationUnitSyntax node.
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public override void visit(Columbus.Csharp.Asg.Nodes.Structure.CompilationUnitSyntax node, bool callVirtualBase) {
            visit((Columbus.Csharp.Asg.Nodes.Base.Positioned)node, false);
        }

        /// <summary>
        /// Abstract end visitor, which calls the end visitor of the base class (Columbus.Csharp.Asg.Nodes.Base.Positioned) of the Columbus.Csharp.Asg.Nodes.Structure.CompilationUnitSyntax node.
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public override void visitEnd(Columbus.Csharp.Asg.Nodes.Structure.CompilationUnitSyntax node, bool callVirtualBase) {
            visitEnd((Columbus.Csharp.Asg.Nodes.Base.Positioned)node, false);
        }

        /// <summary>
        /// Abstract visitor, which calls the visitor of the base class (Columbus.Csharp.Asg.Nodes.Structure.PatternSyntax) of the Columbus.Csharp.Asg.Nodes.Structure.ConstantPatternSyntax node.
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public override void visit(Columbus.Csharp.Asg.Nodes.Structure.ConstantPatternSyntax node, bool callVirtualBase) {
            visit((Columbus.Csharp.Asg.Nodes.Structure.PatternSyntax)node, false);
        }

        /// <summary>
        /// Abstract end visitor, which calls the end visitor of the base class (Columbus.Csharp.Asg.Nodes.Structure.PatternSyntax) of the Columbus.Csharp.Asg.Nodes.Structure.ConstantPatternSyntax node.
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public override void visitEnd(Columbus.Csharp.Asg.Nodes.Structure.ConstantPatternSyntax node, bool callVirtualBase) {
            visitEnd((Columbus.Csharp.Asg.Nodes.Structure.PatternSyntax)node, false);
        }

        /// <summary>
        /// Abstract visitor, which calls the visitor of the base class (Columbus.Csharp.Asg.Nodes.Structure.TypeParameterConstraintSyntax) of the Columbus.Csharp.Asg.Nodes.Structure.ConstructorConstraintSyntax node.
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public override void visit(Columbus.Csharp.Asg.Nodes.Structure.ConstructorConstraintSyntax node, bool callVirtualBase) {
            visit((Columbus.Csharp.Asg.Nodes.Structure.TypeParameterConstraintSyntax)node, false);
        }

        /// <summary>
        /// Abstract end visitor, which calls the end visitor of the base class (Columbus.Csharp.Asg.Nodes.Structure.TypeParameterConstraintSyntax) of the Columbus.Csharp.Asg.Nodes.Structure.ConstructorConstraintSyntax node.
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public override void visitEnd(Columbus.Csharp.Asg.Nodes.Structure.ConstructorConstraintSyntax node, bool callVirtualBase) {
            visitEnd((Columbus.Csharp.Asg.Nodes.Structure.TypeParameterConstraintSyntax)node, false);
        }

        /// <summary>
        /// Abstract visitor, which calls the visitor of the base class (Columbus.Csharp.Asg.Nodes.Structure.BaseMethodDeclarationSyntax) of the Columbus.Csharp.Asg.Nodes.Structure.ConstructorDeclarationSyntax node.
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public override void visit(Columbus.Csharp.Asg.Nodes.Structure.ConstructorDeclarationSyntax node, bool callVirtualBase) {
            visit((Columbus.Csharp.Asg.Nodes.Structure.BaseMethodDeclarationSyntax)node, false);
        }

        /// <summary>
        /// Abstract end visitor, which calls the end visitor of the base class (Columbus.Csharp.Asg.Nodes.Structure.BaseMethodDeclarationSyntax) of the Columbus.Csharp.Asg.Nodes.Structure.ConstructorDeclarationSyntax node.
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public override void visitEnd(Columbus.Csharp.Asg.Nodes.Structure.ConstructorDeclarationSyntax node, bool callVirtualBase) {
            visitEnd((Columbus.Csharp.Asg.Nodes.Structure.BaseMethodDeclarationSyntax)node, false);
        }

        /// <summary>
        /// Abstract visitor, which calls the visitor of the base class (Columbus.Csharp.Asg.Nodes.Base.Positioned) of the Columbus.Csharp.Asg.Nodes.Structure.ConstructorInitializerSyntax node.
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public override void visit(Columbus.Csharp.Asg.Nodes.Structure.ConstructorInitializerSyntax node, bool callVirtualBase) {
            visit((Columbus.Csharp.Asg.Nodes.Base.Positioned)node, false);
        }

        /// <summary>
        /// Abstract end visitor, which calls the end visitor of the base class (Columbus.Csharp.Asg.Nodes.Base.Positioned) of the Columbus.Csharp.Asg.Nodes.Structure.ConstructorInitializerSyntax node.
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public override void visitEnd(Columbus.Csharp.Asg.Nodes.Structure.ConstructorInitializerSyntax node, bool callVirtualBase) {
            visitEnd((Columbus.Csharp.Asg.Nodes.Base.Positioned)node, false);
        }

        /// <summary>
        /// Abstract visitor, which calls the visitor of the base class (Columbus.Csharp.Asg.Nodes.Structure.BaseMethodDeclarationSyntax) of the Columbus.Csharp.Asg.Nodes.Structure.ConversionOperatorDeclarationSyntax node.
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public override void visit(Columbus.Csharp.Asg.Nodes.Structure.ConversionOperatorDeclarationSyntax node, bool callVirtualBase) {
            visit((Columbus.Csharp.Asg.Nodes.Structure.BaseMethodDeclarationSyntax)node, false);
        }

        /// <summary>
        /// Abstract end visitor, which calls the end visitor of the base class (Columbus.Csharp.Asg.Nodes.Structure.BaseMethodDeclarationSyntax) of the Columbus.Csharp.Asg.Nodes.Structure.ConversionOperatorDeclarationSyntax node.
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public override void visitEnd(Columbus.Csharp.Asg.Nodes.Structure.ConversionOperatorDeclarationSyntax node, bool callVirtualBase) {
            visitEnd((Columbus.Csharp.Asg.Nodes.Structure.BaseMethodDeclarationSyntax)node, false);
        }

        /// <summary>
        /// Abstract visitor, which calls the visitor of the base class (Columbus.Csharp.Asg.Nodes.Structure.MemberCrefSyntax) of the Columbus.Csharp.Asg.Nodes.Structure.ConversionOperatorMemberCrefSyntax node.
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public override void visit(Columbus.Csharp.Asg.Nodes.Structure.ConversionOperatorMemberCrefSyntax node, bool callVirtualBase) {
            visit((Columbus.Csharp.Asg.Nodes.Structure.MemberCrefSyntax)node, false);
        }

        /// <summary>
        /// Abstract end visitor, which calls the end visitor of the base class (Columbus.Csharp.Asg.Nodes.Structure.MemberCrefSyntax) of the Columbus.Csharp.Asg.Nodes.Structure.ConversionOperatorMemberCrefSyntax node.
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public override void visitEnd(Columbus.Csharp.Asg.Nodes.Structure.ConversionOperatorMemberCrefSyntax node, bool callVirtualBase) {
            visitEnd((Columbus.Csharp.Asg.Nodes.Structure.MemberCrefSyntax)node, false);
        }

        /// <summary>
        /// Abstract visitor, which calls the visitor of the base class (Columbus.Csharp.Asg.Nodes.Structure.BaseCrefParameterListSyntax) of the Columbus.Csharp.Asg.Nodes.Structure.CrefBracketedParameterListSyntax node.
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public override void visit(Columbus.Csharp.Asg.Nodes.Structure.CrefBracketedParameterListSyntax node, bool callVirtualBase) {
            visit((Columbus.Csharp.Asg.Nodes.Structure.BaseCrefParameterListSyntax)node, false);
        }

        /// <summary>
        /// Abstract end visitor, which calls the end visitor of the base class (Columbus.Csharp.Asg.Nodes.Structure.BaseCrefParameterListSyntax) of the Columbus.Csharp.Asg.Nodes.Structure.CrefBracketedParameterListSyntax node.
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public override void visitEnd(Columbus.Csharp.Asg.Nodes.Structure.CrefBracketedParameterListSyntax node, bool callVirtualBase) {
            visitEnd((Columbus.Csharp.Asg.Nodes.Structure.BaseCrefParameterListSyntax)node, false);
        }

        /// <summary>
        /// Abstract visitor, which calls the visitor of the base class (Columbus.Csharp.Asg.Nodes.Structure.BaseCrefParameterListSyntax) of the Columbus.Csharp.Asg.Nodes.Structure.CrefParameterListSyntax node.
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public override void visit(Columbus.Csharp.Asg.Nodes.Structure.CrefParameterListSyntax node, bool callVirtualBase) {
            visit((Columbus.Csharp.Asg.Nodes.Structure.BaseCrefParameterListSyntax)node, false);
        }

        /// <summary>
        /// Abstract end visitor, which calls the end visitor of the base class (Columbus.Csharp.Asg.Nodes.Structure.BaseCrefParameterListSyntax) of the Columbus.Csharp.Asg.Nodes.Structure.CrefParameterListSyntax node.
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public override void visitEnd(Columbus.Csharp.Asg.Nodes.Structure.CrefParameterListSyntax node, bool callVirtualBase) {
            visitEnd((Columbus.Csharp.Asg.Nodes.Structure.BaseCrefParameterListSyntax)node, false);
        }

        /// <summary>
        /// Abstract visitor, which calls the visitor of the base class (Columbus.Csharp.Asg.Nodes.Base.Positioned) of the Columbus.Csharp.Asg.Nodes.Structure.CrefParameterSyntax node.
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public override void visit(Columbus.Csharp.Asg.Nodes.Structure.CrefParameterSyntax node, bool callVirtualBase) {
            visit((Columbus.Csharp.Asg.Nodes.Base.Positioned)node, false);
        }

        /// <summary>
        /// Abstract end visitor, which calls the end visitor of the base class (Columbus.Csharp.Asg.Nodes.Base.Positioned) of the Columbus.Csharp.Asg.Nodes.Structure.CrefParameterSyntax node.
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public override void visitEnd(Columbus.Csharp.Asg.Nodes.Structure.CrefParameterSyntax node, bool callVirtualBase) {
            visitEnd((Columbus.Csharp.Asg.Nodes.Base.Positioned)node, false);
        }

        /// <summary>
        /// Abstract visitor, which calls the visitor of the base class (Columbus.Csharp.Asg.Nodes.Base.Positioned) of the Columbus.Csharp.Asg.Nodes.Structure.CrefSyntax node.
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public virtual void visit(Columbus.Csharp.Asg.Nodes.Structure.CrefSyntax node, bool callVirtualBase) {
            visit((Columbus.Csharp.Asg.Nodes.Base.Positioned)node, false);
        }

        /// <summary>
        /// Abstract end visitor, which calls the end visitor of the base class (Columbus.Csharp.Asg.Nodes.Base.Positioned) of the Columbus.Csharp.Asg.Nodes.Structure.CrefSyntax node.
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public virtual void visitEnd(Columbus.Csharp.Asg.Nodes.Structure.CrefSyntax node, bool callVirtualBase) {
            visitEnd((Columbus.Csharp.Asg.Nodes.Base.Positioned)node, false);
        }

        /// <summary>
        /// Abstract visitor, which calls the visitor of the base class (Columbus.Csharp.Asg.Nodes.Structure.PatternSyntax) of the Columbus.Csharp.Asg.Nodes.Structure.DeclarationPatternSyntax node.
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public override void visit(Columbus.Csharp.Asg.Nodes.Structure.DeclarationPatternSyntax node, bool callVirtualBase) {
            visit((Columbus.Csharp.Asg.Nodes.Structure.PatternSyntax)node, false);
        }

        /// <summary>
        /// Abstract end visitor, which calls the end visitor of the base class (Columbus.Csharp.Asg.Nodes.Structure.PatternSyntax) of the Columbus.Csharp.Asg.Nodes.Structure.DeclarationPatternSyntax node.
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public override void visitEnd(Columbus.Csharp.Asg.Nodes.Structure.DeclarationPatternSyntax node, bool callVirtualBase) {
            visitEnd((Columbus.Csharp.Asg.Nodes.Structure.PatternSyntax)node, false);
        }

        /// <summary>
        /// Abstract visitor, which calls the visitor of the base class (Columbus.Csharp.Asg.Nodes.Structure.SwitchLabelSyntax) of the Columbus.Csharp.Asg.Nodes.Structure.DefaultSwitchLabelSyntax node.
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public override void visit(Columbus.Csharp.Asg.Nodes.Structure.DefaultSwitchLabelSyntax node, bool callVirtualBase) {
            visit((Columbus.Csharp.Asg.Nodes.Structure.SwitchLabelSyntax)node, false);
        }

        /// <summary>
        /// Abstract end visitor, which calls the end visitor of the base class (Columbus.Csharp.Asg.Nodes.Structure.SwitchLabelSyntax) of the Columbus.Csharp.Asg.Nodes.Structure.DefaultSwitchLabelSyntax node.
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public override void visitEnd(Columbus.Csharp.Asg.Nodes.Structure.DefaultSwitchLabelSyntax node, bool callVirtualBase) {
            visitEnd((Columbus.Csharp.Asg.Nodes.Structure.SwitchLabelSyntax)node, false);
        }

        /// <summary>
        /// Abstract visitor, which calls the visitor of the base class (Columbus.Csharp.Asg.Nodes.Structure.MemberDeclarationSyntax) of the Columbus.Csharp.Asg.Nodes.Structure.DelegateDeclarationSyntax node.
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public override void visit(Columbus.Csharp.Asg.Nodes.Structure.DelegateDeclarationSyntax node, bool callVirtualBase) {
            visit((Columbus.Csharp.Asg.Nodes.Structure.MemberDeclarationSyntax)node, false);
        }

        /// <summary>
        /// Abstract end visitor, which calls the end visitor of the base class (Columbus.Csharp.Asg.Nodes.Structure.MemberDeclarationSyntax) of the Columbus.Csharp.Asg.Nodes.Structure.DelegateDeclarationSyntax node.
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public override void visitEnd(Columbus.Csharp.Asg.Nodes.Structure.DelegateDeclarationSyntax node, bool callVirtualBase) {
            visitEnd((Columbus.Csharp.Asg.Nodes.Structure.MemberDeclarationSyntax)node, false);
        }

        /// <summary>
        /// Abstract visitor, which calls the visitor of the base class (Columbus.Csharp.Asg.Nodes.Structure.BaseMethodDeclarationSyntax) of the Columbus.Csharp.Asg.Nodes.Structure.DestructorDeclarationSyntax node.
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public override void visit(Columbus.Csharp.Asg.Nodes.Structure.DestructorDeclarationSyntax node, bool callVirtualBase) {
            visit((Columbus.Csharp.Asg.Nodes.Structure.BaseMethodDeclarationSyntax)node, false);
        }

        /// <summary>
        /// Abstract end visitor, which calls the end visitor of the base class (Columbus.Csharp.Asg.Nodes.Structure.BaseMethodDeclarationSyntax) of the Columbus.Csharp.Asg.Nodes.Structure.DestructorDeclarationSyntax node.
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public override void visitEnd(Columbus.Csharp.Asg.Nodes.Structure.DestructorDeclarationSyntax node, bool callVirtualBase) {
            visitEnd((Columbus.Csharp.Asg.Nodes.Structure.BaseMethodDeclarationSyntax)node, false);
        }

        /// <summary>
        /// Abstract visitor, which calls the visitor of the base class (Columbus.Csharp.Asg.Nodes.Structure.VariableDesignationSyntax) of the Columbus.Csharp.Asg.Nodes.Structure.DiscardDesignationSyntax node.
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public override void visit(Columbus.Csharp.Asg.Nodes.Structure.DiscardDesignationSyntax node, bool callVirtualBase) {
            visit((Columbus.Csharp.Asg.Nodes.Structure.VariableDesignationSyntax)node, false);
        }

        /// <summary>
        /// Abstract end visitor, which calls the end visitor of the base class (Columbus.Csharp.Asg.Nodes.Structure.VariableDesignationSyntax) of the Columbus.Csharp.Asg.Nodes.Structure.DiscardDesignationSyntax node.
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public override void visitEnd(Columbus.Csharp.Asg.Nodes.Structure.DiscardDesignationSyntax node, bool callVirtualBase) {
            visitEnd((Columbus.Csharp.Asg.Nodes.Structure.VariableDesignationSyntax)node, false);
        }

        /// <summary>
        /// Abstract visitor, which calls the visitor of the base class (Columbus.Csharp.Asg.Nodes.Structure.PatternSyntax) of the Columbus.Csharp.Asg.Nodes.Structure.DiscardPatternSyntax node.
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public override void visit(Columbus.Csharp.Asg.Nodes.Structure.DiscardPatternSyntax node, bool callVirtualBase) {
            visit((Columbus.Csharp.Asg.Nodes.Structure.PatternSyntax)node, false);
        }

        /// <summary>
        /// Abstract end visitor, which calls the end visitor of the base class (Columbus.Csharp.Asg.Nodes.Structure.PatternSyntax) of the Columbus.Csharp.Asg.Nodes.Structure.DiscardPatternSyntax node.
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public override void visitEnd(Columbus.Csharp.Asg.Nodes.Structure.DiscardPatternSyntax node, bool callVirtualBase) {
            visitEnd((Columbus.Csharp.Asg.Nodes.Structure.PatternSyntax)node, false);
        }

        /// <summary>
        /// Abstract visitor, which calls the visitor of the base class (Columbus.Csharp.Asg.Nodes.Base.Positioned) of the Columbus.Csharp.Asg.Nodes.Structure.ElseClauseSyntax node.
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public override void visit(Columbus.Csharp.Asg.Nodes.Structure.ElseClauseSyntax node, bool callVirtualBase) {
            visit((Columbus.Csharp.Asg.Nodes.Base.Positioned)node, false);
        }

        /// <summary>
        /// Abstract end visitor, which calls the end visitor of the base class (Columbus.Csharp.Asg.Nodes.Base.Positioned) of the Columbus.Csharp.Asg.Nodes.Structure.ElseClauseSyntax node.
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public override void visitEnd(Columbus.Csharp.Asg.Nodes.Structure.ElseClauseSyntax node, bool callVirtualBase) {
            visitEnd((Columbus.Csharp.Asg.Nodes.Base.Positioned)node, false);
        }

        /// <summary>
        /// Abstract visitor, which calls the visitor of the base class (Columbus.Csharp.Asg.Nodes.Structure.BaseTypeDeclarationSyntax) of the Columbus.Csharp.Asg.Nodes.Structure.EnumDeclarationSyntax node.
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public override void visit(Columbus.Csharp.Asg.Nodes.Structure.EnumDeclarationSyntax node, bool callVirtualBase) {
            visit((Columbus.Csharp.Asg.Nodes.Structure.BaseTypeDeclarationSyntax)node, false);
        }

        /// <summary>
        /// Abstract end visitor, which calls the end visitor of the base class (Columbus.Csharp.Asg.Nodes.Structure.BaseTypeDeclarationSyntax) of the Columbus.Csharp.Asg.Nodes.Structure.EnumDeclarationSyntax node.
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public override void visitEnd(Columbus.Csharp.Asg.Nodes.Structure.EnumDeclarationSyntax node, bool callVirtualBase) {
            visitEnd((Columbus.Csharp.Asg.Nodes.Structure.BaseTypeDeclarationSyntax)node, false);
        }

        /// <summary>
        /// Abstract visitor, which calls the visitor of the base class (Columbus.Csharp.Asg.Nodes.Structure.MemberDeclarationSyntax) of the Columbus.Csharp.Asg.Nodes.Structure.EnumMemberDeclarationSyntax node.
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public override void visit(Columbus.Csharp.Asg.Nodes.Structure.EnumMemberDeclarationSyntax node, bool callVirtualBase) {
            visit((Columbus.Csharp.Asg.Nodes.Structure.MemberDeclarationSyntax)node, false);
        }

        /// <summary>
        /// Abstract end visitor, which calls the end visitor of the base class (Columbus.Csharp.Asg.Nodes.Structure.MemberDeclarationSyntax) of the Columbus.Csharp.Asg.Nodes.Structure.EnumMemberDeclarationSyntax node.
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public override void visitEnd(Columbus.Csharp.Asg.Nodes.Structure.EnumMemberDeclarationSyntax node, bool callVirtualBase) {
            visitEnd((Columbus.Csharp.Asg.Nodes.Structure.MemberDeclarationSyntax)node, false);
        }

        /// <summary>
        /// Abstract visitor, which calls the visitor of the base class (Columbus.Csharp.Asg.Nodes.Base.Positioned) of the Columbus.Csharp.Asg.Nodes.Structure.EqualsValueClauseSyntax node.
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public override void visit(Columbus.Csharp.Asg.Nodes.Structure.EqualsValueClauseSyntax node, bool callVirtualBase) {
            visit((Columbus.Csharp.Asg.Nodes.Base.Positioned)node, false);
        }

        /// <summary>
        /// Abstract end visitor, which calls the end visitor of the base class (Columbus.Csharp.Asg.Nodes.Base.Positioned) of the Columbus.Csharp.Asg.Nodes.Structure.EqualsValueClauseSyntax node.
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public override void visitEnd(Columbus.Csharp.Asg.Nodes.Structure.EqualsValueClauseSyntax node, bool callVirtualBase) {
            visitEnd((Columbus.Csharp.Asg.Nodes.Base.Positioned)node, false);
        }

        /// <summary>
        /// Abstract visitor, which calls the visitor of the base class (Columbus.Csharp.Asg.Nodes.Structure.BasePropertyDeclarationSyntax) of the Columbus.Csharp.Asg.Nodes.Structure.EventDeclarationSyntax node.
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public override void visit(Columbus.Csharp.Asg.Nodes.Structure.EventDeclarationSyntax node, bool callVirtualBase) {
            visit((Columbus.Csharp.Asg.Nodes.Structure.BasePropertyDeclarationSyntax)node, false);
        }

        /// <summary>
        /// Abstract end visitor, which calls the end visitor of the base class (Columbus.Csharp.Asg.Nodes.Structure.BasePropertyDeclarationSyntax) of the Columbus.Csharp.Asg.Nodes.Structure.EventDeclarationSyntax node.
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public override void visitEnd(Columbus.Csharp.Asg.Nodes.Structure.EventDeclarationSyntax node, bool callVirtualBase) {
            visitEnd((Columbus.Csharp.Asg.Nodes.Structure.BasePropertyDeclarationSyntax)node, false);
        }

        /// <summary>
        /// Abstract visitor, which calls the visitor of the base class (Columbus.Csharp.Asg.Nodes.Structure.BaseFieldDeclarationSyntax) of the Columbus.Csharp.Asg.Nodes.Structure.EventFieldDeclarationSyntax node.
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public override void visit(Columbus.Csharp.Asg.Nodes.Structure.EventFieldDeclarationSyntax node, bool callVirtualBase) {
            visit((Columbus.Csharp.Asg.Nodes.Structure.BaseFieldDeclarationSyntax)node, false);
        }

        /// <summary>
        /// Abstract end visitor, which calls the end visitor of the base class (Columbus.Csharp.Asg.Nodes.Structure.BaseFieldDeclarationSyntax) of the Columbus.Csharp.Asg.Nodes.Structure.EventFieldDeclarationSyntax node.
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public override void visitEnd(Columbus.Csharp.Asg.Nodes.Structure.EventFieldDeclarationSyntax node, bool callVirtualBase) {
            visitEnd((Columbus.Csharp.Asg.Nodes.Structure.BaseFieldDeclarationSyntax)node, false);
        }

        /// <summary>
        /// Abstract visitor, which calls the visitor of the base class (Columbus.Csharp.Asg.Nodes.Base.Positioned) of the Columbus.Csharp.Asg.Nodes.Structure.ExplicitInterfaceSpecifierSyntax node.
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public override void visit(Columbus.Csharp.Asg.Nodes.Structure.ExplicitInterfaceSpecifierSyntax node, bool callVirtualBase) {
            visit((Columbus.Csharp.Asg.Nodes.Base.Positioned)node, false);
        }

        /// <summary>
        /// Abstract end visitor, which calls the end visitor of the base class (Columbus.Csharp.Asg.Nodes.Base.Positioned) of the Columbus.Csharp.Asg.Nodes.Structure.ExplicitInterfaceSpecifierSyntax node.
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public override void visitEnd(Columbus.Csharp.Asg.Nodes.Structure.ExplicitInterfaceSpecifierSyntax node, bool callVirtualBase) {
            visitEnd((Columbus.Csharp.Asg.Nodes.Base.Positioned)node, false);
        }

        /// <summary>
        /// Abstract visitor, which calls the visitor of the base class (Columbus.Csharp.Asg.Nodes.Base.Positioned) of the Columbus.Csharp.Asg.Nodes.Structure.ExternAliasDirectiveSyntax node.
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public override void visit(Columbus.Csharp.Asg.Nodes.Structure.ExternAliasDirectiveSyntax node, bool callVirtualBase) {
            visit((Columbus.Csharp.Asg.Nodes.Base.Positioned)node, false);
        }

        /// <summary>
        /// Abstract end visitor, which calls the end visitor of the base class (Columbus.Csharp.Asg.Nodes.Base.Positioned) of the Columbus.Csharp.Asg.Nodes.Structure.ExternAliasDirectiveSyntax node.
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public override void visitEnd(Columbus.Csharp.Asg.Nodes.Structure.ExternAliasDirectiveSyntax node, bool callVirtualBase) {
            visitEnd((Columbus.Csharp.Asg.Nodes.Base.Positioned)node, false);
        }

        /// <summary>
        /// Abstract visitor, which calls the visitor of the base class (Columbus.Csharp.Asg.Nodes.Structure.BaseFieldDeclarationSyntax) of the Columbus.Csharp.Asg.Nodes.Structure.FieldDeclarationSyntax node.
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public override void visit(Columbus.Csharp.Asg.Nodes.Structure.FieldDeclarationSyntax node, bool callVirtualBase) {
            visit((Columbus.Csharp.Asg.Nodes.Structure.BaseFieldDeclarationSyntax)node, false);
        }

        /// <summary>
        /// Abstract end visitor, which calls the end visitor of the base class (Columbus.Csharp.Asg.Nodes.Structure.BaseFieldDeclarationSyntax) of the Columbus.Csharp.Asg.Nodes.Structure.FieldDeclarationSyntax node.
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public override void visitEnd(Columbus.Csharp.Asg.Nodes.Structure.FieldDeclarationSyntax node, bool callVirtualBase) {
            visitEnd((Columbus.Csharp.Asg.Nodes.Structure.BaseFieldDeclarationSyntax)node, false);
        }

        /// <summary>
        /// Abstract visitor, which calls the visitor of the base class (Columbus.Csharp.Asg.Nodes.Base.Positioned) of the Columbus.Csharp.Asg.Nodes.Structure.FinallyClauseSyntax node.
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public override void visit(Columbus.Csharp.Asg.Nodes.Structure.FinallyClauseSyntax node, bool callVirtualBase) {
            visit((Columbus.Csharp.Asg.Nodes.Base.Positioned)node, false);
        }

        /// <summary>
        /// Abstract end visitor, which calls the end visitor of the base class (Columbus.Csharp.Asg.Nodes.Base.Positioned) of the Columbus.Csharp.Asg.Nodes.Structure.FinallyClauseSyntax node.
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public override void visitEnd(Columbus.Csharp.Asg.Nodes.Structure.FinallyClauseSyntax node, bool callVirtualBase) {
            visitEnd((Columbus.Csharp.Asg.Nodes.Base.Positioned)node, false);
        }

        /// <summary>
        /// Abstract visitor, which calls the visitor of the base class (Columbus.Csharp.Asg.Nodes.Structure.QueryClauseSyntax) of the Columbus.Csharp.Asg.Nodes.Structure.FromClauseSyntax node.
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public override void visit(Columbus.Csharp.Asg.Nodes.Structure.FromClauseSyntax node, bool callVirtualBase) {
            visit((Columbus.Csharp.Asg.Nodes.Structure.QueryClauseSyntax)node, false);
        }

        /// <summary>
        /// Abstract end visitor, which calls the end visitor of the base class (Columbus.Csharp.Asg.Nodes.Structure.QueryClauseSyntax) of the Columbus.Csharp.Asg.Nodes.Structure.FromClauseSyntax node.
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public override void visitEnd(Columbus.Csharp.Asg.Nodes.Structure.FromClauseSyntax node, bool callVirtualBase) {
            visitEnd((Columbus.Csharp.Asg.Nodes.Structure.QueryClauseSyntax)node, false);
        }

        /// <summary>
        /// Abstract visitor, which calls the visitor of the base class (Columbus.Csharp.Asg.Nodes.Structure.MemberDeclarationSyntax) of the Columbus.Csharp.Asg.Nodes.Structure.GlobalStatementSyntax node.
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public override void visit(Columbus.Csharp.Asg.Nodes.Structure.GlobalStatementSyntax node, bool callVirtualBase) {
            visit((Columbus.Csharp.Asg.Nodes.Structure.MemberDeclarationSyntax)node, false);
        }

        /// <summary>
        /// Abstract end visitor, which calls the end visitor of the base class (Columbus.Csharp.Asg.Nodes.Structure.MemberDeclarationSyntax) of the Columbus.Csharp.Asg.Nodes.Structure.GlobalStatementSyntax node.
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public override void visitEnd(Columbus.Csharp.Asg.Nodes.Structure.GlobalStatementSyntax node, bool callVirtualBase) {
            visitEnd((Columbus.Csharp.Asg.Nodes.Structure.MemberDeclarationSyntax)node, false);
        }

        /// <summary>
        /// Abstract visitor, which calls the visitor of the base class (Columbus.Csharp.Asg.Nodes.Structure.SelectOrGroupClauseSyntax) of the Columbus.Csharp.Asg.Nodes.Structure.GroupClauseSyntax node.
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public override void visit(Columbus.Csharp.Asg.Nodes.Structure.GroupClauseSyntax node, bool callVirtualBase) {
            visit((Columbus.Csharp.Asg.Nodes.Structure.SelectOrGroupClauseSyntax)node, false);
        }

        /// <summary>
        /// Abstract end visitor, which calls the end visitor of the base class (Columbus.Csharp.Asg.Nodes.Structure.SelectOrGroupClauseSyntax) of the Columbus.Csharp.Asg.Nodes.Structure.GroupClauseSyntax node.
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public override void visitEnd(Columbus.Csharp.Asg.Nodes.Structure.GroupClauseSyntax node, bool callVirtualBase) {
            visitEnd((Columbus.Csharp.Asg.Nodes.Structure.SelectOrGroupClauseSyntax)node, false);
        }

        /// <summary>
        /// Abstract visitor, which calls the visitor of the base class (Columbus.Csharp.Asg.Nodes.Structure.MemberDeclarationSyntax) of the Columbus.Csharp.Asg.Nodes.Structure.IncompleteMemberSyntax node.
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public override void visit(Columbus.Csharp.Asg.Nodes.Structure.IncompleteMemberSyntax node, bool callVirtualBase) {
            visit((Columbus.Csharp.Asg.Nodes.Structure.MemberDeclarationSyntax)node, false);
        }

        /// <summary>
        /// Abstract end visitor, which calls the end visitor of the base class (Columbus.Csharp.Asg.Nodes.Structure.MemberDeclarationSyntax) of the Columbus.Csharp.Asg.Nodes.Structure.IncompleteMemberSyntax node.
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public override void visitEnd(Columbus.Csharp.Asg.Nodes.Structure.IncompleteMemberSyntax node, bool callVirtualBase) {
            visitEnd((Columbus.Csharp.Asg.Nodes.Structure.MemberDeclarationSyntax)node, false);
        }

        /// <summary>
        /// Abstract visitor, which calls the visitor of the base class (Columbus.Csharp.Asg.Nodes.Structure.BasePropertyDeclarationSyntax) of the Columbus.Csharp.Asg.Nodes.Structure.IndexerDeclarationSyntax node.
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public override void visit(Columbus.Csharp.Asg.Nodes.Structure.IndexerDeclarationSyntax node, bool callVirtualBase) {
            visit((Columbus.Csharp.Asg.Nodes.Structure.BasePropertyDeclarationSyntax)node, false);
        }

        /// <summary>
        /// Abstract end visitor, which calls the end visitor of the base class (Columbus.Csharp.Asg.Nodes.Structure.BasePropertyDeclarationSyntax) of the Columbus.Csharp.Asg.Nodes.Structure.IndexerDeclarationSyntax node.
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public override void visitEnd(Columbus.Csharp.Asg.Nodes.Structure.IndexerDeclarationSyntax node, bool callVirtualBase) {
            visitEnd((Columbus.Csharp.Asg.Nodes.Structure.BasePropertyDeclarationSyntax)node, false);
        }

        /// <summary>
        /// Abstract visitor, which calls the visitor of the base class (Columbus.Csharp.Asg.Nodes.Structure.MemberCrefSyntax) of the Columbus.Csharp.Asg.Nodes.Structure.IndexerMemberCrefSyntax node.
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public override void visit(Columbus.Csharp.Asg.Nodes.Structure.IndexerMemberCrefSyntax node, bool callVirtualBase) {
            visit((Columbus.Csharp.Asg.Nodes.Structure.MemberCrefSyntax)node, false);
        }

        /// <summary>
        /// Abstract end visitor, which calls the end visitor of the base class (Columbus.Csharp.Asg.Nodes.Structure.MemberCrefSyntax) of the Columbus.Csharp.Asg.Nodes.Structure.IndexerMemberCrefSyntax node.
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public override void visitEnd(Columbus.Csharp.Asg.Nodes.Structure.IndexerMemberCrefSyntax node, bool callVirtualBase) {
            visitEnd((Columbus.Csharp.Asg.Nodes.Structure.MemberCrefSyntax)node, false);
        }

        /// <summary>
        /// Abstract visitor, which calls the visitor of the base class (Columbus.Csharp.Asg.Nodes.Structure.TypeDeclarationSyntax) of the Columbus.Csharp.Asg.Nodes.Structure.InterfaceDeclarationSyntax node.
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public override void visit(Columbus.Csharp.Asg.Nodes.Structure.InterfaceDeclarationSyntax node, bool callVirtualBase) {
            visit((Columbus.Csharp.Asg.Nodes.Structure.TypeDeclarationSyntax)node, false);
        }

        /// <summary>
        /// Abstract end visitor, which calls the end visitor of the base class (Columbus.Csharp.Asg.Nodes.Structure.TypeDeclarationSyntax) of the Columbus.Csharp.Asg.Nodes.Structure.InterfaceDeclarationSyntax node.
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public override void visitEnd(Columbus.Csharp.Asg.Nodes.Structure.InterfaceDeclarationSyntax node, bool callVirtualBase) {
            visitEnd((Columbus.Csharp.Asg.Nodes.Structure.TypeDeclarationSyntax)node, false);
        }

        /// <summary>
        /// Abstract visitor, which calls the visitor of the base class (Columbus.Csharp.Asg.Nodes.Base.Positioned) of the Columbus.Csharp.Asg.Nodes.Structure.InterpolatedStringContentSyntax node.
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public virtual void visit(Columbus.Csharp.Asg.Nodes.Structure.InterpolatedStringContentSyntax node, bool callVirtualBase) {
            visit((Columbus.Csharp.Asg.Nodes.Base.Positioned)node, false);
        }

        /// <summary>
        /// Abstract end visitor, which calls the end visitor of the base class (Columbus.Csharp.Asg.Nodes.Base.Positioned) of the Columbus.Csharp.Asg.Nodes.Structure.InterpolatedStringContentSyntax node.
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public virtual void visitEnd(Columbus.Csharp.Asg.Nodes.Structure.InterpolatedStringContentSyntax node, bool callVirtualBase) {
            visitEnd((Columbus.Csharp.Asg.Nodes.Base.Positioned)node, false);
        }

        /// <summary>
        /// Abstract visitor, which calls the visitor of the base class (Columbus.Csharp.Asg.Nodes.Structure.InterpolatedStringContentSyntax) of the Columbus.Csharp.Asg.Nodes.Structure.InterpolatedStringTextSyntax node.
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public override void visit(Columbus.Csharp.Asg.Nodes.Structure.InterpolatedStringTextSyntax node, bool callVirtualBase) {
            visit((Columbus.Csharp.Asg.Nodes.Structure.InterpolatedStringContentSyntax)node, false);
        }

        /// <summary>
        /// Abstract end visitor, which calls the end visitor of the base class (Columbus.Csharp.Asg.Nodes.Structure.InterpolatedStringContentSyntax) of the Columbus.Csharp.Asg.Nodes.Structure.InterpolatedStringTextSyntax node.
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public override void visitEnd(Columbus.Csharp.Asg.Nodes.Structure.InterpolatedStringTextSyntax node, bool callVirtualBase) {
            visitEnd((Columbus.Csharp.Asg.Nodes.Structure.InterpolatedStringContentSyntax)node, false);
        }

        /// <summary>
        /// Abstract visitor, which calls the visitor of the base class (Columbus.Csharp.Asg.Nodes.Base.Positioned) of the Columbus.Csharp.Asg.Nodes.Structure.InterpolationAlignmentClauseSyntax node.
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public override void visit(Columbus.Csharp.Asg.Nodes.Structure.InterpolationAlignmentClauseSyntax node, bool callVirtualBase) {
            visit((Columbus.Csharp.Asg.Nodes.Base.Positioned)node, false);
        }

        /// <summary>
        /// Abstract end visitor, which calls the end visitor of the base class (Columbus.Csharp.Asg.Nodes.Base.Positioned) of the Columbus.Csharp.Asg.Nodes.Structure.InterpolationAlignmentClauseSyntax node.
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public override void visitEnd(Columbus.Csharp.Asg.Nodes.Structure.InterpolationAlignmentClauseSyntax node, bool callVirtualBase) {
            visitEnd((Columbus.Csharp.Asg.Nodes.Base.Positioned)node, false);
        }

        /// <summary>
        /// Abstract visitor, which calls the visitor of the base class (Columbus.Csharp.Asg.Nodes.Base.Positioned) of the Columbus.Csharp.Asg.Nodes.Structure.InterpolationFormatClauseSyntax node.
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public override void visit(Columbus.Csharp.Asg.Nodes.Structure.InterpolationFormatClauseSyntax node, bool callVirtualBase) {
            visit((Columbus.Csharp.Asg.Nodes.Base.Positioned)node, false);
        }

        /// <summary>
        /// Abstract end visitor, which calls the end visitor of the base class (Columbus.Csharp.Asg.Nodes.Base.Positioned) of the Columbus.Csharp.Asg.Nodes.Structure.InterpolationFormatClauseSyntax node.
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public override void visitEnd(Columbus.Csharp.Asg.Nodes.Structure.InterpolationFormatClauseSyntax node, bool callVirtualBase) {
            visitEnd((Columbus.Csharp.Asg.Nodes.Base.Positioned)node, false);
        }

        /// <summary>
        /// Abstract visitor, which calls the visitor of the base class (Columbus.Csharp.Asg.Nodes.Structure.InterpolatedStringContentSyntax) of the Columbus.Csharp.Asg.Nodes.Structure.InterpolationSyntax node.
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public override void visit(Columbus.Csharp.Asg.Nodes.Structure.InterpolationSyntax node, bool callVirtualBase) {
            visit((Columbus.Csharp.Asg.Nodes.Structure.InterpolatedStringContentSyntax)node, false);
        }

        /// <summary>
        /// Abstract end visitor, which calls the end visitor of the base class (Columbus.Csharp.Asg.Nodes.Structure.InterpolatedStringContentSyntax) of the Columbus.Csharp.Asg.Nodes.Structure.InterpolationSyntax node.
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public override void visitEnd(Columbus.Csharp.Asg.Nodes.Structure.InterpolationSyntax node, bool callVirtualBase) {
            visitEnd((Columbus.Csharp.Asg.Nodes.Structure.InterpolatedStringContentSyntax)node, false);
        }

        /// <summary>
        /// Abstract visitor, which calls the visitor of the base class (Columbus.Csharp.Asg.Nodes.Structure.QueryClauseSyntax) of the Columbus.Csharp.Asg.Nodes.Structure.JoinClauseSyntax node.
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public override void visit(Columbus.Csharp.Asg.Nodes.Structure.JoinClauseSyntax node, bool callVirtualBase) {
            visit((Columbus.Csharp.Asg.Nodes.Structure.QueryClauseSyntax)node, false);
        }

        /// <summary>
        /// Abstract end visitor, which calls the end visitor of the base class (Columbus.Csharp.Asg.Nodes.Structure.QueryClauseSyntax) of the Columbus.Csharp.Asg.Nodes.Structure.JoinClauseSyntax node.
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public override void visitEnd(Columbus.Csharp.Asg.Nodes.Structure.JoinClauseSyntax node, bool callVirtualBase) {
            visitEnd((Columbus.Csharp.Asg.Nodes.Structure.QueryClauseSyntax)node, false);
        }

        /// <summary>
        /// Abstract visitor, which calls the visitor of the base class (Columbus.Csharp.Asg.Nodes.Base.Positioned) of the Columbus.Csharp.Asg.Nodes.Structure.JoinIntoClauseSyntax node.
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public override void visit(Columbus.Csharp.Asg.Nodes.Structure.JoinIntoClauseSyntax node, bool callVirtualBase) {
            visit((Columbus.Csharp.Asg.Nodes.Base.Positioned)node, false);
        }

        /// <summary>
        /// Abstract end visitor, which calls the end visitor of the base class (Columbus.Csharp.Asg.Nodes.Base.Positioned) of the Columbus.Csharp.Asg.Nodes.Structure.JoinIntoClauseSyntax node.
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public override void visitEnd(Columbus.Csharp.Asg.Nodes.Structure.JoinIntoClauseSyntax node, bool callVirtualBase) {
            visitEnd((Columbus.Csharp.Asg.Nodes.Base.Positioned)node, false);
        }

        /// <summary>
        /// Abstract visitor, which calls the visitor of the base class (Columbus.Csharp.Asg.Nodes.Structure.QueryClauseSyntax) of the Columbus.Csharp.Asg.Nodes.Structure.LetClauseSyntax node.
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public override void visit(Columbus.Csharp.Asg.Nodes.Structure.LetClauseSyntax node, bool callVirtualBase) {
            visit((Columbus.Csharp.Asg.Nodes.Structure.QueryClauseSyntax)node, false);
        }

        /// <summary>
        /// Abstract end visitor, which calls the end visitor of the base class (Columbus.Csharp.Asg.Nodes.Structure.QueryClauseSyntax) of the Columbus.Csharp.Asg.Nodes.Structure.LetClauseSyntax node.
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public override void visitEnd(Columbus.Csharp.Asg.Nodes.Structure.LetClauseSyntax node, bool callVirtualBase) {
            visitEnd((Columbus.Csharp.Asg.Nodes.Structure.QueryClauseSyntax)node, false);
        }

        /// <summary>
        /// Abstract visitor, which calls the visitor of the base class (Columbus.Csharp.Asg.Nodes.Structure.CrefSyntax) of the Columbus.Csharp.Asg.Nodes.Structure.MemberCrefSyntax node.
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public virtual void visit(Columbus.Csharp.Asg.Nodes.Structure.MemberCrefSyntax node, bool callVirtualBase) {
            visit((Columbus.Csharp.Asg.Nodes.Structure.CrefSyntax)node, false);
        }

        /// <summary>
        /// Abstract end visitor, which calls the end visitor of the base class (Columbus.Csharp.Asg.Nodes.Structure.CrefSyntax) of the Columbus.Csharp.Asg.Nodes.Structure.MemberCrefSyntax node.
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public virtual void visitEnd(Columbus.Csharp.Asg.Nodes.Structure.MemberCrefSyntax node, bool callVirtualBase) {
            visitEnd((Columbus.Csharp.Asg.Nodes.Structure.CrefSyntax)node, false);
        }

        /// <summary>
        /// Abstract visitor, which calls the visitor of the base class (Columbus.Csharp.Asg.Nodes.Base.Positioned) of the Columbus.Csharp.Asg.Nodes.Structure.MemberDeclarationSyntax node.
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public virtual void visit(Columbus.Csharp.Asg.Nodes.Structure.MemberDeclarationSyntax node, bool callVirtualBase) {
            visit((Columbus.Csharp.Asg.Nodes.Base.Positioned)node, false);
        }

        /// <summary>
        /// Abstract end visitor, which calls the end visitor of the base class (Columbus.Csharp.Asg.Nodes.Base.Positioned) of the Columbus.Csharp.Asg.Nodes.Structure.MemberDeclarationSyntax node.
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public virtual void visitEnd(Columbus.Csharp.Asg.Nodes.Structure.MemberDeclarationSyntax node, bool callVirtualBase) {
            visitEnd((Columbus.Csharp.Asg.Nodes.Base.Positioned)node, false);
        }

        /// <summary>
        /// Abstract visitor, which calls the visitor of the base class (Columbus.Csharp.Asg.Nodes.Structure.BaseMethodDeclarationSyntax) of the Columbus.Csharp.Asg.Nodes.Structure.MethodDeclarationSyntax node.
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public override void visit(Columbus.Csharp.Asg.Nodes.Structure.MethodDeclarationSyntax node, bool callVirtualBase) {
            visit((Columbus.Csharp.Asg.Nodes.Structure.BaseMethodDeclarationSyntax)node, false);
        }

        /// <summary>
        /// Abstract end visitor, which calls the end visitor of the base class (Columbus.Csharp.Asg.Nodes.Structure.BaseMethodDeclarationSyntax) of the Columbus.Csharp.Asg.Nodes.Structure.MethodDeclarationSyntax node.
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public override void visitEnd(Columbus.Csharp.Asg.Nodes.Structure.MethodDeclarationSyntax node, bool callVirtualBase) {
            visitEnd((Columbus.Csharp.Asg.Nodes.Structure.BaseMethodDeclarationSyntax)node, false);
        }

        /// <summary>
        /// Abstract visitor, which calls the visitor of the base class (Columbus.Csharp.Asg.Nodes.Base.Positioned) of the Columbus.Csharp.Asg.Nodes.Structure.NameColonSyntax node.
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public override void visit(Columbus.Csharp.Asg.Nodes.Structure.NameColonSyntax node, bool callVirtualBase) {
            visit((Columbus.Csharp.Asg.Nodes.Base.Positioned)node, false);
        }

        /// <summary>
        /// Abstract end visitor, which calls the end visitor of the base class (Columbus.Csharp.Asg.Nodes.Base.Positioned) of the Columbus.Csharp.Asg.Nodes.Structure.NameColonSyntax node.
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public override void visitEnd(Columbus.Csharp.Asg.Nodes.Structure.NameColonSyntax node, bool callVirtualBase) {
            visitEnd((Columbus.Csharp.Asg.Nodes.Base.Positioned)node, false);
        }

        /// <summary>
        /// Abstract visitor, which calls the visitor of the base class (Columbus.Csharp.Asg.Nodes.Base.Positioned) of the Columbus.Csharp.Asg.Nodes.Structure.NameEqualsSyntax node.
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public override void visit(Columbus.Csharp.Asg.Nodes.Structure.NameEqualsSyntax node, bool callVirtualBase) {
            visit((Columbus.Csharp.Asg.Nodes.Base.Positioned)node, false);
        }

        /// <summary>
        /// Abstract end visitor, which calls the end visitor of the base class (Columbus.Csharp.Asg.Nodes.Base.Positioned) of the Columbus.Csharp.Asg.Nodes.Structure.NameEqualsSyntax node.
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public override void visitEnd(Columbus.Csharp.Asg.Nodes.Structure.NameEqualsSyntax node, bool callVirtualBase) {
            visitEnd((Columbus.Csharp.Asg.Nodes.Base.Positioned)node, false);
        }

        /// <summary>
        /// Abstract visitor, which calls the visitor of the base class (Columbus.Csharp.Asg.Nodes.Structure.MemberCrefSyntax) of the Columbus.Csharp.Asg.Nodes.Structure.NameMemberCrefSyntax node.
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public override void visit(Columbus.Csharp.Asg.Nodes.Structure.NameMemberCrefSyntax node, bool callVirtualBase) {
            visit((Columbus.Csharp.Asg.Nodes.Structure.MemberCrefSyntax)node, false);
        }

        /// <summary>
        /// Abstract end visitor, which calls the end visitor of the base class (Columbus.Csharp.Asg.Nodes.Structure.MemberCrefSyntax) of the Columbus.Csharp.Asg.Nodes.Structure.NameMemberCrefSyntax node.
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public override void visitEnd(Columbus.Csharp.Asg.Nodes.Structure.NameMemberCrefSyntax node, bool callVirtualBase) {
            visitEnd((Columbus.Csharp.Asg.Nodes.Structure.MemberCrefSyntax)node, false);
        }

        /// <summary>
        /// Abstract visitor, which calls the visitor of the base class (Columbus.Csharp.Asg.Nodes.Structure.MemberDeclarationSyntax) of the Columbus.Csharp.Asg.Nodes.Structure.NamespaceDeclarationSyntax node.
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public override void visit(Columbus.Csharp.Asg.Nodes.Structure.NamespaceDeclarationSyntax node, bool callVirtualBase) {
            visit((Columbus.Csharp.Asg.Nodes.Structure.MemberDeclarationSyntax)node, false);
        }

        /// <summary>
        /// Abstract end visitor, which calls the end visitor of the base class (Columbus.Csharp.Asg.Nodes.Structure.MemberDeclarationSyntax) of the Columbus.Csharp.Asg.Nodes.Structure.NamespaceDeclarationSyntax node.
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public override void visitEnd(Columbus.Csharp.Asg.Nodes.Structure.NamespaceDeclarationSyntax node, bool callVirtualBase) {
            visitEnd((Columbus.Csharp.Asg.Nodes.Structure.MemberDeclarationSyntax)node, false);
        }

        /// <summary>
        /// Abstract visitor, which calls the visitor of the base class (Columbus.Csharp.Asg.Nodes.Structure.BaseMethodDeclarationSyntax) of the Columbus.Csharp.Asg.Nodes.Structure.OperatorDeclarationSyntax node.
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public override void visit(Columbus.Csharp.Asg.Nodes.Structure.OperatorDeclarationSyntax node, bool callVirtualBase) {
            visit((Columbus.Csharp.Asg.Nodes.Structure.BaseMethodDeclarationSyntax)node, false);
        }

        /// <summary>
        /// Abstract end visitor, which calls the end visitor of the base class (Columbus.Csharp.Asg.Nodes.Structure.BaseMethodDeclarationSyntax) of the Columbus.Csharp.Asg.Nodes.Structure.OperatorDeclarationSyntax node.
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public override void visitEnd(Columbus.Csharp.Asg.Nodes.Structure.OperatorDeclarationSyntax node, bool callVirtualBase) {
            visitEnd((Columbus.Csharp.Asg.Nodes.Structure.BaseMethodDeclarationSyntax)node, false);
        }

        /// <summary>
        /// Abstract visitor, which calls the visitor of the base class (Columbus.Csharp.Asg.Nodes.Structure.MemberCrefSyntax) of the Columbus.Csharp.Asg.Nodes.Structure.OperatorMemberCrefSyntax node.
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public override void visit(Columbus.Csharp.Asg.Nodes.Structure.OperatorMemberCrefSyntax node, bool callVirtualBase) {
            visit((Columbus.Csharp.Asg.Nodes.Structure.MemberCrefSyntax)node, false);
        }

        /// <summary>
        /// Abstract end visitor, which calls the end visitor of the base class (Columbus.Csharp.Asg.Nodes.Structure.MemberCrefSyntax) of the Columbus.Csharp.Asg.Nodes.Structure.OperatorMemberCrefSyntax node.
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public override void visitEnd(Columbus.Csharp.Asg.Nodes.Structure.OperatorMemberCrefSyntax node, bool callVirtualBase) {
            visitEnd((Columbus.Csharp.Asg.Nodes.Structure.MemberCrefSyntax)node, false);
        }

        /// <summary>
        /// Abstract visitor, which calls the visitor of the base class (Columbus.Csharp.Asg.Nodes.Structure.QueryClauseSyntax) of the Columbus.Csharp.Asg.Nodes.Structure.OrderByClauseSyntax node.
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public override void visit(Columbus.Csharp.Asg.Nodes.Structure.OrderByClauseSyntax node, bool callVirtualBase) {
            visit((Columbus.Csharp.Asg.Nodes.Structure.QueryClauseSyntax)node, false);
        }

        /// <summary>
        /// Abstract end visitor, which calls the end visitor of the base class (Columbus.Csharp.Asg.Nodes.Structure.QueryClauseSyntax) of the Columbus.Csharp.Asg.Nodes.Structure.OrderByClauseSyntax node.
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public override void visitEnd(Columbus.Csharp.Asg.Nodes.Structure.OrderByClauseSyntax node, bool callVirtualBase) {
            visitEnd((Columbus.Csharp.Asg.Nodes.Structure.QueryClauseSyntax)node, false);
        }

        /// <summary>
        /// Abstract visitor, which calls the visitor of the base class (Columbus.Csharp.Asg.Nodes.Base.Positioned) of the Columbus.Csharp.Asg.Nodes.Structure.OrderingSyntax node.
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public override void visit(Columbus.Csharp.Asg.Nodes.Structure.OrderingSyntax node, bool callVirtualBase) {
            visit((Columbus.Csharp.Asg.Nodes.Base.Positioned)node, false);
        }

        /// <summary>
        /// Abstract end visitor, which calls the end visitor of the base class (Columbus.Csharp.Asg.Nodes.Base.Positioned) of the Columbus.Csharp.Asg.Nodes.Structure.OrderingSyntax node.
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public override void visitEnd(Columbus.Csharp.Asg.Nodes.Structure.OrderingSyntax node, bool callVirtualBase) {
            visitEnd((Columbus.Csharp.Asg.Nodes.Base.Positioned)node, false);
        }

        /// <summary>
        /// Abstract visitor, which calls the visitor of the base class (Columbus.Csharp.Asg.Nodes.Structure.BaseParameterListSyntax) of the Columbus.Csharp.Asg.Nodes.Structure.ParameterListSyntax node.
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public override void visit(Columbus.Csharp.Asg.Nodes.Structure.ParameterListSyntax node, bool callVirtualBase) {
            visit((Columbus.Csharp.Asg.Nodes.Structure.BaseParameterListSyntax)node, false);
        }

        /// <summary>
        /// Abstract end visitor, which calls the end visitor of the base class (Columbus.Csharp.Asg.Nodes.Structure.BaseParameterListSyntax) of the Columbus.Csharp.Asg.Nodes.Structure.ParameterListSyntax node.
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public override void visitEnd(Columbus.Csharp.Asg.Nodes.Structure.ParameterListSyntax node, bool callVirtualBase) {
            visitEnd((Columbus.Csharp.Asg.Nodes.Structure.BaseParameterListSyntax)node, false);
        }

        /// <summary>
        /// Abstract visitor, which calls the visitor of the base class (Columbus.Csharp.Asg.Nodes.Base.Positioned) of the Columbus.Csharp.Asg.Nodes.Structure.ParameterSyntax node.
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public override void visit(Columbus.Csharp.Asg.Nodes.Structure.ParameterSyntax node, bool callVirtualBase) {
            visit((Columbus.Csharp.Asg.Nodes.Base.Positioned)node, false);
        }

        /// <summary>
        /// Abstract end visitor, which calls the end visitor of the base class (Columbus.Csharp.Asg.Nodes.Base.Positioned) of the Columbus.Csharp.Asg.Nodes.Structure.ParameterSyntax node.
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public override void visitEnd(Columbus.Csharp.Asg.Nodes.Structure.ParameterSyntax node, bool callVirtualBase) {
            visitEnd((Columbus.Csharp.Asg.Nodes.Base.Positioned)node, false);
        }

        /// <summary>
        /// Abstract visitor, which calls the visitor of the base class (Columbus.Csharp.Asg.Nodes.Structure.VariableDesignationSyntax) of the Columbus.Csharp.Asg.Nodes.Structure.ParenthesizedVariableDesignationSyntax node.
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public override void visit(Columbus.Csharp.Asg.Nodes.Structure.ParenthesizedVariableDesignationSyntax node, bool callVirtualBase) {
            visit((Columbus.Csharp.Asg.Nodes.Structure.VariableDesignationSyntax)node, false);
        }

        /// <summary>
        /// Abstract end visitor, which calls the end visitor of the base class (Columbus.Csharp.Asg.Nodes.Structure.VariableDesignationSyntax) of the Columbus.Csharp.Asg.Nodes.Structure.ParenthesizedVariableDesignationSyntax node.
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public override void visitEnd(Columbus.Csharp.Asg.Nodes.Structure.ParenthesizedVariableDesignationSyntax node, bool callVirtualBase) {
            visitEnd((Columbus.Csharp.Asg.Nodes.Structure.VariableDesignationSyntax)node, false);
        }

        /// <summary>
        /// Abstract visitor, which calls the visitor of the base class (Columbus.Csharp.Asg.Nodes.Base.Positioned) of the Columbus.Csharp.Asg.Nodes.Structure.PatternSyntax node.
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public virtual void visit(Columbus.Csharp.Asg.Nodes.Structure.PatternSyntax node, bool callVirtualBase) {
            visit((Columbus.Csharp.Asg.Nodes.Base.Positioned)node, false);
        }

        /// <summary>
        /// Abstract end visitor, which calls the end visitor of the base class (Columbus.Csharp.Asg.Nodes.Base.Positioned) of the Columbus.Csharp.Asg.Nodes.Structure.PatternSyntax node.
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public virtual void visitEnd(Columbus.Csharp.Asg.Nodes.Structure.PatternSyntax node, bool callVirtualBase) {
            visitEnd((Columbus.Csharp.Asg.Nodes.Base.Positioned)node, false);
        }

        /// <summary>
        /// Abstract visitor, which calls the visitor of the base class (Columbus.Csharp.Asg.Nodes.Base.Positioned) of the Columbus.Csharp.Asg.Nodes.Structure.PositionalPatternClauseSyntax node.
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public override void visit(Columbus.Csharp.Asg.Nodes.Structure.PositionalPatternClauseSyntax node, bool callVirtualBase) {
            visit((Columbus.Csharp.Asg.Nodes.Base.Positioned)node, false);
        }

        /// <summary>
        /// Abstract end visitor, which calls the end visitor of the base class (Columbus.Csharp.Asg.Nodes.Base.Positioned) of the Columbus.Csharp.Asg.Nodes.Structure.PositionalPatternClauseSyntax node.
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public override void visitEnd(Columbus.Csharp.Asg.Nodes.Structure.PositionalPatternClauseSyntax node, bool callVirtualBase) {
            visitEnd((Columbus.Csharp.Asg.Nodes.Base.Positioned)node, false);
        }

        /// <summary>
        /// Abstract visitor, which calls the visitor of the base class (Columbus.Csharp.Asg.Nodes.Structure.BasePropertyDeclarationSyntax) of the Columbus.Csharp.Asg.Nodes.Structure.PropertyDeclarationSyntax node.
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public override void visit(Columbus.Csharp.Asg.Nodes.Structure.PropertyDeclarationSyntax node, bool callVirtualBase) {
            visit((Columbus.Csharp.Asg.Nodes.Structure.BasePropertyDeclarationSyntax)node, false);
        }

        /// <summary>
        /// Abstract end visitor, which calls the end visitor of the base class (Columbus.Csharp.Asg.Nodes.Structure.BasePropertyDeclarationSyntax) of the Columbus.Csharp.Asg.Nodes.Structure.PropertyDeclarationSyntax node.
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public override void visitEnd(Columbus.Csharp.Asg.Nodes.Structure.PropertyDeclarationSyntax node, bool callVirtualBase) {
            visitEnd((Columbus.Csharp.Asg.Nodes.Structure.BasePropertyDeclarationSyntax)node, false);
        }

        /// <summary>
        /// Abstract visitor, which calls the visitor of the base class (Columbus.Csharp.Asg.Nodes.Base.Positioned) of the Columbus.Csharp.Asg.Nodes.Structure.PropertyPatternClauseSyntax node.
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public override void visit(Columbus.Csharp.Asg.Nodes.Structure.PropertyPatternClauseSyntax node, bool callVirtualBase) {
            visit((Columbus.Csharp.Asg.Nodes.Base.Positioned)node, false);
        }

        /// <summary>
        /// Abstract end visitor, which calls the end visitor of the base class (Columbus.Csharp.Asg.Nodes.Base.Positioned) of the Columbus.Csharp.Asg.Nodes.Structure.PropertyPatternClauseSyntax node.
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public override void visitEnd(Columbus.Csharp.Asg.Nodes.Structure.PropertyPatternClauseSyntax node, bool callVirtualBase) {
            visitEnd((Columbus.Csharp.Asg.Nodes.Base.Positioned)node, false);
        }

        /// <summary>
        /// Abstract visitor, which calls the visitor of the base class (Columbus.Csharp.Asg.Nodes.Structure.CrefSyntax) of the Columbus.Csharp.Asg.Nodes.Structure.QualifiedCrefSyntax node.
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public override void visit(Columbus.Csharp.Asg.Nodes.Structure.QualifiedCrefSyntax node, bool callVirtualBase) {
            visit((Columbus.Csharp.Asg.Nodes.Structure.CrefSyntax)node, false);
        }

        /// <summary>
        /// Abstract end visitor, which calls the end visitor of the base class (Columbus.Csharp.Asg.Nodes.Structure.CrefSyntax) of the Columbus.Csharp.Asg.Nodes.Structure.QualifiedCrefSyntax node.
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public override void visitEnd(Columbus.Csharp.Asg.Nodes.Structure.QualifiedCrefSyntax node, bool callVirtualBase) {
            visitEnd((Columbus.Csharp.Asg.Nodes.Structure.CrefSyntax)node, false);
        }

        /// <summary>
        /// Abstract visitor, which calls the visitor of the base class (Columbus.Csharp.Asg.Nodes.Base.Positioned) of the Columbus.Csharp.Asg.Nodes.Structure.QueryBodySyntax node.
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public override void visit(Columbus.Csharp.Asg.Nodes.Structure.QueryBodySyntax node, bool callVirtualBase) {
            visit((Columbus.Csharp.Asg.Nodes.Base.Positioned)node, false);
        }

        /// <summary>
        /// Abstract end visitor, which calls the end visitor of the base class (Columbus.Csharp.Asg.Nodes.Base.Positioned) of the Columbus.Csharp.Asg.Nodes.Structure.QueryBodySyntax node.
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public override void visitEnd(Columbus.Csharp.Asg.Nodes.Structure.QueryBodySyntax node, bool callVirtualBase) {
            visitEnd((Columbus.Csharp.Asg.Nodes.Base.Positioned)node, false);
        }

        /// <summary>
        /// Abstract visitor, which calls the visitor of the base class (Columbus.Csharp.Asg.Nodes.Base.Positioned) of the Columbus.Csharp.Asg.Nodes.Structure.QueryClauseSyntax node.
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public virtual void visit(Columbus.Csharp.Asg.Nodes.Structure.QueryClauseSyntax node, bool callVirtualBase) {
            visit((Columbus.Csharp.Asg.Nodes.Base.Positioned)node, false);
        }

        /// <summary>
        /// Abstract end visitor, which calls the end visitor of the base class (Columbus.Csharp.Asg.Nodes.Base.Positioned) of the Columbus.Csharp.Asg.Nodes.Structure.QueryClauseSyntax node.
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public virtual void visitEnd(Columbus.Csharp.Asg.Nodes.Structure.QueryClauseSyntax node, bool callVirtualBase) {
            visitEnd((Columbus.Csharp.Asg.Nodes.Base.Positioned)node, false);
        }

        /// <summary>
        /// Abstract visitor, which calls the visitor of the base class (Columbus.Csharp.Asg.Nodes.Base.Positioned) of the Columbus.Csharp.Asg.Nodes.Structure.QueryContinuationSyntax node.
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public override void visit(Columbus.Csharp.Asg.Nodes.Structure.QueryContinuationSyntax node, bool callVirtualBase) {
            visit((Columbus.Csharp.Asg.Nodes.Base.Positioned)node, false);
        }

        /// <summary>
        /// Abstract end visitor, which calls the end visitor of the base class (Columbus.Csharp.Asg.Nodes.Base.Positioned) of the Columbus.Csharp.Asg.Nodes.Structure.QueryContinuationSyntax node.
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public override void visitEnd(Columbus.Csharp.Asg.Nodes.Structure.QueryContinuationSyntax node, bool callVirtualBase) {
            visitEnd((Columbus.Csharp.Asg.Nodes.Base.Positioned)node, false);
        }

        /// <summary>
        /// Abstract visitor, which calls the visitor of the base class (Columbus.Csharp.Asg.Nodes.Structure.PatternSyntax) of the Columbus.Csharp.Asg.Nodes.Structure.RecursivePatternSyntax node.
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public override void visit(Columbus.Csharp.Asg.Nodes.Structure.RecursivePatternSyntax node, bool callVirtualBase) {
            visit((Columbus.Csharp.Asg.Nodes.Structure.PatternSyntax)node, false);
        }

        /// <summary>
        /// Abstract end visitor, which calls the end visitor of the base class (Columbus.Csharp.Asg.Nodes.Structure.PatternSyntax) of the Columbus.Csharp.Asg.Nodes.Structure.RecursivePatternSyntax node.
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public override void visitEnd(Columbus.Csharp.Asg.Nodes.Structure.RecursivePatternSyntax node, bool callVirtualBase) {
            visitEnd((Columbus.Csharp.Asg.Nodes.Structure.PatternSyntax)node, false);
        }

        /// <summary>
        /// Abstract visitor, which calls the visitor of the base class (Columbus.Csharp.Asg.Nodes.Structure.SelectOrGroupClauseSyntax) of the Columbus.Csharp.Asg.Nodes.Structure.SelectClauseSyntax node.
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public override void visit(Columbus.Csharp.Asg.Nodes.Structure.SelectClauseSyntax node, bool callVirtualBase) {
            visit((Columbus.Csharp.Asg.Nodes.Structure.SelectOrGroupClauseSyntax)node, false);
        }

        /// <summary>
        /// Abstract end visitor, which calls the end visitor of the base class (Columbus.Csharp.Asg.Nodes.Structure.SelectOrGroupClauseSyntax) of the Columbus.Csharp.Asg.Nodes.Structure.SelectClauseSyntax node.
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public override void visitEnd(Columbus.Csharp.Asg.Nodes.Structure.SelectClauseSyntax node, bool callVirtualBase) {
            visitEnd((Columbus.Csharp.Asg.Nodes.Structure.SelectOrGroupClauseSyntax)node, false);
        }

        /// <summary>
        /// Abstract visitor, which calls the visitor of the base class (Columbus.Csharp.Asg.Nodes.Base.Positioned) of the Columbus.Csharp.Asg.Nodes.Structure.SelectOrGroupClauseSyntax node.
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public virtual void visit(Columbus.Csharp.Asg.Nodes.Structure.SelectOrGroupClauseSyntax node, bool callVirtualBase) {
            visit((Columbus.Csharp.Asg.Nodes.Base.Positioned)node, false);
        }

        /// <summary>
        /// Abstract end visitor, which calls the end visitor of the base class (Columbus.Csharp.Asg.Nodes.Base.Positioned) of the Columbus.Csharp.Asg.Nodes.Structure.SelectOrGroupClauseSyntax node.
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public virtual void visitEnd(Columbus.Csharp.Asg.Nodes.Structure.SelectOrGroupClauseSyntax node, bool callVirtualBase) {
            visitEnd((Columbus.Csharp.Asg.Nodes.Base.Positioned)node, false);
        }

        /// <summary>
        /// Abstract visitor, which calls the visitor of the base class (Columbus.Csharp.Asg.Nodes.Structure.BaseTypeSyntax) of the Columbus.Csharp.Asg.Nodes.Structure.SimpleBaseTypeSyntax node.
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public override void visit(Columbus.Csharp.Asg.Nodes.Structure.SimpleBaseTypeSyntax node, bool callVirtualBase) {
            visit((Columbus.Csharp.Asg.Nodes.Structure.BaseTypeSyntax)node, false);
        }

        /// <summary>
        /// Abstract end visitor, which calls the end visitor of the base class (Columbus.Csharp.Asg.Nodes.Structure.BaseTypeSyntax) of the Columbus.Csharp.Asg.Nodes.Structure.SimpleBaseTypeSyntax node.
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public override void visitEnd(Columbus.Csharp.Asg.Nodes.Structure.SimpleBaseTypeSyntax node, bool callVirtualBase) {
            visitEnd((Columbus.Csharp.Asg.Nodes.Structure.BaseTypeSyntax)node, false);
        }

        /// <summary>
        /// Abstract visitor, which calls the visitor of the base class (Columbus.Csharp.Asg.Nodes.Structure.VariableDesignationSyntax) of the Columbus.Csharp.Asg.Nodes.Structure.SingleVariableDesignationSyntax node.
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public override void visit(Columbus.Csharp.Asg.Nodes.Structure.SingleVariableDesignationSyntax node, bool callVirtualBase) {
            visit((Columbus.Csharp.Asg.Nodes.Structure.VariableDesignationSyntax)node, false);
        }

        /// <summary>
        /// Abstract end visitor, which calls the end visitor of the base class (Columbus.Csharp.Asg.Nodes.Structure.VariableDesignationSyntax) of the Columbus.Csharp.Asg.Nodes.Structure.SingleVariableDesignationSyntax node.
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public override void visitEnd(Columbus.Csharp.Asg.Nodes.Structure.SingleVariableDesignationSyntax node, bool callVirtualBase) {
            visitEnd((Columbus.Csharp.Asg.Nodes.Structure.VariableDesignationSyntax)node, false);
        }

        /// <summary>
        /// Abstract visitor, which calls the visitor of the base class (Columbus.Csharp.Asg.Nodes.Structure.TypeDeclarationSyntax) of the Columbus.Csharp.Asg.Nodes.Structure.StructDeclarationSyntax node.
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public override void visit(Columbus.Csharp.Asg.Nodes.Structure.StructDeclarationSyntax node, bool callVirtualBase) {
            visit((Columbus.Csharp.Asg.Nodes.Structure.TypeDeclarationSyntax)node, false);
        }

        /// <summary>
        /// Abstract end visitor, which calls the end visitor of the base class (Columbus.Csharp.Asg.Nodes.Structure.TypeDeclarationSyntax) of the Columbus.Csharp.Asg.Nodes.Structure.StructDeclarationSyntax node.
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public override void visitEnd(Columbus.Csharp.Asg.Nodes.Structure.StructDeclarationSyntax node, bool callVirtualBase) {
            visitEnd((Columbus.Csharp.Asg.Nodes.Structure.TypeDeclarationSyntax)node, false);
        }

        /// <summary>
        /// Abstract visitor, which calls the visitor of the base class (Columbus.Csharp.Asg.Nodes.Base.Positioned) of the Columbus.Csharp.Asg.Nodes.Structure.SubpatternSyntax node.
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public override void visit(Columbus.Csharp.Asg.Nodes.Structure.SubpatternSyntax node, bool callVirtualBase) {
            visit((Columbus.Csharp.Asg.Nodes.Base.Positioned)node, false);
        }

        /// <summary>
        /// Abstract end visitor, which calls the end visitor of the base class (Columbus.Csharp.Asg.Nodes.Base.Positioned) of the Columbus.Csharp.Asg.Nodes.Structure.SubpatternSyntax node.
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public override void visitEnd(Columbus.Csharp.Asg.Nodes.Structure.SubpatternSyntax node, bool callVirtualBase) {
            visitEnd((Columbus.Csharp.Asg.Nodes.Base.Positioned)node, false);
        }

        /// <summary>
        /// Abstract visitor, which calls the visitor of the base class (Columbus.Csharp.Asg.Nodes.Base.Positioned) of the Columbus.Csharp.Asg.Nodes.Structure.SwitchExpressionArmSyntax node.
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public override void visit(Columbus.Csharp.Asg.Nodes.Structure.SwitchExpressionArmSyntax node, bool callVirtualBase) {
            visit((Columbus.Csharp.Asg.Nodes.Base.Positioned)node, false);
        }

        /// <summary>
        /// Abstract end visitor, which calls the end visitor of the base class (Columbus.Csharp.Asg.Nodes.Base.Positioned) of the Columbus.Csharp.Asg.Nodes.Structure.SwitchExpressionArmSyntax node.
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public override void visitEnd(Columbus.Csharp.Asg.Nodes.Structure.SwitchExpressionArmSyntax node, bool callVirtualBase) {
            visitEnd((Columbus.Csharp.Asg.Nodes.Base.Positioned)node, false);
        }

        /// <summary>
        /// Abstract visitor, which calls the visitor of the base class (Columbus.Csharp.Asg.Nodes.Base.Positioned) of the Columbus.Csharp.Asg.Nodes.Structure.SwitchLabelSyntax node.
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public virtual void visit(Columbus.Csharp.Asg.Nodes.Structure.SwitchLabelSyntax node, bool callVirtualBase) {
            visit((Columbus.Csharp.Asg.Nodes.Base.Positioned)node, false);
        }

        /// <summary>
        /// Abstract end visitor, which calls the end visitor of the base class (Columbus.Csharp.Asg.Nodes.Base.Positioned) of the Columbus.Csharp.Asg.Nodes.Structure.SwitchLabelSyntax node.
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public virtual void visitEnd(Columbus.Csharp.Asg.Nodes.Structure.SwitchLabelSyntax node, bool callVirtualBase) {
            visitEnd((Columbus.Csharp.Asg.Nodes.Base.Positioned)node, false);
        }

        /// <summary>
        /// Abstract visitor, which calls the visitor of the base class (Columbus.Csharp.Asg.Nodes.Base.Positioned) of the Columbus.Csharp.Asg.Nodes.Structure.SwitchSectionSyntax node.
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public override void visit(Columbus.Csharp.Asg.Nodes.Structure.SwitchSectionSyntax node, bool callVirtualBase) {
            visit((Columbus.Csharp.Asg.Nodes.Base.Positioned)node, false);
        }

        /// <summary>
        /// Abstract end visitor, which calls the end visitor of the base class (Columbus.Csharp.Asg.Nodes.Base.Positioned) of the Columbus.Csharp.Asg.Nodes.Structure.SwitchSectionSyntax node.
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public override void visitEnd(Columbus.Csharp.Asg.Nodes.Structure.SwitchSectionSyntax node, bool callVirtualBase) {
            visitEnd((Columbus.Csharp.Asg.Nodes.Base.Positioned)node, false);
        }

        /// <summary>
        /// Abstract visitor, which calls the visitor of the base class (Columbus.Csharp.Asg.Nodes.Base.Positioned) of the Columbus.Csharp.Asg.Nodes.Structure.SyntaxToken node.
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public override void visit(Columbus.Csharp.Asg.Nodes.Structure.SyntaxToken node, bool callVirtualBase) {
            visit((Columbus.Csharp.Asg.Nodes.Base.Positioned)node, false);
        }

        /// <summary>
        /// Abstract end visitor, which calls the end visitor of the base class (Columbus.Csharp.Asg.Nodes.Base.Positioned) of the Columbus.Csharp.Asg.Nodes.Structure.SyntaxToken node.
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public override void visitEnd(Columbus.Csharp.Asg.Nodes.Structure.SyntaxToken node, bool callVirtualBase) {
            visitEnd((Columbus.Csharp.Asg.Nodes.Base.Positioned)node, false);
        }

        /// <summary>
        /// Abstract visitor, which calls the visitor of the base class (Columbus.Csharp.Asg.Nodes.Base.Positioned) of the Columbus.Csharp.Asg.Nodes.Structure.TupleElementSyntax node.
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public override void visit(Columbus.Csharp.Asg.Nodes.Structure.TupleElementSyntax node, bool callVirtualBase) {
            visit((Columbus.Csharp.Asg.Nodes.Base.Positioned)node, false);
        }

        /// <summary>
        /// Abstract end visitor, which calls the end visitor of the base class (Columbus.Csharp.Asg.Nodes.Base.Positioned) of the Columbus.Csharp.Asg.Nodes.Structure.TupleElementSyntax node.
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public override void visitEnd(Columbus.Csharp.Asg.Nodes.Structure.TupleElementSyntax node, bool callVirtualBase) {
            visitEnd((Columbus.Csharp.Asg.Nodes.Base.Positioned)node, false);
        }

        /// <summary>
        /// Abstract visitor, which calls the visitor of the base class (Columbus.Csharp.Asg.Nodes.Base.Positioned) of the Columbus.Csharp.Asg.Nodes.Structure.TypeArgumentListSyntax node.
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public override void visit(Columbus.Csharp.Asg.Nodes.Structure.TypeArgumentListSyntax node, bool callVirtualBase) {
            visit((Columbus.Csharp.Asg.Nodes.Base.Positioned)node, false);
        }

        /// <summary>
        /// Abstract end visitor, which calls the end visitor of the base class (Columbus.Csharp.Asg.Nodes.Base.Positioned) of the Columbus.Csharp.Asg.Nodes.Structure.TypeArgumentListSyntax node.
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public override void visitEnd(Columbus.Csharp.Asg.Nodes.Structure.TypeArgumentListSyntax node, bool callVirtualBase) {
            visitEnd((Columbus.Csharp.Asg.Nodes.Base.Positioned)node, false);
        }

        /// <summary>
        /// Abstract visitor, which calls the visitor of the base class (Columbus.Csharp.Asg.Nodes.Structure.TypeParameterConstraintSyntax) of the Columbus.Csharp.Asg.Nodes.Structure.TypeConstraintSyntax node.
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public override void visit(Columbus.Csharp.Asg.Nodes.Structure.TypeConstraintSyntax node, bool callVirtualBase) {
            visit((Columbus.Csharp.Asg.Nodes.Structure.TypeParameterConstraintSyntax)node, false);
        }

        /// <summary>
        /// Abstract end visitor, which calls the end visitor of the base class (Columbus.Csharp.Asg.Nodes.Structure.TypeParameterConstraintSyntax) of the Columbus.Csharp.Asg.Nodes.Structure.TypeConstraintSyntax node.
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public override void visitEnd(Columbus.Csharp.Asg.Nodes.Structure.TypeConstraintSyntax node, bool callVirtualBase) {
            visitEnd((Columbus.Csharp.Asg.Nodes.Structure.TypeParameterConstraintSyntax)node, false);
        }

        /// <summary>
        /// Abstract visitor, which calls the visitor of the base class (Columbus.Csharp.Asg.Nodes.Structure.CrefSyntax) of the Columbus.Csharp.Asg.Nodes.Structure.TypeCrefSyntax node.
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public override void visit(Columbus.Csharp.Asg.Nodes.Structure.TypeCrefSyntax node, bool callVirtualBase) {
            visit((Columbus.Csharp.Asg.Nodes.Structure.CrefSyntax)node, false);
        }

        /// <summary>
        /// Abstract end visitor, which calls the end visitor of the base class (Columbus.Csharp.Asg.Nodes.Structure.CrefSyntax) of the Columbus.Csharp.Asg.Nodes.Structure.TypeCrefSyntax node.
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public override void visitEnd(Columbus.Csharp.Asg.Nodes.Structure.TypeCrefSyntax node, bool callVirtualBase) {
            visitEnd((Columbus.Csharp.Asg.Nodes.Structure.CrefSyntax)node, false);
        }

        /// <summary>
        /// Abstract visitor, which calls the visitor of the base class (Columbus.Csharp.Asg.Nodes.Structure.BaseTypeDeclarationSyntax) of the Columbus.Csharp.Asg.Nodes.Structure.TypeDeclarationSyntax node.
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public virtual void visit(Columbus.Csharp.Asg.Nodes.Structure.TypeDeclarationSyntax node, bool callVirtualBase) {
            visit((Columbus.Csharp.Asg.Nodes.Structure.BaseTypeDeclarationSyntax)node, false);
        }

        /// <summary>
        /// Abstract end visitor, which calls the end visitor of the base class (Columbus.Csharp.Asg.Nodes.Structure.BaseTypeDeclarationSyntax) of the Columbus.Csharp.Asg.Nodes.Structure.TypeDeclarationSyntax node.
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public virtual void visitEnd(Columbus.Csharp.Asg.Nodes.Structure.TypeDeclarationSyntax node, bool callVirtualBase) {
            visitEnd((Columbus.Csharp.Asg.Nodes.Structure.BaseTypeDeclarationSyntax)node, false);
        }

        /// <summary>
        /// Abstract visitor, which calls the visitor of the base class (Columbus.Csharp.Asg.Nodes.Base.Positioned) of the Columbus.Csharp.Asg.Nodes.Structure.TypeParameterConstraintClauseSyntax node.
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public override void visit(Columbus.Csharp.Asg.Nodes.Structure.TypeParameterConstraintClauseSyntax node, bool callVirtualBase) {
            visit((Columbus.Csharp.Asg.Nodes.Base.Positioned)node, false);
        }

        /// <summary>
        /// Abstract end visitor, which calls the end visitor of the base class (Columbus.Csharp.Asg.Nodes.Base.Positioned) of the Columbus.Csharp.Asg.Nodes.Structure.TypeParameterConstraintClauseSyntax node.
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public override void visitEnd(Columbus.Csharp.Asg.Nodes.Structure.TypeParameterConstraintClauseSyntax node, bool callVirtualBase) {
            visitEnd((Columbus.Csharp.Asg.Nodes.Base.Positioned)node, false);
        }

        /// <summary>
        /// Abstract visitor, which calls the visitor of the base class (Columbus.Csharp.Asg.Nodes.Base.Positioned) of the Columbus.Csharp.Asg.Nodes.Structure.TypeParameterConstraintSyntax node.
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public virtual void visit(Columbus.Csharp.Asg.Nodes.Structure.TypeParameterConstraintSyntax node, bool callVirtualBase) {
            visit((Columbus.Csharp.Asg.Nodes.Base.Positioned)node, false);
        }

        /// <summary>
        /// Abstract end visitor, which calls the end visitor of the base class (Columbus.Csharp.Asg.Nodes.Base.Positioned) of the Columbus.Csharp.Asg.Nodes.Structure.TypeParameterConstraintSyntax node.
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public virtual void visitEnd(Columbus.Csharp.Asg.Nodes.Structure.TypeParameterConstraintSyntax node, bool callVirtualBase) {
            visitEnd((Columbus.Csharp.Asg.Nodes.Base.Positioned)node, false);
        }

        /// <summary>
        /// Abstract visitor, which calls the visitor of the base class (Columbus.Csharp.Asg.Nodes.Base.Positioned) of the Columbus.Csharp.Asg.Nodes.Structure.TypeParameterListSyntax node.
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public override void visit(Columbus.Csharp.Asg.Nodes.Structure.TypeParameterListSyntax node, bool callVirtualBase) {
            visit((Columbus.Csharp.Asg.Nodes.Base.Positioned)node, false);
        }

        /// <summary>
        /// Abstract end visitor, which calls the end visitor of the base class (Columbus.Csharp.Asg.Nodes.Base.Positioned) of the Columbus.Csharp.Asg.Nodes.Structure.TypeParameterListSyntax node.
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public override void visitEnd(Columbus.Csharp.Asg.Nodes.Structure.TypeParameterListSyntax node, bool callVirtualBase) {
            visitEnd((Columbus.Csharp.Asg.Nodes.Base.Positioned)node, false);
        }

        /// <summary>
        /// Abstract visitor, which calls the visitor of the base class (Columbus.Csharp.Asg.Nodes.Base.Positioned) of the Columbus.Csharp.Asg.Nodes.Structure.TypeParameterSyntax node.
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public override void visit(Columbus.Csharp.Asg.Nodes.Structure.TypeParameterSyntax node, bool callVirtualBase) {
            visit((Columbus.Csharp.Asg.Nodes.Base.Positioned)node, false);
        }

        /// <summary>
        /// Abstract end visitor, which calls the end visitor of the base class (Columbus.Csharp.Asg.Nodes.Base.Positioned) of the Columbus.Csharp.Asg.Nodes.Structure.TypeParameterSyntax node.
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public override void visitEnd(Columbus.Csharp.Asg.Nodes.Structure.TypeParameterSyntax node, bool callVirtualBase) {
            visitEnd((Columbus.Csharp.Asg.Nodes.Base.Positioned)node, false);
        }

        /// <summary>
        /// Abstract visitor, which calls the visitor of the base class (Columbus.Csharp.Asg.Nodes.Base.Positioned) of the Columbus.Csharp.Asg.Nodes.Structure.UsingDirectiveSyntax node.
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public override void visit(Columbus.Csharp.Asg.Nodes.Structure.UsingDirectiveSyntax node, bool callVirtualBase) {
            visit((Columbus.Csharp.Asg.Nodes.Base.Positioned)node, false);
        }

        /// <summary>
        /// Abstract end visitor, which calls the end visitor of the base class (Columbus.Csharp.Asg.Nodes.Base.Positioned) of the Columbus.Csharp.Asg.Nodes.Structure.UsingDirectiveSyntax node.
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public override void visitEnd(Columbus.Csharp.Asg.Nodes.Structure.UsingDirectiveSyntax node, bool callVirtualBase) {
            visitEnd((Columbus.Csharp.Asg.Nodes.Base.Positioned)node, false);
        }

        /// <summary>
        /// Abstract visitor, which calls the visitor of the base class (Columbus.Csharp.Asg.Nodes.Structure.PatternSyntax) of the Columbus.Csharp.Asg.Nodes.Structure.VarPatternSyntax node.
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public override void visit(Columbus.Csharp.Asg.Nodes.Structure.VarPatternSyntax node, bool callVirtualBase) {
            visit((Columbus.Csharp.Asg.Nodes.Structure.PatternSyntax)node, false);
        }

        /// <summary>
        /// Abstract end visitor, which calls the end visitor of the base class (Columbus.Csharp.Asg.Nodes.Structure.PatternSyntax) of the Columbus.Csharp.Asg.Nodes.Structure.VarPatternSyntax node.
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public override void visitEnd(Columbus.Csharp.Asg.Nodes.Structure.VarPatternSyntax node, bool callVirtualBase) {
            visitEnd((Columbus.Csharp.Asg.Nodes.Structure.PatternSyntax)node, false);
        }

        /// <summary>
        /// Abstract visitor, which calls the visitor of the base class (Columbus.Csharp.Asg.Nodes.Base.Positioned) of the Columbus.Csharp.Asg.Nodes.Structure.VariableDeclarationSyntax node.
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public override void visit(Columbus.Csharp.Asg.Nodes.Structure.VariableDeclarationSyntax node, bool callVirtualBase) {
            visit((Columbus.Csharp.Asg.Nodes.Base.Positioned)node, false);
        }

        /// <summary>
        /// Abstract end visitor, which calls the end visitor of the base class (Columbus.Csharp.Asg.Nodes.Base.Positioned) of the Columbus.Csharp.Asg.Nodes.Structure.VariableDeclarationSyntax node.
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public override void visitEnd(Columbus.Csharp.Asg.Nodes.Structure.VariableDeclarationSyntax node, bool callVirtualBase) {
            visitEnd((Columbus.Csharp.Asg.Nodes.Base.Positioned)node, false);
        }

        /// <summary>
        /// Abstract visitor, which calls the visitor of the base class (Columbus.Csharp.Asg.Nodes.Base.Positioned) of the Columbus.Csharp.Asg.Nodes.Structure.VariableDeclaratorSyntax node.
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public override void visit(Columbus.Csharp.Asg.Nodes.Structure.VariableDeclaratorSyntax node, bool callVirtualBase) {
            visit((Columbus.Csharp.Asg.Nodes.Base.Positioned)node, false);
        }

        /// <summary>
        /// Abstract end visitor, which calls the end visitor of the base class (Columbus.Csharp.Asg.Nodes.Base.Positioned) of the Columbus.Csharp.Asg.Nodes.Structure.VariableDeclaratorSyntax node.
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public override void visitEnd(Columbus.Csharp.Asg.Nodes.Structure.VariableDeclaratorSyntax node, bool callVirtualBase) {
            visitEnd((Columbus.Csharp.Asg.Nodes.Base.Positioned)node, false);
        }

        /// <summary>
        /// Abstract visitor, which calls the visitor of the base class (Columbus.Csharp.Asg.Nodes.Base.Positioned) of the Columbus.Csharp.Asg.Nodes.Structure.VariableDesignationSyntax node.
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public virtual void visit(Columbus.Csharp.Asg.Nodes.Structure.VariableDesignationSyntax node, bool callVirtualBase) {
            visit((Columbus.Csharp.Asg.Nodes.Base.Positioned)node, false);
        }

        /// <summary>
        /// Abstract end visitor, which calls the end visitor of the base class (Columbus.Csharp.Asg.Nodes.Base.Positioned) of the Columbus.Csharp.Asg.Nodes.Structure.VariableDesignationSyntax node.
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public virtual void visitEnd(Columbus.Csharp.Asg.Nodes.Structure.VariableDesignationSyntax node, bool callVirtualBase) {
            visitEnd((Columbus.Csharp.Asg.Nodes.Base.Positioned)node, false);
        }

        /// <summary>
        /// Abstract visitor, which calls the visitor of the base class (Columbus.Csharp.Asg.Nodes.Base.Positioned) of the Columbus.Csharp.Asg.Nodes.Structure.WhenClauseSyntax node.
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public override void visit(Columbus.Csharp.Asg.Nodes.Structure.WhenClauseSyntax node, bool callVirtualBase) {
            visit((Columbus.Csharp.Asg.Nodes.Base.Positioned)node, false);
        }

        /// <summary>
        /// Abstract end visitor, which calls the end visitor of the base class (Columbus.Csharp.Asg.Nodes.Base.Positioned) of the Columbus.Csharp.Asg.Nodes.Structure.WhenClauseSyntax node.
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public override void visitEnd(Columbus.Csharp.Asg.Nodes.Structure.WhenClauseSyntax node, bool callVirtualBase) {
            visitEnd((Columbus.Csharp.Asg.Nodes.Base.Positioned)node, false);
        }

        /// <summary>
        /// Abstract visitor, which calls the visitor of the base class (Columbus.Csharp.Asg.Nodes.Structure.QueryClauseSyntax) of the Columbus.Csharp.Asg.Nodes.Structure.WhereClauseSyntax node.
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public override void visit(Columbus.Csharp.Asg.Nodes.Structure.WhereClauseSyntax node, bool callVirtualBase) {
            visit((Columbus.Csharp.Asg.Nodes.Structure.QueryClauseSyntax)node, false);
        }

        /// <summary>
        /// Abstract end visitor, which calls the end visitor of the base class (Columbus.Csharp.Asg.Nodes.Structure.QueryClauseSyntax) of the Columbus.Csharp.Asg.Nodes.Structure.WhereClauseSyntax node.
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public override void visitEnd(Columbus.Csharp.Asg.Nodes.Structure.WhereClauseSyntax node, bool callVirtualBase) {
            visitEnd((Columbus.Csharp.Asg.Nodes.Structure.QueryClauseSyntax)node, false);
        }

        /// <summary>
        /// Abstract visitor, which calls the visitor of the base class (Columbus.Csharp.Asg.Nodes.Base.Positioned) of the Columbus.Csharp.Asg.Nodes.Structure.XmlAttributeSyntax node.
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public virtual void visit(Columbus.Csharp.Asg.Nodes.Structure.XmlAttributeSyntax node, bool callVirtualBase) {
            visit((Columbus.Csharp.Asg.Nodes.Base.Positioned)node, false);
        }

        /// <summary>
        /// Abstract end visitor, which calls the end visitor of the base class (Columbus.Csharp.Asg.Nodes.Base.Positioned) of the Columbus.Csharp.Asg.Nodes.Structure.XmlAttributeSyntax node.
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public virtual void visitEnd(Columbus.Csharp.Asg.Nodes.Structure.XmlAttributeSyntax node, bool callVirtualBase) {
            visitEnd((Columbus.Csharp.Asg.Nodes.Base.Positioned)node, false);
        }

        /// <summary>
        /// Abstract visitor, which calls the visitor of the base class (Columbus.Csharp.Asg.Nodes.Structure.XmlNodeSyntax) of the Columbus.Csharp.Asg.Nodes.Structure.XmlCDataSectionSyntax node.
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public override void visit(Columbus.Csharp.Asg.Nodes.Structure.XmlCDataSectionSyntax node, bool callVirtualBase) {
            visit((Columbus.Csharp.Asg.Nodes.Structure.XmlNodeSyntax)node, false);
        }

        /// <summary>
        /// Abstract end visitor, which calls the end visitor of the base class (Columbus.Csharp.Asg.Nodes.Structure.XmlNodeSyntax) of the Columbus.Csharp.Asg.Nodes.Structure.XmlCDataSectionSyntax node.
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public override void visitEnd(Columbus.Csharp.Asg.Nodes.Structure.XmlCDataSectionSyntax node, bool callVirtualBase) {
            visitEnd((Columbus.Csharp.Asg.Nodes.Structure.XmlNodeSyntax)node, false);
        }

        /// <summary>
        /// Abstract visitor, which calls the visitor of the base class (Columbus.Csharp.Asg.Nodes.Structure.XmlNodeSyntax) of the Columbus.Csharp.Asg.Nodes.Structure.XmlCommentSyntax node.
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public override void visit(Columbus.Csharp.Asg.Nodes.Structure.XmlCommentSyntax node, bool callVirtualBase) {
            visit((Columbus.Csharp.Asg.Nodes.Structure.XmlNodeSyntax)node, false);
        }

        /// <summary>
        /// Abstract end visitor, which calls the end visitor of the base class (Columbus.Csharp.Asg.Nodes.Structure.XmlNodeSyntax) of the Columbus.Csharp.Asg.Nodes.Structure.XmlCommentSyntax node.
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public override void visitEnd(Columbus.Csharp.Asg.Nodes.Structure.XmlCommentSyntax node, bool callVirtualBase) {
            visitEnd((Columbus.Csharp.Asg.Nodes.Structure.XmlNodeSyntax)node, false);
        }

        /// <summary>
        /// Abstract visitor, which calls the visitor of the base class (Columbus.Csharp.Asg.Nodes.Structure.XmlAttributeSyntax) of the Columbus.Csharp.Asg.Nodes.Structure.XmlCrefAttributeSyntax node.
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public override void visit(Columbus.Csharp.Asg.Nodes.Structure.XmlCrefAttributeSyntax node, bool callVirtualBase) {
            visit((Columbus.Csharp.Asg.Nodes.Structure.XmlAttributeSyntax)node, false);
        }

        /// <summary>
        /// Abstract end visitor, which calls the end visitor of the base class (Columbus.Csharp.Asg.Nodes.Structure.XmlAttributeSyntax) of the Columbus.Csharp.Asg.Nodes.Structure.XmlCrefAttributeSyntax node.
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public override void visitEnd(Columbus.Csharp.Asg.Nodes.Structure.XmlCrefAttributeSyntax node, bool callVirtualBase) {
            visitEnd((Columbus.Csharp.Asg.Nodes.Structure.XmlAttributeSyntax)node, false);
        }

        /// <summary>
        /// Abstract visitor, which calls the visitor of the base class (Columbus.Csharp.Asg.Nodes.Base.Positioned) of the Columbus.Csharp.Asg.Nodes.Structure.XmlElementEndTagSyntax node.
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public override void visit(Columbus.Csharp.Asg.Nodes.Structure.XmlElementEndTagSyntax node, bool callVirtualBase) {
            visit((Columbus.Csharp.Asg.Nodes.Base.Positioned)node, false);
        }

        /// <summary>
        /// Abstract end visitor, which calls the end visitor of the base class (Columbus.Csharp.Asg.Nodes.Base.Positioned) of the Columbus.Csharp.Asg.Nodes.Structure.XmlElementEndTagSyntax node.
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public override void visitEnd(Columbus.Csharp.Asg.Nodes.Structure.XmlElementEndTagSyntax node, bool callVirtualBase) {
            visitEnd((Columbus.Csharp.Asg.Nodes.Base.Positioned)node, false);
        }

        /// <summary>
        /// Abstract visitor, which calls the visitor of the base class (Columbus.Csharp.Asg.Nodes.Base.Positioned) of the Columbus.Csharp.Asg.Nodes.Structure.XmlElementStartTagSyntax node.
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public override void visit(Columbus.Csharp.Asg.Nodes.Structure.XmlElementStartTagSyntax node, bool callVirtualBase) {
            visit((Columbus.Csharp.Asg.Nodes.Base.Positioned)node, false);
        }

        /// <summary>
        /// Abstract end visitor, which calls the end visitor of the base class (Columbus.Csharp.Asg.Nodes.Base.Positioned) of the Columbus.Csharp.Asg.Nodes.Structure.XmlElementStartTagSyntax node.
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public override void visitEnd(Columbus.Csharp.Asg.Nodes.Structure.XmlElementStartTagSyntax node, bool callVirtualBase) {
            visitEnd((Columbus.Csharp.Asg.Nodes.Base.Positioned)node, false);
        }

        /// <summary>
        /// Abstract visitor, which calls the visitor of the base class (Columbus.Csharp.Asg.Nodes.Structure.XmlNodeSyntax) of the Columbus.Csharp.Asg.Nodes.Structure.XmlElementSyntax node.
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public override void visit(Columbus.Csharp.Asg.Nodes.Structure.XmlElementSyntax node, bool callVirtualBase) {
            visit((Columbus.Csharp.Asg.Nodes.Structure.XmlNodeSyntax)node, false);
        }

        /// <summary>
        /// Abstract end visitor, which calls the end visitor of the base class (Columbus.Csharp.Asg.Nodes.Structure.XmlNodeSyntax) of the Columbus.Csharp.Asg.Nodes.Structure.XmlElementSyntax node.
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public override void visitEnd(Columbus.Csharp.Asg.Nodes.Structure.XmlElementSyntax node, bool callVirtualBase) {
            visitEnd((Columbus.Csharp.Asg.Nodes.Structure.XmlNodeSyntax)node, false);
        }

        /// <summary>
        /// Abstract visitor, which calls the visitor of the base class (Columbus.Csharp.Asg.Nodes.Structure.XmlNodeSyntax) of the Columbus.Csharp.Asg.Nodes.Structure.XmlEmptyElementSyntax node.
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public override void visit(Columbus.Csharp.Asg.Nodes.Structure.XmlEmptyElementSyntax node, bool callVirtualBase) {
            visit((Columbus.Csharp.Asg.Nodes.Structure.XmlNodeSyntax)node, false);
        }

        /// <summary>
        /// Abstract end visitor, which calls the end visitor of the base class (Columbus.Csharp.Asg.Nodes.Structure.XmlNodeSyntax) of the Columbus.Csharp.Asg.Nodes.Structure.XmlEmptyElementSyntax node.
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public override void visitEnd(Columbus.Csharp.Asg.Nodes.Structure.XmlEmptyElementSyntax node, bool callVirtualBase) {
            visitEnd((Columbus.Csharp.Asg.Nodes.Structure.XmlNodeSyntax)node, false);
        }

        /// <summary>
        /// Abstract visitor, which calls the visitor of the base class (Columbus.Csharp.Asg.Nodes.Structure.XmlAttributeSyntax) of the Columbus.Csharp.Asg.Nodes.Structure.XmlNameAttributeSyntax node.
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public override void visit(Columbus.Csharp.Asg.Nodes.Structure.XmlNameAttributeSyntax node, bool callVirtualBase) {
            visit((Columbus.Csharp.Asg.Nodes.Structure.XmlAttributeSyntax)node, false);
        }

        /// <summary>
        /// Abstract end visitor, which calls the end visitor of the base class (Columbus.Csharp.Asg.Nodes.Structure.XmlAttributeSyntax) of the Columbus.Csharp.Asg.Nodes.Structure.XmlNameAttributeSyntax node.
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public override void visitEnd(Columbus.Csharp.Asg.Nodes.Structure.XmlNameAttributeSyntax node, bool callVirtualBase) {
            visitEnd((Columbus.Csharp.Asg.Nodes.Structure.XmlAttributeSyntax)node, false);
        }

        /// <summary>
        /// Abstract visitor, which calls the visitor of the base class (Columbus.Csharp.Asg.Nodes.Base.Positioned) of the Columbus.Csharp.Asg.Nodes.Structure.XmlNameSyntax node.
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public override void visit(Columbus.Csharp.Asg.Nodes.Structure.XmlNameSyntax node, bool callVirtualBase) {
            visit((Columbus.Csharp.Asg.Nodes.Base.Positioned)node, false);
        }

        /// <summary>
        /// Abstract end visitor, which calls the end visitor of the base class (Columbus.Csharp.Asg.Nodes.Base.Positioned) of the Columbus.Csharp.Asg.Nodes.Structure.XmlNameSyntax node.
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public override void visitEnd(Columbus.Csharp.Asg.Nodes.Structure.XmlNameSyntax node, bool callVirtualBase) {
            visitEnd((Columbus.Csharp.Asg.Nodes.Base.Positioned)node, false);
        }

        /// <summary>
        /// Abstract visitor, which calls the visitor of the base class (Columbus.Csharp.Asg.Nodes.Base.Positioned) of the Columbus.Csharp.Asg.Nodes.Structure.XmlNodeSyntax node.
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public virtual void visit(Columbus.Csharp.Asg.Nodes.Structure.XmlNodeSyntax node, bool callVirtualBase) {
            visit((Columbus.Csharp.Asg.Nodes.Base.Positioned)node, false);
        }

        /// <summary>
        /// Abstract end visitor, which calls the end visitor of the base class (Columbus.Csharp.Asg.Nodes.Base.Positioned) of the Columbus.Csharp.Asg.Nodes.Structure.XmlNodeSyntax node.
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public virtual void visitEnd(Columbus.Csharp.Asg.Nodes.Structure.XmlNodeSyntax node, bool callVirtualBase) {
            visitEnd((Columbus.Csharp.Asg.Nodes.Base.Positioned)node, false);
        }

        /// <summary>
        /// Abstract visitor, which calls the visitor of the base class (Columbus.Csharp.Asg.Nodes.Base.Positioned) of the Columbus.Csharp.Asg.Nodes.Structure.XmlPrefixSyntax node.
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public override void visit(Columbus.Csharp.Asg.Nodes.Structure.XmlPrefixSyntax node, bool callVirtualBase) {
            visit((Columbus.Csharp.Asg.Nodes.Base.Positioned)node, false);
        }

        /// <summary>
        /// Abstract end visitor, which calls the end visitor of the base class (Columbus.Csharp.Asg.Nodes.Base.Positioned) of the Columbus.Csharp.Asg.Nodes.Structure.XmlPrefixSyntax node.
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public override void visitEnd(Columbus.Csharp.Asg.Nodes.Structure.XmlPrefixSyntax node, bool callVirtualBase) {
            visitEnd((Columbus.Csharp.Asg.Nodes.Base.Positioned)node, false);
        }

        /// <summary>
        /// Abstract visitor, which calls the visitor of the base class (Columbus.Csharp.Asg.Nodes.Structure.XmlNodeSyntax) of the Columbus.Csharp.Asg.Nodes.Structure.XmlProcessingInstructionSyntax node.
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public override void visit(Columbus.Csharp.Asg.Nodes.Structure.XmlProcessingInstructionSyntax node, bool callVirtualBase) {
            visit((Columbus.Csharp.Asg.Nodes.Structure.XmlNodeSyntax)node, false);
        }

        /// <summary>
        /// Abstract end visitor, which calls the end visitor of the base class (Columbus.Csharp.Asg.Nodes.Structure.XmlNodeSyntax) of the Columbus.Csharp.Asg.Nodes.Structure.XmlProcessingInstructionSyntax node.
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public override void visitEnd(Columbus.Csharp.Asg.Nodes.Structure.XmlProcessingInstructionSyntax node, bool callVirtualBase) {
            visitEnd((Columbus.Csharp.Asg.Nodes.Structure.XmlNodeSyntax)node, false);
        }

        /// <summary>
        /// Abstract visitor, which calls the visitor of the base class (Columbus.Csharp.Asg.Nodes.Structure.XmlAttributeSyntax) of the Columbus.Csharp.Asg.Nodes.Structure.XmlTextAttributeSyntax node.
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public override void visit(Columbus.Csharp.Asg.Nodes.Structure.XmlTextAttributeSyntax node, bool callVirtualBase) {
            visit((Columbus.Csharp.Asg.Nodes.Structure.XmlAttributeSyntax)node, false);
        }

        /// <summary>
        /// Abstract end visitor, which calls the end visitor of the base class (Columbus.Csharp.Asg.Nodes.Structure.XmlAttributeSyntax) of the Columbus.Csharp.Asg.Nodes.Structure.XmlTextAttributeSyntax node.
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public override void visitEnd(Columbus.Csharp.Asg.Nodes.Structure.XmlTextAttributeSyntax node, bool callVirtualBase) {
            visitEnd((Columbus.Csharp.Asg.Nodes.Structure.XmlAttributeSyntax)node, false);
        }

        /// <summary>
        /// Abstract visitor, which calls the visitor of the base class (Columbus.Csharp.Asg.Nodes.Structure.XmlNodeSyntax) of the Columbus.Csharp.Asg.Nodes.Structure.XmlTextSyntax node.
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public override void visit(Columbus.Csharp.Asg.Nodes.Structure.XmlTextSyntax node, bool callVirtualBase) {
            visit((Columbus.Csharp.Asg.Nodes.Structure.XmlNodeSyntax)node, false);
        }

        /// <summary>
        /// Abstract end visitor, which calls the end visitor of the base class (Columbus.Csharp.Asg.Nodes.Structure.XmlNodeSyntax) of the Columbus.Csharp.Asg.Nodes.Structure.XmlTextSyntax node.
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public override void visitEnd(Columbus.Csharp.Asg.Nodes.Structure.XmlTextSyntax node, bool callVirtualBase) {
            visitEnd((Columbus.Csharp.Asg.Nodes.Structure.XmlNodeSyntax)node, false);
        }

    }

}
