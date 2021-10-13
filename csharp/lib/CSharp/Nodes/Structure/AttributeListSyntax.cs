using System;
using System.Text;
using System.Diagnostics;
using System.Collections.Generic;

namespace Columbus.Csharp.Asg.Nodes.Structure {

    /// <summary>
    /// AttributeListSyntax class, which represents the structure::AttributeListSyntax node.
    /// </summary>
    [DebuggerDisplay("Id={Id}")]
#if (CSHARP_INTERNAL)
    internal
#else
    public
#endif
    class AttributeListSyntax : Columbus.Csharp.Asg.Nodes.Base.Positioned {


        // ---------- Edges ----------

        /// <summary>Container stores the id of the nodes the Attributes edge points to.</summary>
        protected LinkedList<uint> AttributesContainer;

        /// <summary>The id of the node the Target edge points to.</summary>
        protected uint m_Target;

        /// <summary>
        /// Constructor, only factory can instantiates nodes.
        /// </summary>
        /// <param name="nodeId">[in] The id of the node.</param>
        /// <param name="factory">[in] Poiter to the Factory the node belongs to.</param>
        public AttributeListSyntax(uint nodeId, Factory factory) : base(nodeId, factory) {
            AttributesContainer = new LinkedList<uint>();
            m_Target = 0;
        }

        /// <summary>
        /// Gives back the NodeKind of the node.
        /// </summary>
        /// <returns>Returns with the NodeKind.</returns>
        public override Types.NodeKind NodeKind {
            get { return Types.NodeKind.ndkAttributeListSyntax; }
        }


        // ---------- Reflection getter function ----------

        /// <summary>
        /// Gives back the begin iterator for the edge specified
        /// </summary>
        /// <param name="edge">[in] The multiple edge for which the iterator is requested</param>
        public override ListIterator<Columbus.Csharp.Asg.Nodes.Base.Base> GetListIteratorBegin(string edge) {
            switch(edge) {
                case "Attributes":
                    return AttributesListIteratorBegin.Convert<Columbus.Csharp.Asg.Nodes.Base.Base>();
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
                case "Attributes":
                    addAttributes(nodeId);
                    return;
                default:
                    base.add(edge, nodeId);
                    return;
            }
        }


        // ---------- Edge getter function(s) ----------

        /// <summary>
        /// Gives back iterator for the Attributes edges.
        /// </summary>
        /// <returns>Returns an iterator for the Attributes edges.</returns>
        public ListIterator<Columbus.Csharp.Asg.Nodes.Structure.AttributeSyntax> AttributesListIteratorBegin {
            get {
                return new ListIterator<Columbus.Csharp.Asg.Nodes.Structure.AttributeSyntax>(AttributesContainer, fact, true);
            }
        }

        /// <summary>
        /// Gives back iterator for the Attributes edges.
        /// </summary>
        /// <returns>Returns an iterator for the Attributes edges.</returns>
        public ListIterator<Columbus.Csharp.Asg.Nodes.Structure.AttributeSyntax> AttributesListIteratorEnd {
            get {
                return new ListIterator<Columbus.Csharp.Asg.Nodes.Structure.AttributeSyntax>(AttributesContainer, fact, false);
            }
        }

        /// <summary>
        /// Tells whether the node has Attributes edges or not.
        /// </summary>
        /// <returns>Returns true if the node has at least one Attributes edge.</returns>
        public bool AttributesIsEmpty {
            get { return AttributesContainer.Count == 0; }
        }

        /// <summary>
        /// Gives back how many Attributes edges the node has.
        /// </summary>
        /// <returns>Returns with the number of Attributes edges.</returns>
        public uint AttributesSize {
            get { return (uint)(AttributesContainer.Count); }
        }

        /// <summary>
        /// Gives back the id of the node the Target edge points to.
        /// </summary>
        /// <returns>Returns the end point of the m_Target edge.</returns>
        /// <exception cref="Columbus.Csharp.Asg.CsharpException">Throws CsharpException if the edge id is invalid.</exception>
        public uint getTarget() {
            if (fact.getIsFiltered(m_Target))
                return 1;
            else
                return m_Target;
        }


        // ---------- Edge setter function(s) ----------

        /// <summary>
        /// Adds a new Attributes edge to the node and inserts it after the other ones.
        /// </summary>
        /// <param name="node">[in] The end point of the new Attributes edge.</param>
        /// <exception cref="Columbus.Csharp.Asg.CsharpException">Throws CsharpException if there is something wrong with the given node.</exception>
        public void addAttributes(Columbus.Csharp.Asg.Nodes.Structure.AttributeSyntax node) {
            addAttributes(node.Id);
        }

        /// <summary>
        /// Adds a new Attributes edge to the node and inserts it after the other ones.
        /// </summary>
        /// <param name="nodeId">[in] The end point of the new Attributes edge.</param>
        /// <exception cref="Columbus.Csharp.Asg.CsharpException">Throws CsharpException if the given nodeId is invalid.</exception>
        public void addAttributes(uint nodeId) {
            if (!fact.getExist(nodeId))
                throw new CsharpException("Columbus.Csharp.Asg.Nodes.Structure.AttributeListSyntax.addAttributes(NodeId)", "The end point of the edge does not exist.");
            Columbus.Csharp.Asg.Nodes.Base.Base node = fact.getRef(nodeId);
            if (Common.getIsBaseClassKind(node.NodeKind, Types.NodeKind.ndkAttributeSyntax)) {
                AttributesContainer.AddLast(nodeId);
            } else {
                throw new CsharpException("Columbus.Csharp.Asg.Nodes.Structure.AttributeListSyntax.setAttributes(NodeId)", "Invalid NodeKind (" + node.NodeKind.ToString() + ").");
            }
           setParentEdge(nodeId, (uint)Types.EdgeKind.edkAttributeListSyntax_Attributes);
            if (fact.ReverseEdges != null)
              fact.ReverseEdges.insertEdge(nodeId, this.Id, Types.EdgeKind.edkAttributeListSyntax_Attributes);
        }

        /// <summary>
        /// Sets the Target edge.
        /// </summary>
        /// <param name="nodeId">[in] The new end point of the Target edge or 0. With 0 the edge can be deleted.</param>
        /// <exception cref="Columbus.Csharp.Asg.CsharpException">Throws CsharpException if the nodeId is invalid.</exception>
        public void setTarget(uint nodeId) {
            if (nodeId != 0) {
                if (!fact.getExist(nodeId))
                    throw new CsharpException("Columbus.Csharp.Asg.Nodes.Structure.AttributeListSyntax.setTarget(NodeId)", "The end point of the edge does not exist.");

                Columbus.Csharp.Asg.Nodes.Base.Base node = fact.getRef(nodeId);
                if (Common.getIsBaseClassKind(node.NodeKind, Types.NodeKind.ndkAttributeTargetSpecifierSyntax)) {
                    if (m_Target != 0) {
                        removeParentEdge(m_Target);
                    }
                    m_Target = nodeId;
                    setParentEdge(m_Target, (uint)Types.EdgeKind.edkAttributeListSyntax_Target);
                } else {
                    throw new CsharpException("Columbus.Csharp.Asg.Nodes.Structure.AttributeListSyntax.setTarget(NodeId)", "Invalid NodeKind (" + node.NodeKind.ToString() + ").");
                }
            } else {
                if (m_Target != 0) {
                    removeParentEdge(m_Target);
                }
                m_Target = 0;
            }
        }

        /// <summary>
        /// Sets the Target edge.
        /// </summary>
        /// <param name="node">[in] The new end point of the Target edge.</param>
        /// <exception cref="Columbus.Csharp.Asg.CsharpException">Throws CsharpException if there's something wrong with the given node.</exception>
        public void setTarget(Columbus.Csharp.Asg.Nodes.Structure.AttributeTargetSpecifierSyntax node) {
            if (m_Target != 0) {
                removeParentEdge(m_Target);
            }
            m_Target = node.Id;
            setParentEdge(m_Target, (uint)Types.EdgeKind.edkAttributeListSyntax_Target);
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

            io.writeUInt4(m_Target);


            foreach (var Attributes in AttributesContainer) {
              io.writeUInt4(Attributes);
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

            m_Target =  binIo.readUInt4();
            if (m_Target != 0)
              setParentEdge(m_Target,(uint)Types.EdgeKind.edkAttributeListSyntax_Target);

            uint _id;

            _id = binIo.readUInt4();
            while (_id != 0) {
              AttributesContainer.AddLast(_id);
              setParentEdge(_id, (uint)Types.EdgeKind.edkAttributeListSyntax_Attributes);
              _id = binIo.readUInt4();
            }
        }

    }

}
