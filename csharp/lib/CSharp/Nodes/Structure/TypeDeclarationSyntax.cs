using System;
using System.Text;
using System.Diagnostics;
using System.Collections.Generic;

namespace Columbus.Csharp.Asg.Nodes.Structure {

    /// <summary>
    /// TypeDeclarationSyntax class, which represents the structure::TypeDeclarationSyntax node.
    /// </summary>
    [DebuggerDisplay("Id={Id}, Identifier=\"{Identifier}\"")]
#if (CSHARP_INTERNAL)
    internal
#else
    public
#endif
    class TypeDeclarationSyntax : BaseTypeDeclarationSyntax {


        // ---------- Edges ----------

        /// <summary>Container stores the id of the nodes the ConstraintClauses edge points to.</summary>
        protected LinkedList<uint> ConstraintClausesContainer;

        /// <summary>Container stores the id of the nodes the Members edge points to.</summary>
        protected LinkedList<uint> MembersContainer;

        /// <summary>The id of the node the TypeParameterList edge points to.</summary>
        protected uint m_TypeParameterList;

        /// <summary>
        /// Constructor, only factory can instantiates nodes.
        /// </summary>
        /// <param name="nodeId">[in] The id of the node.</param>
        /// <param name="factory">[in] Poiter to the Factory the node belongs to.</param>
        public TypeDeclarationSyntax(uint nodeId, Factory factory) : base(nodeId, factory) {
            ConstraintClausesContainer = new LinkedList<uint>();
            MembersContainer = new LinkedList<uint>();
            m_TypeParameterList = 0;
        }

        /// <summary>
        /// Gives back the NodeKind of the node.
        /// </summary>
        /// <returns>Returns with the NodeKind.</returns>
        public override Types.NodeKind NodeKind {
            get { return Types.NodeKind.ndkTypeDeclarationSyntax; }
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
                case "Members":
                    return MembersListIteratorBegin.Convert<Columbus.Csharp.Asg.Nodes.Base.Base>();
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
                case "Members":
                    addMembers(nodeId);
                    return;
                default:
                    base.add(edge, nodeId);
                    return;
            }
        }


        // ---------- Edge getter function(s) ----------

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
        /// Gives back iterator for the Members edges.
        /// </summary>
        /// <returns>Returns an iterator for the Members edges.</returns>
        public ListIterator<Columbus.Csharp.Asg.Nodes.Structure.MemberDeclarationSyntax> MembersListIteratorBegin {
            get {
                return new ListIterator<Columbus.Csharp.Asg.Nodes.Structure.MemberDeclarationSyntax>(MembersContainer, fact, true);
            }
        }

        /// <summary>
        /// Gives back iterator for the Members edges.
        /// </summary>
        /// <returns>Returns an iterator for the Members edges.</returns>
        public ListIterator<Columbus.Csharp.Asg.Nodes.Structure.MemberDeclarationSyntax> MembersListIteratorEnd {
            get {
                return new ListIterator<Columbus.Csharp.Asg.Nodes.Structure.MemberDeclarationSyntax>(MembersContainer, fact, false);
            }
        }

        /// <summary>
        /// Tells whether the node has Members edges or not.
        /// </summary>
        /// <returns>Returns true if the node has at least one Members edge.</returns>
        public bool MembersIsEmpty {
            get { return MembersContainer.Count == 0; }
        }

        /// <summary>
        /// Gives back how many Members edges the node has.
        /// </summary>
        /// <returns>Returns with the number of Members edges.</returns>
        public uint MembersSize {
            get { return (uint)(MembersContainer.Count); }
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
                throw new CsharpException("Columbus.Csharp.Asg.Nodes.Structure.TypeDeclarationSyntax.addConstraintClauses(NodeId)", "The end point of the edge does not exist.");
            Columbus.Csharp.Asg.Nodes.Base.Base node = fact.getRef(nodeId);
            if (Common.getIsBaseClassKind(node.NodeKind, Types.NodeKind.ndkTypeParameterConstraintClauseSyntax)) {
                ConstraintClausesContainer.AddLast(nodeId);
            } else {
                throw new CsharpException("Columbus.Csharp.Asg.Nodes.Structure.TypeDeclarationSyntax.setConstraintClauses(NodeId)", "Invalid NodeKind (" + node.NodeKind.ToString() + ").");
            }
           setParentEdge(nodeId, (uint)Types.EdgeKind.edkTypeDeclarationSyntax_ConstraintClauses);
            if (fact.ReverseEdges != null)
              fact.ReverseEdges.insertEdge(nodeId, this.Id, Types.EdgeKind.edkTypeDeclarationSyntax_ConstraintClauses);
        }

        /// <summary>
        /// Adds a new Members edge to the node and inserts it after the other ones.
        /// </summary>
        /// <param name="node">[in] The end point of the new Members edge.</param>
        /// <exception cref="Columbus.Csharp.Asg.CsharpException">Throws CsharpException if there is something wrong with the given node.</exception>
        public void addMembers(Columbus.Csharp.Asg.Nodes.Structure.MemberDeclarationSyntax node) {
            addMembers(node.Id);
        }

        /// <summary>
        /// Adds a new Members edge to the node and inserts it after the other ones.
        /// </summary>
        /// <param name="nodeId">[in] The end point of the new Members edge.</param>
        /// <exception cref="Columbus.Csharp.Asg.CsharpException">Throws CsharpException if the given nodeId is invalid.</exception>
        public void addMembers(uint nodeId) {
            if (!fact.getExist(nodeId))
                throw new CsharpException("Columbus.Csharp.Asg.Nodes.Structure.TypeDeclarationSyntax.addMembers(NodeId)", "The end point of the edge does not exist.");
            Columbus.Csharp.Asg.Nodes.Base.Base node = fact.getRef(nodeId);
            if (Common.getIsBaseClassKind(node.NodeKind, Types.NodeKind.ndkMemberDeclarationSyntax)) {
                MembersContainer.AddLast(nodeId);
            } else {
                throw new CsharpException("Columbus.Csharp.Asg.Nodes.Structure.TypeDeclarationSyntax.setMembers(NodeId)", "Invalid NodeKind (" + node.NodeKind.ToString() + ").");
            }
           setParentEdge(nodeId, (uint)Types.EdgeKind.edkTypeDeclarationSyntax_Members);
            if (fact.ReverseEdges != null)
              fact.ReverseEdges.insertEdge(nodeId, this.Id, Types.EdgeKind.edkTypeDeclarationSyntax_Members);
        }

        /// <summary>
        /// Sets the TypeParameterList edge.
        /// </summary>
        /// <param name="nodeId">[in] The new end point of the TypeParameterList edge or 0. With 0 the edge can be deleted.</param>
        /// <exception cref="Columbus.Csharp.Asg.CsharpException">Throws CsharpException if the nodeId is invalid.</exception>
        public void setTypeParameterList(uint nodeId) {
            if (nodeId != 0) {
                if (!fact.getExist(nodeId))
                    throw new CsharpException("Columbus.Csharp.Asg.Nodes.Structure.TypeDeclarationSyntax.setTypeParameterList(NodeId)", "The end point of the edge does not exist.");

                Columbus.Csharp.Asg.Nodes.Base.Base node = fact.getRef(nodeId);
                if (Common.getIsBaseClassKind(node.NodeKind, Types.NodeKind.ndkTypeParameterListSyntax)) {
                    if (m_TypeParameterList != 0) {
                        removeParentEdge(m_TypeParameterList);
                    }
                    m_TypeParameterList = nodeId;
                    setParentEdge(m_TypeParameterList, (uint)Types.EdgeKind.edkTypeDeclarationSyntax_TypeParameterList);
                } else {
                    throw new CsharpException("Columbus.Csharp.Asg.Nodes.Structure.TypeDeclarationSyntax.setTypeParameterList(NodeId)", "Invalid NodeKind (" + node.NodeKind.ToString() + ").");
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
            setParentEdge(m_TypeParameterList, (uint)Types.EdgeKind.edkTypeDeclarationSyntax_TypeParameterList);
        }

        /// <summary>
        /// Saves the node.
        /// </summary>
        /// <param name="io">[in] The node is written into io.</param>
        /// <exception cref="Columbus.ColumbusIOException">Throws ColumbusIOException if there is something wrong with the file.</exception>
        public override void save(IO io) {
            base.save(io);

            io.writeUInt4(m_TypeParameterList);


            foreach (var ConstraintClauses in ConstraintClausesContainer) {
              io.writeUInt4(ConstraintClauses);
            }
            io.writeUInt4(0); // This is the end sign

            foreach (var Members in MembersContainer) {
              io.writeUInt4(Members);
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

            m_TypeParameterList =  binIo.readUInt4();
            if (m_TypeParameterList != 0)
              setParentEdge(m_TypeParameterList,(uint)Types.EdgeKind.edkTypeDeclarationSyntax_TypeParameterList);

            uint _id;

            _id = binIo.readUInt4();
            while (_id != 0) {
              ConstraintClausesContainer.AddLast(_id);
              setParentEdge(_id, (uint)Types.EdgeKind.edkTypeDeclarationSyntax_ConstraintClauses);
              _id = binIo.readUInt4();
            }

            _id = binIo.readUInt4();
            while (_id != 0) {
              MembersContainer.AddLast(_id);
              setParentEdge(_id, (uint)Types.EdgeKind.edkTypeDeclarationSyntax_Members);
              _id = binIo.readUInt4();
            }
        }

    }

}
