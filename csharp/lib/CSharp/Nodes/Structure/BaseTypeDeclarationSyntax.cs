using System;
using System.Text;
using System.Diagnostics;
using System.Collections.Generic;

namespace Columbus.Csharp.Asg.Nodes.Structure {

    /// <summary>
    /// BaseTypeDeclarationSyntax class, which represents the structure::BaseTypeDeclarationSyntax node.
    /// </summary>
    [DebuggerDisplay("Id={Id}, Identifier=\"{Identifier}\"")]
#if (CSHARP_INTERNAL)
    internal
#else
    public
#endif
    class BaseTypeDeclarationSyntax : MemberDeclarationSyntax {

        /// <summary>The Key of the `identifier`.</summary>
        protected uint m_identifier;


        // ---------- Edges ----------

        /// <summary>Container stores the id of the nodes the AttributeLists edge points to.</summary>
        protected LinkedList<uint> AttributeListsContainer;

        /// <summary>The id of the node the BaseList edge points to.</summary>
        protected uint m_BaseList;

        /// <summary>
        /// Constructor, only factory can instantiates nodes.
        /// </summary>
        /// <param name="nodeId">[in] The id of the node.</param>
        /// <param name="factory">[in] Poiter to the Factory the node belongs to.</param>
        public BaseTypeDeclarationSyntax(uint nodeId, Factory factory) : base(nodeId, factory) {
            m_identifier = 0;
            AttributeListsContainer = new LinkedList<uint>();
            m_BaseList = 0;
        }

        /// <summary>
        /// Gives back the NodeKind of the node.
        /// </summary>
        /// <returns>Returns with the NodeKind.</returns>
        public override Types.NodeKind NodeKind {
            get { return Types.NodeKind.ndkBaseTypeDeclarationSyntax; }
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
                case "AttributeLists":
                    return AttributeListsListIteratorBegin.Convert<Columbus.Csharp.Asg.Nodes.Base.Base>();
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
                case "AttributeLists":
                    addAttributeLists(nodeId);
                    return;
                default:
                    base.add(edge, nodeId);
                    return;
            }
        }


        // ---------- Edge getter function(s) ----------

        /// <summary>
        /// Gives back iterator for the AttributeLists edges.
        /// </summary>
        /// <returns>Returns an iterator for the AttributeLists edges.</returns>
        public ListIterator<Columbus.Csharp.Asg.Nodes.Structure.AttributeListSyntax> AttributeListsListIteratorBegin {
            get {
                return new ListIterator<Columbus.Csharp.Asg.Nodes.Structure.AttributeListSyntax>(AttributeListsContainer, fact, true);
            }
        }

        /// <summary>
        /// Gives back iterator for the AttributeLists edges.
        /// </summary>
        /// <returns>Returns an iterator for the AttributeLists edges.</returns>
        public ListIterator<Columbus.Csharp.Asg.Nodes.Structure.AttributeListSyntax> AttributeListsListIteratorEnd {
            get {
                return new ListIterator<Columbus.Csharp.Asg.Nodes.Structure.AttributeListSyntax>(AttributeListsContainer, fact, false);
            }
        }

        /// <summary>
        /// Tells whether the node has AttributeLists edges or not.
        /// </summary>
        /// <returns>Returns true if the node has at least one AttributeLists edge.</returns>
        public bool AttributeListsIsEmpty {
            get { return AttributeListsContainer.Count == 0; }
        }

        /// <summary>
        /// Gives back how many AttributeLists edges the node has.
        /// </summary>
        /// <returns>Returns with the number of AttributeLists edges.</returns>
        public uint AttributeListsSize {
            get { return (uint)(AttributeListsContainer.Count); }
        }

        /// <summary>
        /// Gives back the id of the node the BaseList edge points to.
        /// </summary>
        /// <returns>Returns the end point of the m_BaseList edge.</returns>
        /// <exception cref="Columbus.Csharp.Asg.CsharpException">Throws CsharpException if the edge id is invalid.</exception>
        public uint getBaseList() {
            if (fact.getIsFiltered(m_BaseList))
                return 1;
            else
                return m_BaseList;
        }


        // ---------- Edge setter function(s) ----------

        /// <summary>
        /// Adds a new AttributeLists edge to the node and inserts it after the other ones.
        /// </summary>
        /// <param name="node">[in] The end point of the new AttributeLists edge.</param>
        /// <exception cref="Columbus.Csharp.Asg.CsharpException">Throws CsharpException if there is something wrong with the given node.</exception>
        public void addAttributeLists(Columbus.Csharp.Asg.Nodes.Structure.AttributeListSyntax node) {
            addAttributeLists(node.Id);
        }

        /// <summary>
        /// Adds a new AttributeLists edge to the node and inserts it after the other ones.
        /// </summary>
        /// <param name="nodeId">[in] The end point of the new AttributeLists edge.</param>
        /// <exception cref="Columbus.Csharp.Asg.CsharpException">Throws CsharpException if the given nodeId is invalid.</exception>
        public void addAttributeLists(uint nodeId) {
            if (!fact.getExist(nodeId))
                throw new CsharpException("Columbus.Csharp.Asg.Nodes.Structure.BaseTypeDeclarationSyntax.addAttributeLists(NodeId)", "The end point of the edge does not exist.");
            Columbus.Csharp.Asg.Nodes.Base.Base node = fact.getRef(nodeId);
            if (Common.getIsBaseClassKind(node.NodeKind, Types.NodeKind.ndkAttributeListSyntax)) {
                AttributeListsContainer.AddLast(nodeId);
            } else {
                throw new CsharpException("Columbus.Csharp.Asg.Nodes.Structure.BaseTypeDeclarationSyntax.setAttributeLists(NodeId)", "Invalid NodeKind (" + node.NodeKind.ToString() + ").");
            }
           setParentEdge(nodeId, (uint)Types.EdgeKind.edkBaseTypeDeclarationSyntax_AttributeLists);
            if (fact.ReverseEdges != null)
              fact.ReverseEdges.insertEdge(nodeId, this.Id, Types.EdgeKind.edkBaseTypeDeclarationSyntax_AttributeLists);
        }

        /// <summary>
        /// Sets the BaseList edge.
        /// </summary>
        /// <param name="nodeId">[in] The new end point of the BaseList edge or 0. With 0 the edge can be deleted.</param>
        /// <exception cref="Columbus.Csharp.Asg.CsharpException">Throws CsharpException if the nodeId is invalid.</exception>
        public void setBaseList(uint nodeId) {
            if (nodeId != 0) {
                if (!fact.getExist(nodeId))
                    throw new CsharpException("Columbus.Csharp.Asg.Nodes.Structure.BaseTypeDeclarationSyntax.setBaseList(NodeId)", "The end point of the edge does not exist.");

                Columbus.Csharp.Asg.Nodes.Base.Base node = fact.getRef(nodeId);
                if (Common.getIsBaseClassKind(node.NodeKind, Types.NodeKind.ndkBaseListSyntax)) {
                    if (m_BaseList != 0) {
                        removeParentEdge(m_BaseList);
                    }
                    m_BaseList = nodeId;
                    setParentEdge(m_BaseList, (uint)Types.EdgeKind.edkBaseTypeDeclarationSyntax_BaseList);
                } else {
                    throw new CsharpException("Columbus.Csharp.Asg.Nodes.Structure.BaseTypeDeclarationSyntax.setBaseList(NodeId)", "Invalid NodeKind (" + node.NodeKind.ToString() + ").");
                }
            } else {
                if (m_BaseList != 0) {
                    removeParentEdge(m_BaseList);
                }
                m_BaseList = 0;
            }
        }

        /// <summary>
        /// Sets the BaseList edge.
        /// </summary>
        /// <param name="node">[in] The new end point of the BaseList edge.</param>
        /// <exception cref="Columbus.Csharp.Asg.CsharpException">Throws CsharpException if there's something wrong with the given node.</exception>
        public void setBaseList(Columbus.Csharp.Asg.Nodes.Structure.BaseListSyntax node) {
            if (m_BaseList != 0) {
                removeParentEdge(m_BaseList);
            }
            m_BaseList = node.Id;
            setParentEdge(m_BaseList, (uint)Types.EdgeKind.edkBaseTypeDeclarationSyntax_BaseList);
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

            io.writeUInt4(m_BaseList);


            foreach (var AttributeLists in AttributeListsContainer) {
              io.writeUInt4(AttributeLists);
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

            m_BaseList =  binIo.readUInt4();
            if (m_BaseList != 0)
              setParentEdge(m_BaseList,(uint)Types.EdgeKind.edkBaseTypeDeclarationSyntax_BaseList);

            uint _id;

            _id = binIo.readUInt4();
            while (_id != 0) {
              AttributeListsContainer.AddLast(_id);
              setParentEdge(_id, (uint)Types.EdgeKind.edkBaseTypeDeclarationSyntax_AttributeLists);
              _id = binIo.readUInt4();
            }
        }

    }

}
