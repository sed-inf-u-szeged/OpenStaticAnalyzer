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

namespace Columbus.Lim.Asg.Visitors {

    /// <summary>
    /// Visitor for each non-abstract nodes and all edges of the graph.
    /// </summary>
#if (LIM_INTERNAL)
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
        /// Visitor which is called at the beginning of the Columbus.Lim.Asg.Nodes.Base.Comment node visiting.
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public virtual void visit(Columbus.Lim.Asg.Nodes.Base.Comment node, bool callVirtualBase = true) { }

        /// <summary>
        /// Visitor which is called at the end of the Columbus.Lim.Asg.Nodes.Base.Comment node visiting.
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public virtual void visitEnd(Columbus.Lim.Asg.Nodes.Base.Comment node, bool callVirtualBase = true) { }

        /// <summary>
        /// Visitor which is called at the beginning of the Columbus.Lim.Asg.Nodes.Base.Component node visiting.
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public virtual void visit(Columbus.Lim.Asg.Nodes.Base.Component node, bool callVirtualBase = true) { }

        /// <summary>
        /// Visitor which is called at the end of the Columbus.Lim.Asg.Nodes.Base.Component node visiting.
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public virtual void visitEnd(Columbus.Lim.Asg.Nodes.Base.Component node, bool callVirtualBase = true) { }

        /// <summary>
        /// Visitor which is called at the beginning of the Columbus.Lim.Asg.Nodes.Base.ControlFlowBlock node visiting.
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public virtual void visit(Columbus.Lim.Asg.Nodes.Base.ControlFlowBlock node, bool callVirtualBase = true) { }

        /// <summary>
        /// Visitor which is called at the end of the Columbus.Lim.Asg.Nodes.Base.ControlFlowBlock node visiting.
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public virtual void visitEnd(Columbus.Lim.Asg.Nodes.Base.ControlFlowBlock node, bool callVirtualBase = true) { }

        /// <summary>
        /// Visitor which is called at the beginning of the Columbus.Lim.Asg.Nodes.Logical.Attribute node visiting.
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public virtual void visit(Columbus.Lim.Asg.Nodes.Logical.Attribute node, bool callVirtualBase = true) { }

        /// <summary>
        /// Visitor which is called at the end of the Columbus.Lim.Asg.Nodes.Logical.Attribute node visiting.
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public virtual void visitEnd(Columbus.Lim.Asg.Nodes.Logical.Attribute node, bool callVirtualBase = true) { }

        /// <summary>
        /// Visitor which is called at the beginning of the Columbus.Lim.Asg.Nodes.Logical.AttributeAccess node visiting.
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public virtual void visit(Columbus.Lim.Asg.Nodes.Logical.AttributeAccess node, bool callVirtualBase = true) { }

        /// <summary>
        /// Visitor which is called at the end of the Columbus.Lim.Asg.Nodes.Logical.AttributeAccess node visiting.
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public virtual void visitEnd(Columbus.Lim.Asg.Nodes.Logical.AttributeAccess node, bool callVirtualBase = true) { }

        /// <summary>
        /// Visitor which is called at the beginning of the Columbus.Lim.Asg.Nodes.Logical.Class node visiting.
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public virtual void visit(Columbus.Lim.Asg.Nodes.Logical.Class node, bool callVirtualBase = true) { }

        /// <summary>
        /// Visitor which is called at the end of the Columbus.Lim.Asg.Nodes.Logical.Class node visiting.
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public virtual void visitEnd(Columbus.Lim.Asg.Nodes.Logical.Class node, bool callVirtualBase = true) { }

        /// <summary>
        /// Visitor which is called at the beginning of the Columbus.Lim.Asg.Nodes.Logical.ClassGeneric node visiting.
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public virtual void visit(Columbus.Lim.Asg.Nodes.Logical.ClassGeneric node, bool callVirtualBase = true) { }

        /// <summary>
        /// Visitor which is called at the end of the Columbus.Lim.Asg.Nodes.Logical.ClassGeneric node visiting.
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public virtual void visitEnd(Columbus.Lim.Asg.Nodes.Logical.ClassGeneric node, bool callVirtualBase = true) { }

        /// <summary>
        /// Visitor which is called at the beginning of the Columbus.Lim.Asg.Nodes.Logical.ClassGenericInstance node visiting.
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public virtual void visit(Columbus.Lim.Asg.Nodes.Logical.ClassGenericInstance node, bool callVirtualBase = true) { }

        /// <summary>
        /// Visitor which is called at the end of the Columbus.Lim.Asg.Nodes.Logical.ClassGenericInstance node visiting.
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public virtual void visitEnd(Columbus.Lim.Asg.Nodes.Logical.ClassGenericInstance node, bool callVirtualBase = true) { }

        /// <summary>
        /// Visitor which is called at the beginning of the Columbus.Lim.Asg.Nodes.Logical.ClassGenericSpec node visiting.
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public virtual void visit(Columbus.Lim.Asg.Nodes.Logical.ClassGenericSpec node, bool callVirtualBase = true) { }

        /// <summary>
        /// Visitor which is called at the end of the Columbus.Lim.Asg.Nodes.Logical.ClassGenericSpec node visiting.
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public virtual void visitEnd(Columbus.Lim.Asg.Nodes.Logical.ClassGenericSpec node, bool callVirtualBase = true) { }

        /// <summary>
        /// Visitor which is called at the beginning of the Columbus.Lim.Asg.Nodes.Logical.Friendship node visiting.
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public virtual void visit(Columbus.Lim.Asg.Nodes.Logical.Friendship node, bool callVirtualBase = true) { }

        /// <summary>
        /// Visitor which is called at the end of the Columbus.Lim.Asg.Nodes.Logical.Friendship node visiting.
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public virtual void visitEnd(Columbus.Lim.Asg.Nodes.Logical.Friendship node, bool callVirtualBase = true) { }

        /// <summary>
        /// Visitor which is called at the beginning of the Columbus.Lim.Asg.Nodes.Logical.GenericParameter node visiting.
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public virtual void visit(Columbus.Lim.Asg.Nodes.Logical.GenericParameter node, bool callVirtualBase = true) { }

        /// <summary>
        /// Visitor which is called at the end of the Columbus.Lim.Asg.Nodes.Logical.GenericParameter node visiting.
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public virtual void visitEnd(Columbus.Lim.Asg.Nodes.Logical.GenericParameter node, bool callVirtualBase = true) { }

        /// <summary>
        /// Visitor which is called at the beginning of the Columbus.Lim.Asg.Nodes.Logical.Method node visiting.
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public virtual void visit(Columbus.Lim.Asg.Nodes.Logical.Method node, bool callVirtualBase = true) { }

        /// <summary>
        /// Visitor which is called at the end of the Columbus.Lim.Asg.Nodes.Logical.Method node visiting.
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public virtual void visitEnd(Columbus.Lim.Asg.Nodes.Logical.Method node, bool callVirtualBase = true) { }

        /// <summary>
        /// Visitor which is called at the beginning of the Columbus.Lim.Asg.Nodes.Logical.MethodCall node visiting.
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public virtual void visit(Columbus.Lim.Asg.Nodes.Logical.MethodCall node, bool callVirtualBase = true) { }

        /// <summary>
        /// Visitor which is called at the end of the Columbus.Lim.Asg.Nodes.Logical.MethodCall node visiting.
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public virtual void visitEnd(Columbus.Lim.Asg.Nodes.Logical.MethodCall node, bool callVirtualBase = true) { }

        /// <summary>
        /// Visitor which is called at the beginning of the Columbus.Lim.Asg.Nodes.Logical.MethodGeneric node visiting.
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public virtual void visit(Columbus.Lim.Asg.Nodes.Logical.MethodGeneric node, bool callVirtualBase = true) { }

        /// <summary>
        /// Visitor which is called at the end of the Columbus.Lim.Asg.Nodes.Logical.MethodGeneric node visiting.
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public virtual void visitEnd(Columbus.Lim.Asg.Nodes.Logical.MethodGeneric node, bool callVirtualBase = true) { }

        /// <summary>
        /// Visitor which is called at the beginning of the Columbus.Lim.Asg.Nodes.Logical.MethodGenericInstance node visiting.
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public virtual void visit(Columbus.Lim.Asg.Nodes.Logical.MethodGenericInstance node, bool callVirtualBase = true) { }

        /// <summary>
        /// Visitor which is called at the end of the Columbus.Lim.Asg.Nodes.Logical.MethodGenericInstance node visiting.
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public virtual void visitEnd(Columbus.Lim.Asg.Nodes.Logical.MethodGenericInstance node, bool callVirtualBase = true) { }

        /// <summary>
        /// Visitor which is called at the beginning of the Columbus.Lim.Asg.Nodes.Logical.MethodGenericSpec node visiting.
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public virtual void visit(Columbus.Lim.Asg.Nodes.Logical.MethodGenericSpec node, bool callVirtualBase = true) { }

        /// <summary>
        /// Visitor which is called at the end of the Columbus.Lim.Asg.Nodes.Logical.MethodGenericSpec node visiting.
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public virtual void visitEnd(Columbus.Lim.Asg.Nodes.Logical.MethodGenericSpec node, bool callVirtualBase = true) { }

        /// <summary>
        /// Visitor which is called at the beginning of the Columbus.Lim.Asg.Nodes.Logical.Package node visiting.
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public virtual void visit(Columbus.Lim.Asg.Nodes.Logical.Package node, bool callVirtualBase = true) { }

        /// <summary>
        /// Visitor which is called at the end of the Columbus.Lim.Asg.Nodes.Logical.Package node visiting.
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public virtual void visitEnd(Columbus.Lim.Asg.Nodes.Logical.Package node, bool callVirtualBase = true) { }

        /// <summary>
        /// Visitor which is called at the beginning of the Columbus.Lim.Asg.Nodes.Logical.Parameter node visiting.
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public virtual void visit(Columbus.Lim.Asg.Nodes.Logical.Parameter node, bool callVirtualBase = true) { }

        /// <summary>
        /// Visitor which is called at the end of the Columbus.Lim.Asg.Nodes.Logical.Parameter node visiting.
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public virtual void visitEnd(Columbus.Lim.Asg.Nodes.Logical.Parameter node, bool callVirtualBase = true) { }

        /// <summary>
        /// Visitor which is called at the beginning of the Columbus.Lim.Asg.Nodes.Physical.File node visiting.
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public virtual void visit(Columbus.Lim.Asg.Nodes.Physical.File node, bool callVirtualBase = true) { }

        /// <summary>
        /// Visitor which is called at the end of the Columbus.Lim.Asg.Nodes.Physical.File node visiting.
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public virtual void visitEnd(Columbus.Lim.Asg.Nodes.Physical.File node, bool callVirtualBase = true) { }

        /// <summary>
        /// Visitor which is called at the beginning of the Columbus.Lim.Asg.Nodes.Physical.FileSystem node visiting.
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public virtual void visit(Columbus.Lim.Asg.Nodes.Physical.FileSystem node, bool callVirtualBase = true) { }

        /// <summary>
        /// Visitor which is called at the end of the Columbus.Lim.Asg.Nodes.Physical.FileSystem node visiting.
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public virtual void visitEnd(Columbus.Lim.Asg.Nodes.Physical.FileSystem node, bool callVirtualBase = true) { }

        /// <summary>
        /// Visitor which is called at the beginning of the Columbus.Lim.Asg.Nodes.Physical.Folder node visiting.
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public virtual void visit(Columbus.Lim.Asg.Nodes.Physical.Folder node, bool callVirtualBase = true) { }

        /// <summary>
        /// Visitor which is called at the end of the Columbus.Lim.Asg.Nodes.Physical.Folder node visiting.
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public virtual void visitEnd(Columbus.Lim.Asg.Nodes.Physical.Folder node, bool callVirtualBase = true) { }

        /// <summary>
        /// Visitor which is called at the beginning of the Columbus.Lim.Asg.Nodes.Type.SimpleType node visiting.
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public virtual void visit(Columbus.Lim.Asg.Nodes.Type.SimpleType node, bool callVirtualBase = true) { }

        /// <summary>
        /// Visitor which is called at the end of the Columbus.Lim.Asg.Nodes.Type.SimpleType node visiting.
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public virtual void visitEnd(Columbus.Lim.Asg.Nodes.Type.SimpleType node, bool callVirtualBase = true) { }

        /// <summary>
        /// Visitor which is called at the beginning of the Columbus.Lim.Asg.Nodes.Type.Type node visiting.
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public virtual void visit(Columbus.Lim.Asg.Nodes.Type.Type node, bool callVirtualBase = true) { }

        /// <summary>
        /// Visitor which is called at the end of the Columbus.Lim.Asg.Nodes.Type.Type node visiting.
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public virtual void visitEnd(Columbus.Lim.Asg.Nodes.Type.Type node, bool callVirtualBase = true) { }

        /// <summary>
        /// Visitor which is called at the beginning of the Columbus.Lim.Asg.Nodes.Type.TypeFormerArray node visiting.
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public virtual void visit(Columbus.Lim.Asg.Nodes.Type.TypeFormerArray node, bool callVirtualBase = true) { }

        /// <summary>
        /// Visitor which is called at the end of the Columbus.Lim.Asg.Nodes.Type.TypeFormerArray node visiting.
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public virtual void visitEnd(Columbus.Lim.Asg.Nodes.Type.TypeFormerArray node, bool callVirtualBase = true) { }

        /// <summary>
        /// Visitor which is called at the beginning of the Columbus.Lim.Asg.Nodes.Type.TypeFormerMethod node visiting.
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public virtual void visit(Columbus.Lim.Asg.Nodes.Type.TypeFormerMethod node, bool callVirtualBase = true) { }

        /// <summary>
        /// Visitor which is called at the end of the Columbus.Lim.Asg.Nodes.Type.TypeFormerMethod node visiting.
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public virtual void visitEnd(Columbus.Lim.Asg.Nodes.Type.TypeFormerMethod node, bool callVirtualBase = true) { }

        /// <summary>
        /// Visitor which is called at the beginning of the Columbus.Lim.Asg.Nodes.Type.TypeFormerNonType node visiting.
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public virtual void visit(Columbus.Lim.Asg.Nodes.Type.TypeFormerNonType node, bool callVirtualBase = true) { }

        /// <summary>
        /// Visitor which is called at the end of the Columbus.Lim.Asg.Nodes.Type.TypeFormerNonType node visiting.
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public virtual void visitEnd(Columbus.Lim.Asg.Nodes.Type.TypeFormerNonType node, bool callVirtualBase = true) { }

        /// <summary>
        /// Visitor which is called at the beginning of the Columbus.Lim.Asg.Nodes.Type.TypeFormerPointer node visiting.
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public virtual void visit(Columbus.Lim.Asg.Nodes.Type.TypeFormerPointer node, bool callVirtualBase = true) { }

        /// <summary>
        /// Visitor which is called at the end of the Columbus.Lim.Asg.Nodes.Type.TypeFormerPointer node visiting.
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public virtual void visitEnd(Columbus.Lim.Asg.Nodes.Type.TypeFormerPointer node, bool callVirtualBase = true) { }

        /// <summary>
        /// Visitor which is called at the beginning of the Columbus.Lim.Asg.Nodes.Type.TypeFormerType node visiting.
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public virtual void visit(Columbus.Lim.Asg.Nodes.Type.TypeFormerType node, bool callVirtualBase = true) { }

        /// <summary>
        /// Visitor which is called at the end of the Columbus.Lim.Asg.Nodes.Type.TypeFormerType node visiting.
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public virtual void visitEnd(Columbus.Lim.Asg.Nodes.Type.TypeFormerType node, bool callVirtualBase = true) { }

        /// <summary>
        /// Edge visitor for contains edge which.
        /// </summary>
        /// <param name="begin">[in] The id of the node the edge starts from.</param>
        /// <param name="end">[in] The id of the node the edge points to.</param>
        public virtual void visitComponent_Contains(uint begin, uint end) { }

        /// <summary>
        /// Edge end visitor for contains edge which is called after the visit pair of this edge is called.
        /// </summary>
        /// <param name="begin">[in] The id of the node the edge starts from.</param>
        /// <param name="end">[in] The id of the node the edge points to.</param>
        public virtual void visitEndComponent_Contains(uint begin, uint end) { }

        /// <summary>
        /// Edge visitor for hasFiles edge which.
        /// </summary>
        /// <param name="begin">[in] The id of the node the edge starts from.</param>
        /// <param name="end">[in] The id of the node the edge points to.</param>
        public virtual void visitComponent_HasFiles(uint begin, uint end) { }

        /// <summary>
        /// Edge end visitor for hasFiles edge which is called after the visit pair of this edge is called.
        /// </summary>
        /// <param name="begin">[in] The id of the node the edge starts from.</param>
        /// <param name="end">[in] The id of the node the edge points to.</param>
        public virtual void visitEndComponent_HasFiles(uint begin, uint end) { }

        /// <summary>
        /// Edge visitor for calls edge which.
        /// </summary>
        /// <param name="begin">[in] The id of the node the edge starts from.</param>
        /// <param name="end">[in] The id of the node the edge points to.</param>
        public virtual void visitControlFlowBlock_Calls(uint begin, uint end) { }

        /// <summary>
        /// Edge end visitor for calls edge which is called after the visit pair of this edge is called.
        /// </summary>
        /// <param name="begin">[in] The id of the node the edge starts from.</param>
        /// <param name="end">[in] The id of the node the edge points to.</param>
        public virtual void visitEndControlFlowBlock_Calls(uint begin, uint end) { }

        /// <summary>
        /// Edge visitor for pred edge which.
        /// </summary>
        /// <param name="begin">[in] The id of the node the edge starts from.</param>
        /// <param name="end">[in] The id of the node the edge points to.</param>
        public virtual void visitControlFlowBlock_Pred(uint begin, uint end) { }

        /// <summary>
        /// Edge end visitor for pred edge which is called after the visit pair of this edge is called.
        /// </summary>
        /// <param name="begin">[in] The id of the node the edge starts from.</param>
        /// <param name="end">[in] The id of the node the edge points to.</param>
        public virtual void visitEndControlFlowBlock_Pred(uint begin, uint end) { }

        /// <summary>
        /// Edge visitor for dependsOn edge which.
        /// </summary>
        /// <param name="begin">[in] The id of the node the edge starts from.</param>
        /// <param name="end">[in] The id of the node the edge points to.</param>
        /// <param name="acString">[in] The value of the association class.</param>
        public virtual void visitNamed_DependsOn(uint begin, uint end, string acString) { }

        /// <summary>
        /// Edge end visitor for dependsOn edge which is called after the visit pair of this edge is called.
        /// </summary>
        /// <param name="begin">[in] The id of the node the edge starts from.</param>
        /// <param name="end">[in] The id of the node the edge points to.</param>
        /// <param name="acString">[in] The value of the association class.</param>
        public virtual void visitEndNamed_DependsOn(uint begin, uint end, string acString) { }

        /// <summary>
        /// Edge visitor for calls edge which.
        /// </summary>
        /// <param name="begin">[in] The id of the node the edge starts from.</param>
        /// <param name="end">[in] The id of the node the edge points to.</param>
        public virtual void visitAttribute_Calls(uint begin, uint end) { }

        /// <summary>
        /// Edge end visitor for calls edge which is called after the visit pair of this edge is called.
        /// </summary>
        /// <param name="begin">[in] The id of the node the edge starts from.</param>
        /// <param name="end">[in] The id of the node the edge points to.</param>
        public virtual void visitEndAttribute_Calls(uint begin, uint end) { }

        /// <summary>
        /// Edge visitor for hasType edge which.
        /// </summary>
        /// <param name="begin">[in] The id of the node the edge starts from.</param>
        /// <param name="end">[in] The id of the node the edge points to.</param>
        public virtual void visitAttribute_HasType(uint begin, uint end) { }

        /// <summary>
        /// Edge end visitor for hasType edge which is called after the visit pair of this edge is called.
        /// </summary>
        /// <param name="begin">[in] The id of the node the edge starts from.</param>
        /// <param name="end">[in] The id of the node the edge points to.</param>
        public virtual void visitEndAttribute_HasType(uint begin, uint end) { }

        /// <summary>
        /// Edge visitor for attribute edge which.
        /// </summary>
        /// <param name="begin">[in] The id of the node the edge starts from.</param>
        /// <param name="end">[in] The id of the node the edge points to.</param>
        public virtual void visitAttributeAccess_Attribute(uint begin, uint end) { }

        /// <summary>
        /// Edge end visitor for attribute edge which is called after the visit pair of this edge is called.
        /// </summary>
        /// <param name="begin">[in] The id of the node the edge starts from.</param>
        /// <param name="end">[in] The id of the node the edge points to.</param>
        public virtual void visitEndAttributeAccess_Attribute(uint begin, uint end) { }

        /// <summary>
        /// Edge visitor for grantsFriendship edge which.
        /// </summary>
        /// <param name="begin">[in] The id of the node the edge starts from.</param>
        /// <param name="end">[in] The id of the node the edge points to.</param>
        public virtual void visitClass_GrantsFriendship(uint begin, uint end) { }

        /// <summary>
        /// Edge end visitor for grantsFriendship edge which is called after the visit pair of this edge is called.
        /// </summary>
        /// <param name="begin">[in] The id of the node the edge starts from.</param>
        /// <param name="end">[in] The id of the node the edge points to.</param>
        public virtual void visitEndClass_GrantsFriendship(uint begin, uint end) { }

        /// <summary>
        /// Edge visitor for isSubclass edge which.
        /// </summary>
        /// <param name="begin">[in] The id of the node the edge starts from.</param>
        /// <param name="end">[in] The id of the node the edge points to.</param>
        public virtual void visitClass_IsSubclass(uint begin, uint end) { }

        /// <summary>
        /// Edge end visitor for isSubclass edge which is called after the visit pair of this edge is called.
        /// </summary>
        /// <param name="begin">[in] The id of the node the edge starts from.</param>
        /// <param name="end">[in] The id of the node the edge points to.</param>
        public virtual void visitEndClass_IsSubclass(uint begin, uint end) { }

        /// <summary>
        /// Edge visitor for hasGenericParameter edge which is called when the subtree of this edge is started.
        /// </summary>
        /// <param name="begin">[in] The id of the node the edge starts from.</param>
        /// <param name="end">[in] The id of the node the edge points to.</param>
        public virtual void visitClassGeneric_HasGenericParameter(uint begin, uint end) { }

        /// <summary>
        /// Edge end visitor for hasGenericParameter edge which is called after the subtree of this edge is finished.
        /// </summary>
        /// <param name="begin">[in] The id of the node the edge starts from.</param>
        /// <param name="end">[in] The id of the node the edge points to.</param>
        public virtual void visitEndClassGeneric_HasGenericParameter(uint begin, uint end) { }

        /// <summary>
        /// Edge visitor for hasArguments edge which.
        /// </summary>
        /// <param name="begin">[in] The id of the node the edge starts from.</param>
        /// <param name="end">[in] The id of the node the edge points to.</param>
        /// <param name="acTypeArgumentConstraintKind">[in] The value of the association class.</param>
        public virtual void visitClassGenericInstance_HasArguments(uint begin, uint end, Types.TypeArgumentConstraintKind acTypeArgumentConstraintKind) { }

        /// <summary>
        /// Edge end visitor for hasArguments edge which is called after the visit pair of this edge is called.
        /// </summary>
        /// <param name="begin">[in] The id of the node the edge starts from.</param>
        /// <param name="end">[in] The id of the node the edge points to.</param>
        /// <param name="acTypeArgumentConstraintKind">[in] The value of the association class.</param>
        public virtual void visitEndClassGenericInstance_HasArguments(uint begin, uint end, Types.TypeArgumentConstraintKind acTypeArgumentConstraintKind) { }

        /// <summary>
        /// Edge visitor for hasArguments edge which.
        /// </summary>
        /// <param name="begin">[in] The id of the node the edge starts from.</param>
        /// <param name="end">[in] The id of the node the edge points to.</param>
        /// <param name="acTypeArgumentConstraintKind">[in] The value of the association class.</param>
        public virtual void visitClassGenericSpec_HasArguments(uint begin, uint end, Types.TypeArgumentConstraintKind acTypeArgumentConstraintKind) { }

        /// <summary>
        /// Edge end visitor for hasArguments edge which is called after the visit pair of this edge is called.
        /// </summary>
        /// <param name="begin">[in] The id of the node the edge starts from.</param>
        /// <param name="end">[in] The id of the node the edge points to.</param>
        /// <param name="acTypeArgumentConstraintKind">[in] The value of the association class.</param>
        public virtual void visitEndClassGenericSpec_HasArguments(uint begin, uint end, Types.TypeArgumentConstraintKind acTypeArgumentConstraintKind) { }

        /// <summary>
        /// Edge visitor for specialize edge which.
        /// </summary>
        /// <param name="begin">[in] The id of the node the edge starts from.</param>
        /// <param name="end">[in] The id of the node the edge points to.</param>
        public virtual void visitClassGenericSpec_Specialize(uint begin, uint end) { }

        /// <summary>
        /// Edge end visitor for specialize edge which is called after the visit pair of this edge is called.
        /// </summary>
        /// <param name="begin">[in] The id of the node the edge starts from.</param>
        /// <param name="end">[in] The id of the node the edge points to.</param>
        public virtual void visitEndClassGenericSpec_Specialize(uint begin, uint end) { }

        /// <summary>
        /// Edge visitor for friend edge which.
        /// </summary>
        /// <param name="begin">[in] The id of the node the edge starts from.</param>
        /// <param name="end">[in] The id of the node the edge points to.</param>
        public virtual void visitFriendship_Friend(uint begin, uint end) { }

        /// <summary>
        /// Edge end visitor for friend edge which is called after the visit pair of this edge is called.
        /// </summary>
        /// <param name="begin">[in] The id of the node the edge starts from.</param>
        /// <param name="end">[in] The id of the node the edge points to.</param>
        public virtual void visitEndFriendship_Friend(uint begin, uint end) { }

        /// <summary>
        /// Edge visitor for hasParameterConstraint edge which.
        /// </summary>
        /// <param name="begin">[in] The id of the node the edge starts from.</param>
        /// <param name="end">[in] The id of the node the edge points to.</param>
        public virtual void visitGenericParameter_HasParameterConstraint(uint begin, uint end) { }

        /// <summary>
        /// Edge end visitor for hasParameterConstraint edge which is called after the visit pair of this edge is called.
        /// </summary>
        /// <param name="begin">[in] The id of the node the edge starts from.</param>
        /// <param name="end">[in] The id of the node the edge points to.</param>
        public virtual void visitEndGenericParameter_HasParameterConstraint(uint begin, uint end) { }

        /// <summary>
        /// Edge visitor for aggregated edge which.
        /// </summary>
        /// <param name="begin">[in] The id of the node the edge starts from.</param>
        /// <param name="end">[in] The id of the node the edge points to.</param>
        public virtual void visitMember_Aggregated(uint begin, uint end) { }

        /// <summary>
        /// Edge end visitor for aggregated edge which is called after the visit pair of this edge is called.
        /// </summary>
        /// <param name="begin">[in] The id of the node the edge starts from.</param>
        /// <param name="end">[in] The id of the node the edge points to.</param>
        public virtual void visitEndMember_Aggregated(uint begin, uint end) { }

        /// <summary>
        /// Edge visitor for belongsTo edge which.
        /// </summary>
        /// <param name="begin">[in] The id of the node the edge starts from.</param>
        /// <param name="end">[in] The id of the node the edge points to.</param>
        public virtual void visitMember_BelongsTo(uint begin, uint end) { }

        /// <summary>
        /// Edge end visitor for belongsTo edge which is called after the visit pair of this edge is called.
        /// </summary>
        /// <param name="begin">[in] The id of the node the edge starts from.</param>
        /// <param name="end">[in] The id of the node the edge points to.</param>
        public virtual void visitEndMember_BelongsTo(uint begin, uint end) { }

        /// <summary>
        /// Edge visitor for compilationUnit edge which.
        /// </summary>
        /// <param name="begin">[in] The id of the node the edge starts from.</param>
        /// <param name="end">[in] The id of the node the edge points to.</param>
        public virtual void visitMember_CompilationUnit(uint begin, uint end) { }

        /// <summary>
        /// Edge end visitor for compilationUnit edge which is called after the visit pair of this edge is called.
        /// </summary>
        /// <param name="begin">[in] The id of the node the edge starts from.</param>
        /// <param name="end">[in] The id of the node the edge points to.</param>
        public virtual void visitEndMember_CompilationUnit(uint begin, uint end) { }

        /// <summary>
        /// Edge visitor for declares edge which.
        /// </summary>
        /// <param name="begin">[in] The id of the node the edge starts from.</param>
        /// <param name="end">[in] The id of the node the edge points to.</param>
        public virtual void visitMember_Declares(uint begin, uint end) { }

        /// <summary>
        /// Edge end visitor for declares edge which is called after the visit pair of this edge is called.
        /// </summary>
        /// <param name="begin">[in] The id of the node the edge starts from.</param>
        /// <param name="end">[in] The id of the node the edge points to.</param>
        public virtual void visitEndMember_Declares(uint begin, uint end) { }

        /// <summary>
        /// Edge visitor for hasComment edge which.
        /// </summary>
        /// <param name="begin">[in] The id of the node the edge starts from.</param>
        /// <param name="end">[in] The id of the node the edge points to.</param>
        public virtual void visitMember_HasComment(uint begin, uint end) { }

        /// <summary>
        /// Edge end visitor for hasComment edge which is called after the visit pair of this edge is called.
        /// </summary>
        /// <param name="begin">[in] The id of the node the edge starts from.</param>
        /// <param name="end">[in] The id of the node the edge points to.</param>
        public virtual void visitEndMember_HasComment(uint begin, uint end) { }

        /// <summary>
        /// Edge visitor for instance edge which.
        /// </summary>
        /// <param name="begin">[in] The id of the node the edge starts from.</param>
        /// <param name="end">[in] The id of the node the edge points to.</param>
        public virtual void visitMember_Instance(uint begin, uint end) { }

        /// <summary>
        /// Edge end visitor for instance edge which is called after the visit pair of this edge is called.
        /// </summary>
        /// <param name="begin">[in] The id of the node the edge starts from.</param>
        /// <param name="end">[in] The id of the node the edge points to.</param>
        public virtual void visitEndMember_Instance(uint begin, uint end) { }

        /// <summary>
        /// Edge visitor for isContainedIn edge which.
        /// </summary>
        /// <param name="begin">[in] The id of the node the edge starts from.</param>
        /// <param name="end">[in] The id of the node the edge points to.</param>
        /// <param name="acSourcePosition">[in] The value of the association class.</param>
        public virtual void visitMember_IsContainedIn(uint begin, uint end, SourcePosition acSourcePosition) { }

        /// <summary>
        /// Edge end visitor for isContainedIn edge which is called after the visit pair of this edge is called.
        /// </summary>
        /// <param name="begin">[in] The id of the node the edge starts from.</param>
        /// <param name="end">[in] The id of the node the edge points to.</param>
        /// <param name="acSourcePosition">[in] The value of the association class.</param>
        public virtual void visitEndMember_IsContainedIn(uint begin, uint end, SourcePosition acSourcePosition) { }

        /// <summary>
        /// Edge visitor for languageVariant edge which.
        /// </summary>
        /// <param name="begin">[in] The id of the node the edge starts from.</param>
        /// <param name="end">[in] The id of the node the edge points to.</param>
        public virtual void visitMember_LanguageVariant(uint begin, uint end) { }

        /// <summary>
        /// Edge end visitor for languageVariant edge which is called after the visit pair of this edge is called.
        /// </summary>
        /// <param name="begin">[in] The id of the node the edge starts from.</param>
        /// <param name="end">[in] The id of the node the edge points to.</param>
        public virtual void visitEndMember_LanguageVariant(uint begin, uint end) { }

        /// <summary>
        /// Edge visitor for uses edge which.
        /// </summary>
        /// <param name="begin">[in] The id of the node the edge starts from.</param>
        /// <param name="end">[in] The id of the node the edge points to.</param>
        public virtual void visitMember_Uses(uint begin, uint end) { }

        /// <summary>
        /// Edge end visitor for uses edge which is called after the visit pair of this edge is called.
        /// </summary>
        /// <param name="begin">[in] The id of the node the edge starts from.</param>
        /// <param name="end">[in] The id of the node the edge points to.</param>
        public virtual void visitEndMember_Uses(uint begin, uint end) { }

        /// <summary>
        /// Edge visitor for variant edge which.
        /// </summary>
        /// <param name="begin">[in] The id of the node the edge starts from.</param>
        /// <param name="end">[in] The id of the node the edge points to.</param>
        public virtual void visitMember_Variant(uint begin, uint end) { }

        /// <summary>
        /// Edge end visitor for variant edge which is called after the visit pair of this edge is called.
        /// </summary>
        /// <param name="begin">[in] The id of the node the edge starts from.</param>
        /// <param name="end">[in] The id of the node the edge points to.</param>
        public virtual void visitEndMember_Variant(uint begin, uint end) { }

        /// <summary>
        /// Edge visitor for accessesAttribute edge which.
        /// </summary>
        /// <param name="begin">[in] The id of the node the edge starts from.</param>
        /// <param name="end">[in] The id of the node the edge points to.</param>
        public virtual void visitMethod_AccessesAttribute(uint begin, uint end) { }

        /// <summary>
        /// Edge end visitor for accessesAttribute edge which is called after the visit pair of this edge is called.
        /// </summary>
        /// <param name="begin">[in] The id of the node the edge starts from.</param>
        /// <param name="end">[in] The id of the node the edge points to.</param>
        public virtual void visitEndMethod_AccessesAttribute(uint begin, uint end) { }

        /// <summary>
        /// Edge visitor for calls edge which.
        /// </summary>
        /// <param name="begin">[in] The id of the node the edge starts from.</param>
        /// <param name="end">[in] The id of the node the edge points to.</param>
        public virtual void visitMethod_Calls(uint begin, uint end) { }

        /// <summary>
        /// Edge end visitor for calls edge which is called after the visit pair of this edge is called.
        /// </summary>
        /// <param name="begin">[in] The id of the node the edge starts from.</param>
        /// <param name="end">[in] The id of the node the edge points to.</param>
        public virtual void visitEndMethod_Calls(uint begin, uint end) { }

        /// <summary>
        /// Edge visitor for canThrow edge which.
        /// </summary>
        /// <param name="begin">[in] The id of the node the edge starts from.</param>
        /// <param name="end">[in] The id of the node the edge points to.</param>
        public virtual void visitMethod_CanThrow(uint begin, uint end) { }

        /// <summary>
        /// Edge end visitor for canThrow edge which is called after the visit pair of this edge is called.
        /// </summary>
        /// <param name="begin">[in] The id of the node the edge starts from.</param>
        /// <param name="end">[in] The id of the node the edge points to.</param>
        public virtual void visitEndMethod_CanThrow(uint begin, uint end) { }

        /// <summary>
        /// Edge visitor for hasControlFlowBlock edge which is called when the subtree of this edge is started.
        /// </summary>
        /// <param name="begin">[in] The id of the node the edge starts from.</param>
        /// <param name="end">[in] The id of the node the edge points to.</param>
        public virtual void visitMethod_HasControlFlowBlock(uint begin, uint end) { }

        /// <summary>
        /// Edge end visitor for hasControlFlowBlock edge which is called after the subtree of this edge is finished.
        /// </summary>
        /// <param name="begin">[in] The id of the node the edge starts from.</param>
        /// <param name="end">[in] The id of the node the edge points to.</param>
        public virtual void visitEndMethod_HasControlFlowBlock(uint begin, uint end) { }

        /// <summary>
        /// Edge visitor for hasParameter edge which is called when the subtree of this edge is started.
        /// </summary>
        /// <param name="begin">[in] The id of the node the edge starts from.</param>
        /// <param name="end">[in] The id of the node the edge points to.</param>
        public virtual void visitMethod_HasParameter(uint begin, uint end) { }

        /// <summary>
        /// Edge end visitor for hasParameter edge which is called after the subtree of this edge is finished.
        /// </summary>
        /// <param name="begin">[in] The id of the node the edge starts from.</param>
        /// <param name="end">[in] The id of the node the edge points to.</param>
        public virtual void visitEndMethod_HasParameter(uint begin, uint end) { }

        /// <summary>
        /// Edge visitor for instantiates edge which.
        /// </summary>
        /// <param name="begin">[in] The id of the node the edge starts from.</param>
        /// <param name="end">[in] The id of the node the edge points to.</param>
        public virtual void visitMethod_Instantiates(uint begin, uint end) { }

        /// <summary>
        /// Edge end visitor for instantiates edge which is called after the visit pair of this edge is called.
        /// </summary>
        /// <param name="begin">[in] The id of the node the edge starts from.</param>
        /// <param name="end">[in] The id of the node the edge points to.</param>
        public virtual void visitEndMethod_Instantiates(uint begin, uint end) { }

        /// <summary>
        /// Edge visitor for returns edge which.
        /// </summary>
        /// <param name="begin">[in] The id of the node the edge starts from.</param>
        /// <param name="end">[in] The id of the node the edge points to.</param>
        public virtual void visitMethod_Returns(uint begin, uint end) { }

        /// <summary>
        /// Edge end visitor for returns edge which is called after the visit pair of this edge is called.
        /// </summary>
        /// <param name="begin">[in] The id of the node the edge starts from.</param>
        /// <param name="end">[in] The id of the node the edge points to.</param>
        public virtual void visitEndMethod_Returns(uint begin, uint end) { }

        /// <summary>
        /// Edge visitor for throws edge which.
        /// </summary>
        /// <param name="begin">[in] The id of the node the edge starts from.</param>
        /// <param name="end">[in] The id of the node the edge points to.</param>
        public virtual void visitMethod_Throws(uint begin, uint end) { }

        /// <summary>
        /// Edge end visitor for throws edge which is called after the visit pair of this edge is called.
        /// </summary>
        /// <param name="begin">[in] The id of the node the edge starts from.</param>
        /// <param name="end">[in] The id of the node the edge points to.</param>
        public virtual void visitEndMethod_Throws(uint begin, uint end) { }

        /// <summary>
        /// Edge visitor for method edge which.
        /// </summary>
        /// <param name="begin">[in] The id of the node the edge starts from.</param>
        /// <param name="end">[in] The id of the node the edge points to.</param>
        public virtual void visitMethodCall_Method(uint begin, uint end) { }

        /// <summary>
        /// Edge end visitor for method edge which is called after the visit pair of this edge is called.
        /// </summary>
        /// <param name="begin">[in] The id of the node the edge starts from.</param>
        /// <param name="end">[in] The id of the node the edge points to.</param>
        public virtual void visitEndMethodCall_Method(uint begin, uint end) { }

        /// <summary>
        /// Edge visitor for hasGenericParameter edge which is called when the subtree of this edge is started.
        /// </summary>
        /// <param name="begin">[in] The id of the node the edge starts from.</param>
        /// <param name="end">[in] The id of the node the edge points to.</param>
        public virtual void visitMethodGeneric_HasGenericParameter(uint begin, uint end) { }

        /// <summary>
        /// Edge end visitor for hasGenericParameter edge which is called after the subtree of this edge is finished.
        /// </summary>
        /// <param name="begin">[in] The id of the node the edge starts from.</param>
        /// <param name="end">[in] The id of the node the edge points to.</param>
        public virtual void visitEndMethodGeneric_HasGenericParameter(uint begin, uint end) { }

        /// <summary>
        /// Edge visitor for hasArguments edge which.
        /// </summary>
        /// <param name="begin">[in] The id of the node the edge starts from.</param>
        /// <param name="end">[in] The id of the node the edge points to.</param>
        /// <param name="acTypeArgumentConstraintKind">[in] The value of the association class.</param>
        public virtual void visitMethodGenericInstance_HasArguments(uint begin, uint end, Types.TypeArgumentConstraintKind acTypeArgumentConstraintKind) { }

        /// <summary>
        /// Edge end visitor for hasArguments edge which is called after the visit pair of this edge is called.
        /// </summary>
        /// <param name="begin">[in] The id of the node the edge starts from.</param>
        /// <param name="end">[in] The id of the node the edge points to.</param>
        /// <param name="acTypeArgumentConstraintKind">[in] The value of the association class.</param>
        public virtual void visitEndMethodGenericInstance_HasArguments(uint begin, uint end, Types.TypeArgumentConstraintKind acTypeArgumentConstraintKind) { }

        /// <summary>
        /// Edge visitor for hasArguments edge which.
        /// </summary>
        /// <param name="begin">[in] The id of the node the edge starts from.</param>
        /// <param name="end">[in] The id of the node the edge points to.</param>
        /// <param name="acTypeArgumentConstraintKind">[in] The value of the association class.</param>
        public virtual void visitMethodGenericSpec_HasArguments(uint begin, uint end, Types.TypeArgumentConstraintKind acTypeArgumentConstraintKind) { }

        /// <summary>
        /// Edge end visitor for hasArguments edge which is called after the visit pair of this edge is called.
        /// </summary>
        /// <param name="begin">[in] The id of the node the edge starts from.</param>
        /// <param name="end">[in] The id of the node the edge points to.</param>
        /// <param name="acTypeArgumentConstraintKind">[in] The value of the association class.</param>
        public virtual void visitEndMethodGenericSpec_HasArguments(uint begin, uint end, Types.TypeArgumentConstraintKind acTypeArgumentConstraintKind) { }

        /// <summary>
        /// Edge visitor for specialize edge which.
        /// </summary>
        /// <param name="begin">[in] The id of the node the edge starts from.</param>
        /// <param name="end">[in] The id of the node the edge points to.</param>
        public virtual void visitMethodGenericSpec_Specialize(uint begin, uint end) { }

        /// <summary>
        /// Edge end visitor for specialize edge which is called after the visit pair of this edge is called.
        /// </summary>
        /// <param name="begin">[in] The id of the node the edge starts from.</param>
        /// <param name="end">[in] The id of the node the edge points to.</param>
        public virtual void visitEndMethodGenericSpec_Specialize(uint begin, uint end) { }

        /// <summary>
        /// Edge visitor for hasType edge which.
        /// </summary>
        /// <param name="begin">[in] The id of the node the edge starts from.</param>
        /// <param name="end">[in] The id of the node the edge points to.</param>
        public virtual void visitParameter_HasType(uint begin, uint end) { }

        /// <summary>
        /// Edge end visitor for hasType edge which is called after the visit pair of this edge is called.
        /// </summary>
        /// <param name="begin">[in] The id of the node the edge starts from.</param>
        /// <param name="end">[in] The id of the node the edge points to.</param>
        public virtual void visitEndParameter_HasType(uint begin, uint end) { }

        /// <summary>
        /// Edge visitor for hasMember edge which.
        /// </summary>
        /// <param name="begin">[in] The id of the node the edge starts from.</param>
        /// <param name="end">[in] The id of the node the edge points to.</param>
        public virtual void visitScope_HasMember(uint begin, uint end) { }

        /// <summary>
        /// Edge end visitor for hasMember edge which is called after the visit pair of this edge is called.
        /// </summary>
        /// <param name="begin">[in] The id of the node the edge starts from.</param>
        /// <param name="end">[in] The id of the node the edge points to.</param>
        public virtual void visitEndScope_HasMember(uint begin, uint end) { }

        /// <summary>
        /// Edge visitor for hasComment edge which.
        /// </summary>
        /// <param name="begin">[in] The id of the node the edge starts from.</param>
        /// <param name="end">[in] The id of the node the edge points to.</param>
        public virtual void visitFile_HasComment(uint begin, uint end) { }

        /// <summary>
        /// Edge end visitor for hasComment edge which is called after the visit pair of this edge is called.
        /// </summary>
        /// <param name="begin">[in] The id of the node the edge starts from.</param>
        /// <param name="end">[in] The id of the node the edge points to.</param>
        public virtual void visitEndFile_HasComment(uint begin, uint end) { }

        /// <summary>
        /// Edge visitor for includes edge which.
        /// </summary>
        /// <param name="begin">[in] The id of the node the edge starts from.</param>
        /// <param name="end">[in] The id of the node the edge points to.</param>
        public virtual void visitFile_Includes(uint begin, uint end) { }

        /// <summary>
        /// Edge end visitor for includes edge which is called after the visit pair of this edge is called.
        /// </summary>
        /// <param name="begin">[in] The id of the node the edge starts from.</param>
        /// <param name="end">[in] The id of the node the edge points to.</param>
        public virtual void visitEndFile_Includes(uint begin, uint end) { }

        /// <summary>
        /// Edge visitor for hasFSEntry edge which is called when the subtree of this edge is started.
        /// </summary>
        /// <param name="begin">[in] The id of the node the edge starts from.</param>
        /// <param name="end">[in] The id of the node the edge points to.</param>
        public virtual void visitFileSystem_HasFSEntry(uint begin, uint end) { }

        /// <summary>
        /// Edge end visitor for hasFSEntry edge which is called after the subtree of this edge is finished.
        /// </summary>
        /// <param name="begin">[in] The id of the node the edge starts from.</param>
        /// <param name="end">[in] The id of the node the edge points to.</param>
        public virtual void visitEndFileSystem_HasFSEntry(uint begin, uint end) { }

        /// <summary>
        /// Edge visitor for contains edge which is called when the subtree of this edge is started.
        /// </summary>
        /// <param name="begin">[in] The id of the node the edge starts from.</param>
        /// <param name="end">[in] The id of the node the edge points to.</param>
        public virtual void visitFolder_Contains(uint begin, uint end) { }

        /// <summary>
        /// Edge end visitor for contains edge which is called after the subtree of this edge is finished.
        /// </summary>
        /// <param name="begin">[in] The id of the node the edge starts from.</param>
        /// <param name="end">[in] The id of the node the edge points to.</param>
        public virtual void visitEndFolder_Contains(uint begin, uint end) { }

        /// <summary>
        /// Edge visitor for hasTypeFormer edge which.
        /// </summary>
        /// <param name="begin">[in] The id of the node the edge starts from.</param>
        /// <param name="end">[in] The id of the node the edge points to.</param>
        public virtual void visitType_HasTypeFormer(uint begin, uint end) { }

        /// <summary>
        /// Edge end visitor for hasTypeFormer edge which is called after the visit pair of this edge is called.
        /// </summary>
        /// <param name="begin">[in] The id of the node the edge starts from.</param>
        /// <param name="end">[in] The id of the node the edge points to.</param>
        public virtual void visitEndType_HasTypeFormer(uint begin, uint end) { }

        /// <summary>
        /// Edge visitor for hasParameterType edge which.
        /// </summary>
        /// <param name="begin">[in] The id of the node the edge starts from.</param>
        /// <param name="end">[in] The id of the node the edge points to.</param>
        /// <param name="acParameterKind">[in] The value of the association class.</param>
        public virtual void visitTypeFormerMethod_HasParameterType(uint begin, uint end, Types.ParameterKind acParameterKind) { }

        /// <summary>
        /// Edge end visitor for hasParameterType edge which is called after the visit pair of this edge is called.
        /// </summary>
        /// <param name="begin">[in] The id of the node the edge starts from.</param>
        /// <param name="end">[in] The id of the node the edge points to.</param>
        /// <param name="acParameterKind">[in] The value of the association class.</param>
        public virtual void visitEndTypeFormerMethod_HasParameterType(uint begin, uint end, Types.ParameterKind acParameterKind) { }

        /// <summary>
        /// Edge visitor for hasReturnType edge which.
        /// </summary>
        /// <param name="begin">[in] The id of the node the edge starts from.</param>
        /// <param name="end">[in] The id of the node the edge points to.</param>
        public virtual void visitTypeFormerMethod_HasReturnType(uint begin, uint end) { }

        /// <summary>
        /// Edge end visitor for hasReturnType edge which is called after the visit pair of this edge is called.
        /// </summary>
        /// <param name="begin">[in] The id of the node the edge starts from.</param>
        /// <param name="end">[in] The id of the node the edge points to.</param>
        public virtual void visitEndTypeFormerMethod_HasReturnType(uint begin, uint end) { }

        /// <summary>
        /// Edge visitor for refersTo edge which.
        /// </summary>
        /// <param name="begin">[in] The id of the node the edge starts from.</param>
        /// <param name="end">[in] The id of the node the edge points to.</param>
        public virtual void visitTypeFormerType_RefersTo(uint begin, uint end) { }

        /// <summary>
        /// Edge end visitor for refersTo edge which is called after the visit pair of this edge is called.
        /// </summary>
        /// <param name="begin">[in] The id of the node the edge starts from.</param>
        /// <param name="end">[in] The id of the node the edge points to.</param>
        public virtual void visitEndTypeFormerType_RefersTo(uint begin, uint end) { }

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
