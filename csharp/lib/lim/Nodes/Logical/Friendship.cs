/*
 *  This file is part of OpenStaticAnalyzer.
 *
 *  Copyright (c) 2004-2017 Department of Software Engineering - University of Szeged
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
    /// Friendship class, which represents the logical::Friendship node.
    /// </summary>
    [DebuggerDisplay("{DemangledName}")]
#if (LIM_INTERNAL)
    internal
#else
    public
#endif
    class Friendship : Columbus.Lim.Asg.Nodes.Base.Base {

        /// <summary>The Key of the `grants`.</summary>
        protected uint m_grants;


        // ---------- Edges ----------

        /// <summary>The id of the node the friend edge points to.</summary>
        protected uint m_friend;

        /// <summary>
        /// Constructor, only factory can instantiates nodes.
        /// </summary>
        /// <param name="nodeId">[in] The id of the node.</param>
        /// <param name="factory">[in] Poiter to the Factory the node belongs to.</param>
        public Friendship(uint nodeId, Factory factory) : base(nodeId, factory) {
            m_grants = 0;
            m_friend = 0;
        }

        /// <summary>
        /// Gives back the NodeKind of the node.
        /// </summary>
        /// <returns>Returns with the NodeKind.</returns>
        public override Types.NodeKind NodeKind {
            get { return Types.NodeKind.ndkFriendship; }
        }


        // ---------- Attribute propert(y)(ies) ----------

        /// <summary>
        /// Gives back or sets the grants of the node.
        /// </summary>
        public string Grants
        {
            get
            {
                return fact.StringTable.get(m_grants);
            }
            set
            {
                m_grants = fact.StringTable.set( value );
            }
        }

        /// <summary>
        /// Gives back or sets the Key of grants of the node.
        /// </summary>
        public uint GrantsKey
        {
            get
            {
                return m_grants;
            }
            set
            {
               m_grants = value;
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
        /// Gives back the id of the node the friend edge points to.
        /// </summary>
        /// <returns>Returns the end point of the m_friend edge.</returns>
        /// <exception cref="Columbus.Lim.Asg.LimException">Throws LimException if the edge id is invalid.</exception>
        public uint getFriend() {
            if (fact.getIsFiltered(m_friend))
                return 1;
            else
                return m_friend;
        }


        // ---------- Edge setter function(s) ----------

        /// <summary>
        /// Sets the friend edge.
        /// </summary>
        /// <param name="nodeId">[in] The new end point of the friend edge or 0. With 0 the edge can be deleted.</param>
        /// <exception cref="Columbus.Lim.Asg.LimException">Throws LimException if the nodeId is invalid.</exception>
        public void setFriend(uint nodeId) {
            if (nodeId != 0) {
                if (!fact.getExist(nodeId))
                    throw new LimException("Columbus.Lim.Asg.Nodes.Logical.Friendship.setFriend(NodeId)", "The end point of the edge does not exist.");

                Columbus.Lim.Asg.Nodes.Base.Base node = fact.getRef(nodeId);
                if (Common.getIsBaseClassKind(node.NodeKind, Types.NodeKind.ndkMethod) || Common.getIsBaseClassKind(node.NodeKind, Types.NodeKind.ndkClass)) {
                    if (m_friend != 0) {
                    }
                    m_friend = nodeId;
                } else {
                    throw new LimException("Columbus.Lim.Asg.Nodes.Logical.Friendship.setFriend(NodeId)", "Invalid NodeKind (" + node.NodeKind.ToString() + ").");
                }
            } else {
                if (m_friend != 0) {
                }
                m_friend = 0;
            }
        }

        /// <summary>
        /// Sets the friend edge.
        /// </summary>
        /// <param name="node">[in] The new end point of the friend edge.</param>
        /// <exception cref="Columbus.Lim.Asg.LimException">Throws LimException if there's something wrong with the given node.</exception>
        public void setFriend(Columbus.Lim.Asg.Nodes.Logical.Scope node) {
            if (Common.getIsBaseClassKind(node.NodeKind, Types.NodeKind.ndkMethod) || Common.getIsBaseClassKind(node.NodeKind, Types.NodeKind.ndkClass)) {
                if (m_friend != 0) {
                }
                m_friend = node.Id;
            } else {
                throw new LimException("Columbus.Lim.Asg.Nodes.Logical.Friendship.setFriend(NodeId)", "Invalid NodeKind (" + node.NodeKind.ToString() + ").");
            }
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

            fact.StringTable.setType(m_grants, StrTable.StrType.strToSave);
            io.writeUInt4(m_grants);

            io.writeUInt4(m_friend);

        }

        /// <summary>
        /// Loads the node.
        /// </summary>
        /// <param name="io">[in] The node is read from io.</param>
        /// <exception cref="Columbus.ColumbusIOException">Throws ColumbusIOException if there is something wrong with the file.</exception>
        public override void load(IO binIo) {
            base.load(binIo);

            m_grants = binIo.readUInt4();

            m_friend =  binIo.readUInt4();

        }

    }

}
