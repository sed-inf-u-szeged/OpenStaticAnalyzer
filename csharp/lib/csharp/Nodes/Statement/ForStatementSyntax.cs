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

namespace Columbus.Csharp.Asg.Nodes.Statement {

    /// <summary>
    /// ForStatementSyntax class, which represents the statement::ForStatementSyntax node.
    /// </summary>
    [DebuggerDisplay("{DemangledName}")]
#if (CSHARP_INTERNAL)
    internal
#else
    public
#endif
    class ForStatementSyntax : StatementSyntax {


        // ---------- Edges ----------

        /// <summary>The id of the node the Condition edge points to.</summary>
        protected uint m_Condition;

        /// <summary>The id of the node the Declaration edge points to.</summary>
        protected uint m_Declaration;

        /// <summary>Container stores the id of the nodes the Incrementors edge points to.</summary>
        protected LinkedList<uint> IncrementorsContainer;

        /// <summary>Container stores the id of the nodes the Initializers edge points to.</summary>
        protected LinkedList<uint> InitializersContainer;

        /// <summary>The id of the node the Statement edge points to.</summary>
        protected uint m_Statement;

        /// <summary>
        /// Constructor, only factory can instantiates nodes.
        /// </summary>
        /// <param name="nodeId">[in] The id of the node.</param>
        /// <param name="factory">[in] Poiter to the Factory the node belongs to.</param>
        public ForStatementSyntax(uint nodeId, Factory factory) : base(nodeId, factory) {
            m_Condition = 0;
            m_Declaration = 0;
            IncrementorsContainer = new LinkedList<uint>();
            InitializersContainer = new LinkedList<uint>();
            m_Statement = 0;
        }

        /// <summary>
        /// Gives back the NodeKind of the node.
        /// </summary>
        /// <returns>Returns with the NodeKind.</returns>
        public override Types.NodeKind NodeKind {
            get { return Types.NodeKind.ndkForStatementSyntax; }
        }


        // ---------- Reflection getter function ----------

        /// <summary>
        /// Gives back the begin iterator for the edge specified
        /// </summary>
        /// <param name="edge">[in] The multiple edge for which the iterator is requested</param>
        public override ListIterator<Columbus.Csharp.Asg.Nodes.Base.Base> GetListIteratorBegin(string edge) {
            switch(edge) {
                case "Incrementors":
                    return IncrementorsListIteratorBegin.Convert<Columbus.Csharp.Asg.Nodes.Base.Base>();
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
                case "Incrementors":
                    addIncrementors(nodeId);
                    return;
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
        /// Gives back the id of the node the Condition edge points to.
        /// </summary>
        /// <returns>Returns the end point of the m_Condition edge.</returns>
        /// <exception cref="Columbus.Csharp.Asg.CsharpException">Throws CsharpException if the edge id is invalid.</exception>
        public uint getCondition() {
            if (fact.getIsFiltered(m_Condition))
                return 1;
            else
                return m_Condition;
        }

        /// <summary>
        /// Gives back the id of the node the Declaration edge points to.
        /// </summary>
        /// <returns>Returns the end point of the m_Declaration edge.</returns>
        /// <exception cref="Columbus.Csharp.Asg.CsharpException">Throws CsharpException if the edge id is invalid.</exception>
        public uint getDeclaration() {
            if (fact.getIsFiltered(m_Declaration))
                return 1;
            else
                return m_Declaration;
        }

        /// <summary>
        /// Gives back iterator for the Incrementors edges.
        /// </summary>
        /// <returns>Returns an iterator for the Incrementors edges.</returns>
        public ListIterator<Columbus.Csharp.Asg.Nodes.Expression.ExpressionSyntax> IncrementorsListIteratorBegin {
            get {
                return new ListIterator<Columbus.Csharp.Asg.Nodes.Expression.ExpressionSyntax>(IncrementorsContainer, fact, true);
            }
        }

        /// <summary>
        /// Gives back iterator for the Incrementors edges.
        /// </summary>
        /// <returns>Returns an iterator for the Incrementors edges.</returns>
        public ListIterator<Columbus.Csharp.Asg.Nodes.Expression.ExpressionSyntax> IncrementorsListIteratorEnd {
            get {
                return new ListIterator<Columbus.Csharp.Asg.Nodes.Expression.ExpressionSyntax>(IncrementorsContainer, fact, false);
            }
        }

        /// <summary>
        /// Tells whether the node has Incrementors edges or not.
        /// </summary>
        /// <returns>Returns true if the node has at least one Incrementors edge.</returns>
        public bool IncrementorsIsEmpty {
            get { return IncrementorsContainer.Count == 0; }
        }

        /// <summary>
        /// Gives back how many Incrementors edges the node has.
        /// </summary>
        /// <returns>Returns with the number of Incrementors edges.</returns>
        public uint IncrementorsSize {
            get { return (uint)(IncrementorsContainer.Count); }
        }

        /// <summary>
        /// Gives back iterator for the Initializers edges.
        /// </summary>
        /// <returns>Returns an iterator for the Initializers edges.</returns>
        public ListIterator<Columbus.Csharp.Asg.Nodes.Expression.ExpressionSyntax> InitializersListIteratorBegin {
            get {
                return new ListIterator<Columbus.Csharp.Asg.Nodes.Expression.ExpressionSyntax>(InitializersContainer, fact, true);
            }
        }

        /// <summary>
        /// Gives back iterator for the Initializers edges.
        /// </summary>
        /// <returns>Returns an iterator for the Initializers edges.</returns>
        public ListIterator<Columbus.Csharp.Asg.Nodes.Expression.ExpressionSyntax> InitializersListIteratorEnd {
            get {
                return new ListIterator<Columbus.Csharp.Asg.Nodes.Expression.ExpressionSyntax>(InitializersContainer, fact, false);
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

        /// <summary>
        /// Gives back the id of the node the Statement edge points to.
        /// </summary>
        /// <returns>Returns the end point of the m_Statement edge.</returns>
        /// <exception cref="Columbus.Csharp.Asg.CsharpException">Throws CsharpException if the edge id is invalid.</exception>
        public uint getStatement() {
            if (fact.getIsFiltered(m_Statement))
                return 1;
            else
                return m_Statement;
        }


        // ---------- Edge setter function(s) ----------

        /// <summary>
        /// Sets the Condition edge.
        /// </summary>
        /// <param name="nodeId">[in] The new end point of the Condition edge or 0. With 0 the edge can be deleted.</param>
        /// <exception cref="Columbus.Csharp.Asg.CsharpException">Throws CsharpException if the nodeId is invalid.</exception>
        public void setCondition(uint nodeId) {
            if (nodeId != 0) {
                if (!fact.getExist(nodeId))
                    throw new CsharpException("Columbus.Csharp.Asg.Nodes.Statement.ForStatementSyntax.setCondition(NodeId)", "The end point of the edge does not exist.");

                Columbus.Csharp.Asg.Nodes.Base.Base node = fact.getRef(nodeId);
                if (Common.getIsBaseClassKind(node.NodeKind, Types.NodeKind.ndkExpressionSyntax)) {
                    if (m_Condition != 0) {
                        removeParentEdge(m_Condition);
                    }
                    m_Condition = nodeId;
                    setParentEdge(m_Condition, (uint)Types.EdgeKind.edkForStatementSyntax_Condition);
                } else {
                    throw new CsharpException("Columbus.Csharp.Asg.Nodes.Statement.ForStatementSyntax.setCondition(NodeId)", "Invalid NodeKind (" + node.NodeKind.ToString() + ").");
                }
            } else {
                if (m_Condition != 0) {
                    removeParentEdge(m_Condition);
                }
                m_Condition = 0;
            }
        }

        /// <summary>
        /// Sets the Condition edge.
        /// </summary>
        /// <param name="node">[in] The new end point of the Condition edge.</param>
        /// <exception cref="Columbus.Csharp.Asg.CsharpException">Throws CsharpException if there's something wrong with the given node.</exception>
        public void setCondition(Columbus.Csharp.Asg.Nodes.Expression.ExpressionSyntax node) {
            if (m_Condition != 0) {
                removeParentEdge(m_Condition);
            }
            m_Condition = node.Id;
            setParentEdge(m_Condition, (uint)Types.EdgeKind.edkForStatementSyntax_Condition);
        }

        /// <summary>
        /// Sets the Declaration edge.
        /// </summary>
        /// <param name="nodeId">[in] The new end point of the Declaration edge or 0. With 0 the edge can be deleted.</param>
        /// <exception cref="Columbus.Csharp.Asg.CsharpException">Throws CsharpException if the nodeId is invalid.</exception>
        public void setDeclaration(uint nodeId) {
            if (nodeId != 0) {
                if (!fact.getExist(nodeId))
                    throw new CsharpException("Columbus.Csharp.Asg.Nodes.Statement.ForStatementSyntax.setDeclaration(NodeId)", "The end point of the edge does not exist.");

                Columbus.Csharp.Asg.Nodes.Base.Base node = fact.getRef(nodeId);
                if (Common.getIsBaseClassKind(node.NodeKind, Types.NodeKind.ndkVariableDeclarationSyntax)) {
                    if (m_Declaration != 0) {
                        removeParentEdge(m_Declaration);
                    }
                    m_Declaration = nodeId;
                    setParentEdge(m_Declaration, (uint)Types.EdgeKind.edkForStatementSyntax_Declaration);
                } else {
                    throw new CsharpException("Columbus.Csharp.Asg.Nodes.Statement.ForStatementSyntax.setDeclaration(NodeId)", "Invalid NodeKind (" + node.NodeKind.ToString() + ").");
                }
            } else {
                if (m_Declaration != 0) {
                    removeParentEdge(m_Declaration);
                }
                m_Declaration = 0;
            }
        }

        /// <summary>
        /// Sets the Declaration edge.
        /// </summary>
        /// <param name="node">[in] The new end point of the Declaration edge.</param>
        /// <exception cref="Columbus.Csharp.Asg.CsharpException">Throws CsharpException if there's something wrong with the given node.</exception>
        public void setDeclaration(Columbus.Csharp.Asg.Nodes.Structure.VariableDeclarationSyntax node) {
            if (m_Declaration != 0) {
                removeParentEdge(m_Declaration);
            }
            m_Declaration = node.Id;
            setParentEdge(m_Declaration, (uint)Types.EdgeKind.edkForStatementSyntax_Declaration);
        }

        /// <summary>
        /// Adds a new Incrementors edge to the node and inserts it after the other ones.
        /// </summary>
        /// <param name="node">[in] The end point of the new Incrementors edge.</param>
        /// <exception cref="Columbus.Csharp.Asg.CsharpException">Throws CsharpException if there is something wrong with the given node.</exception>
        public void addIncrementors(Columbus.Csharp.Asg.Nodes.Expression.ExpressionSyntax node) {
            addIncrementors(node.Id);
        }

        /// <summary>
        /// Adds a new Incrementors edge to the node and inserts it after the other ones.
        /// </summary>
        /// <param name="nodeId">[in] The end point of the new Incrementors edge.</param>
        /// <exception cref="Columbus.Csharp.Asg.CsharpException">Throws CsharpException if the given nodeId is invalid.</exception>
        public void addIncrementors(uint nodeId) {
            if (!fact.getExist(nodeId))
                throw new CsharpException("Columbus.Csharp.Asg.Nodes.Statement.ForStatementSyntax.addIncrementors(NodeId)", "The end point of the edge does not exist.");
            Columbus.Csharp.Asg.Nodes.Base.Base node = fact.getRef(nodeId);
            if (Common.getIsBaseClassKind(node.NodeKind, Types.NodeKind.ndkExpressionSyntax)) {
                IncrementorsContainer.AddLast(nodeId);
            } else {
                throw new CsharpException("Columbus.Csharp.Asg.Nodes.Statement.ForStatementSyntax.setIncrementors(NodeId)", "Invalid NodeKind (" + node.NodeKind.ToString() + ").");
            }
           setParentEdge(nodeId, (uint)Types.EdgeKind.edkForStatementSyntax_Incrementors);
            if (fact.ReverseEdges != null)
              fact.ReverseEdges.insertEdge(nodeId, this.Id, Types.EdgeKind.edkForStatementSyntax_Incrementors);
        }

        /// <summary>
        /// Adds a new Initializers edge to the node and inserts it after the other ones.
        /// </summary>
        /// <param name="node">[in] The end point of the new Initializers edge.</param>
        /// <exception cref="Columbus.Csharp.Asg.CsharpException">Throws CsharpException if there is something wrong with the given node.</exception>
        public void addInitializers(Columbus.Csharp.Asg.Nodes.Expression.ExpressionSyntax node) {
            addInitializers(node.Id);
        }

        /// <summary>
        /// Adds a new Initializers edge to the node and inserts it after the other ones.
        /// </summary>
        /// <param name="nodeId">[in] The end point of the new Initializers edge.</param>
        /// <exception cref="Columbus.Csharp.Asg.CsharpException">Throws CsharpException if the given nodeId is invalid.</exception>
        public void addInitializers(uint nodeId) {
            if (!fact.getExist(nodeId))
                throw new CsharpException("Columbus.Csharp.Asg.Nodes.Statement.ForStatementSyntax.addInitializers(NodeId)", "The end point of the edge does not exist.");
            Columbus.Csharp.Asg.Nodes.Base.Base node = fact.getRef(nodeId);
            if (Common.getIsBaseClassKind(node.NodeKind, Types.NodeKind.ndkExpressionSyntax)) {
                InitializersContainer.AddLast(nodeId);
            } else {
                throw new CsharpException("Columbus.Csharp.Asg.Nodes.Statement.ForStatementSyntax.setInitializers(NodeId)", "Invalid NodeKind (" + node.NodeKind.ToString() + ").");
            }
           setParentEdge(nodeId, (uint)Types.EdgeKind.edkForStatementSyntax_Initializers);
            if (fact.ReverseEdges != null)
              fact.ReverseEdges.insertEdge(nodeId, this.Id, Types.EdgeKind.edkForStatementSyntax_Initializers);
        }

        /// <summary>
        /// Sets the Statement edge.
        /// </summary>
        /// <param name="nodeId">[in] The new end point of the Statement edge or 0. With 0 the edge can be deleted.</param>
        /// <exception cref="Columbus.Csharp.Asg.CsharpException">Throws CsharpException if the nodeId is invalid.</exception>
        public void setStatement(uint nodeId) {
            if (nodeId != 0) {
                if (!fact.getExist(nodeId))
                    throw new CsharpException("Columbus.Csharp.Asg.Nodes.Statement.ForStatementSyntax.setStatement(NodeId)", "The end point of the edge does not exist.");

                Columbus.Csharp.Asg.Nodes.Base.Base node = fact.getRef(nodeId);
                if (Common.getIsBaseClassKind(node.NodeKind, Types.NodeKind.ndkStatementSyntax)) {
                    if (m_Statement != 0) {
                        removeParentEdge(m_Statement);
                    }
                    m_Statement = nodeId;
                    setParentEdge(m_Statement, (uint)Types.EdgeKind.edkForStatementSyntax_Statement);
                } else {
                    throw new CsharpException("Columbus.Csharp.Asg.Nodes.Statement.ForStatementSyntax.setStatement(NodeId)", "Invalid NodeKind (" + node.NodeKind.ToString() + ").");
                }
            } else {
                if (m_Statement != 0) {
                    removeParentEdge(m_Statement);
                }
                m_Statement = 0;
            }
        }

        /// <summary>
        /// Sets the Statement edge.
        /// </summary>
        /// <param name="node">[in] The new end point of the Statement edge.</param>
        /// <exception cref="Columbus.Csharp.Asg.CsharpException">Throws CsharpException if there's something wrong with the given node.</exception>
        public void setStatement(Columbus.Csharp.Asg.Nodes.Statement.StatementSyntax node) {
            if (m_Statement != 0) {
                removeParentEdge(m_Statement);
            }
            m_Statement = node.Id;
            setParentEdge(m_Statement, (uint)Types.EdgeKind.edkForStatementSyntax_Statement);
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

            io.writeUInt4(m_Condition);
            io.writeUInt4(m_Declaration);
            io.writeUInt4(m_Statement);


            foreach (var Incrementors in IncrementorsContainer) {
              io.writeUInt4(Incrementors);
            }
            io.writeUInt4(0); // This is the end sign

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

            m_Condition =  binIo.readUInt4();
            if (m_Condition != 0)
              setParentEdge(m_Condition,(uint)Types.EdgeKind.edkForStatementSyntax_Condition);

            m_Declaration =  binIo.readUInt4();
            if (m_Declaration != 0)
              setParentEdge(m_Declaration,(uint)Types.EdgeKind.edkForStatementSyntax_Declaration);

            m_Statement =  binIo.readUInt4();
            if (m_Statement != 0)
              setParentEdge(m_Statement,(uint)Types.EdgeKind.edkForStatementSyntax_Statement);

            uint _id;

            _id = binIo.readUInt4();
            while (_id != 0) {
              IncrementorsContainer.AddLast(_id);
              setParentEdge(_id, (uint)Types.EdgeKind.edkForStatementSyntax_Incrementors);
              _id = binIo.readUInt4();
            }

            _id = binIo.readUInt4();
            while (_id != 0) {
              InitializersContainer.AddLast(_id);
              setParentEdge(_id, (uint)Types.EdgeKind.edkForStatementSyntax_Initializers);
              _id = binIo.readUInt4();
            }
        }

    }

}
