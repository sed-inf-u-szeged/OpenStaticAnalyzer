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

namespace Columbus.Csharp.Asg.Nodes.Structure {

    /// <summary>
    /// GroupClauseSyntax class, which represents the structure::GroupClauseSyntax node.
    /// </summary>
    [DebuggerDisplay("{DemangledName}")]
#if (CSHARP_INTERNAL)
    internal
#else
    public
#endif
    class GroupClauseSyntax : SelectOrGroupClauseSyntax {


        // ---------- Edges ----------

        /// <summary>The id of the node the ByExpression edge points to.</summary>
        protected uint m_ByExpression;

        /// <summary>The id of the node the GroupExpression edge points to.</summary>
        protected uint m_GroupExpression;

        /// <summary>
        /// Constructor, only factory can instantiates nodes.
        /// </summary>
        /// <param name="nodeId">[in] The id of the node.</param>
        /// <param name="factory">[in] Poiter to the Factory the node belongs to.</param>
        public GroupClauseSyntax(uint nodeId, Factory factory) : base(nodeId, factory) {
            m_ByExpression = 0;
            m_GroupExpression = 0;
        }

        /// <summary>
        /// Gives back the NodeKind of the node.
        /// </summary>
        /// <returns>Returns with the NodeKind.</returns>
        public override Types.NodeKind NodeKind {
            get { return Types.NodeKind.ndkGroupClauseSyntax; }
        }


        // ---------- Reflection getter function ----------

        /// <summary>
        /// Gives back the begin iterator for the edge specified
        /// </summary>
        /// <param name="edge">[in] The multiple edge for which the iterator is requested</param>
        public override ListIterator<Columbus.Csharp.Asg.Nodes.Base.Base> GetListIteratorBegin(string edge) {
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
        /// Gives back the id of the node the ByExpression edge points to.
        /// </summary>
        /// <returns>Returns the end point of the m_ByExpression edge.</returns>
        /// <exception cref="Columbus.Csharp.Asg.CsharpException">Throws CsharpException if the edge id is invalid.</exception>
        public uint getByExpression() {
            if (fact.getIsFiltered(m_ByExpression))
                return 1;
            else
                return m_ByExpression;
        }

        /// <summary>
        /// Gives back the id of the node the GroupExpression edge points to.
        /// </summary>
        /// <returns>Returns the end point of the m_GroupExpression edge.</returns>
        /// <exception cref="Columbus.Csharp.Asg.CsharpException">Throws CsharpException if the edge id is invalid.</exception>
        public uint getGroupExpression() {
            if (fact.getIsFiltered(m_GroupExpression))
                return 1;
            else
                return m_GroupExpression;
        }


        // ---------- Edge setter function(s) ----------

        /// <summary>
        /// Sets the ByExpression edge.
        /// </summary>
        /// <param name="nodeId">[in] The new end point of the ByExpression edge or 0. With 0 the edge can be deleted.</param>
        /// <exception cref="Columbus.Csharp.Asg.CsharpException">Throws CsharpException if the nodeId is invalid.</exception>
        public void setByExpression(uint nodeId) {
            if (nodeId != 0) {
                if (!fact.getExist(nodeId))
                    throw new CsharpException("Columbus.Csharp.Asg.Nodes.Structure.GroupClauseSyntax.setByExpression(NodeId)", "The end point of the edge does not exist.");

                Columbus.Csharp.Asg.Nodes.Base.Base node = fact.getRef(nodeId);
                if (Common.getIsBaseClassKind(node.NodeKind, Types.NodeKind.ndkExpressionSyntax)) {
                    if (m_ByExpression != 0) {
                        removeParentEdge(m_ByExpression);
                    }
                    m_ByExpression = nodeId;
                    setParentEdge(m_ByExpression, (uint)Types.EdgeKind.edkGroupClauseSyntax_ByExpression);
                } else {
                    throw new CsharpException("Columbus.Csharp.Asg.Nodes.Structure.GroupClauseSyntax.setByExpression(NodeId)", "Invalid NodeKind (" + node.NodeKind.ToString() + ").");
                }
            } else {
                if (m_ByExpression != 0) {
                    removeParentEdge(m_ByExpression);
                }
                m_ByExpression = 0;
            }
        }

        /// <summary>
        /// Sets the ByExpression edge.
        /// </summary>
        /// <param name="node">[in] The new end point of the ByExpression edge.</param>
        /// <exception cref="Columbus.Csharp.Asg.CsharpException">Throws CsharpException if there's something wrong with the given node.</exception>
        public void setByExpression(Columbus.Csharp.Asg.Nodes.Expression.ExpressionSyntax node) {
            if (m_ByExpression != 0) {
                removeParentEdge(m_ByExpression);
            }
            m_ByExpression = node.Id;
            setParentEdge(m_ByExpression, (uint)Types.EdgeKind.edkGroupClauseSyntax_ByExpression);
        }

        /// <summary>
        /// Sets the GroupExpression edge.
        /// </summary>
        /// <param name="nodeId">[in] The new end point of the GroupExpression edge or 0. With 0 the edge can be deleted.</param>
        /// <exception cref="Columbus.Csharp.Asg.CsharpException">Throws CsharpException if the nodeId is invalid.</exception>
        public void setGroupExpression(uint nodeId) {
            if (nodeId != 0) {
                if (!fact.getExist(nodeId))
                    throw new CsharpException("Columbus.Csharp.Asg.Nodes.Structure.GroupClauseSyntax.setGroupExpression(NodeId)", "The end point of the edge does not exist.");

                Columbus.Csharp.Asg.Nodes.Base.Base node = fact.getRef(nodeId);
                if (Common.getIsBaseClassKind(node.NodeKind, Types.NodeKind.ndkExpressionSyntax)) {
                    if (m_GroupExpression != 0) {
                        removeParentEdge(m_GroupExpression);
                    }
                    m_GroupExpression = nodeId;
                    setParentEdge(m_GroupExpression, (uint)Types.EdgeKind.edkGroupClauseSyntax_GroupExpression);
                } else {
                    throw new CsharpException("Columbus.Csharp.Asg.Nodes.Structure.GroupClauseSyntax.setGroupExpression(NodeId)", "Invalid NodeKind (" + node.NodeKind.ToString() + ").");
                }
            } else {
                if (m_GroupExpression != 0) {
                    removeParentEdge(m_GroupExpression);
                }
                m_GroupExpression = 0;
            }
        }

        /// <summary>
        /// Sets the GroupExpression edge.
        /// </summary>
        /// <param name="node">[in] The new end point of the GroupExpression edge.</param>
        /// <exception cref="Columbus.Csharp.Asg.CsharpException">Throws CsharpException if there's something wrong with the given node.</exception>
        public void setGroupExpression(Columbus.Csharp.Asg.Nodes.Expression.ExpressionSyntax node) {
            if (m_GroupExpression != 0) {
                removeParentEdge(m_GroupExpression);
            }
            m_GroupExpression = node.Id;
            setParentEdge(m_GroupExpression, (uint)Types.EdgeKind.edkGroupClauseSyntax_GroupExpression);
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

            io.writeUInt4(m_ByExpression);
            io.writeUInt4(m_GroupExpression);

        }

        /// <summary>
        /// Loads the node.
        /// </summary>
        /// <param name="io">[in] The node is read from io.</param>
        /// <exception cref="Columbus.ColumbusIOException">Throws ColumbusIOException if there is something wrong with the file.</exception>
        public override void load(IO binIo) {
            base.load(binIo);

            m_ByExpression =  binIo.readUInt4();
            if (m_ByExpression != 0)
              setParentEdge(m_ByExpression,(uint)Types.EdgeKind.edkGroupClauseSyntax_ByExpression);

            m_GroupExpression =  binIo.readUInt4();
            if (m_GroupExpression != 0)
              setParentEdge(m_GroupExpression,(uint)Types.EdgeKind.edkGroupClauseSyntax_GroupExpression);

        }

    }

}
