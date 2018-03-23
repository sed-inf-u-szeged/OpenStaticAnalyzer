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
using System.Diagnostics;
using System.Collections.Generic;

namespace Columbus.Csharp.Asg.Nodes.Structure {

    /// <summary>
    /// TypeArgumentListSyntax class, which represents the structure::TypeArgumentListSyntax node.
    /// </summary>
    [DebuggerDisplay("{DemangledName}")]
#if (CSHARP_INTERNAL)
    internal
#else
    public
#endif
    class TypeArgumentListSyntax : Columbus.Csharp.Asg.Nodes.Base.Positioned {


        // ---------- Edges ----------

        /// <summary>Container stores the id of the nodes the Arguments edge points to.</summary>
        protected LinkedList<uint> ArgumentsContainer;

        /// <summary>
        /// Constructor, only factory can instantiates nodes.
        /// </summary>
        /// <param name="nodeId">[in] The id of the node.</param>
        /// <param name="factory">[in] Poiter to the Factory the node belongs to.</param>
        public TypeArgumentListSyntax(uint nodeId, Factory factory) : base(nodeId, factory) {
            ArgumentsContainer = new LinkedList<uint>();
        }

        /// <summary>
        /// Gives back the NodeKind of the node.
        /// </summary>
        /// <returns>Returns with the NodeKind.</returns>
        public override Types.NodeKind NodeKind {
            get { return Types.NodeKind.ndkTypeArgumentListSyntax; }
        }


        // ---------- Reflection getter function ----------

        /// <summary>
        /// Gives back the begin iterator for the edge specified
        /// </summary>
        /// <param name="edge">[in] The multiple edge for which the iterator is requested</param>
        public override ListIterator<Columbus.Csharp.Asg.Nodes.Base.Base> GetListIteratorBegin(string edge) {
            switch(edge) {
                case "Arguments":
                    return ArgumentsListIteratorBegin.Convert<Columbus.Csharp.Asg.Nodes.Base.Base>();
                default:
                    return base.GetListIteratorBegin(edge);
            }
        }


        // ---------- Reflection add function ----------

        /// <summary>
        /// Adds item as a new edge
        /// </summary>
        public override void add(string edge, uint nodeId) {
            switch(edge) {
                case "Arguments":
                    addArguments(nodeId);
                    return;
                default:
                    base.add(edge, nodeId);
                    return;
            }
        }


        // ---------- Edge getter function(s) ----------

        /// <summary>
        /// Gives back iterator for the Arguments edges.
        /// </summary>
        /// <returns>Returns an iterator for the Arguments edges.</returns>
        public ListIterator<Columbus.Csharp.Asg.Nodes.Expression.TypeSyntax> ArgumentsListIteratorBegin {
            get {
                return new ListIterator<Columbus.Csharp.Asg.Nodes.Expression.TypeSyntax>(ArgumentsContainer, fact, true);
            }
        }

        /// <summary>
        /// Gives back iterator for the Arguments edges.
        /// </summary>
        /// <returns>Returns an iterator for the Arguments edges.</returns>
        public ListIterator<Columbus.Csharp.Asg.Nodes.Expression.TypeSyntax> ArgumentsListIteratorEnd {
            get {
                return new ListIterator<Columbus.Csharp.Asg.Nodes.Expression.TypeSyntax>(ArgumentsContainer, fact, false);
            }
        }

        /// <summary>
        /// Tells whether the node has Arguments edges or not.
        /// </summary>
        /// <returns>Returns true if the node has at least one Arguments edge.</returns>
        public bool ArgumentsIsEmpty {
            get { return ArgumentsContainer.Count == 0; }
        }

        /// <summary>
        /// Gives back how many Arguments edges the node has.
        /// </summary>
        /// <returns>Returns with the number of Arguments edges.</returns>
        public uint ArgumentsSize {
            get { return (uint)(ArgumentsContainer.Count); }
        }


        // ---------- Edge setter function(s) ----------

        /// <summary>
        /// Adds a new Arguments edge to the node and inserts it after the other ones.
        /// </summary>
        /// <param name="node">[in] The end point of the new Arguments edge.</param>
        /// <exception cref="Columbus.Csharp.Asg.CsharpException">Throws CsharpException if there is something wrong with the given node.</exception>
        public void addArguments(Columbus.Csharp.Asg.Nodes.Expression.TypeSyntax node) {
            addArguments(node.Id);
        }

        /// <summary>
        /// Adds a new Arguments edge to the node and inserts it after the other ones.
        /// </summary>
        /// <param name="nodeId">[in] The end point of the new Arguments edge.</param>
        /// <exception cref="Columbus.Csharp.Asg.CsharpException">Throws CsharpException if the given nodeId is invalid.</exception>
        public void addArguments(uint nodeId) {
            if (!fact.getExist(nodeId))
                throw new CsharpException("Columbus.Csharp.Asg.Nodes.Structure.TypeArgumentListSyntax.addArguments(NodeId)", "The end point of the edge does not exist.");
            Columbus.Csharp.Asg.Nodes.Base.Base node = fact.getRef(nodeId);
            if (Common.getIsBaseClassKind(node.NodeKind, Types.NodeKind.ndkTypeSyntax)) {
                ArgumentsContainer.AddLast(nodeId);
            } else {
                throw new CsharpException("Columbus.Csharp.Asg.Nodes.Structure.TypeArgumentListSyntax.setArguments(NodeId)", "Invalid NodeKind (" + node.NodeKind.ToString() + ").");
            }
           setParentEdge(nodeId, (uint)Types.EdgeKind.edkTypeArgumentListSyntax_Arguments);
            if (fact.ReverseEdges != null)
              fact.ReverseEdges.insertEdge(nodeId, this.Id, Types.EdgeKind.edkTypeArgumentListSyntax_Arguments);
        }


        // ---------- Accept functions for Visitor ----------

        /// <summary>
        /// It calls the appropriate visit method of the given visitor.
        /// </summary>
        /// <param name="visitor">[in] The used visitor.</param>
        public override void accept(Visitors.Visitor visitor) {
            visitor.visit(this);
        }

        /// <summary>
        /// It calls the appropriate visitEnd method of the given visitor.
        /// </summary>
        /// <param name="visitor">[in] The used visitor.</param>
        public override void acceptEnd(Visitors.Visitor visitor) {
            visitor.visitEnd(this);
        }

        /// <summary>
        /// Saves the node.
        /// </summary>
        /// <param name="io">[in] The node is written into io.</param>
        /// <exception cref="Columbus.ColumbusIOException">Throws ColumbusIOException if there is something wrong with the file.</exception>
        public override void save(IO io) {
            base.save(io);


            foreach (var Arguments in ArgumentsContainer) {
              io.writeUInt4(Arguments);
            }
            io.writeUInt4(0); // This is the end sign
        }

        /// <summary>
        /// Loads the node.
        /// </summary>
        /// <param name="io">[in] The node is read from io.</param>
        /// <exception cref="Columbus.ColumbusIOException">Throws ColumbusIOException if there is something wrong with the file.</exception>
        public override void load(IO binIo) {
            base.load(binIo);

            uint _id;

            _id = binIo.readUInt4();
            while (_id != 0) {
              ArgumentsContainer.AddLast(_id);
              setParentEdge(_id, (uint)Types.EdgeKind.edkTypeArgumentListSyntax_Arguments);
              _id = binIo.readUInt4();
            }
        }

    }

}
