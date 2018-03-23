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
    /// OrderByClauseSyntax class, which represents the structure::OrderByClauseSyntax node.
    /// </summary>
    [DebuggerDisplay("{DemangledName}")]
#if (CSHARP_INTERNAL)
    internal
#else
    public
#endif
    class OrderByClauseSyntax : QueryClauseSyntax {


        // ---------- Edges ----------

        /// <summary>Container stores the id of the nodes the Orderings edge points to.</summary>
        protected LinkedList<uint> OrderingsContainer;

        /// <summary>
        /// Constructor, only factory can instantiates nodes.
        /// </summary>
        /// <param name="nodeId">[in] The id of the node.</param>
        /// <param name="factory">[in] Poiter to the Factory the node belongs to.</param>
        public OrderByClauseSyntax(uint nodeId, Factory factory) : base(nodeId, factory) {
            OrderingsContainer = new LinkedList<uint>();
        }

        /// <summary>
        /// Gives back the NodeKind of the node.
        /// </summary>
        /// <returns>Returns with the NodeKind.</returns>
        public override Types.NodeKind NodeKind {
            get { return Types.NodeKind.ndkOrderByClauseSyntax; }
        }


        // ---------- Reflection getter function ----------

        /// <summary>
        /// Gives back the begin iterator for the edge specified
        /// </summary>
        /// <param name="edge">[in] The multiple edge for which the iterator is requested</param>
        public override ListIterator<Columbus.Csharp.Asg.Nodes.Base.Base> GetListIteratorBegin(string edge) {
            switch(edge) {
                case "Orderings":
                    return OrderingsListIteratorBegin.Convert<Columbus.Csharp.Asg.Nodes.Base.Base>();
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
                case "Orderings":
                    addOrderings(nodeId);
                    return;
                default:
                    base.add(edge, nodeId);
                    return;
            }
        }


        // ---------- Edge getter function(s) ----------

        /// <summary>
        /// Gives back iterator for the Orderings edges.
        /// </summary>
        /// <returns>Returns an iterator for the Orderings edges.</returns>
        public ListIterator<Columbus.Csharp.Asg.Nodes.Structure.OrderingSyntax> OrderingsListIteratorBegin {
            get {
                return new ListIterator<Columbus.Csharp.Asg.Nodes.Structure.OrderingSyntax>(OrderingsContainer, fact, true);
            }
        }

        /// <summary>
        /// Gives back iterator for the Orderings edges.
        /// </summary>
        /// <returns>Returns an iterator for the Orderings edges.</returns>
        public ListIterator<Columbus.Csharp.Asg.Nodes.Structure.OrderingSyntax> OrderingsListIteratorEnd {
            get {
                return new ListIterator<Columbus.Csharp.Asg.Nodes.Structure.OrderingSyntax>(OrderingsContainer, fact, false);
            }
        }

        /// <summary>
        /// Tells whether the node has Orderings edges or not.
        /// </summary>
        /// <returns>Returns true if the node has at least one Orderings edge.</returns>
        public bool OrderingsIsEmpty {
            get { return OrderingsContainer.Count == 0; }
        }

        /// <summary>
        /// Gives back how many Orderings edges the node has.
        /// </summary>
        /// <returns>Returns with the number of Orderings edges.</returns>
        public uint OrderingsSize {
            get { return (uint)(OrderingsContainer.Count); }
        }


        // ---------- Edge setter function(s) ----------

        /// <summary>
        /// Adds a new Orderings edge to the node and inserts it after the other ones.
        /// </summary>
        /// <param name="node">[in] The end point of the new Orderings edge.</param>
        /// <exception cref="Columbus.Csharp.Asg.CsharpException">Throws CsharpException if there is something wrong with the given node.</exception>
        public void addOrderings(Columbus.Csharp.Asg.Nodes.Structure.OrderingSyntax node) {
            addOrderings(node.Id);
        }

        /// <summary>
        /// Adds a new Orderings edge to the node and inserts it after the other ones.
        /// </summary>
        /// <param name="nodeId">[in] The end point of the new Orderings edge.</param>
        /// <exception cref="Columbus.Csharp.Asg.CsharpException">Throws CsharpException if the given nodeId is invalid.</exception>
        public void addOrderings(uint nodeId) {
            if (!fact.getExist(nodeId))
                throw new CsharpException("Columbus.Csharp.Asg.Nodes.Structure.OrderByClauseSyntax.addOrderings(NodeId)", "The end point of the edge does not exist.");
            Columbus.Csharp.Asg.Nodes.Base.Base node = fact.getRef(nodeId);
            if (Common.getIsBaseClassKind(node.NodeKind, Types.NodeKind.ndkOrderingSyntax)) {
                OrderingsContainer.AddLast(nodeId);
            } else {
                throw new CsharpException("Columbus.Csharp.Asg.Nodes.Structure.OrderByClauseSyntax.setOrderings(NodeId)", "Invalid NodeKind (" + node.NodeKind.ToString() + ").");
            }
           setParentEdge(nodeId, (uint)Types.EdgeKind.edkOrderByClauseSyntax_Orderings);
            if (fact.ReverseEdges != null)
              fact.ReverseEdges.insertEdge(nodeId, this.Id, Types.EdgeKind.edkOrderByClauseSyntax_Orderings);
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


            foreach (var Orderings in OrderingsContainer) {
              io.writeUInt4(Orderings);
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
              OrderingsContainer.AddLast(_id);
              setParentEdge(_id, (uint)Types.EdgeKind.edkOrderByClauseSyntax_Orderings);
              _id = binIo.readUInt4();
            }
        }

    }

}
