using System;
using System.Text;
using System.Diagnostics;
using System.Collections.Generic;

namespace Columbus.Csharp.Asg.Nodes.Structure {

    /// <summary>
    /// CompilationUnitSyntax class, which represents the structure::CompilationUnitSyntax node.
    /// </summary>
    [DebuggerDisplay("Id={Id}")]
#if (CSHARP_INTERNAL)
    internal
#else
    public
#endif
    class CompilationUnitSyntax : Columbus.Csharp.Asg.Nodes.Base.Positioned {


        // ---------- Edges ----------

        /// <summary>Container stores the id of the nodes the AttributeLists edge points to.</summary>
        protected LinkedList<uint> AttributeListsContainer;

        /// <summary>Container stores the id of the nodes the Externs edge points to.</summary>
        protected LinkedList<uint> ExternsContainer;

        /// <summary>Container stores the id of the nodes the Members edge points to.</summary>
        protected LinkedList<uint> MembersContainer;

        /// <summary>Container stores the id of the nodes the Usings edge points to.</summary>
        protected LinkedList<uint> UsingsContainer;

        /// <summary>
        /// Constructor, only factory can instantiates nodes.
        /// </summary>
        /// <param name="nodeId">[in] The id of the node.</param>
        /// <param name="factory">[in] Poiter to the Factory the node belongs to.</param>
        public CompilationUnitSyntax(uint nodeId, Factory factory) : base(nodeId, factory) {
            AttributeListsContainer = new LinkedList<uint>();
            ExternsContainer = new LinkedList<uint>();
            MembersContainer = new LinkedList<uint>();
            UsingsContainer = new LinkedList<uint>();
        }

        /// <summary>
        /// Gives back the NodeKind of the node.
        /// </summary>
        /// <returns>Returns with the NodeKind.</returns>
        public override Types.NodeKind NodeKind {
            get { return Types.NodeKind.ndkCompilationUnitSyntax; }
        }


        // ---------- Reflection getter function ----------

        /// <summary>
        /// Gives back the begin iterator for the edge specified
        /// </summary>
        /// <param name="edge">[in] The multiple edge for which the iterator is requested</param>
        public override ListIterator<Columbus.Csharp.Asg.Nodes.Base.Base> GetListIteratorBegin(string edge) {
            switch(edge) {
                case "AttributeLists":
                    return AttributeListsListIteratorBegin.Convert<Columbus.Csharp.Asg.Nodes.Base.Base>();
                case "Externs":
                    return ExternsListIteratorBegin.Convert<Columbus.Csharp.Asg.Nodes.Base.Base>();
                case "Members":
                    return MembersListIteratorBegin.Convert<Columbus.Csharp.Asg.Nodes.Base.Base>();
                case "Usings":
                    return UsingsListIteratorBegin.Convert<Columbus.Csharp.Asg.Nodes.Base.Base>();
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
                case "AttributeLists":
                    addAttributeLists(nodeId);
                    return;
                case "Externs":
                    addExterns(nodeId);
                    return;
                case "Members":
                    addMembers(nodeId);
                    return;
                case "Usings":
                    addUsings(nodeId);
                    return;
                default:
                    base.add(edge, nodeId);
                    return;
            }
        }


        // ---------- Edge getter function(s) ----------

        /// <summary>
        /// Gives back iterator for the AttributeLists edges.
        /// </summary>
        /// <returns>Returns an iterator for the AttributeLists edges.</returns>
        public ListIterator<Columbus.Csharp.Asg.Nodes.Structure.AttributeListSyntax> AttributeListsListIteratorBegin {
            get {
                return new ListIterator<Columbus.Csharp.Asg.Nodes.Structure.AttributeListSyntax>(AttributeListsContainer, fact, true);
            }
        }

        /// <summary>
        /// Gives back iterator for the AttributeLists edges.
        /// </summary>
        /// <returns>Returns an iterator for the AttributeLists edges.</returns>
        public ListIterator<Columbus.Csharp.Asg.Nodes.Structure.AttributeListSyntax> AttributeListsListIteratorEnd {
            get {
                return new ListIterator<Columbus.Csharp.Asg.Nodes.Structure.AttributeListSyntax>(AttributeListsContainer, fact, false);
            }
        }

        /// <summary>
        /// Tells whether the node has AttributeLists edges or not.
        /// </summary>
        /// <returns>Returns true if the node has at least one AttributeLists edge.</returns>
        public bool AttributeListsIsEmpty {
            get { return AttributeListsContainer.Count == 0; }
        }

        /// <summary>
        /// Gives back how many AttributeLists edges the node has.
        /// </summary>
        /// <returns>Returns with the number of AttributeLists edges.</returns>
        public uint AttributeListsSize {
            get { return (uint)(AttributeListsContainer.Count); }
        }

        /// <summary>
        /// Gives back iterator for the Externs edges.
        /// </summary>
        /// <returns>Returns an iterator for the Externs edges.</returns>
        public ListIterator<Columbus.Csharp.Asg.Nodes.Structure.ExternAliasDirectiveSyntax> ExternsListIteratorBegin {
            get {
                return new ListIterator<Columbus.Csharp.Asg.Nodes.Structure.ExternAliasDirectiveSyntax>(ExternsContainer, fact, true);
            }
        }

        /// <summary>
        /// Gives back iterator for the Externs edges.
        /// </summary>
        /// <returns>Returns an iterator for the Externs edges.</returns>
        public ListIterator<Columbus.Csharp.Asg.Nodes.Structure.ExternAliasDirectiveSyntax> ExternsListIteratorEnd {
            get {
                return new ListIterator<Columbus.Csharp.Asg.Nodes.Structure.ExternAliasDirectiveSyntax>(ExternsContainer, fact, false);
            }
        }

        /// <summary>
        /// Tells whether the node has Externs edges or not.
        /// </summary>
        /// <returns>Returns true if the node has at least one Externs edge.</returns>
        public bool ExternsIsEmpty {
            get { return ExternsContainer.Count == 0; }
        }

        /// <summary>
        /// Gives back how many Externs edges the node has.
        /// </summary>
        /// <returns>Returns with the number of Externs edges.</returns>
        public uint ExternsSize {
            get { return (uint)(ExternsContainer.Count); }
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
        /// Gives back iterator for the Usings edges.
        /// </summary>
        /// <returns>Returns an iterator for the Usings edges.</returns>
        public ListIterator<Columbus.Csharp.Asg.Nodes.Structure.UsingDirectiveSyntax> UsingsListIteratorBegin {
            get {
                return new ListIterator<Columbus.Csharp.Asg.Nodes.Structure.UsingDirectiveSyntax>(UsingsContainer, fact, true);
            }
        }

        /// <summary>
        /// Gives back iterator for the Usings edges.
        /// </summary>
        /// <returns>Returns an iterator for the Usings edges.</returns>
        public ListIterator<Columbus.Csharp.Asg.Nodes.Structure.UsingDirectiveSyntax> UsingsListIteratorEnd {
            get {
                return new ListIterator<Columbus.Csharp.Asg.Nodes.Structure.UsingDirectiveSyntax>(UsingsContainer, fact, false);
            }
        }

        /// <summary>
        /// Tells whether the node has Usings edges or not.
        /// </summary>
        /// <returns>Returns true if the node has at least one Usings edge.</returns>
        public bool UsingsIsEmpty {
            get { return UsingsContainer.Count == 0; }
        }

        /// <summary>
        /// Gives back how many Usings edges the node has.
        /// </summary>
        /// <returns>Returns with the number of Usings edges.</returns>
        public uint UsingsSize {
            get { return (uint)(UsingsContainer.Count); }
        }


        // ---------- Edge setter function(s) ----------

        /// <summary>
        /// Adds a new AttributeLists edge to the node and inserts it after the other ones.
        /// </summary>
        /// <param name="node">[in] The end point of the new AttributeLists edge.</param>
        /// <exception cref="Columbus.Csharp.Asg.CsharpException">Throws CsharpException if there is something wrong with the given node.</exception>
        public void addAttributeLists(Columbus.Csharp.Asg.Nodes.Structure.AttributeListSyntax node) {
            addAttributeLists(node.Id);
        }

        /// <summary>
        /// Adds a new AttributeLists edge to the node and inserts it after the other ones.
        /// </summary>
        /// <param name="nodeId">[in] The end point of the new AttributeLists edge.</param>
        /// <exception cref="Columbus.Csharp.Asg.CsharpException">Throws CsharpException if the given nodeId is invalid.</exception>
        public void addAttributeLists(uint nodeId) {
            if (!fact.getExist(nodeId))
                throw new CsharpException("Columbus.Csharp.Asg.Nodes.Structure.CompilationUnitSyntax.addAttributeLists(NodeId)", "The end point of the edge does not exist.");
            Columbus.Csharp.Asg.Nodes.Base.Base node = fact.getRef(nodeId);
            if (Common.getIsBaseClassKind(node.NodeKind, Types.NodeKind.ndkAttributeListSyntax)) {
                AttributeListsContainer.AddLast(nodeId);
            } else {
                throw new CsharpException("Columbus.Csharp.Asg.Nodes.Structure.CompilationUnitSyntax.setAttributeLists(NodeId)", "Invalid NodeKind (" + node.NodeKind.ToString() + ").");
            }
           setParentEdge(nodeId, (uint)Types.EdgeKind.edkCompilationUnitSyntax_AttributeLists);
            if (fact.ReverseEdges != null)
              fact.ReverseEdges.insertEdge(nodeId, this.Id, Types.EdgeKind.edkCompilationUnitSyntax_AttributeLists);
        }

        /// <summary>
        /// Adds a new Externs edge to the node and inserts it after the other ones.
        /// </summary>
        /// <param name="node">[in] The end point of the new Externs edge.</param>
        /// <exception cref="Columbus.Csharp.Asg.CsharpException">Throws CsharpException if there is something wrong with the given node.</exception>
        public void addExterns(Columbus.Csharp.Asg.Nodes.Structure.ExternAliasDirectiveSyntax node) {
            addExterns(node.Id);
        }

        /// <summary>
        /// Adds a new Externs edge to the node and inserts it after the other ones.
        /// </summary>
        /// <param name="nodeId">[in] The end point of the new Externs edge.</param>
        /// <exception cref="Columbus.Csharp.Asg.CsharpException">Throws CsharpException if the given nodeId is invalid.</exception>
        public void addExterns(uint nodeId) {
            if (!fact.getExist(nodeId))
                throw new CsharpException("Columbus.Csharp.Asg.Nodes.Structure.CompilationUnitSyntax.addExterns(NodeId)", "The end point of the edge does not exist.");
            Columbus.Csharp.Asg.Nodes.Base.Base node = fact.getRef(nodeId);
            if (Common.getIsBaseClassKind(node.NodeKind, Types.NodeKind.ndkExternAliasDirectiveSyntax)) {
                ExternsContainer.AddLast(nodeId);
            } else {
                throw new CsharpException("Columbus.Csharp.Asg.Nodes.Structure.CompilationUnitSyntax.setExterns(NodeId)", "Invalid NodeKind (" + node.NodeKind.ToString() + ").");
            }
           setParentEdge(nodeId, (uint)Types.EdgeKind.edkCompilationUnitSyntax_Externs);
            if (fact.ReverseEdges != null)
              fact.ReverseEdges.insertEdge(nodeId, this.Id, Types.EdgeKind.edkCompilationUnitSyntax_Externs);
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
                throw new CsharpException("Columbus.Csharp.Asg.Nodes.Structure.CompilationUnitSyntax.addMembers(NodeId)", "The end point of the edge does not exist.");
            Columbus.Csharp.Asg.Nodes.Base.Base node = fact.getRef(nodeId);
            if (Common.getIsBaseClassKind(node.NodeKind, Types.NodeKind.ndkMemberDeclarationSyntax)) {
                MembersContainer.AddLast(nodeId);
            } else {
                throw new CsharpException("Columbus.Csharp.Asg.Nodes.Structure.CompilationUnitSyntax.setMembers(NodeId)", "Invalid NodeKind (" + node.NodeKind.ToString() + ").");
            }
           setParentEdge(nodeId, (uint)Types.EdgeKind.edkCompilationUnitSyntax_Members);
            if (fact.ReverseEdges != null)
              fact.ReverseEdges.insertEdge(nodeId, this.Id, Types.EdgeKind.edkCompilationUnitSyntax_Members);
        }

        /// <summary>
        /// Adds a new Usings edge to the node and inserts it after the other ones.
        /// </summary>
        /// <param name="node">[in] The end point of the new Usings edge.</param>
        /// <exception cref="Columbus.Csharp.Asg.CsharpException">Throws CsharpException if there is something wrong with the given node.</exception>
        public void addUsings(Columbus.Csharp.Asg.Nodes.Structure.UsingDirectiveSyntax node) {
            addUsings(node.Id);
        }

        /// <summary>
        /// Adds a new Usings edge to the node and inserts it after the other ones.
        /// </summary>
        /// <param name="nodeId">[in] The end point of the new Usings edge.</param>
        /// <exception cref="Columbus.Csharp.Asg.CsharpException">Throws CsharpException if the given nodeId is invalid.</exception>
        public void addUsings(uint nodeId) {
            if (!fact.getExist(nodeId))
                throw new CsharpException("Columbus.Csharp.Asg.Nodes.Structure.CompilationUnitSyntax.addUsings(NodeId)", "The end point of the edge does not exist.");
            Columbus.Csharp.Asg.Nodes.Base.Base node = fact.getRef(nodeId);
            if (Common.getIsBaseClassKind(node.NodeKind, Types.NodeKind.ndkUsingDirectiveSyntax)) {
                UsingsContainer.AddLast(nodeId);
            } else {
                throw new CsharpException("Columbus.Csharp.Asg.Nodes.Structure.CompilationUnitSyntax.setUsings(NodeId)", "Invalid NodeKind (" + node.NodeKind.ToString() + ").");
            }
           setParentEdge(nodeId, (uint)Types.EdgeKind.edkCompilationUnitSyntax_Usings);
            if (fact.ReverseEdges != null)
              fact.ReverseEdges.insertEdge(nodeId, this.Id, Types.EdgeKind.edkCompilationUnitSyntax_Usings);
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


            foreach (var AttributeLists in AttributeListsContainer) {
              io.writeUInt4(AttributeLists);
            }
            io.writeUInt4(0); // This is the end sign

            foreach (var Externs in ExternsContainer) {
              io.writeUInt4(Externs);
            }
            io.writeUInt4(0); // This is the end sign

            foreach (var Members in MembersContainer) {
              io.writeUInt4(Members);
            }
            io.writeUInt4(0); // This is the end sign

            foreach (var Usings in UsingsContainer) {
              io.writeUInt4(Usings);
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

            uint _id;

            _id = binIo.readUInt4();
            while (_id != 0) {
              AttributeListsContainer.AddLast(_id);
              setParentEdge(_id, (uint)Types.EdgeKind.edkCompilationUnitSyntax_AttributeLists);
              _id = binIo.readUInt4();
            }

            _id = binIo.readUInt4();
            while (_id != 0) {
              ExternsContainer.AddLast(_id);
              setParentEdge(_id, (uint)Types.EdgeKind.edkCompilationUnitSyntax_Externs);
              _id = binIo.readUInt4();
            }

            _id = binIo.readUInt4();
            while (_id != 0) {
              MembersContainer.AddLast(_id);
              setParentEdge(_id, (uint)Types.EdgeKind.edkCompilationUnitSyntax_Members);
              _id = binIo.readUInt4();
            }

            _id = binIo.readUInt4();
            while (_id != 0) {
              UsingsContainer.AddLast(_id);
              setParentEdge(_id, (uint)Types.EdgeKind.edkCompilationUnitSyntax_Usings);
              _id = binIo.readUInt4();
            }
        }

    }

}
