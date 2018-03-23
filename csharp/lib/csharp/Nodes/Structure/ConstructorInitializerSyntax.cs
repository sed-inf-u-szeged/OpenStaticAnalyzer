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
    /// ConstructorInitializerSyntax class, which represents the structure::ConstructorInitializerSyntax node.
    /// </summary>
    [DebuggerDisplay("{DemangledName}")]
#if (CSHARP_INTERNAL)
    internal
#else
    public
#endif
    class ConstructorInitializerSyntax : Columbus.Csharp.Asg.Nodes.Base.Positioned {


        // ---------- Edges ----------

        /// <summary>The id of the node the ArgumentList edge points to.</summary>
        protected uint m_ArgumentList;

        /// <summary>The id of the node the ConstructorCall edge points to.</summary>
        protected uint m_ConstructorCall;

        /// <summary>
        /// Constructor, only factory can instantiates nodes.
        /// </summary>
        /// <param name="nodeId">[in] The id of the node.</param>
        /// <param name="factory">[in] Poiter to the Factory the node belongs to.</param>
        public ConstructorInitializerSyntax(uint nodeId, Factory factory) : base(nodeId, factory) {
            m_ArgumentList = 0;
            m_ConstructorCall = 0;
        }

        /// <summary>
        /// Gives back the NodeKind of the node.
        /// </summary>
        /// <returns>Returns with the NodeKind.</returns>
        public override Types.NodeKind NodeKind {
            get { return Types.NodeKind.ndkConstructorInitializerSyntax; }
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
        /// Gives back the id of the node the ArgumentList edge points to.
        /// </summary>
        /// <returns>Returns the end point of the m_ArgumentList edge.</returns>
        /// <exception cref="Columbus.Csharp.Asg.CsharpException">Throws CsharpException if the edge id is invalid.</exception>
        public uint getArgumentList() {
            if (fact.getIsFiltered(m_ArgumentList))
                return 1;
            else
                return m_ArgumentList;
        }

        /// <summary>
        /// Gives back the id of the node the ConstructorCall edge points to.
        /// </summary>
        /// <returns>Returns the end point of the m_ConstructorCall edge.</returns>
        /// <exception cref="Columbus.Csharp.Asg.CsharpException">Throws CsharpException if the edge id is invalid.</exception>
        public uint getConstructorCall() {
            if (fact.getIsFiltered(m_ConstructorCall))
                return 1;
            else
                return m_ConstructorCall;
        }


        // ---------- Edge setter function(s) ----------

        /// <summary>
        /// Sets the ArgumentList edge.
        /// </summary>
        /// <param name="nodeId">[in] The new end point of the ArgumentList edge or 0. With 0 the edge can be deleted.</param>
        /// <exception cref="Columbus.Csharp.Asg.CsharpException">Throws CsharpException if the nodeId is invalid.</exception>
        public void setArgumentList(uint nodeId) {
            if (nodeId != 0) {
                if (!fact.getExist(nodeId))
                    throw new CsharpException("Columbus.Csharp.Asg.Nodes.Structure.ConstructorInitializerSyntax.setArgumentList(NodeId)", "The end point of the edge does not exist.");

                Columbus.Csharp.Asg.Nodes.Base.Base node = fact.getRef(nodeId);
                if (Common.getIsBaseClassKind(node.NodeKind, Types.NodeKind.ndkArgumentListSyntax)) {
                    if (m_ArgumentList != 0) {
                        removeParentEdge(m_ArgumentList);
                    }
                    m_ArgumentList = nodeId;
                    setParentEdge(m_ArgumentList, (uint)Types.EdgeKind.edkConstructorInitializerSyntax_ArgumentList);
                } else {
                    throw new CsharpException("Columbus.Csharp.Asg.Nodes.Structure.ConstructorInitializerSyntax.setArgumentList(NodeId)", "Invalid NodeKind (" + node.NodeKind.ToString() + ").");
                }
            } else {
                if (m_ArgumentList != 0) {
                    removeParentEdge(m_ArgumentList);
                }
                m_ArgumentList = 0;
            }
        }

        /// <summary>
        /// Sets the ArgumentList edge.
        /// </summary>
        /// <param name="node">[in] The new end point of the ArgumentList edge.</param>
        /// <exception cref="Columbus.Csharp.Asg.CsharpException">Throws CsharpException if there's something wrong with the given node.</exception>
        public void setArgumentList(Columbus.Csharp.Asg.Nodes.Structure.ArgumentListSyntax node) {
            if (m_ArgumentList != 0) {
                removeParentEdge(m_ArgumentList);
            }
            m_ArgumentList = node.Id;
            setParentEdge(m_ArgumentList, (uint)Types.EdgeKind.edkConstructorInitializerSyntax_ArgumentList);
        }

        /// <summary>
        /// Sets the ConstructorCall edge.
        /// </summary>
        /// <param name="nodeId">[in] The new end point of the ConstructorCall edge or 0. With 0 the edge can be deleted.</param>
        /// <exception cref="Columbus.Csharp.Asg.CsharpException">Throws CsharpException if the nodeId is invalid.</exception>
        public void setConstructorCall(uint nodeId) {
            if (nodeId != 0) {
                if (!fact.getExist(nodeId))
                    throw new CsharpException("Columbus.Csharp.Asg.Nodes.Structure.ConstructorInitializerSyntax.setConstructorCall(NodeId)", "The end point of the edge does not exist.");

                Columbus.Csharp.Asg.Nodes.Base.Base node = fact.getRef(nodeId);
                if (Common.getIsBaseClassKind(node.NodeKind, Types.NodeKind.ndkConstructorDeclarationSyntax)) {
                    if (m_ConstructorCall != 0) {
                    }
                    m_ConstructorCall = nodeId;
                } else {
                    throw new CsharpException("Columbus.Csharp.Asg.Nodes.Structure.ConstructorInitializerSyntax.setConstructorCall(NodeId)", "Invalid NodeKind (" + node.NodeKind.ToString() + ").");
                }
            } else {
                if (m_ConstructorCall != 0) {
                }
                m_ConstructorCall = 0;
            }
        }

        /// <summary>
        /// Sets the ConstructorCall edge.
        /// </summary>
        /// <param name="node">[in] The new end point of the ConstructorCall edge.</param>
        /// <exception cref="Columbus.Csharp.Asg.CsharpException">Throws CsharpException if there's something wrong with the given node.</exception>
        public void setConstructorCall(Columbus.Csharp.Asg.Nodes.Structure.ConstructorDeclarationSyntax node) {
            if (m_ConstructorCall != 0) {
            }
            m_ConstructorCall = node.Id;
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

            io.writeUInt4(m_ArgumentList);
            io.writeUInt4(m_ConstructorCall);

        }

        /// <summary>
        /// Loads the node.
        /// </summary>
        /// <param name="io">[in] The node is read from io.</param>
        /// <exception cref="Columbus.ColumbusIOException">Throws ColumbusIOException if there is something wrong with the file.</exception>
        public override void load(IO binIo) {
            base.load(binIo);

            m_ArgumentList =  binIo.readUInt4();
            if (m_ArgumentList != 0)
              setParentEdge(m_ArgumentList,(uint)Types.EdgeKind.edkConstructorInitializerSyntax_ArgumentList);

            m_ConstructorCall =  binIo.readUInt4();

        }

    }

}
