using System;
using System.Text;
using System.Diagnostics;
using System.Collections.Generic;

namespace Columbus.Csharp.Asg.Nodes.Structure {

    /// <summary>
    /// CatchClauseSyntax class, which represents the structure::CatchClauseSyntax node.
    /// </summary>
    [DebuggerDisplay("Id={Id}")]
#if (CSHARP_INTERNAL)
    internal
#else
    public
#endif
    class CatchClauseSyntax : Columbus.Csharp.Asg.Nodes.Base.Positioned {


        // ---------- Edges ----------

        /// <summary>The id of the node the Block edge points to.</summary>
        protected uint m_Block;

        /// <summary>The id of the node the Declaration edge points to.</summary>
        protected uint m_Declaration;

        /// <summary>The id of the node the Filter edge points to.</summary>
        protected uint m_Filter;

        /// <summary>
        /// Constructor, only factory can instantiates nodes.
        /// </summary>
        /// <param name="nodeId">[in] The id of the node.</param>
        /// <param name="factory">[in] Poiter to the Factory the node belongs to.</param>
        public CatchClauseSyntax(uint nodeId, Factory factory) : base(nodeId, factory) {
            m_Block = 0;
            m_Declaration = 0;
            m_Filter = 0;
        }

        /// <summary>
        /// Gives back the NodeKind of the node.
        /// </summary>
        /// <returns>Returns with the NodeKind.</returns>
        public override Types.NodeKind NodeKind {
            get { return Types.NodeKind.ndkCatchClauseSyntax; }
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
        /// Gives back the id of the node the Block edge points to.
        /// </summary>
        /// <returns>Returns the end point of the m_Block edge.</returns>
        /// <exception cref="Columbus.Csharp.Asg.CsharpException">Throws CsharpException if the edge id is invalid.</exception>
        public uint getBlock() {
            if (fact.getIsFiltered(m_Block))
                return 1;
            else
                return m_Block;
        }

        /// <summary>
        /// Gives back the id of the node the Declaration edge points to.
        /// </summary>
        /// <returns>Returns the end point of the m_Declaration edge.</returns>
        /// <exception cref="Columbus.Csharp.Asg.CsharpException">Throws CsharpException if the edge id is invalid.</exception>
        public uint getDeclaration() {
            if (fact.getIsFiltered(m_Declaration))
                return 1;
            else
                return m_Declaration;
        }

        /// <summary>
        /// Gives back the id of the node the Filter edge points to.
        /// </summary>
        /// <returns>Returns the end point of the m_Filter edge.</returns>
        /// <exception cref="Columbus.Csharp.Asg.CsharpException">Throws CsharpException if the edge id is invalid.</exception>
        public uint getFilter() {
            if (fact.getIsFiltered(m_Filter))
                return 1;
            else
                return m_Filter;
        }


        // ---------- Edge setter function(s) ----------

        /// <summary>
        /// Sets the Block edge.
        /// </summary>
        /// <param name="nodeId">[in] The new end point of the Block edge or 0. With 0 the edge can be deleted.</param>
        /// <exception cref="Columbus.Csharp.Asg.CsharpException">Throws CsharpException if the nodeId is invalid.</exception>
        public void setBlock(uint nodeId) {
            if (nodeId != 0) {
                if (!fact.getExist(nodeId))
                    throw new CsharpException("Columbus.Csharp.Asg.Nodes.Structure.CatchClauseSyntax.setBlock(NodeId)", "The end point of the edge does not exist.");

                Columbus.Csharp.Asg.Nodes.Base.Base node = fact.getRef(nodeId);
                if (Common.getIsBaseClassKind(node.NodeKind, Types.NodeKind.ndkBlockSyntax)) {
                    if (m_Block != 0) {
                        removeParentEdge(m_Block);
                    }
                    m_Block = nodeId;
                    setParentEdge(m_Block, (uint)Types.EdgeKind.edkCatchClauseSyntax_Block);
                } else {
                    throw new CsharpException("Columbus.Csharp.Asg.Nodes.Structure.CatchClauseSyntax.setBlock(NodeId)", "Invalid NodeKind (" + node.NodeKind.ToString() + ").");
                }
            } else {
                if (m_Block != 0) {
                    removeParentEdge(m_Block);
                }
                m_Block = 0;
            }
        }

        /// <summary>
        /// Sets the Block edge.
        /// </summary>
        /// <param name="node">[in] The new end point of the Block edge.</param>
        /// <exception cref="Columbus.Csharp.Asg.CsharpException">Throws CsharpException if there's something wrong with the given node.</exception>
        public void setBlock(Columbus.Csharp.Asg.Nodes.Statement.BlockSyntax node) {
            if (m_Block != 0) {
                removeParentEdge(m_Block);
            }
            m_Block = node.Id;
            setParentEdge(m_Block, (uint)Types.EdgeKind.edkCatchClauseSyntax_Block);
        }

        /// <summary>
        /// Sets the Declaration edge.
        /// </summary>
        /// <param name="nodeId">[in] The new end point of the Declaration edge or 0. With 0 the edge can be deleted.</param>
        /// <exception cref="Columbus.Csharp.Asg.CsharpException">Throws CsharpException if the nodeId is invalid.</exception>
        public void setDeclaration(uint nodeId) {
            if (nodeId != 0) {
                if (!fact.getExist(nodeId))
                    throw new CsharpException("Columbus.Csharp.Asg.Nodes.Structure.CatchClauseSyntax.setDeclaration(NodeId)", "The end point of the edge does not exist.");

                Columbus.Csharp.Asg.Nodes.Base.Base node = fact.getRef(nodeId);
                if (Common.getIsBaseClassKind(node.NodeKind, Types.NodeKind.ndkCatchDeclarationSyntax)) {
                    if (m_Declaration != 0) {
                        removeParentEdge(m_Declaration);
                    }
                    m_Declaration = nodeId;
                    setParentEdge(m_Declaration, (uint)Types.EdgeKind.edkCatchClauseSyntax_Declaration);
                } else {
                    throw new CsharpException("Columbus.Csharp.Asg.Nodes.Structure.CatchClauseSyntax.setDeclaration(NodeId)", "Invalid NodeKind (" + node.NodeKind.ToString() + ").");
                }
            } else {
                if (m_Declaration != 0) {
                    removeParentEdge(m_Declaration);
                }
                m_Declaration = 0;
            }
        }

        /// <summary>
        /// Sets the Declaration edge.
        /// </summary>
        /// <param name="node">[in] The new end point of the Declaration edge.</param>
        /// <exception cref="Columbus.Csharp.Asg.CsharpException">Throws CsharpException if there's something wrong with the given node.</exception>
        public void setDeclaration(Columbus.Csharp.Asg.Nodes.Structure.CatchDeclarationSyntax node) {
            if (m_Declaration != 0) {
                removeParentEdge(m_Declaration);
            }
            m_Declaration = node.Id;
            setParentEdge(m_Declaration, (uint)Types.EdgeKind.edkCatchClauseSyntax_Declaration);
        }

        /// <summary>
        /// Sets the Filter edge.
        /// </summary>
        /// <param name="nodeId">[in] The new end point of the Filter edge or 0. With 0 the edge can be deleted.</param>
        /// <exception cref="Columbus.Csharp.Asg.CsharpException">Throws CsharpException if the nodeId is invalid.</exception>
        public void setFilter(uint nodeId) {
            if (nodeId != 0) {
                if (!fact.getExist(nodeId))
                    throw new CsharpException("Columbus.Csharp.Asg.Nodes.Structure.CatchClauseSyntax.setFilter(NodeId)", "The end point of the edge does not exist.");

                Columbus.Csharp.Asg.Nodes.Base.Base node = fact.getRef(nodeId);
                if (Common.getIsBaseClassKind(node.NodeKind, Types.NodeKind.ndkCatchFilterClauseSyntax)) {
                    if (m_Filter != 0) {
                        removeParentEdge(m_Filter);
                    }
                    m_Filter = nodeId;
                    setParentEdge(m_Filter, (uint)Types.EdgeKind.edkCatchClauseSyntax_Filter);
                } else {
                    throw new CsharpException("Columbus.Csharp.Asg.Nodes.Structure.CatchClauseSyntax.setFilter(NodeId)", "Invalid NodeKind (" + node.NodeKind.ToString() + ").");
                }
            } else {
                if (m_Filter != 0) {
                    removeParentEdge(m_Filter);
                }
                m_Filter = 0;
            }
        }

        /// <summary>
        /// Sets the Filter edge.
        /// </summary>
        /// <param name="node">[in] The new end point of the Filter edge.</param>
        /// <exception cref="Columbus.Csharp.Asg.CsharpException">Throws CsharpException if there's something wrong with the given node.</exception>
        public void setFilter(Columbus.Csharp.Asg.Nodes.Structure.CatchFilterClauseSyntax node) {
            if (m_Filter != 0) {
                removeParentEdge(m_Filter);
            }
            m_Filter = node.Id;
            setParentEdge(m_Filter, (uint)Types.EdgeKind.edkCatchClauseSyntax_Filter);
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

            io.writeUInt4(m_Block);
            io.writeUInt4(m_Declaration);
            io.writeUInt4(m_Filter);

        }

        /// <summary>
        /// Loads the node.
        /// </summary>
        /// <param name="io">[in] The node is read from io.</param>
        /// <exception cref="Columbus.ColumbusIOException">Throws ColumbusIOException if there is something wrong with the file.</exception>
        public override void load(IO binIo) {
            base.load(binIo);

            m_Block =  binIo.readUInt4();
            if (m_Block != 0)
              setParentEdge(m_Block,(uint)Types.EdgeKind.edkCatchClauseSyntax_Block);

            m_Declaration =  binIo.readUInt4();
            if (m_Declaration != 0)
              setParentEdge(m_Declaration,(uint)Types.EdgeKind.edkCatchClauseSyntax_Declaration);

            m_Filter =  binIo.readUInt4();
            if (m_Filter != 0)
              setParentEdge(m_Filter,(uint)Types.EdgeKind.edkCatchClauseSyntax_Filter);

        }

    }

}
