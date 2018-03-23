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

namespace Columbus.Lim.Asg.Nodes.Physical {

    /// <summary>
    /// File class, which represents the physical::File node.
    /// </summary>
    [DebuggerDisplay("{DemangledName}")]
#if (LIM_INTERNAL)
    internal
#else
    public
#endif
    class File : FSEntry {

        /// <summary>The value of the `CLOC`.</summary>
        protected uint m_CLOC;

        /// <summary>The value of the `LLOC`.</summary>
        protected uint m_LLOC;

        /// <summary>The value of the `LOC`.</summary>
        protected uint m_LOC;

        /// <summary>The value of the `numberOfBranches`.</summary>
        protected uint m_numberOfBranches;


        // ---------- Edges ----------

        /// <summary>Container stores the id of the nodes the hasComment edge points to.</summary>
        protected LinkedList<uint> hasCommentContainer;

        /// <summary>Container stores the id of the nodes the includes edge points to.</summary>
        protected LinkedList<uint> includesContainer;

        /// <summary>
        /// Constructor, only factory can instantiates nodes.
        /// </summary>
        /// <param name="nodeId">[in] The id of the node.</param>
        /// <param name="factory">[in] Poiter to the Factory the node belongs to.</param>
        public File(uint nodeId, Factory factory) : base(nodeId, factory) {
            m_CLOC = 0;
            m_LLOC = 0;
            m_LOC = 0;
            m_numberOfBranches = 0;
            hasCommentContainer = new LinkedList<uint>();
            includesContainer = new LinkedList<uint>();
        }

        /// <summary>
        /// Gives back the NodeKind of the node.
        /// </summary>
        /// <returns>Returns with the NodeKind.</returns>
        public override Types.NodeKind NodeKind {
            get { return Types.NodeKind.ndkFile; }
        }


        // ---------- Attribute propert(y)(ies) ----------

        /// <summary>
        /// Gives back the CLOC of the node.
        /// </summary>
        /// <returns>Returns with the CLOC.</returns>
        public uint CLOC
        {
            get
            {
                return m_CLOC;
            }
            set
            {
                m_CLOC = value;
            }
        }

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
        /// Gives back the numberOfBranches of the node.
        /// </summary>
        /// <returns>Returns with the numberOfBranches.</returns>
        public uint NumberOfBranches
        {
            get
            {
                return m_numberOfBranches;
            }
            set
            {
                m_numberOfBranches = value;
            }
        }


        // ---------- Reflection getter function ----------

        /// <summary>
        /// Gives back the begin iterator for the edge specified
        /// </summary>
        /// <param name="edge">[in] The multiple edge for which the iterator is requested</param>
        public override ListIterator<Columbus.Lim.Asg.Nodes.Base.Base> GetListIteratorBegin(string edge) {
            switch(edge) {
                case "HasComment":
                    return HasCommentListIteratorBegin.Convert<Columbus.Lim.Asg.Nodes.Base.Base>();
                case "Includes":
                    return IncludesListIteratorBegin.Convert<Columbus.Lim.Asg.Nodes.Base.Base>();
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
                case "HasComment":
                    addHasComment(nodeId);
                    return;
                case "Includes":
                    addIncludes(nodeId);
                    return;
                default:
                    base.add(edge, nodeId);
                    return;
            }
        }


        // ---------- Edge getter function(s) ----------

        /// <summary>
        /// Gives back iterator for the hasComment edges.
        /// </summary>
        /// <returns>Returns an iterator for the hasComment edges.</returns>
        public ListIterator<Columbus.Lim.Asg.Nodes.Base.Comment> HasCommentListIteratorBegin {
            get {
                return new ListIterator<Columbus.Lim.Asg.Nodes.Base.Comment>(hasCommentContainer, fact, true);
            }
        }

        /// <summary>
        /// Gives back iterator for the hasComment edges.
        /// </summary>
        /// <returns>Returns an iterator for the hasComment edges.</returns>
        public ListIterator<Columbus.Lim.Asg.Nodes.Base.Comment> HasCommentListIteratorEnd {
            get {
                return new ListIterator<Columbus.Lim.Asg.Nodes.Base.Comment>(hasCommentContainer, fact, false);
            }
        }

        /// <summary>
        /// Tells whether the node has hasComment edges or not.
        /// </summary>
        /// <returns>Returns true if the node has at least one hasComment edge.</returns>
        public bool HasCommentIsEmpty {
            get { return hasCommentContainer.Count == 0; }
        }

        /// <summary>
        /// Gives back how many hasComment edges the node has.
        /// </summary>
        /// <returns>Returns with the number of hasComment edges.</returns>
        public uint HasCommentSize {
            get { return (uint)(hasCommentContainer.Count); }
        }

        /// <summary>
        /// Gives back iterator for the includes edges.
        /// </summary>
        /// <returns>Returns an iterator for the includes edges.</returns>
        public ListIterator<Columbus.Lim.Asg.Nodes.Physical.File> IncludesListIteratorBegin {
            get {
                return new ListIterator<Columbus.Lim.Asg.Nodes.Physical.File>(includesContainer, fact, true);
            }
        }

        /// <summary>
        /// Gives back iterator for the includes edges.
        /// </summary>
        /// <returns>Returns an iterator for the includes edges.</returns>
        public ListIterator<Columbus.Lim.Asg.Nodes.Physical.File> IncludesListIteratorEnd {
            get {
                return new ListIterator<Columbus.Lim.Asg.Nodes.Physical.File>(includesContainer, fact, false);
            }
        }

        /// <summary>
        /// Tells whether the node has includes edges or not.
        /// </summary>
        /// <returns>Returns true if the node has at least one includes edge.</returns>
        public bool IncludesIsEmpty {
            get { return includesContainer.Count == 0; }
        }

        /// <summary>
        /// Gives back how many includes edges the node has.
        /// </summary>
        /// <returns>Returns with the number of includes edges.</returns>
        public uint IncludesSize {
            get { return (uint)(includesContainer.Count); }
        }


        // ---------- Edge setter function(s) ----------

        /// <summary>
        /// Adds a new hasComment edge to the node and inserts it after the other ones.
        /// </summary>
        /// <param name="node">[in] The end point of the new hasComment edge.</param>
        /// <exception cref="Columbus.Lim.Asg.LimException">Throws LimException if there is something wrong with the given node.</exception>
        public void addHasComment(Columbus.Lim.Asg.Nodes.Base.Comment node) {
            addHasComment(node.Id);
        }

        /// <summary>
        /// Adds a new hasComment edge to the node and inserts it after the other ones.
        /// </summary>
        /// <param name="nodeId">[in] The end point of the new hasComment edge.</param>
        /// <exception cref="Columbus.Lim.Asg.LimException">Throws LimException if the given nodeId is invalid.</exception>
        public void addHasComment(uint nodeId) {
            if (!fact.getExist(nodeId))
                throw new LimException("Columbus.Lim.Asg.Nodes.Physical.File.addHasComment(NodeId)", "The end point of the edge does not exist.");
            Columbus.Lim.Asg.Nodes.Base.Base node = fact.getRef(nodeId);
            if (Common.getIsBaseClassKind(node.NodeKind, Types.NodeKind.ndkComment)) {
                hasCommentContainer.AddLast(nodeId);
            } else {
                throw new LimException("Columbus.Lim.Asg.Nodes.Physical.File.setHasComment(NodeId)", "Invalid NodeKind (" + node.NodeKind.ToString() + ").");
            }
            if (fact.ReverseEdges != null)
              fact.ReverseEdges.insertEdge(nodeId, this.Id, Types.EdgeKind.edkFile_HasComment);
        }

        /// <summary>
        /// Adds a new includes edge to the node and inserts it after the other ones.
        /// </summary>
        /// <param name="node">[in] The end point of the new includes edge.</param>
        /// <exception cref="Columbus.Lim.Asg.LimException">Throws LimException if there is something wrong with the given node.</exception>
        public void addIncludes(Columbus.Lim.Asg.Nodes.Physical.File node) {
            addIncludes(node.Id);
        }

        /// <summary>
        /// Adds a new includes edge to the node and inserts it after the other ones.
        /// </summary>
        /// <param name="nodeId">[in] The end point of the new includes edge.</param>
        /// <exception cref="Columbus.Lim.Asg.LimException">Throws LimException if the given nodeId is invalid.</exception>
        public void addIncludes(uint nodeId) {
            if (!fact.getExist(nodeId))
                throw new LimException("Columbus.Lim.Asg.Nodes.Physical.File.addIncludes(NodeId)", "The end point of the edge does not exist.");
            Columbus.Lim.Asg.Nodes.Base.Base node = fact.getRef(nodeId);
            if (Common.getIsBaseClassKind(node.NodeKind, Types.NodeKind.ndkFile)) {
                includesContainer.AddLast(nodeId);
            } else {
                throw new LimException("Columbus.Lim.Asg.Nodes.Physical.File.setIncludes(NodeId)", "Invalid NodeKind (" + node.NodeKind.ToString() + ").");
            }
            if (fact.ReverseEdges != null)
              fact.ReverseEdges.insertEdge(nodeId, this.Id, Types.EdgeKind.edkFile_Includes);
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

            io.writeUInt4(m_CLOC);
            io.writeUInt4(m_LLOC);
            io.writeUInt4(m_LOC);
            io.writeUInt4(m_numberOfBranches);


            foreach (var hasComment in hasCommentContainer) {
              io.writeUInt4(hasComment);
            }
            io.writeUInt4(0); // This is the end sign

            foreach (var includes in includesContainer) {
              io.writeUInt4(includes);
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

            m_CLOC = binIo.readUInt4();
            m_LLOC = binIo.readUInt4();
            m_LOC = binIo.readUInt4();
            m_numberOfBranches = binIo.readUInt4();

            uint _id;

            _id = binIo.readUInt4();
            while (_id != 0) {
              hasCommentContainer.AddLast(_id);
              _id = binIo.readUInt4();
            }

            _id = binIo.readUInt4();
            while (_id != 0) {
              includesContainer.AddLast(_id);
              _id = binIo.readUInt4();
            }
        }

    }

}
