using System;
using System.Text;
using System.Diagnostics;
using System.Collections.Generic;

namespace Columbus.Csharp.Asg.Nodes.Expression {

    /// <summary>
    /// BinaryExpressionSyntax class, which represents the expression::BinaryExpressionSyntax node.
    /// </summary>
    [DebuggerDisplay("Id={Id}")]
#if (CSHARP_INTERNAL)
    internal
#else
    public
#endif
    class BinaryExpressionSyntax : ExpressionSyntax {


        // ---------- Edges ----------

        /// <summary>The id of the node the Left edge points to.</summary>
        protected uint m_Left;

        /// <summary>The id of the node the OverloadedOperatorCall edge points to.</summary>
        protected uint m_OverloadedOperatorCall;

        /// <summary>The id of the node the Right edge points to.</summary>
        protected uint m_Right;

        /// <summary>
        /// Constructor, only factory can instantiates nodes.
        /// </summary>
        /// <param name="nodeId">[in] The id of the node.</param>
        /// <param name="factory">[in] Poiter to the Factory the node belongs to.</param>
        public BinaryExpressionSyntax(uint nodeId, Factory factory) : base(nodeId, factory) {
            m_Left = 0;
            m_OverloadedOperatorCall = 0;
            m_Right = 0;
        }

        /// <summary>
        /// Gives back the NodeKind of the node.
        /// </summary>
        /// <returns>Returns with the NodeKind.</returns>
        public override Types.NodeKind NodeKind {
            get { return Types.NodeKind.ndkBinaryExpressionSyntax; }
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
        /// Gives back the id of the node the Left edge points to.
        /// </summary>
        /// <returns>Returns the end point of the m_Left edge.</returns>
        /// <exception cref="Columbus.Csharp.Asg.CsharpException">Throws CsharpException if the edge id is invalid.</exception>
        public uint getLeft() {
            if (fact.getIsFiltered(m_Left))
                return 1;
            else
                return m_Left;
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

        /// <summary>
        /// Gives back the id of the node the Right edge points to.
        /// </summary>
        /// <returns>Returns the end point of the m_Right edge.</returns>
        /// <exception cref="Columbus.Csharp.Asg.CsharpException">Throws CsharpException if the edge id is invalid.</exception>
        public uint getRight() {
            if (fact.getIsFiltered(m_Right))
                return 1;
            else
                return m_Right;
        }


        // ---------- Edge setter function(s) ----------

        /// <summary>
        /// Sets the Left edge.
        /// </summary>
        /// <param name="nodeId">[in] The new end point of the Left edge or 0. With 0 the edge can be deleted.</param>
        /// <exception cref="Columbus.Csharp.Asg.CsharpException">Throws CsharpException if the nodeId is invalid.</exception>
        public void setLeft(uint nodeId) {
            if (nodeId != 0) {
                if (!fact.getExist(nodeId))
                    throw new CsharpException("Columbus.Csharp.Asg.Nodes.Expression.BinaryExpressionSyntax.setLeft(NodeId)", "The end point of the edge does not exist.");

                Columbus.Csharp.Asg.Nodes.Base.Base node = fact.getRef(nodeId);
                if (Common.getIsBaseClassKind(node.NodeKind, Types.NodeKind.ndkExpressionSyntax)) {
                    if (m_Left != 0) {
                        removeParentEdge(m_Left);
                    }
                    m_Left = nodeId;
                    setParentEdge(m_Left, (uint)Types.EdgeKind.edkBinaryExpressionSyntax_Left);
                } else {
                    throw new CsharpException("Columbus.Csharp.Asg.Nodes.Expression.BinaryExpressionSyntax.setLeft(NodeId)", "Invalid NodeKind (" + node.NodeKind.ToString() + ").");
                }
            } else {
                if (m_Left != 0) {
                    removeParentEdge(m_Left);
                }
                m_Left = 0;
            }
        }

        /// <summary>
        /// Sets the Left edge.
        /// </summary>
        /// <param name="node">[in] The new end point of the Left edge.</param>
        /// <exception cref="Columbus.Csharp.Asg.CsharpException">Throws CsharpException if there's something wrong with the given node.</exception>
        public void setLeft(Columbus.Csharp.Asg.Nodes.Expression.ExpressionSyntax node) {
            if (m_Left != 0) {
                removeParentEdge(m_Left);
            }
            m_Left = node.Id;
            setParentEdge(m_Left, (uint)Types.EdgeKind.edkBinaryExpressionSyntax_Left);
        }

        /// <summary>
        /// Sets the OverloadedOperatorCall edge.
        /// </summary>
        /// <param name="nodeId">[in] The new end point of the OverloadedOperatorCall edge or 0. With 0 the edge can be deleted.</param>
        /// <exception cref="Columbus.Csharp.Asg.CsharpException">Throws CsharpException if the nodeId is invalid.</exception>
        public void setOverloadedOperatorCall(uint nodeId) {
            if (nodeId != 0) {
                if (!fact.getExist(nodeId))
                    throw new CsharpException("Columbus.Csharp.Asg.Nodes.Expression.BinaryExpressionSyntax.setOverloadedOperatorCall(NodeId)", "The end point of the edge does not exist.");

                Columbus.Csharp.Asg.Nodes.Base.Base node = fact.getRef(nodeId);
                if (Common.getIsBaseClassKind(node.NodeKind, Types.NodeKind.ndkOperatorDeclarationSyntax)) {
                    if (m_OverloadedOperatorCall != 0) {
                    }
                    m_OverloadedOperatorCall = nodeId;
                } else {
                    throw new CsharpException("Columbus.Csharp.Asg.Nodes.Expression.BinaryExpressionSyntax.setOverloadedOperatorCall(NodeId)", "Invalid NodeKind (" + node.NodeKind.ToString() + ").");
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

        /// <summary>
        /// Sets the Right edge.
        /// </summary>
        /// <param name="nodeId">[in] The new end point of the Right edge or 0. With 0 the edge can be deleted.</param>
        /// <exception cref="Columbus.Csharp.Asg.CsharpException">Throws CsharpException if the nodeId is invalid.</exception>
        public void setRight(uint nodeId) {
            if (nodeId != 0) {
                if (!fact.getExist(nodeId))
                    throw new CsharpException("Columbus.Csharp.Asg.Nodes.Expression.BinaryExpressionSyntax.setRight(NodeId)", "The end point of the edge does not exist.");

                Columbus.Csharp.Asg.Nodes.Base.Base node = fact.getRef(nodeId);
                if (Common.getIsBaseClassKind(node.NodeKind, Types.NodeKind.ndkExpressionSyntax)) {
                    if (m_Right != 0) {
                        removeParentEdge(m_Right);
                    }
                    m_Right = nodeId;
                    setParentEdge(m_Right, (uint)Types.EdgeKind.edkBinaryExpressionSyntax_Right);
                } else {
                    throw new CsharpException("Columbus.Csharp.Asg.Nodes.Expression.BinaryExpressionSyntax.setRight(NodeId)", "Invalid NodeKind (" + node.NodeKind.ToString() + ").");
                }
            } else {
                if (m_Right != 0) {
                    removeParentEdge(m_Right);
                }
                m_Right = 0;
            }
        }

        /// <summary>
        /// Sets the Right edge.
        /// </summary>
        /// <param name="node">[in] The new end point of the Right edge.</param>
        /// <exception cref="Columbus.Csharp.Asg.CsharpException">Throws CsharpException if there's something wrong with the given node.</exception>
        public void setRight(Columbus.Csharp.Asg.Nodes.Expression.ExpressionSyntax node) {
            if (m_Right != 0) {
                removeParentEdge(m_Right);
            }
            m_Right = node.Id;
            setParentEdge(m_Right, (uint)Types.EdgeKind.edkBinaryExpressionSyntax_Right);
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

            io.writeUInt4(m_Left);
            io.writeUInt4(m_OverloadedOperatorCall);
            io.writeUInt4(m_Right);

        }

        /// <summary>
        /// Loads the node.
        /// </summary>
        /// <param name="io">[in] The node is read from io.</param>
        /// <exception cref="Columbus.ColumbusIOException">Throws ColumbusIOException if there is something wrong with the file.</exception>
        public override void load(IO binIo) {
            base.load(binIo);

            m_Left =  binIo.readUInt4();
            if (m_Left != 0)
              setParentEdge(m_Left,(uint)Types.EdgeKind.edkBinaryExpressionSyntax_Left);

            m_OverloadedOperatorCall =  binIo.readUInt4();

            m_Right =  binIo.readUInt4();
            if (m_Right != 0)
              setParentEdge(m_Right,(uint)Types.EdgeKind.edkBinaryExpressionSyntax_Right);

        }

    }

}
