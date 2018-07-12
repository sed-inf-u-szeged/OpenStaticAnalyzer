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

namespace Columbus.Lim.Asg.Nodes.Logical {

    /// <summary>
    /// Scope class, which represents the logical::Scope node.
    /// </summary>
    [DebuggerDisplay("{DemangledName}")]
#if (LIM_INTERNAL)
    internal
#else
    public
#endif
    class Scope : Member {

        /// <summary>The value of the `LLOC`.</summary>
        protected uint m_LLOC;

        /// <summary>The value of the `LOC`.</summary>
        protected uint m_LOC;

        /// <summary>The value of the `TLLOC`.</summary>
        protected uint m_TLLOC;

        /// <summary>The value of the `TLOC`.</summary>
        protected uint m_TLOC;

        /// <summary>Stores whether the node is `Anonymous` or not.</summary>
        protected bool m_isAnonymous;


        // ---------- Edges ----------

        /// <summary>Container stores the id of the nodes the hasMember edge points to.</summary>
        protected LinkedList<uint> hasMemberContainer;

        /// <summary>
        /// Constructor, only factory can instantiates nodes.
        /// </summary>
        /// <param name="nodeId">[in] The id of the node.</param>
        /// <param name="factory">[in] Poiter to the Factory the node belongs to.</param>
        public Scope(uint nodeId, Factory factory) : base(nodeId, factory) {
            m_LLOC = 0;
            m_LOC = 0;
            m_TLLOC = 0;
            m_TLOC = 0;
            m_isAnonymous = false;
            hasMemberContainer = new LinkedList<uint>();
        }

        /// <summary>
        /// Gives back the NodeKind of the node.
        /// </summary>
        /// <returns>Returns with the NodeKind.</returns>
        public override Types.NodeKind NodeKind {
            get { return Types.NodeKind.ndkScope; }
        }


        // ---------- Attribute propert(y)(ies) ----------

        /// <summary>
        /// Gives back the LLOC of the node.
        /// </summary>
        /// <returns>Returns with the LLOC.</returns>
        public uint LLOC
        {
            get
            {
                return m_LLOC;
            }
            set
            {
                m_LLOC = value;
            }
        }

        /// <summary>
        /// Gives back the LOC of the node.
        /// </summary>
        /// <returns>Returns with the LOC.</returns>
        public uint LOC
        {
            get
            {
                return m_LOC;
            }
            set
            {
                m_LOC = value;
            }
        }

        /// <summary>
        /// Gives back the TLLOC of the node.
        /// </summary>
        /// <returns>Returns with the TLLOC.</returns>
        public uint TLLOC
        {
            get
            {
                return m_TLLOC;
            }
            set
            {
                m_TLLOC = value;
            }
        }

        /// <summary>
        /// Gives back the TLOC of the node.
        /// </summary>
        /// <returns>Returns with the TLOC.</returns>
        public uint TLOC
        {
            get
            {
                return m_TLOC;
            }
            set
            {
                m_TLOC = value;
            }
        }

        /// <summary>
        /// Gives back the isAnonymous of the node.
        /// </summary>
        /// <returns>Returns with the isAnonymous.</returns>
        public bool IsAnonymous
        {
            get
            {
                return m_isAnonymous;
            }
            set
            {
                m_isAnonymous = value;
            }
        }


        // ---------- Reflection getter function ----------

        /// <summary>
        /// Gives back the begin iterator for the edge specified
        /// </summary>
        /// <param name="edge">[in] The multiple edge for which the iterator is requested</param>
        public override ListIterator<Columbus.Lim.Asg.Nodes.Base.Base> GetListIteratorBegin(string edge) {
            switch(edge) {
                case "HasMember":
                    return HasMemberListIteratorBegin.Convert<Columbus.Lim.Asg.Nodes.Base.Base>();
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
                case "HasMember":
                    addHasMember(nodeId);
                    return;
                default:
                    base.add(edge, nodeId);
                    return;
            }
        }


        // ---------- Edge getter function(s) ----------

        /// <summary>
        /// Gives back iterator for the hasMember edges.
        /// </summary>
        /// <returns>Returns an iterator for the hasMember edges.</returns>
        public ListIterator<Columbus.Lim.Asg.Nodes.Logical.Member> HasMemberListIteratorBegin {
            get {
                return new ListIterator<Columbus.Lim.Asg.Nodes.Logical.Member>(hasMemberContainer, fact, true);
            }
        }

        /// <summary>
        /// Gives back iterator for the hasMember edges.
        /// </summary>
        /// <returns>Returns an iterator for the hasMember edges.</returns>
        public ListIterator<Columbus.Lim.Asg.Nodes.Logical.Member> HasMemberListIteratorEnd {
            get {
                return new ListIterator<Columbus.Lim.Asg.Nodes.Logical.Member>(hasMemberContainer, fact, false);
            }
        }

        /// <summary>
        /// Tells whether the node has hasMember edges or not.
        /// </summary>
        /// <returns>Returns true if the node has at least one hasMember edge.</returns>
        public bool HasMemberIsEmpty {
            get { return hasMemberContainer.Count == 0; }
        }

        /// <summary>
        /// Gives back how many hasMember edges the node has.
        /// </summary>
        /// <returns>Returns with the number of hasMember edges.</returns>
        public uint HasMemberSize {
            get { return (uint)(hasMemberContainer.Count); }
        }


        // ---------- Edge setter function(s) ----------

        /// <summary>
        /// Adds a new hasMember edge to the node and inserts it after the other ones.
        /// </summary>
        /// <param name="node">[in] The end point of the new hasMember edge.</param>
        /// <exception cref="Columbus.Lim.Asg.LimException">Throws LimException if there is something wrong with the given node.</exception>
        public void addHasMember(Columbus.Lim.Asg.Nodes.Logical.Member node) {
            addHasMember(node.Id);
        }

        /// <summary>
        /// Adds a new hasMember edge to the node and inserts it after the other ones.
        /// </summary>
        /// <param name="nodeId">[in] The end point of the new hasMember edge.</param>
        /// <exception cref="Columbus.Lim.Asg.LimException">Throws LimException if the given nodeId is invalid.</exception>
        public void addHasMember(uint nodeId) {
            if (!fact.getExist(nodeId))
                throw new LimException("Columbus.Lim.Asg.Nodes.Logical.Scope.addHasMember(NodeId)", "The end point of the edge does not exist.");
            Columbus.Lim.Asg.Nodes.Base.Base node = fact.getRef(nodeId);
            if (Common.getIsBaseClassKind(node.NodeKind, Types.NodeKind.ndkMember)) {
                hasMemberContainer.AddLast(nodeId);
            } else {
                throw new LimException("Columbus.Lim.Asg.Nodes.Logical.Scope.setHasMember(NodeId)", "Invalid NodeKind (" + node.NodeKind.ToString() + ").");
            }
            if (fact.ReverseEdges != null)
              fact.ReverseEdges.insertEdge(nodeId, this.Id, Types.EdgeKind.edkScope_HasMember);
        }

        /// <summary>
        /// Saves the node.
        /// </summary>
        /// <param name="io">[in] The node is written into io.</param>
        /// <exception cref="Columbus.ColumbusIOException">Throws ColumbusIOException if there is something wrong with the file.</exception>
        public override void save(IO io) {
            base.save(io);

            byte boolValues = 0;
            boolValues <<= 1;
            if (m_isAnonymous)
              boolValues |= 1;
            io.writeUByte1(boolValues);
            io.writeUInt4(m_LLOC);
            io.writeUInt4(m_LOC);
            io.writeUInt4(m_TLLOC);
            io.writeUInt4(m_TLOC);


            foreach (var hasMember in hasMemberContainer) {
              io.writeUInt4(hasMember);
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

            byte boolValues = binIo.readUByte1();
            m_isAnonymous = Convert.ToBoolean(boolValues & 1);
            boolValues >>= 1;
            m_LLOC = binIo.readUInt4();
            m_LOC = binIo.readUInt4();
            m_TLLOC = binIo.readUInt4();
            m_TLOC = binIo.readUInt4();

            uint _id;

            _id = binIo.readUInt4();
            while (_id != 0) {
              hasMemberContainer.AddLast(_id);
              _id = binIo.readUInt4();
            }
        }

    }

}
