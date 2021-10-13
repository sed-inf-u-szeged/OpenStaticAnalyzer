using System;
using System.Text;
using System.Diagnostics;
using System.Collections.Generic;

namespace Columbus.Csharp.Asg.Nodes.Structure {

    /// <summary>
    /// VariableDeclarationSyntax class, which represents the structure::VariableDeclarationSyntax node.
    /// </summary>
    [DebuggerDisplay("Id={Id}")]
#if (CSHARP_INTERNAL)
    internal
#else
    public
#endif
    class VariableDeclarationSyntax : Columbus.Csharp.Asg.Nodes.Base.Positioned {


        // ---------- Edges ----------

        /// <summary>The id of the node the Type edge points to.</summary>
        protected uint m_Type;

        /// <summary>Container stores the id of the nodes the Variables edge points to.</summary>
        protected LinkedList<uint> VariablesContainer;

        /// <summary>
        /// Constructor, only factory can instantiates nodes.
        /// </summary>
        /// <param name="nodeId">[in] The id of the node.</param>
        /// <param name="factory">[in] Poiter to the Factory the node belongs to.</param>
        public VariableDeclarationSyntax(uint nodeId, Factory factory) : base(nodeId, factory) {
            m_Type = 0;
            VariablesContainer = new LinkedList<uint>();
        }

        /// <summary>
        /// Gives back the NodeKind of the node.
        /// </summary>
        /// <returns>Returns with the NodeKind.</returns>
        public override Types.NodeKind NodeKind {
            get { return Types.NodeKind.ndkVariableDeclarationSyntax; }
        }


        // ---------- Reflection getter function ----------

        /// <summary>
        /// Gives back the begin iterator for the edge specified
        /// </summary>
        /// <param name="edge">[in] The multiple edge for which the iterator is requested</param>
        public override ListIterator<Columbus.Csharp.Asg.Nodes.Base.Base> GetListIteratorBegin(string edge) {
            switch(edge) {
                case "Variables":
                    return VariablesListIteratorBegin.Convert<Columbus.Csharp.Asg.Nodes.Base.Base>();
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
                case "Variables":
                    addVariables(nodeId);
                    return;
                default:
                    base.add(edge, nodeId);
                    return;
            }
        }


        // ---------- Edge getter function(s) ----------

        /// <summary>
        /// Gives back the id of the node the Type edge points to.
        /// </summary>
        /// <returns>Returns the end point of the m_Type edge.</returns>
        /// <exception cref="Columbus.Csharp.Asg.CsharpException">Throws CsharpException if the edge id is invalid.</exception>
        public uint getType() {
            if (fact.getIsFiltered(m_Type))
                return 1;
            else
                return m_Type;
        }

        /// <summary>
        /// Gives back iterator for the Variables edges.
        /// </summary>
        /// <returns>Returns an iterator for the Variables edges.</returns>
        public ListIterator<Columbus.Csharp.Asg.Nodes.Structure.VariableDeclaratorSyntax> VariablesListIteratorBegin {
            get {
                return new ListIterator<Columbus.Csharp.Asg.Nodes.Structure.VariableDeclaratorSyntax>(VariablesContainer, fact, true);
            }
        }

        /// <summary>
        /// Gives back iterator for the Variables edges.
        /// </summary>
        /// <returns>Returns an iterator for the Variables edges.</returns>
        public ListIterator<Columbus.Csharp.Asg.Nodes.Structure.VariableDeclaratorSyntax> VariablesListIteratorEnd {
            get {
                return new ListIterator<Columbus.Csharp.Asg.Nodes.Structure.VariableDeclaratorSyntax>(VariablesContainer, fact, false);
            }
        }

        /// <summary>
        /// Tells whether the node has Variables edges or not.
        /// </summary>
        /// <returns>Returns true if the node has at least one Variables edge.</returns>
        public bool VariablesIsEmpty {
            get { return VariablesContainer.Count == 0; }
        }

        /// <summary>
        /// Gives back how many Variables edges the node has.
        /// </summary>
        /// <returns>Returns with the number of Variables edges.</returns>
        public uint VariablesSize {
            get { return (uint)(VariablesContainer.Count); }
        }


        // ---------- Edge setter function(s) ----------

        /// <summary>
        /// Sets the Type edge.
        /// </summary>
        /// <param name="nodeId">[in] The new end point of the Type edge or 0. With 0 the edge can be deleted.</param>
        /// <exception cref="Columbus.Csharp.Asg.CsharpException">Throws CsharpException if the nodeId is invalid.</exception>
        public void setType(uint nodeId) {
            if (nodeId != 0) {
                if (!fact.getExist(nodeId))
                    throw new CsharpException("Columbus.Csharp.Asg.Nodes.Structure.VariableDeclarationSyntax.setType(NodeId)", "The end point of the edge does not exist.");

                Columbus.Csharp.Asg.Nodes.Base.Base node = fact.getRef(nodeId);
                if (Common.getIsBaseClassKind(node.NodeKind, Types.NodeKind.ndkTypeSyntax)) {
                    if (m_Type != 0) {
                        removeParentEdge(m_Type);
                    }
                    m_Type = nodeId;
                    setParentEdge(m_Type, (uint)Types.EdgeKind.edkVariableDeclarationSyntax_Type);
                } else {
                    throw new CsharpException("Columbus.Csharp.Asg.Nodes.Structure.VariableDeclarationSyntax.setType(NodeId)", "Invalid NodeKind (" + node.NodeKind.ToString() + ").");
                }
            } else {
                if (m_Type != 0) {
                    removeParentEdge(m_Type);
                }
                m_Type = 0;
            }
        }

        /// <summary>
        /// Sets the Type edge.
        /// </summary>
        /// <param name="node">[in] The new end point of the Type edge.</param>
        /// <exception cref="Columbus.Csharp.Asg.CsharpException">Throws CsharpException if there's something wrong with the given node.</exception>
        public void setType(Columbus.Csharp.Asg.Nodes.Expression.TypeSyntax node) {
            if (m_Type != 0) {
                removeParentEdge(m_Type);
            }
            m_Type = node.Id;
            setParentEdge(m_Type, (uint)Types.EdgeKind.edkVariableDeclarationSyntax_Type);
        }

        /// <summary>
        /// Adds a new Variables edge to the node and inserts it after the other ones.
        /// </summary>
        /// <param name="node">[in] The end point of the new Variables edge.</param>
        /// <exception cref="Columbus.Csharp.Asg.CsharpException">Throws CsharpException if there is something wrong with the given node.</exception>
        public void addVariables(Columbus.Csharp.Asg.Nodes.Structure.VariableDeclaratorSyntax node) {
            addVariables(node.Id);
        }

        /// <summary>
        /// Adds a new Variables edge to the node and inserts it after the other ones.
        /// </summary>
        /// <param name="nodeId">[in] The end point of the new Variables edge.</param>
        /// <exception cref="Columbus.Csharp.Asg.CsharpException">Throws CsharpException if the given nodeId is invalid.</exception>
        public void addVariables(uint nodeId) {
            if (!fact.getExist(nodeId))
                throw new CsharpException("Columbus.Csharp.Asg.Nodes.Structure.VariableDeclarationSyntax.addVariables(NodeId)", "The end point of the edge does not exist.");
            Columbus.Csharp.Asg.Nodes.Base.Base node = fact.getRef(nodeId);
            if (Common.getIsBaseClassKind(node.NodeKind, Types.NodeKind.ndkVariableDeclaratorSyntax)) {
                VariablesContainer.AddLast(nodeId);
            } else {
                throw new CsharpException("Columbus.Csharp.Asg.Nodes.Structure.VariableDeclarationSyntax.setVariables(NodeId)", "Invalid NodeKind (" + node.NodeKind.ToString() + ").");
            }
           setParentEdge(nodeId, (uint)Types.EdgeKind.edkVariableDeclarationSyntax_Variables);
            if (fact.ReverseEdges != null)
              fact.ReverseEdges.insertEdge(nodeId, this.Id, Types.EdgeKind.edkVariableDeclarationSyntax_Variables);
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

            io.writeUInt4(m_Type);


            foreach (var Variables in VariablesContainer) {
              io.writeUInt4(Variables);
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

            m_Type =  binIo.readUInt4();
            if (m_Type != 0)
              setParentEdge(m_Type,(uint)Types.EdgeKind.edkVariableDeclarationSyntax_Type);

            uint _id;

            _id = binIo.readUInt4();
            while (_id != 0) {
              VariablesContainer.AddLast(_id);
              setParentEdge(_id, (uint)Types.EdgeKind.edkVariableDeclarationSyntax_Variables);
              _id = binIo.readUInt4();
            }
        }

    }

}
