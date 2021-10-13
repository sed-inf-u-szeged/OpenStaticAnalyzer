using System;
using System.Text;
using System.Diagnostics;
using System.Collections.Generic;

namespace Columbus.Lim.Asg.Nodes.Logical {

    /// <summary>
    /// MethodCall class, which represents the logical::MethodCall node.
    /// </summary>
    [DebuggerDisplay("Id={Id}")]
#if (LIM_INTERNAL)
    internal
#else
    public
#endif
    class MethodCall : Columbus.Lim.Asg.Nodes.Base.Base {

        /// <summary>The Key of the `calls`.</summary>
        protected uint m_calls;


        // ---------- Edges ----------

        /// <summary>The id of the node the method edge points to.</summary>
        protected uint m_method;

        /// <summary>
        /// Constructor, only factory can instantiates nodes.
        /// </summary>
        /// <param name="nodeId">[in] The id of the node.</param>
        /// <param name="factory">[in] Poiter to the Factory the node belongs to.</param>
        public MethodCall(uint nodeId, Factory factory) : base(nodeId, factory) {
            m_calls = 0;
            m_method = 0;
        }

        /// <summary>
        /// Gives back the NodeKind of the node.
        /// </summary>
        /// <returns>Returns with the NodeKind.</returns>
        public override Types.NodeKind NodeKind {
            get { return Types.NodeKind.ndkMethodCall; }
        }


        // ---------- Attribute propert(y)(ies) ----------

        /// <summary>
        /// Gives back or sets the calls of the node.
        /// </summary>
        public string Calls
        {
            get
            {
                return fact.StringTable.get(m_calls);
            }
            set
            {
                m_calls = fact.StringTable.set( value );
            }
        }

        /// <summary>
        /// Gives back or sets the Key of calls of the node.
        /// </summary>
        public uint CallsKey
        {
            get
            {
                return m_calls;
            }
            set
            {
               m_calls = value;
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
        /// Gives back the id of the node the method edge points to.
        /// </summary>
        /// <returns>Returns the end point of the m_method edge.</returns>
        /// <exception cref="Columbus.Lim.Asg.LimException">Throws LimException if the edge id is invalid.</exception>
        public uint getMethod() {
            if (fact.getIsFiltered(m_method))
                return 1;
            else
                return m_method;
        }


        // ---------- Edge setter function(s) ----------

        /// <summary>
        /// Sets the method edge.
        /// </summary>
        /// <param name="nodeId">[in] The new end point of the method edge or 0. With 0 the edge can be deleted.</param>
        /// <exception cref="Columbus.Lim.Asg.LimException">Throws LimException if the nodeId is invalid.</exception>
        public void setMethod(uint nodeId) {
            if (nodeId != 0) {
                if (!fact.getExist(nodeId))
                    throw new LimException("Columbus.Lim.Asg.Nodes.Logical.MethodCall.setMethod(NodeId)", "The end point of the edge does not exist.");

                Columbus.Lim.Asg.Nodes.Base.Base node = fact.getRef(nodeId);
                if (Common.getIsBaseClassKind(node.NodeKind, Types.NodeKind.ndkMethod)) {
                    if (m_method != 0) {
                    }
                    m_method = nodeId;
                } else {
                    throw new LimException("Columbus.Lim.Asg.Nodes.Logical.MethodCall.setMethod(NodeId)", "Invalid NodeKind (" + node.NodeKind.ToString() + ").");
                }
            } else {
                if (m_method != 0) {
                }
                m_method = 0;
            }
        }

        /// <summary>
        /// Sets the method edge.
        /// </summary>
        /// <param name="node">[in] The new end point of the method edge.</param>
        /// <exception cref="Columbus.Lim.Asg.LimException">Throws LimException if there's something wrong with the given node.</exception>
        public void setMethod(Columbus.Lim.Asg.Nodes.Logical.Method node) {
            if (m_method != 0) {
            }
            m_method = node.Id;
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

            fact.StringTable.setType(m_calls, StrTable.StrType.strToSave);
            io.writeUInt4(m_calls);

            io.writeUInt4(m_method);

        }

        /// <summary>
        /// Loads the node.
        /// </summary>
        /// <param name="io">[in] The node is read from io.</param>
        /// <exception cref="Columbus.ColumbusIOException">Throws ColumbusIOException if there is something wrong with the file.</exception>
        public override void load(IO binIo) {
            base.load(binIo);

            m_calls = binIo.readUInt4();

            m_method =  binIo.readUInt4();

        }

    }

}
