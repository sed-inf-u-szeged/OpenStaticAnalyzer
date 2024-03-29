using System;
using System.Text;
using System.Diagnostics;
using System.Collections.Generic;

namespace Columbus.Csharp.Asg.Nodes.Structure {

    /// <summary>
    /// InterpolationAlignmentClauseSyntax class, which represents the structure::InterpolationAlignmentClauseSyntax node.
    /// </summary>
    [DebuggerDisplay("Id={Id}")]
#if (CSHARP_INTERNAL)
    internal
#else
    public
#endif
    class InterpolationAlignmentClauseSyntax : Columbus.Csharp.Asg.Nodes.Base.Positioned {


        // ---------- Edges ----------

        /// <summary>The id of the node the Value edge points to.</summary>
        protected uint m_Value;

        /// <summary>
        /// Constructor, only factory can instantiates nodes.
        /// </summary>
        /// <param name="nodeId">[in] The id of the node.</param>
        /// <param name="factory">[in] Poiter to the Factory the node belongs to.</param>
        public InterpolationAlignmentClauseSyntax(uint nodeId, Factory factory) : base(nodeId, factory) {
            m_Value = 0;
        }

        /// <summary>
        /// Gives back the NodeKind of the node.
        /// </summary>
        /// <returns>Returns with the NodeKind.</returns>
        public override Types.NodeKind NodeKind {
            get { return Types.NodeKind.ndkInterpolationAlignmentClauseSyntax; }
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
        /// Gives back the id of the node the Value edge points to.
        /// </summary>
        /// <returns>Returns the end point of the m_Value edge.</returns>
        /// <exception cref="Columbus.Csharp.Asg.CsharpException">Throws CsharpException if the edge id is invalid.</exception>
        public uint getValue() {
            if (fact.getIsFiltered(m_Value))
                return 1;
            else
                return m_Value;
        }


        // ---------- Edge setter function(s) ----------

        /// <summary>
        /// Sets the Value edge.
        /// </summary>
        /// <param name="nodeId">[in] The new end point of the Value edge or 0. With 0 the edge can be deleted.</param>
        /// <exception cref="Columbus.Csharp.Asg.CsharpException">Throws CsharpException if the nodeId is invalid.</exception>
        public void setValue(uint nodeId) {
            if (nodeId != 0) {
                if (!fact.getExist(nodeId))
                    throw new CsharpException("Columbus.Csharp.Asg.Nodes.Structure.InterpolationAlignmentClauseSyntax.setValue(NodeId)", "The end point of the edge does not exist.");

                Columbus.Csharp.Asg.Nodes.Base.Base node = fact.getRef(nodeId);
                if (Common.getIsBaseClassKind(node.NodeKind, Types.NodeKind.ndkExpressionSyntax)) {
                    if (m_Value != 0) {
                        removeParentEdge(m_Value);
                    }
                    m_Value = nodeId;
                    setParentEdge(m_Value, (uint)Types.EdgeKind.edkInterpolationAlignmentClauseSyntax_Value);
                } else {
                    throw new CsharpException("Columbus.Csharp.Asg.Nodes.Structure.InterpolationAlignmentClauseSyntax.setValue(NodeId)", "Invalid NodeKind (" + node.NodeKind.ToString() + ").");
                }
            } else {
                if (m_Value != 0) {
                    removeParentEdge(m_Value);
                }
                m_Value = 0;
            }
        }

        /// <summary>
        /// Sets the Value edge.
        /// </summary>
        /// <param name="node">[in] The new end point of the Value edge.</param>
        /// <exception cref="Columbus.Csharp.Asg.CsharpException">Throws CsharpException if there's something wrong with the given node.</exception>
        public void setValue(Columbus.Csharp.Asg.Nodes.Expression.ExpressionSyntax node) {
            if (m_Value != 0) {
                removeParentEdge(m_Value);
            }
            m_Value = node.Id;
            setParentEdge(m_Value, (uint)Types.EdgeKind.edkInterpolationAlignmentClauseSyntax_Value);
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

            io.writeUInt4(m_Value);

        }

        /// <summary>
        /// Loads the node.
        /// </summary>
        /// <param name="io">[in] The node is read from io.</param>
        /// <exception cref="Columbus.ColumbusIOException">Throws ColumbusIOException if there is something wrong with the file.</exception>
        public override void load(IO binIo) {
            base.load(binIo);

            m_Value =  binIo.readUInt4();
            if (m_Value != 0)
              setParentEdge(m_Value,(uint)Types.EdgeKind.edkInterpolationAlignmentClauseSyntax_Value);

        }

    }

}
