using System;
using System.Text;
using System.Diagnostics;
using System.Collections.Generic;

namespace Columbus.Csharp.Asg.Nodes.Structure {

    /// <summary>
    /// QueryBodySyntax class, which represents the structure::QueryBodySyntax node.
    /// </summary>
    [DebuggerDisplay("Id={Id}")]
#if (CSHARP_INTERNAL)
    internal
#else
    public
#endif
    class QueryBodySyntax : Columbus.Csharp.Asg.Nodes.Base.Positioned {


        // ---------- Edges ----------

        /// <summary>Container stores the id of the nodes the Clauses edge points to.</summary>
        protected LinkedList<uint> ClausesContainer;

        /// <summary>The id of the node the Continuation edge points to.</summary>
        protected uint m_Continuation;

        /// <summary>The id of the node the SelectOrGroup edge points to.</summary>
        protected uint m_SelectOrGroup;

        /// <summary>
        /// Constructor, only factory can instantiates nodes.
        /// </summary>
        /// <param name="nodeId">[in] The id of the node.</param>
        /// <param name="factory">[in] Poiter to the Factory the node belongs to.</param>
        public QueryBodySyntax(uint nodeId, Factory factory) : base(nodeId, factory) {
            ClausesContainer = new LinkedList<uint>();
            m_Continuation = 0;
            m_SelectOrGroup = 0;
        }

        /// <summary>
        /// Gives back the NodeKind of the node.
        /// </summary>
        /// <returns>Returns with the NodeKind.</returns>
        public override Types.NodeKind NodeKind {
            get { return Types.NodeKind.ndkQueryBodySyntax; }
        }


        // ---------- Reflection getter function ----------

        /// <summary>
        /// Gives back the begin iterator for the edge specified
        /// </summary>
        /// <param name="edge">[in] The multiple edge for which the iterator is requested</param>
        public override ListIterator<Columbus.Csharp.Asg.Nodes.Base.Base> GetListIteratorBegin(string edge) {
            switch(edge) {
                case "Clauses":
                    return ClausesListIteratorBegin.Convert<Columbus.Csharp.Asg.Nodes.Base.Base>();
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
                case "Clauses":
                    addClauses(nodeId);
                    return;
                default:
                    base.add(edge, nodeId);
                    return;
            }
        }


        // ---------- Edge getter function(s) ----------

        /// <summary>
        /// Gives back iterator for the Clauses edges.
        /// </summary>
        /// <returns>Returns an iterator for the Clauses edges.</returns>
        public ListIterator<Columbus.Csharp.Asg.Nodes.Structure.QueryClauseSyntax> ClausesListIteratorBegin {
            get {
                return new ListIterator<Columbus.Csharp.Asg.Nodes.Structure.QueryClauseSyntax>(ClausesContainer, fact, true);
            }
        }

        /// <summary>
        /// Gives back iterator for the Clauses edges.
        /// </summary>
        /// <returns>Returns an iterator for the Clauses edges.</returns>
        public ListIterator<Columbus.Csharp.Asg.Nodes.Structure.QueryClauseSyntax> ClausesListIteratorEnd {
            get {
                return new ListIterator<Columbus.Csharp.Asg.Nodes.Structure.QueryClauseSyntax>(ClausesContainer, fact, false);
            }
        }

        /// <summary>
        /// Tells whether the node has Clauses edges or not.
        /// </summary>
        /// <returns>Returns true if the node has at least one Clauses edge.</returns>
        public bool ClausesIsEmpty {
            get { return ClausesContainer.Count == 0; }
        }

        /// <summary>
        /// Gives back how many Clauses edges the node has.
        /// </summary>
        /// <returns>Returns with the number of Clauses edges.</returns>
        public uint ClausesSize {
            get { return (uint)(ClausesContainer.Count); }
        }

        /// <summary>
        /// Gives back the id of the node the Continuation edge points to.
        /// </summary>
        /// <returns>Returns the end point of the m_Continuation edge.</returns>
        /// <exception cref="Columbus.Csharp.Asg.CsharpException">Throws CsharpException if the edge id is invalid.</exception>
        public uint getContinuation() {
            if (fact.getIsFiltered(m_Continuation))
                return 1;
            else
                return m_Continuation;
        }

        /// <summary>
        /// Gives back the id of the node the SelectOrGroup edge points to.
        /// </summary>
        /// <returns>Returns the end point of the m_SelectOrGroup edge.</returns>
        /// <exception cref="Columbus.Csharp.Asg.CsharpException">Throws CsharpException if the edge id is invalid.</exception>
        public uint getSelectOrGroup() {
            if (fact.getIsFiltered(m_SelectOrGroup))
                return 1;
            else
                return m_SelectOrGroup;
        }


        // ---------- Edge setter function(s) ----------

        /// <summary>
        /// Adds a new Clauses edge to the node and inserts it after the other ones.
        /// </summary>
        /// <param name="node">[in] The end point of the new Clauses edge.</param>
        /// <exception cref="Columbus.Csharp.Asg.CsharpException">Throws CsharpException if there is something wrong with the given node.</exception>
        public void addClauses(Columbus.Csharp.Asg.Nodes.Structure.QueryClauseSyntax node) {
            addClauses(node.Id);
        }

        /// <summary>
        /// Adds a new Clauses edge to the node and inserts it after the other ones.
        /// </summary>
        /// <param name="nodeId">[in] The end point of the new Clauses edge.</param>
        /// <exception cref="Columbus.Csharp.Asg.CsharpException">Throws CsharpException if the given nodeId is invalid.</exception>
        public void addClauses(uint nodeId) {
            if (!fact.getExist(nodeId))
                throw new CsharpException("Columbus.Csharp.Asg.Nodes.Structure.QueryBodySyntax.addClauses(NodeId)", "The end point of the edge does not exist.");
            Columbus.Csharp.Asg.Nodes.Base.Base node = fact.getRef(nodeId);
            if (Common.getIsBaseClassKind(node.NodeKind, Types.NodeKind.ndkQueryClauseSyntax)) {
                ClausesContainer.AddLast(nodeId);
            } else {
                throw new CsharpException("Columbus.Csharp.Asg.Nodes.Structure.QueryBodySyntax.setClauses(NodeId)", "Invalid NodeKind (" + node.NodeKind.ToString() + ").");
            }
           setParentEdge(nodeId, (uint)Types.EdgeKind.edkQueryBodySyntax_Clauses);
            if (fact.ReverseEdges != null)
              fact.ReverseEdges.insertEdge(nodeId, this.Id, Types.EdgeKind.edkQueryBodySyntax_Clauses);
        }

        /// <summary>
        /// Sets the Continuation edge.
        /// </summary>
        /// <param name="nodeId">[in] The new end point of the Continuation edge or 0. With 0 the edge can be deleted.</param>
        /// <exception cref="Columbus.Csharp.Asg.CsharpException">Throws CsharpException if the nodeId is invalid.</exception>
        public void setContinuation(uint nodeId) {
            if (nodeId != 0) {
                if (!fact.getExist(nodeId))
                    throw new CsharpException("Columbus.Csharp.Asg.Nodes.Structure.QueryBodySyntax.setContinuation(NodeId)", "The end point of the edge does not exist.");

                Columbus.Csharp.Asg.Nodes.Base.Base node = fact.getRef(nodeId);
                if (Common.getIsBaseClassKind(node.NodeKind, Types.NodeKind.ndkQueryContinuationSyntax)) {
                    if (m_Continuation != 0) {
                        removeParentEdge(m_Continuation);
                    }
                    m_Continuation = nodeId;
                    setParentEdge(m_Continuation, (uint)Types.EdgeKind.edkQueryBodySyntax_Continuation);
                } else {
                    throw new CsharpException("Columbus.Csharp.Asg.Nodes.Structure.QueryBodySyntax.setContinuation(NodeId)", "Invalid NodeKind (" + node.NodeKind.ToString() + ").");
                }
            } else {
                if (m_Continuation != 0) {
                    removeParentEdge(m_Continuation);
                }
                m_Continuation = 0;
            }
        }

        /// <summary>
        /// Sets the Continuation edge.
        /// </summary>
        /// <param name="node">[in] The new end point of the Continuation edge.</param>
        /// <exception cref="Columbus.Csharp.Asg.CsharpException">Throws CsharpException if there's something wrong with the given node.</exception>
        public void setContinuation(Columbus.Csharp.Asg.Nodes.Structure.QueryContinuationSyntax node) {
            if (m_Continuation != 0) {
                removeParentEdge(m_Continuation);
            }
            m_Continuation = node.Id;
            setParentEdge(m_Continuation, (uint)Types.EdgeKind.edkQueryBodySyntax_Continuation);
        }

        /// <summary>
        /// Sets the SelectOrGroup edge.
        /// </summary>
        /// <param name="nodeId">[in] The new end point of the SelectOrGroup edge or 0. With 0 the edge can be deleted.</param>
        /// <exception cref="Columbus.Csharp.Asg.CsharpException">Throws CsharpException if the nodeId is invalid.</exception>
        public void setSelectOrGroup(uint nodeId) {
            if (nodeId != 0) {
                if (!fact.getExist(nodeId))
                    throw new CsharpException("Columbus.Csharp.Asg.Nodes.Structure.QueryBodySyntax.setSelectOrGroup(NodeId)", "The end point of the edge does not exist.");

                Columbus.Csharp.Asg.Nodes.Base.Base node = fact.getRef(nodeId);
                if (Common.getIsBaseClassKind(node.NodeKind, Types.NodeKind.ndkSelectOrGroupClauseSyntax)) {
                    if (m_SelectOrGroup != 0) {
                        removeParentEdge(m_SelectOrGroup);
                    }
                    m_SelectOrGroup = nodeId;
                    setParentEdge(m_SelectOrGroup, (uint)Types.EdgeKind.edkQueryBodySyntax_SelectOrGroup);
                } else {
                    throw new CsharpException("Columbus.Csharp.Asg.Nodes.Structure.QueryBodySyntax.setSelectOrGroup(NodeId)", "Invalid NodeKind (" + node.NodeKind.ToString() + ").");
                }
            } else {
                if (m_SelectOrGroup != 0) {
                    removeParentEdge(m_SelectOrGroup);
                }
                m_SelectOrGroup = 0;
            }
        }

        /// <summary>
        /// Sets the SelectOrGroup edge.
        /// </summary>
        /// <param name="node">[in] The new end point of the SelectOrGroup edge.</param>
        /// <exception cref="Columbus.Csharp.Asg.CsharpException">Throws CsharpException if there's something wrong with the given node.</exception>
        public void setSelectOrGroup(Columbus.Csharp.Asg.Nodes.Structure.SelectOrGroupClauseSyntax node) {
            if (m_SelectOrGroup != 0) {
                removeParentEdge(m_SelectOrGroup);
            }
            m_SelectOrGroup = node.Id;
            setParentEdge(m_SelectOrGroup, (uint)Types.EdgeKind.edkQueryBodySyntax_SelectOrGroup);
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

            io.writeUInt4(m_Continuation);
            io.writeUInt4(m_SelectOrGroup);


            foreach (var Clauses in ClausesContainer) {
              io.writeUInt4(Clauses);
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

            m_Continuation =  binIo.readUInt4();
            if (m_Continuation != 0)
              setParentEdge(m_Continuation,(uint)Types.EdgeKind.edkQueryBodySyntax_Continuation);

            m_SelectOrGroup =  binIo.readUInt4();
            if (m_SelectOrGroup != 0)
              setParentEdge(m_SelectOrGroup,(uint)Types.EdgeKind.edkQueryBodySyntax_SelectOrGroup);

            uint _id;

            _id = binIo.readUInt4();
            while (_id != 0) {
              ClausesContainer.AddLast(_id);
              setParentEdge(_id, (uint)Types.EdgeKind.edkQueryBodySyntax_Clauses);
              _id = binIo.readUInt4();
            }
        }

    }

}
