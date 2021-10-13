using System;
using System.Text;
using System.Diagnostics;
using System.Collections.Generic;

namespace Columbus.Lim.Asg.Nodes.Logical {

    /// <summary>
    /// ClassGenericInstance class, which represents the logical::ClassGenericInstance node.
    /// </summary>
    [DebuggerDisplay("Id={Id}, DemangledName=\"{DemangledName}\", Name=\"{Name}\"")]
#if (LIM_INTERNAL)
    internal
#else
    public
#endif
    class ClassGenericInstance : Class {

        /// <summary>Stores whether the node is `RealInstance` or not.</summary>
        protected bool m_isRealInstance;


        // ---------- Edges ----------

        /// <summary>Container stores the id of the nodes the hasArguments edge points to and the association classes.</summary>
        protected LinkedList<ListIteratorAssoc<Columbus.Lim.Asg.Nodes.Type.Type>.AssocEdge> hasArgumentsAssocContainer;

        /// <summary>
        /// Constructor, only factory can instantiates nodes.
        /// </summary>
        /// <param name="nodeId">[in] The id of the node.</param>
        /// <param name="factory">[in] Poiter to the Factory the node belongs to.</param>
        public ClassGenericInstance(uint nodeId, Factory factory) : base(nodeId, factory) {
            m_isRealInstance = false;
            hasArgumentsAssocContainer = new LinkedList<ListIteratorAssoc<Columbus.Lim.Asg.Nodes.Type.Type>.AssocEdge>();
        }

        /// <summary>
        /// Gives back the NodeKind of the node.
        /// </summary>
        /// <returns>Returns with the NodeKind.</returns>
        public override Types.NodeKind NodeKind {
            get { return Types.NodeKind.ndkClassGenericInstance; }
        }


        // ---------- Attribute propert(y)(ies) ----------

        /// <summary>
        /// Gives back the isRealInstance of the node.
        /// </summary>
        /// <returns>Returns with the isRealInstance.</returns>
        public bool IsRealInstance
        {
            get
            {
                return m_isRealInstance;
            }
            set
            {
                m_isRealInstance = value;
            }
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
        /// Gives back iterator for the hasArguments edges.
        /// </summary>
        /// <returns>Returns an iterator for the hasArguments edges.</returns>
        public ListIteratorAssocTypeArgumentConstraintKind<Columbus.Lim.Asg.Nodes.Type.Type> HasArgumentsListIteratorAssocBegin {
            get {
                return new ListIteratorAssocTypeArgumentConstraintKind<Columbus.Lim.Asg.Nodes.Type.Type>(hasArgumentsAssocContainer, fact, true);
            }
        }

        /// <summary>
        /// Gives back iterator for the hasArguments edges.
        /// </summary>
        /// <returns>Returns an iterator for the hasArguments edges.</returns>
        public ListIteratorAssocTypeArgumentConstraintKind<Columbus.Lim.Asg.Nodes.Type.Type> HasArgumentsListIteratorAssocEnd {
            get {
                return new ListIteratorAssocTypeArgumentConstraintKind<Columbus.Lim.Asg.Nodes.Type.Type>(hasArgumentsAssocContainer, fact, false);
            }
        }

        /// <summary>
        /// Tells whether the node has hasArguments edges or not.
        /// </summary>
        /// <returns>Returns true if the node has at least one hasArguments edge.</returns>
        public bool HasArgumentsIsEmpty {
            get { return hasArgumentsAssocContainer.Count == 0; }
        }

        /// <summary>
        /// Gives back how many hasArguments edges the node has.
        /// </summary>
        /// <returns>Returns with the number of hasArguments edges.</returns>
        public uint HasArgumentsSize {
            get { return (uint)(hasArgumentsAssocContainer.Count); }
        }


        // ---------- Edge setter function(s) ----------

        /// <summary>
        /// Adds a new hasArguments edge to the node.
        /// </summary>
        /// <param name="node">[in] The end point of the new hasArguments edge.</param>
        /// <param name="acValue">[in] The value of the association class.</param>
        /// <exception cref="Columbus.Lim.Asg.LimException">Throws LimException if there is something wrong with the given node.</exception>
        public void addHasArguments(Columbus.Lim.Asg.Nodes.Type.Type node, Types.TypeArgumentConstraintKind acValue) {
            addHasArguments(node.Id, acValue);
        }

        /// <summary>
        /// Adds a new hasArguments edge to the node.
        /// </summary>
        /// <param name="nodeId">[in] The end point of the new hasArguments edge.</param>
        /// <param name="acValue">[in] The value of the association class.</param>
        /// <exception cref="Columbus.Lim.Asg.LimException">Throws LimException if the given nodeId is invalid.</exception>
        public void addHasArguments(uint nodeId, Types.TypeArgumentConstraintKind acValue) {
            if (!fact.getExist(nodeId))
                throw new LimException("Columbus.Lim.Asg.Nodes.Logical.ClassGenericInstance.addHasArguments(NodeId)", "The end point of the edge does not exist.");
            Columbus.Lim.Asg.Nodes.Base.Base node = fact.getRef(nodeId);
            if (Common.getIsBaseClassKind(node.NodeKind, Types.NodeKind.ndkType)) {
                ListIteratorAssoc<Columbus.Lim.Asg.Nodes.Type.Type>.AssocEdge ac = new ListIteratorAssoc<Columbus.Lim.Asg.Nodes.Type.Type>.AssocEdge();
                ac.assocClass = new ListIteratorAssoc<Columbus.Lim.Asg.Nodes.Type.Type>.AssocClass();

                ac.id = nodeId;
                ac.assocClass.acTypeArgumentConstraintKind = acValue;

                hasArgumentsAssocContainer.AddLast(ac);
            } else {
                throw new LimException("Columbus.Lim.Asg.Nodes.Logical.ClassGenericInstance.setHasArguments(NodeId)", "Invalid NodeKind (" + node.NodeKind.ToString() + ").");
            }
            if (fact.ReverseEdges != null)
              fact.ReverseEdges.insertEdge(nodeId, this.Id, Types.EdgeKind.edkClassGenericInstance_HasArguments);
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
            if (m_isRealInstance)
              boolValues |= 1;
            io.writeUByte1(boolValues);


            foreach (var hasArgumentsAssoc in hasArgumentsAssocContainer) {
                io.writeUInt4(hasArgumentsAssoc.id);
              io.writeUByte1((byte)hasArgumentsAssoc.assocClass.acTypeArgumentConstraintKind);
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
            m_isRealInstance = Convert.ToBoolean(boolValues & 1);
            boolValues >>= 1;

            uint _id;

            _id = binIo.readUInt4();
            while (_id != 0) {
              Types.TypeArgumentConstraintKind _ac = (Types.TypeArgumentConstraintKind)(binIo.readUByte1());
                ListIteratorAssoc<Columbus.Lim.Asg.Nodes.Type.Type>.AssocEdge hasArgumentsAc = new ListIteratorAssoc<Columbus.Lim.Asg.Nodes.Type.Type>.AssocEdge();
                hasArgumentsAc.assocClass.acTypeArgumentConstraintKind = _ac;
                hasArgumentsAc.id = _id;
                hasArgumentsAssocContainer.AddLast(hasArgumentsAc);
              _id = binIo.readUInt4();
            }
        }

    }

}
