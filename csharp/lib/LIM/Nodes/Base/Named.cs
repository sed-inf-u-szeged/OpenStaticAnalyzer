using System;
using System.Text;
using System.Diagnostics;
using System.Collections.Generic;

namespace Columbus.Lim.Asg.Nodes.Base {

    /// <summary>
    /// Named class, which represents the base::Named node.
    /// </summary>
    [DebuggerDisplay("Id={Id}, Name=\"{Name}\"")]
#if (LIM_INTERNAL)
    internal
#else
    public
#endif
    class Named : Base {

        /// <summary>The Key of the `name`.</summary>
        protected uint m_name;


        // ---------- Edges ----------

        /// <summary>Container stores the id of the nodes the dependsOn edge points to and the association classes.</summary>
        protected LinkedList<ListIteratorAssoc<Columbus.Lim.Asg.Nodes.Base.Named>.AssocEdge> dependsOnAssocContainer;

        /// <summary>
        /// Constructor, only factory can instantiates nodes.
        /// </summary>
        /// <param name="nodeId">[in] The id of the node.</param>
        /// <param name="factory">[in] Poiter to the Factory the node belongs to.</param>
        public Named(uint nodeId, Factory factory) : base(nodeId, factory) {
            m_name = 0;
            dependsOnAssocContainer = new LinkedList<ListIteratorAssoc<Columbus.Lim.Asg.Nodes.Base.Named>.AssocEdge>();
        }

        /// <summary>
        /// Gives back the NodeKind of the node.
        /// </summary>
        /// <returns>Returns with the NodeKind.</returns>
        public override Types.NodeKind NodeKind {
            get { return Types.NodeKind.ndkNamed; }
        }


        // ---------- Attribute propert(y)(ies) ----------

        /// <summary>
        /// Gives back or sets the name of the node.
        /// </summary>
        public string Name
        {
            get
            {
                return fact.StringTable.get(m_name);
            }
            set
            {
                m_name = fact.StringTable.set( value );
            }
        }

        /// <summary>
        /// Gives back or sets the Key of name of the node.
        /// </summary>
        public uint NameKey
        {
            get
            {
                return m_name;
            }
            set
            {
               m_name = value;
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
        /// Gives back iterator for the dependsOn edges.
        /// </summary>
        /// <returns>Returns an iterator for the dependsOn edges.</returns>
        public ListIteratorAssocString<Columbus.Lim.Asg.Nodes.Base.Named> DependsOnListIteratorAssocBegin {
            get {
                return new ListIteratorAssocString<Columbus.Lim.Asg.Nodes.Base.Named>(dependsOnAssocContainer, fact, true);
            }
        }

        /// <summary>
        /// Gives back iterator for the dependsOn edges.
        /// </summary>
        /// <returns>Returns an iterator for the dependsOn edges.</returns>
        public ListIteratorAssocString<Columbus.Lim.Asg.Nodes.Base.Named> DependsOnListIteratorAssocEnd {
            get {
                return new ListIteratorAssocString<Columbus.Lim.Asg.Nodes.Base.Named>(dependsOnAssocContainer, fact, false);
            }
        }

        /// <summary>
        /// Tells whether the node has dependsOn edges or not.
        /// </summary>
        /// <returns>Returns true if the node has at least one dependsOn edge.</returns>
        public bool DependsOnIsEmpty {
            get { return dependsOnAssocContainer.Count == 0; }
        }

        /// <summary>
        /// Gives back how many dependsOn edges the node has.
        /// </summary>
        /// <returns>Returns with the number of dependsOn edges.</returns>
        public uint DependsOnSize {
            get { return (uint)(dependsOnAssocContainer.Count); }
        }


        // ---------- Edge setter function(s) ----------

        /// <summary>
        /// Adds a new dependsOn edge to the node.
        /// </summary>
        /// <param name="node">[in] The end point of the new dependsOn edge.</param>
        /// <param name="acValue">[in] The value of the association class.</param>
        /// <exception cref="Columbus.Lim.Asg.LimException">Throws LimException if there is something wrong with the given node.</exception>
        public void addDependsOn(Columbus.Lim.Asg.Nodes.Base.Named node, string acValue) {
            addDependsOn(node.Id, acValue);
        }

        /// <summary>
        /// Adds a new dependsOn edge to the node.
        /// </summary>
        /// <param name="nodeId">[in] The end point of the new dependsOn edge.</param>
        /// <param name="acValue">[in] The value of the association class.</param>
        /// <exception cref="Columbus.Lim.Asg.LimException">Throws LimException if the given nodeId is invalid.</exception>
        public void addDependsOn(uint nodeId, string acValue) {
            if (!fact.getExist(nodeId))
                throw new LimException("Columbus.Lim.Asg.Nodes.Base.Named.addDependsOn(NodeId)", "The end point of the edge does not exist.");
            Columbus.Lim.Asg.Nodes.Base.Base node = fact.getRef(nodeId);
            if (Common.getIsBaseClassKind(node.NodeKind, Types.NodeKind.ndkNamed)) {
                ListIteratorAssoc<Columbus.Lim.Asg.Nodes.Base.Named>.AssocEdge ac = new ListIteratorAssoc<Columbus.Lim.Asg.Nodes.Base.Named>.AssocEdge();
                ac.assocClass = new ListIteratorAssoc<Columbus.Lim.Asg.Nodes.Base.Named>.AssocClass();

                ac.id = nodeId;
                ac.assocClass.acString = Convert.ToString(fact.StringTable.set(acValue));

                dependsOnAssocContainer.AddLast(ac);
            } else {
                throw new LimException("Columbus.Lim.Asg.Nodes.Base.Named.setDependsOn(NodeId)", "Invalid NodeKind (" + node.NodeKind.ToString() + ").");
            }
            if (fact.ReverseEdges != null)
              fact.ReverseEdges.insertEdge(nodeId, this.Id, Types.EdgeKind.edkNamed_DependsOn);
        }

        /// <summary>
        /// Saves the node.
        /// </summary>
        /// <param name="io">[in] The node is written into io.</param>
        /// <exception cref="Columbus.ColumbusIOException">Throws ColumbusIOException if there is something wrong with the file.</exception>
        public override void save(IO io) {
            base.save(io);

            fact.StringTable.setType(m_name, StrTable.StrType.strToSave);
            io.writeUInt4(m_name);


            foreach (var dependsOnAssoc in dependsOnAssocContainer) {
                io.writeUInt4(dependsOnAssoc.id);
              fact.StringTable.setType(dependsOnAssoc.assocClass.acString, StrTable.StrType.strToSave);
              io.writeUInt4(Convert.ToUInt32(dependsOnAssoc.assocClass.acString));
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

            m_name = binIo.readUInt4();

            uint _id;

            _id = binIo.readUInt4();
            while (_id != 0) {
              string _ac = binIo.readUInt4().ToString();
                ListIteratorAssoc<Columbus.Lim.Asg.Nodes.Base.Named>.AssocEdge dependsOnAc = new ListIteratorAssoc<Columbus.Lim.Asg.Nodes.Base.Named>.AssocEdge();
                dependsOnAc.assocClass.acString = _ac;
                dependsOnAc.id = _id;
                dependsOnAssocContainer.AddLast(dependsOnAc);
              _id = binIo.readUInt4();
            }
        }

    }

}
