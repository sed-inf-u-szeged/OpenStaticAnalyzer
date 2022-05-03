using System;
using System.Text;
using System.Diagnostics;
using System.Collections.Generic;

namespace Columbus.Csharp.Asg.Nodes.Statement {

    /// <summary>
    /// LocalFunctionStatementSyntax class, which represents the statement::LocalFunctionStatementSyntax node.
    /// </summary>
    [DebuggerDisplay("Id={Id}, Identifier=\"{Identifier}\"")]
#if (CSHARP_INTERNAL)
    internal
#else
    public
#endif
    class LocalFunctionStatementSyntax : StatementSyntax {

        /// <summary>The Key of the `identifier`.</summary>
        protected uint m_identifier;


        // ---------- Edges ----------

        /// <summary>The id of the node the Body edge points to.</summary>
        protected uint m_Body;

        /// <summary>Container stores the id of the nodes the ConstraintClauses edge points to.</summary>
        protected LinkedList<uint> ConstraintClausesContainer;

        /// <summary>The id of the node the ExpressionBody edge points to.</summary>
        protected uint m_ExpressionBody;

        /// <summary>The id of the node the ParameterList edge points to.</summary>
        protected uint m_ParameterList;

        /// <summary>The id of the node the ReturnType edge points to.</summary>
        protected uint m_ReturnType;

        /// <summary>The id of the node the TypeParameterList edge points to.</summary>
        protected uint m_TypeParameterList;

        /// <summary>
        /// Constructor, only factory can instantiates nodes.
        /// </summary>
        /// <param name="nodeId">[in] The id of the node.</param>
        /// <param name="factory">[in] Poiter to the Factory the node belongs to.</param>
        public LocalFunctionStatementSyntax(uint nodeId, Factory factory) : base(nodeId, factory) {
            m_identifier = 0;
            m_Body = 0;
            ConstraintClausesContainer = new LinkedList<uint>();
            m_ExpressionBody = 0;
            m_ParameterList = 0;
            m_ReturnType = 0;
            m_TypeParameterList = 0;
        }

        /// <summary>
        /// Gives back the NodeKind of the node.
        /// </summary>
        /// <returns>Returns with the NodeKind.</returns>
        public override Types.NodeKind NodeKind {
            get { return Types.NodeKind.ndkLocalFunctionStatementSyntax; }
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
                case "ConstraintClauses":
                    return ConstraintClausesListIteratorBegin.Convert<Columbus.Csharp.Asg.Nodes.Base.Base>();
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
                case "ConstraintClauses":
                    addConstraintClauses(nodeId);
                    return;
                default:
                    base.add(edge, nodeId);
                    return;
            }
        }


        // ---------- Edge getter function(s) ----------

        /// <summary>
        /// Gives back the id of the node the Body edge points to.
        /// </summary>
        /// <returns>Returns the end point of the m_Body edge.</returns>
        /// <exception cref="Columbus.Csharp.Asg.CsharpException">Throws CsharpException if the edge id is invalid.</exception>
        public uint getBody() {
            if (fact.getIsFiltered(m_Body))
                return 1;
            else
                return m_Body;
        }

        /// <summary>
        /// Gives back iterator for the ConstraintClauses edges.
        /// </summary>
        /// <returns>Returns an iterator for the ConstraintClauses edges.</returns>
        public ListIterator<Columbus.Csharp.Asg.Nodes.Structure.TypeParameterConstraintClauseSyntax> ConstraintClausesListIteratorBegin {
            get {
                return new ListIterator<Columbus.Csharp.Asg.Nodes.Structure.TypeParameterConstraintClauseSyntax>(ConstraintClausesContainer, fact, true);
            }
        }

        /// <summary>
        /// Gives back iterator for the ConstraintClauses edges.
        /// </summary>
        /// <returns>Returns an iterator for the ConstraintClauses edges.</returns>
        public ListIterator<Columbus.Csharp.Asg.Nodes.Structure.TypeParameterConstraintClauseSyntax> ConstraintClausesListIteratorEnd {
            get {
                return new ListIterator<Columbus.Csharp.Asg.Nodes.Structure.TypeParameterConstraintClauseSyntax>(ConstraintClausesContainer, fact, false);
            }
        }

        /// <summary>
        /// Tells whether the node has ConstraintClauses edges or not.
        /// </summary>
        /// <returns>Returns true if the node has at least one ConstraintClauses edge.</returns>
        public bool ConstraintClausesIsEmpty {
            get { return ConstraintClausesContainer.Count == 0; }
        }

        /// <summary>
        /// Gives back how many ConstraintClauses edges the node has.
        /// </summary>
        /// <returns>Returns with the number of ConstraintClauses edges.</returns>
        public uint ConstraintClausesSize {
            get { return (uint)(ConstraintClausesContainer.Count); }
        }

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
        /// Gives back the id of the node the ParameterList edge points to.
        /// </summary>
        /// <returns>Returns the end point of the m_ParameterList edge.</returns>
        /// <exception cref="Columbus.Csharp.Asg.CsharpException">Throws CsharpException if the edge id is invalid.</exception>
        public uint getParameterList() {
            if (fact.getIsFiltered(m_ParameterList))
                return 1;
            else
                return m_ParameterList;
        }

        /// <summary>
        /// Gives back the id of the node the ReturnType edge points to.
        /// </summary>
        /// <returns>Returns the end point of the m_ReturnType edge.</returns>
        /// <exception cref="Columbus.Csharp.Asg.CsharpException">Throws CsharpException if the edge id is invalid.</exception>
        public uint getReturnType() {
            if (fact.getIsFiltered(m_ReturnType))
                return 1;
            else
                return m_ReturnType;
        }

        /// <summary>
        /// Gives back the id of the node the TypeParameterList edge points to.
        /// </summary>
        /// <returns>Returns the end point of the m_TypeParameterList edge.</returns>
        /// <exception cref="Columbus.Csharp.Asg.CsharpException">Throws CsharpException if the edge id is invalid.</exception>
        public uint getTypeParameterList() {
            if (fact.getIsFiltered(m_TypeParameterList))
                return 1;
            else
                return m_TypeParameterList;
        }


        // ---------- Edge setter function(s) ----------

        /// <summary>
        /// Sets the Body edge.
        /// </summary>
        /// <param name="nodeId">[in] The new end point of the Body edge or 0. With 0 the edge can be deleted.</param>
        /// <exception cref="Columbus.Csharp.Asg.CsharpException">Throws CsharpException if the nodeId is invalid.</exception>
        public void setBody(uint nodeId) {
            if (nodeId != 0) {
                if (!fact.getExist(nodeId))
                    throw new CsharpException("Columbus.Csharp.Asg.Nodes.Statement.LocalFunctionStatementSyntax.setBody(NodeId)", "The end point of the edge does not exist.");

                Columbus.Csharp.Asg.Nodes.Base.Base node = fact.getRef(nodeId);
                if (Common.getIsBaseClassKind(node.NodeKind, Types.NodeKind.ndkBlockSyntax)) {
                    if (m_Body != 0) {
                        removeParentEdge(m_Body);
                    }
                    m_Body = nodeId;
                    setParentEdge(m_Body, (uint)Types.EdgeKind.edkLocalFunctionStatementSyntax_Body);
                } else {
                    throw new CsharpException("Columbus.Csharp.Asg.Nodes.Statement.LocalFunctionStatementSyntax.setBody(NodeId)", "Invalid NodeKind (" + node.NodeKind.ToString() + ").");
                }
            } else {
                if (m_Body != 0) {
                    removeParentEdge(m_Body);
                }
                m_Body = 0;
            }
        }

        /// <summary>
        /// Sets the Body edge.
        /// </summary>
        /// <param name="node">[in] The new end point of the Body edge.</param>
        /// <exception cref="Columbus.Csharp.Asg.CsharpException">Throws CsharpException if there's something wrong with the given node.</exception>
        public void setBody(Columbus.Csharp.Asg.Nodes.Statement.BlockSyntax node) {
            if (m_Body != 0) {
                removeParentEdge(m_Body);
            }
            m_Body = node.Id;
            setParentEdge(m_Body, (uint)Types.EdgeKind.edkLocalFunctionStatementSyntax_Body);
        }

        /// <summary>
        /// Adds a new ConstraintClauses edge to the node and inserts it after the other ones.
        /// </summary>
        /// <param name="node">[in] The end point of the new ConstraintClauses edge.</param>
        /// <exception cref="Columbus.Csharp.Asg.CsharpException">Throws CsharpException if there is something wrong with the given node.</exception>
        public void addConstraintClauses(Columbus.Csharp.Asg.Nodes.Structure.TypeParameterConstraintClauseSyntax node) {
            addConstraintClauses(node.Id);
        }

        /// <summary>
        /// Adds a new ConstraintClauses edge to the node and inserts it after the other ones.
        /// </summary>
        /// <param name="nodeId">[in] The end point of the new ConstraintClauses edge.</param>
        /// <exception cref="Columbus.Csharp.Asg.CsharpException">Throws CsharpException if the given nodeId is invalid.</exception>
        public void addConstraintClauses(uint nodeId) {
            if (!fact.getExist(nodeId))
                throw new CsharpException("Columbus.Csharp.Asg.Nodes.Statement.LocalFunctionStatementSyntax.addConstraintClauses(NodeId)", "The end point of the edge does not exist.");
            Columbus.Csharp.Asg.Nodes.Base.Base node = fact.getRef(nodeId);
            if (Common.getIsBaseClassKind(node.NodeKind, Types.NodeKind.ndkTypeParameterConstraintClauseSyntax)) {
                ConstraintClausesContainer.AddLast(nodeId);
            } else {
                throw new CsharpException("Columbus.Csharp.Asg.Nodes.Statement.LocalFunctionStatementSyntax.setConstraintClauses(NodeId)", "Invalid NodeKind (" + node.NodeKind.ToString() + ").");
            }
           setParentEdge(nodeId, (uint)Types.EdgeKind.edkLocalFunctionStatementSyntax_ConstraintClauses);
            if (fact.ReverseEdges != null)
              fact.ReverseEdges.insertEdge(nodeId, this.Id, Types.EdgeKind.edkLocalFunctionStatementSyntax_ConstraintClauses);
        }

        /// <summary>
        /// Sets the ExpressionBody edge.
        /// </summary>
        /// <param name="nodeId">[in] The new end point of the ExpressionBody edge or 0. With 0 the edge can be deleted.</param>
        /// <exception cref="Columbus.Csharp.Asg.CsharpException">Throws CsharpException if the nodeId is invalid.</exception>
        public void setExpressionBody(uint nodeId) {
            if (nodeId != 0) {
                if (!fact.getExist(nodeId))
                    throw new CsharpException("Columbus.Csharp.Asg.Nodes.Statement.LocalFunctionStatementSyntax.setExpressionBody(NodeId)", "The end point of the edge does not exist.");

                Columbus.Csharp.Asg.Nodes.Base.Base node = fact.getRef(nodeId);
                if (Common.getIsBaseClassKind(node.NodeKind, Types.NodeKind.ndkArrowExpressionClauseSyntax)) {
                    if (m_ExpressionBody != 0) {
                        removeParentEdge(m_ExpressionBody);
                    }
                    m_ExpressionBody = nodeId;
                    setParentEdge(m_ExpressionBody, (uint)Types.EdgeKind.edkLocalFunctionStatementSyntax_ExpressionBody);
                } else {
                    throw new CsharpException("Columbus.Csharp.Asg.Nodes.Statement.LocalFunctionStatementSyntax.setExpressionBody(NodeId)", "Invalid NodeKind (" + node.NodeKind.ToString() + ").");
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
            setParentEdge(m_ExpressionBody, (uint)Types.EdgeKind.edkLocalFunctionStatementSyntax_ExpressionBody);
        }

        /// <summary>
        /// Sets the ParameterList edge.
        /// </summary>
        /// <param name="nodeId">[in] The new end point of the ParameterList edge or 0. With 0 the edge can be deleted.</param>
        /// <exception cref="Columbus.Csharp.Asg.CsharpException">Throws CsharpException if the nodeId is invalid.</exception>
        public void setParameterList(uint nodeId) {
            if (nodeId != 0) {
                if (!fact.getExist(nodeId))
                    throw new CsharpException("Columbus.Csharp.Asg.Nodes.Statement.LocalFunctionStatementSyntax.setParameterList(NodeId)", "The end point of the edge does not exist.");

                Columbus.Csharp.Asg.Nodes.Base.Base node = fact.getRef(nodeId);
                if (Common.getIsBaseClassKind(node.NodeKind, Types.NodeKind.ndkParameterListSyntax)) {
                    if (m_ParameterList != 0) {
                        removeParentEdge(m_ParameterList);
                    }
                    m_ParameterList = nodeId;
                    setParentEdge(m_ParameterList, (uint)Types.EdgeKind.edkLocalFunctionStatementSyntax_ParameterList);
                } else {
                    throw new CsharpException("Columbus.Csharp.Asg.Nodes.Statement.LocalFunctionStatementSyntax.setParameterList(NodeId)", "Invalid NodeKind (" + node.NodeKind.ToString() + ").");
                }
            } else {
                if (m_ParameterList != 0) {
                    removeParentEdge(m_ParameterList);
                }
                m_ParameterList = 0;
            }
        }

        /// <summary>
        /// Sets the ParameterList edge.
        /// </summary>
        /// <param name="node">[in] The new end point of the ParameterList edge.</param>
        /// <exception cref="Columbus.Csharp.Asg.CsharpException">Throws CsharpException if there's something wrong with the given node.</exception>
        public void setParameterList(Columbus.Csharp.Asg.Nodes.Structure.ParameterListSyntax node) {
            if (m_ParameterList != 0) {
                removeParentEdge(m_ParameterList);
            }
            m_ParameterList = node.Id;
            setParentEdge(m_ParameterList, (uint)Types.EdgeKind.edkLocalFunctionStatementSyntax_ParameterList);
        }

        /// <summary>
        /// Sets the ReturnType edge.
        /// </summary>
        /// <param name="nodeId">[in] The new end point of the ReturnType edge or 0. With 0 the edge can be deleted.</param>
        /// <exception cref="Columbus.Csharp.Asg.CsharpException">Throws CsharpException if the nodeId is invalid.</exception>
        public void setReturnType(uint nodeId) {
            if (nodeId != 0) {
                if (!fact.getExist(nodeId))
                    throw new CsharpException("Columbus.Csharp.Asg.Nodes.Statement.LocalFunctionStatementSyntax.setReturnType(NodeId)", "The end point of the edge does not exist.");

                Columbus.Csharp.Asg.Nodes.Base.Base node = fact.getRef(nodeId);
                if (Common.getIsBaseClassKind(node.NodeKind, Types.NodeKind.ndkTypeSyntax)) {
                    if (m_ReturnType != 0) {
                        removeParentEdge(m_ReturnType);
                    }
                    m_ReturnType = nodeId;
                    setParentEdge(m_ReturnType, (uint)Types.EdgeKind.edkLocalFunctionStatementSyntax_ReturnType);
                } else {
                    throw new CsharpException("Columbus.Csharp.Asg.Nodes.Statement.LocalFunctionStatementSyntax.setReturnType(NodeId)", "Invalid NodeKind (" + node.NodeKind.ToString() + ").");
                }
            } else {
                if (m_ReturnType != 0) {
                    removeParentEdge(m_ReturnType);
                }
                m_ReturnType = 0;
            }
        }

        /// <summary>
        /// Sets the ReturnType edge.
        /// </summary>
        /// <param name="node">[in] The new end point of the ReturnType edge.</param>
        /// <exception cref="Columbus.Csharp.Asg.CsharpException">Throws CsharpException if there's something wrong with the given node.</exception>
        public void setReturnType(Columbus.Csharp.Asg.Nodes.Expression.TypeSyntax node) {
            if (m_ReturnType != 0) {
                removeParentEdge(m_ReturnType);
            }
            m_ReturnType = node.Id;
            setParentEdge(m_ReturnType, (uint)Types.EdgeKind.edkLocalFunctionStatementSyntax_ReturnType);
        }

        /// <summary>
        /// Sets the TypeParameterList edge.
        /// </summary>
        /// <param name="nodeId">[in] The new end point of the TypeParameterList edge or 0. With 0 the edge can be deleted.</param>
        /// <exception cref="Columbus.Csharp.Asg.CsharpException">Throws CsharpException if the nodeId is invalid.</exception>
        public void setTypeParameterList(uint nodeId) {
            if (nodeId != 0) {
                if (!fact.getExist(nodeId))
                    throw new CsharpException("Columbus.Csharp.Asg.Nodes.Statement.LocalFunctionStatementSyntax.setTypeParameterList(NodeId)", "The end point of the edge does not exist.");

                Columbus.Csharp.Asg.Nodes.Base.Base node = fact.getRef(nodeId);
                if (Common.getIsBaseClassKind(node.NodeKind, Types.NodeKind.ndkTypeParameterListSyntax)) {
                    if (m_TypeParameterList != 0) {
                        removeParentEdge(m_TypeParameterList);
                    }
                    m_TypeParameterList = nodeId;
                    setParentEdge(m_TypeParameterList, (uint)Types.EdgeKind.edkLocalFunctionStatementSyntax_TypeParameterList);
                } else {
                    throw new CsharpException("Columbus.Csharp.Asg.Nodes.Statement.LocalFunctionStatementSyntax.setTypeParameterList(NodeId)", "Invalid NodeKind (" + node.NodeKind.ToString() + ").");
                }
            } else {
                if (m_TypeParameterList != 0) {
                    removeParentEdge(m_TypeParameterList);
                }
                m_TypeParameterList = 0;
            }
        }

        /// <summary>
        /// Sets the TypeParameterList edge.
        /// </summary>
        /// <param name="node">[in] The new end point of the TypeParameterList edge.</param>
        /// <exception cref="Columbus.Csharp.Asg.CsharpException">Throws CsharpException if there's something wrong with the given node.</exception>
        public void setTypeParameterList(Columbus.Csharp.Asg.Nodes.Structure.TypeParameterListSyntax node) {
            if (m_TypeParameterList != 0) {
                removeParentEdge(m_TypeParameterList);
            }
            m_TypeParameterList = node.Id;
            setParentEdge(m_TypeParameterList, (uint)Types.EdgeKind.edkLocalFunctionStatementSyntax_TypeParameterList);
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

            io.writeUInt4(m_Body);
            io.writeUInt4(m_ExpressionBody);
            io.writeUInt4(m_ParameterList);
            io.writeUInt4(m_ReturnType);
            io.writeUInt4(m_TypeParameterList);


            foreach (var ConstraintClauses in ConstraintClausesContainer) {
              io.writeUInt4(ConstraintClauses);
            }
            io.writeUInt4(0); // This is the end sign
        }

        /// <summary>
        /// Loads the node.
        /// </summary>
        /// <param name="io">[in] The node is read from io.</param>
        /// <exception cref="Columbus.ColumbusIOException">Throws ColumbusIOException if there is something wrong with the file.</exception>
        public override void load(IO binIo) {
            base.load(binIo);

            m_identifier = binIo.readUInt4();

            m_Body =  binIo.readUInt4();
            if (m_Body != 0)
              setParentEdge(m_Body,(uint)Types.EdgeKind.edkLocalFunctionStatementSyntax_Body);

            m_ExpressionBody =  binIo.readUInt4();
            if (m_ExpressionBody != 0)
              setParentEdge(m_ExpressionBody,(uint)Types.EdgeKind.edkLocalFunctionStatementSyntax_ExpressionBody);

            m_ParameterList =  binIo.readUInt4();
            if (m_ParameterList != 0)
              setParentEdge(m_ParameterList,(uint)Types.EdgeKind.edkLocalFunctionStatementSyntax_ParameterList);

            m_ReturnType =  binIo.readUInt4();
            if (m_ReturnType != 0)
              setParentEdge(m_ReturnType,(uint)Types.EdgeKind.edkLocalFunctionStatementSyntax_ReturnType);

            m_TypeParameterList =  binIo.readUInt4();
            if (m_TypeParameterList != 0)
              setParentEdge(m_TypeParameterList,(uint)Types.EdgeKind.edkLocalFunctionStatementSyntax_TypeParameterList);

            uint _id;

            _id = binIo.readUInt4();
            while (_id != 0) {
              ConstraintClausesContainer.AddLast(_id);
              setParentEdge(_id, (uint)Types.EdgeKind.edkLocalFunctionStatementSyntax_ConstraintClauses);
              _id = binIo.readUInt4();
            }
        }

    }

}