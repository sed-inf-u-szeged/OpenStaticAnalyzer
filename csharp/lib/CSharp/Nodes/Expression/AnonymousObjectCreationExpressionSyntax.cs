using System;
using System.Text;
using System.Diagnostics;
using System.Collections.Generic;

namespace Columbus.Csharp.Asg.Nodes.Expression {

    /// <summary>
    /// AnonymousObjectCreationExpressionSyntax class, which represents the expression::AnonymousObjectCreationExpressionSyntax node.
    /// </summary>
    [DebuggerDisplay("Id={Id}, Identifier=\"{Identifier}\"")]
#if (CSHARP_INTERNAL)
    internal
#else
    public
#endif
    class AnonymousObjectCreationExpressionSyntax : ExpressionSyntax {

        /// <summary>The Key of the `identifier`.</summary>
        protected uint m_identifier;


        // ---------- Edges ----------

        /// <summary>Container stores the id of the nodes the Initializers edge points to.</summary>
        protected LinkedList<uint> InitializersContainer;

        /// <summary>
        /// Constructor, only factory can instantiates nodes.
        /// </summary>
        /// <param name="nodeId">[in] The id of the node.</param>
        /// <param name="factory">[in] Poiter to the Factory the node belongs to.</param>
        public AnonymousObjectCreationExpressionSyntax(uint nodeId, Factory factory) : base(nodeId, factory) {
            m_identifier = 0;
            InitializersContainer = new LinkedList<uint>();
        }

        /// <summary>
        /// Gives back the NodeKind of the node.
        /// </summary>
        /// <returns>Returns with the NodeKind.</returns>
        public override Types.NodeKind NodeKind {
            get { return Types.NodeKind.ndkAnonymousObjectCreationExpressionSyntax; }
        }


        // ---------- Attribute propert(y)(ies) ----------

        /// <summary>
        /// Gives back or sets the identifier of the node.
        /// </summary>
        public string Identifier
        {
            get
            {
                return fact.StringTable.get(m_identifier);
            }
            set
            {
                m_identifier = fact.StringTable.set( value );
            }
        }

        /// <summary>
        /// Gives back or sets the Key of identifier of the node.
        /// </summary>
        public uint IdentifierKey
        {
            get
            {
                return m_identifier;
            }
            set
            {
               m_identifier = value;
            }
        }


        // ---------- Reflection getter function ----------

        /// <summary>
        /// Gives back the begin iterator for the edge specified
        /// </summary>
        /// <param name="edge">[in] The multiple edge for which the iterator is requested</param>
        public override ListIterator<Columbus.Csharp.Asg.Nodes.Base.Base> GetListIteratorBegin(string edge) {
            switch(edge) {
                case "Initializers":
                    return InitializersListIteratorBegin.Convert<Columbus.Csharp.Asg.Nodes.Base.Base>();
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
                case "Initializers":
                    addInitializers(nodeId);
                    return;
                default:
                    base.add(edge, nodeId);
                    return;
            }
        }


        // ---------- Edge getter function(s) ----------

        /// <summary>
        /// Gives back iterator for the Initializers edges.
        /// </summary>
        /// <returns>Returns an iterator for the Initializers edges.</returns>
        public ListIterator<Columbus.Csharp.Asg.Nodes.Structure.AnonymousObjectMemberDeclaratorSyntax> InitializersListIteratorBegin {
            get {
                return new ListIterator<Columbus.Csharp.Asg.Nodes.Structure.AnonymousObjectMemberDeclaratorSyntax>(InitializersContainer, fact, true);
            }
        }

        /// <summary>
        /// Gives back iterator for the Initializers edges.
        /// </summary>
        /// <returns>Returns an iterator for the Initializers edges.</returns>
        public ListIterator<Columbus.Csharp.Asg.Nodes.Structure.AnonymousObjectMemberDeclaratorSyntax> InitializersListIteratorEnd {
            get {
                return new ListIterator<Columbus.Csharp.Asg.Nodes.Structure.AnonymousObjectMemberDeclaratorSyntax>(InitializersContainer, fact, false);
            }
        }

        /// <summary>
        /// Tells whether the node has Initializers edges or not.
        /// </summary>
        /// <returns>Returns true if the node has at least one Initializers edge.</returns>
        public bool InitializersIsEmpty {
            get { return InitializersContainer.Count == 0; }
        }

        /// <summary>
        /// Gives back how many Initializers edges the node has.
        /// </summary>
        /// <returns>Returns with the number of Initializers edges.</returns>
        public uint InitializersSize {
            get { return (uint)(InitializersContainer.Count); }
        }


        // ---------- Edge setter function(s) ----------

        /// <summary>
        /// Adds a new Initializers edge to the node and inserts it after the other ones.
        /// </summary>
        /// <param name="node">[in] The end point of the new Initializers edge.</param>
        /// <exception cref="Columbus.Csharp.Asg.CsharpException">Throws CsharpException if there is something wrong with the given node.</exception>
        public void addInitializers(Columbus.Csharp.Asg.Nodes.Structure.AnonymousObjectMemberDeclaratorSyntax node) {
            addInitializers(node.Id);
        }

        /// <summary>
        /// Adds a new Initializers edge to the node and inserts it after the other ones.
        /// </summary>
        /// <param name="nodeId">[in] The end point of the new Initializers edge.</param>
        /// <exception cref="Columbus.Csharp.Asg.CsharpException">Throws CsharpException if the given nodeId is invalid.</exception>
        public void addInitializers(uint nodeId) {
            if (!fact.getExist(nodeId))
                throw new CsharpException("Columbus.Csharp.Asg.Nodes.Expression.AnonymousObjectCreationExpressionSyntax.addInitializers(NodeId)", "The end point of the edge does not exist.");
            Columbus.Csharp.Asg.Nodes.Base.Base node = fact.getRef(nodeId);
            if (Common.getIsBaseClassKind(node.NodeKind, Types.NodeKind.ndkAnonymousObjectMemberDeclaratorSyntax)) {
                InitializersContainer.AddLast(nodeId);
            } else {
                throw new CsharpException("Columbus.Csharp.Asg.Nodes.Expression.AnonymousObjectCreationExpressionSyntax.setInitializers(NodeId)", "Invalid NodeKind (" + node.NodeKind.ToString() + ").");
            }
           setParentEdge(nodeId, (uint)Types.EdgeKind.edkAnonymousObjectCreationExpressionSyntax_Initializers);
            if (fact.ReverseEdges != null)
              fact.ReverseEdges.insertEdge(nodeId, this.Id, Types.EdgeKind.edkAnonymousObjectCreationExpressionSyntax_Initializers);
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

            fact.StringTable.setType(m_identifier, StrTable.StrType.strToSave);
            io.writeUInt4(m_identifier);


            foreach (var Initializers in InitializersContainer) {
              io.writeUInt4(Initializers);
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

            m_identifier = binIo.readUInt4();

            uint _id;

            _id = binIo.readUInt4();
            while (_id != 0) {
              InitializersContainer.AddLast(_id);
              setParentEdge(_id, (uint)Types.EdgeKind.edkAnonymousObjectCreationExpressionSyntax_Initializers);
              _id = binIo.readUInt4();
            }
        }

    }

}
