using System;
using System.Text;
using System.Diagnostics;
using System.Collections.Generic;

namespace Columbus.Lim.Asg.Nodes.Logical {

    /// <summary>
    /// Attribute class, which represents the logical::Attribute node.
    /// </summary>
    [DebuggerDisplay("Id={Id}, DemangledName=\"{DemangledName}\", Name=\"{Name}\"")]
#if (LIM_INTERNAL)
    internal
#else
    public
#endif
    class Attribute : Member {


        // ---------- Edges ----------

        /// <summary>Container stores the id of the nodes the calls edge points to.</summary>
        protected LinkedList<uint> callsContainer;

        /// <summary>Container stores the id of the nodes the hasType edge points to.</summary>
        protected LinkedList<uint> hasTypeContainer;

        /// <summary>
        /// Constructor, only factory can instantiates nodes.
        /// </summary>
        /// <param name="nodeId">[in] The id of the node.</param>
        /// <param name="factory">[in] Poiter to the Factory the node belongs to.</param>
        public Attribute(uint nodeId, Factory factory) : base(nodeId, factory) {
            callsContainer = new LinkedList<uint>();
            hasTypeContainer = new LinkedList<uint>();
        }

        /// <summary>
        /// Gives back the NodeKind of the node.
        /// </summary>
        /// <returns>Returns with the NodeKind.</returns>
        public override Types.NodeKind NodeKind {
            get { return Types.NodeKind.ndkAttribute; }
        }


        // ---------- Reflection getter function ----------

        /// <summary>
        /// Gives back the begin iterator for the edge specified
        /// </summary>
        /// <param name="edge">[in] The multiple edge for which the iterator is requested</param>
        public override ListIterator<Columbus.Lim.Asg.Nodes.Base.Base> GetListIteratorBegin(string edge) {
            switch(edge) {
                case "Calls":
                    return CallsListIteratorBegin.Convert<Columbus.Lim.Asg.Nodes.Base.Base>();
                case "HasType":
                    return HasTypeListIteratorBegin.Convert<Columbus.Lim.Asg.Nodes.Base.Base>();
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
                case "Calls":
                    addCalls(nodeId);
                    return;
                case "HasType":
                    addHasType(nodeId);
                    return;
                default:
                    base.add(edge, nodeId);
                    return;
            }
        }


        // ---------- Edge getter function(s) ----------

        /// <summary>
        /// Gives back iterator for the calls edges.
        /// </summary>
        /// <returns>Returns an iterator for the calls edges.</returns>
        public ListIterator<Columbus.Lim.Asg.Nodes.Logical.MethodCall> CallsListIteratorBegin {
            get {
                return new ListIterator<Columbus.Lim.Asg.Nodes.Logical.MethodCall>(callsContainer, fact, true);
            }
        }

        /// <summary>
        /// Gives back iterator for the calls edges.
        /// </summary>
        /// <returns>Returns an iterator for the calls edges.</returns>
        public ListIterator<Columbus.Lim.Asg.Nodes.Logical.MethodCall> CallsListIteratorEnd {
            get {
                return new ListIterator<Columbus.Lim.Asg.Nodes.Logical.MethodCall>(callsContainer, fact, false);
            }
        }

        /// <summary>
        /// Tells whether the node has calls edges or not.
        /// </summary>
        /// <returns>Returns true if the node has at least one calls edge.</returns>
        public bool CallsIsEmpty {
            get { return callsContainer.Count == 0; }
        }

        /// <summary>
        /// Gives back how many calls edges the node has.
        /// </summary>
        /// <returns>Returns with the number of calls edges.</returns>
        public uint CallsSize {
            get { return (uint)(callsContainer.Count); }
        }

        /// <summary>
        /// Gives back iterator for the hasType edges.
        /// </summary>
        /// <returns>Returns an iterator for the hasType edges.</returns>
        public ListIterator<Columbus.Lim.Asg.Nodes.Type.Type> HasTypeListIteratorBegin {
            get {
                return new ListIterator<Columbus.Lim.Asg.Nodes.Type.Type>(hasTypeContainer, fact, true);
            }
        }

        /// <summary>
        /// Gives back iterator for the hasType edges.
        /// </summary>
        /// <returns>Returns an iterator for the hasType edges.</returns>
        public ListIterator<Columbus.Lim.Asg.Nodes.Type.Type> HasTypeListIteratorEnd {
            get {
                return new ListIterator<Columbus.Lim.Asg.Nodes.Type.Type>(hasTypeContainer, fact, false);
            }
        }

        /// <summary>
        /// Tells whether the node has hasType edges or not.
        /// </summary>
        /// <returns>Returns true if the node has at least one hasType edge.</returns>
        public bool HasTypeIsEmpty {
            get { return hasTypeContainer.Count == 0; }
        }

        /// <summary>
        /// Gives back how many hasType edges the node has.
        /// </summary>
        /// <returns>Returns with the number of hasType edges.</returns>
        public uint HasTypeSize {
            get { return (uint)(hasTypeContainer.Count); }
        }


        // ---------- Edge setter function(s) ----------

        /// <summary>
        /// Adds a new calls edge to the node and inserts it after the other ones.
        /// </summary>
        /// <param name="node">[in] The end point of the new calls edge.</param>
        /// <exception cref="Columbus.Lim.Asg.LimException">Throws LimException if there is something wrong with the given node.</exception>
        public void addCalls(Columbus.Lim.Asg.Nodes.Logical.MethodCall node) {
            addCalls(node.Id);
        }

        /// <summary>
        /// Adds a new calls edge to the node and inserts it after the other ones.
        /// </summary>
        /// <param name="nodeId">[in] The end point of the new calls edge.</param>
        /// <exception cref="Columbus.Lim.Asg.LimException">Throws LimException if the given nodeId is invalid.</exception>
        public void addCalls(uint nodeId) {
            if (!fact.getExist(nodeId))
                throw new LimException("Columbus.Lim.Asg.Nodes.Logical.Attribute.addCalls(NodeId)", "The end point of the edge does not exist.");
            Columbus.Lim.Asg.Nodes.Base.Base node = fact.getRef(nodeId);
            if (Common.getIsBaseClassKind(node.NodeKind, Types.NodeKind.ndkMethodCall)) {
                callsContainer.AddLast(nodeId);
            } else {
                throw new LimException("Columbus.Lim.Asg.Nodes.Logical.Attribute.setCalls(NodeId)", "Invalid NodeKind (" + node.NodeKind.ToString() + ").");
            }
            if (fact.ReverseEdges != null)
              fact.ReverseEdges.insertEdge(nodeId, this.Id, Types.EdgeKind.edkAttribute_Calls);
        }

        /// <summary>
        /// Adds a new hasType edge to the node and inserts it after the other ones.
        /// </summary>
        /// <param name="node">[in] The end point of the new hasType edge.</param>
        /// <exception cref="Columbus.Lim.Asg.LimException">Throws LimException if there is something wrong with the given node.</exception>
        public void addHasType(Columbus.Lim.Asg.Nodes.Type.Type node) {
            addHasType(node.Id);
        }

        /// <summary>
        /// Adds a new hasType edge to the node and inserts it after the other ones.
        /// </summary>
        /// <param name="nodeId">[in] The end point of the new hasType edge.</param>
        /// <exception cref="Columbus.Lim.Asg.LimException">Throws LimException if the given nodeId is invalid.</exception>
        public void addHasType(uint nodeId) {
            if (!fact.getExist(nodeId))
                throw new LimException("Columbus.Lim.Asg.Nodes.Logical.Attribute.addHasType(NodeId)", "The end point of the edge does not exist.");
            Columbus.Lim.Asg.Nodes.Base.Base node = fact.getRef(nodeId);
            if (Common.getIsBaseClassKind(node.NodeKind, Types.NodeKind.ndkType)) {
                hasTypeContainer.AddLast(nodeId);
            } else {
                throw new LimException("Columbus.Lim.Asg.Nodes.Logical.Attribute.setHasType(NodeId)", "Invalid NodeKind (" + node.NodeKind.ToString() + ").");
            }
            if (fact.ReverseEdges != null)
              fact.ReverseEdges.insertEdge(nodeId, this.Id, Types.EdgeKind.edkAttribute_HasType);
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


            foreach (var calls in callsContainer) {
              io.writeUInt4(calls);
            }
            io.writeUInt4(0); // This is the end sign

            foreach (var hasType in hasTypeContainer) {
              io.writeUInt4(hasType);
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
              callsContainer.AddLast(_id);
              _id = binIo.readUInt4();
            }

            _id = binIo.readUInt4();
            while (_id != 0) {
              hasTypeContainer.AddLast(_id);
              _id = binIo.readUInt4();
            }
        }

    }

}
