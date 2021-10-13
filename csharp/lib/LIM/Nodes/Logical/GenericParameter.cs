using System;
using System.Text;
using System.Diagnostics;
using System.Collections.Generic;

namespace Columbus.Lim.Asg.Nodes.Logical {

    /// <summary>
    /// GenericParameter class, which represents the logical::GenericParameter node.
    /// </summary>
    [DebuggerDisplay("Id={Id}, Name=\"{Name}\"")]
#if (LIM_INTERNAL)
    internal
#else
    public
#endif
    class GenericParameter : Columbus.Lim.Asg.Nodes.Base.Named {

        /// <summary>The GenericParameterKind of the node.</summary>
        protected Types.GenericParameterKind m_genericParameterKind;


        // ---------- Edges ----------

        /// <summary>Container stores the id of the nodes the hasParameterConstraint edge points to.</summary>
        protected LinkedList<uint> hasParameterConstraintContainer;

        /// <summary>
        /// Constructor, only factory can instantiates nodes.
        /// </summary>
        /// <param name="nodeId">[in] The id of the node.</param>
        /// <param name="factory">[in] Poiter to the Factory the node belongs to.</param>
        public GenericParameter(uint nodeId, Factory factory) : base(nodeId, factory) {
            m_genericParameterKind = Types.GenericParameterKind.gpkConstraint;
            hasParameterConstraintContainer = new LinkedList<uint>();
        }

        /// <summary>
        /// Gives back the NodeKind of the node.
        /// </summary>
        /// <returns>Returns with the NodeKind.</returns>
        public override Types.NodeKind NodeKind {
            get { return Types.NodeKind.ndkGenericParameter; }
        }


        // ---------- Attribute propert(y)(ies) ----------

        /// <summary>
        /// Gives back the genericParameterKind of the node.
        /// </summary>
        /// <returns>Returns with the genericParameterKind.</returns>
        public Types.GenericParameterKind GenericParameterKind
        {
            get
            {
                return m_genericParameterKind;
            }
            set
            {
                m_genericParameterKind = value;
            }
        }


        // ---------- Reflection getter function ----------

        /// <summary>
        /// Gives back the begin iterator for the edge specified
        /// </summary>
        /// <param name="edge">[in] The multiple edge for which the iterator is requested</param>
        public override ListIterator<Columbus.Lim.Asg.Nodes.Base.Base> GetListIteratorBegin(string edge) {
            switch(edge) {
                case "HasParameterConstraint":
                    return HasParameterConstraintListIteratorBegin.Convert<Columbus.Lim.Asg.Nodes.Base.Base>();
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
                case "HasParameterConstraint":
                    addHasParameterConstraint(nodeId);
                    return;
                default:
                    base.add(edge, nodeId);
                    return;
            }
        }


        // ---------- Edge getter function(s) ----------

        /// <summary>
        /// Gives back iterator for the hasParameterConstraint edges.
        /// </summary>
        /// <returns>Returns an iterator for the hasParameterConstraint edges.</returns>
        public ListIterator<Columbus.Lim.Asg.Nodes.Type.Type> HasParameterConstraintListIteratorBegin {
            get {
                return new ListIterator<Columbus.Lim.Asg.Nodes.Type.Type>(hasParameterConstraintContainer, fact, true);
            }
        }

        /// <summary>
        /// Gives back iterator for the hasParameterConstraint edges.
        /// </summary>
        /// <returns>Returns an iterator for the hasParameterConstraint edges.</returns>
        public ListIterator<Columbus.Lim.Asg.Nodes.Type.Type> HasParameterConstraintListIteratorEnd {
            get {
                return new ListIterator<Columbus.Lim.Asg.Nodes.Type.Type>(hasParameterConstraintContainer, fact, false);
            }
        }

        /// <summary>
        /// Tells whether the node has hasParameterConstraint edges or not.
        /// </summary>
        /// <returns>Returns true if the node has at least one hasParameterConstraint edge.</returns>
        public bool HasParameterConstraintIsEmpty {
            get { return hasParameterConstraintContainer.Count == 0; }
        }

        /// <summary>
        /// Gives back how many hasParameterConstraint edges the node has.
        /// </summary>
        /// <returns>Returns with the number of hasParameterConstraint edges.</returns>
        public uint HasParameterConstraintSize {
            get { return (uint)(hasParameterConstraintContainer.Count); }
        }


        // ---------- Edge setter function(s) ----------

        /// <summary>
        /// Adds a new hasParameterConstraint edge to the node and inserts it after the other ones.
        /// </summary>
        /// <param name="node">[in] The end point of the new hasParameterConstraint edge.</param>
        /// <exception cref="Columbus.Lim.Asg.LimException">Throws LimException if there is something wrong with the given node.</exception>
        public void addHasParameterConstraint(Columbus.Lim.Asg.Nodes.Type.Type node) {
            addHasParameterConstraint(node.Id);
        }

        /// <summary>
        /// Adds a new hasParameterConstraint edge to the node and inserts it after the other ones.
        /// </summary>
        /// <param name="nodeId">[in] The end point of the new hasParameterConstraint edge.</param>
        /// <exception cref="Columbus.Lim.Asg.LimException">Throws LimException if the given nodeId is invalid.</exception>
        public void addHasParameterConstraint(uint nodeId) {
            if (!fact.getExist(nodeId))
                throw new LimException("Columbus.Lim.Asg.Nodes.Logical.GenericParameter.addHasParameterConstraint(NodeId)", "The end point of the edge does not exist.");
            Columbus.Lim.Asg.Nodes.Base.Base node = fact.getRef(nodeId);
            if (Common.getIsBaseClassKind(node.NodeKind, Types.NodeKind.ndkType)) {
                hasParameterConstraintContainer.AddLast(nodeId);
            } else {
                throw new LimException("Columbus.Lim.Asg.Nodes.Logical.GenericParameter.setHasParameterConstraint(NodeId)", "Invalid NodeKind (" + node.NodeKind.ToString() + ").");
            }
            if (fact.ReverseEdges != null)
              fact.ReverseEdges.insertEdge(nodeId, this.Id, Types.EdgeKind.edkGenericParameter_HasParameterConstraint);
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

            io.writeUByte1((byte)m_genericParameterKind);


            foreach (var hasParameterConstraint in hasParameterConstraintContainer) {
              io.writeUInt4(hasParameterConstraint);
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

            m_genericParameterKind = (Types.GenericParameterKind)binIo.readUByte1();

            uint _id;

            _id = binIo.readUInt4();
            while (_id != 0) {
              hasParameterConstraintContainer.AddLast(_id);
              _id = binIo.readUInt4();
            }
        }

    }

}
