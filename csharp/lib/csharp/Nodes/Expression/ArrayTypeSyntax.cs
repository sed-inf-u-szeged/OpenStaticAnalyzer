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

namespace Columbus.Csharp.Asg.Nodes.Expression {

    /// <summary>
    /// ArrayTypeSyntax class, which represents the expression::ArrayTypeSyntax node.
    /// </summary>
    [DebuggerDisplay("{DemangledName}")]
#if (CSHARP_INTERNAL)
    internal
#else
    public
#endif
    class ArrayTypeSyntax : TypeSyntax {


        // ---------- Edges ----------

        /// <summary>The id of the node the ElementType edge points to.</summary>
        protected uint m_ElementType;

        /// <summary>Container stores the id of the nodes the RankSpecifiers edge points to.</summary>
        protected LinkedList<uint> RankSpecifiersContainer;

        /// <summary>
        /// Constructor, only factory can instantiates nodes.
        /// </summary>
        /// <param name="nodeId">[in] The id of the node.</param>
        /// <param name="factory">[in] Poiter to the Factory the node belongs to.</param>
        public ArrayTypeSyntax(uint nodeId, Factory factory) : base(nodeId, factory) {
            m_ElementType = 0;
            RankSpecifiersContainer = new LinkedList<uint>();
        }

        /// <summary>
        /// Gives back the NodeKind of the node.
        /// </summary>
        /// <returns>Returns with the NodeKind.</returns>
        public override Types.NodeKind NodeKind {
            get { return Types.NodeKind.ndkArrayTypeSyntax; }
        }


        // ---------- Reflection getter function ----------

        /// <summary>
        /// Gives back the begin iterator for the edge specified
        /// </summary>
        /// <param name="edge">[in] The multiple edge for which the iterator is requested</param>
        public override ListIterator<Columbus.Csharp.Asg.Nodes.Base.Base> GetListIteratorBegin(string edge) {
            switch(edge) {
                case "RankSpecifiers":
                    return RankSpecifiersListIteratorBegin.Convert<Columbus.Csharp.Asg.Nodes.Base.Base>();
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
                case "RankSpecifiers":
                    addRankSpecifiers(nodeId);
                    return;
                default:
                    base.add(edge, nodeId);
                    return;
            }
        }


        // ---------- Edge getter function(s) ----------

        /// <summary>
        /// Gives back the id of the node the ElementType edge points to.
        /// </summary>
        /// <returns>Returns the end point of the m_ElementType edge.</returns>
        /// <exception cref="Columbus.Csharp.Asg.CsharpException">Throws CsharpException if the edge id is invalid.</exception>
        public uint getElementType() {
            if (fact.getIsFiltered(m_ElementType))
                return 1;
            else
                return m_ElementType;
        }

        /// <summary>
        /// Gives back iterator for the RankSpecifiers edges.
        /// </summary>
        /// <returns>Returns an iterator for the RankSpecifiers edges.</returns>
        public ListIterator<Columbus.Csharp.Asg.Nodes.Structure.ArrayRankSpecifierSyntax> RankSpecifiersListIteratorBegin {
            get {
                return new ListIterator<Columbus.Csharp.Asg.Nodes.Structure.ArrayRankSpecifierSyntax>(RankSpecifiersContainer, fact, true);
            }
        }

        /// <summary>
        /// Gives back iterator for the RankSpecifiers edges.
        /// </summary>
        /// <returns>Returns an iterator for the RankSpecifiers edges.</returns>
        public ListIterator<Columbus.Csharp.Asg.Nodes.Structure.ArrayRankSpecifierSyntax> RankSpecifiersListIteratorEnd {
            get {
                return new ListIterator<Columbus.Csharp.Asg.Nodes.Structure.ArrayRankSpecifierSyntax>(RankSpecifiersContainer, fact, false);
            }
        }

        /// <summary>
        /// Tells whether the node has RankSpecifiers edges or not.
        /// </summary>
        /// <returns>Returns true if the node has at least one RankSpecifiers edge.</returns>
        public bool RankSpecifiersIsEmpty {
            get { return RankSpecifiersContainer.Count == 0; }
        }

        /// <summary>
        /// Gives back how many RankSpecifiers edges the node has.
        /// </summary>
        /// <returns>Returns with the number of RankSpecifiers edges.</returns>
        public uint RankSpecifiersSize {
            get { return (uint)(RankSpecifiersContainer.Count); }
        }


        // ---------- Edge setter function(s) ----------

        /// <summary>
        /// Sets the ElementType edge.
        /// </summary>
        /// <param name="nodeId">[in] The new end point of the ElementType edge or 0. With 0 the edge can be deleted.</param>
        /// <exception cref="Columbus.Csharp.Asg.CsharpException">Throws CsharpException if the nodeId is invalid.</exception>
        public void setElementType(uint nodeId) {
            if (nodeId != 0) {
                if (!fact.getExist(nodeId))
                    throw new CsharpException("Columbus.Csharp.Asg.Nodes.Expression.ArrayTypeSyntax.setElementType(NodeId)", "The end point of the edge does not exist.");

                Columbus.Csharp.Asg.Nodes.Base.Base node = fact.getRef(nodeId);
                if (Common.getIsBaseClassKind(node.NodeKind, Types.NodeKind.ndkTypeSyntax)) {
                    if (m_ElementType != 0) {
                        removeParentEdge(m_ElementType);
                    }
                    m_ElementType = nodeId;
                    setParentEdge(m_ElementType, (uint)Types.EdgeKind.edkArrayTypeSyntax_ElementType);
                } else {
                    throw new CsharpException("Columbus.Csharp.Asg.Nodes.Expression.ArrayTypeSyntax.setElementType(NodeId)", "Invalid NodeKind (" + node.NodeKind.ToString() + ").");
                }
            } else {
                if (m_ElementType != 0) {
                    removeParentEdge(m_ElementType);
                }
                m_ElementType = 0;
            }
        }

        /// <summary>
        /// Sets the ElementType edge.
        /// </summary>
        /// <param name="node">[in] The new end point of the ElementType edge.</param>
        /// <exception cref="Columbus.Csharp.Asg.CsharpException">Throws CsharpException if there's something wrong with the given node.</exception>
        public void setElementType(Columbus.Csharp.Asg.Nodes.Expression.TypeSyntax node) {
            if (m_ElementType != 0) {
                removeParentEdge(m_ElementType);
            }
            m_ElementType = node.Id;
            setParentEdge(m_ElementType, (uint)Types.EdgeKind.edkArrayTypeSyntax_ElementType);
        }

        /// <summary>
        /// Adds a new RankSpecifiers edge to the node and inserts it after the other ones.
        /// </summary>
        /// <param name="node">[in] The end point of the new RankSpecifiers edge.</param>
        /// <exception cref="Columbus.Csharp.Asg.CsharpException">Throws CsharpException if there is something wrong with the given node.</exception>
        public void addRankSpecifiers(Columbus.Csharp.Asg.Nodes.Structure.ArrayRankSpecifierSyntax node) {
            addRankSpecifiers(node.Id);
        }

        /// <summary>
        /// Adds a new RankSpecifiers edge to the node and inserts it after the other ones.
        /// </summary>
        /// <param name="nodeId">[in] The end point of the new RankSpecifiers edge.</param>
        /// <exception cref="Columbus.Csharp.Asg.CsharpException">Throws CsharpException if the given nodeId is invalid.</exception>
        public void addRankSpecifiers(uint nodeId) {
            if (!fact.getExist(nodeId))
                throw new CsharpException("Columbus.Csharp.Asg.Nodes.Expression.ArrayTypeSyntax.addRankSpecifiers(NodeId)", "The end point of the edge does not exist.");
            Columbus.Csharp.Asg.Nodes.Base.Base node = fact.getRef(nodeId);
            if (Common.getIsBaseClassKind(node.NodeKind, Types.NodeKind.ndkArrayRankSpecifierSyntax)) {
                RankSpecifiersContainer.AddLast(nodeId);
            } else {
                throw new CsharpException("Columbus.Csharp.Asg.Nodes.Expression.ArrayTypeSyntax.setRankSpecifiers(NodeId)", "Invalid NodeKind (" + node.NodeKind.ToString() + ").");
            }
           setParentEdge(nodeId, (uint)Types.EdgeKind.edkArrayTypeSyntax_RankSpecifiers);
            if (fact.ReverseEdges != null)
              fact.ReverseEdges.insertEdge(nodeId, this.Id, Types.EdgeKind.edkArrayTypeSyntax_RankSpecifiers);
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

            io.writeUInt4(m_ElementType);


            foreach (var RankSpecifiers in RankSpecifiersContainer) {
              io.writeUInt4(RankSpecifiers);
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

            m_ElementType =  binIo.readUInt4();
            if (m_ElementType != 0)
              setParentEdge(m_ElementType,(uint)Types.EdgeKind.edkArrayTypeSyntax_ElementType);

            uint _id;

            _id = binIo.readUInt4();
            while (_id != 0) {
              RankSpecifiersContainer.AddLast(_id);
              setParentEdge(_id, (uint)Types.EdgeKind.edkArrayTypeSyntax_RankSpecifiers);
              _id = binIo.readUInt4();
            }
        }

    }

}
