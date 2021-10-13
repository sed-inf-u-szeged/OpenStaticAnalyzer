using System;
using System.Text;
using System.Diagnostics;
using System.Collections.Generic;

namespace Columbus.Csharp.Asg.Nodes.Structure {

    /// <summary>
    /// XmlElementSyntax class, which represents the structure::XmlElementSyntax node.
    /// </summary>
    [DebuggerDisplay("Id={Id}")]
#if (CSHARP_INTERNAL)
    internal
#else
    public
#endif
    class XmlElementSyntax : XmlNodeSyntax {


        // ---------- Edges ----------

        /// <summary>Container stores the id of the nodes the Content edge points to.</summary>
        protected LinkedList<uint> ContentContainer;

        /// <summary>The id of the node the EndTag edge points to.</summary>
        protected uint m_EndTag;

        /// <summary>The id of the node the StartTag edge points to.</summary>
        protected uint m_StartTag;

        /// <summary>
        /// Constructor, only factory can instantiates nodes.
        /// </summary>
        /// <param name="nodeId">[in] The id of the node.</param>
        /// <param name="factory">[in] Poiter to the Factory the node belongs to.</param>
        public XmlElementSyntax(uint nodeId, Factory factory) : base(nodeId, factory) {
            ContentContainer = new LinkedList<uint>();
            m_EndTag = 0;
            m_StartTag = 0;
        }

        /// <summary>
        /// Gives back the NodeKind of the node.
        /// </summary>
        /// <returns>Returns with the NodeKind.</returns>
        public override Types.NodeKind NodeKind {
            get { return Types.NodeKind.ndkXmlElementSyntax; }
        }


        // ---------- Reflection getter function ----------

        /// <summary>
        /// Gives back the begin iterator for the edge specified
        /// </summary>
        /// <param name="edge">[in] The multiple edge for which the iterator is requested</param>
        public override ListIterator<Columbus.Csharp.Asg.Nodes.Base.Base> GetListIteratorBegin(string edge) {
            switch(edge) {
                case "Content":
                    return ContentListIteratorBegin.Convert<Columbus.Csharp.Asg.Nodes.Base.Base>();
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
                case "Content":
                    addContent(nodeId);
                    return;
                default:
                    base.add(edge, nodeId);
                    return;
            }
        }


        // ---------- Edge getter function(s) ----------

        /// <summary>
        /// Gives back iterator for the Content edges.
        /// </summary>
        /// <returns>Returns an iterator for the Content edges.</returns>
        public ListIterator<Columbus.Csharp.Asg.Nodes.Structure.XmlNodeSyntax> ContentListIteratorBegin {
            get {
                return new ListIterator<Columbus.Csharp.Asg.Nodes.Structure.XmlNodeSyntax>(ContentContainer, fact, true);
            }
        }

        /// <summary>
        /// Gives back iterator for the Content edges.
        /// </summary>
        /// <returns>Returns an iterator for the Content edges.</returns>
        public ListIterator<Columbus.Csharp.Asg.Nodes.Structure.XmlNodeSyntax> ContentListIteratorEnd {
            get {
                return new ListIterator<Columbus.Csharp.Asg.Nodes.Structure.XmlNodeSyntax>(ContentContainer, fact, false);
            }
        }

        /// <summary>
        /// Tells whether the node has Content edges or not.
        /// </summary>
        /// <returns>Returns true if the node has at least one Content edge.</returns>
        public bool ContentIsEmpty {
            get { return ContentContainer.Count == 0; }
        }

        /// <summary>
        /// Gives back how many Content edges the node has.
        /// </summary>
        /// <returns>Returns with the number of Content edges.</returns>
        public uint ContentSize {
            get { return (uint)(ContentContainer.Count); }
        }

        /// <summary>
        /// Gives back the id of the node the EndTag edge points to.
        /// </summary>
        /// <returns>Returns the end point of the m_EndTag edge.</returns>
        /// <exception cref="Columbus.Csharp.Asg.CsharpException">Throws CsharpException if the edge id is invalid.</exception>
        public uint getEndTag() {
            if (fact.getIsFiltered(m_EndTag))
                return 1;
            else
                return m_EndTag;
        }

        /// <summary>
        /// Gives back the id of the node the StartTag edge points to.
        /// </summary>
        /// <returns>Returns the end point of the m_StartTag edge.</returns>
        /// <exception cref="Columbus.Csharp.Asg.CsharpException">Throws CsharpException if the edge id is invalid.</exception>
        public uint getStartTag() {
            if (fact.getIsFiltered(m_StartTag))
                return 1;
            else
                return m_StartTag;
        }


        // ---------- Edge setter function(s) ----------

        /// <summary>
        /// Adds a new Content edge to the node and inserts it after the other ones.
        /// </summary>
        /// <param name="node">[in] The end point of the new Content edge.</param>
        /// <exception cref="Columbus.Csharp.Asg.CsharpException">Throws CsharpException if there is something wrong with the given node.</exception>
        public void addContent(Columbus.Csharp.Asg.Nodes.Structure.XmlNodeSyntax node) {
            addContent(node.Id);
        }

        /// <summary>
        /// Adds a new Content edge to the node and inserts it after the other ones.
        /// </summary>
        /// <param name="nodeId">[in] The end point of the new Content edge.</param>
        /// <exception cref="Columbus.Csharp.Asg.CsharpException">Throws CsharpException if the given nodeId is invalid.</exception>
        public void addContent(uint nodeId) {
            if (!fact.getExist(nodeId))
                throw new CsharpException("Columbus.Csharp.Asg.Nodes.Structure.XmlElementSyntax.addContent(NodeId)", "The end point of the edge does not exist.");
            Columbus.Csharp.Asg.Nodes.Base.Base node = fact.getRef(nodeId);
            if (Common.getIsBaseClassKind(node.NodeKind, Types.NodeKind.ndkXmlNodeSyntax)) {
                ContentContainer.AddLast(nodeId);
            } else {
                throw new CsharpException("Columbus.Csharp.Asg.Nodes.Structure.XmlElementSyntax.setContent(NodeId)", "Invalid NodeKind (" + node.NodeKind.ToString() + ").");
            }
           setParentEdge(nodeId, (uint)Types.EdgeKind.edkXmlElementSyntax_Content);
            if (fact.ReverseEdges != null)
              fact.ReverseEdges.insertEdge(nodeId, this.Id, Types.EdgeKind.edkXmlElementSyntax_Content);
        }

        /// <summary>
        /// Sets the EndTag edge.
        /// </summary>
        /// <param name="nodeId">[in] The new end point of the EndTag edge or 0. With 0 the edge can be deleted.</param>
        /// <exception cref="Columbus.Csharp.Asg.CsharpException">Throws CsharpException if the nodeId is invalid.</exception>
        public void setEndTag(uint nodeId) {
            if (nodeId != 0) {
                if (!fact.getExist(nodeId))
                    throw new CsharpException("Columbus.Csharp.Asg.Nodes.Structure.XmlElementSyntax.setEndTag(NodeId)", "The end point of the edge does not exist.");

                Columbus.Csharp.Asg.Nodes.Base.Base node = fact.getRef(nodeId);
                if (Common.getIsBaseClassKind(node.NodeKind, Types.NodeKind.ndkXmlElementEndTagSyntax)) {
                    if (m_EndTag != 0) {
                        removeParentEdge(m_EndTag);
                    }
                    m_EndTag = nodeId;
                    setParentEdge(m_EndTag, (uint)Types.EdgeKind.edkXmlElementSyntax_EndTag);
                } else {
                    throw new CsharpException("Columbus.Csharp.Asg.Nodes.Structure.XmlElementSyntax.setEndTag(NodeId)", "Invalid NodeKind (" + node.NodeKind.ToString() + ").");
                }
            } else {
                if (m_EndTag != 0) {
                    removeParentEdge(m_EndTag);
                }
                m_EndTag = 0;
            }
        }

        /// <summary>
        /// Sets the EndTag edge.
        /// </summary>
        /// <param name="node">[in] The new end point of the EndTag edge.</param>
        /// <exception cref="Columbus.Csharp.Asg.CsharpException">Throws CsharpException if there's something wrong with the given node.</exception>
        public void setEndTag(Columbus.Csharp.Asg.Nodes.Structure.XmlElementEndTagSyntax node) {
            if (m_EndTag != 0) {
                removeParentEdge(m_EndTag);
            }
            m_EndTag = node.Id;
            setParentEdge(m_EndTag, (uint)Types.EdgeKind.edkXmlElementSyntax_EndTag);
        }

        /// <summary>
        /// Sets the StartTag edge.
        /// </summary>
        /// <param name="nodeId">[in] The new end point of the StartTag edge or 0. With 0 the edge can be deleted.</param>
        /// <exception cref="Columbus.Csharp.Asg.CsharpException">Throws CsharpException if the nodeId is invalid.</exception>
        public void setStartTag(uint nodeId) {
            if (nodeId != 0) {
                if (!fact.getExist(nodeId))
                    throw new CsharpException("Columbus.Csharp.Asg.Nodes.Structure.XmlElementSyntax.setStartTag(NodeId)", "The end point of the edge does not exist.");

                Columbus.Csharp.Asg.Nodes.Base.Base node = fact.getRef(nodeId);
                if (Common.getIsBaseClassKind(node.NodeKind, Types.NodeKind.ndkXmlElementStartTagSyntax)) {
                    if (m_StartTag != 0) {
                        removeParentEdge(m_StartTag);
                    }
                    m_StartTag = nodeId;
                    setParentEdge(m_StartTag, (uint)Types.EdgeKind.edkXmlElementSyntax_StartTag);
                } else {
                    throw new CsharpException("Columbus.Csharp.Asg.Nodes.Structure.XmlElementSyntax.setStartTag(NodeId)", "Invalid NodeKind (" + node.NodeKind.ToString() + ").");
                }
            } else {
                if (m_StartTag != 0) {
                    removeParentEdge(m_StartTag);
                }
                m_StartTag = 0;
            }
        }

        /// <summary>
        /// Sets the StartTag edge.
        /// </summary>
        /// <param name="node">[in] The new end point of the StartTag edge.</param>
        /// <exception cref="Columbus.Csharp.Asg.CsharpException">Throws CsharpException if there's something wrong with the given node.</exception>
        public void setStartTag(Columbus.Csharp.Asg.Nodes.Structure.XmlElementStartTagSyntax node) {
            if (m_StartTag != 0) {
                removeParentEdge(m_StartTag);
            }
            m_StartTag = node.Id;
            setParentEdge(m_StartTag, (uint)Types.EdgeKind.edkXmlElementSyntax_StartTag);
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

            io.writeUInt4(m_EndTag);
            io.writeUInt4(m_StartTag);


            foreach (var Content in ContentContainer) {
              io.writeUInt4(Content);
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

            m_EndTag =  binIo.readUInt4();
            if (m_EndTag != 0)
              setParentEdge(m_EndTag,(uint)Types.EdgeKind.edkXmlElementSyntax_EndTag);

            m_StartTag =  binIo.readUInt4();
            if (m_StartTag != 0)
              setParentEdge(m_StartTag,(uint)Types.EdgeKind.edkXmlElementSyntax_StartTag);

            uint _id;

            _id = binIo.readUInt4();
            while (_id != 0) {
              ContentContainer.AddLast(_id);
              setParentEdge(_id, (uint)Types.EdgeKind.edkXmlElementSyntax_Content);
              _id = binIo.readUInt4();
            }
        }

    }

}
