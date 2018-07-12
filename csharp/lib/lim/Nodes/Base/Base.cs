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

namespace Columbus.Lim.Asg.Nodes.Base {

    /// <summary>
    /// Base class, which represents the base::Base node.
    /// </summary>
    [DebuggerDisplay("{DemangledName}")]
#if (LIM_INTERNAL)
    internal
#else
    public
#endif
    class Base {

        /// <summary>The value of the `id`.</summary>
        protected uint m_id;

        /// <summary>The Factory of the node.</summary>
        protected Factory fact;

        /// <summary>Edge to the parent node.</summary>
        protected uint parent;

        /// <summary>
        /// Constructor, only factory can instantiates nodes.
        /// </summary>
        /// <param name="nodeId">[in] The id of the node.</param>
        /// <param name="factory">[in] Poiter to the Factory the node belongs to.</param>
        public Base(uint nodeId, Factory factory) {
            m_id = nodeId;
            fact = factory;
            parent = 0;
        }

        /// <summary>
        /// Sets this node the parent of the node given in parameter.
        /// </summary>
        /// <param name="childNode">[in] The node whose parent is set to this node.</param>
        /// <exception cref="Columbus.Lim.Asg.LimException">Throws LimException if the id is invalid.</exception>
        public void setParentEdge(uint childNode, uint parentEdgeKind) {
            fact.getRef(childNode).Parent = m_id;
            fact.getRef(childNode).ParentEdgeKind = parentEdgeKind;
        }

        /// <summary>
        /// Removes the parent of the node given in parameter.
        /// </summary>
        /// <param name="childNode">[in] The node whose parent is removed.</param>
        /// <exception cref="Columbus.Lim.Asg.LimException">Throws LimException if the id is invalid.</exception>
        public void removeParentEdge(uint childNode) {
            fact.getRef(childNode).Parent = 0;
        }

        /// <summary>
        /// Sets and gets the parent of this node.
        /// </summary>
        public uint Parent
        {
            get
            {
                return parent;
            }
            set
            {
                parent = value;
            }
        }

        public uint ParentEdgeKind { get; set; }
        /// <summary>
        /// Gives back the Factory the node belongs to.
        /// </summary>
        /// <returns>Return with a reference to the Factory.</returns>
        public Factory Factory {
            get { return fact; }
        }

        /// <summary>
        /// Gives back the begin iterator for the edge specified
        /// </summary>
        public virtual ListIterator<Columbus.Lim.Asg.Nodes.Base.Base> GetListIteratorBegin(string edge) {
            return null;
        }

        /// <summary>
        /// Adds nodeId as a new edge
        /// </summary>
        public virtual void add(string edge, uint nodId) { }

        /// <summary>
        /// Gives back the NodeKind of the node.
        /// </summary>
        /// <returns>Returns with the NodeKind.</returns>
        public virtual Types.NodeKind NodeKind {
            get { return Types.NodeKind.ndkBase; }
        }


        // ---------- Attribute propert(y)(ies) ----------

        /// <summary>
        /// Gives back the id of the node.
        /// </summary>
        /// <returns>Returns with the id.</returns>
        public uint Id
        {
            get
            {
                return m_id;
            }
            set
            {
                m_id = value;
            }
        }


        // ---------- Accept functions for Visitor ----------

        /// <summary>
        /// It calls the appropriate visit method of the given visitor.
        /// </summary>
        /// <param name="visitor">[in] The used visitor.</param>
        public virtual void accept(Visitors.Visitor visitor) {
        }

        /// <summary>
        /// It calls the appropriate visitEnd method of the given visitor.
        /// </summary>
        /// <param name="visitor">[in] The used visitor.</param>
        public virtual void acceptEnd(Visitors.Visitor visitor) {
        }

        /// <summary>
        /// Saves the node.
        /// </summary>
        /// <param name="io">[in] The node is written into io.</param>
        /// <exception cref="Columbus.ColumbusIOException">Throws ColumbusIOException if there is something wrong with the file.</exception>
        public virtual void save(IO io) {
            io.writeUInt4(m_id);
            io.writeUShort2((ushort)NodeKind);

        }

        /// <summary>
        /// Loads the node.
        /// </summary>
        /// <param name="io">[in] The node is read from io.</param>
        /// <exception cref="Columbus.ColumbusIOException">Throws ColumbusIOException if there is something wrong with the file.</exception>
        public virtual void load(IO binIo) {

        }

    }

}
