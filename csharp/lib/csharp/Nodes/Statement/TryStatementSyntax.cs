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

namespace Columbus.Csharp.Asg.Nodes.Statement {

    /// <summary>
    /// TryStatementSyntax class, which represents the statement::TryStatementSyntax node.
    /// </summary>
    [DebuggerDisplay("{DemangledName}")]
#if (CSHARP_INTERNAL)
    internal
#else
    public
#endif
    class TryStatementSyntax : StatementSyntax {


        // ---------- Edges ----------

        /// <summary>The id of the node the Block edge points to.</summary>
        protected uint m_Block;

        /// <summary>Container stores the id of the nodes the Catches edge points to.</summary>
        protected LinkedList<uint> CatchesContainer;

        /// <summary>The id of the node the Finally edge points to.</summary>
        protected uint m_Finally;

        /// <summary>
        /// Constructor, only factory can instantiates nodes.
        /// </summary>
        /// <param name="nodeId">[in] The id of the node.</param>
        /// <param name="factory">[in] Poiter to the Factory the node belongs to.</param>
        public TryStatementSyntax(uint nodeId, Factory factory) : base(nodeId, factory) {
            m_Block = 0;
            CatchesContainer = new LinkedList<uint>();
            m_Finally = 0;
        }

        /// <summary>
        /// Gives back the NodeKind of the node.
        /// </summary>
        /// <returns>Returns with the NodeKind.</returns>
        public override Types.NodeKind NodeKind {
            get { return Types.NodeKind.ndkTryStatementSyntax; }
        }


        // ---------- Reflection getter function ----------

        /// <summary>
        /// Gives back the begin iterator for the edge specified
        /// </summary>
        /// <param name="edge">[in] The multiple edge for which the iterator is requested</param>
        public override ListIterator<Columbus.Csharp.Asg.Nodes.Base.Base> GetListIteratorBegin(string edge) {
            switch(edge) {
                case "Catches":
                    return CatchesListIteratorBegin.Convert<Columbus.Csharp.Asg.Nodes.Base.Base>();
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
                case "Catches":
                    addCatches(nodeId);
                    return;
                default:
                    base.add(edge, nodeId);
                    return;
            }
        }


        // ---------- Edge getter function(s) ----------

        /// <summary>
        /// Gives back the id of the node the Block edge points to.
        /// </summary>
        /// <returns>Returns the end point of the m_Block edge.</returns>
        /// <exception cref="Columbus.Csharp.Asg.CsharpException">Throws CsharpException if the edge id is invalid.</exception>
        public uint getBlock() {
            if (fact.getIsFiltered(m_Block))
                return 1;
            else
                return m_Block;
        }

        /// <summary>
        /// Gives back iterator for the Catches edges.
        /// </summary>
        /// <returns>Returns an iterator for the Catches edges.</returns>
        public ListIterator<Columbus.Csharp.Asg.Nodes.Structure.CatchClauseSyntax> CatchesListIteratorBegin {
            get {
                return new ListIterator<Columbus.Csharp.Asg.Nodes.Structure.CatchClauseSyntax>(CatchesContainer, fact, true);
            }
        }

        /// <summary>
        /// Gives back iterator for the Catches edges.
        /// </summary>
        /// <returns>Returns an iterator for the Catches edges.</returns>
        public ListIterator<Columbus.Csharp.Asg.Nodes.Structure.CatchClauseSyntax> CatchesListIteratorEnd {
            get {
                return new ListIterator<Columbus.Csharp.Asg.Nodes.Structure.CatchClauseSyntax>(CatchesContainer, fact, false);
            }
        }

        /// <summary>
        /// Tells whether the node has Catches edges or not.
        /// </summary>
        /// <returns>Returns true if the node has at least one Catches edge.</returns>
        public bool CatchesIsEmpty {
            get { return CatchesContainer.Count == 0; }
        }

        /// <summary>
        /// Gives back how many Catches edges the node has.
        /// </summary>
        /// <returns>Returns with the number of Catches edges.</returns>
        public uint CatchesSize {
            get { return (uint)(CatchesContainer.Count); }
        }

        /// <summary>
        /// Gives back the id of the node the Finally edge points to.
        /// </summary>
        /// <returns>Returns the end point of the m_Finally edge.</returns>
        /// <exception cref="Columbus.Csharp.Asg.CsharpException">Throws CsharpException if the edge id is invalid.</exception>
        public uint getFinally() {
            if (fact.getIsFiltered(m_Finally))
                return 1;
            else
                return m_Finally;
        }


        // ---------- Edge setter function(s) ----------

        /// <summary>
        /// Sets the Block edge.
        /// </summary>
        /// <param name="nodeId">[in] The new end point of the Block edge or 0. With 0 the edge can be deleted.</param>
        /// <exception cref="Columbus.Csharp.Asg.CsharpException">Throws CsharpException if the nodeId is invalid.</exception>
        public void setBlock(uint nodeId) {
            if (nodeId != 0) {
                if (!fact.getExist(nodeId))
                    throw new CsharpException("Columbus.Csharp.Asg.Nodes.Statement.TryStatementSyntax.setBlock(NodeId)", "The end point of the edge does not exist.");

                Columbus.Csharp.Asg.Nodes.Base.Base node = fact.getRef(nodeId);
                if (Common.getIsBaseClassKind(node.NodeKind, Types.NodeKind.ndkBlockSyntax)) {
                    if (m_Block != 0) {
                        removeParentEdge(m_Block);
                    }
                    m_Block = nodeId;
                    setParentEdge(m_Block, (uint)Types.EdgeKind.edkTryStatementSyntax_Block);
                } else {
                    throw new CsharpException("Columbus.Csharp.Asg.Nodes.Statement.TryStatementSyntax.setBlock(NodeId)", "Invalid NodeKind (" + node.NodeKind.ToString() + ").");
                }
            } else {
                if (m_Block != 0) {
                    removeParentEdge(m_Block);
                }
                m_Block = 0;
            }
        }

        /// <summary>
        /// Sets the Block edge.
        /// </summary>
        /// <param name="node">[in] The new end point of the Block edge.</param>
        /// <exception cref="Columbus.Csharp.Asg.CsharpException">Throws CsharpException if there's something wrong with the given node.</exception>
        public void setBlock(Columbus.Csharp.Asg.Nodes.Statement.BlockSyntax node) {
            if (m_Block != 0) {
                removeParentEdge(m_Block);
            }
            m_Block = node.Id;
            setParentEdge(m_Block, (uint)Types.EdgeKind.edkTryStatementSyntax_Block);
        }

        /// <summary>
        /// Adds a new Catches edge to the node and inserts it after the other ones.
        /// </summary>
        /// <param name="node">[in] The end point of the new Catches edge.</param>
        /// <exception cref="Columbus.Csharp.Asg.CsharpException">Throws CsharpException if there is something wrong with the given node.</exception>
        public void addCatches(Columbus.Csharp.Asg.Nodes.Structure.CatchClauseSyntax node) {
            addCatches(node.Id);
        }

        /// <summary>
        /// Adds a new Catches edge to the node and inserts it after the other ones.
        /// </summary>
        /// <param name="nodeId">[in] The end point of the new Catches edge.</param>
        /// <exception cref="Columbus.Csharp.Asg.CsharpException">Throws CsharpException if the given nodeId is invalid.</exception>
        public void addCatches(uint nodeId) {
            if (!fact.getExist(nodeId))
                throw new CsharpException("Columbus.Csharp.Asg.Nodes.Statement.TryStatementSyntax.addCatches(NodeId)", "The end point of the edge does not exist.");
            Columbus.Csharp.Asg.Nodes.Base.Base node = fact.getRef(nodeId);
            if (Common.getIsBaseClassKind(node.NodeKind, Types.NodeKind.ndkCatchClauseSyntax)) {
                CatchesContainer.AddLast(nodeId);
            } else {
                throw new CsharpException("Columbus.Csharp.Asg.Nodes.Statement.TryStatementSyntax.setCatches(NodeId)", "Invalid NodeKind (" + node.NodeKind.ToString() + ").");
            }
           setParentEdge(nodeId, (uint)Types.EdgeKind.edkTryStatementSyntax_Catches);
            if (fact.ReverseEdges != null)
              fact.ReverseEdges.insertEdge(nodeId, this.Id, Types.EdgeKind.edkTryStatementSyntax_Catches);
        }

        /// <summary>
        /// Sets the Finally edge.
        /// </summary>
        /// <param name="nodeId">[in] The new end point of the Finally edge or 0. With 0 the edge can be deleted.</param>
        /// <exception cref="Columbus.Csharp.Asg.CsharpException">Throws CsharpException if the nodeId is invalid.</exception>
        public void setFinally(uint nodeId) {
            if (nodeId != 0) {
                if (!fact.getExist(nodeId))
                    throw new CsharpException("Columbus.Csharp.Asg.Nodes.Statement.TryStatementSyntax.setFinally(NodeId)", "The end point of the edge does not exist.");

                Columbus.Csharp.Asg.Nodes.Base.Base node = fact.getRef(nodeId);
                if (Common.getIsBaseClassKind(node.NodeKind, Types.NodeKind.ndkFinallyClauseSyntax)) {
                    if (m_Finally != 0) {
                        removeParentEdge(m_Finally);
                    }
                    m_Finally = nodeId;
                    setParentEdge(m_Finally, (uint)Types.EdgeKind.edkTryStatementSyntax_Finally);
                } else {
                    throw new CsharpException("Columbus.Csharp.Asg.Nodes.Statement.TryStatementSyntax.setFinally(NodeId)", "Invalid NodeKind (" + node.NodeKind.ToString() + ").");
                }
            } else {
                if (m_Finally != 0) {
                    removeParentEdge(m_Finally);
                }
                m_Finally = 0;
            }
        }

        /// <summary>
        /// Sets the Finally edge.
        /// </summary>
        /// <param name="node">[in] The new end point of the Finally edge.</param>
        /// <exception cref="Columbus.Csharp.Asg.CsharpException">Throws CsharpException if there's something wrong with the given node.</exception>
        public void setFinally(Columbus.Csharp.Asg.Nodes.Structure.FinallyClauseSyntax node) {
            if (m_Finally != 0) {
                removeParentEdge(m_Finally);
            }
            m_Finally = node.Id;
            setParentEdge(m_Finally, (uint)Types.EdgeKind.edkTryStatementSyntax_Finally);
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

            io.writeUInt4(m_Block);
            io.writeUInt4(m_Finally);


            foreach (var Catches in CatchesContainer) {
              io.writeUInt4(Catches);
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

            m_Block =  binIo.readUInt4();
            if (m_Block != 0)
              setParentEdge(m_Block,(uint)Types.EdgeKind.edkTryStatementSyntax_Block);

            m_Finally =  binIo.readUInt4();
            if (m_Finally != 0)
              setParentEdge(m_Finally,(uint)Types.EdgeKind.edkTryStatementSyntax_Finally);

            uint _id;

            _id = binIo.readUInt4();
            while (_id != 0) {
              CatchesContainer.AddLast(_id);
              setParentEdge(_id, (uint)Types.EdgeKind.edkTryStatementSyntax_Catches);
              _id = binIo.readUInt4();
            }
        }

    }

}
