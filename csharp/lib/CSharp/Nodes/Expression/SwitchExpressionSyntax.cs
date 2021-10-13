using System;
using System.Text;
using System.Diagnostics;
using System.Collections.Generic;

namespace Columbus.Csharp.Asg.Nodes.Expression {

    /// <summary>
    /// SwitchExpressionSyntax class, which represents the expression::SwitchExpressionSyntax node.
    /// </summary>
    [DebuggerDisplay("Id={Id}")]
#if (CSHARP_INTERNAL)
    internal
#else
    public
#endif
    class SwitchExpressionSyntax : ExpressionSyntax {


        // ---------- Edges ----------

        /// <summary>Container stores the id of the nodes the Arms edge points to.</summary>
        protected LinkedList<uint> ArmsContainer;

        /// <summary>The id of the node the GoverningExpression edge points to.</summary>
        protected uint m_GoverningExpression;

        /// <summary>
        /// Constructor, only factory can instantiates nodes.
        /// </summary>
        /// <param name="nodeId">[in] The id of the node.</param>
        /// <param name="factory">[in] Poiter to the Factory the node belongs to.</param>
        public SwitchExpressionSyntax(uint nodeId, Factory factory) : base(nodeId, factory) {
            ArmsContainer = new LinkedList<uint>();
            m_GoverningExpression = 0;
        }

        /// <summary>
        /// Gives back the NodeKind of the node.
        /// </summary>
        /// <returns>Returns with the NodeKind.</returns>
        public override Types.NodeKind NodeKind {
            get { return Types.NodeKind.ndkSwitchExpressionSyntax; }
        }


        // ---------- Reflection getter function ----------

        /// <summary>
        /// Gives back the begin iterator for the edge specified
        /// </summary>
        /// <param name="edge">[in] The multiple edge for which the iterator is requested</param>
        public override ListIterator<Columbus.Csharp.Asg.Nodes.Base.Base> GetListIteratorBegin(string edge) {
            switch(edge) {
                case "Arms":
                    return ArmsListIteratorBegin.Convert<Columbus.Csharp.Asg.Nodes.Base.Base>();
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
                case "Arms":
                    addArms(nodeId);
                    return;
                default:
                    base.add(edge, nodeId);
                    return;
            }
        }


        // ---------- Edge getter function(s) ----------

        /// <summary>
        /// Gives back iterator for the Arms edges.
        /// </summary>
        /// <returns>Returns an iterator for the Arms edges.</returns>
        public ListIterator<Columbus.Csharp.Asg.Nodes.Structure.SwitchExpressionArmSyntax> ArmsListIteratorBegin {
            get {
                return new ListIterator<Columbus.Csharp.Asg.Nodes.Structure.SwitchExpressionArmSyntax>(ArmsContainer, fact, true);
            }
        }

        /// <summary>
        /// Gives back iterator for the Arms edges.
        /// </summary>
        /// <returns>Returns an iterator for the Arms edges.</returns>
        public ListIterator<Columbus.Csharp.Asg.Nodes.Structure.SwitchExpressionArmSyntax> ArmsListIteratorEnd {
            get {
                return new ListIterator<Columbus.Csharp.Asg.Nodes.Structure.SwitchExpressionArmSyntax>(ArmsContainer, fact, false);
            }
        }

        /// <summary>
        /// Tells whether the node has Arms edges or not.
        /// </summary>
        /// <returns>Returns true if the node has at least one Arms edge.</returns>
        public bool ArmsIsEmpty {
            get { return ArmsContainer.Count == 0; }
        }

        /// <summary>
        /// Gives back how many Arms edges the node has.
        /// </summary>
        /// <returns>Returns with the number of Arms edges.</returns>
        public uint ArmsSize {
            get { return (uint)(ArmsContainer.Count); }
        }

        /// <summary>
        /// Gives back the id of the node the GoverningExpression edge points to.
        /// </summary>
        /// <returns>Returns the end point of the m_GoverningExpression edge.</returns>
        /// <exception cref="Columbus.Csharp.Asg.CsharpException">Throws CsharpException if the edge id is invalid.</exception>
        public uint getGoverningExpression() {
            if (fact.getIsFiltered(m_GoverningExpression))
                return 1;
            else
                return m_GoverningExpression;
        }


        // ---------- Edge setter function(s) ----------

        /// <summary>
        /// Adds a new Arms edge to the node and inserts it after the other ones.
        /// </summary>
        /// <param name="node">[in] The end point of the new Arms edge.</param>
        /// <exception cref="Columbus.Csharp.Asg.CsharpException">Throws CsharpException if there is something wrong with the given node.</exception>
        public void addArms(Columbus.Csharp.Asg.Nodes.Structure.SwitchExpressionArmSyntax node) {
            addArms(node.Id);
        }

        /// <summary>
        /// Adds a new Arms edge to the node and inserts it after the other ones.
        /// </summary>
        /// <param name="nodeId">[in] The end point of the new Arms edge.</param>
        /// <exception cref="Columbus.Csharp.Asg.CsharpException">Throws CsharpException if the given nodeId is invalid.</exception>
        public void addArms(uint nodeId) {
            if (!fact.getExist(nodeId))
                throw new CsharpException("Columbus.Csharp.Asg.Nodes.Expression.SwitchExpressionSyntax.addArms(NodeId)", "The end point of the edge does not exist.");
            Columbus.Csharp.Asg.Nodes.Base.Base node = fact.getRef(nodeId);
            if (Common.getIsBaseClassKind(node.NodeKind, Types.NodeKind.ndkSwitchExpressionArmSyntax)) {
                ArmsContainer.AddLast(nodeId);
            } else {
                throw new CsharpException("Columbus.Csharp.Asg.Nodes.Expression.SwitchExpressionSyntax.setArms(NodeId)", "Invalid NodeKind (" + node.NodeKind.ToString() + ").");
            }
           setParentEdge(nodeId, (uint)Types.EdgeKind.edkSwitchExpressionSyntax_Arms);
            if (fact.ReverseEdges != null)
              fact.ReverseEdges.insertEdge(nodeId, this.Id, Types.EdgeKind.edkSwitchExpressionSyntax_Arms);
        }

        /// <summary>
        /// Sets the GoverningExpression edge.
        /// </summary>
        /// <param name="nodeId">[in] The new end point of the GoverningExpression edge or 0. With 0 the edge can be deleted.</param>
        /// <exception cref="Columbus.Csharp.Asg.CsharpException">Throws CsharpException if the nodeId is invalid.</exception>
        public void setGoverningExpression(uint nodeId) {
            if (nodeId != 0) {
                if (!fact.getExist(nodeId))
                    throw new CsharpException("Columbus.Csharp.Asg.Nodes.Expression.SwitchExpressionSyntax.setGoverningExpression(NodeId)", "The end point of the edge does not exist.");

                Columbus.Csharp.Asg.Nodes.Base.Base node = fact.getRef(nodeId);
                if (Common.getIsBaseClassKind(node.NodeKind, Types.NodeKind.ndkExpressionSyntax)) {
                    if (m_GoverningExpression != 0) {
                        removeParentEdge(m_GoverningExpression);
                    }
                    m_GoverningExpression = nodeId;
                    setParentEdge(m_GoverningExpression, (uint)Types.EdgeKind.edkSwitchExpressionSyntax_GoverningExpression);
                } else {
                    throw new CsharpException("Columbus.Csharp.Asg.Nodes.Expression.SwitchExpressionSyntax.setGoverningExpression(NodeId)", "Invalid NodeKind (" + node.NodeKind.ToString() + ").");
                }
            } else {
                if (m_GoverningExpression != 0) {
                    removeParentEdge(m_GoverningExpression);
                }
                m_GoverningExpression = 0;
            }
        }

        /// <summary>
        /// Sets the GoverningExpression edge.
        /// </summary>
        /// <param name="node">[in] The new end point of the GoverningExpression edge.</param>
        /// <exception cref="Columbus.Csharp.Asg.CsharpException">Throws CsharpException if there's something wrong with the given node.</exception>
        public void setGoverningExpression(Columbus.Csharp.Asg.Nodes.Expression.ExpressionSyntax node) {
            if (m_GoverningExpression != 0) {
                removeParentEdge(m_GoverningExpression);
            }
            m_GoverningExpression = node.Id;
            setParentEdge(m_GoverningExpression, (uint)Types.EdgeKind.edkSwitchExpressionSyntax_GoverningExpression);
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

            io.writeUInt4(m_GoverningExpression);


            foreach (var Arms in ArmsContainer) {
              io.writeUInt4(Arms);
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

            m_GoverningExpression =  binIo.readUInt4();
            if (m_GoverningExpression != 0)
              setParentEdge(m_GoverningExpression,(uint)Types.EdgeKind.edkSwitchExpressionSyntax_GoverningExpression);

            uint _id;

            _id = binIo.readUInt4();
            while (_id != 0) {
              ArmsContainer.AddLast(_id);
              setParentEdge(_id, (uint)Types.EdgeKind.edkSwitchExpressionSyntax_Arms);
              _id = binIo.readUInt4();
            }
        }

    }

}
