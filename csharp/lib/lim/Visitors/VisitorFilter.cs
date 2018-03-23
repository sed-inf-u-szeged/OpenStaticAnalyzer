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
    /// VisitorFilter class filters out nodes from the ASG.
    /// </summary>
#if (LIM_INTERNAL)
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
        public override void visitEnd(Columbus.Lim.Asg.Nodes.Base.Comment node, bool callVirtualBase) { selector(node.Id); } 

        /// <summary>
        /// Deselects the actual node (and only this).
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public override void visitEnd(Columbus.Lim.Asg.Nodes.Base.Component node, bool callVirtualBase) { selector(node.Id); } 

        /// <summary>
        /// Deselects the actual node (and only this).
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public override void visitEnd(Columbus.Lim.Asg.Nodes.Base.ControlFlowBlock node, bool callVirtualBase) { selector(node.Id); } 

        /// <summary>
        /// Deselects the actual node (and only this).
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public override void visitEnd(Columbus.Lim.Asg.Nodes.Logical.Attribute node, bool callVirtualBase) { selector(node.Id); } 

        /// <summary>
        /// Deselects the actual node (and only this).
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public override void visitEnd(Columbus.Lim.Asg.Nodes.Logical.AttributeAccess node, bool callVirtualBase) { selector(node.Id); } 

        /// <summary>
        /// Deselects the actual node (and only this).
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public override void visitEnd(Columbus.Lim.Asg.Nodes.Logical.Class node, bool callVirtualBase) { selector(node.Id); } 

        /// <summary>
        /// Deselects the actual node (and only this).
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public override void visitEnd(Columbus.Lim.Asg.Nodes.Logical.ClassGeneric node, bool callVirtualBase) { selector(node.Id); } 

        /// <summary>
        /// Deselects the actual node (and only this).
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public override void visitEnd(Columbus.Lim.Asg.Nodes.Logical.ClassGenericInstance node, bool callVirtualBase) { selector(node.Id); } 

        /// <summary>
        /// Deselects the actual node (and only this).
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public override void visitEnd(Columbus.Lim.Asg.Nodes.Logical.ClassGenericSpec node, bool callVirtualBase) { selector(node.Id); } 

        /// <summary>
        /// Deselects the actual node (and only this).
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public override void visitEnd(Columbus.Lim.Asg.Nodes.Logical.Friendship node, bool callVirtualBase) { selector(node.Id); } 

        /// <summary>
        /// Deselects the actual node (and only this).
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public override void visitEnd(Columbus.Lim.Asg.Nodes.Logical.GenericParameter node, bool callVirtualBase) { selector(node.Id); } 

        /// <summary>
        /// Deselects the actual node (and only this).
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public override void visitEnd(Columbus.Lim.Asg.Nodes.Logical.Method node, bool callVirtualBase) { selector(node.Id); } 

        /// <summary>
        /// Deselects the actual node (and only this).
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public override void visitEnd(Columbus.Lim.Asg.Nodes.Logical.MethodCall node, bool callVirtualBase) { selector(node.Id); } 

        /// <summary>
        /// Deselects the actual node (and only this).
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public override void visitEnd(Columbus.Lim.Asg.Nodes.Logical.MethodGeneric node, bool callVirtualBase) { selector(node.Id); } 

        /// <summary>
        /// Deselects the actual node (and only this).
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public override void visitEnd(Columbus.Lim.Asg.Nodes.Logical.MethodGenericInstance node, bool callVirtualBase) { selector(node.Id); } 

        /// <summary>
        /// Deselects the actual node (and only this).
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public override void visitEnd(Columbus.Lim.Asg.Nodes.Logical.MethodGenericSpec node, bool callVirtualBase) { selector(node.Id); } 

        /// <summary>
        /// Deselects the actual node (and only this).
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public override void visitEnd(Columbus.Lim.Asg.Nodes.Logical.Package node, bool callVirtualBase) { selector(node.Id); } 

        /// <summary>
        /// Deselects the actual node (and only this).
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public override void visitEnd(Columbus.Lim.Asg.Nodes.Logical.Parameter node, bool callVirtualBase) { selector(node.Id); } 

        /// <summary>
        /// Deselects the actual node (and only this).
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public override void visitEnd(Columbus.Lim.Asg.Nodes.Physical.File node, bool callVirtualBase) { selector(node.Id); } 

        /// <summary>
        /// Deselects the actual node (and only this).
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public override void visitEnd(Columbus.Lim.Asg.Nodes.Physical.FileSystem node, bool callVirtualBase) { selector(node.Id); } 

        /// <summary>
        /// Deselects the actual node (and only this).
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public override void visitEnd(Columbus.Lim.Asg.Nodes.Physical.Folder node, bool callVirtualBase) { selector(node.Id); } 

        /// <summary>
        /// Deselects the actual node (and only this).
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public override void visitEnd(Columbus.Lim.Asg.Nodes.Type.SimpleType node, bool callVirtualBase) { selector(node.Id); } 

        /// <summary>
        /// Deselects the actual node (and only this).
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public override void visitEnd(Columbus.Lim.Asg.Nodes.Type.Type node, bool callVirtualBase) { selector(node.Id); } 

        /// <summary>
        /// Deselects the actual node (and only this).
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public override void visitEnd(Columbus.Lim.Asg.Nodes.Type.TypeFormerArray node, bool callVirtualBase) { selector(node.Id); } 

        /// <summary>
        /// Deselects the actual node (and only this).
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public override void visitEnd(Columbus.Lim.Asg.Nodes.Type.TypeFormerMethod node, bool callVirtualBase) { selector(node.Id); } 

        /// <summary>
        /// Deselects the actual node (and only this).
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public override void visitEnd(Columbus.Lim.Asg.Nodes.Type.TypeFormerNonType node, bool callVirtualBase) { selector(node.Id); } 

        /// <summary>
        /// Deselects the actual node (and only this).
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public override void visitEnd(Columbus.Lim.Asg.Nodes.Type.TypeFormerPointer node, bool callVirtualBase) { selector(node.Id); } 

        /// <summary>
        /// Deselects the actual node (and only this).
        /// </summary>
        /// <param name="node">[in] The node which is visited.</param>
        public override void visitEnd(Columbus.Lim.Asg.Nodes.Type.TypeFormerType node, bool callVirtualBase) { selector(node.Id); } 

    }

}
