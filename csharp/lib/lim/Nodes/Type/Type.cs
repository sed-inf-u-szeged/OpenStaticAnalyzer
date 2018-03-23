/*
 *  This file is part of OpenStaticAnalyzer.
 *
 *  Copyright (c) 2004-2017 Department of Software Engineering - University of Szeged
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
    /// Type class, which represents the type::Type node.
    /// </summary>
    [DebuggerDisplay("{DemangledName}")]
#if (LIM_INTERNAL)
    internal
#else
    public
#endif
    class Type : Columbus.Lim.Asg.Nodes.Base.Base {

        /// <summary>The Key of the `refers`.</summary>
        protected uint m_refers;


        // ---------- Edges ----------

        /// <summary>Container stores the id of the nodes the hasTypeFormer edge points to.</summary>
        protected LinkedList<uint> hasTypeFormerContainer;

        /// <summary>
        /// Constructor, only factory can instantiates nodes.
        /// </summary>
        /// <param name="nodeId">[in] The id of the node.</param>
        /// <param name="factory">[in] Poiter to the Factory the node belongs to.</param>
        public Type(uint nodeId, Factory factory) : base(nodeId, factory) {
            m_refers = 0;
            hasTypeFormerContainer = new LinkedList<uint>();
        }

        /// <summary>
        /// Gives back the NodeKind of the node.
        /// </summary>
        /// <returns>Returns with the NodeKind.</returns>
        public override Types.NodeKind NodeKind {
            get { return Types.NodeKind.ndkType; }
        }


        // ---------- Attribute propert(y)(ies) ----------

        /// <summary>
        /// Gives back or sets the refers of the node.
        /// </summary>
        public string Refers
        {
            get
            {
                return fact.StringTable.get(m_refers);
            }
            set
            {
                m_refers = fact.StringTable.set( value );
            }
        }

        /// <summary>
        /// Gives back or sets the Key of refers of the node.
        /// </summary>
        public uint RefersKey
        {
            get
            {
                return m_refers;
            }
            set
            {
               m_refers = value;
            }
        }


        // ---------- Reflection getter function ----------

        /// <summary>
        /// Gives back the begin iterator for the edge specified
        /// </summary>
        /// <param name="edge">[in] The multiple edge for which the iterator is requested</param>
        public override ListIterator<Columbus.Lim.Asg.Nodes.Base.Base> GetListIteratorBegin(string edge) {
            switch(edge) {
                case "HasTypeFormer":
                    return HasTypeFormerListIteratorBegin.Convert<Columbus.Lim.Asg.Nodes.Base.Base>();
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
                case "HasTypeFormer":
                    addHasTypeFormer(nodeId);
                    return;
                default:
                    base.add(edge, nodeId);
                    return;
            }
        }


        // ---------- Edge getter function(s) ----------

        /// <summary>
        /// Gives back iterator for the hasTypeFormer edges.
        /// </summary>
        /// <returns>Returns an iterator for the hasTypeFormer edges.</returns>
        public ListIterator<Columbus.Lim.Asg.Nodes.Type.TypeFormer> HasTypeFormerListIteratorBegin {
            get {
                return new ListIterator<Columbus.Lim.Asg.Nodes.Type.TypeFormer>(hasTypeFormerContainer, fact, true);
            }
        }

        /// <summary>
        /// Gives back iterator for the hasTypeFormer edges.
        /// </summary>
        /// <returns>Returns an iterator for the hasTypeFormer edges.</returns>
        public ListIterator<Columbus.Lim.Asg.Nodes.Type.TypeFormer> HasTypeFormerListIteratorEnd {
            get {
                return new ListIterator<Columbus.Lim.Asg.Nodes.Type.TypeFormer>(hasTypeFormerContainer, fact, false);
            }
        }

        /// <summary>
        /// Tells whether the node has hasTypeFormer edges or not.
        /// </summary>
        /// <returns>Returns true if the node has at least one hasTypeFormer edge.</returns>
        public bool HasTypeFormerIsEmpty {
            get { return hasTypeFormerContainer.Count == 0; }
        }

        /// <summary>
        /// Gives back how many hasTypeFormer edges the node has.
        /// </summary>
        /// <returns>Returns with the number of hasTypeFormer edges.</returns>
        public uint HasTypeFormerSize {
            get { return (uint)(hasTypeFormerContainer.Count); }
        }


        // ---------- Edge setter function(s) ----------

        /// <summary>
        /// Adds a new hasTypeFormer edge to the node and inserts it after the other ones.
        /// </summary>
        /// <param name="node">[in] The end point of the new hasTypeFormer edge.</param>
        /// <exception cref="Columbus.Lim.Asg.LimException">Throws LimException if there is something wrong with the given node.</exception>
        public void addHasTypeFormer(Columbus.Lim.Asg.Nodes.Type.TypeFormer node) {
            addHasTypeFormer(node.Id);
        }

        /// <summary>
        /// Adds a new hasTypeFormer edge to the node and inserts it after the other ones.
        /// </summary>
        /// <param name="nodeId">[in] The end point of the new hasTypeFormer edge.</param>
        /// <exception cref="Columbus.Lim.Asg.LimException">Throws LimException if the given nodeId is invalid.</exception>
        public void addHasTypeFormer(uint nodeId) {
            if (!fact.getExist(nodeId))
                throw new LimException("Columbus.Lim.Asg.Nodes.Type.Type.addHasTypeFormer(NodeId)", "The end point of the edge does not exist.");
            Columbus.Lim.Asg.Nodes.Base.Base node = fact.getRef(nodeId);
            if (Common.getIsBaseClassKind(node.NodeKind, Types.NodeKind.ndkTypeFormer)) {
                hasTypeFormerContainer.AddLast(nodeId);
            } else {
                throw new LimException("Columbus.Lim.Asg.Nodes.Type.Type.setHasTypeFormer(NodeId)", "Invalid NodeKind (" + node.NodeKind.ToString() + ").");
            }
            if (fact.ReverseEdges != null)
              fact.ReverseEdges.insertEdge(nodeId, this.Id, Types.EdgeKind.edkType_HasTypeFormer);
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

            fact.StringTable.setType(m_refers, StrTable.StrType.strToSave);
            io.writeUInt4(m_refers);


            foreach (var hasTypeFormer in hasTypeFormerContainer) {
              io.writeUInt4(hasTypeFormer);
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

            m_refers = binIo.readUInt4();

            uint _id;

            _id = binIo.readUInt4();
            while (_id != 0) {
              hasTypeFormerContainer.AddLast(_id);
              _id = binIo.readUInt4();
            }
        }

    }

}
