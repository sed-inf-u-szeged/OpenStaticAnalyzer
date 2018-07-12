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
    class Visitor {

        /// <summary>The Visitors depth.</summary>
        protected uint depth;
        /// <summary>
        /// Constructor for the Visitor.
        /// </summary>
        public Visitor() {
            depth = 0;
        }

        /// <summary>
        /// Return the Visitors depth.
        /// </summary>
        /// <returns>The visitors depth.</returns>
        public uint Depth {
            get { return depth; }
        }

        /// <summary>
        /// Increases the Visitors depth.
        /// </summary>
        public void incDepth() {
            ++depth;
        }

        /// <summary>
        /// Decreases the Visitors depth.
        /// </summary>
        public void decDepth() {
            --depth;
        }

        /// <summary>
        /// Visitor which is called at the beginning of the Columbus.Csharp.Asg.Nodes.Expression.AliasQualifiedNameSyntax node visiting.
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public virtual void visit(Columbus.Csharp.Asg.Nodes.Expression.AliasQualifiedNameSyntax node, bool callVirtualBase = true) { }

        /// <summary>
        /// Visitor which is called at the end of the Columbus.Csharp.Asg.Nodes.Expression.AliasQualifiedNameSyntax node visiting.
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public virtual void visitEnd(Columbus.Csharp.Asg.Nodes.Expression.AliasQualifiedNameSyntax node, bool callVirtualBase = true) { }

        /// <summary>
        /// Visitor which is called at the beginning of the Columbus.Csharp.Asg.Nodes.Expression.AnonymousMethodExpressionSyntax node visiting.
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public virtual void visit(Columbus.Csharp.Asg.Nodes.Expression.AnonymousMethodExpressionSyntax node, bool callVirtualBase = true) { }

        /// <summary>
        /// Visitor which is called at the end of the Columbus.Csharp.Asg.Nodes.Expression.AnonymousMethodExpressionSyntax node visiting.
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public virtual void visitEnd(Columbus.Csharp.Asg.Nodes.Expression.AnonymousMethodExpressionSyntax node, bool callVirtualBase = true) { }

        /// <summary>
        /// Visitor which is called at the beginning of the Columbus.Csharp.Asg.Nodes.Expression.AnonymousObjectCreationExpressionSyntax node visiting.
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public virtual void visit(Columbus.Csharp.Asg.Nodes.Expression.AnonymousObjectCreationExpressionSyntax node, bool callVirtualBase = true) { }

        /// <summary>
        /// Visitor which is called at the end of the Columbus.Csharp.Asg.Nodes.Expression.AnonymousObjectCreationExpressionSyntax node visiting.
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public virtual void visitEnd(Columbus.Csharp.Asg.Nodes.Expression.AnonymousObjectCreationExpressionSyntax node, bool callVirtualBase = true) { }

        /// <summary>
        /// Visitor which is called at the beginning of the Columbus.Csharp.Asg.Nodes.Expression.ArrayCreationExpressionSyntax node visiting.
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public virtual void visit(Columbus.Csharp.Asg.Nodes.Expression.ArrayCreationExpressionSyntax node, bool callVirtualBase = true) { }

        /// <summary>
        /// Visitor which is called at the end of the Columbus.Csharp.Asg.Nodes.Expression.ArrayCreationExpressionSyntax node visiting.
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public virtual void visitEnd(Columbus.Csharp.Asg.Nodes.Expression.ArrayCreationExpressionSyntax node, bool callVirtualBase = true) { }

        /// <summary>
        /// Visitor which is called at the beginning of the Columbus.Csharp.Asg.Nodes.Expression.ArrayTypeSyntax node visiting.
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public virtual void visit(Columbus.Csharp.Asg.Nodes.Expression.ArrayTypeSyntax node, bool callVirtualBase = true) { }

        /// <summary>
        /// Visitor which is called at the end of the Columbus.Csharp.Asg.Nodes.Expression.ArrayTypeSyntax node visiting.
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public virtual void visitEnd(Columbus.Csharp.Asg.Nodes.Expression.ArrayTypeSyntax node, bool callVirtualBase = true) { }

        /// <summary>
        /// Visitor which is called at the beginning of the Columbus.Csharp.Asg.Nodes.Expression.AssignmentExpressionSyntax node visiting.
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public virtual void visit(Columbus.Csharp.Asg.Nodes.Expression.AssignmentExpressionSyntax node, bool callVirtualBase = true) { }

        /// <summary>
        /// Visitor which is called at the end of the Columbus.Csharp.Asg.Nodes.Expression.AssignmentExpressionSyntax node visiting.
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public virtual void visitEnd(Columbus.Csharp.Asg.Nodes.Expression.AssignmentExpressionSyntax node, bool callVirtualBase = true) { }

        /// <summary>
        /// Visitor which is called at the beginning of the Columbus.Csharp.Asg.Nodes.Expression.AwaitExpressionSyntax node visiting.
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public virtual void visit(Columbus.Csharp.Asg.Nodes.Expression.AwaitExpressionSyntax node, bool callVirtualBase = true) { }

        /// <summary>
        /// Visitor which is called at the end of the Columbus.Csharp.Asg.Nodes.Expression.AwaitExpressionSyntax node visiting.
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public virtual void visitEnd(Columbus.Csharp.Asg.Nodes.Expression.AwaitExpressionSyntax node, bool callVirtualBase = true) { }

        /// <summary>
        /// Visitor which is called at the beginning of the Columbus.Csharp.Asg.Nodes.Expression.BaseExpressionSyntax node visiting.
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public virtual void visit(Columbus.Csharp.Asg.Nodes.Expression.BaseExpressionSyntax node, bool callVirtualBase = true) { }

        /// <summary>
        /// Visitor which is called at the end of the Columbus.Csharp.Asg.Nodes.Expression.BaseExpressionSyntax node visiting.
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public virtual void visitEnd(Columbus.Csharp.Asg.Nodes.Expression.BaseExpressionSyntax node, bool callVirtualBase = true) { }

        /// <summary>
        /// Visitor which is called at the beginning of the Columbus.Csharp.Asg.Nodes.Expression.BinaryExpressionSyntax node visiting.
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public virtual void visit(Columbus.Csharp.Asg.Nodes.Expression.BinaryExpressionSyntax node, bool callVirtualBase = true) { }

        /// <summary>
        /// Visitor which is called at the end of the Columbus.Csharp.Asg.Nodes.Expression.BinaryExpressionSyntax node visiting.
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public virtual void visitEnd(Columbus.Csharp.Asg.Nodes.Expression.BinaryExpressionSyntax node, bool callVirtualBase = true) { }

        /// <summary>
        /// Visitor which is called at the beginning of the Columbus.Csharp.Asg.Nodes.Expression.CastExpressionSyntax node visiting.
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public virtual void visit(Columbus.Csharp.Asg.Nodes.Expression.CastExpressionSyntax node, bool callVirtualBase = true) { }

        /// <summary>
        /// Visitor which is called at the end of the Columbus.Csharp.Asg.Nodes.Expression.CastExpressionSyntax node visiting.
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public virtual void visitEnd(Columbus.Csharp.Asg.Nodes.Expression.CastExpressionSyntax node, bool callVirtualBase = true) { }

        /// <summary>
        /// Visitor which is called at the beginning of the Columbus.Csharp.Asg.Nodes.Expression.CheckedExpressionSyntax node visiting.
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public virtual void visit(Columbus.Csharp.Asg.Nodes.Expression.CheckedExpressionSyntax node, bool callVirtualBase = true) { }

        /// <summary>
        /// Visitor which is called at the end of the Columbus.Csharp.Asg.Nodes.Expression.CheckedExpressionSyntax node visiting.
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public virtual void visitEnd(Columbus.Csharp.Asg.Nodes.Expression.CheckedExpressionSyntax node, bool callVirtualBase = true) { }

        /// <summary>
        /// Visitor which is called at the beginning of the Columbus.Csharp.Asg.Nodes.Expression.ConditionalAccessExpressionSyntax node visiting.
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public virtual void visit(Columbus.Csharp.Asg.Nodes.Expression.ConditionalAccessExpressionSyntax node, bool callVirtualBase = true) { }

        /// <summary>
        /// Visitor which is called at the end of the Columbus.Csharp.Asg.Nodes.Expression.ConditionalAccessExpressionSyntax node visiting.
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public virtual void visitEnd(Columbus.Csharp.Asg.Nodes.Expression.ConditionalAccessExpressionSyntax node, bool callVirtualBase = true) { }

        /// <summary>
        /// Visitor which is called at the beginning of the Columbus.Csharp.Asg.Nodes.Expression.ConditionalExpressionSyntax node visiting.
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public virtual void visit(Columbus.Csharp.Asg.Nodes.Expression.ConditionalExpressionSyntax node, bool callVirtualBase = true) { }

        /// <summary>
        /// Visitor which is called at the end of the Columbus.Csharp.Asg.Nodes.Expression.ConditionalExpressionSyntax node visiting.
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public virtual void visitEnd(Columbus.Csharp.Asg.Nodes.Expression.ConditionalExpressionSyntax node, bool callVirtualBase = true) { }

        /// <summary>
        /// Visitor which is called at the beginning of the Columbus.Csharp.Asg.Nodes.Expression.DefaultExpressionSyntax node visiting.
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public virtual void visit(Columbus.Csharp.Asg.Nodes.Expression.DefaultExpressionSyntax node, bool callVirtualBase = true) { }

        /// <summary>
        /// Visitor which is called at the end of the Columbus.Csharp.Asg.Nodes.Expression.DefaultExpressionSyntax node visiting.
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public virtual void visitEnd(Columbus.Csharp.Asg.Nodes.Expression.DefaultExpressionSyntax node, bool callVirtualBase = true) { }

        /// <summary>
        /// Visitor which is called at the beginning of the Columbus.Csharp.Asg.Nodes.Expression.ElementAccessExpressionSyntax node visiting.
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public virtual void visit(Columbus.Csharp.Asg.Nodes.Expression.ElementAccessExpressionSyntax node, bool callVirtualBase = true) { }

        /// <summary>
        /// Visitor which is called at the end of the Columbus.Csharp.Asg.Nodes.Expression.ElementAccessExpressionSyntax node visiting.
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public virtual void visitEnd(Columbus.Csharp.Asg.Nodes.Expression.ElementAccessExpressionSyntax node, bool callVirtualBase = true) { }

        /// <summary>
        /// Visitor which is called at the beginning of the Columbus.Csharp.Asg.Nodes.Expression.ElementBindingExpressionSyntax node visiting.
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public virtual void visit(Columbus.Csharp.Asg.Nodes.Expression.ElementBindingExpressionSyntax node, bool callVirtualBase = true) { }

        /// <summary>
        /// Visitor which is called at the end of the Columbus.Csharp.Asg.Nodes.Expression.ElementBindingExpressionSyntax node visiting.
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public virtual void visitEnd(Columbus.Csharp.Asg.Nodes.Expression.ElementBindingExpressionSyntax node, bool callVirtualBase = true) { }

        /// <summary>
        /// Visitor which is called at the beginning of the Columbus.Csharp.Asg.Nodes.Expression.GenericNameSyntax node visiting.
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public virtual void visit(Columbus.Csharp.Asg.Nodes.Expression.GenericNameSyntax node, bool callVirtualBase = true) { }

        /// <summary>
        /// Visitor which is called at the end of the Columbus.Csharp.Asg.Nodes.Expression.GenericNameSyntax node visiting.
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public virtual void visitEnd(Columbus.Csharp.Asg.Nodes.Expression.GenericNameSyntax node, bool callVirtualBase = true) { }

        /// <summary>
        /// Visitor which is called at the beginning of the Columbus.Csharp.Asg.Nodes.Expression.IdentifierNameSyntax node visiting.
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public virtual void visit(Columbus.Csharp.Asg.Nodes.Expression.IdentifierNameSyntax node, bool callVirtualBase = true) { }

        /// <summary>
        /// Visitor which is called at the end of the Columbus.Csharp.Asg.Nodes.Expression.IdentifierNameSyntax node visiting.
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public virtual void visitEnd(Columbus.Csharp.Asg.Nodes.Expression.IdentifierNameSyntax node, bool callVirtualBase = true) { }

        /// <summary>
        /// Visitor which is called at the beginning of the Columbus.Csharp.Asg.Nodes.Expression.ImplicitArrayCreationExpressionSyntax node visiting.
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public virtual void visit(Columbus.Csharp.Asg.Nodes.Expression.ImplicitArrayCreationExpressionSyntax node, bool callVirtualBase = true) { }

        /// <summary>
        /// Visitor which is called at the end of the Columbus.Csharp.Asg.Nodes.Expression.ImplicitArrayCreationExpressionSyntax node visiting.
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public virtual void visitEnd(Columbus.Csharp.Asg.Nodes.Expression.ImplicitArrayCreationExpressionSyntax node, bool callVirtualBase = true) { }

        /// <summary>
        /// Visitor which is called at the beginning of the Columbus.Csharp.Asg.Nodes.Expression.ImplicitElementAccessSyntax node visiting.
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public virtual void visit(Columbus.Csharp.Asg.Nodes.Expression.ImplicitElementAccessSyntax node, bool callVirtualBase = true) { }

        /// <summary>
        /// Visitor which is called at the end of the Columbus.Csharp.Asg.Nodes.Expression.ImplicitElementAccessSyntax node visiting.
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public virtual void visitEnd(Columbus.Csharp.Asg.Nodes.Expression.ImplicitElementAccessSyntax node, bool callVirtualBase = true) { }

        /// <summary>
        /// Visitor which is called at the beginning of the Columbus.Csharp.Asg.Nodes.Expression.InitializerExpressionSyntax node visiting.
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public virtual void visit(Columbus.Csharp.Asg.Nodes.Expression.InitializerExpressionSyntax node, bool callVirtualBase = true) { }

        /// <summary>
        /// Visitor which is called at the end of the Columbus.Csharp.Asg.Nodes.Expression.InitializerExpressionSyntax node visiting.
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public virtual void visitEnd(Columbus.Csharp.Asg.Nodes.Expression.InitializerExpressionSyntax node, bool callVirtualBase = true) { }

        /// <summary>
        /// Visitor which is called at the beginning of the Columbus.Csharp.Asg.Nodes.Expression.InterpolatedStringExpressionSyntax node visiting.
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public virtual void visit(Columbus.Csharp.Asg.Nodes.Expression.InterpolatedStringExpressionSyntax node, bool callVirtualBase = true) { }

        /// <summary>
        /// Visitor which is called at the end of the Columbus.Csharp.Asg.Nodes.Expression.InterpolatedStringExpressionSyntax node visiting.
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public virtual void visitEnd(Columbus.Csharp.Asg.Nodes.Expression.InterpolatedStringExpressionSyntax node, bool callVirtualBase = true) { }

        /// <summary>
        /// Visitor which is called at the beginning of the Columbus.Csharp.Asg.Nodes.Expression.InvocationExpressionSyntax node visiting.
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public virtual void visit(Columbus.Csharp.Asg.Nodes.Expression.InvocationExpressionSyntax node, bool callVirtualBase = true) { }

        /// <summary>
        /// Visitor which is called at the end of the Columbus.Csharp.Asg.Nodes.Expression.InvocationExpressionSyntax node visiting.
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public virtual void visitEnd(Columbus.Csharp.Asg.Nodes.Expression.InvocationExpressionSyntax node, bool callVirtualBase = true) { }

        /// <summary>
        /// Visitor which is called at the beginning of the Columbus.Csharp.Asg.Nodes.Expression.LiteralExpressionSyntax node visiting.
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public virtual void visit(Columbus.Csharp.Asg.Nodes.Expression.LiteralExpressionSyntax node, bool callVirtualBase = true) { }

        /// <summary>
        /// Visitor which is called at the end of the Columbus.Csharp.Asg.Nodes.Expression.LiteralExpressionSyntax node visiting.
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public virtual void visitEnd(Columbus.Csharp.Asg.Nodes.Expression.LiteralExpressionSyntax node, bool callVirtualBase = true) { }

        /// <summary>
        /// Visitor which is called at the beginning of the Columbus.Csharp.Asg.Nodes.Expression.MakeRefExpressionSyntax node visiting.
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public virtual void visit(Columbus.Csharp.Asg.Nodes.Expression.MakeRefExpressionSyntax node, bool callVirtualBase = true) { }

        /// <summary>
        /// Visitor which is called at the end of the Columbus.Csharp.Asg.Nodes.Expression.MakeRefExpressionSyntax node visiting.
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public virtual void visitEnd(Columbus.Csharp.Asg.Nodes.Expression.MakeRefExpressionSyntax node, bool callVirtualBase = true) { }

        /// <summary>
        /// Visitor which is called at the beginning of the Columbus.Csharp.Asg.Nodes.Expression.MemberAccessExpressionSyntax node visiting.
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public virtual void visit(Columbus.Csharp.Asg.Nodes.Expression.MemberAccessExpressionSyntax node, bool callVirtualBase = true) { }

        /// <summary>
        /// Visitor which is called at the end of the Columbus.Csharp.Asg.Nodes.Expression.MemberAccessExpressionSyntax node visiting.
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public virtual void visitEnd(Columbus.Csharp.Asg.Nodes.Expression.MemberAccessExpressionSyntax node, bool callVirtualBase = true) { }

        /// <summary>
        /// Visitor which is called at the beginning of the Columbus.Csharp.Asg.Nodes.Expression.MemberBindingExpressionSyntax node visiting.
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public virtual void visit(Columbus.Csharp.Asg.Nodes.Expression.MemberBindingExpressionSyntax node, bool callVirtualBase = true) { }

        /// <summary>
        /// Visitor which is called at the end of the Columbus.Csharp.Asg.Nodes.Expression.MemberBindingExpressionSyntax node visiting.
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public virtual void visitEnd(Columbus.Csharp.Asg.Nodes.Expression.MemberBindingExpressionSyntax node, bool callVirtualBase = true) { }

        /// <summary>
        /// Visitor which is called at the beginning of the Columbus.Csharp.Asg.Nodes.Expression.NullableTypeSyntax node visiting.
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public virtual void visit(Columbus.Csharp.Asg.Nodes.Expression.NullableTypeSyntax node, bool callVirtualBase = true) { }

        /// <summary>
        /// Visitor which is called at the end of the Columbus.Csharp.Asg.Nodes.Expression.NullableTypeSyntax node visiting.
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public virtual void visitEnd(Columbus.Csharp.Asg.Nodes.Expression.NullableTypeSyntax node, bool callVirtualBase = true) { }

        /// <summary>
        /// Visitor which is called at the beginning of the Columbus.Csharp.Asg.Nodes.Expression.ObjectCreationExpressionSyntax node visiting.
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public virtual void visit(Columbus.Csharp.Asg.Nodes.Expression.ObjectCreationExpressionSyntax node, bool callVirtualBase = true) { }

        /// <summary>
        /// Visitor which is called at the end of the Columbus.Csharp.Asg.Nodes.Expression.ObjectCreationExpressionSyntax node visiting.
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public virtual void visitEnd(Columbus.Csharp.Asg.Nodes.Expression.ObjectCreationExpressionSyntax node, bool callVirtualBase = true) { }

        /// <summary>
        /// Visitor which is called at the beginning of the Columbus.Csharp.Asg.Nodes.Expression.OmittedArraySizeExpressionSyntax node visiting.
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public virtual void visit(Columbus.Csharp.Asg.Nodes.Expression.OmittedArraySizeExpressionSyntax node, bool callVirtualBase = true) { }

        /// <summary>
        /// Visitor which is called at the end of the Columbus.Csharp.Asg.Nodes.Expression.OmittedArraySizeExpressionSyntax node visiting.
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public virtual void visitEnd(Columbus.Csharp.Asg.Nodes.Expression.OmittedArraySizeExpressionSyntax node, bool callVirtualBase = true) { }

        /// <summary>
        /// Visitor which is called at the beginning of the Columbus.Csharp.Asg.Nodes.Expression.OmittedTypeArgumentSyntax node visiting.
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public virtual void visit(Columbus.Csharp.Asg.Nodes.Expression.OmittedTypeArgumentSyntax node, bool callVirtualBase = true) { }

        /// <summary>
        /// Visitor which is called at the end of the Columbus.Csharp.Asg.Nodes.Expression.OmittedTypeArgumentSyntax node visiting.
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public virtual void visitEnd(Columbus.Csharp.Asg.Nodes.Expression.OmittedTypeArgumentSyntax node, bool callVirtualBase = true) { }

        /// <summary>
        /// Visitor which is called at the beginning of the Columbus.Csharp.Asg.Nodes.Expression.ParenthesizedExpressionSyntax node visiting.
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public virtual void visit(Columbus.Csharp.Asg.Nodes.Expression.ParenthesizedExpressionSyntax node, bool callVirtualBase = true) { }

        /// <summary>
        /// Visitor which is called at the end of the Columbus.Csharp.Asg.Nodes.Expression.ParenthesizedExpressionSyntax node visiting.
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public virtual void visitEnd(Columbus.Csharp.Asg.Nodes.Expression.ParenthesizedExpressionSyntax node, bool callVirtualBase = true) { }

        /// <summary>
        /// Visitor which is called at the beginning of the Columbus.Csharp.Asg.Nodes.Expression.ParenthesizedLambdaExpressionSyntax node visiting.
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public virtual void visit(Columbus.Csharp.Asg.Nodes.Expression.ParenthesizedLambdaExpressionSyntax node, bool callVirtualBase = true) { }

        /// <summary>
        /// Visitor which is called at the end of the Columbus.Csharp.Asg.Nodes.Expression.ParenthesizedLambdaExpressionSyntax node visiting.
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public virtual void visitEnd(Columbus.Csharp.Asg.Nodes.Expression.ParenthesizedLambdaExpressionSyntax node, bool callVirtualBase = true) { }

        /// <summary>
        /// Visitor which is called at the beginning of the Columbus.Csharp.Asg.Nodes.Expression.PointerTypeSyntax node visiting.
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public virtual void visit(Columbus.Csharp.Asg.Nodes.Expression.PointerTypeSyntax node, bool callVirtualBase = true) { }

        /// <summary>
        /// Visitor which is called at the end of the Columbus.Csharp.Asg.Nodes.Expression.PointerTypeSyntax node visiting.
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public virtual void visitEnd(Columbus.Csharp.Asg.Nodes.Expression.PointerTypeSyntax node, bool callVirtualBase = true) { }

        /// <summary>
        /// Visitor which is called at the beginning of the Columbus.Csharp.Asg.Nodes.Expression.PostfixUnaryExpressionSyntax node visiting.
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public virtual void visit(Columbus.Csharp.Asg.Nodes.Expression.PostfixUnaryExpressionSyntax node, bool callVirtualBase = true) { }

        /// <summary>
        /// Visitor which is called at the end of the Columbus.Csharp.Asg.Nodes.Expression.PostfixUnaryExpressionSyntax node visiting.
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public virtual void visitEnd(Columbus.Csharp.Asg.Nodes.Expression.PostfixUnaryExpressionSyntax node, bool callVirtualBase = true) { }

        /// <summary>
        /// Visitor which is called at the beginning of the Columbus.Csharp.Asg.Nodes.Expression.PredefinedTypeSyntax node visiting.
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public virtual void visit(Columbus.Csharp.Asg.Nodes.Expression.PredefinedTypeSyntax node, bool callVirtualBase = true) { }

        /// <summary>
        /// Visitor which is called at the end of the Columbus.Csharp.Asg.Nodes.Expression.PredefinedTypeSyntax node visiting.
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public virtual void visitEnd(Columbus.Csharp.Asg.Nodes.Expression.PredefinedTypeSyntax node, bool callVirtualBase = true) { }

        /// <summary>
        /// Visitor which is called at the beginning of the Columbus.Csharp.Asg.Nodes.Expression.PrefixUnaryExpressionSyntax node visiting.
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public virtual void visit(Columbus.Csharp.Asg.Nodes.Expression.PrefixUnaryExpressionSyntax node, bool callVirtualBase = true) { }

        /// <summary>
        /// Visitor which is called at the end of the Columbus.Csharp.Asg.Nodes.Expression.PrefixUnaryExpressionSyntax node visiting.
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public virtual void visitEnd(Columbus.Csharp.Asg.Nodes.Expression.PrefixUnaryExpressionSyntax node, bool callVirtualBase = true) { }

        /// <summary>
        /// Visitor which is called at the beginning of the Columbus.Csharp.Asg.Nodes.Expression.QualifiedNameSyntax node visiting.
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public virtual void visit(Columbus.Csharp.Asg.Nodes.Expression.QualifiedNameSyntax node, bool callVirtualBase = true) { }

        /// <summary>
        /// Visitor which is called at the end of the Columbus.Csharp.Asg.Nodes.Expression.QualifiedNameSyntax node visiting.
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public virtual void visitEnd(Columbus.Csharp.Asg.Nodes.Expression.QualifiedNameSyntax node, bool callVirtualBase = true) { }

        /// <summary>
        /// Visitor which is called at the beginning of the Columbus.Csharp.Asg.Nodes.Expression.QueryExpressionSyntax node visiting.
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public virtual void visit(Columbus.Csharp.Asg.Nodes.Expression.QueryExpressionSyntax node, bool callVirtualBase = true) { }

        /// <summary>
        /// Visitor which is called at the end of the Columbus.Csharp.Asg.Nodes.Expression.QueryExpressionSyntax node visiting.
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public virtual void visitEnd(Columbus.Csharp.Asg.Nodes.Expression.QueryExpressionSyntax node, bool callVirtualBase = true) { }

        /// <summary>
        /// Visitor which is called at the beginning of the Columbus.Csharp.Asg.Nodes.Expression.RefTypeExpressionSyntax node visiting.
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public virtual void visit(Columbus.Csharp.Asg.Nodes.Expression.RefTypeExpressionSyntax node, bool callVirtualBase = true) { }

        /// <summary>
        /// Visitor which is called at the end of the Columbus.Csharp.Asg.Nodes.Expression.RefTypeExpressionSyntax node visiting.
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public virtual void visitEnd(Columbus.Csharp.Asg.Nodes.Expression.RefTypeExpressionSyntax node, bool callVirtualBase = true) { }

        /// <summary>
        /// Visitor which is called at the beginning of the Columbus.Csharp.Asg.Nodes.Expression.RefValueExpressionSyntax node visiting.
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public virtual void visit(Columbus.Csharp.Asg.Nodes.Expression.RefValueExpressionSyntax node, bool callVirtualBase = true) { }

        /// <summary>
        /// Visitor which is called at the end of the Columbus.Csharp.Asg.Nodes.Expression.RefValueExpressionSyntax node visiting.
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public virtual void visitEnd(Columbus.Csharp.Asg.Nodes.Expression.RefValueExpressionSyntax node, bool callVirtualBase = true) { }

        /// <summary>
        /// Visitor which is called at the beginning of the Columbus.Csharp.Asg.Nodes.Expression.SimpleLambdaExpressionSyntax node visiting.
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public virtual void visit(Columbus.Csharp.Asg.Nodes.Expression.SimpleLambdaExpressionSyntax node, bool callVirtualBase = true) { }

        /// <summary>
        /// Visitor which is called at the end of the Columbus.Csharp.Asg.Nodes.Expression.SimpleLambdaExpressionSyntax node visiting.
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public virtual void visitEnd(Columbus.Csharp.Asg.Nodes.Expression.SimpleLambdaExpressionSyntax node, bool callVirtualBase = true) { }

        /// <summary>
        /// Visitor which is called at the beginning of the Columbus.Csharp.Asg.Nodes.Expression.SizeOfExpressionSyntax node visiting.
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public virtual void visit(Columbus.Csharp.Asg.Nodes.Expression.SizeOfExpressionSyntax node, bool callVirtualBase = true) { }

        /// <summary>
        /// Visitor which is called at the end of the Columbus.Csharp.Asg.Nodes.Expression.SizeOfExpressionSyntax node visiting.
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public virtual void visitEnd(Columbus.Csharp.Asg.Nodes.Expression.SizeOfExpressionSyntax node, bool callVirtualBase = true) { }

        /// <summary>
        /// Visitor which is called at the beginning of the Columbus.Csharp.Asg.Nodes.Expression.StackAllocArrayCreationExpressionSyntax node visiting.
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public virtual void visit(Columbus.Csharp.Asg.Nodes.Expression.StackAllocArrayCreationExpressionSyntax node, bool callVirtualBase = true) { }

        /// <summary>
        /// Visitor which is called at the end of the Columbus.Csharp.Asg.Nodes.Expression.StackAllocArrayCreationExpressionSyntax node visiting.
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public virtual void visitEnd(Columbus.Csharp.Asg.Nodes.Expression.StackAllocArrayCreationExpressionSyntax node, bool callVirtualBase = true) { }

        /// <summary>
        /// Visitor which is called at the beginning of the Columbus.Csharp.Asg.Nodes.Expression.ThisExpressionSyntax node visiting.
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public virtual void visit(Columbus.Csharp.Asg.Nodes.Expression.ThisExpressionSyntax node, bool callVirtualBase = true) { }

        /// <summary>
        /// Visitor which is called at the end of the Columbus.Csharp.Asg.Nodes.Expression.ThisExpressionSyntax node visiting.
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public virtual void visitEnd(Columbus.Csharp.Asg.Nodes.Expression.ThisExpressionSyntax node, bool callVirtualBase = true) { }

        /// <summary>
        /// Visitor which is called at the beginning of the Columbus.Csharp.Asg.Nodes.Expression.TypeOfExpressionSyntax node visiting.
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public virtual void visit(Columbus.Csharp.Asg.Nodes.Expression.TypeOfExpressionSyntax node, bool callVirtualBase = true) { }

        /// <summary>
        /// Visitor which is called at the end of the Columbus.Csharp.Asg.Nodes.Expression.TypeOfExpressionSyntax node visiting.
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public virtual void visitEnd(Columbus.Csharp.Asg.Nodes.Expression.TypeOfExpressionSyntax node, bool callVirtualBase = true) { }

        /// <summary>
        /// Visitor which is called at the beginning of the Columbus.Csharp.Asg.Nodes.Statement.BlockSyntax node visiting.
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public virtual void visit(Columbus.Csharp.Asg.Nodes.Statement.BlockSyntax node, bool callVirtualBase = true) { }

        /// <summary>
        /// Visitor which is called at the end of the Columbus.Csharp.Asg.Nodes.Statement.BlockSyntax node visiting.
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public virtual void visitEnd(Columbus.Csharp.Asg.Nodes.Statement.BlockSyntax node, bool callVirtualBase = true) { }

        /// <summary>
        /// Visitor which is called at the beginning of the Columbus.Csharp.Asg.Nodes.Statement.BreakStatementSyntax node visiting.
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public virtual void visit(Columbus.Csharp.Asg.Nodes.Statement.BreakStatementSyntax node, bool callVirtualBase = true) { }

        /// <summary>
        /// Visitor which is called at the end of the Columbus.Csharp.Asg.Nodes.Statement.BreakStatementSyntax node visiting.
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public virtual void visitEnd(Columbus.Csharp.Asg.Nodes.Statement.BreakStatementSyntax node, bool callVirtualBase = true) { }

        /// <summary>
        /// Visitor which is called at the beginning of the Columbus.Csharp.Asg.Nodes.Statement.CheckedStatementSyntax node visiting.
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public virtual void visit(Columbus.Csharp.Asg.Nodes.Statement.CheckedStatementSyntax node, bool callVirtualBase = true) { }

        /// <summary>
        /// Visitor which is called at the end of the Columbus.Csharp.Asg.Nodes.Statement.CheckedStatementSyntax node visiting.
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public virtual void visitEnd(Columbus.Csharp.Asg.Nodes.Statement.CheckedStatementSyntax node, bool callVirtualBase = true) { }

        /// <summary>
        /// Visitor which is called at the beginning of the Columbus.Csharp.Asg.Nodes.Statement.ContinueStatementSyntax node visiting.
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public virtual void visit(Columbus.Csharp.Asg.Nodes.Statement.ContinueStatementSyntax node, bool callVirtualBase = true) { }

        /// <summary>
        /// Visitor which is called at the end of the Columbus.Csharp.Asg.Nodes.Statement.ContinueStatementSyntax node visiting.
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public virtual void visitEnd(Columbus.Csharp.Asg.Nodes.Statement.ContinueStatementSyntax node, bool callVirtualBase = true) { }

        /// <summary>
        /// Visitor which is called at the beginning of the Columbus.Csharp.Asg.Nodes.Statement.DoStatementSyntax node visiting.
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public virtual void visit(Columbus.Csharp.Asg.Nodes.Statement.DoStatementSyntax node, bool callVirtualBase = true) { }

        /// <summary>
        /// Visitor which is called at the end of the Columbus.Csharp.Asg.Nodes.Statement.DoStatementSyntax node visiting.
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public virtual void visitEnd(Columbus.Csharp.Asg.Nodes.Statement.DoStatementSyntax node, bool callVirtualBase = true) { }

        /// <summary>
        /// Visitor which is called at the beginning of the Columbus.Csharp.Asg.Nodes.Statement.EmptyStatementSyntax node visiting.
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public virtual void visit(Columbus.Csharp.Asg.Nodes.Statement.EmptyStatementSyntax node, bool callVirtualBase = true) { }

        /// <summary>
        /// Visitor which is called at the end of the Columbus.Csharp.Asg.Nodes.Statement.EmptyStatementSyntax node visiting.
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public virtual void visitEnd(Columbus.Csharp.Asg.Nodes.Statement.EmptyStatementSyntax node, bool callVirtualBase = true) { }

        /// <summary>
        /// Visitor which is called at the beginning of the Columbus.Csharp.Asg.Nodes.Statement.ExpressionStatementSyntax node visiting.
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public virtual void visit(Columbus.Csharp.Asg.Nodes.Statement.ExpressionStatementSyntax node, bool callVirtualBase = true) { }

        /// <summary>
        /// Visitor which is called at the end of the Columbus.Csharp.Asg.Nodes.Statement.ExpressionStatementSyntax node visiting.
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public virtual void visitEnd(Columbus.Csharp.Asg.Nodes.Statement.ExpressionStatementSyntax node, bool callVirtualBase = true) { }

        /// <summary>
        /// Visitor which is called at the beginning of the Columbus.Csharp.Asg.Nodes.Statement.FixedStatementSyntax node visiting.
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public virtual void visit(Columbus.Csharp.Asg.Nodes.Statement.FixedStatementSyntax node, bool callVirtualBase = true) { }

        /// <summary>
        /// Visitor which is called at the end of the Columbus.Csharp.Asg.Nodes.Statement.FixedStatementSyntax node visiting.
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public virtual void visitEnd(Columbus.Csharp.Asg.Nodes.Statement.FixedStatementSyntax node, bool callVirtualBase = true) { }

        /// <summary>
        /// Visitor which is called at the beginning of the Columbus.Csharp.Asg.Nodes.Statement.ForEachStatementSyntax node visiting.
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public virtual void visit(Columbus.Csharp.Asg.Nodes.Statement.ForEachStatementSyntax node, bool callVirtualBase = true) { }

        /// <summary>
        /// Visitor which is called at the end of the Columbus.Csharp.Asg.Nodes.Statement.ForEachStatementSyntax node visiting.
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public virtual void visitEnd(Columbus.Csharp.Asg.Nodes.Statement.ForEachStatementSyntax node, bool callVirtualBase = true) { }

        /// <summary>
        /// Visitor which is called at the beginning of the Columbus.Csharp.Asg.Nodes.Statement.ForStatementSyntax node visiting.
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public virtual void visit(Columbus.Csharp.Asg.Nodes.Statement.ForStatementSyntax node, bool callVirtualBase = true) { }

        /// <summary>
        /// Visitor which is called at the end of the Columbus.Csharp.Asg.Nodes.Statement.ForStatementSyntax node visiting.
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public virtual void visitEnd(Columbus.Csharp.Asg.Nodes.Statement.ForStatementSyntax node, bool callVirtualBase = true) { }

        /// <summary>
        /// Visitor which is called at the beginning of the Columbus.Csharp.Asg.Nodes.Statement.GotoStatementSyntax node visiting.
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public virtual void visit(Columbus.Csharp.Asg.Nodes.Statement.GotoStatementSyntax node, bool callVirtualBase = true) { }

        /// <summary>
        /// Visitor which is called at the end of the Columbus.Csharp.Asg.Nodes.Statement.GotoStatementSyntax node visiting.
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public virtual void visitEnd(Columbus.Csharp.Asg.Nodes.Statement.GotoStatementSyntax node, bool callVirtualBase = true) { }

        /// <summary>
        /// Visitor which is called at the beginning of the Columbus.Csharp.Asg.Nodes.Statement.IfStatementSyntax node visiting.
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public virtual void visit(Columbus.Csharp.Asg.Nodes.Statement.IfStatementSyntax node, bool callVirtualBase = true) { }

        /// <summary>
        /// Visitor which is called at the end of the Columbus.Csharp.Asg.Nodes.Statement.IfStatementSyntax node visiting.
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public virtual void visitEnd(Columbus.Csharp.Asg.Nodes.Statement.IfStatementSyntax node, bool callVirtualBase = true) { }

        /// <summary>
        /// Visitor which is called at the beginning of the Columbus.Csharp.Asg.Nodes.Statement.LabeledStatementSyntax node visiting.
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public virtual void visit(Columbus.Csharp.Asg.Nodes.Statement.LabeledStatementSyntax node, bool callVirtualBase = true) { }

        /// <summary>
        /// Visitor which is called at the end of the Columbus.Csharp.Asg.Nodes.Statement.LabeledStatementSyntax node visiting.
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public virtual void visitEnd(Columbus.Csharp.Asg.Nodes.Statement.LabeledStatementSyntax node, bool callVirtualBase = true) { }

        /// <summary>
        /// Visitor which is called at the beginning of the Columbus.Csharp.Asg.Nodes.Statement.LocalDeclarationStatementSyntax node visiting.
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public virtual void visit(Columbus.Csharp.Asg.Nodes.Statement.LocalDeclarationStatementSyntax node, bool callVirtualBase = true) { }

        /// <summary>
        /// Visitor which is called at the end of the Columbus.Csharp.Asg.Nodes.Statement.LocalDeclarationStatementSyntax node visiting.
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public virtual void visitEnd(Columbus.Csharp.Asg.Nodes.Statement.LocalDeclarationStatementSyntax node, bool callVirtualBase = true) { }

        /// <summary>
        /// Visitor which is called at the beginning of the Columbus.Csharp.Asg.Nodes.Statement.LockStatementSyntax node visiting.
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public virtual void visit(Columbus.Csharp.Asg.Nodes.Statement.LockStatementSyntax node, bool callVirtualBase = true) { }

        /// <summary>
        /// Visitor which is called at the end of the Columbus.Csharp.Asg.Nodes.Statement.LockStatementSyntax node visiting.
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public virtual void visitEnd(Columbus.Csharp.Asg.Nodes.Statement.LockStatementSyntax node, bool callVirtualBase = true) { }

        /// <summary>
        /// Visitor which is called at the beginning of the Columbus.Csharp.Asg.Nodes.Statement.ReturnStatementSyntax node visiting.
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public virtual void visit(Columbus.Csharp.Asg.Nodes.Statement.ReturnStatementSyntax node, bool callVirtualBase = true) { }

        /// <summary>
        /// Visitor which is called at the end of the Columbus.Csharp.Asg.Nodes.Statement.ReturnStatementSyntax node visiting.
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public virtual void visitEnd(Columbus.Csharp.Asg.Nodes.Statement.ReturnStatementSyntax node, bool callVirtualBase = true) { }

        /// <summary>
        /// Visitor which is called at the beginning of the Columbus.Csharp.Asg.Nodes.Statement.SwitchStatementSyntax node visiting.
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public virtual void visit(Columbus.Csharp.Asg.Nodes.Statement.SwitchStatementSyntax node, bool callVirtualBase = true) { }

        /// <summary>
        /// Visitor which is called at the end of the Columbus.Csharp.Asg.Nodes.Statement.SwitchStatementSyntax node visiting.
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public virtual void visitEnd(Columbus.Csharp.Asg.Nodes.Statement.SwitchStatementSyntax node, bool callVirtualBase = true) { }

        /// <summary>
        /// Visitor which is called at the beginning of the Columbus.Csharp.Asg.Nodes.Statement.ThrowStatementSyntax node visiting.
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public virtual void visit(Columbus.Csharp.Asg.Nodes.Statement.ThrowStatementSyntax node, bool callVirtualBase = true) { }

        /// <summary>
        /// Visitor which is called at the end of the Columbus.Csharp.Asg.Nodes.Statement.ThrowStatementSyntax node visiting.
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public virtual void visitEnd(Columbus.Csharp.Asg.Nodes.Statement.ThrowStatementSyntax node, bool callVirtualBase = true) { }

        /// <summary>
        /// Visitor which is called at the beginning of the Columbus.Csharp.Asg.Nodes.Statement.TryStatementSyntax node visiting.
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public virtual void visit(Columbus.Csharp.Asg.Nodes.Statement.TryStatementSyntax node, bool callVirtualBase = true) { }

        /// <summary>
        /// Visitor which is called at the end of the Columbus.Csharp.Asg.Nodes.Statement.TryStatementSyntax node visiting.
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public virtual void visitEnd(Columbus.Csharp.Asg.Nodes.Statement.TryStatementSyntax node, bool callVirtualBase = true) { }

        /// <summary>
        /// Visitor which is called at the beginning of the Columbus.Csharp.Asg.Nodes.Statement.UnsafeStatementSyntax node visiting.
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public virtual void visit(Columbus.Csharp.Asg.Nodes.Statement.UnsafeStatementSyntax node, bool callVirtualBase = true) { }

        /// <summary>
        /// Visitor which is called at the end of the Columbus.Csharp.Asg.Nodes.Statement.UnsafeStatementSyntax node visiting.
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public virtual void visitEnd(Columbus.Csharp.Asg.Nodes.Statement.UnsafeStatementSyntax node, bool callVirtualBase = true) { }

        /// <summary>
        /// Visitor which is called at the beginning of the Columbus.Csharp.Asg.Nodes.Statement.UsingStatementSyntax node visiting.
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public virtual void visit(Columbus.Csharp.Asg.Nodes.Statement.UsingStatementSyntax node, bool callVirtualBase = true) { }

        /// <summary>
        /// Visitor which is called at the end of the Columbus.Csharp.Asg.Nodes.Statement.UsingStatementSyntax node visiting.
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public virtual void visitEnd(Columbus.Csharp.Asg.Nodes.Statement.UsingStatementSyntax node, bool callVirtualBase = true) { }

        /// <summary>
        /// Visitor which is called at the beginning of the Columbus.Csharp.Asg.Nodes.Statement.WhileStatementSyntax node visiting.
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public virtual void visit(Columbus.Csharp.Asg.Nodes.Statement.WhileStatementSyntax node, bool callVirtualBase = true) { }

        /// <summary>
        /// Visitor which is called at the end of the Columbus.Csharp.Asg.Nodes.Statement.WhileStatementSyntax node visiting.
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public virtual void visitEnd(Columbus.Csharp.Asg.Nodes.Statement.WhileStatementSyntax node, bool callVirtualBase = true) { }

        /// <summary>
        /// Visitor which is called at the beginning of the Columbus.Csharp.Asg.Nodes.Statement.YieldStatementSyntax node visiting.
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public virtual void visit(Columbus.Csharp.Asg.Nodes.Statement.YieldStatementSyntax node, bool callVirtualBase = true) { }

        /// <summary>
        /// Visitor which is called at the end of the Columbus.Csharp.Asg.Nodes.Statement.YieldStatementSyntax node visiting.
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public virtual void visitEnd(Columbus.Csharp.Asg.Nodes.Statement.YieldStatementSyntax node, bool callVirtualBase = true) { }

        /// <summary>
        /// Visitor which is called at the beginning of the Columbus.Csharp.Asg.Nodes.Structure.AccessorDeclarationSyntax node visiting.
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public virtual void visit(Columbus.Csharp.Asg.Nodes.Structure.AccessorDeclarationSyntax node, bool callVirtualBase = true) { }

        /// <summary>
        /// Visitor which is called at the end of the Columbus.Csharp.Asg.Nodes.Structure.AccessorDeclarationSyntax node visiting.
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public virtual void visitEnd(Columbus.Csharp.Asg.Nodes.Structure.AccessorDeclarationSyntax node, bool callVirtualBase = true) { }

        /// <summary>
        /// Visitor which is called at the beginning of the Columbus.Csharp.Asg.Nodes.Structure.AccessorListSyntax node visiting.
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public virtual void visit(Columbus.Csharp.Asg.Nodes.Structure.AccessorListSyntax node, bool callVirtualBase = true) { }

        /// <summary>
        /// Visitor which is called at the end of the Columbus.Csharp.Asg.Nodes.Structure.AccessorListSyntax node visiting.
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public virtual void visitEnd(Columbus.Csharp.Asg.Nodes.Structure.AccessorListSyntax node, bool callVirtualBase = true) { }

        /// <summary>
        /// Visitor which is called at the beginning of the Columbus.Csharp.Asg.Nodes.Structure.AnonymousObjectMemberDeclaratorSyntax node visiting.
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public virtual void visit(Columbus.Csharp.Asg.Nodes.Structure.AnonymousObjectMemberDeclaratorSyntax node, bool callVirtualBase = true) { }

        /// <summary>
        /// Visitor which is called at the end of the Columbus.Csharp.Asg.Nodes.Structure.AnonymousObjectMemberDeclaratorSyntax node visiting.
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public virtual void visitEnd(Columbus.Csharp.Asg.Nodes.Structure.AnonymousObjectMemberDeclaratorSyntax node, bool callVirtualBase = true) { }

        /// <summary>
        /// Visitor which is called at the beginning of the Columbus.Csharp.Asg.Nodes.Structure.ArgumentListSyntax node visiting.
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public virtual void visit(Columbus.Csharp.Asg.Nodes.Structure.ArgumentListSyntax node, bool callVirtualBase = true) { }

        /// <summary>
        /// Visitor which is called at the end of the Columbus.Csharp.Asg.Nodes.Structure.ArgumentListSyntax node visiting.
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public virtual void visitEnd(Columbus.Csharp.Asg.Nodes.Structure.ArgumentListSyntax node, bool callVirtualBase = true) { }

        /// <summary>
        /// Visitor which is called at the beginning of the Columbus.Csharp.Asg.Nodes.Structure.ArgumentSyntax node visiting.
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public virtual void visit(Columbus.Csharp.Asg.Nodes.Structure.ArgumentSyntax node, bool callVirtualBase = true) { }

        /// <summary>
        /// Visitor which is called at the end of the Columbus.Csharp.Asg.Nodes.Structure.ArgumentSyntax node visiting.
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public virtual void visitEnd(Columbus.Csharp.Asg.Nodes.Structure.ArgumentSyntax node, bool callVirtualBase = true) { }

        /// <summary>
        /// Visitor which is called at the beginning of the Columbus.Csharp.Asg.Nodes.Structure.ArrayRankSpecifierSyntax node visiting.
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public virtual void visit(Columbus.Csharp.Asg.Nodes.Structure.ArrayRankSpecifierSyntax node, bool callVirtualBase = true) { }

        /// <summary>
        /// Visitor which is called at the end of the Columbus.Csharp.Asg.Nodes.Structure.ArrayRankSpecifierSyntax node visiting.
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public virtual void visitEnd(Columbus.Csharp.Asg.Nodes.Structure.ArrayRankSpecifierSyntax node, bool callVirtualBase = true) { }

        /// <summary>
        /// Visitor which is called at the beginning of the Columbus.Csharp.Asg.Nodes.Structure.ArrowExpressionClauseSyntax node visiting.
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public virtual void visit(Columbus.Csharp.Asg.Nodes.Structure.ArrowExpressionClauseSyntax node, bool callVirtualBase = true) { }

        /// <summary>
        /// Visitor which is called at the end of the Columbus.Csharp.Asg.Nodes.Structure.ArrowExpressionClauseSyntax node visiting.
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public virtual void visitEnd(Columbus.Csharp.Asg.Nodes.Structure.ArrowExpressionClauseSyntax node, bool callVirtualBase = true) { }

        /// <summary>
        /// Visitor which is called at the beginning of the Columbus.Csharp.Asg.Nodes.Structure.AttributeArgumentListSyntax node visiting.
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public virtual void visit(Columbus.Csharp.Asg.Nodes.Structure.AttributeArgumentListSyntax node, bool callVirtualBase = true) { }

        /// <summary>
        /// Visitor which is called at the end of the Columbus.Csharp.Asg.Nodes.Structure.AttributeArgumentListSyntax node visiting.
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public virtual void visitEnd(Columbus.Csharp.Asg.Nodes.Structure.AttributeArgumentListSyntax node, bool callVirtualBase = true) { }

        /// <summary>
        /// Visitor which is called at the beginning of the Columbus.Csharp.Asg.Nodes.Structure.AttributeArgumentSyntax node visiting.
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public virtual void visit(Columbus.Csharp.Asg.Nodes.Structure.AttributeArgumentSyntax node, bool callVirtualBase = true) { }

        /// <summary>
        /// Visitor which is called at the end of the Columbus.Csharp.Asg.Nodes.Structure.AttributeArgumentSyntax node visiting.
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public virtual void visitEnd(Columbus.Csharp.Asg.Nodes.Structure.AttributeArgumentSyntax node, bool callVirtualBase = true) { }

        /// <summary>
        /// Visitor which is called at the beginning of the Columbus.Csharp.Asg.Nodes.Structure.AttributeListSyntax node visiting.
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public virtual void visit(Columbus.Csharp.Asg.Nodes.Structure.AttributeListSyntax node, bool callVirtualBase = true) { }

        /// <summary>
        /// Visitor which is called at the end of the Columbus.Csharp.Asg.Nodes.Structure.AttributeListSyntax node visiting.
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public virtual void visitEnd(Columbus.Csharp.Asg.Nodes.Structure.AttributeListSyntax node, bool callVirtualBase = true) { }

        /// <summary>
        /// Visitor which is called at the beginning of the Columbus.Csharp.Asg.Nodes.Structure.AttributeSyntax node visiting.
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public virtual void visit(Columbus.Csharp.Asg.Nodes.Structure.AttributeSyntax node, bool callVirtualBase = true) { }

        /// <summary>
        /// Visitor which is called at the end of the Columbus.Csharp.Asg.Nodes.Structure.AttributeSyntax node visiting.
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public virtual void visitEnd(Columbus.Csharp.Asg.Nodes.Structure.AttributeSyntax node, bool callVirtualBase = true) { }

        /// <summary>
        /// Visitor which is called at the beginning of the Columbus.Csharp.Asg.Nodes.Structure.AttributeTargetSpecifierSyntax node visiting.
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public virtual void visit(Columbus.Csharp.Asg.Nodes.Structure.AttributeTargetSpecifierSyntax node, bool callVirtualBase = true) { }

        /// <summary>
        /// Visitor which is called at the end of the Columbus.Csharp.Asg.Nodes.Structure.AttributeTargetSpecifierSyntax node visiting.
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public virtual void visitEnd(Columbus.Csharp.Asg.Nodes.Structure.AttributeTargetSpecifierSyntax node, bool callVirtualBase = true) { }

        /// <summary>
        /// Visitor which is called at the beginning of the Columbus.Csharp.Asg.Nodes.Structure.BaseListSyntax node visiting.
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public virtual void visit(Columbus.Csharp.Asg.Nodes.Structure.BaseListSyntax node, bool callVirtualBase = true) { }

        /// <summary>
        /// Visitor which is called at the end of the Columbus.Csharp.Asg.Nodes.Structure.BaseListSyntax node visiting.
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public virtual void visitEnd(Columbus.Csharp.Asg.Nodes.Structure.BaseListSyntax node, bool callVirtualBase = true) { }

        /// <summary>
        /// Visitor which is called at the beginning of the Columbus.Csharp.Asg.Nodes.Structure.BracketedArgumentListSyntax node visiting.
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public virtual void visit(Columbus.Csharp.Asg.Nodes.Structure.BracketedArgumentListSyntax node, bool callVirtualBase = true) { }

        /// <summary>
        /// Visitor which is called at the end of the Columbus.Csharp.Asg.Nodes.Structure.BracketedArgumentListSyntax node visiting.
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public virtual void visitEnd(Columbus.Csharp.Asg.Nodes.Structure.BracketedArgumentListSyntax node, bool callVirtualBase = true) { }

        /// <summary>
        /// Visitor which is called at the beginning of the Columbus.Csharp.Asg.Nodes.Structure.BracketedParameterListSyntax node visiting.
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public virtual void visit(Columbus.Csharp.Asg.Nodes.Structure.BracketedParameterListSyntax node, bool callVirtualBase = true) { }

        /// <summary>
        /// Visitor which is called at the end of the Columbus.Csharp.Asg.Nodes.Structure.BracketedParameterListSyntax node visiting.
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public virtual void visitEnd(Columbus.Csharp.Asg.Nodes.Structure.BracketedParameterListSyntax node, bool callVirtualBase = true) { }

        /// <summary>
        /// Visitor which is called at the beginning of the Columbus.Csharp.Asg.Nodes.Structure.CaseSwitchLabelSyntax node visiting.
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public virtual void visit(Columbus.Csharp.Asg.Nodes.Structure.CaseSwitchLabelSyntax node, bool callVirtualBase = true) { }

        /// <summary>
        /// Visitor which is called at the end of the Columbus.Csharp.Asg.Nodes.Structure.CaseSwitchLabelSyntax node visiting.
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public virtual void visitEnd(Columbus.Csharp.Asg.Nodes.Structure.CaseSwitchLabelSyntax node, bool callVirtualBase = true) { }

        /// <summary>
        /// Visitor which is called at the beginning of the Columbus.Csharp.Asg.Nodes.Structure.CatchClauseSyntax node visiting.
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public virtual void visit(Columbus.Csharp.Asg.Nodes.Structure.CatchClauseSyntax node, bool callVirtualBase = true) { }

        /// <summary>
        /// Visitor which is called at the end of the Columbus.Csharp.Asg.Nodes.Structure.CatchClauseSyntax node visiting.
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public virtual void visitEnd(Columbus.Csharp.Asg.Nodes.Structure.CatchClauseSyntax node, bool callVirtualBase = true) { }

        /// <summary>
        /// Visitor which is called at the beginning of the Columbus.Csharp.Asg.Nodes.Structure.CatchDeclarationSyntax node visiting.
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public virtual void visit(Columbus.Csharp.Asg.Nodes.Structure.CatchDeclarationSyntax node, bool callVirtualBase = true) { }

        /// <summary>
        /// Visitor which is called at the end of the Columbus.Csharp.Asg.Nodes.Structure.CatchDeclarationSyntax node visiting.
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public virtual void visitEnd(Columbus.Csharp.Asg.Nodes.Structure.CatchDeclarationSyntax node, bool callVirtualBase = true) { }

        /// <summary>
        /// Visitor which is called at the beginning of the Columbus.Csharp.Asg.Nodes.Structure.CatchFilterClauseSyntax node visiting.
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public virtual void visit(Columbus.Csharp.Asg.Nodes.Structure.CatchFilterClauseSyntax node, bool callVirtualBase = true) { }

        /// <summary>
        /// Visitor which is called at the end of the Columbus.Csharp.Asg.Nodes.Structure.CatchFilterClauseSyntax node visiting.
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public virtual void visitEnd(Columbus.Csharp.Asg.Nodes.Structure.CatchFilterClauseSyntax node, bool callVirtualBase = true) { }

        /// <summary>
        /// Visitor which is called at the beginning of the Columbus.Csharp.Asg.Nodes.Structure.ClassDeclarationSyntax node visiting.
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public virtual void visit(Columbus.Csharp.Asg.Nodes.Structure.ClassDeclarationSyntax node, bool callVirtualBase = true) { }

        /// <summary>
        /// Visitor which is called at the end of the Columbus.Csharp.Asg.Nodes.Structure.ClassDeclarationSyntax node visiting.
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public virtual void visitEnd(Columbus.Csharp.Asg.Nodes.Structure.ClassDeclarationSyntax node, bool callVirtualBase = true) { }

        /// <summary>
        /// Visitor which is called at the beginning of the Columbus.Csharp.Asg.Nodes.Structure.ClassOrStructConstraintSyntax node visiting.
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public virtual void visit(Columbus.Csharp.Asg.Nodes.Structure.ClassOrStructConstraintSyntax node, bool callVirtualBase = true) { }

        /// <summary>
        /// Visitor which is called at the end of the Columbus.Csharp.Asg.Nodes.Structure.ClassOrStructConstraintSyntax node visiting.
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public virtual void visitEnd(Columbus.Csharp.Asg.Nodes.Structure.ClassOrStructConstraintSyntax node, bool callVirtualBase = true) { }

        /// <summary>
        /// Visitor which is called at the beginning of the Columbus.Csharp.Asg.Nodes.Structure.CompilationUnitSyntax node visiting.
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public virtual void visit(Columbus.Csharp.Asg.Nodes.Structure.CompilationUnitSyntax node, bool callVirtualBase = true) { }

        /// <summary>
        /// Visitor which is called at the end of the Columbus.Csharp.Asg.Nodes.Structure.CompilationUnitSyntax node visiting.
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public virtual void visitEnd(Columbus.Csharp.Asg.Nodes.Structure.CompilationUnitSyntax node, bool callVirtualBase = true) { }

        /// <summary>
        /// Visitor which is called at the beginning of the Columbus.Csharp.Asg.Nodes.Structure.ConstructorConstraintSyntax node visiting.
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public virtual void visit(Columbus.Csharp.Asg.Nodes.Structure.ConstructorConstraintSyntax node, bool callVirtualBase = true) { }

        /// <summary>
        /// Visitor which is called at the end of the Columbus.Csharp.Asg.Nodes.Structure.ConstructorConstraintSyntax node visiting.
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public virtual void visitEnd(Columbus.Csharp.Asg.Nodes.Structure.ConstructorConstraintSyntax node, bool callVirtualBase = true) { }

        /// <summary>
        /// Visitor which is called at the beginning of the Columbus.Csharp.Asg.Nodes.Structure.ConstructorDeclarationSyntax node visiting.
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public virtual void visit(Columbus.Csharp.Asg.Nodes.Structure.ConstructorDeclarationSyntax node, bool callVirtualBase = true) { }

        /// <summary>
        /// Visitor which is called at the end of the Columbus.Csharp.Asg.Nodes.Structure.ConstructorDeclarationSyntax node visiting.
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public virtual void visitEnd(Columbus.Csharp.Asg.Nodes.Structure.ConstructorDeclarationSyntax node, bool callVirtualBase = true) { }

        /// <summary>
        /// Visitor which is called at the beginning of the Columbus.Csharp.Asg.Nodes.Structure.ConstructorInitializerSyntax node visiting.
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public virtual void visit(Columbus.Csharp.Asg.Nodes.Structure.ConstructorInitializerSyntax node, bool callVirtualBase = true) { }

        /// <summary>
        /// Visitor which is called at the end of the Columbus.Csharp.Asg.Nodes.Structure.ConstructorInitializerSyntax node visiting.
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public virtual void visitEnd(Columbus.Csharp.Asg.Nodes.Structure.ConstructorInitializerSyntax node, bool callVirtualBase = true) { }

        /// <summary>
        /// Visitor which is called at the beginning of the Columbus.Csharp.Asg.Nodes.Structure.ConversionOperatorDeclarationSyntax node visiting.
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public virtual void visit(Columbus.Csharp.Asg.Nodes.Structure.ConversionOperatorDeclarationSyntax node, bool callVirtualBase = true) { }

        /// <summary>
        /// Visitor which is called at the end of the Columbus.Csharp.Asg.Nodes.Structure.ConversionOperatorDeclarationSyntax node visiting.
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public virtual void visitEnd(Columbus.Csharp.Asg.Nodes.Structure.ConversionOperatorDeclarationSyntax node, bool callVirtualBase = true) { }

        /// <summary>
        /// Visitor which is called at the beginning of the Columbus.Csharp.Asg.Nodes.Structure.ConversionOperatorMemberCrefSyntax node visiting.
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public virtual void visit(Columbus.Csharp.Asg.Nodes.Structure.ConversionOperatorMemberCrefSyntax node, bool callVirtualBase = true) { }

        /// <summary>
        /// Visitor which is called at the end of the Columbus.Csharp.Asg.Nodes.Structure.ConversionOperatorMemberCrefSyntax node visiting.
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public virtual void visitEnd(Columbus.Csharp.Asg.Nodes.Structure.ConversionOperatorMemberCrefSyntax node, bool callVirtualBase = true) { }

        /// <summary>
        /// Visitor which is called at the beginning of the Columbus.Csharp.Asg.Nodes.Structure.CrefBracketedParameterListSyntax node visiting.
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public virtual void visit(Columbus.Csharp.Asg.Nodes.Structure.CrefBracketedParameterListSyntax node, bool callVirtualBase = true) { }

        /// <summary>
        /// Visitor which is called at the end of the Columbus.Csharp.Asg.Nodes.Structure.CrefBracketedParameterListSyntax node visiting.
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public virtual void visitEnd(Columbus.Csharp.Asg.Nodes.Structure.CrefBracketedParameterListSyntax node, bool callVirtualBase = true) { }

        /// <summary>
        /// Visitor which is called at the beginning of the Columbus.Csharp.Asg.Nodes.Structure.CrefParameterListSyntax node visiting.
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public virtual void visit(Columbus.Csharp.Asg.Nodes.Structure.CrefParameterListSyntax node, bool callVirtualBase = true) { }

        /// <summary>
        /// Visitor which is called at the end of the Columbus.Csharp.Asg.Nodes.Structure.CrefParameterListSyntax node visiting.
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public virtual void visitEnd(Columbus.Csharp.Asg.Nodes.Structure.CrefParameterListSyntax node, bool callVirtualBase = true) { }

        /// <summary>
        /// Visitor which is called at the beginning of the Columbus.Csharp.Asg.Nodes.Structure.CrefParameterSyntax node visiting.
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public virtual void visit(Columbus.Csharp.Asg.Nodes.Structure.CrefParameterSyntax node, bool callVirtualBase = true) { }

        /// <summary>
        /// Visitor which is called at the end of the Columbus.Csharp.Asg.Nodes.Structure.CrefParameterSyntax node visiting.
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public virtual void visitEnd(Columbus.Csharp.Asg.Nodes.Structure.CrefParameterSyntax node, bool callVirtualBase = true) { }

        /// <summary>
        /// Visitor which is called at the beginning of the Columbus.Csharp.Asg.Nodes.Structure.DefaultSwitchLabelSyntax node visiting.
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public virtual void visit(Columbus.Csharp.Asg.Nodes.Structure.DefaultSwitchLabelSyntax node, bool callVirtualBase = true) { }

        /// <summary>
        /// Visitor which is called at the end of the Columbus.Csharp.Asg.Nodes.Structure.DefaultSwitchLabelSyntax node visiting.
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public virtual void visitEnd(Columbus.Csharp.Asg.Nodes.Structure.DefaultSwitchLabelSyntax node, bool callVirtualBase = true) { }

        /// <summary>
        /// Visitor which is called at the beginning of the Columbus.Csharp.Asg.Nodes.Structure.DelegateDeclarationSyntax node visiting.
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public virtual void visit(Columbus.Csharp.Asg.Nodes.Structure.DelegateDeclarationSyntax node, bool callVirtualBase = true) { }

        /// <summary>
        /// Visitor which is called at the end of the Columbus.Csharp.Asg.Nodes.Structure.DelegateDeclarationSyntax node visiting.
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public virtual void visitEnd(Columbus.Csharp.Asg.Nodes.Structure.DelegateDeclarationSyntax node, bool callVirtualBase = true) { }

        /// <summary>
        /// Visitor which is called at the beginning of the Columbus.Csharp.Asg.Nodes.Structure.DestructorDeclarationSyntax node visiting.
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public virtual void visit(Columbus.Csharp.Asg.Nodes.Structure.DestructorDeclarationSyntax node, bool callVirtualBase = true) { }

        /// <summary>
        /// Visitor which is called at the end of the Columbus.Csharp.Asg.Nodes.Structure.DestructorDeclarationSyntax node visiting.
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public virtual void visitEnd(Columbus.Csharp.Asg.Nodes.Structure.DestructorDeclarationSyntax node, bool callVirtualBase = true) { }

        /// <summary>
        /// Visitor which is called at the beginning of the Columbus.Csharp.Asg.Nodes.Structure.ElseClauseSyntax node visiting.
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public virtual void visit(Columbus.Csharp.Asg.Nodes.Structure.ElseClauseSyntax node, bool callVirtualBase = true) { }

        /// <summary>
        /// Visitor which is called at the end of the Columbus.Csharp.Asg.Nodes.Structure.ElseClauseSyntax node visiting.
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public virtual void visitEnd(Columbus.Csharp.Asg.Nodes.Structure.ElseClauseSyntax node, bool callVirtualBase = true) { }

        /// <summary>
        /// Visitor which is called at the beginning of the Columbus.Csharp.Asg.Nodes.Structure.EnumDeclarationSyntax node visiting.
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public virtual void visit(Columbus.Csharp.Asg.Nodes.Structure.EnumDeclarationSyntax node, bool callVirtualBase = true) { }

        /// <summary>
        /// Visitor which is called at the end of the Columbus.Csharp.Asg.Nodes.Structure.EnumDeclarationSyntax node visiting.
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public virtual void visitEnd(Columbus.Csharp.Asg.Nodes.Structure.EnumDeclarationSyntax node, bool callVirtualBase = true) { }

        /// <summary>
        /// Visitor which is called at the beginning of the Columbus.Csharp.Asg.Nodes.Structure.EnumMemberDeclarationSyntax node visiting.
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public virtual void visit(Columbus.Csharp.Asg.Nodes.Structure.EnumMemberDeclarationSyntax node, bool callVirtualBase = true) { }

        /// <summary>
        /// Visitor which is called at the end of the Columbus.Csharp.Asg.Nodes.Structure.EnumMemberDeclarationSyntax node visiting.
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public virtual void visitEnd(Columbus.Csharp.Asg.Nodes.Structure.EnumMemberDeclarationSyntax node, bool callVirtualBase = true) { }

        /// <summary>
        /// Visitor which is called at the beginning of the Columbus.Csharp.Asg.Nodes.Structure.EqualsValueClauseSyntax node visiting.
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public virtual void visit(Columbus.Csharp.Asg.Nodes.Structure.EqualsValueClauseSyntax node, bool callVirtualBase = true) { }

        /// <summary>
        /// Visitor which is called at the end of the Columbus.Csharp.Asg.Nodes.Structure.EqualsValueClauseSyntax node visiting.
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public virtual void visitEnd(Columbus.Csharp.Asg.Nodes.Structure.EqualsValueClauseSyntax node, bool callVirtualBase = true) { }

        /// <summary>
        /// Visitor which is called at the beginning of the Columbus.Csharp.Asg.Nodes.Structure.EventDeclarationSyntax node visiting.
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public virtual void visit(Columbus.Csharp.Asg.Nodes.Structure.EventDeclarationSyntax node, bool callVirtualBase = true) { }

        /// <summary>
        /// Visitor which is called at the end of the Columbus.Csharp.Asg.Nodes.Structure.EventDeclarationSyntax node visiting.
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public virtual void visitEnd(Columbus.Csharp.Asg.Nodes.Structure.EventDeclarationSyntax node, bool callVirtualBase = true) { }

        /// <summary>
        /// Visitor which is called at the beginning of the Columbus.Csharp.Asg.Nodes.Structure.EventFieldDeclarationSyntax node visiting.
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public virtual void visit(Columbus.Csharp.Asg.Nodes.Structure.EventFieldDeclarationSyntax node, bool callVirtualBase = true) { }

        /// <summary>
        /// Visitor which is called at the end of the Columbus.Csharp.Asg.Nodes.Structure.EventFieldDeclarationSyntax node visiting.
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public virtual void visitEnd(Columbus.Csharp.Asg.Nodes.Structure.EventFieldDeclarationSyntax node, bool callVirtualBase = true) { }

        /// <summary>
        /// Visitor which is called at the beginning of the Columbus.Csharp.Asg.Nodes.Structure.ExplicitInterfaceSpecifierSyntax node visiting.
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public virtual void visit(Columbus.Csharp.Asg.Nodes.Structure.ExplicitInterfaceSpecifierSyntax node, bool callVirtualBase = true) { }

        /// <summary>
        /// Visitor which is called at the end of the Columbus.Csharp.Asg.Nodes.Structure.ExplicitInterfaceSpecifierSyntax node visiting.
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public virtual void visitEnd(Columbus.Csharp.Asg.Nodes.Structure.ExplicitInterfaceSpecifierSyntax node, bool callVirtualBase = true) { }

        /// <summary>
        /// Visitor which is called at the beginning of the Columbus.Csharp.Asg.Nodes.Structure.ExternAliasDirectiveSyntax node visiting.
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public virtual void visit(Columbus.Csharp.Asg.Nodes.Structure.ExternAliasDirectiveSyntax node, bool callVirtualBase = true) { }

        /// <summary>
        /// Visitor which is called at the end of the Columbus.Csharp.Asg.Nodes.Structure.ExternAliasDirectiveSyntax node visiting.
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public virtual void visitEnd(Columbus.Csharp.Asg.Nodes.Structure.ExternAliasDirectiveSyntax node, bool callVirtualBase = true) { }

        /// <summary>
        /// Visitor which is called at the beginning of the Columbus.Csharp.Asg.Nodes.Structure.FieldDeclarationSyntax node visiting.
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public virtual void visit(Columbus.Csharp.Asg.Nodes.Structure.FieldDeclarationSyntax node, bool callVirtualBase = true) { }

        /// <summary>
        /// Visitor which is called at the end of the Columbus.Csharp.Asg.Nodes.Structure.FieldDeclarationSyntax node visiting.
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public virtual void visitEnd(Columbus.Csharp.Asg.Nodes.Structure.FieldDeclarationSyntax node, bool callVirtualBase = true) { }

        /// <summary>
        /// Visitor which is called at the beginning of the Columbus.Csharp.Asg.Nodes.Structure.FinallyClauseSyntax node visiting.
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public virtual void visit(Columbus.Csharp.Asg.Nodes.Structure.FinallyClauseSyntax node, bool callVirtualBase = true) { }

        /// <summary>
        /// Visitor which is called at the end of the Columbus.Csharp.Asg.Nodes.Structure.FinallyClauseSyntax node visiting.
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public virtual void visitEnd(Columbus.Csharp.Asg.Nodes.Structure.FinallyClauseSyntax node, bool callVirtualBase = true) { }

        /// <summary>
        /// Visitor which is called at the beginning of the Columbus.Csharp.Asg.Nodes.Structure.FromClauseSyntax node visiting.
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public virtual void visit(Columbus.Csharp.Asg.Nodes.Structure.FromClauseSyntax node, bool callVirtualBase = true) { }

        /// <summary>
        /// Visitor which is called at the end of the Columbus.Csharp.Asg.Nodes.Structure.FromClauseSyntax node visiting.
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public virtual void visitEnd(Columbus.Csharp.Asg.Nodes.Structure.FromClauseSyntax node, bool callVirtualBase = true) { }

        /// <summary>
        /// Visitor which is called at the beginning of the Columbus.Csharp.Asg.Nodes.Structure.GlobalStatementSyntax node visiting.
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public virtual void visit(Columbus.Csharp.Asg.Nodes.Structure.GlobalStatementSyntax node, bool callVirtualBase = true) { }

        /// <summary>
        /// Visitor which is called at the end of the Columbus.Csharp.Asg.Nodes.Structure.GlobalStatementSyntax node visiting.
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public virtual void visitEnd(Columbus.Csharp.Asg.Nodes.Structure.GlobalStatementSyntax node, bool callVirtualBase = true) { }

        /// <summary>
        /// Visitor which is called at the beginning of the Columbus.Csharp.Asg.Nodes.Structure.GroupClauseSyntax node visiting.
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public virtual void visit(Columbus.Csharp.Asg.Nodes.Structure.GroupClauseSyntax node, bool callVirtualBase = true) { }

        /// <summary>
        /// Visitor which is called at the end of the Columbus.Csharp.Asg.Nodes.Structure.GroupClauseSyntax node visiting.
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public virtual void visitEnd(Columbus.Csharp.Asg.Nodes.Structure.GroupClauseSyntax node, bool callVirtualBase = true) { }

        /// <summary>
        /// Visitor which is called at the beginning of the Columbus.Csharp.Asg.Nodes.Structure.IncompleteMemberSyntax node visiting.
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public virtual void visit(Columbus.Csharp.Asg.Nodes.Structure.IncompleteMemberSyntax node, bool callVirtualBase = true) { }

        /// <summary>
        /// Visitor which is called at the end of the Columbus.Csharp.Asg.Nodes.Structure.IncompleteMemberSyntax node visiting.
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public virtual void visitEnd(Columbus.Csharp.Asg.Nodes.Structure.IncompleteMemberSyntax node, bool callVirtualBase = true) { }

        /// <summary>
        /// Visitor which is called at the beginning of the Columbus.Csharp.Asg.Nodes.Structure.IndexerDeclarationSyntax node visiting.
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public virtual void visit(Columbus.Csharp.Asg.Nodes.Structure.IndexerDeclarationSyntax node, bool callVirtualBase = true) { }

        /// <summary>
        /// Visitor which is called at the end of the Columbus.Csharp.Asg.Nodes.Structure.IndexerDeclarationSyntax node visiting.
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public virtual void visitEnd(Columbus.Csharp.Asg.Nodes.Structure.IndexerDeclarationSyntax node, bool callVirtualBase = true) { }

        /// <summary>
        /// Visitor which is called at the beginning of the Columbus.Csharp.Asg.Nodes.Structure.IndexerMemberCrefSyntax node visiting.
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public virtual void visit(Columbus.Csharp.Asg.Nodes.Structure.IndexerMemberCrefSyntax node, bool callVirtualBase = true) { }

        /// <summary>
        /// Visitor which is called at the end of the Columbus.Csharp.Asg.Nodes.Structure.IndexerMemberCrefSyntax node visiting.
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public virtual void visitEnd(Columbus.Csharp.Asg.Nodes.Structure.IndexerMemberCrefSyntax node, bool callVirtualBase = true) { }

        /// <summary>
        /// Visitor which is called at the beginning of the Columbus.Csharp.Asg.Nodes.Structure.InterfaceDeclarationSyntax node visiting.
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public virtual void visit(Columbus.Csharp.Asg.Nodes.Structure.InterfaceDeclarationSyntax node, bool callVirtualBase = true) { }

        /// <summary>
        /// Visitor which is called at the end of the Columbus.Csharp.Asg.Nodes.Structure.InterfaceDeclarationSyntax node visiting.
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public virtual void visitEnd(Columbus.Csharp.Asg.Nodes.Structure.InterfaceDeclarationSyntax node, bool callVirtualBase = true) { }

        /// <summary>
        /// Visitor which is called at the beginning of the Columbus.Csharp.Asg.Nodes.Structure.InterpolatedStringTextSyntax node visiting.
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public virtual void visit(Columbus.Csharp.Asg.Nodes.Structure.InterpolatedStringTextSyntax node, bool callVirtualBase = true) { }

        /// <summary>
        /// Visitor which is called at the end of the Columbus.Csharp.Asg.Nodes.Structure.InterpolatedStringTextSyntax node visiting.
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public virtual void visitEnd(Columbus.Csharp.Asg.Nodes.Structure.InterpolatedStringTextSyntax node, bool callVirtualBase = true) { }

        /// <summary>
        /// Visitor which is called at the beginning of the Columbus.Csharp.Asg.Nodes.Structure.InterpolationAlignmentClauseSyntax node visiting.
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public virtual void visit(Columbus.Csharp.Asg.Nodes.Structure.InterpolationAlignmentClauseSyntax node, bool callVirtualBase = true) { }

        /// <summary>
        /// Visitor which is called at the end of the Columbus.Csharp.Asg.Nodes.Structure.InterpolationAlignmentClauseSyntax node visiting.
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public virtual void visitEnd(Columbus.Csharp.Asg.Nodes.Structure.InterpolationAlignmentClauseSyntax node, bool callVirtualBase = true) { }

        /// <summary>
        /// Visitor which is called at the beginning of the Columbus.Csharp.Asg.Nodes.Structure.InterpolationFormatClauseSyntax node visiting.
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public virtual void visit(Columbus.Csharp.Asg.Nodes.Structure.InterpolationFormatClauseSyntax node, bool callVirtualBase = true) { }

        /// <summary>
        /// Visitor which is called at the end of the Columbus.Csharp.Asg.Nodes.Structure.InterpolationFormatClauseSyntax node visiting.
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public virtual void visitEnd(Columbus.Csharp.Asg.Nodes.Structure.InterpolationFormatClauseSyntax node, bool callVirtualBase = true) { }

        /// <summary>
        /// Visitor which is called at the beginning of the Columbus.Csharp.Asg.Nodes.Structure.InterpolationSyntax node visiting.
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public virtual void visit(Columbus.Csharp.Asg.Nodes.Structure.InterpolationSyntax node, bool callVirtualBase = true) { }

        /// <summary>
        /// Visitor which is called at the end of the Columbus.Csharp.Asg.Nodes.Structure.InterpolationSyntax node visiting.
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public virtual void visitEnd(Columbus.Csharp.Asg.Nodes.Structure.InterpolationSyntax node, bool callVirtualBase = true) { }

        /// <summary>
        /// Visitor which is called at the beginning of the Columbus.Csharp.Asg.Nodes.Structure.JoinClauseSyntax node visiting.
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public virtual void visit(Columbus.Csharp.Asg.Nodes.Structure.JoinClauseSyntax node, bool callVirtualBase = true) { }

        /// <summary>
        /// Visitor which is called at the end of the Columbus.Csharp.Asg.Nodes.Structure.JoinClauseSyntax node visiting.
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public virtual void visitEnd(Columbus.Csharp.Asg.Nodes.Structure.JoinClauseSyntax node, bool callVirtualBase = true) { }

        /// <summary>
        /// Visitor which is called at the beginning of the Columbus.Csharp.Asg.Nodes.Structure.JoinIntoClauseSyntax node visiting.
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public virtual void visit(Columbus.Csharp.Asg.Nodes.Structure.JoinIntoClauseSyntax node, bool callVirtualBase = true) { }

        /// <summary>
        /// Visitor which is called at the end of the Columbus.Csharp.Asg.Nodes.Structure.JoinIntoClauseSyntax node visiting.
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public virtual void visitEnd(Columbus.Csharp.Asg.Nodes.Structure.JoinIntoClauseSyntax node, bool callVirtualBase = true) { }

        /// <summary>
        /// Visitor which is called at the beginning of the Columbus.Csharp.Asg.Nodes.Structure.LetClauseSyntax node visiting.
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public virtual void visit(Columbus.Csharp.Asg.Nodes.Structure.LetClauseSyntax node, bool callVirtualBase = true) { }

        /// <summary>
        /// Visitor which is called at the end of the Columbus.Csharp.Asg.Nodes.Structure.LetClauseSyntax node visiting.
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public virtual void visitEnd(Columbus.Csharp.Asg.Nodes.Structure.LetClauseSyntax node, bool callVirtualBase = true) { }

        /// <summary>
        /// Visitor which is called at the beginning of the Columbus.Csharp.Asg.Nodes.Structure.MethodDeclarationSyntax node visiting.
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public virtual void visit(Columbus.Csharp.Asg.Nodes.Structure.MethodDeclarationSyntax node, bool callVirtualBase = true) { }

        /// <summary>
        /// Visitor which is called at the end of the Columbus.Csharp.Asg.Nodes.Structure.MethodDeclarationSyntax node visiting.
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public virtual void visitEnd(Columbus.Csharp.Asg.Nodes.Structure.MethodDeclarationSyntax node, bool callVirtualBase = true) { }

        /// <summary>
        /// Visitor which is called at the beginning of the Columbus.Csharp.Asg.Nodes.Structure.NameColonSyntax node visiting.
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public virtual void visit(Columbus.Csharp.Asg.Nodes.Structure.NameColonSyntax node, bool callVirtualBase = true) { }

        /// <summary>
        /// Visitor which is called at the end of the Columbus.Csharp.Asg.Nodes.Structure.NameColonSyntax node visiting.
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public virtual void visitEnd(Columbus.Csharp.Asg.Nodes.Structure.NameColonSyntax node, bool callVirtualBase = true) { }

        /// <summary>
        /// Visitor which is called at the beginning of the Columbus.Csharp.Asg.Nodes.Structure.NameEqualsSyntax node visiting.
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public virtual void visit(Columbus.Csharp.Asg.Nodes.Structure.NameEqualsSyntax node, bool callVirtualBase = true) { }

        /// <summary>
        /// Visitor which is called at the end of the Columbus.Csharp.Asg.Nodes.Structure.NameEqualsSyntax node visiting.
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public virtual void visitEnd(Columbus.Csharp.Asg.Nodes.Structure.NameEqualsSyntax node, bool callVirtualBase = true) { }

        /// <summary>
        /// Visitor which is called at the beginning of the Columbus.Csharp.Asg.Nodes.Structure.NameMemberCrefSyntax node visiting.
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public virtual void visit(Columbus.Csharp.Asg.Nodes.Structure.NameMemberCrefSyntax node, bool callVirtualBase = true) { }

        /// <summary>
        /// Visitor which is called at the end of the Columbus.Csharp.Asg.Nodes.Structure.NameMemberCrefSyntax node visiting.
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public virtual void visitEnd(Columbus.Csharp.Asg.Nodes.Structure.NameMemberCrefSyntax node, bool callVirtualBase = true) { }

        /// <summary>
        /// Visitor which is called at the beginning of the Columbus.Csharp.Asg.Nodes.Structure.NamespaceDeclarationSyntax node visiting.
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public virtual void visit(Columbus.Csharp.Asg.Nodes.Structure.NamespaceDeclarationSyntax node, bool callVirtualBase = true) { }

        /// <summary>
        /// Visitor which is called at the end of the Columbus.Csharp.Asg.Nodes.Structure.NamespaceDeclarationSyntax node visiting.
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public virtual void visitEnd(Columbus.Csharp.Asg.Nodes.Structure.NamespaceDeclarationSyntax node, bool callVirtualBase = true) { }

        /// <summary>
        /// Visitor which is called at the beginning of the Columbus.Csharp.Asg.Nodes.Structure.OperatorDeclarationSyntax node visiting.
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public virtual void visit(Columbus.Csharp.Asg.Nodes.Structure.OperatorDeclarationSyntax node, bool callVirtualBase = true) { }

        /// <summary>
        /// Visitor which is called at the end of the Columbus.Csharp.Asg.Nodes.Structure.OperatorDeclarationSyntax node visiting.
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public virtual void visitEnd(Columbus.Csharp.Asg.Nodes.Structure.OperatorDeclarationSyntax node, bool callVirtualBase = true) { }

        /// <summary>
        /// Visitor which is called at the beginning of the Columbus.Csharp.Asg.Nodes.Structure.OperatorMemberCrefSyntax node visiting.
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public virtual void visit(Columbus.Csharp.Asg.Nodes.Structure.OperatorMemberCrefSyntax node, bool callVirtualBase = true) { }

        /// <summary>
        /// Visitor which is called at the end of the Columbus.Csharp.Asg.Nodes.Structure.OperatorMemberCrefSyntax node visiting.
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public virtual void visitEnd(Columbus.Csharp.Asg.Nodes.Structure.OperatorMemberCrefSyntax node, bool callVirtualBase = true) { }

        /// <summary>
        /// Visitor which is called at the beginning of the Columbus.Csharp.Asg.Nodes.Structure.OrderByClauseSyntax node visiting.
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public virtual void visit(Columbus.Csharp.Asg.Nodes.Structure.OrderByClauseSyntax node, bool callVirtualBase = true) { }

        /// <summary>
        /// Visitor which is called at the end of the Columbus.Csharp.Asg.Nodes.Structure.OrderByClauseSyntax node visiting.
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public virtual void visitEnd(Columbus.Csharp.Asg.Nodes.Structure.OrderByClauseSyntax node, bool callVirtualBase = true) { }

        /// <summary>
        /// Visitor which is called at the beginning of the Columbus.Csharp.Asg.Nodes.Structure.OrderingSyntax node visiting.
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public virtual void visit(Columbus.Csharp.Asg.Nodes.Structure.OrderingSyntax node, bool callVirtualBase = true) { }

        /// <summary>
        /// Visitor which is called at the end of the Columbus.Csharp.Asg.Nodes.Structure.OrderingSyntax node visiting.
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public virtual void visitEnd(Columbus.Csharp.Asg.Nodes.Structure.OrderingSyntax node, bool callVirtualBase = true) { }

        /// <summary>
        /// Visitor which is called at the beginning of the Columbus.Csharp.Asg.Nodes.Structure.ParameterListSyntax node visiting.
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public virtual void visit(Columbus.Csharp.Asg.Nodes.Structure.ParameterListSyntax node, bool callVirtualBase = true) { }

        /// <summary>
        /// Visitor which is called at the end of the Columbus.Csharp.Asg.Nodes.Structure.ParameterListSyntax node visiting.
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public virtual void visitEnd(Columbus.Csharp.Asg.Nodes.Structure.ParameterListSyntax node, bool callVirtualBase = true) { }

        /// <summary>
        /// Visitor which is called at the beginning of the Columbus.Csharp.Asg.Nodes.Structure.ParameterSyntax node visiting.
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public virtual void visit(Columbus.Csharp.Asg.Nodes.Structure.ParameterSyntax node, bool callVirtualBase = true) { }

        /// <summary>
        /// Visitor which is called at the end of the Columbus.Csharp.Asg.Nodes.Structure.ParameterSyntax node visiting.
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public virtual void visitEnd(Columbus.Csharp.Asg.Nodes.Structure.ParameterSyntax node, bool callVirtualBase = true) { }

        /// <summary>
        /// Visitor which is called at the beginning of the Columbus.Csharp.Asg.Nodes.Structure.PropertyDeclarationSyntax node visiting.
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public virtual void visit(Columbus.Csharp.Asg.Nodes.Structure.PropertyDeclarationSyntax node, bool callVirtualBase = true) { }

        /// <summary>
        /// Visitor which is called at the end of the Columbus.Csharp.Asg.Nodes.Structure.PropertyDeclarationSyntax node visiting.
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public virtual void visitEnd(Columbus.Csharp.Asg.Nodes.Structure.PropertyDeclarationSyntax node, bool callVirtualBase = true) { }

        /// <summary>
        /// Visitor which is called at the beginning of the Columbus.Csharp.Asg.Nodes.Structure.QualifiedCrefSyntax node visiting.
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public virtual void visit(Columbus.Csharp.Asg.Nodes.Structure.QualifiedCrefSyntax node, bool callVirtualBase = true) { }

        /// <summary>
        /// Visitor which is called at the end of the Columbus.Csharp.Asg.Nodes.Structure.QualifiedCrefSyntax node visiting.
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public virtual void visitEnd(Columbus.Csharp.Asg.Nodes.Structure.QualifiedCrefSyntax node, bool callVirtualBase = true) { }

        /// <summary>
        /// Visitor which is called at the beginning of the Columbus.Csharp.Asg.Nodes.Structure.QueryBodySyntax node visiting.
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public virtual void visit(Columbus.Csharp.Asg.Nodes.Structure.QueryBodySyntax node, bool callVirtualBase = true) { }

        /// <summary>
        /// Visitor which is called at the end of the Columbus.Csharp.Asg.Nodes.Structure.QueryBodySyntax node visiting.
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public virtual void visitEnd(Columbus.Csharp.Asg.Nodes.Structure.QueryBodySyntax node, bool callVirtualBase = true) { }

        /// <summary>
        /// Visitor which is called at the beginning of the Columbus.Csharp.Asg.Nodes.Structure.QueryContinuationSyntax node visiting.
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public virtual void visit(Columbus.Csharp.Asg.Nodes.Structure.QueryContinuationSyntax node, bool callVirtualBase = true) { }

        /// <summary>
        /// Visitor which is called at the end of the Columbus.Csharp.Asg.Nodes.Structure.QueryContinuationSyntax node visiting.
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public virtual void visitEnd(Columbus.Csharp.Asg.Nodes.Structure.QueryContinuationSyntax node, bool callVirtualBase = true) { }

        /// <summary>
        /// Visitor which is called at the beginning of the Columbus.Csharp.Asg.Nodes.Structure.SelectClauseSyntax node visiting.
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public virtual void visit(Columbus.Csharp.Asg.Nodes.Structure.SelectClauseSyntax node, bool callVirtualBase = true) { }

        /// <summary>
        /// Visitor which is called at the end of the Columbus.Csharp.Asg.Nodes.Structure.SelectClauseSyntax node visiting.
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public virtual void visitEnd(Columbus.Csharp.Asg.Nodes.Structure.SelectClauseSyntax node, bool callVirtualBase = true) { }

        /// <summary>
        /// Visitor which is called at the beginning of the Columbus.Csharp.Asg.Nodes.Structure.SimpleBaseTypeSyntax node visiting.
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public virtual void visit(Columbus.Csharp.Asg.Nodes.Structure.SimpleBaseTypeSyntax node, bool callVirtualBase = true) { }

        /// <summary>
        /// Visitor which is called at the end of the Columbus.Csharp.Asg.Nodes.Structure.SimpleBaseTypeSyntax node visiting.
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public virtual void visitEnd(Columbus.Csharp.Asg.Nodes.Structure.SimpleBaseTypeSyntax node, bool callVirtualBase = true) { }

        /// <summary>
        /// Visitor which is called at the beginning of the Columbus.Csharp.Asg.Nodes.Structure.StructDeclarationSyntax node visiting.
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public virtual void visit(Columbus.Csharp.Asg.Nodes.Structure.StructDeclarationSyntax node, bool callVirtualBase = true) { }

        /// <summary>
        /// Visitor which is called at the end of the Columbus.Csharp.Asg.Nodes.Structure.StructDeclarationSyntax node visiting.
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public virtual void visitEnd(Columbus.Csharp.Asg.Nodes.Structure.StructDeclarationSyntax node, bool callVirtualBase = true) { }

        /// <summary>
        /// Visitor which is called at the beginning of the Columbus.Csharp.Asg.Nodes.Structure.SwitchSectionSyntax node visiting.
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public virtual void visit(Columbus.Csharp.Asg.Nodes.Structure.SwitchSectionSyntax node, bool callVirtualBase = true) { }

        /// <summary>
        /// Visitor which is called at the end of the Columbus.Csharp.Asg.Nodes.Structure.SwitchSectionSyntax node visiting.
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public virtual void visitEnd(Columbus.Csharp.Asg.Nodes.Structure.SwitchSectionSyntax node, bool callVirtualBase = true) { }

        /// <summary>
        /// Visitor which is called at the beginning of the Columbus.Csharp.Asg.Nodes.Structure.SyntaxToken node visiting.
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public virtual void visit(Columbus.Csharp.Asg.Nodes.Structure.SyntaxToken node, bool callVirtualBase = true) { }

        /// <summary>
        /// Visitor which is called at the end of the Columbus.Csharp.Asg.Nodes.Structure.SyntaxToken node visiting.
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public virtual void visitEnd(Columbus.Csharp.Asg.Nodes.Structure.SyntaxToken node, bool callVirtualBase = true) { }

        /// <summary>
        /// Visitor which is called at the beginning of the Columbus.Csharp.Asg.Nodes.Structure.TypeArgumentListSyntax node visiting.
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public virtual void visit(Columbus.Csharp.Asg.Nodes.Structure.TypeArgumentListSyntax node, bool callVirtualBase = true) { }

        /// <summary>
        /// Visitor which is called at the end of the Columbus.Csharp.Asg.Nodes.Structure.TypeArgumentListSyntax node visiting.
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public virtual void visitEnd(Columbus.Csharp.Asg.Nodes.Structure.TypeArgumentListSyntax node, bool callVirtualBase = true) { }

        /// <summary>
        /// Visitor which is called at the beginning of the Columbus.Csharp.Asg.Nodes.Structure.TypeConstraintSyntax node visiting.
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public virtual void visit(Columbus.Csharp.Asg.Nodes.Structure.TypeConstraintSyntax node, bool callVirtualBase = true) { }

        /// <summary>
        /// Visitor which is called at the end of the Columbus.Csharp.Asg.Nodes.Structure.TypeConstraintSyntax node visiting.
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public virtual void visitEnd(Columbus.Csharp.Asg.Nodes.Structure.TypeConstraintSyntax node, bool callVirtualBase = true) { }

        /// <summary>
        /// Visitor which is called at the beginning of the Columbus.Csharp.Asg.Nodes.Structure.TypeCrefSyntax node visiting.
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public virtual void visit(Columbus.Csharp.Asg.Nodes.Structure.TypeCrefSyntax node, bool callVirtualBase = true) { }

        /// <summary>
        /// Visitor which is called at the end of the Columbus.Csharp.Asg.Nodes.Structure.TypeCrefSyntax node visiting.
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public virtual void visitEnd(Columbus.Csharp.Asg.Nodes.Structure.TypeCrefSyntax node, bool callVirtualBase = true) { }

        /// <summary>
        /// Visitor which is called at the beginning of the Columbus.Csharp.Asg.Nodes.Structure.TypeParameterConstraintClauseSyntax node visiting.
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public virtual void visit(Columbus.Csharp.Asg.Nodes.Structure.TypeParameterConstraintClauseSyntax node, bool callVirtualBase = true) { }

        /// <summary>
        /// Visitor which is called at the end of the Columbus.Csharp.Asg.Nodes.Structure.TypeParameterConstraintClauseSyntax node visiting.
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public virtual void visitEnd(Columbus.Csharp.Asg.Nodes.Structure.TypeParameterConstraintClauseSyntax node, bool callVirtualBase = true) { }

        /// <summary>
        /// Visitor which is called at the beginning of the Columbus.Csharp.Asg.Nodes.Structure.TypeParameterListSyntax node visiting.
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public virtual void visit(Columbus.Csharp.Asg.Nodes.Structure.TypeParameterListSyntax node, bool callVirtualBase = true) { }

        /// <summary>
        /// Visitor which is called at the end of the Columbus.Csharp.Asg.Nodes.Structure.TypeParameterListSyntax node visiting.
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public virtual void visitEnd(Columbus.Csharp.Asg.Nodes.Structure.TypeParameterListSyntax node, bool callVirtualBase = true) { }

        /// <summary>
        /// Visitor which is called at the beginning of the Columbus.Csharp.Asg.Nodes.Structure.TypeParameterSyntax node visiting.
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public virtual void visit(Columbus.Csharp.Asg.Nodes.Structure.TypeParameterSyntax node, bool callVirtualBase = true) { }

        /// <summary>
        /// Visitor which is called at the end of the Columbus.Csharp.Asg.Nodes.Structure.TypeParameterSyntax node visiting.
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public virtual void visitEnd(Columbus.Csharp.Asg.Nodes.Structure.TypeParameterSyntax node, bool callVirtualBase = true) { }

        /// <summary>
        /// Visitor which is called at the beginning of the Columbus.Csharp.Asg.Nodes.Structure.UsingDirectiveSyntax node visiting.
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public virtual void visit(Columbus.Csharp.Asg.Nodes.Structure.UsingDirectiveSyntax node, bool callVirtualBase = true) { }

        /// <summary>
        /// Visitor which is called at the end of the Columbus.Csharp.Asg.Nodes.Structure.UsingDirectiveSyntax node visiting.
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public virtual void visitEnd(Columbus.Csharp.Asg.Nodes.Structure.UsingDirectiveSyntax node, bool callVirtualBase = true) { }

        /// <summary>
        /// Visitor which is called at the beginning of the Columbus.Csharp.Asg.Nodes.Structure.VariableDeclarationSyntax node visiting.
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public virtual void visit(Columbus.Csharp.Asg.Nodes.Structure.VariableDeclarationSyntax node, bool callVirtualBase = true) { }

        /// <summary>
        /// Visitor which is called at the end of the Columbus.Csharp.Asg.Nodes.Structure.VariableDeclarationSyntax node visiting.
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public virtual void visitEnd(Columbus.Csharp.Asg.Nodes.Structure.VariableDeclarationSyntax node, bool callVirtualBase = true) { }

        /// <summary>
        /// Visitor which is called at the beginning of the Columbus.Csharp.Asg.Nodes.Structure.VariableDeclaratorSyntax node visiting.
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public virtual void visit(Columbus.Csharp.Asg.Nodes.Structure.VariableDeclaratorSyntax node, bool callVirtualBase = true) { }

        /// <summary>
        /// Visitor which is called at the end of the Columbus.Csharp.Asg.Nodes.Structure.VariableDeclaratorSyntax node visiting.
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public virtual void visitEnd(Columbus.Csharp.Asg.Nodes.Structure.VariableDeclaratorSyntax node, bool callVirtualBase = true) { }

        /// <summary>
        /// Visitor which is called at the beginning of the Columbus.Csharp.Asg.Nodes.Structure.WhereClauseSyntax node visiting.
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public virtual void visit(Columbus.Csharp.Asg.Nodes.Structure.WhereClauseSyntax node, bool callVirtualBase = true) { }

        /// <summary>
        /// Visitor which is called at the end of the Columbus.Csharp.Asg.Nodes.Structure.WhereClauseSyntax node visiting.
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public virtual void visitEnd(Columbus.Csharp.Asg.Nodes.Structure.WhereClauseSyntax node, bool callVirtualBase = true) { }

        /// <summary>
        /// Visitor which is called at the beginning of the Columbus.Csharp.Asg.Nodes.Structure.XmlCDataSectionSyntax node visiting.
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public virtual void visit(Columbus.Csharp.Asg.Nodes.Structure.XmlCDataSectionSyntax node, bool callVirtualBase = true) { }

        /// <summary>
        /// Visitor which is called at the end of the Columbus.Csharp.Asg.Nodes.Structure.XmlCDataSectionSyntax node visiting.
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public virtual void visitEnd(Columbus.Csharp.Asg.Nodes.Structure.XmlCDataSectionSyntax node, bool callVirtualBase = true) { }

        /// <summary>
        /// Visitor which is called at the beginning of the Columbus.Csharp.Asg.Nodes.Structure.XmlCommentSyntax node visiting.
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public virtual void visit(Columbus.Csharp.Asg.Nodes.Structure.XmlCommentSyntax node, bool callVirtualBase = true) { }

        /// <summary>
        /// Visitor which is called at the end of the Columbus.Csharp.Asg.Nodes.Structure.XmlCommentSyntax node visiting.
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public virtual void visitEnd(Columbus.Csharp.Asg.Nodes.Structure.XmlCommentSyntax node, bool callVirtualBase = true) { }

        /// <summary>
        /// Visitor which is called at the beginning of the Columbus.Csharp.Asg.Nodes.Structure.XmlCrefAttributeSyntax node visiting.
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public virtual void visit(Columbus.Csharp.Asg.Nodes.Structure.XmlCrefAttributeSyntax node, bool callVirtualBase = true) { }

        /// <summary>
        /// Visitor which is called at the end of the Columbus.Csharp.Asg.Nodes.Structure.XmlCrefAttributeSyntax node visiting.
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public virtual void visitEnd(Columbus.Csharp.Asg.Nodes.Structure.XmlCrefAttributeSyntax node, bool callVirtualBase = true) { }

        /// <summary>
        /// Visitor which is called at the beginning of the Columbus.Csharp.Asg.Nodes.Structure.XmlElementEndTagSyntax node visiting.
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public virtual void visit(Columbus.Csharp.Asg.Nodes.Structure.XmlElementEndTagSyntax node, bool callVirtualBase = true) { }

        /// <summary>
        /// Visitor which is called at the end of the Columbus.Csharp.Asg.Nodes.Structure.XmlElementEndTagSyntax node visiting.
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public virtual void visitEnd(Columbus.Csharp.Asg.Nodes.Structure.XmlElementEndTagSyntax node, bool callVirtualBase = true) { }

        /// <summary>
        /// Visitor which is called at the beginning of the Columbus.Csharp.Asg.Nodes.Structure.XmlElementStartTagSyntax node visiting.
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public virtual void visit(Columbus.Csharp.Asg.Nodes.Structure.XmlElementStartTagSyntax node, bool callVirtualBase = true) { }

        /// <summary>
        /// Visitor which is called at the end of the Columbus.Csharp.Asg.Nodes.Structure.XmlElementStartTagSyntax node visiting.
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public virtual void visitEnd(Columbus.Csharp.Asg.Nodes.Structure.XmlElementStartTagSyntax node, bool callVirtualBase = true) { }

        /// <summary>
        /// Visitor which is called at the beginning of the Columbus.Csharp.Asg.Nodes.Structure.XmlElementSyntax node visiting.
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public virtual void visit(Columbus.Csharp.Asg.Nodes.Structure.XmlElementSyntax node, bool callVirtualBase = true) { }

        /// <summary>
        /// Visitor which is called at the end of the Columbus.Csharp.Asg.Nodes.Structure.XmlElementSyntax node visiting.
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public virtual void visitEnd(Columbus.Csharp.Asg.Nodes.Structure.XmlElementSyntax node, bool callVirtualBase = true) { }

        /// <summary>
        /// Visitor which is called at the beginning of the Columbus.Csharp.Asg.Nodes.Structure.XmlEmptyElementSyntax node visiting.
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public virtual void visit(Columbus.Csharp.Asg.Nodes.Structure.XmlEmptyElementSyntax node, bool callVirtualBase = true) { }

        /// <summary>
        /// Visitor which is called at the end of the Columbus.Csharp.Asg.Nodes.Structure.XmlEmptyElementSyntax node visiting.
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public virtual void visitEnd(Columbus.Csharp.Asg.Nodes.Structure.XmlEmptyElementSyntax node, bool callVirtualBase = true) { }

        /// <summary>
        /// Visitor which is called at the beginning of the Columbus.Csharp.Asg.Nodes.Structure.XmlNameAttributeSyntax node visiting.
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public virtual void visit(Columbus.Csharp.Asg.Nodes.Structure.XmlNameAttributeSyntax node, bool callVirtualBase = true) { }

        /// <summary>
        /// Visitor which is called at the end of the Columbus.Csharp.Asg.Nodes.Structure.XmlNameAttributeSyntax node visiting.
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public virtual void visitEnd(Columbus.Csharp.Asg.Nodes.Structure.XmlNameAttributeSyntax node, bool callVirtualBase = true) { }

        /// <summary>
        /// Visitor which is called at the beginning of the Columbus.Csharp.Asg.Nodes.Structure.XmlNameSyntax node visiting.
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public virtual void visit(Columbus.Csharp.Asg.Nodes.Structure.XmlNameSyntax node, bool callVirtualBase = true) { }

        /// <summary>
        /// Visitor which is called at the end of the Columbus.Csharp.Asg.Nodes.Structure.XmlNameSyntax node visiting.
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public virtual void visitEnd(Columbus.Csharp.Asg.Nodes.Structure.XmlNameSyntax node, bool callVirtualBase = true) { }

        /// <summary>
        /// Visitor which is called at the beginning of the Columbus.Csharp.Asg.Nodes.Structure.XmlPrefixSyntax node visiting.
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public virtual void visit(Columbus.Csharp.Asg.Nodes.Structure.XmlPrefixSyntax node, bool callVirtualBase = true) { }

        /// <summary>
        /// Visitor which is called at the end of the Columbus.Csharp.Asg.Nodes.Structure.XmlPrefixSyntax node visiting.
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public virtual void visitEnd(Columbus.Csharp.Asg.Nodes.Structure.XmlPrefixSyntax node, bool callVirtualBase = true) { }

        /// <summary>
        /// Visitor which is called at the beginning of the Columbus.Csharp.Asg.Nodes.Structure.XmlProcessingInstructionSyntax node visiting.
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public virtual void visit(Columbus.Csharp.Asg.Nodes.Structure.XmlProcessingInstructionSyntax node, bool callVirtualBase = true) { }

        /// <summary>
        /// Visitor which is called at the end of the Columbus.Csharp.Asg.Nodes.Structure.XmlProcessingInstructionSyntax node visiting.
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public virtual void visitEnd(Columbus.Csharp.Asg.Nodes.Structure.XmlProcessingInstructionSyntax node, bool callVirtualBase = true) { }

        /// <summary>
        /// Visitor which is called at the beginning of the Columbus.Csharp.Asg.Nodes.Structure.XmlTextAttributeSyntax node visiting.
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public virtual void visit(Columbus.Csharp.Asg.Nodes.Structure.XmlTextAttributeSyntax node, bool callVirtualBase = true) { }

        /// <summary>
        /// Visitor which is called at the end of the Columbus.Csharp.Asg.Nodes.Structure.XmlTextAttributeSyntax node visiting.
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public virtual void visitEnd(Columbus.Csharp.Asg.Nodes.Structure.XmlTextAttributeSyntax node, bool callVirtualBase = true) { }

        /// <summary>
        /// Visitor which is called at the beginning of the Columbus.Csharp.Asg.Nodes.Structure.XmlTextSyntax node visiting.
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public virtual void visit(Columbus.Csharp.Asg.Nodes.Structure.XmlTextSyntax node, bool callVirtualBase = true) { }

        /// <summary>
        /// Visitor which is called at the end of the Columbus.Csharp.Asg.Nodes.Structure.XmlTextSyntax node visiting.
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public virtual void visitEnd(Columbus.Csharp.Asg.Nodes.Structure.XmlTextSyntax node, bool callVirtualBase = true) { }

        /// <summary>
        /// Edge visitor for Alias edge which is called when the subtree of this edge is started.
        /// </summary>
        /// <param name="begin">[in] The id of the node the edge starts from.</param>
        /// <param name="end">[in] The id of the node the edge points to.</param>
        public virtual void visitAliasQualifiedNameSyntax_Alias(uint begin, uint end) { }

        /// <summary>
        /// Edge end visitor for Alias edge which is called after the subtree of this edge is finished.
        /// </summary>
        /// <param name="begin">[in] The id of the node the edge starts from.</param>
        /// <param name="end">[in] The id of the node the edge points to.</param>
        public virtual void visitEndAliasQualifiedNameSyntax_Alias(uint begin, uint end) { }

        /// <summary>
        /// Edge visitor for Name edge which is called when the subtree of this edge is started.
        /// </summary>
        /// <param name="begin">[in] The id of the node the edge starts from.</param>
        /// <param name="end">[in] The id of the node the edge points to.</param>
        public virtual void visitAliasQualifiedNameSyntax_Name(uint begin, uint end) { }

        /// <summary>
        /// Edge end visitor for Name edge which is called after the subtree of this edge is finished.
        /// </summary>
        /// <param name="begin">[in] The id of the node the edge starts from.</param>
        /// <param name="end">[in] The id of the node the edge points to.</param>
        public virtual void visitEndAliasQualifiedNameSyntax_Name(uint begin, uint end) { }

        /// <summary>
        /// Edge visitor for Body edge which is called when the subtree of this edge is started.
        /// </summary>
        /// <param name="begin">[in] The id of the node the edge starts from.</param>
        /// <param name="end">[in] The id of the node the edge points to.</param>
        public virtual void visitAnonymousFunctionExpressionSyntax_Body(uint begin, uint end) { }

        /// <summary>
        /// Edge end visitor for Body edge which is called after the subtree of this edge is finished.
        /// </summary>
        /// <param name="begin">[in] The id of the node the edge starts from.</param>
        /// <param name="end">[in] The id of the node the edge points to.</param>
        public virtual void visitEndAnonymousFunctionExpressionSyntax_Body(uint begin, uint end) { }

        /// <summary>
        /// Edge visitor for ParameterList edge which is called when the subtree of this edge is started.
        /// </summary>
        /// <param name="begin">[in] The id of the node the edge starts from.</param>
        /// <param name="end">[in] The id of the node the edge points to.</param>
        public virtual void visitAnonymousMethodExpressionSyntax_ParameterList(uint begin, uint end) { }

        /// <summary>
        /// Edge end visitor for ParameterList edge which is called after the subtree of this edge is finished.
        /// </summary>
        /// <param name="begin">[in] The id of the node the edge starts from.</param>
        /// <param name="end">[in] The id of the node the edge points to.</param>
        public virtual void visitEndAnonymousMethodExpressionSyntax_ParameterList(uint begin, uint end) { }

        /// <summary>
        /// Edge visitor for Initializers edge which is called when the subtree of this edge is started.
        /// </summary>
        /// <param name="begin">[in] The id of the node the edge starts from.</param>
        /// <param name="end">[in] The id of the node the edge points to.</param>
        public virtual void visitAnonymousObjectCreationExpressionSyntax_Initializers(uint begin, uint end) { }

        /// <summary>
        /// Edge end visitor for Initializers edge which is called after the subtree of this edge is finished.
        /// </summary>
        /// <param name="begin">[in] The id of the node the edge starts from.</param>
        /// <param name="end">[in] The id of the node the edge points to.</param>
        public virtual void visitEndAnonymousObjectCreationExpressionSyntax_Initializers(uint begin, uint end) { }

        /// <summary>
        /// Edge visitor for Initializer edge which is called when the subtree of this edge is started.
        /// </summary>
        /// <param name="begin">[in] The id of the node the edge starts from.</param>
        /// <param name="end">[in] The id of the node the edge points to.</param>
        public virtual void visitArrayCreationExpressionSyntax_Initializer(uint begin, uint end) { }

        /// <summary>
        /// Edge end visitor for Initializer edge which is called after the subtree of this edge is finished.
        /// </summary>
        /// <param name="begin">[in] The id of the node the edge starts from.</param>
        /// <param name="end">[in] The id of the node the edge points to.</param>
        public virtual void visitEndArrayCreationExpressionSyntax_Initializer(uint begin, uint end) { }

        /// <summary>
        /// Edge visitor for Type edge which is called when the subtree of this edge is started.
        /// </summary>
        /// <param name="begin">[in] The id of the node the edge starts from.</param>
        /// <param name="end">[in] The id of the node the edge points to.</param>
        public virtual void visitArrayCreationExpressionSyntax_Type(uint begin, uint end) { }

        /// <summary>
        /// Edge end visitor for Type edge which is called after the subtree of this edge is finished.
        /// </summary>
        /// <param name="begin">[in] The id of the node the edge starts from.</param>
        /// <param name="end">[in] The id of the node the edge points to.</param>
        public virtual void visitEndArrayCreationExpressionSyntax_Type(uint begin, uint end) { }

        /// <summary>
        /// Edge visitor for ElementType edge which is called when the subtree of this edge is started.
        /// </summary>
        /// <param name="begin">[in] The id of the node the edge starts from.</param>
        /// <param name="end">[in] The id of the node the edge points to.</param>
        public virtual void visitArrayTypeSyntax_ElementType(uint begin, uint end) { }

        /// <summary>
        /// Edge end visitor for ElementType edge which is called after the subtree of this edge is finished.
        /// </summary>
        /// <param name="begin">[in] The id of the node the edge starts from.</param>
        /// <param name="end">[in] The id of the node the edge points to.</param>
        public virtual void visitEndArrayTypeSyntax_ElementType(uint begin, uint end) { }

        /// <summary>
        /// Edge visitor for RankSpecifiers edge which is called when the subtree of this edge is started.
        /// </summary>
        /// <param name="begin">[in] The id of the node the edge starts from.</param>
        /// <param name="end">[in] The id of the node the edge points to.</param>
        public virtual void visitArrayTypeSyntax_RankSpecifiers(uint begin, uint end) { }

        /// <summary>
        /// Edge end visitor for RankSpecifiers edge which is called after the subtree of this edge is finished.
        /// </summary>
        /// <param name="begin">[in] The id of the node the edge starts from.</param>
        /// <param name="end">[in] The id of the node the edge points to.</param>
        public virtual void visitEndArrayTypeSyntax_RankSpecifiers(uint begin, uint end) { }

        /// <summary>
        /// Edge visitor for EventAccessorCall edge which.
        /// </summary>
        /// <param name="begin">[in] The id of the node the edge starts from.</param>
        /// <param name="end">[in] The id of the node the edge points to.</param>
        public virtual void visitAssignmentExpressionSyntax_EventAccessorCall(uint begin, uint end) { }

        /// <summary>
        /// Edge end visitor for EventAccessorCall edge which is called after the visit pair of this edge is called.
        /// </summary>
        /// <param name="begin">[in] The id of the node the edge starts from.</param>
        /// <param name="end">[in] The id of the node the edge points to.</param>
        public virtual void visitEndAssignmentExpressionSyntax_EventAccessorCall(uint begin, uint end) { }

        /// <summary>
        /// Edge visitor for Left edge which is called when the subtree of this edge is started.
        /// </summary>
        /// <param name="begin">[in] The id of the node the edge starts from.</param>
        /// <param name="end">[in] The id of the node the edge points to.</param>
        public virtual void visitAssignmentExpressionSyntax_Left(uint begin, uint end) { }

        /// <summary>
        /// Edge end visitor for Left edge which is called after the subtree of this edge is finished.
        /// </summary>
        /// <param name="begin">[in] The id of the node the edge starts from.</param>
        /// <param name="end">[in] The id of the node the edge points to.</param>
        public virtual void visitEndAssignmentExpressionSyntax_Left(uint begin, uint end) { }

        /// <summary>
        /// Edge visitor for OverloadedOperatorCall edge which.
        /// </summary>
        /// <param name="begin">[in] The id of the node the edge starts from.</param>
        /// <param name="end">[in] The id of the node the edge points to.</param>
        public virtual void visitAssignmentExpressionSyntax_OverloadedOperatorCall(uint begin, uint end) { }

        /// <summary>
        /// Edge end visitor for OverloadedOperatorCall edge which is called after the visit pair of this edge is called.
        /// </summary>
        /// <param name="begin">[in] The id of the node the edge starts from.</param>
        /// <param name="end">[in] The id of the node the edge points to.</param>
        public virtual void visitEndAssignmentExpressionSyntax_OverloadedOperatorCall(uint begin, uint end) { }

        /// <summary>
        /// Edge visitor for Right edge which is called when the subtree of this edge is started.
        /// </summary>
        /// <param name="begin">[in] The id of the node the edge starts from.</param>
        /// <param name="end">[in] The id of the node the edge points to.</param>
        public virtual void visitAssignmentExpressionSyntax_Right(uint begin, uint end) { }

        /// <summary>
        /// Edge end visitor for Right edge which is called after the subtree of this edge is finished.
        /// </summary>
        /// <param name="begin">[in] The id of the node the edge starts from.</param>
        /// <param name="end">[in] The id of the node the edge points to.</param>
        public virtual void visitEndAssignmentExpressionSyntax_Right(uint begin, uint end) { }

        /// <summary>
        /// Edge visitor for Expression edge which is called when the subtree of this edge is started.
        /// </summary>
        /// <param name="begin">[in] The id of the node the edge starts from.</param>
        /// <param name="end">[in] The id of the node the edge points to.</param>
        public virtual void visitAwaitExpressionSyntax_Expression(uint begin, uint end) { }

        /// <summary>
        /// Edge end visitor for Expression edge which is called after the subtree of this edge is finished.
        /// </summary>
        /// <param name="begin">[in] The id of the node the edge starts from.</param>
        /// <param name="end">[in] The id of the node the edge points to.</param>
        public virtual void visitEndAwaitExpressionSyntax_Expression(uint begin, uint end) { }

        /// <summary>
        /// Edge visitor for Left edge which is called when the subtree of this edge is started.
        /// </summary>
        /// <param name="begin">[in] The id of the node the edge starts from.</param>
        /// <param name="end">[in] The id of the node the edge points to.</param>
        public virtual void visitBinaryExpressionSyntax_Left(uint begin, uint end) { }

        /// <summary>
        /// Edge end visitor for Left edge which is called after the subtree of this edge is finished.
        /// </summary>
        /// <param name="begin">[in] The id of the node the edge starts from.</param>
        /// <param name="end">[in] The id of the node the edge points to.</param>
        public virtual void visitEndBinaryExpressionSyntax_Left(uint begin, uint end) { }

        /// <summary>
        /// Edge visitor for OverloadedOperatorCall edge which.
        /// </summary>
        /// <param name="begin">[in] The id of the node the edge starts from.</param>
        /// <param name="end">[in] The id of the node the edge points to.</param>
        public virtual void visitBinaryExpressionSyntax_OverloadedOperatorCall(uint begin, uint end) { }

        /// <summary>
        /// Edge end visitor for OverloadedOperatorCall edge which is called after the visit pair of this edge is called.
        /// </summary>
        /// <param name="begin">[in] The id of the node the edge starts from.</param>
        /// <param name="end">[in] The id of the node the edge points to.</param>
        public virtual void visitEndBinaryExpressionSyntax_OverloadedOperatorCall(uint begin, uint end) { }

        /// <summary>
        /// Edge visitor for Right edge which is called when the subtree of this edge is started.
        /// </summary>
        /// <param name="begin">[in] The id of the node the edge starts from.</param>
        /// <param name="end">[in] The id of the node the edge points to.</param>
        public virtual void visitBinaryExpressionSyntax_Right(uint begin, uint end) { }

        /// <summary>
        /// Edge end visitor for Right edge which is called after the subtree of this edge is finished.
        /// </summary>
        /// <param name="begin">[in] The id of the node the edge starts from.</param>
        /// <param name="end">[in] The id of the node the edge points to.</param>
        public virtual void visitEndBinaryExpressionSyntax_Right(uint begin, uint end) { }

        /// <summary>
        /// Edge visitor for ConversionOperatorCall edge which.
        /// </summary>
        /// <param name="begin">[in] The id of the node the edge starts from.</param>
        /// <param name="end">[in] The id of the node the edge points to.</param>
        public virtual void visitCastExpressionSyntax_ConversionOperatorCall(uint begin, uint end) { }

        /// <summary>
        /// Edge end visitor for ConversionOperatorCall edge which is called after the visit pair of this edge is called.
        /// </summary>
        /// <param name="begin">[in] The id of the node the edge starts from.</param>
        /// <param name="end">[in] The id of the node the edge points to.</param>
        public virtual void visitEndCastExpressionSyntax_ConversionOperatorCall(uint begin, uint end) { }

        /// <summary>
        /// Edge visitor for Expression edge which is called when the subtree of this edge is started.
        /// </summary>
        /// <param name="begin">[in] The id of the node the edge starts from.</param>
        /// <param name="end">[in] The id of the node the edge points to.</param>
        public virtual void visitCastExpressionSyntax_Expression(uint begin, uint end) { }

        /// <summary>
        /// Edge end visitor for Expression edge which is called after the subtree of this edge is finished.
        /// </summary>
        /// <param name="begin">[in] The id of the node the edge starts from.</param>
        /// <param name="end">[in] The id of the node the edge points to.</param>
        public virtual void visitEndCastExpressionSyntax_Expression(uint begin, uint end) { }

        /// <summary>
        /// Edge visitor for Type edge which is called when the subtree of this edge is started.
        /// </summary>
        /// <param name="begin">[in] The id of the node the edge starts from.</param>
        /// <param name="end">[in] The id of the node the edge points to.</param>
        public virtual void visitCastExpressionSyntax_Type(uint begin, uint end) { }

        /// <summary>
        /// Edge end visitor for Type edge which is called after the subtree of this edge is finished.
        /// </summary>
        /// <param name="begin">[in] The id of the node the edge starts from.</param>
        /// <param name="end">[in] The id of the node the edge points to.</param>
        public virtual void visitEndCastExpressionSyntax_Type(uint begin, uint end) { }

        /// <summary>
        /// Edge visitor for Expression edge which is called when the subtree of this edge is started.
        /// </summary>
        /// <param name="begin">[in] The id of the node the edge starts from.</param>
        /// <param name="end">[in] The id of the node the edge points to.</param>
        public virtual void visitCheckedExpressionSyntax_Expression(uint begin, uint end) { }

        /// <summary>
        /// Edge end visitor for Expression edge which is called after the subtree of this edge is finished.
        /// </summary>
        /// <param name="begin">[in] The id of the node the edge starts from.</param>
        /// <param name="end">[in] The id of the node the edge points to.</param>
        public virtual void visitEndCheckedExpressionSyntax_Expression(uint begin, uint end) { }

        /// <summary>
        /// Edge visitor for Expression edge which is called when the subtree of this edge is started.
        /// </summary>
        /// <param name="begin">[in] The id of the node the edge starts from.</param>
        /// <param name="end">[in] The id of the node the edge points to.</param>
        public virtual void visitConditionalAccessExpressionSyntax_Expression(uint begin, uint end) { }

        /// <summary>
        /// Edge end visitor for Expression edge which is called after the subtree of this edge is finished.
        /// </summary>
        /// <param name="begin">[in] The id of the node the edge starts from.</param>
        /// <param name="end">[in] The id of the node the edge points to.</param>
        public virtual void visitEndConditionalAccessExpressionSyntax_Expression(uint begin, uint end) { }

        /// <summary>
        /// Edge visitor for WhenNotNull edge which is called when the subtree of this edge is started.
        /// </summary>
        /// <param name="begin">[in] The id of the node the edge starts from.</param>
        /// <param name="end">[in] The id of the node the edge points to.</param>
        public virtual void visitConditionalAccessExpressionSyntax_WhenNotNull(uint begin, uint end) { }

        /// <summary>
        /// Edge end visitor for WhenNotNull edge which is called after the subtree of this edge is finished.
        /// </summary>
        /// <param name="begin">[in] The id of the node the edge starts from.</param>
        /// <param name="end">[in] The id of the node the edge points to.</param>
        public virtual void visitEndConditionalAccessExpressionSyntax_WhenNotNull(uint begin, uint end) { }

        /// <summary>
        /// Edge visitor for Condition edge which is called when the subtree of this edge is started.
        /// </summary>
        /// <param name="begin">[in] The id of the node the edge starts from.</param>
        /// <param name="end">[in] The id of the node the edge points to.</param>
        public virtual void visitConditionalExpressionSyntax_Condition(uint begin, uint end) { }

        /// <summary>
        /// Edge end visitor for Condition edge which is called after the subtree of this edge is finished.
        /// </summary>
        /// <param name="begin">[in] The id of the node the edge starts from.</param>
        /// <param name="end">[in] The id of the node the edge points to.</param>
        public virtual void visitEndConditionalExpressionSyntax_Condition(uint begin, uint end) { }

        /// <summary>
        /// Edge visitor for WhenFalse edge which is called when the subtree of this edge is started.
        /// </summary>
        /// <param name="begin">[in] The id of the node the edge starts from.</param>
        /// <param name="end">[in] The id of the node the edge points to.</param>
        public virtual void visitConditionalExpressionSyntax_WhenFalse(uint begin, uint end) { }

        /// <summary>
        /// Edge end visitor for WhenFalse edge which is called after the subtree of this edge is finished.
        /// </summary>
        /// <param name="begin">[in] The id of the node the edge starts from.</param>
        /// <param name="end">[in] The id of the node the edge points to.</param>
        public virtual void visitEndConditionalExpressionSyntax_WhenFalse(uint begin, uint end) { }

        /// <summary>
        /// Edge visitor for WhenTrue edge which is called when the subtree of this edge is started.
        /// </summary>
        /// <param name="begin">[in] The id of the node the edge starts from.</param>
        /// <param name="end">[in] The id of the node the edge points to.</param>
        public virtual void visitConditionalExpressionSyntax_WhenTrue(uint begin, uint end) { }

        /// <summary>
        /// Edge end visitor for WhenTrue edge which is called after the subtree of this edge is finished.
        /// </summary>
        /// <param name="begin">[in] The id of the node the edge starts from.</param>
        /// <param name="end">[in] The id of the node the edge points to.</param>
        public virtual void visitEndConditionalExpressionSyntax_WhenTrue(uint begin, uint end) { }

        /// <summary>
        /// Edge visitor for Type edge which is called when the subtree of this edge is started.
        /// </summary>
        /// <param name="begin">[in] The id of the node the edge starts from.</param>
        /// <param name="end">[in] The id of the node the edge points to.</param>
        public virtual void visitDefaultExpressionSyntax_Type(uint begin, uint end) { }

        /// <summary>
        /// Edge end visitor for Type edge which is called after the subtree of this edge is finished.
        /// </summary>
        /// <param name="begin">[in] The id of the node the edge starts from.</param>
        /// <param name="end">[in] The id of the node the edge points to.</param>
        public virtual void visitEndDefaultExpressionSyntax_Type(uint begin, uint end) { }

        /// <summary>
        /// Edge visitor for AccessorCall edge which.
        /// </summary>
        /// <param name="begin">[in] The id of the node the edge starts from.</param>
        /// <param name="end">[in] The id of the node the edge points to.</param>
        public virtual void visitElementAccessExpressionSyntax_AccessorCall(uint begin, uint end) { }

        /// <summary>
        /// Edge end visitor for AccessorCall edge which is called after the visit pair of this edge is called.
        /// </summary>
        /// <param name="begin">[in] The id of the node the edge starts from.</param>
        /// <param name="end">[in] The id of the node the edge points to.</param>
        public virtual void visitEndElementAccessExpressionSyntax_AccessorCall(uint begin, uint end) { }

        /// <summary>
        /// Edge visitor for ArgumentList edge which is called when the subtree of this edge is started.
        /// </summary>
        /// <param name="begin">[in] The id of the node the edge starts from.</param>
        /// <param name="end">[in] The id of the node the edge points to.</param>
        public virtual void visitElementAccessExpressionSyntax_ArgumentList(uint begin, uint end) { }

        /// <summary>
        /// Edge end visitor for ArgumentList edge which is called after the subtree of this edge is finished.
        /// </summary>
        /// <param name="begin">[in] The id of the node the edge starts from.</param>
        /// <param name="end">[in] The id of the node the edge points to.</param>
        public virtual void visitEndElementAccessExpressionSyntax_ArgumentList(uint begin, uint end) { }

        /// <summary>
        /// Edge visitor for Expression edge which is called when the subtree of this edge is started.
        /// </summary>
        /// <param name="begin">[in] The id of the node the edge starts from.</param>
        /// <param name="end">[in] The id of the node the edge points to.</param>
        public virtual void visitElementAccessExpressionSyntax_Expression(uint begin, uint end) { }

        /// <summary>
        /// Edge end visitor for Expression edge which is called after the subtree of this edge is finished.
        /// </summary>
        /// <param name="begin">[in] The id of the node the edge starts from.</param>
        /// <param name="end">[in] The id of the node the edge points to.</param>
        public virtual void visitEndElementAccessExpressionSyntax_Expression(uint begin, uint end) { }

        /// <summary>
        /// Edge visitor for ArgumentList edge which is called when the subtree of this edge is started.
        /// </summary>
        /// <param name="begin">[in] The id of the node the edge starts from.</param>
        /// <param name="end">[in] The id of the node the edge points to.</param>
        public virtual void visitElementBindingExpressionSyntax_ArgumentList(uint begin, uint end) { }

        /// <summary>
        /// Edge end visitor for ArgumentList edge which is called after the subtree of this edge is finished.
        /// </summary>
        /// <param name="begin">[in] The id of the node the edge starts from.</param>
        /// <param name="end">[in] The id of the node the edge points to.</param>
        public virtual void visitEndElementBindingExpressionSyntax_ArgumentList(uint begin, uint end) { }

        /// <summary>
        /// Edge visitor for TypeArgumentList edge which is called when the subtree of this edge is started.
        /// </summary>
        /// <param name="begin">[in] The id of the node the edge starts from.</param>
        /// <param name="end">[in] The id of the node the edge points to.</param>
        public virtual void visitGenericNameSyntax_TypeArgumentList(uint begin, uint end) { }

        /// <summary>
        /// Edge end visitor for TypeArgumentList edge which is called after the subtree of this edge is finished.
        /// </summary>
        /// <param name="begin">[in] The id of the node the edge starts from.</param>
        /// <param name="end">[in] The id of the node the edge points to.</param>
        public virtual void visitEndGenericNameSyntax_TypeArgumentList(uint begin, uint end) { }

        /// <summary>
        /// Edge visitor for AccessorCall edge which.
        /// </summary>
        /// <param name="begin">[in] The id of the node the edge starts from.</param>
        /// <param name="end">[in] The id of the node the edge points to.</param>
        public virtual void visitIdentifierNameSyntax_AccessorCall(uint begin, uint end) { }

        /// <summary>
        /// Edge end visitor for AccessorCall edge which is called after the visit pair of this edge is called.
        /// </summary>
        /// <param name="begin">[in] The id of the node the edge starts from.</param>
        /// <param name="end">[in] The id of the node the edge points to.</param>
        public virtual void visitEndIdentifierNameSyntax_AccessorCall(uint begin, uint end) { }

        /// <summary>
        /// Edge visitor for Declaration edge which.
        /// </summary>
        /// <param name="begin">[in] The id of the node the edge starts from.</param>
        /// <param name="end">[in] The id of the node the edge points to.</param>
        public virtual void visitIdentifierNameSyntax_Declaration(uint begin, uint end) { }

        /// <summary>
        /// Edge end visitor for Declaration edge which is called after the visit pair of this edge is called.
        /// </summary>
        /// <param name="begin">[in] The id of the node the edge starts from.</param>
        /// <param name="end">[in] The id of the node the edge points to.</param>
        public virtual void visitEndIdentifierNameSyntax_Declaration(uint begin, uint end) { }

        /// <summary>
        /// Edge visitor for Initializer edge which is called when the subtree of this edge is started.
        /// </summary>
        /// <param name="begin">[in] The id of the node the edge starts from.</param>
        /// <param name="end">[in] The id of the node the edge points to.</param>
        public virtual void visitImplicitArrayCreationExpressionSyntax_Initializer(uint begin, uint end) { }

        /// <summary>
        /// Edge end visitor for Initializer edge which is called after the subtree of this edge is finished.
        /// </summary>
        /// <param name="begin">[in] The id of the node the edge starts from.</param>
        /// <param name="end">[in] The id of the node the edge points to.</param>
        public virtual void visitEndImplicitArrayCreationExpressionSyntax_Initializer(uint begin, uint end) { }

        /// <summary>
        /// Edge visitor for ArgumentList edge which is called when the subtree of this edge is started.
        /// </summary>
        /// <param name="begin">[in] The id of the node the edge starts from.</param>
        /// <param name="end">[in] The id of the node the edge points to.</param>
        public virtual void visitImplicitElementAccessSyntax_ArgumentList(uint begin, uint end) { }

        /// <summary>
        /// Edge end visitor for ArgumentList edge which is called after the subtree of this edge is finished.
        /// </summary>
        /// <param name="begin">[in] The id of the node the edge starts from.</param>
        /// <param name="end">[in] The id of the node the edge points to.</param>
        public virtual void visitEndImplicitElementAccessSyntax_ArgumentList(uint begin, uint end) { }

        /// <summary>
        /// Edge visitor for Expressions edge which is called when the subtree of this edge is started.
        /// </summary>
        /// <param name="begin">[in] The id of the node the edge starts from.</param>
        /// <param name="end">[in] The id of the node the edge points to.</param>
        public virtual void visitInitializerExpressionSyntax_Expressions(uint begin, uint end) { }

        /// <summary>
        /// Edge end visitor for Expressions edge which is called after the subtree of this edge is finished.
        /// </summary>
        /// <param name="begin">[in] The id of the node the edge starts from.</param>
        /// <param name="end">[in] The id of the node the edge points to.</param>
        public virtual void visitEndInitializerExpressionSyntax_Expressions(uint begin, uint end) { }

        /// <summary>
        /// Edge visitor for Contents edge which is called when the subtree of this edge is started.
        /// </summary>
        /// <param name="begin">[in] The id of the node the edge starts from.</param>
        /// <param name="end">[in] The id of the node the edge points to.</param>
        public virtual void visitInterpolatedStringExpressionSyntax_Contents(uint begin, uint end) { }

        /// <summary>
        /// Edge end visitor for Contents edge which is called after the subtree of this edge is finished.
        /// </summary>
        /// <param name="begin">[in] The id of the node the edge starts from.</param>
        /// <param name="end">[in] The id of the node the edge points to.</param>
        public virtual void visitEndInterpolatedStringExpressionSyntax_Contents(uint begin, uint end) { }

        /// <summary>
        /// Edge visitor for ArgumentList edge which is called when the subtree of this edge is started.
        /// </summary>
        /// <param name="begin">[in] The id of the node the edge starts from.</param>
        /// <param name="end">[in] The id of the node the edge points to.</param>
        public virtual void visitInvocationExpressionSyntax_ArgumentList(uint begin, uint end) { }

        /// <summary>
        /// Edge end visitor for ArgumentList edge which is called after the subtree of this edge is finished.
        /// </summary>
        /// <param name="begin">[in] The id of the node the edge starts from.</param>
        /// <param name="end">[in] The id of the node the edge points to.</param>
        public virtual void visitEndInvocationExpressionSyntax_ArgumentList(uint begin, uint end) { }

        /// <summary>
        /// Edge visitor for Expression edge which is called when the subtree of this edge is started.
        /// </summary>
        /// <param name="begin">[in] The id of the node the edge starts from.</param>
        /// <param name="end">[in] The id of the node the edge points to.</param>
        public virtual void visitInvocationExpressionSyntax_Expression(uint begin, uint end) { }

        /// <summary>
        /// Edge end visitor for Expression edge which is called after the subtree of this edge is finished.
        /// </summary>
        /// <param name="begin">[in] The id of the node the edge starts from.</param>
        /// <param name="end">[in] The id of the node the edge points to.</param>
        public virtual void visitEndInvocationExpressionSyntax_Expression(uint begin, uint end) { }

        /// <summary>
        /// Edge visitor for MethodCall edge which.
        /// </summary>
        /// <param name="begin">[in] The id of the node the edge starts from.</param>
        /// <param name="end">[in] The id of the node the edge points to.</param>
        public virtual void visitInvocationExpressionSyntax_MethodCall(uint begin, uint end) { }

        /// <summary>
        /// Edge end visitor for MethodCall edge which is called after the visit pair of this edge is called.
        /// </summary>
        /// <param name="begin">[in] The id of the node the edge starts from.</param>
        /// <param name="end">[in] The id of the node the edge points to.</param>
        public virtual void visitEndInvocationExpressionSyntax_MethodCall(uint begin, uint end) { }

        /// <summary>
        /// Edge visitor for Expression edge which is called when the subtree of this edge is started.
        /// </summary>
        /// <param name="begin">[in] The id of the node the edge starts from.</param>
        /// <param name="end">[in] The id of the node the edge points to.</param>
        public virtual void visitMakeRefExpressionSyntax_Expression(uint begin, uint end) { }

        /// <summary>
        /// Edge end visitor for Expression edge which is called after the subtree of this edge is finished.
        /// </summary>
        /// <param name="begin">[in] The id of the node the edge starts from.</param>
        /// <param name="end">[in] The id of the node the edge points to.</param>
        public virtual void visitEndMakeRefExpressionSyntax_Expression(uint begin, uint end) { }

        /// <summary>
        /// Edge visitor for Expression edge which is called when the subtree of this edge is started.
        /// </summary>
        /// <param name="begin">[in] The id of the node the edge starts from.</param>
        /// <param name="end">[in] The id of the node the edge points to.</param>
        public virtual void visitMemberAccessExpressionSyntax_Expression(uint begin, uint end) { }

        /// <summary>
        /// Edge end visitor for Expression edge which is called after the subtree of this edge is finished.
        /// </summary>
        /// <param name="begin">[in] The id of the node the edge starts from.</param>
        /// <param name="end">[in] The id of the node the edge points to.</param>
        public virtual void visitEndMemberAccessExpressionSyntax_Expression(uint begin, uint end) { }

        /// <summary>
        /// Edge visitor for Name edge which is called when the subtree of this edge is started.
        /// </summary>
        /// <param name="begin">[in] The id of the node the edge starts from.</param>
        /// <param name="end">[in] The id of the node the edge points to.</param>
        public virtual void visitMemberAccessExpressionSyntax_Name(uint begin, uint end) { }

        /// <summary>
        /// Edge end visitor for Name edge which is called after the subtree of this edge is finished.
        /// </summary>
        /// <param name="begin">[in] The id of the node the edge starts from.</param>
        /// <param name="end">[in] The id of the node the edge points to.</param>
        public virtual void visitEndMemberAccessExpressionSyntax_Name(uint begin, uint end) { }

        /// <summary>
        /// Edge visitor for Name edge which is called when the subtree of this edge is started.
        /// </summary>
        /// <param name="begin">[in] The id of the node the edge starts from.</param>
        /// <param name="end">[in] The id of the node the edge points to.</param>
        public virtual void visitMemberBindingExpressionSyntax_Name(uint begin, uint end) { }

        /// <summary>
        /// Edge end visitor for Name edge which is called after the subtree of this edge is finished.
        /// </summary>
        /// <param name="begin">[in] The id of the node the edge starts from.</param>
        /// <param name="end">[in] The id of the node the edge points to.</param>
        public virtual void visitEndMemberBindingExpressionSyntax_Name(uint begin, uint end) { }

        /// <summary>
        /// Edge visitor for ElementType edge which is called when the subtree of this edge is started.
        /// </summary>
        /// <param name="begin">[in] The id of the node the edge starts from.</param>
        /// <param name="end">[in] The id of the node the edge points to.</param>
        public virtual void visitNullableTypeSyntax_ElementType(uint begin, uint end) { }

        /// <summary>
        /// Edge end visitor for ElementType edge which is called after the subtree of this edge is finished.
        /// </summary>
        /// <param name="begin">[in] The id of the node the edge starts from.</param>
        /// <param name="end">[in] The id of the node the edge points to.</param>
        public virtual void visitEndNullableTypeSyntax_ElementType(uint begin, uint end) { }

        /// <summary>
        /// Edge visitor for ArgumentList edge which is called when the subtree of this edge is started.
        /// </summary>
        /// <param name="begin">[in] The id of the node the edge starts from.</param>
        /// <param name="end">[in] The id of the node the edge points to.</param>
        public virtual void visitObjectCreationExpressionSyntax_ArgumentList(uint begin, uint end) { }

        /// <summary>
        /// Edge end visitor for ArgumentList edge which is called after the subtree of this edge is finished.
        /// </summary>
        /// <param name="begin">[in] The id of the node the edge starts from.</param>
        /// <param name="end">[in] The id of the node the edge points to.</param>
        public virtual void visitEndObjectCreationExpressionSyntax_ArgumentList(uint begin, uint end) { }

        /// <summary>
        /// Edge visitor for ConstructorCall edge which.
        /// </summary>
        /// <param name="begin">[in] The id of the node the edge starts from.</param>
        /// <param name="end">[in] The id of the node the edge points to.</param>
        public virtual void visitObjectCreationExpressionSyntax_ConstructorCall(uint begin, uint end) { }

        /// <summary>
        /// Edge end visitor for ConstructorCall edge which is called after the visit pair of this edge is called.
        /// </summary>
        /// <param name="begin">[in] The id of the node the edge starts from.</param>
        /// <param name="end">[in] The id of the node the edge points to.</param>
        public virtual void visitEndObjectCreationExpressionSyntax_ConstructorCall(uint begin, uint end) { }

        /// <summary>
        /// Edge visitor for Initializer edge which is called when the subtree of this edge is started.
        /// </summary>
        /// <param name="begin">[in] The id of the node the edge starts from.</param>
        /// <param name="end">[in] The id of the node the edge points to.</param>
        public virtual void visitObjectCreationExpressionSyntax_Initializer(uint begin, uint end) { }

        /// <summary>
        /// Edge end visitor for Initializer edge which is called after the subtree of this edge is finished.
        /// </summary>
        /// <param name="begin">[in] The id of the node the edge starts from.</param>
        /// <param name="end">[in] The id of the node the edge points to.</param>
        public virtual void visitEndObjectCreationExpressionSyntax_Initializer(uint begin, uint end) { }

        /// <summary>
        /// Edge visitor for Type edge which is called when the subtree of this edge is started.
        /// </summary>
        /// <param name="begin">[in] The id of the node the edge starts from.</param>
        /// <param name="end">[in] The id of the node the edge points to.</param>
        public virtual void visitObjectCreationExpressionSyntax_Type(uint begin, uint end) { }

        /// <summary>
        /// Edge end visitor for Type edge which is called after the subtree of this edge is finished.
        /// </summary>
        /// <param name="begin">[in] The id of the node the edge starts from.</param>
        /// <param name="end">[in] The id of the node the edge points to.</param>
        public virtual void visitEndObjectCreationExpressionSyntax_Type(uint begin, uint end) { }

        /// <summary>
        /// Edge visitor for Expression edge which is called when the subtree of this edge is started.
        /// </summary>
        /// <param name="begin">[in] The id of the node the edge starts from.</param>
        /// <param name="end">[in] The id of the node the edge points to.</param>
        public virtual void visitParenthesizedExpressionSyntax_Expression(uint begin, uint end) { }

        /// <summary>
        /// Edge end visitor for Expression edge which is called after the subtree of this edge is finished.
        /// </summary>
        /// <param name="begin">[in] The id of the node the edge starts from.</param>
        /// <param name="end">[in] The id of the node the edge points to.</param>
        public virtual void visitEndParenthesizedExpressionSyntax_Expression(uint begin, uint end) { }

        /// <summary>
        /// Edge visitor for ParameterList edge which is called when the subtree of this edge is started.
        /// </summary>
        /// <param name="begin">[in] The id of the node the edge starts from.</param>
        /// <param name="end">[in] The id of the node the edge points to.</param>
        public virtual void visitParenthesizedLambdaExpressionSyntax_ParameterList(uint begin, uint end) { }

        /// <summary>
        /// Edge end visitor for ParameterList edge which is called after the subtree of this edge is finished.
        /// </summary>
        /// <param name="begin">[in] The id of the node the edge starts from.</param>
        /// <param name="end">[in] The id of the node the edge points to.</param>
        public virtual void visitEndParenthesizedLambdaExpressionSyntax_ParameterList(uint begin, uint end) { }

        /// <summary>
        /// Edge visitor for ElementType edge which is called when the subtree of this edge is started.
        /// </summary>
        /// <param name="begin">[in] The id of the node the edge starts from.</param>
        /// <param name="end">[in] The id of the node the edge points to.</param>
        public virtual void visitPointerTypeSyntax_ElementType(uint begin, uint end) { }

        /// <summary>
        /// Edge end visitor for ElementType edge which is called after the subtree of this edge is finished.
        /// </summary>
        /// <param name="begin">[in] The id of the node the edge starts from.</param>
        /// <param name="end">[in] The id of the node the edge points to.</param>
        public virtual void visitEndPointerTypeSyntax_ElementType(uint begin, uint end) { }

        /// <summary>
        /// Edge visitor for Operand edge which is called when the subtree of this edge is started.
        /// </summary>
        /// <param name="begin">[in] The id of the node the edge starts from.</param>
        /// <param name="end">[in] The id of the node the edge points to.</param>
        public virtual void visitPostfixUnaryExpressionSyntax_Operand(uint begin, uint end) { }

        /// <summary>
        /// Edge end visitor for Operand edge which is called after the subtree of this edge is finished.
        /// </summary>
        /// <param name="begin">[in] The id of the node the edge starts from.</param>
        /// <param name="end">[in] The id of the node the edge points to.</param>
        public virtual void visitEndPostfixUnaryExpressionSyntax_Operand(uint begin, uint end) { }

        /// <summary>
        /// Edge visitor for OverloadedOperatorCall edge which.
        /// </summary>
        /// <param name="begin">[in] The id of the node the edge starts from.</param>
        /// <param name="end">[in] The id of the node the edge points to.</param>
        public virtual void visitPostfixUnaryExpressionSyntax_OverloadedOperatorCall(uint begin, uint end) { }

        /// <summary>
        /// Edge end visitor for OverloadedOperatorCall edge which is called after the visit pair of this edge is called.
        /// </summary>
        /// <param name="begin">[in] The id of the node the edge starts from.</param>
        /// <param name="end">[in] The id of the node the edge points to.</param>
        public virtual void visitEndPostfixUnaryExpressionSyntax_OverloadedOperatorCall(uint begin, uint end) { }

        /// <summary>
        /// Edge visitor for Operand edge which is called when the subtree of this edge is started.
        /// </summary>
        /// <param name="begin">[in] The id of the node the edge starts from.</param>
        /// <param name="end">[in] The id of the node the edge points to.</param>
        public virtual void visitPrefixUnaryExpressionSyntax_Operand(uint begin, uint end) { }

        /// <summary>
        /// Edge end visitor for Operand edge which is called after the subtree of this edge is finished.
        /// </summary>
        /// <param name="begin">[in] The id of the node the edge starts from.</param>
        /// <param name="end">[in] The id of the node the edge points to.</param>
        public virtual void visitEndPrefixUnaryExpressionSyntax_Operand(uint begin, uint end) { }

        /// <summary>
        /// Edge visitor for OverloadedOperatorCall edge which.
        /// </summary>
        /// <param name="begin">[in] The id of the node the edge starts from.</param>
        /// <param name="end">[in] The id of the node the edge points to.</param>
        public virtual void visitPrefixUnaryExpressionSyntax_OverloadedOperatorCall(uint begin, uint end) { }

        /// <summary>
        /// Edge end visitor for OverloadedOperatorCall edge which is called after the visit pair of this edge is called.
        /// </summary>
        /// <param name="begin">[in] The id of the node the edge starts from.</param>
        /// <param name="end">[in] The id of the node the edge points to.</param>
        public virtual void visitEndPrefixUnaryExpressionSyntax_OverloadedOperatorCall(uint begin, uint end) { }

        /// <summary>
        /// Edge visitor for Left edge which is called when the subtree of this edge is started.
        /// </summary>
        /// <param name="begin">[in] The id of the node the edge starts from.</param>
        /// <param name="end">[in] The id of the node the edge points to.</param>
        public virtual void visitQualifiedNameSyntax_Left(uint begin, uint end) { }

        /// <summary>
        /// Edge end visitor for Left edge which is called after the subtree of this edge is finished.
        /// </summary>
        /// <param name="begin">[in] The id of the node the edge starts from.</param>
        /// <param name="end">[in] The id of the node the edge points to.</param>
        public virtual void visitEndQualifiedNameSyntax_Left(uint begin, uint end) { }

        /// <summary>
        /// Edge visitor for Right edge which is called when the subtree of this edge is started.
        /// </summary>
        /// <param name="begin">[in] The id of the node the edge starts from.</param>
        /// <param name="end">[in] The id of the node the edge points to.</param>
        public virtual void visitQualifiedNameSyntax_Right(uint begin, uint end) { }

        /// <summary>
        /// Edge end visitor for Right edge which is called after the subtree of this edge is finished.
        /// </summary>
        /// <param name="begin">[in] The id of the node the edge starts from.</param>
        /// <param name="end">[in] The id of the node the edge points to.</param>
        public virtual void visitEndQualifiedNameSyntax_Right(uint begin, uint end) { }

        /// <summary>
        /// Edge visitor for Body edge which is called when the subtree of this edge is started.
        /// </summary>
        /// <param name="begin">[in] The id of the node the edge starts from.</param>
        /// <param name="end">[in] The id of the node the edge points to.</param>
        public virtual void visitQueryExpressionSyntax_Body(uint begin, uint end) { }

        /// <summary>
        /// Edge end visitor for Body edge which is called after the subtree of this edge is finished.
        /// </summary>
        /// <param name="begin">[in] The id of the node the edge starts from.</param>
        /// <param name="end">[in] The id of the node the edge points to.</param>
        public virtual void visitEndQueryExpressionSyntax_Body(uint begin, uint end) { }

        /// <summary>
        /// Edge visitor for FromClause edge which is called when the subtree of this edge is started.
        /// </summary>
        /// <param name="begin">[in] The id of the node the edge starts from.</param>
        /// <param name="end">[in] The id of the node the edge points to.</param>
        public virtual void visitQueryExpressionSyntax_FromClause(uint begin, uint end) { }

        /// <summary>
        /// Edge end visitor for FromClause edge which is called after the subtree of this edge is finished.
        /// </summary>
        /// <param name="begin">[in] The id of the node the edge starts from.</param>
        /// <param name="end">[in] The id of the node the edge points to.</param>
        public virtual void visitEndQueryExpressionSyntax_FromClause(uint begin, uint end) { }

        /// <summary>
        /// Edge visitor for Expression edge which is called when the subtree of this edge is started.
        /// </summary>
        /// <param name="begin">[in] The id of the node the edge starts from.</param>
        /// <param name="end">[in] The id of the node the edge points to.</param>
        public virtual void visitRefTypeExpressionSyntax_Expression(uint begin, uint end) { }

        /// <summary>
        /// Edge end visitor for Expression edge which is called after the subtree of this edge is finished.
        /// </summary>
        /// <param name="begin">[in] The id of the node the edge starts from.</param>
        /// <param name="end">[in] The id of the node the edge points to.</param>
        public virtual void visitEndRefTypeExpressionSyntax_Expression(uint begin, uint end) { }

        /// <summary>
        /// Edge visitor for Expression edge which is called when the subtree of this edge is started.
        /// </summary>
        /// <param name="begin">[in] The id of the node the edge starts from.</param>
        /// <param name="end">[in] The id of the node the edge points to.</param>
        public virtual void visitRefValueExpressionSyntax_Expression(uint begin, uint end) { }

        /// <summary>
        /// Edge end visitor for Expression edge which is called after the subtree of this edge is finished.
        /// </summary>
        /// <param name="begin">[in] The id of the node the edge starts from.</param>
        /// <param name="end">[in] The id of the node the edge points to.</param>
        public virtual void visitEndRefValueExpressionSyntax_Expression(uint begin, uint end) { }

        /// <summary>
        /// Edge visitor for Type edge which is called when the subtree of this edge is started.
        /// </summary>
        /// <param name="begin">[in] The id of the node the edge starts from.</param>
        /// <param name="end">[in] The id of the node the edge points to.</param>
        public virtual void visitRefValueExpressionSyntax_Type(uint begin, uint end) { }

        /// <summary>
        /// Edge end visitor for Type edge which is called after the subtree of this edge is finished.
        /// </summary>
        /// <param name="begin">[in] The id of the node the edge starts from.</param>
        /// <param name="end">[in] The id of the node the edge points to.</param>
        public virtual void visitEndRefValueExpressionSyntax_Type(uint begin, uint end) { }

        /// <summary>
        /// Edge visitor for Parameter edge which is called when the subtree of this edge is started.
        /// </summary>
        /// <param name="begin">[in] The id of the node the edge starts from.</param>
        /// <param name="end">[in] The id of the node the edge points to.</param>
        public virtual void visitSimpleLambdaExpressionSyntax_Parameter(uint begin, uint end) { }

        /// <summary>
        /// Edge end visitor for Parameter edge which is called after the subtree of this edge is finished.
        /// </summary>
        /// <param name="begin">[in] The id of the node the edge starts from.</param>
        /// <param name="end">[in] The id of the node the edge points to.</param>
        public virtual void visitEndSimpleLambdaExpressionSyntax_Parameter(uint begin, uint end) { }

        /// <summary>
        /// Edge visitor for Type edge which is called when the subtree of this edge is started.
        /// </summary>
        /// <param name="begin">[in] The id of the node the edge starts from.</param>
        /// <param name="end">[in] The id of the node the edge points to.</param>
        public virtual void visitSizeOfExpressionSyntax_Type(uint begin, uint end) { }

        /// <summary>
        /// Edge end visitor for Type edge which is called after the subtree of this edge is finished.
        /// </summary>
        /// <param name="begin">[in] The id of the node the edge starts from.</param>
        /// <param name="end">[in] The id of the node the edge points to.</param>
        public virtual void visitEndSizeOfExpressionSyntax_Type(uint begin, uint end) { }

        /// <summary>
        /// Edge visitor for Type edge which is called when the subtree of this edge is started.
        /// </summary>
        /// <param name="begin">[in] The id of the node the edge starts from.</param>
        /// <param name="end">[in] The id of the node the edge points to.</param>
        public virtual void visitStackAllocArrayCreationExpressionSyntax_Type(uint begin, uint end) { }

        /// <summary>
        /// Edge end visitor for Type edge which is called after the subtree of this edge is finished.
        /// </summary>
        /// <param name="begin">[in] The id of the node the edge starts from.</param>
        /// <param name="end">[in] The id of the node the edge points to.</param>
        public virtual void visitEndStackAllocArrayCreationExpressionSyntax_Type(uint begin, uint end) { }

        /// <summary>
        /// Edge visitor for Type edge which is called when the subtree of this edge is started.
        /// </summary>
        /// <param name="begin">[in] The id of the node the edge starts from.</param>
        /// <param name="end">[in] The id of the node the edge points to.</param>
        public virtual void visitTypeOfExpressionSyntax_Type(uint begin, uint end) { }

        /// <summary>
        /// Edge end visitor for Type edge which is called after the subtree of this edge is finished.
        /// </summary>
        /// <param name="begin">[in] The id of the node the edge starts from.</param>
        /// <param name="end">[in] The id of the node the edge points to.</param>
        public virtual void visitEndTypeOfExpressionSyntax_Type(uint begin, uint end) { }

        /// <summary>
        /// Edge visitor for OriginalDefinition edge which.
        /// </summary>
        /// <param name="begin">[in] The id of the node the edge starts from.</param>
        /// <param name="end">[in] The id of the node the edge points to.</param>
        public virtual void visitTypeSyntax_OriginalDefinition(uint begin, uint end) { }

        /// <summary>
        /// Edge end visitor for OriginalDefinition edge which is called after the visit pair of this edge is called.
        /// </summary>
        /// <param name="begin">[in] The id of the node the edge starts from.</param>
        /// <param name="end">[in] The id of the node the edge points to.</param>
        public virtual void visitEndTypeSyntax_OriginalDefinition(uint begin, uint end) { }

        /// <summary>
        /// Edge visitor for Statements edge which is called when the subtree of this edge is started.
        /// </summary>
        /// <param name="begin">[in] The id of the node the edge starts from.</param>
        /// <param name="end">[in] The id of the node the edge points to.</param>
        public virtual void visitBlockSyntax_Statements(uint begin, uint end) { }

        /// <summary>
        /// Edge end visitor for Statements edge which is called after the subtree of this edge is finished.
        /// </summary>
        /// <param name="begin">[in] The id of the node the edge starts from.</param>
        /// <param name="end">[in] The id of the node the edge points to.</param>
        public virtual void visitEndBlockSyntax_Statements(uint begin, uint end) { }

        /// <summary>
        /// Edge visitor for Block edge which is called when the subtree of this edge is started.
        /// </summary>
        /// <param name="begin">[in] The id of the node the edge starts from.</param>
        /// <param name="end">[in] The id of the node the edge points to.</param>
        public virtual void visitCheckedStatementSyntax_Block(uint begin, uint end) { }

        /// <summary>
        /// Edge end visitor for Block edge which is called after the subtree of this edge is finished.
        /// </summary>
        /// <param name="begin">[in] The id of the node the edge starts from.</param>
        /// <param name="end">[in] The id of the node the edge points to.</param>
        public virtual void visitEndCheckedStatementSyntax_Block(uint begin, uint end) { }

        /// <summary>
        /// Edge visitor for Condition edge which is called when the subtree of this edge is started.
        /// </summary>
        /// <param name="begin">[in] The id of the node the edge starts from.</param>
        /// <param name="end">[in] The id of the node the edge points to.</param>
        public virtual void visitDoStatementSyntax_Condition(uint begin, uint end) { }

        /// <summary>
        /// Edge end visitor for Condition edge which is called after the subtree of this edge is finished.
        /// </summary>
        /// <param name="begin">[in] The id of the node the edge starts from.</param>
        /// <param name="end">[in] The id of the node the edge points to.</param>
        public virtual void visitEndDoStatementSyntax_Condition(uint begin, uint end) { }

        /// <summary>
        /// Edge visitor for Statement edge which is called when the subtree of this edge is started.
        /// </summary>
        /// <param name="begin">[in] The id of the node the edge starts from.</param>
        /// <param name="end">[in] The id of the node the edge points to.</param>
        public virtual void visitDoStatementSyntax_Statement(uint begin, uint end) { }

        /// <summary>
        /// Edge end visitor for Statement edge which is called after the subtree of this edge is finished.
        /// </summary>
        /// <param name="begin">[in] The id of the node the edge starts from.</param>
        /// <param name="end">[in] The id of the node the edge points to.</param>
        public virtual void visitEndDoStatementSyntax_Statement(uint begin, uint end) { }

        /// <summary>
        /// Edge visitor for Expression edge which is called when the subtree of this edge is started.
        /// </summary>
        /// <param name="begin">[in] The id of the node the edge starts from.</param>
        /// <param name="end">[in] The id of the node the edge points to.</param>
        public virtual void visitExpressionStatementSyntax_Expression(uint begin, uint end) { }

        /// <summary>
        /// Edge end visitor for Expression edge which is called after the subtree of this edge is finished.
        /// </summary>
        /// <param name="begin">[in] The id of the node the edge starts from.</param>
        /// <param name="end">[in] The id of the node the edge points to.</param>
        public virtual void visitEndExpressionStatementSyntax_Expression(uint begin, uint end) { }

        /// <summary>
        /// Edge visitor for Declaration edge which is called when the subtree of this edge is started.
        /// </summary>
        /// <param name="begin">[in] The id of the node the edge starts from.</param>
        /// <param name="end">[in] The id of the node the edge points to.</param>
        public virtual void visitFixedStatementSyntax_Declaration(uint begin, uint end) { }

        /// <summary>
        /// Edge end visitor for Declaration edge which is called after the subtree of this edge is finished.
        /// </summary>
        /// <param name="begin">[in] The id of the node the edge starts from.</param>
        /// <param name="end">[in] The id of the node the edge points to.</param>
        public virtual void visitEndFixedStatementSyntax_Declaration(uint begin, uint end) { }

        /// <summary>
        /// Edge visitor for Statement edge which is called when the subtree of this edge is started.
        /// </summary>
        /// <param name="begin">[in] The id of the node the edge starts from.</param>
        /// <param name="end">[in] The id of the node the edge points to.</param>
        public virtual void visitFixedStatementSyntax_Statement(uint begin, uint end) { }

        /// <summary>
        /// Edge end visitor for Statement edge which is called after the subtree of this edge is finished.
        /// </summary>
        /// <param name="begin">[in] The id of the node the edge starts from.</param>
        /// <param name="end">[in] The id of the node the edge points to.</param>
        public virtual void visitEndFixedStatementSyntax_Statement(uint begin, uint end) { }

        /// <summary>
        /// Edge visitor for Expression edge which is called when the subtree of this edge is started.
        /// </summary>
        /// <param name="begin">[in] The id of the node the edge starts from.</param>
        /// <param name="end">[in] The id of the node the edge points to.</param>
        public virtual void visitForEachStatementSyntax_Expression(uint begin, uint end) { }

        /// <summary>
        /// Edge end visitor for Expression edge which is called after the subtree of this edge is finished.
        /// </summary>
        /// <param name="begin">[in] The id of the node the edge starts from.</param>
        /// <param name="end">[in] The id of the node the edge points to.</param>
        public virtual void visitEndForEachStatementSyntax_Expression(uint begin, uint end) { }

        /// <summary>
        /// Edge visitor for Statement edge which is called when the subtree of this edge is started.
        /// </summary>
        /// <param name="begin">[in] The id of the node the edge starts from.</param>
        /// <param name="end">[in] The id of the node the edge points to.</param>
        public virtual void visitForEachStatementSyntax_Statement(uint begin, uint end) { }

        /// <summary>
        /// Edge end visitor for Statement edge which is called after the subtree of this edge is finished.
        /// </summary>
        /// <param name="begin">[in] The id of the node the edge starts from.</param>
        /// <param name="end">[in] The id of the node the edge points to.</param>
        public virtual void visitEndForEachStatementSyntax_Statement(uint begin, uint end) { }

        /// <summary>
        /// Edge visitor for Type edge which is called when the subtree of this edge is started.
        /// </summary>
        /// <param name="begin">[in] The id of the node the edge starts from.</param>
        /// <param name="end">[in] The id of the node the edge points to.</param>
        public virtual void visitForEachStatementSyntax_Type(uint begin, uint end) { }

        /// <summary>
        /// Edge end visitor for Type edge which is called after the subtree of this edge is finished.
        /// </summary>
        /// <param name="begin">[in] The id of the node the edge starts from.</param>
        /// <param name="end">[in] The id of the node the edge points to.</param>
        public virtual void visitEndForEachStatementSyntax_Type(uint begin, uint end) { }

        /// <summary>
        /// Edge visitor for Condition edge which is called when the subtree of this edge is started.
        /// </summary>
        /// <param name="begin">[in] The id of the node the edge starts from.</param>
        /// <param name="end">[in] The id of the node the edge points to.</param>
        public virtual void visitForStatementSyntax_Condition(uint begin, uint end) { }

        /// <summary>
        /// Edge end visitor for Condition edge which is called after the subtree of this edge is finished.
        /// </summary>
        /// <param name="begin">[in] The id of the node the edge starts from.</param>
        /// <param name="end">[in] The id of the node the edge points to.</param>
        public virtual void visitEndForStatementSyntax_Condition(uint begin, uint end) { }

        /// <summary>
        /// Edge visitor for Declaration edge which is called when the subtree of this edge is started.
        /// </summary>
        /// <param name="begin">[in] The id of the node the edge starts from.</param>
        /// <param name="end">[in] The id of the node the edge points to.</param>
        public virtual void visitForStatementSyntax_Declaration(uint begin, uint end) { }

        /// <summary>
        /// Edge end visitor for Declaration edge which is called after the subtree of this edge is finished.
        /// </summary>
        /// <param name="begin">[in] The id of the node the edge starts from.</param>
        /// <param name="end">[in] The id of the node the edge points to.</param>
        public virtual void visitEndForStatementSyntax_Declaration(uint begin, uint end) { }

        /// <summary>
        /// Edge visitor for Incrementors edge which is called when the subtree of this edge is started.
        /// </summary>
        /// <param name="begin">[in] The id of the node the edge starts from.</param>
        /// <param name="end">[in] The id of the node the edge points to.</param>
        public virtual void visitForStatementSyntax_Incrementors(uint begin, uint end) { }

        /// <summary>
        /// Edge end visitor for Incrementors edge which is called after the subtree of this edge is finished.
        /// </summary>
        /// <param name="begin">[in] The id of the node the edge starts from.</param>
        /// <param name="end">[in] The id of the node the edge points to.</param>
        public virtual void visitEndForStatementSyntax_Incrementors(uint begin, uint end) { }

        /// <summary>
        /// Edge visitor for Initializers edge which is called when the subtree of this edge is started.
        /// </summary>
        /// <param name="begin">[in] The id of the node the edge starts from.</param>
        /// <param name="end">[in] The id of the node the edge points to.</param>
        public virtual void visitForStatementSyntax_Initializers(uint begin, uint end) { }

        /// <summary>
        /// Edge end visitor for Initializers edge which is called after the subtree of this edge is finished.
        /// </summary>
        /// <param name="begin">[in] The id of the node the edge starts from.</param>
        /// <param name="end">[in] The id of the node the edge points to.</param>
        public virtual void visitEndForStatementSyntax_Initializers(uint begin, uint end) { }

        /// <summary>
        /// Edge visitor for Statement edge which is called when the subtree of this edge is started.
        /// </summary>
        /// <param name="begin">[in] The id of the node the edge starts from.</param>
        /// <param name="end">[in] The id of the node the edge points to.</param>
        public virtual void visitForStatementSyntax_Statement(uint begin, uint end) { }

        /// <summary>
        /// Edge end visitor for Statement edge which is called after the subtree of this edge is finished.
        /// </summary>
        /// <param name="begin">[in] The id of the node the edge starts from.</param>
        /// <param name="end">[in] The id of the node the edge points to.</param>
        public virtual void visitEndForStatementSyntax_Statement(uint begin, uint end) { }

        /// <summary>
        /// Edge visitor for Expression edge which is called when the subtree of this edge is started.
        /// </summary>
        /// <param name="begin">[in] The id of the node the edge starts from.</param>
        /// <param name="end">[in] The id of the node the edge points to.</param>
        public virtual void visitGotoStatementSyntax_Expression(uint begin, uint end) { }

        /// <summary>
        /// Edge end visitor for Expression edge which is called after the subtree of this edge is finished.
        /// </summary>
        /// <param name="begin">[in] The id of the node the edge starts from.</param>
        /// <param name="end">[in] The id of the node the edge points to.</param>
        public virtual void visitEndGotoStatementSyntax_Expression(uint begin, uint end) { }

        /// <summary>
        /// Edge visitor for Condition edge which is called when the subtree of this edge is started.
        /// </summary>
        /// <param name="begin">[in] The id of the node the edge starts from.</param>
        /// <param name="end">[in] The id of the node the edge points to.</param>
        public virtual void visitIfStatementSyntax_Condition(uint begin, uint end) { }

        /// <summary>
        /// Edge end visitor for Condition edge which is called after the subtree of this edge is finished.
        /// </summary>
        /// <param name="begin">[in] The id of the node the edge starts from.</param>
        /// <param name="end">[in] The id of the node the edge points to.</param>
        public virtual void visitEndIfStatementSyntax_Condition(uint begin, uint end) { }

        /// <summary>
        /// Edge visitor for Else edge which is called when the subtree of this edge is started.
        /// </summary>
        /// <param name="begin">[in] The id of the node the edge starts from.</param>
        /// <param name="end">[in] The id of the node the edge points to.</param>
        public virtual void visitIfStatementSyntax_Else(uint begin, uint end) { }

        /// <summary>
        /// Edge end visitor for Else edge which is called after the subtree of this edge is finished.
        /// </summary>
        /// <param name="begin">[in] The id of the node the edge starts from.</param>
        /// <param name="end">[in] The id of the node the edge points to.</param>
        public virtual void visitEndIfStatementSyntax_Else(uint begin, uint end) { }

        /// <summary>
        /// Edge visitor for Statement edge which is called when the subtree of this edge is started.
        /// </summary>
        /// <param name="begin">[in] The id of the node the edge starts from.</param>
        /// <param name="end">[in] The id of the node the edge points to.</param>
        public virtual void visitIfStatementSyntax_Statement(uint begin, uint end) { }

        /// <summary>
        /// Edge end visitor for Statement edge which is called after the subtree of this edge is finished.
        /// </summary>
        /// <param name="begin">[in] The id of the node the edge starts from.</param>
        /// <param name="end">[in] The id of the node the edge points to.</param>
        public virtual void visitEndIfStatementSyntax_Statement(uint begin, uint end) { }

        /// <summary>
        /// Edge visitor for Statement edge which is called when the subtree of this edge is started.
        /// </summary>
        /// <param name="begin">[in] The id of the node the edge starts from.</param>
        /// <param name="end">[in] The id of the node the edge points to.</param>
        public virtual void visitLabeledStatementSyntax_Statement(uint begin, uint end) { }

        /// <summary>
        /// Edge end visitor for Statement edge which is called after the subtree of this edge is finished.
        /// </summary>
        /// <param name="begin">[in] The id of the node the edge starts from.</param>
        /// <param name="end">[in] The id of the node the edge points to.</param>
        public virtual void visitEndLabeledStatementSyntax_Statement(uint begin, uint end) { }

        /// <summary>
        /// Edge visitor for Declaration edge which is called when the subtree of this edge is started.
        /// </summary>
        /// <param name="begin">[in] The id of the node the edge starts from.</param>
        /// <param name="end">[in] The id of the node the edge points to.</param>
        public virtual void visitLocalDeclarationStatementSyntax_Declaration(uint begin, uint end) { }

        /// <summary>
        /// Edge end visitor for Declaration edge which is called after the subtree of this edge is finished.
        /// </summary>
        /// <param name="begin">[in] The id of the node the edge starts from.</param>
        /// <param name="end">[in] The id of the node the edge points to.</param>
        public virtual void visitEndLocalDeclarationStatementSyntax_Declaration(uint begin, uint end) { }

        /// <summary>
        /// Edge visitor for Expression edge which is called when the subtree of this edge is started.
        /// </summary>
        /// <param name="begin">[in] The id of the node the edge starts from.</param>
        /// <param name="end">[in] The id of the node the edge points to.</param>
        public virtual void visitLockStatementSyntax_Expression(uint begin, uint end) { }

        /// <summary>
        /// Edge end visitor for Expression edge which is called after the subtree of this edge is finished.
        /// </summary>
        /// <param name="begin">[in] The id of the node the edge starts from.</param>
        /// <param name="end">[in] The id of the node the edge points to.</param>
        public virtual void visitEndLockStatementSyntax_Expression(uint begin, uint end) { }

        /// <summary>
        /// Edge visitor for Statement edge which is called when the subtree of this edge is started.
        /// </summary>
        /// <param name="begin">[in] The id of the node the edge starts from.</param>
        /// <param name="end">[in] The id of the node the edge points to.</param>
        public virtual void visitLockStatementSyntax_Statement(uint begin, uint end) { }

        /// <summary>
        /// Edge end visitor for Statement edge which is called after the subtree of this edge is finished.
        /// </summary>
        /// <param name="begin">[in] The id of the node the edge starts from.</param>
        /// <param name="end">[in] The id of the node the edge points to.</param>
        public virtual void visitEndLockStatementSyntax_Statement(uint begin, uint end) { }

        /// <summary>
        /// Edge visitor for Expression edge which is called when the subtree of this edge is started.
        /// </summary>
        /// <param name="begin">[in] The id of the node the edge starts from.</param>
        /// <param name="end">[in] The id of the node the edge points to.</param>
        public virtual void visitReturnStatementSyntax_Expression(uint begin, uint end) { }

        /// <summary>
        /// Edge end visitor for Expression edge which is called after the subtree of this edge is finished.
        /// </summary>
        /// <param name="begin">[in] The id of the node the edge starts from.</param>
        /// <param name="end">[in] The id of the node the edge points to.</param>
        public virtual void visitEndReturnStatementSyntax_Expression(uint begin, uint end) { }

        /// <summary>
        /// Edge visitor for Expression edge which is called when the subtree of this edge is started.
        /// </summary>
        /// <param name="begin">[in] The id of the node the edge starts from.</param>
        /// <param name="end">[in] The id of the node the edge points to.</param>
        public virtual void visitSwitchStatementSyntax_Expression(uint begin, uint end) { }

        /// <summary>
        /// Edge end visitor for Expression edge which is called after the subtree of this edge is finished.
        /// </summary>
        /// <param name="begin">[in] The id of the node the edge starts from.</param>
        /// <param name="end">[in] The id of the node the edge points to.</param>
        public virtual void visitEndSwitchStatementSyntax_Expression(uint begin, uint end) { }

        /// <summary>
        /// Edge visitor for Sections edge which is called when the subtree of this edge is started.
        /// </summary>
        /// <param name="begin">[in] The id of the node the edge starts from.</param>
        /// <param name="end">[in] The id of the node the edge points to.</param>
        public virtual void visitSwitchStatementSyntax_Sections(uint begin, uint end) { }

        /// <summary>
        /// Edge end visitor for Sections edge which is called after the subtree of this edge is finished.
        /// </summary>
        /// <param name="begin">[in] The id of the node the edge starts from.</param>
        /// <param name="end">[in] The id of the node the edge points to.</param>
        public virtual void visitEndSwitchStatementSyntax_Sections(uint begin, uint end) { }

        /// <summary>
        /// Edge visitor for Expression edge which is called when the subtree of this edge is started.
        /// </summary>
        /// <param name="begin">[in] The id of the node the edge starts from.</param>
        /// <param name="end">[in] The id of the node the edge points to.</param>
        public virtual void visitThrowStatementSyntax_Expression(uint begin, uint end) { }

        /// <summary>
        /// Edge end visitor for Expression edge which is called after the subtree of this edge is finished.
        /// </summary>
        /// <param name="begin">[in] The id of the node the edge starts from.</param>
        /// <param name="end">[in] The id of the node the edge points to.</param>
        public virtual void visitEndThrowStatementSyntax_Expression(uint begin, uint end) { }

        /// <summary>
        /// Edge visitor for Block edge which is called when the subtree of this edge is started.
        /// </summary>
        /// <param name="begin">[in] The id of the node the edge starts from.</param>
        /// <param name="end">[in] The id of the node the edge points to.</param>
        public virtual void visitTryStatementSyntax_Block(uint begin, uint end) { }

        /// <summary>
        /// Edge end visitor for Block edge which is called after the subtree of this edge is finished.
        /// </summary>
        /// <param name="begin">[in] The id of the node the edge starts from.</param>
        /// <param name="end">[in] The id of the node the edge points to.</param>
        public virtual void visitEndTryStatementSyntax_Block(uint begin, uint end) { }

        /// <summary>
        /// Edge visitor for Catches edge which is called when the subtree of this edge is started.
        /// </summary>
        /// <param name="begin">[in] The id of the node the edge starts from.</param>
        /// <param name="end">[in] The id of the node the edge points to.</param>
        public virtual void visitTryStatementSyntax_Catches(uint begin, uint end) { }

        /// <summary>
        /// Edge end visitor for Catches edge which is called after the subtree of this edge is finished.
        /// </summary>
        /// <param name="begin">[in] The id of the node the edge starts from.</param>
        /// <param name="end">[in] The id of the node the edge points to.</param>
        public virtual void visitEndTryStatementSyntax_Catches(uint begin, uint end) { }

        /// <summary>
        /// Edge visitor for Finally edge which is called when the subtree of this edge is started.
        /// </summary>
        /// <param name="begin">[in] The id of the node the edge starts from.</param>
        /// <param name="end">[in] The id of the node the edge points to.</param>
        public virtual void visitTryStatementSyntax_Finally(uint begin, uint end) { }

        /// <summary>
        /// Edge end visitor for Finally edge which is called after the subtree of this edge is finished.
        /// </summary>
        /// <param name="begin">[in] The id of the node the edge starts from.</param>
        /// <param name="end">[in] The id of the node the edge points to.</param>
        public virtual void visitEndTryStatementSyntax_Finally(uint begin, uint end) { }

        /// <summary>
        /// Edge visitor for Block edge which is called when the subtree of this edge is started.
        /// </summary>
        /// <param name="begin">[in] The id of the node the edge starts from.</param>
        /// <param name="end">[in] The id of the node the edge points to.</param>
        public virtual void visitUnsafeStatementSyntax_Block(uint begin, uint end) { }

        /// <summary>
        /// Edge end visitor for Block edge which is called after the subtree of this edge is finished.
        /// </summary>
        /// <param name="begin">[in] The id of the node the edge starts from.</param>
        /// <param name="end">[in] The id of the node the edge points to.</param>
        public virtual void visitEndUnsafeStatementSyntax_Block(uint begin, uint end) { }

        /// <summary>
        /// Edge visitor for Declaration edge which is called when the subtree of this edge is started.
        /// </summary>
        /// <param name="begin">[in] The id of the node the edge starts from.</param>
        /// <param name="end">[in] The id of the node the edge points to.</param>
        public virtual void visitUsingStatementSyntax_Declaration(uint begin, uint end) { }

        /// <summary>
        /// Edge end visitor for Declaration edge which is called after the subtree of this edge is finished.
        /// </summary>
        /// <param name="begin">[in] The id of the node the edge starts from.</param>
        /// <param name="end">[in] The id of the node the edge points to.</param>
        public virtual void visitEndUsingStatementSyntax_Declaration(uint begin, uint end) { }

        /// <summary>
        /// Edge visitor for Expression edge which is called when the subtree of this edge is started.
        /// </summary>
        /// <param name="begin">[in] The id of the node the edge starts from.</param>
        /// <param name="end">[in] The id of the node the edge points to.</param>
        public virtual void visitUsingStatementSyntax_Expression(uint begin, uint end) { }

        /// <summary>
        /// Edge end visitor for Expression edge which is called after the subtree of this edge is finished.
        /// </summary>
        /// <param name="begin">[in] The id of the node the edge starts from.</param>
        /// <param name="end">[in] The id of the node the edge points to.</param>
        public virtual void visitEndUsingStatementSyntax_Expression(uint begin, uint end) { }

        /// <summary>
        /// Edge visitor for Statement edge which is called when the subtree of this edge is started.
        /// </summary>
        /// <param name="begin">[in] The id of the node the edge starts from.</param>
        /// <param name="end">[in] The id of the node the edge points to.</param>
        public virtual void visitUsingStatementSyntax_Statement(uint begin, uint end) { }

        /// <summary>
        /// Edge end visitor for Statement edge which is called after the subtree of this edge is finished.
        /// </summary>
        /// <param name="begin">[in] The id of the node the edge starts from.</param>
        /// <param name="end">[in] The id of the node the edge points to.</param>
        public virtual void visitEndUsingStatementSyntax_Statement(uint begin, uint end) { }

        /// <summary>
        /// Edge visitor for Condition edge which is called when the subtree of this edge is started.
        /// </summary>
        /// <param name="begin">[in] The id of the node the edge starts from.</param>
        /// <param name="end">[in] The id of the node the edge points to.</param>
        public virtual void visitWhileStatementSyntax_Condition(uint begin, uint end) { }

        /// <summary>
        /// Edge end visitor for Condition edge which is called after the subtree of this edge is finished.
        /// </summary>
        /// <param name="begin">[in] The id of the node the edge starts from.</param>
        /// <param name="end">[in] The id of the node the edge points to.</param>
        public virtual void visitEndWhileStatementSyntax_Condition(uint begin, uint end) { }

        /// <summary>
        /// Edge visitor for Statement edge which is called when the subtree of this edge is started.
        /// </summary>
        /// <param name="begin">[in] The id of the node the edge starts from.</param>
        /// <param name="end">[in] The id of the node the edge points to.</param>
        public virtual void visitWhileStatementSyntax_Statement(uint begin, uint end) { }

        /// <summary>
        /// Edge end visitor for Statement edge which is called after the subtree of this edge is finished.
        /// </summary>
        /// <param name="begin">[in] The id of the node the edge starts from.</param>
        /// <param name="end">[in] The id of the node the edge points to.</param>
        public virtual void visitEndWhileStatementSyntax_Statement(uint begin, uint end) { }

        /// <summary>
        /// Edge visitor for Expression edge which is called when the subtree of this edge is started.
        /// </summary>
        /// <param name="begin">[in] The id of the node the edge starts from.</param>
        /// <param name="end">[in] The id of the node the edge points to.</param>
        public virtual void visitYieldStatementSyntax_Expression(uint begin, uint end) { }

        /// <summary>
        /// Edge end visitor for Expression edge which is called after the subtree of this edge is finished.
        /// </summary>
        /// <param name="begin">[in] The id of the node the edge starts from.</param>
        /// <param name="end">[in] The id of the node the edge points to.</param>
        public virtual void visitEndYieldStatementSyntax_Expression(uint begin, uint end) { }

        /// <summary>
        /// Edge visitor for AttributeLists edge which is called when the subtree of this edge is started.
        /// </summary>
        /// <param name="begin">[in] The id of the node the edge starts from.</param>
        /// <param name="end">[in] The id of the node the edge points to.</param>
        public virtual void visitAccessorDeclarationSyntax_AttributeLists(uint begin, uint end) { }

        /// <summary>
        /// Edge end visitor for AttributeLists edge which is called after the subtree of this edge is finished.
        /// </summary>
        /// <param name="begin">[in] The id of the node the edge starts from.</param>
        /// <param name="end">[in] The id of the node the edge points to.</param>
        public virtual void visitEndAccessorDeclarationSyntax_AttributeLists(uint begin, uint end) { }

        /// <summary>
        /// Edge visitor for Body edge which is called when the subtree of this edge is started.
        /// </summary>
        /// <param name="begin">[in] The id of the node the edge starts from.</param>
        /// <param name="end">[in] The id of the node the edge points to.</param>
        public virtual void visitAccessorDeclarationSyntax_Body(uint begin, uint end) { }

        /// <summary>
        /// Edge end visitor for Body edge which is called after the subtree of this edge is finished.
        /// </summary>
        /// <param name="begin">[in] The id of the node the edge starts from.</param>
        /// <param name="end">[in] The id of the node the edge points to.</param>
        public virtual void visitEndAccessorDeclarationSyntax_Body(uint begin, uint end) { }

        /// <summary>
        /// Edge visitor for Accessors edge which is called when the subtree of this edge is started.
        /// </summary>
        /// <param name="begin">[in] The id of the node the edge starts from.</param>
        /// <param name="end">[in] The id of the node the edge points to.</param>
        public virtual void visitAccessorListSyntax_Accessors(uint begin, uint end) { }

        /// <summary>
        /// Edge end visitor for Accessors edge which is called after the subtree of this edge is finished.
        /// </summary>
        /// <param name="begin">[in] The id of the node the edge starts from.</param>
        /// <param name="end">[in] The id of the node the edge points to.</param>
        public virtual void visitEndAccessorListSyntax_Accessors(uint begin, uint end) { }

        /// <summary>
        /// Edge visitor for Expression edge which is called when the subtree of this edge is started.
        /// </summary>
        /// <param name="begin">[in] The id of the node the edge starts from.</param>
        /// <param name="end">[in] The id of the node the edge points to.</param>
        public virtual void visitAnonymousObjectMemberDeclaratorSyntax_Expression(uint begin, uint end) { }

        /// <summary>
        /// Edge end visitor for Expression edge which is called after the subtree of this edge is finished.
        /// </summary>
        /// <param name="begin">[in] The id of the node the edge starts from.</param>
        /// <param name="end">[in] The id of the node the edge points to.</param>
        public virtual void visitEndAnonymousObjectMemberDeclaratorSyntax_Expression(uint begin, uint end) { }

        /// <summary>
        /// Edge visitor for NameEquals edge which is called when the subtree of this edge is started.
        /// </summary>
        /// <param name="begin">[in] The id of the node the edge starts from.</param>
        /// <param name="end">[in] The id of the node the edge points to.</param>
        public virtual void visitAnonymousObjectMemberDeclaratorSyntax_NameEquals(uint begin, uint end) { }

        /// <summary>
        /// Edge end visitor for NameEquals edge which is called after the subtree of this edge is finished.
        /// </summary>
        /// <param name="begin">[in] The id of the node the edge starts from.</param>
        /// <param name="end">[in] The id of the node the edge points to.</param>
        public virtual void visitEndAnonymousObjectMemberDeclaratorSyntax_NameEquals(uint begin, uint end) { }

        /// <summary>
        /// Edge visitor for Expression edge which is called when the subtree of this edge is started.
        /// </summary>
        /// <param name="begin">[in] The id of the node the edge starts from.</param>
        /// <param name="end">[in] The id of the node the edge points to.</param>
        public virtual void visitArgumentSyntax_Expression(uint begin, uint end) { }

        /// <summary>
        /// Edge end visitor for Expression edge which is called after the subtree of this edge is finished.
        /// </summary>
        /// <param name="begin">[in] The id of the node the edge starts from.</param>
        /// <param name="end">[in] The id of the node the edge points to.</param>
        public virtual void visitEndArgumentSyntax_Expression(uint begin, uint end) { }

        /// <summary>
        /// Edge visitor for NameColon edge which is called when the subtree of this edge is started.
        /// </summary>
        /// <param name="begin">[in] The id of the node the edge starts from.</param>
        /// <param name="end">[in] The id of the node the edge points to.</param>
        public virtual void visitArgumentSyntax_NameColon(uint begin, uint end) { }

        /// <summary>
        /// Edge end visitor for NameColon edge which is called after the subtree of this edge is finished.
        /// </summary>
        /// <param name="begin">[in] The id of the node the edge starts from.</param>
        /// <param name="end">[in] The id of the node the edge points to.</param>
        public virtual void visitEndArgumentSyntax_NameColon(uint begin, uint end) { }

        /// <summary>
        /// Edge visitor for Sizes edge which is called when the subtree of this edge is started.
        /// </summary>
        /// <param name="begin">[in] The id of the node the edge starts from.</param>
        /// <param name="end">[in] The id of the node the edge points to.</param>
        public virtual void visitArrayRankSpecifierSyntax_Sizes(uint begin, uint end) { }

        /// <summary>
        /// Edge end visitor for Sizes edge which is called after the subtree of this edge is finished.
        /// </summary>
        /// <param name="begin">[in] The id of the node the edge starts from.</param>
        /// <param name="end">[in] The id of the node the edge points to.</param>
        public virtual void visitEndArrayRankSpecifierSyntax_Sizes(uint begin, uint end) { }

        /// <summary>
        /// Edge visitor for Expression edge which is called when the subtree of this edge is started.
        /// </summary>
        /// <param name="begin">[in] The id of the node the edge starts from.</param>
        /// <param name="end">[in] The id of the node the edge points to.</param>
        public virtual void visitArrowExpressionClauseSyntax_Expression(uint begin, uint end) { }

        /// <summary>
        /// Edge end visitor for Expression edge which is called after the subtree of this edge is finished.
        /// </summary>
        /// <param name="begin">[in] The id of the node the edge starts from.</param>
        /// <param name="end">[in] The id of the node the edge points to.</param>
        public virtual void visitEndArrowExpressionClauseSyntax_Expression(uint begin, uint end) { }

        /// <summary>
        /// Edge visitor for Arguments edge which is called when the subtree of this edge is started.
        /// </summary>
        /// <param name="begin">[in] The id of the node the edge starts from.</param>
        /// <param name="end">[in] The id of the node the edge points to.</param>
        public virtual void visitAttributeArgumentListSyntax_Arguments(uint begin, uint end) { }

        /// <summary>
        /// Edge end visitor for Arguments edge which is called after the subtree of this edge is finished.
        /// </summary>
        /// <param name="begin">[in] The id of the node the edge starts from.</param>
        /// <param name="end">[in] The id of the node the edge points to.</param>
        public virtual void visitEndAttributeArgumentListSyntax_Arguments(uint begin, uint end) { }

        /// <summary>
        /// Edge visitor for Expression edge which is called when the subtree of this edge is started.
        /// </summary>
        /// <param name="begin">[in] The id of the node the edge starts from.</param>
        /// <param name="end">[in] The id of the node the edge points to.</param>
        public virtual void visitAttributeArgumentSyntax_Expression(uint begin, uint end) { }

        /// <summary>
        /// Edge end visitor for Expression edge which is called after the subtree of this edge is finished.
        /// </summary>
        /// <param name="begin">[in] The id of the node the edge starts from.</param>
        /// <param name="end">[in] The id of the node the edge points to.</param>
        public virtual void visitEndAttributeArgumentSyntax_Expression(uint begin, uint end) { }

        /// <summary>
        /// Edge visitor for NameColon edge which is called when the subtree of this edge is started.
        /// </summary>
        /// <param name="begin">[in] The id of the node the edge starts from.</param>
        /// <param name="end">[in] The id of the node the edge points to.</param>
        public virtual void visitAttributeArgumentSyntax_NameColon(uint begin, uint end) { }

        /// <summary>
        /// Edge end visitor for NameColon edge which is called after the subtree of this edge is finished.
        /// </summary>
        /// <param name="begin">[in] The id of the node the edge starts from.</param>
        /// <param name="end">[in] The id of the node the edge points to.</param>
        public virtual void visitEndAttributeArgumentSyntax_NameColon(uint begin, uint end) { }

        /// <summary>
        /// Edge visitor for NameEquals edge which is called when the subtree of this edge is started.
        /// </summary>
        /// <param name="begin">[in] The id of the node the edge starts from.</param>
        /// <param name="end">[in] The id of the node the edge points to.</param>
        public virtual void visitAttributeArgumentSyntax_NameEquals(uint begin, uint end) { }

        /// <summary>
        /// Edge end visitor for NameEquals edge which is called after the subtree of this edge is finished.
        /// </summary>
        /// <param name="begin">[in] The id of the node the edge starts from.</param>
        /// <param name="end">[in] The id of the node the edge points to.</param>
        public virtual void visitEndAttributeArgumentSyntax_NameEquals(uint begin, uint end) { }

        /// <summary>
        /// Edge visitor for Attributes edge which is called when the subtree of this edge is started.
        /// </summary>
        /// <param name="begin">[in] The id of the node the edge starts from.</param>
        /// <param name="end">[in] The id of the node the edge points to.</param>
        public virtual void visitAttributeListSyntax_Attributes(uint begin, uint end) { }

        /// <summary>
        /// Edge end visitor for Attributes edge which is called after the subtree of this edge is finished.
        /// </summary>
        /// <param name="begin">[in] The id of the node the edge starts from.</param>
        /// <param name="end">[in] The id of the node the edge points to.</param>
        public virtual void visitEndAttributeListSyntax_Attributes(uint begin, uint end) { }

        /// <summary>
        /// Edge visitor for Target edge which is called when the subtree of this edge is started.
        /// </summary>
        /// <param name="begin">[in] The id of the node the edge starts from.</param>
        /// <param name="end">[in] The id of the node the edge points to.</param>
        public virtual void visitAttributeListSyntax_Target(uint begin, uint end) { }

        /// <summary>
        /// Edge end visitor for Target edge which is called after the subtree of this edge is finished.
        /// </summary>
        /// <param name="begin">[in] The id of the node the edge starts from.</param>
        /// <param name="end">[in] The id of the node the edge points to.</param>
        public virtual void visitEndAttributeListSyntax_Target(uint begin, uint end) { }

        /// <summary>
        /// Edge visitor for ArgumentList edge which is called when the subtree of this edge is started.
        /// </summary>
        /// <param name="begin">[in] The id of the node the edge starts from.</param>
        /// <param name="end">[in] The id of the node the edge points to.</param>
        public virtual void visitAttributeSyntax_ArgumentList(uint begin, uint end) { }

        /// <summary>
        /// Edge end visitor for ArgumentList edge which is called after the subtree of this edge is finished.
        /// </summary>
        /// <param name="begin">[in] The id of the node the edge starts from.</param>
        /// <param name="end">[in] The id of the node the edge points to.</param>
        public virtual void visitEndAttributeSyntax_ArgumentList(uint begin, uint end) { }

        /// <summary>
        /// Edge visitor for Name edge which is called when the subtree of this edge is started.
        /// </summary>
        /// <param name="begin">[in] The id of the node the edge starts from.</param>
        /// <param name="end">[in] The id of the node the edge points to.</param>
        public virtual void visitAttributeSyntax_Name(uint begin, uint end) { }

        /// <summary>
        /// Edge end visitor for Name edge which is called after the subtree of this edge is finished.
        /// </summary>
        /// <param name="begin">[in] The id of the node the edge starts from.</param>
        /// <param name="end">[in] The id of the node the edge points to.</param>
        public virtual void visitEndAttributeSyntax_Name(uint begin, uint end) { }

        /// <summary>
        /// Edge visitor for Arguments edge which is called when the subtree of this edge is started.
        /// </summary>
        /// <param name="begin">[in] The id of the node the edge starts from.</param>
        /// <param name="end">[in] The id of the node the edge points to.</param>
        public virtual void visitBaseArgumentListSyntax_Arguments(uint begin, uint end) { }

        /// <summary>
        /// Edge end visitor for Arguments edge which is called after the subtree of this edge is finished.
        /// </summary>
        /// <param name="begin">[in] The id of the node the edge starts from.</param>
        /// <param name="end">[in] The id of the node the edge points to.</param>
        public virtual void visitEndBaseArgumentListSyntax_Arguments(uint begin, uint end) { }

        /// <summary>
        /// Edge visitor for Parameters edge which is called when the subtree of this edge is started.
        /// </summary>
        /// <param name="begin">[in] The id of the node the edge starts from.</param>
        /// <param name="end">[in] The id of the node the edge points to.</param>
        public virtual void visitBaseCrefParameterListSyntax_Parameters(uint begin, uint end) { }

        /// <summary>
        /// Edge end visitor for Parameters edge which is called after the subtree of this edge is finished.
        /// </summary>
        /// <param name="begin">[in] The id of the node the edge starts from.</param>
        /// <param name="end">[in] The id of the node the edge points to.</param>
        public virtual void visitEndBaseCrefParameterListSyntax_Parameters(uint begin, uint end) { }

        /// <summary>
        /// Edge visitor for AttributeLists edge which is called when the subtree of this edge is started.
        /// </summary>
        /// <param name="begin">[in] The id of the node the edge starts from.</param>
        /// <param name="end">[in] The id of the node the edge points to.</param>
        public virtual void visitBaseFieldDeclarationSyntax_AttributeLists(uint begin, uint end) { }

        /// <summary>
        /// Edge end visitor for AttributeLists edge which is called after the subtree of this edge is finished.
        /// </summary>
        /// <param name="begin">[in] The id of the node the edge starts from.</param>
        /// <param name="end">[in] The id of the node the edge points to.</param>
        public virtual void visitEndBaseFieldDeclarationSyntax_AttributeLists(uint begin, uint end) { }

        /// <summary>
        /// Edge visitor for Declaration edge which is called when the subtree of this edge is started.
        /// </summary>
        /// <param name="begin">[in] The id of the node the edge starts from.</param>
        /// <param name="end">[in] The id of the node the edge points to.</param>
        public virtual void visitBaseFieldDeclarationSyntax_Declaration(uint begin, uint end) { }

        /// <summary>
        /// Edge end visitor for Declaration edge which is called after the subtree of this edge is finished.
        /// </summary>
        /// <param name="begin">[in] The id of the node the edge starts from.</param>
        /// <param name="end">[in] The id of the node the edge points to.</param>
        public virtual void visitEndBaseFieldDeclarationSyntax_Declaration(uint begin, uint end) { }

        /// <summary>
        /// Edge visitor for Types edge which is called when the subtree of this edge is started.
        /// </summary>
        /// <param name="begin">[in] The id of the node the edge starts from.</param>
        /// <param name="end">[in] The id of the node the edge points to.</param>
        public virtual void visitBaseListSyntax_Types(uint begin, uint end) { }

        /// <summary>
        /// Edge end visitor for Types edge which is called after the subtree of this edge is finished.
        /// </summary>
        /// <param name="begin">[in] The id of the node the edge starts from.</param>
        /// <param name="end">[in] The id of the node the edge points to.</param>
        public virtual void visitEndBaseListSyntax_Types(uint begin, uint end) { }

        /// <summary>
        /// Edge visitor for AccessedEnumMembers edge which.
        /// </summary>
        /// <param name="begin">[in] The id of the node the edge starts from.</param>
        /// <param name="end">[in] The id of the node the edge points to.</param>
        public virtual void visitBaseMethodDeclarationSyntax_AccessedEnumMembers(uint begin, uint end) { }

        /// <summary>
        /// Edge end visitor for AccessedEnumMembers edge which is called after the visit pair of this edge is called.
        /// </summary>
        /// <param name="begin">[in] The id of the node the edge starts from.</param>
        /// <param name="end">[in] The id of the node the edge points to.</param>
        public virtual void visitEndBaseMethodDeclarationSyntax_AccessedEnumMembers(uint begin, uint end) { }

        /// <summary>
        /// Edge visitor for AttributeLists edge which is called when the subtree of this edge is started.
        /// </summary>
        /// <param name="begin">[in] The id of the node the edge starts from.</param>
        /// <param name="end">[in] The id of the node the edge points to.</param>
        public virtual void visitBaseMethodDeclarationSyntax_AttributeLists(uint begin, uint end) { }

        /// <summary>
        /// Edge end visitor for AttributeLists edge which is called after the subtree of this edge is finished.
        /// </summary>
        /// <param name="begin">[in] The id of the node the edge starts from.</param>
        /// <param name="end">[in] The id of the node the edge points to.</param>
        public virtual void visitEndBaseMethodDeclarationSyntax_AttributeLists(uint begin, uint end) { }

        /// <summary>
        /// Edge visitor for Body edge which is called when the subtree of this edge is started.
        /// </summary>
        /// <param name="begin">[in] The id of the node the edge starts from.</param>
        /// <param name="end">[in] The id of the node the edge points to.</param>
        public virtual void visitBaseMethodDeclarationSyntax_Body(uint begin, uint end) { }

        /// <summary>
        /// Edge end visitor for Body edge which is called after the subtree of this edge is finished.
        /// </summary>
        /// <param name="begin">[in] The id of the node the edge starts from.</param>
        /// <param name="end">[in] The id of the node the edge points to.</param>
        public virtual void visitEndBaseMethodDeclarationSyntax_Body(uint begin, uint end) { }

        /// <summary>
        /// Edge visitor for ParameterList edge which is called when the subtree of this edge is started.
        /// </summary>
        /// <param name="begin">[in] The id of the node the edge starts from.</param>
        /// <param name="end">[in] The id of the node the edge points to.</param>
        public virtual void visitBaseMethodDeclarationSyntax_ParameterList(uint begin, uint end) { }

        /// <summary>
        /// Edge end visitor for ParameterList edge which is called after the subtree of this edge is finished.
        /// </summary>
        /// <param name="begin">[in] The id of the node the edge starts from.</param>
        /// <param name="end">[in] The id of the node the edge points to.</param>
        public virtual void visitEndBaseMethodDeclarationSyntax_ParameterList(uint begin, uint end) { }

        /// <summary>
        /// Edge visitor for Parameters edge which is called when the subtree of this edge is started.
        /// </summary>
        /// <param name="begin">[in] The id of the node the edge starts from.</param>
        /// <param name="end">[in] The id of the node the edge points to.</param>
        public virtual void visitBaseParameterListSyntax_Parameters(uint begin, uint end) { }

        /// <summary>
        /// Edge end visitor for Parameters edge which is called after the subtree of this edge is finished.
        /// </summary>
        /// <param name="begin">[in] The id of the node the edge starts from.</param>
        /// <param name="end">[in] The id of the node the edge points to.</param>
        public virtual void visitEndBaseParameterListSyntax_Parameters(uint begin, uint end) { }

        /// <summary>
        /// Edge visitor for AccessorList edge which is called when the subtree of this edge is started.
        /// </summary>
        /// <param name="begin">[in] The id of the node the edge starts from.</param>
        /// <param name="end">[in] The id of the node the edge points to.</param>
        public virtual void visitBasePropertyDeclarationSyntax_AccessorList(uint begin, uint end) { }

        /// <summary>
        /// Edge end visitor for AccessorList edge which is called after the subtree of this edge is finished.
        /// </summary>
        /// <param name="begin">[in] The id of the node the edge starts from.</param>
        /// <param name="end">[in] The id of the node the edge points to.</param>
        public virtual void visitEndBasePropertyDeclarationSyntax_AccessorList(uint begin, uint end) { }

        /// <summary>
        /// Edge visitor for AttributeLists edge which is called when the subtree of this edge is started.
        /// </summary>
        /// <param name="begin">[in] The id of the node the edge starts from.</param>
        /// <param name="end">[in] The id of the node the edge points to.</param>
        public virtual void visitBasePropertyDeclarationSyntax_AttributeLists(uint begin, uint end) { }

        /// <summary>
        /// Edge end visitor for AttributeLists edge which is called after the subtree of this edge is finished.
        /// </summary>
        /// <param name="begin">[in] The id of the node the edge starts from.</param>
        /// <param name="end">[in] The id of the node the edge points to.</param>
        public virtual void visitEndBasePropertyDeclarationSyntax_AttributeLists(uint begin, uint end) { }

        /// <summary>
        /// Edge visitor for ExplicitInterfaceSpecifier edge which is called when the subtree of this edge is started.
        /// </summary>
        /// <param name="begin">[in] The id of the node the edge starts from.</param>
        /// <param name="end">[in] The id of the node the edge points to.</param>
        public virtual void visitBasePropertyDeclarationSyntax_ExplicitInterfaceSpecifier(uint begin, uint end) { }

        /// <summary>
        /// Edge end visitor for ExplicitInterfaceSpecifier edge which is called after the subtree of this edge is finished.
        /// </summary>
        /// <param name="begin">[in] The id of the node the edge starts from.</param>
        /// <param name="end">[in] The id of the node the edge points to.</param>
        public virtual void visitEndBasePropertyDeclarationSyntax_ExplicitInterfaceSpecifier(uint begin, uint end) { }

        /// <summary>
        /// Edge visitor for Type edge which is called when the subtree of this edge is started.
        /// </summary>
        /// <param name="begin">[in] The id of the node the edge starts from.</param>
        /// <param name="end">[in] The id of the node the edge points to.</param>
        public virtual void visitBasePropertyDeclarationSyntax_Type(uint begin, uint end) { }

        /// <summary>
        /// Edge end visitor for Type edge which is called after the subtree of this edge is finished.
        /// </summary>
        /// <param name="begin">[in] The id of the node the edge starts from.</param>
        /// <param name="end">[in] The id of the node the edge points to.</param>
        public virtual void visitEndBasePropertyDeclarationSyntax_Type(uint begin, uint end) { }

        /// <summary>
        /// Edge visitor for AttributeLists edge which is called when the subtree of this edge is started.
        /// </summary>
        /// <param name="begin">[in] The id of the node the edge starts from.</param>
        /// <param name="end">[in] The id of the node the edge points to.</param>
        public virtual void visitBaseTypeDeclarationSyntax_AttributeLists(uint begin, uint end) { }

        /// <summary>
        /// Edge end visitor for AttributeLists edge which is called after the subtree of this edge is finished.
        /// </summary>
        /// <param name="begin">[in] The id of the node the edge starts from.</param>
        /// <param name="end">[in] The id of the node the edge points to.</param>
        public virtual void visitEndBaseTypeDeclarationSyntax_AttributeLists(uint begin, uint end) { }

        /// <summary>
        /// Edge visitor for BaseList edge which is called when the subtree of this edge is started.
        /// </summary>
        /// <param name="begin">[in] The id of the node the edge starts from.</param>
        /// <param name="end">[in] The id of the node the edge points to.</param>
        public virtual void visitBaseTypeDeclarationSyntax_BaseList(uint begin, uint end) { }

        /// <summary>
        /// Edge end visitor for BaseList edge which is called after the subtree of this edge is finished.
        /// </summary>
        /// <param name="begin">[in] The id of the node the edge starts from.</param>
        /// <param name="end">[in] The id of the node the edge points to.</param>
        public virtual void visitEndBaseTypeDeclarationSyntax_BaseList(uint begin, uint end) { }

        /// <summary>
        /// Edge visitor for Type edge which is called when the subtree of this edge is started.
        /// </summary>
        /// <param name="begin">[in] The id of the node the edge starts from.</param>
        /// <param name="end">[in] The id of the node the edge points to.</param>
        public virtual void visitBaseTypeSyntax_Type(uint begin, uint end) { }

        /// <summary>
        /// Edge end visitor for Type edge which is called after the subtree of this edge is finished.
        /// </summary>
        /// <param name="begin">[in] The id of the node the edge starts from.</param>
        /// <param name="end">[in] The id of the node the edge points to.</param>
        public virtual void visitEndBaseTypeSyntax_Type(uint begin, uint end) { }

        /// <summary>
        /// Edge visitor for Value edge which is called when the subtree of this edge is started.
        /// </summary>
        /// <param name="begin">[in] The id of the node the edge starts from.</param>
        /// <param name="end">[in] The id of the node the edge points to.</param>
        public virtual void visitCaseSwitchLabelSyntax_Value(uint begin, uint end) { }

        /// <summary>
        /// Edge end visitor for Value edge which is called after the subtree of this edge is finished.
        /// </summary>
        /// <param name="begin">[in] The id of the node the edge starts from.</param>
        /// <param name="end">[in] The id of the node the edge points to.</param>
        public virtual void visitEndCaseSwitchLabelSyntax_Value(uint begin, uint end) { }

        /// <summary>
        /// Edge visitor for Block edge which is called when the subtree of this edge is started.
        /// </summary>
        /// <param name="begin">[in] The id of the node the edge starts from.</param>
        /// <param name="end">[in] The id of the node the edge points to.</param>
        public virtual void visitCatchClauseSyntax_Block(uint begin, uint end) { }

        /// <summary>
        /// Edge end visitor for Block edge which is called after the subtree of this edge is finished.
        /// </summary>
        /// <param name="begin">[in] The id of the node the edge starts from.</param>
        /// <param name="end">[in] The id of the node the edge points to.</param>
        public virtual void visitEndCatchClauseSyntax_Block(uint begin, uint end) { }

        /// <summary>
        /// Edge visitor for Declaration edge which is called when the subtree of this edge is started.
        /// </summary>
        /// <param name="begin">[in] The id of the node the edge starts from.</param>
        /// <param name="end">[in] The id of the node the edge points to.</param>
        public virtual void visitCatchClauseSyntax_Declaration(uint begin, uint end) { }

        /// <summary>
        /// Edge end visitor for Declaration edge which is called after the subtree of this edge is finished.
        /// </summary>
        /// <param name="begin">[in] The id of the node the edge starts from.</param>
        /// <param name="end">[in] The id of the node the edge points to.</param>
        public virtual void visitEndCatchClauseSyntax_Declaration(uint begin, uint end) { }

        /// <summary>
        /// Edge visitor for Filter edge which is called when the subtree of this edge is started.
        /// </summary>
        /// <param name="begin">[in] The id of the node the edge starts from.</param>
        /// <param name="end">[in] The id of the node the edge points to.</param>
        public virtual void visitCatchClauseSyntax_Filter(uint begin, uint end) { }

        /// <summary>
        /// Edge end visitor for Filter edge which is called after the subtree of this edge is finished.
        /// </summary>
        /// <param name="begin">[in] The id of the node the edge starts from.</param>
        /// <param name="end">[in] The id of the node the edge points to.</param>
        public virtual void visitEndCatchClauseSyntax_Filter(uint begin, uint end) { }

        /// <summary>
        /// Edge visitor for Type edge which is called when the subtree of this edge is started.
        /// </summary>
        /// <param name="begin">[in] The id of the node the edge starts from.</param>
        /// <param name="end">[in] The id of the node the edge points to.</param>
        public virtual void visitCatchDeclarationSyntax_Type(uint begin, uint end) { }

        /// <summary>
        /// Edge end visitor for Type edge which is called after the subtree of this edge is finished.
        /// </summary>
        /// <param name="begin">[in] The id of the node the edge starts from.</param>
        /// <param name="end">[in] The id of the node the edge points to.</param>
        public virtual void visitEndCatchDeclarationSyntax_Type(uint begin, uint end) { }

        /// <summary>
        /// Edge visitor for FilterExpression edge which is called when the subtree of this edge is started.
        /// </summary>
        /// <param name="begin">[in] The id of the node the edge starts from.</param>
        /// <param name="end">[in] The id of the node the edge points to.</param>
        public virtual void visitCatchFilterClauseSyntax_FilterExpression(uint begin, uint end) { }

        /// <summary>
        /// Edge end visitor for FilterExpression edge which is called after the subtree of this edge is finished.
        /// </summary>
        /// <param name="begin">[in] The id of the node the edge starts from.</param>
        /// <param name="end">[in] The id of the node the edge points to.</param>
        public virtual void visitEndCatchFilterClauseSyntax_FilterExpression(uint begin, uint end) { }

        /// <summary>
        /// Edge visitor for AttributeLists edge which is called when the subtree of this edge is started.
        /// </summary>
        /// <param name="begin">[in] The id of the node the edge starts from.</param>
        /// <param name="end">[in] The id of the node the edge points to.</param>
        public virtual void visitCompilationUnitSyntax_AttributeLists(uint begin, uint end) { }

        /// <summary>
        /// Edge end visitor for AttributeLists edge which is called after the subtree of this edge is finished.
        /// </summary>
        /// <param name="begin">[in] The id of the node the edge starts from.</param>
        /// <param name="end">[in] The id of the node the edge points to.</param>
        public virtual void visitEndCompilationUnitSyntax_AttributeLists(uint begin, uint end) { }

        /// <summary>
        /// Edge visitor for Externs edge which is called when the subtree of this edge is started.
        /// </summary>
        /// <param name="begin">[in] The id of the node the edge starts from.</param>
        /// <param name="end">[in] The id of the node the edge points to.</param>
        public virtual void visitCompilationUnitSyntax_Externs(uint begin, uint end) { }

        /// <summary>
        /// Edge end visitor for Externs edge which is called after the subtree of this edge is finished.
        /// </summary>
        /// <param name="begin">[in] The id of the node the edge starts from.</param>
        /// <param name="end">[in] The id of the node the edge points to.</param>
        public virtual void visitEndCompilationUnitSyntax_Externs(uint begin, uint end) { }

        /// <summary>
        /// Edge visitor for Members edge which is called when the subtree of this edge is started.
        /// </summary>
        /// <param name="begin">[in] The id of the node the edge starts from.</param>
        /// <param name="end">[in] The id of the node the edge points to.</param>
        public virtual void visitCompilationUnitSyntax_Members(uint begin, uint end) { }

        /// <summary>
        /// Edge end visitor for Members edge which is called after the subtree of this edge is finished.
        /// </summary>
        /// <param name="begin">[in] The id of the node the edge starts from.</param>
        /// <param name="end">[in] The id of the node the edge points to.</param>
        public virtual void visitEndCompilationUnitSyntax_Members(uint begin, uint end) { }

        /// <summary>
        /// Edge visitor for Usings edge which is called when the subtree of this edge is started.
        /// </summary>
        /// <param name="begin">[in] The id of the node the edge starts from.</param>
        /// <param name="end">[in] The id of the node the edge points to.</param>
        public virtual void visitCompilationUnitSyntax_Usings(uint begin, uint end) { }

        /// <summary>
        /// Edge end visitor for Usings edge which is called after the subtree of this edge is finished.
        /// </summary>
        /// <param name="begin">[in] The id of the node the edge starts from.</param>
        /// <param name="end">[in] The id of the node the edge points to.</param>
        public virtual void visitEndCompilationUnitSyntax_Usings(uint begin, uint end) { }

        /// <summary>
        /// Edge visitor for Initializer edge which is called when the subtree of this edge is started.
        /// </summary>
        /// <param name="begin">[in] The id of the node the edge starts from.</param>
        /// <param name="end">[in] The id of the node the edge points to.</param>
        public virtual void visitConstructorDeclarationSyntax_Initializer(uint begin, uint end) { }

        /// <summary>
        /// Edge end visitor for Initializer edge which is called after the subtree of this edge is finished.
        /// </summary>
        /// <param name="begin">[in] The id of the node the edge starts from.</param>
        /// <param name="end">[in] The id of the node the edge points to.</param>
        public virtual void visitEndConstructorDeclarationSyntax_Initializer(uint begin, uint end) { }

        /// <summary>
        /// Edge visitor for ArgumentList edge which is called when the subtree of this edge is started.
        /// </summary>
        /// <param name="begin">[in] The id of the node the edge starts from.</param>
        /// <param name="end">[in] The id of the node the edge points to.</param>
        public virtual void visitConstructorInitializerSyntax_ArgumentList(uint begin, uint end) { }

        /// <summary>
        /// Edge end visitor for ArgumentList edge which is called after the subtree of this edge is finished.
        /// </summary>
        /// <param name="begin">[in] The id of the node the edge starts from.</param>
        /// <param name="end">[in] The id of the node the edge points to.</param>
        public virtual void visitEndConstructorInitializerSyntax_ArgumentList(uint begin, uint end) { }

        /// <summary>
        /// Edge visitor for ConstructorCall edge which.
        /// </summary>
        /// <param name="begin">[in] The id of the node the edge starts from.</param>
        /// <param name="end">[in] The id of the node the edge points to.</param>
        public virtual void visitConstructorInitializerSyntax_ConstructorCall(uint begin, uint end) { }

        /// <summary>
        /// Edge end visitor for ConstructorCall edge which is called after the visit pair of this edge is called.
        /// </summary>
        /// <param name="begin">[in] The id of the node the edge starts from.</param>
        /// <param name="end">[in] The id of the node the edge points to.</param>
        public virtual void visitEndConstructorInitializerSyntax_ConstructorCall(uint begin, uint end) { }

        /// <summary>
        /// Edge visitor for ExpressionBody edge which is called when the subtree of this edge is started.
        /// </summary>
        /// <param name="begin">[in] The id of the node the edge starts from.</param>
        /// <param name="end">[in] The id of the node the edge points to.</param>
        public virtual void visitConversionOperatorDeclarationSyntax_ExpressionBody(uint begin, uint end) { }

        /// <summary>
        /// Edge end visitor for ExpressionBody edge which is called after the subtree of this edge is finished.
        /// </summary>
        /// <param name="begin">[in] The id of the node the edge starts from.</param>
        /// <param name="end">[in] The id of the node the edge points to.</param>
        public virtual void visitEndConversionOperatorDeclarationSyntax_ExpressionBody(uint begin, uint end) { }

        /// <summary>
        /// Edge visitor for Type edge which is called when the subtree of this edge is started.
        /// </summary>
        /// <param name="begin">[in] The id of the node the edge starts from.</param>
        /// <param name="end">[in] The id of the node the edge points to.</param>
        public virtual void visitConversionOperatorDeclarationSyntax_Type(uint begin, uint end) { }

        /// <summary>
        /// Edge end visitor for Type edge which is called after the subtree of this edge is finished.
        /// </summary>
        /// <param name="begin">[in] The id of the node the edge starts from.</param>
        /// <param name="end">[in] The id of the node the edge points to.</param>
        public virtual void visitEndConversionOperatorDeclarationSyntax_Type(uint begin, uint end) { }

        /// <summary>
        /// Edge visitor for Parameters edge which is called when the subtree of this edge is started.
        /// </summary>
        /// <param name="begin">[in] The id of the node the edge starts from.</param>
        /// <param name="end">[in] The id of the node the edge points to.</param>
        public virtual void visitConversionOperatorMemberCrefSyntax_Parameters(uint begin, uint end) { }

        /// <summary>
        /// Edge end visitor for Parameters edge which is called after the subtree of this edge is finished.
        /// </summary>
        /// <param name="begin">[in] The id of the node the edge starts from.</param>
        /// <param name="end">[in] The id of the node the edge points to.</param>
        public virtual void visitEndConversionOperatorMemberCrefSyntax_Parameters(uint begin, uint end) { }

        /// <summary>
        /// Edge visitor for Type edge which is called when the subtree of this edge is started.
        /// </summary>
        /// <param name="begin">[in] The id of the node the edge starts from.</param>
        /// <param name="end">[in] The id of the node the edge points to.</param>
        public virtual void visitConversionOperatorMemberCrefSyntax_Type(uint begin, uint end) { }

        /// <summary>
        /// Edge end visitor for Type edge which is called after the subtree of this edge is finished.
        /// </summary>
        /// <param name="begin">[in] The id of the node the edge starts from.</param>
        /// <param name="end">[in] The id of the node the edge points to.</param>
        public virtual void visitEndConversionOperatorMemberCrefSyntax_Type(uint begin, uint end) { }

        /// <summary>
        /// Edge visitor for Type edge which is called when the subtree of this edge is started.
        /// </summary>
        /// <param name="begin">[in] The id of the node the edge starts from.</param>
        /// <param name="end">[in] The id of the node the edge points to.</param>
        public virtual void visitCrefParameterSyntax_Type(uint begin, uint end) { }

        /// <summary>
        /// Edge end visitor for Type edge which is called after the subtree of this edge is finished.
        /// </summary>
        /// <param name="begin">[in] The id of the node the edge starts from.</param>
        /// <param name="end">[in] The id of the node the edge points to.</param>
        public virtual void visitEndCrefParameterSyntax_Type(uint begin, uint end) { }

        /// <summary>
        /// Edge visitor for AttributeLists edge which is called when the subtree of this edge is started.
        /// </summary>
        /// <param name="begin">[in] The id of the node the edge starts from.</param>
        /// <param name="end">[in] The id of the node the edge points to.</param>
        public virtual void visitDelegateDeclarationSyntax_AttributeLists(uint begin, uint end) { }

        /// <summary>
        /// Edge end visitor for AttributeLists edge which is called after the subtree of this edge is finished.
        /// </summary>
        /// <param name="begin">[in] The id of the node the edge starts from.</param>
        /// <param name="end">[in] The id of the node the edge points to.</param>
        public virtual void visitEndDelegateDeclarationSyntax_AttributeLists(uint begin, uint end) { }

        /// <summary>
        /// Edge visitor for ConstraintClauses edge which is called when the subtree of this edge is started.
        /// </summary>
        /// <param name="begin">[in] The id of the node the edge starts from.</param>
        /// <param name="end">[in] The id of the node the edge points to.</param>
        public virtual void visitDelegateDeclarationSyntax_ConstraintClauses(uint begin, uint end) { }

        /// <summary>
        /// Edge end visitor for ConstraintClauses edge which is called after the subtree of this edge is finished.
        /// </summary>
        /// <param name="begin">[in] The id of the node the edge starts from.</param>
        /// <param name="end">[in] The id of the node the edge points to.</param>
        public virtual void visitEndDelegateDeclarationSyntax_ConstraintClauses(uint begin, uint end) { }

        /// <summary>
        /// Edge visitor for ParameterList edge which is called when the subtree of this edge is started.
        /// </summary>
        /// <param name="begin">[in] The id of the node the edge starts from.</param>
        /// <param name="end">[in] The id of the node the edge points to.</param>
        public virtual void visitDelegateDeclarationSyntax_ParameterList(uint begin, uint end) { }

        /// <summary>
        /// Edge end visitor for ParameterList edge which is called after the subtree of this edge is finished.
        /// </summary>
        /// <param name="begin">[in] The id of the node the edge starts from.</param>
        /// <param name="end">[in] The id of the node the edge points to.</param>
        public virtual void visitEndDelegateDeclarationSyntax_ParameterList(uint begin, uint end) { }

        /// <summary>
        /// Edge visitor for ReturnType edge which is called when the subtree of this edge is started.
        /// </summary>
        /// <param name="begin">[in] The id of the node the edge starts from.</param>
        /// <param name="end">[in] The id of the node the edge points to.</param>
        public virtual void visitDelegateDeclarationSyntax_ReturnType(uint begin, uint end) { }

        /// <summary>
        /// Edge end visitor for ReturnType edge which is called after the subtree of this edge is finished.
        /// </summary>
        /// <param name="begin">[in] The id of the node the edge starts from.</param>
        /// <param name="end">[in] The id of the node the edge points to.</param>
        public virtual void visitEndDelegateDeclarationSyntax_ReturnType(uint begin, uint end) { }

        /// <summary>
        /// Edge visitor for Statement edge which is called when the subtree of this edge is started.
        /// </summary>
        /// <param name="begin">[in] The id of the node the edge starts from.</param>
        /// <param name="end">[in] The id of the node the edge points to.</param>
        public virtual void visitElseClauseSyntax_Statement(uint begin, uint end) { }

        /// <summary>
        /// Edge end visitor for Statement edge which is called after the subtree of this edge is finished.
        /// </summary>
        /// <param name="begin">[in] The id of the node the edge starts from.</param>
        /// <param name="end">[in] The id of the node the edge points to.</param>
        public virtual void visitEndElseClauseSyntax_Statement(uint begin, uint end) { }

        /// <summary>
        /// Edge visitor for Members edge which is called when the subtree of this edge is started.
        /// </summary>
        /// <param name="begin">[in] The id of the node the edge starts from.</param>
        /// <param name="end">[in] The id of the node the edge points to.</param>
        public virtual void visitEnumDeclarationSyntax_Members(uint begin, uint end) { }

        /// <summary>
        /// Edge end visitor for Members edge which is called after the subtree of this edge is finished.
        /// </summary>
        /// <param name="begin">[in] The id of the node the edge starts from.</param>
        /// <param name="end">[in] The id of the node the edge points to.</param>
        public virtual void visitEndEnumDeclarationSyntax_Members(uint begin, uint end) { }

        /// <summary>
        /// Edge visitor for AttributeLists edge which is called when the subtree of this edge is started.
        /// </summary>
        /// <param name="begin">[in] The id of the node the edge starts from.</param>
        /// <param name="end">[in] The id of the node the edge points to.</param>
        public virtual void visitEnumMemberDeclarationSyntax_AttributeLists(uint begin, uint end) { }

        /// <summary>
        /// Edge end visitor for AttributeLists edge which is called after the subtree of this edge is finished.
        /// </summary>
        /// <param name="begin">[in] The id of the node the edge starts from.</param>
        /// <param name="end">[in] The id of the node the edge points to.</param>
        public virtual void visitEndEnumMemberDeclarationSyntax_AttributeLists(uint begin, uint end) { }

        /// <summary>
        /// Edge visitor for EqualsValue edge which is called when the subtree of this edge is started.
        /// </summary>
        /// <param name="begin">[in] The id of the node the edge starts from.</param>
        /// <param name="end">[in] The id of the node the edge points to.</param>
        public virtual void visitEnumMemberDeclarationSyntax_EqualsValue(uint begin, uint end) { }

        /// <summary>
        /// Edge end visitor for EqualsValue edge which is called after the subtree of this edge is finished.
        /// </summary>
        /// <param name="begin">[in] The id of the node the edge starts from.</param>
        /// <param name="end">[in] The id of the node the edge points to.</param>
        public virtual void visitEndEnumMemberDeclarationSyntax_EqualsValue(uint begin, uint end) { }

        /// <summary>
        /// Edge visitor for Value edge which is called when the subtree of this edge is started.
        /// </summary>
        /// <param name="begin">[in] The id of the node the edge starts from.</param>
        /// <param name="end">[in] The id of the node the edge points to.</param>
        public virtual void visitEqualsValueClauseSyntax_Value(uint begin, uint end) { }

        /// <summary>
        /// Edge end visitor for Value edge which is called after the subtree of this edge is finished.
        /// </summary>
        /// <param name="begin">[in] The id of the node the edge starts from.</param>
        /// <param name="end">[in] The id of the node the edge points to.</param>
        public virtual void visitEndEqualsValueClauseSyntax_Value(uint begin, uint end) { }

        /// <summary>
        /// Edge visitor for Name edge which is called when the subtree of this edge is started.
        /// </summary>
        /// <param name="begin">[in] The id of the node the edge starts from.</param>
        /// <param name="end">[in] The id of the node the edge points to.</param>
        public virtual void visitExplicitInterfaceSpecifierSyntax_Name(uint begin, uint end) { }

        /// <summary>
        /// Edge end visitor for Name edge which is called after the subtree of this edge is finished.
        /// </summary>
        /// <param name="begin">[in] The id of the node the edge starts from.</param>
        /// <param name="end">[in] The id of the node the edge points to.</param>
        public virtual void visitEndExplicitInterfaceSpecifierSyntax_Name(uint begin, uint end) { }

        /// <summary>
        /// Edge visitor for Block edge which is called when the subtree of this edge is started.
        /// </summary>
        /// <param name="begin">[in] The id of the node the edge starts from.</param>
        /// <param name="end">[in] The id of the node the edge points to.</param>
        public virtual void visitFinallyClauseSyntax_Block(uint begin, uint end) { }

        /// <summary>
        /// Edge end visitor for Block edge which is called after the subtree of this edge is finished.
        /// </summary>
        /// <param name="begin">[in] The id of the node the edge starts from.</param>
        /// <param name="end">[in] The id of the node the edge points to.</param>
        public virtual void visitEndFinallyClauseSyntax_Block(uint begin, uint end) { }

        /// <summary>
        /// Edge visitor for Expression edge which is called when the subtree of this edge is started.
        /// </summary>
        /// <param name="begin">[in] The id of the node the edge starts from.</param>
        /// <param name="end">[in] The id of the node the edge points to.</param>
        public virtual void visitFromClauseSyntax_Expression(uint begin, uint end) { }

        /// <summary>
        /// Edge end visitor for Expression edge which is called after the subtree of this edge is finished.
        /// </summary>
        /// <param name="begin">[in] The id of the node the edge starts from.</param>
        /// <param name="end">[in] The id of the node the edge points to.</param>
        public virtual void visitEndFromClauseSyntax_Expression(uint begin, uint end) { }

        /// <summary>
        /// Edge visitor for Type edge which is called when the subtree of this edge is started.
        /// </summary>
        /// <param name="begin">[in] The id of the node the edge starts from.</param>
        /// <param name="end">[in] The id of the node the edge points to.</param>
        public virtual void visitFromClauseSyntax_Type(uint begin, uint end) { }

        /// <summary>
        /// Edge end visitor for Type edge which is called after the subtree of this edge is finished.
        /// </summary>
        /// <param name="begin">[in] The id of the node the edge starts from.</param>
        /// <param name="end">[in] The id of the node the edge points to.</param>
        public virtual void visitEndFromClauseSyntax_Type(uint begin, uint end) { }

        /// <summary>
        /// Edge visitor for Statement edge which is called when the subtree of this edge is started.
        /// </summary>
        /// <param name="begin">[in] The id of the node the edge starts from.</param>
        /// <param name="end">[in] The id of the node the edge points to.</param>
        public virtual void visitGlobalStatementSyntax_Statement(uint begin, uint end) { }

        /// <summary>
        /// Edge end visitor for Statement edge which is called after the subtree of this edge is finished.
        /// </summary>
        /// <param name="begin">[in] The id of the node the edge starts from.</param>
        /// <param name="end">[in] The id of the node the edge points to.</param>
        public virtual void visitEndGlobalStatementSyntax_Statement(uint begin, uint end) { }

        /// <summary>
        /// Edge visitor for ByExpression edge which is called when the subtree of this edge is started.
        /// </summary>
        /// <param name="begin">[in] The id of the node the edge starts from.</param>
        /// <param name="end">[in] The id of the node the edge points to.</param>
        public virtual void visitGroupClauseSyntax_ByExpression(uint begin, uint end) { }

        /// <summary>
        /// Edge end visitor for ByExpression edge which is called after the subtree of this edge is finished.
        /// </summary>
        /// <param name="begin">[in] The id of the node the edge starts from.</param>
        /// <param name="end">[in] The id of the node the edge points to.</param>
        public virtual void visitEndGroupClauseSyntax_ByExpression(uint begin, uint end) { }

        /// <summary>
        /// Edge visitor for GroupExpression edge which is called when the subtree of this edge is started.
        /// </summary>
        /// <param name="begin">[in] The id of the node the edge starts from.</param>
        /// <param name="end">[in] The id of the node the edge points to.</param>
        public virtual void visitGroupClauseSyntax_GroupExpression(uint begin, uint end) { }

        /// <summary>
        /// Edge end visitor for GroupExpression edge which is called after the subtree of this edge is finished.
        /// </summary>
        /// <param name="begin">[in] The id of the node the edge starts from.</param>
        /// <param name="end">[in] The id of the node the edge points to.</param>
        public virtual void visitEndGroupClauseSyntax_GroupExpression(uint begin, uint end) { }

        /// <summary>
        /// Edge visitor for AttributeLists edge which is called when the subtree of this edge is started.
        /// </summary>
        /// <param name="begin">[in] The id of the node the edge starts from.</param>
        /// <param name="end">[in] The id of the node the edge points to.</param>
        public virtual void visitIncompleteMemberSyntax_AttributeLists(uint begin, uint end) { }

        /// <summary>
        /// Edge end visitor for AttributeLists edge which is called after the subtree of this edge is finished.
        /// </summary>
        /// <param name="begin">[in] The id of the node the edge starts from.</param>
        /// <param name="end">[in] The id of the node the edge points to.</param>
        public virtual void visitEndIncompleteMemberSyntax_AttributeLists(uint begin, uint end) { }

        /// <summary>
        /// Edge visitor for Type edge which is called when the subtree of this edge is started.
        /// </summary>
        /// <param name="begin">[in] The id of the node the edge starts from.</param>
        /// <param name="end">[in] The id of the node the edge points to.</param>
        public virtual void visitIncompleteMemberSyntax_Type(uint begin, uint end) { }

        /// <summary>
        /// Edge end visitor for Type edge which is called after the subtree of this edge is finished.
        /// </summary>
        /// <param name="begin">[in] The id of the node the edge starts from.</param>
        /// <param name="end">[in] The id of the node the edge points to.</param>
        public virtual void visitEndIncompleteMemberSyntax_Type(uint begin, uint end) { }

        /// <summary>
        /// Edge visitor for ExpressionBody edge which is called when the subtree of this edge is started.
        /// </summary>
        /// <param name="begin">[in] The id of the node the edge starts from.</param>
        /// <param name="end">[in] The id of the node the edge points to.</param>
        public virtual void visitIndexerDeclarationSyntax_ExpressionBody(uint begin, uint end) { }

        /// <summary>
        /// Edge end visitor for ExpressionBody edge which is called after the subtree of this edge is finished.
        /// </summary>
        /// <param name="begin">[in] The id of the node the edge starts from.</param>
        /// <param name="end">[in] The id of the node the edge points to.</param>
        public virtual void visitEndIndexerDeclarationSyntax_ExpressionBody(uint begin, uint end) { }

        /// <summary>
        /// Edge visitor for ParameterList edge which is called when the subtree of this edge is started.
        /// </summary>
        /// <param name="begin">[in] The id of the node the edge starts from.</param>
        /// <param name="end">[in] The id of the node the edge points to.</param>
        public virtual void visitIndexerDeclarationSyntax_ParameterList(uint begin, uint end) { }

        /// <summary>
        /// Edge end visitor for ParameterList edge which is called after the subtree of this edge is finished.
        /// </summary>
        /// <param name="begin">[in] The id of the node the edge starts from.</param>
        /// <param name="end">[in] The id of the node the edge points to.</param>
        public virtual void visitEndIndexerDeclarationSyntax_ParameterList(uint begin, uint end) { }

        /// <summary>
        /// Edge visitor for Parameters edge which is called when the subtree of this edge is started.
        /// </summary>
        /// <param name="begin">[in] The id of the node the edge starts from.</param>
        /// <param name="end">[in] The id of the node the edge points to.</param>
        public virtual void visitIndexerMemberCrefSyntax_Parameters(uint begin, uint end) { }

        /// <summary>
        /// Edge end visitor for Parameters edge which is called after the subtree of this edge is finished.
        /// </summary>
        /// <param name="begin">[in] The id of the node the edge starts from.</param>
        /// <param name="end">[in] The id of the node the edge points to.</param>
        public virtual void visitEndIndexerMemberCrefSyntax_Parameters(uint begin, uint end) { }

        /// <summary>
        /// Edge visitor for Value edge which is called when the subtree of this edge is started.
        /// </summary>
        /// <param name="begin">[in] The id of the node the edge starts from.</param>
        /// <param name="end">[in] The id of the node the edge points to.</param>
        public virtual void visitInterpolationAlignmentClauseSyntax_Value(uint begin, uint end) { }

        /// <summary>
        /// Edge end visitor for Value edge which is called after the subtree of this edge is finished.
        /// </summary>
        /// <param name="begin">[in] The id of the node the edge starts from.</param>
        /// <param name="end">[in] The id of the node the edge points to.</param>
        public virtual void visitEndInterpolationAlignmentClauseSyntax_Value(uint begin, uint end) { }

        /// <summary>
        /// Edge visitor for AlignmentClause edge which is called when the subtree of this edge is started.
        /// </summary>
        /// <param name="begin">[in] The id of the node the edge starts from.</param>
        /// <param name="end">[in] The id of the node the edge points to.</param>
        public virtual void visitInterpolationSyntax_AlignmentClause(uint begin, uint end) { }

        /// <summary>
        /// Edge end visitor for AlignmentClause edge which is called after the subtree of this edge is finished.
        /// </summary>
        /// <param name="begin">[in] The id of the node the edge starts from.</param>
        /// <param name="end">[in] The id of the node the edge points to.</param>
        public virtual void visitEndInterpolationSyntax_AlignmentClause(uint begin, uint end) { }

        /// <summary>
        /// Edge visitor for Expression edge which is called when the subtree of this edge is started.
        /// </summary>
        /// <param name="begin">[in] The id of the node the edge starts from.</param>
        /// <param name="end">[in] The id of the node the edge points to.</param>
        public virtual void visitInterpolationSyntax_Expression(uint begin, uint end) { }

        /// <summary>
        /// Edge end visitor for Expression edge which is called after the subtree of this edge is finished.
        /// </summary>
        /// <param name="begin">[in] The id of the node the edge starts from.</param>
        /// <param name="end">[in] The id of the node the edge points to.</param>
        public virtual void visitEndInterpolationSyntax_Expression(uint begin, uint end) { }

        /// <summary>
        /// Edge visitor for FormatClause edge which is called when the subtree of this edge is started.
        /// </summary>
        /// <param name="begin">[in] The id of the node the edge starts from.</param>
        /// <param name="end">[in] The id of the node the edge points to.</param>
        public virtual void visitInterpolationSyntax_FormatClause(uint begin, uint end) { }

        /// <summary>
        /// Edge end visitor for FormatClause edge which is called after the subtree of this edge is finished.
        /// </summary>
        /// <param name="begin">[in] The id of the node the edge starts from.</param>
        /// <param name="end">[in] The id of the node the edge points to.</param>
        public virtual void visitEndInterpolationSyntax_FormatClause(uint begin, uint end) { }

        /// <summary>
        /// Edge visitor for InExpression edge which is called when the subtree of this edge is started.
        /// </summary>
        /// <param name="begin">[in] The id of the node the edge starts from.</param>
        /// <param name="end">[in] The id of the node the edge points to.</param>
        public virtual void visitJoinClauseSyntax_InExpression(uint begin, uint end) { }

        /// <summary>
        /// Edge end visitor for InExpression edge which is called after the subtree of this edge is finished.
        /// </summary>
        /// <param name="begin">[in] The id of the node the edge starts from.</param>
        /// <param name="end">[in] The id of the node the edge points to.</param>
        public virtual void visitEndJoinClauseSyntax_InExpression(uint begin, uint end) { }

        /// <summary>
        /// Edge visitor for Into edge which is called when the subtree of this edge is started.
        /// </summary>
        /// <param name="begin">[in] The id of the node the edge starts from.</param>
        /// <param name="end">[in] The id of the node the edge points to.</param>
        public virtual void visitJoinClauseSyntax_Into(uint begin, uint end) { }

        /// <summary>
        /// Edge end visitor for Into edge which is called after the subtree of this edge is finished.
        /// </summary>
        /// <param name="begin">[in] The id of the node the edge starts from.</param>
        /// <param name="end">[in] The id of the node the edge points to.</param>
        public virtual void visitEndJoinClauseSyntax_Into(uint begin, uint end) { }

        /// <summary>
        /// Edge visitor for LeftExpression edge which is called when the subtree of this edge is started.
        /// </summary>
        /// <param name="begin">[in] The id of the node the edge starts from.</param>
        /// <param name="end">[in] The id of the node the edge points to.</param>
        public virtual void visitJoinClauseSyntax_LeftExpression(uint begin, uint end) { }

        /// <summary>
        /// Edge end visitor for LeftExpression edge which is called after the subtree of this edge is finished.
        /// </summary>
        /// <param name="begin">[in] The id of the node the edge starts from.</param>
        /// <param name="end">[in] The id of the node the edge points to.</param>
        public virtual void visitEndJoinClauseSyntax_LeftExpression(uint begin, uint end) { }

        /// <summary>
        /// Edge visitor for RightExpression edge which is called when the subtree of this edge is started.
        /// </summary>
        /// <param name="begin">[in] The id of the node the edge starts from.</param>
        /// <param name="end">[in] The id of the node the edge points to.</param>
        public virtual void visitJoinClauseSyntax_RightExpression(uint begin, uint end) { }

        /// <summary>
        /// Edge end visitor for RightExpression edge which is called after the subtree of this edge is finished.
        /// </summary>
        /// <param name="begin">[in] The id of the node the edge starts from.</param>
        /// <param name="end">[in] The id of the node the edge points to.</param>
        public virtual void visitEndJoinClauseSyntax_RightExpression(uint begin, uint end) { }

        /// <summary>
        /// Edge visitor for Type edge which is called when the subtree of this edge is started.
        /// </summary>
        /// <param name="begin">[in] The id of the node the edge starts from.</param>
        /// <param name="end">[in] The id of the node the edge points to.</param>
        public virtual void visitJoinClauseSyntax_Type(uint begin, uint end) { }

        /// <summary>
        /// Edge end visitor for Type edge which is called after the subtree of this edge is finished.
        /// </summary>
        /// <param name="begin">[in] The id of the node the edge starts from.</param>
        /// <param name="end">[in] The id of the node the edge points to.</param>
        public virtual void visitEndJoinClauseSyntax_Type(uint begin, uint end) { }

        /// <summary>
        /// Edge visitor for Expression edge which is called when the subtree of this edge is started.
        /// </summary>
        /// <param name="begin">[in] The id of the node the edge starts from.</param>
        /// <param name="end">[in] The id of the node the edge points to.</param>
        public virtual void visitLetClauseSyntax_Expression(uint begin, uint end) { }

        /// <summary>
        /// Edge end visitor for Expression edge which is called after the subtree of this edge is finished.
        /// </summary>
        /// <param name="begin">[in] The id of the node the edge starts from.</param>
        /// <param name="end">[in] The id of the node the edge points to.</param>
        public virtual void visitEndLetClauseSyntax_Expression(uint begin, uint end) { }

        /// <summary>
        /// Edge visitor for ConstraintClauses edge which is called when the subtree of this edge is started.
        /// </summary>
        /// <param name="begin">[in] The id of the node the edge starts from.</param>
        /// <param name="end">[in] The id of the node the edge points to.</param>
        public virtual void visitMethodDeclarationSyntax_ConstraintClauses(uint begin, uint end) { }

        /// <summary>
        /// Edge end visitor for ConstraintClauses edge which is called after the subtree of this edge is finished.
        /// </summary>
        /// <param name="begin">[in] The id of the node the edge starts from.</param>
        /// <param name="end">[in] The id of the node the edge points to.</param>
        public virtual void visitEndMethodDeclarationSyntax_ConstraintClauses(uint begin, uint end) { }

        /// <summary>
        /// Edge visitor for ExplicitInterfaceSpecifier edge which is called when the subtree of this edge is started.
        /// </summary>
        /// <param name="begin">[in] The id of the node the edge starts from.</param>
        /// <param name="end">[in] The id of the node the edge points to.</param>
        public virtual void visitMethodDeclarationSyntax_ExplicitInterfaceSpecifier(uint begin, uint end) { }

        /// <summary>
        /// Edge end visitor for ExplicitInterfaceSpecifier edge which is called after the subtree of this edge is finished.
        /// </summary>
        /// <param name="begin">[in] The id of the node the edge starts from.</param>
        /// <param name="end">[in] The id of the node the edge points to.</param>
        public virtual void visitEndMethodDeclarationSyntax_ExplicitInterfaceSpecifier(uint begin, uint end) { }

        /// <summary>
        /// Edge visitor for ExpressionBody edge which is called when the subtree of this edge is started.
        /// </summary>
        /// <param name="begin">[in] The id of the node the edge starts from.</param>
        /// <param name="end">[in] The id of the node the edge points to.</param>
        public virtual void visitMethodDeclarationSyntax_ExpressionBody(uint begin, uint end) { }

        /// <summary>
        /// Edge end visitor for ExpressionBody edge which is called after the subtree of this edge is finished.
        /// </summary>
        /// <param name="begin">[in] The id of the node the edge starts from.</param>
        /// <param name="end">[in] The id of the node the edge points to.</param>
        public virtual void visitEndMethodDeclarationSyntax_ExpressionBody(uint begin, uint end) { }

        /// <summary>
        /// Edge visitor for ReturnType edge which is called when the subtree of this edge is started.
        /// </summary>
        /// <param name="begin">[in] The id of the node the edge starts from.</param>
        /// <param name="end">[in] The id of the node the edge points to.</param>
        public virtual void visitMethodDeclarationSyntax_ReturnType(uint begin, uint end) { }

        /// <summary>
        /// Edge end visitor for ReturnType edge which is called after the subtree of this edge is finished.
        /// </summary>
        /// <param name="begin">[in] The id of the node the edge starts from.</param>
        /// <param name="end">[in] The id of the node the edge points to.</param>
        public virtual void visitEndMethodDeclarationSyntax_ReturnType(uint begin, uint end) { }

        /// <summary>
        /// Edge visitor for Name edge which is called when the subtree of this edge is started.
        /// </summary>
        /// <param name="begin">[in] The id of the node the edge starts from.</param>
        /// <param name="end">[in] The id of the node the edge points to.</param>
        public virtual void visitNameColonSyntax_Name(uint begin, uint end) { }

        /// <summary>
        /// Edge end visitor for Name edge which is called after the subtree of this edge is finished.
        /// </summary>
        /// <param name="begin">[in] The id of the node the edge starts from.</param>
        /// <param name="end">[in] The id of the node the edge points to.</param>
        public virtual void visitEndNameColonSyntax_Name(uint begin, uint end) { }

        /// <summary>
        /// Edge visitor for Name edge which is called when the subtree of this edge is started.
        /// </summary>
        /// <param name="begin">[in] The id of the node the edge starts from.</param>
        /// <param name="end">[in] The id of the node the edge points to.</param>
        public virtual void visitNameEqualsSyntax_Name(uint begin, uint end) { }

        /// <summary>
        /// Edge end visitor for Name edge which is called after the subtree of this edge is finished.
        /// </summary>
        /// <param name="begin">[in] The id of the node the edge starts from.</param>
        /// <param name="end">[in] The id of the node the edge points to.</param>
        public virtual void visitEndNameEqualsSyntax_Name(uint begin, uint end) { }

        /// <summary>
        /// Edge visitor for Name edge which is called when the subtree of this edge is started.
        /// </summary>
        /// <param name="begin">[in] The id of the node the edge starts from.</param>
        /// <param name="end">[in] The id of the node the edge points to.</param>
        public virtual void visitNameMemberCrefSyntax_Name(uint begin, uint end) { }

        /// <summary>
        /// Edge end visitor for Name edge which is called after the subtree of this edge is finished.
        /// </summary>
        /// <param name="begin">[in] The id of the node the edge starts from.</param>
        /// <param name="end">[in] The id of the node the edge points to.</param>
        public virtual void visitEndNameMemberCrefSyntax_Name(uint begin, uint end) { }

        /// <summary>
        /// Edge visitor for Parameters edge which is called when the subtree of this edge is started.
        /// </summary>
        /// <param name="begin">[in] The id of the node the edge starts from.</param>
        /// <param name="end">[in] The id of the node the edge points to.</param>
        public virtual void visitNameMemberCrefSyntax_Parameters(uint begin, uint end) { }

        /// <summary>
        /// Edge end visitor for Parameters edge which is called after the subtree of this edge is finished.
        /// </summary>
        /// <param name="begin">[in] The id of the node the edge starts from.</param>
        /// <param name="end">[in] The id of the node the edge points to.</param>
        public virtual void visitEndNameMemberCrefSyntax_Parameters(uint begin, uint end) { }

        /// <summary>
        /// Edge visitor for Externs edge which is called when the subtree of this edge is started.
        /// </summary>
        /// <param name="begin">[in] The id of the node the edge starts from.</param>
        /// <param name="end">[in] The id of the node the edge points to.</param>
        public virtual void visitNamespaceDeclarationSyntax_Externs(uint begin, uint end) { }

        /// <summary>
        /// Edge end visitor for Externs edge which is called after the subtree of this edge is finished.
        /// </summary>
        /// <param name="begin">[in] The id of the node the edge starts from.</param>
        /// <param name="end">[in] The id of the node the edge points to.</param>
        public virtual void visitEndNamespaceDeclarationSyntax_Externs(uint begin, uint end) { }

        /// <summary>
        /// Edge visitor for Members edge which is called when the subtree of this edge is started.
        /// </summary>
        /// <param name="begin">[in] The id of the node the edge starts from.</param>
        /// <param name="end">[in] The id of the node the edge points to.</param>
        public virtual void visitNamespaceDeclarationSyntax_Members(uint begin, uint end) { }

        /// <summary>
        /// Edge end visitor for Members edge which is called after the subtree of this edge is finished.
        /// </summary>
        /// <param name="begin">[in] The id of the node the edge starts from.</param>
        /// <param name="end">[in] The id of the node the edge points to.</param>
        public virtual void visitEndNamespaceDeclarationSyntax_Members(uint begin, uint end) { }

        /// <summary>
        /// Edge visitor for Name edge which is called when the subtree of this edge is started.
        /// </summary>
        /// <param name="begin">[in] The id of the node the edge starts from.</param>
        /// <param name="end">[in] The id of the node the edge points to.</param>
        public virtual void visitNamespaceDeclarationSyntax_Name(uint begin, uint end) { }

        /// <summary>
        /// Edge end visitor for Name edge which is called after the subtree of this edge is finished.
        /// </summary>
        /// <param name="begin">[in] The id of the node the edge starts from.</param>
        /// <param name="end">[in] The id of the node the edge points to.</param>
        public virtual void visitEndNamespaceDeclarationSyntax_Name(uint begin, uint end) { }

        /// <summary>
        /// Edge visitor for Usings edge which is called when the subtree of this edge is started.
        /// </summary>
        /// <param name="begin">[in] The id of the node the edge starts from.</param>
        /// <param name="end">[in] The id of the node the edge points to.</param>
        public virtual void visitNamespaceDeclarationSyntax_Usings(uint begin, uint end) { }

        /// <summary>
        /// Edge end visitor for Usings edge which is called after the subtree of this edge is finished.
        /// </summary>
        /// <param name="begin">[in] The id of the node the edge starts from.</param>
        /// <param name="end">[in] The id of the node the edge points to.</param>
        public virtual void visitEndNamespaceDeclarationSyntax_Usings(uint begin, uint end) { }

        /// <summary>
        /// Edge visitor for ExpressionBody edge which is called when the subtree of this edge is started.
        /// </summary>
        /// <param name="begin">[in] The id of the node the edge starts from.</param>
        /// <param name="end">[in] The id of the node the edge points to.</param>
        public virtual void visitOperatorDeclarationSyntax_ExpressionBody(uint begin, uint end) { }

        /// <summary>
        /// Edge end visitor for ExpressionBody edge which is called after the subtree of this edge is finished.
        /// </summary>
        /// <param name="begin">[in] The id of the node the edge starts from.</param>
        /// <param name="end">[in] The id of the node the edge points to.</param>
        public virtual void visitEndOperatorDeclarationSyntax_ExpressionBody(uint begin, uint end) { }

        /// <summary>
        /// Edge visitor for ReturnType edge which is called when the subtree of this edge is started.
        /// </summary>
        /// <param name="begin">[in] The id of the node the edge starts from.</param>
        /// <param name="end">[in] The id of the node the edge points to.</param>
        public virtual void visitOperatorDeclarationSyntax_ReturnType(uint begin, uint end) { }

        /// <summary>
        /// Edge end visitor for ReturnType edge which is called after the subtree of this edge is finished.
        /// </summary>
        /// <param name="begin">[in] The id of the node the edge starts from.</param>
        /// <param name="end">[in] The id of the node the edge points to.</param>
        public virtual void visitEndOperatorDeclarationSyntax_ReturnType(uint begin, uint end) { }

        /// <summary>
        /// Edge visitor for Parameters edge which is called when the subtree of this edge is started.
        /// </summary>
        /// <param name="begin">[in] The id of the node the edge starts from.</param>
        /// <param name="end">[in] The id of the node the edge points to.</param>
        public virtual void visitOperatorMemberCrefSyntax_Parameters(uint begin, uint end) { }

        /// <summary>
        /// Edge end visitor for Parameters edge which is called after the subtree of this edge is finished.
        /// </summary>
        /// <param name="begin">[in] The id of the node the edge starts from.</param>
        /// <param name="end">[in] The id of the node the edge points to.</param>
        public virtual void visitEndOperatorMemberCrefSyntax_Parameters(uint begin, uint end) { }

        /// <summary>
        /// Edge visitor for Orderings edge which is called when the subtree of this edge is started.
        /// </summary>
        /// <param name="begin">[in] The id of the node the edge starts from.</param>
        /// <param name="end">[in] The id of the node the edge points to.</param>
        public virtual void visitOrderByClauseSyntax_Orderings(uint begin, uint end) { }

        /// <summary>
        /// Edge end visitor for Orderings edge which is called after the subtree of this edge is finished.
        /// </summary>
        /// <param name="begin">[in] The id of the node the edge starts from.</param>
        /// <param name="end">[in] The id of the node the edge points to.</param>
        public virtual void visitEndOrderByClauseSyntax_Orderings(uint begin, uint end) { }

        /// <summary>
        /// Edge visitor for Expression edge which is called when the subtree of this edge is started.
        /// </summary>
        /// <param name="begin">[in] The id of the node the edge starts from.</param>
        /// <param name="end">[in] The id of the node the edge points to.</param>
        public virtual void visitOrderingSyntax_Expression(uint begin, uint end) { }

        /// <summary>
        /// Edge end visitor for Expression edge which is called after the subtree of this edge is finished.
        /// </summary>
        /// <param name="begin">[in] The id of the node the edge starts from.</param>
        /// <param name="end">[in] The id of the node the edge points to.</param>
        public virtual void visitEndOrderingSyntax_Expression(uint begin, uint end) { }

        /// <summary>
        /// Edge visitor for AttributeLists edge which is called when the subtree of this edge is started.
        /// </summary>
        /// <param name="begin">[in] The id of the node the edge starts from.</param>
        /// <param name="end">[in] The id of the node the edge points to.</param>
        public virtual void visitParameterSyntax_AttributeLists(uint begin, uint end) { }

        /// <summary>
        /// Edge end visitor for AttributeLists edge which is called after the subtree of this edge is finished.
        /// </summary>
        /// <param name="begin">[in] The id of the node the edge starts from.</param>
        /// <param name="end">[in] The id of the node the edge points to.</param>
        public virtual void visitEndParameterSyntax_AttributeLists(uint begin, uint end) { }

        /// <summary>
        /// Edge visitor for Default edge which is called when the subtree of this edge is started.
        /// </summary>
        /// <param name="begin">[in] The id of the node the edge starts from.</param>
        /// <param name="end">[in] The id of the node the edge points to.</param>
        public virtual void visitParameterSyntax_Default(uint begin, uint end) { }

        /// <summary>
        /// Edge end visitor for Default edge which is called after the subtree of this edge is finished.
        /// </summary>
        /// <param name="begin">[in] The id of the node the edge starts from.</param>
        /// <param name="end">[in] The id of the node the edge points to.</param>
        public virtual void visitEndParameterSyntax_Default(uint begin, uint end) { }

        /// <summary>
        /// Edge visitor for Type edge which is called when the subtree of this edge is started.
        /// </summary>
        /// <param name="begin">[in] The id of the node the edge starts from.</param>
        /// <param name="end">[in] The id of the node the edge points to.</param>
        public virtual void visitParameterSyntax_Type(uint begin, uint end) { }

        /// <summary>
        /// Edge end visitor for Type edge which is called after the subtree of this edge is finished.
        /// </summary>
        /// <param name="begin">[in] The id of the node the edge starts from.</param>
        /// <param name="end">[in] The id of the node the edge points to.</param>
        public virtual void visitEndParameterSyntax_Type(uint begin, uint end) { }

        /// <summary>
        /// Edge visitor for ExpressionBody edge which is called when the subtree of this edge is started.
        /// </summary>
        /// <param name="begin">[in] The id of the node the edge starts from.</param>
        /// <param name="end">[in] The id of the node the edge points to.</param>
        public virtual void visitPropertyDeclarationSyntax_ExpressionBody(uint begin, uint end) { }

        /// <summary>
        /// Edge end visitor for ExpressionBody edge which is called after the subtree of this edge is finished.
        /// </summary>
        /// <param name="begin">[in] The id of the node the edge starts from.</param>
        /// <param name="end">[in] The id of the node the edge points to.</param>
        public virtual void visitEndPropertyDeclarationSyntax_ExpressionBody(uint begin, uint end) { }

        /// <summary>
        /// Edge visitor for Initializer edge which is called when the subtree of this edge is started.
        /// </summary>
        /// <param name="begin">[in] The id of the node the edge starts from.</param>
        /// <param name="end">[in] The id of the node the edge points to.</param>
        public virtual void visitPropertyDeclarationSyntax_Initializer(uint begin, uint end) { }

        /// <summary>
        /// Edge end visitor for Initializer edge which is called after the subtree of this edge is finished.
        /// </summary>
        /// <param name="begin">[in] The id of the node the edge starts from.</param>
        /// <param name="end">[in] The id of the node the edge points to.</param>
        public virtual void visitEndPropertyDeclarationSyntax_Initializer(uint begin, uint end) { }

        /// <summary>
        /// Edge visitor for Container edge which is called when the subtree of this edge is started.
        /// </summary>
        /// <param name="begin">[in] The id of the node the edge starts from.</param>
        /// <param name="end">[in] The id of the node the edge points to.</param>
        public virtual void visitQualifiedCrefSyntax_Container(uint begin, uint end) { }

        /// <summary>
        /// Edge end visitor for Container edge which is called after the subtree of this edge is finished.
        /// </summary>
        /// <param name="begin">[in] The id of the node the edge starts from.</param>
        /// <param name="end">[in] The id of the node the edge points to.</param>
        public virtual void visitEndQualifiedCrefSyntax_Container(uint begin, uint end) { }

        /// <summary>
        /// Edge visitor for Member edge which is called when the subtree of this edge is started.
        /// </summary>
        /// <param name="begin">[in] The id of the node the edge starts from.</param>
        /// <param name="end">[in] The id of the node the edge points to.</param>
        public virtual void visitQualifiedCrefSyntax_Member(uint begin, uint end) { }

        /// <summary>
        /// Edge end visitor for Member edge which is called after the subtree of this edge is finished.
        /// </summary>
        /// <param name="begin">[in] The id of the node the edge starts from.</param>
        /// <param name="end">[in] The id of the node the edge points to.</param>
        public virtual void visitEndQualifiedCrefSyntax_Member(uint begin, uint end) { }

        /// <summary>
        /// Edge visitor for Clauses edge which is called when the subtree of this edge is started.
        /// </summary>
        /// <param name="begin">[in] The id of the node the edge starts from.</param>
        /// <param name="end">[in] The id of the node the edge points to.</param>
        public virtual void visitQueryBodySyntax_Clauses(uint begin, uint end) { }

        /// <summary>
        /// Edge end visitor for Clauses edge which is called after the subtree of this edge is finished.
        /// </summary>
        /// <param name="begin">[in] The id of the node the edge starts from.</param>
        /// <param name="end">[in] The id of the node the edge points to.</param>
        public virtual void visitEndQueryBodySyntax_Clauses(uint begin, uint end) { }

        /// <summary>
        /// Edge visitor for Continuation edge which is called when the subtree of this edge is started.
        /// </summary>
        /// <param name="begin">[in] The id of the node the edge starts from.</param>
        /// <param name="end">[in] The id of the node the edge points to.</param>
        public virtual void visitQueryBodySyntax_Continuation(uint begin, uint end) { }

        /// <summary>
        /// Edge end visitor for Continuation edge which is called after the subtree of this edge is finished.
        /// </summary>
        /// <param name="begin">[in] The id of the node the edge starts from.</param>
        /// <param name="end">[in] The id of the node the edge points to.</param>
        public virtual void visitEndQueryBodySyntax_Continuation(uint begin, uint end) { }

        /// <summary>
        /// Edge visitor for SelectOrGroup edge which is called when the subtree of this edge is started.
        /// </summary>
        /// <param name="begin">[in] The id of the node the edge starts from.</param>
        /// <param name="end">[in] The id of the node the edge points to.</param>
        public virtual void visitQueryBodySyntax_SelectOrGroup(uint begin, uint end) { }

        /// <summary>
        /// Edge end visitor for SelectOrGroup edge which is called after the subtree of this edge is finished.
        /// </summary>
        /// <param name="begin">[in] The id of the node the edge starts from.</param>
        /// <param name="end">[in] The id of the node the edge points to.</param>
        public virtual void visitEndQueryBodySyntax_SelectOrGroup(uint begin, uint end) { }

        /// <summary>
        /// Edge visitor for Body edge which is called when the subtree of this edge is started.
        /// </summary>
        /// <param name="begin">[in] The id of the node the edge starts from.</param>
        /// <param name="end">[in] The id of the node the edge points to.</param>
        public virtual void visitQueryContinuationSyntax_Body(uint begin, uint end) { }

        /// <summary>
        /// Edge end visitor for Body edge which is called after the subtree of this edge is finished.
        /// </summary>
        /// <param name="begin">[in] The id of the node the edge starts from.</param>
        /// <param name="end">[in] The id of the node the edge points to.</param>
        public virtual void visitEndQueryContinuationSyntax_Body(uint begin, uint end) { }

        /// <summary>
        /// Edge visitor for Expression edge which is called when the subtree of this edge is started.
        /// </summary>
        /// <param name="begin">[in] The id of the node the edge starts from.</param>
        /// <param name="end">[in] The id of the node the edge points to.</param>
        public virtual void visitSelectClauseSyntax_Expression(uint begin, uint end) { }

        /// <summary>
        /// Edge end visitor for Expression edge which is called after the subtree of this edge is finished.
        /// </summary>
        /// <param name="begin">[in] The id of the node the edge starts from.</param>
        /// <param name="end">[in] The id of the node the edge points to.</param>
        public virtual void visitEndSelectClauseSyntax_Expression(uint begin, uint end) { }

        /// <summary>
        /// Edge visitor for Labels edge which is called when the subtree of this edge is started.
        /// </summary>
        /// <param name="begin">[in] The id of the node the edge starts from.</param>
        /// <param name="end">[in] The id of the node the edge points to.</param>
        public virtual void visitSwitchSectionSyntax_Labels(uint begin, uint end) { }

        /// <summary>
        /// Edge end visitor for Labels edge which is called after the subtree of this edge is finished.
        /// </summary>
        /// <param name="begin">[in] The id of the node the edge starts from.</param>
        /// <param name="end">[in] The id of the node the edge points to.</param>
        public virtual void visitEndSwitchSectionSyntax_Labels(uint begin, uint end) { }

        /// <summary>
        /// Edge visitor for Statements edge which is called when the subtree of this edge is started.
        /// </summary>
        /// <param name="begin">[in] The id of the node the edge starts from.</param>
        /// <param name="end">[in] The id of the node the edge points to.</param>
        public virtual void visitSwitchSectionSyntax_Statements(uint begin, uint end) { }

        /// <summary>
        /// Edge end visitor for Statements edge which is called after the subtree of this edge is finished.
        /// </summary>
        /// <param name="begin">[in] The id of the node the edge starts from.</param>
        /// <param name="end">[in] The id of the node the edge points to.</param>
        public virtual void visitEndSwitchSectionSyntax_Statements(uint begin, uint end) { }

        /// <summary>
        /// Edge visitor for Arguments edge which is called when the subtree of this edge is started.
        /// </summary>
        /// <param name="begin">[in] The id of the node the edge starts from.</param>
        /// <param name="end">[in] The id of the node the edge points to.</param>
        public virtual void visitTypeArgumentListSyntax_Arguments(uint begin, uint end) { }

        /// <summary>
        /// Edge end visitor for Arguments edge which is called after the subtree of this edge is finished.
        /// </summary>
        /// <param name="begin">[in] The id of the node the edge starts from.</param>
        /// <param name="end">[in] The id of the node the edge points to.</param>
        public virtual void visitEndTypeArgumentListSyntax_Arguments(uint begin, uint end) { }

        /// <summary>
        /// Edge visitor for Type edge which is called when the subtree of this edge is started.
        /// </summary>
        /// <param name="begin">[in] The id of the node the edge starts from.</param>
        /// <param name="end">[in] The id of the node the edge points to.</param>
        public virtual void visitTypeConstraintSyntax_Type(uint begin, uint end) { }

        /// <summary>
        /// Edge end visitor for Type edge which is called after the subtree of this edge is finished.
        /// </summary>
        /// <param name="begin">[in] The id of the node the edge starts from.</param>
        /// <param name="end">[in] The id of the node the edge points to.</param>
        public virtual void visitEndTypeConstraintSyntax_Type(uint begin, uint end) { }

        /// <summary>
        /// Edge visitor for Type edge which is called when the subtree of this edge is started.
        /// </summary>
        /// <param name="begin">[in] The id of the node the edge starts from.</param>
        /// <param name="end">[in] The id of the node the edge points to.</param>
        public virtual void visitTypeCrefSyntax_Type(uint begin, uint end) { }

        /// <summary>
        /// Edge end visitor for Type edge which is called after the subtree of this edge is finished.
        /// </summary>
        /// <param name="begin">[in] The id of the node the edge starts from.</param>
        /// <param name="end">[in] The id of the node the edge points to.</param>
        public virtual void visitEndTypeCrefSyntax_Type(uint begin, uint end) { }

        /// <summary>
        /// Edge visitor for ConstraintClauses edge which is called when the subtree of this edge is started.
        /// </summary>
        /// <param name="begin">[in] The id of the node the edge starts from.</param>
        /// <param name="end">[in] The id of the node the edge points to.</param>
        public virtual void visitTypeDeclarationSyntax_ConstraintClauses(uint begin, uint end) { }

        /// <summary>
        /// Edge end visitor for ConstraintClauses edge which is called after the subtree of this edge is finished.
        /// </summary>
        /// <param name="begin">[in] The id of the node the edge starts from.</param>
        /// <param name="end">[in] The id of the node the edge points to.</param>
        public virtual void visitEndTypeDeclarationSyntax_ConstraintClauses(uint begin, uint end) { }

        /// <summary>
        /// Edge visitor for Members edge which is called when the subtree of this edge is started.
        /// </summary>
        /// <param name="begin">[in] The id of the node the edge starts from.</param>
        /// <param name="end">[in] The id of the node the edge points to.</param>
        public virtual void visitTypeDeclarationSyntax_Members(uint begin, uint end) { }

        /// <summary>
        /// Edge end visitor for Members edge which is called after the subtree of this edge is finished.
        /// </summary>
        /// <param name="begin">[in] The id of the node the edge starts from.</param>
        /// <param name="end">[in] The id of the node the edge points to.</param>
        public virtual void visitEndTypeDeclarationSyntax_Members(uint begin, uint end) { }

        /// <summary>
        /// Edge visitor for TypeParameterList edge which is called when the subtree of this edge is started.
        /// </summary>
        /// <param name="begin">[in] The id of the node the edge starts from.</param>
        /// <param name="end">[in] The id of the node the edge points to.</param>
        public virtual void visitTypeDeclarationSyntax_TypeParameterList(uint begin, uint end) { }

        /// <summary>
        /// Edge end visitor for TypeParameterList edge which is called after the subtree of this edge is finished.
        /// </summary>
        /// <param name="begin">[in] The id of the node the edge starts from.</param>
        /// <param name="end">[in] The id of the node the edge points to.</param>
        public virtual void visitEndTypeDeclarationSyntax_TypeParameterList(uint begin, uint end) { }

        /// <summary>
        /// Edge visitor for Constraints edge which is called when the subtree of this edge is started.
        /// </summary>
        /// <param name="begin">[in] The id of the node the edge starts from.</param>
        /// <param name="end">[in] The id of the node the edge points to.</param>
        public virtual void visitTypeParameterConstraintClauseSyntax_Constraints(uint begin, uint end) { }

        /// <summary>
        /// Edge end visitor for Constraints edge which is called after the subtree of this edge is finished.
        /// </summary>
        /// <param name="begin">[in] The id of the node the edge starts from.</param>
        /// <param name="end">[in] The id of the node the edge points to.</param>
        public virtual void visitEndTypeParameterConstraintClauseSyntax_Constraints(uint begin, uint end) { }

        /// <summary>
        /// Edge visitor for Name edge which is called when the subtree of this edge is started.
        /// </summary>
        /// <param name="begin">[in] The id of the node the edge starts from.</param>
        /// <param name="end">[in] The id of the node the edge points to.</param>
        public virtual void visitTypeParameterConstraintClauseSyntax_Name(uint begin, uint end) { }

        /// <summary>
        /// Edge end visitor for Name edge which is called after the subtree of this edge is finished.
        /// </summary>
        /// <param name="begin">[in] The id of the node the edge starts from.</param>
        /// <param name="end">[in] The id of the node the edge points to.</param>
        public virtual void visitEndTypeParameterConstraintClauseSyntax_Name(uint begin, uint end) { }

        /// <summary>
        /// Edge visitor for Parameters edge which.
        /// </summary>
        /// <param name="begin">[in] The id of the node the edge starts from.</param>
        /// <param name="end">[in] The id of the node the edge points to.</param>
        public virtual void visitTypeParameterListSyntax_Parameters(uint begin, uint end) { }

        /// <summary>
        /// Edge end visitor for Parameters edge which is called after the visit pair of this edge is called.
        /// </summary>
        /// <param name="begin">[in] The id of the node the edge starts from.</param>
        /// <param name="end">[in] The id of the node the edge points to.</param>
        public virtual void visitEndTypeParameterListSyntax_Parameters(uint begin, uint end) { }

        /// <summary>
        /// Edge visitor for AttributeLists edge which is called when the subtree of this edge is started.
        /// </summary>
        /// <param name="begin">[in] The id of the node the edge starts from.</param>
        /// <param name="end">[in] The id of the node the edge points to.</param>
        public virtual void visitTypeParameterSyntax_AttributeLists(uint begin, uint end) { }

        /// <summary>
        /// Edge end visitor for AttributeLists edge which is called after the subtree of this edge is finished.
        /// </summary>
        /// <param name="begin">[in] The id of the node the edge starts from.</param>
        /// <param name="end">[in] The id of the node the edge points to.</param>
        public virtual void visitEndTypeParameterSyntax_AttributeLists(uint begin, uint end) { }

        /// <summary>
        /// Edge visitor for Alias edge which is called when the subtree of this edge is started.
        /// </summary>
        /// <param name="begin">[in] The id of the node the edge starts from.</param>
        /// <param name="end">[in] The id of the node the edge points to.</param>
        public virtual void visitUsingDirectiveSyntax_Alias(uint begin, uint end) { }

        /// <summary>
        /// Edge end visitor for Alias edge which is called after the subtree of this edge is finished.
        /// </summary>
        /// <param name="begin">[in] The id of the node the edge starts from.</param>
        /// <param name="end">[in] The id of the node the edge points to.</param>
        public virtual void visitEndUsingDirectiveSyntax_Alias(uint begin, uint end) { }

        /// <summary>
        /// Edge visitor for Name edge which is called when the subtree of this edge is started.
        /// </summary>
        /// <param name="begin">[in] The id of the node the edge starts from.</param>
        /// <param name="end">[in] The id of the node the edge points to.</param>
        public virtual void visitUsingDirectiveSyntax_Name(uint begin, uint end) { }

        /// <summary>
        /// Edge end visitor for Name edge which is called after the subtree of this edge is finished.
        /// </summary>
        /// <param name="begin">[in] The id of the node the edge starts from.</param>
        /// <param name="end">[in] The id of the node the edge points to.</param>
        public virtual void visitEndUsingDirectiveSyntax_Name(uint begin, uint end) { }

        /// <summary>
        /// Edge visitor for Type edge which is called when the subtree of this edge is started.
        /// </summary>
        /// <param name="begin">[in] The id of the node the edge starts from.</param>
        /// <param name="end">[in] The id of the node the edge points to.</param>
        public virtual void visitVariableDeclarationSyntax_Type(uint begin, uint end) { }

        /// <summary>
        /// Edge end visitor for Type edge which is called after the subtree of this edge is finished.
        /// </summary>
        /// <param name="begin">[in] The id of the node the edge starts from.</param>
        /// <param name="end">[in] The id of the node the edge points to.</param>
        public virtual void visitEndVariableDeclarationSyntax_Type(uint begin, uint end) { }

        /// <summary>
        /// Edge visitor for Variables edge which is called when the subtree of this edge is started.
        /// </summary>
        /// <param name="begin">[in] The id of the node the edge starts from.</param>
        /// <param name="end">[in] The id of the node the edge points to.</param>
        public virtual void visitVariableDeclarationSyntax_Variables(uint begin, uint end) { }

        /// <summary>
        /// Edge end visitor for Variables edge which is called after the subtree of this edge is finished.
        /// </summary>
        /// <param name="begin">[in] The id of the node the edge starts from.</param>
        /// <param name="end">[in] The id of the node the edge points to.</param>
        public virtual void visitEndVariableDeclarationSyntax_Variables(uint begin, uint end) { }

        /// <summary>
        /// Edge visitor for ArgumentList edge which is called when the subtree of this edge is started.
        /// </summary>
        /// <param name="begin">[in] The id of the node the edge starts from.</param>
        /// <param name="end">[in] The id of the node the edge points to.</param>
        public virtual void visitVariableDeclaratorSyntax_ArgumentList(uint begin, uint end) { }

        /// <summary>
        /// Edge end visitor for ArgumentList edge which is called after the subtree of this edge is finished.
        /// </summary>
        /// <param name="begin">[in] The id of the node the edge starts from.</param>
        /// <param name="end">[in] The id of the node the edge points to.</param>
        public virtual void visitEndVariableDeclaratorSyntax_ArgumentList(uint begin, uint end) { }

        /// <summary>
        /// Edge visitor for Initializer edge which is called when the subtree of this edge is started.
        /// </summary>
        /// <param name="begin">[in] The id of the node the edge starts from.</param>
        /// <param name="end">[in] The id of the node the edge points to.</param>
        public virtual void visitVariableDeclaratorSyntax_Initializer(uint begin, uint end) { }

        /// <summary>
        /// Edge end visitor for Initializer edge which is called after the subtree of this edge is finished.
        /// </summary>
        /// <param name="begin">[in] The id of the node the edge starts from.</param>
        /// <param name="end">[in] The id of the node the edge points to.</param>
        public virtual void visitEndVariableDeclaratorSyntax_Initializer(uint begin, uint end) { }

        /// <summary>
        /// Edge visitor for Condition edge which is called when the subtree of this edge is started.
        /// </summary>
        /// <param name="begin">[in] The id of the node the edge starts from.</param>
        /// <param name="end">[in] The id of the node the edge points to.</param>
        public virtual void visitWhereClauseSyntax_Condition(uint begin, uint end) { }

        /// <summary>
        /// Edge end visitor for Condition edge which is called after the subtree of this edge is finished.
        /// </summary>
        /// <param name="begin">[in] The id of the node the edge starts from.</param>
        /// <param name="end">[in] The id of the node the edge points to.</param>
        public virtual void visitEndWhereClauseSyntax_Condition(uint begin, uint end) { }

        /// <summary>
        /// Edge visitor for Name edge which is called when the subtree of this edge is started.
        /// </summary>
        /// <param name="begin">[in] The id of the node the edge starts from.</param>
        /// <param name="end">[in] The id of the node the edge points to.</param>
        public virtual void visitXmlAttributeSyntax_Name(uint begin, uint end) { }

        /// <summary>
        /// Edge end visitor for Name edge which is called after the subtree of this edge is finished.
        /// </summary>
        /// <param name="begin">[in] The id of the node the edge starts from.</param>
        /// <param name="end">[in] The id of the node the edge points to.</param>
        public virtual void visitEndXmlAttributeSyntax_Name(uint begin, uint end) { }

        /// <summary>
        /// Edge visitor for Cref edge which is called when the subtree of this edge is started.
        /// </summary>
        /// <param name="begin">[in] The id of the node the edge starts from.</param>
        /// <param name="end">[in] The id of the node the edge points to.</param>
        public virtual void visitXmlCrefAttributeSyntax_Cref(uint begin, uint end) { }

        /// <summary>
        /// Edge end visitor for Cref edge which is called after the subtree of this edge is finished.
        /// </summary>
        /// <param name="begin">[in] The id of the node the edge starts from.</param>
        /// <param name="end">[in] The id of the node the edge points to.</param>
        public virtual void visitEndXmlCrefAttributeSyntax_Cref(uint begin, uint end) { }

        /// <summary>
        /// Edge visitor for Name edge which is called when the subtree of this edge is started.
        /// </summary>
        /// <param name="begin">[in] The id of the node the edge starts from.</param>
        /// <param name="end">[in] The id of the node the edge points to.</param>
        public virtual void visitXmlElementEndTagSyntax_Name(uint begin, uint end) { }

        /// <summary>
        /// Edge end visitor for Name edge which is called after the subtree of this edge is finished.
        /// </summary>
        /// <param name="begin">[in] The id of the node the edge starts from.</param>
        /// <param name="end">[in] The id of the node the edge points to.</param>
        public virtual void visitEndXmlElementEndTagSyntax_Name(uint begin, uint end) { }

        /// <summary>
        /// Edge visitor for Attributes edge which is called when the subtree of this edge is started.
        /// </summary>
        /// <param name="begin">[in] The id of the node the edge starts from.</param>
        /// <param name="end">[in] The id of the node the edge points to.</param>
        public virtual void visitXmlElementStartTagSyntax_Attributes(uint begin, uint end) { }

        /// <summary>
        /// Edge end visitor for Attributes edge which is called after the subtree of this edge is finished.
        /// </summary>
        /// <param name="begin">[in] The id of the node the edge starts from.</param>
        /// <param name="end">[in] The id of the node the edge points to.</param>
        public virtual void visitEndXmlElementStartTagSyntax_Attributes(uint begin, uint end) { }

        /// <summary>
        /// Edge visitor for Name edge which is called when the subtree of this edge is started.
        /// </summary>
        /// <param name="begin">[in] The id of the node the edge starts from.</param>
        /// <param name="end">[in] The id of the node the edge points to.</param>
        public virtual void visitXmlElementStartTagSyntax_Name(uint begin, uint end) { }

        /// <summary>
        /// Edge end visitor for Name edge which is called after the subtree of this edge is finished.
        /// </summary>
        /// <param name="begin">[in] The id of the node the edge starts from.</param>
        /// <param name="end">[in] The id of the node the edge points to.</param>
        public virtual void visitEndXmlElementStartTagSyntax_Name(uint begin, uint end) { }

        /// <summary>
        /// Edge visitor for Content edge which is called when the subtree of this edge is started.
        /// </summary>
        /// <param name="begin">[in] The id of the node the edge starts from.</param>
        /// <param name="end">[in] The id of the node the edge points to.</param>
        public virtual void visitXmlElementSyntax_Content(uint begin, uint end) { }

        /// <summary>
        /// Edge end visitor for Content edge which is called after the subtree of this edge is finished.
        /// </summary>
        /// <param name="begin">[in] The id of the node the edge starts from.</param>
        /// <param name="end">[in] The id of the node the edge points to.</param>
        public virtual void visitEndXmlElementSyntax_Content(uint begin, uint end) { }

        /// <summary>
        /// Edge visitor for EndTag edge which is called when the subtree of this edge is started.
        /// </summary>
        /// <param name="begin">[in] The id of the node the edge starts from.</param>
        /// <param name="end">[in] The id of the node the edge points to.</param>
        public virtual void visitXmlElementSyntax_EndTag(uint begin, uint end) { }

        /// <summary>
        /// Edge end visitor for EndTag edge which is called after the subtree of this edge is finished.
        /// </summary>
        /// <param name="begin">[in] The id of the node the edge starts from.</param>
        /// <param name="end">[in] The id of the node the edge points to.</param>
        public virtual void visitEndXmlElementSyntax_EndTag(uint begin, uint end) { }

        /// <summary>
        /// Edge visitor for StartTag edge which is called when the subtree of this edge is started.
        /// </summary>
        /// <param name="begin">[in] The id of the node the edge starts from.</param>
        /// <param name="end">[in] The id of the node the edge points to.</param>
        public virtual void visitXmlElementSyntax_StartTag(uint begin, uint end) { }

        /// <summary>
        /// Edge end visitor for StartTag edge which is called after the subtree of this edge is finished.
        /// </summary>
        /// <param name="begin">[in] The id of the node the edge starts from.</param>
        /// <param name="end">[in] The id of the node the edge points to.</param>
        public virtual void visitEndXmlElementSyntax_StartTag(uint begin, uint end) { }

        /// <summary>
        /// Edge visitor for Attributes edge which is called when the subtree of this edge is started.
        /// </summary>
        /// <param name="begin">[in] The id of the node the edge starts from.</param>
        /// <param name="end">[in] The id of the node the edge points to.</param>
        public virtual void visitXmlEmptyElementSyntax_Attributes(uint begin, uint end) { }

        /// <summary>
        /// Edge end visitor for Attributes edge which is called after the subtree of this edge is finished.
        /// </summary>
        /// <param name="begin">[in] The id of the node the edge starts from.</param>
        /// <param name="end">[in] The id of the node the edge points to.</param>
        public virtual void visitEndXmlEmptyElementSyntax_Attributes(uint begin, uint end) { }

        /// <summary>
        /// Edge visitor for Name edge which is called when the subtree of this edge is started.
        /// </summary>
        /// <param name="begin">[in] The id of the node the edge starts from.</param>
        /// <param name="end">[in] The id of the node the edge points to.</param>
        public virtual void visitXmlEmptyElementSyntax_Name(uint begin, uint end) { }

        /// <summary>
        /// Edge end visitor for Name edge which is called after the subtree of this edge is finished.
        /// </summary>
        /// <param name="begin">[in] The id of the node the edge starts from.</param>
        /// <param name="end">[in] The id of the node the edge points to.</param>
        public virtual void visitEndXmlEmptyElementSyntax_Name(uint begin, uint end) { }

        /// <summary>
        /// Edge visitor for Identifier edge which is called when the subtree of this edge is started.
        /// </summary>
        /// <param name="begin">[in] The id of the node the edge starts from.</param>
        /// <param name="end">[in] The id of the node the edge points to.</param>
        public virtual void visitXmlNameAttributeSyntax_Identifier(uint begin, uint end) { }

        /// <summary>
        /// Edge end visitor for Identifier edge which is called after the subtree of this edge is finished.
        /// </summary>
        /// <param name="begin">[in] The id of the node the edge starts from.</param>
        /// <param name="end">[in] The id of the node the edge points to.</param>
        public virtual void visitEndXmlNameAttributeSyntax_Identifier(uint begin, uint end) { }

        /// <summary>
        /// Edge visitor for Prefix edge which is called when the subtree of this edge is started.
        /// </summary>
        /// <param name="begin">[in] The id of the node the edge starts from.</param>
        /// <param name="end">[in] The id of the node the edge points to.</param>
        public virtual void visitXmlNameSyntax_Prefix(uint begin, uint end) { }

        /// <summary>
        /// Edge end visitor for Prefix edge which is called after the subtree of this edge is finished.
        /// </summary>
        /// <param name="begin">[in] The id of the node the edge starts from.</param>
        /// <param name="end">[in] The id of the node the edge points to.</param>
        public virtual void visitEndXmlNameSyntax_Prefix(uint begin, uint end) { }

        /// <summary>
        /// Edge visitor for Name edge which is called when the subtree of this edge is started.
        /// </summary>
        /// <param name="begin">[in] The id of the node the edge starts from.</param>
        /// <param name="end">[in] The id of the node the edge points to.</param>
        public virtual void visitXmlProcessingInstructionSyntax_Name(uint begin, uint end) { }

        /// <summary>
        /// Edge end visitor for Name edge which is called after the subtree of this edge is finished.
        /// </summary>
        /// <param name="begin">[in] The id of the node the edge starts from.</param>
        /// <param name="end">[in] The id of the node the edge points to.</param>
        public virtual void visitEndXmlProcessingInstructionSyntax_Name(uint begin, uint end) { }

        /// <summary>
        /// Begin the node visiting.
        /// </summary>
        public virtual void beginVisit(){}

        /// <summary>
        /// Finishes the node visiting.
        /// </summary>
        public virtual void finishVisit(){}


    }

}
