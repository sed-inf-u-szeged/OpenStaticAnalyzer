using System;
using System.Text;
using System.Diagnostics;
using System.Collections.Generic;

namespace Columbus.Csharp.Asg.Nodes.Structure {

    /// <summary>
    /// QualifiedCrefSyntax class, which represents the structure::QualifiedCrefSyntax node.
    /// </summary>
    [DebuggerDisplay("Id={Id}")]
#if (CSHARP_INTERNAL)
    internal
#else
    public
#endif
    class QualifiedCrefSyntax : CrefSyntax {


        // ---------- Edges ----------

        /// <summary>The id of the node the Container edge points to.</summary>
        protected uint m_Container;

        /// <summary>The id of the node the Member edge points to.</summary>
        protected uint m_Member;

        /// <summary>
        /// Constructor, only factory can instantiates nodes.
        /// </summary>
        /// <param name="nodeId">[in] The id of the node.</param>
        /// <param name="factory">[in] Poiter to the Factory the node belongs to.</param>
        public QualifiedCrefSyntax(uint nodeId, Factory factory) : base(nodeId, factory) {
            m_Container = 0;
            m_Member = 0;
        }

        /// <summary>
        /// Gives back the NodeKind of the node.
        /// </summary>
        /// <returns>Returns with the NodeKind.</returns>
        public override Types.NodeKind NodeKind {
            get { return Types.NodeKind.ndkQualifiedCrefSyntax; }
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
        /// Gives back the id of the node the Container edge points to.
        /// </summary>
        /// <returns>Returns the end point of the m_Container edge.</returns>
        /// <exception cref="Columbus.Csharp.Asg.CsharpException">Throws CsharpException if the edge id is invalid.</exception>
        public uint getContainer() {
            if (fact.getIsFiltered(m_Container))
                return 1;
            else
                return m_Container;
        }

        /// <summary>
        /// Gives back the id of the node the Member edge points to.
        /// </summary>
        /// <returns>Returns the end point of the m_Member edge.</returns>
        /// <exception cref="Columbus.Csharp.Asg.CsharpException">Throws CsharpException if the edge id is invalid.</exception>
        public uint getMember() {
            if (fact.getIsFiltered(m_Member))
                return 1;
            else
                return m_Member;
        }


        // ---------- Edge setter function(s) ----------

        /// <summary>
        /// Sets the Container edge.
        /// </summary>
        /// <param name="nodeId">[in] The new end point of the Container edge or 0. With 0 the edge can be deleted.</param>
        /// <exception cref="Columbus.Csharp.Asg.CsharpException">Throws CsharpException if the nodeId is invalid.</exception>
        public void setContainer(uint nodeId) {
            if (nodeId != 0) {
                if (!fact.getExist(nodeId))
                    throw new CsharpException("Columbus.Csharp.Asg.Nodes.Structure.QualifiedCrefSyntax.setContainer(NodeId)", "The end point of the edge does not exist.");

                Columbus.Csharp.Asg.Nodes.Base.Base node = fact.getRef(nodeId);
                if (Common.getIsBaseClassKind(node.NodeKind, Types.NodeKind.ndkTypeSyntax)) {
                    if (m_Container != 0) {
                        removeParentEdge(m_Container);
                    }
                    m_Container = nodeId;
                    setParentEdge(m_Container, (uint)Types.EdgeKind.edkQualifiedCrefSyntax_Container);
                } else {
                    throw new CsharpException("Columbus.Csharp.Asg.Nodes.Structure.QualifiedCrefSyntax.setContainer(NodeId)", "Invalid NodeKind (" + node.NodeKind.ToString() + ").");
                }
            } else {
                if (m_Container != 0) {
                    removeParentEdge(m_Container);
                }
                m_Container = 0;
            }
        }

        /// <summary>
        /// Sets the Container edge.
        /// </summary>
        /// <param name="node">[in] The new end point of the Container edge.</param>
        /// <exception cref="Columbus.Csharp.Asg.CsharpException">Throws CsharpException if there's something wrong with the given node.</exception>
        public void setContainer(Columbus.Csharp.Asg.Nodes.Expression.TypeSyntax node) {
            if (m_Container != 0) {
                removeParentEdge(m_Container);
            }
            m_Container = node.Id;
            setParentEdge(m_Container, (uint)Types.EdgeKind.edkQualifiedCrefSyntax_Container);
        }

        /// <summary>
        /// Sets the Member edge.
        /// </summary>
        /// <param name="nodeId">[in] The new end point of the Member edge or 0. With 0 the edge can be deleted.</param>
        /// <exception cref="Columbus.Csharp.Asg.CsharpException">Throws CsharpException if the nodeId is invalid.</exception>
        public void setMember(uint nodeId) {
            if (nodeId != 0) {
                if (!fact.getExist(nodeId))
                    throw new CsharpException("Columbus.Csharp.Asg.Nodes.Structure.QualifiedCrefSyntax.setMember(NodeId)", "The end point of the edge does not exist.");

                Columbus.Csharp.Asg.Nodes.Base.Base node = fact.getRef(nodeId);
                if (Common.getIsBaseClassKind(node.NodeKind, Types.NodeKind.ndkMemberCrefSyntax)) {
                    if (m_Member != 0) {
                        removeParentEdge(m_Member);
                    }
                    m_Member = nodeId;
                    setParentEdge(m_Member, (uint)Types.EdgeKind.edkQualifiedCrefSyntax_Member);
                } else {
                    throw new CsharpException("Columbus.Csharp.Asg.Nodes.Structure.QualifiedCrefSyntax.setMember(NodeId)", "Invalid NodeKind (" + node.NodeKind.ToString() + ").");
                }
            } else {
                if (m_Member != 0) {
                    removeParentEdge(m_Member);
                }
                m_Member = 0;
            }
        }

        /// <summary>
        /// Sets the Member edge.
        /// </summary>
        /// <param name="node">[in] The new end point of the Member edge.</param>
        /// <exception cref="Columbus.Csharp.Asg.CsharpException">Throws CsharpException if there's something wrong with the given node.</exception>
        public void setMember(Columbus.Csharp.Asg.Nodes.Structure.MemberCrefSyntax node) {
            if (m_Member != 0) {
                removeParentEdge(m_Member);
            }
            m_Member = node.Id;
            setParentEdge(m_Member, (uint)Types.EdgeKind.edkQualifiedCrefSyntax_Member);
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

            io.writeUInt4(m_Container);
            io.writeUInt4(m_Member);

        }

        /// <summary>
        /// Loads the node.
        /// </summary>
        /// <param name="io">[in] The node is read from io.</param>
        /// <exception cref="Columbus.ColumbusIOException">Throws ColumbusIOException if there is something wrong with the file.</exception>
        public override void load(IO binIo) {
            base.load(binIo);

            m_Container =  binIo.readUInt4();
            if (m_Container != 0)
              setParentEdge(m_Container,(uint)Types.EdgeKind.edkQualifiedCrefSyntax_Container);

            m_Member =  binIo.readUInt4();
            if (m_Member != 0)
              setParentEdge(m_Member,(uint)Types.EdgeKind.edkQualifiedCrefSyntax_Member);

        }

    }

}
