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

namespace Columbus.Lim.Asg.Nodes.Base {

    /// <summary>
    /// Component class, which represents the base::Component node.
    /// </summary>
    [DebuggerDisplay("{DemangledName}")]
#if (LIM_INTERNAL)
    internal
#else
    public
#endif
    class Component : Named {

        /// <summary>The value of the `TLLOC`.</summary>
        protected uint m_TLLOC;

        /// <summary>The value of the `TLOC`.</summary>
        protected uint m_TLOC;

        /// <summary>The AnalysisTimeKind of the node.</summary>
        protected Types.AnalysisTimeKind m_analysisTime;

        /// <summary>The Key of the `changesetID`.</summary>
        protected uint m_changesetID;

        /// <summary>The Key of the `shortName`.</summary>
        protected uint m_shortName;


        // ---------- Edges ----------

        /// <summary>Container stores the id of the nodes the contains edge points to.</summary>
        protected LinkedList<uint> containsContainer;

        /// <summary>Container stores the id of the nodes the hasFiles edge points to.</summary>
        protected LinkedList<uint> hasFilesContainer;

        /// <summary>
        /// Constructor, only factory can instantiates nodes.
        /// </summary>
        /// <param name="nodeId">[in] The id of the node.</param>
        /// <param name="factory">[in] Poiter to the Factory the node belongs to.</param>
        public Component(uint nodeId, Factory factory) : base(nodeId, factory) {
            m_TLLOC = 0;
            m_TLOC = 0;
            m_analysisTime = Types.AnalysisTimeKind.atkNow;
            m_changesetID = 0;
            m_shortName = 0;
            containsContainer = new LinkedList<uint>();
            hasFilesContainer = new LinkedList<uint>();
        }

        /// <summary>
        /// Gives back the NodeKind of the node.
        /// </summary>
        /// <returns>Returns with the NodeKind.</returns>
        public override Types.NodeKind NodeKind {
            get { return Types.NodeKind.ndkComponent; }
        }


        // ---------- Attribute propert(y)(ies) ----------

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
        /// Gives back the analysisTime of the node.
        /// </summary>
        /// <returns>Returns with the analysisTime.</returns>
        public Types.AnalysisTimeKind AnalysisTime
        {
            get
            {
                return m_analysisTime;
            }
            set
            {
                m_analysisTime = value;
            }
        }

        /// <summary>
        /// Gives back or sets the changesetID of the node.
        /// </summary>
        public string ChangesetID
        {
            get
            {
                return fact.StringTable.get(m_changesetID);
            }
            set
            {
                m_changesetID = fact.StringTable.set( value );
            }
        }

        /// <summary>
        /// Gives back or sets the Key of changesetID of the node.
        /// </summary>
        public uint ChangesetIDKey
        {
            get
            {
                return m_changesetID;
            }
            set
            {
               m_changesetID = value;
            }
        }

        /// <summary>
        /// Gives back or sets the shortName of the node.
        /// </summary>
        public string ShortName
        {
            get
            {
                return fact.StringTable.get(m_shortName);
            }
            set
            {
                m_shortName = fact.StringTable.set( value );
            }
        }

        /// <summary>
        /// Gives back or sets the Key of shortName of the node.
        /// </summary>
        public uint ShortNameKey
        {
            get
            {
                return m_shortName;
            }
            set
            {
               m_shortName = value;
            }
        }


        // ---------- Reflection getter function ----------

        /// <summary>
        /// Gives back the begin iterator for the edge specified
        /// </summary>
        /// <param name="edge">[in] The multiple edge for which the iterator is requested</param>
        public override ListIterator<Columbus.Lim.Asg.Nodes.Base.Base> GetListIteratorBegin(string edge) {
            switch(edge) {
                case "Contains":
                    return ContainsListIteratorBegin.Convert<Columbus.Lim.Asg.Nodes.Base.Base>();
                case "HasFiles":
                    return HasFilesListIteratorBegin.Convert<Columbus.Lim.Asg.Nodes.Base.Base>();
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
                case "Contains":
                    addContains(nodeId);
                    return;
                case "HasFiles":
                    addHasFiles(nodeId);
                    return;
                default:
                    base.add(edge, nodeId);
                    return;
            }
        }


        // ---------- Edge getter function(s) ----------

        /// <summary>
        /// Gives back iterator for the contains edges.
        /// </summary>
        /// <returns>Returns an iterator for the contains edges.</returns>
        public ListIterator<Columbus.Lim.Asg.Nodes.Base.Component> ContainsListIteratorBegin {
            get {
                return new ListIterator<Columbus.Lim.Asg.Nodes.Base.Component>(containsContainer, fact, true);
            }
        }

        /// <summary>
        /// Gives back iterator for the contains edges.
        /// </summary>
        /// <returns>Returns an iterator for the contains edges.</returns>
        public ListIterator<Columbus.Lim.Asg.Nodes.Base.Component> ContainsListIteratorEnd {
            get {
                return new ListIterator<Columbus.Lim.Asg.Nodes.Base.Component>(containsContainer, fact, false);
            }
        }

        /// <summary>
        /// Tells whether the node has contains edges or not.
        /// </summary>
        /// <returns>Returns true if the node has at least one contains edge.</returns>
        public bool ContainsIsEmpty {
            get { return containsContainer.Count == 0; }
        }

        /// <summary>
        /// Gives back how many contains edges the node has.
        /// </summary>
        /// <returns>Returns with the number of contains edges.</returns>
        public uint ContainsSize {
            get { return (uint)(containsContainer.Count); }
        }

        /// <summary>
        /// Gives back iterator for the hasFiles edges.
        /// </summary>
        /// <returns>Returns an iterator for the hasFiles edges.</returns>
        public ListIterator<Columbus.Lim.Asg.Nodes.Physical.File> HasFilesListIteratorBegin {
            get {
                return new ListIterator<Columbus.Lim.Asg.Nodes.Physical.File>(hasFilesContainer, fact, true);
            }
        }

        /// <summary>
        /// Gives back iterator for the hasFiles edges.
        /// </summary>
        /// <returns>Returns an iterator for the hasFiles edges.</returns>
        public ListIterator<Columbus.Lim.Asg.Nodes.Physical.File> HasFilesListIteratorEnd {
            get {
                return new ListIterator<Columbus.Lim.Asg.Nodes.Physical.File>(hasFilesContainer, fact, false);
            }
        }

        /// <summary>
        /// Tells whether the node has hasFiles edges or not.
        /// </summary>
        /// <returns>Returns true if the node has at least one hasFiles edge.</returns>
        public bool HasFilesIsEmpty {
            get { return hasFilesContainer.Count == 0; }
        }

        /// <summary>
        /// Gives back how many hasFiles edges the node has.
        /// </summary>
        /// <returns>Returns with the number of hasFiles edges.</returns>
        public uint HasFilesSize {
            get { return (uint)(hasFilesContainer.Count); }
        }


        // ---------- Edge setter function(s) ----------

        /// <summary>
        /// Adds a new contains edge to the node and inserts it after the other ones.
        /// </summary>
        /// <param name="node">[in] The end point of the new contains edge.</param>
        /// <exception cref="Columbus.Lim.Asg.LimException">Throws LimException if there is something wrong with the given node.</exception>
        public void addContains(Columbus.Lim.Asg.Nodes.Base.Component node) {
            addContains(node.Id);
        }

        /// <summary>
        /// Adds a new contains edge to the node and inserts it after the other ones.
        /// </summary>
        /// <param name="nodeId">[in] The end point of the new contains edge.</param>
        /// <exception cref="Columbus.Lim.Asg.LimException">Throws LimException if the given nodeId is invalid.</exception>
        public void addContains(uint nodeId) {
            if (!fact.getExist(nodeId))
                throw new LimException("Columbus.Lim.Asg.Nodes.Base.Component.addContains(NodeId)", "The end point of the edge does not exist.");
            Columbus.Lim.Asg.Nodes.Base.Base node = fact.getRef(nodeId);
            if (Common.getIsBaseClassKind(node.NodeKind, Types.NodeKind.ndkComponent)) {
                containsContainer.AddLast(nodeId);
            } else {
                throw new LimException("Columbus.Lim.Asg.Nodes.Base.Component.setContains(NodeId)", "Invalid NodeKind (" + node.NodeKind.ToString() + ").");
            }
            if (fact.ReverseEdges != null)
              fact.ReverseEdges.insertEdge(nodeId, this.Id, Types.EdgeKind.edkComponent_Contains);
        }

        /// <summary>
        /// Adds a new hasFiles edge to the node and inserts it after the other ones.
        /// </summary>
        /// <param name="node">[in] The end point of the new hasFiles edge.</param>
        /// <exception cref="Columbus.Lim.Asg.LimException">Throws LimException if there is something wrong with the given node.</exception>
        public void addHasFiles(Columbus.Lim.Asg.Nodes.Physical.File node) {
            addHasFiles(node.Id);
        }

        /// <summary>
        /// Adds a new hasFiles edge to the node and inserts it after the other ones.
        /// </summary>
        /// <param name="nodeId">[in] The end point of the new hasFiles edge.</param>
        /// <exception cref="Columbus.Lim.Asg.LimException">Throws LimException if the given nodeId is invalid.</exception>
        public void addHasFiles(uint nodeId) {
            if (!fact.getExist(nodeId))
                throw new LimException("Columbus.Lim.Asg.Nodes.Base.Component.addHasFiles(NodeId)", "The end point of the edge does not exist.");
            Columbus.Lim.Asg.Nodes.Base.Base node = fact.getRef(nodeId);
            if (Common.getIsBaseClassKind(node.NodeKind, Types.NodeKind.ndkFile)) {
                hasFilesContainer.AddLast(nodeId);
            } else {
                throw new LimException("Columbus.Lim.Asg.Nodes.Base.Component.setHasFiles(NodeId)", "Invalid NodeKind (" + node.NodeKind.ToString() + ").");
            }
            if (fact.ReverseEdges != null)
              fact.ReverseEdges.insertEdge(nodeId, this.Id, Types.EdgeKind.edkComponent_HasFiles);
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

            io.writeUInt4(m_TLLOC);
            io.writeUInt4(m_TLOC);
            io.writeUByte1((byte)m_analysisTime);
            fact.StringTable.setType(m_changesetID, StrTable.StrType.strToSave);
            io.writeUInt4(m_changesetID);
            fact.StringTable.setType(m_shortName, StrTable.StrType.strToSave);
            io.writeUInt4(m_shortName);


            foreach (var contains in containsContainer) {
              io.writeUInt4(contains);
            }
            io.writeUInt4(0); // This is the end sign

            foreach (var hasFiles in hasFilesContainer) {
              io.writeUInt4(hasFiles);
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

            m_TLLOC = binIo.readUInt4();
            m_TLOC = binIo.readUInt4();
            m_analysisTime = (Types.AnalysisTimeKind)binIo.readUByte1();
            m_changesetID = binIo.readUInt4();
            m_shortName = binIo.readUInt4();

            uint _id;

            _id = binIo.readUInt4();
            while (_id != 0) {
              containsContainer.AddLast(_id);
              _id = binIo.readUInt4();
            }

            _id = binIo.readUInt4();
            while (_id != 0) {
              hasFilesContainer.AddLast(_id);
              _id = binIo.readUInt4();
            }
        }

    }

}
