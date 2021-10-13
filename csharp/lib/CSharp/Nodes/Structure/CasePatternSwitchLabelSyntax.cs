using System;
using System.Text;
using System.Diagnostics;
using System.Collections.Generic;

namespace Columbus.Csharp.Asg.Nodes.Structure {

    /// <summary>
    /// CasePatternSwitchLabelSyntax class, which represents the structure::CasePatternSwitchLabelSyntax node.
    /// </summary>
    [DebuggerDisplay("Id={Id}")]
#if (CSHARP_INTERNAL)
    internal
#else
    public
#endif
    class CasePatternSwitchLabelSyntax : SwitchLabelSyntax {


        // ---------- Edges ----------

        /// <summary>The id of the node the Pattern edge points to.</summary>
        protected uint m_Pattern;

        /// <summary>The id of the node the WhenClause edge points to.</summary>
        protected uint m_WhenClause;

        /// <summary>
        /// Constructor, only factory can instantiates nodes.
        /// </summary>
        /// <param name="nodeId">[in] The id of the node.</param>
        /// <param name="factory">[in] Poiter to the Factory the node belongs to.</param>
        public CasePatternSwitchLabelSyntax(uint nodeId, Factory factory) : base(nodeId, factory) {
            m_Pattern = 0;
            m_WhenClause = 0;
        }

        /// <summary>
        /// Gives back the NodeKind of the node.
        /// </summary>
        /// <returns>Returns with the NodeKind.</returns>
        public override Types.NodeKind NodeKind {
            get { return Types.NodeKind.ndkCasePatternSwitchLabelSyntax; }
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
        /// Gives back the id of the node the Pattern edge points to.
        /// </summary>
        /// <returns>Returns the end point of the m_Pattern edge.</returns>
        /// <exception cref="Columbus.Csharp.Asg.CsharpException">Throws CsharpException if the edge id is invalid.</exception>
        public uint getPattern() {
            if (fact.getIsFiltered(m_Pattern))
                return 1;
            else
                return m_Pattern;
        }

        /// <summary>
        /// Gives back the id of the node the WhenClause edge points to.
        /// </summary>
        /// <returns>Returns the end point of the m_WhenClause edge.</returns>
        /// <exception cref="Columbus.Csharp.Asg.CsharpException">Throws CsharpException if the edge id is invalid.</exception>
        public uint getWhenClause() {
            if (fact.getIsFiltered(m_WhenClause))
                return 1;
            else
                return m_WhenClause;
        }


        // ---------- Edge setter function(s) ----------

        /// <summary>
        /// Sets the Pattern edge.
        /// </summary>
        /// <param name="nodeId">[in] The new end point of the Pattern edge or 0. With 0 the edge can be deleted.</param>
        /// <exception cref="Columbus.Csharp.Asg.CsharpException">Throws CsharpException if the nodeId is invalid.</exception>
        public void setPattern(uint nodeId) {
            if (nodeId != 0) {
                if (!fact.getExist(nodeId))
                    throw new CsharpException("Columbus.Csharp.Asg.Nodes.Structure.CasePatternSwitchLabelSyntax.setPattern(NodeId)", "The end point of the edge does not exist.");

                Columbus.Csharp.Asg.Nodes.Base.Base node = fact.getRef(nodeId);
                if (Common.getIsBaseClassKind(node.NodeKind, Types.NodeKind.ndkPatternSyntax)) {
                    if (m_Pattern != 0) {
                        removeParentEdge(m_Pattern);
                    }
                    m_Pattern = nodeId;
                    setParentEdge(m_Pattern, (uint)Types.EdgeKind.edkCasePatternSwitchLabelSyntax_Pattern);
                } else {
                    throw new CsharpException("Columbus.Csharp.Asg.Nodes.Structure.CasePatternSwitchLabelSyntax.setPattern(NodeId)", "Invalid NodeKind (" + node.NodeKind.ToString() + ").");
                }
            } else {
                if (m_Pattern != 0) {
                    removeParentEdge(m_Pattern);
                }
                m_Pattern = 0;
            }
        }

        /// <summary>
        /// Sets the Pattern edge.
        /// </summary>
        /// <param name="node">[in] The new end point of the Pattern edge.</param>
        /// <exception cref="Columbus.Csharp.Asg.CsharpException">Throws CsharpException if there's something wrong with the given node.</exception>
        public void setPattern(Columbus.Csharp.Asg.Nodes.Structure.PatternSyntax node) {
            if (m_Pattern != 0) {
                removeParentEdge(m_Pattern);
            }
            m_Pattern = node.Id;
            setParentEdge(m_Pattern, (uint)Types.EdgeKind.edkCasePatternSwitchLabelSyntax_Pattern);
        }

        /// <summary>
        /// Sets the WhenClause edge.
        /// </summary>
        /// <param name="nodeId">[in] The new end point of the WhenClause edge or 0. With 0 the edge can be deleted.</param>
        /// <exception cref="Columbus.Csharp.Asg.CsharpException">Throws CsharpException if the nodeId is invalid.</exception>
        public void setWhenClause(uint nodeId) {
            if (nodeId != 0) {
                if (!fact.getExist(nodeId))
                    throw new CsharpException("Columbus.Csharp.Asg.Nodes.Structure.CasePatternSwitchLabelSyntax.setWhenClause(NodeId)", "The end point of the edge does not exist.");

                Columbus.Csharp.Asg.Nodes.Base.Base node = fact.getRef(nodeId);
                if (Common.getIsBaseClassKind(node.NodeKind, Types.NodeKind.ndkWhenClauseSyntax)) {
                    if (m_WhenClause != 0) {
                        removeParentEdge(m_WhenClause);
                    }
                    m_WhenClause = nodeId;
                    setParentEdge(m_WhenClause, (uint)Types.EdgeKind.edkCasePatternSwitchLabelSyntax_WhenClause);
                } else {
                    throw new CsharpException("Columbus.Csharp.Asg.Nodes.Structure.CasePatternSwitchLabelSyntax.setWhenClause(NodeId)", "Invalid NodeKind (" + node.NodeKind.ToString() + ").");
                }
            } else {
                if (m_WhenClause != 0) {
                    removeParentEdge(m_WhenClause);
                }
                m_WhenClause = 0;
            }
        }

        /// <summary>
        /// Sets the WhenClause edge.
        /// </summary>
        /// <param name="node">[in] The new end point of the WhenClause edge.</param>
        /// <exception cref="Columbus.Csharp.Asg.CsharpException">Throws CsharpException if there's something wrong with the given node.</exception>
        public void setWhenClause(Columbus.Csharp.Asg.Nodes.Structure.WhenClauseSyntax node) {
            if (m_WhenClause != 0) {
                removeParentEdge(m_WhenClause);
            }
            m_WhenClause = node.Id;
            setParentEdge(m_WhenClause, (uint)Types.EdgeKind.edkCasePatternSwitchLabelSyntax_WhenClause);
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

            io.writeUInt4(m_Pattern);
            io.writeUInt4(m_WhenClause);

        }

        /// <summary>
        /// Loads the node.
        /// </summary>
        /// <param name="io">[in] The node is read from io.</param>
        /// <exception cref="Columbus.ColumbusIOException">Throws ColumbusIOException if there is something wrong with the file.</exception>
        public override void load(IO binIo) {
            base.load(binIo);

            m_Pattern =  binIo.readUInt4();
            if (m_Pattern != 0)
              setParentEdge(m_Pattern,(uint)Types.EdgeKind.edkCasePatternSwitchLabelSyntax_Pattern);

            m_WhenClause =  binIo.readUInt4();
            if (m_WhenClause != 0)
              setParentEdge(m_WhenClause,(uint)Types.EdgeKind.edkCasePatternSwitchLabelSyntax_WhenClause);

        }

    }

}
