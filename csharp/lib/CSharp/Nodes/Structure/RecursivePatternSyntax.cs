using System;
using System.Text;
using System.Diagnostics;
using System.Collections.Generic;

namespace Columbus.Csharp.Asg.Nodes.Structure {

    /// <summary>
    /// RecursivePatternSyntax class, which represents the structure::RecursivePatternSyntax node.
    /// </summary>
    [DebuggerDisplay("Id={Id}")]
#if (CSHARP_INTERNAL)
    internal
#else
    public
#endif
    class RecursivePatternSyntax : PatternSyntax {


        // ---------- Edges ----------

        /// <summary>The id of the node the Designation edge points to.</summary>
        protected uint m_Designation;

        /// <summary>The id of the node the PositionalPatternClause edge points to.</summary>
        protected uint m_PositionalPatternClause;

        /// <summary>The id of the node the PropertyPatternClause edge points to.</summary>
        protected uint m_PropertyPatternClause;

        /// <summary>The id of the node the Type edge points to.</summary>
        protected uint m_Type;

        /// <summary>
        /// Constructor, only factory can instantiates nodes.
        /// </summary>
        /// <param name="nodeId">[in] The id of the node.</param>
        /// <param name="factory">[in] Poiter to the Factory the node belongs to.</param>
        public RecursivePatternSyntax(uint nodeId, Factory factory) : base(nodeId, factory) {
            m_Designation = 0;
            m_PositionalPatternClause = 0;
            m_PropertyPatternClause = 0;
            m_Type = 0;
        }

        /// <summary>
        /// Gives back the NodeKind of the node.
        /// </summary>
        /// <returns>Returns with the NodeKind.</returns>
        public override Types.NodeKind NodeKind {
            get { return Types.NodeKind.ndkRecursivePatternSyntax; }
        }


        // ---------- Reflection getter function ----------

        /// <summary>
        /// Gives back the begin iterator for the edge specified
        /// </summary>
        /// <param name="edge">[in] The multiple edge for which the iterator is requested</param>
        public override ListIterator<Columbus.Csharp.Asg.Nodes.Base.Base> GetListIteratorBegin(string edge) {
            switch(edge) {
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
                default:
                    base.add(edge, nodeId);
                    return;
            }
        }


        // ---------- Edge getter function(s) ----------

        /// <summary>
        /// Gives back the id of the node the Designation edge points to.
        /// </summary>
        /// <returns>Returns the end point of the m_Designation edge.</returns>
        /// <exception cref="Columbus.Csharp.Asg.CsharpException">Throws CsharpException if the edge id is invalid.</exception>
        public uint getDesignation() {
            if (fact.getIsFiltered(m_Designation))
                return 1;
            else
                return m_Designation;
        }

        /// <summary>
        /// Gives back the id of the node the PositionalPatternClause edge points to.
        /// </summary>
        /// <returns>Returns the end point of the m_PositionalPatternClause edge.</returns>
        /// <exception cref="Columbus.Csharp.Asg.CsharpException">Throws CsharpException if the edge id is invalid.</exception>
        public uint getPositionalPatternClause() {
            if (fact.getIsFiltered(m_PositionalPatternClause))
                return 1;
            else
                return m_PositionalPatternClause;
        }

        /// <summary>
        /// Gives back the id of the node the PropertyPatternClause edge points to.
        /// </summary>
        /// <returns>Returns the end point of the m_PropertyPatternClause edge.</returns>
        /// <exception cref="Columbus.Csharp.Asg.CsharpException">Throws CsharpException if the edge id is invalid.</exception>
        public uint getPropertyPatternClause() {
            if (fact.getIsFiltered(m_PropertyPatternClause))
                return 1;
            else
                return m_PropertyPatternClause;
        }

        /// <summary>
        /// Gives back the id of the node the Type edge points to.
        /// </summary>
        /// <returns>Returns the end point of the m_Type edge.</returns>
        /// <exception cref="Columbus.Csharp.Asg.CsharpException">Throws CsharpException if the edge id is invalid.</exception>
        public uint getType() {
            if (fact.getIsFiltered(m_Type))
                return 1;
            else
                return m_Type;
        }


        // ---------- Edge setter function(s) ----------

        /// <summary>
        /// Sets the Designation edge.
        /// </summary>
        /// <param name="nodeId">[in] The new end point of the Designation edge or 0. With 0 the edge can be deleted.</param>
        /// <exception cref="Columbus.Csharp.Asg.CsharpException">Throws CsharpException if the nodeId is invalid.</exception>
        public void setDesignation(uint nodeId) {
            if (nodeId != 0) {
                if (!fact.getExist(nodeId))
                    throw new CsharpException("Columbus.Csharp.Asg.Nodes.Structure.RecursivePatternSyntax.setDesignation(NodeId)", "The end point of the edge does not exist.");

                Columbus.Csharp.Asg.Nodes.Base.Base node = fact.getRef(nodeId);
                if (Common.getIsBaseClassKind(node.NodeKind, Types.NodeKind.ndkVariableDesignationSyntax)) {
                    if (m_Designation != 0) {
                        removeParentEdge(m_Designation);
                    }
                    m_Designation = nodeId;
                    setParentEdge(m_Designation, (uint)Types.EdgeKind.edkRecursivePatternSyntax_Designation);
                } else {
                    throw new CsharpException("Columbus.Csharp.Asg.Nodes.Structure.RecursivePatternSyntax.setDesignation(NodeId)", "Invalid NodeKind (" + node.NodeKind.ToString() + ").");
                }
            } else {
                if (m_Designation != 0) {
                    removeParentEdge(m_Designation);
                }
                m_Designation = 0;
            }
        }

        /// <summary>
        /// Sets the Designation edge.
        /// </summary>
        /// <param name="node">[in] The new end point of the Designation edge.</param>
        /// <exception cref="Columbus.Csharp.Asg.CsharpException">Throws CsharpException if there's something wrong with the given node.</exception>
        public void setDesignation(Columbus.Csharp.Asg.Nodes.Structure.VariableDesignationSyntax node) {
            if (m_Designation != 0) {
                removeParentEdge(m_Designation);
            }
            m_Designation = node.Id;
            setParentEdge(m_Designation, (uint)Types.EdgeKind.edkRecursivePatternSyntax_Designation);
        }

        /// <summary>
        /// Sets the PositionalPatternClause edge.
        /// </summary>
        /// <param name="nodeId">[in] The new end point of the PositionalPatternClause edge or 0. With 0 the edge can be deleted.</param>
        /// <exception cref="Columbus.Csharp.Asg.CsharpException">Throws CsharpException if the nodeId is invalid.</exception>
        public void setPositionalPatternClause(uint nodeId) {
            if (nodeId != 0) {
                if (!fact.getExist(nodeId))
                    throw new CsharpException("Columbus.Csharp.Asg.Nodes.Structure.RecursivePatternSyntax.setPositionalPatternClause(NodeId)", "The end point of the edge does not exist.");

                Columbus.Csharp.Asg.Nodes.Base.Base node = fact.getRef(nodeId);
                if (Common.getIsBaseClassKind(node.NodeKind, Types.NodeKind.ndkPositionalPatternClauseSyntax)) {
                    if (m_PositionalPatternClause != 0) {
                        removeParentEdge(m_PositionalPatternClause);
                    }
                    m_PositionalPatternClause = nodeId;
                    setParentEdge(m_PositionalPatternClause, (uint)Types.EdgeKind.edkRecursivePatternSyntax_PositionalPatternClause);
                } else {
                    throw new CsharpException("Columbus.Csharp.Asg.Nodes.Structure.RecursivePatternSyntax.setPositionalPatternClause(NodeId)", "Invalid NodeKind (" + node.NodeKind.ToString() + ").");
                }
            } else {
                if (m_PositionalPatternClause != 0) {
                    removeParentEdge(m_PositionalPatternClause);
                }
                m_PositionalPatternClause = 0;
            }
        }

        /// <summary>
        /// Sets the PositionalPatternClause edge.
        /// </summary>
        /// <param name="node">[in] The new end point of the PositionalPatternClause edge.</param>
        /// <exception cref="Columbus.Csharp.Asg.CsharpException">Throws CsharpException if there's something wrong with the given node.</exception>
        public void setPositionalPatternClause(Columbus.Csharp.Asg.Nodes.Structure.PositionalPatternClauseSyntax node) {
            if (m_PositionalPatternClause != 0) {
                removeParentEdge(m_PositionalPatternClause);
            }
            m_PositionalPatternClause = node.Id;
            setParentEdge(m_PositionalPatternClause, (uint)Types.EdgeKind.edkRecursivePatternSyntax_PositionalPatternClause);
        }

        /// <summary>
        /// Sets the PropertyPatternClause edge.
        /// </summary>
        /// <param name="nodeId">[in] The new end point of the PropertyPatternClause edge or 0. With 0 the edge can be deleted.</param>
        /// <exception cref="Columbus.Csharp.Asg.CsharpException">Throws CsharpException if the nodeId is invalid.</exception>
        public void setPropertyPatternClause(uint nodeId) {
            if (nodeId != 0) {
                if (!fact.getExist(nodeId))
                    throw new CsharpException("Columbus.Csharp.Asg.Nodes.Structure.RecursivePatternSyntax.setPropertyPatternClause(NodeId)", "The end point of the edge does not exist.");

                Columbus.Csharp.Asg.Nodes.Base.Base node = fact.getRef(nodeId);
                if (Common.getIsBaseClassKind(node.NodeKind, Types.NodeKind.ndkPropertyPatternClauseSyntax)) {
                    if (m_PropertyPatternClause != 0) {
                        removeParentEdge(m_PropertyPatternClause);
                    }
                    m_PropertyPatternClause = nodeId;
                    setParentEdge(m_PropertyPatternClause, (uint)Types.EdgeKind.edkRecursivePatternSyntax_PropertyPatternClause);
                } else {
                    throw new CsharpException("Columbus.Csharp.Asg.Nodes.Structure.RecursivePatternSyntax.setPropertyPatternClause(NodeId)", "Invalid NodeKind (" + node.NodeKind.ToString() + ").");
                }
            } else {
                if (m_PropertyPatternClause != 0) {
                    removeParentEdge(m_PropertyPatternClause);
                }
                m_PropertyPatternClause = 0;
            }
        }

        /// <summary>
        /// Sets the PropertyPatternClause edge.
        /// </summary>
        /// <param name="node">[in] The new end point of the PropertyPatternClause edge.</param>
        /// <exception cref="Columbus.Csharp.Asg.CsharpException">Throws CsharpException if there's something wrong with the given node.</exception>
        public void setPropertyPatternClause(Columbus.Csharp.Asg.Nodes.Structure.PropertyPatternClauseSyntax node) {
            if (m_PropertyPatternClause != 0) {
                removeParentEdge(m_PropertyPatternClause);
            }
            m_PropertyPatternClause = node.Id;
            setParentEdge(m_PropertyPatternClause, (uint)Types.EdgeKind.edkRecursivePatternSyntax_PropertyPatternClause);
        }

        /// <summary>
        /// Sets the Type edge.
        /// </summary>
        /// <param name="nodeId">[in] The new end point of the Type edge or 0. With 0 the edge can be deleted.</param>
        /// <exception cref="Columbus.Csharp.Asg.CsharpException">Throws CsharpException if the nodeId is invalid.</exception>
        public void setType(uint nodeId) {
            if (nodeId != 0) {
                if (!fact.getExist(nodeId))
                    throw new CsharpException("Columbus.Csharp.Asg.Nodes.Structure.RecursivePatternSyntax.setType(NodeId)", "The end point of the edge does not exist.");

                Columbus.Csharp.Asg.Nodes.Base.Base node = fact.getRef(nodeId);
                if (Common.getIsBaseClassKind(node.NodeKind, Types.NodeKind.ndkTypeSyntax)) {
                    if (m_Type != 0) {
                        removeParentEdge(m_Type);
                    }
                    m_Type = nodeId;
                    setParentEdge(m_Type, (uint)Types.EdgeKind.edkRecursivePatternSyntax_Type);
                } else {
                    throw new CsharpException("Columbus.Csharp.Asg.Nodes.Structure.RecursivePatternSyntax.setType(NodeId)", "Invalid NodeKind (" + node.NodeKind.ToString() + ").");
                }
            } else {
                if (m_Type != 0) {
                    removeParentEdge(m_Type);
                }
                m_Type = 0;
            }
        }

        /// <summary>
        /// Sets the Type edge.
        /// </summary>
        /// <param name="node">[in] The new end point of the Type edge.</param>
        /// <exception cref="Columbus.Csharp.Asg.CsharpException">Throws CsharpException if there's something wrong with the given node.</exception>
        public void setType(Columbus.Csharp.Asg.Nodes.Expression.TypeSyntax node) {
            if (m_Type != 0) {
                removeParentEdge(m_Type);
            }
            m_Type = node.Id;
            setParentEdge(m_Type, (uint)Types.EdgeKind.edkRecursivePatternSyntax_Type);
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

            io.writeUInt4(m_Designation);
            io.writeUInt4(m_PositionalPatternClause);
            io.writeUInt4(m_PropertyPatternClause);
            io.writeUInt4(m_Type);

        }

        /// <summary>
        /// Loads the node.
        /// </summary>
        /// <param name="io">[in] The node is read from io.</param>
        /// <exception cref="Columbus.ColumbusIOException">Throws ColumbusIOException if there is something wrong with the file.</exception>
        public override void load(IO binIo) {
            base.load(binIo);

            m_Designation =  binIo.readUInt4();
            if (m_Designation != 0)
              setParentEdge(m_Designation,(uint)Types.EdgeKind.edkRecursivePatternSyntax_Designation);

            m_PositionalPatternClause =  binIo.readUInt4();
            if (m_PositionalPatternClause != 0)
              setParentEdge(m_PositionalPatternClause,(uint)Types.EdgeKind.edkRecursivePatternSyntax_PositionalPatternClause);

            m_PropertyPatternClause =  binIo.readUInt4();
            if (m_PropertyPatternClause != 0)
              setParentEdge(m_PropertyPatternClause,(uint)Types.EdgeKind.edkRecursivePatternSyntax_PropertyPatternClause);

            m_Type =  binIo.readUInt4();
            if (m_Type != 0)
              setParentEdge(m_Type,(uint)Types.EdgeKind.edkRecursivePatternSyntax_Type);

        }

    }

}
