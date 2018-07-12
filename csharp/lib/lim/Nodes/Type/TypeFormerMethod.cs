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

namespace Columbus.Lim.Asg.Nodes.Type {

    /// <summary>
    /// TypeFormerMethod class, which represents the type::TypeFormerMethod node.
    /// </summary>
    [DebuggerDisplay("{DemangledName}")]
#if (LIM_INTERNAL)
    internal
#else
    public
#endif
    class TypeFormerMethod : TypeFormer {


        // ---------- Edges ----------

        /// <summary>Container stores the id of the nodes the hasParameterType edge points to and the association classes.</summary>
        protected LinkedList<ListIteratorAssoc<Columbus.Lim.Asg.Nodes.Type.Type>.AssocEdge> hasParameterTypeAssocContainer;

        /// <summary>The id of the node the hasReturnType edge points to.</summary>
        protected uint m_hasReturnType;

        /// <summary>
        /// Constructor, only factory can instantiates nodes.
        /// </summary>
        /// <param name="nodeId">[in] The id of the node.</param>
        /// <param name="factory">[in] Poiter to the Factory the node belongs to.</param>
        public TypeFormerMethod(uint nodeId, Factory factory) : base(nodeId, factory) {
            hasParameterTypeAssocContainer = new LinkedList<ListIteratorAssoc<Columbus.Lim.Asg.Nodes.Type.Type>.AssocEdge>();
            m_hasReturnType = 0;
        }

        /// <summary>
        /// Gives back the NodeKind of the node.
        /// </summary>
        /// <returns>Returns with the NodeKind.</returns>
        public override Types.NodeKind NodeKind {
            get { return Types.NodeKind.ndkTypeFormerMethod; }
        }


        // ---------- Reflection getter function ----------

        /// <summary>
        /// Gives back the begin iterator for the edge specified
        /// </summary>
        /// <param name="edge">[in] The multiple edge for which the iterator is requested</param>
        public override ListIterator<Columbus.Lim.Asg.Nodes.Base.Base> GetListIteratorBegin(string edge) {
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
        /// Gives back iterator for the hasParameterType edges.
        /// </summary>
        /// <returns>Returns an iterator for the hasParameterType edges.</returns>
        public ListIteratorAssocParameterKind<Columbus.Lim.Asg.Nodes.Type.Type> HasParameterTypeListIteratorAssocBegin {
            get {
                return new ListIteratorAssocParameterKind<Columbus.Lim.Asg.Nodes.Type.Type>(hasParameterTypeAssocContainer, fact, true);
            }
        }

        /// <summary>
        /// Gives back iterator for the hasParameterType edges.
        /// </summary>
        /// <returns>Returns an iterator for the hasParameterType edges.</returns>
        public ListIteratorAssocParameterKind<Columbus.Lim.Asg.Nodes.Type.Type> HasParameterTypeListIteratorAssocEnd {
            get {
                return new ListIteratorAssocParameterKind<Columbus.Lim.Asg.Nodes.Type.Type>(hasParameterTypeAssocContainer, fact, false);
            }
        }

        /// <summary>
        /// Tells whether the node has hasParameterType edges or not.
        /// </summary>
        /// <returns>Returns true if the node has at least one hasParameterType edge.</returns>
        public bool HasParameterTypeIsEmpty {
            get { return hasParameterTypeAssocContainer.Count == 0; }
        }

        /// <summary>
        /// Gives back how many hasParameterType edges the node has.
        /// </summary>
        /// <returns>Returns with the number of hasParameterType edges.</returns>
        public uint HasParameterTypeSize {
            get { return (uint)(hasParameterTypeAssocContainer.Count); }
        }

        /// <summary>
        /// Gives back the id of the node the hasReturnType edge points to.
        /// </summary>
        /// <returns>Returns the end point of the m_hasReturnType edge.</returns>
        /// <exception cref="Columbus.Lim.Asg.LimException">Throws LimException if the edge id is invalid.</exception>
        public uint getHasReturnType() {
            if (fact.getIsFiltered(m_hasReturnType))
                return 1;
            else
                return m_hasReturnType;
        }


        // ---------- Edge setter function(s) ----------

        /// <summary>
        /// Adds a new hasParameterType edge to the node.
        /// </summary>
        /// <param name="node">[in] The end point of the new hasParameterType edge.</param>
        /// <param name="acValue">[in] The value of the association class.</param>
        /// <exception cref="Columbus.Lim.Asg.LimException">Throws LimException if there is something wrong with the given node.</exception>
        public void addHasParameterType(Columbus.Lim.Asg.Nodes.Type.Type node, Types.ParameterKind acValue) {
            addHasParameterType(node.Id, acValue);
        }

        /// <summary>
        /// Adds a new hasParameterType edge to the node.
        /// </summary>
        /// <param name="nodeId">[in] The end point of the new hasParameterType edge.</param>
        /// <param name="acValue">[in] The value of the association class.</param>
        /// <exception cref="Columbus.Lim.Asg.LimException">Throws LimException if the given nodeId is invalid.</exception>
        public void addHasParameterType(uint nodeId, Types.ParameterKind acValue) {
            if (!fact.getExist(nodeId))
                throw new LimException("Columbus.Lim.Asg.Nodes.Type.TypeFormerMethod.addHasParameterType(NodeId)", "The end point of the edge does not exist.");
            Columbus.Lim.Asg.Nodes.Base.Base node = fact.getRef(nodeId);
            if (Common.getIsBaseClassKind(node.NodeKind, Types.NodeKind.ndkType)) {
                ListIteratorAssoc<Columbus.Lim.Asg.Nodes.Type.Type>.AssocEdge ac = new ListIteratorAssoc<Columbus.Lim.Asg.Nodes.Type.Type>.AssocEdge();
                ac.assocClass = new ListIteratorAssoc<Columbus.Lim.Asg.Nodes.Type.Type>.AssocClass();

                ac.id = nodeId;
                ac.assocClass.acParameterKind = acValue;

                hasParameterTypeAssocContainer.AddLast(ac);
            } else {
                throw new LimException("Columbus.Lim.Asg.Nodes.Type.TypeFormerMethod.setHasParameterType(NodeId)", "Invalid NodeKind (" + node.NodeKind.ToString() + ").");
            }
            if (fact.ReverseEdges != null)
              fact.ReverseEdges.insertEdge(nodeId, this.Id, Types.EdgeKind.edkTypeFormerMethod_HasParameterType);
        }

        /// <summary>
        /// Sets the hasReturnType edge.
        /// </summary>
        /// <param name="nodeId">[in] The new end point of the hasReturnType edge or 0. With 0 the edge can be deleted.</param>
        /// <exception cref="Columbus.Lim.Asg.LimException">Throws LimException if the nodeId is invalid.</exception>
        public void setHasReturnType(uint nodeId) {
            if (nodeId != 0) {
                if (!fact.getExist(nodeId))
                    throw new LimException("Columbus.Lim.Asg.Nodes.Type.TypeFormerMethod.setHasReturnType(NodeId)", "The end point of the edge does not exist.");

                Columbus.Lim.Asg.Nodes.Base.Base node = fact.getRef(nodeId);
                if (Common.getIsBaseClassKind(node.NodeKind, Types.NodeKind.ndkType)) {
                    if (m_hasReturnType != 0) {
                    }
                    m_hasReturnType = nodeId;
                } else {
                    throw new LimException("Columbus.Lim.Asg.Nodes.Type.TypeFormerMethod.setHasReturnType(NodeId)", "Invalid NodeKind (" + node.NodeKind.ToString() + ").");
                }
            } else {
                if (m_hasReturnType != 0) {
                }
                m_hasReturnType = 0;
            }
        }

        /// <summary>
        /// Sets the hasReturnType edge.
        /// </summary>
        /// <param name="node">[in] The new end point of the hasReturnType edge.</param>
        /// <exception cref="Columbus.Lim.Asg.LimException">Throws LimException if there's something wrong with the given node.</exception>
        public void setHasReturnType(Columbus.Lim.Asg.Nodes.Type.Type node) {
            if (m_hasReturnType != 0) {
            }
            m_hasReturnType = node.Id;
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

            io.writeUInt4(m_hasReturnType);


            foreach (var hasParameterTypeAssoc in hasParameterTypeAssocContainer) {
                io.writeUInt4(hasParameterTypeAssoc.id);
              io.writeUByte1((byte)hasParameterTypeAssoc.assocClass.acParameterKind);
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

            m_hasReturnType =  binIo.readUInt4();

            uint _id;

            _id = binIo.readUInt4();
            while (_id != 0) {
              Types.ParameterKind _ac = (Types.ParameterKind)(binIo.readUByte1());
                ListIteratorAssoc<Columbus.Lim.Asg.Nodes.Type.Type>.AssocEdge hasParameterTypeAc = new ListIteratorAssoc<Columbus.Lim.Asg.Nodes.Type.Type>.AssocEdge();
                hasParameterTypeAc.assocClass.acParameterKind = _ac;
                hasParameterTypeAc.id = _id;
                hasParameterTypeAssocContainer.AddLast(hasParameterTypeAc);
              _id = binIo.readUInt4();
            }
        }

    }

}
