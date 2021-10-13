using System;
using System.Text;
using System.Diagnostics;
using System.Collections.Generic;

namespace Columbus.Csharp.Asg.Nodes.Expression {

    /// <summary>
    /// ImplicitArrayCreationExpressionSyntax class, which represents the expression::ImplicitArrayCreationExpressionSyntax node.
    /// </summary>
    [DebuggerDisplay("Id={Id}")]
#if (CSHARP_INTERNAL)
    internal
#else
    public
#endif
    class ImplicitArrayCreationExpressionSyntax : ExpressionSyntax {


        // ---------- Edges ----------

        /// <summary>The id of the node the Initializer edge points to.</summary>
        protected uint m_Initializer;

        /// <summary>
        /// Constructor, only factory can instantiates nodes.
        /// </summary>
        /// <param name="nodeId">[in] The id of the node.</param>
        /// <param name="factory">[in] Poiter to the Factory the node belongs to.</param>
        public ImplicitArrayCreationExpressionSyntax(uint nodeId, Factory factory) : base(nodeId, factory) {
            m_Initializer = 0;
        }

        /// <summary>
        /// Gives back the NodeKind of the node.
        /// </summary>
        /// <returns>Returns with the NodeKind.</returns>
        public override Types.NodeKind NodeKind {
            get { return Types.NodeKind.ndkImplicitArrayCreationExpressionSyntax; }
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


        // ---------- Edge setter function(s) ----------

        /// <summary>
        /// Sets the Initializer edge.
        /// </summary>
        /// <param name="nodeId">[in] The new end point of the Initializer edge or 0. With 0 the edge can be deleted.</param>
        /// <exception cref="Columbus.Csharp.Asg.CsharpException">Throws CsharpException if the nodeId is invalid.</exception>
        public void setInitializer(uint nodeId) {
            if (nodeId != 0) {
                if (!fact.getExist(nodeId))
                    throw new CsharpException("Columbus.Csharp.Asg.Nodes.Expression.ImplicitArrayCreationExpressionSyntax.setInitializer(NodeId)", "The end point of the edge does not exist.");

                Columbus.Csharp.Asg.Nodes.Base.Base node = fact.getRef(nodeId);
                if (Common.getIsBaseClassKind(node.NodeKind, Types.NodeKind.ndkInitializerExpressionSyntax)) {
                    if (m_Initializer != 0) {
                        removeParentEdge(m_Initializer);
                    }
                    m_Initializer = nodeId;
                    setParentEdge(m_Initializer, (uint)Types.EdgeKind.edkImplicitArrayCreationExpressionSyntax_Initializer);
                } else {
                    throw new CsharpException("Columbus.Csharp.Asg.Nodes.Expression.ImplicitArrayCreationExpressionSyntax.setInitializer(NodeId)", "Invalid NodeKind (" + node.NodeKind.ToString() + ").");
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
            setParentEdge(m_Initializer, (uint)Types.EdgeKind.edkImplicitArrayCreationExpressionSyntax_Initializer);
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

            io.writeUInt4(m_Initializer);

        }

        /// <summary>
        /// Loads the node.
        /// </summary>
        /// <param name="io">[in] The node is read from io.</param>
        /// <exception cref="Columbus.ColumbusIOException">Throws ColumbusIOException if there is something wrong with the file.</exception>
        public override void load(IO binIo) {
            base.load(binIo);

            m_Initializer =  binIo.readUInt4();
            if (m_Initializer != 0)
              setParentEdge(m_Initializer,(uint)Types.EdgeKind.edkImplicitArrayCreationExpressionSyntax_Initializer);

        }

    }

}
