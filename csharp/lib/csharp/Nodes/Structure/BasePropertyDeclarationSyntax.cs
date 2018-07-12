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
    /// BasePropertyDeclarationSyntax class, which represents the structure::BasePropertyDeclarationSyntax node.
    /// </summary>
    [DebuggerDisplay("{DemangledName}")]
#if (CSHARP_INTERNAL)
    internal
#else
    public
#endif
    class BasePropertyDeclarationSyntax : MemberDeclarationSyntax {


        // ---------- Edges ----------

        /// <summary>The id of the node the AccessorList edge points to.</summary>
        protected uint m_AccessorList;

        /// <summary>Container stores the id of the nodes the AttributeLists edge points to.</summary>
        protected LinkedList<uint> AttributeListsContainer;

        /// <summary>The id of the node the ExplicitInterfaceSpecifier edge points to.</summary>
        protected uint m_ExplicitInterfaceSpecifier;

        /// <summary>The id of the node the Type edge points to.</summary>
        protected uint m_Type;

        /// <summary>
        /// Constructor, only factory can instantiates nodes.
        /// </summary>
        /// <param name="nodeId">[in] The id of the node.</param>
        /// <param name="factory">[in] Poiter to the Factory the node belongs to.</param>
        public BasePropertyDeclarationSyntax(uint nodeId, Factory factory) : base(nodeId, factory) {
            m_AccessorList = 0;
            AttributeListsContainer = new LinkedList<uint>();
            m_ExplicitInterfaceSpecifier = 0;
            m_Type = 0;
        }

        /// <summary>
        /// Gives back the NodeKind of the node.
        /// </summary>
        /// <returns>Returns with the NodeKind.</returns>
        public override Types.NodeKind NodeKind {
            get { return Types.NodeKind.ndkBasePropertyDeclarationSyntax; }
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
                default:
                    base.add(edge, nodeId);
                    return;
            }
        }


        // ---------- Edge getter function(s) ----------

        /// <summary>
        /// Gives back the id of the node the AccessorList edge points to.
        /// </summary>
        /// <returns>Returns the end point of the m_AccessorList edge.</returns>
        /// <exception cref="Columbus.Csharp.Asg.CsharpException">Throws CsharpException if the edge id is invalid.</exception>
        public uint getAccessorList() {
            if (fact.getIsFiltered(m_AccessorList))
                return 1;
            else
                return m_AccessorList;
        }

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
        /// Gives back the id of the node the ExplicitInterfaceSpecifier edge points to.
        /// </summary>
        /// <returns>Returns the end point of the m_ExplicitInterfaceSpecifier edge.</returns>
        /// <exception cref="Columbus.Csharp.Asg.CsharpException">Throws CsharpException if the edge id is invalid.</exception>
        public uint getExplicitInterfaceSpecifier() {
            if (fact.getIsFiltered(m_ExplicitInterfaceSpecifier))
                return 1;
            else
                return m_ExplicitInterfaceSpecifier;
        }

        /// <summary>
        /// Gives back the id of the node the Type edge points to.
        /// </summary>
        /// <returns>Returns the end point of the m_Type edge.</returns>
        /// <exception cref="Columbus.Csharp.Asg.CsharpException">Throws CsharpException if the edge id is invalid.</exception>
        public uint getType() {
            if (fact.getIsFiltered(m_Type))
                return 1;
            else
                return m_Type;
        }


        // ---------- Edge setter function(s) ----------

        /// <summary>
        /// Sets the AccessorList edge.
        /// </summary>
        /// <param name="nodeId">[in] The new end point of the AccessorList edge or 0. With 0 the edge can be deleted.</param>
        /// <exception cref="Columbus.Csharp.Asg.CsharpException">Throws CsharpException if the nodeId is invalid.</exception>
        public void setAccessorList(uint nodeId) {
            if (nodeId != 0) {
                if (!fact.getExist(nodeId))
                    throw new CsharpException("Columbus.Csharp.Asg.Nodes.Structure.BasePropertyDeclarationSyntax.setAccessorList(NodeId)", "The end point of the edge does not exist.");

                Columbus.Csharp.Asg.Nodes.Base.Base node = fact.getRef(nodeId);
                if (Common.getIsBaseClassKind(node.NodeKind, Types.NodeKind.ndkAccessorListSyntax)) {
                    if (m_AccessorList != 0) {
                        removeParentEdge(m_AccessorList);
                    }
                    m_AccessorList = nodeId;
                    setParentEdge(m_AccessorList, (uint)Types.EdgeKind.edkBasePropertyDeclarationSyntax_AccessorList);
                } else {
                    throw new CsharpException("Columbus.Csharp.Asg.Nodes.Structure.BasePropertyDeclarationSyntax.setAccessorList(NodeId)", "Invalid NodeKind (" + node.NodeKind.ToString() + ").");
                }
            } else {
                if (m_AccessorList != 0) {
                    removeParentEdge(m_AccessorList);
                }
                m_AccessorList = 0;
            }
        }

        /// <summary>
        /// Sets the AccessorList edge.
        /// </summary>
        /// <param name="node">[in] The new end point of the AccessorList edge.</param>
        /// <exception cref="Columbus.Csharp.Asg.CsharpException">Throws CsharpException if there's something wrong with the given node.</exception>
        public void setAccessorList(Columbus.Csharp.Asg.Nodes.Structure.AccessorListSyntax node) {
            if (m_AccessorList != 0) {
                removeParentEdge(m_AccessorList);
            }
            m_AccessorList = node.Id;
            setParentEdge(m_AccessorList, (uint)Types.EdgeKind.edkBasePropertyDeclarationSyntax_AccessorList);
        }

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
                throw new CsharpException("Columbus.Csharp.Asg.Nodes.Structure.BasePropertyDeclarationSyntax.addAttributeLists(NodeId)", "The end point of the edge does not exist.");
            Columbus.Csharp.Asg.Nodes.Base.Base node = fact.getRef(nodeId);
            if (Common.getIsBaseClassKind(node.NodeKind, Types.NodeKind.ndkAttributeListSyntax)) {
                AttributeListsContainer.AddLast(nodeId);
            } else {
                throw new CsharpException("Columbus.Csharp.Asg.Nodes.Structure.BasePropertyDeclarationSyntax.setAttributeLists(NodeId)", "Invalid NodeKind (" + node.NodeKind.ToString() + ").");
            }
           setParentEdge(nodeId, (uint)Types.EdgeKind.edkBasePropertyDeclarationSyntax_AttributeLists);
            if (fact.ReverseEdges != null)
              fact.ReverseEdges.insertEdge(nodeId, this.Id, Types.EdgeKind.edkBasePropertyDeclarationSyntax_AttributeLists);
        }

        /// <summary>
        /// Sets the ExplicitInterfaceSpecifier edge.
        /// </summary>
        /// <param name="nodeId">[in] The new end point of the ExplicitInterfaceSpecifier edge or 0. With 0 the edge can be deleted.</param>
        /// <exception cref="Columbus.Csharp.Asg.CsharpException">Throws CsharpException if the nodeId is invalid.</exception>
        public void setExplicitInterfaceSpecifier(uint nodeId) {
            if (nodeId != 0) {
                if (!fact.getExist(nodeId))
                    throw new CsharpException("Columbus.Csharp.Asg.Nodes.Structure.BasePropertyDeclarationSyntax.setExplicitInterfaceSpecifier(NodeId)", "The end point of the edge does not exist.");

                Columbus.Csharp.Asg.Nodes.Base.Base node = fact.getRef(nodeId);
                if (Common.getIsBaseClassKind(node.NodeKind, Types.NodeKind.ndkExplicitInterfaceSpecifierSyntax)) {
                    if (m_ExplicitInterfaceSpecifier != 0) {
                        removeParentEdge(m_ExplicitInterfaceSpecifier);
                    }
                    m_ExplicitInterfaceSpecifier = nodeId;
                    setParentEdge(m_ExplicitInterfaceSpecifier, (uint)Types.EdgeKind.edkBasePropertyDeclarationSyntax_ExplicitInterfaceSpecifier);
                } else {
                    throw new CsharpException("Columbus.Csharp.Asg.Nodes.Structure.BasePropertyDeclarationSyntax.setExplicitInterfaceSpecifier(NodeId)", "Invalid NodeKind (" + node.NodeKind.ToString() + ").");
                }
            } else {
                if (m_ExplicitInterfaceSpecifier != 0) {
                    removeParentEdge(m_ExplicitInterfaceSpecifier);
                }
                m_ExplicitInterfaceSpecifier = 0;
            }
        }

        /// <summary>
        /// Sets the ExplicitInterfaceSpecifier edge.
        /// </summary>
        /// <param name="node">[in] The new end point of the ExplicitInterfaceSpecifier edge.</param>
        /// <exception cref="Columbus.Csharp.Asg.CsharpException">Throws CsharpException if there's something wrong with the given node.</exception>
        public void setExplicitInterfaceSpecifier(Columbus.Csharp.Asg.Nodes.Structure.ExplicitInterfaceSpecifierSyntax node) {
            if (m_ExplicitInterfaceSpecifier != 0) {
                removeParentEdge(m_ExplicitInterfaceSpecifier);
            }
            m_ExplicitInterfaceSpecifier = node.Id;
            setParentEdge(m_ExplicitInterfaceSpecifier, (uint)Types.EdgeKind.edkBasePropertyDeclarationSyntax_ExplicitInterfaceSpecifier);
        }

        /// <summary>
        /// Sets the Type edge.
        /// </summary>
        /// <param name="nodeId">[in] The new end point of the Type edge or 0. With 0 the edge can be deleted.</param>
        /// <exception cref="Columbus.Csharp.Asg.CsharpException">Throws CsharpException if the nodeId is invalid.</exception>
        public void setType(uint nodeId) {
            if (nodeId != 0) {
                if (!fact.getExist(nodeId))
                    throw new CsharpException("Columbus.Csharp.Asg.Nodes.Structure.BasePropertyDeclarationSyntax.setType(NodeId)", "The end point of the edge does not exist.");

                Columbus.Csharp.Asg.Nodes.Base.Base node = fact.getRef(nodeId);
                if (Common.getIsBaseClassKind(node.NodeKind, Types.NodeKind.ndkTypeSyntax)) {
                    if (m_Type != 0) {
                        removeParentEdge(m_Type);
                    }
                    m_Type = nodeId;
                    setParentEdge(m_Type, (uint)Types.EdgeKind.edkBasePropertyDeclarationSyntax_Type);
                } else {
                    throw new CsharpException("Columbus.Csharp.Asg.Nodes.Structure.BasePropertyDeclarationSyntax.setType(NodeId)", "Invalid NodeKind (" + node.NodeKind.ToString() + ").");
                }
            } else {
                if (m_Type != 0) {
                    removeParentEdge(m_Type);
                }
                m_Type = 0;
            }
        }

        /// <summary>
        /// Sets the Type edge.
        /// </summary>
        /// <param name="node">[in] The new end point of the Type edge.</param>
        /// <exception cref="Columbus.Csharp.Asg.CsharpException">Throws CsharpException if there's something wrong with the given node.</exception>
        public void setType(Columbus.Csharp.Asg.Nodes.Expression.TypeSyntax node) {
            if (m_Type != 0) {
                removeParentEdge(m_Type);
            }
            m_Type = node.Id;
            setParentEdge(m_Type, (uint)Types.EdgeKind.edkBasePropertyDeclarationSyntax_Type);
        }

        /// <summary>
        /// Saves the node.
        /// </summary>
        /// <param name="io">[in] The node is written into io.</param>
        /// <exception cref="Columbus.ColumbusIOException">Throws ColumbusIOException if there is something wrong with the file.</exception>
        public override void save(IO io) {
            base.save(io);

            io.writeUInt4(m_AccessorList);
            io.writeUInt4(m_ExplicitInterfaceSpecifier);
            io.writeUInt4(m_Type);


            foreach (var AttributeLists in AttributeListsContainer) {
              io.writeUInt4(AttributeLists);
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

            m_AccessorList =  binIo.readUInt4();
            if (m_AccessorList != 0)
              setParentEdge(m_AccessorList,(uint)Types.EdgeKind.edkBasePropertyDeclarationSyntax_AccessorList);

            m_ExplicitInterfaceSpecifier =  binIo.readUInt4();
            if (m_ExplicitInterfaceSpecifier != 0)
              setParentEdge(m_ExplicitInterfaceSpecifier,(uint)Types.EdgeKind.edkBasePropertyDeclarationSyntax_ExplicitInterfaceSpecifier);

            m_Type =  binIo.readUInt4();
            if (m_Type != 0)
              setParentEdge(m_Type,(uint)Types.EdgeKind.edkBasePropertyDeclarationSyntax_Type);

            uint _id;

            _id = binIo.readUInt4();
            while (_id != 0) {
              AttributeListsContainer.AddLast(_id);
              setParentEdge(_id, (uint)Types.EdgeKind.edkBasePropertyDeclarationSyntax_AttributeLists);
              _id = binIo.readUInt4();
            }
        }

    }

}
