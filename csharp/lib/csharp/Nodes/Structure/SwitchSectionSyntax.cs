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
using System.Diagnostics;
using System.Collections.Generic;

namespace Columbus.Csharp.Asg.Nodes.Structure {

    /// <summary>
    /// SwitchSectionSyntax class, which represents the structure::SwitchSectionSyntax node.
    /// </summary>
    [DebuggerDisplay("{DemangledName}")]
#if (CSHARP_INTERNAL)
    internal
#else
    public
#endif
    class SwitchSectionSyntax : Columbus.Csharp.Asg.Nodes.Base.Positioned {


        // ---------- Edges ----------

        /// <summary>Container stores the id of the nodes the Labels edge points to.</summary>
        protected LinkedList<uint> LabelsContainer;

        /// <summary>Container stores the id of the nodes the Statements edge points to.</summary>
        protected LinkedList<uint> StatementsContainer;

        /// <summary>
        /// Constructor, only factory can instantiates nodes.
        /// </summary>
        /// <param name="nodeId">[in] The id of the node.</param>
        /// <param name="factory">[in] Poiter to the Factory the node belongs to.</param>
        public SwitchSectionSyntax(uint nodeId, Factory factory) : base(nodeId, factory) {
            LabelsContainer = new LinkedList<uint>();
            StatementsContainer = new LinkedList<uint>();
        }

        /// <summary>
        /// Gives back the NodeKind of the node.
        /// </summary>
        /// <returns>Returns with the NodeKind.</returns>
        public override Types.NodeKind NodeKind {
            get { return Types.NodeKind.ndkSwitchSectionSyntax; }
        }


        // ---------- Reflection getter function ----------

        /// <summary>
        /// Gives back the begin iterator for the edge specified
        /// </summary>
        /// <param name="edge">[in] The multiple edge for which the iterator is requested</param>
        public override ListIterator<Columbus.Csharp.Asg.Nodes.Base.Base> GetListIteratorBegin(string edge) {
            switch(edge) {
                case "Labels":
                    return LabelsListIteratorBegin.Convert<Columbus.Csharp.Asg.Nodes.Base.Base>();
                case "Statements":
                    return StatementsListIteratorBegin.Convert<Columbus.Csharp.Asg.Nodes.Base.Base>();
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
                case "Labels":
                    addLabels(nodeId);
                    return;
                case "Statements":
                    addStatements(nodeId);
                    return;
                default:
                    base.add(edge, nodeId);
                    return;
            }
        }


        // ---------- Edge getter function(s) ----------

        /// <summary>
        /// Gives back iterator for the Labels edges.
        /// </summary>
        /// <returns>Returns an iterator for the Labels edges.</returns>
        public ListIterator<Columbus.Csharp.Asg.Nodes.Structure.SwitchLabelSyntax> LabelsListIteratorBegin {
            get {
                return new ListIterator<Columbus.Csharp.Asg.Nodes.Structure.SwitchLabelSyntax>(LabelsContainer, fact, true);
            }
        }

        /// <summary>
        /// Gives back iterator for the Labels edges.
        /// </summary>
        /// <returns>Returns an iterator for the Labels edges.</returns>
        public ListIterator<Columbus.Csharp.Asg.Nodes.Structure.SwitchLabelSyntax> LabelsListIteratorEnd {
            get {
                return new ListIterator<Columbus.Csharp.Asg.Nodes.Structure.SwitchLabelSyntax>(LabelsContainer, fact, false);
            }
        }

        /// <summary>
        /// Tells whether the node has Labels edges or not.
        /// </summary>
        /// <returns>Returns true if the node has at least one Labels edge.</returns>
        public bool LabelsIsEmpty {
            get { return LabelsContainer.Count == 0; }
        }

        /// <summary>
        /// Gives back how many Labels edges the node has.
        /// </summary>
        /// <returns>Returns with the number of Labels edges.</returns>
        public uint LabelsSize {
            get { return (uint)(LabelsContainer.Count); }
        }

        /// <summary>
        /// Gives back iterator for the Statements edges.
        /// </summary>
        /// <returns>Returns an iterator for the Statements edges.</returns>
        public ListIterator<Columbus.Csharp.Asg.Nodes.Statement.StatementSyntax> StatementsListIteratorBegin {
            get {
                return new ListIterator<Columbus.Csharp.Asg.Nodes.Statement.StatementSyntax>(StatementsContainer, fact, true);
            }
        }

        /// <summary>
        /// Gives back iterator for the Statements edges.
        /// </summary>
        /// <returns>Returns an iterator for the Statements edges.</returns>
        public ListIterator<Columbus.Csharp.Asg.Nodes.Statement.StatementSyntax> StatementsListIteratorEnd {
            get {
                return new ListIterator<Columbus.Csharp.Asg.Nodes.Statement.StatementSyntax>(StatementsContainer, fact, false);
            }
        }

        /// <summary>
        /// Tells whether the node has Statements edges or not.
        /// </summary>
        /// <returns>Returns true if the node has at least one Statements edge.</returns>
        public bool StatementsIsEmpty {
            get { return StatementsContainer.Count == 0; }
        }

        /// <summary>
        /// Gives back how many Statements edges the node has.
        /// </summary>
        /// <returns>Returns with the number of Statements edges.</returns>
        public uint StatementsSize {
            get { return (uint)(StatementsContainer.Count); }
        }


        // ---------- Edge setter function(s) ----------

        /// <summary>
        /// Adds a new Labels edge to the node and inserts it after the other ones.
        /// </summary>
        /// <param name="node">[in] The end point of the new Labels edge.</param>
        /// <exception cref="Columbus.Csharp.Asg.CsharpException">Throws CsharpException if there is something wrong with the given node.</exception>
        public void addLabels(Columbus.Csharp.Asg.Nodes.Structure.SwitchLabelSyntax node) {
            addLabels(node.Id);
        }

        /// <summary>
        /// Adds a new Labels edge to the node and inserts it after the other ones.
        /// </summary>
        /// <param name="nodeId">[in] The end point of the new Labels edge.</param>
        /// <exception cref="Columbus.Csharp.Asg.CsharpException">Throws CsharpException if the given nodeId is invalid.</exception>
        public void addLabels(uint nodeId) {
            if (!fact.getExist(nodeId))
                throw new CsharpException("Columbus.Csharp.Asg.Nodes.Structure.SwitchSectionSyntax.addLabels(NodeId)", "The end point of the edge does not exist.");
            Columbus.Csharp.Asg.Nodes.Base.Base node = fact.getRef(nodeId);
            if (Common.getIsBaseClassKind(node.NodeKind, Types.NodeKind.ndkSwitchLabelSyntax)) {
                LabelsContainer.AddLast(nodeId);
            } else {
                throw new CsharpException("Columbus.Csharp.Asg.Nodes.Structure.SwitchSectionSyntax.setLabels(NodeId)", "Invalid NodeKind (" + node.NodeKind.ToString() + ").");
            }
           setParentEdge(nodeId, (uint)Types.EdgeKind.edkSwitchSectionSyntax_Labels);
            if (fact.ReverseEdges != null)
              fact.ReverseEdges.insertEdge(nodeId, this.Id, Types.EdgeKind.edkSwitchSectionSyntax_Labels);
        }

        /// <summary>
        /// Adds a new Statements edge to the node and inserts it after the other ones.
        /// </summary>
        /// <param name="node">[in] The end point of the new Statements edge.</param>
        /// <exception cref="Columbus.Csharp.Asg.CsharpException">Throws CsharpException if there is something wrong with the given node.</exception>
        public void addStatements(Columbus.Csharp.Asg.Nodes.Statement.StatementSyntax node) {
            addStatements(node.Id);
        }

        /// <summary>
        /// Adds a new Statements edge to the node and inserts it after the other ones.
        /// </summary>
        /// <param name="nodeId">[in] The end point of the new Statements edge.</param>
        /// <exception cref="Columbus.Csharp.Asg.CsharpException">Throws CsharpException if the given nodeId is invalid.</exception>
        public void addStatements(uint nodeId) {
            if (!fact.getExist(nodeId))
                throw new CsharpException("Columbus.Csharp.Asg.Nodes.Structure.SwitchSectionSyntax.addStatements(NodeId)", "The end point of the edge does not exist.");
            Columbus.Csharp.Asg.Nodes.Base.Base node = fact.getRef(nodeId);
            if (Common.getIsBaseClassKind(node.NodeKind, Types.NodeKind.ndkStatementSyntax)) {
                StatementsContainer.AddLast(nodeId);
            } else {
                throw new CsharpException("Columbus.Csharp.Asg.Nodes.Structure.SwitchSectionSyntax.setStatements(NodeId)", "Invalid NodeKind (" + node.NodeKind.ToString() + ").");
            }
           setParentEdge(nodeId, (uint)Types.EdgeKind.edkSwitchSectionSyntax_Statements);
            if (fact.ReverseEdges != null)
              fact.ReverseEdges.insertEdge(nodeId, this.Id, Types.EdgeKind.edkSwitchSectionSyntax_Statements);
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


            foreach (var Labels in LabelsContainer) {
              io.writeUInt4(Labels);
            }
            io.writeUInt4(0); // This is the end sign

            foreach (var Statements in StatementsContainer) {
              io.writeUInt4(Statements);
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
              LabelsContainer.AddLast(_id);
              setParentEdge(_id, (uint)Types.EdgeKind.edkSwitchSectionSyntax_Labels);
              _id = binIo.readUInt4();
            }

            _id = binIo.readUInt4();
            while (_id != 0) {
              StatementsContainer.AddLast(_id);
              setParentEdge(_id, (uint)Types.EdgeKind.edkSwitchSectionSyntax_Statements);
              _id = binIo.readUInt4();
            }
        }

    }

}
