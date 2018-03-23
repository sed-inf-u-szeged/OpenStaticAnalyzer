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

namespace Columbus.Csharp.Asg.Nodes.Structure {

    /// <summary>
    /// JoinClauseSyntax class, which represents the structure::JoinClauseSyntax node.
    /// </summary>
    [DebuggerDisplay("{DemangledName}")]
#if (CSHARP_INTERNAL)
    internal
#else
    public
#endif
    class JoinClauseSyntax : QueryClauseSyntax {

        /// <summary>The Key of the `identifier`.</summary>
        protected uint m_identifier;


        // ---------- Edges ----------

        /// <summary>The id of the node the InExpression edge points to.</summary>
        protected uint m_InExpression;

        /// <summary>The id of the node the Into edge points to.</summary>
        protected uint m_Into;

        /// <summary>The id of the node the LeftExpression edge points to.</summary>
        protected uint m_LeftExpression;

        /// <summary>The id of the node the RightExpression edge points to.</summary>
        protected uint m_RightExpression;

        /// <summary>The id of the node the Type edge points to.</summary>
        protected uint m_Type;

        /// <summary>
        /// Constructor, only factory can instantiates nodes.
        /// </summary>
        /// <param name="nodeId">[in] The id of the node.</param>
        /// <param name="factory">[in] Poiter to the Factory the node belongs to.</param>
        public JoinClauseSyntax(uint nodeId, Factory factory) : base(nodeId, factory) {
            m_identifier = 0;
            m_InExpression = 0;
            m_Into = 0;
            m_LeftExpression = 0;
            m_RightExpression = 0;
            m_Type = 0;
        }

        /// <summary>
        /// Gives back the NodeKind of the node.
        /// </summary>
        /// <returns>Returns with the NodeKind.</returns>
        public override Types.NodeKind NodeKind {
            get { return Types.NodeKind.ndkJoinClauseSyntax; }
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
        /// Gives back the id of the node the InExpression edge points to.
        /// </summary>
        /// <returns>Returns the end point of the m_InExpression edge.</returns>
        /// <exception cref="Columbus.Csharp.Asg.CsharpException">Throws CsharpException if the edge id is invalid.</exception>
        public uint getInExpression() {
            if (fact.getIsFiltered(m_InExpression))
                return 1;
            else
                return m_InExpression;
        }

        /// <summary>
        /// Gives back the id of the node the Into edge points to.
        /// </summary>
        /// <returns>Returns the end point of the m_Into edge.</returns>
        /// <exception cref="Columbus.Csharp.Asg.CsharpException">Throws CsharpException if the edge id is invalid.</exception>
        public uint getInto() {
            if (fact.getIsFiltered(m_Into))
                return 1;
            else
                return m_Into;
        }

        /// <summary>
        /// Gives back the id of the node the LeftExpression edge points to.
        /// </summary>
        /// <returns>Returns the end point of the m_LeftExpression edge.</returns>
        /// <exception cref="Columbus.Csharp.Asg.CsharpException">Throws CsharpException if the edge id is invalid.</exception>
        public uint getLeftExpression() {
            if (fact.getIsFiltered(m_LeftExpression))
                return 1;
            else
                return m_LeftExpression;
        }

        /// <summary>
        /// Gives back the id of the node the RightExpression edge points to.
        /// </summary>
        /// <returns>Returns the end point of the m_RightExpression edge.</returns>
        /// <exception cref="Columbus.Csharp.Asg.CsharpException">Throws CsharpException if the edge id is invalid.</exception>
        public uint getRightExpression() {
            if (fact.getIsFiltered(m_RightExpression))
                return 1;
            else
                return m_RightExpression;
        }

        /// <summary>
        /// Gives back the id of the node the Type edge points to.
        /// </summary>
        /// <returns>Returns the end point of the m_Type edge.</returns>
        /// <exception cref="Columbus.Csharp.Asg.CsharpException">Throws CsharpException if the edge id is invalid.</exception>
        public uint getType() {
            if (fact.getIsFiltered(m_Type))
                return 1;
            else
                return m_Type;
        }


        // ---------- Edge setter function(s) ----------

        /// <summary>
        /// Sets the InExpression edge.
        /// </summary>
        /// <param name="nodeId">[in] The new end point of the InExpression edge or 0. With 0 the edge can be deleted.</param>
        /// <exception cref="Columbus.Csharp.Asg.CsharpException">Throws CsharpException if the nodeId is invalid.</exception>
        public void setInExpression(uint nodeId) {
            if (nodeId != 0) {
                if (!fact.getExist(nodeId))
                    throw new CsharpException("Columbus.Csharp.Asg.Nodes.Structure.JoinClauseSyntax.setInExpression(NodeId)", "The end point of the edge does not exist.");

                Columbus.Csharp.Asg.Nodes.Base.Base node = fact.getRef(nodeId);
                if (Common.getIsBaseClassKind(node.NodeKind, Types.NodeKind.ndkExpressionSyntax)) {
                    if (m_InExpression != 0) {
                        removeParentEdge(m_InExpression);
                    }
                    m_InExpression = nodeId;
                    setParentEdge(m_InExpression, (uint)Types.EdgeKind.edkJoinClauseSyntax_InExpression);
                } else {
                    throw new CsharpException("Columbus.Csharp.Asg.Nodes.Structure.JoinClauseSyntax.setInExpression(NodeId)", "Invalid NodeKind (" + node.NodeKind.ToString() + ").");
                }
            } else {
                if (m_InExpression != 0) {
                    removeParentEdge(m_InExpression);
                }
                m_InExpression = 0;
            }
        }

        /// <summary>
        /// Sets the InExpression edge.
        /// </summary>
        /// <param name="node">[in] The new end point of the InExpression edge.</param>
        /// <exception cref="Columbus.Csharp.Asg.CsharpException">Throws CsharpException if there's something wrong with the given node.</exception>
        public void setInExpression(Columbus.Csharp.Asg.Nodes.Expression.ExpressionSyntax node) {
            if (m_InExpression != 0) {
                removeParentEdge(m_InExpression);
            }
            m_InExpression = node.Id;
            setParentEdge(m_InExpression, (uint)Types.EdgeKind.edkJoinClauseSyntax_InExpression);
        }

        /// <summary>
        /// Sets the Into edge.
        /// </summary>
        /// <param name="nodeId">[in] The new end point of the Into edge or 0. With 0 the edge can be deleted.</param>
        /// <exception cref="Columbus.Csharp.Asg.CsharpException">Throws CsharpException if the nodeId is invalid.</exception>
        public void setInto(uint nodeId) {
            if (nodeId != 0) {
                if (!fact.getExist(nodeId))
                    throw new CsharpException("Columbus.Csharp.Asg.Nodes.Structure.JoinClauseSyntax.setInto(NodeId)", "The end point of the edge does not exist.");

                Columbus.Csharp.Asg.Nodes.Base.Base node = fact.getRef(nodeId);
                if (Common.getIsBaseClassKind(node.NodeKind, Types.NodeKind.ndkJoinIntoClauseSyntax)) {
                    if (m_Into != 0) {
                        removeParentEdge(m_Into);
                    }
                    m_Into = nodeId;
                    setParentEdge(m_Into, (uint)Types.EdgeKind.edkJoinClauseSyntax_Into);
                } else {
                    throw new CsharpException("Columbus.Csharp.Asg.Nodes.Structure.JoinClauseSyntax.setInto(NodeId)", "Invalid NodeKind (" + node.NodeKind.ToString() + ").");
                }
            } else {
                if (m_Into != 0) {
                    removeParentEdge(m_Into);
                }
                m_Into = 0;
            }
        }

        /// <summary>
        /// Sets the Into edge.
        /// </summary>
        /// <param name="node">[in] The new end point of the Into edge.</param>
        /// <exception cref="Columbus.Csharp.Asg.CsharpException">Throws CsharpException if there's something wrong with the given node.</exception>
        public void setInto(Columbus.Csharp.Asg.Nodes.Structure.JoinIntoClauseSyntax node) {
            if (m_Into != 0) {
                removeParentEdge(m_Into);
            }
            m_Into = node.Id;
            setParentEdge(m_Into, (uint)Types.EdgeKind.edkJoinClauseSyntax_Into);
        }

        /// <summary>
        /// Sets the LeftExpression edge.
        /// </summary>
        /// <param name="nodeId">[in] The new end point of the LeftExpression edge or 0. With 0 the edge can be deleted.</param>
        /// <exception cref="Columbus.Csharp.Asg.CsharpException">Throws CsharpException if the nodeId is invalid.</exception>
        public void setLeftExpression(uint nodeId) {
            if (nodeId != 0) {
                if (!fact.getExist(nodeId))
                    throw new CsharpException("Columbus.Csharp.Asg.Nodes.Structure.JoinClauseSyntax.setLeftExpression(NodeId)", "The end point of the edge does not exist.");

                Columbus.Csharp.Asg.Nodes.Base.Base node = fact.getRef(nodeId);
                if (Common.getIsBaseClassKind(node.NodeKind, Types.NodeKind.ndkExpressionSyntax)) {
                    if (m_LeftExpression != 0) {
                        removeParentEdge(m_LeftExpression);
                    }
                    m_LeftExpression = nodeId;
                    setParentEdge(m_LeftExpression, (uint)Types.EdgeKind.edkJoinClauseSyntax_LeftExpression);
                } else {
                    throw new CsharpException("Columbus.Csharp.Asg.Nodes.Structure.JoinClauseSyntax.setLeftExpression(NodeId)", "Invalid NodeKind (" + node.NodeKind.ToString() + ").");
                }
            } else {
                if (m_LeftExpression != 0) {
                    removeParentEdge(m_LeftExpression);
                }
                m_LeftExpression = 0;
            }
        }

        /// <summary>
        /// Sets the LeftExpression edge.
        /// </summary>
        /// <param name="node">[in] The new end point of the LeftExpression edge.</param>
        /// <exception cref="Columbus.Csharp.Asg.CsharpException">Throws CsharpException if there's something wrong with the given node.</exception>
        public void setLeftExpression(Columbus.Csharp.Asg.Nodes.Expression.ExpressionSyntax node) {
            if (m_LeftExpression != 0) {
                removeParentEdge(m_LeftExpression);
            }
            m_LeftExpression = node.Id;
            setParentEdge(m_LeftExpression, (uint)Types.EdgeKind.edkJoinClauseSyntax_LeftExpression);
        }

        /// <summary>
        /// Sets the RightExpression edge.
        /// </summary>
        /// <param name="nodeId">[in] The new end point of the RightExpression edge or 0. With 0 the edge can be deleted.</param>
        /// <exception cref="Columbus.Csharp.Asg.CsharpException">Throws CsharpException if the nodeId is invalid.</exception>
        public void setRightExpression(uint nodeId) {
            if (nodeId != 0) {
                if (!fact.getExist(nodeId))
                    throw new CsharpException("Columbus.Csharp.Asg.Nodes.Structure.JoinClauseSyntax.setRightExpression(NodeId)", "The end point of the edge does not exist.");

                Columbus.Csharp.Asg.Nodes.Base.Base node = fact.getRef(nodeId);
                if (Common.getIsBaseClassKind(node.NodeKind, Types.NodeKind.ndkExpressionSyntax)) {
                    if (m_RightExpression != 0) {
                        removeParentEdge(m_RightExpression);
                    }
                    m_RightExpression = nodeId;
                    setParentEdge(m_RightExpression, (uint)Types.EdgeKind.edkJoinClauseSyntax_RightExpression);
                } else {
                    throw new CsharpException("Columbus.Csharp.Asg.Nodes.Structure.JoinClauseSyntax.setRightExpression(NodeId)", "Invalid NodeKind (" + node.NodeKind.ToString() + ").");
                }
            } else {
                if (m_RightExpression != 0) {
                    removeParentEdge(m_RightExpression);
                }
                m_RightExpression = 0;
            }
        }

        /// <summary>
        /// Sets the RightExpression edge.
        /// </summary>
        /// <param name="node">[in] The new end point of the RightExpression edge.</param>
        /// <exception cref="Columbus.Csharp.Asg.CsharpException">Throws CsharpException if there's something wrong with the given node.</exception>
        public void setRightExpression(Columbus.Csharp.Asg.Nodes.Expression.ExpressionSyntax node) {
            if (m_RightExpression != 0) {
                removeParentEdge(m_RightExpression);
            }
            m_RightExpression = node.Id;
            setParentEdge(m_RightExpression, (uint)Types.EdgeKind.edkJoinClauseSyntax_RightExpression);
        }

        /// <summary>
        /// Sets the Type edge.
        /// </summary>
        /// <param name="nodeId">[in] The new end point of the Type edge or 0. With 0 the edge can be deleted.</param>
        /// <exception cref="Columbus.Csharp.Asg.CsharpException">Throws CsharpException if the nodeId is invalid.</exception>
        public void setType(uint nodeId) {
            if (nodeId != 0) {
                if (!fact.getExist(nodeId))
                    throw new CsharpException("Columbus.Csharp.Asg.Nodes.Structure.JoinClauseSyntax.setType(NodeId)", "The end point of the edge does not exist.");

                Columbus.Csharp.Asg.Nodes.Base.Base node = fact.getRef(nodeId);
                if (Common.getIsBaseClassKind(node.NodeKind, Types.NodeKind.ndkTypeSyntax)) {
                    if (m_Type != 0) {
                        removeParentEdge(m_Type);
                    }
                    m_Type = nodeId;
                    setParentEdge(m_Type, (uint)Types.EdgeKind.edkJoinClauseSyntax_Type);
                } else {
                    throw new CsharpException("Columbus.Csharp.Asg.Nodes.Structure.JoinClauseSyntax.setType(NodeId)", "Invalid NodeKind (" + node.NodeKind.ToString() + ").");
                }
            } else {
                if (m_Type != 0) {
                    removeParentEdge(m_Type);
                }
                m_Type = 0;
            }
        }

        /// <summary>
        /// Sets the Type edge.
        /// </summary>
        /// <param name="node">[in] The new end point of the Type edge.</param>
        /// <exception cref="Columbus.Csharp.Asg.CsharpException">Throws CsharpException if there's something wrong with the given node.</exception>
        public void setType(Columbus.Csharp.Asg.Nodes.Expression.TypeSyntax node) {
            if (m_Type != 0) {
                removeParentEdge(m_Type);
            }
            m_Type = node.Id;
            setParentEdge(m_Type, (uint)Types.EdgeKind.edkJoinClauseSyntax_Type);
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

            io.writeUInt4(m_InExpression);
            io.writeUInt4(m_Into);
            io.writeUInt4(m_LeftExpression);
            io.writeUInt4(m_RightExpression);
            io.writeUInt4(m_Type);

        }

        /// <summary>
        /// Loads the node.
        /// </summary>
        /// <param name="io">[in] The node is read from io.</param>
        /// <exception cref="Columbus.ColumbusIOException">Throws ColumbusIOException if there is something wrong with the file.</exception>
        public override void load(IO binIo) {
            base.load(binIo);

            m_identifier = binIo.readUInt4();

            m_InExpression =  binIo.readUInt4();
            if (m_InExpression != 0)
              setParentEdge(m_InExpression,(uint)Types.EdgeKind.edkJoinClauseSyntax_InExpression);

            m_Into =  binIo.readUInt4();
            if (m_Into != 0)
              setParentEdge(m_Into,(uint)Types.EdgeKind.edkJoinClauseSyntax_Into);

            m_LeftExpression =  binIo.readUInt4();
            if (m_LeftExpression != 0)
              setParentEdge(m_LeftExpression,(uint)Types.EdgeKind.edkJoinClauseSyntax_LeftExpression);

            m_RightExpression =  binIo.readUInt4();
            if (m_RightExpression != 0)
              setParentEdge(m_RightExpression,(uint)Types.EdgeKind.edkJoinClauseSyntax_RightExpression);

            m_Type =  binIo.readUInt4();
            if (m_Type != 0)
              setParentEdge(m_Type,(uint)Types.EdgeKind.edkJoinClauseSyntax_Type);

        }

    }

}
