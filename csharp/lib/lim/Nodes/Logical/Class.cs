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
    /// Class class, which represents the logical::Class node.
    /// </summary>
    [DebuggerDisplay("{DemangledName}")]
#if (LIM_INTERNAL)
    internal
#else
    public
#endif
    class Class : Scope {

        /// <summary>The ClassKind of the node.</summary>
        protected Types.ClassKind m_classKind;

        /// <summary>Stores whether the node is `Abstract` or not.</summary>
        protected bool m_isAbstract;

        /// <summary>The value of the `objectSize`.</summary>
        protected uint m_objectSize;


        // ---------- Edges ----------

        /// <summary>Container stores the id of the nodes the grantsFriendship edge points to.</summary>
        protected LinkedList<uint> grantsFriendshipContainer;

        /// <summary>Container stores the id of the nodes the isSubclass edge points to.</summary>
        protected LinkedList<uint> isSubclassContainer;

        /// <summary>
        /// Constructor, only factory can instantiates nodes.
        /// </summary>
        /// <param name="nodeId">[in] The id of the node.</param>
        /// <param name="factory">[in] Poiter to the Factory the node belongs to.</param>
        public Class(uint nodeId, Factory factory) : base(nodeId, factory) {
            m_classKind = Types.ClassKind.clkAnnotation;
            m_isAbstract = false;
            m_objectSize = 0;
            grantsFriendshipContainer = new LinkedList<uint>();
            isSubclassContainer = new LinkedList<uint>();
        }

        /// <summary>
        /// Gives back the NodeKind of the node.
        /// </summary>
        /// <returns>Returns with the NodeKind.</returns>
        public override Types.NodeKind NodeKind {
            get { return Types.NodeKind.ndkClass; }
        }


        // ---------- Attribute propert(y)(ies) ----------

        /// <summary>
        /// Gives back the classKind of the node.
        /// </summary>
        /// <returns>Returns with the classKind.</returns>
        public Types.ClassKind ClassKind
        {
            get
            {
                return m_classKind;
            }
            set
            {
                m_classKind = value;
            }
        }

        /// <summary>
        /// Gives back the isAbstract of the node.
        /// </summary>
        /// <returns>Returns with the isAbstract.</returns>
        public bool IsAbstract
        {
            get
            {
                return m_isAbstract;
            }
            set
            {
                m_isAbstract = value;
            }
        }

        /// <summary>
        /// Gives back the objectSize of the node.
        /// </summary>
        /// <returns>Returns with the objectSize.</returns>
        public uint ObjectSize
        {
            get
            {
                return m_objectSize;
            }
            set
            {
                m_objectSize = value;
            }
        }


        // ---------- Reflection getter function ----------

        /// <summary>
        /// Gives back the begin iterator for the edge specified
        /// </summary>
        /// <param name="edge">[in] The multiple edge for which the iterator is requested</param>
        public override ListIterator<Columbus.Lim.Asg.Nodes.Base.Base> GetListIteratorBegin(string edge) {
            switch(edge) {
                case "GrantsFriendship":
                    return GrantsFriendshipListIteratorBegin.Convert<Columbus.Lim.Asg.Nodes.Base.Base>();
                case "IsSubclass":
                    return IsSubclassListIteratorBegin.Convert<Columbus.Lim.Asg.Nodes.Base.Base>();
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
                case "GrantsFriendship":
                    addGrantsFriendship(nodeId);
                    return;
                case "IsSubclass":
                    addIsSubclass(nodeId);
                    return;
                default:
                    base.add(edge, nodeId);
                    return;
            }
        }


        // ---------- Edge getter function(s) ----------

        /// <summary>
        /// Gives back iterator for the grantsFriendship edges.
        /// </summary>
        /// <returns>Returns an iterator for the grantsFriendship edges.</returns>
        public ListIterator<Columbus.Lim.Asg.Nodes.Logical.Friendship> GrantsFriendshipListIteratorBegin {
            get {
                return new ListIterator<Columbus.Lim.Asg.Nodes.Logical.Friendship>(grantsFriendshipContainer, fact, true);
            }
        }

        /// <summary>
        /// Gives back iterator for the grantsFriendship edges.
        /// </summary>
        /// <returns>Returns an iterator for the grantsFriendship edges.</returns>
        public ListIterator<Columbus.Lim.Asg.Nodes.Logical.Friendship> GrantsFriendshipListIteratorEnd {
            get {
                return new ListIterator<Columbus.Lim.Asg.Nodes.Logical.Friendship>(grantsFriendshipContainer, fact, false);
            }
        }

        /// <summary>
        /// Tells whether the node has grantsFriendship edges or not.
        /// </summary>
        /// <returns>Returns true if the node has at least one grantsFriendship edge.</returns>
        public bool GrantsFriendshipIsEmpty {
            get { return grantsFriendshipContainer.Count == 0; }
        }

        /// <summary>
        /// Gives back how many grantsFriendship edges the node has.
        /// </summary>
        /// <returns>Returns with the number of grantsFriendship edges.</returns>
        public uint GrantsFriendshipSize {
            get { return (uint)(grantsFriendshipContainer.Count); }
        }

        /// <summary>
        /// Gives back iterator for the isSubclass edges.
        /// </summary>
        /// <returns>Returns an iterator for the isSubclass edges.</returns>
        public ListIterator<Columbus.Lim.Asg.Nodes.Type.Type> IsSubclassListIteratorBegin {
            get {
                return new ListIterator<Columbus.Lim.Asg.Nodes.Type.Type>(isSubclassContainer, fact, true);
            }
        }

        /// <summary>
        /// Gives back iterator for the isSubclass edges.
        /// </summary>
        /// <returns>Returns an iterator for the isSubclass edges.</returns>
        public ListIterator<Columbus.Lim.Asg.Nodes.Type.Type> IsSubclassListIteratorEnd {
            get {
                return new ListIterator<Columbus.Lim.Asg.Nodes.Type.Type>(isSubclassContainer, fact, false);
            }
        }

        /// <summary>
        /// Tells whether the node has isSubclass edges or not.
        /// </summary>
        /// <returns>Returns true if the node has at least one isSubclass edge.</returns>
        public bool IsSubclassIsEmpty {
            get { return isSubclassContainer.Count == 0; }
        }

        /// <summary>
        /// Gives back how many isSubclass edges the node has.
        /// </summary>
        /// <returns>Returns with the number of isSubclass edges.</returns>
        public uint IsSubclassSize {
            get { return (uint)(isSubclassContainer.Count); }
        }


        // ---------- Edge setter function(s) ----------

        /// <summary>
        /// Adds a new grantsFriendship edge to the node and inserts it after the other ones.
        /// </summary>
        /// <param name="node">[in] The end point of the new grantsFriendship edge.</param>
        /// <exception cref="Columbus.Lim.Asg.LimException">Throws LimException if there is something wrong with the given node.</exception>
        public void addGrantsFriendship(Columbus.Lim.Asg.Nodes.Logical.Friendship node) {
            addGrantsFriendship(node.Id);
        }

        /// <summary>
        /// Adds a new grantsFriendship edge to the node and inserts it after the other ones.
        /// </summary>
        /// <param name="nodeId">[in] The end point of the new grantsFriendship edge.</param>
        /// <exception cref="Columbus.Lim.Asg.LimException">Throws LimException if the given nodeId is invalid.</exception>
        public void addGrantsFriendship(uint nodeId) {
            if (!fact.getExist(nodeId))
                throw new LimException("Columbus.Lim.Asg.Nodes.Logical.Class.addGrantsFriendship(NodeId)", "The end point of the edge does not exist.");
            Columbus.Lim.Asg.Nodes.Base.Base node = fact.getRef(nodeId);
            if (Common.getIsBaseClassKind(node.NodeKind, Types.NodeKind.ndkFriendship)) {
                grantsFriendshipContainer.AddLast(nodeId);
            } else {
                throw new LimException("Columbus.Lim.Asg.Nodes.Logical.Class.setGrantsFriendship(NodeId)", "Invalid NodeKind (" + node.NodeKind.ToString() + ").");
            }
            if (fact.ReverseEdges != null)
              fact.ReverseEdges.insertEdge(nodeId, this.Id, Types.EdgeKind.edkClass_GrantsFriendship);
        }

        /// <summary>
        /// Adds a new isSubclass edge to the node and inserts it after the other ones.
        /// </summary>
        /// <param name="node">[in] The end point of the new isSubclass edge.</param>
        /// <exception cref="Columbus.Lim.Asg.LimException">Throws LimException if there is something wrong with the given node.</exception>
        public void addIsSubclass(Columbus.Lim.Asg.Nodes.Type.Type node) {
            addIsSubclass(node.Id);
        }

        /// <summary>
        /// Adds a new isSubclass edge to the node and inserts it after the other ones.
        /// </summary>
        /// <param name="nodeId">[in] The end point of the new isSubclass edge.</param>
        /// <exception cref="Columbus.Lim.Asg.LimException">Throws LimException if the given nodeId is invalid.</exception>
        public void addIsSubclass(uint nodeId) {
            if (!fact.getExist(nodeId))
                throw new LimException("Columbus.Lim.Asg.Nodes.Logical.Class.addIsSubclass(NodeId)", "The end point of the edge does not exist.");
            Columbus.Lim.Asg.Nodes.Base.Base node = fact.getRef(nodeId);
            if (Common.getIsBaseClassKind(node.NodeKind, Types.NodeKind.ndkType)) {
                isSubclassContainer.AddLast(nodeId);
            } else {
                throw new LimException("Columbus.Lim.Asg.Nodes.Logical.Class.setIsSubclass(NodeId)", "Invalid NodeKind (" + node.NodeKind.ToString() + ").");
            }
            if (fact.ReverseEdges != null)
              fact.ReverseEdges.insertEdge(nodeId, this.Id, Types.EdgeKind.edkClass_IsSubclass);
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

            byte boolValues = 0;
            boolValues <<= 1;
            if (m_isAbstract)
              boolValues |= 1;
            io.writeUByte1(boolValues);
            io.writeUByte1((byte)m_classKind);
            io.writeUInt4(m_objectSize);


            foreach (var grantsFriendship in grantsFriendshipContainer) {
              io.writeUInt4(grantsFriendship);
            }
            io.writeUInt4(0); // This is the end sign

            foreach (var isSubclass in isSubclassContainer) {
              io.writeUInt4(isSubclass);
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
            m_isAbstract = Convert.ToBoolean(boolValues & 1);
            boolValues >>= 1;
            m_classKind = (Types.ClassKind)binIo.readUByte1();
            m_objectSize = binIo.readUInt4();

            uint _id;

            _id = binIo.readUInt4();
            while (_id != 0) {
              grantsFriendshipContainer.AddLast(_id);
              _id = binIo.readUInt4();
            }

            _id = binIo.readUInt4();
            while (_id != 0) {
              isSubclassContainer.AddLast(_id);
              _id = binIo.readUInt4();
            }
        }

    }

}
