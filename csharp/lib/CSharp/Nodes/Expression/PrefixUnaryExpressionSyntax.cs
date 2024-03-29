using System;
using System.Text;
using System.Diagnostics;
using System.Collections.Generic;

namespace Columbus.Csharp.Asg.Nodes.Expression {

    /// <summary>
    /// PrefixUnaryExpressionSyntax class, which represents the expression::PrefixUnaryExpressionSyntax node.
    /// </summary>
    [DebuggerDisplay("Id={Id}")]
#if (CSHARP_INTERNAL)
    internal
#else
    public
#endif
    class PrefixUnaryExpressionSyntax : ExpressionSyntax {


        // ---------- Edges ----------

        /// <summary>The id of the node the Operand edge points to.</summary>
        protected uint m_Operand;

        /// <summary>The id of the node the OverloadedOperatorCall edge points to.</summary>
        protected uint m_OverloadedOperatorCall;

        /// <summary>
        /// Constructor, only factory can instantiates nodes.
        /// </summary>
        /// <param name="nodeId">[in] The id of the node.</param>
        /// <param name="factory">[in] Poiter to the Factory the node belongs to.</param>
        public PrefixUnaryExpressionSyntax(uint nodeId, Factory factory) : base(nodeId, factory) {
            m_Operand = 0;
            m_OverloadedOperatorCall = 0;
        }

        /// <summary>
        /// Gives back the NodeKind of the node.
        /// </summary>
        /// <returns>Returns with the NodeKind.</returns>
        public override Types.NodeKind NodeKind {
            get { return Types.NodeKind.ndkPrefixUnaryExpressionSyntax; }
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
        /// Gives back the id of the node the Operand edge points to.
        /// </summary>
        /// <returns>Returns the end point of the m_Operand edge.</returns>
        /// <exception cref="Columbus.Csharp.Asg.CsharpException">Throws CsharpException if the edge id is invalid.</exception>
        public uint getOperand() {
            if (fact.getIsFiltered(m_Operand))
                return 1;
            else
                return m_Operand;
        }

        /// <summary>
        /// Gives back the id of the node the OverloadedOperatorCall edge points to.
        /// </summary>
        /// <returns>Returns the end point of the m_OverloadedOperatorCall edge.</returns>
        /// <exception cref="Columbus.Csharp.Asg.CsharpException">Throws CsharpException if the edge id is invalid.</exception>
        public uint getOverloadedOperatorCall() {
            if (fact.getIsFiltered(m_OverloadedOperatorCall))
                return 1;
            else
                return m_OverloadedOperatorCall;
        }


        // ---------- Edge setter function(s) ----------

        /// <summary>
        /// Sets the Operand edge.
        /// </summary>
        /// <param name="nodeId">[in] The new end point of the Operand edge or 0. With 0 the edge can be deleted.</param>
        /// <exception cref="Columbus.Csharp.Asg.CsharpException">Throws CsharpException if the nodeId is invalid.</exception>
        public void setOperand(uint nodeId) {
            if (nodeId != 0) {
                if (!fact.getExist(nodeId))
                    throw new CsharpException("Columbus.Csharp.Asg.Nodes.Expression.PrefixUnaryExpressionSyntax.setOperand(NodeId)", "The end point of the edge does not exist.");

                Columbus.Csharp.Asg.Nodes.Base.Base node = fact.getRef(nodeId);
                if (Common.getIsBaseClassKind(node.NodeKind, Types.NodeKind.ndkExpressionSyntax)) {
                    if (m_Operand != 0) {
                        removeParentEdge(m_Operand);
                    }
                    m_Operand = nodeId;
                    setParentEdge(m_Operand, (uint)Types.EdgeKind.edkPrefixUnaryExpressionSyntax_Operand);
                } else {
                    throw new CsharpException("Columbus.Csharp.Asg.Nodes.Expression.PrefixUnaryExpressionSyntax.setOperand(NodeId)", "Invalid NodeKind (" + node.NodeKind.ToString() + ").");
                }
            } else {
                if (m_Operand != 0) {
                    removeParentEdge(m_Operand);
                }
                m_Operand = 0;
            }
        }

        /// <summary>
        /// Sets the Operand edge.
        /// </summary>
        /// <param name="node">[in] The new end point of the Operand edge.</param>
        /// <exception cref="Columbus.Csharp.Asg.CsharpException">Throws CsharpException if there's something wrong with the given node.</exception>
        public void setOperand(Columbus.Csharp.Asg.Nodes.Expression.ExpressionSyntax node) {
            if (m_Operand != 0) {
                removeParentEdge(m_Operand);
            }
            m_Operand = node.Id;
            setParentEdge(m_Operand, (uint)Types.EdgeKind.edkPrefixUnaryExpressionSyntax_Operand);
        }

        /// <summary>
        /// Sets the OverloadedOperatorCall edge.
        /// </summary>
        /// <param name="nodeId">[in] The new end point of the OverloadedOperatorCall edge or 0. With 0 the edge can be deleted.</param>
        /// <exception cref="Columbus.Csharp.Asg.CsharpException">Throws CsharpException if the nodeId is invalid.</exception>
        public void setOverloadedOperatorCall(uint nodeId) {
            if (nodeId != 0) {
                if (!fact.getExist(nodeId))
                    throw new CsharpException("Columbus.Csharp.Asg.Nodes.Expression.PrefixUnaryExpressionSyntax.setOverloadedOperatorCall(NodeId)", "The end point of the edge does not exist.");

                Columbus.Csharp.Asg.Nodes.Base.Base node = fact.getRef(nodeId);
                if (Common.getIsBaseClassKind(node.NodeKind, Types.NodeKind.ndkOperatorDeclarationSyntax)) {
                    if (m_OverloadedOperatorCall != 0) {
                    }
                    m_OverloadedOperatorCall = nodeId;
                } else {
                    throw new CsharpException("Columbus.Csharp.Asg.Nodes.Expression.PrefixUnaryExpressionSyntax.setOverloadedOperatorCall(NodeId)", "Invalid NodeKind (" + node.NodeKind.ToString() + ").");
                }
            } else {
                if (m_OverloadedOperatorCall != 0) {
                }
                m_OverloadedOperatorCall = 0;
            }
        }

        /// <summary>
        /// Sets the OverloadedOperatorCall edge.
        /// </summary>
        /// <param name="node">[in] The new end point of the OverloadedOperatorCall edge.</param>
        /// <exception cref="Columbus.Csharp.Asg.CsharpException">Throws CsharpException if there's something wrong with the given node.</exception>
        public void setOverloadedOperatorCall(Columbus.Csharp.Asg.Nodes.Structure.OperatorDeclarationSyntax node) {
            if (m_OverloadedOperatorCall != 0) {
            }
            m_OverloadedOperatorCall = node.Id;
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

            io.writeUInt4(m_Operand);
            io.writeUInt4(m_OverloadedOperatorCall);

        }

        /// <summary>
        /// Loads the node.
        /// </summary>
        /// <param name="io">[in] The node is read from io.</param>
        /// <exception cref="Columbus.ColumbusIOException">Throws ColumbusIOException if there is something wrong with the file.</exception>
        public override void load(IO binIo) {
            base.load(binIo);

            m_Operand =  binIo.readUInt4();
            if (m_Operand != 0)
              setParentEdge(m_Operand,(uint)Types.EdgeKind.edkPrefixUnaryExpressionSyntax_Operand);

            m_OverloadedOperatorCall =  binIo.readUInt4();

        }

    }

}
