/*
 *  This file is part of OpenStaticAnalyzer.
 *
 *  Copyright (c) 2004-2018 Department of Software Engineering - University of Szeged
 *
 *  Licensed under Version 1.2 of the EUPL (the "Licence");
 *
 *  You may not use this work except in compliance with the Licence.
 *
 *  You may obtain a copy of the Licence in the LICENSE file or at:
 *
 *  https://joinup.ec.europa.eu/software/page/eupl
 *
 *  Unless required by applicable law or agreed to in writing, software
 *  distributed under the Licence is distributed on an "AS IS" basis,
 *  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *  See the Licence for the specific language governing permissions and
 *  limitations under the Licence.
 */

using System;
using System.Text;
using System.Diagnostics;
using System.Collections.Generic;

namespace Columbus.Lim.Asg.Nodes.Logical {

    /// <summary>
    /// AttributeAccess class, which represents the logical::AttributeAccess node.
    /// </summary>
    [DebuggerDisplay("{DemangledName}")]
#if (LIM_INTERNAL)
    internal
#else
    public
#endif
    class AttributeAccess : Columbus.Lim.Asg.Nodes.Base.Base {

        /// <summary>The Key of the `accesses`.</summary>
        protected uint m_accesses;


        // ---------- Edges ----------

        /// <summary>The id of the node the attribute edge points to.</summary>
        protected uint m_attribute;

        /// <summary>
        /// Constructor, only factory can instantiates nodes.
        /// </summary>
        /// <param name="nodeId">[in] The id of the node.</param>
        /// <param name="factory">[in] Poiter to the Factory the node belongs to.</param>
        public AttributeAccess(uint nodeId, Factory factory) : base(nodeId, factory) {
            m_accesses = 0;
            m_attribute = 0;
        }

        /// <summary>
        /// Gives back the NodeKind of the node.
        /// </summary>
        /// <returns>Returns with the NodeKind.</returns>
        public override Types.NodeKind NodeKind {
            get { return Types.NodeKind.ndkAttributeAccess; }
        }


        // ---------- Attribute propert(y)(ies) ----------

        /// <summary>
        /// Gives back or sets the accesses of the node.
        /// </summary>
        public string Accesses
        {
            get
            {
                return fact.StringTable.get(m_accesses);
            }
            set
            {
                m_accesses = fact.StringTable.set( value );
            }
        }

        /// <summary>
        /// Gives back or sets the Key of accesses of the node.
        /// </summary>
        public uint AccessesKey
        {
            get
            {
                return m_accesses;
            }
            set
            {
               m_accesses = value;
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
        /// Gives back the id of the node the attribute edge points to.
        /// </summary>
        /// <returns>Returns the end point of the m_attribute edge.</returns>
        /// <exception cref="Columbus.Lim.Asg.LimException">Throws LimException if the edge id is invalid.</exception>
        public uint getAttribute() {
            if (fact.getIsFiltered(m_attribute))
                return 1;
            else
                return m_attribute;
        }


        // ---------- Edge setter function(s) ----------

        /// <summary>
        /// Sets the attribute edge.
        /// </summary>
        /// <param name="nodeId">[in] The new end point of the attribute edge or 0. With 0 the edge can be deleted.</param>
        /// <exception cref="Columbus.Lim.Asg.LimException">Throws LimException if the nodeId is invalid.</exception>
        public void setAttribute(uint nodeId) {
            if (nodeId != 0) {
                if (!fact.getExist(nodeId))
                    throw new LimException("Columbus.Lim.Asg.Nodes.Logical.AttributeAccess.setAttribute(NodeId)", "The end point of the edge does not exist.");

                Columbus.Lim.Asg.Nodes.Base.Base node = fact.getRef(nodeId);
                if (Common.getIsBaseClassKind(node.NodeKind, Types.NodeKind.ndkAttribute)) {
                    if (m_attribute != 0) {
                    }
                    m_attribute = nodeId;
                } else {
                    throw new LimException("Columbus.Lim.Asg.Nodes.Logical.AttributeAccess.setAttribute(NodeId)", "Invalid NodeKind (" + node.NodeKind.ToString() + ").");
                }
            } else {
                if (m_attribute != 0) {
                }
                m_attribute = 0;
            }
        }

        /// <summary>
        /// Sets the attribute edge.
        /// </summary>
        /// <param name="node">[in] The new end point of the attribute edge.</param>
        /// <exception cref="Columbus.Lim.Asg.LimException">Throws LimException if there's something wrong with the given node.</exception>
        public void setAttribute(Columbus.Lim.Asg.Nodes.Logical.Attribute node) {
            if (m_attribute != 0) {
            }
            m_attribute = node.Id;
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

            fact.StringTable.setType(m_accesses, StrTable.StrType.strToSave);
            io.writeUInt4(m_accesses);

            io.writeUInt4(m_attribute);

        }

        /// <summary>
        /// Loads the node.
        /// </summary>
        /// <param name="io">[in] The node is read from io.</param>
        /// <exception cref="Columbus.ColumbusIOException">Throws ColumbusIOException if there is something wrong with the file.</exception>
        public override void load(IO binIo) {
            base.load(binIo);

            m_accesses = binIo.readUInt4();

            m_attribute =  binIo.readUInt4();

        }

    }

}
