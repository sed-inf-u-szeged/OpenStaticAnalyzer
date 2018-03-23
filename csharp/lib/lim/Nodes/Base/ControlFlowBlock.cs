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

namespace Columbus.Lim.Asg.Nodes.Base {

    /// <summary>
    /// ControlFlowBlock class, which represents the base::ControlFlowBlock node.
    /// </summary>
    [DebuggerDisplay("{DemangledName}")]
#if (LIM_INTERNAL)
    internal
#else
    public
#endif
    class ControlFlowBlock : Base {


        // ---------- Edges ----------

        /// <summary>Container stores the id of the nodes the calls edge points to.</summary>
        protected LinkedList<uint> callsContainer;

        /// <summary>Container stores the id of the nodes the pred edge points to.</summary>
        protected LinkedList<uint> predContainer;

        /// <summary>
        /// Constructor, only factory can instantiates nodes.
        /// </summary>
        /// <param name="nodeId">[in] The id of the node.</param>
        /// <param name="factory">[in] Poiter to the Factory the node belongs to.</param>
        public ControlFlowBlock(uint nodeId, Factory factory) : base(nodeId, factory) {
            callsContainer = new LinkedList<uint>();
            predContainer = new LinkedList<uint>();
        }

        /// <summary>
        /// Gives back the NodeKind of the node.
        /// </summary>
        /// <returns>Returns with the NodeKind.</returns>
        public override Types.NodeKind NodeKind {
            get { return Types.NodeKind.ndkControlFlowBlock; }
        }


        // ---------- Reflection getter function ----------

        /// <summary>
        /// Gives back the begin iterator for the edge specified
        /// </summary>
        /// <param name="edge">[in] The multiple edge for which the iterator is requested</param>
        public override ListIterator<Columbus.Lim.Asg.Nodes.Base.Base> GetListIteratorBegin(string edge) {
            switch(edge) {
                case "Calls":
                    return CallsListIteratorBegin.Convert<Columbus.Lim.Asg.Nodes.Base.Base>();
                case "Pred":
                    return PredListIteratorBegin.Convert<Columbus.Lim.Asg.Nodes.Base.Base>();
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
                case "Calls":
                    addCalls(nodeId);
                    return;
                case "Pred":
                    addPred(nodeId);
                    return;
                default:
                    base.add(edge, nodeId);
                    return;
            }
        }


        // ---------- Edge getter function(s) ----------

        /// <summary>
        /// Gives back iterator for the calls edges.
        /// </summary>
        /// <returns>Returns an iterator for the calls edges.</returns>
        public ListIterator<Columbus.Lim.Asg.Nodes.Logical.Method> CallsListIteratorBegin {
            get {
                return new ListIterator<Columbus.Lim.Asg.Nodes.Logical.Method>(callsContainer, fact, true);
            }
        }

        /// <summary>
        /// Gives back iterator for the calls edges.
        /// </summary>
        /// <returns>Returns an iterator for the calls edges.</returns>
        public ListIterator<Columbus.Lim.Asg.Nodes.Logical.Method> CallsListIteratorEnd {
            get {
                return new ListIterator<Columbus.Lim.Asg.Nodes.Logical.Method>(callsContainer, fact, false);
            }
        }

        /// <summary>
        /// Tells whether the node has calls edges or not.
        /// </summary>
        /// <returns>Returns true if the node has at least one calls edge.</returns>
        public bool CallsIsEmpty {
            get { return callsContainer.Count == 0; }
        }

        /// <summary>
        /// Gives back how many calls edges the node has.
        /// </summary>
        /// <returns>Returns with the number of calls edges.</returns>
        public uint CallsSize {
            get { return (uint)(callsContainer.Count); }
        }

        /// <summary>
        /// Gives back iterator for the pred edges.
        /// </summary>
        /// <returns>Returns an iterator for the pred edges.</returns>
        public ListIterator<Columbus.Lim.Asg.Nodes.Base.ControlFlowBlock> PredListIteratorBegin {
            get {
                return new ListIterator<Columbus.Lim.Asg.Nodes.Base.ControlFlowBlock>(predContainer, fact, true);
            }
        }

        /// <summary>
        /// Gives back iterator for the pred edges.
        /// </summary>
        /// <returns>Returns an iterator for the pred edges.</returns>
        public ListIterator<Columbus.Lim.Asg.Nodes.Base.ControlFlowBlock> PredListIteratorEnd {
            get {
                return new ListIterator<Columbus.Lim.Asg.Nodes.Base.ControlFlowBlock>(predContainer, fact, false);
            }
        }

        /// <summary>
        /// Tells whether the node has pred edges or not.
        /// </summary>
        /// <returns>Returns true if the node has at least one pred edge.</returns>
        public bool PredIsEmpty {
            get { return predContainer.Count == 0; }
        }

        /// <summary>
        /// Gives back how many pred edges the node has.
        /// </summary>
        /// <returns>Returns with the number of pred edges.</returns>
        public uint PredSize {
            get { return (uint)(predContainer.Count); }
        }


        // ---------- Edge setter function(s) ----------

        /// <summary>
        /// Adds a new calls edge to the node and inserts it after the other ones.
        /// </summary>
        /// <param name="node">[in] The end point of the new calls edge.</param>
        /// <exception cref="Columbus.Lim.Asg.LimException">Throws LimException if there is something wrong with the given node.</exception>
        public void addCalls(Columbus.Lim.Asg.Nodes.Logical.Method node) {
            addCalls(node.Id);
        }

        /// <summary>
        /// Adds a new calls edge to the node and inserts it after the other ones.
        /// </summary>
        /// <param name="nodeId">[in] The end point of the new calls edge.</param>
        /// <exception cref="Columbus.Lim.Asg.LimException">Throws LimException if the given nodeId is invalid.</exception>
        public void addCalls(uint nodeId) {
            if (!fact.getExist(nodeId))
                throw new LimException("Columbus.Lim.Asg.Nodes.Base.ControlFlowBlock.addCalls(NodeId)", "The end point of the edge does not exist.");
            Columbus.Lim.Asg.Nodes.Base.Base node = fact.getRef(nodeId);
            if (Common.getIsBaseClassKind(node.NodeKind, Types.NodeKind.ndkMethod)) {
                callsContainer.AddLast(nodeId);
            } else {
                throw new LimException("Columbus.Lim.Asg.Nodes.Base.ControlFlowBlock.setCalls(NodeId)", "Invalid NodeKind (" + node.NodeKind.ToString() + ").");
            }
            if (fact.ReverseEdges != null)
              fact.ReverseEdges.insertEdge(nodeId, this.Id, Types.EdgeKind.edkControlFlowBlock_Calls);
        }

        /// <summary>
        /// Adds a new pred edge to the node and inserts it after the other ones.
        /// </summary>
        /// <param name="node">[in] The end point of the new pred edge.</param>
        /// <exception cref="Columbus.Lim.Asg.LimException">Throws LimException if there is something wrong with the given node.</exception>
        public void addPred(Columbus.Lim.Asg.Nodes.Base.ControlFlowBlock node) {
            addPred(node.Id);
        }

        /// <summary>
        /// Adds a new pred edge to the node and inserts it after the other ones.
        /// </summary>
        /// <param name="nodeId">[in] The end point of the new pred edge.</param>
        /// <exception cref="Columbus.Lim.Asg.LimException">Throws LimException if the given nodeId is invalid.</exception>
        public void addPred(uint nodeId) {
            if (!fact.getExist(nodeId))
                throw new LimException("Columbus.Lim.Asg.Nodes.Base.ControlFlowBlock.addPred(NodeId)", "The end point of the edge does not exist.");
            Columbus.Lim.Asg.Nodes.Base.Base node = fact.getRef(nodeId);
            if (Common.getIsBaseClassKind(node.NodeKind, Types.NodeKind.ndkControlFlowBlock)) {
                predContainer.AddLast(nodeId);
            } else {
                throw new LimException("Columbus.Lim.Asg.Nodes.Base.ControlFlowBlock.setPred(NodeId)", "Invalid NodeKind (" + node.NodeKind.ToString() + ").");
            }
            if (fact.ReverseEdges != null)
              fact.ReverseEdges.insertEdge(nodeId, this.Id, Types.EdgeKind.edkControlFlowBlock_Pred);
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


            foreach (var calls in callsContainer) {
              io.writeUInt4(calls);
            }
            io.writeUInt4(0); // This is the end sign

            foreach (var pred in predContainer) {
              io.writeUInt4(pred);
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
              callsContainer.AddLast(_id);
              _id = binIo.readUInt4();
            }

            _id = binIo.readUInt4();
            while (_id != 0) {
              predContainer.AddLast(_id);
              _id = binIo.readUInt4();
            }
        }

    }

}
