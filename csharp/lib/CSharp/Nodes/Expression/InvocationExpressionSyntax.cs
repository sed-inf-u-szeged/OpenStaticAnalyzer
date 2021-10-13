using System;
using System.Text;
using System.Diagnostics;
using System.Collections.Generic;

namespace Columbus.Csharp.Asg.Nodes.Expression {

    /// <summary>
    /// InvocationExpressionSyntax class, which represents the expression::InvocationExpressionSyntax node.
    /// </summary>
    [DebuggerDisplay("Id={Id}")]
#if (CSHARP_INTERNAL)
    internal
#else
    public
#endif
    class InvocationExpressionSyntax : ExpressionSyntax {


        // ---------- Edges ----------

        /// <summary>The id of the node the ArgumentList edge points to.</summary>
        protected uint m_ArgumentList;

        /// <summary>The id of the node the Expression edge points to.</summary>
        protected uint m_Expression;

        /// <summary>The id of the node the LocalFunctionCall edge points to.</summary>
        protected uint m_LocalFunctionCall;

        /// <summary>The id of the node the MethodCall edge points to.</summary>
        protected uint m_MethodCall;

        /// <summary>
        /// Constructor, only factory can instantiates nodes.
        /// </summary>
        /// <param name="nodeId">[in] The id of the node.</param>
        /// <param name="factory">[in] Poiter to the Factory the node belongs to.</param>
        public InvocationExpressionSyntax(uint nodeId, Factory factory) : base(nodeId, factory) {
            m_ArgumentList = 0;
            m_Expression = 0;
            m_LocalFunctionCall = 0;
            m_MethodCall = 0;
        }

        /// <summary>
        /// Gives back the NodeKind of the node.
        /// </summary>
        /// <returns>Returns with the NodeKind.</returns>
        public override Types.NodeKind NodeKind {
            get { return Types.NodeKind.ndkInvocationExpressionSyntax; }
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
        /// Gives back the id of the node the ArgumentList edge points to.
        /// </summary>
        /// <returns>Returns the end point of the m_ArgumentList edge.</returns>
        /// <exception cref="Columbus.Csharp.Asg.CsharpException">Throws CsharpException if the edge id is invalid.</exception>
        public uint getArgumentList() {
            if (fact.getIsFiltered(m_ArgumentList))
                return 1;
            else
                return m_ArgumentList;
        }

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
        /// Gives back the id of the node the LocalFunctionCall edge points to.
        /// </summary>
        /// <returns>Returns the end point of the m_LocalFunctionCall edge.</returns>
        /// <exception cref="Columbus.Csharp.Asg.CsharpException">Throws CsharpException if the edge id is invalid.</exception>
        public uint getLocalFunctionCall() {
            if (fact.getIsFiltered(m_LocalFunctionCall))
                return 1;
            else
                return m_LocalFunctionCall;
        }

        /// <summary>
        /// Gives back the id of the node the MethodCall edge points to.
        /// </summary>
        /// <returns>Returns the end point of the m_MethodCall edge.</returns>
        /// <exception cref="Columbus.Csharp.Asg.CsharpException">Throws CsharpException if the edge id is invalid.</exception>
        public uint getMethodCall() {
            if (fact.getIsFiltered(m_MethodCall))
                return 1;
            else
                return m_MethodCall;
        }


        // ---------- Edge setter function(s) ----------

        /// <summary>
        /// Sets the ArgumentList edge.
        /// </summary>
        /// <param name="nodeId">[in] The new end point of the ArgumentList edge or 0. With 0 the edge can be deleted.</param>
        /// <exception cref="Columbus.Csharp.Asg.CsharpException">Throws CsharpException if the nodeId is invalid.</exception>
        public void setArgumentList(uint nodeId) {
            if (nodeId != 0) {
                if (!fact.getExist(nodeId))
                    throw new CsharpException("Columbus.Csharp.Asg.Nodes.Expression.InvocationExpressionSyntax.setArgumentList(NodeId)", "The end point of the edge does not exist.");

                Columbus.Csharp.Asg.Nodes.Base.Base node = fact.getRef(nodeId);
                if (Common.getIsBaseClassKind(node.NodeKind, Types.NodeKind.ndkArgumentListSyntax)) {
                    if (m_ArgumentList != 0) {
                        removeParentEdge(m_ArgumentList);
                    }
                    m_ArgumentList = nodeId;
                    setParentEdge(m_ArgumentList, (uint)Types.EdgeKind.edkInvocationExpressionSyntax_ArgumentList);
                } else {
                    throw new CsharpException("Columbus.Csharp.Asg.Nodes.Expression.InvocationExpressionSyntax.setArgumentList(NodeId)", "Invalid NodeKind (" + node.NodeKind.ToString() + ").");
                }
            } else {
                if (m_ArgumentList != 0) {
                    removeParentEdge(m_ArgumentList);
                }
                m_ArgumentList = 0;
            }
        }

        /// <summary>
        /// Sets the ArgumentList edge.
        /// </summary>
        /// <param name="node">[in] The new end point of the ArgumentList edge.</param>
        /// <exception cref="Columbus.Csharp.Asg.CsharpException">Throws CsharpException if there's something wrong with the given node.</exception>
        public void setArgumentList(Columbus.Csharp.Asg.Nodes.Structure.ArgumentListSyntax node) {
            if (m_ArgumentList != 0) {
                removeParentEdge(m_ArgumentList);
            }
            m_ArgumentList = node.Id;
            setParentEdge(m_ArgumentList, (uint)Types.EdgeKind.edkInvocationExpressionSyntax_ArgumentList);
        }

        /// <summary>
        /// Sets the Expression edge.
        /// </summary>
        /// <param name="nodeId">[in] The new end point of the Expression edge or 0. With 0 the edge can be deleted.</param>
        /// <exception cref="Columbus.Csharp.Asg.CsharpException">Throws CsharpException if the nodeId is invalid.</exception>
        public void setExpression(uint nodeId) {
            if (nodeId != 0) {
                if (!fact.getExist(nodeId))
                    throw new CsharpException("Columbus.Csharp.Asg.Nodes.Expression.InvocationExpressionSyntax.setExpression(NodeId)", "The end point of the edge does not exist.");

                Columbus.Csharp.Asg.Nodes.Base.Base node = fact.getRef(nodeId);
                if (Common.getIsBaseClassKind(node.NodeKind, Types.NodeKind.ndkExpressionSyntax)) {
                    if (m_Expression != 0) {
                        removeParentEdge(m_Expression);
                    }
                    m_Expression = nodeId;
                    setParentEdge(m_Expression, (uint)Types.EdgeKind.edkInvocationExpressionSyntax_Expression);
                } else {
                    throw new CsharpException("Columbus.Csharp.Asg.Nodes.Expression.InvocationExpressionSyntax.setExpression(NodeId)", "Invalid NodeKind (" + node.NodeKind.ToString() + ").");
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
            setParentEdge(m_Expression, (uint)Types.EdgeKind.edkInvocationExpressionSyntax_Expression);
        }

        /// <summary>
        /// Sets the LocalFunctionCall edge.
        /// </summary>
        /// <param name="nodeId">[in] The new end point of the LocalFunctionCall edge or 0. With 0 the edge can be deleted.</param>
        /// <exception cref="Columbus.Csharp.Asg.CsharpException">Throws CsharpException if the nodeId is invalid.</exception>
        public void setLocalFunctionCall(uint nodeId) {
            if (nodeId != 0) {
                if (!fact.getExist(nodeId))
                    throw new CsharpException("Columbus.Csharp.Asg.Nodes.Expression.InvocationExpressionSyntax.setLocalFunctionCall(NodeId)", "The end point of the edge does not exist.");

                Columbus.Csharp.Asg.Nodes.Base.Base node = fact.getRef(nodeId);
                if (Common.getIsBaseClassKind(node.NodeKind, Types.NodeKind.ndkLocalFunctionStatementSyntax)) {
                    if (m_LocalFunctionCall != 0) {
                    }
                    m_LocalFunctionCall = nodeId;
                } else {
                    throw new CsharpException("Columbus.Csharp.Asg.Nodes.Expression.InvocationExpressionSyntax.setLocalFunctionCall(NodeId)", "Invalid NodeKind (" + node.NodeKind.ToString() + ").");
                }
            } else {
                if (m_LocalFunctionCall != 0) {
                }
                m_LocalFunctionCall = 0;
            }
        }

        /// <summary>
        /// Sets the LocalFunctionCall edge.
        /// </summary>
        /// <param name="node">[in] The new end point of the LocalFunctionCall edge.</param>
        /// <exception cref="Columbus.Csharp.Asg.CsharpException">Throws CsharpException if there's something wrong with the given node.</exception>
        public void setLocalFunctionCall(Columbus.Csharp.Asg.Nodes.Statement.LocalFunctionStatementSyntax node) {
            if (m_LocalFunctionCall != 0) {
            }
            m_LocalFunctionCall = node.Id;
        }

        /// <summary>
        /// Sets the MethodCall edge.
        /// </summary>
        /// <param name="nodeId">[in] The new end point of the MethodCall edge or 0. With 0 the edge can be deleted.</param>
        /// <exception cref="Columbus.Csharp.Asg.CsharpException">Throws CsharpException if the nodeId is invalid.</exception>
        public void setMethodCall(uint nodeId) {
            if (nodeId != 0) {
                if (!fact.getExist(nodeId))
                    throw new CsharpException("Columbus.Csharp.Asg.Nodes.Expression.InvocationExpressionSyntax.setMethodCall(NodeId)", "The end point of the edge does not exist.");

                Columbus.Csharp.Asg.Nodes.Base.Base node = fact.getRef(nodeId);
                if (Common.getIsBaseClassKind(node.NodeKind, Types.NodeKind.ndkMethodDeclarationSyntax)) {
                    if (m_MethodCall != 0) {
                    }
                    m_MethodCall = nodeId;
                } else {
                    throw new CsharpException("Columbus.Csharp.Asg.Nodes.Expression.InvocationExpressionSyntax.setMethodCall(NodeId)", "Invalid NodeKind (" + node.NodeKind.ToString() + ").");
                }
            } else {
                if (m_MethodCall != 0) {
                }
                m_MethodCall = 0;
            }
        }

        /// <summary>
        /// Sets the MethodCall edge.
        /// </summary>
        /// <param name="node">[in] The new end point of the MethodCall edge.</param>
        /// <exception cref="Columbus.Csharp.Asg.CsharpException">Throws CsharpException if there's something wrong with the given node.</exception>
        public void setMethodCall(Columbus.Csharp.Asg.Nodes.Structure.MethodDeclarationSyntax node) {
            if (m_MethodCall != 0) {
            }
            m_MethodCall = node.Id;
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

            io.writeUInt4(m_ArgumentList);
            io.writeUInt4(m_Expression);
            io.writeUInt4(m_LocalFunctionCall);
            io.writeUInt4(m_MethodCall);

        }

        /// <summary>
        /// Loads the node.
        /// </summary>
        /// <param name="io">[in] The node is read from io.</param>
        /// <exception cref="Columbus.ColumbusIOException">Throws ColumbusIOException if there is something wrong with the file.</exception>
        public override void load(IO binIo) {
            base.load(binIo);

            m_ArgumentList =  binIo.readUInt4();
            if (m_ArgumentList != 0)
              setParentEdge(m_ArgumentList,(uint)Types.EdgeKind.edkInvocationExpressionSyntax_ArgumentList);

            m_Expression =  binIo.readUInt4();
            if (m_Expression != 0)
              setParentEdge(m_Expression,(uint)Types.EdgeKind.edkInvocationExpressionSyntax_Expression);

            m_LocalFunctionCall =  binIo.readUInt4();

            m_MethodCall =  binIo.readUInt4();

        }

    }

}
