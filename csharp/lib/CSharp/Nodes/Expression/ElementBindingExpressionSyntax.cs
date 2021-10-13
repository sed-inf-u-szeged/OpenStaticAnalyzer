using System;
using System.Text;
using System.Diagnostics;
using System.Collections.Generic;

namespace Columbus.Csharp.Asg.Nodes.Expression {

    /// <summary>
    /// ElementBindingExpressionSyntax class, which represents the expression::ElementBindingExpressionSyntax node.
    /// </summary>
    [DebuggerDisplay("Id={Id}")]
#if (CSHARP_INTERNAL)
    internal
#else
    public
#endif
    class ElementBindingExpressionSyntax : ExpressionSyntax {


        // ---------- Edges ----------

        /// <summary>The id of the node the ArgumentList edge points to.</summary>
        protected uint m_ArgumentList;

        /// <summary>
        /// Constructor, only factory can instantiates nodes.
        /// </summary>
        /// <param name="nodeId">[in] The id of the node.</param>
        /// <param name="factory">[in] Poiter to the Factory the node belongs to.</param>
        public ElementBindingExpressionSyntax(uint nodeId, Factory factory) : base(nodeId, factory) {
            m_ArgumentList = 0;
        }

        /// <summary>
        /// Gives back the NodeKind of the node.
        /// </summary>
        /// <returns>Returns with the NodeKind.</returns>
        public override Types.NodeKind NodeKind {
            get { return Types.NodeKind.ndkElementBindingExpressionSyntax; }
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


        // ---------- Edge setter function(s) ----------

        /// <summary>
        /// Sets the ArgumentList edge.
        /// </summary>
        /// <param name="nodeId">[in] The new end point of the ArgumentList edge or 0. With 0 the edge can be deleted.</param>
        /// <exception cref="Columbus.Csharp.Asg.CsharpException">Throws CsharpException if the nodeId is invalid.</exception>
        public void setArgumentList(uint nodeId) {
            if (nodeId != 0) {
                if (!fact.getExist(nodeId))
                    throw new CsharpException("Columbus.Csharp.Asg.Nodes.Expression.ElementBindingExpressionSyntax.setArgumentList(NodeId)", "The end point of the edge does not exist.");

                Columbus.Csharp.Asg.Nodes.Base.Base node = fact.getRef(nodeId);
                if (Common.getIsBaseClassKind(node.NodeKind, Types.NodeKind.ndkBracketedArgumentListSyntax)) {
                    if (m_ArgumentList != 0) {
                        removeParentEdge(m_ArgumentList);
                    }
                    m_ArgumentList = nodeId;
                    setParentEdge(m_ArgumentList, (uint)Types.EdgeKind.edkElementBindingExpressionSyntax_ArgumentList);
                } else {
                    throw new CsharpException("Columbus.Csharp.Asg.Nodes.Expression.ElementBindingExpressionSyntax.setArgumentList(NodeId)", "Invalid NodeKind (" + node.NodeKind.ToString() + ").");
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
        public void setArgumentList(Columbus.Csharp.Asg.Nodes.Structure.BracketedArgumentListSyntax node) {
            if (m_ArgumentList != 0) {
                removeParentEdge(m_ArgumentList);
            }
            m_ArgumentList = node.Id;
            setParentEdge(m_ArgumentList, (uint)Types.EdgeKind.edkElementBindingExpressionSyntax_ArgumentList);
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
              setParentEdge(m_ArgumentList,(uint)Types.EdgeKind.edkElementBindingExpressionSyntax_ArgumentList);

        }

    }

}
