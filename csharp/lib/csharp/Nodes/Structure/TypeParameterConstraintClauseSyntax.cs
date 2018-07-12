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
    /// TypeParameterConstraintClauseSyntax class, which represents the structure::TypeParameterConstraintClauseSyntax node.
    /// </summary>
    [DebuggerDisplay("{DemangledName}")]
#if (CSHARP_INTERNAL)
    internal
#else
    public
#endif
    class TypeParameterConstraintClauseSyntax : Columbus.Csharp.Asg.Nodes.Base.Positioned {


        // ---------- Edges ----------

        /// <summary>Container stores the id of the nodes the Constraints edge points to.</summary>
        protected LinkedList<uint> ConstraintsContainer;

        /// <summary>The id of the node the Name edge points to.</summary>
        protected uint m_Name;

        /// <summary>
        /// Constructor, only factory can instantiates nodes.
        /// </summary>
        /// <param name="nodeId">[in] The id of the node.</param>
        /// <param name="factory">[in] Poiter to the Factory the node belongs to.</param>
        public TypeParameterConstraintClauseSyntax(uint nodeId, Factory factory) : base(nodeId, factory) {
            ConstraintsContainer = new LinkedList<uint>();
            m_Name = 0;
        }

        /// <summary>
        /// Gives back the NodeKind of the node.
        /// </summary>
        /// <returns>Returns with the NodeKind.</returns>
        public override Types.NodeKind NodeKind {
            get { return Types.NodeKind.ndkTypeParameterConstraintClauseSyntax; }
        }


        // ---------- Reflection getter function ----------

        /// <summary>
        /// Gives back the begin iterator for the edge specified
        /// </summary>
        /// <param name="edge">[in] The multiple edge for which the iterator is requested</param>
        public override ListIterator<Columbus.Csharp.Asg.Nodes.Base.Base> GetListIteratorBegin(string edge) {
            switch(edge) {
                case "Constraints":
                    return ConstraintsListIteratorBegin.Convert<Columbus.Csharp.Asg.Nodes.Base.Base>();
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
                case "Constraints":
                    addConstraints(nodeId);
                    return;
                default:
                    base.add(edge, nodeId);
                    return;
            }
        }


        // ---------- Edge getter function(s) ----------

        /// <summary>
        /// Gives back iterator for the Constraints edges.
        /// </summary>
        /// <returns>Returns an iterator for the Constraints edges.</returns>
        public ListIterator<Columbus.Csharp.Asg.Nodes.Structure.TypeParameterConstraintSyntax> ConstraintsListIteratorBegin {
            get {
                return new ListIterator<Columbus.Csharp.Asg.Nodes.Structure.TypeParameterConstraintSyntax>(ConstraintsContainer, fact, true);
            }
        }

        /// <summary>
        /// Gives back iterator for the Constraints edges.
        /// </summary>
        /// <returns>Returns an iterator for the Constraints edges.</returns>
        public ListIterator<Columbus.Csharp.Asg.Nodes.Structure.TypeParameterConstraintSyntax> ConstraintsListIteratorEnd {
            get {
                return new ListIterator<Columbus.Csharp.Asg.Nodes.Structure.TypeParameterConstraintSyntax>(ConstraintsContainer, fact, false);
            }
        }

        /// <summary>
        /// Tells whether the node has Constraints edges or not.
        /// </summary>
        /// <returns>Returns true if the node has at least one Constraints edge.</returns>
        public bool ConstraintsIsEmpty {
            get { return ConstraintsContainer.Count == 0; }
        }

        /// <summary>
        /// Gives back how many Constraints edges the node has.
        /// </summary>
        /// <returns>Returns with the number of Constraints edges.</returns>
        public uint ConstraintsSize {
            get { return (uint)(ConstraintsContainer.Count); }
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


        // ---------- Edge setter function(s) ----------

        /// <summary>
        /// Adds a new Constraints edge to the node and inserts it after the other ones.
        /// </summary>
        /// <param name="node">[in] The end point of the new Constraints edge.</param>
        /// <exception cref="Columbus.Csharp.Asg.CsharpException">Throws CsharpException if there is something wrong with the given node.</exception>
        public void addConstraints(Columbus.Csharp.Asg.Nodes.Structure.TypeParameterConstraintSyntax node) {
            addConstraints(node.Id);
        }

        /// <summary>
        /// Adds a new Constraints edge to the node and inserts it after the other ones.
        /// </summary>
        /// <param name="nodeId">[in] The end point of the new Constraints edge.</param>
        /// <exception cref="Columbus.Csharp.Asg.CsharpException">Throws CsharpException if the given nodeId is invalid.</exception>
        public void addConstraints(uint nodeId) {
            if (!fact.getExist(nodeId))
                throw new CsharpException("Columbus.Csharp.Asg.Nodes.Structure.TypeParameterConstraintClauseSyntax.addConstraints(NodeId)", "The end point of the edge does not exist.");
            Columbus.Csharp.Asg.Nodes.Base.Base node = fact.getRef(nodeId);
            if (Common.getIsBaseClassKind(node.NodeKind, Types.NodeKind.ndkTypeParameterConstraintSyntax)) {
                ConstraintsContainer.AddLast(nodeId);
            } else {
                throw new CsharpException("Columbus.Csharp.Asg.Nodes.Structure.TypeParameterConstraintClauseSyntax.setConstraints(NodeId)", "Invalid NodeKind (" + node.NodeKind.ToString() + ").");
            }
           setParentEdge(nodeId, (uint)Types.EdgeKind.edkTypeParameterConstraintClauseSyntax_Constraints);
            if (fact.ReverseEdges != null)
              fact.ReverseEdges.insertEdge(nodeId, this.Id, Types.EdgeKind.edkTypeParameterConstraintClauseSyntax_Constraints);
        }

        /// <summary>
        /// Sets the Name edge.
        /// </summary>
        /// <param name="nodeId">[in] The new end point of the Name edge or 0. With 0 the edge can be deleted.</param>
        /// <exception cref="Columbus.Csharp.Asg.CsharpException">Throws CsharpException if the nodeId is invalid.</exception>
        public void setName(uint nodeId) {
            if (nodeId != 0) {
                if (!fact.getExist(nodeId))
                    throw new CsharpException("Columbus.Csharp.Asg.Nodes.Structure.TypeParameterConstraintClauseSyntax.setName(NodeId)", "The end point of the edge does not exist.");

                Columbus.Csharp.Asg.Nodes.Base.Base node = fact.getRef(nodeId);
                if (Common.getIsBaseClassKind(node.NodeKind, Types.NodeKind.ndkIdentifierNameSyntax)) {
                    if (m_Name != 0) {
                        removeParentEdge(m_Name);
                    }
                    m_Name = nodeId;
                    setParentEdge(m_Name, (uint)Types.EdgeKind.edkTypeParameterConstraintClauseSyntax_Name);
                } else {
                    throw new CsharpException("Columbus.Csharp.Asg.Nodes.Structure.TypeParameterConstraintClauseSyntax.setName(NodeId)", "Invalid NodeKind (" + node.NodeKind.ToString() + ").");
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
        public void setName(Columbus.Csharp.Asg.Nodes.Expression.IdentifierNameSyntax node) {
            if (m_Name != 0) {
                removeParentEdge(m_Name);
            }
            m_Name = node.Id;
            setParentEdge(m_Name, (uint)Types.EdgeKind.edkTypeParameterConstraintClauseSyntax_Name);
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


            foreach (var Constraints in ConstraintsContainer) {
              io.writeUInt4(Constraints);
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
              setParentEdge(m_Name,(uint)Types.EdgeKind.edkTypeParameterConstraintClauseSyntax_Name);

            uint _id;

            _id = binIo.readUInt4();
            while (_id != 0) {
              ConstraintsContainer.AddLast(_id);
              setParentEdge(_id, (uint)Types.EdgeKind.edkTypeParameterConstraintClauseSyntax_Constraints);
              _id = binIo.readUInt4();
            }
        }

    }

}
