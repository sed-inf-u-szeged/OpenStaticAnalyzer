using System;
using System.Text;
using System.Diagnostics;
using System.Collections.Generic;

namespace Columbus.Csharp.Asg.Nodes.Expression {

    /// <summary>
    /// IdentifierNameSyntax class, which represents the expression::IdentifierNameSyntax node.
    /// </summary>
    [DebuggerDisplay("Id={Id}, Identifier=\"{Identifier}\"")]
#if (CSHARP_INTERNAL)
    internal
#else
    public
#endif
    class IdentifierNameSyntax : SimpleNameSyntax {


        // ---------- Edges ----------

        /// <summary>Container stores the id of the nodes the AccessorCall edge points to.</summary>
        protected LinkedList<uint> AccessorCallContainer;

        /// <summary>The id of the node the Declaration edge points to.</summary>
        protected uint m_Declaration;

        /// <summary>
        /// Constructor, only factory can instantiates nodes.
        /// </summary>
        /// <param name="nodeId">[in] The id of the node.</param>
        /// <param name="factory">[in] Poiter to the Factory the node belongs to.</param>
        public IdentifierNameSyntax(uint nodeId, Factory factory) : base(nodeId, factory) {
            AccessorCallContainer = new LinkedList<uint>();
            m_Declaration = 0;
        }

        /// <summary>
        /// Gives back the NodeKind of the node.
        /// </summary>
        /// <returns>Returns with the NodeKind.</returns>
        public override Types.NodeKind NodeKind {
            get { return Types.NodeKind.ndkIdentifierNameSyntax; }
        }


        // ---------- Reflection getter function ----------

        /// <summary>
        /// Gives back the begin iterator for the edge specified
        /// </summary>
        /// <param name="edge">[in] The multiple edge for which the iterator is requested</param>
        public override ListIterator<Columbus.Csharp.Asg.Nodes.Base.Base> GetListIteratorBegin(string edge) {
            switch(edge) {
                case "AccessorCall":
                    return AccessorCallListIteratorBegin.Convert<Columbus.Csharp.Asg.Nodes.Base.Base>();
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
                case "AccessorCall":
                    addAccessorCall(nodeId);
                    return;
                default:
                    base.add(edge, nodeId);
                    return;
            }
        }


        // ---------- Edge getter function(s) ----------

        /// <summary>
        /// Gives back iterator for the AccessorCall edges.
        /// </summary>
        /// <returns>Returns an iterator for the AccessorCall edges.</returns>
        public ListIterator<Columbus.Csharp.Asg.Nodes.Structure.AccessorDeclarationSyntax> AccessorCallListIteratorBegin {
            get {
                return new ListIterator<Columbus.Csharp.Asg.Nodes.Structure.AccessorDeclarationSyntax>(AccessorCallContainer, fact, true);
            }
        }

        /// <summary>
        /// Gives back iterator for the AccessorCall edges.
        /// </summary>
        /// <returns>Returns an iterator for the AccessorCall edges.</returns>
        public ListIterator<Columbus.Csharp.Asg.Nodes.Structure.AccessorDeclarationSyntax> AccessorCallListIteratorEnd {
            get {
                return new ListIterator<Columbus.Csharp.Asg.Nodes.Structure.AccessorDeclarationSyntax>(AccessorCallContainer, fact, false);
            }
        }

        /// <summary>
        /// Tells whether the node has AccessorCall edges or not.
        /// </summary>
        /// <returns>Returns true if the node has at least one AccessorCall edge.</returns>
        public bool AccessorCallIsEmpty {
            get { return AccessorCallContainer.Count == 0; }
        }

        /// <summary>
        /// Gives back how many AccessorCall edges the node has.
        /// </summary>
        /// <returns>Returns with the number of AccessorCall edges.</returns>
        public uint AccessorCallSize {
            get { return (uint)(AccessorCallContainer.Count); }
        }

        /// <summary>
        /// Gives back the id of the node the Declaration edge points to.
        /// </summary>
        /// <returns>Returns the end point of the m_Declaration edge.</returns>
        /// <exception cref="Columbus.Csharp.Asg.CsharpException">Throws CsharpException if the edge id is invalid.</exception>
        public uint getDeclaration() {
            if (fact.getIsFiltered(m_Declaration))
                return 1;
            else
                return m_Declaration;
        }


        // ---------- Edge setter function(s) ----------

        /// <summary>
        /// Adds a new AccessorCall edge to the node and inserts it after the other ones.
        /// </summary>
        /// <param name="node">[in] The end point of the new AccessorCall edge.</param>
        /// <exception cref="Columbus.Csharp.Asg.CsharpException">Throws CsharpException if there is something wrong with the given node.</exception>
        public void addAccessorCall(Columbus.Csharp.Asg.Nodes.Structure.AccessorDeclarationSyntax node) {
            addAccessorCall(node.Id);
        }

        /// <summary>
        /// Adds a new AccessorCall edge to the node and inserts it after the other ones.
        /// </summary>
        /// <param name="nodeId">[in] The end point of the new AccessorCall edge.</param>
        /// <exception cref="Columbus.Csharp.Asg.CsharpException">Throws CsharpException if the given nodeId is invalid.</exception>
        public void addAccessorCall(uint nodeId) {
            if (!fact.getExist(nodeId))
                throw new CsharpException("Columbus.Csharp.Asg.Nodes.Expression.IdentifierNameSyntax.addAccessorCall(NodeId)", "The end point of the edge does not exist.");
            Columbus.Csharp.Asg.Nodes.Base.Base node = fact.getRef(nodeId);
            if (Common.getIsBaseClassKind(node.NodeKind, Types.NodeKind.ndkAccessorDeclarationSyntax)) {
                AccessorCallContainer.AddLast(nodeId);
            } else {
                throw new CsharpException("Columbus.Csharp.Asg.Nodes.Expression.IdentifierNameSyntax.setAccessorCall(NodeId)", "Invalid NodeKind (" + node.NodeKind.ToString() + ").");
            }
            if (fact.ReverseEdges != null)
              fact.ReverseEdges.insertEdge(nodeId, this.Id, Types.EdgeKind.edkIdentifierNameSyntax_AccessorCall);
        }

        /// <summary>
        /// Sets the Declaration edge.
        /// </summary>
        /// <param name="nodeId">[in] The new end point of the Declaration edge or 0. With 0 the edge can be deleted.</param>
        /// <exception cref="Columbus.Csharp.Asg.CsharpException">Throws CsharpException if the nodeId is invalid.</exception>
        public void setDeclaration(uint nodeId) {
            if (nodeId != 0) {
                if (!fact.getExist(nodeId))
                    throw new CsharpException("Columbus.Csharp.Asg.Nodes.Expression.IdentifierNameSyntax.setDeclaration(NodeId)", "The end point of the edge does not exist.");

                Columbus.Csharp.Asg.Nodes.Base.Base node = fact.getRef(nodeId);
                if (Common.getIsBaseClassKind(node.NodeKind, Types.NodeKind.ndkPositioned)) {
                    if (m_Declaration != 0) {
                    }
                    m_Declaration = nodeId;
                } else {
                    throw new CsharpException("Columbus.Csharp.Asg.Nodes.Expression.IdentifierNameSyntax.setDeclaration(NodeId)", "Invalid NodeKind (" + node.NodeKind.ToString() + ").");
                }
            } else {
                if (m_Declaration != 0) {
                }
                m_Declaration = 0;
            }
        }

        /// <summary>
        /// Sets the Declaration edge.
        /// </summary>
        /// <param name="node">[in] The new end point of the Declaration edge.</param>
        /// <exception cref="Columbus.Csharp.Asg.CsharpException">Throws CsharpException if there's something wrong with the given node.</exception>
        public void setDeclaration(Columbus.Csharp.Asg.Nodes.Base.Positioned node) {
            if (m_Declaration != 0) {
            }
            m_Declaration = node.Id;
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

            io.writeUInt4(m_Declaration);


            foreach (var AccessorCall in AccessorCallContainer) {
              io.writeUInt4(AccessorCall);
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

            m_Declaration =  binIo.readUInt4();

            uint _id;

            _id = binIo.readUInt4();
            while (_id != 0) {
              AccessorCallContainer.AddLast(_id);
              _id = binIo.readUInt4();
            }
        }

    }

}
