using System;
using System.Text;
using System.Diagnostics;
using System.Collections.Generic;

namespace Columbus.Csharp.Asg.Nodes.Expression {

    /// <summary>
    /// ObjectCreationExpressionSyntax class, which represents the expression::ObjectCreationExpressionSyntax node.
    /// </summary>
    [DebuggerDisplay("Id={Id}")]
#if (CSHARP_INTERNAL)
    internal
#else
    public
#endif
    class ObjectCreationExpressionSyntax : ExpressionSyntax {


        // ---------- Edges ----------

        /// <summary>The id of the node the ArgumentList edge points to.</summary>
        protected uint m_ArgumentList;

        /// <summary>The id of the node the ConstructorCall edge points to.</summary>
        protected uint m_ConstructorCall;

        /// <summary>The id of the node the Initializer edge points to.</summary>
        protected uint m_Initializer;

        /// <summary>The id of the node the Type edge points to.</summary>
        protected uint m_Type;

        /// <summary>
        /// Constructor, only factory can instantiates nodes.
        /// </summary>
        /// <param name="nodeId">[in] The id of the node.</param>
        /// <param name="factory">[in] Poiter to the Factory the node belongs to.</param>
        public ObjectCreationExpressionSyntax(uint nodeId, Factory factory) : base(nodeId, factory) {
            m_ArgumentList = 0;
            m_ConstructorCall = 0;
            m_Initializer = 0;
            m_Type = 0;
        }

        /// <summary>
        /// Gives back the NodeKind of the node.
        /// </summary>
        /// <returns>Returns with the NodeKind.</returns>
        public override Types.NodeKind NodeKind {
            get { return Types.NodeKind.ndkObjectCreationExpressionSyntax; }
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
        /// Gives back the id of the node the ConstructorCall edge points to.
        /// </summary>
        /// <returns>Returns the end point of the m_ConstructorCall edge.</returns>
        /// <exception cref="Columbus.Csharp.Asg.CsharpException">Throws CsharpException if the edge id is invalid.</exception>
        public uint getConstructorCall() {
            if (fact.getIsFiltered(m_ConstructorCall))
                return 1;
            else
                return m_ConstructorCall;
        }

        /// <summary>
        /// Gives back the id of the node the Initializer edge points to.
        /// </summary>
        /// <returns>Returns the end point of the m_Initializer edge.</returns>
        /// <exception cref="Columbus.Csharp.Asg.CsharpException">Throws CsharpException if the edge id is invalid.</exception>
        public uint getInitializer() {
            if (fact.getIsFiltered(m_Initializer))
                return 1;
            else
                return m_Initializer;
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
        /// Sets the ArgumentList edge.
        /// </summary>
        /// <param name="nodeId">[in] The new end point of the ArgumentList edge or 0. With 0 the edge can be deleted.</param>
        /// <exception cref="Columbus.Csharp.Asg.CsharpException">Throws CsharpException if the nodeId is invalid.</exception>
        public void setArgumentList(uint nodeId) {
            if (nodeId != 0) {
                if (!fact.getExist(nodeId))
                    throw new CsharpException("Columbus.Csharp.Asg.Nodes.Expression.ObjectCreationExpressionSyntax.setArgumentList(NodeId)", "The end point of the edge does not exist.");

                Columbus.Csharp.Asg.Nodes.Base.Base node = fact.getRef(nodeId);
                if (Common.getIsBaseClassKind(node.NodeKind, Types.NodeKind.ndkArgumentListSyntax)) {
                    if (m_ArgumentList != 0) {
                        removeParentEdge(m_ArgumentList);
                    }
                    m_ArgumentList = nodeId;
                    setParentEdge(m_ArgumentList, (uint)Types.EdgeKind.edkObjectCreationExpressionSyntax_ArgumentList);
                } else {
                    throw new CsharpException("Columbus.Csharp.Asg.Nodes.Expression.ObjectCreationExpressionSyntax.setArgumentList(NodeId)", "Invalid NodeKind (" + node.NodeKind.ToString() + ").");
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
            setParentEdge(m_ArgumentList, (uint)Types.EdgeKind.edkObjectCreationExpressionSyntax_ArgumentList);
        }

        /// <summary>
        /// Sets the ConstructorCall edge.
        /// </summary>
        /// <param name="nodeId">[in] The new end point of the ConstructorCall edge or 0. With 0 the edge can be deleted.</param>
        /// <exception cref="Columbus.Csharp.Asg.CsharpException">Throws CsharpException if the nodeId is invalid.</exception>
        public void setConstructorCall(uint nodeId) {
            if (nodeId != 0) {
                if (!fact.getExist(nodeId))
                    throw new CsharpException("Columbus.Csharp.Asg.Nodes.Expression.ObjectCreationExpressionSyntax.setConstructorCall(NodeId)", "The end point of the edge does not exist.");

                Columbus.Csharp.Asg.Nodes.Base.Base node = fact.getRef(nodeId);
                if (Common.getIsBaseClassKind(node.NodeKind, Types.NodeKind.ndkConstructorDeclarationSyntax)) {
                    if (m_ConstructorCall != 0) {
                    }
                    m_ConstructorCall = nodeId;
                } else {
                    throw new CsharpException("Columbus.Csharp.Asg.Nodes.Expression.ObjectCreationExpressionSyntax.setConstructorCall(NodeId)", "Invalid NodeKind (" + node.NodeKind.ToString() + ").");
                }
            } else {
                if (m_ConstructorCall != 0) {
                }
                m_ConstructorCall = 0;
            }
        }

        /// <summary>
        /// Sets the ConstructorCall edge.
        /// </summary>
        /// <param name="node">[in] The new end point of the ConstructorCall edge.</param>
        /// <exception cref="Columbus.Csharp.Asg.CsharpException">Throws CsharpException if there's something wrong with the given node.</exception>
        public void setConstructorCall(Columbus.Csharp.Asg.Nodes.Structure.ConstructorDeclarationSyntax node) {
            if (m_ConstructorCall != 0) {
            }
            m_ConstructorCall = node.Id;
        }

        /// <summary>
        /// Sets the Initializer edge.
        /// </summary>
        /// <param name="nodeId">[in] The new end point of the Initializer edge or 0. With 0 the edge can be deleted.</param>
        /// <exception cref="Columbus.Csharp.Asg.CsharpException">Throws CsharpException if the nodeId is invalid.</exception>
        public void setInitializer(uint nodeId) {
            if (nodeId != 0) {
                if (!fact.getExist(nodeId))
                    throw new CsharpException("Columbus.Csharp.Asg.Nodes.Expression.ObjectCreationExpressionSyntax.setInitializer(NodeId)", "The end point of the edge does not exist.");

                Columbus.Csharp.Asg.Nodes.Base.Base node = fact.getRef(nodeId);
                if (Common.getIsBaseClassKind(node.NodeKind, Types.NodeKind.ndkInitializerExpressionSyntax)) {
                    if (m_Initializer != 0) {
                        removeParentEdge(m_Initializer);
                    }
                    m_Initializer = nodeId;
                    setParentEdge(m_Initializer, (uint)Types.EdgeKind.edkObjectCreationExpressionSyntax_Initializer);
                } else {
                    throw new CsharpException("Columbus.Csharp.Asg.Nodes.Expression.ObjectCreationExpressionSyntax.setInitializer(NodeId)", "Invalid NodeKind (" + node.NodeKind.ToString() + ").");
                }
            } else {
                if (m_Initializer != 0) {
                    removeParentEdge(m_Initializer);
                }
                m_Initializer = 0;
            }
        }

        /// <summary>
        /// Sets the Initializer edge.
        /// </summary>
        /// <param name="node">[in] The new end point of the Initializer edge.</param>
        /// <exception cref="Columbus.Csharp.Asg.CsharpException">Throws CsharpException if there's something wrong with the given node.</exception>
        public void setInitializer(Columbus.Csharp.Asg.Nodes.Expression.InitializerExpressionSyntax node) {
            if (m_Initializer != 0) {
                removeParentEdge(m_Initializer);
            }
            m_Initializer = node.Id;
            setParentEdge(m_Initializer, (uint)Types.EdgeKind.edkObjectCreationExpressionSyntax_Initializer);
        }

        /// <summary>
        /// Sets the Type edge.
        /// </summary>
        /// <param name="nodeId">[in] The new end point of the Type edge or 0. With 0 the edge can be deleted.</param>
        /// <exception cref="Columbus.Csharp.Asg.CsharpException">Throws CsharpException if the nodeId is invalid.</exception>
        public void setType(uint nodeId) {
            if (nodeId != 0) {
                if (!fact.getExist(nodeId))
                    throw new CsharpException("Columbus.Csharp.Asg.Nodes.Expression.ObjectCreationExpressionSyntax.setType(NodeId)", "The end point of the edge does not exist.");

                Columbus.Csharp.Asg.Nodes.Base.Base node = fact.getRef(nodeId);
                if (Common.getIsBaseClassKind(node.NodeKind, Types.NodeKind.ndkTypeSyntax)) {
                    if (m_Type != 0) {
                        removeParentEdge(m_Type);
                    }
                    m_Type = nodeId;
                    setParentEdge(m_Type, (uint)Types.EdgeKind.edkObjectCreationExpressionSyntax_Type);
                } else {
                    throw new CsharpException("Columbus.Csharp.Asg.Nodes.Expression.ObjectCreationExpressionSyntax.setType(NodeId)", "Invalid NodeKind (" + node.NodeKind.ToString() + ").");
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
            setParentEdge(m_Type, (uint)Types.EdgeKind.edkObjectCreationExpressionSyntax_Type);
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
            io.writeUInt4(m_ConstructorCall);
            io.writeUInt4(m_Initializer);
            io.writeUInt4(m_Type);

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
              setParentEdge(m_ArgumentList,(uint)Types.EdgeKind.edkObjectCreationExpressionSyntax_ArgumentList);

            m_ConstructorCall =  binIo.readUInt4();

            m_Initializer =  binIo.readUInt4();
            if (m_Initializer != 0)
              setParentEdge(m_Initializer,(uint)Types.EdgeKind.edkObjectCreationExpressionSyntax_Initializer);

            m_Type =  binIo.readUInt4();
            if (m_Type != 0)
              setParentEdge(m_Type,(uint)Types.EdgeKind.edkObjectCreationExpressionSyntax_Type);

        }

    }

}
