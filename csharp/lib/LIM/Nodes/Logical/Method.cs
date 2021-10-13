using System;
using System.Text;
using System.Diagnostics;
using System.Collections.Generic;

namespace Columbus.Lim.Asg.Nodes.Logical {

    /// <summary>
    /// Method class, which represents the logical::Method node.
    /// </summary>
    [DebuggerDisplay("Id={Id}, DemangledName=\"{DemangledName}\", Name=\"{Name}\"")]
#if (LIM_INTERNAL)
    internal
#else
    public
#endif
    class Method : Scope {

        /// <summary>The value of the `distinctOperands`.</summary>
        protected uint m_distinctOperands;

        /// <summary>The value of the `distinctOperators`.</summary>
        protected uint m_distinctOperators;

        /// <summary>Stores whether the node is `Abstract` or not.</summary>
        protected bool m_isAbstract;

        /// <summary>Stores whether the node is `Virtual` or not.</summary>
        protected bool m_isVirtual;

        /// <summary>The MethodKind of the node.</summary>
        protected Types.MethodKind m_methodKind;

        /// <summary>The value of the `nestingLevel`.</summary>
        protected ushort m_nestingLevel;

        /// <summary>The value of the `nestingLevelElseIf`.</summary>
        protected ushort m_nestingLevelElseIf;

        /// <summary>The value of the `numberOfBranches`.</summary>
        protected uint m_numberOfBranches;

        /// <summary>The value of the `numberOfStatements`.</summary>
        protected uint m_numberOfStatements;

        /// <summary>The value of the `totalOperands`.</summary>
        protected uint m_totalOperands;

        /// <summary>The value of the `totalOperators`.</summary>
        protected uint m_totalOperators;


        // ---------- Edges ----------

        /// <summary>Container stores the id of the nodes the accessesAttribute edge points to.</summary>
        protected LinkedList<uint> accessesAttributeContainer;

        /// <summary>Container stores the id of the nodes the calls edge points to.</summary>
        protected LinkedList<uint> callsContainer;

        /// <summary>Container stores the id of the nodes the canThrow edge points to.</summary>
        protected LinkedList<uint> canThrowContainer;

        /// <summary>Container stores the id of the nodes the hasControlFlowBlock edge points to.</summary>
        protected LinkedList<uint> hasControlFlowBlockContainer;

        /// <summary>Container stores the id of the nodes the hasParameter edge points to.</summary>
        protected LinkedList<uint> hasParameterContainer;

        /// <summary>Container stores the id of the nodes the instantiates edge points to.</summary>
        protected LinkedList<uint> instantiatesContainer;

        /// <summary>Container stores the id of the nodes the returns edge points to.</summary>
        protected LinkedList<uint> returnsContainer;

        /// <summary>Container stores the id of the nodes the throws edge points to.</summary>
        protected LinkedList<uint> throwsContainer;

        /// <summary>
        /// Constructor, only factory can instantiates nodes.
        /// </summary>
        /// <param name="nodeId">[in] The id of the node.</param>
        /// <param name="factory">[in] Poiter to the Factory the node belongs to.</param>
        public Method(uint nodeId, Factory factory) : base(nodeId, factory) {
            m_distinctOperands = 0;
            m_distinctOperators = 0;
            m_isAbstract = false;
            m_isVirtual = false;
            m_methodKind = Types.MethodKind.mekAdd;
            m_nestingLevel = 0;
            m_nestingLevelElseIf = 0;
            m_numberOfBranches = 0;
            m_numberOfStatements = 0;
            m_totalOperands = 0;
            m_totalOperators = 0;
            accessesAttributeContainer = new LinkedList<uint>();
            callsContainer = new LinkedList<uint>();
            canThrowContainer = new LinkedList<uint>();
            hasControlFlowBlockContainer = new LinkedList<uint>();
            hasParameterContainer = new LinkedList<uint>();
            instantiatesContainer = new LinkedList<uint>();
            returnsContainer = new LinkedList<uint>();
            throwsContainer = new LinkedList<uint>();
        }

        /// <summary>
        /// Gives back the NodeKind of the node.
        /// </summary>
        /// <returns>Returns with the NodeKind.</returns>
        public override Types.NodeKind NodeKind {
            get { return Types.NodeKind.ndkMethod; }
        }


        // ---------- Attribute propert(y)(ies) ----------

        /// <summary>
        /// Gives back the distinctOperands of the node.
        /// </summary>
        /// <returns>Returns with the distinctOperands.</returns>
        public uint DistinctOperands
        {
            get
            {
                return m_distinctOperands;
            }
            set
            {
                m_distinctOperands = value;
            }
        }

        /// <summary>
        /// Gives back the distinctOperators of the node.
        /// </summary>
        /// <returns>Returns with the distinctOperators.</returns>
        public uint DistinctOperators
        {
            get
            {
                return m_distinctOperators;
            }
            set
            {
                m_distinctOperators = value;
            }
        }

        /// <summary>
        /// Gives back the isAbstract of the node.
        /// </summary>
        /// <returns>Returns with the isAbstract.</returns>
        public bool IsAbstract
        {
            get
            {
                return m_isAbstract;
            }
            set
            {
                m_isAbstract = value;
            }
        }

        /// <summary>
        /// Gives back the isVirtual of the node.
        /// </summary>
        /// <returns>Returns with the isVirtual.</returns>
        public bool IsVirtual
        {
            get
            {
                return m_isVirtual;
            }
            set
            {
                m_isVirtual = value;
            }
        }

        /// <summary>
        /// Gives back the methodKind of the node.
        /// </summary>
        /// <returns>Returns with the methodKind.</returns>
        public Types.MethodKind MethodKind
        {
            get
            {
                return m_methodKind;
            }
            set
            {
                m_methodKind = value;
            }
        }

        /// <summary>
        /// Gives back the nestingLevel of the node.
        /// </summary>
        /// <returns>Returns with the nestingLevel.</returns>
        public ushort NestingLevel
        {
            get
            {
                return m_nestingLevel;
            }
            set
            {
                m_nestingLevel = value;
            }
        }

        /// <summary>
        /// Gives back the nestingLevelElseIf of the node.
        /// </summary>
        /// <returns>Returns with the nestingLevelElseIf.</returns>
        public ushort NestingLevelElseIf
        {
            get
            {
                return m_nestingLevelElseIf;
            }
            set
            {
                m_nestingLevelElseIf = value;
            }
        }

        /// <summary>
        /// Gives back the numberOfBranches of the node.
        /// </summary>
        /// <returns>Returns with the numberOfBranches.</returns>
        public uint NumberOfBranches
        {
            get
            {
                return m_numberOfBranches;
            }
            set
            {
                m_numberOfBranches = value;
            }
        }

        /// <summary>
        /// Gives back the numberOfStatements of the node.
        /// </summary>
        /// <returns>Returns with the numberOfStatements.</returns>
        public uint NumberOfStatements
        {
            get
            {
                return m_numberOfStatements;
            }
            set
            {
                m_numberOfStatements = value;
            }
        }

        /// <summary>
        /// Gives back the totalOperands of the node.
        /// </summary>
        /// <returns>Returns with the totalOperands.</returns>
        public uint TotalOperands
        {
            get
            {
                return m_totalOperands;
            }
            set
            {
                m_totalOperands = value;
            }
        }

        /// <summary>
        /// Gives back the totalOperators of the node.
        /// </summary>
        /// <returns>Returns with the totalOperators.</returns>
        public uint TotalOperators
        {
            get
            {
                return m_totalOperators;
            }
            set
            {
                m_totalOperators = value;
            }
        }


        // ---------- Reflection getter function ----------

        /// <summary>
        /// Gives back the begin iterator for the edge specified
        /// </summary>
        /// <param name="edge">[in] The multiple edge for which the iterator is requested</param>
        public override ListIterator<Columbus.Lim.Asg.Nodes.Base.Base> GetListIteratorBegin(string edge) {
            switch(edge) {
                case "AccessesAttribute":
                    return AccessesAttributeListIteratorBegin.Convert<Columbus.Lim.Asg.Nodes.Base.Base>();
                case "Calls":
                    return CallsListIteratorBegin.Convert<Columbus.Lim.Asg.Nodes.Base.Base>();
                case "CanThrow":
                    return CanThrowListIteratorBegin.Convert<Columbus.Lim.Asg.Nodes.Base.Base>();
                case "HasControlFlowBlock":
                    return HasControlFlowBlockListIteratorBegin.Convert<Columbus.Lim.Asg.Nodes.Base.Base>();
                case "HasParameter":
                    return HasParameterListIteratorBegin.Convert<Columbus.Lim.Asg.Nodes.Base.Base>();
                case "Instantiates":
                    return InstantiatesListIteratorBegin.Convert<Columbus.Lim.Asg.Nodes.Base.Base>();
                case "Returns":
                    return ReturnsListIteratorBegin.Convert<Columbus.Lim.Asg.Nodes.Base.Base>();
                case "Throws":
                    return ThrowsListIteratorBegin.Convert<Columbus.Lim.Asg.Nodes.Base.Base>();
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
                case "AccessesAttribute":
                    addAccessesAttribute(nodeId);
                    return;
                case "Calls":
                    addCalls(nodeId);
                    return;
                case "CanThrow":
                    addCanThrow(nodeId);
                    return;
                case "HasControlFlowBlock":
                    addHasControlFlowBlock(nodeId);
                    return;
                case "HasParameter":
                    addHasParameter(nodeId);
                    return;
                case "Instantiates":
                    addInstantiates(nodeId);
                    return;
                case "Returns":
                    addReturns(nodeId);
                    return;
                case "Throws":
                    addThrows(nodeId);
                    return;
                default:
                    base.add(edge, nodeId);
                    return;
            }
        }


        // ---------- Edge getter function(s) ----------

        /// <summary>
        /// Gives back iterator for the accessesAttribute edges.
        /// </summary>
        /// <returns>Returns an iterator for the accessesAttribute edges.</returns>
        public ListIterator<Columbus.Lim.Asg.Nodes.Logical.AttributeAccess> AccessesAttributeListIteratorBegin {
            get {
                return new ListIterator<Columbus.Lim.Asg.Nodes.Logical.AttributeAccess>(accessesAttributeContainer, fact, true);
            }
        }

        /// <summary>
        /// Gives back iterator for the accessesAttribute edges.
        /// </summary>
        /// <returns>Returns an iterator for the accessesAttribute edges.</returns>
        public ListIterator<Columbus.Lim.Asg.Nodes.Logical.AttributeAccess> AccessesAttributeListIteratorEnd {
            get {
                return new ListIterator<Columbus.Lim.Asg.Nodes.Logical.AttributeAccess>(accessesAttributeContainer, fact, false);
            }
        }

        /// <summary>
        /// Tells whether the node has accessesAttribute edges or not.
        /// </summary>
        /// <returns>Returns true if the node has at least one accessesAttribute edge.</returns>
        public bool AccessesAttributeIsEmpty {
            get { return accessesAttributeContainer.Count == 0; }
        }

        /// <summary>
        /// Gives back how many accessesAttribute edges the node has.
        /// </summary>
        /// <returns>Returns with the number of accessesAttribute edges.</returns>
        public uint AccessesAttributeSize {
            get { return (uint)(accessesAttributeContainer.Count); }
        }

        /// <summary>
        /// Gives back iterator for the calls edges.
        /// </summary>
        /// <returns>Returns an iterator for the calls edges.</returns>
        public ListIterator<Columbus.Lim.Asg.Nodes.Logical.MethodCall> CallsListIteratorBegin {
            get {
                return new ListIterator<Columbus.Lim.Asg.Nodes.Logical.MethodCall>(callsContainer, fact, true);
            }
        }

        /// <summary>
        /// Gives back iterator for the calls edges.
        /// </summary>
        /// <returns>Returns an iterator for the calls edges.</returns>
        public ListIterator<Columbus.Lim.Asg.Nodes.Logical.MethodCall> CallsListIteratorEnd {
            get {
                return new ListIterator<Columbus.Lim.Asg.Nodes.Logical.MethodCall>(callsContainer, fact, false);
            }
        }

        /// <summary>
        /// Tells whether the node has calls edges or not.
        /// </summary>
        /// <returns>Returns true if the node has at least one calls edge.</returns>
        public bool CallsIsEmpty {
            get { return callsContainer.Count == 0; }
        }

        /// <summary>
        /// Gives back how many calls edges the node has.
        /// </summary>
        /// <returns>Returns with the number of calls edges.</returns>
        public uint CallsSize {
            get { return (uint)(callsContainer.Count); }
        }

        /// <summary>
        /// Gives back iterator for the canThrow edges.
        /// </summary>
        /// <returns>Returns an iterator for the canThrow edges.</returns>
        public ListIterator<Columbus.Lim.Asg.Nodes.Type.Type> CanThrowListIteratorBegin {
            get {
                return new ListIterator<Columbus.Lim.Asg.Nodes.Type.Type>(canThrowContainer, fact, true);
            }
        }

        /// <summary>
        /// Gives back iterator for the canThrow edges.
        /// </summary>
        /// <returns>Returns an iterator for the canThrow edges.</returns>
        public ListIterator<Columbus.Lim.Asg.Nodes.Type.Type> CanThrowListIteratorEnd {
            get {
                return new ListIterator<Columbus.Lim.Asg.Nodes.Type.Type>(canThrowContainer, fact, false);
            }
        }

        /// <summary>
        /// Tells whether the node has canThrow edges or not.
        /// </summary>
        /// <returns>Returns true if the node has at least one canThrow edge.</returns>
        public bool CanThrowIsEmpty {
            get { return canThrowContainer.Count == 0; }
        }

        /// <summary>
        /// Gives back how many canThrow edges the node has.
        /// </summary>
        /// <returns>Returns with the number of canThrow edges.</returns>
        public uint CanThrowSize {
            get { return (uint)(canThrowContainer.Count); }
        }

        /// <summary>
        /// Gives back iterator for the hasControlFlowBlock edges.
        /// </summary>
        /// <returns>Returns an iterator for the hasControlFlowBlock edges.</returns>
        public ListIterator<Columbus.Lim.Asg.Nodes.Base.ControlFlowBlock> HasControlFlowBlockListIteratorBegin {
            get {
                return new ListIterator<Columbus.Lim.Asg.Nodes.Base.ControlFlowBlock>(hasControlFlowBlockContainer, fact, true);
            }
        }

        /// <summary>
        /// Gives back iterator for the hasControlFlowBlock edges.
        /// </summary>
        /// <returns>Returns an iterator for the hasControlFlowBlock edges.</returns>
        public ListIterator<Columbus.Lim.Asg.Nodes.Base.ControlFlowBlock> HasControlFlowBlockListIteratorEnd {
            get {
                return new ListIterator<Columbus.Lim.Asg.Nodes.Base.ControlFlowBlock>(hasControlFlowBlockContainer, fact, false);
            }
        }

        /// <summary>
        /// Tells whether the node has hasControlFlowBlock edges or not.
        /// </summary>
        /// <returns>Returns true if the node has at least one hasControlFlowBlock edge.</returns>
        public bool HasControlFlowBlockIsEmpty {
            get { return hasControlFlowBlockContainer.Count == 0; }
        }

        /// <summary>
        /// Gives back how many hasControlFlowBlock edges the node has.
        /// </summary>
        /// <returns>Returns with the number of hasControlFlowBlock edges.</returns>
        public uint HasControlFlowBlockSize {
            get { return (uint)(hasControlFlowBlockContainer.Count); }
        }

        /// <summary>
        /// Gives back iterator for the hasParameter edges.
        /// </summary>
        /// <returns>Returns an iterator for the hasParameter edges.</returns>
        public ListIterator<Columbus.Lim.Asg.Nodes.Logical.Parameter> HasParameterListIteratorBegin {
            get {
                return new ListIterator<Columbus.Lim.Asg.Nodes.Logical.Parameter>(hasParameterContainer, fact, true);
            }
        }

        /// <summary>
        /// Gives back iterator for the hasParameter edges.
        /// </summary>
        /// <returns>Returns an iterator for the hasParameter edges.</returns>
        public ListIterator<Columbus.Lim.Asg.Nodes.Logical.Parameter> HasParameterListIteratorEnd {
            get {
                return new ListIterator<Columbus.Lim.Asg.Nodes.Logical.Parameter>(hasParameterContainer, fact, false);
            }
        }

        /// <summary>
        /// Tells whether the node has hasParameter edges or not.
        /// </summary>
        /// <returns>Returns true if the node has at least one hasParameter edge.</returns>
        public bool HasParameterIsEmpty {
            get { return hasParameterContainer.Count == 0; }
        }

        /// <summary>
        /// Gives back how many hasParameter edges the node has.
        /// </summary>
        /// <returns>Returns with the number of hasParameter edges.</returns>
        public uint HasParameterSize {
            get { return (uint)(hasParameterContainer.Count); }
        }

        /// <summary>
        /// Gives back iterator for the instantiates edges.
        /// </summary>
        /// <returns>Returns an iterator for the instantiates edges.</returns>
        public ListIterator<Columbus.Lim.Asg.Nodes.Type.Type> InstantiatesListIteratorBegin {
            get {
                return new ListIterator<Columbus.Lim.Asg.Nodes.Type.Type>(instantiatesContainer, fact, true);
            }
        }

        /// <summary>
        /// Gives back iterator for the instantiates edges.
        /// </summary>
        /// <returns>Returns an iterator for the instantiates edges.</returns>
        public ListIterator<Columbus.Lim.Asg.Nodes.Type.Type> InstantiatesListIteratorEnd {
            get {
                return new ListIterator<Columbus.Lim.Asg.Nodes.Type.Type>(instantiatesContainer, fact, false);
            }
        }

        /// <summary>
        /// Tells whether the node has instantiates edges or not.
        /// </summary>
        /// <returns>Returns true if the node has at least one instantiates edge.</returns>
        public bool InstantiatesIsEmpty {
            get { return instantiatesContainer.Count == 0; }
        }

        /// <summary>
        /// Gives back how many instantiates edges the node has.
        /// </summary>
        /// <returns>Returns with the number of instantiates edges.</returns>
        public uint InstantiatesSize {
            get { return (uint)(instantiatesContainer.Count); }
        }

        /// <summary>
        /// Gives back iterator for the returns edges.
        /// </summary>
        /// <returns>Returns an iterator for the returns edges.</returns>
        public ListIterator<Columbus.Lim.Asg.Nodes.Type.Type> ReturnsListIteratorBegin {
            get {
                return new ListIterator<Columbus.Lim.Asg.Nodes.Type.Type>(returnsContainer, fact, true);
            }
        }

        /// <summary>
        /// Gives back iterator for the returns edges.
        /// </summary>
        /// <returns>Returns an iterator for the returns edges.</returns>
        public ListIterator<Columbus.Lim.Asg.Nodes.Type.Type> ReturnsListIteratorEnd {
            get {
                return new ListIterator<Columbus.Lim.Asg.Nodes.Type.Type>(returnsContainer, fact, false);
            }
        }

        /// <summary>
        /// Tells whether the node has returns edges or not.
        /// </summary>
        /// <returns>Returns true if the node has at least one returns edge.</returns>
        public bool ReturnsIsEmpty {
            get { return returnsContainer.Count == 0; }
        }

        /// <summary>
        /// Gives back how many returns edges the node has.
        /// </summary>
        /// <returns>Returns with the number of returns edges.</returns>
        public uint ReturnsSize {
            get { return (uint)(returnsContainer.Count); }
        }

        /// <summary>
        /// Gives back iterator for the throws edges.
        /// </summary>
        /// <returns>Returns an iterator for the throws edges.</returns>
        public ListIterator<Columbus.Lim.Asg.Nodes.Type.Type> ThrowsListIteratorBegin {
            get {
                return new ListIterator<Columbus.Lim.Asg.Nodes.Type.Type>(throwsContainer, fact, true);
            }
        }

        /// <summary>
        /// Gives back iterator for the throws edges.
        /// </summary>
        /// <returns>Returns an iterator for the throws edges.</returns>
        public ListIterator<Columbus.Lim.Asg.Nodes.Type.Type> ThrowsListIteratorEnd {
            get {
                return new ListIterator<Columbus.Lim.Asg.Nodes.Type.Type>(throwsContainer, fact, false);
            }
        }

        /// <summary>
        /// Tells whether the node has throws edges or not.
        /// </summary>
        /// <returns>Returns true if the node has at least one throws edge.</returns>
        public bool ThrowsIsEmpty {
            get { return throwsContainer.Count == 0; }
        }

        /// <summary>
        /// Gives back how many throws edges the node has.
        /// </summary>
        /// <returns>Returns with the number of throws edges.</returns>
        public uint ThrowsSize {
            get { return (uint)(throwsContainer.Count); }
        }


        // ---------- Edge setter function(s) ----------

        /// <summary>
        /// Adds a new accessesAttribute edge to the node and inserts it after the other ones.
        /// </summary>
        /// <param name="node">[in] The end point of the new accessesAttribute edge.</param>
        /// <exception cref="Columbus.Lim.Asg.LimException">Throws LimException if there is something wrong with the given node.</exception>
        public void addAccessesAttribute(Columbus.Lim.Asg.Nodes.Logical.AttributeAccess node) {
            addAccessesAttribute(node.Id);
        }

        /// <summary>
        /// Adds a new accessesAttribute edge to the node and inserts it after the other ones.
        /// </summary>
        /// <param name="nodeId">[in] The end point of the new accessesAttribute edge.</param>
        /// <exception cref="Columbus.Lim.Asg.LimException">Throws LimException if the given nodeId is invalid.</exception>
        public void addAccessesAttribute(uint nodeId) {
            if (!fact.getExist(nodeId))
                throw new LimException("Columbus.Lim.Asg.Nodes.Logical.Method.addAccessesAttribute(NodeId)", "The end point of the edge does not exist.");
            Columbus.Lim.Asg.Nodes.Base.Base node = fact.getRef(nodeId);
            if (Common.getIsBaseClassKind(node.NodeKind, Types.NodeKind.ndkAttributeAccess)) {
                accessesAttributeContainer.AddLast(nodeId);
            } else {
                throw new LimException("Columbus.Lim.Asg.Nodes.Logical.Method.setAccessesAttribute(NodeId)", "Invalid NodeKind (" + node.NodeKind.ToString() + ").");
            }
            if (fact.ReverseEdges != null)
              fact.ReverseEdges.insertEdge(nodeId, this.Id, Types.EdgeKind.edkMethod_AccessesAttribute);
        }

        /// <summary>
        /// Adds a new calls edge to the node and inserts it after the other ones.
        /// </summary>
        /// <param name="node">[in] The end point of the new calls edge.</param>
        /// <exception cref="Columbus.Lim.Asg.LimException">Throws LimException if there is something wrong with the given node.</exception>
        public void addCalls(Columbus.Lim.Asg.Nodes.Logical.MethodCall node) {
            addCalls(node.Id);
        }

        /// <summary>
        /// Adds a new calls edge to the node and inserts it after the other ones.
        /// </summary>
        /// <param name="nodeId">[in] The end point of the new calls edge.</param>
        /// <exception cref="Columbus.Lim.Asg.LimException">Throws LimException if the given nodeId is invalid.</exception>
        public void addCalls(uint nodeId) {
            if (!fact.getExist(nodeId))
                throw new LimException("Columbus.Lim.Asg.Nodes.Logical.Method.addCalls(NodeId)", "The end point of the edge does not exist.");
            Columbus.Lim.Asg.Nodes.Base.Base node = fact.getRef(nodeId);
            if (Common.getIsBaseClassKind(node.NodeKind, Types.NodeKind.ndkMethodCall)) {
                callsContainer.AddLast(nodeId);
            } else {
                throw new LimException("Columbus.Lim.Asg.Nodes.Logical.Method.setCalls(NodeId)", "Invalid NodeKind (" + node.NodeKind.ToString() + ").");
            }
            if (fact.ReverseEdges != null)
              fact.ReverseEdges.insertEdge(nodeId, this.Id, Types.EdgeKind.edkMethod_Calls);
        }

        /// <summary>
        /// Adds a new canThrow edge to the node and inserts it after the other ones.
        /// </summary>
        /// <param name="node">[in] The end point of the new canThrow edge.</param>
        /// <exception cref="Columbus.Lim.Asg.LimException">Throws LimException if there is something wrong with the given node.</exception>
        public void addCanThrow(Columbus.Lim.Asg.Nodes.Type.Type node) {
            addCanThrow(node.Id);
        }

        /// <summary>
        /// Adds a new canThrow edge to the node and inserts it after the other ones.
        /// </summary>
        /// <param name="nodeId">[in] The end point of the new canThrow edge.</param>
        /// <exception cref="Columbus.Lim.Asg.LimException">Throws LimException if the given nodeId is invalid.</exception>
        public void addCanThrow(uint nodeId) {
            if (!fact.getExist(nodeId))
                throw new LimException("Columbus.Lim.Asg.Nodes.Logical.Method.addCanThrow(NodeId)", "The end point of the edge does not exist.");
            Columbus.Lim.Asg.Nodes.Base.Base node = fact.getRef(nodeId);
            if (Common.getIsBaseClassKind(node.NodeKind, Types.NodeKind.ndkType)) {
                canThrowContainer.AddLast(nodeId);
            } else {
                throw new LimException("Columbus.Lim.Asg.Nodes.Logical.Method.setCanThrow(NodeId)", "Invalid NodeKind (" + node.NodeKind.ToString() + ").");
            }
            if (fact.ReverseEdges != null)
              fact.ReverseEdges.insertEdge(nodeId, this.Id, Types.EdgeKind.edkMethod_CanThrow);
        }

        /// <summary>
        /// Adds a new hasControlFlowBlock edge to the node and inserts it after the other ones.
        /// </summary>
        /// <param name="node">[in] The end point of the new hasControlFlowBlock edge.</param>
        /// <exception cref="Columbus.Lim.Asg.LimException">Throws LimException if there is something wrong with the given node.</exception>
        public void addHasControlFlowBlock(Columbus.Lim.Asg.Nodes.Base.ControlFlowBlock node) {
            addHasControlFlowBlock(node.Id);
        }

        /// <summary>
        /// Adds a new hasControlFlowBlock edge to the node and inserts it after the other ones.
        /// </summary>
        /// <param name="nodeId">[in] The end point of the new hasControlFlowBlock edge.</param>
        /// <exception cref="Columbus.Lim.Asg.LimException">Throws LimException if the given nodeId is invalid.</exception>
        public void addHasControlFlowBlock(uint nodeId) {
            if (!fact.getExist(nodeId))
                throw new LimException("Columbus.Lim.Asg.Nodes.Logical.Method.addHasControlFlowBlock(NodeId)", "The end point of the edge does not exist.");
            Columbus.Lim.Asg.Nodes.Base.Base node = fact.getRef(nodeId);
            if (Common.getIsBaseClassKind(node.NodeKind, Types.NodeKind.ndkControlFlowBlock)) {
                hasControlFlowBlockContainer.AddLast(nodeId);
            } else {
                throw new LimException("Columbus.Lim.Asg.Nodes.Logical.Method.setHasControlFlowBlock(NodeId)", "Invalid NodeKind (" + node.NodeKind.ToString() + ").");
            }
           setParentEdge(nodeId, (uint)Types.EdgeKind.edkMethod_HasControlFlowBlock);
            if (fact.ReverseEdges != null)
              fact.ReverseEdges.insertEdge(nodeId, this.Id, Types.EdgeKind.edkMethod_HasControlFlowBlock);
        }

        /// <summary>
        /// Adds a new hasParameter edge to the node and inserts it after the other ones.
        /// </summary>
        /// <param name="node">[in] The end point of the new hasParameter edge.</param>
        /// <exception cref="Columbus.Lim.Asg.LimException">Throws LimException if there is something wrong with the given node.</exception>
        public void addHasParameter(Columbus.Lim.Asg.Nodes.Logical.Parameter node) {
            addHasParameter(node.Id);
        }

        /// <summary>
        /// Adds a new hasParameter edge to the node and inserts it after the other ones.
        /// </summary>
        /// <param name="nodeId">[in] The end point of the new hasParameter edge.</param>
        /// <exception cref="Columbus.Lim.Asg.LimException">Throws LimException if the given nodeId is invalid.</exception>
        public void addHasParameter(uint nodeId) {
            if (!fact.getExist(nodeId))
                throw new LimException("Columbus.Lim.Asg.Nodes.Logical.Method.addHasParameter(NodeId)", "The end point of the edge does not exist.");
            Columbus.Lim.Asg.Nodes.Base.Base node = fact.getRef(nodeId);
            if (Common.getIsBaseClassKind(node.NodeKind, Types.NodeKind.ndkParameter)) {
                hasParameterContainer.AddLast(nodeId);
            } else {
                throw new LimException("Columbus.Lim.Asg.Nodes.Logical.Method.setHasParameter(NodeId)", "Invalid NodeKind (" + node.NodeKind.ToString() + ").");
            }
           setParentEdge(nodeId, (uint)Types.EdgeKind.edkMethod_HasParameter);
            if (fact.ReverseEdges != null)
              fact.ReverseEdges.insertEdge(nodeId, this.Id, Types.EdgeKind.edkMethod_HasParameter);
        }

        /// <summary>
        /// Adds a new instantiates edge to the node and inserts it after the other ones.
        /// </summary>
        /// <param name="node">[in] The end point of the new instantiates edge.</param>
        /// <exception cref="Columbus.Lim.Asg.LimException">Throws LimException if there is something wrong with the given node.</exception>
        public void addInstantiates(Columbus.Lim.Asg.Nodes.Type.Type node) {
            addInstantiates(node.Id);
        }

        /// <summary>
        /// Adds a new instantiates edge to the node and inserts it after the other ones.
        /// </summary>
        /// <param name="nodeId">[in] The end point of the new instantiates edge.</param>
        /// <exception cref="Columbus.Lim.Asg.LimException">Throws LimException if the given nodeId is invalid.</exception>
        public void addInstantiates(uint nodeId) {
            if (!fact.getExist(nodeId))
                throw new LimException("Columbus.Lim.Asg.Nodes.Logical.Method.addInstantiates(NodeId)", "The end point of the edge does not exist.");
            Columbus.Lim.Asg.Nodes.Base.Base node = fact.getRef(nodeId);
            if (Common.getIsBaseClassKind(node.NodeKind, Types.NodeKind.ndkType)) {
                instantiatesContainer.AddLast(nodeId);
            } else {
                throw new LimException("Columbus.Lim.Asg.Nodes.Logical.Method.setInstantiates(NodeId)", "Invalid NodeKind (" + node.NodeKind.ToString() + ").");
            }
            if (fact.ReverseEdges != null)
              fact.ReverseEdges.insertEdge(nodeId, this.Id, Types.EdgeKind.edkMethod_Instantiates);
        }

        /// <summary>
        /// Adds a new returns edge to the node and inserts it after the other ones.
        /// </summary>
        /// <param name="node">[in] The end point of the new returns edge.</param>
        /// <exception cref="Columbus.Lim.Asg.LimException">Throws LimException if there is something wrong with the given node.</exception>
        public void addReturns(Columbus.Lim.Asg.Nodes.Type.Type node) {
            addReturns(node.Id);
        }

        /// <summary>
        /// Adds a new returns edge to the node and inserts it after the other ones.
        /// </summary>
        /// <param name="nodeId">[in] The end point of the new returns edge.</param>
        /// <exception cref="Columbus.Lim.Asg.LimException">Throws LimException if the given nodeId is invalid.</exception>
        public void addReturns(uint nodeId) {
            if (!fact.getExist(nodeId))
                throw new LimException("Columbus.Lim.Asg.Nodes.Logical.Method.addReturns(NodeId)", "The end point of the edge does not exist.");
            Columbus.Lim.Asg.Nodes.Base.Base node = fact.getRef(nodeId);
            if (Common.getIsBaseClassKind(node.NodeKind, Types.NodeKind.ndkType)) {
                returnsContainer.AddLast(nodeId);
            } else {
                throw new LimException("Columbus.Lim.Asg.Nodes.Logical.Method.setReturns(NodeId)", "Invalid NodeKind (" + node.NodeKind.ToString() + ").");
            }
            if (fact.ReverseEdges != null)
              fact.ReverseEdges.insertEdge(nodeId, this.Id, Types.EdgeKind.edkMethod_Returns);
        }

        /// <summary>
        /// Adds a new throws edge to the node and inserts it after the other ones.
        /// </summary>
        /// <param name="node">[in] The end point of the new throws edge.</param>
        /// <exception cref="Columbus.Lim.Asg.LimException">Throws LimException if there is something wrong with the given node.</exception>
        public void addThrows(Columbus.Lim.Asg.Nodes.Type.Type node) {
            addThrows(node.Id);
        }

        /// <summary>
        /// Adds a new throws edge to the node and inserts it after the other ones.
        /// </summary>
        /// <param name="nodeId">[in] The end point of the new throws edge.</param>
        /// <exception cref="Columbus.Lim.Asg.LimException">Throws LimException if the given nodeId is invalid.</exception>
        public void addThrows(uint nodeId) {
            if (!fact.getExist(nodeId))
                throw new LimException("Columbus.Lim.Asg.Nodes.Logical.Method.addThrows(NodeId)", "The end point of the edge does not exist.");
            Columbus.Lim.Asg.Nodes.Base.Base node = fact.getRef(nodeId);
            if (Common.getIsBaseClassKind(node.NodeKind, Types.NodeKind.ndkType)) {
                throwsContainer.AddLast(nodeId);
            } else {
                throw new LimException("Columbus.Lim.Asg.Nodes.Logical.Method.setThrows(NodeId)", "Invalid NodeKind (" + node.NodeKind.ToString() + ").");
            }
            if (fact.ReverseEdges != null)
              fact.ReverseEdges.insertEdge(nodeId, this.Id, Types.EdgeKind.edkMethod_Throws);
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

            byte boolValues = 0;
            boolValues <<= 1;
            if (m_isAbstract)
              boolValues |= 1;
            boolValues <<= 1;
            if (m_isVirtual)
              boolValues |= 1;
            io.writeUByte1(boolValues);
            io.writeUInt4(m_distinctOperands);
            io.writeUInt4(m_distinctOperators);
            io.writeUByte1((byte)m_methodKind);
            io.writeUShort2(m_nestingLevel);
            io.writeUShort2(m_nestingLevelElseIf);
            io.writeUInt4(m_numberOfBranches);
            io.writeUInt4(m_numberOfStatements);
            io.writeUInt4(m_totalOperands);
            io.writeUInt4(m_totalOperators);


            foreach (var accessesAttribute in accessesAttributeContainer) {
              io.writeUInt4(accessesAttribute);
            }
            io.writeUInt4(0); // This is the end sign

            foreach (var calls in callsContainer) {
              io.writeUInt4(calls);
            }
            io.writeUInt4(0); // This is the end sign

            foreach (var canThrow in canThrowContainer) {
              io.writeUInt4(canThrow);
            }
            io.writeUInt4(0); // This is the end sign

            foreach (var hasControlFlowBlock in hasControlFlowBlockContainer) {
              io.writeUInt4(hasControlFlowBlock);
            }
            io.writeUInt4(0); // This is the end sign

            foreach (var hasParameter in hasParameterContainer) {
              io.writeUInt4(hasParameter);
            }
            io.writeUInt4(0); // This is the end sign

            foreach (var instantiates in instantiatesContainer) {
              io.writeUInt4(instantiates);
            }
            io.writeUInt4(0); // This is the end sign

            foreach (var returns in returnsContainer) {
              io.writeUInt4(returns);
            }
            io.writeUInt4(0); // This is the end sign

            foreach (var throws in throwsContainer) {
              io.writeUInt4(throws);
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
            m_isVirtual = Convert.ToBoolean(boolValues & 1);
            boolValues >>= 1;
            m_isAbstract = Convert.ToBoolean(boolValues & 1);
            boolValues >>= 1;
            m_distinctOperands = binIo.readUInt4();
            m_distinctOperators = binIo.readUInt4();
            m_methodKind = (Types.MethodKind)binIo.readUByte1();
            m_nestingLevel = binIo.readUShort2();
            m_nestingLevelElseIf = binIo.readUShort2();
            m_numberOfBranches = binIo.readUInt4();
            m_numberOfStatements = binIo.readUInt4();
            m_totalOperands = binIo.readUInt4();
            m_totalOperators = binIo.readUInt4();

            uint _id;

            _id = binIo.readUInt4();
            while (_id != 0) {
              accessesAttributeContainer.AddLast(_id);
              _id = binIo.readUInt4();
            }

            _id = binIo.readUInt4();
            while (_id != 0) {
              callsContainer.AddLast(_id);
              _id = binIo.readUInt4();
            }

            _id = binIo.readUInt4();
            while (_id != 0) {
              canThrowContainer.AddLast(_id);
              _id = binIo.readUInt4();
            }

            _id = binIo.readUInt4();
            while (_id != 0) {
              hasControlFlowBlockContainer.AddLast(_id);
              setParentEdge(_id, (uint)Types.EdgeKind.edkMethod_HasControlFlowBlock);
              _id = binIo.readUInt4();
            }

            _id = binIo.readUInt4();
            while (_id != 0) {
              hasParameterContainer.AddLast(_id);
              setParentEdge(_id, (uint)Types.EdgeKind.edkMethod_HasParameter);
              _id = binIo.readUInt4();
            }

            _id = binIo.readUInt4();
            while (_id != 0) {
              instantiatesContainer.AddLast(_id);
              _id = binIo.readUInt4();
            }

            _id = binIo.readUInt4();
            while (_id != 0) {
              returnsContainer.AddLast(_id);
              _id = binIo.readUInt4();
            }

            _id = binIo.readUInt4();
            while (_id != 0) {
              throwsContainer.AddLast(_id);
              _id = binIo.readUInt4();
            }
        }

    }

}
