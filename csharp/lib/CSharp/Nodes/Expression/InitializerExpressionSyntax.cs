using System;
using System.Text;
using System.Diagnostics;
using System.Collections.Generic;

namespace Columbus.Csharp.Asg.Nodes.Expression {

    /// <summary>
    /// InitializerExpressionSyntax class, which represents the expression::InitializerExpressionSyntax node.
    /// </summary>
    [DebuggerDisplay("Id={Id}")]
#if (CSHARP_INTERNAL)
    internal
#else
    public
#endif
    class InitializerExpressionSyntax : ExpressionSyntax {


        // ---------- Edges ----------

        /// <summary>Container stores the id of the nodes the Expressions edge points to.</summary>
        protected LinkedList<uint> ExpressionsContainer;

        /// <summary>
        /// Constructor, only factory can instantiates nodes.
        /// </summary>
        /// <param name="nodeId">[in] The id of the node.</param>
        /// <param name="factory">[in] Poiter to the Factory the node belongs to.</param>
        public InitializerExpressionSyntax(uint nodeId, Factory factory) : base(nodeId, factory) {
            ExpressionsContainer = new LinkedList<uint>();
        }

        /// <summary>
        /// Gives back the NodeKind of the node.
        /// </summary>
        /// <returns>Returns with the NodeKind.</returns>
        public override Types.NodeKind NodeKind {
            get { return Types.NodeKind.ndkInitializerExpressionSyntax; }
        }


        // ---------- Reflection getter function ----------

        /// <summary>
        /// Gives back the begin iterator for the edge specified
        /// </summary>
        /// <param name="edge">[in] The multiple edge for which the iterator is requested</param>
        public override ListIterator<Columbus.Csharp.Asg.Nodes.Base.Base> GetListIteratorBegin(string edge) {
            switch(edge) {
                case "Expressions":
                    return ExpressionsListIteratorBegin.Convert<Columbus.Csharp.Asg.Nodes.Base.Base>();
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
                case "Expressions":
                    addExpressions(nodeId);
                    return;
                default:
                    base.add(edge, nodeId);
                    return;
            }
        }


        // ---------- Edge getter function(s) ----------

        /// <summary>
        /// Gives back iterator for the Expressions edges.
        /// </summary>
        /// <returns>Returns an iterator for the Expressions edges.</returns>
        public ListIterator<Columbus.Csharp.Asg.Nodes.Expression.ExpressionSyntax> ExpressionsListIteratorBegin {
            get {
                return new ListIterator<Columbus.Csharp.Asg.Nodes.Expression.ExpressionSyntax>(ExpressionsContainer, fact, true);
            }
        }

        /// <summary>
        /// Gives back iterator for the Expressions edges.
        /// </summary>
        /// <returns>Returns an iterator for the Expressions edges.</returns>
        public ListIterator<Columbus.Csharp.Asg.Nodes.Expression.ExpressionSyntax> ExpressionsListIteratorEnd {
            get {
                return new ListIterator<Columbus.Csharp.Asg.Nodes.Expression.ExpressionSyntax>(ExpressionsContainer, fact, false);
            }
        }

        /// <summary>
        /// Tells whether the node has Expressions edges or not.
        /// </summary>
        /// <returns>Returns true if the node has at least one Expressions edge.</returns>
        public bool ExpressionsIsEmpty {
            get { return ExpressionsContainer.Count == 0; }
        }

        /// <summary>
        /// Gives back how many Expressions edges the node has.
        /// </summary>
        /// <returns>Returns with the number of Expressions edges.</returns>
        public uint ExpressionsSize {
            get { return (uint)(ExpressionsContainer.Count); }
        }


        // ---------- Edge setter function(s) ----------

        /// <summary>
        /// Adds a new Expressions edge to the node and inserts it after the other ones.
        /// </summary>
        /// <param name="node">[in] The end point of the new Expressions edge.</param>
        /// <exception cref="Columbus.Csharp.Asg.CsharpException">Throws CsharpException if there is something wrong with the given node.</exception>
        public void addExpressions(Columbus.Csharp.Asg.Nodes.Expression.ExpressionSyntax node) {
            addExpressions(node.Id);
        }

        /// <summary>
        /// Adds a new Expressions edge to the node and inserts it after the other ones.
        /// </summary>
        /// <param name="nodeId">[in] The end point of the new Expressions edge.</param>
        /// <exception cref="Columbus.Csharp.Asg.CsharpException">Throws CsharpException if the given nodeId is invalid.</exception>
        public void addExpressions(uint nodeId) {
            if (!fact.getExist(nodeId))
                throw new CsharpException("Columbus.Csharp.Asg.Nodes.Expression.InitializerExpressionSyntax.addExpressions(NodeId)", "The end point of the edge does not exist.");
            Columbus.Csharp.Asg.Nodes.Base.Base node = fact.getRef(nodeId);
            if (Common.getIsBaseClassKind(node.NodeKind, Types.NodeKind.ndkExpressionSyntax)) {
                ExpressionsContainer.AddLast(nodeId);
            } else {
                throw new CsharpException("Columbus.Csharp.Asg.Nodes.Expression.InitializerExpressionSyntax.setExpressions(NodeId)", "Invalid NodeKind (" + node.NodeKind.ToString() + ").");
            }
           setParentEdge(nodeId, (uint)Types.EdgeKind.edkInitializerExpressionSyntax_Expressions);
            if (fact.ReverseEdges != null)
              fact.ReverseEdges.insertEdge(nodeId, this.Id, Types.EdgeKind.edkInitializerExpressionSyntax_Expressions);
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


            foreach (var Expressions in ExpressionsContainer) {
              io.writeUInt4(Expressions);
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
              ExpressionsContainer.AddLast(_id);
              setParentEdge(_id, (uint)Types.EdgeKind.edkInitializerExpressionSyntax_Expressions);
              _id = binIo.readUInt4();
            }
        }

    }

}
