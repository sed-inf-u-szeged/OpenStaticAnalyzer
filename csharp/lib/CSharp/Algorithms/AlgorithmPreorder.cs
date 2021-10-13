    using System;
    using System.Collections.Generic;
    using System.Text;
    using System.Linq;

namespace Columbus.Csharp.Asg.Algorithms {
    
    using Visitors;

    /// <summary>
    /// Implements the preorder traversal of the ASG.
    /// </summary>
#if (CSHARP_INTERNAL)
    internal
#else
    public
#endif
    class AlgorithmPreorder : Algorithm {

    /// <summary>
    /// If it is true, two node are not visited during preorder.
    /// </summary>
            private bool safeMode;

    /// <summary>
    /// Stores the ids of the node which are already visited during the actual run.
    /// </summary>
        private List<bool> visitedNodes;

    /// <summary>
    /// The set of ids of nodes which need to be visited.
    /// </summary>
        private List<bool> unvisitedNodes;

    /// <summary>
    /// If it is true, it collect the sub trees.
    /// </summary>
        private bool visitCrossEdgeTree;

    /// <summary>
    /// If it is true, the preorder is stopped because of a visitor.
    /// </summary>
        private bool needPreorderStop;

    /// <summary>
    /// The set of visitors we stop in the next clearStoppedVisitors call.
    /// </summary>
        private List<Visitor> stoppeds;

        private bool visitFilteredEdge;

        private bool originalFilterState;

        private Columbus.Csharp.Asg.Nodes.Base.Base apRoot;

        private List<Visitor> visitorList;

        private Factory fact;

        private List<bool> traversaldCrossEdges;

        /// <summary>
        /// Constructor.
        /// </summary>
        public AlgorithmPreorder() {
            safeMode = false;
            visitedNodes = new List<bool>();
            unvisitedNodes = new List<bool>();
            visitCrossEdgeTree = false;
            needPreorderStop = false;
            visitFilteredEdge = false;
            originalFilterState = false;
            visitorList = new List<Visitor>();
            traversaldCrossEdges = new List<bool>();
            stoppeds = new List<Visitor>();
            for (int i = 0; i < 293; i++) {
                traversaldCrossEdges.Add(false);
            }
        }

        public void setSafeMode() {
          safeMode = true;
        }

        public void setUnsafeMode() {
          safeMode = false;
        }

        public bool VisitCrossEdgeTree
        {
            get
            {
                return visitCrossEdgeTree;
            }
            set
            {
                visitCrossEdgeTree = value;
            }
        }

        public Types.EdgeKind CrossEdgeToTraversal
        {
            set
            {
                traversaldCrossEdges[(int)value] = true;
            }
        }

        public bool VisitFilteredEdges
        {
            get
            {
                return visitFilteredEdge;
            }
            set
            {
                visitFilteredEdge = value;
            }
        }

        public void run(Factory fact = null, Visitor visitor = null, Columbus.Csharp.Asg.Nodes.Base.Base node = null) {
          mainRun(fact, visitor, node);
        }

        private void mainRun(Factory _fact, Visitor visitor, Columbus.Csharp.Asg.Nodes.Base.Base node) {
            if (_fact != null) {
                fact = _fact;
            }
            if (visitor != null) {
                visitorList.Clear();
                visitorList.Add(visitor);

            }
            apRoot = node;

            startPreorder();

            if (apRoot != null) {
                apRoot.accept(this);

                if (!needPreorderStop && (visitCrossEdgeTree)) {
                    bool wasNodeToTraversal = false;
                    int factSize = (int)fact.Size;
                    do {
                        wasNodeToTraversal = false;
                        for (int i = 0; i < factSize; ++i) {
                            if (unvisitedNodes[i] && !visitedNodes[i]) {
                                fact.getRef((uint)i).accept(this);
                                wasNodeToTraversal = true;
                                unvisitedNodes[i] = false;

                                if(needPreorderStop)
                                    return;
                            }
                        }
                    } while (wasNodeToTraversal);
                }
            }else {
                int factSize = (int)fact.Size;
                for (int i = 0; i < factSize; ++i) {
                    if ((!fact.getIsFiltered((uint)i)) &&  fact.isIndividual(i)){
                        (fact.getRef((uint)i)).accept(this);

                        if(needPreorderStop)
                            return;
                    }
                }
            }
        
          endPreorder();
        }

        public void setFactory(Factory _fact) {
          fact = _fact;
        }

public void addVisitor(Visitor visitor) {
  visitorList.Add( visitor);
}

        /// <summary>
        /// It call the traversal for the edges
        /// </summary>
        /// <param name="node">[in] The node with own type</param>
        /// <param name="callVirtualBase">[in] This paramater is don't used just api copatibility used.</param>
        public void visitAllEdges(Columbus.Csharp.Asg.Nodes.Base.Base node, bool callFirst = true){
        }

        /// <summary>
        /// It call the traversal for the edges
        /// </summary>
        /// <param name="node">[in] The node with own type</param>
        /// <param name="callVirtualBase">[in] This paramater is don't used just api copatibility used.</param>
        public void visitAllEdges(Columbus.Csharp.Asg.Nodes.Base.Positioned node, bool callFirst = true){
            visitAllEdges((Columbus.Csharp.Asg.Nodes.Base.Base)(node),false);
        }

        /// <summary>
        /// It call the traversal for the edges
        /// </summary>
        /// <param name="node">[in] The node with own type</param>
        /// <param name="callVirtualBase">[in] This paramater is don't used just api copatibility used.</param>
        public void visitAllEdges(Columbus.Csharp.Asg.Nodes.Expression.AliasQualifiedNameSyntax node, bool callFirst = true){
            visitAllEdges((Columbus.Csharp.Asg.Nodes.Expression.NameSyntax)(node),false);


            Columbus.Csharp.Asg.Nodes.Base.Base genNodePtr;
            // edge: Alias
            genNodePtr = fact.getRef(node.getAlias()) ;
            if (genNodePtr != null) {
              Columbus.Csharp.Asg.Nodes.Expression.IdentifierNameSyntax endNodeRef = (Columbus.Csharp.Asg.Nodes.Expression.IdentifierNameSyntax)(genNodePtr);
              foreach (var visitor in visitorList) {
                visitor.visitAliasQualifiedNameSyntax_Alias(node.Id, endNodeRef.Id);
              }

              clearStoppedVisitors();
              if(needPreorderStop)
                return;

              if ((!fact.IsFilterTurnedOn && !visitFilteredEdge) || (fact.getFilterState(endNodeRef.Id) == Filter.FilterState.NotFiltered) || (!originalFilterState && visitFilteredEdge)) {
                  endNodeRef.accept(this);
              }
              foreach (var visitor in visitorList) {
                visitor.visitEndAliasQualifiedNameSyntax_Alias(node.Id, endNodeRef.Id);
              }

              clearStoppedVisitors();
              if(needPreorderStop)
                return;

            }

            // edge: Name
            genNodePtr = fact.getRef(node.getName()) ;
            if (genNodePtr != null) {
              Columbus.Csharp.Asg.Nodes.Expression.SimpleNameSyntax endNodeRef = (Columbus.Csharp.Asg.Nodes.Expression.SimpleNameSyntax)(genNodePtr);
              foreach (var visitor in visitorList) {
                visitor.visitAliasQualifiedNameSyntax_Name(node.Id, endNodeRef.Id);
              }

              clearStoppedVisitors();
              if(needPreorderStop)
                return;

              if ((!fact.IsFilterTurnedOn && !visitFilteredEdge) || (fact.getFilterState(endNodeRef.Id) == Filter.FilterState.NotFiltered) || (!originalFilterState && visitFilteredEdge)) {
                  endNodeRef.accept(this);
              }
              foreach (var visitor in visitorList) {
                visitor.visitEndAliasQualifiedNameSyntax_Name(node.Id, endNodeRef.Id);
              }

              clearStoppedVisitors();
              if(needPreorderStop)
                return;

            }
        }

        public override void visit(Columbus.Csharp.Asg.Nodes.Expression.AliasQualifiedNameSyntax node, bool callFirst = true){
          if (safeMode || visitCrossEdgeTree) {
            if (safeMode) {
              if (visitedNodes[(int)node.Id]) { // for safemode
                return;
              }
            }
            visitedNodes[(int)node.Id] = true;
          }

          foreach (var visitor in visitorList) {
            visitor.visit(node);
            incVisitorDepth(visitor);
          }

          clearStoppedVisitors();
          if(needPreorderStop)
            return;

          visitAllEdges(node, true);

          foreach (var visitor in visitorList) {
            decVisitorDepth(visitor);
            visitor.visitEnd(node);
          }

          clearStoppedVisitors();
        }

        /// <summary>
        /// It call the traversal for the edges
        /// </summary>
        /// <param name="node">[in] The node with own type</param>
        /// <param name="callVirtualBase">[in] This paramater is don't used just api copatibility used.</param>
        public void visitAllEdges(Columbus.Csharp.Asg.Nodes.Expression.AnonymousFunctionExpressionSyntax node, bool callFirst = true){
            visitAllEdges((Columbus.Csharp.Asg.Nodes.Expression.ExpressionSyntax)(node),false);


            Columbus.Csharp.Asg.Nodes.Base.Base genNodePtr;
            // edge: Block
            genNodePtr = fact.getRef(node.getBlock()) ;
            if (genNodePtr != null) {
              Columbus.Csharp.Asg.Nodes.Statement.BlockSyntax endNodeRef = (Columbus.Csharp.Asg.Nodes.Statement.BlockSyntax)(genNodePtr);
              foreach (var visitor in visitorList) {
                visitor.visitAnonymousFunctionExpressionSyntax_Block(node.Id, endNodeRef.Id);
              }

              clearStoppedVisitors();
              if(needPreorderStop)
                return;

              if ((!fact.IsFilterTurnedOn && !visitFilteredEdge) || (fact.getFilterState(endNodeRef.Id) == Filter.FilterState.NotFiltered) || (!originalFilterState && visitFilteredEdge)) {
                  endNodeRef.accept(this);
              }
              foreach (var visitor in visitorList) {
                visitor.visitEndAnonymousFunctionExpressionSyntax_Block(node.Id, endNodeRef.Id);
              }

              clearStoppedVisitors();
              if(needPreorderStop)
                return;

            }

            // edge: ExpressionBody
            genNodePtr = fact.getRef(node.getExpressionBody()) ;
            if (genNodePtr != null) {
              Columbus.Csharp.Asg.Nodes.Expression.ExpressionSyntax endNodeRef = (Columbus.Csharp.Asg.Nodes.Expression.ExpressionSyntax)(genNodePtr);
              foreach (var visitor in visitorList) {
                visitor.visitAnonymousFunctionExpressionSyntax_ExpressionBody(node.Id, endNodeRef.Id);
              }

              clearStoppedVisitors();
              if(needPreorderStop)
                return;

              if ((!fact.IsFilterTurnedOn && !visitFilteredEdge) || (fact.getFilterState(endNodeRef.Id) == Filter.FilterState.NotFiltered) || (!originalFilterState && visitFilteredEdge)) {
                  endNodeRef.accept(this);
              }
              foreach (var visitor in visitorList) {
                visitor.visitEndAnonymousFunctionExpressionSyntax_ExpressionBody(node.Id, endNodeRef.Id);
              }

              clearStoppedVisitors();
              if(needPreorderStop)
                return;

            }
        }

        /// <summary>
        /// It call the traversal for the edges
        /// </summary>
        /// <param name="node">[in] The node with own type</param>
        /// <param name="callVirtualBase">[in] This paramater is don't used just api copatibility used.</param>
        public void visitAllEdges(Columbus.Csharp.Asg.Nodes.Expression.AnonymousMethodExpressionSyntax node, bool callFirst = true){
            visitAllEdges((Columbus.Csharp.Asg.Nodes.Expression.AnonymousFunctionExpressionSyntax)(node),false);


            Columbus.Csharp.Asg.Nodes.Base.Base genNodePtr;
            // edge: ParameterList
            genNodePtr = fact.getRef(node.getParameterList()) ;
            if (genNodePtr != null) {
              Columbus.Csharp.Asg.Nodes.Structure.ParameterListSyntax endNodeRef = (Columbus.Csharp.Asg.Nodes.Structure.ParameterListSyntax)(genNodePtr);
              foreach (var visitor in visitorList) {
                visitor.visitAnonymousMethodExpressionSyntax_ParameterList(node.Id, endNodeRef.Id);
              }

              clearStoppedVisitors();
              if(needPreorderStop)
                return;

              if ((!fact.IsFilterTurnedOn && !visitFilteredEdge) || (fact.getFilterState(endNodeRef.Id) == Filter.FilterState.NotFiltered) || (!originalFilterState && visitFilteredEdge)) {
                  endNodeRef.accept(this);
              }
              foreach (var visitor in visitorList) {
                visitor.visitEndAnonymousMethodExpressionSyntax_ParameterList(node.Id, endNodeRef.Id);
              }

              clearStoppedVisitors();
              if(needPreorderStop)
                return;

            }
        }

        public override void visit(Columbus.Csharp.Asg.Nodes.Expression.AnonymousMethodExpressionSyntax node, bool callFirst = true){
          if (safeMode || visitCrossEdgeTree) {
            if (safeMode) {
              if (visitedNodes[(int)node.Id]) { // for safemode
                return;
              }
            }
            visitedNodes[(int)node.Id] = true;
          }

          foreach (var visitor in visitorList) {
            visitor.visit(node);
            incVisitorDepth(visitor);
          }

          clearStoppedVisitors();
          if(needPreorderStop)
            return;

          visitAllEdges(node, true);

          foreach (var visitor in visitorList) {
            decVisitorDepth(visitor);
            visitor.visitEnd(node);
          }

          clearStoppedVisitors();
        }

        /// <summary>
        /// It call the traversal for the edges
        /// </summary>
        /// <param name="node">[in] The node with own type</param>
        /// <param name="callVirtualBase">[in] This paramater is don't used just api copatibility used.</param>
        public void visitAllEdges(Columbus.Csharp.Asg.Nodes.Expression.AnonymousObjectCreationExpressionSyntax node, bool callFirst = true){
            visitAllEdges((Columbus.Csharp.Asg.Nodes.Expression.ExpressionSyntax)(node),false);


            // edge: Initializers
            ListIterator<Columbus.Csharp.Asg.Nodes.Structure.AnonymousObjectMemberDeclaratorSyntax> iteratorForInitializers = node.InitializersListIteratorBegin;
            while (iteratorForInitializers.getValue() != null) {
               Columbus.Csharp.Asg.Nodes.Structure.AnonymousObjectMemberDeclaratorSyntax endNodeRef = (Columbus.Csharp.Asg.Nodes.Structure.AnonymousObjectMemberDeclaratorSyntax)iteratorForInitializers.getValue();
              foreach (var visitor in visitorList) {
                visitor.visitAnonymousObjectCreationExpressionSyntax_Initializers(node.Id, endNodeRef.Id);
              }

              clearStoppedVisitors();
              if(needPreorderStop)
                return;

              if ((!fact.IsFilterTurnedOn && !visitFilteredEdge) || (fact.getFilterState(endNodeRef.Id) == Filter.FilterState.NotFiltered) || (!originalFilterState && visitFilteredEdge)) {
                  endNodeRef.accept(this);
              }
              foreach (var visitor in visitorList) {
                visitor.visitEndAnonymousObjectCreationExpressionSyntax_Initializers(node.Id, endNodeRef.Id);
              }

              clearStoppedVisitors();
              if(needPreorderStop)
                return;

            iteratorForInitializers = iteratorForInitializers.getNext();
            }
        }

        public override void visit(Columbus.Csharp.Asg.Nodes.Expression.AnonymousObjectCreationExpressionSyntax node, bool callFirst = true){
          if (safeMode || visitCrossEdgeTree) {
            if (safeMode) {
              if (visitedNodes[(int)node.Id]) { // for safemode
                return;
              }
            }
            visitedNodes[(int)node.Id] = true;
          }

          foreach (var visitor in visitorList) {
            visitor.visit(node);
            incVisitorDepth(visitor);
          }

          clearStoppedVisitors();
          if(needPreorderStop)
            return;

          visitAllEdges(node, true);

          foreach (var visitor in visitorList) {
            decVisitorDepth(visitor);
            visitor.visitEnd(node);
          }

          clearStoppedVisitors();
        }

        /// <summary>
        /// It call the traversal for the edges
        /// </summary>
        /// <param name="node">[in] The node with own type</param>
        /// <param name="callVirtualBase">[in] This paramater is don't used just api copatibility used.</param>
        public void visitAllEdges(Columbus.Csharp.Asg.Nodes.Expression.ArrayCreationExpressionSyntax node, bool callFirst = true){
            visitAllEdges((Columbus.Csharp.Asg.Nodes.Expression.ExpressionSyntax)(node),false);


            Columbus.Csharp.Asg.Nodes.Base.Base genNodePtr;
            // edge: Initializer
            genNodePtr = fact.getRef(node.getInitializer()) ;
            if (genNodePtr != null) {
              Columbus.Csharp.Asg.Nodes.Expression.InitializerExpressionSyntax endNodeRef = (Columbus.Csharp.Asg.Nodes.Expression.InitializerExpressionSyntax)(genNodePtr);
              foreach (var visitor in visitorList) {
                visitor.visitArrayCreationExpressionSyntax_Initializer(node.Id, endNodeRef.Id);
              }

              clearStoppedVisitors();
              if(needPreorderStop)
                return;

              if ((!fact.IsFilterTurnedOn && !visitFilteredEdge) || (fact.getFilterState(endNodeRef.Id) == Filter.FilterState.NotFiltered) || (!originalFilterState && visitFilteredEdge)) {
                  endNodeRef.accept(this);
              }
              foreach (var visitor in visitorList) {
                visitor.visitEndArrayCreationExpressionSyntax_Initializer(node.Id, endNodeRef.Id);
              }

              clearStoppedVisitors();
              if(needPreorderStop)
                return;

            }

            // edge: Type
            genNodePtr = fact.getRef(node.getType()) ;
            if (genNodePtr != null) {
              Columbus.Csharp.Asg.Nodes.Expression.ArrayTypeSyntax endNodeRef = (Columbus.Csharp.Asg.Nodes.Expression.ArrayTypeSyntax)(genNodePtr);
              foreach (var visitor in visitorList) {
                visitor.visitArrayCreationExpressionSyntax_Type(node.Id, endNodeRef.Id);
              }

              clearStoppedVisitors();
              if(needPreorderStop)
                return;

              if ((!fact.IsFilterTurnedOn && !visitFilteredEdge) || (fact.getFilterState(endNodeRef.Id) == Filter.FilterState.NotFiltered) || (!originalFilterState && visitFilteredEdge)) {
                  endNodeRef.accept(this);
              }
              foreach (var visitor in visitorList) {
                visitor.visitEndArrayCreationExpressionSyntax_Type(node.Id, endNodeRef.Id);
              }

              clearStoppedVisitors();
              if(needPreorderStop)
                return;

            }
        }

        public override void visit(Columbus.Csharp.Asg.Nodes.Expression.ArrayCreationExpressionSyntax node, bool callFirst = true){
          if (safeMode || visitCrossEdgeTree) {
            if (safeMode) {
              if (visitedNodes[(int)node.Id]) { // for safemode
                return;
              }
            }
            visitedNodes[(int)node.Id] = true;
          }

          foreach (var visitor in visitorList) {
            visitor.visit(node);
            incVisitorDepth(visitor);
          }

          clearStoppedVisitors();
          if(needPreorderStop)
            return;

          visitAllEdges(node, true);

          foreach (var visitor in visitorList) {
            decVisitorDepth(visitor);
            visitor.visitEnd(node);
          }

          clearStoppedVisitors();
        }

        /// <summary>
        /// It call the traversal for the edges
        /// </summary>
        /// <param name="node">[in] The node with own type</param>
        /// <param name="callVirtualBase">[in] This paramater is don't used just api copatibility used.</param>
        public void visitAllEdges(Columbus.Csharp.Asg.Nodes.Expression.ArrayTypeSyntax node, bool callFirst = true){
            visitAllEdges((Columbus.Csharp.Asg.Nodes.Expression.TypeSyntax)(node),false);


            Columbus.Csharp.Asg.Nodes.Base.Base genNodePtr;
            // edge: ElementType
            genNodePtr = fact.getRef(node.getElementType()) ;
            if (genNodePtr != null) {
              Columbus.Csharp.Asg.Nodes.Expression.TypeSyntax endNodeRef = (Columbus.Csharp.Asg.Nodes.Expression.TypeSyntax)(genNodePtr);
              foreach (var visitor in visitorList) {
                visitor.visitArrayTypeSyntax_ElementType(node.Id, endNodeRef.Id);
              }

              clearStoppedVisitors();
              if(needPreorderStop)
                return;

              if ((!fact.IsFilterTurnedOn && !visitFilteredEdge) || (fact.getFilterState(endNodeRef.Id) == Filter.FilterState.NotFiltered) || (!originalFilterState && visitFilteredEdge)) {
                  endNodeRef.accept(this);
              }
              foreach (var visitor in visitorList) {
                visitor.visitEndArrayTypeSyntax_ElementType(node.Id, endNodeRef.Id);
              }

              clearStoppedVisitors();
              if(needPreorderStop)
                return;

            }

            // edge: RankSpecifiers
            ListIterator<Columbus.Csharp.Asg.Nodes.Structure.ArrayRankSpecifierSyntax> iteratorForRankSpecifiers = node.RankSpecifiersListIteratorBegin;
            while (iteratorForRankSpecifiers.getValue() != null) {
               Columbus.Csharp.Asg.Nodes.Structure.ArrayRankSpecifierSyntax endNodeRef = (Columbus.Csharp.Asg.Nodes.Structure.ArrayRankSpecifierSyntax)iteratorForRankSpecifiers.getValue();
              foreach (var visitor in visitorList) {
                visitor.visitArrayTypeSyntax_RankSpecifiers(node.Id, endNodeRef.Id);
              }

              clearStoppedVisitors();
              if(needPreorderStop)
                return;

              if ((!fact.IsFilterTurnedOn && !visitFilteredEdge) || (fact.getFilterState(endNodeRef.Id) == Filter.FilterState.NotFiltered) || (!originalFilterState && visitFilteredEdge)) {
                  endNodeRef.accept(this);
              }
              foreach (var visitor in visitorList) {
                visitor.visitEndArrayTypeSyntax_RankSpecifiers(node.Id, endNodeRef.Id);
              }

              clearStoppedVisitors();
              if(needPreorderStop)
                return;

            iteratorForRankSpecifiers = iteratorForRankSpecifiers.getNext();
            }
        }

        public override void visit(Columbus.Csharp.Asg.Nodes.Expression.ArrayTypeSyntax node, bool callFirst = true){
          if (safeMode || visitCrossEdgeTree) {
            if (safeMode) {
              if (visitedNodes[(int)node.Id]) { // for safemode
                return;
              }
            }
            visitedNodes[(int)node.Id] = true;
          }

          foreach (var visitor in visitorList) {
            visitor.visit(node);
            incVisitorDepth(visitor);
          }

          clearStoppedVisitors();
          if(needPreorderStop)
            return;

          visitAllEdges(node, true);

          foreach (var visitor in visitorList) {
            decVisitorDepth(visitor);
            visitor.visitEnd(node);
          }

          clearStoppedVisitors();
        }

        /// <summary>
        /// It call the traversal for the edges
        /// </summary>
        /// <param name="node">[in] The node with own type</param>
        /// <param name="callVirtualBase">[in] This paramater is don't used just api copatibility used.</param>
        public void visitAllEdges(Columbus.Csharp.Asg.Nodes.Expression.AssignmentExpressionSyntax node, bool callFirst = true){
            visitAllEdges((Columbus.Csharp.Asg.Nodes.Expression.ExpressionSyntax)(node),false);


            Columbus.Csharp.Asg.Nodes.Base.Base genNodePtr;
            // edge: EventAccessorCall
            genNodePtr = fact.getRef(node.getEventAccessorCall()) ;
            if (genNodePtr != null) {
              Columbus.Csharp.Asg.Nodes.Structure.AccessorDeclarationSyntax endNodeRef = (Columbus.Csharp.Asg.Nodes.Structure.AccessorDeclarationSyntax)(genNodePtr);
              foreach (var visitor in visitorList) {
                visitor.visitAssignmentExpressionSyntax_EventAccessorCall(node.Id, endNodeRef.Id);
              }

              clearStoppedVisitors();
              if(needPreorderStop)
                return;

              if ((!fact.IsFilterTurnedOn && !visitFilteredEdge) || (fact.getFilterState(endNodeRef.Id) == Filter.FilterState.NotFiltered) || (!originalFilterState && visitFilteredEdge)) {
                  if (apRoot != null) {
                    if (visitCrossEdgeTree) {
                      unvisitedNodes[(int)endNodeRef.Id] = true;
                    }
                  }
                  if (traversaldCrossEdges[(int)Types.EdgeKind.edkAssignmentExpressionSyntax_EventAccessorCall]) {
                    endNodeRef.accept(this);
                  }
              }
              foreach (var visitor in visitorList) {
                visitor.visitEndAssignmentExpressionSyntax_EventAccessorCall(node.Id, endNodeRef.Id);
              }

              clearStoppedVisitors();
              if(needPreorderStop)
                return;

            }

            // edge: Left
            genNodePtr = fact.getRef(node.getLeft()) ;
            if (genNodePtr != null) {
              Columbus.Csharp.Asg.Nodes.Expression.ExpressionSyntax endNodeRef = (Columbus.Csharp.Asg.Nodes.Expression.ExpressionSyntax)(genNodePtr);
              foreach (var visitor in visitorList) {
                visitor.visitAssignmentExpressionSyntax_Left(node.Id, endNodeRef.Id);
              }

              clearStoppedVisitors();
              if(needPreorderStop)
                return;

              if ((!fact.IsFilterTurnedOn && !visitFilteredEdge) || (fact.getFilterState(endNodeRef.Id) == Filter.FilterState.NotFiltered) || (!originalFilterState && visitFilteredEdge)) {
                  endNodeRef.accept(this);
              }
              foreach (var visitor in visitorList) {
                visitor.visitEndAssignmentExpressionSyntax_Left(node.Id, endNodeRef.Id);
              }

              clearStoppedVisitors();
              if(needPreorderStop)
                return;

            }

            // edge: OverloadedOperatorCall
            genNodePtr = fact.getRef(node.getOverloadedOperatorCall()) ;
            if (genNodePtr != null) {
              Columbus.Csharp.Asg.Nodes.Structure.OperatorDeclarationSyntax endNodeRef = (Columbus.Csharp.Asg.Nodes.Structure.OperatorDeclarationSyntax)(genNodePtr);
              foreach (var visitor in visitorList) {
                visitor.visitAssignmentExpressionSyntax_OverloadedOperatorCall(node.Id, endNodeRef.Id);
              }

              clearStoppedVisitors();
              if(needPreorderStop)
                return;

              if ((!fact.IsFilterTurnedOn && !visitFilteredEdge) || (fact.getFilterState(endNodeRef.Id) == Filter.FilterState.NotFiltered) || (!originalFilterState && visitFilteredEdge)) {
                  if (apRoot != null) {
                    if (visitCrossEdgeTree) {
                      unvisitedNodes[(int)endNodeRef.Id] = true;
                    }
                  }
                  if (traversaldCrossEdges[(int)Types.EdgeKind.edkAssignmentExpressionSyntax_OverloadedOperatorCall]) {
                    endNodeRef.accept(this);
                  }
              }
              foreach (var visitor in visitorList) {
                visitor.visitEndAssignmentExpressionSyntax_OverloadedOperatorCall(node.Id, endNodeRef.Id);
              }

              clearStoppedVisitors();
              if(needPreorderStop)
                return;

            }

            // edge: Right
            genNodePtr = fact.getRef(node.getRight()) ;
            if (genNodePtr != null) {
              Columbus.Csharp.Asg.Nodes.Expression.ExpressionSyntax endNodeRef = (Columbus.Csharp.Asg.Nodes.Expression.ExpressionSyntax)(genNodePtr);
              foreach (var visitor in visitorList) {
                visitor.visitAssignmentExpressionSyntax_Right(node.Id, endNodeRef.Id);
              }

              clearStoppedVisitors();
              if(needPreorderStop)
                return;

              if ((!fact.IsFilterTurnedOn && !visitFilteredEdge) || (fact.getFilterState(endNodeRef.Id) == Filter.FilterState.NotFiltered) || (!originalFilterState && visitFilteredEdge)) {
                  endNodeRef.accept(this);
              }
              foreach (var visitor in visitorList) {
                visitor.visitEndAssignmentExpressionSyntax_Right(node.Id, endNodeRef.Id);
              }

              clearStoppedVisitors();
              if(needPreorderStop)
                return;

            }
        }

        public override void visit(Columbus.Csharp.Asg.Nodes.Expression.AssignmentExpressionSyntax node, bool callFirst = true){
          if (safeMode || visitCrossEdgeTree) {
            if (safeMode) {
              if (visitedNodes[(int)node.Id]) { // for safemode
                return;
              }
            }
            visitedNodes[(int)node.Id] = true;
          }

          foreach (var visitor in visitorList) {
            visitor.visit(node);
            incVisitorDepth(visitor);
          }

          clearStoppedVisitors();
          if(needPreorderStop)
            return;

          visitAllEdges(node, true);

          foreach (var visitor in visitorList) {
            decVisitorDepth(visitor);
            visitor.visitEnd(node);
          }

          clearStoppedVisitors();
        }

        /// <summary>
        /// It call the traversal for the edges
        /// </summary>
        /// <param name="node">[in] The node with own type</param>
        /// <param name="callVirtualBase">[in] This paramater is don't used just api copatibility used.</param>
        public void visitAllEdges(Columbus.Csharp.Asg.Nodes.Expression.AwaitExpressionSyntax node, bool callFirst = true){
            visitAllEdges((Columbus.Csharp.Asg.Nodes.Expression.ExpressionSyntax)(node),false);


            Columbus.Csharp.Asg.Nodes.Base.Base genNodePtr;
            // edge: Expression
            genNodePtr = fact.getRef(node.getExpression()) ;
            if (genNodePtr != null) {
              Columbus.Csharp.Asg.Nodes.Expression.ExpressionSyntax endNodeRef = (Columbus.Csharp.Asg.Nodes.Expression.ExpressionSyntax)(genNodePtr);
              foreach (var visitor in visitorList) {
                visitor.visitAwaitExpressionSyntax_Expression(node.Id, endNodeRef.Id);
              }

              clearStoppedVisitors();
              if(needPreorderStop)
                return;

              if ((!fact.IsFilterTurnedOn && !visitFilteredEdge) || (fact.getFilterState(endNodeRef.Id) == Filter.FilterState.NotFiltered) || (!originalFilterState && visitFilteredEdge)) {
                  endNodeRef.accept(this);
              }
              foreach (var visitor in visitorList) {
                visitor.visitEndAwaitExpressionSyntax_Expression(node.Id, endNodeRef.Id);
              }

              clearStoppedVisitors();
              if(needPreorderStop)
                return;

            }
        }

        public override void visit(Columbus.Csharp.Asg.Nodes.Expression.AwaitExpressionSyntax node, bool callFirst = true){
          if (safeMode || visitCrossEdgeTree) {
            if (safeMode) {
              if (visitedNodes[(int)node.Id]) { // for safemode
                return;
              }
            }
            visitedNodes[(int)node.Id] = true;
          }

          foreach (var visitor in visitorList) {
            visitor.visit(node);
            incVisitorDepth(visitor);
          }

          clearStoppedVisitors();
          if(needPreorderStop)
            return;

          visitAllEdges(node, true);

          foreach (var visitor in visitorList) {
            decVisitorDepth(visitor);
            visitor.visitEnd(node);
          }

          clearStoppedVisitors();
        }

        /// <summary>
        /// It call the traversal for the edges
        /// </summary>
        /// <param name="node">[in] The node with own type</param>
        /// <param name="callVirtualBase">[in] This paramater is don't used just api copatibility used.</param>
        public void visitAllEdges(Columbus.Csharp.Asg.Nodes.Expression.BaseExpressionSyntax node, bool callFirst = true){
            visitAllEdges((Columbus.Csharp.Asg.Nodes.Expression.InstanceExpressionSyntax)(node),false);
        }

        public override void visit(Columbus.Csharp.Asg.Nodes.Expression.BaseExpressionSyntax node, bool callFirst = true){
          if (safeMode || visitCrossEdgeTree) {
            if (safeMode) {
              if (visitedNodes[(int)node.Id]) { // for safemode
                return;
              }
            }
            visitedNodes[(int)node.Id] = true;
          }

          foreach (var visitor in visitorList) {
            visitor.visit(node);
            incVisitorDepth(visitor);
          }

          clearStoppedVisitors();
          if(needPreorderStop)
            return;

          visitAllEdges(node, true);

          foreach (var visitor in visitorList) {
            decVisitorDepth(visitor);
            visitor.visitEnd(node);
          }

          clearStoppedVisitors();
        }

        /// <summary>
        /// It call the traversal for the edges
        /// </summary>
        /// <param name="node">[in] The node with own type</param>
        /// <param name="callVirtualBase">[in] This paramater is don't used just api copatibility used.</param>
        public void visitAllEdges(Columbus.Csharp.Asg.Nodes.Expression.BinaryExpressionSyntax node, bool callFirst = true){
            visitAllEdges((Columbus.Csharp.Asg.Nodes.Expression.ExpressionSyntax)(node),false);


            Columbus.Csharp.Asg.Nodes.Base.Base genNodePtr;
            // edge: Left
            genNodePtr = fact.getRef(node.getLeft()) ;
            if (genNodePtr != null) {
              Columbus.Csharp.Asg.Nodes.Expression.ExpressionSyntax endNodeRef = (Columbus.Csharp.Asg.Nodes.Expression.ExpressionSyntax)(genNodePtr);
              foreach (var visitor in visitorList) {
                visitor.visitBinaryExpressionSyntax_Left(node.Id, endNodeRef.Id);
              }

              clearStoppedVisitors();
              if(needPreorderStop)
                return;

              if ((!fact.IsFilterTurnedOn && !visitFilteredEdge) || (fact.getFilterState(endNodeRef.Id) == Filter.FilterState.NotFiltered) || (!originalFilterState && visitFilteredEdge)) {
                  endNodeRef.accept(this);
              }
              foreach (var visitor in visitorList) {
                visitor.visitEndBinaryExpressionSyntax_Left(node.Id, endNodeRef.Id);
              }

              clearStoppedVisitors();
              if(needPreorderStop)
                return;

            }

            // edge: OverloadedOperatorCall
            genNodePtr = fact.getRef(node.getOverloadedOperatorCall()) ;
            if (genNodePtr != null) {
              Columbus.Csharp.Asg.Nodes.Structure.OperatorDeclarationSyntax endNodeRef = (Columbus.Csharp.Asg.Nodes.Structure.OperatorDeclarationSyntax)(genNodePtr);
              foreach (var visitor in visitorList) {
                visitor.visitBinaryExpressionSyntax_OverloadedOperatorCall(node.Id, endNodeRef.Id);
              }

              clearStoppedVisitors();
              if(needPreorderStop)
                return;

              if ((!fact.IsFilterTurnedOn && !visitFilteredEdge) || (fact.getFilterState(endNodeRef.Id) == Filter.FilterState.NotFiltered) || (!originalFilterState && visitFilteredEdge)) {
                  if (apRoot != null) {
                    if (visitCrossEdgeTree) {
                      unvisitedNodes[(int)endNodeRef.Id] = true;
                    }
                  }
                  if (traversaldCrossEdges[(int)Types.EdgeKind.edkBinaryExpressionSyntax_OverloadedOperatorCall]) {
                    endNodeRef.accept(this);
                  }
              }
              foreach (var visitor in visitorList) {
                visitor.visitEndBinaryExpressionSyntax_OverloadedOperatorCall(node.Id, endNodeRef.Id);
              }

              clearStoppedVisitors();
              if(needPreorderStop)
                return;

            }

            // edge: Right
            genNodePtr = fact.getRef(node.getRight()) ;
            if (genNodePtr != null) {
              Columbus.Csharp.Asg.Nodes.Expression.ExpressionSyntax endNodeRef = (Columbus.Csharp.Asg.Nodes.Expression.ExpressionSyntax)(genNodePtr);
              foreach (var visitor in visitorList) {
                visitor.visitBinaryExpressionSyntax_Right(node.Id, endNodeRef.Id);
              }

              clearStoppedVisitors();
              if(needPreorderStop)
                return;

              if ((!fact.IsFilterTurnedOn && !visitFilteredEdge) || (fact.getFilterState(endNodeRef.Id) == Filter.FilterState.NotFiltered) || (!originalFilterState && visitFilteredEdge)) {
                  endNodeRef.accept(this);
              }
              foreach (var visitor in visitorList) {
                visitor.visitEndBinaryExpressionSyntax_Right(node.Id, endNodeRef.Id);
              }

              clearStoppedVisitors();
              if(needPreorderStop)
                return;

            }
        }

        public override void visit(Columbus.Csharp.Asg.Nodes.Expression.BinaryExpressionSyntax node, bool callFirst = true){
          if (safeMode || visitCrossEdgeTree) {
            if (safeMode) {
              if (visitedNodes[(int)node.Id]) { // for safemode
                return;
              }
            }
            visitedNodes[(int)node.Id] = true;
          }

          foreach (var visitor in visitorList) {
            visitor.visit(node);
            incVisitorDepth(visitor);
          }

          clearStoppedVisitors();
          if(needPreorderStop)
            return;

          visitAllEdges(node, true);

          foreach (var visitor in visitorList) {
            decVisitorDepth(visitor);
            visitor.visitEnd(node);
          }

          clearStoppedVisitors();
        }

        /// <summary>
        /// It call the traversal for the edges
        /// </summary>
        /// <param name="node">[in] The node with own type</param>
        /// <param name="callVirtualBase">[in] This paramater is don't used just api copatibility used.</param>
        public void visitAllEdges(Columbus.Csharp.Asg.Nodes.Expression.CastExpressionSyntax node, bool callFirst = true){
            visitAllEdges((Columbus.Csharp.Asg.Nodes.Expression.ExpressionSyntax)(node),false);


            Columbus.Csharp.Asg.Nodes.Base.Base genNodePtr;
            // edge: ConversionOperatorCall
            genNodePtr = fact.getRef(node.getConversionOperatorCall()) ;
            if (genNodePtr != null) {
              Columbus.Csharp.Asg.Nodes.Structure.ConversionOperatorDeclarationSyntax endNodeRef = (Columbus.Csharp.Asg.Nodes.Structure.ConversionOperatorDeclarationSyntax)(genNodePtr);
              foreach (var visitor in visitorList) {
                visitor.visitCastExpressionSyntax_ConversionOperatorCall(node.Id, endNodeRef.Id);
              }

              clearStoppedVisitors();
              if(needPreorderStop)
                return;

              if ((!fact.IsFilterTurnedOn && !visitFilteredEdge) || (fact.getFilterState(endNodeRef.Id) == Filter.FilterState.NotFiltered) || (!originalFilterState && visitFilteredEdge)) {
                  if (apRoot != null) {
                    if (visitCrossEdgeTree) {
                      unvisitedNodes[(int)endNodeRef.Id] = true;
                    }
                  }
                  if (traversaldCrossEdges[(int)Types.EdgeKind.edkCastExpressionSyntax_ConversionOperatorCall]) {
                    endNodeRef.accept(this);
                  }
              }
              foreach (var visitor in visitorList) {
                visitor.visitEndCastExpressionSyntax_ConversionOperatorCall(node.Id, endNodeRef.Id);
              }

              clearStoppedVisitors();
              if(needPreorderStop)
                return;

            }

            // edge: Expression
            genNodePtr = fact.getRef(node.getExpression()) ;
            if (genNodePtr != null) {
              Columbus.Csharp.Asg.Nodes.Expression.ExpressionSyntax endNodeRef = (Columbus.Csharp.Asg.Nodes.Expression.ExpressionSyntax)(genNodePtr);
              foreach (var visitor in visitorList) {
                visitor.visitCastExpressionSyntax_Expression(node.Id, endNodeRef.Id);
              }

              clearStoppedVisitors();
              if(needPreorderStop)
                return;

              if ((!fact.IsFilterTurnedOn && !visitFilteredEdge) || (fact.getFilterState(endNodeRef.Id) == Filter.FilterState.NotFiltered) || (!originalFilterState && visitFilteredEdge)) {
                  endNodeRef.accept(this);
              }
              foreach (var visitor in visitorList) {
                visitor.visitEndCastExpressionSyntax_Expression(node.Id, endNodeRef.Id);
              }

              clearStoppedVisitors();
              if(needPreorderStop)
                return;

            }

            // edge: Type
            genNodePtr = fact.getRef(node.getType()) ;
            if (genNodePtr != null) {
              Columbus.Csharp.Asg.Nodes.Expression.TypeSyntax endNodeRef = (Columbus.Csharp.Asg.Nodes.Expression.TypeSyntax)(genNodePtr);
              foreach (var visitor in visitorList) {
                visitor.visitCastExpressionSyntax_Type(node.Id, endNodeRef.Id);
              }

              clearStoppedVisitors();
              if(needPreorderStop)
                return;

              if ((!fact.IsFilterTurnedOn && !visitFilteredEdge) || (fact.getFilterState(endNodeRef.Id) == Filter.FilterState.NotFiltered) || (!originalFilterState && visitFilteredEdge)) {
                  endNodeRef.accept(this);
              }
              foreach (var visitor in visitorList) {
                visitor.visitEndCastExpressionSyntax_Type(node.Id, endNodeRef.Id);
              }

              clearStoppedVisitors();
              if(needPreorderStop)
                return;

            }
        }

        public override void visit(Columbus.Csharp.Asg.Nodes.Expression.CastExpressionSyntax node, bool callFirst = true){
          if (safeMode || visitCrossEdgeTree) {
            if (safeMode) {
              if (visitedNodes[(int)node.Id]) { // for safemode
                return;
              }
            }
            visitedNodes[(int)node.Id] = true;
          }

          foreach (var visitor in visitorList) {
            visitor.visit(node);
            incVisitorDepth(visitor);
          }

          clearStoppedVisitors();
          if(needPreorderStop)
            return;

          visitAllEdges(node, true);

          foreach (var visitor in visitorList) {
            decVisitorDepth(visitor);
            visitor.visitEnd(node);
          }

          clearStoppedVisitors();
        }

        /// <summary>
        /// It call the traversal for the edges
        /// </summary>
        /// <param name="node">[in] The node with own type</param>
        /// <param name="callVirtualBase">[in] This paramater is don't used just api copatibility used.</param>
        public void visitAllEdges(Columbus.Csharp.Asg.Nodes.Expression.CheckedExpressionSyntax node, bool callFirst = true){
            visitAllEdges((Columbus.Csharp.Asg.Nodes.Expression.ExpressionSyntax)(node),false);


            Columbus.Csharp.Asg.Nodes.Base.Base genNodePtr;
            // edge: Expression
            genNodePtr = fact.getRef(node.getExpression()) ;
            if (genNodePtr != null) {
              Columbus.Csharp.Asg.Nodes.Expression.ExpressionSyntax endNodeRef = (Columbus.Csharp.Asg.Nodes.Expression.ExpressionSyntax)(genNodePtr);
              foreach (var visitor in visitorList) {
                visitor.visitCheckedExpressionSyntax_Expression(node.Id, endNodeRef.Id);
              }

              clearStoppedVisitors();
              if(needPreorderStop)
                return;

              if ((!fact.IsFilterTurnedOn && !visitFilteredEdge) || (fact.getFilterState(endNodeRef.Id) == Filter.FilterState.NotFiltered) || (!originalFilterState && visitFilteredEdge)) {
                  endNodeRef.accept(this);
              }
              foreach (var visitor in visitorList) {
                visitor.visitEndCheckedExpressionSyntax_Expression(node.Id, endNodeRef.Id);
              }

              clearStoppedVisitors();
              if(needPreorderStop)
                return;

            }
        }

        public override void visit(Columbus.Csharp.Asg.Nodes.Expression.CheckedExpressionSyntax node, bool callFirst = true){
          if (safeMode || visitCrossEdgeTree) {
            if (safeMode) {
              if (visitedNodes[(int)node.Id]) { // for safemode
                return;
              }
            }
            visitedNodes[(int)node.Id] = true;
          }

          foreach (var visitor in visitorList) {
            visitor.visit(node);
            incVisitorDepth(visitor);
          }

          clearStoppedVisitors();
          if(needPreorderStop)
            return;

          visitAllEdges(node, true);

          foreach (var visitor in visitorList) {
            decVisitorDepth(visitor);
            visitor.visitEnd(node);
          }

          clearStoppedVisitors();
        }

        /// <summary>
        /// It call the traversal for the edges
        /// </summary>
        /// <param name="node">[in] The node with own type</param>
        /// <param name="callVirtualBase">[in] This paramater is don't used just api copatibility used.</param>
        public void visitAllEdges(Columbus.Csharp.Asg.Nodes.Expression.ConditionalAccessExpressionSyntax node, bool callFirst = true){
            visitAllEdges((Columbus.Csharp.Asg.Nodes.Expression.ExpressionSyntax)(node),false);


            Columbus.Csharp.Asg.Nodes.Base.Base genNodePtr;
            // edge: Expression
            genNodePtr = fact.getRef(node.getExpression()) ;
            if (genNodePtr != null) {
              Columbus.Csharp.Asg.Nodes.Expression.ExpressionSyntax endNodeRef = (Columbus.Csharp.Asg.Nodes.Expression.ExpressionSyntax)(genNodePtr);
              foreach (var visitor in visitorList) {
                visitor.visitConditionalAccessExpressionSyntax_Expression(node.Id, endNodeRef.Id);
              }

              clearStoppedVisitors();
              if(needPreorderStop)
                return;

              if ((!fact.IsFilterTurnedOn && !visitFilteredEdge) || (fact.getFilterState(endNodeRef.Id) == Filter.FilterState.NotFiltered) || (!originalFilterState && visitFilteredEdge)) {
                  endNodeRef.accept(this);
              }
              foreach (var visitor in visitorList) {
                visitor.visitEndConditionalAccessExpressionSyntax_Expression(node.Id, endNodeRef.Id);
              }

              clearStoppedVisitors();
              if(needPreorderStop)
                return;

            }

            // edge: WhenNotNull
            genNodePtr = fact.getRef(node.getWhenNotNull()) ;
            if (genNodePtr != null) {
              Columbus.Csharp.Asg.Nodes.Expression.ExpressionSyntax endNodeRef = (Columbus.Csharp.Asg.Nodes.Expression.ExpressionSyntax)(genNodePtr);
              foreach (var visitor in visitorList) {
                visitor.visitConditionalAccessExpressionSyntax_WhenNotNull(node.Id, endNodeRef.Id);
              }

              clearStoppedVisitors();
              if(needPreorderStop)
                return;

              if ((!fact.IsFilterTurnedOn && !visitFilteredEdge) || (fact.getFilterState(endNodeRef.Id) == Filter.FilterState.NotFiltered) || (!originalFilterState && visitFilteredEdge)) {
                  endNodeRef.accept(this);
              }
              foreach (var visitor in visitorList) {
                visitor.visitEndConditionalAccessExpressionSyntax_WhenNotNull(node.Id, endNodeRef.Id);
              }

              clearStoppedVisitors();
              if(needPreorderStop)
                return;

            }
        }

        public override void visit(Columbus.Csharp.Asg.Nodes.Expression.ConditionalAccessExpressionSyntax node, bool callFirst = true){
          if (safeMode || visitCrossEdgeTree) {
            if (safeMode) {
              if (visitedNodes[(int)node.Id]) { // for safemode
                return;
              }
            }
            visitedNodes[(int)node.Id] = true;
          }

          foreach (var visitor in visitorList) {
            visitor.visit(node);
            incVisitorDepth(visitor);
          }

          clearStoppedVisitors();
          if(needPreorderStop)
            return;

          visitAllEdges(node, true);

          foreach (var visitor in visitorList) {
            decVisitorDepth(visitor);
            visitor.visitEnd(node);
          }

          clearStoppedVisitors();
        }

        /// <summary>
        /// It call the traversal for the edges
        /// </summary>
        /// <param name="node">[in] The node with own type</param>
        /// <param name="callVirtualBase">[in] This paramater is don't used just api copatibility used.</param>
        public void visitAllEdges(Columbus.Csharp.Asg.Nodes.Expression.ConditionalExpressionSyntax node, bool callFirst = true){
            visitAllEdges((Columbus.Csharp.Asg.Nodes.Expression.ExpressionSyntax)(node),false);


            Columbus.Csharp.Asg.Nodes.Base.Base genNodePtr;
            // edge: Condition
            genNodePtr = fact.getRef(node.getCondition()) ;
            if (genNodePtr != null) {
              Columbus.Csharp.Asg.Nodes.Expression.ExpressionSyntax endNodeRef = (Columbus.Csharp.Asg.Nodes.Expression.ExpressionSyntax)(genNodePtr);
              foreach (var visitor in visitorList) {
                visitor.visitConditionalExpressionSyntax_Condition(node.Id, endNodeRef.Id);
              }

              clearStoppedVisitors();
              if(needPreorderStop)
                return;

              if ((!fact.IsFilterTurnedOn && !visitFilteredEdge) || (fact.getFilterState(endNodeRef.Id) == Filter.FilterState.NotFiltered) || (!originalFilterState && visitFilteredEdge)) {
                  endNodeRef.accept(this);
              }
              foreach (var visitor in visitorList) {
                visitor.visitEndConditionalExpressionSyntax_Condition(node.Id, endNodeRef.Id);
              }

              clearStoppedVisitors();
              if(needPreorderStop)
                return;

            }

            // edge: WhenFalse
            genNodePtr = fact.getRef(node.getWhenFalse()) ;
            if (genNodePtr != null) {
              Columbus.Csharp.Asg.Nodes.Expression.ExpressionSyntax endNodeRef = (Columbus.Csharp.Asg.Nodes.Expression.ExpressionSyntax)(genNodePtr);
              foreach (var visitor in visitorList) {
                visitor.visitConditionalExpressionSyntax_WhenFalse(node.Id, endNodeRef.Id);
              }

              clearStoppedVisitors();
              if(needPreorderStop)
                return;

              if ((!fact.IsFilterTurnedOn && !visitFilteredEdge) || (fact.getFilterState(endNodeRef.Id) == Filter.FilterState.NotFiltered) || (!originalFilterState && visitFilteredEdge)) {
                  endNodeRef.accept(this);
              }
              foreach (var visitor in visitorList) {
                visitor.visitEndConditionalExpressionSyntax_WhenFalse(node.Id, endNodeRef.Id);
              }

              clearStoppedVisitors();
              if(needPreorderStop)
                return;

            }

            // edge: WhenTrue
            genNodePtr = fact.getRef(node.getWhenTrue()) ;
            if (genNodePtr != null) {
              Columbus.Csharp.Asg.Nodes.Expression.ExpressionSyntax endNodeRef = (Columbus.Csharp.Asg.Nodes.Expression.ExpressionSyntax)(genNodePtr);
              foreach (var visitor in visitorList) {
                visitor.visitConditionalExpressionSyntax_WhenTrue(node.Id, endNodeRef.Id);
              }

              clearStoppedVisitors();
              if(needPreorderStop)
                return;

              if ((!fact.IsFilterTurnedOn && !visitFilteredEdge) || (fact.getFilterState(endNodeRef.Id) == Filter.FilterState.NotFiltered) || (!originalFilterState && visitFilteredEdge)) {
                  endNodeRef.accept(this);
              }
              foreach (var visitor in visitorList) {
                visitor.visitEndConditionalExpressionSyntax_WhenTrue(node.Id, endNodeRef.Id);
              }

              clearStoppedVisitors();
              if(needPreorderStop)
                return;

            }
        }

        public override void visit(Columbus.Csharp.Asg.Nodes.Expression.ConditionalExpressionSyntax node, bool callFirst = true){
          if (safeMode || visitCrossEdgeTree) {
            if (safeMode) {
              if (visitedNodes[(int)node.Id]) { // for safemode
                return;
              }
            }
            visitedNodes[(int)node.Id] = true;
          }

          foreach (var visitor in visitorList) {
            visitor.visit(node);
            incVisitorDepth(visitor);
          }

          clearStoppedVisitors();
          if(needPreorderStop)
            return;

          visitAllEdges(node, true);

          foreach (var visitor in visitorList) {
            decVisitorDepth(visitor);
            visitor.visitEnd(node);
          }

          clearStoppedVisitors();
        }

        /// <summary>
        /// It call the traversal for the edges
        /// </summary>
        /// <param name="node">[in] The node with own type</param>
        /// <param name="callVirtualBase">[in] This paramater is don't used just api copatibility used.</param>
        public void visitAllEdges(Columbus.Csharp.Asg.Nodes.Expression.DeclarationExpressionSyntax node, bool callFirst = true){
            visitAllEdges((Columbus.Csharp.Asg.Nodes.Expression.ExpressionSyntax)(node),false);


            Columbus.Csharp.Asg.Nodes.Base.Base genNodePtr;
            // edge: Designation
            genNodePtr = fact.getRef(node.getDesignation()) ;
            if (genNodePtr != null) {
              Columbus.Csharp.Asg.Nodes.Structure.VariableDesignationSyntax endNodeRef = (Columbus.Csharp.Asg.Nodes.Structure.VariableDesignationSyntax)(genNodePtr);
              foreach (var visitor in visitorList) {
                visitor.visitDeclarationExpressionSyntax_Designation(node.Id, endNodeRef.Id);
              }

              clearStoppedVisitors();
              if(needPreorderStop)
                return;

              if ((!fact.IsFilterTurnedOn && !visitFilteredEdge) || (fact.getFilterState(endNodeRef.Id) == Filter.FilterState.NotFiltered) || (!originalFilterState && visitFilteredEdge)) {
                  endNodeRef.accept(this);
              }
              foreach (var visitor in visitorList) {
                visitor.visitEndDeclarationExpressionSyntax_Designation(node.Id, endNodeRef.Id);
              }

              clearStoppedVisitors();
              if(needPreorderStop)
                return;

            }

            // edge: Type
            genNodePtr = fact.getRef(node.getType()) ;
            if (genNodePtr != null) {
              Columbus.Csharp.Asg.Nodes.Expression.TypeSyntax endNodeRef = (Columbus.Csharp.Asg.Nodes.Expression.TypeSyntax)(genNodePtr);
              foreach (var visitor in visitorList) {
                visitor.visitDeclarationExpressionSyntax_Type(node.Id, endNodeRef.Id);
              }

              clearStoppedVisitors();
              if(needPreorderStop)
                return;

              if ((!fact.IsFilterTurnedOn && !visitFilteredEdge) || (fact.getFilterState(endNodeRef.Id) == Filter.FilterState.NotFiltered) || (!originalFilterState && visitFilteredEdge)) {
                  endNodeRef.accept(this);
              }
              foreach (var visitor in visitorList) {
                visitor.visitEndDeclarationExpressionSyntax_Type(node.Id, endNodeRef.Id);
              }

              clearStoppedVisitors();
              if(needPreorderStop)
                return;

            }
        }

        public override void visit(Columbus.Csharp.Asg.Nodes.Expression.DeclarationExpressionSyntax node, bool callFirst = true){
          if (safeMode || visitCrossEdgeTree) {
            if (safeMode) {
              if (visitedNodes[(int)node.Id]) { // for safemode
                return;
              }
            }
            visitedNodes[(int)node.Id] = true;
          }

          foreach (var visitor in visitorList) {
            visitor.visit(node);
            incVisitorDepth(visitor);
          }

          clearStoppedVisitors();
          if(needPreorderStop)
            return;

          visitAllEdges(node, true);

          foreach (var visitor in visitorList) {
            decVisitorDepth(visitor);
            visitor.visitEnd(node);
          }

          clearStoppedVisitors();
        }

        /// <summary>
        /// It call the traversal for the edges
        /// </summary>
        /// <param name="node">[in] The node with own type</param>
        /// <param name="callVirtualBase">[in] This paramater is don't used just api copatibility used.</param>
        public void visitAllEdges(Columbus.Csharp.Asg.Nodes.Expression.DefaultExpressionSyntax node, bool callFirst = true){
            visitAllEdges((Columbus.Csharp.Asg.Nodes.Expression.ExpressionSyntax)(node),false);


            Columbus.Csharp.Asg.Nodes.Base.Base genNodePtr;
            // edge: Type
            genNodePtr = fact.getRef(node.getType()) ;
            if (genNodePtr != null) {
              Columbus.Csharp.Asg.Nodes.Expression.TypeSyntax endNodeRef = (Columbus.Csharp.Asg.Nodes.Expression.TypeSyntax)(genNodePtr);
              foreach (var visitor in visitorList) {
                visitor.visitDefaultExpressionSyntax_Type(node.Id, endNodeRef.Id);
              }

              clearStoppedVisitors();
              if(needPreorderStop)
                return;

              if ((!fact.IsFilterTurnedOn && !visitFilteredEdge) || (fact.getFilterState(endNodeRef.Id) == Filter.FilterState.NotFiltered) || (!originalFilterState && visitFilteredEdge)) {
                  endNodeRef.accept(this);
              }
              foreach (var visitor in visitorList) {
                visitor.visitEndDefaultExpressionSyntax_Type(node.Id, endNodeRef.Id);
              }

              clearStoppedVisitors();
              if(needPreorderStop)
                return;

            }
        }

        public override void visit(Columbus.Csharp.Asg.Nodes.Expression.DefaultExpressionSyntax node, bool callFirst = true){
          if (safeMode || visitCrossEdgeTree) {
            if (safeMode) {
              if (visitedNodes[(int)node.Id]) { // for safemode
                return;
              }
            }
            visitedNodes[(int)node.Id] = true;
          }

          foreach (var visitor in visitorList) {
            visitor.visit(node);
            incVisitorDepth(visitor);
          }

          clearStoppedVisitors();
          if(needPreorderStop)
            return;

          visitAllEdges(node, true);

          foreach (var visitor in visitorList) {
            decVisitorDepth(visitor);
            visitor.visitEnd(node);
          }

          clearStoppedVisitors();
        }

        /// <summary>
        /// It call the traversal for the edges
        /// </summary>
        /// <param name="node">[in] The node with own type</param>
        /// <param name="callVirtualBase">[in] This paramater is don't used just api copatibility used.</param>
        public void visitAllEdges(Columbus.Csharp.Asg.Nodes.Expression.ElementAccessExpressionSyntax node, bool callFirst = true){
            visitAllEdges((Columbus.Csharp.Asg.Nodes.Expression.ExpressionSyntax)(node),false);


            // edge: AccessorCall
            ListIterator<Columbus.Csharp.Asg.Nodes.Structure.AccessorDeclarationSyntax> iteratorForAccessorCall = node.AccessorCallListIteratorBegin;
            while (iteratorForAccessorCall.getValue() != null) {
               Columbus.Csharp.Asg.Nodes.Structure.AccessorDeclarationSyntax endNodeRef = (Columbus.Csharp.Asg.Nodes.Structure.AccessorDeclarationSyntax)iteratorForAccessorCall.getValue();
              foreach (var visitor in visitorList) {
                visitor.visitElementAccessExpressionSyntax_AccessorCall(node.Id, endNodeRef.Id);
              }

              clearStoppedVisitors();
              if(needPreorderStop)
                return;

              if ((!fact.IsFilterTurnedOn && !visitFilteredEdge) || (fact.getFilterState(endNodeRef.Id) == Filter.FilterState.NotFiltered) || (!originalFilterState && visitFilteredEdge)) {
                  if (apRoot != null) {
                    if (visitCrossEdgeTree) {
                      unvisitedNodes[(int)endNodeRef.Id] = true;
                    }
                  }
                  if (traversaldCrossEdges[(int)Types.EdgeKind.edkElementAccessExpressionSyntax_AccessorCall]) {
                    endNodeRef.accept(this);
                  }
              }
              foreach (var visitor in visitorList) {
                visitor.visitEndElementAccessExpressionSyntax_AccessorCall(node.Id, endNodeRef.Id);
              }

              clearStoppedVisitors();
              if(needPreorderStop)
                return;

            iteratorForAccessorCall = iteratorForAccessorCall.getNext();
            }

            Columbus.Csharp.Asg.Nodes.Base.Base genNodePtr;
            // edge: ArgumentList
            genNodePtr = fact.getRef(node.getArgumentList()) ;
            if (genNodePtr != null) {
              Columbus.Csharp.Asg.Nodes.Structure.BracketedArgumentListSyntax endNodeRef = (Columbus.Csharp.Asg.Nodes.Structure.BracketedArgumentListSyntax)(genNodePtr);
              foreach (var visitor in visitorList) {
                visitor.visitElementAccessExpressionSyntax_ArgumentList(node.Id, endNodeRef.Id);
              }

              clearStoppedVisitors();
              if(needPreorderStop)
                return;

              if ((!fact.IsFilterTurnedOn && !visitFilteredEdge) || (fact.getFilterState(endNodeRef.Id) == Filter.FilterState.NotFiltered) || (!originalFilterState && visitFilteredEdge)) {
                  endNodeRef.accept(this);
              }
              foreach (var visitor in visitorList) {
                visitor.visitEndElementAccessExpressionSyntax_ArgumentList(node.Id, endNodeRef.Id);
              }

              clearStoppedVisitors();
              if(needPreorderStop)
                return;

            }

            // edge: Expression
            genNodePtr = fact.getRef(node.getExpression()) ;
            if (genNodePtr != null) {
              Columbus.Csharp.Asg.Nodes.Expression.ExpressionSyntax endNodeRef = (Columbus.Csharp.Asg.Nodes.Expression.ExpressionSyntax)(genNodePtr);
              foreach (var visitor in visitorList) {
                visitor.visitElementAccessExpressionSyntax_Expression(node.Id, endNodeRef.Id);
              }

              clearStoppedVisitors();
              if(needPreorderStop)
                return;

              if ((!fact.IsFilterTurnedOn && !visitFilteredEdge) || (fact.getFilterState(endNodeRef.Id) == Filter.FilterState.NotFiltered) || (!originalFilterState && visitFilteredEdge)) {
                  endNodeRef.accept(this);
              }
              foreach (var visitor in visitorList) {
                visitor.visitEndElementAccessExpressionSyntax_Expression(node.Id, endNodeRef.Id);
              }

              clearStoppedVisitors();
              if(needPreorderStop)
                return;

            }
        }

        public override void visit(Columbus.Csharp.Asg.Nodes.Expression.ElementAccessExpressionSyntax node, bool callFirst = true){
          if (safeMode || visitCrossEdgeTree) {
            if (safeMode) {
              if (visitedNodes[(int)node.Id]) { // for safemode
                return;
              }
            }
            visitedNodes[(int)node.Id] = true;
          }

          foreach (var visitor in visitorList) {
            visitor.visit(node);
            incVisitorDepth(visitor);
          }

          clearStoppedVisitors();
          if(needPreorderStop)
            return;

          visitAllEdges(node, true);

          foreach (var visitor in visitorList) {
            decVisitorDepth(visitor);
            visitor.visitEnd(node);
          }

          clearStoppedVisitors();
        }

        /// <summary>
        /// It call the traversal for the edges
        /// </summary>
        /// <param name="node">[in] The node with own type</param>
        /// <param name="callVirtualBase">[in] This paramater is don't used just api copatibility used.</param>
        public void visitAllEdges(Columbus.Csharp.Asg.Nodes.Expression.ElementBindingExpressionSyntax node, bool callFirst = true){
            visitAllEdges((Columbus.Csharp.Asg.Nodes.Expression.ExpressionSyntax)(node),false);


            Columbus.Csharp.Asg.Nodes.Base.Base genNodePtr;
            // edge: ArgumentList
            genNodePtr = fact.getRef(node.getArgumentList()) ;
            if (genNodePtr != null) {
              Columbus.Csharp.Asg.Nodes.Structure.BracketedArgumentListSyntax endNodeRef = (Columbus.Csharp.Asg.Nodes.Structure.BracketedArgumentListSyntax)(genNodePtr);
              foreach (var visitor in visitorList) {
                visitor.visitElementBindingExpressionSyntax_ArgumentList(node.Id, endNodeRef.Id);
              }

              clearStoppedVisitors();
              if(needPreorderStop)
                return;

              if ((!fact.IsFilterTurnedOn && !visitFilteredEdge) || (fact.getFilterState(endNodeRef.Id) == Filter.FilterState.NotFiltered) || (!originalFilterState && visitFilteredEdge)) {
                  endNodeRef.accept(this);
              }
              foreach (var visitor in visitorList) {
                visitor.visitEndElementBindingExpressionSyntax_ArgumentList(node.Id, endNodeRef.Id);
              }

              clearStoppedVisitors();
              if(needPreorderStop)
                return;

            }
        }

        public override void visit(Columbus.Csharp.Asg.Nodes.Expression.ElementBindingExpressionSyntax node, bool callFirst = true){
          if (safeMode || visitCrossEdgeTree) {
            if (safeMode) {
              if (visitedNodes[(int)node.Id]) { // for safemode
                return;
              }
            }
            visitedNodes[(int)node.Id] = true;
          }

          foreach (var visitor in visitorList) {
            visitor.visit(node);
            incVisitorDepth(visitor);
          }

          clearStoppedVisitors();
          if(needPreorderStop)
            return;

          visitAllEdges(node, true);

          foreach (var visitor in visitorList) {
            decVisitorDepth(visitor);
            visitor.visitEnd(node);
          }

          clearStoppedVisitors();
        }

        /// <summary>
        /// It call the traversal for the edges
        /// </summary>
        /// <param name="node">[in] The node with own type</param>
        /// <param name="callVirtualBase">[in] This paramater is don't used just api copatibility used.</param>
        public void visitAllEdges(Columbus.Csharp.Asg.Nodes.Expression.ExpressionSyntax node, bool callFirst = true){
            visitAllEdges((Columbus.Csharp.Asg.Nodes.Base.Positioned)(node),false);
        }

        /// <summary>
        /// It call the traversal for the edges
        /// </summary>
        /// <param name="node">[in] The node with own type</param>
        /// <param name="callVirtualBase">[in] This paramater is don't used just api copatibility used.</param>
        public void visitAllEdges(Columbus.Csharp.Asg.Nodes.Expression.GenericNameSyntax node, bool callFirst = true){
            visitAllEdges((Columbus.Csharp.Asg.Nodes.Expression.SimpleNameSyntax)(node),false);


            Columbus.Csharp.Asg.Nodes.Base.Base genNodePtr;
            // edge: TypeArgumentList
            genNodePtr = fact.getRef(node.getTypeArgumentList()) ;
            if (genNodePtr != null) {
              Columbus.Csharp.Asg.Nodes.Structure.TypeArgumentListSyntax endNodeRef = (Columbus.Csharp.Asg.Nodes.Structure.TypeArgumentListSyntax)(genNodePtr);
              foreach (var visitor in visitorList) {
                visitor.visitGenericNameSyntax_TypeArgumentList(node.Id, endNodeRef.Id);
              }

              clearStoppedVisitors();
              if(needPreorderStop)
                return;

              if ((!fact.IsFilterTurnedOn && !visitFilteredEdge) || (fact.getFilterState(endNodeRef.Id) == Filter.FilterState.NotFiltered) || (!originalFilterState && visitFilteredEdge)) {
                  endNodeRef.accept(this);
              }
              foreach (var visitor in visitorList) {
                visitor.visitEndGenericNameSyntax_TypeArgumentList(node.Id, endNodeRef.Id);
              }

              clearStoppedVisitors();
              if(needPreorderStop)
                return;

            }
        }

        public override void visit(Columbus.Csharp.Asg.Nodes.Expression.GenericNameSyntax node, bool callFirst = true){
          if (safeMode || visitCrossEdgeTree) {
            if (safeMode) {
              if (visitedNodes[(int)node.Id]) { // for safemode
                return;
              }
            }
            visitedNodes[(int)node.Id] = true;
          }

          foreach (var visitor in visitorList) {
            visitor.visit(node);
            incVisitorDepth(visitor);
          }

          clearStoppedVisitors();
          if(needPreorderStop)
            return;

          visitAllEdges(node, true);

          foreach (var visitor in visitorList) {
            decVisitorDepth(visitor);
            visitor.visitEnd(node);
          }

          clearStoppedVisitors();
        }

        /// <summary>
        /// It call the traversal for the edges
        /// </summary>
        /// <param name="node">[in] The node with own type</param>
        /// <param name="callVirtualBase">[in] This paramater is don't used just api copatibility used.</param>
        public void visitAllEdges(Columbus.Csharp.Asg.Nodes.Expression.IdentifierNameSyntax node, bool callFirst = true){
            visitAllEdges((Columbus.Csharp.Asg.Nodes.Expression.SimpleNameSyntax)(node),false);


            // edge: AccessorCall
            ListIterator<Columbus.Csharp.Asg.Nodes.Structure.AccessorDeclarationSyntax> iteratorForAccessorCall = node.AccessorCallListIteratorBegin;
            while (iteratorForAccessorCall.getValue() != null) {
               Columbus.Csharp.Asg.Nodes.Structure.AccessorDeclarationSyntax endNodeRef = (Columbus.Csharp.Asg.Nodes.Structure.AccessorDeclarationSyntax)iteratorForAccessorCall.getValue();
              foreach (var visitor in visitorList) {
                visitor.visitIdentifierNameSyntax_AccessorCall(node.Id, endNodeRef.Id);
              }

              clearStoppedVisitors();
              if(needPreorderStop)
                return;

              if ((!fact.IsFilterTurnedOn && !visitFilteredEdge) || (fact.getFilterState(endNodeRef.Id) == Filter.FilterState.NotFiltered) || (!originalFilterState && visitFilteredEdge)) {
                  if (apRoot != null) {
                    if (visitCrossEdgeTree) {
                      unvisitedNodes[(int)endNodeRef.Id] = true;
                    }
                  }
                  if (traversaldCrossEdges[(int)Types.EdgeKind.edkIdentifierNameSyntax_AccessorCall]) {
                    endNodeRef.accept(this);
                  }
              }
              foreach (var visitor in visitorList) {
                visitor.visitEndIdentifierNameSyntax_AccessorCall(node.Id, endNodeRef.Id);
              }

              clearStoppedVisitors();
              if(needPreorderStop)
                return;

            iteratorForAccessorCall = iteratorForAccessorCall.getNext();
            }

            Columbus.Csharp.Asg.Nodes.Base.Base genNodePtr;
            // edge: Declaration
            genNodePtr = fact.getRef(node.getDeclaration()) ;
            if (genNodePtr != null) {
              Columbus.Csharp.Asg.Nodes.Base.Positioned endNodeRef = (Columbus.Csharp.Asg.Nodes.Base.Positioned)(genNodePtr);
              foreach (var visitor in visitorList) {
                visitor.visitIdentifierNameSyntax_Declaration(node.Id, endNodeRef.Id);
              }

              clearStoppedVisitors();
              if(needPreorderStop)
                return;

              if ((!fact.IsFilterTurnedOn && !visitFilteredEdge) || (fact.getFilterState(endNodeRef.Id) == Filter.FilterState.NotFiltered) || (!originalFilterState && visitFilteredEdge)) {
                  if (apRoot != null) {
                    if (visitCrossEdgeTree) {
                      unvisitedNodes[(int)endNodeRef.Id] = true;
                    }
                  }
                  if (traversaldCrossEdges[(int)Types.EdgeKind.edkIdentifierNameSyntax_Declaration]) {
                    endNodeRef.accept(this);
                  }
              }
              foreach (var visitor in visitorList) {
                visitor.visitEndIdentifierNameSyntax_Declaration(node.Id, endNodeRef.Id);
              }

              clearStoppedVisitors();
              if(needPreorderStop)
                return;

            }
        }

        public override void visit(Columbus.Csharp.Asg.Nodes.Expression.IdentifierNameSyntax node, bool callFirst = true){
          if (safeMode || visitCrossEdgeTree) {
            if (safeMode) {
              if (visitedNodes[(int)node.Id]) { // for safemode
                return;
              }
            }
            visitedNodes[(int)node.Id] = true;
          }

          foreach (var visitor in visitorList) {
            visitor.visit(node);
            incVisitorDepth(visitor);
          }

          clearStoppedVisitors();
          if(needPreorderStop)
            return;

          visitAllEdges(node, true);

          foreach (var visitor in visitorList) {
            decVisitorDepth(visitor);
            visitor.visitEnd(node);
          }

          clearStoppedVisitors();
        }

        /// <summary>
        /// It call the traversal for the edges
        /// </summary>
        /// <param name="node">[in] The node with own type</param>
        /// <param name="callVirtualBase">[in] This paramater is don't used just api copatibility used.</param>
        public void visitAllEdges(Columbus.Csharp.Asg.Nodes.Expression.ImplicitArrayCreationExpressionSyntax node, bool callFirst = true){
            visitAllEdges((Columbus.Csharp.Asg.Nodes.Expression.ExpressionSyntax)(node),false);


            Columbus.Csharp.Asg.Nodes.Base.Base genNodePtr;
            // edge: Initializer
            genNodePtr = fact.getRef(node.getInitializer()) ;
            if (genNodePtr != null) {
              Columbus.Csharp.Asg.Nodes.Expression.InitializerExpressionSyntax endNodeRef = (Columbus.Csharp.Asg.Nodes.Expression.InitializerExpressionSyntax)(genNodePtr);
              foreach (var visitor in visitorList) {
                visitor.visitImplicitArrayCreationExpressionSyntax_Initializer(node.Id, endNodeRef.Id);
              }

              clearStoppedVisitors();
              if(needPreorderStop)
                return;

              if ((!fact.IsFilterTurnedOn && !visitFilteredEdge) || (fact.getFilterState(endNodeRef.Id) == Filter.FilterState.NotFiltered) || (!originalFilterState && visitFilteredEdge)) {
                  endNodeRef.accept(this);
              }
              foreach (var visitor in visitorList) {
                visitor.visitEndImplicitArrayCreationExpressionSyntax_Initializer(node.Id, endNodeRef.Id);
              }

              clearStoppedVisitors();
              if(needPreorderStop)
                return;

            }
        }

        public override void visit(Columbus.Csharp.Asg.Nodes.Expression.ImplicitArrayCreationExpressionSyntax node, bool callFirst = true){
          if (safeMode || visitCrossEdgeTree) {
            if (safeMode) {
              if (visitedNodes[(int)node.Id]) { // for safemode
                return;
              }
            }
            visitedNodes[(int)node.Id] = true;
          }

          foreach (var visitor in visitorList) {
            visitor.visit(node);
            incVisitorDepth(visitor);
          }

          clearStoppedVisitors();
          if(needPreorderStop)
            return;

          visitAllEdges(node, true);

          foreach (var visitor in visitorList) {
            decVisitorDepth(visitor);
            visitor.visitEnd(node);
          }

          clearStoppedVisitors();
        }

        /// <summary>
        /// It call the traversal for the edges
        /// </summary>
        /// <param name="node">[in] The node with own type</param>
        /// <param name="callVirtualBase">[in] This paramater is don't used just api copatibility used.</param>
        public void visitAllEdges(Columbus.Csharp.Asg.Nodes.Expression.ImplicitElementAccessSyntax node, bool callFirst = true){
            visitAllEdges((Columbus.Csharp.Asg.Nodes.Expression.ExpressionSyntax)(node),false);


            Columbus.Csharp.Asg.Nodes.Base.Base genNodePtr;
            // edge: ArgumentList
            genNodePtr = fact.getRef(node.getArgumentList()) ;
            if (genNodePtr != null) {
              Columbus.Csharp.Asg.Nodes.Structure.BracketedArgumentListSyntax endNodeRef = (Columbus.Csharp.Asg.Nodes.Structure.BracketedArgumentListSyntax)(genNodePtr);
              foreach (var visitor in visitorList) {
                visitor.visitImplicitElementAccessSyntax_ArgumentList(node.Id, endNodeRef.Id);
              }

              clearStoppedVisitors();
              if(needPreorderStop)
                return;

              if ((!fact.IsFilterTurnedOn && !visitFilteredEdge) || (fact.getFilterState(endNodeRef.Id) == Filter.FilterState.NotFiltered) || (!originalFilterState && visitFilteredEdge)) {
                  endNodeRef.accept(this);
              }
              foreach (var visitor in visitorList) {
                visitor.visitEndImplicitElementAccessSyntax_ArgumentList(node.Id, endNodeRef.Id);
              }

              clearStoppedVisitors();
              if(needPreorderStop)
                return;

            }
        }

        public override void visit(Columbus.Csharp.Asg.Nodes.Expression.ImplicitElementAccessSyntax node, bool callFirst = true){
          if (safeMode || visitCrossEdgeTree) {
            if (safeMode) {
              if (visitedNodes[(int)node.Id]) { // for safemode
                return;
              }
            }
            visitedNodes[(int)node.Id] = true;
          }

          foreach (var visitor in visitorList) {
            visitor.visit(node);
            incVisitorDepth(visitor);
          }

          clearStoppedVisitors();
          if(needPreorderStop)
            return;

          visitAllEdges(node, true);

          foreach (var visitor in visitorList) {
            decVisitorDepth(visitor);
            visitor.visitEnd(node);
          }

          clearStoppedVisitors();
        }

        /// <summary>
        /// It call the traversal for the edges
        /// </summary>
        /// <param name="node">[in] The node with own type</param>
        /// <param name="callVirtualBase">[in] This paramater is don't used just api copatibility used.</param>
        public void visitAllEdges(Columbus.Csharp.Asg.Nodes.Expression.ImplicitStackAllocArrayCreationExpressionSyntax node, bool callFirst = true){
            visitAllEdges((Columbus.Csharp.Asg.Nodes.Expression.ExpressionSyntax)(node),false);


            Columbus.Csharp.Asg.Nodes.Base.Base genNodePtr;
            // edge: Initializer
            genNodePtr = fact.getRef(node.getInitializer()) ;
            if (genNodePtr != null) {
              Columbus.Csharp.Asg.Nodes.Expression.InitializerExpressionSyntax endNodeRef = (Columbus.Csharp.Asg.Nodes.Expression.InitializerExpressionSyntax)(genNodePtr);
              foreach (var visitor in visitorList) {
                visitor.visitImplicitStackAllocArrayCreationExpressionSyntax_Initializer(node.Id, endNodeRef.Id);
              }

              clearStoppedVisitors();
              if(needPreorderStop)
                return;

              if ((!fact.IsFilterTurnedOn && !visitFilteredEdge) || (fact.getFilterState(endNodeRef.Id) == Filter.FilterState.NotFiltered) || (!originalFilterState && visitFilteredEdge)) {
                  endNodeRef.accept(this);
              }
              foreach (var visitor in visitorList) {
                visitor.visitEndImplicitStackAllocArrayCreationExpressionSyntax_Initializer(node.Id, endNodeRef.Id);
              }

              clearStoppedVisitors();
              if(needPreorderStop)
                return;

            }
        }

        public override void visit(Columbus.Csharp.Asg.Nodes.Expression.ImplicitStackAllocArrayCreationExpressionSyntax node, bool callFirst = true){
          if (safeMode || visitCrossEdgeTree) {
            if (safeMode) {
              if (visitedNodes[(int)node.Id]) { // for safemode
                return;
              }
            }
            visitedNodes[(int)node.Id] = true;
          }

          foreach (var visitor in visitorList) {
            visitor.visit(node);
            incVisitorDepth(visitor);
          }

          clearStoppedVisitors();
          if(needPreorderStop)
            return;

          visitAllEdges(node, true);

          foreach (var visitor in visitorList) {
            decVisitorDepth(visitor);
            visitor.visitEnd(node);
          }

          clearStoppedVisitors();
        }

        /// <summary>
        /// It call the traversal for the edges
        /// </summary>
        /// <param name="node">[in] The node with own type</param>
        /// <param name="callVirtualBase">[in] This paramater is don't used just api copatibility used.</param>
        public void visitAllEdges(Columbus.Csharp.Asg.Nodes.Expression.InitializerExpressionSyntax node, bool callFirst = true){
            visitAllEdges((Columbus.Csharp.Asg.Nodes.Expression.ExpressionSyntax)(node),false);


            // edge: Expressions
            ListIterator<Columbus.Csharp.Asg.Nodes.Expression.ExpressionSyntax> iteratorForExpressions = node.ExpressionsListIteratorBegin;
            while (iteratorForExpressions.getValue() != null) {
               Columbus.Csharp.Asg.Nodes.Expression.ExpressionSyntax endNodeRef = (Columbus.Csharp.Asg.Nodes.Expression.ExpressionSyntax)iteratorForExpressions.getValue();
              foreach (var visitor in visitorList) {
                visitor.visitInitializerExpressionSyntax_Expressions(node.Id, endNodeRef.Id);
              }

              clearStoppedVisitors();
              if(needPreorderStop)
                return;

              if ((!fact.IsFilterTurnedOn && !visitFilteredEdge) || (fact.getFilterState(endNodeRef.Id) == Filter.FilterState.NotFiltered) || (!originalFilterState && visitFilteredEdge)) {
                  endNodeRef.accept(this);
              }
              foreach (var visitor in visitorList) {
                visitor.visitEndInitializerExpressionSyntax_Expressions(node.Id, endNodeRef.Id);
              }

              clearStoppedVisitors();
              if(needPreorderStop)
                return;

            iteratorForExpressions = iteratorForExpressions.getNext();
            }
        }

        public override void visit(Columbus.Csharp.Asg.Nodes.Expression.InitializerExpressionSyntax node, bool callFirst = true){
          if (safeMode || visitCrossEdgeTree) {
            if (safeMode) {
              if (visitedNodes[(int)node.Id]) { // for safemode
                return;
              }
            }
            visitedNodes[(int)node.Id] = true;
          }

          foreach (var visitor in visitorList) {
            visitor.visit(node);
            incVisitorDepth(visitor);
          }

          clearStoppedVisitors();
          if(needPreorderStop)
            return;

          visitAllEdges(node, true);

          foreach (var visitor in visitorList) {
            decVisitorDepth(visitor);
            visitor.visitEnd(node);
          }

          clearStoppedVisitors();
        }

        /// <summary>
        /// It call the traversal for the edges
        /// </summary>
        /// <param name="node">[in] The node with own type</param>
        /// <param name="callVirtualBase">[in] This paramater is don't used just api copatibility used.</param>
        public void visitAllEdges(Columbus.Csharp.Asg.Nodes.Expression.InstanceExpressionSyntax node, bool callFirst = true){
            visitAllEdges((Columbus.Csharp.Asg.Nodes.Expression.ExpressionSyntax)(node),false);
        }

        /// <summary>
        /// It call the traversal for the edges
        /// </summary>
        /// <param name="node">[in] The node with own type</param>
        /// <param name="callVirtualBase">[in] This paramater is don't used just api copatibility used.</param>
        public void visitAllEdges(Columbus.Csharp.Asg.Nodes.Expression.InterpolatedStringExpressionSyntax node, bool callFirst = true){
            visitAllEdges((Columbus.Csharp.Asg.Nodes.Expression.ExpressionSyntax)(node),false);


            // edge: Contents
            ListIterator<Columbus.Csharp.Asg.Nodes.Structure.InterpolatedStringContentSyntax> iteratorForContents = node.ContentsListIteratorBegin;
            while (iteratorForContents.getValue() != null) {
               Columbus.Csharp.Asg.Nodes.Structure.InterpolatedStringContentSyntax endNodeRef = (Columbus.Csharp.Asg.Nodes.Structure.InterpolatedStringContentSyntax)iteratorForContents.getValue();
              foreach (var visitor in visitorList) {
                visitor.visitInterpolatedStringExpressionSyntax_Contents(node.Id, endNodeRef.Id);
              }

              clearStoppedVisitors();
              if(needPreorderStop)
                return;

              if ((!fact.IsFilterTurnedOn && !visitFilteredEdge) || (fact.getFilterState(endNodeRef.Id) == Filter.FilterState.NotFiltered) || (!originalFilterState && visitFilteredEdge)) {
                  endNodeRef.accept(this);
              }
              foreach (var visitor in visitorList) {
                visitor.visitEndInterpolatedStringExpressionSyntax_Contents(node.Id, endNodeRef.Id);
              }

              clearStoppedVisitors();
              if(needPreorderStop)
                return;

            iteratorForContents = iteratorForContents.getNext();
            }
        }

        public override void visit(Columbus.Csharp.Asg.Nodes.Expression.InterpolatedStringExpressionSyntax node, bool callFirst = true){
          if (safeMode || visitCrossEdgeTree) {
            if (safeMode) {
              if (visitedNodes[(int)node.Id]) { // for safemode
                return;
              }
            }
            visitedNodes[(int)node.Id] = true;
          }

          foreach (var visitor in visitorList) {
            visitor.visit(node);
            incVisitorDepth(visitor);
          }

          clearStoppedVisitors();
          if(needPreorderStop)
            return;

          visitAllEdges(node, true);

          foreach (var visitor in visitorList) {
            decVisitorDepth(visitor);
            visitor.visitEnd(node);
          }

          clearStoppedVisitors();
        }

        /// <summary>
        /// It call the traversal for the edges
        /// </summary>
        /// <param name="node">[in] The node with own type</param>
        /// <param name="callVirtualBase">[in] This paramater is don't used just api copatibility used.</param>
        public void visitAllEdges(Columbus.Csharp.Asg.Nodes.Expression.InvocationExpressionSyntax node, bool callFirst = true){
            visitAllEdges((Columbus.Csharp.Asg.Nodes.Expression.ExpressionSyntax)(node),false);


            Columbus.Csharp.Asg.Nodes.Base.Base genNodePtr;
            // edge: ArgumentList
            genNodePtr = fact.getRef(node.getArgumentList()) ;
            if (genNodePtr != null) {
              Columbus.Csharp.Asg.Nodes.Structure.ArgumentListSyntax endNodeRef = (Columbus.Csharp.Asg.Nodes.Structure.ArgumentListSyntax)(genNodePtr);
              foreach (var visitor in visitorList) {
                visitor.visitInvocationExpressionSyntax_ArgumentList(node.Id, endNodeRef.Id);
              }

              clearStoppedVisitors();
              if(needPreorderStop)
                return;

              if ((!fact.IsFilterTurnedOn && !visitFilteredEdge) || (fact.getFilterState(endNodeRef.Id) == Filter.FilterState.NotFiltered) || (!originalFilterState && visitFilteredEdge)) {
                  endNodeRef.accept(this);
              }
              foreach (var visitor in visitorList) {
                visitor.visitEndInvocationExpressionSyntax_ArgumentList(node.Id, endNodeRef.Id);
              }

              clearStoppedVisitors();
              if(needPreorderStop)
                return;

            }

            // edge: Expression
            genNodePtr = fact.getRef(node.getExpression()) ;
            if (genNodePtr != null) {
              Columbus.Csharp.Asg.Nodes.Expression.ExpressionSyntax endNodeRef = (Columbus.Csharp.Asg.Nodes.Expression.ExpressionSyntax)(genNodePtr);
              foreach (var visitor in visitorList) {
                visitor.visitInvocationExpressionSyntax_Expression(node.Id, endNodeRef.Id);
              }

              clearStoppedVisitors();
              if(needPreorderStop)
                return;

              if ((!fact.IsFilterTurnedOn && !visitFilteredEdge) || (fact.getFilterState(endNodeRef.Id) == Filter.FilterState.NotFiltered) || (!originalFilterState && visitFilteredEdge)) {
                  endNodeRef.accept(this);
              }
              foreach (var visitor in visitorList) {
                visitor.visitEndInvocationExpressionSyntax_Expression(node.Id, endNodeRef.Id);
              }

              clearStoppedVisitors();
              if(needPreorderStop)
                return;

            }

            // edge: LocalFunctionCall
            genNodePtr = fact.getRef(node.getLocalFunctionCall()) ;
            if (genNodePtr != null) {
              Columbus.Csharp.Asg.Nodes.Statement.LocalFunctionStatementSyntax endNodeRef = (Columbus.Csharp.Asg.Nodes.Statement.LocalFunctionStatementSyntax)(genNodePtr);
              foreach (var visitor in visitorList) {
                visitor.visitInvocationExpressionSyntax_LocalFunctionCall(node.Id, endNodeRef.Id);
              }

              clearStoppedVisitors();
              if(needPreorderStop)
                return;

              if ((!fact.IsFilterTurnedOn && !visitFilteredEdge) || (fact.getFilterState(endNodeRef.Id) == Filter.FilterState.NotFiltered) || (!originalFilterState && visitFilteredEdge)) {
                  if (apRoot != null) {
                    if (visitCrossEdgeTree) {
                      unvisitedNodes[(int)endNodeRef.Id] = true;
                    }
                  }
                  if (traversaldCrossEdges[(int)Types.EdgeKind.edkInvocationExpressionSyntax_LocalFunctionCall]) {
                    endNodeRef.accept(this);
                  }
              }
              foreach (var visitor in visitorList) {
                visitor.visitEndInvocationExpressionSyntax_LocalFunctionCall(node.Id, endNodeRef.Id);
              }

              clearStoppedVisitors();
              if(needPreorderStop)
                return;

            }

            // edge: MethodCall
            genNodePtr = fact.getRef(node.getMethodCall()) ;
            if (genNodePtr != null) {
              Columbus.Csharp.Asg.Nodes.Structure.MethodDeclarationSyntax endNodeRef = (Columbus.Csharp.Asg.Nodes.Structure.MethodDeclarationSyntax)(genNodePtr);
              foreach (var visitor in visitorList) {
                visitor.visitInvocationExpressionSyntax_MethodCall(node.Id, endNodeRef.Id);
              }

              clearStoppedVisitors();
              if(needPreorderStop)
                return;

              if ((!fact.IsFilterTurnedOn && !visitFilteredEdge) || (fact.getFilterState(endNodeRef.Id) == Filter.FilterState.NotFiltered) || (!originalFilterState && visitFilteredEdge)) {
                  if (apRoot != null) {
                    if (visitCrossEdgeTree) {
                      unvisitedNodes[(int)endNodeRef.Id] = true;
                    }
                  }
                  if (traversaldCrossEdges[(int)Types.EdgeKind.edkInvocationExpressionSyntax_MethodCall]) {
                    endNodeRef.accept(this);
                  }
              }
              foreach (var visitor in visitorList) {
                visitor.visitEndInvocationExpressionSyntax_MethodCall(node.Id, endNodeRef.Id);
              }

              clearStoppedVisitors();
              if(needPreorderStop)
                return;

            }
        }

        public override void visit(Columbus.Csharp.Asg.Nodes.Expression.InvocationExpressionSyntax node, bool callFirst = true){
          if (safeMode || visitCrossEdgeTree) {
            if (safeMode) {
              if (visitedNodes[(int)node.Id]) { // for safemode
                return;
              }
            }
            visitedNodes[(int)node.Id] = true;
          }

          foreach (var visitor in visitorList) {
            visitor.visit(node);
            incVisitorDepth(visitor);
          }

          clearStoppedVisitors();
          if(needPreorderStop)
            return;

          visitAllEdges(node, true);

          foreach (var visitor in visitorList) {
            decVisitorDepth(visitor);
            visitor.visitEnd(node);
          }

          clearStoppedVisitors();
        }

        /// <summary>
        /// It call the traversal for the edges
        /// </summary>
        /// <param name="node">[in] The node with own type</param>
        /// <param name="callVirtualBase">[in] This paramater is don't used just api copatibility used.</param>
        public void visitAllEdges(Columbus.Csharp.Asg.Nodes.Expression.IsPatternExpressionSyntax node, bool callFirst = true){
            visitAllEdges((Columbus.Csharp.Asg.Nodes.Expression.ExpressionSyntax)(node),false);


            Columbus.Csharp.Asg.Nodes.Base.Base genNodePtr;
            // edge: Expression
            genNodePtr = fact.getRef(node.getExpression()) ;
            if (genNodePtr != null) {
              Columbus.Csharp.Asg.Nodes.Expression.ExpressionSyntax endNodeRef = (Columbus.Csharp.Asg.Nodes.Expression.ExpressionSyntax)(genNodePtr);
              foreach (var visitor in visitorList) {
                visitor.visitIsPatternExpressionSyntax_Expression(node.Id, endNodeRef.Id);
              }

              clearStoppedVisitors();
              if(needPreorderStop)
                return;

              if ((!fact.IsFilterTurnedOn && !visitFilteredEdge) || (fact.getFilterState(endNodeRef.Id) == Filter.FilterState.NotFiltered) || (!originalFilterState && visitFilteredEdge)) {
                  endNodeRef.accept(this);
              }
              foreach (var visitor in visitorList) {
                visitor.visitEndIsPatternExpressionSyntax_Expression(node.Id, endNodeRef.Id);
              }

              clearStoppedVisitors();
              if(needPreorderStop)
                return;

            }

            // edge: Pattern
            genNodePtr = fact.getRef(node.getPattern()) ;
            if (genNodePtr != null) {
              Columbus.Csharp.Asg.Nodes.Structure.PatternSyntax endNodeRef = (Columbus.Csharp.Asg.Nodes.Structure.PatternSyntax)(genNodePtr);
              foreach (var visitor in visitorList) {
                visitor.visitIsPatternExpressionSyntax_Pattern(node.Id, endNodeRef.Id);
              }

              clearStoppedVisitors();
              if(needPreorderStop)
                return;

              if ((!fact.IsFilterTurnedOn && !visitFilteredEdge) || (fact.getFilterState(endNodeRef.Id) == Filter.FilterState.NotFiltered) || (!originalFilterState && visitFilteredEdge)) {
                  endNodeRef.accept(this);
              }
              foreach (var visitor in visitorList) {
                visitor.visitEndIsPatternExpressionSyntax_Pattern(node.Id, endNodeRef.Id);
              }

              clearStoppedVisitors();
              if(needPreorderStop)
                return;

            }
        }

        public override void visit(Columbus.Csharp.Asg.Nodes.Expression.IsPatternExpressionSyntax node, bool callFirst = true){
          if (safeMode || visitCrossEdgeTree) {
            if (safeMode) {
              if (visitedNodes[(int)node.Id]) { // for safemode
                return;
              }
            }
            visitedNodes[(int)node.Id] = true;
          }

          foreach (var visitor in visitorList) {
            visitor.visit(node);
            incVisitorDepth(visitor);
          }

          clearStoppedVisitors();
          if(needPreorderStop)
            return;

          visitAllEdges(node, true);

          foreach (var visitor in visitorList) {
            decVisitorDepth(visitor);
            visitor.visitEnd(node);
          }

          clearStoppedVisitors();
        }

        /// <summary>
        /// It call the traversal for the edges
        /// </summary>
        /// <param name="node">[in] The node with own type</param>
        /// <param name="callVirtualBase">[in] This paramater is don't used just api copatibility used.</param>
        public void visitAllEdges(Columbus.Csharp.Asg.Nodes.Expression.LambdaExpressionSyntax node, bool callFirst = true){
            visitAllEdges((Columbus.Csharp.Asg.Nodes.Expression.AnonymousFunctionExpressionSyntax)(node),false);
        }

        /// <summary>
        /// It call the traversal for the edges
        /// </summary>
        /// <param name="node">[in] The node with own type</param>
        /// <param name="callVirtualBase">[in] This paramater is don't used just api copatibility used.</param>
        public void visitAllEdges(Columbus.Csharp.Asg.Nodes.Expression.LiteralExpressionSyntax node, bool callFirst = true){
            visitAllEdges((Columbus.Csharp.Asg.Nodes.Expression.ExpressionSyntax)(node),false);
        }

        public override void visit(Columbus.Csharp.Asg.Nodes.Expression.LiteralExpressionSyntax node, bool callFirst = true){
          if (safeMode || visitCrossEdgeTree) {
            if (safeMode) {
              if (visitedNodes[(int)node.Id]) { // for safemode
                return;
              }
            }
            visitedNodes[(int)node.Id] = true;
          }

          foreach (var visitor in visitorList) {
            visitor.visit(node);
            incVisitorDepth(visitor);
          }

          clearStoppedVisitors();
          if(needPreorderStop)
            return;

          visitAllEdges(node, true);

          foreach (var visitor in visitorList) {
            decVisitorDepth(visitor);
            visitor.visitEnd(node);
          }

          clearStoppedVisitors();
        }

        /// <summary>
        /// It call the traversal for the edges
        /// </summary>
        /// <param name="node">[in] The node with own type</param>
        /// <param name="callVirtualBase">[in] This paramater is don't used just api copatibility used.</param>
        public void visitAllEdges(Columbus.Csharp.Asg.Nodes.Expression.MakeRefExpressionSyntax node, bool callFirst = true){
            visitAllEdges((Columbus.Csharp.Asg.Nodes.Expression.ExpressionSyntax)(node),false);


            Columbus.Csharp.Asg.Nodes.Base.Base genNodePtr;
            // edge: Expression
            genNodePtr = fact.getRef(node.getExpression()) ;
            if (genNodePtr != null) {
              Columbus.Csharp.Asg.Nodes.Expression.ExpressionSyntax endNodeRef = (Columbus.Csharp.Asg.Nodes.Expression.ExpressionSyntax)(genNodePtr);
              foreach (var visitor in visitorList) {
                visitor.visitMakeRefExpressionSyntax_Expression(node.Id, endNodeRef.Id);
              }

              clearStoppedVisitors();
              if(needPreorderStop)
                return;

              if ((!fact.IsFilterTurnedOn && !visitFilteredEdge) || (fact.getFilterState(endNodeRef.Id) == Filter.FilterState.NotFiltered) || (!originalFilterState && visitFilteredEdge)) {
                  endNodeRef.accept(this);
              }
              foreach (var visitor in visitorList) {
                visitor.visitEndMakeRefExpressionSyntax_Expression(node.Id, endNodeRef.Id);
              }

              clearStoppedVisitors();
              if(needPreorderStop)
                return;

            }
        }

        public override void visit(Columbus.Csharp.Asg.Nodes.Expression.MakeRefExpressionSyntax node, bool callFirst = true){
          if (safeMode || visitCrossEdgeTree) {
            if (safeMode) {
              if (visitedNodes[(int)node.Id]) { // for safemode
                return;
              }
            }
            visitedNodes[(int)node.Id] = true;
          }

          foreach (var visitor in visitorList) {
            visitor.visit(node);
            incVisitorDepth(visitor);
          }

          clearStoppedVisitors();
          if(needPreorderStop)
            return;

          visitAllEdges(node, true);

          foreach (var visitor in visitorList) {
            decVisitorDepth(visitor);
            visitor.visitEnd(node);
          }

          clearStoppedVisitors();
        }

        /// <summary>
        /// It call the traversal for the edges
        /// </summary>
        /// <param name="node">[in] The node with own type</param>
        /// <param name="callVirtualBase">[in] This paramater is don't used just api copatibility used.</param>
        public void visitAllEdges(Columbus.Csharp.Asg.Nodes.Expression.MemberAccessExpressionSyntax node, bool callFirst = true){
            visitAllEdges((Columbus.Csharp.Asg.Nodes.Expression.ExpressionSyntax)(node),false);


            Columbus.Csharp.Asg.Nodes.Base.Base genNodePtr;
            // edge: Expression
            genNodePtr = fact.getRef(node.getExpression()) ;
            if (genNodePtr != null) {
              Columbus.Csharp.Asg.Nodes.Expression.ExpressionSyntax endNodeRef = (Columbus.Csharp.Asg.Nodes.Expression.ExpressionSyntax)(genNodePtr);
              foreach (var visitor in visitorList) {
                visitor.visitMemberAccessExpressionSyntax_Expression(node.Id, endNodeRef.Id);
              }

              clearStoppedVisitors();
              if(needPreorderStop)
                return;

              if ((!fact.IsFilterTurnedOn && !visitFilteredEdge) || (fact.getFilterState(endNodeRef.Id) == Filter.FilterState.NotFiltered) || (!originalFilterState && visitFilteredEdge)) {
                  endNodeRef.accept(this);
              }
              foreach (var visitor in visitorList) {
                visitor.visitEndMemberAccessExpressionSyntax_Expression(node.Id, endNodeRef.Id);
              }

              clearStoppedVisitors();
              if(needPreorderStop)
                return;

            }

            // edge: Name
            genNodePtr = fact.getRef(node.getName()) ;
            if (genNodePtr != null) {
              Columbus.Csharp.Asg.Nodes.Expression.SimpleNameSyntax endNodeRef = (Columbus.Csharp.Asg.Nodes.Expression.SimpleNameSyntax)(genNodePtr);
              foreach (var visitor in visitorList) {
                visitor.visitMemberAccessExpressionSyntax_Name(node.Id, endNodeRef.Id);
              }

              clearStoppedVisitors();
              if(needPreorderStop)
                return;

              if ((!fact.IsFilterTurnedOn && !visitFilteredEdge) || (fact.getFilterState(endNodeRef.Id) == Filter.FilterState.NotFiltered) || (!originalFilterState && visitFilteredEdge)) {
                  endNodeRef.accept(this);
              }
              foreach (var visitor in visitorList) {
                visitor.visitEndMemberAccessExpressionSyntax_Name(node.Id, endNodeRef.Id);
              }

              clearStoppedVisitors();
              if(needPreorderStop)
                return;

            }
        }

        public override void visit(Columbus.Csharp.Asg.Nodes.Expression.MemberAccessExpressionSyntax node, bool callFirst = true){
          if (safeMode || visitCrossEdgeTree) {
            if (safeMode) {
              if (visitedNodes[(int)node.Id]) { // for safemode
                return;
              }
            }
            visitedNodes[(int)node.Id] = true;
          }

          foreach (var visitor in visitorList) {
            visitor.visit(node);
            incVisitorDepth(visitor);
          }

          clearStoppedVisitors();
          if(needPreorderStop)
            return;

          visitAllEdges(node, true);

          foreach (var visitor in visitorList) {
            decVisitorDepth(visitor);
            visitor.visitEnd(node);
          }

          clearStoppedVisitors();
        }

        /// <summary>
        /// It call the traversal for the edges
        /// </summary>
        /// <param name="node">[in] The node with own type</param>
        /// <param name="callVirtualBase">[in] This paramater is don't used just api copatibility used.</param>
        public void visitAllEdges(Columbus.Csharp.Asg.Nodes.Expression.MemberBindingExpressionSyntax node, bool callFirst = true){
            visitAllEdges((Columbus.Csharp.Asg.Nodes.Expression.ExpressionSyntax)(node),false);


            Columbus.Csharp.Asg.Nodes.Base.Base genNodePtr;
            // edge: Name
            genNodePtr = fact.getRef(node.getName()) ;
            if (genNodePtr != null) {
              Columbus.Csharp.Asg.Nodes.Expression.SimpleNameSyntax endNodeRef = (Columbus.Csharp.Asg.Nodes.Expression.SimpleNameSyntax)(genNodePtr);
              foreach (var visitor in visitorList) {
                visitor.visitMemberBindingExpressionSyntax_Name(node.Id, endNodeRef.Id);
              }

              clearStoppedVisitors();
              if(needPreorderStop)
                return;

              if ((!fact.IsFilterTurnedOn && !visitFilteredEdge) || (fact.getFilterState(endNodeRef.Id) == Filter.FilterState.NotFiltered) || (!originalFilterState && visitFilteredEdge)) {
                  endNodeRef.accept(this);
              }
              foreach (var visitor in visitorList) {
                visitor.visitEndMemberBindingExpressionSyntax_Name(node.Id, endNodeRef.Id);
              }

              clearStoppedVisitors();
              if(needPreorderStop)
                return;

            }
        }

        public override void visit(Columbus.Csharp.Asg.Nodes.Expression.MemberBindingExpressionSyntax node, bool callFirst = true){
          if (safeMode || visitCrossEdgeTree) {
            if (safeMode) {
              if (visitedNodes[(int)node.Id]) { // for safemode
                return;
              }
            }
            visitedNodes[(int)node.Id] = true;
          }

          foreach (var visitor in visitorList) {
            visitor.visit(node);
            incVisitorDepth(visitor);
          }

          clearStoppedVisitors();
          if(needPreorderStop)
            return;

          visitAllEdges(node, true);

          foreach (var visitor in visitorList) {
            decVisitorDepth(visitor);
            visitor.visitEnd(node);
          }

          clearStoppedVisitors();
        }

        /// <summary>
        /// It call the traversal for the edges
        /// </summary>
        /// <param name="node">[in] The node with own type</param>
        /// <param name="callVirtualBase">[in] This paramater is don't used just api copatibility used.</param>
        public void visitAllEdges(Columbus.Csharp.Asg.Nodes.Expression.NameSyntax node, bool callFirst = true){
            visitAllEdges((Columbus.Csharp.Asg.Nodes.Expression.TypeSyntax)(node),false);
        }

        /// <summary>
        /// It call the traversal for the edges
        /// </summary>
        /// <param name="node">[in] The node with own type</param>
        /// <param name="callVirtualBase">[in] This paramater is don't used just api copatibility used.</param>
        public void visitAllEdges(Columbus.Csharp.Asg.Nodes.Expression.NullableTypeSyntax node, bool callFirst = true){
            visitAllEdges((Columbus.Csharp.Asg.Nodes.Expression.TypeSyntax)(node),false);


            Columbus.Csharp.Asg.Nodes.Base.Base genNodePtr;
            // edge: ElementType
            genNodePtr = fact.getRef(node.getElementType()) ;
            if (genNodePtr != null) {
              Columbus.Csharp.Asg.Nodes.Expression.TypeSyntax endNodeRef = (Columbus.Csharp.Asg.Nodes.Expression.TypeSyntax)(genNodePtr);
              foreach (var visitor in visitorList) {
                visitor.visitNullableTypeSyntax_ElementType(node.Id, endNodeRef.Id);
              }

              clearStoppedVisitors();
              if(needPreorderStop)
                return;

              if ((!fact.IsFilterTurnedOn && !visitFilteredEdge) || (fact.getFilterState(endNodeRef.Id) == Filter.FilterState.NotFiltered) || (!originalFilterState && visitFilteredEdge)) {
                  endNodeRef.accept(this);
              }
              foreach (var visitor in visitorList) {
                visitor.visitEndNullableTypeSyntax_ElementType(node.Id, endNodeRef.Id);
              }

              clearStoppedVisitors();
              if(needPreorderStop)
                return;

            }
        }

        public override void visit(Columbus.Csharp.Asg.Nodes.Expression.NullableTypeSyntax node, bool callFirst = true){
          if (safeMode || visitCrossEdgeTree) {
            if (safeMode) {
              if (visitedNodes[(int)node.Id]) { // for safemode
                return;
              }
            }
            visitedNodes[(int)node.Id] = true;
          }

          foreach (var visitor in visitorList) {
            visitor.visit(node);
            incVisitorDepth(visitor);
          }

          clearStoppedVisitors();
          if(needPreorderStop)
            return;

          visitAllEdges(node, true);

          foreach (var visitor in visitorList) {
            decVisitorDepth(visitor);
            visitor.visitEnd(node);
          }

          clearStoppedVisitors();
        }

        /// <summary>
        /// It call the traversal for the edges
        /// </summary>
        /// <param name="node">[in] The node with own type</param>
        /// <param name="callVirtualBase">[in] This paramater is don't used just api copatibility used.</param>
        public void visitAllEdges(Columbus.Csharp.Asg.Nodes.Expression.ObjectCreationExpressionSyntax node, bool callFirst = true){
            visitAllEdges((Columbus.Csharp.Asg.Nodes.Expression.ExpressionSyntax)(node),false);


            Columbus.Csharp.Asg.Nodes.Base.Base genNodePtr;
            // edge: ArgumentList
            genNodePtr = fact.getRef(node.getArgumentList()) ;
            if (genNodePtr != null) {
              Columbus.Csharp.Asg.Nodes.Structure.ArgumentListSyntax endNodeRef = (Columbus.Csharp.Asg.Nodes.Structure.ArgumentListSyntax)(genNodePtr);
              foreach (var visitor in visitorList) {
                visitor.visitObjectCreationExpressionSyntax_ArgumentList(node.Id, endNodeRef.Id);
              }

              clearStoppedVisitors();
              if(needPreorderStop)
                return;

              if ((!fact.IsFilterTurnedOn && !visitFilteredEdge) || (fact.getFilterState(endNodeRef.Id) == Filter.FilterState.NotFiltered) || (!originalFilterState && visitFilteredEdge)) {
                  endNodeRef.accept(this);
              }
              foreach (var visitor in visitorList) {
                visitor.visitEndObjectCreationExpressionSyntax_ArgumentList(node.Id, endNodeRef.Id);
              }

              clearStoppedVisitors();
              if(needPreorderStop)
                return;

            }

            // edge: ConstructorCall
            genNodePtr = fact.getRef(node.getConstructorCall()) ;
            if (genNodePtr != null) {
              Columbus.Csharp.Asg.Nodes.Structure.ConstructorDeclarationSyntax endNodeRef = (Columbus.Csharp.Asg.Nodes.Structure.ConstructorDeclarationSyntax)(genNodePtr);
              foreach (var visitor in visitorList) {
                visitor.visitObjectCreationExpressionSyntax_ConstructorCall(node.Id, endNodeRef.Id);
              }

              clearStoppedVisitors();
              if(needPreorderStop)
                return;

              if ((!fact.IsFilterTurnedOn && !visitFilteredEdge) || (fact.getFilterState(endNodeRef.Id) == Filter.FilterState.NotFiltered) || (!originalFilterState && visitFilteredEdge)) {
                  if (apRoot != null) {
                    if (visitCrossEdgeTree) {
                      unvisitedNodes[(int)endNodeRef.Id] = true;
                    }
                  }
                  if (traversaldCrossEdges[(int)Types.EdgeKind.edkObjectCreationExpressionSyntax_ConstructorCall]) {
                    endNodeRef.accept(this);
                  }
              }
              foreach (var visitor in visitorList) {
                visitor.visitEndObjectCreationExpressionSyntax_ConstructorCall(node.Id, endNodeRef.Id);
              }

              clearStoppedVisitors();
              if(needPreorderStop)
                return;

            }

            // edge: Initializer
            genNodePtr = fact.getRef(node.getInitializer()) ;
            if (genNodePtr != null) {
              Columbus.Csharp.Asg.Nodes.Expression.InitializerExpressionSyntax endNodeRef = (Columbus.Csharp.Asg.Nodes.Expression.InitializerExpressionSyntax)(genNodePtr);
              foreach (var visitor in visitorList) {
                visitor.visitObjectCreationExpressionSyntax_Initializer(node.Id, endNodeRef.Id);
              }

              clearStoppedVisitors();
              if(needPreorderStop)
                return;

              if ((!fact.IsFilterTurnedOn && !visitFilteredEdge) || (fact.getFilterState(endNodeRef.Id) == Filter.FilterState.NotFiltered) || (!originalFilterState && visitFilteredEdge)) {
                  endNodeRef.accept(this);
              }
              foreach (var visitor in visitorList) {
                visitor.visitEndObjectCreationExpressionSyntax_Initializer(node.Id, endNodeRef.Id);
              }

              clearStoppedVisitors();
              if(needPreorderStop)
                return;

            }

            // edge: Type
            genNodePtr = fact.getRef(node.getType()) ;
            if (genNodePtr != null) {
              Columbus.Csharp.Asg.Nodes.Expression.TypeSyntax endNodeRef = (Columbus.Csharp.Asg.Nodes.Expression.TypeSyntax)(genNodePtr);
              foreach (var visitor in visitorList) {
                visitor.visitObjectCreationExpressionSyntax_Type(node.Id, endNodeRef.Id);
              }

              clearStoppedVisitors();
              if(needPreorderStop)
                return;

              if ((!fact.IsFilterTurnedOn && !visitFilteredEdge) || (fact.getFilterState(endNodeRef.Id) == Filter.FilterState.NotFiltered) || (!originalFilterState && visitFilteredEdge)) {
                  endNodeRef.accept(this);
              }
              foreach (var visitor in visitorList) {
                visitor.visitEndObjectCreationExpressionSyntax_Type(node.Id, endNodeRef.Id);
              }

              clearStoppedVisitors();
              if(needPreorderStop)
                return;

            }
        }

        public override void visit(Columbus.Csharp.Asg.Nodes.Expression.ObjectCreationExpressionSyntax node, bool callFirst = true){
          if (safeMode || visitCrossEdgeTree) {
            if (safeMode) {
              if (visitedNodes[(int)node.Id]) { // for safemode
                return;
              }
            }
            visitedNodes[(int)node.Id] = true;
          }

          foreach (var visitor in visitorList) {
            visitor.visit(node);
            incVisitorDepth(visitor);
          }

          clearStoppedVisitors();
          if(needPreorderStop)
            return;

          visitAllEdges(node, true);

          foreach (var visitor in visitorList) {
            decVisitorDepth(visitor);
            visitor.visitEnd(node);
          }

          clearStoppedVisitors();
        }

        /// <summary>
        /// It call the traversal for the edges
        /// </summary>
        /// <param name="node">[in] The node with own type</param>
        /// <param name="callVirtualBase">[in] This paramater is don't used just api copatibility used.</param>
        public void visitAllEdges(Columbus.Csharp.Asg.Nodes.Expression.OmittedArraySizeExpressionSyntax node, bool callFirst = true){
            visitAllEdges((Columbus.Csharp.Asg.Nodes.Expression.ExpressionSyntax)(node),false);
        }

        public override void visit(Columbus.Csharp.Asg.Nodes.Expression.OmittedArraySizeExpressionSyntax node, bool callFirst = true){
          if (safeMode || visitCrossEdgeTree) {
            if (safeMode) {
              if (visitedNodes[(int)node.Id]) { // for safemode
                return;
              }
            }
            visitedNodes[(int)node.Id] = true;
          }

          foreach (var visitor in visitorList) {
            visitor.visit(node);
            incVisitorDepth(visitor);
          }

          clearStoppedVisitors();
          if(needPreorderStop)
            return;

          visitAllEdges(node, true);

          foreach (var visitor in visitorList) {
            decVisitorDepth(visitor);
            visitor.visitEnd(node);
          }

          clearStoppedVisitors();
        }

        /// <summary>
        /// It call the traversal for the edges
        /// </summary>
        /// <param name="node">[in] The node with own type</param>
        /// <param name="callVirtualBase">[in] This paramater is don't used just api copatibility used.</param>
        public void visitAllEdges(Columbus.Csharp.Asg.Nodes.Expression.OmittedTypeArgumentSyntax node, bool callFirst = true){
            visitAllEdges((Columbus.Csharp.Asg.Nodes.Expression.TypeSyntax)(node),false);
        }

        public override void visit(Columbus.Csharp.Asg.Nodes.Expression.OmittedTypeArgumentSyntax node, bool callFirst = true){
          if (safeMode || visitCrossEdgeTree) {
            if (safeMode) {
              if (visitedNodes[(int)node.Id]) { // for safemode
                return;
              }
            }
            visitedNodes[(int)node.Id] = true;
          }

          foreach (var visitor in visitorList) {
            visitor.visit(node);
            incVisitorDepth(visitor);
          }

          clearStoppedVisitors();
          if(needPreorderStop)
            return;

          visitAllEdges(node, true);

          foreach (var visitor in visitorList) {
            decVisitorDepth(visitor);
            visitor.visitEnd(node);
          }

          clearStoppedVisitors();
        }

        /// <summary>
        /// It call the traversal for the edges
        /// </summary>
        /// <param name="node">[in] The node with own type</param>
        /// <param name="callVirtualBase">[in] This paramater is don't used just api copatibility used.</param>
        public void visitAllEdges(Columbus.Csharp.Asg.Nodes.Expression.ParenthesizedExpressionSyntax node, bool callFirst = true){
            visitAllEdges((Columbus.Csharp.Asg.Nodes.Expression.ExpressionSyntax)(node),false);


            Columbus.Csharp.Asg.Nodes.Base.Base genNodePtr;
            // edge: Expression
            genNodePtr = fact.getRef(node.getExpression()) ;
            if (genNodePtr != null) {
              Columbus.Csharp.Asg.Nodes.Expression.ExpressionSyntax endNodeRef = (Columbus.Csharp.Asg.Nodes.Expression.ExpressionSyntax)(genNodePtr);
              foreach (var visitor in visitorList) {
                visitor.visitParenthesizedExpressionSyntax_Expression(node.Id, endNodeRef.Id);
              }

              clearStoppedVisitors();
              if(needPreorderStop)
                return;

              if ((!fact.IsFilterTurnedOn && !visitFilteredEdge) || (fact.getFilterState(endNodeRef.Id) == Filter.FilterState.NotFiltered) || (!originalFilterState && visitFilteredEdge)) {
                  endNodeRef.accept(this);
              }
              foreach (var visitor in visitorList) {
                visitor.visitEndParenthesizedExpressionSyntax_Expression(node.Id, endNodeRef.Id);
              }

              clearStoppedVisitors();
              if(needPreorderStop)
                return;

            }
        }

        public override void visit(Columbus.Csharp.Asg.Nodes.Expression.ParenthesizedExpressionSyntax node, bool callFirst = true){
          if (safeMode || visitCrossEdgeTree) {
            if (safeMode) {
              if (visitedNodes[(int)node.Id]) { // for safemode
                return;
              }
            }
            visitedNodes[(int)node.Id] = true;
          }

          foreach (var visitor in visitorList) {
            visitor.visit(node);
            incVisitorDepth(visitor);
          }

          clearStoppedVisitors();
          if(needPreorderStop)
            return;

          visitAllEdges(node, true);

          foreach (var visitor in visitorList) {
            decVisitorDepth(visitor);
            visitor.visitEnd(node);
          }

          clearStoppedVisitors();
        }

        /// <summary>
        /// It call the traversal for the edges
        /// </summary>
        /// <param name="node">[in] The node with own type</param>
        /// <param name="callVirtualBase">[in] This paramater is don't used just api copatibility used.</param>
        public void visitAllEdges(Columbus.Csharp.Asg.Nodes.Expression.ParenthesizedLambdaExpressionSyntax node, bool callFirst = true){
            visitAllEdges((Columbus.Csharp.Asg.Nodes.Expression.LambdaExpressionSyntax)(node),false);


            Columbus.Csharp.Asg.Nodes.Base.Base genNodePtr;
            // edge: ParameterList
            genNodePtr = fact.getRef(node.getParameterList()) ;
            if (genNodePtr != null) {
              Columbus.Csharp.Asg.Nodes.Structure.ParameterListSyntax endNodeRef = (Columbus.Csharp.Asg.Nodes.Structure.ParameterListSyntax)(genNodePtr);
              foreach (var visitor in visitorList) {
                visitor.visitParenthesizedLambdaExpressionSyntax_ParameterList(node.Id, endNodeRef.Id);
              }

              clearStoppedVisitors();
              if(needPreorderStop)
                return;

              if ((!fact.IsFilterTurnedOn && !visitFilteredEdge) || (fact.getFilterState(endNodeRef.Id) == Filter.FilterState.NotFiltered) || (!originalFilterState && visitFilteredEdge)) {
                  endNodeRef.accept(this);
              }
              foreach (var visitor in visitorList) {
                visitor.visitEndParenthesizedLambdaExpressionSyntax_ParameterList(node.Id, endNodeRef.Id);
              }

              clearStoppedVisitors();
              if(needPreorderStop)
                return;

            }
        }

        public override void visit(Columbus.Csharp.Asg.Nodes.Expression.ParenthesizedLambdaExpressionSyntax node, bool callFirst = true){
          if (safeMode || visitCrossEdgeTree) {
            if (safeMode) {
              if (visitedNodes[(int)node.Id]) { // for safemode
                return;
              }
            }
            visitedNodes[(int)node.Id] = true;
          }

          foreach (var visitor in visitorList) {
            visitor.visit(node);
            incVisitorDepth(visitor);
          }

          clearStoppedVisitors();
          if(needPreorderStop)
            return;

          visitAllEdges(node, true);

          foreach (var visitor in visitorList) {
            decVisitorDepth(visitor);
            visitor.visitEnd(node);
          }

          clearStoppedVisitors();
        }

        /// <summary>
        /// It call the traversal for the edges
        /// </summary>
        /// <param name="node">[in] The node with own type</param>
        /// <param name="callVirtualBase">[in] This paramater is don't used just api copatibility used.</param>
        public void visitAllEdges(Columbus.Csharp.Asg.Nodes.Expression.PointerTypeSyntax node, bool callFirst = true){
            visitAllEdges((Columbus.Csharp.Asg.Nodes.Expression.TypeSyntax)(node),false);


            Columbus.Csharp.Asg.Nodes.Base.Base genNodePtr;
            // edge: ElementType
            genNodePtr = fact.getRef(node.getElementType()) ;
            if (genNodePtr != null) {
              Columbus.Csharp.Asg.Nodes.Expression.TypeSyntax endNodeRef = (Columbus.Csharp.Asg.Nodes.Expression.TypeSyntax)(genNodePtr);
              foreach (var visitor in visitorList) {
                visitor.visitPointerTypeSyntax_ElementType(node.Id, endNodeRef.Id);
              }

              clearStoppedVisitors();
              if(needPreorderStop)
                return;

              if ((!fact.IsFilterTurnedOn && !visitFilteredEdge) || (fact.getFilterState(endNodeRef.Id) == Filter.FilterState.NotFiltered) || (!originalFilterState && visitFilteredEdge)) {
                  endNodeRef.accept(this);
              }
              foreach (var visitor in visitorList) {
                visitor.visitEndPointerTypeSyntax_ElementType(node.Id, endNodeRef.Id);
              }

              clearStoppedVisitors();
              if(needPreorderStop)
                return;

            }
        }

        public override void visit(Columbus.Csharp.Asg.Nodes.Expression.PointerTypeSyntax node, bool callFirst = true){
          if (safeMode || visitCrossEdgeTree) {
            if (safeMode) {
              if (visitedNodes[(int)node.Id]) { // for safemode
                return;
              }
            }
            visitedNodes[(int)node.Id] = true;
          }

          foreach (var visitor in visitorList) {
            visitor.visit(node);
            incVisitorDepth(visitor);
          }

          clearStoppedVisitors();
          if(needPreorderStop)
            return;

          visitAllEdges(node, true);

          foreach (var visitor in visitorList) {
            decVisitorDepth(visitor);
            visitor.visitEnd(node);
          }

          clearStoppedVisitors();
        }

        /// <summary>
        /// It call the traversal for the edges
        /// </summary>
        /// <param name="node">[in] The node with own type</param>
        /// <param name="callVirtualBase">[in] This paramater is don't used just api copatibility used.</param>
        public void visitAllEdges(Columbus.Csharp.Asg.Nodes.Expression.PostfixUnaryExpressionSyntax node, bool callFirst = true){
            visitAllEdges((Columbus.Csharp.Asg.Nodes.Expression.ExpressionSyntax)(node),false);


            Columbus.Csharp.Asg.Nodes.Base.Base genNodePtr;
            // edge: Operand
            genNodePtr = fact.getRef(node.getOperand()) ;
            if (genNodePtr != null) {
              Columbus.Csharp.Asg.Nodes.Expression.ExpressionSyntax endNodeRef = (Columbus.Csharp.Asg.Nodes.Expression.ExpressionSyntax)(genNodePtr);
              foreach (var visitor in visitorList) {
                visitor.visitPostfixUnaryExpressionSyntax_Operand(node.Id, endNodeRef.Id);
              }

              clearStoppedVisitors();
              if(needPreorderStop)
                return;

              if ((!fact.IsFilterTurnedOn && !visitFilteredEdge) || (fact.getFilterState(endNodeRef.Id) == Filter.FilterState.NotFiltered) || (!originalFilterState && visitFilteredEdge)) {
                  endNodeRef.accept(this);
              }
              foreach (var visitor in visitorList) {
                visitor.visitEndPostfixUnaryExpressionSyntax_Operand(node.Id, endNodeRef.Id);
              }

              clearStoppedVisitors();
              if(needPreorderStop)
                return;

            }

            // edge: OverloadedOperatorCall
            genNodePtr = fact.getRef(node.getOverloadedOperatorCall()) ;
            if (genNodePtr != null) {
              Columbus.Csharp.Asg.Nodes.Structure.OperatorDeclarationSyntax endNodeRef = (Columbus.Csharp.Asg.Nodes.Structure.OperatorDeclarationSyntax)(genNodePtr);
              foreach (var visitor in visitorList) {
                visitor.visitPostfixUnaryExpressionSyntax_OverloadedOperatorCall(node.Id, endNodeRef.Id);
              }

              clearStoppedVisitors();
              if(needPreorderStop)
                return;

              if ((!fact.IsFilterTurnedOn && !visitFilteredEdge) || (fact.getFilterState(endNodeRef.Id) == Filter.FilterState.NotFiltered) || (!originalFilterState && visitFilteredEdge)) {
                  if (apRoot != null) {
                    if (visitCrossEdgeTree) {
                      unvisitedNodes[(int)endNodeRef.Id] = true;
                    }
                  }
                  if (traversaldCrossEdges[(int)Types.EdgeKind.edkPostfixUnaryExpressionSyntax_OverloadedOperatorCall]) {
                    endNodeRef.accept(this);
                  }
              }
              foreach (var visitor in visitorList) {
                visitor.visitEndPostfixUnaryExpressionSyntax_OverloadedOperatorCall(node.Id, endNodeRef.Id);
              }

              clearStoppedVisitors();
              if(needPreorderStop)
                return;

            }
        }

        public override void visit(Columbus.Csharp.Asg.Nodes.Expression.PostfixUnaryExpressionSyntax node, bool callFirst = true){
          if (safeMode || visitCrossEdgeTree) {
            if (safeMode) {
              if (visitedNodes[(int)node.Id]) { // for safemode
                return;
              }
            }
            visitedNodes[(int)node.Id] = true;
          }

          foreach (var visitor in visitorList) {
            visitor.visit(node);
            incVisitorDepth(visitor);
          }

          clearStoppedVisitors();
          if(needPreorderStop)
            return;

          visitAllEdges(node, true);

          foreach (var visitor in visitorList) {
            decVisitorDepth(visitor);
            visitor.visitEnd(node);
          }

          clearStoppedVisitors();
        }

        /// <summary>
        /// It call the traversal for the edges
        /// </summary>
        /// <param name="node">[in] The node with own type</param>
        /// <param name="callVirtualBase">[in] This paramater is don't used just api copatibility used.</param>
        public void visitAllEdges(Columbus.Csharp.Asg.Nodes.Expression.PredefinedTypeSyntax node, bool callFirst = true){
            visitAllEdges((Columbus.Csharp.Asg.Nodes.Expression.TypeSyntax)(node),false);
        }

        public override void visit(Columbus.Csharp.Asg.Nodes.Expression.PredefinedTypeSyntax node, bool callFirst = true){
          if (safeMode || visitCrossEdgeTree) {
            if (safeMode) {
              if (visitedNodes[(int)node.Id]) { // for safemode
                return;
              }
            }
            visitedNodes[(int)node.Id] = true;
          }

          foreach (var visitor in visitorList) {
            visitor.visit(node);
            incVisitorDepth(visitor);
          }

          clearStoppedVisitors();
          if(needPreorderStop)
            return;

          visitAllEdges(node, true);

          foreach (var visitor in visitorList) {
            decVisitorDepth(visitor);
            visitor.visitEnd(node);
          }

          clearStoppedVisitors();
        }

        /// <summary>
        /// It call the traversal for the edges
        /// </summary>
        /// <param name="node">[in] The node with own type</param>
        /// <param name="callVirtualBase">[in] This paramater is don't used just api copatibility used.</param>
        public void visitAllEdges(Columbus.Csharp.Asg.Nodes.Expression.PrefixUnaryExpressionSyntax node, bool callFirst = true){
            visitAllEdges((Columbus.Csharp.Asg.Nodes.Expression.ExpressionSyntax)(node),false);


            Columbus.Csharp.Asg.Nodes.Base.Base genNodePtr;
            // edge: Operand
            genNodePtr = fact.getRef(node.getOperand()) ;
            if (genNodePtr != null) {
              Columbus.Csharp.Asg.Nodes.Expression.ExpressionSyntax endNodeRef = (Columbus.Csharp.Asg.Nodes.Expression.ExpressionSyntax)(genNodePtr);
              foreach (var visitor in visitorList) {
                visitor.visitPrefixUnaryExpressionSyntax_Operand(node.Id, endNodeRef.Id);
              }

              clearStoppedVisitors();
              if(needPreorderStop)
                return;

              if ((!fact.IsFilterTurnedOn && !visitFilteredEdge) || (fact.getFilterState(endNodeRef.Id) == Filter.FilterState.NotFiltered) || (!originalFilterState && visitFilteredEdge)) {
                  endNodeRef.accept(this);
              }
              foreach (var visitor in visitorList) {
                visitor.visitEndPrefixUnaryExpressionSyntax_Operand(node.Id, endNodeRef.Id);
              }

              clearStoppedVisitors();
              if(needPreorderStop)
                return;

            }

            // edge: OverloadedOperatorCall
            genNodePtr = fact.getRef(node.getOverloadedOperatorCall()) ;
            if (genNodePtr != null) {
              Columbus.Csharp.Asg.Nodes.Structure.OperatorDeclarationSyntax endNodeRef = (Columbus.Csharp.Asg.Nodes.Structure.OperatorDeclarationSyntax)(genNodePtr);
              foreach (var visitor in visitorList) {
                visitor.visitPrefixUnaryExpressionSyntax_OverloadedOperatorCall(node.Id, endNodeRef.Id);
              }

              clearStoppedVisitors();
              if(needPreorderStop)
                return;

              if ((!fact.IsFilterTurnedOn && !visitFilteredEdge) || (fact.getFilterState(endNodeRef.Id) == Filter.FilterState.NotFiltered) || (!originalFilterState && visitFilteredEdge)) {
                  if (apRoot != null) {
                    if (visitCrossEdgeTree) {
                      unvisitedNodes[(int)endNodeRef.Id] = true;
                    }
                  }
                  if (traversaldCrossEdges[(int)Types.EdgeKind.edkPrefixUnaryExpressionSyntax_OverloadedOperatorCall]) {
                    endNodeRef.accept(this);
                  }
              }
              foreach (var visitor in visitorList) {
                visitor.visitEndPrefixUnaryExpressionSyntax_OverloadedOperatorCall(node.Id, endNodeRef.Id);
              }

              clearStoppedVisitors();
              if(needPreorderStop)
                return;

            }
        }

        public override void visit(Columbus.Csharp.Asg.Nodes.Expression.PrefixUnaryExpressionSyntax node, bool callFirst = true){
          if (safeMode || visitCrossEdgeTree) {
            if (safeMode) {
              if (visitedNodes[(int)node.Id]) { // for safemode
                return;
              }
            }
            visitedNodes[(int)node.Id] = true;
          }

          foreach (var visitor in visitorList) {
            visitor.visit(node);
            incVisitorDepth(visitor);
          }

          clearStoppedVisitors();
          if(needPreorderStop)
            return;

          visitAllEdges(node, true);

          foreach (var visitor in visitorList) {
            decVisitorDepth(visitor);
            visitor.visitEnd(node);
          }

          clearStoppedVisitors();
        }

        /// <summary>
        /// It call the traversal for the edges
        /// </summary>
        /// <param name="node">[in] The node with own type</param>
        /// <param name="callVirtualBase">[in] This paramater is don't used just api copatibility used.</param>
        public void visitAllEdges(Columbus.Csharp.Asg.Nodes.Expression.QualifiedNameSyntax node, bool callFirst = true){
            visitAllEdges((Columbus.Csharp.Asg.Nodes.Expression.NameSyntax)(node),false);


            Columbus.Csharp.Asg.Nodes.Base.Base genNodePtr;
            // edge: Left
            genNodePtr = fact.getRef(node.getLeft()) ;
            if (genNodePtr != null) {
              Columbus.Csharp.Asg.Nodes.Expression.NameSyntax endNodeRef = (Columbus.Csharp.Asg.Nodes.Expression.NameSyntax)(genNodePtr);
              foreach (var visitor in visitorList) {
                visitor.visitQualifiedNameSyntax_Left(node.Id, endNodeRef.Id);
              }

              clearStoppedVisitors();
              if(needPreorderStop)
                return;

              if ((!fact.IsFilterTurnedOn && !visitFilteredEdge) || (fact.getFilterState(endNodeRef.Id) == Filter.FilterState.NotFiltered) || (!originalFilterState && visitFilteredEdge)) {
                  endNodeRef.accept(this);
              }
              foreach (var visitor in visitorList) {
                visitor.visitEndQualifiedNameSyntax_Left(node.Id, endNodeRef.Id);
              }

              clearStoppedVisitors();
              if(needPreorderStop)
                return;

            }

            // edge: Right
            genNodePtr = fact.getRef(node.getRight()) ;
            if (genNodePtr != null) {
              Columbus.Csharp.Asg.Nodes.Expression.SimpleNameSyntax endNodeRef = (Columbus.Csharp.Asg.Nodes.Expression.SimpleNameSyntax)(genNodePtr);
              foreach (var visitor in visitorList) {
                visitor.visitQualifiedNameSyntax_Right(node.Id, endNodeRef.Id);
              }

              clearStoppedVisitors();
              if(needPreorderStop)
                return;

              if ((!fact.IsFilterTurnedOn && !visitFilteredEdge) || (fact.getFilterState(endNodeRef.Id) == Filter.FilterState.NotFiltered) || (!originalFilterState && visitFilteredEdge)) {
                  endNodeRef.accept(this);
              }
              foreach (var visitor in visitorList) {
                visitor.visitEndQualifiedNameSyntax_Right(node.Id, endNodeRef.Id);
              }

              clearStoppedVisitors();
              if(needPreorderStop)
                return;

            }
        }

        public override void visit(Columbus.Csharp.Asg.Nodes.Expression.QualifiedNameSyntax node, bool callFirst = true){
          if (safeMode || visitCrossEdgeTree) {
            if (safeMode) {
              if (visitedNodes[(int)node.Id]) { // for safemode
                return;
              }
            }
            visitedNodes[(int)node.Id] = true;
          }

          foreach (var visitor in visitorList) {
            visitor.visit(node);
            incVisitorDepth(visitor);
          }

          clearStoppedVisitors();
          if(needPreorderStop)
            return;

          visitAllEdges(node, true);

          foreach (var visitor in visitorList) {
            decVisitorDepth(visitor);
            visitor.visitEnd(node);
          }

          clearStoppedVisitors();
        }

        /// <summary>
        /// It call the traversal for the edges
        /// </summary>
        /// <param name="node">[in] The node with own type</param>
        /// <param name="callVirtualBase">[in] This paramater is don't used just api copatibility used.</param>
        public void visitAllEdges(Columbus.Csharp.Asg.Nodes.Expression.QueryExpressionSyntax node, bool callFirst = true){
            visitAllEdges((Columbus.Csharp.Asg.Nodes.Expression.ExpressionSyntax)(node),false);


            Columbus.Csharp.Asg.Nodes.Base.Base genNodePtr;
            // edge: Body
            genNodePtr = fact.getRef(node.getBody()) ;
            if (genNodePtr != null) {
              Columbus.Csharp.Asg.Nodes.Structure.QueryBodySyntax endNodeRef = (Columbus.Csharp.Asg.Nodes.Structure.QueryBodySyntax)(genNodePtr);
              foreach (var visitor in visitorList) {
                visitor.visitQueryExpressionSyntax_Body(node.Id, endNodeRef.Id);
              }

              clearStoppedVisitors();
              if(needPreorderStop)
                return;

              if ((!fact.IsFilterTurnedOn && !visitFilteredEdge) || (fact.getFilterState(endNodeRef.Id) == Filter.FilterState.NotFiltered) || (!originalFilterState && visitFilteredEdge)) {
                  endNodeRef.accept(this);
              }
              foreach (var visitor in visitorList) {
                visitor.visitEndQueryExpressionSyntax_Body(node.Id, endNodeRef.Id);
              }

              clearStoppedVisitors();
              if(needPreorderStop)
                return;

            }

            // edge: FromClause
            genNodePtr = fact.getRef(node.getFromClause()) ;
            if (genNodePtr != null) {
              Columbus.Csharp.Asg.Nodes.Structure.FromClauseSyntax endNodeRef = (Columbus.Csharp.Asg.Nodes.Structure.FromClauseSyntax)(genNodePtr);
              foreach (var visitor in visitorList) {
                visitor.visitQueryExpressionSyntax_FromClause(node.Id, endNodeRef.Id);
              }

              clearStoppedVisitors();
              if(needPreorderStop)
                return;

              if ((!fact.IsFilterTurnedOn && !visitFilteredEdge) || (fact.getFilterState(endNodeRef.Id) == Filter.FilterState.NotFiltered) || (!originalFilterState && visitFilteredEdge)) {
                  endNodeRef.accept(this);
              }
              foreach (var visitor in visitorList) {
                visitor.visitEndQueryExpressionSyntax_FromClause(node.Id, endNodeRef.Id);
              }

              clearStoppedVisitors();
              if(needPreorderStop)
                return;

            }
        }

        public override void visit(Columbus.Csharp.Asg.Nodes.Expression.QueryExpressionSyntax node, bool callFirst = true){
          if (safeMode || visitCrossEdgeTree) {
            if (safeMode) {
              if (visitedNodes[(int)node.Id]) { // for safemode
                return;
              }
            }
            visitedNodes[(int)node.Id] = true;
          }

          foreach (var visitor in visitorList) {
            visitor.visit(node);
            incVisitorDepth(visitor);
          }

          clearStoppedVisitors();
          if(needPreorderStop)
            return;

          visitAllEdges(node, true);

          foreach (var visitor in visitorList) {
            decVisitorDepth(visitor);
            visitor.visitEnd(node);
          }

          clearStoppedVisitors();
        }

        /// <summary>
        /// It call the traversal for the edges
        /// </summary>
        /// <param name="node">[in] The node with own type</param>
        /// <param name="callVirtualBase">[in] This paramater is don't used just api copatibility used.</param>
        public void visitAllEdges(Columbus.Csharp.Asg.Nodes.Expression.RangeExpressionSyntax node, bool callFirst = true){
            visitAllEdges((Columbus.Csharp.Asg.Nodes.Expression.ExpressionSyntax)(node),false);


            Columbus.Csharp.Asg.Nodes.Base.Base genNodePtr;
            // edge: LeftOperand
            genNodePtr = fact.getRef(node.getLeftOperand()) ;
            if (genNodePtr != null) {
              Columbus.Csharp.Asg.Nodes.Expression.ExpressionSyntax endNodeRef = (Columbus.Csharp.Asg.Nodes.Expression.ExpressionSyntax)(genNodePtr);
              foreach (var visitor in visitorList) {
                visitor.visitRangeExpressionSyntax_LeftOperand(node.Id, endNodeRef.Id);
              }

              clearStoppedVisitors();
              if(needPreorderStop)
                return;

              if ((!fact.IsFilterTurnedOn && !visitFilteredEdge) || (fact.getFilterState(endNodeRef.Id) == Filter.FilterState.NotFiltered) || (!originalFilterState && visitFilteredEdge)) {
                  endNodeRef.accept(this);
              }
              foreach (var visitor in visitorList) {
                visitor.visitEndRangeExpressionSyntax_LeftOperand(node.Id, endNodeRef.Id);
              }

              clearStoppedVisitors();
              if(needPreorderStop)
                return;

            }

            // edge: RightOperand
            genNodePtr = fact.getRef(node.getRightOperand()) ;
            if (genNodePtr != null) {
              Columbus.Csharp.Asg.Nodes.Expression.ExpressionSyntax endNodeRef = (Columbus.Csharp.Asg.Nodes.Expression.ExpressionSyntax)(genNodePtr);
              foreach (var visitor in visitorList) {
                visitor.visitRangeExpressionSyntax_RightOperand(node.Id, endNodeRef.Id);
              }

              clearStoppedVisitors();
              if(needPreorderStop)
                return;

              if ((!fact.IsFilterTurnedOn && !visitFilteredEdge) || (fact.getFilterState(endNodeRef.Id) == Filter.FilterState.NotFiltered) || (!originalFilterState && visitFilteredEdge)) {
                  endNodeRef.accept(this);
              }
              foreach (var visitor in visitorList) {
                visitor.visitEndRangeExpressionSyntax_RightOperand(node.Id, endNodeRef.Id);
              }

              clearStoppedVisitors();
              if(needPreorderStop)
                return;

            }
        }

        public override void visit(Columbus.Csharp.Asg.Nodes.Expression.RangeExpressionSyntax node, bool callFirst = true){
          if (safeMode || visitCrossEdgeTree) {
            if (safeMode) {
              if (visitedNodes[(int)node.Id]) { // for safemode
                return;
              }
            }
            visitedNodes[(int)node.Id] = true;
          }

          foreach (var visitor in visitorList) {
            visitor.visit(node);
            incVisitorDepth(visitor);
          }

          clearStoppedVisitors();
          if(needPreorderStop)
            return;

          visitAllEdges(node, true);

          foreach (var visitor in visitorList) {
            decVisitorDepth(visitor);
            visitor.visitEnd(node);
          }

          clearStoppedVisitors();
        }

        /// <summary>
        /// It call the traversal for the edges
        /// </summary>
        /// <param name="node">[in] The node with own type</param>
        /// <param name="callVirtualBase">[in] This paramater is don't used just api copatibility used.</param>
        public void visitAllEdges(Columbus.Csharp.Asg.Nodes.Expression.RefExpressionSyntax node, bool callFirst = true){
            visitAllEdges((Columbus.Csharp.Asg.Nodes.Expression.ExpressionSyntax)(node),false);


            Columbus.Csharp.Asg.Nodes.Base.Base genNodePtr;
            // edge: Expression
            genNodePtr = fact.getRef(node.getExpression()) ;
            if (genNodePtr != null) {
              Columbus.Csharp.Asg.Nodes.Expression.ExpressionSyntax endNodeRef = (Columbus.Csharp.Asg.Nodes.Expression.ExpressionSyntax)(genNodePtr);
              foreach (var visitor in visitorList) {
                visitor.visitRefExpressionSyntax_Expression(node.Id, endNodeRef.Id);
              }

              clearStoppedVisitors();
              if(needPreorderStop)
                return;

              if ((!fact.IsFilterTurnedOn && !visitFilteredEdge) || (fact.getFilterState(endNodeRef.Id) == Filter.FilterState.NotFiltered) || (!originalFilterState && visitFilteredEdge)) {
                  endNodeRef.accept(this);
              }
              foreach (var visitor in visitorList) {
                visitor.visitEndRefExpressionSyntax_Expression(node.Id, endNodeRef.Id);
              }

              clearStoppedVisitors();
              if(needPreorderStop)
                return;

            }
        }

        public override void visit(Columbus.Csharp.Asg.Nodes.Expression.RefExpressionSyntax node, bool callFirst = true){
          if (safeMode || visitCrossEdgeTree) {
            if (safeMode) {
              if (visitedNodes[(int)node.Id]) { // for safemode
                return;
              }
            }
            visitedNodes[(int)node.Id] = true;
          }

          foreach (var visitor in visitorList) {
            visitor.visit(node);
            incVisitorDepth(visitor);
          }

          clearStoppedVisitors();
          if(needPreorderStop)
            return;

          visitAllEdges(node, true);

          foreach (var visitor in visitorList) {
            decVisitorDepth(visitor);
            visitor.visitEnd(node);
          }

          clearStoppedVisitors();
        }

        /// <summary>
        /// It call the traversal for the edges
        /// </summary>
        /// <param name="node">[in] The node with own type</param>
        /// <param name="callVirtualBase">[in] This paramater is don't used just api copatibility used.</param>
        public void visitAllEdges(Columbus.Csharp.Asg.Nodes.Expression.RefTypeExpressionSyntax node, bool callFirst = true){
            visitAllEdges((Columbus.Csharp.Asg.Nodes.Expression.ExpressionSyntax)(node),false);


            Columbus.Csharp.Asg.Nodes.Base.Base genNodePtr;
            // edge: Expression
            genNodePtr = fact.getRef(node.getExpression()) ;
            if (genNodePtr != null) {
              Columbus.Csharp.Asg.Nodes.Expression.ExpressionSyntax endNodeRef = (Columbus.Csharp.Asg.Nodes.Expression.ExpressionSyntax)(genNodePtr);
              foreach (var visitor in visitorList) {
                visitor.visitRefTypeExpressionSyntax_Expression(node.Id, endNodeRef.Id);
              }

              clearStoppedVisitors();
              if(needPreorderStop)
                return;

              if ((!fact.IsFilterTurnedOn && !visitFilteredEdge) || (fact.getFilterState(endNodeRef.Id) == Filter.FilterState.NotFiltered) || (!originalFilterState && visitFilteredEdge)) {
                  endNodeRef.accept(this);
              }
              foreach (var visitor in visitorList) {
                visitor.visitEndRefTypeExpressionSyntax_Expression(node.Id, endNodeRef.Id);
              }

              clearStoppedVisitors();
              if(needPreorderStop)
                return;

            }
        }

        public override void visit(Columbus.Csharp.Asg.Nodes.Expression.RefTypeExpressionSyntax node, bool callFirst = true){
          if (safeMode || visitCrossEdgeTree) {
            if (safeMode) {
              if (visitedNodes[(int)node.Id]) { // for safemode
                return;
              }
            }
            visitedNodes[(int)node.Id] = true;
          }

          foreach (var visitor in visitorList) {
            visitor.visit(node);
            incVisitorDepth(visitor);
          }

          clearStoppedVisitors();
          if(needPreorderStop)
            return;

          visitAllEdges(node, true);

          foreach (var visitor in visitorList) {
            decVisitorDepth(visitor);
            visitor.visitEnd(node);
          }

          clearStoppedVisitors();
        }

        /// <summary>
        /// It call the traversal for the edges
        /// </summary>
        /// <param name="node">[in] The node with own type</param>
        /// <param name="callVirtualBase">[in] This paramater is don't used just api copatibility used.</param>
        public void visitAllEdges(Columbus.Csharp.Asg.Nodes.Expression.RefTypeSyntax node, bool callFirst = true){
            visitAllEdges((Columbus.Csharp.Asg.Nodes.Expression.TypeSyntax)(node),false);


            Columbus.Csharp.Asg.Nodes.Base.Base genNodePtr;
            // edge: Type
            genNodePtr = fact.getRef(node.getType()) ;
            if (genNodePtr != null) {
              Columbus.Csharp.Asg.Nodes.Expression.TypeSyntax endNodeRef = (Columbus.Csharp.Asg.Nodes.Expression.TypeSyntax)(genNodePtr);
              foreach (var visitor in visitorList) {
                visitor.visitRefTypeSyntax_Type(node.Id, endNodeRef.Id);
              }

              clearStoppedVisitors();
              if(needPreorderStop)
                return;

              if ((!fact.IsFilterTurnedOn && !visitFilteredEdge) || (fact.getFilterState(endNodeRef.Id) == Filter.FilterState.NotFiltered) || (!originalFilterState && visitFilteredEdge)) {
                  endNodeRef.accept(this);
              }
              foreach (var visitor in visitorList) {
                visitor.visitEndRefTypeSyntax_Type(node.Id, endNodeRef.Id);
              }

              clearStoppedVisitors();
              if(needPreorderStop)
                return;

            }
        }

        public override void visit(Columbus.Csharp.Asg.Nodes.Expression.RefTypeSyntax node, bool callFirst = true){
          if (safeMode || visitCrossEdgeTree) {
            if (safeMode) {
              if (visitedNodes[(int)node.Id]) { // for safemode
                return;
              }
            }
            visitedNodes[(int)node.Id] = true;
          }

          foreach (var visitor in visitorList) {
            visitor.visit(node);
            incVisitorDepth(visitor);
          }

          clearStoppedVisitors();
          if(needPreorderStop)
            return;

          visitAllEdges(node, true);

          foreach (var visitor in visitorList) {
            decVisitorDepth(visitor);
            visitor.visitEnd(node);
          }

          clearStoppedVisitors();
        }

        /// <summary>
        /// It call the traversal for the edges
        /// </summary>
        /// <param name="node">[in] The node with own type</param>
        /// <param name="callVirtualBase">[in] This paramater is don't used just api copatibility used.</param>
        public void visitAllEdges(Columbus.Csharp.Asg.Nodes.Expression.RefValueExpressionSyntax node, bool callFirst = true){
            visitAllEdges((Columbus.Csharp.Asg.Nodes.Expression.ExpressionSyntax)(node),false);


            Columbus.Csharp.Asg.Nodes.Base.Base genNodePtr;
            // edge: Expression
            genNodePtr = fact.getRef(node.getExpression()) ;
            if (genNodePtr != null) {
              Columbus.Csharp.Asg.Nodes.Expression.ExpressionSyntax endNodeRef = (Columbus.Csharp.Asg.Nodes.Expression.ExpressionSyntax)(genNodePtr);
              foreach (var visitor in visitorList) {
                visitor.visitRefValueExpressionSyntax_Expression(node.Id, endNodeRef.Id);
              }

              clearStoppedVisitors();
              if(needPreorderStop)
                return;

              if ((!fact.IsFilterTurnedOn && !visitFilteredEdge) || (fact.getFilterState(endNodeRef.Id) == Filter.FilterState.NotFiltered) || (!originalFilterState && visitFilteredEdge)) {
                  endNodeRef.accept(this);
              }
              foreach (var visitor in visitorList) {
                visitor.visitEndRefValueExpressionSyntax_Expression(node.Id, endNodeRef.Id);
              }

              clearStoppedVisitors();
              if(needPreorderStop)
                return;

            }

            // edge: Type
            genNodePtr = fact.getRef(node.getType()) ;
            if (genNodePtr != null) {
              Columbus.Csharp.Asg.Nodes.Expression.TypeSyntax endNodeRef = (Columbus.Csharp.Asg.Nodes.Expression.TypeSyntax)(genNodePtr);
              foreach (var visitor in visitorList) {
                visitor.visitRefValueExpressionSyntax_Type(node.Id, endNodeRef.Id);
              }

              clearStoppedVisitors();
              if(needPreorderStop)
                return;

              if ((!fact.IsFilterTurnedOn && !visitFilteredEdge) || (fact.getFilterState(endNodeRef.Id) == Filter.FilterState.NotFiltered) || (!originalFilterState && visitFilteredEdge)) {
                  endNodeRef.accept(this);
              }
              foreach (var visitor in visitorList) {
                visitor.visitEndRefValueExpressionSyntax_Type(node.Id, endNodeRef.Id);
              }

              clearStoppedVisitors();
              if(needPreorderStop)
                return;

            }
        }

        public override void visit(Columbus.Csharp.Asg.Nodes.Expression.RefValueExpressionSyntax node, bool callFirst = true){
          if (safeMode || visitCrossEdgeTree) {
            if (safeMode) {
              if (visitedNodes[(int)node.Id]) { // for safemode
                return;
              }
            }
            visitedNodes[(int)node.Id] = true;
          }

          foreach (var visitor in visitorList) {
            visitor.visit(node);
            incVisitorDepth(visitor);
          }

          clearStoppedVisitors();
          if(needPreorderStop)
            return;

          visitAllEdges(node, true);

          foreach (var visitor in visitorList) {
            decVisitorDepth(visitor);
            visitor.visitEnd(node);
          }

          clearStoppedVisitors();
        }

        /// <summary>
        /// It call the traversal for the edges
        /// </summary>
        /// <param name="node">[in] The node with own type</param>
        /// <param name="callVirtualBase">[in] This paramater is don't used just api copatibility used.</param>
        public void visitAllEdges(Columbus.Csharp.Asg.Nodes.Expression.SimpleLambdaExpressionSyntax node, bool callFirst = true){
            visitAllEdges((Columbus.Csharp.Asg.Nodes.Expression.LambdaExpressionSyntax)(node),false);


            Columbus.Csharp.Asg.Nodes.Base.Base genNodePtr;
            // edge: Parameter
            genNodePtr = fact.getRef(node.getParameter()) ;
            if (genNodePtr != null) {
              Columbus.Csharp.Asg.Nodes.Structure.ParameterSyntax endNodeRef = (Columbus.Csharp.Asg.Nodes.Structure.ParameterSyntax)(genNodePtr);
              foreach (var visitor in visitorList) {
                visitor.visitSimpleLambdaExpressionSyntax_Parameter(node.Id, endNodeRef.Id);
              }

              clearStoppedVisitors();
              if(needPreorderStop)
                return;

              if ((!fact.IsFilterTurnedOn && !visitFilteredEdge) || (fact.getFilterState(endNodeRef.Id) == Filter.FilterState.NotFiltered) || (!originalFilterState && visitFilteredEdge)) {
                  endNodeRef.accept(this);
              }
              foreach (var visitor in visitorList) {
                visitor.visitEndSimpleLambdaExpressionSyntax_Parameter(node.Id, endNodeRef.Id);
              }

              clearStoppedVisitors();
              if(needPreorderStop)
                return;

            }
        }

        public override void visit(Columbus.Csharp.Asg.Nodes.Expression.SimpleLambdaExpressionSyntax node, bool callFirst = true){
          if (safeMode || visitCrossEdgeTree) {
            if (safeMode) {
              if (visitedNodes[(int)node.Id]) { // for safemode
                return;
              }
            }
            visitedNodes[(int)node.Id] = true;
          }

          foreach (var visitor in visitorList) {
            visitor.visit(node);
            incVisitorDepth(visitor);
          }

          clearStoppedVisitors();
          if(needPreorderStop)
            return;

          visitAllEdges(node, true);

          foreach (var visitor in visitorList) {
            decVisitorDepth(visitor);
            visitor.visitEnd(node);
          }

          clearStoppedVisitors();
        }

        /// <summary>
        /// It call the traversal for the edges
        /// </summary>
        /// <param name="node">[in] The node with own type</param>
        /// <param name="callVirtualBase">[in] This paramater is don't used just api copatibility used.</param>
        public void visitAllEdges(Columbus.Csharp.Asg.Nodes.Expression.SimpleNameSyntax node, bool callFirst = true){
            visitAllEdges((Columbus.Csharp.Asg.Nodes.Expression.NameSyntax)(node),false);
        }

        /// <summary>
        /// It call the traversal for the edges
        /// </summary>
        /// <param name="node">[in] The node with own type</param>
        /// <param name="callVirtualBase">[in] This paramater is don't used just api copatibility used.</param>
        public void visitAllEdges(Columbus.Csharp.Asg.Nodes.Expression.SizeOfExpressionSyntax node, bool callFirst = true){
            visitAllEdges((Columbus.Csharp.Asg.Nodes.Expression.ExpressionSyntax)(node),false);


            Columbus.Csharp.Asg.Nodes.Base.Base genNodePtr;
            // edge: Type
            genNodePtr = fact.getRef(node.getType()) ;
            if (genNodePtr != null) {
              Columbus.Csharp.Asg.Nodes.Expression.TypeSyntax endNodeRef = (Columbus.Csharp.Asg.Nodes.Expression.TypeSyntax)(genNodePtr);
              foreach (var visitor in visitorList) {
                visitor.visitSizeOfExpressionSyntax_Type(node.Id, endNodeRef.Id);
              }

              clearStoppedVisitors();
              if(needPreorderStop)
                return;

              if ((!fact.IsFilterTurnedOn && !visitFilteredEdge) || (fact.getFilterState(endNodeRef.Id) == Filter.FilterState.NotFiltered) || (!originalFilterState && visitFilteredEdge)) {
                  endNodeRef.accept(this);
              }
              foreach (var visitor in visitorList) {
                visitor.visitEndSizeOfExpressionSyntax_Type(node.Id, endNodeRef.Id);
              }

              clearStoppedVisitors();
              if(needPreorderStop)
                return;

            }
        }

        public override void visit(Columbus.Csharp.Asg.Nodes.Expression.SizeOfExpressionSyntax node, bool callFirst = true){
          if (safeMode || visitCrossEdgeTree) {
            if (safeMode) {
              if (visitedNodes[(int)node.Id]) { // for safemode
                return;
              }
            }
            visitedNodes[(int)node.Id] = true;
          }

          foreach (var visitor in visitorList) {
            visitor.visit(node);
            incVisitorDepth(visitor);
          }

          clearStoppedVisitors();
          if(needPreorderStop)
            return;

          visitAllEdges(node, true);

          foreach (var visitor in visitorList) {
            decVisitorDepth(visitor);
            visitor.visitEnd(node);
          }

          clearStoppedVisitors();
        }

        /// <summary>
        /// It call the traversal for the edges
        /// </summary>
        /// <param name="node">[in] The node with own type</param>
        /// <param name="callVirtualBase">[in] This paramater is don't used just api copatibility used.</param>
        public void visitAllEdges(Columbus.Csharp.Asg.Nodes.Expression.StackAllocArrayCreationExpressionSyntax node, bool callFirst = true){
            visitAllEdges((Columbus.Csharp.Asg.Nodes.Expression.ExpressionSyntax)(node),false);


            Columbus.Csharp.Asg.Nodes.Base.Base genNodePtr;
            // edge: Initializer
            genNodePtr = fact.getRef(node.getInitializer()) ;
            if (genNodePtr != null) {
              Columbus.Csharp.Asg.Nodes.Expression.InitializerExpressionSyntax endNodeRef = (Columbus.Csharp.Asg.Nodes.Expression.InitializerExpressionSyntax)(genNodePtr);
              foreach (var visitor in visitorList) {
                visitor.visitStackAllocArrayCreationExpressionSyntax_Initializer(node.Id, endNodeRef.Id);
              }

              clearStoppedVisitors();
              if(needPreorderStop)
                return;

              if ((!fact.IsFilterTurnedOn && !visitFilteredEdge) || (fact.getFilterState(endNodeRef.Id) == Filter.FilterState.NotFiltered) || (!originalFilterState && visitFilteredEdge)) {
                  endNodeRef.accept(this);
              }
              foreach (var visitor in visitorList) {
                visitor.visitEndStackAllocArrayCreationExpressionSyntax_Initializer(node.Id, endNodeRef.Id);
              }

              clearStoppedVisitors();
              if(needPreorderStop)
                return;

            }

            // edge: Type
            genNodePtr = fact.getRef(node.getType()) ;
            if (genNodePtr != null) {
              Columbus.Csharp.Asg.Nodes.Expression.TypeSyntax endNodeRef = (Columbus.Csharp.Asg.Nodes.Expression.TypeSyntax)(genNodePtr);
              foreach (var visitor in visitorList) {
                visitor.visitStackAllocArrayCreationExpressionSyntax_Type(node.Id, endNodeRef.Id);
              }

              clearStoppedVisitors();
              if(needPreorderStop)
                return;

              if ((!fact.IsFilterTurnedOn && !visitFilteredEdge) || (fact.getFilterState(endNodeRef.Id) == Filter.FilterState.NotFiltered) || (!originalFilterState && visitFilteredEdge)) {
                  endNodeRef.accept(this);
              }
              foreach (var visitor in visitorList) {
                visitor.visitEndStackAllocArrayCreationExpressionSyntax_Type(node.Id, endNodeRef.Id);
              }

              clearStoppedVisitors();
              if(needPreorderStop)
                return;

            }
        }

        public override void visit(Columbus.Csharp.Asg.Nodes.Expression.StackAllocArrayCreationExpressionSyntax node, bool callFirst = true){
          if (safeMode || visitCrossEdgeTree) {
            if (safeMode) {
              if (visitedNodes[(int)node.Id]) { // for safemode
                return;
              }
            }
            visitedNodes[(int)node.Id] = true;
          }

          foreach (var visitor in visitorList) {
            visitor.visit(node);
            incVisitorDepth(visitor);
          }

          clearStoppedVisitors();
          if(needPreorderStop)
            return;

          visitAllEdges(node, true);

          foreach (var visitor in visitorList) {
            decVisitorDepth(visitor);
            visitor.visitEnd(node);
          }

          clearStoppedVisitors();
        }

        /// <summary>
        /// It call the traversal for the edges
        /// </summary>
        /// <param name="node">[in] The node with own type</param>
        /// <param name="callVirtualBase">[in] This paramater is don't used just api copatibility used.</param>
        public void visitAllEdges(Columbus.Csharp.Asg.Nodes.Expression.SwitchExpressionSyntax node, bool callFirst = true){
            visitAllEdges((Columbus.Csharp.Asg.Nodes.Expression.ExpressionSyntax)(node),false);


            // edge: Arms
            ListIterator<Columbus.Csharp.Asg.Nodes.Structure.SwitchExpressionArmSyntax> iteratorForArms = node.ArmsListIteratorBegin;
            while (iteratorForArms.getValue() != null) {
               Columbus.Csharp.Asg.Nodes.Structure.SwitchExpressionArmSyntax endNodeRef = (Columbus.Csharp.Asg.Nodes.Structure.SwitchExpressionArmSyntax)iteratorForArms.getValue();
              foreach (var visitor in visitorList) {
                visitor.visitSwitchExpressionSyntax_Arms(node.Id, endNodeRef.Id);
              }

              clearStoppedVisitors();
              if(needPreorderStop)
                return;

              if ((!fact.IsFilterTurnedOn && !visitFilteredEdge) || (fact.getFilterState(endNodeRef.Id) == Filter.FilterState.NotFiltered) || (!originalFilterState && visitFilteredEdge)) {
                  endNodeRef.accept(this);
              }
              foreach (var visitor in visitorList) {
                visitor.visitEndSwitchExpressionSyntax_Arms(node.Id, endNodeRef.Id);
              }

              clearStoppedVisitors();
              if(needPreorderStop)
                return;

            iteratorForArms = iteratorForArms.getNext();
            }

            Columbus.Csharp.Asg.Nodes.Base.Base genNodePtr;
            // edge: GoverningExpression
            genNodePtr = fact.getRef(node.getGoverningExpression()) ;
            if (genNodePtr != null) {
              Columbus.Csharp.Asg.Nodes.Expression.ExpressionSyntax endNodeRef = (Columbus.Csharp.Asg.Nodes.Expression.ExpressionSyntax)(genNodePtr);
              foreach (var visitor in visitorList) {
                visitor.visitSwitchExpressionSyntax_GoverningExpression(node.Id, endNodeRef.Id);
              }

              clearStoppedVisitors();
              if(needPreorderStop)
                return;

              if ((!fact.IsFilterTurnedOn && !visitFilteredEdge) || (fact.getFilterState(endNodeRef.Id) == Filter.FilterState.NotFiltered) || (!originalFilterState && visitFilteredEdge)) {
                  endNodeRef.accept(this);
              }
              foreach (var visitor in visitorList) {
                visitor.visitEndSwitchExpressionSyntax_GoverningExpression(node.Id, endNodeRef.Id);
              }

              clearStoppedVisitors();
              if(needPreorderStop)
                return;

            }
        }

        public override void visit(Columbus.Csharp.Asg.Nodes.Expression.SwitchExpressionSyntax node, bool callFirst = true){
          if (safeMode || visitCrossEdgeTree) {
            if (safeMode) {
              if (visitedNodes[(int)node.Id]) { // for safemode
                return;
              }
            }
            visitedNodes[(int)node.Id] = true;
          }

          foreach (var visitor in visitorList) {
            visitor.visit(node);
            incVisitorDepth(visitor);
          }

          clearStoppedVisitors();
          if(needPreorderStop)
            return;

          visitAllEdges(node, true);

          foreach (var visitor in visitorList) {
            decVisitorDepth(visitor);
            visitor.visitEnd(node);
          }

          clearStoppedVisitors();
        }

        /// <summary>
        /// It call the traversal for the edges
        /// </summary>
        /// <param name="node">[in] The node with own type</param>
        /// <param name="callVirtualBase">[in] This paramater is don't used just api copatibility used.</param>
        public void visitAllEdges(Columbus.Csharp.Asg.Nodes.Expression.ThisExpressionSyntax node, bool callFirst = true){
            visitAllEdges((Columbus.Csharp.Asg.Nodes.Expression.InstanceExpressionSyntax)(node),false);
        }

        public override void visit(Columbus.Csharp.Asg.Nodes.Expression.ThisExpressionSyntax node, bool callFirst = true){
          if (safeMode || visitCrossEdgeTree) {
            if (safeMode) {
              if (visitedNodes[(int)node.Id]) { // for safemode
                return;
              }
            }
            visitedNodes[(int)node.Id] = true;
          }

          foreach (var visitor in visitorList) {
            visitor.visit(node);
            incVisitorDepth(visitor);
          }

          clearStoppedVisitors();
          if(needPreorderStop)
            return;

          visitAllEdges(node, true);

          foreach (var visitor in visitorList) {
            decVisitorDepth(visitor);
            visitor.visitEnd(node);
          }

          clearStoppedVisitors();
        }

        /// <summary>
        /// It call the traversal for the edges
        /// </summary>
        /// <param name="node">[in] The node with own type</param>
        /// <param name="callVirtualBase">[in] This paramater is don't used just api copatibility used.</param>
        public void visitAllEdges(Columbus.Csharp.Asg.Nodes.Expression.ThrowExpressionSyntax node, bool callFirst = true){
            visitAllEdges((Columbus.Csharp.Asg.Nodes.Expression.ExpressionSyntax)(node),false);


            Columbus.Csharp.Asg.Nodes.Base.Base genNodePtr;
            // edge: Expression
            genNodePtr = fact.getRef(node.getExpression()) ;
            if (genNodePtr != null) {
              Columbus.Csharp.Asg.Nodes.Expression.ExpressionSyntax endNodeRef = (Columbus.Csharp.Asg.Nodes.Expression.ExpressionSyntax)(genNodePtr);
              foreach (var visitor in visitorList) {
                visitor.visitThrowExpressionSyntax_Expression(node.Id, endNodeRef.Id);
              }

              clearStoppedVisitors();
              if(needPreorderStop)
                return;

              if ((!fact.IsFilterTurnedOn && !visitFilteredEdge) || (fact.getFilterState(endNodeRef.Id) == Filter.FilterState.NotFiltered) || (!originalFilterState && visitFilteredEdge)) {
                  endNodeRef.accept(this);
              }
              foreach (var visitor in visitorList) {
                visitor.visitEndThrowExpressionSyntax_Expression(node.Id, endNodeRef.Id);
              }

              clearStoppedVisitors();
              if(needPreorderStop)
                return;

            }
        }

        public override void visit(Columbus.Csharp.Asg.Nodes.Expression.ThrowExpressionSyntax node, bool callFirst = true){
          if (safeMode || visitCrossEdgeTree) {
            if (safeMode) {
              if (visitedNodes[(int)node.Id]) { // for safemode
                return;
              }
            }
            visitedNodes[(int)node.Id] = true;
          }

          foreach (var visitor in visitorList) {
            visitor.visit(node);
            incVisitorDepth(visitor);
          }

          clearStoppedVisitors();
          if(needPreorderStop)
            return;

          visitAllEdges(node, true);

          foreach (var visitor in visitorList) {
            decVisitorDepth(visitor);
            visitor.visitEnd(node);
          }

          clearStoppedVisitors();
        }

        /// <summary>
        /// It call the traversal for the edges
        /// </summary>
        /// <param name="node">[in] The node with own type</param>
        /// <param name="callVirtualBase">[in] This paramater is don't used just api copatibility used.</param>
        public void visitAllEdges(Columbus.Csharp.Asg.Nodes.Expression.TupleExpressionSyntax node, bool callFirst = true){
            visitAllEdges((Columbus.Csharp.Asg.Nodes.Expression.ExpressionSyntax)(node),false);


            // edge: Arguments
            ListIterator<Columbus.Csharp.Asg.Nodes.Structure.ArgumentSyntax> iteratorForArguments = node.ArgumentsListIteratorBegin;
            while (iteratorForArguments.getValue() != null) {
               Columbus.Csharp.Asg.Nodes.Structure.ArgumentSyntax endNodeRef = (Columbus.Csharp.Asg.Nodes.Structure.ArgumentSyntax)iteratorForArguments.getValue();
              foreach (var visitor in visitorList) {
                visitor.visitTupleExpressionSyntax_Arguments(node.Id, endNodeRef.Id);
              }

              clearStoppedVisitors();
              if(needPreorderStop)
                return;

              if ((!fact.IsFilterTurnedOn && !visitFilteredEdge) || (fact.getFilterState(endNodeRef.Id) == Filter.FilterState.NotFiltered) || (!originalFilterState && visitFilteredEdge)) {
                  endNodeRef.accept(this);
              }
              foreach (var visitor in visitorList) {
                visitor.visitEndTupleExpressionSyntax_Arguments(node.Id, endNodeRef.Id);
              }

              clearStoppedVisitors();
              if(needPreorderStop)
                return;

            iteratorForArguments = iteratorForArguments.getNext();
            }
        }

        public override void visit(Columbus.Csharp.Asg.Nodes.Expression.TupleExpressionSyntax node, bool callFirst = true){
          if (safeMode || visitCrossEdgeTree) {
            if (safeMode) {
              if (visitedNodes[(int)node.Id]) { // for safemode
                return;
              }
            }
            visitedNodes[(int)node.Id] = true;
          }

          foreach (var visitor in visitorList) {
            visitor.visit(node);
            incVisitorDepth(visitor);
          }

          clearStoppedVisitors();
          if(needPreorderStop)
            return;

          visitAllEdges(node, true);

          foreach (var visitor in visitorList) {
            decVisitorDepth(visitor);
            visitor.visitEnd(node);
          }

          clearStoppedVisitors();
        }

        /// <summary>
        /// It call the traversal for the edges
        /// </summary>
        /// <param name="node">[in] The node with own type</param>
        /// <param name="callVirtualBase">[in] This paramater is don't used just api copatibility used.</param>
        public void visitAllEdges(Columbus.Csharp.Asg.Nodes.Expression.TupleTypeSyntax node, bool callFirst = true){
            visitAllEdges((Columbus.Csharp.Asg.Nodes.Expression.TypeSyntax)(node),false);


            // edge: Elements
            ListIterator<Columbus.Csharp.Asg.Nodes.Structure.TupleElementSyntax> iteratorForElements = node.ElementsListIteratorBegin;
            while (iteratorForElements.getValue() != null) {
               Columbus.Csharp.Asg.Nodes.Structure.TupleElementSyntax endNodeRef = (Columbus.Csharp.Asg.Nodes.Structure.TupleElementSyntax)iteratorForElements.getValue();
              foreach (var visitor in visitorList) {
                visitor.visitTupleTypeSyntax_Elements(node.Id, endNodeRef.Id);
              }

              clearStoppedVisitors();
              if(needPreorderStop)
                return;

              if ((!fact.IsFilterTurnedOn && !visitFilteredEdge) || (fact.getFilterState(endNodeRef.Id) == Filter.FilterState.NotFiltered) || (!originalFilterState && visitFilteredEdge)) {
                  endNodeRef.accept(this);
              }
              foreach (var visitor in visitorList) {
                visitor.visitEndTupleTypeSyntax_Elements(node.Id, endNodeRef.Id);
              }

              clearStoppedVisitors();
              if(needPreorderStop)
                return;

            iteratorForElements = iteratorForElements.getNext();
            }
        }

        public override void visit(Columbus.Csharp.Asg.Nodes.Expression.TupleTypeSyntax node, bool callFirst = true){
          if (safeMode || visitCrossEdgeTree) {
            if (safeMode) {
              if (visitedNodes[(int)node.Id]) { // for safemode
                return;
              }
            }
            visitedNodes[(int)node.Id] = true;
          }

          foreach (var visitor in visitorList) {
            visitor.visit(node);
            incVisitorDepth(visitor);
          }

          clearStoppedVisitors();
          if(needPreorderStop)
            return;

          visitAllEdges(node, true);

          foreach (var visitor in visitorList) {
            decVisitorDepth(visitor);
            visitor.visitEnd(node);
          }

          clearStoppedVisitors();
        }

        /// <summary>
        /// It call the traversal for the edges
        /// </summary>
        /// <param name="node">[in] The node with own type</param>
        /// <param name="callVirtualBase">[in] This paramater is don't used just api copatibility used.</param>
        public void visitAllEdges(Columbus.Csharp.Asg.Nodes.Expression.TypeOfExpressionSyntax node, bool callFirst = true){
            visitAllEdges((Columbus.Csharp.Asg.Nodes.Expression.ExpressionSyntax)(node),false);


            Columbus.Csharp.Asg.Nodes.Base.Base genNodePtr;
            // edge: Type
            genNodePtr = fact.getRef(node.getType()) ;
            if (genNodePtr != null) {
              Columbus.Csharp.Asg.Nodes.Expression.TypeSyntax endNodeRef = (Columbus.Csharp.Asg.Nodes.Expression.TypeSyntax)(genNodePtr);
              foreach (var visitor in visitorList) {
                visitor.visitTypeOfExpressionSyntax_Type(node.Id, endNodeRef.Id);
              }

              clearStoppedVisitors();
              if(needPreorderStop)
                return;

              if ((!fact.IsFilterTurnedOn && !visitFilteredEdge) || (fact.getFilterState(endNodeRef.Id) == Filter.FilterState.NotFiltered) || (!originalFilterState && visitFilteredEdge)) {
                  endNodeRef.accept(this);
              }
              foreach (var visitor in visitorList) {
                visitor.visitEndTypeOfExpressionSyntax_Type(node.Id, endNodeRef.Id);
              }

              clearStoppedVisitors();
              if(needPreorderStop)
                return;

            }
        }

        public override void visit(Columbus.Csharp.Asg.Nodes.Expression.TypeOfExpressionSyntax node, bool callFirst = true){
          if (safeMode || visitCrossEdgeTree) {
            if (safeMode) {
              if (visitedNodes[(int)node.Id]) { // for safemode
                return;
              }
            }
            visitedNodes[(int)node.Id] = true;
          }

          foreach (var visitor in visitorList) {
            visitor.visit(node);
            incVisitorDepth(visitor);
          }

          clearStoppedVisitors();
          if(needPreorderStop)
            return;

          visitAllEdges(node, true);

          foreach (var visitor in visitorList) {
            decVisitorDepth(visitor);
            visitor.visitEnd(node);
          }

          clearStoppedVisitors();
        }

        /// <summary>
        /// It call the traversal for the edges
        /// </summary>
        /// <param name="node">[in] The node with own type</param>
        /// <param name="callVirtualBase">[in] This paramater is don't used just api copatibility used.</param>
        public void visitAllEdges(Columbus.Csharp.Asg.Nodes.Expression.TypeSyntax node, bool callFirst = true){
            visitAllEdges((Columbus.Csharp.Asg.Nodes.Expression.ExpressionSyntax)(node),false);


            Columbus.Csharp.Asg.Nodes.Base.Base genNodePtr;
            // edge: OriginalDefinition
            genNodePtr = fact.getRef(node.getOriginalDefinition()) ;
            if (genNodePtr != null) {
              Columbus.Csharp.Asg.Nodes.Structure.MemberDeclarationSyntax endNodeRef = (Columbus.Csharp.Asg.Nodes.Structure.MemberDeclarationSyntax)(genNodePtr);
              foreach (var visitor in visitorList) {
                visitor.visitTypeSyntax_OriginalDefinition(node.Id, endNodeRef.Id);
              }

              clearStoppedVisitors();
              if(needPreorderStop)
                return;

              if ((!fact.IsFilterTurnedOn && !visitFilteredEdge) || (fact.getFilterState(endNodeRef.Id) == Filter.FilterState.NotFiltered) || (!originalFilterState && visitFilteredEdge)) {
                  if (apRoot != null) {
                    if (visitCrossEdgeTree) {
                      unvisitedNodes[(int)endNodeRef.Id] = true;
                    }
                  }
                  if (traversaldCrossEdges[(int)Types.EdgeKind.edkTypeSyntax_OriginalDefinition]) {
                    endNodeRef.accept(this);
                  }
              }
              foreach (var visitor in visitorList) {
                visitor.visitEndTypeSyntax_OriginalDefinition(node.Id, endNodeRef.Id);
              }

              clearStoppedVisitors();
              if(needPreorderStop)
                return;

            }
        }

        /// <summary>
        /// It call the traversal for the edges
        /// </summary>
        /// <param name="node">[in] The node with own type</param>
        /// <param name="callVirtualBase">[in] This paramater is don't used just api copatibility used.</param>
        public void visitAllEdges(Columbus.Csharp.Asg.Nodes.Statement.BlockSyntax node, bool callFirst = true){
            visitAllEdges((Columbus.Csharp.Asg.Nodes.Statement.StatementSyntax)(node),false);


            // edge: Statements
            ListIterator<Columbus.Csharp.Asg.Nodes.Statement.StatementSyntax> iteratorForStatements = node.StatementsListIteratorBegin;
            while (iteratorForStatements.getValue() != null) {
               Columbus.Csharp.Asg.Nodes.Statement.StatementSyntax endNodeRef = (Columbus.Csharp.Asg.Nodes.Statement.StatementSyntax)iteratorForStatements.getValue();
              foreach (var visitor in visitorList) {
                visitor.visitBlockSyntax_Statements(node.Id, endNodeRef.Id);
              }

              clearStoppedVisitors();
              if(needPreorderStop)
                return;

              if ((!fact.IsFilterTurnedOn && !visitFilteredEdge) || (fact.getFilterState(endNodeRef.Id) == Filter.FilterState.NotFiltered) || (!originalFilterState && visitFilteredEdge)) {
                  endNodeRef.accept(this);
              }
              foreach (var visitor in visitorList) {
                visitor.visitEndBlockSyntax_Statements(node.Id, endNodeRef.Id);
              }

              clearStoppedVisitors();
              if(needPreorderStop)
                return;

            iteratorForStatements = iteratorForStatements.getNext();
            }
        }

        public override void visit(Columbus.Csharp.Asg.Nodes.Statement.BlockSyntax node, bool callFirst = true){
          if (safeMode || visitCrossEdgeTree) {
            if (safeMode) {
              if (visitedNodes[(int)node.Id]) { // for safemode
                return;
              }
            }
            visitedNodes[(int)node.Id] = true;
          }

          foreach (var visitor in visitorList) {
            visitor.visit(node);
            incVisitorDepth(visitor);
          }

          clearStoppedVisitors();
          if(needPreorderStop)
            return;

          visitAllEdges(node, true);

          foreach (var visitor in visitorList) {
            decVisitorDepth(visitor);
            visitor.visitEnd(node);
          }

          clearStoppedVisitors();
        }

        /// <summary>
        /// It call the traversal for the edges
        /// </summary>
        /// <param name="node">[in] The node with own type</param>
        /// <param name="callVirtualBase">[in] This paramater is don't used just api copatibility used.</param>
        public void visitAllEdges(Columbus.Csharp.Asg.Nodes.Statement.BreakStatementSyntax node, bool callFirst = true){
            visitAllEdges((Columbus.Csharp.Asg.Nodes.Statement.StatementSyntax)(node),false);
        }

        public override void visit(Columbus.Csharp.Asg.Nodes.Statement.BreakStatementSyntax node, bool callFirst = true){
          if (safeMode || visitCrossEdgeTree) {
            if (safeMode) {
              if (visitedNodes[(int)node.Id]) { // for safemode
                return;
              }
            }
            visitedNodes[(int)node.Id] = true;
          }

          foreach (var visitor in visitorList) {
            visitor.visit(node);
            incVisitorDepth(visitor);
          }

          clearStoppedVisitors();
          if(needPreorderStop)
            return;

          visitAllEdges(node, true);

          foreach (var visitor in visitorList) {
            decVisitorDepth(visitor);
            visitor.visitEnd(node);
          }

          clearStoppedVisitors();
        }

        /// <summary>
        /// It call the traversal for the edges
        /// </summary>
        /// <param name="node">[in] The node with own type</param>
        /// <param name="callVirtualBase">[in] This paramater is don't used just api copatibility used.</param>
        public void visitAllEdges(Columbus.Csharp.Asg.Nodes.Statement.CheckedStatementSyntax node, bool callFirst = true){
            visitAllEdges((Columbus.Csharp.Asg.Nodes.Statement.StatementSyntax)(node),false);


            Columbus.Csharp.Asg.Nodes.Base.Base genNodePtr;
            // edge: Block
            genNodePtr = fact.getRef(node.getBlock()) ;
            if (genNodePtr != null) {
              Columbus.Csharp.Asg.Nodes.Statement.BlockSyntax endNodeRef = (Columbus.Csharp.Asg.Nodes.Statement.BlockSyntax)(genNodePtr);
              foreach (var visitor in visitorList) {
                visitor.visitCheckedStatementSyntax_Block(node.Id, endNodeRef.Id);
              }

              clearStoppedVisitors();
              if(needPreorderStop)
                return;

              if ((!fact.IsFilterTurnedOn && !visitFilteredEdge) || (fact.getFilterState(endNodeRef.Id) == Filter.FilterState.NotFiltered) || (!originalFilterState && visitFilteredEdge)) {
                  endNodeRef.accept(this);
              }
              foreach (var visitor in visitorList) {
                visitor.visitEndCheckedStatementSyntax_Block(node.Id, endNodeRef.Id);
              }

              clearStoppedVisitors();
              if(needPreorderStop)
                return;

            }
        }

        public override void visit(Columbus.Csharp.Asg.Nodes.Statement.CheckedStatementSyntax node, bool callFirst = true){
          if (safeMode || visitCrossEdgeTree) {
            if (safeMode) {
              if (visitedNodes[(int)node.Id]) { // for safemode
                return;
              }
            }
            visitedNodes[(int)node.Id] = true;
          }

          foreach (var visitor in visitorList) {
            visitor.visit(node);
            incVisitorDepth(visitor);
          }

          clearStoppedVisitors();
          if(needPreorderStop)
            return;

          visitAllEdges(node, true);

          foreach (var visitor in visitorList) {
            decVisitorDepth(visitor);
            visitor.visitEnd(node);
          }

          clearStoppedVisitors();
        }

        /// <summary>
        /// It call the traversal for the edges
        /// </summary>
        /// <param name="node">[in] The node with own type</param>
        /// <param name="callVirtualBase">[in] This paramater is don't used just api copatibility used.</param>
        public void visitAllEdges(Columbus.Csharp.Asg.Nodes.Statement.CommonForEachStatementSyntax node, bool callFirst = true){
            visitAllEdges((Columbus.Csharp.Asg.Nodes.Statement.StatementSyntax)(node),false);


            Columbus.Csharp.Asg.Nodes.Base.Base genNodePtr;
            // edge: Expression
            genNodePtr = fact.getRef(node.getExpression()) ;
            if (genNodePtr != null) {
              Columbus.Csharp.Asg.Nodes.Expression.ExpressionSyntax endNodeRef = (Columbus.Csharp.Asg.Nodes.Expression.ExpressionSyntax)(genNodePtr);
              foreach (var visitor in visitorList) {
                visitor.visitCommonForEachStatementSyntax_Expression(node.Id, endNodeRef.Id);
              }

              clearStoppedVisitors();
              if(needPreorderStop)
                return;

              if ((!fact.IsFilterTurnedOn && !visitFilteredEdge) || (fact.getFilterState(endNodeRef.Id) == Filter.FilterState.NotFiltered) || (!originalFilterState && visitFilteredEdge)) {
                  endNodeRef.accept(this);
              }
              foreach (var visitor in visitorList) {
                visitor.visitEndCommonForEachStatementSyntax_Expression(node.Id, endNodeRef.Id);
              }

              clearStoppedVisitors();
              if(needPreorderStop)
                return;

            }

            // edge: Statement
            genNodePtr = fact.getRef(node.getStatement()) ;
            if (genNodePtr != null) {
              Columbus.Csharp.Asg.Nodes.Statement.StatementSyntax endNodeRef = (Columbus.Csharp.Asg.Nodes.Statement.StatementSyntax)(genNodePtr);
              foreach (var visitor in visitorList) {
                visitor.visitCommonForEachStatementSyntax_Statement(node.Id, endNodeRef.Id);
              }

              clearStoppedVisitors();
              if(needPreorderStop)
                return;

              if ((!fact.IsFilterTurnedOn && !visitFilteredEdge) || (fact.getFilterState(endNodeRef.Id) == Filter.FilterState.NotFiltered) || (!originalFilterState && visitFilteredEdge)) {
                  endNodeRef.accept(this);
              }
              foreach (var visitor in visitorList) {
                visitor.visitEndCommonForEachStatementSyntax_Statement(node.Id, endNodeRef.Id);
              }

              clearStoppedVisitors();
              if(needPreorderStop)
                return;

            }
        }

        /// <summary>
        /// It call the traversal for the edges
        /// </summary>
        /// <param name="node">[in] The node with own type</param>
        /// <param name="callVirtualBase">[in] This paramater is don't used just api copatibility used.</param>
        public void visitAllEdges(Columbus.Csharp.Asg.Nodes.Statement.ContinueStatementSyntax node, bool callFirst = true){
            visitAllEdges((Columbus.Csharp.Asg.Nodes.Statement.StatementSyntax)(node),false);
        }

        public override void visit(Columbus.Csharp.Asg.Nodes.Statement.ContinueStatementSyntax node, bool callFirst = true){
          if (safeMode || visitCrossEdgeTree) {
            if (safeMode) {
              if (visitedNodes[(int)node.Id]) { // for safemode
                return;
              }
            }
            visitedNodes[(int)node.Id] = true;
          }

          foreach (var visitor in visitorList) {
            visitor.visit(node);
            incVisitorDepth(visitor);
          }

          clearStoppedVisitors();
          if(needPreorderStop)
            return;

          visitAllEdges(node, true);

          foreach (var visitor in visitorList) {
            decVisitorDepth(visitor);
            visitor.visitEnd(node);
          }

          clearStoppedVisitors();
        }

        /// <summary>
        /// It call the traversal for the edges
        /// </summary>
        /// <param name="node">[in] The node with own type</param>
        /// <param name="callVirtualBase">[in] This paramater is don't used just api copatibility used.</param>
        public void visitAllEdges(Columbus.Csharp.Asg.Nodes.Statement.DoStatementSyntax node, bool callFirst = true){
            visitAllEdges((Columbus.Csharp.Asg.Nodes.Statement.StatementSyntax)(node),false);


            Columbus.Csharp.Asg.Nodes.Base.Base genNodePtr;
            // edge: Condition
            genNodePtr = fact.getRef(node.getCondition()) ;
            if (genNodePtr != null) {
              Columbus.Csharp.Asg.Nodes.Expression.ExpressionSyntax endNodeRef = (Columbus.Csharp.Asg.Nodes.Expression.ExpressionSyntax)(genNodePtr);
              foreach (var visitor in visitorList) {
                visitor.visitDoStatementSyntax_Condition(node.Id, endNodeRef.Id);
              }

              clearStoppedVisitors();
              if(needPreorderStop)
                return;

              if ((!fact.IsFilterTurnedOn && !visitFilteredEdge) || (fact.getFilterState(endNodeRef.Id) == Filter.FilterState.NotFiltered) || (!originalFilterState && visitFilteredEdge)) {
                  endNodeRef.accept(this);
              }
              foreach (var visitor in visitorList) {
                visitor.visitEndDoStatementSyntax_Condition(node.Id, endNodeRef.Id);
              }

              clearStoppedVisitors();
              if(needPreorderStop)
                return;

            }

            // edge: Statement
            genNodePtr = fact.getRef(node.getStatement()) ;
            if (genNodePtr != null) {
              Columbus.Csharp.Asg.Nodes.Statement.StatementSyntax endNodeRef = (Columbus.Csharp.Asg.Nodes.Statement.StatementSyntax)(genNodePtr);
              foreach (var visitor in visitorList) {
                visitor.visitDoStatementSyntax_Statement(node.Id, endNodeRef.Id);
              }

              clearStoppedVisitors();
              if(needPreorderStop)
                return;

              if ((!fact.IsFilterTurnedOn && !visitFilteredEdge) || (fact.getFilterState(endNodeRef.Id) == Filter.FilterState.NotFiltered) || (!originalFilterState && visitFilteredEdge)) {
                  endNodeRef.accept(this);
              }
              foreach (var visitor in visitorList) {
                visitor.visitEndDoStatementSyntax_Statement(node.Id, endNodeRef.Id);
              }

              clearStoppedVisitors();
              if(needPreorderStop)
                return;

            }
        }

        public override void visit(Columbus.Csharp.Asg.Nodes.Statement.DoStatementSyntax node, bool callFirst = true){
          if (safeMode || visitCrossEdgeTree) {
            if (safeMode) {
              if (visitedNodes[(int)node.Id]) { // for safemode
                return;
              }
            }
            visitedNodes[(int)node.Id] = true;
          }

          foreach (var visitor in visitorList) {
            visitor.visit(node);
            incVisitorDepth(visitor);
          }

          clearStoppedVisitors();
          if(needPreorderStop)
            return;

          visitAllEdges(node, true);

          foreach (var visitor in visitorList) {
            decVisitorDepth(visitor);
            visitor.visitEnd(node);
          }

          clearStoppedVisitors();
        }

        /// <summary>
        /// It call the traversal for the edges
        /// </summary>
        /// <param name="node">[in] The node with own type</param>
        /// <param name="callVirtualBase">[in] This paramater is don't used just api copatibility used.</param>
        public void visitAllEdges(Columbus.Csharp.Asg.Nodes.Statement.EmptyStatementSyntax node, bool callFirst = true){
            visitAllEdges((Columbus.Csharp.Asg.Nodes.Statement.StatementSyntax)(node),false);
        }

        public override void visit(Columbus.Csharp.Asg.Nodes.Statement.EmptyStatementSyntax node, bool callFirst = true){
          if (safeMode || visitCrossEdgeTree) {
            if (safeMode) {
              if (visitedNodes[(int)node.Id]) { // for safemode
                return;
              }
            }
            visitedNodes[(int)node.Id] = true;
          }

          foreach (var visitor in visitorList) {
            visitor.visit(node);
            incVisitorDepth(visitor);
          }

          clearStoppedVisitors();
          if(needPreorderStop)
            return;

          visitAllEdges(node, true);

          foreach (var visitor in visitorList) {
            decVisitorDepth(visitor);
            visitor.visitEnd(node);
          }

          clearStoppedVisitors();
        }

        /// <summary>
        /// It call the traversal for the edges
        /// </summary>
        /// <param name="node">[in] The node with own type</param>
        /// <param name="callVirtualBase">[in] This paramater is don't used just api copatibility used.</param>
        public void visitAllEdges(Columbus.Csharp.Asg.Nodes.Statement.ExpressionStatementSyntax node, bool callFirst = true){
            visitAllEdges((Columbus.Csharp.Asg.Nodes.Statement.StatementSyntax)(node),false);


            Columbus.Csharp.Asg.Nodes.Base.Base genNodePtr;
            // edge: Expression
            genNodePtr = fact.getRef(node.getExpression()) ;
            if (genNodePtr != null) {
              Columbus.Csharp.Asg.Nodes.Expression.ExpressionSyntax endNodeRef = (Columbus.Csharp.Asg.Nodes.Expression.ExpressionSyntax)(genNodePtr);
              foreach (var visitor in visitorList) {
                visitor.visitExpressionStatementSyntax_Expression(node.Id, endNodeRef.Id);
              }

              clearStoppedVisitors();
              if(needPreorderStop)
                return;

              if ((!fact.IsFilterTurnedOn && !visitFilteredEdge) || (fact.getFilterState(endNodeRef.Id) == Filter.FilterState.NotFiltered) || (!originalFilterState && visitFilteredEdge)) {
                  endNodeRef.accept(this);
              }
              foreach (var visitor in visitorList) {
                visitor.visitEndExpressionStatementSyntax_Expression(node.Id, endNodeRef.Id);
              }

              clearStoppedVisitors();
              if(needPreorderStop)
                return;

            }
        }

        public override void visit(Columbus.Csharp.Asg.Nodes.Statement.ExpressionStatementSyntax node, bool callFirst = true){
          if (safeMode || visitCrossEdgeTree) {
            if (safeMode) {
              if (visitedNodes[(int)node.Id]) { // for safemode
                return;
              }
            }
            visitedNodes[(int)node.Id] = true;
          }

          foreach (var visitor in visitorList) {
            visitor.visit(node);
            incVisitorDepth(visitor);
          }

          clearStoppedVisitors();
          if(needPreorderStop)
            return;

          visitAllEdges(node, true);

          foreach (var visitor in visitorList) {
            decVisitorDepth(visitor);
            visitor.visitEnd(node);
          }

          clearStoppedVisitors();
        }

        /// <summary>
        /// It call the traversal for the edges
        /// </summary>
        /// <param name="node">[in] The node with own type</param>
        /// <param name="callVirtualBase">[in] This paramater is don't used just api copatibility used.</param>
        public void visitAllEdges(Columbus.Csharp.Asg.Nodes.Statement.FixedStatementSyntax node, bool callFirst = true){
            visitAllEdges((Columbus.Csharp.Asg.Nodes.Statement.StatementSyntax)(node),false);


            Columbus.Csharp.Asg.Nodes.Base.Base genNodePtr;
            // edge: Declaration
            genNodePtr = fact.getRef(node.getDeclaration()) ;
            if (genNodePtr != null) {
              Columbus.Csharp.Asg.Nodes.Structure.VariableDeclarationSyntax endNodeRef = (Columbus.Csharp.Asg.Nodes.Structure.VariableDeclarationSyntax)(genNodePtr);
              foreach (var visitor in visitorList) {
                visitor.visitFixedStatementSyntax_Declaration(node.Id, endNodeRef.Id);
              }

              clearStoppedVisitors();
              if(needPreorderStop)
                return;

              if ((!fact.IsFilterTurnedOn && !visitFilteredEdge) || (fact.getFilterState(endNodeRef.Id) == Filter.FilterState.NotFiltered) || (!originalFilterState && visitFilteredEdge)) {
                  endNodeRef.accept(this);
              }
              foreach (var visitor in visitorList) {
                visitor.visitEndFixedStatementSyntax_Declaration(node.Id, endNodeRef.Id);
              }

              clearStoppedVisitors();
              if(needPreorderStop)
                return;

            }

            // edge: Statement
            genNodePtr = fact.getRef(node.getStatement()) ;
            if (genNodePtr != null) {
              Columbus.Csharp.Asg.Nodes.Statement.StatementSyntax endNodeRef = (Columbus.Csharp.Asg.Nodes.Statement.StatementSyntax)(genNodePtr);
              foreach (var visitor in visitorList) {
                visitor.visitFixedStatementSyntax_Statement(node.Id, endNodeRef.Id);
              }

              clearStoppedVisitors();
              if(needPreorderStop)
                return;

              if ((!fact.IsFilterTurnedOn && !visitFilteredEdge) || (fact.getFilterState(endNodeRef.Id) == Filter.FilterState.NotFiltered) || (!originalFilterState && visitFilteredEdge)) {
                  endNodeRef.accept(this);
              }
              foreach (var visitor in visitorList) {
                visitor.visitEndFixedStatementSyntax_Statement(node.Id, endNodeRef.Id);
              }

              clearStoppedVisitors();
              if(needPreorderStop)
                return;

            }
        }

        public override void visit(Columbus.Csharp.Asg.Nodes.Statement.FixedStatementSyntax node, bool callFirst = true){
          if (safeMode || visitCrossEdgeTree) {
            if (safeMode) {
              if (visitedNodes[(int)node.Id]) { // for safemode
                return;
              }
            }
            visitedNodes[(int)node.Id] = true;
          }

          foreach (var visitor in visitorList) {
            visitor.visit(node);
            incVisitorDepth(visitor);
          }

          clearStoppedVisitors();
          if(needPreorderStop)
            return;

          visitAllEdges(node, true);

          foreach (var visitor in visitorList) {
            decVisitorDepth(visitor);
            visitor.visitEnd(node);
          }

          clearStoppedVisitors();
        }

        /// <summary>
        /// It call the traversal for the edges
        /// </summary>
        /// <param name="node">[in] The node with own type</param>
        /// <param name="callVirtualBase">[in] This paramater is don't used just api copatibility used.</param>
        public void visitAllEdges(Columbus.Csharp.Asg.Nodes.Statement.ForEachStatementSyntax node, bool callFirst = true){
            visitAllEdges((Columbus.Csharp.Asg.Nodes.Statement.CommonForEachStatementSyntax)(node),false);


            Columbus.Csharp.Asg.Nodes.Base.Base genNodePtr;
            // edge: Type
            genNodePtr = fact.getRef(node.getType()) ;
            if (genNodePtr != null) {
              Columbus.Csharp.Asg.Nodes.Expression.TypeSyntax endNodeRef = (Columbus.Csharp.Asg.Nodes.Expression.TypeSyntax)(genNodePtr);
              foreach (var visitor in visitorList) {
                visitor.visitForEachStatementSyntax_Type(node.Id, endNodeRef.Id);
              }

              clearStoppedVisitors();
              if(needPreorderStop)
                return;

              if ((!fact.IsFilterTurnedOn && !visitFilteredEdge) || (fact.getFilterState(endNodeRef.Id) == Filter.FilterState.NotFiltered) || (!originalFilterState && visitFilteredEdge)) {
                  endNodeRef.accept(this);
              }
              foreach (var visitor in visitorList) {
                visitor.visitEndForEachStatementSyntax_Type(node.Id, endNodeRef.Id);
              }

              clearStoppedVisitors();
              if(needPreorderStop)
                return;

            }
        }

        public override void visit(Columbus.Csharp.Asg.Nodes.Statement.ForEachStatementSyntax node, bool callFirst = true){
          if (safeMode || visitCrossEdgeTree) {
            if (safeMode) {
              if (visitedNodes[(int)node.Id]) { // for safemode
                return;
              }
            }
            visitedNodes[(int)node.Id] = true;
          }

          foreach (var visitor in visitorList) {
            visitor.visit(node);
            incVisitorDepth(visitor);
          }

          clearStoppedVisitors();
          if(needPreorderStop)
            return;

          visitAllEdges(node, true);

          foreach (var visitor in visitorList) {
            decVisitorDepth(visitor);
            visitor.visitEnd(node);
          }

          clearStoppedVisitors();
        }

        /// <summary>
        /// It call the traversal for the edges
        /// </summary>
        /// <param name="node">[in] The node with own type</param>
        /// <param name="callVirtualBase">[in] This paramater is don't used just api copatibility used.</param>
        public void visitAllEdges(Columbus.Csharp.Asg.Nodes.Statement.ForEachVariableStatementSyntax node, bool callFirst = true){
            visitAllEdges((Columbus.Csharp.Asg.Nodes.Statement.CommonForEachStatementSyntax)(node),false);


            Columbus.Csharp.Asg.Nodes.Base.Base genNodePtr;
            // edge: Variable
            genNodePtr = fact.getRef(node.getVariable()) ;
            if (genNodePtr != null) {
              Columbus.Csharp.Asg.Nodes.Expression.ExpressionSyntax endNodeRef = (Columbus.Csharp.Asg.Nodes.Expression.ExpressionSyntax)(genNodePtr);
              foreach (var visitor in visitorList) {
                visitor.visitForEachVariableStatementSyntax_Variable(node.Id, endNodeRef.Id);
              }

              clearStoppedVisitors();
              if(needPreorderStop)
                return;

              if ((!fact.IsFilterTurnedOn && !visitFilteredEdge) || (fact.getFilterState(endNodeRef.Id) == Filter.FilterState.NotFiltered) || (!originalFilterState && visitFilteredEdge)) {
                  endNodeRef.accept(this);
              }
              foreach (var visitor in visitorList) {
                visitor.visitEndForEachVariableStatementSyntax_Variable(node.Id, endNodeRef.Id);
              }

              clearStoppedVisitors();
              if(needPreorderStop)
                return;

            }
        }

        public override void visit(Columbus.Csharp.Asg.Nodes.Statement.ForEachVariableStatementSyntax node, bool callFirst = true){
          if (safeMode || visitCrossEdgeTree) {
            if (safeMode) {
              if (visitedNodes[(int)node.Id]) { // for safemode
                return;
              }
            }
            visitedNodes[(int)node.Id] = true;
          }

          foreach (var visitor in visitorList) {
            visitor.visit(node);
            incVisitorDepth(visitor);
          }

          clearStoppedVisitors();
          if(needPreorderStop)
            return;

          visitAllEdges(node, true);

          foreach (var visitor in visitorList) {
            decVisitorDepth(visitor);
            visitor.visitEnd(node);
          }

          clearStoppedVisitors();
        }

        /// <summary>
        /// It call the traversal for the edges
        /// </summary>
        /// <param name="node">[in] The node with own type</param>
        /// <param name="callVirtualBase">[in] This paramater is don't used just api copatibility used.</param>
        public void visitAllEdges(Columbus.Csharp.Asg.Nodes.Statement.ForStatementSyntax node, bool callFirst = true){
            visitAllEdges((Columbus.Csharp.Asg.Nodes.Statement.StatementSyntax)(node),false);


            Columbus.Csharp.Asg.Nodes.Base.Base genNodePtr;
            // edge: Condition
            genNodePtr = fact.getRef(node.getCondition()) ;
            if (genNodePtr != null) {
              Columbus.Csharp.Asg.Nodes.Expression.ExpressionSyntax endNodeRef = (Columbus.Csharp.Asg.Nodes.Expression.ExpressionSyntax)(genNodePtr);
              foreach (var visitor in visitorList) {
                visitor.visitForStatementSyntax_Condition(node.Id, endNodeRef.Id);
              }

              clearStoppedVisitors();
              if(needPreorderStop)
                return;

              if ((!fact.IsFilterTurnedOn && !visitFilteredEdge) || (fact.getFilterState(endNodeRef.Id) == Filter.FilterState.NotFiltered) || (!originalFilterState && visitFilteredEdge)) {
                  endNodeRef.accept(this);
              }
              foreach (var visitor in visitorList) {
                visitor.visitEndForStatementSyntax_Condition(node.Id, endNodeRef.Id);
              }

              clearStoppedVisitors();
              if(needPreorderStop)
                return;

            }

            // edge: Declaration
            genNodePtr = fact.getRef(node.getDeclaration()) ;
            if (genNodePtr != null) {
              Columbus.Csharp.Asg.Nodes.Structure.VariableDeclarationSyntax endNodeRef = (Columbus.Csharp.Asg.Nodes.Structure.VariableDeclarationSyntax)(genNodePtr);
              foreach (var visitor in visitorList) {
                visitor.visitForStatementSyntax_Declaration(node.Id, endNodeRef.Id);
              }

              clearStoppedVisitors();
              if(needPreorderStop)
                return;

              if ((!fact.IsFilterTurnedOn && !visitFilteredEdge) || (fact.getFilterState(endNodeRef.Id) == Filter.FilterState.NotFiltered) || (!originalFilterState && visitFilteredEdge)) {
                  endNodeRef.accept(this);
              }
              foreach (var visitor in visitorList) {
                visitor.visitEndForStatementSyntax_Declaration(node.Id, endNodeRef.Id);
              }

              clearStoppedVisitors();
              if(needPreorderStop)
                return;

            }

            // edge: Incrementors
            ListIterator<Columbus.Csharp.Asg.Nodes.Expression.ExpressionSyntax> iteratorForIncrementors = node.IncrementorsListIteratorBegin;
            while (iteratorForIncrementors.getValue() != null) {
               Columbus.Csharp.Asg.Nodes.Expression.ExpressionSyntax endNodeRef = (Columbus.Csharp.Asg.Nodes.Expression.ExpressionSyntax)iteratorForIncrementors.getValue();
              foreach (var visitor in visitorList) {
                visitor.visitForStatementSyntax_Incrementors(node.Id, endNodeRef.Id);
              }

              clearStoppedVisitors();
              if(needPreorderStop)
                return;

              if ((!fact.IsFilterTurnedOn && !visitFilteredEdge) || (fact.getFilterState(endNodeRef.Id) == Filter.FilterState.NotFiltered) || (!originalFilterState && visitFilteredEdge)) {
                  endNodeRef.accept(this);
              }
              foreach (var visitor in visitorList) {
                visitor.visitEndForStatementSyntax_Incrementors(node.Id, endNodeRef.Id);
              }

              clearStoppedVisitors();
              if(needPreorderStop)
                return;

            iteratorForIncrementors = iteratorForIncrementors.getNext();
            }

            // edge: Initializers
            ListIterator<Columbus.Csharp.Asg.Nodes.Expression.ExpressionSyntax> iteratorForInitializers = node.InitializersListIteratorBegin;
            while (iteratorForInitializers.getValue() != null) {
               Columbus.Csharp.Asg.Nodes.Expression.ExpressionSyntax endNodeRef = (Columbus.Csharp.Asg.Nodes.Expression.ExpressionSyntax)iteratorForInitializers.getValue();
              foreach (var visitor in visitorList) {
                visitor.visitForStatementSyntax_Initializers(node.Id, endNodeRef.Id);
              }

              clearStoppedVisitors();
              if(needPreorderStop)
                return;

              if ((!fact.IsFilterTurnedOn && !visitFilteredEdge) || (fact.getFilterState(endNodeRef.Id) == Filter.FilterState.NotFiltered) || (!originalFilterState && visitFilteredEdge)) {
                  endNodeRef.accept(this);
              }
              foreach (var visitor in visitorList) {
                visitor.visitEndForStatementSyntax_Initializers(node.Id, endNodeRef.Id);
              }

              clearStoppedVisitors();
              if(needPreorderStop)
                return;

            iteratorForInitializers = iteratorForInitializers.getNext();
            }

            // edge: Statement
            genNodePtr = fact.getRef(node.getStatement()) ;
            if (genNodePtr != null) {
              Columbus.Csharp.Asg.Nodes.Statement.StatementSyntax endNodeRef = (Columbus.Csharp.Asg.Nodes.Statement.StatementSyntax)(genNodePtr);
              foreach (var visitor in visitorList) {
                visitor.visitForStatementSyntax_Statement(node.Id, endNodeRef.Id);
              }

              clearStoppedVisitors();
              if(needPreorderStop)
                return;

              if ((!fact.IsFilterTurnedOn && !visitFilteredEdge) || (fact.getFilterState(endNodeRef.Id) == Filter.FilterState.NotFiltered) || (!originalFilterState && visitFilteredEdge)) {
                  endNodeRef.accept(this);
              }
              foreach (var visitor in visitorList) {
                visitor.visitEndForStatementSyntax_Statement(node.Id, endNodeRef.Id);
              }

              clearStoppedVisitors();
              if(needPreorderStop)
                return;

            }
        }

        public override void visit(Columbus.Csharp.Asg.Nodes.Statement.ForStatementSyntax node, bool callFirst = true){
          if (safeMode || visitCrossEdgeTree) {
            if (safeMode) {
              if (visitedNodes[(int)node.Id]) { // for safemode
                return;
              }
            }
            visitedNodes[(int)node.Id] = true;
          }

          foreach (var visitor in visitorList) {
            visitor.visit(node);
            incVisitorDepth(visitor);
          }

          clearStoppedVisitors();
          if(needPreorderStop)
            return;

          visitAllEdges(node, true);

          foreach (var visitor in visitorList) {
            decVisitorDepth(visitor);
            visitor.visitEnd(node);
          }

          clearStoppedVisitors();
        }

        /// <summary>
        /// It call the traversal for the edges
        /// </summary>
        /// <param name="node">[in] The node with own type</param>
        /// <param name="callVirtualBase">[in] This paramater is don't used just api copatibility used.</param>
        public void visitAllEdges(Columbus.Csharp.Asg.Nodes.Statement.GotoStatementSyntax node, bool callFirst = true){
            visitAllEdges((Columbus.Csharp.Asg.Nodes.Statement.StatementSyntax)(node),false);


            Columbus.Csharp.Asg.Nodes.Base.Base genNodePtr;
            // edge: Expression
            genNodePtr = fact.getRef(node.getExpression()) ;
            if (genNodePtr != null) {
              Columbus.Csharp.Asg.Nodes.Expression.ExpressionSyntax endNodeRef = (Columbus.Csharp.Asg.Nodes.Expression.ExpressionSyntax)(genNodePtr);
              foreach (var visitor in visitorList) {
                visitor.visitGotoStatementSyntax_Expression(node.Id, endNodeRef.Id);
              }

              clearStoppedVisitors();
              if(needPreorderStop)
                return;

              if ((!fact.IsFilterTurnedOn && !visitFilteredEdge) || (fact.getFilterState(endNodeRef.Id) == Filter.FilterState.NotFiltered) || (!originalFilterState && visitFilteredEdge)) {
                  endNodeRef.accept(this);
              }
              foreach (var visitor in visitorList) {
                visitor.visitEndGotoStatementSyntax_Expression(node.Id, endNodeRef.Id);
              }

              clearStoppedVisitors();
              if(needPreorderStop)
                return;

            }
        }

        public override void visit(Columbus.Csharp.Asg.Nodes.Statement.GotoStatementSyntax node, bool callFirst = true){
          if (safeMode || visitCrossEdgeTree) {
            if (safeMode) {
              if (visitedNodes[(int)node.Id]) { // for safemode
                return;
              }
            }
            visitedNodes[(int)node.Id] = true;
          }

          foreach (var visitor in visitorList) {
            visitor.visit(node);
            incVisitorDepth(visitor);
          }

          clearStoppedVisitors();
          if(needPreorderStop)
            return;

          visitAllEdges(node, true);

          foreach (var visitor in visitorList) {
            decVisitorDepth(visitor);
            visitor.visitEnd(node);
          }

          clearStoppedVisitors();
        }

        /// <summary>
        /// It call the traversal for the edges
        /// </summary>
        /// <param name="node">[in] The node with own type</param>
        /// <param name="callVirtualBase">[in] This paramater is don't used just api copatibility used.</param>
        public void visitAllEdges(Columbus.Csharp.Asg.Nodes.Statement.IfStatementSyntax node, bool callFirst = true){
            visitAllEdges((Columbus.Csharp.Asg.Nodes.Statement.StatementSyntax)(node),false);


            Columbus.Csharp.Asg.Nodes.Base.Base genNodePtr;
            // edge: Condition
            genNodePtr = fact.getRef(node.getCondition()) ;
            if (genNodePtr != null) {
              Columbus.Csharp.Asg.Nodes.Expression.ExpressionSyntax endNodeRef = (Columbus.Csharp.Asg.Nodes.Expression.ExpressionSyntax)(genNodePtr);
              foreach (var visitor in visitorList) {
                visitor.visitIfStatementSyntax_Condition(node.Id, endNodeRef.Id);
              }

              clearStoppedVisitors();
              if(needPreorderStop)
                return;

              if ((!fact.IsFilterTurnedOn && !visitFilteredEdge) || (fact.getFilterState(endNodeRef.Id) == Filter.FilterState.NotFiltered) || (!originalFilterState && visitFilteredEdge)) {
                  endNodeRef.accept(this);
              }
              foreach (var visitor in visitorList) {
                visitor.visitEndIfStatementSyntax_Condition(node.Id, endNodeRef.Id);
              }

              clearStoppedVisitors();
              if(needPreorderStop)
                return;

            }

            // edge: Else
            genNodePtr = fact.getRef(node.getElse()) ;
            if (genNodePtr != null) {
              Columbus.Csharp.Asg.Nodes.Structure.ElseClauseSyntax endNodeRef = (Columbus.Csharp.Asg.Nodes.Structure.ElseClauseSyntax)(genNodePtr);
              foreach (var visitor in visitorList) {
                visitor.visitIfStatementSyntax_Else(node.Id, endNodeRef.Id);
              }

              clearStoppedVisitors();
              if(needPreorderStop)
                return;

              if ((!fact.IsFilterTurnedOn && !visitFilteredEdge) || (fact.getFilterState(endNodeRef.Id) == Filter.FilterState.NotFiltered) || (!originalFilterState && visitFilteredEdge)) {
                  endNodeRef.accept(this);
              }
              foreach (var visitor in visitorList) {
                visitor.visitEndIfStatementSyntax_Else(node.Id, endNodeRef.Id);
              }

              clearStoppedVisitors();
              if(needPreorderStop)
                return;

            }

            // edge: Statement
            genNodePtr = fact.getRef(node.getStatement()) ;
            if (genNodePtr != null) {
              Columbus.Csharp.Asg.Nodes.Statement.StatementSyntax endNodeRef = (Columbus.Csharp.Asg.Nodes.Statement.StatementSyntax)(genNodePtr);
              foreach (var visitor in visitorList) {
                visitor.visitIfStatementSyntax_Statement(node.Id, endNodeRef.Id);
              }

              clearStoppedVisitors();
              if(needPreorderStop)
                return;

              if ((!fact.IsFilterTurnedOn && !visitFilteredEdge) || (fact.getFilterState(endNodeRef.Id) == Filter.FilterState.NotFiltered) || (!originalFilterState && visitFilteredEdge)) {
                  endNodeRef.accept(this);
              }
              foreach (var visitor in visitorList) {
                visitor.visitEndIfStatementSyntax_Statement(node.Id, endNodeRef.Id);
              }

              clearStoppedVisitors();
              if(needPreorderStop)
                return;

            }
        }

        public override void visit(Columbus.Csharp.Asg.Nodes.Statement.IfStatementSyntax node, bool callFirst = true){
          if (safeMode || visitCrossEdgeTree) {
            if (safeMode) {
              if (visitedNodes[(int)node.Id]) { // for safemode
                return;
              }
            }
            visitedNodes[(int)node.Id] = true;
          }

          foreach (var visitor in visitorList) {
            visitor.visit(node);
            incVisitorDepth(visitor);
          }

          clearStoppedVisitors();
          if(needPreorderStop)
            return;

          visitAllEdges(node, true);

          foreach (var visitor in visitorList) {
            decVisitorDepth(visitor);
            visitor.visitEnd(node);
          }

          clearStoppedVisitors();
        }

        /// <summary>
        /// It call the traversal for the edges
        /// </summary>
        /// <param name="node">[in] The node with own type</param>
        /// <param name="callVirtualBase">[in] This paramater is don't used just api copatibility used.</param>
        public void visitAllEdges(Columbus.Csharp.Asg.Nodes.Statement.LabeledStatementSyntax node, bool callFirst = true){
            visitAllEdges((Columbus.Csharp.Asg.Nodes.Statement.StatementSyntax)(node),false);


            Columbus.Csharp.Asg.Nodes.Base.Base genNodePtr;
            // edge: Statement
            genNodePtr = fact.getRef(node.getStatement()) ;
            if (genNodePtr != null) {
              Columbus.Csharp.Asg.Nodes.Statement.StatementSyntax endNodeRef = (Columbus.Csharp.Asg.Nodes.Statement.StatementSyntax)(genNodePtr);
              foreach (var visitor in visitorList) {
                visitor.visitLabeledStatementSyntax_Statement(node.Id, endNodeRef.Id);
              }

              clearStoppedVisitors();
              if(needPreorderStop)
                return;

              if ((!fact.IsFilterTurnedOn && !visitFilteredEdge) || (fact.getFilterState(endNodeRef.Id) == Filter.FilterState.NotFiltered) || (!originalFilterState && visitFilteredEdge)) {
                  endNodeRef.accept(this);
              }
              foreach (var visitor in visitorList) {
                visitor.visitEndLabeledStatementSyntax_Statement(node.Id, endNodeRef.Id);
              }

              clearStoppedVisitors();
              if(needPreorderStop)
                return;

            }
        }

        public override void visit(Columbus.Csharp.Asg.Nodes.Statement.LabeledStatementSyntax node, bool callFirst = true){
          if (safeMode || visitCrossEdgeTree) {
            if (safeMode) {
              if (visitedNodes[(int)node.Id]) { // for safemode
                return;
              }
            }
            visitedNodes[(int)node.Id] = true;
          }

          foreach (var visitor in visitorList) {
            visitor.visit(node);
            incVisitorDepth(visitor);
          }

          clearStoppedVisitors();
          if(needPreorderStop)
            return;

          visitAllEdges(node, true);

          foreach (var visitor in visitorList) {
            decVisitorDepth(visitor);
            visitor.visitEnd(node);
          }

          clearStoppedVisitors();
        }

        /// <summary>
        /// It call the traversal for the edges
        /// </summary>
        /// <param name="node">[in] The node with own type</param>
        /// <param name="callVirtualBase">[in] This paramater is don't used just api copatibility used.</param>
        public void visitAllEdges(Columbus.Csharp.Asg.Nodes.Statement.LocalDeclarationStatementSyntax node, bool callFirst = true){
            visitAllEdges((Columbus.Csharp.Asg.Nodes.Statement.StatementSyntax)(node),false);


            Columbus.Csharp.Asg.Nodes.Base.Base genNodePtr;
            // edge: Declaration
            genNodePtr = fact.getRef(node.getDeclaration()) ;
            if (genNodePtr != null) {
              Columbus.Csharp.Asg.Nodes.Structure.VariableDeclarationSyntax endNodeRef = (Columbus.Csharp.Asg.Nodes.Structure.VariableDeclarationSyntax)(genNodePtr);
              foreach (var visitor in visitorList) {
                visitor.visitLocalDeclarationStatementSyntax_Declaration(node.Id, endNodeRef.Id);
              }

              clearStoppedVisitors();
              if(needPreorderStop)
                return;

              if ((!fact.IsFilterTurnedOn && !visitFilteredEdge) || (fact.getFilterState(endNodeRef.Id) == Filter.FilterState.NotFiltered) || (!originalFilterState && visitFilteredEdge)) {
                  endNodeRef.accept(this);
              }
              foreach (var visitor in visitorList) {
                visitor.visitEndLocalDeclarationStatementSyntax_Declaration(node.Id, endNodeRef.Id);
              }

              clearStoppedVisitors();
              if(needPreorderStop)
                return;

            }
        }

        public override void visit(Columbus.Csharp.Asg.Nodes.Statement.LocalDeclarationStatementSyntax node, bool callFirst = true){
          if (safeMode || visitCrossEdgeTree) {
            if (safeMode) {
              if (visitedNodes[(int)node.Id]) { // for safemode
                return;
              }
            }
            visitedNodes[(int)node.Id] = true;
          }

          foreach (var visitor in visitorList) {
            visitor.visit(node);
            incVisitorDepth(visitor);
          }

          clearStoppedVisitors();
          if(needPreorderStop)
            return;

          visitAllEdges(node, true);

          foreach (var visitor in visitorList) {
            decVisitorDepth(visitor);
            visitor.visitEnd(node);
          }

          clearStoppedVisitors();
        }

        /// <summary>
        /// It call the traversal for the edges
        /// </summary>
        /// <param name="node">[in] The node with own type</param>
        /// <param name="callVirtualBase">[in] This paramater is don't used just api copatibility used.</param>
        public void visitAllEdges(Columbus.Csharp.Asg.Nodes.Statement.LocalFunctionStatementSyntax node, bool callFirst = true){
            visitAllEdges((Columbus.Csharp.Asg.Nodes.Statement.StatementSyntax)(node),false);


            Columbus.Csharp.Asg.Nodes.Base.Base genNodePtr;
            // edge: Body
            genNodePtr = fact.getRef(node.getBody()) ;
            if (genNodePtr != null) {
              Columbus.Csharp.Asg.Nodes.Statement.BlockSyntax endNodeRef = (Columbus.Csharp.Asg.Nodes.Statement.BlockSyntax)(genNodePtr);
              foreach (var visitor in visitorList) {
                visitor.visitLocalFunctionStatementSyntax_Body(node.Id, endNodeRef.Id);
              }

              clearStoppedVisitors();
              if(needPreorderStop)
                return;

              if ((!fact.IsFilterTurnedOn && !visitFilteredEdge) || (fact.getFilterState(endNodeRef.Id) == Filter.FilterState.NotFiltered) || (!originalFilterState && visitFilteredEdge)) {
                  endNodeRef.accept(this);
              }
              foreach (var visitor in visitorList) {
                visitor.visitEndLocalFunctionStatementSyntax_Body(node.Id, endNodeRef.Id);
              }

              clearStoppedVisitors();
              if(needPreorderStop)
                return;

            }

            // edge: ConstraintClauses
            ListIterator<Columbus.Csharp.Asg.Nodes.Structure.TypeParameterConstraintClauseSyntax> iteratorForConstraintClauses = node.ConstraintClausesListIteratorBegin;
            while (iteratorForConstraintClauses.getValue() != null) {
               Columbus.Csharp.Asg.Nodes.Structure.TypeParameterConstraintClauseSyntax endNodeRef = (Columbus.Csharp.Asg.Nodes.Structure.TypeParameterConstraintClauseSyntax)iteratorForConstraintClauses.getValue();
              foreach (var visitor in visitorList) {
                visitor.visitLocalFunctionStatementSyntax_ConstraintClauses(node.Id, endNodeRef.Id);
              }

              clearStoppedVisitors();
              if(needPreorderStop)
                return;

              if ((!fact.IsFilterTurnedOn && !visitFilteredEdge) || (fact.getFilterState(endNodeRef.Id) == Filter.FilterState.NotFiltered) || (!originalFilterState && visitFilteredEdge)) {
                  endNodeRef.accept(this);
              }
              foreach (var visitor in visitorList) {
                visitor.visitEndLocalFunctionStatementSyntax_ConstraintClauses(node.Id, endNodeRef.Id);
              }

              clearStoppedVisitors();
              if(needPreorderStop)
                return;

            iteratorForConstraintClauses = iteratorForConstraintClauses.getNext();
            }

            // edge: ExpressionBody
            genNodePtr = fact.getRef(node.getExpressionBody()) ;
            if (genNodePtr != null) {
              Columbus.Csharp.Asg.Nodes.Structure.ArrowExpressionClauseSyntax endNodeRef = (Columbus.Csharp.Asg.Nodes.Structure.ArrowExpressionClauseSyntax)(genNodePtr);
              foreach (var visitor in visitorList) {
                visitor.visitLocalFunctionStatementSyntax_ExpressionBody(node.Id, endNodeRef.Id);
              }

              clearStoppedVisitors();
              if(needPreorderStop)
                return;

              if ((!fact.IsFilterTurnedOn && !visitFilteredEdge) || (fact.getFilterState(endNodeRef.Id) == Filter.FilterState.NotFiltered) || (!originalFilterState && visitFilteredEdge)) {
                  endNodeRef.accept(this);
              }
              foreach (var visitor in visitorList) {
                visitor.visitEndLocalFunctionStatementSyntax_ExpressionBody(node.Id, endNodeRef.Id);
              }

              clearStoppedVisitors();
              if(needPreorderStop)
                return;

            }

            // edge: ParameterList
            genNodePtr = fact.getRef(node.getParameterList()) ;
            if (genNodePtr != null) {
              Columbus.Csharp.Asg.Nodes.Structure.ParameterListSyntax endNodeRef = (Columbus.Csharp.Asg.Nodes.Structure.ParameterListSyntax)(genNodePtr);
              foreach (var visitor in visitorList) {
                visitor.visitLocalFunctionStatementSyntax_ParameterList(node.Id, endNodeRef.Id);
              }

              clearStoppedVisitors();
              if(needPreorderStop)
                return;

              if ((!fact.IsFilterTurnedOn && !visitFilteredEdge) || (fact.getFilterState(endNodeRef.Id) == Filter.FilterState.NotFiltered) || (!originalFilterState && visitFilteredEdge)) {
                  endNodeRef.accept(this);
              }
              foreach (var visitor in visitorList) {
                visitor.visitEndLocalFunctionStatementSyntax_ParameterList(node.Id, endNodeRef.Id);
              }

              clearStoppedVisitors();
              if(needPreorderStop)
                return;

            }

            // edge: ReturnType
            genNodePtr = fact.getRef(node.getReturnType()) ;
            if (genNodePtr != null) {
              Columbus.Csharp.Asg.Nodes.Expression.TypeSyntax endNodeRef = (Columbus.Csharp.Asg.Nodes.Expression.TypeSyntax)(genNodePtr);
              foreach (var visitor in visitorList) {
                visitor.visitLocalFunctionStatementSyntax_ReturnType(node.Id, endNodeRef.Id);
              }

              clearStoppedVisitors();
              if(needPreorderStop)
                return;

              if ((!fact.IsFilterTurnedOn && !visitFilteredEdge) || (fact.getFilterState(endNodeRef.Id) == Filter.FilterState.NotFiltered) || (!originalFilterState && visitFilteredEdge)) {
                  endNodeRef.accept(this);
              }
              foreach (var visitor in visitorList) {
                visitor.visitEndLocalFunctionStatementSyntax_ReturnType(node.Id, endNodeRef.Id);
              }

              clearStoppedVisitors();
              if(needPreorderStop)
                return;

            }

            // edge: TypeParameterList
            genNodePtr = fact.getRef(node.getTypeParameterList()) ;
            if (genNodePtr != null) {
              Columbus.Csharp.Asg.Nodes.Structure.TypeParameterListSyntax endNodeRef = (Columbus.Csharp.Asg.Nodes.Structure.TypeParameterListSyntax)(genNodePtr);
              foreach (var visitor in visitorList) {
                visitor.visitLocalFunctionStatementSyntax_TypeParameterList(node.Id, endNodeRef.Id);
              }

              clearStoppedVisitors();
              if(needPreorderStop)
                return;

              if ((!fact.IsFilterTurnedOn && !visitFilteredEdge) || (fact.getFilterState(endNodeRef.Id) == Filter.FilterState.NotFiltered) || (!originalFilterState && visitFilteredEdge)) {
                  endNodeRef.accept(this);
              }
              foreach (var visitor in visitorList) {
                visitor.visitEndLocalFunctionStatementSyntax_TypeParameterList(node.Id, endNodeRef.Id);
              }

              clearStoppedVisitors();
              if(needPreorderStop)
                return;

            }
        }

        public override void visit(Columbus.Csharp.Asg.Nodes.Statement.LocalFunctionStatementSyntax node, bool callFirst = true){
          if (safeMode || visitCrossEdgeTree) {
            if (safeMode) {
              if (visitedNodes[(int)node.Id]) { // for safemode
                return;
              }
            }
            visitedNodes[(int)node.Id] = true;
          }

          foreach (var visitor in visitorList) {
            visitor.visit(node);
            incVisitorDepth(visitor);
          }

          clearStoppedVisitors();
          if(needPreorderStop)
            return;

          visitAllEdges(node, true);

          foreach (var visitor in visitorList) {
            decVisitorDepth(visitor);
            visitor.visitEnd(node);
          }

          clearStoppedVisitors();
        }

        /// <summary>
        /// It call the traversal for the edges
        /// </summary>
        /// <param name="node">[in] The node with own type</param>
        /// <param name="callVirtualBase">[in] This paramater is don't used just api copatibility used.</param>
        public void visitAllEdges(Columbus.Csharp.Asg.Nodes.Statement.LockStatementSyntax node, bool callFirst = true){
            visitAllEdges((Columbus.Csharp.Asg.Nodes.Statement.StatementSyntax)(node),false);


            Columbus.Csharp.Asg.Nodes.Base.Base genNodePtr;
            // edge: Expression
            genNodePtr = fact.getRef(node.getExpression()) ;
            if (genNodePtr != null) {
              Columbus.Csharp.Asg.Nodes.Expression.ExpressionSyntax endNodeRef = (Columbus.Csharp.Asg.Nodes.Expression.ExpressionSyntax)(genNodePtr);
              foreach (var visitor in visitorList) {
                visitor.visitLockStatementSyntax_Expression(node.Id, endNodeRef.Id);
              }

              clearStoppedVisitors();
              if(needPreorderStop)
                return;

              if ((!fact.IsFilterTurnedOn && !visitFilteredEdge) || (fact.getFilterState(endNodeRef.Id) == Filter.FilterState.NotFiltered) || (!originalFilterState && visitFilteredEdge)) {
                  endNodeRef.accept(this);
              }
              foreach (var visitor in visitorList) {
                visitor.visitEndLockStatementSyntax_Expression(node.Id, endNodeRef.Id);
              }

              clearStoppedVisitors();
              if(needPreorderStop)
                return;

            }

            // edge: Statement
            genNodePtr = fact.getRef(node.getStatement()) ;
            if (genNodePtr != null) {
              Columbus.Csharp.Asg.Nodes.Statement.StatementSyntax endNodeRef = (Columbus.Csharp.Asg.Nodes.Statement.StatementSyntax)(genNodePtr);
              foreach (var visitor in visitorList) {
                visitor.visitLockStatementSyntax_Statement(node.Id, endNodeRef.Id);
              }

              clearStoppedVisitors();
              if(needPreorderStop)
                return;

              if ((!fact.IsFilterTurnedOn && !visitFilteredEdge) || (fact.getFilterState(endNodeRef.Id) == Filter.FilterState.NotFiltered) || (!originalFilterState && visitFilteredEdge)) {
                  endNodeRef.accept(this);
              }
              foreach (var visitor in visitorList) {
                visitor.visitEndLockStatementSyntax_Statement(node.Id, endNodeRef.Id);
              }

              clearStoppedVisitors();
              if(needPreorderStop)
                return;

            }
        }

        public override void visit(Columbus.Csharp.Asg.Nodes.Statement.LockStatementSyntax node, bool callFirst = true){
          if (safeMode || visitCrossEdgeTree) {
            if (safeMode) {
              if (visitedNodes[(int)node.Id]) { // for safemode
                return;
              }
            }
            visitedNodes[(int)node.Id] = true;
          }

          foreach (var visitor in visitorList) {
            visitor.visit(node);
            incVisitorDepth(visitor);
          }

          clearStoppedVisitors();
          if(needPreorderStop)
            return;

          visitAllEdges(node, true);

          foreach (var visitor in visitorList) {
            decVisitorDepth(visitor);
            visitor.visitEnd(node);
          }

          clearStoppedVisitors();
        }

        /// <summary>
        /// It call the traversal for the edges
        /// </summary>
        /// <param name="node">[in] The node with own type</param>
        /// <param name="callVirtualBase">[in] This paramater is don't used just api copatibility used.</param>
        public void visitAllEdges(Columbus.Csharp.Asg.Nodes.Statement.ReturnStatementSyntax node, bool callFirst = true){
            visitAllEdges((Columbus.Csharp.Asg.Nodes.Statement.StatementSyntax)(node),false);


            Columbus.Csharp.Asg.Nodes.Base.Base genNodePtr;
            // edge: Expression
            genNodePtr = fact.getRef(node.getExpression()) ;
            if (genNodePtr != null) {
              Columbus.Csharp.Asg.Nodes.Expression.ExpressionSyntax endNodeRef = (Columbus.Csharp.Asg.Nodes.Expression.ExpressionSyntax)(genNodePtr);
              foreach (var visitor in visitorList) {
                visitor.visitReturnStatementSyntax_Expression(node.Id, endNodeRef.Id);
              }

              clearStoppedVisitors();
              if(needPreorderStop)
                return;

              if ((!fact.IsFilterTurnedOn && !visitFilteredEdge) || (fact.getFilterState(endNodeRef.Id) == Filter.FilterState.NotFiltered) || (!originalFilterState && visitFilteredEdge)) {
                  endNodeRef.accept(this);
              }
              foreach (var visitor in visitorList) {
                visitor.visitEndReturnStatementSyntax_Expression(node.Id, endNodeRef.Id);
              }

              clearStoppedVisitors();
              if(needPreorderStop)
                return;

            }
        }

        public override void visit(Columbus.Csharp.Asg.Nodes.Statement.ReturnStatementSyntax node, bool callFirst = true){
          if (safeMode || visitCrossEdgeTree) {
            if (safeMode) {
              if (visitedNodes[(int)node.Id]) { // for safemode
                return;
              }
            }
            visitedNodes[(int)node.Id] = true;
          }

          foreach (var visitor in visitorList) {
            visitor.visit(node);
            incVisitorDepth(visitor);
          }

          clearStoppedVisitors();
          if(needPreorderStop)
            return;

          visitAllEdges(node, true);

          foreach (var visitor in visitorList) {
            decVisitorDepth(visitor);
            visitor.visitEnd(node);
          }

          clearStoppedVisitors();
        }

        /// <summary>
        /// It call the traversal for the edges
        /// </summary>
        /// <param name="node">[in] The node with own type</param>
        /// <param name="callVirtualBase">[in] This paramater is don't used just api copatibility used.</param>
        public void visitAllEdges(Columbus.Csharp.Asg.Nodes.Statement.StatementSyntax node, bool callFirst = true){
            visitAllEdges((Columbus.Csharp.Asg.Nodes.Base.Positioned)(node),false);


            // edge: AttributeLists
            ListIterator<Columbus.Csharp.Asg.Nodes.Structure.AttributeListSyntax> iteratorForAttributeLists = node.AttributeListsListIteratorBegin;
            while (iteratorForAttributeLists.getValue() != null) {
               Columbus.Csharp.Asg.Nodes.Structure.AttributeListSyntax endNodeRef = (Columbus.Csharp.Asg.Nodes.Structure.AttributeListSyntax)iteratorForAttributeLists.getValue();
              foreach (var visitor in visitorList) {
                visitor.visitStatementSyntax_AttributeLists(node.Id, endNodeRef.Id);
              }

              clearStoppedVisitors();
              if(needPreorderStop)
                return;

              if ((!fact.IsFilterTurnedOn && !visitFilteredEdge) || (fact.getFilterState(endNodeRef.Id) == Filter.FilterState.NotFiltered) || (!originalFilterState && visitFilteredEdge)) {
                  endNodeRef.accept(this);
              }
              foreach (var visitor in visitorList) {
                visitor.visitEndStatementSyntax_AttributeLists(node.Id, endNodeRef.Id);
              }

              clearStoppedVisitors();
              if(needPreorderStop)
                return;

            iteratorForAttributeLists = iteratorForAttributeLists.getNext();
            }
        }

        /// <summary>
        /// It call the traversal for the edges
        /// </summary>
        /// <param name="node">[in] The node with own type</param>
        /// <param name="callVirtualBase">[in] This paramater is don't used just api copatibility used.</param>
        public void visitAllEdges(Columbus.Csharp.Asg.Nodes.Statement.SwitchStatementSyntax node, bool callFirst = true){
            visitAllEdges((Columbus.Csharp.Asg.Nodes.Statement.StatementSyntax)(node),false);


            Columbus.Csharp.Asg.Nodes.Base.Base genNodePtr;
            // edge: Expression
            genNodePtr = fact.getRef(node.getExpression()) ;
            if (genNodePtr != null) {
              Columbus.Csharp.Asg.Nodes.Expression.ExpressionSyntax endNodeRef = (Columbus.Csharp.Asg.Nodes.Expression.ExpressionSyntax)(genNodePtr);
              foreach (var visitor in visitorList) {
                visitor.visitSwitchStatementSyntax_Expression(node.Id, endNodeRef.Id);
              }

              clearStoppedVisitors();
              if(needPreorderStop)
                return;

              if ((!fact.IsFilterTurnedOn && !visitFilteredEdge) || (fact.getFilterState(endNodeRef.Id) == Filter.FilterState.NotFiltered) || (!originalFilterState && visitFilteredEdge)) {
                  endNodeRef.accept(this);
              }
              foreach (var visitor in visitorList) {
                visitor.visitEndSwitchStatementSyntax_Expression(node.Id, endNodeRef.Id);
              }

              clearStoppedVisitors();
              if(needPreorderStop)
                return;

            }

            // edge: Sections
            ListIterator<Columbus.Csharp.Asg.Nodes.Structure.SwitchSectionSyntax> iteratorForSections = node.SectionsListIteratorBegin;
            while (iteratorForSections.getValue() != null) {
               Columbus.Csharp.Asg.Nodes.Structure.SwitchSectionSyntax endNodeRef = (Columbus.Csharp.Asg.Nodes.Structure.SwitchSectionSyntax)iteratorForSections.getValue();
              foreach (var visitor in visitorList) {
                visitor.visitSwitchStatementSyntax_Sections(node.Id, endNodeRef.Id);
              }

              clearStoppedVisitors();
              if(needPreorderStop)
                return;

              if ((!fact.IsFilterTurnedOn && !visitFilteredEdge) || (fact.getFilterState(endNodeRef.Id) == Filter.FilterState.NotFiltered) || (!originalFilterState && visitFilteredEdge)) {
                  endNodeRef.accept(this);
              }
              foreach (var visitor in visitorList) {
                visitor.visitEndSwitchStatementSyntax_Sections(node.Id, endNodeRef.Id);
              }

              clearStoppedVisitors();
              if(needPreorderStop)
                return;

            iteratorForSections = iteratorForSections.getNext();
            }
        }

        public override void visit(Columbus.Csharp.Asg.Nodes.Statement.SwitchStatementSyntax node, bool callFirst = true){
          if (safeMode || visitCrossEdgeTree) {
            if (safeMode) {
              if (visitedNodes[(int)node.Id]) { // for safemode
                return;
              }
            }
            visitedNodes[(int)node.Id] = true;
          }

          foreach (var visitor in visitorList) {
            visitor.visit(node);
            incVisitorDepth(visitor);
          }

          clearStoppedVisitors();
          if(needPreorderStop)
            return;

          visitAllEdges(node, true);

          foreach (var visitor in visitorList) {
            decVisitorDepth(visitor);
            visitor.visitEnd(node);
          }

          clearStoppedVisitors();
        }

        /// <summary>
        /// It call the traversal for the edges
        /// </summary>
        /// <param name="node">[in] The node with own type</param>
        /// <param name="callVirtualBase">[in] This paramater is don't used just api copatibility used.</param>
        public void visitAllEdges(Columbus.Csharp.Asg.Nodes.Statement.ThrowStatementSyntax node, bool callFirst = true){
            visitAllEdges((Columbus.Csharp.Asg.Nodes.Statement.StatementSyntax)(node),false);


            Columbus.Csharp.Asg.Nodes.Base.Base genNodePtr;
            // edge: Expression
            genNodePtr = fact.getRef(node.getExpression()) ;
            if (genNodePtr != null) {
              Columbus.Csharp.Asg.Nodes.Expression.ExpressionSyntax endNodeRef = (Columbus.Csharp.Asg.Nodes.Expression.ExpressionSyntax)(genNodePtr);
              foreach (var visitor in visitorList) {
                visitor.visitThrowStatementSyntax_Expression(node.Id, endNodeRef.Id);
              }

              clearStoppedVisitors();
              if(needPreorderStop)
                return;

              if ((!fact.IsFilterTurnedOn && !visitFilteredEdge) || (fact.getFilterState(endNodeRef.Id) == Filter.FilterState.NotFiltered) || (!originalFilterState && visitFilteredEdge)) {
                  endNodeRef.accept(this);
              }
              foreach (var visitor in visitorList) {
                visitor.visitEndThrowStatementSyntax_Expression(node.Id, endNodeRef.Id);
              }

              clearStoppedVisitors();
              if(needPreorderStop)
                return;

            }
        }

        public override void visit(Columbus.Csharp.Asg.Nodes.Statement.ThrowStatementSyntax node, bool callFirst = true){
          if (safeMode || visitCrossEdgeTree) {
            if (safeMode) {
              if (visitedNodes[(int)node.Id]) { // for safemode
                return;
              }
            }
            visitedNodes[(int)node.Id] = true;
          }

          foreach (var visitor in visitorList) {
            visitor.visit(node);
            incVisitorDepth(visitor);
          }

          clearStoppedVisitors();
          if(needPreorderStop)
            return;

          visitAllEdges(node, true);

          foreach (var visitor in visitorList) {
            decVisitorDepth(visitor);
            visitor.visitEnd(node);
          }

          clearStoppedVisitors();
        }

        /// <summary>
        /// It call the traversal for the edges
        /// </summary>
        /// <param name="node">[in] The node with own type</param>
        /// <param name="callVirtualBase">[in] This paramater is don't used just api copatibility used.</param>
        public void visitAllEdges(Columbus.Csharp.Asg.Nodes.Statement.TryStatementSyntax node, bool callFirst = true){
            visitAllEdges((Columbus.Csharp.Asg.Nodes.Statement.StatementSyntax)(node),false);


            Columbus.Csharp.Asg.Nodes.Base.Base genNodePtr;
            // edge: Block
            genNodePtr = fact.getRef(node.getBlock()) ;
            if (genNodePtr != null) {
              Columbus.Csharp.Asg.Nodes.Statement.BlockSyntax endNodeRef = (Columbus.Csharp.Asg.Nodes.Statement.BlockSyntax)(genNodePtr);
              foreach (var visitor in visitorList) {
                visitor.visitTryStatementSyntax_Block(node.Id, endNodeRef.Id);
              }

              clearStoppedVisitors();
              if(needPreorderStop)
                return;

              if ((!fact.IsFilterTurnedOn && !visitFilteredEdge) || (fact.getFilterState(endNodeRef.Id) == Filter.FilterState.NotFiltered) || (!originalFilterState && visitFilteredEdge)) {
                  endNodeRef.accept(this);
              }
              foreach (var visitor in visitorList) {
                visitor.visitEndTryStatementSyntax_Block(node.Id, endNodeRef.Id);
              }

              clearStoppedVisitors();
              if(needPreorderStop)
                return;

            }

            // edge: Catches
            ListIterator<Columbus.Csharp.Asg.Nodes.Structure.CatchClauseSyntax> iteratorForCatches = node.CatchesListIteratorBegin;
            while (iteratorForCatches.getValue() != null) {
               Columbus.Csharp.Asg.Nodes.Structure.CatchClauseSyntax endNodeRef = (Columbus.Csharp.Asg.Nodes.Structure.CatchClauseSyntax)iteratorForCatches.getValue();
              foreach (var visitor in visitorList) {
                visitor.visitTryStatementSyntax_Catches(node.Id, endNodeRef.Id);
              }

              clearStoppedVisitors();
              if(needPreorderStop)
                return;

              if ((!fact.IsFilterTurnedOn && !visitFilteredEdge) || (fact.getFilterState(endNodeRef.Id) == Filter.FilterState.NotFiltered) || (!originalFilterState && visitFilteredEdge)) {
                  endNodeRef.accept(this);
              }
              foreach (var visitor in visitorList) {
                visitor.visitEndTryStatementSyntax_Catches(node.Id, endNodeRef.Id);
              }

              clearStoppedVisitors();
              if(needPreorderStop)
                return;

            iteratorForCatches = iteratorForCatches.getNext();
            }

            // edge: Finally
            genNodePtr = fact.getRef(node.getFinally()) ;
            if (genNodePtr != null) {
              Columbus.Csharp.Asg.Nodes.Structure.FinallyClauseSyntax endNodeRef = (Columbus.Csharp.Asg.Nodes.Structure.FinallyClauseSyntax)(genNodePtr);
              foreach (var visitor in visitorList) {
                visitor.visitTryStatementSyntax_Finally(node.Id, endNodeRef.Id);
              }

              clearStoppedVisitors();
              if(needPreorderStop)
                return;

              if ((!fact.IsFilterTurnedOn && !visitFilteredEdge) || (fact.getFilterState(endNodeRef.Id) == Filter.FilterState.NotFiltered) || (!originalFilterState && visitFilteredEdge)) {
                  endNodeRef.accept(this);
              }
              foreach (var visitor in visitorList) {
                visitor.visitEndTryStatementSyntax_Finally(node.Id, endNodeRef.Id);
              }

              clearStoppedVisitors();
              if(needPreorderStop)
                return;

            }
        }

        public override void visit(Columbus.Csharp.Asg.Nodes.Statement.TryStatementSyntax node, bool callFirst = true){
          if (safeMode || visitCrossEdgeTree) {
            if (safeMode) {
              if (visitedNodes[(int)node.Id]) { // for safemode
                return;
              }
            }
            visitedNodes[(int)node.Id] = true;
          }

          foreach (var visitor in visitorList) {
            visitor.visit(node);
            incVisitorDepth(visitor);
          }

          clearStoppedVisitors();
          if(needPreorderStop)
            return;

          visitAllEdges(node, true);

          foreach (var visitor in visitorList) {
            decVisitorDepth(visitor);
            visitor.visitEnd(node);
          }

          clearStoppedVisitors();
        }

        /// <summary>
        /// It call the traversal for the edges
        /// </summary>
        /// <param name="node">[in] The node with own type</param>
        /// <param name="callVirtualBase">[in] This paramater is don't used just api copatibility used.</param>
        public void visitAllEdges(Columbus.Csharp.Asg.Nodes.Statement.UnsafeStatementSyntax node, bool callFirst = true){
            visitAllEdges((Columbus.Csharp.Asg.Nodes.Statement.StatementSyntax)(node),false);


            Columbus.Csharp.Asg.Nodes.Base.Base genNodePtr;
            // edge: Block
            genNodePtr = fact.getRef(node.getBlock()) ;
            if (genNodePtr != null) {
              Columbus.Csharp.Asg.Nodes.Statement.BlockSyntax endNodeRef = (Columbus.Csharp.Asg.Nodes.Statement.BlockSyntax)(genNodePtr);
              foreach (var visitor in visitorList) {
                visitor.visitUnsafeStatementSyntax_Block(node.Id, endNodeRef.Id);
              }

              clearStoppedVisitors();
              if(needPreorderStop)
                return;

              if ((!fact.IsFilterTurnedOn && !visitFilteredEdge) || (fact.getFilterState(endNodeRef.Id) == Filter.FilterState.NotFiltered) || (!originalFilterState && visitFilteredEdge)) {
                  endNodeRef.accept(this);
              }
              foreach (var visitor in visitorList) {
                visitor.visitEndUnsafeStatementSyntax_Block(node.Id, endNodeRef.Id);
              }

              clearStoppedVisitors();
              if(needPreorderStop)
                return;

            }
        }

        public override void visit(Columbus.Csharp.Asg.Nodes.Statement.UnsafeStatementSyntax node, bool callFirst = true){
          if (safeMode || visitCrossEdgeTree) {
            if (safeMode) {
              if (visitedNodes[(int)node.Id]) { // for safemode
                return;
              }
            }
            visitedNodes[(int)node.Id] = true;
          }

          foreach (var visitor in visitorList) {
            visitor.visit(node);
            incVisitorDepth(visitor);
          }

          clearStoppedVisitors();
          if(needPreorderStop)
            return;

          visitAllEdges(node, true);

          foreach (var visitor in visitorList) {
            decVisitorDepth(visitor);
            visitor.visitEnd(node);
          }

          clearStoppedVisitors();
        }

        /// <summary>
        /// It call the traversal for the edges
        /// </summary>
        /// <param name="node">[in] The node with own type</param>
        /// <param name="callVirtualBase">[in] This paramater is don't used just api copatibility used.</param>
        public void visitAllEdges(Columbus.Csharp.Asg.Nodes.Statement.UsingStatementSyntax node, bool callFirst = true){
            visitAllEdges((Columbus.Csharp.Asg.Nodes.Statement.StatementSyntax)(node),false);


            Columbus.Csharp.Asg.Nodes.Base.Base genNodePtr;
            // edge: Declaration
            genNodePtr = fact.getRef(node.getDeclaration()) ;
            if (genNodePtr != null) {
              Columbus.Csharp.Asg.Nodes.Structure.VariableDeclarationSyntax endNodeRef = (Columbus.Csharp.Asg.Nodes.Structure.VariableDeclarationSyntax)(genNodePtr);
              foreach (var visitor in visitorList) {
                visitor.visitUsingStatementSyntax_Declaration(node.Id, endNodeRef.Id);
              }

              clearStoppedVisitors();
              if(needPreorderStop)
                return;

              if ((!fact.IsFilterTurnedOn && !visitFilteredEdge) || (fact.getFilterState(endNodeRef.Id) == Filter.FilterState.NotFiltered) || (!originalFilterState && visitFilteredEdge)) {
                  endNodeRef.accept(this);
              }
              foreach (var visitor in visitorList) {
                visitor.visitEndUsingStatementSyntax_Declaration(node.Id, endNodeRef.Id);
              }

              clearStoppedVisitors();
              if(needPreorderStop)
                return;

            }

            // edge: Expression
            genNodePtr = fact.getRef(node.getExpression()) ;
            if (genNodePtr != null) {
              Columbus.Csharp.Asg.Nodes.Expression.ExpressionSyntax endNodeRef = (Columbus.Csharp.Asg.Nodes.Expression.ExpressionSyntax)(genNodePtr);
              foreach (var visitor in visitorList) {
                visitor.visitUsingStatementSyntax_Expression(node.Id, endNodeRef.Id);
              }

              clearStoppedVisitors();
              if(needPreorderStop)
                return;

              if ((!fact.IsFilterTurnedOn && !visitFilteredEdge) || (fact.getFilterState(endNodeRef.Id) == Filter.FilterState.NotFiltered) || (!originalFilterState && visitFilteredEdge)) {
                  endNodeRef.accept(this);
              }
              foreach (var visitor in visitorList) {
                visitor.visitEndUsingStatementSyntax_Expression(node.Id, endNodeRef.Id);
              }

              clearStoppedVisitors();
              if(needPreorderStop)
                return;

            }

            // edge: Statement
            genNodePtr = fact.getRef(node.getStatement()) ;
            if (genNodePtr != null) {
              Columbus.Csharp.Asg.Nodes.Statement.StatementSyntax endNodeRef = (Columbus.Csharp.Asg.Nodes.Statement.StatementSyntax)(genNodePtr);
              foreach (var visitor in visitorList) {
                visitor.visitUsingStatementSyntax_Statement(node.Id, endNodeRef.Id);
              }

              clearStoppedVisitors();
              if(needPreorderStop)
                return;

              if ((!fact.IsFilterTurnedOn && !visitFilteredEdge) || (fact.getFilterState(endNodeRef.Id) == Filter.FilterState.NotFiltered) || (!originalFilterState && visitFilteredEdge)) {
                  endNodeRef.accept(this);
              }
              foreach (var visitor in visitorList) {
                visitor.visitEndUsingStatementSyntax_Statement(node.Id, endNodeRef.Id);
              }

              clearStoppedVisitors();
              if(needPreorderStop)
                return;

            }
        }

        public override void visit(Columbus.Csharp.Asg.Nodes.Statement.UsingStatementSyntax node, bool callFirst = true){
          if (safeMode || visitCrossEdgeTree) {
            if (safeMode) {
              if (visitedNodes[(int)node.Id]) { // for safemode
                return;
              }
            }
            visitedNodes[(int)node.Id] = true;
          }

          foreach (var visitor in visitorList) {
            visitor.visit(node);
            incVisitorDepth(visitor);
          }

          clearStoppedVisitors();
          if(needPreorderStop)
            return;

          visitAllEdges(node, true);

          foreach (var visitor in visitorList) {
            decVisitorDepth(visitor);
            visitor.visitEnd(node);
          }

          clearStoppedVisitors();
        }

        /// <summary>
        /// It call the traversal for the edges
        /// </summary>
        /// <param name="node">[in] The node with own type</param>
        /// <param name="callVirtualBase">[in] This paramater is don't used just api copatibility used.</param>
        public void visitAllEdges(Columbus.Csharp.Asg.Nodes.Statement.WhileStatementSyntax node, bool callFirst = true){
            visitAllEdges((Columbus.Csharp.Asg.Nodes.Statement.StatementSyntax)(node),false);


            Columbus.Csharp.Asg.Nodes.Base.Base genNodePtr;
            // edge: Condition
            genNodePtr = fact.getRef(node.getCondition()) ;
            if (genNodePtr != null) {
              Columbus.Csharp.Asg.Nodes.Expression.ExpressionSyntax endNodeRef = (Columbus.Csharp.Asg.Nodes.Expression.ExpressionSyntax)(genNodePtr);
              foreach (var visitor in visitorList) {
                visitor.visitWhileStatementSyntax_Condition(node.Id, endNodeRef.Id);
              }

              clearStoppedVisitors();
              if(needPreorderStop)
                return;

              if ((!fact.IsFilterTurnedOn && !visitFilteredEdge) || (fact.getFilterState(endNodeRef.Id) == Filter.FilterState.NotFiltered) || (!originalFilterState && visitFilteredEdge)) {
                  endNodeRef.accept(this);
              }
              foreach (var visitor in visitorList) {
                visitor.visitEndWhileStatementSyntax_Condition(node.Id, endNodeRef.Id);
              }

              clearStoppedVisitors();
              if(needPreorderStop)
                return;

            }

            // edge: Statement
            genNodePtr = fact.getRef(node.getStatement()) ;
            if (genNodePtr != null) {
              Columbus.Csharp.Asg.Nodes.Statement.StatementSyntax endNodeRef = (Columbus.Csharp.Asg.Nodes.Statement.StatementSyntax)(genNodePtr);
              foreach (var visitor in visitorList) {
                visitor.visitWhileStatementSyntax_Statement(node.Id, endNodeRef.Id);
              }

              clearStoppedVisitors();
              if(needPreorderStop)
                return;

              if ((!fact.IsFilterTurnedOn && !visitFilteredEdge) || (fact.getFilterState(endNodeRef.Id) == Filter.FilterState.NotFiltered) || (!originalFilterState && visitFilteredEdge)) {
                  endNodeRef.accept(this);
              }
              foreach (var visitor in visitorList) {
                visitor.visitEndWhileStatementSyntax_Statement(node.Id, endNodeRef.Id);
              }

              clearStoppedVisitors();
              if(needPreorderStop)
                return;

            }
        }

        public override void visit(Columbus.Csharp.Asg.Nodes.Statement.WhileStatementSyntax node, bool callFirst = true){
          if (safeMode || visitCrossEdgeTree) {
            if (safeMode) {
              if (visitedNodes[(int)node.Id]) { // for safemode
                return;
              }
            }
            visitedNodes[(int)node.Id] = true;
          }

          foreach (var visitor in visitorList) {
            visitor.visit(node);
            incVisitorDepth(visitor);
          }

          clearStoppedVisitors();
          if(needPreorderStop)
            return;

          visitAllEdges(node, true);

          foreach (var visitor in visitorList) {
            decVisitorDepth(visitor);
            visitor.visitEnd(node);
          }

          clearStoppedVisitors();
        }

        /// <summary>
        /// It call the traversal for the edges
        /// </summary>
        /// <param name="node">[in] The node with own type</param>
        /// <param name="callVirtualBase">[in] This paramater is don't used just api copatibility used.</param>
        public void visitAllEdges(Columbus.Csharp.Asg.Nodes.Statement.YieldStatementSyntax node, bool callFirst = true){
            visitAllEdges((Columbus.Csharp.Asg.Nodes.Statement.StatementSyntax)(node),false);


            Columbus.Csharp.Asg.Nodes.Base.Base genNodePtr;
            // edge: Expression
            genNodePtr = fact.getRef(node.getExpression()) ;
            if (genNodePtr != null) {
              Columbus.Csharp.Asg.Nodes.Expression.ExpressionSyntax endNodeRef = (Columbus.Csharp.Asg.Nodes.Expression.ExpressionSyntax)(genNodePtr);
              foreach (var visitor in visitorList) {
                visitor.visitYieldStatementSyntax_Expression(node.Id, endNodeRef.Id);
              }

              clearStoppedVisitors();
              if(needPreorderStop)
                return;

              if ((!fact.IsFilterTurnedOn && !visitFilteredEdge) || (fact.getFilterState(endNodeRef.Id) == Filter.FilterState.NotFiltered) || (!originalFilterState && visitFilteredEdge)) {
                  endNodeRef.accept(this);
              }
              foreach (var visitor in visitorList) {
                visitor.visitEndYieldStatementSyntax_Expression(node.Id, endNodeRef.Id);
              }

              clearStoppedVisitors();
              if(needPreorderStop)
                return;

            }
        }

        public override void visit(Columbus.Csharp.Asg.Nodes.Statement.YieldStatementSyntax node, bool callFirst = true){
          if (safeMode || visitCrossEdgeTree) {
            if (safeMode) {
              if (visitedNodes[(int)node.Id]) { // for safemode
                return;
              }
            }
            visitedNodes[(int)node.Id] = true;
          }

          foreach (var visitor in visitorList) {
            visitor.visit(node);
            incVisitorDepth(visitor);
          }

          clearStoppedVisitors();
          if(needPreorderStop)
            return;

          visitAllEdges(node, true);

          foreach (var visitor in visitorList) {
            decVisitorDepth(visitor);
            visitor.visitEnd(node);
          }

          clearStoppedVisitors();
        }

        /// <summary>
        /// It call the traversal for the edges
        /// </summary>
        /// <param name="node">[in] The node with own type</param>
        /// <param name="callVirtualBase">[in] This paramater is don't used just api copatibility used.</param>
        public void visitAllEdges(Columbus.Csharp.Asg.Nodes.Structure.AccessorDeclarationSyntax node, bool callFirst = true){
            visitAllEdges((Columbus.Csharp.Asg.Nodes.Base.Positioned)(node),false);


            // edge: AttributeLists
            ListIterator<Columbus.Csharp.Asg.Nodes.Structure.AttributeListSyntax> iteratorForAttributeLists = node.AttributeListsListIteratorBegin;
            while (iteratorForAttributeLists.getValue() != null) {
               Columbus.Csharp.Asg.Nodes.Structure.AttributeListSyntax endNodeRef = (Columbus.Csharp.Asg.Nodes.Structure.AttributeListSyntax)iteratorForAttributeLists.getValue();
              foreach (var visitor in visitorList) {
                visitor.visitAccessorDeclarationSyntax_AttributeLists(node.Id, endNodeRef.Id);
              }

              clearStoppedVisitors();
              if(needPreorderStop)
                return;

              if ((!fact.IsFilterTurnedOn && !visitFilteredEdge) || (fact.getFilterState(endNodeRef.Id) == Filter.FilterState.NotFiltered) || (!originalFilterState && visitFilteredEdge)) {
                  endNodeRef.accept(this);
              }
              foreach (var visitor in visitorList) {
                visitor.visitEndAccessorDeclarationSyntax_AttributeLists(node.Id, endNodeRef.Id);
              }

              clearStoppedVisitors();
              if(needPreorderStop)
                return;

            iteratorForAttributeLists = iteratorForAttributeLists.getNext();
            }

            Columbus.Csharp.Asg.Nodes.Base.Base genNodePtr;
            // edge: Body
            genNodePtr = fact.getRef(node.getBody()) ;
            if (genNodePtr != null) {
              Columbus.Csharp.Asg.Nodes.Statement.BlockSyntax endNodeRef = (Columbus.Csharp.Asg.Nodes.Statement.BlockSyntax)(genNodePtr);
              foreach (var visitor in visitorList) {
                visitor.visitAccessorDeclarationSyntax_Body(node.Id, endNodeRef.Id);
              }

              clearStoppedVisitors();
              if(needPreorderStop)
                return;

              if ((!fact.IsFilterTurnedOn && !visitFilteredEdge) || (fact.getFilterState(endNodeRef.Id) == Filter.FilterState.NotFiltered) || (!originalFilterState && visitFilteredEdge)) {
                  endNodeRef.accept(this);
              }
              foreach (var visitor in visitorList) {
                visitor.visitEndAccessorDeclarationSyntax_Body(node.Id, endNodeRef.Id);
              }

              clearStoppedVisitors();
              if(needPreorderStop)
                return;

            }

            // edge: ExpressionBody
            genNodePtr = fact.getRef(node.getExpressionBody()) ;
            if (genNodePtr != null) {
              Columbus.Csharp.Asg.Nodes.Structure.ArrowExpressionClauseSyntax endNodeRef = (Columbus.Csharp.Asg.Nodes.Structure.ArrowExpressionClauseSyntax)(genNodePtr);
              foreach (var visitor in visitorList) {
                visitor.visitAccessorDeclarationSyntax_ExpressionBody(node.Id, endNodeRef.Id);
              }

              clearStoppedVisitors();
              if(needPreorderStop)
                return;

              if ((!fact.IsFilterTurnedOn && !visitFilteredEdge) || (fact.getFilterState(endNodeRef.Id) == Filter.FilterState.NotFiltered) || (!originalFilterState && visitFilteredEdge)) {
                  endNodeRef.accept(this);
              }
              foreach (var visitor in visitorList) {
                visitor.visitEndAccessorDeclarationSyntax_ExpressionBody(node.Id, endNodeRef.Id);
              }

              clearStoppedVisitors();
              if(needPreorderStop)
                return;

            }
        }

        public override void visit(Columbus.Csharp.Asg.Nodes.Structure.AccessorDeclarationSyntax node, bool callFirst = true){
          if (safeMode || visitCrossEdgeTree) {
            if (safeMode) {
              if (visitedNodes[(int)node.Id]) { // for safemode
                return;
              }
            }
            visitedNodes[(int)node.Id] = true;
          }

          foreach (var visitor in visitorList) {
            visitor.visit(node);
            incVisitorDepth(visitor);
          }

          clearStoppedVisitors();
          if(needPreorderStop)
            return;

          visitAllEdges(node, true);

          foreach (var visitor in visitorList) {
            decVisitorDepth(visitor);
            visitor.visitEnd(node);
          }

          clearStoppedVisitors();
        }

        /// <summary>
        /// It call the traversal for the edges
        /// </summary>
        /// <param name="node">[in] The node with own type</param>
        /// <param name="callVirtualBase">[in] This paramater is don't used just api copatibility used.</param>
        public void visitAllEdges(Columbus.Csharp.Asg.Nodes.Structure.AccessorListSyntax node, bool callFirst = true){
            visitAllEdges((Columbus.Csharp.Asg.Nodes.Base.Positioned)(node),false);


            // edge: Accessors
            ListIterator<Columbus.Csharp.Asg.Nodes.Structure.AccessorDeclarationSyntax> iteratorForAccessors = node.AccessorsListIteratorBegin;
            while (iteratorForAccessors.getValue() != null) {
               Columbus.Csharp.Asg.Nodes.Structure.AccessorDeclarationSyntax endNodeRef = (Columbus.Csharp.Asg.Nodes.Structure.AccessorDeclarationSyntax)iteratorForAccessors.getValue();
              foreach (var visitor in visitorList) {
                visitor.visitAccessorListSyntax_Accessors(node.Id, endNodeRef.Id);
              }

              clearStoppedVisitors();
              if(needPreorderStop)
                return;

              if ((!fact.IsFilterTurnedOn && !visitFilteredEdge) || (fact.getFilterState(endNodeRef.Id) == Filter.FilterState.NotFiltered) || (!originalFilterState && visitFilteredEdge)) {
                  endNodeRef.accept(this);
              }
              foreach (var visitor in visitorList) {
                visitor.visitEndAccessorListSyntax_Accessors(node.Id, endNodeRef.Id);
              }

              clearStoppedVisitors();
              if(needPreorderStop)
                return;

            iteratorForAccessors = iteratorForAccessors.getNext();
            }
        }

        public override void visit(Columbus.Csharp.Asg.Nodes.Structure.AccessorListSyntax node, bool callFirst = true){
          if (safeMode || visitCrossEdgeTree) {
            if (safeMode) {
              if (visitedNodes[(int)node.Id]) { // for safemode
                return;
              }
            }
            visitedNodes[(int)node.Id] = true;
          }

          foreach (var visitor in visitorList) {
            visitor.visit(node);
            incVisitorDepth(visitor);
          }

          clearStoppedVisitors();
          if(needPreorderStop)
            return;

          visitAllEdges(node, true);

          foreach (var visitor in visitorList) {
            decVisitorDepth(visitor);
            visitor.visitEnd(node);
          }

          clearStoppedVisitors();
        }

        /// <summary>
        /// It call the traversal for the edges
        /// </summary>
        /// <param name="node">[in] The node with own type</param>
        /// <param name="callVirtualBase">[in] This paramater is don't used just api copatibility used.</param>
        public void visitAllEdges(Columbus.Csharp.Asg.Nodes.Structure.AnonymousObjectMemberDeclaratorSyntax node, bool callFirst = true){
            visitAllEdges((Columbus.Csharp.Asg.Nodes.Base.Positioned)(node),false);


            Columbus.Csharp.Asg.Nodes.Base.Base genNodePtr;
            // edge: Expression
            genNodePtr = fact.getRef(node.getExpression()) ;
            if (genNodePtr != null) {
              Columbus.Csharp.Asg.Nodes.Expression.ExpressionSyntax endNodeRef = (Columbus.Csharp.Asg.Nodes.Expression.ExpressionSyntax)(genNodePtr);
              foreach (var visitor in visitorList) {
                visitor.visitAnonymousObjectMemberDeclaratorSyntax_Expression(node.Id, endNodeRef.Id);
              }

              clearStoppedVisitors();
              if(needPreorderStop)
                return;

              if ((!fact.IsFilterTurnedOn && !visitFilteredEdge) || (fact.getFilterState(endNodeRef.Id) == Filter.FilterState.NotFiltered) || (!originalFilterState && visitFilteredEdge)) {
                  endNodeRef.accept(this);
              }
              foreach (var visitor in visitorList) {
                visitor.visitEndAnonymousObjectMemberDeclaratorSyntax_Expression(node.Id, endNodeRef.Id);
              }

              clearStoppedVisitors();
              if(needPreorderStop)
                return;

            }

            // edge: NameEquals
            genNodePtr = fact.getRef(node.getNameEquals()) ;
            if (genNodePtr != null) {
              Columbus.Csharp.Asg.Nodes.Structure.NameEqualsSyntax endNodeRef = (Columbus.Csharp.Asg.Nodes.Structure.NameEqualsSyntax)(genNodePtr);
              foreach (var visitor in visitorList) {
                visitor.visitAnonymousObjectMemberDeclaratorSyntax_NameEquals(node.Id, endNodeRef.Id);
              }

              clearStoppedVisitors();
              if(needPreorderStop)
                return;

              if ((!fact.IsFilterTurnedOn && !visitFilteredEdge) || (fact.getFilterState(endNodeRef.Id) == Filter.FilterState.NotFiltered) || (!originalFilterState && visitFilteredEdge)) {
                  endNodeRef.accept(this);
              }
              foreach (var visitor in visitorList) {
                visitor.visitEndAnonymousObjectMemberDeclaratorSyntax_NameEquals(node.Id, endNodeRef.Id);
              }

              clearStoppedVisitors();
              if(needPreorderStop)
                return;

            }
        }

        public override void visit(Columbus.Csharp.Asg.Nodes.Structure.AnonymousObjectMemberDeclaratorSyntax node, bool callFirst = true){
          if (safeMode || visitCrossEdgeTree) {
            if (safeMode) {
              if (visitedNodes[(int)node.Id]) { // for safemode
                return;
              }
            }
            visitedNodes[(int)node.Id] = true;
          }

          foreach (var visitor in visitorList) {
            visitor.visit(node);
            incVisitorDepth(visitor);
          }

          clearStoppedVisitors();
          if(needPreorderStop)
            return;

          visitAllEdges(node, true);

          foreach (var visitor in visitorList) {
            decVisitorDepth(visitor);
            visitor.visitEnd(node);
          }

          clearStoppedVisitors();
        }

        /// <summary>
        /// It call the traversal for the edges
        /// </summary>
        /// <param name="node">[in] The node with own type</param>
        /// <param name="callVirtualBase">[in] This paramater is don't used just api copatibility used.</param>
        public void visitAllEdges(Columbus.Csharp.Asg.Nodes.Structure.ArgumentListSyntax node, bool callFirst = true){
            visitAllEdges((Columbus.Csharp.Asg.Nodes.Structure.BaseArgumentListSyntax)(node),false);
        }

        public override void visit(Columbus.Csharp.Asg.Nodes.Structure.ArgumentListSyntax node, bool callFirst = true){
          if (safeMode || visitCrossEdgeTree) {
            if (safeMode) {
              if (visitedNodes[(int)node.Id]) { // for safemode
                return;
              }
            }
            visitedNodes[(int)node.Id] = true;
          }

          foreach (var visitor in visitorList) {
            visitor.visit(node);
            incVisitorDepth(visitor);
          }

          clearStoppedVisitors();
          if(needPreorderStop)
            return;

          visitAllEdges(node, true);

          foreach (var visitor in visitorList) {
            decVisitorDepth(visitor);
            visitor.visitEnd(node);
          }

          clearStoppedVisitors();
        }

        /// <summary>
        /// It call the traversal for the edges
        /// </summary>
        /// <param name="node">[in] The node with own type</param>
        /// <param name="callVirtualBase">[in] This paramater is don't used just api copatibility used.</param>
        public void visitAllEdges(Columbus.Csharp.Asg.Nodes.Structure.ArgumentSyntax node, bool callFirst = true){
            visitAllEdges((Columbus.Csharp.Asg.Nodes.Base.Positioned)(node),false);


            Columbus.Csharp.Asg.Nodes.Base.Base genNodePtr;
            // edge: Expression
            genNodePtr = fact.getRef(node.getExpression()) ;
            if (genNodePtr != null) {
              Columbus.Csharp.Asg.Nodes.Expression.ExpressionSyntax endNodeRef = (Columbus.Csharp.Asg.Nodes.Expression.ExpressionSyntax)(genNodePtr);
              foreach (var visitor in visitorList) {
                visitor.visitArgumentSyntax_Expression(node.Id, endNodeRef.Id);
              }

              clearStoppedVisitors();
              if(needPreorderStop)
                return;

              if ((!fact.IsFilterTurnedOn && !visitFilteredEdge) || (fact.getFilterState(endNodeRef.Id) == Filter.FilterState.NotFiltered) || (!originalFilterState && visitFilteredEdge)) {
                  endNodeRef.accept(this);
              }
              foreach (var visitor in visitorList) {
                visitor.visitEndArgumentSyntax_Expression(node.Id, endNodeRef.Id);
              }

              clearStoppedVisitors();
              if(needPreorderStop)
                return;

            }

            // edge: NameColon
            genNodePtr = fact.getRef(node.getNameColon()) ;
            if (genNodePtr != null) {
              Columbus.Csharp.Asg.Nodes.Structure.NameColonSyntax endNodeRef = (Columbus.Csharp.Asg.Nodes.Structure.NameColonSyntax)(genNodePtr);
              foreach (var visitor in visitorList) {
                visitor.visitArgumentSyntax_NameColon(node.Id, endNodeRef.Id);
              }

              clearStoppedVisitors();
              if(needPreorderStop)
                return;

              if ((!fact.IsFilterTurnedOn && !visitFilteredEdge) || (fact.getFilterState(endNodeRef.Id) == Filter.FilterState.NotFiltered) || (!originalFilterState && visitFilteredEdge)) {
                  endNodeRef.accept(this);
              }
              foreach (var visitor in visitorList) {
                visitor.visitEndArgumentSyntax_NameColon(node.Id, endNodeRef.Id);
              }

              clearStoppedVisitors();
              if(needPreorderStop)
                return;

            }
        }

        public override void visit(Columbus.Csharp.Asg.Nodes.Structure.ArgumentSyntax node, bool callFirst = true){
          if (safeMode || visitCrossEdgeTree) {
            if (safeMode) {
              if (visitedNodes[(int)node.Id]) { // for safemode
                return;
              }
            }
            visitedNodes[(int)node.Id] = true;
          }

          foreach (var visitor in visitorList) {
            visitor.visit(node);
            incVisitorDepth(visitor);
          }

          clearStoppedVisitors();
          if(needPreorderStop)
            return;

          visitAllEdges(node, true);

          foreach (var visitor in visitorList) {
            decVisitorDepth(visitor);
            visitor.visitEnd(node);
          }

          clearStoppedVisitors();
        }

        /// <summary>
        /// It call the traversal for the edges
        /// </summary>
        /// <param name="node">[in] The node with own type</param>
        /// <param name="callVirtualBase">[in] This paramater is don't used just api copatibility used.</param>
        public void visitAllEdges(Columbus.Csharp.Asg.Nodes.Structure.ArrayRankSpecifierSyntax node, bool callFirst = true){
            visitAllEdges((Columbus.Csharp.Asg.Nodes.Base.Positioned)(node),false);


            // edge: Sizes
            ListIterator<Columbus.Csharp.Asg.Nodes.Expression.ExpressionSyntax> iteratorForSizes = node.SizesListIteratorBegin;
            while (iteratorForSizes.getValue() != null) {
               Columbus.Csharp.Asg.Nodes.Expression.ExpressionSyntax endNodeRef = (Columbus.Csharp.Asg.Nodes.Expression.ExpressionSyntax)iteratorForSizes.getValue();
              foreach (var visitor in visitorList) {
                visitor.visitArrayRankSpecifierSyntax_Sizes(node.Id, endNodeRef.Id);
              }

              clearStoppedVisitors();
              if(needPreorderStop)
                return;

              if ((!fact.IsFilterTurnedOn && !visitFilteredEdge) || (fact.getFilterState(endNodeRef.Id) == Filter.FilterState.NotFiltered) || (!originalFilterState && visitFilteredEdge)) {
                  endNodeRef.accept(this);
              }
              foreach (var visitor in visitorList) {
                visitor.visitEndArrayRankSpecifierSyntax_Sizes(node.Id, endNodeRef.Id);
              }

              clearStoppedVisitors();
              if(needPreorderStop)
                return;

            iteratorForSizes = iteratorForSizes.getNext();
            }
        }

        public override void visit(Columbus.Csharp.Asg.Nodes.Structure.ArrayRankSpecifierSyntax node, bool callFirst = true){
          if (safeMode || visitCrossEdgeTree) {
            if (safeMode) {
              if (visitedNodes[(int)node.Id]) { // for safemode
                return;
              }
            }
            visitedNodes[(int)node.Id] = true;
          }

          foreach (var visitor in visitorList) {
            visitor.visit(node);
            incVisitorDepth(visitor);
          }

          clearStoppedVisitors();
          if(needPreorderStop)
            return;

          visitAllEdges(node, true);

          foreach (var visitor in visitorList) {
            decVisitorDepth(visitor);
            visitor.visitEnd(node);
          }

          clearStoppedVisitors();
        }

        /// <summary>
        /// It call the traversal for the edges
        /// </summary>
        /// <param name="node">[in] The node with own type</param>
        /// <param name="callVirtualBase">[in] This paramater is don't used just api copatibility used.</param>
        public void visitAllEdges(Columbus.Csharp.Asg.Nodes.Structure.ArrowExpressionClauseSyntax node, bool callFirst = true){
            visitAllEdges((Columbus.Csharp.Asg.Nodes.Base.Positioned)(node),false);


            Columbus.Csharp.Asg.Nodes.Base.Base genNodePtr;
            // edge: Expression
            genNodePtr = fact.getRef(node.getExpression()) ;
            if (genNodePtr != null) {
              Columbus.Csharp.Asg.Nodes.Expression.ExpressionSyntax endNodeRef = (Columbus.Csharp.Asg.Nodes.Expression.ExpressionSyntax)(genNodePtr);
              foreach (var visitor in visitorList) {
                visitor.visitArrowExpressionClauseSyntax_Expression(node.Id, endNodeRef.Id);
              }

              clearStoppedVisitors();
              if(needPreorderStop)
                return;

              if ((!fact.IsFilterTurnedOn && !visitFilteredEdge) || (fact.getFilterState(endNodeRef.Id) == Filter.FilterState.NotFiltered) || (!originalFilterState && visitFilteredEdge)) {
                  endNodeRef.accept(this);
              }
              foreach (var visitor in visitorList) {
                visitor.visitEndArrowExpressionClauseSyntax_Expression(node.Id, endNodeRef.Id);
              }

              clearStoppedVisitors();
              if(needPreorderStop)
                return;

            }
        }

        public override void visit(Columbus.Csharp.Asg.Nodes.Structure.ArrowExpressionClauseSyntax node, bool callFirst = true){
          if (safeMode || visitCrossEdgeTree) {
            if (safeMode) {
              if (visitedNodes[(int)node.Id]) { // for safemode
                return;
              }
            }
            visitedNodes[(int)node.Id] = true;
          }

          foreach (var visitor in visitorList) {
            visitor.visit(node);
            incVisitorDepth(visitor);
          }

          clearStoppedVisitors();
          if(needPreorderStop)
            return;

          visitAllEdges(node, true);

          foreach (var visitor in visitorList) {
            decVisitorDepth(visitor);
            visitor.visitEnd(node);
          }

          clearStoppedVisitors();
        }

        /// <summary>
        /// It call the traversal for the edges
        /// </summary>
        /// <param name="node">[in] The node with own type</param>
        /// <param name="callVirtualBase">[in] This paramater is don't used just api copatibility used.</param>
        public void visitAllEdges(Columbus.Csharp.Asg.Nodes.Structure.AttributeArgumentListSyntax node, bool callFirst = true){
            visitAllEdges((Columbus.Csharp.Asg.Nodes.Base.Positioned)(node),false);


            // edge: Arguments
            ListIterator<Columbus.Csharp.Asg.Nodes.Structure.AttributeArgumentSyntax> iteratorForArguments = node.ArgumentsListIteratorBegin;
            while (iteratorForArguments.getValue() != null) {
               Columbus.Csharp.Asg.Nodes.Structure.AttributeArgumentSyntax endNodeRef = (Columbus.Csharp.Asg.Nodes.Structure.AttributeArgumentSyntax)iteratorForArguments.getValue();
              foreach (var visitor in visitorList) {
                visitor.visitAttributeArgumentListSyntax_Arguments(node.Id, endNodeRef.Id);
              }

              clearStoppedVisitors();
              if(needPreorderStop)
                return;

              if ((!fact.IsFilterTurnedOn && !visitFilteredEdge) || (fact.getFilterState(endNodeRef.Id) == Filter.FilterState.NotFiltered) || (!originalFilterState && visitFilteredEdge)) {
                  endNodeRef.accept(this);
              }
              foreach (var visitor in visitorList) {
                visitor.visitEndAttributeArgumentListSyntax_Arguments(node.Id, endNodeRef.Id);
              }

              clearStoppedVisitors();
              if(needPreorderStop)
                return;

            iteratorForArguments = iteratorForArguments.getNext();
            }
        }

        public override void visit(Columbus.Csharp.Asg.Nodes.Structure.AttributeArgumentListSyntax node, bool callFirst = true){
          if (safeMode || visitCrossEdgeTree) {
            if (safeMode) {
              if (visitedNodes[(int)node.Id]) { // for safemode
                return;
              }
            }
            visitedNodes[(int)node.Id] = true;
          }

          foreach (var visitor in visitorList) {
            visitor.visit(node);
            incVisitorDepth(visitor);
          }

          clearStoppedVisitors();
          if(needPreorderStop)
            return;

          visitAllEdges(node, true);

          foreach (var visitor in visitorList) {
            decVisitorDepth(visitor);
            visitor.visitEnd(node);
          }

          clearStoppedVisitors();
        }

        /// <summary>
        /// It call the traversal for the edges
        /// </summary>
        /// <param name="node">[in] The node with own type</param>
        /// <param name="callVirtualBase">[in] This paramater is don't used just api copatibility used.</param>
        public void visitAllEdges(Columbus.Csharp.Asg.Nodes.Structure.AttributeArgumentSyntax node, bool callFirst = true){
            visitAllEdges((Columbus.Csharp.Asg.Nodes.Base.Positioned)(node),false);


            Columbus.Csharp.Asg.Nodes.Base.Base genNodePtr;
            // edge: Expression
            genNodePtr = fact.getRef(node.getExpression()) ;
            if (genNodePtr != null) {
              Columbus.Csharp.Asg.Nodes.Expression.ExpressionSyntax endNodeRef = (Columbus.Csharp.Asg.Nodes.Expression.ExpressionSyntax)(genNodePtr);
              foreach (var visitor in visitorList) {
                visitor.visitAttributeArgumentSyntax_Expression(node.Id, endNodeRef.Id);
              }

              clearStoppedVisitors();
              if(needPreorderStop)
                return;

              if ((!fact.IsFilterTurnedOn && !visitFilteredEdge) || (fact.getFilterState(endNodeRef.Id) == Filter.FilterState.NotFiltered) || (!originalFilterState && visitFilteredEdge)) {
                  endNodeRef.accept(this);
              }
              foreach (var visitor in visitorList) {
                visitor.visitEndAttributeArgumentSyntax_Expression(node.Id, endNodeRef.Id);
              }

              clearStoppedVisitors();
              if(needPreorderStop)
                return;

            }

            // edge: NameColon
            genNodePtr = fact.getRef(node.getNameColon()) ;
            if (genNodePtr != null) {
              Columbus.Csharp.Asg.Nodes.Structure.NameColonSyntax endNodeRef = (Columbus.Csharp.Asg.Nodes.Structure.NameColonSyntax)(genNodePtr);
              foreach (var visitor in visitorList) {
                visitor.visitAttributeArgumentSyntax_NameColon(node.Id, endNodeRef.Id);
              }

              clearStoppedVisitors();
              if(needPreorderStop)
                return;

              if ((!fact.IsFilterTurnedOn && !visitFilteredEdge) || (fact.getFilterState(endNodeRef.Id) == Filter.FilterState.NotFiltered) || (!originalFilterState && visitFilteredEdge)) {
                  endNodeRef.accept(this);
              }
              foreach (var visitor in visitorList) {
                visitor.visitEndAttributeArgumentSyntax_NameColon(node.Id, endNodeRef.Id);
              }

              clearStoppedVisitors();
              if(needPreorderStop)
                return;

            }

            // edge: NameEquals
            genNodePtr = fact.getRef(node.getNameEquals()) ;
            if (genNodePtr != null) {
              Columbus.Csharp.Asg.Nodes.Structure.NameEqualsSyntax endNodeRef = (Columbus.Csharp.Asg.Nodes.Structure.NameEqualsSyntax)(genNodePtr);
              foreach (var visitor in visitorList) {
                visitor.visitAttributeArgumentSyntax_NameEquals(node.Id, endNodeRef.Id);
              }

              clearStoppedVisitors();
              if(needPreorderStop)
                return;

              if ((!fact.IsFilterTurnedOn && !visitFilteredEdge) || (fact.getFilterState(endNodeRef.Id) == Filter.FilterState.NotFiltered) || (!originalFilterState && visitFilteredEdge)) {
                  endNodeRef.accept(this);
              }
              foreach (var visitor in visitorList) {
                visitor.visitEndAttributeArgumentSyntax_NameEquals(node.Id, endNodeRef.Id);
              }

              clearStoppedVisitors();
              if(needPreorderStop)
                return;

            }
        }

        public override void visit(Columbus.Csharp.Asg.Nodes.Structure.AttributeArgumentSyntax node, bool callFirst = true){
          if (safeMode || visitCrossEdgeTree) {
            if (safeMode) {
              if (visitedNodes[(int)node.Id]) { // for safemode
                return;
              }
            }
            visitedNodes[(int)node.Id] = true;
          }

          foreach (var visitor in visitorList) {
            visitor.visit(node);
            incVisitorDepth(visitor);
          }

          clearStoppedVisitors();
          if(needPreorderStop)
            return;

          visitAllEdges(node, true);

          foreach (var visitor in visitorList) {
            decVisitorDepth(visitor);
            visitor.visitEnd(node);
          }

          clearStoppedVisitors();
        }

        /// <summary>
        /// It call the traversal for the edges
        /// </summary>
        /// <param name="node">[in] The node with own type</param>
        /// <param name="callVirtualBase">[in] This paramater is don't used just api copatibility used.</param>
        public void visitAllEdges(Columbus.Csharp.Asg.Nodes.Structure.AttributeListSyntax node, bool callFirst = true){
            visitAllEdges((Columbus.Csharp.Asg.Nodes.Base.Positioned)(node),false);


            // edge: Attributes
            ListIterator<Columbus.Csharp.Asg.Nodes.Structure.AttributeSyntax> iteratorForAttributes = node.AttributesListIteratorBegin;
            while (iteratorForAttributes.getValue() != null) {
               Columbus.Csharp.Asg.Nodes.Structure.AttributeSyntax endNodeRef = (Columbus.Csharp.Asg.Nodes.Structure.AttributeSyntax)iteratorForAttributes.getValue();
              foreach (var visitor in visitorList) {
                visitor.visitAttributeListSyntax_Attributes(node.Id, endNodeRef.Id);
              }

              clearStoppedVisitors();
              if(needPreorderStop)
                return;

              if ((!fact.IsFilterTurnedOn && !visitFilteredEdge) || (fact.getFilterState(endNodeRef.Id) == Filter.FilterState.NotFiltered) || (!originalFilterState && visitFilteredEdge)) {
                  endNodeRef.accept(this);
              }
              foreach (var visitor in visitorList) {
                visitor.visitEndAttributeListSyntax_Attributes(node.Id, endNodeRef.Id);
              }

              clearStoppedVisitors();
              if(needPreorderStop)
                return;

            iteratorForAttributes = iteratorForAttributes.getNext();
            }

            Columbus.Csharp.Asg.Nodes.Base.Base genNodePtr;
            // edge: Target
            genNodePtr = fact.getRef(node.getTarget()) ;
            if (genNodePtr != null) {
              Columbus.Csharp.Asg.Nodes.Structure.AttributeTargetSpecifierSyntax endNodeRef = (Columbus.Csharp.Asg.Nodes.Structure.AttributeTargetSpecifierSyntax)(genNodePtr);
              foreach (var visitor in visitorList) {
                visitor.visitAttributeListSyntax_Target(node.Id, endNodeRef.Id);
              }

              clearStoppedVisitors();
              if(needPreorderStop)
                return;

              if ((!fact.IsFilterTurnedOn && !visitFilteredEdge) || (fact.getFilterState(endNodeRef.Id) == Filter.FilterState.NotFiltered) || (!originalFilterState && visitFilteredEdge)) {
                  endNodeRef.accept(this);
              }
              foreach (var visitor in visitorList) {
                visitor.visitEndAttributeListSyntax_Target(node.Id, endNodeRef.Id);
              }

              clearStoppedVisitors();
              if(needPreorderStop)
                return;

            }
        }

        public override void visit(Columbus.Csharp.Asg.Nodes.Structure.AttributeListSyntax node, bool callFirst = true){
          if (safeMode || visitCrossEdgeTree) {
            if (safeMode) {
              if (visitedNodes[(int)node.Id]) { // for safemode
                return;
              }
            }
            visitedNodes[(int)node.Id] = true;
          }

          foreach (var visitor in visitorList) {
            visitor.visit(node);
            incVisitorDepth(visitor);
          }

          clearStoppedVisitors();
          if(needPreorderStop)
            return;

          visitAllEdges(node, true);

          foreach (var visitor in visitorList) {
            decVisitorDepth(visitor);
            visitor.visitEnd(node);
          }

          clearStoppedVisitors();
        }

        /// <summary>
        /// It call the traversal for the edges
        /// </summary>
        /// <param name="node">[in] The node with own type</param>
        /// <param name="callVirtualBase">[in] This paramater is don't used just api copatibility used.</param>
        public void visitAllEdges(Columbus.Csharp.Asg.Nodes.Structure.AttributeSyntax node, bool callFirst = true){
            visitAllEdges((Columbus.Csharp.Asg.Nodes.Base.Positioned)(node),false);


            Columbus.Csharp.Asg.Nodes.Base.Base genNodePtr;
            // edge: ArgumentList
            genNodePtr = fact.getRef(node.getArgumentList()) ;
            if (genNodePtr != null) {
              Columbus.Csharp.Asg.Nodes.Structure.AttributeArgumentListSyntax endNodeRef = (Columbus.Csharp.Asg.Nodes.Structure.AttributeArgumentListSyntax)(genNodePtr);
              foreach (var visitor in visitorList) {
                visitor.visitAttributeSyntax_ArgumentList(node.Id, endNodeRef.Id);
              }

              clearStoppedVisitors();
              if(needPreorderStop)
                return;

              if ((!fact.IsFilterTurnedOn && !visitFilteredEdge) || (fact.getFilterState(endNodeRef.Id) == Filter.FilterState.NotFiltered) || (!originalFilterState && visitFilteredEdge)) {
                  endNodeRef.accept(this);
              }
              foreach (var visitor in visitorList) {
                visitor.visitEndAttributeSyntax_ArgumentList(node.Id, endNodeRef.Id);
              }

              clearStoppedVisitors();
              if(needPreorderStop)
                return;

            }

            // edge: Name
            genNodePtr = fact.getRef(node.getName()) ;
            if (genNodePtr != null) {
              Columbus.Csharp.Asg.Nodes.Expression.NameSyntax endNodeRef = (Columbus.Csharp.Asg.Nodes.Expression.NameSyntax)(genNodePtr);
              foreach (var visitor in visitorList) {
                visitor.visitAttributeSyntax_Name(node.Id, endNodeRef.Id);
              }

              clearStoppedVisitors();
              if(needPreorderStop)
                return;

              if ((!fact.IsFilterTurnedOn && !visitFilteredEdge) || (fact.getFilterState(endNodeRef.Id) == Filter.FilterState.NotFiltered) || (!originalFilterState && visitFilteredEdge)) {
                  endNodeRef.accept(this);
              }
              foreach (var visitor in visitorList) {
                visitor.visitEndAttributeSyntax_Name(node.Id, endNodeRef.Id);
              }

              clearStoppedVisitors();
              if(needPreorderStop)
                return;

            }
        }

        public override void visit(Columbus.Csharp.Asg.Nodes.Structure.AttributeSyntax node, bool callFirst = true){
          if (safeMode || visitCrossEdgeTree) {
            if (safeMode) {
              if (visitedNodes[(int)node.Id]) { // for safemode
                return;
              }
            }
            visitedNodes[(int)node.Id] = true;
          }

          foreach (var visitor in visitorList) {
            visitor.visit(node);
            incVisitorDepth(visitor);
          }

          clearStoppedVisitors();
          if(needPreorderStop)
            return;

          visitAllEdges(node, true);

          foreach (var visitor in visitorList) {
            decVisitorDepth(visitor);
            visitor.visitEnd(node);
          }

          clearStoppedVisitors();
        }

        /// <summary>
        /// It call the traversal for the edges
        /// </summary>
        /// <param name="node">[in] The node with own type</param>
        /// <param name="callVirtualBase">[in] This paramater is don't used just api copatibility used.</param>
        public void visitAllEdges(Columbus.Csharp.Asg.Nodes.Structure.AttributeTargetSpecifierSyntax node, bool callFirst = true){
            visitAllEdges((Columbus.Csharp.Asg.Nodes.Base.Positioned)(node),false);
        }

        public override void visit(Columbus.Csharp.Asg.Nodes.Structure.AttributeTargetSpecifierSyntax node, bool callFirst = true){
          if (safeMode || visitCrossEdgeTree) {
            if (safeMode) {
              if (visitedNodes[(int)node.Id]) { // for safemode
                return;
              }
            }
            visitedNodes[(int)node.Id] = true;
          }

          foreach (var visitor in visitorList) {
            visitor.visit(node);
            incVisitorDepth(visitor);
          }

          clearStoppedVisitors();
          if(needPreorderStop)
            return;

          visitAllEdges(node, true);

          foreach (var visitor in visitorList) {
            decVisitorDepth(visitor);
            visitor.visitEnd(node);
          }

          clearStoppedVisitors();
        }

        /// <summary>
        /// It call the traversal for the edges
        /// </summary>
        /// <param name="node">[in] The node with own type</param>
        /// <param name="callVirtualBase">[in] This paramater is don't used just api copatibility used.</param>
        public void visitAllEdges(Columbus.Csharp.Asg.Nodes.Structure.BaseArgumentListSyntax node, bool callFirst = true){
            visitAllEdges((Columbus.Csharp.Asg.Nodes.Base.Positioned)(node),false);


            // edge: Arguments
            ListIterator<Columbus.Csharp.Asg.Nodes.Structure.ArgumentSyntax> iteratorForArguments = node.ArgumentsListIteratorBegin;
            while (iteratorForArguments.getValue() != null) {
               Columbus.Csharp.Asg.Nodes.Structure.ArgumentSyntax endNodeRef = (Columbus.Csharp.Asg.Nodes.Structure.ArgumentSyntax)iteratorForArguments.getValue();
              foreach (var visitor in visitorList) {
                visitor.visitBaseArgumentListSyntax_Arguments(node.Id, endNodeRef.Id);
              }

              clearStoppedVisitors();
              if(needPreorderStop)
                return;

              if ((!fact.IsFilterTurnedOn && !visitFilteredEdge) || (fact.getFilterState(endNodeRef.Id) == Filter.FilterState.NotFiltered) || (!originalFilterState && visitFilteredEdge)) {
                  endNodeRef.accept(this);
              }
              foreach (var visitor in visitorList) {
                visitor.visitEndBaseArgumentListSyntax_Arguments(node.Id, endNodeRef.Id);
              }

              clearStoppedVisitors();
              if(needPreorderStop)
                return;

            iteratorForArguments = iteratorForArguments.getNext();
            }
        }

        /// <summary>
        /// It call the traversal for the edges
        /// </summary>
        /// <param name="node">[in] The node with own type</param>
        /// <param name="callVirtualBase">[in] This paramater is don't used just api copatibility used.</param>
        public void visitAllEdges(Columbus.Csharp.Asg.Nodes.Structure.BaseCrefParameterListSyntax node, bool callFirst = true){
            visitAllEdges((Columbus.Csharp.Asg.Nodes.Base.Positioned)(node),false);


            // edge: Parameters
            ListIterator<Columbus.Csharp.Asg.Nodes.Structure.CrefParameterSyntax> iteratorForParameters = node.ParametersListIteratorBegin;
            while (iteratorForParameters.getValue() != null) {
               Columbus.Csharp.Asg.Nodes.Structure.CrefParameterSyntax endNodeRef = (Columbus.Csharp.Asg.Nodes.Structure.CrefParameterSyntax)iteratorForParameters.getValue();
              foreach (var visitor in visitorList) {
                visitor.visitBaseCrefParameterListSyntax_Parameters(node.Id, endNodeRef.Id);
              }

              clearStoppedVisitors();
              if(needPreorderStop)
                return;

              if ((!fact.IsFilterTurnedOn && !visitFilteredEdge) || (fact.getFilterState(endNodeRef.Id) == Filter.FilterState.NotFiltered) || (!originalFilterState && visitFilteredEdge)) {
                  endNodeRef.accept(this);
              }
              foreach (var visitor in visitorList) {
                visitor.visitEndBaseCrefParameterListSyntax_Parameters(node.Id, endNodeRef.Id);
              }

              clearStoppedVisitors();
              if(needPreorderStop)
                return;

            iteratorForParameters = iteratorForParameters.getNext();
            }
        }

        /// <summary>
        /// It call the traversal for the edges
        /// </summary>
        /// <param name="node">[in] The node with own type</param>
        /// <param name="callVirtualBase">[in] This paramater is don't used just api copatibility used.</param>
        public void visitAllEdges(Columbus.Csharp.Asg.Nodes.Structure.BaseFieldDeclarationSyntax node, bool callFirst = true){
            visitAllEdges((Columbus.Csharp.Asg.Nodes.Structure.MemberDeclarationSyntax)(node),false);


            // edge: AttributeLists
            ListIterator<Columbus.Csharp.Asg.Nodes.Structure.AttributeListSyntax> iteratorForAttributeLists = node.AttributeListsListIteratorBegin;
            while (iteratorForAttributeLists.getValue() != null) {
               Columbus.Csharp.Asg.Nodes.Structure.AttributeListSyntax endNodeRef = (Columbus.Csharp.Asg.Nodes.Structure.AttributeListSyntax)iteratorForAttributeLists.getValue();
              foreach (var visitor in visitorList) {
                visitor.visitBaseFieldDeclarationSyntax_AttributeLists(node.Id, endNodeRef.Id);
              }

              clearStoppedVisitors();
              if(needPreorderStop)
                return;

              if ((!fact.IsFilterTurnedOn && !visitFilteredEdge) || (fact.getFilterState(endNodeRef.Id) == Filter.FilterState.NotFiltered) || (!originalFilterState && visitFilteredEdge)) {
                  endNodeRef.accept(this);
              }
              foreach (var visitor in visitorList) {
                visitor.visitEndBaseFieldDeclarationSyntax_AttributeLists(node.Id, endNodeRef.Id);
              }

              clearStoppedVisitors();
              if(needPreorderStop)
                return;

            iteratorForAttributeLists = iteratorForAttributeLists.getNext();
            }

            Columbus.Csharp.Asg.Nodes.Base.Base genNodePtr;
            // edge: Declaration
            genNodePtr = fact.getRef(node.getDeclaration()) ;
            if (genNodePtr != null) {
              Columbus.Csharp.Asg.Nodes.Structure.VariableDeclarationSyntax endNodeRef = (Columbus.Csharp.Asg.Nodes.Structure.VariableDeclarationSyntax)(genNodePtr);
              foreach (var visitor in visitorList) {
                visitor.visitBaseFieldDeclarationSyntax_Declaration(node.Id, endNodeRef.Id);
              }

              clearStoppedVisitors();
              if(needPreorderStop)
                return;

              if ((!fact.IsFilterTurnedOn && !visitFilteredEdge) || (fact.getFilterState(endNodeRef.Id) == Filter.FilterState.NotFiltered) || (!originalFilterState && visitFilteredEdge)) {
                  endNodeRef.accept(this);
              }
              foreach (var visitor in visitorList) {
                visitor.visitEndBaseFieldDeclarationSyntax_Declaration(node.Id, endNodeRef.Id);
              }

              clearStoppedVisitors();
              if(needPreorderStop)
                return;

            }
        }

        /// <summary>
        /// It call the traversal for the edges
        /// </summary>
        /// <param name="node">[in] The node with own type</param>
        /// <param name="callVirtualBase">[in] This paramater is don't used just api copatibility used.</param>
        public void visitAllEdges(Columbus.Csharp.Asg.Nodes.Structure.BaseListSyntax node, bool callFirst = true){
            visitAllEdges((Columbus.Csharp.Asg.Nodes.Base.Positioned)(node),false);


            // edge: Types
            ListIterator<Columbus.Csharp.Asg.Nodes.Structure.BaseTypeSyntax> iteratorForTypes = node.TypesListIteratorBegin;
            while (iteratorForTypes.getValue() != null) {
               Columbus.Csharp.Asg.Nodes.Structure.BaseTypeSyntax endNodeRef = (Columbus.Csharp.Asg.Nodes.Structure.BaseTypeSyntax)iteratorForTypes.getValue();
              foreach (var visitor in visitorList) {
                visitor.visitBaseListSyntax_Types(node.Id, endNodeRef.Id);
              }

              clearStoppedVisitors();
              if(needPreorderStop)
                return;

              if ((!fact.IsFilterTurnedOn && !visitFilteredEdge) || (fact.getFilterState(endNodeRef.Id) == Filter.FilterState.NotFiltered) || (!originalFilterState && visitFilteredEdge)) {
                  endNodeRef.accept(this);
              }
              foreach (var visitor in visitorList) {
                visitor.visitEndBaseListSyntax_Types(node.Id, endNodeRef.Id);
              }

              clearStoppedVisitors();
              if(needPreorderStop)
                return;

            iteratorForTypes = iteratorForTypes.getNext();
            }
        }

        public override void visit(Columbus.Csharp.Asg.Nodes.Structure.BaseListSyntax node, bool callFirst = true){
          if (safeMode || visitCrossEdgeTree) {
            if (safeMode) {
              if (visitedNodes[(int)node.Id]) { // for safemode
                return;
              }
            }
            visitedNodes[(int)node.Id] = true;
          }

          foreach (var visitor in visitorList) {
            visitor.visit(node);
            incVisitorDepth(visitor);
          }

          clearStoppedVisitors();
          if(needPreorderStop)
            return;

          visitAllEdges(node, true);

          foreach (var visitor in visitorList) {
            decVisitorDepth(visitor);
            visitor.visitEnd(node);
          }

          clearStoppedVisitors();
        }

        /// <summary>
        /// It call the traversal for the edges
        /// </summary>
        /// <param name="node">[in] The node with own type</param>
        /// <param name="callVirtualBase">[in] This paramater is don't used just api copatibility used.</param>
        public void visitAllEdges(Columbus.Csharp.Asg.Nodes.Structure.BaseMethodDeclarationSyntax node, bool callFirst = true){
            visitAllEdges((Columbus.Csharp.Asg.Nodes.Structure.MemberDeclarationSyntax)(node),false);


            // edge: AccessedEnumMembers
            ListIterator<Columbus.Csharp.Asg.Nodes.Structure.EnumMemberDeclarationSyntax> iteratorForAccessedEnumMembers = node.AccessedEnumMembersListIteratorBegin;
            while (iteratorForAccessedEnumMembers.getValue() != null) {
               Columbus.Csharp.Asg.Nodes.Structure.EnumMemberDeclarationSyntax endNodeRef = (Columbus.Csharp.Asg.Nodes.Structure.EnumMemberDeclarationSyntax)iteratorForAccessedEnumMembers.getValue();
              foreach (var visitor in visitorList) {
                visitor.visitBaseMethodDeclarationSyntax_AccessedEnumMembers(node.Id, endNodeRef.Id);
              }

              clearStoppedVisitors();
              if(needPreorderStop)
                return;

              if ((!fact.IsFilterTurnedOn && !visitFilteredEdge) || (fact.getFilterState(endNodeRef.Id) == Filter.FilterState.NotFiltered) || (!originalFilterState && visitFilteredEdge)) {
                  if (apRoot != null) {
                    if (visitCrossEdgeTree) {
                      unvisitedNodes[(int)endNodeRef.Id] = true;
                    }
                  }
                  if (traversaldCrossEdges[(int)Types.EdgeKind.edkBaseMethodDeclarationSyntax_AccessedEnumMembers]) {
                    endNodeRef.accept(this);
                  }
              }
              foreach (var visitor in visitorList) {
                visitor.visitEndBaseMethodDeclarationSyntax_AccessedEnumMembers(node.Id, endNodeRef.Id);
              }

              clearStoppedVisitors();
              if(needPreorderStop)
                return;

            iteratorForAccessedEnumMembers = iteratorForAccessedEnumMembers.getNext();
            }

            // edge: AttributeLists
            ListIterator<Columbus.Csharp.Asg.Nodes.Structure.AttributeListSyntax> iteratorForAttributeLists = node.AttributeListsListIteratorBegin;
            while (iteratorForAttributeLists.getValue() != null) {
               Columbus.Csharp.Asg.Nodes.Structure.AttributeListSyntax endNodeRef = (Columbus.Csharp.Asg.Nodes.Structure.AttributeListSyntax)iteratorForAttributeLists.getValue();
              foreach (var visitor in visitorList) {
                visitor.visitBaseMethodDeclarationSyntax_AttributeLists(node.Id, endNodeRef.Id);
              }

              clearStoppedVisitors();
              if(needPreorderStop)
                return;

              if ((!fact.IsFilterTurnedOn && !visitFilteredEdge) || (fact.getFilterState(endNodeRef.Id) == Filter.FilterState.NotFiltered) || (!originalFilterState && visitFilteredEdge)) {
                  endNodeRef.accept(this);
              }
              foreach (var visitor in visitorList) {
                visitor.visitEndBaseMethodDeclarationSyntax_AttributeLists(node.Id, endNodeRef.Id);
              }

              clearStoppedVisitors();
              if(needPreorderStop)
                return;

            iteratorForAttributeLists = iteratorForAttributeLists.getNext();
            }

            Columbus.Csharp.Asg.Nodes.Base.Base genNodePtr;
            // edge: Body
            genNodePtr = fact.getRef(node.getBody()) ;
            if (genNodePtr != null) {
              Columbus.Csharp.Asg.Nodes.Statement.BlockSyntax endNodeRef = (Columbus.Csharp.Asg.Nodes.Statement.BlockSyntax)(genNodePtr);
              foreach (var visitor in visitorList) {
                visitor.visitBaseMethodDeclarationSyntax_Body(node.Id, endNodeRef.Id);
              }

              clearStoppedVisitors();
              if(needPreorderStop)
                return;

              if ((!fact.IsFilterTurnedOn && !visitFilteredEdge) || (fact.getFilterState(endNodeRef.Id) == Filter.FilterState.NotFiltered) || (!originalFilterState && visitFilteredEdge)) {
                  endNodeRef.accept(this);
              }
              foreach (var visitor in visitorList) {
                visitor.visitEndBaseMethodDeclarationSyntax_Body(node.Id, endNodeRef.Id);
              }

              clearStoppedVisitors();
              if(needPreorderStop)
                return;

            }

            // edge: ExpressionBody
            genNodePtr = fact.getRef(node.getExpressionBody()) ;
            if (genNodePtr != null) {
              Columbus.Csharp.Asg.Nodes.Structure.ArrowExpressionClauseSyntax endNodeRef = (Columbus.Csharp.Asg.Nodes.Structure.ArrowExpressionClauseSyntax)(genNodePtr);
              foreach (var visitor in visitorList) {
                visitor.visitBaseMethodDeclarationSyntax_ExpressionBody(node.Id, endNodeRef.Id);
              }

              clearStoppedVisitors();
              if(needPreorderStop)
                return;

              if ((!fact.IsFilterTurnedOn && !visitFilteredEdge) || (fact.getFilterState(endNodeRef.Id) == Filter.FilterState.NotFiltered) || (!originalFilterState && visitFilteredEdge)) {
                  endNodeRef.accept(this);
              }
              foreach (var visitor in visitorList) {
                visitor.visitEndBaseMethodDeclarationSyntax_ExpressionBody(node.Id, endNodeRef.Id);
              }

              clearStoppedVisitors();
              if(needPreorderStop)
                return;

            }

            // edge: ParameterList
            genNodePtr = fact.getRef(node.getParameterList()) ;
            if (genNodePtr != null) {
              Columbus.Csharp.Asg.Nodes.Structure.ParameterListSyntax endNodeRef = (Columbus.Csharp.Asg.Nodes.Structure.ParameterListSyntax)(genNodePtr);
              foreach (var visitor in visitorList) {
                visitor.visitBaseMethodDeclarationSyntax_ParameterList(node.Id, endNodeRef.Id);
              }

              clearStoppedVisitors();
              if(needPreorderStop)
                return;

              if ((!fact.IsFilterTurnedOn && !visitFilteredEdge) || (fact.getFilterState(endNodeRef.Id) == Filter.FilterState.NotFiltered) || (!originalFilterState && visitFilteredEdge)) {
                  endNodeRef.accept(this);
              }
              foreach (var visitor in visitorList) {
                visitor.visitEndBaseMethodDeclarationSyntax_ParameterList(node.Id, endNodeRef.Id);
              }

              clearStoppedVisitors();
              if(needPreorderStop)
                return;

            }
        }

        /// <summary>
        /// It call the traversal for the edges
        /// </summary>
        /// <param name="node">[in] The node with own type</param>
        /// <param name="callVirtualBase">[in] This paramater is don't used just api copatibility used.</param>
        public void visitAllEdges(Columbus.Csharp.Asg.Nodes.Structure.BaseParameterListSyntax node, bool callFirst = true){
            visitAllEdges((Columbus.Csharp.Asg.Nodes.Base.Positioned)(node),false);


            // edge: Parameters
            ListIterator<Columbus.Csharp.Asg.Nodes.Structure.ParameterSyntax> iteratorForParameters = node.ParametersListIteratorBegin;
            while (iteratorForParameters.getValue() != null) {
               Columbus.Csharp.Asg.Nodes.Structure.ParameterSyntax endNodeRef = (Columbus.Csharp.Asg.Nodes.Structure.ParameterSyntax)iteratorForParameters.getValue();
              foreach (var visitor in visitorList) {
                visitor.visitBaseParameterListSyntax_Parameters(node.Id, endNodeRef.Id);
              }

              clearStoppedVisitors();
              if(needPreorderStop)
                return;

              if ((!fact.IsFilterTurnedOn && !visitFilteredEdge) || (fact.getFilterState(endNodeRef.Id) == Filter.FilterState.NotFiltered) || (!originalFilterState && visitFilteredEdge)) {
                  endNodeRef.accept(this);
              }
              foreach (var visitor in visitorList) {
                visitor.visitEndBaseParameterListSyntax_Parameters(node.Id, endNodeRef.Id);
              }

              clearStoppedVisitors();
              if(needPreorderStop)
                return;

            iteratorForParameters = iteratorForParameters.getNext();
            }
        }

        /// <summary>
        /// It call the traversal for the edges
        /// </summary>
        /// <param name="node">[in] The node with own type</param>
        /// <param name="callVirtualBase">[in] This paramater is don't used just api copatibility used.</param>
        public void visitAllEdges(Columbus.Csharp.Asg.Nodes.Structure.BasePropertyDeclarationSyntax node, bool callFirst = true){
            visitAllEdges((Columbus.Csharp.Asg.Nodes.Structure.MemberDeclarationSyntax)(node),false);


            Columbus.Csharp.Asg.Nodes.Base.Base genNodePtr;
            // edge: AccessorList
            genNodePtr = fact.getRef(node.getAccessorList()) ;
            if (genNodePtr != null) {
              Columbus.Csharp.Asg.Nodes.Structure.AccessorListSyntax endNodeRef = (Columbus.Csharp.Asg.Nodes.Structure.AccessorListSyntax)(genNodePtr);
              foreach (var visitor in visitorList) {
                visitor.visitBasePropertyDeclarationSyntax_AccessorList(node.Id, endNodeRef.Id);
              }

              clearStoppedVisitors();
              if(needPreorderStop)
                return;

              if ((!fact.IsFilterTurnedOn && !visitFilteredEdge) || (fact.getFilterState(endNodeRef.Id) == Filter.FilterState.NotFiltered) || (!originalFilterState && visitFilteredEdge)) {
                  endNodeRef.accept(this);
              }
              foreach (var visitor in visitorList) {
                visitor.visitEndBasePropertyDeclarationSyntax_AccessorList(node.Id, endNodeRef.Id);
              }

              clearStoppedVisitors();
              if(needPreorderStop)
                return;

            }

            // edge: AttributeLists
            ListIterator<Columbus.Csharp.Asg.Nodes.Structure.AttributeListSyntax> iteratorForAttributeLists = node.AttributeListsListIteratorBegin;
            while (iteratorForAttributeLists.getValue() != null) {
               Columbus.Csharp.Asg.Nodes.Structure.AttributeListSyntax endNodeRef = (Columbus.Csharp.Asg.Nodes.Structure.AttributeListSyntax)iteratorForAttributeLists.getValue();
              foreach (var visitor in visitorList) {
                visitor.visitBasePropertyDeclarationSyntax_AttributeLists(node.Id, endNodeRef.Id);
              }

              clearStoppedVisitors();
              if(needPreorderStop)
                return;

              if ((!fact.IsFilterTurnedOn && !visitFilteredEdge) || (fact.getFilterState(endNodeRef.Id) == Filter.FilterState.NotFiltered) || (!originalFilterState && visitFilteredEdge)) {
                  endNodeRef.accept(this);
              }
              foreach (var visitor in visitorList) {
                visitor.visitEndBasePropertyDeclarationSyntax_AttributeLists(node.Id, endNodeRef.Id);
              }

              clearStoppedVisitors();
              if(needPreorderStop)
                return;

            iteratorForAttributeLists = iteratorForAttributeLists.getNext();
            }

            // edge: ExplicitInterfaceSpecifier
            genNodePtr = fact.getRef(node.getExplicitInterfaceSpecifier()) ;
            if (genNodePtr != null) {
              Columbus.Csharp.Asg.Nodes.Structure.ExplicitInterfaceSpecifierSyntax endNodeRef = (Columbus.Csharp.Asg.Nodes.Structure.ExplicitInterfaceSpecifierSyntax)(genNodePtr);
              foreach (var visitor in visitorList) {
                visitor.visitBasePropertyDeclarationSyntax_ExplicitInterfaceSpecifier(node.Id, endNodeRef.Id);
              }

              clearStoppedVisitors();
              if(needPreorderStop)
                return;

              if ((!fact.IsFilterTurnedOn && !visitFilteredEdge) || (fact.getFilterState(endNodeRef.Id) == Filter.FilterState.NotFiltered) || (!originalFilterState && visitFilteredEdge)) {
                  endNodeRef.accept(this);
              }
              foreach (var visitor in visitorList) {
                visitor.visitEndBasePropertyDeclarationSyntax_ExplicitInterfaceSpecifier(node.Id, endNodeRef.Id);
              }

              clearStoppedVisitors();
              if(needPreorderStop)
                return;

            }

            // edge: Type
            genNodePtr = fact.getRef(node.getType()) ;
            if (genNodePtr != null) {
              Columbus.Csharp.Asg.Nodes.Expression.TypeSyntax endNodeRef = (Columbus.Csharp.Asg.Nodes.Expression.TypeSyntax)(genNodePtr);
              foreach (var visitor in visitorList) {
                visitor.visitBasePropertyDeclarationSyntax_Type(node.Id, endNodeRef.Id);
              }

              clearStoppedVisitors();
              if(needPreorderStop)
                return;

              if ((!fact.IsFilterTurnedOn && !visitFilteredEdge) || (fact.getFilterState(endNodeRef.Id) == Filter.FilterState.NotFiltered) || (!originalFilterState && visitFilteredEdge)) {
                  endNodeRef.accept(this);
              }
              foreach (var visitor in visitorList) {
                visitor.visitEndBasePropertyDeclarationSyntax_Type(node.Id, endNodeRef.Id);
              }

              clearStoppedVisitors();
              if(needPreorderStop)
                return;

            }
        }

        /// <summary>
        /// It call the traversal for the edges
        /// </summary>
        /// <param name="node">[in] The node with own type</param>
        /// <param name="callVirtualBase">[in] This paramater is don't used just api copatibility used.</param>
        public void visitAllEdges(Columbus.Csharp.Asg.Nodes.Structure.BaseTypeDeclarationSyntax node, bool callFirst = true){
            visitAllEdges((Columbus.Csharp.Asg.Nodes.Structure.MemberDeclarationSyntax)(node),false);


            // edge: AttributeLists
            ListIterator<Columbus.Csharp.Asg.Nodes.Structure.AttributeListSyntax> iteratorForAttributeLists = node.AttributeListsListIteratorBegin;
            while (iteratorForAttributeLists.getValue() != null) {
               Columbus.Csharp.Asg.Nodes.Structure.AttributeListSyntax endNodeRef = (Columbus.Csharp.Asg.Nodes.Structure.AttributeListSyntax)iteratorForAttributeLists.getValue();
              foreach (var visitor in visitorList) {
                visitor.visitBaseTypeDeclarationSyntax_AttributeLists(node.Id, endNodeRef.Id);
              }

              clearStoppedVisitors();
              if(needPreorderStop)
                return;

              if ((!fact.IsFilterTurnedOn && !visitFilteredEdge) || (fact.getFilterState(endNodeRef.Id) == Filter.FilterState.NotFiltered) || (!originalFilterState && visitFilteredEdge)) {
                  endNodeRef.accept(this);
              }
              foreach (var visitor in visitorList) {
                visitor.visitEndBaseTypeDeclarationSyntax_AttributeLists(node.Id, endNodeRef.Id);
              }

              clearStoppedVisitors();
              if(needPreorderStop)
                return;

            iteratorForAttributeLists = iteratorForAttributeLists.getNext();
            }

            Columbus.Csharp.Asg.Nodes.Base.Base genNodePtr;
            // edge: BaseList
            genNodePtr = fact.getRef(node.getBaseList()) ;
            if (genNodePtr != null) {
              Columbus.Csharp.Asg.Nodes.Structure.BaseListSyntax endNodeRef = (Columbus.Csharp.Asg.Nodes.Structure.BaseListSyntax)(genNodePtr);
              foreach (var visitor in visitorList) {
                visitor.visitBaseTypeDeclarationSyntax_BaseList(node.Id, endNodeRef.Id);
              }

              clearStoppedVisitors();
              if(needPreorderStop)
                return;

              if ((!fact.IsFilterTurnedOn && !visitFilteredEdge) || (fact.getFilterState(endNodeRef.Id) == Filter.FilterState.NotFiltered) || (!originalFilterState && visitFilteredEdge)) {
                  endNodeRef.accept(this);
              }
              foreach (var visitor in visitorList) {
                visitor.visitEndBaseTypeDeclarationSyntax_BaseList(node.Id, endNodeRef.Id);
              }

              clearStoppedVisitors();
              if(needPreorderStop)
                return;

            }
        }

        /// <summary>
        /// It call the traversal for the edges
        /// </summary>
        /// <param name="node">[in] The node with own type</param>
        /// <param name="callVirtualBase">[in] This paramater is don't used just api copatibility used.</param>
        public void visitAllEdges(Columbus.Csharp.Asg.Nodes.Structure.BaseTypeSyntax node, bool callFirst = true){
            visitAllEdges((Columbus.Csharp.Asg.Nodes.Base.Positioned)(node),false);


            Columbus.Csharp.Asg.Nodes.Base.Base genNodePtr;
            // edge: Type
            genNodePtr = fact.getRef(node.getType()) ;
            if (genNodePtr != null) {
              Columbus.Csharp.Asg.Nodes.Expression.TypeSyntax endNodeRef = (Columbus.Csharp.Asg.Nodes.Expression.TypeSyntax)(genNodePtr);
              foreach (var visitor in visitorList) {
                visitor.visitBaseTypeSyntax_Type(node.Id, endNodeRef.Id);
              }

              clearStoppedVisitors();
              if(needPreorderStop)
                return;

              if ((!fact.IsFilterTurnedOn && !visitFilteredEdge) || (fact.getFilterState(endNodeRef.Id) == Filter.FilterState.NotFiltered) || (!originalFilterState && visitFilteredEdge)) {
                  endNodeRef.accept(this);
              }
              foreach (var visitor in visitorList) {
                visitor.visitEndBaseTypeSyntax_Type(node.Id, endNodeRef.Id);
              }

              clearStoppedVisitors();
              if(needPreorderStop)
                return;

            }
        }

        /// <summary>
        /// It call the traversal for the edges
        /// </summary>
        /// <param name="node">[in] The node with own type</param>
        /// <param name="callVirtualBase">[in] This paramater is don't used just api copatibility used.</param>
        public void visitAllEdges(Columbus.Csharp.Asg.Nodes.Structure.BracketedArgumentListSyntax node, bool callFirst = true){
            visitAllEdges((Columbus.Csharp.Asg.Nodes.Structure.BaseArgumentListSyntax)(node),false);
        }

        public override void visit(Columbus.Csharp.Asg.Nodes.Structure.BracketedArgumentListSyntax node, bool callFirst = true){
          if (safeMode || visitCrossEdgeTree) {
            if (safeMode) {
              if (visitedNodes[(int)node.Id]) { // for safemode
                return;
              }
            }
            visitedNodes[(int)node.Id] = true;
          }

          foreach (var visitor in visitorList) {
            visitor.visit(node);
            incVisitorDepth(visitor);
          }

          clearStoppedVisitors();
          if(needPreorderStop)
            return;

          visitAllEdges(node, true);

          foreach (var visitor in visitorList) {
            decVisitorDepth(visitor);
            visitor.visitEnd(node);
          }

          clearStoppedVisitors();
        }

        /// <summary>
        /// It call the traversal for the edges
        /// </summary>
        /// <param name="node">[in] The node with own type</param>
        /// <param name="callVirtualBase">[in] This paramater is don't used just api copatibility used.</param>
        public void visitAllEdges(Columbus.Csharp.Asg.Nodes.Structure.BracketedParameterListSyntax node, bool callFirst = true){
            visitAllEdges((Columbus.Csharp.Asg.Nodes.Structure.BaseParameterListSyntax)(node),false);
        }

        public override void visit(Columbus.Csharp.Asg.Nodes.Structure.BracketedParameterListSyntax node, bool callFirst = true){
          if (safeMode || visitCrossEdgeTree) {
            if (safeMode) {
              if (visitedNodes[(int)node.Id]) { // for safemode
                return;
              }
            }
            visitedNodes[(int)node.Id] = true;
          }

          foreach (var visitor in visitorList) {
            visitor.visit(node);
            incVisitorDepth(visitor);
          }

          clearStoppedVisitors();
          if(needPreorderStop)
            return;

          visitAllEdges(node, true);

          foreach (var visitor in visitorList) {
            decVisitorDepth(visitor);
            visitor.visitEnd(node);
          }

          clearStoppedVisitors();
        }

        /// <summary>
        /// It call the traversal for the edges
        /// </summary>
        /// <param name="node">[in] The node with own type</param>
        /// <param name="callVirtualBase">[in] This paramater is don't used just api copatibility used.</param>
        public void visitAllEdges(Columbus.Csharp.Asg.Nodes.Structure.CasePatternSwitchLabelSyntax node, bool callFirst = true){
            visitAllEdges((Columbus.Csharp.Asg.Nodes.Structure.SwitchLabelSyntax)(node),false);


            Columbus.Csharp.Asg.Nodes.Base.Base genNodePtr;
            // edge: Pattern
            genNodePtr = fact.getRef(node.getPattern()) ;
            if (genNodePtr != null) {
              Columbus.Csharp.Asg.Nodes.Structure.PatternSyntax endNodeRef = (Columbus.Csharp.Asg.Nodes.Structure.PatternSyntax)(genNodePtr);
              foreach (var visitor in visitorList) {
                visitor.visitCasePatternSwitchLabelSyntax_Pattern(node.Id, endNodeRef.Id);
              }

              clearStoppedVisitors();
              if(needPreorderStop)
                return;

              if ((!fact.IsFilterTurnedOn && !visitFilteredEdge) || (fact.getFilterState(endNodeRef.Id) == Filter.FilterState.NotFiltered) || (!originalFilterState && visitFilteredEdge)) {
                  endNodeRef.accept(this);
              }
              foreach (var visitor in visitorList) {
                visitor.visitEndCasePatternSwitchLabelSyntax_Pattern(node.Id, endNodeRef.Id);
              }

              clearStoppedVisitors();
              if(needPreorderStop)
                return;

            }

            // edge: WhenClause
            genNodePtr = fact.getRef(node.getWhenClause()) ;
            if (genNodePtr != null) {
              Columbus.Csharp.Asg.Nodes.Structure.WhenClauseSyntax endNodeRef = (Columbus.Csharp.Asg.Nodes.Structure.WhenClauseSyntax)(genNodePtr);
              foreach (var visitor in visitorList) {
                visitor.visitCasePatternSwitchLabelSyntax_WhenClause(node.Id, endNodeRef.Id);
              }

              clearStoppedVisitors();
              if(needPreorderStop)
                return;

              if ((!fact.IsFilterTurnedOn && !visitFilteredEdge) || (fact.getFilterState(endNodeRef.Id) == Filter.FilterState.NotFiltered) || (!originalFilterState && visitFilteredEdge)) {
                  endNodeRef.accept(this);
              }
              foreach (var visitor in visitorList) {
                visitor.visitEndCasePatternSwitchLabelSyntax_WhenClause(node.Id, endNodeRef.Id);
              }

              clearStoppedVisitors();
              if(needPreorderStop)
                return;

            }
        }

        public override void visit(Columbus.Csharp.Asg.Nodes.Structure.CasePatternSwitchLabelSyntax node, bool callFirst = true){
          if (safeMode || visitCrossEdgeTree) {
            if (safeMode) {
              if (visitedNodes[(int)node.Id]) { // for safemode
                return;
              }
            }
            visitedNodes[(int)node.Id] = true;
          }

          foreach (var visitor in visitorList) {
            visitor.visit(node);
            incVisitorDepth(visitor);
          }

          clearStoppedVisitors();
          if(needPreorderStop)
            return;

          visitAllEdges(node, true);

          foreach (var visitor in visitorList) {
            decVisitorDepth(visitor);
            visitor.visitEnd(node);
          }

          clearStoppedVisitors();
        }

        /// <summary>
        /// It call the traversal for the edges
        /// </summary>
        /// <param name="node">[in] The node with own type</param>
        /// <param name="callVirtualBase">[in] This paramater is don't used just api copatibility used.</param>
        public void visitAllEdges(Columbus.Csharp.Asg.Nodes.Structure.CaseSwitchLabelSyntax node, bool callFirst = true){
            visitAllEdges((Columbus.Csharp.Asg.Nodes.Structure.SwitchLabelSyntax)(node),false);


            Columbus.Csharp.Asg.Nodes.Base.Base genNodePtr;
            // edge: Value
            genNodePtr = fact.getRef(node.getValue()) ;
            if (genNodePtr != null) {
              Columbus.Csharp.Asg.Nodes.Expression.ExpressionSyntax endNodeRef = (Columbus.Csharp.Asg.Nodes.Expression.ExpressionSyntax)(genNodePtr);
              foreach (var visitor in visitorList) {
                visitor.visitCaseSwitchLabelSyntax_Value(node.Id, endNodeRef.Id);
              }

              clearStoppedVisitors();
              if(needPreorderStop)
                return;

              if ((!fact.IsFilterTurnedOn && !visitFilteredEdge) || (fact.getFilterState(endNodeRef.Id) == Filter.FilterState.NotFiltered) || (!originalFilterState && visitFilteredEdge)) {
                  endNodeRef.accept(this);
              }
              foreach (var visitor in visitorList) {
                visitor.visitEndCaseSwitchLabelSyntax_Value(node.Id, endNodeRef.Id);
              }

              clearStoppedVisitors();
              if(needPreorderStop)
                return;

            }
        }

        public override void visit(Columbus.Csharp.Asg.Nodes.Structure.CaseSwitchLabelSyntax node, bool callFirst = true){
          if (safeMode || visitCrossEdgeTree) {
            if (safeMode) {
              if (visitedNodes[(int)node.Id]) { // for safemode
                return;
              }
            }
            visitedNodes[(int)node.Id] = true;
          }

          foreach (var visitor in visitorList) {
            visitor.visit(node);
            incVisitorDepth(visitor);
          }

          clearStoppedVisitors();
          if(needPreorderStop)
            return;

          visitAllEdges(node, true);

          foreach (var visitor in visitorList) {
            decVisitorDepth(visitor);
            visitor.visitEnd(node);
          }

          clearStoppedVisitors();
        }

        /// <summary>
        /// It call the traversal for the edges
        /// </summary>
        /// <param name="node">[in] The node with own type</param>
        /// <param name="callVirtualBase">[in] This paramater is don't used just api copatibility used.</param>
        public void visitAllEdges(Columbus.Csharp.Asg.Nodes.Structure.CatchClauseSyntax node, bool callFirst = true){
            visitAllEdges((Columbus.Csharp.Asg.Nodes.Base.Positioned)(node),false);


            Columbus.Csharp.Asg.Nodes.Base.Base genNodePtr;
            // edge: Block
            genNodePtr = fact.getRef(node.getBlock()) ;
            if (genNodePtr != null) {
              Columbus.Csharp.Asg.Nodes.Statement.BlockSyntax endNodeRef = (Columbus.Csharp.Asg.Nodes.Statement.BlockSyntax)(genNodePtr);
              foreach (var visitor in visitorList) {
                visitor.visitCatchClauseSyntax_Block(node.Id, endNodeRef.Id);
              }

              clearStoppedVisitors();
              if(needPreorderStop)
                return;

              if ((!fact.IsFilterTurnedOn && !visitFilteredEdge) || (fact.getFilterState(endNodeRef.Id) == Filter.FilterState.NotFiltered) || (!originalFilterState && visitFilteredEdge)) {
                  endNodeRef.accept(this);
              }
              foreach (var visitor in visitorList) {
                visitor.visitEndCatchClauseSyntax_Block(node.Id, endNodeRef.Id);
              }

              clearStoppedVisitors();
              if(needPreorderStop)
                return;

            }

            // edge: Declaration
            genNodePtr = fact.getRef(node.getDeclaration()) ;
            if (genNodePtr != null) {
              Columbus.Csharp.Asg.Nodes.Structure.CatchDeclarationSyntax endNodeRef = (Columbus.Csharp.Asg.Nodes.Structure.CatchDeclarationSyntax)(genNodePtr);
              foreach (var visitor in visitorList) {
                visitor.visitCatchClauseSyntax_Declaration(node.Id, endNodeRef.Id);
              }

              clearStoppedVisitors();
              if(needPreorderStop)
                return;

              if ((!fact.IsFilterTurnedOn && !visitFilteredEdge) || (fact.getFilterState(endNodeRef.Id) == Filter.FilterState.NotFiltered) || (!originalFilterState && visitFilteredEdge)) {
                  endNodeRef.accept(this);
              }
              foreach (var visitor in visitorList) {
                visitor.visitEndCatchClauseSyntax_Declaration(node.Id, endNodeRef.Id);
              }

              clearStoppedVisitors();
              if(needPreorderStop)
                return;

            }

            // edge: Filter
            genNodePtr = fact.getRef(node.getFilter()) ;
            if (genNodePtr != null) {
              Columbus.Csharp.Asg.Nodes.Structure.CatchFilterClauseSyntax endNodeRef = (Columbus.Csharp.Asg.Nodes.Structure.CatchFilterClauseSyntax)(genNodePtr);
              foreach (var visitor in visitorList) {
                visitor.visitCatchClauseSyntax_Filter(node.Id, endNodeRef.Id);
              }

              clearStoppedVisitors();
              if(needPreorderStop)
                return;

              if ((!fact.IsFilterTurnedOn && !visitFilteredEdge) || (fact.getFilterState(endNodeRef.Id) == Filter.FilterState.NotFiltered) || (!originalFilterState && visitFilteredEdge)) {
                  endNodeRef.accept(this);
              }
              foreach (var visitor in visitorList) {
                visitor.visitEndCatchClauseSyntax_Filter(node.Id, endNodeRef.Id);
              }

              clearStoppedVisitors();
              if(needPreorderStop)
                return;

            }
        }

        public override void visit(Columbus.Csharp.Asg.Nodes.Structure.CatchClauseSyntax node, bool callFirst = true){
          if (safeMode || visitCrossEdgeTree) {
            if (safeMode) {
              if (visitedNodes[(int)node.Id]) { // for safemode
                return;
              }
            }
            visitedNodes[(int)node.Id] = true;
          }

          foreach (var visitor in visitorList) {
            visitor.visit(node);
            incVisitorDepth(visitor);
          }

          clearStoppedVisitors();
          if(needPreorderStop)
            return;

          visitAllEdges(node, true);

          foreach (var visitor in visitorList) {
            decVisitorDepth(visitor);
            visitor.visitEnd(node);
          }

          clearStoppedVisitors();
        }

        /// <summary>
        /// It call the traversal for the edges
        /// </summary>
        /// <param name="node">[in] The node with own type</param>
        /// <param name="callVirtualBase">[in] This paramater is don't used just api copatibility used.</param>
        public void visitAllEdges(Columbus.Csharp.Asg.Nodes.Structure.CatchDeclarationSyntax node, bool callFirst = true){
            visitAllEdges((Columbus.Csharp.Asg.Nodes.Base.Positioned)(node),false);


            Columbus.Csharp.Asg.Nodes.Base.Base genNodePtr;
            // edge: Type
            genNodePtr = fact.getRef(node.getType()) ;
            if (genNodePtr != null) {
              Columbus.Csharp.Asg.Nodes.Expression.TypeSyntax endNodeRef = (Columbus.Csharp.Asg.Nodes.Expression.TypeSyntax)(genNodePtr);
              foreach (var visitor in visitorList) {
                visitor.visitCatchDeclarationSyntax_Type(node.Id, endNodeRef.Id);
              }

              clearStoppedVisitors();
              if(needPreorderStop)
                return;

              if ((!fact.IsFilterTurnedOn && !visitFilteredEdge) || (fact.getFilterState(endNodeRef.Id) == Filter.FilterState.NotFiltered) || (!originalFilterState && visitFilteredEdge)) {
                  endNodeRef.accept(this);
              }
              foreach (var visitor in visitorList) {
                visitor.visitEndCatchDeclarationSyntax_Type(node.Id, endNodeRef.Id);
              }

              clearStoppedVisitors();
              if(needPreorderStop)
                return;

            }
        }

        public override void visit(Columbus.Csharp.Asg.Nodes.Structure.CatchDeclarationSyntax node, bool callFirst = true){
          if (safeMode || visitCrossEdgeTree) {
            if (safeMode) {
              if (visitedNodes[(int)node.Id]) { // for safemode
                return;
              }
            }
            visitedNodes[(int)node.Id] = true;
          }

          foreach (var visitor in visitorList) {
            visitor.visit(node);
            incVisitorDepth(visitor);
          }

          clearStoppedVisitors();
          if(needPreorderStop)
            return;

          visitAllEdges(node, true);

          foreach (var visitor in visitorList) {
            decVisitorDepth(visitor);
            visitor.visitEnd(node);
          }

          clearStoppedVisitors();
        }

        /// <summary>
        /// It call the traversal for the edges
        /// </summary>
        /// <param name="node">[in] The node with own type</param>
        /// <param name="callVirtualBase">[in] This paramater is don't used just api copatibility used.</param>
        public void visitAllEdges(Columbus.Csharp.Asg.Nodes.Structure.CatchFilterClauseSyntax node, bool callFirst = true){
            visitAllEdges((Columbus.Csharp.Asg.Nodes.Base.Positioned)(node),false);


            Columbus.Csharp.Asg.Nodes.Base.Base genNodePtr;
            // edge: FilterExpression
            genNodePtr = fact.getRef(node.getFilterExpression()) ;
            if (genNodePtr != null) {
              Columbus.Csharp.Asg.Nodes.Expression.ExpressionSyntax endNodeRef = (Columbus.Csharp.Asg.Nodes.Expression.ExpressionSyntax)(genNodePtr);
              foreach (var visitor in visitorList) {
                visitor.visitCatchFilterClauseSyntax_FilterExpression(node.Id, endNodeRef.Id);
              }

              clearStoppedVisitors();
              if(needPreorderStop)
                return;

              if ((!fact.IsFilterTurnedOn && !visitFilteredEdge) || (fact.getFilterState(endNodeRef.Id) == Filter.FilterState.NotFiltered) || (!originalFilterState && visitFilteredEdge)) {
                  endNodeRef.accept(this);
              }
              foreach (var visitor in visitorList) {
                visitor.visitEndCatchFilterClauseSyntax_FilterExpression(node.Id, endNodeRef.Id);
              }

              clearStoppedVisitors();
              if(needPreorderStop)
                return;

            }
        }

        public override void visit(Columbus.Csharp.Asg.Nodes.Structure.CatchFilterClauseSyntax node, bool callFirst = true){
          if (safeMode || visitCrossEdgeTree) {
            if (safeMode) {
              if (visitedNodes[(int)node.Id]) { // for safemode
                return;
              }
            }
            visitedNodes[(int)node.Id] = true;
          }

          foreach (var visitor in visitorList) {
            visitor.visit(node);
            incVisitorDepth(visitor);
          }

          clearStoppedVisitors();
          if(needPreorderStop)
            return;

          visitAllEdges(node, true);

          foreach (var visitor in visitorList) {
            decVisitorDepth(visitor);
            visitor.visitEnd(node);
          }

          clearStoppedVisitors();
        }

        /// <summary>
        /// It call the traversal for the edges
        /// </summary>
        /// <param name="node">[in] The node with own type</param>
        /// <param name="callVirtualBase">[in] This paramater is don't used just api copatibility used.</param>
        public void visitAllEdges(Columbus.Csharp.Asg.Nodes.Structure.ClassDeclarationSyntax node, bool callFirst = true){
            visitAllEdges((Columbus.Csharp.Asg.Nodes.Structure.TypeDeclarationSyntax)(node),false);
        }

        public override void visit(Columbus.Csharp.Asg.Nodes.Structure.ClassDeclarationSyntax node, bool callFirst = true){
          if (safeMode || visitCrossEdgeTree) {
            if (safeMode) {
              if (visitedNodes[(int)node.Id]) { // for safemode
                return;
              }
            }
            visitedNodes[(int)node.Id] = true;
          }

          foreach (var visitor in visitorList) {
            visitor.visit(node);
            incVisitorDepth(visitor);
          }

          clearStoppedVisitors();
          if(needPreorderStop)
            return;

          visitAllEdges(node, true);

          foreach (var visitor in visitorList) {
            decVisitorDepth(visitor);
            visitor.visitEnd(node);
          }

          clearStoppedVisitors();
        }

        /// <summary>
        /// It call the traversal for the edges
        /// </summary>
        /// <param name="node">[in] The node with own type</param>
        /// <param name="callVirtualBase">[in] This paramater is don't used just api copatibility used.</param>
        public void visitAllEdges(Columbus.Csharp.Asg.Nodes.Structure.ClassOrStructConstraintSyntax node, bool callFirst = true){
            visitAllEdges((Columbus.Csharp.Asg.Nodes.Structure.TypeParameterConstraintSyntax)(node),false);
        }

        public override void visit(Columbus.Csharp.Asg.Nodes.Structure.ClassOrStructConstraintSyntax node, bool callFirst = true){
          if (safeMode || visitCrossEdgeTree) {
            if (safeMode) {
              if (visitedNodes[(int)node.Id]) { // for safemode
                return;
              }
            }
            visitedNodes[(int)node.Id] = true;
          }

          foreach (var visitor in visitorList) {
            visitor.visit(node);
            incVisitorDepth(visitor);
          }

          clearStoppedVisitors();
          if(needPreorderStop)
            return;

          visitAllEdges(node, true);

          foreach (var visitor in visitorList) {
            decVisitorDepth(visitor);
            visitor.visitEnd(node);
          }

          clearStoppedVisitors();
        }

        /// <summary>
        /// It call the traversal for the edges
        /// </summary>
        /// <param name="node">[in] The node with own type</param>
        /// <param name="callVirtualBase">[in] This paramater is don't used just api copatibility used.</param>
        public void visitAllEdges(Columbus.Csharp.Asg.Nodes.Structure.CompilationUnitSyntax node, bool callFirst = true){
            visitAllEdges((Columbus.Csharp.Asg.Nodes.Base.Positioned)(node),false);


            // edge: AttributeLists
            ListIterator<Columbus.Csharp.Asg.Nodes.Structure.AttributeListSyntax> iteratorForAttributeLists = node.AttributeListsListIteratorBegin;
            while (iteratorForAttributeLists.getValue() != null) {
               Columbus.Csharp.Asg.Nodes.Structure.AttributeListSyntax endNodeRef = (Columbus.Csharp.Asg.Nodes.Structure.AttributeListSyntax)iteratorForAttributeLists.getValue();
              foreach (var visitor in visitorList) {
                visitor.visitCompilationUnitSyntax_AttributeLists(node.Id, endNodeRef.Id);
              }

              clearStoppedVisitors();
              if(needPreorderStop)
                return;

              if ((!fact.IsFilterTurnedOn && !visitFilteredEdge) || (fact.getFilterState(endNodeRef.Id) == Filter.FilterState.NotFiltered) || (!originalFilterState && visitFilteredEdge)) {
                  endNodeRef.accept(this);
              }
              foreach (var visitor in visitorList) {
                visitor.visitEndCompilationUnitSyntax_AttributeLists(node.Id, endNodeRef.Id);
              }

              clearStoppedVisitors();
              if(needPreorderStop)
                return;

            iteratorForAttributeLists = iteratorForAttributeLists.getNext();
            }

            // edge: Externs
            ListIterator<Columbus.Csharp.Asg.Nodes.Structure.ExternAliasDirectiveSyntax> iteratorForExterns = node.ExternsListIteratorBegin;
            while (iteratorForExterns.getValue() != null) {
               Columbus.Csharp.Asg.Nodes.Structure.ExternAliasDirectiveSyntax endNodeRef = (Columbus.Csharp.Asg.Nodes.Structure.ExternAliasDirectiveSyntax)iteratorForExterns.getValue();
              foreach (var visitor in visitorList) {
                visitor.visitCompilationUnitSyntax_Externs(node.Id, endNodeRef.Id);
              }

              clearStoppedVisitors();
              if(needPreorderStop)
                return;

              if ((!fact.IsFilterTurnedOn && !visitFilteredEdge) || (fact.getFilterState(endNodeRef.Id) == Filter.FilterState.NotFiltered) || (!originalFilterState && visitFilteredEdge)) {
                  endNodeRef.accept(this);
              }
              foreach (var visitor in visitorList) {
                visitor.visitEndCompilationUnitSyntax_Externs(node.Id, endNodeRef.Id);
              }

              clearStoppedVisitors();
              if(needPreorderStop)
                return;

            iteratorForExterns = iteratorForExterns.getNext();
            }

            // edge: Members
            ListIterator<Columbus.Csharp.Asg.Nodes.Structure.MemberDeclarationSyntax> iteratorForMembers = node.MembersListIteratorBegin;
            while (iteratorForMembers.getValue() != null) {
               Columbus.Csharp.Asg.Nodes.Structure.MemberDeclarationSyntax endNodeRef = (Columbus.Csharp.Asg.Nodes.Structure.MemberDeclarationSyntax)iteratorForMembers.getValue();
              foreach (var visitor in visitorList) {
                visitor.visitCompilationUnitSyntax_Members(node.Id, endNodeRef.Id);
              }

              clearStoppedVisitors();
              if(needPreorderStop)
                return;

              if ((!fact.IsFilterTurnedOn && !visitFilteredEdge) || (fact.getFilterState(endNodeRef.Id) == Filter.FilterState.NotFiltered) || (!originalFilterState && visitFilteredEdge)) {
                  endNodeRef.accept(this);
              }
              foreach (var visitor in visitorList) {
                visitor.visitEndCompilationUnitSyntax_Members(node.Id, endNodeRef.Id);
              }

              clearStoppedVisitors();
              if(needPreorderStop)
                return;

            iteratorForMembers = iteratorForMembers.getNext();
            }

            // edge: Usings
            ListIterator<Columbus.Csharp.Asg.Nodes.Structure.UsingDirectiveSyntax> iteratorForUsings = node.UsingsListIteratorBegin;
            while (iteratorForUsings.getValue() != null) {
               Columbus.Csharp.Asg.Nodes.Structure.UsingDirectiveSyntax endNodeRef = (Columbus.Csharp.Asg.Nodes.Structure.UsingDirectiveSyntax)iteratorForUsings.getValue();
              foreach (var visitor in visitorList) {
                visitor.visitCompilationUnitSyntax_Usings(node.Id, endNodeRef.Id);
              }

              clearStoppedVisitors();
              if(needPreorderStop)
                return;

              if ((!fact.IsFilterTurnedOn && !visitFilteredEdge) || (fact.getFilterState(endNodeRef.Id) == Filter.FilterState.NotFiltered) || (!originalFilterState && visitFilteredEdge)) {
                  endNodeRef.accept(this);
              }
              foreach (var visitor in visitorList) {
                visitor.visitEndCompilationUnitSyntax_Usings(node.Id, endNodeRef.Id);
              }

              clearStoppedVisitors();
              if(needPreorderStop)
                return;

            iteratorForUsings = iteratorForUsings.getNext();
            }
        }

        public override void visit(Columbus.Csharp.Asg.Nodes.Structure.CompilationUnitSyntax node, bool callFirst = true){
          if (safeMode || visitCrossEdgeTree) {
            if (safeMode) {
              if (visitedNodes[(int)node.Id]) { // for safemode
                return;
              }
            }
            visitedNodes[(int)node.Id] = true;
          }

          foreach (var visitor in visitorList) {
            visitor.visit(node);
            incVisitorDepth(visitor);
          }

          clearStoppedVisitors();
          if(needPreorderStop)
            return;

          visitAllEdges(node, true);

          foreach (var visitor in visitorList) {
            decVisitorDepth(visitor);
            visitor.visitEnd(node);
          }

          clearStoppedVisitors();
        }

        /// <summary>
        /// It call the traversal for the edges
        /// </summary>
        /// <param name="node">[in] The node with own type</param>
        /// <param name="callVirtualBase">[in] This paramater is don't used just api copatibility used.</param>
        public void visitAllEdges(Columbus.Csharp.Asg.Nodes.Structure.ConstantPatternSyntax node, bool callFirst = true){
            visitAllEdges((Columbus.Csharp.Asg.Nodes.Structure.PatternSyntax)(node),false);


            Columbus.Csharp.Asg.Nodes.Base.Base genNodePtr;
            // edge: Expression
            genNodePtr = fact.getRef(node.getExpression()) ;
            if (genNodePtr != null) {
              Columbus.Csharp.Asg.Nodes.Expression.ExpressionSyntax endNodeRef = (Columbus.Csharp.Asg.Nodes.Expression.ExpressionSyntax)(genNodePtr);
              foreach (var visitor in visitorList) {
                visitor.visitConstantPatternSyntax_Expression(node.Id, endNodeRef.Id);
              }

              clearStoppedVisitors();
              if(needPreorderStop)
                return;

              if ((!fact.IsFilterTurnedOn && !visitFilteredEdge) || (fact.getFilterState(endNodeRef.Id) == Filter.FilterState.NotFiltered) || (!originalFilterState && visitFilteredEdge)) {
                  endNodeRef.accept(this);
              }
              foreach (var visitor in visitorList) {
                visitor.visitEndConstantPatternSyntax_Expression(node.Id, endNodeRef.Id);
              }

              clearStoppedVisitors();
              if(needPreorderStop)
                return;

            }
        }

        public override void visit(Columbus.Csharp.Asg.Nodes.Structure.ConstantPatternSyntax node, bool callFirst = true){
          if (safeMode || visitCrossEdgeTree) {
            if (safeMode) {
              if (visitedNodes[(int)node.Id]) { // for safemode
                return;
              }
            }
            visitedNodes[(int)node.Id] = true;
          }

          foreach (var visitor in visitorList) {
            visitor.visit(node);
            incVisitorDepth(visitor);
          }

          clearStoppedVisitors();
          if(needPreorderStop)
            return;

          visitAllEdges(node, true);

          foreach (var visitor in visitorList) {
            decVisitorDepth(visitor);
            visitor.visitEnd(node);
          }

          clearStoppedVisitors();
        }

        /// <summary>
        /// It call the traversal for the edges
        /// </summary>
        /// <param name="node">[in] The node with own type</param>
        /// <param name="callVirtualBase">[in] This paramater is don't used just api copatibility used.</param>
        public void visitAllEdges(Columbus.Csharp.Asg.Nodes.Structure.ConstructorConstraintSyntax node, bool callFirst = true){
            visitAllEdges((Columbus.Csharp.Asg.Nodes.Structure.TypeParameterConstraintSyntax)(node),false);
        }

        public override void visit(Columbus.Csharp.Asg.Nodes.Structure.ConstructorConstraintSyntax node, bool callFirst = true){
          if (safeMode || visitCrossEdgeTree) {
            if (safeMode) {
              if (visitedNodes[(int)node.Id]) { // for safemode
                return;
              }
            }
            visitedNodes[(int)node.Id] = true;
          }

          foreach (var visitor in visitorList) {
            visitor.visit(node);
            incVisitorDepth(visitor);
          }

          clearStoppedVisitors();
          if(needPreorderStop)
            return;

          visitAllEdges(node, true);

          foreach (var visitor in visitorList) {
            decVisitorDepth(visitor);
            visitor.visitEnd(node);
          }

          clearStoppedVisitors();
        }

        /// <summary>
        /// It call the traversal for the edges
        /// </summary>
        /// <param name="node">[in] The node with own type</param>
        /// <param name="callVirtualBase">[in] This paramater is don't used just api copatibility used.</param>
        public void visitAllEdges(Columbus.Csharp.Asg.Nodes.Structure.ConstructorDeclarationSyntax node, bool callFirst = true){
            visitAllEdges((Columbus.Csharp.Asg.Nodes.Structure.BaseMethodDeclarationSyntax)(node),false);


            Columbus.Csharp.Asg.Nodes.Base.Base genNodePtr;
            // edge: Initializer
            genNodePtr = fact.getRef(node.getInitializer()) ;
            if (genNodePtr != null) {
              Columbus.Csharp.Asg.Nodes.Structure.ConstructorInitializerSyntax endNodeRef = (Columbus.Csharp.Asg.Nodes.Structure.ConstructorInitializerSyntax)(genNodePtr);
              foreach (var visitor in visitorList) {
                visitor.visitConstructorDeclarationSyntax_Initializer(node.Id, endNodeRef.Id);
              }

              clearStoppedVisitors();
              if(needPreorderStop)
                return;

              if ((!fact.IsFilterTurnedOn && !visitFilteredEdge) || (fact.getFilterState(endNodeRef.Id) == Filter.FilterState.NotFiltered) || (!originalFilterState && visitFilteredEdge)) {
                  endNodeRef.accept(this);
              }
              foreach (var visitor in visitorList) {
                visitor.visitEndConstructorDeclarationSyntax_Initializer(node.Id, endNodeRef.Id);
              }

              clearStoppedVisitors();
              if(needPreorderStop)
                return;

            }
        }

        public override void visit(Columbus.Csharp.Asg.Nodes.Structure.ConstructorDeclarationSyntax node, bool callFirst = true){
          if (safeMode || visitCrossEdgeTree) {
            if (safeMode) {
              if (visitedNodes[(int)node.Id]) { // for safemode
                return;
              }
            }
            visitedNodes[(int)node.Id] = true;
          }

          foreach (var visitor in visitorList) {
            visitor.visit(node);
            incVisitorDepth(visitor);
          }

          clearStoppedVisitors();
          if(needPreorderStop)
            return;

          visitAllEdges(node, true);

          foreach (var visitor in visitorList) {
            decVisitorDepth(visitor);
            visitor.visitEnd(node);
          }

          clearStoppedVisitors();
        }

        /// <summary>
        /// It call the traversal for the edges
        /// </summary>
        /// <param name="node">[in] The node with own type</param>
        /// <param name="callVirtualBase">[in] This paramater is don't used just api copatibility used.</param>
        public void visitAllEdges(Columbus.Csharp.Asg.Nodes.Structure.ConstructorInitializerSyntax node, bool callFirst = true){
            visitAllEdges((Columbus.Csharp.Asg.Nodes.Base.Positioned)(node),false);


            Columbus.Csharp.Asg.Nodes.Base.Base genNodePtr;
            // edge: ArgumentList
            genNodePtr = fact.getRef(node.getArgumentList()) ;
            if (genNodePtr != null) {
              Columbus.Csharp.Asg.Nodes.Structure.ArgumentListSyntax endNodeRef = (Columbus.Csharp.Asg.Nodes.Structure.ArgumentListSyntax)(genNodePtr);
              foreach (var visitor in visitorList) {
                visitor.visitConstructorInitializerSyntax_ArgumentList(node.Id, endNodeRef.Id);
              }

              clearStoppedVisitors();
              if(needPreorderStop)
                return;

              if ((!fact.IsFilterTurnedOn && !visitFilteredEdge) || (fact.getFilterState(endNodeRef.Id) == Filter.FilterState.NotFiltered) || (!originalFilterState && visitFilteredEdge)) {
                  endNodeRef.accept(this);
              }
              foreach (var visitor in visitorList) {
                visitor.visitEndConstructorInitializerSyntax_ArgumentList(node.Id, endNodeRef.Id);
              }

              clearStoppedVisitors();
              if(needPreorderStop)
                return;

            }

            // edge: ConstructorCall
            genNodePtr = fact.getRef(node.getConstructorCall()) ;
            if (genNodePtr != null) {
              Columbus.Csharp.Asg.Nodes.Structure.ConstructorDeclarationSyntax endNodeRef = (Columbus.Csharp.Asg.Nodes.Structure.ConstructorDeclarationSyntax)(genNodePtr);
              foreach (var visitor in visitorList) {
                visitor.visitConstructorInitializerSyntax_ConstructorCall(node.Id, endNodeRef.Id);
              }

              clearStoppedVisitors();
              if(needPreorderStop)
                return;

              if ((!fact.IsFilterTurnedOn && !visitFilteredEdge) || (fact.getFilterState(endNodeRef.Id) == Filter.FilterState.NotFiltered) || (!originalFilterState && visitFilteredEdge)) {
                  if (apRoot != null) {
                    if (visitCrossEdgeTree) {
                      unvisitedNodes[(int)endNodeRef.Id] = true;
                    }
                  }
                  if (traversaldCrossEdges[(int)Types.EdgeKind.edkConstructorInitializerSyntax_ConstructorCall]) {
                    endNodeRef.accept(this);
                  }
              }
              foreach (var visitor in visitorList) {
                visitor.visitEndConstructorInitializerSyntax_ConstructorCall(node.Id, endNodeRef.Id);
              }

              clearStoppedVisitors();
              if(needPreorderStop)
                return;

            }
        }

        public override void visit(Columbus.Csharp.Asg.Nodes.Structure.ConstructorInitializerSyntax node, bool callFirst = true){
          if (safeMode || visitCrossEdgeTree) {
            if (safeMode) {
              if (visitedNodes[(int)node.Id]) { // for safemode
                return;
              }
            }
            visitedNodes[(int)node.Id] = true;
          }

          foreach (var visitor in visitorList) {
            visitor.visit(node);
            incVisitorDepth(visitor);
          }

          clearStoppedVisitors();
          if(needPreorderStop)
            return;

          visitAllEdges(node, true);

          foreach (var visitor in visitorList) {
            decVisitorDepth(visitor);
            visitor.visitEnd(node);
          }

          clearStoppedVisitors();
        }

        /// <summary>
        /// It call the traversal for the edges
        /// </summary>
        /// <param name="node">[in] The node with own type</param>
        /// <param name="callVirtualBase">[in] This paramater is don't used just api copatibility used.</param>
        public void visitAllEdges(Columbus.Csharp.Asg.Nodes.Structure.ConversionOperatorDeclarationSyntax node, bool callFirst = true){
            visitAllEdges((Columbus.Csharp.Asg.Nodes.Structure.BaseMethodDeclarationSyntax)(node),false);


            Columbus.Csharp.Asg.Nodes.Base.Base genNodePtr;
            // edge: Type
            genNodePtr = fact.getRef(node.getType()) ;
            if (genNodePtr != null) {
              Columbus.Csharp.Asg.Nodes.Expression.TypeSyntax endNodeRef = (Columbus.Csharp.Asg.Nodes.Expression.TypeSyntax)(genNodePtr);
              foreach (var visitor in visitorList) {
                visitor.visitConversionOperatorDeclarationSyntax_Type(node.Id, endNodeRef.Id);
              }

              clearStoppedVisitors();
              if(needPreorderStop)
                return;

              if ((!fact.IsFilterTurnedOn && !visitFilteredEdge) || (fact.getFilterState(endNodeRef.Id) == Filter.FilterState.NotFiltered) || (!originalFilterState && visitFilteredEdge)) {
                  endNodeRef.accept(this);
              }
              foreach (var visitor in visitorList) {
                visitor.visitEndConversionOperatorDeclarationSyntax_Type(node.Id, endNodeRef.Id);
              }

              clearStoppedVisitors();
              if(needPreorderStop)
                return;

            }
        }

        public override void visit(Columbus.Csharp.Asg.Nodes.Structure.ConversionOperatorDeclarationSyntax node, bool callFirst = true){
          if (safeMode || visitCrossEdgeTree) {
            if (safeMode) {
              if (visitedNodes[(int)node.Id]) { // for safemode
                return;
              }
            }
            visitedNodes[(int)node.Id] = true;
          }

          foreach (var visitor in visitorList) {
            visitor.visit(node);
            incVisitorDepth(visitor);
          }

          clearStoppedVisitors();
          if(needPreorderStop)
            return;

          visitAllEdges(node, true);

          foreach (var visitor in visitorList) {
            decVisitorDepth(visitor);
            visitor.visitEnd(node);
          }

          clearStoppedVisitors();
        }

        /// <summary>
        /// It call the traversal for the edges
        /// </summary>
        /// <param name="node">[in] The node with own type</param>
        /// <param name="callVirtualBase">[in] This paramater is don't used just api copatibility used.</param>
        public void visitAllEdges(Columbus.Csharp.Asg.Nodes.Structure.ConversionOperatorMemberCrefSyntax node, bool callFirst = true){
            visitAllEdges((Columbus.Csharp.Asg.Nodes.Structure.MemberCrefSyntax)(node),false);


            Columbus.Csharp.Asg.Nodes.Base.Base genNodePtr;
            // edge: Parameters
            genNodePtr = fact.getRef(node.getParameters()) ;
            if (genNodePtr != null) {
              Columbus.Csharp.Asg.Nodes.Structure.CrefParameterListSyntax endNodeRef = (Columbus.Csharp.Asg.Nodes.Structure.CrefParameterListSyntax)(genNodePtr);
              foreach (var visitor in visitorList) {
                visitor.visitConversionOperatorMemberCrefSyntax_Parameters(node.Id, endNodeRef.Id);
              }

              clearStoppedVisitors();
              if(needPreorderStop)
                return;

              if ((!fact.IsFilterTurnedOn && !visitFilteredEdge) || (fact.getFilterState(endNodeRef.Id) == Filter.FilterState.NotFiltered) || (!originalFilterState && visitFilteredEdge)) {
                  endNodeRef.accept(this);
              }
              foreach (var visitor in visitorList) {
                visitor.visitEndConversionOperatorMemberCrefSyntax_Parameters(node.Id, endNodeRef.Id);
              }

              clearStoppedVisitors();
              if(needPreorderStop)
                return;

            }

            // edge: Type
            genNodePtr = fact.getRef(node.getType()) ;
            if (genNodePtr != null) {
              Columbus.Csharp.Asg.Nodes.Expression.TypeSyntax endNodeRef = (Columbus.Csharp.Asg.Nodes.Expression.TypeSyntax)(genNodePtr);
              foreach (var visitor in visitorList) {
                visitor.visitConversionOperatorMemberCrefSyntax_Type(node.Id, endNodeRef.Id);
              }

              clearStoppedVisitors();
              if(needPreorderStop)
                return;

              if ((!fact.IsFilterTurnedOn && !visitFilteredEdge) || (fact.getFilterState(endNodeRef.Id) == Filter.FilterState.NotFiltered) || (!originalFilterState && visitFilteredEdge)) {
                  endNodeRef.accept(this);
              }
              foreach (var visitor in visitorList) {
                visitor.visitEndConversionOperatorMemberCrefSyntax_Type(node.Id, endNodeRef.Id);
              }

              clearStoppedVisitors();
              if(needPreorderStop)
                return;

            }
        }

        public override void visit(Columbus.Csharp.Asg.Nodes.Structure.ConversionOperatorMemberCrefSyntax node, bool callFirst = true){
          if (safeMode || visitCrossEdgeTree) {
            if (safeMode) {
              if (visitedNodes[(int)node.Id]) { // for safemode
                return;
              }
            }
            visitedNodes[(int)node.Id] = true;
          }

          foreach (var visitor in visitorList) {
            visitor.visit(node);
            incVisitorDepth(visitor);
          }

          clearStoppedVisitors();
          if(needPreorderStop)
            return;

          visitAllEdges(node, true);

          foreach (var visitor in visitorList) {
            decVisitorDepth(visitor);
            visitor.visitEnd(node);
          }

          clearStoppedVisitors();
        }

        /// <summary>
        /// It call the traversal for the edges
        /// </summary>
        /// <param name="node">[in] The node with own type</param>
        /// <param name="callVirtualBase">[in] This paramater is don't used just api copatibility used.</param>
        public void visitAllEdges(Columbus.Csharp.Asg.Nodes.Structure.CrefBracketedParameterListSyntax node, bool callFirst = true){
            visitAllEdges((Columbus.Csharp.Asg.Nodes.Structure.BaseCrefParameterListSyntax)(node),false);
        }

        public override void visit(Columbus.Csharp.Asg.Nodes.Structure.CrefBracketedParameterListSyntax node, bool callFirst = true){
          if (safeMode || visitCrossEdgeTree) {
            if (safeMode) {
              if (visitedNodes[(int)node.Id]) { // for safemode
                return;
              }
            }
            visitedNodes[(int)node.Id] = true;
          }

          foreach (var visitor in visitorList) {
            visitor.visit(node);
            incVisitorDepth(visitor);
          }

          clearStoppedVisitors();
          if(needPreorderStop)
            return;

          visitAllEdges(node, true);

          foreach (var visitor in visitorList) {
            decVisitorDepth(visitor);
            visitor.visitEnd(node);
          }

          clearStoppedVisitors();
        }

        /// <summary>
        /// It call the traversal for the edges
        /// </summary>
        /// <param name="node">[in] The node with own type</param>
        /// <param name="callVirtualBase">[in] This paramater is don't used just api copatibility used.</param>
        public void visitAllEdges(Columbus.Csharp.Asg.Nodes.Structure.CrefParameterListSyntax node, bool callFirst = true){
            visitAllEdges((Columbus.Csharp.Asg.Nodes.Structure.BaseCrefParameterListSyntax)(node),false);
        }

        public override void visit(Columbus.Csharp.Asg.Nodes.Structure.CrefParameterListSyntax node, bool callFirst = true){
          if (safeMode || visitCrossEdgeTree) {
            if (safeMode) {
              if (visitedNodes[(int)node.Id]) { // for safemode
                return;
              }
            }
            visitedNodes[(int)node.Id] = true;
          }

          foreach (var visitor in visitorList) {
            visitor.visit(node);
            incVisitorDepth(visitor);
          }

          clearStoppedVisitors();
          if(needPreorderStop)
            return;

          visitAllEdges(node, true);

          foreach (var visitor in visitorList) {
            decVisitorDepth(visitor);
            visitor.visitEnd(node);
          }

          clearStoppedVisitors();
        }

        /// <summary>
        /// It call the traversal for the edges
        /// </summary>
        /// <param name="node">[in] The node with own type</param>
        /// <param name="callVirtualBase">[in] This paramater is don't used just api copatibility used.</param>
        public void visitAllEdges(Columbus.Csharp.Asg.Nodes.Structure.CrefParameterSyntax node, bool callFirst = true){
            visitAllEdges((Columbus.Csharp.Asg.Nodes.Base.Positioned)(node),false);


            Columbus.Csharp.Asg.Nodes.Base.Base genNodePtr;
            // edge: Type
            genNodePtr = fact.getRef(node.getType()) ;
            if (genNodePtr != null) {
              Columbus.Csharp.Asg.Nodes.Expression.TypeSyntax endNodeRef = (Columbus.Csharp.Asg.Nodes.Expression.TypeSyntax)(genNodePtr);
              foreach (var visitor in visitorList) {
                visitor.visitCrefParameterSyntax_Type(node.Id, endNodeRef.Id);
              }

              clearStoppedVisitors();
              if(needPreorderStop)
                return;

              if ((!fact.IsFilterTurnedOn && !visitFilteredEdge) || (fact.getFilterState(endNodeRef.Id) == Filter.FilterState.NotFiltered) || (!originalFilterState && visitFilteredEdge)) {
                  endNodeRef.accept(this);
              }
              foreach (var visitor in visitorList) {
                visitor.visitEndCrefParameterSyntax_Type(node.Id, endNodeRef.Id);
              }

              clearStoppedVisitors();
              if(needPreorderStop)
                return;

            }
        }

        public override void visit(Columbus.Csharp.Asg.Nodes.Structure.CrefParameterSyntax node, bool callFirst = true){
          if (safeMode || visitCrossEdgeTree) {
            if (safeMode) {
              if (visitedNodes[(int)node.Id]) { // for safemode
                return;
              }
            }
            visitedNodes[(int)node.Id] = true;
          }

          foreach (var visitor in visitorList) {
            visitor.visit(node);
            incVisitorDepth(visitor);
          }

          clearStoppedVisitors();
          if(needPreorderStop)
            return;

          visitAllEdges(node, true);

          foreach (var visitor in visitorList) {
            decVisitorDepth(visitor);
            visitor.visitEnd(node);
          }

          clearStoppedVisitors();
        }

        /// <summary>
        /// It call the traversal for the edges
        /// </summary>
        /// <param name="node">[in] The node with own type</param>
        /// <param name="callVirtualBase">[in] This paramater is don't used just api copatibility used.</param>
        public void visitAllEdges(Columbus.Csharp.Asg.Nodes.Structure.CrefSyntax node, bool callFirst = true){
            visitAllEdges((Columbus.Csharp.Asg.Nodes.Base.Positioned)(node),false);
        }

        /// <summary>
        /// It call the traversal for the edges
        /// </summary>
        /// <param name="node">[in] The node with own type</param>
        /// <param name="callVirtualBase">[in] This paramater is don't used just api copatibility used.</param>
        public void visitAllEdges(Columbus.Csharp.Asg.Nodes.Structure.DeclarationPatternSyntax node, bool callFirst = true){
            visitAllEdges((Columbus.Csharp.Asg.Nodes.Structure.PatternSyntax)(node),false);


            Columbus.Csharp.Asg.Nodes.Base.Base genNodePtr;
            // edge: Designation
            genNodePtr = fact.getRef(node.getDesignation()) ;
            if (genNodePtr != null) {
              Columbus.Csharp.Asg.Nodes.Structure.VariableDesignationSyntax endNodeRef = (Columbus.Csharp.Asg.Nodes.Structure.VariableDesignationSyntax)(genNodePtr);
              foreach (var visitor in visitorList) {
                visitor.visitDeclarationPatternSyntax_Designation(node.Id, endNodeRef.Id);
              }

              clearStoppedVisitors();
              if(needPreorderStop)
                return;

              if ((!fact.IsFilterTurnedOn && !visitFilteredEdge) || (fact.getFilterState(endNodeRef.Id) == Filter.FilterState.NotFiltered) || (!originalFilterState && visitFilteredEdge)) {
                  endNodeRef.accept(this);
              }
              foreach (var visitor in visitorList) {
                visitor.visitEndDeclarationPatternSyntax_Designation(node.Id, endNodeRef.Id);
              }

              clearStoppedVisitors();
              if(needPreorderStop)
                return;

            }

            // edge: Type
            genNodePtr = fact.getRef(node.getType()) ;
            if (genNodePtr != null) {
              Columbus.Csharp.Asg.Nodes.Expression.TypeSyntax endNodeRef = (Columbus.Csharp.Asg.Nodes.Expression.TypeSyntax)(genNodePtr);
              foreach (var visitor in visitorList) {
                visitor.visitDeclarationPatternSyntax_Type(node.Id, endNodeRef.Id);
              }

              clearStoppedVisitors();
              if(needPreorderStop)
                return;

              if ((!fact.IsFilterTurnedOn && !visitFilteredEdge) || (fact.getFilterState(endNodeRef.Id) == Filter.FilterState.NotFiltered) || (!originalFilterState && visitFilteredEdge)) {
                  endNodeRef.accept(this);
              }
              foreach (var visitor in visitorList) {
                visitor.visitEndDeclarationPatternSyntax_Type(node.Id, endNodeRef.Id);
              }

              clearStoppedVisitors();
              if(needPreorderStop)
                return;

            }
        }

        public override void visit(Columbus.Csharp.Asg.Nodes.Structure.DeclarationPatternSyntax node, bool callFirst = true){
          if (safeMode || visitCrossEdgeTree) {
            if (safeMode) {
              if (visitedNodes[(int)node.Id]) { // for safemode
                return;
              }
            }
            visitedNodes[(int)node.Id] = true;
          }

          foreach (var visitor in visitorList) {
            visitor.visit(node);
            incVisitorDepth(visitor);
          }

          clearStoppedVisitors();
          if(needPreorderStop)
            return;

          visitAllEdges(node, true);

          foreach (var visitor in visitorList) {
            decVisitorDepth(visitor);
            visitor.visitEnd(node);
          }

          clearStoppedVisitors();
        }

        /// <summary>
        /// It call the traversal for the edges
        /// </summary>
        /// <param name="node">[in] The node with own type</param>
        /// <param name="callVirtualBase">[in] This paramater is don't used just api copatibility used.</param>
        public void visitAllEdges(Columbus.Csharp.Asg.Nodes.Structure.DefaultSwitchLabelSyntax node, bool callFirst = true){
            visitAllEdges((Columbus.Csharp.Asg.Nodes.Structure.SwitchLabelSyntax)(node),false);
        }

        public override void visit(Columbus.Csharp.Asg.Nodes.Structure.DefaultSwitchLabelSyntax node, bool callFirst = true){
          if (safeMode || visitCrossEdgeTree) {
            if (safeMode) {
              if (visitedNodes[(int)node.Id]) { // for safemode
                return;
              }
            }
            visitedNodes[(int)node.Id] = true;
          }

          foreach (var visitor in visitorList) {
            visitor.visit(node);
            incVisitorDepth(visitor);
          }

          clearStoppedVisitors();
          if(needPreorderStop)
            return;

          visitAllEdges(node, true);

          foreach (var visitor in visitorList) {
            decVisitorDepth(visitor);
            visitor.visitEnd(node);
          }

          clearStoppedVisitors();
        }

        /// <summary>
        /// It call the traversal for the edges
        /// </summary>
        /// <param name="node">[in] The node with own type</param>
        /// <param name="callVirtualBase">[in] This paramater is don't used just api copatibility used.</param>
        public void visitAllEdges(Columbus.Csharp.Asg.Nodes.Structure.DelegateDeclarationSyntax node, bool callFirst = true){
            visitAllEdges((Columbus.Csharp.Asg.Nodes.Structure.MemberDeclarationSyntax)(node),false);


            // edge: AttributeLists
            ListIterator<Columbus.Csharp.Asg.Nodes.Structure.AttributeListSyntax> iteratorForAttributeLists = node.AttributeListsListIteratorBegin;
            while (iteratorForAttributeLists.getValue() != null) {
               Columbus.Csharp.Asg.Nodes.Structure.AttributeListSyntax endNodeRef = (Columbus.Csharp.Asg.Nodes.Structure.AttributeListSyntax)iteratorForAttributeLists.getValue();
              foreach (var visitor in visitorList) {
                visitor.visitDelegateDeclarationSyntax_AttributeLists(node.Id, endNodeRef.Id);
              }

              clearStoppedVisitors();
              if(needPreorderStop)
                return;

              if ((!fact.IsFilterTurnedOn && !visitFilteredEdge) || (fact.getFilterState(endNodeRef.Id) == Filter.FilterState.NotFiltered) || (!originalFilterState && visitFilteredEdge)) {
                  endNodeRef.accept(this);
              }
              foreach (var visitor in visitorList) {
                visitor.visitEndDelegateDeclarationSyntax_AttributeLists(node.Id, endNodeRef.Id);
              }

              clearStoppedVisitors();
              if(needPreorderStop)
                return;

            iteratorForAttributeLists = iteratorForAttributeLists.getNext();
            }

            // edge: ConstraintClauses
            ListIterator<Columbus.Csharp.Asg.Nodes.Structure.TypeParameterConstraintClauseSyntax> iteratorForConstraintClauses = node.ConstraintClausesListIteratorBegin;
            while (iteratorForConstraintClauses.getValue() != null) {
               Columbus.Csharp.Asg.Nodes.Structure.TypeParameterConstraintClauseSyntax endNodeRef = (Columbus.Csharp.Asg.Nodes.Structure.TypeParameterConstraintClauseSyntax)iteratorForConstraintClauses.getValue();
              foreach (var visitor in visitorList) {
                visitor.visitDelegateDeclarationSyntax_ConstraintClauses(node.Id, endNodeRef.Id);
              }

              clearStoppedVisitors();
              if(needPreorderStop)
                return;

              if ((!fact.IsFilterTurnedOn && !visitFilteredEdge) || (fact.getFilterState(endNodeRef.Id) == Filter.FilterState.NotFiltered) || (!originalFilterState && visitFilteredEdge)) {
                  endNodeRef.accept(this);
              }
              foreach (var visitor in visitorList) {
                visitor.visitEndDelegateDeclarationSyntax_ConstraintClauses(node.Id, endNodeRef.Id);
              }

              clearStoppedVisitors();
              if(needPreorderStop)
                return;

            iteratorForConstraintClauses = iteratorForConstraintClauses.getNext();
            }

            Columbus.Csharp.Asg.Nodes.Base.Base genNodePtr;
            // edge: ParameterList
            genNodePtr = fact.getRef(node.getParameterList()) ;
            if (genNodePtr != null) {
              Columbus.Csharp.Asg.Nodes.Structure.ParameterListSyntax endNodeRef = (Columbus.Csharp.Asg.Nodes.Structure.ParameterListSyntax)(genNodePtr);
              foreach (var visitor in visitorList) {
                visitor.visitDelegateDeclarationSyntax_ParameterList(node.Id, endNodeRef.Id);
              }

              clearStoppedVisitors();
              if(needPreorderStop)
                return;

              if ((!fact.IsFilterTurnedOn && !visitFilteredEdge) || (fact.getFilterState(endNodeRef.Id) == Filter.FilterState.NotFiltered) || (!originalFilterState && visitFilteredEdge)) {
                  endNodeRef.accept(this);
              }
              foreach (var visitor in visitorList) {
                visitor.visitEndDelegateDeclarationSyntax_ParameterList(node.Id, endNodeRef.Id);
              }

              clearStoppedVisitors();
              if(needPreorderStop)
                return;

            }

            // edge: ReturnType
            genNodePtr = fact.getRef(node.getReturnType()) ;
            if (genNodePtr != null) {
              Columbus.Csharp.Asg.Nodes.Expression.TypeSyntax endNodeRef = (Columbus.Csharp.Asg.Nodes.Expression.TypeSyntax)(genNodePtr);
              foreach (var visitor in visitorList) {
                visitor.visitDelegateDeclarationSyntax_ReturnType(node.Id, endNodeRef.Id);
              }

              clearStoppedVisitors();
              if(needPreorderStop)
                return;

              if ((!fact.IsFilterTurnedOn && !visitFilteredEdge) || (fact.getFilterState(endNodeRef.Id) == Filter.FilterState.NotFiltered) || (!originalFilterState && visitFilteredEdge)) {
                  endNodeRef.accept(this);
              }
              foreach (var visitor in visitorList) {
                visitor.visitEndDelegateDeclarationSyntax_ReturnType(node.Id, endNodeRef.Id);
              }

              clearStoppedVisitors();
              if(needPreorderStop)
                return;

            }
        }

        public override void visit(Columbus.Csharp.Asg.Nodes.Structure.DelegateDeclarationSyntax node, bool callFirst = true){
          if (safeMode || visitCrossEdgeTree) {
            if (safeMode) {
              if (visitedNodes[(int)node.Id]) { // for safemode
                return;
              }
            }
            visitedNodes[(int)node.Id] = true;
          }

          foreach (var visitor in visitorList) {
            visitor.visit(node);
            incVisitorDepth(visitor);
          }

          clearStoppedVisitors();
          if(needPreorderStop)
            return;

          visitAllEdges(node, true);

          foreach (var visitor in visitorList) {
            decVisitorDepth(visitor);
            visitor.visitEnd(node);
          }

          clearStoppedVisitors();
        }

        /// <summary>
        /// It call the traversal for the edges
        /// </summary>
        /// <param name="node">[in] The node with own type</param>
        /// <param name="callVirtualBase">[in] This paramater is don't used just api copatibility used.</param>
        public void visitAllEdges(Columbus.Csharp.Asg.Nodes.Structure.DestructorDeclarationSyntax node, bool callFirst = true){
            visitAllEdges((Columbus.Csharp.Asg.Nodes.Structure.BaseMethodDeclarationSyntax)(node),false);
        }

        public override void visit(Columbus.Csharp.Asg.Nodes.Structure.DestructorDeclarationSyntax node, bool callFirst = true){
          if (safeMode || visitCrossEdgeTree) {
            if (safeMode) {
              if (visitedNodes[(int)node.Id]) { // for safemode
                return;
              }
            }
            visitedNodes[(int)node.Id] = true;
          }

          foreach (var visitor in visitorList) {
            visitor.visit(node);
            incVisitorDepth(visitor);
          }

          clearStoppedVisitors();
          if(needPreorderStop)
            return;

          visitAllEdges(node, true);

          foreach (var visitor in visitorList) {
            decVisitorDepth(visitor);
            visitor.visitEnd(node);
          }

          clearStoppedVisitors();
        }

        /// <summary>
        /// It call the traversal for the edges
        /// </summary>
        /// <param name="node">[in] The node with own type</param>
        /// <param name="callVirtualBase">[in] This paramater is don't used just api copatibility used.</param>
        public void visitAllEdges(Columbus.Csharp.Asg.Nodes.Structure.DiscardDesignationSyntax node, bool callFirst = true){
            visitAllEdges((Columbus.Csharp.Asg.Nodes.Structure.VariableDesignationSyntax)(node),false);
        }

        public override void visit(Columbus.Csharp.Asg.Nodes.Structure.DiscardDesignationSyntax node, bool callFirst = true){
          if (safeMode || visitCrossEdgeTree) {
            if (safeMode) {
              if (visitedNodes[(int)node.Id]) { // for safemode
                return;
              }
            }
            visitedNodes[(int)node.Id] = true;
          }

          foreach (var visitor in visitorList) {
            visitor.visit(node);
            incVisitorDepth(visitor);
          }

          clearStoppedVisitors();
          if(needPreorderStop)
            return;

          visitAllEdges(node, true);

          foreach (var visitor in visitorList) {
            decVisitorDepth(visitor);
            visitor.visitEnd(node);
          }

          clearStoppedVisitors();
        }

        /// <summary>
        /// It call the traversal for the edges
        /// </summary>
        /// <param name="node">[in] The node with own type</param>
        /// <param name="callVirtualBase">[in] This paramater is don't used just api copatibility used.</param>
        public void visitAllEdges(Columbus.Csharp.Asg.Nodes.Structure.DiscardPatternSyntax node, bool callFirst = true){
            visitAllEdges((Columbus.Csharp.Asg.Nodes.Structure.PatternSyntax)(node),false);
        }

        public override void visit(Columbus.Csharp.Asg.Nodes.Structure.DiscardPatternSyntax node, bool callFirst = true){
          if (safeMode || visitCrossEdgeTree) {
            if (safeMode) {
              if (visitedNodes[(int)node.Id]) { // for safemode
                return;
              }
            }
            visitedNodes[(int)node.Id] = true;
          }

          foreach (var visitor in visitorList) {
            visitor.visit(node);
            incVisitorDepth(visitor);
          }

          clearStoppedVisitors();
          if(needPreorderStop)
            return;

          visitAllEdges(node, true);

          foreach (var visitor in visitorList) {
            decVisitorDepth(visitor);
            visitor.visitEnd(node);
          }

          clearStoppedVisitors();
        }

        /// <summary>
        /// It call the traversal for the edges
        /// </summary>
        /// <param name="node">[in] The node with own type</param>
        /// <param name="callVirtualBase">[in] This paramater is don't used just api copatibility used.</param>
        public void visitAllEdges(Columbus.Csharp.Asg.Nodes.Structure.ElseClauseSyntax node, bool callFirst = true){
            visitAllEdges((Columbus.Csharp.Asg.Nodes.Base.Positioned)(node),false);


            Columbus.Csharp.Asg.Nodes.Base.Base genNodePtr;
            // edge: Statement
            genNodePtr = fact.getRef(node.getStatement()) ;
            if (genNodePtr != null) {
              Columbus.Csharp.Asg.Nodes.Statement.StatementSyntax endNodeRef = (Columbus.Csharp.Asg.Nodes.Statement.StatementSyntax)(genNodePtr);
              foreach (var visitor in visitorList) {
                visitor.visitElseClauseSyntax_Statement(node.Id, endNodeRef.Id);
              }

              clearStoppedVisitors();
              if(needPreorderStop)
                return;

              if ((!fact.IsFilterTurnedOn && !visitFilteredEdge) || (fact.getFilterState(endNodeRef.Id) == Filter.FilterState.NotFiltered) || (!originalFilterState && visitFilteredEdge)) {
                  endNodeRef.accept(this);
              }
              foreach (var visitor in visitorList) {
                visitor.visitEndElseClauseSyntax_Statement(node.Id, endNodeRef.Id);
              }

              clearStoppedVisitors();
              if(needPreorderStop)
                return;

            }
        }

        public override void visit(Columbus.Csharp.Asg.Nodes.Structure.ElseClauseSyntax node, bool callFirst = true){
          if (safeMode || visitCrossEdgeTree) {
            if (safeMode) {
              if (visitedNodes[(int)node.Id]) { // for safemode
                return;
              }
            }
            visitedNodes[(int)node.Id] = true;
          }

          foreach (var visitor in visitorList) {
            visitor.visit(node);
            incVisitorDepth(visitor);
          }

          clearStoppedVisitors();
          if(needPreorderStop)
            return;

          visitAllEdges(node, true);

          foreach (var visitor in visitorList) {
            decVisitorDepth(visitor);
            visitor.visitEnd(node);
          }

          clearStoppedVisitors();
        }

        /// <summary>
        /// It call the traversal for the edges
        /// </summary>
        /// <param name="node">[in] The node with own type</param>
        /// <param name="callVirtualBase">[in] This paramater is don't used just api copatibility used.</param>
        public void visitAllEdges(Columbus.Csharp.Asg.Nodes.Structure.EnumDeclarationSyntax node, bool callFirst = true){
            visitAllEdges((Columbus.Csharp.Asg.Nodes.Structure.BaseTypeDeclarationSyntax)(node),false);


            // edge: Members
            ListIterator<Columbus.Csharp.Asg.Nodes.Structure.EnumMemberDeclarationSyntax> iteratorForMembers = node.MembersListIteratorBegin;
            while (iteratorForMembers.getValue() != null) {
               Columbus.Csharp.Asg.Nodes.Structure.EnumMemberDeclarationSyntax endNodeRef = (Columbus.Csharp.Asg.Nodes.Structure.EnumMemberDeclarationSyntax)iteratorForMembers.getValue();
              foreach (var visitor in visitorList) {
                visitor.visitEnumDeclarationSyntax_Members(node.Id, endNodeRef.Id);
              }

              clearStoppedVisitors();
              if(needPreorderStop)
                return;

              if ((!fact.IsFilterTurnedOn && !visitFilteredEdge) || (fact.getFilterState(endNodeRef.Id) == Filter.FilterState.NotFiltered) || (!originalFilterState && visitFilteredEdge)) {
                  endNodeRef.accept(this);
              }
              foreach (var visitor in visitorList) {
                visitor.visitEndEnumDeclarationSyntax_Members(node.Id, endNodeRef.Id);
              }

              clearStoppedVisitors();
              if(needPreorderStop)
                return;

            iteratorForMembers = iteratorForMembers.getNext();
            }
        }

        public override void visit(Columbus.Csharp.Asg.Nodes.Structure.EnumDeclarationSyntax node, bool callFirst = true){
          if (safeMode || visitCrossEdgeTree) {
            if (safeMode) {
              if (visitedNodes[(int)node.Id]) { // for safemode
                return;
              }
            }
            visitedNodes[(int)node.Id] = true;
          }

          foreach (var visitor in visitorList) {
            visitor.visit(node);
            incVisitorDepth(visitor);
          }

          clearStoppedVisitors();
          if(needPreorderStop)
            return;

          visitAllEdges(node, true);

          foreach (var visitor in visitorList) {
            decVisitorDepth(visitor);
            visitor.visitEnd(node);
          }

          clearStoppedVisitors();
        }

        /// <summary>
        /// It call the traversal for the edges
        /// </summary>
        /// <param name="node">[in] The node with own type</param>
        /// <param name="callVirtualBase">[in] This paramater is don't used just api copatibility used.</param>
        public void visitAllEdges(Columbus.Csharp.Asg.Nodes.Structure.EnumMemberDeclarationSyntax node, bool callFirst = true){
            visitAllEdges((Columbus.Csharp.Asg.Nodes.Structure.MemberDeclarationSyntax)(node),false);


            // edge: AttributeLists
            ListIterator<Columbus.Csharp.Asg.Nodes.Structure.AttributeListSyntax> iteratorForAttributeLists = node.AttributeListsListIteratorBegin;
            while (iteratorForAttributeLists.getValue() != null) {
               Columbus.Csharp.Asg.Nodes.Structure.AttributeListSyntax endNodeRef = (Columbus.Csharp.Asg.Nodes.Structure.AttributeListSyntax)iteratorForAttributeLists.getValue();
              foreach (var visitor in visitorList) {
                visitor.visitEnumMemberDeclarationSyntax_AttributeLists(node.Id, endNodeRef.Id);
              }

              clearStoppedVisitors();
              if(needPreorderStop)
                return;

              if ((!fact.IsFilterTurnedOn && !visitFilteredEdge) || (fact.getFilterState(endNodeRef.Id) == Filter.FilterState.NotFiltered) || (!originalFilterState && visitFilteredEdge)) {
                  endNodeRef.accept(this);
              }
              foreach (var visitor in visitorList) {
                visitor.visitEndEnumMemberDeclarationSyntax_AttributeLists(node.Id, endNodeRef.Id);
              }

              clearStoppedVisitors();
              if(needPreorderStop)
                return;

            iteratorForAttributeLists = iteratorForAttributeLists.getNext();
            }

            Columbus.Csharp.Asg.Nodes.Base.Base genNodePtr;
            // edge: EqualsValue
            genNodePtr = fact.getRef(node.getEqualsValue()) ;
            if (genNodePtr != null) {
              Columbus.Csharp.Asg.Nodes.Structure.EqualsValueClauseSyntax endNodeRef = (Columbus.Csharp.Asg.Nodes.Structure.EqualsValueClauseSyntax)(genNodePtr);
              foreach (var visitor in visitorList) {
                visitor.visitEnumMemberDeclarationSyntax_EqualsValue(node.Id, endNodeRef.Id);
              }

              clearStoppedVisitors();
              if(needPreorderStop)
                return;

              if ((!fact.IsFilterTurnedOn && !visitFilteredEdge) || (fact.getFilterState(endNodeRef.Id) == Filter.FilterState.NotFiltered) || (!originalFilterState && visitFilteredEdge)) {
                  endNodeRef.accept(this);
              }
              foreach (var visitor in visitorList) {
                visitor.visitEndEnumMemberDeclarationSyntax_EqualsValue(node.Id, endNodeRef.Id);
              }

              clearStoppedVisitors();
              if(needPreorderStop)
                return;

            }
        }

        public override void visit(Columbus.Csharp.Asg.Nodes.Structure.EnumMemberDeclarationSyntax node, bool callFirst = true){
          if (safeMode || visitCrossEdgeTree) {
            if (safeMode) {
              if (visitedNodes[(int)node.Id]) { // for safemode
                return;
              }
            }
            visitedNodes[(int)node.Id] = true;
          }

          foreach (var visitor in visitorList) {
            visitor.visit(node);
            incVisitorDepth(visitor);
          }

          clearStoppedVisitors();
          if(needPreorderStop)
            return;

          visitAllEdges(node, true);

          foreach (var visitor in visitorList) {
            decVisitorDepth(visitor);
            visitor.visitEnd(node);
          }

          clearStoppedVisitors();
        }

        /// <summary>
        /// It call the traversal for the edges
        /// </summary>
        /// <param name="node">[in] The node with own type</param>
        /// <param name="callVirtualBase">[in] This paramater is don't used just api copatibility used.</param>
        public void visitAllEdges(Columbus.Csharp.Asg.Nodes.Structure.EqualsValueClauseSyntax node, bool callFirst = true){
            visitAllEdges((Columbus.Csharp.Asg.Nodes.Base.Positioned)(node),false);


            Columbus.Csharp.Asg.Nodes.Base.Base genNodePtr;
            // edge: Value
            genNodePtr = fact.getRef(node.getValue()) ;
            if (genNodePtr != null) {
              Columbus.Csharp.Asg.Nodes.Expression.ExpressionSyntax endNodeRef = (Columbus.Csharp.Asg.Nodes.Expression.ExpressionSyntax)(genNodePtr);
              foreach (var visitor in visitorList) {
                visitor.visitEqualsValueClauseSyntax_Value(node.Id, endNodeRef.Id);
              }

              clearStoppedVisitors();
              if(needPreorderStop)
                return;

              if ((!fact.IsFilterTurnedOn && !visitFilteredEdge) || (fact.getFilterState(endNodeRef.Id) == Filter.FilterState.NotFiltered) || (!originalFilterState && visitFilteredEdge)) {
                  endNodeRef.accept(this);
              }
              foreach (var visitor in visitorList) {
                visitor.visitEndEqualsValueClauseSyntax_Value(node.Id, endNodeRef.Id);
              }

              clearStoppedVisitors();
              if(needPreorderStop)
                return;

            }
        }

        public override void visit(Columbus.Csharp.Asg.Nodes.Structure.EqualsValueClauseSyntax node, bool callFirst = true){
          if (safeMode || visitCrossEdgeTree) {
            if (safeMode) {
              if (visitedNodes[(int)node.Id]) { // for safemode
                return;
              }
            }
            visitedNodes[(int)node.Id] = true;
          }

          foreach (var visitor in visitorList) {
            visitor.visit(node);
            incVisitorDepth(visitor);
          }

          clearStoppedVisitors();
          if(needPreorderStop)
            return;

          visitAllEdges(node, true);

          foreach (var visitor in visitorList) {
            decVisitorDepth(visitor);
            visitor.visitEnd(node);
          }

          clearStoppedVisitors();
        }

        /// <summary>
        /// It call the traversal for the edges
        /// </summary>
        /// <param name="node">[in] The node with own type</param>
        /// <param name="callVirtualBase">[in] This paramater is don't used just api copatibility used.</param>
        public void visitAllEdges(Columbus.Csharp.Asg.Nodes.Structure.EventDeclarationSyntax node, bool callFirst = true){
            visitAllEdges((Columbus.Csharp.Asg.Nodes.Structure.BasePropertyDeclarationSyntax)(node),false);
        }

        public override void visit(Columbus.Csharp.Asg.Nodes.Structure.EventDeclarationSyntax node, bool callFirst = true){
          if (safeMode || visitCrossEdgeTree) {
            if (safeMode) {
              if (visitedNodes[(int)node.Id]) { // for safemode
                return;
              }
            }
            visitedNodes[(int)node.Id] = true;
          }

          foreach (var visitor in visitorList) {
            visitor.visit(node);
            incVisitorDepth(visitor);
          }

          clearStoppedVisitors();
          if(needPreorderStop)
            return;

          visitAllEdges(node, true);

          foreach (var visitor in visitorList) {
            decVisitorDepth(visitor);
            visitor.visitEnd(node);
          }

          clearStoppedVisitors();
        }

        /// <summary>
        /// It call the traversal for the edges
        /// </summary>
        /// <param name="node">[in] The node with own type</param>
        /// <param name="callVirtualBase">[in] This paramater is don't used just api copatibility used.</param>
        public void visitAllEdges(Columbus.Csharp.Asg.Nodes.Structure.EventFieldDeclarationSyntax node, bool callFirst = true){
            visitAllEdges((Columbus.Csharp.Asg.Nodes.Structure.BaseFieldDeclarationSyntax)(node),false);
        }

        public override void visit(Columbus.Csharp.Asg.Nodes.Structure.EventFieldDeclarationSyntax node, bool callFirst = true){
          if (safeMode || visitCrossEdgeTree) {
            if (safeMode) {
              if (visitedNodes[(int)node.Id]) { // for safemode
                return;
              }
            }
            visitedNodes[(int)node.Id] = true;
          }

          foreach (var visitor in visitorList) {
            visitor.visit(node);
            incVisitorDepth(visitor);
          }

          clearStoppedVisitors();
          if(needPreorderStop)
            return;

          visitAllEdges(node, true);

          foreach (var visitor in visitorList) {
            decVisitorDepth(visitor);
            visitor.visitEnd(node);
          }

          clearStoppedVisitors();
        }

        /// <summary>
        /// It call the traversal for the edges
        /// </summary>
        /// <param name="node">[in] The node with own type</param>
        /// <param name="callVirtualBase">[in] This paramater is don't used just api copatibility used.</param>
        public void visitAllEdges(Columbus.Csharp.Asg.Nodes.Structure.ExplicitInterfaceSpecifierSyntax node, bool callFirst = true){
            visitAllEdges((Columbus.Csharp.Asg.Nodes.Base.Positioned)(node),false);


            Columbus.Csharp.Asg.Nodes.Base.Base genNodePtr;
            // edge: Name
            genNodePtr = fact.getRef(node.getName()) ;
            if (genNodePtr != null) {
              Columbus.Csharp.Asg.Nodes.Expression.NameSyntax endNodeRef = (Columbus.Csharp.Asg.Nodes.Expression.NameSyntax)(genNodePtr);
              foreach (var visitor in visitorList) {
                visitor.visitExplicitInterfaceSpecifierSyntax_Name(node.Id, endNodeRef.Id);
              }

              clearStoppedVisitors();
              if(needPreorderStop)
                return;

              if ((!fact.IsFilterTurnedOn && !visitFilteredEdge) || (fact.getFilterState(endNodeRef.Id) == Filter.FilterState.NotFiltered) || (!originalFilterState && visitFilteredEdge)) {
                  endNodeRef.accept(this);
              }
              foreach (var visitor in visitorList) {
                visitor.visitEndExplicitInterfaceSpecifierSyntax_Name(node.Id, endNodeRef.Id);
              }

              clearStoppedVisitors();
              if(needPreorderStop)
                return;

            }
        }

        public override void visit(Columbus.Csharp.Asg.Nodes.Structure.ExplicitInterfaceSpecifierSyntax node, bool callFirst = true){
          if (safeMode || visitCrossEdgeTree) {
            if (safeMode) {
              if (visitedNodes[(int)node.Id]) { // for safemode
                return;
              }
            }
            visitedNodes[(int)node.Id] = true;
          }

          foreach (var visitor in visitorList) {
            visitor.visit(node);
            incVisitorDepth(visitor);
          }

          clearStoppedVisitors();
          if(needPreorderStop)
            return;

          visitAllEdges(node, true);

          foreach (var visitor in visitorList) {
            decVisitorDepth(visitor);
            visitor.visitEnd(node);
          }

          clearStoppedVisitors();
        }

        /// <summary>
        /// It call the traversal for the edges
        /// </summary>
        /// <param name="node">[in] The node with own type</param>
        /// <param name="callVirtualBase">[in] This paramater is don't used just api copatibility used.</param>
        public void visitAllEdges(Columbus.Csharp.Asg.Nodes.Structure.ExternAliasDirectiveSyntax node, bool callFirst = true){
            visitAllEdges((Columbus.Csharp.Asg.Nodes.Base.Positioned)(node),false);
        }

        public override void visit(Columbus.Csharp.Asg.Nodes.Structure.ExternAliasDirectiveSyntax node, bool callFirst = true){
          if (safeMode || visitCrossEdgeTree) {
            if (safeMode) {
              if (visitedNodes[(int)node.Id]) { // for safemode
                return;
              }
            }
            visitedNodes[(int)node.Id] = true;
          }

          foreach (var visitor in visitorList) {
            visitor.visit(node);
            incVisitorDepth(visitor);
          }

          clearStoppedVisitors();
          if(needPreorderStop)
            return;

          visitAllEdges(node, true);

          foreach (var visitor in visitorList) {
            decVisitorDepth(visitor);
            visitor.visitEnd(node);
          }

          clearStoppedVisitors();
        }

        /// <summary>
        /// It call the traversal for the edges
        /// </summary>
        /// <param name="node">[in] The node with own type</param>
        /// <param name="callVirtualBase">[in] This paramater is don't used just api copatibility used.</param>
        public void visitAllEdges(Columbus.Csharp.Asg.Nodes.Structure.FieldDeclarationSyntax node, bool callFirst = true){
            visitAllEdges((Columbus.Csharp.Asg.Nodes.Structure.BaseFieldDeclarationSyntax)(node),false);
        }

        public override void visit(Columbus.Csharp.Asg.Nodes.Structure.FieldDeclarationSyntax node, bool callFirst = true){
          if (safeMode || visitCrossEdgeTree) {
            if (safeMode) {
              if (visitedNodes[(int)node.Id]) { // for safemode
                return;
              }
            }
            visitedNodes[(int)node.Id] = true;
          }

          foreach (var visitor in visitorList) {
            visitor.visit(node);
            incVisitorDepth(visitor);
          }

          clearStoppedVisitors();
          if(needPreorderStop)
            return;

          visitAllEdges(node, true);

          foreach (var visitor in visitorList) {
            decVisitorDepth(visitor);
            visitor.visitEnd(node);
          }

          clearStoppedVisitors();
        }

        /// <summary>
        /// It call the traversal for the edges
        /// </summary>
        /// <param name="node">[in] The node with own type</param>
        /// <param name="callVirtualBase">[in] This paramater is don't used just api copatibility used.</param>
        public void visitAllEdges(Columbus.Csharp.Asg.Nodes.Structure.FinallyClauseSyntax node, bool callFirst = true){
            visitAllEdges((Columbus.Csharp.Asg.Nodes.Base.Positioned)(node),false);


            Columbus.Csharp.Asg.Nodes.Base.Base genNodePtr;
            // edge: Block
            genNodePtr = fact.getRef(node.getBlock()) ;
            if (genNodePtr != null) {
              Columbus.Csharp.Asg.Nodes.Statement.BlockSyntax endNodeRef = (Columbus.Csharp.Asg.Nodes.Statement.BlockSyntax)(genNodePtr);
              foreach (var visitor in visitorList) {
                visitor.visitFinallyClauseSyntax_Block(node.Id, endNodeRef.Id);
              }

              clearStoppedVisitors();
              if(needPreorderStop)
                return;

              if ((!fact.IsFilterTurnedOn && !visitFilteredEdge) || (fact.getFilterState(endNodeRef.Id) == Filter.FilterState.NotFiltered) || (!originalFilterState && visitFilteredEdge)) {
                  endNodeRef.accept(this);
              }
              foreach (var visitor in visitorList) {
                visitor.visitEndFinallyClauseSyntax_Block(node.Id, endNodeRef.Id);
              }

              clearStoppedVisitors();
              if(needPreorderStop)
                return;

            }
        }

        public override void visit(Columbus.Csharp.Asg.Nodes.Structure.FinallyClauseSyntax node, bool callFirst = true){
          if (safeMode || visitCrossEdgeTree) {
            if (safeMode) {
              if (visitedNodes[(int)node.Id]) { // for safemode
                return;
              }
            }
            visitedNodes[(int)node.Id] = true;
          }

          foreach (var visitor in visitorList) {
            visitor.visit(node);
            incVisitorDepth(visitor);
          }

          clearStoppedVisitors();
          if(needPreorderStop)
            return;

          visitAllEdges(node, true);

          foreach (var visitor in visitorList) {
            decVisitorDepth(visitor);
            visitor.visitEnd(node);
          }

          clearStoppedVisitors();
        }

        /// <summary>
        /// It call the traversal for the edges
        /// </summary>
        /// <param name="node">[in] The node with own type</param>
        /// <param name="callVirtualBase">[in] This paramater is don't used just api copatibility used.</param>
        public void visitAllEdges(Columbus.Csharp.Asg.Nodes.Structure.FromClauseSyntax node, bool callFirst = true){
            visitAllEdges((Columbus.Csharp.Asg.Nodes.Structure.QueryClauseSyntax)(node),false);


            Columbus.Csharp.Asg.Nodes.Base.Base genNodePtr;
            // edge: Expression
            genNodePtr = fact.getRef(node.getExpression()) ;
            if (genNodePtr != null) {
              Columbus.Csharp.Asg.Nodes.Expression.ExpressionSyntax endNodeRef = (Columbus.Csharp.Asg.Nodes.Expression.ExpressionSyntax)(genNodePtr);
              foreach (var visitor in visitorList) {
                visitor.visitFromClauseSyntax_Expression(node.Id, endNodeRef.Id);
              }

              clearStoppedVisitors();
              if(needPreorderStop)
                return;

              if ((!fact.IsFilterTurnedOn && !visitFilteredEdge) || (fact.getFilterState(endNodeRef.Id) == Filter.FilterState.NotFiltered) || (!originalFilterState && visitFilteredEdge)) {
                  endNodeRef.accept(this);
              }
              foreach (var visitor in visitorList) {
                visitor.visitEndFromClauseSyntax_Expression(node.Id, endNodeRef.Id);
              }

              clearStoppedVisitors();
              if(needPreorderStop)
                return;

            }

            // edge: Type
            genNodePtr = fact.getRef(node.getType()) ;
            if (genNodePtr != null) {
              Columbus.Csharp.Asg.Nodes.Expression.TypeSyntax endNodeRef = (Columbus.Csharp.Asg.Nodes.Expression.TypeSyntax)(genNodePtr);
              foreach (var visitor in visitorList) {
                visitor.visitFromClauseSyntax_Type(node.Id, endNodeRef.Id);
              }

              clearStoppedVisitors();
              if(needPreorderStop)
                return;

              if ((!fact.IsFilterTurnedOn && !visitFilteredEdge) || (fact.getFilterState(endNodeRef.Id) == Filter.FilterState.NotFiltered) || (!originalFilterState && visitFilteredEdge)) {
                  endNodeRef.accept(this);
              }
              foreach (var visitor in visitorList) {
                visitor.visitEndFromClauseSyntax_Type(node.Id, endNodeRef.Id);
              }

              clearStoppedVisitors();
              if(needPreorderStop)
                return;

            }
        }

        public override void visit(Columbus.Csharp.Asg.Nodes.Structure.FromClauseSyntax node, bool callFirst = true){
          if (safeMode || visitCrossEdgeTree) {
            if (safeMode) {
              if (visitedNodes[(int)node.Id]) { // for safemode
                return;
              }
            }
            visitedNodes[(int)node.Id] = true;
          }

          foreach (var visitor in visitorList) {
            visitor.visit(node);
            incVisitorDepth(visitor);
          }

          clearStoppedVisitors();
          if(needPreorderStop)
            return;

          visitAllEdges(node, true);

          foreach (var visitor in visitorList) {
            decVisitorDepth(visitor);
            visitor.visitEnd(node);
          }

          clearStoppedVisitors();
        }

        /// <summary>
        /// It call the traversal for the edges
        /// </summary>
        /// <param name="node">[in] The node with own type</param>
        /// <param name="callVirtualBase">[in] This paramater is don't used just api copatibility used.</param>
        public void visitAllEdges(Columbus.Csharp.Asg.Nodes.Structure.GlobalStatementSyntax node, bool callFirst = true){
            visitAllEdges((Columbus.Csharp.Asg.Nodes.Structure.MemberDeclarationSyntax)(node),false);


            Columbus.Csharp.Asg.Nodes.Base.Base genNodePtr;
            // edge: Statement
            genNodePtr = fact.getRef(node.getStatement()) ;
            if (genNodePtr != null) {
              Columbus.Csharp.Asg.Nodes.Statement.StatementSyntax endNodeRef = (Columbus.Csharp.Asg.Nodes.Statement.StatementSyntax)(genNodePtr);
              foreach (var visitor in visitorList) {
                visitor.visitGlobalStatementSyntax_Statement(node.Id, endNodeRef.Id);
              }

              clearStoppedVisitors();
              if(needPreorderStop)
                return;

              if ((!fact.IsFilterTurnedOn && !visitFilteredEdge) || (fact.getFilterState(endNodeRef.Id) == Filter.FilterState.NotFiltered) || (!originalFilterState && visitFilteredEdge)) {
                  endNodeRef.accept(this);
              }
              foreach (var visitor in visitorList) {
                visitor.visitEndGlobalStatementSyntax_Statement(node.Id, endNodeRef.Id);
              }

              clearStoppedVisitors();
              if(needPreorderStop)
                return;

            }
        }

        public override void visit(Columbus.Csharp.Asg.Nodes.Structure.GlobalStatementSyntax node, bool callFirst = true){
          if (safeMode || visitCrossEdgeTree) {
            if (safeMode) {
              if (visitedNodes[(int)node.Id]) { // for safemode
                return;
              }
            }
            visitedNodes[(int)node.Id] = true;
          }

          foreach (var visitor in visitorList) {
            visitor.visit(node);
            incVisitorDepth(visitor);
          }

          clearStoppedVisitors();
          if(needPreorderStop)
            return;

          visitAllEdges(node, true);

          foreach (var visitor in visitorList) {
            decVisitorDepth(visitor);
            visitor.visitEnd(node);
          }

          clearStoppedVisitors();
        }

        /// <summary>
        /// It call the traversal for the edges
        /// </summary>
        /// <param name="node">[in] The node with own type</param>
        /// <param name="callVirtualBase">[in] This paramater is don't used just api copatibility used.</param>
        public void visitAllEdges(Columbus.Csharp.Asg.Nodes.Structure.GroupClauseSyntax node, bool callFirst = true){
            visitAllEdges((Columbus.Csharp.Asg.Nodes.Structure.SelectOrGroupClauseSyntax)(node),false);


            Columbus.Csharp.Asg.Nodes.Base.Base genNodePtr;
            // edge: ByExpression
            genNodePtr = fact.getRef(node.getByExpression()) ;
            if (genNodePtr != null) {
              Columbus.Csharp.Asg.Nodes.Expression.ExpressionSyntax endNodeRef = (Columbus.Csharp.Asg.Nodes.Expression.ExpressionSyntax)(genNodePtr);
              foreach (var visitor in visitorList) {
                visitor.visitGroupClauseSyntax_ByExpression(node.Id, endNodeRef.Id);
              }

              clearStoppedVisitors();
              if(needPreorderStop)
                return;

              if ((!fact.IsFilterTurnedOn && !visitFilteredEdge) || (fact.getFilterState(endNodeRef.Id) == Filter.FilterState.NotFiltered) || (!originalFilterState && visitFilteredEdge)) {
                  endNodeRef.accept(this);
              }
              foreach (var visitor in visitorList) {
                visitor.visitEndGroupClauseSyntax_ByExpression(node.Id, endNodeRef.Id);
              }

              clearStoppedVisitors();
              if(needPreorderStop)
                return;

            }

            // edge: GroupExpression
            genNodePtr = fact.getRef(node.getGroupExpression()) ;
            if (genNodePtr != null) {
              Columbus.Csharp.Asg.Nodes.Expression.ExpressionSyntax endNodeRef = (Columbus.Csharp.Asg.Nodes.Expression.ExpressionSyntax)(genNodePtr);
              foreach (var visitor in visitorList) {
                visitor.visitGroupClauseSyntax_GroupExpression(node.Id, endNodeRef.Id);
              }

              clearStoppedVisitors();
              if(needPreorderStop)
                return;

              if ((!fact.IsFilterTurnedOn && !visitFilteredEdge) || (fact.getFilterState(endNodeRef.Id) == Filter.FilterState.NotFiltered) || (!originalFilterState && visitFilteredEdge)) {
                  endNodeRef.accept(this);
              }
              foreach (var visitor in visitorList) {
                visitor.visitEndGroupClauseSyntax_GroupExpression(node.Id, endNodeRef.Id);
              }

              clearStoppedVisitors();
              if(needPreorderStop)
                return;

            }
        }

        public override void visit(Columbus.Csharp.Asg.Nodes.Structure.GroupClauseSyntax node, bool callFirst = true){
          if (safeMode || visitCrossEdgeTree) {
            if (safeMode) {
              if (visitedNodes[(int)node.Id]) { // for safemode
                return;
              }
            }
            visitedNodes[(int)node.Id] = true;
          }

          foreach (var visitor in visitorList) {
            visitor.visit(node);
            incVisitorDepth(visitor);
          }

          clearStoppedVisitors();
          if(needPreorderStop)
            return;

          visitAllEdges(node, true);

          foreach (var visitor in visitorList) {
            decVisitorDepth(visitor);
            visitor.visitEnd(node);
          }

          clearStoppedVisitors();
        }

        /// <summary>
        /// It call the traversal for the edges
        /// </summary>
        /// <param name="node">[in] The node with own type</param>
        /// <param name="callVirtualBase">[in] This paramater is don't used just api copatibility used.</param>
        public void visitAllEdges(Columbus.Csharp.Asg.Nodes.Structure.IncompleteMemberSyntax node, bool callFirst = true){
            visitAllEdges((Columbus.Csharp.Asg.Nodes.Structure.MemberDeclarationSyntax)(node),false);


            // edge: AttributeLists
            ListIterator<Columbus.Csharp.Asg.Nodes.Structure.AttributeListSyntax> iteratorForAttributeLists = node.AttributeListsListIteratorBegin;
            while (iteratorForAttributeLists.getValue() != null) {
               Columbus.Csharp.Asg.Nodes.Structure.AttributeListSyntax endNodeRef = (Columbus.Csharp.Asg.Nodes.Structure.AttributeListSyntax)iteratorForAttributeLists.getValue();
              foreach (var visitor in visitorList) {
                visitor.visitIncompleteMemberSyntax_AttributeLists(node.Id, endNodeRef.Id);
              }

              clearStoppedVisitors();
              if(needPreorderStop)
                return;

              if ((!fact.IsFilterTurnedOn && !visitFilteredEdge) || (fact.getFilterState(endNodeRef.Id) == Filter.FilterState.NotFiltered) || (!originalFilterState && visitFilteredEdge)) {
                  endNodeRef.accept(this);
              }
              foreach (var visitor in visitorList) {
                visitor.visitEndIncompleteMemberSyntax_AttributeLists(node.Id, endNodeRef.Id);
              }

              clearStoppedVisitors();
              if(needPreorderStop)
                return;

            iteratorForAttributeLists = iteratorForAttributeLists.getNext();
            }

            Columbus.Csharp.Asg.Nodes.Base.Base genNodePtr;
            // edge: Type
            genNodePtr = fact.getRef(node.getType()) ;
            if (genNodePtr != null) {
              Columbus.Csharp.Asg.Nodes.Expression.TypeSyntax endNodeRef = (Columbus.Csharp.Asg.Nodes.Expression.TypeSyntax)(genNodePtr);
              foreach (var visitor in visitorList) {
                visitor.visitIncompleteMemberSyntax_Type(node.Id, endNodeRef.Id);
              }

              clearStoppedVisitors();
              if(needPreorderStop)
                return;

              if ((!fact.IsFilterTurnedOn && !visitFilteredEdge) || (fact.getFilterState(endNodeRef.Id) == Filter.FilterState.NotFiltered) || (!originalFilterState && visitFilteredEdge)) {
                  endNodeRef.accept(this);
              }
              foreach (var visitor in visitorList) {
                visitor.visitEndIncompleteMemberSyntax_Type(node.Id, endNodeRef.Id);
              }

              clearStoppedVisitors();
              if(needPreorderStop)
                return;

            }
        }

        public override void visit(Columbus.Csharp.Asg.Nodes.Structure.IncompleteMemberSyntax node, bool callFirst = true){
          if (safeMode || visitCrossEdgeTree) {
            if (safeMode) {
              if (visitedNodes[(int)node.Id]) { // for safemode
                return;
              }
            }
            visitedNodes[(int)node.Id] = true;
          }

          foreach (var visitor in visitorList) {
            visitor.visit(node);
            incVisitorDepth(visitor);
          }

          clearStoppedVisitors();
          if(needPreorderStop)
            return;

          visitAllEdges(node, true);

          foreach (var visitor in visitorList) {
            decVisitorDepth(visitor);
            visitor.visitEnd(node);
          }

          clearStoppedVisitors();
        }

        /// <summary>
        /// It call the traversal for the edges
        /// </summary>
        /// <param name="node">[in] The node with own type</param>
        /// <param name="callVirtualBase">[in] This paramater is don't used just api copatibility used.</param>
        public void visitAllEdges(Columbus.Csharp.Asg.Nodes.Structure.IndexerDeclarationSyntax node, bool callFirst = true){
            visitAllEdges((Columbus.Csharp.Asg.Nodes.Structure.BasePropertyDeclarationSyntax)(node),false);


            Columbus.Csharp.Asg.Nodes.Base.Base genNodePtr;
            // edge: ExpressionBody
            genNodePtr = fact.getRef(node.getExpressionBody()) ;
            if (genNodePtr != null) {
              Columbus.Csharp.Asg.Nodes.Structure.ArrowExpressionClauseSyntax endNodeRef = (Columbus.Csharp.Asg.Nodes.Structure.ArrowExpressionClauseSyntax)(genNodePtr);
              foreach (var visitor in visitorList) {
                visitor.visitIndexerDeclarationSyntax_ExpressionBody(node.Id, endNodeRef.Id);
              }

              clearStoppedVisitors();
              if(needPreorderStop)
                return;

              if ((!fact.IsFilterTurnedOn && !visitFilteredEdge) || (fact.getFilterState(endNodeRef.Id) == Filter.FilterState.NotFiltered) || (!originalFilterState && visitFilteredEdge)) {
                  endNodeRef.accept(this);
              }
              foreach (var visitor in visitorList) {
                visitor.visitEndIndexerDeclarationSyntax_ExpressionBody(node.Id, endNodeRef.Id);
              }

              clearStoppedVisitors();
              if(needPreorderStop)
                return;

            }

            // edge: ParameterList
            genNodePtr = fact.getRef(node.getParameterList()) ;
            if (genNodePtr != null) {
              Columbus.Csharp.Asg.Nodes.Structure.BracketedParameterListSyntax endNodeRef = (Columbus.Csharp.Asg.Nodes.Structure.BracketedParameterListSyntax)(genNodePtr);
              foreach (var visitor in visitorList) {
                visitor.visitIndexerDeclarationSyntax_ParameterList(node.Id, endNodeRef.Id);
              }

              clearStoppedVisitors();
              if(needPreorderStop)
                return;

              if ((!fact.IsFilterTurnedOn && !visitFilteredEdge) || (fact.getFilterState(endNodeRef.Id) == Filter.FilterState.NotFiltered) || (!originalFilterState && visitFilteredEdge)) {
                  endNodeRef.accept(this);
              }
              foreach (var visitor in visitorList) {
                visitor.visitEndIndexerDeclarationSyntax_ParameterList(node.Id, endNodeRef.Id);
              }

              clearStoppedVisitors();
              if(needPreorderStop)
                return;

            }
        }

        public override void visit(Columbus.Csharp.Asg.Nodes.Structure.IndexerDeclarationSyntax node, bool callFirst = true){
          if (safeMode || visitCrossEdgeTree) {
            if (safeMode) {
              if (visitedNodes[(int)node.Id]) { // for safemode
                return;
              }
            }
            visitedNodes[(int)node.Id] = true;
          }

          foreach (var visitor in visitorList) {
            visitor.visit(node);
            incVisitorDepth(visitor);
          }

          clearStoppedVisitors();
          if(needPreorderStop)
            return;

          visitAllEdges(node, true);

          foreach (var visitor in visitorList) {
            decVisitorDepth(visitor);
            visitor.visitEnd(node);
          }

          clearStoppedVisitors();
        }

        /// <summary>
        /// It call the traversal for the edges
        /// </summary>
        /// <param name="node">[in] The node with own type</param>
        /// <param name="callVirtualBase">[in] This paramater is don't used just api copatibility used.</param>
        public void visitAllEdges(Columbus.Csharp.Asg.Nodes.Structure.IndexerMemberCrefSyntax node, bool callFirst = true){
            visitAllEdges((Columbus.Csharp.Asg.Nodes.Structure.MemberCrefSyntax)(node),false);


            Columbus.Csharp.Asg.Nodes.Base.Base genNodePtr;
            // edge: Parameters
            genNodePtr = fact.getRef(node.getParameters()) ;
            if (genNodePtr != null) {
              Columbus.Csharp.Asg.Nodes.Structure.CrefBracketedParameterListSyntax endNodeRef = (Columbus.Csharp.Asg.Nodes.Structure.CrefBracketedParameterListSyntax)(genNodePtr);
              foreach (var visitor in visitorList) {
                visitor.visitIndexerMemberCrefSyntax_Parameters(node.Id, endNodeRef.Id);
              }

              clearStoppedVisitors();
              if(needPreorderStop)
                return;

              if ((!fact.IsFilterTurnedOn && !visitFilteredEdge) || (fact.getFilterState(endNodeRef.Id) == Filter.FilterState.NotFiltered) || (!originalFilterState && visitFilteredEdge)) {
                  endNodeRef.accept(this);
              }
              foreach (var visitor in visitorList) {
                visitor.visitEndIndexerMemberCrefSyntax_Parameters(node.Id, endNodeRef.Id);
              }

              clearStoppedVisitors();
              if(needPreorderStop)
                return;

            }
        }

        public override void visit(Columbus.Csharp.Asg.Nodes.Structure.IndexerMemberCrefSyntax node, bool callFirst = true){
          if (safeMode || visitCrossEdgeTree) {
            if (safeMode) {
              if (visitedNodes[(int)node.Id]) { // for safemode
                return;
              }
            }
            visitedNodes[(int)node.Id] = true;
          }

          foreach (var visitor in visitorList) {
            visitor.visit(node);
            incVisitorDepth(visitor);
          }

          clearStoppedVisitors();
          if(needPreorderStop)
            return;

          visitAllEdges(node, true);

          foreach (var visitor in visitorList) {
            decVisitorDepth(visitor);
            visitor.visitEnd(node);
          }

          clearStoppedVisitors();
        }

        /// <summary>
        /// It call the traversal for the edges
        /// </summary>
        /// <param name="node">[in] The node with own type</param>
        /// <param name="callVirtualBase">[in] This paramater is don't used just api copatibility used.</param>
        public void visitAllEdges(Columbus.Csharp.Asg.Nodes.Structure.InterfaceDeclarationSyntax node, bool callFirst = true){
            visitAllEdges((Columbus.Csharp.Asg.Nodes.Structure.TypeDeclarationSyntax)(node),false);
        }

        public override void visit(Columbus.Csharp.Asg.Nodes.Structure.InterfaceDeclarationSyntax node, bool callFirst = true){
          if (safeMode || visitCrossEdgeTree) {
            if (safeMode) {
              if (visitedNodes[(int)node.Id]) { // for safemode
                return;
              }
            }
            visitedNodes[(int)node.Id] = true;
          }

          foreach (var visitor in visitorList) {
            visitor.visit(node);
            incVisitorDepth(visitor);
          }

          clearStoppedVisitors();
          if(needPreorderStop)
            return;

          visitAllEdges(node, true);

          foreach (var visitor in visitorList) {
            decVisitorDepth(visitor);
            visitor.visitEnd(node);
          }

          clearStoppedVisitors();
        }

        /// <summary>
        /// It call the traversal for the edges
        /// </summary>
        /// <param name="node">[in] The node with own type</param>
        /// <param name="callVirtualBase">[in] This paramater is don't used just api copatibility used.</param>
        public void visitAllEdges(Columbus.Csharp.Asg.Nodes.Structure.InterpolatedStringContentSyntax node, bool callFirst = true){
            visitAllEdges((Columbus.Csharp.Asg.Nodes.Base.Positioned)(node),false);
        }

        /// <summary>
        /// It call the traversal for the edges
        /// </summary>
        /// <param name="node">[in] The node with own type</param>
        /// <param name="callVirtualBase">[in] This paramater is don't used just api copatibility used.</param>
        public void visitAllEdges(Columbus.Csharp.Asg.Nodes.Structure.InterpolatedStringTextSyntax node, bool callFirst = true){
            visitAllEdges((Columbus.Csharp.Asg.Nodes.Structure.InterpolatedStringContentSyntax)(node),false);
        }

        public override void visit(Columbus.Csharp.Asg.Nodes.Structure.InterpolatedStringTextSyntax node, bool callFirst = true){
          if (safeMode || visitCrossEdgeTree) {
            if (safeMode) {
              if (visitedNodes[(int)node.Id]) { // for safemode
                return;
              }
            }
            visitedNodes[(int)node.Id] = true;
          }

          foreach (var visitor in visitorList) {
            visitor.visit(node);
            incVisitorDepth(visitor);
          }

          clearStoppedVisitors();
          if(needPreorderStop)
            return;

          visitAllEdges(node, true);

          foreach (var visitor in visitorList) {
            decVisitorDepth(visitor);
            visitor.visitEnd(node);
          }

          clearStoppedVisitors();
        }

        /// <summary>
        /// It call the traversal for the edges
        /// </summary>
        /// <param name="node">[in] The node with own type</param>
        /// <param name="callVirtualBase">[in] This paramater is don't used just api copatibility used.</param>
        public void visitAllEdges(Columbus.Csharp.Asg.Nodes.Structure.InterpolationAlignmentClauseSyntax node, bool callFirst = true){
            visitAllEdges((Columbus.Csharp.Asg.Nodes.Base.Positioned)(node),false);


            Columbus.Csharp.Asg.Nodes.Base.Base genNodePtr;
            // edge: Value
            genNodePtr = fact.getRef(node.getValue()) ;
            if (genNodePtr != null) {
              Columbus.Csharp.Asg.Nodes.Expression.ExpressionSyntax endNodeRef = (Columbus.Csharp.Asg.Nodes.Expression.ExpressionSyntax)(genNodePtr);
              foreach (var visitor in visitorList) {
                visitor.visitInterpolationAlignmentClauseSyntax_Value(node.Id, endNodeRef.Id);
              }

              clearStoppedVisitors();
              if(needPreorderStop)
                return;

              if ((!fact.IsFilterTurnedOn && !visitFilteredEdge) || (fact.getFilterState(endNodeRef.Id) == Filter.FilterState.NotFiltered) || (!originalFilterState && visitFilteredEdge)) {
                  endNodeRef.accept(this);
              }
              foreach (var visitor in visitorList) {
                visitor.visitEndInterpolationAlignmentClauseSyntax_Value(node.Id, endNodeRef.Id);
              }

              clearStoppedVisitors();
              if(needPreorderStop)
                return;

            }
        }

        public override void visit(Columbus.Csharp.Asg.Nodes.Structure.InterpolationAlignmentClauseSyntax node, bool callFirst = true){
          if (safeMode || visitCrossEdgeTree) {
            if (safeMode) {
              if (visitedNodes[(int)node.Id]) { // for safemode
                return;
              }
            }
            visitedNodes[(int)node.Id] = true;
          }

          foreach (var visitor in visitorList) {
            visitor.visit(node);
            incVisitorDepth(visitor);
          }

          clearStoppedVisitors();
          if(needPreorderStop)
            return;

          visitAllEdges(node, true);

          foreach (var visitor in visitorList) {
            decVisitorDepth(visitor);
            visitor.visitEnd(node);
          }

          clearStoppedVisitors();
        }

        /// <summary>
        /// It call the traversal for the edges
        /// </summary>
        /// <param name="node">[in] The node with own type</param>
        /// <param name="callVirtualBase">[in] This paramater is don't used just api copatibility used.</param>
        public void visitAllEdges(Columbus.Csharp.Asg.Nodes.Structure.InterpolationFormatClauseSyntax node, bool callFirst = true){
            visitAllEdges((Columbus.Csharp.Asg.Nodes.Base.Positioned)(node),false);
        }

        public override void visit(Columbus.Csharp.Asg.Nodes.Structure.InterpolationFormatClauseSyntax node, bool callFirst = true){
          if (safeMode || visitCrossEdgeTree) {
            if (safeMode) {
              if (visitedNodes[(int)node.Id]) { // for safemode
                return;
              }
            }
            visitedNodes[(int)node.Id] = true;
          }

          foreach (var visitor in visitorList) {
            visitor.visit(node);
            incVisitorDepth(visitor);
          }

          clearStoppedVisitors();
          if(needPreorderStop)
            return;

          visitAllEdges(node, true);

          foreach (var visitor in visitorList) {
            decVisitorDepth(visitor);
            visitor.visitEnd(node);
          }

          clearStoppedVisitors();
        }

        /// <summary>
        /// It call the traversal for the edges
        /// </summary>
        /// <param name="node">[in] The node with own type</param>
        /// <param name="callVirtualBase">[in] This paramater is don't used just api copatibility used.</param>
        public void visitAllEdges(Columbus.Csharp.Asg.Nodes.Structure.InterpolationSyntax node, bool callFirst = true){
            visitAllEdges((Columbus.Csharp.Asg.Nodes.Structure.InterpolatedStringContentSyntax)(node),false);


            Columbus.Csharp.Asg.Nodes.Base.Base genNodePtr;
            // edge: AlignmentClause
            genNodePtr = fact.getRef(node.getAlignmentClause()) ;
            if (genNodePtr != null) {
              Columbus.Csharp.Asg.Nodes.Structure.InterpolationAlignmentClauseSyntax endNodeRef = (Columbus.Csharp.Asg.Nodes.Structure.InterpolationAlignmentClauseSyntax)(genNodePtr);
              foreach (var visitor in visitorList) {
                visitor.visitInterpolationSyntax_AlignmentClause(node.Id, endNodeRef.Id);
              }

              clearStoppedVisitors();
              if(needPreorderStop)
                return;

              if ((!fact.IsFilterTurnedOn && !visitFilteredEdge) || (fact.getFilterState(endNodeRef.Id) == Filter.FilterState.NotFiltered) || (!originalFilterState && visitFilteredEdge)) {
                  endNodeRef.accept(this);
              }
              foreach (var visitor in visitorList) {
                visitor.visitEndInterpolationSyntax_AlignmentClause(node.Id, endNodeRef.Id);
              }

              clearStoppedVisitors();
              if(needPreorderStop)
                return;

            }

            // edge: Expression
            genNodePtr = fact.getRef(node.getExpression()) ;
            if (genNodePtr != null) {
              Columbus.Csharp.Asg.Nodes.Expression.ExpressionSyntax endNodeRef = (Columbus.Csharp.Asg.Nodes.Expression.ExpressionSyntax)(genNodePtr);
              foreach (var visitor in visitorList) {
                visitor.visitInterpolationSyntax_Expression(node.Id, endNodeRef.Id);
              }

              clearStoppedVisitors();
              if(needPreorderStop)
                return;

              if ((!fact.IsFilterTurnedOn && !visitFilteredEdge) || (fact.getFilterState(endNodeRef.Id) == Filter.FilterState.NotFiltered) || (!originalFilterState && visitFilteredEdge)) {
                  endNodeRef.accept(this);
              }
              foreach (var visitor in visitorList) {
                visitor.visitEndInterpolationSyntax_Expression(node.Id, endNodeRef.Id);
              }

              clearStoppedVisitors();
              if(needPreorderStop)
                return;

            }

            // edge: FormatClause
            genNodePtr = fact.getRef(node.getFormatClause()) ;
            if (genNodePtr != null) {
              Columbus.Csharp.Asg.Nodes.Structure.InterpolationFormatClauseSyntax endNodeRef = (Columbus.Csharp.Asg.Nodes.Structure.InterpolationFormatClauseSyntax)(genNodePtr);
              foreach (var visitor in visitorList) {
                visitor.visitInterpolationSyntax_FormatClause(node.Id, endNodeRef.Id);
              }

              clearStoppedVisitors();
              if(needPreorderStop)
                return;

              if ((!fact.IsFilterTurnedOn && !visitFilteredEdge) || (fact.getFilterState(endNodeRef.Id) == Filter.FilterState.NotFiltered) || (!originalFilterState && visitFilteredEdge)) {
                  endNodeRef.accept(this);
              }
              foreach (var visitor in visitorList) {
                visitor.visitEndInterpolationSyntax_FormatClause(node.Id, endNodeRef.Id);
              }

              clearStoppedVisitors();
              if(needPreorderStop)
                return;

            }
        }

        public override void visit(Columbus.Csharp.Asg.Nodes.Structure.InterpolationSyntax node, bool callFirst = true){
          if (safeMode || visitCrossEdgeTree) {
            if (safeMode) {
              if (visitedNodes[(int)node.Id]) { // for safemode
                return;
              }
            }
            visitedNodes[(int)node.Id] = true;
          }

          foreach (var visitor in visitorList) {
            visitor.visit(node);
            incVisitorDepth(visitor);
          }

          clearStoppedVisitors();
          if(needPreorderStop)
            return;

          visitAllEdges(node, true);

          foreach (var visitor in visitorList) {
            decVisitorDepth(visitor);
            visitor.visitEnd(node);
          }

          clearStoppedVisitors();
        }

        /// <summary>
        /// It call the traversal for the edges
        /// </summary>
        /// <param name="node">[in] The node with own type</param>
        /// <param name="callVirtualBase">[in] This paramater is don't used just api copatibility used.</param>
        public void visitAllEdges(Columbus.Csharp.Asg.Nodes.Structure.JoinClauseSyntax node, bool callFirst = true){
            visitAllEdges((Columbus.Csharp.Asg.Nodes.Structure.QueryClauseSyntax)(node),false);


            Columbus.Csharp.Asg.Nodes.Base.Base genNodePtr;
            // edge: InExpression
            genNodePtr = fact.getRef(node.getInExpression()) ;
            if (genNodePtr != null) {
              Columbus.Csharp.Asg.Nodes.Expression.ExpressionSyntax endNodeRef = (Columbus.Csharp.Asg.Nodes.Expression.ExpressionSyntax)(genNodePtr);
              foreach (var visitor in visitorList) {
                visitor.visitJoinClauseSyntax_InExpression(node.Id, endNodeRef.Id);
              }

              clearStoppedVisitors();
              if(needPreorderStop)
                return;

              if ((!fact.IsFilterTurnedOn && !visitFilteredEdge) || (fact.getFilterState(endNodeRef.Id) == Filter.FilterState.NotFiltered) || (!originalFilterState && visitFilteredEdge)) {
                  endNodeRef.accept(this);
              }
              foreach (var visitor in visitorList) {
                visitor.visitEndJoinClauseSyntax_InExpression(node.Id, endNodeRef.Id);
              }

              clearStoppedVisitors();
              if(needPreorderStop)
                return;

            }

            // edge: Into
            genNodePtr = fact.getRef(node.getInto()) ;
            if (genNodePtr != null) {
              Columbus.Csharp.Asg.Nodes.Structure.JoinIntoClauseSyntax endNodeRef = (Columbus.Csharp.Asg.Nodes.Structure.JoinIntoClauseSyntax)(genNodePtr);
              foreach (var visitor in visitorList) {
                visitor.visitJoinClauseSyntax_Into(node.Id, endNodeRef.Id);
              }

              clearStoppedVisitors();
              if(needPreorderStop)
                return;

              if ((!fact.IsFilterTurnedOn && !visitFilteredEdge) || (fact.getFilterState(endNodeRef.Id) == Filter.FilterState.NotFiltered) || (!originalFilterState && visitFilteredEdge)) {
                  endNodeRef.accept(this);
              }
              foreach (var visitor in visitorList) {
                visitor.visitEndJoinClauseSyntax_Into(node.Id, endNodeRef.Id);
              }

              clearStoppedVisitors();
              if(needPreorderStop)
                return;

            }

            // edge: LeftExpression
            genNodePtr = fact.getRef(node.getLeftExpression()) ;
            if (genNodePtr != null) {
              Columbus.Csharp.Asg.Nodes.Expression.ExpressionSyntax endNodeRef = (Columbus.Csharp.Asg.Nodes.Expression.ExpressionSyntax)(genNodePtr);
              foreach (var visitor in visitorList) {
                visitor.visitJoinClauseSyntax_LeftExpression(node.Id, endNodeRef.Id);
              }

              clearStoppedVisitors();
              if(needPreorderStop)
                return;

              if ((!fact.IsFilterTurnedOn && !visitFilteredEdge) || (fact.getFilterState(endNodeRef.Id) == Filter.FilterState.NotFiltered) || (!originalFilterState && visitFilteredEdge)) {
                  endNodeRef.accept(this);
              }
              foreach (var visitor in visitorList) {
                visitor.visitEndJoinClauseSyntax_LeftExpression(node.Id, endNodeRef.Id);
              }

              clearStoppedVisitors();
              if(needPreorderStop)
                return;

            }

            // edge: RightExpression
            genNodePtr = fact.getRef(node.getRightExpression()) ;
            if (genNodePtr != null) {
              Columbus.Csharp.Asg.Nodes.Expression.ExpressionSyntax endNodeRef = (Columbus.Csharp.Asg.Nodes.Expression.ExpressionSyntax)(genNodePtr);
              foreach (var visitor in visitorList) {
                visitor.visitJoinClauseSyntax_RightExpression(node.Id, endNodeRef.Id);
              }

              clearStoppedVisitors();
              if(needPreorderStop)
                return;

              if ((!fact.IsFilterTurnedOn && !visitFilteredEdge) || (fact.getFilterState(endNodeRef.Id) == Filter.FilterState.NotFiltered) || (!originalFilterState && visitFilteredEdge)) {
                  endNodeRef.accept(this);
              }
              foreach (var visitor in visitorList) {
                visitor.visitEndJoinClauseSyntax_RightExpression(node.Id, endNodeRef.Id);
              }

              clearStoppedVisitors();
              if(needPreorderStop)
                return;

            }

            // edge: Type
            genNodePtr = fact.getRef(node.getType()) ;
            if (genNodePtr != null) {
              Columbus.Csharp.Asg.Nodes.Expression.TypeSyntax endNodeRef = (Columbus.Csharp.Asg.Nodes.Expression.TypeSyntax)(genNodePtr);
              foreach (var visitor in visitorList) {
                visitor.visitJoinClauseSyntax_Type(node.Id, endNodeRef.Id);
              }

              clearStoppedVisitors();
              if(needPreorderStop)
                return;

              if ((!fact.IsFilterTurnedOn && !visitFilteredEdge) || (fact.getFilterState(endNodeRef.Id) == Filter.FilterState.NotFiltered) || (!originalFilterState && visitFilteredEdge)) {
                  endNodeRef.accept(this);
              }
              foreach (var visitor in visitorList) {
                visitor.visitEndJoinClauseSyntax_Type(node.Id, endNodeRef.Id);
              }

              clearStoppedVisitors();
              if(needPreorderStop)
                return;

            }
        }

        public override void visit(Columbus.Csharp.Asg.Nodes.Structure.JoinClauseSyntax node, bool callFirst = true){
          if (safeMode || visitCrossEdgeTree) {
            if (safeMode) {
              if (visitedNodes[(int)node.Id]) { // for safemode
                return;
              }
            }
            visitedNodes[(int)node.Id] = true;
          }

          foreach (var visitor in visitorList) {
            visitor.visit(node);
            incVisitorDepth(visitor);
          }

          clearStoppedVisitors();
          if(needPreorderStop)
            return;

          visitAllEdges(node, true);

          foreach (var visitor in visitorList) {
            decVisitorDepth(visitor);
            visitor.visitEnd(node);
          }

          clearStoppedVisitors();
        }

        /// <summary>
        /// It call the traversal for the edges
        /// </summary>
        /// <param name="node">[in] The node with own type</param>
        /// <param name="callVirtualBase">[in] This paramater is don't used just api copatibility used.</param>
        public void visitAllEdges(Columbus.Csharp.Asg.Nodes.Structure.JoinIntoClauseSyntax node, bool callFirst = true){
            visitAllEdges((Columbus.Csharp.Asg.Nodes.Base.Positioned)(node),false);
        }

        public override void visit(Columbus.Csharp.Asg.Nodes.Structure.JoinIntoClauseSyntax node, bool callFirst = true){
          if (safeMode || visitCrossEdgeTree) {
            if (safeMode) {
              if (visitedNodes[(int)node.Id]) { // for safemode
                return;
              }
            }
            visitedNodes[(int)node.Id] = true;
          }

          foreach (var visitor in visitorList) {
            visitor.visit(node);
            incVisitorDepth(visitor);
          }

          clearStoppedVisitors();
          if(needPreorderStop)
            return;

          visitAllEdges(node, true);

          foreach (var visitor in visitorList) {
            decVisitorDepth(visitor);
            visitor.visitEnd(node);
          }

          clearStoppedVisitors();
        }

        /// <summary>
        /// It call the traversal for the edges
        /// </summary>
        /// <param name="node">[in] The node with own type</param>
        /// <param name="callVirtualBase">[in] This paramater is don't used just api copatibility used.</param>
        public void visitAllEdges(Columbus.Csharp.Asg.Nodes.Structure.LetClauseSyntax node, bool callFirst = true){
            visitAllEdges((Columbus.Csharp.Asg.Nodes.Structure.QueryClauseSyntax)(node),false);


            Columbus.Csharp.Asg.Nodes.Base.Base genNodePtr;
            // edge: Expression
            genNodePtr = fact.getRef(node.getExpression()) ;
            if (genNodePtr != null) {
              Columbus.Csharp.Asg.Nodes.Expression.ExpressionSyntax endNodeRef = (Columbus.Csharp.Asg.Nodes.Expression.ExpressionSyntax)(genNodePtr);
              foreach (var visitor in visitorList) {
                visitor.visitLetClauseSyntax_Expression(node.Id, endNodeRef.Id);
              }

              clearStoppedVisitors();
              if(needPreorderStop)
                return;

              if ((!fact.IsFilterTurnedOn && !visitFilteredEdge) || (fact.getFilterState(endNodeRef.Id) == Filter.FilterState.NotFiltered) || (!originalFilterState && visitFilteredEdge)) {
                  endNodeRef.accept(this);
              }
              foreach (var visitor in visitorList) {
                visitor.visitEndLetClauseSyntax_Expression(node.Id, endNodeRef.Id);
              }

              clearStoppedVisitors();
              if(needPreorderStop)
                return;

            }
        }

        public override void visit(Columbus.Csharp.Asg.Nodes.Structure.LetClauseSyntax node, bool callFirst = true){
          if (safeMode || visitCrossEdgeTree) {
            if (safeMode) {
              if (visitedNodes[(int)node.Id]) { // for safemode
                return;
              }
            }
            visitedNodes[(int)node.Id] = true;
          }

          foreach (var visitor in visitorList) {
            visitor.visit(node);
            incVisitorDepth(visitor);
          }

          clearStoppedVisitors();
          if(needPreorderStop)
            return;

          visitAllEdges(node, true);

          foreach (var visitor in visitorList) {
            decVisitorDepth(visitor);
            visitor.visitEnd(node);
          }

          clearStoppedVisitors();
        }

        /// <summary>
        /// It call the traversal for the edges
        /// </summary>
        /// <param name="node">[in] The node with own type</param>
        /// <param name="callVirtualBase">[in] This paramater is don't used just api copatibility used.</param>
        public void visitAllEdges(Columbus.Csharp.Asg.Nodes.Structure.MemberCrefSyntax node, bool callFirst = true){
            visitAllEdges((Columbus.Csharp.Asg.Nodes.Structure.CrefSyntax)(node),false);
        }

        /// <summary>
        /// It call the traversal for the edges
        /// </summary>
        /// <param name="node">[in] The node with own type</param>
        /// <param name="callVirtualBase">[in] This paramater is don't used just api copatibility used.</param>
        public void visitAllEdges(Columbus.Csharp.Asg.Nodes.Structure.MemberDeclarationSyntax node, bool callFirst = true){
            visitAllEdges((Columbus.Csharp.Asg.Nodes.Base.Positioned)(node),false);
        }

        /// <summary>
        /// It call the traversal for the edges
        /// </summary>
        /// <param name="node">[in] The node with own type</param>
        /// <param name="callVirtualBase">[in] This paramater is don't used just api copatibility used.</param>
        public void visitAllEdges(Columbus.Csharp.Asg.Nodes.Structure.MethodDeclarationSyntax node, bool callFirst = true){
            visitAllEdges((Columbus.Csharp.Asg.Nodes.Structure.BaseMethodDeclarationSyntax)(node),false);


            // edge: ConstraintClauses
            ListIterator<Columbus.Csharp.Asg.Nodes.Structure.TypeParameterConstraintClauseSyntax> iteratorForConstraintClauses = node.ConstraintClausesListIteratorBegin;
            while (iteratorForConstraintClauses.getValue() != null) {
               Columbus.Csharp.Asg.Nodes.Structure.TypeParameterConstraintClauseSyntax endNodeRef = (Columbus.Csharp.Asg.Nodes.Structure.TypeParameterConstraintClauseSyntax)iteratorForConstraintClauses.getValue();
              foreach (var visitor in visitorList) {
                visitor.visitMethodDeclarationSyntax_ConstraintClauses(node.Id, endNodeRef.Id);
              }

              clearStoppedVisitors();
              if(needPreorderStop)
                return;

              if ((!fact.IsFilterTurnedOn && !visitFilteredEdge) || (fact.getFilterState(endNodeRef.Id) == Filter.FilterState.NotFiltered) || (!originalFilterState && visitFilteredEdge)) {
                  endNodeRef.accept(this);
              }
              foreach (var visitor in visitorList) {
                visitor.visitEndMethodDeclarationSyntax_ConstraintClauses(node.Id, endNodeRef.Id);
              }

              clearStoppedVisitors();
              if(needPreorderStop)
                return;

            iteratorForConstraintClauses = iteratorForConstraintClauses.getNext();
            }

            Columbus.Csharp.Asg.Nodes.Base.Base genNodePtr;
            // edge: ExplicitInterfaceSpecifier
            genNodePtr = fact.getRef(node.getExplicitInterfaceSpecifier()) ;
            if (genNodePtr != null) {
              Columbus.Csharp.Asg.Nodes.Structure.ExplicitInterfaceSpecifierSyntax endNodeRef = (Columbus.Csharp.Asg.Nodes.Structure.ExplicitInterfaceSpecifierSyntax)(genNodePtr);
              foreach (var visitor in visitorList) {
                visitor.visitMethodDeclarationSyntax_ExplicitInterfaceSpecifier(node.Id, endNodeRef.Id);
              }

              clearStoppedVisitors();
              if(needPreorderStop)
                return;

              if ((!fact.IsFilterTurnedOn && !visitFilteredEdge) || (fact.getFilterState(endNodeRef.Id) == Filter.FilterState.NotFiltered) || (!originalFilterState && visitFilteredEdge)) {
                  endNodeRef.accept(this);
              }
              foreach (var visitor in visitorList) {
                visitor.visitEndMethodDeclarationSyntax_ExplicitInterfaceSpecifier(node.Id, endNodeRef.Id);
              }

              clearStoppedVisitors();
              if(needPreorderStop)
                return;

            }

            // edge: ReturnType
            genNodePtr = fact.getRef(node.getReturnType()) ;
            if (genNodePtr != null) {
              Columbus.Csharp.Asg.Nodes.Expression.TypeSyntax endNodeRef = (Columbus.Csharp.Asg.Nodes.Expression.TypeSyntax)(genNodePtr);
              foreach (var visitor in visitorList) {
                visitor.visitMethodDeclarationSyntax_ReturnType(node.Id, endNodeRef.Id);
              }

              clearStoppedVisitors();
              if(needPreorderStop)
                return;

              if ((!fact.IsFilterTurnedOn && !visitFilteredEdge) || (fact.getFilterState(endNodeRef.Id) == Filter.FilterState.NotFiltered) || (!originalFilterState && visitFilteredEdge)) {
                  endNodeRef.accept(this);
              }
              foreach (var visitor in visitorList) {
                visitor.visitEndMethodDeclarationSyntax_ReturnType(node.Id, endNodeRef.Id);
              }

              clearStoppedVisitors();
              if(needPreorderStop)
                return;

            }
        }

        public override void visit(Columbus.Csharp.Asg.Nodes.Structure.MethodDeclarationSyntax node, bool callFirst = true){
          if (safeMode || visitCrossEdgeTree) {
            if (safeMode) {
              if (visitedNodes[(int)node.Id]) { // for safemode
                return;
              }
            }
            visitedNodes[(int)node.Id] = true;
          }

          foreach (var visitor in visitorList) {
            visitor.visit(node);
            incVisitorDepth(visitor);
          }

          clearStoppedVisitors();
          if(needPreorderStop)
            return;

          visitAllEdges(node, true);

          foreach (var visitor in visitorList) {
            decVisitorDepth(visitor);
            visitor.visitEnd(node);
          }

          clearStoppedVisitors();
        }

        /// <summary>
        /// It call the traversal for the edges
        /// </summary>
        /// <param name="node">[in] The node with own type</param>
        /// <param name="callVirtualBase">[in] This paramater is don't used just api copatibility used.</param>
        public void visitAllEdges(Columbus.Csharp.Asg.Nodes.Structure.NameColonSyntax node, bool callFirst = true){
            visitAllEdges((Columbus.Csharp.Asg.Nodes.Base.Positioned)(node),false);


            Columbus.Csharp.Asg.Nodes.Base.Base genNodePtr;
            // edge: Name
            genNodePtr = fact.getRef(node.getName()) ;
            if (genNodePtr != null) {
              Columbus.Csharp.Asg.Nodes.Expression.IdentifierNameSyntax endNodeRef = (Columbus.Csharp.Asg.Nodes.Expression.IdentifierNameSyntax)(genNodePtr);
              foreach (var visitor in visitorList) {
                visitor.visitNameColonSyntax_Name(node.Id, endNodeRef.Id);
              }

              clearStoppedVisitors();
              if(needPreorderStop)
                return;

              if ((!fact.IsFilterTurnedOn && !visitFilteredEdge) || (fact.getFilterState(endNodeRef.Id) == Filter.FilterState.NotFiltered) || (!originalFilterState && visitFilteredEdge)) {
                  endNodeRef.accept(this);
              }
              foreach (var visitor in visitorList) {
                visitor.visitEndNameColonSyntax_Name(node.Id, endNodeRef.Id);
              }

              clearStoppedVisitors();
              if(needPreorderStop)
                return;

            }
        }

        public override void visit(Columbus.Csharp.Asg.Nodes.Structure.NameColonSyntax node, bool callFirst = true){
          if (safeMode || visitCrossEdgeTree) {
            if (safeMode) {
              if (visitedNodes[(int)node.Id]) { // for safemode
                return;
              }
            }
            visitedNodes[(int)node.Id] = true;
          }

          foreach (var visitor in visitorList) {
            visitor.visit(node);
            incVisitorDepth(visitor);
          }

          clearStoppedVisitors();
          if(needPreorderStop)
            return;

          visitAllEdges(node, true);

          foreach (var visitor in visitorList) {
            decVisitorDepth(visitor);
            visitor.visitEnd(node);
          }

          clearStoppedVisitors();
        }

        /// <summary>
        /// It call the traversal for the edges
        /// </summary>
        /// <param name="node">[in] The node with own type</param>
        /// <param name="callVirtualBase">[in] This paramater is don't used just api copatibility used.</param>
        public void visitAllEdges(Columbus.Csharp.Asg.Nodes.Structure.NameEqualsSyntax node, bool callFirst = true){
            visitAllEdges((Columbus.Csharp.Asg.Nodes.Base.Positioned)(node),false);


            Columbus.Csharp.Asg.Nodes.Base.Base genNodePtr;
            // edge: Name
            genNodePtr = fact.getRef(node.getName()) ;
            if (genNodePtr != null) {
              Columbus.Csharp.Asg.Nodes.Expression.IdentifierNameSyntax endNodeRef = (Columbus.Csharp.Asg.Nodes.Expression.IdentifierNameSyntax)(genNodePtr);
              foreach (var visitor in visitorList) {
                visitor.visitNameEqualsSyntax_Name(node.Id, endNodeRef.Id);
              }

              clearStoppedVisitors();
              if(needPreorderStop)
                return;

              if ((!fact.IsFilterTurnedOn && !visitFilteredEdge) || (fact.getFilterState(endNodeRef.Id) == Filter.FilterState.NotFiltered) || (!originalFilterState && visitFilteredEdge)) {
                  endNodeRef.accept(this);
              }
              foreach (var visitor in visitorList) {
                visitor.visitEndNameEqualsSyntax_Name(node.Id, endNodeRef.Id);
              }

              clearStoppedVisitors();
              if(needPreorderStop)
                return;

            }
        }

        public override void visit(Columbus.Csharp.Asg.Nodes.Structure.NameEqualsSyntax node, bool callFirst = true){
          if (safeMode || visitCrossEdgeTree) {
            if (safeMode) {
              if (visitedNodes[(int)node.Id]) { // for safemode
                return;
              }
            }
            visitedNodes[(int)node.Id] = true;
          }

          foreach (var visitor in visitorList) {
            visitor.visit(node);
            incVisitorDepth(visitor);
          }

          clearStoppedVisitors();
          if(needPreorderStop)
            return;

          visitAllEdges(node, true);

          foreach (var visitor in visitorList) {
            decVisitorDepth(visitor);
            visitor.visitEnd(node);
          }

          clearStoppedVisitors();
        }

        /// <summary>
        /// It call the traversal for the edges
        /// </summary>
        /// <param name="node">[in] The node with own type</param>
        /// <param name="callVirtualBase">[in] This paramater is don't used just api copatibility used.</param>
        public void visitAllEdges(Columbus.Csharp.Asg.Nodes.Structure.NameMemberCrefSyntax node, bool callFirst = true){
            visitAllEdges((Columbus.Csharp.Asg.Nodes.Structure.MemberCrefSyntax)(node),false);


            Columbus.Csharp.Asg.Nodes.Base.Base genNodePtr;
            // edge: Name
            genNodePtr = fact.getRef(node.getName()) ;
            if (genNodePtr != null) {
              Columbus.Csharp.Asg.Nodes.Expression.TypeSyntax endNodeRef = (Columbus.Csharp.Asg.Nodes.Expression.TypeSyntax)(genNodePtr);
              foreach (var visitor in visitorList) {
                visitor.visitNameMemberCrefSyntax_Name(node.Id, endNodeRef.Id);
              }

              clearStoppedVisitors();
              if(needPreorderStop)
                return;

              if ((!fact.IsFilterTurnedOn && !visitFilteredEdge) || (fact.getFilterState(endNodeRef.Id) == Filter.FilterState.NotFiltered) || (!originalFilterState && visitFilteredEdge)) {
                  endNodeRef.accept(this);
              }
              foreach (var visitor in visitorList) {
                visitor.visitEndNameMemberCrefSyntax_Name(node.Id, endNodeRef.Id);
              }

              clearStoppedVisitors();
              if(needPreorderStop)
                return;

            }

            // edge: Parameters
            genNodePtr = fact.getRef(node.getParameters()) ;
            if (genNodePtr != null) {
              Columbus.Csharp.Asg.Nodes.Structure.CrefParameterListSyntax endNodeRef = (Columbus.Csharp.Asg.Nodes.Structure.CrefParameterListSyntax)(genNodePtr);
              foreach (var visitor in visitorList) {
                visitor.visitNameMemberCrefSyntax_Parameters(node.Id, endNodeRef.Id);
              }

              clearStoppedVisitors();
              if(needPreorderStop)
                return;

              if ((!fact.IsFilterTurnedOn && !visitFilteredEdge) || (fact.getFilterState(endNodeRef.Id) == Filter.FilterState.NotFiltered) || (!originalFilterState && visitFilteredEdge)) {
                  endNodeRef.accept(this);
              }
              foreach (var visitor in visitorList) {
                visitor.visitEndNameMemberCrefSyntax_Parameters(node.Id, endNodeRef.Id);
              }

              clearStoppedVisitors();
              if(needPreorderStop)
                return;

            }
        }

        public override void visit(Columbus.Csharp.Asg.Nodes.Structure.NameMemberCrefSyntax node, bool callFirst = true){
          if (safeMode || visitCrossEdgeTree) {
            if (safeMode) {
              if (visitedNodes[(int)node.Id]) { // for safemode
                return;
              }
            }
            visitedNodes[(int)node.Id] = true;
          }

          foreach (var visitor in visitorList) {
            visitor.visit(node);
            incVisitorDepth(visitor);
          }

          clearStoppedVisitors();
          if(needPreorderStop)
            return;

          visitAllEdges(node, true);

          foreach (var visitor in visitorList) {
            decVisitorDepth(visitor);
            visitor.visitEnd(node);
          }

          clearStoppedVisitors();
        }

        /// <summary>
        /// It call the traversal for the edges
        /// </summary>
        /// <param name="node">[in] The node with own type</param>
        /// <param name="callVirtualBase">[in] This paramater is don't used just api copatibility used.</param>
        public void visitAllEdges(Columbus.Csharp.Asg.Nodes.Structure.NamespaceDeclarationSyntax node, bool callFirst = true){
            visitAllEdges((Columbus.Csharp.Asg.Nodes.Structure.MemberDeclarationSyntax)(node),false);


            // edge: Externs
            ListIterator<Columbus.Csharp.Asg.Nodes.Structure.ExternAliasDirectiveSyntax> iteratorForExterns = node.ExternsListIteratorBegin;
            while (iteratorForExterns.getValue() != null) {
               Columbus.Csharp.Asg.Nodes.Structure.ExternAliasDirectiveSyntax endNodeRef = (Columbus.Csharp.Asg.Nodes.Structure.ExternAliasDirectiveSyntax)iteratorForExterns.getValue();
              foreach (var visitor in visitorList) {
                visitor.visitNamespaceDeclarationSyntax_Externs(node.Id, endNodeRef.Id);
              }

              clearStoppedVisitors();
              if(needPreorderStop)
                return;

              if ((!fact.IsFilterTurnedOn && !visitFilteredEdge) || (fact.getFilterState(endNodeRef.Id) == Filter.FilterState.NotFiltered) || (!originalFilterState && visitFilteredEdge)) {
                  endNodeRef.accept(this);
              }
              foreach (var visitor in visitorList) {
                visitor.visitEndNamespaceDeclarationSyntax_Externs(node.Id, endNodeRef.Id);
              }

              clearStoppedVisitors();
              if(needPreorderStop)
                return;

            iteratorForExterns = iteratorForExterns.getNext();
            }

            // edge: Members
            ListIterator<Columbus.Csharp.Asg.Nodes.Structure.MemberDeclarationSyntax> iteratorForMembers = node.MembersListIteratorBegin;
            while (iteratorForMembers.getValue() != null) {
               Columbus.Csharp.Asg.Nodes.Structure.MemberDeclarationSyntax endNodeRef = (Columbus.Csharp.Asg.Nodes.Structure.MemberDeclarationSyntax)iteratorForMembers.getValue();
              foreach (var visitor in visitorList) {
                visitor.visitNamespaceDeclarationSyntax_Members(node.Id, endNodeRef.Id);
              }

              clearStoppedVisitors();
              if(needPreorderStop)
                return;

              if ((!fact.IsFilterTurnedOn && !visitFilteredEdge) || (fact.getFilterState(endNodeRef.Id) == Filter.FilterState.NotFiltered) || (!originalFilterState && visitFilteredEdge)) {
                  endNodeRef.accept(this);
              }
              foreach (var visitor in visitorList) {
                visitor.visitEndNamespaceDeclarationSyntax_Members(node.Id, endNodeRef.Id);
              }

              clearStoppedVisitors();
              if(needPreorderStop)
                return;

            iteratorForMembers = iteratorForMembers.getNext();
            }

            Columbus.Csharp.Asg.Nodes.Base.Base genNodePtr;
            // edge: Name
            genNodePtr = fact.getRef(node.getName()) ;
            if (genNodePtr != null) {
              Columbus.Csharp.Asg.Nodes.Expression.NameSyntax endNodeRef = (Columbus.Csharp.Asg.Nodes.Expression.NameSyntax)(genNodePtr);
              foreach (var visitor in visitorList) {
                visitor.visitNamespaceDeclarationSyntax_Name(node.Id, endNodeRef.Id);
              }

              clearStoppedVisitors();
              if(needPreorderStop)
                return;

              if ((!fact.IsFilterTurnedOn && !visitFilteredEdge) || (fact.getFilterState(endNodeRef.Id) == Filter.FilterState.NotFiltered) || (!originalFilterState && visitFilteredEdge)) {
                  endNodeRef.accept(this);
              }
              foreach (var visitor in visitorList) {
                visitor.visitEndNamespaceDeclarationSyntax_Name(node.Id, endNodeRef.Id);
              }

              clearStoppedVisitors();
              if(needPreorderStop)
                return;

            }

            // edge: Usings
            ListIterator<Columbus.Csharp.Asg.Nodes.Structure.UsingDirectiveSyntax> iteratorForUsings = node.UsingsListIteratorBegin;
            while (iteratorForUsings.getValue() != null) {
               Columbus.Csharp.Asg.Nodes.Structure.UsingDirectiveSyntax endNodeRef = (Columbus.Csharp.Asg.Nodes.Structure.UsingDirectiveSyntax)iteratorForUsings.getValue();
              foreach (var visitor in visitorList) {
                visitor.visitNamespaceDeclarationSyntax_Usings(node.Id, endNodeRef.Id);
              }

              clearStoppedVisitors();
              if(needPreorderStop)
                return;

              if ((!fact.IsFilterTurnedOn && !visitFilteredEdge) || (fact.getFilterState(endNodeRef.Id) == Filter.FilterState.NotFiltered) || (!originalFilterState && visitFilteredEdge)) {
                  endNodeRef.accept(this);
              }
              foreach (var visitor in visitorList) {
                visitor.visitEndNamespaceDeclarationSyntax_Usings(node.Id, endNodeRef.Id);
              }

              clearStoppedVisitors();
              if(needPreorderStop)
                return;

            iteratorForUsings = iteratorForUsings.getNext();
            }
        }

        public override void visit(Columbus.Csharp.Asg.Nodes.Structure.NamespaceDeclarationSyntax node, bool callFirst = true){
          if (safeMode || visitCrossEdgeTree) {
            if (safeMode) {
              if (visitedNodes[(int)node.Id]) { // for safemode
                return;
              }
            }
            visitedNodes[(int)node.Id] = true;
          }

          foreach (var visitor in visitorList) {
            visitor.visit(node);
            incVisitorDepth(visitor);
          }

          clearStoppedVisitors();
          if(needPreorderStop)
            return;

          visitAllEdges(node, true);

          foreach (var visitor in visitorList) {
            decVisitorDepth(visitor);
            visitor.visitEnd(node);
          }

          clearStoppedVisitors();
        }

        /// <summary>
        /// It call the traversal for the edges
        /// </summary>
        /// <param name="node">[in] The node with own type</param>
        /// <param name="callVirtualBase">[in] This paramater is don't used just api copatibility used.</param>
        public void visitAllEdges(Columbus.Csharp.Asg.Nodes.Structure.OperatorDeclarationSyntax node, bool callFirst = true){
            visitAllEdges((Columbus.Csharp.Asg.Nodes.Structure.BaseMethodDeclarationSyntax)(node),false);


            Columbus.Csharp.Asg.Nodes.Base.Base genNodePtr;
            // edge: ReturnType
            genNodePtr = fact.getRef(node.getReturnType()) ;
            if (genNodePtr != null) {
              Columbus.Csharp.Asg.Nodes.Expression.TypeSyntax endNodeRef = (Columbus.Csharp.Asg.Nodes.Expression.TypeSyntax)(genNodePtr);
              foreach (var visitor in visitorList) {
                visitor.visitOperatorDeclarationSyntax_ReturnType(node.Id, endNodeRef.Id);
              }

              clearStoppedVisitors();
              if(needPreorderStop)
                return;

              if ((!fact.IsFilterTurnedOn && !visitFilteredEdge) || (fact.getFilterState(endNodeRef.Id) == Filter.FilterState.NotFiltered) || (!originalFilterState && visitFilteredEdge)) {
                  endNodeRef.accept(this);
              }
              foreach (var visitor in visitorList) {
                visitor.visitEndOperatorDeclarationSyntax_ReturnType(node.Id, endNodeRef.Id);
              }

              clearStoppedVisitors();
              if(needPreorderStop)
                return;

            }
        }

        public override void visit(Columbus.Csharp.Asg.Nodes.Structure.OperatorDeclarationSyntax node, bool callFirst = true){
          if (safeMode || visitCrossEdgeTree) {
            if (safeMode) {
              if (visitedNodes[(int)node.Id]) { // for safemode
                return;
              }
            }
            visitedNodes[(int)node.Id] = true;
          }

          foreach (var visitor in visitorList) {
            visitor.visit(node);
            incVisitorDepth(visitor);
          }

          clearStoppedVisitors();
          if(needPreorderStop)
            return;

          visitAllEdges(node, true);

          foreach (var visitor in visitorList) {
            decVisitorDepth(visitor);
            visitor.visitEnd(node);
          }

          clearStoppedVisitors();
        }

        /// <summary>
        /// It call the traversal for the edges
        /// </summary>
        /// <param name="node">[in] The node with own type</param>
        /// <param name="callVirtualBase">[in] This paramater is don't used just api copatibility used.</param>
        public void visitAllEdges(Columbus.Csharp.Asg.Nodes.Structure.OperatorMemberCrefSyntax node, bool callFirst = true){
            visitAllEdges((Columbus.Csharp.Asg.Nodes.Structure.MemberCrefSyntax)(node),false);


            Columbus.Csharp.Asg.Nodes.Base.Base genNodePtr;
            // edge: Parameters
            genNodePtr = fact.getRef(node.getParameters()) ;
            if (genNodePtr != null) {
              Columbus.Csharp.Asg.Nodes.Structure.CrefParameterListSyntax endNodeRef = (Columbus.Csharp.Asg.Nodes.Structure.CrefParameterListSyntax)(genNodePtr);
              foreach (var visitor in visitorList) {
                visitor.visitOperatorMemberCrefSyntax_Parameters(node.Id, endNodeRef.Id);
              }

              clearStoppedVisitors();
              if(needPreorderStop)
                return;

              if ((!fact.IsFilterTurnedOn && !visitFilteredEdge) || (fact.getFilterState(endNodeRef.Id) == Filter.FilterState.NotFiltered) || (!originalFilterState && visitFilteredEdge)) {
                  endNodeRef.accept(this);
              }
              foreach (var visitor in visitorList) {
                visitor.visitEndOperatorMemberCrefSyntax_Parameters(node.Id, endNodeRef.Id);
              }

              clearStoppedVisitors();
              if(needPreorderStop)
                return;

            }
        }

        public override void visit(Columbus.Csharp.Asg.Nodes.Structure.OperatorMemberCrefSyntax node, bool callFirst = true){
          if (safeMode || visitCrossEdgeTree) {
            if (safeMode) {
              if (visitedNodes[(int)node.Id]) { // for safemode
                return;
              }
            }
            visitedNodes[(int)node.Id] = true;
          }

          foreach (var visitor in visitorList) {
            visitor.visit(node);
            incVisitorDepth(visitor);
          }

          clearStoppedVisitors();
          if(needPreorderStop)
            return;

          visitAllEdges(node, true);

          foreach (var visitor in visitorList) {
            decVisitorDepth(visitor);
            visitor.visitEnd(node);
          }

          clearStoppedVisitors();
        }

        /// <summary>
        /// It call the traversal for the edges
        /// </summary>
        /// <param name="node">[in] The node with own type</param>
        /// <param name="callVirtualBase">[in] This paramater is don't used just api copatibility used.</param>
        public void visitAllEdges(Columbus.Csharp.Asg.Nodes.Structure.OrderByClauseSyntax node, bool callFirst = true){
            visitAllEdges((Columbus.Csharp.Asg.Nodes.Structure.QueryClauseSyntax)(node),false);


            // edge: Orderings
            ListIterator<Columbus.Csharp.Asg.Nodes.Structure.OrderingSyntax> iteratorForOrderings = node.OrderingsListIteratorBegin;
            while (iteratorForOrderings.getValue() != null) {
               Columbus.Csharp.Asg.Nodes.Structure.OrderingSyntax endNodeRef = (Columbus.Csharp.Asg.Nodes.Structure.OrderingSyntax)iteratorForOrderings.getValue();
              foreach (var visitor in visitorList) {
                visitor.visitOrderByClauseSyntax_Orderings(node.Id, endNodeRef.Id);
              }

              clearStoppedVisitors();
              if(needPreorderStop)
                return;

              if ((!fact.IsFilterTurnedOn && !visitFilteredEdge) || (fact.getFilterState(endNodeRef.Id) == Filter.FilterState.NotFiltered) || (!originalFilterState && visitFilteredEdge)) {
                  endNodeRef.accept(this);
              }
              foreach (var visitor in visitorList) {
                visitor.visitEndOrderByClauseSyntax_Orderings(node.Id, endNodeRef.Id);
              }

              clearStoppedVisitors();
              if(needPreorderStop)
                return;

            iteratorForOrderings = iteratorForOrderings.getNext();
            }
        }

        public override void visit(Columbus.Csharp.Asg.Nodes.Structure.OrderByClauseSyntax node, bool callFirst = true){
          if (safeMode || visitCrossEdgeTree) {
            if (safeMode) {
              if (visitedNodes[(int)node.Id]) { // for safemode
                return;
              }
            }
            visitedNodes[(int)node.Id] = true;
          }

          foreach (var visitor in visitorList) {
            visitor.visit(node);
            incVisitorDepth(visitor);
          }

          clearStoppedVisitors();
          if(needPreorderStop)
            return;

          visitAllEdges(node, true);

          foreach (var visitor in visitorList) {
            decVisitorDepth(visitor);
            visitor.visitEnd(node);
          }

          clearStoppedVisitors();
        }

        /// <summary>
        /// It call the traversal for the edges
        /// </summary>
        /// <param name="node">[in] The node with own type</param>
        /// <param name="callVirtualBase">[in] This paramater is don't used just api copatibility used.</param>
        public void visitAllEdges(Columbus.Csharp.Asg.Nodes.Structure.OrderingSyntax node, bool callFirst = true){
            visitAllEdges((Columbus.Csharp.Asg.Nodes.Base.Positioned)(node),false);


            Columbus.Csharp.Asg.Nodes.Base.Base genNodePtr;
            // edge: Expression
            genNodePtr = fact.getRef(node.getExpression()) ;
            if (genNodePtr != null) {
              Columbus.Csharp.Asg.Nodes.Expression.ExpressionSyntax endNodeRef = (Columbus.Csharp.Asg.Nodes.Expression.ExpressionSyntax)(genNodePtr);
              foreach (var visitor in visitorList) {
                visitor.visitOrderingSyntax_Expression(node.Id, endNodeRef.Id);
              }

              clearStoppedVisitors();
              if(needPreorderStop)
                return;

              if ((!fact.IsFilterTurnedOn && !visitFilteredEdge) || (fact.getFilterState(endNodeRef.Id) == Filter.FilterState.NotFiltered) || (!originalFilterState && visitFilteredEdge)) {
                  endNodeRef.accept(this);
              }
              foreach (var visitor in visitorList) {
                visitor.visitEndOrderingSyntax_Expression(node.Id, endNodeRef.Id);
              }

              clearStoppedVisitors();
              if(needPreorderStop)
                return;

            }
        }

        public override void visit(Columbus.Csharp.Asg.Nodes.Structure.OrderingSyntax node, bool callFirst = true){
          if (safeMode || visitCrossEdgeTree) {
            if (safeMode) {
              if (visitedNodes[(int)node.Id]) { // for safemode
                return;
              }
            }
            visitedNodes[(int)node.Id] = true;
          }

          foreach (var visitor in visitorList) {
            visitor.visit(node);
            incVisitorDepth(visitor);
          }

          clearStoppedVisitors();
          if(needPreorderStop)
            return;

          visitAllEdges(node, true);

          foreach (var visitor in visitorList) {
            decVisitorDepth(visitor);
            visitor.visitEnd(node);
          }

          clearStoppedVisitors();
        }

        /// <summary>
        /// It call the traversal for the edges
        /// </summary>
        /// <param name="node">[in] The node with own type</param>
        /// <param name="callVirtualBase">[in] This paramater is don't used just api copatibility used.</param>
        public void visitAllEdges(Columbus.Csharp.Asg.Nodes.Structure.ParameterListSyntax node, bool callFirst = true){
            visitAllEdges((Columbus.Csharp.Asg.Nodes.Structure.BaseParameterListSyntax)(node),false);
        }

        public override void visit(Columbus.Csharp.Asg.Nodes.Structure.ParameterListSyntax node, bool callFirst = true){
          if (safeMode || visitCrossEdgeTree) {
            if (safeMode) {
              if (visitedNodes[(int)node.Id]) { // for safemode
                return;
              }
            }
            visitedNodes[(int)node.Id] = true;
          }

          foreach (var visitor in visitorList) {
            visitor.visit(node);
            incVisitorDepth(visitor);
          }

          clearStoppedVisitors();
          if(needPreorderStop)
            return;

          visitAllEdges(node, true);

          foreach (var visitor in visitorList) {
            decVisitorDepth(visitor);
            visitor.visitEnd(node);
          }

          clearStoppedVisitors();
        }

        /// <summary>
        /// It call the traversal for the edges
        /// </summary>
        /// <param name="node">[in] The node with own type</param>
        /// <param name="callVirtualBase">[in] This paramater is don't used just api copatibility used.</param>
        public void visitAllEdges(Columbus.Csharp.Asg.Nodes.Structure.ParameterSyntax node, bool callFirst = true){
            visitAllEdges((Columbus.Csharp.Asg.Nodes.Base.Positioned)(node),false);


            // edge: AttributeLists
            ListIterator<Columbus.Csharp.Asg.Nodes.Structure.AttributeListSyntax> iteratorForAttributeLists = node.AttributeListsListIteratorBegin;
            while (iteratorForAttributeLists.getValue() != null) {
               Columbus.Csharp.Asg.Nodes.Structure.AttributeListSyntax endNodeRef = (Columbus.Csharp.Asg.Nodes.Structure.AttributeListSyntax)iteratorForAttributeLists.getValue();
              foreach (var visitor in visitorList) {
                visitor.visitParameterSyntax_AttributeLists(node.Id, endNodeRef.Id);
              }

              clearStoppedVisitors();
              if(needPreorderStop)
                return;

              if ((!fact.IsFilterTurnedOn && !visitFilteredEdge) || (fact.getFilterState(endNodeRef.Id) == Filter.FilterState.NotFiltered) || (!originalFilterState && visitFilteredEdge)) {
                  endNodeRef.accept(this);
              }
              foreach (var visitor in visitorList) {
                visitor.visitEndParameterSyntax_AttributeLists(node.Id, endNodeRef.Id);
              }

              clearStoppedVisitors();
              if(needPreorderStop)
                return;

            iteratorForAttributeLists = iteratorForAttributeLists.getNext();
            }

            Columbus.Csharp.Asg.Nodes.Base.Base genNodePtr;
            // edge: Default
            genNodePtr = fact.getRef(node.getDefault()) ;
            if (genNodePtr != null) {
              Columbus.Csharp.Asg.Nodes.Structure.EqualsValueClauseSyntax endNodeRef = (Columbus.Csharp.Asg.Nodes.Structure.EqualsValueClauseSyntax)(genNodePtr);
              foreach (var visitor in visitorList) {
                visitor.visitParameterSyntax_Default(node.Id, endNodeRef.Id);
              }

              clearStoppedVisitors();
              if(needPreorderStop)
                return;

              if ((!fact.IsFilterTurnedOn && !visitFilteredEdge) || (fact.getFilterState(endNodeRef.Id) == Filter.FilterState.NotFiltered) || (!originalFilterState && visitFilteredEdge)) {
                  endNodeRef.accept(this);
              }
              foreach (var visitor in visitorList) {
                visitor.visitEndParameterSyntax_Default(node.Id, endNodeRef.Id);
              }

              clearStoppedVisitors();
              if(needPreorderStop)
                return;

            }

            // edge: Type
            genNodePtr = fact.getRef(node.getType()) ;
            if (genNodePtr != null) {
              Columbus.Csharp.Asg.Nodes.Expression.TypeSyntax endNodeRef = (Columbus.Csharp.Asg.Nodes.Expression.TypeSyntax)(genNodePtr);
              foreach (var visitor in visitorList) {
                visitor.visitParameterSyntax_Type(node.Id, endNodeRef.Id);
              }

              clearStoppedVisitors();
              if(needPreorderStop)
                return;

              if ((!fact.IsFilterTurnedOn && !visitFilteredEdge) || (fact.getFilterState(endNodeRef.Id) == Filter.FilterState.NotFiltered) || (!originalFilterState && visitFilteredEdge)) {
                  endNodeRef.accept(this);
              }
              foreach (var visitor in visitorList) {
                visitor.visitEndParameterSyntax_Type(node.Id, endNodeRef.Id);
              }

              clearStoppedVisitors();
              if(needPreorderStop)
                return;

            }
        }

        public override void visit(Columbus.Csharp.Asg.Nodes.Structure.ParameterSyntax node, bool callFirst = true){
          if (safeMode || visitCrossEdgeTree) {
            if (safeMode) {
              if (visitedNodes[(int)node.Id]) { // for safemode
                return;
              }
            }
            visitedNodes[(int)node.Id] = true;
          }

          foreach (var visitor in visitorList) {
            visitor.visit(node);
            incVisitorDepth(visitor);
          }

          clearStoppedVisitors();
          if(needPreorderStop)
            return;

          visitAllEdges(node, true);

          foreach (var visitor in visitorList) {
            decVisitorDepth(visitor);
            visitor.visitEnd(node);
          }

          clearStoppedVisitors();
        }

        /// <summary>
        /// It call the traversal for the edges
        /// </summary>
        /// <param name="node">[in] The node with own type</param>
        /// <param name="callVirtualBase">[in] This paramater is don't used just api copatibility used.</param>
        public void visitAllEdges(Columbus.Csharp.Asg.Nodes.Structure.ParenthesizedVariableDesignationSyntax node, bool callFirst = true){
            visitAllEdges((Columbus.Csharp.Asg.Nodes.Structure.VariableDesignationSyntax)(node),false);


            // edge: Variables
            ListIterator<Columbus.Csharp.Asg.Nodes.Structure.VariableDesignationSyntax> iteratorForVariables = node.VariablesListIteratorBegin;
            while (iteratorForVariables.getValue() != null) {
               Columbus.Csharp.Asg.Nodes.Structure.VariableDesignationSyntax endNodeRef = (Columbus.Csharp.Asg.Nodes.Structure.VariableDesignationSyntax)iteratorForVariables.getValue();
              foreach (var visitor in visitorList) {
                visitor.visitParenthesizedVariableDesignationSyntax_Variables(node.Id, endNodeRef.Id);
              }

              clearStoppedVisitors();
              if(needPreorderStop)
                return;

              if ((!fact.IsFilterTurnedOn && !visitFilteredEdge) || (fact.getFilterState(endNodeRef.Id) == Filter.FilterState.NotFiltered) || (!originalFilterState && visitFilteredEdge)) {
                  endNodeRef.accept(this);
              }
              foreach (var visitor in visitorList) {
                visitor.visitEndParenthesizedVariableDesignationSyntax_Variables(node.Id, endNodeRef.Id);
              }

              clearStoppedVisitors();
              if(needPreorderStop)
                return;

            iteratorForVariables = iteratorForVariables.getNext();
            }
        }

        public override void visit(Columbus.Csharp.Asg.Nodes.Structure.ParenthesizedVariableDesignationSyntax node, bool callFirst = true){
          if (safeMode || visitCrossEdgeTree) {
            if (safeMode) {
              if (visitedNodes[(int)node.Id]) { // for safemode
                return;
              }
            }
            visitedNodes[(int)node.Id] = true;
          }

          foreach (var visitor in visitorList) {
            visitor.visit(node);
            incVisitorDepth(visitor);
          }

          clearStoppedVisitors();
          if(needPreorderStop)
            return;

          visitAllEdges(node, true);

          foreach (var visitor in visitorList) {
            decVisitorDepth(visitor);
            visitor.visitEnd(node);
          }

          clearStoppedVisitors();
        }

        /// <summary>
        /// It call the traversal for the edges
        /// </summary>
        /// <param name="node">[in] The node with own type</param>
        /// <param name="callVirtualBase">[in] This paramater is don't used just api copatibility used.</param>
        public void visitAllEdges(Columbus.Csharp.Asg.Nodes.Structure.PatternSyntax node, bool callFirst = true){
            visitAllEdges((Columbus.Csharp.Asg.Nodes.Base.Positioned)(node),false);
        }

        /// <summary>
        /// It call the traversal for the edges
        /// </summary>
        /// <param name="node">[in] The node with own type</param>
        /// <param name="callVirtualBase">[in] This paramater is don't used just api copatibility used.</param>
        public void visitAllEdges(Columbus.Csharp.Asg.Nodes.Structure.PositionalPatternClauseSyntax node, bool callFirst = true){
            visitAllEdges((Columbus.Csharp.Asg.Nodes.Base.Positioned)(node),false);


            // edge: Subpatterns
            ListIterator<Columbus.Csharp.Asg.Nodes.Structure.SubpatternSyntax> iteratorForSubpatterns = node.SubpatternsListIteratorBegin;
            while (iteratorForSubpatterns.getValue() != null) {
               Columbus.Csharp.Asg.Nodes.Structure.SubpatternSyntax endNodeRef = (Columbus.Csharp.Asg.Nodes.Structure.SubpatternSyntax)iteratorForSubpatterns.getValue();
              foreach (var visitor in visitorList) {
                visitor.visitPositionalPatternClauseSyntax_Subpatterns(node.Id, endNodeRef.Id);
              }

              clearStoppedVisitors();
              if(needPreorderStop)
                return;

              if ((!fact.IsFilterTurnedOn && !visitFilteredEdge) || (fact.getFilterState(endNodeRef.Id) == Filter.FilterState.NotFiltered) || (!originalFilterState && visitFilteredEdge)) {
                  endNodeRef.accept(this);
              }
              foreach (var visitor in visitorList) {
                visitor.visitEndPositionalPatternClauseSyntax_Subpatterns(node.Id, endNodeRef.Id);
              }

              clearStoppedVisitors();
              if(needPreorderStop)
                return;

            iteratorForSubpatterns = iteratorForSubpatterns.getNext();
            }
        }

        public override void visit(Columbus.Csharp.Asg.Nodes.Structure.PositionalPatternClauseSyntax node, bool callFirst = true){
          if (safeMode || visitCrossEdgeTree) {
            if (safeMode) {
              if (visitedNodes[(int)node.Id]) { // for safemode
                return;
              }
            }
            visitedNodes[(int)node.Id] = true;
          }

          foreach (var visitor in visitorList) {
            visitor.visit(node);
            incVisitorDepth(visitor);
          }

          clearStoppedVisitors();
          if(needPreorderStop)
            return;

          visitAllEdges(node, true);

          foreach (var visitor in visitorList) {
            decVisitorDepth(visitor);
            visitor.visitEnd(node);
          }

          clearStoppedVisitors();
        }

        /// <summary>
        /// It call the traversal for the edges
        /// </summary>
        /// <param name="node">[in] The node with own type</param>
        /// <param name="callVirtualBase">[in] This paramater is don't used just api copatibility used.</param>
        public void visitAllEdges(Columbus.Csharp.Asg.Nodes.Structure.PropertyDeclarationSyntax node, bool callFirst = true){
            visitAllEdges((Columbus.Csharp.Asg.Nodes.Structure.BasePropertyDeclarationSyntax)(node),false);


            Columbus.Csharp.Asg.Nodes.Base.Base genNodePtr;
            // edge: ExpressionBody
            genNodePtr = fact.getRef(node.getExpressionBody()) ;
            if (genNodePtr != null) {
              Columbus.Csharp.Asg.Nodes.Structure.ArrowExpressionClauseSyntax endNodeRef = (Columbus.Csharp.Asg.Nodes.Structure.ArrowExpressionClauseSyntax)(genNodePtr);
              foreach (var visitor in visitorList) {
                visitor.visitPropertyDeclarationSyntax_ExpressionBody(node.Id, endNodeRef.Id);
              }

              clearStoppedVisitors();
              if(needPreorderStop)
                return;

              if ((!fact.IsFilterTurnedOn && !visitFilteredEdge) || (fact.getFilterState(endNodeRef.Id) == Filter.FilterState.NotFiltered) || (!originalFilterState && visitFilteredEdge)) {
                  endNodeRef.accept(this);
              }
              foreach (var visitor in visitorList) {
                visitor.visitEndPropertyDeclarationSyntax_ExpressionBody(node.Id, endNodeRef.Id);
              }

              clearStoppedVisitors();
              if(needPreorderStop)
                return;

            }

            // edge: Initializer
            genNodePtr = fact.getRef(node.getInitializer()) ;
            if (genNodePtr != null) {
              Columbus.Csharp.Asg.Nodes.Structure.EqualsValueClauseSyntax endNodeRef = (Columbus.Csharp.Asg.Nodes.Structure.EqualsValueClauseSyntax)(genNodePtr);
              foreach (var visitor in visitorList) {
                visitor.visitPropertyDeclarationSyntax_Initializer(node.Id, endNodeRef.Id);
              }

              clearStoppedVisitors();
              if(needPreorderStop)
                return;

              if ((!fact.IsFilterTurnedOn && !visitFilteredEdge) || (fact.getFilterState(endNodeRef.Id) == Filter.FilterState.NotFiltered) || (!originalFilterState && visitFilteredEdge)) {
                  endNodeRef.accept(this);
              }
              foreach (var visitor in visitorList) {
                visitor.visitEndPropertyDeclarationSyntax_Initializer(node.Id, endNodeRef.Id);
              }

              clearStoppedVisitors();
              if(needPreorderStop)
                return;

            }
        }

        public override void visit(Columbus.Csharp.Asg.Nodes.Structure.PropertyDeclarationSyntax node, bool callFirst = true){
          if (safeMode || visitCrossEdgeTree) {
            if (safeMode) {
              if (visitedNodes[(int)node.Id]) { // for safemode
                return;
              }
            }
            visitedNodes[(int)node.Id] = true;
          }

          foreach (var visitor in visitorList) {
            visitor.visit(node);
            incVisitorDepth(visitor);
          }

          clearStoppedVisitors();
          if(needPreorderStop)
            return;

          visitAllEdges(node, true);

          foreach (var visitor in visitorList) {
            decVisitorDepth(visitor);
            visitor.visitEnd(node);
          }

          clearStoppedVisitors();
        }

        /// <summary>
        /// It call the traversal for the edges
        /// </summary>
        /// <param name="node">[in] The node with own type</param>
        /// <param name="callVirtualBase">[in] This paramater is don't used just api copatibility used.</param>
        public void visitAllEdges(Columbus.Csharp.Asg.Nodes.Structure.PropertyPatternClauseSyntax node, bool callFirst = true){
            visitAllEdges((Columbus.Csharp.Asg.Nodes.Base.Positioned)(node),false);


            // edge: Subpatterns
            ListIterator<Columbus.Csharp.Asg.Nodes.Structure.SubpatternSyntax> iteratorForSubpatterns = node.SubpatternsListIteratorBegin;
            while (iteratorForSubpatterns.getValue() != null) {
               Columbus.Csharp.Asg.Nodes.Structure.SubpatternSyntax endNodeRef = (Columbus.Csharp.Asg.Nodes.Structure.SubpatternSyntax)iteratorForSubpatterns.getValue();
              foreach (var visitor in visitorList) {
                visitor.visitPropertyPatternClauseSyntax_Subpatterns(node.Id, endNodeRef.Id);
              }

              clearStoppedVisitors();
              if(needPreorderStop)
                return;

              if ((!fact.IsFilterTurnedOn && !visitFilteredEdge) || (fact.getFilterState(endNodeRef.Id) == Filter.FilterState.NotFiltered) || (!originalFilterState && visitFilteredEdge)) {
                  endNodeRef.accept(this);
              }
              foreach (var visitor in visitorList) {
                visitor.visitEndPropertyPatternClauseSyntax_Subpatterns(node.Id, endNodeRef.Id);
              }

              clearStoppedVisitors();
              if(needPreorderStop)
                return;

            iteratorForSubpatterns = iteratorForSubpatterns.getNext();
            }
        }

        public override void visit(Columbus.Csharp.Asg.Nodes.Structure.PropertyPatternClauseSyntax node, bool callFirst = true){
          if (safeMode || visitCrossEdgeTree) {
            if (safeMode) {
              if (visitedNodes[(int)node.Id]) { // for safemode
                return;
              }
            }
            visitedNodes[(int)node.Id] = true;
          }

          foreach (var visitor in visitorList) {
            visitor.visit(node);
            incVisitorDepth(visitor);
          }

          clearStoppedVisitors();
          if(needPreorderStop)
            return;

          visitAllEdges(node, true);

          foreach (var visitor in visitorList) {
            decVisitorDepth(visitor);
            visitor.visitEnd(node);
          }

          clearStoppedVisitors();
        }

        /// <summary>
        /// It call the traversal for the edges
        /// </summary>
        /// <param name="node">[in] The node with own type</param>
        /// <param name="callVirtualBase">[in] This paramater is don't used just api copatibility used.</param>
        public void visitAllEdges(Columbus.Csharp.Asg.Nodes.Structure.QualifiedCrefSyntax node, bool callFirst = true){
            visitAllEdges((Columbus.Csharp.Asg.Nodes.Structure.CrefSyntax)(node),false);


            Columbus.Csharp.Asg.Nodes.Base.Base genNodePtr;
            // edge: Container
            genNodePtr = fact.getRef(node.getContainer()) ;
            if (genNodePtr != null) {
              Columbus.Csharp.Asg.Nodes.Expression.TypeSyntax endNodeRef = (Columbus.Csharp.Asg.Nodes.Expression.TypeSyntax)(genNodePtr);
              foreach (var visitor in visitorList) {
                visitor.visitQualifiedCrefSyntax_Container(node.Id, endNodeRef.Id);
              }

              clearStoppedVisitors();
              if(needPreorderStop)
                return;

              if ((!fact.IsFilterTurnedOn && !visitFilteredEdge) || (fact.getFilterState(endNodeRef.Id) == Filter.FilterState.NotFiltered) || (!originalFilterState && visitFilteredEdge)) {
                  endNodeRef.accept(this);
              }
              foreach (var visitor in visitorList) {
                visitor.visitEndQualifiedCrefSyntax_Container(node.Id, endNodeRef.Id);
              }

              clearStoppedVisitors();
              if(needPreorderStop)
                return;

            }

            // edge: Member
            genNodePtr = fact.getRef(node.getMember()) ;
            if (genNodePtr != null) {
              Columbus.Csharp.Asg.Nodes.Structure.MemberCrefSyntax endNodeRef = (Columbus.Csharp.Asg.Nodes.Structure.MemberCrefSyntax)(genNodePtr);
              foreach (var visitor in visitorList) {
                visitor.visitQualifiedCrefSyntax_Member(node.Id, endNodeRef.Id);
              }

              clearStoppedVisitors();
              if(needPreorderStop)
                return;

              if ((!fact.IsFilterTurnedOn && !visitFilteredEdge) || (fact.getFilterState(endNodeRef.Id) == Filter.FilterState.NotFiltered) || (!originalFilterState && visitFilteredEdge)) {
                  endNodeRef.accept(this);
              }
              foreach (var visitor in visitorList) {
                visitor.visitEndQualifiedCrefSyntax_Member(node.Id, endNodeRef.Id);
              }

              clearStoppedVisitors();
              if(needPreorderStop)
                return;

            }
        }

        public override void visit(Columbus.Csharp.Asg.Nodes.Structure.QualifiedCrefSyntax node, bool callFirst = true){
          if (safeMode || visitCrossEdgeTree) {
            if (safeMode) {
              if (visitedNodes[(int)node.Id]) { // for safemode
                return;
              }
            }
            visitedNodes[(int)node.Id] = true;
          }

          foreach (var visitor in visitorList) {
            visitor.visit(node);
            incVisitorDepth(visitor);
          }

          clearStoppedVisitors();
          if(needPreorderStop)
            return;

          visitAllEdges(node, true);

          foreach (var visitor in visitorList) {
            decVisitorDepth(visitor);
            visitor.visitEnd(node);
          }

          clearStoppedVisitors();
        }

        /// <summary>
        /// It call the traversal for the edges
        /// </summary>
        /// <param name="node">[in] The node with own type</param>
        /// <param name="callVirtualBase">[in] This paramater is don't used just api copatibility used.</param>
        public void visitAllEdges(Columbus.Csharp.Asg.Nodes.Structure.QueryBodySyntax node, bool callFirst = true){
            visitAllEdges((Columbus.Csharp.Asg.Nodes.Base.Positioned)(node),false);


            // edge: Clauses
            ListIterator<Columbus.Csharp.Asg.Nodes.Structure.QueryClauseSyntax> iteratorForClauses = node.ClausesListIteratorBegin;
            while (iteratorForClauses.getValue() != null) {
               Columbus.Csharp.Asg.Nodes.Structure.QueryClauseSyntax endNodeRef = (Columbus.Csharp.Asg.Nodes.Structure.QueryClauseSyntax)iteratorForClauses.getValue();
              foreach (var visitor in visitorList) {
                visitor.visitQueryBodySyntax_Clauses(node.Id, endNodeRef.Id);
              }

              clearStoppedVisitors();
              if(needPreorderStop)
                return;

              if ((!fact.IsFilterTurnedOn && !visitFilteredEdge) || (fact.getFilterState(endNodeRef.Id) == Filter.FilterState.NotFiltered) || (!originalFilterState && visitFilteredEdge)) {
                  endNodeRef.accept(this);
              }
              foreach (var visitor in visitorList) {
                visitor.visitEndQueryBodySyntax_Clauses(node.Id, endNodeRef.Id);
              }

              clearStoppedVisitors();
              if(needPreorderStop)
                return;

            iteratorForClauses = iteratorForClauses.getNext();
            }

            Columbus.Csharp.Asg.Nodes.Base.Base genNodePtr;
            // edge: Continuation
            genNodePtr = fact.getRef(node.getContinuation()) ;
            if (genNodePtr != null) {
              Columbus.Csharp.Asg.Nodes.Structure.QueryContinuationSyntax endNodeRef = (Columbus.Csharp.Asg.Nodes.Structure.QueryContinuationSyntax)(genNodePtr);
              foreach (var visitor in visitorList) {
                visitor.visitQueryBodySyntax_Continuation(node.Id, endNodeRef.Id);
              }

              clearStoppedVisitors();
              if(needPreorderStop)
                return;

              if ((!fact.IsFilterTurnedOn && !visitFilteredEdge) || (fact.getFilterState(endNodeRef.Id) == Filter.FilterState.NotFiltered) || (!originalFilterState && visitFilteredEdge)) {
                  endNodeRef.accept(this);
              }
              foreach (var visitor in visitorList) {
                visitor.visitEndQueryBodySyntax_Continuation(node.Id, endNodeRef.Id);
              }

              clearStoppedVisitors();
              if(needPreorderStop)
                return;

            }

            // edge: SelectOrGroup
            genNodePtr = fact.getRef(node.getSelectOrGroup()) ;
            if (genNodePtr != null) {
              Columbus.Csharp.Asg.Nodes.Structure.SelectOrGroupClauseSyntax endNodeRef = (Columbus.Csharp.Asg.Nodes.Structure.SelectOrGroupClauseSyntax)(genNodePtr);
              foreach (var visitor in visitorList) {
                visitor.visitQueryBodySyntax_SelectOrGroup(node.Id, endNodeRef.Id);
              }

              clearStoppedVisitors();
              if(needPreorderStop)
                return;

              if ((!fact.IsFilterTurnedOn && !visitFilteredEdge) || (fact.getFilterState(endNodeRef.Id) == Filter.FilterState.NotFiltered) || (!originalFilterState && visitFilteredEdge)) {
                  endNodeRef.accept(this);
              }
              foreach (var visitor in visitorList) {
                visitor.visitEndQueryBodySyntax_SelectOrGroup(node.Id, endNodeRef.Id);
              }

              clearStoppedVisitors();
              if(needPreorderStop)
                return;

            }
        }

        public override void visit(Columbus.Csharp.Asg.Nodes.Structure.QueryBodySyntax node, bool callFirst = true){
          if (safeMode || visitCrossEdgeTree) {
            if (safeMode) {
              if (visitedNodes[(int)node.Id]) { // for safemode
                return;
              }
            }
            visitedNodes[(int)node.Id] = true;
          }

          foreach (var visitor in visitorList) {
            visitor.visit(node);
            incVisitorDepth(visitor);
          }

          clearStoppedVisitors();
          if(needPreorderStop)
            return;

          visitAllEdges(node, true);

          foreach (var visitor in visitorList) {
            decVisitorDepth(visitor);
            visitor.visitEnd(node);
          }

          clearStoppedVisitors();
        }

        /// <summary>
        /// It call the traversal for the edges
        /// </summary>
        /// <param name="node">[in] The node with own type</param>
        /// <param name="callVirtualBase">[in] This paramater is don't used just api copatibility used.</param>
        public void visitAllEdges(Columbus.Csharp.Asg.Nodes.Structure.QueryClauseSyntax node, bool callFirst = true){
            visitAllEdges((Columbus.Csharp.Asg.Nodes.Base.Positioned)(node),false);
        }

        /// <summary>
        /// It call the traversal for the edges
        /// </summary>
        /// <param name="node">[in] The node with own type</param>
        /// <param name="callVirtualBase">[in] This paramater is don't used just api copatibility used.</param>
        public void visitAllEdges(Columbus.Csharp.Asg.Nodes.Structure.QueryContinuationSyntax node, bool callFirst = true){
            visitAllEdges((Columbus.Csharp.Asg.Nodes.Base.Positioned)(node),false);


            Columbus.Csharp.Asg.Nodes.Base.Base genNodePtr;
            // edge: Body
            genNodePtr = fact.getRef(node.getBody()) ;
            if (genNodePtr != null) {
              Columbus.Csharp.Asg.Nodes.Structure.QueryBodySyntax endNodeRef = (Columbus.Csharp.Asg.Nodes.Structure.QueryBodySyntax)(genNodePtr);
              foreach (var visitor in visitorList) {
                visitor.visitQueryContinuationSyntax_Body(node.Id, endNodeRef.Id);
              }

              clearStoppedVisitors();
              if(needPreorderStop)
                return;

              if ((!fact.IsFilterTurnedOn && !visitFilteredEdge) || (fact.getFilterState(endNodeRef.Id) == Filter.FilterState.NotFiltered) || (!originalFilterState && visitFilteredEdge)) {
                  endNodeRef.accept(this);
              }
              foreach (var visitor in visitorList) {
                visitor.visitEndQueryContinuationSyntax_Body(node.Id, endNodeRef.Id);
              }

              clearStoppedVisitors();
              if(needPreorderStop)
                return;

            }
        }

        public override void visit(Columbus.Csharp.Asg.Nodes.Structure.QueryContinuationSyntax node, bool callFirst = true){
          if (safeMode || visitCrossEdgeTree) {
            if (safeMode) {
              if (visitedNodes[(int)node.Id]) { // for safemode
                return;
              }
            }
            visitedNodes[(int)node.Id] = true;
          }

          foreach (var visitor in visitorList) {
            visitor.visit(node);
            incVisitorDepth(visitor);
          }

          clearStoppedVisitors();
          if(needPreorderStop)
            return;

          visitAllEdges(node, true);

          foreach (var visitor in visitorList) {
            decVisitorDepth(visitor);
            visitor.visitEnd(node);
          }

          clearStoppedVisitors();
        }

        /// <summary>
        /// It call the traversal for the edges
        /// </summary>
        /// <param name="node">[in] The node with own type</param>
        /// <param name="callVirtualBase">[in] This paramater is don't used just api copatibility used.</param>
        public void visitAllEdges(Columbus.Csharp.Asg.Nodes.Structure.RecursivePatternSyntax node, bool callFirst = true){
            visitAllEdges((Columbus.Csharp.Asg.Nodes.Structure.PatternSyntax)(node),false);


            Columbus.Csharp.Asg.Nodes.Base.Base genNodePtr;
            // edge: Designation
            genNodePtr = fact.getRef(node.getDesignation()) ;
            if (genNodePtr != null) {
              Columbus.Csharp.Asg.Nodes.Structure.VariableDesignationSyntax endNodeRef = (Columbus.Csharp.Asg.Nodes.Structure.VariableDesignationSyntax)(genNodePtr);
              foreach (var visitor in visitorList) {
                visitor.visitRecursivePatternSyntax_Designation(node.Id, endNodeRef.Id);
              }

              clearStoppedVisitors();
              if(needPreorderStop)
                return;

              if ((!fact.IsFilterTurnedOn && !visitFilteredEdge) || (fact.getFilterState(endNodeRef.Id) == Filter.FilterState.NotFiltered) || (!originalFilterState && visitFilteredEdge)) {
                  endNodeRef.accept(this);
              }
              foreach (var visitor in visitorList) {
                visitor.visitEndRecursivePatternSyntax_Designation(node.Id, endNodeRef.Id);
              }

              clearStoppedVisitors();
              if(needPreorderStop)
                return;

            }

            // edge: PositionalPatternClause
            genNodePtr = fact.getRef(node.getPositionalPatternClause()) ;
            if (genNodePtr != null) {
              Columbus.Csharp.Asg.Nodes.Structure.PositionalPatternClauseSyntax endNodeRef = (Columbus.Csharp.Asg.Nodes.Structure.PositionalPatternClauseSyntax)(genNodePtr);
              foreach (var visitor in visitorList) {
                visitor.visitRecursivePatternSyntax_PositionalPatternClause(node.Id, endNodeRef.Id);
              }

              clearStoppedVisitors();
              if(needPreorderStop)
                return;

              if ((!fact.IsFilterTurnedOn && !visitFilteredEdge) || (fact.getFilterState(endNodeRef.Id) == Filter.FilterState.NotFiltered) || (!originalFilterState && visitFilteredEdge)) {
                  endNodeRef.accept(this);
              }
              foreach (var visitor in visitorList) {
                visitor.visitEndRecursivePatternSyntax_PositionalPatternClause(node.Id, endNodeRef.Id);
              }

              clearStoppedVisitors();
              if(needPreorderStop)
                return;

            }

            // edge: PropertyPatternClause
            genNodePtr = fact.getRef(node.getPropertyPatternClause()) ;
            if (genNodePtr != null) {
              Columbus.Csharp.Asg.Nodes.Structure.PropertyPatternClauseSyntax endNodeRef = (Columbus.Csharp.Asg.Nodes.Structure.PropertyPatternClauseSyntax)(genNodePtr);
              foreach (var visitor in visitorList) {
                visitor.visitRecursivePatternSyntax_PropertyPatternClause(node.Id, endNodeRef.Id);
              }

              clearStoppedVisitors();
              if(needPreorderStop)
                return;

              if ((!fact.IsFilterTurnedOn && !visitFilteredEdge) || (fact.getFilterState(endNodeRef.Id) == Filter.FilterState.NotFiltered) || (!originalFilterState && visitFilteredEdge)) {
                  endNodeRef.accept(this);
              }
              foreach (var visitor in visitorList) {
                visitor.visitEndRecursivePatternSyntax_PropertyPatternClause(node.Id, endNodeRef.Id);
              }

              clearStoppedVisitors();
              if(needPreorderStop)
                return;

            }

            // edge: Type
            genNodePtr = fact.getRef(node.getType()) ;
            if (genNodePtr != null) {
              Columbus.Csharp.Asg.Nodes.Expression.TypeSyntax endNodeRef = (Columbus.Csharp.Asg.Nodes.Expression.TypeSyntax)(genNodePtr);
              foreach (var visitor in visitorList) {
                visitor.visitRecursivePatternSyntax_Type(node.Id, endNodeRef.Id);
              }

              clearStoppedVisitors();
              if(needPreorderStop)
                return;

              if ((!fact.IsFilterTurnedOn && !visitFilteredEdge) || (fact.getFilterState(endNodeRef.Id) == Filter.FilterState.NotFiltered) || (!originalFilterState && visitFilteredEdge)) {
                  endNodeRef.accept(this);
              }
              foreach (var visitor in visitorList) {
                visitor.visitEndRecursivePatternSyntax_Type(node.Id, endNodeRef.Id);
              }

              clearStoppedVisitors();
              if(needPreorderStop)
                return;

            }
        }

        public override void visit(Columbus.Csharp.Asg.Nodes.Structure.RecursivePatternSyntax node, bool callFirst = true){
          if (safeMode || visitCrossEdgeTree) {
            if (safeMode) {
              if (visitedNodes[(int)node.Id]) { // for safemode
                return;
              }
            }
            visitedNodes[(int)node.Id] = true;
          }

          foreach (var visitor in visitorList) {
            visitor.visit(node);
            incVisitorDepth(visitor);
          }

          clearStoppedVisitors();
          if(needPreorderStop)
            return;

          visitAllEdges(node, true);

          foreach (var visitor in visitorList) {
            decVisitorDepth(visitor);
            visitor.visitEnd(node);
          }

          clearStoppedVisitors();
        }

        /// <summary>
        /// It call the traversal for the edges
        /// </summary>
        /// <param name="node">[in] The node with own type</param>
        /// <param name="callVirtualBase">[in] This paramater is don't used just api copatibility used.</param>
        public void visitAllEdges(Columbus.Csharp.Asg.Nodes.Structure.SelectClauseSyntax node, bool callFirst = true){
            visitAllEdges((Columbus.Csharp.Asg.Nodes.Structure.SelectOrGroupClauseSyntax)(node),false);


            Columbus.Csharp.Asg.Nodes.Base.Base genNodePtr;
            // edge: Expression
            genNodePtr = fact.getRef(node.getExpression()) ;
            if (genNodePtr != null) {
              Columbus.Csharp.Asg.Nodes.Expression.ExpressionSyntax endNodeRef = (Columbus.Csharp.Asg.Nodes.Expression.ExpressionSyntax)(genNodePtr);
              foreach (var visitor in visitorList) {
                visitor.visitSelectClauseSyntax_Expression(node.Id, endNodeRef.Id);
              }

              clearStoppedVisitors();
              if(needPreorderStop)
                return;

              if ((!fact.IsFilterTurnedOn && !visitFilteredEdge) || (fact.getFilterState(endNodeRef.Id) == Filter.FilterState.NotFiltered) || (!originalFilterState && visitFilteredEdge)) {
                  endNodeRef.accept(this);
              }
              foreach (var visitor in visitorList) {
                visitor.visitEndSelectClauseSyntax_Expression(node.Id, endNodeRef.Id);
              }

              clearStoppedVisitors();
              if(needPreorderStop)
                return;

            }
        }

        public override void visit(Columbus.Csharp.Asg.Nodes.Structure.SelectClauseSyntax node, bool callFirst = true){
          if (safeMode || visitCrossEdgeTree) {
            if (safeMode) {
              if (visitedNodes[(int)node.Id]) { // for safemode
                return;
              }
            }
            visitedNodes[(int)node.Id] = true;
          }

          foreach (var visitor in visitorList) {
            visitor.visit(node);
            incVisitorDepth(visitor);
          }

          clearStoppedVisitors();
          if(needPreorderStop)
            return;

          visitAllEdges(node, true);

          foreach (var visitor in visitorList) {
            decVisitorDepth(visitor);
            visitor.visitEnd(node);
          }

          clearStoppedVisitors();
        }

        /// <summary>
        /// It call the traversal for the edges
        /// </summary>
        /// <param name="node">[in] The node with own type</param>
        /// <param name="callVirtualBase">[in] This paramater is don't used just api copatibility used.</param>
        public void visitAllEdges(Columbus.Csharp.Asg.Nodes.Structure.SelectOrGroupClauseSyntax node, bool callFirst = true){
            visitAllEdges((Columbus.Csharp.Asg.Nodes.Base.Positioned)(node),false);
        }

        /// <summary>
        /// It call the traversal for the edges
        /// </summary>
        /// <param name="node">[in] The node with own type</param>
        /// <param name="callVirtualBase">[in] This paramater is don't used just api copatibility used.</param>
        public void visitAllEdges(Columbus.Csharp.Asg.Nodes.Structure.SimpleBaseTypeSyntax node, bool callFirst = true){
            visitAllEdges((Columbus.Csharp.Asg.Nodes.Structure.BaseTypeSyntax)(node),false);
        }

        public override void visit(Columbus.Csharp.Asg.Nodes.Structure.SimpleBaseTypeSyntax node, bool callFirst = true){
          if (safeMode || visitCrossEdgeTree) {
            if (safeMode) {
              if (visitedNodes[(int)node.Id]) { // for safemode
                return;
              }
            }
            visitedNodes[(int)node.Id] = true;
          }

          foreach (var visitor in visitorList) {
            visitor.visit(node);
            incVisitorDepth(visitor);
          }

          clearStoppedVisitors();
          if(needPreorderStop)
            return;

          visitAllEdges(node, true);

          foreach (var visitor in visitorList) {
            decVisitorDepth(visitor);
            visitor.visitEnd(node);
          }

          clearStoppedVisitors();
        }

        /// <summary>
        /// It call the traversal for the edges
        /// </summary>
        /// <param name="node">[in] The node with own type</param>
        /// <param name="callVirtualBase">[in] This paramater is don't used just api copatibility used.</param>
        public void visitAllEdges(Columbus.Csharp.Asg.Nodes.Structure.SingleVariableDesignationSyntax node, bool callFirst = true){
            visitAllEdges((Columbus.Csharp.Asg.Nodes.Structure.VariableDesignationSyntax)(node),false);
        }

        public override void visit(Columbus.Csharp.Asg.Nodes.Structure.SingleVariableDesignationSyntax node, bool callFirst = true){
          if (safeMode || visitCrossEdgeTree) {
            if (safeMode) {
              if (visitedNodes[(int)node.Id]) { // for safemode
                return;
              }
            }
            visitedNodes[(int)node.Id] = true;
          }

          foreach (var visitor in visitorList) {
            visitor.visit(node);
            incVisitorDepth(visitor);
          }

          clearStoppedVisitors();
          if(needPreorderStop)
            return;

          visitAllEdges(node, true);

          foreach (var visitor in visitorList) {
            decVisitorDepth(visitor);
            visitor.visitEnd(node);
          }

          clearStoppedVisitors();
        }

        /// <summary>
        /// It call the traversal for the edges
        /// </summary>
        /// <param name="node">[in] The node with own type</param>
        /// <param name="callVirtualBase">[in] This paramater is don't used just api copatibility used.</param>
        public void visitAllEdges(Columbus.Csharp.Asg.Nodes.Structure.StructDeclarationSyntax node, bool callFirst = true){
            visitAllEdges((Columbus.Csharp.Asg.Nodes.Structure.TypeDeclarationSyntax)(node),false);
        }

        public override void visit(Columbus.Csharp.Asg.Nodes.Structure.StructDeclarationSyntax node, bool callFirst = true){
          if (safeMode || visitCrossEdgeTree) {
            if (safeMode) {
              if (visitedNodes[(int)node.Id]) { // for safemode
                return;
              }
            }
            visitedNodes[(int)node.Id] = true;
          }

          foreach (var visitor in visitorList) {
            visitor.visit(node);
            incVisitorDepth(visitor);
          }

          clearStoppedVisitors();
          if(needPreorderStop)
            return;

          visitAllEdges(node, true);

          foreach (var visitor in visitorList) {
            decVisitorDepth(visitor);
            visitor.visitEnd(node);
          }

          clearStoppedVisitors();
        }

        /// <summary>
        /// It call the traversal for the edges
        /// </summary>
        /// <param name="node">[in] The node with own type</param>
        /// <param name="callVirtualBase">[in] This paramater is don't used just api copatibility used.</param>
        public void visitAllEdges(Columbus.Csharp.Asg.Nodes.Structure.SubpatternSyntax node, bool callFirst = true){
            visitAllEdges((Columbus.Csharp.Asg.Nodes.Base.Positioned)(node),false);


            Columbus.Csharp.Asg.Nodes.Base.Base genNodePtr;
            // edge: Pattern
            genNodePtr = fact.getRef(node.getPattern()) ;
            if (genNodePtr != null) {
              Columbus.Csharp.Asg.Nodes.Structure.PatternSyntax endNodeRef = (Columbus.Csharp.Asg.Nodes.Structure.PatternSyntax)(genNodePtr);
              foreach (var visitor in visitorList) {
                visitor.visitSubpatternSyntax_Pattern(node.Id, endNodeRef.Id);
              }

              clearStoppedVisitors();
              if(needPreorderStop)
                return;

              if ((!fact.IsFilterTurnedOn && !visitFilteredEdge) || (fact.getFilterState(endNodeRef.Id) == Filter.FilterState.NotFiltered) || (!originalFilterState && visitFilteredEdge)) {
                  endNodeRef.accept(this);
              }
              foreach (var visitor in visitorList) {
                visitor.visitEndSubpatternSyntax_Pattern(node.Id, endNodeRef.Id);
              }

              clearStoppedVisitors();
              if(needPreorderStop)
                return;

            }
        }

        public override void visit(Columbus.Csharp.Asg.Nodes.Structure.SubpatternSyntax node, bool callFirst = true){
          if (safeMode || visitCrossEdgeTree) {
            if (safeMode) {
              if (visitedNodes[(int)node.Id]) { // for safemode
                return;
              }
            }
            visitedNodes[(int)node.Id] = true;
          }

          foreach (var visitor in visitorList) {
            visitor.visit(node);
            incVisitorDepth(visitor);
          }

          clearStoppedVisitors();
          if(needPreorderStop)
            return;

          visitAllEdges(node, true);

          foreach (var visitor in visitorList) {
            decVisitorDepth(visitor);
            visitor.visitEnd(node);
          }

          clearStoppedVisitors();
        }

        /// <summary>
        /// It call the traversal for the edges
        /// </summary>
        /// <param name="node">[in] The node with own type</param>
        /// <param name="callVirtualBase">[in] This paramater is don't used just api copatibility used.</param>
        public void visitAllEdges(Columbus.Csharp.Asg.Nodes.Structure.SwitchExpressionArmSyntax node, bool callFirst = true){
            visitAllEdges((Columbus.Csharp.Asg.Nodes.Base.Positioned)(node),false);


            Columbus.Csharp.Asg.Nodes.Base.Base genNodePtr;
            // edge: Expression
            genNodePtr = fact.getRef(node.getExpression()) ;
            if (genNodePtr != null) {
              Columbus.Csharp.Asg.Nodes.Expression.ExpressionSyntax endNodeRef = (Columbus.Csharp.Asg.Nodes.Expression.ExpressionSyntax)(genNodePtr);
              foreach (var visitor in visitorList) {
                visitor.visitSwitchExpressionArmSyntax_Expression(node.Id, endNodeRef.Id);
              }

              clearStoppedVisitors();
              if(needPreorderStop)
                return;

              if ((!fact.IsFilterTurnedOn && !visitFilteredEdge) || (fact.getFilterState(endNodeRef.Id) == Filter.FilterState.NotFiltered) || (!originalFilterState && visitFilteredEdge)) {
                  endNodeRef.accept(this);
              }
              foreach (var visitor in visitorList) {
                visitor.visitEndSwitchExpressionArmSyntax_Expression(node.Id, endNodeRef.Id);
              }

              clearStoppedVisitors();
              if(needPreorderStop)
                return;

            }

            // edge: Pattern
            genNodePtr = fact.getRef(node.getPattern()) ;
            if (genNodePtr != null) {
              Columbus.Csharp.Asg.Nodes.Structure.PatternSyntax endNodeRef = (Columbus.Csharp.Asg.Nodes.Structure.PatternSyntax)(genNodePtr);
              foreach (var visitor in visitorList) {
                visitor.visitSwitchExpressionArmSyntax_Pattern(node.Id, endNodeRef.Id);
              }

              clearStoppedVisitors();
              if(needPreorderStop)
                return;

              if ((!fact.IsFilterTurnedOn && !visitFilteredEdge) || (fact.getFilterState(endNodeRef.Id) == Filter.FilterState.NotFiltered) || (!originalFilterState && visitFilteredEdge)) {
                  endNodeRef.accept(this);
              }
              foreach (var visitor in visitorList) {
                visitor.visitEndSwitchExpressionArmSyntax_Pattern(node.Id, endNodeRef.Id);
              }

              clearStoppedVisitors();
              if(needPreorderStop)
                return;

            }

            // edge: WhenClause
            genNodePtr = fact.getRef(node.getWhenClause()) ;
            if (genNodePtr != null) {
              Columbus.Csharp.Asg.Nodes.Structure.WhenClauseSyntax endNodeRef = (Columbus.Csharp.Asg.Nodes.Structure.WhenClauseSyntax)(genNodePtr);
              foreach (var visitor in visitorList) {
                visitor.visitSwitchExpressionArmSyntax_WhenClause(node.Id, endNodeRef.Id);
              }

              clearStoppedVisitors();
              if(needPreorderStop)
                return;

              if ((!fact.IsFilterTurnedOn && !visitFilteredEdge) || (fact.getFilterState(endNodeRef.Id) == Filter.FilterState.NotFiltered) || (!originalFilterState && visitFilteredEdge)) {
                  endNodeRef.accept(this);
              }
              foreach (var visitor in visitorList) {
                visitor.visitEndSwitchExpressionArmSyntax_WhenClause(node.Id, endNodeRef.Id);
              }

              clearStoppedVisitors();
              if(needPreorderStop)
                return;

            }
        }

        public override void visit(Columbus.Csharp.Asg.Nodes.Structure.SwitchExpressionArmSyntax node, bool callFirst = true){
          if (safeMode || visitCrossEdgeTree) {
            if (safeMode) {
              if (visitedNodes[(int)node.Id]) { // for safemode
                return;
              }
            }
            visitedNodes[(int)node.Id] = true;
          }

          foreach (var visitor in visitorList) {
            visitor.visit(node);
            incVisitorDepth(visitor);
          }

          clearStoppedVisitors();
          if(needPreorderStop)
            return;

          visitAllEdges(node, true);

          foreach (var visitor in visitorList) {
            decVisitorDepth(visitor);
            visitor.visitEnd(node);
          }

          clearStoppedVisitors();
        }

        /// <summary>
        /// It call the traversal for the edges
        /// </summary>
        /// <param name="node">[in] The node with own type</param>
        /// <param name="callVirtualBase">[in] This paramater is don't used just api copatibility used.</param>
        public void visitAllEdges(Columbus.Csharp.Asg.Nodes.Structure.SwitchLabelSyntax node, bool callFirst = true){
            visitAllEdges((Columbus.Csharp.Asg.Nodes.Base.Positioned)(node),false);
        }

        /// <summary>
        /// It call the traversal for the edges
        /// </summary>
        /// <param name="node">[in] The node with own type</param>
        /// <param name="callVirtualBase">[in] This paramater is don't used just api copatibility used.</param>
        public void visitAllEdges(Columbus.Csharp.Asg.Nodes.Structure.SwitchSectionSyntax node, bool callFirst = true){
            visitAllEdges((Columbus.Csharp.Asg.Nodes.Base.Positioned)(node),false);


            // edge: Labels
            ListIterator<Columbus.Csharp.Asg.Nodes.Structure.SwitchLabelSyntax> iteratorForLabels = node.LabelsListIteratorBegin;
            while (iteratorForLabels.getValue() != null) {
               Columbus.Csharp.Asg.Nodes.Structure.SwitchLabelSyntax endNodeRef = (Columbus.Csharp.Asg.Nodes.Structure.SwitchLabelSyntax)iteratorForLabels.getValue();
              foreach (var visitor in visitorList) {
                visitor.visitSwitchSectionSyntax_Labels(node.Id, endNodeRef.Id);
              }

              clearStoppedVisitors();
              if(needPreorderStop)
                return;

              if ((!fact.IsFilterTurnedOn && !visitFilteredEdge) || (fact.getFilterState(endNodeRef.Id) == Filter.FilterState.NotFiltered) || (!originalFilterState && visitFilteredEdge)) {
                  endNodeRef.accept(this);
              }
              foreach (var visitor in visitorList) {
                visitor.visitEndSwitchSectionSyntax_Labels(node.Id, endNodeRef.Id);
              }

              clearStoppedVisitors();
              if(needPreorderStop)
                return;

            iteratorForLabels = iteratorForLabels.getNext();
            }

            // edge: Statements
            ListIterator<Columbus.Csharp.Asg.Nodes.Statement.StatementSyntax> iteratorForStatements = node.StatementsListIteratorBegin;
            while (iteratorForStatements.getValue() != null) {
               Columbus.Csharp.Asg.Nodes.Statement.StatementSyntax endNodeRef = (Columbus.Csharp.Asg.Nodes.Statement.StatementSyntax)iteratorForStatements.getValue();
              foreach (var visitor in visitorList) {
                visitor.visitSwitchSectionSyntax_Statements(node.Id, endNodeRef.Id);
              }

              clearStoppedVisitors();
              if(needPreorderStop)
                return;

              if ((!fact.IsFilterTurnedOn && !visitFilteredEdge) || (fact.getFilterState(endNodeRef.Id) == Filter.FilterState.NotFiltered) || (!originalFilterState && visitFilteredEdge)) {
                  endNodeRef.accept(this);
              }
              foreach (var visitor in visitorList) {
                visitor.visitEndSwitchSectionSyntax_Statements(node.Id, endNodeRef.Id);
              }

              clearStoppedVisitors();
              if(needPreorderStop)
                return;

            iteratorForStatements = iteratorForStatements.getNext();
            }
        }

        public override void visit(Columbus.Csharp.Asg.Nodes.Structure.SwitchSectionSyntax node, bool callFirst = true){
          if (safeMode || visitCrossEdgeTree) {
            if (safeMode) {
              if (visitedNodes[(int)node.Id]) { // for safemode
                return;
              }
            }
            visitedNodes[(int)node.Id] = true;
          }

          foreach (var visitor in visitorList) {
            visitor.visit(node);
            incVisitorDepth(visitor);
          }

          clearStoppedVisitors();
          if(needPreorderStop)
            return;

          visitAllEdges(node, true);

          foreach (var visitor in visitorList) {
            decVisitorDepth(visitor);
            visitor.visitEnd(node);
          }

          clearStoppedVisitors();
        }

        /// <summary>
        /// It call the traversal for the edges
        /// </summary>
        /// <param name="node">[in] The node with own type</param>
        /// <param name="callVirtualBase">[in] This paramater is don't used just api copatibility used.</param>
        public void visitAllEdges(Columbus.Csharp.Asg.Nodes.Structure.SyntaxToken node, bool callFirst = true){
            visitAllEdges((Columbus.Csharp.Asg.Nodes.Base.Positioned)(node),false);
        }

        public override void visit(Columbus.Csharp.Asg.Nodes.Structure.SyntaxToken node, bool callFirst = true){
          if (safeMode || visitCrossEdgeTree) {
            if (safeMode) {
              if (visitedNodes[(int)node.Id]) { // for safemode
                return;
              }
            }
            visitedNodes[(int)node.Id] = true;
          }

          foreach (var visitor in visitorList) {
            visitor.visit(node);
            incVisitorDepth(visitor);
          }

          clearStoppedVisitors();
          if(needPreorderStop)
            return;

          visitAllEdges(node, true);

          foreach (var visitor in visitorList) {
            decVisitorDepth(visitor);
            visitor.visitEnd(node);
          }

          clearStoppedVisitors();
        }

        /// <summary>
        /// It call the traversal for the edges
        /// </summary>
        /// <param name="node">[in] The node with own type</param>
        /// <param name="callVirtualBase">[in] This paramater is don't used just api copatibility used.</param>
        public void visitAllEdges(Columbus.Csharp.Asg.Nodes.Structure.TupleElementSyntax node, bool callFirst = true){
            visitAllEdges((Columbus.Csharp.Asg.Nodes.Base.Positioned)(node),false);


            Columbus.Csharp.Asg.Nodes.Base.Base genNodePtr;
            // edge: Type
            genNodePtr = fact.getRef(node.getType()) ;
            if (genNodePtr != null) {
              Columbus.Csharp.Asg.Nodes.Expression.TypeSyntax endNodeRef = (Columbus.Csharp.Asg.Nodes.Expression.TypeSyntax)(genNodePtr);
              foreach (var visitor in visitorList) {
                visitor.visitTupleElementSyntax_Type(node.Id, endNodeRef.Id);
              }

              clearStoppedVisitors();
              if(needPreorderStop)
                return;

              if ((!fact.IsFilterTurnedOn && !visitFilteredEdge) || (fact.getFilterState(endNodeRef.Id) == Filter.FilterState.NotFiltered) || (!originalFilterState && visitFilteredEdge)) {
                  endNodeRef.accept(this);
              }
              foreach (var visitor in visitorList) {
                visitor.visitEndTupleElementSyntax_Type(node.Id, endNodeRef.Id);
              }

              clearStoppedVisitors();
              if(needPreorderStop)
                return;

            }
        }

        public override void visit(Columbus.Csharp.Asg.Nodes.Structure.TupleElementSyntax node, bool callFirst = true){
          if (safeMode || visitCrossEdgeTree) {
            if (safeMode) {
              if (visitedNodes[(int)node.Id]) { // for safemode
                return;
              }
            }
            visitedNodes[(int)node.Id] = true;
          }

          foreach (var visitor in visitorList) {
            visitor.visit(node);
            incVisitorDepth(visitor);
          }

          clearStoppedVisitors();
          if(needPreorderStop)
            return;

          visitAllEdges(node, true);

          foreach (var visitor in visitorList) {
            decVisitorDepth(visitor);
            visitor.visitEnd(node);
          }

          clearStoppedVisitors();
        }

        /// <summary>
        /// It call the traversal for the edges
        /// </summary>
        /// <param name="node">[in] The node with own type</param>
        /// <param name="callVirtualBase">[in] This paramater is don't used just api copatibility used.</param>
        public void visitAllEdges(Columbus.Csharp.Asg.Nodes.Structure.TypeArgumentListSyntax node, bool callFirst = true){
            visitAllEdges((Columbus.Csharp.Asg.Nodes.Base.Positioned)(node),false);


            // edge: Arguments
            ListIterator<Columbus.Csharp.Asg.Nodes.Expression.TypeSyntax> iteratorForArguments = node.ArgumentsListIteratorBegin;
            while (iteratorForArguments.getValue() != null) {
               Columbus.Csharp.Asg.Nodes.Expression.TypeSyntax endNodeRef = (Columbus.Csharp.Asg.Nodes.Expression.TypeSyntax)iteratorForArguments.getValue();
              foreach (var visitor in visitorList) {
                visitor.visitTypeArgumentListSyntax_Arguments(node.Id, endNodeRef.Id);
              }

              clearStoppedVisitors();
              if(needPreorderStop)
                return;

              if ((!fact.IsFilterTurnedOn && !visitFilteredEdge) || (fact.getFilterState(endNodeRef.Id) == Filter.FilterState.NotFiltered) || (!originalFilterState && visitFilteredEdge)) {
                  endNodeRef.accept(this);
              }
              foreach (var visitor in visitorList) {
                visitor.visitEndTypeArgumentListSyntax_Arguments(node.Id, endNodeRef.Id);
              }

              clearStoppedVisitors();
              if(needPreorderStop)
                return;

            iteratorForArguments = iteratorForArguments.getNext();
            }
        }

        public override void visit(Columbus.Csharp.Asg.Nodes.Structure.TypeArgumentListSyntax node, bool callFirst = true){
          if (safeMode || visitCrossEdgeTree) {
            if (safeMode) {
              if (visitedNodes[(int)node.Id]) { // for safemode
                return;
              }
            }
            visitedNodes[(int)node.Id] = true;
          }

          foreach (var visitor in visitorList) {
            visitor.visit(node);
            incVisitorDepth(visitor);
          }

          clearStoppedVisitors();
          if(needPreorderStop)
            return;

          visitAllEdges(node, true);

          foreach (var visitor in visitorList) {
            decVisitorDepth(visitor);
            visitor.visitEnd(node);
          }

          clearStoppedVisitors();
        }

        /// <summary>
        /// It call the traversal for the edges
        /// </summary>
        /// <param name="node">[in] The node with own type</param>
        /// <param name="callVirtualBase">[in] This paramater is don't used just api copatibility used.</param>
        public void visitAllEdges(Columbus.Csharp.Asg.Nodes.Structure.TypeConstraintSyntax node, bool callFirst = true){
            visitAllEdges((Columbus.Csharp.Asg.Nodes.Structure.TypeParameterConstraintSyntax)(node),false);


            Columbus.Csharp.Asg.Nodes.Base.Base genNodePtr;
            // edge: Type
            genNodePtr = fact.getRef(node.getType()) ;
            if (genNodePtr != null) {
              Columbus.Csharp.Asg.Nodes.Expression.TypeSyntax endNodeRef = (Columbus.Csharp.Asg.Nodes.Expression.TypeSyntax)(genNodePtr);
              foreach (var visitor in visitorList) {
                visitor.visitTypeConstraintSyntax_Type(node.Id, endNodeRef.Id);
              }

              clearStoppedVisitors();
              if(needPreorderStop)
                return;

              if ((!fact.IsFilterTurnedOn && !visitFilteredEdge) || (fact.getFilterState(endNodeRef.Id) == Filter.FilterState.NotFiltered) || (!originalFilterState && visitFilteredEdge)) {
                  endNodeRef.accept(this);
              }
              foreach (var visitor in visitorList) {
                visitor.visitEndTypeConstraintSyntax_Type(node.Id, endNodeRef.Id);
              }

              clearStoppedVisitors();
              if(needPreorderStop)
                return;

            }
        }

        public override void visit(Columbus.Csharp.Asg.Nodes.Structure.TypeConstraintSyntax node, bool callFirst = true){
          if (safeMode || visitCrossEdgeTree) {
            if (safeMode) {
              if (visitedNodes[(int)node.Id]) { // for safemode
                return;
              }
            }
            visitedNodes[(int)node.Id] = true;
          }

          foreach (var visitor in visitorList) {
            visitor.visit(node);
            incVisitorDepth(visitor);
          }

          clearStoppedVisitors();
          if(needPreorderStop)
            return;

          visitAllEdges(node, true);

          foreach (var visitor in visitorList) {
            decVisitorDepth(visitor);
            visitor.visitEnd(node);
          }

          clearStoppedVisitors();
        }

        /// <summary>
        /// It call the traversal for the edges
        /// </summary>
        /// <param name="node">[in] The node with own type</param>
        /// <param name="callVirtualBase">[in] This paramater is don't used just api copatibility used.</param>
        public void visitAllEdges(Columbus.Csharp.Asg.Nodes.Structure.TypeCrefSyntax node, bool callFirst = true){
            visitAllEdges((Columbus.Csharp.Asg.Nodes.Structure.CrefSyntax)(node),false);


            Columbus.Csharp.Asg.Nodes.Base.Base genNodePtr;
            // edge: Type
            genNodePtr = fact.getRef(node.getType()) ;
            if (genNodePtr != null) {
              Columbus.Csharp.Asg.Nodes.Expression.TypeSyntax endNodeRef = (Columbus.Csharp.Asg.Nodes.Expression.TypeSyntax)(genNodePtr);
              foreach (var visitor in visitorList) {
                visitor.visitTypeCrefSyntax_Type(node.Id, endNodeRef.Id);
              }

              clearStoppedVisitors();
              if(needPreorderStop)
                return;

              if ((!fact.IsFilterTurnedOn && !visitFilteredEdge) || (fact.getFilterState(endNodeRef.Id) == Filter.FilterState.NotFiltered) || (!originalFilterState && visitFilteredEdge)) {
                  endNodeRef.accept(this);
              }
              foreach (var visitor in visitorList) {
                visitor.visitEndTypeCrefSyntax_Type(node.Id, endNodeRef.Id);
              }

              clearStoppedVisitors();
              if(needPreorderStop)
                return;

            }
        }

        public override void visit(Columbus.Csharp.Asg.Nodes.Structure.TypeCrefSyntax node, bool callFirst = true){
          if (safeMode || visitCrossEdgeTree) {
            if (safeMode) {
              if (visitedNodes[(int)node.Id]) { // for safemode
                return;
              }
            }
            visitedNodes[(int)node.Id] = true;
          }

          foreach (var visitor in visitorList) {
            visitor.visit(node);
            incVisitorDepth(visitor);
          }

          clearStoppedVisitors();
          if(needPreorderStop)
            return;

          visitAllEdges(node, true);

          foreach (var visitor in visitorList) {
            decVisitorDepth(visitor);
            visitor.visitEnd(node);
          }

          clearStoppedVisitors();
        }

        /// <summary>
        /// It call the traversal for the edges
        /// </summary>
        /// <param name="node">[in] The node with own type</param>
        /// <param name="callVirtualBase">[in] This paramater is don't used just api copatibility used.</param>
        public void visitAllEdges(Columbus.Csharp.Asg.Nodes.Structure.TypeDeclarationSyntax node, bool callFirst = true){
            visitAllEdges((Columbus.Csharp.Asg.Nodes.Structure.BaseTypeDeclarationSyntax)(node),false);


            // edge: ConstraintClauses
            ListIterator<Columbus.Csharp.Asg.Nodes.Structure.TypeParameterConstraintClauseSyntax> iteratorForConstraintClauses = node.ConstraintClausesListIteratorBegin;
            while (iteratorForConstraintClauses.getValue() != null) {
               Columbus.Csharp.Asg.Nodes.Structure.TypeParameterConstraintClauseSyntax endNodeRef = (Columbus.Csharp.Asg.Nodes.Structure.TypeParameterConstraintClauseSyntax)iteratorForConstraintClauses.getValue();
              foreach (var visitor in visitorList) {
                visitor.visitTypeDeclarationSyntax_ConstraintClauses(node.Id, endNodeRef.Id);
              }

              clearStoppedVisitors();
              if(needPreorderStop)
                return;

              if ((!fact.IsFilterTurnedOn && !visitFilteredEdge) || (fact.getFilterState(endNodeRef.Id) == Filter.FilterState.NotFiltered) || (!originalFilterState && visitFilteredEdge)) {
                  endNodeRef.accept(this);
              }
              foreach (var visitor in visitorList) {
                visitor.visitEndTypeDeclarationSyntax_ConstraintClauses(node.Id, endNodeRef.Id);
              }

              clearStoppedVisitors();
              if(needPreorderStop)
                return;

            iteratorForConstraintClauses = iteratorForConstraintClauses.getNext();
            }

            // edge: Members
            ListIterator<Columbus.Csharp.Asg.Nodes.Structure.MemberDeclarationSyntax> iteratorForMembers = node.MembersListIteratorBegin;
            while (iteratorForMembers.getValue() != null) {
               Columbus.Csharp.Asg.Nodes.Structure.MemberDeclarationSyntax endNodeRef = (Columbus.Csharp.Asg.Nodes.Structure.MemberDeclarationSyntax)iteratorForMembers.getValue();
              foreach (var visitor in visitorList) {
                visitor.visitTypeDeclarationSyntax_Members(node.Id, endNodeRef.Id);
              }

              clearStoppedVisitors();
              if(needPreorderStop)
                return;

              if ((!fact.IsFilterTurnedOn && !visitFilteredEdge) || (fact.getFilterState(endNodeRef.Id) == Filter.FilterState.NotFiltered) || (!originalFilterState && visitFilteredEdge)) {
                  endNodeRef.accept(this);
              }
              foreach (var visitor in visitorList) {
                visitor.visitEndTypeDeclarationSyntax_Members(node.Id, endNodeRef.Id);
              }

              clearStoppedVisitors();
              if(needPreorderStop)
                return;

            iteratorForMembers = iteratorForMembers.getNext();
            }

            Columbus.Csharp.Asg.Nodes.Base.Base genNodePtr;
            // edge: TypeParameterList
            genNodePtr = fact.getRef(node.getTypeParameterList()) ;
            if (genNodePtr != null) {
              Columbus.Csharp.Asg.Nodes.Structure.TypeParameterListSyntax endNodeRef = (Columbus.Csharp.Asg.Nodes.Structure.TypeParameterListSyntax)(genNodePtr);
              foreach (var visitor in visitorList) {
                visitor.visitTypeDeclarationSyntax_TypeParameterList(node.Id, endNodeRef.Id);
              }

              clearStoppedVisitors();
              if(needPreorderStop)
                return;

              if ((!fact.IsFilterTurnedOn && !visitFilteredEdge) || (fact.getFilterState(endNodeRef.Id) == Filter.FilterState.NotFiltered) || (!originalFilterState && visitFilteredEdge)) {
                  endNodeRef.accept(this);
              }
              foreach (var visitor in visitorList) {
                visitor.visitEndTypeDeclarationSyntax_TypeParameterList(node.Id, endNodeRef.Id);
              }

              clearStoppedVisitors();
              if(needPreorderStop)
                return;

            }
        }

        /// <summary>
        /// It call the traversal for the edges
        /// </summary>
        /// <param name="node">[in] The node with own type</param>
        /// <param name="callVirtualBase">[in] This paramater is don't used just api copatibility used.</param>
        public void visitAllEdges(Columbus.Csharp.Asg.Nodes.Structure.TypeParameterConstraintClauseSyntax node, bool callFirst = true){
            visitAllEdges((Columbus.Csharp.Asg.Nodes.Base.Positioned)(node),false);


            // edge: Constraints
            ListIterator<Columbus.Csharp.Asg.Nodes.Structure.TypeParameterConstraintSyntax> iteratorForConstraints = node.ConstraintsListIteratorBegin;
            while (iteratorForConstraints.getValue() != null) {
               Columbus.Csharp.Asg.Nodes.Structure.TypeParameterConstraintSyntax endNodeRef = (Columbus.Csharp.Asg.Nodes.Structure.TypeParameterConstraintSyntax)iteratorForConstraints.getValue();
              foreach (var visitor in visitorList) {
                visitor.visitTypeParameterConstraintClauseSyntax_Constraints(node.Id, endNodeRef.Id);
              }

              clearStoppedVisitors();
              if(needPreorderStop)
                return;

              if ((!fact.IsFilterTurnedOn && !visitFilteredEdge) || (fact.getFilterState(endNodeRef.Id) == Filter.FilterState.NotFiltered) || (!originalFilterState && visitFilteredEdge)) {
                  endNodeRef.accept(this);
              }
              foreach (var visitor in visitorList) {
                visitor.visitEndTypeParameterConstraintClauseSyntax_Constraints(node.Id, endNodeRef.Id);
              }

              clearStoppedVisitors();
              if(needPreorderStop)
                return;

            iteratorForConstraints = iteratorForConstraints.getNext();
            }

            Columbus.Csharp.Asg.Nodes.Base.Base genNodePtr;
            // edge: Name
            genNodePtr = fact.getRef(node.getName()) ;
            if (genNodePtr != null) {
              Columbus.Csharp.Asg.Nodes.Expression.IdentifierNameSyntax endNodeRef = (Columbus.Csharp.Asg.Nodes.Expression.IdentifierNameSyntax)(genNodePtr);
              foreach (var visitor in visitorList) {
                visitor.visitTypeParameterConstraintClauseSyntax_Name(node.Id, endNodeRef.Id);
              }

              clearStoppedVisitors();
              if(needPreorderStop)
                return;

              if ((!fact.IsFilterTurnedOn && !visitFilteredEdge) || (fact.getFilterState(endNodeRef.Id) == Filter.FilterState.NotFiltered) || (!originalFilterState && visitFilteredEdge)) {
                  endNodeRef.accept(this);
              }
              foreach (var visitor in visitorList) {
                visitor.visitEndTypeParameterConstraintClauseSyntax_Name(node.Id, endNodeRef.Id);
              }

              clearStoppedVisitors();
              if(needPreorderStop)
                return;

            }
        }

        public override void visit(Columbus.Csharp.Asg.Nodes.Structure.TypeParameterConstraintClauseSyntax node, bool callFirst = true){
          if (safeMode || visitCrossEdgeTree) {
            if (safeMode) {
              if (visitedNodes[(int)node.Id]) { // for safemode
                return;
              }
            }
            visitedNodes[(int)node.Id] = true;
          }

          foreach (var visitor in visitorList) {
            visitor.visit(node);
            incVisitorDepth(visitor);
          }

          clearStoppedVisitors();
          if(needPreorderStop)
            return;

          visitAllEdges(node, true);

          foreach (var visitor in visitorList) {
            decVisitorDepth(visitor);
            visitor.visitEnd(node);
          }

          clearStoppedVisitors();
        }

        /// <summary>
        /// It call the traversal for the edges
        /// </summary>
        /// <param name="node">[in] The node with own type</param>
        /// <param name="callVirtualBase">[in] This paramater is don't used just api copatibility used.</param>
        public void visitAllEdges(Columbus.Csharp.Asg.Nodes.Structure.TypeParameterConstraintSyntax node, bool callFirst = true){
            visitAllEdges((Columbus.Csharp.Asg.Nodes.Base.Positioned)(node),false);
        }

        /// <summary>
        /// It call the traversal for the edges
        /// </summary>
        /// <param name="node">[in] The node with own type</param>
        /// <param name="callVirtualBase">[in] This paramater is don't used just api copatibility used.</param>
        public void visitAllEdges(Columbus.Csharp.Asg.Nodes.Structure.TypeParameterListSyntax node, bool callFirst = true){
            visitAllEdges((Columbus.Csharp.Asg.Nodes.Base.Positioned)(node),false);


            // edge: Parameters
            ListIterator<Columbus.Csharp.Asg.Nodes.Structure.TypeParameterSyntax> iteratorForParameters = node.ParametersListIteratorBegin;
            while (iteratorForParameters.getValue() != null) {
               Columbus.Csharp.Asg.Nodes.Structure.TypeParameterSyntax endNodeRef = (Columbus.Csharp.Asg.Nodes.Structure.TypeParameterSyntax)iteratorForParameters.getValue();
              foreach (var visitor in visitorList) {
                visitor.visitTypeParameterListSyntax_Parameters(node.Id, endNodeRef.Id);
              }

              clearStoppedVisitors();
              if(needPreorderStop)
                return;

              if ((!fact.IsFilterTurnedOn && !visitFilteredEdge) || (fact.getFilterState(endNodeRef.Id) == Filter.FilterState.NotFiltered) || (!originalFilterState && visitFilteredEdge)) {
                  endNodeRef.accept(this);
              }
              foreach (var visitor in visitorList) {
                visitor.visitEndTypeParameterListSyntax_Parameters(node.Id, endNodeRef.Id);
              }

              clearStoppedVisitors();
              if(needPreorderStop)
                return;

            iteratorForParameters = iteratorForParameters.getNext();
            }
        }

        public override void visit(Columbus.Csharp.Asg.Nodes.Structure.TypeParameterListSyntax node, bool callFirst = true){
          if (safeMode || visitCrossEdgeTree) {
            if (safeMode) {
              if (visitedNodes[(int)node.Id]) { // for safemode
                return;
              }
            }
            visitedNodes[(int)node.Id] = true;
          }

          foreach (var visitor in visitorList) {
            visitor.visit(node);
            incVisitorDepth(visitor);
          }

          clearStoppedVisitors();
          if(needPreorderStop)
            return;

          visitAllEdges(node, true);

          foreach (var visitor in visitorList) {
            decVisitorDepth(visitor);
            visitor.visitEnd(node);
          }

          clearStoppedVisitors();
        }

        /// <summary>
        /// It call the traversal for the edges
        /// </summary>
        /// <param name="node">[in] The node with own type</param>
        /// <param name="callVirtualBase">[in] This paramater is don't used just api copatibility used.</param>
        public void visitAllEdges(Columbus.Csharp.Asg.Nodes.Structure.TypeParameterSyntax node, bool callFirst = true){
            visitAllEdges((Columbus.Csharp.Asg.Nodes.Base.Positioned)(node),false);


            // edge: AttributeLists
            ListIterator<Columbus.Csharp.Asg.Nodes.Structure.AttributeListSyntax> iteratorForAttributeLists = node.AttributeListsListIteratorBegin;
            while (iteratorForAttributeLists.getValue() != null) {
               Columbus.Csharp.Asg.Nodes.Structure.AttributeListSyntax endNodeRef = (Columbus.Csharp.Asg.Nodes.Structure.AttributeListSyntax)iteratorForAttributeLists.getValue();
              foreach (var visitor in visitorList) {
                visitor.visitTypeParameterSyntax_AttributeLists(node.Id, endNodeRef.Id);
              }

              clearStoppedVisitors();
              if(needPreorderStop)
                return;

              if ((!fact.IsFilterTurnedOn && !visitFilteredEdge) || (fact.getFilterState(endNodeRef.Id) == Filter.FilterState.NotFiltered) || (!originalFilterState && visitFilteredEdge)) {
                  endNodeRef.accept(this);
              }
              foreach (var visitor in visitorList) {
                visitor.visitEndTypeParameterSyntax_AttributeLists(node.Id, endNodeRef.Id);
              }

              clearStoppedVisitors();
              if(needPreorderStop)
                return;

            iteratorForAttributeLists = iteratorForAttributeLists.getNext();
            }
        }

        public override void visit(Columbus.Csharp.Asg.Nodes.Structure.TypeParameterSyntax node, bool callFirst = true){
          if (safeMode || visitCrossEdgeTree) {
            if (safeMode) {
              if (visitedNodes[(int)node.Id]) { // for safemode
                return;
              }
            }
            visitedNodes[(int)node.Id] = true;
          }

          foreach (var visitor in visitorList) {
            visitor.visit(node);
            incVisitorDepth(visitor);
          }

          clearStoppedVisitors();
          if(needPreorderStop)
            return;

          visitAllEdges(node, true);

          foreach (var visitor in visitorList) {
            decVisitorDepth(visitor);
            visitor.visitEnd(node);
          }

          clearStoppedVisitors();
        }

        /// <summary>
        /// It call the traversal for the edges
        /// </summary>
        /// <param name="node">[in] The node with own type</param>
        /// <param name="callVirtualBase">[in] This paramater is don't used just api copatibility used.</param>
        public void visitAllEdges(Columbus.Csharp.Asg.Nodes.Structure.UsingDirectiveSyntax node, bool callFirst = true){
            visitAllEdges((Columbus.Csharp.Asg.Nodes.Base.Positioned)(node),false);


            Columbus.Csharp.Asg.Nodes.Base.Base genNodePtr;
            // edge: Alias
            genNodePtr = fact.getRef(node.getAlias()) ;
            if (genNodePtr != null) {
              Columbus.Csharp.Asg.Nodes.Structure.NameEqualsSyntax endNodeRef = (Columbus.Csharp.Asg.Nodes.Structure.NameEqualsSyntax)(genNodePtr);
              foreach (var visitor in visitorList) {
                visitor.visitUsingDirectiveSyntax_Alias(node.Id, endNodeRef.Id);
              }

              clearStoppedVisitors();
              if(needPreorderStop)
                return;

              if ((!fact.IsFilterTurnedOn && !visitFilteredEdge) || (fact.getFilterState(endNodeRef.Id) == Filter.FilterState.NotFiltered) || (!originalFilterState && visitFilteredEdge)) {
                  endNodeRef.accept(this);
              }
              foreach (var visitor in visitorList) {
                visitor.visitEndUsingDirectiveSyntax_Alias(node.Id, endNodeRef.Id);
              }

              clearStoppedVisitors();
              if(needPreorderStop)
                return;

            }

            // edge: Name
            genNodePtr = fact.getRef(node.getName()) ;
            if (genNodePtr != null) {
              Columbus.Csharp.Asg.Nodes.Expression.NameSyntax endNodeRef = (Columbus.Csharp.Asg.Nodes.Expression.NameSyntax)(genNodePtr);
              foreach (var visitor in visitorList) {
                visitor.visitUsingDirectiveSyntax_Name(node.Id, endNodeRef.Id);
              }

              clearStoppedVisitors();
              if(needPreorderStop)
                return;

              if ((!fact.IsFilterTurnedOn && !visitFilteredEdge) || (fact.getFilterState(endNodeRef.Id) == Filter.FilterState.NotFiltered) || (!originalFilterState && visitFilteredEdge)) {
                  endNodeRef.accept(this);
              }
              foreach (var visitor in visitorList) {
                visitor.visitEndUsingDirectiveSyntax_Name(node.Id, endNodeRef.Id);
              }

              clearStoppedVisitors();
              if(needPreorderStop)
                return;

            }
        }

        public override void visit(Columbus.Csharp.Asg.Nodes.Structure.UsingDirectiveSyntax node, bool callFirst = true){
          if (safeMode || visitCrossEdgeTree) {
            if (safeMode) {
              if (visitedNodes[(int)node.Id]) { // for safemode
                return;
              }
            }
            visitedNodes[(int)node.Id] = true;
          }

          foreach (var visitor in visitorList) {
            visitor.visit(node);
            incVisitorDepth(visitor);
          }

          clearStoppedVisitors();
          if(needPreorderStop)
            return;

          visitAllEdges(node, true);

          foreach (var visitor in visitorList) {
            decVisitorDepth(visitor);
            visitor.visitEnd(node);
          }

          clearStoppedVisitors();
        }

        /// <summary>
        /// It call the traversal for the edges
        /// </summary>
        /// <param name="node">[in] The node with own type</param>
        /// <param name="callVirtualBase">[in] This paramater is don't used just api copatibility used.</param>
        public void visitAllEdges(Columbus.Csharp.Asg.Nodes.Structure.VarPatternSyntax node, bool callFirst = true){
            visitAllEdges((Columbus.Csharp.Asg.Nodes.Structure.PatternSyntax)(node),false);


            Columbus.Csharp.Asg.Nodes.Base.Base genNodePtr;
            // edge: Designation
            genNodePtr = fact.getRef(node.getDesignation()) ;
            if (genNodePtr != null) {
              Columbus.Csharp.Asg.Nodes.Structure.VariableDesignationSyntax endNodeRef = (Columbus.Csharp.Asg.Nodes.Structure.VariableDesignationSyntax)(genNodePtr);
              foreach (var visitor in visitorList) {
                visitor.visitVarPatternSyntax_Designation(node.Id, endNodeRef.Id);
              }

              clearStoppedVisitors();
              if(needPreorderStop)
                return;

              if ((!fact.IsFilterTurnedOn && !visitFilteredEdge) || (fact.getFilterState(endNodeRef.Id) == Filter.FilterState.NotFiltered) || (!originalFilterState && visitFilteredEdge)) {
                  endNodeRef.accept(this);
              }
              foreach (var visitor in visitorList) {
                visitor.visitEndVarPatternSyntax_Designation(node.Id, endNodeRef.Id);
              }

              clearStoppedVisitors();
              if(needPreorderStop)
                return;

            }
        }

        public override void visit(Columbus.Csharp.Asg.Nodes.Structure.VarPatternSyntax node, bool callFirst = true){
          if (safeMode || visitCrossEdgeTree) {
            if (safeMode) {
              if (visitedNodes[(int)node.Id]) { // for safemode
                return;
              }
            }
            visitedNodes[(int)node.Id] = true;
          }

          foreach (var visitor in visitorList) {
            visitor.visit(node);
            incVisitorDepth(visitor);
          }

          clearStoppedVisitors();
          if(needPreorderStop)
            return;

          visitAllEdges(node, true);

          foreach (var visitor in visitorList) {
            decVisitorDepth(visitor);
            visitor.visitEnd(node);
          }

          clearStoppedVisitors();
        }

        /// <summary>
        /// It call the traversal for the edges
        /// </summary>
        /// <param name="node">[in] The node with own type</param>
        /// <param name="callVirtualBase">[in] This paramater is don't used just api copatibility used.</param>
        public void visitAllEdges(Columbus.Csharp.Asg.Nodes.Structure.VariableDeclarationSyntax node, bool callFirst = true){
            visitAllEdges((Columbus.Csharp.Asg.Nodes.Base.Positioned)(node),false);


            Columbus.Csharp.Asg.Nodes.Base.Base genNodePtr;
            // edge: Type
            genNodePtr = fact.getRef(node.getType()) ;
            if (genNodePtr != null) {
              Columbus.Csharp.Asg.Nodes.Expression.TypeSyntax endNodeRef = (Columbus.Csharp.Asg.Nodes.Expression.TypeSyntax)(genNodePtr);
              foreach (var visitor in visitorList) {
                visitor.visitVariableDeclarationSyntax_Type(node.Id, endNodeRef.Id);
              }

              clearStoppedVisitors();
              if(needPreorderStop)
                return;

              if ((!fact.IsFilterTurnedOn && !visitFilteredEdge) || (fact.getFilterState(endNodeRef.Id) == Filter.FilterState.NotFiltered) || (!originalFilterState && visitFilteredEdge)) {
                  endNodeRef.accept(this);
              }
              foreach (var visitor in visitorList) {
                visitor.visitEndVariableDeclarationSyntax_Type(node.Id, endNodeRef.Id);
              }

              clearStoppedVisitors();
              if(needPreorderStop)
                return;

            }

            // edge: Variables
            ListIterator<Columbus.Csharp.Asg.Nodes.Structure.VariableDeclaratorSyntax> iteratorForVariables = node.VariablesListIteratorBegin;
            while (iteratorForVariables.getValue() != null) {
               Columbus.Csharp.Asg.Nodes.Structure.VariableDeclaratorSyntax endNodeRef = (Columbus.Csharp.Asg.Nodes.Structure.VariableDeclaratorSyntax)iteratorForVariables.getValue();
              foreach (var visitor in visitorList) {
                visitor.visitVariableDeclarationSyntax_Variables(node.Id, endNodeRef.Id);
              }

              clearStoppedVisitors();
              if(needPreorderStop)
                return;

              if ((!fact.IsFilterTurnedOn && !visitFilteredEdge) || (fact.getFilterState(endNodeRef.Id) == Filter.FilterState.NotFiltered) || (!originalFilterState && visitFilteredEdge)) {
                  endNodeRef.accept(this);
              }
              foreach (var visitor in visitorList) {
                visitor.visitEndVariableDeclarationSyntax_Variables(node.Id, endNodeRef.Id);
              }

              clearStoppedVisitors();
              if(needPreorderStop)
                return;

            iteratorForVariables = iteratorForVariables.getNext();
            }
        }

        public override void visit(Columbus.Csharp.Asg.Nodes.Structure.VariableDeclarationSyntax node, bool callFirst = true){
          if (safeMode || visitCrossEdgeTree) {
            if (safeMode) {
              if (visitedNodes[(int)node.Id]) { // for safemode
                return;
              }
            }
            visitedNodes[(int)node.Id] = true;
          }

          foreach (var visitor in visitorList) {
            visitor.visit(node);
            incVisitorDepth(visitor);
          }

          clearStoppedVisitors();
          if(needPreorderStop)
            return;

          visitAllEdges(node, true);

          foreach (var visitor in visitorList) {
            decVisitorDepth(visitor);
            visitor.visitEnd(node);
          }

          clearStoppedVisitors();
        }

        /// <summary>
        /// It call the traversal for the edges
        /// </summary>
        /// <param name="node">[in] The node with own type</param>
        /// <param name="callVirtualBase">[in] This paramater is don't used just api copatibility used.</param>
        public void visitAllEdges(Columbus.Csharp.Asg.Nodes.Structure.VariableDeclaratorSyntax node, bool callFirst = true){
            visitAllEdges((Columbus.Csharp.Asg.Nodes.Base.Positioned)(node),false);


            Columbus.Csharp.Asg.Nodes.Base.Base genNodePtr;
            // edge: ArgumentList
            genNodePtr = fact.getRef(node.getArgumentList()) ;
            if (genNodePtr != null) {
              Columbus.Csharp.Asg.Nodes.Structure.BracketedArgumentListSyntax endNodeRef = (Columbus.Csharp.Asg.Nodes.Structure.BracketedArgumentListSyntax)(genNodePtr);
              foreach (var visitor in visitorList) {
                visitor.visitVariableDeclaratorSyntax_ArgumentList(node.Id, endNodeRef.Id);
              }

              clearStoppedVisitors();
              if(needPreorderStop)
                return;

              if ((!fact.IsFilterTurnedOn && !visitFilteredEdge) || (fact.getFilterState(endNodeRef.Id) == Filter.FilterState.NotFiltered) || (!originalFilterState && visitFilteredEdge)) {
                  endNodeRef.accept(this);
              }
              foreach (var visitor in visitorList) {
                visitor.visitEndVariableDeclaratorSyntax_ArgumentList(node.Id, endNodeRef.Id);
              }

              clearStoppedVisitors();
              if(needPreorderStop)
                return;

            }

            // edge: Initializer
            genNodePtr = fact.getRef(node.getInitializer()) ;
            if (genNodePtr != null) {
              Columbus.Csharp.Asg.Nodes.Structure.EqualsValueClauseSyntax endNodeRef = (Columbus.Csharp.Asg.Nodes.Structure.EqualsValueClauseSyntax)(genNodePtr);
              foreach (var visitor in visitorList) {
                visitor.visitVariableDeclaratorSyntax_Initializer(node.Id, endNodeRef.Id);
              }

              clearStoppedVisitors();
              if(needPreorderStop)
                return;

              if ((!fact.IsFilterTurnedOn && !visitFilteredEdge) || (fact.getFilterState(endNodeRef.Id) == Filter.FilterState.NotFiltered) || (!originalFilterState && visitFilteredEdge)) {
                  endNodeRef.accept(this);
              }
              foreach (var visitor in visitorList) {
                visitor.visitEndVariableDeclaratorSyntax_Initializer(node.Id, endNodeRef.Id);
              }

              clearStoppedVisitors();
              if(needPreorderStop)
                return;

            }
        }

        public override void visit(Columbus.Csharp.Asg.Nodes.Structure.VariableDeclaratorSyntax node, bool callFirst = true){
          if (safeMode || visitCrossEdgeTree) {
            if (safeMode) {
              if (visitedNodes[(int)node.Id]) { // for safemode
                return;
              }
            }
            visitedNodes[(int)node.Id] = true;
          }

          foreach (var visitor in visitorList) {
            visitor.visit(node);
            incVisitorDepth(visitor);
          }

          clearStoppedVisitors();
          if(needPreorderStop)
            return;

          visitAllEdges(node, true);

          foreach (var visitor in visitorList) {
            decVisitorDepth(visitor);
            visitor.visitEnd(node);
          }

          clearStoppedVisitors();
        }

        /// <summary>
        /// It call the traversal for the edges
        /// </summary>
        /// <param name="node">[in] The node with own type</param>
        /// <param name="callVirtualBase">[in] This paramater is don't used just api copatibility used.</param>
        public void visitAllEdges(Columbus.Csharp.Asg.Nodes.Structure.VariableDesignationSyntax node, bool callFirst = true){
            visitAllEdges((Columbus.Csharp.Asg.Nodes.Base.Positioned)(node),false);
        }

        /// <summary>
        /// It call the traversal for the edges
        /// </summary>
        /// <param name="node">[in] The node with own type</param>
        /// <param name="callVirtualBase">[in] This paramater is don't used just api copatibility used.</param>
        public void visitAllEdges(Columbus.Csharp.Asg.Nodes.Structure.WhenClauseSyntax node, bool callFirst = true){
            visitAllEdges((Columbus.Csharp.Asg.Nodes.Base.Positioned)(node),false);


            Columbus.Csharp.Asg.Nodes.Base.Base genNodePtr;
            // edge: Condition
            genNodePtr = fact.getRef(node.getCondition()) ;
            if (genNodePtr != null) {
              Columbus.Csharp.Asg.Nodes.Expression.ExpressionSyntax endNodeRef = (Columbus.Csharp.Asg.Nodes.Expression.ExpressionSyntax)(genNodePtr);
              foreach (var visitor in visitorList) {
                visitor.visitWhenClauseSyntax_Condition(node.Id, endNodeRef.Id);
              }

              clearStoppedVisitors();
              if(needPreorderStop)
                return;

              if ((!fact.IsFilterTurnedOn && !visitFilteredEdge) || (fact.getFilterState(endNodeRef.Id) == Filter.FilterState.NotFiltered) || (!originalFilterState && visitFilteredEdge)) {
                  endNodeRef.accept(this);
              }
              foreach (var visitor in visitorList) {
                visitor.visitEndWhenClauseSyntax_Condition(node.Id, endNodeRef.Id);
              }

              clearStoppedVisitors();
              if(needPreorderStop)
                return;

            }
        }

        public override void visit(Columbus.Csharp.Asg.Nodes.Structure.WhenClauseSyntax node, bool callFirst = true){
          if (safeMode || visitCrossEdgeTree) {
            if (safeMode) {
              if (visitedNodes[(int)node.Id]) { // for safemode
                return;
              }
            }
            visitedNodes[(int)node.Id] = true;
          }

          foreach (var visitor in visitorList) {
            visitor.visit(node);
            incVisitorDepth(visitor);
          }

          clearStoppedVisitors();
          if(needPreorderStop)
            return;

          visitAllEdges(node, true);

          foreach (var visitor in visitorList) {
            decVisitorDepth(visitor);
            visitor.visitEnd(node);
          }

          clearStoppedVisitors();
        }

        /// <summary>
        /// It call the traversal for the edges
        /// </summary>
        /// <param name="node">[in] The node with own type</param>
        /// <param name="callVirtualBase">[in] This paramater is don't used just api copatibility used.</param>
        public void visitAllEdges(Columbus.Csharp.Asg.Nodes.Structure.WhereClauseSyntax node, bool callFirst = true){
            visitAllEdges((Columbus.Csharp.Asg.Nodes.Structure.QueryClauseSyntax)(node),false);


            Columbus.Csharp.Asg.Nodes.Base.Base genNodePtr;
            // edge: Condition
            genNodePtr = fact.getRef(node.getCondition()) ;
            if (genNodePtr != null) {
              Columbus.Csharp.Asg.Nodes.Expression.ExpressionSyntax endNodeRef = (Columbus.Csharp.Asg.Nodes.Expression.ExpressionSyntax)(genNodePtr);
              foreach (var visitor in visitorList) {
                visitor.visitWhereClauseSyntax_Condition(node.Id, endNodeRef.Id);
              }

              clearStoppedVisitors();
              if(needPreorderStop)
                return;

              if ((!fact.IsFilterTurnedOn && !visitFilteredEdge) || (fact.getFilterState(endNodeRef.Id) == Filter.FilterState.NotFiltered) || (!originalFilterState && visitFilteredEdge)) {
                  endNodeRef.accept(this);
              }
              foreach (var visitor in visitorList) {
                visitor.visitEndWhereClauseSyntax_Condition(node.Id, endNodeRef.Id);
              }

              clearStoppedVisitors();
              if(needPreorderStop)
                return;

            }
        }

        public override void visit(Columbus.Csharp.Asg.Nodes.Structure.WhereClauseSyntax node, bool callFirst = true){
          if (safeMode || visitCrossEdgeTree) {
            if (safeMode) {
              if (visitedNodes[(int)node.Id]) { // for safemode
                return;
              }
            }
            visitedNodes[(int)node.Id] = true;
          }

          foreach (var visitor in visitorList) {
            visitor.visit(node);
            incVisitorDepth(visitor);
          }

          clearStoppedVisitors();
          if(needPreorderStop)
            return;

          visitAllEdges(node, true);

          foreach (var visitor in visitorList) {
            decVisitorDepth(visitor);
            visitor.visitEnd(node);
          }

          clearStoppedVisitors();
        }

        /// <summary>
        /// It call the traversal for the edges
        /// </summary>
        /// <param name="node">[in] The node with own type</param>
        /// <param name="callVirtualBase">[in] This paramater is don't used just api copatibility used.</param>
        public void visitAllEdges(Columbus.Csharp.Asg.Nodes.Structure.XmlAttributeSyntax node, bool callFirst = true){
            visitAllEdges((Columbus.Csharp.Asg.Nodes.Base.Positioned)(node),false);


            Columbus.Csharp.Asg.Nodes.Base.Base genNodePtr;
            // edge: Name
            genNodePtr = fact.getRef(node.getName()) ;
            if (genNodePtr != null) {
              Columbus.Csharp.Asg.Nodes.Structure.XmlNameSyntax endNodeRef = (Columbus.Csharp.Asg.Nodes.Structure.XmlNameSyntax)(genNodePtr);
              foreach (var visitor in visitorList) {
                visitor.visitXmlAttributeSyntax_Name(node.Id, endNodeRef.Id);
              }

              clearStoppedVisitors();
              if(needPreorderStop)
                return;

              if ((!fact.IsFilterTurnedOn && !visitFilteredEdge) || (fact.getFilterState(endNodeRef.Id) == Filter.FilterState.NotFiltered) || (!originalFilterState && visitFilteredEdge)) {
                  endNodeRef.accept(this);
              }
              foreach (var visitor in visitorList) {
                visitor.visitEndXmlAttributeSyntax_Name(node.Id, endNodeRef.Id);
              }

              clearStoppedVisitors();
              if(needPreorderStop)
                return;

            }
        }

        /// <summary>
        /// It call the traversal for the edges
        /// </summary>
        /// <param name="node">[in] The node with own type</param>
        /// <param name="callVirtualBase">[in] This paramater is don't used just api copatibility used.</param>
        public void visitAllEdges(Columbus.Csharp.Asg.Nodes.Structure.XmlCDataSectionSyntax node, bool callFirst = true){
            visitAllEdges((Columbus.Csharp.Asg.Nodes.Structure.XmlNodeSyntax)(node),false);
        }

        public override void visit(Columbus.Csharp.Asg.Nodes.Structure.XmlCDataSectionSyntax node, bool callFirst = true){
          if (safeMode || visitCrossEdgeTree) {
            if (safeMode) {
              if (visitedNodes[(int)node.Id]) { // for safemode
                return;
              }
            }
            visitedNodes[(int)node.Id] = true;
          }

          foreach (var visitor in visitorList) {
            visitor.visit(node);
            incVisitorDepth(visitor);
          }

          clearStoppedVisitors();
          if(needPreorderStop)
            return;

          visitAllEdges(node, true);

          foreach (var visitor in visitorList) {
            decVisitorDepth(visitor);
            visitor.visitEnd(node);
          }

          clearStoppedVisitors();
        }

        /// <summary>
        /// It call the traversal for the edges
        /// </summary>
        /// <param name="node">[in] The node with own type</param>
        /// <param name="callVirtualBase">[in] This paramater is don't used just api copatibility used.</param>
        public void visitAllEdges(Columbus.Csharp.Asg.Nodes.Structure.XmlCommentSyntax node, bool callFirst = true){
            visitAllEdges((Columbus.Csharp.Asg.Nodes.Structure.XmlNodeSyntax)(node),false);
        }

        public override void visit(Columbus.Csharp.Asg.Nodes.Structure.XmlCommentSyntax node, bool callFirst = true){
          if (safeMode || visitCrossEdgeTree) {
            if (safeMode) {
              if (visitedNodes[(int)node.Id]) { // for safemode
                return;
              }
            }
            visitedNodes[(int)node.Id] = true;
          }

          foreach (var visitor in visitorList) {
            visitor.visit(node);
            incVisitorDepth(visitor);
          }

          clearStoppedVisitors();
          if(needPreorderStop)
            return;

          visitAllEdges(node, true);

          foreach (var visitor in visitorList) {
            decVisitorDepth(visitor);
            visitor.visitEnd(node);
          }

          clearStoppedVisitors();
        }

        /// <summary>
        /// It call the traversal for the edges
        /// </summary>
        /// <param name="node">[in] The node with own type</param>
        /// <param name="callVirtualBase">[in] This paramater is don't used just api copatibility used.</param>
        public void visitAllEdges(Columbus.Csharp.Asg.Nodes.Structure.XmlCrefAttributeSyntax node, bool callFirst = true){
            visitAllEdges((Columbus.Csharp.Asg.Nodes.Structure.XmlAttributeSyntax)(node),false);


            Columbus.Csharp.Asg.Nodes.Base.Base genNodePtr;
            // edge: Cref
            genNodePtr = fact.getRef(node.getCref()) ;
            if (genNodePtr != null) {
              Columbus.Csharp.Asg.Nodes.Structure.CrefSyntax endNodeRef = (Columbus.Csharp.Asg.Nodes.Structure.CrefSyntax)(genNodePtr);
              foreach (var visitor in visitorList) {
                visitor.visitXmlCrefAttributeSyntax_Cref(node.Id, endNodeRef.Id);
              }

              clearStoppedVisitors();
              if(needPreorderStop)
                return;

              if ((!fact.IsFilterTurnedOn && !visitFilteredEdge) || (fact.getFilterState(endNodeRef.Id) == Filter.FilterState.NotFiltered) || (!originalFilterState && visitFilteredEdge)) {
                  endNodeRef.accept(this);
              }
              foreach (var visitor in visitorList) {
                visitor.visitEndXmlCrefAttributeSyntax_Cref(node.Id, endNodeRef.Id);
              }

              clearStoppedVisitors();
              if(needPreorderStop)
                return;

            }
        }

        public override void visit(Columbus.Csharp.Asg.Nodes.Structure.XmlCrefAttributeSyntax node, bool callFirst = true){
          if (safeMode || visitCrossEdgeTree) {
            if (safeMode) {
              if (visitedNodes[(int)node.Id]) { // for safemode
                return;
              }
            }
            visitedNodes[(int)node.Id] = true;
          }

          foreach (var visitor in visitorList) {
            visitor.visit(node);
            incVisitorDepth(visitor);
          }

          clearStoppedVisitors();
          if(needPreorderStop)
            return;

          visitAllEdges(node, true);

          foreach (var visitor in visitorList) {
            decVisitorDepth(visitor);
            visitor.visitEnd(node);
          }

          clearStoppedVisitors();
        }

        /// <summary>
        /// It call the traversal for the edges
        /// </summary>
        /// <param name="node">[in] The node with own type</param>
        /// <param name="callVirtualBase">[in] This paramater is don't used just api copatibility used.</param>
        public void visitAllEdges(Columbus.Csharp.Asg.Nodes.Structure.XmlElementEndTagSyntax node, bool callFirst = true){
            visitAllEdges((Columbus.Csharp.Asg.Nodes.Base.Positioned)(node),false);


            Columbus.Csharp.Asg.Nodes.Base.Base genNodePtr;
            // edge: Name
            genNodePtr = fact.getRef(node.getName()) ;
            if (genNodePtr != null) {
              Columbus.Csharp.Asg.Nodes.Structure.XmlNameSyntax endNodeRef = (Columbus.Csharp.Asg.Nodes.Structure.XmlNameSyntax)(genNodePtr);
              foreach (var visitor in visitorList) {
                visitor.visitXmlElementEndTagSyntax_Name(node.Id, endNodeRef.Id);
              }

              clearStoppedVisitors();
              if(needPreorderStop)
                return;

              if ((!fact.IsFilterTurnedOn && !visitFilteredEdge) || (fact.getFilterState(endNodeRef.Id) == Filter.FilterState.NotFiltered) || (!originalFilterState && visitFilteredEdge)) {
                  endNodeRef.accept(this);
              }
              foreach (var visitor in visitorList) {
                visitor.visitEndXmlElementEndTagSyntax_Name(node.Id, endNodeRef.Id);
              }

              clearStoppedVisitors();
              if(needPreorderStop)
                return;

            }
        }

        public override void visit(Columbus.Csharp.Asg.Nodes.Structure.XmlElementEndTagSyntax node, bool callFirst = true){
          if (safeMode || visitCrossEdgeTree) {
            if (safeMode) {
              if (visitedNodes[(int)node.Id]) { // for safemode
                return;
              }
            }
            visitedNodes[(int)node.Id] = true;
          }

          foreach (var visitor in visitorList) {
            visitor.visit(node);
            incVisitorDepth(visitor);
          }

          clearStoppedVisitors();
          if(needPreorderStop)
            return;

          visitAllEdges(node, true);

          foreach (var visitor in visitorList) {
            decVisitorDepth(visitor);
            visitor.visitEnd(node);
          }

          clearStoppedVisitors();
        }

        /// <summary>
        /// It call the traversal for the edges
        /// </summary>
        /// <param name="node">[in] The node with own type</param>
        /// <param name="callVirtualBase">[in] This paramater is don't used just api copatibility used.</param>
        public void visitAllEdges(Columbus.Csharp.Asg.Nodes.Structure.XmlElementStartTagSyntax node, bool callFirst = true){
            visitAllEdges((Columbus.Csharp.Asg.Nodes.Base.Positioned)(node),false);


            // edge: Attributes
            ListIterator<Columbus.Csharp.Asg.Nodes.Structure.XmlAttributeSyntax> iteratorForAttributes = node.AttributesListIteratorBegin;
            while (iteratorForAttributes.getValue() != null) {
               Columbus.Csharp.Asg.Nodes.Structure.XmlAttributeSyntax endNodeRef = (Columbus.Csharp.Asg.Nodes.Structure.XmlAttributeSyntax)iteratorForAttributes.getValue();
              foreach (var visitor in visitorList) {
                visitor.visitXmlElementStartTagSyntax_Attributes(node.Id, endNodeRef.Id);
              }

              clearStoppedVisitors();
              if(needPreorderStop)
                return;

              if ((!fact.IsFilterTurnedOn && !visitFilteredEdge) || (fact.getFilterState(endNodeRef.Id) == Filter.FilterState.NotFiltered) || (!originalFilterState && visitFilteredEdge)) {
                  endNodeRef.accept(this);
              }
              foreach (var visitor in visitorList) {
                visitor.visitEndXmlElementStartTagSyntax_Attributes(node.Id, endNodeRef.Id);
              }

              clearStoppedVisitors();
              if(needPreorderStop)
                return;

            iteratorForAttributes = iteratorForAttributes.getNext();
            }

            Columbus.Csharp.Asg.Nodes.Base.Base genNodePtr;
            // edge: Name
            genNodePtr = fact.getRef(node.getName()) ;
            if (genNodePtr != null) {
              Columbus.Csharp.Asg.Nodes.Structure.XmlNameSyntax endNodeRef = (Columbus.Csharp.Asg.Nodes.Structure.XmlNameSyntax)(genNodePtr);
              foreach (var visitor in visitorList) {
                visitor.visitXmlElementStartTagSyntax_Name(node.Id, endNodeRef.Id);
              }

              clearStoppedVisitors();
              if(needPreorderStop)
                return;

              if ((!fact.IsFilterTurnedOn && !visitFilteredEdge) || (fact.getFilterState(endNodeRef.Id) == Filter.FilterState.NotFiltered) || (!originalFilterState && visitFilteredEdge)) {
                  endNodeRef.accept(this);
              }
              foreach (var visitor in visitorList) {
                visitor.visitEndXmlElementStartTagSyntax_Name(node.Id, endNodeRef.Id);
              }

              clearStoppedVisitors();
              if(needPreorderStop)
                return;

            }
        }

        public override void visit(Columbus.Csharp.Asg.Nodes.Structure.XmlElementStartTagSyntax node, bool callFirst = true){
          if (safeMode || visitCrossEdgeTree) {
            if (safeMode) {
              if (visitedNodes[(int)node.Id]) { // for safemode
                return;
              }
            }
            visitedNodes[(int)node.Id] = true;
          }

          foreach (var visitor in visitorList) {
            visitor.visit(node);
            incVisitorDepth(visitor);
          }

          clearStoppedVisitors();
          if(needPreorderStop)
            return;

          visitAllEdges(node, true);

          foreach (var visitor in visitorList) {
            decVisitorDepth(visitor);
            visitor.visitEnd(node);
          }

          clearStoppedVisitors();
        }

        /// <summary>
        /// It call the traversal for the edges
        /// </summary>
        /// <param name="node">[in] The node with own type</param>
        /// <param name="callVirtualBase">[in] This paramater is don't used just api copatibility used.</param>
        public void visitAllEdges(Columbus.Csharp.Asg.Nodes.Structure.XmlElementSyntax node, bool callFirst = true){
            visitAllEdges((Columbus.Csharp.Asg.Nodes.Structure.XmlNodeSyntax)(node),false);


            // edge: Content
            ListIterator<Columbus.Csharp.Asg.Nodes.Structure.XmlNodeSyntax> iteratorForContent = node.ContentListIteratorBegin;
            while (iteratorForContent.getValue() != null) {
               Columbus.Csharp.Asg.Nodes.Structure.XmlNodeSyntax endNodeRef = (Columbus.Csharp.Asg.Nodes.Structure.XmlNodeSyntax)iteratorForContent.getValue();
              foreach (var visitor in visitorList) {
                visitor.visitXmlElementSyntax_Content(node.Id, endNodeRef.Id);
              }

              clearStoppedVisitors();
              if(needPreorderStop)
                return;

              if ((!fact.IsFilterTurnedOn && !visitFilteredEdge) || (fact.getFilterState(endNodeRef.Id) == Filter.FilterState.NotFiltered) || (!originalFilterState && visitFilteredEdge)) {
                  endNodeRef.accept(this);
              }
              foreach (var visitor in visitorList) {
                visitor.visitEndXmlElementSyntax_Content(node.Id, endNodeRef.Id);
              }

              clearStoppedVisitors();
              if(needPreorderStop)
                return;

            iteratorForContent = iteratorForContent.getNext();
            }

            Columbus.Csharp.Asg.Nodes.Base.Base genNodePtr;
            // edge: EndTag
            genNodePtr = fact.getRef(node.getEndTag()) ;
            if (genNodePtr != null) {
              Columbus.Csharp.Asg.Nodes.Structure.XmlElementEndTagSyntax endNodeRef = (Columbus.Csharp.Asg.Nodes.Structure.XmlElementEndTagSyntax)(genNodePtr);
              foreach (var visitor in visitorList) {
                visitor.visitXmlElementSyntax_EndTag(node.Id, endNodeRef.Id);
              }

              clearStoppedVisitors();
              if(needPreorderStop)
                return;

              if ((!fact.IsFilterTurnedOn && !visitFilteredEdge) || (fact.getFilterState(endNodeRef.Id) == Filter.FilterState.NotFiltered) || (!originalFilterState && visitFilteredEdge)) {
                  endNodeRef.accept(this);
              }
              foreach (var visitor in visitorList) {
                visitor.visitEndXmlElementSyntax_EndTag(node.Id, endNodeRef.Id);
              }

              clearStoppedVisitors();
              if(needPreorderStop)
                return;

            }

            // edge: StartTag
            genNodePtr = fact.getRef(node.getStartTag()) ;
            if (genNodePtr != null) {
              Columbus.Csharp.Asg.Nodes.Structure.XmlElementStartTagSyntax endNodeRef = (Columbus.Csharp.Asg.Nodes.Structure.XmlElementStartTagSyntax)(genNodePtr);
              foreach (var visitor in visitorList) {
                visitor.visitXmlElementSyntax_StartTag(node.Id, endNodeRef.Id);
              }

              clearStoppedVisitors();
              if(needPreorderStop)
                return;

              if ((!fact.IsFilterTurnedOn && !visitFilteredEdge) || (fact.getFilterState(endNodeRef.Id) == Filter.FilterState.NotFiltered) || (!originalFilterState && visitFilteredEdge)) {
                  endNodeRef.accept(this);
              }
              foreach (var visitor in visitorList) {
                visitor.visitEndXmlElementSyntax_StartTag(node.Id, endNodeRef.Id);
              }

              clearStoppedVisitors();
              if(needPreorderStop)
                return;

            }
        }

        public override void visit(Columbus.Csharp.Asg.Nodes.Structure.XmlElementSyntax node, bool callFirst = true){
          if (safeMode || visitCrossEdgeTree) {
            if (safeMode) {
              if (visitedNodes[(int)node.Id]) { // for safemode
                return;
              }
            }
            visitedNodes[(int)node.Id] = true;
          }

          foreach (var visitor in visitorList) {
            visitor.visit(node);
            incVisitorDepth(visitor);
          }

          clearStoppedVisitors();
          if(needPreorderStop)
            return;

          visitAllEdges(node, true);

          foreach (var visitor in visitorList) {
            decVisitorDepth(visitor);
            visitor.visitEnd(node);
          }

          clearStoppedVisitors();
        }

        /// <summary>
        /// It call the traversal for the edges
        /// </summary>
        /// <param name="node">[in] The node with own type</param>
        /// <param name="callVirtualBase">[in] This paramater is don't used just api copatibility used.</param>
        public void visitAllEdges(Columbus.Csharp.Asg.Nodes.Structure.XmlEmptyElementSyntax node, bool callFirst = true){
            visitAllEdges((Columbus.Csharp.Asg.Nodes.Structure.XmlNodeSyntax)(node),false);


            // edge: Attributes
            ListIterator<Columbus.Csharp.Asg.Nodes.Structure.XmlAttributeSyntax> iteratorForAttributes = node.AttributesListIteratorBegin;
            while (iteratorForAttributes.getValue() != null) {
               Columbus.Csharp.Asg.Nodes.Structure.XmlAttributeSyntax endNodeRef = (Columbus.Csharp.Asg.Nodes.Structure.XmlAttributeSyntax)iteratorForAttributes.getValue();
              foreach (var visitor in visitorList) {
                visitor.visitXmlEmptyElementSyntax_Attributes(node.Id, endNodeRef.Id);
              }

              clearStoppedVisitors();
              if(needPreorderStop)
                return;

              if ((!fact.IsFilterTurnedOn && !visitFilteredEdge) || (fact.getFilterState(endNodeRef.Id) == Filter.FilterState.NotFiltered) || (!originalFilterState && visitFilteredEdge)) {
                  endNodeRef.accept(this);
              }
              foreach (var visitor in visitorList) {
                visitor.visitEndXmlEmptyElementSyntax_Attributes(node.Id, endNodeRef.Id);
              }

              clearStoppedVisitors();
              if(needPreorderStop)
                return;

            iteratorForAttributes = iteratorForAttributes.getNext();
            }

            Columbus.Csharp.Asg.Nodes.Base.Base genNodePtr;
            // edge: Name
            genNodePtr = fact.getRef(node.getName()) ;
            if (genNodePtr != null) {
              Columbus.Csharp.Asg.Nodes.Structure.XmlNameSyntax endNodeRef = (Columbus.Csharp.Asg.Nodes.Structure.XmlNameSyntax)(genNodePtr);
              foreach (var visitor in visitorList) {
                visitor.visitXmlEmptyElementSyntax_Name(node.Id, endNodeRef.Id);
              }

              clearStoppedVisitors();
              if(needPreorderStop)
                return;

              if ((!fact.IsFilterTurnedOn && !visitFilteredEdge) || (fact.getFilterState(endNodeRef.Id) == Filter.FilterState.NotFiltered) || (!originalFilterState && visitFilteredEdge)) {
                  endNodeRef.accept(this);
              }
              foreach (var visitor in visitorList) {
                visitor.visitEndXmlEmptyElementSyntax_Name(node.Id, endNodeRef.Id);
              }

              clearStoppedVisitors();
              if(needPreorderStop)
                return;

            }
        }

        public override void visit(Columbus.Csharp.Asg.Nodes.Structure.XmlEmptyElementSyntax node, bool callFirst = true){
          if (safeMode || visitCrossEdgeTree) {
            if (safeMode) {
              if (visitedNodes[(int)node.Id]) { // for safemode
                return;
              }
            }
            visitedNodes[(int)node.Id] = true;
          }

          foreach (var visitor in visitorList) {
            visitor.visit(node);
            incVisitorDepth(visitor);
          }

          clearStoppedVisitors();
          if(needPreorderStop)
            return;

          visitAllEdges(node, true);

          foreach (var visitor in visitorList) {
            decVisitorDepth(visitor);
            visitor.visitEnd(node);
          }

          clearStoppedVisitors();
        }

        /// <summary>
        /// It call the traversal for the edges
        /// </summary>
        /// <param name="node">[in] The node with own type</param>
        /// <param name="callVirtualBase">[in] This paramater is don't used just api copatibility used.</param>
        public void visitAllEdges(Columbus.Csharp.Asg.Nodes.Structure.XmlNameAttributeSyntax node, bool callFirst = true){
            visitAllEdges((Columbus.Csharp.Asg.Nodes.Structure.XmlAttributeSyntax)(node),false);


            Columbus.Csharp.Asg.Nodes.Base.Base genNodePtr;
            // edge: Identifier
            genNodePtr = fact.getRef(node.getIdentifier()) ;
            if (genNodePtr != null) {
              Columbus.Csharp.Asg.Nodes.Expression.IdentifierNameSyntax endNodeRef = (Columbus.Csharp.Asg.Nodes.Expression.IdentifierNameSyntax)(genNodePtr);
              foreach (var visitor in visitorList) {
                visitor.visitXmlNameAttributeSyntax_Identifier(node.Id, endNodeRef.Id);
              }

              clearStoppedVisitors();
              if(needPreorderStop)
                return;

              if ((!fact.IsFilterTurnedOn && !visitFilteredEdge) || (fact.getFilterState(endNodeRef.Id) == Filter.FilterState.NotFiltered) || (!originalFilterState && visitFilteredEdge)) {
                  endNodeRef.accept(this);
              }
              foreach (var visitor in visitorList) {
                visitor.visitEndXmlNameAttributeSyntax_Identifier(node.Id, endNodeRef.Id);
              }

              clearStoppedVisitors();
              if(needPreorderStop)
                return;

            }
        }

        public override void visit(Columbus.Csharp.Asg.Nodes.Structure.XmlNameAttributeSyntax node, bool callFirst = true){
          if (safeMode || visitCrossEdgeTree) {
            if (safeMode) {
              if (visitedNodes[(int)node.Id]) { // for safemode
                return;
              }
            }
            visitedNodes[(int)node.Id] = true;
          }

          foreach (var visitor in visitorList) {
            visitor.visit(node);
            incVisitorDepth(visitor);
          }

          clearStoppedVisitors();
          if(needPreorderStop)
            return;

          visitAllEdges(node, true);

          foreach (var visitor in visitorList) {
            decVisitorDepth(visitor);
            visitor.visitEnd(node);
          }

          clearStoppedVisitors();
        }

        /// <summary>
        /// It call the traversal for the edges
        /// </summary>
        /// <param name="node">[in] The node with own type</param>
        /// <param name="callVirtualBase">[in] This paramater is don't used just api copatibility used.</param>
        public void visitAllEdges(Columbus.Csharp.Asg.Nodes.Structure.XmlNameSyntax node, bool callFirst = true){
            visitAllEdges((Columbus.Csharp.Asg.Nodes.Base.Positioned)(node),false);


            Columbus.Csharp.Asg.Nodes.Base.Base genNodePtr;
            // edge: Prefix
            genNodePtr = fact.getRef(node.getPrefix()) ;
            if (genNodePtr != null) {
              Columbus.Csharp.Asg.Nodes.Structure.XmlPrefixSyntax endNodeRef = (Columbus.Csharp.Asg.Nodes.Structure.XmlPrefixSyntax)(genNodePtr);
              foreach (var visitor in visitorList) {
                visitor.visitXmlNameSyntax_Prefix(node.Id, endNodeRef.Id);
              }

              clearStoppedVisitors();
              if(needPreorderStop)
                return;

              if ((!fact.IsFilterTurnedOn && !visitFilteredEdge) || (fact.getFilterState(endNodeRef.Id) == Filter.FilterState.NotFiltered) || (!originalFilterState && visitFilteredEdge)) {
                  endNodeRef.accept(this);
              }
              foreach (var visitor in visitorList) {
                visitor.visitEndXmlNameSyntax_Prefix(node.Id, endNodeRef.Id);
              }

              clearStoppedVisitors();
              if(needPreorderStop)
                return;

            }
        }

        public override void visit(Columbus.Csharp.Asg.Nodes.Structure.XmlNameSyntax node, bool callFirst = true){
          if (safeMode || visitCrossEdgeTree) {
            if (safeMode) {
              if (visitedNodes[(int)node.Id]) { // for safemode
                return;
              }
            }
            visitedNodes[(int)node.Id] = true;
          }

          foreach (var visitor in visitorList) {
            visitor.visit(node);
            incVisitorDepth(visitor);
          }

          clearStoppedVisitors();
          if(needPreorderStop)
            return;

          visitAllEdges(node, true);

          foreach (var visitor in visitorList) {
            decVisitorDepth(visitor);
            visitor.visitEnd(node);
          }

          clearStoppedVisitors();
        }

        /// <summary>
        /// It call the traversal for the edges
        /// </summary>
        /// <param name="node">[in] The node with own type</param>
        /// <param name="callVirtualBase">[in] This paramater is don't used just api copatibility used.</param>
        public void visitAllEdges(Columbus.Csharp.Asg.Nodes.Structure.XmlNodeSyntax node, bool callFirst = true){
            visitAllEdges((Columbus.Csharp.Asg.Nodes.Base.Positioned)(node),false);
        }

        /// <summary>
        /// It call the traversal for the edges
        /// </summary>
        /// <param name="node">[in] The node with own type</param>
        /// <param name="callVirtualBase">[in] This paramater is don't used just api copatibility used.</param>
        public void visitAllEdges(Columbus.Csharp.Asg.Nodes.Structure.XmlPrefixSyntax node, bool callFirst = true){
            visitAllEdges((Columbus.Csharp.Asg.Nodes.Base.Positioned)(node),false);
        }

        public override void visit(Columbus.Csharp.Asg.Nodes.Structure.XmlPrefixSyntax node, bool callFirst = true){
          if (safeMode || visitCrossEdgeTree) {
            if (safeMode) {
              if (visitedNodes[(int)node.Id]) { // for safemode
                return;
              }
            }
            visitedNodes[(int)node.Id] = true;
          }

          foreach (var visitor in visitorList) {
            visitor.visit(node);
            incVisitorDepth(visitor);
          }

          clearStoppedVisitors();
          if(needPreorderStop)
            return;

          visitAllEdges(node, true);

          foreach (var visitor in visitorList) {
            decVisitorDepth(visitor);
            visitor.visitEnd(node);
          }

          clearStoppedVisitors();
        }

        /// <summary>
        /// It call the traversal for the edges
        /// </summary>
        /// <param name="node">[in] The node with own type</param>
        /// <param name="callVirtualBase">[in] This paramater is don't used just api copatibility used.</param>
        public void visitAllEdges(Columbus.Csharp.Asg.Nodes.Structure.XmlProcessingInstructionSyntax node, bool callFirst = true){
            visitAllEdges((Columbus.Csharp.Asg.Nodes.Structure.XmlNodeSyntax)(node),false);


            Columbus.Csharp.Asg.Nodes.Base.Base genNodePtr;
            // edge: Name
            genNodePtr = fact.getRef(node.getName()) ;
            if (genNodePtr != null) {
              Columbus.Csharp.Asg.Nodes.Structure.XmlNameSyntax endNodeRef = (Columbus.Csharp.Asg.Nodes.Structure.XmlNameSyntax)(genNodePtr);
              foreach (var visitor in visitorList) {
                visitor.visitXmlProcessingInstructionSyntax_Name(node.Id, endNodeRef.Id);
              }

              clearStoppedVisitors();
              if(needPreorderStop)
                return;

              if ((!fact.IsFilterTurnedOn && !visitFilteredEdge) || (fact.getFilterState(endNodeRef.Id) == Filter.FilterState.NotFiltered) || (!originalFilterState && visitFilteredEdge)) {
                  endNodeRef.accept(this);
              }
              foreach (var visitor in visitorList) {
                visitor.visitEndXmlProcessingInstructionSyntax_Name(node.Id, endNodeRef.Id);
              }

              clearStoppedVisitors();
              if(needPreorderStop)
                return;

            }
        }

        public override void visit(Columbus.Csharp.Asg.Nodes.Structure.XmlProcessingInstructionSyntax node, bool callFirst = true){
          if (safeMode || visitCrossEdgeTree) {
            if (safeMode) {
              if (visitedNodes[(int)node.Id]) { // for safemode
                return;
              }
            }
            visitedNodes[(int)node.Id] = true;
          }

          foreach (var visitor in visitorList) {
            visitor.visit(node);
            incVisitorDepth(visitor);
          }

          clearStoppedVisitors();
          if(needPreorderStop)
            return;

          visitAllEdges(node, true);

          foreach (var visitor in visitorList) {
            decVisitorDepth(visitor);
            visitor.visitEnd(node);
          }

          clearStoppedVisitors();
        }

        /// <summary>
        /// It call the traversal for the edges
        /// </summary>
        /// <param name="node">[in] The node with own type</param>
        /// <param name="callVirtualBase">[in] This paramater is don't used just api copatibility used.</param>
        public void visitAllEdges(Columbus.Csharp.Asg.Nodes.Structure.XmlTextAttributeSyntax node, bool callFirst = true){
            visitAllEdges((Columbus.Csharp.Asg.Nodes.Structure.XmlAttributeSyntax)(node),false);
        }

        public override void visit(Columbus.Csharp.Asg.Nodes.Structure.XmlTextAttributeSyntax node, bool callFirst = true){
          if (safeMode || visitCrossEdgeTree) {
            if (safeMode) {
              if (visitedNodes[(int)node.Id]) { // for safemode
                return;
              }
            }
            visitedNodes[(int)node.Id] = true;
          }

          foreach (var visitor in visitorList) {
            visitor.visit(node);
            incVisitorDepth(visitor);
          }

          clearStoppedVisitors();
          if(needPreorderStop)
            return;

          visitAllEdges(node, true);

          foreach (var visitor in visitorList) {
            decVisitorDepth(visitor);
            visitor.visitEnd(node);
          }

          clearStoppedVisitors();
        }

        /// <summary>
        /// It call the traversal for the edges
        /// </summary>
        /// <param name="node">[in] The node with own type</param>
        /// <param name="callVirtualBase">[in] This paramater is don't used just api copatibility used.</param>
        public void visitAllEdges(Columbus.Csharp.Asg.Nodes.Structure.XmlTextSyntax node, bool callFirst = true){
            visitAllEdges((Columbus.Csharp.Asg.Nodes.Structure.XmlNodeSyntax)(node),false);
        }

        public override void visit(Columbus.Csharp.Asg.Nodes.Structure.XmlTextSyntax node, bool callFirst = true){
          if (safeMode || visitCrossEdgeTree) {
            if (safeMode) {
              if (visitedNodes[(int)node.Id]) { // for safemode
                return;
              }
            }
            visitedNodes[(int)node.Id] = true;
          }

          foreach (var visitor in visitorList) {
            visitor.visit(node);
            incVisitorDepth(visitor);
          }

          clearStoppedVisitors();
          if(needPreorderStop)
            return;

          visitAllEdges(node, true);

          foreach (var visitor in visitorList) {
            decVisitorDepth(visitor);
            visitor.visitEnd(node);
          }

          clearStoppedVisitors();
        }

        private void startPreorder(){

          if (fact == null){
            throw new CsharpException("", "Factory is null");
          }

          if (visitorList.Count <= 0){
            throw new CsharpException("", "Visitor array size 0");
          }

          if (safeMode || visitCrossEdgeTree) {
            visitedNodes.Clear();
            for (int i = 0; i < fact.Size; i++){
                visitedNodes.Add(false);
            }
          }

          if (visitCrossEdgeTree) {
            unvisitedNodes.Clear();
            for (int i = 0; i < fact.Size; i++){
                unvisitedNodes.Add(false);
            }
          }

          if (visitFilteredEdge){
            originalFilterState = fact.IsFilterTurnedOn;
            fact.turnFilterOff();
          }

          foreach (var visitor in visitorList) {
            visitor.beginVisit();
          }

        }

        private void endPreorder(){

          foreach (var visitor in visitorList) {
            visitor.finishVisit();
          }

          if (visitFilteredEdge){
            if (originalFilterState)
              fact.turnFilterOn();
          }

        }

        public void setCrossEdgeToTraversal(Types.EdgeKind edgekind){

          traversaldCrossEdges[(int)edgekind] = true;        }

        public void stop(Visitor visitor){
          stoppeds.Add(visitor);        }

        public void clearStoppedVisitors(){
          if(stoppeds == null){
            return;
          }

          foreach (var visitor in stoppeds){
            visitorList.Remove(visitor);
          }

          stoppeds.Clear();
          needPreorderStop = visitorList.Count == 0;
        }        }

}
