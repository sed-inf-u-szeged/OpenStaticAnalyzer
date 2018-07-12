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

namespace Columbus.Lim.Asg.Visitors {

    /// <summary>
    /// Visitor for each non-abstract nodes and all edges of the graph.
    /// </summary>
#if (LIM_INTERNAL)
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
        /// Empty abstract visitor for Columbus.Lim.Asg.Nodes.Base.Base node.
        /// </summary>
        public virtual void visit(Columbus.Lim.Asg.Nodes.Base.Base node, bool callVirtualBase) {}

        public virtual void visitEnd(Columbus.Lim.Asg.Nodes.Base.Base node, bool callVirtualBase) {}

        /// <summary>
        /// Abstract visitor, which calls the visitor of the base class (Columbus.Lim.Asg.Nodes.Base.Base) of the Columbus.Lim.Asg.Nodes.Base.Comment node.
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public override void visit(Columbus.Lim.Asg.Nodes.Base.Comment node, bool callVirtualBase) {
            visit((Columbus.Lim.Asg.Nodes.Base.Base)node, false);
        }

        /// <summary>
        /// Abstract end visitor, which calls the end visitor of the base class (Columbus.Lim.Asg.Nodes.Base.Base) of the Columbus.Lim.Asg.Nodes.Base.Comment node.
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public override void visitEnd(Columbus.Lim.Asg.Nodes.Base.Comment node, bool callVirtualBase) {
            visitEnd((Columbus.Lim.Asg.Nodes.Base.Base)node, false);
        }

        /// <summary>
        /// Abstract visitor, which calls the visitor of the base class (Columbus.Lim.Asg.Nodes.Base.Named) of the Columbus.Lim.Asg.Nodes.Base.Component node.
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public override void visit(Columbus.Lim.Asg.Nodes.Base.Component node, bool callVirtualBase) {
            visit((Columbus.Lim.Asg.Nodes.Base.Named)node, false);
        }

        /// <summary>
        /// Abstract end visitor, which calls the end visitor of the base class (Columbus.Lim.Asg.Nodes.Base.Named) of the Columbus.Lim.Asg.Nodes.Base.Component node.
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public override void visitEnd(Columbus.Lim.Asg.Nodes.Base.Component node, bool callVirtualBase) {
            visitEnd((Columbus.Lim.Asg.Nodes.Base.Named)node, false);
        }

        /// <summary>
        /// Abstract visitor, which calls the visitor of the base class (Columbus.Lim.Asg.Nodes.Base.Base) of the Columbus.Lim.Asg.Nodes.Base.ControlFlowBlock node.
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public override void visit(Columbus.Lim.Asg.Nodes.Base.ControlFlowBlock node, bool callVirtualBase) {
            visit((Columbus.Lim.Asg.Nodes.Base.Base)node, false);
        }

        /// <summary>
        /// Abstract end visitor, which calls the end visitor of the base class (Columbus.Lim.Asg.Nodes.Base.Base) of the Columbus.Lim.Asg.Nodes.Base.ControlFlowBlock node.
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public override void visitEnd(Columbus.Lim.Asg.Nodes.Base.ControlFlowBlock node, bool callVirtualBase) {
            visitEnd((Columbus.Lim.Asg.Nodes.Base.Base)node, false);
        }

        /// <summary>
        /// Abstract visitor, which calls the visitor of the base class (Columbus.Lim.Asg.Nodes.Base.Base) of the Columbus.Lim.Asg.Nodes.Base.Named node.
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public virtual void visit(Columbus.Lim.Asg.Nodes.Base.Named node, bool callVirtualBase) {
            visit((Columbus.Lim.Asg.Nodes.Base.Base)node, false);
        }

        /// <summary>
        /// Abstract end visitor, which calls the end visitor of the base class (Columbus.Lim.Asg.Nodes.Base.Base) of the Columbus.Lim.Asg.Nodes.Base.Named node.
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public virtual void visitEnd(Columbus.Lim.Asg.Nodes.Base.Named node, bool callVirtualBase) {
            visitEnd((Columbus.Lim.Asg.Nodes.Base.Base)node, false);
        }

        /// <summary>
        /// Abstract visitor, which calls the visitor of the base class (Columbus.Lim.Asg.Nodes.Logical.Member) of the Columbus.Lim.Asg.Nodes.Logical.Attribute node.
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public override void visit(Columbus.Lim.Asg.Nodes.Logical.Attribute node, bool callVirtualBase) {
            visit((Columbus.Lim.Asg.Nodes.Logical.Member)node, false);
        }

        /// <summary>
        /// Abstract end visitor, which calls the end visitor of the base class (Columbus.Lim.Asg.Nodes.Logical.Member) of the Columbus.Lim.Asg.Nodes.Logical.Attribute node.
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public override void visitEnd(Columbus.Lim.Asg.Nodes.Logical.Attribute node, bool callVirtualBase) {
            visitEnd((Columbus.Lim.Asg.Nodes.Logical.Member)node, false);
        }

        /// <summary>
        /// Abstract visitor, which calls the visitor of the base class (Columbus.Lim.Asg.Nodes.Base.Base) of the Columbus.Lim.Asg.Nodes.Logical.AttributeAccess node.
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public override void visit(Columbus.Lim.Asg.Nodes.Logical.AttributeAccess node, bool callVirtualBase) {
            visit((Columbus.Lim.Asg.Nodes.Base.Base)node, false);
        }

        /// <summary>
        /// Abstract end visitor, which calls the end visitor of the base class (Columbus.Lim.Asg.Nodes.Base.Base) of the Columbus.Lim.Asg.Nodes.Logical.AttributeAccess node.
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public override void visitEnd(Columbus.Lim.Asg.Nodes.Logical.AttributeAccess node, bool callVirtualBase) {
            visitEnd((Columbus.Lim.Asg.Nodes.Base.Base)node, false);
        }

        /// <summary>
        /// Abstract visitor, which calls the visitor of the base class (Columbus.Lim.Asg.Nodes.Logical.Scope) of the Columbus.Lim.Asg.Nodes.Logical.Class node.
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public override void visit(Columbus.Lim.Asg.Nodes.Logical.Class node, bool callVirtualBase) {
            visit((Columbus.Lim.Asg.Nodes.Logical.Scope)node, false);
        }

        /// <summary>
        /// Abstract end visitor, which calls the end visitor of the base class (Columbus.Lim.Asg.Nodes.Logical.Scope) of the Columbus.Lim.Asg.Nodes.Logical.Class node.
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public override void visitEnd(Columbus.Lim.Asg.Nodes.Logical.Class node, bool callVirtualBase) {
            visitEnd((Columbus.Lim.Asg.Nodes.Logical.Scope)node, false);
        }

        /// <summary>
        /// Abstract visitor, which calls the visitor of the base class (Columbus.Lim.Asg.Nodes.Logical.Class) of the Columbus.Lim.Asg.Nodes.Logical.ClassGeneric node.
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public override void visit(Columbus.Lim.Asg.Nodes.Logical.ClassGeneric node, bool callVirtualBase) {
            visit((Columbus.Lim.Asg.Nodes.Logical.Class)node, false);
        }

        /// <summary>
        /// Abstract end visitor, which calls the end visitor of the base class (Columbus.Lim.Asg.Nodes.Logical.Class) of the Columbus.Lim.Asg.Nodes.Logical.ClassGeneric node.
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public override void visitEnd(Columbus.Lim.Asg.Nodes.Logical.ClassGeneric node, bool callVirtualBase) {
            visitEnd((Columbus.Lim.Asg.Nodes.Logical.Class)node, false);
        }

        /// <summary>
        /// Abstract visitor, which calls the visitor of the base class (Columbus.Lim.Asg.Nodes.Logical.Class) of the Columbus.Lim.Asg.Nodes.Logical.ClassGenericInstance node.
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public override void visit(Columbus.Lim.Asg.Nodes.Logical.ClassGenericInstance node, bool callVirtualBase) {
            visit((Columbus.Lim.Asg.Nodes.Logical.Class)node, false);
        }

        /// <summary>
        /// Abstract end visitor, which calls the end visitor of the base class (Columbus.Lim.Asg.Nodes.Logical.Class) of the Columbus.Lim.Asg.Nodes.Logical.ClassGenericInstance node.
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public override void visitEnd(Columbus.Lim.Asg.Nodes.Logical.ClassGenericInstance node, bool callVirtualBase) {
            visitEnd((Columbus.Lim.Asg.Nodes.Logical.Class)node, false);
        }

        /// <summary>
        /// Abstract visitor, which calls the visitor of the base class (Columbus.Lim.Asg.Nodes.Logical.ClassGeneric) of the Columbus.Lim.Asg.Nodes.Logical.ClassGenericSpec node.
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public override void visit(Columbus.Lim.Asg.Nodes.Logical.ClassGenericSpec node, bool callVirtualBase) {
            visit((Columbus.Lim.Asg.Nodes.Logical.ClassGeneric)node, false);
        }

        /// <summary>
        /// Abstract end visitor, which calls the end visitor of the base class (Columbus.Lim.Asg.Nodes.Logical.ClassGeneric) of the Columbus.Lim.Asg.Nodes.Logical.ClassGenericSpec node.
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public override void visitEnd(Columbus.Lim.Asg.Nodes.Logical.ClassGenericSpec node, bool callVirtualBase) {
            visitEnd((Columbus.Lim.Asg.Nodes.Logical.ClassGeneric)node, false);
        }

        /// <summary>
        /// Abstract visitor, which calls the visitor of the base class (Columbus.Lim.Asg.Nodes.Base.Base) of the Columbus.Lim.Asg.Nodes.Logical.Friendship node.
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public override void visit(Columbus.Lim.Asg.Nodes.Logical.Friendship node, bool callVirtualBase) {
            visit((Columbus.Lim.Asg.Nodes.Base.Base)node, false);
        }

        /// <summary>
        /// Abstract end visitor, which calls the end visitor of the base class (Columbus.Lim.Asg.Nodes.Base.Base) of the Columbus.Lim.Asg.Nodes.Logical.Friendship node.
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public override void visitEnd(Columbus.Lim.Asg.Nodes.Logical.Friendship node, bool callVirtualBase) {
            visitEnd((Columbus.Lim.Asg.Nodes.Base.Base)node, false);
        }

        /// <summary>
        /// Abstract visitor, which calls the visitor of the base class (Columbus.Lim.Asg.Nodes.Base.Named) of the Columbus.Lim.Asg.Nodes.Logical.GenericParameter node.
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public override void visit(Columbus.Lim.Asg.Nodes.Logical.GenericParameter node, bool callVirtualBase) {
            visit((Columbus.Lim.Asg.Nodes.Base.Named)node, false);
        }

        /// <summary>
        /// Abstract end visitor, which calls the end visitor of the base class (Columbus.Lim.Asg.Nodes.Base.Named) of the Columbus.Lim.Asg.Nodes.Logical.GenericParameter node.
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public override void visitEnd(Columbus.Lim.Asg.Nodes.Logical.GenericParameter node, bool callVirtualBase) {
            visitEnd((Columbus.Lim.Asg.Nodes.Base.Named)node, false);
        }

        /// <summary>
        /// Abstract visitor, which calls the visitor of the base class (Columbus.Lim.Asg.Nodes.Base.Named) of the Columbus.Lim.Asg.Nodes.Logical.Member node.
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public virtual void visit(Columbus.Lim.Asg.Nodes.Logical.Member node, bool callVirtualBase) {
            visit((Columbus.Lim.Asg.Nodes.Base.Named)node, false);
        }

        /// <summary>
        /// Abstract end visitor, which calls the end visitor of the base class (Columbus.Lim.Asg.Nodes.Base.Named) of the Columbus.Lim.Asg.Nodes.Logical.Member node.
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public virtual void visitEnd(Columbus.Lim.Asg.Nodes.Logical.Member node, bool callVirtualBase) {
            visitEnd((Columbus.Lim.Asg.Nodes.Base.Named)node, false);
        }

        /// <summary>
        /// Abstract visitor, which calls the visitor of the base class (Columbus.Lim.Asg.Nodes.Logical.Scope) of the Columbus.Lim.Asg.Nodes.Logical.Method node.
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public override void visit(Columbus.Lim.Asg.Nodes.Logical.Method node, bool callVirtualBase) {
            visit((Columbus.Lim.Asg.Nodes.Logical.Scope)node, false);
        }

        /// <summary>
        /// Abstract end visitor, which calls the end visitor of the base class (Columbus.Lim.Asg.Nodes.Logical.Scope) of the Columbus.Lim.Asg.Nodes.Logical.Method node.
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public override void visitEnd(Columbus.Lim.Asg.Nodes.Logical.Method node, bool callVirtualBase) {
            visitEnd((Columbus.Lim.Asg.Nodes.Logical.Scope)node, false);
        }

        /// <summary>
        /// Abstract visitor, which calls the visitor of the base class (Columbus.Lim.Asg.Nodes.Base.Base) of the Columbus.Lim.Asg.Nodes.Logical.MethodCall node.
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public override void visit(Columbus.Lim.Asg.Nodes.Logical.MethodCall node, bool callVirtualBase) {
            visit((Columbus.Lim.Asg.Nodes.Base.Base)node, false);
        }

        /// <summary>
        /// Abstract end visitor, which calls the end visitor of the base class (Columbus.Lim.Asg.Nodes.Base.Base) of the Columbus.Lim.Asg.Nodes.Logical.MethodCall node.
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public override void visitEnd(Columbus.Lim.Asg.Nodes.Logical.MethodCall node, bool callVirtualBase) {
            visitEnd((Columbus.Lim.Asg.Nodes.Base.Base)node, false);
        }

        /// <summary>
        /// Abstract visitor, which calls the visitor of the base class (Columbus.Lim.Asg.Nodes.Logical.Method) of the Columbus.Lim.Asg.Nodes.Logical.MethodGeneric node.
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public override void visit(Columbus.Lim.Asg.Nodes.Logical.MethodGeneric node, bool callVirtualBase) {
            visit((Columbus.Lim.Asg.Nodes.Logical.Method)node, false);
        }

        /// <summary>
        /// Abstract end visitor, which calls the end visitor of the base class (Columbus.Lim.Asg.Nodes.Logical.Method) of the Columbus.Lim.Asg.Nodes.Logical.MethodGeneric node.
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public override void visitEnd(Columbus.Lim.Asg.Nodes.Logical.MethodGeneric node, bool callVirtualBase) {
            visitEnd((Columbus.Lim.Asg.Nodes.Logical.Method)node, false);
        }

        /// <summary>
        /// Abstract visitor, which calls the visitor of the base class (Columbus.Lim.Asg.Nodes.Logical.Method) of the Columbus.Lim.Asg.Nodes.Logical.MethodGenericInstance node.
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public override void visit(Columbus.Lim.Asg.Nodes.Logical.MethodGenericInstance node, bool callVirtualBase) {
            visit((Columbus.Lim.Asg.Nodes.Logical.Method)node, false);
        }

        /// <summary>
        /// Abstract end visitor, which calls the end visitor of the base class (Columbus.Lim.Asg.Nodes.Logical.Method) of the Columbus.Lim.Asg.Nodes.Logical.MethodGenericInstance node.
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public override void visitEnd(Columbus.Lim.Asg.Nodes.Logical.MethodGenericInstance node, bool callVirtualBase) {
            visitEnd((Columbus.Lim.Asg.Nodes.Logical.Method)node, false);
        }

        /// <summary>
        /// Abstract visitor, which calls the visitor of the base class (Columbus.Lim.Asg.Nodes.Logical.MethodGeneric) of the Columbus.Lim.Asg.Nodes.Logical.MethodGenericSpec node.
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public override void visit(Columbus.Lim.Asg.Nodes.Logical.MethodGenericSpec node, bool callVirtualBase) {
            visit((Columbus.Lim.Asg.Nodes.Logical.MethodGeneric)node, false);
        }

        /// <summary>
        /// Abstract end visitor, which calls the end visitor of the base class (Columbus.Lim.Asg.Nodes.Logical.MethodGeneric) of the Columbus.Lim.Asg.Nodes.Logical.MethodGenericSpec node.
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public override void visitEnd(Columbus.Lim.Asg.Nodes.Logical.MethodGenericSpec node, bool callVirtualBase) {
            visitEnd((Columbus.Lim.Asg.Nodes.Logical.MethodGeneric)node, false);
        }

        /// <summary>
        /// Abstract visitor, which calls the visitor of the base class (Columbus.Lim.Asg.Nodes.Logical.Scope) of the Columbus.Lim.Asg.Nodes.Logical.Package node.
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public override void visit(Columbus.Lim.Asg.Nodes.Logical.Package node, bool callVirtualBase) {
            visit((Columbus.Lim.Asg.Nodes.Logical.Scope)node, false);
        }

        /// <summary>
        /// Abstract end visitor, which calls the end visitor of the base class (Columbus.Lim.Asg.Nodes.Logical.Scope) of the Columbus.Lim.Asg.Nodes.Logical.Package node.
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public override void visitEnd(Columbus.Lim.Asg.Nodes.Logical.Package node, bool callVirtualBase) {
            visitEnd((Columbus.Lim.Asg.Nodes.Logical.Scope)node, false);
        }

        /// <summary>
        /// Abstract visitor, which calls the visitor of the base class (Columbus.Lim.Asg.Nodes.Base.Named) of the Columbus.Lim.Asg.Nodes.Logical.Parameter node.
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public override void visit(Columbus.Lim.Asg.Nodes.Logical.Parameter node, bool callVirtualBase) {
            visit((Columbus.Lim.Asg.Nodes.Base.Named)node, false);
        }

        /// <summary>
        /// Abstract end visitor, which calls the end visitor of the base class (Columbus.Lim.Asg.Nodes.Base.Named) of the Columbus.Lim.Asg.Nodes.Logical.Parameter node.
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public override void visitEnd(Columbus.Lim.Asg.Nodes.Logical.Parameter node, bool callVirtualBase) {
            visitEnd((Columbus.Lim.Asg.Nodes.Base.Named)node, false);
        }

        /// <summary>
        /// Abstract visitor, which calls the visitor of the base class (Columbus.Lim.Asg.Nodes.Logical.Member) of the Columbus.Lim.Asg.Nodes.Logical.Scope node.
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public virtual void visit(Columbus.Lim.Asg.Nodes.Logical.Scope node, bool callVirtualBase) {
            visit((Columbus.Lim.Asg.Nodes.Logical.Member)node, false);
        }

        /// <summary>
        /// Abstract end visitor, which calls the end visitor of the base class (Columbus.Lim.Asg.Nodes.Logical.Member) of the Columbus.Lim.Asg.Nodes.Logical.Scope node.
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public virtual void visitEnd(Columbus.Lim.Asg.Nodes.Logical.Scope node, bool callVirtualBase) {
            visitEnd((Columbus.Lim.Asg.Nodes.Logical.Member)node, false);
        }

        /// <summary>
        /// Abstract visitor, which calls the visitor of the base class (Columbus.Lim.Asg.Nodes.Base.Named) of the Columbus.Lim.Asg.Nodes.Physical.FSEntry node.
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public virtual void visit(Columbus.Lim.Asg.Nodes.Physical.FSEntry node, bool callVirtualBase) {
            visit((Columbus.Lim.Asg.Nodes.Base.Named)node, false);
        }

        /// <summary>
        /// Abstract end visitor, which calls the end visitor of the base class (Columbus.Lim.Asg.Nodes.Base.Named) of the Columbus.Lim.Asg.Nodes.Physical.FSEntry node.
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public virtual void visitEnd(Columbus.Lim.Asg.Nodes.Physical.FSEntry node, bool callVirtualBase) {
            visitEnd((Columbus.Lim.Asg.Nodes.Base.Named)node, false);
        }

        /// <summary>
        /// Abstract visitor, which calls the visitor of the base class (Columbus.Lim.Asg.Nodes.Physical.FSEntry) of the Columbus.Lim.Asg.Nodes.Physical.File node.
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public override void visit(Columbus.Lim.Asg.Nodes.Physical.File node, bool callVirtualBase) {
            visit((Columbus.Lim.Asg.Nodes.Physical.FSEntry)node, false);
        }

        /// <summary>
        /// Abstract end visitor, which calls the end visitor of the base class (Columbus.Lim.Asg.Nodes.Physical.FSEntry) of the Columbus.Lim.Asg.Nodes.Physical.File node.
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public override void visitEnd(Columbus.Lim.Asg.Nodes.Physical.File node, bool callVirtualBase) {
            visitEnd((Columbus.Lim.Asg.Nodes.Physical.FSEntry)node, false);
        }

        /// <summary>
        /// Abstract visitor, which calls the visitor of the base class (Columbus.Lim.Asg.Nodes.Base.Named) of the Columbus.Lim.Asg.Nodes.Physical.FileSystem node.
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public override void visit(Columbus.Lim.Asg.Nodes.Physical.FileSystem node, bool callVirtualBase) {
            visit((Columbus.Lim.Asg.Nodes.Base.Named)node, false);
        }

        /// <summary>
        /// Abstract end visitor, which calls the end visitor of the base class (Columbus.Lim.Asg.Nodes.Base.Named) of the Columbus.Lim.Asg.Nodes.Physical.FileSystem node.
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public override void visitEnd(Columbus.Lim.Asg.Nodes.Physical.FileSystem node, bool callVirtualBase) {
            visitEnd((Columbus.Lim.Asg.Nodes.Base.Named)node, false);
        }

        /// <summary>
        /// Abstract visitor, which calls the visitor of the base class (Columbus.Lim.Asg.Nodes.Physical.FSEntry) of the Columbus.Lim.Asg.Nodes.Physical.Folder node.
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public override void visit(Columbus.Lim.Asg.Nodes.Physical.Folder node, bool callVirtualBase) {
            visit((Columbus.Lim.Asg.Nodes.Physical.FSEntry)node, false);
        }

        /// <summary>
        /// Abstract end visitor, which calls the end visitor of the base class (Columbus.Lim.Asg.Nodes.Physical.FSEntry) of the Columbus.Lim.Asg.Nodes.Physical.Folder node.
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public override void visitEnd(Columbus.Lim.Asg.Nodes.Physical.Folder node, bool callVirtualBase) {
            visitEnd((Columbus.Lim.Asg.Nodes.Physical.FSEntry)node, false);
        }

        /// <summary>
        /// Abstract visitor, which calls the visitor of the base class (Columbus.Lim.Asg.Nodes.Base.Base) of the Columbus.Lim.Asg.Nodes.Type.SimpleType node.
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public override void visit(Columbus.Lim.Asg.Nodes.Type.SimpleType node, bool callVirtualBase) {
            visit((Columbus.Lim.Asg.Nodes.Base.Base)node, false);
        }

        /// <summary>
        /// Abstract end visitor, which calls the end visitor of the base class (Columbus.Lim.Asg.Nodes.Base.Base) of the Columbus.Lim.Asg.Nodes.Type.SimpleType node.
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public override void visitEnd(Columbus.Lim.Asg.Nodes.Type.SimpleType node, bool callVirtualBase) {
            visitEnd((Columbus.Lim.Asg.Nodes.Base.Base)node, false);
        }

        /// <summary>
        /// Abstract visitor, which calls the visitor of the base class (Columbus.Lim.Asg.Nodes.Base.Base) of the Columbus.Lim.Asg.Nodes.Type.Type node.
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public override void visit(Columbus.Lim.Asg.Nodes.Type.Type node, bool callVirtualBase) {
            visit((Columbus.Lim.Asg.Nodes.Base.Base)node, false);
        }

        /// <summary>
        /// Abstract end visitor, which calls the end visitor of the base class (Columbus.Lim.Asg.Nodes.Base.Base) of the Columbus.Lim.Asg.Nodes.Type.Type node.
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public override void visitEnd(Columbus.Lim.Asg.Nodes.Type.Type node, bool callVirtualBase) {
            visitEnd((Columbus.Lim.Asg.Nodes.Base.Base)node, false);
        }

        /// <summary>
        /// Abstract visitor, which calls the visitor of the base class (Columbus.Lim.Asg.Nodes.Base.Base) of the Columbus.Lim.Asg.Nodes.Type.TypeFormer node.
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public virtual void visit(Columbus.Lim.Asg.Nodes.Type.TypeFormer node, bool callVirtualBase) {
            visit((Columbus.Lim.Asg.Nodes.Base.Base)node, false);
        }

        /// <summary>
        /// Abstract end visitor, which calls the end visitor of the base class (Columbus.Lim.Asg.Nodes.Base.Base) of the Columbus.Lim.Asg.Nodes.Type.TypeFormer node.
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public virtual void visitEnd(Columbus.Lim.Asg.Nodes.Type.TypeFormer node, bool callVirtualBase) {
            visitEnd((Columbus.Lim.Asg.Nodes.Base.Base)node, false);
        }

        /// <summary>
        /// Abstract visitor, which calls the visitor of the base class (Columbus.Lim.Asg.Nodes.Type.TypeFormer) of the Columbus.Lim.Asg.Nodes.Type.TypeFormerArray node.
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public override void visit(Columbus.Lim.Asg.Nodes.Type.TypeFormerArray node, bool callVirtualBase) {
            visit((Columbus.Lim.Asg.Nodes.Type.TypeFormer)node, false);
        }

        /// <summary>
        /// Abstract end visitor, which calls the end visitor of the base class (Columbus.Lim.Asg.Nodes.Type.TypeFormer) of the Columbus.Lim.Asg.Nodes.Type.TypeFormerArray node.
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public override void visitEnd(Columbus.Lim.Asg.Nodes.Type.TypeFormerArray node, bool callVirtualBase) {
            visitEnd((Columbus.Lim.Asg.Nodes.Type.TypeFormer)node, false);
        }

        /// <summary>
        /// Abstract visitor, which calls the visitor of the base class (Columbus.Lim.Asg.Nodes.Type.TypeFormer) of the Columbus.Lim.Asg.Nodes.Type.TypeFormerMethod node.
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public override void visit(Columbus.Lim.Asg.Nodes.Type.TypeFormerMethod node, bool callVirtualBase) {
            visit((Columbus.Lim.Asg.Nodes.Type.TypeFormer)node, false);
        }

        /// <summary>
        /// Abstract end visitor, which calls the end visitor of the base class (Columbus.Lim.Asg.Nodes.Type.TypeFormer) of the Columbus.Lim.Asg.Nodes.Type.TypeFormerMethod node.
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public override void visitEnd(Columbus.Lim.Asg.Nodes.Type.TypeFormerMethod node, bool callVirtualBase) {
            visitEnd((Columbus.Lim.Asg.Nodes.Type.TypeFormer)node, false);
        }

        /// <summary>
        /// Abstract visitor, which calls the visitor of the base class (Columbus.Lim.Asg.Nodes.Type.TypeFormer) of the Columbus.Lim.Asg.Nodes.Type.TypeFormerNonType node.
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public override void visit(Columbus.Lim.Asg.Nodes.Type.TypeFormerNonType node, bool callVirtualBase) {
            visit((Columbus.Lim.Asg.Nodes.Type.TypeFormer)node, false);
        }

        /// <summary>
        /// Abstract end visitor, which calls the end visitor of the base class (Columbus.Lim.Asg.Nodes.Type.TypeFormer) of the Columbus.Lim.Asg.Nodes.Type.TypeFormerNonType node.
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public override void visitEnd(Columbus.Lim.Asg.Nodes.Type.TypeFormerNonType node, bool callVirtualBase) {
            visitEnd((Columbus.Lim.Asg.Nodes.Type.TypeFormer)node, false);
        }

        /// <summary>
        /// Abstract visitor, which calls the visitor of the base class (Columbus.Lim.Asg.Nodes.Type.TypeFormer) of the Columbus.Lim.Asg.Nodes.Type.TypeFormerPointer node.
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public override void visit(Columbus.Lim.Asg.Nodes.Type.TypeFormerPointer node, bool callVirtualBase) {
            visit((Columbus.Lim.Asg.Nodes.Type.TypeFormer)node, false);
        }

        /// <summary>
        /// Abstract end visitor, which calls the end visitor of the base class (Columbus.Lim.Asg.Nodes.Type.TypeFormer) of the Columbus.Lim.Asg.Nodes.Type.TypeFormerPointer node.
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public override void visitEnd(Columbus.Lim.Asg.Nodes.Type.TypeFormerPointer node, bool callVirtualBase) {
            visitEnd((Columbus.Lim.Asg.Nodes.Type.TypeFormer)node, false);
        }

        /// <summary>
        /// Abstract visitor, which calls the visitor of the base class (Columbus.Lim.Asg.Nodes.Type.TypeFormer) of the Columbus.Lim.Asg.Nodes.Type.TypeFormerType node.
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public override void visit(Columbus.Lim.Asg.Nodes.Type.TypeFormerType node, bool callVirtualBase) {
            visit((Columbus.Lim.Asg.Nodes.Type.TypeFormer)node, false);
        }

        /// <summary>
        /// Abstract end visitor, which calls the end visitor of the base class (Columbus.Lim.Asg.Nodes.Type.TypeFormer) of the Columbus.Lim.Asg.Nodes.Type.TypeFormerType node.
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public override void visitEnd(Columbus.Lim.Asg.Nodes.Type.TypeFormerType node, bool callVirtualBase) {
            visitEnd((Columbus.Lim.Asg.Nodes.Type.TypeFormer)node, false);
        }

    }

}
