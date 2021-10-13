using System;
using System.Text;
using System.Diagnostics;
using System.Collections.Generic;

namespace Columbus.Csharp.Asg.Nodes.Structure {

    /// <summary>
    /// XmlNameAttributeSyntax class, which represents the structure::XmlNameAttributeSyntax node.
    /// </summary>
    [DebuggerDisplay("Id={Id}")]
#if (CSHARP_INTERNAL)
    internal
#else
    public
#endif
    class XmlNameAttributeSyntax : XmlAttributeSyntax {


        // ---------- Edges ----------

        /// <summary>The id of the node the Identifier edge points to.</summary>
        protected uint m_Identifier;

        /// <summary>
        /// Constructor, only factory can instantiates nodes.
        /// </summary>
        /// <param name="nodeId">[in] The id of the node.</param>
        /// <param name="factory">[in] Poiter to the Factory the node belongs to.</param>
        public XmlNameAttributeSyntax(uint nodeId, Factory factory) : base(nodeId, factory) {
            m_Identifier = 0;
        }

        /// <summary>
        /// Gives back the NodeKind of the node.
        /// </summary>
        /// <returns>Returns with the NodeKind.</returns>
        public override Types.NodeKind NodeKind {
            get { return Types.NodeKind.ndkXmlNameAttributeSyntax; }
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
        /// Gives back the id of the node the Identifier edge points to.
        /// </summary>
        /// <returns>Returns the end point of the m_Identifier edge.</returns>
        /// <exception cref="Columbus.Csharp.Asg.CsharpException">Throws CsharpException if the edge id is invalid.</exception>
        public uint getIdentifier() {
            if (fact.getIsFiltered(m_Identifier))
                return 1;
            else
                return m_Identifier;
        }


        // ---------- Edge setter function(s) ----------

        /// <summary>
        /// Sets the Identifier edge.
        /// </summary>
        /// <param name="nodeId">[in] The new end point of the Identifier edge or 0. With 0 the edge can be deleted.</param>
        /// <exception cref="Columbus.Csharp.Asg.CsharpException">Throws CsharpException if the nodeId is invalid.</exception>
        public void setIdentifier(uint nodeId) {
            if (nodeId != 0) {
                if (!fact.getExist(nodeId))
                    throw new CsharpException("Columbus.Csharp.Asg.Nodes.Structure.XmlNameAttributeSyntax.setIdentifier(NodeId)", "The end point of the edge does not exist.");

                Columbus.Csharp.Asg.Nodes.Base.Base node = fact.getRef(nodeId);
                if (Common.getIsBaseClassKind(node.NodeKind, Types.NodeKind.ndkIdentifierNameSyntax)) {
                    if (m_Identifier != 0) {
                        removeParentEdge(m_Identifier);
                    }
                    m_Identifier = nodeId;
                    setParentEdge(m_Identifier, (uint)Types.EdgeKind.edkXmlNameAttributeSyntax_Identifier);
                } else {
                    throw new CsharpException("Columbus.Csharp.Asg.Nodes.Structure.XmlNameAttributeSyntax.setIdentifier(NodeId)", "Invalid NodeKind (" + node.NodeKind.ToString() + ").");
                }
            } else {
                if (m_Identifier != 0) {
                    removeParentEdge(m_Identifier);
                }
                m_Identifier = 0;
            }
        }

        /// <summary>
        /// Sets the Identifier edge.
        /// </summary>
        /// <param name="node">[in] The new end point of the Identifier edge.</param>
        /// <exception cref="Columbus.Csharp.Asg.CsharpException">Throws CsharpException if there's something wrong with the given node.</exception>
        public void setIdentifier(Columbus.Csharp.Asg.Nodes.Expression.IdentifierNameSyntax node) {
            if (m_Identifier != 0) {
                removeParentEdge(m_Identifier);
            }
            m_Identifier = node.Id;
            setParentEdge(m_Identifier, (uint)Types.EdgeKind.edkXmlNameAttributeSyntax_Identifier);
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

            io.writeUInt4(m_Identifier);

        }

        /// <summary>
        /// Loads the node.
        /// </summary>
        /// <param name="io">[in] The node is read from io.</param>
        /// <exception cref="Columbus.ColumbusIOException">Throws ColumbusIOException if there is something wrong with the file.</exception>
        public override void load(IO binIo) {
            base.load(binIo);

            m_Identifier =  binIo.readUInt4();
            if (m_Identifier != 0)
              setParentEdge(m_Identifier,(uint)Types.EdgeKind.edkXmlNameAttributeSyntax_Identifier);

        }

    }

}
