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
    /// Member class, which represents the logical::Member node.
    /// </summary>
    [DebuggerDisplay("{DemangledName}")]
#if (LIM_INTERNAL)
    internal
#else
    public
#endif
    class Member : Columbus.Lim.Asg.Nodes.Base.Named {

        /// <summary>The AccessibilityKind of the node.</summary>
        protected Types.AccessibilityKind m_accessibility;

        /// <summary>The value of the `commentLines`.</summary>
        protected uint m_commentLines;

        /// <summary>The Key of the `demangledName`.</summary>
        protected uint m_demangledName;

        /// <summary>Stores whether the node is `CompilerGenerated` or not.</summary>
        protected bool m_isCompilerGenerated;

        /// <summary>Stores whether the node is `Static` or not.</summary>
        protected bool m_isStatic;

        /// <summary>The LanguageKind of the node.</summary>
        protected Types.LanguageKind m_language;

        /// <summary>The Key of the `mangledName`.</summary>
        protected uint m_mangledName;


        // ---------- Edges ----------

        /// <summary>The id of the node the aggregated edge points to.</summary>
        protected uint m_aggregated;

        /// <summary>Container stores the id of the nodes the belongsTo edge points to.</summary>
        protected LinkedList<uint> belongsToContainer;

        /// <summary>Container stores the id of the nodes the compilationUnit edge points to.</summary>
        protected LinkedList<uint> compilationUnitContainer;

        /// <summary>The id of the node the declares edge points to.</summary>
        protected uint m_declares;

        /// <summary>Container stores the id of the nodes the hasComment edge points to.</summary>
        protected LinkedList<uint> hasCommentContainer;

        /// <summary>Container stores the id of the nodes the instance edge points to.</summary>
        protected LinkedList<uint> instanceContainer;

        /// <summary>Container stores the id of the nodes the isContainedIn edge points to and the association classes.</summary>
        protected LinkedList<ListIteratorAssoc<Columbus.Lim.Asg.Nodes.Physical.File>.AssocEdge> isContainedInAssocContainer;

        /// <summary>The id of the node the languageVariant edge points to.</summary>
        protected uint m_languageVariant;

        /// <summary>Container stores the id of the nodes the uses edge points to.</summary>
        protected LinkedList<uint> usesContainer;

        /// <summary>Container stores the id of the nodes the variant edge points to.</summary>
        protected LinkedList<uint> variantContainer;

        /// <summary>
        /// Constructor, only factory can instantiates nodes.
        /// </summary>
        /// <param name="nodeId">[in] The id of the node.</param>
        /// <param name="factory">[in] Poiter to the Factory the node belongs to.</param>
        public Member(uint nodeId, Factory factory) : base(nodeId, factory) {
            m_accessibility = Types.AccessibilityKind.ackInternal;
            m_commentLines = 0;
            m_demangledName = 0;
            m_isCompilerGenerated = false;
            m_isStatic = false;
            m_language = Types.LanguageKind.lnkNotSet;
            m_mangledName = 0;
            m_aggregated = 0;
            belongsToContainer = new LinkedList<uint>();
            compilationUnitContainer = new LinkedList<uint>();
            m_declares = 0;
            hasCommentContainer = new LinkedList<uint>();
            instanceContainer = new LinkedList<uint>();
            isContainedInAssocContainer = new LinkedList<ListIteratorAssoc<Columbus.Lim.Asg.Nodes.Physical.File>.AssocEdge>();
            m_languageVariant = 0;
            usesContainer = new LinkedList<uint>();
            variantContainer = new LinkedList<uint>();
        }

        /// <summary>
        /// Gives back the NodeKind of the node.
        /// </summary>
        /// <returns>Returns with the NodeKind.</returns>
        public override Types.NodeKind NodeKind {
            get { return Types.NodeKind.ndkMember; }
        }


        // ---------- Attribute propert(y)(ies) ----------

        /// <summary>
        /// Gives back the accessibility of the node.
        /// </summary>
        /// <returns>Returns with the accessibility.</returns>
        public Types.AccessibilityKind Accessibility
        {
            get
            {
                return m_accessibility;
            }
            set
            {
                m_accessibility = value;
            }
        }

        /// <summary>
        /// Gives back the commentLines of the node.
        /// </summary>
        /// <returns>Returns with the commentLines.</returns>
        public uint CommentLines
        {
            get
            {
                return m_commentLines;
            }
            set
            {
                m_commentLines = value;
            }
        }

        /// <summary>
        /// Gives back or sets the demangledName of the node.
        /// </summary>
        public string DemangledName
        {
            get
            {
                return fact.StringTable.get(m_demangledName);
            }
            set
            {
                m_demangledName = fact.StringTable.set( value );
            }
        }

        /// <summary>
        /// Gives back or sets the Key of demangledName of the node.
        /// </summary>
        public uint DemangledNameKey
        {
            get
            {
                return m_demangledName;
            }
            set
            {
               m_demangledName = value;
            }
        }

        /// <summary>
        /// Gives back the isCompilerGenerated of the node.
        /// </summary>
        /// <returns>Returns with the isCompilerGenerated.</returns>
        public bool IsCompilerGenerated
        {
            get
            {
                return m_isCompilerGenerated;
            }
            set
            {
                m_isCompilerGenerated = value;
            }
        }

        /// <summary>
        /// Gives back the isStatic of the node.
        /// </summary>
        /// <returns>Returns with the isStatic.</returns>
        public bool IsStatic
        {
            get
            {
                return m_isStatic;
            }
            set
            {
                m_isStatic = value;
            }
        }

        /// <summary>
        /// Gives back the language of the node.
        /// </summary>
        /// <returns>Returns with the language.</returns>
        public Types.LanguageKind Language
        {
            get
            {
                return m_language;
            }
            set
            {
                m_language = value;
            }
        }

        /// <summary>
        /// Gives back or sets the mangledName of the node.
        /// </summary>
        public string MangledName
        {
            get
            {
                return fact.StringTable.get(m_mangledName);
            }
            set
            {
                m_mangledName = fact.StringTable.set( value );
            }
        }

        /// <summary>
        /// Gives back or sets the Key of mangledName of the node.
        /// </summary>
        public uint MangledNameKey
        {
            get
            {
                return m_mangledName;
            }
            set
            {
               m_mangledName = value;
            }
        }


        // ---------- Reflection getter function ----------

        /// <summary>
        /// Gives back the begin iterator for the edge specified
        /// </summary>
        /// <param name="edge">[in] The multiple edge for which the iterator is requested</param>
        public override ListIterator<Columbus.Lim.Asg.Nodes.Base.Base> GetListIteratorBegin(string edge) {
            switch(edge) {
                case "BelongsTo":
                    return BelongsToListIteratorBegin.Convert<Columbus.Lim.Asg.Nodes.Base.Base>();
                case "CompilationUnit":
                    return CompilationUnitListIteratorBegin.Convert<Columbus.Lim.Asg.Nodes.Base.Base>();
                case "HasComment":
                    return HasCommentListIteratorBegin.Convert<Columbus.Lim.Asg.Nodes.Base.Base>();
                case "Instance":
                    return InstanceListIteratorBegin.Convert<Columbus.Lim.Asg.Nodes.Base.Base>();
                case "Uses":
                    return UsesListIteratorBegin.Convert<Columbus.Lim.Asg.Nodes.Base.Base>();
                case "Variant":
                    return VariantListIteratorBegin.Convert<Columbus.Lim.Asg.Nodes.Base.Base>();
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
                case "BelongsTo":
                    addBelongsTo(nodeId);
                    return;
                case "CompilationUnit":
                    addCompilationUnit(nodeId);
                    return;
                case "HasComment":
                    addHasComment(nodeId);
                    return;
                case "Instance":
                    addInstance(nodeId);
                    return;
                case "Uses":
                    addUses(nodeId);
                    return;
                case "Variant":
                    addVariant(nodeId);
                    return;
                default:
                    base.add(edge, nodeId);
                    return;
            }
        }


        // ---------- Edge getter function(s) ----------

        /// <summary>
        /// Gives back the id of the node the aggregated edge points to.
        /// </summary>
        /// <returns>Returns the end point of the m_aggregated edge.</returns>
        /// <exception cref="Columbus.Lim.Asg.LimException">Throws LimException if the edge id is invalid.</exception>
        public uint getAggregated() {
            if (fact.getIsFiltered(m_aggregated))
                return 1;
            else
                return m_aggregated;
        }

        /// <summary>
        /// Gives back iterator for the belongsTo edges.
        /// </summary>
        /// <returns>Returns an iterator for the belongsTo edges.</returns>
        public ListIterator<Columbus.Lim.Asg.Nodes.Base.Component> BelongsToListIteratorBegin {
            get {
                return new ListIterator<Columbus.Lim.Asg.Nodes.Base.Component>(belongsToContainer, fact, true);
            }
        }

        /// <summary>
        /// Gives back iterator for the belongsTo edges.
        /// </summary>
        /// <returns>Returns an iterator for the belongsTo edges.</returns>
        public ListIterator<Columbus.Lim.Asg.Nodes.Base.Component> BelongsToListIteratorEnd {
            get {
                return new ListIterator<Columbus.Lim.Asg.Nodes.Base.Component>(belongsToContainer, fact, false);
            }
        }

        /// <summary>
        /// Tells whether the node has belongsTo edges or not.
        /// </summary>
        /// <returns>Returns true if the node has at least one belongsTo edge.</returns>
        public bool BelongsToIsEmpty {
            get { return belongsToContainer.Count == 0; }
        }

        /// <summary>
        /// Gives back how many belongsTo edges the node has.
        /// </summary>
        /// <returns>Returns with the number of belongsTo edges.</returns>
        public uint BelongsToSize {
            get { return (uint)(belongsToContainer.Count); }
        }

        /// <summary>
        /// Gives back iterator for the compilationUnit edges.
        /// </summary>
        /// <returns>Returns an iterator for the compilationUnit edges.</returns>
        public ListIterator<Columbus.Lim.Asg.Nodes.Physical.File> CompilationUnitListIteratorBegin {
            get {
                return new ListIterator<Columbus.Lim.Asg.Nodes.Physical.File>(compilationUnitContainer, fact, true);
            }
        }

        /// <summary>
        /// Gives back iterator for the compilationUnit edges.
        /// </summary>
        /// <returns>Returns an iterator for the compilationUnit edges.</returns>
        public ListIterator<Columbus.Lim.Asg.Nodes.Physical.File> CompilationUnitListIteratorEnd {
            get {
                return new ListIterator<Columbus.Lim.Asg.Nodes.Physical.File>(compilationUnitContainer, fact, false);
            }
        }

        /// <summary>
        /// Tells whether the node has compilationUnit edges or not.
        /// </summary>
        /// <returns>Returns true if the node has at least one compilationUnit edge.</returns>
        public bool CompilationUnitIsEmpty {
            get { return compilationUnitContainer.Count == 0; }
        }

        /// <summary>
        /// Gives back how many compilationUnit edges the node has.
        /// </summary>
        /// <returns>Returns with the number of compilationUnit edges.</returns>
        public uint CompilationUnitSize {
            get { return (uint)(compilationUnitContainer.Count); }
        }

        /// <summary>
        /// Gives back the id of the node the declares edge points to.
        /// </summary>
        /// <returns>Returns the end point of the m_declares edge.</returns>
        /// <exception cref="Columbus.Lim.Asg.LimException">Throws LimException if the edge id is invalid.</exception>
        public uint getDeclares() {
            if (fact.getIsFiltered(m_declares))
                return 1;
            else
                return m_declares;
        }

        /// <summary>
        /// Gives back iterator for the hasComment edges.
        /// </summary>
        /// <returns>Returns an iterator for the hasComment edges.</returns>
        public ListIterator<Columbus.Lim.Asg.Nodes.Base.Comment> HasCommentListIteratorBegin {
            get {
                return new ListIterator<Columbus.Lim.Asg.Nodes.Base.Comment>(hasCommentContainer, fact, true);
            }
        }

        /// <summary>
        /// Gives back iterator for the hasComment edges.
        /// </summary>
        /// <returns>Returns an iterator for the hasComment edges.</returns>
        public ListIterator<Columbus.Lim.Asg.Nodes.Base.Comment> HasCommentListIteratorEnd {
            get {
                return new ListIterator<Columbus.Lim.Asg.Nodes.Base.Comment>(hasCommentContainer, fact, false);
            }
        }

        /// <summary>
        /// Tells whether the node has hasComment edges or not.
        /// </summary>
        /// <returns>Returns true if the node has at least one hasComment edge.</returns>
        public bool HasCommentIsEmpty {
            get { return hasCommentContainer.Count == 0; }
        }

        /// <summary>
        /// Gives back how many hasComment edges the node has.
        /// </summary>
        /// <returns>Returns with the number of hasComment edges.</returns>
        public uint HasCommentSize {
            get { return (uint)(hasCommentContainer.Count); }
        }

        /// <summary>
        /// Gives back iterator for the instance edges.
        /// </summary>
        /// <returns>Returns an iterator for the instance edges.</returns>
        public ListIterator<Columbus.Lim.Asg.Nodes.Logical.Member> InstanceListIteratorBegin {
            get {
                return new ListIterator<Columbus.Lim.Asg.Nodes.Logical.Member>(instanceContainer, fact, true);
            }
        }

        /// <summary>
        /// Gives back iterator for the instance edges.
        /// </summary>
        /// <returns>Returns an iterator for the instance edges.</returns>
        public ListIterator<Columbus.Lim.Asg.Nodes.Logical.Member> InstanceListIteratorEnd {
            get {
                return new ListIterator<Columbus.Lim.Asg.Nodes.Logical.Member>(instanceContainer, fact, false);
            }
        }

        /// <summary>
        /// Tells whether the node has instance edges or not.
        /// </summary>
        /// <returns>Returns true if the node has at least one instance edge.</returns>
        public bool InstanceIsEmpty {
            get { return instanceContainer.Count == 0; }
        }

        /// <summary>
        /// Gives back how many instance edges the node has.
        /// </summary>
        /// <returns>Returns with the number of instance edges.</returns>
        public uint InstanceSize {
            get { return (uint)(instanceContainer.Count); }
        }

        /// <summary>
        /// Gives back iterator for the isContainedIn edges.
        /// </summary>
        /// <returns>Returns an iterator for the isContainedIn edges.</returns>
        public ListIteratorAssocSourcePosition<Columbus.Lim.Asg.Nodes.Physical.File> IsContainedInListIteratorAssocBegin {
            get {
                return new ListIteratorAssocSourcePosition<Columbus.Lim.Asg.Nodes.Physical.File>(isContainedInAssocContainer, fact, true);
            }
        }

        /// <summary>
        /// Gives back iterator for the isContainedIn edges.
        /// </summary>
        /// <returns>Returns an iterator for the isContainedIn edges.</returns>
        public ListIteratorAssocSourcePosition<Columbus.Lim.Asg.Nodes.Physical.File> IsContainedInListIteratorAssocEnd {
            get {
                return new ListIteratorAssocSourcePosition<Columbus.Lim.Asg.Nodes.Physical.File>(isContainedInAssocContainer, fact, false);
            }
        }

        /// <summary>
        /// Tells whether the node has isContainedIn edges or not.
        /// </summary>
        /// <returns>Returns true if the node has at least one isContainedIn edge.</returns>
        public bool IsContainedInIsEmpty {
            get { return isContainedInAssocContainer.Count == 0; }
        }

        /// <summary>
        /// Gives back how many isContainedIn edges the node has.
        /// </summary>
        /// <returns>Returns with the number of isContainedIn edges.</returns>
        public uint IsContainedInSize {
            get { return (uint)(isContainedInAssocContainer.Count); }
        }

        /// <summary>
        /// Gives back the id of the node the languageVariant edge points to.
        /// </summary>
        /// <returns>Returns the end point of the m_languageVariant edge.</returns>
        /// <exception cref="Columbus.Lim.Asg.LimException">Throws LimException if the edge id is invalid.</exception>
        public uint getLanguageVariant() {
            if (fact.getIsFiltered(m_languageVariant))
                return 1;
            else
                return m_languageVariant;
        }

        /// <summary>
        /// Gives back iterator for the uses edges.
        /// </summary>
        /// <returns>Returns an iterator for the uses edges.</returns>
        public ListIterator<Columbus.Lim.Asg.Nodes.Type.Type> UsesListIteratorBegin {
            get {
                return new ListIterator<Columbus.Lim.Asg.Nodes.Type.Type>(usesContainer, fact, true);
            }
        }

        /// <summary>
        /// Gives back iterator for the uses edges.
        /// </summary>
        /// <returns>Returns an iterator for the uses edges.</returns>
        public ListIterator<Columbus.Lim.Asg.Nodes.Type.Type> UsesListIteratorEnd {
            get {
                return new ListIterator<Columbus.Lim.Asg.Nodes.Type.Type>(usesContainer, fact, false);
            }
        }

        /// <summary>
        /// Tells whether the node has uses edges or not.
        /// </summary>
        /// <returns>Returns true if the node has at least one uses edge.</returns>
        public bool UsesIsEmpty {
            get { return usesContainer.Count == 0; }
        }

        /// <summary>
        /// Gives back how many uses edges the node has.
        /// </summary>
        /// <returns>Returns with the number of uses edges.</returns>
        public uint UsesSize {
            get { return (uint)(usesContainer.Count); }
        }

        /// <summary>
        /// Gives back iterator for the variant edges.
        /// </summary>
        /// <returns>Returns an iterator for the variant edges.</returns>
        public ListIterator<Columbus.Lim.Asg.Nodes.Logical.Member> VariantListIteratorBegin {
            get {
                return new ListIterator<Columbus.Lim.Asg.Nodes.Logical.Member>(variantContainer, fact, true);
            }
        }

        /// <summary>
        /// Gives back iterator for the variant edges.
        /// </summary>
        /// <returns>Returns an iterator for the variant edges.</returns>
        public ListIterator<Columbus.Lim.Asg.Nodes.Logical.Member> VariantListIteratorEnd {
            get {
                return new ListIterator<Columbus.Lim.Asg.Nodes.Logical.Member>(variantContainer, fact, false);
            }
        }

        /// <summary>
        /// Tells whether the node has variant edges or not.
        /// </summary>
        /// <returns>Returns true if the node has at least one variant edge.</returns>
        public bool VariantIsEmpty {
            get { return variantContainer.Count == 0; }
        }

        /// <summary>
        /// Gives back how many variant edges the node has.
        /// </summary>
        /// <returns>Returns with the number of variant edges.</returns>
        public uint VariantSize {
            get { return (uint)(variantContainer.Count); }
        }


        // ---------- Edge setter function(s) ----------

        /// <summary>
        /// Sets the aggregated edge.
        /// </summary>
        /// <param name="nodeId">[in] The new end point of the aggregated edge or 0. With 0 the edge can be deleted.</param>
        /// <exception cref="Columbus.Lim.Asg.LimException">Throws LimException if the nodeId is invalid.</exception>
        public void setAggregated(uint nodeId) {
            if (nodeId != 0) {
                if (!fact.getExist(nodeId))
                    throw new LimException("Columbus.Lim.Asg.Nodes.Logical.Member.setAggregated(NodeId)", "The end point of the edge does not exist.");

                Columbus.Lim.Asg.Nodes.Base.Base node = fact.getRef(nodeId);
                if (Common.getIsBaseClassKind(node.NodeKind, Types.NodeKind.ndkMember)) {
                    if (m_aggregated != 0) {
                    }
                    m_aggregated = nodeId;
                } else {
                    throw new LimException("Columbus.Lim.Asg.Nodes.Logical.Member.setAggregated(NodeId)", "Invalid NodeKind (" + node.NodeKind.ToString() + ").");
                }
            } else {
                if (m_aggregated != 0) {
                }
                m_aggregated = 0;
            }
        }

        /// <summary>
        /// Sets the aggregated edge.
        /// </summary>
        /// <param name="node">[in] The new end point of the aggregated edge.</param>
        /// <exception cref="Columbus.Lim.Asg.LimException">Throws LimException if there's something wrong with the given node.</exception>
        public void setAggregated(Columbus.Lim.Asg.Nodes.Logical.Member node) {
            if (m_aggregated != 0) {
            }
            m_aggregated = node.Id;
        }

        /// <summary>
        /// Adds a new belongsTo edge to the node and inserts it after the other ones.
        /// </summary>
        /// <param name="node">[in] The end point of the new belongsTo edge.</param>
        /// <exception cref="Columbus.Lim.Asg.LimException">Throws LimException if there is something wrong with the given node.</exception>
        public void addBelongsTo(Columbus.Lim.Asg.Nodes.Base.Component node) {
            addBelongsTo(node.Id);
        }

        /// <summary>
        /// Adds a new belongsTo edge to the node and inserts it after the other ones.
        /// </summary>
        /// <param name="nodeId">[in] The end point of the new belongsTo edge.</param>
        /// <exception cref="Columbus.Lim.Asg.LimException">Throws LimException if the given nodeId is invalid.</exception>
        public void addBelongsTo(uint nodeId) {
            if (!fact.getExist(nodeId))
                throw new LimException("Columbus.Lim.Asg.Nodes.Logical.Member.addBelongsTo(NodeId)", "The end point of the edge does not exist.");
            Columbus.Lim.Asg.Nodes.Base.Base node = fact.getRef(nodeId);
            if (Common.getIsBaseClassKind(node.NodeKind, Types.NodeKind.ndkComponent)) {
                belongsToContainer.AddLast(nodeId);
            } else {
                throw new LimException("Columbus.Lim.Asg.Nodes.Logical.Member.setBelongsTo(NodeId)", "Invalid NodeKind (" + node.NodeKind.ToString() + ").");
            }
            if (fact.ReverseEdges != null)
              fact.ReverseEdges.insertEdge(nodeId, this.Id, Types.EdgeKind.edkMember_BelongsTo);
        }

        /// <summary>
        /// Adds a new compilationUnit edge to the node and inserts it after the other ones.
        /// </summary>
        /// <param name="node">[in] The end point of the new compilationUnit edge.</param>
        /// <exception cref="Columbus.Lim.Asg.LimException">Throws LimException if there is something wrong with the given node.</exception>
        public void addCompilationUnit(Columbus.Lim.Asg.Nodes.Physical.File node) {
            addCompilationUnit(node.Id);
        }

        /// <summary>
        /// Adds a new compilationUnit edge to the node and inserts it after the other ones.
        /// </summary>
        /// <param name="nodeId">[in] The end point of the new compilationUnit edge.</param>
        /// <exception cref="Columbus.Lim.Asg.LimException">Throws LimException if the given nodeId is invalid.</exception>
        public void addCompilationUnit(uint nodeId) {
            if (!fact.getExist(nodeId))
                throw new LimException("Columbus.Lim.Asg.Nodes.Logical.Member.addCompilationUnit(NodeId)", "The end point of the edge does not exist.");
            Columbus.Lim.Asg.Nodes.Base.Base node = fact.getRef(nodeId);
            if (Common.getIsBaseClassKind(node.NodeKind, Types.NodeKind.ndkFile)) {
                compilationUnitContainer.AddLast(nodeId);
            } else {
                throw new LimException("Columbus.Lim.Asg.Nodes.Logical.Member.setCompilationUnit(NodeId)", "Invalid NodeKind (" + node.NodeKind.ToString() + ").");
            }
            if (fact.ReverseEdges != null)
              fact.ReverseEdges.insertEdge(nodeId, this.Id, Types.EdgeKind.edkMember_CompilationUnit);
        }

        /// <summary>
        /// Sets the declares edge.
        /// </summary>
        /// <param name="nodeId">[in] The new end point of the declares edge or 0. With 0 the edge can be deleted.</param>
        /// <exception cref="Columbus.Lim.Asg.LimException">Throws LimException if the nodeId is invalid.</exception>
        public void setDeclares(uint nodeId) {
            if (nodeId != 0) {
                if (!fact.getExist(nodeId))
                    throw new LimException("Columbus.Lim.Asg.Nodes.Logical.Member.setDeclares(NodeId)", "The end point of the edge does not exist.");

                Columbus.Lim.Asg.Nodes.Base.Base node = fact.getRef(nodeId);
                if (Common.getIsBaseClassKind(node.NodeKind, Types.NodeKind.ndkMember)) {
                    if (m_declares != 0) {
                    }
                    m_declares = nodeId;
                } else {
                    throw new LimException("Columbus.Lim.Asg.Nodes.Logical.Member.setDeclares(NodeId)", "Invalid NodeKind (" + node.NodeKind.ToString() + ").");
                }
            } else {
                if (m_declares != 0) {
                }
                m_declares = 0;
            }
        }

        /// <summary>
        /// Sets the declares edge.
        /// </summary>
        /// <param name="node">[in] The new end point of the declares edge.</param>
        /// <exception cref="Columbus.Lim.Asg.LimException">Throws LimException if there's something wrong with the given node.</exception>
        public void setDeclares(Columbus.Lim.Asg.Nodes.Logical.Member node) {
            if (m_declares != 0) {
            }
            m_declares = node.Id;
        }

        /// <summary>
        /// Adds a new hasComment edge to the node and inserts it after the other ones.
        /// </summary>
        /// <param name="node">[in] The end point of the new hasComment edge.</param>
        /// <exception cref="Columbus.Lim.Asg.LimException">Throws LimException if there is something wrong with the given node.</exception>
        public void addHasComment(Columbus.Lim.Asg.Nodes.Base.Comment node) {
            addHasComment(node.Id);
        }

        /// <summary>
        /// Adds a new hasComment edge to the node and inserts it after the other ones.
        /// </summary>
        /// <param name="nodeId">[in] The end point of the new hasComment edge.</param>
        /// <exception cref="Columbus.Lim.Asg.LimException">Throws LimException if the given nodeId is invalid.</exception>
        public void addHasComment(uint nodeId) {
            if (!fact.getExist(nodeId))
                throw new LimException("Columbus.Lim.Asg.Nodes.Logical.Member.addHasComment(NodeId)", "The end point of the edge does not exist.");
            Columbus.Lim.Asg.Nodes.Base.Base node = fact.getRef(nodeId);
            if (Common.getIsBaseClassKind(node.NodeKind, Types.NodeKind.ndkComment)) {
                hasCommentContainer.AddLast(nodeId);
            } else {
                throw new LimException("Columbus.Lim.Asg.Nodes.Logical.Member.setHasComment(NodeId)", "Invalid NodeKind (" + node.NodeKind.ToString() + ").");
            }
            if (fact.ReverseEdges != null)
              fact.ReverseEdges.insertEdge(nodeId, this.Id, Types.EdgeKind.edkMember_HasComment);
        }

        /// <summary>
        /// Adds a new instance edge to the node and inserts it after the other ones.
        /// </summary>
        /// <param name="node">[in] The end point of the new instance edge.</param>
        /// <exception cref="Columbus.Lim.Asg.LimException">Throws LimException if there is something wrong with the given node.</exception>
        public void addInstance(Columbus.Lim.Asg.Nodes.Logical.Member node) {
            addInstance(node.Id);
        }

        /// <summary>
        /// Adds a new instance edge to the node and inserts it after the other ones.
        /// </summary>
        /// <param name="nodeId">[in] The end point of the new instance edge.</param>
        /// <exception cref="Columbus.Lim.Asg.LimException">Throws LimException if the given nodeId is invalid.</exception>
        public void addInstance(uint nodeId) {
            if (!fact.getExist(nodeId))
                throw new LimException("Columbus.Lim.Asg.Nodes.Logical.Member.addInstance(NodeId)", "The end point of the edge does not exist.");
            Columbus.Lim.Asg.Nodes.Base.Base node = fact.getRef(nodeId);
            if (Common.getIsBaseClassKind(node.NodeKind, Types.NodeKind.ndkMember)) {
                instanceContainer.AddLast(nodeId);
            } else {
                throw new LimException("Columbus.Lim.Asg.Nodes.Logical.Member.setInstance(NodeId)", "Invalid NodeKind (" + node.NodeKind.ToString() + ").");
            }
            if (fact.ReverseEdges != null)
              fact.ReverseEdges.insertEdge(nodeId, this.Id, Types.EdgeKind.edkMember_Instance);
        }

        /// <summary>
        /// Adds a new isContainedIn edge to the node.
        /// </summary>
        /// <param name="node">[in] The end point of the new isContainedIn edge.</param>
        /// <param name="acValue">[in] The value of the association class.</param>
        /// <exception cref="Columbus.Lim.Asg.LimException">Throws LimException if there is something wrong with the given node.</exception>
        public void addIsContainedIn(Columbus.Lim.Asg.Nodes.Physical.File node, SourcePosition acValue) {
            addIsContainedIn(node.Id, acValue);
        }

        /// <summary>
        /// Adds a new isContainedIn edge to the node.
        /// </summary>
        /// <param name="nodeId">[in] The end point of the new isContainedIn edge.</param>
        /// <param name="acValue">[in] The value of the association class.</param>
        /// <exception cref="Columbus.Lim.Asg.LimException">Throws LimException if the given nodeId is invalid.</exception>
        public void addIsContainedIn(uint nodeId, SourcePosition acValue) {
            if (!fact.getExist(nodeId))
                throw new LimException("Columbus.Lim.Asg.Nodes.Logical.Member.addIsContainedIn(NodeId)", "The end point of the edge does not exist.");
            Columbus.Lim.Asg.Nodes.Base.Base node = fact.getRef(nodeId);
            if (Common.getIsBaseClassKind(node.NodeKind, Types.NodeKind.ndkFile)) {
                ListIteratorAssoc<Columbus.Lim.Asg.Nodes.Physical.File>.AssocEdge ac = new ListIteratorAssoc<Columbus.Lim.Asg.Nodes.Physical.File>.AssocEdge();
                ac.assocClass = new ListIteratorAssoc<Columbus.Lim.Asg.Nodes.Physical.File>.AssocClass();

                ac.id = nodeId;
                ac.assocClass.acSourcePosition = acValue;

                isContainedInAssocContainer.AddLast(ac);
            } else {
                throw new LimException("Columbus.Lim.Asg.Nodes.Logical.Member.setIsContainedIn(NodeId)", "Invalid NodeKind (" + node.NodeKind.ToString() + ").");
            }
            if (fact.ReverseEdges != null)
              fact.ReverseEdges.insertEdge(nodeId, this.Id, Types.EdgeKind.edkMember_IsContainedIn);
        }

        /// <summary>
        /// Sets the languageVariant edge.
        /// </summary>
        /// <param name="nodeId">[in] The new end point of the languageVariant edge or 0. With 0 the edge can be deleted.</param>
        /// <exception cref="Columbus.Lim.Asg.LimException">Throws LimException if the nodeId is invalid.</exception>
        public void setLanguageVariant(uint nodeId) {
            if (nodeId != 0) {
                if (!fact.getExist(nodeId))
                    throw new LimException("Columbus.Lim.Asg.Nodes.Logical.Member.setLanguageVariant(NodeId)", "The end point of the edge does not exist.");

                Columbus.Lim.Asg.Nodes.Base.Base node = fact.getRef(nodeId);
                if (Common.getIsBaseClassKind(node.NodeKind, Types.NodeKind.ndkMember)) {
                    if (m_languageVariant != 0) {
                    }
                    m_languageVariant = nodeId;
                } else {
                    throw new LimException("Columbus.Lim.Asg.Nodes.Logical.Member.setLanguageVariant(NodeId)", "Invalid NodeKind (" + node.NodeKind.ToString() + ").");
                }
            } else {
                if (m_languageVariant != 0) {
                }
                m_languageVariant = 0;
            }
        }

        /// <summary>
        /// Sets the languageVariant edge.
        /// </summary>
        /// <param name="node">[in] The new end point of the languageVariant edge.</param>
        /// <exception cref="Columbus.Lim.Asg.LimException">Throws LimException if there's something wrong with the given node.</exception>
        public void setLanguageVariant(Columbus.Lim.Asg.Nodes.Logical.Member node) {
            if (m_languageVariant != 0) {
            }
            m_languageVariant = node.Id;
        }

        /// <summary>
        /// Adds a new uses edge to the node and inserts it after the other ones.
        /// </summary>
        /// <param name="node">[in] The end point of the new uses edge.</param>
        /// <exception cref="Columbus.Lim.Asg.LimException">Throws LimException if there is something wrong with the given node.</exception>
        public void addUses(Columbus.Lim.Asg.Nodes.Type.Type node) {
            addUses(node.Id);
        }

        /// <summary>
        /// Adds a new uses edge to the node and inserts it after the other ones.
        /// </summary>
        /// <param name="nodeId">[in] The end point of the new uses edge.</param>
        /// <exception cref="Columbus.Lim.Asg.LimException">Throws LimException if the given nodeId is invalid.</exception>
        public void addUses(uint nodeId) {
            if (!fact.getExist(nodeId))
                throw new LimException("Columbus.Lim.Asg.Nodes.Logical.Member.addUses(NodeId)", "The end point of the edge does not exist.");
            Columbus.Lim.Asg.Nodes.Base.Base node = fact.getRef(nodeId);
            if (Common.getIsBaseClassKind(node.NodeKind, Types.NodeKind.ndkType)) {
                usesContainer.AddLast(nodeId);
            } else {
                throw new LimException("Columbus.Lim.Asg.Nodes.Logical.Member.setUses(NodeId)", "Invalid NodeKind (" + node.NodeKind.ToString() + ").");
            }
            if (fact.ReverseEdges != null)
              fact.ReverseEdges.insertEdge(nodeId, this.Id, Types.EdgeKind.edkMember_Uses);
        }

        /// <summary>
        /// Adds a new variant edge to the node and inserts it after the other ones.
        /// </summary>
        /// <param name="node">[in] The end point of the new variant edge.</param>
        /// <exception cref="Columbus.Lim.Asg.LimException">Throws LimException if there is something wrong with the given node.</exception>
        public void addVariant(Columbus.Lim.Asg.Nodes.Logical.Member node) {
            addVariant(node.Id);
        }

        /// <summary>
        /// Adds a new variant edge to the node and inserts it after the other ones.
        /// </summary>
        /// <param name="nodeId">[in] The end point of the new variant edge.</param>
        /// <exception cref="Columbus.Lim.Asg.LimException">Throws LimException if the given nodeId is invalid.</exception>
        public void addVariant(uint nodeId) {
            if (!fact.getExist(nodeId))
                throw new LimException("Columbus.Lim.Asg.Nodes.Logical.Member.addVariant(NodeId)", "The end point of the edge does not exist.");
            Columbus.Lim.Asg.Nodes.Base.Base node = fact.getRef(nodeId);
            if (Common.getIsBaseClassKind(node.NodeKind, Types.NodeKind.ndkMember)) {
                variantContainer.AddLast(nodeId);
            } else {
                throw new LimException("Columbus.Lim.Asg.Nodes.Logical.Member.setVariant(NodeId)", "Invalid NodeKind (" + node.NodeKind.ToString() + ").");
            }
            if (fact.ReverseEdges != null)
              fact.ReverseEdges.insertEdge(nodeId, this.Id, Types.EdgeKind.edkMember_Variant);
        }

        /// <summary>
        /// Saves the node.
        /// </summary>
        /// <param name="io">[in] The node is written into io.</param>
        /// <exception cref="Columbus.ColumbusIOException">Throws ColumbusIOException if there is something wrong with the file.</exception>
        public override void save(IO io) {
            base.save(io);

            byte boolValues = 0;
            boolValues <<= 1;
            if (m_isCompilerGenerated)
              boolValues |= 1;
            boolValues <<= 1;
            if (m_isStatic)
              boolValues |= 1;
            io.writeUByte1(boolValues);
            io.writeUByte1((byte)m_accessibility);
            io.writeUInt4(m_commentLines);
            fact.StringTable.setType(m_demangledName, StrTable.StrType.strToSave);
            io.writeUInt4(m_demangledName);
            io.writeUByte1((byte)m_language);
            fact.StringTable.setType(m_mangledName, StrTable.StrType.strToSave);
            io.writeUInt4(m_mangledName);

            io.writeUInt4(m_aggregated);
            io.writeUInt4(m_declares);
            io.writeUInt4(m_languageVariant);


            foreach (var belongsTo in belongsToContainer) {
              io.writeUInt4(belongsTo);
            }
            io.writeUInt4(0); // This is the end sign

            foreach (var compilationUnit in compilationUnitContainer) {
              io.writeUInt4(compilationUnit);
            }
            io.writeUInt4(0); // This is the end sign

            foreach (var hasComment in hasCommentContainer) {
              io.writeUInt4(hasComment);
            }
            io.writeUInt4(0); // This is the end sign

            foreach (var instance in instanceContainer) {
              io.writeUInt4(instance);
            }
            io.writeUInt4(0); // This is the end sign

            foreach (var isContainedInAssoc in isContainedInAssocContainer) {
                io.writeUInt4(isContainedInAssoc.id);
              isContainedInAssoc.assocClass.acSourcePosition.save(io);
            }
            io.writeUInt4(0); // This is the end sign

            foreach (var uses in usesContainer) {
              io.writeUInt4(uses);
            }
            io.writeUInt4(0); // This is the end sign

            foreach (var variant in variantContainer) {
              io.writeUInt4(variant);
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

            byte boolValues = binIo.readUByte1();
            m_isStatic = Convert.ToBoolean(boolValues & 1);
            boolValues >>= 1;
            m_isCompilerGenerated = Convert.ToBoolean(boolValues & 1);
            boolValues >>= 1;
            m_accessibility = (Types.AccessibilityKind)binIo.readUByte1();
            m_commentLines = binIo.readUInt4();
            m_demangledName = binIo.readUInt4();
            m_language = (Types.LanguageKind)binIo.readUByte1();
            m_mangledName = binIo.readUInt4();

            m_aggregated =  binIo.readUInt4();

            m_declares =  binIo.readUInt4();

            m_languageVariant =  binIo.readUInt4();

            uint _id;

            _id = binIo.readUInt4();
            while (_id != 0) {
              belongsToContainer.AddLast(_id);
              _id = binIo.readUInt4();
            }

            _id = binIo.readUInt4();
            while (_id != 0) {
              compilationUnitContainer.AddLast(_id);
              _id = binIo.readUInt4();
            }

            _id = binIo.readUInt4();
            while (_id != 0) {
              hasCommentContainer.AddLast(_id);
              _id = binIo.readUInt4();
            }

            _id = binIo.readUInt4();
            while (_id != 0) {
              instanceContainer.AddLast(_id);
              _id = binIo.readUInt4();
            }

            _id = binIo.readUInt4();
            while (_id != 0) {
              SourcePosition _ac = new SourcePosition();
              _ac.load(binIo);
                ListIteratorAssoc<Columbus.Lim.Asg.Nodes.Physical.File>.AssocEdge isContainedInAc = new ListIteratorAssoc<Columbus.Lim.Asg.Nodes.Physical.File>.AssocEdge();
                isContainedInAc.assocClass.acSourcePosition = _ac;
                isContainedInAc.id = _id;
                isContainedInAssocContainer.AddLast(isContainedInAc);
              _id = binIo.readUInt4();
            }

            _id = binIo.readUInt4();
            while (_id != 0) {
              usesContainer.AddLast(_id);
              _id = binIo.readUInt4();
            }

            _id = binIo.readUInt4();
            while (_id != 0) {
              variantContainer.AddLast(_id);
              _id = binIo.readUInt4();
            }
        }

    }

}
