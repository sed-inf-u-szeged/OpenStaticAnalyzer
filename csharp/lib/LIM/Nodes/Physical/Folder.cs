using System;
using System.Text;
using System.Diagnostics;
using System.Collections.Generic;

namespace Columbus.Lim.Asg.Nodes.Physical {

    /// <summary>
    /// Folder class, which represents the physical::Folder node.
    /// </summary>
    [DebuggerDisplay("Id={Id}, Name=\"{Name}\"")]
#if (LIM_INTERNAL)
    internal
#else
    public
#endif
    class Folder : FSEntry {


        // ---------- Edges ----------

        /// <summary>Container stores the id of the nodes the contains edge points to.</summary>
        protected LinkedList<uint> containsContainer;

        /// <summary>
        /// Constructor, only factory can instantiates nodes.
        /// </summary>
        /// <param name="nodeId">[in] The id of the node.</param>
        /// <param name="factory">[in] Poiter to the Factory the node belongs to.</param>
        public Folder(uint nodeId, Factory factory) : base(nodeId, factory) {
            containsContainer = new LinkedList<uint>();
        }

        /// <summary>
        /// Gives back the NodeKind of the node.
        /// </summary>
        /// <returns>Returns with the NodeKind.</returns>
        public override Types.NodeKind NodeKind {
            get { return Types.NodeKind.ndkFolder; }
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
        public ListIterator<Columbus.Lim.Asg.Nodes.Physical.FSEntry> ContainsListIteratorBegin {
            get {
                return new ListIterator<Columbus.Lim.Asg.Nodes.Physical.FSEntry>(containsContainer, fact, true);
            }
        }

        /// <summary>
        /// Gives back iterator for the contains edges.
        /// </summary>
        /// <returns>Returns an iterator for the contains edges.</returns>
        public ListIterator<Columbus.Lim.Asg.Nodes.Physical.FSEntry> ContainsListIteratorEnd {
            get {
                return new ListIterator<Columbus.Lim.Asg.Nodes.Physical.FSEntry>(containsContainer, fact, false);
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


        // ---------- Edge setter function(s) ----------

        /// <summary>
        /// Adds a new contains edge to the node and inserts it after the other ones.
        /// </summary>
        /// <param name="node">[in] The end point of the new contains edge.</param>
        /// <exception cref="Columbus.Lim.Asg.LimException">Throws LimException if there is something wrong with the given node.</exception>
        public void addContains(Columbus.Lim.Asg.Nodes.Physical.FSEntry node) {
            addContains(node.Id);
        }

        /// <summary>
        /// Adds a new contains edge to the node and inserts it after the other ones.
        /// </summary>
        /// <param name="nodeId">[in] The end point of the new contains edge.</param>
        /// <exception cref="Columbus.Lim.Asg.LimException">Throws LimException if the given nodeId is invalid.</exception>
        public void addContains(uint nodeId) {
            if (!fact.getExist(nodeId))
                throw new LimException("Columbus.Lim.Asg.Nodes.Physical.Folder.addContains(NodeId)", "The end point of the edge does not exist.");
            Columbus.Lim.Asg.Nodes.Base.Base node = fact.getRef(nodeId);
            if (Common.getIsBaseClassKind(node.NodeKind, Types.NodeKind.ndkFSEntry)) {
                containsContainer.AddLast(nodeId);
            } else {
                throw new LimException("Columbus.Lim.Asg.Nodes.Physical.Folder.setContains(NodeId)", "Invalid NodeKind (" + node.NodeKind.ToString() + ").");
            }
           setParentEdge(nodeId, (uint)Types.EdgeKind.edkFolder_Contains);
            if (fact.ReverseEdges != null)
              fact.ReverseEdges.insertEdge(nodeId, this.Id, Types.EdgeKind.edkFolder_Contains);
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


            foreach (var contains in containsContainer) {
              io.writeUInt4(contains);
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

            uint _id;

            _id = binIo.readUInt4();
            while (_id != 0) {
              containsContainer.AddLast(_id);
              setParentEdge(_id, (uint)Types.EdgeKind.edkFolder_Contains);
              _id = binIo.readUInt4();
            }
        }

    }

}
