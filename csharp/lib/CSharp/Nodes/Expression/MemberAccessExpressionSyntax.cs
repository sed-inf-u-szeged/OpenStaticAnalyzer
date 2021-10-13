using System;
using System.Text;
using System.Diagnostics;
using System.Collections.Generic;

namespace Columbus.Csharp.Asg.Nodes.Expression {

    /// <summary>
    /// MemberAccessExpressionSyntax class, which represents the expression::MemberAccessExpressionSyntax node.
    /// </summary>
    [DebuggerDisplay("Id={Id}")]
#if (CSHARP_INTERNAL)
    internal
#else
    public
#endif
    class MemberAccessExpressionSyntax : ExpressionSyntax {


        // ---------- Edges ----------

        /// <summary>The id of the node the Expression edge points to.</summary>
        protected uint m_Expression;

        /// <summary>The id of the node the Name edge points to.</summary>
        protected uint m_Name;

        /// <summary>
        /// Constructor, only factory can instantiates nodes.
        /// </summary>
        /// <param name="nodeId">[in] The id of the node.</param>
        /// <param name="factory">[in] Poiter to the Factory the node belongs to.</param>
        public MemberAccessExpressionSyntax(uint nodeId, Factory factory) : base(nodeId, factory) {
            m_Expression = 0;
            m_Name = 0;
        }

        /// <summary>
        /// Gives back the NodeKind of the node.
        /// </summary>
        /// <returns>Returns with the NodeKind.</returns>
        public override Types.NodeKind NodeKind {
            get { return Types.NodeKind.ndkMemberAccessExpressionSyntax; }
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
        /// Gives back the id of the node the Expression edge points to.
        /// </summary>
        /// <returns>Returns the end point of the m_Expression edge.</returns>
        /// <exception cref="Columbus.Csharp.Asg.CsharpException">Throws CsharpException if the edge id is invalid.</exception>
        public uint getExpression() {
            if (fact.getIsFiltered(m_Expression))
                return 1;
            else
                return m_Expression;
        }

        /// <summary>
        /// Gives back the id of the node the Name edge points to.
        /// </summary>
        /// <returns>Returns the end point of the m_Name edge.</returns>
        /// <exception cref="Columbus.Csharp.Asg.CsharpException">Throws CsharpException if the edge id is invalid.</exception>
        public uint getName() {
            if (fact.getIsFiltered(m_Name))
                return 1;
            else
                return m_Name;
        }


        // ---------- Edge setter function(s) ----------

        /// <summary>
        /// Sets the Expression edge.
        /// </summary>
        /// <param name="nodeId">[in] The new end point of the Expression edge or 0. With 0 the edge can be deleted.</param>
        /// <exception cref="Columbus.Csharp.Asg.CsharpException">Throws CsharpException if the nodeId is invalid.</exception>
        public void setExpression(uint nodeId) {
            if (nodeId != 0) {
                if (!fact.getExist(nodeId))
                    throw new CsharpException("Columbus.Csharp.Asg.Nodes.Expression.MemberAccessExpressionSyntax.setExpression(NodeId)", "The end point of the edge does not exist.");

                Columbus.Csharp.Asg.Nodes.Base.Base node = fact.getRef(nodeId);
                if (Common.getIsBaseClassKind(node.NodeKind, Types.NodeKind.ndkExpressionSyntax)) {
                    if (m_Expression != 0) {
                        removeParentEdge(m_Expression);
                    }
                    m_Expression = nodeId;
                    setParentEdge(m_Expression, (uint)Types.EdgeKind.edkMemberAccessExpressionSyntax_Expression);
                } else {
                    throw new CsharpException("Columbus.Csharp.Asg.Nodes.Expression.MemberAccessExpressionSyntax.setExpression(NodeId)", "Invalid NodeKind (" + node.NodeKind.ToString() + ").");
                }
            } else {
                if (m_Expression != 0) {
                    removeParentEdge(m_Expression);
                }
                m_Expression = 0;
            }
        }

        /// <summary>
        /// Sets the Expression edge.
        /// </summary>
        /// <param name="node">[in] The new end point of the Expression edge.</param>
        /// <exception cref="Columbus.Csharp.Asg.CsharpException">Throws CsharpException if there's something wrong with the given node.</exception>
        public void setExpression(Columbus.Csharp.Asg.Nodes.Expression.ExpressionSyntax node) {
            if (m_Expression != 0) {
                removeParentEdge(m_Expression);
            }
            m_Expression = node.Id;
            setParentEdge(m_Expression, (uint)Types.EdgeKind.edkMemberAccessExpressionSyntax_Expression);
        }

        /// <summary>
        /// Sets the Name edge.
        /// </summary>
        /// <param name="nodeId">[in] The new end point of the Name edge or 0. With 0 the edge can be deleted.</param>
        /// <exception cref="Columbus.Csharp.Asg.CsharpException">Throws CsharpException if the nodeId is invalid.</exception>
        public void setName(uint nodeId) {
            if (nodeId != 0) {
                if (!fact.getExist(nodeId))
                    throw new CsharpException("Columbus.Csharp.Asg.Nodes.Expression.MemberAccessExpressionSyntax.setName(NodeId)", "The end point of the edge does not exist.");

                Columbus.Csharp.Asg.Nodes.Base.Base node = fact.getRef(nodeId);
                if (Common.getIsBaseClassKind(node.NodeKind, Types.NodeKind.ndkSimpleNameSyntax)) {
                    if (m_Name != 0) {
                        removeParentEdge(m_Name);
                    }
                    m_Name = nodeId;
                    setParentEdge(m_Name, (uint)Types.EdgeKind.edkMemberAccessExpressionSyntax_Name);
                } else {
                    throw new CsharpException("Columbus.Csharp.Asg.Nodes.Expression.MemberAccessExpressionSyntax.setName(NodeId)", "Invalid NodeKind (" + node.NodeKind.ToString() + ").");
                }
            } else {
                if (m_Name != 0) {
                    removeParentEdge(m_Name);
                }
                m_Name = 0;
            }
        }

        /// <summary>
        /// Sets the Name edge.
        /// </summary>
        /// <param name="node">[in] The new end point of the Name edge.</param>
        /// <exception cref="Columbus.Csharp.Asg.CsharpException">Throws CsharpException if there's something wrong with the given node.</exception>
        public void setName(Columbus.Csharp.Asg.Nodes.Expression.SimpleNameSyntax node) {
            if (m_Name != 0) {
                removeParentEdge(m_Name);
            }
            m_Name = node.Id;
            setParentEdge(m_Name, (uint)Types.EdgeKind.edkMemberAccessExpressionSyntax_Name);
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

            io.writeUInt4(m_Expression);
            io.writeUInt4(m_Name);

        }

        /// <summary>
        /// Loads the node.
        /// </summary>
        /// <param name="io">[in] The node is read from io.</param>
        /// <exception cref="Columbus.ColumbusIOException">Throws ColumbusIOException if there is something wrong with the file.</exception>
        public override void load(IO binIo) {
            base.load(binIo);

            m_Expression =  binIo.readUInt4();
            if (m_Expression != 0)
              setParentEdge(m_Expression,(uint)Types.EdgeKind.edkMemberAccessExpressionSyntax_Expression);

            m_Name =  binIo.readUInt4();
            if (m_Name != 0)
              setParentEdge(m_Name,(uint)Types.EdgeKind.edkMemberAccessExpressionSyntax_Name);

        }

    }

}
