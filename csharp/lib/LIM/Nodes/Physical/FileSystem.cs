using System;
using System.Text;
using System.Diagnostics;
using System.Collections.Generic;

namespace Columbus.Lim.Asg.Nodes.Physical {

    /// <summary>
    /// FileSystem class, which represents the physical::FileSystem node.
    /// </summary>
    [DebuggerDisplay("Id={Id}, Name=\"{Name}\"")]
#if (LIM_INTERNAL)
    internal
#else
    public
#endif
    class FileSystem : Columbus.Lim.Asg.Nodes.Base.Named {


        // ---------- Edges ----------

        /// <summary>Container stores the id of the nodes the hasFSEntry edge points to.</summary>
        protected LinkedList<uint> hasFSEntryContainer;

        /// <summary>
        /// Constructor, only factory can instantiates nodes.
        /// </summary>
        /// <param name="nodeId">[in] The id of the node.</param>
        /// <param name="factory">[in] Poiter to the Factory the node belongs to.</param>
        public FileSystem(uint nodeId, Factory factory) : base(nodeId, factory) {
            hasFSEntryContainer = new LinkedList<uint>();
        }

        /// <summary>
        /// Gives back the NodeKind of the node.
        /// </summary>
        /// <returns>Returns with the NodeKind.</returns>
        public override Types.NodeKind NodeKind {
            get { return Types.NodeKind.ndkFileSystem; }
        }


        // ---------- Reflection getter function ----------

        /// <summary>
        /// Gives back the begin iterator for the edge specified
        /// </summary>
        /// <param name="edge">[in] The multiple edge for which the iterator is requested</param>
        public override ListIterator<Columbus.Lim.Asg.Nodes.Base.Base> GetListIteratorBegin(string edge) {
            switch(edge) {
                case "HasFSEntry":
                    return HasFSEntryListIteratorBegin.Convert<Columbus.Lim.Asg.Nodes.Base.Base>();
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
                case "HasFSEntry":
                    addHasFSEntry(nodeId);
                    return;
                default:
                    base.add(edge, nodeId);
                    return;
            }
        }


        // ---------- Edge getter function(s) ----------

        /// <summary>
        /// Gives back iterator for the hasFSEntry edges.
        /// </summary>
        /// <returns>Returns an iterator for the hasFSEntry edges.</returns>
        public ListIterator<Columbus.Lim.Asg.Nodes.Physical.FSEntry> HasFSEntryListIteratorBegin {
            get {
                return new ListIterator<Columbus.Lim.Asg.Nodes.Physical.FSEntry>(hasFSEntryContainer, fact, true);
            }
        }

        /// <summary>
        /// Gives back iterator for the hasFSEntry edges.
        /// </summary>
        /// <returns>Returns an iterator for the hasFSEntry edges.</returns>
        public ListIterator<Columbus.Lim.Asg.Nodes.Physical.FSEntry> HasFSEntryListIteratorEnd {
            get {
                return new ListIterator<Columbus.Lim.Asg.Nodes.Physical.FSEntry>(hasFSEntryContainer, fact, false);
            }
        }

        /// <summary>
        /// Tells whether the node has hasFSEntry edges or not.
        /// </summary>
        /// <returns>Returns true if the node has at least one hasFSEntry edge.</returns>
        public bool HasFSEntryIsEmpty {
            get { return hasFSEntryContainer.Count == 0; }
        }

        /// <summary>
        /// Gives back how many hasFSEntry edges the node has.
        /// </summary>
        /// <returns>Returns with the number of hasFSEntry edges.</returns>
        public uint HasFSEntrySize {
            get { return (uint)(hasFSEntryContainer.Count); }
        }


        // ---------- Edge setter function(s) ----------

        /// <summary>
        /// Adds a new hasFSEntry edge to the node and inserts it after the other ones.
        /// </summary>
        /// <param name="node">[in] The end point of the new hasFSEntry edge.</param>
        /// <exception cref="Columbus.Lim.Asg.LimException">Throws LimException if there is something wrong with the given node.</exception>
        public void addHasFSEntry(Columbus.Lim.Asg.Nodes.Physical.FSEntry node) {
            addHasFSEntry(node.Id);
        }

        /// <summary>
        /// Adds a new hasFSEntry edge to the node and inserts it after the other ones.
        /// </summary>
        /// <param name="nodeId">[in] The end point of the new hasFSEntry edge.</param>
        /// <exception cref="Columbus.Lim.Asg.LimException">Throws LimException if the given nodeId is invalid.</exception>
        public void addHasFSEntry(uint nodeId) {
            if (!fact.getExist(nodeId))
                throw new LimException("Columbus.Lim.Asg.Nodes.Physical.FileSystem.addHasFSEntry(NodeId)", "The end point of the edge does not exist.");
            Columbus.Lim.Asg.Nodes.Base.Base node = fact.getRef(nodeId);
            if (Common.getIsBaseClassKind(node.NodeKind, Types.NodeKind.ndkFSEntry)) {
                hasFSEntryContainer.AddLast(nodeId);
            } else {
                throw new LimException("Columbus.Lim.Asg.Nodes.Physical.FileSystem.setHasFSEntry(NodeId)", "Invalid NodeKind (" + node.NodeKind.ToString() + ").");
            }
           setParentEdge(nodeId, (uint)Types.EdgeKind.edkFileSystem_HasFSEntry);
            if (fact.ReverseEdges != null)
              fact.ReverseEdges.insertEdge(nodeId, this.Id, Types.EdgeKind.edkFileSystem_HasFSEntry);
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


            foreach (var hasFSEntry in hasFSEntryContainer) {
              io.writeUInt4(hasFSEntry);
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
              hasFSEntryContainer.AddLast(_id);
              setParentEdge(_id, (uint)Types.EdgeKind.edkFileSystem_HasFSEntry);
              _id = binIo.readUInt4();
            }
        }

    }

}
