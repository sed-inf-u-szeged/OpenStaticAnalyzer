using System;
using System.Text;
using System.Diagnostics;
using System.Collections.Generic;

namespace Columbus.Lim.Asg.Nodes.Type {

    /// <summary>
    /// TypeFormerType class, which represents the type::TypeFormerType node.
    /// </summary>
    [DebuggerDisplay("Id={Id}")]
#if (LIM_INTERNAL)
    internal
#else
    public
#endif
    class TypeFormerType : TypeFormer {


        // ---------- Edges ----------

        /// <summary>The id of the node the refersTo edge points to.</summary>
        protected uint m_refersTo;

        /// <summary>
        /// Constructor, only factory can instantiates nodes.
        /// </summary>
        /// <param name="nodeId">[in] The id of the node.</param>
        /// <param name="factory">[in] Poiter to the Factory the node belongs to.</param>
        public TypeFormerType(uint nodeId, Factory factory) : base(nodeId, factory) {
            m_refersTo = 0;
        }

        /// <summary>
        /// Gives back the NodeKind of the node.
        /// </summary>
        /// <returns>Returns with the NodeKind.</returns>
        public override Types.NodeKind NodeKind {
            get { return Types.NodeKind.ndkTypeFormerType; }
        }


        // ---------- Reflection getter function ----------

        /// <summary>
        /// Gives back the begin iterator for the edge specified
        /// </summary>
        /// <param name="edge">[in] The multiple edge for which the iterator is requested</param>
        public override ListIterator<Columbus.Lim.Asg.Nodes.Base.Base> GetListIteratorBegin(string edge) {
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
        /// Gives back the id of the node the refersTo edge points to.
        /// </summary>
        /// <returns>Returns the end point of the m_refersTo edge.</returns>
        /// <exception cref="Columbus.Lim.Asg.LimException">Throws LimException if the edge id is invalid.</exception>
        public uint getRefersTo() {
            if (fact.getIsFiltered(m_refersTo))
                return 1;
            else
                return m_refersTo;
        }


        // ---------- Edge setter function(s) ----------

        /// <summary>
        /// Sets the refersTo edge.
        /// </summary>
        /// <param name="nodeId">[in] The new end point of the refersTo edge or 0. With 0 the edge can be deleted.</param>
        /// <exception cref="Columbus.Lim.Asg.LimException">Throws LimException if the nodeId is invalid.</exception>
        public void setRefersTo(uint nodeId) {
            if (nodeId != 0) {
                if (!fact.getExist(nodeId))
                    throw new LimException("Columbus.Lim.Asg.Nodes.Type.TypeFormerType.setRefersTo(NodeId)", "The end point of the edge does not exist.");

                Columbus.Lim.Asg.Nodes.Base.Base node = fact.getRef(nodeId);
                if (Common.getIsBaseClassKind(node.NodeKind, Types.NodeKind.ndkSimpleType) || Common.getIsBaseClassKind(node.NodeKind, Types.NodeKind.ndkGenericParameter) || Common.getIsBaseClassKind(node.NodeKind, Types.NodeKind.ndkMethodGenericInstance) || Common.getIsBaseClassKind(node.NodeKind, Types.NodeKind.ndkClass)) {
                    if (m_refersTo != 0) {
                    }
                    m_refersTo = nodeId;
                } else {
                    throw new LimException("Columbus.Lim.Asg.Nodes.Type.TypeFormerType.setRefersTo(NodeId)", "Invalid NodeKind (" + node.NodeKind.ToString() + ").");
                }
            } else {
                if (m_refersTo != 0) {
                }
                m_refersTo = 0;
            }
        }

        /// <summary>
        /// Sets the refersTo edge.
        /// </summary>
        /// <param name="node">[in] The new end point of the refersTo edge.</param>
        /// <exception cref="Columbus.Lim.Asg.LimException">Throws LimException if there's something wrong with the given node.</exception>
        public void setRefersTo(Columbus.Lim.Asg.Nodes.Base.Base node) {
            if (Common.getIsBaseClassKind(node.NodeKind, Types.NodeKind.ndkSimpleType) || Common.getIsBaseClassKind(node.NodeKind, Types.NodeKind.ndkGenericParameter) || Common.getIsBaseClassKind(node.NodeKind, Types.NodeKind.ndkMethodGenericInstance) || Common.getIsBaseClassKind(node.NodeKind, Types.NodeKind.ndkClass)) {
                if (m_refersTo != 0) {
                }
                m_refersTo = node.Id;
            } else {
                throw new LimException("Columbus.Lim.Asg.Nodes.Type.TypeFormerType.setRefersTo(NodeId)", "Invalid NodeKind (" + node.NodeKind.ToString() + ").");
            }
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

            io.writeUInt4(m_refersTo);

        }

        /// <summary>
        /// Loads the node.
        /// </summary>
        /// <param name="io">[in] The node is read from io.</param>
        /// <exception cref="Columbus.ColumbusIOException">Throws ColumbusIOException if there is something wrong with the file.</exception>
        public override void load(IO binIo) {
            base.load(binIo);

            m_refersTo =  binIo.readUInt4();

        }

    }

}
