using System;
using System.Text;
using System.Diagnostics;
using System.Collections.Generic;

namespace Columbus.Csharp.Asg.Nodes.Structure {

    /// <summary>
    /// PositionalPatternClauseSyntax class, which represents the structure::PositionalPatternClauseSyntax node.
    /// </summary>
    [DebuggerDisplay("Id={Id}")]
#if (CSHARP_INTERNAL)
    internal
#else
    public
#endif
    class PositionalPatternClauseSyntax : Columbus.Csharp.Asg.Nodes.Base.Positioned {


        // ---------- Edges ----------

        /// <summary>Container stores the id of the nodes the Subpatterns edge points to.</summary>
        protected LinkedList<uint> SubpatternsContainer;

        /// <summary>
        /// Constructor, only factory can instantiates nodes.
        /// </summary>
        /// <param name="nodeId">[in] The id of the node.</param>
        /// <param name="factory">[in] Poiter to the Factory the node belongs to.</param>
        public PositionalPatternClauseSyntax(uint nodeId, Factory factory) : base(nodeId, factory) {
            SubpatternsContainer = new LinkedList<uint>();
        }

        /// <summary>
        /// Gives back the NodeKind of the node.
        /// </summary>
        /// <returns>Returns with the NodeKind.</returns>
        public override Types.NodeKind NodeKind {
            get { return Types.NodeKind.ndkPositionalPatternClauseSyntax; }
        }


        // ---------- Reflection getter function ----------

        /// <summary>
        /// Gives back the begin iterator for the edge specified
        /// </summary>
        /// <param name="edge">[in] The multiple edge for which the iterator is requested</param>
        public override ListIterator<Columbus.Csharp.Asg.Nodes.Base.Base> GetListIteratorBegin(string edge) {
            switch(edge) {
                case "Subpatterns":
                    return SubpatternsListIteratorBegin.Convert<Columbus.Csharp.Asg.Nodes.Base.Base>();
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
                case "Subpatterns":
                    addSubpatterns(nodeId);
                    return;
                default:
                    base.add(edge, nodeId);
                    return;
            }
        }


        // ---------- Edge getter function(s) ----------

        /// <summary>
        /// Gives back iterator for the Subpatterns edges.
        /// </summary>
        /// <returns>Returns an iterator for the Subpatterns edges.</returns>
        public ListIterator<Columbus.Csharp.Asg.Nodes.Structure.SubpatternSyntax> SubpatternsListIteratorBegin {
            get {
                return new ListIterator<Columbus.Csharp.Asg.Nodes.Structure.SubpatternSyntax>(SubpatternsContainer, fact, true);
            }
        }

        /// <summary>
        /// Gives back iterator for the Subpatterns edges.
        /// </summary>
        /// <returns>Returns an iterator for the Subpatterns edges.</returns>
        public ListIterator<Columbus.Csharp.Asg.Nodes.Structure.SubpatternSyntax> SubpatternsListIteratorEnd {
            get {
                return new ListIterator<Columbus.Csharp.Asg.Nodes.Structure.SubpatternSyntax>(SubpatternsContainer, fact, false);
            }
        }

        /// <summary>
        /// Tells whether the node has Subpatterns edges or not.
        /// </summary>
        /// <returns>Returns true if the node has at least one Subpatterns edge.</returns>
        public bool SubpatternsIsEmpty {
            get { return SubpatternsContainer.Count == 0; }
        }

        /// <summary>
        /// Gives back how many Subpatterns edges the node has.
        /// </summary>
        /// <returns>Returns with the number of Subpatterns edges.</returns>
        public uint SubpatternsSize {
            get { return (uint)(SubpatternsContainer.Count); }
        }


        // ---------- Edge setter function(s) ----------

        /// <summary>
        /// Adds a new Subpatterns edge to the node and inserts it after the other ones.
        /// </summary>
        /// <param name="node">[in] The end point of the new Subpatterns edge.</param>
        /// <exception cref="Columbus.Csharp.Asg.CsharpException">Throws CsharpException if there is something wrong with the given node.</exception>
        public void addSubpatterns(Columbus.Csharp.Asg.Nodes.Structure.SubpatternSyntax node) {
            addSubpatterns(node.Id);
        }

        /// <summary>
        /// Adds a new Subpatterns edge to the node and inserts it after the other ones.
        /// </summary>
        /// <param name="nodeId">[in] The end point of the new Subpatterns edge.</param>
        /// <exception cref="Columbus.Csharp.Asg.CsharpException">Throws CsharpException if the given nodeId is invalid.</exception>
        public void addSubpatterns(uint nodeId) {
            if (!fact.getExist(nodeId))
                throw new CsharpException("Columbus.Csharp.Asg.Nodes.Structure.PositionalPatternClauseSyntax.addSubpatterns(NodeId)", "The end point of the edge does not exist.");
            Columbus.Csharp.Asg.Nodes.Base.Base node = fact.getRef(nodeId);
            if (Common.getIsBaseClassKind(node.NodeKind, Types.NodeKind.ndkSubpatternSyntax)) {
                SubpatternsContainer.AddLast(nodeId);
            } else {
                throw new CsharpException("Columbus.Csharp.Asg.Nodes.Structure.PositionalPatternClauseSyntax.setSubpatterns(NodeId)", "Invalid NodeKind (" + node.NodeKind.ToString() + ").");
            }
           setParentEdge(nodeId, (uint)Types.EdgeKind.edkPositionalPatternClauseSyntax_Subpatterns);
            if (fact.ReverseEdges != null)
              fact.ReverseEdges.insertEdge(nodeId, this.Id, Types.EdgeKind.edkPositionalPatternClauseSyntax_Subpatterns);
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


            foreach (var Subpatterns in SubpatternsContainer) {
              io.writeUInt4(Subpatterns);
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
              SubpatternsContainer.AddLast(_id);
              setParentEdge(_id, (uint)Types.EdgeKind.edkPositionalPatternClauseSyntax_Subpatterns);
              _id = binIo.readUInt4();
            }
        }

    }

}
