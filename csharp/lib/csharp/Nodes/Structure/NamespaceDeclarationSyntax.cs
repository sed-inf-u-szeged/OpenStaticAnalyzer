/*
 *  This file is part of OpenStaticAnalyzer.
 *
 *  Copyright (c) 2004-2018 Department of Software Engineering - University of Szeged
 *
 *  Licensed under Version 1.2 of the EUPL (the "Licence");
 *
 *  You may not use this work except in compliance with the Licence.
 *
 *  You may obtain a copy of the Licence in the LICENSE file or at:
 *
 *  https://joinup.ec.europa.eu/software/page/eupl
 *
 *  Unless required by applicable law or agreed to in writing, software
 *  distributed under the Licence is distributed on an "AS IS" basis,
 *  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *  See the Licence for the specific language governing permissions and
 *  limitations under the Licence.
 */

using System;
using System.Text;
using System.Diagnostics;
using System.Collections.Generic;

namespace Columbus.Csharp.Asg.Nodes.Structure {

    /// <summary>
    /// NamespaceDeclarationSyntax class, which represents the structure::NamespaceDeclarationSyntax node.
    /// </summary>
    [DebuggerDisplay("{DemangledName}")]
#if (CSHARP_INTERNAL)
    internal
#else
    public
#endif
    class NamespaceDeclarationSyntax : MemberDeclarationSyntax {


        // ---------- Edges ----------

        /// <summary>Container stores the id of the nodes the Externs edge points to.</summary>
        protected LinkedList<uint> ExternsContainer;

        /// <summary>Container stores the id of the nodes the Members edge points to.</summary>
        protected LinkedList<uint> MembersContainer;

        /// <summary>The id of the node the Name edge points to.</summary>
        protected uint m_Name;

        /// <summary>Container stores the id of the nodes the Usings edge points to.</summary>
        protected LinkedList<uint> UsingsContainer;

        /// <summary>
        /// Constructor, only factory can instantiates nodes.
        /// </summary>
        /// <param name="nodeId">[in] The id of the node.</param>
        /// <param name="factory">[in] Poiter to the Factory the node belongs to.</param>
        public NamespaceDeclarationSyntax(uint nodeId, Factory factory) : base(nodeId, factory) {
            ExternsContainer = new LinkedList<uint>();
            MembersContainer = new LinkedList<uint>();
            m_Name = 0;
            UsingsContainer = new LinkedList<uint>();
        }

        /// <summary>
        /// Gives back the NodeKind of the node.
        /// </summary>
        /// <returns>Returns with the NodeKind.</returns>
        public override Types.NodeKind NodeKind {
            get { return Types.NodeKind.ndkNamespaceDeclarationSyntax; }
        }


        // ---------- Reflection getter function ----------

        /// <summary>
        /// Gives back the begin iterator for the edge specified
        /// </summary>
        /// <param name="edge">[in] The multiple edge for which the iterator is requested</param>
        public override ListIterator<Columbus.Csharp.Asg.Nodes.Base.Base> GetListIteratorBegin(string edge) {
            switch(edge) {
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
        /// Gives back the id of the node the Name edge points to.
        /// </summary>
        /// <returns>Returns the end point of the m_Name edge.</returns>
        /// <exception cref="Columbus.Csharp.Asg.CsharpException">Throws CsharpException if the edge id is invalid.</exception>
        public uint getName() {
            if (fact.getIsFiltered(m_Name))
                return 1;
            else
                return m_Name;
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
                throw new CsharpException("Columbus.Csharp.Asg.Nodes.Structure.NamespaceDeclarationSyntax.addExterns(NodeId)", "The end point of the edge does not exist.");
            Columbus.Csharp.Asg.Nodes.Base.Base node = fact.getRef(nodeId);
            if (Common.getIsBaseClassKind(node.NodeKind, Types.NodeKind.ndkExternAliasDirectiveSyntax)) {
                ExternsContainer.AddLast(nodeId);
            } else {
                throw new CsharpException("Columbus.Csharp.Asg.Nodes.Structure.NamespaceDeclarationSyntax.setExterns(NodeId)", "Invalid NodeKind (" + node.NodeKind.ToString() + ").");
            }
           setParentEdge(nodeId, (uint)Types.EdgeKind.edkNamespaceDeclarationSyntax_Externs);
            if (fact.ReverseEdges != null)
              fact.ReverseEdges.insertEdge(nodeId, this.Id, Types.EdgeKind.edkNamespaceDeclarationSyntax_Externs);
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
                throw new CsharpException("Columbus.Csharp.Asg.Nodes.Structure.NamespaceDeclarationSyntax.addMembers(NodeId)", "The end point of the edge does not exist.");
            Columbus.Csharp.Asg.Nodes.Base.Base node = fact.getRef(nodeId);
            if (Common.getIsBaseClassKind(node.NodeKind, Types.NodeKind.ndkMemberDeclarationSyntax)) {
                MembersContainer.AddLast(nodeId);
            } else {
                throw new CsharpException("Columbus.Csharp.Asg.Nodes.Structure.NamespaceDeclarationSyntax.setMembers(NodeId)", "Invalid NodeKind (" + node.NodeKind.ToString() + ").");
            }
           setParentEdge(nodeId, (uint)Types.EdgeKind.edkNamespaceDeclarationSyntax_Members);
            if (fact.ReverseEdges != null)
              fact.ReverseEdges.insertEdge(nodeId, this.Id, Types.EdgeKind.edkNamespaceDeclarationSyntax_Members);
        }

        /// <summary>
        /// Sets the Name edge.
        /// </summary>
        /// <param name="nodeId">[in] The new end point of the Name edge or 0. With 0 the edge can be deleted.</param>
        /// <exception cref="Columbus.Csharp.Asg.CsharpException">Throws CsharpException if the nodeId is invalid.</exception>
        public void setName(uint nodeId) {
            if (nodeId != 0) {
                if (!fact.getExist(nodeId))
                    throw new CsharpException("Columbus.Csharp.Asg.Nodes.Structure.NamespaceDeclarationSyntax.setName(NodeId)", "The end point of the edge does not exist.");

                Columbus.Csharp.Asg.Nodes.Base.Base node = fact.getRef(nodeId);
                if (Common.getIsBaseClassKind(node.NodeKind, Types.NodeKind.ndkNameSyntax)) {
                    if (m_Name != 0) {
                        removeParentEdge(m_Name);
                    }
                    m_Name = nodeId;
                    setParentEdge(m_Name, (uint)Types.EdgeKind.edkNamespaceDeclarationSyntax_Name);
                } else {
                    throw new CsharpException("Columbus.Csharp.Asg.Nodes.Structure.NamespaceDeclarationSyntax.setName(NodeId)", "Invalid NodeKind (" + node.NodeKind.ToString() + ").");
                }
            } else {
                if (m_Name != 0) {
                    removeParentEdge(m_Name);
                }
                m_Name = 0;
            }
        }

        /// <summary>
        /// Sets the Name edge.
        /// </summary>
        /// <param name="node">[in] The new end point of the Name edge.</param>
        /// <exception cref="Columbus.Csharp.Asg.CsharpException">Throws CsharpException if there's something wrong with the given node.</exception>
        public void setName(Columbus.Csharp.Asg.Nodes.Expression.NameSyntax node) {
            if (m_Name != 0) {
                removeParentEdge(m_Name);
            }
            m_Name = node.Id;
            setParentEdge(m_Name, (uint)Types.EdgeKind.edkNamespaceDeclarationSyntax_Name);
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
                throw new CsharpException("Columbus.Csharp.Asg.Nodes.Structure.NamespaceDeclarationSyntax.addUsings(NodeId)", "The end point of the edge does not exist.");
            Columbus.Csharp.Asg.Nodes.Base.Base node = fact.getRef(nodeId);
            if (Common.getIsBaseClassKind(node.NodeKind, Types.NodeKind.ndkUsingDirectiveSyntax)) {
                UsingsContainer.AddLast(nodeId);
            } else {
                throw new CsharpException("Columbus.Csharp.Asg.Nodes.Structure.NamespaceDeclarationSyntax.setUsings(NodeId)", "Invalid NodeKind (" + node.NodeKind.ToString() + ").");
            }
           setParentEdge(nodeId, (uint)Types.EdgeKind.edkNamespaceDeclarationSyntax_Usings);
            if (fact.ReverseEdges != null)
              fact.ReverseEdges.insertEdge(nodeId, this.Id, Types.EdgeKind.edkNamespaceDeclarationSyntax_Usings);
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

            io.writeUInt4(m_Name);


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

            m_Name =  binIo.readUInt4();
            if (m_Name != 0)
              setParentEdge(m_Name,(uint)Types.EdgeKind.edkNamespaceDeclarationSyntax_Name);

            uint _id;

            _id = binIo.readUInt4();
            while (_id != 0) {
              ExternsContainer.AddLast(_id);
              setParentEdge(_id, (uint)Types.EdgeKind.edkNamespaceDeclarationSyntax_Externs);
              _id = binIo.readUInt4();
            }

            _id = binIo.readUInt4();
            while (_id != 0) {
              MembersContainer.AddLast(_id);
              setParentEdge(_id, (uint)Types.EdgeKind.edkNamespaceDeclarationSyntax_Members);
              _id = binIo.readUInt4();
            }

            _id = binIo.readUInt4();
            while (_id != 0) {
              UsingsContainer.AddLast(_id);
              setParentEdge(_id, (uint)Types.EdgeKind.edkNamespaceDeclarationSyntax_Usings);
              _id = binIo.readUInt4();
            }
        }

    }

}
