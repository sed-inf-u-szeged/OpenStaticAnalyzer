using System;
using System.Text;
using System.Diagnostics;
using System.Collections.Generic;

namespace Columbus.Csharp.Asg.Nodes.Structure {

    /// <summary>
    /// PropertyDeclarationSyntax class, which represents the structure::PropertyDeclarationSyntax node.
    /// </summary>
    [DebuggerDisplay("Id={Id}, Identifier=\"{Identifier}\"")]
#if (CSHARP_INTERNAL)
    internal
#else
    public
#endif
    class PropertyDeclarationSyntax : BasePropertyDeclarationSyntax {

        /// <summary>The Key of the `identifier`.</summary>
        protected uint m_identifier;


        // ---------- Edges ----------

        /// <summary>The id of the node the ExpressionBody edge points to.</summary>
        protected uint m_ExpressionBody;

        /// <summary>The id of the node the Initializer edge points to.</summary>
        protected uint m_Initializer;

        /// <summary>
        /// Constructor, only factory can instantiates nodes.
        /// </summary>
        /// <param name="nodeId">[in] The id of the node.</param>
        /// <param name="factory">[in] Poiter to the Factory the node belongs to.</param>
        public PropertyDeclarationSyntax(uint nodeId, Factory factory) : base(nodeId, factory) {
            m_identifier = 0;
            m_ExpressionBody = 0;
            m_Initializer = 0;
        }

        /// <summary>
        /// Gives back the NodeKind of the node.
        /// </summary>
        /// <returns>Returns with the NodeKind.</returns>
        public override Types.NodeKind NodeKind {
            get { return Types.NodeKind.ndkPropertyDeclarationSyntax; }
        }


        // ---------- Attribute propert(y)(ies) ----------

        /// <summary>
        /// Gives back or sets the identifier of the node.
        /// </summary>
        public string Identifier
        {
            get
            {
                return fact.StringTable.get(m_identifier);
            }
            set
            {
                m_identifier = fact.StringTable.set( value );
            }
        }

        /// <summary>
        /// Gives back or sets the Key of identifier of the node.
        /// </summary>
        public uint IdentifierKey
        {
            get
            {
                return m_identifier;
            }
            set
            {
               m_identifier = value;
            }
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
        /// Gives back the id of the node the ExpressionBody edge points to.
        /// </summary>
        /// <returns>Returns the end point of the m_ExpressionBody edge.</returns>
        /// <exception cref="Columbus.Csharp.Asg.CsharpException">Throws CsharpException if the edge id is invalid.</exception>
        public uint getExpressionBody() {
            if (fact.getIsFiltered(m_ExpressionBody))
                return 1;
            else
                return m_ExpressionBody;
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


        // ---------- Edge setter function(s) ----------

        /// <summary>
        /// Sets the ExpressionBody edge.
        /// </summary>
        /// <param name="nodeId">[in] The new end point of the ExpressionBody edge or 0. With 0 the edge can be deleted.</param>
        /// <exception cref="Columbus.Csharp.Asg.CsharpException">Throws CsharpException if the nodeId is invalid.</exception>
        public void setExpressionBody(uint nodeId) {
            if (nodeId != 0) {
                if (!fact.getExist(nodeId))
                    throw new CsharpException("Columbus.Csharp.Asg.Nodes.Structure.PropertyDeclarationSyntax.setExpressionBody(NodeId)", "The end point of the edge does not exist.");

                Columbus.Csharp.Asg.Nodes.Base.Base node = fact.getRef(nodeId);
                if (Common.getIsBaseClassKind(node.NodeKind, Types.NodeKind.ndkArrowExpressionClauseSyntax)) {
                    if (m_ExpressionBody != 0) {
                        removeParentEdge(m_ExpressionBody);
                    }
                    m_ExpressionBody = nodeId;
                    setParentEdge(m_ExpressionBody, (uint)Types.EdgeKind.edkPropertyDeclarationSyntax_ExpressionBody);
                } else {
                    throw new CsharpException("Columbus.Csharp.Asg.Nodes.Structure.PropertyDeclarationSyntax.setExpressionBody(NodeId)", "Invalid NodeKind (" + node.NodeKind.ToString() + ").");
                }
            } else {
                if (m_ExpressionBody != 0) {
                    removeParentEdge(m_ExpressionBody);
                }
                m_ExpressionBody = 0;
            }
        }

        /// <summary>
        /// Sets the ExpressionBody edge.
        /// </summary>
        /// <param name="node">[in] The new end point of the ExpressionBody edge.</param>
        /// <exception cref="Columbus.Csharp.Asg.CsharpException">Throws CsharpException if there's something wrong with the given node.</exception>
        public void setExpressionBody(Columbus.Csharp.Asg.Nodes.Structure.ArrowExpressionClauseSyntax node) {
            if (m_ExpressionBody != 0) {
                removeParentEdge(m_ExpressionBody);
            }
            m_ExpressionBody = node.Id;
            setParentEdge(m_ExpressionBody, (uint)Types.EdgeKind.edkPropertyDeclarationSyntax_ExpressionBody);
        }

        /// <summary>
        /// Sets the Initializer edge.
        /// </summary>
        /// <param name="nodeId">[in] The new end point of the Initializer edge or 0. With 0 the edge can be deleted.</param>
        /// <exception cref="Columbus.Csharp.Asg.CsharpException">Throws CsharpException if the nodeId is invalid.</exception>
        public void setInitializer(uint nodeId) {
            if (nodeId != 0) {
                if (!fact.getExist(nodeId))
                    throw new CsharpException("Columbus.Csharp.Asg.Nodes.Structure.PropertyDeclarationSyntax.setInitializer(NodeId)", "The end point of the edge does not exist.");

                Columbus.Csharp.Asg.Nodes.Base.Base node = fact.getRef(nodeId);
                if (Common.getIsBaseClassKind(node.NodeKind, Types.NodeKind.ndkEqualsValueClauseSyntax)) {
                    if (m_Initializer != 0) {
                        removeParentEdge(m_Initializer);
                    }
                    m_Initializer = nodeId;
                    setParentEdge(m_Initializer, (uint)Types.EdgeKind.edkPropertyDeclarationSyntax_Initializer);
                } else {
                    throw new CsharpException("Columbus.Csharp.Asg.Nodes.Structure.PropertyDeclarationSyntax.setInitializer(NodeId)", "Invalid NodeKind (" + node.NodeKind.ToString() + ").");
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
        public void setInitializer(Columbus.Csharp.Asg.Nodes.Structure.EqualsValueClauseSyntax node) {
            if (m_Initializer != 0) {
                removeParentEdge(m_Initializer);
            }
            m_Initializer = node.Id;
            setParentEdge(m_Initializer, (uint)Types.EdgeKind.edkPropertyDeclarationSyntax_Initializer);
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

            fact.StringTable.setType(m_identifier, StrTable.StrType.strToSave);
            io.writeUInt4(m_identifier);

            io.writeUInt4(m_ExpressionBody);
            io.writeUInt4(m_Initializer);

        }

        /// <summary>
        /// Loads the node.
        /// </summary>
        /// <param name="io">[in] The node is read from io.</param>
        /// <exception cref="Columbus.ColumbusIOException">Throws ColumbusIOException if there is something wrong with the file.</exception>
        public override void load(IO binIo) {
            base.load(binIo);

            m_identifier = binIo.readUInt4();

            m_ExpressionBody =  binIo.readUInt4();
            if (m_ExpressionBody != 0)
              setParentEdge(m_ExpressionBody,(uint)Types.EdgeKind.edkPropertyDeclarationSyntax_ExpressionBody);

            m_Initializer =  binIo.readUInt4();
            if (m_Initializer != 0)
              setParentEdge(m_Initializer,(uint)Types.EdgeKind.edkPropertyDeclarationSyntax_Initializer);

        }

    }

}
