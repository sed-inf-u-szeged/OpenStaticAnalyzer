using System;
using System.Text;
using System.Diagnostics;
using System.Collections.Generic;

namespace Columbus.Csharp.Asg.Nodes.Expression {

    /// <summary>
    /// ConditionalExpressionSyntax class, which represents the expression::ConditionalExpressionSyntax node.
    /// </summary>
    [DebuggerDisplay("Id={Id}")]
#if (CSHARP_INTERNAL)
    internal
#else
    public
#endif
    class ConditionalExpressionSyntax : ExpressionSyntax {


        // ---------- Edges ----------

        /// <summary>The id of the node the Condition edge points to.</summary>
        protected uint m_Condition;

        /// <summary>The id of the node the WhenFalse edge points to.</summary>
        protected uint m_WhenFalse;

        /// <summary>The id of the node the WhenTrue edge points to.</summary>
        protected uint m_WhenTrue;

        /// <summary>
        /// Constructor, only factory can instantiates nodes.
        /// </summary>
        /// <param name="nodeId">[in] The id of the node.</param>
        /// <param name="factory">[in] Poiter to the Factory the node belongs to.</param>
        public ConditionalExpressionSyntax(uint nodeId, Factory factory) : base(nodeId, factory) {
            m_Condition = 0;
            m_WhenFalse = 0;
            m_WhenTrue = 0;
        }

        /// <summary>
        /// Gives back the NodeKind of the node.
        /// </summary>
        /// <returns>Returns with the NodeKind.</returns>
        public override Types.NodeKind NodeKind {
            get { return Types.NodeKind.ndkConditionalExpressionSyntax; }
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
        /// Gives back the id of the node the Condition edge points to.
        /// </summary>
        /// <returns>Returns the end point of the m_Condition edge.</returns>
        /// <exception cref="Columbus.Csharp.Asg.CsharpException">Throws CsharpException if the edge id is invalid.</exception>
        public uint getCondition() {
            if (fact.getIsFiltered(m_Condition))
                return 1;
            else
                return m_Condition;
        }

        /// <summary>
        /// Gives back the id of the node the WhenFalse edge points to.
        /// </summary>
        /// <returns>Returns the end point of the m_WhenFalse edge.</returns>
        /// <exception cref="Columbus.Csharp.Asg.CsharpException">Throws CsharpException if the edge id is invalid.</exception>
        public uint getWhenFalse() {
            if (fact.getIsFiltered(m_WhenFalse))
                return 1;
            else
                return m_WhenFalse;
        }

        /// <summary>
        /// Gives back the id of the node the WhenTrue edge points to.
        /// </summary>
        /// <returns>Returns the end point of the m_WhenTrue edge.</returns>
        /// <exception cref="Columbus.Csharp.Asg.CsharpException">Throws CsharpException if the edge id is invalid.</exception>
        public uint getWhenTrue() {
            if (fact.getIsFiltered(m_WhenTrue))
                return 1;
            else
                return m_WhenTrue;
        }


        // ---------- Edge setter function(s) ----------

        /// <summary>
        /// Sets the Condition edge.
        /// </summary>
        /// <param name="nodeId">[in] The new end point of the Condition edge or 0. With 0 the edge can be deleted.</param>
        /// <exception cref="Columbus.Csharp.Asg.CsharpException">Throws CsharpException if the nodeId is invalid.</exception>
        public void setCondition(uint nodeId) {
            if (nodeId != 0) {
                if (!fact.getExist(nodeId))
                    throw new CsharpException("Columbus.Csharp.Asg.Nodes.Expression.ConditionalExpressionSyntax.setCondition(NodeId)", "The end point of the edge does not exist.");

                Columbus.Csharp.Asg.Nodes.Base.Base node = fact.getRef(nodeId);
                if (Common.getIsBaseClassKind(node.NodeKind, Types.NodeKind.ndkExpressionSyntax)) {
                    if (m_Condition != 0) {
                        removeParentEdge(m_Condition);
                    }
                    m_Condition = nodeId;
                    setParentEdge(m_Condition, (uint)Types.EdgeKind.edkConditionalExpressionSyntax_Condition);
                } else {
                    throw new CsharpException("Columbus.Csharp.Asg.Nodes.Expression.ConditionalExpressionSyntax.setCondition(NodeId)", "Invalid NodeKind (" + node.NodeKind.ToString() + ").");
                }
            } else {
                if (m_Condition != 0) {
                    removeParentEdge(m_Condition);
                }
                m_Condition = 0;
            }
        }

        /// <summary>
        /// Sets the Condition edge.
        /// </summary>
        /// <param name="node">[in] The new end point of the Condition edge.</param>
        /// <exception cref="Columbus.Csharp.Asg.CsharpException">Throws CsharpException if there's something wrong with the given node.</exception>
        public void setCondition(Columbus.Csharp.Asg.Nodes.Expression.ExpressionSyntax node) {
            if (m_Condition != 0) {
                removeParentEdge(m_Condition);
            }
            m_Condition = node.Id;
            setParentEdge(m_Condition, (uint)Types.EdgeKind.edkConditionalExpressionSyntax_Condition);
        }

        /// <summary>
        /// Sets the WhenFalse edge.
        /// </summary>
        /// <param name="nodeId">[in] The new end point of the WhenFalse edge or 0. With 0 the edge can be deleted.</param>
        /// <exception cref="Columbus.Csharp.Asg.CsharpException">Throws CsharpException if the nodeId is invalid.</exception>
        public void setWhenFalse(uint nodeId) {
            if (nodeId != 0) {
                if (!fact.getExist(nodeId))
                    throw new CsharpException("Columbus.Csharp.Asg.Nodes.Expression.ConditionalExpressionSyntax.setWhenFalse(NodeId)", "The end point of the edge does not exist.");

                Columbus.Csharp.Asg.Nodes.Base.Base node = fact.getRef(nodeId);
                if (Common.getIsBaseClassKind(node.NodeKind, Types.NodeKind.ndkExpressionSyntax)) {
                    if (m_WhenFalse != 0) {
                        removeParentEdge(m_WhenFalse);
                    }
                    m_WhenFalse = nodeId;
                    setParentEdge(m_WhenFalse, (uint)Types.EdgeKind.edkConditionalExpressionSyntax_WhenFalse);
                } else {
                    throw new CsharpException("Columbus.Csharp.Asg.Nodes.Expression.ConditionalExpressionSyntax.setWhenFalse(NodeId)", "Invalid NodeKind (" + node.NodeKind.ToString() + ").");
                }
            } else {
                if (m_WhenFalse != 0) {
                    removeParentEdge(m_WhenFalse);
                }
                m_WhenFalse = 0;
            }
        }

        /// <summary>
        /// Sets the WhenFalse edge.
        /// </summary>
        /// <param name="node">[in] The new end point of the WhenFalse edge.</param>
        /// <exception cref="Columbus.Csharp.Asg.CsharpException">Throws CsharpException if there's something wrong with the given node.</exception>
        public void setWhenFalse(Columbus.Csharp.Asg.Nodes.Expression.ExpressionSyntax node) {
            if (m_WhenFalse != 0) {
                removeParentEdge(m_WhenFalse);
            }
            m_WhenFalse = node.Id;
            setParentEdge(m_WhenFalse, (uint)Types.EdgeKind.edkConditionalExpressionSyntax_WhenFalse);
        }

        /// <summary>
        /// Sets the WhenTrue edge.
        /// </summary>
        /// <param name="nodeId">[in] The new end point of the WhenTrue edge or 0. With 0 the edge can be deleted.</param>
        /// <exception cref="Columbus.Csharp.Asg.CsharpException">Throws CsharpException if the nodeId is invalid.</exception>
        public void setWhenTrue(uint nodeId) {
            if (nodeId != 0) {
                if (!fact.getExist(nodeId))
                    throw new CsharpException("Columbus.Csharp.Asg.Nodes.Expression.ConditionalExpressionSyntax.setWhenTrue(NodeId)", "The end point of the edge does not exist.");

                Columbus.Csharp.Asg.Nodes.Base.Base node = fact.getRef(nodeId);
                if (Common.getIsBaseClassKind(node.NodeKind, Types.NodeKind.ndkExpressionSyntax)) {
                    if (m_WhenTrue != 0) {
                        removeParentEdge(m_WhenTrue);
                    }
                    m_WhenTrue = nodeId;
                    setParentEdge(m_WhenTrue, (uint)Types.EdgeKind.edkConditionalExpressionSyntax_WhenTrue);
                } else {
                    throw new CsharpException("Columbus.Csharp.Asg.Nodes.Expression.ConditionalExpressionSyntax.setWhenTrue(NodeId)", "Invalid NodeKind (" + node.NodeKind.ToString() + ").");
                }
            } else {
                if (m_WhenTrue != 0) {
                    removeParentEdge(m_WhenTrue);
                }
                m_WhenTrue = 0;
            }
        }

        /// <summary>
        /// Sets the WhenTrue edge.
        /// </summary>
        /// <param name="node">[in] The new end point of the WhenTrue edge.</param>
        /// <exception cref="Columbus.Csharp.Asg.CsharpException">Throws CsharpException if there's something wrong with the given node.</exception>
        public void setWhenTrue(Columbus.Csharp.Asg.Nodes.Expression.ExpressionSyntax node) {
            if (m_WhenTrue != 0) {
                removeParentEdge(m_WhenTrue);
            }
            m_WhenTrue = node.Id;
            setParentEdge(m_WhenTrue, (uint)Types.EdgeKind.edkConditionalExpressionSyntax_WhenTrue);
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

            io.writeUInt4(m_Condition);
            io.writeUInt4(m_WhenFalse);
            io.writeUInt4(m_WhenTrue);

        }

        /// <summary>
        /// Loads the node.
        /// </summary>
        /// <param name="io">[in] The node is read from io.</param>
        /// <exception cref="Columbus.ColumbusIOException">Throws ColumbusIOException if there is something wrong with the file.</exception>
        public override void load(IO binIo) {
            base.load(binIo);

            m_Condition =  binIo.readUInt4();
            if (m_Condition != 0)
              setParentEdge(m_Condition,(uint)Types.EdgeKind.edkConditionalExpressionSyntax_Condition);

            m_WhenFalse =  binIo.readUInt4();
            if (m_WhenFalse != 0)
              setParentEdge(m_WhenFalse,(uint)Types.EdgeKind.edkConditionalExpressionSyntax_WhenFalse);

            m_WhenTrue =  binIo.readUInt4();
            if (m_WhenTrue != 0)
              setParentEdge(m_WhenTrue,(uint)Types.EdgeKind.edkConditionalExpressionSyntax_WhenTrue);

        }

    }

}
